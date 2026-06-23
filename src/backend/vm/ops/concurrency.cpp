#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_value.h"
#include "../../channel.hh"
#include "../../scheduler.hh"
#include "../../shared_cell.hh"
#include "../../../lir/function_registry.hh"
#include "../resource_manager.hh"
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <chrono>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_concurrency(const LIR::LIR_Inst* pc) {
    auto& rm = ResourceManager::getInstance();
    switch (pc->op) {
        case LIR::LIR_Op::ChannelAlloc: {
            size_t capacity = pc->a == 0 ? 1024 : static_cast<size_t>(pc->a);
            auto channel = std::make_unique<LM::Backend::Channel>(capacity);
            channels.push_back(std::move(channel));
            registers[pc->dst] = BOX_PTR(channels.back().get());
            break;
        }
        case LIR::LIR_Op::ResourceCreate: {
            ResourceType type = static_cast<ResourceType>(to_int(registers[pc->a]));
            // Allow callers to pass additional creation args via call_args
            // (e.g. size for MEMORY, capacity for CHANNEL).
            std::vector<RegisterValue> create_args;
            for (auto arg_reg : pc->call_args) {
                if (arg_reg != UINT32_MAX) create_args.push_back(registers[arg_reg]);
            }
            int64_t id = rm.create(type, create_args);
            registers[pc->dst] = (id != -1) ? BOX_INT(id) : VAL_NIL;
            break;
        }
        case LIR::LIR_Op::ResourceCall: {
            int64_t id = to_int(registers[pc->a]);
            ResourceOperation op = static_cast<ResourceOperation>(pc->imm);
            std::vector<RegisterValue> args;
            // H34: pc->b == 0 was incorrectly treated as "no arg", which
            // silently dropped any argument that happened to land in
            // register 0. Use UINT32_MAX as the "no arg" sentinel.
            if (pc->b != UINT32_MAX) args.push_back(registers[pc->b]);
            for (auto arg_reg : pc->call_args) {
                if (arg_reg != UINT32_MAX) args.push_back(registers[arg_reg]);
            }

            registers[pc->dst] = rm.call(id, op, args, get_current_fiber());
            break;
        }
        case LIR::LIR_Op::ResourceDestroy: {
            int64_t id = to_int(registers[pc->a]);
            rm.destroy(id);
            break;
        }
        case LIR::LIR_Op::ChannelSend:
        case LIR::LIR_Op::ChannelPush: {
            // ChannelPush is an alias for ChannelSend.
            if (IS_PTR(registers[pc->a])) {
                auto* channel = (LM::Backend::Channel*)UNBOX_PTR(registers[pc->a]);
                RegisterValue value = (pc->b != UINT32_MAX) ? registers[pc->b] : VAL_NIL;
                channel->send(value, get_current_fiber());
            }
            break;
        }
        case LIR::LIR_Op::ChannelOffer: {
            if (IS_PTR(registers[pc->a])) {
                auto* channel = (LM::Backend::Channel*)UNBOX_PTR(registers[pc->a]);
                RegisterValue value = (pc->b != UINT32_MAX) ? registers[pc->b] : VAL_NIL;
                registers[pc->dst] = channel->offer(value) ? VAL_TRUE : VAL_FALSE;
            } else {
                registers[pc->dst] = VAL_FALSE;
            }
            break;
        }
        case LIR::LIR_Op::ChannelRecv:
        case LIR::LIR_Op::ChannelPop: {
            // ChannelPop is an alias for ChannelRecv.
            if (IS_PTR(registers[pc->a])) {
                auto* channel = (LM::Backend::Channel*)UNBOX_PTR(registers[pc->a]);
                registers[pc->dst] = channel->recv(get_current_fiber());
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        }
        case LIR::LIR_Op::ChannelPoll: {
            if (IS_PTR(registers[pc->a])) {
                auto* channel = (LM::Backend::Channel*)UNBOX_PTR(registers[pc->a]);
                RegisterValue out = VAL_NIL;
                registers[pc->dst] = channel->poll(out) ? out : VAL_NIL;
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        }
        case LIR::LIR_Op::ChannelClose: {
            if (IS_PTR(registers[pc->a])) {
                auto* channel = (LM::Backend::Channel*)UNBOX_PTR(registers[pc->a]);
                channel->close();
            }
            registers[pc->dst] = VAL_NIL;
            break;
        }
        case LIR::LIR_Op::ChannelHasData: {
            if (IS_PTR(registers[pc->a])) {
                auto* channel = (LM::Backend::Channel*)UNBOX_PTR(registers[pc->a]);
                registers[pc->dst] = channel->has_data() ? VAL_TRUE : VAL_FALSE;
            } else {
                registers[pc->dst] = VAL_FALSE;
            }
            break;
        }
        case LIR::LIR_Op::SharedCellAlloc: {
            uint32_t id = static_cast<uint32_t>(shared_cells.size() + 1);
            shared_cells[id] = std::make_unique<SharedCell>(id, 0);
            registers[pc->dst] = make_i64(id);
            break;
        }
        case LIR::LIR_Op::SharedCellLoad: {
            uint32_t id = static_cast<uint32_t>(as_i64(registers[pc->a]));
            auto it = shared_cells.find(id);
            registers[pc->dst] = it == shared_cells.end() ? make_i64(0) : make_i64(it->second->value.load());
            break;
        }
        case LIR::LIR_Op::SharedCellStore: {
            uint32_t id = static_cast<uint32_t>(as_i64(registers[pc->a]));
            auto it = shared_cells.find(id);
            if (it != shared_cells.end()) it->second->value.store(as_i64(registers[pc->b]));
            registers[pc->dst] = registers[pc->b];
            break;
        }
        case LIR::LIR_Op::SharedCellAdd:
        case LIR::LIR_Op::SharedCellSub: {
            uint32_t id = static_cast<uint32_t>(as_i64(registers[pc->a]));
            auto it = shared_cells.find(id);
            int64_t delta = as_i64(registers[pc->b]);
            int64_t value = 0;
            if (it != shared_cells.end()) {
                value = (pc->op == LIR::LIR_Op::SharedCellAdd)
                    ? it->second->value.fetch_add(delta) + delta
                    : it->second->value.fetch_sub(delta) - delta;
            }
            registers[pc->dst] = make_i64(value);
            break;
        }
        case LIR::LIR_Op::ParallelInit:
            registers[pc->dst] = make_i64(1);
            break;
        case LIR::LIR_Op::ParallelSync:
            break;
        case LIR::LIR_Op::TaskContextAlloc: {
            auto context = std::make_unique<TaskContext>();
            auto* raw = context.get();
            task_contexts.push_back(std::move(context));
            registers[pc->dst] = BOX_PTR(raw);
            break;
        }
        case LIR::LIR_Op::TaskContextInit:
            if (IS_PTR(registers[pc->a])) ((TaskContext*)UNBOX_PTR(registers[pc->a]))->state = TaskState::RUNNING;
            break;
        case LIR::LIR_Op::TaskSetField: {
            // H35: the value to write was being read from pc->dst (the
            // result register), which is wrong. The value lives in pc->b
            // for the modern generator pattern (e.g. when emitted as
            // `TaskSetField(0, ctx, value, imm)`); for the legacy pattern
            // `TaskSetField(value, ctx, 0, imm)` it lives in pc->dst. We
            // prefer pc->b when it is a valid non-zero register, else fall
            // back to pc->dst, so both generator call-sites work.
            if (IS_PTR(registers[pc->a])) {
                RegisterValue value;
                if (pc->b != 0 && pc->b != UINT32_MAX) {
                    value = registers[pc->b];
                } else if (pc->dst != UINT32_MAX) {
                    value = registers[pc->dst];
                } else {
                    value = VAL_NIL;
                }
                ((TaskContext*)UNBOX_PTR(registers[pc->a]))
                    ->fields[static_cast<int>(pc->imm)] = value;
            }
            break;
        }
        case LIR::LIR_Op::TaskGetField:
            if (IS_PTR(registers[pc->a])) {
                auto* context = (TaskContext*)UNBOX_PTR(registers[pc->a]);
                auto it = context->fields.find(static_cast<int>(pc->imm));
                registers[pc->dst] = it == context->fields.end() ? VAL_NIL : it->second;
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        case LIR::LIR_Op::TaskGetState: {
            // Read a task context's state into pc->dst as an int.
            // State encoding: 0=INIT, 1=RUNNING, 2=SLEEPING, 3=COMPLETED.
            if (IS_PTR(registers[pc->a])) {
                auto* context = (TaskContext*)UNBOX_PTR(registers[pc->a]);
                int64_t s = 0;
                switch (context->state) {
                    case TaskState::INIT:      s = 0; break;
                    case TaskState::RUNNING:   s = 1; break;
                    case TaskState::SLEEPING:  s = 2; break;
                    case TaskState::COMPLETED: s = 3; break;
                }
                registers[pc->dst] = make_i64(s);
            } else {
                registers[pc->dst] = make_i64(0);
            }
            break;
        }
        case LIR::LIR_Op::TaskSetState: {
            // Write the task context's state from pc->b (or pc->imm if
            // pc->b is unset).
            if (IS_PTR(registers[pc->a])) {
                auto* context = (TaskContext*)UNBOX_PTR(registers[pc->a]);
                int64_t s = (pc->b != UINT32_MAX) ? as_i64(registers[pc->b])
                                                   : static_cast<int64_t>(pc->imm);
                TaskState new_state;
                switch (s) {
                    case 0:  new_state = TaskState::INIT; break;
                    case 1:  new_state = TaskState::RUNNING; break;
                    case 2:  new_state = TaskState::SLEEPING; break;
                    case 3:  new_state = TaskState::COMPLETED; break;
                    default: new_state = TaskState::INIT; break;
                }
                context->state = new_state;
            }
            break;
        }
        case LIR::LIR_Op::SchedulerInit:
            scheduler = std::make_unique<Scheduler>();
            current_time = 0;
            registers[pc->dst] = make_i64(1);
            break;
        case LIR::LIR_Op::SchedulerAddTask:
            // No-op stub: tasks are added implicitly via TaskContextAlloc.
            // Touched here so the dispatcher does not silently drop it.
            break;
        case LIR::LIR_Op::SchedulerTick:
            // Advance the scheduler by one tick, waking up sleeping tasks
            // whose sleep_until has been reached.
            if (scheduler) scheduler->tick();
            current_time++;
            break;
        case LIR::LIR_Op::GetTickCount:
            // Return the current tick count. Prefer the scheduler's clock
            // when one exists, otherwise fall back to the VM's own counter.
            registers[pc->dst] = make_i64(
                static_cast<int64_t>(scheduler ? scheduler->current_time : current_time));
            break;
        case LIR::LIR_Op::DelayUntil: {
            // Mark the current task as sleeping until the given tick.
            // Arg layout: pc->a = target tick (int). For now this is a
            // best-effort cooperative stub: it records the wake-up time
            // but does not actually yield (the VM is single-threaded).
            int64_t target = (pc->a != UINT32_MAX) ? as_i64(registers[pc->a])
                                                   : static_cast<int64_t>(pc->imm);
            // Advance current_time so subsequent GetTickCount calls are
            // consistent.
            if (scheduler && (int64_t)scheduler->current_time < target) {
                while ((int64_t)scheduler->current_time < target) scheduler->tick();
            } else if ((int64_t)current_time < target) {
                current_time = static_cast<uint64_t>(target);
            }
            break;
        }
        case LIR::LIR_Op::SchedulerRun: {
            auto saved_registers = registers;
            const LIR::LIR_Function* saved_func = current_function_;
            auto& registry = LIR::FunctionRegistry::getInstance();
            for (auto& context_ptr : task_contexts) {
                TaskContext* context = context_ptr.get();
                if (!context || context->state == TaskState::COMPLETED) continue;
                auto name_it = context->fields.find(4);
                if (name_it == context->fields.end()) continue;

                // Extract function name from register value
                std::string func_name = "";
                if (IS_PTR(name_it->second)) {
                    ObjHeader* h = (ObjHeader*)UNBOX_PTR(name_it->second);
                    if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                        func_name = (char*)((LmBox*)h)->value.as_ptr;
                    }
                }

                auto* func = registry.getFunction(func_name);
                if (!func) continue;

                auto run_once = [&](RegisterValue field1) {
                    registers.assign(saved_registers.size(), VAL_NIL);
                    registers[1] = field1;
                    auto ch = context->fields.find(2);
                    if (ch != context->fields.end()) registers[2] = ch->second;
                    current_function_ = func;
                    execute_instructions(*func, 0, func->instructions.size());
                };

                auto data_it = context->fields.find(1);
                if (func_name.rfind("worker_", 0) == 0 && data_it != context->fields.end() && IS_PTR(data_it->second)) {
                    auto* channel = (LM::Backend::Channel*)UNBOX_PTR(data_it->second);
                    RegisterValue item = VAL_NIL;
                    while (channel->poll(item)) run_once(item);
                } else {
                    run_once(data_it == context->fields.end() ? VAL_NIL : data_it->second);
                }
                context->state = TaskState::COMPLETED;
            }
            registers = saved_registers;
            current_function_ = saved_func;
            break;
        }
        default:
            throw std::runtime_error(
                "VM: execute_concurrency: unsupported opcode " +
                std::to_string(static_cast<int>(pc->op)));
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM

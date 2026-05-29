#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_value.h"
#include "../../channel.hh"
#include "../../scheduler.hh"
#include "../../shared_cell.hh"
#include "../../../lir/function_registry.hh"
#include <string>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

namespace {
std::string value_to_std_string(RegisterValue value) {
    if (!IS_PTR(value)) return {};
    ObjHeader* h = (ObjHeader*)UNBOX_PTR(value);
    if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
        return std::string((char*)((LmBox*)h)->value.as_ptr);
    }
    return {};
}
}

void RegisterVM::execute_concurrency(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::ChannelAlloc: {
            size_t capacity = pc->a == 0 ? 1024 : static_cast<size_t>(pc->a);
            auto channel = std::make_unique<LM::Backend::Channel>(capacity);
            channels.push_back(std::move(channel));
            registers[pc->dst] = BOX_PTR(channels.back().get());
            break;
        }
        case LIR::LIR_Op::ResourceCreate: {
            if (pc->imm == static_cast<uint32_t>(LIR::ResourceType::CHANNEL)) {
                auto channel = std::make_unique<LM::Backend::Channel>(1024);
                channels.push_back(std::move(channel));
                registers[pc->dst] = BOX_PTR(channels.back().get());
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        }
        case LIR::LIR_Op::ChannelSend: {
            if (IS_PTR(registers[pc->a])) {
                auto* channel = (LM::Backend::Channel*)UNBOX_PTR(registers[pc->a]);
                channel->send(registers[pc->b], get_current_fiber());
            }
            break;
        }
        case LIR::LIR_Op::ChannelOffer: {
            if (IS_PTR(registers[pc->a])) {
                auto* channel = (LM::Backend::Channel*)UNBOX_PTR(registers[pc->a]);
                registers[pc->dst] = channel->offer(registers[pc->b]) ? VAL_TRUE : VAL_FALSE;
            } else {
                registers[pc->dst] = VAL_FALSE;
            }
            break;
        }
        case LIR::LIR_Op::ChannelRecv: {
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
        case LIR::LIR_Op::TaskSetField:
            if (IS_PTR(registers[pc->a])) ((TaskContext*)UNBOX_PTR(registers[pc->a]))->fields[static_cast<int>(pc->imm)] = registers[pc->dst];
            break;
        case LIR::LIR_Op::TaskGetField:
            if (IS_PTR(registers[pc->a])) {
                auto* context = (TaskContext*)UNBOX_PTR(registers[pc->a]);
                auto it = context->fields.find(static_cast<int>(pc->imm));
                registers[pc->dst] = it == context->fields.end() ? VAL_NIL : it->second;
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        case LIR::LIR_Op::SchedulerInit:
            scheduler = std::make_unique<Scheduler>();
            registers[pc->dst] = make_i64(1);
            break;
        case LIR::LIR_Op::SchedulerAddTask:
            // Task contexts are stored as they are allocated; SchedulerRun executes pending contexts sequentially.
            break;
        case LIR::LIR_Op::SchedulerRun: {
            auto saved_registers = registers;
            const LIR::LIR_Function* saved_func = current_function_;
            auto& registry = LIR::FunctionRegistry::getInstance();
            for (auto& context_ptr : task_contexts) {
                TaskContext* context = context_ptr.get();
                if (!context || context->state == TaskState::COMPLETED) continue;
                auto name_it = context->fields.find(4);
                if (name_it == context->fields.end()) continue;
                std::string func_name = value_to_std_string(name_it->second);
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
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM

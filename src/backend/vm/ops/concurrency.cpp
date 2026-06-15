#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_value.h"
#include "../../channel.hh"
#include "../../scheduler.hh"
#include "../../shared_cell.hh"
#include "../../../lir/function_registry.hh"
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <sstream>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

namespace {
std::string value_to_std_string(RegisterValue value) {
    if (is_integer(value)) return std::to_string(as_i64(value));
    if (!IS_PTR(value)) return {};
    ObjHeader* h = (ObjHeader*)UNBOX_PTR(value);
    if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
        return std::string((char*)((LmBox*)h)->value.as_ptr);
    }
    return {};
}

static std::mutex g_resource_mutex;
static std::unordered_map<int64_t, std::shared_ptr<std::fstream>> g_file_resources;
static std::unordered_map<int64_t, int> g_socket_resources;
static int64_t g_next_resource_id = 1;
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
            std::lock_guard<std::mutex> lock(g_resource_mutex);
            int64_t id = g_next_resource_id++;
            LIR::ResourceType type = static_cast<LIR::ResourceType>(to_int(registers[pc->a]));
            
            if (type == LIR::ResourceType::FILE) {
                g_file_resources[id] = std::make_shared<std::fstream>();
                registers[pc->dst] = BOX_INT(id);
            } else if (type == LIR::ResourceType::SOCKET) {
                int fd = socket(AF_INET, SOCK_STREAM, 0);
                g_socket_resources[id] = fd;
                registers[pc->dst] = BOX_INT(id);
            } else if (type == LIR::ResourceType::CHANNEL) {
                auto channel = std::make_unique<LM::Backend::Channel>(1024);
                channels.push_back(std::move(channel));
                registers[pc->dst] = BOX_PTR(channels.back().get());
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        }
        case LIR::LIR_Op::ResourceCall: {
            int64_t id = to_int(registers[pc->a]);
            LIR::ResourceOperation op = static_cast<LIR::ResourceOperation>(pc->imm);
            
            std::lock_guard<std::mutex> lock(g_resource_mutex);
            if (g_file_resources.count(id)) {
                auto file = g_file_resources[id];
                if (op == LIR::ResourceOperation::OPEN) {
                    std::string path = value_to_std_string(registers[pc->b]);
                    std::string mode_str = value_to_std_string(registers[pc->call_args[0]]);
                    std::ios_base::openmode mode = (std::ios_base::openmode)0;
                    if (mode_str.find('r') != std::string::npos) mode |= std::ios_base::in;
                    if (mode_str.find('w') != std::string::npos) mode |= std::ios_base::out;
                    if (mode_str.find('a') != std::string::npos) mode |= std::ios_base::app;
                    file->open(path, mode);
                    registers[pc->dst] = file->is_open() ? VAL_TRUE : VAL_FALSE;
                } else if (op == LIR::ResourceOperation::READ) {
                    if (file->is_open()) {
                        std::stringstream ss;
                        ss << file->rdbuf();
                        registers[pc->dst] = BOX_PTR(lm_box_string(ss.str().c_str()));
                    } else registers[pc->dst] = VAL_NIL;
                } else if (op == LIR::ResourceOperation::WRITE) {
                    if (file->is_open()) {
                        std::string data = value_to_std_string(registers[pc->b]);
                        (*file) << data;
                        file->flush();
                        registers[pc->dst] = VAL_TRUE;
                    } else registers[pc->dst] = VAL_FALSE;
                } else if (op == LIR::ResourceOperation::CLOSE) {
                    if (file->is_open()) file->close();
                    registers[pc->dst] = VAL_TRUE;
                }
            } else if (g_socket_resources.count(id)) {
                int fd = g_socket_resources[id];
                if (op == LIR::ResourceOperation::CONNECT) {
                    std::string addr_str = value_to_std_string(registers[pc->b]);
                    int port = (int)to_int(registers[pc->call_args[0]]);
                    struct sockaddr_in serv_addr;
                    serv_addr.sin_family = AF_INET;
                    serv_addr.sin_port = htons(port);
                    inet_pton(AF_INET, addr_str.c_str(), &serv_addr.sin_addr);
                    int res = connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
                    registers[pc->dst] = (res == 0) ? VAL_TRUE : VAL_FALSE;
                } else if (op == LIR::ResourceOperation::SEND) {
                    std::string data = value_to_std_string(registers[pc->b]);
                    ssize_t bytes = send(fd, data.c_str(), data.length(), 0);
                    registers[pc->dst] = BOX_INT((int64_t)bytes);
                } else if (op == LIR::ResourceOperation::RECEIVE) {
                    char buf[4096];
                    ssize_t bytes = recv(fd, buf, 4095, 0);
                    if (bytes > 0) {
                        buf[bytes] = '\0';
                        registers[pc->dst] = BOX_PTR(lm_box_string(buf));
                    } else registers[pc->dst] = VAL_NIL;
                } else if (op == LIR::ResourceOperation::CLOSE) {
                    close(fd);
                    registers[pc->dst] = VAL_TRUE;
                }
            } else {
                registers[pc->dst] = VAL_NIL;
            }
            break;
        }
        case LIR::LIR_Op::ResourceDestroy: {
            int64_t id = to_int(registers[pc->a]);
            std::lock_guard<std::mutex> lock(g_resource_mutex);
            if (g_file_resources.count(id)) {
                if (g_file_resources[id]->is_open()) g_file_resources[id]->close();
                g_file_resources.erase(id);
            } else if (g_socket_resources.count(id)) {
                close(g_socket_resources[id]);
                g_socket_resources.erase(id);
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

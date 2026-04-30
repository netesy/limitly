#include "../../lir/lir.hh"
#include "../../lir/functions.hh"
#include "../../lir/function_registry.hh"
#include "../../lir/builtin_functions.hh"
#include "../types.hh"
#include "register.hh"
#include "../../lir/lir.hh"
#include "../../runtime/runtime.h"
#include "../../runtime/runtime_list.h"
#include "../../runtime/runtime_dict.h"
#include "../../runtime/runtime_tuple.h"
#include "../../runtime/runtime_value.h"
#include <iostream>
#include <variant>
#include <memory>
#include <cstring>
#include <cstdint>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

// Forward declarations for helper functions
int64_t to_int(const RegisterValue& value);
uint64_t to_uint(const RegisterValue& value);
double to_float(const RegisterValue& value);
bool to_bool(const RegisterValue& value);

constexpr const char* INTERNAL_ENUM_FRAME_TYPE = "__lir_internal_enum__";

// Boxing/Unboxing functions for C runtime integration
void* box_register_value(const RegisterValue& value) {
    // Use the runtime boxing functions
    if (std::holds_alternative<int64_t>(value)) {
        return lm_box_int(to_int(value));
    } else if (std::holds_alternative<double>(value)) {
        return lm_box_float(to_float(value));
    } else if (std::holds_alternative<bool>(value)) {
        return lm_box_bool(to_bool(value) ? 1 : 0);
    } else if (std::holds_alternative<std::string>(value)) {
        return lm_box_string(std::get<std::string>(value).c_str());
    } else if (std::holds_alternative<uint64_t>(value)) {
        return lm_box_int(static_cast<int64_t>(to_uint(value)));
    } else {
        return lm_box_nullptr(); // nullptr stays nullptr
    }
}

// Hash function for boxed values - now defined in runtime_dict.c
extern "C" {
    uint64_t hash_boxed_value(void* key);
    int cmp_boxed_value(void* k1, void* k2);
}

RegisterValue unbox_register_value(void* boxed_value) {
    if (!boxed_value) {
        return nullptr;
    }
    
    // Safety check: if the pointer is very small, it's not a valid object
    if (reinterpret_cast<uintptr_t>(boxed_value) < 4096) {
        return nullptr;
    }

    // Use the runtime unboxing functions
    LmBox* box = static_cast<LmBox*>(boxed_value);
    
    switch (box->type) {
        case LM_BOX_INT:
            return box->value.as_int;
        case LM_BOX_FLOAT:
            return box->value.as_float;
        case LM_BOX_BOOL:
            return box->value.as_bool ? true : false;
        case LM_BOX_STRING:
            return std::string(lm_unbox_string(box));
        case LM_BOX_NULLPTR:
            return nullptr;
        default:
            return nullptr;
    }
}

// Helper functions
bool is_numeric(const RegisterValue& value) {
    return std::holds_alternative<int64_t>(value) || 
           std::holds_alternative<double>(value) || 
           std::holds_alternative<uint64_t>(value);
}

int64_t to_int(const RegisterValue& value) {
    if (std::holds_alternative<int64_t>(value)) {
        return std::get<int64_t>(value);
    } else if (std::holds_alternative<double>(value)) {
        return static_cast<int64_t>(std::get<double>(value));
    } else if (std::holds_alternative<uint64_t>(value)) {
        return static_cast<int64_t>(std::get<uint64_t>(value));
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? 1 : 0;
    } else if (std::holds_alternative<std::string>(value)) {
        try {
            return std::stoll(std::get<std::string>(value));
        } catch (...) {
            return 0;
        }
    } else {
        return 0;
    }
}

uint64_t to_uint(const RegisterValue& value) {
    if (std::holds_alternative<uint64_t>(value)) {
        return std::get<uint64_t>(value);
    } else if (std::holds_alternative<int64_t>(value)) {
        return static_cast<uint64_t>(std::get<int64_t>(value));
    } else if (std::holds_alternative<double>(value)) {
        return static_cast<uint64_t>(std::get<double>(value));
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? 1 : 0;
    } else if (std::holds_alternative<std::string>(value)) {
        try {
            return std::stoull(std::get<std::string>(value));
        } catch (...) {
            return 0;
        }
    } else {
        return 0;
    }
}

double to_float(const RegisterValue& value) {
    if (std::holds_alternative<double>(value)) {
        return std::get<double>(value);
    } else if (std::holds_alternative<int64_t>(value)) {
        return static_cast<double>(std::get<int64_t>(value));
    } else if (std::holds_alternative<uint64_t>(value)) {
        return static_cast<double>(std::get<uint64_t>(value));
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? 1.0 : 0.0;
    } else if (std::holds_alternative<std::string>(value)) {
        try {
            return std::stod(std::get<std::string>(value));
        } catch (...) {
            return 0.0;
        }
    } else {
        return 0.0;
    }
}

bool to_bool(const RegisterValue& value) {
    if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value);
    } else if (std::holds_alternative<int64_t>(value)) {
        return to_int(value) != 0;
    } else if (std::holds_alternative<double>(value)) {
        return to_float(value) != 0.0;
    } else if (std::holds_alternative<std::string>(value)) {
        return !std::get<std::string>(value).empty();
    } else if (std::holds_alternative<FrameInstancePtr>(value)) {
        return std::get<std::shared_ptr<struct FrameInstance>>(value) != nullptr;
    } else {
        return false;
    }
}

void RegisterVM::execute_task_body(TaskContext* task, const LIR::LIR_Function& function) {
    // Get task function name from task context field 4
    auto func_name_it = task->fields.find(4);
    if (func_name_it == task->fields.end()) {
        std::cerr << "[ERROR] Task function name not found in task context" << std::endl;
        return;
    }

    // Extract function name from register value
    std::string task_func_name;
    if (std::holds_alternative<std::string>(func_name_it->second)) {
        task_func_name = this->to_string(func_name_it->second);
    } else {
        std::cerr << "[ERROR] Task function name is not a string" << std::endl;
        return;
    }

    // Get task function from registry
    auto& func_registry = LIR::FunctionRegistry::getInstance();
    LIR::LIR_Function* task_func = func_registry.getFunction(task_func_name);
    if (!task_func) {
        std::cerr << "[ERROR] Task function '" << task_func_name << "' not found in registry" << std::endl;
        return;
    }

    std::cout << "Task calling function: " << task_func_name << std::endl;

    // Save current register state
    auto saved_registers = registers;

    // Initialize a fresh register context for this task
    registers.clear();
    registers.resize(1024);
    for (auto& reg : registers) {
        reg = nullptr;
    }

    // Set up task context parameters in fresh register space
    if (task) {
        // Set task ID from task context field 0
        auto task_id_it = task->fields.find(0);
        if (task_id_it != task->fields.end()) {
            registers[0] = task_id_it->second;
        }

        // Set loop variable value from task context field 1
        auto loop_var_it = task->fields.find(1);
        if (loop_var_it != task->fields.end()) {
            registers[1] = loop_var_it->second;
        }

        // Set channel from task context field 2
        auto channel_it = task->fields.find(2);
        if (channel_it != task->fields.end()) {
            registers[2] = channel_it->second;
        }
    }

    // Execute task function
    current_function_ = task_func;
    execute_instructions(*task_func, 0, task_func->instructions.size());
    
    // Restore register state and current function
    registers = saved_registers;
    current_function_ = nullptr;
}

void RegisterVM::execute_function(const LIR::LIR_Function& function) {
    execute_instructions(function, 0, function.instructions.size());
}

void RegisterVM::execute_lir_function(const LIR::LIRFunction& function) {
    // Create a temporary LIR_Function wrapper to reuse existing execution logic
    LIR::LIR_Function temp_wrapper(function.getName(), function.getParameters().size());
    temp_wrapper.instructions = function.getInstructions();
    execute_instructions(temp_wrapper, 0, function.getInstructions().size());
}

std::string RegisterVM::to_string(const RegisterValue& value) const {
    return std::visit(overloaded{
        [](std::nullptr_t) -> std::string { return "nil"; },
        [](int64_t v) -> std::string { return std::to_string(v); },
        [](uint64_t v) -> std::string { return std::to_string(v); },
        [](double v) -> std::string {
            std::ostringstream oss;
            oss << v;
            return oss.str();
        },
        [](bool v) -> std::string { return v ? "true" : "false"; },
        [](const std::string& v) -> std::string { return v; },
        [this](const FrameInstancePtr& frame) -> std::string {
            if (!frame) return "nil";
            std::string result = frame->frame_type + "{";
            for (size_t i = 0; i < frame->fields.size(); ++i) {
                if (i > 0) result += ", ";
                result += "field_" + std::to_string(i) + ": " + this->to_string(frame->fields[i]);
            }
            result += "}";
            return result;
        }
    }, value);
}

ValuePtr RegisterVM::createErrorValue(const std::string& errorType, const std::string& message) {
    auto nil_type = std::make_shared<::Type>(TypeTag::Nil);
    return std::make_shared<Value>(nil_type, "Error: " + errorType + ": " + message);
}

ValuePtr RegisterVM::createSuccessValue(const RegisterValue& value) {
    if (std::holds_alternative<std::string>(value)) {
        auto string_type = std::make_shared<::Type>(TypeTag::String);
        return std::make_shared<Value>(string_type, this->to_string(value));
    } else if (std::holds_alternative<int64_t>(value)) {
        auto int_type = std::make_shared<::Type>(TypeTag::Int64);
        return std::make_shared<Value>(int_type, std::to_string(to_int(value)));
    } else if (std::holds_alternative<double>(value)) {
        auto float_type = std::make_shared<::Type>(TypeTag::Float64);
        return std::make_shared<Value>(float_type, std::to_string(to_float(value)));
    } else if (std::holds_alternative<bool>(value)) {
        auto bool_type = std::make_shared<::Type>(TypeTag::Bool);
        return std::make_shared<Value>(bool_type, to_bool(value) ? "true" : "false");
    } else {
        auto nil_type = std::make_shared<::Type>(TypeTag::Nil);
        return std::make_shared<Value>(nil_type, "nil");
    }
}

bool RegisterVM::isErrorValue(LIR::Reg reg) const {
    auto& value = registers[reg];
    if (std::holds_alternative<int64_t>(value)) {
        int64_t int_val = to_int(value);
        return int_val <= -1000000; // Error IDs are negative numbers starting from -1000000
    }
    return false;
}

RegisterVM::RegisterVM() 
    : type_system(std::make_unique<TypeSystem>()) {
    registers.resize(1024, nullptr);
    scheduler = std::make_unique<Scheduler>();
    current_time = 0;
    current_function_ = nullptr;
    
    // Initialize shared variables
    shared_variables.emplace(std::piecewise_construct, 
        std::forward_as_tuple("shared_counter"), 
        std::forward_as_tuple(0));
}

void RegisterVM::reset() {
    std::fill(registers.begin(), registers.end(), nullptr);
    argument_stack.clear();
    task_contexts.clear();
    channels.clear();
    scheduler = std::make_unique<Scheduler>();
    current_time = 0;
    current_function_ = nullptr;
    
    // Reset shared variables
    shared_variables.clear();
    shared_variables.emplace(std::piecewise_construct, 
        std::forward_as_tuple("shared_counter"), 
        std::forward_as_tuple(0));
    
    // Reset SharedCell operations
    shared_cells.clear();
    
    // Reset atomic variables and work queues
    default_atomic.store(0);
    work_queues.clear();
    work_queue_counter.store(0);
    instruction_count = 0;
}

void RegisterVM::execute_instructions(const LIR::LIR_Function& function, size_t start_pc, size_t end_pc) {
    
    const LIR::LIR_Inst* pc = function.instructions.data() + start_pc;
    const LIR::LIR_Inst* end = function.instructions.data() + end_pc;
    
    // Main execution loop using switch statement
    while (pc < end) {
        std::cout << "[VM TRACE] " << function.name << " PC=" << (pc - function.instructions.data()) << " " << pc->to_string() << std::endl;
        instruction_count++;
        if (instruction_count > MAX_INSTRUCTIONS) {
            std::cerr << "Error: Instruction limit exceeded (" << MAX_INSTRUCTIONS << ") - possible infinite loop" << std::endl;
            return;
        }
        
        switch (pc->op) {
            case LIR::LIR_Op::Nop: {
                // No operation
                break;
            }

            case LIR::LIR_Op::TraitCallMethod: {
                // Dynamic dispatch (simplified for VM)
                if (!pc->call_args.empty() && pc->call_args[0] < registers.size()) {
                    auto& obj = registers[pc->call_args[0]];
                    if (std::holds_alternative<FrameInstancePtr>(obj)) {
                        auto frame = std::get<std::shared_ptr<struct FrameInstance>>(obj);
                        if (frame) {
                            std::string frame_method_name = frame->frame_type + "." + pc->func_name;
                            auto& func_manager = LIR::LIRFunctionManager::getInstance();
                            if (!func_manager.hasFunction(frame_method_name)) {
                                frame_method_name = pc->type_name + "." + pc->func_name;
                            }
                            
                            if (func_manager.hasFunction(frame_method_name)) {
                                auto func = func_manager.getFunction(frame_method_name);
                                std::vector<RegisterValue> arg_vals;
                                for (auto arg_reg : pc->call_args) arg_vals.push_back(registers[arg_reg]);

                                auto saved_registers = registers;
                                const LIR::LIR_Function* saved_func = current_function_;
                                registers.assign(registers.size(), nullptr);
                                for (size_t i = 0; i < arg_vals.size() && i < registers.size(); ++i) registers[i] = arg_vals[i];

                                LIR::LIR_Function temp_wrapper(func->getName(), static_cast<uint32_t>(arg_vals.size()));
                                temp_wrapper.instructions = func->getInstructions();
                                current_function_ = &temp_wrapper;
                                execute_instructions(temp_wrapper, 0, temp_wrapper.instructions.size());

                                RegisterValue return_value = registers[0];
                                registers = saved_registers;
                                current_function_ = saved_func;
                                registers[pc->dst] = return_value;
                            }
                        }
                    }
                }
                break;
            }
            case LIR::LIR_Op::FrameGetFieldAtomic: {
                // In Register VM, we use mutex for atomic frame field access
                if (std::holds_alternative<FrameInstancePtr>(registers[pc->a])) {
                    auto frame = std::get<std::shared_ptr<struct FrameInstance>>(registers[pc->a]);
                    if (frame && pc->b < frame->fields.size()) {
                        std::lock_guard<std::mutex> lock(frame->mutex);
                        registers[pc->dst] = frame->fields[pc->b];
                    } else {
                        registers[pc->dst] = nullptr;
                    }
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::FrameSetFieldAtomic: {
                if (std::holds_alternative<FrameInstancePtr>(registers[pc->dst])) {
                    auto frame = std::get<std::shared_ptr<struct FrameInstance>>(registers[pc->dst]);
                    if (frame) {
                        std::lock_guard<std::mutex> lock(frame->mutex);
                        frame->setField(pc->a, registers[pc->b]);
                    }
                }
                break;
            }
            case LIR::LIR_Op::FrameFieldAtomicAdd: {
                if (std::holds_alternative<FrameInstancePtr>(registers[pc->dst])) {
                    auto frame = std::get<std::shared_ptr<struct FrameInstance>>(registers[pc->dst]);
                    if (frame) {
                        std::lock_guard<std::mutex> lock(frame->mutex);
                        auto& field = frame->fields[pc->a];
                        if (std::holds_alternative<int64_t>(field) && std::holds_alternative<int64_t>(registers[pc->b])) {
                            field = to_int(field) + to_int(registers[pc->b]);
                        }
                    }
                }
                break;
            }
            case LIR::LIR_Op::FrameFieldAtomicSub: {
                if (std::holds_alternative<FrameInstancePtr>(registers[pc->dst])) {
                    auto frame = std::get<std::shared_ptr<struct FrameInstance>>(registers[pc->dst]);
                    if (frame) {
                        std::lock_guard<std::mutex> lock(frame->mutex);
                        auto& field = frame->fields[pc->a];
                        if (std::holds_alternative<int64_t>(field) && std::holds_alternative<int64_t>(registers[pc->b])) {
                            field = to_int(field) - to_int(registers[pc->b]);
                        }
                    }
                }
                break;
            }

            case LIR::LIR_Op::MakeTraitObject: {
                if (pc->a < registers.size()) {
                    registers[pc->dst] = registers[pc->a];
                }
                break;
            }
            case LIR::LIR_Op::Mov: {
                registers[pc->dst] = registers[pc->a];
                break;
            }
            case LIR::LIR_Op::LoadConst: {
                ValuePtr cv = pc->const_val;
                if (!cv) {
                    registers[pc->dst] = nullptr;
                } else {
                    // Use TypeSystem to handle type conversion properly
                    TypePtr target_type;
                    switch (cv->type->tag) {
                        case TypeTag::Int8:
                        case TypeTag::Int16:
                        case TypeTag::Int32:
                            target_type = type_system->INT32_TYPE;
                            break;
                        case TypeTag::Int:    
                        case TypeTag::Int64:
                            target_type = type_system->INT64_TYPE;
                            break;
                        case TypeTag::UInt8:
                        case TypeTag::UInt16:
                        case TypeTag::UInt32:
                            target_type = type_system->UINT32_TYPE;
                            break;
                        case TypeTag::UInt:    
                        case TypeTag::UInt64:
                            target_type = type_system->UINT64_TYPE;
                            break;    
                        case TypeTag::Float32:
                        case TypeTag::Float64:
                            target_type = type_system->FLOAT64_TYPE;
                            break;
                        case TypeTag::Bool:
                            target_type = type_system->BOOL_TYPE;
                            break;
                        case TypeTag::String:
                            target_type = type_system->STRING_TYPE;
                            break;
                        default:
                            target_type = type_system->NIL_TYPE;
                            break;
                    }
                    
                    // Create a typed value and convert to register representation
                    ValuePtr typed_value = type_system->createValue(target_type);
                    typed_value->data = cv->data;
                    
                    // Convert to register value representation
                    if (target_type->tag == TypeTag::Int32 || target_type->tag == TypeTag::Int64) {
                        registers[pc->dst] = static_cast<int64_t>(std::stoll(cv->data));
                    } else if (target_type->tag == TypeTag::UInt32 || target_type->tag == TypeTag::UInt64) {
                        registers[pc->dst] = static_cast<uint64_t>(std::stoull(cv->data));
                    } else if (target_type->tag == TypeTag::Float32) {
                        registers[pc->dst] = std::stof(cv->data);
                    } else if (target_type->tag == TypeTag::Float64) {
                        registers[pc->dst] = std::stod(cv->data);
                    } else if (target_type->tag == TypeTag::Bool) {
                        registers[pc->dst] = static_cast<bool>(cv->data == "true");
                    } else if (target_type->tag == TypeTag::String) {
                        registers[pc->dst] = cv->data;
                    } else {
                        registers[pc->dst] = nullptr;
                    }
                }
                break;
            }
            case LIR::LIR_Op::Ret: {
                // Copy return value from specified register to register 0 (standard return register)
                if (pc->a != 0) {
                    registers[0] = registers[pc->a];
                } else if (pc->dst != 0) {
                    registers[0] = registers[pc->dst];
                }
                return;
            }
            case LIR::LIR_Op::Add: {
                if (pc->dst >= registers.size() || pc->a >= registers.size() || pc->b >= registers.size()) break;
                const RegisterValue& val_a = registers[pc->a];
                const RegisterValue& val_b = registers[pc->b];
                if (is_numeric(val_a) && is_numeric(val_b)) {
                    if (std::holds_alternative<double>(val_a) || std::holds_alternative<double>(val_b)) {
                        registers[pc->dst] = to_float(val_a) + to_float(val_b);
                    } else {
                        registers[pc->dst] = to_int(val_a) + to_int(val_b);
                    }
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::Sub: {
                if (pc->dst >= registers.size() || pc->a >= registers.size() || pc->b >= registers.size()) break;
                const RegisterValue& val_a = registers[pc->a];
                const RegisterValue& val_b = registers[pc->b];
                if (is_numeric(val_a) && is_numeric(val_b)) {
                    if (std::holds_alternative<double>(val_a) || std::holds_alternative<double>(val_b)) {
                        registers[pc->dst] = to_float(val_a) - to_float(val_b);
                    } else {
                        registers[pc->dst] = to_int(val_a) - to_int(val_b);
                    }
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::Mul: {
                if (pc->dst >= registers.size() || pc->a >= registers.size() || pc->b >= registers.size()) break;
                const RegisterValue& val_a = registers[pc->a];
                const RegisterValue& val_b = registers[pc->b];
                if (is_numeric(val_a) && is_numeric(val_b)) {
                    if (std::holds_alternative<double>(val_a) || std::holds_alternative<double>(val_b)) {
                        registers[pc->dst] = to_float(val_a) * to_float(val_b);
                    } else {
                        registers[pc->dst] = to_int(val_a) * to_int(val_b);
                    }
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::Div: {
                if (pc->dst >= registers.size() || pc->a >= registers.size() || pc->b >= registers.size()) break;
                const RegisterValue& val_a = registers[pc->a];
                const RegisterValue& val_b = registers[pc->b];
                
                if (is_numeric(val_a) && is_numeric(val_b)) {
                    double fa = to_float(val_a);
                    double fb = to_float(val_b);
                    
                    if (fb != 0.0) {
                        if (std::holds_alternative<double>(val_a) || std::holds_alternative<double>(val_b)) {
                            registers[pc->dst] = fa / fb;
                        } else {
                            int64_t ia = to_int(val_a);
                            int64_t ib = to_int(val_b);
                            if (ib == -1 && (uint64_t)ia == 0x8000000000000000ULL) {
                                registers[pc->dst] = ia;
                            } else {
                                registers[pc->dst] = ia / ib;
                            }
                        }
                    } else {
                         std::cerr << "VM Error: Division by zero" << std::endl;
                         registers[pc->dst] = nullptr;
                    }
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::Mod: {
                if (pc->dst >= registers.size() || pc->a >= registers.size() || pc->b >= registers.size()) break;
                const RegisterValue& val_a = registers[pc->a];
                const RegisterValue& val_b = registers[pc->b];
                if (is_numeric(val_a) && is_numeric(val_b)) {
                    int64_t ia = to_int(val_a);
                    int64_t ib = to_int(val_b);
                    if (ib != 0) {
                        if (ib == -1 && (uint64_t)ia == 0x8000000000000000ULL) {
                            registers[pc->dst] = (int64_t)0;
                        } else {
                            registers[pc->dst] = ia % ib;
                        }
                    } else {
                        std::cerr << "VM Error: Modulo by zero" << std::endl;
                        registers[pc->dst] = nullptr;
                    }
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::And: {
                // Logical AND for booleans
                const RegisterValue* temp_a = &registers[pc->a];
                const RegisterValue* temp_b = &registers[pc->b];
                registers[pc->dst] = to_bool(*temp_a) && to_bool(*temp_b);
                break;
            }
            case LIR::LIR_Op::Or: {
                // Logical OR for booleans
                const RegisterValue* temp_a = &registers[pc->a];
                const RegisterValue* temp_b = &registers[pc->b];
                registers[pc->dst] = to_bool(*temp_a) || to_bool(*temp_b);
                break;
            }
            case LIR::LIR_Op::Xor: {
                // Logical XOR for booleans
                const RegisterValue* temp_a = &registers[pc->a];
                const RegisterValue* temp_b = &registers[pc->b];
                bool a_bool = to_bool(*temp_a);
                bool b_bool = to_bool(*temp_b);
                registers[pc->dst] = (a_bool && !b_bool) || (!a_bool && b_bool);
                break;
            }
            case LIR::LIR_Op::CmpLT: {
                const RegisterValue* temp_a = &registers[pc->a];
                const RegisterValue* temp_b = &registers[pc->b];
                if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
                    if (std::holds_alternative<double>(*temp_a) || std::holds_alternative<double>(*temp_b)) {
                        registers[pc->dst] = to_float(*temp_a) < to_float(*temp_b);
                    } else {
                        registers[pc->dst] = to_int(*temp_a) < to_int(*temp_b);
                    }
                } else {
                    registers[pc->dst] = to_string(*temp_a) < to_string(*temp_b);
                }
                break;
            }
            case LIR::LIR_Op::CmpLE: {
                const RegisterValue* temp_a = &registers[pc->a];
                const RegisterValue* temp_b = &registers[pc->b];
                if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
                    if (std::holds_alternative<double>(*temp_a) || std::holds_alternative<double>(*temp_b)) {
                        registers[pc->dst] = to_float(*temp_a) <= to_float(*temp_b);
                    } else {
                        registers[pc->dst] = to_int(*temp_a) <= to_int(*temp_b);
                    }
                } else {
                    registers[pc->dst] = to_string(*temp_a) <= to_string(*temp_b);
                }
                break;
            }
            case LIR::LIR_Op::CmpGT: {
                const RegisterValue* temp_a = &registers[pc->a];
                const RegisterValue* temp_b = &registers[pc->b];
                if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
                    if (std::holds_alternative<double>(*temp_a) || std::holds_alternative<double>(*temp_b)) {
                        registers[pc->dst] = to_float(*temp_a) > to_float(*temp_b);
                    } else {
                        registers[pc->dst] = to_int(*temp_a) > to_int(*temp_b);
                    }
                } else {
                    registers[pc->dst] = to_string(*temp_a) > to_string(*temp_b);
                }
                break;
            }
            case LIR::LIR_Op::CmpGE: {
                const RegisterValue* temp_a = &registers[pc->a];
                const RegisterValue* temp_b = &registers[pc->b];
                if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
                    if (std::holds_alternative<double>(*temp_a) || std::holds_alternative<double>(*temp_b)) {
                        registers[pc->dst] = to_float(*temp_a) >= to_float(*temp_b);
                    } else {
                        registers[pc->dst] = to_int(*temp_a) >= to_int(*temp_b);
                    }
                } else {
                    registers[pc->dst] = to_string(*temp_a) >= to_string(*temp_b);
                }
                break;
            }
            case LIR::LIR_Op::CmpEQ: {
                const RegisterValue* temp_a = &registers[pc->a];
                const RegisterValue* temp_b = &registers[pc->b];
                if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
                    if (std::holds_alternative<double>(*temp_a) || std::holds_alternative<double>(*temp_b)) {
                        registers[pc->dst] = to_float(*temp_a) == to_float(*temp_b);
                    } else {
                        registers[pc->dst] = to_int(*temp_a) == to_int(*temp_b);
                    }
                } else {
                    registers[pc->dst] = to_string(*temp_a) == to_string(*temp_b);
                }
                break;
            }
            case LIR::LIR_Op::CmpNEQ: {
                const RegisterValue* temp_a = &registers[pc->a];
                const RegisterValue* temp_b = &registers[pc->b];
                if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
                    if (std::holds_alternative<double>(*temp_a) || std::holds_alternative<double>(*temp_b)) {
                        registers[pc->dst] = to_float(*temp_a) != to_float(*temp_b);
                    } else {
                        registers[pc->dst] = to_int(*temp_a) != to_int(*temp_b);
                    }
                } else {
                    registers[pc->dst] = to_string(*temp_a) != to_string(*temp_b);
                }
                break;
            }
            case LIR::LIR_Op::Jump: {
                pc = function.instructions.data() + (pc->imm);
                if (pc >= end) return;
                continue; // Skip pc++ at end of loop
            }
            case LIR::LIR_Op::JumpIfFalse: {
                if (!to_bool(registers[pc->a])) {
                    pc = function.instructions.data() + (pc->imm);
                    if (pc >= end) return;
                    continue; // Skip pc++ at end of loop
                }
                break;
            }
            case LIR::LIR_Op::Return: {
                // Copy return value from specified register to register 0 (standard return register)
                if (pc->a != 0) {
                    registers[0] = registers[pc->a];
                } else if (pc->dst != 0) {
                    registers[0] = registers[pc->dst];
                }
                return;
            }
            case LIR::LIR_Op::PrintInt: {
                std::cout << to_int(registers[pc->a]) << std::endl;
                break;
            }
            case LIR::LIR_Op::ChannelAlloc: {
                size_t capacity = static_cast<size_t>(to_int(registers[pc->a]));
                if (capacity == 0) capacity = 32;
                auto channel = std::make_unique<Channel>(capacity);
                uint64_t channel_id = channels.size();
                channels.push_back(std::move(channel));
                registers[pc->dst] = static_cast<int64_t>(channel_id);
                break;
            }
            case LIR::LIR_Op::ChannelSend: {
                uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
                RegisterValue value = registers[pc->b];
                if (channel_id < channels.size()) {
                    // For now, use non-blocking offer. TODO: Implement proper blocking send with fiber suspension
                    bool success = channels[channel_id]->offer(value);
                    registers[pc->dst] = static_cast<int64_t>(success ? 1 : 0);
                } else {
                    registers[pc->dst] = static_cast<int64_t>(0);
                }
                break;
            }
            case LIR::LIR_Op::ChannelOffer: {
                uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
                RegisterValue value = registers[pc->b];
                if (channel_id < channels.size()) {
                    bool success = channels[channel_id]->offer(value);
                    registers[pc->dst] = static_cast<int64_t>(success ? 1 : 0);
                } else {
                    registers[pc->dst] = static_cast<int64_t>(0);
                }
                break;
            }
            case LIR::LIR_Op::ChannelRecv: {
                uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
                if (channel_id < channels.size()) {
                    // For now, use non-blocking poll. TODO: Implement proper blocking recv with fiber suspension
                    RegisterValue value;
                    bool success = channels[channel_id]->poll(value);
                    if (success) {
                        registers[pc->dst] = value;
                    } else {
                        registers[pc->dst] = nullptr;
                    }
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::ChannelPoll: {
                uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
                if (channel_id < channels.size()) {
                    RegisterValue value;
                    bool success = channels[channel_id]->poll(value);
                    if (success) {
                        registers[pc->dst] = value;
                    } else {
                        registers[pc->dst] = nullptr;
                    }
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::ChannelClose: {
                uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
                if (channel_id < channels.size()) {
                    channels[channel_id]->close();
                    registers[pc->dst] = static_cast<int64_t>(1);
                } else {
                    registers[pc->dst] = static_cast<int64_t>(0);
                }
                break;
            }
            case LIR::LIR_Op::ChannelHasData: {
                uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
                if (channel_id < channels.size()) {
                    registers[pc->dst] = static_cast<bool>(channels[channel_id]->has_data());
                } else {
                    registers[pc->dst] = static_cast<bool>(false);
                }
                break;
            }
            case LIR::LIR_Op::PrintUint: {
                std::cout << to_uint(registers[pc->a]) << std::endl;
                break;
            }
            case LIR::LIR_Op::PrintFloat: {
                std::cout << to_float(registers[pc->a]) << std::endl;
                break;
            }
            case LIR::LIR_Op::PrintBool: {
                std::cout << (to_bool(registers[pc->a]) ? "true" : "false") << std::endl;
                break;
            }
            case LIR::LIR_Op::PrintString: {
                std::cout << to_string(registers[pc->a]) << std::endl;
                break;
            }
            case LIR::LIR_Op::ToString: {
                // Convert value to string using type information
                const auto& value = registers[pc->a];
                if (std::holds_alternative<FrameInstancePtr>(value) || std::holds_alternative<std::nullptr_t>(value)) {
                    registers[pc->dst] = to_string(value);
                } else if (pc->type_a == LIR::Type::Ptr) {
                    // Value is a pointer - call runtime function to handle collections
                    if (std::holds_alternative<int64_t>(value)) {
                        int64_t ptr_value = to_int(value);

                        // Defensive check: don't pass small integers as pointers to the runtime
                        if (ptr_value > 0 && ptr_value < 4096) {
                            registers[pc->dst] = std::to_string(ptr_value);
                        } else if (ptr_value == 0) {
                            registers[pc->dst] = "nil";
                        } else {
                            void* ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(ptr_value));
                            LmString result = lm_value_to_string(ptr);
                            registers[pc->dst] = std::string(result.data, result.len);
                            lm_string_free(result);
                        }
                    } else if (std::holds_alternative<uint64_t>(value)) {
                        uint64_t ptr_value = to_uint(value);
                        if (ptr_value > 0 && ptr_value < 4096) {
                            registers[pc->dst] = std::to_string(ptr_value);
                        } else {
                            void* ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(ptr_value));
                            LmString result = lm_value_to_string(ptr);
                            registers[pc->dst] = std::string(result.data, result.len);
                            lm_string_free(result);
                        }
                    } else {
                        registers[pc->dst] = to_string(value);
                    }
                } else {
                    // Value is a primitive - use standard conversion
                    registers[pc->dst] = to_string(value);
                }
                break;
            }
            case LIR::LIR_Op::STR_CONCAT: {
                registers[pc->dst] = to_string(registers[pc->a]) + to_string(registers[pc->b]);
                break;
            }
            case LIR::LIR_Op::STR_FORMAT: {
                std::string format = to_string(registers[pc->a]);
                std::string arg = to_string(registers[pc->b]);
                size_t pos = format.find("%s");
                if (pos != std::string::npos) {
                    format.replace(pos, 2, arg);
                } else {
                    format += arg;
                }
                registers[pc->dst] = format;
                break;
            }
            case LIR::LIR_Op::Cast: {
                registers[pc->dst] = registers[pc->a];
                break;
            }
            case LIR::LIR_Op::ListCreate: {
                // Create a new list using C runtime
                // Store the list pointer as int64_t handle
                void* list = lm_list_new();
                registers[pc->dst] = static_cast<int64_t>(reinterpret_cast<uintptr_t>(list));
                break;
            }
            case LIR::LIR_Op::ListAppend: {
                // Append value to list using C runtime
                auto& list_reg = registers[pc->a];
                auto& value_reg = registers[pc->b];
                
                if (std::holds_alternative<int64_t>(list_reg)) {
                    void* list = reinterpret_cast<void*>(static_cast<uintptr_t>(to_int(list_reg)));
                    if (list) {
                        // Box the value for C runtime
                        void* boxed_value = box_register_value(value_reg);
                        lm_list_append(static_cast<LmList*>(list), boxed_value);
                        registers[pc->dst] = static_cast<int64_t>(1); // Success
                    } else {
                        registers[pc->dst] = nullptr; // Invalid list pointer
                    }
                } else {
                    registers[pc->dst] = nullptr; // Invalid list register
                }
                break;
            }
            case LIR::LIR_Op::ListIndex: {
                // Get value from list using C runtime
                auto& list_reg = registers[pc->a];
                auto& index_reg = registers[pc->b];
                
                if (std::holds_alternative<int64_t>(list_reg) && is_numeric(index_reg)) {
                    void* list = reinterpret_cast<void*>(static_cast<uintptr_t>(to_int(list_reg)));
                    if (list) {
                        void* result = lm_list_get(static_cast<LmList*>(list), static_cast<uint64_t>(to_int(index_reg)));
                        if (result) {
                            // Check if result is a boxed value or a raw pointer (like a tuple)
                            LmBox* box = static_cast<LmBox*>(result);
                            if (box && box->type >= 0 && box->type <= 4) {
                                // It's a boxed value
                                registers[pc->dst] = unbox_register_value(result);
                            } else {
                                // It's a raw pointer (like a tuple), store as int64
                                registers[pc->dst] = static_cast<int64_t>(reinterpret_cast<uintptr_t>(result));
                            }
                        } else {
                            registers[pc->dst] = nullptr; // Index out of bounds
                        }
                    } else {
                        registers[pc->dst] = nullptr; // Invalid list pointer
                    }
                } else {
                    registers[pc->dst] = nullptr; // Invalid registers
                }
                break;
            }
            case LIR::LIR_Op::ListLen: {
                // Get list length using C runtime
                auto& list_reg = registers[pc->a];
                
                if (std::holds_alternative<int64_t>(list_reg)) {
                    void* list = reinterpret_cast<void*>(static_cast<uintptr_t>(to_int(list_reg)));
                    if (list) {
                        uint64_t len = lm_list_len(static_cast<LmList*>(list));
                        registers[pc->dst] = static_cast<int64_t>(len);
                    } else {
                        registers[pc->dst] = 0; // Invalid list pointer
                    }
                } else {
                    registers[pc->dst] = 0; // Invalid register
                }
                break;
            }
            case LIR::LIR_Op::DictCreate: {
                // Create a new dict using C runtime with boxed value hash/compare functions
                void* dict = lm_dict_new(hash_boxed_value, cmp_boxed_value);
                if (dict) {
                    registers[pc->dst] = static_cast<int64_t>(reinterpret_cast<uintptr_t>(dict));
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::DictSet: {
                // DictSet: dst=dict, a=key, b=value
                // Instruction format: DictSet dict_reg, key_reg, value_reg
                const RegisterValue& dict_val = registers[pc->dst];
                const RegisterValue& key_val = registers[pc->a];
                const RegisterValue& value_val = registers[pc->b];
                
                // Validate dict register contains a pointer
                if (!std::holds_alternative<int64_t>(dict_val)) {
                    registers[pc->dst] = nullptr;
                    break;
                }
                
                void* dict_ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(to_int(dict_val)));
                if (!dict_ptr) {
                    registers[pc->dst] = nullptr;
                    break;
                }
                
                // Box key and value for C runtime
                void* boxed_key = box_register_value(key_val);
                void* boxed_value = box_register_value(value_val);
                
                if (!boxed_key || !boxed_value) {
                    registers[pc->dst] = nullptr;
                    break;
                }
                
                // Set the key-value pair in the dict
                lm_dict_set(static_cast<LmDict*>(dict_ptr), boxed_key, boxed_value);
                
                // Return the dict register (for chaining)
                registers[pc->dst] = dict_val;
                break;
            }
            case LIR::LIR_Op::DictGet: {
                // DictGet: dst=result, a=dict, b=key
                // Instruction format: DictGet result_reg, dict_reg, key_reg
                const RegisterValue& dict_val = registers[pc->a];
                const RegisterValue& key_val = registers[pc->b];
                
                // Validate dict register contains a pointer
                if (!std::holds_alternative<int64_t>(dict_val)) {
                    registers[pc->dst] = nullptr;
                    break;
                }
                
                void* dict_ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(to_int(dict_val)));
                if (!dict_ptr) {
                    registers[pc->dst] = nullptr;
                    break;
                }
                
                // Box key for C runtime lookup
                void* boxed_key = box_register_value(key_val);
                if (!boxed_key) {
                    registers[pc->dst] = nullptr;
                    break;
                }
                
                // Get the value from the dict
                void* result = lm_dict_get(static_cast<LmDict*>(dict_ptr), boxed_key);
                if (result) {
                    registers[pc->dst] = unbox_register_value(result);
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::DictItems: {
                // DictItems: dst=result_list, a=dict
                // Instruction format: DictItems result_reg, dict_reg
                const RegisterValue& dict_val = registers[pc->a];
                
                // Validate dict register contains a pointer
                if (!std::holds_alternative<int64_t>(dict_val)) {
                    void* empty_list = lm_list_new();
                    registers[pc->dst] = static_cast<int64_t>(reinterpret_cast<uintptr_t>(empty_list));
                    break;
                }
                
                void* dict_ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(to_int(dict_val)));
                if (!dict_ptr) {
                    void* empty_list = lm_list_new();
                    registers[pc->dst] = static_cast<int64_t>(reinterpret_cast<uintptr_t>(empty_list));
                    break;
                }
                
                // Get all items from the dict
                uint64_t count = 0;
                void** items = lm_dict_items(static_cast<LmDict*>(dict_ptr), &count);
                
                // Create a list to hold the (key, value) tuples
                void* items_list = lm_list_new();
                if (!items_list) {
                    if (items) free(items);
                    registers[pc->dst] = nullptr;
                    break;
                }
                
                // Process each key-value pair
                for (uint64_t i = 0; i < count; i++) {
                    // Create a tuple for this (key, value) pair
                    void* tuple = lm_tuple_new(2);
                    if (!tuple) {
                        // Cleanup on error
                        if (items) free(items);
                        registers[pc->dst] = nullptr;
                        break;
                    }
                    
                    // Set key at index 0 (already boxed from dict)
                    lm_tuple_set(static_cast<LmTuple*>(tuple), 0, items[i * 2]);
                    
                    // Set value at index 1 (already boxed from dict)
                    lm_tuple_set(static_cast<LmTuple*>(tuple), 1, items[i * 2 + 1]);
                    
                    // Add tuple pointer directly to the items list
                    // Lists store void* pointers, so we can store the tuple pointer directly
                    lm_list_append(static_cast<LmList*>(items_list), tuple);
                }
                
                // Cleanup items array
                if (items) free(items);
                
                // Return the list of tuples
                registers[pc->dst] = static_cast<int64_t>(reinterpret_cast<uintptr_t>(items_list));
                break;
            }
            case LIR::LIR_Op::TupleCreate: {
                // Create a proper tuple using C runtime with size
                uint64_t size = static_cast<uint64_t>(pc->imm);
                void* tuple = lm_tuple_new(size);
                registers[pc->dst] = static_cast<int64_t>(reinterpret_cast<uintptr_t>(tuple));
                break;
            }
            case LIR::LIR_Op::TupleGet: {
                // Get value from tuple using C runtime
                auto& tuple_reg = registers[pc->a];
                auto& index_reg = registers[pc->b];
                
                if (std::holds_alternative<int64_t>(tuple_reg)) {
                    void* tuple = reinterpret_cast<void*>(static_cast<uintptr_t>(to_int(tuple_reg)));
                    if (tuple) {
                        uint64_t index = static_cast<uint64_t>(to_int(index_reg));
                        void* result = lm_tuple_get(static_cast<LmTuple*>(tuple), index);
                        if (result) {
                            registers[pc->dst] = unbox_register_value(result);
                        } else {
                            registers[pc->dst] = nullptr; // Index out of bounds
                        }
                    } else {
                        registers[pc->dst] = nullptr; // Invalid tuple pointer
                    }
                } else {
                    registers[pc->dst] = nullptr; // Invalid tuple register
                }
                break;
            }
            case LIR::LIR_Op::TupleSet: {
                // Set value in tuple using C runtime
                // Format: tuple_set tuple, index, value
                auto& tuple_reg = registers[pc->dst];
                auto& index_reg = registers[pc->a];
                auto& value_reg = registers[pc->b];
                
                if (std::holds_alternative<int64_t>(tuple_reg)) {
                    void* tuple = reinterpret_cast<void*>(static_cast<uintptr_t>(to_int(tuple_reg)));
                    if (tuple) {
                        uint64_t index = static_cast<uint64_t>(to_int(index_reg));
                        void* boxed_value = box_register_value(value_reg);
                        lm_tuple_set(static_cast<LmTuple*>(tuple), index, boxed_value);
                    }
                }
                break;
            }
            case LIR::LIR_Op::TaskContextAlloc: {
                uint64_t count = static_cast<uint64_t>(pc->a);
                uint64_t start_context_id = task_contexts.size();
                

                
                for (uint64_t i = 0; i < count; i++) {
                    auto task_ctx = std::make_unique<TaskContext>();
                    task_contexts.push_back(std::move(task_ctx));

                }
                
                registers[pc->dst] = static_cast<int64_t>(start_context_id);
                break;
            }
            case LIR::LIR_Op::TaskContextInit: {
                uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
                if (context_id < task_contexts.size()) {
                    TaskContext* ctx = task_contexts[context_id].get();
                    ctx->state = TaskState::INIT;
                    ctx->task_id = context_id;
                    registers[pc->dst] = static_cast<int64_t>(context_id);
                } else {
                    registers[pc->dst] = static_cast<int64_t>(0);
                }
                break;
            }
            case LIR::LIR_Op::TaskGetState: {
                uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
                if (context_id < scheduler->fibers.size()) {
                    registers[pc->dst] = static_cast<int64_t>(scheduler->fibers[context_id]->state);
                } else {
                    registers[pc->dst] = static_cast<int64_t>(TaskState::INIT);
                }
                break;
            }
            case LIR::LIR_Op::TaskSetState: {
                uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
                TaskState new_state = static_cast<TaskState>(to_int(registers[pc->b]));
                if (context_id < scheduler->fibers.size()) {
                    scheduler->fibers[context_id]->state = static_cast<FiberState>(new_state);
                    registers[pc->dst] = static_cast<int64_t>(1);
                } else {
                    registers[pc->dst] = static_cast<int64_t>(0);
                }
                break;
            }
            case LIR::LIR_Op::TaskSetField: {
                uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
                int field_index = static_cast<int>(to_int(registers[pc->b]));
                RegisterValue field_value = registers[pc->dst];

                if (pc->imm != 0) {
                    field_index = static_cast<int>(pc->imm);
                }


                // Check if context exists in scheduler first, then in task_contexts
                if (context_id < scheduler->fibers.size()) {
                    auto& fiber = scheduler->fibers[context_id];
                    if (fiber->task_context) {
                        fiber->task_context->fields[field_index] = field_value;

                        registers[pc->dst] = static_cast<int64_t>(1);
                    } else {

                        registers[pc->dst] = static_cast<int64_t>(0);
                    }
                } else if (context_id < task_contexts.size()) {
                    // Task context exists but not yet in scheduler
                    auto& ctx = task_contexts[context_id];
                    if (ctx) {
                        ctx->fields[field_index] = field_value;

                        registers[pc->dst] = static_cast<int64_t>(1);
                    } else {

                        registers[pc->dst] = static_cast<int64_t>(0);
                    }
                } else {

                    registers[pc->dst] = static_cast<int64_t>(0);
                }
                break;
            }
            case LIR::LIR_Op::TaskGetField: {
                uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
                int field_index = static_cast<int>(to_int(registers[pc->b]));
                if (context_id < scheduler->fibers.size()) {
                    auto it = scheduler->fibers[context_id]->task_context->fields.find(field_index);
                    if (it != scheduler->fibers[context_id]->task_context->fields.end()) {
                        registers[pc->dst] = it->second;
                    } else {
                        registers[pc->dst] = static_cast<int64_t>(0);
                    }
                } else {
                    registers[pc->dst] = static_cast<int64_t>(0);
                }
                break;
            }
            case LIR::LIR_Op::SchedulerInit: {
                scheduler = std::make_unique<Scheduler>();
                break;
            }
            case LIR::LIR_Op::SchedulerAddTask: {
                uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
                if (context_id < task_contexts.size()) {
                    TaskContext* ctx = task_contexts[context_id].get();
                    if (ctx) {
                        // Copy task context to scheduler
                        scheduler->add_fiber(std::make_unique<TaskContext>(*ctx));
                        registers[pc->dst] = static_cast<int64_t>(1);
                    } else {
                        registers[pc->dst] = static_cast<int64_t>(0);
                    }
                } else {
                    registers[pc->dst] = static_cast<int64_t>(0);
                }
                break;
            }
            case LIR::LIR_Op::SchedulerRun: {

                // Execute all running tasks (they should already be in scheduler via OP_SCHEDULER_ADD_TASK)
                // Keep running until all fibers are completed
                bool all_completed = false;
                while (!all_completed) {
                    all_completed = true;
                    
                    for (size_t i = 0; i < scheduler->fibers.size(); ++i) {
                        auto& fiber = scheduler->fibers[i];

                        if (fiber->state == FiberState::CREATED) {
                            fiber->state = FiberState::RUNNING;
                        }

                        if (fiber->state == FiberState::RUNNING) {
                            all_completed = false;

                            // Get task function name from task context field 4
                            auto func_name_it = fiber->task_context->fields.find(4);
                            if (func_name_it == fiber->task_context->fields.end()) {
                                std::cerr << "[ERROR] Task function name not found in task context" << std::endl;
                                std::cerr << "[DEBUG] Task context has " << fiber->task_context->fields.size() << " fields:" << std::endl;
                                for (const auto& field : fiber->task_context->fields) {
                                    std::cerr << "[DEBUG] Field " << field.first << " type: " << field.second.index() << std::endl;
                                }
                                fiber->state = FiberState::COMPLETED;
                                continue;
                            }

                            // Extract function name from register value
                            std::string task_func_name;
                            if (std::holds_alternative<std::string>(func_name_it->second)) {
                                task_func_name = this->to_string(func_name_it->second);

                            } else {
                                std::cerr << "[ERROR] Task function name is not a string, type index: " << func_name_it->second.index() << std::endl;
                                fiber->state = FiberState::COMPLETED;
                                continue;
                            }

                            // Get task function from registry
                            auto& func_registry = LIR::FunctionRegistry::getInstance();
                            LIR::LIR_Function* task_func = func_registry.getFunction(task_func_name);
                            if (!task_func) {
                                std::cerr << "[ERROR] Task function '" << task_func_name << "' not found in registry" << std::endl;
                                fiber->state = FiberState::COMPLETED;
                                continue;
                            }

                            // Save current register state
                            auto saved_registers = registers;

                            // Initialize a fresh register context for this task
                            registers.clear();
                            registers.resize(1024);
                            for (auto& reg : registers) {
                                reg = nullptr;
                            }

                            // Track if this is a channel worker
                            bool is_channel_worker = false;

                            // Set up task context parameters in fresh register space
                            if (fiber) {
                                // Set task ID from task context field 0
                                auto task_id_it = fiber->task_context->fields.find(0);
                                if (task_id_it != fiber->task_context->fields.end()) {
                                    registers[0] = task_id_it->second;
                                }

                                // Set loop variable value from task context field 1
                                auto loop_var_it = fiber->task_context->fields.find(1);
                                if (loop_var_it != fiber->task_context->fields.end()) {
                                    // Check if field 1 is a channel (for worker iteration)
                                    // If it's an int64, it should be a channel ID
                                    if (std::holds_alternative<int64_t>(loop_var_it->second)) {
                                        int64_t potential_channel_id = to_int(loop_var_it->second);
                                        
                                        // Check if this is a valid channel ID
                                        if (potential_channel_id >= 0 && potential_channel_id < static_cast<int64_t>(channels.size())) {
                                            // This is a channel - poll it for data
                                            auto& channel = channels[potential_channel_id];
                                            if (channel && channel->has_data()) {
                                                // Poll the channel for data
                                                RegisterValue data;
                                                if (channel->poll(data)) {
                                                    registers[1] = data;
                                                    is_channel_worker = true;
                                                } else {
                                                    // Channel is closed or empty
                                                    fiber->state = FiberState::COMPLETED;
                                                    registers = saved_registers;
                                                    current_function_ = nullptr;
                                                    continue;
                                                }
                                            } else {
                                                // Channel is empty or closed
                                                fiber->state = FiberState::COMPLETED;
                                                registers = saved_registers;
                                                current_function_ = nullptr;
                                                continue;
                                            }
                                        } else {
                                            // Not a channel, use as-is
                                            registers[1] = loop_var_it->second;
                                        }
                                    } else {
                                        // Not an int64, use as-is
                                        registers[1] = loop_var_it->second;
                                    }
                                }

                                // Set channel from task context field 2
                                auto channel_it = fiber->task_context->fields.find(2);
                                if (channel_it != fiber->task_context->fields.end()) {
                                    registers[2] = channel_it->second;
                                }
                            }

                            // Execute task function
                            current_function_ = task_func;
                            execute_instructions(*task_func, 0, task_func->instructions.size());
                            
                            // Restore register state and current function
                            registers = saved_registers;
                            current_function_ = nullptr;
                            
                            // Only mark as completed if not a channel worker
                            // Channel workers will be marked completed when channel is empty
                            if (!is_channel_worker) {
                                fiber->state = FiberState::COMPLETED;
                            }

                        }
                    }
                }
                
                registers[pc->dst] = static_cast<int64_t>(1);
                break;
            }
            case LIR::LIR_Op::SchedulerTick: {
                scheduler->tick();
                current_time++;
                registers[pc->dst] = static_cast<int64_t>(1);
                break;
            }
            case LIR::LIR_Op::GetTickCount: {
                registers[pc->dst] = static_cast<int64_t>(current_time);
                break;
            }
            case LIR::LIR_Op::DelayUntil: {
                uint64_t target_time = static_cast<uint64_t>(to_int(registers[pc->a]));
                registers[pc->dst] = static_cast<bool>(current_time >= target_time);
                break;
            }
            case LIR::LIR_Op::ParallelInit: {
                registers[pc->dst] = static_cast<int64_t>(1);
                break;
            }
            case LIR::LIR_Op::ParallelSync: {
                registers[pc->dst] = static_cast<int64_t>(1);
                break;
            }
            case LIR::LIR_Op::SharedCellAlloc: {
                static uint32_t next_cell_id = 1;
                uint32_t cell_id = next_cell_id++;
                
                shared_cells[cell_id] = std::make_unique<SharedCell>(cell_id, 0);
                registers[pc->dst] = static_cast<int64_t>(cell_id);
                break;
            }
            case LIR::LIR_Op::SharedCellLoad: {
                uint32_t cell_id = static_cast<uint32_t>(to_int(registers[pc->a]));
                
                if (shared_cells.find(cell_id) != shared_cells.end()) {
                    int64_t value = shared_cells[cell_id]->value.load();
                    registers[pc->dst] = value;
                } else {
                    registers[pc->dst] = static_cast<int64_t>(0);
                }
                break;
            }
            case LIR::LIR_Op::SharedCellStore: {
                uint32_t cell_id = static_cast<uint32_t>(to_int(registers[pc->a]));
                int64_t value = to_int(registers[pc->b]);
                
                if (shared_cells.find(cell_id) != shared_cells.end()) {
                    shared_cells[cell_id]->value.store(value);
                    registers[pc->dst] = value;
                } else {
                    registers[pc->dst] = static_cast<int64_t>(0);
                }
                break;
            }
            case LIR::LIR_Op::SharedCellAdd: {
                uint32_t cell_id = static_cast<uint32_t>(to_int(registers[pc->a]));
                int64_t value = to_int(registers[pc->b]);
                
                if (shared_cells.find(cell_id) != shared_cells.end()) {
                    int64_t old_value = shared_cells[cell_id]->value.fetch_add(value);
                    int64_t new_value = old_value + value;
                    registers[pc->dst] = new_value;
                } else {
                    std::cerr << "[ERROR] SharedCell ID " << cell_id << " not found" << std::endl;
                    registers[pc->dst] = static_cast<int64_t>(0);
                }
                break;
            }
            case LIR::LIR_Op::SharedCellSub: {
                uint32_t cell_id = static_cast<uint32_t>(to_int(registers[pc->a]));
                int64_t value = to_int(registers[pc->b]);
                
                if (shared_cells.find(cell_id) != shared_cells.end()) {
                    int64_t old_value = shared_cells[cell_id]->value.fetch_sub(value);
                    int64_t new_value = old_value - value;
                    registers[pc->dst] = new_value;
                } else {
                    std::cerr << "[ERROR] SharedCell ID " << cell_id << " not found" << std::endl;
                    registers[pc->dst] = static_cast<int64_t>(0);
                }
                break;
            }
            case LIR::LIR_Op::CallIndirect: {
                const RegisterValue& func_val = registers[pc->a];
                std::string func_name;
                RegisterValue env_val = nullptr;
                bool has_env = false;

                if (std::holds_alternative<std::string>(func_val)) {
                    func_name = std::get<std::string>(func_val);
                } else if (std::holds_alternative<int64_t>(func_val)) {
                    // Possible closure Tuple pointer
                    void* tuple_ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(to_int(func_val)));
                    if (tuple_ptr) {
                        void* name_val = lm_tuple_get(static_cast<LmTuple*>(tuple_ptr), 0);
                        if (name_val) {
                            RegisterValue unboxed_name = unbox_register_value(name_val);
                            if (std::holds_alternative<std::string>(unboxed_name)) {
                                func_name = std::get<std::string>(unboxed_name);
                                env_val = func_val; // The tuple itself is the environment
                                has_env = true;
                            }
                        }
                    }
                }

                if (func_name.empty()) {
                    registers[pc->dst] = nullptr;
                    break;
                }

                auto& func_manager = LIR::LIRFunctionManager::getInstance();
                auto func = func_manager.getFunction(func_name);

                if (func) {
                    auto saved_registers = registers;
                    const LIR::LIR_Function* saved_func = current_function_;
                    size_t param_count = func->getParameters().size();
                    std::vector<RegisterValue> args;
                    
                    // Pop arguments in correct order (they were pushed in order, so popping gives reverse)
                    size_t expected_stack_args = param_count;
                    if (has_env) {
                        if (expected_stack_args == 0) {
                            std::cerr << "VM Error: Invalid closure call target '" << func_name
                                      << "' with zero parameters" << std::endl;
                            registers[pc->dst] = nullptr;
                            break;
                        }
                        expected_stack_args -= 1;
                    }
                    for (size_t i = 0; i < expected_stack_args && !argument_stack.empty(); ++i) {
                        args.insert(args.begin(), argument_stack.back());
                        argument_stack.pop_back();
                    }
                    argument_stack.clear();

                    if (has_env) {
                        args.push_back(env_val);
                    }

                    // Reset registers for new call frame
                    registers.assign(registers.size(), nullptr);
                    for (size_t i = 0; i < args.size() && i < registers.size(); ++i) {
                        registers[i] = args[i];
                    }
                    
                    LIR::LIR_Function temp_wrapper(func->getName(), static_cast<uint32_t>(param_count));
                    temp_wrapper.instructions = func->getInstructions();
                    current_function_ = &temp_wrapper;

                    execute_instructions(temp_wrapper, 0, temp_wrapper.instructions.size());
                    
                    RegisterValue return_value = registers[0];
                    registers = saved_registers;
                    current_function_ = saved_func;
                    registers[pc->dst] = return_value;
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::Call: {
                // Handle both builtin and user function calls using new LIR format
                if (!pc->func_name.empty()) {
                    std::string func_name = pc->func_name;
                    const auto& arg_regs = pc->call_args;
                    // std::cout << "[VM DEBUG] Call: " << func_name << " dst=" << pc->dst << std::endl;
                    
                    // Then try user-defined functions FIRST to allow shadowing builtins
                    auto& func_manager = LIR::LIRFunctionManager::getInstance();
                    if (func_manager.hasFunction(func_name)) {
                        auto func = func_manager.getFunction(func_name);
                        
                        if (func) {
                            auto saved_registers = registers;
                            
                            // Use a temporary vector to avoid overwriting registers that are used as source for subsequent parameters
                            std::vector<RegisterValue> args;
                            for (size_t i = 0; i < arg_regs.size(); ++i) {
                                args.push_back(registers[arg_regs[i]]);
                            }

                            // Save current context
                            const LIR::LIR_Function* saved_func = current_function_;

                            // Set up parameters and clear other registers to prevent state leakage/corruption
                            size_t param_count = func->getParameters().size();
                            for (size_t i = 0; i < registers.size(); ++i) {
                                if (i < param_count) {
                                    registers[i] = (i < args.size()) ? args[i] : nullptr;
                                } else {
                                    registers[i] = nullptr;
                                }
                            }
                            
                            // Execute function
                            LIR::LIR_Function temp_wrapper(func->getName(), param_count);
                            temp_wrapper.instructions = func->getInstructions();
                            current_function_ = &temp_wrapper;

                            execute_instructions(temp_wrapper, 0, temp_wrapper.instructions.size());
                            
                            // Get return value from register 0 (standard return register)
                            RegisterValue return_value = registers[0];
                            
                            // Restore caller's context
                            registers = saved_registers;
                            current_function_ = saved_func;
                            
                            // Set return value in destination register
                            registers[pc->dst] = return_value;
                            
                            break;
                        }
                    }

                    // Then try builtin functions
                    if (LIR::BuiltinUtils::isBuiltinFunction(func_name)) {
                        std::vector<ValuePtr> args;
                        
                        for (size_t i = 0; i < arg_regs.size(); ++i) {
                            auto reg_value = registers[arg_regs[i]];
                            
                            ValuePtr arg_value;
                            if (std::holds_alternative<int64_t>(reg_value)) {
                                auto int_type = std::make_shared<::Type>(TypeTag::Int);
                                arg_value = std::make_shared<Value>(int_type, to_int(reg_value));
                            } else if (std::holds_alternative<double>(reg_value)) {
                                auto float_type = std::make_shared<::Type>(TypeTag::Float64);
                                arg_value = std::make_shared<Value>(float_type, to_float(reg_value));
                            } else if (std::holds_alternative<bool>(reg_value)) {
                                auto bool_type = std::make_shared<::Type>(TypeTag::Bool);
                                arg_value = std::make_shared<Value>(bool_type, to_bool(reg_value));
                            } else if (std::holds_alternative<std::string>(reg_value)) {
                                auto string_type = std::make_shared<::Type>(TypeTag::String);
                                arg_value = std::make_shared<Value>(string_type, this->to_string(reg_value));
                            } else {
                                auto nil_type = std::make_shared<::Type>(TypeTag::Nil);
                                arg_value = std::make_shared<Value>(nil_type);
                            }
                            args.push_back(arg_value);
                        }
                        
                        try {
                            ValuePtr result = LIR::BuiltinUtils::callBuiltinFunction(func_name, args);
                            
                            if (result && result->type) {
                                switch (result->type->tag) {
                                    case TypeTag::Int:
                                    case TypeTag::Int64:
                                        registers[pc->dst] = result->as<int64_t>();
                                        break;
                                    case TypeTag::Float32:
                                    case TypeTag::Float64:
                                        registers[pc->dst] = result->as<double>();
                                        break;
                                    case TypeTag::Bool:
                                        registers[pc->dst] = result->as<bool>();
                                        break;
                                    case TypeTag::String:
                                        registers[pc->dst] = result->as<std::string>();
                                        break;
                                    default:
                                        registers[pc->dst] = nullptr;
                                        break;
                                }
                            } else {
                                registers[pc->dst] = nullptr;
                            }
                        } catch (const std::exception& e) {
                            std::cerr << "Error calling builtin function " << func_name << ": " << e.what() << std::endl;
                            registers[pc->dst] = nullptr;
                        }
                        
                        break;
                    }
                    
                    // Function not found
                    std::cerr << "Error: Function '" << func_name << "' not found" << std::endl;
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::Neg: {
                const RegisterValue* temp_a = &registers[pc->a];
                if (is_numeric(*temp_a)) {
                    registers[pc->dst] = -to_float(*temp_a);
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::JumpIf: {
                if (to_bool(registers[pc->a])) {
                    pc = function.instructions.data() + (pc->imm);
                    if (pc >= end) return;
                    continue; // Skip pc++ at end of loop
                }
                break;
            }
            case LIR::LIR_Op::Label:
            case LIR::LIR_Op::FuncDef:
                break;
            case LIR::LIR_Op::Param: {
                argument_stack.push_back(registers[pc->a]);
                break;
            }
            case LIR::LIR_Op::ConstructError: {
                std::string errorType = "DefaultError";
                std::string errorMessage = "Operation failed";
                
                if (!pc->comment.empty() && pc->comment.find("ERROR_INFO:") == 0) {
                    std::string info = pc->comment.substr(11);
                    size_t colon_pos = info.find(':');
                    if (colon_pos != std::string::npos) {
                        errorType = info.substr(0, colon_pos);
                        errorMessage = info.substr(colon_pos + 1);
                    }
                }
                
                static int64_t next_error_id = -1000000;
                int64_t error_id = next_error_id--;
                
                ErrorInfo error_info;
                error_info.errorType = errorType;
                error_info.message = errorMessage;
                error_info.isError = true;
                error_table[error_id] = error_info;
                
                registers[pc->dst] = error_id;
                break;
            }
            case LIR::LIR_Op::ConstructOk: {
                registers[pc->dst] = registers[pc->a];
                break;
            }
            case LIR::LIR_Op::IsError: {
                bool is_error = isErrorValue(pc->a);
                registers[pc->dst] = is_error;
                break;
            }
            case LIR::LIR_Op::Unwrap: {
                auto& value = registers[pc->a];
                
                if (isErrorValue(pc->a)) {
                    std::cerr << "Runtime Error: Attempted to unwrap an error value" << std::endl;
                    registers[pc->dst] = nullptr;
                } else if (std::holds_alternative<FrameInstancePtr>(value)) {
                    // Defensive union-layout validation: if the runtime value is represented
                    // as an internal enum/union frame, ensure tag/payload layout is intact.
                    auto frame = std::get<FrameInstancePtr>(value);
                    if (!frame || frame->frame_type != INTERNAL_ENUM_FRAME_TYPE || frame->fields.size() < 2) {
                        std::cerr << "Runtime Error: Invalid union layout during unwrap (expected enum frame with tag+payload)" << std::endl;
                        registers[pc->dst] = nullptr;
                    } else {
                        const auto& tag_reg = frame->getField(0);
                        if (!(std::holds_alternative<int64_t>(tag_reg) || std::holds_alternative<uint64_t>(tag_reg))) {
                            std::cerr << "Runtime Error: Invalid union tag type during unwrap" << std::endl;
                            registers[pc->dst] = nullptr;
                        } else {
                            registers[pc->dst] = frame->getField(1);
                        }
                    }
                } else {
                    registers[pc->dst] = value;
                }
                break;
            }
            case LIR::LIR_Op::UnwrapOr: {
                if (std::holds_alternative<std::nullptr_t>(registers[pc->a])) {
                    registers[pc->dst] = registers[pc->b];
                } else {
                    registers[pc->dst] = registers[pc->a];
                }
                break;
            }
            case LIR::LIR_Op::MakeEnum: {
                auto enum_value = std::make_shared<FrameInstance>(INTERNAL_ENUM_FRAME_TYPE, 2);
                enum_value->setField(0, static_cast<int64_t>(pc->imm));
                enum_value->setField(1, (pc->a != 0) ? registers[pc->a] : RegisterValue(nullptr));
                registers[pc->dst] = enum_value;
                break;
            }
            case LIR::LIR_Op::GetTag: {
                if (std::holds_alternative<FrameInstancePtr>(registers[pc->a])) {
                    auto enum_value = std::get<FrameInstancePtr>(registers[pc->a]);
                    if (enum_value && enum_value->frame_type == INTERNAL_ENUM_FRAME_TYPE && enum_value->fields.size() >= 2) {
                        const auto& tag = enum_value->getField(0);
                        if (!(std::holds_alternative<int64_t>(tag) || std::holds_alternative<uint64_t>(tag))) {
                            std::cerr << "Runtime Error: Invalid union tag representation in GetTag" << std::endl;
                            registers[pc->dst] = int64_t(0);
                        } else {
                            registers[pc->dst] = to_int(tag);
                        }
                    } else {
                        std::cerr << "Runtime Error: Invalid union layout in GetTag" << std::endl;
                        registers[pc->dst] = int64_t(0);
                    }
                } else {
                    registers[pc->dst] = int64_t(0);
                }
                break;
            }
            case LIR::LIR_Op::GetPayload: {
                if (std::holds_alternative<FrameInstancePtr>(registers[pc->a])) {
                    auto enum_value = std::get<FrameInstancePtr>(registers[pc->a]);
                    if (enum_value && enum_value->frame_type == INTERNAL_ENUM_FRAME_TYPE && enum_value->fields.size() >= 2) {
                        const auto& tag = enum_value->getField(0);
                        if (!(std::holds_alternative<int64_t>(tag) || std::holds_alternative<uint64_t>(tag))) {
                            std::cerr << "Runtime Error: Invalid union tag representation in GetPayload" << std::endl;
                            registers[pc->dst] = nullptr;
                        } else {
                            registers[pc->dst] = enum_value->getField(1);
                        }
                    } else {
                        std::cerr << "Runtime Error: Invalid union layout in GetPayload" << std::endl;
                        registers[pc->dst] = nullptr;
                    }
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::AtomicLoad: {
                registers[pc->dst] = default_atomic.load();
                break;
            }
            case LIR::LIR_Op::AtomicStore: {
                int64_t value = to_int(registers[pc->a]);
                default_atomic.store(value);
                registers[pc->dst] = static_cast<int64_t>(1);
                break;
            }
            case LIR::LIR_Op::AtomicFetchAdd: {
                int64_t addend = to_int(registers[pc->b]);
                int64_t old_value = default_atomic.fetch_add(addend);
                registers[pc->dst] = old_value;
                break;
            }
            case LIR::LIR_Op::LoadGlobal: {
                if (globals_.count(pc->func_name)) {
                    registers[pc->dst] = globals_[pc->func_name];
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::StoreGlobal: {
                globals_[pc->func_name] = registers[pc->a];
                break;
            }
            case LIR::LIR_Op::Await:
            case LIR::LIR_Op::AsyncCall:
            case LIR::LIR_Op::ImportModule:
            case LIR::LIR_Op::ExportSymbol:
            case LIR::LIR_Op::BeginModule:
            case LIR::LIR_Op::EndModule: {
                // Placeholder implementations
                break;
            }
            case LIR::LIR_Op::NewFrame: {
                // Allocate and initialize a new frame instance
                // dst = frame register, imm = frame size (number of fields)
                auto frame = std::make_shared<FrameInstance>(pc->func_name, pc->imm);
                registers[pc->dst] = frame;
                break;
            }
            case LIR::LIR_Op::FrameGetField: {
                // Load field from frame instance
                // dst = destination register, a = frame register, b = field offset
                // std::cout << "[VM DEBUG] FrameGetField: frame_reg=" << pc->a << " offset=" << pc->b << " dst=" << pc->dst << std::endl;
                if (std::holds_alternative<FrameInstancePtr>(registers[pc->a])) {
                    auto frame = std::get<std::shared_ptr<struct FrameInstance>>(registers[pc->a]);
                    if (frame && pc->b < frame->fields.size()) {
                        registers[pc->dst] = frame->fields[pc->b];
                    } else {
                        registers[pc->dst] = nullptr;
                    }
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::FrameSetField: {
                // Store field to frame instance
                // dst = frame register, a = field offset, b = value register
                // std::cout << "[VM DEBUG] FrameSetField: frame_reg=" << pc->dst << " offset=" << pc->a << " val_reg=" << pc->b << std::endl;
                if (std::holds_alternative<FrameInstancePtr>(registers[pc->dst])) {
                    auto frame = std::get<std::shared_ptr<struct FrameInstance>>(registers[pc->dst]);
                    if (frame) {
                        frame->setField(pc->a, registers[pc->b]);
                    }
                } else {
                    // Error: not a frame instance
                }
                break;
            }
            case LIR::LIR_Op::FrameCallMethod: {
                // Call frame method (static dispatch)
                // This is a placeholder - actual method calls would be handled by Call instruction
                // with the frame as the first argument
                break;
            }
            case LIR::LIR_Op::FrameCallInit: {
                // Call frame init() method
                // dst = frame register
                // For now, this is a placeholder - actual init calls would be handled by Call instruction
                break;
            }
            case LIR::LIR_Op::FrameCallDeinit: {
                // Call frame deinit() method
                // dst = frame register
                if (pc->dst < registers.size() && std::holds_alternative<FrameInstancePtr>(registers[pc->dst])) {
                    auto frame = std::get<std::shared_ptr<struct FrameInstance>>(registers[pc->dst]);
                    if (frame) {
                        std::string deinit_name = frame->frame_type + ".deinit";
                        auto& func_manager = LIR::LIRFunctionManager::getInstance();
                        if (func_manager.hasFunction(deinit_name)) {
                            auto func = func_manager.getFunction(deinit_name);
                            if (func) {
                                // Save current context
                                auto saved_registers = registers;
                                const LIR::LIR_Function* saved_func = current_function_;

                                // Prepare fresh register set for deinit call to prevent corruption
                                registers.assign(registers.size(), nullptr);
                                registers[0] = frame; // 'this'

                                // Create a temporary LIR_Function for execution
                                LIR::LIR_Function deinit_wrapper(func->getName(), 1);
                                deinit_wrapper.instructions = func->getInstructions();
                                current_function_ = &deinit_wrapper;

                                // Execute deinit instructions
                                execute_instructions(deinit_wrapper, 0, deinit_wrapper.instructions.size());

                                // Restore caller context
                                registers = saved_registers;
                                current_function_ = saved_func;
                            }
                        }
                    }
                }
                break;
            }
            default: {
                std::cerr << "Error: Unknown LIR operation: " << static_cast<int>(pc->op) << std::endl;
                return;
            }
        }
        
        pc++; // Move to next instruction
    }
}

// Frame management method implementations
FrameInstancePtr RegisterVM::createFrameInstance(const std::string& frame_type) {
    auto frame = std::make_shared<FrameInstance>(frame_type);
    return frame;
}

void RegisterVM::setFrameField(FrameInstancePtr frame, size_t index, const RegisterValue& value) {
    if (!frame) {
        throw std::runtime_error("Cannot set field on null frame");
    }
    frame->setField(index, value);
}

RegisterValue RegisterVM::getFrameField(FrameInstancePtr frame, size_t index) const {
    if (!frame) {
        throw std::runtime_error("Cannot get field from null frame");
    }
    return frame->getField(index);
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM

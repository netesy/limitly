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

// Boxing/Unboxing functions for C runtime integration
void* box_register_value(const RegisterValue& value) {
    // Use the runtime boxing functions
    if (std::holds_alternative<int64_t>(value)) {
        return lm_box_int(std::get<int64_t>(value));
    } else if (std::holds_alternative<double>(value)) {
        return lm_box_float(std::get<double>(value));
    } else if (std::holds_alternative<bool>(value)) {
        return lm_box_bool(std::get<bool>(value) ? 1 : 0);
    } else if (std::holds_alternative<std::string>(value)) {
        return lm_box_string(std::get<std::string>(value).c_str());
    } else if (std::holds_alternative<uint64_t>(value)) {
        return lm_box_int(static_cast<int64_t>(std::get<uint64_t>(value)));
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
    
    // Use the runtime unboxing functions
    LmBox* box = static_cast<LmBox*>(boxed_value);
    if (!box) {
        return nullptr;
    }
    
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
    } else {
        return 0;
    }
}

uint64_t to_uint(const RegisterValue& value) {
    if (std::holds_alternative<int64_t>(value)) {
        return static_cast<uint64_t>(std::get<int64_t>(value));
    } else if (std::holds_alternative<double>(value)) {
        return static_cast<uint64_t>(std::get<double>(value));
    } else if (std::holds_alternative<uint64_t>(value)) {
        return std::get<uint64_t>(value);
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? 1 : 0;
    } else {
        return 0;
    }
}

double to_float(const RegisterValue& value) {
    if (std::holds_alternative<int64_t>(value)) {
        return static_cast<double>(std::get<int64_t>(value));
    } else if (std::holds_alternative<double>(value)) {
        return std::get<double>(value);
    } else if (std::holds_alternative<uint64_t>(value)) {
        return static_cast<double>(std::get<uint64_t>(value));
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? 1.0 : 0.0;
    } else {
        return 0.0;
    }
}

bool to_bool(const RegisterValue& value) {
    if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value);
    } else if (std::holds_alternative<int64_t>(value)) {
        return std::get<int64_t>(value) != 0;
    } else if (std::holds_alternative<double>(value)) {
        return std::get<double>(value) != 0.0;
    } else if (std::holds_alternative<std::string>(value)) {
        return !std::get<std::string>(value).empty();
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
        task_func_name = std::get<std::string>(func_name_it->second);
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
    if (std::holds_alternative<std::string>(value)) {
        return std::get<std::string>(value);
    } else if (std::holds_alternative<int64_t>(value)) {
        int64_t int_val = std::get<int64_t>(value);
        
        // Use the runtime function to convert any value to string
        // This handles primitives and collections uniformly
        void* ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(int_val));
        LmString result = lm_value_to_string(ptr);
        std::string str_result(result.data, result.len);
        lm_string_free(result);
        return str_result;
    } else if (std::holds_alternative<double>(value)) {
        return std::to_string(std::get<double>(value));
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? "true" : "false";
    } else {
        return "nil";
    }
}

ValuePtr RegisterVM::createErrorValue(const std::string& errorType, const std::string& message) {
    auto nil_type = std::make_shared<::Type>(TypeTag::Nil);
    return std::make_shared<Value>(nil_type, "Error: " + errorType + ": " + message);
}

ValuePtr RegisterVM::createSuccessValue(const RegisterValue& value) {
    if (std::holds_alternative<std::string>(value)) {
        auto string_type = std::make_shared<::Type>(TypeTag::String);
        return std::make_shared<Value>(string_type, std::get<std::string>(value));
    } else if (std::holds_alternative<int64_t>(value)) {
        auto int_type = std::make_shared<::Type>(TypeTag::Int64);
        return std::make_shared<Value>(int_type, std::to_string(std::get<int64_t>(value)));
    } else if (std::holds_alternative<double>(value)) {
        auto float_type = std::make_shared<::Type>(TypeTag::Float64);
        return std::make_shared<Value>(float_type, std::to_string(std::get<double>(value)));
    } else if (std::holds_alternative<bool>(value)) {
        auto bool_type = std::make_shared<::Type>(TypeTag::Bool);
        return std::make_shared<Value>(bool_type, std::get<bool>(value) ? "true" : "false");
    } else {
        auto nil_type = std::make_shared<::Type>(TypeTag::Nil);
        return std::make_shared<Value>(nil_type, "nil");
    }
}

bool RegisterVM::isErrorValue(LIR::Reg reg) const {
    auto& value = registers[reg];
    if (std::holds_alternative<int64_t>(value)) {
        int64_t int_val = std::get<int64_t>(value);
        return int_val <= -1000000; // Error IDs are negative numbers starting from -1000000
    }
    return false;
}

RegisterVM::RegisterVM() 
    : memoryRegion(memoryManager), 
      type_system(std::make_unique<TypeSystem>(memoryManager, memoryRegion)) {
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
                        registers[pc->dst] = std::string(static_cast<const char*>(cv->data.c_str()));
                    } else {
                        registers[pc->dst] = nullptr;
                    }
                }
                break;
            }
            case LIR::LIR_Op::Add: {
                const RegisterValue* temp_a = &registers[pc->a];
                const RegisterValue* temp_b = &registers[pc->b];
                if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
                    TypePtr result_type = (pc->result_type == LIR::Type::F64) ? 
                                          type_system->FLOAT64_TYPE : type_system->INT64_TYPE;
                    
                    bool a_is_float = std::holds_alternative<double>(*temp_a);
                    bool b_is_float = std::holds_alternative<double>(*temp_b);
                    
                    if (result_type->tag == TypeTag::Float32 || result_type->tag == TypeTag::Float64 || a_is_float || b_is_float) {
                        registers[pc->dst] = to_float(*temp_a) + to_float(*temp_b);
                    } else {
                        int64_t left = to_int(*temp_a);
                        int64_t right = to_int(*temp_b);
                        int64_t int_result = left + right;
                        registers[pc->dst] = int_result;
                    }
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::Sub: {
                const RegisterValue* temp_a = &registers[pc->a];
                const RegisterValue* temp_b = &registers[pc->b];
                if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
                    TypePtr result_type = (pc->result_type == LIR::Type::F64) ? 
                                          type_system->FLOAT64_TYPE : type_system->INT64_TYPE;
                    
                    bool a_is_float = std::holds_alternative<double>(*temp_a);
                    bool b_is_float = std::holds_alternative<double>(*temp_b);
                    
                    if (result_type->tag == TypeTag::Float32 || result_type->tag == TypeTag::Float64 || a_is_float || b_is_float) {
                        registers[pc->dst] = to_float(*temp_a) - to_float(*temp_b);
                    } else {
                        int64_t int_result = to_int(*temp_a) - to_int(*temp_b);
                        registers[pc->dst] = int_result;
                    }
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::Mul: {
                const RegisterValue* temp_a = &registers[pc->a];
                const RegisterValue* temp_b = &registers[pc->b];
                if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
                    TypePtr result_type = (pc->result_type == LIR::Type::F64) ? 
                                          type_system->FLOAT64_TYPE : type_system->INT64_TYPE;
                    
                    bool a_is_float = std::holds_alternative<double>(*temp_a);
                    bool b_is_float = std::holds_alternative<double>(*temp_b);
                    
                    if (result_type->tag == TypeTag::Float32 || result_type->tag == TypeTag::Float64 || a_is_float || b_is_float) {
                        registers[pc->dst] = to_float(*temp_a) * to_float(*temp_b);
                    } else {
                        int64_t int_result = to_int(*temp_a) * to_int(*temp_b);
                        registers[pc->dst] = int_result;
                    }
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::Div: {
                const RegisterValue* temp_a = &registers[pc->a];
                const RegisterValue* temp_b = &registers[pc->b];
                if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
                    TypePtr result_type = (pc->result_type == LIR::Type::F64) ? 
                                          type_system->FLOAT64_TYPE : type_system->INT64_TYPE;
                    
                    bool a_is_float = std::holds_alternative<double>(*temp_a);
                    bool b_is_float = std::holds_alternative<double>(*temp_b);
                    
                    if (result_type->tag == TypeTag::Float32 || result_type->tag == TypeTag::Float64 || a_is_float || b_is_float) {
                        double divisor = to_float(*temp_b);
                        if (divisor != 0.0) {
                            registers[pc->dst] = to_float(*temp_a) / divisor;
                        } else {
                            registers[pc->dst] = nullptr; // Division by zero
                        }
                    } else {
                        int64_t divisor = to_int(*temp_b);
                        if (divisor != 0) {
                            int64_t int_result = to_int(*temp_a) / divisor;
                            registers[pc->dst] = int_result;
                        } else {
                            registers[pc->dst] = nullptr; // Division by zero
                        }
                    }
                } else {
                    registers[pc->dst] = nullptr;
                }
                break;
            }
            case LIR::LIR_Op::Mod: {
                const RegisterValue* temp_a = &registers[pc->a];
                const RegisterValue* temp_b = &registers[pc->b];
                if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
                    int64_t divisor = to_int(*temp_b);
                    if (divisor != 0) {
                        int64_t int_result = to_int(*temp_a) % divisor;
                        registers[pc->dst] = int_result;
                    } else {
                        registers[pc->dst] = nullptr; // Modulo by zero
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
                if (pc->dst != 0) {
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
                // If type_a is Ptr, the value is a pointer to a collection
                if (pc->type_a == LIR::Type::Ptr) {
                    // Value is a pointer - call runtime function to handle collections
                    int64_t ptr_value = std::get<int64_t>(registers[pc->a]);
                    void* ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(ptr_value));
                    LmString result = lm_value_to_string(ptr);
                    registers[pc->dst] = std::string(result.data, result.len);
                    lm_string_free(result);
                } else {
                    // Value is a primitive - use standard conversion
                    registers[pc->dst] = to_string(registers[pc->a]);
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
                    void* list = reinterpret_cast<void*>(static_cast<uintptr_t>(std::get<int64_t>(list_reg)));
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
                    void* list = reinterpret_cast<void*>(static_cast<uintptr_t>(std::get<int64_t>(list_reg)));
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
                    void* list = reinterpret_cast<void*>(static_cast<uintptr_t>(std::get<int64_t>(list_reg)));
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
                
                void* dict_ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(std::get<int64_t>(dict_val)));
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
                
                void* dict_ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(std::get<int64_t>(dict_val)));
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
                
                void* dict_ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(std::get<int64_t>(dict_val)));
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
                uint64_t size = static_cast<uint64_t>(pc->b);
                void* tuple = lm_tuple_new(size);
                registers[pc->dst] = static_cast<int64_t>(reinterpret_cast<uintptr_t>(tuple));
                break;
            }
            case LIR::LIR_Op::TupleGet: {
                // Get value from tuple using C runtime
                auto& tuple_reg = registers[pc->a];
                auto& index_reg = registers[pc->b];
                
                if (std::holds_alternative<int64_t>(tuple_reg)) {
                    void* tuple = reinterpret_cast<void*>(static_cast<uintptr_t>(std::get<int64_t>(tuple_reg)));
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
                    void* tuple = reinterpret_cast<void*>(static_cast<uintptr_t>(std::get<int64_t>(tuple_reg)));
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
                                task_func_name = std::get<std::string>(func_name_it->second);

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
                                        int64_t potential_channel_id = std::get<int64_t>(loop_var_it->second);
                                        
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
            case LIR::LIR_Op::Call: {
                // Handle both builtin and user function calls using new LIR format
                if (!pc->func_name.empty()) {
                    std::string func_name = pc->func_name;
                    const auto& arg_regs = pc->call_args;
                    
                    // First try builtin functions
                    if (LIR::BuiltinUtils::isBuiltinFunction(func_name)) {
                        std::vector<ValuePtr> args;
                        
                        for (size_t i = 0; i < arg_regs.size(); ++i) {
                            auto reg_value = registers[arg_regs[i]];
                            
                            ValuePtr arg_value;
                            if (std::holds_alternative<int64_t>(reg_value)) {
                                auto int_type = std::make_shared<::Type>(TypeTag::Int);
                                arg_value = std::make_shared<Value>(int_type, std::get<int64_t>(reg_value));
                            } else if (std::holds_alternative<double>(reg_value)) {
                                auto float_type = std::make_shared<::Type>(TypeTag::Float64);
                                arg_value = std::make_shared<Value>(float_type, std::get<double>(reg_value));
                            } else if (std::holds_alternative<bool>(reg_value)) {
                                auto bool_type = std::make_shared<::Type>(TypeTag::Bool);
                                arg_value = std::make_shared<Value>(bool_type, std::get<bool>(reg_value));
                            } else if (std::holds_alternative<std::string>(reg_value)) {
                                auto string_type = std::make_shared<::Type>(TypeTag::String);
                                arg_value = std::make_shared<Value>(string_type, std::get<std::string>(reg_value));
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
                    
                    // Then try user-defined functions
                    auto& func_manager = LIR::LIRFunctionManager::getInstance();
                    if (func_manager.hasFunction(func_name)) {
                        auto func = func_manager.getFunction(func_name);
                        
                        if (func) {
                            auto saved_registers = registers;
                            
                            // Set up parameters (copy arguments to parameter registers r0, r1, r2, ...)
                            for (size_t i = 0; i < func->getParameters().size(); ++i) {
                                if (i < arg_regs.size()) {
                                    registers[i] = registers[arg_regs[i]];
                                } else {
                                    registers[i] = nullptr;
                                }
                            }
                            
                            // Execute function directly without resetting registers
                            LIR::LIR_Function temp_wrapper(func->getName(), func->getParameters().size());
                            temp_wrapper.instructions = func->getInstructions();
                            execute_instructions(temp_wrapper, 0, func->getInstructions().size());
                            
                            // Get return value from register 0 (standard return register)
                            RegisterValue return_value = registers[0];
                            
                            // Restore caller's registers
                            registers = saved_registers;
                            
                            // Set return value in destination register
                            registers[pc->dst] = return_value;
                            
                            break;
                        }
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
            case LIR::LIR_Op::Param:
            case LIR::LIR_Op::Ret: {
                // These are handled elsewhere or are no-ops in this context
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
            case LIR::LIR_Op::Await:
            case LIR::LIR_Op::AsyncCall:
            case LIR::LIR_Op::ImportModule:
            case LIR::LIR_Op::ExportSymbol:
            case LIR::LIR_Op::BeginModule:
            case LIR::LIR_Op::EndModule: {
                // Placeholder implementations
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

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM

#include "../register.hh"
#include "../../../lir/function_registry.hh"
#include "../../../lir/builtin_functions.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_value.h"
#include "../../../runtime/runtime_tuple.h"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

void RegisterVM::execute_calls(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::Call: {
            auto& func_manager = LIR::LIRFunctionManager::getInstance();
            if (func_manager.hasFunction(pc->func_name)) {
                auto func = func_manager.getFunction(pc->func_name);
                std::vector<RegisterValue> arg_vals;
                for (auto arg_reg : pc->call_args) arg_vals.push_back(registers[arg_reg]);

                auto saved_registers = registers;
                const LIR::LIR_Function* saved_func = current_function_;

                registers.assign(registers.size(), VAL_NIL);
                for (size_t i = 0; i < arg_vals.size() && i < registers.size(); ++i) {
                    registers[i] = arg_vals[i];
                }

                LIR::LIR_Function temp_wrapper(func->getName(), static_cast<uint32_t>(arg_vals.size()));
                temp_wrapper.instructions = func->getInstructions();
                current_function_ = &temp_wrapper;

                execute_instructions(temp_wrapper, 0, temp_wrapper.instructions.size());

                RegisterValue return_value = registers[0];

                registers = saved_registers;
                current_function_ = saved_func;
                registers[pc->dst] = return_value;
            } else if (pc->func_name == "assert") {
                bool condition = to_bool(registers[pc->call_args[0]]);
                if (!condition) {
                    std::string msg = "Assertion failed";
                    if (pc->call_args.size() > 1) msg = to_string(registers[pc->call_args[1]]);
                    std::cerr << msg << std::endl;
                }
            }
            break;
        }
        case LIR::LIR_Op::CallIndirect: {
            RegisterValue func_obj = registers[pc->a];
            std::string func_name = "";
            RegisterValue closure_env = VAL_NIL;
            
            if (IS_PTR(func_obj)) {
                ObjHeader* h = (ObjHeader*)UNBOX_PTR(func_obj);
                if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                    func_name = (char*)((LmBox*)h)->value.as_ptr;
                } else if (h->type_id == TYPE_TUPLE) {
                    closure_env = func_obj;
                    LmValue first_elem = lm_tuple_get((LmTuple*)h, 0);
                    if (IS_PTR(first_elem)) {
                        ObjHeader* fh = (ObjHeader*)UNBOX_PTR(first_elem);
                        if (fh->type_id == TYPE_BOX && ((LmBox*)fh)->type == LM_BOX_STRING) {
                            func_name = (char*)((LmBox*)fh)->value.as_ptr;
                        }
                    }
                }
            }
            
            if (!func_name.empty()) {
                auto& func_manager = LIR::LIRFunctionManager::getInstance();
                if (func_manager.hasFunction(func_name)) {
                    auto func = func_manager.getFunction(func_name);
                    std::vector<RegisterValue> arg_vals;
                    size_t expected_params = func->getParameters().size();

                    if (pc->call_args.empty()) {
                        size_t num_given_args = expected_params;
                        bool is_closure_call = false;
                        if (closure_env != VAL_NIL && expected_params > 0) {
                            num_given_args = expected_params - 1;
                            is_closure_call = true;
                        }

                        if (argument_stack.size() >= num_given_args) {
                            for (size_t i = 0; i < num_given_args; ++i) {
                                arg_vals.push_back(argument_stack[argument_stack.size() - num_given_args + i]);
                            }
                            argument_stack.resize(argument_stack.size() - num_given_args);
                        }

                        if (is_closure_call) {
                            arg_vals.push_back(closure_env);
                        }
                    } else {
                        for (auto arg_reg : pc->call_args) {
                            arg_vals.push_back(registers[arg_reg]);
                        }
                        if (closure_env != VAL_NIL && arg_vals.size() < expected_params) {
                            arg_vals.push_back(closure_env);
                        }
                    }

                    auto saved_registers = registers;
                    const LIR::LIR_Function* saved_func = current_function_;

                    registers.assign(registers.size(), VAL_NIL);
                    for (size_t i = 0; i < arg_vals.size() && i < registers.size(); ++i) {
                        registers[i] = arg_vals[i];
                    }

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

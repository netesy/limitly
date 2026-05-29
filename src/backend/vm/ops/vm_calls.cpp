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
                    throw std::runtime_error("Assertion failed: " + msg);
                }
            }
            break;
        }
        case LIR::LIR_Op::CallIndirect: {
            // Register a contains the function object (which currently is just the function pointer/name in our simplified model)
            RegisterValue func_obj = registers[pc->a];
            std::string func_name = "";
            
            std::vector<RegisterValue> closure_extra_args;
            if (IS_PTR(func_obj)) {
                ObjHeader* h = (ObjHeader*)UNBOX_PTR(func_obj);
                if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                    func_name = (char*)((LmBox*)h)->value.as_ptr;
                } else if (h->type_id == TYPE_TUPLE) {
                    LmTuple* closure_tuple = (LmTuple*)h;
                    RegisterValue name_value = lm_tuple_get(closure_tuple, 0);
                    if (IS_PTR(name_value)) {
                        ObjHeader* name_header = (ObjHeader*)UNBOX_PTR(name_value);
                        if (name_header->type_id == TYPE_BOX && ((LmBox*)name_header)->type == LM_BOX_STRING) {
                            func_name = (char*)((LmBox*)name_header)->value.as_ptr;
                            closure_extra_args.push_back(func_obj);
                        }
                    }
                }
            }
            
            if (!func_name.empty()) {
                auto& func_manager = LIR::LIRFunctionManager::getInstance();
                if (func_manager.hasFunction(func_name)) {
                    auto func = func_manager.getFunction(func_name);
                    std::vector<RegisterValue> arg_vals;
                    for (auto arg_reg : pc->call_args) arg_vals.push_back(registers[arg_reg]);
                    arg_vals.insert(arg_vals.end(), closure_extra_args.begin(), closure_extra_args.end());

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

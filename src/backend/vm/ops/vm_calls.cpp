#include "../register.hh"
#include "../resource_manager.hh"
#include "../../../lir/function_registry.hh"
#include "../../../lir/builtin_functions.hh"
#include "../../../frontend/module_manager.hh"
#include "../../../runtime/lymarrt/lymarrt.h"
#include "../vm_runtime.hh"
#include "../vm_value.hh"
#include "../vm_tuple.hh"
#include "../vm_list.hh"
#include "../vm_dict.hh"
#include "../constant_utils.hh"
#include "../compiled_resolver.hh"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

RegisterValue RegisterVM::call_interpreted(const std::string& name,
                                            const std::vector<RegisterValue>& args) {
    auto* function = LIR::FunctionRegistry::getInstance().getFunction(name);
    if (!function) throw std::runtime_error("Missing interpreted function: " + name);

    for (auto value : args) register_native_allocation(value);
    size_t caller_depth = vm_region_stack.size();
    uint64_t caller_region = active_region_id;
    invocation_parents.push_back(caller_region);
    auto caller_arguments = std::move(argument_stack);
    argument_stack.clear();
    auto caller_registers = std::move(registers);
    const auto* caller_function = current_function_;
    if (!spare_register_files_.empty()) {
        registers = std::move(spare_register_files_.back());
        spare_register_files_.pop_back();
    }
    registers.assign(std::max(size_t(256), args.size()), VAL_NIL);
    std::copy(args.begin(), args.end(), registers.begin());
    current_function_ = function;
    try {
        // The registry already owns the immutable instructions and type maps.
        execute_instructions(*function, 0, function->instructions.size());
        auto result = registers[0];
        register_native_allocation(result);
        promote_graph(result, caller_region);
        while (vm_region_stack.size() > caller_depth) exit_region();
        invocation_parents.pop_back();
        argument_stack = std::move(caller_arguments);
        spare_register_files_.push_back(std::move(registers));
        registers = std::move(caller_registers);
        current_function_ = caller_function;
        return result;
    } catch (...) {
        while (vm_region_stack.size() > caller_depth) exit_region();
        invocation_parents.pop_back();
        argument_stack = std::move(caller_arguments);
        spare_register_files_.push_back(std::move(registers));
        registers = std::move(caller_registers);
        current_function_ = caller_function;
        throw;
    }
}

void RegisterVM::execute_calls(const LIR::LIR_Inst* pc) {
    ResourceManager::getInstance().setCurrentFiber(get_current_fiber());
    switch (pc->op) {
        case LIR::LIR_Op::CallBuiltin:
        case LIR::LIR_Op::Call: {
            auto& func_manager = LIR::LIRFunctionManager::getInstance();
            // Length queries must inspect the runtime header, never copy a graph.
            // Keep unsupported types on the existing builtin validation path.
            if (pc->call_args.size() == 1 &&
                (pc->func_name == "len" || pc->func_name == "_builtin_string_byte_len")) {
                auto value = registers[pc->call_args[0]];
                auto* header = IS_PTR(value) ? static_cast<ObjHeader*>(UNBOX_PTR(value)) : nullptr;
                bool handled = false;
                uint64_t length = 0;
                if (header && header->type_id == TYPE_STRING) {
                    length = reinterpret_cast<LmStringHeader*>(header)->len;
                    handled = true;
                } else if (pc->func_name == "len") {
                    if (header && header->type_id == TYPE_LIST) {
                        length = reinterpret_cast<LmList*>(header)->size;
                        handled = true;
                    } else if (header && header->type_id == TYPE_DICT) {
                        length = reinterpret_cast<LmDict*>(header)->size;
                        handled = true;
                    } else if (value == VAL_NIL) {
                        handled = true;
                    }
                }
                if (handled) {
                    registers[pc->dst] = make_i64(length);
                    break;
                }
            }
            bool is_builtin_target = (pc->op == LIR::LIR_Op::CallBuiltin) ||
                                     (pc->func_name.rfind("_builtin_", 0) == 0);

            if (is_builtin_target && LIR::BuiltinUtils::isBuiltinFunction(pc->func_name)) {
                // Native fast-path for LmStringHeader string builtins
                auto get_hdr = [this](uint32_t r) -> LmStringHeader* {
                    RegisterValue val = registers[r];
                    if (!IS_PTR(val)) return nullptr;
                    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
                    if (!h) return nullptr;
                    if (h->type_id == TYPE_STRING) return (LmStringHeader*)h;
                    if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                        const char* cstr = (const char*)((LmBox*)h)->value.as_ptr;
                        return lm_str_from_bytes(cstr ? cstr : "", cstr ? strlen(cstr) : 0);
                    }
                    return nullptr;
                };

                const std::string& fname = pc->func_name;
                bool handled = false;
                if (fname == "_builtin_string_join" || fname == "_builtin_list_slice" || fname == "_builtin_string_hash_bytes") {
                    std::vector<LmValue> args;
                    for (auto reg : pc->call_args) args.push_back(registers[reg]);
                    registers[pc->dst] = Backend::Native::host_api().helper(this,
                        static_cast<uint32_t>(Backend::Native::Helper::Builtin),
                        VAL_NIL, VAL_NIL, VAL_NIL, fname.c_str(), args.data(), args.size());
                    handled = true;
                } else if (fname == "_builtin_substring" && pc->call_args.size() >= 3) {
                    LmStringHeader* str = get_hdr(pc->call_args[0]);
                    int64_t start = as_i64(registers[pc->call_args[1]]);
                    int64_t end = as_i64(registers[pc->call_args[2]]);
                    LmStringHeader* res = lm_str_substring(str, start, end);
                    registers[pc->dst] = BOX_PTR(res);
                    register_native_allocation(registers[pc->dst]);
                    handled = true;
                } else if (fname == "_builtin_string_byte_at" && pc->call_args.size() >= 2) {
                    LmStringHeader* str = get_hdr(pc->call_args[0]);
                    int64_t idx = as_i64(registers[pc->call_args[1]]);
                    registers[pc->dst] = make_i64(lm_str_byte_at(str, idx >= 0 ? (uint64_t)idx : UINT64_MAX));
                    handled = true;
                } else if (fname == "_builtin_string_index_of" && pc->call_args.size() >= 2) {
                    LmStringHeader* str = get_hdr(pc->call_args[0]);
                    LmStringHeader* sub = get_hdr(pc->call_args[1]);
                    registers[pc->dst] = make_i64(lm_str_index_of(str, sub));
                    handled = true;
                } else if (fname == "_builtin_string_contains" && pc->call_args.size() >= 2) {
                    LmStringHeader* str = get_hdr(pc->call_args[0]);
                    LmStringHeader* sub = get_hdr(pc->call_args[1]);
                    registers[pc->dst] = lm_str_contains(str, sub) ? VAL_TRUE : VAL_FALSE;
                    handled = true;
                } else if (fname == "_builtin_string_starts_with" && pc->call_args.size() >= 2) {
                    LmStringHeader* str = get_hdr(pc->call_args[0]);
                    LmStringHeader* pre = get_hdr(pc->call_args[1]);
                    registers[pc->dst] = lm_str_starts_with(str, pre) ? VAL_TRUE : VAL_FALSE;
                    handled = true;
                } else if (fname == "_builtin_string_ends_with" && pc->call_args.size() >= 2) {
                    LmStringHeader* str = get_hdr(pc->call_args[0]);
                    LmStringHeader* sfx = get_hdr(pc->call_args[1]);
                    registers[pc->dst] = lm_str_ends_with(str, sfx) ? VAL_TRUE : VAL_FALSE;
                    handled = true;
                } else if (fname == "_builtin_string_trim" && pc->call_args.size() >= 1) {
                    LmStringHeader* str = get_hdr(pc->call_args[0]);
                    LmStringHeader* res = lm_str_trim(str);
                    registers[pc->dst] = BOX_PTR(res);
                    register_native_allocation(registers[pc->dst]);
                    handled = true;
                } else if (fname == "_builtin_string_to_lower" && pc->call_args.size() >= 1) {
                    LmStringHeader* str = get_hdr(pc->call_args[0]);
                    LmStringHeader* res = lm_str_to_lower(str);
                    registers[pc->dst] = BOX_PTR(res);
                    register_native_allocation(registers[pc->dst]);
                    handled = true;
                } else if (fname == "_builtin_string_to_upper" && pc->call_args.size() >= 1) {
                    LmStringHeader* str = get_hdr(pc->call_args[0]);
                    LmStringHeader* res = lm_str_to_upper(str);
                    registers[pc->dst] = BOX_PTR(res);
                    register_native_allocation(registers[pc->dst]);
                    handled = true;
                } else if (fname == "_builtin_string_replace" && pc->call_args.size() >= 3) {
                    LmStringHeader* str = get_hdr(pc->call_args[0]);
                    LmStringHeader* old_sub = get_hdr(pc->call_args[1]);
                    LmStringHeader* new_sub = get_hdr(pc->call_args[2]);
                    LmStringHeader* res = lm_str_replace(str, old_sub, new_sub);
                    registers[pc->dst] = BOX_PTR(res);
                    register_native_allocation(registers[pc->dst]);
                    handled = true;
                } else if (fname == "_builtin_string_decode_next" && pc->call_args.size() >= 2) {
                    LmStringHeader* str = get_hdr(pc->call_args[0]);
                    int64_t offset = as_i64(registers[pc->call_args[1]]);
                    uint64_t res = lm_str_decode_next(str, offset >= 0 ? (uint64_t)offset : 0);
                    registers[pc->dst] = make_i64((int64_t)res);
                    handled = true;
                }

                if (!handled) {
                    // Fallback for general builtins (print, input, time, etc.)
                    std::vector<ValuePtr> args;
                    args.reserve(pc->call_args.size());
                    for (auto arg_reg : pc->call_args) {
                        args.push_back(register_to_value_ptr(registers[arg_reg], get_register_language_type(arg_reg)));
                    }
                    try {
                        ValuePtr result = LIR::BuiltinUtils::callBuiltinFunction(pc->func_name, args);
                        registers[pc->dst] = LM::Backend::VM::compiler_value_to_backend_value(result);
                    } catch (const std::exception& e) {
                        throw std::runtime_error("Builtin function '" + pc->func_name + "' error: " + e.what());
                    }
                }
                break;
            }

            if (CompiledResolver::getInstance().dispatch(pc->func_name, *pc, registers, this)) {
                break;
            }

            if (func_manager.hasFunction(pc->func_name)) {
                auto func = func_manager.getFunction(pc->func_name);
                std::vector<RegisterValue> arg_vals;
                size_t expected_total = func->getParameters().size();
                arg_vals.reserve(std::max((size_t)pc->call_args.size(), expected_total));
                for (auto arg_reg : pc->call_args) {
                    if (arg_reg < registers.size()) {
                        arg_vals.push_back(registers[arg_reg]);
                    } else {
                        arg_vals.push_back(VAL_NIL);
                    }
                }
                while (arg_vals.size() < expected_total) {
                    arg_vals.push_back(VAL_NIL);
                }

                auto return_value = call_interpreted(pc->func_name, arg_vals);
                if (pc->dst != UINT32_MAX) registers[pc->dst] = return_value;
            } else if (pc->func_name == "channel") {
                // Allocate a real runtime Channel pointer boxed as a pointer!
                auto channel = std::make_unique<LM::Backend::Channel>(1024);
                channels.push_back(std::move(channel));
                registers[pc->dst] = BOX_PTR(channels.back().get());
                opaque_runtime_pointers.insert(reinterpret_cast<uintptr_t>(channels.back().get()));
            } else if (LIR::BuiltinUtils::isBuiltinFunction(pc->func_name)) {
                // Handle builtin functions (print, input, etc.)
                std::vector<ValuePtr> args;
                args.reserve(pc->call_args.size());
                for (auto arg_reg : pc->call_args) {
                    args.push_back(register_to_value_ptr(registers[arg_reg], get_register_language_type(arg_reg)));
                }
                try {
                    ValuePtr result = LIR::BuiltinUtils::callBuiltinFunction(pc->func_name, args);
                    // Builtin functions return ValuePtr, convert to RegisterValue
                    registers[pc->dst] = LM::Backend::VM::compiler_value_to_backend_value(result);
                } catch (const std::exception& e) {
                    throw std::runtime_error("Builtin function '" + pc->func_name + "' error: " + e.what());
                }
            } else if (pc->func_name == "assert") {
                bool condition = (registers[pc->call_args[0]] == VAL_TRUE);
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
                } else if (h->type_id == TYPE_STRING) {
                    func_name = ((LmStringHeader*)h)->data;
                } else if (h->type_id == TYPE_TUPLE) {
                    LmTuple* closure_tuple = (LmTuple*)h;
                    RegisterValue name_value = lm_tuple_get(closure_tuple, 0);
                    if (IS_PTR(name_value)) {
                        ObjHeader* name_header = (ObjHeader*)UNBOX_PTR(name_value);
                        if (name_header->type_id == TYPE_BOX && ((LmBox*)name_header)->type == LM_BOX_STRING) {
                            func_name = (char*)((LmBox*)name_header)->value.as_ptr;
                            closure_extra_args.push_back(func_obj);
                        } else if (name_header->type_id == TYPE_STRING) {
                            func_name = ((LmStringHeader*)name_header)->data;
                            closure_extra_args.push_back(func_obj);
                        }
                    }
                }
            }
            
            if (!func_name.empty()) {
                if (CompiledResolver::getInstance().dispatch(func_name, *pc, registers, this, closure_extra_args)) {
                    break;
                }

                auto& func_manager = LIR::LIRFunctionManager::getInstance();
                if (func_manager.hasFunction(func_name)) {
                    auto func = func_manager.getFunction(func_name);
                    std::vector<RegisterValue> arg_vals;
                    size_t expected_total = func->getParameters().size();
                    arg_vals.reserve(std::max((size_t)pc->call_args.size() + closure_extra_args.size(), expected_total));
                    for (auto arg_reg : pc->call_args) arg_vals.push_back(registers[arg_reg]);
                    arg_vals.insert(arg_vals.end(), closure_extra_args.begin(), closure_extra_args.end());

                    while (arg_vals.size() < expected_total) {
                        arg_vals.push_back(VAL_NIL);
                    }

                    auto return_value = call_interpreted(func_name, arg_vals);
                    if (pc->dst != UINT32_MAX) registers[pc->dst] = return_value;
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

#include "../register.hh"
#include "../vm_runtime.hh"
#include "../vm_value.hh"
#include "../vm_list.hh"
#include "../../../lir/functions.hh"
#include "../vm_string.hh"
#include "../../../runtime/limitrt/limitrt.h"
#include <cstdlib>
#include <cstring>
#include <memory>
#include <unordered_map>
#include <mutex>
#include <functional>
#include <vector>
#include <string>
#include <iostream>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

namespace {
    std::mutex g_callframe_mutex;
    std::unordered_map<uint64_t, std::vector<RegisterValue>> g_callframe_registers;
    std::unordered_map<uint64_t, std::vector<uint8_t>> g_callframe_stack;
    uint64_t g_next_callframe_id = 0;

    struct VmCallbackUserData {
        RegisterVM* vm;
        std::string func_name;
    };

    LIR::Reg arg_reg(const LIR::LIR_Inst* pc, size_t index, LIR::Reg fallback) {
        return index < pc->call_args.size() ? pc->call_args[index] : fallback;
    }

    const char* get_cstring_from_value(RegisterValue value) {
        if (!IS_PTR(value)) return nullptr;
        auto* header = static_cast<ObjHeader*>(UNBOX_PTR(value));
        if (header->type_id == TYPE_STRING) {
            return static_cast<const char*>(reinterpret_cast<LmStringHeader*>(header)->data);
        }
        if (header->type_id == TYPE_BOX && static_cast<LmBox*>(static_cast<void*>(header))->type == LM_BOX_STRING) {
            return static_cast<const char*>(static_cast<LmBox*>(static_cast<void*>(header))->value.as_ptr);
        }
        return nullptr;
    }

    limitrt_type lir_type_to_limitrt_type(LIR::Type type) {
        switch (type) {
            case LIR::Type::I8:   return LIMITRT_TYPE_I8;
            case LIR::Type::U8:   return LIMITRT_TYPE_U8;
            case LIR::Type::I16:  return LIMITRT_TYPE_I16;
            case LIR::Type::U16:  return LIMITRT_TYPE_U16;
            case LIR::Type::I32:  return LIMITRT_TYPE_I32;
            case LIR::Type::U32:  return LIMITRT_TYPE_U32;
            case LIR::Type::I64:  return LIMITRT_TYPE_I64;
            case LIR::Type::U64:  return LIMITRT_TYPE_U64;
            case LIR::Type::F32:  return LIMITRT_TYPE_F32;
            case LIR::Type::F64:  return LIMITRT_TYPE_F64;
            case LIR::Type::Bool: return LIMITRT_TYPE_U8;
            case LIR::Type::Ptr:  return LIMITRT_TYPE_PTR;
            case LIR::Type::Void: return LIMITRT_TYPE_VOID;
            default:              return LIMITRT_TYPE_VOID;
        }
    }

    bool ffi_type_id_to_limitrt(int64_t id, bool allow_void, limitrt_type& out) {
        switch (id) {
            case 0:  out = LIMITRT_TYPE_I8;  return true;
            case 1:  out = LIMITRT_TYPE_U8;  return true;
            case 2:  out = LIMITRT_TYPE_I16; return true;
            case 3:  out = LIMITRT_TYPE_U16; return true;
            case 4:  out = LIMITRT_TYPE_I32; return true;
            case 5:  out = LIMITRT_TYPE_U32; return true;
            case 6:  out = LIMITRT_TYPE_I64; return true;
            case 7:  out = LIMITRT_TYPE_U64; return true;
            case 8:  out = LIMITRT_TYPE_F32; return true;
            case 9:  out = LIMITRT_TYPE_F64; return true;
            case 10: out = LIMITRT_TYPE_PTR; return true;
            case 11: out = LIMITRT_TYPE_CSTRING; return true;
            case 12:
                if (allow_void) { out = LIMITRT_TYPE_VOID; return true; }
                return false;
            default: return false;
        }
    }

    void* value_to_ptr(RegisterValue val) {
        if (IS_PTR(val)) {
            auto* header = static_cast<ObjHeader*>(UNBOX_PTR(val));
            if (header->type_id == TYPE_FOREIGN_PTR) return ((ObjForeignPtr*)header)->ptr;
            if (header->type_id == TYPE_FRAME) {
                LmFrame* frame = reinterpret_cast<LmFrame*>(header);
                if (frame->field_count > 0) return value_to_ptr(frame->fields[0]);
            }
            return UNBOX_PTR(val);
        }
        if (is_integer(val)) return (void*)(uintptr_t)as_i64(val);
        return nullptr;
    }

    limitrt_value vm_val_to_limitrt_val(RegisterValue val, limitrt_type type) {
        limitrt_value v;
        std::memset(&v, 0, sizeof(v));
        v.type = type;
        switch (type) {
            case LIMITRT_TYPE_I8:  v.val.i8 = (int8_t)as_i64(val); break;
            case LIMITRT_TYPE_U8:  v.val.u8 = (uint8_t)as_i64(val); break;
            case LIMITRT_TYPE_I16: v.val.i16 = (int16_t)as_i64(val); break;
            case LIMITRT_TYPE_U16: v.val.u16 = (uint16_t)as_i64(val); break;
            case LIMITRT_TYPE_I32: v.val.i32 = (int32_t)as_i64(val); break;
            case LIMITRT_TYPE_U32: v.val.u32 = (uint32_t)as_i64(val); break;
            case LIMITRT_TYPE_I64: v.val.i64 = as_i64(val); break;
            case LIMITRT_TYPE_U64: v.val.u64 = (uint64_t)as_i64(val); break;
            case LIMITRT_TYPE_F32: v.val.f32 = (float)as_float(val); break;
            case LIMITRT_TYPE_F64: v.val.f64 = as_float(val); break;
            case LIMITRT_TYPE_PTR:
            case LIMITRT_TYPE_CSTRING: {
                void* p = value_to_ptr(val);
                const char* cstr = get_cstring_from_value(val);
                if (cstr) p = (void*)cstr;
                v.val.ptr = p;
                break;
            }
            default: break;
        }
        return v;
    }

    RegisterValue limitrt_val_to_vm_val(const limitrt_value& v, limitrt_type type) {
        switch (type) {
            case LIMITRT_TYPE_I8:  return BOX_INT((int64_t)v.val.i8);
            case LIMITRT_TYPE_U8:  return BOX_INT((int64_t)v.val.u8);
            case LIMITRT_TYPE_I16: return BOX_INT((int64_t)v.val.i16);
            case LIMITRT_TYPE_U16: return BOX_INT((int64_t)v.val.u16);
            case LIMITRT_TYPE_I32: return BOX_INT((int64_t)v.val.i32);
            case LIMITRT_TYPE_U32: return BOX_INT((int64_t)v.val.u32);
            case LIMITRT_TYPE_I64: return BOX_INT(v.val.i64);
            case LIMITRT_TYPE_U64: return BOX_INT((int64_t)v.val.u64);
            case LIMITRT_TYPE_F32: return make_float((double)v.val.f32);
            case LIMITRT_TYPE_F64: return make_float(v.val.f64);
            case LIMITRT_TYPE_PTR:
            case LIMITRT_TYPE_CSTRING:
                return v.val.ptr ? lm_alloc_foreign_ptr(v.val.ptr) : VAL_NIL;
            default:
                return VAL_NIL;
        }
    }

    void vm_callback_trampoline_handler(
        void* userdata,
        const limitrt_value* args,
        size_t num_args,
        limitrt_value* out_result)
    {
        auto* data = static_cast<VmCallbackUserData*>(userdata);
        RegisterVM* vm = data->vm;

        std::vector<RegisterValue> vm_args;
        vm_args.reserve(num_args);
        for (size_t i = 0; i < num_args; ++i) {
            vm_args.push_back(limitrt_val_to_vm_val(args[i], (limitrt_type)args[i].type));
        }

        RegisterValue rv = vm->invoke_for_callback(data->func_name, vm_args);
        if (out_result) {
            *out_result = vm_val_to_limitrt_val(rv, (limitrt_type)out_result->type);
        }
    }

} // namespace (anonymous)

RegisterValue RegisterVM::invoke_for_callback(
    const std::string& func_name,
    const std::vector<RegisterValue>& args)
{
    auto& func_manager = LIR::LIRFunctionManager::getInstance();
    if (!func_manager.hasFunction(func_name)) {
        std::cerr << "[trampoline] function '" << func_name << "' not found in registry\n";
        return VAL_NIL;
    }
    auto func = func_manager.getFunction(func_name);

    std::vector<RegisterValue> arg_vals = args;
    size_t expected = func->getParameters().size();
    while (arg_vals.size() < expected) arg_vals.push_back(VAL_NIL);

    auto saved_registers              = registers;
    const LIR::LIR_Function* saved_func = current_function_;

    registers.assign(registers.size(), VAL_NIL);
    for (size_t i = 0; i < arg_vals.size() && i < registers.size(); ++i)
        registers[i] = arg_vals[i];

    LIR::LIR_Function temp_wrapper(func->getName(),
                                    static_cast<uint32_t>(arg_vals.size()));
    temp_wrapper.instructions            = func->getInstructions();
    temp_wrapper.register_language_types = func->getRegisterLanguageTypes();
    temp_wrapper.register_types          = func->getRegisterTypes();
    current_function_ = &temp_wrapper;

    try {
        execute_instructions(temp_wrapper, 0, temp_wrapper.instructions.size());
    } catch (const std::exception& e) {
        std::cerr << "[trampoline] Limitly callback '" << func_name
                  << "' threw: " << e.what() << '\n';
    } catch (...) {
        std::cerr << "[trampoline] Limitly callback '" << func_name
                  << "' threw unknown exception\n";
    }

    RegisterValue return_value = registers[0];

    registers        = saved_registers;
    current_function_ = saved_func;

    return return_value;
}

void RegisterVM::execute_extern_library_load(const LIR::LIR_Inst* pc) {
    LIR::Reg path_reg = arg_reg(pc, 0, pc->a);
    const char* path = get_cstring_from_value(registers[path_reg]);
    if (!path) { registers[pc->dst] = VAL_NIL; return; }
    void* handle = limitrt_library_open(path);
    if (!handle) { registers[pc->dst] = VAL_NIL; return; }
    RegisterValue val = lm_alloc_foreign_ptr(handle);
    registers[pc->dst] = val;
    if (IS_PTR(val) && !vm_region_stack.empty()) {
        uintptr_t ptr = reinterpret_cast<uintptr_t>(UNBOX_PTR(val));
        vm_allocation_regions[ptr] = active_region_id;
    }
}

void RegisterVM::execute_extern_library_unload(const LIR::LIR_Inst* pc) {
    void* handle = value_to_ptr(registers[pc->a]);
    if (handle) {
        limitrt_library_close(handle);
    }
}

void RegisterVM::execute_extern_library_get_symbol(const LIR::LIR_Inst* pc) {
    LIR::Reg handle_reg = arg_reg(pc, 0, pc->a);
    LIR::Reg symbol_reg = arg_reg(pc, 1, pc->b);
    void* handle = value_to_ptr(registers[handle_reg]);
    if (!handle) { registers[pc->dst] = VAL_NIL; return; }
    const char* symbol = get_cstring_from_value(registers[symbol_reg]);
    if (!symbol) { registers[pc->dst] = VAL_NIL; return; }
    void* ptr = limitrt_symbol_lookup(handle, symbol);
    RegisterValue val = ptr ? lm_alloc_foreign_ptr(ptr) : VAL_NIL;
    registers[pc->dst] = val;
    if (IS_PTR(val) && !vm_region_stack.empty()) {
        uintptr_t ptr_val = reinterpret_cast<uintptr_t>(UNBOX_PTR(val));
        vm_allocation_regions[ptr_val] = active_region_id;
    }
}

void RegisterVM::execute_extern_call_function(const LIR::LIR_Inst* pc) {
    RegisterValue func_ptr_val = registers[arg_reg(pc, 0, pc->a)];
    void* func_ptr = value_to_ptr(func_ptr_val);
    if (!func_ptr) { registers[pc->dst] = VAL_NIL; return; }

    limitrt_type ret_type = lir_type_to_limitrt_type(pc->result_type);
    std::vector<LIR::Reg> arg_regs = pc->call_args;
    std::vector<RegisterValue> call_arg_values;
    std::vector<limitrt_type> resolved_arg_types;

    if (pc->func_name == "std.ffi.foreign_call" || pc->func_name == "ffi.foreign_call") {
        if (pc->call_args.size() > 2) {
            int64_t ret_id = as_i64(registers[pc->call_args[2]]);
            ffi_type_id_to_limitrt(ret_id, true, ret_type);
        }

        LmList* pt_list = nullptr;
        if (pc->call_args.size() > 3) {
            RegisterValue pt_val = registers[pc->call_args[3]];
            if (IS_PTR(pt_val) && ((ObjHeader*)UNBOX_PTR(pt_val))->type_id == TYPE_LIST) {
                pt_list = (LmList*)UNBOX_PTR(pt_val);
            }
        }

        if (pc->call_args.size() > 1) {
            RegisterValue args_val = registers[pc->call_args[1]];
            if (IS_PTR(args_val) && ((ObjHeader*)UNBOX_PTR(args_val))->type_id == TYPE_LIST) {
                LmList* args_list = (LmList*)UNBOX_PTR(args_val);
                for (uint64_t i = 0; i < args_list->size; ++i) {
                    RegisterValue val = args_list->data[i];
                    call_arg_values.push_back(val);
                    limitrt_type arg_t = LIMITRT_TYPE_I64;
                    bool got_type = false;
                    if (pt_list && i < pt_list->size) {
                        int64_t tid = as_i64(pt_list->data[i]);
                        got_type = ffi_type_id_to_limitrt(tid, false, arg_t);
                    }
                    if (!got_type) {
                        if (is_float(val)) arg_t = LIMITRT_TYPE_F64;
                        else if (IS_PTR(val)) arg_t = LIMITRT_TYPE_PTR;
                        else arg_t = LIMITRT_TYPE_I64;
                    }
                    resolved_arg_types.push_back(arg_t);
                }
            }
        }
    } else {
        size_t arg_start = 0;
        if (pc->op == LIR::LIR_Op::ForeignCall) arg_start = 1;
        for (size_t i = arg_start; i < arg_regs.size(); ++i) {
            call_arg_values.push_back(registers[arg_regs[i]]);
            if (i < pc->call_arg_types.size() && pc->call_arg_types[i] != LIR::Type::Void) {
                resolved_arg_types.push_back(lir_type_to_limitrt_type(pc->call_arg_types[i]));
            } else {
                RegisterValue val = registers[arg_regs[i]];
                if (is_float(val)) resolved_arg_types.push_back(LIMITRT_TYPE_F64);
                else if (IS_PTR(val)) resolved_arg_types.push_back(LIMITRT_TYPE_PTR);
                else resolved_arg_types.push_back(LIMITRT_TYPE_I64);
            }
        }
    }

    size_t num_args = call_arg_values.size();
    std::vector<limitrt_value> limitrt_args(num_args);
    for (size_t i = 0; i < num_args; ++i) {
        limitrt_args[i] = vm_val_to_limitrt_val(call_arg_values[i], resolved_arg_types[i]);
    }

    limitrt_value out_res;
    std::memset(&out_res, 0, sizeof(out_res));
    if (limitrt_ffi_call(func_ptr, ret_type, resolved_arg_types.data(), limitrt_args.data(), num_args, &out_res)) {
        RegisterValue val = limitrt_val_to_vm_val(out_res, ret_type);
        registers[pc->dst] = val;
        if (IS_PTR(val) && !vm_region_stack.empty()) {
            uintptr_t ptr_val = reinterpret_cast<uintptr_t>(UNBOX_PTR(val));
            vm_allocation_regions[ptr_val] = active_region_id;
        }
    } else {
        registers[pc->dst] = VAL_NIL;
    }
}

void RegisterVM::execute_extern_register_callback(const LIR::LIR_Inst* pc) {
    if (pc->call_args.size() != 3) {
        std::cerr << "[ffi] callback_create: expected name, argument types, and return type\n";
        registers[pc->dst] = VAL_NIL;
        return;
    }
    std::string limitly_func_name;
    if (!pc->call_args.empty()) {
        const char* cstr = get_cstring_from_value(registers[pc->call_args[0]]);
        if (cstr) {
            limitly_func_name = cstr;
        } else {
            RegisterValue nv = registers[pc->call_args[0]];
            if (IS_PTR(nv)) {
                auto* h = static_cast<ObjHeader*>(UNBOX_PTR(nv));
                if (h && h->type_id == TYPE_STRING)
                    limitly_func_name = ((LmStringHeader*)h)->data;
            }
        }
    }
    if (limitly_func_name.empty()) {
        std::cerr << "[ffi] callback_create: missing or empty function name\n";
        registers[pc->dst] = VAL_NIL;
        return;
    }
    auto& functions = LIR::LIRFunctionManager::getInstance();
    if (!functions.hasFunction(limitly_func_name)) {
        std::cerr << "[ffi] callback_create: function '" << limitly_func_name
                  << "' is not registered\n";
        registers[pc->dst] = VAL_NIL;
        return;
    }

    std::vector<limitrt_type> arg_types;
    bool valid_arg_list = false;
    if (pc->call_args.size() >= 2) {
        RegisterValue list_val = registers[pc->call_args[1]];
        if (IS_PTR(list_val)) {
            auto* h = static_cast<ObjHeader*>(UNBOX_PTR(list_val));
            if (h && h->type_id == TYPE_LIST) {
                valid_arg_list = true;
                LmList* lst = (LmList*)h;
                uint64_t count = lm_list_len(lst);
                if (count > 64) {
                    std::cerr << "[ffi] callback_create: at most 64 arguments are supported\n";
                    registers[pc->dst] = VAL_NIL;
                    return;
                }
                arg_types.reserve(count);
                for (uint64_t i = 0; i < count; ++i) {
                    int64_t type_id = as_i64(lm_list_get(lst, i));
                    limitrt_type type;
                    if (!ffi_type_id_to_limitrt(type_id, false, type)) {
                        std::cerr << "[ffi] callback_create: invalid argument type id "
                                  << type_id << " at index " << i << '\n';
                        registers[pc->dst] = VAL_NIL;
                        return;
                    }
                    arg_types.push_back(type);
                }
            }
        }
    }
    if (!valid_arg_list) {
        std::cerr << "[ffi] callback_create: argument types must be a list\n";
        registers[pc->dst] = VAL_NIL;
        return;
    }
    const size_t expected_args = functions.getFunction(limitly_func_name)->getParameters().size();
    if (arg_types.size() != expected_args) {
        std::cerr << "[ffi] callback_create: signature for '" << limitly_func_name
                  << "' declares " << arg_types.size() << " native arguments but function expects "
                  << expected_args << '\n';
        registers[pc->dst] = VAL_NIL;
        return;
    }

    limitrt_type ret_type;
    int64_t rid = as_i64(registers[pc->call_args[2]]);
    if (!ffi_type_id_to_limitrt(rid, true, ret_type)) {
        std::cerr << "[ffi] callback_create: invalid return type id " << rid << '\n';
        registers[pc->dst] = VAL_NIL;
        return;
    }

    VmCallbackUserData* udata = new VmCallbackUserData{this, limitly_func_name};
    int64_t id = limitrt_callback_create(
        vm_callback_trampoline_handler,
        udata,
        arg_types.data(),
        arg_types.size(),
        ret_type
    );

    if (id <= 0) {
        delete udata;
        registers[pc->dst] = VAL_NIL;
        return;
    }
    registers[pc->dst] = BOX_INT(id);
}

void RegisterVM::execute_extern_unregister_callback(const LIR::LIR_Inst* pc) {
    int64_t id = as_i64(registers[pc->a]);
    void* udata = limitrt_callback_get_userdata(id);
    if (udata) {
        delete static_cast<VmCallbackUserData*>(udata);
    }
    limitrt_callback_destroy(id);
}

void RegisterVM::execute_extern_get_callback_ptr(const LIR::LIR_Inst* pc) {
    int64_t id = as_i64(registers[pc->a]);
    void* code_ptr = limitrt_callback_get_ptr(id);
    if (code_ptr) {
        RegisterValue val = lm_alloc_foreign_ptr(code_ptr);
        registers[pc->dst] = val;
        if (IS_PTR(val) && !vm_region_stack.empty()) {
            uintptr_t ptr_val = reinterpret_cast<uintptr_t>(UNBOX_PTR(val));
            vm_allocation_regions[ptr_val] = active_region_id;
        }
    } else {
        registers[pc->dst] = VAL_NIL;
    }
}

void RegisterVM::execute_extern_ccall_frame_create(const LIR::LIR_Inst* pc) {
    int64_t rc = as_i64(registers[pc->a]); int64_t ss = as_i64(registers[pc->b]);
    if (rc < 0 || ss < 0) { registers[pc->dst] = VAL_NIL; return; }
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    uint64_t id = g_next_callframe_id++;
    g_callframe_registers[id] = std::vector<RegisterValue>(rc, VAL_NIL);
    g_callframe_stack[id] = std::vector<uint8_t>(ss, 0);
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(id));
}
void RegisterVM::execute_extern_ccall_frame_destroy(const LIR::LIR_Inst* pc) {
    int64_t id = as_i64(registers[pc->a]);
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    g_callframe_registers.erase(id); g_callframe_stack.erase(id);
}
void RegisterVM::execute_extern_ccall_frame_set_reg(const LIR::LIR_Inst* pc) {
    int64_t id = as_i64(registers[pc->dst]); int64_t idx = as_i64(registers[pc->a]);
    RegisterValue val = registers[pc->b];
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    auto it = g_callframe_registers.find(id);
    if (it != g_callframe_registers.end() && idx >= 0 && idx < (int64_t)it->second.size()) it->second[idx] = val;
}
void RegisterVM::execute_extern_ccall_frame_get_reg(const LIR::LIR_Inst* pc) {
    int64_t id = as_i64(registers[pc->a]); int64_t idx = as_i64(registers[pc->b]);
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    auto it = g_callframe_registers.find(id);
    if (it != g_callframe_registers.end() && idx >= 0 && idx < (int64_t)it->second.size()) registers[pc->dst] = it->second[idx];
    else registers[pc->dst] = VAL_NIL;
}
void RegisterVM::execute_extern_ccall_frame_set_stack_arg(const LIR::LIR_Inst* pc) {
    int64_t id = as_i64(registers[pc->dst]); int64_t off = as_i64(registers[pc->a]); int64_t val = as_i64(registers[pc->b]);
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    auto it = g_callframe_stack.find(id);
    if (it != g_callframe_stack.end() && off >= 0 && off + 8 <= (int64_t)it->second.size()) std::memcpy(&it->second[off], &val, 8);
}
void RegisterVM::execute_extern_ccall_frame_get_stack_arg(const LIR::LIR_Inst* pc) {
    int64_t id = as_i64(registers[pc->a]); int64_t off = as_i64(registers[pc->b]);
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    auto it = g_callframe_stack.find(id);
    if (it != g_callframe_stack.end() && off >= 0 && off + 8 <= (int64_t)it->second.size()) {
        int64_t val; std::memcpy(&val, &it->second[off], 8); registers[pc->dst] = BOX_INT(val);
    } else registers[pc->dst] = BOX_INT(0);
}
void RegisterVM::execute_extern_vm_save(const LIR::LIR_Inst* pc) { registers[pc->dst] = VAL_NIL; }
void RegisterVM::execute_extern_vm_restore(const LIR::LIR_Inst* pc) {}
void RegisterVM::execute_extern_calc_struct_layout(const LIR::LIR_Inst* pc) { registers[pc->dst] = VAL_NIL; }
void RegisterVM::execute_extern_get_abi_info(const LIR::LIR_Inst* pc) { registers[pc->dst] = VAL_NIL; }

void RegisterVM::execute_ffi(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::LibraryLoad: execute_extern_library_load(pc); break;
        case LIR::LIR_Op::LibraryUnload: execute_extern_library_unload(pc); break;
        case LIR::LIR_Op::LibrarySymbol: execute_extern_library_get_symbol(pc); break;
        case LIR::LIR_Op::ForeignCall:
        case LIR::LIR_Op::ForeignCallDirect: execute_extern_call_function(pc); break;
        case LIR::LIR_Op::CallbackCreate:
            if (pc->imm == 1) execute_extern_get_callback_ptr(pc);
            else              execute_extern_register_callback(pc);
            break;
        case LIR::LIR_Op::CallbackDestroy: execute_extern_unregister_callback(pc); break;
        default: break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM

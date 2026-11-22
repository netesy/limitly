#include "../register.hh"
#include "../vm_runtime.hh"
#include "../vm_value.hh"
#include "../vm_list.hh"
#include "../../../lir/functions.hh"
#include "../vm_string.hh"
#include "../../../runtime/lymarrt/lymarrt.h"
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

    lymarrt_type lir_type_to_lymarrt_type(LIR::Type type) {
        switch (type) {
            case LIR::Type::I8:   return LYMARRT_TYPE_I8;
            case LIR::Type::U8:   return LYMARRT_TYPE_U8;
            case LIR::Type::I16:  return LYMARRT_TYPE_I16;
            case LIR::Type::U16:  return LYMARRT_TYPE_U16;
            case LIR::Type::I32:  return LYMARRT_TYPE_I32;
            case LIR::Type::U32:  return LYMARRT_TYPE_U32;
            case LIR::Type::I64:  return LYMARRT_TYPE_I64;
            case LIR::Type::U64:  return LYMARRT_TYPE_U64;
            case LIR::Type::F32:  return LYMARRT_TYPE_F32;
            case LIR::Type::F64:  return LYMARRT_TYPE_F64;
            case LIR::Type::Bool: return LYMARRT_TYPE_U8;
            case LIR::Type::Ptr:  return LYMARRT_TYPE_PTR;
            case LIR::Type::Void: return LYMARRT_TYPE_VOID;
            default:              return LYMARRT_TYPE_VOID;
        }
    }

    bool ffi_type_id_to_lymarrt(int64_t id, bool allow_void, lymarrt_type& out) {
        switch (id) {
            case 0:  out = LYMARRT_TYPE_I8;  return true;
            case 1:  out = LYMARRT_TYPE_U8;  return true;
            case 2:  out = LYMARRT_TYPE_I16; return true;
            case 3:  out = LYMARRT_TYPE_U16; return true;
            case 4:  out = LYMARRT_TYPE_I32; return true;
            case 5:  out = LYMARRT_TYPE_U32; return true;
            case 6:  out = LYMARRT_TYPE_I64; return true;
            case 7:  out = LYMARRT_TYPE_U64; return true;
            case 8:  out = LYMARRT_TYPE_F32; return true;
            case 9:  out = LYMARRT_TYPE_F64; return true;
            case 10: out = LYMARRT_TYPE_PTR; return true;
            case 11: out = LYMARRT_TYPE_CSTRING; return true;
            case 12:
                if (allow_void) { out = LYMARRT_TYPE_VOID; return true; }
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

    lymarrt_value vm_val_to_lymarrt_val(RegisterValue val, lymarrt_type type) {
        lymarrt_value v;
        std::memset(&v, 0, sizeof(v));
        v.type = type;
        switch (type) {
            case LYMARRT_TYPE_I8:  v.val.i8 = (int8_t)as_i64(val); break;
            case LYMARRT_TYPE_U8:  v.val.u8 = (uint8_t)as_i64(val); break;
            case LYMARRT_TYPE_I16: v.val.i16 = (int16_t)as_i64(val); break;
            case LYMARRT_TYPE_U16: v.val.u16 = (uint16_t)as_i64(val); break;
            case LYMARRT_TYPE_I32: v.val.i32 = (int32_t)as_i64(val); break;
            case LYMARRT_TYPE_U32: v.val.u32 = (uint32_t)as_i64(val); break;
            case LYMARRT_TYPE_I64: v.val.i64 = as_i64(val); break;
            case LYMARRT_TYPE_U64: v.val.u64 = (uint64_t)as_i64(val); break;
            case LYMARRT_TYPE_F32: v.val.f32 = (float)as_float(val); break;
            case LYMARRT_TYPE_F64: v.val.f64 = as_float(val); break;
            case LYMARRT_TYPE_PTR:
            case LYMARRT_TYPE_CSTRING: {
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

    RegisterValue lymarrt_val_to_vm_val(const lymarrt_value& v, lymarrt_type type) {
        switch (type) {
            case LYMARRT_TYPE_I8:  return BOX_INT((int64_t)v.val.i8);
            case LYMARRT_TYPE_U8:  return BOX_INT((int64_t)v.val.u8);
            case LYMARRT_TYPE_I16: return BOX_INT((int64_t)v.val.i16);
            case LYMARRT_TYPE_U16: return BOX_INT((int64_t)v.val.u16);
            case LYMARRT_TYPE_I32: return BOX_INT((int64_t)v.val.i32);
            case LYMARRT_TYPE_U32: return BOX_INT((int64_t)v.val.u32);
            // i64/u64 from C can exceed the 61-bit immediate payload; BOX_INT would
            // shift those bits away and hand back a silently wrong number.
            case LYMARRT_TYPE_I64: return make_i64(v.val.i64);
            case LYMARRT_TYPE_U64: return make_u64(v.val.u64);
            case LYMARRT_TYPE_F32: return make_float((double)v.val.f32);
            case LYMARRT_TYPE_F64: return make_float(v.val.f64);
            case LYMARRT_TYPE_PTR:
            case LYMARRT_TYPE_CSTRING:
                return v.val.ptr ? lm_alloc_foreign_ptr(v.val.ptr) : VAL_NIL;
            default:
                return VAL_NIL;
        }
    }

    void vm_callback_trampoline_handler(
        void* userdata,
        const lymarrt_value* args,
        size_t num_args,
        lymarrt_value* out_result)
    {
        auto* data = static_cast<VmCallbackUserData*>(userdata);
        RegisterVM* vm = data->vm;

        std::vector<RegisterValue> vm_args;
        vm_args.reserve(num_args);
        for (size_t i = 0; i < num_args; ++i) {
            vm_args.push_back(lymarrt_val_to_vm_val(args[i], (lymarrt_type)args[i].type));
        }

        RegisterValue rv = vm->invoke_for_callback(data->func_name, vm_args);
        if (out_result) {
            *out_result = vm_val_to_lymarrt_val(rv, (lymarrt_type)out_result->type);
        }
    }

} // namespace (anonymous)

RegisterValue RegisterVM::invoke_for_callback(
    const std::string& func_name,
    const std::vector<RegisterValue>& args, bool propagate_errors)
{
    auto tid = std::this_thread::get_id();
    if (!callback_owner_set_) {
        callback_owner_ = tid;
        callback_owner_set_ = true;
    } else if (tid != callback_owner_) {
        // Foreign-thread native call: running call_interpreted here would
        // race the VM's shared registers/heap. Return a zeroed result.
        return VAL_NIL;
    }
    auto& manager = LIR::LIRFunctionManager::getInstance();
    if (!manager.hasFunction(func_name)) {
        if (propagate_errors) throw std::runtime_error("Native callback function not found: " + func_name);
        return VAL_NIL;
    }
    auto arg_vals = args;
    size_t expected = manager.getFunction(func_name)->getParameters().size();
    while (arg_vals.size() < expected) arg_vals.push_back(VAL_NIL);
    try {
        return call_interpreted(func_name, arg_vals);
    } catch (const std::exception& e) {
        if (propagate_errors) throw;
        std::cerr << "[trampoline] Lymar callback '" << func_name << "' threw: " << e.what() << '\n';
    } catch (...) {
        if (propagate_errors) throw;
        std::cerr << "[trampoline] Lymar callback threw an unknown exception\n";
    }
    return VAL_NIL;
}

void RegisterVM::execute_extern_library_load(const LIR::LIR_Inst* pc) {
    LIR::Reg path_reg = arg_reg(pc, 0, pc->a);
    const char* path = get_cstring_from_value(registers[path_reg]);
    if (!path) { registers[pc->dst] = VAL_NIL; return; }
    void* handle = lymarrt_library_open(path);
    if (!handle) { registers[pc->dst] = VAL_NIL; return; }
    RegisterValue val = lm_alloc_foreign_ptr(handle);
    registers[pc->dst] = val;
    register_native_allocation(registers[pc->dst]);
}

void RegisterVM::execute_extern_library_unload(const LIR::LIR_Inst* pc) {
    void* handle = value_to_ptr(registers[pc->a]);
    if (handle) {
        lymarrt_library_close(handle);
    }
}

void RegisterVM::execute_extern_library_get_symbol(const LIR::LIR_Inst* pc) {
    LIR::Reg handle_reg = arg_reg(pc, 0, pc->a);
    LIR::Reg symbol_reg = arg_reg(pc, 1, pc->b);
    void* handle = value_to_ptr(registers[handle_reg]);
    if (!handle) { registers[pc->dst] = VAL_NIL; return; }
    const char* symbol = get_cstring_from_value(registers[symbol_reg]);
    if (!symbol) { registers[pc->dst] = VAL_NIL; return; }
    void* ptr = lymarrt_symbol_lookup(handle, symbol);
    RegisterValue val = ptr ? lm_alloc_foreign_ptr(ptr) : VAL_NIL;
    registers[pc->dst] = val;
    register_native_allocation(registers[pc->dst]);
}

void RegisterVM::execute_extern_call_function(const LIR::LIR_Inst* pc) {
    // ForeignCallDirect carries the resolved fnptr in `a` and the C arguments
    // in call_args (func_name holds the symbol for AOT); ForeignCall carries
    // the fnptr as call_args[0] followed by the C arguments.
    RegisterValue func_ptr_val = (pc->op == LIR::LIR_Op::ForeignCallDirect && pc->a != UINT32_MAX)
        ? registers[pc->a]
        : registers[arg_reg(pc, 0, pc->a)];
    void* func_ptr = value_to_ptr(func_ptr_val);
    if (!func_ptr) { registers[pc->dst] = VAL_NIL; return; }

    lymarrt_type ret_type = lir_type_to_lymarrt_type(pc->result_type);
    std::vector<LIR::Reg> arg_regs = pc->call_args;
    std::vector<RegisterValue> call_arg_values;
    std::vector<lymarrt_type> resolved_arg_types;
    std::vector<lymarrt_struct_layout> struct_layouts;

    if (pc->func_name == "std.ffi.foreign_call" || pc->func_name == "ffi.foreign_call") {
        if (pc->call_args.size() > 2) {
            int64_t ret_id = as_i64(registers[pc->call_args[2]]);
            ffi_type_id_to_lymarrt(ret_id, true, ret_type);
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
                    lymarrt_type arg_t = LYMARRT_TYPE_I64;
                    bool got_type = false;
                    bool is_struct_arg = false;
                    if (pt_list && i < pt_list->size) {
                        RegisterValue ptv = pt_list->data[i];
                        // A param-type entry that is itself a list is a
                        // struct descriptor: [TYPE_STRUCT, e1, e2, ...].
                        if (IS_PTR(ptv) &&
                            ((ObjHeader*)UNBOX_PTR(ptv))->type_id == TYPE_LIST) {
                            LmList* desc = (LmList*)UNBOX_PTR(ptv);
                            if (desc->size >= 2 && desc->size - 1 <= LYMARRT_MAX_STRUCT_ELEMS &&
                                as_i64(desc->data[0]) == 13 /* TYPE_STRUCT */) {
                                lymarrt_struct_layout lay{};
                                lay.arg_index = (uint32_t)i;
                                lay.count = (uint32_t)(desc->size - 1);
                                bool ok_layout = true;
                                for (uint32_t e = 0; e < lay.count; ++e) {
                                    int64_t etid = as_i64(desc->data[e + 1]);
                                    if (!ffi_type_id_to_lymarrt(etid, false, lay.types[e])) {
                                        ok_layout = false;
                                        break;
                                    }
                                }
                                if (ok_layout) {
                                    struct_layouts.push_back(lay);
                                    arg_t = LYMARRT_TYPE_PTR;
                                    got_type = true;
                                    is_struct_arg = true;
                                }
                            }
                        } else {
                            int64_t tid = as_i64(ptv);
                            got_type = ffi_type_id_to_lymarrt(tid, false, arg_t);
                        }
                    }
                    (void)is_struct_arg;
                    if (!got_type) {
                        if (is_float(val)) arg_t = LYMARRT_TYPE_F64;
                        else if (IS_PTR(val)) arg_t = LYMARRT_TYPE_PTR;
                        else arg_t = LYMARRT_TYPE_I64;
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
                resolved_arg_types.push_back(lir_type_to_lymarrt_type(pc->call_arg_types[i]));
            } else {
                RegisterValue val = registers[arg_regs[i]];
                if (is_float(val)) resolved_arg_types.push_back(LYMARRT_TYPE_F64);
                else if (IS_PTR(val)) resolved_arg_types.push_back(LYMARRT_TYPE_PTR);
                else resolved_arg_types.push_back(LYMARRT_TYPE_I64);
            }
        }
    }

    size_t num_args = call_arg_values.size();
    std::vector<lymarrt_value> lymarrt_args(num_args);
    for (size_t i = 0; i < num_args; ++i) {
        lymarrt_args[i] = vm_val_to_lymarrt_val(call_arg_values[i], resolved_arg_types[i]);
    }

    lymarrt_value out_res;
    std::memset(&out_res, 0, sizeof(out_res));
    if (lymarrt_ffi_call_ex(func_ptr, ret_type, resolved_arg_types.data(), lymarrt_args.data(), num_args,
                            struct_layouts.empty() ? nullptr : struct_layouts.data(), struct_layouts.size(), &out_res)) {
        RegisterValue val = lymarrt_val_to_vm_val(out_res, ret_type);
        registers[pc->dst] = val;
        register_native_allocation(registers[pc->dst]);
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
    std::string lymar_func_name;
    if (!pc->call_args.empty()) {
        const char* cstr = get_cstring_from_value(registers[pc->call_args[0]]);
        if (cstr) {
            lymar_func_name = cstr;
        } else {
            RegisterValue nv = registers[pc->call_args[0]];
            if (IS_PTR(nv)) {
                auto* h = static_cast<ObjHeader*>(UNBOX_PTR(nv));
                if (h && h->type_id == TYPE_STRING)
                    lymar_func_name = ((LmStringHeader*)h)->data;
            }
        }
    }
    if (lymar_func_name.empty()) {
        std::cerr << "[ffi] callback_create: missing or empty function name\n";
        registers[pc->dst] = VAL_NIL;
        return;
    }
    auto& functions = LIR::LIRFunctionManager::getInstance();
    if (!functions.hasFunction(lymar_func_name)) {
        std::cerr << "[ffi] callback_create: function '" << lymar_func_name
                  << "' is not registered\n";
        registers[pc->dst] = VAL_NIL;
        return;
    }

    std::vector<lymarrt_type> arg_types;
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
                    lymarrt_type type;
                    if (!ffi_type_id_to_lymarrt(type_id, false, type)) {
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
    const size_t expected_args = functions.getFunction(lymar_func_name)->getParameters().size();
    if (arg_types.size() != expected_args) {
        std::cerr << "[ffi] callback_create: signature for '" << lymar_func_name
                  << "' declares " << arg_types.size() << " native arguments but function expects "
                  << expected_args << '\n';
        registers[pc->dst] = VAL_NIL;
        return;
    }

    lymarrt_type ret_type;
    int64_t rid = as_i64(registers[pc->call_args[2]]);
    if (!ffi_type_id_to_lymarrt(rid, true, ret_type)) {
        std::cerr << "[ffi] callback_create: invalid return type id " << rid << '\n';
        registers[pc->dst] = VAL_NIL;
        return;
    }

    VmCallbackUserData* udata = new VmCallbackUserData{this, lymar_func_name};
    int64_t id = lymarrt_callback_create(
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
    owned_callbacks.insert(id);
    registers[pc->dst] = BOX_INT(id);
}

void RegisterVM::revoke_callbacks() {
    while (!owned_callbacks.empty()) {
        int64_t id = *owned_callbacks.begin();
        owned_callbacks.erase(id);
        auto* data = static_cast<VmCallbackUserData*>(lymarrt_callback_get_userdata(id));
        lymarrt_callback_destroy(id);
        delete data;
    }
}

void RegisterVM::execute_extern_unregister_callback(const LIR::LIR_Inst* pc) {
    int64_t id = as_i64(registers[pc->a]);
    if (!owned_callbacks.erase(id)) return;
    void* udata = lymarrt_callback_get_userdata(id);
    if (udata) {
        delete static_cast<VmCallbackUserData*>(udata);
    }
    lymarrt_callback_destroy(id);
}

void RegisterVM::execute_extern_get_callback_ptr(const LIR::LIR_Inst* pc) {
    int64_t id = as_i64(registers[pc->a]);
    void* code_ptr = lymarrt_callback_get_ptr(id);
    if (code_ptr) {
        RegisterValue val = lm_alloc_foreign_ptr(code_ptr);
        registers[pc->dst] = val;
        register_native_allocation(registers[pc->dst]);
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
        int64_t val; std::memcpy(&val, &it->second[off], 8); registers[pc->dst] = make_i64(val);
    } else registers[pc->dst] = BOX_INT(0);
}
void RegisterVM::execute_extern_vm_save(const LIR::LIR_Inst* pc) { registers[pc->dst] = VAL_NIL; }
void RegisterVM::execute_extern_vm_restore(const LIR::LIR_Inst* pc) {}
void RegisterVM::execute_extern_calc_struct_layout(const LIR::LIR_Inst* pc) { registers[pc->dst] = VAL_NIL; }
void RegisterVM::execute_extern_get_abi_info(const LIR::LIR_Inst* pc) { registers[pc->dst] = VAL_NIL; }

// Entry point for native shared modules (emit_shared_module): the module's
// generated code cannot reach the interpreter's register file, so it forwards
// each ffi intrinsic through the host Api helper table. This reconstructs a
// synthetic LIR_Inst over a scratch register span and runs the exact same
// execute_* implementation the interpreter uses — identical semantics for
// alloc/free/load/store, pointer arithmetic, dynamic linking, and foreign
// calls, including lymarrt marshaling and struct layouts.
//
// Contract (emitter -> here): `op` is one of alloc, free, resize, load,
// store, copy, fill, compare, ptr_add, ptr_sub, ptr_diff, ptr_align,
// ptr_is_aligned, lib_load, lib_unload, lib_symbol, foreign_call,
// foreign_direct. `args` holds operand values in LIR call_args order; load
// and store append the type-code immediate, foreign_direct appends the LIR
// result type as a trailing integer.
RegisterValue RegisterVM::native_ffi_call(const char* op,
                                          const std::vector<RegisterValue>& args) {
    auto to_op = [](const char* name) -> LIR::LIR_Op {
        const std::string n(name);
        if (n == "alloc") return LIR::LIR_Op::MemoryAlloc;
        if (n == "free") return LIR::LIR_Op::MemoryFree;
        if (n == "resize") return LIR::LIR_Op::MemoryResize;
        if (n == "load") return LIR::LIR_Op::MemoryLoad;
        if (n == "store") return LIR::LIR_Op::MemoryStore;
        if (n == "copy") return LIR::LIR_Op::MemoryCopy;
        if (n == "fill") return LIR::LIR_Op::MemoryFill;
        if (n == "compare") return LIR::LIR_Op::MemoryCompare;
        if (n == "ptr_add") return LIR::LIR_Op::PtrAdd;
        if (n == "ptr_sub") return LIR::LIR_Op::PtrSub;
        if (n == "ptr_diff") return LIR::LIR_Op::PtrDiff;
        if (n == "ptr_align") return LIR::LIR_Op::PtrAlign;
        if (n == "ptr_is_aligned") return LIR::LIR_Op::PtrIsAligned;
        if (n == "lib_load") return LIR::LIR_Op::LibraryLoad;
        if (n == "lib_unload") return LIR::LIR_Op::LibraryUnload;
        if (n == "lib_symbol") return LIR::LIR_Op::LibrarySymbol;
        if (n == "foreign_call") return LIR::LIR_Op::ForeignCall;
        if (n == "foreign_direct") return LIR::LIR_Op::ForeignCall;
        throw std::runtime_error(std::string("native_ffi_call: unknown op '") + name);
    };
    const std::string name(op);
    const bool is_load = name == "load" || name == "store";
    const bool is_foreign = name == "foreign_call" || name == "foreign_direct";
    const size_t meta = is_load ? 1 : (is_foreign && name == "foreign_direct" ? 1 : 0);
    if (args.size() < meta) throw std::runtime_error("native_ffi_call: too few arguments");

    std::vector<RegisterValue> buf(args.size() + 1, VAL_NIL);
    for (size_t i = 0; i < args.size(); ++i) buf[i] = args[i];
    const LIR::Reg RDST = static_cast<LIR::Reg>(args.size());

    LIR::LIR_Inst pc;
    pc.op = to_op(op);
    pc.dst = RDST;
    pc.result_type = LIR::Type::I64;
    if (is_foreign && name == "foreign_direct" && !args.empty())
        pc.result_type = static_cast<LIR::Type>(as_i64(args.back()));
    if (is_foreign) pc.func_name = name == "foreign_call" ? "std.ffi.foreign_call" : "std.ffi.foreign_call_direct";
    if (is_load) pc.imm = static_cast<LIR::Imm>(as_i64(args.back()));
    const size_t operands = args.size() - meta;
    if (operands > 0) { pc.a = 0; pc.call_args.push_back(0); }
    if (operands > 1) { pc.b = 1; pc.call_args.push_back(1); }
    for (size_t i = 2; i < operands; ++i) pc.call_args.push_back(static_cast<LIR::Reg>(i));

    // Temporarily point the register span at the scratch buffer so the shared
    // execute_* implementations read operand values exactly as the
    // interpreter would. Single-threaded host call; always restored.
    RegisterValue* saved_data = registers.data_;
    size_t saved_size = registers.size_;
    registers.data_ = buf.data();
    registers.size_ = buf.size();
    RegisterValue result = VAL_NIL;
    try {
        switch (pc.op) {
            case LIR::LIR_Op::MemoryAlloc: execute_memory_alloc(&pc); break;
            case LIR::LIR_Op::MemoryFree: execute_memory_free(&pc); break;
            case LIR::LIR_Op::MemoryResize: execute_memory_realloc(&pc); break;
            case LIR::LIR_Op::MemoryLoad: execute_memory_load(&pc); break;
            case LIR::LIR_Op::MemoryStore: execute_memory_store(&pc); break;
            case LIR::LIR_Op::MemoryCopy: execute_memory_copy(&pc); break;
            case LIR::LIR_Op::MemoryFill: execute_memory_fill(&pc); break;
            case LIR::LIR_Op::MemoryCompare: execute_memory_compare(&pc); break;
            case LIR::LIR_Op::PtrAdd: execute_ptr_add(&pc); break;
            case LIR::LIR_Op::PtrSub: execute_ptr_sub(&pc); break;
            case LIR::LIR_Op::PtrDiff: execute_ptr_diff(&pc); break;
            case LIR::LIR_Op::PtrAlign: execute_ptr_align(&pc); break;
            case LIR::LIR_Op::PtrIsAligned: execute_ptr_is_aligned(&pc); break;
            case LIR::LIR_Op::LibraryLoad: execute_extern_library_load(&pc); break;
            case LIR::LIR_Op::LibraryUnload: execute_extern_library_unload(&pc); break;
            case LIR::LIR_Op::LibrarySymbol: execute_extern_library_get_symbol(&pc); break;
            case LIR::LIR_Op::ForeignCall: execute_extern_call_function(&pc); break;
            default: break;
        }
        result = registers[RDST];
    } catch (...) {
        registers.data_ = saved_data;
        registers.size_ = saved_size;
        throw;
    }
    registers.data_ = saved_data;
    registers.size_ = saved_size;
    return result;
}

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

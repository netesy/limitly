#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_value.h"
#include <cstdlib>
#include <cstring>
#include <memory>
#include <unordered_map>
#include <mutex>
#include <functional>
#include <ffi.h>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

namespace {
    std::mutex g_library_mutex;
    std::unordered_map<uintptr_t, std::string> g_libraries;
    std::mutex g_callback_mutex;
    std::unordered_map<int64_t, void*> g_callbacks;
    int64_t g_next_callback_id = 0;
    std::mutex g_callframe_mutex;
    std::unordered_map<uint64_t, std::vector<RegisterValue>> g_callframe_registers;
    std::unordered_map<uint64_t, std::vector<uint8_t>> g_callframe_stack;
    uint64_t g_next_callframe_id = 0;

    LIR::Reg arg_reg(const LIR::LIR_Inst* pc, size_t index, LIR::Reg fallback) {
        return index < pc->call_args.size() ? pc->call_args[index] : fallback;
    }

    const char* get_cstring_from_value(RegisterValue value) {
        if (!IS_PTR(value)) return nullptr;
        auto* header = static_cast<ObjHeader*>(UNBOX_PTR(value));
        if (header->type_id == TYPE_BOX && static_cast<LmBox*>(static_cast<void*>(header))->type == LM_BOX_STRING) {
            return static_cast<const char*>(static_cast<LmBox*>(static_cast<void*>(header))->value.as_ptr);
        }
        return nullptr;
    }

    ffi_type* lir_type_to_ffi_type(LIR::Type type) {
        switch (type) {
            case LIR::Type::I8: return &ffi_type_sint8;
            case LIR::Type::U8: return &ffi_type_uint8;
            case LIR::Type::I16: return &ffi_type_sint16;
            case LIR::Type::U16: return &ffi_type_uint16;
            case LIR::Type::I32: return &ffi_type_sint32;
            case LIR::Type::U32: return &ffi_type_uint32;
            case LIR::Type::I64: return &ffi_type_sint64;
            case LIR::Type::U64: return &ffi_type_uint64;
            case LIR::Type::F32: return &ffi_type_float;
            case LIR::Type::F64: return &ffi_type_double;
            case LIR::Type::Bool: return &ffi_type_uint8;
            case LIR::Type::Ptr: return &ffi_type_pointer;
            case LIR::Type::Void: return &ffi_type_void;
            default: return &ffi_type_void;
        }
    }

    void* value_to_ptr(RegisterValue val) {
        if (IS_PTR(val)) {
            auto* header = static_cast<ObjHeader*>(UNBOX_PTR(val));
            if (header->type_id == TYPE_FOREIGN_PTR) return ((ObjForeignPtr*)header)->ptr;
            return UNBOX_PTR(val);
        }
        if (is_integer(val)) return (void*)(uintptr_t)as_i64(val);
        return nullptr;
    }
}

void RegisterVM::execute_extern_library_load(const LIR::LIR_Inst* pc) {
    LIR::Reg path_reg = arg_reg(pc, 0, pc->a);
    const char* path = get_cstring_from_value(registers[path_reg]);
    if (!path) { registers[pc->dst] = VAL_NIL; return; }
    #ifdef _WIN32
    void* handle = static_cast<void*>(LoadLibraryA(path));
    #else
    void* handle = dlopen(path, RTLD_LAZY | RTLD_LOCAL);
    #endif
    if (!handle) { registers[pc->dst] = VAL_NIL; return; }
    std::lock_guard<std::mutex> lock(g_library_mutex);
    g_libraries[reinterpret_cast<uintptr_t>(handle)] = path;
    registers[pc->dst] = lm_alloc_foreign_ptr(handle);
}

void RegisterVM::execute_extern_library_unload(const LIR::LIR_Inst* pc) {
    void* handle = value_to_ptr(registers[pc->a]);
    if (handle) {
        #ifdef _WIN32
        FreeLibrary(static_cast<HMODULE>(handle));
        #else
        dlclose(handle);
        #endif
        std::lock_guard<std::mutex> lock(g_library_mutex);
        g_libraries.erase(reinterpret_cast<uintptr_t>(handle));
    }
}

void RegisterVM::execute_extern_library_get_symbol(const LIR::LIR_Inst* pc) {
    LIR::Reg handle_reg = arg_reg(pc, 0, pc->a);
    LIR::Reg symbol_reg = arg_reg(pc, 1, pc->b);
    void* handle = value_to_ptr(registers[handle_reg]);
    if (!handle) { registers[pc->dst] = VAL_NIL; return; }
    const char* symbol = get_cstring_from_value(registers[symbol_reg]);
    if (!symbol) { registers[pc->dst] = VAL_NIL; return; }
    #ifdef _WIN32
    void* ptr = reinterpret_cast<void*>(GetProcAddress(static_cast<HMODULE>(handle), symbol));
    #else
    void* ptr = dlsym(handle, symbol);
    #endif
    registers[pc->dst] = ptr ? lm_alloc_foreign_ptr(ptr) : VAL_NIL;
}

void RegisterVM::execute_extern_call_function(const LIR::LIR_Inst* pc) {
    RegisterValue func_ptr_val = registers[arg_reg(pc, 0, pc->a)];
    void* func_ptr = value_to_ptr(func_ptr_val);
    if (!func_ptr) { registers[pc->dst] = VAL_NIL; return; }
    
    LIR::Type ret_type = pc->result_type;
    std::vector<LIR::Reg> arg_regs = pc->call_args;
    size_t arg_start = 0;
    if (pc->op == LIR::LIR_Op::ForeignCall || pc->op == LIR::LIR_Op::FFICCallExecute) arg_start = 1;
    size_t num_args = (arg_regs.size() > arg_start) ? (arg_regs.size() - arg_start) : 0;
    
    std::vector<LIR::Type> resolved_arg_types;
    for (size_t i = arg_start; i < arg_regs.size(); ++i) {
        if (i < pc->call_arg_types.size() && pc->call_arg_types[i] != LIR::Type::Void) resolved_arg_types.push_back(pc->call_arg_types[i]);
        else {
            RegisterValue val = registers[arg_regs[i]];
            if (is_float(val)) resolved_arg_types.push_back(LIR::Type::F64);
            else if (IS_PTR(val)) resolved_arg_types.push_back(LIR::Type::Ptr);
            else resolved_arg_types.push_back(LIR::Type::I64);
        }
    }

    std::vector<ffi_type*> ffi_arg_types(num_args);
    std::vector<void*> ffi_arg_values(num_args);
    std::vector<uint64_t> arg_storage(num_args);

    for (size_t i = 0; i < num_args; ++i) {
        LIR::Type type = resolved_arg_types[i];
        ffi_arg_types[i] = lir_type_to_ffi_type(type);
        RegisterValue val = registers[arg_regs[i + arg_start]];
        switch (type) {
            case LIR::Type::I8:  *(int8_t*)&arg_storage[i] = (int8_t)to_int(val); break;
            case LIR::Type::U8:  *(uint8_t*)&arg_storage[i] = (uint8_t)to_int(val); break;
            case LIR::Type::I16: *(int16_t*)&arg_storage[i] = (int16_t)to_int(val); break;
            case LIR::Type::U16: *(uint16_t*)&arg_storage[i] = (uint16_t)to_int(val); break;
            case LIR::Type::I32: *(int32_t*)&arg_storage[i] = (int32_t)to_int(val); break;
            case LIR::Type::U32: *(uint32_t*)&arg_storage[i] = (uint32_t)to_int(val); break;
            case LIR::Type::I64: *(int64_t*)&arg_storage[i] = to_int(val); break;
            case LIR::Type::U64: *(uint64_t*)&arg_storage[i] = (uint64_t)to_int(val); break;
            case LIR::Type::F32: *(float*)&arg_storage[i] = (float)to_float(val); break;
            case LIR::Type::F64: *(double*)&arg_storage[i] = to_float(val); break;
            case LIR::Type::Bool: *(uint8_t*)&arg_storage[i] = (uint8_t)(to_int(val) != 0); break;
            case LIR::Type::Ptr: {
                void* p = value_to_ptr(val);
                const char* cstr = get_cstring_from_value(val);
                if (cstr) p = (void*)cstr;
                *(void**)&arg_storage[i] = p;
                break;
            }
            default: arg_storage[i] = 0; break;
        }
        ffi_arg_values[i] = &arg_storage[i];
    }

    ffi_cif cif;
    ffi_type* ffi_ret_type = lir_type_to_ffi_type(ret_type);
    if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, num_args, ffi_ret_type, ffi_arg_types.data()) == FFI_OK) {
        uint64_t result_storage = 0;
        ffi_call(&cif, FFI_FN(func_ptr), &result_storage, ffi_arg_values.data());
        switch (ret_type) {
            case LIR::Type::I8:  registers[pc->dst] = BOX_INT((int64_t)*(int8_t*)&result_storage); break;
            case LIR::Type::U8:  registers[pc->dst] = BOX_INT((int64_t)*(uint8_t*)&result_storage); break;
            case LIR::Type::I16: registers[pc->dst] = BOX_INT((int64_t)*(int16_t*)&result_storage); break;
            case LIR::Type::U16: registers[pc->dst] = BOX_INT((int64_t)*(uint16_t*)&result_storage); break;
            case LIR::Type::I32: registers[pc->dst] = BOX_INT((int64_t)*(int32_t*)&result_storage); break;
            case LIR::Type::U32: registers[pc->dst] = BOX_INT((int64_t)*(uint32_t*)&result_storage); break;
            case LIR::Type::I64: registers[pc->dst] = BOX_INT(*(int64_t*)&result_storage); break;
            case LIR::Type::U64: registers[pc->dst] = BOX_INT((int64_t)*(uint64_t*)&result_storage); break;
            case LIR::Type::F32: registers[pc->dst] = make_float((double)*(float*)&result_storage); break;
            case LIR::Type::F64: registers[pc->dst] = make_float(*(double*)&result_storage); break;
            case LIR::Type::Bool: registers[pc->dst] = (*(uint8_t*)&result_storage) ? VAL_TRUE : VAL_FALSE; break;
            case LIR::Type::Ptr:  registers[pc->dst] = lm_alloc_foreign_ptr(*(void**)&result_storage); break;
            default: registers[pc->dst] = VAL_NIL; break;
        }
    } else registers[pc->dst] = VAL_NIL;
}

void RegisterVM::execute_extern_register_callback(const LIR::LIR_Inst* pc) {
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    registers[pc->dst] = BOX_INT(g_next_callback_id++);
}
void RegisterVM::execute_extern_unregister_callback(const LIR::LIR_Inst* pc) {
    int64_t id = to_int(registers[pc->a]);
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    auto it = g_callbacks.find(id);
    if (it != g_callbacks.end()) { std::free(it->second); g_callbacks.erase(it); }
}
void RegisterVM::execute_extern_get_callback_ptr(const LIR::LIR_Inst* pc) {
    int64_t id = to_int(registers[pc->a]);
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    auto it = g_callbacks.find(id);
    if (it != g_callbacks.end()) registers[pc->dst] = lm_alloc_foreign_ptr(it->second);
    else registers[pc->dst] = VAL_NIL;
}

void RegisterVM::execute_extern_ccall_frame_create(const LIR::LIR_Inst* pc) {
    int64_t rc = to_int(registers[pc->a]); int64_t ss = to_int(registers[pc->b]);
    if (rc < 0 || ss < 0) { registers[pc->dst] = VAL_NIL; return; }
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    uint64_t id = g_next_callframe_id++;
    g_callframe_registers[id] = std::vector<RegisterValue>(rc, VAL_NIL);
    g_callframe_stack[id] = std::vector<uint8_t>(ss, 0);
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(id));
}
void RegisterVM::execute_extern_ccall_frame_destroy(const LIR::LIR_Inst* pc) {
    int64_t id = to_int(registers[pc->a]);
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    g_callframe_registers.erase(id); g_callframe_stack.erase(id);
}
void RegisterVM::execute_extern_ccall_frame_set_reg(const LIR::LIR_Inst* pc) {
    int64_t id = to_int(registers[pc->dst]); int64_t idx = to_int(registers[pc->a]);
    RegisterValue val = registers[pc->b];
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    auto it = g_callframe_registers.find(id);
    if (it != g_callframe_registers.end() && idx >= 0 && idx < (int64_t)it->second.size()) it->second[idx] = val;
}
void RegisterVM::execute_extern_ccall_frame_get_reg(const LIR::LIR_Inst* pc) {
    int64_t id = to_int(registers[pc->a]); int64_t idx = to_int(registers[pc->b]);
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    auto it = g_callframe_registers.find(id);
    if (it != g_callframe_registers.end() && idx >= 0 && idx < (int64_t)it->second.size()) registers[pc->dst] = it->second[idx];
    else registers[pc->dst] = VAL_NIL;
}
void RegisterVM::execute_extern_ccall_frame_set_stack_arg(const LIR::LIR_Inst* pc) {
    int64_t id = to_int(registers[pc->dst]); int64_t off = to_int(registers[pc->a]); int64_t val = to_int(registers[pc->b]);
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    auto it = g_callframe_stack.find(id);
    if (it != g_callframe_stack.end() && off >= 0 && off + 8 <= (int64_t)it->second.size()) std::memcpy(&it->second[off], &val, 8);
}
void RegisterVM::execute_extern_ccall_frame_get_stack_arg(const LIR::LIR_Inst* pc) {
    int64_t id = to_int(registers[pc->a]); int64_t off = to_int(registers[pc->b]);
    std::lock_guard<std::mutex> lock(g_callback_mutex);
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
        case LIR::LIR_Op::LibraryLoad:
        case LIR::LIR_Op::FFILibraryLoad: execute_extern_library_load(pc); break;
        case LIR::LIR_Op::LibraryUnload:
        case LIR::LIR_Op::FFILibraryUnload: execute_extern_library_unload(pc); break;
        case LIR::LIR_Op::LibrarySymbol:
        case LIR::LIR_Op::FFILibraryGetSymbol: execute_extern_library_get_symbol(pc); break;
        case LIR::LIR_Op::ForeignCall:
        case LIR::LIR_Op::ForeignCallDirect:
        case LIR::LIR_Op::FFICallPtr:
        case LIR::LIR_Op::FFICallPtr0:
        case LIR::LIR_Op::FFICallPtr1:
        case LIR::LIR_Op::FFICallPtr2:
        case LIR::LIR_Op::FFICallPtr3:
        case LIR::LIR_Op::FFICallPtr4:
        case LIR::LIR_Op::FFICallPtr5:
        case LIR::LIR_Op::FFICCallExecute: execute_extern_call_function(pc); break;
        case LIR::LIR_Op::FFIRegisterCallback: execute_extern_register_callback(pc); break;
        case LIR::LIR_Op::FFIUnregisterCallback: execute_extern_unregister_callback(pc); break;
        case LIR::LIR_Op::FFIGetCallbackPtr: execute_extern_get_callback_ptr(pc); break;
        case LIR::LIR_Op::FFICCallFrameCreate: execute_extern_ccall_frame_create(pc); break;
        case LIR::LIR_Op::FFICCallFrameDestroy: execute_extern_ccall_frame_destroy(pc); break;
        case LIR::LIR_Op::FFICCallFrameSetReg: execute_extern_ccall_frame_set_reg(pc); break;
        case LIR::LIR_Op::FFICCallFrameGetReg: execute_extern_ccall_frame_get_reg(pc); break;
        case LIR::LIR_Op::FFICCallFrameSetStackArg: execute_extern_ccall_frame_set_stack_arg(pc); break;
        case LIR::LIR_Op::FFICCallFrameGetStackArg: execute_extern_ccall_frame_get_stack_arg(pc); break;
        case LIR::LIR_Op::FFIVMSave: execute_extern_vm_save(pc); break;
        case LIR::LIR_Op::FFIVMRestore: execute_extern_vm_restore(pc); break;
        case LIR::LIR_Op::FFICalcStructLayout: execute_extern_calc_struct_layout(pc); break;
        case LIR::LIR_Op::FFIGetABIInfo: execute_extern_get_abi_info(pc); break;
        default: break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM

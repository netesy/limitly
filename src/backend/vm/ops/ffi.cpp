#include "../register.hh"
#include "../../../runtime/runtime.h"
#include "../../../runtime/runtime_value.h"
#include <cstdlib>
#include <cstring>
#include <memory>
#include <unordered_map>
#include <mutex>
#include <functional>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

// External C library management
namespace {
    std::mutex g_library_mutex;
    std::unordered_map<uintptr_t, std::string> g_libraries;

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
}

// Library loading - true external C interop
void RegisterVM::execute_extern_library_load(const LIR::LIR_Inst* pc) {
    LIR::Reg path_reg = arg_reg(pc, 0, pc->a);
    const char* path = get_cstring_from_value(registers[path_reg]);
    if (!path) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    #ifdef _WIN32
    void* handle = static_cast<void*>(LoadLibraryA(path));
    #else
    void* handle = dlopen(path, RTLD_LAZY | RTLD_LOCAL);
    #endif
    
    if (!handle) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    std::lock_guard<std::mutex> lock(g_library_mutex);
    g_libraries[reinterpret_cast<uintptr_t>(handle)] = path;
    registers[pc->dst] = BOX_PTR(handle);
}

// Library unloading - true external C interop
void RegisterVM::execute_extern_library_unload(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        return;
    }
    
    void* handle = UNBOX_PTR(registers[pc->a]);
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

// Get symbol from library - true external C interop
void RegisterVM::execute_extern_library_get_symbol(const LIR::LIR_Inst* pc) {
    LIR::Reg handle_reg = arg_reg(pc, 0, pc->a);
    LIR::Reg symbol_reg = arg_reg(pc, 1, pc->b);
    
    if (!IS_PTR(registers[handle_reg])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    const char* symbol = get_cstring_from_value(registers[symbol_reg]);
    if (!symbol) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* handle = UNBOX_PTR(registers[handle_reg]);
    
    #ifdef _WIN32
    void* ptr = reinterpret_cast<void*>(GetProcAddress(static_cast<HMODULE>(handle), symbol));
    #else
    void* ptr = dlsym(handle, symbol);
    #endif
    
    registers[pc->dst] = ptr ? BOX_PTR(ptr) : VAL_NIL;
}

// Foreign function call - true external C interop
void RegisterVM::execute_extern_call_function(const LIR::LIR_Inst* pc) {
    RegisterValue func_ptr_val = registers[arg_reg(pc, 0, pc->a)];
    if (!IS_PTR(func_ptr_val)) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* func_ptr = UNBOX_PTR(func_ptr_val);
    
    // TODO: Call with proper calling convention (requires platform-specific code)
    // For now, placeholder
    registers[pc->dst] = BOX_INT(0);
}

// Callback registration - true external C interop
namespace {
    std::mutex g_callback_mutex;
    std::unordered_map<int64_t, void*> g_callbacks;
    int64_t g_next_callback_id = 0;
}

void RegisterVM::execute_extern_register_callback(const LIR::LIR_Inst* pc) {
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    int64_t callback_id = g_next_callback_id++;
    
    // TODO: Create trampoline for callback (requires platform-specific assembly)
    // For now, just register the ID
    registers[pc->dst] = BOX_INT(callback_id);
}

// Callback unregistration - true external C interop
void RegisterVM::execute_extern_unregister_callback(const LIR::LIR_Inst* pc) {
    int64_t callback_id = to_int(registers[pc->a]);
    
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    auto it = g_callbacks.find(callback_id);
    if (it != g_callbacks.end()) {
        // Free trampoline memory
        std::free(it->second);
        g_callbacks.erase(it);
    }
}

// Get callback pointer - true external C interop
void RegisterVM::execute_extern_get_callback_ptr(const LIR::LIR_Inst* pc) {
    int64_t callback_id = to_int(registers[pc->a]);
    
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    auto it = g_callbacks.find(callback_id);
    if (it != g_callbacks.end()) {
        registers[pc->dst] = BOX_PTR(it->second);
    } else {
        registers[pc->dst] = VAL_NIL;
    }
}

// C call frame management - supporting infrastructure for C interop
namespace {
    std::mutex g_callframe_mutex;
    std::unordered_map<uint64_t, std::vector<RegisterValue>> g_callframe_registers;
    std::unordered_map<uint64_t, std::vector<uint8_t>> g_callframe_stack;
    uint64_t g_next_callframe_id = 0;
}

void RegisterVM::execute_extern_ccall_frame_create(const LIR::LIR_Inst* pc) {
    int64_t register_count = to_int(registers[pc->a]);
    int64_t stack_arg_size = to_int(registers[pc->b]);
    
    if (register_count < 0 || stack_arg_size < 0) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    uint64_t callframe_id = g_next_callframe_id++;
    
    g_callframe_registers[callframe_id] = std::vector<RegisterValue>(register_count, VAL_NIL);
    g_callframe_stack[callframe_id] = std::vector<uint8_t>(stack_arg_size, 0);
    
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(callframe_id));
}

void RegisterVM::execute_extern_ccall_frame_destroy(const LIR::LIR_Inst* pc) {
    int64_t callframe_id = to_int(registers[pc->a]);
    
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    g_callframe_registers.erase(callframe_id);
    g_callframe_stack.erase(callframe_id);
}

void RegisterVM::execute_extern_ccall_frame_set_reg(const LIR::LIR_Inst* pc) {
    int64_t callframe_id = to_int(registers[pc->dst]);
    int64_t reg_index = to_int(registers[pc->a]);
    RegisterValue value = registers[pc->b];
    
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    auto it = g_callframe_registers.find(callframe_id);
    if (it != g_callframe_registers.end() && reg_index >= 0 && reg_index < static_cast<int64_t>(it->second.size())) {
        it->second[reg_index] = value;
    }
}

void RegisterVM::execute_extern_ccall_frame_get_reg(const LIR::LIR_Inst* pc) {
    int64_t callframe_id = to_int(registers[pc->a]);
    int64_t reg_index = to_int(registers[pc->b]);
    
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    auto it = g_callframe_registers.find(callframe_id);
    if (it != g_callframe_registers.end() && reg_index >= 0 && reg_index < static_cast<int64_t>(it->second.size())) {
        registers[pc->dst] = it->second[reg_index];
    } else {
        registers[pc->dst] = VAL_NIL;
    }
}

void RegisterVM::execute_extern_ccall_frame_set_stack_arg(const LIR::LIR_Inst* pc) {
    int64_t callframe_id = to_int(registers[pc->dst]);
    int64_t offset = to_int(registers[pc->a]);
    int64_t value = to_int(registers[pc->b]);
    
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    auto it = g_callframe_stack.find(callframe_id);
    if (it != g_callframe_stack.end() && offset >= 0 && offset + 8 <= static_cast<int64_t>(it->second.size())) {
        std::memcpy(&it->second[offset], &value, 8);
    }
}

void RegisterVM::execute_extern_ccall_frame_get_stack_arg(const LIR::LIR_Inst* pc) {
    int64_t callframe_id = to_int(registers[pc->a]);
    int64_t offset = to_int(registers[pc->b]);
    
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    auto it = g_callframe_stack.find(callframe_id);
    if (it != g_callframe_stack.end() && offset >= 0 && offset + 8 <= static_cast<int64_t>(it->second.size())) {
        int64_t value;
        std::memcpy(&value, &it->second[offset], 8);
        registers[pc->dst] = BOX_INT(value);
    } else {
        registers[pc->dst] = BOX_INT(0);
    }
}

// VM state management for C boundary crossing
void RegisterVM::execute_extern_vm_save(const LIR::LIR_Inst* pc) {
    // Save all VM registers to a list
    // TODO: Implement when needed for C callbacks
    registers[pc->dst] = VAL_NIL;
}

void RegisterVM::execute_extern_vm_restore(const LIR::LIR_Inst* pc) {
    // Restore VM registers from a list
    // TODO: Implement when needed for C callbacks
}

// Struct layout calculation
void RegisterVM::execute_extern_calc_struct_layout(const LIR::LIR_Inst* pc) {
    // Calculate struct layout with padding
    // TODO: Implement for struct interop
    registers[pc->dst] = VAL_NIL;
}

// ABI information query
void RegisterVM::execute_extern_get_abi_info(const LIR::LIR_Inst* pc) {
    // Get platform ABI information
    // TODO: Implement for ABI queries
    registers[pc->dst] = VAL_NIL;
}

// Main FFI dispatcher - handles only true external C interop
// Memory operations, data construction are in separate dispatchers
void RegisterVM::execute_ffi(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        // Library loading/unloading - true C interop
        case LIR::LIR_Op::FFILibraryLoad:
            execute_extern_library_load(pc);
            break;
        case LIR::LIR_Op::FFILibraryUnload:
            execute_extern_library_unload(pc);
            break;
        case LIR::LIR_Op::FFILibraryGetSymbol:
            execute_extern_library_get_symbol(pc);
            break;
        
        // Foreign function calls - true C interop
        case LIR::LIR_Op::ForeignCall:
        case LIR::LIR_Op::FFICallPtr:
        case LIR::LIR_Op::FFICallPtr0:
        case LIR::LIR_Op::FFICallPtr1:
        case LIR::LIR_Op::FFICallPtr2:
        case LIR::LIR_Op::FFICallPtr3:
        case LIR::LIR_Op::FFICallPtr4:
        case LIR::LIR_Op::FFICallPtr5:
            execute_extern_call_function(pc);
            break;
        
        // Callback support - true C interop
        case LIR::LIR_Op::FFIRegisterCallback:
            execute_extern_register_callback(pc);
            break;
        case LIR::LIR_Op::FFIUnregisterCallback:
            execute_extern_unregister_callback(pc);
            break;
        case LIR::LIR_Op::FFIGetCallbackPtr:
            execute_extern_get_callback_ptr(pc);
            break;
        
        // Call frame management - supporting infrastructure
        case LIR::LIR_Op::FFICCallFrameCreate:
            execute_extern_ccall_frame_create(pc);
            break;
        case LIR::LIR_Op::FFICCallFrameDestroy:
            execute_extern_ccall_frame_destroy(pc);
            break;
        case LIR::LIR_Op::FFICCallFrameSetReg:
            execute_extern_ccall_frame_set_reg(pc);
            break;
        case LIR::LIR_Op::FFICCallFrameGetReg:
            execute_extern_ccall_frame_get_reg(pc);
            break;
        case LIR::LIR_Op::FFICCallFrameSetStackArg:
            execute_extern_ccall_frame_set_stack_arg(pc);
            break;
        case LIR::LIR_Op::FFICCallFrameGetStackArg:
            execute_extern_ccall_frame_get_stack_arg(pc);
            break;
        
        // VM state management - supporting infrastructure
        case LIR::LIR_Op::FFIVMSave:
            execute_extern_vm_save(pc);
            break;
        case LIR::LIR_Op::FFIVMRestore:
            execute_extern_vm_restore(pc);
            break;
        case LIR::LIR_Op::FFICCallExecute:
            execute_extern_call_function(pc);
            break;
        
        // ABI/struct support - supporting infrastructure
        case LIR::LIR_Op::FFICalcStructLayout:
            execute_extern_calc_struct_layout(pc);
            break;
        case LIR::LIR_Op::FFIGetABIInfo:
            execute_extern_get_abi_info(pc);
            break;
        
        default:
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM

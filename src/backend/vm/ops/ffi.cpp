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

// FFI memory allocation tracking
namespace {
    std::mutex g_ffi_mutex;
    std::unordered_map<uintptr_t, size_t> g_ffi_allocations;

    LIR::Reg arg_reg(const LIR::LIR_Inst* pc, size_t index, LIR::Reg fallback) {
        return index < pc->call_args.size() ? pc->call_args[index] : fallback;
    }

    const char* boxed_c_string(RegisterValue value) {
        if (!IS_PTR(value)) return nullptr;
        auto* header = static_cast<ObjHeader*>(UNBOX_PTR(value));
        if (header->type_id == TYPE_BOX && static_cast<LmBox*>(static_cast<void*>(header))->type == LM_BOX_STRING) {
            return static_cast<const char*>(static_cast<LmBox*>(static_cast<void*>(header))->value.as_ptr);
        }
        return nullptr;
    }
}

// Memory allocation/deallocation
void RegisterVM::execute_ffi_alloc(const LIR::LIR_Inst* pc) {
    int64_t size = to_int(registers[arg_reg(pc, 0, pc->a)]);
    if (size < 0) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* ptr = std::malloc(size);
    if (ptr) {
        std::lock_guard<std::mutex> lock(g_ffi_mutex);
        g_ffi_allocations[reinterpret_cast<uintptr_t>(ptr)] = size;
        registers[pc->dst] = BOX_PTR(ptr);
    } else {
        registers[pc->dst] = VAL_NIL;
    }
}

void RegisterVM::execute_ffi_free(const LIR::LIR_Inst* pc) {
    LIR::Reg ptr_reg = arg_reg(pc, 0, pc->a);
    if (!IS_PTR(registers[ptr_reg])) {
        return;
    }
    
    void* ptr = UNBOX_PTR(registers[ptr_reg]);
    if (ptr) {
        std::lock_guard<std::mutex> lock(g_ffi_mutex);
        auto it = g_ffi_allocations.find(reinterpret_cast<uintptr_t>(ptr));
        if (it != g_ffi_allocations.end()) {
            g_ffi_allocations.erase(it);
            std::free(ptr);
        }
    }
}

void RegisterVM::execute_ffi_realloc(const LIR::LIR_Inst* pc) {
    LIR::Reg ptr_reg = arg_reg(pc, 0, pc->a);
    LIR::Reg size_reg = arg_reg(pc, 1, pc->b);
    if (!IS_PTR(registers[ptr_reg])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* ptr = UNBOX_PTR(registers[ptr_reg]);
    int64_t new_size = to_int(registers[size_reg]);
    
    if (new_size < 0) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void* new_ptr = std::realloc(ptr, new_size);
    if (new_ptr) {
        std::lock_guard<std::mutex> lock(g_ffi_mutex);
        g_ffi_allocations.erase(reinterpret_cast<uintptr_t>(ptr));
        g_ffi_allocations[reinterpret_cast<uintptr_t>(new_ptr)] = new_size;
        registers[pc->dst] = BOX_PTR(new_ptr);
    } else {
        registers[pc->dst] = VAL_NIL;
    }
}

// Memory operations
void RegisterVM::execute_ffi_memcpy(const LIR::LIR_Inst* pc) {
    LIR::Reg dest_reg = arg_reg(pc, 0, pc->a);
    LIR::Reg src_reg = arg_reg(pc, 1, pc->b);
    LIR::Reg size_reg = arg_reg(pc, 2, pc->dst);
    if (!IS_PTR(registers[dest_reg]) || !IS_PTR(registers[src_reg])) {
        return;
    }
    
    void* dest = UNBOX_PTR(registers[dest_reg]);
    void* src = UNBOX_PTR(registers[src_reg]);
    int64_t size = to_int(registers[size_reg]);
    
    if (dest && src && size > 0) {
        std::memcpy(dest, src, size);
    }
}

void RegisterVM::execute_ffi_memset(const LIR::LIR_Inst* pc) {
    LIR::Reg ptr_reg = arg_reg(pc, 0, pc->a);
    LIR::Reg value_reg = arg_reg(pc, 1, pc->b);
    LIR::Reg size_reg = arg_reg(pc, 2, pc->dst);
    if (!IS_PTR(registers[ptr_reg])) {
        return;
    }
    
    void* ptr = UNBOX_PTR(registers[ptr_reg]);
    int64_t value = to_int(registers[value_reg]);
    int64_t size = to_int(registers[size_reg]);
    
    if (ptr && size > 0) {
        std::memset(ptr, static_cast<int>(value), size);
    }
}

void RegisterVM::execute_ffi_memcmp(const LIR::LIR_Inst* pc) {
    LIR::Reg lhs_reg = arg_reg(pc, 0, pc->a);
    LIR::Reg rhs_reg = arg_reg(pc, 1, pc->b);
    LIR::Reg size_reg = arg_reg(pc, 2, pc->imm);
    if (!IS_PTR(registers[lhs_reg]) || !IS_PTR(registers[rhs_reg])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    
    void* ptr1 = UNBOX_PTR(registers[lhs_reg]);
    void* ptr2 = UNBOX_PTR(registers[rhs_reg]);
    int64_t size = to_int(registers[size_reg]);
    
    if (ptr1 && ptr2 && size > 0) {
        int result = std::memcmp(ptr1, ptr2, size);
        registers[pc->dst] = BOX_INT(result);
    } else {
        registers[pc->dst] = BOX_INT(0);
    }
}

// Pointer arithmetic
void RegisterVM::execute_ffi_add_ptr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    uintptr_t ptr = reinterpret_cast<uintptr_t>(UNBOX_PTR(registers[pc->a]));
    int64_t offset = to_int(registers[pc->b]);
    uintptr_t result = ptr + static_cast<uintptr_t>(offset);
    registers[pc->dst] = BOX_PTR(reinterpret_cast<void*>(result));
}

void RegisterVM::execute_ffi_sub_ptr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    uintptr_t ptr = reinterpret_cast<uintptr_t>(UNBOX_PTR(registers[pc->a]));
    int64_t offset = to_int(registers[pc->b]);
    uintptr_t result = ptr - static_cast<uintptr_t>(offset);
    registers[pc->dst] = BOX_PTR(reinterpret_cast<void*>(result));
}

void RegisterVM::execute_ffi_ptr_diff(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a]) || !IS_PTR(registers[pc->b])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    
    uintptr_t ptr1 = reinterpret_cast<uintptr_t>(UNBOX_PTR(registers[pc->a]));
    uintptr_t ptr2 = reinterpret_cast<uintptr_t>(UNBOX_PTR(registers[pc->b]));
    int64_t diff = static_cast<int64_t>(ptr1 - ptr2);
    registers[pc->dst] = BOX_INT(diff);
}

void RegisterVM::execute_ffi_align_ptr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    uintptr_t ptr = reinterpret_cast<uintptr_t>(UNBOX_PTR(registers[pc->a]));
    int64_t alignment = to_int(registers[pc->b]);
    
    if (alignment <= 0 || (alignment & (alignment - 1)) != 0) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    uintptr_t aligned = (ptr + alignment - 1) & ~(alignment - 1);
    registers[pc->dst] = BOX_PTR(reinterpret_cast<void*>(aligned));
}

void RegisterVM::execute_ffi_is_aligned(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_FALSE;
        return;
    }
    
    uintptr_t ptr = reinterpret_cast<uintptr_t>(UNBOX_PTR(registers[pc->a]));
    int64_t alignment = to_int(registers[pc->b]);
    
    if (alignment <= 0) {
        registers[pc->dst] = VAL_FALSE;
        return;
    }
    
    bool aligned = (ptr % static_cast<uintptr_t>(alignment)) == 0;
    registers[pc->dst] = aligned ? VAL_TRUE : VAL_FALSE;
}

// Load operations for primitive types
void RegisterVM::execute_ffi_load_int8(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    
    int8_t* ptr = static_cast<int8_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(*ptr));
}

void RegisterVM::execute_ffi_load_uint8(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    
    uint8_t* ptr = static_cast<uint8_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(*ptr));
}

void RegisterVM::execute_ffi_load_int16(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    
    int16_t* ptr = static_cast<int16_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(*ptr));
}

void RegisterVM::execute_ffi_load_uint16(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    
    uint16_t* ptr = static_cast<uint16_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(*ptr));
}

void RegisterVM::execute_ffi_load_int32(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    
    int32_t* ptr = static_cast<int32_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(*ptr));
}

void RegisterVM::execute_ffi_load_uint32(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    
    uint32_t* ptr = static_cast<uint32_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(*ptr));
}

void RegisterVM::execute_ffi_load_int64(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    
    int64_t* ptr = static_cast<int64_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(*ptr);
}

void RegisterVM::execute_ffi_load_uint64(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = BOX_INT(0);
        return;
    }
    
    uint64_t* ptr = static_cast<uint64_t*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_INT(static_cast<int64_t>(*ptr));
}

void RegisterVM::execute_ffi_load_float(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = make_float(0.0);
        return;
    }
    
    float* ptr = static_cast<float*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = make_float(static_cast<double>(*ptr));
}

void RegisterVM::execute_ffi_load_double(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = make_float(0.0);
        return;
    }
    
    double* ptr = static_cast<double*>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = make_float(*ptr);
}

void RegisterVM::execute_ffi_load_ptr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    void** ptr = static_cast<void**>(UNBOX_PTR(registers[pc->a]));
    registers[pc->dst] = BOX_PTR(*ptr);
}

// Store operations for primitive types
void RegisterVM::execute_ffi_store_int8(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) {
        return;
    }
    
    int8_t* ptr = static_cast<int8_t*>(UNBOX_PTR(registers[pc->dst]));
    int64_t value = to_int(registers[pc->a]);
    *ptr = static_cast<int8_t>(value);
}

void RegisterVM::execute_ffi_store_uint8(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) {
        return;
    }
    
    uint8_t* ptr = static_cast<uint8_t*>(UNBOX_PTR(registers[pc->dst]));
    int64_t value = to_int(registers[pc->a]);
    *ptr = static_cast<uint8_t>(value);
}

void RegisterVM::execute_ffi_store_int16(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) {
        return;
    }
    
    int16_t* ptr = static_cast<int16_t*>(UNBOX_PTR(registers[pc->dst]));
    int64_t value = to_int(registers[pc->a]);
    *ptr = static_cast<int16_t>(value);
}

void RegisterVM::execute_ffi_store_uint16(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) {
        return;
    }
    
    uint16_t* ptr = static_cast<uint16_t*>(UNBOX_PTR(registers[pc->dst]));
    int64_t value = to_int(registers[pc->a]);
    *ptr = static_cast<uint16_t>(value);
}

void RegisterVM::execute_ffi_store_int32(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) {
        return;
    }
    
    int32_t* ptr = static_cast<int32_t*>(UNBOX_PTR(registers[pc->dst]));
    int64_t value = to_int(registers[pc->a]);
    *ptr = static_cast<int32_t>(value);
}

void RegisterVM::execute_ffi_store_uint32(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) {
        return;
    }
    
    uint32_t* ptr = static_cast<uint32_t*>(UNBOX_PTR(registers[pc->dst]));
    int64_t value = to_int(registers[pc->a]);
    *ptr = static_cast<uint32_t>(value);
}

void RegisterVM::execute_ffi_store_int64(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) {
        return;
    }
    
    int64_t* ptr = static_cast<int64_t*>(UNBOX_PTR(registers[pc->dst]));
    int64_t value = to_int(registers[pc->a]);
    *ptr = value;
}

void RegisterVM::execute_ffi_store_uint64(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) {
        return;
    }
    
    uint64_t* ptr = static_cast<uint64_t*>(UNBOX_PTR(registers[pc->dst]));
    int64_t value = to_int(registers[pc->a]);
    *ptr = static_cast<uint64_t>(value);
}

void RegisterVM::execute_ffi_store_float(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) {
        return;
    }
    
    float* ptr = static_cast<float*>(UNBOX_PTR(registers[pc->dst]));
    double value = to_float(registers[pc->a]);
    *ptr = static_cast<float>(value);
}

void RegisterVM::execute_ffi_store_double(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) {
        return;
    }
    
    double* ptr = static_cast<double*>(UNBOX_PTR(registers[pc->dst]));
    double value = to_float(registers[pc->a]);
    *ptr = value;
}

void RegisterVM::execute_ffi_store_ptr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->dst])) {
        return;
    }
    
    void** ptr = static_cast<void**>(UNBOX_PTR(registers[pc->dst]));
    if (!IS_PTR(registers[pc->a])) {
        *ptr = nullptr;
    } else {
        *ptr = UNBOX_PTR(registers[pc->a]);
    }
}

// CString operations
void RegisterVM::execute_ffi_to_cstring(const LIR::LIR_Inst* pc) {
    // Get Limitly string from register
    // This requires runtime support to extract string data
    // For now, return nil as placeholder
    registers[pc->dst] = VAL_NIL;
}

void RegisterVM::execute_ffi_from_cstring(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    const char* cstr = static_cast<const char*>(UNBOX_PTR(registers[pc->a]));
    if (!cstr) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    // Convert C string to Limitly string
    // This requires runtime support
    // For now, return nil as placeholder
    registers[pc->dst] = VAL_NIL;
}

void RegisterVM::execute_ffi_free_cstring(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        return;
    }
    
    void* ptr = UNBOX_PTR(registers[pc->a]);
    if (ptr) {
        std::free(ptr);
    }
}

void RegisterVM::execute_ffi_cstring_ptr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    // CString is a frame, need to extract ptr field
    // For now, just pass through the pointer
    registers[pc->dst] = registers[pc->a];
}

void RegisterVM::execute_ffi_cstring_from_ptr(const LIR::LIR_Inst* pc) {
    if (!IS_PTR(registers[pc->a])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    
    // Create CString frame from existing pointer
    // This requires runtime support for frame creation
    // For now, return nil as placeholder
    registers[pc->dst] = VAL_NIL;
}

// Library operations
namespace {
    std::mutex g_library_mutex;
    std::unordered_map<uintptr_t, std::string> g_libraries;
}

void RegisterVM::execute_ffi_library_load(const LIR::LIR_Inst* pc) {
    LIR::Reg path_reg = arg_reg(pc, 0, pc->a);
    const char* path = boxed_c_string(registers[path_reg]);
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

void RegisterVM::execute_ffi_library_unload(const LIR::LIR_Inst* pc) {
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

void RegisterVM::execute_ffi_library_get_symbol(const LIR::LIR_Inst* pc) {
    LIR::Reg handle_reg = arg_reg(pc, 0, pc->a);
    LIR::Reg symbol_reg = arg_reg(pc, 1, pc->b);
    if (!IS_PTR(registers[handle_reg])) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    const char* symbol = boxed_c_string(registers[symbol_reg]);
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

// Callback registration
namespace {
    std::mutex g_callback_mutex;
    std::unordered_map<int64_t, void*> g_callbacks;
    int64_t g_next_callback_id = 0;
}

void RegisterVM::execute_ffi_register_callback(const LIR::LIR_Inst* pc) {
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    int64_t callback_id = g_next_callback_id++;
    
    // Register callback function
    // This requires runtime support to create trampoline
    // For now, just return the ID
    registers[pc->dst] = BOX_INT(callback_id);
}

void RegisterVM::execute_ffi_unregister_callback(const LIR::LIR_Inst* pc) {
    int64_t callback_id = to_int(registers[pc->a]);
    
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    auto it = g_callbacks.find(callback_id);
    if (it != g_callbacks.end()) {
        // Free trampoline memory
        std::free(it->second);
        g_callbacks.erase(it);
    }
}

void RegisterVM::execute_ffi_get_callback_ptr(const LIR::LIR_Inst* pc) {
    int64_t callback_id = to_int(registers[pc->a]);
    
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    auto it = g_callbacks.find(callback_id);
    if (it != g_callbacks.end()) {
        registers[pc->dst] = BOX_PTR(it->second);
    } else {
        registers[pc->dst] = VAL_NIL;
    }
}

// C call frame operations
namespace {
    std::mutex g_callframe_mutex;
    std::unordered_map<uint64_t, std::vector<RegisterValue>> g_callframe_registers;
    std::unordered_map<uint64_t, std::vector<uint8_t>> g_callframe_stack;
    uint64_t g_next_callframe_id = 0;
}

void RegisterVM::execute_ffi_ccall_frame_create(const LIR::LIR_Inst* pc) {
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

void RegisterVM::execute_ffi_ccall_frame_destroy(const LIR::LIR_Inst* pc) {
    int64_t callframe_id = to_int(registers[pc->a]);
    
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    g_callframe_registers.erase(callframe_id);
    g_callframe_stack.erase(callframe_id);
}

void RegisterVM::execute_ffi_ccall_frame_set_reg(const LIR::LIR_Inst* pc) {
    int64_t callframe_id = to_int(registers[pc->dst]);
    int64_t reg_index = to_int(registers[pc->a]);
    RegisterValue value = registers[pc->b];
    
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    auto it = g_callframe_registers.find(callframe_id);
    if (it != g_callframe_registers.end() && reg_index >= 0 && reg_index < static_cast<int64_t>(it->second.size())) {
        it->second[reg_index] = value;
    }
}

void RegisterVM::execute_ffi_ccall_frame_get_reg(const LIR::LIR_Inst* pc) {
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

void RegisterVM::execute_ffi_ccall_frame_set_stack_arg(const LIR::LIR_Inst* pc) {
    int64_t callframe_id = to_int(registers[pc->dst]);
    int64_t offset = to_int(registers[pc->a]);
    int64_t value = to_int(registers[pc->b]);
    
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    auto it = g_callframe_stack.find(callframe_id);
    if (it != g_callframe_stack.end() && offset >= 0 && offset + 8 <= static_cast<int64_t>(it->second.size())) {
        std::memcpy(&it->second[offset], &value, 8);
    }
}

void RegisterVM::execute_ffi_ccall_frame_get_stack_arg(const LIR::LIR_Inst* pc) {
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

// VM state management
void RegisterVM::execute_ffi_vm_save(const LIR::LIR_Inst* pc) {
    // Save all VM registers to a list
    // This requires runtime support for list creation
    // For now, return nil as placeholder
    registers[pc->dst] = VAL_NIL;
}

void RegisterVM::execute_ffi_vm_restore(const LIR::LIR_Inst* pc) {
    // Restore VM registers from a list
    // This requires runtime support for list access
    // For now, do nothing
}

void RegisterVM::execute_ffi_ccall_execute(const LIR::LIR_Inst* pc) {
    // Execute C call with VM state management
    // This requires runtime support for actual function calling
    // For now, return 0 as placeholder
    registers[pc->dst] = BOX_INT(0);
}

// Struct layout calculation
void RegisterVM::execute_ffi_calc_struct_layout(const LIR::LIR_Inst* pc) {
    // Calculate struct layout with padding
    // This requires runtime support for frame creation
    // For now, return nil as placeholder
    registers[pc->dst] = VAL_NIL;
}

// ABI information
void RegisterVM::execute_ffi_get_abi_info(const LIR::LIR_Inst* pc) {
    // Get platform ABI information
    // This requires runtime support for frame creation
    // For now, return nil as placeholder
    registers[pc->dst] = VAL_NIL;
}

// Main FFI execution dispatcher
void RegisterVM::execute_ffi(const LIR::LIR_Inst* pc) {
    switch (pc->op) {
        case LIR::LIR_Op::MemoryAlloc:
            execute_ffi_alloc(pc);
            break;
        case LIR::LIR_Op::MemoryFree:
            execute_ffi_free(pc);
            break;
        case LIR::LIR_Op::MemoryResize:
            execute_ffi_realloc(pc);
            break;
        case LIR::LIR_Op::MemoryLoad: {
            switch (pc->imm) {
                case 0: execute_ffi_load_int8(pc); break;
                case 1: execute_ffi_load_uint8(pc); break;
                case 2: execute_ffi_load_int16(pc); break;
                case 3: execute_ffi_load_uint16(pc); break;
                case 4: execute_ffi_load_int32(pc); break;
                case 5: execute_ffi_load_uint32(pc); break;
                case 6: execute_ffi_load_int64(pc); break;
                case 7: execute_ffi_load_uint64(pc); break;
                case 8: execute_ffi_load_float(pc); break;
                case 9: execute_ffi_load_double(pc); break;
                case 10: execute_ffi_load_ptr(pc); break;
                default: registers[pc->dst] = VAL_NIL; break;
            }
            break;
        }
        case LIR::LIR_Op::MemoryStore: {
            LIR::Reg ptr_reg = arg_reg(pc, 0, pc->a);
            LIR::Reg value_reg = arg_reg(pc, 1, pc->b);
            if (!IS_PTR(registers[ptr_reg])) break;
            void* ptr = UNBOX_PTR(registers[ptr_reg]);
            switch (pc->imm) {
                case 0: *static_cast<int8_t*>(ptr) = static_cast<int8_t>(to_int(registers[value_reg])); break;
                case 1: *static_cast<uint8_t*>(ptr) = static_cast<uint8_t>(to_int(registers[value_reg])); break;
                case 2: *static_cast<int16_t*>(ptr) = static_cast<int16_t>(to_int(registers[value_reg])); break;
                case 3: *static_cast<uint16_t*>(ptr) = static_cast<uint16_t>(to_int(registers[value_reg])); break;
                case 4: *static_cast<int32_t*>(ptr) = static_cast<int32_t>(to_int(registers[value_reg])); break;
                case 5: *static_cast<uint32_t*>(ptr) = static_cast<uint32_t>(to_int(registers[value_reg])); break;
                case 6: *static_cast<int64_t*>(ptr) = to_int(registers[value_reg]); break;
                case 7: *static_cast<uint64_t*>(ptr) = static_cast<uint64_t>(to_int(registers[value_reg])); break;
                case 8: *static_cast<float*>(ptr) = static_cast<float>(to_float(registers[value_reg])); break;
                case 9: *static_cast<double*>(ptr) = to_float(registers[value_reg]); break;
                case 10: *static_cast<void**>(ptr) = IS_PTR(registers[value_reg]) ? UNBOX_PTR(registers[value_reg]) : nullptr; break;
                default: break;
            }
            registers[pc->dst] = registers[value_reg];
            break;
        }
        case LIR::LIR_Op::ForeignCall:
            execute_ffi_ccall_execute(pc);
            break;
        // Memory allocation/deallocation
        case LIR::LIR_Op::FFIAlloc:
            execute_ffi_alloc(pc);
            break;
        case LIR::LIR_Op::FFIFree:
            execute_ffi_free(pc);
            break;
        case LIR::LIR_Op::FFIRealloc:
            execute_ffi_realloc(pc);
            break;
        
        // Memory operations
        case LIR::LIR_Op::FFIMemcpy:
            execute_ffi_memcpy(pc);
            break;
        case LIR::LIR_Op::FFIMemset:
            execute_ffi_memset(pc);
            break;
        case LIR::LIR_Op::FFIMemcmp:
            execute_ffi_memcmp(pc);
            break;
        
        // Pointer arithmetic
        case LIR::LIR_Op::FFIAddPtr:
            execute_ffi_add_ptr(pc);
            break;
        case LIR::LIR_Op::FFISubPtr:
            execute_ffi_sub_ptr(pc);
            break;
        case LIR::LIR_Op::FFIPtrDiff:
            execute_ffi_ptr_diff(pc);
            break;
        case LIR::LIR_Op::FFIAlignPtr:
            execute_ffi_align_ptr(pc);
            break;
        case LIR::LIR_Op::FFIIsAligned:
            execute_ffi_is_aligned(pc);
            break;
        
        // Load operations
        case LIR::LIR_Op::FFILoadInt8:
            execute_ffi_load_int8(pc);
            break;
        case LIR::LIR_Op::FFILoadUInt8:
            execute_ffi_load_uint8(pc);
            break;
        case LIR::LIR_Op::FFILoadInt16:
            execute_ffi_load_int16(pc);
            break;
        case LIR::LIR_Op::FFILoadUInt16:
            execute_ffi_load_uint16(pc);
            break;
        case LIR::LIR_Op::FFILoadInt32:
            execute_ffi_load_int32(pc);
            break;
        case LIR::LIR_Op::FFILoadUInt32:
            execute_ffi_load_uint32(pc);
            break;
        case LIR::LIR_Op::FFILoadInt64:
            execute_ffi_load_int64(pc);
            break;
        case LIR::LIR_Op::FFILoadUInt64:
            execute_ffi_load_uint64(pc);
            break;
        case LIR::LIR_Op::FFILoadFloat:
            execute_ffi_load_float(pc);
            break;
        case LIR::LIR_Op::FFILoadDouble:
            execute_ffi_load_double(pc);
            break;
        case LIR::LIR_Op::FFILoadPtr:
            execute_ffi_load_ptr(pc);
            break;
        
        // Store operations
        case LIR::LIR_Op::FFIStoreInt8:
            execute_ffi_store_int8(pc);
            break;
        case LIR::LIR_Op::FFIStoreUInt8:
            execute_ffi_store_uint8(pc);
            break;
        case LIR::LIR_Op::FFIStoreInt16:
            execute_ffi_store_int16(pc);
            break;
        case LIR::LIR_Op::FFIStoreUInt16:
            execute_ffi_store_uint16(pc);
            break;
        case LIR::LIR_Op::FFIStoreInt32:
            execute_ffi_store_int32(pc);
            break;
        case LIR::LIR_Op::FFIStoreUInt32:
            execute_ffi_store_uint32(pc);
            break;
        case LIR::LIR_Op::FFIStoreInt64:
            execute_ffi_store_int64(pc);
            break;
        case LIR::LIR_Op::FFIStoreUInt64:
            execute_ffi_store_uint64(pc);
            break;
        case LIR::LIR_Op::FFIStoreFloat:
            execute_ffi_store_float(pc);
            break;
        case LIR::LIR_Op::FFIStoreDouble:
            execute_ffi_store_double(pc);
            break;
        case LIR::LIR_Op::FFIStorePtr:
            execute_ffi_store_ptr(pc);
            break;
        
        // CString operations
        case LIR::LIR_Op::FFIToCString:
            execute_ffi_to_cstring(pc);
            break;
        case LIR::LIR_Op::FFIFromCString:
            execute_ffi_from_cstring(pc);
            break;
        case LIR::LIR_Op::FFIFreeCString:
            execute_ffi_free_cstring(pc);
            break;
        case LIR::LIR_Op::FFICStringPtr:
            execute_ffi_cstring_ptr(pc);
            break;
        case LIR::LIR_Op::FFICStringFromPtr:
            execute_ffi_cstring_from_ptr(pc);
            break;
        
        // Library operations
        case LIR::LIR_Op::FFILibraryLoad:
            execute_ffi_library_load(pc);
            break;
        case LIR::LIR_Op::FFILibraryUnload:
            execute_ffi_library_unload(pc);
            break;
        case LIR::LIR_Op::FFILibraryGetSymbol:
            execute_ffi_library_get_symbol(pc);
            break;
        
        // Callback registration
        case LIR::LIR_Op::FFIRegisterCallback:
            execute_ffi_register_callback(pc);
            break;
        case LIR::LIR_Op::FFIUnregisterCallback:
            execute_ffi_unregister_callback(pc);
            break;
        case LIR::LIR_Op::FFIGetCallbackPtr:
            execute_ffi_get_callback_ptr(pc);
            break;
        
        // C call frame operations
        case LIR::LIR_Op::FFICCallFrameCreate:
            execute_ffi_ccall_frame_create(pc);
            break;
        case LIR::LIR_Op::FFICCallFrameDestroy:
            execute_ffi_ccall_frame_destroy(pc);
            break;
        case LIR::LIR_Op::FFICCallFrameSetReg:
            execute_ffi_ccall_frame_set_reg(pc);
            break;
        case LIR::LIR_Op::FFICCallFrameGetReg:
            execute_ffi_ccall_frame_get_reg(pc);
            break;
        case LIR::LIR_Op::FFICCallFrameSetStackArg:
            execute_ffi_ccall_frame_set_stack_arg(pc);
            break;
        case LIR::LIR_Op::FFICCallFrameGetStackArg:
            execute_ffi_ccall_frame_get_stack_arg(pc);
            break;
        
        // VM state management
        case LIR::LIR_Op::FFIVMSave:
            execute_ffi_vm_save(pc);
            break;
        case LIR::LIR_Op::FFIVMRestore:
            execute_ffi_vm_restore(pc);
            break;
        case LIR::LIR_Op::FFICCallExecute:
            execute_ffi_ccall_execute(pc);
            break;
        
        // Struct layout
        case LIR::LIR_Op::FFICalcStructLayout:
            execute_ffi_calc_struct_layout(pc);
            break;
        
        // ABI information
        case LIR::LIR_Op::FFIGetABIInfo:
            execute_ffi_get_abi_info(pc);
            break;
        
        default:
            break;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM

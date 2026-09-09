#include "../register.hh"
#include "../vm_runtime.hh"
#include "../vm_value.hh"
#include "../vm_list.hh"
#include "../../../lir/functions.hh"
#include "../vm_string.hh"
#include <cstdlib>
#include <cstring>
#include <memory>
#include <unordered_map>
#include <mutex>
#include <functional>
#include <vector>
#include <string>
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
    // Zero is reserved as the invalid native handle throughout std.ffi.
    int64_t g_next_callback_id = 1;
    std::mutex g_callframe_mutex;
    std::unordered_map<uint64_t, std::vector<RegisterValue>> g_callframe_registers;
    std::unordered_map<uint64_t, std::vector<uint8_t>> g_callframe_stack;
    uint64_t g_next_callframe_id = 0;

    // -----------------------------------------------------------------------
    // Native trampoline infrastructure
    // -----------------------------------------------------------------------

    // Per-trampoline context: everything the dispatcher needs to re-enter the VM.
    struct TrampolineContext {
        RegisterVM*            vm;          // The VM that owns this callback
        std::string            func_name;   // Limitly function name to invoke
        std::vector<LIR::Type> arg_types;   // Native parameter types (from LIR)
        LIR::Type              ret_type;    // Native return type  (from LIR)
        ffi_cif                cif;         // Prepared call-interface (owned)
        std::vector<ffi_type*> ffi_arg_ptrs;// Pointers into ffi_arg_types storage
        ffi_closure*           closure;     // The executable closure page
        void*                  code_ptr;    // Executable address inside the page
        int64_t                id;          // Our callback ID
    };

    // id -> TrampolineContext*   (heap-allocated, freed on CallbackDestroy)
    std::unordered_map<int64_t, TrampolineContext*> g_callbacks;

    // -----------------------------------------------------------------------
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

    ffi_type* lir_type_to_ffi_type(LIR::Type type) {
        switch (type) {
            case LIR::Type::I8:   return &ffi_type_sint8;
            case LIR::Type::U8:   return &ffi_type_uint8;
            case LIR::Type::I16:  return &ffi_type_sint16;
            case LIR::Type::U16:  return &ffi_type_uint16;
            case LIR::Type::I32:  return &ffi_type_sint32;
            case LIR::Type::U32:  return &ffi_type_uint32;
            case LIR::Type::I64:  return &ffi_type_sint64;
            case LIR::Type::U64:  return &ffi_type_uint64;
            case LIR::Type::F32:  return &ffi_type_float;
            case LIR::Type::F64:  return &ffi_type_double;
            case LIR::Type::Bool: return &ffi_type_uint8;
            case LIR::Type::Ptr:  return &ffi_type_pointer;
            case LIR::Type::Void: return &ffi_type_void;
            default:              return &ffi_type_void;
        }
    }

    bool ffi_type_id_to_lir(int64_t id, bool allow_void, LIR::Type& out) {
        switch (id) {
            case 0:  out = LIR::Type::I8;  return true;
            case 1:  out = LIR::Type::U8;  return true;
            case 2:  out = LIR::Type::I16; return true;
            case 3:  out = LIR::Type::U16; return true;
            case 4:  out = LIR::Type::I32; return true;
            case 5:  out = LIR::Type::U32; return true;
            case 6:  out = LIR::Type::I64; return true;
            case 7:  out = LIR::Type::U64; return true;
            case 8:  out = LIR::Type::F32; return true;
            case 9:  out = LIR::Type::F64; return true;
            case 10: // pointer
            case 11: out = LIR::Type::Ptr; return true; // C string
            case 12:
                if (allow_void) { out = LIR::Type::Void; return true; }
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

    // -----------------------------------------------------------------------
    // Convert a raw C argument slot (void*) to a Limitly RegisterValue.
    // `args[i]` from libffi is a pointer TO the argument, not the argument.
    // -----------------------------------------------------------------------
    RegisterValue ffi_arg_to_register(void* arg_slot, LIR::Type type) {
        switch (type) {
            case LIR::Type::I8:  { int8_t   v; std::memcpy(&v, arg_slot, sizeof(v)); return make_i64((int64_t)v); }
            case LIR::Type::U8:  { uint8_t  v; std::memcpy(&v, arg_slot, sizeof(v)); return make_i64((int64_t)v); }
            case LIR::Type::I16: { int16_t  v; std::memcpy(&v, arg_slot, sizeof(v)); return make_i64((int64_t)v); }
            case LIR::Type::U16: { uint16_t v; std::memcpy(&v, arg_slot, sizeof(v)); return make_i64((int64_t)v); }
            case LIR::Type::I32: { int32_t  v; std::memcpy(&v, arg_slot, sizeof(v)); return make_i64((int64_t)v); }
            case LIR::Type::U32: { uint32_t v; std::memcpy(&v, arg_slot, sizeof(v)); return make_i64((int64_t)v); }
            case LIR::Type::I64: { int64_t  v; std::memcpy(&v, arg_slot, sizeof(v)); return make_i64(v);           }
            case LIR::Type::U64: { uint64_t v; std::memcpy(&v, arg_slot, sizeof(v)); return make_i64((int64_t)v); }
            case LIR::Type::F32: { float    v; std::memcpy(&v, arg_slot, sizeof(v)); return make_float((double)v); }
            case LIR::Type::F64: { double   v; std::memcpy(&v, arg_slot, sizeof(v)); return make_float(v);          }
            case LIR::Type::Bool:{ uint8_t  v; std::memcpy(&v, arg_slot, sizeof(v)); return v ? VAL_TRUE : VAL_FALSE; }
            case LIR::Type::Ptr: {
                void* p; std::memcpy(&p, arg_slot, sizeof(p));
                return lm_alloc_foreign_ptr(p);
            }
            default: return VAL_NIL;
        }
    }

    // -----------------------------------------------------------------------
    // Convert a Limitly RegisterValue to the native return slot expected by
    // libffi.  `ret` points to the caller-allocated return buffer.
    // -----------------------------------------------------------------------
    void register_to_ffi_ret(RegisterValue rv, LIR::Type type, void* ret) {
        switch (type) {
            case LIR::Type::I8:  { int8_t   v = (int8_t)as_i64(rv);   std::memcpy(ret, &v, sizeof(v)); break; }
            case LIR::Type::U8:  { uint8_t  v = (uint8_t)as_i64(rv);  std::memcpy(ret, &v, sizeof(v)); break; }
            case LIR::Type::I16: { int16_t  v = (int16_t)as_i64(rv);  std::memcpy(ret, &v, sizeof(v)); break; }
            case LIR::Type::U16: { uint16_t v = (uint16_t)as_i64(rv); std::memcpy(ret, &v, sizeof(v)); break; }
            case LIR::Type::I32: { int32_t  v = (int32_t)as_i64(rv);  std::memcpy(ret, &v, sizeof(v)); break; }
            case LIR::Type::U32: { uint32_t v = (uint32_t)as_i64(rv); std::memcpy(ret, &v, sizeof(v)); break; }
            case LIR::Type::I64: { int64_t  v = as_i64(rv);           std::memcpy(ret, &v, sizeof(v)); break; }
            case LIR::Type::U64: { uint64_t v = (uint64_t)as_i64(rv); std::memcpy(ret, &v, sizeof(v)); break; }
            case LIR::Type::F32: { float    v = (float)as_float(rv);  std::memcpy(ret, &v, sizeof(v)); break; }
            case LIR::Type::F64: { double   v = as_float(rv);         std::memcpy(ret, &v, sizeof(v)); break; }
            case LIR::Type::Bool:{ uint8_t  v = IS_BOOL(rv) ? (UNBOX_BOOL(rv) ? 1 : 0) : (uint8_t)(as_i64(rv) != 0); std::memcpy(ret, &v, sizeof(v)); break; }
            case LIR::Type::Ptr: {
                void* p = value_to_ptr(rv);
                std::memcpy(ret, &p, sizeof(p));
                break;
            }
            case LIR::Type::Void:
            default: break;  // nothing to write for void return
        }
    }

    // -----------------------------------------------------------------------
    // Generic trampoline dispatcher — called by every ffi_closure.
    // Signature matches what ffi_prep_closure_loc expects.
    // -----------------------------------------------------------------------
    static void trampoline_dispatcher(
        ffi_cif*  /*cif*/,
        void*      ret,
        void**     args,
        void*      user_data)
    {
        TrampolineContext* ctx = static_cast<TrampolineContext*>(user_data);
        RegisterVM* vm = ctx->vm;

        // Marshal raw C arguments to Limitly RegisterValues
        std::vector<RegisterValue> arg_vals;
        arg_vals.reserve(ctx->arg_types.size());
        for (size_t i = 0; i < ctx->arg_types.size(); ++i)
            arg_vals.push_back(ffi_arg_to_register(args[i], ctx->arg_types[i]));

        // Re-enter VM through the public bridge (handles save/restore)
        RegisterValue rv = vm->invoke_for_callback(ctx->func_name, arg_vals);

        // Marshal return value back to native ABI
        if (ret) register_to_ffi_ret(rv, ctx->ret_type, ret);
    }

} // namespace (anonymous)

// ---------------------------------------------------------------------------
// RegisterVM::invoke_for_callback
//
// Public bridge called by the trampoline dispatcher.  Mirrors the save/restore
// pattern used by the Call handler in vm_calls.cpp so the two paths remain
// consistent.  On entry, `args` are already Limitly RegisterValues.
// Returns whatever registers[0] held after the Limitly function returns.
// ---------------------------------------------------------------------------
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

    // Pad arg list to expected parameter count
    std::vector<RegisterValue> arg_vals = args;
    size_t expected = func->getParameters().size();
    while (arg_vals.size() < expected) arg_vals.push_back(VAL_NIL);

    // Save current VM execution state
    auto saved_registers              = registers;
    const LIR::LIR_Function* saved_func = current_function_;

    // Set up fresh register file with arguments
    registers.assign(registers.size(), VAL_NIL);
    for (size_t i = 0; i < arg_vals.size() && i < registers.size(); ++i)
        registers[i] = arg_vals[i];

    // Build a temporary LIR_Function wrapper (same pattern as vm_calls.cpp)
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

    // Restore caller's VM state
    registers        = saved_registers;
    current_function_ = saved_func;

    return return_value;
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
    RegisterValue val = lm_alloc_foreign_ptr(handle);
    registers[pc->dst] = val;
    // Register allocation with current active region
    if (IS_PTR(val) && !vm_region_stack.empty()) {
        uintptr_t ptr = reinterpret_cast<uintptr_t>(UNBOX_PTR(val));
        vm_allocation_regions[ptr] = active_region_id;
    }
}

void RegisterVM::execute_extern_library_unload(const LIR::LIR_Inst* pc) {
    void* handle = value_to_ptr(registers[pc->a]);
    if (handle) {
        {
            std::lock_guard<std::mutex> lock(g_library_mutex);
            auto it = g_libraries.find(reinterpret_cast<uintptr_t>(handle));
            if (it == g_libraries.end()) return;
            // Remove before unloading so concurrent resolve/unload attempts fail.
            g_libraries.erase(it);
        }
        #ifdef _WIN32
        FreeLibrary(static_cast<HMODULE>(handle));
        #else
        dlclose(handle);
        #endif
    }
}

void RegisterVM::execute_extern_library_get_symbol(const LIR::LIR_Inst* pc) {
    LIR::Reg handle_reg = arg_reg(pc, 0, pc->a);
    LIR::Reg symbol_reg = arg_reg(pc, 1, pc->b);
    void* handle = value_to_ptr(registers[handle_reg]);
    if (!handle) { registers[pc->dst] = VAL_NIL; return; }
    const char* symbol = get_cstring_from_value(registers[symbol_reg]);
    if (!symbol) { registers[pc->dst] = VAL_NIL; return; }
    // Keep the handle alive across symbol lookup; unload uses the same mutex.
    std::lock_guard<std::mutex> lock(g_library_mutex);
    if (g_libraries.find(reinterpret_cast<uintptr_t>(handle)) == g_libraries.end()) {
        registers[pc->dst] = VAL_NIL;
        return;
    }
    #ifdef _WIN32
    void* ptr = reinterpret_cast<void*>(GetProcAddress(static_cast<HMODULE>(handle), symbol));
    #else
    void* ptr = dlsym(handle, symbol);
    #endif
    RegisterValue val = ptr ? lm_alloc_foreign_ptr(ptr) : VAL_NIL;
    registers[pc->dst] = val;
    // Register allocation with current active region
    if (IS_PTR(val) && !vm_region_stack.empty()) {
        uintptr_t ptr_val = reinterpret_cast<uintptr_t>(UNBOX_PTR(val));
        vm_allocation_regions[ptr_val] = active_region_id;
    }
}

void RegisterVM::execute_extern_call_function(const LIR::LIR_Inst* pc) {
    RegisterValue func_ptr_val = registers[arg_reg(pc, 0, pc->a)];
    void* func_ptr = value_to_ptr(func_ptr_val);
    if (!func_ptr) { registers[pc->dst] = VAL_NIL; return; }
    
    LIR::Type ret_type = pc->result_type;
    std::vector<LIR::Reg> arg_regs = pc->call_args;
    size_t arg_start = 0;
    if (pc->op == LIR::LIR_Op::ForeignCall) arg_start = 1;
    std::vector<RegisterValue> call_arg_values;
    std::vector<LIR::Type> resolved_arg_types;

    if (pc->func_name == "std.ffi.foreign_call" || pc->func_name == "ffi.foreign_call") {
        if (pc->call_args.size() > 2) {
            int64_t ret_id = to_int(registers[pc->call_args[2]]);
            ffi_type_id_to_lir(ret_id, true, ret_type);
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
                    LIR::Type arg_t = LIR::Type::I64;
                    bool got_type = false;
                    if (pt_list && i < pt_list->size) {
                        int64_t tid = to_int(pt_list->data[i]);
                        got_type = ffi_type_id_to_lir(tid, false, arg_t);
                    }
                    if (!got_type) {
                        if (is_float(val)) arg_t = LIR::Type::F64;
                        else if (IS_PTR(val)) arg_t = LIR::Type::Ptr;
                        else arg_t = LIR::Type::I64;
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
                resolved_arg_types.push_back(pc->call_arg_types[i]);
            } else {
                RegisterValue val = registers[arg_regs[i]];
                if (is_float(val)) resolved_arg_types.push_back(LIR::Type::F64);
                else if (IS_PTR(val)) resolved_arg_types.push_back(LIR::Type::Ptr);
                else resolved_arg_types.push_back(LIR::Type::I64);
            }
        }
    }

    size_t num_args = call_arg_values.size();
    std::vector<ffi_type*> ffi_arg_types(num_args);
    std::vector<void*> ffi_arg_values(num_args);
    std::vector<uint64_t> arg_storage(num_args);

    for (size_t i = 0; i < num_args; ++i) {
        LIR::Type type = resolved_arg_types[i];
        ffi_arg_types[i] = lir_type_to_ffi_type(type);
        RegisterValue val = call_arg_values[i];
        switch (type) {
            case LIR::Type::I8:  { int8_t v = (int8_t)to_int(val); std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LIR::Type::U8:  { uint8_t v = (uint8_t)to_int(val); std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LIR::Type::I16: { int16_t v = (int16_t)to_int(val); std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LIR::Type::U16: { uint16_t v = (uint16_t)to_int(val); std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LIR::Type::I32: { int32_t v = (int32_t)to_int(val); std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LIR::Type::U32: { uint32_t v = (uint32_t)to_int(val); std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LIR::Type::I64: { int64_t v = to_int(val); std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LIR::Type::U64: { uint64_t v = (uint64_t)to_int(val); std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LIR::Type::F32: { float v = (float)to_float(val); std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LIR::Type::F64: { double v = to_float(val); std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LIR::Type::Bool: { uint8_t v = (uint8_t)(to_int(val) != 0); std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LIR::Type::Ptr: {
                void* p = value_to_ptr(val);
                const char* cstr = get_cstring_from_value(val);
                if (cstr) p = (void*)cstr;
                std::memcpy(&arg_storage[i], &p, sizeof(p));
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
            case LIR::Type::I8:  { int8_t v; std::memcpy(&v, &result_storage, sizeof(v)); registers[pc->dst] = BOX_INT((int64_t)v); break; }
            case LIR::Type::U8:  { uint8_t v; std::memcpy(&v, &result_storage, sizeof(v)); registers[pc->dst] = BOX_INT((int64_t)v); break; }
            case LIR::Type::I16: { int16_t v; std::memcpy(&v, &result_storage, sizeof(v)); registers[pc->dst] = BOX_INT((int64_t)v); break; }
            case LIR::Type::U16: { uint16_t v; std::memcpy(&v, &result_storage, sizeof(v)); registers[pc->dst] = BOX_INT((int64_t)v); break; }
            case LIR::Type::I32: { int32_t v; std::memcpy(&v, &result_storage, sizeof(v)); registers[pc->dst] = BOX_INT((int64_t)v); break; }
            case LIR::Type::U32: { uint32_t v; std::memcpy(&v, &result_storage, sizeof(v)); registers[pc->dst] = BOX_INT((int64_t)v); break; }
            case LIR::Type::I64: { int64_t v; std::memcpy(&v, &result_storage, sizeof(v)); registers[pc->dst] = BOX_INT(v); break; }
            case LIR::Type::U64: { uint64_t v; std::memcpy(&v, &result_storage, sizeof(v)); registers[pc->dst] = BOX_INT((int64_t)v); break; }
            case LIR::Type::F32: { float v; std::memcpy(&v, &result_storage, sizeof(v)); registers[pc->dst] = make_float((double)v); break; }
            case LIR::Type::F64: { double v; std::memcpy(&v, &result_storage, sizeof(v)); registers[pc->dst] = make_float(v); break; }
            case LIR::Type::Bool: { uint8_t v; std::memcpy(&v, &result_storage, sizeof(v)); registers[pc->dst] = v ? VAL_TRUE : VAL_FALSE; break; }
            case LIR::Type::Ptr:  {
                void* p; std::memcpy(&p, &result_storage, sizeof(p));
                RegisterValue val = p ? lm_alloc_foreign_ptr(p) : VAL_NIL;
                registers[pc->dst] = val;
                // Register allocation with current active region
                if (IS_PTR(val) && !vm_region_stack.empty()) {
                    uintptr_t ptr_val = reinterpret_cast<uintptr_t>(UNBOX_PTR(val));
                    vm_allocation_regions[ptr_val] = active_region_id;
                }
                break;
            }
            default: registers[pc->dst] = VAL_NIL; break;
        }
    } else registers[pc->dst] = VAL_NIL;
}

// ---------------------------------------------------------------------------
// CallbackCreate -- allocate a genuine native trampoline via libffi closures.
//
// Called as:  ffi.callback_create(func_name: str,
//                                  arg_types: [int],
//                                  ret_type:  int): int
//
// The LIR instruction's call_args hold the three argument registers:
//   call_args[0] : register containing the Limitly function name (str)
//   call_args[1] : register containing the arg-type list ([int])
//   call_args[2] : register containing the return-type integer (int)
//
// Returns an integer handle (callback ID) that identifies the trampoline.
// ---------------------------------------------------------------------------
void RegisterVM::execute_extern_register_callback(const LIR::LIR_Inst* pc) {
    if (pc->call_args.size() != 3) {
        std::cerr << "[ffi] callback_create: expected name, argument types, and return type\n";
        registers[pc->dst] = VAL_NIL;
        return;
    }
    // ── Step 1: Read the Limitly function name from call_args[0] ──────────
    std::string limitly_func_name;
    if (!pc->call_args.empty()) {
        const char* cstr = get_cstring_from_value(registers[pc->call_args[0]]);
        if (cstr) {
            limitly_func_name = cstr;
        } else {
            // Try plain string value
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

    // ── Step 2: Read the arg-type list from call_args[1] ─────────────────
    // Each element is a TYPE_* integer constant (e.g., TYPE_I64 == 6).
    std::vector<LIR::Type> arg_types;
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
                    LIR::Type type;
                    if (!ffi_type_id_to_lir(type_id, false, type)) {
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

    // ── Step 3: Read the return-type integer from call_args[2] ───────────
    LIR::Type ret_type;
    int64_t rid = as_i64(registers[pc->call_args[2]]);
    if (!ffi_type_id_to_lir(rid, true, ret_type)) {
        std::cerr << "[ffi] callback_create: invalid return type id " << rid << '\n';
        registers[pc->dst] = VAL_NIL;
        return;
    }
    // ── Step 4: Assign a stable callback ID ──────────────────────────────
    int64_t id;
    {
        std::lock_guard<std::mutex> lock(g_callback_mutex);
        id = g_next_callback_id++;
    }

    // Build the ffi_type* vectors (must outlive ffi_prep_cif — stored in ctx)
    auto* ctx = new TrampolineContext();
    ctx->vm        = this;
    ctx->func_name = limitly_func_name;  // runtime function name from call arg
    ctx->arg_types = arg_types;
    ctx->ret_type  = ret_type;
    ctx->id        = id;

    ctx->ffi_arg_ptrs.reserve(arg_types.size());
    for (auto t : arg_types)
        ctx->ffi_arg_ptrs.push_back(lir_type_to_ffi_type(t));

    ffi_type* ffi_ret = lir_type_to_ffi_type(ret_type);
    ffi_status status = ffi_prep_cif(
        &ctx->cif,
        FFI_DEFAULT_ABI,
        static_cast<unsigned>(ctx->ffi_arg_ptrs.size()),
        ffi_ret,
        ctx->ffi_arg_ptrs.empty() ? nullptr : ctx->ffi_arg_ptrs.data());

    if (status != FFI_OK) {
        std::cerr << "[ffi] ffi_prep_cif failed (status=" << status
                  << ") for callback '" << limitly_func_name << "'\n";
        delete ctx;
        registers[pc->dst] = VAL_NIL;
        return;
    }

    // Allocate an executable closure page
    ctx->closure  = static_cast<ffi_closure*>(ffi_closure_alloc(sizeof(ffi_closure), &ctx->code_ptr));
    if (!ctx->closure) {
        std::cerr << "[ffi] ffi_closure_alloc failed for callback '" << limitly_func_name << "'\n";
        delete ctx;
        registers[pc->dst] = VAL_NIL;
        return;
    }

    status = ffi_prep_closure_loc(
        ctx->closure,
        &ctx->cif,
        trampoline_dispatcher,
        ctx,
        ctx->code_ptr);

    if (status != FFI_OK) {
        std::cerr << "[ffi] ffi_prep_closure_loc failed (status=" << status
                  << ") for callback '" << limitly_func_name << "'\n";
        ffi_closure_free(ctx->closure);
        delete ctx;
        registers[pc->dst] = VAL_NIL;
        return;
    }

    // Register the context
    {
        std::lock_guard<std::mutex> lock(g_callback_mutex);
        g_callbacks[id] = ctx;
    }
    registers[pc->dst] = BOX_INT(id);
}

// ---------------------------------------------------------------------------
// CallbackDestroy — release the libffi closure and its context.
// ---------------------------------------------------------------------------
void RegisterVM::execute_extern_unregister_callback(const LIR::LIR_Inst* pc) {
    int64_t id = to_int(registers[pc->a]);
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    auto it = g_callbacks.find(id);
    if (it != g_callbacks.end()) {
        TrampolineContext* ctx = it->second;
        ffi_closure_free(ctx->closure); // releases the executable page
        delete ctx;
        g_callbacks.erase(it);
    }
}

// ---------------------------------------------------------------------------
// execute_extern_get_callback_ptr — return the executable code pointer
// (i.e. the real C-callable address) for a previously created trampoline.
// This is the address you pass to RegisterClassEx, SetWindowsHookEx, etc.
// ---------------------------------------------------------------------------
void RegisterVM::execute_extern_get_callback_ptr(const LIR::LIR_Inst* pc) {
    int64_t id = to_int(registers[pc->a]);
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    auto it = g_callbacks.find(id);
    if (it != g_callbacks.end()) {
        TrampolineContext* ctx = it->second;
        // code_ptr is the executable entry point — box it as a foreign pointer
        RegisterValue val = lm_alloc_foreign_ptr(ctx->code_ptr);
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
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    g_callframe_registers.erase(id); g_callframe_stack.erase(id);
}
void RegisterVM::execute_extern_ccall_frame_set_reg(const LIR::LIR_Inst* pc) {
    int64_t id = to_int(registers[pc->dst]); int64_t idx = to_int(registers[pc->a]);
    RegisterValue val = registers[pc->b];
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    auto it = g_callframe_registers.find(id);
    if (it != g_callframe_registers.end() && idx >= 0 && idx < (int64_t)it->second.size()) it->second[idx] = val;
}
void RegisterVM::execute_extern_ccall_frame_get_reg(const LIR::LIR_Inst* pc) {
    int64_t id = to_int(registers[pc->a]); int64_t idx = to_int(registers[pc->b]);
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    auto it = g_callframe_registers.find(id);
    if (it != g_callframe_registers.end() && idx >= 0 && idx < (int64_t)it->second.size()) registers[pc->dst] = it->second[idx];
    else registers[pc->dst] = VAL_NIL;
}
void RegisterVM::execute_extern_ccall_frame_set_stack_arg(const LIR::LIR_Inst* pc) {
    int64_t id = to_int(registers[pc->dst]); int64_t off = to_int(registers[pc->a]); int64_t val = to_int(registers[pc->b]);
    std::lock_guard<std::mutex> lock(g_callframe_mutex);
    auto it = g_callframe_stack.find(id);
    if (it != g_callframe_stack.end() && off >= 0 && off + 8 <= (int64_t)it->second.size()) std::memcpy(&it->second[off], &val, 8);
}
void RegisterVM::execute_extern_ccall_frame_get_stack_arg(const LIR::LIR_Inst* pc) {
    int64_t id = to_int(registers[pc->a]); int64_t off = to_int(registers[pc->b]);
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
            // imm == 0: create trampoline (returns int handle)
            // imm == 1: get executable code pointer (returns fnptr)
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

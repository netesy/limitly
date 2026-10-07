#include "lymarrt.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>
#include <mutex>
#include <vector>
#include <ffi.h>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace {

std::mutex g_lymarrt_lib_mutex;
std::unordered_map<uintptr_t, std::string> g_lymarrt_libraries;

std::mutex g_lymarrt_cb_mutex;
int64_t g_lymarrt_next_cb_id = 1;

struct LymarrtTrampolineContext {
    lymarrt_callback_handler handler;
    void*                    userdata;
    std::vector<lymarrt_type> arg_types;
    lymarrt_type             ret_type;
    ffi_cif                  cif;
    std::vector<ffi_type*>   ffi_arg_ptrs;
    ffi_closure*             closure;
    void*                    code_ptr;
    int64_t                  id;
};

std::unordered_map<int64_t, LymarrtTrampolineContext*> g_lymarrt_callbacks;

ffi_type* lymarrt_type_to_ffi(lymarrt_type type) {
    switch (type) {
        case LYMARRT_TYPE_I8:   return &ffi_type_sint8;
        case LYMARRT_TYPE_U8:   return &ffi_type_uint8;
        case LYMARRT_TYPE_I16:  return &ffi_type_sint16;
        case LYMARRT_TYPE_U16:  return &ffi_type_uint16;
        case LYMARRT_TYPE_I32:  return &ffi_type_sint32;
        case LYMARRT_TYPE_U32:  return &ffi_type_uint32;
        case LYMARRT_TYPE_I64:  return &ffi_type_sint64;
        case LYMARRT_TYPE_U64:  return &ffi_type_uint64;
        case LYMARRT_TYPE_F32:  return &ffi_type_float;
        case LYMARRT_TYPE_F64:  return &ffi_type_double;
        case LYMARRT_TYPE_PTR:
        case LYMARRT_TYPE_CSTRING: return &ffi_type_pointer;
        case LYMARRT_TYPE_VOID: return &ffi_type_void;
        default:                return &ffi_type_void;
    }
}

lymarrt_value lymarrt_ffi_arg_to_val(void* arg_slot, lymarrt_type type) {
    lymarrt_value v;
    std::memset(&v, 0, sizeof(v));
    v.type = type;
    switch (type) {
        case LYMARRT_TYPE_I8:  { int8_t x; std::memcpy(&x, arg_slot, sizeof(x)); v.val.i8 = x; break; }
        case LYMARRT_TYPE_U8:  { uint8_t x; std::memcpy(&x, arg_slot, sizeof(x)); v.val.u8 = x; break; }
        case LYMARRT_TYPE_I16: { int16_t x; std::memcpy(&x, arg_slot, sizeof(x)); v.val.i16 = x; break; }
        case LYMARRT_TYPE_U16: { uint16_t x; std::memcpy(&x, arg_slot, sizeof(x)); v.val.u16 = x; break; }
        case LYMARRT_TYPE_I32: { int32_t x; std::memcpy(&x, arg_slot, sizeof(x)); v.val.i32 = x; break; }
        case LYMARRT_TYPE_U32: { uint32_t x; std::memcpy(&x, arg_slot, sizeof(x)); v.val.u32 = x; break; }
        case LYMARRT_TYPE_I64: { int64_t x; std::memcpy(&x, arg_slot, sizeof(x)); v.val.i64 = x; break; }
        case LYMARRT_TYPE_U64: { uint64_t x; std::memcpy(&x, arg_slot, sizeof(x)); v.val.u64 = x; break; }
        case LYMARRT_TYPE_F32: { float x; std::memcpy(&x, arg_slot, sizeof(x)); v.val.f32 = x; break; }
        case LYMARRT_TYPE_F64: { double x; std::memcpy(&x, arg_slot, sizeof(x)); v.val.f64 = x; break; }
        case LYMARRT_TYPE_PTR:
        case LYMARRT_TYPE_CSTRING: { void* x; std::memcpy(&x, arg_slot, sizeof(x)); v.val.ptr = x; break; }
        default: break;
    }
    return v;
}

void lymarrt_val_to_ffi_ret(const lymarrt_value* val, lymarrt_type type, void* ret) {
    if (!ret) return;
    switch (type) {
        case LYMARRT_TYPE_I8:  { int8_t x = val->val.i8; std::memcpy(ret, &x, sizeof(x)); break; }
        case LYMARRT_TYPE_U8:  { uint8_t x = val->val.u8; std::memcpy(ret, &x, sizeof(x)); break; }
        case LYMARRT_TYPE_I16: { int16_t x = val->val.i16; std::memcpy(ret, &x, sizeof(x)); break; }
        case LYMARRT_TYPE_U16: { uint16_t x = val->val.u16; std::memcpy(ret, &x, sizeof(x)); break; }
        case LYMARRT_TYPE_I32: { int32_t x = val->val.i32; std::memcpy(ret, &x, sizeof(x)); break; }
        case LYMARRT_TYPE_U32: { uint32_t x = val->val.u32; std::memcpy(ret, &x, sizeof(x)); break; }
        case LYMARRT_TYPE_I64: { int64_t x = val->val.i64; std::memcpy(ret, &x, sizeof(x)); break; }
        case LYMARRT_TYPE_U64: { uint64_t x = val->val.u64; std::memcpy(ret, &x, sizeof(x)); break; }
        case LYMARRT_TYPE_F32: { float x = val->val.f32; std::memcpy(ret, &x, sizeof(x)); break; }
        case LYMARRT_TYPE_F64: { double x = val->val.f64; std::memcpy(ret, &x, sizeof(x)); break; }
        case LYMARRT_TYPE_PTR:
        case LYMARRT_TYPE_CSTRING: { void* x = val->val.ptr; std::memcpy(ret, &x, sizeof(x)); break; }
        case LYMARRT_TYPE_VOID:
        default: break;
    }
}

static void lymarrt_trampoline_dispatcher(
    ffi_cif* /*cif*/,
    void* ret,
    void** args,
    void* user_data)
{
    LymarrtTrampolineContext* ctx = static_cast<LymarrtTrampolineContext*>(user_data);
    std::vector<lymarrt_value> arg_vals(ctx->arg_types.size());
    for (size_t i = 0; i < ctx->arg_types.size(); ++i) {
        arg_vals[i] = lymarrt_ffi_arg_to_val(args[i], ctx->arg_types[i]);
    }
    lymarrt_value res;
    std::memset(&res, 0, sizeof(res));
    res.type = ctx->ret_type;
    if (ctx->handler) {
        ctx->handler(ctx->userdata, arg_vals.data(), arg_vals.size(), &res);
    }
    if (ret) {
        lymarrt_val_to_ffi_ret(&res, ctx->ret_type, ret);
    }
}

} // namespace

extern "C" {

uint32_t lymarrt_abi_version(void) {
    return LYMARRT_ABI_VERSION;
}

void* lymarrt_library_open(const char* path) {
    if (!path) return NULL;
#ifdef _WIN32
    void* handle = static_cast<void*>(LoadLibraryA(path));
#else
    void* handle = dlopen(path, RTLD_LAZY | RTLD_LOCAL);
#endif
    if (!handle) {
        if (const char* home = std::getenv("LYMAR_HOME")) {
            auto bundled = std::filesystem::path(home) / "bin" / std::filesystem::path(path).filename();
#ifdef _WIN32
            handle = static_cast<void*>(LoadLibraryA(bundled.string().c_str()));
#else
            handle = dlopen(bundled.string().c_str(), RTLD_LAZY | RTLD_LOCAL);
#endif
        }
    }
    if (!handle) return NULL;
    std::lock_guard<std::mutex> lock(g_lymarrt_lib_mutex);
    g_lymarrt_libraries[reinterpret_cast<uintptr_t>(handle)] = path;
    return handle;
}

void lymarrt_library_close(void* handle) {
    if (!handle) return;
    {
        std::lock_guard<std::mutex> lock(g_lymarrt_lib_mutex);
        auto it = g_lymarrt_libraries.find(reinterpret_cast<uintptr_t>(handle));
        if (it == g_lymarrt_libraries.end()) return;
        g_lymarrt_libraries.erase(it);
    }
#ifdef _WIN32
    FreeLibrary(static_cast<HMODULE>(handle));
#else
    dlclose(handle);
#endif
}

void* lymarrt_symbol_lookup(void* handle, const char* symbol) {
    if (!handle || !symbol) return NULL;
    std::lock_guard<std::mutex> lock(g_lymarrt_lib_mutex);
    if (g_lymarrt_libraries.find(reinterpret_cast<uintptr_t>(handle)) == g_lymarrt_libraries.end()) {
        return NULL;
    }
#ifdef _WIN32
    return reinterpret_cast<void*>(GetProcAddress(static_cast<HMODULE>(handle), symbol));
#else
    return dlsym(handle, symbol);
#endif
}

bool lymarrt_ffi_call(
    void* func_ptr,
    lymarrt_type ret_type,
    const lymarrt_type* arg_types,
    const lymarrt_value* arg_values,
    size_t num_args,
    lymarrt_value* out_result)
{
    if (!func_ptr) return false;
    std::vector<ffi_type*> ffi_arg_types(num_args);
    std::vector<void*> ffi_arg_values(num_args);
    std::vector<uint64_t> arg_storage(num_args, 0);

    for (size_t i = 0; i < num_args; ++i) {
        lymarrt_type t = arg_types ? arg_types[i] : LYMARRT_TYPE_I64;
        ffi_arg_types[i] = lymarrt_type_to_ffi(t);
        const lymarrt_value& val = arg_values[i];
        switch (t) {
            case LYMARRT_TYPE_I8:  { int8_t v = val.val.i8; std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LYMARRT_TYPE_U8:  { uint8_t v = val.val.u8; std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LYMARRT_TYPE_I16: { int16_t v = val.val.i16; std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LYMARRT_TYPE_U16: { uint16_t v = val.val.u16; std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LYMARRT_TYPE_I32: { int32_t v = val.val.i32; std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LYMARRT_TYPE_U32: { uint32_t v = val.val.u32; std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LYMARRT_TYPE_I64: { int64_t v = val.val.i64; std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LYMARRT_TYPE_U64: { uint64_t v = val.val.u64; std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LYMARRT_TYPE_F32: { float v = val.val.f32; std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LYMARRT_TYPE_F64: { double v = val.val.f64; std::memcpy(&arg_storage[i], &v, sizeof(v)); break; }
            case LYMARRT_TYPE_PTR:
            case LYMARRT_TYPE_CSTRING: { void* p = val.val.ptr; std::memcpy(&arg_storage[i], &p, sizeof(p)); break; }
            default: break;
        }
        ffi_arg_values[i] = &arg_storage[i];
    }

    ffi_cif cif;
    ffi_type* ffi_ret = lymarrt_type_to_ffi(ret_type);
    if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, (unsigned)num_args, ffi_ret, ffi_arg_types.data()) != FFI_OK) {
        return false;
    }

    uint64_t result_storage = 0;
    ffi_call(&cif, FFI_FN(func_ptr), &result_storage, ffi_arg_values.data());

    if (out_result) {
        std::memset(out_result, 0, sizeof(*out_result));
        out_result->type = ret_type;
        switch (ret_type) {
            case LYMARRT_TYPE_I8:  { int8_t v; std::memcpy(&v, &result_storage, sizeof(v)); out_result->val.i8 = v; break; }
            case LYMARRT_TYPE_U8:  { uint8_t v; std::memcpy(&v, &result_storage, sizeof(v)); out_result->val.u8 = v; break; }
            case LYMARRT_TYPE_I16: { int16_t v; std::memcpy(&v, &result_storage, sizeof(v)); out_result->val.i16 = v; break; }
            case LYMARRT_TYPE_U16: { uint16_t v; std::memcpy(&v, &result_storage, sizeof(v)); out_result->val.u16 = v; break; }
            case LYMARRT_TYPE_I32: { int32_t v; std::memcpy(&v, &result_storage, sizeof(v)); out_result->val.i32 = v; break; }
            case LYMARRT_TYPE_U32: { uint32_t v; std::memcpy(&v, &result_storage, sizeof(v)); out_result->val.u32 = v; break; }
            case LYMARRT_TYPE_I64: { int64_t v; std::memcpy(&v, &result_storage, sizeof(v)); out_result->val.i64 = v; break; }
            case LYMARRT_TYPE_U64: { uint64_t v; std::memcpy(&v, &result_storage, sizeof(v)); out_result->val.u64 = v; break; }
            case LYMARRT_TYPE_F32: { float v; std::memcpy(&v, &result_storage, sizeof(v)); out_result->val.f32 = v; break; }
            case LYMARRT_TYPE_F64: { double v; std::memcpy(&v, &result_storage, sizeof(v)); out_result->val.f64 = v; break; }
            case LYMARRT_TYPE_PTR:
            case LYMARRT_TYPE_CSTRING: { void* p; std::memcpy(&p, &result_storage, sizeof(p)); out_result->val.ptr = p; break; }
            case LYMARRT_TYPE_VOID:
            default: break;
        }
    }
    return true;
}

int64_t lymarrt_callback_create(
    lymarrt_callback_handler handler,
    void* userdata,
    const lymarrt_type* arg_types,
    size_t num_args,
    lymarrt_type ret_type)
{
    if (!handler) return 0;
    int64_t id;
    {
        std::lock_guard<std::mutex> lock(g_lymarrt_cb_mutex);
        id = g_lymarrt_next_cb_id++;
    }

    LymarrtTrampolineContext* ctx = new LymarrtTrampolineContext();
    ctx->handler  = handler;
    ctx->userdata = userdata;
    ctx->ret_type = ret_type;
    ctx->id       = id;
    if (arg_types && num_args > 0) {
        ctx->arg_types.assign(arg_types, arg_types + num_args);
    }
    for (auto t : ctx->arg_types) {
        ctx->ffi_arg_ptrs.push_back(lymarrt_type_to_ffi(t));
    }

    ffi_type* ffi_ret = lymarrt_type_to_ffi(ret_type);
    if (ffi_prep_cif(&ctx->cif, FFI_DEFAULT_ABI, (unsigned)ctx->ffi_arg_ptrs.size(), ffi_ret,
                     ctx->ffi_arg_ptrs.empty() ? NULL : ctx->ffi_arg_ptrs.data()) != FFI_OK) {
        delete ctx;
        return 0;
    }

    ctx->closure = static_cast<ffi_closure*>(ffi_closure_alloc(sizeof(ffi_closure), &ctx->code_ptr));
    if (!ctx->closure) {
        delete ctx;
        return 0;
    }

    if (ffi_prep_closure_loc(ctx->closure, &ctx->cif, lymarrt_trampoline_dispatcher, ctx, ctx->code_ptr) != FFI_OK) {
        ffi_closure_free(ctx->closure);
        delete ctx;
        return 0;
    }

    {
        std::lock_guard<std::mutex> lock(g_lymarrt_cb_mutex);
        g_lymarrt_callbacks[id] = ctx;
    }
    return id;
}

void* lymarrt_callback_get_ptr(int64_t handle) {
    if (handle <= 0) return NULL;
    std::lock_guard<std::mutex> lock(g_lymarrt_cb_mutex);
    auto it = g_lymarrt_callbacks.find(handle);
    if (it != g_lymarrt_callbacks.end()) {
        return it->second->code_ptr;
    }
    return NULL;
}

void* lymarrt_callback_get_userdata(int64_t handle) {
    if (handle <= 0) return NULL;
    std::lock_guard<std::mutex> lock(g_lymarrt_cb_mutex);
    auto it = g_lymarrt_callbacks.find(handle);
    if (it != g_lymarrt_callbacks.end()) {
        return it->second->userdata;
    }
    return NULL;
}

void lymarrt_callback_destroy(int64_t handle) {
    if (handle <= 0) return;
    LymarrtTrampolineContext* ctx = NULL;
    {
        std::lock_guard<std::mutex> lock(g_lymarrt_cb_mutex);
        auto it = g_lymarrt_callbacks.find(handle);
        if (it != g_lymarrt_callbacks.end()) {
            ctx = it->second;
            g_lymarrt_callbacks.erase(it);
        }
    }
    if (ctx) {
        if (ctx->closure) ffi_closure_free(ctx->closure);
        delete ctx;
    }
}

} // extern "C"

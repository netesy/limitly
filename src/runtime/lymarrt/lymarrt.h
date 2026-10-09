#ifndef LYMARRT_H
#define LYMARRT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Lymar Runtime ABI Versioning (0.0.1)
#define LYMARRT_ABI_VERSION 0x00000001U

typedef enum lymarrt_type {
    LYMARRT_TYPE_I8 = 0,
    LYMARRT_TYPE_U8 = 1,
    LYMARRT_TYPE_I16 = 2,
    LYMARRT_TYPE_U16 = 3,
    LYMARRT_TYPE_I32 = 4,
    LYMARRT_TYPE_U32 = 5,
    LYMARRT_TYPE_I64 = 6,
    LYMARRT_TYPE_U64 = 7,
    LYMARRT_TYPE_F32 = 8,
    LYMARRT_TYPE_F64 = 9,
    LYMARRT_TYPE_PTR = 10,
    LYMARRT_TYPE_CSTRING = 11,
    LYMARRT_TYPE_VOID = 12
} lymarrt_type;

typedef struct lymarrt_value {
    uint8_t type;
    union {
        int8_t i8;
        uint8_t u8;
        int16_t i16;
        uint16_t u16;
        int32_t i32;
        uint32_t u32;
        int64_t i64;
        uint64_t u64;
        float f32;
        double f64;
        void* ptr;
    } val;
} lymarrt_value;

// Precompiled module metadata
typedef struct lymarrt_module_info {
    uint32_t abi_version;
    const char* module_name;
    const char* build_target;
    size_t num_exports;
    const char** export_names;
} lymarrt_module_info;

// Runtime version check
uint32_t lymarrt_abi_version(void);

// Dynamic library management
void* lymarrt_library_open(const char* path);
void lymarrt_library_close(void* handle);
void* lymarrt_symbol_lookup(void* handle, const char* symbol);

// Native FFI Invocation
bool lymarrt_ffi_call(
    void* func_ptr,
    lymarrt_type ret_type,
    const lymarrt_type* arg_types,
    const lymarrt_value* arg_values,
    size_t num_args,
    lymarrt_value* out_result
);

// Callback / Trampoline Support
typedef void (*lymarrt_callback_handler)(
    void* userdata,
    const lymarrt_value* args,
    size_t num_args,
    lymarrt_value* out_result
);

int64_t lymarrt_callback_create(
    lymarrt_callback_handler handler,
    void* userdata,
    const lymarrt_type* arg_types,
    size_t num_args,
    lymarrt_type ret_type
);

void* lymarrt_callback_get_ptr(int64_t handle);
void* lymarrt_callback_get_userdata(int64_t handle);
void lymarrt_callback_destroy(int64_t handle);

#ifdef __cplusplus
}
#endif

#endif // LYMARRT_H

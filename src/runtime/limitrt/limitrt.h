#ifndef LIMITRT_H
#define LIMITRT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum limitrt_type {
    LIMITRT_TYPE_I8 = 0,
    LIMITRT_TYPE_U8 = 1,
    LIMITRT_TYPE_I16 = 2,
    LIMITRT_TYPE_U16 = 3,
    LIMITRT_TYPE_I32 = 4,
    LIMITRT_TYPE_U32 = 5,
    LIMITRT_TYPE_I64 = 6,
    LIMITRT_TYPE_U64 = 7,
    LIMITRT_TYPE_F32 = 8,
    LIMITRT_TYPE_F64 = 9,
    LIMITRT_TYPE_PTR = 10,
    LIMITRT_TYPE_CSTRING = 11,
    LIMITRT_TYPE_VOID = 12
} limitrt_type;

typedef struct limitrt_value {
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
} limitrt_value;

// Dynamic library management
void* limitrt_library_open(const char* path);
void limitrt_library_close(void* handle);
void* limitrt_symbol_lookup(void* handle, const char* symbol);

// Native FFI Invocation
bool limitrt_ffi_call(
    void* func_ptr,
    limitrt_type ret_type,
    const limitrt_type* arg_types,
    const limitrt_value* arg_values,
    size_t num_args,
    limitrt_value* out_result
);

// Callback / Trampoline Support
typedef void (*limitrt_callback_handler)(
    void* userdata,
    const limitrt_value* args,
    size_t num_args,
    limitrt_value* out_result
);

int64_t limitrt_callback_create(
    limitrt_callback_handler handler,
    void* userdata,
    const limitrt_type* arg_types,
    size_t num_args,
    limitrt_type ret_type
);

void* limitrt_callback_get_ptr(int64_t handle);
void* limitrt_callback_get_userdata(int64_t handle);
void limitrt_callback_destroy(int64_t handle);

#ifdef __cplusplus
}
#endif

#endif // LIMITRT_H

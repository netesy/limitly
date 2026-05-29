#ifndef RUNTIME_H
#define RUNTIME_H

#include <stdint.h>
#include <stdbool.h>
#include "runtime_value_base.h"
#include "runtime_string.h"

#ifndef RUNTIME_API
    #define RUNTIME_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    ObjHeader header;
    int64_t value;
} ObjI64;

typedef struct {
    ObjHeader header;
    uint64_t value;
} ObjU64;

typedef struct {
    ObjHeader header;
    uint64_t _padding;
    __int128 value;
} ObjI128;

typedef struct {
    ObjHeader header;
    uint64_t _padding;
    unsigned __int128 value;
} ObjU128;

typedef struct {
    ObjHeader header;
    double value;
} ObjFloat;

typedef struct {
    ObjHeader header;
    uint8_t type;
    union {
        int64_t as_int;
        double as_float;
        uint8_t as_bool;
        void* as_ptr;
    } value;
} LmBox;

#define LM_BOX_INT    0
#define LM_BOX_FLOAT  1
#define LM_BOX_BOOL   2
#define LM_BOX_STRING 3
#define LM_BOX_NULLPTR 4

typedef struct {
    ObjHeader header;
    char* name;
    LmValue* fields;
    int field_count;
    void* mutex;
} LmFrame;

typedef struct {
    ObjHeader header;
    LmValue function;
    LmValue captured_env;
    uint32_t captured_count;
} LmClosure;

typedef struct {
    ObjHeader header;
    void* ptr;
} ObjForeignPtr;

RUNTIME_API LmValue lm_alloc_i64(int64_t value);
RUNTIME_API LmValue lm_alloc_u64(uint64_t value);
RUNTIME_API LmValue lm_alloc_i128(__int128 value);
RUNTIME_API LmValue lm_alloc_u128(unsigned __int128 value);
RUNTIME_API LmValue lm_alloc_float(double value);
RUNTIME_API LmValue lm_alloc_foreign_ptr(void* ptr);

RUNTIME_API LmBox* lm_box_int(int64_t value);
RUNTIME_API LmBox* lm_box_float(double value);
RUNTIME_API LmBox* lm_box_bool(uint8_t value);
RUNTIME_API LmBox* lm_box_string(const char* value);
RUNTIME_API LmBox* lm_box_nullptr(void);

RUNTIME_API void* lm_frame_alloc(const char* name, int fields);
RUNTIME_API LmValue lm_frame_get_field(void* frame, int offset);
RUNTIME_API void lm_frame_set_field(void* frame, int offset, LmValue value);

#ifdef __cplusplus
}
#endif

#endif
RUNTIME_API LmValue lm_frame_get_field_atomic(void* frame, int offset);
RUNTIME_API void lm_frame_set_field_atomic(void* frame, int offset, LmValue value);

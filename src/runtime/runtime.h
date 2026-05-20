#ifndef RUNTIME_H
#define RUNTIME_H

#include <stdint.h>
#include "runtime_value_base.h"

// For static linking, define as empty
#ifndef RUNTIME_API
    #define RUNTIME_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Include all runtime sub-modules
#include "runtime_list.h"
#include "runtime_dict.h"
#include "runtime_string.h"
#include "runtime_tuple.h"

// Boxed Numeric Objects with proper alignment for 128-bit
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
    // For now simple representation
    int64_t high;
    uint64_t low;
} ObjDecimal;

// Legacy LmBox (Keeping for compatibility for now, but will transition)
typedef struct {
    ObjHeader header;
    uint8_t type;  // 0=int, 1=float, 2=bool, 3=string, 4=nullptr
    union {
        int64_t as_int;
        double as_float;
        uint8_t as_bool;
        void* as_ptr;
    } value;
} LmBox;

// Box type constants
#define LM_BOX_INT    0
#define LM_BOX_FLOAT  1
#define LM_BOX_BOOL   2
#define LM_BOX_STRING 3
#define LM_BOX_NULLPTR 4

// Runtime Object Allocation Helpers
RUNTIME_API LmValue lm_alloc_i64(int64_t value);
RUNTIME_API LmValue lm_alloc_u64(uint64_t value);
RUNTIME_API LmValue lm_alloc_i128(__int128 value);
RUNTIME_API LmValue lm_alloc_u128(unsigned __int128 value);
RUNTIME_API LmValue lm_alloc_float(double value);

// Boxing operations (legacy)
RUNTIME_API LmBox* lm_box_int(int64_t value);
RUNTIME_API LmBox* lm_box_float(double value);
RUNTIME_API LmBox* lm_box_bool(uint8_t value);
RUNTIME_API LmBox* lm_box_string(const char* value);
RUNTIME_API LmBox* lm_box_nullptr(void);

// Unboxing operations (legacy)
RUNTIME_API int64_t lm_unbox_int(LmBox* box);
RUNTIME_API double lm_unbox_float(LmBox* box);
RUNTIME_API uint8_t lm_unbox_bool(LmBox* box);
RUNTIME_API const char* lm_unbox_string(LmBox* box);
RUNTIME_API void* lm_unbox_ptr(LmBox* box);

// Memory management
RUNTIME_API void lm_box_free(LmBox* box);

// Frame runtime support
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

RUNTIME_API void* lm_frame_alloc(const char* name, int fields);
RUNTIME_API LmValue lm_frame_get_field(void* frame, int offset);
RUNTIME_API void lm_frame_set_field(void* frame, int offset, LmValue value);
RUNTIME_API LmValue lm_frame_get_field_atomic(void* frame, int offset);
RUNTIME_API void lm_frame_set_field_atomic(void* frame, int offset, LmValue value);
RUNTIME_API void lm_frame_field_atomic_add(void* frame, int offset, LmValue value);
RUNTIME_API void lm_frame_field_atomic_sub(void* frame, int offset, LmValue value);
RUNTIME_API void* lm_trait_dispatch(void* trait_obj, const char* trait_name, const char* method_name);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_H

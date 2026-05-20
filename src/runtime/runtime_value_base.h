#ifndef RUNTIME_VALUE_BASE_H
#define RUNTIME_VALUE_BASE_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Canonical runtime execution value
typedef uint64_t LmValue;
// For backward compatibility or if the name 'Value' is strictly required by the prompt instructions in some contexts,
// but we must avoid clash with Backend::Value.
// The prompt said: using Value = uint64_t;
// I will use LmValue internally in runtime and try to keep RegisterValue as Value if possible,
// but Backend::Value is a struct.

// Low-bit tags (bottom 3 bits)
#define TAG_PTR       0x0  // 000
#define TAG_INT       0x1  // 001
#define TAG_IMMEDIATE 0x2  // 010
#define TAG_MASK      0x7

// Immediate values
#define VAL_NIL       ((LmValue)(0 << 3) | TAG_IMMEDIATE)
#define VAL_FALSE     ((LmValue)(1 << 3) | TAG_IMMEDIATE)
#define VAL_TRUE      ((LmValue)(2 << 3) | TAG_IMMEDIATE)

// Header for all heap-allocated objects
typedef struct {
    uint32_t type_id;
    uint32_t metadata;  // Length, GC marks, flags, etc.
} ObjHeader;

#define TYPE_BOX      0
#define TYPE_LIST     1
#define TYPE_DICT     2
#define TYPE_TUPLE    3
#define TYPE_FRAME    4
#define TYPE_I64      5
#define TYPE_U64      6
#define TYPE_I128     7
#define TYPE_U128     8
#define TYPE_FLOAT    9
#define TYPE_DECIMAL  10
#define TYPE_STRING   11
#define TYPE_CLOSURE  12

// SMI (Small Integer) Constants - 61-bit signed
#define MAX_SMI ((int64_t)((1ULL << 60) - 1))
#define MIN_SMI (-(int64_t)(1ULL << 60))

static inline bool fits_smi_i64(int64_t v) {
    return v >= MIN_SMI && v <= MAX_SMI;
}

static inline bool fits_smi_u64(uint64_t v) {
    return v <= (uint64_t)MAX_SMI;
}

// Boxing/Unboxing Macros
#define BOX_INT(i)   ((LmValue)(((int64_t)(i)) << 3) | TAG_INT)
#define UNBOX_INT(v) ((int64_t)(((int64_t)(v)) >> 3))
#define IS_INT(v)    (((v) & TAG_MASK) == TAG_INT)

#define BOX_PTR(p)   ((LmValue)(p))
#define UNBOX_PTR(v) ((void*)((uintptr_t)(v) & ~TAG_MASK))
#define IS_PTR(v)    (((v) & TAG_MASK) == TAG_PTR && (v) != 0)

#define IS_NIL(v)    ((v) == VAL_NIL)
#define IS_BOOL(v)   (((v) == VAL_FALSE) || ((v) == VAL_TRUE))
#define UNBOX_BOOL(v) ((v) == VAL_TRUE)

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_VALUE_BASE_H

#ifndef RUNTIME_VALUE_BASE_H
#define RUNTIME_VALUE_BASE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Low-bit tags (bottom 3 bits)
#define TAG_PTR       0x0  // 000
#define TAG_INT       0x1  // 001
#define TAG_IMMEDIATE 0x2  // 010
#define TAG_MASK      0x7

// Immediate values
#define VAL_NIL       ((0 << 3) | TAG_IMMEDIATE)
#define VAL_FALSE     ((1 << 3) | TAG_IMMEDIATE)
#define VAL_TRUE      ((2 << 3) | TAG_IMMEDIATE)

// Header for all heap-allocated objects
typedef struct {
    uint32_t type_id;   // 1 = List, 2 = Record/Dict, 3 = Tuple, 4 = Frame/Object
    uint32_t metadata;  // Length, GC marks, flags, etc.
} ObjHeader;

#define TYPE_LIST   1
#define TYPE_DICT   2
#define TYPE_TUPLE  3
#define TYPE_FRAME  4
#define TYPE_BOX    0

// Boxing/Unboxing Macros
// Shift by 3 to preserve 3-bit tag
#define BOX_INT(i)   ((((int64_t)(i)) << 3) | TAG_INT)
#define UNBOX_INT(v) ((int64_t)(((int64_t)(v)) >> 3))
#define IS_INT(v)    (((v) & TAG_MASK) == TAG_INT)

#define BOX_PTR(p)   ((uint64_t)(p)) // Assuming 8-byte alignment, bottom bits are 0
#define UNBOX_PTR(v) ((void*)((uintptr_t)(v) & ~TAG_MASK))
#define IS_PTR(v)    (((v) & TAG_MASK) == TAG_PTR && (v) != 0)

#define IS_NIL(v)    ((v) == VAL_NIL)
#define IS_BOOL(v)   (((v) == VAL_FALSE) || ((v) == VAL_TRUE))
#define UNBOX_BOOL(v) ((v) == VAL_TRUE)

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_VALUE_BASE_H

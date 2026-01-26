#ifndef RUNTIME_TUPLE_H
#define RUNTIME_TUPLE_H

#include <stdint.h>

// For static linking, define as empty
#ifndef RUNTIME_API
    #define RUNTIME_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Complete tuple structure - fixed size array of boxed values
typedef struct {
    uint64_t magic;      // Magic number for safe type detection: 0x4C6D5475 ("LmTu")
    void** elements;
    uint64_t size;
    uint64_t capacity;
} LmTuple;

// Magic number for tuple detection
#define LM_TUPLE_MAGIC 0x4C6D5475ULL  // "LmTu" in hex

// Complete tuple operations
RUNTIME_API LmTuple* lm_tuple_new(uint64_t size);
RUNTIME_API LmTuple* lm_tuple_new_with_values(uint64_t size, void** values);  // Create with initial values
RUNTIME_API void lm_tuple_set(LmTuple* tuple, uint64_t index, void* value);
RUNTIME_API void* lm_tuple_get(LmTuple* tuple, uint64_t index);
RUNTIME_API uint64_t lm_tuple_size(LmTuple* tuple);  // Get current size
RUNTIME_API uint64_t lm_tuple_capacity(LmTuple* tuple);  // Get capacity
RUNTIME_API void lm_tuple_resize(LmTuple* tuple, uint64_t new_size);  // Resize tuple
RUNTIME_API void lm_tuple_append(LmTuple* tuple, void* value);  // Append value
RUNTIME_API void lm_tuple_clear(LmTuple* tuple);  // Clear all elements
RUNTIME_API void lm_tuple_free(LmTuple* tuple);

// Tuple iteration support
typedef struct {
    LmTuple* tuple;
    uint64_t current_index;
} LmTupleIterator;

RUNTIME_API LmTupleIterator* lm_tuple_iterator_new(LmTuple* tuple);
RUNTIME_API void* lm_tuple_iterator_next(LmTupleIterator* iterator);  // Get next value
RUNTIME_API uint8_t lm_tuple_iterator_has_next(LmTupleIterator* iterator);  // Check if more values
RUNTIME_API void lm_tuple_iterator_free(LmTupleIterator* iterator);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_TUPLE_H

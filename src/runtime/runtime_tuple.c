#include "runtime_tuple.h"
#include <stdlib.h>
#include <string.h>

RUNTIME_API LmTuple* lm_tuple_new(uint64_t size) {
    LmTuple* tuple = (LmTuple*)malloc(sizeof(LmTuple));
    if (!tuple) return NULL;
    
    tuple->elements = (void**)malloc(sizeof(void*) * size);
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }
    
    tuple->size = size;  // Set size correctly
    tuple->capacity = size;
    
    // Initialize all elements to NULL
    memset(tuple->elements, 0, sizeof(void*) * size);
    
    return tuple;
}

RUNTIME_API LmTuple* lm_tuple_new_with_values(uint64_t size, void** values) {
    LmTuple* tuple = lm_tuple_new(size);
    if (!tuple) return NULL;
    
    // Copy initial values
    for (uint64_t i = 0; i < size; i++) {
        tuple->elements[i] = values[i];
        tuple->size++;
    }
    
    return tuple;
}

RUNTIME_API void lm_tuple_set(LmTuple* tuple, uint64_t index, void* value) {
    if (!tuple || !tuple->elements || index >= tuple->capacity) {
        return;
    }
    
    // Ensure we have capacity
    if (index >= tuple->capacity) {
        // Resize to accommodate new index
        uint64_t new_capacity = tuple->capacity * 2;
        while (new_capacity <= index) {
            new_capacity *= 2;
        }
        
        void** new_elements = (void**)realloc(tuple->elements, sizeof(void*) * new_capacity);
        if (!new_elements) return;
        
        tuple->elements = new_elements;
        tuple->capacity = new_capacity;
    }
    
    tuple->elements[index] = value;
    
    // Update size if this is a new element
    if (index >= tuple->size) {
        tuple->size = index + 1;
    }
}

RUNTIME_API void* lm_tuple_get(LmTuple* tuple, uint64_t index) {
    if (!tuple || !tuple->elements || index >= tuple->size) {
        return NULL;
    }
    return tuple->elements[index];
}

RUNTIME_API uint64_t lm_tuple_size(LmTuple* tuple) {
    return tuple ? tuple->size : 0;
}

RUNTIME_API uint64_t lm_tuple_capacity(LmTuple* tuple) {
    return tuple ? tuple->capacity : 0;
}

RUNTIME_API void lm_tuple_resize(LmTuple* tuple, uint64_t new_size) {
    if (!tuple) return;
    
    if (new_size > tuple->capacity) {
        void** new_elements = (void**)realloc(tuple->elements, sizeof(void*) * new_size);
        if (new_elements) {
            tuple->elements = new_elements;
            tuple->capacity = new_size;
        }
    }
    
    // Adjust size if shrinking
    if (new_size < tuple->size) {
        tuple->size = new_size;
    }
}

RUNTIME_API void lm_tuple_append(LmTuple* tuple, void* value) {
    if (!tuple) return;
    
    uint64_t index = tuple->size;
    lm_tuple_set(tuple, index, value);
}

RUNTIME_API void lm_tuple_clear(LmTuple* tuple) {
    if (!tuple) return;
    
    if (tuple->elements) {
        // Clear elements but keep memory
        memset(tuple->elements, 0, sizeof(void*) * tuple->capacity);
        tuple->size = 0;
    }
}

RUNTIME_API void lm_tuple_free(LmTuple* tuple) {
    if (tuple) {
        if (tuple->elements) {
            free(tuple->elements);
        }
        free(tuple);
    }
}

// Iterator implementation
RUNTIME_API LmTupleIterator* lm_tuple_iterator_new(LmTuple* tuple) {
    if (!tuple) return NULL;
    
    LmTupleIterator* iterator = (LmTupleIterator*)malloc(sizeof(LmTupleIterator));
    if (!iterator) return NULL;
    
    iterator->tuple = tuple;
    iterator->current_index = 0;
    return iterator;
}

RUNTIME_API void* lm_tuple_iterator_next(LmTupleIterator* iterator) {
    if (!iterator || !iterator->tuple || iterator->current_index >= iterator->tuple->size) {
        return NULL;
    }
    
    return iterator->tuple->elements[iterator->current_index++];
}

RUNTIME_API uint8_t lm_tuple_iterator_has_next(LmTupleIterator* iterator) {
    return iterator && iterator->tuple && iterator->current_index < iterator->tuple->size;
}

RUNTIME_API void lm_tuple_iterator_free(LmTupleIterator* iterator) {
    if (iterator) {
        free(iterator);
    }
}

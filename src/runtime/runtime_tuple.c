#include "runtime_tuple.h"
#include <stdlib.h>
#include <string.h>

RUNTIME_API LmTuple* lm_tuple_new(uint64_t size) {
    LmTuple* tuple = (LmTuple*)malloc(sizeof(LmTuple));
    if (!tuple) return NULL;
    
    tuple->elements = (LmValue*)malloc(sizeof(LmValue) * size);
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }
    
    tuple->header.type_id = TYPE_TUPLE;
    tuple->header.metadata = 0;
    tuple->size = size;
    tuple->capacity = size;
    
    for (uint64_t i = 0; i < size; i++) tuple->elements[i] = VAL_NIL;
    
    return tuple;
}

RUNTIME_API LmTuple* lm_tuple_new_with_values(uint64_t size, LmValue* values) {
    LmTuple* tuple = lm_tuple_new(size);
    if (!tuple) return NULL;
    
    for (uint64_t i = 0; i < size; i++) {
        tuple->elements[i] = values[i];
    }
    tuple->size = size;
    
    return tuple;
}

RUNTIME_API void lm_tuple_set(LmTuple* tuple, uint64_t index, LmValue value) {
    if (!tuple || !tuple->elements || index >= tuple->capacity) {
        return;
    }
    
    tuple->elements[index] = value;
    if (index >= tuple->size) {
        tuple->size = index + 1;
    }
}

RUNTIME_API LmValue lm_tuple_get(LmTuple* tuple, uint64_t index) {
    if (!tuple || !tuple->elements || index >= tuple->size) {
        return VAL_NIL;
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
        LmValue* new_elements = (LmValue*)realloc(tuple->elements, sizeof(LmValue) * new_size);
        if (new_elements) {
            for (uint64_t i = tuple->capacity; i < new_size; i++) new_elements[i] = VAL_NIL;
            tuple->elements = new_elements;
            tuple->capacity = new_size;
        }
    }
    
    if (new_size < tuple->size) {
        tuple->size = new_size;
    }
}

RUNTIME_API void lm_tuple_append(LmTuple* tuple, LmValue value) {
    if (!tuple) return;
    if (tuple->size >= tuple->capacity) {
        lm_tuple_resize(tuple, tuple->capacity == 0 ? 8 : tuple->capacity * 2);
    }
    tuple->elements[tuple->size++] = value;
}

RUNTIME_API void lm_tuple_clear(LmTuple* tuple) {
    if (!tuple) return;
    for (uint64_t i = 0; i < tuple->size; i++) tuple->elements[i] = VAL_NIL;
    tuple->size = 0;
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

RUNTIME_API LmValue lm_tuple_iterator_next(LmTupleIterator* iterator) {
    if (!iterator || !iterator->tuple || iterator->current_index >= iterator->tuple->size) {
        return VAL_NIL;
    }
    return iterator->tuple->elements[iterator->current_index++];
}

RUNTIME_API uint8_t lm_tuple_iterator_has_next(LmTupleIterator* iterator) {
    return iterator && iterator->tuple && iterator->current_index < iterator->tuple->size;
}

RUNTIME_API void lm_tuple_iterator_free(LmTupleIterator* iterator) {
    if (iterator) free(iterator);
}

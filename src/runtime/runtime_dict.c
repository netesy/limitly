#define BUILDING_RUNTIME
#include "runtime_dict.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INITIAL_BUCKET_COUNT 16

RUNTIME_API LmDict* lm_dict_new(uint64_t (*hash_fn)(void*), 
                                 int (*cmp_fn)(void*, void*)) {
    LmDict* dict = (LmDict*)malloc(sizeof(LmDict));
    if (!dict) return NULL;
    
    dict->bucket_count = INITIAL_BUCKET_COUNT;
    dict->size = 0;
    dict->hash_fn = hash_fn;
    dict->cmp_fn = cmp_fn;
    
    dict->buckets = (LmDictEntry**)calloc(dict->bucket_count, 
                                           sizeof(LmDictEntry*));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }
    
    return dict;
}

RUNTIME_API void lm_dict_set(LmDict* dict, void* key, void* value) {
    if (!dict || !key) return;
    
    uint64_t hash = dict->hash_fn(key);
    uint64_t bucket = hash % dict->bucket_count;
    
    // Check if key already exists
    LmDictEntry* entry = dict->buckets[bucket];
    while (entry) {
        if (entry->hash == hash && dict->cmp_fn(entry->key, key) == 0) {
            entry->value = value;
            return;
        }
        entry = entry->next;
    }
    
    // Create new entry
    LmDictEntry* new_entry = (LmDictEntry*)malloc(sizeof(LmDictEntry));
    if (!new_entry) return;
    
    new_entry->key = key;
    new_entry->value = value;
    new_entry->hash = hash;
    new_entry->next = dict->buckets[bucket];
    dict->buckets[bucket] = new_entry;
    dict->size++;
}

RUNTIME_API void* lm_dict_get(LmDict* dict, void* key) {
    if (!dict || !key) return NULL;
    
    uint64_t hash = dict->hash_fn(key);
    uint64_t bucket = hash % dict->bucket_count;
    
    LmDictEntry* entry = dict->buckets[bucket];
    while (entry) {
        if (entry->hash == hash && dict->cmp_fn(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    
    return NULL;
}

RUNTIME_API int lm_dict_contains(LmDict* dict, void* key) {
    return lm_dict_get(dict, key) != NULL;
}

RUNTIME_API void lm_dict_free(LmDict* dict) {
    if (!dict) return;
    
    for (uint64_t i = 0; i < dict->bucket_count; i++) {
        LmDictEntry* entry = dict->buckets[i];
        while (entry) {
            LmDictEntry* next = entry->next;
            free(entry);
            entry = next;
        }
    }
    
    free(dict->buckets);
    free(dict);
}

RUNTIME_API void** lm_dict_items(LmDict* dict, uint64_t* out_count) {
    if (!dict || dict->size == 0) {
        *out_count = 0;
        return NULL;
    }
    
    // Allocate array for (key, value) pairs - 2 pointers per entry
    void** items = (void**)malloc(sizeof(void*) * dict->size * 2);
    if (!items) {
        *out_count = 0;
        return NULL;
    }
    
    uint64_t index = 0;
    for (uint64_t i = 0; i < dict->bucket_count; i++) {
        LmDictEntry* entry = dict->buckets[i];
        while (entry) {
            items[index * 2] = entry->key;      // Even indices: keys
            items[index * 2 + 1] = entry->value; // Odd indices: values
            index++;
            entry = entry->next;
        }
    }
    
    *out_count = dict->size;
    return items;
}

RUNTIME_API uint64_t lm_hash_int(void* key) {
    int64_t k = (int64_t)key;
    return (uint64_t)(k * 2654435761ULL);
}

RUNTIME_API uint64_t lm_hash_string(void* key) {
    const char* str = (const char*)key;
    uint64_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

RUNTIME_API int lm_cmp_int(void* k1, void* k2) {
    int64_t i1 = (int64_t)k1;
    int64_t i2 = (int64_t)k2;
    return (i1 > i2) - (i1 < i2);
}

RUNTIME_API int lm_cmp_string(void* k1, void* k2) {
    return strcmp((const char*)k1, (const char*)k2);
}

// Include boxing definitions for boxed value functions
#include "runtime.h"

// Hash function for boxed values (used by both VM and JIT)
RUNTIME_API uint64_t hash_boxed_value(void* key) {
    if (!key) return 0;
    LmBox* box = (LmBox*)key;
    
    switch (box->type) {
        case LM_BOX_INT:
            return lm_hash_int((void*)(intptr_t)box->value.as_int);
        case LM_BOX_STRING: {
            const char* str = lm_unbox_string(box);
            return lm_hash_string((void*)str);
        }
        case LM_BOX_FLOAT: {
            int64_t int_val = (int64_t)box->value.as_float;
            return lm_hash_int((void*)(intptr_t)int_val);
        }
        case LM_BOX_BOOL:
            return lm_hash_int((void*)(intptr_t)box->value.as_bool);
        default:
            return 0;
    }
}

// Compare function for boxed values (used by both VM and JIT)
RUNTIME_API int cmp_boxed_value(void* k1, void* k2) {
    if (!k1 || !k2) return (k1 != k2) ? 1 : 0;
    
    LmBox* box1 = (LmBox*)k1;
    LmBox* box2 = (LmBox*)k2;
    
    // Different types are not equal
    if (box1->type != box2->type) return 1;
    
    switch (box1->type) {
        case LM_BOX_INT:
            return lm_cmp_int((void*)(intptr_t)box1->value.as_int,
                            (void*)(intptr_t)box2->value.as_int);
        case LM_BOX_STRING: {
            const char* str1 = lm_unbox_string(box1);
            const char* str2 = lm_unbox_string(box2);
            return lm_cmp_string((void*)str1, (void*)str2);
        }
        case LM_BOX_FLOAT: {
            double diff = box1->value.as_float - box2->value.as_float;
            return (diff > 0) - (diff < 0);
        }
        case LM_BOX_BOOL:
            return (box1->value.as_bool > box2->value.as_bool) - 
                   (box1->value.as_bool < box2->value.as_bool);
        default:
            return 0;
    }
}

// Wrapper function for JIT to create dicts with proper hash/compare functions
RUNTIME_API void* jit_dict_new(void) {
    return lm_dict_new(hash_boxed_value, cmp_boxed_value);
}

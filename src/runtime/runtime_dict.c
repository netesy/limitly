#define BUILDING_RUNTIME
#include "runtime_dict.h"
#include "runtime_value.h"
#include "runtime.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INITIAL_BUCKET_COUNT 16

RUNTIME_API LmDict* lm_dict_new(uint64_t (*hash_fn)(LmValue),
                                 int (*cmp_fn)(LmValue, LmValue)) {
    LmDict* dict = (LmDict*)malloc(sizeof(LmDict));
    if (!dict) return NULL;
    
    dict->header.type_id = TYPE_DICT;
    dict->header.metadata = 0;
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

RUNTIME_API void lm_dict_set(LmDict* dict, LmValue key, LmValue value) {
    if (!dict) return;
    
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

RUNTIME_API LmValue lm_dict_get(LmDict* dict, LmValue key) {
    if (!dict) return VAL_NIL;
    
    uint64_t hash = dict->hash_fn(key);
    uint64_t bucket = hash % dict->bucket_count;
    
    LmDictEntry* entry = dict->buckets[bucket];
    while (entry) {
        if (entry->hash == hash && dict->cmp_fn(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    
    return VAL_NIL;
}

RUNTIME_API int lm_dict_contains(LmDict* dict, LmValue key) {
    return lm_dict_get(dict, key) != VAL_NIL;
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

RUNTIME_API LmValue* lm_dict_items(LmDict* dict, uint64_t* out_count) {
    if (!dict || dict->size == 0) {
        *out_count = 0;
        return NULL;
    }
    
    LmValue* items = (LmValue*)malloc(sizeof(LmValue) * dict->size * 2);
    if (!items) {
        *out_count = 0;
        return NULL;
    }
    
    uint64_t index = 0;
    for (uint64_t i = 0; i < dict->bucket_count; i++) {
        LmDictEntry* entry = dict->buckets[i];
        while (entry) {
            items[index * 2] = entry->key;
            items[index * 2 + 1] = entry->value;
            index++;
            entry = entry->next;
        }
    }
    
    *out_count = dict->size;
    return items;
}

RUNTIME_API uint64_t lm_hash_int(LmValue key) {
    int64_t k = as_i64(key);
    return (uint64_t)(k * 2654435761ULL);
}

RUNTIME_API uint64_t lm_hash_string(LmValue key) {
    if (!IS_PTR(key)) return 0;
    LmBox* box = (LmBox*)UNBOX_PTR(key);
    if (box->header.type_id != TYPE_BOX || box->type != LM_BOX_STRING) return 0;
    const char* str = (const char*)box->value.as_ptr;
    uint64_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

RUNTIME_API int lm_cmp_int(LmValue k1, LmValue k2) {
    __int128 i1 = as_i128(k1);
    __int128 i2 = as_i128(k2);
    return (i1 > i2) - (i1 < i2);
}

RUNTIME_API int lm_cmp_string(LmValue k1, LmValue k2) {
    if (!IS_PTR(k1) || !IS_PTR(k2)) return (k1 > k2) - (k1 < k2);
    LmBox* b1 = (LmBox*)UNBOX_PTR(k1);
    LmBox* b2 = (LmBox*)UNBOX_PTR(k2);
    if (b1->header.type_id != TYPE_BOX || b1->type != LM_BOX_STRING) return 1;
    if (b2->header.type_id != TYPE_BOX || b2->type != LM_BOX_STRING) return -1;
    return strcmp((const char*)b1->value.as_ptr, (const char*)b2->value.as_ptr);
}

RUNTIME_API uint64_t hash_boxed_value(LmValue key) {
    if (is_integer(key)) return lm_hash_int(key);
    if (IS_BOOL(key)) return lm_hash_int(key);
    if (IS_NIL(key)) return 0;
    if (IS_PTR(key)) {
        ObjHeader* h = (ObjHeader*)UNBOX_PTR(key);
        if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) return lm_hash_string(key);
        return (uint64_t)h;
    }
    return (uint64_t)key;
}

RUNTIME_API int cmp_boxed_value(LmValue k1, LmValue k2) {
    return lm_value_eq(k1, k2) ? 0 : (k1 > k2 ? 1 : -1);
}

RUNTIME_API void* jit_dict_new(void) {
    return lm_dict_new(hash_boxed_value, cmp_boxed_value);
}

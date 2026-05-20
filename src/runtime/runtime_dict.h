#ifndef RUNTIME_DICT_H
#define RUNTIME_DICT_H

#include <stdint.h>
#include "runtime_value_base.h"

// For static linking, define as empty
#ifndef RUNTIME_API
    #define RUNTIME_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LmDictEntry {
    LmValue key;
    LmValue value;
    uint64_t hash;
    struct LmDictEntry* next;
} LmDictEntry;

typedef struct {
    ObjHeader header;
    LmDictEntry** buckets;
    uint64_t bucket_count;
    uint64_t size;
    uint64_t (*hash_fn)(LmValue key);
    int (*cmp_fn)(LmValue k1, LmValue k2);
} LmDict;

// Dict operations
RUNTIME_API LmDict* lm_dict_new(uint64_t (*hash_fn)(LmValue),
                                 int (*cmp_fn)(LmValue, LmValue));
RUNTIME_API void lm_dict_set(LmDict* dict, LmValue key, LmValue value);
RUNTIME_API LmValue lm_dict_get(LmDict* dict, LmValue key);
RUNTIME_API LmValue* lm_dict_items(LmDict* dict, uint64_t* out_count);
RUNTIME_API int lm_dict_contains(LmDict* dict, LmValue key);
RUNTIME_API void lm_dict_free(LmDict* dict);

// Built-in hash functions for common types
RUNTIME_API uint64_t lm_hash_int(LmValue key);
RUNTIME_API uint64_t lm_hash_string(LmValue key);
RUNTIME_API int lm_cmp_int(LmValue k1, LmValue k2);
RUNTIME_API int lm_cmp_string(LmValue k1, LmValue k2);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_DICT_H

// Boxed value hash and compare functions (used by both VM and JIT)
RUNTIME_API uint64_t hash_boxed_value(LmValue key);
RUNTIME_API int cmp_boxed_value(LmValue k1, LmValue k2);

// Wrapper function for JIT to create dicts with proper hash/compare functions
RUNTIME_API void* jit_dict_new(void);

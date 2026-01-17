#ifndef RUNTIME_DICT_H
#define RUNTIME_DICT_H

#include <stdint.h>


// For static linking, define as empty
#ifndef RUNTIME_API
    #define RUNTIME_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LmDictEntry {
    void* key;
    void* value;
    uint64_t hash;
    struct LmDictEntry* next;
} LmDictEntry;

typedef struct {
    LmDictEntry** buckets;
    uint64_t bucket_count;
    uint64_t size;
    uint64_t (*hash_fn)(void* key);
    int (*cmp_fn)(void* k1, void* k2);
} LmDict;

// Dict operations
RUNTIME_API LmDict* lm_dict_new(uint64_t (*hash_fn)(void*), 
                                 int (*cmp_fn)(void*, void*));
RUNTIME_API void lm_dict_set(LmDict* dict, void* key, void* value);
RUNTIME_API void* lm_dict_get(LmDict* dict, void* key);
RUNTIME_API void** lm_dict_items(LmDict* dict, uint64_t* out_count);
RUNTIME_API int lm_dict_contains(LmDict* dict, void* key);
RUNTIME_API void lm_dict_free(LmDict* dict);

// Built-in hash functions for common types
RUNTIME_API uint64_t lm_hash_int(void* key);
RUNTIME_API uint64_t lm_hash_string(void* key);
RUNTIME_API int lm_cmp_int(void* k1, void* k2);
RUNTIME_API int lm_cmp_string(void* k1, void* k2);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_DICT_H

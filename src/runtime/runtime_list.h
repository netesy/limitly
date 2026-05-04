#ifndef RUNTIME_LIST_H
#define RUNTIME_LIST_H

#include <stdint.h>
#include <stdlib.h>

// For static linking, define as empty
#ifndef RUNTIME_API
    #define RUNTIME_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Magic number for list detection
#define LM_LIST_MAGIC  0x4C6D4C69ULL  // "LmLi" in hex

// Generic list structure (stores void pointers)
typedef struct {
    uint64_t magic;
    void** data;
    uint64_t size;
    uint64_t capacity;
} LmList;

// List operations
RUNTIME_API LmList* lm_list_new(void);
RUNTIME_API void lm_list_append(LmList* list, void* element);
RUNTIME_API void* lm_list_get(LmList* list, uint64_t index);
RUNTIME_API void lm_list_set(LmList* list, uint64_t index, void* element);
RUNTIME_API uint64_t lm_list_len(LmList* list);
RUNTIME_API void lm_list_free(LmList* list);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_LIST_H

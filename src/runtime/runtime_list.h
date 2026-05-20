#ifndef RUNTIME_LIST_H
#define RUNTIME_LIST_H

#include <stdint.h>
#include <stdlib.h>
#include "runtime_value_base.h"

// For static linking, define as empty
#ifndef RUNTIME_API
    #define RUNTIME_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Generic list structure (stores Values)
typedef struct {
    ObjHeader header;
    LmValue* data;
    uint64_t size;
    uint64_t capacity;
} LmList;

// List operations
RUNTIME_API LmList* lm_list_new(void);
RUNTIME_API void lm_list_append(LmList* list, LmValue element);
RUNTIME_API LmValue lm_list_get(LmList* list, uint64_t index);
RUNTIME_API void lm_list_set(LmList* list, uint64_t index, LmValue element);
RUNTIME_API uint64_t lm_list_len(LmList* list);
RUNTIME_API void lm_list_free(LmList* list);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_LIST_H

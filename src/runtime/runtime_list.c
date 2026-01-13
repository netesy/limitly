#define BUILDING_RUNTIME
#include "runtime_list.h"
#include <string.h>

RUNTIME_API LmList* lm_list_new(void) {
    LmList* list = (LmList*)malloc(sizeof(LmList));
    if (!list) return NULL;
    
    list->capacity = 8;
    list->size = 0;
    list->data = (void**)malloc(sizeof(void*) * list->capacity);
    if (!list->data) {
        free(list);
        return NULL;
    }
    
    return list;
}

RUNTIME_API void lm_list_append(LmList* list, void* element) {
    if (!list) return;
    
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        void** new_data = (void**)realloc(list->data, 
                                          sizeof(void*) * list->capacity);
        if (!new_data) return;
        list->data = new_data;
    }
    
    list->data[list->size++] = element;
}

RUNTIME_API void* lm_list_get(LmList* list, uint64_t index) {
    if (!list || index >= list->size) return NULL;
    return list->data[index];
}

RUNTIME_API void lm_list_set(LmList* list, uint64_t index, void* element) {
    if (!list || index >= list->size) return;
    list->data[index] = element;
}

RUNTIME_API uint64_t lm_list_len(LmList* list) {
    return list ? list->size : 0;
}

RUNTIME_API void lm_list_free(LmList* list) {
    if (!list) return;
    if (list->data) free(list->data);
    free(list);
}

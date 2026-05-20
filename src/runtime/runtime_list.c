#define BUILDING_RUNTIME
#include "runtime_list.h"
#include <string.h>

RUNTIME_API LmList* lm_list_new(void) {
    LmList* list = (LmList*)malloc(sizeof(LmList));
    if (!list) return NULL;
    
    list->header.type_id = TYPE_LIST;
    list->header.metadata = 0;
    list->capacity = 8;
    list->size = 0;
    list->data = (LmValue*)malloc(sizeof(LmValue) * list->capacity);
    if (!list->data) {
        free(list);
        return NULL;
    }
    
    return list;
}

RUNTIME_API void lm_list_append(LmList* list, LmValue element) {
    if (!list) return;
    
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        LmValue* new_data = (LmValue*)realloc(list->data,
                                          sizeof(LmValue) * list->capacity);
        if (!new_data) return;
        list->data = new_data;
    }
    
    list->data[list->size++] = element;
}

RUNTIME_API LmValue lm_list_get(LmList* list, uint64_t index) {
    if (!list || index >= list->size) return VAL_NIL;
    return list->data[index];
}

RUNTIME_API void lm_list_set(LmList* list, uint64_t index, LmValue element) {
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

#define BUILDING_RUNTIME
#include "runtime.h"
#include <stdlib.h>
#include <string.h>

RUNTIME_API LmBox* lm_box_int(int64_t value) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    
    box->type = LM_BOX_INT;
    box->value.as_int = value;
    return box;
}

RUNTIME_API LmBox* lm_box_float(double value) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    
    box->type = LM_BOX_FLOAT;
    box->value.as_float = value;
    return box;
}

RUNTIME_API LmBox* lm_box_bool(uint8_t value) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    
    box->type = LM_BOX_BOOL;
    box->value.as_bool = value;
    return box;
}

RUNTIME_API LmBox* lm_box_string(const char* value) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    
    box->type = LM_BOX_STRING;
    box->value.as_ptr = (void*)value;
    return box;
}

RUNTIME_API LmBox* lm_box_nullptr(void) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    
    box->type = LM_BOX_NULLPTR;
    box->value.as_ptr = NULL;
    return box;
}

RUNTIME_API int64_t lm_unbox_int(LmBox* box) {
    if (!box || box->type != LM_BOX_INT) return 0;
    return box->value.as_int;
}

RUNTIME_API double lm_unbox_float(LmBox* box) {
    if (!box || box->type != LM_BOX_FLOAT) return 0.0;
    return box->value.as_float;
}

RUNTIME_API uint8_t lm_unbox_bool(LmBox* box) {
    if (!box || box->type != LM_BOX_BOOL) return 0;
    return box->value.as_bool;
}

RUNTIME_API const char* lm_unbox_string(LmBox* box) {
    if (!box || box->type != LM_BOX_STRING) return "";
    return (const char*)box->value.as_ptr;
}

RUNTIME_API void* lm_unbox_ptr(LmBox* box) {
    if (!box) return NULL;
    return box->value.as_ptr;
}

RUNTIME_API void lm_box_free(LmBox* box) {
    if (!box) return;
    
    // Free string data if it's a string
    if (box->type == LM_BOX_STRING && box->value.as_ptr) {
        free(box->value.as_ptr);
    }
    
    free(box);
}

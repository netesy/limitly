#define BUILDING_RUNTIME
#define _POSIX_C_SOURCE 200809L
#include "runtime.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

RUNTIME_API void lm_print_int(int64_t val) {
    printf("%ld\n", val);
}

RUNTIME_API void lm_print_string(const char* val) {
    if (val) printf("%s\n", val);
}

RUNTIME_API void lm_print_box(LmBox* box) {
    if (!box) {
        printf("null\n");
        return;
    }
    switch (box->type) {
        case LM_BOX_INT: printf("%ld\n", box->value.as_int); break;
        case LM_BOX_FLOAT: printf("%f\n", box->value.as_float); break;
        case LM_BOX_BOOL: printf("%s\n", box->value.as_bool ? "true" : "false"); break;
        case LM_BOX_STRING: printf("%s\n", (char*)box->value.as_ptr); break;
        case LM_BOX_NULLPTR: printf("null\n"); break;
        default: printf("<unknown box type %d>\n", box->type);
    }
}

RUNTIME_API void lm_assert(int condition, const char* message) {
    if (!condition) {
        fprintf(stderr, "Assertion failed: %s\n", message ? message : "unnamed assertion");
        abort();
    }
}

RUNTIME_API LmBox* lm_box_int(int64_t value) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    box->header.type_id = TYPE_BOX; 
    box->header.metadata = 0;
    box->type = LM_BOX_INT;
    box->value.as_int = value;
    return box;
}

RUNTIME_API LmBox* lm_box_float(double value) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    box->header.type_id = TYPE_BOX;
    box->header.metadata = 0;
    box->type = LM_BOX_FLOAT;
    box->value.as_float = value;
    return box;
}

RUNTIME_API LmBox* lm_box_bool(uint8_t value) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    box->header.type_id = TYPE_BOX;
    box->header.metadata = 0;
    box->type = LM_BOX_BOOL;
    box->value.as_bool = value;
    return box;
}

RUNTIME_API LmBox* lm_box_string(const char* value) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    box->header.type_id = TYPE_BOX;
    box->header.metadata = 0;
    box->type = LM_BOX_STRING;
    box->value.as_ptr = value ? strdup(value) : NULL;
    return box;
}

RUNTIME_API LmBox* lm_box_nullptr(void) {
    LmBox* box = (LmBox*)malloc(sizeof(LmBox));
    if (!box) return NULL;
    box->header.type_id = TYPE_BOX;
    box->header.metadata = 0;
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
    if (box->type == LM_BOX_STRING && box->value.as_ptr) {
        free(box->value.as_ptr);
    }
    free(box);
}

RUNTIME_API LmValue lm_alloc_i64(int64_t value) {
    ObjI64* obj = (ObjI64*)malloc(sizeof(ObjI64));
    if (!obj) return VAL_NIL;
    obj->header.type_id = TYPE_I64;
    obj->header.metadata = 0;
    obj->value = value;
    return BOX_PTR(obj);
}

RUNTIME_API LmValue lm_alloc_u64(uint64_t value) {
    ObjU64* obj = (ObjU64*)malloc(sizeof(ObjU64));
    if (!obj) return VAL_NIL;
    obj->header.type_id = TYPE_U64;
    obj->header.metadata = 0;
    obj->value = value;
    return BOX_PTR(obj);
}

RUNTIME_API LmValue lm_alloc_i128(__int128 value) {
    ObjI128* obj = (ObjI128*)malloc(sizeof(ObjI128));
    if (!obj) return VAL_NIL;
    obj->header.type_id = TYPE_I128;
    obj->header.metadata = 0;
    obj->value = value;
    return BOX_PTR(obj);
}

RUNTIME_API LmValue lm_alloc_u128(unsigned __int128 value) {
    ObjU128* obj = (ObjU128*)malloc(sizeof(ObjU128));
    if (!obj) return VAL_NIL;
    obj->header.type_id = TYPE_U128;
    obj->header.metadata = 0;
    obj->value = value;
    return BOX_PTR(obj);
}

RUNTIME_API LmValue lm_alloc_float(double value) {
    ObjFloat* obj = (ObjFloat*)malloc(sizeof(ObjFloat));
    if (!obj) return VAL_NIL;
    obj->header.type_id = TYPE_FLOAT;
    obj->header.metadata = 0;
    obj->value = value;
    return BOX_PTR(obj);
}

RUNTIME_API void* lm_frame_alloc(const char* name, int fields) {
    LmFrame* frame = (LmFrame*)malloc(sizeof(LmFrame));
    if (!frame) return NULL;
    frame->header.type_id = TYPE_FRAME;
    frame->header.metadata = 0;
    frame->name = strdup(name);
    frame->field_count = fields;
    frame->fields = (LmValue*)calloc(fields, sizeof(LmValue));
    for (int i = 0; i < fields; i++) frame->fields[i] = VAL_NIL;
    pthread_mutex_t* mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);
    frame->mutex = mutex;
    return (void*)frame;
}

RUNTIME_API LmValue lm_frame_get_field(void* frame_ptr, int offset) {
    LmFrame* frame = (LmFrame*)frame_ptr;
    if (!frame || offset < 0 || offset >= frame->field_count) return VAL_NIL;
    return frame->fields[offset];
}

RUNTIME_API void lm_frame_set_field(void* frame_ptr, int offset, LmValue value) {
    LmFrame* frame = (LmFrame*)frame_ptr;
    if (!frame || offset < 0 || offset >= frame->field_count) return;
    frame->fields[offset] = value;
}

RUNTIME_API LmValue lm_frame_get_field_atomic(void* frame_ptr, int offset) {
    LmFrame* frame = (LmFrame*)frame_ptr;
    if (!frame || offset < 0 || offset >= frame->field_count) return VAL_NIL;
    pthread_mutex_lock((pthread_mutex_t*)frame->mutex);
    LmValue val = frame->fields[offset];
    pthread_mutex_unlock((pthread_mutex_t*)frame->mutex);
    return val;
}

RUNTIME_API void lm_frame_set_field_atomic(void* frame_ptr, int offset, LmValue value) {
    LmFrame* frame = (LmFrame*)frame_ptr;
    if (!frame || offset < 0 || offset >= frame->field_count) return;
    pthread_mutex_lock((pthread_mutex_t*)frame->mutex);
    frame->fields[offset] = value;
    pthread_mutex_unlock((pthread_mutex_t*)frame->mutex);
}

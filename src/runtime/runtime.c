#define BUILDING_RUNTIME
#define _POSIX_C_SOURCE 200809L
#include "runtime.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

#include <pthread.h>

RUNTIME_API void* lm_frame_alloc(const char* name, int fields) {
    LmFrame* frame = (LmFrame*)malloc(sizeof(LmFrame));
    if (!frame) return NULL;
    
    frame->name = strdup(name);
    frame->field_count = fields;
    frame->fields = (void**)calloc(fields, sizeof(void*));
    
    pthread_mutex_t* mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);
    frame->mutex = mutex;
    
    return frame;
}

RUNTIME_API void* lm_frame_get_field(void* frame_ptr, int offset) {
    LmFrame* frame = (LmFrame*)frame_ptr;
    if (!frame || offset < 0 || offset >= frame->field_count) return NULL;
    return frame->fields[offset];
}

RUNTIME_API void lm_frame_set_field(void* frame_ptr, int offset, void* value) {
    LmFrame* frame = (LmFrame*)frame_ptr;
    if (!frame || offset < 0 || offset >= frame->field_count) return;
    frame->fields[offset] = value;
}

RUNTIME_API void* lm_frame_get_field_atomic(void* frame_ptr, int offset) {
    LmFrame* frame = (LmFrame*)frame_ptr;
    if (!frame || offset < 0 || offset >= frame->field_count) return NULL;
    
    pthread_mutex_lock((pthread_mutex_t*)frame->mutex);
    void* value = frame->fields[offset];
    pthread_mutex_unlock((pthread_mutex_t*)frame->mutex);
    
    return value;
}

RUNTIME_API void lm_frame_set_field_atomic(void* frame_ptr, int offset, void* value) {
    LmFrame* frame = (LmFrame*)frame_ptr;
    if (!frame || offset < 0 || offset >= frame->field_count) return;
    
    pthread_mutex_lock((pthread_mutex_t*)frame->mutex);
    frame->fields[offset] = value;
    pthread_mutex_unlock((pthread_mutex_t*)frame->mutex);
}

RUNTIME_API void lm_frame_field_atomic_add(void* frame_ptr, int offset, void* value_ptr) {
    LmFrame* frame = (LmFrame*)frame_ptr;
    if (!frame || offset < 0 || offset >= frame->field_count) return;
    
    LmBox* add_box = (LmBox*)value_ptr;
    if (!add_box || add_box->type != LM_BOX_INT) return;
    
    pthread_mutex_lock((pthread_mutex_t*)frame->mutex);
    LmBox* current_box = (LmBox*)frame->fields[offset];
    if (current_box && current_box->type == LM_BOX_INT) {
        current_box->value.as_int += add_box->value.as_int;
    }
    pthread_mutex_unlock((pthread_mutex_t*)frame->mutex);
}

RUNTIME_API void lm_frame_field_atomic_sub(void* frame_ptr, int offset, void* value_ptr) {
    LmFrame* frame = (LmFrame*)frame_ptr;
    if (!frame || offset < 0 || offset >= frame->field_count) return;
    
    LmBox* sub_box = (LmBox*)value_ptr;
    if (!sub_box || sub_box->type != LM_BOX_INT) return;
    
    pthread_mutex_lock((pthread_mutex_t*)frame->mutex);
    LmBox* current_box = (LmBox*)frame->fields[offset];
    if (current_box && current_box->type == LM_BOX_INT) {
        current_box->value.as_int -= sub_box->value.as_int;
    }
    pthread_mutex_unlock((pthread_mutex_t*)frame->mutex);
}

RUNTIME_API void* lm_trait_dispatch(void* trait_obj, const char* trait_name, const char* method_name) {
    // Dynamic dispatch implementation for JIT/VM
    LmFrame* frame = (LmFrame*)trait_obj;
    if (!frame) return NULL;
    
    // Construct method name: FrameName.MethodName
    char full_name[256];
    snprintf(full_name, sizeof(full_name), "%s.%s", frame->name, method_name);
    
    // In a full implementation, we'd look up the function pointer in a global table
    // For now, this is a placeholder for the JIT/VM to find the concrete implementation
    return NULL;
}

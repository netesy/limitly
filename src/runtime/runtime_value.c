#define BUILDING_RUNTIME
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "runtime_string.h"
#include "runtime_list.h"
#include "runtime_dict.h"
#include "runtime_tuple.h"
#include "runtime.h"

// Forward declarations for helper functions
static LmString format_list(LmList* list);
static LmString format_dict(LmDict* dict);
static LmString format_tuple(LmTuple* tuple);

// Helper: Append string to buffer
static void append_to_buffer(char** buf, uint64_t* pos, uint64_t* capacity, const char* str) {
    if (!str) return;
    
    uint64_t str_len = strlen(str);
    
    // Resize buffer if needed
    while (*pos + str_len >= *capacity) {
        *capacity *= 2;
        char* new_buf = (char*)realloc(*buf, *capacity);
        if (!new_buf) return;
        *buf = new_buf;
    }
    
    // Copy string
    memcpy(*buf + *pos, str, str_len);
    *pos += str_len;
}

// Helper: Format a single value (recursive for nested structures)
static LmString format_value(int64_t value);

// Format list as string: [elem1, elem2, ...]
static LmString format_list(LmList* list) {
    if (!list) {
        return lm_string_from_cstr("[]");
    }
    
    // Safety check: verify list structure looks valid
    if (!list->data || list->size > 1000000 || list->capacity < list->size) {
        return lm_string_from_cstr("[]");
    }
    
    uint64_t capacity = 256;
    char* buf = (char*)malloc(capacity);
    if (!buf) return (LmString){ NULL, 0 };
    
    uint64_t pos = 0;
    append_to_buffer(&buf, &pos, &capacity, "[");
    
    for (uint64_t i = 0; i < list->size; i++) {
        if (i > 0) {
            append_to_buffer(&buf, &pos, &capacity, ", ");
        }
        
        // Format element
        int64_t elem = (int64_t)(uintptr_t)list->data[i];
        LmString elem_str = format_value(elem);
        if (elem_str.data) {
            append_to_buffer(&buf, &pos, &capacity, elem_str.data);
            lm_string_free(elem_str);
        }
    }
    
    append_to_buffer(&buf, &pos, &capacity, "]");
    buf[pos] = 0;
    
    return (LmString){ buf, pos };
}

// Format dict as string: {key1: value1, key2: value2, ...}
static LmString format_dict(LmDict* dict) {
    if (!dict || !dict->buckets) {
        return lm_string_from_cstr("{}");
    }
    
    uint64_t capacity = 512;
    char* buf = (char*)malloc(capacity);
    if (!buf) return (LmString){ NULL, 0 };
    
    uint64_t pos = 0;
    append_to_buffer(&buf, &pos, &capacity, "{");
    
    uint64_t count = 0;
    for (uint64_t i = 0; i < dict->bucket_count; i++) {
        LmDictEntry* entry = dict->buckets[i];
        while (entry) {
            if (count > 0) {
                append_to_buffer(&buf, &pos, &capacity, ", ");
            }
            
            // Format key
            int64_t key = (int64_t)(uintptr_t)entry->key;
            LmString key_str = format_value(key);
            append_to_buffer(&buf, &pos, &capacity, key_str.data);
            lm_string_free(key_str);
            
            append_to_buffer(&buf, &pos, &capacity, ": ");
            
            // Format value
            int64_t val = (int64_t)(uintptr_t)entry->value;
            LmString val_str = format_value(val);
            append_to_buffer(&buf, &pos, &capacity, val_str.data);
            lm_string_free(val_str);
            
            entry = entry->next;
            count++;
        }
    }
    
    append_to_buffer(&buf, &pos, &capacity, "}");
    buf[pos] = 0;
    
    return (LmString){ buf, pos };
}

// Format tuple as string: (elem1, elem2, ...)
static LmString format_tuple(LmTuple* tuple) {
    if (!tuple || !tuple->elements) {
        return lm_string_from_cstr("()");
    }
    
    uint64_t capacity = 256;
    char* buf = (char*)malloc(capacity);
    if (!buf) return (LmString){ NULL, 0 };
    
    uint64_t pos = 0;
    append_to_buffer(&buf, &pos, &capacity, "(");
    
    for (uint64_t i = 0; i < tuple->size; i++) {
        if (i > 0) {
            append_to_buffer(&buf, &pos, &capacity, ", ");
        }
        
        // Format element
        int64_t elem = (int64_t)(uintptr_t)tuple->elements[i];
        LmString elem_str = format_value(elem);
        append_to_buffer(&buf, &pos, &capacity, elem_str.data);
        lm_string_free(elem_str);
    }
    
    append_to_buffer(&buf, &pos, &capacity, ")");
    buf[pos] = 0;
    
    return (LmString){ buf, pos };
}

// Format a single value (handles primitives and collections)
static LmString format_value(int64_t value) {
    // Since we now have explicit type information in LIR instructions,
    // we should only reach this function when we know the value is a pointer
    // to a collection. We trust the type system and don't do pointer range detection.
    
    void* ptr = (void*)(uintptr_t)value;
    
    // Try as boxed value FIRST (for elements in collections)
    // Boxed values have a type field at the beginning
    LmBox* box = (LmBox*)ptr;
    if (box && box->type >= 0 && box->type <= 4) {
        // It's a boxed value, format it
        switch (box->type) {
            case LM_BOX_INT:
                return lm_int_to_string(box->value.as_int);
            case LM_BOX_FLOAT: {
                return lm_double_to_string(box->value.as_float);
            }
            case LM_BOX_BOOL:
                return lm_bool_to_string(box->value.as_bool ? 1 : 0);
            case LM_BOX_STRING: {
                const char* str = lm_unbox_string(box);
                return lm_string_from_cstr(str);
            }
            case LM_BOX_NULLPTR:
                return lm_string_from_cstr("nil");
            default:
                return lm_string_from_cstr("?");
        }
    }
    
    // Try as tuple (has magic number - most reliable)
    LmTuple* tuple = (LmTuple*)ptr;
    if (tuple && tuple->magic == LM_TUPLE_MAGIC && tuple->elements && tuple->size < 1000000) {
        return format_tuple(tuple);
    }
    
    // Try as list
    LmList* list = (LmList*)ptr;
    if (list && list->data && list->size < 1000000 && list->capacity >= list->size) {
        return format_list(list);
    }
    
    // Try as dict
    LmDict* dict = (LmDict*)ptr;
    if (dict && dict->buckets && dict->bucket_count > 0 && dict->bucket_count < 1000000) {
        return format_dict(dict);
    }
    
    // If none of the above, fall back to integer representation
    return lm_int_to_string(value);
}

// Main API: Convert any value to a printable string
// This is the function called by both JIT and Register VM
RUNTIME_API LmString lm_value_to_string(void* value) {
    return format_value((int64_t)(uintptr_t)value);
}

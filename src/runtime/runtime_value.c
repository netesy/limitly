#define BUILDING_RUNTIME
#include "runtime_value.h"
#include "runtime_value_base.h"
#include "runtime_list.h"
#include "runtime_dict.h"
#include "runtime_tuple.h"
#include "runtime_string.h"
#include "runtime.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
    if (!list) return lm_string_from_cstr("[]");
    
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
        if (elem_str.data) {
            append_to_buffer(&buf, &pos, &capacity, elem_str.data);
            lm_string_free(elem_str);
        }
    }
    
    append_to_buffer(&buf, &pos, &capacity, ")");
    buf[pos] = 0;
    
    return (LmString){ buf, pos };
}

// Format a single value using Low-Bit Tagging
static LmString format_value(int64_t value) {
    if (IS_INT(value)) {
        return lm_int_to_string(UNBOX_INT(value));
    }
    if (IS_NIL(value)) {
        return lm_string_from_cstr("nil");
    }
    if (IS_BOOL(value)) {
        return lm_bool_to_string(UNBOX_BOOL(value) ? 1 : 0);
    }

    if (IS_PTR(value)) {
        void* ptr = UNBOX_PTR(value);
        if (!ptr) return lm_string_from_cstr("nil");

        ObjHeader* header = (ObjHeader*)ptr;
        switch (header->type_id) {
            case TYPE_LIST:
                return format_list((LmList*)ptr);
            case TYPE_DICT:
                return format_dict((LmDict*)ptr);
            case TYPE_TUPLE:
                return format_tuple((LmTuple*)ptr);
            case TYPE_FRAME: {
                LmFrame* frame = (LmFrame*)ptr;
                return lm_string_from_cstr(frame->name ? frame->name : "frame");
            }
            case TYPE_BOX: {
                LmBox* box = (LmBox*)ptr;
                switch (box->type) {
                    case LM_BOX_INT: return lm_int_to_string(box->value.as_int);
                    case LM_BOX_FLOAT: {
                        char b[64];
                        snprintf(b, sizeof(b), "%g", box->value.as_float);
                        return lm_string_from_cstr(b);
                    }
                    case LM_BOX_BOOL: return lm_bool_to_string(box->value.as_bool);
                    case LM_BOX_STRING: return lm_string_from_cstr((char*)box->value.as_ptr);
                    case LM_BOX_NULLPTR: return lm_string_from_cstr("nil");
                    default: return lm_string_from_cstr("<box>");
                }
            }
            default:
                break;
        }
    }
    
    // Fallback for unhandled or raw values
    return lm_int_to_string(value);
}

// Main API: Convert any value to a printable string
RUNTIME_API LmString lm_value_to_string(void* value) {
    return format_value((int64_t)(uintptr_t)value);
}

// Unified equality comparison for any two tagged values
RUNTIME_API int lm_value_eq(void* v1, void* v2) {
    if (v1 == v2) return 1;
    
    int64_t val1 = (int64_t)(uintptr_t)v1;
    int64_t val2 = (int64_t)(uintptr_t)v2;
    
    if (IS_INT(val1) && IS_INT(val2)) return UNBOX_INT(val1) == UNBOX_INT(val2);
    if (IS_BOOL(val1) && IS_BOOL(val2)) return val1 == val2;
    if (IS_NIL(val1) || IS_NIL(val2)) return val1 == val2;
    
    if (IS_PTR(val1) && IS_PTR(val2)) {
        void* p1 = UNBOX_PTR(val1);
        void* p2 = UNBOX_PTR(val2);
        ObjHeader* h1 = (ObjHeader*)p1;
        ObjHeader* h2 = (ObjHeader*)p2;
        
        if (h1->type_id != h2->type_id) return 0;
        
        switch (h1->type_id) {
            case TYPE_BOX: {
                LmBox* b1 = (LmBox*)p1;
                LmBox* b2 = (LmBox*)p2;
                if (b1->type != b2->type) return 0;
                switch (b1->type) {
                    case LM_BOX_INT: return b1->value.as_int == b2->value.as_int;
                    case LM_BOX_FLOAT: return b1->value.as_float == b2->value.as_float;
                    case LM_BOX_BOOL: return b1->value.as_bool == b2->value.as_bool;
                    case LM_BOX_STRING: return strcmp((const char*)b1->value.as_ptr, (const char*)b2->value.as_ptr) == 0;
                    case LM_BOX_NULLPTR: return 1;
                    default: return 0;
                }
            }
            // For collections, we currently only support identity equality unless deep comparison is implemented
            default: return p1 == p2;
        }
    }
    
    return val1 == val2;
}

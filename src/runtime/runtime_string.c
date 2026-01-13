#define BUILDING_RUNTIME
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "runtime_string.h"

// String concatenation function
RUNTIME_API LmString lm_string_concat(LmString a, LmString b) {
    char* buf = (char*)malloc(a.len + b.len + 1);
    if (!buf) {
        // Return empty string on allocation failure
        return (LmString){ NULL, 0 };
    }
    
    // Copy first string
    for (uint64_t i = 0; i < a.len; i++)
        buf[i] = a.data[i];
    
    // Copy second string
    for (uint64_t i = 0; i < b.len; i++)
        buf[a.len + i] = b.data[i];
    
    // Null terminate
    buf[a.len + b.len] = 0;
    
    return (LmString){ buf, a.len + b.len };
}

// Convert integer to string
RUNTIME_API LmString lm_int_to_string(int64_t value) {
    // Buffer large enough for 64-bit integer
    char temp[32];
    int len = snprintf(temp, sizeof(temp), "%lld", (long long)value);
    if (len <= 0) {
        return (LmString){ NULL, 0 };
    }
    
    char* buf = (char*)malloc(len + 1);
    if (!buf) {
        return (LmString){ NULL, 0 };
    }
    
    memcpy(buf, temp, len);
    buf[len] = 0;
    
    return (LmString){ buf, (uint64_t)len };
}

// Convert double to string
RUNTIME_API LmString lm_double_to_string(double value) {
    // Buffer large enough for 64-bit double
    char temp[64];
    int len = snprintf(temp, sizeof(temp), "%.15g", value);
    if (len <= 0) {
        return (LmString){ NULL, 0 };
    }
    
    char* buf = (char*)malloc(len + 1);
    if (!buf) {
        return (LmString){ NULL, 0 };
    }
    
    memcpy(buf, temp, len);
    buf[len] = 0;
    
    return (LmString){ buf, (uint64_t)len };
}

// Convert boolean to string
RUNTIME_API LmString lm_bool_to_string(uint8_t value) {
    const char* str = value ? "true" : "false";
    uint64_t len = strlen(str);
    
    char* buf = (char*)malloc(len + 1);
    if (!buf) {
        return (LmString){ NULL, 0 };
    }
    
    memcpy(buf, str, len);
    buf[len] = 0;
    
    return (LmString){ buf, len };
}

// Get data pointer from LmString
RUNTIME_API const char* lm_string_get_data(LmString str) {
    return str.data;
}

// Create LmString from C string
RUNTIME_API LmString lm_string_from_cstr(const char* cstr) {
    if (!cstr) {
        return (LmString){ NULL, 0 };
    }
    
    uint64_t len = strlen(cstr);
    char* buf = (char*)malloc(len + 1);
    if (!buf) {
        return (LmString){ NULL, 0 };
    }
    
    memcpy(buf, cstr, len);
    buf[len] = 0;
    
    return (LmString){ buf, len };
}

// Simple string formatting (replace %s with argument)
RUNTIME_API LmString lm_string_format(LmString format_str, LmString arg_str) {
    const char* format = lm_string_get_data(format_str);
    const char* arg = lm_string_get_data(arg_str);
    
    // Find %s in format
    const char* placeholder = "%s";
    char* pos = strstr(format, placeholder);
    
    if (pos) {
        size_t placeholder_len = pos - format;
        size_t before_len = placeholder_len;
        size_t after_len = strlen(format) - placeholder_len - 2; // -2 for %s
        
        char* buf = (char*)malloc(before_len + arg_str.len + after_len + 1);
        if (!buf) {
            return (LmString){ NULL, 0 };
        }
        
        // Copy before placeholder
        memcpy(buf, format, before_len);
        buf[before_len] = '\0';
        
        // Copy arg
        memcpy(buf + before_len, arg, arg_str.len);
        buf[before_len + arg_str.len] = '\0';
        
        // Copy after placeholder
        memcpy(buf + before_len + arg_str.len, pos + 2, after_len);
        buf[before_len + arg_str.len + after_len] = '\0';
        
        return (LmString){ buf, before_len + arg_str.len + after_len };
    } else {
        // No placeholder found, just concatenate
        return lm_string_concat(format_str, arg_str);
    }
}

// String interpolation (multiple arguments)
RUNTIME_API LmString lm_string_interpolate(LmString format_str, LmString* args, uint64_t arg_count) {
    // Simple implementation - just concatenate all arguments
    if (arg_count == 0) {
        return format_str;
    }
    
    LmString result = format_str;
    for (uint64_t i = 0; i < arg_count; i++) {
        result = lm_string_concat(result, args[i]);
    }
    
    return result;
}

// Free LmString
RUNTIME_API void lm_string_free(LmString str) {
    if (str.data) {
        free((void*)str.data);
    }
}

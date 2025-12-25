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
    char temp[64];
    int len = snprintf(temp, sizeof(temp), "%g", value);
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
    uint64_t len = value ? 4 : 5;
    
    char* buf = (char*)malloc(len + 1);
    if (!buf) {
        return (LmString){ NULL, 0 };
    }
    
    memcpy(buf, str, len);
    buf[len] = 0;
    
    return (LmString){ buf, len };
}

// String formatting function - simple version for variable arguments
RUNTIME_API LmString lm_string_format(LmString format_str, LmString* args, uint64_t arg_count) {
    // Simple implementation - just concatenate all arguments
    // In a full implementation, this would handle format specifiers
    
    // Calculate total length needed
    uint64_t total_len = format_str.len;
    for (uint64_t i = 0; i < arg_count; i++) {
        total_len += args[i].len;
    }
    
    char* buf = (char*)malloc(total_len + 1);
    if (!buf) {
        return (LmString){ NULL, 0 };
    }
    
    // Copy format string
    uint64_t pos = 0;
    for (uint64_t i = 0; i < format_str.len; i++) {
        buf[pos++] = format_str.data[i];
    }
    
    // Copy all arguments
    for (uint64_t i = 0; i < arg_count; i++) {
        for (uint64_t j = 0; j < args[i].len; j++) {
            buf[pos++] = args[i].data[j];
        }
    }
    
    buf[pos] = 0;
    
    return (LmString){ buf, total_len };
}

// Free string memory
RUNTIME_API void lm_string_free(LmString str) {
    if (str.data) {
        free(str.data);
    }
}

// Convert C string to LmString
RUNTIME_API LmString lm_string_from_cstr(const char* str) {
    LmString result;
    result.data = (char*)str;
    result.len = strlen(str);
    return result;
}

// Helper: Extract data pointer from LmString (for JIT)
RUNTIME_API const char* lm_string_get_data(LmString str) {
    return str.data;
}

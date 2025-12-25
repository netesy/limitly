#ifndef RUNTIME_STRING_H
#define RUNTIME_STRING_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char* data;
    uint64_t len;
} LmString;

// String concatenation function
LmString lm_string_concat(LmString a, LmString b);

// Convert integer to string
LmString lm_int_to_string(int64_t value);

// Convert double to string
LmString lm_double_to_string(double value);

// Convert boolean to string
LmString lm_bool_to_string(uint8_t value);

// String formatting function
LmString lm_string_format(LmString format_str, LmString* args, uint64_t arg_count);

// Free string memory
void lm_string_free(LmString str);

// Create string from C string literal
LmString lm_string_from_cstr(const char* cstr);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_STRING_H

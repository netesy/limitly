#ifndef RUNTIME_STRING_H
#define RUNTIME_STRING_H

#include <stdint.h>

// For static linking, define as empty
#ifndef RUNTIME_API
    #define RUNTIME_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char* data;
    uint64_t len;
} LmString;

// String operations
RUNTIME_API LmString lm_string_concat(LmString a, LmString b);
RUNTIME_API LmString lm_int_to_string(int64_t value);
RUNTIME_API LmString lm_double_to_string(double value);
RUNTIME_API LmString lm_bool_to_string(uint8_t value);
RUNTIME_API const char* lm_string_get_data(LmString str);
RUNTIME_API LmString lm_string_from_cstr(const char* cstr);
RUNTIME_API LmString lm_string_format(LmString format_str, LmString arg_str);
RUNTIME_API LmString lm_string_interpolate(LmString format_str, LmString* args, uint64_t arg_count);
RUNTIME_API void lm_string_free(LmString str);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_STRING_H

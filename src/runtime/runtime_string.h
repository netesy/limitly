#ifndef RUNTIME_STRING_H
#define RUNTIME_STRING_H

#include <stdint.h>
#include <stdbool.h>
#include "runtime_value_base.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declaration for static linking
#ifndef RUNTIME_API
    #define RUNTIME_API
#endif

typedef struct {
    const char* data;
    uint64_t len;
} LmString;

// Header-only string structure for heap objects
typedef struct {
    ObjHeader header;
    char data[0];
} LmStringObj;

// String management functions
RUNTIME_API LmString lm_string_concat(LmString a, LmString b);
RUNTIME_API LmString lm_int_to_string(int64_t value);
RUNTIME_API LmString lm_double_to_string(double value);
RUNTIME_API LmString lm_bool_to_string(uint8_t value);
RUNTIME_API const char* lm_string_get_data(LmString str);
RUNTIME_API LmString lm_string_from_cstr(const char* cstr);
RUNTIME_API LmString lm_string_format(LmString format, LmString arg);
RUNTIME_API LmString lm_string_interpolate(LmString format, LmString* args, uint64_t arg_count);
RUNTIME_API void lm_string_free(LmString str);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_STRING_H

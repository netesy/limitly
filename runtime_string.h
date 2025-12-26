#ifndef RUNTIME_STRING_H
#define RUNTIME_STRING_H

#include <stdint.h>

#ifdef _WIN32
#  ifdef BUILDING_RUNTIME
#    define RUNTIME_API __declspec(dllexport)
#  else
#    define RUNTIME_API __declspec(dllimport)
#  endif
#else
#  define RUNTIME_API __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char* data;
    uint64_t len;
} LmString;

// String concatenation function
RUNTIME_API LmString lm_string_concat(LmString a, LmString b);

// Convert C string to LmString
RUNTIME_API LmString lm_string_from_cstr(const char* str);

// Get data pointer from LmString (for JIT)
RUNTIME_API const char* lm_string_get_data(LmString str);

// String interpolation function for JIT - replaces {placeholder} with values
RUNTIME_API LmString lm_string_interpolate(LmString format_str, LmString* args, uint64_t arg_count);

// Convert integer to string
RUNTIME_API LmString lm_int_to_string(int64_t value);

// Convert double to string
RUNTIME_API LmString lm_double_to_string(double value);

// Convert boolean to string
RUNTIME_API LmString lm_bool_to_string(uint8_t value);

// String formatting function
RUNTIME_API LmString lm_string_format(LmString format_str, LmString* args, uint64_t arg_count);

// Free string memory
RUNTIME_API void lm_string_free(LmString str);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_STRING_H

#ifndef RUNTIME_STRING_H
#define RUNTIME_STRING_H

#include <stdint.h>
#include <stdbool.h>
#include "vm_value_base.hh"

#ifdef __cplusplus
extern "C" {
#endif

// Forward declaration for static linking
#ifndef RUNTIME_API
    #define RUNTIME_API
#endif

// Canonical Limitly Native String Representation
typedef struct {
    ObjHeader header;   // type_id = TYPE_STRING (11)
    uint64_t len;       // Authoritative UTF-8 byte length
    uint64_t cap;       // Allocated capacity (excluding trailing NUL)
    char data[];        // Contiguous UTF-8 byte payload + '\0' at data[len]
} LmStringHeader;

// Native String Allocation & Management Primitives
RUNTIME_API LmStringHeader* lm_str_alloc(uint64_t cap);
RUNTIME_API LmStringHeader* lm_str_from_bytes(const char* data, uint64_t len);
RUNTIME_API LmStringHeader* lm_str_from_cstr(const char* cstr);
RUNTIME_API void lm_str_free(LmStringHeader* str);

// Native String Operation Primitives
RUNTIME_API LmStringHeader* lm_str_concat(const LmStringHeader* a, const LmStringHeader* b);
RUNTIME_API LmStringHeader* lm_str_substring(const LmStringHeader* str, int64_t start, int64_t end);
RUNTIME_API uint8_t lm_str_byte_at(const LmStringHeader* str, uint64_t index);
RUNTIME_API int64_t lm_str_index_of(const LmStringHeader* str, const LmStringHeader* needle);
RUNTIME_API bool lm_str_contains(const LmStringHeader* str, const LmStringHeader* needle);
RUNTIME_API bool lm_str_starts_with(const LmStringHeader* str, const LmStringHeader* prefix);
RUNTIME_API bool lm_str_ends_with(const LmStringHeader* str, const LmStringHeader* suffix);
RUNTIME_API LmStringHeader* lm_str_trim(const LmStringHeader* str);
RUNTIME_API LmStringHeader* lm_str_to_lower(const LmStringHeader* str);
RUNTIME_API LmStringHeader* lm_str_to_upper(const LmStringHeader* str);
RUNTIME_API LmStringHeader* lm_str_replace(const LmStringHeader* str, const LmStringHeader* old_sub, const LmStringHeader* new_sub);
RUNTIME_API uint64_t lm_str_decode_next(const LmStringHeader* str, uint64_t offset);

// Formatting helpers
RUNTIME_API LmStringHeader* lm_int_to_str(int64_t value);
RUNTIME_API LmStringHeader* lm_double_to_str(double value);
RUNTIME_API LmStringHeader* lm_bool_to_str(uint8_t value);
RUNTIME_API LmStringHeader* lm_str_format(const LmStringHeader* format, const LmStringHeader* arg);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_STRING_H

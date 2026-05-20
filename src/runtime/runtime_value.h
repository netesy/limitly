#ifndef RUNTIME_VALUE_H
#define RUNTIME_VALUE_H

#include <stdint.h>
#include <stdbool.h>
#include "runtime_string.h"
#include "runtime_value_base.h"

// For static linking, define as empty
#ifndef RUNTIME_API
    #define RUNTIME_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Centralized Runtime Constructors (Phase 6)
RUNTIME_API LmValue make_i64(int64_t v);
RUNTIME_API LmValue make_u64(uint64_t v);
RUNTIME_API LmValue make_i128(__int128 v);
RUNTIME_API LmValue make_u128(unsigned __int128 v);
RUNTIME_API LmValue make_float(double v);

// Centralized Extraction Helpers (Phase 7)
RUNTIME_API bool is_integer(LmValue v);
RUNTIME_API bool is_float(LmValue v);
static inline bool is_numeric(LmValue v) { return is_integer(v) || is_float(v); }

RUNTIME_API int64_t as_i64(LmValue v);
RUNTIME_API uint64_t as_u64(LmValue v);
RUNTIME_API __int128 as_i128(LmValue v);
RUNTIME_API unsigned __int128 as_u128(LmValue v);
RUNTIME_API double as_float(LmValue v);

// Arithmetic (Phase 12)
RUNTIME_API LmValue lm_add(LmValue a, LmValue b);
RUNTIME_API LmValue lm_sub(LmValue a, LmValue b);
RUNTIME_API LmValue lm_mul(LmValue a, LmValue b);
RUNTIME_API LmValue lm_div(LmValue a, LmValue b);

// Unified equality comparison for any two tagged values
RUNTIME_API int lm_value_eq(LmValue v1, LmValue v2);

// Numeric comparison (Phase 13)
RUNTIME_API int numeric_compare(LmValue a, LmValue b);

// Convert any value to a printable string
RUNTIME_API LmString lm_value_to_string(LmValue value);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_VALUE_H

#ifndef RUNTIME_VALUE_H
#define RUNTIME_VALUE_H

#include <stdint.h>
#include "runtime_string.h"

// For static linking, define as empty
#ifndef RUNTIME_API
    #define RUNTIME_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Convert any value to a printable string
// Handles primitives (int, bool, etc.) and collections (list, dict, tuple)
// This is the unified function used by both JIT and Register VM
// Note: Accepts void* pointer which is interpreted as int64_t internally
RUNTIME_API LmString lm_value_to_string(void* value);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_VALUE_H

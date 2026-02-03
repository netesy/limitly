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
RUNTIME_API LmString lm_value_to_string(int64_t value);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_VALUE_H

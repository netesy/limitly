#ifndef RUNTIME_H
#define RUNTIME_H

#include <stdint.h>

// For static linking, define as empty
#ifndef RUNTIME_API
    #define RUNTIME_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Include all runtime sub-modules
#include "runtime_list.h"
#include "runtime_dict.h"
#include "runtime_string.h"

// Boxing/Unboxing for primitive types
typedef struct {
    uint8_t type;  // 0=int, 1=float, 2=bool, 3=string, 4=nullptr
    union {
        int64_t as_int;
        double as_float;
        uint8_t as_bool;
        void* as_ptr;
    } value;
} LmBox;

// Box type constants
#define LM_BOX_INT    0
#define LM_BOX_FLOAT  1
#define LM_BOX_BOOL   2
#define LM_BOX_STRING 3
#define LM_BOX_NULLPTR 4

// Boxing operations
RUNTIME_API LmBox* lm_box_int(int64_t value);
RUNTIME_API LmBox* lm_box_float(double value);
RUNTIME_API LmBox* lm_box_bool(uint8_t value);
RUNTIME_API LmBox* lm_box_string(const char* value);
RUNTIME_API LmBox* lm_box_nullptr(void);

// Unboxing operations
RUNTIME_API int64_t lm_unbox_int(LmBox* box);
RUNTIME_API double lm_unbox_float(LmBox* box);
RUNTIME_API uint8_t lm_unbox_bool(LmBox* box);
RUNTIME_API const char* lm_unbox_string(LmBox* box);
RUNTIME_API void* lm_unbox_ptr(LmBox* box);

// Memory management
RUNTIME_API void lm_box_free(LmBox* box);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_H

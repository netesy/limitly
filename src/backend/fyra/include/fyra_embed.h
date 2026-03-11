#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int fyra_compile_ir_to_file(const char* ir_text,
                            const char* output_path,
                            const char* target,
                            int opt_level,
                            int debug_enabled,
                            char* error_buffer,
                            size_t error_buffer_size);

#ifdef __cplusplus
}
#endif

#include "../include/fyra_embed.h"

#include <stdio.h>
#include <string.h>

static void set_error(char* error_buffer, size_t error_buffer_size, const char* msg) {
    if (!error_buffer || error_buffer_size == 0) {
        return;
    }
    snprintf(error_buffer, error_buffer_size, "%s", msg);
}

int fyra_compile_ir_to_file(const char* ir_text,
                            const char* output_path,
                            const char* target,
                            int opt_level,
                            int debug_enabled,
                            char* error_buffer,
                            size_t error_buffer_size) {
    (void)ir_text;
    (void)output_path;
    (void)target;
    (void)opt_level;
    (void)debug_enabled;

    set_error(error_buffer,
              error_buffer_size,
              "Vendored libfyra stub is linked, but real Fyra compiler sources were not available. "
              "Replace src/backend/fyra with the full Fyra project sources.");
    return 1;
}

#define STB_IMAGE_IMPLEMENTATION
#include "../../../vendor/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../../vendor/stb/stb_image_write.h"
#include "vm_runtime.hh"
#include "vm_value.hh"

RUNTIME_API LmValue lm_image_load(const char* filename, int* w, int* h, int* c) {
    unsigned char* data = stbi_load(filename, w, h, c, 0);
    if (!data) return VAL_NIL;
    return lm_alloc_foreign_ptr(data);
}

RUNTIME_API void lm_image_free(void* data) {
    stbi_image_free(data);
}

RUNTIME_API int lm_image_save_png(const char* filename, int w, int h, int c, const void* data) {
    return stbi_write_png(filename, w, h, c, data, w * c);
}

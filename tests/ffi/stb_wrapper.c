#define STB_IMAGE_IMPLEMENTATION
#include "../../vendor/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../vendor/stb/stb_image_write.h"

// Wrappers to handle pointer returns and basic info
unsigned char* load_image(const char* filename, int* width, int* height, int* channels) {
    return stbi_load(filename, width, height, channels, 0);
}

void free_image(unsigned char* data) {
    stbi_image_free(data);
}

int save_image_png(const char* filename, int w, int h, int c, const void* data) {
    return stbi_write_png(filename, w, h, c, data, w * c);
}

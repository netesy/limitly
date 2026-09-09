#define STB_IMAGE_IMPLEMENTATION
#include "../../vendor/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../vendor/stb/stb_image_write.h"
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

// Generic loading & query
EXPORT unsigned char* load_image(const char* filename, int* width, int* height, int* channels) {
    return stbi_load(filename, width, height, channels, 0);
}

EXPORT unsigned char* load_image_forced(const char* filename, int* width, int* height, int* channels, int req_comp) {
    return stbi_load(filename, width, height, channels, req_comp);
}

EXPORT int query_image_info(const char* filename, int* width, int* height, int* channels) {
    return stbi_info(filename, width, height, channels);
}

EXPORT void free_image(unsigned char* data) {
    stbi_image_free(data);
}

// PNG
EXPORT int save_image_png(const char* filename, int w, int h, int c, const void* data) {
    return stbi_write_png(filename, w, h, c, data, w * c);
}

EXPORT int save_image_png_stride(const char* filename, int w, int h, int c, const void* data, int stride) {
    return stbi_write_png(filename, w, h, c, data, stride);
}

// JPG
EXPORT int save_image_jpg(const char* filename, int w, int h, int c, const void* data, int quality) {
    return stbi_write_jpg(filename, w, h, c, data, quality);
}

// BMP
EXPORT int save_image_bmp(const char* filename, int w, int h, int c, const void* data) {
    return stbi_write_bmp(filename, w, h, c, data);
}

// TGA
EXPORT int save_image_tga(const char* filename, int w, int h, int c, const void* data) {
    stbi_write_tga_with_rle = 0;
    return stbi_write_tga(filename, w, h, c, data);
}

EXPORT int save_image_tga_rle(const char* filename, int w, int h, int c, const void* data) {
    stbi_write_tga_with_rle = 1;
    return stbi_write_tga(filename, w, h, c, data);
}

// HDR
EXPORT float* load_image_hdr(const char* filename, int* width, int* height, int* channels) {
    return stbi_loadf(filename, width, height, channels, 0);
}

EXPORT int save_image_hdr(const char* filename, int w, int h, int c, const float* data) {
    return stbi_write_hdr(filename, w, h, c, data);
}

// Resizing with bilinear interpolation
EXPORT int resize_image(const unsigned char* src, int src_w, int src_h, int channels,
                        unsigned char* dst, int dst_w, int dst_h) {
    if (!src || !dst || src_w <= 0 || src_h <= 0 || dst_w <= 0 || dst_h <= 0 || channels <= 0) {
        return 0;
    }
    float x_ratio = (dst_w > 1) ? ((float)(src_w - 1)) / (dst_w - 1) : 0.0f;
    float y_ratio = (dst_h > 1) ? ((float)(src_h - 1)) / (dst_h - 1) : 0.0f;

    for (int y = 0; y < dst_h; y++) {
        float src_y = (dst_h > 1) ? (y * y_ratio) : 0.0f;
        int y_l = (int)src_y;
        int y_h = (y_l + 1 < src_h) ? y_l + 1 : y_l;
        float y_weight = src_y - y_l;

        for (int x = 0; x < dst_w; x++) {
            float src_x = (dst_w > 1) ? (x * x_ratio) : 0.0f;
            int x_l = (int)src_x;
            int x_h = (x_l + 1 < src_w) ? x_l + 1 : x_l;
            float x_weight = src_x - x_l;

            int dst_idx = (y * dst_w + x) * channels;
            int idx_ll = (y_l * src_w + x_l) * channels;
            int idx_lh = (y_l * src_w + x_h) * channels;
            int idx_hl = (y_h * src_w + x_l) * channels;
            int idx_hh = (y_h * src_w + x_h) * channels;

            for (int c = 0; c < channels; c++) {
                float a = src[idx_ll + c];
                float b = src[idx_lh + c];
                float cl = src[idx_hl + c];
                float d = src[idx_hh + c];

                float val = a * (1.0f - x_weight) * (1.0f - y_weight) +
                            b * x_weight * (1.0f - y_weight) +
                            cl * (1.0f - x_weight) * y_weight +
                            d * x_weight * y_weight;

                int ival = (int)(val + 0.5f);
                if (ival < 0) ival = 0;
                if (ival > 255) ival = 255;
                dst[dst_idx + c] = (unsigned char)ival;
            }
        }
    }
    return 1;
}

// Sub-rectangle cropping
EXPORT int crop_image(const unsigned char* src, int src_w, int src_h, int channels,
                      unsigned char* dst, int x, int y, int crop_w, int crop_h) {
    if (!src || !dst || crop_w <= 0 || crop_h <= 0 || channels <= 0) return 0;
    for (int cy = 0; cy < crop_h; cy++) {
        int sy = y + cy;
        for (int cx = 0; cx < crop_w; cx++) {
            int sx = x + cx;
            int dst_idx = (cy * crop_w + cx) * channels;
            if (sx >= 0 && sx < src_w && sy >= 0 && sy < src_h) {
                int src_idx = (sy * src_w + sx) * channels;
                memcpy(dst + dst_idx, src + src_idx, channels);
            } else {
                memset(dst + dst_idx, 0, channels);
            }
        }
    }
    return 1;
}

// In-place vertical flip
EXPORT int flip_image_v(unsigned char* data, int w, int h, int channels) {
    if (!data || w <= 0 || h <= 0 || channels <= 0) return 0;
    int row_bytes = w * channels;
    unsigned char* tmp = (unsigned char*)malloc(row_bytes);
    if (!tmp) return 0;
    for (int y = 0; y < h / 2; y++) {
        unsigned char* row1 = data + y * row_bytes;
        unsigned char* row2 = data + (h - 1 - y) * row_bytes;
        memcpy(tmp, row1, row_bytes);
        memcpy(row1, row2, row_bytes);
        memcpy(row2, tmp, row_bytes);
    }
    free(tmp);
    return 1;
}

// In-place horizontal flip
EXPORT int flip_image_h(unsigned char* data, int w, int h, int channels) {
    if (!data || w <= 0 || h <= 0 || channels <= 0) return 0;
    for (int y = 0; y < h; y++) {
        unsigned char* row = data + y * w * channels;
        for (int x = 0; x < w / 2; x++) {
            int x2 = w - 1 - x;
            for (int c = 0; c < channels; c++) {
                unsigned char t = row[x * channels + c];
                row[x * channels + c] = row[x2 * channels + c];
                row[x2 * channels + c] = t;
            }
        }
    }
    return 1;
}

// 90 degrees clockwise rotation
EXPORT int rotate_image_90_cw(const unsigned char* src, int src_w, int src_h, int channels,
                             unsigned char* dst) {
    if (!src || !dst || src_w <= 0 || src_h <= 0 || channels <= 0) return 0;
    int dst_w = src_h;
    for (int y = 0; y < src_h; y++) {
        for (int x = 0; x < src_w; x++) {
            int dx = src_h - 1 - y;
            int dy = x;
            memcpy(dst + (dy * dst_w + dx) * channels,
                   src + (y * src_w + x) * channels,
                   channels);
        }
    }
    return 1;
}

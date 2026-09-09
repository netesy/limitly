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

// ============================================================================
// TrueType Font Rendering & Metrics (stb_truetype)
// ============================================================================

#define STB_TRUETYPE_IMPLEMENTATION
#include "../../vendor/stb/stb_truetype.h"
#include <stdio.h>

typedef struct {
    unsigned char* file_data;
    size_t file_size;
    stbtt_fontinfo info;
    int is_owned;
} FontHandle;

EXPORT void* load_font_file(const char* filepath) {
    if (!filepath) return NULL;
    FILE* f = fopen(filepath, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (size <= 0) { fclose(f); return NULL; }
    unsigned char* buffer = (unsigned char*)malloc(size);
    if (!buffer) { fclose(f); return NULL; }
    if (fread(buffer, 1, size, f) != (size_t)size) {
        free(buffer);
        fclose(f);
        return NULL;
    }
    fclose(f);

    FontHandle* handle = (FontHandle*)malloc(sizeof(FontHandle));
    if (!handle) {
        free(buffer);
        return NULL;
    }
    handle->file_data = buffer;
    handle->file_size = (size_t)size;
    handle->is_owned = 1;

    int offset = stbtt_GetFontOffsetForIndex(buffer, 0);
    if (offset < 0) offset = 0;
    if (!stbtt_InitFont(&handle->info, buffer, offset)) {
        free(buffer);
        free(handle);
        return NULL;
    }
    return handle;
}




EXPORT void* load_font_memory(const unsigned char* data, int data_len) {
    if (!data || data_len <= 0) return NULL;
    unsigned char* buffer = (unsigned char*)malloc(data_len);
    if (!buffer) return NULL;
    memcpy(buffer, data, data_len);

    FontHandle* handle = (FontHandle*)malloc(sizeof(FontHandle));
    if (!handle) {
        free(buffer);
        return NULL;
    }
    handle->file_data = buffer;
    handle->file_size = (size_t)data_len;
    handle->is_owned = 1;

    int offset = stbtt_GetFontOffsetForIndex(buffer, 0);
    if (offset < 0) offset = 0;
    if (!stbtt_InitFont(&handle->info, buffer, offset)) {
        free(buffer);
        free(handle);
        return NULL;
    }
    return handle;
}

EXPORT void free_font(void* font_handle) {
    if (!font_handle) return;
    FontHandle* handle = (FontHandle*)font_handle;
    if (handle->file_data && handle->is_owned) {
        free(handle->file_data);
    }
    free(handle);
}

EXPORT int get_font_vmetrics(void* font_handle, float font_size, float* ascent, float* descent, float* line_gap) {
    if (!font_handle) return 0;
    FontHandle* handle = (FontHandle*)font_handle;
    int a, d, g;
    stbtt_GetFontVMetrics(&handle->info, &a, &d, &g);
    float scale = stbtt_ScaleForPixelHeight(&handle->info, font_size);
    if (ascent) *ascent = a * scale;
    if (descent) *descent = d * scale;
    if (line_gap) *line_gap = g * scale;
    return 1;
}

EXPORT float measure_text_width(void* font_handle, float font_size, const char* text) {
    if (!font_handle || !text) return 0.0f;
    FontHandle* handle = (FontHandle*)font_handle;
    float scale = stbtt_ScaleForPixelHeight(&handle->info, font_size);
    float max_width = 0.0f;
    float cur_width = 0.0f;
    int len = (int)strlen(text);
    for (int i = 0; i < len; i++) {
        if (text[i] == '\n') {
            if (cur_width > max_width) max_width = cur_width;
            cur_width = 0.0f;
            continue;
        }
        int advance, lsb;
        stbtt_GetCodepointHMetrics(&handle->info, (int)(unsigned char)text[i], &advance, &lsb);
        cur_width += advance * scale;
        if (i + 1 < len && text[i+1] != '\n') {
            int kern = stbtt_GetCodepointKernAdvance(&handle->info, (int)(unsigned char)text[i], (int)(unsigned char)text[i+1]);
            cur_width += kern * scale;
        }
    }
    if (cur_width > max_width) max_width = cur_width;
    return max_width;
}

EXPORT int measure_text_width_int(void* font_handle, int font_size, const char* text) {
    return (int)(measure_text_width(font_handle, (float)font_size, text) + 0.999f);
}

EXPORT int measure_text_height_int(void* font_handle, int font_size, const char* text) {
    if (!font_handle || !text) return 0;
    FontHandle* handle = (FontHandle*)font_handle;
    int a, d, g;
    stbtt_GetFontVMetrics(&handle->info, &a, &d, &g);
    float scale = stbtt_ScaleForPixelHeight(&handle->info, (float)font_size);
    float line_h = (float)(a - d + g) * scale;
    if (line_h < (float)font_size) line_h = (float)font_size;
    int lines = 1;
    for (int i = 0; text[i]; i++) {
        if (text[i] == '\n') lines++;
    }
    return (int)(lines * line_h + 0.5f);
}

EXPORT unsigned char* render_text_rgba(void* font_handle, float font_size, const char* text,
                                       int r, int g, int b, int a,
                                       int* out_w, int* out_h) {
    if (!font_handle || !text) return NULL;
    FontHandle* handle = (FontHandle*)font_handle;

    int num_lines = 1;
    for (int i = 0; text[i]; i++) {
        if (text[i] == '\n') num_lines++;
    }

    int va, vd, vg;
    stbtt_GetFontVMetrics(&handle->info, &va, &vd, &vg);
    float scale = stbtt_ScaleForPixelHeight(&handle->info, font_size);
    float ascent = (float)va * scale;
    float descent = (float)vd * scale;
    float line_gap = (float)vg * scale;
    float line_height = (float)(va - vd + vg) * scale;
    if (line_height < font_size) line_height = font_size;

    float max_w = measure_text_width(font_handle, font_size, text);
    int total_w = (int)(max_w + 1.5f);
    if (total_w < 1) total_w = 1;
    int total_h = (int)((float)num_lines * line_height + 1.5f);
    if (total_h < 1) total_h = 1;

    // Extra padding around bounding box
    total_w += 4;
    total_h += 4;

    unsigned char* out_buf = (unsigned char*)calloc(total_w * total_h * 4, 1);
    if (!out_buf) return NULL;

    int line_idx = 0;
    float x_pos = 2.0f;
    float y_base = 2.0f + ascent;

    int len = (int)strlen(text);
    for (int i = 0; i < len; i++) {
        char ch = text[i];
        if (ch == '\n') {
            line_idx++;
            x_pos = 2.0f;
            y_base = 2.0f + (float)line_idx * line_height + ascent;
            continue;
        }

        int advance, lsb;
        stbtt_GetCodepointHMetrics(&handle->info, (int)(unsigned char)ch, &advance, &lsb);

        int c_x1, c_y1, c_x2, c_y2;
        stbtt_GetCodepointBitmapBox(&handle->info, (int)(unsigned char)ch, scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);
        int gw = c_x2 - c_x1;
        int gh = c_y2 - c_y1;

        if (gw > 0 && gh > 0) {
            unsigned char* glyph_bmp = (unsigned char*)malloc(gw * gh);
            if (glyph_bmp) {
                stbtt_MakeCodepointBitmap(&handle->info, glyph_bmp, gw, gh, gw, scale, scale, (int)(unsigned char)ch);

                int dst_x0 = (int)(x_pos + (float)c_x1);
                int dst_y0 = (int)(y_base + (float)c_y1);

                for (int gy = 0; gy < gh; gy++) {
                    int dy = dst_y0 + gy;
                    if (dy < 0 || dy >= total_h) continue;
                    for (int gx = 0; gx < gw; gx++) {
                        int dx = dst_x0 + gx;
                        if (dx < 0 || dx >= total_w) continue;
                        unsigned char cov = glyph_bmp[gy * gw + gx];
                        if (cov == 0) continue;

                        int idx = (dy * total_w + dx) * 4;
                        float cov_f = (float)cov / 255.0f;
                        float alpha_f = ((float)a / 255.0f) * cov_f;

                        // Alpha composite
                        float cur_a = (float)out_buf[idx + 3] / 255.0f;
                        float new_a = alpha_f + cur_a * (1.0f - alpha_f);
                        if (new_a > 0.0f) {
                            float nr = ((float)r * alpha_f + (float)out_buf[idx] * cur_a * (1.0f - alpha_f)) / new_a;
                            float ng = ((float)g * alpha_f + (float)out_buf[idx + 1] * cur_a * (1.0f - alpha_f)) / new_a;
                            float nb = ((float)b * alpha_f + (float)out_buf[idx + 2] * cur_a * (1.0f - alpha_f)) / new_a;
                            out_buf[idx] = (unsigned char)(nr + 0.5f);
                            out_buf[idx + 1] = (unsigned char)(ng + 0.5f);
                            out_buf[idx + 2] = (unsigned char)(nb + 0.5f);
                            out_buf[idx + 3] = (unsigned char)(new_a * 255.0f + 0.5f);
                        }
                    }
                }
                free(glyph_bmp);
            }
        }

        x_pos += (float)advance * scale;
        if (i + 1 < len && text[i+1] != '\n') {
            int kern = stbtt_GetCodepointKernAdvance(&handle->info, (int)(unsigned char)ch, (int)(unsigned char)text[i+1]);
            x_pos += (float)kern * scale;
        }
    }

    if (out_w) *out_w = total_w;
    if (out_h) *out_h = total_h;
    return out_buf;
}

EXPORT void free_text_rgba(unsigned char* buf) {
    if (buf) free(buf);
}

EXPORT int detect_system_font_path(const char* preferred_name, char* out_path, int max_path_len) {
    if (!out_path || max_path_len <= 0) return 0;
    out_path[0] = '\0';

    static const char* search_dirs[] = {
#ifdef _WIN32
        "C:\\Windows\\Fonts\\",
        "C:\\WinNT\\Fonts\\",
#elif __APPLE__
        "/System/Library/Fonts/",
        "/Library/Fonts/",
        "/System/Library/Fonts/Supplemental/",
#else
        "/usr/share/fonts/truetype/dejavu/",
        "/usr/share/fonts/TTF/",
        "/usr/share/fonts/truetype/liberation/",
        "/usr/share/fonts/truetype/freefont/",
        "/usr/share/fonts/truetype/ubuntu/",
        "/usr/share/fonts/",
        "/usr/local/share/fonts/",
#endif
        NULL
    };

    if (preferred_name && preferred_name[0] != '\0') {
        char temp[512];
        for (int i = 0; search_dirs[i] != NULL; i++) {
            snprintf(temp, sizeof(temp), "%s%s", search_dirs[i], preferred_name);
            FILE* f = fopen(temp, "rb");
            if (f) {
                fclose(f);
                strncpy(out_path, temp, max_path_len - 1);
                out_path[max_path_len - 1] = '\0';
                return 1;
            }
            if (!strstr(preferred_name, ".ttf") && !strstr(preferred_name, ".TTF") &&
                !strstr(preferred_name, ".ttc") && !strstr(preferred_name, ".otf")) {
                snprintf(temp, sizeof(temp), "%s%s.ttf", search_dirs[i], preferred_name);
                f = fopen(temp, "rb");
                if (f) {
                    fclose(f);
                    strncpy(out_path, temp, max_path_len - 1);
                    out_path[max_path_len - 1] = '\0';
                    return 1;
                }
            }
        }
    }

    static const char* fallbacks[] = {
#ifdef _WIN32
        "C:\\Windows\\Fonts\\segoeui.ttf",
        "C:\\Windows\\Fonts\\arial.ttf",
        "C:\\Windows\\Fonts\\tahoma.ttf",
        "C:\\Windows\\Fonts\\calibri.ttf",
        "C:\\Windows\\Fonts\\consola.ttf",
#elif __APPLE__
        "/System/Library/Fonts/SFNS.ttf",
        "/System/Library/Fonts/Helvetica.ttc",
        "/Library/Fonts/Arial.ttf",
        "/System/Library/Fonts/Supplemental/Arial.ttf",
#else
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/usr/share/fonts/truetype/freefont/FreeSans.ttf",
        "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf",
#endif
        NULL
    };

    for (int i = 0; fallbacks[i] != NULL; i++) {
        FILE* f = fopen(fallbacks[i], "rb");
        if (f) {
            fclose(f);
            strncpy(out_path, fallbacks[i], max_path_len - 1);
            out_path[max_path_len - 1] = '\0';
            return 1;
        }
    }

    return 0;
}


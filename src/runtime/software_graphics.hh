#pragma once
// One software renderer, with representation-specific checked value adapters.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <mutex>
#include <string>
#include <vector>
#include "../backend/vm/resource_types.hh"
#include "gfx_uniform_layout.hh"
#include "sokol/sokol_app_runtime.hh"
#include "sokol/sokol_gfx_runtime.hh"
#include "../backend/vm/font8x8_basic.h"
#include "../../vendor/stb/stb_truetype.h"
namespace LM::Runtime {
using LM::Backend::VM::ResourceType;
using LM::Backend::VM::ResourceOperation;
using LM::Backend::VM::RuntimeAppEvent;
using LM::Backend::VM::SokolAppConfig;
using LM::Backend::VM::sokol_app_runtime;
struct SystemFontEngine {
    std::vector<uint8_t> font_bytes;
    stbtt_fontinfo info;
    bool is_ready = false;
    bool attempted = false;

    void init() {
        if (attempted) return;
        attempted = true;

        static const char* search_dirs[] = {
#if defined(_WIN32)
            "C:\\Windows\\Fonts\\",
            "C:\\WINNT\\Fonts\\",
#elif defined(__APPLE__)
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
#endif
            nullptr
        };

        static const char* preferred_fonts[] = {
#if defined(_WIN32)
            "segoeui.ttf",
            "arial.ttf",
            "tahoma.ttf",
            "calibri.ttf",
            "consola.ttf",
#elif defined(__APPLE__)
            "SFNS.ttf",
            "Helvetica.ttc",
            "Arial.ttf",
#else
            "DejaVuSans.ttf",
            "LiberationSans-Regular.ttf",
            "FreeSans.ttf",
            "Ubuntu-R.ttf",
#endif
            nullptr
        };

        for (int i = 0; preferred_fonts[i] != nullptr && !is_ready; ++i) {
            for (int d = 0; search_dirs[d] != nullptr && !is_ready; ++d) {
                std::string path = std::string(search_dirs[d]) + preferred_fonts[i];
                FILE* f = fopen(path.c_str(), "rb");
                if (f) {
                    fseek(f, 0, SEEK_END);
                    long sz = ftell(f);
                    fseek(f, 0, SEEK_SET);
                    if (sz > 0) {
                        font_bytes.resize(sz);
                        if (fread(font_bytes.data(), 1, sz, f) == (size_t)sz) {
                            int offset = stbtt_GetFontOffsetForIndex(font_bytes.data(), 0);
                            if (offset < 0) offset = 0;
                            if (stbtt_InitFont(&info, font_bytes.data(), offset)) {
                                is_ready = true;
                            }
                        }
                    }
                    fclose(f);
                }
            }
        }
    }
};

inline SystemFontEngine s_system_font_engine;
struct GpuBuffer {
    int id = 0;
    std::vector<double> data; // vertex floats (x, y, r, g, b, a)
};

struct GpuPipeline {
    int id = 0;
    int shader_id = 0;
    int primitive_type = 0; // 0 = rect, 1 = triangle, 2 = vertex_stream
};

struct GpuBindings {
    int id = 0;
    int vertex_buffer_id = 0;
    int index_buffer_id = 0;
};

// CPU-side copy of an uploaded texture (RGBA8, row-major). Used by the
// software rasterizer for parity with the GPU sampling path; the Sokol
// backend keeps its own sg_image.
struct GpuImage {
    int id = 0;
    int w = 0;
    int h = 0;
    std::vector<uint8_t> pixels; // w*h*4 RGBA8
};



template<class Access>
class SoftwareGraphicsResource : public Access::Base {
    using RegisterValue=typename Access::Value;
    using LmList=typename Access::List;
    static inline const RegisterValue value_true=Access::boolean(true);
    static inline const RegisterValue value_false=Access::boolean(false);
    static inline const RegisterValue value_nil=Access::nil();
    static constexpr int list_type=1;
    static void* check_header_type(RegisterValue value,int) {return Access::list(value);}
    static int64_t register_value_to_i64(RegisterValue value) {return Access::integer(value);}
    static double register_value_to_double(RegisterValue value) {return Access::floating(value);}
    static const char* register_value_to_cstr(RegisterValue value) {return Access::string(value);}
    static size_t lm_list_len(LmList* list) {return Access::length(list);}
    static RegisterValue lm_list_get(LmList* list,size_t index) {return Access::item(list,index);}
    static LmList* lm_list_new() {return Access::new_list();}
    static void lm_list_append(LmList* list,RegisterValue value) {Access::append(list,value);}
    static RegisterValue pointer_value(LmList* list) {return Access::pointer(list);}
    static RegisterValue integer_value(int64_t value) {return Access::number(value);}
    static RegisterValue make_i64(int64_t value) {return Access::make_integer(value);}
public:
    struct WindowEvent {
        int type;
        int x;
        int y;
        int key;
    };

    SoftwareGraphicsResource() : width_(800), height_(600), pass_active_(false) {
        pixels_.resize(width_ * height_ * 4, 0);
        depth_.assign(static_cast<std::size_t>(width_) * height_, 1.0f);
    }

    struct ClipRect {
        int x0 = 0;
        int y0 = 0;
        int x1 = 100000;
        int y1 = 100000;
    };
    std::vector<ClipRect> clip_stack_;

    ClipRect get_current_clip() const {
        if (clip_stack_.empty()) {
            return ClipRect{0, 0, width_, height_};
        }
        return clip_stack_.back();
    }

    void push_clip(int x, int y, int w, int h) {
        ClipRect current = get_current_clip();
        int new_x0 = std::clamp(x, 0, width_);
        int new_y0 = std::clamp(y, 0, height_);
        int new_x1 = std::clamp(x + w, 0, width_);
        int new_y1 = std::clamp(y + h, 0, height_);

        ClipRect intersected;
        intersected.x0 = std::max(current.x0, new_x0);
        intersected.y0 = std::max(current.y0, new_y0);
        intersected.x1 = std::min(current.x1, new_x1);
        intersected.y1 = std::min(current.y1, new_y1);
        if (intersected.x1 < intersected.x0) intersected.x1 = intersected.x0;
        if (intersected.y1 < intersected.y0) intersected.y1 = intersected.y0;

        clip_stack_.push_back(intersected);
    }

    void pop_clip() {
        if (!clip_stack_.empty()) {
            clip_stack_.pop_back();
        }
    }

    void resize_framebuffer(int width, int height) {
        if (width <= 0 || height <= 0 || (width == width_ && height == height_)) return;
        width_ = width;
        height_ = height;
        pixels_.assign(static_cast<std::size_t>(width_) * height_ * 4, 0);
        depth_.assign(static_cast<std::size_t>(width_) * height_, 1.0f);
        clip_stack_.clear();
    }

    void push_native_event(int type, int x, int y, int key) {
        std::lock_guard<std::mutex> lock(event_mutex_);
        native_events_.push_back({type, x, y, key});
    }

    ResourceType getType() const override { return ResourceType::GRAPHICS; }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void*) override {
        // GPU backend: when sokol_gfx is live (windowed D3D11), decode ops
        // into GfxCommands for the sapp thread. Headless keeps this CPU path.
        if (::sokol_gfx_runtime().ready()) return call_gpu(op, args);
        switch (op) {
            case ResourceOperation::OPEN: {
                int w = 800, h = 600;
                if (!args.empty()) {
                    if (auto* list = reinterpret_cast<LmList*>(check_header_type(args[0], list_type))) {
                        if (lm_list_len(list) > 0) w = static_cast<int>(register_value_to_i64(lm_list_get(list, 0)));
                        if (lm_list_len(list) > 1) h = static_cast<int>(register_value_to_i64(lm_list_get(list, 1)));
                    } else {
                        w = static_cast<int>(register_value_to_i64(args[0]));
                        if (args.size() > 1) h = static_cast<int>(register_value_to_i64(args[1]));
                    }
                }
                if (w > 0 && h > 0) {
                    width_ = w;
                    height_ = h;
                    pixels_.assign(width_ * height_ * 4, 0);
                    depth_.assign(static_cast<std::size_t>(width_) * height_, 1.0f);
                }
                return value_true;
            }
            case ResourceOperation::MAKE_BUFFER: {
                if (args.empty()) return value_nil;
                int buf_id = static_cast<int>(register_value_to_i64(args[0]));
                GpuBuffer buf;
                buf.id = buf_id;
                if (args.size() > 1) {
                    if (auto* list = reinterpret_cast<LmList*>(check_header_type(args[1], list_type))) {
                        size_t len = lm_list_len(list);
                        for (size_t i = 0; i < len; ++i) {
                            buf.data.push_back(register_value_to_double(lm_list_get(list, i)));
                        }
                    }
                }
                buffers_[buf_id] = buf;
                return value_true;
            }
            case ResourceOperation::MAKE_PIPELINE: {
                if (args.empty()) return value_nil;
                int pip_id = static_cast<int>(register_value_to_i64(args[0]));
                GpuPipeline pip;
                pip.id = pip_id;
                if (args.size() > 1) pip.shader_id = static_cast<int>(register_value_to_i64(args[1]));
                if (args.size() > 2) pip.primitive_type = static_cast<int>(register_value_to_i64(args[2]));
                pipelines_[pip_id] = pip;
                return value_true;
            }
            case ResourceOperation::MAKE_BINDINGS: {
                if (args.empty()) return value_nil;
                int bind_id = static_cast<int>(register_value_to_i64(args[0]));
                GpuBindings b;
                b.id = bind_id;
                if (args.size() > 1) b.vertex_buffer_id = static_cast<int>(register_value_to_i64(args[1]));
                if (args.size() > 2) b.index_buffer_id = static_cast<int>(register_value_to_i64(args[2]));
                bindings_[bind_id] = b;
                return value_true;
            }
            case ResourceOperation::MAKE_IMAGE: {
                // args: [id, w, h, pixels?] — pixels is an optional flat
                // RGBA8 byte list. Empty/missing pixels still registers the id.
                if (args.size() < 3) return value_nil;
                GpuImage img;
                img.id = static_cast<int>(register_value_to_i64(args[0]));
                img.w = static_cast<int>(register_value_to_i64(args[1]));
                img.h = static_cast<int>(register_value_to_i64(args[2]));
                if (args.size() > 3) {
                    if (auto* list = reinterpret_cast<LmList*>(check_header_type(args[3], list_type))) {
                        size_t n = lm_list_len(list);
                        img.pixels.reserve(n);
                        for (size_t i = 0; i < n; ++i)
                            img.pixels.push_back(static_cast<uint8_t>(register_value_to_i64(lm_list_get(list, i))));
                    }
                }
                if (img.w > 0 && img.h > 0 && img.pixels.size() >= static_cast<size_t>(img.w) * img.h * 4) {
                    images_[img.id] = std::move(img);
                }
                return value_true;
            }
            case ResourceOperation::PUSH: {
                double x = 0.0, y = 0.0, w = width_, h = height_;
                if (!args.empty()) {
                    if (auto* list = reinterpret_cast<LmList*>(check_header_type(args[0], list_type))) {
                        if (lm_list_len(list) > 0) x = register_value_to_double(lm_list_get(list, 0));
                        if (lm_list_len(list) > 1) y = register_value_to_double(lm_list_get(list, 1));
                        if (lm_list_len(list) > 2) w = register_value_to_double(lm_list_get(list, 2));
                        if (lm_list_len(list) > 3) h = register_value_to_double(lm_list_get(list, 3));
                    } else {
                        x = register_value_to_double(args[0]);
                        if (args.size() > 1) y = register_value_to_double(args[1]);
                        if (args.size() > 2) w = register_value_to_double(args[2]);
                        if (args.size() > 3) h = register_value_to_double(args[3]);
                    }
                }
                push_clip(static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h));
                return value_true;
            }
            case ResourceOperation::POP: {
                pop_clip();
                return value_true;
            }
            case ResourceOperation::FILL: {
                clip_stack_.clear();
                pass_active_ = true;
                double r = 0.0, g = 0.0, b = 0.0, a = 1.0;
                int req_w = 0, req_h = 0;
                if (!args.empty()) {
                    if (auto* list = reinterpret_cast<LmList*>(check_header_type(args[0], list_type))) {
                        size_t llen = lm_list_len(list);
                        if (llen >= 6) {
                            req_w = static_cast<int>(register_value_to_i64(lm_list_get(list, 0)));
                            req_h = static_cast<int>(register_value_to_i64(lm_list_get(list, 1)));
                            r = register_value_to_double(lm_list_get(list, 2));
                            g = register_value_to_double(lm_list_get(list, 3));
                            b = register_value_to_double(lm_list_get(list, 4));
                            a = register_value_to_double(lm_list_get(list, 5));
                        } else {
                            if (llen > 0) r = register_value_to_double(lm_list_get(list, 0));
                            if (llen > 1) g = register_value_to_double(lm_list_get(list, 1));
                            if (llen > 2) b = register_value_to_double(lm_list_get(list, 2));
                            if (llen > 3) a = register_value_to_double(lm_list_get(list, 3));
                        }
                    } else {
                        if (args.size() >= 6) {
                            req_w = static_cast<int>(register_value_to_i64(args[0]));
                            req_h = static_cast<int>(register_value_to_i64(args[1]));
                            r = register_value_to_double(args[2]);
                            g = register_value_to_double(args[3]);
                            b = register_value_to_double(args[4]);
                            a = register_value_to_double(args[5]);
                        } else {
                            r = register_value_to_double(args[0]);
                            if (args.size() > 1) g = register_value_to_double(args[1]);
                            if (args.size() > 2) b = register_value_to_double(args[2]);
                            if (args.size() > 3) a = register_value_to_double(args[3]);
                        }
                    }
                }

                if (req_w > 0 && req_h > 0 && (req_w != width_ || req_h != height_)) {
                    resize_framebuffer(req_w, req_h);
                }

                uint8_t ru = static_cast<uint8_t>(std::clamp(r * 255.0, 0.0, 255.0));
                uint8_t gu = static_cast<uint8_t>(std::clamp(g * 255.0, 0.0, 255.0));
                uint8_t bu = static_cast<uint8_t>(std::clamp(b * 255.0, 0.0, 255.0));
                uint8_t au = static_cast<uint8_t>(std::clamp(a * 255.0, 0.0, 255.0));

                uint32_t pixel32 = ru | (static_cast<uint32_t>(gu) << 8) |
                                   (static_cast<uint32_t>(bu) << 16) |
                                   (static_cast<uint32_t>(au) << 24);
                auto* p32 = reinterpret_cast<uint32_t*>(pixels_.data());
                std::fill_n(p32, pixels_.size() / 4, pixel32);
                depth_.assign(static_cast<std::size_t>(width_) * height_, 1.0f);
                return value_true;
            }
            case ResourceOperation::END_PASS: {
                if (!pass_active_) return value_false;
                pass_active_ = false;
                return value_true;
            }
            case ResourceOperation::APPLY_PIPELINE: {
                if (!pass_active_) return value_false;
                if (!args.empty()) {
                    if (auto* list = reinterpret_cast<LmList*>(check_header_type(args[0], list_type))) {
                        if (lm_list_len(list) > 0) current_pipeline_ = static_cast<int>(register_value_to_i64(lm_list_get(list, 0)));
                    } else {
                        current_pipeline_ = static_cast<int>(register_value_to_i64(args[0]));
                    }
                }
                return value_true;
            }
            case ResourceOperation::APPLY_BINDINGS: {
                if (!pass_active_) return value_false;
                current_uniforms_.clear();
                current_img_ = 0;
                if (!args.empty()) {
                    if (auto* list = reinterpret_cast<LmList*>(check_header_type(args[0], list_type))) {
                        if (lm_list_len(list) > 0) current_vbuf_ = static_cast<int>(register_value_to_i64(lm_list_get(list, 0)));
                        if (lm_list_len(list) > 1) current_ibuf_ = static_cast<int>(register_value_to_i64(lm_list_get(list, 1)));
                        if (lm_list_len(list) > 2) {
                            if (auto* ulist = reinterpret_cast<LmList*>(check_header_type(lm_list_get(list, 2), list_type))) {
                                size_t ulen = lm_list_len(ulist);
                                current_uniforms_.reserve(ulen);
                                for (size_t ui = 0; ui < ulen; ++ui) {
                                    current_uniforms_.push_back(register_value_to_double(lm_list_get(ulist, ui)));
                                }
                            }
                        }
                        // slots 3/4: texture image id + sampler id (d3 vertex stream)
                        if (lm_list_len(list) > 3) current_img_ = static_cast<int>(register_value_to_i64(lm_list_get(list, 3)));
                    } else {
                        current_vbuf_ = static_cast<int>(register_value_to_i64(args[0]));
                        if (args.size() > 1) current_ibuf_ = static_cast<int>(register_value_to_i64(args[1]));
                        if (args.size() > 2) {
                            if (auto* ulist = reinterpret_cast<LmList*>(check_header_type(args[2], list_type))) {
                                size_t ulen = lm_list_len(ulist);
                                current_uniforms_.reserve(ulen);
                                for (size_t ui = 0; ui < ulen; ++ui) {
                                    current_uniforms_.push_back(register_value_to_double(lm_list_get(ulist, ui)));
                                }
                            }
                        }
                    }
                }
                return value_true;
            }
            case ResourceOperation::DRAW: {
                if (!pass_active_) return value_false;
                auto vbuf_it = buffers_.find(current_vbuf_);
                if (vbuf_it == buffers_.end() || vbuf_it->second.data.empty()) return value_false;

                auto pip_it = pipelines_.find(current_pipeline_);
                int primitive_type = (pip_it != pipelines_.end()) ? pip_it->second.primitive_type : 0;

                const auto& data = vbuf_it->second.data;

                if (primitive_type == 2) {
                    draw_vertex_stream(vbuf_it->second, current_ibuf_, current_uniforms_);
                    return value_true;
                }

                if (primitive_type == 1 && data.size() >= 10) { // Triangle Primitive (x1, y1, x2, y2, x3, y3, r, g, b, a)
                    if (width_ <= 0 || height_ <= 0 || pixels_.empty()) return value_true;
                    double x1 = data[0], y1 = data[1], x2 = data[2], y2 = data[3], x3 = data[4], y3 = data[5];
                    double r = data[6], g = data[7], b = data[8], a = data[9];

                    ClipRect clip = get_current_clip();
                    int min_x = std::clamp(static_cast<int>(std::floor(std::min({x1, x2, x3}))), std::max(0, clip.x0), std::min(width_, clip.x1));
                    int max_x = std::clamp(static_cast<int>(std::ceil(std::max({x1, x2, x3}))), std::max(0, clip.x0), std::min(width_, clip.x1));
                    int min_y = std::clamp(static_cast<int>(std::floor(std::min({y1, y2, y3}))), std::max(0, clip.y0), std::min(height_, clip.y1));
                    int max_y = std::clamp(static_cast<int>(std::ceil(std::max({y1, y2, y3}))), std::max(0, clip.y0), std::min(height_, clip.y1));
                    if (max_x <= min_x || max_y <= min_y) return value_true;

                    auto edge = [](double ax, double ay, double bx, double by, double cx, double cy) {
                        return (cx - ax) * (by - ay) - (cy - ay) * (bx - ax);
                    };

                    uint8_t ru = static_cast<uint8_t>(std::clamp(r * 255.0, 0.0, 255.0));
                    uint8_t gu = static_cast<uint8_t>(std::clamp(g * 255.0, 0.0, 255.0));
                    uint8_t bu = static_cast<uint8_t>(std::clamp(b * 255.0, 0.0, 255.0));
                    uint8_t au = static_cast<uint8_t>(std::clamp(a * 255.0, 0.0, 255.0));

                    for (int py = min_y; py < max_y; ++py) {
                        for (int px = min_x; px < max_x; ++px) {
                            double pX = px + 0.5;
                            double pY = py + 0.5;
                            double w0 = edge(x2, y2, x3, y3, pX, pY);
                            double w1 = edge(x3, y3, x1, y1, pX, pY);
                            double w2 = edge(x1, y1, x2, y2, pX, pY);

                            if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0)) {
                                size_t idx = static_cast<size_t>(py * width_ + px) * 4;
                                if (idx + 3 >= pixels_.size()) continue;
                                if (au >= 255) {
                                    pixels_[idx]     = ru;
                                    pixels_[idx + 1] = gu;
                                    pixels_[idx + 2] = bu;
                                    pixels_[idx + 3] = 255;
                                } else if (au > 0) {
                                    float af = au / 255.0f;
                                    float inv = 1.0f - af;
                                    pixels_[idx]     = static_cast<uint8_t>(ru * af + pixels_[idx] * inv);
                                    pixels_[idx + 1] = static_cast<uint8_t>(gu * af + pixels_[idx + 1] * inv);
                                    pixels_[idx + 2] = static_cast<uint8_t>(bu * af + pixels_[idx + 2] * inv);
                                    pixels_[idx + 3] = std::max(pixels_[idx + 3], au);
                                }
                            }
                        }
                    }
                } else if (data.size() >= 8) { // Rectangle Primitive (x, y, w, h, r, g, b, a)
                    if (width_ <= 0 || height_ <= 0 || pixels_.empty()) return value_true;
                    double x = data[0], y = data[1], w = data[2], h = data[3];
                    double r = data[4], g = data[5], b = data[6], a = data[7];

                    ClipRect clip = get_current_clip();
                    int x0 = std::clamp(static_cast<int>(x), std::max(0, clip.x0), std::min(width_, clip.x1));
                    int y0 = std::clamp(static_cast<int>(y), std::max(0, clip.y0), std::min(height_, clip.y1));
                    int x1 = std::clamp(static_cast<int>(x + w), std::max(0, clip.x0), std::min(width_, clip.x1));
                    int y1 = std::clamp(static_cast<int>(y + h), std::max(0, clip.y0), std::min(height_, clip.y1));
                    if (x1 <= x0 || y1 <= y0) return value_true;

                    uint8_t ru = static_cast<uint8_t>(std::clamp(r * 255.0, 0.0, 255.0));
                    uint8_t gu = static_cast<uint8_t>(std::clamp(g * 255.0, 0.0, 255.0));
                    uint8_t bu = static_cast<uint8_t>(std::clamp(b * 255.0, 0.0, 255.0));
                    uint8_t au = static_cast<uint8_t>(std::clamp(a * 255.0, 0.0, 255.0));

                    uint32_t pixel32 = ru | (static_cast<uint32_t>(gu) << 8) |
                                       (static_cast<uint32_t>(bu) << 16) |
                                       (static_cast<uint32_t>(au) << 24);
                    auto* p32 = reinterpret_cast<uint32_t*>(pixels_.data());
                    int span = x1 - x0;
                    if (span > 0) {
                        for (int py = y0; py < y1; ++py) {
                            std::fill_n(p32 + (py * width_ + x0), span, pixel32);
                        }
                    }
                }
                return value_true;
            }
            case ResourceOperation::DRAW_RECT: {
                double x = 0.0, y = 0.0, w = 0.0, h = 0.0;
                double r = 1.0, g = 1.0, b = 1.0, a = 1.0;
                double rad = 0.0;
                double border_w = 0.0;
                if (!args.empty()) {
                    if (auto* list = reinterpret_cast<LmList*>(check_header_type(args[0], list_type))) {
                        if (lm_list_len(list) > 0) x = register_value_to_double(lm_list_get(list, 0));
                        if (lm_list_len(list) > 1) y = register_value_to_double(lm_list_get(list, 1));
                        if (lm_list_len(list) > 2) w = register_value_to_double(lm_list_get(list, 2));
                        if (lm_list_len(list) > 3) h = register_value_to_double(lm_list_get(list, 3));
                        if (lm_list_len(list) > 4) r = register_value_to_double(lm_list_get(list, 4));
                        if (lm_list_len(list) > 5) g = register_value_to_double(lm_list_get(list, 5));
                        if (lm_list_len(list) > 6) b = register_value_to_double(lm_list_get(list, 6));
                        if (lm_list_len(list) > 7) a = register_value_to_double(lm_list_get(list, 7));
                        size_t llen = lm_list_len(list);
                        if (llen > 0) x = register_value_to_double(lm_list_get(list, 0));
                        if (llen > 1) y = register_value_to_double(lm_list_get(list, 1));
                        if (llen > 2) w = register_value_to_double(lm_list_get(list, 2));
                        if (llen > 3) h = register_value_to_double(lm_list_get(list, 3));
                        if (llen > 4) r = register_value_to_double(lm_list_get(list, 4));
                        if (llen > 5) g = register_value_to_double(lm_list_get(list, 5));
                        if (llen > 6) b = register_value_to_double(lm_list_get(list, 6));
                        if (llen > 7) a = register_value_to_double(lm_list_get(list, 7));
                        if (llen > 8) rad = register_value_to_double(lm_list_get(list, 8));
                        if (llen > 9) border_w = register_value_to_double(lm_list_get(list, 9));
                    } else {
                        x = register_value_to_double(args[0]);
                        if (args.size() > 1) y = register_value_to_double(args[1]);
                        if (args.size() > 2) w = register_value_to_double(args[2]);
                        if (args.size() > 3) h = register_value_to_double(args[3]);
                        if (args.size() > 4) r = register_value_to_double(args[4]);
                        if (args.size() > 5) g = register_value_to_double(args[5]);
                        if (args.size() > 6) b = register_value_to_double(args[6]);
                        if (args.size() > 7) a = register_value_to_double(args[7]);
                        if (args.size() > 8) rad = register_value_to_double(args[8]);
                        if (args.size() > 9) border_w = register_value_to_double(args[9]);
                    }
                }

                if (width_ <= 0 || height_ <= 0 || pixels_.empty()) return value_true;
                if (w <= 0.0 || h <= 0.0) return value_true;

                ClipRect clip = get_current_clip();
                int x0 = std::clamp(static_cast<int>(std::floor(x)), std::max(0, clip.x0), std::min(width_, clip.x1));
                int y0 = std::clamp(static_cast<int>(std::floor(y)), std::max(0, clip.y0), std::min(height_, clip.y1));
                int x1 = std::clamp(static_cast<int>(std::ceil(x + w)), std::max(0, clip.x0), std::min(width_, clip.x1));
                int y1 = std::clamp(static_cast<int>(std::ceil(y + h)), std::max(0, clip.y0), std::min(height_, clip.y1));
                if (x1 <= x0 || y1 <= y0) return value_true;

                uint8_t ru = static_cast<uint8_t>(std::clamp(r * 255.0, 0.0, 255.0));
                uint8_t gu = static_cast<uint8_t>(std::clamp(g * 255.0, 0.0, 255.0));
                uint8_t bu = static_cast<uint8_t>(std::clamp(b * 255.0, 0.0, 255.0));
                uint8_t au = static_cast<uint8_t>(std::clamp(a * 255.0, 0.0, 255.0));
                float alpha_base = static_cast<float>(std::clamp(a, 0.0, 1.0));
                if (alpha_base <= 0.0f) return value_true;

                if (rad <= 0.5 && border_w <= 0.0) {
                    if (alpha_base >= 0.999f) {
                        uint32_t pixel32 = ru | (static_cast<uint32_t>(gu) << 8) |
                                           (static_cast<uint32_t>(bu) << 16) |
                                           (255u << 24);
                        auto* p32 = reinterpret_cast<uint32_t*>(pixels_.data());
                        int span = x1 - x0;
                        if (span > 0) {
                            for (int py = y0; py < y1; ++py) {
                                std::fill_n(p32 + (py * width_ + x0), span, pixel32);
                            }
                        }
                    } else {
                        float inv_a = 1.0f - alpha_base;
                        for (int py = y0; py < y1; ++py) {
                            for (int px = x0; px < x1; ++px) {
                                size_t idx = static_cast<size_t>(py * width_ + px) * 4;
                                pixels_[idx]     = static_cast<uint8_t>(ru * alpha_base + pixels_[idx] * inv_a);
                                pixels_[idx + 1] = static_cast<uint8_t>(gu * alpha_base + pixels_[idx + 1] * inv_a);
                                pixels_[idx + 2] = static_cast<uint8_t>(bu * alpha_base + pixels_[idx + 2] * inv_a);
                                pixels_[idx + 3] = std::max(pixels_[idx + 3], static_cast<uint8_t>(alpha_base * 255.0f));
                            }
                        }
                    }
                } else {
                    double max_r = std::min(w * 0.5, h * 0.5);
                    if (rad > max_r) rad = max_r;
                    if (rad < 0.0) rad = 0.0;

                    double half_w = w * 0.5;
                    double half_h = h * 0.5;
                    double cx = x + half_w;
                    double cy = y + half_h;
                    double bx = half_w - rad;
                    double by = half_h - rad;

                    auto eval_sdf = [&](double px, double py) -> double {
                        double qx = std::abs(px - cx) - bx;
                        double qy = std::abs(py - cy) - by;
                        double ox = std::max(qx, 0.0);
                        double oy = std::max(qy, 0.0);
                        double outside = std::sqrt(ox * ox + oy * oy);
                        double inside = std::min(std::max(qx, qy), 0.0);
                        return outside + inside - rad;
                    };

                    auto stroke_dist = [&](double d) -> double {
                        return std::max(d, -(d + border_w));
                    };

                    for (int py = y0; py < y1; ++py) {
                        double pY = py + 0.5;
                        for (int px = x0; px < x1; ++px) {
                            double pX = px + 0.5;

                            float cov = 0.0f;
                            double d_center = eval_sdf(pX, pY);

                            if (border_w <= 0.0) {
                                if (d_center < -1.5) {
                                    cov = 1.0f;
                                } else if (d_center > 1.5) {
                                    continue;
                                } else {
                                    double d0 = eval_sdf(pX - 0.25, pY - 0.25);
                                    double d1 = eval_sdf(pX + 0.25, pY - 0.25);
                                    double d2 = eval_sdf(pX - 0.25, pY + 0.25);
                                    double d3 = eval_sdf(pX + 0.25, pY + 0.25);

                                    auto sample_cov = [](double d) -> float {
                                        return static_cast<float>(std::clamp(0.5 - d, 0.0, 1.0));
                                    };
                                    cov = (sample_cov(d0) + sample_cov(d1) + sample_cov(d2) + sample_cov(d3)) * 0.25f;
                                }
                            } else {
                                double s_center = stroke_dist(d_center);
                                if (s_center > 1.5) {
                                    continue;
                                } else if (s_center < -1.5) {
                                    cov = 1.0f;
                                } else {
                                    double d0 = eval_sdf(pX - 0.25, pY - 0.25);
                                    double d1 = eval_sdf(pX + 0.25, pY - 0.25);
                                    double d2 = eval_sdf(pX - 0.25, pY + 0.25);
                                    double d3 = eval_sdf(pX + 0.25, pY + 0.25);

                                    auto sample_cov = [&](double d) -> float {
                                        double s = stroke_dist(d);
                                        return static_cast<float>(std::clamp(0.5 - s, 0.0, 1.0));
                                    };
                                    cov = (sample_cov(d0) + sample_cov(d1) + sample_cov(d2) + sample_cov(d3)) * 0.25f;
                                }
                            }

                            float final_a = alpha_base * cov;
                            if (final_a <= 0.001f) continue;

                            size_t idx = static_cast<size_t>(py * width_ + px) * 4;
                            if (idx + 3 >= pixels_.size()) continue;
                            if (final_a >= 0.999f) {
                                pixels_[idx]     = ru;
                                pixels_[idx + 1] = gu;
                                pixels_[idx + 2] = bu;
                                pixels_[idx + 3] = 255;
                            } else {
                                float inv = 1.0f - final_a;
                                pixels_[idx]     = static_cast<uint8_t>(ru * final_a + pixels_[idx] * inv);
                                pixels_[idx + 1] = static_cast<uint8_t>(gu * final_a + pixels_[idx + 1] * inv);
                                pixels_[idx + 2] = static_cast<uint8_t>(bu * final_a + pixels_[idx + 2] * inv);
                                pixels_[idx + 3] = std::max(pixels_[idx + 3], static_cast<uint8_t>(final_a * 255.0f));
                            }
                        }
                    }
                }
                return value_true;
            }
            case ResourceOperation::DRAW_TRIANGLE: {
                double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0, x3 = 0.0, y3 = 0.0;
                double r = 1.0, g = 1.0, b = 1.0, a = 1.0;
                if (!args.empty()) {
                    if (auto* list = reinterpret_cast<LmList*>(check_header_type(args[0], list_type))) {
                        if (lm_list_len(list) > 0) x1 = register_value_to_double(lm_list_get(list, 0));
                        if (lm_list_len(list) > 1) y1 = register_value_to_double(lm_list_get(list, 1));
                        if (lm_list_len(list) > 2) x2 = register_value_to_double(lm_list_get(list, 2));
                        if (lm_list_len(list) > 3) y2 = register_value_to_double(lm_list_get(list, 3));
                        if (lm_list_len(list) > 4) x3 = register_value_to_double(lm_list_get(list, 4));
                        if (lm_list_len(list) > 5) y3 = register_value_to_double(lm_list_get(list, 5));
                        if (lm_list_len(list) > 6) r  = register_value_to_double(lm_list_get(list, 6));
                        if (lm_list_len(list) > 7) g  = register_value_to_double(lm_list_get(list, 7));
                        if (lm_list_len(list) > 8) b  = register_value_to_double(lm_list_get(list, 8));
                        if (lm_list_len(list) > 9) a  = register_value_to_double(lm_list_get(list, 9));
                    } else if (args.size() >= 6) {
                        x1 = register_value_to_double(args[0]);
                        y1 = register_value_to_double(args[1]);
                        x2 = register_value_to_double(args[2]);
                        y2 = register_value_to_double(args[3]);
                        x3 = register_value_to_double(args[4]);
                        y3 = register_value_to_double(args[5]);
                        if (args.size() > 6) r = register_value_to_double(args[6]);
                        if (args.size() > 7) g = register_value_to_double(args[7]);
                        if (args.size() > 8) b = register_value_to_double(args[8]);
                        if (args.size() > 9) a = register_value_to_double(args[9]);
                    }
                }

                if (width_ <= 0 || height_ <= 0 || pixels_.empty()) return value_true;

                ClipRect clip = get_current_clip();
                int min_x = std::clamp(static_cast<int>(std::floor(std::min({x1, x2, x3}))), std::max(0, clip.x0), std::min(width_, clip.x1));
                int max_x = std::clamp(static_cast<int>(std::ceil(std::max({x1, x2, x3}))), std::max(0, clip.x0), std::min(width_, clip.x1));
                int min_y = std::clamp(static_cast<int>(std::floor(std::min({y1, y2, y3}))), std::max(0, clip.y0), std::min(height_, clip.y1));
                int max_y = std::clamp(static_cast<int>(std::ceil(std::max({y1, y2, y3}))), std::max(0, clip.y0), std::min(height_, clip.y1));
                if (max_x <= min_x || max_y <= min_y) return value_true;

                auto edge = [](double ax, double ay, double bx, double by, double cx, double cy) {
                    return (cx - ax) * (by - ay) - (cy - ay) * (bx - ax);
                };

                uint8_t ru = static_cast<uint8_t>(std::clamp(r * 255.0, 0.0, 255.0));
                uint8_t gu = static_cast<uint8_t>(std::clamp(g * 255.0, 0.0, 255.0));
                uint8_t bu = static_cast<uint8_t>(std::clamp(b * 255.0, 0.0, 255.0));
                uint8_t au = static_cast<uint8_t>(std::clamp(a * 255.0, 0.0, 255.0));

                double step_x0 = y3 - y2;
                double step_y0 = -(x3 - x2);
                double step_x1 = y1 - y3;
                double step_y1 = -(x1 - x3);
                double step_x2 = y2 - y1;
                double step_y2 = -(x2 - x1);

                double start_px = min_x + 0.5;
                double start_py = min_y + 0.5;
                double w0_row = edge(x2, y2, x3, y3, start_px, start_py);
                double w1_row = edge(x3, y3, x1, y1, start_px, start_py);
                double w2_row = edge(x1, y1, x2, y2, start_px, start_py);

                for (int py = min_y; py < max_y; ++py) {
                    double w0 = w0_row;
                    double w1 = w1_row;
                    double w2 = w2_row;
                    size_t idx = static_cast<size_t>(py * width_ + min_x) * 4;

                    for (int px = min_x; px < max_x; ++px) {
                        if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0)) {
                            if (idx + 3 < pixels_.size()) {
                                if (au >= 255) {
                                    pixels_[idx]     = ru;
                                    pixels_[idx + 1] = gu;
                                    pixels_[idx + 2] = bu;
                                    pixels_[idx + 3] = 255;
                                } else if (au > 0) {
                                    float af = au / 255.0f;
                                    float inv = 1.0f - af;
                                    pixels_[idx]     = static_cast<uint8_t>(ru * af + pixels_[idx] * inv);
                                    pixels_[idx + 1] = static_cast<uint8_t>(gu * af + pixels_[idx + 1] * inv);
                                    pixels_[idx + 2] = static_cast<uint8_t>(bu * af + pixels_[idx + 2] * inv);
                                    pixels_[idx + 3] = std::max(pixels_[idx + 3], au);
                                }
                            }
                        }
                        w0 += step_x0;
                        w1 += step_x1;
                        w2 += step_x2;
                        idx += 4;
                    }
                    w0_row += step_y0;
                    w1_row += step_y1;
                    w2_row += step_y2;
                }
                return value_true;
            }
            case ResourceOperation::DRAW_TEXT: {
                std::string text = "";
                double x = 0.0, y = 0.0;
                double r = 1.0, g = 1.0, b = 1.0, a = 1.0;
                int scale = 2;
                if (!args.empty()) {
                    if (auto* list = reinterpret_cast<LmList*>(check_header_type(args[0], list_type))) {
                        if (lm_list_len(list) > 0) {
                            const char* s = register_value_to_cstr(lm_list_get(list, 0));
                            if (s) text = s;
                        }
                        if (lm_list_len(list) > 1) x = register_value_to_double(lm_list_get(list, 1));
                        if (lm_list_len(list) > 2) y = register_value_to_double(lm_list_get(list, 2));
                        if (lm_list_len(list) > 3) r = register_value_to_double(lm_list_get(list, 3));
                        if (lm_list_len(list) > 4) g = register_value_to_double(lm_list_get(list, 4));
                        if (lm_list_len(list) > 5) b = register_value_to_double(lm_list_get(list, 5));
                        if (lm_list_len(list) > 6) a = register_value_to_double(lm_list_get(list, 6));
                        if (lm_list_len(list) > 7) {
                            int s = static_cast<int>(register_value_to_i64(lm_list_get(list, 7)));
                            if (s > 0) scale = s;
                        }
                    } else {
                        const char* s = register_value_to_cstr(args[0]);
                        if (s) text = s;
                        if (args.size() > 1) x = register_value_to_double(args[1]);
                        if (args.size() > 2) y = register_value_to_double(args[2]);
                        if (args.size() > 3) r = register_value_to_double(args[3]);
                        if (args.size() > 4) g = register_value_to_double(args[4]);
                        if (args.size() > 5) b = register_value_to_double(args[5]);
                        if (args.size() > 6) a = register_value_to_double(args[6]);
                        if (args.size() > 7) {
                            int s = static_cast<int>(register_value_to_i64(args[7]));
                            if (s > 0) scale = s;
                        }
                    }
                }

                uint8_t ru = static_cast<uint8_t>(std::clamp(r * 255.0, 0.0, 255.0));
                uint8_t gu = static_cast<uint8_t>(std::clamp(g * 255.0, 0.0, 255.0));
                uint8_t bu = static_cast<uint8_t>(std::clamp(b * 255.0, 0.0, 255.0));
                uint8_t au = static_cast<uint8_t>(std::clamp(a * 255.0, 0.0, 255.0));

                ClipRect clip = get_current_clip();

                if (!s_system_font_engine.attempted) {
                    s_system_font_engine.init();
                }

                if (s_system_font_engine.is_ready) {
                    float font_size = 13.0f;
                    if (scale == 2) font_size = 20.0f;
                    else if (scale == 3) font_size = 26.0f;
                    else if (scale > 3 && scale <= 7) font_size = static_cast<float>(scale * 9);
                    else if (scale > 7) font_size = static_cast<float>(scale);

                    float fscale = stbtt_ScaleForPixelHeight(&s_system_font_engine.info, font_size);
                    int ascent = 0, descent = 0, line_gap = 0;
                    stbtt_GetFontVMetrics(&s_system_font_engine.info, &ascent, &descent, &line_gap);

                    int c_x1 = 0, c_y1 = 0, c_x2 = 0, c_y2 = 0;
                    stbtt_GetCodepointBitmapBox(&s_system_font_engine.info, 'A', fscale, fscale, &c_x1, &c_y1, &c_x2, &c_y2);

                    int cursor_x = static_cast<int>(x);
                    int start_y = static_cast<int>(y);
                    int baseline_y = start_y - c_y1;
                    int line_height = static_cast<int>((ascent - descent + line_gap) * fscale + 0.5f);
                    if (line_height < static_cast<int>(font_size)) line_height = static_cast<int>(font_size);

                    for (size_t i = 0; i < text.size(); ++i) {
                        char ch = text[i];
                        if (ch == '\r') continue;
                        if (ch == '\n') {
                            start_y += line_height;
                            baseline_y = start_y - c_y1;
                            cursor_x = static_cast<int>(x);
                            continue;
                        }

                        int advance = 0, lsb = 0;
                        stbtt_GetCodepointHMetrics(&s_system_font_engine.info, static_cast<unsigned char>(ch), &advance, &lsb);

                        int b_w = 0, b_h = 0, b_xoff = 0, b_yoff = 0;
                        unsigned char* bmp = stbtt_GetCodepointBitmap(&s_system_font_engine.info, 0, fscale, static_cast<unsigned char>(ch), &b_w, &b_h, &b_xoff, &b_yoff);
                        if (bmp) {
                            int glyph_ox = cursor_x + b_xoff;
                            int glyph_oy = baseline_y + b_yoff;

                            for (int gy = 0; gy < b_h; ++gy) {
                                int py = glyph_oy + gy;
                                if (py < clip.y0 || py >= clip.y1) continue;
                                for (int gx = 0; gx < b_w; ++gx) {
                                    int px = glyph_ox + gx;
                                    if (px < clip.x0 || px >= clip.x1) continue;

                                    unsigned char cov = bmp[gy * b_w + gx];
                                    if (cov == 0) continue;

                                    size_t idx = static_cast<size_t>(py * width_ + px) * 4;
                                    float alpha_cov = (au / 255.0f) * (cov / 255.0f);
                                    pixels_[idx]     = static_cast<uint8_t>(ru * alpha_cov + pixels_[idx] * (1.0f - alpha_cov));
                                    pixels_[idx + 1] = static_cast<uint8_t>(gu * alpha_cov + pixels_[idx + 1] * (1.0f - alpha_cov));
                                    pixels_[idx + 2] = static_cast<uint8_t>(bu * alpha_cov + pixels_[idx + 2] * (1.0f - alpha_cov));
                                    pixels_[idx + 3] = std::max(pixels_[idx + 3], static_cast<uint8_t>(au * (cov / 255.0f)));
                                }
                            }
                            stbtt_FreeBitmap(bmp, nullptr);
                        }

                        cursor_x += static_cast<int>(advance * fscale + 0.5f);
                        if (i + 1 < text.size() && text[i + 1] != '\n') {
                            int kern = stbtt_GetCodepointKernAdvance(&s_system_font_engine.info, static_cast<unsigned char>(ch), static_cast<unsigned char>(text[i + 1]));
                            cursor_x += static_cast<int>(kern * fscale + 0.5f);
                        }
                    }
                    return value_true;
                }

                // Fallback to basic 8x8 font if no system font could be loaded
                int cursor_x = static_cast<int>(x);
                int start_y = static_cast<int>(y);

                for (unsigned char ch : text) {
                    if (ch == '\n') {
                        start_y += 8 * scale;
                        cursor_x = static_cast<int>(x);
                        continue;
                    }
                    if (ch < 128) {
                        for (int row = 0; row < 8; ++row) {
                            uint8_t row_bits = font8x8_basic[ch][row];
                            for (int col = 0; col < 8; ++col) {
                                if (row_bits & (1 << col)) {
                                    for (int dy = 0; dy < scale; ++dy) {
                                        for (int dx = 0; dx < scale; ++dx) {
                                            int px = cursor_x + col * scale + dx;
                                            int py = start_y + row * scale + dy;
                                            if (px >= clip.x0 && px < clip.x1 && py >= clip.y0 && py < clip.y1) {
                                                size_t idx = static_cast<size_t>(py * width_ + px) * 4;
                                                if (au == 255) {
                                                    pixels_[idx]     = ru;
                                                    pixels_[idx + 1] = gu;
                                                    pixels_[idx + 2] = bu;
                                                    pixels_[idx + 3] = 255;
                                                } else {
                                                    float alpha = au / 255.0f;
                                                    pixels_[idx]     = static_cast<uint8_t>(ru * alpha + pixels_[idx] * (1.0f - alpha));
                                                    pixels_[idx + 1] = static_cast<uint8_t>(gu * alpha + pixels_[idx + 1] * (1.0f - alpha));
                                                    pixels_[idx + 2] = static_cast<uint8_t>(bu * alpha + pixels_[idx + 2] * (1.0f - alpha));
                                                    pixels_[idx + 3] = std::max(pixels_[idx + 3], au);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    cursor_x += 8 * scale;
                }
                return value_true;
            }
            case ResourceOperation::READ: {
                int px = 0;
                int py = 0;
                if (!args.empty()) {
                    if (auto* list = reinterpret_cast<LmList*>(check_header_type(args[0], list_type))) {
                        if (lm_list_len(list) > 0) px = static_cast<int>(register_value_to_i64(lm_list_get(list, 0)));
                        if (lm_list_len(list) > 1) py = static_cast<int>(register_value_to_i64(lm_list_get(list, 1)));
                    } else {
                        px = static_cast<int>(register_value_to_i64(args[0]));
                        if (args.size() > 1) py = static_cast<int>(register_value_to_i64(args[1]));
                    }
                }
                if (px < 0 || px >= width_ || py < 0 || py >= height_) return make_i64(0);
                size_t idx = static_cast<size_t>(py * width_ + px) * 4;
                uint32_t val = (static_cast<uint32_t>(pixels_[idx]) << 24) |
                               (static_cast<uint32_t>(pixels_[idx + 1]) << 16) |
                               (static_cast<uint32_t>(pixels_[idx + 2]) << 8) |
                               (static_cast<uint32_t>(pixels_[idx + 3]));
                return make_i64(static_cast<int64_t>(val));
            }
            case ResourceOperation::SPAWN: {
                int w = width_, h = height_;
                std::string title = "Lymar Application";
                bool resizable = true;
                if (!args.empty()) {
                    if (auto* list = reinterpret_cast<LmList*>(check_header_type(args[0], list_type))) {
                        if (lm_list_len(list) > 0) w = static_cast<int>(register_value_to_i64(lm_list_get(list, 0)));
                        if (lm_list_len(list) > 1) h = static_cast<int>(register_value_to_i64(lm_list_get(list, 1)));
                        if (lm_list_len(list) > 2) {
                            const char* s = register_value_to_cstr(lm_list_get(list, 2));
                            if (s) title = s;
                        }
                        if (lm_list_len(list) > 3) {
                            resizable = register_value_to_i64(lm_list_get(list, 3)) != 0;
                        }
                    } else {
                        w = static_cast<int>(register_value_to_i64(args[0]));
                        if (args.size() > 1) h = static_cast<int>(register_value_to_i64(args[1]));
                        if (args.size() > 2) {
                            const char* s = register_value_to_cstr(args[2]);
                            if (s) title = s;
                        }
                        if (args.size() > 3) {
                            resizable = register_value_to_i64(args[3]) != 0;
                        }
                    }
                }
                if (w > 0 && h > 0) {
                    width_ = w;
                    height_ = h;
                    pixels_.assign(width_ * height_ * 4, 0);
                    depth_.assign(static_cast<std::size_t>(width_) * height_, 1.0f);
                }
                const char* headless = std::getenv("LYMAR_HEADLESS");
                if (!(headless && std::string(headless) != "0")) {
                    sokol_app_runtime().start(SokolAppConfig{width_, height_, title, resizable, true});
                }
                return value_true;
            }
            case ResourceOperation::POLL: {
                // In native mode this is the synchronization boundary from the
                // Sokol frame callback into the VM's existing one-frame step.
                // Headless mode returns immediately.
                sokol_app_runtime().wait_for_frame();
                std::vector<RuntimeAppEvent> app_events;
                sokol_app_runtime().poll_events(app_events);
                for (const auto& ev : app_events) {
                    if (ev.type == 1) resize_framebuffer(ev.x, ev.y);
                    push_native_event(ev.type, ev.x, ev.y, ev.key);
                }
                LmList* list = lm_list_new();
                std::lock_guard<std::mutex> lock(event_mutex_);
                for (const auto& ev : native_events_) {
                    lm_list_append(list, integer_value(ev.type));
                    lm_list_append(list, integer_value(ev.x));
                    lm_list_append(list, integer_value(ev.y));
                    lm_list_append(list, integer_value(ev.key));
                }
                native_events_.clear();
                return pointer_value(list);
            }
            case ResourceOperation::FLUSH: {
                sokol_app_runtime().submit_frame(pixels_.data(), width_, height_);
                return value_true;
            }
            case ResourceOperation::CLOSE: {
                sokol_app_runtime().stop();
                return value_true;
            }
            case ResourceOperation::SET_STATE: {
                int w = 0, h = 0;
                if (!args.empty()) {
                    if (auto* list = reinterpret_cast<LmList*>(check_header_type(args[0], list_type))) {
                        if (lm_list_len(list) > 0) w = static_cast<int>(register_value_to_i64(lm_list_get(list, 0)));
                        if (lm_list_len(list) > 1) h = static_cast<int>(register_value_to_i64(lm_list_get(list, 1)));
                    } else {
                        w = static_cast<int>(register_value_to_i64(args[0]));
                        if (args.size() > 1) h = static_cast<int>(register_value_to_i64(args[1]));
                    }
                }
                if (w > 0 && h > 0) {
                    resize_framebuffer(w, h);
                    sokol_app_runtime().set_window_size(w, h);
                }
                return value_true;
            }
            default:
                return value_nil;
        }
    }

private:
    // GPU-backend op decode: mirrors the software switch above but emits
    // GfxCommands for the sokol_app thread instead of rasterizing. Text
    // (DRAW_TEXT family) is not yet implemented on the GPU path.
    RegisterValue call_gpu(ResourceOperation op, const std::vector<RegisterValue>& args) {
        auto flatten = [&](const std::vector<RegisterValue>& v) {
            std::vector<double> out;
            if (v.empty()) return out;
            if (auto* list = reinterpret_cast<LmList*>(Access::list(v[0]))) {
                size_t n = lm_list_len(list);
                out.reserve(n);
                for (size_t i = 0; i < n; ++i) out.push_back(register_value_to_double(lm_list_get(list, i)));
            } else {
                out.reserve(v.size());
                for (auto& e : v) out.push_back(register_value_to_double(e));
            }
            return out;
        };
        auto list_at = [&](const RegisterValue& v) -> LmList* {
            return reinterpret_cast<LmList*>(Access::list(v));
        };
        switch (op) {
            case ResourceOperation::OPEN: {
                int w = 800, h = 600;
                auto f = flatten(args);
                if (f.size() >= 2) { w = (int)f[0]; h = (int)f[1]; }
                if (w > 0 && h > 0) { width_ = w; height_ = h; }
                return value_true;
            }
            case ResourceOperation::SPAWN: {
                // Window creation is GPU-backend agnostic: start the sapp
                // thread (which brings up sokol_gfx in its init callback).
                int w = width_, h = height_;
                std::string title = "Lymar Application";
                bool resizable = true;
                if (!args.empty()) {
                    if (auto* list = list_at(args[0])) {
                        if (lm_list_len(list) > 0) w = (int)register_value_to_i64(lm_list_get(list, 0));
                        if (lm_list_len(list) > 1) h = (int)register_value_to_i64(lm_list_get(list, 1));
                        if (lm_list_len(list) > 2) {
                            const char* s = register_value_to_cstr(lm_list_get(list, 2));
                            if (s) title = s;
                        }
                        if (lm_list_len(list) > 3) resizable = register_value_to_i64(lm_list_get(list, 3)) != 0;
                    } else {
                        w = (int)register_value_to_i64(args[0]);
                        if (args.size() > 1) h = (int)register_value_to_i64(args[1]);
                        if (args.size() > 2) {
                            const char* s = register_value_to_cstr(args[2]);
                            if (s) title = s;
                        }
                        if (args.size() > 3) resizable = register_value_to_i64(args[3]) != 0;
                    }
                }
                if (w > 0 && h > 0) { width_ = w; height_ = h; }
                const char* headless = std::getenv("LYMAR_HEADLESS");
                if (!(headless && std::string(headless) != "0")) {
                    sokol_app_runtime().start(SokolAppConfig{width_, height_, title, resizable, true});
                }
                return value_true;
            }
            case ResourceOperation::FILL: {
                auto f = flatten(args);
                double r = 0.0, g = 0.0, b = 0.0, a = 1.0;
                if (f.size() >= 6) { r = f[2]; g = f[3]; b = f[4]; a = f[5]; }
                else if (f.size() >= 4) { r = f[0]; g = f[1]; b = f[2]; a = f[3]; }
                clip_stack_.clear();
                pass_active_ = true;
                GfxCommand c;
                c.type = GfxCommand::Type::Clear;
                c.f = {r, g, b, a};
                ::sokol_gfx_runtime().submit(c);
                return value_true;
            }
            case ResourceOperation::END_PASS: {
                if (!pass_active_) return value_false;
                pass_active_ = false;
                GfxCommand c; c.type = GfxCommand::Type::EndPass;
                ::sokol_gfx_runtime().submit(c);
                return value_true;
            }
            case ResourceOperation::PUSH: {
                auto f = flatten(args);
                GfxCommand c; c.type = GfxCommand::Type::PushClip; c.f = f;
                ::sokol_gfx_runtime().submit(c);
                return value_true;
            }
            case ResourceOperation::POP: {
                GfxCommand c; c.type = GfxCommand::Type::PopClip;
                ::sokol_gfx_runtime().submit(c);
                return value_true;
            }
            case ResourceOperation::APPLY_PIPELINE: {
                if (!pass_active_) return value_false;
                auto f = flatten(args);
                if (f.empty()) return value_false;
                GfxCommand c; c.type = GfxCommand::Type::ApplyPipeline;
                c.i = {(int64_t)f[0]};
                ::sokol_gfx_runtime().submit(c);
                return value_true;
            }
            case ResourceOperation::APPLY_BINDINGS: {
                if (!pass_active_ || args.empty()) return value_false;
                GfxCommand c; c.type = GfxCommand::Type::ApplyBindings;
                auto copy_uniforms = [&](LmList* u) {
                    if (!u) return;
                    size_t n = lm_list_len(u);
                    c.lists.resize(1);
                    c.lists[0].reserve(n);
                    for (size_t i = 0; i < n; ++i)
                        c.lists[0].push_back(register_value_to_double(lm_list_get(u, i)));
                };
                // two call shapes: [vbuf, ibuf, uniforms?, img?, smp?] as
                // scalars, or a single list arg holding the same fields
                // (see gg.apply_bindings). Slots 3/4 bind a texture.
                if (auto* list = list_at(args[0])) {
                    if (lm_list_len(list) < 2) return value_false;
                    c.i = {(int64_t)register_value_to_i64(lm_list_get(list, 0)),
                           (int64_t)register_value_to_i64(lm_list_get(list, 1))};
                    if (lm_list_len(list) > 2) copy_uniforms(list_at(lm_list_get(list, 2)));
                    if (lm_list_len(list) > 3)
                        c.i.push_back((int64_t)register_value_to_i64(lm_list_get(list, 3)));
                    if (lm_list_len(list) > 4)
                        c.i.push_back((int64_t)register_value_to_i64(lm_list_get(list, 4)));
                } else {
                    c.i = {(int64_t)register_value_to_i64(args[0]),
                           args.size() > 1 ? (int64_t)register_value_to_i64(args[1]) : 0};
                    if (args.size() > 2) copy_uniforms(list_at(args[2]));
                    if (args.size() > 3)
                        c.i.push_back((int64_t)register_value_to_i64(args[3]));
                    if (args.size() > 4)
                        c.i.push_back((int64_t)register_value_to_i64(args[4]));
                }
                ::sokol_gfx_runtime().submit(c);
                return value_true;
            }
            case ResourceOperation::DRAW: {
                if (!pass_active_) return value_false;
                GfxCommand c; c.type = GfxCommand::Type::Draw;
                auto f = flatten(args);
                for (double d : f) c.i.push_back((int64_t)d);
                ::sokol_gfx_runtime().submit(c);
                return value_true;
            }
            case ResourceOperation::MAKE_BUFFER: {
                if (args.size() < 2) return value_nil;
                GfxCommand c; c.type = GfxCommand::Type::MakeBuffer;
                c.i = {(int64_t)register_value_to_i64(args[0]), 0};
                if (auto* list = list_at(args[1])) {
                    size_t n = lm_list_len(list);
                    c.lists.resize(1);
                    c.lists[0].reserve(n);
                    for (size_t i = 0; i < n; ++i)
                        c.lists[0].push_back(register_value_to_double(lm_list_get(list, i)));
                }
                ::sokol_gfx_runtime().submit(c);
                return value_true;
            }
            case ResourceOperation::MAKE_PIPELINE: {
                if (args.size() < 3) return value_nil;
                GfxCommand c; c.type = GfxCommand::Type::MakePipeline;
                c.i = {(int64_t)register_value_to_i64(args[0]),
                       (int64_t)register_value_to_i64(args[1]),
                       (int64_t)register_value_to_i64(args[2])};
                ::sokol_gfx_runtime().submit(c);
                return value_true;
            }
            case ResourceOperation::MAKE_BINDINGS:
                return value_true; // resolved by id at bind time
            case ResourceOperation::MAKE_IMAGE: {
                // args: [id, w, h, pixels?] — keep a CPU copy for the
                // software rasterizer AND forward RGBA8 to the render thread.
                if (getenv("LYMAR_DBG_TEX")) {
                    size_t psz = 0;
                    if (args.size() > 3) {
                        if (auto* pl = list_at(args[3])) psz = lm_list_len(pl);
                    }
                    fprintf(stderr, "[texdbg-vm] MAKE_IMAGE id=%lld w=%d h=%d psz=%zu need=%d\n",
                        (long long)register_value_to_i64(args[0]),
                        (int)register_value_to_i64(args[1]),
                        (int)register_value_to_i64(args[2]), psz,
                        args.size() > 2 ? (int)(register_value_to_i64(args[1]) * register_value_to_i64(args[2]) * 4) : -1);
                }
                if (args.size() < 3) return value_nil;
                GpuImage img;
                img.id = static_cast<int>(register_value_to_i64(args[0]));
                img.w = static_cast<int>(register_value_to_i64(args[1]));
                img.h = static_cast<int>(register_value_to_i64(args[2]));
                if (args.size() > 3) {
                    if (auto* list = list_at(args[3])) {
                        size_t n = lm_list_len(list);
                        img.pixels.reserve(n);
                        for (size_t i = 0; i < n; ++i)
                            img.pixels.push_back(static_cast<uint8_t>(register_value_to_i64(lm_list_get(list, i))));
                    }
                }
                if (img.w > 0 && img.h > 0 && img.pixels.size() >= static_cast<size_t>(img.w) * img.h * 4) {
                    images_[img.id] = img;
                    GfxCommand c; c.type = GfxCommand::Type::MakeImage;
                    c.i = {(int64_t)img.id};
                    c.w = img.w; c.h = img.h;
                    c.pixels = std::move(img.pixels);
                    ::sokol_gfx_runtime().submit(c);
                }
                return value_true;
            }
            case ResourceOperation::DRAW_RECT: {
                if (!pass_active_) return value_false;
                auto f = flatten(args);
                if (f.size() < 10) return value_true;
                GfxCommand c; c.type = GfxCommand::Type::DrawRect; c.f = f;
                ::sokol_gfx_runtime().submit(c);
                return value_true;
            }
            case ResourceOperation::DRAW_TRIANGLE: {
                if (!pass_active_) return value_false;
                auto f = flatten(args);
                if (f.size() < 10) return value_true;
                GfxCommand c; c.type = GfxCommand::Type::DrawTri; c.f = f;
                ::sokol_gfx_runtime().submit(c);
                return value_true;
            }
            case ResourceOperation::DRAW_TEXT: {
                if (!pass_active_) return value_false;
                std::string text;
                double x = 0, y = 0, r = 1, g = 1, b = 1, a = 1;
                int scale = 2;
                if (!args.empty()) {
                    if (auto* list = list_at(args[0])) {
                        if (lm_list_len(list) > 0) {
                            const char* s = register_value_to_cstr(lm_list_get(list, 0));
                            if (s) text = s;
                        }
                        if (lm_list_len(list) > 1) x = register_value_to_double(lm_list_get(list, 1));
                        if (lm_list_len(list) > 2) y = register_value_to_double(lm_list_get(list, 2));
                        if (lm_list_len(list) > 3) r = register_value_to_double(lm_list_get(list, 3));
                        if (lm_list_len(list) > 4) g = register_value_to_double(lm_list_get(list, 4));
                        if (lm_list_len(list) > 5) b = register_value_to_double(lm_list_get(list, 5));
                        if (lm_list_len(list) > 6) a = register_value_to_double(lm_list_get(list, 6));
                        if (lm_list_len(list) > 7) scale = (int)register_value_to_i64(lm_list_get(list, 7));
                    } else {
                        const char* s = register_value_to_cstr(args[0]);
                        if (s) text = s;
                        if (args.size() > 1) x = register_value_to_double(args[1]);
                        if (args.size() > 2) y = register_value_to_double(args[2]);
                        if (args.size() > 3) r = register_value_to_double(args[3]);
                        if (args.size() > 4) g = register_value_to_double(args[4]);
                        if (args.size() > 5) b = register_value_to_double(args[5]);
                        if (args.size() > 6) a = register_value_to_double(args[6]);
                        if (args.size() > 7) scale = (int)register_value_to_i64(args[7]);
                    }
                }
                if (text.empty()) return value_true;
                GfxCommand c; c.type = GfxCommand::Type::DrawTextCmd;
                c.s = text;
                c.f = {x, y, r, g, b, a, (double)scale};
                ::sokol_gfx_runtime().submit(c);
                return value_true;
            }
            case ResourceOperation::MEASURE_TEXT:
            case ResourceOperation::GET_FONT_METRICS:
            case ResourceOperation::READ:
                return value_nil; // gg falls back to built-in estimates
            case ResourceOperation::POLL: {
                // Frame boundary: publish this frame's command batch so the
                // render thread only ever presents complete frames.
                ::sokol_gfx_runtime().commit_frame();
                sokol_app_runtime().wait_for_frame();
                std::vector<RuntimeAppEvent> app_events;
                sokol_app_runtime().poll_events(app_events);
                for (const auto& ev : app_events) {
                    if (ev.type == 1) { width_ = ev.x; height_ = ev.y; }
                    push_native_event(ev.type, ev.x, ev.y, ev.key);
                }
                LmList* list = lm_list_new();
                std::lock_guard<std::mutex> lock(event_mutex_);
                for (const auto& ev : native_events_) {
                    lm_list_append(list, integer_value(ev.type));
                    lm_list_append(list, integer_value(ev.x));
                    lm_list_append(list, integer_value(ev.y));
                    lm_list_append(list, integer_value(ev.key));
                }
                native_events_.clear();
                return pointer_value(list);
            }
            case ResourceOperation::FLUSH:
                return value_true; // passes commit via sg_commit on EndPass
            case ResourceOperation::CLOSE: {
                sokol_app_runtime().stop();
                return value_true;
            }
            case ResourceOperation::SET_STATE: {
                auto f = flatten(args);
                if (f.size() >= 2) {
                    int w = (int)f[0], h = (int)f[1];
                    if (w > 0 && h > 0) {
                        width_ = w; height_ = h;
                        sokol_app_runtime().set_window_size(w, h);
                    }
                }
                return value_true;
            }
            default:
                return value_nil;
        }
    }

    // Uniform blob layout: canonical indices live in gfx_uniform_layout.hh
    // (shared with the Sokol backend and mirrored by std/d3/uniforms.lm).
    static constexpr int kMaxStreamLights = ::gfx_uniform::kMaxLights;

    void draw_vertex_stream(const GpuBuffer& vb, int ibuf_id, const std::vector<double>& u) {
        if (width_ <= 0 || height_ <= 0 || pixels_.empty() ||
            depth_.size() != static_cast<std::size_t>(width_) * height_) {
            return;
        }
        const auto& vdata = vb.data;
        if (vdata.size() < 8) return;
        // Vertex record: pos3 + normal3 + uv2 = 8 floats (matches
        // _ensure_gpu_buffers in std/d3/renderer.lm and the Sokol layout).
        const int vcount = static_cast<int>(vdata.size() / 8);

        std::vector<int> indices;
        auto ib_it = buffers_.find(ibuf_id);
        if (ib_it != buffers_.end() && !ib_it->second.data.empty()) {
            indices.reserve(ib_it->second.data.size());
            for (double d : ib_it->second.data) {
                indices.push_back(static_cast<int>(std::llround(d)));
            }
        } else {
            indices.reserve(vcount);
            for (int i = 0; i < vcount; ++i) indices.push_back(i);
        }
        const int tri_count = static_cast<int>(indices.size() / 3);
        if (tri_count <= 0) return;

        namespace gu = ::gfx_uniform;
        auto U = [&](int i) -> double {
            return (i >= 0 && i < static_cast<int>(u.size())) ? u[i] : 0.0;
        };
        double m[16], wld[16];
        for (int i = 0; i < 16; ++i) {
            m[i] = U(gu::kMvpOffset + i);
            wld[i] = U(gu::kWorldOffset + i);
        }
        const double cr = U(gu::kColorOffset), cg = U(gu::kColorOffset + 1),
                     cb = U(gu::kColorOffset + 2), ca = U(gu::kColorOffset + 3);
        double ill_base_r = U(gu::kAmbientOffset), ill_base_g = U(gu::kAmbientOffset + 1),
                     ill_base_b = U(gu::kAmbientOffset + 2);
        const double mat_diff = U(gu::kMaterialOffset), mat_spec = U(gu::kMaterialOffset + 1),
                     mat_shin = U(gu::kMaterialOffset + 2);
        const int shading = static_cast<int>(U(gu::kShadingOffset));
        const int cull_mode = static_cast<int>(U(gu::kCullOffset));
        const double wire_w = U(gu::kWireWidthOffset) > 0.0 ? U(gu::kWireWidthOffset) : 1.0;
        const bool has_normals = U(gu::kHasNormalsOffset) != 0.0;
        const double vp_x = U(gu::kViewportOffset), vp_y = U(gu::kViewportOffset + 1),
                     vp_w = U(gu::kViewportOffset + 2), vp_h = U(gu::kViewportOffset + 3);
        const double half_vw = vp_w * 0.5, half_vh = vp_h * 0.5;
        int nlights = static_cast<int>(U(gu::kLightCountOffset));
        if (nlights > gu::kMaxLights) nlights = gu::kMaxLights;
        if (nlights < 0) nlights = 0;

        // Vertex stage: local -> clip -> screen, plus world pos & normal.
        std::vector<float> sx(vcount), sy(vcount), sdepth(vcount), sw(vcount);
        std::vector<float> wpx(vcount * 3), wnx(vcount * 3);
        std::vector<float> suv_u(vcount), suv_v(vcount);
        for (int i = 0; i < vcount; ++i) {
            const double lx = vdata[i * 8], ly = vdata[i * 8 + 1], lz = vdata[i * 8 + 2];
            const double cx = m[0] * lx + m[1] * ly + m[2] * lz + m[3];
            const double cy = m[4] * lx + m[5] * ly + m[6] * lz + m[7];
            const double cz = m[8] * lx + m[9] * ly + m[10] * lz + m[11];
            const double cw = m[12] * lx + m[13] * ly + m[14] * lz + m[15];
            sw[i] = static_cast<float>(cw);
            if (std::abs(cw) > 1e-9) {
                const double inv = 1.0 / cw;
                const double ndx = cx * inv, ndy = cy * inv, ndz = cz * inv;
                sx[i] = static_cast<float>(vp_x + (ndx + 1.0) * half_vw);
                sy[i] = static_cast<float>(vp_y + (1.0 - ndy) * half_vh);
                sdepth[i] = static_cast<float>((ndz + 1.0) * 0.5);
            } else {
                sx[i] = sy[i] = sdepth[i] = 0.0f;
            }
            // world-space position (for point lights)
            wpx[i * 3]     = static_cast<float>(wld[0] * lx + wld[1] * ly + wld[2] * lz + wld[3]);
            wpx[i * 3 + 1] = static_cast<float>(wld[4] * lx + wld[5] * ly + wld[6] * lz + wld[7]);
            wpx[i * 3 + 2] = static_cast<float>(wld[8] * lx + wld[9] * ly + wld[10] * lz + wld[11]);
            // world-space normal (upper 3x3 only)
            double nx = 0.0, ny = 1.0, nz = 0.0;
            if (has_normals) {
                nx = vdata[i * 8 + 3]; ny = vdata[i * 8 + 4]; nz = vdata[i * 8 + 5];
            }
            suv_u[i] = static_cast<float>(vdata[i * 8 + 6]);
            suv_v[i] = static_cast<float>(vdata[i * 8 + 7]);
            double tx = wld[0] * nx + wld[1] * ny + wld[2] * nz;
            double ty = wld[4] * nx + wld[5] * ny + wld[6] * nz;
            double tz = wld[8] * nx + wld[9] * ny + wld[10] * nz;
            const double nl = std::sqrt(tx * tx + ty * ty + tz * tz);
            if (nl > 1e-9) { const double inv = 1.0 / nl; tx *= inv; ty *= inv; tz *= inv; }
            wnx[i * 3] = static_cast<float>(tx);
            wnx[i * 3 + 1] = static_cast<float>(ty);
            wnx[i * 3 + 2] = static_cast<float>(tz);
        }

        ClipRect clip = get_current_clip();
        const int cx0 = std::max(0, clip.x0), cy0 = std::max(0, clip.y0);
        const int cx1 = std::min(width_, clip.x1), cy1 = std::min(height_, clip.y1);
        if (cx1 <= cx0 || cy1 <= cy0) return;

        auto blend_px = [&](int px, int py, double r, double g, double b, double a) {
            size_t idx = static_cast<size_t>(py * width_ + px) * 4;
            if (idx + 3 >= pixels_.size()) return;
            const uint8_t ru = static_cast<uint8_t>(std::clamp(r * 255.0, 0.0, 255.0));
            const uint8_t gu = static_cast<uint8_t>(std::clamp(g * 255.0, 0.0, 255.0));
            const uint8_t bu = static_cast<uint8_t>(std::clamp(b * 255.0, 0.0, 255.0));
            const uint8_t au = static_cast<uint8_t>(std::clamp(a * 255.0, 0.0, 255.0));
            if (au >= 255) {
                pixels_[idx] = ru; pixels_[idx + 1] = gu;
                pixels_[idx + 2] = bu; pixels_[idx + 3] = 255;
            } else if (au > 0) {
                const float af = au / 255.0f, inv = 1.0f - af;
                pixels_[idx]     = static_cast<uint8_t>(ru * af + pixels_[idx] * inv);
                pixels_[idx + 1] = static_cast<uint8_t>(gu * af + pixels_[idx + 1] * inv);
                pixels_[idx + 2] = static_cast<uint8_t>(bu * af + pixels_[idx + 2] * inv);
                pixels_[idx + 3] = std::max(pixels_[idx + 3], au);
            }
        };

        // Bound texture (parity with the GPU vertex-stream FS): bilinear,
        // v flipped so uv v=0 samples the bottom row of the image.
        const bool has_tex = U(gu::kTexFlagOffset) != 0.0;
        const GpuImage* tex = nullptr;
        if (has_tex) {
            auto ti = images_.find(current_img_);
            if (ti != images_.end() && ti->second.w > 0 && ti->second.h > 0) tex = &ti->second;
        }
        auto sample_tex = [&](double u, double v, double& r, double& g, double& b, double& a) {
            r = 1.0; g = 1.0; b = 1.0; a = 1.0;
            if (!tex) return;
            const double tw = tex->w, th = tex->h;
            u = std::clamp(u, 0.0, 1.0);
            v = std::clamp(v, 0.0, 1.0);
            const double fx = u * (tw - 1.0), fy = (1.0 - v) * (th - 1.0);
            const int x0 = std::clamp((int)std::floor(fx), 0, tex->w - 1);
            const int y0 = std::clamp((int)std::floor(fy), 0, tex->h - 1);
            const int x1 = std::min(x0 + 1, tex->w - 1);
            const int y1 = std::min(y0 + 1, tex->h - 1);
            const double tx = fx - std::floor(fx), ty = fy - std::floor(fy);
            const auto tap = [&](int x, int y, int c) -> double {
                return tex->pixels[(size_t)(y * tex->w + x) * 4 + c] / 255.0;
            };
            const double w00 = (1.0 - tx) * (1.0 - ty), w10 = tx * (1.0 - ty);
            const double w01 = (1.0 - tx) * ty,       w11 = tx * ty;
            r = tap(x0,y0,0)*w00 + tap(x1,y0,0)*w10 + tap(x0,y1,0)*w01 + tap(x1,y1,0)*w11;
            g = tap(x0,y0,1)*w00 + tap(x1,y0,1)*w10 + tap(x0,y1,1)*w01 + tap(x1,y1,1)*w11;
            b = tap(x0,y0,2)*w00 + tap(x1,y0,2)*w10 + tap(x0,y1,2)*w01 + tap(x1,y1,2)*w11;
            a = tap(x0,y0,3)*w00 + tap(x1,y0,3)*w10 + tap(x0,y1,3)*w01 + tap(x1,y1,3)*w11;
        };

        for (int t = 0; t < tri_count; ++t) {
            const int i0 = indices[t * 3], i1 = indices[t * 3 + 1], i2 = indices[t * 3 + 2];
            if (i0 < 0 || i1 < 0 || i2 < 0 || i0 >= vcount || i1 >= vcount || i2 >= vcount) continue;
            // Near-plane clip: same contract as the CPU rasterizer (all w > 0.1).
            if (!(sw[i0] > 0.1f && sw[i1] > 0.1f && sw[i2] > 0.1f)) continue;

            const double x0 = sx[i0], y0 = sy[i0];
            const double x1 = sx[i1], y1 = sy[i1];
            const double x2 = sx[i2], y2 = sy[i2];

            const int min_x = std::clamp(static_cast<int>(std::floor(std::min({x0, x1, x2}))), cx0, cx1);
            const int max_x = std::clamp(static_cast<int>(std::ceil(std::max({x0, x1, x2}))), cx0, cx1);
            const int min_y = std::clamp(static_cast<int>(std::floor(std::min({y0, y1, y2}))), cy0, cy1);
            const int max_y = std::clamp(static_cast<int>(std::ceil(std::max({y0, y1, y2}))), cy0, cy1);
            if (max_x <= min_x || max_y <= min_y) continue;

            // Backface culling in screen space (y-down), matching CPU path.
            const double e1x = x1 - x0, e1y = y1 - y0;
            const double e2x = x2 - x0, e2y = y2 - y0;
            const double cross_z = e1x * e2y - e1y * e2x;
            bool culled = false;
            if (cull_mode == 1) culled = (cross_z >= 0.0);
            else if (cull_mode == 2) culled = (cross_z <= 0.0);
            if (culled) continue;

            // Face normal: smooth averages the three vertex normals.
            double fnx = wnx[i0 * 3], fny = wnx[i0 * 3 + 1], fnz = wnx[i0 * 3 + 2];
            if (shading == 1) {
                fnx = (wnx[i0 * 3] + wnx[i1 * 3] + wnx[i2 * 3]) / 3.0;
                fny = (wnx[i0 * 3 + 1] + wnx[i1 * 3 + 1] + wnx[i2 * 3 + 1]) / 3.0;
                fnz = (wnx[i0 * 3 + 2] + wnx[i1 * 3 + 2] + wnx[i2 * 3 + 2]) / 3.0;
                const double nl = std::sqrt(fnx * fnx + fny * fny + fnz * fnz);
                if (nl > 1e-9) { const double inv = 1.0 / nl; fnx *= inv; fny *= inv; fnz *= inv; }
            }

            // Two-sided lighting: fragments rasterized as back-facing
            // (cross_z > 0 in y-down screen space, i.e. drawn under
            // CullMode.None or CullMode.Front) flip the shading normal so
            // interior surfaces aren't lit by the outward normal.
            if (cross_z > 0.0) { fnx = -fnx; fny = -fny; fnz = -fnz; }

            // Fragment stage: lighting ported from std.d3 _accumulate_lights.
            double out_r = cr, out_g = cg, out_b = cb;
            const bool is_wire = (shading == 3);
            if (shading == 4) {
                out_r = fnx * 0.5 + 0.5;
                out_g = fny * 0.5 + 0.5;
                out_b = fnz * 0.5 + 0.5;
            } else if (shading != 2) {
                const double wcx = (wpx[i0 * 3] + wpx[i1 * 3] + wpx[i2 * 3]) / 3.0;
                const double wcy = (wpx[i0 * 3 + 1] + wpx[i1 * 3 + 1] + wpx[i2 * 3 + 1]) / 3.0;
                const double wcz = (wpx[i0 * 3 + 2] + wpx[i1 * 3 + 2] + wpx[i2 * 3 + 2]) / 3.0;
                double ir = ill_base_r, ig = ill_base_g, ib = ill_base_b;
                for (int li = 0; li < nlights; ++li) {
                    const int lb = gu::kLightBase + li * gu::kLightStride;
                    const int ltype = static_cast<int>(U(lb + gu::kLightTypeOffset));
                    const double lx = U(lb + gu::kLightDirOffset), ly = U(lb + gu::kLightDirOffset + 1),
                                 lz = U(lb + gu::kLightDirOffset + 2);
                    const double lr = U(lb + gu::kLightColorOffset), lg = U(lb + gu::kLightColorOffset + 1),
                                 lbcol = U(lb + gu::kLightColorOffset + 2);
                    const double lint = U(lb + gu::kLightIntOffset);
                    if (ltype == 1) {
                        const double dotv = fnx * lx + fny * ly + fnz * lz;
                        if (dotv > 0.0) {
                            const double df = dotv * mat_diff * lint;
                            ir += lr * df; ig += lg * df; ib += lbcol * df;
                            if (mat_spec > 0.0) {
                                const double hx = lx, hy = ly, hz = lz + 1.0;
                                const double hlen = std::sqrt(hx * hx + hy * hy + hz * hz);
                                if (hlen > 1e-6) {
                                    const double ndoth = (fnx * hx + fny * hy + fnz * hz) / hlen;
                                    if (ndoth > 0.0) {
                                        double sp = ndoth * ndoth * ndoth * ndoth;
                                        if (mat_shin >= 16.0) sp *= sp;
                                        if (mat_shin >= 32.0) sp *= sp;
                                        const double s = sp * mat_spec * lint;
                                        ir += s; ig += s; ib += s;
                                    }
                                }
                            }
                        }
                    } else if (ltype == 2) {
                        const double dx = lx - wcx, dy = ly - wcy, dz = lz - wcz;
                        const double dsq = dx * dx + dy * dy + dz * dz;
                        if (dsq > 1e-6) {
                            const double dist = std::sqrt(dsq);
                            const double pdot = (fnx * dx + fny * dy + fnz * dz) / dist;
                            if (pdot > 0.0) {
                                const double atten = 1.0 / (1.0 + 0.09 * dist + 0.032 * dist * dist);
                                const double pf = pdot * mat_diff * lint * atten;
                                ir += lr * pf; ig += lg * pf; ib += lbcol * pf;
                            }
                        }
                    }
                }
                if (ir > 1.0) ir = 1.0; if (ig > 1.0) ig = 1.0; if (ib > 1.0) ib = 1.0;
                out_r = cr * ir; out_g = cg * ig; out_b = cb * ib;
            }

            if (is_wire) {
                // Wireframe: distance-to-segment edge rasterization.
                const double half_wpx = wire_w * 0.5;
                const double vx[3] = {x0, x1, x2}, vy[3] = {y0, y1, y2};
                for (int py = min_y; py < max_y; ++py) {
                    for (int px = min_x; px < max_x; ++px) {
                        const double qx = px + 0.5, qy = py + 0.5;
                        bool on_edge = false;
                        for (int e = 0; e < 3 && !on_edge; ++e) {
                            const int a = e, b = (e + 1) % 3;
                            const double ax = vx[a], ay = vy[a], bx = vx[b], by = vy[b];
                            const double abx = bx - ax, aby = by - ay;
                            const double len2 = abx * abx + aby * aby;
                            double tt = 0.0;
                            if (len2 > 1e-9) {
                                tt = ((qx - ax) * abx + (qy - ay) * aby) / len2;
                                tt = std::clamp(tt, 0.0, 1.0);
                            }
                            const double ddx = qx - (ax + tt * abx);
                            const double ddy = qy - (ay + tt * aby);
                            if (ddx * ddx + ddy * ddy <= half_wpx * half_wpx) on_edge = true;
                        }
                        if (on_edge) blend_px(px, py, out_r, out_g, out_b, ca);
                    }
                }
                continue;
            }

            // Filled rasterization with per-pixel depth test.
            const double d0 = sdepth[i0], d1 = sdepth[i1], d2 = sdepth[i2];
            const double denom = (y1 - y2) * (x0 - x2) + (x2 - x1) * (y0 - y2);
            if (std::abs(denom) < 1e-12) continue;
            const double inv_denom = 1.0 / denom;
            for (int py = min_y; py < max_y; ++py) {
                const double qy = py + 0.5;
                for (int px = min_x; px < max_x; ++px) {
                    const double qx = px + 0.5;
                    const double l0 = ((y1 - y2) * (qx - x2) + (x2 - x1) * (qy - y2)) * inv_denom;
                    const double l1 = ((y2 - y0) * (qx - x2) + (x0 - x2) * (qy - y2)) * inv_denom;
                    const double l2 = 1.0 - l0 - l1;
                    const double eps = -1e-6;
                    if ((l0 >= eps && l1 >= eps && l2 >= eps) || (l0 <= -eps && l1 <= -eps && l2 <= -eps)) {
                        const double dep = l0 * d0 + l1 * d1 + l2 * d2;
                        const size_t didx = static_cast<size_t>(py * width_ + px);
                        if (dep >= 0.0 && dep < depth_[didx]) {
                            depth_[didx] = static_cast<float>(dep);
                            double fr = out_r, fg = out_g, fb = out_b, fa = ca;
                            if (tex) {
                                // Perspective-correct UV interpolation.
                                const double iw0 = sw[i0] > 1e-6 ? 1.0 / sw[i0] : 0.0;
                                const double iw1 = sw[i1] > 1e-6 ? 1.0 / sw[i1] : 0.0;
                                const double iw2 = sw[i2] > 1e-6 ? 1.0 / sw[i2] : 0.0;
                                const double wsum = l0 * iw0 + l1 * iw1 + l2 * iw2;
                                double tu = 0.0, tv = 0.0;
                                if (wsum > 1e-9) {
                                    tu = (l0 * suv_u[i0] * iw0 + l1 * suv_u[i1] * iw1 + l2 * suv_u[i2] * iw2) / wsum;
                                    tv = (l0 * suv_v[i0] * iw0 + l1 * suv_v[i1] * iw1 + l2 * suv_v[i2] * iw2) / wsum;
                                }
                                double tr, tg, tb, ta;
                                sample_tex(tu, tv, tr, tg, tb, ta);
                                fr *= tr; fg *= tg; fb *= tb; fa *= ta;
                            }
                            blend_px(px, py, fr, fg, fb, fa);
                        }
                    }
                }
            }
        }
    }

    int width_;
    int height_;
    bool pass_active_ = false;
    int current_pipeline_ = 0;
    int current_vbuf_ = 0;
    int current_ibuf_ = 0;
    std::vector<double> current_uniforms_;
    std::map<int, GpuBuffer> buffers_;
    std::map<int, GpuPipeline> pipelines_;
    std::map<int, GpuBindings> bindings_;
    std::map<int, GpuImage> images_;
    int current_img_ = 0;   // texture bound by the last APPLY_BINDINGS
    std::vector<uint8_t> pixels_;
    std::vector<float> depth_;
    std::mutex event_mutex_;
    std::vector<WindowEvent> native_events_;
};



}

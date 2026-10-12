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
#include "sokol/sokol_app_runtime.hh"
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
        clip_stack_.clear();
    }

    void push_native_event(int type, int x, int y, int key) {
        std::lock_guard<std::mutex> lock(event_mutex_);
        native_events_.push_back({type, x, y, key});
    }

    ResourceType getType() const override { return ResourceType::GRAPHICS; }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void*) override {
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

                for (size_t i = 0; i < pixels_.size(); i += 4) {
                    pixels_[i]     = ru;
                    pixels_[i + 1] = gu;
                    pixels_[i + 2] = bu;
                    pixels_[i + 3] = au;
                }
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
                if (!args.empty()) {
                    if (auto* list = reinterpret_cast<LmList*>(check_header_type(args[0], list_type))) {
                        if (lm_list_len(list) > 0) current_vbuf_ = static_cast<int>(register_value_to_i64(lm_list_get(list, 0)));
                        if (lm_list_len(list) > 1) current_ibuf_ = static_cast<int>(register_value_to_i64(lm_list_get(list, 1)));
                    } else {
                        current_vbuf_ = static_cast<int>(register_value_to_i64(args[0]));
                        if (args.size() > 1) current_ibuf_ = static_cast<int>(register_value_to_i64(args[1]));
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

                if (primitive_type == 1 && data.size() >= 10) { // Triangle Primitive (x1, y1, x2, y2, x3, y3, r, g, b, a)
                    double x1 = data[0], y1 = data[1], x2 = data[2], y2 = data[3], x3 = data[4], y3 = data[5];
                    double r = data[6], g = data[7], b = data[8], a = data[9];

                    ClipRect clip = get_current_clip();
                    int min_x = std::clamp(static_cast<int>(std::floor(std::min({x1, x2, x3}))), clip.x0, clip.x1);
                    int max_x = std::clamp(static_cast<int>(std::ceil(std::max({x1, x2, x3}))), clip.x0, clip.x1);
                    int min_y = std::clamp(static_cast<int>(std::floor(std::min({y1, y2, y3}))), clip.y0, clip.y1);
                    int max_y = std::clamp(static_cast<int>(std::ceil(std::max({y1, y2, y3}))), clip.y0, clip.y1);

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
                                pixels_[idx]     = ru;
                                pixels_[idx + 1] = gu;
                                pixels_[idx + 2] = bu;
                                pixels_[idx + 3] = au;
                            }
                        }
                    }
                } else if (data.size() >= 8) { // Rectangle Primitive (x, y, w, h, r, g, b, a)
                    double x = data[0], y = data[1], w = data[2], h = data[3];
                    double r = data[4], g = data[5], b = data[6], a = data[7];

                    ClipRect clip = get_current_clip();
                    int x0 = std::clamp(static_cast<int>(x), clip.x0, clip.x1);
                    int y0 = std::clamp(static_cast<int>(y), clip.y0, clip.y1);
                    int x1 = std::clamp(static_cast<int>(x + w), clip.x0, clip.x1);
                    int y1 = std::clamp(static_cast<int>(y + h), clip.y0, clip.y1);

                    uint8_t ru = static_cast<uint8_t>(std::clamp(r * 255.0, 0.0, 255.0));
                    uint8_t gu = static_cast<uint8_t>(std::clamp(g * 255.0, 0.0, 255.0));
                    uint8_t bu = static_cast<uint8_t>(std::clamp(b * 255.0, 0.0, 255.0));
                    uint8_t au = static_cast<uint8_t>(std::clamp(a * 255.0, 0.0, 255.0));

                    for (int py = y0; py < y1; ++py) {
                        for (int px = x0; px < x1; ++px) {
                            size_t idx = static_cast<size_t>(py * width_ + px) * 4;
                            pixels_[idx]     = ru;
                            pixels_[idx + 1] = gu;
                            pixels_[idx + 2] = bu;
                            pixels_[idx + 3] = au;
                        }
                    }
                }
                return value_true;
            }
            case ResourceOperation::DRAW_RECT: {
                double x = 0.0, y = 0.0, w = 0.0, h = 0.0;
                double r = 1.0, g = 1.0, b = 1.0, a = 1.0;
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
                    } else {
                        x = register_value_to_double(args[0]);
                        if (args.size() > 1) y = register_value_to_double(args[1]);
                        if (args.size() > 2) w = register_value_to_double(args[2]);
                        if (args.size() > 3) h = register_value_to_double(args[3]);
                        if (args.size() > 4) r = register_value_to_double(args[4]);
                        if (args.size() > 5) g = register_value_to_double(args[5]);
                        if (args.size() > 6) b = register_value_to_double(args[6]);
                        if (args.size() > 7) a = register_value_to_double(args[7]);
                    }
                }

                ClipRect clip = get_current_clip();
                int x0 = std::clamp(static_cast<int>(x), clip.x0, clip.x1);
                int y0 = std::clamp(static_cast<int>(y), clip.y0, clip.y1);
                int x1 = std::clamp(static_cast<int>(x + w), clip.x0, clip.x1);
                int y1 = std::clamp(static_cast<int>(y + h), clip.y0, clip.y1);

                uint8_t ru = static_cast<uint8_t>(std::clamp(r * 255.0, 0.0, 255.0));
                uint8_t gu = static_cast<uint8_t>(std::clamp(g * 255.0, 0.0, 255.0));
                uint8_t bu = static_cast<uint8_t>(std::clamp(b * 255.0, 0.0, 255.0));
                uint8_t au = static_cast<uint8_t>(std::clamp(a * 255.0, 0.0, 255.0));

                for (int py = y0; py < y1; ++py) {
                    for (int px = x0; px < x1; ++px) {
                        size_t idx = static_cast<size_t>(py * width_ + px) * 4;
                        pixels_[idx]     = ru;
                        pixels_[idx + 1] = gu;
                        pixels_[idx + 2] = bu;
                        pixels_[idx + 3] = au;
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
                    }
                }

                ClipRect clip = get_current_clip();
                int min_x = std::clamp(static_cast<int>(std::floor(std::min({x1, x2, x3}))), clip.x0, clip.x1);
                int max_x = std::clamp(static_cast<int>(std::ceil(std::max({x1, x2, x3}))), clip.x0, clip.x1);
                int min_y = std::clamp(static_cast<int>(std::floor(std::min({y1, y2, y3}))), clip.y0, clip.y1);
                int max_y = std::clamp(static_cast<int>(std::ceil(std::max({y1, y2, y3}))), clip.y0, clip.y1);

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
                            pixels_[idx]     = ru;
                            pixels_[idx + 1] = gu;
                            pixels_[idx + 2] = bu;
                            pixels_[idx + 3] = au;
                        }
                    }
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
    int width_;
    int height_;
    bool pass_active_ = false;
    int current_pipeline_ = 0;
    int current_vbuf_ = 0;
    int current_ibuf_ = 0;
    std::map<int, GpuBuffer> buffers_;
    std::map<int, GpuPipeline> pipelines_;
    std::map<int, GpuBindings> bindings_;
    std::vector<uint8_t> pixels_;
    std::mutex event_mutex_;
    std::vector<WindowEvent> native_events_;
};



}

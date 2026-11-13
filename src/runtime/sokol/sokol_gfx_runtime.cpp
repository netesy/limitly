// Sokol-GFX GPU backend runtime for the Lymar VM graphics resource.
//
// All sg_* calls happen on the sokol_app thread (inside sokol_init /
// sokol_frame / sokol_cleanup callbacks in sokol_app_runtime.cpp). Commands
// are decoded on the VM thread into GfxCommand records and drained here.

#include "sokol_gfx_runtime.hh"
#include "../gfx_uniform_layout.hh"

#if defined(_WIN32)
#define SOKOL_D3D11
#endif
#define SOKOL_NO_ENTRY
#define SOKOL_NOAPI
#define SOKOL_GFX_IMPL
#define SOKOL_GLUE_IMPL

#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"

// Stage 2: immediate-mode text via sokol_gl + fontstash (atlas -> R8 texture).
#define SOKOL_GL_IMPL
#include "util/sokol_gl.h"
#define FONTSTASH_IMPLEMENTATION
#include "util/fontstash.h"
#define SOKOL_FONTSTASH_IMPL
#include "util/sokol_fontstash.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>

namespace {

// ---------------------------------------------------------------------------
// HLSL shaders (D3D11 backend)
// ---------------------------------------------------------------------------

// Shared NDC transform helper: pixel coords (y-down) -> clip space.
// viewport = (width, height) in pixels.

// --- rect: rounded-rect SDF, vertex-less via SV_VertexID ---------------------
static const char* kRectVS = R"(
cbuffer RectVS : register(b0) {
    float2 u_pos;
    float2 u_size;
    float4 u_color;
    float2 u_rad_bw;
    float2 u_viewport;
};
struct VSOut {
    float4 pos : SV_POSITION;
    float2 lpos : TEXCOORD0;
};
VSOut vs_main(uint vid : SV_VertexID) {
    // 6-vertex quad, unit square corners
    float2 uv = float2((vid == 1 || vid == 2 || vid == 4) ? 1.0 : 0.0,
                       (vid == 2 || vid == 4 || vid == 5) ? 1.0 : 0.0);
    float2 px = u_pos + uv * u_size;
    float2 ndc = float2(px.x / u_viewport.x * 2.0 - 1.0,
                        1.0 - px.y / u_viewport.y * 2.0);
    VSOut o;
    o.pos = float4(ndc, 0.0, 1.0);
    o.lpos = px - u_pos;
    return o;
}
)";

static const char* kRectFS = R"(
cbuffer RectFS : register(b1) {
    float2 u_pos;
    float2 u_size;
    float4 u_color;
    float2 u_rad_bw;
    float2 u_viewport;
};
struct VSOut {
    float4 pos : SV_POSITION;
    float2 lpos : TEXCOORD0;
};
float round_rect_sdf(float2 p, float2 b, float r) {
    float2 q = abs(p) - b + r;
    return length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - r;
}
float4 fs_main(VSOut i) : SV_TARGET {
    float radius = u_rad_bw.x;
    float border_w = u_rad_bw.y;
    float2 half_size = u_size * 0.5;
    float2 c = i.lpos - half_size;
    float d = round_rect_sdf(c, half_size, radius);
    float cov;
    if (border_w <= 0.0) {
        cov = saturate(0.5 - d);
    } else {
        cov = saturate(0.5 - abs(d + border_w * 0.5) + border_w * 0.5);
        // stroke coverage: inside band |d| <= border_w/2 around edge
        cov = saturate((border_w * 0.5 + 0.5 - abs(d)) * 1.0);
        cov = (d < -border_w * 0.5) ? 1.0 : cov;
    }
    return float4(u_color.rgb, u_color.a * cov);
}
)";

// --- tri: flat-colored triangle, vertex-less via SV_VertexID -----------------
static const char* kTriVS = R"(
cbuffer TriVS : register(b0) {
    float2 u_p0;
    float2 u_p1;
    float2 u_p2;
    float2 u_viewport;
};
struct VSOut {
    float4 pos : SV_POSITION;
};
VSOut vs_main(uint vid : SV_VertexID) {
    float2 px = (vid == 0) ? u_p0 : ((vid == 1) ? u_p1 : u_p2);
    float2 ndc = float2(px.x / u_viewport.x * 2.0 - 1.0,
                        1.0 - px.y / u_viewport.y * 2.0);
    VSOut o;
    o.pos = float4(ndc, 0.0, 1.0);
    return o;
}
)";

static const char* kTriFS = R"(
cbuffer TriFS : register(b1) {
    float4 u_color;
};
struct VSOut {
    float4 pos : SV_POSITION;
};
float4 fs_main(VSOut i) : SV_TARGET {
    return u_color;
}
)";

// --- vstream: pos+normal vertex stream with full uniform lighting -----------
// Uniform blob layout: indices come from gfx_uniform_layout.hh (the single
// source of truth shared with software_graphics.hh and mirrored by
// std/d3/uniforms.lm). u_data[i] is float4; blob element j is
// u_data[j>>2][j&3]. The prelude below injects the same indices as HLSL
// #defines so the shader body never repeats magic numbers.
static std::string vstream_hlsl_prelude() {
    char buf[2048];
    std::snprintf(buf, sizeof(buf),
        "// auto-generated from gfx_uniform_layout.hh — do not edit indices\n"
        "#define U_MVP %d\n"
        "#define U_WORLD %d\n"
        "#define U_COLOR %d\n"
        "#define U_AMBIENT %d\n"
        "#define U_MATERIAL %d\n"
        "#define U_SHADING %d\n"
        "#define U_CULL %d\n"
        "#define U_WIRE_WIDTH %d\n"
        "#define U_HAS_NORMALS %d\n"
        "#define U_HAS_TEXTURE %d\n"
        "#define U_VIEWPORT %d\n"
        "#define U_LIGHT_COUNT %d\n"
        "#define U_LIGHT_BASE %d\n"
        "#define U_LIGHT_STRIDE %d\n"
        "#define U_LIGHT_TYPE %d\n"
        "#define U_LIGHT_DIR %d\n"
        "#define U_LIGHT_COLOR %d\n"
        "#define U_LIGHT_INT %d\n"
        "#define SH_FLAT %.1ff\n"
        "#define SH_SMOOTH %.1ff\n"
        "#define SH_UNLIT %.1ff\n"
        "#define SH_WIREFRAME %.1ff\n"
        "#define SH_NORMAL_VIZ %.1ff\n"
        "#define CU_NONE %.1ff\n"
        "#define CU_BACK %.1ff\n"
        "#define CU_FRONT %.1ff\n"
        "#define LT_AMBIENT %.1ff\n"
        "#define LT_DIRECTIONAL %.1ff\n"
        "#define LT_POINT %.1ff\n",
        gfx_uniform::kMvpOffset, gfx_uniform::kWorldOffset,
        gfx_uniform::kColorOffset, gfx_uniform::kAmbientOffset,
        gfx_uniform::kMaterialOffset, gfx_uniform::kShadingOffset,
        gfx_uniform::kCullOffset, gfx_uniform::kWireWidthOffset,
        gfx_uniform::kHasNormalsOffset, gfx_uniform::kTexFlagOffset,
        gfx_uniform::kViewportOffset,
        gfx_uniform::kLightCountOffset, gfx_uniform::kLightBase,
        gfx_uniform::kLightStride, gfx_uniform::kLightTypeOffset,
        gfx_uniform::kLightDirOffset, gfx_uniform::kLightColorOffset,
        gfx_uniform::kLightIntOffset,
        (double)gfx_uniform::kShadingFlat, (double)gfx_uniform::kShadingSmooth,
        (double)gfx_uniform::kShadingUnlit, (double)gfx_uniform::kShadingWireframe,
        (double)gfx_uniform::kShadingNormalVisualizer,
        (double)gfx_uniform::kCullNone, (double)gfx_uniform::kCullBack,
        (double)gfx_uniform::kCullFront,
        (double)gfx_uniform::kLightAmbient, (double)gfx_uniform::kLightDirectional,
        (double)gfx_uniform::kLightPoint);
    return std::string(buf);
}
static const char* kVStreamVS = R"(
cbuffer VSVS : register(b0) {
    float4 u_data[48];
};
struct VSIn {
    float3 pos : TEXCOORD0;
    float3 nrm : TEXCOORD1;
    float2 uv : TEXCOORD2;
};
struct VSOut {
    float4 pos : SV_POSITION;
    float3 wpos : TEXCOORD0;
    float3 nrm : TEXCOORD1;
    float2 uv : TEXCOORD2;
};
VSOut vs_main(VSIn i) {
    float4 p = float4(i.pos, 1.0);
    // MVP rows are blob floats 0..15 -> u_data[0..3]
    float cx = dot(u_data[0], p);
    float cy = dot(u_data[1], p);
    float cz = dot(u_data[2], p);
    float cw = dot(u_data[3], p);
    // world rows are blob floats 16..31 -> u_data[4..7]
    float3 wpos = float3(dot(u_data[4], p), dot(u_data[5], p), dot(u_data[6], p));
    float3 n = float3(dot(u_data[4], float4(i.nrm, 0.0)),
                      dot(u_data[5], float4(i.nrm, 0.0)),
                      dot(u_data[6], float4(i.nrm, 0.0)));
    float nl = length(n);
    if (nl > 1e-9) n /= nl;
    // Lymar clip z is [-1,1]; D3D11 expects [0,w] -> remap: z' = (z + w) / 2
    VSOut o;
    o.pos = float4(cx, cy, (cz + cw) * 0.5, cw);
    o.wpos = wpos;
    o.nrm = n;
    o.uv = i.uv;
    return o;
}
)";

static const char* kVStreamFS = R"(
cbuffer VSFS : register(b1) {
    float4 u_data[48];
};
Texture2D u_tex : register(t0);
SamplerState u_smp : register(s0);
struct VSOut {
    float4 pos : SV_POSITION;
    float3 wpos : TEXCOORD0;
    float3 nrm : TEXCOORD1;
    float2 uv : TEXCOORD2;
    bool front : SV_IsFrontFace;
};
float4 fs_main(VSOut i) : SV_TARGET {
    // blob element j -> u_data[j>>2][j&3]
    #define U(j) u_data[(j)>>2][(j)&3]
    float shading = U(U_SHADING);
    float cull = U(U_CULL);
    // wireframe draws LINES; SV_IsFrontFace is undefined there
    if (shading != SH_WIREFRAME) {
        if (cull == CU_BACK && !i.front) discard;
        if (cull == CU_FRONT && i.front) discard;
    }

    float3 n = normalize(i.nrm);
    // Two-sided lighting: back-facing fragments (drawn under CullMode.None or
    // Front) get their shading normal flipped toward the viewer so interiors
    // aren't lit by the outward normal. Undefined for line primitives.
    if (shading != SH_WIREFRAME && !i.front) n = -n;
    float3 col = float3(U(U_COLOR), U(U_COLOR + 1), U(U_COLOR + 2));
    float alpha = U(U_COLOR + 3);
    // Base-color texture modulates the material color (tint semantics),
    // matching the software rasterizer's per-pixel multiply.
    if (U(U_HAS_TEXTURE) != 0.0) {
        // v flipped: geometry UVs are GL-style (v=0 at bottom), PNG rows
        // are stored top-first.
        float4 tx = u_tex.Sample(u_smp, float2(i.uv.x, 1.0 - i.uv.y));
        col *= tx.rgb;
        alpha *= tx.a;
    }
    float3 outc = col;

    if (shading == SH_NORMAL_VIZ) {
        // normal visualizer
        outc = n * 0.5 + 0.5;
    } else if (shading != SH_UNLIT) {
        // lit: port of std.d3 _accumulate_lights
        float3 ill = float3(U(U_AMBIENT), U(U_AMBIENT + 1), U(U_AMBIENT + 2));
        float mat_diff = U(U_MATERIAL);
        float mat_spec = U(U_MATERIAL + 1);
        float mat_shin = U(U_MATERIAL + 2);
        int nlights = (int)U(U_LIGHT_COUNT);
        if (nlights > 16) nlights = 16;
        [loop] for (int li = 0; li < nlights; ++li) {
            int lb = U_LIGHT_BASE + li * U_LIGHT_STRIDE;
            int ltype = (int)U(lb + U_LIGHT_TYPE);
            float3 lp = float3(U(lb + U_LIGHT_DIR), U(lb + U_LIGHT_DIR + 1), U(lb + U_LIGHT_DIR + 2));
            float3 lc = float3(U(lb + U_LIGHT_COLOR), U(lb + U_LIGHT_COLOR + 1), U(lb + U_LIGHT_COLOR + 2));
            float lint = U(lb + U_LIGHT_INT);
            if (ltype == LT_DIRECTIONAL) {
                // directional
                float d = dot(n, lp);
                if (d > 0.0) {
                    float df = d * mat_diff * lint;
                    ill += lc * df;
                    if (mat_spec > 0.0) {
                        float3 h = normalize(float3(lp.x, lp.y, lp.z + 1.0));
                        float ndh = dot(n, h);
                        if (ndh > 0.0) {
                            float sp = ndh * ndh * ndh * ndh;
                            if (mat_shin >= 16.0) sp *= sp;
                            if (mat_shin >= 32.0) sp *= sp;
                            ill += sp * mat_spec * lint;
                        }
                    }
                }
            } else if (ltype == LT_POINT) {
                // point
                float3 L = lp - i.wpos;
                float dsq = dot(L, L);
                if (dsq > 1e-6) {
                    float dist = sqrt(dsq);
                    float pd = dot(n, L) / dist;
                    if (pd > 0.0) {
                        float atten = 1.0 / (1.0 + 0.09 * dist + 0.032 * dist * dist);
                        ill += lc * (pd * mat_diff * lint * atten);
                    }
                }
            }
        }
        ill = min(ill, 1.0);
        outc = col * ill;
    }
    #undef U
    return float4(outc, alpha);
}
)";

// --- blit: fullscreen triangle sampling an RGBA8 texture ---------------------
static const char* kBlitVS = R"(
struct VSOut {
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};
VSOut vs_main(uint vid : SV_VertexID) {
    // fullscreen triangle, y-down pixel space -> NDC with v flipped for texture
    float2 p = (vid == 0) ? float2(-1.0, -1.0) : ((vid == 1) ? float2(3.0, -1.0) : float2(-1.0, 3.0));
    VSOut o;
    o.pos = float4(p, 0.0, 1.0);
    o.uv = float2((p.x + 1.0) * 0.5, (1.0 - p.y) * 0.5);
    return o;
}
)";

static const char* kBlitFS = R"(
Texture2D u_tex : register(t0);
SamplerState u_smp : register(s0);
struct VSOut {
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};
float4 fs_main(VSOut i) : SV_TARGET {
    return u_tex.Sample(u_smp, i.uv);
}
)";

// ---------------------------------------------------------------------------
// Impl: sg objects, maps, pipeline cache (render thread only)
// ---------------------------------------------------------------------------
} // namespace

struct SokolGfxRuntime::Impl {
    sg_shader sh_rect = {SG_INVALID_ID};
    sg_shader sh_tri = {SG_INVALID_ID};
    sg_shader sh_vstream = {SG_INVALID_ID};
    sg_shader sh_blit = {SG_INVALID_ID};

    sg_pipeline pipe_rect = {SG_INVALID_ID};
    sg_pipeline pipe_tri = {SG_INVALID_ID};
    sg_pipeline pipe_vstream = {SG_INVALID_ID};
    sg_pipeline pipe_vlines = {SG_INVALID_ID};
    sg_pipeline pipe_blit = {SG_INVALID_ID};

    struct BufRec {
        sg_buffer buf = {SG_INVALID_ID};
        int count = 0;   // index buffers: element count; vertex buffers: vertex count
        sg_buffer edge_buf = {SG_INVALID_ID}; // wireframe: line-list indices (2 per edge)
        int edge_count = 0;
    };
    std::map<int, BufRec> buffers;
    std::map<int, std::vector<double>> pending_bufs; // raw Lymar data until bound
    std::map<int, int> pipeline_kinds;   // lymar pip id -> kind (0 rect-ish, 1 tri-ish, 2 vstream)

    // bound state
    int bound_pipe_kind = -1;
    sg_buffer bound_vbuf = {SG_INVALID_ID};
    sg_buffer bound_ibuf = {SG_INVALID_ID};

    // textures (d3 vertex-stream sampling)
    struct TexRec { sg_image img = {SG_INVALID_ID}; sg_view view = {SG_INVALID_ID}; };
    std::map<int, TexRec> textures;
    int cur_img_ = 0;                    // lymar image id from APPLY_BINDINGS
    sg_sampler tex_smp = {SG_INVALID_ID};
    sg_image white_img = {SG_INVALID_ID};   // 1x1 fallback so slot 0 is always bound
    sg_view white_view = {SG_INVALID_ID};

    // blit (software framebuffer presentation)
    sg_image blit_img = {SG_INVALID_ID};
    sg_view blit_view = {SG_INVALID_ID};
    sg_sampler blit_smp = {SG_INVALID_ID};
    int blit_w = 0, blit_h = 0;

    // fontstash text (render thread only)
    FONScontext* fons = nullptr;
    int fons_font = -1;
    std::vector<GfxCommand> deferred_text; // text waits for end-of-pass: single atlas upload

    std::vector<std::vector<int>> clip_stack;
    int pass_w = 0, pass_h = 0;
    uint64_t dbg_deferred_total = 0, dbg_flushed_total = 0;
    float clear_r = 0, clear_g = 0, clear_b = 0, clear_a = 1;
    std::vector<double> uniforms;          // last APPLY_BINDINGS uniform blob
};

// Lazily create the sg_buffer for a Lymar buffer id. Vertex buffers hold
// float32 vertex records; index buffers hold uint32 indices.
static sg_buffer ensure_buffer(SokolGfxRuntime::Impl* im, int id, bool is_index) {
    if (id <= 0) return {SG_INVALID_ID};
    auto it = im->buffers.find(id);
    if (it != im->buffers.end() && it->second.buf.id != SG_INVALID_ID)
        return it->second.buf;
    auto pit = im->pending_bufs.find(id);
    if (pit == im->pending_bufs.end() || pit->second.empty())
        return {SG_INVALID_ID};
    const auto& data = pit->second;
    sg_buffer_desc bd{};
    bd.usage.immutable = true;
    if (is_index) bd.usage.index_buffer = true;
    else bd.usage.vertex_buffer = true;
    bd.label = is_index ? "lymar_ibuf" : "lymar_vbuf";
    auto& rec = im->buffers[id];
    if (is_index) {
        std::vector<uint32_t> idx;
        idx.reserve(data.size());
        for (double d : data) idx.push_back((uint32_t)std::llround(d));
        bd.size = idx.size() * sizeof(uint32_t);
        bd.data.ptr = idx.data();
        bd.data.size = bd.size;
        rec.buf = sg_make_buffer(&bd);
        rec.count = (int)idx.size();
        // Wireframe: expand each triangle (a,b,c) into line segments
        // (a,b),(b,c),(c,a). Duplicated edges are harmless.
        if (idx.size() >= 3 && idx.size() % 3 == 0) {
            std::vector<uint32_t> edges;
            edges.reserve(idx.size() * 2);
            for (size_t t = 0; t + 2 < idx.size(); t += 3) {
                const uint32_t a = idx[t], b = idx[t + 1], c = idx[t + 2];
                edges.push_back(a); edges.push_back(b);
                edges.push_back(b); edges.push_back(c);
                edges.push_back(c); edges.push_back(a);
            }
            sg_buffer_desc ebd{};
            ebd.usage.immutable = true;
            ebd.usage.index_buffer = true;
            ebd.size = edges.size() * sizeof(uint32_t);
            ebd.data.ptr = edges.data();
            ebd.data.size = ebd.size;
            ebd.label = "lymar_ibuf_edges";
            rec.edge_buf = sg_make_buffer(&ebd);
            rec.edge_count = (int)edges.size();
        }
    } else {
        std::vector<float> fv;
        fv.reserve(data.size());
        for (double d : data) fv.push_back((float)d);
        bd.size = fv.size() * sizeof(float);
        bd.data.ptr = fv.data();
        bd.data.size = bd.size;
        rec.buf = sg_make_buffer(&bd);
        rec.count = (int)(fv.size() / 8); // pos+normal+uv stride
    }
    return rec.buf;
}

// ---------------------------------------------------------------------------
// Font loading + VM-thread text metrics
// ---------------------------------------------------------------------------

static std::vector<uint8_t> g_font_data;
static bool g_font_loaded = false;

static bool load_font_data() {
    if (g_font_loaded) return !g_font_data.empty();
    g_font_loaded = true;
    static const char* dirs[] = {
#if defined(_WIN32)
        "C:\\Windows\\Fonts\\", "C:\\WINNT\\Fonts\\",
#elif defined(__APPLE__)
        "/System/Library/Fonts/", "/Library/Fonts/",
#else
        "/usr/share/fonts/truetype/dejavu/", "/usr/share/fonts/",
#endif
        nullptr
    };
    static const char* fonts[] = {
#if defined(_WIN32)
        "segoeui.ttf", "arial.ttf", "tahoma.ttf", "calibri.ttf", "consola.ttf",
#elif defined(__APPLE__)
        "SFNS.ttf", "Helvetica.ttc", "Arial.ttf",
#else
        "DejaVuSans.ttf", "LiberationSans-Regular.ttf", "FreeSans.ttf",
#endif
        nullptr
    };
    for (int i = 0; fonts[i] && g_font_data.empty(); ++i) {
        for (int d = 0; dirs[d] && g_font_data.empty(); ++d) {
            std::string path = std::string(dirs[d]) + fonts[i];
            FILE* f = fopen(path.c_str(), "rb");
            if (!f) continue;
            fseek(f, 0, SEEK_END);
            long sz = ftell(f);
            fseek(f, 0, SEEK_SET);
            if (sz > 0) {
                g_font_data.resize((size_t)sz);
                if (fread(g_font_data.data(), 1, (size_t)sz, f) != (size_t)sz)
                    g_font_data.clear();
            }
            fclose(f);
        }
    }
    return !g_font_data.empty();
}

float gfx_font_size_for_scale(int scale) {
    // Mirrors the software rasterizer's scale->pixels mapping.
    if (scale == 2) return 20.0f;
    if (scale == 3) return 26.0f;
    if (scale > 3 && scale <= 7) return (float)(scale * 9);
    if (scale > 7) return (float)scale;
    return 13.0f;
}

// VM-thread metrics context: pure CPU fontstash (all render callbacks NULL),
// used for measure_text / line_height without touching GPU objects.
static FONScontext* g_metrics_ctx = nullptr;
static int g_metrics_font = -1;
static bool g_metrics_tried = false;

static bool ensure_metrics() {
    if (g_metrics_tried) return g_metrics_ctx != nullptr;
    g_metrics_tried = true;
    if (!load_font_data()) return false;
    FONSparams params{};
    params.width = 256;
    params.height = 256;
    params.flags = FONS_ZERO_TOPLEFT;
    g_metrics_ctx = fonsCreateInternal(&params);
    if (!g_metrics_ctx) return false;
    g_metrics_font = fonsAddFontMem(g_metrics_ctx, "lymar",
        g_font_data.data(), (int)g_font_data.size(), 0);
    if (g_metrics_font < 0) { fonsDeleteInternal(g_metrics_ctx); g_metrics_ctx = nullptr; return false; }
    fonsSetFont(g_metrics_ctx, g_metrics_font);
    fonsSetAlign(g_metrics_ctx, FONS_ALIGN_LEFT | FONS_ALIGN_TOP);
    return true;
}

bool gfx_text_metrics_ready() { return ensure_metrics(); }

float gfx_measure_text(const char* text, int scale) {
    if (!text || !ensure_metrics()) return 0.0f;
    fonsSetSize(g_metrics_ctx, gfx_font_size_for_scale(scale));
    return fonsTextBounds(g_metrics_ctx, 0.0f, 0.0f, text, text + strlen(text), nullptr);
}

float gfx_line_height(int scale) {
    if (!ensure_metrics()) return 0.0f;
    fonsSetSize(g_metrics_ctx, gfx_font_size_for_scale(scale));
    float asc = 0, desc = 0, lineh = 0;
    fonsVertMetrics(g_metrics_ctx, &asc, &desc, &lineh);
    return lineh;
}

static sg_shader make_rect_shader() {
    sg_shader_desc d{};
    d.vertex_func.source = kRectVS;
    d.vertex_func.entry = "vs_main";
    d.vertex_func.d3d11_target = "vs_5_0";
    d.fragment_func.source = kRectFS;
    d.fragment_func.entry = "fs_main";
    d.fragment_func.d3d11_target = "ps_5_0";
    // two uniform blocks: vs register(b0), fs register(b1), each 48 bytes
    d.uniform_blocks[0].stage = SG_SHADERSTAGE_VERTEX;
    d.uniform_blocks[0].size = 48;
    d.uniform_blocks[0].hlsl_register_b_n = 0;
    d.uniform_blocks[1].stage = SG_SHADERSTAGE_FRAGMENT;
    d.uniform_blocks[1].size = 48;
    d.uniform_blocks[1].hlsl_register_b_n = 1;
    d.label = "lymar_rect";
    return sg_make_shader(&d);
}

static sg_shader make_tri_shader() {
    sg_shader_desc d{};
    d.vertex_func.source = kTriVS;
    d.vertex_func.entry = "vs_main";
    d.vertex_func.d3d11_target = "vs_5_0";
    d.fragment_func.source = kTriFS;
    d.fragment_func.entry = "fs_main";
    d.fragment_func.d3d11_target = "ps_5_0";
    d.uniform_blocks[0].stage = SG_SHADERSTAGE_VERTEX;
    d.uniform_blocks[0].size = 32;   // 3*float2 + float2
    d.uniform_blocks[0].hlsl_register_b_n = 0;
    d.uniform_blocks[1].stage = SG_SHADERSTAGE_FRAGMENT;
    d.uniform_blocks[1].size = 16;
    d.uniform_blocks[1].hlsl_register_b_n = 1;
    d.label = "lymar_tri";
    return sg_make_shader(&d);
}

static sg_shader make_vstream_shader() {
    sg_shader_desc d{};
    // Prepend the generated index/value defines; sg_make_shader compiles
    // synchronously so the temporaries only need to outlive this call.
    const std::string prelude = vstream_hlsl_prelude();
    const std::string vs_src = prelude + kVStreamVS;
    const std::string fs_src = prelude + kVStreamFS;
    d.vertex_func.source = vs_src.c_str();
    d.vertex_func.entry = "vs_main";
    d.vertex_func.d3d11_target = "vs_5_0";
    d.fragment_func.source = fs_src.c_str();
    d.fragment_func.entry = "fs_main";
    d.fragment_func.d3d11_target = "ps_5_0";
    d.attrs[0].base_type = SG_SHADERATTRBASETYPE_FLOAT;
    d.attrs[0].hlsl_sem_name = "TEXCOORD";
    d.attrs[0].hlsl_sem_index = 0;
    d.attrs[1].base_type = SG_SHADERATTRBASETYPE_FLOAT;
    d.attrs[1].hlsl_sem_name = "TEXCOORD";
    d.attrs[1].hlsl_sem_index = 1;
    d.attrs[2].base_type = SG_SHADERATTRBASETYPE_FLOAT;
    d.attrs[2].hlsl_sem_name = "TEXCOORD";
    d.attrs[2].hlsl_sem_index = 2;
    // uniform blob: 48 float4 = 768 bytes per stage
    d.uniform_blocks[0].stage = SG_SHADERSTAGE_VERTEX;
    d.uniform_blocks[0].size = 768;
    d.uniform_blocks[0].hlsl_register_b_n = 0;
    d.uniform_blocks[1].stage = SG_SHADERSTAGE_FRAGMENT;
    d.uniform_blocks[1].size = 768;
    d.uniform_blocks[1].hlsl_register_b_n = 1;
    // texture slot 0 + linear sampler slot 0 (bound per draw; a 1x1 white
    // fallback is bound when the material has no texture)
    sg_shader_view tv{};
    tv.texture.stage = SG_SHADERSTAGE_FRAGMENT;
    tv.texture.image_type = SG_IMAGETYPE_2D;
    tv.texture.sample_type = SG_IMAGESAMPLETYPE_FLOAT;
    tv.texture.hlsl_register_t_n = 0;
    d.views[0] = tv;
    sg_shader_sampler sm{};
    sm.stage = SG_SHADERSTAGE_FRAGMENT;
    sm.sampler_type = SG_SAMPLERTYPE_FILTERING;
    sm.hlsl_register_s_n = 0;
    d.samplers[0] = sm;
    sg_shader_texture_sampler_pair pair{};
    pair.stage = SG_SHADERSTAGE_FRAGMENT;
    pair.view_slot = 0;
    pair.sampler_slot = 0;
    d.texture_sampler_pairs[0] = pair;
    d.label = "lymar_vstream";
    return sg_make_shader(&d);
}

static sg_shader make_blit_shader() {
    sg_shader_desc d{};
    d.vertex_func.source = kBlitVS;
    d.vertex_func.entry = "vs_main";
    d.vertex_func.d3d11_target = "vs_5_0";
    d.fragment_func.source = kBlitFS;
    d.fragment_func.entry = "fs_main";
    d.fragment_func.d3d11_target = "ps_5_0";
    sg_shader_view tv{};
    tv.texture.stage = SG_SHADERSTAGE_FRAGMENT;
    tv.texture.image_type = SG_IMAGETYPE_2D;
    tv.texture.sample_type = SG_IMAGESAMPLETYPE_FLOAT;
    tv.texture.hlsl_register_t_n = 0;
    d.views[0] = tv;
    sg_shader_sampler sm{};
    sm.stage = SG_SHADERSTAGE_FRAGMENT;
    sm.sampler_type = SG_SAMPLERTYPE_FILTERING;
    sm.hlsl_register_s_n = 0;
    d.samplers[0] = sm;
    sg_shader_texture_sampler_pair pair{};
    pair.stage = SG_SHADERSTAGE_FRAGMENT;
    pair.view_slot = 0;
    pair.sampler_slot = 0;
    d.texture_sampler_pairs[0] = pair;
    d.label = "lymar_blit";
    return sg_make_shader(&d);
}

static sg_pipeline make_pipe(sg_shader sh, bool depth, bool blend, int prim) {
    sg_pipeline_desc d{};
    d.shader = sh;
    d.primitive_type = (prim == 1) ? SG_PRIMITIVETYPE_LINES : SG_PRIMITIVETYPE_TRIANGLES;
    if (depth) {
        d.depth.pixel_format = SG_PIXELFORMAT_DEPTH;
        d.depth.compare = SG_COMPAREFUNC_LESS;
        d.depth.write_enabled = true;
    }
    if (blend) {
        d.colors[0].blend.enabled = true;
        d.colors[0].blend.src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA;
        d.colors[0].blend.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
        d.colors[0].blend.op_rgb = SG_BLENDOP_ADD;
        d.colors[0].blend.src_factor_alpha = SG_BLENDFACTOR_ONE;
        d.colors[0].blend.dst_factor_alpha = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
        d.colors[0].blend.op_alpha = SG_BLENDOP_ADD;
    }
    d.colors[0].write_mask = SG_COLORMASK_RGBA;
    d.label = "lymar_pipe";
    return sg_make_pipeline(&d);
}

static sg_pipeline make_vstream_pipe(sg_shader sh, sg_primitive_type prim) {
    sg_pipeline_desc d{};
    d.shader = sh;
    d.primitive_type = prim;
    d.index_type = SG_INDEXTYPE_UINT32;
    // Match the software/CPU rasterizer: front = CCW in y-down screen space
    // (renderer.lm and software_graphics.hh keep cross_z < 0 for CullMode.Back).
    d.face_winding = SG_FACEWINDING_CCW;
    d.depth.pixel_format = SG_PIXELFORMAT_DEPTH;
    d.depth.compare = SG_COMPAREFUNC_LESS;
    d.depth.write_enabled = true;
    d.colors[0].blend.enabled = true;
    d.colors[0].blend.src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA;
    d.colors[0].blend.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
    d.colors[0].blend.op_rgb = SG_BLENDOP_ADD;
    d.colors[0].blend.src_factor_alpha = SG_BLENDFACTOR_ONE;
    d.colors[0].blend.dst_factor_alpha = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
    d.colors[0].blend.op_alpha = SG_BLENDOP_ADD;
    d.colors[0].write_mask = SG_COLORMASK_RGBA;
    // vertex buffer 0: stride 32, attrs pos@0 (float3), nrm@12 (float3), uv@24 (float2)
    d.layout.buffers[0].stride = 32;
    d.layout.attrs[0].buffer_index = 0;
    d.layout.attrs[0].offset = 0;
    d.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT3;
    d.layout.attrs[1].buffer_index = 0;
    d.layout.attrs[1].offset = 12;
    d.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT3;
    d.layout.attrs[2].buffer_index = 0;
    d.layout.attrs[2].offset = 24;
    d.layout.attrs[2].format = SG_VERTEXFORMAT_FLOAT2;
    d.label = "lymar_vstream_pipe";
    return sg_make_pipeline(&d);
}

// ---------------------------------------------------------------------------

static void sg_log_stderr(const char* tag, uint32_t level, uint32_t item,
                          const char* msg, uint32_t line, const char* file, void*) {
    std::fprintf(stderr, "[sg:%s] %s (%s:%u)\n", tag ? tag : "?",
                 msg ? msg : "(no message)", file ? file : "?", line);
    (void)level; (void)item;
}

SokolGfxRuntime& sokol_gfx_runtime() {
    static SokolGfxRuntime rt;
    return rt;
}

bool SokolGfxRuntime::setup() {
    if (ready_) return true;
    impl_ = new Impl();

    sg_desc desc{};
    desc.environment = sglue_environment();
    desc.logger.func = sg_log_stderr;
    sg_setup(&desc); // returns void; validity checked via sg_isvalid()
    if (!sg_isvalid()) {
        delete impl_;
        impl_ = nullptr;
        return false;
    }

    impl_->sh_rect = make_rect_shader();
    impl_->sh_tri = make_tri_shader();
    impl_->sh_vstream = make_vstream_shader();
    impl_->sh_blit = make_blit_shader();

    impl_->pipe_rect = make_pipe(impl_->sh_rect, false, true, 0);
    impl_->pipe_tri = make_pipe(impl_->sh_tri, false, true, 0);
    impl_->pipe_vstream = make_vstream_pipe(impl_->sh_vstream, SG_PRIMITIVETYPE_TRIANGLES);
    impl_->pipe_vlines = make_vstream_pipe(impl_->sh_vstream, SG_PRIMITIVETYPE_LINES);
    // TEMP-DIAG: shader/pipeline validity (SG_INVALID_ID means creation failed)
    std::fprintf(stderr, "[lymar-dbg] shaders: rect=%d tri=%d vstream=%d blit=%d | pipes: vstream=%d vlines=%d\n",
        impl_->sh_rect.id, impl_->sh_tri.id, impl_->sh_vstream.id, impl_->sh_blit.id,
        impl_->pipe_vstream.id, impl_->pipe_vlines.id);

    sg_sampler_desc sd{};
    sd.min_filter = SG_FILTER_LINEAR;
    sd.mag_filter = SG_FILTER_LINEAR;
    impl_->blit_smp = sg_make_sampler(&sd);

    // d3 vertex-stream texture sampler (linear, clamp to edge)
    sg_sampler_desc tsd{};
    tsd.min_filter = SG_FILTER_LINEAR;
    tsd.mag_filter = SG_FILTER_LINEAR;
    tsd.wrap_u = SG_WRAP_CLAMP_TO_EDGE;
    tsd.wrap_v = SG_WRAP_CLAMP_TO_EDGE;
    impl_->tex_smp = sg_make_sampler(&tsd);

    // 1x1 white fallback texture: bound whenever a vstream draw has no
    // material texture, so shader slot 0 is always valid.
    {
        const uint8_t white[4] = {255, 255, 255, 255};
        sg_image_desc id{};
        id.width = 1; id.height = 1;
        id.pixel_format = SG_PIXELFORMAT_RGBA8;
        id.num_mipmaps = 1;
        id.data.mip_levels[0].ptr = white;
        id.data.mip_levels[0].size = 4;
        id.label = "lymar_white";
        impl_->white_img = sg_make_image(&id);
        sg_view_desc vd{};
        vd.texture.image = impl_->white_img;
        impl_->white_view = sg_make_view(&vd);
    }

    // blit pipeline needs a texture-bound pipeline variant; reuse pipe_rect
    // style but with the blit shader:
    {
        sg_pipeline_desc d{};
        d.shader = impl_->sh_blit;
        d.primitive_type = SG_PRIMITIVETYPE_TRIANGLES;
        d.colors[0].write_mask = (sg_color_mask)(SG_COLORMASK_RGB | SG_COLORMASK_A);
        d.label = "lymar_blit_pipe";
        impl_->pipe_blit = sg_make_pipeline(&d);
    }

    // immediate-mode text: sokol_gl + fontstash atlas
    sgl_desc_t sgl_desc{};
    sgl_setup(&sgl_desc);
    if (load_font_data()) {
        sfons_desc_t fd{};
        fd.width = 512;
        fd.height = 512;
        impl_->fons = sfons_create(&fd);
        if (impl_->fons) {
            impl_->fons_font = fonsAddFontMem(impl_->fons, "lymar",
                g_font_data.data(), (int)g_font_data.size(), 0);
        }
    }

    ready_ = true;
    return true;
}

void SokolGfxRuntime::shutdown() {
    if (!ready_) return;
    ready_ = false;
    if (impl_) {
        if (impl_->fons) { sfons_destroy(impl_->fons); impl_->fons = nullptr; }
        impl_->fons_font = -1;
    }
    sgl_shutdown();
    sg_shutdown();
    if (impl_) {
        delete impl_;
        impl_ = nullptr;
    }
}

void SokolGfxRuntime::submit(const GfxCommand& cmd) {
    // Queue even before ready_: resource creation (textures, buffers) can run
    // on the VM thread before sokol_init finishes setup() on the app thread.
    // pending_ is only drained by render_frame() after setup, so early
    // commands execute in order on the first presented frame. In headless
    // mode the deque simply fills to the safety cap and is never drained.
    if (cmd.type == GfxCommand::Type::MakeImage && getenv("LYMAR_DBG_TEX"))
        fprintf(stderr, "[texdbg-sub] MakeImage queued ready=%d pending=%zu\n",
            (int)ready_.load(), pending_.size());
    std::lock_guard<std::mutex> lock(mutex_);
    if (pending_.size() > 65536) pending_.pop_front(); // safety valve
    pending_.push_back(cmd);
}

void SokolGfxRuntime::commit_frame() {
    if (!ready_) return;
    std::lock_guard<std::mutex> lock(mutex_);
    if (pending_.empty()) return;
    ++dbg_commits_;
    // Latest-frame-wins: drop any complete frames the render thread hasn't
    // presented yet. Concatenating them would issue multiple sg_commit
    // presents per display refresh and visibly alternate old/new content.
    // Resource-creation commands are idempotent (MakeImage/MakeBuffer/
    // MakePipeline destroy-then-recreate) and MUST survive the drop — a
    // texture uploaded in a frame that loses the race would otherwise never
    // reach the GPU and every textured draw silently binds the fallback.
    for (auto it = completed_.rbegin(); it != completed_.rend(); ++it) {
        const auto t = it->type;
        if (t == GfxCommand::Type::MakeImage ||
            t == GfxCommand::Type::MakeBuffer ||
            t == GfxCommand::Type::MakePipeline) {
            pending_.push_front(*it);
        }
    }
    completed_.clear();
    completed_.insert(completed_.end(),
                  std::make_move_iterator(pending_.begin()),
                  std::make_move_iterator(pending_.end()));
    pending_.clear();
}

bool SokolGfxRuntime::render_frame() {
    if (!ready_ || !impl_) return false;
    ++frame_id_;
    auto t0 = std::chrono::steady_clock::now();

    std::deque<GfxCommand> cmds;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        cmds.swap(completed_);
    }
    // TEMP-DIAG: periodic pacing summary — evaluated on EVERY sapp frame.
    if (++dbg_frames_ % 120 == 0) {
        std::fprintf(stderr, "[lymar-dbg] pacing: presents=%d commits=%d skips=%d vdraws=%d last_cmds=%zu\n",
            dbg_presents_, dbg_commits_, dbg_skips_, dbg_vdraw_, cmds.size());
        dbg_vdraw_ = 0;
    }
    if (cmds.empty()) {
        // TEMP-DIAG: sapp frame fired but no complete frame was committed —
        // the VM is producing slower than the display refresh.
        ++dbg_skips_;
        return false; // no complete frame -> keep last presented frame
    }
    ++dbg_presents_;

    // Pass state mirrors Impl::pass_open_
    for (auto& cmd : cmds) {
        execute(cmd);
    }
    // Close any pass left open at end of frame.
    flush_text();
    if (pass_open_) {
        sg_end_pass();
        sg_commit();
        pass_open_ = false;
    }
    // TEMP-DIAG: render-thread frame cost; >~12ms risks a missed vsync.
    auto t1 = std::chrono::steady_clock::now();
    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    if (ms > 8.0) {
        ++dbg_slow_;
        if (dbg_slow_ <= 20) {
            std::fprintf(stderr, "[lymar-dbg] slow render_frame %.1fms cmds=%zu\n", ms, cmds.size());
        }
    }
    return true; // a complete frame batch was processed (pass committed)
}

static void apply_scissor(SokolGfxRuntime::Impl* impl) {
    if (impl->clip_stack.empty()) {
        // reset to full pass area
        sg_apply_scissor_rect(0, 0, impl->pass_w, impl->pass_h, true);
        return;
    }
    auto& r = impl->clip_stack.back();
    sg_apply_scissor_rect(r[0], r[1], r[2], r[3], true);
}

void SokolGfxRuntime::execute(const GfxCommand& cmd) {
    Impl* im = impl_;
    switch (cmd.type) {
        case GfxCommand::Type::Clear: {
            if (pass_open_) { flush_text(); sg_end_pass(); }
            float r = 0, g = 0, b = 0, a = 1;
            if (cmd.f.size() >= 4) { r = cmd.f[0]; g = cmd.f[1]; b = cmd.f[2]; a = cmd.f[3]; }
            sg_pass pass{};
            pass.action.colors[0].load_action = SG_LOADACTION_CLEAR;
            pass.action.colors[0].store_action = SG_STOREACTION_STORE;
            pass.action.colors[0].clear_value.r = r;
            pass.action.colors[0].clear_value.g = g;
            pass.action.colors[0].clear_value.b = b;
            pass.action.colors[0].clear_value.a = a;
            pass.action.depth.load_action = SG_LOADACTION_CLEAR;
            pass.action.depth.store_action = SG_STOREACTION_STORE;
            pass.action.depth.clear_value = 1.0f;
            pass.swapchain = sglue_swapchain();
            if (pass.swapchain.invalid) return;
            im->pass_w = pass.swapchain.width;
            im->pass_h = pass.swapchain.height;
            sg_begin_pass(&pass);
            pass_open_ = true;
            im->clip_stack.clear();
            apply_scissor(im);
            break;
        }
        case GfxCommand::Type::EndPass: {
            if (pass_open_) {
                flush_text();
                sg_end_pass();
                sg_commit();
                pass_open_ = false;
            }
            break;
        }
        case GfxCommand::Type::DrawRect: {
            if (!pass_open_ || cmd.f.size() < 10) break;
            sg_apply_pipeline(im->pipe_rect);
            // uniforms: pos(2) size(2) color(4) rad_bw(2) viewport(2) = 48 bytes
            float ub[12] = {};
            ub[0] = cmd.f[0]; ub[1] = cmd.f[1];          // pos
            ub[2] = cmd.f[2]; ub[3] = cmd.f[3];          // size
            ub[4] = cmd.f[4]; ub[5] = cmd.f[5]; ub[6] = cmd.f[6]; ub[7] = cmd.f[7]; // color
            ub[8] = cmd.f[8]; ub[9] = cmd.f[9];          // radius, border_w
            ub[10] = im->pass_w; ub[11] = im->pass_h;    // viewport
            sg_range rng{ub, sizeof(ub)};
            sg_apply_uniforms(0, &rng);
            sg_apply_uniforms(1, &rng);
            sg_draw(0, 6, 1);
            break;
        }
        case GfxCommand::Type::DrawTri: {
            if (!pass_open_ || cmd.f.size() < 10) break;
            sg_apply_pipeline(im->pipe_tri);
            float ub[8] = {};
            ub[0] = cmd.f[0]; ub[1] = cmd.f[1];
            ub[2] = cmd.f[2]; ub[3] = cmd.f[3];
            ub[4] = cmd.f[4]; ub[5] = cmd.f[5];
            ub[6] = im->pass_w; ub[7] = im->pass_h;
            sg_range vrng{ub, 32};
            sg_apply_uniforms(0, &vrng);
            float fc[4] = {(float)cmd.f[6], (float)cmd.f[7], (float)cmd.f[8], (float)cmd.f[9]};
            sg_range frng{fc, sizeof(fc)};
            sg_apply_uniforms(1, &frng);
            sg_draw(0, 3, 1);
            break;
        }
        case GfxCommand::Type::PushClip: {
            if (cmd.f.size() < 4) break;
            int x = (int)cmd.f[0], y = (int)cmd.f[1];
            int w = (int)cmd.f[2], h = (int)cmd.f[3];
            int x0 = x, y0 = y, x1 = x + w, y1 = y + h;
            if (!im->clip_stack.empty()) {
                auto& p = im->clip_stack.back();
                x0 = std::max(x0, p[0]); y0 = std::max(y0, p[1]);
                x1 = std::min(x1, p[0] + p[2]); y1 = std::min(y1, p[1] + p[3]);
            }
            x0 = std::clamp(x0, 0, im->pass_w);
            y0 = std::clamp(y0, 0, im->pass_h);
            x1 = std::clamp(x1, 0, im->pass_w);
            y1 = std::clamp(y1, 0, im->pass_h);
            im->clip_stack.push_back({x0, y0, std::max(0, x1 - x0), std::max(0, y1 - y0)});
            apply_scissor(im);
            break;
        }
        case GfxCommand::Type::PopClip: {
            if (!im->clip_stack.empty()) im->clip_stack.pop_back();
            apply_scissor(im);
            break;
        }
        case GfxCommand::Type::MakeBuffer: {
            if (cmd.i.empty()) break;
            int id = (int)cmd.i[0];
            // Defer sg_make_buffer until bind time: vertex vs index encoding
            // is only known when the buffer is bound.
            im->pending_bufs[id] = cmd.lists.empty() ? std::vector<double>() : cmd.lists[0];
            auto bit = im->buffers.find(id);
            if (bit != im->buffers.end()) {
                if (bit->second.buf.id != SG_INVALID_ID) sg_destroy_buffer(bit->second.buf);
                if (bit->second.edge_buf.id != SG_INVALID_ID) sg_destroy_buffer(bit->second.edge_buf);
                bit->second = Impl::BufRec{};
            }
            break;
        }
        case GfxCommand::Type::MakePipeline: {
            if (cmd.i.size() < 3) break;
            int id = (int)cmd.i[0];
            int prim = (int)cmd.i[2];
            im->pipeline_kinds[id] = prim;
            break;
        }
        case GfxCommand::Type::ApplyPipeline: {
            if (cmd.i.empty()) break;
            cur_pipeline_ = (int)cmd.i[0];
            auto it = im->pipeline_kinds.find(cur_pipeline_);
            int kind = (it != im->pipeline_kinds.end()) ? it->second : 0;
            // kind: 2 = vertex stream; anything else maps to the solid pipes
            if (kind == 2) {
                sg_apply_pipeline(im->pipe_vstream);
                im->bound_pipe_kind = 2;
            } else {
                sg_apply_pipeline(im->pipe_tri); // placeholder solid pipe
                im->bound_pipe_kind = 1;
            }
            break;
        }
        case GfxCommand::Type::ApplyBindings: {
            if (!pass_open_ || cmd.i.size() < 2) break;
            int vid = (int)cmd.i[0], iid = (int)cmd.i[1];
            cur_vbuf_ = vid;
            cur_ibuf_ = iid;
            im->cur_img_ = (cmd.i.size() > 2) ? (int)cmd.i[2] : 0;
            im->bound_vbuf = ensure_buffer(im, vid, false);
            im->bound_ibuf = (iid > 0) ? ensure_buffer(im, iid, true) : (sg_buffer){SG_INVALID_ID};
            im->uniforms.clear();
            if (!cmd.lists.empty()) {
                im->uniforms = cmd.lists[0];
            }
            break;
        }
        case GfxCommand::Type::Draw: {
            if (!pass_open_ || im->bound_pipe_kind != 2) break;
            if (im->bound_vbuf.id == SG_INVALID_ID) break;
            // uniforms: pad blob to 768 bytes (48 float4 cbuffer capacity)
            namespace gu = gfx_uniform;
            float ub[gu::kCBufferFloat4s * 4];
            std::memset(ub, 0, sizeof(ub));
            size_t n = std::min(im->uniforms.size(), (size_t)(gu::kCBufferFloat4s * 4));
            for (size_t k = 0; k < n; ++k) ub[k] = (float)im->uniforms[k];
            bool wire = (n > (size_t)gu::kShadingOffset && ub[gu::kShadingOffset] == (float)gu::kShadingWireframe);
            // sokol requires bindings+uniforms AFTER the last apply_pipeline
            sg_apply_pipeline(wire ? im->pipe_vlines : im->pipe_vstream);
            sg_range vr{ub, sizeof(ub)};
            sg_apply_uniforms(0, &vr);
            sg_apply_uniforms(1, &vr);
            sg_bindings b{};
            b.vertex_buffers[0] = im->bound_vbuf;
            // texture slot: bound image or the 1x1 white fallback
            auto tit = im->textures.find(im->cur_img_);
            if (getenv("LYMAR_DBG_TEX") && dbg_vdraw_ < 6) {
                fprintf(stderr, "[texdbg] img=%d found=%d flag=%f view=%u uv0=(%.2f,%.2f)\n",
                    im->cur_img_, tit != im->textures.end() ? 1 : 0,
                    n > 179 ? ub[179] : -1.f,
                    tit != im->textures.end() ? tit->second.view.id : im->white_view.id,
                    0.f, 0.f);
            }
            if (tit != im->textures.end()) {
                b.views[0] = tit->second.view;
            } else {
                b.views[0] = im->white_view;
            }
            b.samplers[0] = im->tex_smp;
            int elems = 0;
            if (im->bound_ibuf.id != SG_INVALID_ID) {
                auto iit = im->buffers.find(cur_ibuf_);
                if (wire && iit != im->buffers.end() && iit->second.edge_buf.id != SG_INVALID_ID) {
                    // Wireframe: draw triangle edges as a line list. D3D11 has
                    // no wide-line support, so thickness is fixed at 1px.
                    b.index_buffer = iit->second.edge_buf;
                    elems = iit->second.edge_count;
                } else {
                    b.index_buffer = im->bound_ibuf;
                    elems = (iit != im->buffers.end()) ? iit->second.count : 0;
                }
            } else {
                auto vit = im->buffers.find(cur_vbuf_);
                elems = (vit != im->buffers.end()) ? vit->second.count : 0;
            }
            if (elems <= 0) break;
            ++dbg_vdraw_;
            sg_apply_bindings(&b);
            sg_draw(0, elems, 1);
            break;
        }
        case GfxCommand::Type::MakeImage: {
            if (getenv("LYMAR_DBG_TEX"))
                fprintf(stderr, "[texdbg-exec] MakeImage id=%lld w=%d h=%d px=%zu\n",
                    cmd.i.empty() ? -1LL : (long long)cmd.i[0], cmd.w, cmd.h, cmd.pixels.size());
            // RGBA8: exactly w*h*4 bytes or the upload is rejected by sokol
            // validation and leaves an invalid view bound at draw time.
            if (cmd.i.empty() || cmd.w <= 0 || cmd.h <= 0 ||
                cmd.pixels.size() != (size_t)cmd.w * (size_t)cmd.h * 4) break;
            int id = (int)cmd.i[0];
            auto& rec = im->textures[id];
            if (rec.img.id != SG_INVALID_ID) sg_destroy_image(rec.img);
            if (rec.view.id != SG_INVALID_ID) sg_destroy_view(rec.view);
            sg_image_desc idesc{};
            idesc.width = cmd.w;
            idesc.height = cmd.h;
            idesc.pixel_format = SG_PIXELFORMAT_RGBA8;
            idesc.num_mipmaps = 1;
            idesc.data.mip_levels[0].ptr = cmd.pixels.data();
            idesc.data.mip_levels[0].size = cmd.pixels.size();
            idesc.label = "lymar_tex";
            rec.img = sg_make_image(&idesc);
            sg_view_desc vd{};
            vd.texture.image = rec.img;
            rec.view = sg_make_view(&vd);
            break;
        }
        case GfxCommand::Type::DrawTextCmd: {
            // Defer: glyphs rasterize lazily inside fonsDrawText and dirty the
            // atlas; sokol allows only ONE sg_update_image per image per frame,
            // so all text must rasterize before a single sfons_flush+sgl_draw.
            if (!pass_open_ || cmd.s.empty()) break;
            GfxCommand d = cmd;
            if (!im->clip_stack.empty()) d.clip = im->clip_stack.back();
            im->deferred_text.push_back(std::move(d));
            ++im->dbg_deferred_total;
            break;
        }
        case GfxCommand::Type::BlitFramebuffer: {
            if (!pass_open_ || cmd.pixels.empty() || cmd.w <= 0 || cmd.h <= 0) break;
            // (re)create image+view when size changes
            if (im->blit_w != cmd.w || im->blit_h != cmd.h || im->blit_img.id == SG_INVALID_ID) {
                if (im->blit_img.id != SG_INVALID_ID) sg_destroy_image(im->blit_img);
                if (im->blit_view.id != SG_INVALID_ID) sg_destroy_view(im->blit_view);
                sg_image_desc id{};
                id.width = cmd.w; id.height = cmd.h;
                id.pixel_format = SG_PIXELFORMAT_RGBA8;
                id.num_mipmaps = 1;
                id.usage.dynamic_update = true;
                id.label = "lymar_fb";
                im->blit_img = sg_make_image(&id);
                sg_view_desc vd{};
                vd.texture.image = im->blit_img;
                im->blit_view = sg_make_view(&vd);
                im->blit_w = cmd.w; im->blit_h = cmd.h;
            }
            sg_image_data idata{};
            idata.mip_levels[0].ptr = cmd.pixels.data();
            idata.mip_levels[0].size = cmd.pixels.size();
            sg_update_image(im->blit_img, &idata);
            sg_apply_pipeline(im->pipe_blit);
            sg_bindings b{};
            b.views[0] = im->blit_view;
            b.samplers[0] = im->blit_smp;
            sg_apply_bindings(&b);
            sg_draw(0, 3, 1);
            break;
        }
        default:
            break;
    }
}

void SokolGfxRuntime::flush_text() {
    Impl* im = impl_;
    if (im->deferred_text.empty()) return;
    if (!pass_open_ || !im->fons || im->fons_font < 0) {
        im->deferred_text.clear();
        return;
    }
    FONScontext* f = im->fons;
    // sgl's projection matrix defaults to identity and sgl_ortho MULTIPLIES
    // into the current matrix (it does not replace), so the stack must be
    // reset to identity first or the transform degenerates after ~2 flushes.
    sgl_matrix_mode_projection();
    sgl_load_identity();
    sgl_ortho(0.0f, (float)im->pass_w, (float)im->pass_h, 0.0f, -1.0f, 1.0f);
    sgl_matrix_mode_modelview();
    sgl_load_identity();
    for (const GfxCommand& cmd : im->deferred_text) {
        // scissor state is recorded into sgl's ordered command stream before
        // this text's draw commands, so per-text clips survive the batch
        if (cmd.clip.size() >= 4) {
            sgl_scissor_rect(cmd.clip[0], cmd.clip[1], cmd.clip[2], cmd.clip[3], true);
        } else {
            sgl_scissor_rect(0, 0, im->pass_w, im->pass_h, true);
        }
        const float size = gfx_font_size_for_scale((int)cmd.f[6]);
        const uint32_t col = sfons_rgba(
            (uint8_t)std::clamp(cmd.f[2] * 255.0, 0.0, 255.0),
            (uint8_t)std::clamp(cmd.f[3] * 255.0, 0.0, 255.0),
            (uint8_t)std::clamp(cmd.f[4] * 255.0, 0.0, 255.0),
            (uint8_t)std::clamp(cmd.f[5] * 255.0, 0.0, 255.0));
        fonsPushState(f);
        fonsSetFont(f, im->fons_font);
        fonsSetSize(f, size);
        fonsSetColor(f, col);
        fonsSetAlign(f, FONS_ALIGN_LEFT | FONS_ALIGN_TOP);
        float asc = 0, desc = 0, lineh = 0;
        fonsVertMetrics(f, &asc, &desc, &lineh);
        if (lineh <= 0) lineh = size;
        const char* p = cmd.s.c_str();
        const char* end = p + cmd.s.size();
        float ty = (float)cmd.f[1];
        while (p < end) {
            const char* nl = (const char*)memchr(p, '\n', (size_t)(end - p));
            if (!nl) nl = end;
            fonsDrawText(f, (float)cmd.f[0], ty, p, nl);
            ty += lineh;
            p = (nl < end) ? nl + 1 : end;
        }
        fonsPopState(f);
    }
    const size_t text_count = im->deferred_text.size();
    im->deferred_text.clear();
    im->dbg_flushed_total += text_count;
    // ONE atlas upload per frame max (sokol allows a single sg_update_image
    // per image per frame); replay sgl's ordered scissor+draw commands and
    // restore the raw sg scissor afterwards
    if (last_text_flush_ != frame_id_) {
        last_text_flush_ = frame_id_;
        sfons_flush(f);
    }
    sgl_draw();
    apply_scissor(im);
}

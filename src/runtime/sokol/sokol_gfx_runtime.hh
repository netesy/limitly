#pragma once
// Sokol-GFX GPU backend runtime for the Lymar VM graphics resource.
//
// Threading model: resource calls arrive on the VM thread and are decoded
// into GfxCommand records pushed onto a mutex-protected queue. The actual
// sg_* calls run on the sokol_app thread inside the frame callback
// (sokol_gfx_runtime().render_frame()), because sokol_gfx is not
// thread-safe and must run on the thread that owns the GL/D3D11 context.

#include <atomic>
#include <cstdint>
#include <deque>
#include <mutex>
#include <string>
#include <vector>

struct GfxCommand {
    enum class Type : uint8_t {
        Clear,          // begin pass: f = [r,g,b,a]
        DrawRect,       // f = [x,y,w,h,r,g,b,a,radius,border_w]
        DrawTri,        // f = [x1,y1,x2,y2,x3,y3,r,g,b,a]
        PushClip,       // f = [x,y,w,h]
        PopClip,
        MakeBuffer,     // i = [id, is_index]; lists[0] = float data
        ApplyPipeline,  // i = [pip_id]
        ApplyBindings,  // i = [vbuf_id, ibuf_id]; lists[0] = uniforms (optional)
        Draw,           // i = [base, count, instances] (informational)
        MakePipeline,   // i = [pip_id, shader_id, prim_type]
        MakeImage,      // i = [id]; w,h + pixels (RGBA8) - texture upload
        BlitFramebuffer,// w,h + pixels (RGBA8) - software rasterizer presentation
        DrawTextCmd,    // s = text, f = [x, y, r, g, b, a, scale]
        EndPass,
        Nop
    };

    Type type = Type::Nop;
    std::vector<double> f;
    std::vector<int64_t> i;
    std::vector<std::vector<double>> lists;
    std::vector<uint8_t> pixels;
    std::string s;
    std::vector<int> clip;  // render-thread clip snapshot {x,y,w,h} (empty = full)
    int w = 0;
    int h = 0;
};

class SokolGfxRuntime {
public:
    // Called on the sokol_app thread (inside init callback, after sapp env is
    // valid). Returns false if sg_setup failed.
    bool setup();
    void shutdown();
    bool ready() const { return ready_.load(); }

    // VM-thread side: enqueue a decoded command. Drops silently when the GPU
    // backend is not active (headless / software mode).
    void submit(const GfxCommand& cmd);
    // VM-thread frame boundary (called from POLL): atomically publish the
    // pending batch as one complete frame. render_frame() only ever sees
    // whole frames, so partial frames can never be presented.
    void commit_frame();

    // sokol_app thread: drain the queue and issue sg_* calls for this frame.
    // Returns true when a frame was actually presented (vsync-throttled by
    // the swapchain); false when the queue held no complete frame.
    bool render_frame();

    struct Impl;   // public so file-local helpers can name the pimpl type

private:
    void execute(const GfxCommand& cmd);
    void flush_text();   // draw deferred DrawTextCmds: one atlas upload + one sgl_draw
    Impl* impl_ = nullptr;

    std::mutex mutex_;
    std::deque<GfxCommand> pending_;  // VM thread appends here
    std::deque<GfxCommand> completed_;  // complete frames, render thread drains
    std::atomic<bool> ready_{false};
    bool pass_open_ = false;
    uint64_t frame_id_ = 0;
    uint64_t last_text_flush_ = ~0ull; // frame id of last sfons_flush (1 atlas upload/frame max)
    int cur_pipeline_ = -1;   // lymar pipeline id currently applied
    int cur_vbuf_ = -1;
    int cur_ibuf_ = -1;
    // TEMP-DIAG pacing counters
    int dbg_presents_ = 0, dbg_skips_ = 0, dbg_slow_ = 0, dbg_commits_ = 0, dbg_frames_ = 0, dbg_vdraw_ = 0;
};

SokolGfxRuntime& sokol_gfx_runtime();

// Lymar text scale (1..n) -> font pixel size, shared by the GPU draw path and
// the VM-thread metrics helpers below.
float gfx_font_size_for_scale(int scale);

// VM-thread text metrics via a dedicated CPU-only fontstash context (no GPU
// resources). Return false until the GPU backend has loaded a font.
bool gfx_text_metrics_ready();
float gfx_measure_text(const char* text, int scale);
float gfx_line_height(int scale);

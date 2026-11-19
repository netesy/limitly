#if !defined(__wasi__)
// AOT graphics resource: native-driver/headless-bookkeeping only.
//
// The full software renderer (sokol_gfx present path, sokol_app window/event
// loop, CPU rasterizer, truetype font atlas) was removed from the standalone
// runtime: std.gg's native driver path (std.native.d3d11/vulkan via FFI)
// owns drawing, and std.app's native window mode owns the HWND. This
// resource remains only for handle bookkeeping and the window-attach ops
// that std.gg still issues; every draw/present op returns nil because no
// caller reaches them while _native_on is set.
#include "aot_graphics_access.hh"
#include "../runtime/native_d3d11_window.h"
#include <vector>

namespace {
struct AotGraphicsResource : GraphicsBase {
    int width_ = 800;
    int height_ = 600;

    LM::Backend::VM::ResourceType getType() const override {
        return LM::Backend::VM::ResourceType::GRAPHICS;
    }

    GraphicsValue call(LM::Backend::VM::ResourceOperation op,
                       const std::vector<GraphicsValue>& args, void*) override {
        using NA = NativeGraphicsAccess;
        switch (op) {
            case LM::Backend::VM::ResourceOperation::OPEN: {
                if (args.size() >= 2) {
                    width_ = static_cast<int>(NA::integer(args[0]));
                    height_ = static_cast<int>(NA::integer(args[1]));
                }
                if (width_ <= 0) width_ = 800;
                if (height_ <= 0) height_ = 600;
                return NA::boolean(true);
            }
            case LM::Backend::VM::ResourceOperation::CLOSE:
            case LM::Backend::VM::ResourceOperation::FLUSH:
                return NA::boolean(true);
            case LM::Backend::VM::ResourceOperation::ATTACH_WINDOW: {
                // args = [hwnd:int, width:int, height:int]; returns bool.
                if (args.size() < 3) return NA::boolean(false);
                auto hwnd = reinterpret_cast<void*>(static_cast<uintptr_t>(NA::integer(args[0])));
                int w = static_cast<int>(NA::integer(args[1]));
                int h = static_cast<int>(NA::integer(args[2]));
                return NA::boolean(LM::Runtime::native_d3d11_attach(hwnd, w, h));
            }
            case LM::Backend::VM::ResourceOperation::DETACH_WINDOW:
                LM::Runtime::native_d3d11_detach();
                return NA::boolean(true);
            case LM::Backend::VM::ResourceOperation::POLL: {
                // Native mode receives OS events through std.events' native
                // drain, not this resource; report an empty event list.
                return NA::pointer(NA::new_list());
            }
            default:
                // Draw/present/resource-creation ops belong to the removed
                // software/sokol backends; native-mode callers never issue
                // them (_native_on short-circuits flush_batch).
                return NA::nil();
        }
    }
};
}

extern "C" GraphicsBase* aot_gfx_create() {
    return new AotGraphicsResource();
}
#endif

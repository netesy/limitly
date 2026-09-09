#include "sokol_app_runtime.hh"

#include <atomic>
#include <condition_variable>
#include <cstring>
#include <mutex>
#include <thread>

#if defined(_WIN32)
#define SOKOL_NO_ENTRY
#define SOKOL_NOAPI
#define SOKOL_APP_IMPL
#include "sokol_app.h"
#include <windows.h>
#endif

namespace LM::Backend::VM {

struct SokolAppRuntime::Impl {
    std::mutex mutex;
    std::condition_variable ready_cv;
    std::condition_variable frame_cv;
    std::vector<RuntimeAppEvent> events;
    std::vector<std::uint8_t> bgra;
    std::thread app_thread;
    std::string title;
    int frame_width = 0;
    int frame_height = 0;
    std::uint64_t frame_generation = 0;
    std::uint64_t consumed_generation = 0;
    std::atomic<bool> started{false};
    std::atomic<bool> finished{false};
    std::atomic<bool> alive{false};
    std::atomic<bool> quit_requested{false};

    void push(int type, int x = 0, int y = 0, int key = 0) {
        std::lock_guard<std::mutex> lock(mutex);
        events.push_back({type, x, y, key});
    }
};

#if defined(_WIN32)
static int normalize_key(sapp_keycode key) {
    switch (key) {
        case SAPP_KEYCODE_BACKSPACE: return 8;
        case SAPP_KEYCODE_TAB: return 9;
        case SAPP_KEYCODE_ENTER: return 13;
        case SAPP_KEYCODE_LEFT: return 37;
        case SAPP_KEYCODE_RIGHT: return 39;
        case SAPP_KEYCODE_DELETE: return 46;
        default: return static_cast<int>(key);
    }
}

static void sokol_init(void* user_data) {
    auto* state = static_cast<SokolAppRuntime::Impl*>(user_data);
    state->alive = true;
    state->started = true;
    state->ready_cv.notify_all();
}

static void sokol_frame(void* user_data) {
    auto* state = static_cast<SokolAppRuntime::Impl*>(user_data);
    if (state->quit_requested.exchange(false)) {
        sapp_request_quit();
    }

    std::lock_guard<std::mutex> lock(state->mutex);
    if (!state->bgra.empty() && state->frame_width > 0 && state->frame_height > 0) {
        HWND hwnd = static_cast<HWND>(const_cast<void*>(sapp_win32_get_hwnd()));
        if (hwnd) {
            HDC hdc = GetDC(hwnd);
            if (hdc) {
                RECT rc{};
                GetClientRect(hwnd, &rc);
                int dst_w = rc.right - rc.left;
                int dst_h = rc.bottom - rc.top;
                BITMAPINFO bmi{};
                bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
                bmi.bmiHeader.biWidth = state->frame_width;
                bmi.bmiHeader.biHeight = -state->frame_height;
                bmi.bmiHeader.biPlanes = 1;
                bmi.bmiHeader.biBitCount = 32;
                bmi.bmiHeader.biCompression = BI_RGB;
                StretchDIBits(hdc, 0, 0, dst_w, dst_h, 0, 0,
                              state->frame_width, state->frame_height, state->bgra.data(),
                              &bmi, DIB_RGB_COLORS, SRCCOPY);
                ReleaseDC(hwnd, hdc);
            }
        }
    }
    ++state->frame_generation;
    state->frame_cv.notify_all();
}

static void sokol_cleanup(void* user_data) {
    auto* state = static_cast<SokolAppRuntime::Impl*>(user_data);
    state->alive = false;
    state->push(0); // EVENT_QUIT
    state->frame_cv.notify_all();
}

static void sokol_event(const sapp_event* event, void* user_data) {
    auto* state = static_cast<SokolAppRuntime::Impl*>(user_data);
    float scale_x = (event->window_width > 0) ? (static_cast<float>(event->framebuffer_width) / static_cast<float>(event->window_width)) : 1.0f;
    float scale_y = (event->window_height > 0) ? (static_cast<float>(event->framebuffer_height) / static_cast<float>(event->window_height)) : 1.0f;
    int mx = static_cast<int>(event->mouse_x * scale_x);
    int my = static_cast<int>(event->mouse_y * scale_y);

    switch (event->type) {
        case SAPP_EVENTTYPE_QUIT_REQUESTED:
            state->push(0);
            break;
        case SAPP_EVENTTYPE_RESIZED:
            // The retained UI and software renderer use framebuffer pixels as
            // their v1 coordinate space.
            state->push(1, event->framebuffer_width, event->framebuffer_height);
            break;
        case SAPP_EVENTTYPE_KEY_DOWN:
            state->push(2, 0, 0, normalize_key(event->key_code));
            break;
        case SAPP_EVENTTYPE_KEY_UP:
            state->push(3, 0, 0, normalize_key(event->key_code));
            break;
        case SAPP_EVENTTYPE_MOUSE_DOWN:
            if (event->mouse_button == SAPP_MOUSEBUTTON_LEFT) {
                state->push(4, mx, my);
            }
            break;
        case SAPP_EVENTTYPE_MOUSE_UP:
            if (event->mouse_button == SAPP_MOUSEBUTTON_LEFT) {
                state->push(5, mx, my);
            }
            break;
        case SAPP_EVENTTYPE_MOUSE_MOVE:
            state->push(6, mx, my);
            break;
        case SAPP_EVENTTYPE_CHAR:
            state->push(7, 0, 0, static_cast<int>(event->char_code));
            break;
        case SAPP_EVENTTYPE_MOUSE_SCROLL:
            // Preserve the existing vertical wheel contract (Win32 wheel units).
            // The runtime event tuple has no horizontal-scroll slot yet.
            state->push(8, 0, static_cast<int>(event->scroll_y * 120.0f));
            break;
        default:
            break;
    }
}
#endif

SokolAppRuntime::SokolAppRuntime() : impl_(new Impl) {}
SokolAppRuntime::~SokolAppRuntime() { stop(); delete impl_; }

bool SokolAppRuntime::start(const SokolAppConfig& config) {
#if defined(_WIN32)
    if (impl_->app_thread.joinable()) return true;
    impl_->title = config.title;
    impl_->app_thread = std::thread([this, config] {
        sapp_desc desc{};
        desc.user_data = impl_;
        desc.init_userdata_cb = sokol_init;
        desc.frame_userdata_cb = sokol_frame;
        desc.cleanup_userdata_cb = sokol_cleanup;
        desc.event_userdata_cb = sokol_event;
        desc.width = config.width;
        desc.height = config.height;
        desc.window_title = impl_->title.c_str();
        desc.high_dpi = config.high_dpi;
        desc.sample_count = 1;
        desc.swap_interval = 1;
        // This vendored sapp_desc has no portable resizable field. Sokol owns
        // the native style and creates a resizable desktop window.
        (void)config.resizable;
        sapp_run(&desc);
        impl_->finished = true;
        impl_->ready_cv.notify_all();
        impl_->frame_cv.notify_all();
    });
    std::unique_lock<std::mutex> lock(impl_->mutex);
    impl_->ready_cv.wait(lock, [this] { return impl_->started.load() || impl_->finished.load(); });
    return impl_->started;
#else
    (void)config;
    return false;
#endif
}

void SokolAppRuntime::request_quit() { impl_->quit_requested = true; }

void SokolAppRuntime::stop() {
#if defined(_WIN32)
    if (impl_->app_thread.joinable()) {
        request_quit();
        impl_->app_thread.join();
    }
#endif
}

bool SokolAppRuntime::running() const { return impl_->alive; }

void SokolAppRuntime::poll_events(std::vector<RuntimeAppEvent>& events) {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    events.insert(events.end(), impl_->events.begin(), impl_->events.end());
    impl_->events.clear();
}

void SokolAppRuntime::submit_frame(const std::uint8_t* rgba, int width, int height) {
    if (!running() || !rgba || width <= 0 || height <= 0) return;
    std::lock_guard<std::mutex> lock(impl_->mutex);
    const std::size_t size = static_cast<std::size_t>(width) * height * 4;
    impl_->bgra.resize(size);
    for (std::size_t i = 0; i < size; i += 4) {
        impl_->bgra[i] = rgba[i + 2];
        impl_->bgra[i + 1] = rgba[i + 1];
        impl_->bgra[i + 2] = rgba[i];
        impl_->bgra[i + 3] = rgba[i + 3];
    }
    impl_->frame_width = width;
    impl_->frame_height = height;
}

void SokolAppRuntime::wait_for_frame() {
    if (!running()) return;
    std::unique_lock<std::mutex> lock(impl_->mutex);
    const auto observed = impl_->consumed_generation;
    impl_->frame_cv.wait(lock, [this, observed] {
        return impl_->frame_generation != observed || !impl_->alive.load();
    });
    impl_->consumed_generation = impl_->frame_generation;
}

void SokolAppRuntime::set_window_size(int width, int height) {
#if defined(_WIN32)
    HWND hwnd = static_cast<HWND>(const_cast<void*>(sapp_win32_get_hwnd()));
    if (hwnd && width > 0 && height > 0) {
        RECT rc = {0, 0, width, height};
        DWORD style = static_cast<DWORD>(GetWindowLong(hwnd, GWL_STYLE));
        DWORD ex_style = static_cast<DWORD>(GetWindowLong(hwnd, GWL_EXSTYLE));
        AdjustWindowRectEx(&rc, style, FALSE, ex_style);
        int w = rc.right - rc.left;
        int h = rc.bottom - rc.top;
        SetWindowPos(hwnd, nullptr, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
#endif
}

SokolAppRuntime& sokol_app_runtime() {
    static SokolAppRuntime runtime;
    return runtime;
}

} // namespace LM::Backend::VM

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace LM::Backend::VM {

struct RuntimeAppEvent {
    int type = 0;
    int x = 0;
    int y = 0;
    int key = 0;
};

struct SokolAppConfig {
    int width = 800;
    int height = 600;
    std::string title = "Limit Application";
    bool resizable = true;
    bool high_dpi = true;
};

// Single-window application bridge. Sokol owns the native window, callbacks,
// and message pump; the VM consumes only normalized RuntimeAppEvent values.
class SokolAppRuntime {
public:
    struct Impl;
    SokolAppRuntime();
    ~SokolAppRuntime();
    SokolAppRuntime(const SokolAppRuntime&) = delete;
    SokolAppRuntime& operator=(const SokolAppRuntime&) = delete;

    bool start(const SokolAppConfig& config);
    void request_quit();
    void stop();
    bool running() const;
    void poll_events(std::vector<RuntimeAppEvent>& events);
    void submit_frame(const std::uint8_t* rgba, int width, int height);
    void wait_for_frame();
    void set_window_size(int width, int height);

private:
    Impl* impl_;
};

// Process-wide runtime application owner. Limit v1 intentionally supports one
// authoritative native application window.
SokolAppRuntime& sokol_app_runtime();

} // namespace LM::Backend::VM

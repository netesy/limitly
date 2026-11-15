// native_d3d11_window - D3D11 device + swapchain on an externally-owned
// HWND (created by std.native.win32 via pure-Lymar FFI).
//
// Replaces the window/swapchain role sokol_app played: the Lymar side
// owns the HWND and all input events; this module only owns the D3D11
// device, swapchain, and back-buffer render target view. sokol_gfx is
// given the device/context via sg_environment.d3d11 and the RTV through
// a hand-built sg_swapchain each frame.

#pragma once

#include <cstdint>

namespace LM::Runtime {

// Creates a D3D11 device (feature level 11_0, BGRA support) and a
// flip-model swapchain bound to `hwnd`. Returns false on failure.
bool native_d3d11_attach(void* hwnd, int width, int height);

// Releases device/context/swapchain/RTV. Safe to call when unattached.
void native_d3d11_detach();

bool native_d3d11_attached();

void* native_d3d11_device();        // ID3D11Device*
void* native_d3d11_device_context();// ID3D11DeviceContext*
void* native_d3d11_rtv();
void* native_d3d11_dsv();           // ID3D11RenderTargetView*
int   native_d3d11_width();
int   native_d3d11_height();

// Recreates the swapchain back buffers + RTV after a resize.
bool native_d3d11_resize(int width, int height);

// Presents the frame (vsync on).
void native_d3d11_present();

} // namespace LM::Runtime

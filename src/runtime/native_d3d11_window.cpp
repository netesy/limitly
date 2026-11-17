// native_d3d11_window.cpp - see header. Windows-only implementation.

#include "native_d3d11_window.h"

#if defined(_WIN32)

#include <d3d11.h>
#include <dxgi1_2.h>
#include <wrl/client.h>
#include <iterator>
#include <cstdio>

namespace LM::Runtime {
namespace {

using Microsoft::WRL::ComPtr;

ComPtr<ID3D11Device>           g_device;
ComPtr<ID3D11DeviceContext>    g_ctx;
ComPtr<IDXGISwapChain1>        g_swap;
ComPtr<ID3D11RenderTargetView> g_rtv;
ComPtr<ID3D11Texture2D>       g_depth_tex;
ComPtr<ID3D11DepthStencilView> g_dsv;
int g_w = 0, g_h = 0;
HWND g_hwnd = nullptr;

bool create_views() {
    ComPtr<ID3D11Texture2D> back;
    if (FAILED(g_swap->GetBuffer(0, IID_PPV_ARGS(&back)))) return false;
    if (FAILED(g_device->CreateRenderTargetView(back.Get(), nullptr, &g_rtv))) {
        return false;
    }
    D3D11_TEXTURE2D_DESC dd{};
    dd.Width = (UINT)g_w;
    dd.Height = (UINT)g_h;
    dd.MipLevels = 1;
    dd.ArraySize = 1;
    dd.Format = DXGI_FORMAT_D32_FLOAT;
    dd.SampleDesc.Count = 1;
    dd.Usage = D3D11_USAGE_DEFAULT;
    dd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    if (FAILED(g_device->CreateTexture2D(&dd, nullptr, &g_depth_tex))) {
        return false;
    }
    if (FAILED(g_device->CreateDepthStencilView(g_depth_tex.Get(), nullptr,
                                              &g_dsv))) {
        return false;
    }
    return true;
}

} // namespace

bool native_d3d11_attach(void* hwnd_ptr, int width, int height) {
    if (!hwnd_ptr || width <= 0 || height <= 0) return false;
    native_d3d11_detach();

    HWND hwnd = static_cast<HWND>(hwnd_ptr);
    g_hwnd = hwnd;

    const D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_0,
                                        D3D_FEATURE_LEVEL_10_1,
                                        D3D_FEATURE_LEVEL_10_0};
    D3D_FEATURE_LEVEL got = D3D_FEATURE_LEVEL_11_0;
    UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                                 flags, levels, (UINT)std::size(levels),
                                 D3D11_SDK_VERSION, &g_device, &got,
                                 &g_ctx))) {
        // Fall back to WARP if no hardware device is available.
        if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr,
                                     flags, levels, (UINT)std::size(levels),
                                     D3D11_SDK_VERSION, &g_device, &got,
                                     &g_ctx))) {
            return false;
        }
    }
    ComPtr<IDXGIDevice> dxgi_dev;
    ComPtr<IDXGIAdapter> adapter;
    ComPtr<IDXGIFactory2> factory;
    if (FAILED(g_device->QueryInterface(IID_PPV_ARGS(&dxgi_dev)))) return false;
    if (FAILED(dxgi_dev->GetAdapter(&adapter))) return false;
    if (FAILED(adapter->GetParent(IID_PPV_ARGS(&factory)))) return false;

    DXGI_SWAP_CHAIN_DESC1 sd{};
    sd.Width = (UINT)width;
    sd.Height = (UINT)height;
    sd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.SampleDesc.Count = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 2;
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    sd.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

    ComPtr<IDXGISwapChain1> swap;
    if (FAILED(factory->CreateSwapChainForHwnd(g_device.Get(), hwnd, &sd,
                                             nullptr, nullptr, &swap))) {
        return false;
    }
    // Keep DXGI out of window management entirely: NO_ALT_ENTER suppresses
    // alt-enter fullscreen, NO_WINDOW_CHANGES stops DXGI from moving or
    // resizing the HWND itself on display-mode changes (which would desync
    // the window, swapchain, and input coordinate spaces).
    factory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER |
                                          DXGI_MWA_NO_WINDOW_CHANGES);
    g_swap = swap;

    g_w = width;
    g_h = height;
    if (!create_views()) { native_d3d11_detach(); return false; }
    return true;
}

void native_d3d11_detach() {
    g_hwnd = nullptr;
    g_dsv.Reset();
    g_depth_tex.Reset();
    g_rtv.Reset();
    g_swap.Reset();
    g_ctx.Reset();
    g_device.Reset();
    g_w = g_h = 0;
}

bool native_d3d11_attached() { return g_swap != nullptr; }
void* native_d3d11_device() { return g_device.Get(); }
void* native_d3d11_device_context() { return g_ctx.Get(); }
void* native_d3d11_rtv() { return g_rtv.Get(); }
void* native_d3d11_dsv() { return g_dsv.Get(); }
int native_d3d11_width() { return g_w; }
int native_d3d11_height() { return g_h; }

bool native_d3d11_resize(int width, int height) {
    if (!g_swap || width <= 0 || height <= 0) return false;
    // The immediate context holds references to our views via the output
    // merger binding, which in turn keeps the back-buffer texture alive.
    // ResizeBuffers fails with DXGI_ERROR_INVALID_CALL unless every
    // reference is dropped first: unbind all state, release the views,
    // then flush so the GPU finishes in-flight work.
    if (g_ctx) {
        g_ctx->ClearState();
        g_ctx->Flush();
    }
    g_dsv.Reset();
    g_depth_tex.Reset();
    g_rtv.Reset();
    HRESULT hr = g_swap->ResizeBuffers(0, (UINT)width, (UINT)height,
                                       DXGI_FORMAT_UNKNOWN, 0);
    if (FAILED(hr)) {
        std::fprintf(stderr,
            "[native_d3d11] ResizeBuffers(%dx%d) failed: hr=0x%08lX %s\n",
            width, height, (unsigned long)hr,
            hr == DXGI_ERROR_DEVICE_REMOVED ? "DEVICE_REMOVED" :
            hr == DXGI_ERROR_DEVICE_RESET ? "DEVICE_RESET" :
            hr == DXGI_ERROR_INVALID_CALL ? "INVALID_CALL" :
            hr == E_INVALIDARG ? "INVALID_ARG" : "other");
        // Buffers were not resized; rebuild the old-size views so the
        // swapchain stays presentable instead of being left view-less.
        create_views();
        return false;
    }
    g_w = width;
    g_h = height;
    return create_views();
}

void native_d3d11_present() {
    if (!g_swap) return;
    HRESULT hr = g_swap->Present(1, 0);
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
        std::fprintf(stderr,
            "[native_d3d11] Present failed: hr=0x%08lX %s\n",
            (unsigned long)hr,
            hr == DXGI_ERROR_DEVICE_REMOVED ? "DEVICE_REMOVED" : "DEVICE_RESET");
    }
}

} // namespace LM::Runtime

#else

namespace LM::Runtime {
bool native_d3d11_attach(void*, int, int) { return false; }
void native_d3d11_detach() {}
bool native_d3d11_attached() { return false; }
void* native_d3d11_device() { return nullptr; }
void* native_d3d11_device_context() { return nullptr; }
void* native_d3d11_rtv() { return nullptr; }
void* native_d3d11_dsv() { return nullptr; }
int native_d3d11_width() { return 0; }
int native_d3d11_height() { return 0; }
bool native_d3d11_resize(int, int) { return false; }
void native_d3d11_present() {}
}

#endif

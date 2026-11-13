#pragma once

// Canonical layout of the 3D vertex-stream uniform blob (179 floats).
//
// This header is the SINGLE SOURCE OF TRUTH for the C++ side: both the
// Sokol/D3D11 backend (sokol_gfx_runtime.cpp) and the software rasterizer
// (software_graphics.hh) read these indices, and the HLSL shaders are
// generated with #define blocks built from these same constants.
//
// The Lymar producer side mirrors these values as pub const in
// std/d3/uniforms.lm — keep the two files in sync (the blob is the ABI
// between std.d3.renderer and the native backends).
//
// Element j of the blob is u_data[j>>2][j&3] inside the 48-float4 cbuffer.

namespace gfx_uniform {

// ---- header fields (float indices into the blob) -------------------------
inline constexpr int kMvpOffset        = 0;    // 16 floats: model-view-projection
inline constexpr int kWorldOffset      = 16;   // 16 floats: world matrix (normals use upper 3x3)
inline constexpr int kColorOffset      = 32;   // material color rgba (4)
inline constexpr int kAmbientOffset    = 36;   // illumination base rgb (3)
inline constexpr int kMaterialOffset   = 39;   // diffuse, specular, shininess (3)
inline constexpr int kShadingOffset    = 42;   // shading model int
inline constexpr int kCullOffset       = 43;   // cull mode int
inline constexpr int kWireWidthOffset  = 44;   // wireframe thickness px
inline constexpr int kHasNormalsOffset = 45;   // 1.0 when vertex normals present
inline constexpr int kViewportOffset   = 46;   // x, y, w, h (4)
inline constexpr int kLightCountOffset = 50;   // number of active lights

// ---- light records --------------------------------------------------------
inline constexpr int kMaxLights        = 16;
inline constexpr int kLightBase        = 51;   // first light record
inline constexpr int kLightStride      = 8;    // floats per light
// per-light fields (added to record base):
inline constexpr int kLightTypeOffset  = 0;    // 0 ambient, 1 directional, 2 point
inline constexpr int kLightPosOffset   = 1;    // position (point) or direction xyz
inline constexpr int kLightDirOffset   = 1;
inline constexpr int kLightColorOffset = 4;    // rgb
inline constexpr int kLightIntOffset   = 7;    // intensity

// ---- sizes ----------------------------------------------------------------
inline constexpr int kTexFlagOffset = kLightBase + kMaxLights * kLightStride; // 179: 1.0 = sample bound texture
inline constexpr int kBlobFloats = kTexFlagOffset + 1; // 180
inline constexpr int kCBufferFloat4s = 48;  // 192 floats of cbuffer capacity

// ---- shading model values (must match std/d3/types.lm ShadingModel) --------
inline constexpr int kShadingFlat             = 0;
inline constexpr int kShadingSmooth           = 1;
inline constexpr int kShadingUnlit            = 2;
inline constexpr int kShadingWireframe        = 3;
inline constexpr int kShadingNormalVisualizer = 4;

// ---- cull mode values (must match std/d3/types.lm CullMode) ---------------
inline constexpr int kCullNone  = 0;
inline constexpr int kCullBack  = 1;
inline constexpr int kCullFront = 2;

// ---- light type values (must match std/d3/types.lm LightType) -------------
inline constexpr int kLightAmbient     = 0;
inline constexpr int kLightDirectional = 1;
inline constexpr int kLightPoint       = 2;

} // namespace gfx_uniform

# API Documentation: `uniforms.lm`

## Overview

std/d3/uniforms.lm
Canonical indices of the 3D vertex-stream uniform blob (180 floats).

This is the PRODUCER side of the ABI shared with the native backends.
The C++ consumers read the same layout from src/runtime/gfx_uniform_layout.hh
(single source of truth on that side; the Sokol HLSL shaders are generated
from it). Keep the two files in sync — element j of the blob is
u_data[j>>2][j&3] inside the 48-float4 cbuffer.

Blob layout (all floats):
  [0..15]    MVP matrix (row-major)
  [16..31]   world matrix (upper 3x3 transforms normals)
  [32..35]   material color rgba
  [36..38]   illumination base rgb (material ambient + scene ambient)
  [39..41]   diffuse, specular, shininess
  [42]       shading model, [43] cull mode, [44] wireframe thickness px,
  [45]       has_normals flag, [46..49] viewport x/y/w/h
  [50]       light count, then per light 8 floats starting at 51
  [179]      has_texture flag (1.0 = sample the texture bound with the draw)


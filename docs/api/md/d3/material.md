# API Documentation: `material.lm`

## Overview

std/d3/material.lm
Surface material definition defining coloration, illumination response, and shading models.

## Symbols

- **Frame**: [`Material`](#Material)
- **Function**: [`basic_material`](#basic_material)
- **Function**: [`lambert_material`](#lambert_material)
- **Function**: [`phong_material`](#phong_material)
- **Function**: [`pbr_material`](#pbr_material)
- **Function**: [`wireframe_material`](#wireframe_material)

---

### `Material` <a id="Material"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Material
```

#### Members

- `var pub color_r: float` *(field)*
- `var pub color_g: float` *(field)*
- `var pub color_b: float` *(field)*
- `var pub color_a: float` *(field)*
- `var pub ambient: float` *(field)*
- `var pub diffuse: float` *(field)*
- `var pub specular: float` *(field)*
- `var pub shininess: float` *(field)*
- `var pub roughness: float` *(field)*
- `var pub metallic: float` *(field)*
- `var pub wireframe: bool` *(field)*
- `var pub wireframe_thickness: float` *(field)*
- `var pub shading: types.ShadingModel` *(field)*
- `var pub cull_mode: types.CullMode` *(field)*
- `var pub base_color_texture: str` *(field)*
- `var pub texture_state: int` *(field)*
- `var pub texture_id: int` *(field)*
- `var pub normal_map: str` *(field)*
- `var pub metallic_roughness_map: str` *(field)*
- `var pub occlusion_map: str` *(field)*
- `var pub emissive_map: str` *(field)*
- `var pub emissive_r: float` *(field)*
- `var pub emissive_g: float` *(field)*
- `var pub emissive_b: float` *(field)*
- `var pub ao: float` *(field)*
- `var pub alpha_cutoff: float` *(field)*
- `var pub double_sided: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_color(r: float, g: float, b: float)` *(method)*

---

### `basic_material` <a id="basic_material"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn basic_material(r: float = ..., g: float = ..., b: float = ..., a: float = ...): Material
```

Creates a flat unlit material unaffected by scene lighting.

---

### `lambert_material` <a id="lambert_material"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lambert_material(r: float = ..., g: float = ..., b: float = ...): Material
```

Creates a matte diffuse-illuminated material (Lambertian reflection).

---

### `phong_material` <a id="phong_material"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn phong_material(r: float = ..., g: float = ..., b: float = ..., shininess: float = ...): Material
```

Creates a glossy material with Blinn-Phong specular highlights.

---

### `pbr_material` <a id="pbr_material"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pbr_material(r: float = ..., g: float = ..., b: float = ..., metallic: float = ..., roughness: float = ...): Material
```

Creates a PBR-lite material carrying metallic/roughness and optional
texture-map bindings for the GPU pipeline.

---

### `wireframe_material` <a id="wireframe_material"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn wireframe_material(r: float = ..., g: float = ..., b: float = ..., thickness: float = ...): Material
```

Creates a wireframe outline material.

---


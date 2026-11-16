# API Documentation: `environment.lm`

## Overview

std/d3/environment.lm
Procedural environment, terrain, and celestial body generators for Lymar 3D (std.d3).

## Symbols

- **Function**: [`hash_2d`](#hash_2d)
- **Function**: [`value_noise_2d`](#value_noise_2d)
- **Function**: [`fractal_elevation`](#fractal_elevation)
- **Function**: [`hash_3d`](#hash_3d)
- **Function**: [`terrain`](#terrain)
- **Function**: [`asteroid`](#asteroid)
- **Function**: [`icosphere`](#icosphere)

---

### `hash_2d` <a id="hash_2d"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn hash_2d(ix: int, iz: int, seed: int): float
```

Deterministic 2D spatial hash returning values in [-1.0, 1.0].

---

### `value_noise_2d` <a id="value_noise_2d"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn value_noise_2d(x: float, z: float, seed: int): float
```

Smooth continuous 2D value noise with cubic Hermite interpolation.

---

### `fractal_elevation` <a id="fractal_elevation"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn fractal_elevation(x: float, z: float, seed: int): float
```

Multi-octave fractal Brownian motion (fBm) elevation generator.

---

### `hash_3d` <a id="hash_3d"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn hash_3d(ix: int, iy: int, iz: int, seed: int): float
```

Deterministic 3D spatial hash returning values in [-1.0, 1.0].

---

### `terrain` <a id="terrain"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn terrain(width: float = ..., depth: float = ..., cols: int = ..., rows: int = ..., height_scale: float = ..., seed: int = ...): geom.Geometry
```

Generates a continuous 3D heightmap terrain grid with mountains, valleys, and smooth normals.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `width` | Total physical width along the X axis. |
| `depth` | Total physical depth along the Z axis. |
| `cols` | Number of horizontal grid subdivisions. |
| `rows` | Number of depth grid subdivisions. |
| `height_scale` | Vertical elevation multiplier. |
| `seed` | Random seed for the procedural terrain generation. |

---

### `asteroid` <a id="asteroid"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn asteroid(radius: float = ..., roughness: float = ..., segments_w: int = ..., segments_h: int = ..., seed: int = ...): geom.Geometry
```

Generates an irregular, cratered celestial asteroid using radial 3D noise displacement.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `radius` | Base spherical radius of the asteroid. |
| `roughness` | Maximum radial displacement ratio (default 0.35). |
| `segments_w` | Horizontal longitude segments (default 12). |
| `segments_h` | Vertical latitude segments (default 8). |
| `seed` | Random seed controlling crater distribution. |

---

### `icosphere` <a id="icosphere"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn icosphere(radius: float = ..., subdivisions: int = ...): geom.Geometry
```

Generates a geodesic icosahedron sphere (icosphere) with uniform triangle distribution.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `radius` | Target radius of the icosphere. |
| `subdivisions` | Number of recursive edge subdivisions (0 = 20 faces, 1 = 80 faces, 2 = 320 faces). |

---


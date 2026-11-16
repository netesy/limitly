# API Documentation: `sculpt.lm`

## Overview

std/d3/sculpt.lm
Procedural sculpting and cross-section modeling engine for Lymar 3D graphics (std.d3).
Provides profile extrusions, lathe/revolve operations, multi-station lofts, and symmetry mirroring.

## Symbols

- **Function**: [`extrude`](#extrude)
- **Function**: [`revolve`](#revolve)
- **Function**: [`loft`](#loft)
- **Function**: [`mirror_compound`](#mirror_compound)

---

### `extrude` <a id="extrude"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn extrude(profile: list, depth: float = ..., taper: float = ..., twist: float = ...): geom.Geometry
```

Extrudes a 2D profile polygon along the Z axis with optional taper scale and twist rotation.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `profile` | Flat list of 2D coordinates [x0, y0, x1, y1, ...] forming a closed polygon. |
| `depth` | Extrusion length along the -Z direction. |
| `taper` | Scale multiplier applied to the back cap (default 1.0). |
| `twist` | Rotation angle in radians applied to the back cap (default 0.0). |

---

### `revolve` <a id="revolve"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn revolve(profile: list, segments: int = ..., sweep_angle: float = ...): geom.Geometry
```

Revolves a 2D profile silhouette [radius, y] around the Y axis into a rotational 3D mesh.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `profile` | Flat list of (r, y) coordinates [r0, y0, r1, y1, ...] representing half-silhouette. |
| `segments` | Number of radial slices around 360 degrees (default 16). |
| `sweep_angle` | Total revolution angle in radians (default 2*PI). |

---

### `loft` <a id="loft"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn loft(sections: list, z_positions: list, cap_start: bool = ..., cap_end: bool = ...): geom.Geometry
```

Skins a 3D geometry across multiple 2D cross-sections positioned along the Z axis.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `sections` | List of 2D profile coordinates, all having the exact same point count N. |
| `z_positions` | Array of Z positions for each respective cross section. |
| `cap_start` | Whether to generate a cap on the first cross-section. |
| `cap_end` | Whether to generate a cap on the last cross-section. |

---

### `mirror_compound` <a id="mirror_compound"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mirror_compound(half_geom: geom.Geometry, axis: int = ...): geom.Geometry
```

Takes a half-model geometry, mirrors it across the chosen axis, and merges both into a single watertight mesh.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `half_geom` | The source half-model (e.g. left side of a spaceship or character). |
| `axis` | 0 = X axis (bilateral symmetry), 1 = Y axis, 2 = Z axis. |

---


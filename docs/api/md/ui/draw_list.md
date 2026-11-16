# API Documentation: `draw_list.lm`

## Overview

std/ui/draw_list.lm
Flat, ordered GPU draw command list with zero-allocation buffer reuse.
Emitted by widgets during tree.update's paint pass; replayed by
replay.lm without recursion. Hit-testing lives in std.ui.tree — this
module carries draw commands only.

## Symbols

- **Frame**: [`DrawCmd`](#DrawCmd)
- **Function**: [`dcmd_rect`](#dcmd_rect)
- **Function**: [`dcmd_rect_rounded`](#dcmd_rect_rounded)
- **Function**: [`dcmd_border_rounded`](#dcmd_border_rounded)
- **Function**: [`dcmd_text`](#dcmd_text)
- **Function**: [`dcmd_line`](#dcmd_line)
- **Function**: [`dcmd_triangle`](#dcmd_triangle)
- **Function**: [`dcmd_clip_push`](#dcmd_clip_push)
- **Function**: [`dcmd_shadow`](#dcmd_shadow)
- **Function**: [`dcmd_clip_pop`](#dcmd_clip_pop)
- **Frame**: [`DrawList`](#DrawList)
- **Function**: [`draw_list`](#draw_list)
- **Function**: [`dl_alloc_cmd`](#dl_alloc_cmd)
- **Function**: [`dl_alloc_overlay_cmd`](#dl_alloc_overlay_cmd)
- **Function**: [`dl_emit_rect`](#dl_emit_rect)
- **Function**: [`dl_emit_rect_rounded`](#dl_emit_rect_rounded)
- **Function**: [`dl_emit_rect_border`](#dl_emit_rect_border)
- **Function**: [`dl_emit_shadow`](#dl_emit_shadow)
- **Function**: [`dl_emit_text`](#dl_emit_text)
- **Function**: [`dl_add`](#dl_add)
- **Function**: [`dl_add_overlay_cmd`](#dl_add_overlay_cmd)
- **Function**: [`dl_flush_overlays`](#dl_flush_overlays)
- **Function**: [`dl_clear`](#dl_clear)
- **Function**: [`dl_clip_balance`](#dl_clip_balance)
- **Frame**: [`PaintContext`](#PaintContext)
- **Function**: [`dl_push_clip`](#dl_push_clip)
- **Function**: [`dl_pop_clip`](#dl_pop_clip)

---

### `DrawCmd` <a id="DrawCmd"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame DrawCmd
```

── DrawCmd ───────────────────────────────────────────────────────────────────
A single GPU-ready draw instruction. Approx 80 bytes vs Widget's ~400 bytes.

#### Members

- `var pub kind: DrawCmdKind` *(field)*
- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub w: float` *(field)*
- `var pub h: float` *(field)*
- `var pub r: float` *(field)*
- `var pub g: float` *(field)*
- `var pub b: float` *(field)*
- `var pub a: float` *(field)*
- `var pub radius: float` *(field)*
- `var pub border_width: float` *(field)*
- `var pub text: str` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub x2: float` *(field)*
- `var pub y2: float` *(field)*
- `var pub x3: float` *(field)*
- `var pub y3: float` *(field)*
- `var pub clip_shape: int` *(field)*
- `pub init()` *(constructor)*

---

### `dcmd_rect` <a id="dcmd_rect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dcmd_rect(x: float, y: float, w: float, h: float, r: float, g: float, b: float, a: float): DrawCmd
```

---

### `dcmd_rect_rounded` <a id="dcmd_rect_rounded"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dcmd_rect_rounded(x: float, y: float, w: float, h: float, radius: float, r: float, g: float, b: float, a: float): DrawCmd
```

---

### `dcmd_border_rounded` <a id="dcmd_border_rounded"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dcmd_border_rounded(x: float, y: float, w: float, h: float, radius: float, border_width: float, r: float, g: float, b: float, a: float): DrawCmd
```

---

### `dcmd_text` <a id="dcmd_text"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dcmd_text(text: str, x: float, y: float, r: float, g: float, b: float, a: float, font_scale: float): DrawCmd
```

---

### `dcmd_line` <a id="dcmd_line"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dcmd_line(x1: float, y1: float, x2: float, y2: float, r: float, g: float, b: float, a: float): DrawCmd
```

---

### `dcmd_triangle` <a id="dcmd_triangle"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dcmd_triangle(x1: float, y1: float, x2: float, y2: float, x3: float, y3: float, r: float, g: float, b: float, a: float): DrawCmd
```

---

### `dcmd_clip_push` <a id="dcmd_clip_push"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dcmd_clip_push(x: float, y: float, w: float, h: float, shape: int = ..., radius: float = ...): DrawCmd
```

---

### `dcmd_shadow` <a id="dcmd_shadow"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dcmd_shadow(x: float, y: float, w: float, h: float, r: float, g: float, b: float, a: float, off_x: float, off_y: float, blur: float, spread: float, radius: float = ...): DrawCmd
```

Soft drop shadow: x2=off_x, y2=off_y, x3=blur, y3=spread (reuses the
line/triangle coordinate fields — Shadow never draws geometry).

---

### `dcmd_clip_pop` <a id="dcmd_clip_pop"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dcmd_clip_pop(): DrawCmd
```

---

### `DrawList` <a id="DrawList"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame DrawList
```

── DrawList ──────────────────────────────────────────────────────────────────
Keeps backing lists and pre-allocated DrawCmd slots across rebuilds
so `clear()` resets cursor counts in O(1) with zero per-frame allocations.

#### Members

- `var pub cmds: list` *(field)*
- `var pub overlay_cmds: list` *(field)*
- `var pub cmd_count: int` *(field)*
- `var pub overlay_cmd_count: int` *(field)*
- `var pub is_valid: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn clear(): nil` *(method)*

---

### `draw_list` <a id="draw_list"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_list(): DrawList
```

---

### `dl_alloc_cmd` <a id="dl_alloc_cmd"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_alloc_cmd(dl: DrawList): DrawCmd
```

---

### `dl_alloc_overlay_cmd` <a id="dl_alloc_overlay_cmd"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_alloc_overlay_cmd(dl: DrawList): DrawCmd
```

---

### `dl_emit_rect` <a id="dl_emit_rect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_emit_rect(dl: DrawList, x: float, y: float, w: float, h: float, r: float, g: float, b: float, a: float = ...): nil
```

---

### `dl_emit_rect_rounded` <a id="dl_emit_rect_rounded"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_emit_rect_rounded(dl: DrawList, x: float, y: float, w: float, h: float, rad: float, r: float, g: float, b: float, a: float = ...): nil
```

---

### `dl_emit_rect_border` <a id="dl_emit_rect_border"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_emit_rect_border(dl: DrawList, x: float, y: float, w: float, h: float, rad: float, bw: float, r: float, g: float, b: float, a: float = ...): nil
```

---

### `dl_emit_shadow` <a id="dl_emit_shadow"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_emit_shadow(dl: DrawList, x: float, y: float, w: float, h: float, r: float, g: float, b: float, a: float, off_x: float, off_y: float, blur: float, spread: float, radius: float = ...): nil
```

---

### `dl_emit_text` <a id="dl_emit_text"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_emit_text(dl: DrawList, txt: str, x: float, y: float, r: float, g: float, b: float, a: float = ..., scale: float = ...): nil
```

---

### `dl_add` <a id="dl_add"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_add(dl: DrawList, cmd: DrawCmd): nil
```

---

### `dl_add_overlay_cmd` <a id="dl_add_overlay_cmd"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_add_overlay_cmd(dl: DrawList, cmd: DrawCmd): nil
```

---

### `dl_flush_overlays` <a id="dl_flush_overlays"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_flush_overlays(dl: DrawList): nil
```

---

### `dl_clear` <a id="dl_clear"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_clear(dl: DrawList): nil
```

---

### `dl_clip_balance` <a id="dl_clip_balance"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_clip_balance(d: DrawList): int
```

M5 batching audit: clip push/pop must balance over the emitted command
stream or the GPU clip stack leaks state into the next frame. Returns
the net balance — 0 means every ClipPush was matched by a ClipPop.

---

### `PaintContext` <a id="PaintContext"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame PaintContext
```

#### Members

- `var pub dl: DrawList` *(field)*
- `pub init()` *(constructor)*

---

### `dl_push_clip` <a id="dl_push_clip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_push_clip(d: DrawList, x: float, y: float, w: float, h: float): nil
```

---

### `dl_pop_clip` <a id="dl_pop_clip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_pop_clip(d: DrawList): nil
```

---


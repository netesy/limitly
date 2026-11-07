# API Documentation: `draw_list.lm`

## Overview

std/ui/draw_list.lm
Flat, ordered GPU draw command list.
Replaces the recursive Widget tree as the engine's internal representation.
Emitted by builder.lm in a single pass; replayed by replay.lm without recursion.

## Symbols

- **Frame**: [`DrawCmd`](#DrawCmd)
- **Function**: [`dcmd_rect`](#dcmd_rect)
- **Function**: [`dcmd_rect_rounded`](#dcmd_rect_rounded)
- **Function**: [`dcmd_text`](#dcmd_text)
- **Function**: [`dcmd_line`](#dcmd_line)
- **Function**: [`dcmd_clip_push`](#dcmd_clip_push)
- **Function**: [`dcmd_clip_pop`](#dcmd_clip_pop)
- **Frame**: [`HitZone`](#HitZone)
- **Function**: [`make_button_zone`](#make_button_zone)
- **Function**: [`make_slider_zone`](#make_slider_zone)
- **Function**: [`make_checkbox_zone`](#make_checkbox_zone)
- **Function**: [`make_input_zone`](#make_input_zone)
- **Frame**: [`DrawList`](#DrawList)
- **Function**: [`draw_list`](#draw_list)
- **Function**: [`dl_add`](#dl_add)
- **Function**: [`dl_add_hit`](#dl_add_hit)
- **Function**: [`dl_hit_test`](#dl_hit_test)
- **Function**: [`dl_clear`](#dl_clear)

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
- `var pub text: str` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub x2: float` *(field)*
- `var pub y2: float` *(field)*
- `var pub x3: float` *(field)*
- `var pub y3: float` *(field)*
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

### `dcmd_clip_push` <a id="dcmd_clip_push"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dcmd_clip_push(x: float, y: float, w: float, h: float): DrawCmd
```

---

### `dcmd_clip_pop` <a id="dcmd_clip_pop"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dcmd_clip_pop(): DrawCmd
```

---

### `HitZone` <a id="HitZone"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame HitZone
```

── HitZone ───────────────────────────────────────────────────────────────────
Parallel list to DrawCmd list — built simultaneously during build pass.
Hit tested as a simple linear scan — no recursion needed.

#### Members

- `var pub id: str` *(field)*
- `var pub kind: HitZoneKind` *(field)*
- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub w: float` *(field)*
- `var pub h: float` *(field)*
- `var pub clip_x: float` *(field)*
- `var pub clip_y: float` *(field)*
- `var pub clip_w: float` *(field)*
- `var pub clip_h: float` *(field)*
- `var pub on_click: any` *(field)*
- `var pub on_change: any` *(field)*
- `var pub slider_min: float` *(field)*
- `var pub slider_max: float` *(field)*
- `var pub slider_val: float` *(field)*
- `var pub tab_index: int` *(field)*
- `var pub is_checked: int` *(field)*
- `var pub widget: any` *(field)*
- `pub init()` *(constructor)*

---

### `make_button_zone` <a id="make_button_zone"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_button_zone(id: str, x: float, y: float, w: float, h: float, on_click, widget = ...): HitZone
```

---

### `make_slider_zone` <a id="make_slider_zone"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_slider_zone(id: str, x: float, y: float, w: float, h: float, min_v: float, max_v: float, cur_v: float, on_change, widget = ...): HitZone
```

---

### `make_checkbox_zone` <a id="make_checkbox_zone"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_checkbox_zone(id: str, x: float, y: float, w: float, h: float, checked: int, on_change, widget = ...): HitZone
```

---

### `make_input_zone` <a id="make_input_zone"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_input_zone(id: str, x: float, y: float, w: float, h: float, widget: any = ...): HitZone
```

---

### `DrawList` <a id="DrawList"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame DrawList
```

── DrawList ──────────────────────────────────────────────────────────────────

#### Members

- `var pub cmds: list` *(field)*
- `var pub hits: list` *(field)*
- `var pub is_valid: int` *(field)*
- `pub init()` *(constructor)*

---

### `draw_list` <a id="draw_list"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn draw_list(): DrawList
```

---

### `dl_add` <a id="dl_add"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_add(dl: DrawList, cmd: DrawCmd): nil
```

---

### `dl_add_hit` <a id="dl_add_hit"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_add_hit(dl: DrawList, hz: HitZone): nil
```

---

### `dl_hit_test` <a id="dl_hit_test"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_hit_test(dl: DrawList, px: float, py: float): HitZone
```

Hit test: returns the topmost HitZone under (px, py), or nil.
O(n) linear scan — no recursion.

---

### `dl_clear` <a id="dl_clear"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dl_clear(dl: DrawList): nil
```

---


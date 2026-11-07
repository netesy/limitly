# API Documentation: `builder.lm`

## Overview

std/ui/builder.lm
Single-pass hybrid builder: walks Widget tree ONCE, emits DrawList + HitZones.

Retained mode in syntax and developer ergonomics, but immediate mode in execution:
  - Walks the composable Widget tree in a single linear pass
  - Emits flat DrawCmds and HitZones directly into a DrawList
  - The DrawList is cached and replayed by replay.lm each frame at zero cost
  - Interactive events hit-test against the flat HitZone list in O(n) time

## Symbols

- **Frame**: [`ThemeSnap`](#ThemeSnap)
- **Function**: [`default_theme_snap`](#default_theme_snap)
- **Function**: [`snap_theme`](#snap_theme)
- **Frame**: [`LayoutCtx`](#LayoutCtx)
- **Function**: [`_add_hit`](#_add_hit)
- **Function**: [`_draw_border`](#_draw_border)
- **Function**: [`_draw_shadow`](#_draw_shadow)
- **Function**: [`_draw_checkmark`](#_draw_checkmark)
- **Function**: [`_draw_chevron_down`](#_draw_chevron_down)
- **Function**: [`_draw_chevron_up`](#_draw_chevron_up)
- **Function**: [`_draw_chevron_right`](#_draw_chevron_right)
- **Function**: [`build`](#build)
- **Function**: [`_emit`](#_emit)
- **Function**: [`_emit_text`](#_emit_text)
- **Function**: [`_emit_button`](#_emit_button)
- **Function**: [`_get_natural_width`](#_get_natural_width)
- **Function**: [`_emit_container`](#_emit_container)
- **Function**: [`_emit_slider`](#_emit_slider)
- **Function**: [`_emit_checkbox`](#_emit_checkbox)
- **Function**: [`_emit_input`](#_emit_input)
- **Function**: [`_emit_progress`](#_emit_progress)
- **Function**: [`_emit_toggle`](#_emit_toggle)
- **Function**: [`_emit_badge`](#_emit_badge)
- **Function**: [`_emit_card`](#_emit_card)
- **Function**: [`_emit_alert`](#_emit_alert)
- **Function**: [`_emit_scroll`](#_emit_scroll)
- **Function**: [`_emit_tabs`](#_emit_tabs)
- **Function**: [`_emit_select`](#_emit_select)
- **Function**: [`_emit_textarea`](#_emit_textarea)
- **Function**: [`_emit_multi_select`](#_emit_multi_select)
- **Function**: [`_emit_table`](#_emit_table)
- **Function**: [`_emit_accordion`](#_emit_accordion)
- **Function**: [`_emit_stat`](#_emit_stat)
- **Function**: [`_emit_indicator`](#_emit_indicator)
- **Function**: [`_emit_link`](#_emit_link)
- **Function**: [`_emit_stepper`](#_emit_stepper)
- **Function**: [`_emit_range_slider`](#_emit_range_slider)
- **Function**: [`_emit_color_picker`](#_emit_color_picker)
- **Function**: [`_emit_steps`](#_emit_steps)
- **Function**: [`_emit_timeline`](#_emit_timeline)
- **Function**: [`_emit_tree_node`](#_emit_tree_node)
- **Function**: [`_emit_form_field`](#_emit_form_field)
- **Function**: [`_emit_diff`](#_emit_diff)
- **Function**: [`_emit_file_input`](#_emit_file_input)
- **Function**: [`_emit_filter`](#_emit_filter)
- **Function**: [`_emit_calendar`](#_emit_calendar)
- **Function**: [`_emit_bar_chart`](#_emit_bar_chart)
- **Function**: [`_emit_line_chart`](#_emit_line_chart)
- **Function**: [`_emit_pie_chart`](#_emit_pie_chart)
- **Function**: [`_emit_histogram`](#_emit_histogram)

---

### `ThemeSnap` <a id="ThemeSnap"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ThemeSnap
```

── Theme snapshot ────────────────────────────────────────────────────────────
Flat color values extracted once per build — avoids repeated field access

#### Members

- `var pub text_r: float` *(field)*
- `var pub text_g: float` *(field)*
- `var pub text_b: float` *(field)*
- `var pub text2_r: float` *(field)*
- `var pub text2_g: float` *(field)*
- `var pub text2_b: float` *(field)*
- `var pub bg_r: float` *(field)*
- `var pub bg_g: float` *(field)*
- `var pub bg_b: float` *(field)*
- `var pub surface_r: float` *(field)*
- `var pub surface_g: float` *(field)*
- `var pub surface_b: float` *(field)*
- `var pub accent_r: float` *(field)*
- `var pub accent_g: float` *(field)*
- `var pub accent_b: float` *(field)*
- `var pub border_r: float` *(field)*
- `var pub border_g: float` *(field)*
- `var pub border_b: float` *(field)*
- `var pub btn_r: float` *(field)*
- `var pub btn_g: float` *(field)*
- `var pub btn_b: float` *(field)*
- `var pub btn_hover_r: float` *(field)*
- `var pub btn_hover_g: float` *(field)*
- `var pub btn_hover_b: float` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub spacing: float` *(field)*
- `var pub corner_radius: float` *(field)*

---

### `default_theme_snap` <a id="default_theme_snap"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn default_theme_snap(): ThemeSnap
```

---

### `snap_theme` <a id="snap_theme"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn snap_theme(pal: theme.ColorPalette, font_scale: float): ThemeSnap
```

---

### `LayoutCtx` <a id="LayoutCtx"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame LayoutCtx
```

── Layout context (stack-based, no heap alloc) ───────────────────────────────

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub avail_w: float` *(field)*
- `var pub avail_h: float` *(field)*
- `var pub spacing: float` *(field)*
- `var pub clip_x: float` *(field)*
- `var pub clip_y: float` *(field)*
- `var pub clip_w: float` *(field)*
- `var pub clip_h: float` *(field)*

---

### `_add_hit` <a id="_add_hit"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _add_hit(dl: dlist.DrawList, hz: dlist.HitZone, ctx: LayoutCtx): nil
```

---

### `_draw_border` <a id="_draw_border"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _draw_border(dl: dlist.DrawList, x: float, y: float, w: float, h: float, r: float, g: float, b: float, a: float = ...): nil
```

── Drawing & Styling Helpers ─────────────────────────────────────────────────

---

### `_draw_shadow` <a id="_draw_shadow"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _draw_shadow(dl: dlist.DrawList, x: float, y: float, w: float, h: float, rad: float = ...): nil
```

---

### `_draw_checkmark` <a id="_draw_checkmark"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _draw_checkmark(dl: dlist.DrawList, cx: float, cy: float, cr: float, cg: float, cb: float): nil
```

---

### `_draw_chevron_down` <a id="_draw_chevron_down"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _draw_chevron_down(dl: dlist.DrawList, cx: float, cy: float, cr: float, cg: float, cb: float): nil
```

---

### `_draw_chevron_up` <a id="_draw_chevron_up"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _draw_chevron_up(dl: dlist.DrawList, cx: float, cy: float, cr: float, cg: float, cb: float): nil
```

---

### `_draw_chevron_right` <a id="_draw_chevron_right"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _draw_chevron_right(dl: dlist.DrawList, cx: float, cy: float, cr: float, cg: float, cb: float): nil
```

---

### `build` <a id="build"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn build(root: ui.Widget, vw: float, vh: float, ts: any = ..., x: float = ..., y: float = ...): dlist.DrawList
```

── Main build entry point ────────────────────────────────────────────────────
Walks root Widget once and emits a fully-populated DrawList.

---

### `_emit` <a id="_emit"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Widget emitter ────────────────────────────────────────────────────────────
Returns height consumed. Adds DrawCmds and HitZones to dl in place.

---

### `_emit_text` <a id="_emit_text"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_text(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Text ──────────────────────────────────────────────────────────────────────

---

### `_emit_button` <a id="_emit_button"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_button(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Button ────────────────────────────────────────────────────────────────────

---

### `_get_natural_width` <a id="_get_natural_width"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _get_natural_width(child: ui.Widget): float
```

── Natural Sizing Resolver for Layout ────────────────────────────────────────

---

### `_emit_container` <a id="_emit_container"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_container(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Container (Column / Row / Stack) ──────────────────────────────────────────

---

### `_emit_slider` <a id="_emit_slider"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_slider(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Slider ────────────────────────────────────────────────────────────────────

---

### `_emit_checkbox` <a id="_emit_checkbox"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_checkbox(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Checkbox ──────────────────────────────────────────────────────────────────

---

### `_emit_input` <a id="_emit_input"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_input(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Input ─────────────────────────────────────────────────────────────────────

---

### `_emit_progress` <a id="_emit_progress"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_progress(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Progress ──────────────────────────────────────────────────────────────────

---

### `_emit_toggle` <a id="_emit_toggle"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_toggle(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Toggle ────────────────────────────────────────────────────────────────────

---

### `_emit_badge` <a id="_emit_badge"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_badge(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Badge ─────────────────────────────────────────────────────────────────────

---

### `_emit_card` <a id="_emit_card"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_card(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Card ──────────────────────────────────────────────────────────────────────

---

### `_emit_alert` <a id="_emit_alert"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_alert(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Alert / Toast ─────────────────────────────────────────────────────────────

---

### `_emit_scroll` <a id="_emit_scroll"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_scroll(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Scroll ────────────────────────────────────────────────────────────────────

---

### `_emit_tabs` <a id="_emit_tabs"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_tabs(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Tabs ──────────────────────────────────────────────────────────────────────

---

### `_emit_select` <a id="_emit_select"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_select(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Select ────────────────────────────────────────────────────────────────────

---

### `_emit_textarea` <a id="_emit_textarea"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_textarea(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Textarea ──────────────────────────────────────────────────────────────────

---

### `_emit_multi_select` <a id="_emit_multi_select"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_multi_select(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── MultiSelect ───────────────────────────────────────────────────────────────

---

### `_emit_table` <a id="_emit_table"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_table(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Table ─────────────────────────────────────────────────────────────────────

---

### `_emit_accordion` <a id="_emit_accordion"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_accordion(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Accordion ─────────────────────────────────────────────────────────────────

---

### `_emit_stat` <a id="_emit_stat"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_stat(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Stat ──────────────────────────────────────────────────────────────────────

---

### `_emit_indicator` <a id="_emit_indicator"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_indicator(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Indicator ─────────────────────────────────────────────────────────────────

---

### `_emit_link` <a id="_emit_link"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_link(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Link ──────────────────────────────────────────────────────────────────────

---

### `_emit_stepper` <a id="_emit_stepper"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_stepper(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Stepper ───────────────────────────────────────────────────────────────────

---

### `_emit_range_slider` <a id="_emit_range_slider"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_range_slider(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── RangeSlider ───────────────────────────────────────────────────────────────

---

### `_emit_color_picker` <a id="_emit_color_picker"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_color_picker(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── ColorPicker ───────────────────────────────────────────────────────────────

---

### `_emit_steps` <a id="_emit_steps"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_steps(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Steps ─────────────────────────────────────────────────────────────────────

---

### `_emit_timeline` <a id="_emit_timeline"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_timeline(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Timeline ──────────────────────────────────────────────────────────────────

---

### `_emit_tree_node` <a id="_emit_tree_node"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_tree_node(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── TreeNode ──────────────────────────────────────────────────────────────────

---

### `_emit_form_field` <a id="_emit_form_field"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_form_field(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── FormField ─────────────────────────────────────────────────────────────────

---

### `_emit_diff` <a id="_emit_diff"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_diff(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Diff ──────────────────────────────────────────────────────────────────────

---

### `_emit_file_input` <a id="_emit_file_input"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_file_input(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── FileInput ─────────────────────────────────────────────────────────────────

---

### `_emit_filter` <a id="_emit_filter"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_filter(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Filter ────────────────────────────────────────────────────────────────────

---

### `_emit_calendar` <a id="_emit_calendar"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_calendar(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Calendar ──────────────────────────────────────────────────────────────────

---

### `_emit_bar_chart` <a id="_emit_bar_chart"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_bar_chart(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── BarChart ──────────────────────────────────────────────────────────────────

---

### `_emit_line_chart` <a id="_emit_line_chart"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_line_chart(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── LineChart ─────────────────────────────────────────────────────────────────

---

### `_emit_pie_chart` <a id="_emit_pie_chart"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_pie_chart(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── PieChart ──────────────────────────────────────────────────────────────────

---

### `_emit_histogram` <a id="_emit_histogram"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _emit_histogram(dl: dlist.DrawList, w: ui.Widget, ctx: LayoutCtx, ts: ThemeSnap): float
```

── Histogram ─────────────────────────────────────────────────────────────────

---


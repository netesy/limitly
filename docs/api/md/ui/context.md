# API Documentation: `context.lm`

## Overview

UI Context Module
Retained UI Pipeline implementation with Dynamic Layout, Flexbox Spacers, Hit Testing, and Callback Dispatch

## Symbols

- **Frame**: [`UIContextState`](#UIContextState)
- **Function**: [`push_overlay`](#push_overlay)
- **Function**: [`clear_overlays`](#clear_overlays)
- **Function**: [`ui_init`](#ui_init)
- **Function**: [`_signal_dirty_cb`](#_signal_dirty_cb)
- **Function**: [`mark_element_dirty`](#mark_element_dirty)
- **Function**: [`set_viewport_size`](#set_viewport_size)
- **Function**: [`get_viewport_width`](#get_viewport_width)
- **Function**: [`get_viewport_height`](#get_viewport_height)
- **Function**: [`set_root`](#set_root)
- **Function**: [`update_blueprint`](#update_blueprint)
- **Function**: [`set_root_any`](#set_root_any)
- **Function**: [`codepoint_to_utf8`](#codepoint_to_utf8)
- **Function**: [`utf8_pop_back`](#utf8_pop_back)
- **Function**: [`get_char_width`](#get_char_width)
- **Function**: [`measure_widget_height`](#measure_widget_height)
- **Function**: [`measure_widget_width`](#measure_widget_width)
- **Function**: [`hit_test_and_click_blueprint`](#hit_test_and_click_blueprint)
- **Function**: [`hit_test_and_click_widget`](#hit_test_and_click_widget)
- **Function**: [`blur_focus_recursive`](#blur_focus_recursive)
- **Function**: [`dispatch_pointer_down`](#dispatch_pointer_down)
- **Function**: [`dispatch_pointer_click`](#dispatch_pointer_click)
- **Function**: [`dispatch_pointer_move`](#dispatch_pointer_move)
- **Function**: [`render_blueprint_node`](#render_blueprint_node)
- **Function**: [`draw_widget_focus_ring`](#draw_widget_focus_ring)
- **Function**: [`render_widget_node`](#render_widget_node)
- **Function**: [`update_animations_recursive`](#update_animations_recursive)
- **Function**: [`render_from_layout_boxes`](#render_from_layout_boxes)
- **Function**: [`frame_update`](#frame_update)
- **Function**: [`reset_pressed_recursive`](#reset_pressed_recursive)
- **Function**: [`update_hover_state_recursive`](#update_hover_state_recursive)
- **Function**: [`dispatch_pointer_up`](#dispatch_pointer_up)
- **Function**: [`send_char_to_widget`](#send_char_to_widget)
- **Function**: [`dispatch_char_input`](#dispatch_char_input)
- **Function**: [`send_key_down_to_widget`](#send_key_down_to_widget)
- **Function**: [`dispatch_key_down`](#dispatch_key_down)
- **Function**: [`send_wheel_to_widget`](#send_wheel_to_widget)
- **Function**: [`dispatch_mouse_wheel`](#dispatch_mouse_wheel)

---

### `UIContextState` <a id="UIContextState"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame UIContextState
```

#### Members

- `var pub is_initialized: int` *(field)*
- `var pub next_element_id: int` *(field)*
- `var pub root_element: int` *(field)*
- `var pub dirty: int` *(field)*
- `var pub current_blueprint: ui_types.Blueprint` *(field)*
- `var pub current_widget: ui.Widget` *(field)*
- `var pub focus_manager: focus.Manager` *(field)*
- `var pub modifiers: int` *(field)*
- `var pub get_clipboard_cb: function?` *(field)*
- `var pub set_clipboard_cb: function?` *(field)*
- `var pub has_widget: int` *(field)*
- `var pub viewport_w: float` *(field)*
- `var pub viewport_h: float` *(field)*
- `var pub captured_widget: ui.Widget` *(field)*
- `var pub has_captured: int` *(field)*
- `var pub captured_bounds_x: float` *(field)*
- `var pub captured_bounds_y: float` *(field)*
- `var pub captured_bounds_w: float` *(field)*
- `var pub captured_bounds_h: float` *(field)*
- `var pub last_pointer_x: float` *(field)*
- `var pub last_pointer_y: float` *(field)*
- `var pub is_pointer_down: int` *(field)*
- `var pub active_overlays: list` *(field)*
- `var pub cached_draw_list: any` *(field)*

---

### `push_overlay` <a id="push_overlay"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn push_overlay(w: ui.Widget): nil
```

---

### `clear_overlays` <a id="clear_overlays"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn clear_overlays(): nil
```

---

### `ui_init` <a id="ui_init"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ui_init(): int
```

---

### `_signal_dirty_cb` <a id="_signal_dirty_cb"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _signal_dirty_cb(): nil
```

---

### `mark_element_dirty` <a id="mark_element_dirty"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mark_element_dirty(element_id: int): nil
```

---

### `set_viewport_size` <a id="set_viewport_size"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_viewport_size(w: float, h: float): nil
```

---

### `get_viewport_width` <a id="get_viewport_width"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_viewport_width(): float
```

---

### `get_viewport_height` <a id="get_viewport_height"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_viewport_height(): float
```

---

### `set_root` <a id="set_root"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_root(w: ui.Widget): nil
```

---

### `update_blueprint` <a id="update_blueprint"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn update_blueprint(bp: ui_types.Blueprint): nil
```

---

### `set_root_any` <a id="set_root_any"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_root_any(root): nil
```

---

### `codepoint_to_utf8` <a id="codepoint_to_utf8"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn codepoint_to_utf8(cp: int): str
```

---

### `utf8_pop_back` <a id="utf8_pop_back"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn utf8_pop_back(s: str): str
```

---

### `get_char_width` <a id="get_char_width"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn get_char_width(font_size: float): float
```

---

### `measure_widget_height` <a id="measure_widget_height"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn measure_widget_height(w: ui.Widget): float
```

---

### `measure_widget_width` <a id="measure_widget_width"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn measure_widget_width(w: ui.Widget, available_w: float): float
```

---

### `hit_test_and_click_blueprint` <a id="hit_test_and_click_blueprint"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hit_test_and_click_blueprint(bp: ui_types.Blueprint, px: float, py: float, x: float, y: float, available_w: float, available_h: float): ui_types.Blueprint
```

---

### `hit_test_and_click_widget` <a id="hit_test_and_click_widget"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hit_test_and_click_widget(w: ui.Widget, px: float, py: float, x: float, y: float, available_w: float, available_h: float): nil
```

---

### `blur_focus_recursive` <a id="blur_focus_recursive"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn blur_focus_recursive(w: ui.Widget): nil
```

---

### `dispatch_pointer_down` <a id="dispatch_pointer_down"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dispatch_pointer_down(px: float, py: float): nil
```

---

### `dispatch_pointer_click` <a id="dispatch_pointer_click"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dispatch_pointer_click(px: float, py: float): nil
```

---

### `dispatch_pointer_move` <a id="dispatch_pointer_move"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dispatch_pointer_move(px: float, py: float): nil
```

---

### `render_blueprint_node` <a id="render_blueprint_node"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn render_blueprint_node(bp: ui_types.Blueprint, x: float, y: float, available_w: float, available_h: float, cvs: canvas.Canvas): nil
```

---

### `draw_widget_focus_ring` <a id="draw_widget_focus_ring"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn draw_widget_focus_ring(w: ui.Widget, x: float, y: float, width: float, height: float, cvs: canvas.Canvas): nil
```

Helper to draw focus ring if widget is focused

---

### `render_widget_node` <a id="render_widget_node"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn render_widget_node(w: ui.Widget, x: float, y: float, available_w: float, available_h: float, cvs: canvas.Canvas): nil
```

---

### `update_animations_recursive` <a id="update_animations_recursive"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn update_animations_recursive(w: ui.Widget, dt: float): nil
```

---

### `render_from_layout_boxes` <a id="render_from_layout_boxes"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn render_from_layout_boxes(boxes: list, cvs: canvas.Canvas): nil
```

Render using pre-computed layout boxes for better performance
This is called when layout.lm's LayoutBox system is integrated

---

### `frame_update` <a id="frame_update"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn frame_update(delta_time: float): nil
```

---

### `reset_pressed_recursive` <a id="reset_pressed_recursive"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn reset_pressed_recursive(w: ui.Widget): nil
```

---

### `update_hover_state_recursive` <a id="update_hover_state_recursive"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn update_hover_state_recursive(w: ui.Widget, px: float, py: float, x: float, y: float, available_w: float, available_h: float, mark_dirty: int): nil
```

Update hover states for interactive widgets

---

### `dispatch_pointer_up` <a id="dispatch_pointer_up"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dispatch_pointer_up(px: float, py: float): nil
```

---

### `send_char_to_widget` <a id="send_char_to_widget"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn send_char_to_widget(w: ui.Widget, cp: int): int
```

---

### `dispatch_char_input` <a id="dispatch_char_input"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dispatch_char_input(cp: int): nil
```

---

### `send_key_down_to_widget` <a id="send_key_down_to_widget"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn send_key_down_to_widget(w: ui.Widget, key_code: int, mods: int): int
```

---

### `dispatch_key_down` <a id="dispatch_key_down"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dispatch_key_down(key_code: int, mods: int = ...): nil
```

---

### `send_wheel_to_widget` <a id="send_wheel_to_widget"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn send_wheel_to_widget(w: ui.Widget, px: float, py: float, delta: float, x: float, y: float, available_w: float, available_h: float): int
```

---

### `dispatch_mouse_wheel` <a id="dispatch_mouse_wheel"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dispatch_mouse_wheel(delta: float): nil
```

---


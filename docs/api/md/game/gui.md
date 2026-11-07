# API Documentation: `gui.lm`

## Overview

std/game/gui.lm
High-performance, zero-DOM Immediate-Mode GUI (IMGUI) engine for game developers.
Features comprehensive widget library, moddable style stack, and customizable themes.

## Symbols

- **Frame**: [`WindowState`](#WindowState)
- **Frame**: [`GUI`](#GUI)

---

### `WindowState` <a id="WindowState"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame WindowState
```

#### Members

- `var pub collapsed: bool` *(field)*
- `var pub is_dragging: bool` *(field)*
- `var pub drag_off_x: float` *(field)*
- `var pub drag_off_y: float` *(field)*
- `pub init()` *(constructor)*

---

### `GUI` <a id="GUI"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame GUI
```

#### Members

- `var pub theme: types.GUITheme` *(field)*
- `var pub mouse_x: float` *(field)*
- `var pub mouse_y: float` *(field)*
- `var pub mouse_down: bool` *(field)*
- `var pub mouse_pressed: bool` *(field)*
- `var pub mouse_released: bool` *(field)*
- `var pub mouse_wheel: float` *(field)*
- `var pub prev_mouse_down: bool` *(field)*
- `var pub dt: float` *(field)*
- `var pub keys_down: list` *(field)*
- `var pub keys_pressed: list` *(field)*
- `var pub typed_chars: list` *(field)*
- `var pub active_modifiers: int` *(field)*
- `var pub get_clipboard_cb: function?` *(field)*
- `var pub set_clipboard_cb: function?` *(field)*
- `var pub hot_id: str` *(field)*
- `var pub active_id: str` *(field)*
- `var pub id_prefix: str` *(field)*
- `var pub prev_item_hovered: bool` *(field)*
- `var pub prev_item_rect: types.Rect` *(field)*
- `var pub cursor_x: float` *(field)*
- `var pub cursor_y: float` *(field)*
- `var pub start_x: float` *(field)*
- `var pub start_y: float` *(field)*
- `var pub line_h: float` *(field)*
- `var pub same_line_flag: bool` *(field)*
- `var pub prev_item_w: float` *(field)*
- `var pub indent_x: float` *(field)*
- `var pub columns_count: int` *(field)*
- `var pub columns_idx: int` *(field)*
- `var pub columns_start_x: float` *(field)*
- `var pub columns_width: float` *(field)*
- `var pub scroll_y: float` *(field)*
- `var pub active_popup_id: str` *(field)*
- `var pub popup_x: float` *(field)*
- `var pub popup_y: float` *(field)*
- `var pub popup_w: float` *(field)*
- `var pub popup_h: float` *(field)*
- `var pub cur_tab_bar_id: str` *(field)*
- `var pub combo_open_id: str` *(field)*
- `var pub editor_controllers: dict` *(field)*
- `var pub scroll_offsets: dict` *(field)*
- `var pub focus_manager: focus.Manager` *(field)*
- `var pub next_shadow: any` *(field)*
- `var pub has_next_shadow: bool` *(field)*
- `var pub shadow_stack: list` *(field)*
- `var pub next_opacity: float` *(field)*
- `var pub has_next_opacity: bool` *(field)*
- `var pub next_disabled: bool` *(field)*
- `var pub has_next_disabled: bool` *(field)*
- `var pub in_window: bool` *(field)*
- `var pub cur_window_title: str` *(field)*
- `var pub cur_window_x: float` *(field)*
- `var pub cur_window_y: float` *(field)*
- `var pub cur_window_w: float` *(field)*
- `var pub cur_window_h: float` *(field)*
- `var pub windows: dict` *(field)*
- `var pub headers: dict` *(field)*
- `var pub anim_store: anim.IMGUIAnimationStore` *(field)*
- `var pub style_color_indices: list` *(field)*
- `var pub style_color_stack: list` *(field)*
- `var pub style_var_indices: list` *(field)*
- `var pub style_var_stack: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn begin(mx: float, my: float, is_down: bool): nil` *(method)*
- `pub fn is_occluded(x: float, y: float, w: float, h: float): bool` *(method)*
- `pub fn end(): nil` *(method)*
- `pub fn set_theme(new_theme: types.GUITheme): nil` *(method)*
- `pub fn push_style_color(idx: int, c: color.Color): nil` *(method)*
- `pub fn push_color_role(role: types.ColorRole, c: color.Color): nil` *(method)*
- `pub fn pop_style_color(): nil` *(method)*
- `pub fn push_style_var(idx: int, value: float): nil` *(method)*
- `pub fn pop_style_var(): nil` *(method)*
- `pub fn set_next_shadow(s: any): nil` *(method)*
- `pub fn shadow(s: any): GUI` *(method)*
- `pub fn opacity(o: float): GUI` *(method)*
- `pub fn disabled(): GUI` *(method)*
- `pub fn push_shadow(s: any): nil` *(method)*
- `pub fn pop_shadow(): nil` *(method)*
- `pub fn get_active_shadow(): any` *(method)*
- `pub fn get_style_color(idx: int): color.Color` *(method)*
- `pub fn get_style_var(idx: int, default_value: float): float` *(method)*
- `pub fn get_color_role(role: types.ColorRole): color.Color` *(method)*
- `pub fn get_var_type(v: types.StyleVar, default_value: float): float` *(method)*
- `pub fn make_id(label: str): str` *(method)*
- `pub fn push_id(prefix: str): nil` *(method)*
- `pub fn pop_id(): nil` *(method)*
- `pub fn set_cursor(x: float, y: float): nil` *(method)*
- `pub fn same_line(): nil` *(method)*
- `pub fn spacing(): nil` *(method)*
- `pub fn indent(): nil` *(method)*
- `pub fn unindent(): nil` *(method)*
- `fn advance(item_w: float, item_h: float): nil` *(method)*
- `pub fn columns(count: int): nil` *(method)*
- `pub fn next_column(): nil` *(method)*
- `pub fn draw_rect(x: float, y: float, w: float, h: float, col: color.Color): nil` *(method)*
- `pub fn label(text: str): nil` *(method)*
- `pub fn button(text: str): bool` *(method)*
- `pub fn button_colored(text: str, bg_color: color.Color): bool` *(method)*
- `pub fn checkbox(label: str, checked: bool): bool` *(method)*
- `pub fn radio_button(label: str, active: bool): bool` *(method)*
- `pub fn toggle(label: str, enabled: bool): bool` *(method)*
- `pub fn slider(label: str, value: float, min_val: float, max_val: float): float` *(method)*
- `pub fn slider_int(label: str, value: int): int` *(method)*
- `pub fn stepper_int(label: str, value: int): int` *(method)*
- `pub fn stepper_float(label: str, value: float): float` *(method)*
- `pub fn is_key_down(k: int): bool` *(method)*
- `pub fn is_key_pressed(k: int): bool` *(method)*
- `pub fn get_typed_chars(): list` *(method)*
- `pub fn get_editor_controller(label: str): any` *(method)*
- `pub fn set_multiline_selection(label: str, line: int, col: int, end_line: int, end_col: int): nil` *(method)*
- `pub fn set_multiline_text(label: str, new_text: str): nil` *(method)*
- `pub fn get_multiline_cursor(label: str): tuple` *(method)*
- `pub fn input_text_multiline(label: str, text: str, width: float, height: float): str` *(method)*
- `pub fn input_text(label: str, text: str): str` *(method)*
- `pub fn combo_box(label: str, items: list, selected_idx: int): int` *(method)*
- `pub fn color_button(id: str, col: color.Color): bool` *(method)*
- `pub fn color_picker(label: str, col: color.Color): color.Color` *(method)*
- `pub fn plot_lines(label: str, values: list): nil` *(method)*
- `pub fn plot_histogram(label: str, values: list): nil` *(method)*
- `pub fn progress_bar(fraction: float): nil` *(method)*
- `pub fn separator(): nil` *(method)*
- `pub fn header(title: str): bool` *(method)*
- `pub fn begin_tab_bar(id: str): bool` *(method)*
- `pub fn tab_item(label: str, is_active: bool): bool` *(method)*
- `pub fn end_tab_bar(): nil` *(method)*
- `pub fn tree_node(label: str): bool` *(method)*
- `pub fn tree_pop(): nil` *(method)*
- `pub fn tooltip(text: str): nil` *(method)*
- `pub fn open_popup(id: str): nil` *(method)*
- `pub fn close_popup(id: str): nil` *(method)*
- `pub fn is_popup_open(id: str): bool` *(method)*
- `pub fn begin_popup(id: str, x: float, y: float, w: float, h: float): bool` *(method)*
- `pub fn end_popup(): nil` *(method)*
- `pub fn table(headers: list, rows_count: int): bool` *(method)*
- `pub fn begin_scroll_area(w: float, h: float, content_h: float): bool` *(method)*
- `pub fn end_scroll_area(): nil` *(method)*
- `pub fn set_window_rect(title: str, x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn begin_window(title: str, default_x: float, default_y: float, default_w: float, default_h: float): bool` *(method)*
- `pub fn end_window(): nil` *(method)*
- `pub fn show_debug_hud(fps: float, dt: float): nil` *(method)*

---


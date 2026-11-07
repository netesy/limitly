# API Documentation: `input.lm`

## Overview

Mouse Button Enumeration

## Symbols

- **Frame**: [`InputManager`](#InputManager)

---

### `InputManager` <a id="InputManager"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame InputManager
```

#### Members

- `var pub mouse_x: float` *(field)*
- `var pub mouse_y: float` *(field)*
- `var pub mouse_prev_x: float` *(field)*
- `var pub mouse_prev_y: float` *(field)*
- `var pub mouse_delta_x: float` *(field)*
- `var pub mouse_delta_y: float` *(field)*
- `var pub mouse_wheel: float` *(field)*
- `var pub mouse_buttons_down: list` *(field)*
- `var pub mouse_buttons_pressed: list` *(field)*
- `var pub mouse_buttons_released: list` *(field)*
- `var pub keys_down: list` *(field)*
- `var pub keys_pressed: list` *(field)*
- `var pub keys_released: list` *(field)*
- `var pub typed_chars: list` *(field)*
- `var pub active_modifiers: int` *(field)*
- `var pub actions: dict` *(field)*
- `var pub axes: dict` *(field)*
- `pub init()` *(constructor)*
- `pub fn begin_frame(): nil` *(method)*
- `pub fn on_mouse_move(x: float, y: float): nil` *(method)*
- `pub fn on_mouse_down(button: int, x: float, y: float): nil` *(method)*
- `pub fn on_mouse_up(button: int, x: float, y: float): nil` *(method)*
- `pub fn on_mouse_wheel(wheel: float): nil` *(method)*
- `pub fn on_key_down(key: int): nil` *(method)*
- `pub fn on_key_up(key: int): nil` *(method)*
- `pub fn on_char(codepoint: int): nil` *(method)*
- `pub fn is_key_down(key: int): bool` *(method)*
- `pub fn is_key_pressed(key: int): bool` *(method)*
- `pub fn is_key_released(key: int): bool` *(method)*
- `pub fn is_mouse_down(): bool` *(method)*
- `pub fn is_mouse_pressed(): bool` *(method)*
- `pub fn is_mouse_released(): bool` *(method)*
- `pub fn mouse_pos(): types.Vec2` *(method)*
- `pub fn mouse_delta(): types.Vec2` *(method)*
- `pub fn bind_action(action_name: str, key_codes: list): nil` *(method)*
- `pub fn is_action_down(action_name: str): bool` *(method)*
- `pub fn is_action_pressed(action_name: str): bool` *(method)*
- `pub fn is_action_released(action_name: str): bool` *(method)*
- `pub fn bind_axis(axis_name: str, neg_key: int, pos_key: int): nil` *(method)*
- `pub fn get_axis(axis_name: str): float` *(method)*

---


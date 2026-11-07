# API Documentation: `app.lm`

## Overview

std/game/app.lm
High-level game loop, event polling, timing driver, and application runner for std.game

## Symbols

- **Frame**: [`Config`](#Config)
- **Function**: [`default_config`](#default_config)
- **Frame**: [`Game`](#Game)

---

### `Config` <a id="Config"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Config
```

#### Members

- `var pub title: str` *(field)*
- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `var pub resizable: bool` *(field)*
- `var pub bg_color: color.Color` *(field)*
- `var pub fixed_dt: float` *(field)*
- `pub init()` *(constructor)*

---

### `default_config` <a id="default_config"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn default_config(): Config
```

---

### `Game` <a id="Game"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Game
```

#### Members

- `var pub config: Config` *(field)*
- `var pub gui: GUI` *(field)*
- `var pub input: InputManager` *(field)*
- `var pub scenes: SceneManager` *(field)*
- `var pub is_running: bool` *(field)*
- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `var pub timer: Timer` *(field)*
- `var pub delta_time: float` *(field)*
- `var pub unscaled_delta_time: float` *(field)*
- `var pub time_scale: float` *(field)*
- `var pub total_time: float` *(field)*
- `var pub frame_count: int` *(field)*
- `var pub fps: float` *(field)*
- `var pub accumulator: float` *(field)*
- `var pub fixed_dt: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn setup(): bool` *(method)*
- `pub fn begin_frame(): nil` *(method)*
- `pub fn end_frame(): nil` *(method)*
- `pub fn dt(): float` *(method)*
- `pub fn step_physics(): bool` *(method)*
- `pub fn register_scene(name: str, sc: Scene): nil` *(method)*
- `pub fn switch_scene(name: str): nil` *(method)*
- `pub fn push_scene(name: str): nil` *(method)*
- `pub fn pop_scene(): union` *(method)*
- `pub fn current_scene(): union` *(method)*
- `pub fn is_key_down(key: int): bool` *(method)*
- `pub fn is_key_pressed(key: int): bool` *(method)*
- `pub fn is_key_released(key: int): bool` *(method)*
- `pub fn is_mouse_down(): bool` *(method)*
- `pub fn is_mouse_pressed(): bool` *(method)*
- `pub fn is_mouse_released(): bool` *(method)*
- `pub fn mouse_pos(): types.Vec2` *(method)*
- `pub fn mouse_delta(): types.Vec2` *(method)*
- `pub fn bind_action(action: str, keys: list): nil` *(method)*
- `pub fn is_action_down(action: str): bool` *(method)*
- `pub fn is_action_pressed(action: str): bool` *(method)*
- `pub fn is_action_released(action: str): bool` *(method)*
- `pub fn bind_axis(axis: str, neg_key: int, pos_key: int): nil` *(method)*
- `pub fn get_axis(axis: str): float` *(method)*
- `pub fn set_resolution(w: int, h: int): nil` *(method)*
- `pub fn set_size(w: int, h: int): nil` *(method)*
- `pub fn quit(): nil` *(method)*
- `pub fn shutdown(): nil` *(method)*

---


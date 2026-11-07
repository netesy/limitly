# API Documentation: `scene.lm`

## Overview

std/game/scene.lm
State machine, scene graph lifecycle hooks, scene stack, and transition engine

## Symbols

- **Frame**: [`Scene`](#Scene)
- **Function**: [`scene`](#scene)
- **Frame**: [`SceneManager`](#SceneManager)
- **Function**: [`SceneManager`](#SceneManager)

---

### `Scene` <a id="Scene"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Scene: gtraits.Updatable
```

#### Members

- `var pub name: str` *(field)*
- `var pub is_active: bool` *(field)*
- `var pub is_paused: bool` *(field)*
- `var pub is_visible: bool` *(field)*
- `var pub on_enter_cb: function?` *(field)*
- `var pub on_exit_cb: function?` *(field)*
- `var pub on_pause_cb: function?` *(field)*
- `var pub on_resume_cb: function?` *(field)*
- `var pub update_cb: function?` *(field)*
- `var pub fixed_update_cb: function?` *(field)*
- `var pub draw_cb: function?` *(field)*
- `var pub draw_gui_cb: function?` *(field)*
- `var pub on_event_cb: function?` *(field)*
- `pub init()` *(constructor)*
- `pub fn on_enter(): nil` *(method)*
- `pub fn on_exit(): nil` *(method)*
- `pub fn on_pause(): nil` *(method)*
- `pub fn on_resume(): nil` *(method)*
- `pub fn update(dt: float): nil` *(method)*
- `pub fn fixed_update(dt: float): nil` *(method)*
- `pub fn draw(): nil` *(method)*
- `pub fn draw_gui(gui: any): nil` *(method)*
- `pub fn on_event(event_type: int, p1: any, p2: any): bool` *(method)*

---

### `scene` <a id="scene"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn scene(name: str = ...): Scene
```

---

### `SceneManager` <a id="SceneManager"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame SceneManager: gtraits.Updatable
```

#### Members

- `var pub scenes: dict` *(field)*
- `var pub stack: list` *(field)*
- `var pub current_name: str` *(field)*
- `var pub is_transitioning: bool` *(field)*
- `var pub transition_mode: int` *(field)*
- `var pub transition_timer: float` *(field)*
- `var pub transition_duration: float` *(field)*
- `var pub transition_alpha: float` *(field)*
- `var pub transition_color: color.Color` *(field)*
- `var pub pending_scene_name: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn register(name: str, s: Scene): nil` *(method)*
- `pub fn get(name: str): union` *(method)*
- `pub fn current(): union` *(method)*
- `pub fn stack_size(): int` *(method)*
- `pub fn has_scenes(): bool` *(method)*
- `fn _perform_switch(name: str): nil` *(method)*
- `pub fn switch_to(name: str): nil` *(method)*
- `pub fn push(name: str): nil` *(method)*
- `pub fn pop(): union` *(method)*
- `pub fn update(dt: float): nil` *(method)*
- `pub fn fixed_update(dt: float): nil` *(method)*
- `pub fn draw(): nil` *(method)*
- `pub fn draw_gui(gui: any): nil` *(method)*
- `pub fn on_event(event_type: int, p1: any, p2: any): bool` *(method)*

---

### `SceneManager` <a id="SceneManager"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn SceneManager(): SceneManager
```

---


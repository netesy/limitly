# API Documentation: `app.lm`

## Overview

std/game/app.lm
Game-domain runtime: timing, input interpretation, scene management, and
IMGUI integration. std.app owns the window, the event pump, and the
frame loop — Game plugs into it.

Two ways to drive a game:

  // 1. Attached — Game state lives in module scope / scenes:
  var g = game.Game(game.default_config());
  g.register_scene("level1", level);
  g.attach();                       // moves g into the app hooks
  var a = app.App("My Game", 1280, 720);
  a.run();                          // pump -> g.poll -> g.render -> UI -> swap

  // 2. Manual loop — game logic lives in main() locals:
  var g = game.Game(game.default_config());
  var a = app.App(g.config.title, g.config.width, g.config.height);
  a.open();
  while (a.is_running()) {
      a.pump();                     // events -> queue + UI dispatch
      g.poll();                     // dt, input, scene update
      // ... all game logic, locals in scope ...
      a.begin_pass();
      g.imgui_begin();
      // ... scene render + IMGUI windows ...
      g.imgui_end();
      a.end_pass();                 // retained UI on top + swap
      sleep(0.008);
  }
  a.close();

Game never calls events.pump_events, gg.begin_pass, or gg.commit — those
belong to std.app. poll() reads events.pending_events() non-destructively
after App.pump() has filled the queue.

## Symbols

- **Frame**: [`Config`](#Config)
- **Function**: [`default_config`](#default_config)
- **Frame**: [`Game`](#Game)
- **Function**: [`_game_update`](#_game_update)
- **Function**: [`_game_draw`](#_game_draw)

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
- `pub fn attach(): nil` *(method)*
- `pub fn window(): app.App` *(method)*
- `pub fn poll(): nil` *(method)*
- `pub fn imgui_begin(): nil` *(method)*
- `pub fn imgui_end(): nil` *(method)*
- `pub fn render(): nil` *(method)*
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
- `pub fn mouse_pos(): Vector2` *(method)*
- `pub fn mouse_delta(): Vector2` *(method)*
- `pub fn bind_action(action: str, keys: list): nil` *(method)*
- `pub fn is_action_down(action: str): bool` *(method)*
- `pub fn is_action_pressed(action: str): bool` *(method)*
- `pub fn is_action_released(action: str): bool` *(method)*
- `pub fn bind_axis(axis: str, neg_key: int, pos_key: int): nil` *(method)*
- `pub fn get_axis(axis: str): float` *(method)*
- `pub fn set_resolution(w: int, h: int): nil` *(method)*
- `pub fn set_size(w: int, h: int): nil` *(method)*
- `pub fn quit(): nil` *(method)*
- `pub fn is_running(): bool` *(method)*

---

### `_game_update` <a id="_game_update"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _game_update(dt: float): nil
```

---

### `_game_draw` <a id="_game_draw"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _game_draw(): nil
```

---


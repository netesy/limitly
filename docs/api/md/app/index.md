# API Documentation: `index.lm`

## Overview

Application Module
The single owner of window lifecycle, the event loop, and frame
presentation for Lymar applications — UI apps and games alike.

Usage (UI app — the common case):

  import std.app as app;
  import std.ui as ui;

  var a = app.App("Gallery", 1280, 800);
  a.ui(root);
  a.run();

Usage (game / custom loop — full control, locals stay in scope):

  var a = app.App("Game", 1280, 720);
  a.open();
  while (a.is_running()) {
      a.pump();          // events -> queue + UI dispatch + frame dt
      // ... game logic, has access to a.delta_time() ...
      a.begin_pass();    // start GPU pass (clear color)
      // ... draw: scenes, std.gui, anything ...
      a.end_pass();      // draw hooks + retained UI on top + swap
      sleep(0.008);
  }
  a.close();

Optional per-frame hooks (module fn values — see std.ui.button for the
same callback convention):

  a.on_update(fn(dt: float): nil { ... });   // after pump, before present
  a.on_draw(fn(): nil { ... });              // inside pass, before UI

OS event pumping and the typed event queue live in std.events — this
module only *dispatches* queued events into the component tree
(std.ui.tree) and calls the registered hooks.

## Symbols

- **Function**: [`native_mode`](#native_mode)
- **Frame**: [`App`](#App)
- **Function**: [`get_window_width`](#get_window_width)
- **Function**: [`get_window_height`](#get_window_height)
- **Function**: [`get_framebuffer_width`](#get_framebuffer_width)
- **Function**: [`get_framebuffer_height`](#get_framebuffer_height)
- **Function**: [`get_dpi_scale`](#get_dpi_scale)
- **Function**: [`get_frame_count`](#get_frame_count)
- **Function**: [`app_delta_time`](#app_delta_time)
- **Function**: [`app_is_running`](#app_is_running)
- **Function**: [`app_is_initialized`](#app_is_initialized)
- **Function**: [`quit`](#quit)
- **Function**: [`on_update`](#on_update)
- **Function**: [`on_draw`](#on_draw)
- **Function**: [`set_clear_color`](#set_clear_color)
- **Function**: [`set_window_size`](#set_window_size)
- **Function**: [`set_window_title`](#set_window_title)
- **Function**: [`set_fullscreen`](#set_fullscreen)
- **Function**: [`set_swap_interval`](#set_swap_interval)
- **Function**: [`get_executable_path`](#get_executable_path)
- **Function**: [`get_home_directory`](#get_home_directory)
- **Frame**: [`WindowConfig`](#WindowConfig)
- **Frame**: [`State`](#State)
- **Function**: [`_boot`](#_boot)
- **Function**: [`_shutdown`](#_shutdown)
- **Function**: [`_pump`](#_pump)
- **Function**: [`_dispatch_events`](#_dispatch_events)
- **Function**: [`_begin_pass`](#_begin_pass)
- **Function**: [`_end_pass`](#_end_pass)
- **Function**: [`_show_window`](#_show_window)

---

### `native_mode` <a id="native_mode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn native_mode(): int
```

---

### `App` <a id="App"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame App
```

── App frame ────────────────────────────────────────────────────────────────
Window + loop configuration. Effectively a singleton façade over the
module state above — one window per process.

#### Members

- `var pub title: str` *(field)*
- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `var pub resizable: int` *(field)*
- `var pub fullscreen: int` *(field)*
- `var pub high_dpi: int` *(field)*
- `var pub sample_count: int` *(field)*
- `var pub swap_interval: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn ui(root: ui_component.Component): nil` *(method)*
- `pub fn on_update(cb: union): nil` *(method)*
- `pub fn on_draw(cb: union): nil` *(method)*
- `pub fn run(): nil` *(method)*
- `pub fn open(): nil` *(method)*
- `pub fn step(): nil` *(method)*
- `pub fn pump(): nil` *(method)*
- `pub fn present(): nil` *(method)*
- `pub fn begin_pass(): nil` *(method)*
- `pub fn end_pass(): nil` *(method)*
- `pub fn close(): nil` *(method)*
- `pub fn quit(): nil` *(method)*
- `pub fn is_running(): bool` *(method)*
- `pub fn view_width(): int` *(method)*
- `pub fn view_height(): int` *(method)*
- `pub fn framebuffer_width(): int` *(method)*
- `pub fn framebuffer_height(): int` *(method)*
- `pub fn dpi_scale(): float` *(method)*
- `pub fn frame_count(): int` *(method)*
- `pub fn delta_time(): float` *(method)*

---

### `get_window_width` <a id="get_window_width"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_window_width(): int
```

---

### `get_window_height` <a id="get_window_height"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_window_height(): int
```

---

### `get_framebuffer_width` <a id="get_framebuffer_width"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_framebuffer_width(): int
```

---

### `get_framebuffer_height` <a id="get_framebuffer_height"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_framebuffer_height(): int
```

---

### `get_dpi_scale` <a id="get_dpi_scale"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_dpi_scale(): float
```

---

### `get_frame_count` <a id="get_frame_count"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_frame_count(): int
```

---

### `app_delta_time` <a id="app_delta_time"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn app_delta_time(): float
```

---

### `app_is_running` <a id="app_is_running"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn app_is_running(): int
```

---

### `app_is_initialized` <a id="app_is_initialized"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn app_is_initialized(): int
```

---

### `quit` <a id="quit"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn quit(): nil
```

---

### `on_update` <a id="on_update"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn on_update(cb: union): nil
```

Per-frame hooks — module fn values, the codebase's callback convention.
on_update runs after event dispatch, before presentation; on_draw runs
inside the GPU pass before the retained UI submits.

---

### `on_draw` <a id="on_draw"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn on_draw(cb: union): nil
```

---

### `set_clear_color` <a id="set_clear_color"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_clear_color(r: float, g: float, b: float, a: float): nil
```

Frame clear color for begin_pass/present (see App.begin_pass).

---

### `set_window_size` <a id="set_window_size"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_window_size(width: int, height: int): nil
```

---

### `set_window_title` <a id="set_window_title"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_window_title(title: str): nil
```

---

### `set_fullscreen` <a id="set_fullscreen"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_fullscreen(fullscreen: int): nil
```

---

### `set_swap_interval` <a id="set_swap_interval"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_swap_interval(interval: int): nil
```

---

### `get_executable_path` <a id="get_executable_path"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_executable_path(): str
```

These two are answered by std.os: they are facts about the machine and the
location of the program, not about the application loop.

---

### `get_home_directory` <a id="get_home_directory"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_home_directory(): str
```

---

### `WindowConfig` <a id="WindowConfig"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame WindowConfig
```

Window configuration carried into global_app_state (kept internal —
App's fields are the public surface).

#### Members

- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `var pub title: str` *(field)*
- `var pub resizable: int` *(field)*
- `var pub fullscreen: int` *(field)*
- `var pub high_dpi: int` *(field)*
- `var pub sample_count: int` *(field)*
- `var pub swap_interval: int` *(field)*

---

### `State` <a id="State"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame State
```

Application state

#### Members

- `var pub is_initialized: int` *(field)*
- `var pub is_running: int` *(field)*
- `var pub window_config: WindowConfig` *(field)*
- `var pub window_id: int` *(field)*
- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `var pub framebuffer_width: int` *(field)*
- `var pub framebuffer_height: int` *(field)*
- `var pub dpi_scale: float` *(field)*
- `var pub frame_count: int` *(field)*
- `var pub last_frame_time: int` *(field)*
- `var pub delta_time: float` *(field)*

---

### `_boot` <a id="_boot"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _boot(title: str, width: int, height: int, resizable: int, fullscreen: int, high_dpi: int, sample_count: int, swap_interval: int): nil
```

---

### `_shutdown` <a id="_shutdown"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _shutdown(): nil
```

---

### `_pump` <a id="_pump"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _pump(): nil
```

---

### `_dispatch_events` <a id="_dispatch_events"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _dispatch_events(): nil
```

dispatch_events delivers this frame's std.events stream into the
component tree. It reads events.pending_events() non-destructively, so
std.game (or any other consumer) can observe the same stream — fan-out
is the default, not the exception.

---

### `_begin_pass` <a id="_begin_pass"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _begin_pass(): nil
```

---

### `_end_pass` <a id="_end_pass"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _end_pass(): nil
```

---

### `_show_window` <a id="_show_window"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _show_window(): nil
```

---


# API Documentation: `index.lm`

## Overview

Application Module
Portable window application lifecycle, event loop, and timing driver

## Symbols

- **Function**: [`event_type_from_int`](#event_type_from_int)
- **Frame**: [`Event`](#Event)
- **Frame**: [`KeyEvent`](#KeyEvent)
- **Frame**: [`MouseEvent`](#MouseEvent)
- **Frame**: [`ResizeEvent`](#ResizeEvent)
- **Frame**: [`WindowConfig`](#WindowConfig)
- **Function**: [`default_window_config`](#default_window_config)
- **Frame**: [`State`](#State)
- **Function**: [`make_default_event`](#make_default_event)
- **Function**: [`app_init`](#app_init)
- **Function**: [`init`](#init)
- **Function**: [`app_shutdown`](#app_shutdown)
- **Function**: [`shutdown`](#shutdown)
- **Function**: [`app_is_valid`](#app_is_valid)
- **Function**: [`app_is_running`](#app_is_running)
- **Function**: [`ui`](#ui)
- **Function**: [`set_ui`](#set_ui)
- **Function**: [`run_frame_step`](#run_frame_step)
- **Function**: [`app_run`](#app_run)
- **Function**: [`run`](#run)
- **Function**: [`app_quit`](#app_quit)
- **Function**: [`quit`](#quit)
- **Function**: [`process_events`](#process_events)
- **Function**: [`push_mouse_click`](#push_mouse_click)
- **Function**: [`push_quit_event`](#push_quit_event)
- **Function**: [`push_event`](#push_event)
- **Function**: [`poll_event`](#poll_event)
- **Function**: [`has_pending_events`](#has_pending_events)
- **Function**: [`present_frame`](#present_frame)
- **Function**: [`set_window_size`](#set_window_size)
- **Function**: [`get_window_width`](#get_window_width)
- **Function**: [`get_window_height`](#get_window_height)
- **Function**: [`get_framebuffer_width`](#get_framebuffer_width)
- **Function**: [`get_framebuffer_height`](#get_framebuffer_height)
- **Function**: [`get_dpi_scale`](#get_dpi_scale)
- **Function**: [`get_frame_count`](#get_frame_count)
- **Function**: [`get_delta_time`](#get_delta_time)
- **Function**: [`set_window_title`](#set_window_title)
- **Function**: [`set_fullscreen`](#set_fullscreen)
- **Function**: [`set_swap_interval`](#set_swap_interval)
- **Function**: [`show_window`](#show_window)
- **Function**: [`hide_window`](#hide_window)
- **Function**: [`focus_window`](#focus_window)
- **Function**: [`request_attention`](#request_attention)
- **Function**: [`get_current_time`](#get_current_time)
- **Function**: [`sleep_ms`](#sleep_ms)
- **Function**: [`get_clipboard_string`](#get_clipboard_string)
- **Function**: [`set_clipboard_string`](#set_clipboard_string)
- **Function**: [`get_mouse_position`](#get_mouse_position)
- **Function**: [`set_mouse_position`](#set_mouse_position)
- **Function**: [`get_mouse_button_state`](#get_mouse_button_state)
- **Function**: [`get_key_state`](#get_key_state)
- **Function**: [`get_modifier_state`](#get_modifier_state)
- **Function**: [`create_app_data_directory`](#create_app_data_directory)
- **Function**: [`get_executable_path`](#get_executable_path)
- **Function**: [`get_home_directory`](#get_home_directory)

---

### `event_type_from_int` <a id="event_type_from_int"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn event_type_from_int(code: int): EventType
```

---

### `Event` <a id="Event"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Event
```

Event frame

#### Members

- `var pub event_type: EventType` *(field)*
- `var pub timestamp: int` *(field)*
- `var pub window_id: int` *(field)*
- `var pub x: int` *(field)*
- `var pub y: int` *(field)*
- `var pub key_code: int` *(field)*
- `var pub xdest: int` *(field)*
- `var pub ydest: int` *(field)*
- `pub init()` *(constructor)*

---

### `KeyEvent` <a id="KeyEvent"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame KeyEvent
```

Key event frame

#### Members

- `var pub modifiers: int` *(field)*
- `var pub repeat: int` *(field)*

---

### `MouseEvent` <a id="MouseEvent"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame MouseEvent
```

Mouse event frame

#### Members

- `var pub button: int` *(field)*
- `var pub modifiers: int` *(field)*

---

### `ResizeEvent` <a id="ResizeEvent"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ResizeEvent
```

Resize event frame

#### Members

- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `var pub framebuffer_width: int` *(field)*
- `var pub framebuffer_height: int` *(field)*

---

### `WindowConfig` <a id="WindowConfig"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame WindowConfig
```

Window configuration

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

### `default_window_config` <a id="default_window_config"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn default_window_config(): WindowConfig
```

Default window configuration

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
- `var pub event_queue: list` *(field)*
- `var pub event_queue_head: int` *(field)*
- `var pub frame_count: int` *(field)*
- `var pub last_frame_time: int` *(field)*
- `var pub delta_time: float` *(field)*

---

### `make_default_event` <a id="make_default_event"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn make_default_event(): Event
```

---

### `app_init` <a id="app_init"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn app_init(config: WindowConfig): int
```

Initialize application with window configuration

---

### `init` <a id="init"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn init(config: any = ...): int
```

---

### `app_shutdown` <a id="app_shutdown"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn app_shutdown(): nil
```

Shutdown application and release resources

---

### `shutdown` <a id="shutdown"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn shutdown(): nil
```

---

### `app_is_valid` <a id="app_is_valid"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn app_is_valid(): int
```

---

### `app_is_running` <a id="app_is_running"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn app_is_running(): int
```

---

### `ui` <a id="ui"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ui(root: ui_types.Widget): nil
```

---

### `set_ui` <a id="set_ui"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_ui(root): nil
```

---

### `run_frame_step` <a id="run_frame_step"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn run_frame_step(): nil
```

---

### `app_run` <a id="app_run"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn app_run(): nil
```

---

### `run` <a id="run"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn run(root: any = ...): nil
```

---

### `app_quit` <a id="app_quit"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn app_quit(): nil
```

---

### `quit` <a id="quit"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn quit(): nil
```

---

### `process_events` <a id="process_events"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn process_events(): nil
```

---

### `push_mouse_click` <a id="push_mouse_click"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn push_mouse_click(x: int, y: int): nil
```

---

### `push_quit_event` <a id="push_quit_event"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn push_quit_event(): nil
```

---

### `push_event` <a id="push_event"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn push_event(event: Event): nil
```

---

### `poll_event` <a id="poll_event"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn poll_event(): Event
```

---

### `has_pending_events` <a id="has_pending_events"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn has_pending_events(): int
```

---

### `present_frame` <a id="present_frame"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn present_frame(): nil
```

---

### `set_window_size` <a id="set_window_size"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_window_size(width: int, height: int): nil
```

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

### `get_delta_time` <a id="get_delta_time"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_delta_time(): float
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

### `show_window` <a id="show_window"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn show_window(): nil
```

---

### `hide_window` <a id="hide_window"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hide_window(): nil
```

---

### `focus_window` <a id="focus_window"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn focus_window(): nil
```

---

### `request_attention` <a id="request_attention"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn request_attention(): nil
```

---

### `get_current_time` <a id="get_current_time"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_current_time(): int
```

---

### `sleep_ms` <a id="sleep_ms"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sleep_ms(milliseconds: int): nil
```

---

### `get_clipboard_string` <a id="get_clipboard_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_clipboard_string(): str
```

---

### `set_clipboard_string` <a id="set_clipboard_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_clipboard_string(text: str): nil
```

---

### `get_mouse_position` <a id="get_mouse_position"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_mouse_position(): tuple
```

---

### `set_mouse_position` <a id="set_mouse_position"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_mouse_position(x: int, y: int): nil
```

---

### `get_mouse_button_state` <a id="get_mouse_button_state"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_mouse_button_state(button: int): int
```

---

### `get_key_state` <a id="get_key_state"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_key_state(key: int): int
```

---

### `get_modifier_state` <a id="get_modifier_state"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_modifier_state(): int
```

---

### `create_app_data_directory` <a id="create_app_data_directory"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_app_data_directory(): str
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


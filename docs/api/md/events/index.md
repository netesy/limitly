# API Documentation: `index.lm`

## Overview

std/events
Typed OS/window event pump and queue.

This is the SINGLE translation point from raw gg.poll_events() records into
typed Event values. Both std.app (Fluent ui_context dispatch) and std.game
(InputManager/IMGUI) consume this queue — neither calls gg.poll_events()
directly, so events are never stolen between frameworks.

Ownership model: exactly one consumer drains the queue per frame. The
Fluent path drains via std.app.dispatch_ui_events(); the game path drains
via poll_event() in Game.begin_frame(). Mixing both in one frame splits
the stream — pick one.

## Symbols

- **Function**: [`event_type_from_int`](#event_type_from_int)
- **Frame**: [`Event`](#Event)
- **Frame**: [`KeyEvent`](#KeyEvent)
- **Frame**: [`MouseEvent`](#MouseEvent)
- **Frame**: [`ResizeEvent`](#ResizeEvent)
- **Function**: [`make_default_event`](#make_default_event)
- **Function**: [`clear`](#clear)
- **Function**: [`pump_events`](#pump_events)
- **Function**: [`push_event`](#push_event)
- **Function**: [`push_mouse_click`](#push_mouse_click)
- **Function**: [`push_quit_event`](#push_quit_event)
- **Function**: [`poll_event`](#poll_event)
- **Function**: [`has_pending_events`](#has_pending_events)

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

### `make_default_event` <a id="make_default_event"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn make_default_event(): Event
```

---

### `clear` <a id="clear"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn clear(): nil
```

Reset the queue (call on app/window init and shutdown).

---

### `pump_events` <a id="pump_events"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pump_events(): nil
```

pump_events drains gg.poll_events() once per frame and enqueues typed
Events. This is the ONLY caller of gg.poll_events() above the gg layer —
it is also the frame-publish boundary on the GPU backend, so it must run
exactly once per frame regardless of which consumer drains the queue.

---

### `push_event` <a id="push_event"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn push_event(event: Event): nil
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

### `poll_event` <a id="poll_event"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn poll_event(): Event
```

Dequeue the next typed event. Only call when has_pending_events() != 0 —
on an empty queue this returns a default Quit event without advancing.

---

### `has_pending_events` <a id="has_pending_events"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn has_pending_events(): int
```

True while unconsumed events remain. Compares head against length — the
consumed prefix does not count as pending.

---


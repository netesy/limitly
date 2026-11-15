# API Documentation: `index.lm`

## Overview

std/events
Typed OS/window event pump and per-frame event queue.

This is the SINGLE translation point from raw gg.poll_events() records into
typed Event values. Both std.app (Fluent ui_context dispatch) and std.game
(InputManager/IMGUI) consume the SAME per-frame event stream — neither
calls gg.poll_events() directly, so events are never stolen between
frameworks.

Fan-out model: pump_events() builds a fresh event_queue once per frame.
Every consumer reads events.pending_events() non-destructively, so any
number of frameworks can observe the same stream. Events pushed via
push_event() land in injected_events and are merged into the queue at the
next pump — they live exactly one frame.

pump_events() is also the frame-publish boundary on the GPU backend, so it
must run exactly once per frame.

## Symbols

- **Function**: [`event_type_from_int`](#event_type_from_int)
- **Frame**: [`Event`](#Event)
- **Frame**: [`KeyEvent`](#KeyEvent)
- **Frame**: [`MouseEvent`](#MouseEvent)
- **Frame**: [`ResizeEvent`](#ResizeEvent)
- **Function**: [`clear`](#clear)
- **Function**: [`pending_events`](#pending_events)
- **Function**: [`pump_events`](#pump_events)
- **Function**: [`push_event`](#push_event)
- **Function**: [`push_mouse_click`](#push_mouse_click)
- **Function**: [`push_quit_event`](#push_quit_event)

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

### `clear` <a id="clear"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn clear(): nil
```

Reset both queues (call on app/window init and shutdown).

---

### `pending_events` <a id="pending_events"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pending_events(): list
```

The current frame's event list. Returns a copy — read-only for consumers,
safe to hold across the next pump_events() (which replaces event_queue).
Every consumer sees the same stream.

---

### `pump_events` <a id="pump_events"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pump_events(): nil
```

pump_events builds this frame's queue: it merges injected_events (synthetic
pushes since the last pump) with freshly decoded native events from
gg.poll_events(), then clears injected_events. It is the ONLY caller of
gg.poll_events() above the gg layer — and the frame-publish boundary on the
GPU backend — so it must run exactly once per frame.

---

### `push_event` <a id="push_event"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn push_event(event: Event): nil
```

Queue a synthetic event for delivery at the next pump_events().

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


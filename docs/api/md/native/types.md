# API Documentation: `types.lm`

## Overview

std.native.types - Shared windowing/event types for the pure-Lymar
native backend (std.native.*). Every platform module (win32, linux,
macos, android) produces these types so std.app / std.events can
consume any backend interchangeably.

All handles are raw pointer-sized integers (ffi.pubptr-compatible).
No `any` in the hot path: events are a fixed-shape frame.

## Symbols

- **Frame**: [`Event`](#Event)
- **Function**: [`event_none`](#event_none)
- **Frame**: [`Window`](#Window)

---

### `Event` <a id="Event"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Event
```

A single input/window event. Fields not meaningful for a given kind
are zero. `ch` is a Unicode codepoint for Char events (platforms
decode UTF-16 surrogate pairs / keysyms before filling it).

#### Members

- `var pub kind: EventKind` *(field)*
- `var pub x: int` *(field)*
- `var pub y: int` *(field)*
- `var pub w: int` *(field)*
- `var pub h: int` *(field)*
- `var pub key: int` *(field)*
- `var pub ch: int` *(field)*
- `var pub mods: int` *(field)*
- `var pub buttons: int` *(field)*
- `var pub delta: int` *(field)*
- `var pub handle: int` *(field)*

---

### `event_none` <a id="event_none"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn event_none(): Event
```

Module-level factory: qualified static calls like `Event.none()` do
not lower through the LIR, so callers use `event_none()`.

---

### `Window` <a id="Window"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Window
```

Opaque native window. `handle` is the platform window object
(HWND / X Window / NSWindow* / ANativeWindow*). `id` is a
backend-assigned small integer for app-level bookkeeping.

#### Members

- `var pub handle: int` *(field)*
- `var pub id: int` *(field)*
- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `var pub closed: bool` *(field)*
- `var pub backend: str` *(field)*
- `pub fn is_valid(): bool` *(method)*

---


# API Documentation: `index.lm`

## Overview

std.native - Platform-native windowing backend dispatch.

Selects the concrete backend for the host OS via std.os.identity and
forwards the shared window/event contract. Each backend is a real
implementation over std.ffi - no shims:

  win32.lm    - Win32 user32/kernel32 (WNDCLASSEXA + WndProc callback)
  linux.lm    - X11 via libX11.so (XOpenDisplay/XNextEvent; XWayland
                covers Wayland sessions; native Wayland is separate)
  macos.lm    - Cocoa via libobjc + AppKit (objc_msgSend FFI, struct
                NSRect args, Lymar-defined NSWindowDelegate)
  android.lm  - JNI + ANativeWindow + AInputQueue (libart/libandroid;
                requires a Lymar host Activity supplying the Surface)

Usage:
  import std.native as native;
  var win = native.create_window("app", 800, 600) ? else { ... };
  var ev = native.poll_event(win);

## Symbols

- **Function**: [`backend_name`](#backend_name)
- **Function**: [`available`](#available)
- **Function**: [`create_window`](#create_window)
- **Function**: [`poll_event`](#poll_event)
- **Function**: [`wait_event`](#wait_event)
- **Function**: [`invalidate`](#invalidate)
- **Function**: [`set_title`](#set_title)
- **Function**: [`set_size`](#set_size)
- **Function**: [`client_size`](#client_size)
- **Function**: [`destroy`](#destroy)
- **Function**: [`run_message_loop`](#run_message_loop)

---

### `backend_name` <a id="backend_name"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn backend_name(): str
```

Name of the selected backend, resolved once per process:
"win32", "linux-x11", "macos", "android", or "none".

---

### `available` <a id="available"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn available(): bool
```

True when a usable native backend exists on this host.

---

### `create_window` <a id="create_window"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_window(title: str, width: int, height: int): nt.Window?
```

---

### `poll_event` <a id="poll_event"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn poll_event(win: nt.Window): nt.Event
```

---

### `wait_event` <a id="wait_event"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn wait_event(win: nt.Window): nt.Event
```

---

### `invalidate` <a id="invalidate"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn invalidate(win: nt.Window): nil
```

---

### `set_title` <a id="set_title"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_title(win: nt.Window, title: str): nil
```

---

### `set_size` <a id="set_size"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_size(win: nt.Window, width: int, height: int): nil
```

---

### `client_size` <a id="client_size"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn client_size(win: nt.Window): tuple
```

---

### `destroy` <a id="destroy"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn destroy(win: nt.Window): nil
```

---

### `run_message_loop` <a id="run_message_loop"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn run_message_loop(): nil
```

---


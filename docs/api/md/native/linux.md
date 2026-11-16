# API Documentation: `linux.lm`

## Overview

std.native.linux - Pure-Lymar X11 windowing backend (Linux/BSD).

Implements the std.native.types contract through std.ffi against
libX11.so: XOpenDisplay/XCreateSimpleWindow/XNextEvent/XLookupKeysym.
No C glue, no sokol. Wayland is a separate display protocol and is
NOT covered here - X11 (incl. XWayland) is the Linux backend.

Design mirrors std.native.win32: per-window control blocks and event
rings live in ffi.alloc'd raw memory so no Lymar heap objects are
touched from native callbacks (X11 needs no callbacks - events are
pulled via XNextEvent/XPending in normal VM context).

XEvent union (512-byte buffer used; LP64 layout); fields read via ffi.load_* at fixed
offsets (xproto.h, LP64):
  type i32@0, serial u64@8, send_event i32@16, display ptr@24,
  union@32: every member begins with Display* @32.
  XKeyEvent:      root@40 sub@48 time@56 x@64 y@68 x_root@72
                  y_root@76 state@80 keycode@84 same@88
  XButtonEvent:   root@40 event@48 child@56 time@64 x@72 y@76
                  x_root@80 y_root@84 state@88 button@92 same@96
  XMotionEvent:   root@40 event@48 child@56 time@64 x@72 y@76
                  x_root@80 y_root@84 state@88 hint@92 same@96
  XConfigureEvent:event@40 window@48 x@56 y@60 w@64 h@68
  XClientMessage: window@40 msgtype@48 format@56 data@64
  XExposeEvent:   event@40 window@48 x@56 y@60 w@64 h@68
  XFocusEvent:    event@40 window@48 mode@56 detail@60

## Symbols

- **Function**: [`keep`](#keep)
- **Function**: [`xsym`](#xsym)
- **Function**: [`call_i64`](#call_i64)
- **Function**: [`call_i32`](#call_i32)
- **Function**: [`call_i64_ret`](#call_i64_ret)
- **Function**: [`call_void`](#call_void)
- **Function**: [`cstr`](#cstr)
- **Function**: [`p2i`](#p2i)
- **Function**: [`cb_load`](#cb_load)
- **Function**: [`cb_store`](#cb_store)
- **Function**: [`find_block`](#find_block)
- **Function**: [`active_window_count`](#active_window_count)
- **Function**: [`ring_push`](#ring_push)
- **Function**: [`kind_from_int`](#kind_from_int)
- **Function**: [`block_pop_event`](#block_pop_event)
- **Function**: [`xev_field`](#xev_field)
- **Function**: [`xev_i32`](#xev_i32)
- **Function**: [`xmods`](#xmods)
- **Function**: [`utf8_first`](#utf8_first)
- **Function**: [`translate_xevent`](#translate_xevent)
- **Function**: [`ensure_display`](#ensure_display)
- **Function**: [`available`](#available)
- **Function**: [`next_window_id`](#next_window_id)
- **Function**: [`add_window_block`](#add_window_block)
- **Function**: [`create_window`](#create_window)
- **Function**: [`pump_events`](#pump_events)
- **Function**: [`poll_event`](#poll_event)
- **Function**: [`wait_event`](#wait_event)
- **Function**: [`invalidate`](#invalidate)
- **Function**: [`set_title`](#set_title)
- **Function**: [`set_size`](#set_size)
- **Function**: [`client_size`](#client_size)
- **Function**: [`destroy`](#destroy)
- **Function**: [`run_message_loop`](#run_message_loop)

---

### `keep` <a id="keep"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn keep(p: pubptr): pubptr
```

---

### `xsym` <a id="xsym"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn xsym(name: str): int
```

---

### `call_i64` <a id="call_i64"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn call_i64(fptr: int, args: list): int
```

---

### `call_i32` <a id="call_i32"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn call_i32(fptr: int, args: list): int
```

---

### `call_i64_ret` <a id="call_i64_ret"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn call_i64_ret(fptr: int, args: list, ret: int): int
```

---

### `call_void` <a id="call_void"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn call_void(fptr: int, args: list): nil
```

---

### `cstr` <a id="cstr"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn cstr(s: str): int
```

---

### `p2i` <a id="p2i"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn p2i(p: int): int
```

---

### `cb_load` <a id="cb_load"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn cb_load(block: int, off: int): int
```

---

### `cb_store` <a id="cb_store"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn cb_store(block: int, off: int, v: int): nil
```

---

### `find_block` <a id="find_block"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn find_block(xwin: int): int
```

---

### `active_window_count` <a id="active_window_count"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn active_window_count(): int
```

---

### `ring_push` <a id="ring_push"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn ring_push(block: int, kind: int, x: int, y: int, w: int, h: int, key: int, ch: int, mods: int, buttons: int, delta: int): nil
```

---

### `kind_from_int` <a id="kind_from_int"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn kind_from_int(k: int): nt.EventKind
```

---

### `block_pop_event` <a id="block_pop_event"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn block_pop_event(block: int): any
```

---

### `xev_field` <a id="xev_field"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn xev_field(buf: int, off: int): int
```

---

### `xev_i32` <a id="xev_i32"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn xev_i32(buf: int, off: int): int
```

---

### `xmods` <a id="xmods"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn xmods(state: int): int
```

Map X11 modifier state bits to MOD_*.

---

### `utf8_first` <a id="utf8_first"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn utf8_first(buf: int, n: int): int
```

Decode the first UTF-8 codepoint from a byte buffer (XLookupString out).

---

### `translate_xevent` <a id="translate_xevent"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn translate_xevent(buf: int): bool
```

Translate one filled XEvent (512B buffer at `buf`) into ring_push calls.
Returns true if the event was consumed for a known window.

---

### `ensure_display` <a id="ensure_display"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn ensure_display(): int
```

Ensure display connection + per-window event buffer.

---

### `available` <a id="available"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn available(): bool
```

---

### `next_window_id` <a id="next_window_id"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn next_window_id(): int
```

---

### `add_window_block` <a id="add_window_block"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn add_window_block(xwin: int, width: int, height: int): int
```

---

### `create_window` <a id="create_window"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_window(title: str, width: int, height: int): nt.Window?
```

---

### `pump_events` <a id="pump_events"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn pump_events(blocking: int): nil
```

Poll all displays' pending events, translating into rings.

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

X11 event loop: pump until all windows closed.

---


# API Documentation: `macos.lm`

## Overview

std.native.macos - Pure-Lymar macOS windowing backend (Cocoa/ObjC).

Implements the std.native.types contract through std.ffi:
  - libobjc.dylib: objc_getClass / sel_registerName / objc_msgSend
    / objc_msgSend_stret / class_addMethod (for a Lymar-defined
    NSWindowDelegate giving us windowShouldClose/windowDidResize)
  - AppKit.framework loaded dynamically (no link-time dependency)
  - NSRect-by-value arguments via ffi struct support
    ([ffi.TYPE_STRUCT, ffi.TYPE_F64 x4])

No C glue, no sokol. The event pump pulls NSEvents via
-[NSApplication nextEventMatchingMask:untilDate:inMode:dequeue:].

Control blocks + event rings are ffi.alloc'd raw memory so native
callbacks never touch Lymar heap objects (same discipline as
std.native.win32/linux).

## Symbols

- **Function**: [`keep`](#keep)
- **Function**: [`asym`](#asym)
- **Function**: [`objc_sym`](#objc_sym)
- **Function**: [`appkit_sym`](#appkit_sym)
- **Function**: [`call_i64`](#call_i64)
- **Function**: [`call_i64_ret`](#call_i64_ret)
- **Function**: [`call_void`](#call_void)
- **Function**: [`cstr`](#cstr)
- **Function**: [`p2i`](#p2i)
- **Function**: [`cb_load`](#cb_load)
- **Function**: [`cb_store`](#cb_store)
- **Function**: [`msg_fn`](#msg_fn)
- **Function**: [`msgstret_fn`](#msgstret_fn)
- **Function**: [`msg0`](#msg0)
- **Function**: [`msg0_ret`](#msg0_ret)
- **Function**: [`msg1i`](#msg1i)
- **Function**: [`msg1i_ret`](#msg1i_ret)
- **Function**: [`msg2i`](#msg2i)
- **Function**: [`msg3i`](#msg3i)
- **Function**: [`msg_stret0`](#msg_stret0)
- **Function**: [`msg_stret1`](#msg_stret1)
- **Function**: [`sel`](#sel)
- **Function**: [`find_block`](#find_block)
- **Function**: [`active_window_count`](#active_window_count)
- **Function**: [`ring_push`](#ring_push)
- **Function**: [`kind_from_int`](#kind_from_int)
- **Function**: [`block_pop_event`](#block_pop_event)
- **Function**: [`delegate_window_should_close`](#delegate_window_should_close)
- **Function**: [`delegate_window_did_resize`](#delegate_window_did_resize)
- **Function**: [`ensure_classes`](#ensure_classes)
- **Function**: [`available`](#available)
- **Function**: [`next_window_id`](#next_window_id)
- **Function**: [`make_nsstring`](#make_nsstring)
- **Function**: [`add_window_block`](#add_window_block)
- **Function**: [`ensure_delegate`](#ensure_delegate)
- **Function**: [`create_window`](#create_window)
- **Function**: [`pump_events`](#pump_events)
- **Function**: [`nsevent_type`](#nsevent_type)
- **Function**: [`translate_nsevent`](#translate_nsevent)
- **Function**: [`nmods`](#nmods)
- **Function**: [`utf8_first`](#utf8_first)
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

### `asym` <a id="asym"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn asym(lib: int, name: str): int
```

---

### `objc_sym` <a id="objc_sym"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn objc_sym(name: str): int
```

---

### `appkit_sym` <a id="appkit_sym"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn appkit_sym(name: str): int
```

---

### `call_i64` <a id="call_i64"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn call_i64(fptr: int, args: list): int
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

### `msg_fn` <a id="msg_fn"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn msg_fn(): int
```

---

### `msgstret_fn` <a id="msgstret_fn"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn msgstret_fn(): int
```

---

### `msg0` <a id="msg0"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn msg0(obj: int, sel: int): int
```

---

### `msg0_ret` <a id="msg0_ret"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn msg0_ret(obj: int, sel: int, ret: int): int
```

---

### `msg1i` <a id="msg1i"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn msg1i(obj: int, sel: int, a: int): int
```

---

### `msg1i_ret` <a id="msg1i_ret"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn msg1i_ret(obj: int, sel: int, a: int, ret: int): int
```

---

### `msg2i` <a id="msg2i"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn msg2i(obj: int, sel: int, a: int, b: int): int
```

---

### `msg3i` <a id="msg3i"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn msg3i(obj: int, sel: int, a: int, b: int, c: int): int
```

---

### `msg_stret0` <a id="msg_stret0"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn msg_stret0(out: int, obj: int, sel: int): nil
```

stret variant: struct return written to `out` buffer.

---

### `msg_stret1` <a id="msg_stret1"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn msg_stret1(out: int, obj: int, sel: int, a: int): nil
```

---

### `sel` <a id="sel"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn sel(name: str): int
```

---

### `find_block` <a id="find_block"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn find_block(nswindow: int): int
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

### `delegate_window_should_close` <a id="delegate_window_should_close"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn delegate_window_should_close(self_obj: int, _cmd: int, sender: int): int
```

windowShouldClose:(id)sender -> BOOL. Push Close, allow close.

---

### `delegate_window_did_resize` <a id="delegate_window_did_resize"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn delegate_window_did_resize(self_obj: int, _cmd: int, sender: int): nil
```

windowDidResize:(id)sender -> void. Push Resize with new size.

---

### `ensure_classes` <a id="ensure_classes"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn ensure_classes(): int
```

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

### `make_nsstring` <a id="make_nsstring"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn make_nsstring(s: str): int
```

---

### `add_window_block` <a id="add_window_block"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn add_window_block(nswindow: int, width: int, height: int): int
```

---

### `ensure_delegate` <a id="ensure_delegate"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn ensure_delegate(): int
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

Pump one batch of NSEvents into rings. blocking=1 uses distantFuture.

---

### `nsevent_type` <a id="nsevent_type"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn nsevent_type(ev: int): int
```

---

### `translate_nsevent` <a id="translate_nsevent"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn translate_nsevent(ev: int): bool
```

---

### `nmods` <a id="nmods"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn nmods(flags: int): int
```

---

### `utf8_first` <a id="utf8_first"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn utf8_first(buf: int): int
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


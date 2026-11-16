# API Documentation: `android.lm`

## Overview

std.native.android - Pure-Lymar Android windowing backend (NDK).

Implements the std.native.types contract through std.ffi:
  - JNI via JNI_GetCreatedJavaVMs / AttachCurrentThread (libart.so)
  - ANativeWindow from a Surface jobject (libandroid.so)
  - ANativeWindow_lock/unlock for the framebuffer
  - ALooper/AInputQueue for the event stream (libandroid.so)

No C glue, no sokol. The Lymar process runs inside ART; a Java host
Activity supplies the Surface via set_native_surface(env, surface).
All FFI args are scalars/pointers - no struct-by-value needed.

Control blocks + event rings are ffi.alloc'd raw memory (same design
as std.native.win32/linux) so native callbacks never touch Lymar
heap objects.

## Symbols

- **Function**: [`keep`](#keep)
- **Function**: [`asym`](#asym)
- **Function**: [`art_sym`](#art_sym)
- **Function**: [`and_sym`](#and_sym)
- **Function**: [`call_i64`](#call_i64)
- **Function**: [`call_i64_ret`](#call_i64_ret)
- **Function**: [`call_void`](#call_void)
- **Function**: [`p2i`](#p2i)
- **Function**: [`cb_load`](#cb_load)
- **Function**: [`cb_store`](#cb_store)
- **Function**: [`find_block`](#find_block)
- **Function**: [`ring_push`](#ring_push)
- **Function**: [`kind_from_int`](#kind_from_int)
- **Function**: [`block_pop_event`](#block_pop_event)
- **Function**: [`jni_call`](#jni_call)
- **Function**: [`ensure_jni`](#ensure_jni)
- **Function**: [`set_native_surface`](#set_native_surface)
- **Function**: [`available`](#available)
- **Function**: [`next_window_id`](#next_window_id)
- **Function**: [`create_window`](#create_window)
- **Function**: [`translate_input`](#translate_input)
- **Function**: [`pump_events`](#pump_events)
- **Function**: [`poll_event`](#poll_event)
- **Function**: [`wait_event`](#wait_event)
- **Function**: [`invalidate`](#invalidate)
- **Function**: [`set_title`](#set_title)
- **Function**: [`set_size`](#set_size)
- **Function**: [`client_size`](#client_size)
- **Function**: [`lock_framebuffer`](#lock_framebuffer)
- **Function**: [`unlock_framebuffer`](#unlock_framebuffer)
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
fn asym(lib: str, name: str): int
```

---

### `art_sym` <a id="art_sym"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn art_sym(name: str): int
```

---

### `and_sym` <a id="and_sym"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn and_sym(name: str): int
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
fn find_block(hwnd: int): int
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

### `jni_call` <a id="jni_call"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn jni_call(env: int, slot_index: int, args: list, ret: int): int
```

---

### `ensure_jni` <a id="ensure_jni"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn ensure_jni(): int
```

Attach the current thread to the JavaVM; returns JNIEnv* or 0.

---

### `set_native_surface` <a id="set_native_surface"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_native_surface(env: int, surface: int): nil
```

Called by the Java host Activity when its Surface is created.
env: JNIEnv*, surface: jobject (local ref; we NewGlobalRef it).

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

### `create_window` <a id="create_window"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_window(title: str, width: int, height: int): nt.Window?
```

---

### `translate_input` <a id="translate_input"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn translate_input(block: int, evt: int): bool
```

Decode one AInputEvent into ring_push calls. Returns true if consumed.

---

### `pump_events` <a id="pump_events"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn pump_events(blocking: int): nil
```

Pump available input events into rings. blocking=1 waits on looper.

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

### `lock_framebuffer` <a id="lock_framebuffer"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lock_framebuffer(win: nt.Window): int
```

Lock the framebuffer for software rendering. Returns a buffer info
block pointer (ffi.alloc'd, caller frees) or 0. Fields:
[0] bits ptr  [1] stride(bytes)  [2] width  [3] height  [4] format

---

### `unlock_framebuffer` <a id="unlock_framebuffer"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn unlock_framebuffer(win: nt.Window): nil
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


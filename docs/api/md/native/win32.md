# API Documentation: `win32.lm`

## Overview

std.native.win32 - Pure-Lymar Win32 windowing backend.

Implements the std.native.types contract entirely through std.ffi:
dynamic symbol resolution (user32/kernel32), hand-marshaled
WNDCLASSEXA/MSG structs, and a Lymar WndProc exposed to Windows as a
native trampoline via ffi.create_callback. No C glue, no sokol.

Callback-safety design (important):
  The WndProc runs inside a libffi trampoline while the VM's outer
  frame may hold borrows on Lymar heap objects. Touching frames/lists
  inside the callback raises "Conflicting memory borrow" / "Invalid
  frame receiver". Therefore wnd_proc ONLY performs raw memory ops
  (ffi.load_*/store_*/ptr_add) and foreign_call. All window state and
  event queues live in ffi.alloc'd control blocks; poll_event /
  wait_event decode raw records into nt.Event frames in normal VM
  context where allocation is safe.

Control block (i64 slots, 16 slots = 128 bytes):
  [0] hwnd          [1] next block ptr   [2] ring head
  [3] ring tail     [4] ring count       [5] ring capacity
  [6] closed flag   [7] client width     [8] client height
  [9] ring ptr      [10] high surrogate  [11..15] reserved
Event record (16 i64 slots = 128 bytes):
  [0]kind [1]x [2]y [3]w [4]h [5]key [6]ch [7]mods
  [8]buttons [9]delta [10]handle [11..15]reserved

x64 WNDCLASSEXA layout (80 bytes):
  cbSize u32@0, style u32@4, lpfnWndProc@8, cbClsExtra i16@16,
  cbWndExtra i32@20, hInstance@24, hIcon@32, hCursor@40,
  hbrBackground@48, lpszMenuName@56, lpszClassName@64, hIconSm@72
MSG (48 bytes): hwnd@0, message u32@8, wParam@16, lParam@24,
  time u32@32, pt@36

## Symbols

- **Function**: [`keep`](#keep)
- **Function**: [`u32sym`](#u32sym)
- **Function**: [`k32sym`](#k32sym)
- **Function**: [`call_i64`](#call_i64)
- **Function**: [`call_i32`](#call_i32)
- **Function**: [`call_i64_ret`](#call_i64_ret)
- **Function**: [`call_void`](#call_void)
- **Function**: [`cstr`](#cstr)
- **Function**: [`p2i`](#p2i)
- **Function**: [`s16`](#s16)
- **Function**: [`modifiers`](#modifiers)
- **Function**: [`cb_load`](#cb_load)
- **Function**: [`cb_store`](#cb_store)
- **Function**: [`find_block`](#find_block)
- **Function**: [`active_window_count`](#active_window_count)
- **Function**: [`ring_push`](#ring_push)
- **Function**: [`mouse_buttons`](#mouse_buttons)
- **Function**: [`wndproc_cb`](#wndproc_cb)
- **Function**: [`wnd_proc`](#wnd_proc)
- **Function**: [`available`](#available)
- **Function**: [`next_window_id`](#next_window_id)
- **Function**: [`ensure_class`](#ensure_class)
- **Function**: [`add_window_block`](#add_window_block)
- **Function**: [`create_window`](#create_window)
- **Function**: [`kind_from_int`](#kind_from_int)
- **Function**: [`block_pop_event`](#block_pop_event)
- **Function**: [`poll_event`](#poll_event)
- **Function**: [`wait_event`](#wait_event)
- **Function**: [`wnd_dbg`](#wnd_dbg)
- **Function**: [`pending_dbg`](#pending_dbg)
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

### `u32sym` <a id="u32sym"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn u32sym(name: str): int
```

── Symbol + call helpers ─────────────────────────────────────────────────

---

### `k32sym` <a id="k32sym"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn k32sym(name: str): int
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

Convert a foreign-ptr box to its raw address as an i64. Needed because
ffi.store_i64/to_int cannot read ptr-boxed values; store_ptr + load_i64
round-trips the address bits. Cold path only (block setup).

---

### `s16` <a id="s16"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn s16(v: int): int
```

Sign-extend a 16-bit field packed into a 32-bit LPARAM/WPARAM word.

---

### `modifiers` <a id="modifiers"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn modifiers(): int
```

Modifier bitmask from GetKeyState high bits (foreign calls only).

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

Find control block for hwnd by walking the raw linked list.
Returns block pointer (int) or 0.

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

Push a packed event record into a window's ring. Safe inside wnd_proc:
raw memory only. Drops oldest event when full.

---

### `mouse_buttons` <a id="mouse_buttons"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn mouse_buttons(wp: int): int
```

---

### `wndproc_cb` <a id="wndproc_cb"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn wndproc_cb(): ffi.Callback?
```

---

### `wnd_proc` <a id="wnd_proc"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn wnd_proc(hwnd: int, msg: int, wp: int, lp: int): int
```

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM)
Top-level pub fn: ffi.create_callback resolves it by LIR name.
ONLY raw memory ops + foreign_call inside - see header comment.

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

### `ensure_class` <a id="ensure_class"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn ensure_class(): int
```

---

### `add_window_block` <a id="add_window_block"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn add_window_block(hwnd: int, width: int, height: int): int
```

Allocate + link a control block and its event ring for hwnd.

---

### `create_window` <a id="create_window"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_window(title: str, width: int, height: int): nt.Window?
```

---

### `kind_from_int` <a id="kind_from_int"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn kind_from_int(k: int): nt.EventKind
```

Map raw kind ordinal back to the EventKind enum (explicit chain -
int->enum `as` casts are not guaranteed by the type checker).

---

### `block_pop_event` <a id="block_pop_event"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn block_pop_event(block: int): any
```

Decode the head event record for `block` into an nt.Event (VM ctx).

---

### `poll_event` <a id="poll_event"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn poll_event(win: nt.Window): nt.Event
```

Drain pending events for `win`. Returns EventKind.None when empty.

---

### `wait_event` <a id="wait_event"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn wait_event(win: nt.Window): nt.Event
```

Blocking wait for the next event on `win` (process-wide dispatch).

---

### `wnd_dbg` <a id="wnd_dbg"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn wnd_dbg(win: nt.Window): int
```

---

### `pending_dbg` <a id="pending_dbg"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pending_dbg(win: nt.Window): int
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

Standard blocking message loop; returns when the last window closes
(PostQuitMessage) or the queue reports WM_QUIT.

---


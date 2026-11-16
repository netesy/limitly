# API Documentation: `file_dialog.lm`

## Overview

std/ui/file_dialog.lm
Native file-open dialog. Windows: Win32 GetOpenFileNameW via comdlg32
(std.ffi). Other platforms: library_load fails and pick_file returns
nil — callers should keep a text-entry fallback.

The owner hwnd is normally registered once by std.app at init via
set_owner(); pass an explicit owner to pick_file to override.

## Symbols

- **Function**: [`set_owner`](#set_owner)
- **Function**: [`set_debug`](#set_debug)
- **Function**: [`utf8_at`](#utf8_at)
- **Function**: [`write_wide`](#write_wide)
- **Function**: [`utf16_to_utf8`](#utf16_to_utf8)
- **Function**: [`desktop_hwnd`](#desktop_hwnd)
- **Function**: [`pick_open`](#pick_open)
- **Function**: [`pick_file`](#pick_file)
- **Function**: [`pick_save`](#pick_save)

---

### `set_owner` <a id="set_owner"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_owner(hwnd: int): nil
```

---

### `set_debug` <a id="set_debug"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_debug(v: int): nil
```

---

### `utf8_at` <a id="utf8_at"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn utf8_at(s: str, pos: int): tuple
```

Decode the UTF-8 codepoint starting at byte offset `pos` in `s`.
Returns (codepoint, seq_len); falls back to (0xFFFD, 1) on invalid input.

---

### `write_wide` <a id="write_wide"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn write_wide(buf: ffi.pubptr, s: str): int
```

Write a Lymar str as UTF-16LE into an ffi buffer (zero-terminated).
Returns the number of WCHARs written (excluding terminator).

---

### `utf16_to_utf8` <a id="utf16_to_utf8"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn utf16_to_utf8(wbuf: ffi.pubptr, max_chars: int, out: ffi.pubptr): int
```

UTF-16LE code units -> UTF-8 bytes into out; returns byte length.
Handles BMP codepoints and surrogate pairs.

---

### `desktop_hwnd` <a id="desktop_hwnd"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn desktop_hwnd(): int
```

GetOpenFileNameW fails with CDERR_INITIALIZATION when hwndOwner is NULL
in some contexts — fall back to the desktop window handle.

---

### `pick_open` <a id="pick_open"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn pick_open(owner: int, title: str, save_mode: int): str?
```

OPENFILENAMEW. lStructSize must be 152 — the size Windows validates
against ends at lpTemplateName; larger tails return CDERR_STRUCTSIZE.
lpstrFile buffer: 1024 WCHARs.

---

### `pick_file` <a id="pick_file"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pick_file(owner: int = ..., title: str = ...): str?
```

Open-file dialog. Returns the chosen path, or nil on cancel/failure.

---

### `pick_save` <a id="pick_save"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pick_save(owner: int = ..., title: str = ...): str?
```

Save-file dialog. Returns the chosen path, or nil on cancel/failure.

---


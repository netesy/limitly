# API Documentation: `context.lm`

## Overview

std/ui/context.lm
Shared retained-UI plumbing: one-time init, viewport size, dirty flag,
and UTF-8 helpers. The component tree (std.ui.tree) owns layout,
dispatch, and replay; this module only carries global UI state that
std.app and widgets read.

## Symbols

- **Frame**: [`UIContextState`](#UIContextState)
- **Function**: [`ui_init`](#ui_init)
- **Function**: [`_signal_dirty_cb`](#_signal_dirty_cb)
- **Function**: [`mark_element_dirty`](#mark_element_dirty)
- **Function**: [`set_viewport_size`](#set_viewport_size)
- **Function**: [`get_viewport_width`](#get_viewport_width)
- **Function**: [`get_viewport_height`](#get_viewport_height)
- **Function**: [`codepoint_to_utf8`](#codepoint_to_utf8)
- **Function**: [`utf8_pop_back`](#utf8_pop_back)

---

### `UIContextState` <a id="UIContextState"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame UIContextState
```

#### Members

- `var pub is_initialized: int` *(field)*
- `var pub dirty: int` *(field)*
- `var pub viewport_w: float` *(field)*
- `var pub viewport_h: float` *(field)*

---

### `ui_init` <a id="ui_init"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ui_init(): int
```

---

### `_signal_dirty_cb` <a id="_signal_dirty_cb"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _signal_dirty_cb(): nil
```

---

### `mark_element_dirty` <a id="mark_element_dirty"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mark_element_dirty(element_id: int): nil
```

---

### `set_viewport_size` <a id="set_viewport_size"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_viewport_size(w: float, h: float): nil
```

---

### `get_viewport_width` <a id="get_viewport_width"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_viewport_width(): float
```

---

### `get_viewport_height` <a id="get_viewport_height"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_viewport_height(): float
```

---

### `codepoint_to_utf8` <a id="codepoint_to_utf8"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn codepoint_to_utf8(cp: int): str
```

── UTF-8 Helpers ─────────────────────────────────────────────────────────────

---

### `utf8_pop_back` <a id="utf8_pop_back"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn utf8_pop_back(s: str): str
```

---


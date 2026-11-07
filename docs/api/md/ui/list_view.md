# API Documentation: `list_view.lm`

## Overview

std/ui/list_view - List widget with virtual scrolling for large datasets

## Symbols

- **Frame**: [`VirtualListState`](#VirtualListState)
- **Function**: [`list_view`](#list_view)
- **Function**: [`virtual_list`](#virtual_list)
- **Function**: [`get_visible_range`](#get_visible_range)
- **Function**: [`render_virtual_list`](#render_virtual_list)

---

### `VirtualListState` <a id="VirtualListState"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame VirtualListState
```

Virtual list state for windowed rendering

#### Members

- `var pub scroll_offset: int` *(field)*
- `var pub visible_count: int` *(field)*
- `var pub item_height: float` *(field)*
- `var pub total_items: int` *(field)*
- `pub init()` *(constructor)*

---

### `list_view` <a id="list_view"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn list_view(items: list): ui_types.Widget
```

Create a scrollable list of items

---

### `virtual_list` <a id="virtual_list"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn virtual_list(items: list, item_height: float = ..., max_visible: int = ...): ui_types.Widget
```

Virtual list (windowed) - only renders visible items

---

### `get_visible_range` <a id="get_visible_range"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_visible_range(state: VirtualListState, viewport_height: float): tuple
```

Get visible range for virtual rendering

---

### `render_virtual_list` <a id="render_virtual_list"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn render_virtual_list(items: list, state: VirtualListState, viewport_height: float): list
```

Render only visible items (performance optimization)

---


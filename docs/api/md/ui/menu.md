# API Documentation: `menu.lm`

## Overview

std/ui/menu - Dropdown and context menus

## Symbols

- **Frame**: [`MenuItem`](#MenuItem)
- **Function**: [`menu`](#menu)
- **Function**: [`menu_items`](#menu_items)
- **Function**: [`context_menu`](#context_menu)
- **Function**: [`dropdown_menu`](#dropdown_menu)

---

### `MenuItem` <a id="MenuItem"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame MenuItem
```

Menu item frame

#### Members

- `var pub label: str` *(field)*
- `var pub icon: str` *(field)*
- `var pub action: any` *(field)*
- `var pub enabled: bool` *(field)*
- `pub init(lbl: str)` *(constructor)*

---

### `menu` <a id="menu"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn menu(items: list, on_select: any = ...): ui_types.Widget
```

Create a simple dropdown menu from items

---

### `menu_items` <a id="menu_items"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn menu_items(items: list): ui_types.Widget
```

Create menu from MenuItems

---

### `context_menu` <a id="context_menu"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn context_menu(x: float, y: float, items: list, on_select: any = ...): ui_types.Widget
```

Context menu (positioned absolutely)

---

### `dropdown_menu` <a id="dropdown_menu"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dropdown_menu(button_label: str, items: list, on_select: any = ...): ui_types.Widget
```

Dropdown menu button

---


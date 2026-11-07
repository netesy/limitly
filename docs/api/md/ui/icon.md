# API Documentation: `icon.lm`

## Overview

std/ui/icon - Icon widget with Unicode symbols

## Symbols

- **Function**: [`icon`](#icon)
- **Function**: [`icon_button`](#icon_button)

---

### `icon` <a id="icon"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn icon(glyph: str, size: float = ..., color_val: color.Color = ...): ui_types.Widget
```

Create an icon widget

---

### `icon_button` <a id="icon_button"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn icon_button(glyph: str, label: str = ..., on_click: any = ..., size: float = ...): ui_types.Widget
```

Icon button (icon + optional label)

---


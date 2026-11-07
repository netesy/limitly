# API Documentation: `text_layout.lm`

## Overview

std/graphics/text_layout.lm
Text Layout submodule for std.graphics. 2D/3D graphics abstractions, canvases, shaders, and rendering pipelines.

## Symbols

- **Frame**: [`TextLayout`](#TextLayout)
- **Function**: [`hit_test_line`](#hit_test_line)
- **Function**: [`hit_test_multiline`](#hit_test_multiline)

---

### `TextLayout` <a id="TextLayout"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TextLayout
```

#### Members

- `var pub text: str` *(field)*
- `var pub font_val: font.Font` *(field)*
- `var pub max_width: float` *(field)*
- `pub init()` *(constructor)*

---

### `hit_test_line` <a id="hit_test_line"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hit_test_line(line_text: str, click_x: float, scale: int = ...): int
```

---

### `hit_test_multiline` <a id="hit_test_multiline"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hit_test_multiline(lines: list, click_x: float, click_y: float, line_height: float, scale: int = ...): list
```

---


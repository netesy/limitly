# API Documentation: `font.lm`

## Overview

std/image/font.lm
TrueType Font loading, rasterization, and system font detection using stb_truetype.

## Symbols

- **Frame**: [`Metrics`](#Metrics)
- **Frame**: [`Font`](#Font)
- **Function**: [`detect_system_font`](#detect_system_font)
- **Function**: [`load_font`](#load_font)
- **Function**: [`load_system_font`](#load_system_font)

---

### `Metrics` <a id="Metrics"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Metrics
```

#### Members

- `var pub ascent: float` *(field)*
- `var pub descent: float` *(field)*
- `var pub line_gap: float` *(field)*
- `var pub line_height: float` *(field)*
- `pub init()` *(constructor)*

---

### `Font` <a id="Font"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Font
```

#### Members

- `var pub handle: int` *(field)*
- `var pub path: str` *(field)*
- `var pub is_valid: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn free(): nil` *(method)*
- `pub fn text_width(text: str): float` *(method)*
- `pub fn text_height(text: str): float` *(method)*
- `pub fn render(text: str): image.Image?` *(method)*

---

### `detect_system_font` <a id="detect_system_font"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn detect_system_font(preferred_name: str = ...): str
```

---

### `load_font` <a id="load_font"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_font(filepath: str): Font?
```

---

### `load_system_font` <a id="load_system_font"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_system_font(preferred_name: str = ...): Font?
```

---


# API Documentation: `theme.lm`

## Overview

std/ui/theme - Design tokens and theming system

## Symbols

- **Frame**: [`ColorPalette`](#ColorPalette)
- **Frame**: [`SpacingTokens`](#SpacingTokens)
- **Frame**: [`TypographyTokens`](#TypographyTokens)
- **Frame**: [`ShapeTokens`](#ShapeTokens)
- **Frame**: [`Theme`](#Theme)

---

### `ColorPalette` <a id="ColorPalette"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ColorPalette
```

Color palette token

#### Members

- `var pub primary: ui_types.Color` *(field)*
- `var pub secondary: ui_types.Color` *(field)*
- `var pub tertiary: ui_types.Color` *(field)*
- `var pub background: ui_types.Color` *(field)*
- `var pub surface: ui_types.Color` *(field)*
- `var pub surface_variant: ui_types.Color` *(field)*
- `var pub error: ui_types.Color` *(field)*
- `var pub success: ui_types.Color` *(field)*
- `var pub warning: ui_types.Color` *(field)*
- `var pub info: ui_types.Color` *(field)*
- `var pub text_primary: ui_types.Color` *(field)*
- `var pub text_secondary: ui_types.Color` *(field)*
- `var pub border: ui_types.Color` *(field)*
- `var pub focus_ring: ui_types.Color` *(field)*
- `pub init()` *(constructor)*

---

### `SpacingTokens` <a id="SpacingTokens"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame SpacingTokens
```

Spacing tokens

#### Members

- `var pub xs: float` *(field)*
- `var pub sm: float` *(field)*
- `var pub md: float` *(field)*
- `var pub lg: float` *(field)*
- `var pub xl: float` *(field)*
- `pub init()` *(constructor)*

---

### `TypographyTokens` <a id="TypographyTokens"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TypographyTokens
```

Typography tokens

#### Members

- `var pub font_family: str` *(field)*
- `var pub display_size: float` *(field)*
- `var pub headline_size: float` *(field)*
- `var pub title_size: float` *(field)*
- `var pub body_size: float` *(field)*
- `var pub label_size: float` *(field)*
- `pub init()` *(constructor)*

---

### `ShapeTokens` <a id="ShapeTokens"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ShapeTokens
```

Border radius tokens

#### Members

- `var pub corner_xs: float` *(field)*
- `var pub corner_sm: float` *(field)*
- `var pub corner_md: float` *(field)*
- `var pub corner_lg: float` *(field)*
- `pub init()` *(constructor)*

---

### `Theme` <a id="Theme"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Theme
```

Complete theme

#### Members

- `var pub colors: ColorPalette` *(field)*
- `var pub spacing: SpacingTokens` *(field)*
- `var pub typography: TypographyTokens` *(field)*
- `var pub shape: ShapeTokens` *(field)*
- `pub init()` *(constructor)*

---


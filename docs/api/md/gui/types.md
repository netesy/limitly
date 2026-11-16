# API Documentation: `types.lm`

## Overview

std/gui/types.lm
Types and theme/style constants consumed by the std.gui immediate-mode engine.
Re-exports canonical primitives — no local duplicates.

## Symbols

- **Type Alias**: [`GUITheme`](#GUITheme)
- **Function**: [`GUITheme`](#GUITheme)

---

### `GUITheme` <a id="GUITheme"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type GUITheme = Theme
```

GUI-facing alias for the canonical theme type.

---

### `GUITheme` <a id="GUITheme"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn GUITheme(): Theme
```

Constructs a default GUI theme.

---


# API Documentation: `align.lm`

## Overview

std/ui/align - Alignment control.

Alignment is a nominal enum (std.ui.types.Align) dispatched through `match`
at the point a widget packs it. This module re-publishes the enum and its
canonical variants via `pub import ... show` (never `var` aliases, which are
invisible in type position) and adds the layout helper that centres a widget.

## Symbols

- **Function**: [`center`](#center)

---

### `center` <a id="center"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn center(child: ui_types.Widget): ui_types.Widget
```

Wrap `child` in a column centred on the cross axis.

---


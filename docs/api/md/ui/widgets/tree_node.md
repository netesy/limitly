# API Documentation: `tree_node.lm`

## Overview

std/ui/widgets/tree_node.lm
Widget — ported from legacy Fluent TreeNode.
Labeled row that expands/collapses a list of child Components on click.
Children may themselves be TreeNodes (recursive trees). Open state is a
plain int field plus an optional BoolSignal.

## Symbols

- **Frame**: [`TreeNode`](#TreeNode)
- **Function**: [`tree_node`](#tree_node)

---

### `TreeNode` <a id="TreeNode"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TreeNode
```

#### Members

- `var pub label: str` *(field)*
- `var pub children: list` *(field)*
- `var pub is_open: int` *(field)*
- `var pub open_sig: state.BoolSignal?` *(field)*
- `var pub text: color.Color` *(field)*
- `var pub text2: color.Color` *(field)*
- `var pub accent: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub row_h: float` *(field)*
- `var pub indent: float` *(field)*
- `var pub _cur: float` *(field)*
- `var pub _cw: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(c: comp.Component): nil` *(method)*
- `pub fn bind_open(sig: state.BoolSignal): nil` *(method)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn child_count(): int` *(method)*
- `pub fn child_at(i: int): any` *(method)*
- `fn open_now(): int` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): comp.Size` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `tree_node` <a id="tree_node"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tree_node(lbl: str = ..., default_open: bool = ...): TreeNode
```

---


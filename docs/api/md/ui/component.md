# API Documentation: `component.lm`

## Overview

std/ui/component.lm
Modern retained-UI core (docs/ui.md M1–M3).

The Component contract: every widget implements kind/measure/arrange/
paint/on_event/bounds. Missing a pass is a compile error, not a runtime
nil. Children are [Component] trait objects — the tree level is
type-erased by necessity (no runtime generics).

Compiler constraint driving the signatures: trait-object dispatch cannot
take managed (frame) arguments — the ownership checker cannot prove
contracts through dynamic calls. So measure/arrange/on_event pass scalars
and enums only, and paint() emits into the shared dl.paint_ctx draw list
instead of receiving one.

Frame→trait coercion snapshots the top-level frame but SHARES
frame-typed fields (verified). Mutable/shared state therefore lives in
fields — signals, sub-frames — never in the widget's own scalar fields.
External code takes `var r = widget.rect` / `var s = widget.text_sig`
BEFORE add(); those aliases stay live inside the tree.

Three passes per frame (see std/ui/tree.lm):
  measure — child reports intrinsic Size under min/max constraints
  arrange — parent assigns each child a Rect (via arrange)
  paint   — widget draws into paint_ctx.dl using its Rect
  on_event— hit-test against bounds(), reverse paint order = topmost

## Symbols

- **Frame**: [`Size`](#Size)
- **Frame**: [`Rect`](#Rect)
- **Frame**: [`Placed`](#Placed)
- **Frame**: [`TextBound`](#TextBound)
- **Trait**: [`Component`](#Component)
- **Function**: [`next_widget_id`](#next_widget_id)
- **Frame**: [`Label`](#Label)
- **Function**: [`label`](#label)

---

### `Size` <a id="Size"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Size
```

#### Members

- `var pub w: float` *(field)*
- `var pub h: float` *(field)*
- `pub init()` *(constructor)*

---

### `Rect` <a id="Rect"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Rect
```

Placed rectangle — output of the arrange step. arrange() mutates the
Rect IN PLACE (never rebinds) so aliases taken before add() stay live.

#### Members

- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub w: float` *(field)*
- `var pub h: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn contains(px: float, py: float): bool` *(method)*

---

### `Placed` <a id="Placed"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Placed
```

#### Members

- `var pub rect: Rect` *(field)*
- `var pub id: int` *(field)*
- `pub fn widget_id(): int` *(method)*
- `pub fn arrange(x: float, y: float, w: float, h: float): nil` *(method)*
- `pub fn bounds(): Rect` *(method)*
- `pub fn child_count(): int` *(method)*
- `pub fn child_at(i: int): any` *(method)*

---

### `TextBound` <a id="TextBound"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TextBound
```

#### Members

- `var pub text: str` *(field)*
- `var pub text_sig: state.StrSignal?` *(field)*
- `pub fn string_val(): str` *(method)*
- `pub fn bind_text(sig: state.StrSignal): nil` *(method)*

---

### `Component` <a id="Component"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Component
```

#### Members

- `fn kind(): ui_types.WidgetKind` *(method requirement)*
- `fn measure(min_w: float, max_w: float, min_h: float, max_h: float): Size` *(method requirement)*
- `fn arrange(x: float, y: float, w: float, h: float): nil` *(method requirement)*
- `fn paint(): nil` *(method requirement)*
- `fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method requirement)*
- `fn bounds(): Rect` *(method requirement)*
- `fn widget_id(): int` *(method requirement)*
- `fn child_count(): int` *(method requirement)*
- `fn child_at(i: int): any` *(method requirement)*
- `fn on_theme_changed(): nil` *(method requirement)*
- `fn wants_pointer_capture(): int` *(method requirement)*
- `fn on_overlay_dismiss(): nil` *(method requirement)*

---

### `next_widget_id` <a id="next_widget_id"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn next_widget_id(): int
```

---

### `Label` <a id="Label"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Label
```

#### Members

- `var pub fg: color.Color` *(field)*
- `var pub font_scale: float` *(field)*
- `var pub pad_x: float` *(field)*
- `var pub pad_y: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn kind(): ui_types.WidgetKind` *(method)*
- `pub fn on_theme_changed(): nil` *(method)*
- `pub fn on_overlay_dismiss(): nil` *(method)*
- `pub fn wants_pointer_capture(): int` *(method)*
- `pub fn measure(min_w: float, max_w: float, min_h: float, max_h: float): Size` *(method)*
- `pub fn paint(): nil` *(method)*
- `pub fn on_event(t: events.EventType, x: int, y: int, key: int): uievent.EventResult` *(method)*

---

### `label` <a id="label"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn label(txt: str, c: color.Color? = ...): Label
```

---


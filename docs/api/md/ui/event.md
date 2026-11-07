# API Documentation: `event.lm`

## Overview

std/ui/event.lm
Type-Safe Event Handling & Fallible Event Propagation for Lymar UI

Replaces untyped `any` callbacks and sentinel numbers with nominal enums,
exhaustive match dispatch, and Lymar fallible types (`EventResult?`).

A widget stores its callback in the `on_click_action` / `on_change_action`
slot as a `fn(): nil` (the shape the retained renderer already invokes).
`fire_action`/`fire_action_for` route that slot through a fallible pipeline
so the dynamic `any` never leaks past this boundary: it is cast once, guarded,
and a nil/absent handler becomes an `Unhandled` result rather than a nil check
at every call site.

## Symbols

- **Frame**: [`UIEvent`](#UIEvent)
- **Function**: [`make_click_event`](#make_click_event)
- **Function**: [`make_hover_event`](#make_hover_event)
- **Function**: [`make_key_event`](#make_key_event)
- **Function**: [`fire_action`](#fire_action)
- **Function**: [`route`](#route)
- **Function**: [`dispatch_event`](#dispatch_event)

---

### `UIEvent` <a id="UIEvent"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame UIEvent
```

#### Members

- `var pub kind: EventKind` *(field)*
- `var pub target_id: str` *(field)*
- `var pub x: float` *(field)*
- `var pub y: float` *(field)*
- `var pub delta_x: float` *(field)*
- `var pub delta_y: float` *(field)*
- `var pub key_code: int` *(field)*
- `var pub is_shift: bool` *(field)*
- `var pub is_ctrl: bool` *(field)*
- `var pub is_alt: bool` *(field)*
- `pub init(k: EventKind)` *(constructor)*

---

### `make_click_event` <a id="make_click_event"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_click_event(target_id: str, x: float, y: float): UIEvent
```

---

### `make_hover_event` <a id="make_hover_event"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_hover_event(target_id: str, x: float, y: float): UIEvent
```

---

### `make_key_event` <a id="make_key_event"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_key_event(k: EventKind, key: int): UIEvent
```

---

### `fire_action` <a id="fire_action"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fire_action(action): EventResult?
```

Invoke a widget's `fn(): nil` action slot fallibly. A nil action is not an
error condition -- it is simply `Unhandled`, which removes the
`if (w.on_click_action != nil)` guard from every dispatch site.

---

### `route` <a id="route"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn route(handler): EventResult?
```

Route an actionable event: fire the handler if one is bound (best-effort),
then report the event as consumed. A nil handler is not a failure of routing
-- the event was still handled by reaching a target.

---

### `dispatch_event` <a id="dispatch_event"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dispatch_event(evt: UIEvent, handler: any = ...): EventResult?
```

Full fallible pipeline: resolve the target, dispatch on the nominal kind via
`match`, then invoke the handler. Returns `err()` when the event carries no
target so callers can propagate with `?` instead of inspecting fields.

---


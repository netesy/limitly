# API Documentation: `tree.lm`

## Overview

std/ui/tree.lm
M2 frame driver: focus ownership + per-frame update/event dispatch.

update() clears the shared draw list (dl.paint_ctx), arranges the root
to the viewport and paints the whole tree into it. submit() replays it
through std.ui.replay. Widgets never receive the DrawList — they emit
into dl.paint_ctx.dl directly (trait dispatch can't take managed args).

dispatch() routes one std.events.Event: pointer events go through
recursive hit-testing (topmost child wins); keyboard/text events go to
the focused component first, then fall through to the root.

Focus rule: single owner. Clicking inside a widget that claims focus
(TextInput) sets it; any MouseDown that lands outside the focused
widget's bounds clears it.

## Symbols

- **Function**: [`subtree_has_widget`](#subtree_has_widget)
- **Function**: [`find_capture`](#find_capture)
- **Function**: [`push_overlay`](#push_overlay)
- **Function**: [`remove_overlay`](#remove_overlay)
- **Function**: [`request_repaint`](#request_repaint)
- **Function**: [`enable_reactive`](#enable_reactive)
- **Function**: [`on_state_dirty`](#on_state_dirty)
- **Function**: [`set_focus`](#set_focus)
- **Function**: [`clear_focus`](#clear_focus)
- **Function**: [`focused`](#focused)
- **Function**: [`update`](#update)
- **Function**: [`submit`](#submit)
- **Function**: [`dispatch`](#dispatch)
- **Function**: [`find_widget`](#find_widget)
- **Function**: [`apply_theme`](#apply_theme)

---

### `subtree_has_widget` <a id="subtree_has_widget"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn subtree_has_widget(c: comp.Component, id: int): bool
```

True when `id` is `c` itself or any descendant (child_at walk).

---

### `find_capture` <a id="find_capture"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn find_capture(c: comp.Component): int
```

Deepest/topmost component wanting capture, or 0. Children are walked
in reverse paint order so the visually-topmost claimant wins.

---

### `push_overlay` <a id="push_overlay"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn push_overlay(c: comp.Component): nil
```

---

### `remove_overlay` <a id="remove_overlay"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn remove_overlay(c: comp.Component): nil
```

---

### `request_repaint` <a id="request_repaint"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn request_repaint(): nil
```

---

### `enable_reactive` <a id="enable_reactive"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn enable_reactive(): nil
```

Wire signal notifications into the dirty flag AND enable repaint
elision. Call once at startup:
tree.enable_reactive();

---

### `on_state_dirty` <a id="on_state_dirty"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn on_state_dirty(): nil
```

---

### `set_focus` <a id="set_focus"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set_focus(c: comp.Component): nil
```

---

### `clear_focus` <a id="clear_focus"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn clear_focus(): nil
```

---

### `focused` <a id="focused"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn focused(): comp.Component?
```

---

### `update` <a id="update"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn update(root: comp.Component, w: float, h: float): nil
```

Arrange the root to the full viewport and paint the tree into the
shared paint-context draw list. Call submit() to replay it to gg.

---

### `submit` <a id="submit"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn submit(): nil
```

Replay the painted frame to the GPU backend.

---

### `dispatch` <a id="dispatch"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn dispatch(root: comp.Component, ev: events.Event): uievent.EventResult
```

Route one event through the tree. Returns the deepest handler's result.

---

### `find_widget` <a id="find_widget"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn find_widget(root: comp.Component, id: int): any
```

Depth-first search for a widget by its stable construction-time id
(component.next_widget_id). Returns the Component as `any`, or nil when
absent — `T?`/`Component?` returns ok-wrap the trait object and break
later dispatch, so `any` is the honest optional-trait channel here.
Walks through child_count/child_at across Flow/Container/ScrollView.

---

### `apply_theme` <a id="apply_theme"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn apply_theme(root: comp.Component): nil
```

Walk the tree calling on_theme_changed() on every component, then
request a repaint. Pair with uitheme.set_*/set_theme — widgets that
snapshot palette() at init re-apply theme-derived fields here.

---


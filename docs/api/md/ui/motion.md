# API Documentation: `motion.lm`

## Overview

std/ui/motion.lm
Minimal tween driver for widget animation. Widgets call
animate_to(id, prop, target, dur) when a visual state changes and read
value(id, prop, fallback) each paint — the returned float eases toward
the target. app.run_frame_step ticks the registry; while any tween is
live it requests repaints so animation actually advances under elision.

prop is an opaque per-widget slot (0=primary, 1=secondary, ...).
Everything is float math — no allocations on the hot path beyond the
small tween list itself.

## Symbols

- **Frame**: [`Tween`](#Tween)
- **Function**: [`ease_out`](#ease_out)
- **Function**: [`tick`](#tick)
- **Function**: [`animate_to`](#animate_to)
- **Function**: [`value`](#value)

---

### `Tween` <a id="Tween"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Tween
```

#### Members

- `var pub owner: int` *(field)*
- `var pub prop: int` *(field)*
- `var pub start_v: float` *(field)*
- `var pub to: float` *(field)*
- `var pub t: float` *(field)*
- `var pub dur: float` *(field)*

---

### `ease_out` <a id="ease_out"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn ease_out(t: float): float
```

---

### `tick` <a id="tick"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tick(dt: float): nil
```

Advance all tweens by dt seconds; request repaint while any are live.

---

### `animate_to` <a id="animate_to"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn animate_to(owner: int, prop: int, target: float, dur: float, cur: float): nil
```

Start (or retarget) a tween. `cur` is the value to start from — callers
pass value(id, prop, target) so retargets are seamless.

---

### `value` <a id="value"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn value(owner: int, prop: int, fallback: float): float
```

Current eased value for (owner, prop); `fallback` when no tween exists.

---


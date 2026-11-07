# API Documentation: `index.lm`

## Overview

std/animation/index.lm
Shared Generic Animation Core Engine for Lymar
Time-based, interruptible, easing curves, spring physics, transitions, keyframes, composition, and ID-keyed state store

## Symbols

- **Frame**: [`Preferences`](#Preferences)
- **Function**: [`apply_easing`](#apply_easing)
- **Function**: [`apply_easing_curve`](#apply_easing_curve)
- **Frame**: [`Spring`](#Spring)
- **Function**: [`lerp_float`](#lerp_float)
- **Function**: [`lerp_rgba`](#lerp_rgba)
- **Frame**: [`Keyframe`](#Keyframe)
- **Frame**: [`Keyframes`](#Keyframes)
- **Frame**: [`PropertyAnimation`](#PropertyAnimation)
- **Frame**: [`Sequence`](#Sequence)
- **Function**: [`sequence`](#sequence)
- **Frame**: [`Parallel`](#Parallel)
- **Function**: [`parallel_group`](#parallel_group)
- **Frame**: [`Transition`](#Transition)
- **Frame**: [`Animator`](#Animator)
- **Frame**: [`IMGUIAnimationState`](#IMGUIAnimationState)
- **Frame**: [`IMGUIAnimationStore`](#IMGUIAnimationStore)

---

### `Preferences` <a id="Preferences"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Preferences
```

#### Members

- `var pub enabled: bool` *(field)*
- `var pub reduce_motion: bool` *(field)*
- `var pub duration_scale: float` *(field)*
- `pub init()` *(constructor)*

---

### `apply_easing` <a id="apply_easing"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn apply_easing(t: float, easing: Easing): float
```

---

### `apply_easing_curve` <a id="apply_easing_curve"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn apply_easing_curve(t: float, easing: Easing): float
```

---

### `Spring` <a id="Spring"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Spring
```

#### Members

- `var pub stiffness: float` *(field)*
- `var pub damping: float` *(field)*
- `var pub mass: float` *(field)*
- `var pub velocity: float` *(field)*
- `pub init()` *(constructor)*
- `pub fn update(current: float, target: float, dt: float): float` *(method)*
- `pub fn is_at_rest(current: float, target: float): bool` *(method)*

---

### `lerp_float` <a id="lerp_float"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lerp_float(a: float, b: float, t: float): float
```

---

### `lerp_rgba` <a id="lerp_rgba"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lerp_rgba(r1: float, g1: float, b1: float, a1: float, r2: float, g2: float, b2: float, a2: float, t: float): list
```

---

### `Keyframe` <a id="Keyframe"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Keyframe
```

#### Members

- `var pub progress: float` *(field)*
- `var pub value: float` *(field)*
- `pub init()` *(constructor)*

---

### `Keyframes` <a id="Keyframes"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Keyframes
```

#### Members

- `var pub frames: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(progress: float, value: float): Keyframes` *(method)*
- `pub fn evaluate(t: float): float` *(method)*

---

### `PropertyAnimation` <a id="PropertyAnimation"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame PropertyAnimation
```

#### Members

- `var pub start_val: float` *(field)*
- `var pub target_val: float` *(field)*
- `var pub current_val: float` *(field)*
- `var pub duration: float` *(field)*
- `var pub elapsed: float` *(field)*
- `var pub delay: float` *(field)*
- `var pub easing: Easing` *(field)*
- `var pub state: State` *(field)*
- `var pub is_spring: bool` *(field)*
- `var pub is_repeat: bool` *(field)*
- `var pub is_reverse: bool` *(field)*
- `var pub spring_model: Spring` *(field)*
- `var pub keyframes_model: Keyframes` *(field)*
- `pub init()` *(constructor)*
- `pub fn play(): nil` *(method)*
- `pub fn pause(): nil` *(method)*
- `pub fn resume(): nil` *(method)*
- `pub fn stop(): nil` *(method)*
- `pub fn reset(): nil` *(method)*
- `pub fn set_delay(d: float): PropertyAnimation` *(method)*
- `pub fn reverse(): PropertyAnimation` *(method)*
- `pub fn repeat_mode(): PropertyAnimation` *(method)*
- `pub fn seek(progress: float): float` *(method)*
- `pub fn set_target(new_target: float): nil` *(method)*
- `pub fn update(dt: float): float` *(method)*

---

### `Sequence` <a id="Sequence"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Sequence
```

#### Members

- `var pub anims: list` *(field)*
- `var pub current_idx: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(anim: PropertyAnimation): Sequence` *(method)*
- `pub fn update(dt: float): float` *(method)*

---

### `sequence` <a id="sequence"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sequence(a1: PropertyAnimation, a2: PropertyAnimation): Sequence
```

---

### `Parallel` <a id="Parallel"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Parallel
```

#### Members

- `var pub anims: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(anim: PropertyAnimation): Parallel` *(method)*
- `pub fn update(dt: float): nil` *(method)*
- `pub fn is_completed(): bool` *(method)*

---

### `parallel_group` <a id="parallel_group"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parallel_group(a1: PropertyAnimation, a2: PropertyAnimation): Parallel
```

---

### `Transition` <a id="Transition"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Transition
```

#### Members

- `var pub opacity_anim: PropertyAnimation` *(field)*
- `var pub scale_anim: PropertyAnimation` *(field)*
- `var pub slide_x_anim: PropertyAnimation` *(field)*
- `var pub slide_y_anim: PropertyAnimation` *(field)*
- `var pub active: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn play(): Transition` *(method)*
- `pub fn fade(): Transition` *(method)*
- `pub fn scale(): Transition` *(method)*
- `pub fn slide(): Transition` *(method)*
- `pub fn update(dt: float): nil` *(method)*

---

### `Animator` <a id="Animator"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Animator
```

#### Members

- `var pub active_animations: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn add(anim: PropertyAnimation): PropertyAnimation` *(method)*
- `pub fn update_all(dt: float): nil` *(method)*

---

### `IMGUIAnimationState` <a id="IMGUIAnimationState"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame IMGUIAnimationState
```

#### Members

- `var pub id: str` *(field)*
- `var pub float_anims: dict` *(field)*
- `var pub last_used_frame: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn animate_property(prop_name: str, target: float): float` *(method)*

---

### `IMGUIAnimationStore` <a id="IMGUIAnimationStore"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame IMGUIAnimationStore
```

#### Members

- `var pub states: dict` *(field)*
- `var pub active_ids: list` *(field)*
- `var pub frame_counter: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn get_or_create(id: str): IMGUIAnimationState` *(method)*
- `pub fn step_frame(): nil` *(method)*
- `pub fn prune_stale(): nil` *(method)*

---


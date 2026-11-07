# API Documentation: `particles.lm`

## Overview

std/game/particles.lm
High-performance 2D particle simulation and emitter engine for game effects

## Symbols

- **Frame**: [`Particle`](#Particle)
- **Frame**: [`ParticleEmitter2D`](#ParticleEmitter2D)
- **Function**: [`ParticleEmitter`](#ParticleEmitter)

---

### `Particle` <a id="Particle"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Particle: gtraits.Updatable
```

#### Members

- `var pub pos: types.Vec2` *(field)*
- `var pub vel: types.Vec2` *(field)*
- `var pub acc: types.Vec2` *(field)*
- `var pub color_start: color.Color` *(field)*
- `var pub color_end: color.Color` *(field)*
- `var pub size_start: float` *(field)*
- `var pub size_end: float` *(field)*
- `var pub life: float` *(field)*
- `var pub max_life: float` *(field)*
- `var pub alive: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn spawn(pos: types.Vec2, vel: types.Vec2, acc: types.Vec2, c_start: color.Color, c_end: color.Color, s_start: float, s_end: float, life_span: float): nil` *(method)*
- `pub fn update(dt: float): nil` *(method)*
- `pub fn current_color(): color.Color` *(method)*
- `pub fn current_size(): float` *(method)*

---

### `ParticleEmitter2D` <a id="ParticleEmitter2D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ParticleEmitter2D: gtraits.Updatable, gtraits.Drawable
```

#### Members

- `var pub position: types.Vec2` *(field)*
- `var pub particles: list` *(field)*
- `var pub max_particles: int` *(field)*
- `var pub active: bool` *(field)*
- `var pub emission_rate: float` *(field)*
- `var pub emission_timer: float` *(field)*
- `var pub life_min: float` *(field)*
- `var pub life_max: float` *(field)*
- `var pub speed_min: float` *(field)*
- `var pub speed_max: float` *(field)*
- `var pub angle_min: float` *(field)*
- `var pub angle_max: float` *(field)*
- `var pub gravity: types.Vec2` *(field)*
- `var pub size_start: float` *(field)*
- `var pub size_end: float` *(field)*
- `var pub color_start: color.Color` *(field)*
- `var pub color_end: color.Color` *(field)*
- `var pub rng_state: int` *(field)*
- `pub init()` *(constructor)*
- `fn next_float(): float` *(method)*
- `fn spawn_one(): nil` *(method)*
- `pub fn burst(count: int): nil` *(method)*
- `pub fn update(dt: float): nil` *(method)*
- `pub fn draw(): nil` *(method)*

---

### `ParticleEmitter` <a id="ParticleEmitter"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ParticleEmitter(max_count: int = ...): ParticleEmitter2D
```

---


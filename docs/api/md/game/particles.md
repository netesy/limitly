# API Documentation: `particles.lm`

## Overview

std/game/particles.lm
High-performance SoA 2D particle simulation and emitter engine with zero per-particle allocations.

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

- `var pub pos: Vector2` *(field)*
- `var pub vel: Vector2` *(field)*
- `var pub acc: Vector2` *(field)*
- `var pub color_start: color.Color` *(field)*
- `var pub color_end: color.Color` *(field)*
- `var pub size_start: float` *(field)*
- `var pub size_end: float` *(field)*
- `var pub life: float` *(field)*
- `var pub max_life: float` *(field)*
- `var pub alive: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn spawn(pos: Vector2, vel: Vector2, acc: Vector2, c_start: color.Color, c_end: color.Color, s_start: float, s_end: float, life_span: float): nil` *(method)*
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

- `var pub position: Vector2` *(field)*
- `var pub max_particles: int` *(field)*
- `var pub active: bool` *(field)*
- `var pub px: list` *(field)*
- `var pub py: list` *(field)*
- `var pub vx: list` *(field)*
- `var pub vy: list` *(field)*
- `var pub ax: list` *(field)*
- `var pub ay: list` *(field)*
- `var pub life: list` *(field)*
- `var pub max_life: list` *(field)*
- `var pub s_start: list` *(field)*
- `var pub s_end: list` *(field)*
- `var pub cr0: list` *(field)*
- `var pub cg0: list` *(field)*
- `var pub cb0: list` *(field)*
- `var pub ca0: list` *(field)*
- `var pub cr1: list` *(field)*
- `var pub cg1: list` *(field)*
- `var pub cb1: list` *(field)*
- `var pub ca1: list` *(field)*
- `var pub alive: list` *(field)*
- `var pub emission_rate: float` *(field)*
- `var pub emission_timer: float` *(field)*
- `var pub life_min: float` *(field)*
- `var pub life_max: float` *(field)*
- `var pub speed_min: float` *(field)*
- `var pub speed_max: float` *(field)*
- `var pub angle_min: float` *(field)*
- `var pub angle_max: float` *(field)*
- `var pub gravity: Vector2` *(field)*
- `var pub size_start: float` *(field)*
- `var pub size_end: float` *(field)*
- `var pub color_start: color.Color` *(field)*
- `var pub color_end: color.Color` *(field)*
- `var pub rng_state: int` *(field)*
- `pub init()` *(constructor)*
- `fn next_float(): float` *(method)*
- `fn spawn_one(): nil` *(method)*
- `pub fn burst(count: int): nil` *(method)*
- `pub fn alive_count(): int` *(method)*
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


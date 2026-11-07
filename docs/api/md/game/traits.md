# API Documentation: `traits.lm`

## Overview

std/game/traits.lm
Behavioral contracts for the game loop: things the loop can tick and paint.

## Symbols

- **Trait**: [`Updatable`](#Updatable)
- **Trait**: [`Drawable`](#Drawable)

---

### `Updatable` <a id="Updatable"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Updatable
```

#### Members

- `fn update(dt: float): nil` *(method requirement)*

---

### `Drawable` <a id="Drawable"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Drawable
```

#### Members

- `fn draw(camera: any): nil` *(method requirement)*

---


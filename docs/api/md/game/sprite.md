# API Documentation: `sprite.lm`

## Overview

std/game/sprite.lm
2D Sprites, SpriteSheets, Frame Animations, and Textured Quad Rendering

## Symbols

- **Frame**: [`Texture2D`](#Texture2D)
- **Function**: [`texture2d`](#texture2d)
- **Frame**: [`Sprite`](#Sprite)
- **Function**: [`sprite`](#sprite)
- **Frame**: [`SpriteSheet`](#SpriteSheet)
- **Frame**: [`AnimationClip`](#AnimationClip)
- **Frame**: [`AnimatedSprite`](#AnimatedSprite)

---

### `Texture2D` <a id="Texture2D"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Texture2D
```

#### Members

- `var pub id: int` *(field)*
- `var pub width: int` *(field)*
- `var pub height: int` *(field)*
- `pub init()` *(constructor)*

---

### `texture2d` <a id="texture2d"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn texture2d(id: int, w: int, h: int): Texture2D
```

---

### `Sprite` <a id="Sprite"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Sprite: gtraits.Drawable
```

#### Members

- `var pub texture: Texture2D` *(field)*
- `var pub position: types.Vec2` *(field)*
- `var pub src_rect: types.Rect` *(field)*
- `var pub origin: types.Vec2` *(field)*
- `var pub scale: types.Vec2` *(field)*
- `var pub rotation: float` *(field)*
- `var pub tint: color.Color` *(field)*
- `var pub flip_x: bool` *(field)*
- `var pub flip_y: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn draw(): nil` *(method)*

---

### `sprite` <a id="sprite"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sprite(texture: any = ..., position: any = ...): Sprite
```

---

### `SpriteSheet` <a id="SpriteSheet"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame SpriteSheet
```

#### Members

- `var pub texture: Texture2D` *(field)*
- `var pub cell_width: int` *(field)*
- `var pub cell_height: int` *(field)*
- `var pub columns: int` *(field)*
- `var pub rows: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn get_frame(col: int, row: int): types.Rect` *(method)*
- `pub fn get_frame_index(index: int): types.Rect` *(method)*

---

### `AnimationClip` <a id="AnimationClip"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame AnimationClip
```

#### Members

- `var pub name: str` *(field)*
- `var pub frames: list` *(field)*
- `var pub fps: float` *(field)*
- `var pub loop: bool` *(field)*
- `pub init()` *(constructor)*

---

### `AnimatedSprite` <a id="AnimatedSprite"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame AnimatedSprite: gtraits.Updatable, gtraits.Drawable
```

AnimatedSprite composes Sprite via `embed`: the sprite fields (texture,
position, origin, scale, rotation, tint, flip_x, flip_y) are promoted from
Sprite rather than duplicated, and `src_rect` comes along for free. Sprite's
`draw` is promoted too but immediately shadowed by the own `draw` below
(name-based dedupe), so animation-aware painting wins.

#### Members

- `var pub clips: dict` *(field)*
- `var pub current_clip: str` *(field)*
- `var pub frame_index: int` *(field)*
- `var pub frame_timer: float` *(field)*
- `var pub is_playing: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn add_clip(clip: AnimationClip): nil` *(method)*
- `pub fn play(clip_name: str): nil` *(method)*
- `pub fn pause(): nil` *(method)*
- `pub fn resume(): nil` *(method)*
- `pub fn stop(): nil` *(method)*
- `pub fn update(dt: float): nil` *(method)*
- `pub fn draw(): nil` *(method)*

---


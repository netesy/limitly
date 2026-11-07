# API Documentation: `palette.lm`

## Overview

std/color/palette.lm
Modern UI Color Palette System for Lymar
Provides 11-step shade scales (50 to 950) for modern UI styling and palettes.

## Symbols

- **Frame**: [`Shades`](#Shades)
- **Function**: [`_shade_from_hex`](#_shade_from_hex)
- **Function**: [`slate`](#slate)
- **Function**: [`gray`](#gray)
- **Function**: [`zinc`](#zinc)
- **Function**: [`neutral`](#neutral)
- **Function**: [`stone`](#stone)
- **Function**: [`red`](#red)
- **Function**: [`orange`](#orange)
- **Function**: [`amber`](#amber)
- **Function**: [`yellow`](#yellow)
- **Function**: [`lime`](#lime)
- **Function**: [`green`](#green)
- **Function**: [`emerald`](#emerald)
- **Function**: [`teal`](#teal)
- **Function**: [`cyan`](#cyan)
- **Function**: [`sky`](#sky)
- **Function**: [`blue`](#blue)
- **Function**: [`indigo`](#indigo)
- **Function**: [`violet`](#violet)
- **Function**: [`purple`](#purple)
- **Function**: [`fuchsia`](#fuchsia)
- **Function**: [`pink`](#pink)
- **Function**: [`rose`](#rose)
- **Function**: [`crimson`](#crimson)
- **Function**: [`cool_gray`](#cool_gray)
- **Function**: [`warm_gray`](#warm_gray)
- **Function**: [`shade`](#shade)
- **Function**: [`palette`](#palette)
- **Function**: [`tw`](#tw)

---

### `Shades` <a id="Shades"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Shades
```

#### Members

- `var pub c50: Color` *(field)*
- `var pub c100: Color` *(field)*
- `var pub c200: Color` *(field)*
- `var pub c300: Color` *(field)*
- `var pub c400: Color` *(field)*
- `var pub c500: Color` *(field)*
- `var pub c600: Color` *(field)*
- `var pub c700: Color` *(field)*
- `var pub c800: Color` *(field)*
- `var pub c900: Color` *(field)*
- `var pub c950: Color` *(field)*
- `pub init(h50: int, h100: int, h200: int, h300: int, h400: int, h500: int, h600: int, h700: int, h800: int, h900: int, h950: int)` *(constructor)*
- `pub fn shade(): Color` *(method)*
- `pub fn get(): Color` *(method)*

---

### `_shade_from_hex` <a id="_shade_from_hex"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _shade_from_hex(level: int, h50: int, h100: int, h200: int, h300: int, h400: int, h500: int, h600: int, h700: int, h800: int, h900: int, h950: int): Color
```

---

### `slate` <a id="slate"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn slate(level: int = ...): Color
```

---

### `gray` <a id="gray"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gray(level: int = ...): Color
```

---

### `zinc` <a id="zinc"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn zinc(level: int = ...): Color
```

---

### `neutral` <a id="neutral"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn neutral(level: int = ...): Color
```

---

### `stone` <a id="stone"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stone(level: int = ...): Color
```

---

### `red` <a id="red"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn red(level: int = ...): Color
```

---

### `orange` <a id="orange"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn orange(level: int = ...): Color
```

---

### `amber` <a id="amber"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn amber(level: int = ...): Color
```

---

### `yellow` <a id="yellow"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn yellow(level: int = ...): Color
```

---

### `lime` <a id="lime"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lime(level: int = ...): Color
```

---

### `green` <a id="green"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn green(level: int = ...): Color
```

---

### `emerald` <a id="emerald"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn emerald(level: int = ...): Color
```

---

### `teal` <a id="teal"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn teal(level: int = ...): Color
```

---

### `cyan` <a id="cyan"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cyan(level: int = ...): Color
```

---

### `sky` <a id="sky"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sky(level: int = ...): Color
```

---

### `blue` <a id="blue"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn blue(level: int = ...): Color
```

---

### `indigo` <a id="indigo"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn indigo(level: int = ...): Color
```

---

### `violet` <a id="violet"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn violet(level: int = ...): Color
```

---

### `purple` <a id="purple"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn purple(level: int = ...): Color
```

---

### `fuchsia` <a id="fuchsia"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fuchsia(level: int = ...): Color
```

---

### `pink` <a id="pink"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pink(level: int = ...): Color
```

---

### `rose` <a id="rose"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rose(level: int = ...): Color
```

---

### `crimson` <a id="crimson"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn crimson(level: int = ...): Color
```

---

### `cool_gray` <a id="cool_gray"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cool_gray(level: int = ...): Color
```

---

### `warm_gray` <a id="warm_gray"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn warm_gray(level: int = ...): Color
```

---

### `shade` <a id="shade"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn shade(name: str, level: int = ...): Color
```

---

### `palette` <a id="palette"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn palette(name: str, level: int = ...): Color
```

---

### `tw` <a id="tw"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tw(name: str, level: int = ...): Color
```

---


# API Documentation: `rune.lm`

## Overview

Standard Library Unicode Rune Module

Unicode code point representation and comparison.

## Symbols

- **Function**: [`char_code`](#char_code)
- **Frame**: [`Rune`](#Rune)

---

### `char_code` <a id="char_code"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn char_code(ch: str): int
```

---

### `Rune` <a id="Rune"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Rune: cmp.Comparable
```

Represents a single Unicode character / rune.
Conforms to `Comparable` for alphabetical ordering.

#### Example: Idiomatic Usage

```lymar
var r1 = Rune("a");
var r2 = Rune("b");
var diff = r1.compare(r2); // -1
```

#### Members

- `var pub value: str` *(field)*
- `pub init(value: str)` *(constructor)*
- `pub fn to_string(): str` *(method)*
- `pub fn compare(other: any): int` *(method)*

---


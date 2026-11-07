# API Documentation: `numbers.lm`

## Overview

Standard Library Parse Numbers Submodule

String to integer and floating-point conversion helpers.

## Symbols

- **Function**: [`char_to_digit`](#char_to_digit)
- **Function**: [`parse_int`](#parse_int)
- **Function**: [`parse_float`](#parse_float)

---

### `char_to_digit` <a id="char_to_digit"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn char_to_digit(ch: str): int
```

---

### `parse_int` <a id="parse_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_int(value: str): int?
```

Parses a string into an integer.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | String containing numeric digits, optionally prefixed with `+` or `-`. |

#### Returns

Fallible integer or error on syntax failure.

#### Example: Idiomatic Usage

```lymar
var num = parse_int("123")? else { return 0; };
```

---

### `parse_float` <a id="parse_float"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_float(value: str): str?
```

Parses a string representation of a float.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | String representing a floating-point number. |

#### Returns

Fallible string representation.

---


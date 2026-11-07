# API Documentation: `parser.lm`

## Overview

std/toml/parser.lm
Line-based TOML document parser.

## Symbols

- **Function**: [`is_digit_char`](#is_digit_char)
- **Frame**: [`Parser`](#Parser)
- **Function**: [`parse`](#parse)

---

### `is_digit_char` <a id="is_digit_char"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_digit_char(ch: str): bool
```

---

### `Parser` <a id="Parser"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Parser
```

Line-based TOML document parser.

#### Members

- `var pub idx: int` *(field)*
- `var pub text: str` *(field)*
- `pub fn parse_value(): value.Value` *(method)*

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(text: str): value.Value
```

Parses TOML formatted document string into an AST `Value` node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | Raw TOML text. |

#### Returns

Root `value.Value` table object.

---


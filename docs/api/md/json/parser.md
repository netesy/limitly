# API Documentation: `parser.lm`

## Overview

std/json/parser.lm
Recursive descent JSON text parser producing structured Value ASTs.

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

Recursive descent JSON text parser.

#### Members

- `var pub idx: int` *(field)*
- `var pub text: str` *(field)*
- `pub fn skip_whitespace()` *(method)*
- `pub fn peek_char(): str` *(method)*
- `pub fn parse_value(): value.Value` *(method)*
- `pub fn parse_string(): value.Value` *(method)*
- `pub fn parse_bool(): value.Value` *(method)*
- `pub fn parse_null(): value.Value` *(method)*
- `pub fn parse_number(): value.Value` *(method)*
- `pub fn parse_array(): value.Value` *(method)*
- `pub fn parse_object(): value.Value` *(method)*

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(text: str): value.Value
```

Parses raw JSON text into an immutable `Value` AST node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | Raw JSON text. |

#### Returns

Parsed `value.Value` root node.

---


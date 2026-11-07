# API Documentation: `parser.lm`

## Overview

Standard Library NOL Parser
Netesy Object Language (NOL)

## Symbols

- **Function**: [`_is_digit`](#_is_digit)
- **Function**: [`_is_ident_char`](#_is_ident_char)
- **Frame**: [`Parser`](#Parser)
- **Function**: [`parse`](#parse)

---

### `_is_digit` <a id="_is_digit"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _is_digit(ch: str): bool
```

---

### `_is_ident_char` <a id="_is_ident_char"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn _is_ident_char(ch: str): bool
```

---

### `Parser` <a id="Parser"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Parser
```

#### Members

- `var pub text: str` *(field)*
- `var pub pos: int` *(field)*
- `var pub text_len: int` *(field)*
- `pub init(text: str)` *(constructor)*
- `fn peek(): str` *(method)*
- `fn peek_next(): str` *(method)*
- `fn advance(): str` *(method)*
- `fn skip_ws()` *(method)*
- `fn read_key(): str` *(method)*
- `fn parse_string(): value.Value` *(method)*
- `fn parse_number(): value.Value` *(method)*
- `fn parse_literal(): value.Value` *(method)*
- `pub fn parse_value(): value.Value` *(method)*
- `fn parse_section_entries(): value.Value` *(method)*
- `pub fn parse_doc(): document.Document` *(method)*

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(text: str): document.Document
```

Parses NOL source text into a `Document`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | NOL document source string. |

#### Returns

Parsed `Document`.

---


# API Documentation: `parser.lm`

## Overview

std/yaml/parser.lm
Line-based YAML document parser.

## Symbols

- **Frame**: [`Parser`](#Parser)
- **Function**: [`parse`](#parse)

---

### `Parser` <a id="Parser"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Parser
```

Line-based YAML document parser.

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

Parses YAML formatted text into an AST `Value` node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | Raw YAML text. |

#### Returns

Root `value.Value` object node.

---


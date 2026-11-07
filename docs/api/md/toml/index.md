# API Documentation: `index.lm`

## Overview

std/toml/index.lm
Public facade for std.toml: TOML parsing and serialization.

## Symbols

- **Function**: [`parse`](#parse)
- **Function**: [`stringify`](#stringify)

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(text: str): value.Value
```

Parses TOML formatted text into an AST `Value` table.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | Raw TOML text. |

#### Returns

Root `Value` object node.

---

### `stringify` <a id="stringify"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stringify(val_obj: value.Value): str
```

Serializes a TOML `Value` node into a TOML formatted document string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `val_obj` | Target value node. |

#### Returns

Formatted TOML text.

---


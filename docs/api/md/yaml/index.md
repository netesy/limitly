# API Documentation: `index.lm`

## Overview

std/yaml/index.lm
Public facade for std.yaml: YAML parsing and serialization.

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

Parses YAML formatted text into an AST `Value` node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | Raw YAML text. |

#### Returns

Root `Value` object node.

---

### `stringify` <a id="stringify"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stringify(val_obj: value.Value): str
```

Serializes a YAML `Value` node into a YAML formatted document string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `val_obj` | Target value node. |

#### Returns

Formatted YAML text.

---


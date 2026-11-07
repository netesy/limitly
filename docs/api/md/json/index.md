# API Documentation: `index.lm`

## Overview

std/json/index.lm
Public facade for std.json: JSON parsing, serializing, and AST values.

## Symbols

- **Function**: [`parse`](#parse)
- **Function**: [`stringify`](#stringify)
- **Function**: [`encode_pair`](#encode_pair)
- **Function**: [`encode_object`](#encode_object)

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(text: str): value.Value?
```

Parses JSON text into a fallible `Value` AST root.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | Raw JSON text. |

#### Returns

Fallible `Value` root node.

---

### `stringify` <a id="stringify"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stringify(val_obj: value.Value): str
```

Serializes a JSON `Value` node into a JSON string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `val_obj` | Value AST node to format. |

#### Returns

Serialized JSON text.

---

### `encode_pair` <a id="encode_pair"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode_pair(key: str, val_str: str): str
```

Encodes a single key-value pair as a JSON object entry.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Object key name. |
| `val_str` | Serialized value text. |

#### Returns

Formatted entry string.

---

### `encode_object` <a id="encode_object"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode_object(keys: list, vals: list): str
```

Encodes parallel lists of keys and string values into a JSON object string.

#### Preconditions (Contracts)

- `requires len(keys) == len(vals)`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `keys` | List of object key names. |
| `vals` | Parallel list of serialized value strings. |

#### Returns

Serialized JSON object literal.

---


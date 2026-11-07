# API Documentation: `writer.lm`

## Overview

std/json/writer.lm
JSON text serializer and encoder.

## Symbols

- **Function**: [`stringify`](#stringify)
- **Function**: [`encode_pair`](#encode_pair)
- **Function**: [`encode_object`](#encode_object)

---

### `stringify` <a id="stringify"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stringify(val_obj: value.Value): str
```

Serializes a JSON `Value` AST node into formatted JSON text.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `val_obj` | Target JSON value node to serialize. |

#### Returns

Serialized JSON string.

---

### `encode_pair` <a id="encode_pair"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode_pair(key: str, val_str: str): str
```

Encodes a single key-value pair as a JSON object entry `"key":"value"`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Key name. |
| `val_str` | Value text. |

#### Returns

Encoded pair string.

---

### `encode_object` <a id="encode_object"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode_object(keys: list, vals: list): str
```

Encodes parallel lists of keys and string values into a JSON object literal.

#### Preconditions (Contracts)

- `requires len(keys) == len(vals)`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `keys` | List of object key names. |
| `vals` | Parallel list of serialized value strings. |

#### Returns

Formatted JSON object string.

---


# API Documentation: `writer.lm`

## Overview

std/yaml/writer.lm
YAML document serializer.

## Symbols

- **Function**: [`stringify`](#stringify)

---

### `stringify` <a id="stringify"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stringify(val_obj: value.Value): str
```

Serializes a YAML `Value` node into YAML document text.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `val_obj` | Value AST node to format. |

#### Returns

Serialized YAML text.

---


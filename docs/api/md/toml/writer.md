# API Documentation: `writer.lm`

## Overview

std/toml/writer.lm
TOML text serializer.

## Symbols

- **Function**: [`stringify`](#stringify)

---

### `stringify` <a id="stringify"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stringify(val_obj: value.Value): str
```

Serializes a TOML `Value` node into formatted TOML configuration text.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `val_obj` | Value AST node to format. |

#### Returns

Serialized TOML text.

---


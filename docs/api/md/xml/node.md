# API Documentation: `node.lm`

## Overview

std/xml/node.lm
XML Node re-export module

## Symbols

- **Function**: [`make_node`](#make_node)

---

### `make_node` <a id="make_node"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_node(name: str, text: str, keys: list, vals: list, children: list): doc.Node
```

Constructs a new XML element node.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `name` | Element tag name. |
| `text` | Inner textual content. |
| `keys` | Attribute names. |
| `vals` | Attribute values. |
| `children` | List of nested child nodes. |

#### Returns

Configured `Node` instance.

---


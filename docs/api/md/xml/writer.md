# API Documentation: `writer.lm`

## Overview

std/xml/writer.lm
XML Writer Module

## Symbols

- **Function**: [`stringify_node`](#stringify_node)
- **Function**: [`stringify`](#stringify)

---

### `stringify_node` <a id="stringify_node"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stringify_node(val_node: doc.Node): str
```

Serializes an XML `Node` AST element into formatted XML text.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `val_node` | XML node to serialize. |

#### Returns

Formatted XML element string.

---

### `stringify` <a id="stringify"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stringify(doc_val: doc.Document): str
```

Serializes an entire `Document` to its XML string representation.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `doc_val` | XML document instance. |

#### Returns

Serialized XML string.

---


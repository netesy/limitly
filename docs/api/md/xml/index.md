# API Documentation: `index.lm`

## Overview

std/xml/index.lm
XML Module Gateway Index

## Symbols

- **Function**: [`parse`](#parse)
- **Function**: [`stringify`](#stringify)

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(text: str): doc.Document
```

Parses XML markup into a `Document` structure.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | XML source string to parse. |

#### Returns

Parsed `Document` AST.

#### Example: Idiomatic Usage

```lymar
var d = xml.parse("<root><item>Hello</item></root>");
```

---

### `stringify` <a id="stringify"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stringify(node_val: doc.Node): str
```

Serializes an XML `Node` tree into formatted XML text.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `node_val` | Node to serialize. |

#### Returns

Serialized XML string.

---


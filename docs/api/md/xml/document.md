# API Documentation: `document.lm`

## Overview

std/xml/document.lm
XML Document and Node representation

## Symbols

- **Frame**: [`Node`](#Node)
- **Frame**: [`Document`](#Document)
- **Function**: [`make_node`](#make_node)
- **Function**: [`make_document`](#make_document)

---

### `Node` <a id="Node"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Node
```

Represents an XML element node with attributes, text, and nested children.

#### Members

- `var pub name: str` *(field)*
- `var pub text: str` *(field)*
- `var pub attrs_keys: list` *(field)*
- `var pub attrs_vals: list` *(field)*
- `var pub children: list` *(field)*

---

### `Document` <a id="Document"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Document
```

Represents a top-level XML document wrapping a root element node.

#### Members

- `var pub root: Node` *(field)*

---

### `make_node` <a id="make_node"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_node(name: str, text: str, keys: list, vals: list, children: list): Node
```

Constructs a new XML `Node` with attributes and children.

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

### `make_document` <a id="make_document"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_document(root: Node): Document
```

Constructs a new XML `Document` wrapping the given root element.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `root` | Root `Node` element. |

#### Returns

Configured `Document` instance.

---


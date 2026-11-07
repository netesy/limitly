# API Documentation: `parser.lm`

## Overview

std/html/parser.lm
HTML5 Tokenizer and Hierarchical DOM Parser Module
Supports HTML void elements (<br>, <img>, <hr>, <input>, <meta>, <link>), attribute parsing, and nested trees.

## Symbols

- **Frame**: [`Node`](#Node)
- **Function**: [`create_text_node`](#create_text_node)
- **Function**: [`is_void_element`](#is_void_element)
- **Function**: [`parse`](#parse)

---

### `Node` <a id="Node"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Node
```

Represents a DOM element or text node in an HTML document tree.

#### Members

- `var pub tag_name: str` *(field)*
- `var pub attributes: dict` *(field)*
- `var pub children: list` *(field)*
- `var pub text_content: str` *(field)*
- `var pub is_text: bool` *(field)*
- `pub init()` *(constructor)*

---

### `create_text_node` <a id="create_text_node"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_text_node(t: str): Node
```

Creates a new DOM node representing plain text.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `t` | Inner text content. |

#### Returns

Configured text `Node`.

---

### `is_void_element` <a id="is_void_element"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_void_element(tag: str): bool
```

Checks whether an HTML tag is a self-closing void element according to the HTML5 specification.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `tag` | Lowercase tag name (e.g. `"br"`, `"img"`, `"hr"`). |

#### Returns

`true` if element does not accept closing tag, `false` otherwise.

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(html_str: str): Node
```

Parses raw HTML markup into a tree of `Node` elements rooted at `<html>`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `html_str` | Raw HTML source string. |

#### Returns

Root `Node` of the parsed document hierarchy.

#### Example: Idiomatic Usage

```lymar
var dom = parser.parse("<div><p>Hello</p><br></div>");
```

---


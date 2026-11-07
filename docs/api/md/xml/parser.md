# API Documentation: `parser.lm`

## Overview

std/xml/parser.lm
XML Parser Module

## Symbols

- **Frame**: [`Parser`](#Parser)
- **Function**: [`parse`](#parse)

---

### `Parser` <a id="Parser"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Parser
```

Recursive descent parser for XML documents.

#### Members

- `var pub idx: int` *(field)*
- `var pub text: str` *(field)*
- `pub fn skip_whitespace()` *(method)*
- `pub fn peek_char(): str` *(method)*
- `pub fn parse_node(): doc.Node` *(method)*

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(text: str): doc.Document
```

Parses an XML document string into a `Document` AST.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | XML document source text. |

#### Returns

Parsed `Document` instance.

#### Example: Idiomatic Usage

```lymar
var d = parser.parse("<user id=\"1\"><name>Alice</name></user>");
```

---


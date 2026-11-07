# API Documentation: `index.lm`

## Overview

std/html/index.lm
HTML Module Gateway Index

## Symbols

- **Function**: [`escape`](#escape)
- **Function**: [`unescape`](#unescape)
- **Function**: [`parse`](#parse)

---

### `escape` <a id="escape"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn escape(text: str): str
```

Escapes HTML-sensitive characters (`&`, `<`, `>`, `"`, `'`) to prevent XSS.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | Raw unescaped text string. |

#### Returns

Escaped HTML text safe for interpolation.

---

### `unescape` <a id="unescape"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn unescape(text: str): str
```

Unescapes common HTML entities back into their raw literal characters.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | HTML markup containing entity codes. |

#### Returns

Unescaped raw string.

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(text: str): parser.Node
```

Parses an HTML source text into a DOM `Node` element tree.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | HTML markup string. |

#### Returns

Root `Node` representing the document hierarchy.

---


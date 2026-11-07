# API Documentation: `escape.lm`

## Overview

std/html/escape.lm
HTML Entity Escape and Unescape Module

## Symbols

- **Function**: [`escape`](#escape)
- **Function**: [`unescape`](#unescape)

---

### `escape` <a id="escape"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn escape(text: str): str
```

Escapes special HTML characters (`&`, `<`, `>`, `"`, `'`) into their corresponding entity references.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | Plain text containing potentially unsafe HTML characters. |

#### Returns

Escaped string safe for insertion into HTML markup.

#### Example: Idiomatic Usage

```lymar
var safe = html.escape("<script>alert('xss')</script>");
```

---

### `unescape` <a id="unescape"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn unescape(text: str): str
```

Unescapes common HTML entities back to their corresponding raw characters.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | HTML text containing entity references (e.g. `&lt;`, `&amp;`). |

#### Returns

Unescaped raw string.

#### Example: Idiomatic Usage

```lymar
var raw = html.unescape("&lt;div&gt;");
```

---


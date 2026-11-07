# API Documentation: `index.lm`

## Overview

std/csv/index.lm
Public facade for std.csv: Comma-Separated Values parsing and serialization.

## Symbols

- **Function**: [`parse`](#parse)
- **Function**: [`stringify`](#stringify)

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(text: str): list
```

Parses CSV formatted text into a 2D matrix of row records and column values.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | Raw CSV text. |

#### Returns

2D list of strings `[[str]]`.

---

### `stringify` <a id="stringify"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stringify(rows: list): str
```

Serializes a 2D matrix of strings into a comma-separated CSV text document.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `rows` | 2D list of row strings to format. |

#### Returns

Formatted CSV text.

---


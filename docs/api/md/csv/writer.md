# API Documentation: `writer.lm`

## Overview

std/csv/writer.lm
CSV tabular text serializer.

## Symbols

- **Function**: [`stringify_csv`](#stringify_csv)

---

### `stringify_csv` <a id="stringify_csv"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stringify_csv(rows: list): str
```

Serializes a 2D matrix of strings into a comma-separated CSV text document.
Appends a newline after each record row.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `rows` | 2D list of row strings to format. |

#### Returns

Formatted CSV text string.

---


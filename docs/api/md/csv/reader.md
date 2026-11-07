# API Documentation: `reader.lm`

## Overview

std/csv/reader.lm
CSV tabular text reader and parser.

## Symbols

- **Function**: [`parse_csv`](#parse_csv)

---

### `parse_csv` <a id="parse_csv"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_csv(text: str): list
```

Parses RFC 4180-style comma-separated text into a 2D matrix of strings.
Strips optional carriage returns (\r) and ignores empty trailing lines.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `text` | Raw CSV formatted string. |

#### Returns

2D list of row records and column field strings.

---


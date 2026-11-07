# API Documentation: `trim.lm`

## Overview

std/string/trim.lm
Whitespace trimming, backed by the compiler intrinsic.

## Symbols

- **Function**: [`trim`](#trim)

---

### `trim` <a id="trim"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn trim(value: str): str
```

Strips leading and trailing ASCII whitespace characters from `value`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The string to trim. |

#### Returns

Trimmed string without leading or trailing spaces, tabs, or newlines.

#### Example: Idiomatic Usage

```lymar
var clean = trim.trim("   hello world\n\t");
```

---


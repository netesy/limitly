# API Documentation: `join.lm`

## Overview

std/string/join.lm
Concatenating multiple strings with a separator.

## Symbols

- **Function**: [`join`](#join)

---

### `join` <a id="join"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn join(values: list, delimiter: str): str
```

Joins a list of strings using the specified delimiter string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `values` | Array of string elements to join. |
| `delimiter` | Separator string placed between each element. |

#### Returns

Concatenated string.

#### Example: Idiomatic Usage

```lymar
var csv = join.join(["a", "b", "c"], ", ");
```

---


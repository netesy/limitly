# API Documentation: `split.lm`

## Overview

std/string/split.lm
Splitting a string on a delimiter.

## Symbols

- **Function**: [`split`](#split)

---

### `split` <a id="split"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn split(value: str, delimiter: str): list
```

Splits a string into substrings using a separator string.
If `delimiter` is empty, splits the string into individual single-character tokens.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The string to split. |
| `delimiter` | Separator string. |

#### Returns

List of split string segments.

#### Example: Idiomatic Usage

```lymar
var parts = split.split("apple,banana,orange", ",");
```

---


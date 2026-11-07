# API Documentation: `replace.lm`

## Overview

std/string/replace.lm
Substring replacement, backed by the compiler intrinsic.

## Symbols

- **Function**: [`replace`](#replace)

---

### `replace` <a id="replace"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn replace(value: str, old: str, replacement: str): str
```

Replaces all occurrences of `old` within `value` with `replacement`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The target string. |
| `old` | Substring to find and replace. |
| `replacement` | String to substitute in place of `old`. |

#### Returns

Resulting modified string.

#### Example: Idiomatic Usage

```lymar
var res = replace.replace("foo bar foo", "foo", "baz");
```

---


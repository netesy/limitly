# API Documentation: `index.lm`

## Overview

Assertions as fallible calls. A failed assertion returns an `Error` carrying
the caller's message, so it lands in the enclosing function's error path
instead of becoming a sentinel integer nobody checks.

  var _ = Debug.assert(ready, "not ready")? else { return; };

`nil` is the success payload: the check has no value to report.

## Symbols

- **Frame**: [`Debug`](#Debug)

---

### `Debug` <a id="Debug"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Debug
```

#### Members

- `pub fn assert(condition: bool, message: str): nil` *(method)*
- `pub fn assert_eq(left: str, right: str): nil` *(method)*
- `pub fn trace(message: str): nil` *(method)*

---


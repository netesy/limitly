# API Documentation: `timer.lm`

## Overview

Standard Library Time Timer Submodule

## Symbols

- **Frame**: [`Timer`](#Timer)

---

### `Timer` <a id="Timer"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Timer
```

#### Members

- `var pub start_time: inst.Instant` *(field)*
- `pub init()` *(constructor)*
- `pub fn reset()` *(method)*
- `pub fn elapsed(): dur.Duration` *(method)*

---


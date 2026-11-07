# API Documentation: `service.lm`

## Overview

std/os/service.lm

Private plumbing between std.os and the RT_OS resource. Not re-exported from
the facade: callers use the typed helpers in the sibling submodules.

The OS resource holds no per-handle state (the facts come from the process
itself), so a handle is cheap and short-lived: it is created, asked one
question and released inside a single request. It is deliberately NOT cached
in a module-level var, because module state is not retained between calls -
a var written inside a function is not visible to the next one.

## Symbols

- **Function**: [`request`](#request)
- **Function**: [`request_with`](#request_with)

---

### `request` <a id="request"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn request(op: int)
```

---

### `request_with` <a id="request_with"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn request_with(op: int, args: list)
```

---


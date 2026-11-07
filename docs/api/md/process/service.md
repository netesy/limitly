# API Documentation: `service.lm`

## Overview

std/process/service.lm

Private plumbing between std.process and the RT_PROCESS resource. Not
re-exported from the facade.

Like std.os/service.lm, no handle is cached: module-level state is not
retained between calls in Lymar, so each request creates the resource, uses
it and releases it within one function.

resource_call flattens a list argument into individual values, so
request_with(op, [a, b]) delivers args[0]=a, args[1]=b.

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


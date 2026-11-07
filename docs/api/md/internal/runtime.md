# API Documentation: `runtime.lm`

## Overview

std/internal/runtime.lm
Runtime submodule for std.internal. Internal runtime support and resource identifiers.

## Symbols

- **Function**: [`resource_kind_id`](#resource_kind_id)
- **Function**: [`create_resource`](#create_resource)
- **Function**: [`create`](#create)
- **Function**: [`call`](#call)
- **Function**: [`destroy`](#destroy)

---

### `resource_kind_id` <a id="resource_kind_id"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn resource_kind_id(k: ResourceKind): int
```

---

### `create_resource` <a id="create_resource"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_resource(kind: ResourceKind, args: any): int
```

---

### `create` <a id="create"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create(type_id: int, args: any): int
```

---

### `call` <a id="call"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn call(handle: int, op_id: int, args: any): any
```

---

### `destroy` <a id="destroy"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn destroy(handle: int): nil
```

---


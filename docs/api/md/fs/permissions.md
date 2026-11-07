# API Documentation: `permissions.lm`

## Overview

std/fs/permissions.lm
Filesystem permissions and access flags.

## Symbols

- **Frame**: [`Permissions`](#Permissions)

---

### `Permissions` <a id="Permissions"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Permissions
```

Represents file or directory access permissions.
Encapsulates read-only status and access control attributes.

#### Example: Idiomatic Usage

```lymar
import std.fs.permissions as perm;
var p = perm.Permissions(false);
print(p.is_readonly()); // false
```

#### Members

- `var pub readonly: bool` *(field)*
- `pub init(readonly: bool)` *(constructor)*
- `pub fn is_readonly(): bool` *(method)*

---


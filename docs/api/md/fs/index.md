# API Documentation: `index.lm`

## Overview

std/fs/index.lm
Public entrypoint and facade for std.fs. Filesystem paths, directory iteration, and file metadata access.

## Symbols

- **Frame**: [`FS`](#FS)

---

### `FS` <a id="FS"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame FS
```

High-level filesystem manager operating on strongly-typed `Path` instances.

#### Members

- `pub init()` *(constructor)*
- `pub fn exists(p: Path): bool` *(method)*
- `pub fn create_dir(p: Path): nil?` *(method)*
- `pub fn remove(p: Path): nil?` *(method)*
- `pub fn rename(from_path: Path, to_path: Path): nil?` *(method)*
- `pub fn list_dir(p: Path): list?` *(method)*

---


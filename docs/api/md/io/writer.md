# API Documentation: `writer.lm`

## Overview

std/io/writer.lm
Abstract writer interface for character and byte streams.

## Symbols

- **Trait**: [`Writer`](#Writer)
- **Frame**: [`StreamWriter`](#StreamWriter)

---

### `Writer` <a id="Writer"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Writer
```

Contract for writable stream handles.

#### Members

- `fn write(args: list): nil?` *(method requirement)*

---

### `StreamWriter` <a id="StreamWriter"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame StreamWriter: Writer
```

Stream writer wrapper around an operating system resource handle.

#### Members

- `var pub w: Writer` *(field)*
- `pub init(resource: Resource)` *(constructor)*
- `pub fn write(args: list): nil?` *(method)*

---


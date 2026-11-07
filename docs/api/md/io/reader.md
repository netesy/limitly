# API Documentation: `reader.lm`

## Overview

std/io/reader.lm
Abstract reader interface for character and byte streams.

## Symbols

- **Trait**: [`Reader`](#Reader)
- **Frame**: [`StreamReader`](#StreamReader)

---

### `Reader` <a id="Reader"></a>

**Kind**: Trait  
**Visibility**: `pub`  

```lymar
trait Reader
```

Contract for readable stream handles.

#### Members

- `fn read(args: list): str?` *(method requirement)*

---

### `StreamReader` <a id="StreamReader"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame StreamReader: Reader
```

Stream reader wrapper around an operating system resource handle.

#### Members

- `var pub r: Reader` *(field)*
- `pub init(resource: Resource)` *(constructor)*
- `pub fn read(): str?` *(method)*

---


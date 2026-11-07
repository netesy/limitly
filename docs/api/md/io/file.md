# API Documentation: `file.lm`

## Overview

std/io/file.lm
File resource handle and stream operations.

## Symbols

- **Frame**: [`FileNotFound`](#FileNotFound)
- **Frame**: [`PermissionDenied`](#PermissionDenied)
- **Frame**: [`DiskFull`](#DiskFull)
- **Frame**: [`NetworkError`](#NetworkError)
- **Frame**: [`UnknownError`](#UnknownError)
- **Type Alias**: [`IOError`](#IOError)
- **Frame**: [`File`](#File)
- **Function**: [`open`](#open)

---

### `FileNotFound` <a id="FileNotFound"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame FileNotFound
```

Error indicating the requested file does not exist.

#### Members

- `var pub path: str` *(field)*

---

### `PermissionDenied` <a id="PermissionDenied"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame PermissionDenied
```

Error indicating insufficient filesystem access permissions.

#### Members

- `var pub path: str` *(field)*
- `var pub operation: str` *(field)*

---

### `DiskFull` <a id="DiskFull"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame DiskFull
```

Error indicating the storage device has no remaining space.

#### Members

- `var pub path: str` *(field)*

---

### `NetworkError` <a id="NetworkError"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame NetworkError
```

Error indicating a network filesystem failure.

#### Members

- `var pub message: str` *(field)*

---

### `UnknownError` <a id="UnknownError"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame UnknownError
```

Error representing an unspecified or operating system I/O failure.

#### Members

- `var pub message: str` *(field)*

---

### `IOError` <a id="IOError"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type IOError = union
```

Fallible I/O error type union.

---

### `File` <a id="File"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame File: Disposable
```

Stream handle for local file reading and writing.
Wraps an operating system file descriptor handle, providing buffered string
and binary I/O, resource cleanup via `close()` or `deinit()`.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Always ensure files are closed via `file.close()` or automatic deinit cleanup.

#### Example: Idiomatic Usage

```lymar
import std.io.file as file;
var f = file.open("test.txt", "w")? else {
    return;
};
f.write("Lymar I/O");
f.close();
```

#### Members

- `var pub path: str` *(field)*
- `var pub resource: res.Resource` *(field)*
- `pub init(p: str, r: res.Resource)` *(constructor)*
- `pub fn dispose(): nil` *(method)*
- `pub fn read(): any` *(method)*
- `pub fn read_bytes(): list` *(method)*
- `pub fn write(arg: any): any` *(method)*
- `pub fn close(): nil` *(method)*
- `pub fn is_open(): bool` *(method)*

---

### `open` <a id="open"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn open(path: str, mode: str): File?
```

Opens a file at the given path with specified mode ("r", "w", "a", etc.).

#### Preconditions (Contracts)

- `requires len(path) > 0 and len(mode) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | The relative or absolute filesystem path. |
| `mode` | File access mode ('r', 'w', 'a', etc.). |

#### Returns

Fallible File handle or IOError variant.

#### Example: Idiomatic Usage

```lymar
var file = open("data.txt", "r")? else {
    print("Failed to open data.txt");
    return;
};
```

---


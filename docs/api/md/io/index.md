# API Documentation: `index.lm`

## Overview

std/io/index.lm
Public entrypoint and facade for std.io. Input/output, console, file, and stream abstractions.

## Symbols

- **Function**: [`create_file_resource`](#create_file_resource)
- **Function**: [`open`](#open)
- **Function**: [`print`](#print)
- **Frame**: [`FileSystem`](#FileSystem)
- **Function**: [`exists`](#exists)
- **Function**: [`delete`](#delete)
- **Function**: [`rename`](#rename)
- **Function**: [`create_directory`](#create_directory)
- **Function**: [`list_directory`](#list_directory)

---

### `create_file_resource` <a id="create_file_resource"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_file_resource(p: str, r: res.Resource): file.File
```

Instantiates a file stream binding directly to an existing operating system resource handle.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `p` | Filesystem path. |
| `r` | Resource handle. |

#### Returns

Configured `File` handle.

---

### `open` <a id="open"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn open(path: str, mode: str): file.File?
```

Opens a file at the specified path with the given access mode ('r', 'w', 'a').

#### Preconditions (Contracts)

- `requires len(path) > 0 and len(mode) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | Relative or absolute path to the file. |
| `mode` | Access mode string. |

#### Returns

Fallible `File` handle.

---

### `print` <a id="print"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn print(msg: str): nil
```

Prints a string message to standard output.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `msg` | Message to display. |

---

### `FileSystem` <a id="FileSystem"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame FileSystem
```

Internal file system resource wrapper for path operations.

#### Members

- `var pub resource: res.Resource` *(field)*
- `pub init(r: res.Resource)` *(constructor)*
- `pub fn exists(path: str): bool` *(method)*
- `pub fn delete(path: str): bool` *(method)*
- `pub fn rename(old: str, new: str): bool` *(method)*
- `pub fn mkdir(path: str): bool` *(method)*
- `pub fn readdir(path: str): any` *(method)*

---

### `exists` <a id="exists"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn exists(path: str): bool
```

Checks whether a file or directory exists at the given path.

#### Preconditions (Contracts)

- `requires len(path) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | Candidate filesystem path. |

#### Returns

True if target exists, false otherwise.

---

### `delete` <a id="delete"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn delete(path: str): bool
```

Deletes a file or empty directory at the given path.

#### Preconditions (Contracts)

- `requires len(path) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | Path to delete. |

#### Returns

True if deletion succeeded, false otherwise.

---

### `rename` <a id="rename"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn rename(old_path: str, new_path: str): bool
```

Renames or moves a file or directory from `old_path` to `new_path`.

#### Preconditions (Contracts)

- `requires len(old_path) > 0 and len(new_path) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `old_path` | Source path. |
| `new_path` | Target destination path. |

#### Returns

True if rename succeeded, false otherwise.

---

### `create_directory` <a id="create_directory"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_directory(path: str): nil?
```

Creates a new directory at the specified path.

#### Preconditions (Contracts)

- `requires len(path) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | Directory path to create. |

#### Returns

Fallible unit result.

---

### `list_directory` <a id="list_directory"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn list_directory(path: str): list?
```

Lists directory entries as a list of filename strings.

#### Preconditions (Contracts)

- `requires len(path) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | Directory path to inspect. |

#### Returns

Fallible list of directory entry names.

---


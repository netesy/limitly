# API Documentation: `directory.lm`

## Overview

std/fs/directory.lm
Filesystem directory manipulation helpers.

## Symbols

- **Function**: [`create_dir`](#create_dir)
- **Function**: [`list_dir`](#list_dir)

---

### `create_dir` <a id="create_dir"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_dir(path_str: str): nil?
```

Creates a new directory at the target path.

#### Preconditions (Contracts)

- `requires len(path_str) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path_str` | Target directory path string. |

#### Returns

Fallible unit result.

---

### `list_dir` <a id="list_dir"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn list_dir(path_str: str): list?
```

Lists all immediate entry names in a directory.

#### Preconditions (Contracts)

- `requires len(path_str) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path_str` | Target directory path string. |

#### Returns

Fallible list of filename strings.

---


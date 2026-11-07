# API Documentation: `directories.lm`

## Overview

std/os/directories.lm
Working directory and well-known locations, backed by the RT_OS resource.

## Symbols

- **Function**: [`cwd`](#cwd)
- **Function**: [`chdir`](#chdir)
- **Function**: [`home_dir`](#home_dir)
- **Function**: [`temp_dir`](#temp_dir)
- **Function**: [`exe_path`](#exe_path)

---

### `cwd` <a id="cwd"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cwd(): str
```

Returns the current working directory of the process.

#### Returns

Absolute working directory path, or empty string when unavailable.

---

### `chdir` <a id="chdir"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn chdir(path: str): bool
```

Changes the current working directory of the process.

#### Preconditions (Contracts)

- `requires len(path) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | Target directory path. |

#### Returns

True if directory change succeeded, false otherwise.

---

### `home_dir` <a id="home_dir"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn home_dir(): str
```

Returns the current user's home directory.

#### Returns

Absolute path to the user's home folder.

---

### `temp_dir` <a id="temp_dir"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn temp_dir(): str
```

Returns the default temporary directory path for the host OS.

#### Returns

Temporary directory path.

---

### `exe_path` <a id="exe_path"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn exe_path(): str
```

Returns the absolute path of the running executable.

#### Returns

Path to current executable binary.

---


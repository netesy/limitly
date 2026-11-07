# API Documentation: `index.lm`

## Overview

std/path/index.lm
Path module - Cross-platform path manipulation.

The separator that gets written is the platform one (std.os.path_separator);
both "/" and "\" are always accepted when reading, so a POSIX path can be
manipulated on Windows and vice versa.

## Symbols

- **Frame**: [`Path`](#Path)
- **Function**: [`from_string`](#from_string)
- **Function**: [`join`](#join)
- **Function**: [`normalize`](#normalize)
- **Function**: [`is_relative`](#is_relative)
- **Function**: [`starts_with`](#starts_with)
- **Function**: [`ends_with`](#ends_with)
- **Function**: [`last_index_of`](#last_index_of)
- **Function**: [`is_separator`](#is_separator)
- **Function**: [`ends_with_separator`](#ends_with_separator)
- **Function**: [`starts_with_separator`](#starts_with_separator)
- **Function**: [`last_separator_index`](#last_separator_index)
- **Function**: [`is_root_text`](#is_root_text)
- **Function**: [`has_drive_prefix`](#has_drive_prefix)
- **Function**: [`is_absolute_text`](#is_absolute_text)
- **Function**: [`separator`](#separator)
- **Function**: [`list_separator`](#list_separator)
- **Function**: [`absolute`](#absolute)

---

### `Path` <a id="Path"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Path
```

Represents a filesystem path, providing methods for component decomposition,
joining, normalization, and filesystem inspection.

> [!TIP]
> **Idiomatic Usage & Best Practice**: All join operations normalize redundant separators automatically.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The raw string path backing this Path instance. |

#### Example: Idiomatic Usage

```lymar
var p = Path("/usr/local/bin");
print("Basename: {p.basename()}"); // "bin"
```

#### Members

- `var pub value: str` *(field)*
- `pub init(value: str)` *(constructor)*
- `pub fn from_string(path: str): Path` *(method)*
- `pub fn join(other: str): Path` *(method)*
- `pub fn join_multiple(parts: list): Path` *(method)*
- `pub fn parent(): Path?` *(method)*
- `pub fn basename(): str` *(method)*
- `pub fn stem(): str` *(method)*
- `pub fn extension(): str` *(method)*
- `pub fn normalize(): Path` *(method)*
- `pub fn resolve(): Path` *(method)*
- `pub fn is_absolute(): bool` *(method)*
- `pub fn is_relative(): bool` *(method)*
- `pub fn exists(): bool` *(method)*
- `pub fn with_extension(extension: str): Path` *(method)*
- `pub fn with_basename(basename: str): Path` *(method)*
- `pub fn equals(other: Path): bool` *(method)*
- `pub fn starts_with(prefix: Path): bool` *(method)*
- `pub fn ends_with(suffix: Path): bool` *(method)*
- `pub fn to_string(): str` *(method)*
- `pub fn display(): str` *(method)*

---

### `from_string` <a id="from_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn from_string(v: str): Path
```

Creates a new Path instance from a raw string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v` | Raw path string. |

#### Returns

New Path instance.

---

### `join` <a id="join"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn join(paths: list): Path
```

Joins an array of path strings using platform separator logic.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `paths` | Array of path segments. |

#### Returns

Joined Path instance.

---

### `normalize` <a id="normalize"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn normalize(path_str: str): Path
```

Normalizes a path string, resolving `.` and `..` segments.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path_str` | Raw path string. |

#### Returns

Normalized Path instance.

---

### `is_relative` <a id="is_relative"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_relative(path_str: str): bool
```

Checks whether a path string represents a relative path.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path_str` | Path string to inspect. |

#### Returns

True if relative, false if absolute.

---

### `starts_with` <a id="starts_with"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn starts_with(s: str, prefix: str): bool
```

Helper functions for string operations since primitive strings don't have methods

---

### `ends_with` <a id="ends_with"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn ends_with(s: str, suffix: str): bool
```

---

### `last_index_of` <a id="last_index_of"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn last_index_of(s: str, pattern: str): int
```

---

### `is_separator` <a id="is_separator"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_separator(c: str): bool
```

Separator helpers. Parsing accepts both separators on every platform; writing
always uses the platform separator. Indexing a string yields its character
code, so characters are extracted with substring() to stay in the str type.

---

### `ends_with_separator` <a id="ends_with_separator"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn ends_with_separator(s: str): bool
```

---

### `starts_with_separator` <a id="starts_with_separator"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn starts_with_separator(s: str): bool
```

---

### `last_separator_index` <a id="last_separator_index"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn last_separator_index(s: str): int
```

Index of the final separator in s, counting either separator, or -1.

---

### `is_root_text` <a id="is_root_text"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_root_text(s: str): bool
```

A path that is nothing but separators is a root ("/", "\\", "//").

---

### `has_drive_prefix` <a id="has_drive_prefix"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn has_drive_prefix(s: str): bool
```

Windows drive prefix, e.g. the "C:" of "C:/Users".

---

### `is_absolute_text` <a id="is_absolute_text"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_absolute_text(s: str): bool
```

---

### `separator` <a id="separator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn separator(): str
```

The platform separator used for writing paths (`\` on Windows, `/` on POSIX).

#### Returns

Host platform path separator string.

---

### `list_separator` <a id="list_separator"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn list_separator(): str
```

The separator between entries of a search-path environment variable (`:` on POSIX, `;` on Windows).

#### Returns

Search list separator string.

---

### `absolute` <a id="absolute"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn absolute(parts: list): Path
```

Resolves an array of subpaths relative to the process's current working directory.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `parts` | Subpath components to join with the current directory. |

#### Returns

Absolute Path instance.

---


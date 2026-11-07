# API Documentation: `index.lm`

## Overview

std/archive/index.lm

Complete Archive management for TAR and ZIP formats.
Supports reading, creating, listing, and extracting archive entries.

## Symbols

- **Function**: [`compression_method_code`](#compression_method_code)
- **Frame**: [`Entry`](#Entry)
- **Frame**: [`Archive`](#Archive)
- **Function**: [`open_tar`](#open_tar)
- **Function**: [`read_tar_from_bytes`](#read_tar_from_bytes)
- **Function**: [`open_zip`](#open_zip)
- **Function**: [`read_zip_from_bytes`](#read_zip_from_bytes)
- **Function**: [`create_tar`](#create_tar)
- **Function**: [`create_zip`](#create_zip)
- **Function**: [`extract_tar`](#extract_tar)
- **Function**: [`extract_zip`](#extract_zip)
- **Function**: [`write_ascii_into`](#write_ascii_into)
- **Function**: [`format_octal`](#format_octal)
- **Function**: [`append_u16_le`](#append_u16_le)
- **Function**: [`append_u32_le`](#append_u32_le)
- **Function**: [`ensure_dir`](#ensure_dir)
- **Function**: [`ensure_parent_dir`](#ensure_parent_dir)

---

### `compression_method_code` <a id="compression_method_code"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compression_method_code(m: CompressionMethod): int
```

Converts a CompressionMethod enum variant into its numerical ZIP/TAR header code.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `m` | The compression method enum variant. |

#### Returns

Returns 0 for Stored, 8 for Deflated.

---

### `Entry` <a id="Entry"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Entry
```

Represents a single file or directory node stored inside an archive.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Query `is_directory` before attempting to read text or binary content.

> [!NOTE]
> **Note**: Instances store the entry payload, uncompressed byte size, and compression method.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `name` | Relative path within the archive hierarchy (e.g. "docs/readme.txt"). |
| `size` | Uncompressed byte size. Inferred automatically if content is provided. |
| `is_dir` | True if this entry represents a directory node. |
| `content` | Raw text or binary data contained within the entry. |
| `method` | Compression method applied (0 for Stored, 8 for Deflated). |

#### Example: Idiomatic Usage

```lymar
var entry = Entry("hello.txt", content="Hello, World!");
print("Size: {entry.size()} bytes");
```

#### Members

- `var pub filename: str` *(field)*
- `var pub uncompressed_size: int` *(field)*
- `var pub is_directory: bool` *(field)*
- `var pub data: str` *(field)*
- `var pub compression_method: int` *(field)*
- `pub init(name: str)` *(constructor)*
- `pub fn method(): CompressionMethod` *(method)*
- `pub fn text(): str` *(method)*
- `pub fn size(): int` *(method)*

---

### `Archive` <a id="Archive"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Archive
```

Multi-entry archive container supporting TAR (USTAR) and ZIP serialization.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Methods like `add_file` and `add_directory` return `self` for fluent chaining.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | Optional default filesystem path associated with this archive. |

#### Example: Idiomatic Usage

```lymar
var arch = Archive();
arch.add_file("config.json", "{}");
var zip_data = arch.to_zip_bytes();
```

#### Members

- `var pub entries: list` *(field)*
- `var pub archive_path: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn add_entry(entry: Entry): nil` *(method)*
- `pub fn add_file(name: str, content: str): Archive` *(method)*
- `pub fn add_directory(name: str): Archive` *(method)*
- `pub fn get_entry(name: str): Entry?` *(method)*
- `pub fn read_text(name: str): str?` *(method)*
- `pub fn has_entry(name: str): bool` *(method)*
- `pub fn count(): int` *(method)*
- `pub fn list(): list` *(method)*
- `pub fn extract(target_dir: str): bool` *(method)*
- `pub fn extract_entry(name: str, target_dir: str): bool` *(method)*
- `pub fn to_tar_bytes(): list` *(method)*
- `pub fn write_tar(output_path: str): bool` *(method)*
- `pub fn to_zip_bytes(): list` *(method)*
- `pub fn write_zip(output_path: str): bool` *(method)*

---

### `open_tar` <a id="open_tar"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn open_tar(path: str): Archive?
```

Opens and parses a TAR archive from disk.

#### Preconditions (Contracts)

- `requires len(path) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | Filesystem path to the TAR archive. |

#### Returns

Returns ok(Archive) on success, or nil if file not found or invalid.

---

### `read_tar_from_bytes` <a id="read_tar_from_bytes"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn read_tar_from_bytes(path: str, bytes: list): Archive
```

Parses a byte array containing USTAR TAR formatted data into an Archive.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | Label path to associate with the parsed Archive. |
| `bytes` | In-memory byte array of TAR archive records. |

#### Returns

Populated Archive instance.

---

### `open_zip` <a id="open_zip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn open_zip(path: str): Archive?
```

Opens and parses a ZIP archive from disk.

#### Preconditions (Contracts)

- `requires len(path) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | Filesystem path to the ZIP archive. |

#### Returns

Returns ok(Archive) on success, or nil if file not found or invalid.

---

### `read_zip_from_bytes` <a id="read_zip_from_bytes"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn read_zip_from_bytes(path: str, bytes: list): Archive
```

Parses an in-memory byte array containing PKZip formatted data into an Archive.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | Label path to associate with the parsed Archive. |
| `bytes` | In-memory byte array of ZIP records. |

#### Returns

Populated Archive instance.

---

### `create_tar` <a id="create_tar"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_tar(path: str = ...): Archive
```

Creates a new, empty TAR archive builder.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | Optional target path. |

#### Returns

Fresh Archive container.

---

### `create_zip` <a id="create_zip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_zip(path: str = ...): Archive
```

Creates a new, empty ZIP archive builder.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | Optional target path. |

#### Returns

Fresh Archive container.

---

### `extract_tar` <a id="extract_tar"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn extract_tar(archive_path: str, target_dir: str): bool
```

Extracts an entire TAR archive on disk into the destination directory.

#### Preconditions (Contracts)

- `requires len(archive_path) > 0 and len(target_dir) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `archive_path` | Path to the source .tar file. |
| `target_dir` | Destination directory to unpack files into. |

#### Returns

Returns true if extracted successfully, false otherwise.

---

### `extract_zip` <a id="extract_zip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn extract_zip(archive_path: str, target_dir: str): bool
```

Extracts an entire ZIP archive on disk into the destination directory.

#### Preconditions (Contracts)

- `requires len(archive_path) > 0 and len(target_dir) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `archive_path` | Path to the source .zip file. |
| `target_dir` | Destination directory to unpack files into. |

#### Returns

Returns true if extracted successfully, false otherwise.

---

### `write_ascii_into` <a id="write_ascii_into"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn write_ascii_into(arr: list, start_idx: int, text: str)
```

Helpers

---

### `format_octal` <a id="format_octal"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn format_octal(val_num: int, digits: int): str
```

---

### `append_u16_le` <a id="append_u16_le"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn append_u16_le(arr: list, val_num: int)
```

---

### `append_u32_le` <a id="append_u32_le"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn append_u32_le(arr: list, val_num: int)
```

---

### `ensure_dir` <a id="ensure_dir"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn ensure_dir(path: str)
```

---

### `ensure_parent_dir` <a id="ensure_parent_dir"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn ensure_parent_dir(file_path: str)
```

---


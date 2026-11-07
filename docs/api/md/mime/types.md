# API Documentation: `types.lm`

## Overview

std/mime/types.lm
Types submodule for std.mime. MIME type registry and content-type detection.

## Symbols

- **Frame**: [`Params`](#Params)
- **Frame**: [`Type`](#Type)
- **Function**: [`parse`](#parse)
- **Function**: [`extension_to_mime`](#extension_to_mime)
- **Function**: [`mime_to_extension`](#mime_to_extension)
- **Function**: [`trim`](#trim)
- **Function**: [`to_lower`](#to_lower)
- **Function**: [`index_of`](#index_of)
- **Function**: [`split_str`](#split_str)

---

### `Params` <a id="Params"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Params
```

Key-value parameters associated with a MIME type (e.g., `charset=utf-8`).

#### Members

- `var pub keys: list` *(field)*
- `var pub values: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn get(key: str): str` *(method)*
- `pub fn set(key: str, value: str)` *(method)*
- `pub fn has(key: str): bool` *(method)*
- `pub fn add(key: str, value: str)` *(method)*
- `pub fn remove(key: str)` *(method)*
- `pub fn to_string(): str` *(method)*

---

### `Type` <a id="Type"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Type
```

Represents a parsed MIME media type with main type, subtype, and parameters.

#### Members

- `var pub is_valid: bool` *(field)*
- `var pub main_type: str` *(field)*
- `var pub params: Params` *(field)*
- `var pub subtype: str` *(field)*
- `pub init(m: str, s: str, p: Params, v: bool)` *(constructor)*
- `pub fn to_string(): str` *(method)*
- `pub fn is_text(): bool` *(method)*
- `pub fn is_image(): bool` *(method)*
- `pub fn is_audio(): bool` *(method)*
- `pub fn is_video(): bool` *(method)*
- `pub fn is_application(): bool` *(method)*

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(mime_str: str): Type
```

Parses a raw MIME / Content-Type string into structured `Type`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `mime_str` | Raw MIME string (e.g. `"text/html; charset=utf-8"`). |

#### Returns

Parsed `Type` structure.

---

### `extension_to_mime` <a id="extension_to_mime"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn extension_to_mime(ext: str): str
```

Maps a file extension to its corresponding MIME type.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `ext` | File extension (e.g. `"html"` or `".png"`). |

#### Returns

Matching MIME type string, or `"application/octet-stream"` if unknown.

---

### `mime_to_extension` <a id="mime_to_extension"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mime_to_extension(mime_str: str): str
```

Maps a MIME type string to its canonical file extension (including leading dot).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `mime_str` | MIME type string (e.g. `"text/html"`). |

#### Returns

File extension starting with dot, or empty string if unknown.

---

### `trim` <a id="trim"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn trim(s: str): str
```

---

### `to_lower` <a id="to_lower"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn to_lower(s: str): str
```

---

### `index_of` <a id="index_of"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn index_of(s: str, pattern: str): int
```

---

### `split_str` <a id="split_str"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn split_str(s: str, delimiter: str): list
```

---


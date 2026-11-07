# API Documentation: `index.lm`

## Overview

std/mime/index.lm
Public entrypoint and facade for std.mime. MIME type registry and content-type detection.

## Symbols

- **Function**: [`parse`](#parse)
- **Function**: [`extension_to_mime`](#extension_to_mime)
- **Function**: [`mime_to_extension`](#mime_to_extension)

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(mime_str: str): types.Type
```

Parses a raw MIME / Content-Type string (e.g. "text/html; charset=utf-8").

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `mime_str` | Raw MIME string to parse. |

#### Returns

Parsed `Type` instance with components and parameters.

#### Example: Idiomatic Usage

```lymar
var m = mime.parse("application/json; charset=utf-8");
if (m.is_valid and m.is_application()) {
    print("Valid application payload\n");
}
```

---

### `extension_to_mime` <a id="extension_to_mime"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn extension_to_mime(ext: str): str
```

Resolves a file extension to its standardized MIME type.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `ext` | File extension with or without leading dot (e.g. `"html"` or `".json"`). |

#### Returns

Matching MIME type string, or `"application/octet-stream"` if unrecognized.

---

### `mime_to_extension` <a id="mime_to_extension"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mime_to_extension(mime_str: str): str
```

Resolves a MIME type string to its canonical file extension (including leading dot).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `mime_str` | MIME type string (e.g. `"text/html"`). |

#### Returns

Canonical file extension with leading dot (e.g. `".html"`), or empty string if unrecognized.

---


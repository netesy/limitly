# API Documentation: `index.lm`

## Overview

std/encoding/index.lm
Public entrypoint and facade for std.encoding. Data encodings: Base64, Hex, URL percent, UTF-16, and UTF-32.

## Symbols

- **Frame**: [`Encoding`](#Encoding)
- **Function**: [`base64_encode`](#base64_encode)
- **Function**: [`base64_decode`](#base64_decode)
- **Function**: [`hex_encode`](#hex_encode)
- **Function**: [`hex_decode`](#hex_decode)
- **Function**: [`byte_to_hex`](#byte_to_hex)
- **Function**: [`hex_to_byte`](#hex_to_byte)
- **Function**: [`url_encode`](#url_encode)
- **Function**: [`url_decode`](#url_decode)
- **Function**: [`utf16_encode`](#utf16_encode)
- **Function**: [`utf16_encode_be`](#utf16_encode_be)
- **Function**: [`utf16_encode_le`](#utf16_encode_le)
- **Function**: [`utf16_decode`](#utf16_decode)
- **Function**: [`utf16_decode_be`](#utf16_decode_be)
- **Function**: [`utf16_decode_le`](#utf16_decode_le)
- **Function**: [`utf32_encode`](#utf32_encode)
- **Function**: [`utf32_encode_be`](#utf32_encode_be)
- **Function**: [`utf32_encode_le`](#utf32_encode_le)
- **Function**: [`utf32_decode`](#utf32_decode)
- **Function**: [`utf32_decode_be`](#utf32_decode_be)
- **Function**: [`utf32_decode_le`](#utf32_decode_le)

---

### `Encoding` <a id="Encoding"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Encoding
```

Static namespace wrapper providing data encoding and decoding routines.

#### Members

- `pub fn base64_encode(data: list): str` *(method)*
- `pub fn base64_decode(data: str): list` *(method)*
- `pub fn hex_encode(data: list): str` *(method)*
- `pub fn hex_decode(data: str): list` *(method)*
- `pub fn byte_to_hex(b: int): str` *(method)*
- `pub fn hex_to_byte(h: str): int` *(method)*
- `pub fn url_encode(s: str): str` *(method)*
- `pub fn url_decode(s: str): str` *(method)*
- `pub fn utf16_encode(s: str): list` *(method)*
- `pub fn utf16_encode_be(s: str): list` *(method)*
- `pub fn utf16_encode_le(s: str): list` *(method)*
- `pub fn utf16_decode(units: list): str` *(method)*
- `pub fn utf16_decode_be(bytes: list): str` *(method)*
- `pub fn utf16_decode_le(bytes: list): str` *(method)*
- `pub fn utf32_encode(s: str): list` *(method)*
- `pub fn utf32_encode_be(s: str): list` *(method)*
- `pub fn utf32_encode_le(s: str): list` *(method)*
- `pub fn utf32_decode(cps: list): str` *(method)*
- `pub fn utf32_decode_be(bytes: list): str` *(method)*
- `pub fn utf32_decode_le(bytes: list): str` *(method)*

---

### `base64_encode` <a id="base64_encode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn base64_encode(data: list): str
```

Encodes binary bytes into an RFC 4648 Base64 string.

---

### `base64_decode` <a id="base64_decode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn base64_decode(data: str): list
```

Decodes an RFC 4648 Base64 string into a byte array.

---

### `hex_encode` <a id="hex_encode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hex_encode(data: list): str
```

Encodes binary bytes into a lowercase hexadecimal string.

---

### `hex_decode` <a id="hex_decode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hex_decode(data: str): list
```

Decodes a hexadecimal string into a byte array.

---

### `byte_to_hex` <a id="byte_to_hex"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn byte_to_hex(b: int): str
```

Converts a single byte value (0-255) to a two-character hex string.

---

### `hex_to_byte` <a id="hex_to_byte"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hex_to_byte(h: str): int
```

Parses a two-character hex string into a single byte value.

---

### `url_encode` <a id="url_encode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn url_encode(s: str): str
```

Encodes reserved URL characters into percent-encoded form.

---

### `url_decode` <a id="url_decode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn url_decode(s: str): str
```

Decodes percent-encoded sequences in a URL string.

---

### `utf16_encode` <a id="utf16_encode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn utf16_encode(s: str): list
```

Encodes a string into 16-bit UTF-16 code units.

---

### `utf16_encode_be` <a id="utf16_encode_be"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn utf16_encode_be(s: str): list
```

Encodes a string into big-endian UTF-16 bytes.

---

### `utf16_encode_le` <a id="utf16_encode_le"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn utf16_encode_le(s: str): list
```

Encodes a string into little-endian UTF-16 bytes.

---

### `utf16_decode` <a id="utf16_decode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn utf16_decode(units: list): str
```

Decodes 16-bit UTF-16 code units into a UTF-8 string.

---

### `utf16_decode_be` <a id="utf16_decode_be"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn utf16_decode_be(bytes: list): str
```

Decodes big-endian UTF-16 bytes into a UTF-8 string.

---

### `utf16_decode_le` <a id="utf16_decode_le"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn utf16_decode_le(bytes: list): str
```

Decodes little-endian UTF-16 bytes into a UTF-8 string.

---

### `utf32_encode` <a id="utf32_encode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn utf32_encode(s: str): list
```

Encodes a string into 32-bit Unicode code points.

---

### `utf32_encode_be` <a id="utf32_encode_be"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn utf32_encode_be(s: str): list
```

Encodes a string into big-endian UTF-32 bytes.

---

### `utf32_encode_le` <a id="utf32_encode_le"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn utf32_encode_le(s: str): list
```

Encodes a string into little-endian UTF-32 bytes.

---

### `utf32_decode` <a id="utf32_decode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn utf32_decode(cps: list): str
```

Decodes 32-bit Unicode code points into a UTF-8 string.

---

### `utf32_decode_be` <a id="utf32_decode_be"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn utf32_decode_be(bytes: list): str
```

Decodes big-endian UTF-32 bytes into a UTF-8 string.

---

### `utf32_decode_le` <a id="utf32_decode_le"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn utf32_decode_le(bytes: list): str
```

Decodes little-endian UTF-32 bytes into a UTF-8 string.

---


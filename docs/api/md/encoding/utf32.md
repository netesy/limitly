# API Documentation: `utf32.lm`

## Overview

std/encoding/utf32.lm
UTF-32 Encoding and Decoding (Code Points, BE, LE).

## Symbols

- **Function**: [`cp_to_utf8_bytes`](#cp_to_utf8_bytes)
- **Function**: [`encode_utf32`](#encode_utf32)
- **Function**: [`encode_utf32_be`](#encode_utf32_be)
- **Function**: [`encode_utf32_le`](#encode_utf32_le)
- **Function**: [`decode_utf32`](#decode_utf32)
- **Function**: [`decode_utf32_be`](#decode_utf32_be)
- **Function**: [`decode_utf32_le`](#decode_utf32_le)

---

### `cp_to_utf8_bytes` <a id="cp_to_utf8_bytes"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn cp_to_utf8_bytes(cp: int): list
```

Helper function to convert a 32-bit Unicode code point to UTF-8 bytes.

---

### `encode_utf32` <a id="encode_utf32"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode_utf32(s: str): list
```

Encodes a UTF-8 string into a list of 32-bit Unicode code points.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Each Unicode scalar value maps directly to an integer code point.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Input Unicode string. |

#### Returns

Array of 32-bit integer code points [int].

#### Example: Idiomatic Usage

```lymar
import std.encoding.utf32 as utf32;
var cps = utf32.encode_utf32("Limitless");
print("Code point count: {len(cps)}");
```

---

### `encode_utf32_be` <a id="encode_utf32_be"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode_utf32_be(s: str): list
```

Encodes a UTF-8 string into big-endian UTF-32 bytes (4 bytes per code point).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Input Unicode string. |

#### Returns

Array of big-endian bytes [int].

---

### `encode_utf32_le` <a id="encode_utf32_le"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode_utf32_le(s: str): list
```

Encodes a UTF-8 string into little-endian UTF-32 bytes (4 bytes per code point).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Input Unicode string. |

#### Returns

Array of little-endian bytes [int].

---

### `decode_utf32` <a id="decode_utf32"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decode_utf32(codepoints: list): str
```

Decodes an array of 32-bit Unicode code points into a UTF-8 string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `codepoints` | Array of Unicode code points. |

#### Returns

Decoded UTF-8 string.

---

### `decode_utf32_be` <a id="decode_utf32_be"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decode_utf32_be(bytes: list): str
```

Decodes an array of big-endian UTF-32 bytes into a UTF-8 string.

#### Preconditions (Contracts)

- `requires len(bytes) % 4 == 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `bytes` | Big-endian byte array. |

#### Returns

Decoded UTF-8 string.

---

### `decode_utf32_le` <a id="decode_utf32_le"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decode_utf32_le(bytes: list): str
```

Decodes an array of little-endian UTF-32 bytes into a UTF-8 string.

#### Preconditions (Contracts)

- `requires len(bytes) % 4 == 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `bytes` | Little-endian byte array. |

#### Returns

Decoded UTF-8 string.

---


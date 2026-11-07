# API Documentation: `utf16.lm`

## Overview

std/encoding/utf16.lm
UTF-16 Encoding and Decoding (Code Units, BE, LE, Surrogate Pairs).

## Symbols

- **Function**: [`cp_to_utf8_bytes`](#cp_to_utf8_bytes)
- **Function**: [`encode_utf16`](#encode_utf16)
- **Function**: [`encode_utf16_be`](#encode_utf16_be)
- **Function**: [`encode_utf16_le`](#encode_utf16_le)
- **Function**: [`decode_utf16`](#decode_utf16)
- **Function**: [`decode_utf16_be`](#decode_utf16_be)
- **Function**: [`decode_utf16_le`](#decode_utf16_le)

---

### `cp_to_utf8_bytes` <a id="cp_to_utf8_bytes"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn cp_to_utf8_bytes(cp: int): list
```

Helper function to convert a Unicode code point to UTF-8 bytes.

---

### `encode_utf16` <a id="encode_utf16"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode_utf16(s: str): list
```

Encodes a UTF-8 string into a sequence of 16-bit UTF-16 code units.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Supplementary characters outside the BMP (>= U+10000) are automatically split into surrogate pairs (high surrogate: 0xD800-0xDBFF, low surrogate: 0xDC00-0xDFFF).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Source Unicode string. |

#### Returns

Array of 16-bit code units [int].

#### Example: Idiomatic Usage

```lymar
import std.encoding.utf16 as utf16;
var units = utf16.encode_utf16("Hello");
print("Code units: {len(units)}");
```

---

### `encode_utf16_be` <a id="encode_utf16_be"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode_utf16_be(s: str): list
```

Encodes a UTF-8 string into big-endian UTF-16 bytes (2 bytes per unit).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Source Unicode string. |

#### Returns

Array of big-endian bytes [int].

---

### `encode_utf16_le` <a id="encode_utf16_le"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode_utf16_le(s: str): list
```

Encodes a UTF-8 string into little-endian UTF-16 bytes (2 bytes per unit).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Source Unicode string. |

#### Returns

Array of little-endian bytes [int].

---

### `decode_utf16` <a id="decode_utf16"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decode_utf16(units: list): str
```

Decodes an array of 16-bit UTF-16 code units into a UTF-8 string.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Correctly combines high and low surrogate pairs back into 32-bit code points.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `units` | Array of 16-bit code units. |

#### Returns

Decoded UTF-8 string.

---

### `decode_utf16_be` <a id="decode_utf16_be"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decode_utf16_be(bytes: list): str
```

Decodes an array of big-endian UTF-16 bytes into a UTF-8 string.

#### Preconditions (Contracts)

- `requires len(bytes) % 2 == 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `bytes` | Big-endian byte array. |

#### Returns

Decoded UTF-8 string.

---

### `decode_utf16_le` <a id="decode_utf16_le"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decode_utf16_le(bytes: list): str
```

Decodes an array of little-endian UTF-16 bytes into a UTF-8 string.

#### Preconditions (Contracts)

- `requires len(bytes) % 2 == 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `bytes` | Little-endian byte array. |

#### Returns

Decoded UTF-8 string.

---


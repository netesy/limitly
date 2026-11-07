# API Documentation: `index.lm`

## Overview

std/bytes/index.lm
Public entrypoint and facade for std.bytes. Byte buffer manipulation, binary slicing, and endian utilities.

## Symbols

- **Frame**: [`ByteBuffer`](#ByteBuffer)
- **Function**: [`encode_i32_be`](#encode_i32_be)
- **Function**: [`encode_i32_le`](#encode_i32_le)
- **Function**: [`decode_i32_be`](#decode_i32_be)
- **Function**: [`decode_i32_le`](#decode_i32_le)

---

### `ByteBuffer` <a id="ByteBuffer"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ByteBuffer
```

Dynamically expanding byte buffer supporting sequential appending, indexing, and hex formatting.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `initial` | Optional starting list of byte values. |

#### Members

- `var pub data: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn append(byte: int)` *(method)*
- `pub fn append_all(bytes: list)` *(method)*
- `pub fn get(idx: int): int` *(method)*
- `pub fn len(): int` *(method)*
- `pub fn to_hex(): str` *(method)*

---

### `encode_i32_be` <a id="encode_i32_be"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode_i32_be(value: int): list
```

Encodes a 32-bit integer into a 4-byte big-endian array.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Integer to encode. |

#### Returns

4-element byte array [MSB, ..., LSB].

---

### `encode_i32_le` <a id="encode_i32_le"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode_i32_le(value: int): list
```

Encodes a 32-bit integer into a 4-byte little-endian array.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Integer to encode. |

#### Returns

4-element byte array [LSB, ..., MSB].

---

### `decode_i32_be` <a id="decode_i32_be"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decode_i32_be(bytes: list): int
```

Decodes a 32-bit big-endian integer from the first 4 bytes of an array.

#### Preconditions (Contracts)

- `requires len(bytes) >= 4`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `bytes` | Byte array of length at least 4. |

#### Returns

Decoded 32-bit integer.

---

### `decode_i32_le` <a id="decode_i32_le"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decode_i32_le(bytes: list): int
```

Decodes a 32-bit little-endian integer from the first 4 bytes of an array.

#### Preconditions (Contracts)

- `requires len(bytes) >= 4`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `bytes` | Byte array of length at least 4. |

#### Returns

Decoded 32-bit integer.

---


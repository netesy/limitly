# API Documentation: `base64.lm`

## Overview

std/encoding/base64.lm
RFC 4648 Base64 Encoding and Decoding.

## Symbols

- **Function**: [`get_b64_index`](#get_b64_index)
- **Function**: [`encode_base64`](#encode_base64)
- **Function**: [`decode_base64`](#decode_base64)

---

### `get_b64_index` <a id="get_b64_index"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn get_b64_index(ch: str): int
```

Decodes an ASCII character to its 6-bit Base64 index.

---

### `encode_base64` <a id="encode_base64"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode_base64(bytes: list): str
```

Encodes an array of binary bytes into an RFC 4648 Base64 string with `=` padding.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Base64 transforms arbitrary binary payloads into URL/safe text representations.

> [!NOTE]
> **Note**: Every 3 bytes of input generate 4 Base64 characters; partial blocks are padded with `=`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `bytes` | Array of byte values (0-255) to encode. |

#### Returns

Encoded Base64 ASCII string.

#### Example: Idiomatic Usage

```lymar
import std.encoding.base64 as b64;
var encoded = b64.encode_base64([72, 101, 108, 108, 111]);
print("Base64: {encoded}"); // "SGVsbG8="
```

---

### `decode_base64` <a id="decode_base64"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decode_base64(s: str): list
```

Decodes an RFC 4648 Base64 encoded string into a byte array.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Handles `=` padding automatically.

> [!WARNING]
> **Warning**: Malformed inputs or non-base64 characters evaluate to zero bits.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Base64 encoded string to decode. |

#### Returns

Array of decoded integer bytes.

#### Example: Idiomatic Usage

```lymar
import std.encoding.base64 as b64;
var bytes = b64.decode_base64("SGVsbG8=");
print("Byte count: {len(bytes)}");
```

---


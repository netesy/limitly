# API Documentation: `index.lm`

## Overview

std/compress/index.lm
Clean standard library entrypoint for data compression

## Symbols

- **Function**: [`compress`](#compress)
- **Function**: [`decompress`](#decompress)
- **Function**: [`compress_hex`](#compress_hex)
- **Function**: [`decompress_hex`](#decompress_hex)

---

### `compress` <a id="compress"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compress(data: str, level: int = ...): str?
```

Compresses an input string into deflate hex representation.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Recommended level 6 for best compression ratio vs performance.

#### Preconditions (Contracts)

- `requires level >= 0 and level <= 9`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `data` | Plain text or binary string to compress. |
| `level` | Compression level between 0 and 9 (default: 6). |

#### Returns

Fallible compressed hex string.

---

### `decompress` <a id="decompress"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decompress(compressed: str, max_limit: int = ...): str?
```

Decompresses a hex-encoded deflate payload.

> [!WARNING]
> **Warning**: Enforce memory limits when handling untrusted inputs.

#### Preconditions (Contracts)

- `requires max_limit > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `compressed` | Hex-encoded compressed payload. |
| `max_limit` | Maximum decompressed bytes allowed (default: 10MB). |

#### Returns

Fallible decompressed string.

---

### `compress_hex` <a id="compress_hex"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compress_hex(data: str, level: int = ...): str?
```

Compresses an input string into raw deflate bytes encoded as hex.

#### Preconditions (Contracts)

- `requires level >= 0 and level <= 9`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `data` | String data to compress. |
| `level` | Compression level (0..9). |

#### Returns

Fallible compressed hex string.

---

### `decompress_hex` <a id="decompress_hex"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decompress_hex(compressed_hex: str, max_limit: int = ...): str?
```

Decompresses a hex-encoded deflate payload into plain text.

#### Preconditions (Contracts)

- `requires max_limit > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `compressed_hex` | Hex-encoded compressed payload. |
| `max_limit` | Maximum decompressed bytes allowed. |

#### Returns

Fallible decompressed string.

---


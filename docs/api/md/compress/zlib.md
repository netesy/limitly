# API Documentation: `zlib.lm`

## Overview

std/compress/zlib.lm
Dynamic buffer zlib compression and decompression

## Symbols

- **Frame**: [`Zlib`](#Zlib)
- **Function**: [`compress_hex`](#compress_hex)
- **Function**: [`decompress_hex`](#decompress_hex)
- **Function**: [`compress`](#compress)
- **Function**: [`decompress`](#decompress)

---

### `Zlib` <a id="Zlib"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Zlib
```

Dynamic buffer zlib compression and decompression engine.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Prefer reusing compression buffers and default compression level 6 for the optimal trade-off between memory usage and throughput.

> [!NOTE]
> **Note**: Thread-safe and allocation-safe.

#### Members

- `pub fn compress(data: str): str?` *(method)*
- `pub fn decompress(compressed_hex: str): str?` *(method)*
- `pub fn compress_hex(data: str): str?` *(method)*
- `pub fn decompress_hex(compressed_hex: str): str?` *(method)*

---

### `compress_hex` <a id="compress_hex"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compress_hex(data: str, level: int = ...): str?
```

Compresses an input string into raw deflate/zlib bytes encoded as hex.

> [!TIP]
> **Idiomatic Usage & Best Practice**: The idiomatic and recommended way to compress data is level 6: it achieves 95% of maximal compression while running 4x faster than level 9.

> [!WARNING]
> **Warning**: Always enforce a maximum buffer limit when decompressing untrusted inputs to prevent memory exhaustion and zip-bomb denial of service attacks.

> [!NOTE]
> **Note**: Thread-safe and allocation-safe; frees temporary native buffers on exit.

#### Preconditions (Contracts)

- `requires len(data) >= 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `data` | The raw ASCII or UTF-8 string to compress. |
| `level` | Compression level between 0 (store) and 9 (max compression). Default is 6. |

#### Returns

Returns ok(hex_str) on success, or err() on compression failure.

#### Example: Idiomatic Usage

```lymar
var payload = "Hello, high-performance Lymar compression!";
var compressed = compress_hex(payload, 6)? else {
    print("Compression failed");
    return;
};
print("Compressed size: {len(compressed)}");
```

---

### `decompress_hex` <a id="decompress_hex"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decompress_hex(compressed_hex: str, max_limit: int = ...): str?
```

Decompresses a hex-encoded deflate payload into plain text.

> [!WARNING]
> **Warning**: Always set a realistic max_limit when decompressing untrusted inputs to protect against decompression bombs.

#### Preconditions (Contracts)

- `requires max_limit > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `compressed_hex` | The hex-encoded deflate string. |
| `max_limit` | Maximum decompressed bytes allowed (default: 10MB). |

#### Returns

Returns ok(uncompressed_str) on success, or err() on failure.

#### Example: Idiomatic Usage

```lymar
var decompressed = decompress_hex(compressed, 10485760)? else {
    print("Decompression failed");
    return;
};
```

---

### `compress` <a id="compress"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compress(data: str, level: int = ...): str?
```

Compresses an input string using zlib deflate algorithm.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Alias for compress_hex.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `data` | String data to compress. |
| `level` | Compression level between 0 and 9. |

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

> [!TIP]
> **Idiomatic Usage & Best Practice**: Alias for decompress_hex.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `compressed` | Hex-encoded compressed payload. |
| `max_limit` | Maximum decompressed bytes allowed. |

#### Returns

Fallible decompressed string.

---


# API Documentation: `hash.lm`

## Overview

std/crypto/hash.lm
Clean cryptographic hashing using OpenSSL EVP

## Symbols

- **Function**: [`algo_name`](#algo_name)
- **Function**: [`_open_lib`](#_open_lib)
- **Frame**: [`Hasher`](#Hasher)
- **Function**: [`hash`](#hash)
- **Function**: [`sha256`](#sha256)
- **Function**: [`sha512`](#sha512)
- **Function**: [`sha384`](#sha384)
- **Function**: [`sha1`](#sha1)
- **Function**: [`md5`](#md5)

---

### `algo_name` <a id="algo_name"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn algo_name(algo): str
```

Returns the normalized lowercase algorithm name string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `algo` | Algorithm identifier (`HashAlgorithm` enum variant or string like `"sha256"`). |

#### Returns

Lowercase algorithm string.

---

### `_open_lib` <a id="_open_lib"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn _open_lib(): int
```

---

### `Hasher` <a id="Hasher"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Hasher: Disposable
```

── Streaming Hasher frame ─────────────────────────────────────────────────

#### Members

- `var pub algorithm: str` *(field)*
- `var pub ctx: any` *(field)*
- `var pub is_open: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn dispose(): nil` *(method)*
- `pub fn update(data: str): Hasher` *(method)*
- `pub fn hex(): str` *(method)*
- `pub fn digest(): str` *(method)*

---

### `hash` <a id="hash"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hash(algo, data: str): str
```

Calculates a one-shot cryptographic hash of input data.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `algo` | Hash algorithm (`HashAlgorithm` enum or string identifier). |
| `data` | Input string to hash. |

#### Returns

Hexadecimal digest string.

#### Example: Idiomatic Usage

```lymar
var hex_digest = hash.hash("sha256", "hello world");
```

---

### `sha256` <a id="sha256"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sha256(data: str): str
```

---

### `sha512` <a id="sha512"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sha512(data: str): str
```

---

### `sha384` <a id="sha384"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sha384(data: str): str
```

---

### `sha1` <a id="sha1"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sha1(data: str): str
```

---

### `md5` <a id="md5"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn md5(data: str): str
```

---


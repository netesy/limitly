# API Documentation: `hmac.lm`

## Overview

std/crypto/hmac.lm
Clean HMAC implementation using OpenSSL EVP HMAC

## Symbols

- **Frame**: [`HMAC`](#HMAC)
- **Function**: [`hmac`](#hmac)
- **Function**: [`sha256`](#sha256)
- **Function**: [`sha512`](#sha512)

---

### `HMAC` <a id="HMAC"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame HMAC
```

Namespace helper frame for HMAC message authentication operations.

#### Members

- `pub fn compute(key: str, data: str): str` *(method)*
- `pub fn sha256(key: str, data: str): str` *(method)*
- `pub fn sha512(key: str, data: str): str` *(method)*
- `pub fn sha384(key: str, data: str): str` *(method)*
- `pub fn md5(key: str, data: str): str` *(method)*
- `pub fn sha1(key: str, data: str): str` *(method)*

---

### `hmac` <a id="hmac"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hmac(algo: str, key: str, data: str): str
```

Computes an HMAC signature using OpenSSL EVP_MAC for arbitrary digest algorithms.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `algo` | Digest algorithm name (e.g. `"sha256"`, `"sha512"`). |
| `key` | Secret key string. |
| `data` | Message payload to authenticate. |

#### Returns

Hexadecimal HMAC signature string.

---

### `sha256` <a id="sha256"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sha256(key: str, data: str): str
```

Computes an HMAC-SHA256 signature for message authentication.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Secret key string. |
| `data` | Message payload. |

#### Returns

64-character lowercase hex signature.

---

### `sha512` <a id="sha512"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sha512(key: str, data: str): str
```

Computes an HMAC-SHA512 signature for message authentication.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Secret key string. |
| `data` | Message payload. |

#### Returns

128-character lowercase hex signature.

---


# API Documentation: `index.lm`

## Overview

std/crypto/index.lm
Clean, unified Cryptography standard library facade powered by OpenSSL

## Symbols

- **Function**: [`hash`](#hash)
- **Function**: [`sha256`](#sha256)
- **Function**: [`sha512`](#sha512)
- **Function**: [`sha384`](#sha384)
- **Function**: [`sha1`](#sha1)
- **Function**: [`md5`](#md5)
- **Function**: [`hmac`](#hmac)
- **Function**: [`hmac_sha256`](#hmac_sha256)
- **Function**: [`hmac_sha512`](#hmac_sha512)
- **Function**: [`encrypt_gcm`](#encrypt_gcm)
- **Function**: [`decrypt_gcm`](#decrypt_gcm)
- **Function**: [`encrypt_cbc`](#encrypt_cbc)
- **Function**: [`decrypt_cbc`](#decrypt_cbc)
- **Function**: [`random_hex`](#random_hex)
- **Function**: [`uuid`](#uuid)
- **Function**: [`random_int`](#random_int)
- **Function**: [`random_string`](#random_string)

---

### `hash` <a id="hash"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hash(algo, data: str): str
```

Calculates a one-shot cryptographic hash of input data using the specified algorithm.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `algo` | Algorithm (`HashAlgorithm` enum or string identifier e.g. `"sha256"`). |
| `data` | String data to hash. |

#### Returns

Hex-encoded digest string.

#### Example: Idiomatic Usage

```lymar
var digest = crypto.hash("sha256", "data");
```

---

### `sha256` <a id="sha256"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sha256(data: str): str
```

Computes SHA-256 hexadecimal digest of input data.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `data` | Plain text or binary string to hash. |

#### Returns

64-character lowercase hex digest string.

---

### `sha512` <a id="sha512"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sha512(data: str): str
```

Computes SHA-512 hexadecimal digest of input data.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `data` | Plain text or binary string to hash. |

#### Returns

128-character lowercase hex digest string.

---

### `sha384` <a id="sha384"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sha384(data: str): str
```

Computes SHA-384 hexadecimal digest of input data.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `data` | Plain text or binary string to hash. |

#### Returns

96-character lowercase hex digest string.

---

### `sha1` <a id="sha1"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sha1(data: str): str
```

Computes legacy SHA-1 hexadecimal digest of input data.

> [!WARNING]
> **Warning**: SHA-1 is cryptographically broken; prefer SHA-256 for secure hashing.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `data` | Plain text or binary string to hash. |

#### Returns

40-character lowercase hex digest string.

---

### `md5` <a id="md5"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn md5(data: str): str
```

Computes legacy MD5 hexadecimal digest of input data.

> [!WARNING]
> **Warning**: MD5 is cryptographically broken; use only for legacy compatibility or checksums.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `data` | Plain text or binary string to hash. |

#### Returns

32-character lowercase hex digest string.

---

### `hmac` <a id="hmac"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hmac(algo: str, key: str, data: str): str
```

Computes an HMAC signature using a chosen digest algorithm.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `algo` | Digest algorithm (e.g. `"sha256"`, `"sha512"`). |
| `key` | Secret key string. |
| `data` | Message payload to authenticate. |

#### Returns

Hexadecimal HMAC signature.

---

### `hmac_sha256` <a id="hmac_sha256"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hmac_sha256(key: str, data: str): str
```

Computes an HMAC-SHA256 signature for message authentication.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Secret key string. |
| `data` | Message payload to authenticate. |

#### Returns

64-character lowercase hex HMAC signature.

---

### `hmac_sha512` <a id="hmac_sha512"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hmac_sha512(key: str, data: str): str
```

Computes an HMAC-SHA512 signature for high-security message authentication.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Secret key string. |
| `data` | Message payload to authenticate. |

#### Returns

128-character lowercase hex HMAC signature.

---

### `encrypt_gcm` <a id="encrypt_gcm"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encrypt_gcm(key: str, iv: str, plaintext: str, aad: str = ...): cipher.GcmCipher?
```

Encrypts plaintext using authenticated AES-GCM (Galois/Counter Mode).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Hex-encoded AES key (16, 24, or 32 bytes for AES-128/192/256). |
| `iv` | Hex-encoded initialization vector (typically 12 bytes / 24 hex characters). |
| `plaintext` | Plain text data to encrypt. |
| `aad` | Optional additional authenticated data. |

#### Returns

Fallible `GcmCipher` structure containing ciphertext and authentication tag.

---

### `decrypt_gcm` <a id="decrypt_gcm"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decrypt_gcm(key: str, iv: str, ciphertext: str, tag: str, aad: str = ...): str?
```

Decrypts and authenticates AES-GCM ciphertext using the provided authentication tag.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Hex-encoded AES key. |
| `iv` | Hex-encoded initialization vector. |
| `ciphertext` | Hex-encoded ciphertext payload. |
| `tag` | Hex-encoded 16-byte authentication tag. |
| `aad` | Optional additional authenticated data matching encryption. |

#### Returns

Fallible decrypted plaintext string.

---

### `encrypt_cbc` <a id="encrypt_cbc"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encrypt_cbc(key: str, iv: str, plaintext: str): str?
```

Encrypts plaintext using AES in CBC mode with PKCS#7 padding.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Hex-encoded AES key. |
| `iv` | Hex-encoded 16-byte initialization vector. |
| `plaintext` | Plain text data to encrypt. |

#### Returns

Fallible hex-encoded ciphertext.

---

### `decrypt_cbc` <a id="decrypt_cbc"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decrypt_cbc(key: str, iv: str, ciphertext: str): str?
```

Decrypts hex-encoded AES-CBC ciphertext with PKCS#7 unpadding.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Hex-encoded AES key. |
| `iv` | Hex-encoded 16-byte initialization vector. |
| `ciphertext` | Hex-encoded ciphertext to decrypt. |

#### Returns

Fallible decrypted plaintext string.

---

### `random_hex` <a id="random_hex"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_hex(num_bytes: int): str
```

Generates cryptographically secure random bytes formatted as a lowercase hex string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `num_bytes` | Number of random bytes to generate. |

#### Returns

Hex string of length `num_bytes * 2`.

---

### `uuid` <a id="uuid"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn uuid(): str
```

Generates a RFC 4122 Version 4 random UUID string.

#### Returns

Formatted UUID string (e.g. `"f47ac10b-58cc-4372-a567-0e02b2c3d479"`).

---

### `random_int` <a id="random_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_int(min: int, max: int): int
```

Generates a cryptographically secure random integer within `[min, max]`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `min` | Minimum inclusive bound. |
| `max` | Maximum inclusive bound. |

#### Returns

Random integer `n` such that `min <= n <= max`.

---

### `random_string` <a id="random_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_string(length: int, alphabet: str = ...): str
```

Generates a cryptographically secure random string of given length using a character set.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `length` | Number of characters to generate. |
| `alphabet` | Character set to sample from (default: alphanumeric). |

#### Returns

Secure random string.

---


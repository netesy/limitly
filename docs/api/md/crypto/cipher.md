# API Documentation: `cipher.lm`

## Overview

std/crypto/cipher.lm
Clean authenticated & symmetric encryption using OpenSSL (AES-256-GCM and AES-256-CBC)

## Symbols

- **Frame**: [`GcmCipher`](#GcmCipher)
- **Frame**: [`AES`](#AES)
- **Function**: [`encrypt_gcm`](#encrypt_gcm)
- **Function**: [`decrypt_gcm`](#decrypt_gcm)
- **Function**: [`encrypt_cbc`](#encrypt_cbc)
- **Function**: [`decrypt_cbc`](#decrypt_cbc)

---

### `GcmCipher` <a id="GcmCipher"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame GcmCipher
```

Container holding AEAD ciphertext and its matching authentication tag.

#### Members

- `var pub ciphertext: str` *(field)*
- `var pub tag: str` *(field)*
- `pub init()` *(constructor)*

---

### `AES` <a id="AES"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame AES
```

AES encryption and decryption operations helper namespace.

#### Members

- `pub fn encrypt_gcm(key: str, iv: str, plaintext: str): GcmCipher?` *(method)*
- `pub fn decrypt_gcm(key: str, iv: str, ciphertext: str, tag: str): str?` *(method)*
- `pub fn encrypt_cbc(key: str, iv: str, plaintext: str): str?` *(method)*
- `pub fn decrypt_cbc(key: str, iv: str, ciphertext: str): str?` *(method)*

---

### `encrypt_gcm` <a id="encrypt_gcm"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encrypt_gcm(key: str, iv: str, plaintext: str, aad: str = ...): GcmCipher?
```

Encrypts plaintext using AES-GCM authenticated encryption.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Hex-encoded encryption key. |
| `iv` | Hex-encoded initialization vector. |
| `plaintext` | Plain text data to encrypt. |
| `aad` | Optional additional authenticated data. |

#### Returns

Fallible `GcmCipher` holding ciphertext and authentication tag.

---

### `decrypt_gcm` <a id="decrypt_gcm"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decrypt_gcm(key: str, iv: str, ciphertext: str, tag: str, aad: str = ...): str?
```

Decrypts AES-GCM authenticated ciphertext.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Hex-encoded encryption key. |
| `iv` | Hex-encoded initialization vector. |
| `ciphertext` | Hex-encoded ciphertext string. |
| `tag` | Hex-encoded authentication tag. |
| `aad` | Optional additional authenticated data. |

#### Returns

Fallible decrypted plaintext string.

---

### `encrypt_cbc` <a id="encrypt_cbc"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encrypt_cbc(key: str, iv: str, plaintext: str): str?
```

Encrypts plaintext using AES-CBC mode with PKCS#7 padding.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Hex-encoded encryption key. |
| `iv` | Hex-encoded 16-byte initialization vector. |
| `plaintext` | Plain text data to encrypt. |

#### Returns

Fallible hex-encoded ciphertext string.

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
| `key` | Hex-encoded encryption key. |
| `iv` | Hex-encoded 16-byte initialization vector. |
| `ciphertext` | Hex-encoded ciphertext string. |

#### Returns

Fallible decrypted plaintext string.

---


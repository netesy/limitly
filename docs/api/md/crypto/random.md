# API Documentation: `random.lm`

## Overview

std/crypto/random.lm
Clean cryptographically secure pseudo-random number generator (CSPRNG) using OpenSSL

## Symbols

- **Frame**: [`Random`](#Random)
- **Function**: [`random_hex`](#random_hex)
- **Function**: [`uuid`](#uuid)
- **Function**: [`random_int`](#random_int)
- **Function**: [`random_string`](#random_string)

---

### `Random` <a id="Random"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Random
```

Namespace helper frame for cryptographically secure pseudo-random generation.

#### Members

- `pub fn hex(num_bytes: int): str` *(method)*
- `pub fn uuid(): str` *(method)*
- `pub fn int_range(min: int, max: int): int` *(method)*
- `pub fn string(length: int): str` *(method)*

---

### `random_hex` <a id="random_hex"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_hex(num_bytes: int): str
```

Generates cryptographically secure random bytes as a lowercase hex string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `num_bytes` | Number of random bytes to draw. |

#### Returns

Hexadecimal representation of random bytes.

---

### `uuid` <a id="uuid"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn uuid(): str
```

Generates a cryptographically secure RFC 4122 v4 UUID string.

#### Returns

Formatted UUID string (e.g. `"f47ac10b-58cc-4372-a567-0e02b2c3d479"`).

---

### `random_int` <a id="random_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_int(min: int, max: int): int
```

Generates a uniform cryptographically secure integer between `min` and `max`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `min` | Lower bound (inclusive). |
| `max` | Upper bound (inclusive). |

#### Returns

Random integer in `[min, max]`.

---

### `random_string` <a id="random_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_string(length: int, alphabet: str = ...): str
```

Generates a secure random string of specified length using a selected alphabet.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `length` | Number of characters to generate. |
| `alphabet` | Character pool string (defaults to alphanumeric). |

#### Returns

Secure random character string.

---


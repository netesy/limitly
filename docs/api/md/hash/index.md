# API Documentation: `index.lm`

## Overview

std/hash/index.lm
Non-cryptographic hash functions for hash tables, checksums, and general use.
For cryptographic hashing (SHA-256, SHA-512, MD5, SHA-1), see std/crypto/hash.lm.

## Symbols

- **Function**: [`fnv1a_32`](#fnv1a_32)
- **Function**: [`fnv1a_32_str`](#fnv1a_32_str)
- **Function**: [`fnv1a_64_str`](#fnv1a_64_str)
- **Function**: [`djb2`](#djb2)
- **Function**: [`sdbm`](#sdbm)
- **Function**: [`jenkins_oaat`](#jenkins_oaat)
- **Function**: [`murmur3_32`](#murmur3_32)
- **Function**: [`crc32`](#crc32)
- **Function**: [`adler32`](#adler32)
- **Function**: [`combine_hashes`](#combine_hashes)
- **Function**: [`hash_bytes`](#hash_bytes)
- **Function**: [`hash_string`](#hash_string)
- **Function**: [`hash_with_seed`](#hash_with_seed)
- **Function**: [`byte_value`](#byte_value)

---

### `fnv1a_32` <a id="fnv1a_32"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fnv1a_32(data: list): int
```

Computes the 32-bit Fowler-Noll-Vo (FNV-1a) hash of a byte array.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Fast, excellent avalanche properties for short keys in hash maps.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `data` | Array of byte integers. |

#### Returns

32-bit unsigned integer hash value.

---

### `fnv1a_32_str` <a id="fnv1a_32_str"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fnv1a_32_str(s: str): int
```

Computes the 32-bit Fowler-Noll-Vo (FNV-1a) hash of an ASCII string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Source ASCII string. |

#### Returns

32-bit integer hash value.

---

### `fnv1a_64_str` <a id="fnv1a_64_str"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fnv1a_64_str(s: str): int
```

Computes a 64-bit FNV-1a hash of a string, returning the lower 32-bit slice.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Source string. |

#### Returns

32-bit integer hash value.

---

### `djb2` <a id="djb2"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn djb2(s: str): int
```

Computes the classic DJB2 hash of a string (by Dan Bernstein).

> [!TIP]
> **Idiomatic Usage & Best Practice**: Highly efficient for string keys in hash tables with good distribution.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Source string. |

#### Returns

Positive 31-bit integer hash value.

---

### `sdbm` <a id="sdbm"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sdbm(s: str): int
```

Computes the SDBM hash of a string (used in Sleepycat DB / Berkeley DB).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Source string. |

#### Returns

Positive 31-bit integer hash value.

---

### `jenkins_oaat` <a id="jenkins_oaat"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn jenkins_oaat(s: str): int
```

Computes the Jenkins One-At-A-Time hash of a string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Source string. |

#### Returns

Positive 31-bit integer hash value.

---

### `murmur3_32` <a id="murmur3_32"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn murmur3_32(s: str, seed: int = ...): int
```

Computes the 32-bit MurmurHash3 (x86_32 variant) with a customizable seed.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Excellent hash uniformity and collision resistance for hash tables.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Source string. |
| `seed` | Integer seed value (default is 0). |

#### Returns

32-bit integer hash value.

#### Example: Idiomatic Usage

```lymar
var h = hash.murmur3_32("data", 42);
```

---

### `crc32` <a id="crc32"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn crc32(s: str): int
```

Computes standard table-driven IEEE 802.3 CRC32 checksum of a string.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Commonly used in network protocols (Ethernet) and container formats (ZIP, PNG).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Input string. |

#### Returns

32-bit CRC checksum integer.

---

### `adler32` <a id="adler32"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn adler32(s: str): int
```

Computes the Adler-32 checksum of a string (RFC 1950, zlib).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Input string. |

#### Returns

32-bit Adler-32 checksum integer.

---

### `combine_hashes` <a id="combine_hashes"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn combine_hashes(h1: int, h2: int): int
```

Combines two 32-bit hashes using the Boost `hash_combine` golden-ratio formula.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `h1` | First hash value. |
| `h2` | Second hash value. |

#### Returns

Combined 31-bit integer hash.

---

### `hash_bytes` <a id="hash_bytes"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hash_bytes(data: list): int
```

Computes the default hash for a byte array using FNV-1a.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `data` | Byte array. |

#### Returns

32-bit integer hash.

---

### `hash_string` <a id="hash_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hash_string(s: str): int
```

Computes the default hash for a string using FNV-1a.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Input string. |

#### Returns

32-bit integer hash.

---

### `hash_with_seed` <a id="hash_with_seed"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hash_with_seed(s: str, seed: int): int
```

Computes a seeded hash for a string using MurmurHash3.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Input string. |
| `seed` | Integer seed. |

#### Returns

32-bit integer hash.

---

### `byte_value` <a id="byte_value"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn byte_value(ch: str): int
```

---- Internal helper: convert single char to byte value ----

---


# API Documentation: `random.lm`

## Overview

std/random/random.lm
Pseudo-random number generator (Xorshift64*) and entropy-backed SecureRandom.

## Symbols

- **Frame**: [`Random`](#Random)
- **Frame**: [`SecureRandom`](#SecureRandom)
- **Function**: [`random_int`](#random_int)
- **Function**: [`random_float`](#random_float)
- **Function**: [`random_bool`](#random_bool)
- **Function**: [`random_bytes`](#random_bytes)
- **Function**: [`random_string`](#random_string)

---

### `Random` <a id="Random"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Random
```

High-performance pseudo-random number generator utilizing a 64-bit Xorshift PRNG.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Provide an explicit non-zero seed for reproducible, deterministic sequences (e.g. testing, simulations). Pass `0` or omit to seed automatically from system entropy.

> [!WARNING]
> **Warning**: `Random` is NOT cryptographically secure. Use `SecureRandom` for cryptographic tokens, nonces, or salts.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `seed` | Initial 64-bit seed. Pass 0 to seed automatically from system entropy. |

#### Example: Idiomatic Usage

```lymar
import std.random as rand;
var rng = rand.Random(seed=42);
var roll = rng.range_int(1, 7); // 1 to 6
```

#### Members

- `var state: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn next_int(): int` *(method)*
- `pub fn next_float(): float` *(method)*
- `pub fn next_bool(): bool` *(method)*
- `pub fn range_int(min_val: int, max_val: int): int` *(method)*
- `pub fn range_float(min_val: float, max_val: float): float` *(method)*
- `pub fn next_bytes(count: int): list` *(method)*
- `pub fn next_string(len_val: int): str` *(method)*

---

### `SecureRandom` <a id="SecureRandom"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame SecureRandom
```

Cryptographically secure random number generator sourced directly from system entropy.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Use for security-critical contexts such as generating session IDs, auth tokens, initialization vectors, and cryptographic nonces.

> [!NOTE]
> **Note**: Reads from underlying OS entropy sources (`/dev/urandom` on POSIX, `BCryptGenRandom` on Windows).

#### Members

- `var reader: res.Reader?` *(field)*
- `pub init()` *(constructor)*
- `pub fn next_int(): int` *(method)*
- `pub fn next_float(): float` *(method)*
- `pub fn next_bytes(count: int): list` *(method)*

---

### `random_int` <a id="random_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_int(min_val: int, max_val: int): int
```

Generates a random integer in `[min_val, max_val)` using the default PRNG.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `min_val` | Inclusive minimum bound. |
| `max_val` | Exclusive maximum bound. |

#### Returns

Random integer.

---

### `random_float` <a id="random_float"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_float(min_val: float, max_val: float): float
```

Generates a random float in `[min_val, max_val)` using the default PRNG.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `min_val` | Inclusive minimum bound. |
| `max_val` | Exclusive maximum bound. |

#### Returns

Random float.

---

### `random_bool` <a id="random_bool"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_bool(): bool
```

Generates a random boolean using the default PRNG.

#### Returns

Random boolean.

---

### `random_bytes` <a id="random_bytes"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_bytes(count: int): list
```

Generates `count` random bytes using the default PRNG.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `count` | Number of bytes to generate. |

#### Returns

Random byte list.

---

### `random_string` <a id="random_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_string(len_val: int): str
```

Generates a random alphanumeric string of length `len_val` using the default PRNG.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `len_val` | Length of the generated string. |

#### Returns

Random alphanumeric string.

---


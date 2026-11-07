# API Documentation: `random.lm`

## Overview

std/math/random.lm
Pseudorandom and entropy-backed number generation for mathematical simulations.

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

Lightweight pseudorandom number generator using a 64-bit linear/xorshift sequence.
Suitable for non-cryptographic simulations, games, and randomized algorithms.

> [!TIP]
> **Idiomatic Usage & Best Practice**: For cryptographic keys or tokens, use `SecureRandom` or `std.random.SecureRandom`.

#### Example: Idiomatic Usage

```lymar
import std.math.random as random;
var rng = random.Random(42);
print(rng.next_int());
```

#### Members

- `var state: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn next_int(): int` *(method)*
- `pub fn next_float(): float` *(method)*
- `pub fn next_bool(): bool` *(method)*
- `pub fn range_int(min: int, max: int): int` *(method)*
- `pub fn range_float(min: float, max: float): float` *(method)*
- `pub fn next_bytes(count: int): list` *(method)*
- `pub fn next_string(len_val: int): str` *(method)*

---

### `SecureRandom` <a id="SecureRandom"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame SecureRandom
```

Cryptographically secure entropy-backed random number generator.

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
pub fn random_int(min: int, max: int): int
```

Generates a random integer in range [min, max) using the default PRNG.

#### Preconditions (Contracts)

- `requires min <= max`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `min` | Inclusive minimum bound. |
| `max` | Exclusive maximum bound. |

#### Returns

Generated integer.

---

### `random_float` <a id="random_float"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_float(min: float, max: float): float
```

Generates a random float in range [min, max] using the default PRNG.

#### Preconditions (Contracts)

- `requires min <= max`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `min` | Inclusive minimum bound. |
| `max` | Inclusive maximum bound. |

#### Returns

Generated float.

---

### `random_bool` <a id="random_bool"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_bool(): bool
```

Generates a random boolean flag using the default PRNG.

#### Returns

Random boolean.

---

### `random_bytes` <a id="random_bytes"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_bytes(count: int): list
```

Generates a list of random byte integers using the default PRNG.

#### Preconditions (Contracts)

- `requires count >= 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `count` | Number of bytes. |

#### Returns

List of random bytes.

---

### `random_string` <a id="random_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_string(len_val: int): str
```

Generates a random alphanumeric string of length `len_val` using the default PRNG.

#### Preconditions (Contracts)

- `requires len_val >= 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `len_val` | Desired string length. |

#### Returns

Random alphanumeric string.

---


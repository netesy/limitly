# API Documentation: `arithmetic.lm`

## Overview

std/math/arithmetic.lm
Fundamental arithmetic operations, integer algorithms, rounding, powers, and roots.

## Symbols

- **Frame**: [`Int`](#Int)
- **Frame**: [`Float`](#Float)
- **Function**: [`abs`](#abs)
- **Function**: [`abs_int`](#abs_int)
- **Function**: [`gcd`](#gcd)
- **Function**: [`lcm`](#lcm)
- **Function**: [`factorial`](#factorial)
- **Function**: [`permutations`](#permutations)
- **Function**: [`combinations`](#combinations)
- **Function**: [`min`](#min)
- **Function**: [`max`](#max)
- **Function**: [`clamp`](#clamp)
- **Function**: [`sign`](#sign)
- **Function**: [`lerp`](#lerp)
- **Function**: [`floor`](#floor)
- **Function**: [`ceil`](#ceil)
- **Function**: [`round`](#round)
- **Function**: [`trunc`](#trunc)
- **Function**: [`fract`](#fract)
- **Function**: [`pow`](#pow)
- **Function**: [`sqrt`](#sqrt)
- **Function**: [`cbrt`](#cbrt)
- **Function**: [`hypot`](#hypot)
- **Function**: [`log`](#log)
- **Function**: [`log2`](#log2)
- **Function**: [`log10`](#log10)
- **Function**: [`exp`](#exp)
- **Function**: [`exp2`](#exp2)

---

### `Int` <a id="Int"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Int
```

Wrapper providing object-oriented arithmetic helpers for 64-bit signed integers.

#### Example: Idiomatic Usage

```lymar
import std.math.arithmetic as arithmetic;
var i = arithmetic.Int(-42);
print(i.abs()); // 42
```

#### Members

- `var pub value: int` *(field)*
- `pub init(value: int)` *(constructor)*
- `pub fn abs(): int` *(method)*
- `pub fn min(other: int): int` *(method)*
- `pub fn max(other: int): int` *(method)*

---

### `Float` <a id="Float"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Float
```

Wrapper providing object-oriented arithmetic, rounding, exponentiation, and logarithms for 64-bit floats.

#### Example: Idiomatic Usage

```lymar
import std.math.arithmetic as arithmetic;
var f = arithmetic.Float(16.0);
print(f.sqrt()); // 4.0
```

#### Members

- `var pub value: float` *(field)*
- `pub init(value: float)` *(constructor)*
- `pub fn abs(): float` *(method)*
- `pub fn min(other: float): float` *(method)*
- `pub fn max(other: float): float` *(method)*
- `pub fn floor(): int` *(method)*
- `pub fn ceil(): int` *(method)*
- `pub fn round(): int` *(method)*
- `pub fn trunc(): int` *(method)*
- `pub fn fract(): float` *(method)*
- `pub fn sqrt(): float` *(method)*
- `pub fn cbrt(): float` *(method)*
- `pub fn exp(): float` *(method)*
- `pub fn log(): float` *(method)*
- `pub fn log2(): float` *(method)*
- `pub fn log10(): float` *(method)*
- `pub fn exp2(): float` *(method)*
- `pub fn pow(exponent: float): float` *(method)*
- `pub fn hypot(other: float): float` *(method)*

---

### `abs` <a id="abs"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn abs(x: float): float
```

Returns the absolute value of a 64-bit float.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Input float. |

#### Returns

Absolute value |x|.

---

### `abs_int` <a id="abs_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn abs_int(x: int): int
```

Returns the absolute value of a 64-bit integer.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Input integer. |

#### Returns

Absolute value |x|.

---

### `gcd` <a id="gcd"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gcd(a: int, b: int): int
```

Computes the Greatest Common Divisor (GCD) of two integers using the Euclidean algorithm.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `a` | First integer. |
| `b` | Second integer. |

#### Returns

Greatest common divisor.

---

### `lcm` <a id="lcm"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lcm(a: int, b: int): int
```

Computes the Least Common Multiple (LCM) of two integers.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `a` | First integer. |
| `b` | Second integer. |

#### Returns

Least common multiple, or 0 if either operand is 0.

---

### `factorial` <a id="factorial"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn factorial(n: int): int
```

Computes the factorial of a non-negative integer (n!).

#### Preconditions (Contracts)

- `requires n >= 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `n` | Non-negative integer. |

#### Returns

Factorial n! (returns 0 for negative input).

---

### `permutations` <a id="permutations"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn permutations(n: int, k: int): int
```

Computes the number of k-permutations of n items: P(n, k) = n! / (n - k)!.

#### Preconditions (Contracts)

- `requires n >= 0 and k >= 0 and k <= n`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `n` | Total items. |
| `k` | Items chosen. |

#### Returns

Permutation count.

---

### `combinations` <a id="combinations"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn combinations(n: int, k: int): int
```

Computes the number of k-combinations of n items: C(n, k) = n! / (k! * (n - k)!).

#### Preconditions (Contracts)

- `requires n >= 0 and k >= 0 and k <= n`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `n` | Total items. |
| `k` | Items chosen. |

#### Returns

Combination count.

---

### `min` <a id="min"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn min(a: float, b: float): float
```

Returns the minimum of two floating-point numbers.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `a` | First operand. |
| `b` | Second operand. |

#### Returns

Lesser of a and b.

---

### `max` <a id="max"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn max(a: float, b: float): float
```

Returns the maximum of two floating-point numbers.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `a` | First operand. |
| `b` | Second operand. |

#### Returns

Greater of a and b.

---

### `clamp` <a id="clamp"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn clamp(value: float, low: float, high: float): float
```

Clamps a value within an inclusive [low, high] interval.

#### Preconditions (Contracts)

- `requires low <= high`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Candidate value. |
| `low` | Lower bound. |
| `high` | Upper bound. |

#### Returns

Clamped value.

---

### `sign` <a id="sign"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sign(x: float): float
```

Returns the sign of a floating-point number (-1.0, 0.0, or 1.0).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Input float. |

#### Returns

1.0 if positive, -1.0 if negative, 0.0 if zero.

---

### `lerp` <a id="lerp"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lerp(a: float, b: float, t: float): float
```

Performs linear interpolation between two endpoints.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `a` | Start value (t = 0.0). |
| `b` | End value (t = 1.0). |
| `t` | Interpolation parameter. |

#### Returns

Interpolated float `a + (b - a) * t`.

---

### `floor` <a id="floor"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn floor(x: float): int
```

Rounds a float down to the nearest integer.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Input float. |

#### Returns

Floor integer.

---

### `ceil` <a id="ceil"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ceil(x: float): int
```

Rounds a float up to the nearest integer.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Input float. |

#### Returns

Ceil integer.

---

### `round` <a id="round"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn round(x: float): int
```

Rounds a float to the nearest integer, half away from zero.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Input float. |

#### Returns

Rounded integer.

---

### `trunc` <a id="trunc"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn trunc(x: float): int
```

Truncates a float towards zero.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Input float. |

#### Returns

Truncated integer.

---

### `fract` <a id="fract"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fract(x: float): float
```

Returns the fractional part of a float.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Input float. |

#### Returns

Fractional component.

---

### `pow` <a id="pow"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pow(base: float, exponent: float): float
```

Computes base raised to the power of exponent (base^exponent).

#### Preconditions (Contracts)

- `requires base >= 0.0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `base` | Base number. |
| `exponent` | Exponent. |

#### Returns

Resulting power.

---

### `sqrt` <a id="sqrt"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sqrt(x: float): float
```

Computes the square root of a non-negative floating-point number.

#### Preconditions (Contracts)

- `requires x >= 0.0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Non-negative float. |

#### Returns

Square root.

---

### `cbrt` <a id="cbrt"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cbrt(x: float): float
```

Computes the cube root of a floating-point number.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Input float. |

#### Returns

Cube root.

---

### `hypot` <a id="hypot"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hypot(x: float, y: float): float
```

Computes the hypotenuse length sqrt(x^2 + y^2).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Leg length x. |
| `y` | Leg length y. |

#### Returns

Hypotenuse length.

---

### `log` <a id="log"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn log(x: float): float
```

Computes the natural logarithm (base e) of a positive number.

#### Preconditions (Contracts)

- `requires x > 0.0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Strictly positive float. |

#### Returns

Natural logarithm.

---

### `log2` <a id="log2"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn log2(x: float): float
```

Computes the binary logarithm (base 2) of a positive number.

#### Preconditions (Contracts)

- `requires x > 0.0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Strictly positive float. |

#### Returns

Base-2 logarithm.

---

### `log10` <a id="log10"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn log10(x: float): float
```

Computes the common logarithm (base 10) of a positive number.

#### Preconditions (Contracts)

- `requires x > 0.0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Strictly positive float. |

#### Returns

Base-10 logarithm.

---

### `exp` <a id="exp"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn exp(x: float): float
```

Computes the exponential function e^x.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Exponent. |

#### Returns

e raised to x.

---

### `exp2` <a id="exp2"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn exp2(x: float): float
```

Computes 2^x.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Exponent. |

#### Returns

2 raised to x.

---


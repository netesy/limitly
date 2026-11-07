# API Documentation: `index.lm`

## Overview

std/math/index.lm
Public entrypoint and facade for std.math. Mathematical constants, arithmetic functions, trigonometry, and statistics.

## Symbols

- **Function**: [`is_nan`](#is_nan)
- **Function**: [`is_inf`](#is_inf)
- **Function**: [`is_finite`](#is_finite)
- **Function**: [`nearly_equal`](#nearly_equal)
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
- **Function**: [`sin`](#sin)
- **Function**: [`cos`](#cos)
- **Function**: [`tan`](#tan)
- **Function**: [`asin`](#asin)
- **Function**: [`acos`](#acos)
- **Function**: [`atan`](#atan)
- **Function**: [`atan2`](#atan2)
- **Function**: [`sinh`](#sinh)
- **Function**: [`cosh`](#cosh)
- **Function**: [`tanh`](#tanh)
- **Function**: [`sum`](#sum)
- **Function**: [`mean`](#mean)
- **Function**: [`median`](#median)
- **Function**: [`variance`](#variance)
- **Function**: [`stddev`](#stddev)
- **Function**: [`random_int`](#random_int)
- **Function**: [`random_float`](#random_float)
- **Function**: [`random_bool`](#random_bool)
- **Function**: [`random_bytes`](#random_bytes)
- **Function**: [`random_string`](#random_string)

---

### `is_nan` <a id="is_nan"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_nan(x: float): bool
```

Checks whether a floating-point value is Not-a-Number (NaN).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Candidate float. |

#### Returns

True if value is NaN.

---

### `is_inf` <a id="is_inf"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_inf(x: float): bool
```

Checks whether a floating-point value is positive or negative infinity.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Candidate float. |

#### Returns

True if value is infinite.

---

### `is_finite` <a id="is_finite"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_finite(x: float): bool
```

Checks whether a floating-point value is finite (neither NaN nor infinite).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Candidate float. |

#### Returns

True if value is finite.

---

### `nearly_equal` <a id="nearly_equal"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn nearly_equal(a: float, b: float, epsilon: float = ...): bool
```

Checks whether two floating-point values are approximately equal within an epsilon tolerance.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `a` | First operand. |
| `b` | Second operand. |
| `epsilon` | Maximum allowable difference tolerance. |

#### Returns

True if |a - b| <= epsilon.

---

### `abs` <a id="abs"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn abs(x: float): float
```

Returns the absolute value of a 64-bit float.

---

### `abs_int` <a id="abs_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn abs_int(x: int): int
```

Returns the absolute value of a 64-bit integer.

---

### `gcd` <a id="gcd"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn gcd(a: int, b: int): int
```

Computes the Greatest Common Divisor (GCD) of two integers.

---

### `lcm` <a id="lcm"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lcm(a: int, b: int): int
```

Computes the Least Common Multiple (LCM) of two integers.

---

### `factorial` <a id="factorial"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn factorial(n: int): int
```

Computes the factorial of a non-negative integer (n!).

---

### `permutations` <a id="permutations"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn permutations(n: int, k: int): int
```

Computes the number of k-permutations of n items: P(n, k).

---

### `combinations` <a id="combinations"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn combinations(n: int, k: int): int
```

Computes the number of k-combinations of n items: C(n, k).

---

### `min` <a id="min"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn min(a: float, b: float): float
```

Returns the minimum of two floating-point numbers.

---

### `max` <a id="max"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn max(a: float, b: float): float
```

Returns the maximum of two floating-point numbers.

---

### `clamp` <a id="clamp"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn clamp(value: float, low: float, high: float): float
```

Clamps a value within an inclusive [low, high] interval.

---

### `sign` <a id="sign"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sign(x: float): float
```

Returns the sign of a floating-point number (-1.0, 0.0, or 1.0).

---

### `lerp` <a id="lerp"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lerp(a: float, b: float, t: float): float
```

Performs linear interpolation between two endpoints: `a + (b - a) * t`.

---

### `floor` <a id="floor"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn floor(x: float): int
```

Rounds a float down to the nearest integer.

---

### `ceil` <a id="ceil"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ceil(x: float): int
```

Rounds a float up to the nearest integer.

---

### `round` <a id="round"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn round(x: float): int
```

Rounds a float to the nearest integer, half away from zero.

---

### `trunc` <a id="trunc"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn trunc(x: float): int
```

Truncates a float towards zero.

---

### `fract` <a id="fract"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn fract(x: float): float
```

Returns the fractional component of a float.

---

### `pow` <a id="pow"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pow(base: float, exponent: float): float
```

Computes base raised to the power of exponent (`base^exponent`).

---

### `sqrt` <a id="sqrt"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sqrt(x: float): float
```

Computes the square root of a non-negative float.

---

### `cbrt` <a id="cbrt"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cbrt(x: float): float
```

Computes the cube root of a float.

---

### `hypot` <a id="hypot"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hypot(x: float, y: float): float
```

Computes the hypotenuse length sqrt(x^2 + y^2).

---

### `log` <a id="log"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn log(x: float): float
```

Computes the natural logarithm (base e) of a positive float.

---

### `log2` <a id="log2"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn log2(x: float): float
```

Computes the binary logarithm (base 2) of a positive float.

---

### `log10` <a id="log10"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn log10(x: float): float
```

Computes the common logarithm (base 10) of a positive float.

---

### `exp` <a id="exp"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn exp(x: float): float
```

Computes the exponential function e^x.

---

### `exp2` <a id="exp2"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn exp2(x: float): float
```

Computes 2^x.

---

### `sin` <a id="sin"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sin(x: float): float
```

Computes the sine of an angle in radians.

---

### `cos` <a id="cos"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cos(x: float): float
```

Computes the cosine of an angle in radians.

---

### `tan` <a id="tan"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tan(x: float): float
```

Computes the tangent of an angle in radians.

---

### `asin` <a id="asin"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn asin(x: float): float
```

Computes the arcsine in radians.

---

### `acos` <a id="acos"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn acos(x: float): float
```

Computes the arccosine in radians.

---

### `atan` <a id="atan"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn atan(x: float): float
```

Computes the arctangent in radians.

---

### `atan2` <a id="atan2"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn atan2(y: float, x: float): float
```

Computes the four-quadrant angle atan2(y, x).

---

### `sinh` <a id="sinh"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sinh(x: float): float
```

Computes the hyperbolic sine.

---

### `cosh` <a id="cosh"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cosh(x: float): float
```

Computes the hyperbolic cosine.

---

### `tanh` <a id="tanh"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tanh(x: float): float
```

Computes the hyperbolic tangent.

---

### `sum` <a id="sum"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sum(items: list): float
```

Computes the sum of all numerical values in a collection.

---

### `mean` <a id="mean"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mean(items: list): float
```

Computes the arithmetic mean of a collection.

---

### `median` <a id="median"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn median(items: list): float
```

Computes the statistical median of a collection.

---

### `variance` <a id="variance"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn variance(items: list): float
```

Computes the population variance of a collection.

---

### `stddev` <a id="stddev"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stddev(items: list): float
```

Computes the population standard deviation of a collection.

---

### `random_int` <a id="random_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_int(min: int, max: int): int
```

Generates a random integer in range [min, max) using the default PRNG.

---

### `random_float` <a id="random_float"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_float(min: float, max: float): float
```

Generates a random float in range [min, max] using the default PRNG.

---

### `random_bool` <a id="random_bool"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_bool(): bool
```

Generates a random boolean flag using the default PRNG.

---

### `random_bytes` <a id="random_bytes"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_bytes(count: int): list
```

Generates a list of random byte integers using the default PRNG.

---

### `random_string` <a id="random_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn random_string(len_val: int): str
```

Generates a random alphanumeric string of length `len_val` using the default PRNG.

---


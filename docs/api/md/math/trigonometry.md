# API Documentation: `trigonometry.lm`

## Overview

std/math/trigonometry.lm
Trigonometric and hyperbolic functions with angle reduction and Taylor series expansion.

## Symbols

- **Frame**: [`TrigFloat`](#TrigFloat)
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

---

### `TrigFloat` <a id="TrigFloat"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TrigFloat
```

Wrapper providing trigonometric and hyperbolic evaluations for angles in radians.
Implements argument reduction modulo 2π and rapid Taylor/Maclaurin series convergence.

#### Example: Idiomatic Usage

```lymar
import std.math.trigonometry as trig;
var tf = trig.TrigFloat(3.14159265 / 2.0);
print(tf.sin()); // ~1.0
```

#### Members

- `var pub value: float` *(field)*
- `pub init(value: float)` *(constructor)*
- `pub fn sin(): float` *(method)*
- `pub fn cos(): float` *(method)*
- `pub fn tan(): float` *(method)*
- `pub fn asin(): float` *(method)*
- `pub fn acos(): float` *(method)*
- `pub fn atan(): float` *(method)*
- `pub fn atan2(x: float): float` *(method)*
- `pub fn sinh(): float` *(method)*
- `pub fn cosh(): float` *(method)*
- `pub fn tanh(): float` *(method)*
- `fn normalize_angle(): float` *(method)*

---

### `sin` <a id="sin"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sin(x: float): float
```

Computes the sine of an angle in radians.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Angle in radians. |

#### Returns

Sine value.

---

### `cos` <a id="cos"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cos(x: float): float
```

Computes the cosine of an angle in radians.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Angle in radians. |

#### Returns

Cosine value.

---

### `tan` <a id="tan"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tan(x: float): float
```

Computes the tangent of an angle in radians.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Angle in radians. |

#### Returns

Tangent value.

---

### `asin` <a id="asin"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn asin(x: float): float
```

Computes the arcsine in radians.

#### Preconditions (Contracts)

- `requires x >= -1.0 and x <= 1.0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Value in domain [-1.0, 1.0]. |

#### Returns

Angle in radians.

---

### `acos` <a id="acos"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn acos(x: float): float
```

Computes the arccosine in radians.

#### Preconditions (Contracts)

- `requires x >= -1.0 and x <= 1.0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Value in domain [-1.0, 1.0]. |

#### Returns

Angle in radians.

---

### `atan` <a id="atan"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn atan(x: float): float
```

Computes the arctangent in radians.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Input float. |

#### Returns

Angle in radians.

---

### `atan2` <a id="atan2"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn atan2(y: float, x: float): float
```

Computes the four-quadrant angle between positive x-axis and point (x, y).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `y` | Vertical coordinate. |
| `x` | Horizontal coordinate. |

#### Returns

Angle in radians in range (-π, π].

---

### `sinh` <a id="sinh"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sinh(x: float): float
```

Computes the hyperbolic sine.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Input float. |

#### Returns

Hyperbolic sine.

---

### `cosh` <a id="cosh"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn cosh(x: float): float
```

Computes the hyperbolic cosine.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Input float. |

#### Returns

Hyperbolic cosine.

---

### `tanh` <a id="tanh"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn tanh(x: float): float
```

Computes the hyperbolic tangent.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `x` | Input float. |

#### Returns

Hyperbolic tangent.

---


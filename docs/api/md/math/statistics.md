# API Documentation: `statistics.lm`

## Overview

std/math/statistics.lm
Descriptive statistics including sum, arithmetic mean, median, variance, and standard deviation.

## Symbols

- **Function**: [`sum`](#sum)
- **Function**: [`mean`](#mean)
- **Function**: [`median`](#median)
- **Function**: [`variance`](#variance)
- **Function**: [`stddev`](#stddev)

---

### `sum` <a id="sum"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sum(items: list): float
```

Computes the sum of all numerical values in a collection.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | List of numerical values. |

#### Returns

Total sum as a 64-bit float.

---

### `mean` <a id="mean"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn mean(items: list): float
```

Computes the arithmetic mean (average) of a collection of numbers.

#### Preconditions (Contracts)

- `requires len(items) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | List of numerical values. |

#### Returns

Mean value, or 0.0 if collection is empty.

---

### `median` <a id="median"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn median(items: list): float
```

Computes the statistical median (middle value) of a collection.
Automatically creates an internal copy to perform sorting, leaving the input collection unmodified.

#### Preconditions (Contracts)

- `requires len(items) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | List of numerical values. |

#### Returns

Median value.

---

### `variance` <a id="variance"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn variance(items: list): float
```

Computes the population variance (σ²) of a collection of values.

#### Preconditions (Contracts)

- `requires len(items) >= 2`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | List of numerical values. |

#### Returns

Population variance.

---

### `stddev` <a id="stddev"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn stddev(items: list): float
```

Computes the population standard deviation (σ = √variance) of a collection.

#### Preconditions (Contracts)

- `requires len(items) >= 2`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `items` | List of numerical values. |

#### Returns

Population standard deviation.

---


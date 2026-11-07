# API Documentation: `index.lm`

## Overview

std/time/index.lm
Public entrypoint and facade for std.time. Date, time, timestamps, durations, and timezone computations.

## Symbols

- **Function**: [`sleep_ms`](#sleep_ms)
- **Function**: [`sleep_seconds`](#sleep_seconds)
- **Function**: [`sleep_duration`](#sleep_duration)
- **Function**: [`is_leap_year`](#is_leap_year)
- **Function**: [`get_days_in_month`](#get_days_in_month)
- **Function**: [`get_days_in_year`](#get_days_in_year)
- **Function**: [`datetime_to_timestamp`](#datetime_to_timestamp)
- **Function**: [`timestamp_to_year`](#timestamp_to_year)
- **Function**: [`timestamp_to_month`](#timestamp_to_month)
- **Function**: [`timestamp_to_day`](#timestamp_to_day)

---

### `sleep_ms` <a id="sleep_ms"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sleep_ms(ms: int): nil
```

Suspends execution of the current thread for the specified number of milliseconds.

#### Preconditions (Contracts)

- `requires ms >= 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `ms` | Milliseconds to sleep. |

---

### `sleep_seconds` <a id="sleep_seconds"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sleep_seconds(seconds: float): nil
```

Suspends execution of the current thread for the specified fractional seconds.

#### Preconditions (Contracts)

- `requires seconds >= 0.0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `seconds` | Seconds to sleep. |

---

### `sleep_duration` <a id="sleep_duration"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sleep_duration(dur: duration.Duration): nil
```

Suspends execution for the duration represented by a Duration instance.

#### Preconditions (Contracts)

- `requires dur != nil`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `dur` | Duration instance. |

---

### `is_leap_year` <a id="is_leap_year"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_leap_year(year: int): bool
```

Determines whether the specified Gregorian calendar year is a leap year.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Years divisible by 4 are leap years, except centenary years not divisible by 400.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `year` | Gregorian year (e.g. 2024, 2028). |

#### Returns

True if leap year, false otherwise.

---

### `get_days_in_month` <a id="get_days_in_month"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_days_in_month(year: int, month: int): int
```

Returns the number of days in the specified month of a given year (taking leap years into account).

#### Preconditions (Contracts)

- `requires month >= 1 and month <= 12`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `year` | Gregorian year. |
| `month` | Month number (1 for January, 12 for December). |

#### Returns

Number of days in the month (28, 29, 30, or 31).

---

### `get_days_in_year` <a id="get_days_in_year"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_days_in_year(year: int): int
```

Returns the total number of days in the specified year (366 for leap years, 365 otherwise).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `year` | Gregorian year. |

#### Returns

366 for leap years, 365 for common years.

---

### `datetime_to_timestamp` <a id="datetime_to_timestamp"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn datetime_to_timestamp(year: int, month: int, day: int, hour: int, minute: int, second: int): int
```

Converts Gregorian date and time components into a Unix epoch timestamp (seconds since Jan 1, 1970 UTC).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `year` | Full year. |
| `month` | Month (1-12). |
| `day` | Day of month (1-31). |
| `hour` | Hour (0-23). |
| `minute` | Minute (0-59). |
| `second` | Second (0-59). |

#### Returns

Integer Unix timestamp in seconds.

---

### `timestamp_to_year` <a id="timestamp_to_year"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn timestamp_to_year(timestamp: int): int
```

Extracts the Gregorian year from a Unix epoch timestamp.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `timestamp` | Seconds since Unix epoch. |

#### Returns

Year integer.

---

### `timestamp_to_month` <a id="timestamp_to_month"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn timestamp_to_month(timestamp: int): int
```

Extracts the month (1-12) from a Unix epoch timestamp.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `timestamp` | Seconds since Unix epoch. |

#### Returns

Month integer (1-12).

---

### `timestamp_to_day` <a id="timestamp_to_day"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn timestamp_to_day(timestamp: int): int
```

Extracts the day of month (1-31) from a Unix epoch timestamp.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `timestamp` | Seconds since Unix epoch. |

#### Returns

Day of month integer (1-31).

---


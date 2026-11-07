# API Documentation: `datetime.lm`

## Overview

Standard Library Time DateTime Submodule

## Symbols

- **Function**: [`to_i`](#to_i)
- **Function**: [`is_leap_year`](#is_leap_year)
- **Function**: [`get_days_in_month`](#get_days_in_month)
- **Function**: [`get_days_in_year`](#get_days_in_year)
- **Function**: [`datetime_to_timestamp`](#datetime_to_timestamp)
- **Function**: [`timestamp_to_year`](#timestamp_to_year)
- **Function**: [`timestamp_to_month`](#timestamp_to_month)
- **Function**: [`timestamp_to_day`](#timestamp_to_day)
- **Frame**: [`DateTime`](#DateTime)
- **Function**: [`sleep_ms`](#sleep_ms)
- **Function**: [`sleep_seconds`](#sleep_seconds)
- **Function**: [`sleep_duration`](#sleep_duration)
- **Function**: [`parse_datetime`](#parse_datetime)

---

### `to_i` <a id="to_i"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn to_i(s: str): int
```

---

### `is_leap_year` <a id="is_leap_year"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_leap_year(year: int): bool
```

Calendar calculation functions

---

### `get_days_in_month` <a id="get_days_in_month"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_days_in_month(year: int, month: int): int
```

---

### `get_days_in_year` <a id="get_days_in_year"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_days_in_year(year: int): int
```

---

### `datetime_to_timestamp` <a id="datetime_to_timestamp"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn datetime_to_timestamp(year: int, month: int, day: int, hour: int, minute: int, second: int): int
```

---

### `timestamp_to_year` <a id="timestamp_to_year"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn timestamp_to_year(timestamp: int): int
```

---

### `timestamp_to_month` <a id="timestamp_to_month"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn timestamp_to_month(timestamp: int): int
```

---

### `timestamp_to_day` <a id="timestamp_to_day"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn timestamp_to_day(timestamp: int): int
```

---

### `DateTime` <a id="DateTime"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame DateTime
```

#### Members

- `var pub timestamp: int` *(field)*
- `var pub microseconds: int` *(field)*
- `var pub timezone: tz.TimeZone` *(field)*
- `pub init(timestamp: int, microseconds: int, timezone: tz.TimeZone)` *(constructor)*
- `pub fn now(): DateTime` *(method)*
- `pub fn from_timestamp(timestamp: int): DateTime` *(method)*
- `pub fn from_string(datetime: str): DateTime?` *(method)*
- `pub fn from_components(year: int, month: int, day: int, hour: int, minute: int, second: int): DateTime` *(method)*
- `pub fn add(duration: dur.Duration): DateTime` *(method)*
- `pub fn subtract(duration: dur.Duration): DateTime` *(method)*
- `pub fn difference(other: DateTime): dur.Duration` *(method)*
- `pub fn year(): int` *(method)*
- `pub fn month(): int` *(method)*
- `pub fn day(): int` *(method)*
- `pub fn hour(): int` *(method)*
- `pub fn minute(): int` *(method)*
- `pub fn second(): int` *(method)*
- `pub fn day_of_week(): int` *(method)*
- `pub fn day_of_year(): int` *(method)*
- `pub fn week_of_year(): int` *(method)*
- `pub fn is_leap_year(): bool` *(method)*
- `pub fn days_in_month(): int` *(method)*
- `pub fn quarter(): int` *(method)*
- `pub fn with_year(year: int): DateTime` *(method)*
- `pub fn with_month(month: int): DateTime` *(method)*
- `pub fn with_day(day: int): DateTime` *(method)*
- `pub fn with_hour(hour: int): DateTime` *(method)*
- `pub fn with_minute(minute: int): DateTime` *(method)*
- `pub fn with_second(second: int): DateTime` *(method)*
- `pub fn with_timezone(tz_val: tz.TimeZone): DateTime` *(method)*
- `pub fn to_timezone(tz_val: tz.TimeZone): DateTime` *(method)*
- `pub fn equals(other: DateTime): bool` *(method)*
- `pub fn greater_than(other: DateTime): bool` *(method)*
- `pub fn less_than(other: DateTime): bool` *(method)*
- `pub fn is_between(start: DateTime, end: DateTime): bool` *(method)*
- `pub fn format(fmt: str): str` *(method)*
- `pub fn to_iso_string(): str` *(method)*
- `pub fn to_iso8601(): str` *(method)*
- `pub fn to_date_string(): str` *(method)*
- `pub fn to_time_string(): str` *(method)*
- `pub fn to_rfc2822(): str` *(method)*
- `pub fn to_string(): str` *(method)*
- `pub fn is_weekend(): bool` *(method)*
- `pub fn is_weekday(): bool` *(method)*
- `pub fn start_of_day(): DateTime` *(method)*
- `pub fn end_of_day(): DateTime` *(method)*
- `pub fn start_of_week(): DateTime` *(method)*
- `pub fn start_of_month(): DateTime` *(method)*
- `pub fn end_of_month(): DateTime` *(method)*
- `pub fn start_of_year(): DateTime` *(method)*
- `pub fn end_of_year(): DateTime` *(method)*
- `pub fn start_of_quarter(): DateTime` *(method)*
- `pub fn age(birthdate: DateTime): dur.Duration` *(method)*

---

### `sleep_ms` <a id="sleep_ms"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sleep_ms(ms: int): nil
```

---

### `sleep_seconds` <a id="sleep_seconds"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sleep_seconds(seconds: float): nil
```

---

### `sleep_duration` <a id="sleep_duration"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn sleep_duration(duration: dur.Duration): nil
```

---

### `parse_datetime` <a id="parse_datetime"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_datetime(value: str): DateTime?
```

---


# API Documentation: `duration.lm`

## Overview

std/time/duration.lm
High-resolution time span representation (seconds and microsecond precision).

## Symbols

- **Function**: [`pad_int`](#pad_int)
- **Frame**: [`Duration`](#Duration)

---

### `pad_int` <a id="pad_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pad_int(n: int, width: int): str
```

Formats an integer with leading zero padding up to `width`.

---

### `Duration` <a id="Duration"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Duration
```

Represents an elapsed duration of time with microsecond resolution.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Construct durations via fluent factory methods like `Duration.from_seconds(10)` or `Duration.from_milliseconds(250)`.

> [!NOTE]
> **Note**: Durations can represent both positive time advances and negative offsets.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `seconds` | Whole seconds component. |
| `microseconds` | Sub-second fractional microseconds component (0-999999). |

#### Example: Idiomatic Usage

```lymar
import std.time as time;
var d = time.Duration.from_seconds(90);
print("Duration: {d.human_readable()}"); // "1m 30s"
```

#### Members

- `var pub microseconds: int` *(field)*
- `var pub seconds: int` *(field)*
- `pub init(seconds: int, microseconds: int)` *(constructor)*
- `pub fn from_days(days: int): Duration` *(method)*
- `pub fn from_hours(hours: int): Duration` *(method)*
- `pub fn from_minutes(minutes: int): Duration` *(method)*
- `pub fn from_seconds(seconds: int): Duration` *(method)*
- `pub fn from_milliseconds(ms: int): Duration` *(method)*
- `pub fn from_microseconds(us: int): Duration` *(method)*
- `pub fn add(other: Duration): Duration` *(method)*
- `pub fn subtract(other: Duration): Duration` *(method)*
- `pub fn multiply(factor: int): Duration` *(method)*
- `pub fn equals(other: Duration): bool` *(method)*
- `pub fn greater_than(other: Duration): bool` *(method)*
- `pub fn less_than(other: Duration): bool` *(method)*
- `pub fn to_seconds(): float` *(method)*
- `pub fn to_milliseconds(): int` *(method)*
- `pub fn to_microseconds(): int` *(method)*
- `pub fn total_seconds(): int` *(method)*
- `pub fn to_string(): str` *(method)*
- `pub fn human_readable(): str` *(method)*

---


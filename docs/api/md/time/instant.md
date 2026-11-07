# API Documentation: `instant.lm`

## Overview

std/time/instant.lm
Monotonic time measurement and elapsed interval calculation.

## Symbols

- **Frame**: [`Instant`](#Instant)

---

### `Instant` <a id="Instant"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Instant
```

Represents a point-in-time timestamp used for high-precision latency and interval measurements.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Call `Instant.now()` before a task and `instant.elapsed()` after to measure duration.

> [!NOTE]
> **Note**: Operates on system monotonic time in milliseconds.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `timestamp_ms` | Milliseconds timestamp value as a float. |

#### Example: Idiomatic Usage

```lymar
import std.time as time;
var start = time.Instant.now();
// ... perform workload ...
var took = start.elapsed();
print("Completed in: {took.human_readable()}");
```

#### Members

- `var pub timestamp_ms: float` *(field)*
- `pub init(timestamp_ms: float)` *(constructor)*
- `pub fn now(): Instant` *(method)*
- `pub fn elapsed(): dur.Duration` *(method)*

---


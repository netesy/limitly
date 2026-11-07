# API Documentation: `timezone.lm`

## Overview

Standard Library Time TimeZone Submodule

## Symbols

- **Frame**: [`TimeZone`](#TimeZone)

---

### `TimeZone` <a id="TimeZone"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TimeZone
```

#### Members

- `var pub name: str` *(field)*
- `var pub offset_hours: int` *(field)*
- `var pub offset_minutes: int` *(field)*
- `pub init(name: str, offset_hours: int, offset_minutes: int)` *(constructor)*
- `pub fn utc(): TimeZone` *(method)*
- `pub fn from_offset(offset_hours: int): TimeZone` *(method)*
- `pub fn to_seconds_offset(): int` *(method)*
- `pub fn offset_string(): str` *(method)*

---


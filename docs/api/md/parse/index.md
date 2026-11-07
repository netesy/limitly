# API Documentation: `index.lm`

## Overview

Standard Library Parsing Module

String to primitive numbers, booleans, and date-time converters.

## Symbols

- **Frame**: [`Parse`](#Parse)
- **Function**: [`parse_bool`](#parse_bool)
- **Function**: [`parse_int`](#parse_int)
- **Function**: [`parse_float`](#parse_float)
- **Function**: [`parse_datetime`](#parse_datetime)

---

### `Parse` <a id="Parse"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Parse
```

Facade frame for parsing operations.

#### Members

- `pub init()` *(constructor)*
- `pub fn parse_bool(value: str): bool` *(method)*
- `pub fn parse_int(value: str): int?` *(method)*
- `pub fn parse_float(value: str): str?` *(method)*
- `pub fn parse_datetime(value: str): datetime.DateTime?` *(method)*

---

### `parse_bool` <a id="parse_bool"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_bool(value: str): bool
```

Parses a boolean literal ("true", "false", "1", "0").

---

### `parse_int` <a id="parse_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_int(value: str): int?
```

Parses a signed integer from string.

---

### `parse_float` <a id="parse_float"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_float(value: str): str?
```

Parses a float from string.

---

### `parse_datetime` <a id="parse_datetime"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_datetime(value: str): datetime.DateTime?
```

Parses a date-time string in ISO format.

---


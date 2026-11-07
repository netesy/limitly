# API Documentation: `index.lm`

## Overview

std/log/index.lm
Public facade for std.log: Structured diagnostic logging.

## Symbols

- **Frame**: [`Logger`](#Logger)
- **Function**: [`log`](#log)
- **Function**: [`info`](#info)
- **Function**: [`warn`](#warn)
- **Function**: [`error`](#error)

---

### `Logger` <a id="Logger"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Logger
```

Logger frame providing leveled log emission methods.

#### Members

- `pub init()` *(constructor)*
- `pub fn log(msg: str): nil` *(method)*
- `pub fn info(msg: str): nil` *(method)*
- `pub fn warn(msg: str): nil` *(method)*
- `pub fn error(msg: str): nil` *(method)*

---

### `log` <a id="log"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn log(msg: str): nil
```

Emits an informational message to standard output using the default logger.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `msg` | Message text. |

---

### `info` <a id="info"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn info(msg: str): nil
```

Emits an informational message to standard output using the default logger.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `msg` | Message text. |

---

### `warn` <a id="warn"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn warn(msg: str): nil
```

Emits a warning message to standard output using the default logger.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `msg` | Message text. |

---

### `error` <a id="error"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn error(msg: str): nil
```

Emits an error message to standard output using the default logger.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `msg` | Message text. |

---


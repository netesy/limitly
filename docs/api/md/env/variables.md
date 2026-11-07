# API Documentation: `variables.lm`

## Overview

std/env/variables.lm
Process environment variables, parsing, and .env file configuration.

## Symbols

- **Function**: [`get`](#get)
- **Function**: [`get_or`](#get_or)
- **Function**: [`has`](#has)
- **Function**: [`contains`](#contains)
- **Function**: [`get_int`](#get_int)
- **Function**: [`get_bool`](#get_bool)
- **Function**: [`set`](#set)
- **Function**: [`unset`](#unset)
- **Function**: [`vars`](#vars)
- **Function**: [`to_dict`](#to_dict)
- **Function**: [`keys`](#keys)
- **Function**: [`values`](#values)
- **Function**: [`parse_env`](#parse_env)
- **Function**: [`load_dotenv`](#load_dotenv)
- **Function**: [`load_file`](#load_file)
- **Function**: [`find_char`](#find_char)
- **Frame**: [`Env`](#Env)

---

### `get` <a id="get"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get(key: str): str?
```

Retrieves the string value of an environment variable, returning nil if unset.

#### Preconditions (Contracts)

- `requires len(key) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Environment variable name. |

#### Returns

Fallible string value or nil.

---

### `get_or` <a id="get_or"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_or(key: str, fallback: str): str
```

Retrieves an environment variable or returns a fallback string if absent.

#### Preconditions (Contracts)

- `requires len(key) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Environment variable name. |
| `fallback` | Default string value. |

#### Returns

Variable value or fallback.

---

### `has` <a id="has"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn has(key: str): bool
```

Checks whether an environment variable exists.

#### Preconditions (Contracts)

- `requires len(key) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Environment variable name. |

#### Returns

True if key is defined in the environment.

---

### `contains` <a id="contains"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn contains(key: str): bool
```

Alias for `has()`.

#### Preconditions (Contracts)

- `requires len(key) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Environment variable name. |

#### Returns

True if key is defined.

---

### `get_int` <a id="get_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_int(key: str, fallback: int = ...): int
```

Parses an environment variable as an integer, falling back to a default if absent or invalid.

#### Preconditions (Contracts)

- `requires len(key) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Environment variable name. |
| `fallback` | Default integer value. |

#### Returns

Parsed integer or fallback.

---

### `get_bool` <a id="get_bool"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get_bool(key: str, fallback: bool = ...): bool
```

Parses a boolean environment variable ("1", "true", "yes", "on" vs "0", "false", "no", "off").

#### Preconditions (Contracts)

- `requires len(key) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Environment variable name. |
| `fallback` | Default boolean value. |

#### Returns

Parsed boolean or fallback.

---

### `set` <a id="set"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn set(key: str, value: str): bool
```

Sets or updates an environment variable for the process.

#### Preconditions (Contracts)

- `requires len(key) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Environment variable name. |
| `value` | Target value string. |

#### Returns

True if successfully set.

---

### `unset` <a id="unset"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn unset(key: str): bool
```

Deletes an environment variable from the process environment.

#### Preconditions (Contracts)

- `requires len(key) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Environment variable name. |

#### Returns

True if successfully removed.

---

### `vars` <a id="vars"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn vars(): list
```

Returns all environment variables formatted as a list of "KEY=VALUE" strings.

#### Returns

List of raw environment entries.

---

### `to_dict` <a id="to_dict"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn to_dict(): dict
```

Parses all environment variables into a dictionary mapping {KEY: VALUE}.

#### Returns

Dictionary of environment variables.

---

### `keys` <a id="keys"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn keys(): list
```

Returns a list of all environment variable names.

#### Returns

List of variable key strings.

---

### `values` <a id="values"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn values(): list
```

Returns a list of all environment variable values.

#### Returns

List of variable value strings.

---

### `parse_env` <a id="parse_env"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_env(content: str): dict
```

Parses a `.env` file content string into a key-value dictionary.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `content` | Raw .env text content. |

#### Returns

Dictionary of parsed configuration variables.

---

### `load_dotenv` <a id="load_dotenv"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_dotenv(content: str): int
```

Parses `.env` content and injects variables into the current process environment.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `content` | Raw .env file content. |

#### Returns

Number of variables successfully set.

---

### `load_file` <a id="load_file"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_file(path: str): int
```

Reads a `.env` file from disk and loads its variables into the process environment.

#### Preconditions (Contracts)

- `requires len(path) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `path` | Filesystem path to the .env file. |

#### Returns

Number of variables loaded, or 0 if unreadable.

---

### `find_char` <a id="find_char"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn find_char(s: str, needle: str): int
```

---

### `Env` <a id="Env"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Env
```

Object-oriented interface to environment variable management.

#### Members

- `pub init()` *(constructor)*
- `pub fn get(key: str): str?` *(method)*
- `pub fn get_or(key: str, fallback: str): str` *(method)*
- `pub fn get_int(key: str): int` *(method)*
- `pub fn get_bool(key: str): bool` *(method)*
- `pub fn has(key: str): bool` *(method)*
- `pub fn contains(key: str): bool` *(method)*
- `pub fn set(key: str, value: str): bool` *(method)*
- `pub fn unset(key: str): bool` *(method)*
- `pub fn vars(): list` *(method)*
- `pub fn to_dict(): dict` *(method)*
- `pub fn keys(): list` *(method)*
- `pub fn values(): list` *(method)*
- `pub fn parse_env(content: str): dict` *(method)*
- `pub fn load_dotenv(content: str): int` *(method)*
- `pub fn load_file(path: str): int` *(method)*
- `pub fn path(fallback: str): str` *(method)*

---


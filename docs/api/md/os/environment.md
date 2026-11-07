# API Documentation: `environment.lm`

## Overview

std/os/environment.lm
Process environment variables, backed by the RT_OS resource.

## Symbols

- **Function**: [`getenv`](#getenv)
- **Function**: [`getenv_or`](#getenv_or)
- **Function**: [`setenv`](#setenv)
- **Function**: [`unsetenv`](#unsetenv)
- **Function**: [`env_vars`](#env_vars)

---

### `getenv` <a id="getenv"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn getenv(key: str): str?
```

Looks up an environment variable by name.

#### Preconditions (Contracts)

- `requires len(key) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Variable name. |

#### Returns

Fallible string value, or nil/error when absent.

---

### `getenv_or` <a id="getenv_or"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn getenv_or(key: str, fallback: str): str
```

Looks up an environment variable with a fallback default value.

#### Preconditions (Contracts)

- `requires len(key) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Variable name. |
| `fallback` | Default string value if absent. |

#### Returns

Variable value or fallback string.

---

### `setenv` <a id="setenv"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn setenv(key: str, value: str): bool
```

Sets or updates an environment variable for the current process.

#### Preconditions (Contracts)

- `requires len(key) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Variable name. |
| `value` | Target string value. |

#### Returns

True if operation succeeded, false otherwise.

---

### `unsetenv` <a id="unsetenv"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn unsetenv(key: str): bool
```

Removes an environment variable from the current process.

#### Preconditions (Contracts)

- `requires len(key) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `key` | Variable name to delete. |

#### Returns

True if operation succeeded, false otherwise.

---

### `env_vars` <a id="env_vars"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn env_vars(): list
```

Retrieves all current environment variables as a list of "NAME=VALUE" pairs.

#### Returns

List of formatted environment key-value pairs.

---


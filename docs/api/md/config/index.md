# API Documentation: `index.lm`

## Overview

std/config/index.lm
Public entrypoint and facade for std.config. Configuration parsing, environment settings, and configuration loaders.

## Symbols

- **Frame**: [`Config`](#Config)
- **Function**: [`new_config`](#new_config)
- **Function**: [`load_json`](#load_json)
- **Function**: [`load_from_env`](#load_from_env)

---

### `Config` <a id="Config"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Config
```

In-memory configuration store supporting type-coerced lookups.

#### Members

- `var pub keys: list` *(field)*
- `var pub vals: list` *(field)*
- `pub fn get(key: str, default_val: any): any` *(method)*
- `pub fn set(key: str, val_any: any)` *(method)*
- `pub fn has(key: str): bool` *(method)*

---

### `new_config` <a id="new_config"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn new_config(): Config
```

Creates a new empty configuration instance.

#### Returns

Initialized `Config` instance.

---

### `load_json` <a id="load_json"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_json(json_str: str): Config
```

Parses a simple JSON string representation into a `Config` object.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `json_str` | JSON formatted text. |

#### Returns

Populated `Config` instance.

---

### `load_from_env` <a id="load_from_env"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_from_env(keys: list): Config
```

Loads specific environment variables into a `Config` instance.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `keys` | List of environment variable names to import. |

#### Returns

`Config` containing resolved environment variables.

---


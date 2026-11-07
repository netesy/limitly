# API Documentation: `environment.lm`

## Overview

std/config/environment.lm
Configuration Environment Module

## Symbols

- **Function**: [`load_from_env`](#load_from_env)

---

### `load_from_env` <a id="load_from_env"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_from_env(keys: list): dict
```

Loads configuration key-value mappings from environment variables.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `keys` | List of environment variable names to query. |

#### Returns

Dictionary mapping found environment variables to their string values.

#### Example: Idiomatic Usage

```lymar
var env_cfg = environment.load_from_env(["PORT", "HOST"]);
```

---


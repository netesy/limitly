# API Documentation: `loader.lm`

## Overview

std/config/loader.lm
Configuration Loader Module

## Symbols

- **Function**: [`load_json`](#load_json)

---

### `load_json` <a id="load_json"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn load_json(json_str: str): dict
```

Parses a simple JSON string representation into a key-value dictionary.
Supports string, boolean, integer, and float values.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `json_str` | JSON formatted configuration text. |

#### Returns

Dictionary mapping string keys to parsed values.

#### Example: Idiomatic Usage

```lymar
var map = loader.load_json("{\"port\": 8080, \"debug\": true}");
```

---


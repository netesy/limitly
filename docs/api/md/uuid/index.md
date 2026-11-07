# API Documentation: `index.lm`

## Overview

std/uuid/index.lm
Public entrypoint and facade for std.uuid. Universally Unique Identifier (UUID) generation and parsing.

## Symbols

- **Function**: [`parse`](#parse)
- **Function**: [`generate_v4`](#generate_v4)

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(uuid_str: str): uuid.UUID
```

Parses a string representation of a UUID into a UUID instance.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `uuid_str` | Hyphenated or braced UUID string. |

#### Returns

Parsed UUID; check `is_valid` for success.

---

### `generate_v4` <a id="generate_v4"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn generate_v4(): uuid.UUID
```

Generates a fresh RFC 4122 Version 4 random UUID.

#### Returns

Random UUID instance.

---


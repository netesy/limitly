# API Documentation: `uuid.lm`

## Overview

std/uuid/uuid.lm
RFC 4122 Universally Unique Identifier (UUID) representation and parsing.

## Symbols

- **Frame**: [`UUID`](#UUID)
- **Function**: [`parse`](#parse)
- **Function**: [`byte_to_hex`](#byte_to_hex)
- **Function**: [`trim`](#trim)
- **Function**: [`to_lower`](#to_lower)
- **Function**: [`index_of`](#index_of)

---

### `UUID` <a id="UUID"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame UUID
```

Represents a 128-bit RFC 4122 Universally Unique Identifier (UUID).

> [!TIP]
> **Idiomatic Usage & Best Practice**: Use `uuid.generate_v4()` to create random UUIDs or `uuid.parse(str)` to parse from strings.

> [!NOTE]
> **Note**: Instances represent 16 raw bytes along with a validation status flag.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `bytes` | 16-element byte array or empty if invalid. |
| `is_valid` | Boolean indicating whether the UUID represents a parsed/valid identifier. |

#### Example: Idiomatic Usage

```lymar
import std.uuid as uuid;
var id = uuid.generate_v4();
print("Generated: {id.to_string()} (v{id.version()})");
```

#### Members

- `var pub bytes: list` *(field)*
- `var pub is_valid: bool` *(field)*
- `pub init(bytes: list, is_valid: bool)` *(constructor)*
- `pub fn to_string(): str` *(method)*
- `pub fn version(): int` *(method)*
- `pub fn variant(): int` *(method)*
- `pub fn equals(other: UUID): bool` *(method)*

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(uuid_str: str): UUID
```

Parses a 36-character hyphenated UUID string (or 38-character braced format) into a UUID.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Tolerates uppercase and lowercase hexadecimal digits, surrounding whitespace, and `{...}` braces.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `uuid_str` | The UUID string to parse. |

#### Returns

Parsed UUID object; check `result.is_valid` for success.

#### Example: Idiomatic Usage

```lymar
var id = uuid.parse("f81d4fae-7dec-11d0-a765-00a0c91e6bf6");
if (id.is_valid) {
    print("Version: {id.version()}");
}
```

---

### `byte_to_hex` <a id="byte_to_hex"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn byte_to_hex(b: int): str
```

---

### `trim` <a id="trim"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn trim(s: str): str
```

---

### `to_lower` <a id="to_lower"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn to_lower(s: str): str
```

---

### `index_of` <a id="index_of"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn index_of(s: str, pattern: str): int
```

---


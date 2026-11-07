# API Documentation: `index.lm`

## Overview

std/semver/index.lm
Semantic Versioning (SemVer 2.0.0) standard library module.

## Symbols

- **Frame**: [`Version`](#Version)
- **Function**: [`parse`](#parse)
- **Function**: [`compare`](#compare)
- **Function**: [`is_compatible`](#is_compatible)
- **Function**: [`to_int`](#to_int)
- **Function**: [`index_of`](#index_of)
- **Function**: [`split_by_dot`](#split_by_dot)
- **Function**: [`is_numeric`](#is_numeric)
- **Function**: [`byte_ord`](#byte_ord)
- **Function**: [`is_valid_char`](#is_valid_char)
- **Function**: [`is_valid_prerelease_id`](#is_valid_prerelease_id)
- **Function**: [`is_valid_build_id`](#is_valid_build_id)
- **Function**: [`has_invalid_leading_zero`](#has_invalid_leading_zero)
- **Function**: [`compare_strings`](#compare_strings)

---

### `Version` <a id="Version"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Version
```

Represents a parsed semantic version conforming to SemVer 2.0.0.

#### Members

- `var pub major: int` *(field)*
- `var pub minor: int` *(field)*
- `var pub patch: int` *(field)*
- `var pub prerelease: str` *(field)*
- `var pub build: str` *(field)*
- `pub init(major: int, minor: int, patch: int, prerelease: str, build: str)` *(constructor)*
- `pub fn compare(other: Version): int` *(method)*
- `pub fn equals(other: Version): bool` *(method)*
- `pub fn greater_than(other: Version): bool` *(method)*
- `pub fn less_than(other: Version): bool` *(method)*
- `pub fn is_compatible(other: Version): bool` *(method)*
- `pub fn to_string(): str` *(method)*

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(s: str): Version?
```

Parses a SemVer 2.0.0 compliant string into a structured `Version` object.
Enforces numeric core segments, forbids leading zeros on numbers, and validates
identifiers for pre-release and build tags.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Candidate semantic version string. |

#### Returns

Fallible Version object or err() if invalid.

---

### `compare` <a id="compare"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compare(v1: Version, v2: Version): int
```

Compares two Version instances.

#### Preconditions (Contracts)

- `requires v1 != nil and v2 != nil`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v1` | First version. |
| `v2` | Second version. |

#### Returns

1 if v1 > v2, -1 if v1 < v2, 0 if equal.

---

### `is_compatible` <a id="is_compatible"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_compatible(v1: Version, v2: Version): bool
```

Evaluates whether `v2` is caret-compatible with `v1`.

#### Preconditions (Contracts)

- `requires v1 != nil and v2 != nil`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `v1` | Base version. |
| `v2` | Target version. |

#### Returns

True if compatible.

---

### `to_int` <a id="to_int"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn to_int(s: str): int
```

---

### `index_of` <a id="index_of"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn index_of(s: str, char: str): int
```

---

### `split_by_dot` <a id="split_by_dot"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn split_by_dot(s: str): list
```

---

### `is_numeric` <a id="is_numeric"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_numeric(s: str): bool
```

---

### `byte_ord` <a id="byte_ord"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn byte_ord(ch: str): int
```

---

### `is_valid_char` <a id="is_valid_char"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_valid_char(ch: str): bool
```

---

### `is_valid_prerelease_id` <a id="is_valid_prerelease_id"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_valid_prerelease_id(s: str): bool
```

---

### `is_valid_build_id` <a id="is_valid_build_id"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_valid_build_id(s: str): bool
```

---

### `has_invalid_leading_zero` <a id="has_invalid_leading_zero"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn has_invalid_leading_zero(s: str): bool
```

---

### `compare_strings` <a id="compare_strings"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn compare_strings(s1: str, s2: str): int
```

---


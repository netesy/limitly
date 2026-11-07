# API Documentation: `query.lm`

## Overview

std/url/query.lm
Query submodule for std.url. URL parsing, URL encoding, query strings, and URI resolution.

## Symbols

- **Frame**: [`QueryParams`](#QueryParams)
- **Function**: [`parse`](#parse)
- **Function**: [`build`](#build)
- **Function**: [`index_of`](#index_of)
- **Function**: [`split_str`](#split_str)

---

### `QueryParams` <a id="QueryParams"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame QueryParams
```

Manages structured URL query parameters as key-value pairs.
Supports duplicate keys, URL-encoding on serialization, and URL-decoding on parsing.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Use `add` to retain duplicate parameter keys and `set` to replace existing keys.

#### Example: Idiomatic Usage

```lymar
import std.url.query as query;
var qp = query.QueryParams();
qp.set("format", "json");
qp.add("filter", "active");
qp.add("filter", "recent");
print(qp.to_string()); // "format=json&filter=active&filter=recent"
```

#### Members

- `var pub keys: list` *(field)*
- `var pub values: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn get(key: str): str` *(method)*
- `pub fn get_all(key: str): list` *(method)*
- `pub fn set(key: str, value: str)` *(method)*
- `pub fn add(key: str, value: str)` *(method)*
- `pub fn remove(key: str)` *(method)*
- `pub fn has(key: str): bool` *(method)*
- `pub fn to_string(): str` *(method)*

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(qs: str): QueryParams
```

Parses an `application/x-www-form-urlencoded` query string into a `QueryParams` object.
Automatically decodes percent-encoded characters in keys and values.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `qs` | Raw query string (without or with leading '?'). |

#### Returns

Populated `QueryParams` instance.

---

### `build` <a id="build"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn build(qp: QueryParams): str
```

Formats a `QueryParams` instance into a percent-encoded query string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `qp` | Parameters to serialize. |

#### Returns

Percent-encoded query string.

---

### `index_of` <a id="index_of"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn index_of(s: str, pattern: str): int
```

---

### `split_str` <a id="split_str"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn split_str(s: str, delimiter: str): list
```

---


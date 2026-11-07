# API Documentation: `url.lm`

## Overview

std/url/url.lm
RFC 3986 Uniform Resource Identifier (URI) / URL parser and resolver.

## Symbols

- **Frame**: [`URL`](#URL)
- **Function**: [`build`](#build)
- **Function**: [`to_lower`](#to_lower)
- **Function**: [`normalize_path`](#normalize_path)
- **Function**: [`find_last`](#find_last)
- **Function**: [`index_of`](#index_of)
- **Function**: [`split_str`](#split_str)
- **Function**: [`substring`](#substring)

---

### `URL` <a id="URL"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame URL
```

Represents a parsed Uniform Resource Locator (URL) conforming to RFC 3986.
Decomposes URLs into scheme, user credentials, host, port, path, query, and fragment.
Supports IPv6 bracketed hosts, default port inference, query parsing, and relative path resolution.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Use `url.resolve("...")` to resolve relative hyperlinks against a base document URL.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `url_str` | Optional candidate URL string to parse immediately upon instantiation. |

#### Example: Idiomatic Usage

```lymar
import std.url as url;
var u = url.URL("https://user:pass@example.com:8080/api/v1?page=1#section");
print("Host: {u.host}, Port: {u.port}, Path: {u.path}");
```

#### Members

- `var pub fragment: str` *(field)*
- `var pub host: str` *(field)*
- `var pub is_valid: bool` *(field)*
- `var pub password: str` *(field)*
- `var pub path: str` *(field)*
- `var pub port: int` *(field)*
- `var pub query: str` *(field)*
- `var pub scheme: str` *(field)*
- `var pub username: str` *(field)*
- `pub init(url_str: str)` *(constructor)*
- `pub fn parse(url_str: str)` *(method)*
- `pub fn to_string(): str` *(method)*
- `pub fn query_params(): query.QueryParams` *(method)*
- `pub fn origin(): str` *(method)*
- `pub fn resolve(relative: str): URL` *(method)*

---

### `build` <a id="build"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn build(scheme: str, host: str, port: int, path: str, query: str, fragment: str): URL
```

Constructs a URL object directly from discrete components.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `scheme` | URL scheme (e.g. "https", "http"). |
| `host` | Hostname or IP. |
| `port` | Integer port (-1 for default). |
| `path` | Resource path. |
| `query` | Query string without leading '?'. |
| `fragment` | Fragment without leading '#'. |

#### Returns

Configured URL instance.

---

### `to_lower` <a id="to_lower"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn to_lower(s: str): str
```

---

### `normalize_path` <a id="normalize_path"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn normalize_path(path_val: str): str
```

---

### `find_last` <a id="find_last"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn find_last(s: str, ch: str): int
```

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

### `substring` <a id="substring"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn substring(s: str, start: int, end_idx: int): str
```

---


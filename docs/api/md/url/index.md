# API Documentation: `index.lm`

## Overview

std/url/index.lm
Public entrypoint and facade for std.url. URL parsing, URL encoding, query strings, and URI resolution.

## Symbols

- **Function**: [`parse`](#parse)
- **Function**: [`parse_query`](#parse_query)
- **Function**: [`build`](#build)

---

### `parse` <a id="parse"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse(url_str: str): url.URL
```

Parses a URL string into its discrete RFC 3986 components.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `url_str` | Target URL string to parse. |

#### Returns

Configured `URL` instance.

---

### `parse_query` <a id="parse_query"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_query(qs: str): query.QueryParams
```

Parses an `application/x-www-form-urlencoded` query string into a `QueryParams` object.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `qs` | Raw query string (with or without leading '?'). |

#### Returns

Populated `QueryParams` instance.

---

### `build` <a id="build"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn build(scheme: str, host: str, port: int, path: str, query: str, fragment: str): url.URL
```

Constructs a URL object directly from discrete components.

#### Preconditions (Contracts)

- `requires len(scheme) > 0`
- `requires port == -1 or (port > 0 and port <= 65535)`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `scheme` | URL scheme (e.g. "https", "http"). |
| `host` | Hostname or IP address. |
| `port` | Integer port (-1 for default). |
| `path` | Hierarchical resource path. |
| `query` | Query parameter string. |
| `fragment` | Section anchor fragment. |

#### Returns

Configured `URL` instance.

---


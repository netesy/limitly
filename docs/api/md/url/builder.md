# API Documentation: `builder.lm`

## Overview

std/url/builder.lm
Builder submodule for std.url. URL parsing, URL encoding, query strings, and URI resolution.

## Symbols

- **Frame**: [`Builder`](#Builder)

---

### `Builder` <a id="Builder"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Builder
```

Fluent builder for constructing and configuring RFC 3986 URLs.
Provides a chainable interface to set individual URL components (scheme, host, port, path, query, fragment, credentials)
before producing an immutable `URL` instance.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Use this builder when assembling URLs dynamically with optional queries and authentication parameters.

#### Example: Idiomatic Usage

```lymar
import std.url.builder as builder;
var u = builder.Builder()
    .set_scheme("https")
    .set_host("api.example.com")
    .set_path("/v1/items")
    .set_query("limit=50")
    .build();
```

#### Members

- `var pub fragment: str` *(field)*
- `var pub host: str` *(field)*
- `var pub password: str` *(field)*
- `var pub path: str` *(field)*
- `var pub port: int` *(field)*
- `var pub query: str` *(field)*
- `var pub scheme: str` *(field)*
- `var pub username: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_scheme(scheme: str): Builder` *(method)*
- `pub fn set_host(host: str): Builder` *(method)*
- `pub fn set_port(port: int): Builder` *(method)*
- `pub fn set_path(path: str): Builder` *(method)*
- `pub fn set_query(query: str): Builder` *(method)*
- `pub fn set_fragment(fragment: str): Builder` *(method)*
- `pub fn set_username(username: str): Builder` *(method)*
- `pub fn set_password(password: str): Builder` *(method)*
- `pub fn build(): url.URL` *(method)*

---


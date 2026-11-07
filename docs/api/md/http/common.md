# API Documentation: `common.lm`

## Overview

HTTP Common: shared types, constants, and utilities for the HTTP module.

## Symbols

- **Function**: [`method_name`](#method_name)
- **Function**: [`status_code`](#status_code)
- **Function**: [`is_informational`](#is_informational)
- **Function**: [`is_success`](#is_success)
- **Function**: [`is_redirect`](#is_redirect)
- **Function**: [`is_client_error`](#is_client_error)
- **Function**: [`is_server_error`](#is_server_error)
- **Function**: [`is_error`](#is_error)
- **Function**: [`is_valid_method`](#is_valid_method)
- **Function**: [`status_text`](#status_text)
- **Function**: [`parse_status_line`](#parse_status_line)
- **Function**: [`parse_headers`](#parse_headers)
- **Function**: [`build_headers_block`](#build_headers_block)
- **Function**: [`parse_query_string`](#parse_query_string)
- **Function**: [`build_query_string`](#build_query_string)
- **Function**: [`parse_cookies`](#parse_cookies)

---

### `method_name` <a id="method_name"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn method_name(m): str
```

Converts an HTTP Method or string to uppercase canonical method name.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `m` | Method enum variant or method name string. |

#### Returns

Uppercase method string (e.g. `"GET"`).

---

### `status_code` <a id="status_code"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn status_code(s: Status): int
```

---

### `is_informational` <a id="is_informational"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_informational(code: int): bool
```

--- Status code classification helpers ---

---

### `is_success` <a id="is_success"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_success(code: int): bool
```

---

### `is_redirect` <a id="is_redirect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_redirect(code: int): bool
```

---

### `is_client_error` <a id="is_client_error"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_client_error(code: int): bool
```

---

### `is_server_error` <a id="is_server_error"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_server_error(code: int): bool
```

---

### `is_error` <a id="is_error"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_error(code: int): bool
```

---

### `is_valid_method` <a id="is_valid_method"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_valid_method(m: str): bool
```

---

### `status_text` <a id="status_text"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn status_text(code: int): str
```

--- Status code to reason phrase mapping ---

---

### `parse_status_line` <a id="parse_status_line"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_status_line(line: str): list
```

Parse status line: returns [version, code_str, reason]

---

### `parse_headers` <a id="parse_headers"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_headers(block: str): dict
```

Parse headers block into a dictionary mapping lowercase names to values

---

### `build_headers_block` <a id="build_headers_block"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn build_headers_block(headers: dict): str
```

Build a serialized headers block string

---

### `parse_query_string` <a id="parse_query_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_query_string(qs: str): dict
```

Parse URL-encoded query string or form body into a dictionary

---

### `build_query_string` <a id="build_query_string"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn build_query_string(params: dict): str
```

Build URL query string from parameters

---

### `parse_cookies` <a id="parse_cookies"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_cookies(cookie_header: str): dict
```

Parse Cookie header into dictionary of cookie name-value pairs

---


# API Documentation: `client.lm`

## Overview

Full HTTP/1.1 client built on top of TCP and DNS resources.

## Symbols

- **Frame**: [`Request`](#Request)
- **Frame**: [`Response`](#Response)
- **Frame**: [`Client`](#Client)
- **Function**: [`parse_http_response`](#parse_http_response)
- **Function**: [`populate_response_headers`](#populate_response_headers)
- **Function**: [`get`](#get)
- **Function**: [`post`](#post)
- **Function**: [`put`](#put)
- **Function**: [`delete`](#delete)
- **Frame**: [`Stream2`](#Stream2)
- **Frame**: [`Client3`](#Client3)

---

### `Request` <a id="Request"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Request
```

#### Members

- `var pub method: str` *(field)*
- `var pub url_str: str` *(field)*
- `var pub headers: dict` *(field)*
- `var pub body: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_header(name: str, value: str): Request` *(method)*
- `pub fn header(name: str): str` *(method)*
- `pub fn set_body(body: str): Request` *(method)*
- `pub fn set_json(json_str: str): Request` *(method)*
- `pub fn set_form(params: dict): Request` *(method)*
- `pub fn set_bearer_token(token: str): Request` *(method)*

---

### `Response` <a id="Response"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Response
```

#### Members

- `var pub status_code: int` *(field)*
- `var pub status_text: str` *(field)*
- `var pub headers: dict` *(field)*
- `var pub body: str` *(field)*
- `var pub protocol: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn is_success(): bool` *(method)*
- `pub fn is_redirect(): bool` *(method)*
- `pub fn is_error(): bool` *(method)*
- `pub fn header(name: str): str` *(method)*
- `pub fn content_type(): str` *(method)*
- `pub fn content_length(): int` *(method)*
- `pub fn cookies(): dict` *(method)*
- `pub fn cookie(name: str): str` *(method)*
- `pub fn text(): str` *(method)*
- `pub fn json(): str` *(method)*

---

### `Client` <a id="Client"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Client
```

#### Members

- `var pub follow_redirects: bool` *(field)*
- `var pub max_redirects: int` *(field)*
- `var pub default_headers: dict` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_header(name: str, value: str): Client` *(method)*
- `pub fn get(url_str: str): Response` *(method)*
- `pub fn post(url_str: str, body: str): Response` *(method)*
- `pub fn put(url_str: str, body: str): Response` *(method)*
- `pub fn delete(url_str: str): Response` *(method)*
- `pub fn patch(url_str: str, body: str): Response` *(method)*
- `pub fn head(url_str: str): Response` *(method)*
- `pub fn execute(req: Request): Response` *(method)*
- `fn execute_single(req: Request): Response` *(method)*

---

### `parse_http_response` <a id="parse_http_response"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_http_response(raw: str): Response
```

---

### `populate_response_headers` <a id="populate_response_headers"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn populate_response_headers(resp: Response, header_section: str)
```

---

### `get` <a id="get"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn get(url_str: str): Response?
```

---

### `post` <a id="post"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn post(url_str: str, body: str, content_type: str = ...): Response?
```

---

### `put` <a id="put"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn put(url_str: str, body: str, content_type: str = ...): Response?
```

---

### `delete` <a id="delete"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn delete(url_str: str): Response?
```

---

### `Stream2` <a id="Stream2"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Stream2
```

#### Members

- `var pub stream_id: int` *(field)*
- `var pub state: str` *(field)*
- `var pub headers: dict` *(field)*
- `var pub body: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn send_headers(headers: dict): bool` *(method)*
- `pub fn send_data(data: str, end_stream: bool): bool` *(method)*
- `pub fn close(): nil` *(method)*

---

### `Client3` <a id="Client3"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Client3
```

#### Members

- `var pub host: str` *(field)*
- `var pub port: int` *(field)*
- `var pub is_quic_connected: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn connect(): bool` *(method)*
- `pub fn request(req: Request): Response` *(method)*
- `pub fn close(): nil` *(method)*

---


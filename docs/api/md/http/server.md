# API Documentation: `server.lm`

## Overview

HTTP Server Module
Built on the standard resource abstraction.

## Symbols

- **Frame**: [`ServerRequest`](#ServerRequest)
- **Frame**: [`ServerResponse`](#ServerResponse)
- **Type Alias**: [`ResultServerRequest`](#ResultServerRequest)
- **Frame**: [`Server`](#Server)
- **Function**: [`parse_server_request`](#parse_server_request)
- **Function**: [`decode_chunked_body`](#decode_chunked_body)
- **Function**: [`hex_digit_val`](#hex_digit_val)
- **Function**: [`parse_hex`](#parse_hex)
- **Frame**: [`Server2`](#Server2)

---

### `ServerRequest` <a id="ServerRequest"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ServerRequest
```

#### Members

- `var pub method: str` *(field)*
- `var pub path: str` *(field)*
- `var pub query_string: str` *(field)*
- `var pub query_params: dict` *(field)*
- `var pub version: str` *(field)*
- `var pub headers: dict` *(field)*
- `var pub body: str` *(field)*
- `var pub remote_addr: str` *(field)*
- `var pub client_resource: res.Resource?` *(field)*
- `pub init()` *(constructor)*
- `pub fn header(name: str): str` *(method)*
- `pub fn query(name: str): str` *(method)*
- `pub fn is_json(): bool` *(method)*
- `pub fn cookies(): dict` *(method)*
- `pub fn cookie(name: str): str` *(method)*

---

### `ServerResponse` <a id="ServerResponse"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ServerResponse
```

#### Members

- `var pub status: int` *(field)*
- `var pub status_text: str` *(field)*
- `var pub headers: dict` *(field)*
- `var pub body: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_header(name: str, value: str): ServerResponse` *(method)*
- `pub fn set_cookie(name: str, value: str): ServerResponse` *(method)*
- `pub fn header(name: str): str` *(method)*
- `pub fn text(): ServerResponse` *(method)*
- `pub fn json(): ServerResponse` *(method)*
- `pub fn html(): ServerResponse` *(method)*
- `pub fn redirect(location: str): ServerResponse` *(method)*
- `pub fn not_found(): ServerResponse` *(method)*

---

### `ResultServerRequest` <a id="ResultServerRequest"></a>

**Kind**: Type Alias  
**Visibility**: `pub`  

```lymar
type ResultServerRequest = union
```

---

### `Server` <a id="Server"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Server
```

#### Members

- `var pub host: str` *(field)*
- `var pub port: int` *(field)*
- `var pub handle: int` *(field)*
- `var pub running: bool` *(field)*
- `var pub resource: res.Resource?` *(field)*
- `var pub binder: res.Binder?` *(field)*
- `var pub listener: res.Listener?` *(field)*
- `var pub accepter: res.Accepter?` *(field)*
- `pub init()` *(constructor)*
- `pub fn listen(host: str, port: int): int` *(method)*
- `pub fn close(): nil` *(method)*
- `pub fn accept_client(): res.Resource?` *(method)*
- `pub fn read_request(client: res.Resource): ServerRequest?` *(method)*
- `pub fn send_response(client: res.Resource, resp: ServerResponse): bool` *(method)*
- `pub fn serve(handler: any): bool` *(method)*

---

### `parse_server_request` <a id="parse_server_request"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_server_request(raw: str): ServerRequest
```

---

### `decode_chunked_body` <a id="decode_chunked_body"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn decode_chunked_body(body_str: str): str
```

---

### `hex_digit_val` <a id="hex_digit_val"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn hex_digit_val(ch: str): int
```

---

### `parse_hex` <a id="parse_hex"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn parse_hex(s: str): int
```

---

### `Server2` <a id="Server2"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Server2
```

#### Members

- `var pub active_streams: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn handle_stream(stream_id: int, req: ServerRequest): ServerResponse` *(method)*

---


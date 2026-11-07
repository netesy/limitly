# API Documentation: `router.lm`

## Overview

HTTP Router Module: Route matching, parameterized routes, and request handling.

## Symbols

- **Frame**: [`RouteRequest`](#RouteRequest)
- **Frame**: [`RouteResponse`](#RouteResponse)
- **Frame**: [`Route`](#Route)
- **Frame**: [`Router`](#Router)
- **Function**: [`router`](#router)
- **Function**: [`make_router`](#make_router)
- **Function**: [`split_path`](#split_path)
- **Function**: [`match_pattern`](#match_pattern)

---

### `RouteRequest` <a id="RouteRequest"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame RouteRequest
```

#### Members

- `var pub method: str` *(field)*
- `var pub path: str` *(field)*
- `var pub headers: list` *(field)*
- `var pub header_map: dict` *(field)*
- `var pub params: dict` *(field)*
- `var pub query: dict` *(field)*
- `var pub body: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn param(name: str): str` *(method)*
- `pub fn query_val(name: str): str` *(method)*
- `pub fn header(name: str): str` *(method)*

---

### `RouteResponse` <a id="RouteResponse"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame RouteResponse
```

#### Members

- `var pub status_code: int` *(field)*
- `var pub headers: list` *(field)*
- `var pub body: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn json(data: str): RouteResponse` *(method)*
- `pub fn html(data: str): RouteResponse` *(method)*
- `pub fn text(data: str): RouteResponse` *(method)*
- `pub fn status(code: int): RouteResponse` *(method)*
- `pub fn set_header(header_line: str): RouteResponse` *(method)*

---

### `Route` <a id="Route"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Route
```

#### Members

- `var pub method: str` *(field)*
- `var pub path: str` *(field)*
- `var pub handler: function` *(field)*
- `pub init(m: str, p: str, h: function)` *(constructor)*
- `pub fn matches(req_method: str, req_path: str): bool` *(method)*
- `pub fn extract_params(req_path: str): dict` *(method)*

---

### `Router` <a id="Router"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Router
```

#### Members

- `var pub routes: list` *(field)*
- `pub init()` *(constructor)*
- `pub fn get(path: str, handler: function): Router` *(method)*
- `pub fn post(path: str, handler: function): Router` *(method)*
- `pub fn put(path: str, handler: function): Router` *(method)*
- `pub fn delete(path: str, handler: function): Router` *(method)*
- `pub fn patch(path: str, handler: function): Router` *(method)*
- `pub fn route(method: str, path: str, handler: function): Router` *(method)*
- `pub fn handle(req: RouteRequest): RouteResponse` *(method)*

---

### `router` <a id="router"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn router(): Router
```

---

### `make_router` <a id="make_router"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn make_router(): Router
```

---

### `split_path` <a id="split_path"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn split_path(p: str): list
```

---

### `match_pattern` <a id="match_pattern"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn match_pattern(pattern: str, actual: str): bool
```

---


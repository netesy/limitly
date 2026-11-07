# API Documentation: `server.lm`

## Overview

Provides WebSocket server utilities built on the raw WebSocket client module.

Operations that can fail return `T?Error` and carry a diagnostic code; the
ones that cannot (`join`, `leave`, `broadcast` on a room) just return a count.

## Symbols

- **Frame**: [`Connection`](#Connection)
- **Frame**: [`Server`](#Server)
- **Frame**: [`Room`](#Room)
- **Function**: [`__room_keys`](#__room_keys)

---

### `Connection` <a id="Connection"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Connection
```

#### Members

- `var pub resource: res.Resource?` *(field)*
- `var pub writer: res.Writer?` *(field)*
- `var pub reader: res.Reader?` *(field)*
- `var pub poller: res.Poller?` *(field)*
- `var pub remote_addr: str` *(field)*
- `var pub connected: bool` *(field)*
- `var pub id: str` *(field)*
- `pub init(handle: int)` *(constructor)*
- `pub fn send(message: str): int` *(method)*
- `pub fn recv(): str` *(method)*
- `pub fn has_message(): bool` *(method)*
- `pub fn send_ping(): bool` *(method)*
- `pub fn send_pong(): bool` *(method)*
- `pub fn close(): nil` *(method)*

---

### `Server` <a id="Server"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Server
```

#### Members

- `var host: str` *(field)*
- `var port: int` *(field)*
- `var running: bool` *(field)*
- `var on_connect: str` *(field)*
- `var on_message: str` *(field)*
- `var on_disconnect: str` *(field)*
- `var pub resource: res.Resource?` *(field)*
- `var pub binder: res.Binder?` *(field)*
- `var pub listener: res.Listener?` *(field)*
- `pub init()` *(constructor)*
- `pub fn set_host(host: str): Server` *(method)*
- `pub fn set_port(port: int): Server` *(method)*
- `pub fn on_connection(handler: str): Server` *(method)*
- `pub fn on_message_handler(handler: str): Server` *(method)*
- `pub fn on_disconnection(handler: str): Server` *(method)*
- `pub fn start(): int` *(method)*
- `pub fn accept(): str` *(method)*
- `pub fn broadcast(handles: list, message: str): int` *(method)*
- `pub fn stop(): nil` *(method)*
- `pub fn select_subprotocol(requested: str, supported: list): str` *(method)*
- `pub fn is_running(): bool` *(method)*

---

### `Room` <a id="Room"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Room
```

#### Members

- `var name: str` *(field)*
- `var connections: dict` *(field)*
- `pub init(name: str)` *(constructor)*
- `pub fn join(id: str, conn: Connection): int` *(method)*
- `pub fn leave(id: str): int` *(method)*
- `pub fn member_count(): int` *(method)*
- `pub fn broadcast(message: str): int` *(method)*

---

### `__room_keys` <a id="__room_keys"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn __room_keys(connections: dict): list
```

Keys of a connection table. `iter` inside a frame method aborts the compiler,
so the loop lives in this free function and the methods walk the resulting
list with a while loop. Dictionaries are walked with the two-variable form,
`iter (key, value in dict)`.

---


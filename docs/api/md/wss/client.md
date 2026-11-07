# API Documentation: `client.lm`

## Overview

Uses the native WEBSOCKET resource for real WebSocket connections.

## Symbols

- **Frame**: [`Client`](#Client)
- **Function**: [`mask_payload`](#mask_payload)

---

### `Client` <a id="Client"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Client
```

#### Members

- `var pub resource: res.Resource?` *(field)*
- `var pub connector: res.Connector?` *(field)*
- `var pub writer: res.Writer?` *(field)*
- `var pub reader: res.Reader?` *(field)*
- `var pub poller: res.Poller?` *(field)*
- `pub init()` *(constructor)*
- `pub fn connect(url_str: str): int` *(method)*
- `pub fn send_text(message: str): int` *(method)*
- `pub fn recv(): str` *(method)*
- `pub fn has_message(): bool` *(method)*
- `pub fn close(): nil` *(method)*
- `pub fn is_connected(): bool` *(method)*
- `pub fn send_ping(): bool` *(method)*
- `pub fn send_pong(): bool` *(method)*
- `pub fn send_frame_masked(opcode: int, data: str): bool` *(method)*

---

### `mask_payload` <a id="mask_payload"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn mask_payload(data: str, mask_key: list): str
```

---


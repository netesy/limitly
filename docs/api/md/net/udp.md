# API Documentation: `udp.lm`

## Overview

std/net/udp.lm
Udp submodule for std.net. Network communications: TCP, UDP sockets, and network addressing.

## Symbols

- **Frame**: [`Datagram`](#Datagram)
- **Frame**: [`UDP`](#UDP)

---

### `Datagram` <a id="Datagram"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Datagram
```

#### Members

- `var resource: res.Resource` *(field)*
- `pub init(r: res.Resource)` *(constructor)*
- `pub fn send_to(addr: str, port: int, data: str): any` *(method)*
- `pub fn recv_from(): any` *(method)*

---

### `UDP` <a id="UDP"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame UDP
```

#### Members

- `var resource: res.Resource?` *(field)*
- `var binder: res.Binder?` *(field)*
- `var datagram: Datagram?` *(field)*
- `var poller: res.Pollable?` *(field)*
- `pub init()` *(constructor)*
- `pub fn bind(address: str, port: int): int` *(method)*
- `pub fn create(): int` *(method)*
- `pub fn send_to(address: str, port: int, data: str): int` *(method)*
- `pub fn recv_from(): str` *(method)*
- `pub fn has_data(): bool` *(method)*
- `pub fn close(): nil` *(method)*

---


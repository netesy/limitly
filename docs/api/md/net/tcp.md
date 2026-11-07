# API Documentation: `tcp.lm`

## Overview

std/net/tcp.lm
Tcp submodule for std.net. Network communications: TCP, UDP sockets, and network addressing.

## Symbols

- **Frame**: [`Connector`](#Connector)
- **Frame**: [`Binder`](#Binder)
- **Frame**: [`Listener`](#Listener)
- **Frame**: [`Accepter`](#Accepter)
- **Frame**: [`Socket`](#Socket)
- **Frame**: [`Server`](#Server)

---

### `Connector` <a id="Connector"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Connector
```

#### Members

- `var resource: res.Resource` *(field)*
- `pub init(r: res.Resource)` *(constructor)*
- `pub fn connect(args: list): bool` *(method)*

---

### `Binder` <a id="Binder"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Binder
```

#### Members

- `var resource: res.Resource` *(field)*
- `pub init(r: res.Resource)` *(constructor)*
- `pub fn bind(args: list): bool` *(method)*

---

### `Listener` <a id="Listener"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Listener
```

#### Members

- `var resource: res.Resource` *(field)*
- `pub init(r: res.Resource)` *(constructor)*
- `pub fn listen(args: list): bool` *(method)*

---

### `Accepter` <a id="Accepter"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Accepter
```

#### Members

- `var resource: res.Resource` *(field)*
- `pub init(r: res.Resource)` *(constructor)*
- `pub fn accept(): int` *(method)*

---

### `Socket` <a id="Socket"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Socket
```

#### Members

- `var pub resource: res.Resource?` *(field)*
- `var pub reader: res.Reader?` *(field)*
- `var pub writer: res.Writer?` *(field)*
- `var pub poller: res.Pollable?` *(field)*
- `pub init()` *(constructor)*
- `pub fn connect(address: str, port: int): int` *(method)*
- `pub fn send(data: str): int` *(method)*
- `pub fn recv(): str` *(method)*
- `pub fn has_data(): bool` *(method)*
- `pub fn close(): nil` *(method)*
- `pub fn is_connected(): bool` *(method)*
- `pub fn handle(): int` *(method)*

---

### `Server` <a id="Server"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Server
```

#### Members

- `var pub resource: res.Resource?` *(field)*
- `var pub binder: Binder?` *(field)*
- `var pub listener: Listener?` *(field)*
- `var pub accepter: Accepter?` *(field)*
- `pub init()` *(constructor)*
- `pub fn bind(address: str, port: int): int` *(method)*
- `pub fn listen(backlog: int): int` *(method)*
- `pub fn accept(): Socket` *(method)*
- `pub fn close(): nil` *(method)*

---


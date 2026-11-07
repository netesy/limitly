# API Documentation: `index.lm`

## Overview

std/resource/index.lm
Public entrypoint and facade for std.resource. Resource management and operating system handles.

## Symbols

- **Frame**: [`Resource`](#Resource)
- **Frame**: [`Memory`](#Memory)
- **Frame**: [`Reader`](#Reader)
- **Frame**: [`Writer`](#Writer)
- **Frame**: [`Pollable`](#Pollable)
- **Frame**: [`Poller`](#Poller)
- **Frame**: [`Connector`](#Connector)
- **Frame**: [`Binder`](#Binder)
- **Frame**: [`Listener`](#Listener)
- **Frame**: [`Accepter`](#Accepter)
- **Function**: [`create_hash_engine`](#create_hash_engine)
- **Function**: [`create_dns_resolver`](#create_dns_resolver)
- **Function**: [`open_file`](#open_file)
- **Function**: [`create_fs_resource`](#create_fs_resource)
- **Function**: [`create_socket`](#create_socket)
- **Function**: [`create_udp_socket`](#create_udp_socket)
- **Function**: [`create_websocket`](#create_websocket)
- **Function**: [`create_entropy`](#create_entropy)
- **Function**: [`create_os_resource`](#create_os_resource)
- **Function**: [`create_process_resource`](#create_process_resource)
- **Function**: [`create_memory`](#create_memory)
- **Function**: [`create`](#create)
- **Function**: [`adopt_socket`](#adopt_socket)
- **Function**: [`_call`](#_call)

---

### `Resource` <a id="Resource"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Resource
```

#### Members

- `var pub handle: int` *(field)*
- `var pub kind: int` *(field)*
- `var pub is_open_val: bool` *(field)*
- `pub init(h: int, k: int)` *(constructor)*
- `pub fn close(): nil?` *(method)*
- `pub fn is_open(): bool` *(method)*
- `pub fn _handle(): int` *(method)*

---

### `Memory` <a id="Memory"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Memory
```

Byte-buffer resource backed by the RT_MEMORY resource, exposing memory measurement.

#### Members

- `var pub resource: Resource` *(field)*
- `pub init(r: Resource)` *(constructor)*
- `pub fn resize(size: int): bool` *(method)*
- `pub fn size(): int` *(method)*
- `pub fn capacity(): int` *(method)*
- `pub fn write(data: str): bool` *(method)*
- `pub fn read(): str` *(method)*
- `pub fn is_open(): bool` *(method)*
- `pub fn release(): bool` *(method)*
- `pub fn close(): nil?` *(method)*

---

### `Reader` <a id="Reader"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Reader
```

#### Members

- `var pub resource: Resource` *(field)*
- `pub init(r: Resource)` *(constructor)*
- `pub fn read(args: list): any` *(method)*
- `pub fn read_bytes(): list` *(method)*

---

### `Writer` <a id="Writer"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Writer
```

#### Members

- `var pub resource: Resource` *(field)*
- `pub init(r: Resource)` *(constructor)*
- `pub fn write(args: list): any` *(method)*

---

### `Pollable` <a id="Pollable"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Pollable
```

#### Members

- `var pub resource: Resource` *(field)*
- `pub init(r: Resource)` *(constructor)*
- `pub fn poll(): bool` *(method)*

---

### `Poller` <a id="Poller"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Poller
```

#### Members

- `var pub resource: Resource` *(field)*
- `pub init(r: Resource)` *(constructor)*
- `pub fn poll(): bool` *(method)*

---

### `Connector` <a id="Connector"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Connector
```

#### Members

- `var pub resource: Resource` *(field)*
- `pub init(r: Resource)` *(constructor)*
- `pub fn connect(args: list): bool` *(method)*

---

### `Binder` <a id="Binder"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Binder
```

#### Members

- `var pub resource: Resource` *(field)*
- `pub init(r: Resource)` *(constructor)*
- `pub fn bind(args: list): bool` *(method)*

---

### `Listener` <a id="Listener"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Listener
```

#### Members

- `var pub resource: Resource` *(field)*
- `pub init(r: Resource)` *(constructor)*
- `pub fn listen(args: list): bool` *(method)*

---

### `Accepter` <a id="Accepter"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Accepter
```

#### Members

- `var pub resource: Resource` *(field)*
- `pub init(r: Resource)` *(constructor)*
- `pub fn accept(): int` *(method)*

---

### `create_hash_engine` <a id="create_hash_engine"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_hash_engine(): Resource?
```

---

### `create_dns_resolver` <a id="create_dns_resolver"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_dns_resolver(): Resource?
```

---

### `open_file` <a id="open_file"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn open_file(path: str, mode: str): Resource?
```

---

### `create_fs_resource` <a id="create_fs_resource"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_fs_resource(): Resource?
```

---

### `create_socket` <a id="create_socket"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_socket(): Resource?
```

---

### `create_udp_socket` <a id="create_udp_socket"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_udp_socket(): Resource?
```

---

### `create_websocket` <a id="create_websocket"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_websocket(): Resource?
```

---

### `create_entropy` <a id="create_entropy"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_entropy(): Resource?
```

---

### `create_os_resource` <a id="create_os_resource"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_os_resource(): Resource?
```

---

### `create_process_resource` <a id="create_process_resource"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_process_resource(): Resource?
```

---

### `create_memory` <a id="create_memory"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create_memory(size: int): Memory?
```

Create a byte-buffer memory resource with memory measurement support.
`size` is the initial number of bytes to allocate (0 for an empty buffer).

---

### `create` <a id="create"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn create(type_id: int, args: list): Resource?
```

---

### `adopt_socket` <a id="adopt_socket"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn adopt_socket(fd: int): Resource
```

---

### `_call` <a id="_call"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn _call(h: int, op: int, args: list): any
```

---


# API Documentation: `tls.lm`

## Overview

std/net/tls.lm
Clean, secure TLS 1.2/1.3 client connection backed by OpenSSL

## Symbols

- **Frame**: [`TLSConfig`](#TLSConfig)
- **Frame**: [`TLSSocket`](#TLSSocket)
- **Function**: [`connect`](#connect)

---

### `TLSConfig` <a id="TLSConfig"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TLSConfig
```

#### Members

- `var pub cert_file: str` *(field)*
- `var pub key_file: str` *(field)*
- `var pub ca_file: str` *(field)*
- `var pub verify_peer: bool` *(field)*
- `var pub sni: str` *(field)*
- `var pub timeout_ms: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn with_verify(verify: bool): TLSConfig` *(method)*
- `pub fn with_sni(sni_host: str): TLSConfig` *(method)*
- `pub fn with_ca(ca_path: str): TLSConfig` *(method)*
- `pub fn with_cert(cert_path: str, key_path: str): TLSConfig` *(method)*
- `pub fn with_timeout(ms: int): TLSConfig` *(method)*

---

### `TLSSocket` <a id="TLSSocket"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame TLSSocket
```

#### Members

- `var pub handle: any` *(field)*
- `var pub host: str` *(field)*
- `var pub port: int` *(field)*
- `var pub is_open: bool` *(field)*
- `pub init()` *(constructor)*
- `pub fn write(data: str): int` *(method)*
- `pub fn read(): str` *(method)*
- `pub fn peer_certificate(): str` *(method)*
- `pub fn close(): nil` *(method)*

---

### `connect` <a id="connect"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn connect(host: str, port: int, config: TLSConfig = ...): TLSSocket?
```

---


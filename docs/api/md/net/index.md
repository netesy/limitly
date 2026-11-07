# API Documentation: `index.lm`

## Overview

std/net/index.lm

Core networking facade: TCP client/server sockets, UDP datagrams,
DNS resolution and IP validation, and TLS transport encryption.

@tip Import `std.net as net;` to access high-level networking primitives
under a single cohesive namespace.

@example
import std.net as net;
var ip = net.resolve("example.com")? else {
    print("DNS lookup failed");
    return;
};
print("Resolved: {ip}");

## Symbols

- **Function**: [`connect_tls`](#connect_tls)

---

### `connect_tls` <a id="connect_tls"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn connect_tls(host: str, port: int, cfg: tls.TLSConfig = ...): tls.TLSSocket?
```

Establishes an encrypted TLS client connection to the specified host and port.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Always specify a hostname rather than a raw IP to ensure SNI certificate validation succeeds.

> [!WARNING]
> **Warning**: Connecting with disabled verification exposes connections to man-in-the-middle attacks.

#### Preconditions (Contracts)

- `requires len(host) > 0 and port > 0 and port <= 65535`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `host` | Target server domain name or IP address. |
| `port` | Target TCP port number (1-65535). |
| `cfg` | Optional custom TLSConfig instance. |

#### Returns

Connected TLSSocket, or err(Error).

---


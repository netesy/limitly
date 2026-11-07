# API Documentation: `index.lm`

## Overview

WebSocket umbrella: re-exports the client and server submodules plus the
RFC 6455 close codes as module-level constants.

Usage:
  import std.wss as wss;
  var client = wss.Client();
  client.connect("ws://localhost:8080/ws");
  client.send_text("Hello");
  var msg = client.recv();

## Symbols

- **Function**: [`close_code_value`](#close_code_value)

---

### `close_code_value` <a id="close_code_value"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn close_code_value(code: CloseCode): int
```

---


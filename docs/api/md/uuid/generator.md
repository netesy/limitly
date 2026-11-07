# API Documentation: `generator.lm`

## Overview

std/uuid/generator.lm
RFC 4122 Version 4 (Random) UUID generator.

## Symbols

- **Function**: [`generate_v4`](#generate_v4)

---

### `generate_v4` <a id="generate_v4"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn generate_v4(): uuid.UUID
```

Generates a cryptographically random RFC 4122 Version 4 UUID.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Sets version 4 (bits 4-7 of byte 6 = 0100) and RFC 4122 variant (bits 6-7 of byte 8 = 10).

#### Returns

Newly generated, random UUID instance.

#### Example: Idiomatic Usage

```lymar
import std.uuid as uuid;
var id = uuid.generate_v4();
print("UUID: {id.to_string()}");
```

---


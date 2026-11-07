# API Documentation: `percent.lm`

## Overview

std/encoding/percent.lm
URL Percent-Encoding and Decoding (RFC 3986).

## Symbols

- **Function**: [`encode`](#encode)
- **Function**: [`decode`](#decode)

---

### `encode` <a id="encode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode(s: str): str
```

Percent-encodes reserved URL characters in a string.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Escapes spaces (`%20`), slashes, colons, question marks, and query delimiters.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Source string. |

#### Returns

URL percent-encoded string.

#### Example: Idiomatic Usage

```lymar
import std.encoding.percent as percent;
var encoded = percent.encode("hello world/path");
print("Encoded: {encoded}");
```

---

### `decode` <a id="decode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decode(s: str): str
```

Decodes a URL percent-encoded string back to its raw character form.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Supports both uppercase (`%2F`) and lowercase (`%2f`) hex tokens.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Percent-encoded string. |

#### Returns

Decoded string.

#### Example: Idiomatic Usage

```lymar
import std.encoding.percent as percent;
var decoded = percent.decode("hello%20world");
print("Decoded: {decoded}");
```

---


# API Documentation: `utf8.lm`

## Overview

std/text/utf8.lm
UTF-8 decode/encode over Lymar's byte-indexed strings.

std.string works on BYTES (byte_at, _builtin_substring). BiDi and
shaping need CODEPOINTS, so this module is the boundary: decode a str
into [int] codepoints, encode a codepoint list back to str.
Invalid byte sequences decode as U+FFFD (replacement char), matching
the WHATWG/Unicode recommendation for ill-formed input.

## Symbols

- **Function**: [`decode`](#decode)
- **Function**: [`encode`](#encode)

---

### `decode` <a id="decode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn decode(s: str): list
```

Decode a UTF-8 string into a list of Unicode codepoints.

---

### `encode` <a id="encode"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn encode(cps: list): str
```

Encode a list of codepoints as a UTF-8 string. Out-of-range values
(> U+10FFFF) encode as U+FFFD.

---


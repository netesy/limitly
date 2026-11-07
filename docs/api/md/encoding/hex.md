# API Documentation: `hex.lm`

## Overview

std/encoding/hex.lm
Hexadecimal Encoding and Decoding.

## Symbols

- **Function**: [`hex_char_to_val`](#hex_char_to_val)
- **Function**: [`to_hex`](#to_hex)
- **Function**: [`from_hex`](#from_hex)
- **Function**: [`byte_to_hex`](#byte_to_hex)
- **Function**: [`hex_to_byte`](#hex_to_byte)

---

### `hex_char_to_val` <a id="hex_char_to_val"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn hex_char_to_val(ch: str): int
```

Converts a single hexadecimal ASCII character to its 0-15 integer nibble value.

---

### `to_hex` <a id="to_hex"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn to_hex(bytes: list): str
```

Encodes an array of bytes into a lowercase hexadecimal string.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Every byte produces exactly two hexadecimal characters.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `bytes` | Array of byte values (0-255). |

#### Returns

Lowercase hexadecimal representation.

#### Example: Idiomatic Usage

```lymar
import std.encoding.hex as hex;
var h = hex.to_hex([255, 0, 127]);
print("Hex: {h}"); // "ff007f"
```

---

### `from_hex` <a id="from_hex"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn from_hex(s: str): list
```

Decodes a hexadecimal string into an array of byte integers.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Case-insensitive; accepts uppercase (A-F) and lowercase (a-f) characters.

#### Preconditions (Contracts)

- `requires len(s) % 2 == 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `s` | Hexadecimal string (must have an even length). |

#### Returns

Decoded byte array [int].

#### Example: Idiomatic Usage

```lymar
import std.encoding.hex as hex;
var bytes = hex.from_hex("48656c6c6f");
print("Decoded byte count: {len(bytes)}");
```

---

### `byte_to_hex` <a id="byte_to_hex"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn byte_to_hex(b: int): str
```

Converts a single byte integer into a 2-character lowercase hex string.

#### Preconditions (Contracts)

- `requires b >= 0 and b <= 255`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `b` | Byte value between 0 and 255. |

#### Returns

2-character lowercase hex string.

#### Example: Idiomatic Usage

```lymar
print("Hex: {hex.byte_to_hex(254)}"); // "fe"
```

---

### `hex_to_byte` <a id="hex_to_byte"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn hex_to_byte(h: str): int
```

Parses a 2-character hex string into a single byte integer (0-255).

#### Preconditions (Contracts)

- `requires len(h) >= 2`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `h` | Hex string of at least 2 characters. |

#### Returns

Parsed byte integer.

#### Example: Idiomatic Usage

```lymar
print("Byte: {hex.hex_to_byte(\"ff\")}"); // 255
```

---


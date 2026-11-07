# API Documentation: `reader.lm`

## Overview

std/font/reader.lm
Big-endian binary reader for TrueType/OpenType font structures.

## Symbols

- **Frame**: [`ByteReader`](#ByteReader)

---

### `ByteReader` <a id="ByteReader"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame ByteReader
```

#### Members

- `var pub data: list` *(field)*
- `var pub pos: int` *(field)*
- `var pub size: int` *(field)*
- `pub init(bytes: list)` *(constructor)*
- `pub fn tell(): int` *(method)*
- `pub fn seek(offset: int)` *(method)*
- `pub fn skip(n: int)` *(method)*
- `pub fn has_more(): bool` *(method)*
- `pub fn remaining(): int` *(method)*
- `pub fn read_u8(): int` *(method)*
- `pub fn read_i8(): int` *(method)*
- `pub fn read_u16(): int` *(method)*
- `pub fn read_i16(): int` *(method)*
- `pub fn read_u24(): int` *(method)*
- `pub fn read_u32(): int` *(method)*
- `pub fn read_i32(): int` *(method)*
- `pub fn read_fixed_16_16(): float` *(method)*
- `pub fn read_tag(): int` *(method)*
- `pub fn peek_u8(offset: int): int` *(method)*
- `pub fn peek_u16(offset: int): int` *(method)*
- `pub fn peek_i16(offset: int): int` *(method)*
- `pub fn peek_u32(offset: int): int` *(method)*

---


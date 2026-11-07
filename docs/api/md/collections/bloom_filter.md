# API Documentation: `bloom_filter.lm`

## Overview

Standard Library BloomFilter Collection

## Symbols

- **Frame**: [`BloomFilter`](#BloomFilter)

---

### `BloomFilter` <a id="BloomFilter"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame BloomFilter
```

#### Members

- `var pub bitset: bitset.BitSet` *(field)*
- `var pub size: int` *(field)*
- `var pub num_hashes: int` *(field)*
- `pub init()` *(constructor)*
- `fn hash(item: any, seed: int): int` *(method)*
- `fn _byte_ord(ch: str): int` *(method)*
- `pub fn add(item: any)` *(method)*
- `pub fn contains(item: any): bool` *(method)*

---


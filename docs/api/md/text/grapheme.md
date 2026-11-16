# API Documentation: `grapheme.lm`

## Overview

std/text/grapheme.lm
Codepoint/grapheme-cluster boundary helpers for byte-indexed strings.

std.text stores columns as BYTE offsets (Document uses _builtin_substring).
Cursor movement and deletion must therefore snap to cluster boundaries:
stepping one byte left inside a multi-byte UTF-8 sequence produces
invalid UTF-8. A cluster here = base codepoint + trailing combining
marks (NSM ranges) — the honest subset of UAX #29 (no regional-
indicator pairs, no ZWJ emoji sequences yet; documented limit).

## Symbols

- **Function**: [`seq_len`](#seq_len)
- **Function**: [`is_mark`](#is_mark)
- **Function**: [`decode_at`](#decode_at)
- **Function**: [`prev_boundary`](#prev_boundary)
- **Function**: [`next_boundary`](#next_boundary)

---

### `seq_len` <a id="seq_len"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn seq_len(b: int): int
```

UTF-8 sequence length from the lead byte (1-4). Continuation bytes
and invalid leads return 1 so we always make progress.

---

### `is_mark` <a id="is_mark"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_mark(cp: int): bool
```

Is cp a combining mark that glues to the preceding base char?
Same NSM ranges bidi.lm uses for classification.

---

### `decode_at` <a id="decode_at"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn decode_at(s: str, pos: int): tuple
```

Decode the codepoint whose UTF-8 sequence STARTS at byte offset `pos`.
Returns (codepoint, sequence_length); on invalid input returns
(0xFFFD, 1) so callers always advance.

---

### `prev_boundary` <a id="prev_boundary"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn prev_boundary(s: str, col: int): int
```

Previous cluster boundary at or before byte col. col<=0 -> 0.

---

### `next_boundary` <a id="next_boundary"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn next_boundary(s: str, col: int): int
```

Next cluster boundary at or after byte col. col>=len -> len.

---


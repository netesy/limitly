# API Documentation: `basic.lm`

## Overview

std/string/basic.lm
Length, positional byte/substring access and byte-wise ordering.

## Symbols

- **Function**: [`length`](#length)
- **Function**: [`byte_at`](#byte_at)
- **Function**: [`substr`](#substr)
- **Function**: [`substring`](#substring)
- **Function**: [`compare`](#compare)

---

### `length` <a id="length"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn length(value: str): int
```

Returns the byte length of the given string.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Wraps `len(value)` for idiomatic functional composition.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The string to measure. |

#### Returns

Length of the string in bytes.

---

### `byte_at` <a id="byte_at"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn byte_at(value: str, index: int): int
```

Retrieves the raw byte value at the specified zero-based index.

#### Preconditions (Contracts)

- `requires index >= 0 and index < len(value)`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The target string. |
| `index` | Zero-based byte offset. |

#### Returns

Byte value as integer (0-255).

---

### `substr` <a id="substr"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn substr(value: str, start: int, end: int): str
```

Extracts a substring from start index to end index (exclusive).

#### Preconditions (Contracts)

- `requires start >= 0 and start <= end and end <= len(value)`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The target string. |
| `start` | Starting byte index (inclusive). |
| `end` | Ending byte index (exclusive). |

#### Returns

Extracted substring.

---

### `substring` <a id="substring"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn substring(value: str, start: int, end: int): str
```

Extracts a substring from start index to end index (exclusive).

> [!TIP]
> **Idiomatic Usage & Best Practice**: Alias for `substr`.

#### Preconditions (Contracts)

- `requires start >= 0 and start <= end and end <= len(value)`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The target string. |
| `start` | Starting byte index (inclusive). |
| `end` | Ending byte index (exclusive). |

#### Returns

Extracted substring.

---

### `compare` <a id="compare"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn compare(left: str, right: str): int
```

Lexicographically compares two strings byte-by-byte.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `left` | The first string. |
| `right` | The second string. |

#### Returns

-1 if left < right, 0 if left == right, 1 if left > right.

---


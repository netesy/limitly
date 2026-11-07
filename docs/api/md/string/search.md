# API Documentation: `search.lm`

## Overview

std/string/search.lm
Containment and prefix/suffix tests.

## Symbols

- **Function**: [`contains`](#contains)
- **Function**: [`starts_with`](#starts_with)
- **Function**: [`ends_with`](#ends_with)

---

### `contains` <a id="contains"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn contains(value: str, needle: str): bool
```

Checks whether `needle` occurs anywhere within `value`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The string to search within. |
| `needle` | The substring to search for. |

#### Returns

`true` if `needle` is found, `false` otherwise.

#### Example: Idiomatic Usage

```lymar
var has_limit = search.contains("limitless", "limit");
```

---

### `starts_with` <a id="starts_with"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn starts_with(value: str, prefix: str): bool
```

Checks whether `value` begins with the given `prefix`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The string to test. |
| `prefix` | The prefix to search for. |

#### Returns

`true` if `value` starts with `prefix`, `false` otherwise.

---

### `ends_with` <a id="ends_with"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn ends_with(value: str, suffix: str): bool
```

Checks whether `value` ends with the given `suffix`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The string to test. |
| `suffix` | The suffix to search for. |

#### Returns

`true` if `value` ends with `suffix`, `false` otherwise.

---


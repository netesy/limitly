# API Documentation: `casing.lm`

## Overview

std/string/casing.lm
Case conversion helpers.

## Symbols

- **Function**: [`to_lower`](#to_lower)
- **Function**: [`to_upper`](#to_upper)
- **Function**: [`uppercase`](#uppercase)
- **Function**: [`lowercase`](#lowercase)

---

### `to_lower` <a id="to_lower"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn to_lower(value: str): str
```

Converts all ASCII characters in `value` to lowercase.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The input string. |

#### Returns

New lowercase string.

---

### `to_upper` <a id="to_upper"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn to_upper(value: str): str
```

Converts all ASCII characters in `value` to uppercase.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The input string. |

#### Returns

New uppercase string.

---

### `uppercase` <a id="uppercase"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn uppercase(value: str): str
```

Alias for `to_upper`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The input string. |

#### Returns

New uppercase string.

---

### `lowercase` <a id="lowercase"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lowercase(value: str): str
```

Alias for `to_lower`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | The input string. |

#### Returns

New lowercase string.

---


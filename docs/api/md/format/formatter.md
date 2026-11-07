# API Documentation: `formatter.lm`

## Overview

Standard Library Format Formatter Submodule

String alignment, case conversions, and primitive value representations.

## Symbols

- **Function**: [`format_int`](#format_int)
- **Function**: [`format_float`](#format_float)
- **Function**: [`format_bool`](#format_bool)
- **Function**: [`pad_left`](#pad_left)
- **Function**: [`pad_right`](#pad_right)
- **Function**: [`center`](#center)
- **Function**: [`truncate`](#truncate)
- **Function**: [`title_case`](#title_case)
- **Function**: [`snake_case`](#snake_case)
- **Function**: [`camel_case`](#camel_case)
- **Function**: [`kebab_case`](#kebab_case)
- **Function**: [`pascal_case`](#pascal_case)

---

### `format_int` <a id="format_int"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn format_int(value: int): str
```

Formats an integer value as a string representation.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Integer number to convert. |

#### Returns

String representation of the integer.

#### Example: Idiomatic Usage

```lymar
var txt = format_int(42);
```

---

### `format_float` <a id="format_float"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn format_float(value: float): str
```

Formats a floating-point value as a string representation.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Floating-point number to convert. |

#### Returns

String representation of the float.

#### Example: Idiomatic Usage

```lymar
var txt = format_float(3.14159);
```

---

### `format_bool` <a id="format_bool"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn format_bool(value: bool): str
```

Formats a boolean value as `"true"` or `"false"`.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Boolean to convert. |

#### Returns

Literal `"true"` or `"false"`.

#### Example: Idiomatic Usage

```lymar
var txt = format_bool(true);
```

---

### `pad_left` <a id="pad_left"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pad_left(value: str, length_val: int, fill_char: str): str
```

Pads the beginning of a string with a fill character until reaching the desired target length.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Source text. |
| `length_val` | Desired minimum length. |
| `fill_char` | Character string used for padding. |

#### Returns

Padded string or original if already long enough.

#### Example: Idiomatic Usage

```lymar
var padded = pad_left("42", 5, "0"); // "00042"
```

---

### `pad_right` <a id="pad_right"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pad_right(value: str, length_val: int, fill_char: str): str
```

Pads the end of a string with a fill character until reaching the desired target length.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Source text. |
| `length_val` | Desired minimum length. |
| `fill_char` | Character string used for padding. |

#### Returns

Padded string or original if already long enough.

#### Example: Idiomatic Usage

```lymar
var padded = pad_right("hello", 8, "."); // "hello..."
```

---

### `center` <a id="center"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn center(value: str, length_val: int, fill_char: str): str
```

Centers text by evenly distributing padding characters on both sides.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Text to center. |
| `length_val` | Total target width. |
| `fill_char` | Character string used for padding. |

#### Returns

Centered text string.

#### Example: Idiomatic Usage

```lymar
var centered = center("title", 11, "="); // "===title==="
```

---

### `truncate` <a id="truncate"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn truncate(value: str, length_val: int, ellipsis: bool): str
```

Truncates a string to maximum length, optionally appending an ellipsis (`"..."`).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Source text. |
| `length_val` | Maximum character length allowed. |
| `ellipsis` | If true and length > 3, replaces trailing characters with `"..."`. |

#### Returns

Truncated string.

#### Example: Idiomatic Usage

```lymar
var short_text = truncate("long descriptive title", 10, true);
```

---

### `title_case` <a id="title_case"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn title_case(value: str): str
```

Converts text into Title Case capitalization.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Input text string. |

#### Returns

Title-cased string.

#### Example: Idiomatic Usage

```lymar
var res = title_case("hello world"); // "Hello World"
```

---

### `snake_case` <a id="snake_case"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn snake_case(value: str): str
```

Converts text into snake_case by lowercasing and replacing whitespace with underscores.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Input text string. |

#### Returns

Lowercase snake_case identifier string.

#### Example: Idiomatic Usage

```lymar
var id = snake_case("User First Name"); // "user_first_name"
```

---

### `camel_case` <a id="camel_case"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn camel_case(value: str): str
```

Converts text into camelCase identifier format.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Input text string. |

#### Returns

camelCase identifier string.

#### Example: Idiomatic Usage

```lymar
var id = camel_case("user first name"); // "userFirstName"
```

---

### `kebab_case` <a id="kebab_case"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn kebab_case(value: str): str
```

Converts text into kebab-case identifier format using hyphens.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Input text string. |

#### Returns

kebab-case string.

#### Example: Idiomatic Usage

```lymar
var id = kebab_case("user profile pic"); // "user-profile-pic"
```

---

### `pascal_case` <a id="pascal_case"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn pascal_case(value: str): str
```

Converts text into PascalCase identifier format.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `value` | Input text string. |

#### Returns

PascalCase string.

#### Example: Idiomatic Usage

```lymar
var id = pascal_case("user account state"); // "UserAccountState"
```

---


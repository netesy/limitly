# API Documentation: `index.lm`

## Overview

std/regex/index.lm
Clean Standard Library Regex Entrypoint Module

## Symbols

- **Function**: [`first_match`](#first_match)
- **Function**: [`all_matches`](#all_matches)
- **Function**: [`is_match`](#is_match)
- **Function**: [`replace`](#replace)
- **Function**: [`replace_all`](#replace_all)
- **Function**: [`split`](#split)

---

### `first_match` <a id="first_match"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn first_match(pattern: str, text: str): regex.Match
```

Finds the first match of a regular expression pattern within target text.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `pattern` | Regular expression pattern string. |
| `text` | Subject string to search. |

#### Returns

`Match` result object containing match status, offset, and captured substring.

#### Example: Idiomatic Usage

```lymar
var m = regex.first_match("[0-9]+", "id: 42");
if (m.is_valid()) {
    print("Found match: {m.value}\n");
}
```

---

### `all_matches` <a id="all_matches"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn all_matches(pattern: str, text: str): list
```

Finds all occurrences of a regular expression pattern within target text.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `pattern` | Regular expression pattern string. |
| `text` | Subject string to search. |

#### Returns

List of `Match` objects for every matching substring.

---

### `is_match` <a id="is_match"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_match(pattern: str, text: str): bool
```

Tests whether a regular expression matches any portion of the input string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `pattern` | Regular expression pattern string. |
| `text` | Subject string to evaluate. |

#### Returns

`true` if pattern matches anywhere in text, `false` otherwise.

---

### `replace` <a id="replace"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn replace(pattern: str, text: str, replacement: str): str
```

Replaces the first match of pattern with a replacement string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `pattern` | Pattern to search for. |
| `text` | Source string to perform substitution on. |
| `replacement` | Replacement string. |

#### Returns

Modified string with first match replaced.

---

### `replace_all` <a id="replace_all"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn replace_all(pattern: str, text: str, replacement: str): str
```

Replaces all matches of pattern with a replacement string.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `pattern` | Pattern to search for. |
| `text` | Source string to perform substitution on. |
| `replacement` | Replacement string. |

#### Returns

Modified string with all matches replaced.

---

### `split` <a id="split"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn split(pattern: str, text: str): list
```

Splits input text by regular expression delimiter.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `pattern` | Regular expression delimiter. |
| `text` | String to split. |

#### Returns

List of string tokens.

---


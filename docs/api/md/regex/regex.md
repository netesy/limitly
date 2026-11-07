# API Documentation: `regex.lm`

## Overview

std/regex/regex.lm
Clean Standard Library Regex Module with rich Match objects and POSIX regular expressions

## Symbols

- **Frame**: [`Match`](#Match)
- **Frame**: [`Regex`](#Regex)
- **Frame**: [`RegexPatterns`](#RegexPatterns)

---

### `Match` <a id="Match"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Match
```

Represents a single pattern match result within target text.

#### Members

- `var pub is_matched: bool` *(field)*
- `var pub value: str` *(field)*
- `var pub start: int` *(field)*
- `var pub end: int` *(field)*
- `var pub index: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn to_string(): str` *(method)*
- `pub fn length(): int` *(method)*
- `pub fn is_valid(): bool` *(method)*

---

### `Regex` <a id="Regex"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Regex
```

Compiled POSIX regular expression evaluator.

#### Members

- `var pub flags: int` *(field)*
- `var pub pattern: str` *(field)*
- `var pub preg: any` *(field)*
- `pub init(pattern: str)` *(constructor)*
- `pub fn is_match(text: str): bool` *(method)*
- `pub fn matches(text: str): bool` *(method)*
- `pub fn find_match(text: str): Match` *(method)*
- `pub fn find_matches(text: str): list` *(method)*
- `pub fn find_first_match(text: str): any` *(method)*
- `pub fn find_all_matches(text: str): list` *(method)*
- `pub fn replace(text: str, replacement: str): str` *(method)*
- `pub fn replace_all(text: str, replacement: str): str` *(method)*
- `pub fn split(text: str): list` *(method)*
- `pub fn is_valid(): bool` *(method)*
- `pub fn to_string(): str` *(method)*
- `pub fn find_match_start(text: str, start_pos: int): int` *(method)*
- `fn is_balanced_pattern(): bool` *(method)*

---

### `RegexPatterns` <a id="RegexPatterns"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame RegexPatterns
```

Predefined common regular expression patterns.

#### Members

- `pub init()` *(constructor)*
- `pub fn email(): Regex` *(method)*
- `pub fn url(): Regex` *(method)*
- `pub fn phone(): Regex` *(method)*

---


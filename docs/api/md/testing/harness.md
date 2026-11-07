# API Documentation: `harness.lm`

## Overview

std/testing/harness.lm

A counting test harness.

Lymar does not retain module-level state (a var written inside a function is
not visible to the next call), so the counters live in a Testing frame
instance that the caller creates and owns - the same explicit-ownership style
std.resource uses for handles. Frame field updates do persist across method
calls on the same instance, which is what makes the tally reliable.

## Symbols

- **Frame**: [`Testing`](#Testing)
- **Function**: [`verify`](#verify)
- **Function**: [`assert_true`](#assert_true)
- **Function**: [`assert_eq`](#assert_eq)
- **Function**: [`assert_ne`](#assert_ne)
- **Function**: [`run_test`](#run_test)

---

### `Testing` <a id="Testing"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Testing
```

#### Members

- `var pub passed: int` *(field)*
- `var pub failed: int` *(field)*
- `var pub section_name: str` *(field)*
- `var pub label: str` *(field)*
- `pub init()` *(constructor)*
- `pub fn reset(name: str)` *(method)*
- `pub fn section(name: str)` *(method)*
- `pub fn check(condition: bool, message: str): bool` *(method)*
- `pub fn check_true(condition: bool, message: str): bool` *(method)*
- `pub fn check_false(condition: bool, message: str): bool` *(method)*
- `pub fn check_int(actual: int, expected: int, message: str): bool` *(method)*
- `pub fn check_str(actual: str, expected: str, message: str): bool` *(method)*
- `pub fn check_equal(actual: any, expected: any, message: str): bool` *(method)*
- `pub fn fail(message: str): bool` *(method)*
- `pub fn count_passed(): int` *(method)*
- `pub fn count_failed(): int` *(method)*
- `pub fn total(): int` *(method)*
- `pub fn all_passed(): bool` *(method)*
- `pub fn report(): bool` *(method)*
- `pub fn finish(): nil` *(method)*

---

### `verify` <a id="verify"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn verify(condition: bool, message: str): bool
```

One-shot check with no tally: prints a line and returns the condition.

---

### `assert_true` <a id="assert_true"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn assert_true(condition: bool, message: str = ...): nil
```

Abort-on-first-failure helpers. These stop the process on the first failed
check, so they suit small scripts; prefer a Testing frame when you want a
full tally. Strings are interpolated rather than concatenated, because Lymar
does not support the + operator on strings.

---

### `assert_eq` <a id="assert_eq"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn assert_eq(actual, expected, message: str = ...): nil
```

---

### `assert_ne` <a id="assert_ne"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn assert_ne(actual, expected, message: str = ...): nil
```

---

### `run_test` <a id="run_test"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn run_test(name: str, test_func: function): bool
```

Run one callable check and report its result without ending the process.

---


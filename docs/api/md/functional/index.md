# API Documentation: `index.lm`

## Overview

std/functional/index.lm
Public entrypoint and facade for std.functional. Functional programming combinators and higher-order helpers.

## Symbols

- **Frame**: [`Function1`](#Function1)
- **Frame**: [`Predicate`](#Predicate)
- **Function**: [`compose_int`](#compose_int)
- **Function**: [`compose_str`](#compose_str)
- **Function**: [`pipe_int`](#pipe_int)
- **Function**: [`pipe_str`](#pipe_str)
- **Function**: [`curry_add`](#curry_add)
- **Function**: [`curry_multiply`](#curry_multiply)
- **Function**: [`curry_string_append`](#curry_string_append)
- **Function**: [`curry_string_prepend`](#curry_string_prepend)
- **Function**: [`partial_apply_binary`](#partial_apply_binary)
- **Function**: [`partial_apply_ternary`](#partial_apply_ternary)
- **Function**: [`compose_three_int`](#compose_three_int)
- **Function**: [`compose_three_str`](#compose_three_str)
- **Function**: [`pipe_three_int`](#pipe_three_int)
- **Function**: [`always_true`](#always_true)
- **Function**: [`always_false`](#always_false)
- **Function**: [`equals`](#equals)
- **Function**: [`not_equals`](#not_equals)
- **Function**: [`greater_than`](#greater_than)
- **Function**: [`less_than`](#less_than)
- **Function**: [`greater_than_or_equal`](#greater_than_or_equal)
- **Function**: [`less_than_or_equal`](#less_than_or_equal)
- **Function**: [`is_even`](#is_even)
- **Function**: [`is_odd`](#is_odd)
- **Function**: [`is_positive`](#is_positive)
- **Function**: [`is_negative`](#is_negative)
- **Function**: [`is_zero`](#is_zero)
- **Function**: [`not_fn`](#not_fn)
- **Function**: [`and_fn`](#and_fn)
- **Function**: [`or_fn`](#or_fn)
- **Function**: [`xor`](#xor)
- **Function**: [`memoize_int`](#memoize_int)
- **Function**: [`memoize_str`](#memoize_str)
- **Function**: [`memoize_bool`](#memoize_bool)
- **Function**: [`identity`](#identity)
- **Function**: [`identity_str`](#identity_str)
- **Function**: [`constant`](#constant)
- **Function**: [`constant_str`](#constant_str)
- **Function**: [`flip`](#flip)
- **Function**: [`apply_n_times`](#apply_n_times)
- **Function**: [`apply_until`](#apply_until)
- **Function**: [`apply_while`](#apply_while)
- **Function**: [`add_n`](#add_n)
- **Function**: [`multiply_n`](#multiply_n)
- **Function**: [`power_n`](#power_n)
- **Function**: [`wrap_with`](#wrap_with)
- **Function**: [`prepend`](#prepend)
- **Function**: [`append`](#append)
- **Function**: [`repeat`](#repeat)

---

### `Function1` <a id="Function1"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Function1
```

#### Members

- `var fn_ref: function` *(field)*
- `pub init(fn_ref: function)` *(constructor)*
- `pub fn call(value: T): T` *(method)*
- `pub fn compose(other: Function1): Function1` *(method)*
- `pub fn and_then(other: Function1): Function1` *(method)*
- `pub fn memoize(): Function1` *(method)*
- `pub fn repeat(n: int): Function1` *(method)*

---

### `Predicate` <a id="Predicate"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Predicate
```

#### Members

- `var fn_ref: function` *(field)*
- `pub init(fn_ref: function)` *(constructor)*
- `pub fn call(value: T): bool` *(method)*
- `pub fn negate(): Predicate` *(method)*
- `pub fn and_fn(other: Predicate): Predicate` *(method)*
- `pub fn or_fn(other: Predicate): Predicate` *(method)*

---

### `compose_int` <a id="compose_int"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn compose_int(f: function, g: function): function
```

Higher-order functions

---

### `compose_str` <a id="compose_str"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn compose_str(f: function, g: function): function
```

---

### `pipe_int` <a id="pipe_int"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn pipe_int(f: function, g: function): function
```

---

### `pipe_str` <a id="pipe_str"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn pipe_str(f: function, g: function): function
```

---

### `curry_add` <a id="curry_add"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn curry_add(a: int): function
```

Currying functions

---

### `curry_multiply` <a id="curry_multiply"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn curry_multiply(a: int): function
```

---

### `curry_string_append` <a id="curry_string_append"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn curry_string_append(prefix: str): function
```

---

### `curry_string_prepend` <a id="curry_string_prepend"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn curry_string_prepend(suffix: str): function
```

---

### `partial_apply_binary` <a id="partial_apply_binary"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn partial_apply_binary(fn_ref: function, first_arg: int): function
```

Partial application

---

### `partial_apply_ternary` <a id="partial_apply_ternary"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn partial_apply_ternary(fn_ref: function, first_arg: int): function
```

---

### `compose_three_int` <a id="compose_three_int"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn compose_three_int(f: function, g: function, h: function): function
```

Function composition utilities

---

### `compose_three_str` <a id="compose_three_str"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn compose_three_str(f: function, g: function, h: function): function
```

---

### `pipe_three_int` <a id="pipe_three_int"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn pipe_three_int(f: function, g: function, h: function): function
```

---

### `always_true` <a id="always_true"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn always_true(x: int): bool
```

Predicate functions

---

### `always_false` <a id="always_false"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn always_false(x: int): bool
```

---

### `equals` <a id="equals"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn equals(value: int): function
```

---

### `not_equals` <a id="not_equals"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn not_equals(value: int): function
```

---

### `greater_than` <a id="greater_than"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn greater_than(value: int): function
```

---

### `less_than` <a id="less_than"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn less_than(value: int): function
```

---

### `greater_than_or_equal` <a id="greater_than_or_equal"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn greater_than_or_equal(value: int): function
```

---

### `less_than_or_equal` <a id="less_than_or_equal"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn less_than_or_equal(value: int): function
```

---

### `is_even` <a id="is_even"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_even(x: int): bool
```

---

### `is_odd` <a id="is_odd"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_odd(x: int): bool
```

---

### `is_positive` <a id="is_positive"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_positive(x: int): bool
```

---

### `is_negative` <a id="is_negative"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_negative(x: int): bool
```

---

### `is_zero` <a id="is_zero"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_zero(x: int): bool
```

---

### `not_fn` <a id="not_fn"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn not_fn(predicate: function): function
```

Predicate combinators

---

### `and_fn` <a id="and_fn"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn and_fn(pred1: function, pred2: function): function
```

---

### `or_fn` <a id="or_fn"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn or_fn(pred1: function, pred2: function): function
```

---

### `xor` <a id="xor"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn xor(pred1: function, pred2: function): function
```

---

### `memoize_int` <a id="memoize_int"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn memoize_int(fn_ref: function): function
```

Memoization utilities

---

### `memoize_str` <a id="memoize_str"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn memoize_str(fn_ref: function): function
```

---

### `memoize_bool` <a id="memoize_bool"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn memoize_bool(fn_ref: function): function
```

---

### `identity` <a id="identity"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn identity(x: int): int
```

Function utilities

---

### `identity_str` <a id="identity_str"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn identity_str(x: str): str
```

---

### `constant` <a id="constant"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn constant(value: int): function
```

---

### `constant_str` <a id="constant_str"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn constant_str(value: str): function
```

---

### `flip` <a id="flip"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn flip(fn_ref: function): function
```

---

### `apply_n_times` <a id="apply_n_times"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn apply_n_times(fn_ref: function, n: int, initial: int): int
```

Function application utilities

---

### `apply_until` <a id="apply_until"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn apply_until(fn_ref: function, predicate: function, initial: int): int
```

---

### `apply_while` <a id="apply_while"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn apply_while(fn_ref: function, predicate: function, initial: int): int
```

---

### `add_n` <a id="add_n"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn add_n(n: int): function
```

Function building utilities

---

### `multiply_n` <a id="multiply_n"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn multiply_n(n: int): function
```

---

### `power_n` <a id="power_n"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn power_n(n: int): function
```

---

### `wrap_with` <a id="wrap_with"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn wrap_with(wrapper: str): function
```

String function utilities

---

### `prepend` <a id="prepend"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn prepend(prefix: str): function
```

---

### `append` <a id="append"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn append(suffix: str): function
```

---

### `repeat` <a id="repeat"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn repeat(times: int): function
```

---


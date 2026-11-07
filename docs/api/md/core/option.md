# API Documentation: `option.lm`

## Overview

Standard Library Core Option — a staged frame template (roadmaps.md item 1b).

`Option(T: type)` is a template, not a frame: each type argument mints a real,
nominal frame (`Option(int)`, `Option(str)`, ...) on first request. Use it in a
type position and construct through that annotation:

  var found: Option(int) = Option(true, 42);
  var empty: Option(int) = Option(false, nil);

The bare template name is not constructible on its own — `Option(true, 42)`
without a type context is a compile error, by design: an untyped Option would
collapse back onto `any`.

Absence without combinators is still just `T?` / `T | nil`; reach for Option
when you want map/filter/unwrap_or chaining over a typed value.

## Symbols

- **Frame**: [`Option`](#Option)

---

### `Option` <a id="Option"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Option
```

Staged optional wrapper template representing an optional value.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Use `T?` for plain presence/absence; reach for `Option(T)` when functional combinators (`map`, `filter`, `unwrap_or`) are desired.

#### Example: Idiomatic Usage

```lymar
var opt: Option(int) = Option(true, 42);
if (opt.is_some()) {
    print("Value is: {opt.unwrap()}");
}
```

#### Members

- `var pub present: bool` *(field)*
- `var pub value: union` *(field)*
- `pub init(p: bool, v: union)` *(constructor)*
- `pub fn is_some(): bool` *(method)*
- `pub fn is_none(): bool` *(method)*
- `pub fn unwrap(): T` *(method)*
- `pub fn unwrap_or(default_value: T): T` *(method)*
- `pub fn map(f: function): Option` *(method)*
- `pub fn filter(predicate: function): Option` *(method)*

---


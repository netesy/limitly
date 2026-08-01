# Limit Language Specification (v0.2)

This document provides a formal specification of the Limit programming language syntax and semantics.

## 1. Lexical Structure

### 1.1 Keywords

```
and, as, break, concurrent, continue, comptime, contract, elif, else, enum,
err, false, fn, for, frame, from, hide, if, import, in, interface, iter,
match, module, nil, not, ok, or, parallel, prot, pub, return, self, show,
static, super, task, trait, true, type, unsafe, val, var, const, where,
while, worker
```

**Removed keywords** (now regular identifiers or deleted):
- `this` — use `self` instead.
- `class` — use `frame`.
- `public`, `protected`, `private` — use `pub`/`prot`; declarations are **private by default** (no explicit `private` keyword).
- `open`, `property`, `cache`, `sleep` — removed; `sleep` is now a regular builtin function identifier.
- `loop` — removed; use `for`, `while`, or `iter`.
- `data` — removed; traits cover the same ground.
- `@annotation` — removed; use `pub`/`prot` directly.

`channel` and `atomic` are reserved as type names but are also usable as builtin function identifiers (e.g. `channel()`).

### 1.2 Literals
- **Integer**: `[0-9]+` (e.g., `42`); hex `0x[0-9a-fA-F]+` (e.g., `0xFF`)
- **Float**: `[0-9]+\.[0-9]+` (e.g., `3.14`)
- **Scientific**: `[0-9]+e[+-]?[0-9]+` (e.g., `1e9`)
- **String**: `"[^"]*"` or `'[^']*'` (supports interpolation via `{expression}`)
- **Boolean**: `true`, `false`
- **Nil**: `nil` (represents a null/empty state)

### 1.3 Operators
- **Arithmetic**: `+`, `-`, `*`, `/`, `%`, `**` (power)
- **Comparison**: `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Logical**: `and`, `or`, `not`, `!` (not)
- **Bitwise**: `&` (and), `|` (or), `^` (xor), `~` (not), `<<` (left shift), `>>` (right shift)
- **Assignment**: `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `|=`, `^=`, `<<=`, `>>=`
- **Access**: `.` (member), `[]` (index), `->` (arrow), `::` (namespace)
- **Optional**: `?` (fallible/optional), `?:` (elvis — coalesce), `?.` (safe member access)
- **Range**: `..` (range), `...` (ellipsis/rest)

### 1.4 Operator Precedence (tightest to loosest)

1. Postfix: `[]`, `()`, `.`, `?.`, `::`
2. Unary: `!`, `not`, `-`, `~`
3. Power: `**` (right-associative; binds tighter than unary `+`/`-`)
4. Multiplicative: `*`, `/`, `%`
5. Additive: `+`, `-`
6. Comparison: `<`, `>`, `<=`, `>=`, `..` (range), `as`
7. Bitwise shift: `<<`, `>>`
8. Bitwise AND: `&`
9. Bitwise XOR: `^`
10. Bitwise OR: `|`
11. Equality: `==`, `!=`
12. Logical AND: `and`
13. Logical OR: `or`
14. Assignment: `=`, `+=`, `-=`, etc.

So `flags & READ == READ` parses as `(flags & READ) == READ`, and `flags << 1 == 2` parses as `(flags << 1) == 2`. Exponentiation remains right-associative and binds tighter than unary plus/minus: `-2 ** 2` parses as `-(2 ** 2)`, while `2 ** 3 ** 2` parses as `2 ** (3 ** 2)`.

## 2. Type System

### 2.1 Primitive Types
- `int`: Signed integer (platform-dependent size, usually 64-bit)
- `uint`: Unsigned integer
- `float`: Floating-point number (64-bit)
- `bool`: Boolean value (`true` or `false`)
- `str`: UTF-8 string
- `any`: Top type (can hold any value)
- `nil`: Type of the `nil` literal (also used as the void return type — `void` is not a keyword)

### 2.2 Fixed-Width Types
- Integers: `i8`, `i16`, `i32`, `i64`, `i128`
- Unsigned: `u8`, `u16`, `u32`, `u64`, `u128`
- Floats: `f32`, `f64`
- Decimals: `d2`, `d4`, `d6`, `decimal` (alias for `d4`). Stored as signed 64-bit integers with fixed scaling.

#### 2.2.1 Decimal Rules
- **Arithmetic**: Operations between decimals promote to the widest scale (e.g., `d2 + d4 -> d4`). Mixed arithmetic between decimals and floats/integers is disallowed.
- **Comparisons**: Require exact scale matches. Comparing `d2` to `d4` is a compile-time error.
- **Modulo**: Requires exact scale matches.
- **Casting**: Narrowing casts (e.g., `d4 as d2`) trigger mandatory runtime traps if precision is lost.

### 2.3 Composite Types
- **List**: `[Type]` — Dynamic array of elements.
- **Dictionary**: `{KeyType: ValueType}` — Key-value map.
- **Tuple**: `(Type1, Type2, ...)` — Fixed-size collection of heterogeneous types.
- **Union**: `Type1 | Type2` — Value that is either Type1 or Type2.
- **Option/Result (Fallible)**: `Type?` — Shorthand for a value that might be absent or an error.
- **Function**: `fn(ParamTypes): ReturnType` — First-class function type.
- **Channel**: `channel` — Communication primitive for structured concurrency.
- **Atomic**: `atomic` — Atomic wrapper for thread-safe access.

## 3. Declarations

### 3.1 Variables

```
var name[: Type] = expression;     // mutable
const name[: Type] = expression;   // immutable (requires initializer)
val name[: Type] = expression;     // alias for const
```

Variables and functions are **private by default** when neither `pub` nor `prot` is specified — there is no explicit `private` keyword.

### 3.2 Functions

```
fn name([params])[: ReturnType] { body }
```
- Supports optional parameters: `name: Type = default`
- Function-level modifiers (parallel to visibility, not interchangeable): `static`, `abstract`, `final`.

### 3.3 Frames (Objects)

Frames are the primary unit of data encapsulation and behavior.

```limit
[modifier] frame Name [: Traits] {
    [visibility] [const|val|var] fieldName: Type [= default];
    [visibility] [modifier] fn methodName([params])[: ReturnType] { body }
    [visibility] init([params]) { body }
    [visibility] deinit() { body }
}
```

#### 3.3.1 Modifiers
- `abstract`: Frame cannot be instantiated directly. May contain abstract methods.
- `final`: Frame cannot be inherited from.
- `static` (method-level): Method does not receive `self`; callable on the frame type itself.
- `abstract` (method-level): Method has no body; must be overridden in subframes.
- `final` (method-level): Method cannot be overridden in subframes.

(The `data` modifier was removed — traits cover the same ground.)

#### 3.3.2 Visibility
- **private** (default): Accessible only within the frame/module. No keyword — declarations are private when neither `pub` nor `prot` is specified.
- `prot`: Accessible within the frame and subframes.
- `pub`: Accessible from any scope.

## 4. Control Flow

### 4.1 Match Statement

Pattern matching for literals, types, and structures. Supports or-patterns via `|`.

```limit
match (expression) {
    pattern [where guard] => statement | { block },
    pattern1 | pattern2 | pattern3 => statement,  // or-pattern
    ...
}
```

### 4.2 Iter Loop

Used for ranges and collection iteration.

```
iter (name in iterable) { body }              // list, range, channel
iter (key in dict) { body }                   // dict (key only)
iter (key, value in dict) { body }            // dict (key and value)
```

### 4.3 Other Loops
- `for (init; condition; step) { body }` — C-style for loop.
- `while (condition) { body }` — while loop.
- `break` / `continue` — loop control (must be inside a loop).

(The `loop` keyword was removed — use `while (true)` for infinite loops.)

### 4.4 Error Handling
- `?`: Propagation operator. If expression returns an error, return error from current function.
- `? else { ... }`: Inline error handling / default value.
- `ok(value)`: Construct a success result.
- `err(type)`: Construct an error result.

## 5. Modules and Imports

### 5.1 Import Syntax
- `import module_name;`
- `import module_name as alias;`
- `import module_name show symbol1, symbol2;`
- `import module_name hide symbol3;`
- `from module_name import symbol;` (Python-style)

### 5.2 Module Blocks

Explicitly group declarations with visibility control. Members use `pub`/`prot` directly (no `@annotation`):

```limit
module name {
    pub fn shared() { ... }
    prot fn internal_helper() { ... }
    fn private_helper() { ... }   // implicitly private
}
```

## 6. Concurrency

### 6.1 Structured Concurrency

Concurrency is bound to the lifetime of the block.
- `parallel(...) { ... }`: CPU-bound tasks.
- `concurrent(...) { ... }`: I/O-bound tasks.

### 6.2 Tasks and Workers
- `task([name in] iterable) { ... }`: Spawn a unit of work. The `name in` part is optional; `task(iterable) { ... }` is valid.
- `worker([param in] channel) { ... }`: Process elements from a channel. The `param in` part is optional; `worker(channel) { ... }` is valid.

### 6.3 Channels
- `channel()`: Create a new channel (builtin function).
- `.send(value)`: Blocking send.
- `.receive(): T?`: Blocking receive.
- `.poll(): T?`: Non-blocking receive.
- `.offer(value): bool`: Non-blocking send.

## 7. Self

`self` is the canonical keyword for the current instance inside a frame method. `this` is no longer a keyword.

```limit
frame Counter {
    pub var count: int;
    pub fn increment(): nil {
        self.count = self.count + 1;
    }
}
```

## Standard-library syntax conformance

The compiler parser is the source of truth for Limit syntax. Standard-library modules use supported statement-level control flow (`if (...) { ... } else { ... }`), `self` for frame receivers, concrete collection shorthand types such as `[int]` and `[any]`, and function types such as `fn(any): any`. Expression-level conditional forms and `this` are not part of the standard-library style.

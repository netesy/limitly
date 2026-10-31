# Lymar Language Specification (v0.2)

This document provides a formal specification of the Lymar programming language syntax and semantics.

## 1. Lexical Structure

### 1.1 Keywords

```
and, as, break, concurrent, continue, staged, contract, elif, else, enum,
err, false, fn, for, frame, from, hide, if, import, in, iter,
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
- `abstract`, `final`, `implements`, `interface` — removed; frame inheritance is eliminated in favor of pure composition using traits (`:`), mixins (`mixin`), and embedding (`embed`).
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
- **Optional**: `?` (fallible/optional), `?.` (safe member access)
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
- `int`: Signed 64-bit integer (`i64` range). The VM stores small values as an
  unboxed 61-bit immediate and transparently heap-promotes any value outside that
  range, so the observable range is the full signed 64-bit space. This is a storage
  detail invisible to the language; see [abi.md](abi.md).
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
- Function-level modifiers (parallel to visibility, not interchangeable): `static`.

A function body reads module-level variables, but a store to one from inside a function does not land: the write is silently dropped and the global keeps its previous value, on every path. Only entry-scope code may assign a module-level variable. Pass the value in and return it, or hold the state in a frame.

### 3.3 Frames (Objects)

Frames are the primary unit of data encapsulation and behavior.

```lymar
[modifier] frame Name [: Traits] {
    [visibility] [const|val|var] fieldName: Type [= default];
    [visibility] [modifier] fn methodName([params])[: ReturnType] { body }
    [visibility] init([params]) { body }
    [visibility] deinit() { body }
}
```

#### 3.3.1 Modifiers
- `static` (method-level): Method does not receive `self`; callable on the frame type itself.

(The `data` modifier was removed — traits cover the same ground.)

#### 3.3.2 Visibility
- **private** (default): Accessible only within the frame/module. No keyword — declarations are private when neither `pub` nor `prot` is specified.
- `prot`: Accessible within the frame and subframes.
- `pub`: Accessible from any scope.

### 3.4 Composition: Traits, Mixins, Embedding

Lymar has **no inheritance between frames**. `frame A : B` where `B` is a frame is a
compile error. The colon `:` is reserved exclusively for trait conformance. The three
composition mechanisms are disjoint — each answers a different question.

| Mechanism | Question it answers | Runtime cost | Dispatch |
|---|---|---|---|
| `trait` | *What behaviour can this call?* | zero (no storage) | dynamic, by trait |
| `mixin` | *Which fields does this share?* | zero (flattened) | static, always concrete |
| `embed` | *Which component's fields and methods does this host own?* | zero (flattened) | static, always concrete |

#### 3.4.1 Traits — behavioural contracts

```lymar
trait Reader {
    fn read(buffer: str, size: int): int;      // requirement: must be implemented
    fn name(): str { return "reader"; }        // default implementation
}

frame File: Reader {
    pub fn read(buffer: str, size: int): int { ... }
}
```

- A trait body contains **methods only**. A field in a trait is a parse error
  (`Expected method declaration in trait.`) — shared state belongs in a mixin.
- `fn sig;` (semicolon) is a requirement. `fn sig { ... }` is a **default
  implementation**: the conforming frame need not redeclare it and may call it
  directly.
- Conformance is declared with `:` and is **strictly checked**: the member must match
  the requirement's name, arity, parameter types and return type. A member that
  merely shares the name does not satisfy the contract. `any` is accepted on either
  side, and a refined type compares equal to its base type.
- Traits may require other traits: `trait Cached: Reader, Disposable { ... }`. Every
  requirement in the graph is verified.
- Traits are public by default; `pub trait` is an error.
- Use traits when a caller needs to accept *any* frame that can do something.

#### 3.4.2 Mixins — shared data fields

```lymar
mixin Identifiable {
    pub id: int;
    pub fn set_id(value: int) { self.id = value; }
}

frame User {
    mixin Identifiable;          // fields and methods are injected, flattened
    pub name: str;
}

var u = User();
u.id = 7;                        // no `u.identifiable` qualifier — there is no sub-object
u.set_id(8);
```

- A mixin is a reusable block of **state**, primarily fields. Methods are permitted so
  a mixin can expose accessors over its own fields, but a mixin is not a contract:
  it never dispatches dynamically.
- Members are copied into the host frame at compile time. A mixin is not a value and
  cannot be instantiated, stored, or passed.
- An unknown mixin name is an error at the including frame.

#### 3.4.3 Embedding — flattened component inlining

```lymar
frame Engine {
    pub rpm: int;
    pub fn start(): str { self.rpm = 1000; return "started"; }
}

frame Car {
    embed Engine;                // anonymous, compile-time flattening
    pub fn drive(): str { self.start(); return "{self.rpm}"; }
}
```

- `embed Type;` inlines another frame's fields into the host and **promotes its
  methods** onto the host. There is no wrapper object, no indirection and no vtable:
  the promoted field is the host's own storage, so `car.rpm` and the `rpm` that
  `Engine.start()` writes are the same slot.
- Embedding is **anonymous**. `embed Engine;` creates no `self.engine` accessor — if
  you need to name the component, declare a field (`pub engine: Engine;`) instead.
- `embed` takes **no visibility modifier**. It is a statement, not a member declaration:
  write `embed Engine;`, never `pub embed Engine;` (a `pub`/`prot` prefix carries no
  meaning there and is discarded). Each flattened field keeps the visibility it declared
  inside the component; promoted methods keep theirs too.
- Name collisions are resolved first-wins: a member the host already declares is never
  overwritten by a promoted one.
- `embed` accepts a mixin name as well as a frame name; an unknown name is an error.
- Promoted members count as real members, so an embedded component's method can
  satisfy a trait requirement declared on the host.
- **`deinit` is not promoted and is not synthesised.** Because flattening leaves no
  embedded sub-object, the embedded frame's `deinit()` does not run when the host is
  destroyed. Forward it explicitly from the host if cleanup is required.

## 4. Control Flow

### 4.1 Match Statement

Pattern matching for literals, types, and structures. Supports or-patterns via `|`.

```lymar
match (expression) {
    pattern [where guard] => statement | { block },
    pattern1 | pattern2 | pattern3 => statement,  // or-pattern
    ...
}
```

### 4.2 Iter Loop

Used for ranges and collection iteration.

```
iter (name in iterable) { body }              // list, range, channel, string
iter (key, value in dict) { body }            // dict
```

Two facts that bite in practice:

- **Always use the two-variable form for dictionaries.** `iter (key in dict)`
  type-checks the loop variable as the key, but at run time the variable holds
  the `(key, value)` pair, so printing it yields `(a, 1)` instead of `a`. The
  two-variable form is the only one that binds real keys and values.
- **A string iterates as code points**, not characters: `iter (cp in "AB")`
  yields `65`, `66`. Slice with `substring` when you want characters.

`iter` over a dictionary must not appear inside a frame method - it aborts the
compiler with an access violation. Iterate in a free function (or use an index
`while` loop over `iter`'s result) and call that from the method.

`in` is a keyword but **not an expression operator**: it only appears in the
`iter`/`for` clauses. For dictionary containment, read the key and compare
against `nil`, since a missing key reads back as `nil`:

```
if (states[key] != nil) { ... }
```

### 4.3 Other Loops
- `for (init; condition; step) { body }` — C-style for loop.
- `while (condition) { body }` — while loop.
- `break` / `continue` — loop control (must be inside a loop).

(The `loop` keyword was removed — use `while (true)` for infinite loops.)

### 4.4 Error Handling
- `?`: Propagation operator. If expression returns an error, return error from current function.
- `? else { ... }`: Inline error handling. The fallback block must end in `return <value>;` — its value comes through. A bare trailing expression (`? else { 0 }`) compiles and runs but is discarded, silently binding `nil` where the declared type was `int`.
- `ok(value)`: Construct a success result.
- `err(type)`: Construct an error result.

A function declared `T?Error` must produce that error from its own body: propagating a callee's error with `?` is currently rejected with `Function 'f' declares error type 'Error' but function body cannot produce this error type`, so intermediate layers unwrap with `? else { return ...; }` or `match` and re-throw explicitly.

`T?` does not model absence, it models failure. `ok(5)` matches `val x`; a fallible holding `nil` also matches `val x` and binds `nil`, because `nil` is a payload, not a missing value — a bare `return nil` is therefore a success carrying nil, and failures must use `err()`. Because a payload-less `err()` also matches a `nil` pattern, `err e` has to be written before `nil` in a `match`, or the nil arm swallows real errors. Test presence with equality (`v == nil`) rather than a `nil` arm.

## 5. Modules and Imports

### 5.1 Import Syntax
- `import module_name;`
- `import module_name as alias;`
- `import module_name show symbol1, symbol2;`
- `import module_name hide symbol3;`
- `import module_name { symbol1, symbol2 };` (brace-select sugar for `show`)
- `from module_name import symbol;` (Python-style)
- `import "c:<header>" [from "<lib>"] [as <ns>] [ { idents } | show idents ];` — declarative
 C header binding, generates the FFI module at compile time (see [FFI](ffi.md#declarative-c-imports-recommended)).

### 5.2 Module Blocks

Explicitly group declarations with visibility control. Members use `pub`/`prot` directly (no `@annotation`):

```lymar
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

```lymar
frame Counter {
    pub var count: int;
    pub fn increment(): nil {
        self.count = self.count + 1;
    }
}
```

## Standard-library syntax conformance

The compiler parser is the source of truth for Lymar syntax. Standard-library modules use supported statement-level control flow (`if (...) { ... } else { ... }`), `self` for frame receivers, concrete collection shorthand types such as `[int]` and `[any]`, and function types such as `fn(any): any`. Expression-level conditional forms and `this` are not part of the standard-library style.

# Lymar Language - AI Agent Guidelines

This document provides essential guidelines for AI agents generating code for the Lymar language. It outlines the valid syntax, supported language constructs, type system rules, module/import behavior, and error handling style that are actually implemented and supported by the Lymar compiler.

---

## **DO NOT USE - Unsupported Features**

### **Reserved Keywords as Identifiers**
- [ ] **DO NOT use reserved keywords as variable names, function names, or method names**. All language keywords (e.g., `iter`, `any`, `fn`, `if`, `while`, `for`, `return`, `var`, `val`, `const`, `frame`, `trait`, `import`, `match`, `in`, `type`, `enum`, `err`, `ok`, `and`, `or`, `not`, `as`, `where`, `self`, `super`, `true`, `false`, `nil`, `break`, `continue`, `parallel`, `concurrent`, `task`, `worker`, `contract`, `staged`, `unsafe`, `module`, `mixin`, `show`, `hide`, `from`, `elif`, `else`, `static`, `pub`, `prot`) are reserved and cannot be used as identifiers.
- [ ] For example: `var iter = 5;` or `fn iter(): int { ... }` or `frame Foo { pub fn iter(): int { ... } }` are **INVALID**.
- [x] **Note**: `list`, `dict`, `array` are **NOT** reserved keywords and can be used as identifiers.

### **Generics/Template Types**
- [ ] `fn my_func<T>(param: T): T` - Generic type parameters are NOT supported.
- [ ] `List<T>` / `Dict<K, V>` - Generic collections are NOT implemented (use `[int]` or `{str: int}`).
- [ ] `Option<T>` / `Result<T, E>` - Generic option/result types are NOT supported as built-in generics (use option/result union types or standard library wrappers).

### **List Concatenation**
- [ ] `list1 + list2` - List concatenation using the `+` operator is NOT supported.
- [x] **Use `append(list, item)`** instead to add a single item to a list.
- [x] **Use `append(list, other_list)`** to append all elements from another list.

---

## **USE - Supported Features**

### **1. Valid Syntax & Basic Constructs**

#### **Variables & Constants**
- **Variable**: `var x = 42;` or `var x: int = 42;`
- **Immutable Local**: `val y = 100;` (binds an immutable variable).
- **Constant**: `const PI = 3.14;` (defines an immutable binding).
- **Atomic**: `var counter: atomic = 0;` (special type for thread-safe operations).

#### **Operators**
- **Arithmetic**: `+`, `-`, `*`, `/`, `%` (modulo), `**` (exponentiation, right-associative).
- **Unary**: `not` (logical negator keyword, preferred over `!`), `-` (negation), `~` (bitwise NOT).
- **Logical**: `and`, `or`, `not` (keywords, not symbols).
- **Bitwise**: `&` (AND), `|` (OR), `^` (XOR), `<<` (left shift), `>>` (right shift).
- **Comparison**: `==`, `!=`, `<`, `<=`, `>`, `>=`
- **Type Cast**: `expression as TargetType`
- **Compound Assignment**: `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `|=`, `^=`, `<<=`, `>>=`

#### **Control Flow**
- **Conditionals**: `if (cond) { ... } elif (cond) { ... } else { ... }`
- **Loops**:
 - `while (cond) { ... }`
 - `for (var i = 0; i < 10; i = i + 1) { ... }`
 - `iter (item in collection) { ... }` (for lists, ranges, channels)  
   `iter (key, value in dict) { ... }` (**always this form for dictionaries** - the single-variable form type-checks as the key but holds the `(key, value)` pair at run time)  
   `iter` inside a **frame method** aborts the compiler; loop in a free function instead. `in` is not an expression operator: test dictionary containment with `if (dict[key] != nil)`.
- **Pattern Matching (Match)**: Uses block syntax `pattern => { statements }`.
 ```lymar
 match (value) {
 5 => { print("Literal match"); },
 Color.Red => { print("Enum variant"); },
 point => { print("Variable binding"); },
 val success => { print("Fallible success: {success}"); },
 err error => { print("Fallible error: {error}"); },
 _ => { print("Wildcard"); }
 }
 ```

#### **Basic Data Structures**
- **Lists**: Homogeneous collection, shorthand: `[int]`. Literal: `[1, 2, 3]`.
- **Dictionaries**: Shorthand: `{str: int}`. Literal: `{"a": 1, "b": 2}`. Bare identifiers are allowed as string keys: `{name: "John"}`.
- **Tuples**: Shorthand: `(int, str)`. Literal: `(42, "hello")`. Indexed with dot notation: `tuple.0`.
- **Objects (frames)**: Construct with the frame's constructor — `var p = Point();` then assign fields, or `Point(10, 20)` when the frame declares `init(x: int, y: int)`. The brace literal `Point { x: 10, y: 20 }` **parses but is rejected by the type checker** (`E003: Unknown expression type`, followed by a spurious `Type 'Nil' has no member ...`), so do not use it.
- **Ranges**: `1..10` (inclusive).

---

### **2. Type System Rules**

#### **Static & Strong Typing**
No implicit type conversions. You must explicitly cast types using `as` (e.g. `x as float`).

#### **Built-in Primitive Types**
- **Integers**: `int`, `i8`, `i16`, `i32`, `i64`, `i128`, `uint`, `u8`, `u16`, `u32`, `u64`, `u128`.
- **Floats**: `float`, `f32`, `f64`.
- **Decimals**: `d2`, `d4`, `d6`, `decimal`.
- **Others**: `str`, `bool`, `any` (dynamically checked), `nil` (null representation), `channel`.

#### **Advanced Type Constructs**
- **Type Aliases**: `type UserId = int;`
- **Union Types**: `int | str`
- **Intersection Types**: `TraitA & TraitB`
- **Refined Types**: `int where value > 0` or `str where length(value) > 10`
- **Optional Types**: `Type?` (syntactic sugar for `Type | nil`)
- **Fallible Types**: `Type?Error1,Error2` (defines specific error types that can be returned)

---

### **3. Object-Oriented Programming (OOP)**

#### **Frames**
Frames are class-like structures that define fields and methods.
- **Modifiers**: Fields and methods use `pub` (public), `prot` (protected), or default to private.
- **`embed` Has No Visibility Modifier**: Write `embed Engine;` — never `pub embed Engine;` or `prot embed Engine;`. An embed is a statement, not a member declaration; a visibility prefix carries no meaning and is discarded. Flattened fields and promoted methods keep the visibility they declare inside the embedded frame.
- **`self` Reference**: Inside methods, `self` is the canonical reference to the current instance (`this` is unsupported).
- **Lifecycle Methods**:
 - `pub init(...)` (constructor)
 - `pub deinit()` (destructor)

```lymar
frame Rectangle {
 pub width: int;
 pub height: int;

 pub init(w: int, h: int) {
 self.width = w;
 self.height = h;
 }

 pub fn area(): int {
 return self.width * self.height;
 }
}
```

#### **Traits**
Traits define **behavioural contracts** (interfaces) that frames conform to. A trait body contains methods only -- never fields. Every method must end in `;` (a requirement) or carry a `{ ... }` body (a default implementation). Omitting both is a parse error.
```lymar
trait Shape {
 fn area(): int;          // requirement: semicolon is mandatory
 fn name(): str { return "shape"; }   // default implementation
}

frame Square: Shape {
 pub side: int;
 pub fn area(): int {
 return self.side * self.side;
 }
}
```
- Conformance is checked **strictly**: the implementing method must match the requirement's name, parameter count, parameter types and return type. A same-named method with a different signature is rejected.
- A trait may require other traits: `trait Cached: Shape, Comparable { ... }`.
- `frame A : B` where `B` is a **frame** is illegal -- there is no frame inheritance.

#### **Mixins**
Mixins supply **shared data fields**. Members are flattened into the including frame at compile time, so the frame gains the fields directly -- there is no mixin sub-object, and a mixin cannot be instantiated on its own.
```lymar
mixin Identifiable {
 pub id: int;
}

frame User {
 mixin Identifiable;      // User now has its own `id` field
 pub name: str;
}

var u = User();
u.id = 7;                 // no `u.identifiable` qualifier
```
- Use a mixin for shared **state**. Use a trait for shared **behaviour**. A mixin is not an interface and never dispatches dynamically (methods are permitted only as accessors over its own fields).

#### **Frame Embedding**
`embed` flattens a component frame into its host at compile time: the component's fields become the host's own storage and the component's methods are **promoted** onto the host. Zero overhead -- no wrapper object, no indirection, no vtable.
```lymar
frame Engine {
 pub rpm: int;
 pub fn start() { self.rpm = 1000; }
}

frame Car {
 embed Engine;            // anonymous: creates no `self.engine`
 pub model: str;
}

var c = Car();
c.start();                // promoted method
c.rpm = 3000;             // promoted field, same storage the method reads
```
- Embedding is anonymous and introduces no accessor name; to name the component, declare a field (`pub engine: Engine;`).
- On a name collision the host's own member wins; promoted members never overwrite an existing one.
- Promoted members count as real members, so `frame Car: Drivable { embed Engine; }` satisfies `Drivable`.
- The component's `deinit()` is **not** called when the host is destroyed. Forward cleanup explicitly from the host's `deinit()`.

---

### **4. Error Handling Style**

#### **Fallible Types & Error Propagation**
Lymar does not use generic `Result` types. Instead, it uses fallible annotations like `int?` (generic error) or `int?DivisionByZero` (specific error).

- **Success/Error constructors**: Values must be returned using `ok(value)` or `err(...)`.
- **Error construction syntax** — exactly three shapes parse:
 - Generic error: `return err();`
 - Typed error without a payload: `return err(DivisionByZero);` (a bare identifier; it feeds only the static error set named in `int?DivisionByZero` and carries nothing at runtime)
 - Typed error with a payload: `return err(ValidationError("Value cannot be negative"));` (arguments are **positional**; the first is the runtime error value)
- **Never write these** — they do not parse:
 - `return err("ValidationError", "msg");` — a string cannot name an error type (`Expected error type name.`)
 - `return err(UnknownError { message = "msg" });` — error constructors take parentheses, not braces
 - `return err(UnknownError(message = "msg"));` — `name = expr` is a named argument only in an ordinary call; inside `err(...)` it parses as an assignment expression
- **Propagator (`?`)**: Suffixing an expression with `?` will propagate the error up the call stack if it fails.
- **Inline Handling (`? else`)**: You can handle errors inline with optional error variable capturing.
 ```lymar
 var value = divide(a, b)? else {
 return 0; // fallback default
 };

 var value_with_err = divide(a, b)? else {
 print("Failed: {err}");
 return 0;
 };
 ```

---

### **5. Module & Import Behavior**

- **Import Module**: `import std.collections as collections;`
- **Import Specific Symbols**: `import std.collections { List, Map };` (utilizes show filters under the hood).
- **Import Alias**: Imports can be aliased with `as`. Qualified names are referenced as `alias.Symbol`.
- **Import Visibility**: `import std.collections show Iterator;`
- **Declarative C Header Import** (`c:` scheme): triggers the header→binding pipeline at compile time, no CLI flag required.
 - Full header bound to a shared library: `import "c:math_ops.h" from "libmath_ops" as math;`
 - Cherry-pick symbols (brace-select is sugar for `show`): `import "c:math_ops.h" from "libmath_ops" as math { add_points, sub_points };`
 - `show` filter: `import "c:math_ops.h" from "libmath_ops" as math show safe_divide;`
 - System header (empty library path — resolves CRT symbols via the process handle): `import "c:stdio.h" as cstdio;`
 The binding is cached at `.cache/bindings/<ns>.lm` and reused when the header mtime is unchanged. See [docs/ffi.md](docs/ffi.md#declarative-c-imports-recommended) for the full grammar and lookup rules.

---

### **6. Stdlib Guidelines**

#### **Type Ownership**
- [ ] **DO NOT put type ownership in stdlib.** Type definitions (primitive types, collection types, enum types) are compiler-owned.
- [x] **Stdlib provides behavior only.** Stdlib modules implement functionality using compiler-defined types.

#### **Stdlib Implementation Rules**
- [ ] **Do not define fake replacement types for compiler collections.** Stdlib should not redefine types like `List`, `Dict`, `Array` as type aliases.
- [ ] **Do not solve missing typing by changing everything to `any`.** The `any` type is a dynamic escape hatch, not a replacement for real types.
- [x] **Use current supported mechanisms for generic-like behavior:**
 - `any` (dynamic typing, use sparingly)
 - `traits` (interface-based polymorphism)
 - `frames` (class-like structures with methods)
 - `union types` (e.g., `int | str`)
 - `function types` (higher-order functions)

#### **Example: Correct Stdlib Implementation**
```lymar
// std/collections/vector.lm
frame Vector {
 pub var data: [int]; // Uses compiler's list type

 pub fn init(): Vector {
 return Vector(data=[]);
 }

 pub fn push(value: int): Vector {
 // Implementation details...
 }
}
```

---

### **7. Concurrency**

- **Parallel Block**: `parallel(cores=2) { ... }` runs blocks in parallel.
- **Concurrent Block**: `concurrent(cores=2) { ... }` handles channel-based execution.
- **Tasks**: `task(i in 1..10) { ... }` spawns parallel tasks.
- **Workers**: `worker(data in stream) { ... }` processes streams.

==================================================
Backend Conformance
==================================================

The redesigned LIR is the canonical language interface.

Every backend must implement the complete semantics of every LIR instruction.

Backends must not require changes to the generator.

Backends must not introduce backend-specific LIR instructions.

Backends must not expose backend-specific concepts to the frontend.

If a backend cannot faithfully implement an LIR instruction, the backend must be extended rather than weakening the language abstraction.

Behavioral equivalence across all supported backends is mandatory.

When modifying Fyra, treat it as an independent repository. Commit and push the Fyra changes to the Fyra repository first, then update the Lymar superproject's Fyra gitlink and commit/push that change. Do not merely commit the modified submodule state in Lymar. Verify git status in both repositories before finishing.
 
Run `git submodule update --init` in Lymar after updating the Fyra gitlink and before building/testing. Verify that the Fyra version in Lymar's git status matches the intended version.
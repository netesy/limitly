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

### **Module Name Prefixing in Identifiers (Package/Module Stutter)**
- [ ] **DO NOT prefix frame, enum, or trait names with the enclosing module name** (e.g., `HTTPRequest`, `HTTPClient`, `HTTPMethod` in `std.http`, or `NOLValue`, `JSONValue`, `TOMLValue`, `TimeDuration`). The module boundary *is* the namespace. When imported as `import std.http as http;`, prefixing creates redundant stutter: `http.HTTPRequest`. Clashing imports are resolved at the call site using `as` or selective `show`, never by polluting symbol names.
- [x] **Use clean, self-contained names**: Declare `frame Request`, `frame Response`, `frame Client`, `frame Server`, `enum Method` in `std/http/`; `frame Value`, `enum Type` in `std/json/`, `std/toml/`, `std/yaml/`, `std/nol/`; `frame Duration`, `frame Instant` in `std/time/`; `frame Entry` in `std/archive/`. Callers access them as `http.Request`, `json.Value`, `time.Duration`, etc.

### **Module Re-export via `var` Aliases**
- [ ] **DO NOT re-export another module's symbols with `var X = mod.Symbol;`** (the old `std/std.lm` facade style). A `var` binding captures only a *runtime value*; it does **not** register the name in type position. So `var Option = core.option.Option;` leaves `Option` unusable as a type or staged-frame template and silently breaks annotations such as `var o: Option(int)`.
- [ ] **DO NOT use a `var` alias to rename an export** (e.g. `var TCP = tcp.TCPClient;`, `var Hash = crypto_hash.Hasher;`). `pub import ... show` re-exports a symbol **under the source module's declared name** and offers no rename facility; renaming files does not change the exported name either. If a friendlier or collision-free name is genuinely required, rename the symbol inside its own module.
- [x] **Use `pub import <module> show <Symbol, ...>;`** to re-export. This is the only pattern that propagates frames, enums, traits, and staged-frame templates through a facade module and keeps them valid in both value and type positions.

### **`pub var` for Module Constants (Anti-Pattern)**
- [ ] **DO NOT use `pub var` or `var` for constants** (e.g., `pub var METHOD_GET = "GET";`, `pub var STATUS_OK = 200;`, `pub var PI = 3.14;`, `pub var RT_FILE = 0;`). `pub var` creates a mutable global variable, allowing accidental mutation, disabling compiler immutability guarantees, preventing stage-0 constant folding, and forcing defensive runtime `Mov` register copying in the VM.
- [x] **Use `pub const` for module-level constants**: `pub const METHOD_GET = "GET";`, `pub const STATUS_OK = 200;`, `pub const PI = 3.14159;`. The compiler enforces immutability (`error[E003]: Cannot reassign to immutable variable`) and folds accesses at compile time.

### **`var` for Single-Assignment Locals**
- [ ] **DO NOT declare local variables that are never mutated with `var`** (e.g., `var client = Client();`, `var doc = parse(text);`). Overusing `var` signals intent to mutate and disables compiler immutable register optimizations.
- [x] **Use `val` for immutable local bindings**: `val client = Client();`, `val result = compute();`. Reserve `var` strictly for loop counters and variables whose values are reassigned.

### **Flat Integer Magic Constants (C-Style Enum Anti-Pattern)**
- [ ] **DO NOT declare groups of integer constants to represent states, modes, tags, or roles** (e.g. `pub const COLOR_BG = 0; pub const COLOR_TEXT = 1;` or `pub const STATE_IDLE = 0; pub const STATE_RUNNING = 1;`) coupled with 20-line `if (x == COLOR_BG) elif (x == COLOR_TEXT) ...` ladders.
- [x] **Use `enum` and `match`**: Declare `enum ColorRole { Bg, Text }` or `enum State { Idle, Running }` and dispatch with `match (role) { ColorRole.Bg => { ... }, ... }`. Enums provide compile-time exhaustiveness checks, eliminate sentinel bounds bugs, and cast cleanly to strings (`role as str`).

### **C-Style Index Loops over Collections**
- [ ] **DO NOT write manual indexing loops over lists or dictionaries** (e.g. `var i = 0; while (i < len(list)) { var item = list[i]; i = i + 1; }`). Manual indexing generates bounds checking overhead on every iteration and introduces off-by-one errors.
- [x] **Use native `iter`**:
  * Lists: `iter (item in list) { ... }`
  * Dictionaries: `iter (key, value in dict) { ... }`
  * Ranges: `iter (i in 0..10) { ... }`

### **C-Style Sentinel Error Return Values**
- [ ] **DO NOT return `-1`, `nil`, or integer error codes to signify failure** (e.g. `fn find(): int` returning `-1`).
- [x] **Use Lymar fallible types**: Annotate functions with `T?` or `T?ErrorType`, construct return values with `ok(value)` or `err(ErrorType(...))`, and propagate errors using `?` or handle them inline using `? else { ... }`.

### **Untyped Dictionaries / Parallel Arrays for Domain Models**
- [ ] **DO NOT use `{str: any}` or parallel lists (`keys: [str]`, `vals: [str]`) to model structured domain data**. Loose string dictionaries lack schema validation, degrade performance, and lose static type safety.
- [x] **Use nominal `frame` declarations**: Declare structured models with fields, default values, and methods: `frame User { pub id: int; pub name: str; }`.

### **Transitive Re-export Pollution (God Modules)**
- [ ] **DO NOT re-export another foundational domain's primitive types from a client library** (e.g. `ui` or `game` re-exporting `Color`, `hex`, `rgb` and redefining shadow copies of `white`, `black`, `red`). Re-exporting cross-domain constants causes runtime nil-pointer lookup bugs in bytecode, leads to cyclic dependencies, and muddies call-site imports.
- [x] **Consume domain types directly**: Code requiring colors should `import std.color as color;` and use `color.white` or `color.indigo(600)`. Each module stays within its own architectural boundary.

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
   `iter (key, value in dict) { ... }` (two-variable form unpacks pairs; the single-variable form `iter (key in dict)` binds the **key**)  
   `iter` works inside **frame methods**. `in` is not an expression operator: test dictionary containment with `if (dict[key] != nil)`.
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
- **Ranges**: `1..10` yields `1` through `9` — the end bound is **exclusive**. To iterate all `n` elements of a list use `0..n`, not `0..(n - 1)`.

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
- The component's `init()` is **not** run for embedded frames — `embed` flattens field declarations only. Give embedded fields field-level defaults (`pub var x: T = <default>;`) or assign the promoted fields in the host's `init()`; otherwise they stay `nil`/zero until set.

---

### **4. Error Handling Style**

#### **Fallible Types & Error Propagation**
Lymar does not use generic `Result` types. Instead, it uses fallible annotations like `int?` (generic error) or `int?DivisionByZero` (specific error).

- **Success/Error constructors**: Values must be returned using `ok(value)` or `err(...)`.
- **Error construction syntax** — four shapes parse:
 - Generic error: `return err();`
 - Typed error without a payload: `return err(DivisionByZero);` (a bare identifier; it feeds only the static error set named in `int?DivisionByZero` and carries nothing at runtime)
 - Typed error with a positional payload: `return err(ValidationError("Value cannot be negative"));` (arguments are **positional**; the first is the runtime error value)
 - Frame constructor with named arguments: `return err(Error(code="DivByZero", message="divisor is zero"));` (the inner `Error(...)` is a standard frame constructor call; named arguments are valid at that level)
- **Never write these** — they do not parse:
 - `return err("ValidationError", "msg");` — a string literal cannot name an error type (`Expected error type name.`)
 - `return err(UnknownError { message = "msg" });` — error constructors take parentheses, not braces
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
- [ ] **Do not re-export with `var` aliases.** Facade/index modules must propagate symbols with `pub import <module> show <Symbol, ...>;`, never `var X = mod.Symbol;` — a `var` alias binds a runtime value only and is invisible in type position (see *Module Re-export via `var` Aliases*).
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

---

### **8. Library-Specific Guidelines: std/ui and std/game**

These guidelines apply when working on the `std/ui` and `std/game` libraries, focusing on leveraging Lymar's native strengths for idiomatic, high-performance code.

#### **Zero-Cost Frame Embedding (embed)**
- [ ] **DO NOT use monolithic 60-field structs** that mix every possible property (e.g., a single `Widget` frame with 60+ fields for all widget types).
- [x] **Use specific widget frames that embed only what they need**: 
  ```lymar
  frame Button {
    embed LayoutBox;
    embed VisualStyle;
    embed Clickable;
    pub var label: str;
  }
  ```
- Embedding flattens fields at compile time with zero pointer overhead. Promoted methods provide fluent syntax without wrapper allocations.
- Each widget type (Button, Label, Slider, etc.) should embed only the component mixins it actually uses.

#### **Compile-Time Staging (staged fn)**
- [ ] **DO NOT construct UI trees at runtime** if they can be static (e.g., parsing style snapshots on every frame).
- [x] **Use staged static UI trees**: Static layout hierarchies, theme palettes, and constant bounding boxes should be computed at compile time into read-only constant memory.
- Only dynamic signal bindings should evaluate at runtime.
- Example: `staged fn build_app_ui(): Widget { ... }` executes at compile time, producing a constant widget tree.

#### **Nominal Enums & Exhaustive match**
- [ ] **DO NOT use 40-line if/elif ladders** or magic integer status codes for widget states, event types, or alignment modes.
- [x] **Use type-safe enums**: Declare `enum WidgetKind { Button, Label, Slider }`, `enum Event { Click, Hover, Focus }`, `enum Alignment { Start, Center, End }`.
- Dispatch with `match` for compiler-optimized jump tables and exhaustiveness checking:
  ```lymar
  match (widget.kind) {
    WidgetKind.Button => { ... },
    WidgetKind.Label => { ... },
    _ => { ... }
  }
  ```

#### **Fallible Types (T?Error) for Event Handling**
- [ ] **DO NOT use nullable `any` action callbacks** (e.g., `on_click_action: any = nil`) that require runtime nil checks.
- [x] **Use typed optional functions**: `on_click_action: (fn(): nil)?` for type-safe event handling.
- Event handling should use fallible streams/results: `Event?Handled` eliminates dynamic `any` boxing and nil-check ladders.
- Invocations should route through fallible types: `var result = button.click()? else { return EventResult.Unhandled; }`.

#### **Clean Domain Imports (No Transitive Re-exports)**
- [ ] **DO NOT re-export another foundational domain's primitive types** from client libraries (e.g., `std/ui` re-exporting `Color`, `hex`, `rgb` and redefining shadow copies of `white`, `black`, `red`).
- Transitive re-exports cause runtime nil-pointer lookup bugs, cyclic dependencies, and muddy call-site imports.
- [x] **Consume domain types directly**: Code requiring colors should `import std.color as color;` and use `color.white` or `color.indigo(600)`.
- Code requiring math types should `import std.math as math;` and use `math.Vec2` or `math.Rect`.
- Each module stays within its own architectural boundary; UI libraries focus on layout and interaction, not color math.

#### **Type-Safe Callbacks over Dynamic `any`**
- [ ] **DO NOT use `any` for callbacks** (e.g., `on_click: any`, `on_change: any`). This disables type checking and requires unsafe casts.
- [x] **Use typed function signatures**: `on_click: (fn(): nil)?`, `on_change: (fn(float)): nil?`.
- This enables compile-time type checking and eliminates runtime cast errors.

#### **Named Constants over Magic Integers**
- [ ] **DO NOT use flat integer magic constants** (e.g., `COLOR_BG = 0`, `COLOR_TEXT = 1`) with if/elif dispatch.
- [x] **Use nominal enums**: `enum ColorRole { WindowBg, Text, Accent }` dispatched via `match`.
- Enums provide compile-time exhaustiveness checks and cast cleanly to strings (`role as str`).

#### **Component-Based Architecture over God Objects**
- [ ] **DO NOT create monolithic frames** that contain every possible field (the "God object" anti-pattern).
- [x] **Use mixins and embed for composition**: Break concerns into reusable component mixins (LayoutMetrics, VisualStyle, Clickable, Focusable) and embed them as needed.
- This follows the single responsibility principle and enables zero-cost composition through `embed`.

When modifying Fyra, treat it as an independent repository. Commit and push the Fyra changes to the Fyra repository first, then update the Lymar superproject's Fyra gitlink and commit/push that change. Do not merely commit the modified submodule state in Lymar. Verify git status in both repositories before finishing.
 
Run `git submodule update --init` in Lymar after updating the Fyra gitlink and before building/testing. Verify that the Fyra version in Lymar's git status matches the intended version.
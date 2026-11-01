# Lymar Code Style & Linting Guide (`lint.md`)

This document defines the canonical standards for writing clean, idiomatic, high-performance Lymar code. It codifies the language's core design strengths—nominal typing, compile-time staging, zero-cost frame embedding, fallible error propagation, and immutability guarantees—while explicitly proscribing anti-patterns inherited from C, Python, Java, or Go.

---

## 1. Naming Conventions

Lymar enforces clear separation between namespaces, types, and values.

| Construct | Convention | Example | Proscribed Anti-Pattern |
| :--- | :--- | :--- | :--- |
| **Modules / Directories** | `snake_case` | `std.http`, `std.crypto.hash` | `std.HTTP`, `std.CryptoHash` |
| **Frames (Classes)** | `PascalCase` | `Request`, `Client`, `Document` | `HTTPRequest`, `XMLDocument` (Module Stutter) |
| **Traits (Interfaces)** | `PascalCase` | `Disposable`, `Reader`, `Shape` | `IDisposable`, `IReader` (C#/COM prefixes) |
| **Mixins** | `PascalCase` | `Identifiable`, `Positionable` | `MIdentifiable`, `MixinPosition` |
| **Enums** | `PascalCase` | `Method`, `Status`, `ColorRole` | `HTTPMethod`, `ColorEnum` |
| **Enum Variants** | `PascalCase` | `Method.Get`, `State.Running` | `Method.METHOD_GET`, `State.STATE_RUNNING` |
| **Functions / Methods** | `snake_case` | `parse()`, `to_string()`, `is_valid()` | `Parse()`, `toString()` |
| **Variables / Locals** | `snake_case` | `max_retries`, `buffer_size` | `maxRetries`, `sBufferSize` |
| **Constants (Module)** | `UPPER_SNAKE_CASE` | `pub const STATUS_OK = 200;` | `pub var STATUS_OK = 200;` |
| **Immutable Locals** | `snake_case` | `val header = req.header;` | `var header = req.header;` |

---

## 2. Immutability & Binding Integrity (`const` vs `val` vs `var`)

Lymar distinguishes between compile-time constants, single-assignment immutable local bindings, and mutable state.

### `const` (Compile-Time / Module-Level Constants)
* **Rule**: All top-level, module-level, and protocol constants must be declared with `pub const` or `const`.
* **Proscribed**: Never use `pub var` or `var` for constants.
* **Why**: `pub var` emits defensive register copies (`LIR_Op::Mov`) in the VM, allows accidental mutation across modules, and prevents compile-time stage-0 folding.
```lymar
// GOOD
pub const METHOD_GET = "GET";
pub const STATUS_OK = 200;
pub const PI = 3.14159265358979323846;

// BAD
pub var METHOD_GET = "GET";
pub var STATUS_OK = 200;
```

### `val` (Immutable Local Bindings)
* **Rule**: Local variables that are assigned once and never reassigned must use `val`.
* **Why**: Signals immutability to the compiler, prevents accidental reassignment (`error[E003]`), and enables register reuse without copying.
```lymar
// GOOD
val client = http.Client();
val response = client.get("https://example.com")?;
val total = a + b;

// BAD (Unnecessary mutability)
var client = http.Client();
var response = client.get("https://example.com")?;
```

### `var` (Mutable State & Loop Accumulators)
* **Rule**: Reserve `var` strictly for loop counters, accumulators, and variables that are genuinely mutated.
```lymar
// GOOD
var counter = 0;
while (counter < 10) {
    counter = counter + 1;
}
```

---

## 3. Namespace Integrity & Elimination of Stutter

The enclosing module boundary **is** the namespace. Types declared inside a module must never repeat the module's name as a prefix.

* **Rule**: Declare clean, self-contained symbols in their respective modules. Clashing symbols at the call site are resolved using import aliases (`as`) or selective imports (`show`), never by polluting the declaration name.

```lymar
// GOOD: In std/http/client.lm
frame Client { ... }
frame Request { ... }
frame Response { ... }
enum Method { Get, Post, ... }

// Call site:
import std.http as http;
val req = http.Request();
val client = http.Client();

// BAD: In std/http/client.lm (Stutter)
frame HTTPClient { ... }
frame HTTPRequest { ... }
// Call site: http.HTTPRequest() -> Redundant stutter!
```

---

## 4. Enums & Type-Safe Matching vs Grouped Constants

Lymar provides first-class `enum` types with variant matching and automatic string conversions (`variant as str`).

### Discrete Domains Belong in Enums
* **Rule**: Whenever a set of values models a discrete, finite domain (e.g. HTTP status codes, HTTP methods, event types, key modifiers, mouse buttons, FFI type IDs, memory alignments, close codes, or graphics channels), declare an `enum`, **not** loose integer or string constants.
* **Proscribed**: Never declare 20+ flat integer constants coupled with long `if/elif` ladders.

```lymar
// GOOD: Enums for Protocols & Domains
enum Status {
    Ok,
    Created,
    BadRequest,
    NotFound,
    InternalServerError
}

enum Method {
    Get,
    Post,
    Put,
    Delete
}

// Exhaustive pattern matching:
match (status) {
    Status.Ok => { print("Success"); },
    Status.NotFound => { print("Resource missing"); },
    _ => { print("Other status"); }
}

// BAD: C-Style flat integer constants and elif ladder
pub const STATUS_OK = 200;
pub const STATUS_NOT_FOUND = 404;

if (status == STATUS_OK) { ... }
elif (status == STATUS_NOT_FOUND) { ... }
```

### Native Lymar Enums vs Foreign Language Helper Trampolines
* **Rule**: Build around Lymar's native language strengths; do not write redundant procedural trampolines (`status_code()`, `method_name()`, `status_text()`) copied from languages like C or Go.
* **Why**:
  1. **Built-in String Reflection**: Lymar provides native compile-time and runtime variant reflection via `variant as str` (`Method.Get as str == "Get"`, `Status.Ok as str == "Ok"`).
  2. **First-Class Match**: Lymar's `match` statement is expressive, exhaustive, and fast. Functions consuming domain states should accept nominal enum types (`method: Method`) and match directly.
  3. **No Redundant Indirection**: In languages lacking expressive enums (e.g. Go or older C), developers are forced to write 40-line procedural mapping trampolines. In Lymar, this is an anti-pattern that dilutes the type system and adds zero-value boilerplate. Accept the nominal enum directly.

---

## 5. Composition: Traits, Mixins, and Frame Embedding

Lymar has **no frame inheritance** (`frame A : B` where `B` is a frame is invalid). Use Lymar's three composition primitives correctly:

### Traits (`trait`)
* Purpose: Defines **behavioral contracts** (interfaces).
* Rules:
  * Contains methods only — **never fields**.
  * Every method must end in `;` (requirement) or `{ ... }` (default implementation).
  * Conformance is checked strictly against parameter count, types, and return types.

```lymar
trait Disposable {
    pub fn dispose(): nil;
}

frame Socket: Disposable {
    pub handle: int;
    pub fn dispose(): nil {
        // cleanup logic
    }
}
```

### Mixins (`mixin`)
* Purpose: Supplies **shared data fields**.
* Rules:
  * Mixin fields are flattened directly into the host frame at compile time.
  * Zero runtime overhead — no sub-object, no indirection.
  * Use for shared state, not dynamic dispatch.

```lymar
mixin Identifiable {
    pub id: int;
}

frame User {
    mixin Identifiable; // User now has self.id directly
    pub name: str;
}
```

### Frame Embedding (`embed`)
* Purpose: Anonymous composition and method promotion.
* Rules:
  * `embed Component;` — never `pub embed` or `prot embed`.
  * Embedded fields are flattened into the host; methods are **promoted** onto the host.
  * Zero indirection, zero wrapper objects, no vtable overhead.

```lymar
frame Engine {
    pub rpm: int;
    pub fn start() { self.rpm = 1000; }
}

frame Car {
    embed Engine;
    pub model: str;
}

val c = Car();
c.start(); // Promoted method from Engine
```

---

## 6. Error Handling: Fallible Types vs Sentinel Returns

Lymar treats errors as first-class fallible types (`T?` or `T?ErrorType`), not generic objects, exceptions, or sentinel return codes (`-1`, `nil`).

### Rules
1. **Never return sentinel error numbers**: Functions must not return `-1` or `nil` to signal error conditions. Use `int?` or `T?Error`.
2. **Always construct results with `ok(...)` or `err(...)`**:
   * Success: `return ok(result);`
   * Generic error: `return err();`
   * Specific error: `return err(ValidationError("invalid port"));`
3. **Propagate with `?`**:
   ```lymar
   val sock = net.connect("127.0.0.1", 8080)?;
   ```
4. **Handle inline with `? else`**:
   ```lymar
   val port = parse_int(str_val)? else {
       return 8080; // Default fallback
   };
   ```

---

## 7. Iteration: Native `iter` vs C-Style Index Loops

Lymar features native `iter` loops that avoid index arithmetic and bounds checking.

* **Lists**: `iter (item in list) { ... }`
* **Dictionaries**: `iter (key, value in dict) { ... }` (unpacks key-value pairs)
* **Ranges**: `iter (i in 0..10) { ... }`

```lymar
// GOOD
iter (header_name, header_val in req.headers) {
    print("{header_name}: {header_val}");
}

// BAD (C-style manual indexing)
var i = 0;
while (i < len(items)) {
    val it = items[i];
    print(it);
    i = i + 1;
}
```

---

## 8. Module Exports & Public Facades

Facade modules (such as `std/std.lm`, `std/http/index.lm`, `std/time/index.lm`) must re-export symbols cleanly without breaking type positions.

* **Rule**: Always use `pub import <submodule> show <Symbols...>;`.
* **Proscribed**: Never re-export symbols using `var X = mod.Symbol;` aliases. A `var` alias captures only a runtime value and is invisible in type positions.

```lymar
// GOOD
pub import std.http.client show Client, Request, Response;
pub import std.http.common show Method, Status, STATUS_OK, METHOD_GET;

// BAD (Breaks type annotations downstream!)
import std.http.client as client;
pub var Client = client.Client;
```

---

## 9. Transitive Re-export Pollution & Domain Encapsulation

Every module in the standard library owns its domain. Foundational domain models (such as `Color` from `std.color`, `Vec2` from `std.math`, or `Duration` from `std.time`) must NOT be re-exported by client libraries (`std.ui`, `std.game`, `std.graphics`) to form "God modules".

* **Rule**: Client modules must consume external domain types by importing them directly. Do not re-export fundamental types from other domains, and never recreate shadow instances/variables of another module's constants.
* **Proscribed**:
  - `pub import std.color show Color;` inside `std.ui` or `std.game`.
  - Re-declaring `pub var white: Color = ...` inside `std/ui/types.lm`, `std/ui/color.lm`, and `std/ui/index.lm`.
* **Why**:
  1. **Namespace Ambiguity**: Downstream code becomes confused over whether to write `ui.white`, `color.white`, `game.white`, or `graphics.white`.
  2. **Storage Decoupling in Bytecode**: Re-exporting module-level constants across modules without direct definition causes runtime nil lookups (`LoadGlobal "mod.var"` resolves to uninitialized memory).
  3. **Dependency Spaghetti**: Re-export chains lead to circular dependencies and fragile compile orders.

```lymar
// GOOD: Each module stays in its domain
import std.ui as ui;
import std.color as color;

val btn = ui.button("Submit")
    .background(color.indigo(600))
    .foreground(color.white);

// BAD: UI pretends to be the color library
import std.ui as ui;

val btn = ui.button("Submit")
    .background(ui.indigo)
    .foreground(ui.white); // Pollutes UI namespace
```

---

## 10. Lint Rules Summary Checklist

| Rule ID | Name | Severity | Description |
| :--- | :--- | :--- | :--- |
| **LM001** | `no-pub-var-constant` | Error | Module constants must use `pub const`, not `pub var`. |
| **LM002** | `no-reassign-val` | Error | Single-assignment locals must use `val`, not `var`. |
| **LM003** | `no-module-stutter` | Warning | Identifiers must not prefix the enclosing module name (`http.Request`, not `http.HTTPRequest`). |
| **LM004** | `no-magic-int-enums` | Warning | Use `enum` and `match` instead of grouped flat integers and `if/elif` ladders. |
| **LM005** | `prefer-native-iter` | Suggestion | Use `iter (x in list)` instead of manual `while (i < len)` indexing. |
| **LM006** | `prefer-fallible-return` | Warning | Return fallible types `T?` with `ok()`/`err()`, not `-1` or `nil` sentinels. |
| **LM007** | `no-var-export-alias` | Error | Re-export facade symbols with `pub import ... show`, not `pub var X = mod.X`. |
| **LM008** | `no-frame-inheritance` | Error | Do not inherit frames (`frame A : B`). Use `embed`, `mixin`, or `trait`. |
| **LM009** | `no-reserved-identifier` | Error | Language keywords (`iter`, `any`, `val`, etc.) must not be used as identifiers. |
| **LM010** | `no-untyped-domain-dict` | Suggestion | Model structured domain entities with `frame`, not loose `{str: any}` dictionaries. |
| **LM011** | `enums-over-grouped-constants` | Suggestion | Discrete domains (statuses, methods, types, buttons, transitions) must be modeled as `enum`s. |
| **LM012** | `no-transitive-reexport-pollution` | Warning | Do not re-export fundamental types from other domains or recreate shadow global instances. |

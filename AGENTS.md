# Limitly Language - AI Agent Guidelines

This document provides essential guidelines for AI agents generating code for the Limitly language. It outlines the valid syntax, supported language constructs, type system rules, module/import behavior, and error handling style that are actually implemented and supported by the Limitly compiler.

---

## 🚫 **DO NOT USE - Unsupported Features**

### **Generics/Template Types**
- ❌ `fn my_func<T>(param: T): T` - Generic type parameters are NOT supported.
- ❌ `List<T>` / `Dict<K, V>` - Generic collections are NOT implemented (use `[int]` or `{str: int}`).
- ❌ `Option<T>` / `Result<T, E>` - Generic option/result types are NOT supported as built-in generics (use option/result union types or standard library wrappers).

---

## ✅ **USE - Supported Features**

### **1. Valid Syntax & Basic Constructs**

#### **Variables & Constants**
- **Variable**: `var x = 42;` or `var x: int = 42;`
- **Immutable Local**: `val y = 100;` (binds an immutable variable).
- **Constant**: `const PI = 3.14;` (defines an immutable binding).
- **Atomic**: `var counter: atomic = 0;` (special type for thread-safe operations).

#### **Operators**
- **Arithmetic**: `+`, `-`, `*`, `/`, `%` (modulo), `**` (exponentiation, right-associative).
- **Unary**: `not` (logical negator keyword, preferred over `!`), `-` (negation), `~` (bitwise NOT).
- **Bitwise**: `&` (AND), `|` (OR), `^` (XOR), `<<` (left shift), `>>` (right shift).
- **Comparison**: `==`, `!=`, `<`, `<=`, `>`, `>=`
- **Type Cast**: `expression as TargetType`
- **Compound Assignment**: `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `|=`, `^=`, `<<=`, `>>=`

#### **Control Flow**
- **Conditionals**: `if (cond) { ... } else if (cond) { ... } else { ... }`
- **Loops**:
  - `while (cond) { ... }`
  - `for (var i = 0; i < 10; i = i + 1) { ... }`
  - `iter (item in collection) { ... }` (for lists, dicts, ranges)
- **Pattern Matching (Match)**: Uses block syntax `pattern => { statements }`.
  ```limit
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
- **Objects**: Literal: `Point { x: 10, y: 20 }`.
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
- **`self` Reference**: Inside methods, `self` is the canonical reference to the current instance (`this` is unsupported).
- **Lifecycle Methods**:
  - `pub init(...)` (constructor)
  - `pub deinit()` (destructor)

```limit
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
Traits define interface requirements that frames can implement.
```limit
trait Shape {
    fn area(): int
}

frame Square: Shape {
    pub side: int;
    pub fn area(): int {
        return self.side * self.side;
    }
}
```

---

### **4. Error Handling Style**

#### **Fallible Types & Error Propagation**
Limitly does not use generic `Result` types. Instead, it uses fallible annotations like `int?` (generic error) or `int?DivisionByZero` (specific error).

- **Success/Error constructors**: Values must be returned using `ok(value)` or `err(ErrorType)` (or `err()` for generic fallible returns).
- **Propagator (`?`)**: Suffixing an expression with `?` will propagate the error up the call stack if it fails.
- **Inline Handling (`? else`)**: You can handle errors inline with optional error variable capturing.
  ```limit
  var value = divide(a, b)? else {
      return 0; // fallback default
  };

  var value_with_err = divide(a, b)? else err {
      print("Failed: {err}");
      return 0;
  };
  ```

---

### **5. Module & Import Behavior**

- **Import Module**: `import std.collections as collections;`
- **Import Specific Symbols**: `import std.collections { List, Map };` (utilizes show filters under the hood).
- **Import Alias**: Imports can be aliased with `as`. Qualified names are referenced as `alias.Symbol`.

---

### **6. Concurrency**

- **Parallel Block**: `parallel { ... }` runs blocks in parallel.
- **Concurrent Block**: `concurrent { ... }` handles channel-based execution.
- **Tasks**: `task(i in 1..10) { ... }` spawns parallel tasks.
- **Workers**: `worker(data in stream) { ... }` processes streams.

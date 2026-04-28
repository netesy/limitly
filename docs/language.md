# Limit Language Specification (v0.1)

This document provides a formal specification of the Limit programming language syntax and semantics.

## 1. Lexical Structure

### 1.1 Keywords
`and`, `as`, `break`, `channel`, `concurrent`, `continue`, `comptime`, `contract`, `data`, `elif`, `else`, `enum`, `err`, `false`, `fn`, `for`, `frame`, `hide`, `if`, `import`, `in`, `interface`, `iter`, `loop`, `match`, `module`, `nil`, `ok`, `or`, `parallel`, `pub`, `prot`, `return`, `show`, `static`, `this`, `trait`, `true`, `type`, `unsafe`, `var`, `where`, `while`

### 1.2 Literals
- **Integer**: `[0-9]+` (e.g., `42`)
- **Float**: `[0-9]+\.[0-9]+` (e.g., `3.14`)
- **Scientific**: `[0-9]+e[+-]?[0-9]+` (e.g., `1e9`)
- **String**: `"[^"]*"` or `'[^']*'` (supports interpolation via `{expression}`)
- **Boolean**: `true`, `false`
- **Nil**: `nil` (represents a null/empty state)

### 1.3 Operators
- **Arithmetic**: `+`, `-`, `*`, `/`, `%`, `**` (power)
- **Comparison**: `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Logical**: `and`, `or`, `!` (not)
- **Bitwise**: `&` (and), `|` (or), `^` (xor), `~` (not)
- **Assignment**: `=`, `+=`, `-=`, `*=`, `/=`, `%=`
- **Access**: `.` (member), `[]` (index), `->` (arrow), `::` (namespace)
- **Special**: `?` (fallible/optional), `..` (range), `...` (ellipsis/rest)

## 2. Type System

### 2.1 Primitive Types
- `int`: Signed integer (platform-dependent size, usually 64-bit)
- `uint`: Unsigned integer
- `float`: Floating-point number (64-bit)
- `bool`: Boolean value (`true` or `false`)
- `str`: UTF-8 string
- `any`: Top type (can hold any value)
- `nil`: Type of the `nil` literal

### 2.2 Fixed-Width Types
- Integers: `i8`, `i16`, `i32`, `i64`, `i128`
- Unsigned: `u8`, `u16`, `u32`, `u64`, `u128`
- Floats: `f32`, `f64`

### 2.3 Composite Types
- **List**: `[Type]` - Dynamic array of elements.
- **Dictionary**: `{KeyType: ValueType}` - Key-value map.
- **Tuple**: `(Type1, Type2, ...)` - Fixed-size collection of heterogeneous types.
- **Union**: `Type1 | Type2` - Value that is either Type1 or Type2.
- **Option/Result (Fallible)**: `Type?` - Shorthand for a value that might be absent or an error.
- **Function**: `fn(ParamTypes): ReturnType` - First-class function type.

## 3. Declarations

### 3.1 Variables
`var name[: Type] = expression;`
Variables are private to their scope by default.

### 3.2 Functions
`fn name([params])[: ReturnType] { body }`
- Supports optional parameters: `name: Type = default`
- Supports generic parameters: `fn name[T](...)`

### 3.3 Frames (Objects)
Frames are the primary unit of data encapsulation and behavior.

```limit
[modifier] frame Name [: Traits] {
    [visibility] var fieldName: Type [= default];
    [visibility] fn methodName([params])[: ReturnType] { body }
    [visibility] init([params]) { body }
    [visibility] deinit() { body }
}
```

#### 3.3.1 Modifiers
- `abstract`: Frame cannot be instantiated directly. May contain abstract methods.
- `final`: Frame cannot be inherited from.
- `data`: Implicitly `final`. Intended for POD (Plain Old Data) with generated helpers.

#### 3.3.2 Visibility
- `private` (default): Accessible only within the frame.
- `prot` (protected): Accessible within the frame and subframes.
- `pub` (public): Accessible from any scope.

## 4. Control Flow

### 4.1 Match Statement
Pattern matching for literals, types, and structures.
```limit
match (expression) {
    pattern [where guard] => statement | { block },
    ...
}
```

### 4.2 Iter Loop
Used for ranges and collection iteration.
`iter (var? name [ , secondName ] in iterable) { body }`

### 4.3 Error Handling
- `?`: Propagation operator. If expression returns `Err`, return `Err` from current function.
- `? else { ... }`: Inline error handling / default value.

## 5. Modules and Imports

### 5.1 Import Syntax
- `import module_name;`
- `import module_name as alias;`
- `import module_name show symbol1, symbol2;`
- `import module_name hide symbol3;`

### 5.2 Module Blocks
Explicitly group declarations with visibility control.
```limit
module name {
    @public fn shared() { ... }
}
```

## 6. Concurrency

### 6.1 Structured Concurrency
Concurrency is bound to the lifetime of the block.
- `parallel(...) { ... }`: CPU-bound tasks.
- `concurrent(...) { ... }`: I/O-bound tasks.

### 6.2 Tasks and Workers
- `task([name in] iterable) { ... }`: Spawn a unit of work.
- `worker(param in channel) { ... }`: Process elements from a channel.

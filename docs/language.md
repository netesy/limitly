# Limit Language Specification (v0.1)

This document provides a formal specification of the Limit programming language syntax and semantics.

## 1. Lexical Structure

### 1.1 Keywords
`and`, `as`, `break`, `channel`, `concurrent`, `continue`, `comptime`, `contract`, `data`, `elif`, `else`, `enum`, `err`, `false`, `fn`, `for`, `frame`, `hide`, `if`, `import`, `in`, `interface`, `iter`, `loop`, `match`, `module`, `nil`, `ok`, `or`, `parallel`, `pub`, `prot`, `return`, `show`, `static`, `this`, `trait`, `true`, `type`, `unsafe`, `var`, `where`, `while`

### 1.2 Literals
- **Integer**: `[0-9]+`
- **Float**: `[0-9]+\.[0-9]+`
- **String**: `"[^"]*"` or `'[^']*'` (supports interpolation via `{expression}`)
- **Boolean**: `true`, `false`
- **Nil**: `nil`

## 2. Types

### 2.1 Primitive Types
- `int`, `uint`, `float`, `bool`, `str`, `any`, `nil`
- Fixed-width: `i8`, `i16`, `i32`, `i64`, `i128`, `u8`, `u16`, `u32`, `u64`, `u128`, `f32`, `f64`

### 2.2 Composite Types
- **List**: `[Type]`
- **Dictionary**: `{KeyType: ValueType}`
- **Tuple**: `(Type1, Type2, ...)`
- **Union**: `Type1 | Type2`
- **Option/Result (Fallible)**: `Type?` (Shorthand for `Result<Type, DefaultError>`)

## 3. Declarations

### 3.1 Variables
`var name[: Type] = expression;`

### 3.2 Functions
`fn name([params])[: ReturnType] { body }`

### 3.3 Frames (Objects)
```limit
[modifier] frame Name [: Traits] {
    [visibility] var fieldName: Type [= default];
    [visibility] fn methodName([params])[: ReturnType] { body }
    [visibility] init([params]) { body }
}
```
- **Modifiers**: `abstract`, `final`, `data`
- **Visibility**: `pub`, `prot` (default is private)

## 4. Control Flow

### 4.1 Match Statement
```limit
match (expression) {
    pattern [where guard] => statement | { block },
    ...
}
```

### 4.2 Iter Loop
`iter (var? name [ , secondName ] in iterable) { body }`

## 5. Concurrency

### 5.1 Structured Blocks
- `parallel(...) { body }`
- `concurrent(...) { body }`

### 5.2 Task Statements
- `task([name in] iterable) { body }`

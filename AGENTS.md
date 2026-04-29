# Limitly Language - AI Agent Guidelines

This document provides essential guidelines for AI agents generating code for the Limitly language to ensure compatibility and avoid introducing unsupported features.

## 🚫 **DO NOT USE - Unsupported Features**

### **Generics/Template Types**
- [FAIL] `fn my_func<T>(param: T): T` - Generic type parameters are NOT supported
- [FAIL] `List<T>` - Generic collections are NOT implemented
- [FAIL] `Dict<K, V>` - Generic dictionaries are NOT implemented
- [FAIL] `Option<T>` - Generic option types are NOT supported
- [FAIL] `Result<T, E>` - Generic result types are NOT supported

### **Advanced Type Features**
- [FAIL] Generic type constraints (`where T: Trait`)
- [FAIL] Type inference for complex generic scenarios
- [FAIL] Variadic generics (`T...`)
- [FAIL] Generic trait implementations

## [OK] **USE - Supported Features**

### **Type System**
- [OK] **Type Aliases**: `type UserId = int`
- [OK] **Optional Types**: `str?` (union with nil)
- [OK] **Union Types**: `int | string`
- [OK] **Error Unions**: `Result<int, Error>`
- [OK] **Frame Types**: User-defined objects with fields and methods
- [OK] **Trait Types**: Interfaces with method signatures
- [OK] **Primitive Types**: `int`, `float`, `str`, `bool`, `nil`
- [OK] **Collection Types**: `[int]` (lists), `{str: int}` (dicts), `(int, str)` (tuples)

### **Functions**
- [OK] **Optional Parameters**: `fn greet(name: str = "World")`
- [OK] **Default Values**: Function parameters can have defaults
- [OK] **Multiple Parameters**: `fn func(a: int, b: str, c: bool = true)`
- [OK] **Return Types**: `fn add(a: int, b: int): int`
- [OK] **Closures**: Functions that capture variables
- [OK] **First-class Functions**: Functions as values

### **Control Flow**
- [OK] **Match Statements**: Pattern matching with type guards
- [OK] **If/Else**: Conditional statements
- [OK] **Loops**: `for`, `while`, `iter`
- [OK] **Ranges**: `1..10`, `start..end`

### **Modules**
- [OK] **Import**: `import std.collections as collections`
- [OK] **Module Aliases**: `as` keyword for renaming
- [OK] **Selective Import**: `import module { specific_function }`

### **OOP Features**
- [OK] **Frames**: User-defined objects with fields and methods
- [OK] **Traits**: Interfaces that frames can implement
- [OK] **Method Calls**: `obj.method()`
- [OK] **Field Access**: `obj.field`
- [OK] **Trait Implementation**: Frames can implement multiple traits

### **Concurrency**
- [OK] **Parallel Blocks**: `parallel { ... }`
- [OK] **Concurrent Blocks**: `concurrent { ... }`
- [OK] **Tasks**: `task(i in 1..10) { ... }`
- [OK] **Atomic Types**: `var counter: atomic = 0`

## 📝 **Code Examples**

### **Correct Usage**
```limit
// Type aliases
type UserId = int
type Name = str

// Optional parameters with defaults
fn createUser(name: str, age: int = 18, active: bool = true): str {
    return "{name}, {age}, {active}"
}

// Optional types (not generics)
fn processOptional(value: int?): str {
    if (value) {
        return "Got: {value}"
    } else {
        return "Got nothing"
    }
}

// Union types
fn handleValue(value: int | str): str {
    match (value) {
        int => return "Integer: {value}",
        str => return "String: {value}"
    }
}

// Frame with trait
trait Drawable {
    fn draw(): str
}

frame Circle implements Drawable {
    var radius: float
    pub fn draw(): str {
        return "Drawing circle with radius {self.radius}"
    }
}

// Collections (concrete types)
var numbers: [int] = [1, 2, 3]
var mapping: {str: int} = {"a": 1, "b": 2}
var point: (int, int) = (10, 20)
```

### **Incorrect Usage - DO NOT DO THIS**
```limit
// [FAIL] NO GENERICS
fn identity<T>(x: T): T {
    return x
}

// [FAIL] NO GENERIC COLLECTIONS
var list: List<int> = [1, 2, 3]
var dict: Dict<string, int> = {"a": 1}

// [FAIL] NO GENERIC TRAITS
trait Comparable<T> {
    fn compare(other: T): int
}

// [FAIL] NO GENERIC CONSTRAINTS
fn sort<T where T: Comparable>(list: [T]): [T] {
    // implementation
}
```

## 🔧 **Common Patterns**

### **Instead of Generics, Use:**
1. **Type Aliases**: `type UserId = int`
2. **Union Types**: `int | str | bool`
3. **Overloaded Functions**: Multiple functions with different parameter types
4. **Trait Objects**: Dynamic dispatch through traits

### **Function Signatures**
```limit
// [OK] GOOD: Specific types
fn processInts(numbers: [int]): int
fn processStrings(texts: [str]): str

// [FAIL] BAD: Generic types
fn process<T>(items: [T]): T
```

### **Collection Handling**
```limit
// [OK] GOOD: Concrete collections
var numbers: [int] = [1, 2, 3]
var names: [str] = ["Alice", "Bob"]
var data: {str: int} = {"count": 10}

// [FAIL] BAD: Generic collections
var items: List<T> = []
var mapping: Dict<K, V> = {}
```

## 🎯 **Key Principles**

1. **Be Specific**: Use concrete types instead of generic placeholders
2. **Use Unions**: For multiple possible types, use union syntax
3. **Leverage Traits**: For polymorphism, use traits not generics
4. **Type Aliases**: Create meaningful aliases for complex types
5. **Optional Types**: Use `?` syntax for nullable values

## [WARN] **Important Notes**

- The type system is **static** and **strong** - no implicit conversions
- **Optional types** use `?` syntax (e.g., `int?`) not generic `Option<T>`
- **Union types** use `|` syntax (e.g., `int | string`)
- **Error handling** uses error unions, not generic `Result<T, E>`
- **Collections** are homogeneous but not generic - specify element types directly

## 📚 **Reference Implementation**

Always check existing standard library code for patterns:
- `std/collections/list.lm` - List implementation
- `std/collections/hashmap.lm` - HashMap implementation  
- `std/core.lm` - Core type definitions
- Test files in `tests/` directory for working examples

When in doubt, write concrete, specific code rather than attempting generic abstractions.

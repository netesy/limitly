# Limitly Language - AI Agent Guidelines

This document provides essential guidelines for AI agents generating code for the Limitly language to ensure compatibility and avoid introducing unsupported features.

## 🚫 **DO NOT USE - Unsupported Features**

### **Generics/Template Types**
- ❌ `fn my_func<T>(param: T): T` - Generic type parameters are NOT supported
- ❌ `List<T>` - Generic collections are NOT implemented
- ❌ `Dict<K, V>` - Generic dictionaries are NOT implemented
- ❌ `Option<T>` - Generic option types are NOT supported
- ❌ `Result<T, E>` - Generic result types are NOT supported

### **Advanced Type Features**
- ❌ Generic type constraints (`where T: Trait`)
- ❌ Type inference for complex generic scenarios
- ❌ Variadic generics (`T...`)
- ❌ Generic trait implementations

## ✅ **USE - Supported Features**

### **Type System**
- ✅ **Type Aliases**: `type UserId = int`
- ✅ **Optional Types**: `str?` (union with nil)
- ✅ **Union Types**: `int | string`
- ✅ **Error Unions**: `Result<int, Error>`
- ✅ **Frame Types**: User-defined objects with fields and methods
- ✅ **Trait Types**: Interfaces with method signatures
- ✅ **Primitive Types**: `int`, `float`, `str`, `bool`, `nil`
- ✅ **Collection Types**: `[int]` (lists), `{str: int}` (dicts), `(int, str)` (tuples)

### **Functions**
- ✅ **Optional Parameters**: `fn greet(name: str = "World")`
- ✅ **Default Values**: Function parameters can have defaults
- ✅ **Multiple Parameters**: `fn func(a: int, b: str, c: bool = true)`
- ✅ **Return Types**: `fn add(a: int, b: int): int`
- ✅ **Closures**: Functions that capture variables
- ✅ **First-class Functions**: Functions as values

### **Control Flow**
- ✅ **Match Statements**: Pattern matching with type guards
- ✅ **If/Else**: Conditional statements
- ✅ **Loops**: `for`, `while`, `iter`
- ✅ **Ranges**: `1..10`, `start..end`

### **Modules**
- ✅ **Import**: `import std.collections as collections`
- ✅ **Module Aliases**: `as` keyword for renaming
- ✅ **Selective Import**: `import module { specific_function }`

### **OOP Features**
- ✅ **Frames**: User-defined objects with fields and methods
- ✅ **Traits**: Interfaces that frames can implement
- ✅ **Method Calls**: `obj.method()`
- ✅ **Field Access**: `obj.field`
- ✅ **Trait Implementation**: Frames can implement multiple traits

### **Concurrency**
- ✅ **Parallel Blocks**: `parallel { ... }`
- ✅ **Concurrent Blocks**: `concurrent { ... }`
- ✅ **Tasks**: `task(i in 1..10) { ... }`
- ✅ **Atomic Types**: `var counter: atomic = 0`

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
// ❌ NO GENERICS
fn identity<T>(x: T): T {
    return x
}

// ❌ NO GENERIC COLLECTIONS
var list: List<int> = [1, 2, 3]
var dict: Dict<string, int> = {"a": 1}

// ❌ NO GENERIC TRAITS
trait Comparable<T> {
    fn compare(other: T): int
}

// ❌ NO GENERIC CONSTRAINTS
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
// ✅ GOOD: Specific types
fn processInts(numbers: [int]): int
fn processStrings(texts: [str]): str

// ❌ BAD: Generic types
fn process<T>(items: [T]): T
```

### **Collection Handling**
```limit
// ✅ GOOD: Concrete collections
var numbers: [int] = [1, 2, 3]
var names: [str] = ["Alice", "Bob"]
var data: {str: int} = {"count": 10}

// ❌ BAD: Generic collections
var items: List<T> = []
var mapping: Dict<K, V> = {}
```

## 🎯 **Key Principles**

1. **Be Specific**: Use concrete types instead of generic placeholders
2. **Use Unions**: For multiple possible types, use union syntax
3. **Leverage Traits**: For polymorphism, use traits not generics
4. **Type Aliases**: Create meaningful aliases for complex types
5. **Optional Types**: Use `?` syntax for nullable values

## ⚠️ **Important Notes**

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

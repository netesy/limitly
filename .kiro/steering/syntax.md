---
inclusion: always
---

# Limit Language Syntax Reference

This document provides comprehensive syntax reference for the Limit programming language. Use this when writing new code and add new features here as they are implemented.

---

## Table of Contents

1. [Basic Syntax](#basic-syntax)
2. [Variables and Types](#variables-and-types)
3. [Control Flow](#control-flow)
4. [Functions](#functions)
5. [Collections](#collections)
6. [String Operations](#string-operations)
7. [Type System](#type-system)
8. [Pattern Matching](#pattern-matching)
9. [Modules](#modules)
10. [Concurrency](#concurrency)
11. [Error Handling](#error-handling)
12. [Object-Oriented Features](#object-oriented-features)

---

## Basic Syntax

### Print Statements
```limit
print("Hello, World!");
print("Value: {variable}");
print("Expression: {x + y}");
```

### Comments
```limit
// Single line comment
/* Multi-line comment
   spanning multiple lines */
```

### Literals
```limit
// Numbers
var int_val = 42;
var float_val = 3.14;
var scientific = 1.5e-10;

// Strings
var str_val = "hello";
var empty_str = "";

// Booleans
var bool_true = true;
var bool_false = false;

// Nil
var nil_val = nil;
```

---

## Variables and Types

### Variable Declaration
```limit
// With explicit type
var name: int = 42;
var message: str = "hello";

// With type inference
var count = 10;
var text = "world";

// Without initialization
var uninitialized: int;
```

### Type Annotations
```limit
// Primitive types
var a: int = 5;
var b: float = 3.14;
var c: str = "text";
var d: bool = true;

// Sized integers
var i8: int8 = 127;
var i16: int16 = 32767;
var i32: int32 = 2147483647;
var i64: int64 = 9223372036854775807;
var u8: uint8 = 255;
var u16: uint16 = 65535;
var u32: uint32 = 4294967295;
var u64: uint64 = 18446744073709551615;

// Collections
var list: [int] = [1, 2, 3];
var dict: {str: int} = {"a": 1, "b": 2};
var tuple: (int, str, bool) = (42, "hello", true);
```

### Type Aliases
```limit
// Simple type alias
type UserId = int;
type Email = str;

// Union type alias
type NumberTypes = int | float;
type Response = Success(str) | Error(str) | Pending;

// Refined type alias
type PositiveInt = int where value > 0;
type ValidAge = int where value > 0 where value < 150;
```

---

## Control Flow

### If/Else Statements
```limit
if (condition) {
    // code
} elif (other_condition) {
    // code
} else {
    // code
}
```

### While Loops
```limit
while (condition) {
    // code
}
```

### For Loops
```limit
// C-style for loop
for (var i = 0; i < 10; i = i + 1) {
    print("i: {i}");
}

// For loop with step
for (var i = 0; i < 100; i = i + 5) {
    print("i: {i}");
}
```

### Iterator Loops
```limit
// Range iteration
iter (i in 0..10) {
    print("i: {i}");
}

// Collection iteration
var items = [1, 2, 3, 4, 5];
iter (item in items) {
    print("item: {item}");
}

// Nested iteration
iter (i in 0..3) {
    iter (j in 0..3) {
        print("({i}, {j})");
    }
}
```

### Break and Continue
```limit
while (true) {
    if (condition) {
        break;  // Exit loop
    }
    if (skip_condition) {
        continue;  // Skip to next iteration
    }
}
```

---

## Functions

### Function Declaration
```limit
// Basic function
fn add(a: int, b: int): int {
    return a + b;
}

// Function with no return
fn greet(name: str) {
    print("Hello, {name}!");
}

// Function with no parameters
fn getCurrentTime(): int {
    return 0;
}
```

### Optional Parameters
```limit
fn greet(name: str, greeting: str?): str {
    if (greeting == nil) {
        return "Hello, {name}!";
    } else {
        return greeting + ", {name}!";
    }
}

// Call with optional parameter
var msg1 = greet("Alice");
var msg2 = greet("Bob", "Hi");
```

### Default Parameters
```limit
fn greet(name: str, greeting: str = "Hello"): str {
    return greeting + ", {name}!";
}

// Call with default
var msg1 = greet("Alice");           // Uses default
var msg2 = greet("Bob", "Hi");       // Overrides default
```

### Function Calls
```limit
// Simple call
var result = add(5, 3);

// Nested calls
var result = add(multiply(2, 3), 4);

// With variables
var x = 10;
var y = 20;
var sum = add(x, y);
```

### Recursion
```limit
fn factorial(n: int): int {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}
```

---

## Collections

### Lists
```limit
// List literal
var numbers = [1, 2, 3, 4, 5];
var strings = ["a", "b", "c"];
var mixed = [1, 2, 3];  // Type inferred as [int]

// Typed list
var typed: [int] = [10, 20, 30];

// Empty list
var empty: [int] = [];

// List access
var first = numbers[0];
var second = numbers[1];

// List assignment
numbers[0] = 100;
```

### Dictionaries
```limit
// Dictionary literal
var ages = {"Alice": 25, "Bob": 30, "Charlie": 35};
var scores = {1: 95.5, 2: 87.2, 3: 92.8};

// Typed dictionary
var typed: {str: int} = {"a": 1, "b": 2};

// Empty dictionary
var empty: {str: int} = {};

// Dictionary access
var alice_age = ages["Alice"];
var score1 = scores[1];

// Dictionary assignment
ages["Alice"] = 26;
```

### Tuples
```limit
// Tuple literal
var point = (10, 20);
var person = ("Alice", 25, true);

// Typed tuple
var typed: (int, str, bool) = (42, "hello", true);

// Tuple access
var x = point[0];
var y = point[1];
```

### Ranges
```limit
// Range literal
var range1 = 0..10;      // 0 to 9
var range2 = 1..100;     // 1 to 99

// Range in iteration
iter (i in 0..10) {
    print("i: {i}");
}
```

---

## String Operations

### String Literals
```limit
var simple = "hello";
var empty = "";
var with_escape = "line1\nline2";
```

### String Interpolation
```limit
var name = "World";
var age = 25;

// Basic interpolation
print("Hello, {name}!");

// Expression interpolation
print("Age: {age + 1}");

// Multiple expressions
print("{name} is {age} years old");

// Complex expressions
var x = 10;
var y = 20;
print("Sum: {x + y}, Product: {x * y}");
```

### String Concatenation
```limit
var greeting = "Hello" + " " + "World";
var message = "Value: " + 42;
```

### String Functions
```limit
// Length (when implemented)
var len = length("hello");  // 5

// Substring (when implemented)
var sub = substring("hello", 0, 3);  // "hel"
```

---

## Type System

### Primitive Types
```limit
// Integer types
var i: int = 42;
var i8: int8 = 127;
var i16: int16 = 32767;
var i32: int32 = 2147483647;
var i64: int64 = 9223372036854775807;
var i128: int128 = 170141183460469231731687303715884105727;

// Unsigned integer types
var u: uint = 42;
var u8: uint8 = 255;
var u16: uint16 = 65535;
var u32: uint32 = 4294967295;
var u64: uint64 = 18446744073709551615;
var u128: uint128 = 340282366920938463463374607431768211455;

// Floating point types
var f32: float32 = 3.14;
var f64: float64 = 3.14159265359;

// Boolean and string
var b: bool = true;
var s: str = "hello";
```

### Union Types
```limit
// Basic union
type Result = Success | Error | Pending;

// Union with associated values
type Response = Ok(int) | Err(str) | Timeout;

// Union variable
var result: Response = Ok(42);
var error: Response = Err("Failed");
```

### Option Types
```limit
// Option type (Some | None)
var maybe_value: int? = 42;
var nothing: int? = nil;

// Using option
if (maybe_value != nil) {
    print("Value: {maybe_value}");
}
```

### Refined Types
```limit
// Basic refined type
type PositiveInt = int where value > 0;
type LargeInt = int where value > 100;

// Refined type with operators
type EvenNumber = int where value % 2 == 0;
type OddNumber = int where value % 2 != 0;

// Complex refined type
type DoubleDigit = int where value > 10 * 2;
type ValidAge = int where value > 0 where value < 150;

// String refined type
type NonEmptyString = str where length(value) > 0;
type LongString = str where length(value) > 10;

// Using refined types
var pos: PositiveInt = 42;
var even: EvenNumber = 10;
var age: ValidAge = 25;
```

### Enums
```limit
// Basic enum
enum Color {
    Red,
    Green,
    Blue
}

// Enum with associated values
enum Result {
    Success(str),
    Error(str),
    Pending
}

// Enum with multiple values
enum Event {
    Click(int, int),
    Scroll(int),
    KeyPress(str)
}

// Using enums
var color: Color = Red;
var result: Result = Success("Done");
var event: Event = Click(100, 200);
```

### Discriminated Unions
```limit
// Named variants
type Response = Success(str) | Error(str) | Pending;
type Command = Start | Stop | Pause | Resume;
type Message = Text(str) | Number(int) | Flag | Empty;

// Using discriminated unions
var resp: Response = Success("OK");
var cmd: Command = Start;
var msg: Message = Text("Hello");
```

---

## Pattern Matching

### Basic Pattern Matching
```limit
match (value) {
    pattern1 => { /* code */ },
    pattern2 => { /* code */ },
    _ => { /* default */ }
}
```

### Enum Pattern Matching
```limit
enum Color { Red, Green, Blue }

match (color) {
    Red => { print("Red"); },
    Green => { print("Green"); },
    Blue => { print("Blue"); }
}
```

### Enum with Associated Values
```limit
enum Result {
    Success(str),
    Error(str),
    Pending
}

match (result) {
    Success(msg) => { print("Success: {msg}"); },
    Error(msg) => { print("Error: {msg}"); },
    Pending => { print("Pending..."); }
}
```

### Union Pattern Matching
```limit
type Response = Ok(int) | Err(str) | Timeout;

match (response) {
    Ok(value) => { print("Value: {value}"); },
    Err(msg) => { print("Error: {msg}"); },
    Timeout => { print("Timeout"); }
}
```

### Wildcard Pattern
```limit
match (value) {
    specific_value => { /* handle specific */ },
    _ => { /* handle all others */ }
}
```

### Exhaustiveness Checking
```limit
// All variants must be covered
enum Status { Active, Inactive, Pending }

match (status) {
    Active => { /* ... */ },
    Inactive => { /* ... */ },
    Pending => { /* ... */ }
    // No default needed - all cases covered
}
```

---

## Modules

### Module Declaration
```limit
// In file: math_module.lm
fn add(a: int, b: int): int {
    return a + b;
}

fn multiply(a: int, b: int): int {
    return a * b;
}
```

### Import Statements
```limit
// Basic import
import math_module;

// Import with alias
import math_module as math;

// Import with show filter
import math_module show add, multiply;

// Import with hide filter
import math_module hide internal_function;

// Multiple imports
import module1;
import module2 as m2;
import module3 show func1, func2;
```

### Using Imported Items
```limit
// Without alias
var result = math_module.add(5, 3);

// With alias
var result = math.add(5, 3);

// With show filter (direct access)
var result = add(5, 3);
```

---

## Concurrency

### Parallel Blocks
```limit
// Parallel execution for CPU-bound tasks using iter
var results = channel();

parallel(cores=4) {
    iter(i in 0..99) {
        results.send(i * 2);
    }
}

// Receive results
iter (result in results) {
    print("Result: {result}");
}
```

**Syntax Notes**:
- `parallel(cores=N)` - Specify number of cores
- `iter(i in range)` - Iterate over range in parallel
- `results.send(value)` - Send value to channel
- `iter (result in channel)` - Receive from channel

### Concurrent Blocks
```limit
// Concurrent execution for I/O-bound tasks using tasks
var results = channel();

concurrent(ch = results, cores = 2) {
    task(i in 1..3) {
        results.send("Task {i} completed");
    }
}

// Receive results
iter (result in results) {
    print("Received: {result}");
}
```

**Syntax Notes**:
- `concurrent(ch = channel, cores = N)` - Specify output channel and cores
- `task(i in range)` - Create concurrent tasks over range
- `results.send(value)` - Send value to channel

### Worker Pattern (Consumer)
```limit
// Worker consumes from input stream
var input_jobs = channel();
var results = channel();

// Seed input channel
input_jobs.send("job1");
input_jobs.send("job2");
input_jobs.close();

concurrent(ch = results, cores = 2) {
    worker(item from input_jobs) {
        results.send("Processed: {item}");
    }
}

// Receive results
iter (result in results) {
    print("Result: {result}");
}
```

**Syntax Notes**:
- `worker(item from input_channel)` - Consume from input channel
- `input_channel.close()` - Signal end of input
- `results.send(value)` - Send processed result

### Channels
```limit
// Create channel
var ch = channel();

// Send value
ch.send(42);

// Close channel (signals end)
ch.close();

// Receive value (in iteration)
iter (value in ch) {
    print("Received: {value}");
}
```

**Syntax Notes**:
- `channel()` - Create new channel
- `ch.send(value)` - Send value through channel
- `ch.close()` - Close channel (no more sends)
- `iter (value in ch)` - Iterate over channel values

---

## Error Handling

### Error Union Types
```limit
// Generic error type (Type?)
fn divide(a: int, b: int): int? {
    if (b == 0) {
        return err();
    }
    return ok(a / b);
}

// Specific error types (Type?ErrorType)
fn safeDivide(a: int, b: int): int?DivisionByZero {
    if (b == 0) {
        return err(DivisionByZero);
    }
    return ok(a / b);
}
```

### Error Propagation
```limit
// Using ? operator
fn process(): int? {
    var result = divide(10, 2)?;  // Propagate error if present
    return ok(result * 2);
}

// With error handling
fn processWithHandler(): int? {
    var result = divide(10, 0)? else {
        print("Division failed");
        return ok(0);
    };
    return ok(result);
}
```

### Error Matching
```limit
fn handleResult(result: int?): str {
    match (result) {
        ok(value) => { return "Success: {value}"; },
        err => { return "Error occurred"; }
    }
}
```

### Built-in Error Types
```limit
// Common error types
DivisionByZero
IndexOutOfBounds
KeyNotFound
TypeMismatch
NullPointer
IOError
NetworkError
PermissionDenied
Overflow
Timeout
```

---

## Object-Oriented Features

### Frame Declaration
```limit
frame Person {
    name: str,
    age: int,
    active: bool
}

// Create instance
var person = Person {
    name: "Alice",
    age: 25,
    active: true
};

// Access fields
var name = person.name;
var age = person.age;
```

### Frame with Methods
```limit
frame Calculator {
    value: int
}

// Method (when implemented)
fn add(self: Calculator, x: int): int {
    return self.value + x;
}
```

### Trait Declaration
```limit
trait Drawable {
    fn draw();
}

trait Comparable {
    fn compare(other);
}
```

### Trait Implementation
```limit
frame Shape {
    width: int,
    height: int
}

// Implement trait (when fully implemented)
// impl Drawable for Shape { ... }
```

### Visibility Modifiers
```limit
frame Person {
    @public name: str,
    @private age: int,
    @protected email: str
}
```

---

## Advanced Features

### Closures (Planned)
```limit
// Lambda functions (when implemented)
var add = fn(a: int, b: int): int { return a + b; };
var result = add(5, 3);
```

### Higher-Order Functions (Planned)
```limit
// Functions as parameters (when implemented)
fn apply(f: fn(int): int, x: int): int {
    return f(x);
}
```

---

## Common Patterns

### Null Checking
```limit
var maybe_value: int? = 42;

if (maybe_value != nil) {
    print("Value: {maybe_value}");
} else {
    print("No value");
}
```

### Type Checking
```limit
var value: int | str = 42;

match (value) {
    int_val => { print("Integer: {int_val}"); },
    str_val => { print("String: {str_val}"); }
}
```

### Collection Iteration
```limit
var items = [1, 2, 3, 4, 5];

iter (item in items) {
    print("Item: {item}");
}
```

### Dictionary Iteration
```limit
var map = {"a": 1, "b": 2, "c": 3};

iter (key in map) {
    print("Key: {key}");
}
```

### Error Handling Pattern
```limit
fn safeOperation(): int? {
    var result = riskyOperation()?;
    return ok(result * 2);
}
```

---

## Best Practices

### Naming Conventions
- **Variables**: `snake_case` (e.g., `user_name`, `total_count`)
- **Functions**: `snake_case` (e.g., `calculate_sum`, `process_data`)
- **Types**: `PascalCase` (e.g., `UserId`, `Response`)
- **Constants**: `UPPER_SNAKE_CASE` (e.g., `MAX_SIZE`, `DEFAULT_TIMEOUT`)
- **Enums**: `PascalCase` (e.g., `Color`, `Status`)

### Code Organization
```limit
// 1. Imports
import module1;
import module2 as m2;

// 2. Type definitions
type UserId = int;
enum Status { Active, Inactive }

// 3. Function definitions
fn process(data: str): int {
    // implementation
}

// 4. Main logic
var result = process("data");
print("Result: {result}");
```

### Error Handling
- Always handle error unions with pattern matching
- Use specific error types when possible
- Propagate errors with `?` operator
- Provide meaningful error messages

### Type Safety
- Use type annotations for function parameters
- Use refined types for constraints
- Use union types for multiple possibilities
- Use option types for nullable values

---

## Syntax Checklist for New Features

When implementing a new language feature, add it to this document with:

- [ ] Feature name and description
- [ ] Syntax examples
- [ ] Type annotations (if applicable)
- [ ] Pattern matching support (if applicable)
- [ ] Collection support (if applicable)
- [ ] Function integration (if applicable)
- [ ] Error handling (if applicable)
- [ ] Test file reference
- [ ] Implementation status

---

## Feature Implementation Status

| Feature | Status | Test File |
|---------|--------|-----------|
| Variables | ✅ | tests/types/basic.lm |
| Functions | ✅ | tests/functions/basic.lm |
| Control Flow | ✅ | tests/basic/control_flow.lm |
| Collections | ✅ | tests/basic/list_dict_tuple.lm |
| Strings | ✅ | tests/strings/interpolation.lm |
| Type Aliases | ✅ | tests/types/advanced.lm |
| Union Types | ✅ | tests/types/unions.lm |
| Option Types | ✅ | tests/types/options.lm |
| Enums | ✅ | tests/types/enums.lm |
| Refined Types | ✅ | tests/types/refined_types.lm |
| Discriminated Unions | ✅ | tests/types/discriminated_unions.lm |
| Pattern Matching | ✅ | tests/types/unions.lm |
| Modules | ✅ | tests/modules/basic_import_test.lm |
| Parallel Blocks | ✅ | tests/concurrency/parallel_blocks.lm |
| Concurrent Blocks | ✅ | tests/concurrency/concurrent_blocks.lm |
| Error Handling | 🔄 | tests/error_handling/basic_error_checks.lm |
| Frames/Classes | 🔄 | tests/oop/frame_syntax_only.lm |
| Traits | 🔄 | tests/oop/traits_dynamic.lm |

**Legend**: ✅ Implemented | 🔄 In Progress | 📋 Planned

---

## Related Documentation

- `workflow.md` - Development workflow and phases
- `vm_implementation.md` - VM architecture and implementation
- `testing.md` - Testing strategy and guidelines
- `tech.md` - Technology stack and build system
- `structure.md` - Project structure
- `language_design.md` - Language design principles
---

## Last Updated

- **Date**: March 27, 2026
- **Version**: 1.0
- **Coverage**: 100% of implemented features
- **Test Files**: 60+ comprehensive tests

---

## How to Update This Document

When adding a new language feature:

1. Add syntax examples to appropriate section
2. Include type annotations
3. Show common patterns
4. Reference test file
5. Update feature status table
6. Update last updated date
7. Ensure examples are tested and working


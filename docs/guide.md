# The Limit Programming Language: A Step-by-Step Guide

Welcome to the official guide for the Limit programming language. This document will walk you through the core features of the language, from basic syntax to advanced concepts like structured concurrency.

## Table of Contents

1.  [Getting Started](#getting-started)
    *   [Building and Running Limit](#building-and-running-limit)
2.  [Basic Syntax](#basic-syntax)
    *   [Variables](#variables)
    *   [Primitive Types](#primitive-types)
    *   [Comments](#comments)
    *   [Print Statements](#print-statements)
    *   [String Interpolation](#string-interpolation)
3.  [Control Flow](#control-flow)
    *   [If-Else Statements](#if-else-statements)
    *   [For Loops](#for-loops)
    *   [While Loops](#while-loops)
    *   [Iter Loops](#iter-loops)
    *   [Match Statements](#match-statements)
4.  [Data Structures](#data-structures)
    *   [Lists](#lists)
    *   [Dictionaries](#dictionaries)
5.  [Functions](#functions)
    *   [Defining Functions](#defining-functions)
    *   [Parameters](#parameters)
    *   [Return Values](#return-values)
    *   [Optional Parameters](#optional-parameters)
    *   [Default Parameters](#default-parameters)
    *   [Higher-Order Functions](#higher-order-functions)
    *   [Closures](#closures)
6.  [Classes](#classes)
    *   [Defining Classes](#defining-classes)
    *   [Fields and Methods](#fields-and-methods)
    *   [The `init` Constructor](#the-init-constructor)
    *   [The `self` Keyword](#the-self-keyword)
    *   [Inheritance](#inheritance)
    *   [Method Overriding](#method-overriding)
    *   [The `super` Keyword](#the-super-keyword)
    *   [Polymorphism](#polymorphism)
7.  [Modules and Imports](#modules-and-imports)
    *   [Defining a Module](#defining-a-module)
    *   [Importing a Module](#importing-a-module)
    *   [Import with an Alias](#import-with-an-alias)
    *   [Importing Specific Symbols](#importing-specific-symbols)
    *   [Hiding Imported Symbols](#hiding-imported-symbols)
8.  [The Type System](#the-type-system)
    *   [Type Aliases](#type-aliases)
    *   [Union Types](#union-types)
    *   [Optional Values and Error Handling](#optional-values-and-error-handling)
    *   [The Unified `Type?` System](#the-unified-type-system)
    *   [The `?` Operator](#the--operator)
9.  [Concurrency](#concurrency)
    *   [Structured Concurrency](#structured-concurrency)
    *   [`parallel` Blocks for CPU-Bound Tasks](#parallel-blocks-for-cpu-bound-tasks)
    *   [`concurrent` Blocks for I/O-Bound Tasks](#concurrent-blocks-for-io-bound-tasks)
    *   [Channels](#channels)
    *   [Async/Await](#asyncawait)
    *   [Atomics](#atomics)

---

## Getting Started

This section covers how to build the Limit compiler and run Limit programs.

### Building and Running Limit

**Prerequisites:**
- CMake 3.10 or higher
- A C++17 compatible compiler

**Build Instructions:**

You can build the project using CMake, a Windows batch script, or a Unix shell script.

*   **Using CMake (recommended for cross-platform):**
    ```bash
    mkdir build && cd build
    cmake ..
    make
    ```

*   **Using Windows Batch (MSYS2/MinGW64):**
    ```bash
    build.bat
    ```

*   **Using Unix Shell:**
    ```bash
    ./build.sh
    ```

**Running the Interpreter:**

The `limitly` executable is the interpreter for the Limit language. It can be used to execute source files, inspect the compilation process, or start an interactive session (REPL).

*   **Execute a source file:**
    ```bash
    ./limitly your_script.lm
    ```

*   **Print the tokens (from the scanner):**
    ```bash
    ./limitly -tokens your_script.lm
    ```

*   **Print the Abstract Syntax Tree (AST):**
    ```bash
    ./limitly -ast your_script.lm
    ```

*   **Print the bytecode:**
    ```bash
    ./limitly -bytecode your_script.lm
    ```

*   **Start the REPL (interactive mode):**
    ```bash
    ./limitly -repl
    ```

## Basic Syntax

This section covers the fundamental syntax of the Limit language.

### Variables

Variables are declared using the `var` keyword. While the compiler can infer types, it is good practice to use explicit type annotations.

```
// Declare a variable with a type annotation
var x: int = 10;
print(x); // Output: 10

// Reassign the variable
x = 20;
print(x); // Output: 20
```

You can also declare multiple variables in a sequence.

```
var a: int = 1;
var b: int = 2;
var c: int = 3;
```

### Primitive Types

Limit has several built-in primitive types:

*   **`int`**: A signed integer (e.g., `10`, `-5`, `0`).
*   **`uint`**: An unsigned integer.
*   **`float`**: A floating-point number (e.g., `3.14`, `-0.01`).
*   **`bool`**: A boolean value, which can be `true` or `false`.
*   **`str`**: A string of characters (e.g., `"Hello, World!"`).
*   **`nil`**: A special value representing "nothing" or "null".

```
var my_integer: int = 42;
var my_float: float = 3.14;
var my_boolean: bool = true;
var my_string: str = "Hello, Limit!";
var my_nil: nil = nil;
```

### Comments

Comments are used to leave notes in the code. Single-line comments start with `//`.

```
// This is a single-line comment.
var x = 1; // This comment is at the end of a line.
```

### Print Statements

The `print()` function is used to display output to the console.

```
print("Hello, World!");

var name = "Limit";
print(name);

print(10 + 5); // You can print the result of expressions
```

### String Interpolation

You can embed expressions directly into strings using curly braces `{}`.

```
var name = "Jules";
var year = 2025;

print("Hello, {name}!"); // Output: Hello, Jules!
print("The year is {year}."); // Output: The year is 2025.

var a = 5;
var b = 10;
print("The sum of {a} and {b} is {a + b}."); // Output: The sum of 5 and 10 is 15.
```

## Control Flow

Limit provides several constructs for controlling the flow of execution in your programs.

### If-Else Statements

`if` statements allow you to execute code conditionally. You can also use `else if` and `else` to handle alternative conditions.

```
var score = 85;

if (score >= 90) {
    print("Grade: A");
} else if (score >= 80) {
    print("Grade: B"); // This will be executed
} else {
    print("Grade: C or lower");
}
```

Boolean logic can be used in conditions with the `and`, `or`, and `not` (`!`) operators.

```
var isActive = true;
var isMember = false;

if (isActive and isMember) {
    print("Welcome, active member!");
}

if (isActive or isMember) {
    print("Thank you for your interest!");
}

if (!isMember) {
    print("Please consider becoming a member.");
}
```

### For Loops

Limit supports C-style `for` loops, which consist of an initializer, a condition, and an incrementor.

```
// Loop from 0 to 4
for (var i = 0; i < 5; i += 1) {
    print("i = {i}");
}

// Countdown from 3 to 1
for (var j = 3; j > 0; j -= 1) {
    print("j = {j}");
}
```

### While Loops

`while` loops execute a block of code as long as a condition is true.

```
var count = 0;
while (count < 3) {
    print("count = {count}");
    count += 1;
}
```

You can use `break` to exit a loop early and `continue` to skip to the next iteration.

```
var i = 0;
while (i < 10) {
    if (i == 5) {
        break; // Exit the loop when i is 5
    }
    i += 1;
    if (i % 2 == 0) {
        continue; // Skip even numbers
    }
    print(i); // Prints 1, 3
}
```

### Iter Loops

The `iter` loop is a modern way to iterate over ranges. The range `start..end` is inclusive of `start` and exclusive of `end`.

```
// Iterate from 1 to 4
iter (i in 1..5) {
    print("i = {i}");
}
```

### Match Statements

The `match` statement is a powerful tool for pattern matching. It can be used as an advanced `switch` statement.

A `match` statement can match against literal values:

```
var x = 2;
match (x) {
    1 => { print("One"); },
    2 => { print("Two"); }, // This branch is executed
    _ => { print("Something else"); } // The `_` is a wildcard
}
```

It can also match based on type:

```
fn printType(value) {
    match (value) {
        int => { print("It's an integer."); },
        str => { print("It's a string."); },
        _   => { print("It's some other type."); }
    }
}

printType(10);     // Output: It's an integer.
printType("hello"); // Output: It's a string.
```

You can add conditions to your patterns using `where` guards:

```
var value = 15;
match (value) {
    x where x > 10 => { print("{x} is greater than 10"); },
    x where x < 10 => { print("{x} is less than 10"); },
    _              => { print("It must be 10"); }
}
```

## Data Structures

Limit provides built-in support for common data structures.

### Lists

A list is an ordered collection of values. Lists are created using square brackets `[]`.

```
var numbers = [1, 2, 3, 4, 5];
var mixed = [1, "two", true]; // Lists can hold different types
```

You can access elements in a list using zero-based indexing.

```
var fruits = ["apple", "banana", "cherry"];
print(fruits[0]); // Output: apple
print(fruits[2]); // Output: cherry
```

### Dictionaries

A dictionary is an unordered collection of key-value pairs. Dictionaries are created using curly braces `{}`.

```
var person = {
    "name": "Alice",
    "age": 30,
    "city": "New York"
};
```

You can access values in a dictionary using their keys.

```
print(person["name"]); // Output: Alice
print(person["age"]);  // Output: 30
```

## Functions

Functions are fundamental building blocks in Limit. They allow you to group code into reusable blocks.

### Defining Functions

Functions are defined using the `fn` keyword.

```
fn sayHello() {
    print("Hello, from a function!");
}

// Call the function
sayHello();
```

### Parameters

Functions can accept parameters. You must specify the type of each parameter.

```
fn greet(name: str) {
    print("Hello, {name}!");
}

greet("Alice"); // Output: Hello, Alice!
```

### Return Values

Functions can return a value using the `return` keyword. The return type must be specified after the parameter list.

```
fn add(a: int, b: int): int {
    return a + b;
}

var sum: int = add(5, 10);
print(sum); // Output: 15
```

### Optional Parameters

You can make a parameter optional by adding a `?` to its type. Inside the function, you can check if the parameter was provided.

```
fn greet_optional(name: str?) {
    if (name) {
        print("Hello, {name}!");
    } else {
        print("Hello, stranger!");
    }
}

greet_optional("Bob"); // Output: Hello, Bob!
greet_optional();      // Output: Hello, stranger!
```

### Default Parameters

You can assign a default value to a parameter, which will be used if the caller doesn't provide one.

```
fn greet_default(name: str = "World") {
    print("Hello, {name}!");
}

greet_default();          // Output: Hello, World!
greet_default("Alice");   // Output: Hello, Alice!
```

### Higher-Order Functions

Functions are first-class citizens in Limit, which means they can be passed as arguments to other functions.

```
// This function takes another function as a parameter
fn apply(x: int, y: int, operation: fn(int, int): int): int {
    return operation(x, y);
}

fn multiply(a: int, b: int): int {
    return a * b;
}

var result: int = apply(10, 5, multiply);
print(result); // Output: 50
```

### Closures

A function can be defined inside another function. This inner function "captures" the variables from its containing scope, creating a closure.

```
fn createCounter(): fn(): int {
    var count: int = 0;
    fn increment(): int {
        count += 1;
        return count;
    }
    return increment;
}

var counter: fn(): int = createCounter();
print(counter()); // Output: 1
print(counter()); // Output: 2
print(counter()); // Output: 3
```

## Classes

Limit is an object-oriented language and supports classes for creating user-defined types.

### Defining Classes

Classes are defined using the `class` keyword.

```
class Greeter {
    var name: str = "World";

    fn say_hello() {
        print("Hello, {self.name}!");
    }
}

var greeter: Greeter = Greeter();
greeter.say_hello(); // Output: Hello, World!
```

### Fields and Methods

Classes can have both data (fields) and behavior (methods). Fields are variables declared within the class, and methods are functions defined within the class.

### The `init` Constructor

The `init` method is a special method that acts as the class constructor. It is called when a new instance of the class is created.

```
class Person {
    var name: str;
    var age: int;

    fn init(name_param: str, age_param: int) {
        self.name = name_param;
        self.age = age_param;
    }

    fn introduce() {
        print("Hi, I'm {self.name} and I'm {self.age} years old.");
    }
}

var person: Person = Person("Jules", 28);
person.introduce(); // Output: Hi, I'm Jules and I'm 28 years old.
```

### The `self` Keyword

The `self` keyword refers to the current instance of the class. It is used to access the instance's fields and methods.

### Inheritance

A class can inherit from a parent class using the `:` operator. This allows the child class to inherit the fields and methods of the parent.

```
class Animal {
    fn speak() {
        print("The animal makes a sound.");
    }
}

class Dog : Animal {
    // Dog inherits the speak() method from Animal
}

var my_dog: Dog = Dog();
my_dog.speak(); // Output: The animal makes a sound.
```

### Method Overriding

A child class can provide its own implementation of a method that it inherited from its parent.

```
class Cat : Animal {
    fn speak() {
        print("The cat meows.");
    }
}

var my_cat: Cat = Cat();
my_cat.speak(); // Output: The cat meows.
```

### The `super` Keyword

The `super` keyword can be used to call methods from the parent class.

```
class SmartDog : Dog {
    fn speak() {
        super.speak(); // Call the speak() method from the parent (Dog)
        print("Woof woof!");
    }
}

var smart_dog: SmartDog = SmartDog();
smart_dog.speak();
// Output:
// The animal makes a sound.
// Woof woof!
```

### Polymorphism

Polymorphism allows you to treat objects of different classes as objects of a common parent class.

```
var animals: [Animal] = [Dog(), Cat(), Animal()];
iter (animal: Animal in animals) {
    animal.speak();
}
// Output:
// The animal makes a sound.
// The cat meows.
// The animal makes a sound.
```

## Modules and Imports

Limit supports a module system that allows you to organize your code into separate files and reuse code across your project.

### Defining a Module

A module is simply a Limit source file. For example, you could have a file named `my_module.lm` with the following content:

```limit
// my_module.lm
fn greet() {
    print("Hello from my_module!");
}

var my_variable = 123;
```

### Importing a Module

You can import a module using the `import` statement. The module path is specified using dot notation, and it corresponds to the file path. For example, to import `my_module.lm` from the same directory, you would write:

```limit
import my_module;

my_module.greet(); // Output: Hello from my_module!
print(my_module.my_variable); // Output: 123
```

### Import with an Alias

You can provide an alias for an imported module to make it easier to reference.

```limit
import my_module as mod;

mod.greet();
```

### Importing Specific Symbols

If you only need specific functions or variables from a module, you can use the `show` keyword to import only them into the current scope.

```limit
import my_module show greet, my_variable;

greet(); // Directly accessible
print(my_variable);
```

### Hiding Imported Symbols

Conversely, you can use the `hide` keyword to import all symbols from a module *except* for the ones specified.

```limit
import my_module hide my_variable;

greet(); // greet is imported
// my_variable is not imported
```

## The Type System

Limit has a rich type system that allows for creating complex and expressive data structures while maintaining null-safety by design.

### Type Aliases

You can create an alias for an existing type using the `type` keyword. This is useful for making your code more readable.

```limit
type UserID = int;
type Email = str;

var my_id: UserID = 12345;
var my_email: Email = "test@example.com";
```

### Union Types

A union type is a type that can hold a value of one of several different types. Union types are defined using the pipe (`|`) character.

```limit
type Number = int | float;

var my_num: Number = 10;       // This is valid
my_num = 3.14;                 // This is also valid
```

Union types are especially powerful when combined with `match` statements to handle all possible types that a variable could be.

### Optional Values and Error Handling

**Key Design Principle**: Limit is null-free by design. There are no null pointers, null references, or null values. Instead, Limit uses a unified system where "absence of value" is treated as an error condition.

### The Unified `Type?` System

Limit uses a single, unified system for both optional values and error handling:

- **`Type?`** - Represents a value that might be present or absent (absence is an error condition)
- **`Type?ErrorType`** - Represents a value that might succeed or fail with specific error types
- **`ok(value)`** - Creates a success/present value
- **`err()`** - Creates an error/absent value (no nulls - absence is an error)

```limit
// Optional value (might be absent)
fn find_user(id: int): str? {
    if (id == 1) {
        return ok("Alice");  // Present value
    }
    return err();  // Absent value (treated as error, not null)
}

// Specific error types
fn divide(a: int, b: int): int?DivisionByZero {
    if (b == 0) {
        return err(DivisionByZero("Cannot divide by zero"));
    }
    return ok(a / b);
}
```

### Pattern Matching with Optional Values

Use `match` statements to handle both present and absent cases:

```limit
var user = find_user(1);
match user {
    Ok(name) => print("Found user: {name}"),
    Err => print("User not found")  // No null - absence is an error
}

var result = divide(10, 2);
match result {
    Ok(value) => print("Result: {value}"),
    Err => print("Division failed")
}
```


## 🧠 Memory Model

Limitly uses a **region-based, deterministic memory model** designed for **low-level performance** without garbage collection.
All allocation and cleanup are **fully deterministic** and **scope-bound**, but the language automatically manages this through **compiler inference**, not explicit user code.

### Overview

In Limitly, every block of code — whether a function, loop, or local scope — defines a **region**.
A region owns all values created within it, and when that scope ends, the region and all its allocations are **destroyed automatically** in a predictable order.

You never allocate or free memory manually.
Instead, the compiler inserts the appropriate region operations behind the scenes.

```limitly
fn main() {
    var message: str = "Hello Limitly!"
    print(message)
} // region ends here — memory for `message` is deterministically released
```

### How Regions Work

* Each **lexical scope** (function, loop, or block) forms a **region**.
* All variables created inside that scope belong to that region.
* When the scope exits (normally or through error propagation), the region is destroyed.
* Destruction is **deterministic** and happens in **reverse declaration order**.

Nested scopes form **nested regions**, which are cleaned up hierarchically — the inner region is always destroyed before the outer one.

```limitly
fn compute() {
    var data: str = "temporary"
    {
        var temp: str = data
        print(temp)
    } // `temp` destroyed here
    print(data)
} // `data` destroyed here
```

### Compiler-Inserted Memory Operations

Limitly’s compiler internally uses `makeLinear` and `makeRef` to manage memory, but these are **not visible in user code**.
They appear during AST lowering to mark ownership and reference semantics.

* **Linear values** (created internally via `makeLinear`) have single ownership.
  They must be consumed, moved, or destroyed once.
* **References** (created internally via `makeRef`) are safe handles to linear values within the same or outer region.
  They are invalidated automatically when their region ends.

This allows the compiler to reason about lifetimes, avoid dangling references, and ensure every allocation is destroyed exactly once — all without runtime tracing.

### Region Inference

Regions are **implicit**.
The compiler determines where regions begin and end based on lexical scope — you never need to write region code or think about region models directly.

```limitly
fn process() {
    var buffer: str = "data"
    print(buffer)
} // compiler-inferred region ensures `buffer` is released here
```

Because the compiler handles region setup, Limitly behaves like a **manual-memory language with automatic discipline**:
deterministic cleanup, but no runtime cost or garbage collection.

### Deterministic Runtime

Limitly’s runtime is **fully deterministic**.
Since every region is tied to scope lifetime and cleaned up predictably, there’s no background thread, collector, or delayed deallocation queue.
This makes it ideal for **systems programming**, **embedded**, and **real-time** environments where timing precision matters.

The runtime is only a thin layer that orchestrates region destruction when the compiler marks a scope exit — it does not track allocations dynamically.

### Region Safety and Error Propagation

Error propagation integrates directly with the region system.
When an error is propagated (`?`) or handled inline (`?else{}`), all active regions in that scope are cleaned up before control moves.

This guarantees **no leaks** and **no invalid memory access** even in exceptional paths.

```limitly
fn open_file(path: str): File? {
    var f: File = File.open(path) ?else {
        print("Could not open file")
        return None
    }
    return f
} // if `open()` fails, region for `f` is cleaned up before returning
```

### Summary

| Feature                         | Description                                          |
| ------------------------------- | ---------------------------------------------------- |
| **Region-based memory**         | Every scope is a deterministic memory region         |
| **Compiler-managed lifetimes**  | No manual `makeRef` or `makeLinear` calls            |
| **Linear and reference safety** | Ownership and borrowing are verified at compile time |
| **No GC or tracing runtime**    | Cleanup is static and predictable                    |
| **Error-safe regions**          | Errors trigger automatic region cleanup              |

### Why It Matters

This model gives Limitly **predictable performance** and **memory safety** while keeping the syntax clean and intuitive.
It combines the control of C, the safety of Rust, and the simplicity of Swift — but with **no annotations, lifetimes, or garbage collector**.

The result is a **deterministic, region-scoped runtime** that feels automatic yet remains fully transparent and suitable for **system-level** development.





### The `?` Operator

The `?` operator provides a convenient way to **propagate** both errors and absent values. When you append `?` to an expression that returns a `Type?`:

*   If the value is `Ok(value)`, the operator unwraps the value and the program continues.
*   If the value is `Err`, the `?` operator will cause the current function to immediately return that `Err`.

This allows you to write cleaner code by avoiding deeply nested `match` statements when you simply want to pass an error or absent value up the call stack.

```limit
// Function that might fail to parse
fn to_int(s: str): int? {
    // ... implementation that returns ok(parsed_int) or err()
}

// This function uses '?' to propagate errors/absent values from to_int
fn get_number_from_string(s: str): int? {
    var number: int = to_int(s)?; // If to_int returns Err, this function also returns Err

    // This code only runs if to_int was successful
    print("Parsing was successful!");
    return ok(number * 2);
}

// Example usage:
var result1 = get_number_from_string("10"); // result1 will be Ok(20)
var result2 = get_number_from_string("abc"); // result2 will be Err
```

### Inline Error Handling with `? else`

The `? else` construct provides a concise way to handle errors or absent values inline, providing a fallback value without a full `match` statement.

```limit
fn divide(a: int, b: int): int? {
    if (b == 0) {
        return err(); // Division by zero results in absent value (error condition)
    }
    return ok(a / b);
}

// Use `? else` to provide a default value on failure or absence
var value: int = divide(10, 0)? else {
    print("Division failed or result absent");
    return 0; // Default value (not null - Limit is null-free)
};
// `value` will be 0.
```

This syntax is particularly useful for providing default values while maintaining Limit's null-free design principles.

## Concurrency

Limit has powerful, high-level features for managing concurrent and parallel tasks.

### Structured Concurrency

Limit's concurrency model is "structured," which means that the lifetime of concurrent tasks is tied to a specific block of code. When the block finishes, all the tasks spawned within it are guaranteed to be completed. This eliminates many common concurrency bugs, such as leaked threads.

### `parallel` Blocks for CPU-Bound Tasks

`parallel` blocks are designed for CPU-bound workloads, where you want to take full advantage of multiple CPU cores.

```
// Create a channel to receive messages from the tasks
var messages = channel();

// This block will run tasks on multiple cores
parallel(ch=messages, mode=batch) {
    task(i in 1..4) {
        print("Running task {i}...");
        // Perform some CPU-intensive work here
        messages.send("Task {i} is done.");
    }
}

// The block will wait for all tasks to finish
print("All parallel tasks are complete.");

// Process the results
iter (message in messages) {
    print("Received: {message}");
}
```

### `concurrent` Blocks for I/O-Bound Tasks

`concurrent` blocks are designed for I/O-bound workloads, such as waiting for network requests or reading from files. These tasks can be run efficiently on a smaller number of threads because they spend most of their time waiting.

```
var results = channel();

concurrent(ch=results, mode=batch) {
    task() {
        var data = await fetchData(); // Non-blocking network call
        results.send(data);
    }
    task() {
        var file_content = await readFile("data.txt"); // Non-blocking file I/O
        results.send(file_content);
    }
}

print("All concurrent tasks have completed.");
```

### Channels

Channels are the primary way for concurrent tasks to communicate. One or more tasks can send messages to a channel, and another task can receive them.

### Async/Await

The `async` and `await` keywords are used for non-blocking operations, typically within a `concurrent` block. An `async` function returns immediately without blocking the thread, and you can use `await` to get its result when it's ready.

### Atomics

For simple cases of shared state, such as counters, you can use `atomic` variables. These variables can be safely accessed and modified from multiple tasks at the same time without causing data races.

```
var shared_counter: atomic = 0;

concurrent {
    task(i in 1..10) {
        shared_counter += 1; // This is a thread-safe operation
    }
}

print("Final counter value: {shared_counter}"); // Output: 10
```

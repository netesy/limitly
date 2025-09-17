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
8.  [Error Handling](#error-handling)
    *   [The `Option` Type](#the-option-type)
    *   [The `Result` Type](#the-result-type)
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

Limit has a rich type system that allows for creating complex and expressive data structures.

### Type Aliases

You can create an alias for an existing type using the `type` keyword. This is useful for making your code more readable.

```
type UserID = int;
type Email = str;

var my_id: UserID = 12345;
var my_email: Email = "test@example.com";
```

### Union Types

A union type is a type that can hold a value of one of several different types. Union types are defined using the pipe (`|`) character.

```
type Number = int | float;

var my_num: Number = 10;       // This is valid
my_num = 3.14;                 // This is also valid
```

Union types are especially powerful when combined with `match` statements to handle all possible types that a variable could be.

## Error Handling

Limit provides a robust system for handling errors based on the `Option` and `Result` types.

### The `Option` Type

The `Option` type is a union type used to represent a value that could be absent. It has two variants:

*   **`Some`**: Represents the presence of a value.
*   **`None`**: Represents the absence of a value.

This is a safer alternative to using `nil` or `null` because the compiler will force you to handle the `None` case.

```
type IntOption = Some | None;

fn find_user(id: int): IntOption {
    if (id == 1) {
        return Some { value: 42 };
    }
    return None;
}

var user_id = find_user(1);
match (user_id) {
    Some(id) => { print("Found user with ID: {id}"); },
    None     => { print("User not found."); }
}
```

### The `Result` Type

The `Result` type is a union type used for functions that can either succeed or fail. It has two variants:

*   **`Success`**: Represents a successful outcome, containing a value.
*   **`Error`**: Represents a failure, containing an error value.

```
type DivisionResult = Success | Error;

fn divide(numerator: int, denominator: int): DivisionResult {
    if (denominator == 0) {
        return Error { error: "Division by zero!" };
    }
    return Success { value: numerator / denominator };
}

var result = divide(10, 2);
match (result) {
    Success(value) => { print("Result: {value}"); },
    Error(err)     => { print("Error: {err}"); }
}
```

### The `?` Operator

The `?` operator provides a convenient way to **propagate** errors. When you append `?` to an expression that returns a `Result` or an `Option`:

*   If the value is a `Success` or `Some`, the operator unwraps the value and the program continues.
*   If the value is an `Error` or `None`, the `?` operator will cause the current function to immediately return that `Error` or `None`.

This allows you to write cleaner code by avoiding deeply nested `match` statements when you simply want to pass an error up the call stack.

```
// Assume this function exists and can fail
fn to_int(s: str): Result<int, str> {
    // ... implementation ...
}

// This function uses '?' to propagate the error from to_int
fn get_number_from_string(s: str): Result<int, str> {
    var number: int = to_int(s)?; // If to_int returns an Error, this function also returns it.

    // This code only runs if to_int was successful
    print("Parsing was successful!");
    return Success(number * 2);
}

// Example usage:
var result1 = get_number_from_string("10"); // result1 will be Success(20)
var result2 = get_number_from_string("abc"); // result2 will be Error(...)
```

### Inline Error Handling with `? else`

The `? else error` construct provides a concise way to handle an error inline, providing a fallback value or executing a block of code without a full `match` statement.

The expression to the left of the `?` is evaluated. If it is a `Success` or `Some`, the value is unwrapped and assigned. If it is an `Error` or `None`, the `else` block is executed. The `error` variable inside the block is bound to the error value. The value returned from the `else` block is then used as the result of the entire expression.

```limit
fn divide(a: int, b: int): Result<int, str> {
    if (b == 0) {
        return Error("DivisionByZero");
    }
    return Success(a / b);
}

// Use `? else` to provide a default value on failure.
var value: int = divide(10, 0)? else err {
    print("An error occurred: {err}");
    return 0; // Default value
};
// `value` will be 0.
```

This syntax is particularly useful for providing default values or for logging an error while allowing the program to continue with a sensible fallback.

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

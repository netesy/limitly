# 🌟 Welcome to the Limit Language!

Hello, and welcome to the Limit programming language!

**What is Limit?**
Limit is a modern programming language designed to be both powerful and safe. It's a statically-typed language, which means it helps you catch errors early, before you even run your code.

**What can you build with it?**
You can use Limit to build a wide variety of applications, from simple command-line tools to complex, high-performance systems. Its strong support for concurrency makes it especially great for programs that need to do many things at once.

**What makes it unique?**
Limit's most unique features are its focus on safety and its structured concurrency model. It's designed to help you write code that is less likely to crash and easier to reason about, especially when dealing with multiple tasks at the same time.

**Why choose it over Python, JS, etc.?**
If you're building a large or complex application where performance and correctness are critical, Limit is a great choice. It provides more safety guarantees than dynamically typed languages like Python or JavaScript, which can save you from many common bugs in the long run.

## ⚙️ Installing the Language

To get started with Limit, you'll need to build the interpreter from source. Don't worry, it's easy!

**Prerequisites:**
- CMake 3.10 or higher
- A C++17 compatible compiler (like GCC, Clang, or MSVC)

**Build Instructions:**

*   **On macOS or Linux:**
    ```bash
    # Open your terminal
    make linux
    ```

*   **On Windows (with MSYS2/MinGW64):**
    ```bash
    # Open the command prompt
    build.bat
    ```

After building, you'll have a `limitly` executable in the `bin/` directory. This is the Limit interpreter!

**Verify your installation:**
While there isn't a `--version` command yet, you can test your installation by starting the interactive REPL (Read-Eval-Print Loop):

```bash
./bin/limitly -repl
```

If you see a `>` prompt, you're all set! You can type `exit` to leave the REPL.

## ✍️ Your First Program

Let's write the classic "Hello, world!" program in Limit.

1.  Create a new file named `hello.lm`.
2.  Add the following code to the file:

```limit
// This is your first Limit program!
print("Hello, world!");
```

3.  Save the file and run it from your terminal:

```bash
./bin/limitly hello.lm
```

You should see the following output:
```
Hello, world!
```

**Explanation:**
*   `// This is your first Limit program!` is a comment. Comments are ignored by the interpreter and are used to leave notes for yourself or other programmers.
*   `print(...)` is a built-in function that prints text to the console.
*   `"Hello, world!"` is a string literal. A string is just a sequence of text.

## 🧱 Basic Concepts

Now that you've written your first program, let's learn some of the basic building blocks of the Limit language.

### Variables and Types

A variable is a name that refers to a value. You can create a variable using the `var` keyword. While Limit can sometimes infer the type, it's good practice to be explicit by adding a type annotation.

```limit
var my_age: int = 28;
var my_name: str = "Jules";
```

Limit is a statically-typed language, which means that every variable has a type that is known when you write the code. The basic types are:
*   **`int`**: for integers (e.g., `10`, `-5`).
*   **`float`**: for decimal numbers (e.g., `3.14`).
*   **`bool`**: for `true` or `false`.
*   **`str`**: for strings of text (e.g., `"Hello"`).

### Printing to Console

As you saw in the "Hello, world!" example, you can use the `print()` function to display output. You can also print the value of variables.

```limit
var planet: str = "Earth";
print(planet); // Output: Earth
```

You can even embed variables directly into strings using curly braces `{}`. This is called **string interpolation**.

```limit
var name: str = "Alice";
var age: int = 30;
print("My name is {name} and I am {age} years old.");
// Output: My name is Alice and I am 30 years old.
```

### Comments

Comments are notes that are ignored by the interpreter. They are useful for explaining your code. In Limit, single-line comments start with `//`.

```limit
// This is a comment.
var x = 10; // This is another comment.
```

### Math and Expressions

You can perform mathematical calculations in Limit using the standard arithmetic operators.

```limit
var a = 10;
var b = 5;

print(a + b); // Output: 15
print(a - b); // Output: 5
print(a * b); // Output: 50
print(a / b); // Output: 2
```

### If/Else Statements

`if` statements allow you to run code conditionally.

```limit
var temperature = 25;

if (temperature > 30) {
    print("It's a hot day!");
} else if (temperature > 20) {
    print("It's a nice day.");
} else {
    print("It's a cold day.");
}
```

### Loops (For, While)

Loops allow you to repeat a block of code multiple times.

**`for` loop:**
A C-style `for` loop is useful when you want to loop a specific number of times.

```limit
for (var i = 0; i < 3; i += 1) {
    print("Looping... i = {i}");
}
```

**`while` loop:**
A `while` loop continues as long as a condition is true.

```limit
var count = 3;
while (count > 0) {
    print("{count}...");
    count -= 1;
}
print("Liftoff!");
```

## 🧰 Functions

Functions are reusable blocks of code that you can call by name. They help you organize your code and avoid repetition.

**How to define and call a function:**
You can define a function using the `fn` keyword.

```limit
fn say_hello() {
    print("Hello from a function!");
}

// Call the function
say_hello();
```

**Parameters and return values:**
Functions can take inputs, called **parameters**, and produce an output, called a **return value**. You must specify the type of each parameter and the type of the return value.

```limit
// This function takes a 'name' of type str as a parameter
fn greet(name: str) {
    print("Hello, {name}!");
}

greet("Bob"); // Output: Hello, Bob!

// This function takes two integers and returns an integer
fn add(a: int, b: int): int {
    return a + b;
}

var result: int = add(5, 7);
print("The result is {result}"); // Output: The result is 12
```

## 📦 Organizing Your Code with Modules

As your programs grow larger, you'll want to split your code into multiple files. Limit's module system makes this easy.

A module is just a separate `.lm` file. You can use the `import` keyword to use functions and variables from one file in another.

**Example:**

Let's say you have a file named `greetings.lm`:
```limit
// greetings.lm
fn say_hi() {
    print("Hi there!");
}
```

In your main file, you can import and use the `say_hi` function:
```limit
// main.lm
import greetings;

greetings.say_hi(); // Output: Hi there!
```

This is just a brief introduction. The module system also supports aliasing, and importing or hiding specific parts of a module. To learn more, check out the [**Modules and Imports**](./guide.md#modules-and-imports) section in the full language guide.

## 🧺 Working with Collections

Collections are data structures that can hold multiple values. Limit has two main types of collections: lists and dictionaries.

### Lists/Arrays

A **list** is an ordered collection of items. You can create a list using square brackets `[]`. It's good practice to specify the type of items the list will hold.

```limit
var fruits: [str] = ["apple", "banana", "cherry"];
print(fruits);
```

You can get an item from a list by its **index**. The index is the item's position in the list, starting from 0.

```limit
print(fruits[0]); // Output: apple
print(fruits[2]); // Output: cherry
```

### Maps/Dictionaries

A **dictionary** (or map) is a collection of key-value pairs. You can create a dictionary using curly braces `{}`.

```limit
var person: {str: any} = {
    "name": "Alice",
    "age": 30
};
```

You can get a value from a dictionary by its **key**.

```limit
print(person["name"]); // Output: Alice
```

### Loops over Collections

You can use the `iter` loop to go through each item in a collection.

```limit
var colors: [str] = ["red", "green", "blue"];

iter (color: str in colors) {
    print("Color: {color}");
}
```

## 🧱 Object-Oriented Programming with Frames

Limit uses **frames** for object-oriented programming. A frame is a blueprint for creating objects that bundle data and behavior.

```limit
frame Greeter {
    pub var name: str = "World";

    pub fn say_hello() {
        print("Hello, {this.name}!");
    }
}

var greeter = Greeter();
greeter.say_hello(); // Output: Hello, World!
```

Wait, what is `this`? Inside a frame's method, `this` refers to the specific object you are working with. You can also use `self` if you prefer - Limit supports both!

## 🧪 Errors and Optional Values

In Limit, errors and absent values are not seen as crashes, but as a normal part of a program's flow that you should plan for. The language gives you powerful tools to handle situations where things might go wrong or where values might be absent.

**Key Principle**: Limit is designed to be safe. We use a unified system where potential failure is represented in the type itself.

### The Unified Error and Optional Value System

Limit uses a single system for both error handling and optional values:
- **`Type?`** represents a value that might be present or absent/error.
- **`ok(value)`** creates a success value.
- **`err()`** creates an error or "absent" value.

### Handling Errors with `match`

When you have a function that might fail or return an absent value, you can use a `match` statement to handle both possibilities:

```limit
fn might_fail(): int? {
    // This function might return a value or be absent
    return err(); 
}

fn do_something(): int? {
    var result = might_fail();
    
    match result {
        Ok(value) => {
            print("Got value: {value}");
            return ok(value * 2);
        },
        Err => {
            print("No value available");
            return err();
        }
    }
}
```

### Propagating Errors with `?`

The `?` operator is a shortcut for passing errors up the line:

```limit
fn might_fail(): int? {
    return err();
}

fn do_something(): int? {
    // If might_fail() returns Err, '?' immediately returns it from do_something()
    var result: int = might_fail()?;

    print("It worked!");
    return ok(result);
}
```

### Inline Error Handling with `? else`

Handle errors or absent values inline with a fallback value:

```limit
fn divide(a: int, b: int): int? {
    if (b == 0) {
        return err(); 
    }
    return ok(a / b);
}

// Provide a default value if division fails
var result: int = divide(10, 0)? else {
    print("Division failed");
    return -1; 
};

print("The final result is: {result}"); // Output: The final result is: -1
```

## 🚀 Mini Project: Number Guessing Game

Now it's time to put everything you've learned together! Let's build a simple number guessing game.

```limit
// --- Number Guessing Game ---

// Assuming built-in helpers
// fn read_line(): str { ... }
// fn to_int(s: str): int? { ... }

var secret_number: int = 7; 
print("I'm thinking of a number. Guess what it is!");

loop { 
    print("Please input your guess:");
    var input_str: str = "7"; // Simulating input

    var guess_result: int? = to_int(input_str);

    match (guess_result) {
        Ok(guess) => {
            print("You guessed: {guess}");
            if (guess < secret_number) {
                print("Too low!");
            } else if (guess > secret_number) {
                print("Too high!");
            } else {
                print("You win!");
                break; 
            }
        },
        Err => {
            print("That's not a number! Please try again.");
        }
    }
    break;
}
```

## 📎 Next Steps / Resources

Congratulations! You've learned the fundamentals of the Limit language.

*   **Full Language Guide:** For a more in-depth look: [**Full Language Guide**](./guide.md).
*   **Language Specification:** Formal details: [**Language Spec**](./language.md).
*   **The Zen of Limit:** Our design philosophy: [**The Zen of Limit**](./zen.md).
*   **Explore the Code:** Check out the `tests/` directory to see examples of every feature in action.

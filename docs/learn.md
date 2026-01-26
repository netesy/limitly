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
    make
    ```

*   **On Windows (with MSYS2/MinGW64):**
    ```bash
    # Open the command prompt
    build.bat
    ```

After building, you'll have a `limitly` executable. This is the Limit interpreter!

**Verify your installation:**
While there isn't a `--version` command yet, you can test your installation by starting the interactive REPL (Read-Eval-Print Loop):

```bash
./limitly -repl
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
./limitly hello.lm
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


## 🧪 Errors and Optional Values

In Limit, errors and absent values are not seen as crashes, but as a normal part of a program's flow that you should plan for. The language gives you powerful tools to handle situations where things might go wrong or where values might be absent.

**Key Principle**: Limit is null-free by design. There are no null pointers or null references. Instead, we use a unified system where "absence of value" is treated as an error condition.

There are two main ways to deal with potential errors or absent values: **handling** them immediately with a `match` statement, or **propagating** (passing) them up to the function that called your function.

### The Unified Error and Optional Value System

Limit uses a single system for both error handling and optional values:
- **`Type?`** represents a value that might be present or absent (where absence is an error condition)
- **`Type?ErrorType`** represents a value that might succeed or fail with specific error types
- **`ok(value)`** creates a success/present value
- **`err()`** creates an error/absent value (no nulls - absence is an error)

### Handling Errors and Optional Values

When you call a function that returns a `Type?`, you can check if it returned a value or an error using a simple `if` statement, because `Type?` values can be used in boolean contexts.

```limit
fn might_fail(): int? {
    // This function might return a value or be absent (error condition)
    return err(); // Absence is treated as an error
}

fn do_something() {
    var result = might_fail();
    
    if (result) {
        print("Got value: {result}");
    } else {
        print("No value available");
    }
}
```

### Propagating Errors with `?`

If you don't want to handle an error right away, you can use the `?` operator to pass it up to the function that called yours.

```limit
fn might_fail(): int? {
    return err(); // Absent value (treated as error)
}

fn do_something_else(): int? {
    // If might_fail() returns an error, the '?' will immediately
    // stop do_something_else() and return that same error.
    var result: int = might_fail()?;

    // This part only runs if might_fail() had a value
    print("It worked!");
    return ok(result);
}
```

### Inline Error Handling with `? else`

You can also handle an error on a single line with `? else`, which is useful for providing a default value.

```limit
fn divide(a: int, b: int): int? {
    if (b == 0) {
        return err(); // Division by zero is an error
    }
    return ok(a / b);
}

// Provide a default value if division fails
var result: int = divide(10, 0)? else {
    print("Division failed!");
    return -1; // Default value
};

print("The final result is: {result}"); // Output: The final result is: -1
```

## 🚀 Mini Project: A Simple Function

Let's write a program that uses a function with optional parameters to greet a user. This will demonstrate how to handle values that may or may not be present.

```limit
// --- Greeting Program ---

fn greet(name: str?) {
    if (name) {
        print("Hello, {name}!");
    } else {
        print("Hello, stranger!");
    }
}

// --- Main Code ---

greet("Alice"); // Prints "Hello, Alice!"
greet(nil);     // Prints "Hello, stranger!"
```

**How it works:**
*   **Optional Parameter:** The `greet` function takes an optional string `name: str?`. This means you can call it with a string or with `nil`.
*   **Checking for a Value:** The `if (name)` statement checks if a name was provided. If `name` is not `nil`, the condition is true.

**Your Challenge:**
*   Can you modify the `greet` function to have a default name, like "World", if no name is provided? (Hint: Look at the `Default Parameters` section in the full guide).

## 📎 Next Steps / Resources

Congratulations on completing this beginner's guide! You've learned the fundamentals of the Limit language.

Here are some resources to help you continue your journey:

*   **Full Language Guide:** For a more in-depth look at all of Limit's features, check out the [**Full Language Guide**](./guide.md).
*   **The Zen of Limit:** To understand the philosophy behind the language, read [**The Zen of Limit**](./zen.md).
*   **Limit vs. Python:** To see how Limit compares to a popular dynamic language, check out our [**Limit vs. Python Comparison**](./limit_vs_python.md).
*   **Explore the Code:** The best way to learn is to read code! Check out the `tests/` directory in this project to see examples of every feature in action.

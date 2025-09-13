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
    mkdir build
    cd build
    cmake ..
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

A variable is a name that refers to a value. You can create a variable using the `var` keyword.

```limit
var my_age = 28;
var my_name = "Jules";
```

Limit is a statically-typed language, which means that every variable has a type that is known when you write the code. In the example above, `my_age` is an `int` (integer) and `my_name` is a `str` (string). Other basic types include `float` (for decimal numbers) and `bool` (for `true` or `false`).

### Printing to Console

As you saw in the "Hello, world!" example, you can use the `print()` function to display output. You can also print the value of variables.

```limit
var planet = "Earth";
print(planet); // Output: Earth
```

You can even embed variables directly into strings using curly braces `{}`. This is called **string interpolation**.

```limit
var name = "Alice";
var age = 30;
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
Functions can take inputs, called **parameters**, and produce an output, called a **return value**.

```limit
// This function takes a 'name' as a parameter
fn greet(name: str) {
    print("Hello, {name}!");
}

greet("Bob"); // Output: Hello, Bob!

// This function takes two numbers and returns their sum
fn add(a: int, b: int): int {
    return a + b;
}

var result = add(5, 7);
print("The result is {result}"); // Output: The result is 12
```

## 🧺 Working with Collections

Collections are data structures that can hold multiple values. Limit has two main types of collections: lists and dictionaries.

### Lists/Arrays

A **list** is an ordered collection of items. You can create a list using square brackets `[]`.

```limit
var fruits = ["apple", "banana", "cherry"];
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
var person = {
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
var colors = ["red", "green", "blue"];

iter (color in colors) {
    print("Color: {color}");
}
```

## 🧪 Errors and Debugging

When you're programming, you'll inevitably run into errors. Don't worry, it's a normal part of the process!

**What happens when you make a mistake?**
If you make a syntax error (like forgetting a semicolon or a closing brace), the Limit interpreter will usually give you an error message that tells you what went wrong and on which line.

For example, if you forget the closing parenthesis in a `print` statement:
```limit
print("hello"
```
You might see an error like:
`Syntax error: Expected ')' after arguments.`

**Basic debugging tips:**
*   **Read the error message carefully.** It often contains valuable clues about what's wrong.
*   **Print statements are your best friend.** If you're not sure what a variable's value is at a certain point in your program, add a `print()` statement to find out.
*   **Start small.** If you're having trouble with a large piece of code, try to break it down into smaller parts and test each part individually.

## 🚀 Mini Project: Number Guessing Game

Now it's time to put everything you've learned together! Let's build a simple number guessing game.

The goal is for the user to guess a secret number. The program will tell them if their guess is too high or too low until they guess the correct number.

```limit
// --- Number Guessing Game ---

// Let's pretend we have a way to get a random number.
// For now, we'll just "hardcode" it to a specific value.
var secret_number = 7;

print("I'm thinking of a number between 1 and 10.");
print("Can you guess what it is?");

var guess = 0;
var attempts = 0;

while (guess != secret_number) {
    attempts += 1;

    // In a real program, you would get user input here.
    // For this example, we'll simulate a few guesses.
    if (attempts == 1) {
        guess = 3;
        print("Your guess: 3");
    } else if (attempts == 2) {
        guess = 8;
        print("Your guess: 8");
    } else {
        guess = 7;
        print("Your guess: 7");
    }

    // Check the guess
    if (guess < secret_number) {
        print("Too low! Try again.");
    } else if (guess > secret_number) {
        print("Too high! Try again.");
    }
}

print("You got it! The secret number was {secret_number}.");
print("It took you {attempts} attempts.");
```

**How it works:**
*   We use a `while` loop to keep the game going until the `guess` matches the `secret_number`.
*   Inside the loop, we use `if/else if` statements to check if the guess is too low or too high and print a message to the user.
*   Once the correct number is guessed, the loop condition becomes false, and the program prints a success message.

**Your Challenge:**
*   Can you modify the code to change the secret number?
*   Can you add a limit to the number of attempts the user has? (Hint: you'll need another condition in your `while` loop).

## 📎 Next Steps / Resources

Congratulations on completing this beginner's guide! You've learned the fundamentals of the Limit language.

Here are some resources to help you continue your journey:

*   **Full Language Guide:** For a more in-depth look at all of Limit's features, check out the [**Full Language Guide**](./doc/guide.md).
*   **The Zen of Limit:** To understand the philosophy behind the language, read [**The Zen of Limit**](./doc/zen.md).
*   **Limit vs. Python:** To see how Limit compares to a popular dynamic language, check out our [**Limit vs. Python Comparison**](./doc/limit_vs_python.md).
*   **Explore the Code:** The best way to learn is to read code! Check out the `tests/` directory in this project to see examples of every feature in action.

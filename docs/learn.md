# Welcome to the Limit Language!

Hello, and welcome to the Limit programming language!

**What is Limit?**
Limit is a modern systems-level programming language designed for both performance and safety. It features static typing, deterministic memory management, and first-class structured concurrency.

**What can you build with it?**
You can use Limit to build command-line utilities, concurrent network services, games, and high-performance systems.

**What makes it unique?**
Limit eliminates common programming errors through:
- **Zero-cost Error Unions (`Type?`)**: Combining optionals and fallible results into a single compiler-checked type system without generic overhead.
- **Structured Concurrency**: Task lifetimes bound to lexical scopes (`parallel` and `concurrent`), avoiding thread leaks.
- **Deterministic Memory**: Region-aware deterministic memory without a tracing garbage collector.
- **Canonical Receiver**: Clear OOP using `self` within `frame` constructs.

---

## Installing and Building

Limitly is built from source using standard build tools.

**Prerequisites:**
- C++20 compatible compiler (GCC 11+, Clang 13+, or MSVC)
- GNU `make` (or CMake 3.20+)
- Windows users: MSYS2 MinGW64 environment (`mingw-w64-x86_64-gcc`, `make`)

**Build Instructions:**

```bash
# Clone the repository
git clone https://github.com/netesy/limitly.git
cd limitly

# Build the compiler executable
make
```

After compilation, the binary will be located in `bin/`:
- Windows: `bin/limitly.exe`
- Linux/macOS: `bin/limitly`

**Verify your installation:**

```bash
# Check compiler help and commands
./bin/limitly help
```

---

## Your First Program

Let's write the classic "Hello, world!" program in Limit.

1. Create a file named `hello.lm`.
2. Add the following code:

```limit
// This is your first Limit program!
print("Hello, world!");
```

3. Run the program using the `run` subcommand:

```bash
./bin/limitly run hello.lm
```

Output:
```text
Hello, world!
```

---

## Variables and Types

### Variables (`var`) and Constants (`val` / `const`)

- `var`: Declares a mutable variable.
- `val` or `const`: Declares an immutable binding.

```limit
// Mutable variable with type annotation
var count: int = 10;
print(count); // Output: 10

count = 20;
print(count); // Output: 20

// Immutable bindings
val name: str = "Limit";
const pi: float = 3.14159;
```

### Primitive Types

- **Integers**: `int` (default 64-bit), fixed-width: `i8`, `i16`, `i32`, `i64`, `i128`, `uint`, `u8`, `u16`, `u32`, `u64`, `u128`.
- **Floating-point**: `float` (default 64-bit), `f32`, `f64`.
- **Decimals**: `d2`, `d4`, `d6`, `decimal` (fixed-precision currency/financial types).
- **Boolean**: `bool` (`true` or `false`).
- **String**: `str` (UTF-8 encoded string).
- **Nil**: `nil` (represents absence or empty value).

### String Interpolation

Embed expressions directly inside strings using `{expression}`:

```limit
var user: str = "Alice";
var score: int = 95;
print("Player {user} scored {score} points!");
```

---

## Control Flow

### If-Else Statements

```limit
var temperature: int = 25;

if (temperature > 30) {
    print("It's hot outside!");
} elif (temperature >= 15) {
    print("It's a pleasant day.");
} else {
    print("It's cold.");
}
```

### Loops

#### For Loop (C-style)
```limit
for (var i = 0; i < 3; i += 1) {
    print("Loop iteration: {i}");
}
```

#### While Loop
```limit
var counter: int = 3;
while (counter > 0) {
    print("{counter}...");
    counter -= 1;
}
print("Liftoff!");
```

#### Iter Loop (Collections and Ranges)
```limit
iter (i in 1..5) {
    print("Value: {i}");
}
```

---

## Functions

Functions are defined with the `fn` keyword. Specify parameter types and an optional return type:

```limit
// Simple function
fn greet(name: str) {
    print("Hello, {name}!");
}

greet("Bob");

// Function with typed parameters and return type
fn add(a: int, b: int): int {
    return a + b;
}

var sum: int = add(10, 20);
print("Sum is {sum}"); // Sum is 30
```

---

## Collections

### Lists

A list is a dynamic, ordered sequence declared using `[Type]`:

```limit
var fruits: [str] = ["apple", "banana", "orange"];
print(fruits[0]); // apple
print(len(fruits)); // 3

// Iterate over items
iter (item in fruits) {
    print("Fruit: {item}");
}
```

### Dictionaries

A dictionary maps keys to values declared using `{KeyType: ValueType}`:

```limit
var scores: {str: int} = {
    "Alice": 100,
    "Bob": 85
};

print(scores["Alice"]); // 100
```

---

## Object-Oriented Programming: Frames

Limitly uses **frames** for data encapsulation and object-oriented programming. Frames use `self` as the instance receiver.

```limit
frame Greeter {
    pub name: str;

    pub init(greeting_name: str) {
        self.name = greeting_name;
    }

    pub fn say_hello() {
        print("Hello, {self.name}!");
    }
}

var g = Greeter("World");
g.say_hello(); // Output: Hello, World!
```

### Traits for Shared Interfaces

Traits define abstract behavior that frames implement:

```limit
trait Speaker {
    fn speak();
}

frame Dog: Speaker {
    pub fn speak() {
        print("Woof!");
    }
}

frame Cat: Speaker {
    pub fn speak() {
        print("Meow!");
    }
}

var dog = Dog();
dog.speak(); // Woof!
```

---

## Error Handling: Unified `Type?` System

Limitly does not use exceptions or generic `Result<T, E>` / `Option<T>` templates. Instead, it has a native, zero-cost error union system denoted by `Type?`:

- `Type?`: A value of `Type` or a runtime error condition.
- `ok(value)`: Return a successful value.
- `err()` or `err(ErrorType)`: Return an error condition.
- `?`: Propagate an error up the call stack.
- `? else { ... }`: Handle an error inline with a fallback.

```limit
fn divide(a: int, b: int): int? {
    if (b == 0) {
        return err();
    }
    return ok(a / b);
}

// Inline fallback handling with ? else
var safe_result: int = divide(10, 0)? else {
    print("Cannot divide by zero, using default fallback.");
    return 0;
};

// Pattern matching on fallible return
match (divide(10, 2)) {
    val value => {
        print("Success: {value}");
    },
    err => {
        print("Calculation failed.");
    }
}
```

---

## Structured Concurrency

Limitly binds concurrent execution to explicit lexical blocks:

- `parallel`: Multi-core data parallelism over disjoint slice capabilities.
- `concurrent`: Cooperative concurrent task blocks communicating through typed `channel` instances.

```limit
var ch = channel();

concurrent {
    task {
        ch.send("Message from worker task");
    }
}

var msg: str? = ch.receive();
match (msg) {
    val text => { print(text); },
    err => { print("Channel empty or closed."); }
}
```

---

## Modules

Organize programs across files with the `import` statement:

```limit
// math_helper.lm
pub fn square(n: int): int {
    return n * n;
}
```

```limit
// main.lm
import math_helper as math;

var res: int = math.square(4);
print("Result: {res}"); // 16
```

---

## Next Steps

Explore the detailed technical documentation:
- [Full Language Guide](./guide.md)
- [Formal Language Specification](./language.md)
- [Compiler & Architecture](./architecture.md)
- [Philosophy: The Zen of Limit](./zen.md)

# Limit Programming Language

Limit is a modern programming language designed with static typing, concurrency primitives, and memory safety features. The language combines the performance of systems programming with the safety and expressiveness of modern language design.

## Project Structure

The project is organized into frontend and backend components:

### Frontend
- `frontend/scanner.hh/cpp`: Tokenizes source code into a stream of tokens
- `frontend/parser.hh/cpp`: Parses tokens into an Abstract Syntax Tree (AST)
- `frontend/ast.hh`: Defines the Abstract Syntax Tree structure

### Backend
- `backend/backend.cpp`: Implements bytecode generation and AST visualization
- `backend/vm.hh/cpp`: Implements the virtual machine for executing bytecode
- `backend/memory.hh`: Provides memory management functionality
- `backend/memory_analyzer.hh`: Analyzes memory usage and detects leaks
- `backend/value.hh`: Defines the value system for runtime values
- `backend/types.hh`: Defines the type system for static typing

### Shared
- `opcodes.hh`: Defines bytecode operation codes
- `debugger.hh/cpp`: Provides error reporting functionality

## Language Features

### Core Type System
- Static typing with type inference
- Primitive types: `int`, `uint`, `float`, `bool`, `str`
- Composite types: `list<T>`, `dict<K,V>`, `array<T>`
- User-defined types: classes, enums, interfaces, traits
- Union types: `T | U`
- Refined types: `T where condition`
- Type aliases and generics

### Memory Safety
- No null pointers by default (use `Option<T>` instead)
- Contract programming for runtime and compile-time checks
- Controlled unsafe operations for low-level memory access
- Region-based memory management

### Concurrency Model
- `parallel` blocks for CPU-bound tasks
- `concurrent` blocks for I/O-bound tasks
- `async`/`await` for non-blocking operations
- Channels for communication between tasks
- Atomic operations for shared state

### Error Handling
- `attempt`-`handle` blocks for operations that might fail
- `Result<T, E>` for operations that might fail
- `Option<T>` for values that might be absent
- Pattern matching for handling different outcomes

### Code Organization
- Module system for code organization
- Interfaces and traits for defining behavior
- Visibility controls (`@public`, `@private`, `@protected`)
- Mixins for code reuse

### Modern Iteration
- `iter` statement for modern iteration over collections
- Support for key-value iteration over dictionaries
- Range-based iteration with `..` operator

### Compile-time Features
- `comptime` for compile-time execution
- Compile-time contract checking
- Compile-time type validation

## Example Code

Here are some examples demonstrating the current features of the Limit language.

### Basic Functions and Variables
```
// Declare a variable
var x = 10;

// Declare a function with a type annotation
fn square(n: int): int {
    return n * n;
}

// Call the function and print the result using string interpolation
var x_squared = square(x);
print("The square of {x} is {x_squared}");
```

### Classes and Methods
```
// Define a class with fields and methods
class Greeter {
    var name: str = "World";

    // The 'init' method acts as the constructor
    fn init(name_param: str) {
        self.name = name_param;
    }

    // A method that uses the 'self' keyword to access instance fields
    fn say_hello() {
        print("Hello, {self.name}!");
    }
}

// Create an instance of the class
var greeter = Greeter("Jules");

// Call a method on the instance
greeter.say_hello();
```

### Loops
```
// A C-style 'for' loop
print("For loop:");
for (var i = 0; i < 3; i += 1) {
    print("i = {i}");
}

// An 'iter' loop over a range
print("Iter loop:");
iter (j in 5..8) {
    print("j = {j}");
}
```

## Building and Running

### Prerequisites
- CMake 3.10 or higher
- C++17 compatible compiler

### Build Instructions
```bash
# Using CMake (recommended for cross-platform)
mkdir build && cd build
cmake ..
make

# Using Zig (alternative build system)
zig build
zig build run

# Using Windows Batch (MSYS2/MinGW64)
build.bat
```

### Running
```bash
# Execute a source file
./limitly sample.lm

# Print the AST for a source file
./limitly -ast sample.lm

# Print the tokens for a source file
./limitly -tokens sample.lm

# Print the bytecode for a source file
./limitly -bytecode sample.lm

# Start the REPL (interactive mode)
./limitly -repl
```

## Current Development Focus
- Completing the VM implementation for complex operations
- Implementing function calls and returns in the VM
- Implementing object-oriented features in the VM
- Implementing concurrency primitives in the VM
- Supporting the full range of language features in the parser

## Development Status

See [activities.md](activities.md) for the current development status and roadmap.
# Language Design Principles

## Core Philosophy

Limit is designed with the following principles in mind:

1. **Safety without sacrifice**: Provide memory and type safety without sacrificing performance
2. **Explicit over implicit**: Prefer explicit code that clearly states intent
3. **Controlled power**: Allow unsafe operations but only in controlled contexts
4. **Concurrency by design**: Built-in primitives for concurrent and parallel programming
5. **Pragmatic features**: Focus on features that solve real-world problems

## Type System

### Static Typing with Inference ✅
- Strong static typing with type inference where possible
- Explicit type annotations for function signatures
- Generics for type-safe containers and algorithms

### Type Hierarchy ✅ IMPLEMENTED
- **Primitive types**: `int`, `uint`, `float`, `bool`, `str`
- **Type aliases**: `type Id = uint;`
- **Union types**: `T | U`
- **Option types**: `Some | None`
- **Optional parameters**: `str?`, `int?`
- **Collections**: `list`, `dict`, `tuple`
- **User-defined types**: classes, enums, interfaces (in progress)

## Syntax Overview

### Variables and Types
```limit
var name: type = value;           // Explicit type
var name = value;                 // Type inference
var name: type;                   // Declaration without initialization
```

### Functions
```limit
fn function_name(param1: type1, param2: type2) -> return_type {
    // Function body
    return value;
}

fn optional_params(required: int, optional: str?) -> int {
    // Optional parameters
}

fn default_params(name: str = "World") -> str {
    return "Hello, {name}";
}
```

### Control Flow
```limit
// If/else
if (condition) {
    // ...
} else if (other_condition) {
    // ...
} else {
    // ...
}

// While loops
while (condition) {
    // ...
}

// For loops
for (var i = 0; i < 10; i = i + 1) {
    // ...
}

// Iterator loops
iter (item in collection) {
    // ...
}

// Range iteration
iter (i in 0..10) {
    // ...
}
```

### Collections
```limit
// Lists
var list = [1, 2, 3, 4, 5];
var elem = list[0];

// Dictionaries
var dict = {"key": "value", "count": 42};
var val = dict["key"];

// Tuples
var tuple = (1, "hello", true);
```

### String Interpolation
```limit
var name = "World";
var age = 25;
print("Hello, {name}! You are {age} years old.");
print("Expression: {x + y}");
```

### Concurrency

#### Parallel Blocks (CPU-bound)
```limit
var results = channel();

parallel(cores=4) {
    iter(i in 0..100) {
        results.send(i * 2);
    }
}

iter (result in results) {
    print("Result: {result}");
}
```

#### Concurrent Blocks (I/O-bound)
```limit
var results = channel();

concurrent(cores=2) {
    task(i in 1..10) {
        results.send(i * i);
    }
}

iter (result in results) {
    print("Result: {result}");
}
```

### Error Handling
```limit
// Result types
var result: int?ErrorType = operation();

// Error propagation
var value = result?;  // Propagate error if present

// Error handling
var value = result? else {
    print("Error occurred");
    0
};
```

### Pattern Matching
```limit
match (value) {
    1 => { print("One"); },
    2 => { print("Two"); },
    _ => { print("Other"); }
}
```

### Modules
```limit
// Import with alias
import module as alias;

// Import with filtering
import module show func1, func2;
import module hide internal_func;

// Use imported items
alias.function();
```

## Memory Model

### Memory Safety ✅ IMPLEMENTED
- No null pointers by default (use Option types instead)
- Region-based memory management
- No uninitialized variables (compile-time checking)
- No dangling references (ownership system)

### Controlled Unsafe Operations
- Unsafe blocks for low-level memory operations
- Contract programming for runtime and compile-time checks
- Memory analyzers for detecting potential issues

## Concurrency Model

### Parallel Execution ✅ IMPLEMENTED
- `parallel(cores=N)` blocks for CPU-bound tasks
- Automatic work distribution across cores
- Thread-safe data structures
- Uses `iter` statements for iteration

### Concurrent Execution ✅ IMPLEMENTED
- `concurrent(cores=N)` blocks for I/O-bound tasks
- Channels for communication between tasks
- Atomic operations for shared state
- Uses `task` statements for task-based concurrency

### Asynchronous Programming
- `async`/`await` for non-blocking operations (planned)
- Future/Promise-based concurrency (planned)
- Structured concurrency with scoped tasks (planned)

## Error Handling

### Result Types ✅ IMPLEMENTED
- `int?ErrorType` for operations that might fail
- `Option<T>` (Some | None) for values that might be absent
- `?` operator for error propagation
- Pattern matching for handling different outcomes

## Code Organization

### Modules and Imports ✅ SYNTAX IMPLEMENTED
- Module system for code organization
- Explicit imports: `import module as alias`
- Import filtering: `show`, `hide` filters
- Module caching and error handling
- Visibility controls (`@public`, `@private`, `@protected`) - planned

### Interfaces and Traits
- Interfaces for defining behavior contracts (planned)
- Traits for adding behavior to existing types (planned)
- Mixins for code reuse (planned)

## Syntax Design Principles

### Readability
- Braces for blocks: `{ ... }`
- Semicolons for statement termination: `;`
- Type annotations after identifiers: `name: type`
- Clear keywords for language constructs

### Expressiveness ✅ MOSTLY IMPLEMENTED
- String interpolation with `{variable}` syntax
- Optional parameters: `fn greet(name: str?)`
- Default parameter values: `fn greet(name: str = "World")`
- Pattern matching with `match` expressions
- Named arguments for function calls (planned)

### Consistency
- Consistent naming conventions
- Predictable operator precedence
- Uniform error handling patterns
- Clear scoping rules

## Known Limitations

### Current Issues
- Nested while loops cause infinite loops (VM bug)
- String keys in dictionaries work but nested dict access needs type tracking
- Nested list iteration doesn't work (type system limitation)
- 3D matrices not feasible with current collection implementation

### Workarounds
- Use sequential loops instead of nested while loops
- Use numeric keys for dictionaries when possible
- Use direct indexing instead of iteration for nested lists
- Use parallel blocks with channels for distributed computation

## Future Enhancements

### Phase 3: Language Features
- Generics and advanced type features
- Async/await for asynchronous programming
- Traits and interfaces
- Reflection and metaprogramming

### Phase 4: Tooling and Documentation
- IDE integration and language server
- Debugger with breakpoints and stepping
- Package manager and dependency resolution
- Comprehensive standard library

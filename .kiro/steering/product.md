# Limit Programming Language

Limit is a modern programming language designed with static typing, concurrency primitives, and memory safety features. The language combines the performance of systems programming with the safety and expressiveness of modern language design.

## Key Features
- Static typing with type inference
- Optional parameters and null safety
- Built-in concurrency (parallel/concurrent blocks)
- Async/await for asynchronous programming
- Pattern matching and enums
- Error handling with attempt-handle blocks
- Memory management with controlled unsafe operations
- Contract programming for compile-time and runtime safety

## Target Use Cases
- Systems programming with safety guarantees
- Concurrent and parallel applications
- Applications requiring both performance and safety
- Projects needing controlled low-level memory access

## Current Status

### ✅ Fully Implemented Features
- **Frontend**: Complete scanner and parser with AST generation
- **Control Flow**: if/else statements, while loops, for loops, nested structures
- **Iterators**: Range-based iteration (`iter (i in 1..10)`) with full nesting support
- **Variables**: Declaration, assignment, scoping with type annotations
- **Expressions**: Arithmetic, comparison, logical operations with proper precedence
- **String Features**: String interpolation with all patterns (`"text {expr} more"`)
- **Print Statements**: Clean output without side effects
- **Memory Management**: Integrated memory manager with region-based allocation

### 🔄 In Development
- **Function System**: Basic function declarations (syntax complete, VM implementation in progress)
- **Object-Oriented Features**: Class declarations (syntax complete, VM implementation pending)
- **Exception Handling**: try/catch blocks (syntax complete, VM implementation pending)
- **Concurrency**: parallel/concurrent blocks (syntax complete, VM implementation pending)

### 📋 Planned Features
- Generics and advanced type features
- Modules and import system
- Standard library
- JIT compilation
- IDE integration and tooling

### Development Quality
- **Comprehensive Test Suite**: 20+ test files covering all implemented features
- **100% Pass Rate**: All implemented features work correctly
- **Clean Architecture**: Well-separated frontend/backend with clear interfaces
- **Memory Safety**: No memory leaks or stack pollution
- **Robust Error Handling**: Clear error messages and graceful failure modes

The project has reached a significant milestone with all core control flow and expression features working correctly. The foundation is solid for implementing the remaining language features.
# VM Implementation Guide

## VM Architecture

The Limit VM is a stack-based virtual machine that executes bytecode generated from the AST. The VM is designed to be:

1. **Efficient**: Minimize overhead for common operations
2. **Safe**: Detect and report runtime errors
3. **Extensible**: Easy to add new operations and features
4. **Debuggable**: Support for debugging and introspection

## Core Components

### Stack
- Main execution stack for operands and results
- Push/pop operations for values
- Stack frames for function calls

### Environment
- Variable storage and lookup
- Scoping rules (global, local, closure)
- Garbage collection

### Instruction Set
- Defined in `opcodes.hh`
- Stack manipulation instructions
- Arithmetic and logical operations
- Control flow instructions
- Function call/return
- Object and memory operations

### Value System
- Defined in `value.hh`
- Runtime representation of values
- Type information and operations
- Boxing/unboxing for primitive types

## Memory Management

### Region-Based Memory
- Allocate memory in regions for efficient cleanup
- Track object lifetimes
- Support for garbage collection

### Value Representation
- Tagged union for primitive types
- Reference counting for complex objects
- Heap allocation for variable-sized objects

## Function Calls

### Call Frames
- Store return address
- Store local variables
- Maintain call stack for debugging

### Calling Convention
- Push arguments onto stack
- Call function
- Return value on stack

## Object System

### Class Representation
- Method table
- Instance variables
- Inheritance chain

### Method Dispatch
- Virtual method lookup
- Method caching for performance
- Support for interfaces and traits

## Concurrency Support

### Thread Management
- Thread pool for parallel execution
- Task scheduling
- Work stealing algorithm

### Synchronization Primitives
- Atomic operations
- Mutex and condition variables
- Channels for communication

## Error Handling

### Exception Mechanism
- Try/catch blocks in bytecode
- Exception objects
- Stack unwinding

### Runtime Checks
- Type checking
- Bounds checking
- Null reference checking
- Contract validation

## Optimization Techniques

### Bytecode Optimization
- Constant folding
- Dead code elimination
- Instruction combining

### Runtime Optimization
- Inline caching
- Type specialization
- Just-in-time compilation (future)

## Recent VM Improvements ✅

### Fixed Critical Issues
- **Jump Offset Calculations**: Fixed inconsistent jump offset calculations in control flow statements
  - All control flow statements (if/else, while, for, match) now execute correctly
  - Standardized jump instruction handlers for consistent behavior
  - Fixed both forward and backward jumps in loops

- **Stack Management**: Improved stack cleanup and management
  - Fixed STORE_TEMP to properly pop values from stack
  - Eliminated spurious `<iterator>` output from iterator operations
  - Clean program termination without stack pollution

- **Iterator Support**: Enhanced iterator implementation
  - Fixed nested iteration with indexed temporary variable system
  - Proper iterator lifecycle management
  - Support for complex nested iterator patterns

### Working VM Features ✅
- ✅ **Basic Operations**: Stack manipulation, arithmetic, logical operations
- ✅ **Control Flow**: if/else statements, while loops, for loops (all types)
- ✅ **Iterators**: Range-based iteration with proper nesting support
- ✅ **Variables**: Declaration, assignment, scoping
- ✅ **Expressions**: All expression types with proper evaluation
- ✅ **String Operations**: String interpolation and concatenation
- ✅ **Print Statements**: Clean output without stack side effects

## Implementation Priorities

### Current Focus
1. ✅ ~~Complete basic VM operations~~ **COMPLETED**
2. **Implement function calls and returns** - IN PROGRESS
3. **Add support for objects and classes** - NEXT
4. **Implement break/continue statements** - NEXT
5. **Add exception handling (try/catch)** - NEXT

### Future Work
6. Implement concurrency primitives
7. Add optimization passes
8. Implement JIT compilation features
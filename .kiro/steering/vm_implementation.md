# VM Implementation Guide

## VM Architecture

The Limit language now supports multiple execution modes:

### 1. Register-Based Virtual Machine (Interpretation)
- **File**: `src/backend/register.cpp`
- **Purpose**: Direct interpretation of LIR instructions
- **Characteristics**:
  - Stack-based with register allocation
  - Efficient for development and debugging
  - No compilation overhead
  - Moderate performance

### 2. JIT Compiler (Just-In-Time)
- **File**: `src/backend/jit.cpp`
- **Purpose**: Compile hot code paths to native code at runtime
- **Characteristics**:
  - Monitors code execution
  - Identifies hot paths
  - Compiles to native code on demand
  - High performance after warmup
  - Slower startup

### 3. AOT Compiler (Ahead-Of-Time)
- **File**: `src/backend/jit.cpp`
- **Purpose**: Compile entire program to native code before execution
- **Characteristics**:
  - Compiles all code before execution
  - Produces standalone executables
  - High performance
  - Slower compilation phase

## Core Components

### Register VM
- Main execution stack for operands and results
- Register allocation for efficient code
- Stack frames for function calls
- Environment for variable storage and lookup

### JIT/AOT Compiler
- Converts LIR to native code
- Performs optimization passes
- Generates machine code
- Handles linking and relocation

### Environment
- Variable storage and lookup
- Scoping rules (global, local, closure)
- Garbage collection

### Instruction Set
- Defined in `src/lir/lir.hh`
- Stack manipulation instructions
- Arithmetic and logical operations
- Control flow instructions
- Function call/return
- Object and memory operations

### Value System
- Defined in `src/backend/value.hh`
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
- Result types
- Error Propogation
- Error Handling Mechanism
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
- ✅ **Variables**: Declaration, assignment, scoping with type annotations
- ✅ **Expressions**: All expression types with proper evaluation
- ✅ **String Operations**: String interpolation and concatenation
- ✅ **Print Statements**: Clean output without stack side effects
- ✅ **Function System**: Function declarations, calls, returns, recursion
- ✅ **Optional Parameters**: Functions with optional parameters (str?, int?)
- ✅ **Default Parameters**: Functions with default parameter values
- ✅ **Type System**: Type aliases, union types, Option types
- ✅ **Module System**: Basic import/export with aliasing and filtering
- ✅ **Parallel Blocks**: Parallel execution with `iter` statements and channels
- ✅ **Concurrent Blocks**: Concurrent execution with `task` statements and channels

## Implementation Priorities

### Current Focus
1. ✅ ~~Complete basic VM operations~~ **COMPLETED**
2. ✅ ~~Implement function calls and returns~~ **COMPLETED**
3. ✅ ~~Implement optional/default parameters~~ **COMPLETED**
4. ✅ ~~Implement basic type system~~ **COMPLETED**
5. ✅ ~~Implement module system~~ **COMPLETED**
6. ✅ ~~Implement parallel/concurrent blocks~~ **COMPLETED**
7. ✅ ~~Implement register-based VM~~ **COMPLETED**
8. **Implement JIT compilation** - IN PROGRESS
9. **Implement AOT compilation** - IN PROGRESS
10. **Complete object-oriented features (classes, methods, inheritance)** - NEXT
11. **Implement closures and higher-order functions** - NEXT
12. **Complete error handling VM implementation** - NEXT

### Future Work
10. Add advanced type features (generics, structural types)
11. Implement async/await functionality
12. Add optimization passes
13. Implement JIT compilation features
# Design Document: Frames - Modern OOP System

## Overview

The frames system is a modern object-oriented programming construct for Limit that emphasizes composition over inheritance, trait-based polymorphism, and integrated concurrency support. Frames are the primary OOP mechanism, replacing traditional class hierarchies with a more flexible, safer design pattern.

**Execution Model**: Frames are compiled to native code via JIT compilation at compile-time. The register VM is used only for development and building.

### Key Design Principles

1. **Composition Over Inheritance**: Frames embed other frames as fields rather than extending them
2. **Trait-Based Polymorphism**: Interfaces define contracts; frames implement traits
3. **Default Private**: All members are private unless explicitly marked `pub` or `prot`
4. **Concurrency Integration**: Frames can contain parallel, concurrent (batch), and concurrent (stream) blocks
5. **Deterministic Cleanup**: `deinit()` methods are guaranteed to run, even during errors
6. **Type Safety**: Full integration with the type system, union types, and pattern matching
7. **Compile-Time Optimization**: All frame operations optimized at compile-time via JIT
8. **Zero-Cost Abstractions**: Frame semantics compile to efficient native code

## Architecture

### 1. Frame Declaration and Structure

```
Frame Declaration
├── Fields (with visibility: private/prot/pub)
├── Methods (with visibility: private/prot/pub)
├── Lifecycle Hooks (init/deinit)
├── Trait Implementations
├── Embedded Frames (composition)
└── Concurrency Blocks (parallel/concurrent)
```

**AST Changes Required**:
- Add `FrameDeclaration` node extending `Statement`
- Add `FrameField` node for frame members
- Add `FrameMethod` node for frame methods
- Add `TraitDeclaration` node for trait definitions
- Extend `ParallelStatement` and `ConcurrentStatement` to support frame context

**Type System Changes**:
- Add `FrameType` to represent frame types
- Add `TraitType` to represent trait types
- Add `TraitObject` for dynamic dispatch (`&Trait`)
- Implement subtyping for trait implementation

### 2. Visibility System

**Visibility Levels**:
- **Private (default)**: No keyword, accessible only within the frame
- **Protected (`prot`)**: Accessible within frame and trait implementations
- **Public (`pub`)**: Accessible from anywhere

**Enforcement Points**:
- Parser: Recognize visibility modifiers
- Type Checker: Enforce visibility rules at compile time
- LIR Generator: Ensure visibility is respected in code generation

**Implementation Strategy**:
```cpp
enum class VisibilityLevel {
    Private,    // default
    Protected,  // prot
    Public      // pub
};

struct FrameField {
    std::string name;
    TypePtr type;
    VisibilityLevel visibility;
    std::shared_ptr<Expression> default_value;
};

struct FrameMethod {
    std::string name;
    TypePtr return_type;
    std::vector<Parameter> parameters;
    VisibilityLevel visibility;
    std::shared_ptr<BlockStatement> body;
};
```

### 3. Trait System

**Trait Definition**:
- Traits define method contracts
- Methods can have default implementations
- Traits can extend other traits

**Trait Implementation**:
- Frames declare trait implementation with `frame Name : Trait1, Trait2`
- Compiler verifies all required methods are implemented
- Frames can override default trait methods

**Dynamic Dispatch**:
- Trait objects (`&Trait`) enable runtime polymorphism
- Virtual method table (vtable) for trait objects
- Static dispatch for direct frame method calls

**Implementation Strategy**:
```cpp
struct TraitDeclaration : public Statement {
    std::string name;
    std::vector<std::shared_ptr<TraitMethod>> methods;
    std::vector<std::string> extends;  // Trait inheritance
};

struct TraitMethod {
    std::string name;
    TypePtr return_type;
    std::vector<Parameter> parameters;
    std::shared_ptr<BlockStatement> default_impl;  // optional
};

struct FrameDeclaration : public Statement {
    std::string name;
    std::vector<std::shared_ptr<FrameField>> fields;
    std::vector<std::shared_ptr<FrameMethod>> methods;
    std::vector<std::string> implements;  // Trait names
    std::shared_ptr<FrameMethod> init;    // optional
    std::shared_ptr<FrameMethod> deinit;  // optional
};
```

### 4. Composition and Embedding

**Embedded Frames**:
- Frames can have fields of other frame types
- Embedded frames are initialized with their defaults
- Embedded frames' `deinit()` called in reverse order

**Access Patterns**:
- Public methods of embedded frames accessible through parent
- Public fields of embedded frames accessible through parent
- Private members of embedded frames not accessible

**Implementation Strategy**:
```cpp
// In FrameField
struct FrameField {
    std::string name;
    TypePtr type;  // Can be a FrameType
    VisibilityLevel visibility;
    std::shared_ptr<Expression> default_value;
    bool is_embedded = false;  // true if type is a frame
};

// In LIR generation
// Embedded frame initialization: call embedded frame's default constructor
// Embedded frame cleanup: call embedded frame's deinit() in reverse order
```

### 5. Lifecycle Management

**Constructor (`init`)**:
- Optional method that initializes frame state
- Called explicitly by user code (not automatic)
- Can perform validation and setup
- Can return Result type for error handling

**Destructor (`deinit`)**:
- Optional method that cleans up resources
- Called automatically when frame goes out of scope
- Guaranteed to run, even during errors
- Called in reverse order for embedded frames

**Implementation Strategy**:
```cpp
// In FrameDeclaration
std::shared_ptr<FrameMethod> init;   // optional
std::shared_ptr<FrameMethod> deinit; // optional

// In LIR generation
// At frame creation: allocate memory, initialize fields with defaults
// At frame destruction: call deinit() if defined, then deallocate
// For embedded frames: call their deinit() in reverse order

// In VM execution
// Track frame lifetime with RAII-style cleanup
// Ensure deinit() runs even if exceptions occur
```

### 6. Parallel Blocks

**Syntax**:
```limit
parallel(cores=N, timeout=Duration?, grace=Duration?, on_error=Stop|Continue|Partial) {
    iter(i in range) {
        // Direct code - access pub/prot fields with atomic operations
    }
}
```

**Semantics**:
- Distributes iterations across N cores
- Uses atomic operations for field access
- Synchronous: waits for all iterations to complete
- Can send values through channels
- Errors handled according to `on_error` policy

**Implementation Strategy**:
- Extend `ParallelStatement` to track frame context
- In LIR generation: emit atomic load/store for field access
- In VM: use thread pool for parallel execution
- Ensure proper synchronization with barriers

### 7. Concurrent Blocks (Batch Mode)

**Syntax**:
```limit
concurrent(ch=channel, cores=N, timeout=Duration?, on_error=Stop|Continue|Retry) {
    task(i in range) {
        // Each iteration is a concurrent task
        ch.send(result);
    }
}
```

**Semantics**:
- Creates bounded concurrent tasks (one per iteration)
- Each task runs on a worker thread
- Tasks communicate via channels
- Channel auto-closes when block completes
- Errors handled according to `on_error` policy

**Implementation Strategy**:
- Extend `ConcurrentStatement` to track frame context
- In LIR generation: emit task creation for each iteration
- In VM: use thread pool with task queue
- Implement channel auto-closing on block completion

### 8. Concurrent Blocks (Stream Mode)

**Syntax**:
```limit
concurrent(ch=channel, cores=N, timeout=Duration?, on_error=Stop|Continue|Retry) {
    worker(event from stream) {
        // Process each event from stream
        ch.send(result);
    }
}
```

**Semantics**:
- Processes unbounded event streams
- Each event becomes a concurrent task
- Workers run on thread pool
- Channel auto-closes when stream exhausted
- Errors handled according to `on_error` policy

**Implementation Strategy**:
- Extend `ConcurrentStatement` to support worker syntax
- In LIR generation: emit worker task creation
- In VM: implement event stream consumption
- Handle stream exhaustion and channel closing

### 9. Frame Instantiation

**Syntax**:
```limit
var obj = FrameName();                    // Default values
var obj = FrameName(field1=val1, field2=val2);  // Override fields
```

**Semantics**:
- Creates frame instance with default field values
- Can override specific fields at creation
- Embedded frames use their defaults
- Returns frame instance (not reference)

**Implementation Strategy**:
```cpp
// In parser: recognize FrameName() and FrameName(field=value) syntax
// In type checker: verify field types and defaults
// In LIR generation: emit frame allocation and field initialization
// In VM: allocate memory, initialize fields, return frame value
```

### 10. Method Dispatch

**Static Dispatch** (Direct frame method calls):
- Compile-time resolution
- No runtime overhead
- Used for direct frame method calls

**Dynamic Dispatch** (Trait object method calls):
- Runtime resolution via vtable
- Used for trait object method calls
- Enables polymorphism

**Implementation Strategy**:
```cpp
// Static dispatch: direct function call in LIR
// Dynamic dispatch: vtable lookup in LIR
// Trait object representation: pointer + vtable pointer

struct TraitObject {
    void* data;           // Pointer to frame instance
    void* vtable;         // Pointer to virtual method table
};
```

### 11. Type System Integration

**Frame Types**:
- Frames are first-class types in the type system
- Can be used in type aliases, union types, Option types
- Support subtyping through trait implementation

**Trait Types**:
- Traits define type contracts
- Trait objects enable polymorphism
- Support structural typing for trait compatibility

**Implementation Strategy**:
```cpp
// Add to type system
class FrameType : public Type {
    std::string frame_name;
    std::vector<std::string> implements;  // Trait names
};

class TraitType : public Type {
    std::string trait_name;
};

class TraitObjectType : public Type {
    std::string trait_name;
};
```

### 12. Error Handling Integration

**Result Types in Methods**:
- Frame methods can return Result types
- `?` operator works in frame methods
- Errors propagate correctly

**Error Handling in Concurrency**:
- Errors in parallel blocks collected and reported
- Errors in concurrent tasks propagated through channels
- `on_error` policy determines handling

**Implementation Strategy**:
- Extend error handling to work with frame methods
- Implement error collection in parallel blocks
- Implement error propagation in concurrent blocks

### 13. Memory Management

**Frame Allocation**:
- Frames allocated in region-based memory system
- Automatic cleanup when out of scope
- Embedded frames cleaned up in reverse order

**Lifetime Tracking**:
- Type checker tracks frame lifetimes
- Ensures no use-after-free
- Validates embedded frame cleanup order

**Implementation Strategy**:
```cpp
// In LIR generation
// Frame creation: allocate in region, initialize fields
// Frame destruction: call deinit() if defined, deallocate
// Embedded frames: track cleanup order

// In VM
// Use RAII-style cleanup
// Maintain frame stack for lifetime tracking
```

### 14. Debugging Support

**Frame Introspection**:
- Access frame field values during debugging
- View frame method calls in stack trace
- Inspect trait implementations

**Implementation Strategy**:
- Extend debugger to show frame structure
- Implement frame field inspection
- Track frame method calls in call stack

## Data Models

### Frame Instance Representation

```cpp
struct FrameInstance {
    std::string frame_type;                    // Frame type name
    std::unordered_map<std::string, Value> fields;  // Field values
    std::shared_ptr<FrameType> type_info;      // Type information
};
```

### Trait Object Representation

```cpp
struct TraitObject {
    void* data;                    // Pointer to frame instance
    std::shared_ptr<VirtualTable> vtable;  // Virtual method table
};
```

### Virtual Method Table

```cpp
struct VirtualTable {
    std::unordered_map<std::string, FunctionPtr> methods;
    std::string trait_name;
};
```

## Error Handling

### Compile-Time Errors

1. **Visibility Violations**: Accessing private members from outside frame
2. **Trait Implementation**: Missing required trait methods
3. **Field Type Mismatches**: Incorrect field types in instantiation
4. **Undefined Frames/Traits**: Using undefined frame or trait names

### Runtime Errors

1. **Null Reference**: Accessing fields on null frame reference
2. **Method Not Found**: Calling undefined method on frame
3. **Type Mismatch**: Passing wrong type to method
4. **Concurrency Errors**: Errors in parallel/concurrent blocks

### Error Reporting

- Clear error messages with line numbers
- Suggestions for fixing common errors
- Stack traces showing frame method calls

## Testing Strategy

### Unit Tests

1. **Frame Declaration**: Test frame creation and field initialization
2. **Visibility**: Test visibility enforcement for fields and methods
3. **Traits**: Test trait definition and implementation
4. **Composition**: Test embedded frames and method delegation
5. **Lifecycle**: Test init/deinit methods and cleanup order
6. **Concurrency**: Test parallel and concurrent blocks in frames

### Integration Tests

1. **Frame + Type System**: Test frames in union types, Option types
2. **Frame + Error Handling**: Test Result types in frame methods
3. **Frame + Modules**: Test frame import/export and visibility
4. **Frame + Concurrency**: Test frames in concurrent contexts

### Test Coverage

- Basic frame creation and method calls
- Visibility enforcement (private, protected, public)
- Trait implementation and polymorphism
- Embedded frames and composition
- Lifecycle management (init/deinit)
- Parallel block execution
- Concurrent block execution (batch and stream)
- Error handling in frame methods
- Memory management and cleanup

## Implementation Phases

### Phase 1: Core Frame System (Foundation)
- Frame declaration and instantiation
- Field and method definitions
- Visibility system (private, protected, public)
- Basic method calls

### Phase 2: Trait System
- Trait definition and implementation
- Static and dynamic dispatch
- Trait objects and polymorphism

### Phase 3: Composition and Lifecycle
- Embedded frames
- init/deinit methods
- Automatic cleanup

### Phase 4: Concurrency Integration
- Parallel blocks in frames
- Concurrent blocks (batch mode)
- Concurrent blocks (stream mode)
- Atomic field access

### Phase 5: Advanced Features
- Error handling integration
- Type system integration
- Module system integration
- Debugging support

## Performance Considerations

### Static Dispatch
- Zero-cost abstraction for direct method calls
- Compile-time resolution
- No runtime overhead

### Dynamic Dispatch
- Virtual method table lookup (one indirection)
- Acceptable overhead for polymorphic code
- Can be optimized with inline caching

### Memory Layout
- Frame fields laid out sequentially in memory
- Embedded frames inline (no indirection)
- Efficient cache locality

### Concurrency
- Thread pool for parallel/concurrent execution
- Lock-free channels for communication
- Atomic operations for field access

## Known Limitations and Future Work

### Current Limitations
- No multiple inheritance (by design - use composition)
- No class hierarchies (by design - use traits)
- No reflection (planned for future)

### Future Enhancements
- Reflection and introspection
- Advanced trait features (associated types, bounds)
- Async/await integration
- Performance optimizations (inline caching, JIT)


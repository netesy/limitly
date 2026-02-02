# Requirements Document: Frames - Modern OOP System

## Introduction

This specification defines the implementation of **frames**, a modern object-oriented programming construct for the Limit language. Frames follow composition-over-inheritance principles, combining Rust-style structs, Go-style interfaces (traits), and built-in concurrency support. Frames are the primary OOP mechanism in Limit, emphasizing safety, clarity, and performance through composition and trait-based polymorphism rather than class hierarchies.

## Glossary

- **Frame**: A composite data structure with fields, methods, traits, and optional concurrency blocks
- **Trait**: An interface defining a contract of methods that frames can implement
- **Visibility Modifier**: Keywords controlling access scope (`pub`, `prot`, or default private)
- **Composition**: Embedding frames as fields in other frames (preferred over inheritance)
- **Trait Implementation**: A frame declaring it implements one or more traits
- **Concurrency Block**: Parallel, concurrent (batch), or concurrent (stream) execution contexts
- **SharedCell**: Atomic access mechanism for shared mutable state in parallel blocks
- **Channel**: Communication primitive for sending/receiving values between concurrent tasks
- **Worker**: Event-processing task in concurrent (stream) mode
- **Task**: Bounded concurrent operation in concurrent (batch) mode
- **Lifecycle Hooks**: `init()` (constructor) and `deinit()` (destructor) methods
- **Protected Field/Method**: Accessible within frame and via trait implementations (`prot` keyword)
- **Public Field/Method**: Accessible from anywhere (`pub` keyword)
- **Private Field/Method**: Accessible only within the declaring frame (default, no keyword)

## Requirements

### Requirement 1: Frame Declaration and Basic Structure

**User Story:** As a developer, I want to declare frames with fields and methods, so that I can create structured data types with associated behavior.

#### Acceptance Criteria

1. WHEN I declare a frame with `frame FrameName { ... }` THEN it SHALL be recognized as a valid type
2. WHEN I declare fields in a frame THEN they SHALL have explicit type annotations
3. WHEN I declare methods in a frame THEN they SHALL be callable on frame instances
4. WHEN I declare a frame without visibility modifiers THEN fields and methods SHALL be private by default
5. WHEN I instantiate a frame with `FrameName()` THEN it SHALL create an instance with default field values

### Requirement 2: Visibility and Access Control

**User Story:** As a developer, I want fine-grained control over frame member visibility, so that I can create well-encapsulated types with clear public APIs.

#### Acceptance Criteria

1. WHEN I declare a field without a modifier THEN it SHALL be private (accessible only within the frame)
2. WHEN I declare a field with `pub` THEN it SHALL be publicly accessible from anywhere
3. WHEN I declare a field with `prot` THEN it SHALL be protected (accessible within frame and trait implementations)
4. WHEN I declare a method without a modifier THEN it SHALL be private by default
5. WHEN I declare a method with `pub` THEN it SHALL be publicly callable from anywhere
6. WHEN I declare a method with `prot` THEN it SHALL be protected (accessible within frame and trait implementations)
7. WHEN I access a private field from outside the frame THEN the compiler SHALL report an error
8. WHEN I access a protected field from a trait implementation THEN it SHALL be allowed

### Requirement 3: Trait System and Implementation

**User Story:** As a developer, I want to define and implement traits, so that I can create polymorphic code with clear contracts.

#### Acceptance Criteria

1. WHEN I declare a trait with `trait TraitName { ... }` THEN it SHALL define a contract of methods
2. WHEN I declare a frame with `frame Name : Trait1, Trait2` THEN it SHALL implement all specified traits
3. WHEN a frame implements a trait THEN it SHALL provide implementations for all required trait methods
4. WHEN a trait method has a default implementation THEN frames implementing the trait MAY override it
5. WHEN I call a trait method on a frame THEN it SHALL invoke the frame's implementation
6. WHEN I use a trait object with `&Trait` THEN it SHALL enable dynamic dispatch at runtime
7. WHEN I pass a frame to a function expecting a trait THEN it SHALL work if the frame implements the trait
8. WHEN multiple traits define the same method THEN the frame SHALL implement all versions

### Requirement 4: Composition and Embedding

**User Story:** As a developer, I want to compose frames by embedding other frames as fields, so that I can build complex types through composition rather than inheritance.

#### Acceptance Criteria

1. WHEN I declare a frame field with another frame type THEN it SHALL be embedded as a field
2. WHEN I access an embedded frame's public methods THEN they SHALL be callable through the parent frame
3. WHEN I access an embedded frame's public fields THEN they SHALL be accessible through the parent frame
4. WHEN an embedded frame has a `deinit()` method THEN it SHALL be called when the parent is destroyed
5. WHEN multiple frames are embedded THEN they SHALL be destroyed in reverse order of declaration
6. WHEN I initialize an embedded frame THEN it SHALL use the embedded frame's default constructor

### Requirement 5: Lifecycle Management (init and deinit)

**User Story:** As a developer, I want to manage frame initialization and cleanup, so that I can ensure proper resource management and state initialization.

#### Acceptance Criteria

1. WHEN I declare a `pub init()` method THEN it SHALL be callable to initialize frame state
2. WHEN I declare a `pub deinit()` method THEN it SHALL be called automatically when the frame is destroyed
3. WHEN a frame is destroyed THEN `deinit()` SHALL be guaranteed to run, even if concurrency blocks panic
4. WHEN a frame has embedded frames THEN their `deinit()` methods SHALL be called in reverse order
5. WHEN `init()` is not called THEN the frame SHALL still be usable with default field values
6. WHEN `deinit()` is defined THEN the compiler SHALL warn if it's never called where needed

### Requirement 6: Parallel Blocks for CPU-Bound Work

**User Story:** As a developer, I want to execute CPU-bound work in parallel within a frame, so that I can leverage multiple cores for computation.

#### Acceptance Criteria

1. WHEN I declare a `parallel(cores=N)` block in a frame THEN it SHALL execute code across N cores
2. WHEN I use `iter(i in range)` in a parallel block THEN it SHALL distribute iterations across cores
3. WHEN I send values through a channel in a parallel block THEN they SHALL be received by the consumer
4. WHEN I access `pub` and `prot` fields in a parallel block THEN it SHALL use atomic operations
5. WHEN I access private fields in a parallel block THEN the compiler SHALL report an error
6. WHEN a parallel block completes THEN all iterations SHALL be finished before returning
7. WHEN I specify `cores=N` THEN it SHALL use N cores for parallel execution
8. WHEN I specify `timeout=Duration` THEN the parallel block SHALL terminate if it exceeds the timeout
9. WHEN I specify `on_error=Stop|Continue|Partial` THEN errors SHALL be handled according to the policy

### Requirement 7: Concurrent Blocks (Batch Mode) for Bounded I/O

**User Story:** As a developer, I want to execute bounded concurrent work with channels, so that I can parallelize I/O-bound operations over a known dataset.

#### Acceptance Criteria

1. WHEN I declare a `concurrent(ch=channel, cores=N)` block THEN it SHALL execute bounded concurrent tasks
2. WHEN I use `task(i in range)` in a concurrent block THEN each iteration becomes a concurrent task
3. WHEN I send values through a channel with `ch.send(value)` THEN they SHALL be received by the consumer
4. WHEN the concurrent block completes THEN the output channel SHALL auto-close
5. WHEN I access `pub` and `prot` fields in a task THEN it SHALL use atomic operations
6. WHEN I access private fields in a task THEN the compiler SHALL report an error
7. WHEN I specify `cores=N` THEN it SHALL use N worker threads for task execution
8. WHEN I specify `timeout=Duration` THEN tasks SHALL terminate if they exceed the timeout
9. WHEN I specify `on_error=Stop|Continue|Retry` THEN errors SHALL be handled according to the policy

### Requirement 8: Concurrent Blocks (Stream Mode) for Unbounded I/O

**User Story:** As a developer, I want to process unbounded event streams concurrently, so that I can handle continuous I/O like WebSocket connections.

#### Acceptance Criteria

1. WHEN I declare a `concurrent(ch=channel)` block with `worker(event from stream)` THEN it SHALL process events from a stream
2. WHEN I use `worker(event from stream)` in a concurrent block THEN each event becomes a concurrent task
3. WHEN I send values through a channel THEN they SHALL be received by the consumer
4. WHEN the event stream is exhausted THEN the output channel SHALL auto-close
5. WHEN I access `pub` and `prot` fields in a worker THEN it SHALL use atomic operations
6. WHEN I access private fields in a worker THEN the compiler SHALL report an error
7. WHEN I specify `cores=N` THEN it SHALL use N worker threads for event processing
8. WHEN I specify `timeout=Duration` THEN the stream processing SHALL terminate if it exceeds the timeout
9. WHEN I specify `on_error=Stop|Continue|Retry` THEN errors SHALL be handled according to the policy

### Requirement 9: Frame Instantiation with Default Values

**User Story:** As a developer, I want to create frame instances with default values and override specific fields, so that I can write concise and readable instantiation code.

#### Acceptance Criteria

1. WHEN I use `FrameName()` THEN it SHALL create an instance with all fields at their default values
2. WHEN I use `FrameName(field1 = value1, field2 = value2)` THEN it SHALL override specific fields
3. WHEN I omit fields in instantiation THEN they SHALL use their declared default values
4. WHEN a field has no default value THEN the compiler SHALL require it in instantiation
5. WHEN I instantiate a frame with embedded frames THEN embedded frames SHALL use their defaults

### Requirement 10: Method Dispatch and Polymorphism

**User Story:** As a developer, I want to use frames polymorphically through traits, so that I can write generic code that works with multiple frame types.

#### Acceptance Criteria

1. WHEN I call a method on a frame THEN it SHALL use static dispatch (compile-time resolution)
2. WHEN I call a method on a trait object `&Trait` THEN it SHALL use dynamic dispatch (runtime resolution)
3. WHEN a frame implements multiple traits THEN each trait's methods SHALL be callable
4. WHEN I pass a frame to a function expecting a trait THEN the compiler SHALL verify trait implementation
5. WHEN I use trait objects in collections THEN they SHALL maintain correct method dispatch

### Requirement 11: Cross-Mode Composition

**User Story:** As a developer, I want to compose frames with different concurrency modes, so that I can build complex applications mixing parallel, batch concurrent, and stream concurrent operations.

#### Acceptance Criteria

1. WHEN I embed a parallel frame in a sequential frame THEN both modes SHALL coexist
2. WHEN I embed a concurrent frame in a parallel frame THEN they SHALL work together
3. WHEN I call methods on embedded frames with different concurrency modes THEN they SHALL execute correctly
4. WHEN I pass data between frames with different modes THEN channels and SharedCells SHALL handle synchronization

### Requirement 12: Error Handling in Frames

**User Story:** As a developer, I want frames to work with the error handling system, so that I can write robust object-oriented code with proper error propagation.

#### Acceptance Criteria

1. WHEN a frame method returns a Result type THEN it SHALL work with the `?` operator
2. WHEN I use the `?` operator in a frame method THEN errors SHALL propagate correctly
3. WHEN a frame method fails THEN the error information SHALL be preserved
4. WHEN I use error handling in concurrent blocks THEN errors SHALL propagate from tasks/workers
5. WHEN I use error handling in parallel blocks THEN errors SHALL be collected and reported

### Requirement 13: Frame Memory Management

**User Story:** As a developer, I want frames to integrate with the memory management system, so that I can write efficient code without memory leaks.

#### Acceptance Criteria

1. WHEN I create a frame instance THEN it SHALL be managed by the region-based memory system
2. WHEN a frame goes out of scope THEN it SHALL be automatically cleaned up
3. WHEN a frame has embedded frames THEN they SHALL be cleaned up in reverse order
4. WHEN I use frames in recursive structures THEN they SHALL avoid memory leaks
5. WHEN I use frames with channels THEN values SHALL be properly transferred and cleaned up

### Requirement 14: Frame Type System Integration

**User Story:** As a developer, I want frames to work with the type system, so that I can use them in type aliases, union types, and generic contexts.

#### Acceptance Criteria

1. WHEN I create a type alias for a frame THEN it SHALL be usable everywhere the frame is usable
2. WHEN I use a frame in union types THEN it SHALL maintain type safety
3. WHEN I use Option types with frames THEN they SHALL support null safety patterns
4. WHEN I use frame types in function signatures THEN they SHALL enforce type checking
5. WHEN I use trait objects in union types THEN they SHALL work correctly

### Requirement 15: Frame Debugging and Introspection

**User Story:** As a developer, I want comprehensive debugging support for frames, so that I can troubleshoot object-oriented code effectively.

#### Acceptance Criteria

1. WHEN I debug a frame instance THEN I SHALL see all field values and their types
2. WHEN I debug frame method calls THEN I SHALL see the call stack with frame context
3. WHEN I debug trait implementations THEN I SHALL see which frame implements which trait
4. WHEN I debug concurrent blocks THEN I SHALL see task/worker execution and channel communication
5. WHEN I use frame introspection THEN I SHALL access metadata about frame structure


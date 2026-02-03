# Implementation Plan: Frames - Modern OOP System

## JIT Compilation Focus

All tasks in this implementation plan focus on JIT compilation as the primary execution model:

- **Compile-Time Analysis**: Frame structure, method dispatch, and trait implementation verified at compile-time
- **Code Generation**: LIR generation includes frame layout and method dispatch information for JIT optimization
- **Static Dispatch**: Direct frame method calls resolved at compile-time with specialized code generation
- **Dynamic Dispatch**: Trait objects use virtual method tables (vtables) optimized for JIT compilation
- **Type Specialization**: Generate specialized code for each frame type and trait combination
- **Optimization**: Eliminate runtime type checks through compile-time analysis
- **Register VM**: Used only for development and testing, not production execution

Each task includes specific JIT optimization opportunities and compile-time focus areas.

## Overview

This implementation plan breaks down the frames OOP system into discrete, manageable coding tasks. Each task builds incrementally on previous tasks, starting with core frame support and progressing through traits, composition, lifecycle management, and concurrency integration.

**Note**: This plan accounts for existing infrastructure already in place:
- ✅ Concurrency blocks (parallel, concurrent batch/stream) fully implemented
- ✅ Type system with union types, Option types, type aliases
- ✅ Visibility system (Private, Protected, Public)
- ✅ Memory management (region-based allocation)
- ✅ Error handling (Result types, ? operator)
- ✅ Module system (import/export)

**Focus**: Implementing frame-specific features that don't exist yet

---

## Phase 1: Core Frame System Foundation

- [x] 1. Add frame-related AST nodes and type definitions






  - Add `FrameDeclaration` AST node with fields, methods, and trait list
  - Add `FrameField` node for frame members with visibility and default values
  - Add `FrameMethod` node for frame methods with visibility and body
  - Add `FrameType` to backend type system (new TypeTag::Frame)
  - Add `TraitType` to backend type system (new TypeTag::Trait)
  - Add `TraitObjectType` to backend type system (new TypeTag::TraitObject)
  - Extend `VisibilityLevel` enum if needed (already has Private, Protected, Public, Const)
  - _Requirements: 1.1, 2.1_
  - **JIT Focus**: Include frame layout and method dispatch information in type definitions for compile-time optimization
  - **Status**: AST nodes exist for ClassDeclaration; need to create frame-specific versions

- [ ] 2. Implement frame declaration parsing

















  - Add `frame` keyword to scanner (if not already present)
  - Implement frame declaration parsing in parser
  - Parse frame fields with type annotations and visibility modifiers
  - Parse frame methods with visibility modifiers
  - Parse trait implementation list (`frame Name : Trait1, Trait2`)
  - Parse init() and deinit() methods
  - _Requirements: 1.1, 1.2_
  - **JIT Focus**: Generate AST with complete frame layout information for compile-time method dispatch resolution
  - **Status**: Parser has class parsing; adapt for frames

- [ ] 3. Implement frame instantiation parsing and type checking
  - Parse `FrameName()` syntax for frame creation
  - Parse `FrameName(field1=value1, field2=value2)` syntax
  - Implement type checking for frame instantiation
  - Verify all required fields are provided or have defaults
  - _Requirements: 1.5, 9.1_
  - **JIT Focus**: Validate frame instantiation at compile-time and generate specialized code for each frame type
  - **Status**: Class instantiation exists; adapt for frames

- [ ] 4. Implement frame field and method access
  - Parse member access syntax (`frame.field`, `frame.method()`)
  - Implement type checking for field access
  - Implement type checking for method calls
  - Verify visibility rules (private, protected, public)
  - _Requirements: 2.1, 2.2_
  - **JIT Focus**: Resolve method dispatch at compile-time and generate direct calls for static dispatch
  - **Optimization**: Eliminate runtime method lookup overhead through compile-time resolution
  - **Status**: Class member access exists; adapt for frames

- [ ] 5. Implement frame LIR code generation
  - Generate LIR for frame instantiation (allocate memory, initialize fields)
  - Generate LIR for field access (load/store operations)
  - Generate LIR for method calls (function calls with frame context)
  - Generate LIR for frame destruction (call deinit if defined)
  - _Requirements: 1.1, 1.5_
  - **JIT Focus**: Generate efficient LIR with frame layout information for JIT compilation to native code
  - **Optimization**: Inline frame method calls where possible; generate specialized code for each frame type
  - **Status**: Class LIR generation exists; adapt for frames

- [ ] 6. Implement frame VM execution
  - Add frame value representation to VM
  - Implement frame allocation in memory system
  - Implement field access in VM
  - Implement method calls on frames
  - Implement frame cleanup on scope exit
  - _Requirements: 1.1, 1.5_
  - **JIT Focus**: Register VM used for development/testing only; production uses JIT-compiled native code
  - **Status**: Class VM execution exists; adapt for frames

- [ ] 7. Create basic frame tests
  - Test frame declaration and instantiation
  - Test field initialization with defaults
  - Test field access (public fields)
  - Test method calls on frames
  - Test frame cleanup
  - _Requirements: 1.1, 1.5_

- [ ] 7.1 Remove unused class infrastructure
  - Remove `ClassDeclaration` AST node and related parsing code
  - Remove class-specific type checking logic from type checker
  - Remove class-specific LIR generation code
  - Remove class-specific VM execution code
  - Clean up parser to remove class keyword and parsing rules
  - Update AST header files to remove class-related nodes
  - _Requirements: 1.1_
  - **JIT Focus**: Eliminate dead code paths; simplify compiler for frame-only OOP model
  - **Cleanup**: Reduce codebase complexity and maintenance burden

---

## Phase 2: Visibility and Access Control

- [ ] 8. Implement visibility enforcement in type checker
  - Enforce private field access restrictions
  - Enforce protected field access restrictions
  - Enforce public field access permissions
  - Generate compile-time errors for visibility violations
  - _Requirements: 2.1, 2.2, 2.3_
  - **JIT Focus**: Validate visibility at compile-time; eliminate runtime visibility checks
  - **Optimization**: Generate code only for valid access patterns
  - **Status**: Visibility system exists for classes; extend for frames

- [ ] 9. Implement visibility enforcement in LIR generation
  - Verify visibility during code generation
  - Ensure visibility checks are consistent with type checker
  - Generate appropriate error messages
  - _Requirements: 2.1, 2.2, 2.3_
  - **JIT Focus**: Compile-time visibility validation ensures no runtime checks needed

- [ ] 10. Create visibility enforcement tests
  - Test private field access restrictions
  - Test protected field access in trait implementations
  - Test public field access from outside frame
  - Test private method access restrictions
  - Test protected method access
  - _Requirements: 2.1, 2.2, 2.3_

- [ ] 10.1 Clean up visibility system
  - Remove any class-specific visibility enforcement code
  - Consolidate visibility checking into frame-specific logic
  - Update type checker to use unified visibility system
  - Remove redundant visibility validation code
  - _Requirements: 2.1, 2.2, 2.3_
  - **JIT Focus**: Streamline compile-time visibility validation
  - **Cleanup**: Eliminate duplicate visibility checking logic

---

## Phase 3: Trait System

- [ ] 11. Add trait-related AST nodes
  - Enhance `TraitDeclaration` AST node (already exists)
  - Add trait method default implementations
  - Add trait inheritance support
  - _Requirements: 3.1, 3.2_
  - **JIT Focus**: Include trait method dispatch information in AST for compile-time resolution
  - **Status**: TraitDeclaration exists; enhance it

- [ ] 12. Implement trait declaration parsing
  - Enhance trait declaration parsing (already partially exists)
  - Parse trait methods with signatures
  - Parse default trait method implementations
  - Parse trait inheritance (`trait Name : ParentTrait`)
  - _Requirements: 3.1, 3.2_
  - **JIT Focus**: Generate complete trait method dispatch information for compile-time resolution

- [ ] 13. Implement trait implementation verification
  - Verify frames implement all required trait methods
  - Check method signatures match trait definitions
  - Allow override of default trait methods
  - Generate compile-time errors for missing implementations
  - _Requirements: 3.2, 3.3_
  - **JIT Focus**: Validate trait implementation at compile-time; generate specialized dispatch code

- [ ] 14. Implement static dispatch for trait methods
  - Generate LIR for direct trait method calls
  - Resolve trait methods at compile time
  - Verify method visibility in trait context
  - _Requirements: 3.4, 10.1_
  - **JIT Focus**: Generate direct method calls for static dispatch; eliminate runtime method lookup

- [ ] 15. Implement trait objects and dynamic dispatch
  - Add `TraitObject` type to type system
  - Implement trait object creation (`&Trait`)
  - Implement virtual method table (vtable) generation
  - Implement dynamic method dispatch via vtable
  - _Requirements: 3.5, 10.2_
  - **JIT Focus**: Generate optimized vtable code for dynamic dispatch; specialize for known trait implementations

- [ ] 16. Implement trait type checking
  - Verify frames implement required traits
  - Support trait objects in function signatures
  - Implement trait subtyping
  - _Requirements: 3.1, 3.2, 3.3_
  - **JIT Focus**: Validate trait compatibility at compile-time; generate specialized code for trait implementations

- [ ] 17. Create trait system tests
  - Test trait definition and implementation
  - Test trait method calls
  - Test default trait method implementations
  - Test trait objects and dynamic dispatch
  - Test multiple trait implementation
  - _Requirements: 3.1, 3.2, 3.3, 3.4, 3.5_

- [ ] 17.1 Clean up trait system infrastructure
  - Remove any unused trait-related code from class system
  - Consolidate trait implementation logic
  - Remove redundant trait type checking code
  - Update LIR generation to use unified trait dispatch
  - _Requirements: 3.1, 3.2, 3.3, 3.4, 3.5_
  - **JIT Focus**: Streamline trait dispatch code generation
  - **Cleanup**: Eliminate duplicate trait handling logic

---

## Phase 4: Composition and Embedding

- [ ] 18. Implement embedded frame field support
  - Allow frame fields to have other frame types
  - Initialize embedded frames with defaults
  - Generate LIR for embedded frame initialization
  - _Requirements: 4.1, 4.2_
  - **JIT Focus**: Generate efficient code for embedded frame initialization and layout

- [ ] 19. Implement embedded frame access
  - Support accessing embedded frame public methods
  - Support accessing embedded frame public fields
  - Enforce visibility for embedded frame members
  - _Requirements: 4.2, 4.3_
  - **JIT Focus**: Generate direct field access code for embedded frames; eliminate indirection where possible

- [ ] 20. Implement embedded frame cleanup
  - Call deinit() on embedded frames when parent destroyed
  - Ensure cleanup in reverse order of declaration
  - Handle nested embedded frames
  - _Requirements: 4.4, 4.5_
  - **JIT Focus**: Generate efficient cleanup code; inline deinit calls where possible

- [ ] 21. Create composition tests
  - Test embedded frame initialization
  - Test accessing embedded frame methods
  - Test accessing embedded frame fields
  - Test embedded frame cleanup order
  - Test nested embedded frames
  - _Requirements: 4.1, 4.2, 4.3, 4.4, 4.5_

- [ ] 21.1 Clean up composition infrastructure
  - Remove any class-based composition code
  - Consolidate embedded frame handling
  - Remove redundant composition type checking
  - Update memory management for frame composition
  - _Requirements: 4.1, 4.2, 4.3, 4.4, 4.5_
  - **JIT Focus**: Optimize embedded frame layout and access patterns
  - **Cleanup**: Eliminate duplicate composition logic

---

## Phase 5: Lifecycle Management

- [ ] 22. Implement init() method support
  - Parse `pub init()` method declarations
  - Allow init() to take parameters
  - Allow init() to return Result types
  - Generate LIR for init() calls
  - _Requirements: 5.1, 5.2_
  - **JIT Focus**: Generate efficient init() code; inline initialization where possible

- [ ] 23. Implement deinit() method support
  - Parse `pub deinit()` method declarations
  - Ensure deinit() is called on frame destruction
  - Guarantee deinit() runs even during errors
  - Generate LIR for deinit() calls
  - _Requirements: 5.2, 5.3, 5.4_
  - **JIT Focus**: Generate guaranteed cleanup code; ensure deinit() inlining for performance

- [ ] 24. Implement lifecycle method type checking
  - Verify init() and deinit() signatures
  - Check init() return types (Result types allowed)
  - Ensure deinit() takes no parameters
  - _Requirements: 5.1, 5.2_
  - **JIT Focus**: Validate lifecycle methods at compile-time; generate specialized code

- [ ] 25. Create lifecycle management tests
  - Test init() method execution
  - Test deinit() method execution
  - Test deinit() guaranteed execution
  - Test init() with parameters
  - Test init() with Result types
  - Test embedded frame lifecycle
  - _Requirements: 5.1, 5.2, 5.3, 5.4, 5.5_

- [ ] 25.1 Clean up lifecycle infrastructure
  - Remove any class-based lifecycle code
  - Consolidate init/deinit handling
  - Remove redundant lifecycle type checking
  - Update error handling for lifecycle methods
  - _Requirements: 5.1, 5.2, 5.3, 5.4, 5.5_
  - **JIT Focus**: Optimize lifecycle code generation
  - **Cleanup**: Eliminate duplicate lifecycle logic

---

## Phase 6: Parallel Block Integration

- [ ] 26. Extend parallel blocks for frame context
  - Modify `ParallelStatement` to track frame context
  - Support field access in parallel blocks
  - Implement atomic operations for field access
  - _Requirements: 6.1, 6.2, 6.3_
  - **JIT Focus**: Generate atomic operations for frame field access in parallel blocks
  - **Status**: Parallel blocks exist; extend for frame context

- [ ] 27. Implement visibility enforcement in parallel blocks
  - Allow access to `pub` and `prot` fields
  - Prevent access to private fields
  - Generate compile-time errors for violations
  - _Requirements: 6.4, 6.5_
  - **JIT Focus**: Validate field access at compile-time; eliminate runtime visibility checks

- [ ] 28. Implement parallel block LIR generation
  - Generate atomic load/store for field access
  - Generate thread pool task creation
  - Generate synchronization barriers
  - _Requirements: 6.1, 6.2_
  - **JIT Focus**: Generate efficient atomic operations; optimize synchronization barriers

- [ ] 29. Create parallel block frame tests
  - Test parallel block with frame field access
  - Test atomic operations on fields
  - Test visibility enforcement in parallel blocks
  - Test parallel block completion
  - _Requirements: 6.1, 6.2, 6.3, 6.4, 6.5_

- [ ] 29.1 Clean up parallel block infrastructure
  - Remove any class-based parallel block code
  - Consolidate frame-parallel block integration
  - Remove redundant atomic operation code
  - Update synchronization for frame fields
  - _Requirements: 6.1, 6.2, 6.3, 6.4, 6.5_
  - **JIT Focus**: Optimize atomic operations for frame fields
  - **Cleanup**: Eliminate duplicate parallel block logic

---

## Phase 7: Concurrent Block Integration (Batch Mode)

- [ ] 30. Extend concurrent blocks for frame context
  - Modify `ConcurrentStatement` to track frame context
  - Support field access in task blocks
  - Implement atomic operations for field access
  - _Requirements: 7.1, 7.2, 7.3_
  - **JIT Focus**: Generate atomic operations for frame field access in concurrent tasks
  - **Status**: Concurrent blocks exist; extend for frame context

- [ ] 31. Implement visibility enforcement in concurrent blocks
  - Allow access to `pub` and `prot` fields in tasks
  - Prevent access to private fields
  - Generate compile-time errors for violations
  - _Requirements: 7.5, 7.6_
  - **JIT Focus**: Validate field access at compile-time; eliminate runtime visibility checks

- [ ] 32. Implement concurrent block LIR generation
  - Generate atomic operations for field access
  - Generate task creation for each iteration
  - Generate channel communication
  - _Requirements: 7.1, 7.2, 7.3_
  - **JIT Focus**: Generate efficient task creation and channel communication code

- [ ] 33. Create concurrent block frame tests
  - Test concurrent block with frame field access
  - Test atomic operations on fields
  - Test visibility enforcement in concurrent blocks
  - Test channel communication from tasks
  - _Requirements: 7.1, 7.2, 7.3, 7.4, 7.5, 7.6_

- [ ] 33.1 Clean up concurrent block infrastructure
  - Remove any class-based concurrent block code
  - Consolidate frame-concurrent block integration
  - Remove redundant task creation code
  - Update channel communication for frame fields
  - _Requirements: 7.1, 7.2, 7.3, 7.4, 7.5, 7.6_
  - **JIT Focus**: Optimize task creation and channel communication
  - **Cleanup**: Eliminate duplicate concurrent block logic

---

## Phase 8: Concurrent Block Integration (Stream Mode)

- [ ] 34. Extend concurrent stream blocks for frame context
  - Support worker syntax in concurrent blocks
  - Support field access in worker blocks
  - Implement atomic operations for field access
  - _Requirements: 8.1, 8.2, 8.3_
  - **JIT Focus**: Generate efficient worker task code for frame field access

- [ ] 35. Implement visibility enforcement in worker blocks
  - Allow access to `pub` and `prot` fields in workers
  - Prevent access to private fields
  - Generate compile-time errors for violations
  - _Requirements: 8.5, 8.6_
  - **JIT Focus**: Validate field access at compile-time; eliminate runtime visibility checks

- [ ] 36. Implement worker block LIR generation
  - Generate atomic operations for field access
  - Generate worker task creation
  - Generate event stream consumption
  - _Requirements: 8.1, 8.2, 8.3_
  - **JIT Focus**: Generate efficient worker task and event stream code

- [ ] 37. Create worker block frame tests
  - Test worker block with frame field access
  - Test atomic operations on fields
  - Test visibility enforcement in worker blocks
  - Test event stream processing
  - _Requirements: 8.1, 8.2, 8.3, 8.4, 8.5, 8.6_

- [ ] 37.1 Clean up worker block infrastructure
  - Remove any class-based worker block code
  - Consolidate frame-worker block integration
  - Remove redundant worker task code
  - Update event stream handling for frame fields
  - _Requirements: 8.1, 8.2, 8.3, 8.4, 8.5, 8.6_
  - **JIT Focus**: Optimize worker task and event stream code
  - **Cleanup**: Eliminate duplicate worker block logic

---

## Phase 9: Type System Integration

- [ ] 38. Integrate frames with type system
  - Add frame types to type inference
  - Support frame types in type aliases
  - Support frame types in union types
  - Support frame types in Option types
  - _Requirements: 14.1, 14.2, 14.3_
  - **JIT Focus**: Generate specialized code for each frame type combination
  - **Status**: Type system exists; extend for frame types

- [ ] 39. Implement frame subtyping
  - Support trait-based subtyping
  - Implement trait object type checking
  - Support polymorphic function calls
  - _Requirements: 14.4, 14.5_
  - **JIT Focus**: Generate specialized code for each trait implementation; optimize vtable dispatch

- [ ] 40. Create type system integration tests
  - Test frame types in type aliases
  - Test frame types in union types
  - Test frame types in Option types
  - Test trait-based subtyping
  - Test polymorphic function calls
  - _Requirements: 14.1, 14.2, 14.3, 14.4, 14.5_

- [ ] 40.1 Clean up type system infrastructure
  - Remove any class-based type system code
  - Consolidate frame type handling
  - Remove redundant type checking for classes
  - Update type inference for frame types
  - _Requirements: 14.1, 14.2, 14.3, 14.4, 14.5_
  - **JIT Focus**: Optimize type specialization for frame types
  - **Cleanup**: Eliminate duplicate type system logic

---

## Phase 10: Error Handling Integration

- [ ] 41. Implement error handling in frame methods
  - Support Result types in frame method returns
  - Support `?` operator in frame methods
  - Implement error propagation from frame methods
  - _Requirements: 12.1, 12.2, 12.3_
  - **JIT Focus**: Generate efficient error propagation code; eliminate error checks in success paths
  - **Status**: Error handling exists; extend for frame methods

- [ ] 42. Implement error handling in concurrency blocks
  - Collect errors in parallel blocks
  - Propagate errors from concurrent tasks
  - Implement `on_error` policy handling
  - _Requirements: 12.4, 12.5_
  - **JIT Focus**: Generate efficient error collection and propagation code

- [ ] 43. Create error handling integration tests
  - Test Result types in frame methods
  - Test `?` operator in frame methods
  - Test error propagation from frame methods
  - Test error handling in parallel blocks
  - Test error handling in concurrent blocks
  - _Requirements: 12.1, 12.2, 12.3, 12.4, 12.5_

- [ ] 43.1 Clean up error handling infrastructure
  - Remove any class-based error handling code
  - Consolidate frame error handling
  - Remove redundant error checking for classes
  - Update error propagation for frame methods
  - _Requirements: 12.1, 12.2, 12.3, 12.4, 12.5_
  - **JIT Focus**: Optimize error propagation code generation
  - **Cleanup**: Eliminate duplicate error handling logic

---

## Phase 11: Memory Management Integration

- [ ] 44. Integrate frames with memory system
  - Allocate frames in region-based memory
  - Track frame lifetimes
  - Implement automatic cleanup on scope exit
  - _Requirements: 13.1, 13.2_
  - **JIT Focus**: Generate efficient frame allocation and cleanup code
  - **Status**: Memory system exists; extend for frames

- [ ] 45. Implement embedded frame cleanup
  - Track embedded frame cleanup order
  - Call deinit() in reverse order
  - Handle nested embedded frames
  - _Requirements: 13.3, 13.4_
  - **JIT Focus**: Generate efficient cleanup code; inline deinit calls where possible

- [ ] 46. Create memory management tests
  - Test frame allocation and cleanup
  - Test embedded frame cleanup order
  - Test nested embedded frame cleanup
  - Test memory leak prevention
  - _Requirements: 13.1, 13.2, 13.3, 13.4, 13.5_

- [ ] 46.1 Clean up memory management infrastructure
  - Remove any class-based memory management code
  - Consolidate frame memory handling
  - Remove redundant memory tracking for classes
  - Update region-based allocation for frames
  - _Requirements: 13.1, 13.2, 13.3, 13.4, 13.5_
  - **JIT Focus**: Optimize frame allocation and cleanup
  - **Cleanup**: Eliminate duplicate memory management logic

---

## Phase 12: Debugging and Introspection

- [ ] 47. Implement frame debugging support
  - Add frame field inspection to debugger
  - Add frame method call tracking
  - Add trait implementation display
  - _Requirements: 15.1, 15.2, 15.3_
  - **JIT Focus**: Generate debug information for frame types and methods
  - **Status**: Debugger exists; extend for frames

- [ ] 48. Implement frame introspection
  - Add frame metadata access
  - Add field type information
  - Add method signature information
  - _Requirements: 15.4, 15.5_
  - **JIT Focus**: Generate compile-time frame metadata for introspection

- [ ] 49. Create debugging tests
  - Test frame field inspection
  - Test frame method call tracking
  - Test trait implementation display
  - _Requirements: 15.1, 15.2, 15.3_

- [ ] 49.1 Clean up debugging infrastructure
  - Remove any class-based debugging code
  - Consolidate frame debugging support
  - Remove redundant debugging for classes
  - Update debugger for frame types
  - _Requirements: 15.1, 15.2, 15.3, 15.4, 15.5_
  - **JIT Focus**: Optimize debug information generation
  - **Cleanup**: Eliminate duplicate debugging logic

---

## Phase 13: Comprehensive Integration Tests

- [ ] 50. Create comprehensive frame integration tests
  - Test frames with all language features
  - Test frames in modules
  - Test frames with pattern matching
  - Test frames with concurrency
  - Test frames with error handling
  - _Requirements: All_

- [ ] 51. Create frame example programs
  - Implement example: Simple data frame
  - Implement example: Frame with traits
  - Implement example: Composed frames
  - Implement example: Parallel frame processing
  - Implement example: Concurrent frame processing
  - _Requirements: All_

---

## Summary

This implementation plan covers all aspects of the frames OOP system:

1. **Core Frame System** (Tasks 1-7): Basic frame declaration, instantiation, and method calls
2. **Visibility Control** (Tasks 8-10): Enforce private, protected, and public access
3. **Trait System** (Tasks 11-17): Define traits, implement them, and support polymorphism
4. **Composition** (Tasks 18-21): Embed frames and manage composition
5. **Lifecycle** (Tasks 22-25): Implement init/deinit methods
6. **Parallel Integration** (Tasks 26-29): Support parallel blocks in frames
7. **Concurrent Integration** (Tasks 30-37): Support concurrent blocks (batch and stream)
8. **Type System** (Tasks 38-40): Integrate with type system
9. **Error Handling** (Tasks 41-43): Support error handling in frames
10. **Memory Management** (Tasks 44-46): Integrate with memory system
11. **Debugging** (Tasks 47-49): Add debugging support
12. **Integration** (Tasks 50-51): Comprehensive testing and examples

Each task is actionable, references specific requirements, and focuses on coding activities only.

**Key Insight**: Most infrastructure already exists (concurrency, type system, memory management, error handling). The main work is creating frame-specific AST nodes and adapting existing systems to support frames.

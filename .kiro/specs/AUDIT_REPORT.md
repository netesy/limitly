# Specification Audit Report: Frames OOP System vs Current Codebase

**Date**: February 2, 2026  
**Status**: Comprehensive audit of all specs against current implementation

---

## Executive Summary

The Limit language codebase has significant OOP infrastructure already in place, but it's based on a **class-based model** rather than the **frame-based composition model** specified in the new frames spec. This audit identifies:

- ✅ **Already Implemented**: Core infrastructure (AST, parser, type system, concurrency)
- ⚠️ **Partially Implemented**: Classes, traits, visibility system
- ❌ **Not Implemented**: Frame-specific features, composition patterns, frame lifecycle

---

## 1. AST and Language Constructs

### Current Implementation Status

| Feature | Status | Location | Notes |
|---------|--------|----------|-------|
| **ClassDeclaration** | ✅ Implemented | `src/frontend/ast.hh:454-481` | Full class support with inheritance, interfaces, visibility |
| **TraitDeclaration** | ✅ Implemented | `src/frontend/ast.hh:699-703` | Basic trait support with methods |
| **FrameDeclaration** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |
| **FrameField** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |
| **FrameMethod** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |
| **VisibilityLevel** | ✅ Implemented | `src/frontend/ast.hh:109-113` | Private, Protected, Public, Const |
| **ParallelStatement** | ✅ Implemented | `src/frontend/ast.hh:526-533` | With cores, timeout, grace, on_error |
| **ConcurrentStatement** | ✅ Implemented | `src/frontend/ast.hh:534-547` | With channel, mode, cores, timeout |
| **TaskStatement** | ✅ Implemented | `src/frontend/ast.hh:548-558` | For concurrent batch mode |
| **WorkerStatement** | ✅ Implemented | `src/frontend/ast.hh:560-568` | For concurrent stream mode |

### Key Differences from Spec

**Current (Class-Based)**:
```cpp
struct ClassDeclaration : public Statement {
    std::string name;
    std::vector<std::shared_ptr<VarDeclaration>> fields;
    std::vector<std::shared_ptr<FunctionDeclaration>> methods;
    std::string superClassName;  // Inheritance
    std::vector<std::string> interfaces;
    bool isAbstract, isFinal, isDataClass;
    std::map<std::string, VisibilityLevel> fieldVisibility;
    std::map<std::string, VisibilityLevel> methodVisibility;
};
```

**Spec (Frame-Based)**:
```cpp
struct FrameDeclaration : public Statement {
    std::string name;
    std::vector<std::shared_ptr<FrameField>> fields;      // Separate field type
    std::vector<std::shared_ptr<FrameMethod>> methods;    // Separate method type
    std::vector<std::string> implements;                  // Traits, not inheritance
    std::shared_ptr<FrameMethod> init;                    // Lifecycle hooks
    std::shared_ptr<FrameMethod> deinit;
};
```

### Recommendation

**Decision Point**: Should we:
1. **Extend ClassDeclaration** to support frame semantics (composition, no inheritance)
2. **Create FrameDeclaration** as a new construct alongside ClassDeclaration
3. **Replace ClassDeclaration** with FrameDeclaration (breaking change)

**Recommended**: Option 2 - Create FrameDeclaration as new construct, keep ClassDeclaration for backward compatibility

---

## 2. Parser Implementation

### Current Status

| Feature | Status | Location | Notes |
|---------|--------|----------|-------|
| **Class Parsing** | ✅ Implemented | `src/frontend/parser.cpp` | Handles `class` keyword |
| **Trait Parsing** | ⚠️ Partial | `src/frontend/parser.cpp` | Basic trait parsing exists |
| **Frame Parsing** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |
| **Visibility Modifiers** | ✅ Implemented | Parser | Recognizes `pub`, `prot` keywords |
| **Parallel Blocks** | ✅ Implemented | Parser | Full parallel block parsing |
| **Concurrent Blocks** | ✅ Implemented | Parser | Full concurrent block parsing |

### Parser Methods Needed

```cpp
// In src/frontend/parser.hh/cpp
std::shared_ptr<AST::FrameDeclaration> parseFrame();
std::shared_ptr<AST::FrameField> parseFrameField();
std::shared_ptr<AST::FrameMethod> parseFrameMethod();
std::shared_ptr<AST::TraitDeclaration> parseTrait();  // Enhance existing
```

### Recommendation

Create new parser methods for frame-specific syntax while reusing existing infrastructure for visibility, concurrency blocks, etc.

---

## 3. Type System

### Current Implementation Status

| Feature | Status | Location | Notes |
|---------|--------|----------|-------|
| **Type Inference** | ✅ Implemented | `src/backend/types.hh` | Full type inference system |
| **Union Types** | ✅ Implemented | Type system | `T \| U` syntax |
| **Option Types** | ✅ Implemented | Type system | `Some \| None` |
| **Type Aliases** | ✅ Implemented | Type system | `type Name = Type;` |
| **FrameType** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |
| **TraitType** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |
| **TraitObjectType** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |
| **Visibility Enforcement** | ⚠️ Partial | Type checker | Works for classes, needs frame support |

### Type System Architecture

Current type tags in `TypeTag` enum:
- Primitive types (Int, Float, Bool, String, etc.)
- Collection types (List, Dict, Tuple)
- Function types
- User-defined types (Classes)
- Union types
- Option types

**Missing**:
- Frame types
- Trait types
- Trait object types (for dynamic dispatch)

### Recommendation

Add new type tags to `TypeTag` enum:
```cpp
enum class TypeTag {
    // ... existing tags ...
    Frame,           // Frame type
    Trait,           // Trait type
    TraitObject,     // Trait object (&Trait)
};
```

---

## 4. Concurrency Support

### Current Implementation Status

| Feature | Status | Location | Notes |
|---------|--------|----------|-------|
| **Parallel Blocks** | ✅ Implemented | AST, Parser, LIR, VM | Full support with `iter` |
| **Concurrent Blocks (Batch)** | ✅ Implemented | AST, Parser, LIR, VM | Full support with `task` |
| **Concurrent Blocks (Stream)** | ✅ Implemented | AST, Parser, LIR, VM | Full support with `worker` |
| **Channels** | ✅ Implemented | Runtime | Full channel support |
| **Atomic Operations** | ✅ Implemented | VM | For shared field access |
| **Frame Context** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |

### Current Concurrency Model

```cpp
struct ParallelStatement : public Statement {
    std::string cores;
    std::string timeout;
    std::string grace;
    std::string on_error;
    std::shared_ptr<BlockStatement> body;
};

struct ConcurrentStatement : public Statement {
    std::string channel;
    std::string mode;  // "batch" or "stream"
    std::string cores;
    std::string onError;
    std::string timeout;
    std::shared_ptr<BlockStatement> body;
};
```

### What Needs to Change

1. **Frame Context Tracking**: Parallel/concurrent blocks need to know which frame they're in
2. **Field Access Control**: Enforce visibility rules in concurrency blocks
3. **Atomic Operations**: Ensure `pub` and `prot` fields use atomic access

### Recommendation

Extend concurrency statements to track frame context:
```cpp
struct ParallelStatement : public Statement {
    // ... existing fields ...
    std::string frame_context;  // Which frame this parallel block belongs to
    std::set<std::string> accessible_fields;  // pub/prot fields accessible
};
```

---

## 5. Visibility System

### Current Implementation Status

| Feature | Status | Location | Notes |
|---------|--------|----------|-------|
| **VisibilityLevel Enum** | ✅ Implemented | `src/frontend/ast.hh:109-113` | Private, Protected, Public, Const |
| **Field Visibility** | ✅ Implemented | ClassDeclaration | Via `fieldVisibility` map |
| **Method Visibility** | ✅ Implemented | ClassDeclaration | Via `methodVisibility` map |
| **Visibility Enforcement** | ⚠️ Partial | Type checker | Works for classes, needs frame support |
| **Protected Access** | ⚠️ Partial | Type checker | Needs trait implementation context |

### Current Visibility Enforcement

```cpp
// In type checker
std::map<std::string, VisibilityLevel> fieldVisibility;
std::map<std::string, VisibilityLevel> methodVisibility;
```

### What Needs to Change

1. **Frame-Specific Visibility**: Extend to support frame fields/methods
2. **Trait Context**: Protected members accessible in trait implementations
3. **Concurrency Context**: Visibility rules in parallel/concurrent blocks

### Recommendation

Enhance visibility enforcement to support frames and trait contexts.

---

## 6. Lifecycle Management

### Current Implementation Status

| Feature | Status | Location | Notes |
|---------|--------|----------|-------|
| **init() Method** | ⚠️ Partial | ClassDeclaration | Inline constructor support exists |
| **deinit() Method** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |
| **Automatic Cleanup** | ⚠️ Partial | VM | Basic cleanup exists |
| **Guaranteed Execution** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |
| **Embedded Frame Cleanup** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |

### Current Constructor Support

```cpp
// In ClassDeclaration
std::vector<std::pair<std::string, std::shared_ptr<TypeAnnotation>>> constructorParams;
bool hasInlineConstructor = false;
```

### What Needs to Change

1. **Explicit init() Method**: Support optional `pub init()` method
2. **Destructor Support**: Implement `pub deinit()` method
3. **Guaranteed Execution**: Ensure deinit() runs even during errors
4. **Cleanup Order**: Reverse order for embedded frames

### Recommendation

Add lifecycle method support to FrameDeclaration:
```cpp
struct FrameDeclaration : public Statement {
    // ... other fields ...
    std::shared_ptr<FrameMethod> init;    // optional
    std::shared_ptr<FrameMethod> deinit;  // optional
};
```

---

## 7. Composition Support

### Current Implementation Status

| Feature | Status | Location | Notes |
|---------|--------|----------|-------|
| **Embedded Objects** | ⚠️ Partial | Type system | Fields can be other types |
| **Composition** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |
| **Method Delegation** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |
| **Embedded Cleanup** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |

### Current Field Support

```cpp
// In ClassDeclaration
std::vector<std::shared_ptr<VarDeclaration>> fields;
```

Fields can have any type, but no special composition semantics.

### What Needs to Change

1. **Composition Semantics**: Embedded frames should be initialized/cleaned up automatically
2. **Method Delegation**: Public methods of embedded frames accessible through parent
3. **Cleanup Order**: Embedded frames destroyed in reverse order

### Recommendation

Implement composition-specific logic in LIR generation and VM execution.

---

## 8. Error Handling Integration

### Current Implementation Status

| Feature | Status | Location | Notes |
|---------|--------|----------|-------|
| **Result Types** | ✅ Implemented | Type system | `T?ErrorType` syntax |
| **? Operator** | ✅ Implemented | Parser, LIR, VM | Error propagation |
| **Error Handling in Methods** | ✅ Implemented | Type system | Methods can return Result types |
| **Error Handling in Concurrency** | ⚠️ Partial | VM | Basic error handling exists |
| **Frame Method Errors** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |

### Current Error Handling

```cpp
struct FallibleExpr : public Expression {
    std::shared_ptr<Expression> expression;
    std::shared_ptr<Statement> elseHandler;
    std::string elseVariable;
};
```

### What Needs to Change

1. **Frame Method Errors**: Support Result types in frame methods
2. **Error Propagation**: Ensure errors propagate correctly from frame methods
3. **Concurrency Errors**: Collect/propagate errors from parallel/concurrent blocks

### Recommendation

Extend error handling to work with frame methods and concurrency blocks.

---

## 9. Memory Management

### Current Implementation Status

| Feature | Status | Location | Notes |
|---------|--------|----------|-------|
| **Region-Based Allocation** | ✅ Implemented | `src/memory/memory.hh` | Full memory management |
| **Automatic Cleanup** | ✅ Implemented | VM | RAII-style cleanup |
| **Lifetime Tracking** | ✅ Implemented | Type checker | Memory safety checks |
| **Frame Allocation** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |
| **Embedded Frame Cleanup** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |

### Current Memory System

```cpp
// In src/memory/memory.hh
class MemoryManager {
    // Region-based allocation
    // Automatic cleanup on scope exit
};
```

### What Needs to Change

1. **Frame Allocation**: Allocate frames in memory system
2. **Embedded Frame Tracking**: Track embedded frame lifetimes
3. **Cleanup Order**: Ensure reverse-order cleanup

### Recommendation

Extend memory system to support frame-specific allocation and cleanup.

---

## 10. Module System

### Current Implementation Status

| Feature | Status | Location | Notes |
|---------|--------|----------|-------|
| **Module Declaration** | ✅ Implemented | AST | `ModuleDeclaration` exists |
| **Import/Export** | ✅ Implemented | Parser | Full import/export support |
| **Visibility Across Modules** | ✅ Implemented | Type checker | Visibility enforced |
| **Frame Module Support** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |

### Recommendation

Module system should work with frames once frames are implemented.

---

## 11. Debugging Support

### Current Implementation Status

| Feature | Status | Location | Notes |
|---------|--------|----------|-------|
| **AST Printing** | ✅ Implemented | `src/error/debugger.cpp` | Full AST visualization |
| **Error Messages** | ✅ Implemented | `src/error/message.hh` | Comprehensive error reporting |
| **Frame Debugging** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |
| **Trait Debugging** | ❌ Missing | N/A | **NEEDS IMPLEMENTATION** |

### Recommendation

Extend debugger to support frame and trait introspection.

---

## Summary of Changes Needed

### Phase 1: Core Frame Infrastructure (CRITICAL)

| Task | Effort | Priority |
|------|--------|----------|
| Add FrameDeclaration AST node | Medium | 🔴 Critical |
| Add FrameField and FrameMethod AST nodes | Medium | 🔴 Critical |
| Add FrameType to type system | Medium | 🔴 Critical |
| Implement frame parsing | High | 🔴 Critical |
| Implement frame type checking | High | 🔴 Critical |
| Implement frame LIR generation | High | 🔴 Critical |
| Implement frame VM execution | High | 🔴 Critical |

### Phase 2: Visibility and Access Control

| Task | Effort | Priority |
|------|--------|----------|
| Extend visibility enforcement to frames | Medium | 🟠 High |
| Implement protected access in traits | Medium | 🟠 High |
| Enforce visibility in concurrency blocks | Medium | 🟠 High |

### Phase 3: Trait System Enhancement

| Task | Effort | Priority |
|------|--------|----------|
| Add TraitType to type system | Medium | 🟠 High |
| Add TraitObjectType for dynamic dispatch | High | 🟠 High |
| Implement trait object creation | High | 🟠 High |
| Implement virtual method table | High | 🟠 High |

### Phase 4: Composition and Lifecycle

| Task | Effort | Priority |
|------|--------|----------|
| Implement embedded frame support | High | 🟠 High |
| Implement init() method support | Medium | 🟠 High |
| Implement deinit() method support | High | 🟠 High |
| Implement guaranteed deinit() execution | High | 🟠 High |

### Phase 5: Concurrency Integration

| Task | Effort | Priority |
|------|--------|----------|
| Add frame context to parallel blocks | Medium | 🟡 Medium |
| Add frame context to concurrent blocks | Medium | 🟡 Medium |
| Implement atomic field access | Medium | 🟡 Medium |
| Implement error handling in concurrency | Medium | 🟡 Medium |

### Phase 6: Advanced Features

| Task | Effort | Priority |
|------|--------|----------|
| Type system integration | Medium | 🟡 Medium |
| Error handling integration | Medium | 🟡 Medium |
| Memory management integration | Medium | 🟡 Medium |
| Debugging support | Low | 🟢 Low |

---

## Recommendations

### 1. **Coexistence Strategy**

Keep both `ClassDeclaration` and `FrameDeclaration`:
- Classes: Traditional OOP with inheritance (backward compatible)
- Frames: Modern OOP with composition (new feature)
- Both can implement traits
- Both support concurrency blocks

### 2. **Implementation Order**

1. **First**: Core frame infrastructure (AST, parser, type system)
2. **Second**: Visibility and trait system
3. **Third**: Composition and lifecycle
4. **Fourth**: Concurrency integration
5. **Fifth**: Advanced features and debugging

### 3. **Code Reuse**

Reuse existing infrastructure:
- ✅ Visibility system (already works)
- ✅ Concurrency blocks (already work)
- ✅ Type system (extend with frame types)
- ✅ Memory management (extend for frames)
- ✅ Error handling (extend for frame methods)

### 4. **Testing Strategy**

Create comprehensive tests for:
1. Frame declaration and instantiation
2. Field and method access
3. Visibility enforcement
4. Trait implementation
5. Composition and embedding
6. Lifecycle management
7. Concurrency integration
8. Error handling
9. Memory management

---

## Conclusion

The Limit language has a solid foundation for implementing frames. Most of the infrastructure is already in place (concurrency, type system, memory management, error handling). The main work is:

1. **Creating frame-specific AST nodes** (FrameDeclaration, FrameField, FrameMethod)
2. **Implementing frame parsing** (extend parser)
3. **Adding frame types** (extend type system)
4. **Implementing frame semantics** (composition, lifecycle, visibility)
5. **Integrating with existing systems** (concurrency, error handling, memory)

The spec is well-aligned with the current codebase architecture. Implementation should proceed in phases, starting with core frame infrastructure and progressing to advanced features.


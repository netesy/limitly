# Design Document

## Overview

This design document outlines the complete integration of classes into the Limit programming language, ensuring seamless interoperability with error handling (`?` operator), pattern matching (`match` expressions), the type system (union types, Option types), modules, and concurrency primitives. The design builds upon the existing class infrastructure while extending it to work with all language features.

## Cross-Spec Integration

### Dependencies
- **Error Handling System**: Classes must integrate with Result types and error propagation
- **Advanced Type System**: Classes must work with union types, type aliases, and Option types  
- **Module System**: Classes must support import/export with visibility controls
- **Concurrency System**: Classes must be thread-safe and work in parallel/concurrent contexts
- **Pattern Matching**: Classes must be matchable and destructurable

### Implementation Coordination
- **Shared Type System**: Extends the existing `TypeSystem` class in `backend/types.hh`
- **Shared AST Nodes**: Uses existing `ClassDeclaration` and extends with new integration nodes
- **Shared Runtime**: Integrates with existing VM, error handling, and concurrency systems
- **Shared Memory Management**: Uses existing region-based memory system

## Architecture Overview

### 1. Enhanced Class Type System
- **Class Types**: Full integration with the type system as first-class types
- **Inheritance Types**: Subtyping relationships for inheritance hierarchies
- **Interface Types**: Abstract contracts for class behavior
- **Class Union Types**: Classes in union types with pattern matching support

### 2. Class Error Integration
- **Error Classes**: Classes that can be used as error types
- **Method Error Handling**: Class methods that return Result types
- **Constructor Error Handling**: Constructors that can fail gracefully
- **Error Inheritance**: Error class hierarchies with proper propagation

### 3. Class Pattern Matching
- **Type Patterns**: Matching on class types and inheritance
- **Destructuring Patterns**: Extracting class fields in patterns
- **Guard Patterns**: Using class methods and fields in pattern guards
- **Nested Patterns**: Complex patterns involving class hierarchies

### 4. Class Concurrency Support
- **Thread Safety**: Automatic synchronization for class instances
- **Concurrent Methods**: Class methods that work in parallel contexts
- **Channel Integration**: Passing class instances through channels
- **Atomic Operations**: Class-based atomic operations and synchronization

## Detailed Design

### 1. Class Visibility and Access Control System

The class system implements comprehensive visibility controls with private-by-default semantics:

```limit
// Private by default - explicit types required
class BankAccount {
    balance: float = 0.0;           // Private field with default value
    accountNumber: str;             // Private field, must be initialized
    
    pub fn deposit(amount: float) { // Public method
        self.balance += amount;
    }
    
    prot fn validateAmount(amount: float) : bool { // Protected method
        return amount > 0.0;
    }
    
    static pub fn createAccount(number: str) : BankAccount { // Static public method
        return BankAccount { accountNumber: number };
    }
    
    pub(read) balance: float;       // Read-only public field
}

// Abstract class with final methods
abstract class Shape {
    abstract fn area() : float;     // Must be implemented
    final fn describe() {           // Cannot be overridden
        print("Area: {self.area()}");
    }
}

// Final class - cannot be inherited
final class Circle : Shape {
    pub radius: float;
    
    fn area() : float {             // Implements abstract method
        return 3.14159 * self.radius * self.radius;
    }
}
```

#### Data Classes - Immutable Value Types

The `data` keyword provides syntactic sugar for creating immutable, final, region-safe classes optimized for data storage and pattern matching:

```limit
// Data class - syntactic sugar for immutable, final class
data Point {
    x: float;
    y: float;
}

// Equivalent to:
final class Point {
    pub(read) x: float;
    pub(read) y: float;
    
    // Auto-generated constructor
    pub fn init(x: float, y: float) {
        self.x = x;
        self.y = y;
    }
    
    // Auto-generated equality
    pub fn equals(other: Point) : bool {
        return self.x == other.x && self.y == other.y;
    }
    
    // Auto-generated hash
    pub fn hash() : int {
        return hash(self.x) ^ hash(self.y);
    }
    
    // Auto-generated toString
    pub fn toString() : str {
        return "Point(x: {self.x}, y: {self.y})";
    }
}

// Data classes work seamlessly with pattern matching
data Result {
    value: int | None;
    error: str | None;
}

fn processResult(result: Result) {
    match result {
        Result { value: Some(v), error: None } => print("Success: {v}"),
        Result { value: None, error: Some(e) } => print("Error: {e}"),
        _ => print("Invalid result state")
    }
}
```

#### Comprehensive Data Class Examples

```limit
// Simple data class for coordinates
data Point {
    x: float;
    y: float;
}

// Usage with auto-generated methods
var p1 = Point(3.0, 4.0);
var p2 = Point(3.0, 4.0);
print(p1.toString());           // "Point(x: 3.0, y: 4.0)"
print(p1.equals(p2));           // true
print(p1.hash());               // auto-generated hash value

// Data class with union types for optional values
data Person {
    name: str;
    age: int | None;
    email: str | None;
}

// Pattern matching with data classes
fn describePerson(person: Person) {
    match person {
        Person { name: n, age: Some(a), email: Some(e) } => 
            print("{n} is {a} years old, email: {e}"),
        Person { name: n, age: Some(a), email: None } => 
            print("{n} is {a} years old, no email"),
        Person { name: n, age: None, email: Some(e) } => 
            print("{n}, age unknown, email: {e}"),
        Person { name: n, age: None, email: None } => 
            print("{n}, minimal info")
    }
}

// Data class for error handling
data ValidationError {
    field: str;
    message: str;
    code: int;
}

// Data class for results with structural typing
data ApiResponse {
    status: int;
    data: str | None;
    error: ValidationError | None;
}

fn handleResponse(response: ApiResponse) {
    match response {
        ApiResponse { status: 200, data: Some(d), error: None } => 
            print("Success: {d}"),
        ApiResponse { status: s, data: None, error: Some(e) } => 
            print("Error {s}: {e.message} in field {e.field}"),
        _ => print("Unexpected response format")
    }
}

// Data classes are immutable - this would be a compile error:
// p1.x = 5.0;  // Error: Cannot modify immutable field

// But you can create new instances
var p3 = Point(p1.x + 1.0, p1.y + 1.0);
```

#### Data Class Features
- **Immutable by default**: All fields are `pub(read)` - readable but not writable after construction
- **Final**: Cannot be inherited (automatically `final`)
- **Region-safe**: Optimized for stack allocation and efficient copying
- **Auto-generated methods**: Constructor, equality, hash, and toString methods
- **Pattern matching optimized**: Efficient destructuring in match expressions
- **Value semantics**: Copied by value, not reference
- **Structural typing**: Works seamlessly with union types and Option types

#### Visibility Rules
- **Private by default**: All members are private unless explicitly marked
- **`pub`**: Explicitly public, accessible from anywhere
- **`prot`**: Protected, accessible from subclasses only
- **`pub(read)`**: Read-only public access, write access is private
- **`static`**: Class-level members, accessed via ClassName.member
- **`abstract`**: Must be implemented in concrete subclasses
- **`final`**: Cannot be inherited (classes) or overridden (methods)
- **`data`**: Syntactic sugar for immutable, final, region-safe classes

### 2. Enhanced Type System Integration

#### Scanner and Parser Extensions

```cpp
// New tokens in frontend/scanner.hh
enum class TokenType {
    // ... existing tokens ...
    PUB,        // pub
    PROT,       // prot  
    STATIC,     // static
    ABSTRACT,   // abstract
    FINAL,      // final
    DATA,       // data
    READ,       // read (for pub(read))
    // ... existing tokens ...
};
```

```cpp
// Enhanced ClassDeclaration in frontend/ast.hh
struct ClassDeclaration : public Statement {
    std::string name;
    std::vector<std::shared_ptr<VarDeclaration>> fields;
    std::vector<std::shared_ptr<FunctionDeclaration>> methods;
    
    // Visibility and inheritance
    std::string superClassName;
    std::vector<std::shared_ptr<Expression>> superConstructorArgs;
    std::vector<std::pair<std::string, std::shared_ptr<TypeAnnotation>>> constructorParams;
    bool hasInlineConstructor = false;
    
    // New visibility features
    bool isAbstract = false;
    bool isFinal = false;
    bool isDataClass = false;  // Data class flag
    std::vector<std::string> interfaces;
    
    // Field and method visibility
    std::map<std::string, VisibilityLevel> fieldVisibility;
    std::map<std::string, VisibilityLevel> methodVisibility;
    std::set<std::string> staticMembers;
    std::set<std::string> abstractMethods;
    std::set<std::string> finalMethods;
    std::set<std::string> readOnlyFields;
};

enum class VisibilityLevel {
    Private,    // Default
    Protected,  // prot
    Public,     // pub
    ReadOnly    // pub(read)
};

// Data class declaration - syntactic sugar for immutable classes
struct DataClassDeclaration : public Statement {
    std::string name;
    std::vector<std::shared_ptr<VarDeclaration>> fields;
    
    // Auto-generated methods (created during parsing)
    std::shared_ptr<FunctionDeclaration> constructor;
    std::shared_ptr<FunctionDeclaration> equalsMethod;
    std::shared_ptr<FunctionDeclaration> hashMethod;
    std::shared_ptr<FunctionDeclaration> toStringMethod;
    
    // Converts to equivalent ClassDeclaration during parsing
    std::shared_ptr<ClassDeclaration> toClassDeclaration() const;
};
```

#### Class Type Representation
```cpp
// Enhanced class type in backend/types.hh
struct ClassType : public Type {
    std::string name;
    std::vector<std::shared_ptr<Type>> fieldTypes;
    std::vector<std::string> fieldNames;
    std::shared_ptr<ClassType> superClass;
    std::vector<std::shared_ptr<InterfaceType>> interfaces;
    
    // Visibility and access control
    std::map<std::string, VisibilityLevel> fieldVisibility;
    std::map<std::string, VisibilityLevel> methodVisibility;
    std::set<std::string> staticMembers;
    std::set<std::string> abstractMethods;
    std::set<std::string> finalMethods;
    std::set<std::string> readOnlyFields;
    
    // Class modifiers
    bool isErrorType = false;
    bool isAbstract = false;
    bool isFinal = false;
    bool isDataClass = false;  // Data class optimization flag
    
    // Integration methods
    bool canConvertTo(const Type& other) const override;
    bool isSubtypeOf(const ClassType& other) const;
    bool implementsInterface(const InterfaceType& interface) const;
    bool canAccess(const std::string& member, const ClassType* accessingClass) const;
};

// Interface type for class contracts
struct InterfaceType : public Type {
    std::string name;
    std::vector<std::pair<std::string, std::shared_ptr<FunctionType>>> methods;
    std::vector<std::pair<std::string, std::shared_ptr<Type>>> properties;
};
```

#### Type System Enhancements
```cpp
class TypeSystem {
private:
    std::map<std::string, std::shared_ptr<ClassType>> classTypes;
    std::map<std::string, std::shared_ptr<InterfaceType>> interfaceTypes;
    
public:
    // Class type management
    void registerClass(const std::string& name, std::shared_ptr<ClassType> type);
    std::shared_ptr<ClassType> getClassType(const std::string& name);
    bool isClassType(const std::string& name);
    
    // Interface type management
    void registerInterface(const std::string& name, std::shared_ptr<InterfaceType> type);
    std::shared_ptr<InterfaceType> getInterfaceType(const std::string& name);
    
    // Integration methods
    bool canAssign(const Type& from, const Type& to) override;
    std::shared_ptr<Type> createUnionWithClass(const std::vector<std::shared_ptr<Type>>& types);
    std::shared_ptr<Type> createOptionType(std::shared_ptr<ClassType> classType);
};
```

### 2. Error Handling Integration

#### Error Class Support
```cpp
// Enhanced AST for error classes
struct ErrorClassDeclaration : public ClassDeclaration {
    std::string errorCode;
    std::vector<std::pair<std::string, std::shared_ptr<TypeAnnotation>>> errorFields;
    bool isBuiltinError = false;
};

// Error class runtime representation
struct ErrorClassValue : public Value {
    std::shared_ptr<ClassType> errorType;
    std::map<std::string, ValuePtr> errorFields;
    std::string message;
    std::string stackTrace;
    
    std::string toString() const override;
    ValuePtr getField(const std::string& name) const;
    void setField(const std::string& name, ValuePtr value);
};
```

#### Method Error Handling
```cpp
// Enhanced method declaration with error handling
struct MethodDeclaration : public FunctionDeclaration {
    bool canThrow = false;
    std::vector<std::shared_ptr<Type>> throwableTypes;
    std::shared_ptr<Type> errorReturnType;  // For Result<T, E> returns
};

// VM opcodes for class error handling
enum class Opcode {
    // ... existing opcodes ...
    
    // Class error handling
    THROW_CLASS_ERROR,      // Throw a class-based error
    CATCH_CLASS_ERROR,      // Catch specific class error types
    PROPAGATE_CLASS_ERROR,  // Propagate error through class method chain
    CHECK_CLASS_ERROR,      // Check if class method returned error
};
```

### 3. Pattern Matching Integration

#### Class Pattern AST Nodes
```cpp
// Class-based pattern matching
struct ClassPattern : public Pattern {
    std::string className;
    std::vector<std::shared_ptr<Pattern>> fieldPatterns;
    std::vector<std::string> fieldNames;
    bool isExhaustive = false;
};

struct InheritancePattern : public Pattern {
    std::string baseClassName;
    std::shared_ptr<Pattern> derivedPattern;
    bool matchExact = false;  // Match exact type vs subtype
};

struct InterfacePattern : public Pattern {
    std::string interfaceName;
    std::vector<std::shared_ptr<Pattern>> methodPatterns;
};
```

#### Pattern Matching Runtime
```cpp
class ClassPatternMatcher {
public:
    // Core pattern matching methods
    bool matchesClassPattern(ValuePtr value, const ClassPattern& pattern);
    bool matchesInheritancePattern(ValuePtr value, const InheritancePattern& pattern);
    bool matchesInterfacePattern(ValuePtr value, const InterfacePattern& pattern);
    
    // Pattern extraction methods
    std::map<std::string, ValuePtr> extractClassFields(ValuePtr value, const ClassPattern& pattern);
    ValuePtr extractInheritanceValue(ValuePtr value, const InheritancePattern& pattern);
    
    // Integration with existing pattern matching
    bool isCompatibleWithUnionPattern(const ClassPattern& classPattern, const UnionPattern& unionPattern);
};
```

### 4. Concurrency Integration

#### Thread-Safe Class Operations
```cpp
// Thread-safe class instance
struct ConcurrentClassInstance : public ClassInstance {
    mutable std::shared_mutex instanceMutex;
    std::atomic<bool> isBeingModified{false};
    
    // Thread-safe field access
    ValuePtr getFieldSafe(const std::string& name) const;
    void setFieldSafe(const std::string& name, ValuePtr value);
    
    // Thread-safe method calls
    ValuePtr callMethodSafe(const std::string& name, const std::vector<ValuePtr>& args);
};

// Class-based synchronization primitives
class ClassMutex : public ClassInstance {
public:
    void lock();
    void unlock();
    bool tryLock();
    
private:
    std::mutex mutex;
};

class ClassChannel : public ClassInstance {
public:
    void send(ValuePtr value);
    ValuePtr receive();
    bool tryReceive(ValuePtr& value);
    
private:
    std::shared_ptr<Channel<ValuePtr>> channel;
};
```

#### Concurrent Class Methods
```cpp
// VM support for concurrent class operations
class VM {
public:
    // Concurrent class method execution
    void handleConcurrentMethodCall(const Instruction& instruction);
    void handleParallelClassOperation(const Instruction& instruction);
    
    // Class instance synchronization
    void synchronizeClassAccess(std::shared_ptr<ClassInstance> instance);
    void releaseClassAccess(std::shared_ptr<ClassInstance> instance);
    
private:
    std::unordered_map<ClassInstance*, std::shared_mutex> classMutexes;
    std::shared_ptr<ThreadPool> threadPool;
};
```

### 5. Module System Integration

#### Class Visibility and Export
```cpp
// Enhanced class declaration with visibility
struct ClassDeclaration : public Statement {
    // ... existing fields ...
    
    // Module integration
    VisibilityLevel visibility = VisibilityLevel::Private;
    std::vector<std::string> exportedMethods;
    std::vector<std::string> exportedFields;
    bool isExported = false;
    
    // Interface implementation
    std::vector<std::string> implementedInterfaces;
};

// Module class registry
class ModuleClassRegistry {
public:
    void registerClass(const std::string& moduleName, const std::string& className, 
                      std::shared_ptr<ClassType> classType);
    std::shared_ptr<ClassType> importClass(const std::string& moduleName, 
                                          const std::string& className);
    bool isClassVisible(const std::string& moduleName, const std::string& className);
    
private:
    std::map<std::string, std::map<std::string, std::shared_ptr<ClassType>>> moduleClasses;
    std::map<std::string, std::set<std::string>> exportedClasses;
};
```

### 6. Class Instantiation and Fluent Interface Design

#### Class Instantiation Syntax
```cpp
// Enhanced class declaration with default values
struct ClassDeclaration : public Statement {
    // ... existing fields ...
    
    // Default value support
    std::map<std::string, std::shared_ptr<Expression>> fieldDefaults;
    std::shared_ptr<FunctionDeclaration> initMethod;  // Optional init() method
    bool hasInitMethod = false;
    
    // Fluent interface support
    std::vector<std::shared_ptr<MethodDeclaration>> fluentSetters;
    bool supportsFluentInterface = true;
};

// Class instantiation AST node
struct ClassInstantiation : public Expression {
    std::string className;
    std::map<std::string, std::shared_ptr<Expression>> fieldOverrides;
    bool callInit = false;  // Whether to automatically call init()
    
    // Method chaining support
    std::vector<std::shared_ptr<MethodCall>> chainedCalls;
};
```

#### Fluent Interface Implementation
```cpp
// Method declaration with fluent support
struct MethodDeclaration : public FunctionDeclaration {
    // ... existing fields ...
    
    // Fluent interface support
    bool returnsSelf = false;
    bool returnsSubtype = false;  // Returns Self type for inheritance
    bool isFluentSetter = false;
    
    // Optimization hints
    bool canInline = true;
    bool isZeroCost = true;
};

// Runtime support for fluent interfaces
class FluentInterfaceManager {
public:
    // Method chaining optimization
    std::shared_ptr<ClassInstance> optimizeMethodChain(
        std::shared_ptr<ClassInstance> instance,
        const std::vector<std::shared_ptr<MethodCall>>& chain);
    
    // Self-type resolution for inheritance
    std::shared_ptr<Type> resolveSelfType(
        std::shared_ptr<ClassType> currentType,
        std::shared_ptr<ClassType> actualType);
    
    // Inline optimization for setter chains
    void inlineSetterChain(std::shared_ptr<ClassInstance> instance,
                          const std::vector<std::shared_ptr<MethodCall>>& setters);
};
```

### 7. Class Inheritance and Self Types

#### Inheritance Type System
```cpp
// Enhanced inheritance support
struct InheritanceChain {
    std::shared_ptr<ClassType> baseClass;
    std::vector<std::shared_ptr<ClassType>> derivedClasses;
    std::map<std::string, std::shared_ptr<MethodDeclaration>> virtualMethods;
    std::map<std::string, std::shared_ptr<MethodDeclaration>> abstractMethods;
};

// Self type resolution
struct SelfType : public Type {
    std::shared_ptr<ClassType> contextClass;  // The class where Self is used
    std::shared_ptr<ClassType> actualClass;   // The actual runtime class
    
    // Type resolution methods
    std::shared_ptr<Type> resolve(std::shared_ptr<ClassType> runtimeType) const;
    bool isCompatibleWith(std::shared_ptr<Type> other) const;
};

// Abstract class and interface support
struct AbstractClassType : public ClassType {
    std::vector<std::string> abstractMethods;
    bool isInterface = false;
    
    // Validation methods
    bool isFullyImplemented(std::shared_ptr<ClassType> implementation) const;
    std::vector<std::string> getMissingImplementations(std::shared_ptr<ClassType> implementation) const;
};
```

#### Virtual Method Dispatch
```cpp
// Virtual method table for efficient dispatch
struct VirtualMethodTable {
    std::map<std::string, std::shared_ptr<MethodDeclaration>> methods;
    std::shared_ptr<VirtualMethodTable> parentVTable;
    
    // Method resolution
    std::shared_ptr<MethodDeclaration> resolveMethod(const std::string& name) const;
    void addMethod(const std::string& name, std::shared_ptr<MethodDeclaration> method);
    void overrideMethod(const std::string& name, std::shared_ptr<MethodDeclaration> method);
};

// Runtime method dispatch
class MethodDispatcher {
public:
    // Virtual method dispatch
    ValuePtr dispatchVirtualMethod(std::shared_ptr<ClassInstance> instance,
                                  const std::string& methodName,
                                  const std::vector<ValuePtr>& args);
    
    // Interface method dispatch
    ValuePtr dispatchInterfaceMethod(std::shared_ptr<ClassInstance> instance,
                                    const std::string& interfaceName,
                                    const std::string& methodName,
                                    const std::vector<ValuePtr>& args);
    
    // Optimization for final methods
    ValuePtr dispatchFinalMethod(std::shared_ptr<ClassInstance> instance,
                                const std::string& methodName,
                                const std::vector<ValuePtr>& args);
};
```

### 8. Memory Management Integration

#### Class Memory Layout
```cpp
// Optimized class instance layout
struct ClassInstance : public Value {
    std::shared_ptr<ClassType> classType;
    std::vector<ValuePtr> fields;  // Optimized field storage
    std::shared_ptr<ClassInstance> superInstance;  // For inheritance
    
    // Memory management
    std::shared_ptr<MemoryRegion> memoryRegion;
    size_t instanceSize;
    
    // Fluent interface optimization
    bool isInFluentChain = false;
    std::shared_ptr<ClassInstance> chainedInstance;
    
    // Garbage collection support
    void markReachable(std::set<Value*>& reachable) override;
    void cleanup() override;
};

// Class-aware memory manager
class ClassMemoryManager {
public:
    std::shared_ptr<ClassInstance> allocateInstance(std::shared_ptr<ClassType> type);
    void deallocateInstance(std::shared_ptr<ClassInstance> instance);
    
    // Inheritance-aware allocation
    std::shared_ptr<ClassInstance> allocateWithInheritance(
        std::shared_ptr<ClassType> type, 
        std::shared_ptr<ClassInstance> superInstance);
    
    // Default value initialization
    void initializeWithDefaults(std::shared_ptr<ClassInstance> instance,
                               const std::map<std::string, std::shared_ptr<Expression>>& defaults);
    
private:
    std::shared_ptr<MemoryRegion> classRegion;
    std::unordered_map<ClassType*, size_t> typeSizes;
};
```

## VM Integration

### New Opcodes for Class Integration
```cpp
enum class Opcode {
    // ... existing opcodes ...
    
    // Enhanced class operations
    CREATE_CLASS_INSTANCE,     // Create instance with error handling
    CREATE_CLASS_WITH_DEFAULTS, // Create instance with default field values
    CREATE_CLASS_WITH_OVERRIDES, // Create instance with field overrides
    CALL_CLASS_METHOD_SAFE,    // Thread-safe method call
    GET_CLASS_FIELD_SAFE,      // Thread-safe field access
    SET_CLASS_FIELD_SAFE,      // Thread-safe field assignment
    
    // Fluent interface operations
    CALL_FLUENT_SETTER,        // Call fluent setter method
    CHAIN_FLUENT_METHODS,      // Chain multiple fluent method calls
    OPTIMIZE_FLUENT_CHAIN,     // Optimize fluent method chain
    CALL_INIT_METHOD,          // Call optional init() method
    
    // Inheritance operations
    CALL_VIRTUAL_METHOD,       // Virtual method dispatch
    CALL_SUPER_METHOD,         // Call parent class method
    CHECK_INSTANCEOF,          // Check if instance is of specific type
    CAST_TO_SUBTYPE,          // Cast to subtype with Self return
    
    // Pattern matching integration
    MATCH_CLASS_TYPE,          // Match on class type
    MATCH_CLASS_FIELDS,        // Match and extract class fields
    MATCH_INHERITANCE,         // Match inheritance hierarchy
    
    // Error handling integration
    CHECK_CLASS_ERROR,         // Check if class operation failed
    PROPAGATE_CLASS_ERROR,     // Propagate class-based error
    HANDLE_CLASS_EXCEPTION,    // Handle class-based exception
    
    // Concurrency integration
    LOCK_CLASS_INSTANCE,       // Lock class instance for thread safety
    UNLOCK_CLASS_INSTANCE,     // Unlock class instance
    SEND_CLASS_TO_CHANNEL,     // Send class instance through channel
    RECEIVE_CLASS_FROM_CHANNEL, // Receive class instance from channel
};
```

### Enhanced VM Methods
```cpp
class VM {
public:
    // Class integration methods
    void handleCreateClassInstance(const Instruction& instruction);
    void handleCreateClassWithDefaults(const Instruction& instruction);
    void handleCreateClassWithOverrides(const Instruction& instruction);
    void handleClassMethodCall(const Instruction& instruction);
    void handleClassFieldAccess(const Instruction& instruction);
    
    // Fluent interface methods
    void handleFluentSetter(const Instruction& instruction);
    void handleFluentMethodChain(const Instruction& instruction);
    void handleOptimizeFluentChain(const Instruction& instruction);
    void handleCallInitMethod(const Instruction& instruction);
    
    // Inheritance methods
    void handleVirtualMethodCall(const Instruction& instruction);
    void handleSuperMethodCall(const Instruction& instruction);
    void handleInstanceOfCheck(const Instruction& instruction);
    void handleSubtypeCast(const Instruction& instruction);
    
    // Pattern matching integration
    void handleClassPatternMatch(const Instruction& instruction);
    void handleInheritanceMatch(const Instruction& instruction);
    
    // Error handling integration
    void handleClassErrorPropagation(const Instruction& instruction);
    void handleClassExceptionHandling(const Instruction& instruction);
    
    // Concurrency integration
    void handleConcurrentClassOperation(const Instruction& instruction);
    void handleClassChannelOperation(const Instruction& instruction);
    
private:
    std::shared_ptr<ClassMemoryManager> classMemoryManager;
    std::shared_ptr<ClassPatternMatcher> patternMatcher;
    std::shared_ptr<ModuleClassRegistry> classRegistry;
    std::shared_ptr<FluentInterfaceManager> fluentManager;
    std::shared_ptr<MethodDispatcher> methodDispatcher;
};
```

## Implementation Strategy

### Phase 1: Core Integration Foundation
1. Enhance `ClassType` in type system with integration support
2. Update AST nodes for class integration features
3. Implement class instantiation with default values and field overrides
4. Add fluent interface support with method chaining
5. Implement basic class-error integration
6. Add class pattern matching support

### Phase 2: Inheritance and Advanced Features
1. Implement class inheritance with Self types
2. Add virtual method dispatch and abstract class support
3. Implement interface contracts and implementation checking
4. Add class concurrency support
5. Enhance class module system integration
6. Implement class-based synchronization primitives

### Phase 3: Optimization and Performance
1. Optimize class method dispatch with virtual method tables
2. Implement fluent interface optimizations and inlining
3. Add class introspection and debugging support
4. Implement class-aware JIT optimizations
5. Optimize memory layout for inheritance hierarchies
6. Add comprehensive error reporting for class operations

### Phase 4: Testing and Documentation
1. Create comprehensive test suite for all integrations
2. Add performance benchmarks for method dispatch and fluent interfaces
3. Test inheritance hierarchies and Self type resolution
4. Update language documentation with class integration examples
5. Create migration guide for existing code
6. Add best practices guide for class design patterns

## Testing Strategy

### Integration Test Categories
1. **Class-Error Integration**: Test error classes, method error handling, constructor failures
2. **Class-Pattern Integration**: Test class patterns, inheritance patterns, destructuring
3. **Class-Type Integration**: Test class union types, Option types, type aliases
4. **Class-Concurrency Integration**: Test thread-safe operations, concurrent methods, channels
5. **Class-Module Integration**: Test class import/export, visibility, cross-module inheritance

### Performance Testing
1. **Method Dispatch Performance**: Benchmark virtual method calls vs direct calls
2. **Memory Usage**: Test class instance memory overhead and garbage collection
3. **Concurrency Performance**: Test thread-safe class operations under load
4. **Pattern Matching Performance**: Benchmark class pattern matching vs other patterns

This design ensures that classes become fully integrated first-class citizens in the Limit language, working seamlessly with all existing and future language features while maintaining performance and safety guarantees.
# Design Document

## Overview

This design implements comprehensive visibility enforcement in the type checker during semantic analysis. The system leverages AST visibility information to enforce access control rules for class members and module members, treating each file as a separate module. All visibility checks occur before bytecode generation, ensuring compile-time safety.

## Architecture

### Core Components

1. **Visibility Information Extraction**: Extract and store visibility metadata from AST nodes during the first pass of type checking
2. **Access Control Validator**: Validate member access expressions against stored visibility rules
3. **Module Context Manager**: Track current module context and manage cross-module access rules
4. **Inheritance Resolver**: Handle protected member access through inheritance relationships
5. **Error Reporter**: Generate detailed visibility violation error messages

### Data Flow

```
AST Parsing → Visibility Extraction → Type Checking → Access Validation → Error Reporting
```

## Components and Interfaces

### 1. Visibility Information Storage

```cpp
// Enhanced visibility tracking structures
struct MemberVisibilityInfo {
    std::string memberName;
    AST::VisibilityLevel visibility;
    std::string declaringModule;
    std::string declaringClass;  // Empty for module-level members
    int declarationLine;
};

struct ClassVisibilityInfo {
    std::string className;
    std::string declaringModule;
    std::string superClassName;  // For inheritance checking
    std::unordered_map<std::string, MemberVisibilityInfo> fields;
    std::unordered_map<std::string, MemberVisibilityInfo> methods;
};

struct ModuleVisibilityInfo {
    std::string modulePath;
    std::unordered_map<std::string, MemberVisibilityInfo> functions;
    std::unordered_map<std::string, MemberVisibilityInfo> variables;
    std::unordered_map<std::string, ClassVisibilityInfo> classes;
};
```

### 2. Enhanced TypeChecker Class

```cpp
class TypeChecker {
private:
    // Visibility tracking
    std::unordered_map<std::string, ModuleVisibilityInfo> moduleRegistry;
    std::unordered_map<std::string, ClassVisibilityInfo> classRegistry;
    std::unordered_map<std::string, std::string> classToModuleMap;
    
    // Current context
    std::string currentModulePath;
    std::string currentClassName;
    
    // Visibility extraction methods
    void extractModuleVisibility(const std::shared_ptr<AST::Program>& program);
    void extractClassVisibility(const std::shared_ptr<AST::ClassDeclaration>& classDecl);
    void extractFunctionVisibility(const std::shared_ptr<AST::FunctionDeclaration>& funcDecl);
    void extractVariableVisibility(const std::shared_ptr<AST::VarDeclaration>& varDecl);
    
    // Access validation methods (with clear separation)
    bool validateClassMemberAccess(const std::shared_ptr<AST::MemberExpr>& expr);
    bool validateModuleMemberAccess(const std::shared_ptr<AST::VariableExpr>& expr);
    bool validateModuleFunctionCall(const std::shared_ptr<AST::CallExpr>& expr);
    
    // Class-based visibility checking logic
    bool canAccessClassMember(const std::string& memberName, 
                             const std::string& declaringClass,
                             AST::VisibilityLevel memberVisibility,
                             const std::string& accessingClass);
    bool canAccessThroughInheritance(const std::string& memberName,
                                   const std::string& declaringClass,
                                   const std::string& accessingClass);
    
    // Module-based access checking logic
    bool canAccessModuleMember(AST::VisibilityLevel visibility, 
                              const std::string& declaringModule,
                              const std::string& accessingModule);
    
    // Context determination methods
    bool isClassMemberAccess(const std::shared_ptr<AST::MemberExpr>& expr);
    bool isModuleMemberAccess(const std::shared_ptr<AST::VariableExpr>& expr);
    
    // Inheritance utilities
    bool isSubclassOf(const std::string& subclass, const std::string& superclass);
    std::vector<std::string> getInheritanceChain(const std::string& className);
    
    // Error reporting
    void reportVisibilityViolation(const std::string& memberName,
                                 AST::VisibilityLevel visibility,
                                 const std::string& context,
                                 int line);
};
```

### 3. Access Validation Logic

#### Module-Level Access Rules (Independent System)
- **Private**: Accessible only within the same module (file)
- **Protected**: Accessible within the same module and related modules (import context)
- **Public**: Accessible from any module

#### Class Member Access Rules (Independent System)
- **Private**: Accessible only within the same class (regardless of module)
- **Protected**: Accessible within the same class and subclasses (even across modules)
- **Public**: Accessible from anywhere

#### Logical Separation Principles
1. **Class members use class-based visibility**: Class member access is determined solely by class hierarchy and member visibility
2. **Module members use module-based visibility**: Module member access is determined solely by module boundaries and member visibility
3. **No cross-contamination**: Class visibility rules do not affect module member access and vice versa
4. **Independent contexts**: A class defined in a module has its own visibility context separate from the module's visibility context
5. **Classes have no visibility modifiers**: Class declarations themselves do not have visibility modifiers (no `pub class`, `prot class`, etc.)
6. **Only members have visibility**: Only class members (fields and methods) have visibility modifiers (`pub`, `prot`, or private by default)

### 4. Inheritance-Based Access Control

```cpp
bool TypeChecker::canAccessThroughInheritance(const std::string& memberName,
                                             const std::string& declaringClass,
                                             const std::string& accessingClass) {
    // Check if accessing class is a subclass of declaring class
    if (isSubclassOf(accessingClass, declaringClass)) {
        return true;
    }
    
    // Check if both classes are in the same inheritance hierarchy
    auto declaringChain = getInheritanceChain(declaringClass);
    auto accessingChain = getInheritanceChain(accessingClass);
    
    // Find common ancestor for protected access
    for (const auto& declaringAncestor : declaringChain) {
        for (const auto& accessingAncestor : accessingChain) {
            if (declaringAncestor == accessingAncestor) {
                return true;
            }
        }
    }
    
    return false;
}
```

## Data Models

### Visibility Information Model

```cpp
enum class AccessContext {
    SameClass,           // Accessing from within the same class
    Subclass,           // Accessing from a subclass
    SameModule,         // Accessing from the same module
    DifferentModule,    // Accessing from a different module
    Global              // Global access context
};

struct AccessValidationRequest {
    std::string memberName;
    std::string declaringClass;
    std::string declaringModule;
    AST::VisibilityLevel memberVisibility;
    
    std::string accessingClass;
    std::string accessingModule;
    AccessContext context;
    
    int accessLine;
    int accessColumn;
};

struct AccessValidationResult {
    bool isAllowed;
    std::string errorMessage;
    std::string suggestion;
};
```

### Module Registry Model

```cpp
class ModuleRegistry {
private:
    std::unordered_map<std::string, ModuleVisibilityInfo> modules;
    
public:
    void registerModule(const std::string& modulePath, 
                       const std::shared_ptr<AST::Program>& program);
    
    MemberVisibilityInfo* findFunction(const std::string& functionName, 
                                      const std::string& modulePath);
    
    MemberVisibilityInfo* findVariable(const std::string& variableName, 
                                      const std::string& modulePath);
    
    ClassVisibilityInfo* findClass(const std::string& className, 
                                  const std::string& modulePath);
    
    bool isModuleAccessible(const std::string& targetModule, 
                           const std::string& currentModule);
};
```

## Error Handling

### Visibility Violation Error Types

1. **Private Member Access**: Attempting to access private members from outside the defining scope
2. **Protected Member Access**: Attempting to access protected members without proper inheritance
3. **Cross-Module Access**: Attempting to access non-public members across module boundaries
4. **Invalid Inheritance Access**: Attempting to access protected members from non-subclasses

### Error Message Templates

```cpp
class VisibilityErrorReporter {
public:
    std::string formatPrivateMemberError(const std::string& memberName,
                                       const std::string& declaringClass,
                                       const std::string& accessingContext);
    
    std::string formatProtectedMemberError(const std::string& memberName,
                                         const std::string& declaringClass,
                                         const std::string& accessingClass);
    
    std::string formatCrossModuleError(const std::string& memberName,
                                     const std::string& targetModule,
                                     const std::string& currentModule);
    
    std::string formatInheritanceError(const std::string& memberName,
                                     const std::string& requiredSuperclass,
                                     const std::string& actualClass);
};
```

## Testing Strategy

### Unit Tests
- Test visibility extraction from AST nodes
- Test access validation logic for each visibility level
- Test inheritance-based access control
- Test cross-module access rules

### Integration Tests
- Test complete visibility enforcement workflow
- Test error reporting accuracy
- Test performance with large codebases

### Test Cases
1. **Same Module Access**: All visibility levels should be accessible within the same module
2. **Cross-Module Private Access**: Should fail with appropriate error
3. **Cross-Module Protected Access**: Should fail unless inheritance allows it
4. **Cross-Module Public Access**: Should always succeed
5. **Inheritance Protected Access**: Should succeed for subclasses across modules
6. **Multiple Inheritance Scenarios**: Test complex inheritance hierarchies

### Test Data Structure

```cpp
struct VisibilityTestCase {
    std::string testName;
    std::string sourceModule;
    std::string targetModule;
    std::string memberName;
    AST::VisibilityLevel memberVisibility;
    std::string accessingClass;
    std::string declaringClass;
    bool expectedResult;
    std::string expectedErrorPattern;
};
```

## Implementation Phases

### Phase 1: Visibility Information Extraction
- Implement AST traversal for visibility extraction
- Build module and class registries
- Store visibility metadata with module context

### Phase 2: Access Validation Core
- Implement basic access validation logic
- Add module-level access checking
- Implement class member access checking

### Phase 3: Inheritance Support
- Add inheritance relationship tracking
- Implement protected member access through inheritance
- Handle complex inheritance scenarios

### Phase 4: Error Reporting Enhancement
- Implement detailed error messages
- Add suggestions for fixing visibility violations
- Integrate with existing error reporting system

### Phase 5: Testing and Optimization
- Comprehensive test suite implementation
- Performance optimization for large codebases
- Integration with existing type checker workflow
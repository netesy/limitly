# Structural Types Implementation Plan

## 📋 **Current Status: Parsing Complete, Type System Missing**

### ✅ **What's Already Working**

#### 1. Parser Support (100% Complete)
```limit
// ✅ All of this syntax is correctly parsed:
type Person = { name: str, age: int };
type Address = { street: str, city: str, zipCode: int };
type Employee = { 
    id: int, 
    name: str, 
    email: str, 
    active: bool,
    salary: float
};
```

**Implementation Details:**
- **File**: `src/frontend/parser.cpp`
- **Methods**: `parseBraceType()`, `parseStructuralType()`
- **AST Support**: `StructuralTypeField`, `TypeAnnotation::isStructural`
- **Field Storage**: `TypeAnnotation::structuralFields` vector

#### 2. AST Integration (100% Complete)
```cpp
struct StructuralTypeField {
    std::string name;
    std::shared_ptr<TypeAnnotation> type;
};

struct TypeAnnotation {
    bool isStructural = false;
    std::vector<StructuralTypeField> structuralFields;
    // ... other fields
};
```

#### 3. Type Checker Recognition (100% Complete)
- **File**: `src/frontend/type_checker.cpp`
- **Detection**: `resolve_type_annotation()` correctly identifies structural types
- **Validation**: Field types are validated recursively
- **Error Reporting**: Clear error messages when structural types are used

### 🔄 **What's Partially Working**

#### 1. Type Checker Integration (50% Complete)
```cpp
// ✅ This works (detection):
if (annotation->isStructural && !annotation->structuralFields.empty()) {
    // Structural type detected correctly
}

// ❌ This is missing (creation):
return type_system.createStructuralType(field_types); // Method doesn't exist
```

### ❌ **What's Missing**

#### 1. Type System Backend (0% Complete)
**Missing Methods in `TypeSystem` class:**
```cpp
// Need to implement:
TypePtr createStructuralType(const std::vector<std::pair<std::string, TypePtr>>& fields);
bool isStructuralType(TypePtr type);
std::vector<std::pair<std::string, TypePtr>> getStructuralFields(TypePtr type);
bool isStructurallyCompatible(TypePtr from, TypePtr to);
```

#### 2. Structural Literals (0% Complete)
**Missing Syntax Support:**
```limit
// ❌ This syntax is not supported yet:
var person: Person = { name: "Alice", age: 30 };

// Current parser treats this as a dictionary literal
// Need to distinguish between:
// - Dictionary: { "key": value }  (string keys)
// - Structural: { field: value }  (identifier keys)
```

#### 3. Field Access (0% Complete)
**Missing Operations:**
```limit
// ❌ These operations are not supported:
var name = person.name;        // Field access
person.age = 31;              // Field assignment
var hasName = "name" in person; // Field existence check
```

#### 4. Type Compatibility (0% Complete)
**Missing Checks:**
```limit
// ❌ These compatibility checks are missing:
type PersonLike = { name: str };
type FullPerson = { name: str, age: int };

var person: FullPerson = { name: "Alice", age: 30 };
var personLike: PersonLike = person; // Structural subtyping
```

## 🛠️ **Implementation Roadmap**

### Phase 1: Type System Backend (High Priority)
**Estimated Effort**: 2-3 days

1. **Add Structural Type Support to TypeSystem**
   ```cpp
   // In src/backend/types.hh:
   struct StructuralType {
       std::vector<std::pair<std::string, TypePtr>> fields;
   };
   
   // Add to Type::extra variant:
   std::variant<..., StructuralType> extra;
   ```

2. **Implement Creation Methods**
   ```cpp
   TypePtr createStructuralType(const std::vector<std::pair<std::string, TypePtr>>& fields);
   ```

3. **Add Type Compatibility**
   ```cpp
   bool isStructurallyCompatible(TypePtr from, TypePtr to);
   ```

4. **Update Type Checker**
   ```cpp
   // In resolve_type_annotation():
   return type_system.createStructuralType(field_types);
   ```

### Phase 2: Structural Literals (Medium Priority)
**Estimated Effort**: 3-4 days

1. **Distinguish Dictionary vs Structural Literals**
   ```cpp
   // Update parser to detect:
   { "key": value }    // Dictionary (string keys)
   { field: value }    // Structural (identifier keys)
   ```

2. **Add StructuralLiteralExpr AST Node**
   ```cpp
   struct StructuralLiteralExpr : public Expression {
       std::string typeName; // Optional type hint
       std::unordered_map<std::string, std::shared_ptr<Expression>> fields;
   };
   ```

3. **Type Checking for Literals**
   ```cpp
   TypePtr check_structural_literal_expr(std::shared_ptr<AST::StructuralLiteralExpr> expr);
   ```

### Phase 3: Field Access (Medium Priority)
**Estimated Effort**: 2-3 days

1. **Enhance Member Expression**
   ```cpp
   // Update check_member_expr() to handle structural types
   TypePtr check_member_expr(std::shared_ptr<AST::MemberExpr> expr);
   ```

2. **Add Field Validation**
   ```cpp
   bool hasField(TypePtr structType, const std::string& fieldName);
   TypePtr getFieldType(TypePtr structType, const std::string& fieldName);
   ```

3. **LIR Generation for Field Access**
   ```cpp
   // Add field access instructions to LIR
   LIR_Op::GetField, LIR_Op::SetField
   ```

### Phase 4: Advanced Features (Low Priority)
**Estimated Effort**: 4-5 days

1. **Structural Subtyping**
   - Duck typing compatibility
   - Subset field matching

2. **Nested Structural Types**
   - Structural types containing other structural types
   - Deep field access (`person.address.street`)

3. **Optional Fields**
   - Fields with default values
   - Partial structural types

## 🧪 **Testing Strategy**

### Phase 1 Tests (Type System)
```limit
// Basic structural type declarations
type Person = { name: str, age: int };
var person: Person; // Should not error

// Nested structural types
type Contact = { person: Person, phone: str };

// Type compatibility
type PersonLike = { name: str };
// Should be compatible with Person (structural subtyping)
```

### Phase 2 Tests (Literals)
```limit
// Structural literal creation
var person: Person = { name: "Alice", age: 30 };

// Type inference
var inferredPerson = { name: "Bob", age: 25 }; // Should infer structural type
```

### Phase 3 Tests (Field Access)
```limit
// Field access
var name = person.name;
var age = person.age;

// Field assignment
person.name = "Charlie";
person.age = 35;
```

## 📊 **Success Metrics**

### Phase 1 Success Criteria
- [ ] Structural type declarations compile without errors
- [ ] Type aliases with structural types work
- [ ] Nested structural type references work
- [ ] Clear error messages for invalid structural types

### Phase 2 Success Criteria
- [ ] Structural literals can be created
- [ ] Type checking validates literal fields against type
- [ ] Type inference works for structural literals
- [ ] Clear errors for missing or extra fields

### Phase 3 Success Criteria
- [ ] Field access works (`obj.field`)
- [ ] Field assignment works (`obj.field = value`)
- [ ] Type checking validates field operations
- [ ] LIR generation supports field operations

## 🔗 **Dependencies**

### Required Before Starting
- ✅ Union types (completed)
- ✅ Type aliases (completed)
- ✅ Basic type system (completed)

### Blocks Other Features
- **Pattern Matching**: Needs structural type destructuring
- **Classes**: May share implementation with structural types
- **Generics**: Generic structural types (`type Point<T> = { x: T, y: T }`)

## 💡 **Implementation Notes**

### Key Design Decisions
1. **Structural vs Nominal**: Use structural typing (duck typing) for compatibility
2. **Memory Layout**: Struct-like memory layout for performance
3. **Type Erasure**: Compile-time type checking, runtime efficiency
4. **Field Order**: Preserve declaration order for consistency

### Potential Challenges
1. **Parser Ambiguity**: Distinguishing dictionaries from structural literals
2. **Type Inference**: Complex inference for nested structural types
3. **Performance**: Efficient field access and type checking
4. **Error Messages**: Clear errors for structural type mismatches

### Integration Points
- **Type System**: Core structural type representation
- **Parser**: Literal syntax and type declarations
- **Type Checker**: Compatibility and validation
- **LIR Generator**: Field access instructions
- **VM**: Runtime field operations
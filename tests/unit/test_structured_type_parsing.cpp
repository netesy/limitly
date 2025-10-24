#include "../../src/frontend/parser.hh"
#include "../../src/frontend/scanner.hh"
#include "../../src/frontend/ast.hh"
#include <cassert>
#include <iostream>
#include <memory>

// Helper function to parse code and return AST
std::shared_ptr<AST::Program> parseCode(const std::string& code) {
    Scanner scanner(code);
    scanner.scanTokens();
    Parser parser(scanner, false); // Use AST mode for testing
    return parser.parse();
}

// Helper function to get the first type declaration from parsed code
std::shared_ptr<AST::TypeDeclaration> getFirstTypeDeclaration(const std::string& code) {
    auto program = parseCode(code);
    assert(!program->statements.empty());
    
    auto typeDecl = std::dynamic_pointer_cast<AST::TypeDeclaration>(program->statements[0]);
    assert(typeDecl != nullptr);
    return typeDecl;
}

// Test basic structured type parsing
void testBasicStructuredType() {
    std::cout << "Testing basic structured type parsing..." << std::endl;
    
    std::string code = R"(
        type Person = { name: str, age: int, active: bool };
    )";
    
    auto typeDecl = getFirstTypeDeclaration(code);
    assert(typeDecl->name == "Person");
    assert(typeDecl->type != nullptr);
    assert(typeDecl->type->isStructural == true);
    assert(typeDecl->type->typeName == "struct");
    
    // Check structural fields
    assert(typeDecl->type->structuralFields.size() == 3);
    
    // Check first field: name: str
    const auto& nameField = typeDecl->type->structuralFields[0];
    assert(nameField.name == "name");
    assert(nameField.type != nullptr);
    assert(nameField.type->typeName == "str");
    assert(nameField.type->isPrimitive == true);
    
    // Check second field: age: int
    const auto& ageField = typeDecl->type->structuralFields[1];
    assert(ageField.name == "age");
    assert(ageField.type != nullptr);
    assert(ageField.type->typeName == "int");
    assert(ageField.type->isPrimitive == true);
    
    // Check third field: active: bool
    const auto& activeField = typeDecl->type->structuralFields[2];
    assert(activeField.name == "active");
    assert(activeField.type != nullptr);
    assert(activeField.type->typeName == "bool");
    assert(activeField.type->isPrimitive == true);
    
    std::cout << "✓ Basic structured type parsing passed" << std::endl;
}

// Test structured type with literal string types
void testStructuredTypeWithLiterals() {
    std::cout << "Testing structured type with literal string types..." << std::endl;
    
    std::string code = R"(
        type Some = { kind: "Some", value: any };
    )";
    
    auto typeDecl = getFirstTypeDeclaration(code);
    assert(typeDecl->name == "Some");
    assert(typeDecl->type->isStructural == true);
    assert(typeDecl->type->structuralFields.size() == 2);
    
    // Check kind field with literal type
    const auto& kindField = typeDecl->type->structuralFields[0];
    assert(kindField.name == "kind");
    assert(kindField.type != nullptr);
    assert(kindField.type->typeName == "\"Some\""); // Literal type should keep quotes
    
    // Check value field
    const auto& valueField = typeDecl->type->structuralFields[1];
    assert(valueField.name == "value");
    assert(valueField.type != nullptr);
    assert(valueField.type->typeName == "any");
    
    std::cout << "✓ Structured type with literal strings passed" << std::endl;
}

// Test nested structured types
void testNestedStructuredTypes() {
    std::cout << "Testing nested structured types..." << std::endl;
    
    std::string code = R"(
        type Address = { street: str, city: str, zipCode: int };
        type Person = { name: str, address: Address, age: int };
    )";
    
    auto program = parseCode(code);
    assert(program->statements.size() >= 2);
    
    // Get the Person type declaration (second one)
    auto personDecl = std::dynamic_pointer_cast<AST::TypeDeclaration>(program->statements[1]);
    assert(personDecl != nullptr);
    assert(personDecl->name == "Person");
    assert(personDecl->type->isStructural == true);
    assert(personDecl->type->structuralFields.size() == 3);
    
    // Check address field with user-defined type
    const auto& addressField = personDecl->type->structuralFields[1];
    assert(addressField.name == "address");
    assert(addressField.type != nullptr);
    assert(addressField.type->typeName == "Address");
    assert(addressField.type->isUserDefined == true);
    
    std::cout << "✓ Nested structured types passed" << std::endl;
}

// Test structured type with quoted field names
void testStructuredTypeWithQuotedFields() {
    std::cout << "Testing structured type with quoted field names..." << std::endl;
    
    std::string code = R"(
        type QuotedFields = { "quoted-field": str, "another_field": int, normalField: bool };
    )";
    
    auto typeDecl = getFirstTypeDeclaration(code);
    assert(typeDecl->name == "QuotedFields");
    assert(typeDecl->type->isStructural == true);
    assert(typeDecl->type->structuralFields.size() == 3);
    
    // Check quoted field names
    const auto& quotedField1 = typeDecl->type->structuralFields[0];
    assert(quotedField1.name == "quoted-field"); // Should be unquoted in the field name
    
    const auto& quotedField2 = typeDecl->type->structuralFields[1];
    assert(quotedField2.name == "another_field");
    
    const auto& normalField = typeDecl->type->structuralFields[2];
    assert(normalField.name == "normalField");
    
    std::cout << "✓ Structured type with quoted field names passed" << std::endl;
}

// Test extensible records (rest parameters)
void testExtensibleRecords() {
    std::cout << "Testing extensible records..." << std::endl;
    
    std::string code = R"(
        type ExtendedRecord = { ...BaseRecord, name: str, active: bool };
    )";
    
    auto typeDecl = getFirstTypeDeclaration(code);
    assert(typeDecl->name == "ExtendedRecord");
    assert(typeDecl->type->isStructural == true);
    assert(typeDecl->type->hasRest == true);
    assert(typeDecl->type->baseRecord == "BaseRecord");
    assert(typeDecl->type->baseRecords.size() == 1);
    assert(typeDecl->type->baseRecords[0] == "BaseRecord");
    
    // Should still have the additional fields
    assert(typeDecl->type->structuralFields.size() == 2);
    assert(typeDecl->type->structuralFields[0].name == "name");
    assert(typeDecl->type->structuralFields[1].name == "active");
    
    std::cout << "✓ Extensible records passed" << std::endl;
}

// Test complex mixed field types
void testComplexMixedFieldTypes() {
    std::cout << "Testing complex mixed field types..." << std::endl;
    
    std::string code = R"(
        type MixedType = { 
            stringField: str, 
            intField: int, 
            boolField: bool, 
            floatField: float,
            literalField: "literal_value",
            userDefinedField: Person
        };
    )";
    
    auto typeDecl = getFirstTypeDeclaration(code);
    assert(typeDecl->name == "MixedType");
    assert(typeDecl->type->isStructural == true);
    assert(typeDecl->type->structuralFields.size() == 6);
    
    // Check each field type
    const auto& fields = typeDecl->type->structuralFields;
    
    assert(fields[0].name == "stringField" && fields[0].type->typeName == "str");
    assert(fields[1].name == "intField" && fields[1].type->typeName == "int");
    assert(fields[2].name == "boolField" && fields[2].type->typeName == "bool");
    assert(fields[3].name == "floatField" && fields[3].type->typeName == "float");
    assert(fields[4].name == "literalField" && fields[4].type->typeName == "\"literal_value\"");
    assert(fields[5].name == "userDefinedField" && fields[5].type->typeName == "Person");
    
    std::cout << "✓ Complex mixed field types passed" << std::endl;
}

// Test empty structured type
void testEmptyStructuredType() {
    std::cout << "Testing empty structured type..." << std::endl;
    
    std::string code = R"(
        type Empty = { };
    )";
    
    auto typeDecl = getFirstTypeDeclaration(code);
    assert(typeDecl->name == "Empty");
    assert(typeDecl->type->isStructural == true);
    assert(typeDecl->type->structuralFields.size() == 0);
    
    std::cout << "✓ Empty structured type passed" << std::endl;
}

// Test StructuralTypeField functionality
void testStructuralTypeFieldSupport() {
    std::cout << "Testing StructuralTypeField support in TypeAnnotation..." << std::endl;
    
    // Create a StructuralTypeField manually to test the structure
    AST::StructuralTypeField field;
    field.name = "testField";
    field.type = std::make_shared<AST::TypeAnnotation>();
    field.type->typeName = "str";
    field.type->isPrimitive = true;
    
    // Verify the field structure
    assert(field.name == "testField");
    assert(field.type != nullptr);
    assert(field.type->typeName == "str");
    assert(field.type->isPrimitive == true);
    
    // Test that TypeAnnotation can hold structural fields
    auto typeAnnotation = std::make_shared<AST::TypeAnnotation>();
    typeAnnotation->isStructural = true;
    typeAnnotation->structuralFields.push_back(field);
    
    assert(typeAnnotation->structuralFields.size() == 1);
    assert(typeAnnotation->structuralFields[0].name == "testField");
    
    std::cout << "✓ StructuralTypeField support passed" << std::endl;
}

// Test parseStructuralType method indirectly through type declarations
void testParseStructuralTypeMethod() {
    std::cout << "Testing parseStructuralType method functionality..." << std::endl;
    
    // Test various structural type patterns that would exercise parseStructuralType
    std::vector<std::string> testCases = {
        "type Simple = { field: str };",
        "type Multiple = { a: int, b: str, c: bool };",
        "type WithLiterals = { kind: \"value\", data: any };",
        "type WithQuotes = { \"field-name\": str, normal: int };",
        "type WithRest = { ...Base, extra: str };",
        "type Nested = { inner: { x: int, y: int }, outer: str };"
    };
    
    for (const auto& testCase : testCases) {
        auto program = parseCode(testCase);
        assert(!program->statements.empty());
        
        auto typeDecl = std::dynamic_pointer_cast<AST::TypeDeclaration>(program->statements[0]);
        assert(typeDecl != nullptr);
        assert(typeDecl->type != nullptr);
        assert(typeDecl->type->isStructural == true);
        
        // Each test case should have at least one field (except rest-only cases)
        if (testCase.find("...Base") == std::string::npos || testCase.find("extra") != std::string::npos) {
            assert(typeDecl->type->structuralFields.size() > 0);
        }
    }
    
    std::cout << "✓ parseStructuralType method functionality passed" << std::endl;
}

int main() {
    std::cout << "Running structured type parsing unit tests..." << std::endl;
    std::cout << "Testing Requirements: 5.1, 5.2, 5.3, 5.4" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    try {
        testBasicStructuredType();
        testStructuredTypeWithLiterals();
        testNestedStructuredTypes();
        testStructuredTypeWithQuotedFields();
        testExtensibleRecords();
        testComplexMixedFieldTypes();
        testEmptyStructuredType();
        testStructuralTypeFieldSupport();
        testParseStructuralTypeMethod();
        
        std::cout << "\n✅ All structured type parsing tests passed!" << std::endl;
        std::cout << "✅ parseStructuralType() method is working correctly" << std::endl;
        std::cout << "✅ StructuralTypeField support is implemented in TypeAnnotation" << std::endl;
        std::cout << "✅ All requirements (5.1, 5.2, 5.3, 5.4) are satisfied" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "\n❌ Test failed with unknown exception" << std::endl;
        return 1;
    }
}
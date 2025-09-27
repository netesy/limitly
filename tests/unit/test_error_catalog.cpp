#include "../../src/error_catalog.hh"
#include <cassert>
#include <iostream>
#include <vector>
#include <string>

using namespace ErrorHandling;

// Test helper function
void assert_true(bool condition, const std::string& message) {
    if (!condition) {
        std::cerr << "ASSERTION FAILED: " << message << std::endl;
        exit(1);
    }
}

void assert_false(bool condition, const std::string& message) {
    if (condition) {
        std::cerr << "ASSERTION FAILED: " << message << std::endl;
        exit(1);
    }
}

void assert_equals(const std::string& expected, const std::string& actual, const std::string& message) {
    if (expected != actual) {
        std::cerr << "ASSERTION FAILED: " << message << std::endl;
        std::cerr << "Expected: '" << expected << "'" << std::endl;
        std::cerr << "Actual: '" << actual << "'" << std::endl;
        exit(1);
    }
}

void assert_not_null(const void* ptr, const std::string& message) {
    if (ptr == nullptr) {
        std::cerr << "ASSERTION FAILED: " << message << std::endl;
        exit(1);
    }
}

void assert_null(const void* ptr, const std::string& message) {
    if (ptr != nullptr) {
        std::cerr << "ASSERTION FAILED: " << message << std::endl;
        exit(1);
    }
}

// Test singleton pattern
void test_singleton_pattern() {
    std::cout << "Testing singleton pattern..." << std::endl;
    
    ErrorCatalog& catalog1 = ErrorCatalog::getInstance();
    ErrorCatalog& catalog2 = ErrorCatalog::getInstance();
    
    assert_true(&catalog1 == &catalog2, "Singleton should return same instance");
    
    std::cout << "✓ Singleton pattern test passed" << std::endl;
}

// Test initialization
void test_initialization() {
    std::cout << "Testing initialization..." << std::endl;
    
    ErrorCatalog& catalog = ErrorCatalog::getInstance();
    catalog.clear(); // Start fresh
    
    assert_false(catalog.isInitialized(), "Catalog should not be initialized initially");
    assert_true(catalog.getDefinitionCount() == 0, "Should have no definitions initially");
    
    catalog.initialize();
    
    assert_true(catalog.isInitialized(), "Catalog should be initialized after initialize()");
    assert_true(catalog.getDefinitionCount() > 0, "Should have definitions after initialization");
    
    // Test that multiple initializations don't cause issues
    size_t count_after_first = catalog.getDefinitionCount();
    catalog.initialize();
    assert_true(catalog.getDefinitionCount() == count_after_first, "Multiple initializations should not duplicate definitions");
    
    std::cout << "✓ Initialization test passed" << std::endl;
}

// Test error definition lookup by code
void test_lookup_by_code() {
    std::cout << "Testing lookup by code..." << std::endl;
    
    ErrorCatalog& catalog = ErrorCatalog::getInstance();
    catalog.initialize();
    
    // Test existing error codes
    const ErrorDefinition* def = catalog.lookupByCode("E001");
    assert_not_null(def, "Should find E001 definition");
    assert_equals("E001", def->code, "Code should match");
    assert_equals("LexicalError", def->type, "Type should be LexicalError");
    
    def = catalog.lookupByCode("E102");
    assert_not_null(def, "Should find E102 definition");
    assert_equals("E102", def->code, "Code should match");
    assert_equals("SyntaxError", def->type, "Type should be SyntaxError");
    
    def = catalog.lookupByCode("E400");
    assert_not_null(def, "Should find E400 definition");
    assert_equals("E400", def->code, "Code should match");
    assert_equals("RuntimeError", def->type, "Type should be RuntimeError");
    
    // Test non-existent error code
    def = catalog.lookupByCode("E999");
    assert_null(def, "Should not find non-existent error code");
    
    std::cout << "✓ Lookup by code test passed" << std::endl;
}

// Test error definition lookup by message pattern
void test_lookup_by_message() {
    std::cout << "Testing lookup by message pattern..." << std::endl;
    
    ErrorCatalog& catalog = ErrorCatalog::getInstance();
    catalog.initialize();
    
    // Test lexical error pattern matching
    const ErrorDefinition* def = catalog.lookupByMessage("Invalid character '@' at position 5", InterpretationStage::SCANNING);
    assert_not_null(def, "Should find definition for invalid character message");
    assert_equals("E001", def->code, "Should match E001 for invalid character");
    
    // Test syntax error pattern matching
    def = catalog.lookupByMessage("Unexpected token '}' found", InterpretationStage::PARSING);
    assert_not_null(def, "Should find definition for unexpected token message");
    assert_true(def->code == "E100" || def->code == "E102", "Should match appropriate syntax error code");
    
    // Test runtime error pattern matching
    def = catalog.lookupByMessage("Division by zero in expression", InterpretationStage::INTERPRETING);
    assert_not_null(def, "Should find definition for division by zero message");
    assert_equals("E400", def->code, "Should match E400 for division by zero");
    
    // Test case-insensitive matching
    def = catalog.lookupByMessage("DIVISION BY ZERO", InterpretationStage::INTERPRETING);
    assert_not_null(def, "Should find definition with case-insensitive matching");
    assert_equals("E400", def->code, "Should match E400 for division by zero (case insensitive)");
    
    // Test no match
    def = catalog.lookupByMessage("This is a completely unknown error message", InterpretationStage::PARSING);
    assert_null(def, "Should not find definition for unknown message");
    
    std::cout << "✓ Lookup by message test passed" << std::endl;
}

// Test getting definitions for specific stages
void test_definitions_for_stage() {
    std::cout << "Testing definitions for stage..." << std::endl;
    
    ErrorCatalog& catalog = ErrorCatalog::getInstance();
    catalog.initialize();
    
    // Test lexical errors
    auto lexicalDefs = catalog.getDefinitionsForStage(InterpretationStage::SCANNING);
    assert_true(lexicalDefs.size() > 0, "Should have lexical error definitions");
    
    // Verify all returned definitions are lexical errors
    for (const auto* def : lexicalDefs) {
        assert_not_null(def, "Definition should not be null");
        assert_equals("LexicalError", def->type, "All definitions should be LexicalError type");
        
        // Check code range (E001-E099)
        if (def->code.length() >= 4 && def->code[0] == 'E') {
            int codeNum = std::stoi(def->code.substr(1));
            assert_true(codeNum >= 1 && codeNum <= 99, "Lexical error codes should be in range E001-E099");
        }
    }
    
    // Test syntax errors
    auto syntaxDefs = catalog.getDefinitionsForStage(InterpretationStage::PARSING);
    assert_true(syntaxDefs.size() > 0, "Should have syntax error definitions");
    
    // Verify all returned definitions are syntax errors
    for (const auto* def : syntaxDefs) {
        assert_not_null(def, "Definition should not be null");
        assert_equals("SyntaxError", def->type, "All definitions should be SyntaxError type");
        
        // Check code range (E100-E199)
        if (def->code.length() >= 4 && def->code[0] == 'E') {
            int codeNum = std::stoi(def->code.substr(1));
            assert_true(codeNum >= 100 && codeNum <= 199, "Syntax error codes should be in range E100-E199");
        }
    }
    
    // Test runtime errors
    auto runtimeDefs = catalog.getDefinitionsForStage(InterpretationStage::INTERPRETING);
    assert_true(runtimeDefs.size() > 0, "Should have runtime error definitions");
    
    // Verify all returned definitions are runtime errors
    for (const auto* def : runtimeDefs) {
        assert_not_null(def, "Definition should not be null");
        assert_equals("RuntimeError", def->type, "All definitions should be RuntimeError type");
        
        // Check code range (E400-E499)
        if (def->code.length() >= 4 && def->code[0] == 'E') {
            int codeNum = std::stoi(def->code.substr(1));
            assert_true(codeNum >= 400 && codeNum <= 499, "Runtime error codes should be in range E400-E499");
        }
    }
    
    std::cout << "✓ Definitions for stage test passed" << std::endl;
}

// Test adding and removing custom definitions
void test_add_remove_definitions() {
    std::cout << "Testing add/remove definitions..." << std::endl;
    
    ErrorCatalog& catalog = ErrorCatalog::getInstance();
    catalog.initialize();
    
    size_t initialCount = catalog.getDefinitionCount();
    
    // Test adding a custom definition
    ErrorDefinition customDef("E999", "CustomError", "Custom test error",
                             "This is a custom test error hint",
                             "This is a custom test error suggestion",
                             {"Custom cause 1", "Custom cause 2"});
    
    bool added = catalog.addDefinition(customDef);
    assert_true(added, "Should successfully add custom definition");
    assert_true(catalog.getDefinitionCount() == initialCount + 1, "Definition count should increase");
    
    // Test lookup of custom definition
    const ErrorDefinition* def = catalog.lookupByCode("E999");
    assert_not_null(def, "Should find custom definition");
    assert_equals("E999", def->code, "Code should match");
    assert_equals("CustomError", def->type, "Type should match");
    assert_equals("Custom test error", def->pattern, "Pattern should match");
    
    // Test adding duplicate definition (should fail)
    bool duplicateAdded = catalog.addDefinition(customDef);
    assert_false(duplicateAdded, "Should not add duplicate definition");
    assert_true(catalog.getDefinitionCount() == initialCount + 1, "Definition count should not change");
    
    // Test removing definition
    bool removed = catalog.removeDefinition("E999");
    assert_true(removed, "Should successfully remove definition");
    assert_true(catalog.getDefinitionCount() == initialCount, "Definition count should decrease");
    
    // Test lookup after removal
    def = catalog.lookupByCode("E999");
    assert_null(def, "Should not find removed definition");
    
    // Test removing non-existent definition
    bool nonExistentRemoved = catalog.removeDefinition("E888");
    assert_false(nonExistentRemoved, "Should not remove non-existent definition");
    
    std::cout << "✓ Add/remove definitions test passed" << std::endl;
}

// Test hint and suggestion generation
void test_hint_suggestion_generation() {
    std::cout << "Testing hint and suggestion generation..." << std::endl;
    
    ErrorCatalog& catalog = ErrorCatalog::getInstance();
    catalog.initialize();
    
    // Create test context
    ErrorContext context("test.lm", 10, 5, "let x = y + z;", "y", "variable", InterpretationStage::SEMANTIC);
    
    // Test with a definition that has templates
    const ErrorDefinition* def = catalog.lookupByCode("E201"); // Undefined variable
    assert_not_null(def, "Should find E201 definition");
    
    std::string hint = catalog.generateHint(*def, context);
    assert_true(!hint.empty(), "Should generate non-empty hint");
    
    std::string suggestion = catalog.generateSuggestion(*def, context);
    assert_true(!suggestion.empty(), "Should generate non-empty suggestion");
    
    // Test template substitution (if the template contains {lexeme})
    if (def->hintTemplate.find("{lexeme}") != std::string::npos) {
        assert_true(hint.find("y") != std::string::npos, "Hint should contain substituted lexeme");
    }
    
    if (def->suggestionTemplate.find("{lexeme}") != std::string::npos) {
        assert_true(suggestion.find("y") != std::string::npos, "Suggestion should contain substituted lexeme");
    }
    
    std::cout << "✓ Hint and suggestion generation test passed" << std::endl;
}

// Test common causes retrieval
void test_common_causes() {
    std::cout << "Testing common causes retrieval..." << std::endl;
    
    ErrorCatalog& catalog = ErrorCatalog::getInstance();
    catalog.initialize();
    
    // Test getting common causes for a known error
    auto causes = catalog.getCommonCauses("E400"); // Division by zero
    assert_true(causes.size() > 0, "Should have common causes for E400");
    
    // Test getting common causes for non-existent error
    auto noCauses = catalog.getCommonCauses("E999");
    assert_true(noCauses.size() == 0, "Should have no causes for non-existent error");
    
    std::cout << "✓ Common causes test passed" << std::endl;
}

// Test thread safety (basic test)
void test_thread_safety() {
    std::cout << "Testing basic thread safety..." << std::endl;
    
    ErrorCatalog& catalog = ErrorCatalog::getInstance();
    catalog.initialize();
    
    // This is a basic test - in a real scenario, we'd use multiple threads
    // For now, just verify that multiple operations don't crash
    
    const ErrorDefinition* def1 = catalog.lookupByCode("E001");
    const ErrorDefinition* def2 = catalog.lookupByMessage("Division by zero", InterpretationStage::INTERPRETING);
    auto defs = catalog.getDefinitionsForStage(InterpretationStage::PARSING);
    size_t count = catalog.getDefinitionCount();
    
    assert_not_null(def1, "Should find definition in thread safety test");
    assert_not_null(def2, "Should find definition by message in thread safety test");
    assert_true(defs.size() > 0, "Should get definitions for stage in thread safety test");
    assert_true(count > 0, "Should get definition count in thread safety test");
    
    std::cout << "✓ Basic thread safety test passed" << std::endl;
}

// Test clear functionality
void test_clear() {
    std::cout << "Testing clear functionality..." << std::endl;
    
    ErrorCatalog& catalog = ErrorCatalog::getInstance();
    catalog.initialize();
    
    assert_true(catalog.isInitialized(), "Should be initialized before clear");
    assert_true(catalog.getDefinitionCount() > 0, "Should have definitions before clear");
    
    catalog.clear();
    
    assert_false(catalog.isInitialized(), "Should not be initialized after clear");
    assert_true(catalog.getDefinitionCount() == 0, "Should have no definitions after clear");
    
    // Test that lookup returns null after clear
    const ErrorDefinition* def = catalog.lookupByCode("E001");
    assert_null(def, "Should not find definition after clear");
    
    // Re-initialize for other tests
    catalog.initialize();
    
    std::cout << "✓ Clear functionality test passed" << std::endl;
}

// Test comprehensive error coverage
void test_comprehensive_coverage() {
    std::cout << "Testing comprehensive error coverage..." << std::endl;
    
    ErrorCatalog& catalog = ErrorCatalog::getInstance();
    catalog.initialize();
    
    // Test that we have definitions for all major error categories
    
    // Lexical errors (E001-E099)
    auto lexicalDefs = catalog.getDefinitionsForStage(InterpretationStage::SCANNING);
    assert_true(lexicalDefs.size() >= 5, "Should have at least 5 lexical error definitions");
    
    // Syntax errors (E100-E199)
    auto syntaxDefs = catalog.getDefinitionsForStage(InterpretationStage::PARSING);
    assert_true(syntaxDefs.size() >= 10, "Should have at least 10 syntax error definitions");
    
    // Semantic errors (E200-E299)
    auto semanticDefs = catalog.getDefinitionsForStage(InterpretationStage::SEMANTIC);
    assert_true(semanticDefs.size() >= 8, "Should have at least 8 semantic error definitions");
    
    // Runtime errors (E400-E499)
    auto runtimeDefs = catalog.getDefinitionsForStage(InterpretationStage::INTERPRETING);
    assert_true(runtimeDefs.size() >= 15, "Should have at least 15 runtime error definitions");
    
    // Bytecode errors (E500-E599)
    auto bytecodeDefs = catalog.getDefinitionsForStage(InterpretationStage::BYTECODE);
    assert_true(bytecodeDefs.size() >= 3, "Should have at least 3 bytecode error definitions");
    
    // Compilation errors (E600-E699)
    auto compilationDefs = catalog.getDefinitionsForStage(InterpretationStage::COMPILING);
    assert_true(compilationDefs.size() >= 3, "Should have at least 3 compilation error definitions");
    
    // Test that all definitions have required fields
    size_t totalDefs = catalog.getDefinitionCount();
    assert_true(totalDefs >= 44, "Should have at least 44 total error definitions");
    
    std::cout << "✓ Comprehensive coverage test passed" << std::endl;
}

int main() {
    std::cout << "Running ErrorCatalog unit tests..." << std::endl;
    std::cout << "=================================" << std::endl;
    
    try {
        test_singleton_pattern();
        test_initialization();
        test_lookup_by_code();
        test_lookup_by_message();
        test_definitions_for_stage();
        test_add_remove_definitions();
        test_hint_suggestion_generation();
        test_common_causes();
        test_thread_safety();
        test_clear();
        test_comprehensive_coverage();
        
        std::cout << std::endl;
        std::cout << "=================================" << std::endl;
        std::cout << "✅ All ErrorCatalog tests passed!" << std::endl;
        
        // Print some statistics
        ErrorCatalog& catalog = ErrorCatalog::getInstance();
        catalog.initialize();
        std::cout << "Total error definitions: " << catalog.getDefinitionCount() << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
}
#include "error_catalog.hh"
#include "error_code_generator.hh"
#include <iostream>

using namespace ErrorHandling;

void demonstrateErrorCatalog() {
    std::cout << "ErrorCatalog Demonstration" << std::endl;
    std::cout << "=========================" << std::endl;
    
    // Initialize the catalog
    ErrorCatalog& catalog = ErrorCatalog::getInstance();
    catalog.initialize();
    
    std::cout << "Initialized catalog with " << catalog.getDefinitionCount() << " error definitions" << std::endl;
    std::cout << std::endl;
    
    // Demonstrate lookup by error code
    std::cout << "1. Lookup by Error Code:" << std::endl;
    std::cout << "------------------------" << std::endl;
    
    const ErrorDefinition* def = catalog.lookupByCode("E102");
    if (def) {
        std::cout << "Code: " << def->code << std::endl;
        std::cout << "Type: " << def->type << std::endl;
        std::cout << "Pattern: " << def->pattern << std::endl;
        std::cout << "Hint: " << def->hintTemplate << std::endl;
        std::cout << "Suggestion: " << def->suggestionTemplate << std::endl;
        std::cout << "Common Causes: ";
        for (size_t i = 0; i < def->commonCauses.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << def->commonCauses[i];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    // Demonstrate lookup by message pattern
    std::cout << "2. Lookup by Message Pattern:" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    
    std::vector<std::pair<std::string, InterpretationStage>> testMessages = {
        {"Invalid character '@' found", InterpretationStage::SCANNING},
        {"Unexpected closing brace '}' at line 15", InterpretationStage::PARSING},
        {"Variable 'x' not found in current scope", InterpretationStage::SEMANTIC},
        {"Division by zero in arithmetic expression", InterpretationStage::INTERPRETING}
    };
    
    for (const auto& testCase : testMessages) {
        const std::string& message = testCase.first;
        InterpretationStage stage = testCase.second;
        
        const ErrorDefinition* matchedDef = catalog.lookupByMessage(message, stage);
        if (matchedDef) {
            std::cout << "Message: \"" << message << "\"" << std::endl;
            std::cout << "  -> Matched: " << matchedDef->code << " (" << matchedDef->type << ")" << std::endl;
        } else {
            std::cout << "Message: \"" << message << "\"" << std::endl;
            std::cout << "  -> No match found" << std::endl;
        }
    }
    std::cout << std::endl;
    
    // Demonstrate hint and suggestion generation
    std::cout << "3. Hint and Suggestion Generation:" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    
    ErrorContext context("example.lm", 15, 8, "let result = x / 0;", "0", "non-zero value", InterpretationStage::INTERPRETING);
    
    const ErrorDefinition* divByZeroDef = catalog.lookupByCode("E400");
    if (divByZeroDef) {
        std::string hint = catalog.generateHint(*divByZeroDef, context);
        std::string suggestion = catalog.generateSuggestion(*divByZeroDef, context);
        
        std::cout << "Error Context:" << std::endl;
        std::cout << "  File: " << context.filePath << std::endl;
        std::cout << "  Line: " << context.line << ", Column: " << context.column << std::endl;
        std::cout << "  Code: " << context.sourceCode << std::endl;
        std::cout << "  Lexeme: " << context.lexeme << std::endl;
        std::cout << std::endl;
        std::cout << "Generated Messages:" << std::endl;
        std::cout << "  Hint: " << hint << std::endl;
        std::cout << "  Suggestion: " << suggestion << std::endl;
    }
    std::cout << std::endl;
    
    // Demonstrate stage-based filtering
    std::cout << "4. Stage-based Error Definitions:" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    
    struct StageInfo {
        InterpretationStage stage;
        std::string name;
    };
    
    std::vector<StageInfo> stages = {
        {InterpretationStage::SCANNING, "Lexical"},
        {InterpretationStage::PARSING, "Syntax"},
        {InterpretationStage::SEMANTIC, "Semantic"},
        {InterpretationStage::INTERPRETING, "Runtime"},
        {InterpretationStage::BYTECODE, "Bytecode"},
        {InterpretationStage::COMPILING, "Compilation"}
    };
    
    for (const auto& stageInfo : stages) {
        auto defs = catalog.getDefinitionsForStage(stageInfo.stage);
        std::cout << stageInfo.name << " errors: " << defs.size() << " definitions" << std::endl;
        
        // Show first few error codes for each stage
        std::cout << "  Codes: ";
        for (size_t i = 0; i < std::min(size_t(5), defs.size()); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << defs[i]->code;
        }
        if (defs.size() > 5) {
            std::cout << ", ... (+" << (defs.size() - 5) << " more)";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    // Demonstrate integration with ErrorCodeGenerator
    std::cout << "5. Integration with ErrorCodeGenerator:" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    
    std::vector<std::pair<std::string, InterpretationStage>> errorScenarios = {
        {"Unexpected token ';'", InterpretationStage::PARSING},
        {"Division by zero", InterpretationStage::INTERPRETING},
        {"Invalid character '#'", InterpretationStage::SCANNING}
    };
    
    for (const auto& scenario : errorScenarios) {
        const std::string& errorMsg = scenario.first;
        InterpretationStage stage = scenario.second;
        
        // Generate error code
        std::string errorCode = ErrorCodeGenerator::generateErrorCode(stage, errorMsg);
        
        // Look up definition in catalog
        const ErrorDefinition* catalogDef = catalog.lookupByMessage(errorMsg, stage);
        
        std::cout << "Error: \"" << errorMsg << "\"" << std::endl;
        std::cout << "  Generated Code: " << errorCode << std::endl;
        std::cout << "  Catalog Match: " << (catalogDef ? catalogDef->code : "None") << std::endl;
        std::cout << "  Error Type: " << ErrorCodeGenerator::getErrorType(stage) << std::endl;
        std::cout << std::endl;
    }
    
    std::cout << "Demonstration completed!" << std::endl;
}

int main() {
    try {
        demonstrateErrorCatalog();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error during demonstration: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error during demonstration" << std::endl;
        return 1;
    }
}
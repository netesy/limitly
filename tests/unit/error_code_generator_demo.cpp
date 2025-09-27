#include "../../src/error_code_generator.hh"
#include <iostream>

using namespace ErrorHandling;

void demonstrateErrorCodeGeneration() {
    std::cout << "ErrorCodeGenerator Demonstration" << std::endl;
    std::cout << "=================================" << std::endl;
    
    // Clear registry for clean demo
    ErrorCodeGenerator::clearRegistry();
    
    std::cout << "\n1. Basic Error Code Generation by Stage:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    // Generate codes for different stages
    std::cout << "SCANNING stage: " 
              << ErrorCodeGenerator::generateErrorCode(InterpretationStage::SCANNING)
              << " (" << ErrorCodeGenerator::getErrorType(InterpretationStage::SCANNING) << ")" << std::endl;
              
    std::cout << "PARSING stage: " 
              << ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING)
              << " (" << ErrorCodeGenerator::getErrorType(InterpretationStage::PARSING) << ")" << std::endl;
              
    std::cout << "SEMANTIC stage: " 
              << ErrorCodeGenerator::generateErrorCode(InterpretationStage::SEMANTIC)
              << " (" << ErrorCodeGenerator::getErrorType(InterpretationStage::SEMANTIC) << ")" << std::endl;
              
    std::cout << "INTERPRETING stage: " 
              << ErrorCodeGenerator::generateErrorCode(InterpretationStage::INTERPRETING)
              << " (" << ErrorCodeGenerator::getErrorType(InterpretationStage::INTERPRETING) << ")" << std::endl;
    
    std::cout << "\n2. Message-Specific Error Code Generation:" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    
    // Generate codes for specific error messages
    std::cout << "Division by zero: " 
              << ErrorCodeGenerator::generateErrorCode(InterpretationStage::INTERPRETING, "Division by zero") << std::endl;
              
    std::cout << "Unexpected token: " 
              << ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING, "Unexpected token") << std::endl;
              
    std::cout << "Invalid character: " 
              << ErrorCodeGenerator::generateErrorCode(InterpretationStage::SCANNING, "Invalid character") << std::endl;
              
    std::cout << "Variable not found: " 
              << ErrorCodeGenerator::generateErrorCode(InterpretationStage::SEMANTIC, "Variable/function not found") << std::endl;
    
    std::cout << "\n3. Consistency Check (same message, same code):" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    
    std::string code1 = ErrorCodeGenerator::generateErrorCode(InterpretationStage::INTERPRETING, "Division by zero");
    std::string code2 = ErrorCodeGenerator::generateErrorCode(InterpretationStage::INTERPRETING, "Division by zero");
    
    std::cout << "First call: " << code1 << std::endl;
    std::cout << "Second call: " << code2 << std::endl;
    std::cout << "Consistent: " << (code1 == code2 ? "YES" : "NO") << std::endl;
    
    std::cout << "\n4. Registry Information:" << std::endl;
    std::cout << "------------------------" << std::endl;
    
    std::cout << "Total registered codes: " << ErrorCodeGenerator::getRegisteredCodeCount() << std::endl;
    
    // Show codes by stage
    auto parsingCodes = ErrorCodeGenerator::getRegisteredCodes(InterpretationStage::PARSING);
    std::cout << "Parsing stage codes (" << parsingCodes.size() << "): ";
    for (const auto& code : parsingCodes) {
        std::cout << code << " ";
    }
    std::cout << std::endl;
    
    auto runtimeCodes = ErrorCodeGenerator::getRegisteredCodes(InterpretationStage::INTERPRETING);
    std::cout << "Runtime stage codes (" << runtimeCodes.size() << "): ";
    for (const auto& code : runtimeCodes) {
        std::cout << code << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\n5. Creating Complete Error Messages:" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    
    // Demonstrate creating complete ErrorMessage structures
    std::string errorCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING, "Unexpected closing brace");
    std::string errorType = ErrorCodeGenerator::getErrorType(InterpretationStage::PARSING);
    
    ErrorMessage errorMsg(errorCode, errorType, "Unexpected closing brace `}`", 
                         "src/utils.calc", 15, 113, "}", InterpretationStage::PARSING);
    
    std::cout << "Complete error message:" << std::endl;
    std::cout << "  Code: " << errorMsg.errorCode << std::endl;
    std::cout << "  Type: " << errorMsg.errorType << std::endl;
    std::cout << "  Description: " << errorMsg.description << std::endl;
    std::cout << "  Location: " << errorMsg.filePath << ":" << errorMsg.line << ":" << errorMsg.column << std::endl;
    std::cout << "  Token: " << errorMsg.problematicToken << std::endl;
    std::cout << "  Complete: " << (errorMsg.isComplete() ? "YES" : "NO") << std::endl;
    
    std::cout << "\n6. Error Context Structures:" << std::endl;
    std::cout << "----------------------------" << std::endl;
    
    // Demonstrate BlockContext
    BlockContext blockCtx("function", 11, 1, "function compute(x, y) =>");
    std::cout << "Block context: " << blockCtx.blockType << " starting at " 
              << blockCtx.startLine << ":" << blockCtx.startColumn 
              << " (" << blockCtx.startLexeme << ")" << std::endl;
    
    // Demonstrate ErrorContext
    ErrorContext errorCtx("src/utils.calc", 15, 113, 
                         "function compute(x, y) =>\n    let x = 514\n    return x + 1;\n}",
                         "}", "{", InterpretationStage::PARSING);
    errorCtx.blockContext = blockCtx;
    
    std::cout << "Error context:" << std::endl;
    std::cout << "  File: " << errorCtx.filePath << std::endl;
    std::cout << "  Position: " << errorCtx.line << ":" << errorCtx.column << std::endl;
    std::cout << "  Lexeme: '" << errorCtx.lexeme << "'" << std::endl;
    std::cout << "  Expected: '" << errorCtx.expectedValue << "'" << std::endl;
    std::cout << "  Has block context: " << (errorCtx.blockContext.has_value() ? "YES" : "NO") << std::endl;
    
    std::cout << "\nDemo completed successfully!" << std::endl;
}

int main() {
    try {
        demonstrateErrorCodeGeneration();
    } catch (const std::exception& e) {
        std::cerr << "Demo failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
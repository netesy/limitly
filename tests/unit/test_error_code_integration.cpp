#include "../../src/error/error_code_generator.hh"
#include "../../src/common/debugger.hh"
#include <iostream>
#include <cassert>

using namespace ErrorHandling;

// Test helper function to print test results
void printTestResult(const std::string& testName, bool passed) {
    std::cout << "[" << (passed ? "PASS" : "FAIL") << "] " << testName << std::endl;
    if (!passed) {
        std::cout << "  Test failed!" << std::endl;
    }
}

// Test integration with existing InterpretationStage enum
void testInterpretationStageIntegration() {
    std::cout << "\n=== Testing InterpretationStage Integration ===" << std::endl;
    
    ErrorCodeGenerator::clearRegistry();
    
    // Test that ErrorCodeGenerator works with the existing InterpretationStage enum
    std::string scanningCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::SCANNING);
    std::string parsingCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING);
    std::string syntaxCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::SYNTAX);
    std::string semanticCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::SEMANTIC);
    std::string bytecodeCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::BYTECODE);
    std::string interpretingCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::INTERPRETING);
    std::string compilingCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::COMPILING);
    
    // Verify all codes are valid
    bool allValid = (scanningCode.length() == 4 && scanningCode[0] == 'E' &&
                    parsingCode.length() == 4 && parsingCode[0] == 'E' &&
                    syntaxCode.length() == 4 && syntaxCode[0] == 'E' &&
                    semanticCode.length() == 4 && semanticCode[0] == 'E' &&
                    bytecodeCode.length() == 4 && bytecodeCode[0] == 'E' &&
                    interpretingCode.length() == 4 && interpretingCode[0] == 'E' &&
                    compilingCode.length() == 4 && compilingCode[0] == 'E');
    
    printTestResult("All InterpretationStage values generate valid codes", allValid);
    
    // Test error type mapping matches expectations
    bool scanningType = (ErrorCodeGenerator::getErrorType(InterpretationStage::SCANNING) == "LexicalError");
    bool parsingType = (ErrorCodeGenerator::getErrorType(InterpretationStage::PARSING) == "SyntaxError");
    bool syntaxType = (ErrorCodeGenerator::getErrorType(InterpretationStage::SYNTAX) == "SyntaxError");
    bool semanticType = (ErrorCodeGenerator::getErrorType(InterpretationStage::SEMANTIC) == "SemanticError");
    bool bytecodeType = (ErrorCodeGenerator::getErrorType(InterpretationStage::BYTECODE) == "BytecodeError");
    bool interpretingType = (ErrorCodeGenerator::getErrorType(InterpretationStage::INTERPRETING) == "RuntimeError");
    bool compilingType = (ErrorCodeGenerator::getErrorType(InterpretationStage::COMPILING) == "CompilationError");
    
    bool allTypesCorrect = scanningType && parsingType && syntaxType && semanticType && 
                          bytecodeType && interpretingType && compilingType;
    
    printTestResult("All error type mappings are correct", allTypesCorrect);
    
    std::cout << "Generated codes: " << scanningCode << " (" << ErrorCodeGenerator::getErrorType(InterpretationStage::SCANNING) << "), "
              << parsingCode << " (" << ErrorCodeGenerator::getErrorType(InterpretationStage::PARSING) << "), "
              << syntaxCode << " (" << ErrorCodeGenerator::getErrorType(InterpretationStage::SYNTAX) << "), "
              << semanticCode << " (" << ErrorCodeGenerator::getErrorType(InterpretationStage::SEMANTIC) << "), "
              << bytecodeCode << " (" << ErrorCodeGenerator::getErrorType(InterpretationStage::BYTECODE) << "), "
              << interpretingCode << " (" << ErrorCodeGenerator::getErrorType(InterpretationStage::INTERPRETING) << "), "
              << compilingCode << " (" << ErrorCodeGenerator::getErrorType(InterpretationStage::COMPILING) << ")" << std::endl;
}

// Test error message consistency with existing debugger patterns
void testExistingErrorMessagePatterns() {
    std::cout << "\n=== Testing Existing Error Message Patterns ===" << std::endl;
    
    ErrorCodeGenerator::clearRegistry();
    
    // Test common error messages that appear in the existing debugger
    std::string divisionCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::INTERPRETING, "Division by zero");
    std::string unexpectedCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING, "Unexpected token");
    std::string undefinedCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::SEMANTIC, "Variable/function not found");
    std::string invalidCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::SCANNING, "Invalid character");
    
    // Verify expected codes
    bool divisionCorrect = (divisionCode == "E400");
    bool unexpectedCorrect = (unexpectedCode == "E100");
    bool undefinedCorrect = (undefinedCode == "E200");
    bool invalidCorrect = (invalidCode == "E001");
    
    printTestResult("Division by zero gets E400", divisionCorrect);
    printTestResult("Unexpected token gets E100", unexpectedCorrect);
    printTestResult("Variable/function not found gets E200", undefinedCorrect);
    printTestResult("Invalid character gets E001", invalidCorrect);
    
    // Test consistency - same message should get same code
    std::string divisionCode2 = ErrorCodeGenerator::generateErrorCode(InterpretationStage::INTERPRETING, "Division by zero");
    std::string unexpectedCode2 = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING, "Unexpected token");
    
    bool divisionConsistent = (divisionCode == divisionCode2);
    bool unexpectedConsistent = (unexpectedCode == unexpectedCode2);
    
    printTestResult("Division by zero codes are consistent", divisionConsistent);
    printTestResult("Unexpected token codes are consistent", unexpectedConsistent);
    
    std::cout << "Error codes: Division=" << divisionCode << ", Unexpected=" << unexpectedCode 
              << ", Undefined=" << undefinedCode << ", Invalid=" << invalidCode << std::endl;
}

// Test ErrorMessage structure creation
void testErrorMessageStructure() {
    std::cout << "\n=== Testing ErrorMessage Structure ===" << std::endl;
    
    // Test creating ErrorMessage with ErrorCodeGenerator
    std::string errorCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING, "Unexpected token");
    std::string errorType = ErrorCodeGenerator::getErrorType(InterpretationStage::PARSING);
    
    ErrorMessage errorMsg(errorCode, errorType, "Unexpected token ';'", "test.lm", 15, 23, ";", InterpretationStage::PARSING);
    
    bool codeCorrect = (errorMsg.errorCode == "E100");
    bool typeCorrect = (errorMsg.errorType == "SyntaxError");
    bool descCorrect = (errorMsg.description == "Unexpected token ';'");
    bool fileCorrect = (errorMsg.filePath == "test.lm");
    bool lineCorrect = (errorMsg.line == 15);
    bool columnCorrect = (errorMsg.column == 23);
    bool tokenCorrect = (errorMsg.problematicToken == ";");
    bool stageCorrect = (errorMsg.stage == InterpretationStage::PARSING);
    bool isComplete = errorMsg.isComplete();
    
    printTestResult("Error code is correct", codeCorrect);
    printTestResult("Error type is correct", typeCorrect);
    printTestResult("Description is correct", descCorrect);
    printTestResult("File path is correct", fileCorrect);
    printTestResult("Line number is correct", lineCorrect);
    printTestResult("Column number is correct", columnCorrect);
    printTestResult("Problematic token is correct", tokenCorrect);
    printTestResult("Stage is correct", stageCorrect);
    printTestResult("Error message is complete", isComplete);
    
    std::cout << "Created ErrorMessage: " << errorMsg.errorCode << "[" << errorMsg.errorType << "] " 
              << errorMsg.description << " at " << errorMsg.filePath << ":" << errorMsg.line << ":" << errorMsg.column << std::endl;
}

// Test ErrorContext and BlockContext structures
void testContextStructures() {
    std::cout << "\n=== Testing Context Structures ===" << std::endl;
    
    // Test BlockContext
    BlockContext blockCtx("function", 10, 5, "function compute");
    
    bool blockTypeCorrect = (blockCtx.blockType == "function");
    bool blockLineCorrect = (blockCtx.startLine == 10);
    bool blockColumnCorrect = (blockCtx.startColumn == 5);
    bool blockLexemeCorrect = (blockCtx.startLexeme == "function compute");
    
    printTestResult("BlockContext type is correct", blockTypeCorrect);
    printTestResult("BlockContext line is correct", blockLineCorrect);
    printTestResult("BlockContext column is correct", blockColumnCorrect);
    printTestResult("BlockContext lexeme is correct", blockLexemeCorrect);
    
    // Test ErrorContext
    ErrorContext errorCtx("test.lm", 15, 23, "let x = 5;\nreturn x + 1;", ";", "}", InterpretationStage::PARSING);
    errorCtx.blockContext = blockCtx;
    
    bool ctxFileCorrect = (errorCtx.filePath == "test.lm");
    bool ctxLineCorrect = (errorCtx.line == 15);
    bool ctxColumnCorrect = (errorCtx.column == 23);
    bool ctxLexemeCorrect = (errorCtx.lexeme == ";");
    bool ctxExpectedCorrect = (errorCtx.expectedValue == "}");
    bool ctxStageCorrect = (errorCtx.stage == InterpretationStage::PARSING);
    bool ctxHasBlock = (errorCtx.blockContext.has_value());
    
    printTestResult("ErrorContext file is correct", ctxFileCorrect);
    printTestResult("ErrorContext line is correct", ctxLineCorrect);
    printTestResult("ErrorContext column is correct", ctxColumnCorrect);
    printTestResult("ErrorContext lexeme is correct", ctxLexemeCorrect);
    printTestResult("ErrorContext expected value is correct", ctxExpectedCorrect);
    printTestResult("ErrorContext stage is correct", ctxStageCorrect);
    printTestResult("ErrorContext has block context", ctxHasBlock);
    
    if (ctxHasBlock) {
        bool blockInCtxCorrect = (errorCtx.blockContext->blockType == "function");
        printTestResult("Block context in ErrorContext is correct", blockInCtxCorrect);
    }
    
    std::cout << "ErrorContext: " << errorCtx.filePath << ":" << errorCtx.line << ":" << errorCtx.column 
              << " (stage: " << static_cast<int>(errorCtx.stage) << ")" << std::endl;
}

int main() {
    std::cout << "Running ErrorCodeGenerator Integration Tests" << std::endl;
    std::cout << "=============================================" << std::endl;
    
    try {
        testInterpretationStageIntegration();
        testExistingErrorMessagePatterns();
        testErrorMessageStructure();
        testContextStructures();
        
        std::cout << "\n=== All Integration Tests Completed ===" << std::endl;
        std::cout << "If all tests show [PASS], the ErrorCodeGenerator integrates correctly!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Integration test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
#include "../../src/error_code_generator.hh"
#include <iostream>
#include <cassert>
#include <thread>
#include <vector>
#include <set>

using namespace ErrorHandling;

// Test helper function to print test results
void printTestResult(const std::string& testName, bool passed) {
    std::cout << "[" << (passed ? "PASS" : "FAIL") << "] " << testName << std::endl;
    if (!passed) {
        std::cout << "  Test failed!" << std::endl;
    }
}

// Test basic error code generation
void testBasicErrorCodeGeneration() {
    std::cout << "\n=== Testing Basic Error Code Generation ===" << std::endl;
    
    ErrorCodeGenerator::clearRegistry();
    
    // Test code generation for different stages
    std::string scanningCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::SCANNING);
    std::string parsingCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING);
    std::string semanticCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::SEMANTIC);
    std::string runtimeCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::INTERPRETING);
    std::string bytecodeCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::BYTECODE);
    std::string compilingCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::COMPILING);
    
    // Verify codes are in correct ranges
    bool scanningInRange = (scanningCode >= "E001" && scanningCode <= "E099");
    bool parsingInRange = (parsingCode >= "E100" && parsingCode <= "E199");
    bool semanticInRange = (semanticCode >= "E200" && semanticCode <= "E299");
    bool runtimeInRange = (runtimeCode >= "E400" && runtimeCode <= "E499");
    bool bytecodeInRange = (bytecodeCode >= "E500" && bytecodeCode <= "E599");
    bool compilingInRange = (compilingCode >= "E600" && compilingCode <= "E699");
    
    printTestResult("Scanning code in range E001-E099", scanningInRange);
    printTestResult("Parsing code in range E100-E199", parsingInRange);
    printTestResult("Semantic code in range E200-E299", semanticInRange);
    printTestResult("Runtime code in range E400-E499", runtimeInRange);
    printTestResult("Bytecode code in range E500-E599", bytecodeInRange);
    printTestResult("Compiling code in range E600-E699", compilingInRange);
    
    // Verify all codes are unique
    std::set<std::string> allCodes = {scanningCode, parsingCode, semanticCode, 
                                     runtimeCode, bytecodeCode, compilingCode};
    bool allUnique = (allCodes.size() == 6);
    printTestResult("All generated codes are unique", allUnique);
    
    std::cout << "Generated codes: " << scanningCode << ", " << parsingCode << ", " 
              << semanticCode << ", " << runtimeCode << ", " << bytecodeCode << ", " 
              << compilingCode << std::endl;
}

// Test error type mapping
void testErrorTypeMapping() {
    std::cout << "\n=== Testing Error Type Mapping ===" << std::endl;
    
    bool scanningType = (ErrorCodeGenerator::getErrorType(InterpretationStage::SCANNING) == "LexicalError");
    bool parsingType = (ErrorCodeGenerator::getErrorType(InterpretationStage::PARSING) == "SyntaxError");
    bool syntaxType = (ErrorCodeGenerator::getErrorType(InterpretationStage::SYNTAX) == "SyntaxError");
    bool semanticType = (ErrorCodeGenerator::getErrorType(InterpretationStage::SEMANTIC) == "SemanticError");
    bool bytecodeType = (ErrorCodeGenerator::getErrorType(InterpretationStage::BYTECODE) == "BytecodeError");
    bool runtimeType = (ErrorCodeGenerator::getErrorType(InterpretationStage::INTERPRETING) == "RuntimeError");
    bool compilingType = (ErrorCodeGenerator::getErrorType(InterpretationStage::COMPILING) == "CompilationError");
    
    printTestResult("SCANNING -> LexicalError", scanningType);
    printTestResult("PARSING -> SyntaxError", parsingType);
    printTestResult("SYNTAX -> SyntaxError", syntaxType);
    printTestResult("SEMANTIC -> SemanticError", semanticType);
    printTestResult("BYTECODE -> BytecodeError", bytecodeType);
    printTestResult("INTERPRETING -> RuntimeError", runtimeType);
    printTestResult("COMPILING -> CompilationError", compilingType);
}

// Test message-specific code generation
void testMessageSpecificCodeGeneration() {
    std::cout << "\n=== Testing Message-Specific Code Generation ===" << std::endl;
    
    ErrorCodeGenerator::clearRegistry();
    
    // Test specific error messages get consistent codes
    std::string divisionCode1 = ErrorCodeGenerator::generateErrorCode(InterpretationStage::INTERPRETING, "Division by zero");
    std::string divisionCode2 = ErrorCodeGenerator::generateErrorCode(InterpretationStage::INTERPRETING, "Division by zero");
    
    std::string unexpectedCode1 = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING, "Unexpected token");
    std::string unexpectedCode2 = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING, "Unexpected token");
    
    bool divisionConsistent = (divisionCode1 == divisionCode2);
    bool unexpectedConsistent = (unexpectedCode1 == unexpectedCode2);
    bool expectedDivisionCode = (divisionCode1 == "E400");
    bool expectedUnexpectedCode = (unexpectedCode1 == "E100");
    
    printTestResult("Division by zero generates consistent codes", divisionConsistent);
    printTestResult("Unexpected token generates consistent codes", unexpectedConsistent);
    printTestResult("Division by zero gets expected code E400", expectedDivisionCode);
    printTestResult("Unexpected token gets expected code E100", expectedUnexpectedCode);
    
    std::cout << "Division codes: " << divisionCode1 << ", " << divisionCode2 << std::endl;
    std::cout << "Unexpected codes: " << unexpectedCode1 << ", " << unexpectedCode2 << std::endl;
}

// Test code registration and conflict prevention
void testCodeRegistration() {
    std::cout << "\n=== Testing Code Registration ===" << std::endl;
    
    ErrorCodeGenerator::clearRegistry();
    
    // Generate some codes
    std::string code1 = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING);
    std::string code2 = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING);
    std::string code3 = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING);
    
    // Check registration
    bool code1Registered = ErrorCodeGenerator::isCodeRegistered(code1);
    bool code2Registered = ErrorCodeGenerator::isCodeRegistered(code2);
    bool code3Registered = ErrorCodeGenerator::isCodeRegistered(code3);
    bool fakeCodeRegistered = ErrorCodeGenerator::isCodeRegistered("E999");
    
    printTestResult("Generated code 1 is registered", code1Registered);
    printTestResult("Generated code 2 is registered", code2Registered);
    printTestResult("Generated code 3 is registered", code3Registered);
    printTestResult("Fake code E999 is not registered", !fakeCodeRegistered);
    
    // Check that all codes are different
    bool allDifferent = (code1 != code2 && code2 != code3 && code1 != code3);
    printTestResult("All generated codes are different", allDifferent);
    
    // Check registry count
    size_t registryCount = ErrorCodeGenerator::getRegisteredCodeCount();
    bool correctCount = (registryCount >= 3); // At least the 3 we generated
    printTestResult("Registry count is correct", correctCount);
    
    std::cout << "Generated codes: " << code1 << ", " << code2 << ", " << code3 << std::endl;
    std::cout << "Registry count: " << registryCount << std::endl;
}

// Test getting registered codes by stage
void testGetRegisteredCodesByStage() {
    std::cout << "\n=== Testing Get Registered Codes by Stage ===" << std::endl;
    
    ErrorCodeGenerator::clearRegistry();
    
    // Generate codes for different stages
    std::string scanCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::SCANNING);
    std::string parseCode1 = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING);
    std::string parseCode2 = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING);
    std::string semanticCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::SEMANTIC);
    
    // Get codes by stage
    auto scanningCodes = ErrorCodeGenerator::getRegisteredCodes(InterpretationStage::SCANNING);
    auto parsingCodes = ErrorCodeGenerator::getRegisteredCodes(InterpretationStage::PARSING);
    auto semanticCodes = ErrorCodeGenerator::getRegisteredCodes(InterpretationStage::SEMANTIC);
    auto runtimeCodes = ErrorCodeGenerator::getRegisteredCodes(InterpretationStage::INTERPRETING);
    
    bool scanningCount = (scanningCodes.size() == 1);
    bool parsingCount = (parsingCodes.size() == 2);
    bool semanticCount = (semanticCodes.size() == 1);
    bool runtimeCount = (runtimeCodes.size() == 0);
    
    printTestResult("Scanning stage has 1 registered code", scanningCount);
    printTestResult("Parsing stage has 2 registered codes", parsingCount);
    printTestResult("Semantic stage has 1 registered code", semanticCount);
    printTestResult("Runtime stage has 0 registered codes", runtimeCount);
    
    // Check that the right codes are in the right stages
    bool scanContainsCode = (scanningCodes.find(scanCode) != scanningCodes.end());
    bool parseContainsCodes = (parsingCodes.find(parseCode1) != parsingCodes.end() && 
                              parsingCodes.find(parseCode2) != parsingCodes.end());
    bool semanticContainsCode = (semanticCodes.find(semanticCode) != semanticCodes.end());
    
    printTestResult("Scanning codes contain generated scanning code", scanContainsCode);
    printTestResult("Parsing codes contain generated parsing codes", parseContainsCodes);
    printTestResult("Semantic codes contain generated semantic code", semanticContainsCode);
}

// Test thread safety
void testThreadSafety() {
    std::cout << "\n=== Testing Thread Safety ===" << std::endl;
    
    ErrorCodeGenerator::clearRegistry();
    
    const int numThreads = 10;
    const int codesPerThread = 5;
    std::vector<std::thread> threads;
    std::vector<std::vector<std::string>> threadCodes(numThreads);
    
    // Launch threads that generate codes concurrently
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([i, codesPerThread, &threadCodes]() {
            for (int j = 0; j < codesPerThread; ++j) {
                std::string code = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING);
                threadCodes[i].push_back(code);
            }
        });
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Collect all generated codes
    std::set<std::string> allCodes;
    for (const auto& codes : threadCodes) {
        for (const auto& code : codes) {
            allCodes.insert(code);
        }
    }
    
    // Check that all codes are unique (no race conditions)
    size_t totalGenerated = numThreads * codesPerThread;
    bool allUnique = (allCodes.size() == totalGenerated);
    
    // Check that registry count matches
    size_t registryCount = ErrorCodeGenerator::getRegisteredCodeCount();
    bool registryMatches = (registryCount == totalGenerated);
    
    printTestResult("All thread-generated codes are unique", allUnique);
    printTestResult("Registry count matches generated codes", registryMatches);
    
    std::cout << "Generated " << totalGenerated << " codes, " << allCodes.size() 
              << " unique, registry has " << registryCount << std::endl;
}

// Test edge cases
void testEdgeCases() {
    std::cout << "\n=== Testing Edge Cases ===" << std::endl;
    
    ErrorCodeGenerator::clearRegistry();
    
    // Test empty error message
    std::string emptyMsgCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING, "");
    bool emptyMsgValid = (emptyMsgCode.length() == 4 && emptyMsgCode[0] == 'E');
    printTestResult("Empty error message generates valid code", emptyMsgValid);
    
    // Test unknown error message
    std::string unknownMsgCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::PARSING, 
                                                                      "This is a completely unknown error message");
    bool unknownMsgValid = (unknownMsgCode.length() == 4 && unknownMsgCode[0] == 'E');
    printTestResult("Unknown error message generates valid code", unknownMsgValid);
    
    // Test partial message match
    std::string partialCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::INTERPRETING, 
                                                                   "Error: Division by zero occurred");
    bool partialMatch = (partialCode == "E400"); // Should match "Division by zero"
    printTestResult("Partial message match works correctly", partialMatch);
    
    // Test case sensitivity
    std::string upperCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::INTERPRETING, 
                                                                 "DIVISION BY ZERO");
    std::string lowerCode = ErrorCodeGenerator::generateErrorCode(InterpretationStage::INTERPRETING, 
                                                                 "division by zero");
    // These should generate different codes since the mapping is case-sensitive
    bool caseSensitive = (upperCode != lowerCode);
    printTestResult("Error code generation is case-sensitive", caseSensitive);
    
    std::cout << "Empty message code: " << emptyMsgCode << std::endl;
    std::cout << "Unknown message code: " << unknownMsgCode << std::endl;
    std::cout << "Partial match code: " << partialCode << std::endl;
    std::cout << "Upper case code: " << upperCode << ", Lower case code: " << lowerCode << std::endl;
}

int main() {
    std::cout << "Running ErrorCodeGenerator Unit Tests" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    try {
        testBasicErrorCodeGeneration();
        testErrorTypeMapping();
        testMessageSpecificCodeGeneration();
        testCodeRegistration();
        testGetRegisteredCodesByStage();
        testThreadSafety();
        testEdgeCases();
        
        std::cout << "\n=== All Tests Completed ===" << std::endl;
        std::cout << "If all tests show [PASS], the ErrorCodeGenerator is working correctly!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
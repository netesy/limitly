#include "error_code_generator.hh"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <regex>

namespace ErrorHandling {

// Static member definitions
std::unordered_set<std::string> ErrorCodeGenerator::registeredCodes;
std::unordered_map<InterpretationStage, int> ErrorCodeGenerator::stageCounters;
std::mutex ErrorCodeGenerator::registryMutex;
std::unordered_map<std::string, std::string> ErrorCodeGenerator::messageToCodeMap;
bool ErrorCodeGenerator::messageMappingInitialized = false;

std::string ErrorCodeGenerator::generateErrorCode(InterpretationStage stage, 
                                                const std::string& errorMessage) {
    std::lock_guard<std::mutex> lock(registryMutex);
    
    // Initialize message mapping if not done yet
    if (!messageMappingInitialized) {
        initializeMessageMapping();
        messageMappingInitialized = true;
    }
    
    // Check if we have a specific code for this error message
    if (!errorMessage.empty()) {
        // Try to find a specific mapping for this error message
        for (const auto& pair : messageToCodeMap) {
            if (errorMessage.find(pair.first) != std::string::npos) {
                // Make sure this code is in the right range for the stage
                CodeRange range = getCodeRange(stage);
                std::string candidateCode = pair.second;
                
                // Extract the numeric part of the code
                if (candidateCode.length() >= 4 && candidateCode[0] == 'E') {
                    int codeNum = std::stoi(candidateCode.substr(1));
                    if (codeNum >= range.start && codeNum <= range.end) {
                        registerErrorCode(candidateCode, stage, errorMessage);
                        return candidateCode;
                    }
                }
            }
        }
    }
    
    // Generate next available code for this stage
    return getNextAvailableCode(stage);
}

std::string ErrorCodeGenerator::getErrorType(InterpretationStage stage) {
    switch (stage) {
        case InterpretationStage::SCANNING:
            return "LexicalError";
        case InterpretationStage::PARSING:
        case InterpretationStage::SYNTAX:
            return "SyntaxError";
        case InterpretationStage::SEMANTIC:
            return "SemanticError";
        case InterpretationStage::BYTECODE:
            return "BytecodeError";
        case InterpretationStage::INTERPRETING:
            return "RuntimeError";
        case InterpretationStage::COMPILING:
            return "CompilationError";
        default:
            return "UnknownError";
    }
}

bool ErrorCodeGenerator::isCodeRegistered(const std::string& errorCode) {
    std::lock_guard<std::mutex> lock(registryMutex);
    return registeredCodes.find(errorCode) != registeredCodes.end();
}

std::string ErrorCodeGenerator::getNextAvailableCode(InterpretationStage stage) {
    CodeRange range = getCodeRange(stage);
    
    // Get current counter for this stage, or initialize to range start
    if (stageCounters.find(stage) == stageCounters.end()) {
        stageCounters[stage] = range.start;
    }
    
    // Find next available code in the range
    int currentCode = stageCounters[stage];
    while (currentCode <= range.end) {
        std::string candidateCode = formatErrorCode(currentCode);
        if (registeredCodes.find(candidateCode) == registeredCodes.end()) {
            // Found an available code
            registerErrorCode(candidateCode, stage);
            stageCounters[stage] = currentCode + 1;
            return candidateCode;
        }
        currentCode++;
    }
    
    // If we've exhausted the range, wrap around and try again
    // This shouldn't happen in normal usage, but provides safety
    for (int code = range.start; code < stageCounters[stage]; code++) {
        std::string candidateCode = formatErrorCode(code);
        if (registeredCodes.find(candidateCode) == registeredCodes.end()) {
            registerErrorCode(candidateCode, stage);
            return candidateCode;
        }
    }
    
    // If we still can't find a code, generate one outside the normal range
    // This indicates a serious issue with code allocation
    std::string fallbackCode = formatErrorCode(range.end + 1);
    registerErrorCode(fallbackCode, stage, "OVERFLOW_CODE");
    return fallbackCode;
}

void ErrorCodeGenerator::registerErrorCode(const std::string& errorCode, 
                                         InterpretationStage stage,
                                         const std::string& description) {
    // Note: This method assumes the mutex is already locked by the caller
    registeredCodes.insert(errorCode);
}

std::unordered_set<std::string> ErrorCodeGenerator::getRegisteredCodes(InterpretationStage stage) {
    std::lock_guard<std::mutex> lock(registryMutex);
    std::unordered_set<std::string> stageCodes;
    CodeRange range = getCodeRange(stage);
    
    for (const std::string& code : registeredCodes) {
        if (code.length() >= 4 && code[0] == 'E') {
            int codeNum = std::stoi(code.substr(1));
            if (codeNum >= range.start && codeNum <= range.end) {
                stageCodes.insert(code);
            }
        }
    }
    
    return stageCodes;
}

void ErrorCodeGenerator::clearRegistry() {
    std::lock_guard<std::mutex> lock(registryMutex);
    registeredCodes.clear();
    stageCounters.clear();
    messageMappingInitialized = false;
}

size_t ErrorCodeGenerator::getRegisteredCodeCount() {
    std::lock_guard<std::mutex> lock(registryMutex);
    return registeredCodes.size();
}

ErrorCodeGenerator::CodeRange ErrorCodeGenerator::getCodeRange(InterpretationStage stage) {
    switch (stage) {
        case InterpretationStage::SCANNING:
            return {1, 99, "E"};
        case InterpretationStage::PARSING:
        case InterpretationStage::SYNTAX:
            return {100, 199, "E"};
        case InterpretationStage::SEMANTIC:
            return {200, 299, "E"};
        case InterpretationStage::BYTECODE:
            return {500, 599, "E"};
        case InterpretationStage::INTERPRETING:
            return {400, 499, "E"};
        case InterpretationStage::COMPILING:
            return {600, 699, "E"};
        default:
            return {900, 999, "E"}; // Unknown/fallback range
    }
}

std::string ErrorCodeGenerator::formatErrorCode(int codeNumber) {
    std::ostringstream oss;
    oss << "E" << std::setfill('0') << std::setw(3) << codeNumber;
    return oss.str();
}

void ErrorCodeGenerator::initializeMessageMapping() {
    // Lexical/Scanning errors (E001-E099)
    messageToCodeMap["Invalid character"] = "E001";
    messageToCodeMap["Unterminated string"] = "E002";
    messageToCodeMap["Unterminated comment"] = "E003";
    messageToCodeMap["Invalid number format"] = "E004";
    messageToCodeMap["Invalid escape sequence"] = "E005";
    
    // Syntax/Parsing errors (E100-E199)
    messageToCodeMap["Unexpected token"] = "E100";
    messageToCodeMap["Expected"] = "E101";
    messageToCodeMap["Unexpected closing brace"] = "E102";
    messageToCodeMap["Missing opening brace"] = "E103";
    messageToCodeMap["Missing closing brace"] = "E104";
    messageToCodeMap["Invalid factor"] = "E105";
    messageToCodeMap["Missing semicolon"] = "E106";
    messageToCodeMap["Invalid expression"] = "E107";
    messageToCodeMap["Invalid statement"] = "E108";
    messageToCodeMap["Unexpected end of file"] = "E109";
    messageToCodeMap["Invalid function declaration"] = "E110";
    messageToCodeMap["Invalid parameter list"] = "E111";
    messageToCodeMap["Invalid variable declaration"] = "E112";
    
    // Semantic errors (E200-E299)
    messageToCodeMap["Variable/function not found"] = "E200";
    messageToCodeMap["Undefined variable"] = "E201";
    messageToCodeMap["Undefined function"] = "E202";
    messageToCodeMap["Variable already declared"] = "E203";
    messageToCodeMap["Function already declared"] = "E204";
    messageToCodeMap["Type mismatch"] = "E205";
    messageToCodeMap["Invalid assignment"] = "E206";
    messageToCodeMap["Invalid function call"] = "E207";
    messageToCodeMap["Wrong number of arguments"] = "E208";
    messageToCodeMap["Invalid return type"] = "E209";
    
    // Runtime/Interpreting errors (E400-E499)
    messageToCodeMap["Division by zero"] = "E400";
    messageToCodeMap["Modulo by zero"] = "E401";
    messageToCodeMap["Invalid value stack for unary operation"] = "E402";
    messageToCodeMap["Invalid value stack for binary operation"] = "E403";
    messageToCodeMap["Unsupported type for NEGATE operation"] = "E404";
    messageToCodeMap["Unsupported type for NOT operation"] = "E405";
    messageToCodeMap["Unsupported types for binary operation"] = "E406";
    messageToCodeMap["Insufficient value stack for logical operation"] = "E407";
    messageToCodeMap["Unsupported types for logical operation"] = "E408";
    messageToCodeMap["Insufficient value stack for comparison operation"] = "E409";
    messageToCodeMap["Unsupported types for comparison operation"] = "E410";
    messageToCodeMap["Invalid variable index"] = "E411";
    messageToCodeMap["value stack underflow"] = "E412";
    messageToCodeMap["Invalid jump offset type"] = "E413";
    messageToCodeMap["JUMP_IF_FALSE requires a boolean condition"] = "E414";
    messageToCodeMap["Stack overflow"] = "E415";
    messageToCodeMap["Null reference"] = "E416";
    messageToCodeMap["Out of bounds access"] = "E417";
    
    // Bytecode generation errors (E500-E599)
    messageToCodeMap["Invalid bytecode instruction"] = "E500";
    messageToCodeMap["Bytecode generation failed"] = "E501";
    messageToCodeMap["Invalid opcode"] = "E502";
    messageToCodeMap["Bytecode optimization error"] = "E503";
    messageToCodeMap["Type mismatch"] = "E504";
    
    // Compilation errors (E600-E699)
    messageToCodeMap["Compilation failed"] = "E600";
    messageToCodeMap["Linker error"] = "E601";
    messageToCodeMap["Missing dependency"] = "E602";
}

} // namespace ErrorHandling
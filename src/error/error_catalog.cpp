#include "error_catalog.hh"
#include <algorithm>
#include <sstream>
#include <iostream>

namespace ErrorHandling {

ErrorCatalog& ErrorCatalog::getInstance() {
    static ErrorCatalog instance;
    return instance;
}

void ErrorCatalog::initialize() {
    std::lock_guard<std::mutex> lock(catalogMutex);
    
    if (initialized) {
        return; // Already initialized
    }
    
    // Clear any existing data
    definitions.clear();
    patternMatchers.clear();
    stageToCodesMap.clear();
    
    // Initialize error definitions for each stage
    initializeLexicalErrors();
    initializeSyntaxErrors();
    initializeSemanticErrors();
    initializeRuntimeErrors();
    initializeBytecodeErrors();
    initializeCompilationErrors();
    
    initialized = true;
}

const ErrorDefinition* ErrorCatalog::lookupByMessage(const std::string& errorMessage, 
                                                    InterpretationStage stage) const {
    std::lock_guard<std::mutex> lock(catalogMutex);
    
    if (!initialized) {
        return nullptr;
    }
    
    // Try pattern matching with stage-specific patterns first
    for (const auto& matcher : patternMatchers) {
        if (matcher.stage == stage && std::regex_search(errorMessage, matcher.pattern)) {
            auto it = definitions.find(matcher.errorCode);
            if (it != definitions.end()) {
                return it->second.get();
            }
        }
    }
    
    // If no stage-specific match, try any stage
    for (const auto& matcher : patternMatchers) {
        if (std::regex_search(errorMessage, matcher.pattern)) {
            auto it = definitions.find(matcher.errorCode);
            if (it != definitions.end()) {
                return it->second.get();
            }
        }
    }
    
    return nullptr;
}

const ErrorDefinition* ErrorCatalog::lookupByCode(const std::string& errorCode) const {
    std::lock_guard<std::mutex> lock(catalogMutex);
    
    auto it = definitions.find(errorCode);
    return (it != definitions.end()) ? it->second.get() : nullptr;
}

std::vector<const ErrorDefinition*> ErrorCatalog::getDefinitionsForStage(InterpretationStage stage) const {
    std::lock_guard<std::mutex> lock(catalogMutex);
    
    std::vector<const ErrorDefinition*> result;
    
    auto stageIt = stageToCodesMap.find(stage);
    if (stageIt != stageToCodesMap.end()) {
        for (const std::string& code : stageIt->second) {
            auto defIt = definitions.find(code);
            if (defIt != definitions.end()) {
                result.push_back(defIt->second.get());
            }
        }
    }
    
    return result;
}

bool ErrorCatalog::addDefinition(const ErrorDefinition& definition) {
    std::lock_guard<std::mutex> lock(catalogMutex);
    
    // Check if code already exists
    if (definitions.find(definition.code) != definitions.end()) {
        return false;
    }
    
    auto newDef = std::make_unique<ErrorDefinition>(definition);
    addDefinitionInternal(std::move(newDef));
    return true;
}

bool ErrorCatalog::removeDefinition(const std::string& errorCode) {
    std::lock_guard<std::mutex> lock(catalogMutex);
    
    auto it = definitions.find(errorCode);
    if (it == definitions.end()) {
        return false;
    }
    
    // Remove from definitions
    definitions.erase(it);
    
    // Remove from pattern matchers
    patternMatchers.erase(
        std::remove_if(patternMatchers.begin(), patternMatchers.end(),
                      [&errorCode](const PatternMatcher& matcher) {
                          return matcher.errorCode == errorCode;
                      }),
        patternMatchers.end());
    
    // Remove from stage map
    for (auto& stagePair : stageToCodesMap) {
        auto& codes = stagePair.second;
        codes.erase(std::remove(codes.begin(), codes.end(), errorCode), codes.end());
    }
    
    return true;
}

size_t ErrorCatalog::getDefinitionCount() const {
    std::lock_guard<std::mutex> lock(catalogMutex);
    return definitions.size();
}

void ErrorCatalog::clear() {
    std::lock_guard<std::mutex> lock(catalogMutex);
    definitions.clear();
    patternMatchers.clear();
    stageToCodesMap.clear();
    initialized = false;
}

bool ErrorCatalog::isInitialized() const {
    std::lock_guard<std::mutex> lock(catalogMutex);
    return initialized;
}

std::string ErrorCatalog::generateHint(const ErrorDefinition& definition, 
                                     const ErrorContext& context) const {
    return substituteTemplate(definition.hintTemplate, context);
}

std::string ErrorCatalog::generateSuggestion(const ErrorDefinition& definition, 
                                           const ErrorContext& context) const {
    return substituteTemplate(definition.suggestionTemplate, context);
}

std::vector<std::string> ErrorCatalog::getCommonCauses(const std::string& errorCode) const {
    std::lock_guard<std::mutex> lock(catalogMutex);
    
    auto it = definitions.find(errorCode);
    if (it != definitions.end()) {
        return it->second->commonCauses;
    }
    
    return {};
}

// Private helper methods

void ErrorCatalog::addDefinitionInternal(std::unique_ptr<ErrorDefinition> definition) {
    std::string code = definition->code;
    
    // Create pattern matcher
    createPatternMatcher(*definition);
    
    // Add to stage map
    // Determine stage from error code range
    InterpretationStage stage = InterpretationStage::SCANNING;
    if (code.length() >= 4 && code[0] == 'E') {
        int codeNum = std::stoi(code.substr(1));
        if (codeNum >= 1 && codeNum <= 99) {
            stage = InterpretationStage::SCANNING;
        } else if (codeNum >= 100 && codeNum <= 199) {
            stage = InterpretationStage::PARSING;
        } else if (codeNum >= 200 && codeNum <= 299) {
            stage = InterpretationStage::SEMANTIC;
        } else if (codeNum >= 400 && codeNum <= 499) {
            stage = InterpretationStage::INTERPRETING;
        } else if (codeNum >= 500 && codeNum <= 599) {
            stage = InterpretationStage::BYTECODE;
        } else if (codeNum >= 600 && codeNum <= 699) {
            stage = InterpretationStage::COMPILING;
        }
    }
    
    stageToCodesMap[stage].push_back(code);
    
    // Add to definitions map
    definitions[code] = std::move(definition);
}

void ErrorCatalog::createPatternMatcher(const ErrorDefinition& definition) {
    if (!definition.pattern.empty()) {
        // Determine stage from error code
        InterpretationStage stage = InterpretationStage::SCANNING;
        if (definition.code.length() >= 4 && definition.code[0] == 'E') {
            int codeNum = std::stoi(definition.code.substr(1));
            if (codeNum >= 1 && codeNum <= 99) {
                stage = InterpretationStage::SCANNING;
            } else if (codeNum >= 100 && codeNum <= 199) {
                stage = InterpretationStage::PARSING;
            } else if (codeNum >= 200 && codeNum <= 299) {
                stage = InterpretationStage::SEMANTIC;
            } else if (codeNum >= 400 && codeNum <= 499) {
                stage = InterpretationStage::INTERPRETING;
            } else if (codeNum >= 500 && codeNum <= 599) {
                stage = InterpretationStage::BYTECODE;
            } else if (codeNum >= 600 && codeNum <= 699) {
                stage = InterpretationStage::COMPILING;
            }
        }
        
        patternMatchers.emplace_back(definition.pattern, definition.code, stage);
    }
}

std::string ErrorCatalog::substituteTemplate(const std::string& templateStr, 
                                           const ErrorContext& context) const {
    std::string result = templateStr;
    
    // Simple template substitution
    // Replace {lexeme} with the actual lexeme
    size_t pos = result.find("{lexeme}");
    if (pos != std::string::npos) {
        result.replace(pos, 8, context.lexeme);
    }
    
    // Replace {expected} with expected value
    pos = result.find("{expected}");
    if (pos != std::string::npos) {
        result.replace(pos, 10, context.expectedValue);
    }
    
    // Replace {file} with file path
    pos = result.find("{file}");
    if (pos != std::string::npos) {
        result.replace(pos, 6, context.filePath);
    }
    
    // Replace {line} with line number
    pos = result.find("{line}");
    if (pos != std::string::npos) {
        result.replace(pos, 6, std::to_string(context.line));
    }
    
    // Replace {column} with column number
    pos = result.find("{column}");
    if (pos != std::string::npos) {
        result.replace(pos, 8, std::to_string(context.column));
    }
    
    return result;
}

bool ErrorCatalog::matchesPattern(const std::string& message, const std::string& pattern) const {
    try {
        std::regex regex_pattern(pattern, std::regex_constants::icase);
        return std::regex_search(message, regex_pattern);
    } catch (const std::regex_error&) {
        // If regex is invalid, fall back to simple string matching
        return message.find(pattern) != std::string::npos;
    }
}

// Error definition initialization methods

void ErrorCatalog::initializeLexicalErrors() {
    // E001-E099: Lexical/Scanning errors
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E001", "LexicalError", "Invalid character",
        "The scanner encountered a character that is not valid in the Limit language.",
        "Remove or replace the invalid character with a valid one.",
        std::vector<std::string>{"Typing error", "Copy-paste from another language", "Encoding issue"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E002", "LexicalError", "Unterminated string",
        "A string literal was started but never closed with a matching quote.",
        "Add the missing closing quote (\") at the end of the string.",
        std::vector<std::string>{"Missing closing quote", "Newline in string without escape"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E003", "LexicalError", "Unterminated comment",
        "A multi-line comment was started with /* but never closed with */.",
        "Add the missing */ to close the comment block.",
        std::vector<std::string>{"Missing closing */", "Nested comments not supported"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E004", "LexicalError", "Invalid number format",
        "The number format is not valid. Numbers should be integers or decimals.",
        "Check the number format. Use digits 0-9, optionally with a decimal point.",
        std::vector<std::string>{"Multiple decimal points", "Invalid digits", "Scientific notation not supported"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E005", "LexicalError", "Invalid escape sequence",
        "An escape sequence in a string is not recognized.",
        "Use valid escape sequences like \\n, \\t, \\r, \\\", or \\\\.",
        std::vector<std::string>{"Unknown escape character", "Incomplete escape sequence"}
    ));
}

void ErrorCatalog::initializeSyntaxErrors() {
    // E100-E199: Syntax/Parsing errors
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E100", "SyntaxError", "Unexpected token",
        "The parser encountered a token that doesn't fit the expected syntax at this location.",
        "Check the syntax around this location. You might be missing an operator, delimiter, or keyword.",
        std::vector<std::string>{"Missing operator", "Wrong delimiter", "Keyword in wrong place"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E101", "SyntaxError", "Expected",
        "The parser expected a specific token but found something else.",
        "Add the expected token '{expected}' at this location.",
        std::vector<std::string>{"Missing required syntax element", "Wrong token type"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E102", "SyntaxError", "Unexpected closing brace",
        "Found a closing brace '}' without a matching opening brace '{'.",
        "Either remove this closing brace or add a matching opening brace before it.",
        std::vector<std::string>{"Extra closing brace", "Missing opening brace", "Mismatched braces"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E103", "SyntaxError", "Missing opening brace",
        "A block structure requires an opening brace '{' but it's missing.",
        "Add an opening brace '{' to start the block.",
        std::vector<std::string>{"Forgot opening brace", "Wrong block syntax"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E104", "SyntaxError", "Missing closing brace",
        "A block was opened with '{' but never closed with '}'.",
        "Add a closing brace '}' to end the block.",
        std::vector<std::string>{"Forgot closing brace", "Nested blocks confusion"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E105", "SyntaxError", "Invalid factor",
        "The expression contains an invalid factor or operand.",
        "Check that all operands in the expression are valid (variables, numbers, or sub-expressions).",
        std::vector<std::string>{"Invalid operand", "Missing operand", "Wrong expression syntax"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E106", "SyntaxError", "Missing semicolon",
        "A statement should end with a semicolon ';' but it's missing.",
        "Add a semicolon ';' at the end of the statement.",
        std::vector<std::string>{"Forgot semicolon", "Statement not properly terminated"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E107", "SyntaxError", "Invalid expression",
        "The expression syntax is not valid.",
        "Check the expression syntax. Ensure operators and operands are properly arranged.",
        std::vector<std::string>{"Wrong operator usage", "Missing operand", "Invalid operator combination"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E108", "SyntaxError", "Invalid statement",
        "The statement syntax is not recognized.",
        "Check the statement syntax. It might be a typo or unsupported statement type.",
        std::vector<std::string>{"Typo in keyword", "Unsupported statement", "Wrong statement structure"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E109", "SyntaxError", "Unexpected end of file",
        "The file ended unexpectedly while parsing was still in progress.",
        "Check if you have unclosed blocks, statements, or expressions at the end of the file.",
        std::vector<std::string>{"Unclosed block", "Incomplete statement", "Missing closing delimiter"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E110", "SyntaxError", "Invalid function declaration",
        "The function declaration syntax is incorrect.",
        "Check the function declaration syntax: 'fn functionName(parameters) -> returnType { ... }'",
        std::vector<std::string>{"Wrong function syntax", "Missing parameters", "Invalid return type"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E111", "SyntaxError", "Invalid parameter list",
        "The function parameter list syntax is incorrect.",
        "Check parameter syntax: each parameter should be 'name: type' separated by commas.",
        std::vector<std::string>{"Missing parameter type", "Wrong parameter syntax", "Missing comma"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E112", "SyntaxError", "Invalid variable declaration",
        "The variable declaration syntax is incorrect.",
        "Use 'let variableName: type = value;' or 'let variableName = value;' for type inference.",
        std::vector<std::string>{"Missing type annotation", "Wrong declaration syntax", "Missing assignment"}
    ));
}

void ErrorCatalog::initializeSemanticErrors() {
    // E200-E299: Semantic errors
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E200", "SemanticError", "Variable/function not found",
        "The identifier '{lexeme}' is not declared in the current scope.",
        "Check the spelling of '{lexeme}' or declare it before use.",
        std::vector<std::string>{"Typo in identifier name", "Variable not declared", "Out of scope"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E201", "SemanticError", "Undefined variable",
        "The variable '{lexeme}' is used before being declared.",
        "Declare the variable '{lexeme}' before using it.",
        std::vector<std::string>{"Variable used before declaration", "Typo in variable name"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E202", "SemanticError", "Undefined function",
        "The function '{lexeme}' is called but not defined.",
        "Define the function '{lexeme}' or check if it's imported from a module.",
        std::vector<std::string>{"Function not defined", "Missing import", "Typo in function name"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E203", "SemanticError", "Variable already declared",
        "The variable '{lexeme}' is already declared in this scope.",
        "Use a different name or remove the duplicate declaration.",
        std::vector<std::string>{"Duplicate variable name", "Redeclaration in same scope"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E204", "SemanticError", "Function already declared",
        "The function '{lexeme}' is already declared.",
        "Use a different function name or remove the duplicate declaration.",
        std::vector<std::string>{"Duplicate function name", "Function redefinition"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E205", "SemanticError", "Type mismatch",
        "The types in this operation are not compatible.",
        "Ensure the types match or add explicit type conversion.",
        std::vector<std::string>{"Incompatible types", "Missing type conversion", "Wrong type annotation"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E206", "SemanticError", "Invalid assignment",
        "The assignment operation is not valid.",
        "Check that you're assigning a compatible type to the variable.",
        std::vector<std::string>{"Type mismatch in assignment", "Assigning to constant", "Invalid left-hand side"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E207", "SemanticError", "Invalid function call",
        "The function call is not valid.",
        "Check the function name, parameter count, and parameter types.",
        std::vector<std::string>{"Wrong parameter count", "Wrong parameter types", "Function not callable"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E208", "SemanticError", "Wrong number of arguments",
        "The function call has the wrong number of arguments.",
        "Check the function signature and provide the correct number of arguments.",
        std::vector<std::string>{"Too many arguments", "Too few arguments", "Missing required parameter"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E209", "SemanticError", "Invalid return type",
        "The return type doesn't match the function's declared return type.",
        "Ensure the returned value matches the function's return type.",
        std::vector<std::string>{"Type mismatch in return", "Missing return statement", "Wrong return type"}
    ));
}

void ErrorCatalog::initializeRuntimeErrors() {
    // E400-E499: Runtime/Interpreting errors
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E400", "RuntimeError", "Division by zero",
        "Attempted to divide by zero, which is mathematically undefined.",
        "Check that the divisor is not zero before performing division.",
        std::vector<std::string>{"Zero divisor", "Uninitialized variable used as divisor"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E401", "RuntimeError", "Modulo by zero",
        "Attempted to perform modulo operation with zero divisor.",
        "Check that the divisor is not zero before performing modulo operation.",
        std::vector<std::string>{"Zero divisor in modulo", "Uninitialized variable"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E402", "RuntimeError", "Invalid value stack for unary operation",
        "The value stack doesn't have enough values for the unary operation.",
        "This is likely a compiler bug. The stack should have at least one value.",
        std::vector<std::string>{"Stack underflow", "Compiler bug", "Invalid bytecode"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E403", "RuntimeError", "Invalid value stack for binary operation",
        "The value stack doesn't have enough values for the binary operation.",
        "This is likely a compiler bug. The stack should have at least two values.",
        std::vector<std::string>{"Stack underflow", "Compiler bug", "Invalid bytecode"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E404", "RuntimeError", "Unsupported type for NEGATE operation",
        "The NEGATE operation only supports numeric types (int, float).",
        "Ensure you're only negating numeric values.",
        std::vector<std::string>{"Wrong type for negation", "Type system bug"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E405", "RuntimeError", "Unsupported type for NOT operation",
        "The NOT operation only supports boolean types.",
        "Ensure you're only using NOT with boolean values.",
        std::vector<std::string>{"Wrong type for NOT", "Type system bug"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E406", "RuntimeError", "Unsupported types for binary operation",
        "The binary operation doesn't support the given types.",
        "Ensure both operands are of compatible types for this operation.",
        std::vector<std::string>{"Type mismatch", "Unsupported operation", "Type system bug"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E407", "RuntimeError", "Insufficient value stack for logical operation",
        "The value stack doesn't have enough values for the logical operation.",
        "This is likely a compiler bug. The stack should have at least two values.",
        std::vector<std::string>{"Stack underflow", "Compiler bug", "Invalid bytecode"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E408", "RuntimeError", "Unsupported types for logical operation",
        "Logical operations only support boolean types.",
        "Ensure both operands are boolean values.",
        std::vector<std::string>{"Wrong type for logical operation", "Type system bug"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E409", "RuntimeError", "Insufficient value stack for comparison operation",
        "The value stack doesn't have enough values for the comparison operation.",
        "This is likely a compiler bug. The stack should have at least two values.",
        std::vector<std::string>{"Stack underflow", "Compiler bug", "Invalid bytecode"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E410", "RuntimeError", "Unsupported types for comparison operation",
        "The comparison operation doesn't support the given types.",
        "Ensure both operands are of comparable types.",
        std::vector<std::string>{"Type mismatch in comparison", "Unsupported comparison", "Type system bug"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E411", "RuntimeError", "Invalid variable index",
        "The variable index is out of bounds.",
        "This is likely a compiler bug. Variable indices should be valid.",
        std::vector<std::string>{"Index out of bounds", "Compiler bug", "Invalid bytecode"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E412", "RuntimeError", "value stack underflow",
        "Attempted to pop from an empty value stack.",
        "This is likely a compiler bug. The stack should have sufficient values.",
        std::vector<std::string>{"Stack underflow", "Compiler bug", "Invalid bytecode"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E413", "RuntimeError", "Invalid jump offset type",
        "The jump offset should be an integer but has a different type.",
        "This is likely a compiler bug. Jump offsets should be integers.",
        std::vector<std::string>{"Wrong jump offset type", "Compiler bug", "Invalid bytecode"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E414", "RuntimeError", "JUMP_IF_FALSE requires a boolean condition",
        "The conditional jump instruction requires a boolean condition.",
        "Ensure the condition evaluates to a boolean value.",
        std::vector<std::string>{"Non-boolean condition", "Type system bug", "Compiler bug"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E415", "RuntimeError", "Stack overflow",
        "The call stack has exceeded its maximum depth.",
        "Check for infinite recursion or reduce the recursion depth.",
        std::vector<std::string>{"Infinite recursion", "Deep recursion", "Stack limit exceeded"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E416", "RuntimeError", "Null reference",
        "Attempted to access a null reference.",
        "Check that the reference is not null before accessing it.",
        std::vector<std::string>{"Uninitialized reference", "Null pointer access"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E417", "RuntimeError", "Out of bounds access",
        "Attempted to access an array or collection element outside its bounds.",
        "Check that the index is within the valid range for the collection.",
        std::vector<std::string>{"Invalid index", "Array bounds exceeded", "Collection access error"}
    ));
}

void ErrorCatalog::initializeBytecodeErrors() {
    // E500-E599: Bytecode generation errors
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E500", "BytecodeError", "Invalid bytecode instruction",
        "An invalid bytecode instruction was generated.",
        "This is a compiler bug. The bytecode generator produced an invalid instruction.",
        std::vector<std::string>{"Compiler bug", "Invalid opcode", "Bytecode generation error"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E501", "BytecodeError", "Bytecode generation failed",
        "The bytecode generation process failed.",
        "This is a compiler bug. The AST could not be converted to bytecode.",
        std::vector<std::string>{"Compiler bug", "AST conversion error", "Code generation failure"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E502", "BytecodeError", "Invalid opcode",
        "An invalid opcode was encountered during bytecode generation.",
        "This is a compiler bug. The opcode is not recognized.",
        std::vector<std::string>{"Compiler bug", "Unknown opcode", "Bytecode error"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E503", "BytecodeError", "Bytecode optimization error",
        "An error occurred during bytecode optimization.",
        "This is a compiler bug in the optimization phase.",
        std::vector<std::string>{"Optimization bug", "Compiler bug", "Invalid optimization"}
    ));
}

void ErrorCatalog::initializeCompilationErrors() {
    // E600-E699: Compilation errors
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E600", "CompilationError", "Compilation failed",
        "The compilation process failed.",
        "Check for syntax, semantic, or other errors in your code.",
        std::vector<std::string>{"Multiple errors", "Build system error", "Compiler failure"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E601", "CompilationError", "Linker error",
        "The linker encountered an error while linking the program.",
        "Check for missing dependencies or conflicting symbols.",
        std::vector<std::string>{"Missing dependency", "Symbol conflict", "Linker failure"}
    ));
    
    addDefinitionInternal(std::make_unique<ErrorDefinition>(
        "E602", "CompilationError", "Missing dependency",
        "A required dependency is missing.",
        "Install the missing dependency or check your import statements.",
        std::vector<std::string>{"Missing module", "Import error", "Dependency not found"}
    ));
}

} // namespace ErrorHandling
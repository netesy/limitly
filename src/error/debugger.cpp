// debugger.cpp

#include "debugger.hh"
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <iomanip>
#include <map>

namespace LM {
namespace Error {

std::vector<std::string> Debugger::sourceCodeLines;
bool Debugger::hadError = false;
std::set<std::string> Debugger::reportedErrors;
bool Debugger::debugMode = false;
size_t Debugger::errorCount = 0;
size_t Debugger::warningCount = 0;
bool Debugger::useModernDiagnostics = false;
std::vector<Debugger::Diagnostic> Debugger::collectedDiagnostics;

void Debugger::error(const std::string &errorMessage,
                     int line,
                     int column,
                     InterpretationStage stage,
                     const std::string &code,
                     const std::string &lexeme,
                     const std::string &expectedValue)
{
    // Create a unique key for this error to prevent duplicates
    std::string errorKey = errorMessage + ":" + std::to_string(line) + ":" + std::to_string(column);
    
    // Check if we've already reported this error
    if (reportedErrors.find(errorKey) != reportedErrors.end()) {
        return; // Skip duplicate error
    }
    
    // Add to reported errors set
    reportedErrors.insert(errorKey);
    
    hadError = true;
    
    // Create enhanced error message
    Message enhancedError = createEnhancedErrorMessage(
        errorMessage, line, column, stage, code, "", lexeme, expectedValue
    );
    debugConsole(enhancedError);
    debugLog(enhancedError);
}

void Debugger::error(const std::string &errorMessage,
                     int line,
                     int column,
                     InterpretationStage stage,
                     const std::string &code,
                     const std::string &filePath,
                     const std::string &lexeme,
                     const std::string &expectedValue)
{
    // Create a unique key for this error to prevent duplicates
    std::string errorKey = errorMessage + ":" + std::to_string(line) + ":" + std::to_string(column) + ":" + filePath;
    
    // Check if we've already reported this error
    if (reportedErrors.find(errorKey) != reportedErrors.end()) {
        return; // Skip duplicate error
    }
    
    // Add to reported errors set
    reportedErrors.insert(errorKey);
    
    hadError = true;
    
    // Create enhanced error message with file path
    Message enhancedError = createEnhancedErrorMessage(
        errorMessage, line, column, stage, code, filePath, lexeme, expectedValue
    );
    debugConsole(enhancedError);
    debugLog(enhancedError);
}

void Debugger::error(const std::string &errorMessage,
                     int line,
                     int column,
                     InterpretationStage stage,
                     const std::string &code,
                     const std::string &filePath,
                     const std::optional<BlockContext> &blockContext,
                     const std::string &lexeme,
                     const std::string &expectedValue)
{
    hadError = true;
    
    // Create enhanced error message with block context
    Message enhancedError = createEnhancedErrorMessage(
        errorMessage, line, column, stage, code, filePath, lexeme, expectedValue, blockContext
    );
    debugConsole(enhancedError);
    debugLog(enhancedError);
}

void Debugger::error(const Message &errorMessage)
{
    hadError = true;
    debugConsole(errorMessage);
    debugLog(errorMessage);
}

void Debugger::debugConsole(const Message &errorMessage)
{
    // Modern compiler-style diagnostics output
    std::string reset = "\033[0m";
    std::string bold = "\033[1m";
    std::string red = "\033[1;31m";      // Bold red for errors
    
    // Format: error[E002]: Expected expression.
    std::cerr << red << bold << "error";
    if (!errorMessage.errorCode.empty()) {
        std::cerr << "[" << errorMessage.errorCode << "]";
    }
    std::cerr << ": " << errorMessage.description << reset << "\n";
    
    // Location: file:line:column
    std::cerr << "  " << bold << "-->" << reset << " " << errorMessage.filePath << ":"
              << errorMessage.line << ":" << errorMessage.column << "\n";
    
    // Source code snippet with line number and caret
    if (!errorMessage.contextLines.empty()) {
        // Show context lines
        for (size_t i = 0; i < errorMessage.contextLines.size(); ++i) {
            int lineNum = errorMessage.line - (errorMessage.contextLines.size() - 1) + i;
            // Adjust for cases where we have more than 2 context lines (error line is not the last)
            if (errorMessage.contextLines.size() > 2) {
                lineNum += 1;
            }
            std::cerr << "   " << std::setw(4) << lineNum 
                      << " | " << errorMessage.contextLines[i] << "\n";
        }
        
        // Show caret pointing to error location
        std::cerr << "       | ";
        for (int i = 1; i < errorMessage.column; ++i) {
            std::cerr << " ";
        }
        std::cerr << "^\n";
    }
    
    // Hint/suggestion
    if (!errorMessage.suggestion.empty()) {
        std::cerr << "   " << bold << "help:" << reset << " " << errorMessage.suggestion << "\n";
    }
    
    if (!errorMessage.hint.empty()) {
        std::cerr << "   " << bold << "note:" << reset << " " << errorMessage.hint << "\n";
    }
    
    if (!errorMessage.causedBy.empty()) {
        std::cerr << "   " << bold << "caused by:" << reset << " " << errorMessage.causedBy << "\n";
    }
    
    std::cerr << "\n";
}

void Debugger::debugLog(const Message &errorMessage)
{
    std::ofstream logfile("debug_log.log", std::ios_base::app);
    if (!logfile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return;
    }

    // Modern compiler-style diagnostics (without colors for log file)
    logfile << "error";
    if (!errorMessage.errorCode.empty()) {
        logfile << "[" << errorMessage.errorCode << "]";
    }
    logfile << ": " << errorMessage.description << "\n";
    
    // Location: file:line:column
    logfile << "  --> " << errorMessage.filePath << ":"
            << errorMessage.line << ":" << errorMessage.column << "\n";
    
    // Source code snippet with line number and caret
    if (!errorMessage.contextLines.empty()) {
        // Show context lines
        for (size_t i = 0; i < errorMessage.contextLines.size(); ++i) {
            int lineNum = errorMessage.line - (errorMessage.contextLines.size() - 1) + i;
            // Adjust for cases where we have more than 2 context lines (error line is not the last)
            if (errorMessage.contextLines.size() > 2) {
                lineNum += 1;
            }
            logfile << "   " << std::setw(4) << lineNum 
                    << " | " << errorMessage.contextLines[i] << "\n";
        }
        
        // Show caret pointing to error location
        logfile << "       | ";
        for (int i = 1; i < errorMessage.column; ++i) {
            logfile << " ";
        }
        logfile << "^\n";
    }
    
    // Hint/suggestion
    if (!errorMessage.suggestion.empty()) {
        logfile << "   help: " << errorMessage.suggestion << "\n";
    }
    
    if (!errorMessage.hint.empty()) {
        logfile << "   note: " << errorMessage.hint << "\n";
    }
    
    if (!errorMessage.causedBy.empty()) {
        logfile << "   caused by: " << errorMessage.causedBy << "\n";
    }
    
    logfile << "\n";
    logfile.close();
}

void Debugger::printContextLines(std::ostream &out, int errorLine, int errorColumn)
{
    std::string boldOn("\033[1m");
    std::string boldOff("\033[0m");
    std::string colorRed("\033[31m");
    std::string colorBlue("\033[32m");
    std::string colorReset("\033[0m");

    // Print the line before the error
    if (errorLine > 1 && errorLine <= int(sourceCodeLines.size())) {
        out << (errorLine - 1) << " | " << sourceCodeLines[errorLine - 2] << std::endl;
    }

    // Print the error line with the faulty token highlighted
    if (errorLine >= 1 && errorLine <= int(sourceCodeLines.size())) {
        std::string currentLine = sourceCodeLines[errorLine - 1];
        out << errorLine << colorBlue << " > " << colorReset << boldOn;

        // Highlight only the faulty token
        int currentColumn = 1;
        for (char c : currentLine) {
            if (currentColumn == errorColumn) {
                out << colorRed;
            }
            out << c;
            if (currentColumn == errorColumn) {
                out << colorReset;
            }
            if (c == '\t') {
                currentColumn += 4; // Assuming tab width of 4
            } else {
                currentColumn++;
            }
        }

        out << boldOff << std::endl;
    }

    // Print the line after the error
    if (errorLine < int(sourceCodeLines.size())) {
        out << (errorLine + 1) << " | " << sourceCodeLines[errorLine] << std::endl;
    }

    out << std::endl;
}

std::vector<std::string> Debugger::splitLines(const std::string &sourceCode)
{
    std::vector<std::string> lines;
    std::stringstream ss(sourceCode);
    std::string line;
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::string Debugger::getTime()
{
    auto current_time = std::chrono::system_clock::now();
    std::time_t current_time_t = std::chrono::system_clock::to_time_t(current_time);
    std::string time_str = std::ctime(&current_time_t);
    // Remove trailing newline from ctime
    if (!time_str.empty() && time_str.back() == '\n') {
        time_str.pop_back();
    }
    return time_str;
}

std::string Debugger::getSuggestion(const std::string &errorMessage,
                                    const std::string &expectedValue)
{
    // Provide suggestions based on the error message and expected value
    
    // === PARSER ERRORS ===
    if (errorMessage.find("Expected method declaration") != std::string::npos) {
        return "Methods in traits/interfaces must have a name, parameters, and return type. Example: fn method(param: type): returnType;";
    } else if (errorMessage.find("Expected 'in' after loop variable") != std::string::npos) {
        return "Iterator syntax is: iter (variable in collection) { ... }. Make sure 'in' is present.";
    } else if (errorMessage.find("Expected variable name or identifier after 'iter'") != std::string::npos) {
        return "Iterator syntax is: iter (variable in collection) { ... }. Provide a variable name.";
    } else if (errorMessage.find("Expected 'task' or 'worker' after 'async'") != std::string::npos) {
        return "Use 'async task' or 'async worker' for concurrent operations.";
    } else if (errorMessage.find("Expected ',' or ')' after type annotation") != std::string::npos) {
        return "Separate parameters with commas or close the parameter list with ')'.";
    } else if (errorMessage.find("Expected '=' or ':' after parameter name") != std::string::npos) {
        return "Parameters need a type annotation (name: type) or default value (name = value).";
    } else if (errorMessage.find("Expected string, number, or identifier as parameter value") != std::string::npos) {
        return "Parameter values must be literals (strings, numbers) or identifiers.";
    } else if (errorMessage.find("Expected ',' or ')' after parameter") != std::string::npos) {
        return "Separate parameters with commas or close the parameter list with ')'.";
    } else if (errorMessage.find("deinit() method cannot have parameters") != std::string::npos) {
        return "The deinit() method takes no parameters. Use: deinit() { ... }";
    } else if (errorMessage.find("Expected ':' after field name in frame member declaration") != std::string::npos) {
        return "Frame fields need a type annotation. Use: fieldName: type";
    } else if (errorMessage.find("Expected frame member declaration") != std::string::npos) {
        return "Frame members must be fields (name: type) or methods (fn name(...): type).";
    } else if (errorMessage.find("Expected module path component") != std::string::npos) {
        return "Module paths should be dot-separated identifiers. Example: import module.submodule;";
    } else if (errorMessage.find("Expected module path or string literal after 'import'") != std::string::npos) {
        return "Import syntax: import module; or import \"path/to/module\";";
    } else if (errorMessage.find("Expected identifier in filter list") != std::string::npos) {
        return "Filter lists contain identifiers. Example: import module show func1, func2;";
    } else if (errorMessage.find("Expected pattern in match case") != std::string::npos) {
        return "Match cases need patterns. Example: match (value) { pattern => { ... }, _ => { ... } }";
    } else if (errorMessage.find("Invalid assignment target") != std::string::npos) {
        return "Assignment targets must be variables or member expressions. Example: x = 5; or obj.field = value;";
    } else if (errorMessage.find("Expected ',' or '}' after rest parameter") != std::string::npos) {
        return "Rest parameters must be followed by a comma or closing brace.";
    } else if (errorMessage.find("Expected field name") != std::string::npos) {
        return "Field declarations need a name. Example: fieldName: type";
    } else if (errorMessage.find("Expected type definition after '='") != std::string::npos) {
        return "Type aliases need a definition. Example: type MyType = int;";
    } else if (errorMessage.find("Expected '[' or '{' for container type") != std::string::npos) {
        return "Container types use brackets: [elementType] for lists or {keyType: valueType} for dicts.";
    } else if (errorMessage.find("Expected identifier after 'err'") != std::string::npos) {
        return "Error types need an identifier. Example: err(ErrorType) or err()";
    } else if (errorMessage.find("Expected expression") != std::string::npos) {
        return "An expression is required here. Provide a value, variable, function call, or operation.";
    } else if (errorMessage.find("Invalid tuple index") != std::string::npos) {
        return "Tuple indices must be numeric literals. Example: tuple[0]";
    }
    
    // === TYPE CHECKER ERRORS ===
    else if (errorMessage.find("Undefined function") != std::string::npos) {
        // Extract function name from error message
        size_t pos = errorMessage.find("Undefined function: ");
        if (pos != std::string::npos) {
            std::string func_name = errorMessage.substr(pos + 20);
            return "Function '" + func_name + "' is not defined. Make sure it's declared before use or imported from a module.";
        }
        return "Check that the function is declared and spelled correctly.";
    } else if (errorMessage.find("Undefined variable") != std::string::npos) {
        // Extract variable name from error message
        size_t pos = errorMessage.find("Undefined variable: ");
        if (pos != std::string::npos) {
            std::string var_name = errorMessage.substr(pos + 20);
            return "Variable '" + var_name + "' is not defined. Declare it before use.";
        }
        return "Check that the variable is declared before use.";
    } else if (errorMessage.find("Type mismatch") != std::string::npos) {
        return "Ensure the value type matches the expected type. Check type annotations and assignments.";
    } else if (errorMessage.find("Cannot call non-function") != std::string::npos) {
        return "Only functions can be called. Check that the expression evaluates to a function.";
    } else if (errorMessage.find("assert() expects exactly 2 arguments") != std::string::npos) {
        return "Use assert(condition, message) with a boolean condition and string message.";
    } else if (errorMessage.find("assert() first argument must be boolean") != std::string::npos) {
        return "The first argument to assert() must be a boolean expression.";
    } else if (errorMessage.find("assert() second argument must be string") != std::string::npos) {
        return "The second argument to assert() must be a string message.";
    }
    
    // === MEMORY SAFETY ERRORS ===
    else if (errorMessage.find("Use of moved linear type") != std::string::npos) {
        return "Linear types can only be used once. After moving a value, it's no longer accessible.";
    } else if (errorMessage.find("Use after move") != std::string::npos) {
        return "The variable was moved and is no longer accessible. Create a new binding or use a reference.";
    } else if (errorMessage.find("Use after drop") != std::string::npos) {
        return "The variable was dropped and is no longer accessible. Ensure proper lifetime management.";
    } else if (errorMessage.find("Use-after-free") != std::string::npos) {
        return "The variable was freed and is no longer accessible. Check memory management and lifetimes.";
    } else if (errorMessage.find("Memory leak") != std::string::npos) {
        return "Memory was allocated but not freed. Ensure all allocated memory is properly released.";
    } else if (errorMessage.find("Dangling pointer") != std::string::npos) {
        return "The pointer references invalid memory. Ensure the referenced object outlives the pointer.";
    } else if (errorMessage.find("Double free") != std::string::npos) {
        return "Memory was freed twice. Ensure each allocation is freed exactly once.";
    } else if (errorMessage.find("Race condition") != std::string::npos) {
        return "Concurrent access to shared data detected. Use synchronization primitives or thread-local storage.";
    } else if (errorMessage.find("Buffer overflow") != std::string::npos) {
        return "Array access may exceed bounds. Check array indices and use bounds checking.";
    } else if (errorMessage.find("Cannot create reference to moved linear type") != std::string::npos) {
        return "Cannot reference a moved value. Create the reference before moving the value.";
    } else if (errorMessage.find("Double move of linear type") != std::string::npos) {
        return "Linear types can only be moved once. After the first move, the value is no longer accessible.";
    } else if (errorMessage.find("Reference invalidated") != std::string::npos) {
        return "The reference became invalid due to changes to the referenced value. Ensure the value remains stable.";
    } else if (errorMessage.find("Use of invalid reference") != std::string::npos) {
        return "The reference is no longer valid. Check that the referenced value still exists.";
    } else if (errorMessage.find("Use of stale reference") != std::string::npos) {
        return "The reference is stale (outdated). References are generation-scoped and become invalid after changes.";
    } else if (errorMessage.find("Cannot create mutable reference") != std::string::npos) {
        return "Mutable references require exclusive access. Ensure no other references exist to the same value.";
    } else if (errorMessage.find("Multiple mutable references") != std::string::npos) {
        return "Only one mutable reference is allowed per value. Ensure exclusive access.";
    } else if (errorMessage.find("Cannot create immutable reference") != std::string::npos) {
        return "Cannot create an immutable reference while a mutable reference exists. Mutable references are exclusive.";
    } else if (errorMessage.find("would escape its creation scope") != std::string::npos) {
        return "References cannot outlive their creation scope. This would create a dangling reference.";
    } else if (errorMessage.find("Mutable reference cannot escape scope") != std::string::npos) {
        return "Mutable references have stricter lifetime requirements and cannot escape their scope.";
    } else if (errorMessage.find("Use before initialization") != std::string::npos) {
        return "The variable is used before being initialized. Assign a value before use.";
    } else if (errorMessage.find("Uninitialized use") != std::string::npos) {
        return "The variable is used before initialization. Ensure all variables are initialized before use.";
    } else if (errorMessage.find("Invalid type") != std::string::npos) {
        return "Type mismatch detected. Ensure the value type matches the expected type.";
    } else if (errorMessage.find("Misalignment") != std::string::npos) {
        return "Pointer alignment issue detected. Ensure proper alignment in memory allocation.";
    } else if (errorMessage.find("Heap corruption") != std::string::npos) {
        return "Heap corruption detected. Check memory operations and bounds.";
    } else if (errorMessage.find("Multiple owners") != std::string::npos) {
        return "Multiple ownership detected. Ensure single ownership of values.";
    }
    
    // === RUNTIME ERRORS ===
    else if (errorMessage.find("Division by zero") != std::string::npos) {
        return "Cannot divide by zero. Ensure the divisor is not zero before performing division.";
    } else if (errorMessage.find("Modulo by zero") != std::string::npos) {
        return "Cannot perform modulo with zero. Ensure the divisor is not zero.";
    }
    
    // === FALLBACK ===
    else if (errorMessage.find("Variable/function not found") != std::string::npos) {
        return "Check the spelling of the variable or function name, or make sure it has been declared or defined before use.";
    } else if (errorMessage.find("Invalid factor") != std::string::npos) {
        return "Check the expression to ensure it follows the correct syntax.";
    } else if (errorMessage.find("Unexpected token") != std::string::npos) {
        if (!expectedValue.empty()) {
            return "Expected '" + expectedValue + "'. Ensure the syntax matches the expected pattern.";
        }
        return "Check your code for syntax errors.";
    } else if (errorMessage.find("Expected") != std::string::npos) {
        return "Ensure the correct syntax is followed. " + errorMessage;
    } else {
        return "Check your code for errors.";
    }
}

std::string Debugger::stageToString(InterpretationStage stage)
{
    switch (stage) {
    case InterpretationStage::SCANNING:
        return "Lexical Error";
    case InterpretationStage::PARSING:
        return "Syntax Error";
    case InterpretationStage::SYNTAX:
        return "Syntax Parsing";
    case InterpretationStage::SEMANTIC:
        return "Semantic Parsing";
    case InterpretationStage::MEMORY:
        return "Memory Safety";
    case InterpretationStage::BYTECODE:
        return "Bytecode Generation";
    case InterpretationStage::INTERPRETING:
        return "Interpreting";
    case InterpretationStage::COMPILING:
        return "Compiling";
    default:
        return "Unknown stage";
    }
}

Message Debugger::createEnhancedErrorMessage(
    const std::string &errorMessage,
    int line,
    int column,
    InterpretationStage stage,
    const std::string &code,
    const std::string &filePath,
    const std::string &lexeme,
    const std::string &expectedValue,
    const std::optional<BlockContext> &blockContext)
{
    // Create error code based on stage
    std::string errorCode = "E";
    switch (stage) {
    case InterpretationStage::SCANNING:
        errorCode += "001";
        break;
    case InterpretationStage::PARSING:
        errorCode += "002";
        break;
    case InterpretationStage::SEMANTIC:
        errorCode += "003";
        break;
    case InterpretationStage::BYTECODE:
        errorCode += "004";
        break;
    case InterpretationStage::INTERPRETING:
        errorCode += "005";
        break;
    default:
        errorCode += "000";
    }

    // Create error type based on stage
    std::string errorType = stageToString(stage);

    // Create error message
    Message msg(errorCode, errorType, errorMessage, filePath, line, column, lexeme, stage);
    
    // Add suggestion
    msg.suggestion = getSuggestion(errorMessage, expectedValue);
    
    // Add block context if available
    if (blockContext.has_value()) {
        msg.causedBy = "Unclosed " + blockContext->blockType + " block starting at line " + 
                      std::to_string(blockContext->startLine);
    }

    // Split source code into lines for context
    sourceCodeLines = splitLines(code);
    if (line > 0 && line <= int(sourceCodeLines.size())) {
        // Add context lines
        if (line > 1) {
            msg.contextLines.push_back(sourceCodeLines[line - 2]);
        }
        msg.contextLines.push_back(sourceCodeLines[line - 1]);
        if (line < int(sourceCodeLines.size())) {
            msg.contextLines.push_back(sourceCodeLines[line]);
        }
    }

    return msg;
}

std::string Debugger::stageToErrorCode(InterpretationStage stage) {
    switch (stage) {
        case InterpretationStage::SCANNING: return "E001";
        case InterpretationStage::PARSING: return "E100";
        case InterpretationStage::SYNTAX: return "E100";
        case InterpretationStage::SEMANTIC: return "E200";
        case InterpretationStage::MEMORY: return "E250";
        case InterpretationStage::BYTECODE: return "E300";
        case InterpretationStage::INTERPRETING: return "E400";
        case InterpretationStage::COMPILING: return "E500";
        default: return "E999";
    }
}

void Debugger::collectDiagnostic(const std::string &code, const std::string &severity,
                                 const std::string &message, const std::string &filePath,
                                 int line, int column, const std::string &sourceSnippet,
                                 const std::string &hint) {
    Diagnostic diag;
    diag.code = code;
    diag.severity = severity;
    diag.message = message;
    diag.filePath = filePath;
    diag.line = line;
    diag.column = column;
    diag.sourceSnippet = sourceSnippet;
    diag.hint = hint;
    
    collectedDiagnostics.push_back(diag);
    
    if (severity == "error") {
        errorCount++;
    } else if (severity == "warning") {
        warningCount++;
    }
}

std::string Debugger::createCaretLine(int column) {
    std::string line;
    for (int i = 1; i < column; ++i) {
        line += " ";
    }
    line += "^";
    return line;
}

void Debugger::printModernDiagnostic(const Diagnostic &diag, bool useColor) {
    std::string reset = useColor ? "\033[0m" : "";
    std::string bold = useColor ? "\033[1m" : "";
    std::string red = useColor ? "\033[1;31m" : "";      // Bold red for errors
    std::string yellow = useColor ? "\033[1;33m" : "";   // Bold yellow for warnings
    std::string cyan = useColor ? "\033[1;36m" : "";     // Bold cyan for notes
    
    std::string severityColor = (diag.severity == "error") ? red : 
                                (diag.severity == "warning") ? yellow : cyan;
    
    // Format: error[E001]: message
    std::cerr << severityColor << bold << diag.severity;
    if (!diag.code.empty()) {
        std::cerr << "[" << diag.code << "]";
    }
    std::cerr << ": " << diag.message << reset << "\n";
    
    // Location: file:line:column
    std::cerr << "  " << bold << "-->" << reset << " " << diag.filePath << ":"
              << diag.line << ":" << diag.column << "\n";
    
    // Source snippet with line number
    if (!diag.sourceSnippet.empty()) {
        std::cerr << "   " << std::setw(4) << diag.line << " | " << diag.sourceSnippet << "\n";
        std::cerr << "       | " << createCaretLine(diag.column) << "\n";
    }
    
    // Hint/suggestion
    if (!diag.hint.empty()) {
        std::cerr << "   " << bold << "help:" << reset << " " << diag.hint << "\n";
    }
    
    std::cerr << "\n";
}

} // namespace Error
} // namespace LM

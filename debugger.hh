#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <string>

enum class InterpretationStage {
    SCANNING,
    PARSING,
    COMPILATION,
    EXECUTION
};

class Debugger {
public:
    static void error(const std::string& message, int line, int position, InterpretationStage stage, const std::string& lexeme = "");
    static void warning(const std::string& message, int line, int position, InterpretationStage stage, const std::string& lexeme = "");
    static void info(const std::string& message);
};

#endif // DEBUGGER_H
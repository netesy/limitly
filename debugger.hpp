// debugger.h
#pragma once

#include <iostream>
#include <stdexcept>
#include <sstream>

enum class InterpretationStage { SCANNING, PARSING, SYNTAX, SEMANTIC, INTERPRETING };

class Debugger {
public:
    static void debugInfo(const std::string &errorMessage,
                          int lineNumber,
                          int position,
                          InterpretationStage stage,
                          const std::string &expectedValue = "");

    static void error(const std::string &errorMessage,
                      int lineNumber,
                      int position,
                      InterpretationStage stage,
                      const std::string &token = "",
                      const std::string &expectedValue = "");

private:
    static std::string getSuggestion(const std::string& errorMessage);
    static std::string stageToString(InterpretationStage stage);
};

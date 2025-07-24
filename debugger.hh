// debugger.h
#pragma once

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

enum class InterpretationStage { SCANNING, PARSING, SYNTAX, SEMANTIC, INTERPRETING, COMPILING };

class Debugger
{
public:
    // Method for reporting errors with source code
    static void error(const std::string &errorMessage,
                      int line,
                      int column,
                      InterpretationStage stage,
                      const std::string &code,
                      const std::string &lexeme = "",
                      const std::string &expectedValue = "");

private:
    static std::vector<std::string> sourceCodez;
    static bool hadError;

    static void debugConsole(const std::string &errorMessage,
                             int line,
                             int column,
                             InterpretationStage stage,
                             const std::string &lexeme,
                             const std::string &expectedValue);
    static void debugLog(const std::string &errorMessage,
                         int line,
                         int column,
                         InterpretationStage stage,
                         const std::string &lexeme,
                         const std::string &expectedValue);
    static void printContextLines(std::ostream &out, int errorLine, int errorColumn);
    static std::vector<std::string> splitLines(const std::string &sourceCode);
    static std::string getTime();
    static std::string getSuggestion(const std::string &errorMessage,
                                     const std::string &expectedValue);
    static std::string getSampleSolution(const std::string &errorMessage,
                                         const std::string &expectedValue);
    static std::string stageToString(InterpretationStage stage);
};
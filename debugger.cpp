#include "debugger.hh"
#include <iostream>

void Debugger::error(const std::string& message, int line, int position, InterpretationStage stage, const std::string& lexeme) {
    std::string stageStr;
    
    switch (stage) {
        case InterpretationStage::SCANNING:
            stageStr = "Scanning";
            break;
        case InterpretationStage::PARSING:
            stageStr = "Parsing";
            break;
        case InterpretationStage::COMPILATION:
            stageStr = "Compilation";
            break;
        case InterpretationStage::EXECUTION:
            stageStr = "Execution";
            break;
    }
    
    std::cerr << "[ERROR] " << stageStr << " error";
    
    if (line > 0) {
        std::cerr << " at line " << line;
        
        if (position > 0) {
            std::cerr << ", position " << position;
        }
    }
    
    std::cerr << ": " << message;
    
    if (!lexeme.empty()) {
        std::cerr << " '" << lexeme << "'";
    }
    
    std::cerr << std::endl;
}

void Debugger::warning(const std::string& message, int line, int position, InterpretationStage stage, const std::string& lexeme) {
    std::string stageStr;
    
    switch (stage) {
        case InterpretationStage::SCANNING:
            stageStr = "Scanning";
            break;
        case InterpretationStage::PARSING:
            stageStr = "Parsing";
            break;
        case InterpretationStage::COMPILATION:
            stageStr = "Compilation";
            break;
        case InterpretationStage::EXECUTION:
            stageStr = "Execution";
            break;
    }
    
    std::cerr << "[WARNING] " << stageStr << " warning";
    
    if (line > 0) {
        std::cerr << " at line " << line;
        
        if (position > 0) {
            std::cerr << ", position " << position;
        }
    }
    
    std::cerr << ": " << message;
    
    if (!lexeme.empty()) {
        std::cerr << " '" << lexeme << "'";
    }
    
    std::cerr << std::endl;
}

void Debugger::info(const std::string& message) {
    std::cout << "[INFO] " << message << std::endl;
}
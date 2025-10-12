#include "src/frontend/scanner.hh"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

// Simple trivia analysis without complex dependencies
class TriviaAnalyzer {
public:
    struct Analysis {
        size_t totalTokens = 0;
        size_t triviaTokens = 0;
        size_t significantTokens = 0;
        size_t totalMemory = 0;
        double triviaRatio = 0.0;
    };
    
    static Analysis analyzeFile(const std::string& filename) {
        Analysis result;
        
        try {
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Could not open file: " << filename << "\n";
                return result;
            }
            
            std::string source((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
            
            Scanner scanner(source, filename);
            auto tokens = scanner.scanTokens();
            
            result.totalTokens = tokens.size();
            
            for (const auto& token : tokens) {
                result.totalMemory += sizeof(token) + token.lexeme.size();
                
                if (token.type == TokenType::WHITESPACE || 
                    token.type == TokenType::NEWLINE ||
                    token.type == TokenType::COMMENT_LINE ||
                    token.type == TokenType::COMMENT_BLOCK) {
                    result.triviaTokens++;
                } else {
                    result.significantTokens++;
                }
            }
            
            if (result.totalTokens > 0) {
                result.triviaRatio = static_cast<double>(result.triviaTokens) / 
                                   static_cast<double>(result.totalTokens);
            }
            
        } catch (const std::exception& e) {
            std::cerr << "Error analyzing file: " << e.what() << "\n";
        }
        
        return result;
    }
    
    static void printAnalysis(const Analysis& analysis, const std::string& filename) {
        std::cout << "Trivia Analysis for: " << filename << "\n";
        std::cout << "  Total Tokens: " << analysis.totalTokens << "\n";
        std::cout << "  Significant Tokens: " << analysis.significantTokens << "\n";
        std::cout << "  Trivia Tokens: " << analysis.triviaTokens << "\n";
        std::cout << "  Trivia Ratio: " << (analysis.triviaRatio * 100.0) << "%\n";
        std::cout << "  Total Memory: " << (analysis.totalMemory / 1024.0) << " KB\n";
        
        if (analysis.triviaRatio > 0.3) {
            std::cout << "  Recommendation: High trivia ratio - consider optimization\n";
        } else {
            std::cout << "  Recommendation: Trivia ratio is acceptable\n";
        }
        std::cout << "\n";
    }
};

int main(int argc, char* argv[]) {
    std::cout << "Trivia Analyzer - Memory Optimization Tool\n";
    std::cout << "==========================================\n\n";
    
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <file1.lm> [file2.lm] ...\n";
        std::cout << "Analyzes trivia (whitespace, comments) in Limit source files\n";
        return 1;
    }
    
    for (int i = 1; i < argc; ++i) {
        auto analysis = TriviaAnalyzer::analyzeFile(argv[i]);
        TriviaAnalyzer::printAnalysis(analysis, argv[i]);
    }
    
    return 0;
}
#include "src/frontend/scanner.hh"
#include "src/frontend/parser.hh"
#include "src/frontend/parser.hh"
#include <iostream>
#include <fstream>
#include <chrono>

class ParserComparison {
public:
    struct Result {
        std::string parserName;
        double parseTimeMs = 0.0;
        bool success = false;
        std::string error;
    };
    
    static Result testParser(const std::string& source, const std::string& parserType) {
        Result result;
        result.parserName = parserType;
        
        try {
            auto start = std::chrono::high_resolution_clock::now();
            
            if (parserType == "Legacy") {
                Scanner scanner(source);
                auto tokens = scanner.scanTokens();
                Parser parser(scanner);
                auto ast = parser.parse();
                result.success = (ast != nullptr);
            } else if (parserType == "CST") {
                Scanner scanner(source);
                auto tokens = scanner.scanTokens();
                Parser cstParser(scanner, true);
                auto ast = cstParser.parse();
                result.success = (ast != nullptr);
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            result.parseTimeMs = duration.count() / 1000.0;
            
        } catch (const std::exception& e) {
            result.error = e.what();
            result.success = false;
        }
        
        return result;
    }
    
    static void compareFile(const std::string& filename) {
        std::cout << "Comparing parsers on: " << filename << "\n";
        std::cout << "----------------------------------------\n";
        
        try {
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Could not open file: " << filename << "\n";
                return;
            }
            
            std::string source((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
            
            std::cout << "Source size: " << source.size() << " bytes\n\n";
            
            // Test Legacy Parser
            auto legacyResult = testParser(source, "Legacy");
            std::cout << "Legacy Parser:\n";
            std::cout << "  Parse Time: " << legacyResult.parseTimeMs << " ms\n";
            std::cout << "  Success: " << (legacyResult.success ? "Yes" : "No") << "\n";
            if (!legacyResult.error.empty()) {
                std::cout << "  Error: " << legacyResult.error << "\n";
            }
            std::cout << "\n";
            
            // Test CST Parser
            auto cstResult = testParser(source, "CST");
            std::cout << "CST Parser:\n";
            std::cout << "  Parse Time: " << cstResult.parseTimeMs << " ms\n";
            std::cout << "  Success: " << (cstResult.success ? "Yes" : "No") << "\n";
            if (!cstResult.error.empty()) {
                std::cout << "  Error: " << cstResult.error << "\n";
            }
            std::cout << "\n";
            
            // Calculate ratio
            if (legacyResult.success && cstResult.success && legacyResult.parseTimeMs > 0) {
                double ratio = cstResult.parseTimeMs / legacyResult.parseTimeMs;
                std::cout << "Performance Ratio (CST/Legacy): " << ratio << "x\n";
                
                if (ratio <= 2.0) {
                    std::cout << "✓ CST parser meets performance requirements (≤2x)\n";
                } else {
                    std::cout << "✗ CST parser exceeds performance requirements (>2x)\n";
                }
            }
            
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
        
        std::cout << "\n";
    }
};

int main(int argc, char* argv[]) {
    std::cout << "Parser Performance Comparison Tool\n";
    std::cout << "==================================\n\n";
    
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <file1.lm> [file2.lm] ...\n";
        std::cout << "Compares Legacy Parser vs CST Parser performance\n";
        return 1;
    }
    
    for (int i = 1; i < argc; ++i) {
        ParserComparison::compareFile(argv[i]);
    }
    
    return 0;
}
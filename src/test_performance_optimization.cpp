#include "frontend/scanner.hh"
#include "frontend/parser_benchmark.hh"
#include "frontend/trivia_optimizer.hh"
#include <iostream>
#include <fstream>
#include <sstream>

// Test data generator
std::string generateTestCode(size_t complexity) {
    std::ostringstream code;
    
    // Add file header comment
    code << "// Generated test file for performance testing\n";
    code << "// Complexity level: " << complexity << "\n\n";
    
    // Generate variable declarations with comments
    for (size_t i = 0; i < complexity; ++i) {
        code << "// Variable " << i << " declaration\n";
        code << "var x" << i << ": int = " << (i * 42) << ";  // Initialize to " << (i * 42) << "\n\n";
    }
    
    // Generate function with complex body
    code << "// Main computation function\n";
    code << "fn compute(): int {\n";
    code << "    var result: int = 0;\n\n";
    
    // Generate loop with nested operations
    for (size_t i = 0; i < complexity / 2; ++i) {
        code << "    // Loop iteration " << i << "\n";
        code << "    for (var j: int = 0; j < 10; j++) {\n";
        code << "        result = result + x" << i << " * j;  // Accumulate\n";
        code << "        if (result > 1000) {\n";
        code << "            result = result / 2;  // Prevent overflow\n";
        code << "        }\n";
        code << "    }\n\n";
    }
    
    code << "    return result;\n";
    code << "}\n\n";
    
    // Generate string interpolation examples
    code << "// String interpolation tests\n";
    for (size_t i = 0; i < complexity / 4; ++i) {
        code << "var msg" << i << ": str = \"Result {x" << i << "} is {x" << i << " * 2}\";\n";
    }
    
    return code.str();
}

void testTriviaOptimization() {
    std::cout << "=== Trivia Optimization Tests ===\n\n";
    
    // Generate test code with lots of trivia
    std::string testCode = generateTestCode(50);
    
    // Scan with trivia collection
    Scanner scanner(testCode);
    CSTConfig config;
    config.preserveWhitespace = true;
    config.preserveComments = true;
    config.attachTrivia = true;
    
    auto tokens = scanner.scanAllTokens(config);
    
    std::cout << "Original tokens: " << tokens.size() << "\n";
    
    // Analyze original memory usage
    auto originalAnalysis = TriviaOptimizer::MemoryAnalyzer::analyzeTokenMemory(tokens);
    std::cout << "\nOriginal Memory Usage:\n" << originalAnalysis.toString() << "\n";
    
    // Convert to optimized tokens
    std::vector<TriviaOptimizer::OptimizedToken> optimizedTokens;
    optimizedTokens.reserve(tokens.size());
    
    for (const auto& token : tokens) {
        optimizedTokens.emplace_back(token);
    }
    
    // Analyze optimized memory usage
    auto optimizedAnalysis = TriviaOptimizer::MemoryAnalyzer::analyzeOptimizedTokenMemory(optimizedTokens);
    std::cout << "Optimized Memory Usage:\n" << optimizedAnalysis.toString() << "\n";
    
    // Calculate savings
    double memorySavings = 1.0 - (static_cast<double>(optimizedAnalysis.totalMemory) / 
                                 static_cast<double>(originalAnalysis.totalMemory));
    
    std::cout << "Memory Savings: " << (memorySavings * 100.0) << "%\n";
    
    // Test trivia pool statistics
    auto& pool = TriviaOptimizer::TriviaPool::getInstance();
    std::cout << "Trivia Pool Statistics:\n";
    std::cout << "  Stored Sequences: " << pool.getStoredSequences() << "\n";
    std::cout << "  Pool Memory Usage: " << (pool.getMemoryUsage() / 1024.0) << " KB\n";
    
    // Get optimization recommendations
    auto recommendations = TriviaOptimizer::getOptimizationRecommendations(originalAnalysis);
    std::cout << "\nOptimization Recommendations:\n";
    for (const auto& rec : recommendations) {
        std::cout << "  - " << rec << "\n";
    }
    
    // Test trivia compression
    std::cout << "\n=== Trivia Compression Tests ===\n";
    
    // Create test trivia with redundant whitespace and newlines
    std::vector<Token> testTrivia = {
        Token(TokenType::WHITESPACE, "  ", 1, 0, 2),
        Token(TokenType::WHITESPACE, "    ", 1, 2, 6),
        Token(TokenType::NEWLINE, "\n", 1, 6, 7),
        Token(TokenType::NEWLINE, "\n", 2, 0, 1),
        Token(TokenType::COMMENT_LINE, "// Comment", 3, 0, 10),
        Token(TokenType::NEWLINE, "\n", 3, 10, 11),
        Token(TokenType::WHITESPACE, " ", 4, 0, 1)
    };
    
    std::cout << "Original trivia tokens: " << testTrivia.size() << "\n";
    
    auto compressedTrivia = TriviaOptimizer::TriviaCompressor::optimizeTrivia(testTrivia);
    std::cout << "Compressed trivia tokens: " << compressedTrivia.size() << "\n";
    
    std::cout << "Compression ratio: " << (1.0 - static_cast<double>(compressedTrivia.size()) / 
                                                static_cast<double>(testTrivia.size())) * 100.0 << "%\n";
}

void testParserPerformance() {
    std::cout << "\n=== Parser Performance Tests ===\n\n";
    
    ParserBenchmark::BenchmarkRunner runner;
    
    // Test with different complexity levels
    std::vector<size_t> complexityLevels = {10, 25, 50, 100};
    
    for (size_t complexity : complexityLevels) {
        std::cout << "Testing complexity level: " << complexity << "\n";
        std::cout << "----------------------------------------\n";
        
        std::string testCode = generateTestCode(complexity);
        std::string filename = "generated_test_" + std::to_string(complexity) + ".lm";
        
        auto comparison = runner.compareParserPerformance(testCode, filename);
        std::cout << comparison.toString() << "\n";
    }
}

void testMemoryScaling() {
    std::cout << "\n=== Memory Scaling Tests ===\n\n";
    
    std::vector<size_t> fileSizes = {1024, 4096, 16384, 65536}; // 1KB, 4KB, 16KB, 64KB
    
    for (size_t targetSize : fileSizes) {
        // Generate code to approximately match target size
        size_t complexity = targetSize / 100; // Rough estimate
        std::string testCode = generateTestCode(complexity);
        
        // Trim or extend to match target size
        if (testCode.size() > targetSize) {
            testCode = testCode.substr(0, targetSize);
        } else {
            while (testCode.size() < targetSize) {
                testCode += " // Padding comment\n";
            }
        }
        
        std::cout << "Testing file size: " << (testCode.size() / 1024.0) << " KB\n";
        std::cout << "----------------------------------------\n";
        
        ParserBenchmark::BenchmarkRunner runner;
        auto comparison = runner.compareParserPerformance(testCode, "size_test_" + std::to_string(targetSize));
        
        std::cout << "Parse Time Ratio: " << comparison.parseTimeRatio << "x\n";
        std::cout << "Memory Usage Ratio: " << comparison.memoryUsageRatio << "x\n";
        std::cout << "Meets Requirements: " << (comparison.meetsPerformanceRequirements ? "Yes" : "No") << "\n\n";
    }
}

int main() {
    std::cout << "Parser Performance and Memory Optimization Tests\n";
    std::cout << "================================================\n\n";
    
    try {
        // Test trivia optimization
        testTriviaOptimization();
        
        // Test parser performance comparison
        testParserPerformance();
        
        // Test memory scaling
        testMemoryScaling();
        
        std::cout << "\n=== Test Summary ===\n";
        std::cout << "All performance optimization tests completed successfully.\n";
        std::cout << "Check the output above for detailed performance metrics and recommendations.\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error during testing: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
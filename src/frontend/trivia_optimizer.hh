#ifndef TRIVIA_OPTIMIZER_HH
#define TRIVIA_OPTIMIZER_HH

#include <unordered_map>
#include <memory>
#include <sstream>
#include "scanner.hh"  // For Token and TokenType definitions

namespace TriviaOptimizer {

    // Handle type for referencing trivia sequences
    using TriviaHandle = uint32_t;
    constexpr TriviaHandle EMPTY_TRIVIA_HANDLE = 0;

    // Trivia pool for deduplicating and sharing common trivia sequences
    class TriviaPool {
    public:
        static TriviaPool& getInstance();
        
        // Store a trivia sequence and return a handle
        TriviaHandle storeTriviaSequence(const std::vector<Token>& trivia);
        
        // Retrieve a trivia sequence by handle
        std::vector<Token> getTriviaSequence(TriviaHandle handle) const;
        
        // Clear all stored trivia (for testing/cleanup)
        void clear();
        
        // Memory usage statistics
        size_t getMemoryUsage() const;
        size_t getStoredSequences() const;
        
    private:
        TriviaPool() = default;
        
        std::unordered_map<TriviaHandle, std::vector<Token>> triviaStorage;
        std::unordered_map<std::string, TriviaHandle> triviaMap; // For deduplication
        TriviaHandle nextHandle = 1;
        
        std::string createTriviaKey(const std::vector<Token>& trivia) const;
    };

    // Optimized token that uses handles for trivia storage
    class OptimizedToken {
    public:
        TokenType type;
        std::string lexeme;
        size_t line;
        size_t start;
        size_t end;
        
        // Constructor from regular token
        explicit OptimizedToken(const Token& original);
        
        // Default constructor
        OptimizedToken() : type(TokenType::UNDEFINED), line(0), start(0), end(0), 
                          leadingTriviaHandle(EMPTY_TRIVIA_HANDLE), 
                          trailingTriviaHandle(EMPTY_TRIVIA_HANDLE) {}
        
        // Trivia access (reconstructed from pool)
        std::vector<Token> getLeadingTrivia() const;
        std::vector<Token> getTrailingTrivia() const;
        
        // Convert back to regular token
        Token toToken() const;
        
        // Memory footprint calculation
        size_t getMemoryFootprint() const;
        
    private:
        TriviaHandle leadingTriviaHandle;
        TriviaHandle trailingTriviaHandle;
    };

    // Trivia compression utilities
    class TriviaCompressor {
    public:
        // Compress consecutive whitespace tokens into single tokens
        static std::vector<Token> compressWhitespace(const std::vector<Token>& trivia);
        
        // Remove redundant consecutive newlines
        static std::vector<Token> removeRedundantNewlines(const std::vector<Token>& trivia);
        
        // Apply all optimization techniques
        static std::vector<Token> optimizeTrivia(const std::vector<Token>& trivia);
    };

    // Memory analysis for trivia usage
    struct MemoryAnalysis {
        size_t totalTokens = 0;
        size_t baseTokenMemory = 0;        // Memory for tokens without trivia
        size_t leadingTriviaMemory = 0;    // Memory for leading trivia
        size_t trailingTriviaMemory = 0;   // Memory for trailing trivia
        size_t totalMemory = 0;            // Total memory usage
        size_t leadingTriviaCount = 0;     // Number of leading trivia tokens
        size_t trailingTriviaCount = 0;    // Number of trailing trivia tokens
        double triviaMemoryRatio = 0.0;    // Ratio of trivia memory to total memory
        
        std::string toString() const;
    };

    // Memory analyzer for comparing different trivia storage approaches
    class MemoryAnalyzer {
    public:
        // Analyze memory usage of regular tokens with trivia
        static MemoryAnalysis analyzeTokenMemory(const std::vector<Token>& tokens);
        
        // Analyze memory usage of optimized tokens
        static MemoryAnalysis analyzeOptimizedTokenMemory(const std::vector<OptimizedToken>& tokens);
    };

    // Utility functions
    std::vector<std::string> getOptimizationRecommendations(const MemoryAnalysis& analysis);

} // namespace TriviaOptimizer

#endif // TRIVIA_OPTIMIZER_HH
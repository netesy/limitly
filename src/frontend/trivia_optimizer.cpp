#include "trivia_optimizer.hh"
#include <algorithm>
#include <unordered_set>
#include <iomanip>

namespace TriviaOptimizer {

    // Optimized trivia storage implementation
    TriviaPool& TriviaPool::getInstance() {
        static TriviaPool instance;
        return instance;
    }

    TriviaHandle TriviaPool::storeTriviaSequence(const std::vector<Token>& trivia) {
        if (trivia.empty()) {
            return EMPTY_TRIVIA_HANDLE;
        }
        
        // Create a key for this trivia sequence
        std::string key = createTriviaKey(trivia);
        
        // Check if we already have this sequence
        auto it = triviaMap.find(key);
        if (it != triviaMap.end()) {
            // Reuse existing trivia sequence
            return it->second;
        }
        
        // Store new trivia sequence
        TriviaHandle handle = nextHandle++;
        triviaStorage[handle] = trivia;
        triviaMap[key] = handle;
        
        return handle;
    }

    std::vector<Token> TriviaPool::getTriviaSequence(TriviaHandle handle) const {
        if (handle == EMPTY_TRIVIA_HANDLE) {
            return {};
        }
        
        auto it = triviaStorage.find(handle);
        if (it != triviaStorage.end()) {
            return it->second;
        }
        
        return {}; // Handle not found
    }

    void TriviaPool::clear() {
        triviaStorage.clear();
        triviaMap.clear();
        nextHandle = 1;
    }

    size_t TriviaPool::getMemoryUsage() const {
        size_t totalSize = 0;
        
        // Calculate storage size
        for (const auto& pair : triviaStorage) {
            totalSize += sizeof(pair.first); // Handle
            for (const auto& token : pair.second) {
                totalSize += sizeof(token) + token.lexeme.size();
            }
        }
        
        // Calculate map overhead
        totalSize += triviaMap.size() * (sizeof(std::string) + sizeof(TriviaHandle));
        for (const auto& pair : triviaMap) {
            totalSize += pair.first.size();
        }
        
        return totalSize;
    }

    size_t TriviaPool::getStoredSequences() const {
        return triviaStorage.size();
    }

    std::string TriviaPool::createTriviaKey(const std::vector<Token>& trivia) const {
        std::string key;
        key.reserve(trivia.size() * 10); // Rough estimate
        
        for (const auto& token : trivia) {
            key += std::to_string(static_cast<int>(token.type));
            key += ":";
            key += token.lexeme;
            key += ";";
        }
        
        return key;
    }

    // Optimized token implementation
    OptimizedToken::OptimizedToken(const Token& original) 
        : type(original.type), lexeme(original.lexeme), line(original.line), 
          start(original.start), end(original.end) {
        
        // Store trivia using the pool
        auto& pool = TriviaPool::getInstance();
        leadingTriviaHandle = pool.storeTriviaSequence(original.getLeadingTrivia());
        trailingTriviaHandle = pool.storeTriviaSequence(original.getTrailingTrivia());
    }

    std::vector<Token> OptimizedToken::getLeadingTrivia() const {
        return TriviaPool::getInstance().getTriviaSequence(leadingTriviaHandle);
    }

    std::vector<Token> OptimizedToken::getTrailingTrivia() const {
        return TriviaPool::getInstance().getTriviaSequence(trailingTriviaHandle);
    }

    Token OptimizedToken::toToken() const {
        Token token(type, lexeme, line, start, end);
        
        // Restore trivia from pool
        auto leading = getLeadingTrivia();
        auto trailing = getTrailingTrivia();
        
        token.leadingTrivia = leading;
        token.trailingTrivia = trailing;
        
        return token;
    }

    size_t OptimizedToken::getMemoryFootprint() const {
        return sizeof(*this) + lexeme.size();
    }

    // Trivia compressor implementation
    std::vector<Token> TriviaCompressor::compressWhitespace(const std::vector<Token>& trivia) {
        std::vector<Token> compressed;
        compressed.reserve(trivia.size());
        
        Token* currentWhitespace = nullptr;
        
        for (const auto& token : trivia) {
            if (token.type == TokenType::WHITESPACE) {
                if (currentWhitespace) {
                    // Merge with previous whitespace
                    currentWhitespace->lexeme += token.lexeme;
                    currentWhitespace->end = token.end;
                } else {
                    // Start new whitespace token
                    compressed.push_back(token);
                    currentWhitespace = &compressed.back();
                }
            } else {
                // Non-whitespace token, reset whitespace merging
                currentWhitespace = nullptr;
                compressed.push_back(token);
            }
        }
        
        return compressed;
    }

    std::vector<Token> TriviaCompressor::removeRedundantNewlines(const std::vector<Token>& trivia) {
        std::vector<Token> filtered;
        filtered.reserve(trivia.size());
        
        bool lastWasNewline = false;
        
        for (const auto& token : trivia) {
            if (token.type == TokenType::NEWLINE) {
                if (!lastWasNewline) {
                    filtered.push_back(token);
                    lastWasNewline = true;
                }
                // Skip redundant newlines
            } else {
                filtered.push_back(token);
                lastWasNewline = false;
            }
        }
        
        return filtered;
    }

    std::vector<Token> TriviaCompressor::optimizeTrivia(const std::vector<Token>& trivia) {
        if (trivia.empty()) {
            return trivia;
        }
        
        // Apply compression techniques
        auto compressed = compressWhitespace(trivia);
        compressed = removeRedundantNewlines(compressed);
        
        return compressed;
    }

    // Memory analyzer implementation
    MemoryAnalysis MemoryAnalyzer::analyzeTokenMemory(const std::vector<Token>& tokens) {
        MemoryAnalysis analysis;
        analysis.totalTokens = tokens.size();
        
        for (const auto& token : tokens) {
            // Base token size
            size_t tokenSize = sizeof(token) + token.lexeme.size();
            analysis.baseTokenMemory += tokenSize;
            
            // Leading trivia
            for (const auto& trivia : token.getLeadingTrivia()) {
                size_t triviaSize = sizeof(trivia) + trivia.lexeme.size();
                analysis.leadingTriviaMemory += triviaSize;
                analysis.leadingTriviaCount++;
            }
            
            // Trailing trivia
            for (const auto& trivia : token.getTrailingTrivia()) {
                size_t triviaSize = sizeof(trivia) + trivia.lexeme.size();
                analysis.trailingTriviaMemory += triviaSize;
                analysis.trailingTriviaCount++;
            }
        }
        
        analysis.totalMemory = analysis.baseTokenMemory + analysis.leadingTriviaMemory + analysis.trailingTriviaMemory;
        
        // Calculate ratios
        if (analysis.totalMemory > 0) {
            analysis.triviaMemoryRatio = static_cast<double>(analysis.leadingTriviaMemory + analysis.trailingTriviaMemory) / 
                                       static_cast<double>(analysis.totalMemory);
        }
        
        return analysis;
    }

    MemoryAnalysis MemoryAnalyzer::analyzeOptimizedTokenMemory(const std::vector<OptimizedToken>& tokens) {
        MemoryAnalysis analysis;
        analysis.totalTokens = tokens.size();
        
        for (const auto& token : tokens) {
            analysis.baseTokenMemory += token.getMemoryFootprint();
        }
        
        // Add trivia pool memory
        auto& pool = TriviaPool::getInstance();
        analysis.leadingTriviaMemory = pool.getMemoryUsage() / 2; // Rough split
        analysis.trailingTriviaMemory = pool.getMemoryUsage() / 2;
        
        analysis.totalMemory = analysis.baseTokenMemory + analysis.leadingTriviaMemory + analysis.trailingTriviaMemory;
        
        if (analysis.totalMemory > 0) {
            analysis.triviaMemoryRatio = static_cast<double>(analysis.leadingTriviaMemory + analysis.trailingTriviaMemory) / 
                                       static_cast<double>(analysis.totalMemory);
        }
        
        return analysis;
    }

    std::string MemoryAnalysis::toString() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        
        oss << "Memory Analysis:\n";
        oss << "  Total Tokens: " << totalTokens << "\n";
        oss << "  Base Token Memory: " << (baseTokenMemory / 1024.0) << " KB\n";
        oss << "  Leading Trivia Memory: " << (leadingTriviaMemory / 1024.0) << " KB (" << leadingTriviaCount << " items)\n";
        oss << "  Trailing Trivia Memory: " << (trailingTriviaMemory / 1024.0) << " KB (" << trailingTriviaCount << " items)\n";
        oss << "  Total Memory: " << (totalMemory / 1024.0) << " KB\n";
        oss << "  Trivia Memory Ratio: " << (triviaMemoryRatio * 100.0) << "%\n";
        
        return oss.str();
    }

    // Optimization recommendations
    std::vector<std::string> getOptimizationRecommendations(const MemoryAnalysis& analysis) {
        std::vector<std::string> recommendations;
        
        if (analysis.triviaMemoryRatio > 0.5) {
            recommendations.push_back("High trivia memory usage (>50%) - consider trivia pooling");
        }
        
        if (analysis.leadingTriviaCount > analysis.totalTokens * 2) {
            recommendations.push_back("High leading trivia count - consider whitespace compression");
        }
        
        if (analysis.trailingTriviaCount > analysis.totalTokens * 2) {
            recommendations.push_back("High trailing trivia count - consider newline deduplication");
        }
        
        if (analysis.totalMemory > 10 * 1024 * 1024) { // 10MB
            recommendations.push_back("Large memory usage - consider lazy trivia loading");
        }
        
        if (recommendations.empty()) {
            recommendations.push_back("Memory usage is within acceptable limits");
        }
        
        return recommendations;
    }

} // namespace TriviaOptimizer
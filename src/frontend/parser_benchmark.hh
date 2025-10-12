#ifndef PARSER_BENCHMARK_HH
#define PARSER_BENCHMARK_HH

#include "scanner.hh"  // Must be first for TokenType definition
#include <string>
#include <vector>
#include <chrono>
#include "ast.hh"

// Forward declarations
class Parser;
class CSTParser;

// Platform-specific includes for memory tracking
#ifdef _WIN32
    #include <windows.h>
    #include <psapi.h>
#elif defined(__linux__)
    #include <unistd.h>
    #include <fstream>
#elif defined(__APPLE__)
    #include <mach/mach.h>
#endif

namespace ParserBenchmark {

    // Structure to hold benchmark results for a single parser
    struct BenchmarkResult {
        std::string parserName;
        std::string filename;
        double parseTimeMs = 0.0;           // Parse time in milliseconds
        size_t memoryUsageBytes = 0;        // Memory used during parsing
        size_t peakMemoryBytes = 0;         // Peak memory usage
        size_t nodesCreated = 0;            // Number of AST/CST nodes created
        size_t tokensProcessed = 0;         // Number of tokens processed
        size_t triviaAttachments = 0;       // Number of trivia attachments (CST only)
        bool success = false;               // Whether parsing succeeded
        std::string errorMessage;           // Error message if parsing failed
        
        std::string toString() const;
    };

    // Structure to hold comparison results between parsers
    struct ComparisonResult {
        std::string filename;
        size_t sourceSize = 0;              // Size of source file in bytes
        BenchmarkResult legacyResult;       // Legacy parser results
        BenchmarkResult cstResult;          // CST parser results
        double parseTimeRatio = 0.0;        // CST time / Legacy time
        double memoryUsageRatio = 0.0;      // CST memory / Legacy memory
        bool meetsPerformanceRequirements = false; // Whether CST parser is within 2x of legacy
        
        std::string toString() const;
    };

    // Main benchmark runner class
    class BenchmarkRunner {
    public:
        // Benchmark individual parsers
        BenchmarkResult benchmarkLegacyParser(const std::string& source, const std::string& filename = "");
        BenchmarkResult benchmarkCSTParser(const std::string& source, const std::string& filename = "");
        
        // Compare both parsers on the same source
        ComparisonResult compareParserPerformance(const std::string& source, const std::string& filename = "");
        
    private:
        // Utility function to count AST nodes
        size_t countASTNodes(AST::Node* node);
    };

    // Benchmark suite for running multiple tests
    class BenchmarkSuite {
    public:
        // Add test files to the suite
        void addTestFile(const std::string& filename);
        
        // Run all benchmarks
        void runAllBenchmarks();
        
        // Print summary of results
        void printSummary();
        
        // Get results
        const std::vector<ComparisonResult>& getResults() const;
        
    private:
        std::vector<std::string> testFiles;
        std::vector<ComparisonResult> results;
        BenchmarkRunner runner;
    };

    // Utility functions
    size_t getCurrentMemoryUsage();

} // namespace ParserBenchmark

#endif // PARSER_BENCHMARK_HH
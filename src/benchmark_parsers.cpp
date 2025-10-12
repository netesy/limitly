#include "frontend/scanner.hh"
#include "frontend/parser_benchmark.hh"
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]) {
    ParserBenchmark::BenchmarkSuite suite;
    
    // Add test files from various directories
    std::vector<std::string> testDirectories = {
        "tests/basic",
        "tests/expressions", 
        "tests/strings",
        "tests/loops",
        "tests/functions",
        "tests/classes",
        "tests/types",
        "tests/modules",
        "tests/error_handling",
        "tests/integration"
    };
    
    // Add individual test files
    std::vector<std::string> specificTests = {
        "tests/comprehensive_language_test.lm",
        "tests/simple_interpolation.lm",
        "test_match_basic.lm",
        "test_match_simple.lm"
    };
    
    // Collect test files from directories
    for (const auto& dir : testDirectories) {
        try {
            if (std::filesystem::exists(dir) && std::filesystem::is_directory(dir)) {
                for (const auto& entry : std::filesystem::directory_iterator(dir)) {
                    if (entry.is_regular_file() && entry.path().extension() == ".lm") {
                        suite.addTestFile(entry.path().string());
                    }
                }
            }
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Warning: Could not access directory " << dir << ": " << e.what() << "\n";
        }
    }
    
    // Add specific test files
    for (const auto& testFile : specificTests) {
        if (std::filesystem::exists(testFile)) {
            suite.addTestFile(testFile);
        }
    }
    
    // If command line arguments provided, use those instead
    if (argc > 1) {
        // Clear default tests and use command line arguments
        ParserBenchmark::BenchmarkSuite customSuite;
        for (int i = 1; i < argc; ++i) {
            if (std::filesystem::exists(argv[i])) {
                customSuite.addTestFile(argv[i]);
            } else {
                std::cerr << "Warning: File not found: " << argv[i] << "\n";
            }
        }
        customSuite.runAllBenchmarks();
    } else {
        // Run default benchmark suite
        suite.runAllBenchmarks();
    }
    
    return 0;
}
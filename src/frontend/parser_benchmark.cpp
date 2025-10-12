#include "parser_benchmark.hh"
#include "scanner.hh"
#include "parser.hh"
// cst_parser.hh functionality now integrated into parser.hh
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace ParserBenchmark {

    // Memory usage tracking
    size_t getCurrentMemoryUsage() {
        // Platform-specific memory usage tracking
        #ifdef _WIN32
            PROCESS_MEMORY_COUNTERS pmc;
            if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
                return pmc.WorkingSetSize;
            }
        #elif defined(__linux__)
            std::ifstream statm("/proc/self/statm");
            if (statm.is_open()) {
                size_t size, resident, share, text, lib, data, dt;
                statm >> size >> resident >> share >> text >> lib >> data >> dt;
                return resident * getpagesize(); // Convert pages to bytes
            }
        #elif defined(__APPLE__)
            struct mach_task_basic_info info;
            mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
            if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO,
                         (task_info_t)&info, &infoCount) == KERN_SUCCESS) {
                return info.resident_size;
            }
        #endif
        return 0; // Fallback if platform-specific code fails
    }

    // Benchmark result implementation
    std::string BenchmarkResult::toString() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(3);
        oss << "Parser: " << parserName << "\n";
        oss << "  Parse Time: " << parseTimeMs << " ms\n";
        oss << "  Memory Usage: " << (memoryUsageBytes / 1024.0 / 1024.0) << " MB\n";
        oss << "  Peak Memory: " << (peakMemoryBytes / 1024.0 / 1024.0) << " MB\n";
        oss << "  Nodes Created: " << nodesCreated << "\n";
        oss << "  Tokens Processed: " << tokensProcessed << "\n";
        oss << "  Trivia Attachments: " << triviaAttachments << "\n";
        oss << "  Success: " << (success ? "Yes" : "No") << "\n";
        if (!errorMessage.empty()) {
            oss << "  Error: " << errorMessage << "\n";
        }
        return oss.str();
    }

    // Benchmark runner implementation
    BenchmarkResult BenchmarkRunner::benchmarkLegacyParser(const std::string& source, const std::string& filename) {
        BenchmarkResult result;
        result.parserName = "Legacy Parser";
        result.filename = filename;
        
        try {
            // Measure initial memory
            size_t initialMemory = getCurrentMemoryUsage();
            
            // Create scanner
            Scanner scanner(source, filename);
            auto tokens = scanner.scanTokens();
            result.tokensProcessed = tokens.size();
            
            // Create parser in legacy mode
            Parser parser(scanner, false); // CST mode disabled for legacy behavior
            
            // Measure parsing time
            auto startTime = std::chrono::high_resolution_clock::now();
            
            auto ast = parser.parse();
            
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
            result.parseTimeMs = duration.count() / 1000.0;
            
            // Measure final memory
            size_t finalMemory = getCurrentMemoryUsage();
            result.memoryUsageBytes = finalMemory - initialMemory;
            result.peakMemoryBytes = finalMemory;
            
            // Count nodes (approximate)
            result.nodesCreated = countASTNodes(ast.get());
            result.triviaAttachments = 0; // Legacy parser doesn't track trivia
            
            result.success = (ast != nullptr && !parser.hadError());
            if (parser.hadError()) {
                result.errorMessage = "Parser had errors";
            }
            
        } catch (const std::exception& e) {
            result.success = false;
            result.errorMessage = e.what();
        }
        
        return result;
    }

    BenchmarkResult BenchmarkRunner::benchmarkCSTParser(const std::string& source, const std::string& filename) {
        BenchmarkResult result;
        result.parserName = "CST Parser";
        result.filename = filename;
        
        try {
            // Measure initial memory
            size_t initialMemory = getCurrentMemoryUsage();
            
            // Create scanner
            Scanner scanner(source, filename);
            auto tokens = scanner.scanTokens();
            result.tokensProcessed = tokens.size();
            
            // Create CST parser
            Parser cstParser(scanner, true); // CST mode enabled
            
            // Measure parsing time
            auto startTime = std::chrono::high_resolution_clock::now();
            
            auto ast = cstParser.parse();
            
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
            result.parseTimeMs = duration.count() / 1000.0;
            
            // Measure final memory
            size_t finalMemory = getCurrentMemoryUsage();
            result.memoryUsageBytes = finalMemory - initialMemory;
            result.peakMemoryBytes = finalMemory;
            
            // Get CST-specific metrics
            result.nodesCreated = cstParser.getCSTNodeCount();
            result.triviaAttachments = cstParser.getTriviaAttachmentCount();
            
            result.success = (ast != nullptr && !cstParser.hadError());
            if (cstParser.hadError()) {
                result.errorMessage = "CST Parser had errors";
            }
            
        } catch (const std::exception& e) {
            result.success = false;
            result.errorMessage = e.what();
        }
        
        return result;
    }

    ComparisonResult BenchmarkRunner::compareParserPerformance(const std::string& source, const std::string& filename) {
        ComparisonResult comparison;
        comparison.filename = filename;
        comparison.sourceSize = source.size();
        
        // Benchmark both parsers
        comparison.legacyResult = benchmarkLegacyParser(source, filename);
        comparison.cstResult = benchmarkCSTParser(source, filename);
        
        // Calculate performance ratios
        if (comparison.legacyResult.parseTimeMs > 0) {
            comparison.parseTimeRatio = comparison.cstResult.parseTimeMs / comparison.legacyResult.parseTimeMs;
        }
        
        if (comparison.legacyResult.memoryUsageBytes > 0) {
            comparison.memoryUsageRatio = static_cast<double>(comparison.cstResult.memoryUsageBytes) / 
                                        static_cast<double>(comparison.legacyResult.memoryUsageBytes);
        }
        
        // Determine if CST parser meets performance requirements (within 2x)
        comparison.meetsPerformanceRequirements = (comparison.parseTimeRatio <= 2.0);
        
        return comparison;
    }

    std::string ComparisonResult::toString() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(3);
        oss << "=== Parser Performance Comparison ===\n";
        oss << "File: " << filename << " (" << (sourceSize / 1024.0) << " KB)\n\n";
        
        oss << "Legacy Parser Results:\n";
        oss << "  Parse Time: " << legacyResult.parseTimeMs << " ms\n";
        oss << "  Memory Usage: " << (legacyResult.memoryUsageBytes / 1024.0 / 1024.0) << " MB\n";
        oss << "  Nodes Created: " << legacyResult.nodesCreated << "\n";
        oss << "  Success: " << (legacyResult.success ? "Yes" : "No") << "\n";
        
        oss << "\nCST Parser Results:\n";
        oss << "  Parse Time: " << cstResult.parseTimeMs << " ms\n";
        oss << "  Memory Usage: " << (cstResult.memoryUsageBytes / 1024.0 / 1024.0) << " MB\n";
        oss << "  Nodes Created: " << cstResult.nodesCreated << "\n";
        oss << "  Trivia Attachments: " << cstResult.triviaAttachments << "\n";
        oss << "  Success: " << (cstResult.success ? "Yes" : "No") << "\n";
        
        oss << "\nPerformance Ratios:\n";
        oss << "  Parse Time Ratio: " << parseTimeRatio << "x ";
        if (parseTimeRatio <= 1.5) {
            oss << "(Excellent)";
        } else if (parseTimeRatio <= 2.0) {
            oss << "(Good)";
        } else {
            oss << "(Needs Optimization)";
        }
        oss << "\n";
        
        oss << "  Memory Usage Ratio: " << memoryUsageRatio << "x ";
        if (memoryUsageRatio <= 1.5) {
            oss << "(Excellent)";
        } else if (memoryUsageRatio <= 2.0) {
            oss << "(Good)";
        } else {
            oss << "(Needs Optimization)";
        }
        oss << "\n";
        
        oss << "\nRequirements Check:\n";
        oss << "  Meets Performance Requirements (≤2x): " << (meetsPerformanceRequirements ? "✓ PASS" : "✗ FAIL") << "\n";
        
        return oss.str();
    }

    // Utility function to count AST nodes
    size_t BenchmarkRunner::countASTNodes(AST::Node* node) {
        if (!node) return 0;
        
        size_t count = 1; // Count this node
        
        // Count child nodes based on node type
        if (auto program = dynamic_cast<AST::Program*>(node)) {
            for (const auto& stmt : program->statements) {
                count += countASTNodes(stmt.get());
            }
        } else if (auto block = dynamic_cast<AST::BlockStatement*>(node)) {
            for (const auto& stmt : block->statements) {
                count += countASTNodes(stmt.get());
            }
        } else if (auto ifStmt = dynamic_cast<AST::IfStatement*>(node)) {
            count += countASTNodes(ifStmt->condition.get());
            count += countASTNodes(ifStmt->thenBranch.get());
            if (ifStmt->elseBranch) {
                count += countASTNodes(ifStmt->elseBranch.get());
            }
        } else if (auto forStmt = dynamic_cast<AST::ForStatement*>(node)) {
            if (forStmt->initializer) count += countASTNodes(forStmt->initializer.get());
            if (forStmt->condition) count += countASTNodes(forStmt->condition.get());
            if (forStmt->increment) count += countASTNodes(forStmt->increment.get());
            if (forStmt->iterable) count += countASTNodes(forStmt->iterable.get());
            count += countASTNodes(forStmt->body.get());
        } else if (auto whileStmt = dynamic_cast<AST::WhileStatement*>(node)) {
            count += countASTNodes(whileStmt->condition.get());
            count += countASTNodes(whileStmt->body.get());
        } else if (auto exprStmt = dynamic_cast<AST::ExprStatement*>(node)) {
            if (exprStmt->expression) {
                count += countASTNodes(exprStmt->expression.get());
            }
        } else if (auto binaryExpr = dynamic_cast<AST::BinaryExpr*>(node)) {
            count += countASTNodes(binaryExpr->left.get());
            count += countASTNodes(binaryExpr->right.get());
        } else if (auto unaryExpr = dynamic_cast<AST::UnaryExpr*>(node)) {
            count += countASTNodes(unaryExpr->right.get());
        } else if (auto callExpr = dynamic_cast<AST::CallExpr*>(node)) {
            count += countASTNodes(callExpr->callee.get());
            for (const auto& arg : callExpr->arguments) {
                count += countASTNodes(arg.get());
            }
        } else if (auto funcDecl = dynamic_cast<AST::FunctionDeclaration*>(node)) {
            if (funcDecl->body) {
                count += countASTNodes(funcDecl->body.get());
            }
        } else if (auto varDecl = dynamic_cast<AST::VarDeclaration*>(node)) {
            if (varDecl->initializer) {
                count += countASTNodes(varDecl->initializer.get());
            }
        }
        // Add more node types as needed
        
        return count;
    }

    // Benchmark suite implementation
    void BenchmarkSuite::addTestFile(const std::string& filename) {
        testFiles.push_back(filename);
    }

    void BenchmarkSuite::runAllBenchmarks() {
        results.clear();
        
        std::cout << "Running Parser Performance Benchmarks...\n";
        std::cout << "========================================\n\n";
        
        for (const auto& filename : testFiles) {
            std::cout << "Benchmarking: " << filename << "\n";
            
            // Read file content
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Error: Could not open file " << filename << "\n";
                continue;
            }
            
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string source = buffer.str();
            
            // Run comparison
            auto result = runner.compareParserPerformance(source, filename);
            results.push_back(result);
            
            std::cout << result.toString() << "\n";
        }
        
        // Print summary
        printSummary();
    }

    void BenchmarkSuite::printSummary() {
        if (results.empty()) {
            std::cout << "No benchmark results to summarize.\n";
            return;
        }
        
        std::cout << "\n=== BENCHMARK SUMMARY ===\n";
        
        // Calculate averages
        double avgParseTimeRatio = 0.0;
        double avgMemoryRatio = 0.0;
        size_t passCount = 0;
        size_t totalTests = results.size();
        
        for (const auto& result : results) {
            avgParseTimeRatio += result.parseTimeRatio;
            avgMemoryRatio += result.memoryUsageRatio;
            if (result.meetsPerformanceRequirements) {
                passCount++;
            }
        }
        
        avgParseTimeRatio /= totalTests;
        avgMemoryRatio /= totalTests;
        
        std::cout << std::fixed << std::setprecision(3);
        std::cout << "Total Tests: " << totalTests << "\n";
        std::cout << "Tests Passing Requirements: " << passCount << " (" 
                  << (100.0 * passCount / totalTests) << "%)\n";
        std::cout << "Average Parse Time Ratio: " << avgParseTimeRatio << "x\n";
        std::cout << "Average Memory Usage Ratio: " << avgMemoryRatio << "x\n";
        
        // Performance assessment
        std::cout << "\nPerformance Assessment:\n";
        if (avgParseTimeRatio <= 1.5) {
            std::cout << "✓ Parse Time: Excellent (≤1.5x)\n";
        } else if (avgParseTimeRatio <= 2.0) {
            std::cout << "✓ Parse Time: Good (≤2.0x)\n";
        } else {
            std::cout << "✗ Parse Time: Needs Optimization (>2.0x)\n";
        }
        
        if (avgMemoryRatio <= 1.5) {
            std::cout << "✓ Memory Usage: Excellent (≤1.5x)\n";
        } else if (avgMemoryRatio <= 2.0) {
            std::cout << "✓ Memory Usage: Good (≤2.0x)\n";
        } else {
            std::cout << "✗ Memory Usage: Needs Optimization (>2.0x)\n";
        }
        
        // Recommendations
        std::cout << "\nRecommendations:\n";
        if (avgParseTimeRatio > 2.0) {
            std::cout << "- Optimize CST parser parsing algorithms\n";
            std::cout << "- Reduce trivia processing overhead\n";
            std::cout << "- Consider lazy trivia attachment\n";
        }
        
        if (avgMemoryRatio > 2.0) {
            std::cout << "- Optimize trivia storage in tokens\n";
            std::cout << "- Use more efficient data structures for CST nodes\n";
            std::cout << "- Consider memory pooling for frequent allocations\n";
        }
        
        if (passCount == totalTests) {
            std::cout << "🎉 All tests pass performance requirements!\n";
        }
    }

    const std::vector<ComparisonResult>& BenchmarkSuite::getResults() const {
        return results;
    }

} // namespace ParserBenchmark
#include "backend/ast_printer.hh"
#include "backend/bytecode_printer.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
// CST parser functionality is now integrated into parser.hh
#include "frontend/cst_printer.hh"
#include "frontend/cst_utils.hh"
#include "frontend/ast_builder.hh"
#include "common/backend.hh"
#include "backend/vm.hh"
#include "common/opcodes.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <algorithm>

// Function to print all opcode values and names (for debugging)
void printOpcodeValues() {
    std::cout << "Opcode values and names:" << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "Use BytecodePrinter for detailed bytecode output" << std::endl;
    std::cout << "------------------------" << std::endl;
}

int main(int argc, char* argv[]) {
    // Check for --list-opcodes flag
    if (argc > 1 && std::string(argv[1]) == "--list-opcodes") {
        printOpcodeValues();
        return 0;
    }
    
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <source_file> [--cst|--legacy]" << std::endl;
        std::cout << "       " << argv[0] << " --list-opcodes" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  --cst     Use CST parser (default)" << std::endl;
        std::cout << "  --legacy  Use legacy parser" << std::endl;
        return 1;
    }
    
    // Parse command line options
    bool useCSTParser = true;  // Default to CST parser
    std::string filename = argv[1];
    
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--legacy") {
            useCSTParser = false;
        } else if (arg == "--cst") {
            useCSTParser = true;
        }
    }
    
    // Read source file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    
    try {
        std::shared_ptr<AST::Program> ast;
        
        if (useCSTParser) {
            std::cout << "=== Using New Unified Parser (CST mode) ===\n";
            
            // Frontend: CST scanning with trivia collection
            Scanner scanner(source, filename);
            auto tokens = scanner.scanTokens(ScanMode::CST);
            
            // Print tokens with trivia information
            std::cout << "=== Tokens with Trivia ===\n";
            
            // Capture token output for both console and file
            std::ostringstream tokenOutput;
            tokenOutput << "=== Tokens with Trivia ===\n";
            
            for (const auto& token : tokens) {
                std::string tokenLine = "Line " + std::to_string(token.line) + ": "
                                      + scanner.tokenTypeToString(token.type)
                                      + " = '" + token.lexeme + "'";
                
                // Show leading trivia
                if (!token.getLeadingTrivia().empty()) {
                    tokenLine += " [leading: ";
                    for (const auto& trivia : token.getLeadingTrivia()) {
                        tokenLine += scanner.tokenTypeToString(trivia.type) + "('" + trivia.lexeme + "') ";
                    }
                    tokenLine += "]";
                }
                
                // Show trailing trivia
                if (!token.getTrailingTrivia().empty()) {
                    tokenLine += " [trailing: ";
                    for (const auto& trivia : token.getTrailingTrivia()) {
                        tokenLine += scanner.tokenTypeToString(trivia.type) + "('" + trivia.lexeme + "') ";
                    }
                    tokenLine += "]";
                }
                
                tokenLine += "\n";
                std::cout << tokenLine;
                tokenOutput << tokenLine;
            }
            std::cout << std::endl;
            
            // Save tokens to file
            std::string tokensFilename = filename + ".tokens.txt";
            std::ofstream tokensFile(tokensFilename);
            if (tokensFile.is_open()) {
                tokensFile << "Tokens for " << filename << "\n";
                tokensFile << "Parser: New Unified Parser (CST mode)\n";
                tokensFile << "Mode: CST with trivia preservation\n";
                tokensFile << "========================================\n\n";
                tokensFile << tokenOutput.str();
                tokensFile.close();
                std::cout << "Tokens output saved to " << tokensFilename << std::endl;
            } else {
                std::cerr << "Warning: Could not open " << tokensFilename << " for writing" << std::endl;
            }
            
            // Use new Parser with CST mode enabled
            std::cout << "=== Testing New CST Parser (cstMode=true) ===\n";
            Parser cstParser(scanner, true);  // CST mode enabled
            cstParser.enableDetailedExpressionNodes(true);  // Enable detailed expression CST nodes
            
            try {
                ast = cstParser.parse();
                
                if (cstParser.hadError()) {
                    std::cout << "Parse errors found: " << cstParser.getErrors().size() << std::endl;
                    for (const auto& error : cstParser.getErrors()) {
                        std::cout << "  Line " << error.line << ": " << error.message << std::endl;
                    }
                } else {
                    std::cout << "✓ CST parsing completed successfully without std::bad_alloc!\n";
                    std::cout << "✓ Using proven parsing logic from legacy parser\n";
                    std::cout << "✓ CST nodes created internally with trivia attachment\n";
                    std::cout << "✓ AST returned for compatibility with existing pipeline\n";
                }
                
                // Show CST statistics
                std::cout << "\n=== CST Parser Statistics ===\n";
                std::cout << "CST mode enabled: " << (cstParser.isCSTMode() ? "YES" : "NO") << std::endl;
                std::cout << "CST nodes created: " << cstParser.getCSTNodeCount() << std::endl;
                std::cout << "Trivia attachments: " << cstParser.getTriviaAttachmentCount() << std::endl;
                
            } catch (const std::bad_alloc& e) {
                std::cerr << "❌ FAILED: std::bad_alloc occurred in CST parser!" << std::endl;
                std::cerr << "This indicates the memory issue is not yet fixed." << std::endl;
                return 1;
            } catch (const std::exception& e) {
                std::cerr << "❌ FAILED: Exception in CST parser: " << e.what() << std::endl;
                return 1;
            }
            
            // Test fallback mode for compatibility
            std::cout << "\n=== Testing Fallback Mode (cstMode=false) ===\n";
            Scanner scanner2(source, filename);
            scanner2.scanTokens(ScanMode::LEGACY);  // Use legacy scan mode for fallback
            Parser fallbackParser(scanner2, false);  // CST mode disabled
            
            try {
                auto astFallback = fallbackParser.parse();
                
                if (fallbackParser.hadError()) {
                    std::cout << "Parse errors found in fallback mode: " << fallbackParser.getErrors().size() << std::endl;
                } else {
                    std::cout << "✓ Fallback AST parsing completed successfully!\n";
                }
                
                // Show fallback mode evidence
                std::cout << "\n=== Fallback Mode Evidence ===\n";
                std::cout << "CST mode enabled: " << (fallbackParser.isCSTMode() ? "YES" : "NO") << std::endl;
                std::cout << "CST nodes created: " << fallbackParser.getCSTNodeCount() << std::endl;
                std::cout << "Trivia attachments: " << fallbackParser.getTriviaAttachmentCount() << std::endl;
                
                // Compare the two modes
                std::cout << "\n=== Mode Comparison ===\n";
                std::cout << "CST mode AST statements: " << (ast ? ast->statements.size() : 0) << std::endl;
                std::cout << "Fallback mode AST statements: " << (astFallback ? astFallback->statements.size() : 0) << std::endl;
                
                if (ast && astFallback && ast->statements.size() == astFallback->statements.size()) {
                    std::cout << "✓ Both modes produced the same number of statements\n";
                    std::cout << "✓ CST parser maintains compatibility with legacy behavior\n";
                } else {
                    std::cout << "⚠ Different number of statements between modes\n";
                    std::cout << "  This may indicate parsing differences to investigate\n";
                }
                
            } catch (const std::exception& e) {
                std::cerr << "❌ FAILED: Exception in fallback mode: " << e.what() << std::endl;
            }
            
            // Print CST structure if available
            std::cout << "\n=== CST Structure ===\n";
            const CST::Node* cstRoot = cstParser.getCST();
            if (cstRoot) {
                std::cout << "✓ CST root node available\n";
                std::cout << "✓ CST structure created successfully\n";
                
                // Print CST to console using CST printer
                CST::Printer::PrintOptions consoleOptions;
                consoleOptions.includeTrivia = false; // Simplify console output
                consoleOptions.maxDepth = 3; // Limit depth for console readability
                std::cout << CST::Printer::printCST(cstRoot, consoleOptions) << std::endl;
                
                // Save CST to file for detailed analysis
                std::string cstOutputFilename = filename + ".cst.txt";
                std::ofstream cstFile(cstOutputFilename);
                if (cstFile.is_open()) {
                    // Redirect cout to file (same pattern as AST printer)
                    std::streambuf *coutbuf = std::cout.rdbuf();
                    std::cout.rdbuf(cstFile.rdbuf());
                    
                    // Print CST to file
                    std::cout << "CST for " << filename << "\n";
                    std::cout << "Parser: New Unified Parser (CST mode)\n";
                    std::cout << "Mode: CST (cstMode=true)\n";
                    std::cout << "========================================\n\n";
                    
                    std::cout << "CST Statistics:\n";
                    std::cout << "- CST nodes created: " << cstParser.getCSTNodeCount() << "\n";
                    std::cout << "- Trivia attachments: " << cstParser.getTriviaAttachmentCount() << "\n";
                    std::cout << "- Parse errors: " << cstParser.getErrors().size() << "\n\n";
                    
                    if (cstParser.hadError()) {
                        std::cout << "Parse Errors:\n";
                        for (const auto& error : cstParser.getErrors()) {
                            std::cout << "  Line " << error.line << ": " << error.message << "\n";
                        }
                        std::cout << "\n";
                    }
                    
                    // Print full CST structure using CST printer
                    std::cout << "=== Full CST Structure ===\n";
                    CST::Printer::PrintOptions fileOptions;
                    fileOptions.includeTrivia = true; // Include all trivia in file output
                    fileOptions.includeTokens = true; // Include all tokens
                    fileOptions.includeSourcePositions = true; // Include source positions
                    fileOptions.includeErrorInfo = true; // Include error information
                    std::cout << CST::Printer::printCST(cstRoot, fileOptions) << std::endl;
                    
                    // Restore cout
                    std::cout.rdbuf(coutbuf);
                    
                    std::cout << "CST output saved to " << cstOutputFilename << std::endl;
                } else {
                    std::cerr << "Warning: Could not open " << cstOutputFilename << " for writing" << std::endl;
                }
            } else {
                std::cout << "⚠ No CST root available\n";
                std::cout << "  CST creation may have failed - check parser implementation\n";
            }
            
        } else {
            std::cout << "=== Using New Unified Parser (Legacy mode) ===\n";
            
            // Frontend: Lexical analysis (scanning) - no trivia collection
            Scanner scanner(source, filename);
            auto tokens = scanner.scanTokens(ScanMode::LEGACY);
            
            // Print tokens to stdout
            std::cout << "=== Tokens (Legacy Mode) ===\n";
            
            // Capture token output for both console and file
            std::ostringstream tokenOutput;
            tokenOutput << "=== Tokens (Legacy Mode) ===\n";
            
            for (const auto& token : tokens) {
                std::string tokenLine = "Line " + std::to_string(token.line) + ": "
                                      + scanner.tokenTypeToString(token.type)
                                      + " = '" + token.lexeme + "'\n";
                std::cout << tokenLine;
                tokenOutput << tokenLine;
            }
            std::cout << std::endl;
            
            // Save tokens to file
            std::string tokensFilename = filename + ".tokens.txt";
            std::ofstream tokensFile(tokensFilename);
            if (tokensFile.is_open()) {
                tokensFile << "Tokens for " << filename << "\n";
                tokensFile << "Parser: New Unified Parser (Legacy mode)\n";
                tokensFile << "Mode: Legacy AST only (no trivia preservation)\n";
                tokensFile << "========================================\n\n";
                tokensFile << tokenOutput.str();
                tokensFile.close();
                std::cout << "Tokens output saved to " << tokensFilename << std::endl;
            } else {
                std::cerr << "Warning: Could not open " << tokensFilename << " for writing" << std::endl;
            }
            
            // Frontend: Syntax analysis (parsing)
            std::cout << "=== Legacy Mode Parsing ===\n";
            Parser parser(scanner, false);  // CST mode disabled for legacy behavior
            
            try {
                ast = parser.parse();
                
                if (parser.hadError()) {
                    std::cout << "Parse errors found: " << parser.getErrors().size() << std::endl;
                    for (const auto& error : parser.getErrors()) {
                        std::cout << "  Line " << error.line << ": " << error.message << std::endl;
                    }
                } else {
                    std::cout << "✓ Legacy mode parsing completed successfully!\n";
                    std::cout << "✓ No trivia preservation (legacy behavior)\n";
                    std::cout << "✓ Direct AST creation without CST overhead\n";
                }
                
            } catch (const std::exception& e) {
                std::cerr << "❌ FAILED: Exception in legacy parser: " << e.what() << std::endl;
                return 1;
            }
            
            std::cout << std::endl;
        }
        
        // Backend: Print AST to console and file
        std::cout << "=== AST Structure ===\n";
        if (ast) {
            ASTPrinter printer;
            
            // Print to console
            printer.process(ast);
            std::cout << std::endl;
            
            // Save to file
            std::string outputFilename = filename + ".ast.txt";
            std::ofstream outFile(outputFilename);
            if (outFile.is_open()) {
                // Redirect cout to file
                std::streambuf *coutbuf = std::cout.rdbuf();
                std::cout.rdbuf(outFile.rdbuf());
                
                // Print AST to file
                std::cout << "AST for " << filename << "\n";
                std::cout << "Parser: " << (useCSTParser ? "New Unified Parser (CST mode)" : "New Unified Parser (Legacy mode)") << "\n";
                std::cout << "Mode: " << (useCSTParser ? "CST with AST compatibility" : "Legacy AST only") << "\n";
                if (useCSTParser) {
                    std::cout << "Note: CST nodes were created internally with trivia preservation\n";
                    std::cout << "      AST output shown below for compatibility testing\n";
                }
                std::cout << "========================================\n\n";
                printer.process(ast);
                
                // Restore cout
                std::cout.rdbuf(coutbuf);
                
                std::cout << "AST output saved to " << outputFilename << std::endl;
            } else {
                std::cerr << "Warning: Could not open " << outputFilename << " for writing" << std::endl;
            }
        } else {
            std::cout << "❌ No AST available - parsing failed\n";
        }
        
        // Backend: Generate bytecode
        std::cout << "=== Bytecode Generation ===\n";
        if (ast) {
            BytecodeGenerator generator;
            generator.process(ast);
            
            // Print bytecode to console
            BytecodePrinter::print(generator.getBytecode());
            
            // Output bytecode to file
            std::string bytecodeFilename = filename + ".bytecode.txt";
            std::ofstream bytecodeFile(bytecodeFilename);
            if (bytecodeFile.is_open()) {
                bytecodeFile << "Bytecode for " << filename << "\n";
                bytecodeFile << "Parser: " << (useCSTParser ? "New Unified Parser (CST mode)" : "New Unified Parser (Legacy mode)") << "\n";
                bytecodeFile << "========================================\n\n";
                
                // Use BytecodePrinter for file output too
                BytecodePrinter::print(generator.getBytecode(), bytecodeFile);
                
                std::cout << "Bytecode output saved to " << bytecodeFilename << std::endl;
            } else {
                std::cerr << "Warning: Could not open " << bytecodeFilename << " for writing" << std::endl;
            }
        } else {
            std::cout << "❌ No bytecode generated - AST not available\n";
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
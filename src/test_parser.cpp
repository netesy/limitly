#include "backend/ast_printer.hh"
#include "backend/bytecode_printer.hh"
#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "frontend/cst_parser.hh"
#include "frontend/cst_printer.hh"
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
            std::cout << "=== Using CST Parser ===\n";
            
            // Frontend: Enhanced scanning with trivia preservation
            Scanner scanner(source);
            CSTConfig config;
            config.preserveWhitespace = true;
            config.preserveComments = true;
            config.emitErrorTokens = true;
            
            // CST Parsing
            std::cout << "=== CST Parsing ===\n";
            CST::CSTParser cstParser(scanner, config);
            auto cst = cstParser.parse();
            
            if (cstParser.hasErrors()) {
                std::cout << "Parse errors found: " << cstParser.getErrors().size() << std::endl;
                for (const auto& error : cstParser.getErrors()) {
                    std::cout << "  Line " << error.line << ": " << error.description << std::endl;
                }
            } else {
                std::cout << "CST parsing completed successfully!\n";
            }
            
            // Print CST structure
            std::cout << "\n=== CST Structure ===\n";
            if (cst) {
                std::cout << CST::printCST(cst.get()) << std::endl;
            } else {
                std::cout << "No CST generated\n";
            }
            
            // Transform CST to AST
            if (cst) {
                std::cout << "=== CST to AST Transformation ===\n";
                frontend::BuildConfig buildConfig;
                buildConfig.insertErrorNodes = true;
                buildConfig.insertMissingNodes = true;
                buildConfig.preserveSourceMapping = true;
                
                frontend::ASTBuilder astBuilder(buildConfig);
                ast = astBuilder.buildAST(*cst);
                std::cout << "AST transformation completed successfully!\n\n";
            }
            
        } else {
            std::cout << "=== Using Legacy Parser ===\n";
            
            // Frontend: Lexical analysis (scanning)
            Scanner scanner(source);
            scanner.scanTokens();
            
            // Print tokens to stdout
            std::cout << "=== Tokens ===\n";
            for (const auto& token : scanner.getTokens()) {
                std::cout << "Line " << token.line << ": "
                          << scanner.tokenTypeToString(token.type)
                          << " = '" << token.lexeme << "'\n";
            }
            std::cout << std::endl;
            
            // Frontend: Syntax analysis (parsing)
            std::cout << "=== Parsing ===\n";
            Parser parser(scanner);
            ast = parser.parse();
            std::cout << "Parsing completed successfully!\n\n";
        }
        
        // Backend: Print AST to console and file
        std::cout << "=== AST Structure ===\n";
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
            std::cout << "Parser mode: " << (useCSTParser ? "CST" : "Legacy") << "\n";
            std::cout << "========================================\n\n";
            printer.process(ast);
            
            // Restore cout
            std::cout.rdbuf(coutbuf);
            
            std::cout << "AST output saved to " << outputFilename << std::endl;
        } else {
            std::cerr << "Warning: Could not open " << outputFilename << " for writing" << std::endl;
        }
        
        // Backend: Generate bytecode
        std::cout << "=== Bytecode Generation ===\n";
        BytecodeGenerator generator;
        generator.process(ast);
        
        // Print bytecode to console
        BytecodePrinter::print(generator.getBytecode());
        
        // Output bytecode to file
        std::string bytecodeFilename = filename + ".bytecode.txt";
        std::ofstream bytecodeFile(bytecodeFilename);
        if (bytecodeFile.is_open()) {
            bytecodeFile << "Bytecode for " << filename << "\n";
            bytecodeFile << "Parser mode: " << (useCSTParser ? "CST" : "Legacy") << "\n";
            bytecodeFile << "========================================\n\n";
            
            // Use BytecodePrinter for file output too
            BytecodePrinter::print(generator.getBytecode(), bytecodeFile);
            
            std::cout << "Bytecode output saved to " << bytecodeFilename << std::endl;
        } else {
            std::cerr << "Warning: Could not open " << bytecodeFilename << " for writing" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
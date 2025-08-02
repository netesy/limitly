#include "frontend/scanner.hh"
#include "frontend/parser.hh"
#include "backend/code_formatter.hh"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
        return 1;
    }
    
    std::string filename = argv[1];
    
    // Read the source file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }
    
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    file.close();
    
    try {
        // Scan the source code and parse into AST
        Scanner scanner(source);
        
        // Parse the tokens into an AST
        Parser parser(scanner);
        auto program = parser.parse();
        
        if (!program) {
            std::cerr << "Error: Failed to parse the source code" << std::endl;
            return 1;
        }
        
        // Format the code
        CodeFormatter formatter;
        
        // Configure formatter options
        formatter.setIndentSize(4);
        formatter.setUseSpaces(true);
        formatter.setMaxLineLength(100);
        
        std::string formattedCode = formatter.format(program);
        
        // Output the formatted code
        std::cout << formattedCode;
        
        // Optionally save to a .formatted file
        std::string outputFilename = filename + ".formatted";
        std::ofstream outputFile(outputFilename);
        if (outputFile.is_open()) {
            outputFile << formattedCode;
            outputFile.close();
            std::cerr << "Formatted code saved to " << outputFilename << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
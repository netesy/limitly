#include "repl.hh"
//#include "parser.h"
#include "parser.hh"
#include "scanner.hh"
#include <fstream>
#include <iostream>
#include <string>
#include <variant>

void REPL::start()
{
    std::cout << "Limit REPL :" << std::endl;
    while (true) {
        try {
            // Read input
            std::string input = readInput();
            std::cout << "Entered: " << input << std::endl;
            // Parse input
            Scanner scanner(input);
            scanner.scanTokens();
            Parser parser(scanner);
            parser.parse();
            std::cout << "======= Debug =======\n"
                    << scanner.toString()
                    << "======= End Debug =======\n"
                    << std::endl;
            // Interpret parsed code
            // Interpreter interpreter(parser.getResult());
            // interpreter.interpret();
        } catch (const std::exception &e) {
            // std::cout << e << std::endl;
            // Debugger::error(e.what(), 0, 0, "", Debugger::getSuggestion(e.what()));
        }
    }
}

void REPL::startDevMode()
{
    //start the language with debugging enabled.
    std::cout << "Not yet Implemented" << std::endl;
    start();
}

std::string REPL::readInput() {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);
    return input;
}

std::string REPL::readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

//parser.cpp
#include "parser.h"
#include "Syntax.h"
#include "debugger.h"

Parser::Parser(Scanner &scanner)
    : scanner(scanner)
{
    advance();
}

void Parser::parse()
{
    // Parse the program
    while (!scanner.isAtEnd()) {
        statement();
    }
}

void Parser::advance()
{
    // Update the currentToken by scanning the next token from the scanner
    currentToken = scanner.getToken();
}

void Parser::consume(TokenType type, const std::string &message)
{
    if (currentToken.type != type) {
        Debugger::error(message,
                        scanner.getLine(),
                        scanner.getCurrent(),
                        InterpretationStage::PARSING,
                        scanner.getLexeme());
    }
    advance();
}

void Parser::emit(Opcode opcode, uint32_t lineNumber)
{
    // Create an Instruction object and add it to the bytecode vector
    bytecode.emplace_back(opcode, lineNumber);
}

void Parser::statement()
{
    // Implement parsing of different types of statements here
    expression(); // Placeholder for expression statement
    consume(TokenType::SEMICOLON, "Expected ';' after statement.");
}

void Parser::expression()
{
    // Implement parsing of expressions using Pratt parser
    // For simplicity, let's parse a primary expression here
    primary();
}

void Parser::declaration()
{
    // Implement parsing of declarations
    // For simplicity, let's parse a variable declaration here
    variableDeclaration();
}

void Parser::functionDeclaration()
{
    // Implement parsing of function declarations
    // For simplicity, let's parse a function declaration here
    Syntax::parseFunctionDeclaration(scanner);
}

void Parser::loop()
{
    // Implement parsing of loops
    // For simplicity, let's parse a loop here
    Syntax::parseLoop(scanner);
}

void Parser::conditional()
{
    // Implement parsing of conditionals
    // For simplicity, let's parse a conditional here
    Syntax::parseConditional(scanner);
}

void Parser::classDeclaration()
{
    // Implement parsing of class declarations
    // For simplicity, let's parse a class declaration here
    Syntax::parseClassDeclaration(scanner);
}

void Parser::variableDeclaration()
{
    // Implement parsing of variable declarations
    // For simplicity, let's parse a variable declaration here
    Syntax::parseVariableDeclaration(scanner);
}

void Parser::assignment()
{
    // Implement parsing of assignments
    // For simplicity, let's parse an assignment here
    Syntax::parseAssignment(scanner);
}

void Parser::primary()
{
    // Implement parsing of primary expressions
    // For simplicity, let's parse a primary expression here
    Syntax::parseExpression(scanner);
}

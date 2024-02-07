// syntax.h
#ifndef SYNTAX_H
#define SYNTAX_H

#pragma once

#include "scanner.h"

class Syntax {
public:
    static void parseFunctionDeclaration(Scanner& scanner);
    static void parseLoop(Scanner& scanner);
    static void parseConditional(Scanner& scanner);
    static void parseClassDeclaration(Scanner& scanner);
    static void parseVariableDeclaration(Scanner& scanner);
    static void parseAssignment(Scanner& scanner);
    static void parseExpression(Scanner& scanner);
    static void parseAttempt(Scanner& scanner);
    static void parseString(Scanner& scanner);
    static void parseConcurrent(Scanner& scanner);
    static void parseParallel(Scanner& scanner);
    static void parseAwait(Scanner& scanner);
    static void parseAsync(Scanner& scanner);
    // Helper functions
    static char advance(Scanner &scanner);
    static bool match(Scanner &scanner, TokenType expected);

private:
    // Arithmetic parsing functions
    static void ternary(Scanner& scanner);
    static void logicalOr(Scanner& scanner);
    static void logicalAnd(Scanner& scanner);
    static void equality(Scanner& scanner);
    static void comparison(Scanner& scanner);
    static void addition(Scanner& scanner);
    static void subtraction(Scanner& scanner);
    static void multiplication(Scanner& scanner);
    static void division(Scanner& scanner);
    static void modulus(Scanner& scanner);
    static void unary(Scanner& scanner);
    static void primary(Scanner& scanner);
    static void parseForLoop(Scanner &scanner);
    static void parseWhileLoop(Scanner &scanner);

    // Helper functions
    static void parseIdentifier(Scanner& scanner);
    static void parseType(Scanner& scanner);
    static void parseArguments(Scanner& scanner);
    static void error(const std::string &message, int line, int start);
};
#endif // SYNTAX_H

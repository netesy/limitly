#include "syntax.hpp"
#include "debugger.hpp"

void Syntax::parseFunctionDeclaration(Scanner& scanner) {
    // Parse function declaration syntax
    // Example:
    // fn greeting(name: str, date: str? = None): str {
    //     ...
    // }
    advance(scanner); // Consume 'fn' token
    // Parse function name
    if (match(scanner, TokenType::IDENTIFIER)) {
        advance(scanner); // Consume function identifier
    } else {
        error("Expected function identifier.", scanner.line, scanner.current);
    }
    // Parse function parameters
    if (match(scanner, TokenType::LEFT_PAREN)) {
        advance(scanner); // Consume '(' token
        while (!match(scanner, TokenType::RIGHT_PAREN) && !match(scanner, TokenType::EOF_TOKEN)) {
            // Parse parameter name
            if (match(scanner, TokenType::IDENTIFIER)) {
                advance(scanner); // Consume parameter identifier
                // Parse optional parameter default value
                if (match(scanner, TokenType::EQUAL)) {
                    advance(scanner); // Consume '=' token
                    parseExpression(scanner); // Parse default value expression
                }
                if (!match(scanner, TokenType::RIGHT_PAREN)) {
                    if (!match(scanner, TokenType::COMMA)) {
                        error("Expected ',' or ')' in parameter list.",
                              scanner.line,
                              scanner.current);
                    } else {
                        advance(scanner); // Consume ',' token
                    }
                }
            } else {
                error("Expected parameter identifier.", scanner.line, scanner.current);
            }
        }
        if (!match(scanner, TokenType::RIGHT_PAREN)) {
            error("Expected ')' after parameter list.", scanner.line, scanner.current);
        } else {
            advance(scanner); // Consume ')' token
        }
    } else {
        error("Expected '(' before parameter list.", scanner.line, scanner.current);
    }
    // Parse return type
    if (match(scanner, TokenType::COLON)) {
        advance(scanner); // Consume ':' token
        parseType(scanner); // Parse return type
    }
    // Parse function body
    if (match(scanner, TokenType::LEFT_BRACE)) {
        advance(scanner); // Consume '{' token
        while (!match(scanner, TokenType::RIGHT_BRACE) && !match(scanner, TokenType::EOF_TOKEN)) {
            parseExpression(scanner); // Parse statements within the function body
        }
        if (!match(scanner, TokenType::RIGHT_BRACE)) {
            error("Expected '}' after function body.", scanner.line, scanner.current);
        } else {
            advance(scanner); // Consume '}' token
        }
    } else {
        error("Expected '{' before function body.", scanner.line, scanner.current);
    }
}

void Syntax::parseLoop(Scanner &scanner)
{
    if (match(scanner, TokenType::FOR)) {
        parseForLoop(scanner);
    } else if (match(scanner, TokenType::WHILE)) {
        parseWhileLoop(scanner);
    } else {
        error("Expected 'for' or 'while' loop.", scanner.line, scanner.current);
    }
}

void Syntax::parseForLoop(Scanner &scanner)
{
    // Parse for loop syntax
    // Example:
    // for (var i = 0; i < 5; i++) {
    //     ...
    // }
    advance(scanner); // Consume 'for' token
    if (!match(scanner, TokenType::LEFT_PAREN)) {
        error("Expected '(' after 'for'.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume '(' token

    // Parse initialization
    parseVariableDeclaration(scanner); // Parse variable declaration

    // Parse condition
    if (!match(scanner, TokenType::SEMICOLON)) {
        error("Expected ';' after loop initialization.", scanner.line, scanner.current);
    }
    advance(scanner);         // Consume ';' token
    parseExpression(scanner); // Parse loop condition

    // Parse increment
    if (!match(scanner, TokenType::SEMICOLON)) {
        error("Expected ';' after loop condition.", scanner.line, scanner.current);
    }
    advance(scanner);         // Consume ';' token
    parseExpression(scanner); // Parse loop increment

    if (!match(scanner, TokenType::RIGHT_PAREN)) {
        error("Expected ')' after loop increment.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume ')' token

    // Parse loop body
    if (!match(scanner, TokenType::LEFT_BRACE)) {
        error("Expected '{' before loop body.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume '{' token
    while (!match(scanner, TokenType::RIGHT_BRACE) && !match(scanner, TokenType::EOF_TOKEN)) {
        parseExpression(scanner); // Parse statements within the loop body
    }
    if (!match(scanner, TokenType::RIGHT_BRACE)) {
        error("Expected '}' after loop body.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume '}' token
}

void Syntax::parseWhileLoop(Scanner &scanner)
{
    // Parse while loop syntax
    // Example:
    // while (condition) {
    //     ...
    // }
    advance(scanner); // Consume 'while' token
    if (!match(scanner, TokenType::LEFT_PAREN)) {
        error("Expected '(' after 'while'.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume '(' token

    // Parse condition
    parseExpression(scanner); // Parse while loop condition

    if (!match(scanner, TokenType::RIGHT_PAREN)) {
        error("Expected ')' after condition.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume ')' token

    // Parse loop body
    if (!match(scanner, TokenType::LEFT_BRACE)) {
        error("Expected '{' before loop body.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume '{' token
    while (!match(scanner, TokenType::RIGHT_BRACE) && !match(scanner, TokenType::EOF_TOKEN)) {
        parseExpression(scanner); // Parse statements within the loop body
    }
    if (!match(scanner, TokenType::RIGHT_BRACE)) {
        error("Expected '}' after loop body.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume '}' token
}

void Syntax::parseConditional(Scanner &scanner)
{
    // Parse conditional syntax
    // Example:
    // if (condition) {
    //     ...
    // } else {
    //     ...
    // }
    advance(scanner); // Consume 'if' token
    if (!match(scanner, TokenType::LEFT_PAREN)) {
        error("Expected '(' after 'if'.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume '(' token

    // Parse condition
    parseExpression(scanner); // Parse conditional expression

    if (!match(scanner, TokenType::RIGHT_PAREN)) {
        error("Expected ')' after condition.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume ')' token

    // Parse true branch
    if (!match(scanner, TokenType::LEFT_BRACE)) {
        error("Expected '{' before true branch.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume '{' token
    while (!match(scanner, TokenType::RIGHT_BRACE) && !match(scanner, TokenType::ELSE) && !match(scanner, TokenType::EOF_TOKEN)) {
        parseExpression(scanner); // Parse statements within the true branch
    }
    if (!match(scanner, TokenType::RIGHT_BRACE)) {
        error("Expected '}' after true branch.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume '}' token

    // Parse optional else branch
    if (match(scanner, TokenType::ELSE)) {
        advance(scanner); // Consume 'else' token
        // Parse else branch
        if (!match(scanner, TokenType::LEFT_BRACE)) {
            error("Expected '{' before else branch.", scanner.line, scanner.current);
        }
        advance(scanner); // Consume '{' token
        while (!match(scanner, TokenType::RIGHT_BRACE) && !match(scanner, TokenType::EOF_TOKEN)) {
            parseExpression(scanner); // Parse statements within the else branch
        }
        if (!match(scanner, TokenType::RIGHT_BRACE)) {
            error("Expected '}' after else branch.", scanner.line, scanner.current);
        }
        advance(scanner); // Consume '}' token
    }
}

void Syntax::parseClassDeclaration(Scanner& scanner) {
    // Parse class declaration syntax
    // Example:
    // class MyClass {
    //     ...
    // }
    advance(scanner); // Consume 'class' token

    // Parse class name (identifier)
    if (!match(scanner, TokenType::IDENTIFIER)) {
        error("Expected class name after 'class' keyword.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume class name token

    // Parse class body
    if (!match(scanner, TokenType::LEFT_BRACE)) {
        error("Expected '{' before class body.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume '{' token

    // Parse class members (variables, methods, etc.)
    while (!match(scanner, TokenType::RIGHT_BRACE) && !match(scanner, TokenType::EOF_TOKEN)) {
        // Here you can implement logic to parse class members
        // For example, parseVariableDeclaration or parseFunctionDeclaration functions can be called here
        // Ensure to handle different class members appropriately
        advance(scanner); // Placeholder for parsing class members
    }

    if (!match(scanner, TokenType::RIGHT_BRACE)) {
        error("Expected '}' after class body.", scanner.line, scanner.current);
    }
    advance(scanner); // Consume '}' token
}

void Syntax::parseVariableDeclaration(Scanner& scanner) {
    // Parse variable declaration syntax
    // Example:
    // var myVar: int = 10;
    advance(scanner);         // Consume 'var' token
    parseIdentifier(scanner); // Parse variable name
    // Parse the variable name
    std::string variableName = scanner.getToken().lexeme;
    advance(scanner);         // Consume ':' token
    parseType(scanner);       // Parse variable type
    // Emit the opcode to declare the variable
    parser.emit(Opcode::DECLARE_VARIABLE, scanner.getLine(), variableName);
    if (match(scanner, TokenType::EQUAL)) {
        advance(scanner);         // Consume '=' token
        parseExpression(scanner); // Parse expression
    }
}

void Syntax::parseAssignment(Scanner& scanner) {
    // Parse assignment syntax
    // Example:
    // myVar = 20;
    parseIdentifier(scanner); // Parse variable name
    advance(scanner); // Consume '=' token
    parseExpression(scanner); // Parse expression
}

void Syntax::parseExpression(Scanner &scanner)
{
    if (match(scanner, TokenType::LEFT_PAREN)) {
        // Parse nested expression within parentheses
        advance(scanner);         // Consume '(' token
        parseExpression(scanner); // Parse nested expression
        if (!match(scanner, TokenType::RIGHT_PAREN)) {
            error("Expected ')' after expression.", scanner.getLine(), scanner.getCurrent());
        }
        advance(scanner); // Consume ')' token
    } else {
        if (match(scanner, TokenType::IDENTIFIER) || match(scanner, TokenType::NUMBER)
            || match(scanner, TokenType::STRING)) {
            advance(scanner); // Consume identifier, number, or string token
        } else {
            error("Expected identifier, number, or string in expression.",
                scanner.getLine(),
                scanner.getCurrent());
            return;
        }
        if (match(scanner, TokenType::LEFT_PAREN)) {
            advance(scanner); // Consume '(' token if it's a function call
            if (!match(scanner, TokenType::RIGHT_PAREN)) {
                parseArguments(scanner); // Parse function arguments
            }
            if (!match(scanner, TokenType::RIGHT_PAREN)) {
                error("Expected ')' after function arguments in expression.",
                    scanner.getLine(),
                    scanner.getCurrent());
            }
            advance(scanner); // Consume ')' token
        }
    }
}

void Syntax::parseAttempt(Scanner& scanner) {
    // Parse attempt syntax
    // Example:
    // attempt {
    //     ...
    // } handle ExceptionType {
    //     ...
    // }
    advance(scanner); // Consume 'attempt' token
    // Parse attempt block
    while (!match(scanner, TokenType::HANDLE) && !match(scanner, TokenType::EOF_TOKEN)) {
        parseExpression(scanner); // Parse statements within the attempt block
    }
    if (match(scanner, TokenType::HANDLE)) {
        advance(scanner); // Consume 'handle' token
        // Parse handle block
        while (!match(scanner, TokenType::EOF_TOKEN)) {
            parseExpression(scanner); // Parse statements within the handle block
        }
    } else {
        error("Expected 'handle' after 'attempt'.", scanner.line, scanner.current);
    }
}

void Syntax::parseString(Scanner& scanner) {
    // Placeholder for parsing string syntax
}

void Syntax::parseConcurrent(Scanner& scanner) {
    // Parse concurrent syntax
    // Example:
    // concurrent {
    //     ...
    // }
    advance(scanner); // Consume 'concurrent' token
    // Parse concurrent block
    while (!match(scanner, TokenType::RIGHT_BRACE) && !match(scanner, TokenType::EOF_TOKEN)) {
        parseExpression(scanner); // Parse statements within the concurrent block
    }
    if (!match(scanner, TokenType::RIGHT_BRACE)) {
        error("Expected '}' after 'concurrent'.", scanner.line, scanner.current);
    } else {
        advance(scanner); // Consume '}' token
    }
}

void Syntax::parseParallel(Scanner& scanner) {
    // Parse parallel syntax
    // Example:
    // parallel {
    //     ...
    // }
    advance(scanner); // Consume 'parallel' token
    // Parse parallel block
    while (!match(scanner, TokenType::RIGHT_BRACE) && !match(scanner, TokenType::EOF_TOKEN)) {
        parseExpression(scanner); // Parse statements within the parallel block
    }
    if (!match(scanner, TokenType::RIGHT_BRACE)) {
        error("Expected '}' after 'parallel'.", scanner.line, scanner.current);
    } else {
        advance(scanner); // Consume '}' token
    }
}

void Syntax::parseAwait(Scanner& scanner) {
    // Parse await syntax
    // Example:
    // var result = await asyncTask();
    parseExpression(scanner); // Parse asynchronous task expression
}

void Syntax::parseAsync(Scanner& scanner) {
    // Parse async syntax
    // Example:
    // async fn asyncTask() {
    //     ...
    // }
    advance(scanner); // Consume 'async' token
    parseFunctionDeclaration(scanner); // Parse asynchronous task function declaration
}

// Arithmetic parsing functions
void Syntax::ternary(Scanner& scanner) {
    // Parse ternary operation syntax
    // Example:
    // var max = (a > b) ? a : b;
    parseExpression(scanner); // Parse condition
    advance(scanner); // Consume '?' token
    parseExpression(scanner); // Parse expression for true branch
    advance(scanner); // Consume ':' token
    parseExpression(scanner); // Parse expression for false branch
}

void Syntax::logicalOr(Scanner& scanner) {
    // Parse logical OR operation syntax
    // Example:
    // if (condition1 or condition2) {
    //     ...
    // }
    parseExpression(scanner); // Parse left operand
    advance(scanner); // Consume 'or' token
    parseExpression(scanner); // Parse right operand
}

void Syntax::logicalAnd(Scanner& scanner) {
     // Parse logical AND operation syntax
    // Example:
    // if (condition1 and condition2) {
    //     ...
    // }
    parseExpression(scanner); // Parse left operand
    advance(scanner); // Consume 'and' token
    parseExpression(scanner); // Parse right operand
}

void Syntax::equality(Scanner& scanner) {
    // Parse equality operation syntax
    // Example:
    // if (a == b) {
    //     ...
    // }
    parseExpression(scanner); // Parse left operand
    advance(scanner); // Consume '==' token
    parseExpression(scanner); // Parse right operand
}

void Syntax::comparison(Scanner& scanner) {
    // Parse comparison operation syntax
    // Example:
    // if (a < b) {
    //     ...
    // }
    parseExpression(scanner); // Parse left operand
    advance(scanner); // Consume comparison token
    parseExpression(scanner); // Parse right operand
}

void Syntax::addition(Scanner& scanner) {
    // Parse addition operation syntax
    // Example:
    // var sum = a + b;
    parseExpression(scanner); // Parse left operand
    advance(scanner); // Consume '+' token
    parseExpression(scanner); // Parse right operand
}

void Syntax::subtraction(Scanner& scanner) {
    // Parse subtraction operation syntax
    // Example:
    // var difference = a - b;
    parseExpression(scanner); // Parse left operand
    advance(scanner); // Consume '-' token
    parseExpression(scanner); // Parse right operand
}

void Syntax::multiplication(Scanner& scanner) {
    // Parse multiplication operation syntax
    // Example:
    // var product = a * b;
    parseExpression(scanner); // Parse left operand
    advance(scanner); // Consume '*' token
    parseExpression(scanner); // Parse right operand
}

void Syntax::division(Scanner& scanner) {
    // Parse division operation syntax
    // Example:
    // var quotient = a / b;
    parseExpression(scanner); // Parse left operand
    advance(scanner); // Consume '/' token
    parseExpression(scanner); // Parse right operand
}

void Syntax::modulus(Scanner& scanner) {
    // Parse modulus operation syntax
    // Example:
    // var remainder = a % b;
    parseExpression(scanner); // Parse left operand
    advance(scanner); // Consume '%' token
    parseExpression(scanner); // Parse right operand
}

void Syntax::unary(Scanner& scanner) {
    // Parse unary operation syntax
    // Example:
    // var result = -value;
    if (match(scanner, TokenType::BANG) || match(scanner, TokenType::MINUS)) {
        advance(scanner); // Consume unary operator
        parseExpression(scanner); // Parse operand
    } else {
        primary(scanner); // Parse primary expression
    }
}

void Syntax::primary(Scanner& scanner) {
    // Parse primary expression syntax
    // Example:
    // var value = (1 + 2) * 3;
    if (match(scanner, TokenType::LEFT_PAREN)) {
        advance(scanner); // Consume '(' token
        parseExpression(scanner); // Parse expression within parentheses
        advance(scanner); // Consume ')' token
    } else if (match(scanner, TokenType::IDENTIFIER) || match(scanner, TokenType::NUMBER) || match(scanner, TokenType::STRING)) {
        advance(scanner); // Consume identifier, number, or string token
    } else {
        error("Expected primary expression.", scanner.line, scanner.current);
    }
}

void Syntax::parseIdentifier(Scanner& scanner) {
    if (match(scanner, TokenType::IDENTIFIER)) {
        advance(scanner); // Consume identifier token
    } else {
        error("Expected an identifier.", scanner.line, scanner.current);
    }
}

void Syntax::parseType(Scanner& scanner) {
    if (match(scanner, TokenType::INT_TYPE) || match(scanner, TokenType::FLOAT_TYPE) ||
        match(scanner, TokenType::STR_TYPE) || match(scanner, TokenType::BOOL_TYPE) ||
        match(scanner, TokenType::USER_TYPE) || match(scanner, TokenType::FUNCTION_TYPE) ||
        match(scanner, TokenType::LIST_TYPE) || match(scanner, TokenType::DICT_TYPE) ||
        match(scanner, TokenType::ARRAY_TYPE) || match(scanner, TokenType::ENUM_TYPE)) {
        advance(scanner); // Consume type token
    } else {
        error("Expected a valid type.", scanner.line, scanner.current);
    }
}

void Syntax::parseArguments(Scanner& scanner) {
    parseExpression(scanner); // Parse first argument
    while (match(scanner, TokenType::COMMA)) {
        advance(scanner); // Consume ',' token
        parseExpression(scanner); // Parse next argument
    }
}

char Syntax::advance(Scanner& scanner) {
    return scanner.advance();
}

bool Syntax::match(Scanner& scanner, TokenType expected) {
    if (scanner.isAtEnd()) return false;
    if (!match(scanner, expected))
        return false;
    //if (scanner.peek().type != expected) return false;
    scanner.advance(); // Consume the token
    return true;
}

void Syntax::error(const std::string &message, int line = 0, int start = 0)
{
    Debugger::error(message, line, start, InterpretationStage::SYNTAX);
}

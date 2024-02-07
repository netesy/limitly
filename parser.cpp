//parser.cpp
#include "parser.hpp"
#include "debugger.hpp"

void Parser::parse()
{
    while (!scanner.isAtEnd()) {
        parseStatement();
    }
}

void Parser::parseStatement()
{
    Token nextToken = scanner.getNextToken();

    // Check the type of the next token and parse accordingly
    switch (nextToken.type) {
    case TokenType::VAR:
        parseVariableDeclaration();
        break;
    case TokenType::IDENTIFIER:
        parseIdentifier();
        break;
    case TokenType::FOR:
        parseForLoop();
        break;
    case TokenType::WHILE:
        parseWhileLoop();
        break;
    case TokenType::IF:
        parseConditional();
        break;
    case TokenType::CLASS:
        parseClassDeclaration();
        break;
    case TokenType::PRINT: // Example: Handle print statement
        syntax.parsePrintStatement(scanner);
        break;
    case TokenType::RETURN: // Example: Handle return statement
        syntax.parseReturnStatement(scanner);
        break;
    case TokenType::ASYNC:
        parseAsync();
        break;
    case TokenType::AWAIT:
        parseAwait();
        break;
    case TokenType::PARALLEL:
        parseParallel();
        break;
    case TokenType::CONCURRENT:
        parseConcurrent();
        break;
    case TokenType::ATTEMPT:
        parseAttempt();
        break;
    case TokenType::MATCH:
        syntax.parsePatternMatching(scanner);
        break;
    default:
        // Handle any other statement types or raise an error
        error("Unexpected token for statement", scanner.getLine(), scanner.getCurrent());
        break;
    }
}

void Parser::parseExpression(int precedence)
{
    Token currentToken = scanner.getToken();
    // Parse the left operand
    parsePrimary();

    // Loop to handle infix operators with precedence greater than or equal to the current precedence
    while (precedence < getPrecedence(currentToken.type)) {
        TokenType operatorType = currentToken.type;

        // Handle unary operators
        if (isUnaryOperator(operatorType)) {
            parseUnary();
        } else {
            // Consume the operator token
            consume(operatorType);

            // Parse the right operand with higher precedence
            int nextPrecedence = getPrecedence(operatorType);

            // Parse the right-hand side of the expression recursively
            parseExpression(nextPrecedence);

            // Handle binary operators
            switch (operatorType) {
            case TokenType::PLUS:
                parseAddition();
                break;
            case TokenType::MINUS:
                parseSubstraction();
                break;
            case TokenType::STAR:
                parseMultiplication();
                break;
            case TokenType::SLASH:
                parseDivision();
                break;
            case TokenType::MODULUS:
                parseModulus();
                break;
            case TokenType::AND:
                parseLogicalAnd();
                break;
            case TokenType::OR:
                parseLogicalOr();
                break;
            case TokenType::EQUAL:
                parseEquality();
                break;
            case TokenType::BANG_EQUAL:
                parseEquality();
                break;
            case TokenType::GREATER:
            case TokenType::GREATER_EQUAL:
            case TokenType::LESS:
            case TokenType::LESS_EQUAL:
                parseComparison();
                break;
            // Add cases for other binary operators as needed
            default:
                // Handle unknown operators or raise an error
                error("Unexpected operator in expression");
                break;
            }
        }
    }
}

void Parser::parsePrimary()
{
    syntax.primary(scanner);
}

void Parser::parseUnary()
{
    syntax.unary(scanner);
}

void Parser::parseBinary(int precedence)
{
    // Implement parsing of binary expressions with given precedence
}

void Parser::parseTernary()
{
    syntax.ternary(scanner);
}

void Parser::parseLogicalOr()
{
    syntax.logicalOr(scanner);
}

void Parser::parseLogicalAnd()
{
    syntax.logicalAnd(scanner);
}

void Parser::parseEquality()
{
    syntax.equality(scanner);
}

void Parser::parseComparison()
{
    syntax.comparison(scanner);
}

void Parser::parseAddition()
{
    syntax.addition(scanner);
    emit(Opcode::ADD, scanner.getLine());
}

void Parser::parseSubstraction()
{
    syntax.subtraction(scanner);
}

void Parser::parseMultiplication()
{
    syntax.multiplication(scanner);
}

void Parser::parseDivision()
{
    syntax.division(scanner);
}

void Parser::parseModulus()
{
    syntax.modulus(scanner);
}

void Parser::parseFunctionDeclaration()
{
    syntax.parseFunctionDeclaration(scanner);
}

void Parser::parseForLoop()
{
    syntax.parseForLoop(scanner);
}

void Parser::parseWhileLoop()
{
    syntax.parseWhileLoop(scanner);
}

void Parser::parseConditional()
{
    syntax.parseConditional(scanner);
}

void Parser::parseClassDeclaration()
{
    syntax.parseClassDeclaration(scanner);
}

void Parser::parseVariableDeclaration()
{
    syntax.parseVariableDeclaration(scanner);
}

void Parser::parseAssignment()
{
    syntax.parseAssignment(scanner);
}

//void Parser::parseExpression()
//{
//    syntax.parseExpression(scanner);
//}

void Parser::parseAttempt()
{
    syntax.parseAttempt(scanner);
}

void Parser::parseString()
{
    syntax.parseString(scanner);
}

void Parser::parseConcurrent()
{
    syntax.parseConcurrent(scanner);
}

void Parser::parseParallel()
{
    syntax.parseParallel(scanner);
}

void Parser::parseAwait()
{
    syntax.parseAwait(scanner);
}

void Parser::parseAsync()
{
    syntax.parseAsync(scanner);
}

void Parser::parseIdentifier()
{
    // Check if the next token is followed by an assignment operator
    if (scanner.getNextToken().type == TokenType::EQUAL) {
        syntax.parseAssignment(scanner);
    } else {
        // Handle other cases for identifier usage (e.g., function call)
        syntax.parseIdentifier(scanner);
    }
}

void Parser::parseType()
{
    syntax.parseType(scanner);
}

void Parser::parseArguments()
{
    syntax.parseArguments(scanner);
}

void Parser::parsePatternMatching()
{
    syntax.parsePatternMatching(scanner);
}

void Parser::parseMatchCase()
{
    syntax.parseMatchCase(scanner);
}

void Parser::emit(Opcode op,
                  uint32_t lineNumber,
                  int32_t intValue,
                  float floatValue,
                  bool boolValue,
                  const std::string &stringValue)
{
    Bytecode bytecode;
    // Create and push the instruction onto the bytecode vector
    if (intValue > 0) {
        bytecode.push_back(Instruction{op, lineNumber, intValue});
    } else if (floatValue > 0.0f) {
        bytecode.push_back(Instruction{op, lineNumber, floatValue});
    } else if (boolValue == true) {
        bytecode.push_back(Instruction{op, lineNumber, boolValue});
    } else if (stringValue != "") {
        bytecode.push_back(Instruction{op, lineNumber, stringValue});
    } else {
        bytecode.push_back(Instruction{op, lineNumber});
    }
}

void Parser::error(const std::string &message, int line, int start)
{
    Debugger::error(message, line, start, InterpretationStage::PARSING);
}

int Parser::getPrecedence(TokenType type)
{
    switch (type) {
    // Group: Delimiters
    case TokenType::LEFT_PAREN:
    case TokenType::RIGHT_PAREN:
    case TokenType::LEFT_BRACE:
    case TokenType::RIGHT_BRACE:
    case TokenType::LEFT_BRACKET:
    case TokenType::RIGHT_BRACKET:
    case TokenType::COMMA:
    case TokenType::DOT:
    case TokenType::COLON:
    case TokenType::SEMICOLON:
    case TokenType::QUESTION:
    case TokenType::ARROW:
        return 0;

        // Group: Operators
    case TokenType::PLUS:
    case TokenType::MINUS:
        return 10; // Addition and subtraction have lower precedence
    case TokenType::SLASH:
    case TokenType::MODULUS:
    case TokenType::STAR:
        return 20; // Multiplication, division, and modulus have higher precedence
    case TokenType::BANG:
        return 30; // Negation has higher precedence than other unary operators
    case TokenType::BANG_EQUAL:
    case TokenType::EQUAL:
    case TokenType::EQUAL_EQUAL:
    case TokenType::GREATER:
    case TokenType::GREATER_EQUAL:
    case TokenType::LESS:
    case TokenType::LESS_EQUAL:
        return 40; // Comparison operators have higher precedence
    case TokenType::AND:
        return 50; // Logical AND has higher precedence than logical OR
    case TokenType::OR:
        return 60; // Logical OR has lower precedence

        // Group: Literals
    case TokenType::IDENTIFIER:
    case TokenType::STRING:
    case TokenType::NUMBER:
        return 70;

        // Group: Types
    case TokenType::INT_TYPE:
    case TokenType::FLOAT_TYPE:
    case TokenType::STR_TYPE:
    case TokenType::BOOL_TYPE:
    case TokenType::USER_TYPE:
    case TokenType::FUNCTION_TYPE:
    case TokenType::LIST_TYPE:
    case TokenType::DICT_TYPE:
    case TokenType::ARRAY_TYPE:
    case TokenType::ENUM_TYPE:
        return 80;

        // Other
    case TokenType::UNDEFINED:
    case TokenType::EOF_TOKEN:
        return -1; // Lowest precedence for these tokens

        // Default
    default:
        return 0;
    }
}

// Example implementation of isUnaryOperator
bool Parser::isUnaryOperator(TokenType type)
{
    return type == TokenType::MINUS; // Example: consider '-' as unary operator
}

// Example implementation of consume
void Parser::consume(TokenType expectedType)
{
    Token token = scanner.getNextToken();
    if (token.type != expectedType) {
        // Handle error: unexpected token type
    }
}

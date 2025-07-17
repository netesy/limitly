#include "parser.hh"
#include "../debugger.hh"
#include <iostream>
#include <stdexcept>

// Helper methods
Token Parser::peek() {
    return scanner.tokens[current];
}

Token Parser::previous() {
    return scanner.tokens[current - 1];
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return peek().type == type;
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::EOF_TOKEN;
}

Token Parser::consume(TokenType type, const std::string &message) {
    if (check(type)) return advance();
    error(message);
    throw std::runtime_error(message);
}

void Parser::synchronize() {
    advance();

    while (!isAtEnd()) {
        if (previous().type == TokenType::SEMICOLON) return;

        switch (peek().type) {
            case TokenType::CLASS:
            case TokenType::FN:
            case TokenType::VAR:
            case TokenType::FOR:
            case TokenType::IF:
            case TokenType::WHILE:
            case TokenType::PRINT:
            case TokenType::RETURN:
                return;
            default:
                break;
        }

        advance();
    }
}

void Parser::error(const std::string &message) {
    Debugger::error(message, peek().line, 0, InterpretationStage::PARSING);
}

// Main parse method
std::shared_ptr<AST::Program> Parser::parse() {
    auto program = std::make_shared<AST::Program>();
    program->line = 1;

    try {
        while (!isAtEnd()) {
            auto stmt = declaration();
            if (stmt) {
                program->statements.push_back(stmt);
            }
        }
    } catch (const std::exception &e) {
        // Handle parsing errors
        synchronize();
    }

    return program;
}

// Parse declarations
std::shared_ptr<AST::Statement> Parser::declaration() {
    try {
        if (match({TokenType::CLASS})) {
            return classDeclaration();
        }
        if (match({TokenType::FN})) {
            return function("function");
        }
        if (match({TokenType::ASYNC})) {
            consume(TokenType::FN, "Expected 'fn' after 'async'.");
            auto asyncFn = std::make_shared<AST::AsyncFunctionDeclaration>(*function("async function"));
            return asyncFn;
        }
        if (match({TokenType::VAR})) {
            return varDeclaration();
        }
        if (match({TokenType::ENUM})) {
            return enumDeclaration();
        }
        if (match({TokenType::IMPORT})) {
            return importStatement();
        }
        if (match({TokenType::TYPE})) {
            return typeDeclaration();
        }
        if (match({TokenType::TRAIT})) {
            return traitDeclaration();
        }
        if (match({TokenType::INTERFACE})) {
            return interfaceDeclaration();
        }
        if (match({TokenType::MODULE})) {
            return moduleDeclaration();
        }

        return statement();
    } catch (const std::exception &e) {
        synchronize();
        return nullptr;
    }
}

std::shared_ptr<AST::Statement> Parser::varDeclaration() {
    auto var = std::make_shared<AST::VarDeclaration>();
    var->line = previous().line;

    // Parse variable name
    Token name = consume(TokenType::IDENTIFIER, "Expected variable name.");
    var->name = name.lexeme;

    // Parse optional type annotation
    if (match({TokenType::COLON})) {
        var->type = parseTypeAnnotation();
    }

    // Parse optional initializer
    if (match({TokenType::EQUAL})) {
        var->initializer = expression();
    }

    consume(TokenType::SEMICOLON, "Expected ';' after variable declaration.");
    return var;
}

std::shared_ptr<AST::Statement> Parser::statement() {
    if (match({TokenType::PRINT})) {
        return printStatement();
    }
    if (match({TokenType::IF})) {
        return ifStatement();
    }
    if (match({TokenType::FOR})) {
        return forStatement();
    }
    if (match({TokenType::WHILE})) {
        return whileStatement();
    }
    if (match({TokenType::ITER})) {
        return iterStatement();
    }
    if (match({TokenType::LEFT_BRACE})) {
        return block();
    }
    if (match({TokenType::RETURN})) {
        return returnStatement();
    }
    if (match({TokenType::PARALLEL})) {
        return parallelStatement();
    }
    if (match({TokenType::CONCURRENT})) {
        return concurrentStatement();
    }
    if (match({TokenType::MATCH})) {
        return matchStatement();
    }
    if (match({TokenType::UNSAFE})) {
        return unsafeBlock();
    }
    if (match({TokenType::CONTRACT})) {
        return contractStatement();
    }
    if (match({TokenType::COMPTIME})) {
        return comptimeStatement();
    }

    return expressionStatement();
}

std::shared_ptr<AST::Statement> Parser::expressionStatement() {
    auto expr = expression();
    consume(TokenType::SEMICOLON, "Expected ';' after expression.");

    auto stmt = std::make_shared<AST::ExprStatement>();
    stmt->line = expr->line;
    stmt->expression = expr;
    return stmt;
}

std::shared_ptr<AST::Statement> Parser::printStatement() {
    auto stmt = std::make_shared<AST::PrintStatement>();
    stmt->line = previous().line;

    // Parse arguments
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'print'.");

    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            stmt->arguments.push_back(expression());
        } while (match({TokenType::COMMA}));
    }

    consume(TokenType::RIGHT_PAREN, "Expected ')' after print arguments.");
    consume(TokenType::SEMICOLON, "Expected ';' after print statement.");

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::traitDeclaration() {
    // Create a new trait declaration statement
    auto traitDecl = std::make_shared<AST::TraitDeclaration>();
    traitDecl->line = previous().line;

    // Check for @open annotation
    if (match({TokenType::AT_SIGN})) {
        Token annotation = consume(TokenType::IDENTIFIER, "Expected annotation name after '@'.");
        if (annotation.lexeme == "open") {
            traitDecl->isOpen = true;
        }
    }

    // Parse trait name
    Token name = consume(TokenType::IDENTIFIER, "Expected trait name.");
    traitDecl->name = name.lexeme;

    // Parse trait body
    consume(TokenType::LEFT_BRACE, "Expected '{' before trait body.");

    // Parse trait methods
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        if (match({TokenType::FN})) {
            auto method = function("method");
            traitDecl->methods.push_back(method);
        } else {
            error("Expected method declaration in trait.");
            break;
        }
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after trait body.");

    return traitDecl;
}

std::shared_ptr<AST::Statement> Parser::interfaceDeclaration() {
    // Create a new interface declaration statement
    auto interfaceDecl = std::make_shared<AST::InterfaceDeclaration>();
    interfaceDecl->line = previous().line;

    // Check for @open annotation
    if (match({TokenType::AT_SIGN})) {
        Token annotation = consume(TokenType::IDENTIFIER, "Expected annotation name after '@'.");
        if (annotation.lexeme == "open") {
            interfaceDecl->isOpen = true;
        }
    }

    // Parse interface name
    Token name = consume(TokenType::IDENTIFIER, "Expected interface name.");
    interfaceDecl->name = name.lexeme;

    // Parse interface body
    consume(TokenType::LEFT_BRACE, "Expected '{' before interface body.");

    // Parse interface methods
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        if (match({TokenType::FN})) {
            auto method = function("method");
            interfaceDecl->methods.push_back(method);
        } else {
            error("Expected method declaration in interface.");
            break;
        }
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after interface body.");

    return interfaceDecl;
}

std::shared_ptr<AST::Statement> Parser::moduleDeclaration() {
    // Create a new module declaration statement
    auto moduleDecl = std::make_shared<AST::ModuleDeclaration>();
    moduleDecl->line = previous().line;

    // Parse module name
    Token name = consume(TokenType::IDENTIFIER, "Expected module name.");
    moduleDecl->name = name.lexeme;

    // Parse module body
    consume(TokenType::LEFT_BRACE, "Expected '{' before module body.");

    // Parse module members
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        // Check for visibility annotations
        bool isPublic = false;
        bool isProtected = false;

        if (match({TokenType::AT_SIGN})) {
            Token annotation = consume(TokenType::IDENTIFIER, "Expected annotation name after '@'.");
            if (annotation.lexeme == "public") {
                isPublic = true;
            } else if (annotation.lexeme == "protected") {
                isProtected = true;
            }
        }

        // Parse module member
        auto member = declaration();
        if (member) {
            if (isPublic) {
                moduleDecl->publicMembers.push_back(member);
            } else if (isProtected) {
                moduleDecl->protectedMembers.push_back(member);
            } else {
                moduleDecl->privateMembers.push_back(member);
            }
        }
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after module body.");

    return moduleDecl;
}

std::shared_ptr<AST::Statement> Parser::iterStatement() {
    auto stmt = std::make_shared<AST::IterStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'iter'.");

    // Parse loop variables
    if (match({TokenType::VAR})) {
        // Variable declaration in loop
        Token name = consume(TokenType::IDENTIFIER, "Expected variable name.");
        stmt->loopVars.push_back(name.lexeme);

        // Check for multiple variables (key, value)
        if (match({TokenType::COMMA})) {
            Token secondVar = consume(TokenType::IDENTIFIER, "Expected second variable name after comma.");
            stmt->loopVars.push_back(secondVar.lexeme);
        }

        consume(TokenType::IN, "Expected 'in' after loop variables.");
        stmt->iterable = expression();
    } else if (match({TokenType::IDENTIFIER})) {
        // Identifier directly
        std::string firstVar = previous().lexeme;
        stmt->loopVars.push_back(firstVar);

        // Check for multiple variables (key, value)
        if (match({TokenType::COMMA})) {
            Token secondVar = consume(TokenType::IDENTIFIER, "Expected second variable name after comma.");
            stmt->loopVars.push_back(secondVar.lexeme);

            consume(TokenType::IN, "Expected 'in' after loop variables.");
            stmt->iterable = expression();
        } else if (match({TokenType::IN})) {
            stmt->iterable = expression();
        } else {
            error("Expected 'in' after loop variable.");
        }
    } else {
        error("Expected variable name or identifier after 'iter ('.");
    }

            std::string firstVar = peek().lexeme;
            std::cout << "Current token in iter: "<< firstVar <<" at line "<< peek().line<< std::endl;
    consume(TokenType::RIGHT_PAREN, "Expected ')' after iter clauses.");

    // Parse loop body
    stmt->body = statement();

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::unsafeBlock() {
    auto stmt = std::make_shared<AST::UnsafeStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_BRACE, "Expected '{' after 'unsafe'.");
    stmt->body = block();

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::contractStatement() {
    auto stmt = std::make_shared<AST::ContractStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'contract'.");
    stmt->condition = expression();

    if (match({TokenType::COMMA})) {
        // Parse error message
        if (match({TokenType::STRING})) {
            auto literalExpr = std::make_shared<AST::LiteralExpr>();
            literalExpr->line = previous().line;
            literalExpr->value = previous().lexeme;
            stmt->message = literalExpr;
        } else {
            stmt->message = expression();
        }
    }

    consume(TokenType::RIGHT_PAREN, "Expected ')' after contract condition.");
    consume(TokenType::SEMICOLON, "Expected ';' after contract statement.");

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::comptimeStatement() {
    auto stmt = std::make_shared<AST::ComptimeStatement>();
    stmt->line = previous().line;

    // Parse the declaration that should be evaluated at compile time
    stmt->declaration = declaration();

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::ifStatement() {
    auto stmt = std::make_shared<AST::IfStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'if'.");
    stmt->condition = expression();
    consume(TokenType::RIGHT_PAREN, "Expected ')' after if condition.");

    stmt->thenBranch = statement();

    if (match({TokenType::ELSE})) {
        stmt->elseBranch = statement();
    }

    return stmt;
}

std::shared_ptr<AST::BlockStatement> Parser::block() {
    auto block = std::make_shared<AST::BlockStatement>();
    block->line = previous().line;

    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        auto declaration = this->declaration();
        if (declaration) {
            block->statements.push_back(declaration);
        }
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after block.");
    return block;
}

std::shared_ptr<AST::Statement> Parser::forStatement() {
    auto stmt = std::make_shared<AST::ForStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'for'.");

    // Check for the type of for loop
    if (match({TokenType::VAR})) {
        // Could be either traditional or iterable loop
        Token name = consume(TokenType::IDENTIFIER, "Expected variable name.");

        if (match({TokenType::IN})) {
            // Iterable loop: for (var i in range(10))
            stmt->isIterableLoop = true;
            stmt->loopVars.push_back(name.lexeme);
            stmt->iterable = expression();
        } else {
            // Traditional loop: for (var i = 0; i < 5; i++)
            auto initializer = std::make_shared<AST::VarDeclaration>();
            initializer->line = name.line;
            initializer->name = name.lexeme;

            // Parse optional type annotation
            if (match({TokenType::COLON})) {
                initializer->type = parseTypeAnnotation();
            }

            // Parse initializer
            if (match({TokenType::EQUAL})) {
                initializer->initializer = expression();
            }

            stmt->initializer = initializer;

            consume(TokenType::SEMICOLON, "Expected ';' after loop initializer.");

            // Parse condition
            if (!check(TokenType::SEMICOLON)) {
                stmt->condition = expression();
            }

            consume(TokenType::SEMICOLON, "Expected ';' after loop condition.");

            // Parse increment
            if (!check(TokenType::RIGHT_PAREN)) {
                stmt->increment = expression();
            }
        }
    } else if (match({TokenType::IDENTIFIER})) {
        // Check if it's an iterable loop with multiple variables
        std::string firstVar = previous().lexeme;

        if (match({TokenType::COMMA})) {
            // Multiple variables: for (key, value in dict)
            stmt->isIterableLoop = true;
            stmt->loopVars.push_back(firstVar);

            Token secondVar = consume(TokenType::IDENTIFIER, "Expected second variable name after comma.");
            stmt->loopVars.push_back(secondVar.lexeme);

            consume(TokenType::IN, "Expected 'in' after loop variables.");
            stmt->iterable = expression();
        } else if (match({TokenType::IN})) {
            // Single variable: for (key in list)
            stmt->isIterableLoop = true;
            stmt->loopVars.push_back(firstVar);
            stmt->iterable = expression();
        } else {
            // Traditional loop with an expression as initializer
            current--; // Rewind to re-parse the identifier
            stmt->initializer = expressionStatement();

            // Parse condition
            if (!check(TokenType::SEMICOLON)) {
                stmt->condition = expression();
            }

            consume(TokenType::SEMICOLON, "Expected ';' after loop condition.");

            // Parse increment
            if (!check(TokenType::RIGHT_PAREN)) {
                stmt->increment = expression();
            }
        }
    } else if (!match({TokenType::SEMICOLON})) {
        // Traditional loop with an expression as initializer
        stmt->initializer = expressionStatement();

        // Parse condition
        if (!check(TokenType::SEMICOLON)) {
            stmt->condition = expression();
        }

        consume(TokenType::SEMICOLON, "Expected ';' after loop condition.");

        // Parse increment
        if (!check(TokenType::RIGHT_PAREN)) {
            stmt->increment = expression();
        }
    } else {
        // Traditional loop with no initializer
        // Parse condition
        if (!check(TokenType::SEMICOLON)) {
            stmt->condition = expression();
        }

        consume(TokenType::SEMICOLON, "Expected ';' after loop condition.");

        // Parse increment
        if (!check(TokenType::RIGHT_PAREN)) {
            stmt->increment = expression();
        }
    }

            std::string firstVar = peek().lexeme;
            std::cout << "Current token in for: "<< firstVar << std::endl;
    consume(TokenType::RIGHT_PAREN, "Expected ')' after for clauses.");
    stmt->body = statement();

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::whileStatement() {
    auto stmt = std::make_shared<AST::WhileStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'while'.");
    stmt->condition = expression();
    consume(TokenType::RIGHT_PAREN, "Expected ')' after while condition.");

    stmt->body = statement();

    return stmt;
}

std::shared_ptr<AST::FunctionDeclaration> Parser::function(const std::string& kind) {
    auto func = std::make_shared<AST::FunctionDeclaration>();
    func->line = previous().line;

    // Parse function name
    Token name = consume(TokenType::IDENTIFIER, "Expected " + kind + " name.");
    func->name = name.lexeme;

    // Check for generic parameters
    if (match({TokenType::LEFT_BRACKET})) {
        do {
            func->genericParams.push_back(consume(TokenType::IDENTIFIER, "Expected generic parameter name.").lexeme);
        } while (match({TokenType::COMMA}));

        consume(TokenType::RIGHT_BRACKET, "Expected ']' after generic parameters.");
    }

    consume(TokenType::LEFT_PAREN, "Expected '(' after " + kind + " name.");

    // Parse parameters
    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            auto paramName = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;

            // Parse parameter type
            consume(TokenType::COLON, "Expected ':' after parameter name.");
            auto paramType = parseTypeAnnotation();

            // Check if parameter is optional
            if (paramType.isOptional) {
                // Parse default value if provided
                std::shared_ptr<AST::Expression> defaultValue = nullptr;
                if (match({TokenType::EQUAL})) {
                    defaultValue = expression();
                }

                func->optionalParams.push_back({paramName, {paramType, defaultValue}});
            } else {
                func->params.push_back({paramName, paramType});
            }
        } while (match({TokenType::COMMA}));
    }

    consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters.");

    // Parse return type
    if (match({TokenType::COLON})) {
        func->returnType = parseTypeAnnotation();
    }

    // Check if function throws
    if (match({TokenType::THROWS})) {
        func->throws = true;
    }

    // Parse function body
    consume(TokenType::LEFT_BRACE, "Expected '{' before " + kind + " body.");
    func->body = block();

    return func;
}

std::shared_ptr<AST::Statement> Parser::returnStatement() {
    auto stmt = std::make_shared<AST::ReturnStatement>();
    stmt->line = previous().line;

    if (!check(TokenType::SEMICOLON)) {
        stmt->value = expression();
    }

    consume(TokenType::SEMICOLON, "Expected ';' after return value.");

    return stmt;
}

std::shared_ptr<AST::ClassDeclaration> Parser::classDeclaration() {
    auto classDecl = std::make_shared<AST::ClassDeclaration>();
    classDecl->line = previous().line;

    // Parse class name
    Token name = consume(TokenType::IDENTIFIER, "Expected class name.");
    classDecl->name = name.lexeme;

    consume(TokenType::LEFT_BRACE, "Expected '{' before class body.");

    // Parse class members
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        if (match({TokenType::VAR})) {
            // Parse field
            auto field = std::dynamic_pointer_cast<AST::VarDeclaration>(varDeclaration());
            if (field) {
                classDecl->fields.push_back(field);
            }
        } else if (match({TokenType::FN})) {
            // Parse method
            auto method = function("method");
            if (method) {
                classDecl->methods.push_back(method);
            }
        } else {
            error("Expected class member declaration.");
            break;
        }
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after class body.");

    return classDecl;
}

std::shared_ptr<AST::Statement> Parser::attemptStatement() {
    auto stmt = std::make_shared<AST::AttemptStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_BRACE, "Expected '{' after 'attempt'.");
    stmt->tryBlock = block();

    // Parse handlers
    while (match({TokenType::HANDLE})) {
        AST::HandleClause handler;

        // Parse error type
        handler.errorType = consume(TokenType::IDENTIFIER, "Expected error type after 'handle'.").lexeme;

        // Parse optional error variable
        if (match({TokenType::LEFT_PAREN})) {
            handler.errorVar = consume(TokenType::IDENTIFIER, "Expected error variable name.").lexeme;
            consume(TokenType::RIGHT_PAREN, "Expected ')' after error variable.");
        }

        // Parse handler body
        consume(TokenType::LEFT_BRACE, "Expected '{' after handle clause.");
        handler.body = block();

        stmt->handlers.push_back(handler);
    }

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::parallelStatement() {
    auto stmt = std::make_shared<AST::ParallelStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_BRACE, "Expected '{' after 'parallel'.");
    stmt->body = block();

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::concurrentStatement() {
    auto stmt = std::make_shared<AST::ConcurrentStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_BRACE, "Expected '{' after 'concurrent'.");
    stmt->body = block();

    return stmt;
}

std::shared_ptr<AST::Statement> Parser::importStatement() {
    auto stmt = std::make_shared<AST::ImportStatement>();
    stmt->line = previous().line;

    stmt->module = consume(TokenType::IDENTIFIER, "Expected module name after 'import'.").lexeme;
    consume(TokenType::SEMICOLON, "Expected ';' after import statement.");

    return stmt;
}

std::shared_ptr<AST::EnumDeclaration> Parser::enumDeclaration() {
    auto enumDecl = std::make_shared<AST::EnumDeclaration>();
    enumDecl->line = previous().line;

    // Parse enum name
    Token name = consume(TokenType::IDENTIFIER, "Expected enum name.");
    enumDecl->name = name.lexeme;

    consume(TokenType::LEFT_BRACE, "Expected '{' before enum body.");

    // Parse enum variants
    if (!check(TokenType::RIGHT_BRACE)) {
        do {
            std::string variantName = consume(TokenType::IDENTIFIER, "Expected variant name.").lexeme;

            std::optional<AST::TypeAnnotation> variantType;
            if (match({TokenType::LEFT_PAREN})) {
                variantType = parseTypeAnnotation();
                consume(TokenType::RIGHT_PAREN, "Expected ')' after variant type.");
            }

            enumDecl->variants.push_back({variantName, variantType});
        } while (match({TokenType::COMMA}));
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after enum body.");

    return enumDecl;
}

std::shared_ptr<AST::Statement> Parser::matchStatement() {
    auto stmt = std::make_shared<AST::MatchStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'match'.");
    stmt->value = expression();
    consume(TokenType::RIGHT_PAREN, "Expected ')' after match value.");

    consume(TokenType::LEFT_BRACE, "Expected '{' before match cases.");

    // Parse match cases
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        AST::MatchCase matchCase;

        // Parse pattern
        matchCase.pattern = expression();
        consume(TokenType::COLON, "Expected ':' after match pattern.");

        // Parse case body
        matchCase.body = statement();

        stmt->cases.push_back(matchCase);
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after match cases.");

    return stmt;
}

// Expression parsing methods
std::shared_ptr<AST::Expression> Parser::expression() {
    return assignment();
}

std::shared_ptr<AST::Expression> Parser::assignment() {
    auto expr = logicalOr();

    if (match({TokenType::EQUAL})) {
        auto equals = previous();
        auto value = assignment();

        if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
            auto assignExpr = std::make_shared<AST::AssignExpr>();
            assignExpr->line = equals.line;
            assignExpr->name = varExpr->name;
            assignExpr->value = value;
            return assignExpr;
        }

        error("Invalid assignment target.");
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::logicalOr() {
    auto expr = logicalAnd();

    while (match({TokenType::OR})) {
        auto op = previous();
        auto right = logicalAnd();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::logicalAnd() {
    auto expr = equality();

    while (match({TokenType::AND})) {
        auto op = previous();
        auto right = equality();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::equality() {
    auto expr = comparison();

    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        auto op = previous();
        auto right = comparison();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::comparison() {
    auto expr = term();

    // Check for range expressions (e.g., 1..10)
    if (match({TokenType::RANGE})) {
        auto rangeExpr = std::make_shared<AST::RangeExpr>();
        rangeExpr->line = previous().line;
        rangeExpr->start = expr;
        rangeExpr->end = term();
        rangeExpr->step = nullptr; // No step value for now
        rangeExpr->inclusive = true; // Default to inclusive range
        return rangeExpr;
    }

    while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
        auto op = previous();
        auto right = term();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::term() {
    auto expr = factor();

    while (match({TokenType::MINUS, TokenType::PLUS})) {
        auto op = previous();
        auto right = factor();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::factor() {
    auto expr = unary();

    while (match({TokenType::SLASH, TokenType::STAR, TokenType::MODULUS})) {
        auto op = previous();
        auto right = unary();

        auto binaryExpr = std::make_shared<AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::unary() {
    if (match({TokenType::BANG, TokenType::MINUS})) {
        auto op = previous();
        auto right = unary();

        auto unaryExpr = std::make_shared<AST::UnaryExpr>();
        unaryExpr->line = op.line;
        unaryExpr->op = op.type;
        unaryExpr->right = right;

        return unaryExpr;
    }

    if (match({TokenType::AWAIT})) {
        auto awaitExpr = std::make_shared<AST::AwaitExpr>();
        awaitExpr->line = previous().line;
        awaitExpr->expression = unary();
        return awaitExpr;
    }

    return call();
}

std::shared_ptr<AST::Expression> Parser::call() {
    auto expr = primary();

    while (true) {
        if (match({TokenType::LEFT_PAREN})) {
            expr = finishCall(expr);
        } else if (match({TokenType::DOT})) {
            auto name = consume(TokenType::IDENTIFIER, "Expected property name after '.'.");

            auto memberExpr = std::make_shared<AST::MemberExpr>();
            memberExpr->line = name.line;
            memberExpr->object = expr;
            memberExpr->name = name.lexeme;

            expr = memberExpr;
        } else if (match({TokenType::LEFT_BRACKET})) {
            auto index = expression();
            consume(TokenType::RIGHT_BRACKET, "Expected ']' after index.");

            auto indexExpr = std::make_shared<AST::IndexExpr>();
            indexExpr->line = previous().line;
            indexExpr->object = expr;
            indexExpr->index = index;

            expr = indexExpr;
        } else {
            break;
        }
    }

    return expr;
}

std::shared_ptr<AST::Expression> Parser::finishCall(std::shared_ptr<AST::Expression> callee) {
    std::vector<std::shared_ptr<AST::Expression>> arguments;
    std::unordered_map<std::string, std::shared_ptr<AST::Expression>> namedArgs;

    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            // Check for named arguments
            if (check(TokenType::IDENTIFIER) && peek().lexeme.length() > 0) {
                Token nameToken = peek();
                advance();

                if (match({TokenType::EQUAL})) {
                    // This is a named argument
                    auto argValue = expression();
                    namedArgs[nameToken.lexeme] = argValue;
                    continue;
                } else {
                    // Not a named argument, rewind and parse as regular expression
                    current--; // Rewind to before the identifier
                }
            }

            // Regular positional argument
            arguments.push_back(expression());
        } while (match({TokenType::COMMA}));
    }

    auto paren = consume(TokenType::RIGHT_PAREN, "Expected ')' after arguments.");

    auto callExpr = std::make_shared<AST::CallExpr>();
    callExpr->line = paren.line;
    callExpr->callee = callee;
    callExpr->arguments = arguments;
    callExpr->namedArgs = namedArgs;

    return callExpr;
}

std::shared_ptr<AST::Expression> Parser::primary() {
    if (match({TokenType::FALSE})) {
        auto literalExpr = std::make_shared<AST::LiteralExpr>();
        literalExpr->line = previous().line;
        literalExpr->value = false;
        return literalExpr;
    }

    if (match({TokenType::TRUE})) {
        auto literalExpr = std::make_shared<AST::LiteralExpr>();
        literalExpr->line = previous().line;
        literalExpr->value = true;
        return literalExpr;
    }

    if (match({TokenType::NONE})) {
        auto literalExpr = std::make_shared<AST::LiteralExpr>();
        literalExpr->line = previous().line;
        literalExpr->value = nullptr;
        return literalExpr;
    }

    if (match({TokenType::NUMBER})) {
        auto token = previous();
        auto literalExpr = std::make_shared<AST::LiteralExpr>();
        literalExpr->line = token.line;

        // Check if the number is an integer or a float
        if (token.lexeme.find('.') != std::string::npos) {
            literalExpr->value = std::stod(token.lexeme);
        } else {
            literalExpr->value = std::stoi(token.lexeme);
        }

        return literalExpr;
    }

    if (match({TokenType::STRING})) {
        auto literalExpr = std::make_shared<AST::LiteralExpr>();
        literalExpr->line = previous().line;
        literalExpr->value = previous().lexeme;
        return literalExpr;
    }

    if (match({TokenType::IDENTIFIER})) {
        auto varExpr = std::make_shared<AST::VariableExpr>();
        varExpr->line = previous().line;
        varExpr->name = previous().lexeme;
        return varExpr;
    }

    if (match({TokenType::LEFT_PAREN})) {
        auto expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expected ')' after expression.");

        auto groupingExpr = std::make_shared<AST::GroupingExpr>();
        groupingExpr->line = previous().line;
        groupingExpr->expression = expr;

        return groupingExpr;
    }

    if (match({TokenType::LEFT_BRACKET})) {
        // Parse list literal
        std::vector<std::shared_ptr<AST::Expression>> elements;

        if (!check(TokenType::RIGHT_BRACKET)) {
            do {
                elements.push_back(expression());
            } while (match({TokenType::COMMA}));
        }

        consume(TokenType::RIGHT_BRACKET, "Expected ']' after list elements.");

        auto listExpr = std::make_shared<AST::ListExpr>();
        listExpr->line = previous().line;
        listExpr->elements = elements;

        return listExpr;
    }

    if(match({})){

    }

    if (match({TokenType::LEFT_BRACE})) {
        // Parse dictionary literal
        std::vector<std::pair<std::shared_ptr<AST::Expression>, std::shared_ptr<AST::Expression>>> entries;

        if (!check(TokenType::RIGHT_BRACE)) {
            do {
                auto key = expression();
                consume(TokenType::COLON, "Expected ':' after dictionary key.");
                auto value = expression();

                entries.push_back({key, value});
            } while (match({TokenType::COMMA}));
        }

        consume(TokenType::RIGHT_BRACE, "Expected '}' after dictionary entries.");

        auto dictExpr = std::make_shared<AST::DictExpr>();
        dictExpr->line = previous().line;
        dictExpr->entries = entries;

        return dictExpr;
    }

    error("Expected expression.");
    throw std::runtime_error("Expected expression.");
}

std::shared_ptr<AST::Statement> Parser::typeDeclaration() {
    // Create a new type declaration statement
    auto typeDecl = std::make_shared<AST::TypeDeclaration>();
    typeDecl->line = previous().line;

    // Parse type name
    Token name = consume(TokenType::IDENTIFIER, "Expected type name.");
    std::cout <<"Type name: " << name.lexeme << std::endl;
    typeDecl->name = name.lexeme;

    // Parse equals sign
    consume(TokenType::EQUAL, "Expected '=' after type name.");

    // Parse type definition
    typeDecl->type = parseTypeAnnotation();

    // Parse optional semicolon
    match({TokenType::SEMICOLON});

    return typeDecl;
}

// Type annotation parsing
AST::TypeAnnotation Parser::parseTypeAnnotation() {
    AST::TypeAnnotation type;

    type.typeName = consume(TokenType::IDENTIFIER, "Expected type name.").lexeme;

    // Check for optional type
    if (match({TokenType::QUESTION})) {
        type.isOptional = true;
    }

    // Check for generic type parameters
    if (match({TokenType::LESS})) {
        do {
            type.genericParams.push_back(parseTypeAnnotation());
        } while (match({TokenType::COMMA}));

        consume(TokenType::GREATER, "Expected '>' after generic parameters.");
    }

    return type;
}



#include "parser.hh"
#include "../debugger.hh"
#include <stdexcept>

// Helper methods
Token Parser::peek() {
    return scanner.getTokens()[current];
}

Token Parser::previous() {
    return scanner.getTokens()[current - 1];
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

void Parser::error(const std::string &message, bool suppressException) {
    // Get the current token's lexeme for better error reporting
    std::string lexeme = "";
    int line = 0;
    int column = 0;
    std::string codeContext = "";
    
    if (current < scanner.getTokens().size()) {
        Token currentToken = peek();
        lexeme = currentToken.lexeme;
        line = currentToken.line;
        column = currentToken.start;
        // Extract code context (source line)
        if (line > 0) {
            const std::string& src = scanner.getSource();
            size_t srcLen = src.length();
            size_t lineStart = 0, lineEnd = srcLen;
            int curLine = 1;
            for (size_t i = 0; i < srcLen; ++i) {
                if (curLine == line) {
                    lineStart = i;
                    while (lineStart > 0 && src[lineStart - 1] != '\n') --lineStart;
                    lineEnd = i;
                    while (lineEnd < srcLen && src[lineEnd] != '\n') ++lineEnd;
                    codeContext = src.substr(lineStart, lineEnd - lineStart);
                    break;
                }
                if (src[i] == '\n') ++curLine;
            }
        }
    }
    
    // Check if this is an "Expected expression" error in a trait method
    if (message == "Expected expression." && 
        (current > 0 && current < scanner.getTokens().size() && 
         scanner.getTokens()[current-1].type == TokenType::LEFT_BRACE && 
         scanner.getTokens()[current].type == TokenType::RIGHT_BRACE)) {
        // Let the debugger handle this common case
        Debugger::error(message, line, column, InterpretationStage::PARSING, "", lexeme, codeContext);
        return;
    }
    
    Debugger::error(message, line, column, InterpretationStage::PARSING, "", lexeme, codeContext);

    // Collect error for multi-error reporting
    errors.push_back(ParseError{message, line, column, codeContext});
    if (errors.size() >= MAX_ERRORS) {
        throw std::runtime_error("Too many syntax errors; aborting parse.");
    }

    // Do not throw for normal errors; let parser continue and synchronize.
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

    // After parsing, print all collected errors if any
    if (!errors.empty()) {
        std::cerr << "\n--- Syntax Errors ---\n";
        for (const auto& err : errors) {
            std::cerr << "[Line " << err.line << ", Col " << err.column << "]: " << err.message << "\n";
            if (!err.codeContext.empty()) {
                std::cerr << "    " << err.codeContext << "\n";
            }
        }
        std::cerr << "---------------------\n";
    }
    return program;
}

// Parse declarations
// Helper to collect leading annotations
std::vector<Token> Parser::collectAnnotations() {
    std::vector<Token> annotations;
    while (check(TokenType::PUBLIC) || check(TokenType::PRIVATE) || check(TokenType::PROTECTED)) {
        annotations.push_back(advance());
    }
    return annotations;
}

std::shared_ptr<AST::Statement> Parser::declaration() {
    try {
        // Collect leading annotations
        std::vector<Token> annotations = collectAnnotations();
        if (match({TokenType::CLASS})) {
            auto decl = classDeclaration();
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::FN})) {
            auto decl = function("function");
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::ASYNC})) {
            consume(TokenType::FN, "Expected 'fn' after 'async'.");
            auto asyncFn = std::make_shared<AST::AsyncFunctionDeclaration>(*function("async function"));
            asyncFn->annotations = annotations;
            return asyncFn;
        }
        if (match({TokenType::VAR})) {
            auto decl = varDeclaration();
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::ENUM})) {
            auto decl = enumDeclaration();
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::IMPORT})) {
            auto decl = importStatement();
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::TYPE})) {
            auto decl = typeDeclaration();
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::TRAIT})) {
            auto decl = traitDeclaration();
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::INTERFACE})) {
            auto decl = interfaceDeclaration();
            if (decl) decl->annotations = annotations;
            return decl;
        }
        if (match({TokenType::MODULE})) {
            auto decl = moduleDeclaration();
            if (decl) decl->annotations = annotations;
            return decl;
        }

        auto stmt = statement();
        if (stmt) stmt->annotations = annotations;
        return stmt;
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
        // Parse the type annotation - all type handling is done in parseTypeAnnotation
        var->type = parseTypeAnnotation();
    }

    // Parse optional initializer
    if (match({TokenType::EQUAL})) {
        var->initializer = expression();
    }

    // Make semicolon optional
    match({TokenType::SEMICOLON});
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
    try {
        auto expr = expression();
        // Make semicolon optional
        match({TokenType::SEMICOLON});

        auto stmt = std::make_shared<AST::ExprStatement>();
        stmt->line = expr->line;
        stmt->expression = expr;
        return stmt;
    } catch (const std::exception &e) {
        // If we can't parse an expression, return an empty statement
        auto stmt = std::make_shared<AST::ExprStatement>();
        stmt->line = peek().line;
        stmt->expression = nullptr;
        return stmt;
    }
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
    // Make semicolon optional
    match({TokenType::SEMICOLON});
    return stmt;
}

std::shared_ptr<AST::Statement> Parser::traitDeclaration() {
    // Create a new trait declaration statement
    auto traitDecl = std::make_shared<AST::TraitDeclaration>();
    traitDecl->line = previous().line;

    // Check for @open annotation
    if (match({TokenType::OPEN})) {
        traitDecl->isOpen = true;
    }

    // Parse trait name
    Token name = consume(TokenType::IDENTIFIER, "Expected trait name.");
    traitDecl->name = name.lexeme;

    // Parse trait body
    consume(TokenType::LEFT_BRACE, "Expected '{' before trait body.");

    // Parse trait methods
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        if (match({TokenType::FN})) {
            // For traits, we need to handle method declarations that might not have bodies
            auto method = std::make_shared<AST::FunctionDeclaration>();
            method->line = previous().line;
            
            // Parse function name
            Token name = consume(TokenType::IDENTIFIER, "Expected method name.");
            method->name = name.lexeme;
            
            consume(TokenType::LEFT_PAREN, "Expected '(' after method name.");
            
            // Parse parameters
            if (!check(TokenType::RIGHT_PAREN)) {
                do {
                    auto paramName = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;
                    
                    // Parse parameter type
                    consume(TokenType::COLON, "Expected ':' after parameter name.");
                    auto paramType = parseTypeAnnotation();
                    
                    method->params.push_back({paramName, paramType});
                } while (match({TokenType::COMMA}));
            }
            
            consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters.");
            
            // Parse return type
            if (match({TokenType::COLON})) {
                method->returnType = parseTypeAnnotation();
            }
            
            // Check if there's a semicolon (no body) or a brace (with body)
            if (match({TokenType::SEMICOLON})) {
                // Method declaration without body (interface/trait style)
                method->body = std::make_shared<AST::BlockStatement>();
                method->body->line = method->line;
            } else {
                // Method with body
                consume(TokenType::LEFT_BRACE, "Expected '{' or ';' after method declaration.");
                method->body = block();
            }
            
            traitDecl->methods.push_back(method);
        } else {
            error("Expected method declaration in trait.");
            // Create a placeholder expression to allow parsing to continue
            auto errorExpr = std::make_shared<AST::LiteralExpr>();
            errorExpr->line = peek().line;
            errorExpr->value = nullptr; // Use null as a placeholder
            // return errorExpr;
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

    // Handle empty blocks
    if (check(TokenType::RIGHT_BRACE)) {
        consume(TokenType::RIGHT_BRACE, "Expected '}' after block.");
        return block;
    }

    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        try {
            // Try to parse a declaration
            auto declaration = this->declaration();
            if (declaration) {
                block->statements.push_back(declaration);
            }
        } catch (const std::exception &e) {
            // Skip invalid statements and continue parsing
            synchronize();
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
            if (paramType->isOptional) {
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

    if (!check(TokenType::SEMICOLON) && !check(TokenType::RIGHT_BRACE)) {
        stmt->value = expression();
    }

    // Make semicolon optional
    match({TokenType::SEMICOLON});

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
        } else if (check(TokenType::IDENTIFIER) && peek().lexeme == classDecl->name) {
            // Parse constructor
            advance(); // Consume the class name
            auto constructor = std::make_shared<AST::FunctionDeclaration>();
            constructor->line = previous().line;
            constructor->name = classDecl->name;
            
            consume(TokenType::LEFT_PAREN, "Expected '(' after constructor name.");
            
            // Parse parameters
            if (!check(TokenType::RIGHT_PAREN)) {
                do {
                    auto paramName = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;
                    
                    // Parse parameter type
                    consume(TokenType::COLON, "Expected ':' after parameter name.");
                    auto paramType = parseTypeAnnotation();
                    
                    constructor->params.push_back({paramName, paramType});
                } while (match({TokenType::COMMA}));
            }
            
            consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters.");
            
            // Parse constructor body
            consume(TokenType::LEFT_BRACE, "Expected '{' before constructor body.");
            constructor->body = block();
            
            classDecl->methods.push_back(constructor);
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

            std::optional<std::shared_ptr<AST::TypeAnnotation>> variantType;
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

// Parse match statement: match(value) { pattern => expr, ... }
std::shared_ptr<AST::Statement> Parser::matchStatement() {
    auto stmt = std::make_shared<AST::MatchStatement>();
    stmt->line = previous().line;

    consume(TokenType::LEFT_PAREN, "Expected '(' after 'match'.");
    stmt->value = expression();
    consume(TokenType::RIGHT_PAREN, "Expected ')' after match value.");

    consume(TokenType::LEFT_BRACE, "Expected '{' before match cases.");

    // Parse match cases: pattern => expr, ...
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        AST::MatchCase matchCase;
        // Parse pattern
        matchCase.pattern = expression();
        consume(TokenType::ARROW, "Expected '=>' after match pattern.");
        // Parse body as a single expression (not statement)
        matchCase.body = std::make_shared<AST::ExprStatement>();
        std::static_pointer_cast<AST::ExprStatement>(matchCase.body)->expression = expression();
        // Optional comma between cases
        if (match({TokenType::COMMA})) {
            // Allow trailing comma before '}'
            if (check(TokenType::RIGHT_BRACE)) break;
        }
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

    if (match({TokenType::EQUAL, TokenType::PLUS_EQUAL, TokenType::MINUS_EQUAL,
               TokenType::STAR_EQUAL, TokenType::SLASH_EQUAL, TokenType::MODULUS_EQUAL})) {
        auto op = previous();
        auto value = assignment();

        if (auto varExpr = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
            auto assignExpr = std::make_shared<AST::AssignExpr>();
            assignExpr->line = op.line;
            assignExpr->name = varExpr->name;
            assignExpr->op = op.type;
            assignExpr->value = value;
            return assignExpr;
        } else if (auto memberExpr = std::dynamic_pointer_cast<AST::MemberExpr>(expr)) {
            auto assignExpr = std::make_shared<AST::AssignExpr>();
            assignExpr->line = op.line;
            assignExpr->object = memberExpr->object;
            assignExpr->member = memberExpr->name;
            assignExpr->op = op.type;
            assignExpr->value = value;
            return assignExpr;
        } else if (auto indexExpr = std::dynamic_pointer_cast<AST::IndexExpr>(expr)) {
            auto assignExpr = std::make_shared<AST::AssignExpr>();
            assignExpr->line = op.line;
            assignExpr->object = indexExpr->object;
            assignExpr->index = indexExpr->index;
            assignExpr->op = op.type;
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
    auto expr = power();

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

std::shared_ptr<AST::Expression> Parser::power() {
    auto expr = unary();
    while (match({TokenType::POWER})) { // Assuming POWER is '**'
        auto op = previous();
        auto right = power(); // Right-associative!
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

std::shared_ptr<AST::InterpolatedStringExpr> Parser::interpolatedString() {
    auto interpolated = std::make_shared<AST::InterpolatedStringExpr>();
    interpolated->line = previous().line;
    
    // The scanner has already tokenized the string into parts
    // We'll process the tokens until we find the closing quote
    while (!isAtEnd() && !check(TokenType::STRING)) {
        if (match({TokenType::INTERPOLATION})) {
            // This is an interpolation start token
            if (check(TokenType::INTERPOLATION) && peek().lexeme == "}") {
                // Empty interpolation, skip it
                advance();
                continue;
            }
            
            // Parse the expression inside the interpolation
            auto expr = expression();
            if (expr) {
                interpolated->addExpressionPart(expr);
            }
            
            // Consume the closing interpolation token
            if (check(TokenType::INTERPOLATION) && peek().lexeme == "}") {
                advance();
            } else {
                error("Expected '}' after expression in string interpolation.");
            }
        } else if (match({TokenType::STRING})) {
            // This is a string literal part
            auto str = previous().lexeme;
            if (!str.empty()) {
                interpolated->addStringPart(str);
            }
        } else {
            // This shouldn't happen if the scanner is working correctly
            error("Unexpected token in interpolated string.");
            break;
        }
    }
    
    // Consume the closing quote if present
    if (check(TokenType::STRING)) {
        advance();
    } else {
        error("Unterminated interpolated string.");
    }
    
    return interpolated;
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
        // Check if this is an interpolated string (starts with a string followed by INTERPOLATION token)
        if (check(TokenType::INTERPOLATION) || 
            (peek().type == TokenType::STRING && current + 1 < scanner.getTokens().size() && 
             scanner.getTokens()[current + 1].type == TokenType::INTERPOLATION)) {
            // This is an interpolated string
            return interpolatedString();
        } else {
            // Regular string literal
            auto literalExpr = std::make_shared<AST::LiteralExpr>();
            literalExpr->line = previous().line;
            literalExpr->value = previous().lexeme;
            return literalExpr;
        }
    }

    if (match({TokenType::IDENTIFIER})) {
        auto token = previous();
        // Check if this is 'self' keyword
        if (token.lexeme == "self") {
            auto thisExpr = std::make_shared<AST::ThisExpr>();
            thisExpr->line = token.line;
            return thisExpr;
        } else {
            auto varExpr = std::make_shared<AST::VariableExpr>();
            varExpr->line = token.line;
            varExpr->name = token.lexeme;
            return varExpr;
        }
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

    // Check if we're in a trait method or other context where an empty expression might be valid
    if (current > 0 && current < scanner.getTokens().size() && 
        scanner.getTokens()[current-1].type == TokenType::LEFT_BRACE && 
        scanner.getTokens()[current].type == TokenType::RIGHT_BRACE) {
        // This is likely an empty block, so we'll create a placeholder expression
        auto placeholderExpr = std::make_shared<AST::LiteralExpr>();
        placeholderExpr->line = peek().line;
        placeholderExpr->value = nullptr; // Use null as a placeholder
        return placeholderExpr;
    } else if (match({TokenType::SELF})) {
        // Handle 'self' as a special case
        auto thisExpr = std::make_shared<AST::ThisExpr>();
        thisExpr->line = previous().line;
        return thisExpr;
    } else {
        // Only report error if we're not at the end of input or at a statement terminator
        if (!isAtEnd() && !check(TokenType::SEMICOLON) && !check(TokenType::RIGHT_BRACE) && 
            !check(TokenType::RIGHT_PAREN) && !check(TokenType::RIGHT_BRACKET)) {
            error("Expected expression.", false);
            advance(); // Move past the error token to avoid infinite loop
        }
        return makeErrorExpr();
    }
}

std::shared_ptr<AST::Statement> Parser::typeDeclaration() {
    // Create a new type declaration statement
    auto typeDecl = std::make_shared<AST::TypeDeclaration>();
    typeDecl->line = previous().line;

    // Parse type name
    Token name = consume(TokenType::IDENTIFIER, "Expected type name.");
    typeDecl->name = name.lexeme;
    
    // Parse equals sign
    consume(TokenType::EQUAL, "Expected '=' after type name.");
    
    // Parse the right-hand side of the type declaration
    
    // For list literals like [any], [str], [Person]
    if (match({TokenType::LEFT_BRACKET})) {
        auto listType = std::make_shared<AST::TypeAnnotation>();
        listType->typeName = "list";
        listType->isList = true;
        
        // Parse element type (e.g., any in [any])
        if (!check(TokenType::RIGHT_BRACKET)) {
            // Parse the element type
            auto elementType = parseTypeAnnotation();
            listType->elementType = elementType;
        } else {
            // Default to any if no element type is specified
            auto anyType = std::make_shared<AST::TypeAnnotation>();
            anyType->typeName = "any";
            anyType->isPrimitive = true;
            listType->elementType = anyType;
        }
        
        consume(TokenType::RIGHT_BRACKET, "Expected ']' after list element type.");
        typeDecl->type = listType;
    }
    // For dictionary literals like {any: any}, {str: str}, {int: User} or structural types like {name: str, age: int}
    else if (match({TokenType::LEFT_BRACE})) {
        // We need to determine if this is a dictionary type or a structural type
        // Dictionary types have the pattern: {KeyType: ValueType} (single key-value pair)
        // Structural types have the pattern: {field: Type, field: Type, ...} (field names)
        
        // Look ahead to determine the type
        size_t savedCurrent = current;
        bool isDictionary = false;
        
        // Check if the first token is a type (for dictionary) or identifier (for field name)
        if (check(TokenType::IDENTIFIER) || isPrimitiveType(peek().type)) {
            Token firstToken = peek();
            advance(); // Consume the first token
            
            if (match({TokenType::COLON})) {
                // We have a colon, now check what comes after
                if (check(TokenType::IDENTIFIER) || isPrimitiveType(peek().type)) {
                    Token secondToken = peek();
                    advance(); // Consume the second token
                    
                    // If we immediately hit a closing brace, it's a dictionary type
                    if (check(TokenType::RIGHT_BRACE)) {
                        isDictionary = true;
                    }
                    // If the first token is a primitive type and second is also a type, it's likely a dictionary
                    else if (isPrimitiveType(firstToken.type) && (isPrimitiveType(secondToken.type) || 
                             secondToken.lexeme == "any" || secondToken.lexeme == "str" || 
                             secondToken.lexeme == "int" || secondToken.lexeme == "float")) {
                        isDictionary = true;
                    }
                }
            }
        }
        
        // Reset the parser position
        current = savedCurrent;
        
        if (isDictionary) {
            // Parse as dictionary type
            auto dictType = std::make_shared<AST::TypeAnnotation>();
            dictType->typeName = "dict";
            dictType->isDict = true;
            
            // Parse key type
            Token keyToken = advance();
            auto keyType = std::make_shared<AST::TypeAnnotation>();
            if (isPrimitiveType(keyToken.type)) {
                keyType->typeName = tokenTypeToString(keyToken.type);
                keyType->isPrimitive = true;
            } else if (keyToken.lexeme == "any") {
                keyType->typeName = "any";
                keyType->isPrimitive = true;
            } else if (keyToken.lexeme == "int") {
                keyType->typeName = "int";
                keyType->isPrimitive = true;
            } else if (keyToken.lexeme == "str") {
                keyType->typeName = "str";
                keyType->isPrimitive = true;
            } else {
                keyType->typeName = keyToken.lexeme;
                keyType->isUserDefined = true;
            }
            
            consume(TokenType::COLON, "Expected ':' in dictionary type.");
            
            // Parse value type
            auto valueType = parseTypeAnnotation();
            
            // Set the key and value types
            dictType->keyType = keyType;
            dictType->valueType = valueType;
            
            consume(TokenType::RIGHT_BRACE, "Expected '}' after dictionary type.");
            typeDecl->type = dictType;
        } else {
            // Parse as structural type
            auto structType = std::make_shared<AST::TypeAnnotation>();
            structType->typeName = "struct";
            structType->isStructural = true;
            
            // Parse fields until we hit a closing brace
            while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
                // Check for rest parameter (...) or extensible record (...baseRecord)
                if (match({TokenType::ELLIPSIS})) {
                    structType->hasRest = true;
                    
                    // Check if there's a base record identifier after ...
                    if (check(TokenType::IDENTIFIER)) {
                        // This is an extensible record with a base record
                        std::string baseRecordName = consume(TokenType::IDENTIFIER, "Expected base record name after '...'.").lexeme;
                        
                        // Store the base record name
                        if (structType->baseRecord.empty()) {
                            structType->baseRecord = baseRecordName;
                        }
                        
                        // Also add to the list of base records for multiple inheritance
                        structType->baseRecords.push_back(baseRecordName);
                    }
                    
                    // Check for comma to continue with more fields
                    if (check(TokenType::COMMA)) {
                        consume(TokenType::COMMA, "Expected ',' after rest parameter.");
                        continue;
                    } else if (check(TokenType::RIGHT_BRACE)) {
                        // End of record definition
                        break;
                    } else {
                        error("Expected ',' or '}' after rest parameter.");
                    }
                }
                
                // Parse field name
                std::string fieldName = consume(TokenType::IDENTIFIER, "Expected field name.").lexeme;
                
                // Parse field type
                consume(TokenType::COLON, "Expected ':' after field name.");
                auto fieldType = parseTypeAnnotation();
                
                // Add field to structural type
                structType->structuralFields.push_back({fieldName, fieldType});
                
                // Check for comma or end of struct
                if (!check(TokenType::RIGHT_BRACE)) {
                    match({TokenType::COMMA}); // Optional comma
                }
            }
            
            consume(TokenType::RIGHT_BRACE, "Expected '}' after structural type.");
            typeDecl->type = structType;
        }
    }
    // For union types like Some | None, Success | Error
    else if (check(TokenType::IDENTIFIER) || isPrimitiveType(peek().type)) {
        // Parse the first type in the union
        auto firstType = parseTypeAnnotation();
        
        // Check if this is a union type (e.g., Some | None)
        if (match({TokenType::PIPE})) {
            // This is a union type
            auto unionType = std::make_shared<AST::TypeAnnotation>();
            unionType->typeName = "union";
            unionType->isUnion = true;
            unionType->unionTypes.push_back(firstType);
            
            // Parse the right side of the union
            do {
                unionType->unionTypes.push_back(parseTypeAnnotation());
            } while (match({TokenType::PIPE}));
            
            typeDecl->type = unionType;
        }
        // Check if this is an intersection type (e.g., HasName and HasAge)
        else if (match({TokenType::AND})) {
            // This is an intersection type
            auto intersectionType = std::make_shared<AST::TypeAnnotation>();
            intersectionType->typeName = "intersection";
            intersectionType->isIntersection = true;
            intersectionType->unionTypes.push_back(firstType);
            
            // Parse the right side of the intersection
            do {
                intersectionType->unionTypes.push_back(parseTypeAnnotation());
            } while (match({TokenType::AND}));
            
            typeDecl->type = intersectionType;
        }
        // Check if this is a refined type (e.g., int where value > 0)
        else if (match({TokenType::WHERE})) {
            // This is a refined type
            firstType->isRefined = true;
            firstType->refinementCondition = expression();
            typeDecl->type = firstType;
        }
        // Otherwise, it's a simple type alias
        else {
            typeDecl->type = firstType;
        }
    }
    // For nil type
    else if (match({TokenType::NIL})) {
        auto nilType = std::make_shared<AST::TypeAnnotation>();
        nilType->typeName = "nil";
        nilType->isPrimitive = true;
        typeDecl->type = nilType;
    }
    else {
        error("Expected type definition after '='.");
    }
    
    // Parse optional semicolon
    match({TokenType::SEMICOLON});
    
    return typeDecl;
}
            
// Type annotation parsing
std::shared_ptr<AST::TypeAnnotation> Parser::parseTypeAnnotation() {
    auto type = std::make_shared<AST::TypeAnnotation>();

    // Check for list types (e.g., [int], [str], [Person])
    if (match({TokenType::LEFT_BRACKET})) {
        type->isList = true;
        type->typeName = "list";
        
        // Parse element type (e.g., int in [int])
        if (!check(TokenType::RIGHT_BRACKET)) {
            // Parse the element type
            type->elementType = parseTypeAnnotation();
        } else {
            // Default to any if no element type is specified
            auto anyType = std::make_shared<AST::TypeAnnotation>();
            anyType->typeName = "any";
            anyType->isPrimitive = true;
            type->elementType = anyType;
        }
        
        consume(TokenType::RIGHT_BRACKET, "Expected ']' after list element type.");
        return type;
    }
    
    // Check for structural types (e.g., { name: str, age: int, ...baseRecord })
    if (match({TokenType::LEFT_BRACE})) {
        // This could be either a structural type or a dictionary type
        
        // For now, treat all { ... } in type declarations as structural types
        // Dictionary types should be explicitly declared with dict<K, V> syntax
        
        // If we get here, it's a structural type
        type->isStructural = true;
        type->typeName = "struct";

        // Parse fields until we hit a closing brace
        while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
            // Check for rest parameter (...) or extensible record (...baseRecord)
            if (match({TokenType::ELLIPSIS})) {
                type->hasRest = true;
                
                // Check if there's a base record identifier after ...
                if (check(TokenType::IDENTIFIER)) {
                    // This is an extensible record with a base record
                    std::string baseRecordName = consume(TokenType::IDENTIFIER, "Expected base record name after '...'.").lexeme;
                    
                    // Store the base record name
                    if (type->baseRecord.empty()) {
                        type->baseRecord = baseRecordName;
                    }
                    
                    // Also add to the list of base records for multiple inheritance
                    type->baseRecords.push_back(baseRecordName);
                }
                
                // Check for comma to continue with more fields
                if (check(TokenType::COMMA)) {
                    consume(TokenType::COMMA, "Expected ',' after rest parameter.");
                    continue;
                } else if (check(TokenType::RIGHT_BRACE)) {
                    // End of record definition
                    break;
                } else {
                    error("Expected ',' or '}' after rest parameter.");
                }
            }

            // Parse field name
            std::string fieldName;
            if (check(TokenType::IDENTIFIER)) {
                fieldName = consume(TokenType::IDENTIFIER, "Expected field name.").lexeme;
            } else if (check(TokenType::STRING)) {
                // Handle string literals as field names (e.g., { "kind": "Some" })
                Token stringToken = consume(TokenType::STRING, "Expected field name.");
                fieldName = stringToken.lexeme;
                // Remove quotes if present
                if (fieldName.size() >= 2 && (fieldName[0] == '"' || fieldName[0] == '\'') && 
                    (fieldName[fieldName.size()-1] == '"' || fieldName[fieldName.size()-1] == '\'')) {
                    fieldName = fieldName.substr(1, fieldName.size() - 2);
                }
            } else {
                error("Expected field name.");
                break;
            }

            // Parse field type
            consume(TokenType::COLON, "Expected ':' after field name.");
            auto fieldType = parseTypeAnnotation();

            // Add field to structural type
            type->structuralFields.push_back({fieldName, fieldType});

            // Check for comma or end of struct
            if (!check(TokenType::RIGHT_BRACE)) {
                match({TokenType::COMMA}); // Optional comma
            }
        }

        consume(TokenType::RIGHT_BRACE, "Expected '}' after structural type.");
        return type;
    }

    // Parse the base type
    if (match({TokenType::INT_TYPE})) {
        type->typeName = "int";
        type->isPrimitive = true;
    } else if (match({TokenType::INT8_TYPE})) {
        type->typeName = "i8";
        type->isPrimitive = true;
    } else if (match({TokenType::INT16_TYPE})) {
        type->typeName = "i16";
        type->isPrimitive = true;
    } else if (match({TokenType::INT32_TYPE})) {
        type->typeName = "i32";
        type->isPrimitive = true;
    } else if (match({TokenType::INT64_TYPE})) {
        type->typeName = "i64";
        type->isPrimitive = true;
    } else if (match({TokenType::UINT_TYPE})) {
        type->typeName = "uint";
        type->isPrimitive = true;
    } else if (match({TokenType::UINT8_TYPE})) {
        type->typeName = "u8";
        type->isPrimitive = true;
    } else if (match({TokenType::UINT16_TYPE})) {
        type->typeName = "u16";
        type->isPrimitive = true;
    } else if (match({TokenType::UINT32_TYPE})) {
        type->typeName = "u32";
        type->isPrimitive = true;
    } else if (match({TokenType::UINT64_TYPE})) {
        type->typeName = "u64";
        type->isPrimitive = true;
    } else if (match({TokenType::FLOAT_TYPE})) {
        type->typeName = "float";
        type->isPrimitive = true;
    } else if (match({TokenType::FLOAT32_TYPE})) {
        type->typeName = "f32";
        type->isPrimitive = true;
    } else if (match({TokenType::FLOAT64_TYPE})) {
        type->typeName = "f64";
        type->isPrimitive = true;
    } else if (match({TokenType::STR_TYPE})) {
        type->typeName = "str";
        type->isPrimitive = true;
    } else if (match({TokenType::BOOL_TYPE})) {
        type->typeName = "bool";
        type->isPrimitive = true;
    } else if (match({TokenType::ANY_TYPE})) {
        type->typeName = "any";
        type->isPrimitive = true;
    } else if (match({TokenType::NIL_TYPE})) {
        type->typeName = "nil";
        type->isPrimitive = true;
    } else if (match({TokenType::LIST_TYPE})) {
        type->typeName = "list";
        type->isList = true;
    } else if (match({TokenType::DICT_TYPE})) {
        type->typeName = "dict";
        type->isDict = true;
    } else if (match({TokenType::ARRAY_TYPE})) {
        type->typeName = "array";
        type->isList = true;
    } else if (match({TokenType::OPTION_TYPE})) {
        type->typeName = "option";
    } else if (match({TokenType::RESULT_TYPE})) {
        type->typeName = "result";
    } else if (match({TokenType::CHANNEL_TYPE})) {
        type->typeName = "channel";
    } else if (match({TokenType::ATOMIC_TYPE})) {
        type->typeName = "atomic";
    } else if (match({TokenType::FUNCTION_TYPE})) {
        type->typeName = "function";
        type->isFunction = true;
    } else if (match({TokenType::ENUM_TYPE})) {
        type->typeName = "enum";
    } else if (match({TokenType::SUM_TYPE})) {
        type->typeName = "sum";
    } else if (match({TokenType::UNION_TYPE})) {
        type->typeName = "union";
        type->isUnion = true;
    } else {
        // Handle user-defined types
        if (check(TokenType::IDENTIFIER)) {
            // Parse the user-defined type name
            std::string typeName = consume(TokenType::IDENTIFIER, "Expected type name.").lexeme;
            type->typeName = typeName;
            type->isUserDefined = true;
            
            // Check if this is a list-like type (e.g., ListOfX)
            if (typeName.substr(0, 4) == "List" && typeName.length() > 4) {
                type->isList = true;
                
                // Create a default element type
                auto elementType = std::make_shared<AST::TypeAnnotation>();
                elementType->typeName = "any"; // Default to any
                elementType->isPrimitive = true;
                
                // Try to infer element type from name pattern
                if (typeName.substr(4, 2) == "Of" && typeName.length() > 6) {
                    std::string elementTypeName = typeName.substr(6);
                    
                    // Handle common primitive type names in the suffix
                    if (elementTypeName == "Any") {
                        elementType->typeName = "any";
                        elementType->isPrimitive = true;
                    } else if (elementTypeName == "String") {
                        elementType->typeName = "str";
                        elementType->isPrimitive = true;
                    } else if (elementTypeName == "Int") {
                        elementType->typeName = "int";
                        elementType->isPrimitive = true;
                    } else {
                        // Assume it's a user-defined type
                        elementType->typeName = elementTypeName;
                        elementType->isUserDefined = true;
                    }
                }
                
                type->elementType = elementType;
            }
            // Check if this is a dictionary-like type (e.g., DictOfX or DictOfXToY)
            else if (typeName.substr(0, 4) == "Dict" && typeName.length() > 4) {
                type->isDict = true;
                
                // Create default key and value types
                auto keyType = std::make_shared<AST::TypeAnnotation>();
                keyType->typeName = "any";
                keyType->isPrimitive = true;
                
                auto valueType = std::make_shared<AST::TypeAnnotation>();
                valueType->typeName = "any";
                valueType->isPrimitive = true;
                
                // Try to infer key and value types from name pattern
                if (typeName.substr(4, 2) == "Of" && typeName.length() > 6) {
                    std::string remainder = typeName.substr(6);
                    size_t toPos = remainder.find("To");
                    
                    if (toPos != std::string::npos && toPos + 2 < remainder.length()) {
                        // Extract key and value type names (e.g., DictOfStrToInt)
                        std::string keyTypeName = remainder.substr(0, toPos);
                        std::string valueTypeName = remainder.substr(toPos + 2);
                        
                        // Handle common primitive type names for keys
                        if (keyTypeName == "Str") {
                            keyType->typeName = "str";
                            keyType->isPrimitive = true;
                        } else if (keyTypeName == "Int") {
                            keyType->typeName = "int";
                            keyType->isPrimitive = true;
                        } else if (keyTypeName == "Any") {
                            keyType->typeName = "any";
                            keyType->isPrimitive = true;
                        } else {
                            // Assume it's a user-defined type
                            keyType->typeName = keyTypeName;
                            keyType->isUserDefined = true;
                        }
                        
                        // Handle common primitive type names for values
                        if (valueTypeName == "Int") {
                            valueType->typeName = "int";
                            valueType->isPrimitive = true;
                        } else if (valueTypeName == "Str") {
                            valueType->typeName = "str";
                            valueType->isPrimitive = true;
                        } else if (valueTypeName == "Any") {
                            valueType->typeName = "any";
                            valueType->isPrimitive = true;
                        } else {
                            // Assume it's a user-defined type
                            valueType->typeName = valueTypeName;
                            valueType->isUserDefined = true;
                        }
                    } else {
                        // Handle cases like DictOfAny, DictOfString
                        std::string typeName = remainder;
                        
                        // Handle common primitive type names
                        if (typeName == "Any") {
                            keyType->typeName = "any";
                            keyType->isPrimitive = true;
                            valueType->typeName = "any";
                            valueType->isPrimitive = true;
                        } else if (typeName == "String") {
                            keyType->typeName = "str";
                            keyType->isPrimitive = true;
                            valueType->typeName = "str";
                            valueType->isPrimitive = true;
                        } else if (typeName == "Int") {
                            keyType->typeName = "int";
                            keyType->isPrimitive = true;
                            valueType->typeName = "int";
                            valueType->isPrimitive = true;
                        } else {
                            // Assume it's a user-defined type
                            keyType->typeName = typeName;
                            keyType->isUserDefined = true;
                            valueType->typeName = typeName;
                            valueType->isUserDefined = true;
                        }
                    }
                }
                
                type->keyType = keyType;
                type->valueType = valueType;
            }
        } else {
            // Fall back to identifier for user-defined types
            type->typeName = consume(TokenType::IDENTIFIER, "Expected type name for definition.").lexeme;
            type->isUserDefined = true;
        }
    }

    // Check for optional type
    if (match({TokenType::QUESTION})) {
        type->isOptional = true;
    }

    // Check for union types (e.g., int | float)
    if (match({TokenType::PIPE})) {
        // This is a union type
        auto unionType = std::make_shared<AST::TypeAnnotation>();
        unionType->typeName = "union";
        unionType->isUnion = true;
        unionType->unionTypes.push_back(type);

        // Parse the right side of the union
        do {
            // Check if this is a user-defined type that might itself be a union type
            if (check(TokenType::IDENTIFIER)) {
                Token typeToken = peek();
                std::string typeName = typeToken.lexeme;
                
                // If it's a user-defined type, parse it normally
                auto rightType = parseTypeAnnotation();
                unionType->unionTypes.push_back(rightType);
            } else {
                // Regular type annotation
                unionType->unionTypes.push_back(parseTypeAnnotation());
            }
        } while (match({TokenType::PIPE}));

        return unionType;
    }

    // Check for intersection types (e.g., HasName and HasAge)
    if (match({TokenType::AND})) {
        // This is an intersection type
        auto intersectionType = std::make_shared<AST::TypeAnnotation>();
        intersectionType->typeName = "intersection";
        intersectionType->isIntersection = true;
        intersectionType->unionTypes.push_back(type); // Reuse unionTypes for intersection types

        // Parse the right side of the intersection
        do {
            // Check if this is a user-defined type that might itself be a structural type
            if (check(TokenType::IDENTIFIER)) {
                Token typeToken = peek();
                std::string typeName = typeToken.lexeme;
                
                // If it's a user-defined type, parse it normally
                auto rightType = parseTypeAnnotation();
                intersectionType->unionTypes.push_back(rightType);
            } else {
                // Regular type annotation
                intersectionType->unionTypes.push_back(parseTypeAnnotation());
            }
        } while (match({TokenType::AND}));

        return intersectionType;
    }

    // Check for refined types (e.g., int where value > 0)
    if (match({TokenType::WHERE})) {
        // This is a refined type with a constraint
        type->isRefined = true;
        
        // Parse the refinement condition
        // For example: "value > 0" or "matches(value, pattern)"
        type->refinementCondition = expression();
    }

    return type;
}


// Helper method to check if a token type is a primitive type
bool Parser::isPrimitiveType(TokenType type) {
    return type == TokenType::INT_TYPE || type == TokenType::INT8_TYPE || type == TokenType::INT16_TYPE ||
           type == TokenType::INT32_TYPE || type == TokenType::INT64_TYPE || type == TokenType::UINT_TYPE ||
           type == TokenType::UINT8_TYPE || type == TokenType::UINT16_TYPE || type == TokenType::UINT32_TYPE ||
           type == TokenType::UINT64_TYPE || type == TokenType::FLOAT_TYPE || type == TokenType::FLOAT32_TYPE ||
           type == TokenType::FLOAT64_TYPE || type == TokenType::STR_TYPE || type == TokenType::BOOL_TYPE ||
           type == TokenType::ANY_TYPE || type == TokenType::NIL_TYPE;
}

// Helper method to convert a token type to a string
std::string Parser::tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::INT_TYPE: return "int";
        case TokenType::INT8_TYPE: return "i8";
        case TokenType::INT16_TYPE: return "i16";
        case TokenType::INT32_TYPE: return "i32";
        case TokenType::INT64_TYPE: return "i64";
        case TokenType::UINT_TYPE: return "uint";
        case TokenType::UINT8_TYPE: return "u8";
        case TokenType::UINT16_TYPE: return "u16";
        case TokenType::UINT32_TYPE: return "u32";
        case TokenType::UINT64_TYPE: return "u64";
        case TokenType::FLOAT_TYPE: return "float";
        case TokenType::FLOAT32_TYPE: return "f32";
        case TokenType::FLOAT64_TYPE: return "f64";
        case TokenType::STR_TYPE: return "str";
        case TokenType::BOOL_TYPE: return "bool";
        case TokenType::ANY_TYPE: return "any";
        case TokenType::NIL_TYPE: return "nil";
        default: return "unknown";
    }
}
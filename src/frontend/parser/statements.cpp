#include "../parser.hh"
#include "../../error/debugger.hh"
#include <stdexcept>
#include <limits>
#include <set>
#include <cmath>

using namespace LM::Frontend;
using namespace LM::Error;

std::shared_ptr<LM::Frontend::AST::Statement> Parser::declaration() {
    try {
        // Collect leading annotations
        std::vector<Token> annotations = collectAnnotations();
        
        // Parse modifiers for module-level declarations
        LM::Frontend::AST::VisibilityLevel visibility = LM::Frontend::AST::VisibilityLevel::Private; // Default to private
        bool isStatic = false;
        bool isAbstract = false;
        bool isFinal = false;
        bool isDataClass = false;
        
        // Parse visibility and modifiers
        while (check(TokenType::PUB) || check(TokenType::PROT) || check(TokenType::PUBLIC) ||
               check(TokenType::PRIVATE) || check(TokenType::PROTECTED) ||
               check(TokenType::CONST) || check(TokenType::STATIC) ||
               check(TokenType::ABSTRACT) || check(TokenType::FINAL) || check(TokenType::DATA)) {
            
            if (match({TokenType::PUB}) || match({TokenType::PUBLIC})) {
                visibility = LM::Frontend::AST::VisibilityLevel::Public;
            } else if (match({TokenType::PROT}) || match({TokenType::PROTECTED})) {
                visibility = LM::Frontend::AST::VisibilityLevel::Protected;
            } else if (match({TokenType::PRIVATE})) {
                visibility = LM::Frontend::AST::VisibilityLevel::Private;
            } else if (match({TokenType::CONST})) {
                visibility = LM::Frontend::AST::VisibilityLevel::Const;
            } else if (match({TokenType::STATIC})) {
                isStatic = true;
            } else if (match({TokenType::ABSTRACT})) {
                isAbstract = true;
            } else if (match({TokenType::FINAL})) {
                isFinal = true;
            } else if (match({TokenType::DATA})) {
                isDataClass = true;
                isFinal = true; // Data classes are automatically final
            }
        }
        
        if (match({TokenType::FRAME})) {
            auto decl = frameDeclaration();
            if (decl) {
                decl->annotations = annotations;
                decl->isAbstract = isAbstract;
                decl->isFinal = isFinal;
            }
            return decl;
        }
        if (match({TokenType::FN})) {
            auto decl = function("function");
            if (decl) {
                decl->annotations = annotations;
                decl->visibility = visibility;
                decl->isStatic = isStatic;
                decl->isAbstract = isAbstract;
                decl->isFinal = isFinal;
            }
            return decl;
        }
        if (match({TokenType::VAR})) {
            auto decl = varDeclaration();
            if (decl) {
                decl->annotations = annotations;
                // Cast to VarDeclaration to access visibility fields
                if (auto varDecl = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(decl)) {
                    varDecl->visibility = visibility;
                    varDecl->isStatic = isStatic;
                }
            }
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
    } catch (const std::runtime_error &e) {
        if (std::string(e.what()).find("Too many syntax errors") != std::string::npos) {
            throw;
        }
        synchronize();
        return nullptr;
    } catch (const std::exception &e) {
        synchronize();
        return nullptr;
    }
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::varDeclaration() {
    int line = previous().line;

    if (check(TokenType::LEFT_PAREN)) {
        auto destructuring = std::make_shared<LM::Frontend::AST::DestructuringDeclaration>();
        destructuring->line = line;
        destructuring->isTuple = true;
        
        advance(); // consume '('
        
        Token firstName = consume(TokenType::IDENTIFIER, "Expected variable name in tuple destructuring.");
        destructuring->names.push_back(firstName.lexeme);
        
        while (match({TokenType::COMMA})) {
            Token varName = consume(TokenType::IDENTIFIER, "Expected variable name in tuple destructuring.");
            destructuring->names.push_back(varName.lexeme);
        }
        
        consume(TokenType::RIGHT_PAREN, "Expected ')' after tuple destructuring variables.");
        
        consume(TokenType::EQUAL, "Expected '=' in tuple destructuring assignment.");
        destructuring->initializer = expression();
        
        consume(TokenType::SEMICOLON, "Expected ';' after variable declaration.");
        
        return destructuring;
    }

    auto var = createNodeWithContext<LM::Frontend::AST::VarDeclaration>();
    var->line = line;

    Token name = consume(TokenType::IDENTIFIER, "Expected variable name.");
    var->name = name.lexeme;

    if (match({TokenType::COLON})) {
        var->type = parseTypeAnnotation();
    }

    if (match({TokenType::EQUAL})) {
        var->initializer = expression();
    }

    consume(TokenType::SEMICOLON, "Expected ';' after variable declaration.");
    
    return var;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::statement() {
    if (check(TokenType::SEMICOLON)) {
        advance();
        auto emptyStmt = std::make_shared<LM::Frontend::AST::ExprStatement>();
        emptyStmt->line = previous().line;
        emptyStmt->expression = nullptr;
        return emptyStmt;
    }
    
    if (isAtEnd() || check(TokenType::RIGHT_BRACE) || check(TokenType::EOF_TOKEN)) {
        auto emptyStmt = std::make_shared<LM::Frontend::AST::ExprStatement>();
        emptyStmt->line = peek().line;
        emptyStmt->expression = nullptr;
        return emptyStmt;
    }
    
    if (match({TokenType::PRINT})) return printStatement();
    if (match({TokenType::IF})) return ifStatement();
    if (match({TokenType::FOR})) return forStatement();
    if (match({TokenType::WHILE})) return whileStatement();
    if (match({TokenType::BREAK})) return breakStatement();
    if (match({TokenType::CONTINUE})) return continueStatement();
    if (match({TokenType::ITER})) return iterStatement();
    if (match({TokenType::LEFT_BRACE})) return block();
    if (match({TokenType::RETURN})) return returnStatement();
    if (match({TokenType::PARALLEL})) return parallelStatement();
    if (match({TokenType::CONCURRENT})) return concurrentStatement();
    if (match({TokenType::MATCH})) return matchStatement();
    if (match({TokenType::UNSAFE})) return unsafeBlock();
    if (match({TokenType::CONTRACT})) return contractStatement();
    if (match({TokenType::COMPTIME})) return comptimeStatement();

    return expressionStatement();
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::expressionStatement() {
    try {
        auto stmt = createNodeWithContext<LM::Frontend::AST::ExprStatement>();
        stmt->line = peek().line;
        auto expr = expression();
        stmt->expression = expr;
        match({TokenType::SEMICOLON});
        return stmt;
    } catch (const std::runtime_error &e) {
        if (std::string(e.what()).find("Too many syntax errors") != std::string::npos) {
            throw;
        }
        auto stmt = createNodeWithContext<LM::Frontend::AST::ExprStatement>();
        stmt->line = peek().line;
        stmt->expression = nullptr;
        return stmt;
    } catch (const std::exception &e) {
        auto stmt = createNodeWithContext<LM::Frontend::AST::ExprStatement>();
        stmt->line = peek().line;
        stmt->expression = nullptr;
        return stmt;
    }
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::printStatement() {
    auto stmt = createNodeWithContext<LM::Frontend::AST::PrintStatement>();
    stmt->line = previous().line;
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'print'.");
    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            stmt->arguments.push_back(expression());
        } while (match({TokenType::COMMA}));
    }
    consume(TokenType::RIGHT_PAREN, "Expected ')' after print arguments.");
    match({TokenType::SEMICOLON});
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::ifStatement() {
    auto stmt = createNodeWithContext<LM::Frontend::AST::IfStatement>();
    Token ifToken = previous();
    stmt->line = ifToken.line;

    CST::Node* ifCSTNode = nullptr;
    if (cstMode && !cstContextStack.empty()) {
        ifCSTNode = cstContextStack.top();
        if (ifCSTNode && ifCSTNode->kind == CST::NodeKind::IF_STATEMENT) {
            ifCSTNode->setDescription("if statement");
            ifCSTNode->addToken(ifToken);
        }
    }

    Token leftParen = consumeWithTrivia(TokenType::LEFT_PAREN, "Expected '(' after 'if'.");
    if (cstMode && ifCSTNode) ifCSTNode->addToken(leftParen);
    
    size_t conditionStart = current;
    stmt->condition = expression();
    size_t conditionEnd = current;
    
    if (cstMode && ifCSTNode) {
        const auto& tokens = scanner.getTokens();
        for (size_t i = conditionStart; i < conditionEnd; ++i) {
            if (i < tokens.size()) ifCSTNode->addToken(tokens[i]);
        }
    }
    
    Token rightParen = consumeWithTrivia(TokenType::RIGHT_PAREN, "Expected ')' after if condition.");
    if (cstMode && ifCSTNode) ifCSTNode->addToken(rightParen);

    stmt->thenBranch = parseStatementWithContext("if", ifToken);

    while (match({TokenType::ELIF})) {
        Token elifToken = previous();
        auto elifStmt = createNodeWithContext<LM::Frontend::AST::IfStatement>();
        elifStmt->line = elifToken.line;
        
        CST::Node* elifCSTNode = nullptr;
        if (cstMode && !cstContextStack.empty()) {
            elifCSTNode = cstContextStack.top();
            if (elifCSTNode && elifCSTNode->kind == CST::NodeKind::IF_STATEMENT) {
                elifCSTNode->setDescription("elif statement");
                elifCSTNode->addToken(elifToken);
            }
        }
        
        Token elifLeftParen = consumeWithTrivia(TokenType::LEFT_PAREN, "Expected '(' after 'elif'.");
        if (cstMode && elifCSTNode) elifCSTNode->addToken(elifLeftParen);
        
        size_t elifConditionStart = current;
        elifStmt->condition = expression();
        size_t elifConditionEnd = current;
        
        if (cstMode && elifCSTNode) {
            const auto& tokens = scanner.getTokens();
            for (size_t i = elifConditionStart; i < elifConditionEnd; ++i) {
                if (i < tokens.size()) elifCSTNode->addToken(tokens[i]);
            }
        }
        
        Token elifRightParen = consumeWithTrivia(TokenType::RIGHT_PAREN, "Expected ')' after elif condition.");
        if (cstMode && elifCSTNode) elifCSTNode->addToken(elifRightParen);
        
        elifStmt->thenBranch = parseStatementWithContext("elif", elifToken);
        
        if (cstMode && elifCSTNode && elifCSTNode->kind == CST::NodeKind::IF_STATEMENT) popCSTContext();
        
        if (!stmt->elseBranch) {
            stmt->elseBranch = elifStmt;
        } else {
            auto current = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(stmt->elseBranch);
            while (current && current->elseBranch && std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(current->elseBranch)) {
                current = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(current->elseBranch);
            }
            if (current) current->elseBranch = elifStmt;
        }
    }

    if (match({TokenType::ELSE})) {
        Token elseToken = previous();
        if (cstMode && ifCSTNode) ifCSTNode->addToken(elseToken);
        auto elseStmt = parseStatementWithContext("else", elseToken);
        if (!stmt->elseBranch) {
            stmt->elseBranch = elseStmt;
        } else {
            auto current = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(stmt->elseBranch);
            while (current && current->elseBranch && std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(current->elseBranch)) {
                current = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(current->elseBranch);
            }
            if (current) current->elseBranch = elseStmt;
        }
    }

    if (cstMode && ifCSTNode && ifCSTNode->kind == CST::NodeKind::IF_STATEMENT) popCSTContext();
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::BlockStatement> Parser::block() {
    auto block = createNodeWithContext<LM::Frontend::AST::BlockStatement>();
    Token leftBrace = previous();
    block->line = leftBrace.line;
    
    CST::Node* blockCSTNode = nullptr;
    if (cstMode) {
        auto cstNode = std::make_unique<CST::Node>(CST::NodeKind::BLOCK_STATEMENT, leftBrace.start, 0);
        cstNode->setDescription("block statement");
        cstNode->addToken(leftBrace);
        blockCSTNode = cstNode.get();
        addChildToCurrentContext(std::move(cstNode));
        pushCSTContext(blockCSTNode);
    }

    if (check(TokenType::RIGHT_BRACE)) {
        Token rightBrace = consume(TokenType::RIGHT_BRACE, "Expected '}' after block.");
        if (cstMode && blockCSTNode) {
            blockCSTNode->addToken(rightBrace);
            blockCSTNode->endPos = rightBrace.end;
            popCSTContext();
        }
        return block;
    }

    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        try {
            if (in_concurrent_block) {
                bool is_async = false; // Temporarily disabled async support
                if (peek().type == TokenType::IDENTIFIER) {
                    if (peek().lexeme == "task") {
                        advance(); 
                        auto stmt = taskStatement();
                        auto task_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::TaskStatement>(stmt);
                        if (task_stmt) task_stmt->isAsync = is_async;
                        block->statements.push_back(stmt);
                        continue;
                    }
                    if (peek().lexeme == "worker") {
                        advance();
                        auto stmt = workerStatement();
                        auto worker_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::WorkerStatement>(stmt);
                        if (worker_stmt) worker_stmt->isAsync = is_async;
                        block->statements.push_back(stmt);
                        continue;
                    }
                }
                if (is_async) error("Expected 'task' or 'worker' after 'async' in this context.");
            }
            auto declaration = this->declaration();
            if (declaration) block->statements.push_back(declaration);
        } catch (const std::runtime_error &e) {
            if (std::string(e.what()).find("Too many syntax errors") != std::string::npos) throw;
            synchronize();
        } catch (const std::exception &e) {
            synchronize();
        }
    }

    Token rightBrace = consume(TokenType::RIGHT_BRACE, "Expected '}' after block.");
    if (cstMode && blockCSTNode) {
        blockCSTNode->addToken(rightBrace);
        blockCSTNode->endPos = rightBrace.end;
        popCSTContext();
    }
    return block;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::forStatement() {
    auto stmt = createNodeWithContext<LM::Frontend::AST::ForStatement>();
    Token forToken = previous();
    stmt->line = forToken.line;

    CST::Node* forCSTNode = nullptr;
    if (cstMode && !cstContextStack.empty()) {
        forCSTNode = cstContextStack.top();
        if (forCSTNode && forCSTNode->kind == CST::NodeKind::FOR_STATEMENT) {
            forCSTNode->setDescription("for statement");
            forCSTNode->addToken(forToken);
        }
    }

    Token leftParen = consumeWithTrivia(TokenType::LEFT_PAREN, "Expected '(' after 'for'.");
    if (cstMode && forCSTNode) forCSTNode->addToken(leftParen);

    if (match({TokenType::SEMICOLON})) {
        if (cstMode && forCSTNode) forCSTNode->addToken(previous());
        stmt->initializer = nullptr;
    } else if (match({TokenType::VAR})) {
        Token varToken = previous();
        if (cstMode && forCSTNode) forCSTNode->addToken(varToken);
        Token name = consumeWithTrivia(TokenType::IDENTIFIER, "Expected variable name.");
        if (cstMode && forCSTNode) forCSTNode->addToken(name);
        auto varDecl = std::make_shared<LM::Frontend::AST::VarDeclaration>();
        varDecl->line = name.line;
        varDecl->name = name.lexeme;
        if (match({TokenType::COLON})) {
            if (cstMode && forCSTNode) forCSTNode->addToken(previous());
            varDecl->type = parseTypeAnnotation();
        }
        if (match({TokenType::EQUAL})) {
            if (cstMode && forCSTNode) forCSTNode->addToken(previous());
            size_t start = current;
            varDecl->initializer = expression();
            if (cstMode && forCSTNode) {
                for (size_t i = start; i < current && i < scanner.getTokens().size(); i++) forCSTNode->addToken(scanner.getTokens()[i]);
            }
        }
        stmt->initializer = varDecl;
        Token semi1 = consumeWithTrivia(TokenType::SEMICOLON, "Expected ';' after var declaration.");
        if (cstMode && forCSTNode) forCSTNode->addToken(semi1);
    } else {
        stmt->initializer = expressionStatement();
    }

    if (!check(TokenType::SEMICOLON)) {
        size_t start = current;
        stmt->condition = expression();
        if (cstMode && forCSTNode) {
            for (size_t i = start; i < current && i < scanner.getTokens().size(); i++) forCSTNode->addToken(scanner.getTokens()[i]);
        }
    }
    Token semi2 = consumeWithTrivia(TokenType::SEMICOLON, "Expected ';' after loop condition.");
    if (cstMode && forCSTNode) forCSTNode->addToken(semi2);

    if (!check(TokenType::RIGHT_PAREN)) {
        size_t start = current;
        stmt->increment = expression();
        if (cstMode && forCSTNode) {
            for (size_t i = start; i < current && i < scanner.getTokens().size(); i++) forCSTNode->addToken(scanner.getTokens()[i]);
        }
    }

    Token rightParen = consumeWithTrivia(TokenType::RIGHT_PAREN, "Expected ')' after for clauses.");
    if (cstMode && forCSTNode) forCSTNode->addToken(rightParen);

    stmt->body = parseStatementWithContext("for", forToken);
    if (cstMode && !cstContextStack.empty()) popCSTContext();
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::whileStatement() {
    auto stmt = createNodeWithContext<LM::Frontend::AST::WhileStatement>();
    Token whileToken = previous();
    stmt->line = whileToken.line;

    CST::Node* whileCSTNode = nullptr;
    if (cstMode && !cstContextStack.empty()) {
        whileCSTNode = cstContextStack.top();
        if (whileCSTNode && whileCSTNode->kind == CST::NodeKind::WHILE_STATEMENT) {
            whileCSTNode->setDescription("while statement");
            whileCSTNode->addToken(whileToken);
        }
    }

    Token leftParen = consumeWithTrivia(TokenType::LEFT_PAREN, "Expected '(' after 'while'.");
    if (cstMode && whileCSTNode) whileCSTNode->addToken(leftParen);
    
    size_t conditionStart = current;
    stmt->condition = expression();
    size_t conditionEnd = current;
    
    if (cstMode && whileCSTNode) {
        for (size_t i = conditionStart; i < conditionEnd && i < scanner.getTokens().size(); i++) whileCSTNode->addToken(scanner.getTokens()[i]);
    }
    
    Token rightParen = consumeWithTrivia(TokenType::RIGHT_PAREN, "Expected ')' after while condition.");
    if (cstMode && whileCSTNode) whileCSTNode->addToken(rightParen);

    stmt->body = parseStatementWithContext("while", whileToken);
    if (cstMode && !cstContextStack.empty()) popCSTContext();
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::FunctionDeclaration> Parser::function(const std::string& kind) {
    auto func = createNodeWithContext<LM::Frontend::AST::FunctionDeclaration>();
    func->line = previous().line;
    attachTriviaFromToken(previous());

    Token name = consume(TokenType::IDENTIFIER, "Expected " + kind + " name.");
    func->name = name.lexeme;

    if (match({TokenType::LEFT_BRACKET})) {
        do {
            func->genericParams.push_back(consume(TokenType::IDENTIFIER, "Expected generic parameter name.").lexeme);
        } while (match({TokenType::COMMA}));
        consume(TokenType::RIGHT_BRACKET, "Expected ']' after generic parameters.");
    }

    consume(TokenType::LEFT_PAREN, "Expected '(' after " + kind + " name.");

    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            auto paramName = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;
            std::shared_ptr<LM::Frontend::AST::TypeAnnotation> paramType = nullptr;
            if (match({TokenType::COLON})) paramType = parseTypeAnnotation();

            if (match({TokenType::EQUAL})) {
                std::shared_ptr<LM::Frontend::AST::Expression> defaultValue = expression();
                func->optionalParams.push_back({paramName, {paramType, defaultValue}});
            } else if (paramType && paramType->isOptional) {
                func->optionalParams.push_back({paramName, {paramType, nullptr}});
            } else {
                func->params.push_back({paramName, paramType});
            }
        } while (match({TokenType::COMMA}));
    }

    consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters.");

    if (match({TokenType::COLON})) {
        func->returnType = parseTypeAnnotation();
        if (func->returnType && (*func->returnType)->isFallible) {
            func->canFail = true;
            func->declaredErrorTypes = (*func->returnType)->errorTypes;
        }
    }

    if (check(TokenType::SEMICOLON)) {
        advance();
        func->body = nullptr;
    } else {
        Token leftBrace = consume(TokenType::LEFT_BRACE, "Expected '{' before " + kind + " body.");
        pushBlockContext("function", leftBrace);
        func->body = block();
        popBlockContext();
    }

    if (cstMode && !cstContextStack.empty()) popCSTContext();
    return func;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::returnStatement() {
    auto stmt = std::make_shared<LM::Frontend::AST::ReturnStatement>();
    stmt->line = previous().line;
    if (!check(TokenType::SEMICOLON) && !check(TokenType::RIGHT_BRACE)) stmt->value = expression();
    match({TokenType::SEMICOLON});
    return stmt;
}

void Parser::parseConcurrencyParams(std::string& channel, std::string& mode, std::string& cores, std::string& onError, std::string& timeout, std::string& grace, std::string& onTimeout) {
    bool has_parens = match({TokenType::LEFT_PAREN});
    if (!has_parens && check(TokenType::IDENTIFIER)) {
        std::string paramName = consume(TokenType::IDENTIFIER, "Expected parameter name").lexeme;
        if (match({TokenType::EQUAL})) {
            std::string paramValue;
            if (check(TokenType::IDENTIFIER)) {
                paramValue = consume(TokenType::IDENTIFIER, "Expected identifier").lexeme;
                if (paramName == "ch") channel = paramValue;
                else if (paramName == "mode") mode = paramValue;
                else if (paramName == "cores") cores = paramValue;
                else if (paramName == "on_error") onError = paramValue;
                else if (paramName == "timeout") timeout = paramValue;
                else if (paramName == "grace") grace = paramValue;
                else if (paramName == "on_timeout") onTimeout = paramValue;
                else error("Unknown parameter: " + paramName);
                return;
            }
        }
    }
    if (has_parens) {
        while (!check(TokenType::RIGHT_PAREN) && !isAtEnd()) {
            std::string paramName = consume(TokenType::IDENTIFIER, "Expected parameter name").lexeme;
            if (match({TokenType::COLON})) {
                consume(TokenType::IDENTIFIER, "Expected type name after ':'");
                if (!match({TokenType::COMMA}) && !check(TokenType::RIGHT_PAREN)) { error("Expected ',' or ')' after type annotation"); break; }
                continue;
            } else if (match({TokenType::EQUAL})) {}
            else { error("Expected '=' or ':' after parameter name"); break; }
            std::string paramValue;
            if (check(TokenType::STRING)) {
                paramValue = consume(TokenType::STRING, "Expected string value").lexeme;
                if (paramValue.size() >= 2) paramValue = paramValue.substr(1, paramValue.size() - 2);
            } else if (check(TokenType::INT_LITERAL) || check(TokenType::FLOAT_LITERAL) || check(TokenType::SCIENTIFIC_LITERAL)) {
                paramValue = advance().lexeme;
                if (check(TokenType::IDENTIFIER)) {
                    std::string unit = peek().lexeme;
                    if (unit == "s" || unit == "ms" || unit == "us" || unit == "ns") { advance(); paramValue += unit; }
                }
            } else if (check(TokenType::IDENTIFIER)) paramValue = consume(TokenType::IDENTIFIER, "Expected identifier").lexeme;
            else { error("Expected string, number, or identifier as parameter value"); break; }
            if (paramName == "ch") channel = paramValue;
            else if (paramName == "mode") mode = paramValue;
            else if (paramName == "cores") cores = paramValue;
            else if (paramName == "on_error") onError = paramValue;
            else if (paramName == "timeout") timeout = paramValue;
            else if (paramName == "grace") grace = paramValue;
            else if (paramName == "on_timeout") onTimeout = paramValue;
            else error("Unknown parameter: " + paramName);
            if (!match({TokenType::COMMA}) && !check(TokenType::RIGHT_PAREN)) { error("Expected ',' or ')' after parameter"); break; }
        }
        consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters");
    }
}

std::shared_ptr<LM::Frontend::AST::FrameDeclaration> Parser::frameDeclaration() {
    auto frameDecl = createNodeWithContext<LM::Frontend::AST::FrameDeclaration>();
    frameDecl->line = previous().line;
    Token name = consume(TokenType::IDENTIFIER, "Expected frame name.");
    frameDecl->name = name.lexeme;
    if (match({TokenType::COLON})) {
        do {
            Token traitName = consume(TokenType::IDENTIFIER, "Expected trait name.");
            frameDecl->implements.push_back(traitName.lexeme);
        } while (match({TokenType::COMMA}));
    }
    Token leftBrace = consume(TokenType::LEFT_BRACE, "Expected '{' before frame body.");
    pushBlockContext("frame", leftBrace);
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        LM::Frontend::AST::VisibilityLevel visibility = LM::Frontend::AST::VisibilityLevel::Private;
        while (check(TokenType::PUB) || check(TokenType::PROT) || check(TokenType::PUBLIC) || check(TokenType::PRIVATE) || check(TokenType::PROTECTED) || check(TokenType::CONST)) {
            if (match({TokenType::PUB}) || match({TokenType::PUBLIC})) visibility = LM::Frontend::AST::VisibilityLevel::Public;
            else if (match({TokenType::PROT}) || match({TokenType::PROTECTED})) visibility = LM::Frontend::AST::VisibilityLevel::Protected;
            else if (match({TokenType::PRIVATE})) visibility = LM::Frontend::AST::VisibilityLevel::Private;
            else if (match({TokenType::CONST})) visibility = LM::Frontend::AST::VisibilityLevel::Const;
        }
        if (check(TokenType::IDENTIFIER) && peek().lexeme == "init") {
            advance(); consume(TokenType::LEFT_PAREN, "Expected '(' after 'init'.");
            auto initMethod = std::make_shared<LM::Frontend::AST::FrameMethod>();
            initMethod->name = "init"; initMethod->visibility = visibility; initMethod->isInit = true;
            if (!check(TokenType::RIGHT_PAREN)) {
                do {
                    auto paramName = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;
                    consume(TokenType::COLON, "Expected ':' after parameter name.");
                    auto paramType = parseTypeAnnotation();
                    if (match({TokenType::EQUAL})) {
                        std::shared_ptr<LM::Frontend::AST::Expression> defaultValue = expression();
                        initMethod->optionalParams.push_back({paramName, {paramType, defaultValue}});
                    } else if (paramType && paramType->isOptional) initMethod->optionalParams.push_back({paramName, {paramType, nullptr}});
                    else initMethod->parameters.push_back({paramName, paramType});
                } while (match({TokenType::COMMA}));
            }
            consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters.");
            if (match({TokenType::COLON})) initMethod->returnType = parseTypeAnnotation();
            consume(TokenType::LEFT_BRACE, "Expected '{' before init body.");
            initMethod->body = block();
            frameDecl->init = initMethod;
        } else if (check(TokenType::IDENTIFIER) && peek().lexeme == "deinit") {
            advance(); consume(TokenType::LEFT_PAREN, "Expected '(' after 'deinit'.");
            auto deinitMethod = std::make_shared<LM::Frontend::AST::FrameMethod>();
            deinitMethod->name = "deinit"; deinitMethod->visibility = visibility; deinitMethod->isDeinit = true;
            if (!check(TokenType::RIGHT_PAREN)) error("deinit() method cannot have parameters.");
            consume(TokenType::RIGHT_PAREN, "Expected ')' after deinit.");
            consume(TokenType::LEFT_BRACE, "Expected '{' before deinit body.");
            deinitMethod->body = block();
            frameDecl->deinit = deinitMethod;
        } else if (match({TokenType::FN})) {
            auto frameMethod = std::make_shared<LM::Frontend::AST::FrameMethod>();
            frameMethod->visibility = visibility;
            Token methodName = consume(TokenType::IDENTIFIER, "Expected method name.");
            frameMethod->name = methodName.lexeme;
            consume(TokenType::LEFT_PAREN, "Expected '(' after method name.");
            if (!check(TokenType::RIGHT_PAREN)) {
                do {
                    auto paramName = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;
                    consume(TokenType::COLON, "Expected ':' after parameter name.");
                    auto paramType = parseTypeAnnotation();
                    if (match({TokenType::EQUAL})) {
                        std::shared_ptr<LM::Frontend::AST::Expression> defaultValue = expression();
                        frameMethod->optionalParams.push_back({paramName, {paramType, defaultValue}});
                    } else if (paramType && paramType->isOptional) frameMethod->optionalParams.push_back({paramName, {paramType, nullptr}});
                    else frameMethod->parameters.push_back({paramName, paramType});
                } while (match({TokenType::COMMA}));
            }
            consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters.");
            if (match({TokenType::COLON})) frameMethod->returnType = parseTypeAnnotation();
            consume(TokenType::LEFT_BRACE, "Expected '{' before method body.");
            frameMethod->body = block();
            if (frameMethod->name == "init") { frameMethod->isInit = true; frameDecl->init = frameMethod; }
            else if (frameMethod->name == "deinit") { frameMethod->isDeinit = true; frameDecl->deinit = frameMethod; }
            else frameDecl->methods.push_back(frameMethod);
        } else if (match({TokenType::VAR})) {
            auto fieldName = consume(TokenType::IDENTIFIER, "Expected field name.").lexeme;
            consume(TokenType::COLON, "Expected ':' after field name.");
            auto fieldType = parseTypeAnnotation();
            auto field = std::make_shared<LM::Frontend::AST::FrameField>();
            field->name = fieldName; field->type = fieldType; field->visibility = visibility;
            if (match({TokenType::EQUAL})) field->defaultValue = expression();
            consume(TokenType::SEMICOLON, "Expected ';' after field declaration.");
            frameDecl->fields.push_back(field);
        } else if (check(TokenType::IDENTIFIER)) {
            Token fieldName = advance();
            if (check(TokenType::COLON)) {
                advance();
                auto field = std::make_shared<LM::Frontend::AST::FrameField>();
                field->name = fieldName.lexeme; field->type = parseTypeAnnotation(); field->visibility = visibility;
                if (match({TokenType::EQUAL})) field->defaultValue = expression();
                consume(TokenType::SEMICOLON, "Expected ';' after field declaration.");
                frameDecl->fields.push_back(field);
            } else { error("Expected ':' after field name in frame member declaration."); break; }
        } else { error("Expected frame member declaration (field or method)."); break; }
    }
    consume(TokenType::RIGHT_BRACE, "Expected '}' after frame body.");
    popBlockContext();
    if (cstMode && !cstContextStack.empty()) popCSTContext();
    return frameDecl;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::parallelStatement() {
    auto stmt = createNodeWithContext<LM::Frontend::AST::ParallelStatement>();
    stmt->line = previous().line;
    stmt->cores = "auto"; stmt->timeout = "0"; stmt->grace = "0"; stmt->on_error = "stop";
    std::string dummy_channel, dummy_mode, dummy_onError, dummy_onTimeout;
    parseConcurrencyParams(dummy_channel, dummy_mode, stmt->cores, stmt->on_error, stmt->timeout, stmt->grace, dummy_onTimeout);
    consume(TokenType::LEFT_BRACE, "Expected '{' after 'parallel'.");
    in_concurrent_block = true; stmt->body = block(); in_concurrent_block = false;
    if (cstMode && !cstContextStack.empty()) popCSTContext();
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::concurrentStatement() {
    auto stmt = createNodeWithContext<LM::Frontend::AST::ConcurrentStatement>();
    stmt->line = previous().line;
    stmt->channel = ""; stmt->channelParam = ""; stmt->mode = "batch"; stmt->cores = "auto"; stmt->onError = "stop"; stmt->timeout = "0"; stmt->grace = "0"; stmt->onTimeout = "partial";
    parseConcurrencyParams(stmt->channel, stmt->mode, stmt->cores, stmt->onError, stmt->timeout, stmt->grace, stmt->onTimeout);
    if (!stmt->channel.empty()) stmt->channelParam = "ch";
    consume(TokenType::LEFT_BRACE, "Expected '{' after 'concurrent'.");
    in_concurrent_block = true; stmt->body = block(); in_concurrent_block = false;
    if (cstMode && !cstContextStack.empty()) popCSTContext();
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::taskStatement() {
    auto stmt = std::make_shared<LM::Frontend::AST::TaskStatement>();
    stmt->line = peek().line;
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'task'.");
    if (check(TokenType::IDENTIFIER)) {
        stmt->loopVar = consume(TokenType::IDENTIFIER, "Expected loop variable name.").lexeme;
        consume(TokenType::IN, "Expected 'in' after loop variable.");
    }
    stmt->iterable = expression();
    consume(TokenType::RIGHT_PAREN, "Expected ')' after task arguments.");
    consume(TokenType::LEFT_BRACE, "Expected '{' before task body.");
    stmt->body = block();
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::workerStatement() {
    auto stmt = std::make_shared<LM::Frontend::AST::WorkerStatement>();
    stmt->line = peek().line;
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'worker'.");
    if (check(TokenType::IDENTIFIER)) {
        stmt->paramName = consume(TokenType::IDENTIFIER, "Expected loop variable name.").lexeme;
        stmt->param = stmt->paramName;
        if (match({TokenType::IN, TokenType::FROM})) stmt->iterable = expression();
    }
    consume(TokenType::RIGHT_PAREN, "Expected ')' after worker arguments.");
    consume(TokenType::LEFT_BRACE, "Expected '{' before worker body.");
    stmt->body = block();
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::importStatement() {
    auto stmt = std::make_shared<LM::Frontend::AST::ImportStatement>();
    stmt->line = previous().line;
    if (check(TokenType::IDENTIFIER) || check(TokenType::MODULE)) {
        stmt->modulePath = advance().lexeme;
        while (match({TokenType::DOT})) {
            if (check(TokenType::IDENTIFIER) || check(TokenType::MODULE)) stmt->modulePath += "." + advance().lexeme;
            else { error("Expected module path component."); return nullptr; }
        }
    } else if (match({TokenType::LEFT_PAREN})) {
        stmt->isStringLiteralPath = true;
        stmt->modulePath = consume(TokenType::STRING, "Expected string literal for module path.").lexeme;
        consume(TokenType::RIGHT_PAREN, "Expected ')' after module path string.");
    } else { error("Expected module path or string literal after 'import'."); return nullptr; }
    if (match({TokenType::AS})) stmt->alias = consume(TokenType::IDENTIFIER, "Expected alias name.").lexeme;
    if (match({TokenType::SHOW, TokenType::HIDE})) {
        LM::Frontend::AST::ImportFilter filter;
        filter.type = previous().type == TokenType::SHOW ? LM::Frontend::AST::ImportFilterType::Show : LM::Frontend::AST::ImportFilterType::Hide;
        do {
            if (check(TokenType::IDENTIFIER) || check(TokenType::MODULE)) filter.identifiers.push_back(advance().lexeme);
            else { error("Expected identifier in filter list."); return nullptr; }
        } while (match({TokenType::COMMA}));
        stmt->filter = filter;
    }
    match({TokenType::SEMICOLON});
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::EnumDeclaration> Parser::enumDeclaration() {
    auto enumDecl = std::make_shared<LM::Frontend::AST::EnumDeclaration>();
    enumDecl->line = previous().line;
    Token name = consume(TokenType::IDENTIFIER, "Expected enum name.");
    enumDecl->name = name.lexeme;
    consume(TokenType::LEFT_BRACE, "Expected '{' before enum body.");
    if (!check(TokenType::RIGHT_BRACE)) {
        do {
            std::string variantName = consume(TokenType::IDENTIFIER, "Expected variant name.").lexeme;
            std::vector<std::shared_ptr<LM::Frontend::AST::TypeAnnotation>> variantTypes;
            if (match({TokenType::LEFT_PAREN})) {
                if (!check(TokenType::RIGHT_PAREN)) {
                    do {
                        variantTypes.push_back(parseTypeAnnotation());
                    } while (match({TokenType::COMMA}));
                }
                consume(TokenType::RIGHT_PAREN, "Expected ')' after variant types.");
            }
            enumDecl->variants.push_back({variantName, variantTypes});
        } while (match({TokenType::COMMA}));
    }
    consume(TokenType::RIGHT_BRACE, "Expected '}' after enum body.");
    return enumDecl;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::matchStatement() {
    auto stmt = createNodeWithContext<LM::Frontend::AST::MatchStatement>();
    stmt->line = previous().line;
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'match'.");
    stmt->value = expression();
    consume(TokenType::RIGHT_PAREN, "Expected ')' after match value.");
    Token leftBrace = consume(TokenType::LEFT_BRACE, "Expected '{' before match cases.");
    
    pushBlockContext("match", leftBrace);
    
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        skipTrivia();
        LM::Frontend::AST::MatchCase matchCase;
        matchCase.pattern = parsePattern();
        if (match({TokenType::WHERE})) matchCase.guard = expression();
        skipTrivia();
        consume(TokenType::ARROW, "Expected '=>' after match pattern.");
        // Handle expressions in match cases without requiring semicolons
        auto exprStmt = createNodeWithContext<LM::Frontend::AST::ExprStatement>();
        exprStmt->line = peek().line;
        exprStmt->expression = expression();
        matchCase.body = exprStmt;
        if (match({TokenType::COMMA})) if (check(TokenType::RIGHT_BRACE)) break;
        stmt->cases.push_back(matchCase);
    }
    
    popBlockContext();
    skipTrivia();
    consume(TokenType::RIGHT_BRACE, "Expected '}' after match cases.");
    if (cstMode && !cstContextStack.empty()) popCSTContext();
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::traitDeclaration() {
    auto traitDecl = std::make_shared<LM::Frontend::AST::TraitDeclaration>();
    traitDecl->line = previous().line;
    if (match({TokenType::OPEN})) traitDecl->isOpen = true;
    Token name = consume(TokenType::IDENTIFIER, "Expected trait name.");
    traitDecl->name = name.lexeme;
    if (match({TokenType::COLON})) {
        do {
            Token parentName = consume(TokenType::IDENTIFIER, "Expected parent trait name.");
            traitDecl->extends.push_back(parentName.lexeme);
        } while (match({TokenType::COMMA}));
    }
    consume(TokenType::LEFT_BRACE, "Expected '{' before trait body.");
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        if (match({TokenType::FN})) {
            auto method = std::make_shared<LM::Frontend::AST::FunctionDeclaration>();
            method->line = previous().line;
            Token name = consume(TokenType::IDENTIFIER, "Expected method name.");
            method->name = name.lexeme;
            consume(TokenType::LEFT_PAREN, "Expected '(' after method name.");
            if (!check(TokenType::RIGHT_PAREN)) {
                do {
                    auto paramName = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;
                    consume(TokenType::COLON, "Expected ':' after parameter name.");
                    auto paramType = parseTypeAnnotation();
                    method->params.push_back({paramName, paramType});
                } while (match({TokenType::COMMA}));
            }
            consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters.");
            if (match({TokenType::COLON})) method->returnType = parseTypeAnnotation();
            if (match({TokenType::SEMICOLON})) {
                method->body = std::make_shared<LM::Frontend::AST::BlockStatement>();
                method->body->line = method->line;
            } else {
                consume(TokenType::LEFT_BRACE, "Expected '{' or ';' after method declaration.");
                method->body = block();
            }
            traitDecl->methods.push_back(method);
        } else {
            error("Expected method declaration in trait.");
            break;
        }
    }
    consume(TokenType::RIGHT_BRACE, "Expected '}' after trait body.");
    return traitDecl;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::interfaceDeclaration() {
    auto interfaceDecl = std::make_shared<LM::Frontend::AST::InterfaceDeclaration>();
    interfaceDecl->line = previous().line;
    if (match({TokenType::AT_SIGN})) {
        Token annotation = consume(TokenType::IDENTIFIER, "Expected annotation name after '@'.");
        if (annotation.lexeme == "open") interfaceDecl->isOpen = true;
    }
    Token name = consume(TokenType::IDENTIFIER, "Expected interface name.");
    interfaceDecl->name = name.lexeme;
    consume(TokenType::LEFT_BRACE, "Expected '{' before interface body.");
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        if (match({TokenType::FN})) {
            auto method = function("method");
            interfaceDecl->methods.push_back(method);
        } else { error("Expected method declaration in interface."); break; }
    }
    consume(TokenType::RIGHT_BRACE, "Expected '}' after interface body.");
    return interfaceDecl;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::moduleDeclaration() {
    auto moduleDecl = std::make_shared<LM::Frontend::AST::ModuleDeclaration>();
    moduleDecl->line = previous().line;
    Token name = consume(TokenType::IDENTIFIER, "Expected module name.");
    moduleDecl->name = name.lexeme;
    consume(TokenType::LEFT_BRACE, "Expected '{' before module body.");
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        bool isPublic = false, isProtected = false;
        if (match({TokenType::AT_SIGN})) {
            Token annotation = consume(TokenType::IDENTIFIER, "Expected annotation name after '@'.");
            if (annotation.lexeme == "public") isPublic = true;
            else if (annotation.lexeme == "protected") isProtected = true;
        }
        auto member = declaration();
        if (member) {
            if (isPublic) moduleDecl->publicMembers.push_back(member);
            else if (isProtected) moduleDecl->protectedMembers.push_back(member);
            else moduleDecl->privateMembers.push_back(member);
        }
    }
    consume(TokenType::RIGHT_BRACE, "Expected '}' after module body.");
    return moduleDecl;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::iterStatement() {
    auto stmt = createNodeWithContext<LM::Frontend::AST::IterStatement>();
    Token iterToken = previous();
    stmt->line = iterToken.line;
    CST::Node* iterCSTNode = nullptr;
    if (cstMode && !cstContextStack.empty()) {
        iterCSTNode = cstContextStack.top();
        if (iterCSTNode && iterCSTNode->kind == CST::NodeKind::ITER_STATEMENT) {
            iterCSTNode->setDescription("iter statement");
            iterCSTNode->addToken(iterToken);
        }
    }
    Token leftParen = consumeWithTrivia(TokenType::LEFT_PAREN, "Expected '(' after 'iter'.");
    if (cstMode && iterCSTNode) iterCSTNode->addToken(leftParen);
    if (match({TokenType::VAR})) {
        Token varToken = previous();
        if (cstMode && iterCSTNode) iterCSTNode->addToken(varToken);
        Token name = consumeWithTrivia(TokenType::IDENTIFIER, "Expected variable name.");
        stmt->loopVars.push_back(name.lexeme);
        if (cstMode && iterCSTNode) iterCSTNode->addToken(name);
        if (match({TokenType::COMMA})) {
            Token comma = previous();
            if (cstMode && iterCSTNode) iterCSTNode->addToken(comma);
            Token secondVar = consumeWithTrivia(TokenType::IDENTIFIER, "Expected second variable name after comma.");
            stmt->loopVars.push_back(secondVar.lexeme);
            if (cstMode && iterCSTNode) iterCSTNode->addToken(secondVar);
        }
        Token inToken = consumeWithTrivia(TokenType::IN, "Expected 'in' after loop variables.");
        if (cstMode && iterCSTNode) iterCSTNode->addToken(inToken);
        size_t iterableStart = current;
        stmt->iterable = expression();
        size_t iterableEnd = current;
        if (cstMode && iterCSTNode) {
            for (size_t i = iterableStart; i < iterableEnd && i < scanner.getTokens().size(); i++) iterCSTNode->addToken(scanner.getTokens()[i]);
        }
    } else if (match({TokenType::IDENTIFIER})) {
        Token firstVarToken = previous();
        stmt->loopVars.push_back(firstVarToken.lexeme);
        if (cstMode && iterCSTNode) iterCSTNode->addToken(firstVarToken);
        if (match({TokenType::COMMA})) {
            Token comma = previous();
            if (cstMode && iterCSTNode) iterCSTNode->addToken(comma);
            Token secondVar = consumeWithTrivia(TokenType::IDENTIFIER, "Expected second variable name after comma.");
            stmt->loopVars.push_back(secondVar.lexeme);
            if (cstMode && iterCSTNode) iterCSTNode->addToken(secondVar);
            Token inToken = consumeWithTrivia(TokenType::IN, "Expected 'in' after loop variables.");
            if (cstMode && iterCSTNode) iterCSTNode->addToken(inToken);
            size_t iterableStart = current;
            stmt->iterable = expression();
            size_t iterableEnd = current;
            if (cstMode && iterCSTNode) {
                for (size_t i = iterableStart; i < iterableEnd && i < scanner.getTokens().size(); i++) iterCSTNode->addToken(scanner.getTokens()[i]);
            }
        } else if (match({TokenType::IN})) {
            Token inToken = previous();
            if (cstMode && iterCSTNode) iterCSTNode->addToken(inToken);
            size_t iterableStart = current;
            stmt->iterable = expression();
            size_t iterableEnd = current;
            if (cstMode && iterCSTNode) {
                for (size_t i = iterableStart; i < iterableEnd && i < scanner.getTokens().size(); i++) iterCSTNode->addToken(scanner.getTokens()[i]);
            }
        } else error("Expected 'in' after loop variable.");
    } else error("Expected variable name or identifier after 'iter ('.");
    Token rightParen = consumeWithTrivia(TokenType::RIGHT_PAREN, "Expected ')' after iter clauses.");
    if (cstMode && iterCSTNode) iterCSTNode->addToken(rightParen);
    stmt->body = parseStatementWithContext("iter", iterToken);
    if (cstMode && !cstContextStack.empty()) popCSTContext();
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::breakStatement() {
    auto stmt = std::make_shared<LM::Frontend::AST::BreakStatement>();
    stmt->line = previous().line;
    consume(TokenType::SEMICOLON, "Expected ';' after 'break'.");
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::continueStatement() {
    auto stmt = std::make_shared<LM::Frontend::AST::ContinueStatement>();
    stmt->line = previous().line;
    consume(TokenType::SEMICOLON, "Expected ';' after 'continue'.");
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::unsafeBlock() {
    auto stmt = std::make_shared<LM::Frontend::AST::UnsafeStatement>();
    stmt->line = previous().line;
    consume(TokenType::LEFT_BRACE, "Expected '{' after 'unsafe'.");
    stmt->body = block();
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::contractStatement() {
    auto stmt = createNodeWithContext<LM::Frontend::AST::ContractStatement>();
    stmt->line = previous().line;
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'contract'.");
    stmt->condition = expression();
    if (match({TokenType::COMMA})) {
        if (match({TokenType::STRING})) {
            auto literalExpr = std::make_shared<LM::Frontend::AST::LiteralExpr>();
            literalExpr->line = previous().line;
            literalExpr->value = previous().lexeme;
            stmt->message = literalExpr;
        } else stmt->message = expression();
    }
    consume(TokenType::RIGHT_PAREN, "Expected ')' after contract condition.");
    consume(TokenType::SEMICOLON, "Expected ';' after contract statement.");
    return stmt;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::comptimeStatement() {
    auto stmt = std::make_shared<LM::Frontend::AST::ComptimeStatement>();
    stmt->line = previous().line;
    stmt->declaration = declaration();
    return stmt;
}

void Parser::pushBlockContext(const std::string& blockType, const Token& startToken) {
    LM::Error::BlockContext context(blockType, startToken.line, startToken.start, startToken.lexeme);
    blockStack.push(context);
}

void Parser::popBlockContext() {
    if (!blockStack.empty()) blockStack.pop();
}

std::optional<LM::Error::BlockContext> Parser::getCurrentBlockContext() const {
    if (blockStack.empty()) return std::nullopt;
    return blockStack.top();
}

std::string Parser::generateCausedByMessage(const LM::Error::BlockContext& context) const {
    std::string message = "Caused by: Unterminated " + context.blockType + " starting at line " + std::to_string(context.startLine) + ":";
    message += "\n" + std::to_string(context.startLine) + " | " + context.startLexeme;
    if (context.blockType == "function" || context.blockType == "frame") message += " - unclosed " + context.blockType + " starts here";
    else message += " - unclosed block starts here";
    return message;
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::parseStatementWithContext(const std::string& blockType, const Token& contextToken) {
    if (check(TokenType::LEFT_BRACE)) {
        pushBlockContext(blockType, contextToken);
        auto stmt = statement();
        popBlockContext();
        return stmt;
    } else return statement();
}

std::shared_ptr<LM::Frontend::AST::Statement> Parser::typeDeclaration() {
    auto typeDecl = std::make_shared<LM::Frontend::AST::TypeDeclaration>();
    typeDecl->line = previous().line;
    Token name = consume(TokenType::IDENTIFIER, "Expected type name.");
    typeDecl->name = name.lexeme;
    consume(TokenType::EQUAL, "Expected '=' after type name.");
    if (match({TokenType::LEFT_BRACKET})) {
        auto listType = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
        listType->typeName = "list"; listType->isList = true;
        if (!check(TokenType::RIGHT_BRACKET)) listType->elementType = parseTypeAnnotation();
        else {
            auto anyType = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
            anyType->typeName = "any"; anyType->isPrimitive = true;
            listType->elementType = anyType;
        }
        consume(TokenType::RIGHT_BRACKET, "Expected ']' after list element type.");
        typeDecl->type = listType;
    } else if (match({TokenType::LEFT_BRACE})) {
        size_t savedCurrent = current; bool isDictionary = false;
        if (check(TokenType::IDENTIFIER) || isPrimitiveType(peek().type)) {
            Token firstToken = peek(); advance();
            if (match({TokenType::COLON})) {
                if (check(TokenType::IDENTIFIER) || isPrimitiveType(peek().type) || check(TokenType::LEFT_BRACKET) || check(TokenType::LEFT_BRACE)) {
                    if (isPrimitiveType(firstToken.type) || (firstToken.type == TokenType::IDENTIFIER && isKnownTypeName(firstToken.lexeme))) isDictionary = true;
                }
            }
        }
        current = savedCurrent;
        if (isDictionary) {
            auto dictType = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
            dictType->typeName = "dict"; dictType->isDict = true;
            Token keyToken = advance(); auto keyType = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
            if (isPrimitiveType(keyToken.type)) { keyType->typeName = tokenTypeToString(keyToken.type); keyType->isPrimitive = true; }
            else if (keyToken.lexeme == "any") { keyType->typeName = "any"; keyType->isPrimitive = true; }
            else if (keyToken.lexeme == "int") { keyType->typeName = "int"; keyType->isPrimitive = true; }
            else if (keyToken.lexeme == "str") { keyType->typeName = "str"; keyType->isPrimitive = true; }
            else { keyType->typeName = keyToken.lexeme; keyType->isUserDefined = true; }
            consume(TokenType::COLON, "Expected ':' in dictionary type.");
            dictType->keyType = keyType; dictType->valueType = parseTypeAnnotation();
            consume(TokenType::RIGHT_BRACE, "Expected '}' after dictionary type.");
            typeDecl->type = dictType;
        } else {
            auto structType = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
            structType->typeName = "struct"; structType->isStructural = true;
            while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
                if (match({TokenType::ELLIPSIS})) {
                    structType->hasRest = true;
                    if (check(TokenType::IDENTIFIER)) {
                        std::string baseRecordName = consume(TokenType::IDENTIFIER, "Expected base record name after '...'.").lexeme;
                        if (structType->baseRecord.empty()) structType->baseRecord = baseRecordName;
                        structType->baseRecords.push_back(baseRecordName);
                    }
                    if (check(TokenType::COMMA)) { consume(TokenType::COMMA, "Expected ',' after rest parameter."); continue; }
                    else if (check(TokenType::RIGHT_BRACE)) break;
                    else error("Expected ',' or '}' after rest parameter.");
                }
                std::string fieldName;
                if (check(TokenType::IDENTIFIER)) fieldName = consume(TokenType::IDENTIFIER, "Expected field name.").lexeme;
                else if (check(TokenType::STRING)) {
                    Token stringToken = consume(TokenType::STRING, "Expected field name.");
                    fieldName = stringToken.lexeme;
                    if (fieldName.size() >= 2 && (fieldName[0] == '"' || fieldName[0] == '\'') && (fieldName[fieldName.size()-1] == '"' || fieldName[fieldName.size()-1] == '\'')) fieldName = fieldName.substr(1, fieldName.size() - 2);
                } else { error("Expected field name."); return typeDecl; }
                consume(TokenType::COLON, "Expected ':' after field name.");
                structType->structuralFields.push_back({fieldName, parseTypeAnnotation()});
                if (!check(TokenType::RIGHT_BRACE)) match({TokenType::COMMA});
            }
            consume(TokenType::RIGHT_BRACE, "Expected '}' after structural type.");
            typeDecl->type = structType;
        }
    } else if (check(TokenType::IDENTIFIER) || isPrimitiveType(peek().type)) {
        auto firstType = parseTypeAnnotation();
        if (match({TokenType::PIPE})) {
            auto unionType = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
            unionType->typeName = "union"; unionType->isUnion = true; unionType->unionTypes.push_back(firstType);
            do { unionType->unionTypes.push_back(parseTypeAnnotation()); } while (match({TokenType::PIPE}));
            typeDecl->type = unionType;
        } else if (match({TokenType::AND})) {
            auto intersectionType = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
            intersectionType->typeName = "intersection"; intersectionType->isIntersection = true; intersectionType->unionTypes.push_back(firstType);
            do { intersectionType->unionTypes.push_back(parseTypeAnnotation()); } while (match({TokenType::AND}));
            typeDecl->type = intersectionType;
        } else if (match({TokenType::WHERE})) {
            firstType->isRefined = true; firstType->refinementCondition = expression(); typeDecl->type = firstType;
        } else typeDecl->type = firstType;
    } else if (match({TokenType::NIL})) {
        auto nilType = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
        nilType->typeName = "nil"; nilType->isPrimitive = true; typeDecl->type = nilType;
    } else error("Expected type definition after '='.");
    consume(TokenType::SEMICOLON, "Expected ';' after type declaration.");
    return typeDecl;
}

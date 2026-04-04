#include "../parser.hh"
#include "../../error/debugger.hh"
#include <stdexcept>
#include <limits>
#include <set>
#include <cmath>

using namespace LM::Frontend;
using namespace LM::Error;

std::shared_ptr<LM::Frontend::AST::Expression> Parser::expression() {
    return assignment();
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::assignment() {
    auto expr = logicalOr();

    if (match({TokenType::EQUAL, TokenType::PLUS_EQUAL, TokenType::MINUS_EQUAL, 
               TokenType::STAR_EQUAL, TokenType::SLASH_EQUAL, TokenType::MODULUS_EQUAL})) {
        Token op = previous();
        auto value = assignment();

        if (auto varExpr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr)) {
            auto assignExpr = std::make_shared<LM::Frontend::AST::AssignExpr>();
            assignExpr->line = op.line;
            assignExpr->name = varExpr->name;
            assignExpr->op = op.type;
            assignExpr->value = value;
            return assignExpr;
        } else if (auto memberExpr = std::dynamic_pointer_cast<LM::Frontend::AST::MemberExpr>(expr)) {
            auto setExpr = std::make_shared<LM::Frontend::AST::AssignExpr>();
            setExpr->line = op.line;
            setExpr->object = memberExpr->object;
            setExpr->member = memberExpr->name;
            setExpr->op = op.type;
            setExpr->value = value;
            return setExpr;
        } else if (auto indexExpr = std::dynamic_pointer_cast<LM::Frontend::AST::IndexExpr>(expr)) {
            auto subscriptSetExpr = std::make_shared<LM::Frontend::AST::AssignExpr>();
            subscriptSetExpr->line = op.line;
            subscriptSetExpr->object = indexExpr->object;
            subscriptSetExpr->index = indexExpr->index;
            subscriptSetExpr->op = op.type;
            subscriptSetExpr->value = value;
            return subscriptSetExpr;
        }

        error("Invalid assignment target.");
    }

    return expr;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::logicalOr() {
    auto expr = logicalAnd();

    while (match({TokenType::OR})) {
        Token op = previous();
        auto right = logicalAnd();
        
        auto logicalExpr = std::make_shared<LM::Frontend::AST::BinaryExpr>();
        logicalExpr->line = op.line;
        logicalExpr->left = expr;
        logicalExpr->op = op.type;
        logicalExpr->right = right;
        expr = logicalExpr;
    }

    return expr;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::logicalAnd() {
    auto expr = equality();

    while (match({TokenType::AND})) {
        Token op = previous();
        auto right = equality();

        auto logicalExpr = std::make_shared<LM::Frontend::AST::BinaryExpr>();
        logicalExpr->line = op.line;
        logicalExpr->left = expr;
        logicalExpr->op = op.type;
        logicalExpr->right = right;
        expr = logicalExpr;
    }

    return expr;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::equality() {
    auto expr = comparison();

    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        auto op = previous();
        auto right = comparison();

        auto binaryExpr = std::make_shared<LM::Frontend::AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        if (cstMode && config.detailedExpressionNodes) {
            auto binaryCSTNode = std::make_unique<CST::Node>(CST::NodeKind::BINARY_EXPR);
            binaryCSTNode->setDescription("equality expression");
            pushCSTContext(binaryCSTNode.get());
            binaryCSTNode->addToken(op);
            attachTriviaFromToken(op);
            binaryCSTNode->setSourceSpan(op.start, op.end);
            addChildToCurrentContext(std::move(binaryCSTNode));
            popCSTContext();
        }

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::comparison() {
    auto expr = term();

    if (match({TokenType::RANGE})) {
        auto rangeExpr = std::make_shared<LM::Frontend::AST::RangeExpr>();
        rangeExpr->line = previous().line;
        rangeExpr->start = expr;
        rangeExpr->end = term();
        rangeExpr->step = nullptr;
        rangeExpr->inclusive = true;
        
        if (cstMode && config.detailedExpressionNodes) {
            auto rangeCSTNode = std::make_unique<CST::Node>(CST::NodeKind::RANGE_EXPR);
            rangeCSTNode->setDescription("range expression");
            pushCSTContext(rangeCSTNode.get());
            Token rangeToken = previous();
            rangeCSTNode->addToken(rangeToken);
            attachTriviaFromToken(rangeToken);
            rangeCSTNode->setSourceSpan(rangeToken.start, rangeToken.end);
            addChildToCurrentContext(std::move(rangeCSTNode));
            popCSTContext();
        }
        
        return rangeExpr;
    }

    while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
        auto op = previous();
        auto right = term();

        auto binaryExpr = std::make_shared<LM::Frontend::AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        if (cstMode && config.detailedExpressionNodes) {
            auto binaryCSTNode = std::make_unique<CST::Node>(CST::NodeKind::BINARY_EXPR);
            binaryCSTNode->setDescription("comparison expression");
            pushCSTContext(binaryCSTNode.get());
            binaryCSTNode->addToken(op);
            attachTriviaFromToken(op);
            binaryCSTNode->setSourceSpan(op.start, op.end);
            addChildToCurrentContext(std::move(binaryCSTNode));
            popCSTContext();
        }

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::term() {
    auto expr = factor();

    while (match({TokenType::MINUS, TokenType::PLUS})) {
        auto op = previous();
        auto right = factor();

        auto binaryExpr = std::make_shared<LM::Frontend::AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        if (cstMode && config.detailedExpressionNodes) {
            auto binaryCSTNode = std::make_unique<CST::Node>(CST::NodeKind::BINARY_EXPR);
            binaryCSTNode->setDescription("arithmetic term expression");
            pushCSTContext(binaryCSTNode.get());
            binaryCSTNode->addToken(op);
            attachTriviaFromToken(op);
            binaryCSTNode->setSourceSpan(op.start, op.end);
            addChildToCurrentContext(std::move(binaryCSTNode));
            popCSTContext();
        }

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::factor() {
    auto expr = power();

    while (match({TokenType::SLASH, TokenType::STAR, TokenType::MODULUS})) {
        auto op = previous();
        auto right = unary();

        auto binaryExpr = std::make_shared<LM::Frontend::AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;

        if (cstMode && config.detailedExpressionNodes) {
            auto binaryCSTNode = std::make_unique<CST::Node>(CST::NodeKind::BINARY_EXPR);
            binaryCSTNode->setDescription("arithmetic factor expression");
            pushCSTContext(binaryCSTNode.get());
            binaryCSTNode->addToken(op);
            attachTriviaFromToken(op);
            binaryCSTNode->setSourceSpan(op.start, op.end);
            addChildToCurrentContext(std::move(binaryCSTNode));
            popCSTContext();
        }

        expr = binaryExpr;
    }

    return expr;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::power() {
    auto expr = unary();
    while (match({TokenType::POWER})) {
        auto op = previous();
        auto right = power();
        auto binaryExpr = createNodeWithContext<LM::Frontend::AST::BinaryExpr>();
        binaryExpr->line = op.line;
        binaryExpr->left = expr;
        binaryExpr->op = op.type;
        binaryExpr->right = right;
        
        if (cstMode && config.detailedExpressionNodes) {
            auto binaryCSTNode = std::make_unique<CST::Node>(CST::NodeKind::BINARY_EXPR);
            binaryCSTNode->setDescription("power expression");
            pushCSTContext(binaryCSTNode.get());
            binaryCSTNode->addToken(op);
            attachTriviaFromToken(op);
            binaryCSTNode->setSourceSpan(op.start, op.end);
            addChildToCurrentContext(std::move(binaryCSTNode));
            popCSTContext();
        } else {
            attachTriviaFromToken(op);
        }
        
        expr = binaryExpr;
    }
    return expr;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::unary() {
    if (match({TokenType::BANG, TokenType::MINUS, TokenType::PLUS})) {
        auto op = previous();
        auto right = unary();

        auto unaryExpr = std::make_shared<LM::Frontend::AST::UnaryExpr>();
        unaryExpr->line = op.line;
        unaryExpr->op = op.type;
        unaryExpr->right = right;

        if (cstMode && config.detailedExpressionNodes) {
            auto unaryCSTNode = std::make_unique<CST::Node>(CST::NodeKind::UNARY_EXPR);
            unaryCSTNode->setDescription("unary expression");
            pushCSTContext(unaryCSTNode.get());
            unaryCSTNode->addToken(op);
            attachTriviaFromToken(op);
            unaryCSTNode->setSourceSpan(op.start, op.end);
            addChildToCurrentContext(std::move(unaryCSTNode));
            popCSTContext();
        }

        return unaryExpr;
    }

    return call();
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::call() {
    auto expr = primary();

    while (true) {
        if (match({TokenType::LEFT_PAREN})) {
            expr = finishCall(expr);
        } else if (match({TokenType::DOT})) {
            auto dotToken = previous();
            if (check(TokenType::INT_LITERAL) || check(TokenType::FLOAT_LITERAL) || check(TokenType::SCIENTIFIC_LITERAL)) {
                auto numberToken = advance();
                auto indexExpr = std::make_shared<LM::Frontend::AST::IndexExpr>();
                indexExpr->line = numberToken.line;
                indexExpr->object = expr;
                auto indexLiteral = std::make_shared<LM::Frontend::AST::LiteralExpr>();
                indexLiteral->line = numberToken.line;
                try {
                    size_t pos;
                    long long indexValue = std::stoll(numberToken.lexeme, &pos);
                    if (pos != numberToken.lexeme.length()) throw std::invalid_argument("Invalid characters in integer");
                    indexLiteral->value = numberToken.lexeme;
                } catch (const std::exception&) {
                    error("Invalid tuple index: " + numberToken.lexeme);
                    indexLiteral->value = "0";
                }
                indexExpr->index = indexLiteral;
                expr = indexExpr;
            } else {
                auto name = consume(TokenType::IDENTIFIER, "Expected property name after '.'.");
                auto memberExpr = std::make_shared<LM::Frontend::AST::MemberExpr>();
                memberExpr->line = name.line;
                memberExpr->object = expr;
                memberExpr->name = name.lexeme;
                if (cstMode && config.detailedExpressionNodes) {
                    auto memberCSTNode = std::make_unique<CST::Node>(CST::NodeKind::MEMBER_EXPR);
                    memberCSTNode->setDescription("member access expression");
                    pushCSTContext(memberCSTNode.get());
                    memberCSTNode->addToken(dotToken);
                    memberCSTNode->addToken(name);
                    attachTriviaFromToken(dotToken);
                    attachTriviaFromToken(name);
                    memberCSTNode->setSourceSpan(dotToken.start, name.end);
                    addChildToCurrentContext(std::move(memberCSTNode));
                    popCSTContext();
                }
                expr = memberExpr;
            }
        } else if (match({TokenType::LEFT_BRACKET})) {
            auto leftBracket = previous();
            auto index = expression();
            auto rightBracket = consume(TokenType::RIGHT_BRACKET, "Expected ']' after index.");
            auto indexExpr = std::make_shared<LM::Frontend::AST::IndexExpr>();
            indexExpr->line = rightBracket.line;
            indexExpr->object = expr;
            indexExpr->index = index;
            if (cstMode && config.detailedExpressionNodes) {
                auto indexCSTNode = std::make_unique<CST::Node>(CST::NodeKind::INDEX_EXPR);
                indexCSTNode->setDescription("index access expression");
                pushCSTContext(indexCSTNode.get());
                indexCSTNode->addToken(leftBracket);
                indexCSTNode->addToken(rightBracket);
                attachTriviaFromToken(leftBracket);
                attachTriviaFromToken(rightBracket);
                indexCSTNode->setSourceSpan(leftBracket.start, rightBracket.end);
                addChildToCurrentContext(std::move(indexCSTNode));
                popCSTContext();
            }
            expr = indexExpr;
        } else if (match({TokenType::QUESTION})) {
            auto fallibleExpr = std::make_shared<LM::Frontend::AST::FallibleExpr>();
            fallibleExpr->line = previous().line;
            fallibleExpr->expression = expr;
            if (match({TokenType::ELSE})) {
                if (check(TokenType::IDENTIFIER)) fallibleExpr->elseVariable = consume(TokenType::IDENTIFIER, "Expected error variable name.").lexeme;
                fallibleExpr->elseHandler = statement();
            }
            expr = fallibleExpr;
        } else break;
    }
    return expr;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::finishCall(std::shared_ptr<LM::Frontend::AST::Expression> callee) {
    std::vector<std::shared_ptr<LM::Frontend::AST::Expression>> arguments;
    std::unordered_map<std::string, std::shared_ptr<LM::Frontend::AST::Expression>> namedArgs;
    std::vector<Token> callTokens;
    Token leftParen = previous();
    if (cstMode && config.detailedExpressionNodes) callTokens.push_back(leftParen);
    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            if (check(TokenType::IDENTIFIER) && peek().lexeme.length() > 0) {
                Token nameToken = peek(); advance();
                if (match({TokenType::EQUAL})) {
                    Token equalToken = previous();
                    if (cstMode && config.detailedExpressionNodes) { callTokens.push_back(nameToken); callTokens.push_back(equalToken); }
                    namedArgs[nameToken.lexeme] = expression();
                } else { current--; arguments.push_back(expression()); }
            } else arguments.push_back(expression());
            if (!match({TokenType::COMMA})) break;
            if (cstMode && config.detailedExpressionNodes) callTokens.push_back(previous());
        } while (true);
    }
    auto paren = consume(TokenType::RIGHT_PAREN, "Expected ')' after arguments.");
    if (cstMode && config.detailedExpressionNodes) callTokens.push_back(paren);
    auto callExpr = std::make_shared<LM::Frontend::AST::CallExpr>();
    callExpr->line = paren.line; callExpr->callee = callee; callExpr->arguments = arguments; callExpr->namedArgs = namedArgs;
    if (cstMode && config.detailedExpressionNodes) {
        auto callCSTNode = std::make_unique<CST::Node>(CST::NodeKind::CALL_EXPR);
        callCSTNode->setDescription("function call expression");
        pushCSTContext(callCSTNode.get());
        for (const auto& token : callTokens) { callCSTNode->addToken(token); attachTriviaFromToken(token); }
        if (!callTokens.empty()) callCSTNode->setSourceSpan(callTokens.front().start, callTokens.back().end);
        addChildToCurrentContext(std::move(callCSTNode));
        popCSTContext();
    }
    return callExpr;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::primary() {
    if (match({TokenType::FALSE})) {
        auto literalExpr = createNodeWithContext<LM::Frontend::AST::LiteralExpr>();
        literalExpr->line = previous().line; literalExpr->value = false;
        if (cstMode && config.detailedExpressionNodes) {
            auto literalCSTNode = std::make_unique<CST::Node>(CST::NodeKind::LITERAL_EXPR);
            literalCSTNode->setDescription("boolean literal (false)");
            literalCSTNode->addToken(previous()); attachTriviaFromToken(previous());
            literalCSTNode->setSourceSpan(previous().start, previous().end);
            addChildToCurrentContext(std::move(literalCSTNode));
        } else attachTriviaFromToken(previous());
        return literalExpr;
    }
    if (match({TokenType::TRUE})) {
        auto literalExpr = createNodeWithContext<LM::Frontend::AST::LiteralExpr>();
        literalExpr->line = previous().line; literalExpr->value = true;
        if (cstMode && config.detailedExpressionNodes) {
            auto literalCSTNode = std::make_unique<CST::Node>(CST::NodeKind::LITERAL_EXPR);
            literalCSTNode->setDescription("boolean literal (true)");
            literalCSTNode->addToken(previous()); attachTriviaFromToken(previous());
            literalCSTNode->setSourceSpan(previous().start, previous().end);
            addChildToCurrentContext(std::move(literalCSTNode));
        } else attachTriviaFromToken(previous());
        return literalExpr;
    }
    if (match({TokenType::NIL})) {
        auto literalExpr = createNodeWithContext<LM::Frontend::AST::LiteralExpr>();
        literalExpr->line = previous().line; literalExpr->value = nullptr;
        attachTriviaFromToken(previous()); return literalExpr;
    }
    if (match({TokenType::INT_LITERAL, TokenType::FLOAT_LITERAL, TokenType::SCIENTIFIC_LITERAL})) {
        auto token = previous(); auto literalExpr = createNodeWithContext<LM::Frontend::AST::LiteralExpr>();
        literalExpr->line = token.line; literalExpr->value = token.lexeme; literalExpr->literalType = token.type;
        if (cstMode && config.detailedExpressionNodes) {
            auto literalCSTNode = std::make_unique<CST::Node>(CST::NodeKind::LITERAL_EXPR);
            literalCSTNode->setDescription("number literal");
            literalCSTNode->addToken(token); attachTriviaFromToken(token);
            literalCSTNode->setSourceSpan(token.start, token.end);
            addChildToCurrentContext(std::move(literalCSTNode));
        } else attachTriviaFromToken(token);
        return literalExpr;
    }
    if (match({TokenType::STRING})) {
        auto literalExpr = std::make_shared<LM::Frontend::AST::LiteralExpr>();
        literalExpr->line = previous().line; literalExpr->value = parseStringLiteral(previous().lexeme);
        if (cstMode && config.detailedExpressionNodes) {
            auto literalCSTNode = std::make_unique<CST::Node>(CST::NodeKind::LITERAL_EXPR);
            literalCSTNode->setDescription("string literal");
            literalCSTNode->addToken(previous()); attachTriviaFromToken(previous());
            literalCSTNode->setSourceSpan(previous().start, previous().end);
            addChildToCurrentContext(std::move(literalCSTNode));
        }
        return literalExpr;
    }
    if (match({TokenType::INTERPOLATION_START})) {
        std::string startPart = previous().lexeme;
        if (startPart.size() >= 2 && startPart.front() == '"' && startPart.back() == '"') startPart = startPart.substr(1, startPart.length() - 2);
        auto interpolated = std::make_shared<LM::Frontend::AST::InterpolatedStringExpr>();
        interpolated->line = previous().line; interpolated->addStringPart(startPart);
        interpolated->addExpressionPart(expression());
        consume(TokenType::INTERPOLATION_END, "Expected '}' after interpolation expression.");
        while (check(TokenType::INTERPOLATION_START)) {
            advance(); std::string nextPart = previous().lexeme;
            if (nextPart.size() >= 2 && nextPart.front() == '"' && nextPart.back() == '"') nextPart = nextPart.substr(1, nextPart.length() - 2);
            interpolated->addStringPart(nextPart); interpolated->addExpressionPart(expression());
            consume(TokenType::INTERPOLATION_END, "Expected '}' after interpolation expression.");
        }
        if (check(TokenType::STRING)) { advance(); interpolated->addStringPart(parseStringLiteral(previous().lexeme)); }
        return interpolated;
    }
    if (match({TokenType::THIS})) {
        auto thisExpr = std::make_shared<LM::Frontend::AST::ThisExpr>();
        thisExpr->line = previous().line; return thisExpr;
    }
    if (match({TokenType::IDENTIFIER})) {
        auto token = previous();
        if (token.lexeme == "self" || token.lexeme == "this") {
            auto thisExpr = std::make_shared<LM::Frontend::AST::ThisExpr>();
            thisExpr->line = token.line; return thisExpr;
        } else {
            if (check(TokenType::LEFT_BRACE)) {
                auto objExpr = std::make_shared<LM::Frontend::AST::ObjectLiteralExpr>();
                objExpr->line = token.line; objExpr->constructorName = token.lexeme;
                advance();
                if (!check(TokenType::RIGHT_BRACE)) {
                    do {
                        Token keyToken = consume(TokenType::IDENTIFIER, "Expected property name in object literal.");
                        consume(TokenType::COLON, "Expected ':' after property name.");
                        objExpr->properties[keyToken.lexeme] = expression();
                    } while (match({TokenType::COMMA}));
                }
                consume(TokenType::RIGHT_BRACE, "Expected '}' after object literal properties."); return objExpr;
            } else {
                auto varExpr = createNodeWithContext<LM::Frontend::AST::VariableExpr>();
                varExpr->line = token.line; varExpr->name = token.lexeme;
                if (cstMode && config.detailedExpressionNodes) {
                    auto varCSTNode = std::make_unique<CST::Node>(CST::NodeKind::VARIABLE_EXPR);
                    varCSTNode->setDescription("variable reference");
                    varCSTNode->addToken(token); attachTriviaFromToken(token);
                    varCSTNode->setSourceSpan(token.start, token.end);
                    addChildToCurrentContext(std::move(varCSTNode));
                } else attachTriviaFromToken(token);
                return varExpr;
            }
        }
    }
    if (match({TokenType::SLEEP})) {
        auto varExpr = createNodeWithContext<LM::Frontend::AST::VariableExpr>();
        varExpr->line = previous().line; varExpr->name = "sleep"; attachTriviaFromToken(previous()); return varExpr;
    }
    if (match({TokenType::ERR})) {
        auto errorExpr = std::make_shared<LM::Frontend::AST::ErrorConstructExpr>();
        errorExpr->line = previous().line; consume(TokenType::LEFT_PAREN, "Expected '(' after 'err'.");
        if (check(TokenType::RIGHT_PAREN)) { errorExpr->errorType = "DefaultError"; consume(TokenType::RIGHT_PAREN, "Expected ')' after 'err()'."); return errorExpr; }
        errorExpr->errorType = consume(TokenType::IDENTIFIER, "Expected error type name.").lexeme;
        if (match({TokenType::LEFT_PAREN})) {
            if (!check(TokenType::RIGHT_PAREN)) { do { errorExpr->arguments.push_back(expression()); } while (match({TokenType::COMMA})); }
            consume(TokenType::RIGHT_PAREN, "Expected ')' after error constructor arguments.");
        }
        consume(TokenType::RIGHT_PAREN, "Expected ')' after error construction."); return errorExpr;
    }
    if (match({TokenType::OK})) {
        auto okExpr = std::make_shared<LM::Frontend::AST::OkConstructExpr>();
        okExpr->line = previous().line; consume(TokenType::LEFT_PAREN, "Expected '(' after 'ok'.");
        okExpr->value = expression(); consume(TokenType::RIGHT_PAREN, "Expected ')' after ok value."); return okExpr;
    }
    if (check(TokenType::FN)) return lambdaExpression();
    if (match({TokenType::LEFT_PAREN})) {
        auto leftParen = previous();
        if (check(TokenType::RIGHT_PAREN)) {
            auto rightParen = consume(TokenType::RIGHT_PAREN, "Expected ')' after empty tuple.");
            auto tupleExpr = std::make_shared<LM::Frontend::AST::TupleExpr>();
            tupleExpr->line = rightParen.line; return tupleExpr;
        }
        auto firstExpr = expression();
        if (match({TokenType::COMMA})) {
            std::vector<std::shared_ptr<LM::Frontend::AST::Expression>> elements; elements.push_back(firstExpr);
            do { if (check(TokenType::RIGHT_PAREN)) break; elements.push_back(expression()); } while (match({TokenType::COMMA}));
            auto rightParen = consume(TokenType::RIGHT_PAREN, "Expected ')' after tuple elements.");
            auto tupleExpr = std::make_shared<LM::Frontend::AST::TupleExpr>();
            tupleExpr->line = rightParen.line; tupleExpr->elements = elements; return tupleExpr;
        } else {
            auto rightParen = consume(TokenType::RIGHT_PAREN, "Expected ')' after expression.");
            auto groupingExpr = std::make_shared<LM::Frontend::AST::GroupingExpr>();
            groupingExpr->line = rightParen.line; groupingExpr->expression = firstExpr;
            if (cstMode && config.detailedExpressionNodes) {
                auto groupingCSTNode = std::make_unique<CST::Node>(CST::NodeKind::GROUPING_EXPR);
                groupingCSTNode->setDescription("grouping expression");
                pushCSTContext(groupingCSTNode.get());
                groupingCSTNode->addToken(leftParen); groupingCSTNode->addToken(rightParen);
                attachTriviaFromToken(leftParen); attachTriviaFromToken(rightParen);
                groupingCSTNode->setSourceSpan(leftParen.start, rightParen.end);
                addChildToCurrentContext(std::move(groupingCSTNode)); popCSTContext();
            }
            return groupingExpr;
        }
    }
    if (match({TokenType::LEFT_BRACKET})) {
        auto leftBracket = previous();
        std::vector<std::shared_ptr<LM::Frontend::AST::Expression>> elements;
        if (!check(TokenType::RIGHT_BRACKET)) { do { elements.push_back(expression()); } while (match({TokenType::COMMA})); }
        auto rightBracket = consume(TokenType::RIGHT_BRACKET, "Expected ']' after list elements.");
        auto listExpr = std::make_shared<LM::Frontend::AST::ListExpr>();
        listExpr->line = rightBracket.line; listExpr->elements = elements;
        if (cstMode && config.detailedExpressionNodes) {
            auto listCSTNode = std::make_unique<CST::Node>(CST::NodeKind::LITERAL_EXPR);
            listCSTNode->setDescription("list literal expression");
            listCSTNode->addToken(leftBracket); listCSTNode->addToken(rightBracket);
            attachTriviaFromToken(leftBracket); attachTriviaFromToken(rightBracket);
            addChildToCurrentContext(std::move(listCSTNode));
        }
        return listExpr;
    }
    if (match({TokenType::LEFT_BRACE})) {
        auto leftBrace = previous();
        std::vector<std::pair<std::shared_ptr<LM::Frontend::AST::Expression>, std::shared_ptr<LM::Frontend::AST::Expression>>> entries;
        if (!check(TokenType::RIGHT_BRACE)) {
            do {
                auto key = expression(); consume(TokenType::COLON, "Expected ':' after dictionary key.");
                auto value = expression(); entries.push_back({key, value});
            } while (match({TokenType::COMMA}));
        }
        auto rightBrace = consume(TokenType::RIGHT_BRACE, "Expected '}' after dictionary entries.");
        auto dictExpr = std::make_shared<LM::Frontend::AST::DictExpr>();
        dictExpr->line = rightBrace.line; dictExpr->entries = entries;
        if (cstMode && config.detailedExpressionNodes) {
            auto dictCSTNode = std::make_unique<CST::Node>(CST::NodeKind::LITERAL_EXPR);
            dictCSTNode->setDescription("dictionary literal expression");
            dictCSTNode->addToken(leftBrace); dictCSTNode->addToken(rightBrace);
            attachTriviaFromToken(leftBrace); attachTriviaFromToken(rightBrace);
            addChildToCurrentContext(std::move(dictCSTNode));
        }
        return dictExpr;
    }
    if (current > 0 && current < scanner.getTokens().size() && scanner.getTokens()[current-1].type == TokenType::LEFT_BRACE && scanner.getTokens()[current].type == TokenType::RIGHT_BRACE) {
        return makeErrorExpr("Empty dictionary not allowed here");
    } else if (match({TokenType::SELF, TokenType::THIS})) {
        auto thisExpr = createNodeWithContext<LM::Frontend::AST::ThisExpr>();
        thisExpr->line = previous().line; attachTriviaFromToken(previous()); return thisExpr;
    } else if (match({TokenType::SUPER})) {
        auto superExpr = createNodeWithContext<LM::Frontend::AST::SuperExpr>();
        superExpr->line = previous().line; attachTriviaFromToken(previous()); return superExpr;
    } else {
        if (!isAtEnd() && !check(TokenType::SEMICOLON) && !check(TokenType::RIGHT_BRACE) && !check(TokenType::RIGHT_PAREN) && !check(TokenType::RIGHT_BRACKET)) {
            error("Expected expression.", false); advance();
        }
        return makeErrorExpr();
    }
}

std::shared_ptr<LM::Frontend::AST::LambdaExpr> Parser::lambdaExpression() {
    auto lambda = std::make_shared<LM::Frontend::AST::LambdaExpr>();
    lambda->line = peek().line;
    consume(TokenType::FN, "Expected 'fn' at start of lambda expression.");
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'fn'.");
    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            std::string paramName = consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme;
            std::shared_ptr<LM::Frontend::AST::TypeAnnotation> paramType = nullptr;
            if (match({TokenType::COLON})) paramType = parseTypeAnnotation();
            lambda->params.push_back({paramName, paramType});
        } while (match({TokenType::COMMA}));
    }
    consume(TokenType::RIGHT_PAREN, "Expected ')' after lambda parameters.");
    if (match({TokenType::COLON})) lambda->returnType = parseTypeAnnotation();
    consume(TokenType::LEFT_BRACE, "Expected '{' before lambda body.");
    auto lambdaBody = std::make_shared<LM::Frontend::AST::BlockStatement>();
    lambdaBody->line = previous().line;
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) lambdaBody->statements.push_back(declaration());
    consume(TokenType::RIGHT_BRACE, "Expected '}' after lambda body.");
    lambda->body = lambdaBody;
    return lambda;
}

#include "../parser.hh"

using namespace LM::Frontend;

std::shared_ptr<LM::Frontend::AST::Expression> Parser::parsePattern() {
    if (match({TokenType::UNDERSCORE, TokenType::DEFAULT})) {
        auto varExpr = std::make_shared<LM::Frontend::AST::VariableExpr>();
        varExpr->line = previous().line;
        varExpr->name = "_";
        return varExpr;
    }
    if (match({TokenType::VAL})) return parseValPattern();
    if (match({TokenType::ERR})) return parseErrPattern();
    if (match({TokenType::LEFT_BRACKET})) return parseListPattern();
    if (match({TokenType::LEFT_BRACE})) return parseDictPattern();
    if (match({TokenType::LEFT_PAREN})) return parseTuplePattern();
    if (check(TokenType::IDENTIFIER)) {
        // Look ahead for potential qualified binding pattern: Type.Variant(args)
        int lookahead = 1;
        const auto& tokens = scanner.getTokens();
        while (current + lookahead < tokens.size() && 
               (tokens[current + lookahead].type == TokenType::DOT || 
                tokens[current + lookahead].type == TokenType::IDENTIFIER)) {
            lookahead++;
        }
        if (current + lookahead < tokens.size() && tokens[current + lookahead].type == TokenType::LEFT_PAREN) {
            return parseBindingPattern();
        }

        if (isErrorType(peek().lexeme)) return parseErrorTypePattern();
    }
    return expression();
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::parseBindingPattern() {
    std::string typeName = consume(TokenType::IDENTIFIER, "Expected type name for binding pattern.").lexeme;
    while (match({TokenType::DOT})) {
        typeName += "." + consume(TokenType::IDENTIFIER, "Expected variant name after '.' in binding pattern.").lexeme;
    }

    auto pattern = std::make_shared<LM::Frontend::AST::BindingPatternExpr>();
    pattern->line = previous().line;
    pattern->typeName = typeName;
    consume(TokenType::LEFT_PAREN, "Expected '(' after type name in binding pattern.");
    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            pattern->variableNames.push_back(consume(TokenType::IDENTIFIER, "Expected variable name in binding pattern.").lexeme);
        } while (match({TokenType::COMMA}));
    }
    consume(TokenType::RIGHT_PAREN, "Expected ')' after binding variables.");
    return pattern;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::parseListPattern() {
    auto pattern = std::make_shared<LM::Frontend::AST::ListPatternExpr>();
    pattern->line = previous().line;
    if (!check(TokenType::RIGHT_BRACKET)) {
        do {
            if (match({TokenType::ELLIPSIS})) {
                if (check(TokenType::IDENTIFIER)) pattern->restElement = consume(TokenType::IDENTIFIER, "Expected identifier after '...'.").lexeme;
                break;
            }
            pattern->elements.push_back(parsePattern());
        } while (match({TokenType::COMMA}));
    }
    consume(TokenType::RIGHT_BRACKET, "Expected ']' after list pattern.");
    return pattern;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::parseDictPattern() {
    auto pattern = std::make_shared<LM::Frontend::AST::DictPatternExpr>();
    pattern->line = previous().line;
    if (!check(TokenType::RIGHT_BRACE)) {
        do {
            if (match({TokenType::ELLIPSIS})) {
                pattern->hasRestElement = true;
                if (check(TokenType::IDENTIFIER)) pattern->restBinding = consume(TokenType::IDENTIFIER, "Expected identifier after '...'.").lexeme;
                break;
            }
            auto key = consume(TokenType::IDENTIFIER, "Expected key in dict pattern.").lexeme;
            std::optional<std::string> binding;
            if (match({TokenType::COLON})) {
                binding = consume(TokenType::IDENTIFIER, "Expected binding name after ':'.") .lexeme;
            }
            pattern->fields.push_back({key, binding});
        } while (match({TokenType::COMMA}));
    }
    consume(TokenType::RIGHT_BRACE, "Expected '}' after dict pattern.");
    return pattern;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::parseTuplePattern() {
    auto pattern = std::make_shared<LM::Frontend::AST::TuplePatternExpr>();
    pattern->line = previous().line;
    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            pattern->elements.push_back(parsePattern());
        } while (match({TokenType::COMMA}));
    }
    consume(TokenType::RIGHT_PAREN, "Expected ')' after tuple pattern.");
    return pattern;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::parseValPattern() {
    auto pattern = std::make_shared<LM::Frontend::AST::ValPatternExpr>();
    pattern->line = previous().line;
    pattern->variableName = consume(TokenType::IDENTIFIER, "Expected variable name after 'val'.").lexeme;
    return pattern;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::parseErrPattern() {
    auto pattern = std::make_shared<LM::Frontend::AST::ErrPatternExpr>();
    pattern->line = previous().line;
    pattern->variableName = consume(TokenType::IDENTIFIER, "Expected variable name after 'err'.").lexeme;
    if (match({TokenType::COLON})) pattern->errorType = consume(TokenType::IDENTIFIER, "Expected error type after ':'.").lexeme;
    return pattern;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::parseErrorTypePattern() {
    auto typeName = consume(TokenType::IDENTIFIER, "Expected error type name.").lexeme;
    auto pattern = std::make_shared<LM::Frontend::AST::ErrorTypePatternExpr>();
    pattern->line = previous().line;
    pattern->errorType = typeName;
    if (match({TokenType::LEFT_PAREN})) {
        if (!check(TokenType::RIGHT_PAREN)) {
            do {
                pattern->parameterNames.push_back(consume(TokenType::IDENTIFIER, "Expected parameter name.").lexeme);
            } while (match({TokenType::COMMA}));
        }
        consume(TokenType::RIGHT_PAREN, "Expected ')' after error parameters.");
    }
    return pattern;
}

bool Parser::isErrorType(const std::string& name) {
    if (name.length() >= 5 && name.substr(name.length() - 5) == "Error") return true;
    static const std::set<std::string> builtins = {"IOError", "NetworkError", "TypeError", "ValueError", "KeyError"};
    return builtins.count(name) > 0;
}

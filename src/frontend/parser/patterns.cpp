#include "../parser.hh"

using namespace LM::Frontend;

// Helper method to create TypeAnnotation from any type token
std::shared_ptr<LM::Frontend::AST::TypeAnnotation> Parser::createTypeAnnotationFromToken(const Token& token) {
    auto type = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
    
    switch (token.type) {
        case TokenType::INT_TYPE: type->typeName = "int"; type->isPrimitive = true; break;
        case TokenType::INT8_TYPE: type->typeName = "i8"; type->isPrimitive = true; break;
        case TokenType::INT16_TYPE: type->typeName = "i16"; type->isPrimitive = true; break;
        case TokenType::INT32_TYPE: type->typeName = "i32"; type->isPrimitive = true; break;
        case TokenType::INT64_TYPE: type->typeName = "i64"; type->isPrimitive = true; break;
        case TokenType::INT128_TYPE: type->typeName = "i128"; type->isPrimitive = true; break;
        case TokenType::UINT_TYPE: type->typeName = "uint"; type->isPrimitive = true; break;
        case TokenType::UINT8_TYPE: type->typeName = "u8"; type->isPrimitive = true; break;
        case TokenType::UINT16_TYPE: type->typeName = "u16"; type->isPrimitive = true; break;
        case TokenType::UINT32_TYPE: type->typeName = "u32"; type->isPrimitive = true; break;
        case TokenType::UINT64_TYPE: type->typeName = "u64"; type->isPrimitive = true; break;
        case TokenType::UINT128_TYPE: type->typeName = "u128"; type->isPrimitive = true; break;
        case TokenType::FLOAT_TYPE: type->typeName = "float"; type->isPrimitive = true; break;
        case TokenType::FLOAT32_TYPE: type->typeName = "f32"; type->isPrimitive = true; break;
        case TokenType::FLOAT64_TYPE: type->typeName = "f64"; type->isPrimitive = true; break;
        case TokenType::STR_TYPE: type->typeName = "str"; type->isPrimitive = true; break;
        case TokenType::BOOL_TYPE: type->typeName = "bool"; type->isPrimitive = true; break;
        case TokenType::USER_TYPE: type->typeName = token.lexeme; type->isUserDefined = true; break;
        case TokenType::FUNCTION_TYPE: type->typeName = "function"; type->isFunction = true; break;
        case TokenType::LIST_TYPE: type->typeName = "list"; type->isList = true; break;
        case TokenType::DICT_TYPE: type->typeName = "dict"; type->isDict = true; break;
        case TokenType::ARRAY_TYPE: type->typeName = "array"; type->isList = true; break;
        case TokenType::ENUM_TYPE: type->typeName = "enum"; break;
        case TokenType::SUM_TYPE: type->typeName = "sum"; type->isUnion = true; break;
        case TokenType::UNION_TYPE: type->typeName = "union"; type->isUnion = true; break;
        case TokenType::OPTION_TYPE: type->typeName = "option"; break;
        case TokenType::RESULT_TYPE: type->typeName = "result"; break;
        case TokenType::ANY_TYPE: type->typeName = "any"; type->isPrimitive = true; break;
        case TokenType::NIL_TYPE: type->typeName = "nil"; type->isPrimitive = true; break;
        case TokenType::CHANNEL_TYPE: type->typeName = "channel"; break;
        case TokenType::ATOMIC_TYPE: type->typeName = "atomic"; break;
        default:
            // Fallback for unknown tokens
            type->typeName = token.lexeme;
            break;
    }
    
    return type;
}

std::shared_ptr<LM::Frontend::AST::Expression> Parser::parsePattern() {
    if (match({TokenType::UNDERSCORE, TokenType::DEFAULT})) {
        auto varExpr = std::make_shared<LM::Frontend::AST::VariableExpr>();
        varExpr->line = previous().line;
        varExpr->name = "_";
        return varExpr;
    }
    if (match({TokenType::VAL})) return parseValPattern();
    if (match({TokenType::ERR})) return parseErrPattern();
    // Handle all type keywords as type patterns comprehensively
    if (check(TokenType::INT_TYPE) || check(TokenType::INT8_TYPE) || check(TokenType::INT16_TYPE) ||
        check(TokenType::INT32_TYPE) || check(TokenType::INT64_TYPE) || check(TokenType::INT128_TYPE) ||
        check(TokenType::UINT_TYPE) || check(TokenType::UINT8_TYPE) || check(TokenType::UINT16_TYPE) ||
        check(TokenType::UINT32_TYPE) || check(TokenType::UINT64_TYPE) || check(TokenType::UINT128_TYPE) ||
        check(TokenType::FLOAT_TYPE) || check(TokenType::FLOAT32_TYPE) || check(TokenType::FLOAT64_TYPE) ||
        check(TokenType::STR_TYPE) || check(TokenType::BOOL_TYPE) || check(TokenType::USER_TYPE) ||
        check(TokenType::FUNCTION_TYPE) || check(TokenType::LIST_TYPE) || check(TokenType::DICT_TYPE) ||
        check(TokenType::ARRAY_TYPE) || check(TokenType::ENUM_TYPE) || check(TokenType::SUM_TYPE) ||
        check(TokenType::UNION_TYPE) || check(TokenType::OPTION_TYPE) || check(TokenType::RESULT_TYPE) ||
        check(TokenType::ANY_TYPE) || check(TokenType::NIL_TYPE) || check(TokenType::CHANNEL_TYPE) ||
        check(TokenType::ATOMIC_TYPE)) {
        
        auto token = advance();
        auto typePattern = std::make_shared<LM::Frontend::AST::TypePatternExpr>();
        typePattern->line = token.line;
        typePattern->type = createTypeAnnotationFromToken(token);
        return typePattern;
    }
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
        
        // Check if this is a variable pattern (followed by WHERE or => without parentheses)
        auto varLookahead = 1;
        const auto& patternTokens = scanner.getTokens();
        bool isVariablePattern = false;
        
        if (current + varLookahead < patternTokens.size()) {
            auto nextToken = patternTokens[current + varLookahead];
            if (nextToken.type == TokenType::WHERE || nextToken.type == TokenType::ARROW) {
                isVariablePattern = true;
            }
        }
        
        if (isVariablePattern) {
            // This is a variable pattern, not a type alias
            auto token = advance();
            auto varExpr = std::make_shared<LM::Frontend::AST::VariableExpr>();
            varExpr->line = token.line;
            varExpr->name = token.lexeme;
            return varExpr;
        } else {
            // Handle potential type aliases - treat IDENTIFIER as type pattern
            auto token = advance();
            auto typePattern = std::make_shared<LM::Frontend::AST::TypePatternExpr>();
            typePattern->line = token.line;
            auto type = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
            type->typeName = token.lexeme;
            type->isUserDefined = true; // Mark as potentially user-defined type alias
            typePattern->type = type;
            return typePattern;
        }
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

#include "../parser.hh"
#include "../../error/debugger.hh"
#include <stdexcept>
#include <limits>
#include <set>
#include <cmath>

using namespace LM::Frontend;
using namespace LM::Error;

std::shared_ptr<LM::Frontend::AST::TypeAnnotation> Parser::parseTypeAnnotation() {
    auto type = parseBasicType();
    if (check(TokenType::PIPE)) {
        auto unionType = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
        unionType->typeName = "union"; unionType->isUnion = true; unionType->unionTypes.push_back(type);
        while (match({TokenType::PIPE})) unionType->unionTypes.push_back(parseBasicType());
        return unionType;
    }
    if (check(TokenType::AND)) {
        auto intersectionType = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
        intersectionType->typeName = "intersection"; intersectionType->isIntersection = true; intersectionType->unionTypes.push_back(type);
        while (match({TokenType::AND})) intersectionType->unionTypes.push_back(parseBasicType());
        return intersectionType;
    }
    if (match({TokenType::WHERE})) {
        type->isRefined = true; type->refinementCondition = expression();
    }
    return type;
}

bool Parser::isPrimitiveType(TokenType type) {
    return type == TokenType::INT_TYPE || type == TokenType::INT8_TYPE || type == TokenType::INT16_TYPE ||
           type == TokenType::INT32_TYPE || type == TokenType::INT64_TYPE || type == TokenType::INT128_TYPE ||
           type == TokenType::UINT_TYPE || type == TokenType::UINT8_TYPE || type == TokenType::UINT16_TYPE || type == TokenType::UINT32_TYPE ||
           type == TokenType::UINT64_TYPE || type == TokenType::UINT128_TYPE || type == TokenType::FLOAT_TYPE || type == TokenType::FLOAT32_TYPE ||
           type == TokenType::FLOAT64_TYPE || type == TokenType::STR_TYPE || type == TokenType::BOOL_TYPE ||
           type == TokenType::ANY_TYPE || type == TokenType::NIL_TYPE;
}

std::string Parser::tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::INT_TYPE: return "int";
        case TokenType::INT8_TYPE: return "i8";
        case TokenType::INT16_TYPE: return "i16";
        case TokenType::INT32_TYPE: return "i32";
        case TokenType::INT64_TYPE: return "i64";
        case TokenType::INT128_TYPE: return "i128";
        case TokenType::UINT_TYPE: return "uint";
        case TokenType::UINT8_TYPE: return "u8";
        case TokenType::UINT16_TYPE: return "u16";
        case TokenType::UINT32_TYPE: return "u32";
        case TokenType::UINT64_TYPE: return "u64";
        case TokenType::UINT128_TYPE: return "u128";
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

std::shared_ptr<LM::Frontend::AST::TypeAnnotation> Parser::parseUnionType() {
    auto unionType = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
    unionType->typeName = "union"; unionType->isUnion = true;
    unionType->unionTypes.push_back(parseBasicType());
    while (match({TokenType::PIPE})) unionType->unionTypes.push_back(parseBasicType());
    return unionType;
}

std::shared_ptr<LM::Frontend::AST::TypeAnnotation> Parser::parseBasicType() {
    auto type = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
    if (match({TokenType::LEFT_BRACKET})) {
        auto type = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
        type->isList = true; type->typeName = "list";
        if (!check(TokenType::RIGHT_BRACKET)) type->elementType = parseBasicType();
        else {
            auto anyType = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
            anyType->typeName = "list"; anyType->isPrimitive = true; type->elementType = anyType;
        }
        consume(TokenType::RIGHT_BRACKET, "Expected ']' after list element type.");
        return type;
    }
    if (match({TokenType::LEFT_PAREN})) {
        type->isTuple = true; type->typeName = "tuple";
        if (!check(TokenType::RIGHT_PAREN)) { do { type->tupleTypes.push_back(parseBasicType()); } while (match({TokenType::COMMA})); }
        consume(TokenType::RIGHT_PAREN, "Expected ')' after tuple element types.");
        return type;
    }
    if (match({TokenType::LEFT_BRACE})) return parseBraceType();
    if (check(TokenType::IDENTIFIER) && !isPrimitiveType(peek().type) && !isKnownTypeName(peek().lexeme)) {
        type->typeName = consume(TokenType::IDENTIFIER, "Expected type name.").lexeme; type->isUserDefined = true;
    } else if (match({TokenType::INT_TYPE})) { type->typeName = "int"; type->isPrimitive = true; }
    else if (match({TokenType::INT8_TYPE})) { type->typeName = "i8"; type->isPrimitive = true; }
    else if (match({TokenType::INT16_TYPE})) { type->typeName = "i16"; type->isPrimitive = true; }
    else if (match({TokenType::INT32_TYPE})) { type->typeName = "i32"; type->isPrimitive = true; }
    else if (match({TokenType::INT64_TYPE})) { type->typeName = "i64"; type->isPrimitive = true; }
    else if (match({TokenType::INT128_TYPE})) { type->typeName = "i128"; type->isPrimitive = true; }
    else if (match({TokenType::UINT_TYPE})) { type->typeName = "uint"; type->isPrimitive = true; }
    else if (match({TokenType::UINT8_TYPE})) { type->typeName = "u8"; type->isPrimitive = true; }
    else if (match({TokenType::UINT16_TYPE})) { type->typeName = "u16"; type->isPrimitive = true; }
    else if (match({TokenType::UINT32_TYPE})) { type->typeName = "u32"; type->isPrimitive = true; }
    else if (match({TokenType::UINT64_TYPE})) { type->typeName = "u64"; type->isPrimitive = true; }
    else if (match({TokenType::UINT128_TYPE})) { type->typeName = "u128"; type->isPrimitive = true; }
    else if (match({TokenType::FLOAT_TYPE})) { type->typeName = "float"; type->isPrimitive = true; }
    else if (match({TokenType::FLOAT32_TYPE})) { type->typeName = "f32"; type->isPrimitive = true; }
    else if (match({TokenType::FLOAT64_TYPE})) { type->typeName = "f64"; type->isPrimitive = true; }
    else if (match({TokenType::STR_TYPE})) { type->typeName = "str"; type->isPrimitive = true; }
    else if (match({TokenType::BOOL_TYPE})) { type->typeName = "bool"; type->isPrimitive = true; }
    else if (match({TokenType::ANY_TYPE})) { type->typeName = "any"; type->isPrimitive = true; }
    else if (match({TokenType::NIL_TYPE}) || match({TokenType::NIL})) { type->typeName = "nil"; type->isPrimitive = true; }
    else if (match({TokenType::LIST_TYPE})) { type->typeName = "list"; type->isList = true; }
    else if (match({TokenType::DICT_TYPE})) { type->typeName = "dict"; type->isDict = true; }
    else if (match({TokenType::ARRAY_TYPE})) { type->typeName = "array"; type->isList = true; }
    else if (match({TokenType::OPTION_TYPE})) type->typeName = "option";
    else if (match({TokenType::RESULT_TYPE})) type->typeName = "result";
    else if (match({TokenType::CHANNEL_TYPE})) type->typeName = "channel";
    else if (match({TokenType::ATOMIC_TYPE})) type->typeName = "atomic";
    else if (match({TokenType::FN})) {
        auto funcType = parseFunctionTypeAnnotation();
        auto type = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
        type->typeName = "function"; type->isFunction = true;
        type->functionParameters = funcType->parameters; type->returnType = funcType->returnType;
        return type;
    } else if (match({TokenType::FUNCTION_TYPE})) return parseLegacyFunctionType();
    else if (match({TokenType::ENUM_TYPE})) type->typeName = "enum";
    else if (match({TokenType::SUM_TYPE})) type->typeName = "sum";
    else if (match({TokenType::UNION_TYPE})) { type->typeName = "union"; type->isUnion = true; }
    else if (match({TokenType::STRING})) {
        std::string literalValue = previous().lexeme;
        if (literalValue.size() >= 2 && (literalValue[0] == '"' || literalValue[0] == '\'') && (literalValue[literalValue.size()-1] == '"' || literalValue[literalValue.size()-1] == '\'')) literalValue = literalValue.substr(1, literalValue.size() - 2);
        type->typeName = "\"" + literalValue + "\""; type->isPrimitive = true;
    }
    if (match({TokenType::QUESTION})) {
        if (check(TokenType::IDENTIFIER)) {
            type->isFallible = true; type->errorTypes.push_back(consume(TokenType::IDENTIFIER, "Expected error type after '?'.").lexeme);
            while (match({TokenType::COMMA})) type->errorTypes.push_back(consume(TokenType::IDENTIFIER, "Expected error type after ','.").lexeme);
        } else type->isOptional = true;
    }
    return type;
}

std::shared_ptr<LM::Frontend::AST::TypeAnnotation> Parser::parseBraceType() {
    bool isDictionary = false;
    if (!check(TokenType::RIGHT_BRACE)) {
        Token firstToken = peek();
        if (isPrimitiveType(firstToken.type)) isDictionary = true;
        else if (firstToken.type == TokenType::IDENTIFIER && isKnownTypeName(firstToken.lexeme)) isDictionary = true;
    }
    if (isDictionary) {
        auto type = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
        type->isDict = true; type->typeName = "dict"; type->keyType = parseBasicType();
        consume(TokenType::COLON, "Expected ':' in dictionary type.");
        type->valueType = parseBasicType(); consume(TokenType::RIGHT_BRACE, "Expected '}' after dictionary type.");
        return type;
    } else {
        auto type = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
        type->isStructural = true; type->typeName = "struct";
        while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
            if (match({TokenType::ELLIPSIS})) {
                type->hasRest = true;
                if (check(TokenType::IDENTIFIER)) {
                    std::string baseRecordName = consume(TokenType::IDENTIFIER, "Expected base record name after '...'.").lexeme;
                    if (type->baseRecord.empty()) type->baseRecord = baseRecordName;
                    type->baseRecords.push_back(baseRecordName);
                }
                if (match({TokenType::COMMA})) continue;
                else if (check(TokenType::RIGHT_BRACE)) break;
                else error("Expected ',' or '}' after rest parameter.");
            }
            std::string fieldName;
            if (check(TokenType::IDENTIFIER)) fieldName = consume(TokenType::IDENTIFIER, "Expected field name.").lexeme;
            else if (check(TokenType::STRING)) {
                Token stringToken = consume(TokenType::STRING, "Expected field name.");
                fieldName = stringToken.lexeme;
                if (fieldName.size() >= 2 && (fieldName[0] == '"' || fieldName[0] == '\'') && (fieldName[fieldName.size()-1] == '"' || fieldName[fieldName.size()-1] == '\'')) fieldName = fieldName.substr(1, fieldName.size() - 2);
            } else { error("Expected field name."); break; }
            consume(TokenType::COLON, "Expected ':' after field name.");
            type->structuralFields.push_back({fieldName, parseBasicType()});
            if (!check(TokenType::RIGHT_BRACE)) match({TokenType::COMMA});
        }
        consume(TokenType::RIGHT_BRACE, "Expected '}' after structural type."); return type;
    }
}

std::shared_ptr<LM::Frontend::AST::TypeAnnotation> Parser::parseDictionaryType() {
    auto type = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
    type->isDict = true; type->typeName = "dict"; type->keyType = parseBasicType();
    consume(TokenType::COLON, "Expected ':' in dictionary type.");
    type->valueType = parseBasicType(); consume(TokenType::RIGHT_BRACE, "Expected '}' after dictionary type.");
    return type;
}

bool Parser::isKnownTypeName(const std::string& name) {
    return name == "any" || name == "str" || name == "int" || name == "float" || 
           name == "bool" || name == "list" || name == "dict" || name == "option" || 
           name == "result" || name == "i8" || name == "i16" || name == "i32" || 
           name == "i64" || name == "u8" || name == "u16" || name == "u32" || 
           name == "u64" || name == "f32" || name == "f64" || name == "uint" ||
           name == "nil" || name == "tuple" || name == "function";
}

std::shared_ptr<LM::Frontend::AST::TypeAnnotation> Parser::parseStructuralType(const std::string& typeName) {
    auto type = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
    type->isStructural = true; type->typeName = typeName.empty() ? "struct" : typeName;
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        if (match({TokenType::ELLIPSIS})) {
            type->hasRest = true;
            if (check(TokenType::IDENTIFIER)) {
                std::string baseRecordName = consume(TokenType::IDENTIFIER, "Expected base record name after '...'.").lexeme;
                if (type->baseRecord.empty()) type->baseRecord = baseRecordName;
                type->baseRecords.push_back(baseRecordName);
            }
            if (match({TokenType::COMMA})) continue;
            else if (check(TokenType::RIGHT_BRACE)) break;
            else error("Expected ',' or '}' after rest parameter.");
        }
        std::string fieldName;
        if (check(TokenType::IDENTIFIER)) fieldName = consume(TokenType::IDENTIFIER, "Expected field name.").lexeme;
        else if (check(TokenType::STRING)) {
            Token stringToken = consume(TokenType::STRING, "Expected field name.");
            fieldName = stringToken.lexeme;
            if (fieldName.size() >= 2 && (fieldName[0] == '"' || fieldName[0] == '\'') && (fieldName[fieldName.size()-1] == '"' || fieldName[fieldName.size()-1] == '\'')) fieldName = fieldName.substr(1, fieldName.size() - 2);
        } else { error("Expected field name."); break; }
        consume(TokenType::COLON, "Expected ':' after field name.");
        type->structuralFields.push_back({fieldName, parseBasicType()});
        if (!check(TokenType::RIGHT_BRACE)) match({TokenType::COMMA});
    }
    consume(TokenType::RIGHT_BRACE, "Expected '}' after structural type."); return type;
}

std::shared_ptr<LM::Frontend::AST::TypeAnnotation> Parser::parseContainerType() {
    if (check(TokenType::LEFT_BRACKET)) {
        advance(); auto type = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
        type->isList = true; type->typeName = "list";
        if (!check(TokenType::RIGHT_BRACKET)) type->elementType = parseTypeAnnotation();
        else {
            auto anyType = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
            anyType->typeName = "any"; anyType->isPrimitive = true; type->elementType = anyType;
        }
        consume(TokenType::RIGHT_BRACKET, "Expected ']' after list element type."); return type;
    }
    if (check(TokenType::LEFT_BRACE)) {
        advance(); auto type = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
        type->isDict = true; type->typeName = "dict"; type->keyType = parseBasicType();
        consume(TokenType::COLON, "Expected ':' in dictionary type.");
        type->valueType = parseBasicType(); consume(TokenType::RIGHT_BRACE, "Expected '}' after dictionary type.");
        return type;
    }
    error("Expected '[' or '{' for container type."); return nullptr;
}

std::shared_ptr<LM::Frontend::AST::FunctionTypeAnnotation> Parser::parseFunctionTypeAnnotation() {
    auto funcType = std::make_shared<LM::Frontend::AST::FunctionTypeAnnotation>();
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'fn' in function type.");
    if (!check(TokenType::RIGHT_PAREN)) { do { funcType->parameters.push_back(parseFunctionParameter()); } while (match({TokenType::COMMA})); }
    consume(TokenType::RIGHT_PAREN, "Expected ')' after function parameters.");
    if (match({TokenType::COLON})) funcType->returnType = parseTypeAnnotation();
    else {
        auto voidType = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
        voidType->typeName = "nil"; voidType->isPrimitive = true; funcType->returnType = voidType;
    }
    return funcType;
}

std::shared_ptr<LM::Frontend::AST::TypeAnnotation> Parser::parseLegacyFunctionType() {
    auto type = std::make_shared<LM::Frontend::AST::TypeAnnotation>();
    type->typeName = "function"; type->isFunction = true;
    if (match({TokenType::LEFT_PAREN})) {
        if (!check(TokenType::RIGHT_PAREN)) {
            do {
                if (check(TokenType::IDENTIFIER) && peek().lexeme != "int" && peek().lexeme != "str" && 
                    peek().lexeme != "bool" && peek().lexeme != "float") {
                    advance(); if (match({TokenType::COLON})) type->functionParams.push_back(parseBasicType());
                } else type->functionParams.push_back(parseBasicType());
            } while (match({TokenType::COMMA}));
        }
        consume(TokenType::RIGHT_PAREN, "Expected ')' after function parameters.");
        if (match({TokenType::COLON})) type->returnType = parseBasicType();
    }
    return type;
}

LM::Frontend::AST::FunctionParameter Parser::parseFunctionParameter() {
    LM::Frontend::AST::FunctionParameter param;
    if (check(TokenType::IDENTIFIER)) {
        Token nameToken = peek(); advance();
        if (match({TokenType::QUESTION})) {
            consume(TokenType::COLON, "Expected ':' after '?' in optional parameter.");
            if (isValidParameterName(nameToken.lexeme)) { param.name = nameToken.lexeme; param.hasDefaultValue = true; }
            else error("Invalid parameter name: " + nameToken.lexeme);
            param.type = parseTypeAnnotation();
        } else if (match({TokenType::COLON})) {
            if (isValidParameterName(nameToken.lexeme)) param.name = nameToken.lexeme;
            else error("Invalid parameter name: " + nameToken.lexeme);
            param.type = parseTypeAnnotation();
        } else { current--; param.type = parseTypeAnnotation(); }
    } else param.type = parseTypeAnnotation();
    return param;
}

bool Parser::isValidParameterName(const std::string& name) {
    static const std::set<std::string> reservedTypes = {
        "int", "i8", "i16", "i32", "i64", "uint", "u8", "u16", "u32", "u64", 
        "float", "f32", "f64", "str", "string", "bool", "nil", "any",
        "list", "dict", "array", "function", "option", "result", "channel", "atomic"
    };
    return reservedTypes.find(name) == reservedTypes.end();
}

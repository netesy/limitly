#include "scanner.hh"
#include "../debugger.hh"

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.push_back({TokenType::EOF_TOKEN, "", line});
    return tokens;
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
    case '(':
        addToken(TokenType::LEFT_PAREN);
        break;
    case ')':
        addToken(TokenType::RIGHT_PAREN);
        break;
    case '{':
        addToken(TokenType::LEFT_BRACE);
        break;
    case '}':
        addToken(TokenType::RIGHT_BRACE);
        break;
    case '[':
        addToken(TokenType::LEFT_BRACKET);
        break;
    case ']':
        addToken(TokenType::RIGHT_BRACKET);
        break;
    case ',':
        addToken(TokenType::COMMA);
        break;
    case '.':
        if (match('.')) {
            if (match('.')) {
                addToken(TokenType::ELLIPSIS);
            } else {
                addToken(TokenType::RANGE);
            }
        } else {
            addToken(TokenType::DOT);
        }
        break;
    case '-':
        if (match('>')) {
            addToken(TokenType::ARROW);
        } else if (match('=')) {
            addToken(TokenType::MINUS_EQUAL);
        } else {
            addToken(TokenType::MINUS);
        }
        break;
    case '+':
        addToken(match('=') ? TokenType::PLUS_EQUAL : TokenType::PLUS);
        break;
    case '?':
        addToken(TokenType::QUESTION);
        break;
    case ':':
        addToken(TokenType::COLON);
        break;
    case ';':
        addToken(TokenType::SEMICOLON);
        break;
    case '*':
        if (match('*')) {
            addToken(TokenType::POWER);
        } else if (match('=')) {
            addToken(TokenType::STAR_EQUAL);
        } else {
            addToken(TokenType::STAR);
        }
        break;
    case '!':
        addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        break;
    case '=':
        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
    case '<':
        addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
    case '>':
        addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;
    case '_':
        // Check if this is part of an identifier or standalone underscore
        if (isAlpha(peek())) {
            identifier();
        } else {
            addToken(TokenType::DEFAULT);
        }
        break;
    case '/':
        if (match('/')) {
            // A comment goes until the end of the line.
            while (peek() != '\n' && !isAtEnd())
                advance();
        } else if (match('=')) {
            addToken(TokenType::SLASH_EQUAL);
        } else {
            addToken(TokenType::SLASH);
        }
        break;
    case '%':
        addToken(match('=') ? TokenType::MODULUS_EQUAL : TokenType::MODULUS);
        break;
    case '|':
        addToken(TokenType::PIPE);
        break;
    case '&':
        addToken(TokenType::AMPERSAND);
        break;
    case '^':
        addToken(TokenType::CARET);
        break;
    case '~':
        addToken(TokenType::TILDE);
        break;
    case '@':
        // Handle annotations
        annotation();
        break;
    case ' ':
    case '\r':
    case '\t':
        // Ignore whitespace.
        break;
    case '\n':
        line++;
        break;
    case '"':
    case '\'':
        string();
        break;
    default:
        if (isDigit(c)) {
            number();
        } else if (isAlpha(c)) {
            identifier();
        } else {
            this->error("Unexpected character.");
        }
        break;
    }
}

void Scanner::annotation() {
    // Consume all alphanumeric characters after the @ symbol
    while (isAlphaNumeric(peek())) {
        advance();
    }

    // Get the annotation name (without the @ symbol)
    std::string annotationName = source.substr(start + 1, current - start - 1);

    // Check for known annotations
    if (annotationName == "open") {
        addToken(TokenType::OPEN);
    } else if (annotationName == "public") {
        addToken(TokenType::PUBLIC);
    } else if (annotationName == "private") {
        addToken(TokenType::PRIVATE);
    } else if (annotationName == "protected") {
        addToken(TokenType::PROTECTED);
    } else if (annotationName == "property") {
        addToken(TokenType::PROPERTY);
    } else if (annotationName == "cache") {
        addToken(TokenType::CACHE);
    } else {
        // For unknown annotations, just add the AT_SIGN token
        addToken(TokenType::AT_SIGN);

        // And then process the identifier separately
        current = start + 1; // Reset to just after the @ symbol
        identifier();
    }
}

bool Scanner::isAtEnd() const {
    return current >= source.size();
}

char Scanner::advance() {
    return source[current++];
}

void Scanner::addToken(TokenType type) {
    addToken(type, "");
}

void Scanner::addToken(TokenType type, const std::string& text) {
    std::string lexeme;
    if (text.empty()) {
        lexeme = source.substr(start, current - start);
    } else {
        lexeme = text;
    }
    
    // Add debug output for string interpolation tokens
    if constexpr (false) {  // Disabled debug output
        if (type == TokenType::INTERPOLATION_START) {
            std::cout << "[SCANNER] Added INTERPOLATION_START token" << std::endl;
        } else if (type == TokenType::INTERPOLATION_END) {
            std::cout << "[SCANNER] Added INTERPOLATION_END token" << std::endl;
        } else if (type == TokenType::STRING) {
            std::cout << "[SCANNER] Added STRING token: \"" << lexeme << "\"" << std::endl;
        }
    }
    
    tokens.push_back({type, lexeme, line, start});
    currentToken = tokens.back(); // Update currentToken
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;

    current++;
    return true;
}

Token Scanner::getToken() {
    return currentToken;
}

Token Scanner::getNextToken() {
    // Return next token or EOF if at end
    size_t nextIndex = current + 1;
    if (nextIndex < tokens.size()) {
        return tokens[nextIndex];
    } else {
        // Handle end of tokens
        return {TokenType::EOF_TOKEN, "", line, static_cast<int>(current)};
    }
}

Token Scanner::getPrevToken() {
    // Return previous token or EOF if at start
    if (current > 0) {
        return tokens[current - 1];
    } else {
        // Handle no previous token
        return {TokenType::EOF_TOKEN, "", line, 0};
    }
}

char Scanner::peek() const {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Scanner::peekNext() const {
    if (current + 1 >= source.size()) return '\0';
    return source[current + 1];
}

char Scanner::peekPrevious() const {
    if (current > start) {
        return source[current - 1];
    }
    return '\0'; // Return null character if no previous character exists
}

bool Scanner::isDigit(char c) const {
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) const {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool Scanner::isAlphaNumeric(char c) const {
    return isAlpha(c) || isDigit(c);
}

void Scanner::string() {
    char quoteType = source[start]; // Store the opening quote type (' or ")
    std::string value;
    size_t literalStart = start + 1; // Start after the opening quote
    current = start + 1; // Skip the opening quote
    
    std::cout << "[SCANNER] Starting string parsing at line " << line << " with quote: " << quoteType << std::endl;
    
    while (!isAtEnd() && peek() != quoteType) {
        // Check for interpolation start
        if (peek() == '{') {
            // Check if this is an escaped brace
            if (peekNext() == '{') {
                // Escaped brace, add a single brace to the value
                value += peek();
                advance(); // Skip the first {
                advance(); // Skip the second {
                literalStart = current;
                continue;
            }
            
            // Add the literal part before the interpolation
            if (current > literalStart) {
                std::string literal = source.substr(literalStart, current - literalStart);
                value += literal;
            }
            
            // Add the string part before the interpolation
            if (!value.empty()) {
                addToken(TokenType::STRING, value);
                value.clear();
            }
            
            // Add the interpolation start token
            std::cout << "[SCANNER] Found interpolation start at line " << line << std::endl;
            addToken(TokenType::INTERPOLATION_START, "{");
            advance(); // Consume the {
            
            // The expression will be handled by the main scanner loop
            // We'll look for the matching }
            int braceCount = 1;
            while (!isAtEnd() && braceCount > 0) {
                if (peek() == '{') {
                    braceCount++;
                } else if (peek() == '}') {
                    braceCount--;
                }
                advance();
            }
            
            if (isAtEnd()) {
                error("Unterminated interpolation expression.");
                return;
            }
            
            // Add the interpolation end token
            std::cout << "[SCANNER] Found interpolation end at line " << line << std::endl;
            addToken(TokenType::INTERPOLATION_END, "}");
            
            // Reset for the next part of the string
            literalStart = current;
            continue;
        }
        
        // Handle escape sequences
        if (peek() == '\\') {
            // Add any literal part before the escape sequence
            if (current > literalStart) {
                std::string literal = source.substr(literalStart, current - literalStart);
                value += literal;
            }
            
            // Handle the escape sequence
            advance(); // Skip the backslash
            if (isAtEnd()) break;
            
            switch (peek()) {
                case 'n': value += '\n'; break;
                case 't': value += '\t'; break;
                case 'r': value += '\r'; break;
                case '\\': value += '\\'; break;
                case '"': value += '"'; break;
                case '\'': value += '\''; break;
                case '{': value += '{'; break;
                case '}': value += '}'; break;
                default:
                    // Unknown escape sequence, just add the character as-is
                    value += '\\';
                    value += peek();
                    break;
            }
            
            advance();
            literalStart = current;
            continue;
        }
        
        // Regular character
        advance();
    }
    
    if (isAtEnd()) {
        error("Unterminated string.");
        return;
    }
    
    // Add any remaining literal part
    if (current > literalStart) {
        std::string literal = source.substr(literalStart, current - literalStart);
        value += literal;
    }
    
    // The closing quote
    advance();
    
    // Add the final string part if there is one
    if (!value.empty()) {
        addToken(TokenType::STRING, value);
    }
}

void Scanner::number() {
    while (isDigit(peek())) advance();

    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the ".".
        advance();

        while (isDigit(peek())) advance();
    }

    addToken(TokenType::NUMBER);
}

void Scanner::identifier() {
    while (isAlphaNumeric(peek()))
        advance();

    std::string text = source.substr(start, current - start);
    TokenType type = checkKeyword(start, current - start, text, TokenType::IDENTIFIER);
    addToken(type);
}

TokenType Scanner::checkKeyword(size_t /*start*/, size_t /*length*/, const std::string& rest, TokenType /*type*/) const {
    // Check if the identifier matches a reserved keyword.
    if (rest == "interface") return TokenType::INTERFACE;
    if (rest == "and") return TokenType::AND;
    if (rest == "class") return TokenType::CLASS;
    if (rest == "else") return TokenType::ELSE;
    if (rest == "false") return TokenType::FALSE;
    if (rest == "for") return TokenType::FOR;
    if (rest == "fn") return TokenType::FN;
    if (rest == "if") return TokenType::IF;
    if (rest == "or") return TokenType::OR;
    if (rest == "print") return TokenType::PRINT;
    if (rest == "return") return TokenType::RETURN;
    if (rest == "super") return TokenType::SUPER;
    if (rest == "this") return TokenType::THIS;
    if (rest == "self") return TokenType::SELF;
    if (rest == "true") return TokenType::TRUE;
    if (rest == "var") return TokenType::VAR;
    if (rest == "while") return TokenType::WHILE;
    if (rest == "attempt") return TokenType::ATTEMPT;
    if (rest == "handle") return TokenType::HANDLE;
    if (rest == "parallel") return TokenType::PARALLEL;
    if (rest == "concurrent") return TokenType::CONCURRENT;
    if (rest == "async") return TokenType::ASYNC;
    if (rest == "await") return TokenType::AWAIT;
    if (rest == "import") return TokenType::IMPORT;
    if (rest == "throws") return TokenType::THROWS;
    if (rest == "match") return TokenType::MATCH;
    if (rest == "in") return TokenType::IN;
    if (rest == "type") return TokenType::TYPE;
    if (rest == "trait") return TokenType::TRAIT;
    if (rest == "interface") return TokenType::INTERFACE;
    if (rest == "mixin") return TokenType::MIXIN;
    if (rest == "implements") return TokenType::IMPLEMENTS;
    if (rest == "module") return TokenType::MODULE;
    if (rest == "public") return TokenType::PUBLIC;
    if (rest == "private") return TokenType::PRIVATE;
    if (rest == "protected") return TokenType::PROTECTED;
    if (rest == "open") return TokenType::OPEN;
    if (rest == "contract") return TokenType::CONTRACT;
    if (rest == "comptime") return TokenType::COMPTIME;
    if (rest == "unsafe") return TokenType::UNSAFE;
    if (rest == "iter") return TokenType::ITER;
    if (rest == "where") return TokenType::WHERE;
    if (rest == "property") return TokenType::PROPERTY;
    if (rest == "cache") return TokenType::CACHE;
    if (rest == "sleep") return TokenType::SLEEP;
    if (rest == "enum") return TokenType::ENUM;

    // Check if the identifier matches a type keyword
    if (rest == "int") return TokenType::INT_TYPE;
    if (rest == "i8") return TokenType::INT8_TYPE;
    if (rest == "i16") return TokenType::INT16_TYPE;
    if (rest == "i32") return TokenType::INT32_TYPE;
    if (rest == "i64") return TokenType::INT64_TYPE;
    if (rest == "uint") return TokenType::UINT_TYPE;
    if (rest == "u8") return TokenType::UINT8_TYPE;
    if (rest == "u16") return TokenType::UINT16_TYPE;
    if (rest == "u32") return TokenType::UINT32_TYPE;
    if (rest == "u64") return TokenType::UINT64_TYPE;
    if (rest == "float") return TokenType::FLOAT_TYPE;
    if (rest == "f32") return TokenType::FLOAT32_TYPE;
    if (rest == "f64") return TokenType::FLOAT64_TYPE;
    if (rest == "any") return TokenType::ANY_TYPE;
    if (rest == "nil") return TokenType::NIL_TYPE;
    if (rest == "str") return TokenType::STR_TYPE;
    if (rest == "bool") return TokenType::BOOL_TYPE;
    if (rest == "list") return TokenType::LIST_TYPE;
    if (rest == "array") return TokenType::ARRAY_TYPE;
    if (rest == "dict") return TokenType::DICT_TYPE;
    if (rest == "option") return TokenType::OPTION_TYPE;
    // Always treat "result" as an identifier to avoid conflicts with variable names
    if (rest == "result") return TokenType::IDENTIFIER;
    if (rest == "channel") return TokenType::CHANNEL_TYPE;
    if (rest == "atomic") return TokenType::ATOMIC_TYPE;
    if (rest == "function") return TokenType::FUNCTION_TYPE;

    return TokenType::IDENTIFIER;
}

std::string Scanner::toString() const {
    std::string result;
    for (const auto &token : tokens) {
        result += "Token: " + token.lexeme + ", Type: " + tokenTypeToString(token.type)
                  + ", Line: " + std::to_string(token.line) + "\n";
    }
    return result;
}

std::string Scanner::tokenTypeToString(TokenType type) const {
    switch (type) {
    case TokenType::LEFT_PAREN:
        return "LEFT_PAREN";
    case TokenType::RIGHT_PAREN:
        return "RIGHT_PAREN";
    case TokenType::LEFT_BRACE:
        return "LEFT_BRACE";
    case TokenType::RIGHT_BRACE:
        return "RIGHT_BRACE";
    case TokenType::LEFT_BRACKET:
        return "LEFT_BRACKET";
    case TokenType::RIGHT_BRACKET:
        return "RIGHT_BRACKET";
    case TokenType::COMMA:
        return "COMMA";
    case TokenType::DOT:
        return "DOT";
    case TokenType::COLON:
        return "COLON";
    case TokenType::SEMICOLON:
        return "SEMICOLON";
    case TokenType::QUESTION:
        return "QUESTION";
    case TokenType::ARROW:
        return "ARROW";
    case TokenType::RANGE:
        return "RANGE";
    case TokenType::ELLIPSIS:
        return "ELLIPSIS";
    case TokenType::AT_SIGN:
        return "AT_SIGN";
    case TokenType::PLUS:
        return "PLUS";
    case TokenType::PLUS_EQUAL:
        return "PLUS_EQUAL";
    case TokenType::MINUS:
        return "MINUS";
    case TokenType::MINUS_EQUAL:
        return "MINUS_EQUAL";
    case TokenType::SLASH:
        return "SLASH";
    case TokenType::SLASH_EQUAL:
        return "SLASH_EQUAL";
    case TokenType::MODULUS:
        return "MODULUS";
    case TokenType::MODULUS_EQUAL:
        return "MODULUS_EQUAL";
    case TokenType::STAR:
        return "STAR";
    case TokenType::STAR_EQUAL:
        return "STAR_EQUAL";
    case TokenType::BANG:
        return "BANG";
    case TokenType::BANG_EQUAL:
        return "BANG_EQUAL";
    case TokenType::EQUAL:
        return "EQUAL";
    case TokenType::EQUAL_EQUAL:
        return "EQUAL_EQUAL";
    case TokenType::GREATER:
        return "GREATER";
    case TokenType::GREATER_EQUAL:
        return "GREATER_EQUAL";
    case TokenType::LESS:
        return "LESS";
    case TokenType::LESS_EQUAL:
        return "LESS_EQUAL";
    case TokenType::AMPERSAND:
        return "AMPERSAND";
    case TokenType::PIPE:
        return "PIPE";
    case TokenType::CARET:
        return "CARET";
    case TokenType::TILDE:
        return "TILDE";
    case TokenType::POWER:
        return "POWER";
    case TokenType::STRING:
        return "STRING";
    case TokenType::NUMBER:
        return "NUMBER";
    case TokenType::IDENTIFIER:
        return "IDENTIFIER";
    case TokenType::INT_TYPE:
        return "INT_TYPE";
    case TokenType::UINT_TYPE:
        return "UINT_TYPE";
    case TokenType::FLOAT_TYPE:
        return "FLOAT_TYPE";
    case TokenType::STR_TYPE:
        return "STR_TYPE";
    case TokenType::BOOL_TYPE:
        return "BOOL_TYPE";
    case TokenType::USER_TYPE:
        return "USER_TYPE";
    case TokenType::FUNCTION_TYPE:
        return "FUNCTION_TYPE";
    case TokenType::LIST_TYPE:
        return "LIST_TYPE";
    case TokenType::DICT_TYPE:
        return "DICT_TYPE";
    case TokenType::ARRAY_TYPE:
        return "ARRAY_TYPE";
    case TokenType::ENUM_TYPE:
        return "ENUM_TYPE";
    case TokenType::OPTION_TYPE:
        return "OPTION_TYPE";
    case TokenType::RESULT_TYPE:
        return "RESULT_TYPE";
    case TokenType::CHANNEL_TYPE:
        return "CHANNEL_TYPE";
    case TokenType::ATOMIC_TYPE:
        return "ATOMIC_TYPE";
    case TokenType::AND:
        return "AND";
    case TokenType::CLASS:
        return "CLASS";
    case TokenType::FALSE:
        return "FALSE";
    case TokenType::FN:
        return "FN";
    case TokenType::ELSE:
        return "ELSE";
    case TokenType::FOR:
        return "FOR";
    case TokenType::WHILE:
        return "WHILE";
    case TokenType::MATCH:
        return "MATCH";
    case TokenType::IF:
        return "IF";
    case TokenType::IN:
        return "IN";
    case TokenType::NIL:
        return "NIL";
    case TokenType::ENUM:
        return "ENUM";
    case TokenType::OR:
        return "OR";
    case TokenType::DEFAULT:
        return "DEFAULT";
    case TokenType::PRINT:
        return "PRINT";
    case TokenType::RETURN:
        return "RETURN";
    case TokenType::SUPER:
        return "SUPER";
    case TokenType::THIS:
        return "THIS";
    case TokenType::SELF:
        return "SELF";
    case TokenType::TRUE:
        return "TRUE";
    case TokenType::VAR:
        return "VAR";
    case TokenType::ATTEMPT:
        return "ATTEMPT";
    case TokenType::HANDLE:
        return "HANDLE";
    case TokenType::PARALLEL:
        return "PARALLEL";
    case TokenType::CONCURRENT:
        return "CONCURRENT";
    case TokenType::ASYNC:
        return "ASYNC";
    case TokenType::AWAIT:
        return "AWAIT";
    case TokenType::IMPORT:
        return "IMPORT";
    case TokenType::NONE:
        return "NONE";
    case TokenType::THROWS:
        return "THROWS";
    case TokenType::TYPE:
        return "TYPE";
    case TokenType::TRAIT:
        return "TRAIT";
    case TokenType::INTERPOLATION_START:
        return "INTERPOLATION_START";
    case TokenType::INTERPOLATION:
        return "INTERPOLATION";
    case TokenType::INTERFACE:
        return "INTERFACE";
    case TokenType::INTERPOLATION_END:
        return "INTERPOLATION_END";
    case TokenType::MIXIN:
        return "MIXIN";
    case TokenType::IMPLEMENTS:
        return "IMPLEMENTS";
    case TokenType::MODULE:
        return "MODULE";
    case TokenType::PUBLIC:
        return "PUBLIC";
    case TokenType::PRIVATE:
        return "PRIVATE";
    case TokenType::PROTECTED:
        return "PROTECTED";
    case TokenType::OPEN:
        return "OPEN";
    case TokenType::CONTRACT:
        return "CONTRACT";
    case TokenType::COMPTIME:
        return "COMPTIME";
    case TokenType::UNSAFE:
        return "UNSAFE";
    case TokenType::ITER:
        return "ITER";
    case TokenType::WHERE:
        return "WHERE";
    case TokenType::PROPERTY:
        return "PROPERTY";
    case TokenType::CACHE:
        return "CACHE";
    case TokenType::SLEEP:
        return "SLEEP";
    case TokenType::UNDEFINED:
        return "UNDEFINED";
    case TokenType::EOF_TOKEN:
        return "EOF_TOKEN";
    case TokenType::ELVIS:
        return "ELVIS";
    case TokenType::SAFE:
        return "SAFE";
    case TokenType::INT8_TYPE:
        return "INT8_TYPE";
    case TokenType::INT16_TYPE:
        return "INT16_TYPE";
    case TokenType::INT32_TYPE:
        return "INT32_TYPE";
    case TokenType::INT64_TYPE:
        return "INT64_TYPE";
    case TokenType::UINT8_TYPE:
        return "UINT8_TYPE";
    case TokenType::UINT16_TYPE:
        return "UINT16_TYPE";
    case TokenType::UINT32_TYPE:
        return "UINT32_TYPE";
    case TokenType::UINT64_TYPE:
        return "UINT64_TYPE";
    case TokenType::FLOAT32_TYPE:
        return "FLOAT32_TYPE";
    case TokenType::FLOAT64_TYPE:
        return "FLOAT64_TYPE";
    case TokenType::SUM_TYPE:
        return "SUM_TYPE";
    case TokenType::UNION_TYPE:
        return "UNION_TYPE";
    case TokenType::ANY_TYPE:
        return "ANY_TYPE";
    case TokenType::NIL_TYPE:
        return "NIL_TYPE";
        break;
    }
    return "UNKNOWN";
}

void Scanner::error(const std::string& message) {
    // Get the current lexeme for better error reporting
    std::string lexeme = getLexeme();
    Debugger::error(message, getLine(), static_cast<int>(getCurrent()), InterpretationStage::SCANNING, "", lexeme, "");
}


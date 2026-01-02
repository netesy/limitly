#include "scanner.hh"
#include "../common/debugger.hh"

std::vector<Token> Scanner::scanTokens() {
    return scanTokens(ScanMode::LEGACY);
}

std::vector<Token> Scanner::scanTokens(ScanMode mode) {
    scanMode = mode;
    
    if (mode == ScanMode::LEGACY) {
        // Original behavior - no trivia preservation
        cstConfig = CSTConfig{};
        cstConfig.preserveWhitespace = false;
        cstConfig.preserveComments = false;
        cstConfig.emitErrorTokens = false;
        cstConfig.attachTrivia = false;
    } else {
        // CST mode - preserve trivia and attach to tokens
        cstConfig = CSTConfig{};
        cstConfig.preserveWhitespace = true;
        cstConfig.preserveComments = true;
        cstConfig.emitErrorTokens = true;
        cstConfig.attachTrivia = true;
    }
    
    triviaBuffer.clear();
    
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.push_back({TokenType::EOF_TOKEN, "", line, 0, 0, {}, {}});
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
        if (inStringInterpolation) {
            inStringInterpolation = false;
            addToken(TokenType::INTERPOLATION_END);
            string();
        } else {
            addToken(TokenType::RIGHT_BRACE);
        }
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
        if (match('=')) {
            addToken(TokenType::EQUAL_EQUAL);
        } else if (match('>')) {
            addToken(TokenType::ARROW);
        } else {
            addToken(TokenType::EQUAL);
        }
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
            if (scanMode == ScanMode::CST) {
                scanComment();
                collectTrivia(TokenType::COMMENT_LINE);
            } else {
                // Original behavior - skip comment
                while (peek() != '\n' && !isAtEnd())
                    advance();
            }
        } else if (match('*')) {
            // Block comment
            if (scanMode == ScanMode::CST) {
                scanComment();
                collectTrivia(TokenType::COMMENT_BLOCK);
            } else {
                // Original behavior - skip block comment
                while (!isAtEnd()) {
                    if (peek() == '*' && peekNext() == '/') {
                        advance(); // consume '*'
                        advance(); // consume '/'
                        break;
                    }
                    if (peek() == '\n') line++;
                    advance();
                }
            }
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
        if (scanMode == ScanMode::CST) {
            // In CST mode, collect whitespace as trivia
            scanWhitespace();
            collectTrivia(TokenType::WHITESPACE);
        }
        // Otherwise ignore whitespace (original behavior)
        break;
    case '\n':
        if (scanMode == ScanMode::CST) {
            // In CST mode, collect newlines as trivia
            collectTrivia(TokenType::NEWLINE);
        }
        line++;
        break;
    case '"':
    case '\'':
        stringQuoteType = c;
        string();
        break;
    default:
        if (isDigit(c)) {
            number();
        } else if (isAlpha(c)) {
            identifier();
        } else {
            // Handle unexpected character
            if (cstConfig.emitErrorTokens) {
                // Create error token and continue scanning
                std::string unexpectedChar = std::string(1, c);
                Token errorToken = createErrorToken("Unexpected character '" + unexpectedChar + "'");
                tokens.push_back(errorToken);
            } else {
                // Original behavior - report error and stop
                std::string unexpectedChar = std::string(1, c);
                this->error("Unexpected character '" + unexpectedChar + "'", "valid identifier, number, string, or operator");
            }
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
            std::cout << "[SCANNER] Added INTERPOLATION_START token: '" << lexeme << "'" << std::endl;
        } else if (type == TokenType::INTERPOLATION_END) {
            std::cout << "[SCANNER] Added INTERPOLATION_END token" << std::endl;
        } else if (type == TokenType::STRING) {
            std::cout << "[SCANNER] Added STRING token: \"" << lexeme << "\"" << std::endl;
        }
    }
    
    Token token = {type, lexeme, line, start, current, {}, {}};  // Include end position and trivia
    
    // In CST mode, attach collected trivia to meaningful tokens
    if (scanMode == ScanMode::CST && 
        type != TokenType::WHITESPACE && 
        type != TokenType::NEWLINE && 
        type != TokenType::COMMENT_LINE && 
        type != TokenType::COMMENT_BLOCK) {
        attachTriviaToToken(token);
    }
    
    tokens.push_back(token);
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
    size_t nextIndex = static_cast<size_t>(current) + 1;
    if (nextIndex < tokens.size()) {
        return tokens[nextIndex];
    } else {
        // Handle end of tokens
        return {TokenType::EOF_TOKEN, "", line, current, current, {}, {}};

    }
}

Token Scanner::getPrevToken() {
    // Return previous token or EOF if at start
    if (current > 0) {
        return tokens[current - 1];
    } else {
        // Handle no previous token
        return {TokenType::EOF_TOKEN, "", line, 0, 0, {}, {}};
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
    current = start + 1; // Skip the opening quote
    bool hasInterpolation = false; // Track if this string has interpolation
    
    
    // Parse string with interpolation support
    while (!isAtEnd() && peek() != quoteType) {
        // Handle escape sequences
        if (peek() == '\\') {
            advance(); // consume the backslash
            char nextChar = peek();
            
            switch (nextChar) {
                case 'n':
                    value += '\n';
                    advance();
                    break;
                case 't':
                    value += '\t';
                    advance();
                    break;
                case 'r':
                    value += '\r';
                    advance();
                    break;
                case '\\':
                    value += '\\';
                    advance();
                    break;
                case '\'':
                    value += '\'';
                    advance();
                    break;
                case '\"':
                    value += '\"';
                    advance();
                    break;
                case '{':
                    value += '{';
                    advance();
                    break;
                case '}':
                    value += '}';
                    advance();
                    break;
                case '0':
                    value += '\0';
                    advance();
                    break;
                case 'a':
                    value += '\a';
                    advance();
                    break;
                case 'b':
                    value += '\b';
                    advance();
                    break;
                case 'f':
                    value += '\f';
                    advance();
                    break;
                case 'v':
                    value += '\v';
                    advance();
                    break;
                default:
                    // Unknown escape sequence, treat as literal
                    value += '\\';
                    value += nextChar;
                    advance();
                    break;
            }
        } else if (peek() == '{') {
            // Check if this looks like interpolation (contains identifier/expression)
            // vs regex quantifier like {2,} or {1,3}
            size_t lookahead = current + 1;
            bool isInterpolation = false;
            
            // Look ahead to see if this is likely interpolation
            while (lookahead < source.size() && source[lookahead] != '}' && source[lookahead] != quoteType) {
                char c = source[lookahead];
                // If we find letters, it's likely an identifier (interpolation)
                if (isAlpha(c) || c == '_') {
                    isInterpolation = true;
                    break;
                }
                // If we find only digits and commas, it's likely a regex quantifier
                if (!isDigit(c) && c != ',' && c != ' ') {
                    isInterpolation = true;
                    break;
                }
                lookahead++;
            }
            
            if (isInterpolation) {
                hasInterpolation = true; // Mark that this string has interpolation
                // Found interpolation start
                // Add interpolation start token with the string part before interpolation
                advance(); // consume '{'
                // Add quotes around the value for consistency with regular strings
                std::string quotedValue = std::string(1, quoteType) + value + std::string(1, quoteType);
                addToken(TokenType::INTERPOLATION_START, quotedValue);
                value.clear();
                
                // Parse the expression inside {}
                int braceCount = 1;
                size_t exprStart = current;
                
                while (!isAtEnd() && braceCount > 0) {
                    if (peek() == '{') {
                        braceCount++;
                    } else if (peek() == '}') {
                        braceCount--;
                    }
                    
                    if (braceCount > 0) {
                        advance();
                    }
                }
                
                if (isAtEnd()) {
                    error("Unterminated string interpolation", "closing '}' for interpolation expression");
                    return;
                }
                
                // Extract the expression content
                std::string exprContent = source.substr(exprStart, current - exprStart);
                
                // Create a sub-scanner for the expression
                Scanner exprScanner(exprContent);
                auto exprTokens = exprScanner.scanTokens();
                
                // Add the expression tokens (excluding EOF)
                for (const auto& token : exprTokens) {
                    if (token.type != TokenType::EOF_TOKEN) {
                        tokens.push_back({token.type, token.lexeme, line, current, current, {}, {}});

                    }
                }
                
                // Add interpolation end token
                advance(); // consume '}'
                // Set start position to current to avoid including previous content
                start = current;
                addToken(TokenType::INTERPOLATION_END, "");
            } else {
                // Regular brace, treat as normal character
                value += peek();
                advance();
            }
            
        } else {
            // Regular character
            value += peek();
            
            // Handle newlines in strings (for multi-line strings)
            if (peek() == '\n') {
                line++;
            }
            
            advance();
        }
    }
    
    // Unterminated string
    if (isAtEnd()) {
        error("Unterminated string", "closing quote (\") to end string literal");
        return;
    }
    
    // Skip the closing quote
    advance();
    
    // Only add final STRING token if this wasn't an interpolated string
    if (!hasInterpolation) {
        // Add the final string part with original lexeme (including quotes)
        // Use the original source span to preserve quotes
        std::string originalLexeme = source.substr(start, current - start);
        addToken(TokenType::STRING, originalLexeme);
    } else {
        // For interpolated strings, add the final string part if there's remaining content
        if (!value.empty()) {
            std::string quotedValue = std::string(1, quoteType) + value + std::string(1, quoteType);
            addToken(TokenType::STRING, quotedValue);
        } else {
            // Add empty string token to complete the interpolation sequence
            std::string emptyQuoted = std::string(2, quoteType);
            addToken(TokenType::STRING, emptyQuoted);
        }
    }
}

void Scanner::number() {
    bool hasDecimal = false;
    bool hasScientific = false;
    
    while (isDigit(peek())) advance();

    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext())) {
        hasDecimal = true;
        // Consume the ".".
        advance();

        while (isDigit(peek())) advance();
    }

    // Look for scientific notation (e.g., 1.23e+10, 4.56E-7)
    if (peek() == 'e' || peek() == 'E') {
        size_t savedCurrent = current; // Save position in case we need to backtrack
        advance(); // consume 'e' or 'E'
        
        // Handle optional + or - after e/E
        bool hasSign = false;
        if (peek() == '+' || peek() == '-') {
            advance();
            hasSign = true;
        }
        
        // Must have at least one digit after e/E (and optional +/-)
        if (!isDigit(peek())) {
            // Invalid scientific notation - backtrack
            current = savedCurrent;
        } else {
            // Valid scientific notation - consume the exponent digits
            hasScientific = true;
            while (isDigit(peek())) advance();
        }
    }

    // Check for time suffixes (only if we don't have scientific notation)
    if (isAlpha(peek()) && peek() != 'e' && peek() != 'E') {
        if (peek() == 's' && !isAlphaNumeric(peekNext())) {
            advance();
        } else if (peek() == 'm' && peekNext() == 's' && !isAlphaNumeric(source[current+2])) {
            advance();
            advance();
        } else if (peek() == 'u' && peekNext() == 's' && !isAlphaNumeric(source[current+2])) {
            advance();
            advance();
        } else if (peek() == 'n' && peekNext() == 's' && !isAlphaNumeric(source[current+2])) {
            advance();
            advance();
        }
    }

    // Determine the appropriate token type based on the literal format
    TokenType tokenType;
    if (hasScientific) {
        tokenType = TokenType::SCIENTIFIC_LITERAL;
    } else if (hasDecimal) {
        tokenType = TokenType::FLOAT_LITERAL;
    } else {
        tokenType = TokenType::INT_LITERAL;
    }

    addToken(tokenType);
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
    if (rest == "as") return TokenType::AS;
    if (rest == "class") return TokenType::CLASS;
    if (rest == "elif") return TokenType::ELIF;
    if (rest == "else") return TokenType::ELSE;
    if (rest == "false") return TokenType::FALSE;
    if (rest == "for") return TokenType::FOR;
    if (rest == "fn") return TokenType::FN;
    if (rest == "if") return TokenType::IF;
    if (rest == "or") return TokenType::OR;
    if (rest == "print") return TokenType::PRINT;
    if (rest == "return") return TokenType::RETURN;
    if (rest == "show") return TokenType::SHOW;
    if (rest == "hide") return TokenType::HIDE;
    if (rest == "super") return TokenType::SUPER;
    if (rest == "this") return TokenType::THIS;
    if (rest == "self") return TokenType::SELF;
    if (rest == "true") return TokenType::TRUE;
    if (rest == "var") return TokenType::VAR;
    if (rest == "while") return TokenType::WHILE;
    // if (rest == "attempt") return TokenType::ATTEMPT;
    // if (rest == "handle") return TokenType::HANDLE;
    if (rest == "parallel") return TokenType::PARALLEL;
    if (rest == "concurrent") return TokenType::CONCURRENT;
    // if (rest == "async") return TokenType::ASYNC;
    // if (rest == "await") return TokenType::AWAIT;
    if (rest == "break") return TokenType::BREAK;
    if (rest == "continue") return TokenType::CONTINUE;
    if (rest == "import") return TokenType::IMPORT;
    // if (rest == "throws") return TokenType::THROWS;
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
    if (rest == "enum") return TokenType::ENUM;
    if (rest == "err") return TokenType::ERR;
    if (rest == "ok") return TokenType::OK;
    if (rest == "val") return TokenType::VAL;
    
    // Visibility keywords
    if (rest == "pub") return TokenType::PUB;
    if (rest == "prot") return TokenType::PROT;
    if (rest == "static") return TokenType::STATIC;
    if (rest == "abstract") return TokenType::ABSTRACT;
    if (rest == "final") return TokenType::FINAL;
    if (rest == "data") return TokenType::DATA;
    if (rest == "const") return TokenType::CONST;

    // Check if the identifier matches a type keyword
    if (rest == "int") return TokenType::INT_TYPE;
    if (rest == "i8") return TokenType::INT8_TYPE;
    if (rest == "i16") return TokenType::INT16_TYPE;
    if (rest == "i32") return TokenType::INT32_TYPE;
    if (rest == "i64") return TokenType::INT64_TYPE;
    if (rest == "i128") return TokenType::INT128_TYPE;
    if (rest == "uint") return TokenType::UINT_TYPE;
    if (rest == "u8") return TokenType::UINT8_TYPE;
    if (rest == "u16") return TokenType::UINT16_TYPE;
    if (rest == "u32") return TokenType::UINT32_TYPE;
    if (rest == "u64") return TokenType::UINT64_TYPE;
    if (rest == "u128") return TokenType::UINT128_TYPE;
    if (rest == "float") return TokenType::FLOAT_TYPE;
    if (rest == "f32") return TokenType::FLOAT32_TYPE;
    if (rest == "f64") return TokenType::FLOAT64_TYPE;
    if (rest == "any") return TokenType::ANY_TYPE;
    if (rest == "nil") return TokenType::NIL;
    if (rest == "str") return TokenType::STR_TYPE;
    if (rest == "bool") return TokenType::BOOL_TYPE;
    if (rest == "list") return TokenType::LIST_TYPE;
    if (rest == "array") return TokenType::ARRAY_TYPE;
    if (rest == "dict") return TokenType::DICT_TYPE;
    if (rest == "option") return TokenType::OPTION_TYPE;
    // Always treat "result" as an identifier to avoid conflicts with variable names
    if (rest == "result") return TokenType::IDENTIFIER;
    if (rest == "channel") return TokenType::IDENTIFIER;
    if (rest == "atomic") return TokenType::IDENTIFIER;
    if (rest == "function") return TokenType::FUNCTION_TYPE;
    if (rest == "events") return TokenType::IDENTIFIER;
    if (rest == "sleep") return TokenType::IDENTIFIER;
    if (rest == "assert") return TokenType::IDENTIFIER;

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
    case TokenType::UNDERSCORE:
        return "UNDERSCORE";
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
    case TokenType::INT_LITERAL:
        return "INT LITERAL";
    case TokenType::FLOAT_LITERAL:
        return "FLOAT LITERAL";                
    case TokenType::SCIENTIFIC_LITERAL:
        return "SCIENTIFIC LITERAL";
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
    case TokenType::AS:
        return "AS";
    case TokenType::CLASS:
        return "CLASS";
    case TokenType::FALSE:
        return "FALSE";
    case TokenType::FN:
        return "FN";
    case TokenType::ELIF:
        return "ELIF";
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
    case TokenType::SHOW:
        return "SHOW";
    case TokenType::HIDE:
        return "HIDE";
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
    // case TokenType::ATTEMPT:
    //     return "ATTEMPT";
    // case TokenType::HANDLE:
    //     return "HANDLE";
    case TokenType::PARALLEL:
        return "PARALLEL";
    case TokenType::CONCURRENT:
        return "CONCURRENT";
    // case TokenType::ASYNC:
    //     return "ASYNC";
    // case TokenType::AWAIT:
    //     return "AWAIT";
    case TokenType::BREAK:
        return "BREAK";
    case TokenType::CONTINUE:
        return "CONTINUE";
    case TokenType::IMPORT:
        return "IMPORT";
    // case TokenType::NONE:
    //     return "NONE";
    // case TokenType::THROWS:
    //     return "THROWS";
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
    case TokenType::WHITESPACE:
        return "WHITESPACE";
    case TokenType::NEWLINE:
        return "NEWLINE";
    case TokenType::COMMENT_LINE:
        return "COMMENT_LINE";
    case TokenType::COMMENT_BLOCK:
        return "COMMENT_BLOCK";
    case TokenType::ERROR:
        return "ERROR";
    case TokenType::MISSING:
        return "MISSING";
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
    case TokenType::INT128_TYPE:
        return "INT128_TYPE";
    case TokenType::UINT8_TYPE:
        return "UINT8_TYPE";
    case TokenType::UINT16_TYPE:
        return "UINT16_TYPE";
    case TokenType::UINT32_TYPE:
        return "UINT32_TYPE";
    case TokenType::UINT64_TYPE:
        return "UINT64_TYPE";
    case TokenType::UINT128_TYPE:
        return "UINT128_TYPE";
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
    case TokenType::ERR:
        return "ERR";
    case TokenType::OK:
        return "OK";
    case TokenType::VAL:
        return "VAL";
    case TokenType::PUB:
        return "PUB";
    case TokenType::PROT:
        return "PROT";
    case TokenType::STATIC:
        return "STATIC";
    case TokenType::ABSTRACT:
        return "ABSTRACT";
    case TokenType::FINAL:
        return "FINAL";
    case TokenType::DATA:
        return "DATA";
    case TokenType::CONST:
        return "CONST";
        break;
    }
    return "UNKNOWN";
}

std::vector<Token> Scanner::scanAllTokens(const CSTConfig& config) {
    cstConfig = config;
    triviaBuffer.clear();
    
    while (!isAtEnd()) {
        start = current;
        scanTokenCST(config);
    }

    tokens.push_back({TokenType::EOF_TOKEN, "", line, start, current, {}, {}});
    return tokens;
}

void Scanner::scanTokenCST(const CSTConfig& config) {
    char c = advance();
    
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
        if (config.preserveWhitespace) {
            scanWhitespace();
        }
        break;
    case '\n':
        if (config.preserveWhitespace) {
            addToken(TokenType::NEWLINE);
        }
        line++;
        break;
    case '/':
        if (match('/')) {
            if (config.preserveComments) {
                scanComment();
            } else {
                // Skip comment as before
                while (peek() != '\n' && !isAtEnd())
                    advance();
            }
        } else if (match('*')) {
            if (config.preserveComments) {
                // Handle block comment - consume everything until */
                while (!isAtEnd()) {
                    if (peek() == '*' && peekNext() == '/') {
                        advance(); // consume '*'
                        advance(); // consume '/'
                        break;
                    }
                    if (peek() == '\n') line++;
                    advance();
                }
                addToken(TokenType::COMMENT_BLOCK);
            } else {
                // Skip block comment as before
                while (!isAtEnd()) {
                    if (peek() == '*' && peekNext() == '/') {
                        advance(); // consume '*'
                        advance(); // consume '/'
                        break;
                    }
                    if (peek() == '\n') line++;
                    advance();
                }
            }
        } else {
            // Back up and let the default case handle it
            current--; // Back up the '/'
            current--; // Back up to re-process
            scanToken(); // Use existing logic
        }
        break;
    default:
        // For all other characters, use the existing scanToken logic
        current--; // Back up to re-process the character
        scanToken();
        break;
    }
}

void Scanner::scanWhitespace() {
    // Consume all consecutive whitespace characters
    while (!isAtEnd() && (peek() == ' ' || peek() == '\r' || peek() == '\t')) {
        advance();
    }
    // Don't call addToken here - let collectTrivia handle it
}

void Scanner::scanComment() {
    // We're already positioned after the '//' or '/*'
    // For line comments, consume until end of line
    if (source[current - 2] == '/' && source[current - 1] == '/') {
        // Line comment - consume until end of line
        while (peek() != '\n' && !isAtEnd()) {
            advance();
        }
        // Don't call addToken here - let collectTrivia handle it
    } else {
        // Block comment - we're positioned after '/*'
        // Consume until we find '*/'
        while (!isAtEnd()) {
            if (peek() == '*' && peekNext() == '/') {
                advance(); // consume '*'
                advance(); // consume '/'
                break;
            }
            if (peek() == '\n') {
                line++;
            }
            advance();
        }
        // Don't call addToken here - let collectTrivia handle it
    }
}

Token Scanner::createErrorToken(const std::string& message) {
    Token errorToken;
    errorToken.type = TokenType::ERROR;
    errorToken.lexeme = source.substr(start, current - start);
    errorToken.line = line;
    errorToken.start = start;
    errorToken.end = current;
    
    // Store error message in a way that can be retrieved later
    // For now, we'll include it in the lexeme with a special prefix
    errorToken.lexeme = "ERROR: " + message + " (" + errorToken.lexeme + ")";
    
    return errorToken;
}

void Scanner::attachTrivia(Token& token, const CSTConfig& config) {
    if (!config.attachTrivia || triviaBuffer.empty()) {
        return;
    }
    
    // Attach collected trivia to the token
    token.leadingTrivia = triviaBuffer;
    triviaBuffer.clear();
}

void Scanner::collectTrivia(TokenType triviaType) {
    // Create trivia token from current scan
    std::string lexeme = source.substr(start, current - start);
    Token triviaToken = {triviaType, lexeme, line, start, current, {}, {}};
    
    // Add to trivia buffer for attachment to next meaningful token
    triviaBuffer.push_back(triviaToken);
}

void Scanner::attachTriviaToToken(Token& token) {
    if (!triviaBuffer.empty()) {
        // Attach all collected trivia as leading trivia
        token.leadingTrivia = triviaBuffer;
        triviaBuffer.clear();
    }
    
    // After adding this meaningful token, we need to collect any trailing trivia
    // until the next meaningful token. This will be handled by the scanning loop
    // as it encounters whitespace/comments after this token.
}

void Scanner::error(const std::string& message, const std::string& expectedValue) {
    // Get the current lexeme for better error reporting
    std::string lexeme = getLexeme();
    Debugger::error(message, getLine(), static_cast<int>(getCurrent()), InterpretationStage::SCANNING, source, filePath, lexeme, expectedValue);
}
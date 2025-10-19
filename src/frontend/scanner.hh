#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <variant>
#include <vector>

enum class TokenType {
    // Group: Delimiters
    LEFT_PAREN,    // (
    RIGHT_PAREN,   // )
    LEFT_BRACE,    // {
    RIGHT_BRACE,   // }
    LEFT_BRACKET,  // [
    RIGHT_BRACKET, // ]
    COMMA,         // ,
    DOT,           // .
    COLON,         // :
    SEMICOLON,     // ;
    QUESTION,      // ?
    ELVIS,         // ?:
    SAFE,          // ?.
    ARROW,         // ->
    RANGE,         // ..
    ELLIPSIS,      // ...
    AT_SIGN,       // @
    UNDERSCORE,    // _

    // Group: Operators
    PLUS,          // +
    PLUS_EQUAL,    // +=
    MINUS,         // -
    MINUS_EQUAL,   // -=
    SLASH,         // /
    SLASH_EQUAL,   // /=
    MODULUS,       // %
    MODULUS_EQUAL, // %=
    STAR,          // *
    STAR_EQUAL,    // *=
    BANG,          // !
    BANG_EQUAL,    // !=
    EQUAL,         // =
    EQUAL_EQUAL,   // ==
    GREATER,       // >
    GREATER_EQUAL, // >=
    LESS,          // <
    LESS_EQUAL,    // <=
    AMPERSAND,     // &
    PIPE,          // |
    CARET,         // ^
    TILDE,         // ~
    POWER,         // **

    // Group: Literals
    IDENTIFIER,         // variable/function names
    STRING,             // string literals
    INTERPOLATION,      // interpolation expression within strings (legacy)
    INTERPOLATION_START,// { for starting interpolation
    INTERPOLATION_END,  // } for ending interpolation
    NUMBER,             // numeric literals

    // Group: Types
    INT_TYPE,      // int
    INT8_TYPE,     // i8
    INT16_TYPE,    // i16
    INT32_TYPE,    // i32
    INT64_TYPE,    // i64
    UINT_TYPE,     // uint
    UINT8_TYPE,    // u8
    UINT16_TYPE,   // u16
    UINT32_TYPE,   // u32
    UINT64_TYPE,   // u64
    FLOAT_TYPE,    // float
    FLOAT32_TYPE,  // f32
    FLOAT64_TYPE,  // f64
    STR_TYPE,      // str
    BOOL_TYPE,     // bool
    USER_TYPE,     // user-defined types
    FUNCTION_TYPE, // function
    LIST_TYPE,     // list
    DICT_TYPE,     // dictionary
    ARRAY_TYPE,    // array
    ENUM_TYPE,     // enum
    SUM_TYPE,      //sum type
    UNION_TYPE,    //union type
    OPTION_TYPE,   // option
    RESULT_TYPE,   // result
    ANY_TYPE,      //any type
    NIL_TYPE,      //nil type
    CHANNEL_TYPE,  // channel
    ATOMIC_TYPE,   // atomic

    // Group: Keywords
    AND,        // and
    AS,         // as
    CLASS,      // class
    FALSE,      // false
    FN,         // fn
    ELIF,       // else if
    ELSE,       // else
    FOR,        // for
    WHILE,      // while
    MATCH,      // match
    IF,         // if
    IN,         // in
    NIL,        // nil
    ENUM,       // enum
    OR,         // or
    DEFAULT,    // default
    PRINT,      // print
    RETURN,     // return
    SHOW,       // show
    HIDE,       // hide
    SUPER,      // super
    THIS,       // this
    SELF,       // self
    TRUE,       // true
    VAR,        // var
    ATTEMPT,    // attempt
    HANDLE,     // handle
    PARALLEL,   // parallel
    CONCURRENT, // concurrent
    ASYNC,      // async
    AWAIT,      // await
    BREAK,      // break
    CONTINUE,   // continue
    IMPORT,     // import
    NONE,       // None
    THROWS,     // throws
    TYPE,       // type
    TRAIT,      // trait
    INTERFACE,  // interface
    MIXIN,      // mixin
    IMPLEMENTS, // implements
    MODULE,     // module
    PUBLIC,     // public
    PRIVATE,    // private
    PROTECTED,  // protected
    OPEN,       // open
    CONTRACT,   // contract
    COMPTIME,   // comptime
    UNSAFE,     // unsafe
    ITER,       // iter
    WHERE,      // where
    PROPERTY,   // property
    CACHE,      // cache
    SLEEP,      // sleep
    ERR,        // err
    OK,         // ok
    VAL,        // val

    // CST Support - Trivia tokens
    WHITESPACE,     // spaces, tabs
    NEWLINE,        // line breaks
    COMMENT_LINE,   // // comments
    COMMENT_BLOCK,  // /* */ comments
    ERROR,          // invalid/unrecognized input
    MISSING,        // placeholder for missing tokens

    // Other
    UNDEFINED, // undefined token
    EOF_TOKEN  // end of file token
};

struct Token {
    TokenType type;
    std::string lexeme;
    size_t line;
    size_t start = 0;
    
    // CST enhancements (backward compatible)
    size_t end = 0;                           // End position for precise spans
    std::vector<Token> leadingTrivia;         // Optional trivia attachment
    std::vector<Token> trailingTrivia;        // Optional trivia attachment
    
    // Default constructors for backward compatibility
    Token() : type(TokenType::UNDEFINED), lexeme(""), line(0), start(0), end(0) {}
    
    Token(TokenType t, const std::string& lex, size_t ln, size_t st = 0, size_t en = 0)
        : type(t), lexeme(lex), line(ln), start(st), end(en) {}
    
    Token(TokenType t, const std::string& lex, size_t ln, size_t st, size_t en,
          const std::vector<Token>& leading, const std::vector<Token>& trailing)
        : type(t), lexeme(lex), line(ln), start(st), end(en), 
          leadingTrivia(leading), trailingTrivia(trailing) {}
    
    // Accessor methods for trivia
    const std::vector<Token>& getLeadingTrivia() const { return leadingTrivia; }
    const std::vector<Token>& getTrailingTrivia() const { return trailingTrivia; }
    
    // Method to reconstruct original source text with trivia
    std::string reconstructSource() const {
        std::string result;
        
        // Add leading trivia
        for (const auto& trivia : leadingTrivia) {
            result += trivia.lexeme;
        }
        
        // Add the token itself
        result += lexeme;
        
        // Add trailing trivia
        for (const auto& trivia : trailingTrivia) {
            result += trivia.lexeme;
        }
        
        return result;
    }
};

// Scan mode enumeration for backward compatibility
enum class ScanMode {
    LEGACY,     // No trivia collection (original behavior)
    CST         // Collect and attach trivia to tokens
};

// Configuration for CST trivia preservation
struct CSTConfig {
    bool preserveWhitespace = true;
    bool preserveComments = true;
    bool emitErrorTokens = true;
    bool attachTrivia = false;      // Attach trivia to meaningful tokens
    bool detailedExpressionNodes = false;  // Create detailed CST nodes for complex expressions
};

class Scanner {
public:
    explicit Scanner(const std::string& source, const std::string& filePath = "") 
        : source(source), filePath(filePath), start(0), current(0), line(1) {}
    
    // Constructor that takes pre-scanned tokens (for use in string interpolation)
    explicit Scanner(const std::vector<Token>& preScannedTokens) 
        : source(""),  // Empty source since we're using pre-scanned tokens
          filePath(""),
          start(0), 
          current(0), 
          line(1) {
        tokens = preScannedTokens;  // Assign tokens after initialization
    }
    

    std::vector<Token> scanTokens();
    std::vector<Token> scanTokens(ScanMode mode);  // Enhanced with mode parameter
    void scanToken();
    
    // CST-enhanced methods (purely additive)
    std::vector<Token> scanAllTokens(const CSTConfig& config = {});
    void scanTokenCST(const CSTConfig& config);
    bool isAtEnd() const;

    std::string toString() const;
    char advance();
    char peek() const;
    char peekNext() const;
    char peekPrevious() const;
    std::string tokenTypeToString(TokenType type) const;
    size_t getLine() const { return line; }
    size_t getCurrent() const { return current; }
    std::string getLexeme() const { return source.substr(start, current - start); }
    const std::string& getSource() const { return source; }
    const std::string& getFilePath() const { return filePath; }

    Token getToken();
    Token peekToken() const { return tokens.empty() ? Token{TokenType::EOF_TOKEN, "", line, 0, 0, {}, {}} : tokens[current]; }
    Token previousToken() const { return current > 0 ? tokens[current - 1] : Token{TokenType::EOF_TOKEN, "", line, 0, 0, {}, {}}; }
    Token getNextToken();
    Token getPrevToken();
    
    // Token access methods
    const std::vector<Token>& getTokens() const { return tokens; }
    size_t getCurrentTokenIndex() const { return current; }
    Token getTokenAt(size_t index) const { 
        return index < tokens.size() ? tokens[index] : Token{TokenType::EOF_TOKEN, "", line, 0, 0, {}, {}}; 
    }

private:
    std::string source;
    std::string filePath;
    size_t start;
    size_t current;
    size_t line;
    Token currentToken;
    std::vector<Token> tokens;

    bool inStringInterpolation = false;
    char stringQuoteType = 0;
    
    // CST support
    CSTConfig cstConfig;
    ScanMode scanMode = ScanMode::LEGACY;  // Current scanning mode
    std::vector<Token> triviaBuffer;       // Buffer for collecting trivia before meaningful tokens

    void addToken(TokenType type);
    void addToken(TokenType type, const std::string& text);
    bool match(char expected);
    bool isDigit(char c) const;
    bool isAlpha(char c) const;
    bool isAlphaNumeric(char c) const;
    void string();
    void number();
    void identifier();
    void annotation();
    void error(const std::string& message, const std::string& expectedValue = "");
    TokenType checkKeyword(size_t start,
                           size_t length,
                           const std::string &rest,
                           TokenType type) const;
    Token getTokenFromChar(char c);
    
    // CST-specific methods
    void scanWhitespace();
    void scanComment();
    Token createErrorToken(const std::string& message);
    void attachTrivia(Token& token, const CSTConfig& config);
    void collectTrivia(TokenType triviaType);  // Collect trivia into buffer
    void attachTriviaToToken(Token& token);    // Attach buffered trivia to token
};

#endif // SCANNER_H

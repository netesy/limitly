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
    IDENTIFIER, // variable/function names
    STRING,     // string literals
    NUMBER,     // numeric literals

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
    CLASS,      // class
    FALSE,      // false
    FN,         // fn
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

    // Other
    UNDEFINED, // undefined token
    EOF_TOKEN  // end of file token
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int start = 0;
};

class Scanner {
public:
    explicit Scanner(const std::string& source) : source(source), start(0), current(0), line(1) {}

    std::vector<Token> scanTokens();
    void scanToken();
    bool isAtEnd() const;

    std::string toString() const;
    char advance();
    char peek() const;
    char peekNext() const;
    char peekPrevious() const;
    std::string tokenTypeToString(TokenType type) const;
    int getLine() const { return line; }
    int getCurrent() const { return current; }
    std::string getLexeme() const { return source.substr(start, current - start); }
    const std::string& getSource() const { return source; }
    size_t current;
    int line;

    Token getToken();
    Token peekToken() const { return tokens.empty() ? Token{TokenType::EOF_TOKEN, "", line} : tokens[current]; }
    Token previousToken() const { return current > 0 ? tokens[current - 1] : Token{TokenType::EOF_TOKEN, "", line}; }
    Token getNextToken();
    Token getPrevToken();

    std::vector<Token> tokens;

private:
    const std::string& source;
    size_t start;
    Token currentToken;

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
    void error(const std::string& message);
    TokenType checkKeyword(size_t start,
                           size_t length,
                           const std::string &rest,
                           TokenType type) const;
    Token getTokenFromChar(char c);
};

#endif // SCANNER_H

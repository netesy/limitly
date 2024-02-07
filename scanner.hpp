// scanner.h
#pragma once

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
    ARROW,         // ->

    // Group: Operators
    PLUS,          // +
    MINUS,         // -
    SLASH,         // /
    MODULUS,       // %
    STAR,          // *
    BANG,          // !
    BANG_EQUAL,    // !=
    EQUAL,         // =
    EQUAL_EQUAL,   // ==
    GREATER,       // >
    GREATER_EQUAL, // >=
    LESS,          // <
    LESS_EQUAL,    // <=

    // Group: Literals
    IDENTIFIER, // variable/function names
    STRING,     // string literals
    NUMBER,     // numeric literals

    // Group: Types
    INT_TYPE,      // int
    FLOAT_TYPE,    // float
    STR_TYPE,      // str
    BOOL_TYPE,     // bool
    USER_TYPE,     // user-defined types
    FUNCTION_TYPE, // function
    LIST_TYPE,     // list
    DICT_TYPE,     // dictionary
    ARRAY_TYPE,    // array
    ENUM_TYPE,     // enum

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
    OR,         // or
    DEFAULT,    // default
    PRINT,      // print
    RETURN,     // return
    SUPER,      // super
    THIS,       // this
    TRUE,       // true
    VAR,        // var
    ATTEMPT,    // attempt
    HANDLE,     // handle
    PARALLEL,   // parallel
    CONCURRENT, // concurrent
    ASYNC,      // async
    AWAIT,      // await
    IMPORT,     // import

    // Other
    UNDEFINED, // undefined token
    EOF_TOKEN  // end of file token
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
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
    size_t current;
    int line;

    Token getToken();
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
    void error(const std::string& message);
    TokenType checkKeyword(size_t start,
                           size_t length,
                           const std::string &rest,
                           TokenType type) const;
    Token getTokenFromChar(char c);
};

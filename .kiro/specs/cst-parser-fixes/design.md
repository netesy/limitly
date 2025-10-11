# CST Parser Fixes - Design Document

## Overview

This design addresses the critical issues in the CST parser while implementing a clean separation between trivia handling and core parsing logic. The key insight is to preserve trivia at the scanner level and reintegrate it only during CST generation, allowing the legacy parser to remain unchanged while enabling full CST functionality.

## Architecture

### Core Design Principles

1. **Trivia Separation**: Store trivia tokens in the scanner, reintegrate only for CST generation
2. **Memory Efficiency**: Use RAII and smart pointers consistently, avoid recursive memory allocation
3. **Incremental Fixes**: Fix the existing CST parser rather than rewriting from scratch
4. **Backward Compatibility**: Keep legacy parser unchanged and fully functional
5. **Performance Focus**: Optimize for common parsing scenarios while maintaining full CST capabilities

### High-Level Architecture

```
Source Code
     ↓
Enhanced Scanner (stores trivia separately)
     ↓
Token Stream (meaningful tokens only) + Trivia Stream (whitespace/comments)
     ↓
┌─────────────────┬─────────────────┐
│   Legacy Parser │   CST Parser    │
│   (unchanged)   │   (enhanced)    │
│        ↓        │        ↓        │
│      AST        │  CST + Trivia   │
└─────────────────┴─────────────────┘
```

## Components and Interfaces

### 1. Enhanced Scanner with Trivia Storage

**Purpose**: Collect and store trivia tokens separately from meaningful tokens

**Interface**:
```cpp
class Scanner {
private:
    struct TriviaToken {
        TokenType type;           // WHITESPACE, COMMENT, NEWLINE
        std::string lexeme;       // Actual trivia content
        size_t position;          // Position in source
        size_t afterTokenIndex;   // Which meaningful token this trivia follows
    };
    
    std::vector<Token> meaningfulTokens;  // Regular tokens for legacy parser
    std::vector<TriviaToken> triviaTokens; // Trivia stored separately
    
public:
    // Existing interface (unchanged for legacy parser)
    std::vector<Token> scanTokens();
    
    // New interface for CST parser
    struct ScanResult {
        std::vector<Token> meaningfulTokens;
        std::vector<TriviaToken> triviaTokens;
    };
    
    ScanResult scanWithTrivia();
    std::vector<TriviaToken> getTriviaAfterToken(size_t tokenIndex) const;
    std::vector<TriviaToken> getTriviaBeforeToken(size_t tokenIndex) const;
};
```

### 2. Simplified CST Parser

**Purpose**: Generate CST nodes with trivia reintegration, fix memory issues

**Key Changes**:
- Remove complex unified grammar system (causing memory issues)
- Use simple recursive descent parsing like legacy parser
- Add trivia reintegration during node creation
- Fix memory management issues

**Interface**:
```cpp
class CSTParser {
private:
    std::vector<Token> tokens;                    // Meaningful tokens only
    std::vector<Scanner::TriviaToken> trivia;     // Trivia tokens
    size_t current = 0;
    
    // Simple node creation with trivia
    std::unique_ptr<Node> createNodeWithTrivia(NodeKind kind);
    void attachTriviaToNode(Node& node, size_t tokenIndex);
    
    // Simple recursive descent methods (mirror legacy parser)
    std::unique_ptr<Node> parseProgram();
    std::unique_ptr<Node> parseStatement();
    std::unique_ptr<Node> parseExpression();
    // ... other parsing methods
    
public:
    CSTParser(const std::vector<Token>& tokens, 
              const std::vector<Scanner::TriviaToken>& trivia);
    
    std::unique_ptr<Node> parse();
    const std::vector<ParseError>& getErrors() const;
};
```

### 3. CST Node Structure with Trivia

**Purpose**: Store both meaningful tokens and trivia in CST nodes

**Interface**:
```cpp
class Node {
private:
    std::vector<Token> leadingTrivia;   // Trivia before this node
    std::vector<Token> trailingTrivia;  // Trivia after this node
    
public:
    void addLeadingTrivia(const std::vector<Token>& trivia);
    void addTrailingTrivia(const std::vector<Token>& trivia);
    
    const std::vector<Token>& getLeadingTrivia() const;
    const std::vector<Token>& getTrailingTrivia() const;
    
    // Reconstruct original source with trivia
    std::string reconstructSource() const;
};
```

## Data Models

### Token with Position Tracking

```cpp
struct Token {
    TokenType type;
    std::string lexeme;
    size_t line;
    size_t column;
    size_t position;        // Absolute position in source
    size_t length;          // Length of token in source
    
    // For trivia association
    size_t triviaIndex;     // Index into trivia array (if applicable)
};
```

### Trivia Token

```cpp
struct TriviaToken {
    enum class TriviaType {
        WHITESPACE,
        LINE_COMMENT,
        BLOCK_COMMENT,
        NEWLINE
    };
    
    TriviaType type;
    std::string content;
    size_t position;
    size_t length;
    size_t associatedTokenIndex;  // Which meaningful token this follows
    bool isLeading;               // True if before token, false if after
};
```

### CST Node with Trivia

```cpp
class Node {
    NodeKind kind;
    std::vector<std::unique_ptr<Node>> children;
    std::vector<Token> tokens;
    
    // Trivia storage
    std::vector<TriviaToken> leadingTrivia;
    std::vector<TriviaToken> trailingTrivia;
    
    // Source span
    size_t startPosition;
    size_t endPosition;
};
```

## Error Handling

### Memory Management Strategy

1. **RAII Everywhere**: Use smart pointers and RAII for all dynamic allocations
2. **Avoid Deep Recursion**: Limit recursion depth and use iterative approaches where possible
3. **Early Cleanup**: Clean up temporary objects promptly
4. **Memory Limits**: Set reasonable limits on node creation and token storage

### Error Recovery Strategy

1. **Synchronization Points**: Use statement boundaries for error recovery
2. **Partial Nodes**: Create partial nodes for incomplete constructs
3. **Error Limits**: Stop parsing after 100 errors to prevent memory exhaustion
4. **Graceful Degradation**: Fall back to simpler parsing when complex parsing fails

### Specific Fixes for Current Issues

#### 1. String Interpolation with Operators

**Problem**: `{p && q}` and `{p || q}` not parsed correctly in interpolated strings

**Solution**:
```cpp
std::unique_ptr<Node> CSTParser::parseInterpolatedString() {
    auto node = createNodeWithTrivia(NodeKind::INTERPOLATED_STRING);
    
    while (!isAtEnd() && !check(TokenType::STRING)) {
        if (check(TokenType::INTERPOLATION_START)) {
            advance(); // consume {
            
            // Parse full expression including && and ||
            auto expr = parseExpression(); // This will handle && and ||
            node->addNode(std::move(expr));
            
            consume(TokenType::INTERPOLATION_END, "Expected '}' after interpolation");
        } else {
            // Regular string content
            node->addToken(advance());
        }
    }
    
    return node;
}
```

#### 2. Elif Statement Recognition

**Problem**: `elif` treated as function call instead of keyword

**Solution**:
```cpp
std::unique_ptr<Node> CSTParser::parseIfStatement() {
    auto ifNode = createNodeWithTrivia(NodeKind::IF_STATEMENT);
    
    consume(TokenType::IF, "Expected 'if'");
    // ... parse condition and then block
    
    // Handle elif chains
    while (check(TokenType::ELIF)) {  // Add ELIF to TokenType enum
        auto elifNode = createNodeWithTrivia(NodeKind::ELIF_CLAUSE);
        elifNode->addToken(advance()); // consume 'elif'
        // ... parse elif condition and block
        ifNode->addNode(std::move(elifNode));
    }
    
    // Handle else
    if (check(TokenType::ELSE)) {
        auto elseNode = createNodeWithTrivia(NodeKind::ELSE_CLAUSE);
        elseNode->addToken(advance()); // consume 'else'
        // ... parse else block
        ifNode->addNode(std::move(elseNode));
    }
    
    return ifNode;
}
```

#### 3. Object Literal Syntax

**Problem**: `Some { kind: "Some", value: 42 }` not parsed correctly

**Solution**:
```cpp
std::unique_ptr<Node> CSTParser::parseObjectLiteral() {
    auto objNode = createNodeWithTrivia(NodeKind::OBJECT_LITERAL);
    
    // Parse constructor name
    if (check(TokenType::IDENTIFIER)) {
        objNode->addToken(advance());
    }
    
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    // Parse key-value pairs
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        auto pairNode = createNodeWithTrivia(NodeKind::OBJECT_PAIR);
        
        // Parse key
        pairNode->addToken(consume(TokenType::IDENTIFIER, "Expected property name"));
        pairNode->addToken(consume(TokenType::COLON, "Expected ':'"));
        
        // Parse value
        auto value = parseExpression();
        pairNode->addNode(std::move(value));
        
        if (check(TokenType::COMMA)) {
            pairNode->addToken(advance());
        }
        
        objNode->addNode(std::move(pairNode));
    }
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    return objNode;
}
```

## Testing Strategy

### 1. Memory Testing

- Run all tests under Valgrind or similar memory checker
- Test with large files to ensure linear memory growth
- Test error recovery scenarios for memory leaks

### 2. Accuracy Testing

- Compare CST parser output with legacy parser AST
- Test all language features systematically
- Verify trivia preservation and reconstruction

### 3. Performance Testing

- Benchmark CST parser against legacy parser
- Measure memory usage patterns
- Test with various file sizes

### 4. Integration Testing

- Test with all existing test files
- Verify `test_parser --cst` vs `test_parser --legacy` equivalence
- Test error reporting and recovery

## Implementation Plan

### Phase 1: Core Fixes (High Priority)

1. Fix memory allocation issues in existing CST parser
2. Implement pratt /recursive descent parsing based on the legacy parser
3. Fix string interpolation parsing
4. Add ELIF token type and parsing

### Phase 2: Trivia Integration

1. Enhance scanner to store trivia separately
2. Implement trivia reintegration in CST nodes
3. Add source reconstruction capability
4. Test trivia preservation

### Phase 3: Error Recovery

1. Implement robust error recovery
2. Add comprehensive error reporting
3. Test with malformed input files
4. Optimize error message quality

### Phase 4: Performance and Polish

1. Optimize parsing performance
2. Add comprehensive test coverage
3. Document API and usage patterns
4. Performance benchmarking and tuning

This design maintains the separation of concerns while fixing the critical issues in the CST parser, enabling accurate parsing with full trivia preservation.
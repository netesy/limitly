# Design Document

## Overview

This design outlines the transformation of the Limit programming language parser from a token-driven architecture that discards whitespace and comments to a Concrete Syntax Tree (CST) based architecture that preserves all lexical information. The new architecture will enable advanced tooling features like code formatting, syntax highlighting, incremental parsing, and robust error recovery while maintaining compatibility with the existing compilation pipeline.

The transformation follows a layered approach where the CST serves as an intermediate representation between the raw tokens and the typed AST, allowing for lossless source reconstruction and error-tolerant parsing.

## Architecture

### Current Architecture
```
Source Code → Scanner → Tokens (filtered) → Parser → AST → Backend → Bytecode
```

### New CST-Based Architecture (Incremental Integration)
```
Source Code → Enhanced Scanner → All Tokens → CST Parser → CST → AST Builder → AST → Backend → Bytecode
                                     ↓                              ↑
                              Legacy Parser (parallel) ────────────┘
```

### Integration Strategy with Current Parser

The CST architecture will be implemented **alongside** your current parser, not as a replacement. Here's how they'll coexist:

#### Phase 1: Parallel Implementation
```cpp
// Current: src/frontend/parser.hh
class Parser {
    Scanner &scanner;
    std::shared_ptr<AST::Program> parse();  // Existing method
    // ... existing methods unchanged
};

// New: src/frontend/cst_parser.hh  
class CSTParser {
    Scanner &scanner;
    std::unique_ptr<CST::Node> parseCST();  // New CST method
    std::shared_ptr<AST::Program> parseAST(); // Wrapper that goes CST→AST
};
```

#### Phase 2: Gradual Migration
```cpp
// Enhanced main.cpp integration
class CompilerFrontend {
    enum class ParserMode {
        LEGACY,     // Use existing Parser class
        CST,        // Use new CSTParser class
        HYBRID      // Use CST for tooling, Legacy for compilation
    };
    
    ParserMode mode = ParserMode::LEGACY;  // Default to existing behavior
    
    std::shared_ptr<AST::Program> parse(const std::string& source) {
        Scanner scanner(source);
        
        switch (mode) {
            case LEGACY:
                return Parser(scanner).parse();  // Your current parser
            case CST:
                return CSTParser(scanner).parseAST();  // New CST→AST path
            case HYBRID:
                // Use CST for error recovery, fallback to legacy
                return tryCSTParseThenFallback(scanner);
        }
    }
};
```

### Layer Responsibilities

| Layer | Input | Output | Responsibility | Integration |
|-------|-------|--------|----------------|-------------|
| **Enhanced Scanner** | Source code | Complete token stream | Tokenize all characters including whitespace/comments | **Extends existing Scanner** |
| **CST Parser** | Token stream | Concrete Syntax Tree | Build untyped tree preserving exact source structure | **New class alongside Parser** |
| **AST Builder** | CST | Abstract Syntax Tree | Transform to typed, semantic tree with error recovery | **New transformation layer** |
| **Legacy Parser** | Token stream | Abstract Syntax Tree | Direct AST generation (current approach) | **Unchanged, runs in parallel** |
| **Backend** | AST | Bytecode | Generate executable bytecode | **Completely unchanged** |

## Components and Interfaces

## Integration with Current Parser

### Coexistence Strategy

The CST parser will be implemented **alongside** your current parser, ensuring zero disruption to existing functionality:

```cpp
// Your existing parser continues unchanged
class Parser {  // src/frontend/parser.hh - NO CHANGES
    Scanner &scanner;
    std::shared_ptr<AST::Program> parse();  // Existing method works as before
    // All existing methods remain identical
};

// New CST parser added in parallel
class CSTParser {  // NEW: src/frontend/cst_parser.hh
    Scanner &scanner;
    std::unique_ptr<CST::Node> parseCST();           // Pure CST parsing
    std::shared_ptr<AST::Program> parseViaCST();     // CST→AST transformation
};
```

### Migration Path

1. **Phase 1**: Add CST parser alongside existing parser
2. **Phase 2**: Use CST parser for tooling features (formatting, error recovery)
3. **Phase 3**: Optionally migrate compilation to use CST→AST path
4. **Phase 4**: Eventually deprecate old parser (only if desired)

### Feature Flags for Gradual Adoption

```cpp
// main.cpp integration
struct CompilerOptions {
    bool useCST = false;              // Default: use existing parser
    bool cstErrorRecovery = false;    // Enhanced error messages via CST
    bool cstTooling = false;          // Enable formatting/highlighting
};

std::shared_ptr<AST::Program> parseSource(const std::string& source, CompilerOptions opts) {
    Scanner scanner(source);
    
    if (opts.useCST) {
        return CSTParser(scanner).parseViaCST();  // New path
    } else {
        return Parser(scanner).parse();           // Your existing path
    }
}
```

## Components and Interfaces

### 1. Enhanced Scanner

#### Token Structure Enhancement
Your existing Token structure will be **extended** without breaking changes:

```cpp
// Current Token structure (from src/frontend/scanner.hh) - UNCHANGED
struct Token {
    TokenType type;        // Existing
    std::string lexeme;    // Existing  
    size_t line;           // Existing
    size_t start = 0;      // Existing
    
    // NEW: Optional CST enhancements (backward compatible)
    size_t end = 0;                           // NEW: End position for precise spans
    std::vector<Token> leadingTrivia;         // NEW: Optional trivia attachment
    std::vector<Token> trailingTrivia;        // NEW: Optional trivia attachment
};

// Your existing TokenType enum will be extended:
enum class TokenType {
    // ALL your existing tokens remain unchanged:
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    IDENTIFIER, STRING, NUMBER, IF, FN, VAR, // ... etc
    
    // NEW: Additional tokens for CST (added at end for compatibility)
    WHITESPACE,           // Spaces, tabs
    NEWLINE,              // Line breaks  
    COMMENT_LINE,         // // comments
    COMMENT_BLOCK,        // /* */ comments
    ERROR,                // Invalid/unrecognized input
    MISSING,              // Placeholder for missing tokens
};
```

#### Scanner Integration
Your existing Scanner class gets **new optional methods** while keeping all current functionality:

```cpp
// Your existing Scanner class (src/frontend/scanner.hh) 
class Scanner {
public:
    // ALL EXISTING METHODS REMAIN UNCHANGED
    explicit Scanner(const std::string& source, const std::string& filePath = "");
    std::vector<Token> scanTokens();    // Your current method - no changes
    void scanToken();                   // Your current method - no changes
    Token peek() const;                 // Your current method - no changes
    // ... all other existing methods work exactly as before
    
    // NEW: Optional CST-enhanced methods (purely additive)
    struct CSTConfig {
        bool preserveWhitespace = true;
        bool preserveComments = true;
        bool emitErrorTokens = true;
    };
    
    std::vector<Token> scanAllTokens(const CSTConfig& config = {});  // NEW
    
private:
    // ALL EXISTING PRIVATE MEMBERS UNCHANGED
    std::string source, filePath;
    size_t start, current, line;
    // ... existing members
    
    // NEW: CST-specific methods (don't affect existing code)
    void scanWhitespace();
    void scanComment();
    Token createErrorToken(const std::string& message);
};
```####
 Scanner Interface Changes
```cpp
class Scanner {
public:
    // NEW: Configuration for trivia handling
    struct Config {
        bool preserveWhitespace = true;
        bool preserveComments = true;
        bool attachTrivia = false;      // Attach to meaningful tokens
        bool emitErrorTokens = true;    // Continue on invalid input
    };
    
    Scanner(const std::string& source, const Config& config = {});
    
    // Enhanced token scanning
    std::vector<Token> scanAllTokens();     // NEW: Returns all tokens including trivia
    
    // Existing interface (for backward compatibility)
    std::vector<Token> scanTokens();        // Filters trivia for existing code
    
private:
    Config config;
    
    // NEW: Trivia handling methods
    void scanWhitespace();
    void scanComment();
    void attachTrivia(Token& token);
    Token createErrorToken(const std::string& message);
};
```

### 2. CST Node Structure

#### Unified Node Design
```cpp
namespace CST {
    enum class NodeKind {
        // Program structure
        PROGRAM,
        STATEMENT_LIST,
        
        // Statements
        VAR_DECLARATION,
        FUNCTION_DECLARATION,
        CLASS_DECLARATION,
        IF_STATEMENT,
        FOR_STATEMENT,
        WHILE_STATEMENT,
        BLOCK_STATEMENT,
        EXPRESSION_STATEMENT,
        RETURN_STATEMENT,
        
        // Expressions
        BINARY_EXPR,
        UNARY_EXPR,
        CALL_EXPR,
        MEMBER_EXPR,
        INDEX_EXPR,
        LITERAL_EXPR,
        VARIABLE_EXPR,
        GROUPING_EXPR,
        
        // Error recovery
        ERROR_NODE,           // Invalid syntax
        MISSING_NODE,         // Missing required elements
        INCOMPLETE_NODE,      // Partial constructs
    };
    
    struct Node {
        NodeKind kind;
        size_t startPos;              // Source position
        size_t endPos;
        
        std::vector<std::unique_ptr<Node>> children;
        std::vector<Token> tokens;    // Direct tokens under this node
        
        // Optional metadata
        bool isValid = true;          // Validation flag
        std::string errorMessage;     // For error nodes
        
        // Utility methods
        std::string getText() const;
        std::vector<Token> getAllTokens() const;
        Node* findChild(NodeKind kind) const;
        std::vector<Node*> findChildren(NodeKind kind) const;
    };
    
    // Factory functions for common node types
    std::unique_ptr<Node> createNode(NodeKind kind);
    std::unique_ptr<Node> createErrorNode(const std::string& message);
    std::unique_ptr<Node> createMissingNode(NodeKind expectedKind);
}
```

### 3. CST Parser

#### Parser Interface
```cpp
class CSTParser {
public:
    CSTParser(const std::vector<Token>& tokens);
    
    // Main parsing entry point
    std::unique_ptr<CST::Node> parse();
    
    // Error recovery configuration
    struct RecoveryConfig {
        std::vector<TokenType> syncTokens = {
            TokenType::SEMICOLON,
            TokenType::RIGHT_BRACE,
            TokenType::NEWLINE
        };
        size_t maxErrors = 100;
        bool continueOnError = true;
    };
    
    void setRecoveryConfig(const RecoveryConfig& config);
    
    // Error reporting
    struct ParseError {
        std::string message;
        size_t position;
        size_t line;
        size_t column;
        std::string context;
    };
    
    const std::vector<ParseError>& getErrors() const { return errors; }
    bool hasErrors() const { return !errors.empty(); }
    
private:
    std::vector<Token> tokens;
    size_t current = 0;
    RecoveryConfig recoveryConfig;
    std::vector<ParseError> errors;
    
    // Core parsing methods (return CST nodes instead of AST)
    std::unique_ptr<CST::Node> parseProgram();
    std::unique_ptr<CST::Node> parseStatement();
    std::unique_ptr<CST::Node> parseExpression();
    std::unique_ptr<CST::Node> parseIfStatement();
    std::unique_ptr<CST::Node> parseForStatement();
    std::unique_ptr<CST::Node> parseBlock();
    
    // Error recovery methods
    void reportError(const std::string& message);
    void synchronize();
    std::unique_ptr<CST::Node> createErrorRecoveryNode();
    
    // Token consumption with error handling
    Token consume(TokenType type, const std::string& message);
    Token consumeOrError(TokenType type, const std::string& message);
    bool match(std::initializer_list<TokenType> types);
    
    // Trivia handling
    void consumeTrivia();
    std::vector<Token> collectTrivia();
};
```

### 4. AST Builder (CST → AST Transformation)

#### Transformation Interface
```cpp
class ASTBuilder {
public:
    ASTBuilder();
    
    // Main transformation entry point
    std::shared_ptr<AST::Program> buildAST(const CST::Node& cst);
    
    // Error handling configuration
    struct BuildConfig {
        bool insertErrorNodes = true;       // Insert Error nodes for invalid CST
        bool insertMissingNodes = true;     // Insert Missing nodes for incomplete CST
        bool preserveSourceMapping = true;  // Maintain CST → AST mapping
        bool validateSemantics = false;     // Perform semantic validation
    };
    
    void setConfig(const BuildConfig& config);
    
    // Source mapping for error reporting
    struct SourceMapping {
        const CST::Node* cstNode;
        std::shared_ptr<AST::Node> astNode;
        size_t startPos;
        size_t endPos;
    };
    
    const std::vector<SourceMapping>& getSourceMappings() const { return sourceMappings; }
    
private:
    BuildConfig config;
    std::vector<SourceMapping> sourceMappings;
    
    // Transformation methods for each node type
    std::shared_ptr<AST::Statement> buildStatement(const CST::Node& cst);
    std::shared_ptr<AST::Expression> buildExpression(const CST::Node& cst);
    std::shared_ptr<AST::VarDeclaration> buildVarDeclaration(const CST::Node& cst);
    std::shared_ptr<AST::FunctionDeclaration> buildFunctionDeclaration(const CST::Node& cst);
    std::shared_ptr<AST::IfStatement> buildIfStatement(const CST::Node& cst);
    std::shared_ptr<AST::BinaryExpr> buildBinaryExpr(const CST::Node& cst);
    
    // Error-tolerant node creation
    std::shared_ptr<AST::Expression> createErrorExpr(const std::string& message);
    std::shared_ptr<AST::Statement> createErrorStmt(const std::string& message);
    std::shared_ptr<AST::Expression> createMissingExpr(const std::string& description);
    
    // Source mapping utilities
    void addSourceMapping(const CST::Node& cst, std::shared_ptr<AST::Node> ast);
    void preserveSourceSpan(const CST::Node& cst, std::shared_ptr<AST::Node> ast);
};
```

## Data Models

### CST Node Hierarchy
```
Node (base)
├── ProgramNode
├── StatementListNode
├── StatementNodes
│   ├── VarDeclarationNode
│   ├── FunctionDeclarationNode
│   ├── ClassDeclarationNode
│   ├── IfStatementNode
│   ├── ForStatementNode
│   ├── WhileStatementNode
│   ├── BlockStatementNode
│   ├── ExpressionStatementNode
│   └── ReturnStatementNode
├── ExpressionNodes
│   ├── BinaryExprNode
│   ├── UnaryExprNode
│   ├── CallExprNode
│   ├── MemberExprNode
│   ├── IndexExprNode
│   ├── LiteralExprNode
│   ├── VariableExprNode
│   └── GroupingExprNode
└── ErrorRecoveryNodes
    ├── ErrorNode
    ├── MissingNode
    └── IncompleteNode
```

### Token Classification
```cpp
enum class TokenClass {
    TRIVIA,          // Whitespace, comments
    KEYWORD,         // Language keywords
    IDENTIFIER,      // Variable/function names
    LITERAL,         // String/number/boolean literals
    OPERATOR,        // Arithmetic/logical operators
    DELIMITER,       // Parentheses, braces, semicolons
    ERROR,           // Invalid tokens
};

TokenClass classifyToken(TokenType type);
bool isTrivia(TokenType type);
bool isMeaningful(TokenType type);
```

## Error Handling

### Error Recovery Strategy

#### Synchronization Points
The parser will use these tokens as synchronization points for error recovery:
- Statement terminators: `;`, `}`
- Block boundaries: `{`, `}`
- Line boundaries: `\n` (in some contexts)
- Declaration keywords: `fn`, `class`, `var`, `type`

#### Error Node Types
```cpp
namespace CST {
    struct ErrorNode : public Node {
        std::string errorMessage;
        std::vector<Token> skippedTokens;  // Tokens skipped during recovery
        TokenType expectedToken;           // What was expected
        TokenType actualToken;             // What was found
    };
    
    struct MissingNode : public Node {
        NodeKind expectedKind;             // What kind of node was expected
        std::string description;           // Human-readable description
    };
    
    struct IncompleteNode : public Node {
        NodeKind targetKind;               // What this was trying to be
        std::vector<std::string> missingElements;  // What's missing
    };
}
```

#### Error Recovery Algorithm
1. **Local Recovery**: Try to fix the immediate error (insert missing token, skip invalid token)
2. **Synchronization**: If local recovery fails, skip tokens until a sync point
3. **Partial Construction**: Create partial nodes with error markers
4. **Continue Parsing**: Resume parsing after synchronization

### Error Reporting Enhancement
```cpp
struct EnhancedError {
    std::string message;
    size_t line;
    size_t column;
    size_t startPos;
    size_t endPos;
    std::string sourceContext;         // Surrounding source code
    std::vector<std::string> suggestions;  // Possible fixes
    ErrorSeverity severity;
    
    // CST-specific information
    const CST::Node* relatedNode;
    std::vector<const CST::Node*> contextNodes;
};
```

## Testing Strategy

### Unit Testing Approach

#### Scanner Testing
```cpp
class ScannerTests {
    void testWhitespacePreservation();
    void testCommentPreservation();
    void testErrorTokenGeneration();
    void testTriviaAttachment();
    void testSourcePositions();
};
```

#### CST Parser Testing
```cpp
class CSTParserTests {
    void testValidSyntaxCST();
    void testInvalidSyntaxRecovery();
    void testPartialNodeCreation();
    void testErrorNodeGeneration();
    void testSourceSpanAccuracy();
    void testTriviaIntegration();
};
```

#### AST Builder Testing
```cpp
class ASTBuilderTests {
    void testValidCSTTransformation();
    void testErrorTolerantTransformation();
    void testSourceMappingPreservation();
    void testMissingNodeHandling();
    void testSemanticValidation();
};
```

### Integration Testing

#### Round-Trip Testing
Verify that CST can reconstruct the original source:
```cpp
void testRoundTrip(const std::string& source) {
    auto tokens = scanner.scanAllTokens(source);
    auto cst = parser.parse(tokens);
    auto reconstructed = cst->getText();
    ASSERT_EQ(source, reconstructed);
}
```

#### Error Recovery Testing
Test parser behavior with various syntax errors:
```cpp
void testErrorRecovery() {
    testMissingSemicolon();
    testMissingBrace();
    testInvalidExpression();
    testIncompleteFunction();
    testNestedErrors();
}
```

#### Performance Testing
Ensure CST doesn't significantly impact performance:
```cpp
void testPerformance() {
    benchmarkScanningSpeed();
    benchmarkParsingSpeed();
    benchmarkMemoryUsage();
    compareWithCurrentParser();
}
```### Test D
ata Organization
```
tests/cst/
├── scanner/
│   ├── whitespace_preservation.lm
│   ├── comment_preservation.lm
│   ├── error_tokens.lm
│   └── trivia_attachment.lm
├── parser/
│   ├── valid_syntax/
│   │   ├── expressions.lm
│   │   ├── statements.lm
│   │   └── declarations.lm
│   ├── invalid_syntax/
│   │   ├── missing_tokens.lm
│   │   ├── unexpected_tokens.lm
│   │   └── incomplete_constructs.lm
│   └── error_recovery/
│       ├── synchronization.lm
│       ├── partial_nodes.lm
│       └── nested_errors.lm
├── ast_builder/
│   ├── transformation.lm
│   ├── error_handling.lm
│   └── source_mapping.lm
└── integration/
    ├── round_trip.lm
    ├── tooling_features.lm
    └── performance.lm
```

## Implementation Phases

### Phase 1: Enhanced Scanner (Week 1-2)
- Add trivia token types to TokenType enum
- Modify Scanner to emit all tokens including whitespace/comments
- Add error token generation and recovery
- Implement optional trivia attachment
- Add comprehensive scanner tests

### Phase 2: CST Node Structure (Week 2-3)
- Define CST::Node base class and hierarchy
- Implement node factory functions
- Add source position tracking
- Create error/missing/incomplete node types
- Add node utility methods (getText, findChild, etc.)

### Phase 3: CST Parser Implementation (Week 3-5)
- Implement CSTParser class with error recovery
- Convert existing parser methods to return CST nodes
- Add synchronization and error recovery logic
- Implement trivia integration in parsing
- Add comprehensive parser tests

### Phase 4: AST Builder (Week 5-6)
- Implement ASTBuilder for CST → AST transformation
- Add error-tolerant transformation logic
- Implement source mapping preservation
- Add missing/error node handling in AST
- Create transformation tests

### Phase 5: Integration and Testing (Week 6-7)
- Integrate CST parser with existing compilation pipeline
- Add backward compatibility layer
- Implement comprehensive test suite
- Performance testing and optimization
- Documentation and examples

### Phase 6: Advanced Features (Week 7-8)
- Implement CST utilities (printer, serializer, traversal)
- Add incremental parsing support
- Create formatting and syntax highlighting examples
- Add debugging and visualization tools
- Final integration testing

## Migration Strategy

### Backward Compatibility
- Maintain existing Parser interface for current code
- Add CSTParser as new option with feature flag
- Gradual migration of components to use CST
- Performance comparison and validation

### Feature Flags
```cpp
struct ParserConfig {
    bool useCSTParser = false;        // Enable CST-based parsing
    bool preserveTrivia = true;       // Keep whitespace/comments
    bool enableErrorRecovery = true;  // Continue parsing on errors
    bool attachTrivia = false;        // Attach trivia to tokens
};
```

### Integration with Current Compilation Pipeline

#### Current main.cpp Integration
Your current compilation flow remains **completely unchanged**:

```cpp
// Current main.cpp (simplified) - NO CHANGES NEEDED
int main(int argc, char* argv[]) {
    std::string source = readFile(argv[1]);
    
    Scanner scanner(source);                    // Your existing scanner
    Parser parser(scanner);                     // Your existing parser  
    auto ast = parser.parse();                  // Your existing parse method
    
    // Your existing backend pipeline continues unchanged
    Backend backend;
    auto bytecode = backend.generateBytecode(ast);
    VM vm;
    vm.execute(bytecode);
    
    return 0;
}
```

#### Enhanced main.cpp with CST Option
When you're ready to experiment with CST features:

```cpp
// Enhanced main.cpp with optional CST support
int main(int argc, char* argv[]) {
    std::string source = readFile(argv[1]);
    bool useCST = hasFlag(argc, argv, "--cst");  // Optional flag
    
    std::shared_ptr<AST::Program> ast;
    
    if (useCST) {
        // NEW: CST-based parsing path
        Scanner scanner(source);
        CSTParser cstParser(scanner);
        ast = cstParser.parseViaCST();          // CST → AST transformation
    } else {
        // EXISTING: Your current parsing path (default)
        Scanner scanner(source);
        Parser parser(scanner);
        ast = parser.parse();                   // Your existing method
    }
    
    // Backend pipeline remains identical regardless of parsing method
    Backend backend;
    auto bytecode = backend.generateBytecode(ast);  // Same AST format
    VM vm;
    vm.execute(bytecode);                           // Same execution
    
    return 0;
}
```

### Migration Steps
1. **Add CST Classes**: Implement CSTParser alongside existing Parser
2. **Extend Scanner**: Add optional CST methods to existing Scanner class
3. **Parallel Testing**: Run both parsers on same code, compare AST output
4. **Feature Adoption**: Use CST for specific features (error recovery, tooling)
5. **Optional Migration**: Eventually switch default to CST (when we have parity)
6. **Legacy Support**: Remove existing Parser 
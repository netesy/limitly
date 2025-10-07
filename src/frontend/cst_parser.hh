#ifndef CST_PARSER_H
#define CST_PARSER_H

#include <memory>
#include <vector>
#include <string>
#include <initializer_list>
#include <functional>
#include <unordered_map>
#include <variant>
#include <optional>
#include <type_traits>
#include "scanner.hh"
#include "cst.hh"
#include "ast.hh"
#include "../error/error_message.hh"

namespace CST {

    // Parser mode determines output type and behavior
    enum class ParserMode {
        DIRECT_AST,      // Direct AST generation (fastest, for compilation)
        CST_THEN_AST,    // Generate CST then transform to AST (for tooling with AST)
        CST_ONLY         // Generate CST only (for IDE features, formatting)
    };

    // Forward declarations for unified grammar system
    class GrammarRule;
    class ParseContext;
    class GrammarTable;
    struct RuleResult;

    // Output type variant - can hold either CST or AST nodes
    using OutputNode = std::variant<
        std::unique_ptr<CST::Node>,
        std::shared_ptr<AST::Node>
    >;

    // Rule execution result
    struct RuleResult {
        OutputNode node;
        bool success = false;
        std::string errorMessage;
        size_t tokensConsumed = 0;
        
        // Make it movable
        RuleResult() = default;
        RuleResult(const RuleResult&) = delete;
        RuleResult& operator=(const RuleResult&) = delete;
        RuleResult(RuleResult&&) = default;
        RuleResult& operator=(RuleResult&&) = default;
        
        // Helper methods for type checking
        bool hasCST() const { return std::holds_alternative<std::unique_ptr<CST::Node>>(node); }
        bool hasAST() const { return !hasCST(); }
        
        // Safe getters
        CST::Node* getCST() const {
            if (auto* cst = std::get_if<std::unique_ptr<CST::Node>>(&node)) {
                return cst->get();
            }
            return nullptr;
        }
        
        template<typename T>
        std::shared_ptr<T> getAST() const {
            if (auto* ast = std::get_if<std::shared_ptr<AST::Node>>(&node)) {
                return std::dynamic_pointer_cast<T>(*ast);
            }
            return nullptr;
        }
    };

    // Parse context tracks current parsing state for unified grammar
    class ParseContext {
    public:
        ParserMode mode;
        class CSTParser* parser;
        size_t currentToken = 0;
        std::vector<Token> tokens;
        
        // Trivia handling
        bool preserveTrivia = true;
        std::vector<Token> triviaBuffer;
        
        // Error tracking
        std::vector<std::string> errors;
        size_t maxErrors = 100;
        
        // Performance optimization flags
        bool skipTriviaCollection = false;  // Set to true in DIRECT_AST mode
        bool enableMemoization = true;
        
        // Constructor
        ParseContext(ParserMode m, CSTParser* p, const std::vector<Token>& toks)
            : mode(m), parser(p), tokens(toks) {
            // Optimize for direct AST mode
            if (mode == ParserMode::DIRECT_AST) {
                preserveTrivia = false;
                skipTriviaCollection = true;
            }
        }
        
        // Token access
        Token peek(size_t offset = 0) const;
        Token advance();
        bool match(TokenType type);
        bool match(std::initializer_list<TokenType> types);
        bool isAtEnd() const { return currentToken >= tokens.size(); }
        
        // Error handling
        void reportError(const std::string& message);
        bool hasErrors() const { return !errors.empty(); }
        
        // Trivia handling
        void collectTrivia();
        std::vector<Token> getTrivia() const { return triviaBuffer; }
        void clearTrivia() { triviaBuffer.clear(); }
    };

    // Grammar rule definition - supports both CST and AST generation
    class GrammarRule {
    public:
        std::string name;
        std::string description;
        
        // Rule execution function - template-based for type safety
        using RuleFunction = std::function<RuleResult(ParseContext&)>;
        RuleFunction execute;
        
        // Rule metadata
        bool isTerminal = false;
        bool isOptional = false;
        std::vector<std::string> dependencies;  // Other rules this depends on
        
        // Performance optimization
        bool cacheable = true;
        size_t priority = 0;  // Higher priority rules checked first
        
        // Constructors
        GrammarRule() = default;  // Default constructor for std::unordered_map
        GrammarRule(const std::string& ruleName, RuleFunction func)
            : name(ruleName), execute(std::move(func)) {}
        
        // Builder pattern methods
        GrammarRule& optional() { isOptional = true; return *this; }
        GrammarRule& terminal() { isTerminal = true; return *this; }
        GrammarRule& dependsOn(const std::vector<std::string>& deps) { 
            dependencies = deps; return *this; 
        }
        GrammarRule& withPriority(size_t p) { priority = p; return *this; }
        GrammarRule& describe(const std::string& desc) { description = desc; return *this; }
        GrammarRule& nocache() { cacheable = false; return *this; }
    };

    // Grammar DSL builder for defining rules
    class RuleBuilder {
    public:
        std::string ruleName;
        
        explicit RuleBuilder(const std::string& name) : ruleName(name) {}
        
        // Sequence combinator: rule("varDecl").sequence("var", "identifier", ":", "type")
        RuleBuilder& sequence(std::initializer_list<std::string> elements);
        RuleBuilder& sequence(const std::vector<std::string>& elements);
        
        // Choice combinator: rule("expr").choice({"binary", "unary", "primary"})
        RuleBuilder& choice(std::initializer_list<std::string> alternatives);
        RuleBuilder& choice(const std::vector<std::string>& alternatives);
        
        // Optional combinator: rule("optionalType").optional("type")
        RuleBuilder& optional(const std::string& element);
        
        // Repetition combinators
        RuleBuilder& zeroOrMore(const std::string& element);
        RuleBuilder& oneOrMore(const std::string& element);
        RuleBuilder& separated(const std::string& element, const std::string& separator);
        
        // Token matching
        RuleBuilder& token(TokenType type);
        RuleBuilder& keyword(const std::string& keyword);
        RuleBuilder& identifier();
        RuleBuilder& literal();
        
        // Build the final rule
        GrammarRule build();
        
    private:
        std::vector<std::string> elements_;
        std::string combinator_;
        std::vector<std::string> alternatives_;
        TokenType tokenType_ = TokenType::UNDEFINED;
        std::string keywordValue_;
    };

    // Grammar table - central repository of all parsing rules
    class GrammarTable {
    public:
        // Rule registration
        void addRule(const GrammarRule& rule);
        void addRule(const std::string& name, GrammarRule::RuleFunction func);
        
        // Rule lookup
        const GrammarRule* getRule(const std::string& name) const;
        bool hasRule(const std::string& name) const;
        
        // Rule execution
        RuleResult executeRule(const std::string& name, ParseContext& context) const;
        
        // Rule dependencies and ordering
        std::vector<std::string> getRuleDependencies(const std::string& name) const;
        std::vector<std::string> getTopologicalOrder() const;
        
        // Grammar validation
        bool validateGrammar() const;
        std::vector<std::string> findCircularDependencies() const;
        std::vector<std::string> findMissingRules() const;
        
        // Performance optimization
        void optimizeRuleOrder();
        void enableMemoization(bool enable = true) { memoizationEnabled = enable; }
        
        // Debug and introspection
        std::vector<std::string> getAllRuleNames() const;
        void printGrammar() const;
        
    private:
        std::unordered_map<std::string, GrammarRule> rules_;
        bool memoizationEnabled = true;
        
        // Memoization cache
        mutable std::unordered_map<std::string, std::unordered_map<size_t, RuleResult>> memoCache_;
        
        // Helper methods
        void clearMemoCache() const { memoCache_.clear(); }
        std::string getMemoKey(const std::string& ruleName, size_t tokenPos) const;
    };

    // Configuration for error recovery behavior
    struct RecoveryConfig {
        // Synchronization points for error recovery
        std::vector<TokenType> syncTokens = {
            TokenType::SEMICOLON,
            TokenType::RIGHT_BRACE,
            TokenType::NEWLINE,
            TokenType::FN,
            TokenType::CLASS,
            TokenType::VAR,
            TokenType::IF,
            TokenType::FOR,
            TokenType::ITER,
            TokenType::WHILE,
            TokenType::MATCH,            
            TokenType::RETURN,
            TokenType::BREAK,
            TokenType::CONTINUE
        };
        
        size_t maxErrors = 100;           // Maximum errors before stopping
        bool continueOnError = true;      // Continue parsing after errors
        bool insertMissingTokens = true;  // Insert placeholder tokens for missing elements
        bool skipInvalidTokens = true;    // Skip tokens that don't fit the grammar
        bool createPartialNodes = true;   // Create partial nodes for incomplete constructs
        
        // Trivia handling during parsing
        bool preserveTrivia = true;       // Keep whitespace and comments in CST
        bool attachTrivia = false;        // Attach trivia to meaningful nodes
    };

    // Use the existing ErrorMessage system instead of custom ParseError
    using ParseError = ErrorHandling::ErrorMessage;

    // Main CST Parser class with unified grammar system
    class CSTParser {
    public:
        // Constructor taking vector of tokens from enhanced Scanner
        explicit CSTParser(const std::vector<Token>& tokens);
        
        // Alternative constructor taking Scanner directly
        explicit CSTParser(Scanner& scanner, const CSTConfig& config = {});
        
        // Main parsing entry point
        std::unique_ptr<Node> parse();
        
        // Unified grammar system - main parsing interface
        template<typename OutputType>
        std::shared_ptr<OutputType> parseRule(const std::string& ruleName, ParserMode mode = ParserMode::DIRECT_AST);
        
        // Specialized parsing methods for different output types
        std::shared_ptr<AST::Program> parseAST();
        std::shared_ptr<AST::Program> parseViaCST();  // CST -> AST transformation
        
        // Mode switching for unified grammar
        void setParserMode(ParserMode mode) { currentMode = mode; }
        ParserMode getParserMode() const { return currentMode; }
        
        // Grammar access and manipulation
        GrammarTable& getGrammar() { return grammar; }
        const GrammarTable& getGrammar() const { return grammar; }
        void initializeUnifiedGrammar();
        
        // Rule execution with context
        RuleResult executeRule(const std::string& ruleName, ParseContext& context);
        
        // Configuration methods
        void setRecoveryConfig(const RecoveryConfig& config);
        const RecoveryConfig& getRecoveryConfig() const { return recoveryConfig; }
        
        // Error reporting and access
        const std::vector<ParseError>& getErrors() const { return errors; }
        bool hasErrors() const { return !errors.empty(); }
        size_t getErrorCount() const { return errors.size(); }
        void clearErrors() { errors.clear(); }
        
        // Parsing statistics
        size_t getTokensConsumed() const { return current; }
        size_t getTotalTokens() const { return tokens.size(); }
        bool isAtEnd() const { return current >= tokens.size(); }
        
    private:
        // Core data members
        std::vector<Token> tokens;        // Token stream to parse
        size_t current = 0;               // Current token index
        RecoveryConfig recoveryConfig;    // Error recovery configuration
        std::vector<ParseError> errors;   // Collected parse errors
        Scanner* scanner = nullptr;       // Reference to scanner for source access
        
        // Unified grammar system members
        ParserMode currentMode = ParserMode::CST_ONLY;  // Default to CST mode
        GrammarTable grammar;             // Central grammar table
        mutable std::unordered_map<std::string, std::unordered_map<size_t, RuleResult>> ruleCache;
        
        // Performance monitoring
        struct ParseStats {
            size_t rulesExecuted = 0;
            size_t cacheHits = 0;
            size_t cacheMisses = 0;
            size_t tokensConsumed = 0;
            double parseTimeMs = 0.0;
        };
        mutable ParseStats stats;
        
        // Trivia handling
        std::vector<Token> triviaBuffer;  // Buffer for collecting trivia tokens
        
        // Block context tracking for better error messages
        std::vector<ErrorHandling::BlockContext> blockStack;
        
        // Core token consumption methods
        Token consume(TokenType type, const std::string& message);
        Token consumeOrError(TokenType type, const std::string& message);
        bool match(std::initializer_list<TokenType> types);
        bool match(TokenType type);
        bool check(TokenType type) const;
        
        // Token access methods
        Token advance();
        Token peek() const;
        Token previous() const;
        Token peekAhead(size_t offset = 1) const;
        
        // Trivia handling methods
        void consumeTrivia();
        std::vector<Token> collectTrivia();
        void attachTrivia(Node& node);
        void attachLeadingTrivia(Node& node);
        void attachTrailingTrivia(Node& node);
        bool isTrivia(TokenType type) const;
        
        // Error recovery methods
        void reportError(const std::string& message);
        void reportError(const std::string& message, TokenType expected, TokenType actual);
        void reportErrorWithSuggestions(const std::string& message, 
                                       const std::vector<std::string>& suggestions);
        void reportDetailedError(const std::string& message, 
                               const std::string& context,
                               const std::vector<std::string>& suggestions);
        void reportErrorAtToken(const std::string& message, const Token& errorToken, 
                               TokenType expected = TokenType::UNDEFINED, TokenType actual = TokenType::UNDEFINED);
        void synchronize();
        std::unique_ptr<Node> createErrorRecoveryNode();
        std::unique_ptr<Node> createErrorRecoveryNode(const std::string& message);
        std::unique_ptr<Node> createPartialNode(NodeKind targetKind, const std::string& description);
        bool attemptErrorRecovery(const std::string& context);
        std::unique_ptr<Node> handleMissingToken(TokenType expectedType, const std::string& context);
        
        // Error context and suggestions
        std::string getSourceContext(size_t position, size_t contextLines = 2) const;
        std::vector<std::string> generateSuggestions(TokenType expected, TokenType actual) const;
        void addErrorContext(ParseError& error, const Node* node) const;
        
        // Synchronization helpers
        bool isSyncToken(TokenType type) const;
        void skipToSyncPoint();
        void skipInvalidTokens();
        bool isRecoverableError(TokenType expected, TokenType actual) const;
        std::string tokenTypeToString(TokenType type) const;
        
        // Node creation helpers
        std::unique_ptr<Node> createNode(NodeKind kind);
        std::unique_ptr<Node> createNodeWithSpan(NodeKind kind, size_t start, size_t end);
        void setNodeSpan(Node& node, size_t start, size_t end);
        void setNodeSpanFromTokens(Node& node, const Token& startToken, const Token& endToken);
        
        // Utility methods for error recovery
        bool canRecover() const;
        bool shouldContinueParsing() const;
        void incrementErrorCount();
        
        // Block context tracking methods
        void pushBlockContext(const std::string& blockType, const Token& startToken);
        void popBlockContext();
        std::optional<ErrorHandling::BlockContext> getCurrentBlockContext() const;
        std::string generateCausedByMessage(const ErrorHandling::BlockContext& context) const;
        
        // Token classification helpers
        bool isMeaningfulToken(TokenType type) const;
        bool isStatementStart(TokenType type) const;
        bool isExpressionStart(TokenType type) const;
        bool isDeclarationStart(TokenType type) const;
        
        // Source position helpers
        size_t getCurrentPosition() const;
        size_t getTokenPosition(const Token& token) const;
        std::pair<size_t, size_t> getLineColumn(size_t position) const;
        
        // Debug and diagnostic helpers
        std::string getCurrentTokenInfo() const;
        std::string getParsingContext() const;
        void logParsingState(const std::string& context) const;
        
        // Core CST parsing methods (Task 5)
        std::unique_ptr<Node> parseCST();
        std::unique_ptr<Node> parseProgram();
        std::unique_ptr<Node> parseStatement();
        std::unique_ptr<Node> parseExpression();
        std::unique_ptr<Node> parseBlock();
        
        // Helper parsing methods
        std::unique_ptr<Node> parseDeclaration();
        std::unique_ptr<Node> parseStatementByType();
        std::unique_ptr<Node> parseAssignmentExpression();
        std::unique_ptr<Node> parseLogicalOrExpression();
        std::unique_ptr<Node> parseLogicalAndExpression();
        std::unique_ptr<Node> parseEqualityExpression();
        std::unique_ptr<Node> parseComparisonExpression();
        std::unique_ptr<Node> parseTermExpression();
        std::unique_ptr<Node> parseFactorExpression();
        std::unique_ptr<Node> parseUnaryExpression();
        std::unique_ptr<Node> parseCallExpression();
        std::unique_ptr<Node> parsePrimaryExpression();
        
        // Statement parsing methods
        std::unique_ptr<Node> parseVariableDeclaration();
        std::unique_ptr<Node> parseFunctionDeclaration();
        std::unique_ptr<Node> parseClassDeclaration();
        std::unique_ptr<Node> parseTypeDeclaration();
        std::unique_ptr<Node> parseTraitDeclaration();
        std::unique_ptr<Node> parseInterfaceDeclaration();
        std::unique_ptr<Node> parseIfStatement();
        std::unique_ptr<Node> parseForStatement();
        std::unique_ptr<Node> parseWhileStatement();
        std::unique_ptr<Node> parseIterStatement();
        std::unique_ptr<Node> parseMatchStatement();
        std::unique_ptr<Node> parseReturnStatement();
        std::unique_ptr<Node> parseBreakStatement();
        std::unique_ptr<Node> parseContinueStatement();
        std::unique_ptr<Node> parsePrintStatement();
        
        // Enhanced expression parsing methods (Task 7)
        std::unique_ptr<Node> parseBinaryExpr(std::unique_ptr<Node> (CSTParser::*parseNext)(), 
                                             const std::vector<TokenType>& operators);
        std::unique_ptr<Node> parseLiteralExpr();
        std::unique_ptr<Node> parseInterpolatedString();
        std::unique_ptr<Node> parseVariableExpr();
        std::unique_ptr<Node> parseGroupingExpr();
        
        // Helper methods for statement parsing
        std::unique_ptr<Node> parseParameter();
        std::unique_ptr<Node> parseType();
        bool isTypeStart(TokenType type) const;
        bool isBuiltinType(TokenType type) const;
        bool isReservedKeyword(const std::string& identifier) const;
        
        // Unified grammar system - core parsing combinators
        RuleResult parseSequence(const std::vector<std::string>& elements, ParseContext& context);
        RuleResult parseChoice(const std::vector<std::string>& alternatives, ParseContext& context);
        RuleResult parseOptional(const std::string& element, ParseContext& context);
        RuleResult parseZeroOrMore(const std::string& element, ParseContext& context);
        RuleResult parseOneOrMore(const std::string& element, ParseContext& context);
        RuleResult parseSeparated(const std::string& element, const std::string& separator, ParseContext& context);
        
        // Token matching for unified grammar
        RuleResult parseToken(TokenType type, ParseContext& context);
        RuleResult parseKeyword(const std::string& keyword, ParseContext& context);
        RuleResult parseIdentifier(ParseContext& context);
        RuleResult parseLiteral(ParseContext& context);
        
        // Output generation - dual mode support
        template<typename NodeType>
        RuleResult createOutputNode(CST::NodeKind cstKind, ParseContext& context);
        
        RuleResult createCSTNode(CST::NodeKind kind, ParseContext& context);
        RuleResult createASTNode(ParseContext& context);
        
        // Grammar initialization methods
        void initializeCoreGrammar();
        void initializeStatementGrammar();
        void initializeExpressionGrammar();
        void initializeDeclarationGrammar();
        void initializeTypeGrammar();
        
        // Performance and caching
        void updateStats(const RuleResult& result) const;
        std::string getCurrentRuleContext(ParseContext& context) const;
        bool shouldUseCache(const std::string& ruleName) const;
        void cacheResult(const std::string& ruleName, size_t tokenPos, const RuleResult& result) const;
        std::optional<RuleResult> getCachedResult(const std::string& ruleName, size_t tokenPos) const;
        
        // Helper method for binary expressions in unified grammar
        RuleResult parseBinaryExpressionRule(const std::string& nextRule, const std::vector<TokenType>& operators, ParseContext& context);
    };

    // Utility functions for working with CSTParser
    
    // Parse source code directly to CST
    std::unique_ptr<Node> parseSourceToCST(const std::string& source, 
                                          const CSTConfig& scanConfig = {},
                                          const RecoveryConfig& parseConfig = {});
    
    // Parse tokens to CST with error recovery
    std::unique_ptr<Node> parseTokensToCST(const std::vector<Token>& tokens,
                                          const RecoveryConfig& config = {});
    
    // Check if parsing was successful (no fatal errors)
    bool isParsingSuccessful(const std::vector<ParseError>& errors);
    
    // Get human-readable error summary
    std::string formatErrors(const std::vector<ParseError>& errors);
    
    // Filter errors by type
    std::vector<ParseError> filterErrorsByType(const std::vector<ParseError>& errors,
                                              const std::string& errorType);

    // Unified grammar utility functions
    
    // Create a rule builder
    RuleBuilder rule(const std::string& name);
    
    // Parse source code with unified parser
    template<typename OutputType>
    std::shared_ptr<OutputType> parseSource(const std::string& source, ParserMode mode = ParserMode::DIRECT_AST);
    
    // Performance comparison utilities
    struct PerformanceComparison {
        double directASTTime = 0.0;
        double cstThenASTTime = 0.0;
        double cstOnlyTime = 0.0;
        size_t tokensProcessed = 0;
        
        double getSpeedup() const {
            return cstThenASTTime > 0 ? cstThenASTTime / directASTTime : 0.0;
        }
        
        void print() const;
    };
    
    PerformanceComparison benchmarkModes(const std::string& source);
    
    // Grammar validation utilities
    bool validateUnifiedGrammar(const GrammarTable& grammar);
    std::vector<std::string> findGrammarIssues(const GrammarTable& grammar);

    // Template specializations for type-safe parsing
    template<>
    std::shared_ptr<AST::Program> CSTParser::parseRule<AST::Program>(const std::string& ruleName, ParserMode mode);
    
    template<>
    std::shared_ptr<AST::Statement> CSTParser::parseRule<AST::Statement>(const std::string& ruleName, ParserMode mode);
    
    template<>
    std::shared_ptr<AST::Expression> CSTParser::parseRule<AST::Expression>(const std::string& ruleName, ParserMode mode);

} // namespace CST

#endif // CST_PARSER_H
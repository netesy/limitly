#ifndef AST_H
#define AST_H

#include <memory>
#include <vector>
#include <string>
#include <variant>
#include <optional>
#include <unordered_map>
#include "scanner.hh"

// Forward declarations for AST node types
namespace AST {
    struct Node;
    struct Expression;
    struct Statement;
    struct Program;
    struct BinaryExpr;
    struct UnaryExpr;
    struct LiteralExpr;
    struct VariableExpr;
    struct CallExpr;
    struct AssignExpr;
    struct TernaryExpr;
    struct GroupingExpr;
    struct IndexExpr;
    struct MemberExpr;
    struct ListExpr;
    struct DictExpr;
    struct RangeExpr;
    struct ExprStatement;
    struct VarDeclaration;
    struct FunctionDeclaration;
    struct ClassDeclaration;
    struct BlockStatement;
    struct IfStatement;
    struct ForStatement;
    struct WhileStatement;
    struct IterStatement;
    struct ReturnStatement;
    struct PrintStatement;
    struct AttemptStatement;
    struct HandleClause;
    struct ParallelStatement;
    struct ConcurrentStatement;
    struct AwaitExpr;
    struct AsyncFunctionDeclaration;
    struct ImportStatement;
    struct EnumDeclaration;
    struct MatchStatement;
    struct MatchCase;
    struct TypeAnnotation;
    struct TypeDeclaration;
    struct TraitDeclaration;
    struct InterfaceDeclaration;
    struct ModuleDeclaration;
    struct UnsafeStatement;
    struct ContractStatement;
    struct ComptimeStatement;
}

// AST Node definitions
namespace AST {
    // Base node type
    struct Node {
        int line;
        virtual ~Node() = default;
    };

    // Base expression type
    struct Expression : public Node {
        virtual ~Expression() = default;
    };

    // Base statement type
    struct Statement : public Node {
        virtual ~Statement() = default;
    };

    // Type annotation structure
    struct TypeAnnotation {
        std::string typeName;
        bool isOptional = false;
        std::vector<TypeAnnotation> genericParams;
        std::vector<TypeAnnotation> functionParams;
        std::vector<TypeAnnotation> unionTypes;
        std::shared_ptr<Expression> refinementCondition = nullptr; // For refined types (e.g., int where value > 0)
    };

    // Program - the root of our AST
    struct Program : public Node {
        std::vector<std::shared_ptr<Statement>> statements;
    };

    // Binary expression (e.g., a + b, x == y)
    struct BinaryExpr : public Expression {
        std::shared_ptr<Expression> left;
        TokenType op;
        std::shared_ptr<Expression> right;
    };

    // Unary expression (e.g., !x, -y)
    struct UnaryExpr : public Expression {
        TokenType op;
        std::shared_ptr<Expression> right;
    };

    // Literal values (numbers, strings, booleans, nil)
    struct LiteralExpr : public Expression {
        std::variant<int, double, std::string, bool, std::nullptr_t> value;
    };

    // Variable reference
    struct VariableExpr : public Expression {
        std::string name;
    };

    // Function call
    struct CallExpr : public Expression {
        std::shared_ptr<Expression> callee;
        std::vector<std::shared_ptr<Expression>> arguments;
        std::unordered_map<std::string, std::shared_ptr<Expression>> namedArgs;
    };

    // Assignment expression
    struct AssignExpr : public Expression {
        std::string name;
        std::shared_ptr<Expression> value;
        TokenType op = TokenType::EQUAL; // Default is simple assignment, but can be +=, -=, etc.
    };

    // Ternary expression (condition ? thenExpr : elseExpr)
    struct TernaryExpr : public Expression {
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Expression> thenBranch;
        std::shared_ptr<Expression> elseBranch;
    };

    // Grouping expression (parenthesized expressions)
    struct GroupingExpr : public Expression {
        std::shared_ptr<Expression> expression;
    };

    // Array/list indexing (arr[idx])
    struct IndexExpr : public Expression {
        std::shared_ptr<Expression> object;
        std::shared_ptr<Expression> index;
    };

    // Member access (obj.member)
    struct MemberExpr : public Expression {
        std::shared_ptr<Expression> object;
        std::string name;
    };

    // List literal [1, 2, 3] or (1, 2, 3)
    struct ListExpr : public Expression {
        std::vector<std::shared_ptr<Expression>> elements;
    };

    // Dictionary literal {'a': 1, 'b': 2}
    struct DictExpr : public Expression {
        std::vector<std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>>> entries;
    };
    
    // Range expression (e.g., 1..10)
    struct RangeExpr : public Expression {
        std::shared_ptr<Expression> start;
        std::shared_ptr<Expression> end;
        std::shared_ptr<Expression> step; // Optional step value
        bool inclusive; // Whether the range includes the step value
    };

    // Expression statement
    struct ExprStatement : public Statement {
        std::shared_ptr<Expression> expression;
    };

    // Variable declaration
    struct VarDeclaration : public Statement {
        std::string name;
        std::optional<TypeAnnotation> type;
        std::shared_ptr<Expression> initializer;
    };

    // Function declaration
    struct FunctionDeclaration : public Statement {
        std::string name;
        std::vector<std::pair<std::string, TypeAnnotation>> params;
        std::vector<std::pair<std::string, std::pair<TypeAnnotation, std::shared_ptr<Expression>>>> optionalParams;
        std::optional<TypeAnnotation> returnType;
        std::shared_ptr<BlockStatement> body;
        std::vector<std::string> genericParams;
        bool throws = false;
    };

    // Async function declaration
    struct AsyncFunctionDeclaration : public FunctionDeclaration {
        // Constructor that takes a FunctionDeclaration
        AsyncFunctionDeclaration(const FunctionDeclaration& func) {
            name = func.name;
            params = func.params;
            optionalParams = func.optionalParams;
            returnType = func.returnType;
            body = func.body;
            genericParams = func.genericParams;
            throws = func.throws;
            line = func.line;
        }
        
        // Default constructor
        AsyncFunctionDeclaration() = default;
    };

    // Class declaration
    struct ClassDeclaration : public Statement {
        std::string name;
        std::vector<std::shared_ptr<VarDeclaration>> fields;
        std::vector<std::shared_ptr<FunctionDeclaration>> methods;
    };

    // Block statement (sequence of statements)
    struct BlockStatement : public Statement {
        std::vector<std::shared_ptr<Statement>> statements;
    };

    // If statement
    struct IfStatement : public Statement {
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Statement> thenBranch;
        std::shared_ptr<Statement> elseBranch;
    };

    // For statement
    struct ForStatement : public Statement {
        // For traditional loop: for (var i = 0; i < 5; i++)
        std::shared_ptr<Statement> initializer;
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Expression> increment;
        
        // For range/collection loop: for (var i in range(10)) or for (key, value in dict)
        std::vector<std::string> loopVars;
        std::shared_ptr<Expression> iterable;
        
        std::shared_ptr<Statement> body;
        bool isIterableLoop = false;
    };

    // While statement
    struct WhileStatement : public Statement {
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Statement> body;
    };

    // Return statement
    struct ReturnStatement : public Statement {
        std::shared_ptr<Expression> value;
    };

    // Print statement
    struct PrintStatement : public Statement {
        std::vector<std::shared_ptr<Expression>> arguments;
    };

    // Exception handling
    struct HandleClause {
        std::string errorType;
        std::string errorVar;
        std::shared_ptr<BlockStatement> body;
    };

    struct AttemptStatement : public Statement {
        std::shared_ptr<BlockStatement> tryBlock;
        std::vector<HandleClause> handlers;
    };

    // Concurrency constructs
    struct ParallelStatement : public Statement {
        std::shared_ptr<BlockStatement> body;
    };

    struct ConcurrentStatement : public Statement {
        std::shared_ptr<BlockStatement> body;
    };

    // Await expression
    struct AwaitExpr : public Expression {
        std::shared_ptr<Expression> expression;
    };

    // Import statement
    struct ImportStatement : public Statement {
        std::string module;
    };

    // Enum declaration
    struct EnumDeclaration : public Statement {
        std::string name;
        std::vector<std::pair<std::string, std::optional<TypeAnnotation>>> variants;
    };

    // Pattern matching
    struct MatchCase {
        std::shared_ptr<Expression> pattern;
        std::shared_ptr<Statement> body;
    };

    struct MatchStatement : public Statement {
        std::shared_ptr<Expression> value;
        std::vector<MatchCase> cases;
    };
    
    // Type declaration (type aliases)
    struct TypeDeclaration : public Statement {
        std::string name;
        TypeAnnotation type;
    };
    
    // Trait declaration
    struct TraitDeclaration : public Statement {
        std::string name;
        std::vector<std::shared_ptr<FunctionDeclaration>> methods;
        bool isOpen = false;
    };
    
    // Interface declaration
    struct InterfaceDeclaration : public Statement {
        std::string name;
        std::vector<std::shared_ptr<FunctionDeclaration>> methods;
        bool isOpen = false;
    };
    
    // Module declaration
    struct ModuleDeclaration : public Statement {
        std::string name;
        std::vector<std::shared_ptr<Statement>> publicMembers;
        std::vector<std::shared_ptr<Statement>> protectedMembers;
        std::vector<std::shared_ptr<Statement>> privateMembers;
    };
    
    // Iter statement (for modern iteration)
    struct IterStatement : public Statement {
        std::vector<std::string> loopVars;
        std::shared_ptr<Expression> iterable;
        std::shared_ptr<Statement> body;
    };
    
    // Unsafe block
    struct UnsafeStatement : public Statement {
        std::shared_ptr<BlockStatement> body;
    };
    
    // Contract statement
    struct ContractStatement : public Statement {
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Expression> message;
    };
    
    // Compile-time statement
    struct ComptimeStatement : public Statement {
        std::shared_ptr<Statement> declaration;
    };
}

#endif // AST_H
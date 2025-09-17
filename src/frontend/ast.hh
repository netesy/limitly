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
    struct ThisExpr;
    struct SuperExpr;
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
    struct BreakStatement;
    struct ContinueStatement;
    struct PrintStatement;
    struct AttemptStatement;
    struct HandleClause;
    struct ParallelStatement;
    struct ConcurrentStatement;
    struct TaskStatement;
    struct WorkerStatement;
    struct AwaitExpr;
    struct AsyncFunctionDeclaration;
    struct ImportStatement;
    struct FallibleExpr;
    struct ErrorConstructExpr;
    struct OkConstructExpr;
    struct EnumDeclaration;
    struct MatchStatement;
    struct MatchCase;
    struct TypePatternExpr;
    struct BindingPatternExpr;
    struct ListPatternExpr;
    struct DictPatternExpr;
    struct TuplePatternExpr;
    struct TypeAnnotation;
    struct StructuralTypeField;
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
        std::vector<Token> annotations;
        virtual ~Statement() = default;
    };

    // Type annotation structure - forward declaration
    struct TypeAnnotation;
    
    // Field in a structural type
    struct StructuralTypeField {
        std::string name;
        std::shared_ptr<TypeAnnotation> type;
    };
    
    // Type annotation structure
    struct TypeAnnotation {
        std::string typeName;                                  // The name of the type (e.g., "int", "str", "Person")
        bool isOptional = false;                               // Whether this is an optional type (e.g., int?)
        bool isPrimitive = false;                              // Whether this is a primitive type (e.g., int, str, bool)
        bool isUserDefined = false;                            // Whether this is a user-defined type (e.g., Person, Vehicle)
        bool isStructural = false;                             // Whether this is a structural type (e.g., { name: str, age: int })
        bool isUnion = false;                                  // Whether this is a union type (e.g., int | str)
        bool isIntersection = false;                           // Whether this is an intersection type (e.g., HasName and HasAge)
        bool isList = false;                                   // Whether this is a list type (e.g., [int], ListOfString)
        bool isDict = false;                                   // Whether this is a dictionary type (e.g., {str: int}, DictOfStrToInt)
        bool isFunction = false;                               // Whether this is a function type
        bool isRefined = false;                                // Whether this is a refined type (e.g., int where value > 0)
        bool hasRest = false;                                  // Whether this structural type has a rest parameter (...)
        
        std::string baseRecord = "";                           // Name of the base record for extensible records
        std::vector<std::string> baseRecords;                  // Multiple base records for extensible records
        
        std::vector<std::shared_ptr<TypeAnnotation>> functionParams;    // Function parameters for function types
        std::vector<std::shared_ptr<TypeAnnotation>> unionTypes;        // Types in a union (e.g., int | str)
        std::vector<StructuralTypeField> structuralFields;              // Fields in a structural type
        
        std::shared_ptr<Expression> refinementCondition = nullptr;      // For refined types (e.g., int where value > 0)
        std::shared_ptr<TypeAnnotation> returnType = nullptr;           // Return type for function types
        std::shared_ptr<TypeAnnotation> elementType = nullptr;          // Element type for list types (e.g., [int])
        std::shared_ptr<TypeAnnotation> keyType = nullptr;              // Key type for dictionary types (e.g., {str: int})
        std::shared_ptr<TypeAnnotation> valueType = nullptr;            // Value type for dictionary types (e.g., {str: int})
        
        // Error handling support
        bool isFallible = false;                                         // Whether this type can fail (Type?)
        std::vector<std::string> errorTypes;                             // Specific error types (Type?Error1, Error2)
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

    // Interpolated string expression (e.g., "Hello, {name}!")
    struct InterpolatedStringExpr : public Expression {
        // Each part is either a string literal or an expression
        std::vector<std::variant<std::string, std::shared_ptr<Expression>>> parts;
        
        // Add a string part
        void addStringPart(const std::string& str) {
            parts.push_back(str);
        }
        
        // Add an expression part
        void addExpressionPart(std::shared_ptr<Expression> expr) {
            parts.push_back(expr);
        }
    };

    // Literal values (numbers, strings, booleans, nil)
    struct LiteralExpr : public Expression {
        std::variant<long long, double, std::string, bool, std::nullptr_t> value;
    };

    // Variable reference
    struct VariableExpr : public Expression {
        std::string name;
    };

    // 'self' reference in methods
    struct ThisExpr : public Expression {
        // No additional fields needed, just represents 'self'
    };

    // 'super' reference for parent class access
    struct SuperExpr : public Expression {
        // No additional fields needed, just represents 'super'
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
    // For member or index assignment
    std::shared_ptr<Expression> object;
    std::optional<std::string> member; // for member assignment
    std::shared_ptr<Expression> index; // for index assignment


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
        std::optional<std::shared_ptr<TypeAnnotation>> type;
        std::shared_ptr<Expression> initializer;
    };

    // Function declaration
    struct FunctionDeclaration : public Statement {
        std::string name;
        std::vector<std::pair<std::string, std::shared_ptr<TypeAnnotation>>> params;
        std::vector<std::pair<std::string, std::pair<std::shared_ptr<TypeAnnotation>, std::shared_ptr<Expression>>>> optionalParams;
        std::optional<std::shared_ptr<TypeAnnotation>> returnType;
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
        
        // Inheritance support
        std::string superClassName;  // Name of the parent class
        std::vector<std::shared_ptr<Expression>> superConstructorArgs;  // Arguments for super constructor call
        
        // Inline constructor support
        std::vector<std::pair<std::string, std::shared_ptr<TypeAnnotation>>> constructorParams;  // Constructor parameters
        bool hasInlineConstructor = false;
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

    // Break statement
    struct BreakStatement : public Statement {};

    // Continue statement
    struct ContinueStatement : public Statement {};

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
        std::string channel;  // Channel name for communication
        std::string mode;     // Execution mode (fork-join, etc.)
        std::string cores;    // Number of cores to use (or "auto")
        std::string onError;  // Error handling strategy
        std::string timeout;  // Timeout duration
        std::string grace;    // Grace period for cleanup
        std::string onTimeout; // Action on timeout
        std::shared_ptr<BlockStatement> body;
    };

    struct ConcurrentStatement : public Statement {
        std::string channel;  // Channel name for communication
        std::string mode;     // Execution mode (batch, stream, async)
        std::string cores;    // Number of cores to use (or "auto")
        std::string onError;  // Error handling strategy
        std::string timeout;  // Timeout duration
        std::string grace;    // Grace period for cleanup
        std::string onTimeout; // Action on timeout
        std::shared_ptr<BlockStatement> body;
    };

    // Task statement inside a concurrent/parallel block
    struct TaskStatement : public Statement {
        bool isAsync = false;
        std::string loopVar;
        std::shared_ptr<Expression> iterable;
        std::shared_ptr<BlockStatement> body;
    };

    // Worker statement inside a concurrent/parallel block
    struct WorkerStatement : public Statement {
        bool isAsync = false;
        std::string param;
        std::shared_ptr<BlockStatement> body;
    };

    // Await expression
    struct AwaitExpr : public Expression {
        std::shared_ptr<Expression> expression;
    };

    // Import statement filter type
    enum class ImportFilterType {
        Show,
        Hide
    };

    // Import statement filter
    struct ImportFilter {
        ImportFilterType type;
        std::vector<std::string> identifiers;
    };

    // Import statement
    struct ImportStatement : public Statement {
        std::string modulePath;
        bool isStringLiteralPath = false;
        std::optional<std::string> alias;
        std::optional<ImportFilter> filter;
    };

    // Enum declaration
    struct EnumDeclaration : public Statement {
        std::string name;
        std::vector<std::pair<std::string, std::optional<std::shared_ptr<TypeAnnotation>>>> variants;
    };

    // Pattern matching
    struct BindingPatternExpr;
    struct ListPatternExpr;

    struct MatchCase {
        std::shared_ptr<Expression> pattern;
        std::shared_ptr<Expression> guard;
        std::shared_ptr<Statement> body;
    };

    struct MatchStatement : public Statement {
        std::shared_ptr<Expression> value;
        std::vector<MatchCase> cases;
    };

    // Type pattern in a match statement
    struct TypePatternExpr : public Expression {
        std::shared_ptr<TypeAnnotation> type;
    };

    // Binding pattern in a match statement (e.g., Some(x))
    struct BindingPatternExpr : public Expression {
        std::string typeName;
        std::string variableName;
    };

    // List pattern in a match statement (e.g., [x, ...xs])
    struct ListPatternExpr : public Expression {
        std::vector<std::shared_ptr<Expression>> elements;
        std::optional<std::string> restElement;
    };

    // Dictionary/Record destructuring pattern (e.g., {name, age} or {name: x, age: y})
    struct DictPatternExpr : public Expression {
        struct Field {
            std::string key;
            std::optional<std::string> binding; // If empty, use key as binding name
        };
        std::vector<Field> fields;
        bool hasRestElement = false;
        std::optional<std::string> restBinding;
    };

    // Tuple destructuring pattern (e.g., (x, y, z))
    struct TuplePatternExpr : public Expression {
        std::vector<std::shared_ptr<Expression>> elements;
    };
    
    // Type declaration (type aliases)
    struct TypeDeclaration : public Statement {
        std::string name;
        std::shared_ptr<TypeAnnotation> type;
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

    // Error handling expressions
    
    // Fallible expression with ? operator
    struct FallibleExpr : public Expression {
        std::shared_ptr<Expression> expression;
        std::shared_ptr<Statement> elseHandler;  // Optional else block
        std::string elseVariable;                // Optional error variable name
    };

    // Error construction expression (err() calls)
    struct ErrorConstructExpr : public Expression {
        std::string errorType;                   // Error type name
        std::vector<std::shared_ptr<Expression>> arguments;  // Constructor arguments
    };

    // Success value construction (ok() calls)
    struct OkConstructExpr : public Expression {
        std::shared_ptr<Expression> value;
    };
}

#endif // AST_H
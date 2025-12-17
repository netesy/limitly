#ifndef AST_H
#define AST_H

#include <memory>
#include <vector>
#include <string>
#include <variant>
#include <optional>
#include <unordered_map>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include "scanner.hh"
// #include "../common/big_int.hh"

// Forward declarations
struct Type;
using TypePtr = std::shared_ptr<Type>;

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
    struct CallClosureExpr;
    struct AssignExpr;
    struct TernaryExpr;
    struct GroupingExpr;
    struct IndexExpr;
    struct MemberExpr;
    struct ListExpr;
    struct DictExpr;
    struct ObjectLiteralExpr;
    struct RangeExpr;
    struct ExprStatement;
    struct VarDeclaration;
    struct DestructuringDeclaration;
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
    struct SomeConstructExpr;
    struct NoneConstructExpr;
    struct EnumDeclaration;
    struct MatchStatement;
    struct MatchCase;
    struct TypePatternExpr;
    struct BindingPatternExpr;
    struct ListPatternExpr;
    struct DictPatternExpr;
    struct TuplePatternExpr;
    struct TupleExpr;
    struct ValPatternExpr;
    struct ErrPatternExpr;
    struct ErrorTypePatternExpr;
    struct LambdaExpr;
    struct TypeAnnotation;
    struct FunctionTypeAnnotation;
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
    // Visibility levels for module-level declarations and class members
    enum class VisibilityLevel {
        Private,    // Default - no keyword
        Protected,  // prot
        Public,     // pub
        Const       // const (read-only public)
    };

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
    
    // Function parameter for function type annotations
    struct FunctionParameter {
        std::string name;                                      // Parameter name (optional)
        std::shared_ptr<TypeAnnotation> type;                  // Parameter type
        bool hasDefaultValue = false;                          // Whether parameter has default value
        
        FunctionParameter() = default;
        FunctionParameter(const std::string& n, std::shared_ptr<TypeAnnotation> t) 
            : name(n), type(t) {}
        FunctionParameter(std::shared_ptr<TypeAnnotation> t) 
            : type(t) {}
    };

    // Type annotation structure
    struct TypeAnnotation {
        virtual ~TypeAnnotation() = default;                  // Make polymorphic for dynamic_cast
        
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
        bool isTuple = false;                                  // Whether this is a tuple type (e.g., (int, str))
        bool isRefined = false;                                // Whether this is a refined type (e.g., int where value > 0)
        bool hasRest = false;                                  // Whether this structural type has a rest parameter (...)
        
        std::string baseRecord = "";                           // Name of the base record for extensible records
        std::vector<std::string> baseRecords;                  // Multiple base records for extensible records
        
        // Enhanced function type support
        std::vector<FunctionParameter> functionParameters;              // Named function parameters with types
        std::vector<std::shared_ptr<TypeAnnotation>> functionParams;    // Legacy function parameters (for backward compatibility)
        std::vector<std::shared_ptr<TypeAnnotation>> unionTypes;        // Types in a union (e.g., int | str)
        std::vector<std::shared_ptr<TypeAnnotation>> tupleTypes;        // Types in a tuple (e.g., (int, str))
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

    // Function type annotation with specific signature (e.g., fn(a: int, b: str): bool)
    struct FunctionTypeAnnotation : public TypeAnnotation {
        std::vector<FunctionParameter> parameters;                       // Named parameters with types
        std::shared_ptr<TypeAnnotation> returnType;                      // Return type
        bool isVariadic = false;                                         // Whether function accepts variable arguments
        
        FunctionTypeAnnotation() {
            typeName = "function";
            isFunction = true;
        }
        
        // Helper methods
        size_t getParameterCount() const { return parameters.size(); }
        
        bool hasNamedParameters() const {
            return std::any_of(parameters.begin(), parameters.end(),
                             [](const FunctionParameter& param) { return !param.name.empty(); });
        }
        
        std::vector<TypePtr> getParameterTypes() const;  // Convert to TypePtr vector
        
        // Type compatibility checking
        bool isCompatibleWith(const FunctionTypeAnnotation& other) const;
        
        // String representation
        std::string toString() const;
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
        std::variant<std::string, bool, std::nullptr_t> value;
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

    // Closure call (for calling closure variables)
    struct CallClosureExpr : public Expression {
        std::shared_ptr<Expression> closure;  // The closure expression to call
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

    // List literal [1, 2, 3]
    struct ListExpr : public Expression {
        std::vector<std::shared_ptr<Expression>> elements;
    };

    // Tuple literal (1, 2, 3)
    struct TupleExpr : public Expression {
        std::vector<std::shared_ptr<Expression>> elements;
    };

    // Dictionary literal {'a': 1, 'b': 2}
    struct DictExpr : public Expression {
        std::vector<std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>>> entries;
    };
    
    // Object literal with constructor name (e.g., Some { kind: "Some", value: 42 })
    struct ObjectLiteralExpr : public Expression {
        std::string constructorName;
        std::unordered_map<std::string, std::shared_ptr<Expression>> properties;
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
        
        // Module-level visibility (for module-level variables)
        VisibilityLevel visibility = VisibilityLevel::Private;  // Default to private
        bool isStatic = false;                                  // For static variables
    };

    // Destructuring assignment (e.g., var (x, y, z) = tuple)
    struct DestructuringDeclaration : public Statement {
        std::vector<std::string> names;  // Variable names to destructure into
        std::shared_ptr<Expression> initializer;  // The tuple/array expression to destructure
        bool isTuple = true;  // Whether destructuring a tuple (true) or array (false)
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
        
        // Error type annotations for function signature
        bool canFail = false;                                    // Whether function can return errors
        std::vector<std::string> declaredErrorTypes;             // Specific error types function can return
        
        // Module-level visibility (for module-level functions)
        VisibilityLevel visibility = VisibilityLevel::Private;  // Default to private
        bool isStatic = false;                                  // For static functions
        bool isAbstract = false;                                // For abstract functions
        bool isFinal = false;                                   // For final functions
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
        
        // Visibility and modifiers
        bool isAbstract = false;
        bool isFinal = false;
        bool isDataClass = false;
        std::vector<std::string> interfaces;
        
        // Field and method visibility
        std::map<std::string, VisibilityLevel> fieldVisibility;
        std::map<std::string, VisibilityLevel> methodVisibility;
        std::set<std::string> staticMembers;
        std::set<std::string> abstractMethods;
        std::set<std::string> finalMethods;
        std::set<std::string> readOnlyFields;
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
        // Traditional C-style for loop: for (var i = 0; i < 5; i++)
        std::shared_ptr<Statement> initializer;
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Expression> increment;
        std::shared_ptr<Statement> body;
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

    // Error pattern matching expressions
    
    // Success value pattern (val identifier)
    struct ValPatternExpr : public Expression {
        std::string variableName;
    };

    // Error pattern (err identifier)
    struct ErrPatternExpr : public Expression {
        std::string variableName;
        std::optional<std::string> errorType;  // Optional specific error type
    };

    // Specific error type pattern (ErrorType or ErrorType(params))
    struct ErrorTypePatternExpr : public Expression {
        std::string errorType;
        std::vector<std::string> parameterNames;  // For extracting error parameters
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

    // Option type construction expressions
    struct SomeConstructExpr : public Expression {
        std::shared_ptr<Expression> value;
    };

    struct NoneConstructExpr : public Expression {
        // None takes no arguments, but may have type annotation context
    };

    // Lambda expression (e.g., fn(x, y) {x + y})
    struct LambdaExpr : public Expression {
        std::vector<std::pair<std::string, std::shared_ptr<TypeAnnotation>>> params;
        std::shared_ptr<BlockStatement> body;  // Block body
        std::optional<std::shared_ptr<TypeAnnotation>> returnType;
        
        // Captured variables (determined during analysis)
        std::vector<std::string> capturedVars;
    };
}

// FunctionTypeAnnotation method implementations
namespace AST {
    inline std::vector<TypePtr> FunctionTypeAnnotation::getParameterTypes() const {
        std::vector<TypePtr> types;
        for (const auto& param : parameters) {
            if (param.type) {
                // This would need to be converted from AST::TypeAnnotation to TypePtr
                // For now, we'll return empty vector as this requires TypeSystem integration
            }
        }
        return types; // Placeholder - needs TypeSystem integration
    }

    inline bool FunctionTypeAnnotation::isCompatibleWith(const FunctionTypeAnnotation& other) const {
        // Check parameter count
        if (parameters.size() != other.parameters.size()) {
            return false;
        }
        
        // For now, do basic comparison - full implementation needs TypeSystem
        for (size_t i = 0; i < parameters.size(); ++i) {
            if (!parameters[i].type || !other.parameters[i].type) {
                return false;
            }
            
            // Basic type name comparison (would need proper type checking)
            if (parameters[i].type->typeName != other.parameters[i].type->typeName) {
                return false;
            }
        }
        
        // Check return types
        if (returnType && other.returnType) {
            return returnType->typeName == other.returnType->typeName;
        }
        
        return returnType == other.returnType; // Both null or both non-null
    }

    inline std::string FunctionTypeAnnotation::toString() const {
        std::ostringstream oss;
        oss << "fn(";
        
        for (size_t i = 0; i < parameters.size(); ++i) {
            if (i > 0) oss << ", ";
            
            // Add parameter name if available
            if (!parameters[i].name.empty()) {
                oss << parameters[i].name << ": ";
            }
            
            // Add parameter type
            if (parameters[i].type) {
                oss << parameters[i].type->typeName;
            } else {
                oss << "unknown";
            }
            
            // Add default indicator if applicable
            if (parameters[i].hasDefaultValue) {
                oss << "?";
            }
        }
        
        if (isVariadic) {
            if (!parameters.empty()) oss << ", ";
            oss << "...";
        }
        
        oss << ")";
        
        // Add return type
        if (returnType) {
            oss << ": " << returnType->typeName;
        }
        
        return oss.str();
    }
}

#endif // AST_H
#ifndef LM_LM_FRONTEND_AST_H
#define LM_LM_FRONTEND_AST_H

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
#include <stack>
#include <queue>
#include "scanner.hh"
#include "../backend/types.hh"

namespace LM {
namespace Frontend {

using TypePtr = LM::Backend::TypePtr;

namespace AST {
    enum class VisibilityLevel {
        Private, Protected, Public, Const
    };

    inline std::string visibilityToString(VisibilityLevel level) {
        switch (level) {
            case VisibilityLevel::Private: return "private";
            case VisibilityLevel::Protected: return "protected";
            case VisibilityLevel::Public: return "public";
            case VisibilityLevel::Const: return "const";
            default: return "unknown";
        }
    }

    struct Node : public std::enable_shared_from_this<Node> {
        int line;
        mutable TypePtr inferred_type = nullptr;
        virtual ~Node() = default;
    };

    struct Expression : public Node {
        virtual ~Expression() = default;
    };

    struct Statement : public Node {
        std::vector<LM::Frontend::Token> annotations;
        virtual ~Statement() = default;
    };

    struct TypeAnnotation {
        virtual ~TypeAnnotation() = default;
        std::string typeName;
        bool isOptional = false;
    };

    struct Program : public Node {
        std::vector<std::shared_ptr<Statement>> statements;
    };

    struct BinaryExpr : public Expression {
        std::shared_ptr<Expression> left;
        LM::Frontend::TokenType op;
        std::shared_ptr<Expression> right;
    };

    struct UnaryExpr : public Expression {
        LM::Frontend::TokenType op;
        std::shared_ptr<Expression> right;
    };

    struct LiteralExpr : public Expression {
        std::variant<std::string, bool, std::nullptr_t> value;
        LM::Frontend::TokenType literalType = LM::Frontend::TokenType::STRING;
    };

    struct VariableExpr : public Expression {
        std::string name;
    };

    struct ThisExpr : public Expression {};
    struct SuperExpr : public Expression {};

    struct CallExpr : public Expression {
        std::shared_ptr<Expression> callee;
        std::vector<std::shared_ptr<Expression>> arguments;
        std::unordered_map<std::string, std::shared_ptr<Expression>> namedArgs;
    };

    struct AssignExpr : public Expression {
        std::string name;
        std::shared_ptr<Expression> object;
        std::optional<std::string> member;
        std::shared_ptr<Expression> index;
        std::shared_ptr<Expression> value;
        LM::Frontend::TokenType op = LM::Frontend::TokenType::EQUAL;
    };

    struct GroupingExpr : public Expression {
        std::shared_ptr<Expression> expression;
    };

    struct MemberExpr : public Expression {
        std::shared_ptr<Expression> object;
        std::string name;
    };

    struct IndexExpr : public Expression {
        std::shared_ptr<Expression> object;
        std::shared_ptr<Expression> index;
    };

    struct ListExpr : public Expression {
        std::vector<std::shared_ptr<Expression>> elements;
    };

    struct TupleExpr : public Expression {
        std::vector<std::shared_ptr<Expression>> elements;
    };

    struct DictExpr : public Expression {
        std::vector<std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>>> entries;
    };

    struct ExprStatement : public Statement {
        std::shared_ptr<Expression> expression;
    };

    struct VarDeclaration : public Statement {
        std::string name;
        std::optional<std::shared_ptr<TypeAnnotation>> type;
        std::shared_ptr<Expression> initializer;
        VisibilityLevel visibility = VisibilityLevel::Private;
    };

    struct BlockStatement : public Statement {
        std::vector<std::shared_ptr<Statement>> statements;
    };

    struct FunctionDeclaration : public Statement {
        std::string name;
        std::vector<std::pair<std::string, std::shared_ptr<TypeAnnotation>>> params;
        std::vector<std::pair<std::string, std::pair<std::shared_ptr<TypeAnnotation>, std::shared_ptr<Expression>>>> optionalParams;
        std::optional<std::shared_ptr<TypeAnnotation>> returnType;
        std::shared_ptr<BlockStatement> body;
        bool throws = false;
        bool canFail = false;
        std::vector<std::string> declaredErrorTypes;
    };

    struct IfStatement : public Statement {
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Statement> thenBranch;
        std::shared_ptr<Statement> elseBranch;
    };

    struct WhileStatement : public Statement {
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Statement> body;
    };

    struct ForStatement : public Statement {
        std::shared_ptr<Statement> initializer;
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Expression> increment;
        std::shared_ptr<Statement> body;
    };

    struct ParallelStatement : public Statement {
        std::shared_ptr<BlockStatement> body;
    };

    struct ConcurrentStatement : public Statement {
        std::string channel;
        std::shared_ptr<BlockStatement> body;
    };

    struct TaskStatement : public Statement {
        std::string loopVar;
        std::shared_ptr<Expression> iterable;
        std::shared_ptr<BlockStatement> body;
    };

    struct WorkerStatement : public Statement {
        std::string paramName;
        std::shared_ptr<Expression> iterable;
        std::shared_ptr<BlockStatement> body;
    };

    struct ReturnStatement : public Statement {
        std::shared_ptr<Expression> value;
    };

    struct PrintStatement : public Statement {
        std::vector<std::shared_ptr<Expression>> arguments;
    };

    struct FallibleExpr : public Expression {
        std::shared_ptr<Expression> expression;
    };

    struct ErrorConstructExpr : public Expression {
        std::string errorType;
        std::vector<std::shared_ptr<Expression>> arguments;
    };

    struct OkConstructExpr : public Expression {
        std::shared_ptr<Expression> value;
    };

    struct MatchCase {
        std::shared_ptr<Expression> pattern;
        std::shared_ptr<Expression> guard;
        std::shared_ptr<Statement> body;
    };

    struct MatchStatement : public Statement {
        std::shared_ptr<Expression> value;
        std::vector<MatchCase> cases;
    };

    struct BindingPatternExpr : public Expression {
        std::string typeName;
        std::string variableName;
    };

    struct TypePatternExpr : public Expression {
        std::shared_ptr<TypeAnnotation> type;
    };

    struct ValPatternExpr : public Expression {
        std::string variableName;
    };

    struct ErrPatternExpr : public Expression {
        std::string variableName;
        std::optional<std::string> errorType;
    };

    struct LambdaExpr : public Expression {
        std::vector<std::pair<std::string, std::shared_ptr<TypeAnnotation>>> params;
        std::shared_ptr<BlockStatement> body;
        std::optional<std::shared_ptr<TypeAnnotation>> returnType;
    };

    struct TypeDeclaration : public Statement {
        std::string name;
        std::shared_ptr<TypeAnnotation> type;
    };

    struct ContractStatement : public Statement {
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Expression> message;
    };

    struct FrameField {
        std::string name;
        std::shared_ptr<TypeAnnotation> type;
        VisibilityLevel visibility;
        std::shared_ptr<Expression> defaultValue;
        int line;
        FrameField() : visibility(VisibilityLevel::Private), defaultValue(nullptr), line(0) {}
    };

    struct FrameMethod : public Statement {
        std::string name;
        std::optional<std::shared_ptr<TypeAnnotation>> returnType;
        std::vector<std::pair<std::string, std::shared_ptr<TypeAnnotation>>> parameters;
        std::vector<std::pair<std::string, std::pair<std::shared_ptr<TypeAnnotation>, std::shared_ptr<Expression>>>> optionalParams;
        VisibilityLevel visibility;
        std::shared_ptr<BlockStatement> body;
        bool isStatic;
        bool isAbstract;
        bool isFinal;
        bool isInit;
        bool isDeinit;
        FrameMethod() : visibility(VisibilityLevel::Private), body(nullptr), isStatic(false), isAbstract(false), isFinal(false), isInit(false), isDeinit(false) {}
    };

    struct FrameDeclaration : public Statement {
        std::string name;
        std::string parentName;
        std::vector<std::shared_ptr<FrameField>> fields;
        std::vector<std::shared_ptr<FrameMethod>> methods;
        std::vector<std::string> implements;
        std::shared_ptr<FrameMethod> init;
        std::shared_ptr<FrameMethod> deinit;
        bool isAbstract;
        bool isFinal;
        FrameDeclaration() : init(nullptr), deinit(nullptr), isAbstract(false), isFinal(false) {}
    };

    struct TraitDeclaration : public Statement {
        std::string name;
        std::vector<std::string> extends;
        std::vector<std::shared_ptr<FunctionDeclaration>> methods;
        bool isOpen = false;
        std::vector<std::string> method_names;
    };

    struct FrameInstantiationExpr : public Expression {
        std::string frameName;
        std::vector<std::shared_ptr<Expression>> positionalArgs;
        std::unordered_map<std::string, std::shared_ptr<Expression>> namedArgs;
    };

    struct InterpolatedStringExpr : public Expression {
        std::vector<std::variant<std::string, std::shared_ptr<Expression>>> parts;
    };

} // namespace AST
} // namespace Frontend
} // namespace LM

#endif

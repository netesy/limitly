#ifndef LM_AST_OPTIMIZER_HH
#define LM_AST_OPTIMIZER_HH

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include "ast.hh"

namespace LM {
namespace Frontend {

namespace AST {

// Optimization context for tracking optimization state
struct OptimizationContext {
    struct Stats {
        size_t constantsFolded = 0;
        size_t constantsPropagated = 0;
        size_t deadCodeEliminated = 0;
        size_t branchesSimplified = 0;
        size_t algebraicSimplified = 0;
    };
    
    Stats stats;
    std::unordered_map<std::string, std::shared_ptr<Expression>> constants;
    std::set<std::string> reassigned_vars;
    std::vector<std::string> reassigned_stack;
    std::set<std::string> escaping_vars;
    
    // Mark variable as reassigned (cannot use constant propagation)
    void markReassigned(const std::string& name) {
        reassigned_vars.insert(name);
        reassigned_stack.push_back(name);
    }
    
    // Mark variable as escaping (cannot propagate)
    void markEscaping(const std::string& name) {
        escaping_vars.insert(name);
    }
};

// Base optimizer class
class ASTOptimizer {
protected:
    OptimizationContext context;
    
public:
    virtual ~ASTOptimizer() = default;
    
    // Main optimization entry point
    virtual std::shared_ptr<Program> optimize(std::shared_ptr<Program> program) {
        return optimizeProgram(program);
    }
    
    // Get optimization statistics
    const OptimizationContext::Stats& getStats() const { return context.stats; }
    
protected:
    // Optimization methods for each node type
    virtual std::shared_ptr<Program> optimizeProgram(std::shared_ptr<Program> program);
    virtual std::shared_ptr<Expression> optimizeExpression(std::shared_ptr<Expression> expr);
    virtual std::shared_ptr<Statement> optimizeStatement(std::shared_ptr<Statement> stmt);
    
    // Specific expression optimizations
    virtual std::shared_ptr<Expression> optimizeBinaryExpr(std::shared_ptr<BinaryExpr> expr);
    virtual std::shared_ptr<Expression> optimizeUnaryExpr(std::shared_ptr<UnaryExpr> expr);
    virtual std::shared_ptr<Expression> optimizeInterpolatedStringExpr(std::shared_ptr<InterpolatedStringExpr> expr);
    virtual std::shared_ptr<LiteralExpr> optimizeLiteralExpr(std::shared_ptr<LiteralExpr> expr);
    virtual std::shared_ptr<VariableExpr> optimizeVariableExpr(std::shared_ptr<VariableExpr> expr);
    virtual std::shared_ptr<Expression> optimizeGroupingExpr(std::shared_ptr<GroupingExpr> expr);
    virtual std::shared_ptr<CallExpr> optimizeCallExpr(std::shared_ptr<CallExpr> expr);
    virtual std::shared_ptr<TernaryExpr> optimizeTernaryExpr(std::shared_ptr<TernaryExpr> expr);
    virtual std::shared_ptr<AssignExpr> optimizeAssignExpr(std::shared_ptr<AssignExpr> expr);
    
    // Specific statement optimizations
    virtual std::shared_ptr<VarDeclaration> optimizeVarDeclaration(std::shared_ptr<VarDeclaration> stmt);
    virtual std::shared_ptr<BlockStatement> optimizeBlockStatement(std::shared_ptr<BlockStatement> stmt);
    virtual std::shared_ptr<Statement> optimizeIfStatement(std::shared_ptr<IfStatement> stmt);
    virtual std::shared_ptr<WhileStatement> optimizeWhileStatement(std::shared_ptr<WhileStatement> stmt);
    virtual std::shared_ptr<ForStatement> optimizeForStatement(std::shared_ptr<ForStatement> stmt);
    virtual std::shared_ptr<ReturnStatement> optimizeReturnStatement(std::shared_ptr<ReturnStatement> stmt);
    virtual std::shared_ptr<PrintStatement> optimizePrintStatement(std::shared_ptr<PrintStatement> stmt);
    
    // Core optimization utilities
    std::shared_ptr<Expression> foldConstants(std::shared_ptr<Expression> expr);
    std::shared_ptr<Expression> propagateConstants(std::shared_ptr<Expression> expr);
    std::shared_ptr<Expression> simplifyBranches(std::shared_ptr<Expression> expr);
    std::shared_ptr<Expression> simplifyAlgebraic(std::shared_ptr<Expression> expr);
    std::shared_ptr<Expression> lowerInterpolation(std::shared_ptr<InterpolatedStringExpr> expr);
    std::shared_ptr<Expression> canonicalizeStrings(std::shared_ptr<Expression> expr);
    
    // Utility methods
    bool isLiteralConstant(std::shared_ptr<Expression> expr);
    std::shared_ptr<Expression> evaluateBinaryOp(TokenType op, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> evaluateUnaryOp(TokenType op, std::shared_ptr<Expression> right);
    bool isCompileTimeFalse(std::shared_ptr<Expression> expr);
    bool isCompileTimeTrue(std::shared_ptr<Expression> expr);
    
    // Dead code detection
    bool isUnreachableCode(std::shared_ptr<Statement> stmt);
    std::shared_ptr<Statement> eliminateDeadCode(std::shared_ptr<Statement> stmt);
    
    // Pre-analysis for reassignment detection
    void preAnalyzeReassignments(std::shared_ptr<Program> program);
    void preAnalyzeStatement(std::shared_ptr<Statement> stmt);
    void preAnalyzeExpression(std::shared_ptr<Expression> expr);
};

} // namespace AST

} // namespace Frontend
} // namespace LM

#endif // LM_AST_OPTIMIZER_HH

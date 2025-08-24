#ifndef JIT_BACKEND_H
#define JIT_BACKEND_H

#include "frontend/ast.hh"
#include <libgccjit.h>
#include <vector>
#include <memory>
#include <unordered_map>

class JitBackend {
public:
    JitBackend();
    ~JitBackend();

    void process(const std::shared_ptr<AST::Program>& program);
    void compile(const char* output_filename);

private:
    gcc_jit_context* ctxt;
    std::unordered_map<std::string, gcc_jit_function*> functions;
    std::unordered_map<std::string, gcc_jit_lvalue*> variables;

    // Visitor methods for AST nodes
    gcc_jit_rvalue* visitExpression(const std::shared_ptr<AST::Expression>& expr, gcc_jit_function* func, gcc_jit_block* block);
    void visitStatement(const std::shared_ptr<AST::Statement>& stmt, gcc_jit_function* func, gcc_jit_block* block);

    // Statement visitors
    void visitVarDeclaration(const std::shared_ptr<AST::VarDeclaration>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    void visitFunctionDeclaration(const std::shared_ptr<AST::FunctionDeclaration>& stmt);
    void visitBlockStatement(const std::shared_ptr<AST::BlockStatement>& stmt, gcc_jit_function* func, gcc_jit_block* parent_block);
    void visitIfStatement(const std::shared_ptr<AST::IfStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    void visitForStatement(const std::shared_ptr<AST::ForStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    void visitWhileStatement(const std::shared_ptr<AST::WhileStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    void visitReturnStatement(const std::shared_ptr<AST::ReturnStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    void visitPrintStatement(const std::shared_ptr<AST::PrintStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    void visitExprStatement(const std::shared_ptr<AST::ExprStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    void visitBreakStatement(const std::shared_ptr<AST::BreakStatement>& stmt, gcc_jit_block* block);
    void visitContinueStatement(const std::shared_ptr<AST::ContinueStatement>& stmt, gcc_jit_block* block);

    // Expression visitors
    gcc_jit_rvalue* visitBinaryExpr(const std::shared_ptr<AST::BinaryExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitUnaryExpr(const std::shared_ptr<AST::UnaryExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitLiteralExpr(const std::shared_ptr<AST::LiteralExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitVariableExpr(const std::shared_ptr<AST::VariableExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitCallExpr(const std::shared_ptr<AST::CallExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitAssignExpr(const std::shared_ptr<AST::AssignExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);

    // Helper methods
    gcc_jit_type* to_jit_type(const std::shared_ptr<AST::TypeAnnotation>& type);
};

#endif // JIT_BACKEND_H

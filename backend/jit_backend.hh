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
    gcc_jit_function* printf_func;
    std::unordered_map<std::string, gcc_jit_function*> functions;
    std::unordered_map<std::string, gcc_jit_lvalue*> variables;
    std::vector<std::pair<gcc_jit_block*, gcc_jit_block*>> loop_contexts;
    gcc_jit_function* strcmp_func;
    gcc_jit_function* asprintf_func;
    gcc_jit_function* malloc_func;

    // Concurrency C-API functions
    gcc_jit_function* scheduler_create_func_;
    gcc_jit_function* scheduler_destroy_func_;
    gcc_jit_function* scheduler_submit_func_;
    gcc_jit_function* scheduler_shutdown_func_;
    gcc_jit_function* thread_pool_create_func_;
    gcc_jit_function* thread_pool_destroy_func_;
    gcc_jit_function* thread_pool_start_func_;
    gcc_jit_function* thread_pool_stop_func_;
    std::unordered_map<std::string, gcc_jit_struct*> class_structs;
    std::unordered_map<std::string, std::vector<gcc_jit_field*>> class_fields;

    // Visitor methods for AST nodes
    gcc_jit_rvalue* visitExpression(const std::shared_ptr<AST::Expression>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_block* visitStatement(const std::shared_ptr<AST::Statement>& stmt, gcc_jit_function* func, gcc_jit_block* block);

    // Statement visitors
    gcc_jit_block* visitVarDeclaration(const std::shared_ptr<AST::VarDeclaration>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    void visitFunctionDeclaration(const std::shared_ptr<AST::FunctionDeclaration>& stmt);
    gcc_jit_block* visitBlockStatement(const std::shared_ptr<AST::BlockStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_block* visitIfStatement(const std::shared_ptr<AST::IfStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_block* visitForStatement(const std::shared_ptr<AST::ForStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_block* visitWhileStatement(const std::shared_ptr<AST::WhileStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_block* visitClassDeclaration(const std::shared_ptr<AST::ClassDeclaration>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_block* visitParallelStatement(const std::shared_ptr<AST::ParallelStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_block* visitConcurrentStatement(const std::shared_ptr<AST::ConcurrentStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_block* visitIterStatement(const std::shared_ptr<AST::IterStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_block* visitReturnStatement(const std::shared_ptr<AST::ReturnStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_block* visitPrintStatement(const std::shared_ptr<AST::PrintStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_block* visitExprStatement(const std::shared_ptr<AST::ExprStatement>& stmt, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_block* visitBreakStatement(const std::shared_ptr<AST::BreakStatement>& stmt, gcc_jit_block* block);
    gcc_jit_block* visitContinueStatement(const std::shared_ptr<AST::ContinueStatement>& stmt, gcc_jit_block* block);

    // Expression visitors
    gcc_jit_rvalue* visitBinaryExpr(const std::shared_ptr<AST::BinaryExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitUnaryExpr(const std::shared_ptr<AST::UnaryExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitLiteralExpr(const std::shared_ptr<AST::LiteralExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitVariableExpr(const std::shared_ptr<AST::VariableExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitCallExpr(const std::shared_ptr<AST::CallExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitAssignExpr(const std::shared_ptr<AST::AssignExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitGroupingExpr(const std::shared_ptr<AST::GroupingExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitRangeExpr(const std::shared_ptr<AST::RangeExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitInterpolatedStringExpr(const std::shared_ptr<AST::InterpolatedStringExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitMemberExpr(const std::shared_ptr<AST::MemberExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);
    gcc_jit_rvalue* visitThisExpr(const std::shared_ptr<AST::ThisExpr>& expr, gcc_jit_function* func, gcc_jit_block* block);

    // Helper methods
    gcc_jit_type* to_jit_type(const std::shared_ptr<AST::TypeAnnotation>& type);
    void print_rvalue(gcc_jit_rvalue* rval, gcc_jit_block* block, bool with_newline);
};

#endif // JIT_BACKEND_H

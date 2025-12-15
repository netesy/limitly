#ifndef LIR_GENERATOR_H
#define LIR_GENERATOR_H

#include "lir.hh"
#include "../frontend/ast.hh"
#include <unordered_map>
#include <string>
#include <memory>

namespace LIR {

class Generator {
public:
    explicit Generator();
    
    // Main entry point
    std::unique_ptr<LIR_Function> generate_program(AST::Program& program);
    std::unique_ptr<LIR_Function> generate_function(AST::FunctionDeclaration& fn);
    
    // Error handling
    bool has_errors() const;
    std::vector<std::string> get_errors() const;

private:
    // Helper methods
    Reg allocate_register();
    void set_variable_register(const std::string& name, Reg reg);
    Reg get_variable_register(const std::string& name);
    void emit_instruction(const LIR_Inst& inst);
    
    // AST node visitors
    void emit_stmt(AST::Statement& stmt);
    Reg emit_expr(AST::Expression& expr);
    
    // Specific expression handlers
    Reg emit_literal_expr(AST::LiteralExpr& expr);
    Reg emit_variable_expr(AST::VariableExpr& expr);
    Reg emit_binary_expr(AST::BinaryExpr& expr);
    Reg emit_unary_expr(AST::UnaryExpr& expr);
    Reg emit_call_expr(AST::CallExpr& expr);
    Reg emit_assign_expr(AST::AssignExpr& expr);
    Reg emit_grouping_expr(AST::GroupingExpr& expr);
    Reg emit_ternary_expr(AST::TernaryExpr& expr);
    Reg emit_index_expr(AST::IndexExpr& expr);
    Reg emit_member_expr(AST::MemberExpr& expr);
    
    // Specific statement handlers
    void emit_expr_stmt(AST::ExprStatement& stmt);
    void emit_print_stmt(AST::PrintStatement& stmt);
    void emit_var_stmt(AST::VarDeclaration& stmt);
    void emit_block_stmt(AST::BlockStatement& stmt);
    void emit_if_stmt(AST::IfStatement& stmt);
    void emit_while_stmt(AST::WhileStatement& stmt);
    void emit_for_stmt(AST::ForStatement& stmt);
    void emit_return_stmt(AST::ReturnStatement& stmt);
    void emit_func_stmt(AST::FunctionDeclaration& stmt);
    void emit_import_stmt(AST::ImportStatement& stmt);
    void emit_match_stmt(AST::MatchStatement& stmt);
    void emit_contract_stmt(AST::ContractStatement& stmt);
    void emit_comptime_stmt(AST::ComptimeStatement& stmt);
    void emit_parallel_stmt(AST::ParallelStatement& stmt);
    void emit_concurrent_stmt(AST::ConcurrentStatement& stmt);
    void emit_task_stmt(AST::TaskStatement& stmt);
    void emit_worker_stmt(AST::WorkerStatement& stmt);
    void emit_iter_stmt(AST::IterStatement& stmt);
    void emit_unsafe_stmt(AST::UnsafeStatement& stmt);
    
    // Error reporting
    void report_error(const std::string& message);
    
    // Member variables
    std::unique_ptr<LIR_Function> current_function_;
    std::unordered_map<std::string, Reg> variable_registers_;
    uint32_t next_register_;
    std::vector<std::string> errors_;
};

} // namespace LIR

#endif // LIR_GENERATOR_H

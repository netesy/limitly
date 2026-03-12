// fyra_ir_generator.hh - Direct AST to Fyra IR Code Generation
// Generates Fyra IR directly from verified AST, bypassing LIR

#pragma once

#include "../frontend/ast.hh"
#include "ir/Module.h"
#include "ir/Function.h"
#include "ir/BasicBlock.h"
#include "ir/Instruction.h"
#include "ir/Value.h"
#include "ir/Type.h"
#include "ir/IRBuilder.h"
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace LM::Backend::Fyra {

// Main Fyra IR generator
class FyraIRGenerator {
public:
    FyraIRGenerator();
    
    // Generate Fyra IR from verified AST
    std::shared_ptr<ir::Module> generate_from_ast(
        const std::shared_ptr<Frontend::AST::Program>& program);
    
    // Generate Fyra IR from a single function
    ir::Function* generate_function(
        const std::shared_ptr<Frontend::AST::FunctionDeclaration>& func_decl);
    
    // Get errors
    const std::vector<std::string>& get_errors() const { return errors_; }
    bool has_errors() const { return !errors_.empty(); }
    
private:
    std::shared_ptr<ir::Module> current_module_;
    std::unique_ptr<ir::IRBuilder> builder_;
    std::unordered_map<std::string, ir::Value*> current_locals_;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> struct_field_indices_;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> struct_field_offsets_;
    std::vector<std::string> errors_;
    int label_counter_ = 0;
    
    // Helper methods
    std::string generate_label();
    ir::Type* ast_type_to_fyra_type(const std::string& ast_type);
    
    // AST traversal methods
    ir::Value* emit_expression(const std::shared_ptr<Frontend::AST::Expression>& expr);
    void emit_statement(const std::shared_ptr<Frontend::AST::Statement>& stmt);
    
    // Expression code generation
    ir::Value* emit_binary_expr(const std::shared_ptr<Frontend::AST::BinaryExpr>& expr);
    ir::Value* emit_unary_expr(const std::shared_ptr<Frontend::AST::UnaryExpr>& expr);
    ir::Value* emit_literal_expr(const std::shared_ptr<Frontend::AST::LiteralExpr>& expr);
    ir::Value* emit_variable_expr(const std::shared_ptr<Frontend::AST::VariableExpr>& expr);
    ir::Value* emit_call_expr(const std::shared_ptr<Frontend::AST::CallExpr>& expr);
    ir::Value* emit_assign_expr(const std::shared_ptr<Frontend::AST::AssignExpr>& expr);
    ir::Value* emit_index_expr(const std::shared_ptr<Frontend::AST::IndexExpr>& expr);
    ir::Value* emit_member_expr(const std::shared_ptr<Frontend::AST::MemberExpr>& expr);
    ir::Value* emit_list_expr(const std::shared_ptr<Frontend::AST::ListExpr>& expr);
    ir::Value* emit_dict_expr(const std::shared_ptr<Frontend::AST::DictExpr>& expr);
    ir::Value* emit_range_expr(const std::shared_ptr<Frontend::AST::RangeExpr>& expr);
    
    // Statement code generation
    void emit_var_declaration(const std::shared_ptr<Frontend::AST::VarDeclaration>& decl);
    void emit_function_declaration(const std::shared_ptr<Frontend::AST::FunctionDeclaration>& decl);
    void emit_class_declaration(const std::shared_ptr<Frontend::AST::FrameDeclaration>& decl);
    void emit_block_statement(const std::shared_ptr<Frontend::AST::BlockStatement>& stmt);
    void emit_if_statement(const std::shared_ptr<Frontend::AST::IfStatement>& stmt);
    void emit_while_statement(const std::shared_ptr<Frontend::AST::WhileStatement>& stmt);
    void emit_for_statement(const std::shared_ptr<Frontend::AST::ForStatement>& stmt);
    void emit_iter_statement(const std::shared_ptr<Frontend::AST::IterStatement>& stmt);
    void emit_parallel_statement(const std::shared_ptr<Frontend::AST::ParallelStatement>& stmt);
    void emit_concurrent_statement(const std::shared_ptr<Frontend::AST::ConcurrentStatement>& stmt);
    void emit_return_statement(const std::shared_ptr<Frontend::AST::ReturnStatement>& stmt);
    void emit_print_statement(const std::shared_ptr<Frontend::AST::PrintStatement>& stmt);
};

} // namespace LM::Backend::Fyra

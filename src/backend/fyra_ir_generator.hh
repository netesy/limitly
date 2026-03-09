// fyra_ir_generator.hh - Direct AST to Fyra IR Code Generation
// Generates Fyra IR directly from verified AST, bypassing LIR

#pragma once

#include "../frontend/ast.hh"
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <sstream>

namespace LM::Backend::Fyra {

// Fyra IR value types (matching Fyra's type system)
enum class FyraType {
    I32,
    I64,
    F64,
    Bool,
    Ptr,
    Void,
    Struct,
    Array,
    Function
};

// Fyra IR instruction representation
struct FyraInstruction {
    std::string op;           // Operation name (add, sub, call, etc.)
    std::string result;       // Result register/variable
    std::vector<std::string> operands;  // Operands
    FyraType result_type;
    std::string comment;
    
    std::string to_string() const;
};

// Fyra IR function representation
struct FyraIRFunction {
    std::string name;
    std::vector<std::pair<std::string, FyraType>> parameters;
    FyraType return_type;
    std::vector<FyraInstruction> instructions;
    std::unordered_map<std::string, FyraType> local_vars;
    
    std::string to_ir_string() const;
};

// Main Fyra IR generator
class FyraIRGenerator {
public:
    FyraIRGenerator();
    
    // Generate Fyra IR from verified AST
    std::shared_ptr<FyraIRFunction> generate_from_ast(
        const std::shared_ptr<Frontend::AST::Program>& program);
    
    // Generate Fyra IR from a single function
    std::shared_ptr<FyraIRFunction> generate_function(
        const std::shared_ptr<Frontend::AST::FunctionDeclaration>& func_decl);
    
    // Get generated IR as string
    std::string get_ir_string() const;
    
    // Get errors
    const std::vector<std::string>& get_errors() const { return errors_; }
    bool has_errors() const { return !errors_.empty(); }
    
private:
    std::vector<FyraInstruction> current_instructions_;
    std::unordered_map<std::string, FyraType> current_locals_;
    std::vector<std::string> errors_;
    int temp_counter_ = 0;
    int label_counter_ = 0;
    
    // Helper methods
    std::string generate_temp_var();
    std::string generate_label();
    
    // AST traversal methods
    std::string emit_expression(const std::shared_ptr<Frontend::AST::Expression>& expr);
    void emit_statement(const std::shared_ptr<Frontend::AST::Statement>& stmt);
    
    // Expression code generation
    std::string emit_binary_expr(const std::shared_ptr<Frontend::AST::BinaryExpr>& expr);
    std::string emit_unary_expr(const std::shared_ptr<Frontend::AST::UnaryExpr>& expr);
    std::string emit_literal_expr(const std::shared_ptr<Frontend::AST::LiteralExpr>& expr);
    std::string emit_variable_expr(const std::shared_ptr<Frontend::AST::VariableExpr>& expr);
    std::string emit_call_expr(const std::shared_ptr<Frontend::AST::CallExpr>& expr);
    std::string emit_assign_expr(const std::shared_ptr<Frontend::AST::AssignExpr>& expr);
    std::string emit_index_expr(const std::shared_ptr<Frontend::AST::IndexExpr>& expr);
    std::string emit_member_expr(const std::shared_ptr<Frontend::AST::MemberExpr>& expr);
    std::string emit_list_expr(const std::shared_ptr<Frontend::AST::ListExpr>& expr);
    std::string emit_dict_expr(const std::shared_ptr<Frontend::AST::DictExpr>& expr);
    std::string emit_range_expr(const std::shared_ptr<Frontend::AST::RangeExpr>& expr);
    
    // Statement code generation
    void emit_var_declaration(const std::shared_ptr<Frontend::AST::VarDeclaration>& decl);
    void emit_function_declaration(const std::shared_ptr<Frontend::AST::FunctionDeclaration>& decl);
    void emit_block_statement(const std::shared_ptr<Frontend::AST::BlockStatement>& stmt);
    void emit_if_statement(const std::shared_ptr<Frontend::AST::IfStatement>& stmt);
    void emit_while_statement(const std::shared_ptr<Frontend::AST::WhileStatement>& stmt);
    void emit_for_statement(const std::shared_ptr<Frontend::AST::ForStatement>& stmt);
    void emit_iter_statement(const std::shared_ptr<Frontend::AST::IterStatement>& stmt);
    void emit_return_statement(const std::shared_ptr<Frontend::AST::ReturnStatement>& stmt);
    void emit_print_statement(const std::shared_ptr<Frontend::AST::PrintStatement>& stmt);
    void emit_parallel_statement(const std::shared_ptr<Frontend::AST::ParallelStatement>& stmt);
    void emit_concurrent_statement(const std::shared_ptr<Frontend::AST::ConcurrentStatement>& stmt);
    
    // Type conversion
    FyraType ast_type_to_fyra_type(const std::string& ast_type);
    std::string fyra_type_to_string(FyraType type);
    
    // Instruction emission
    void emit_instruction(const std::string& op, const std::string& result,
                         const std::vector<std::string>& operands,
                         FyraType result_type, const std::string& comment = "");
};

} // namespace LM::Backend::Fyra

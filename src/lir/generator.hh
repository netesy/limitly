#ifndef LIR_GENERATOR_H
#define LIR_GENERATOR_H

#include "lir.hh"
#include "../backend/memory.hh"
#include "../frontend/ast.hh"
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <variant>

//All semantic decisions about functions, classes, and variables are made in the generator. JIT only sees registers, memory offsets, and low-level types.
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
    // Symbol collection (Pass 0)
    void collect_function_signatures(AST::Program& program);
    void collect_function_signature(AST::FunctionDeclaration& stmt);
    
    // Function body lowering (Pass 1)
    void lower_function_bodies(AST::Program& program);
    void lower_function_body(AST::FunctionDeclaration& stmt);
    
    // Helper methods
    Reg allocate_register();
    void enter_scope();
    void exit_scope();
    void bind_variable(const std::string& name, Reg reg);
    void update_variable_binding(const std::string& name, Reg reg);
    Reg resolve_variable(const std::string& name);
    void set_register_type(Reg reg, TypePtr type);
    TypePtr get_register_type(Reg reg) const;
    void emit_instruction(const LIR_Inst& inst);
    
    // Register value management
    void set_register_value(Reg reg, ValuePtr value);
    ValuePtr get_register_value(Reg reg);
    
    // Type inference helpers
    TypePtr get_promoted_numeric_type(TypePtr left_type, TypePtr right_type);
    bool is_signed_integer_type(TypePtr type);
    TypePtr get_wider_integer_type(TypePtr left_type, TypePtr right_type);
    TypePtr get_unsigned_version(TypePtr type);
    TypePtr get_best_integer_type(const std::string& value_str, bool prefer_signed = true);
    bool is_numeric_string(const std::string& str);
    bool types_match(TypePtr type1, TypePtr type2);
    int get_type_rank(TypePtr type);
    
    // CFG building methods
    void start_cfg_build();
    void finish_cfg_build();
    void remove_unreachable_blocks();
    void flatten_cfg_to_instructions();
    LIR_BasicBlock* create_basic_block(const std::string& label = "");
    void set_current_block(LIR_BasicBlock* block);
    void add_block_edge(LIR_BasicBlock* from, LIR_BasicBlock* to);
    LIR_BasicBlock* get_current_block() const;
    
    // Loop management methods
    uint32_t generate_label();
    void enter_loop();
    void exit_loop();
    void set_loop_labels(uint32_t start_label, uint32_t end_label, uint32_t continue_label);
    uint32_t get_break_label();
    uint32_t get_continue_label();
    bool in_loop() const;
    
    // Memory management methods
    void enter_memory_region();
    void exit_memory_region();
    void* allocate_in_region(size_t size, size_t alignment = alignof(std::max_align_t));
    template<typename T, typename... Args>
    T* create_object(Args&&... args);
    void cleanup_memory();
    
    // AST node visitors
    void emit_stmt(AST::Statement& stmt);
    Reg emit_expr(AST::Expression& expr);
    
    // Specific expression handlers
    Reg emit_literal_expr(AST::LiteralExpr& expr, TypePtr expected_type = nullptr);
    Reg emit_variable_expr(AST::VariableExpr& expr);
    Reg emit_interpolated_string_expr(AST::InterpolatedStringExpr& expr);
    Reg emit_binary_expr(AST::BinaryExpr& expr);
    Reg emit_unary_expr(AST::UnaryExpr& expr);
    Reg emit_grouping_expr(AST::GroupingExpr& expr);
    Reg emit_call_expr(AST::CallExpr& expr);
    Reg emit_assign_expr(AST::AssignExpr& expr);
    Reg emit_list_expr(AST::ListExpr& expr);
    Reg emit_call_closure_expr(AST::CallClosureExpr& expr);
    
    // Loop helper methods
    void emit_traditional_for_loop(AST::ForStatement& stmt);
    Reg emit_ternary_expr(AST::TernaryExpr& expr);
    Reg emit_index_expr(AST::IndexExpr& expr);
    Reg emit_member_expr(AST::MemberExpr& expr);
    Reg emit_tuple_expr(AST::TupleExpr& expr);
    Reg emit_dict_expr(AST::DictExpr& expr);
    Reg emit_range_expr(AST::RangeExpr& expr);
    Reg emit_lambda_expr(AST::LambdaExpr& expr);
    
    // Specific statement handlers
    void emit_expr_stmt(AST::ExprStatement& stmt);
    void emit_print_stmt(AST::PrintStatement& stmt);
    void emit_var_stmt(AST::VarDeclaration& stmt);
    void emit_block_stmt(AST::BlockStatement& stmt);
    void emit_if_stmt(AST::IfStatement& stmt);
    void emit_if_stmt_cfg(AST::IfStatement& stmt);
    void emit_if_stmt_linear(AST::IfStatement& stmt);
    void emit_while_stmt(AST::WhileStatement& stmt);
    void emit_while_stmt_cfg(AST::WhileStatement& stmt);
    void emit_while_stmt_linear(AST::WhileStatement& stmt);
    void emit_for_stmt(AST::ForStatement& stmt);
    void emit_for_stmt_cfg(AST::ForStatement& stmt);
    void emit_for_stmt_linear(AST::ForStatement& stmt);
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
    void emit_break_stmt(AST::BreakStatement& stmt);
    void emit_continue_stmt(AST::ContinueStatement& stmt);
    void emit_unsafe_stmt(AST::UnsafeStatement& stmt);
    
    // Error reporting
    void report_error(const std::string& message);
    
    // Member variables
    struct Scope {
        std::unordered_map<std::string, Reg> vars;
        MemoryManager<>::Region* memory_region = nullptr;
    };

    struct LoopContext {
        uint32_t start_label;
        uint32_t end_label;
        uint32_t continue_label;
    };

    struct CFGContext {
        LIR_BasicBlock* current_block = nullptr;
        LIR_BasicBlock* entry_block = nullptr;
        LIR_BasicBlock* exit_block = nullptr;
        bool building_cfg = false;
    };

    std::unique_ptr<LIR_Function> current_function_;
    std::vector<Scope> scope_stack_;
    std::vector<LoopContext> loop_stack_;
    CFGContext cfg_context_;
    uint32_t next_register_ = 0;
    uint32_t next_label_ = 0;
    std::unordered_map<Reg, TypePtr> register_types_;
    std::unordered_map<Reg, ValuePtr> register_values_;
    std::vector<std::string> errors_;
    
    // Function symbol table for visibility control
    struct FunctionInfo {
        std::string name;
        std::unique_ptr<LIR_Function> lir_function;  // Separate LIR function
        AST::VisibilityLevel visibility;
        size_t param_count;
        size_t optional_param_count;
        bool has_closure;
    };
    std::unordered_map<std::string, FunctionInfo> function_table_;
    
    // Memory management
    MemoryManager<> memory_manager_;
    MemoryManager<>::Region* current_memory_region_ = nullptr;
    
    // Helper methods
    std::shared_ptr<Type> convert_ast_type_to_lir_type(const std::shared_ptr<AST::TypeAnnotation>& ast_type);
};

} // namespace LIR

#endif // LIR_GENERATOR_H

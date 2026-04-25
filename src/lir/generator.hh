#ifndef LIR_GENERATOR_H
#define LIR_GENERATOR_H

#include "lir.hh"
#include "optimizer.hh"
#include "metrics.hh"
#include "../memory/memory.hh"
#include "../frontend/ast.hh"
#include "../frontend/type_checker.hh"
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <variant>

namespace LM {
namespace LIR {

class Generator {
public:
    explicit Generator();
    
    // Main entry point - now takes TypeCheckResult instead of raw LM::Frontend::AST
    std::unique_ptr<LIR_Function> generate_program(const LM::Frontend::TypeCheckResult& type_check_result);
    void generate_function(LM::Frontend::AST::FunctionDeclaration& fn);
    
    // Set import aliases from type checker
    void set_import_aliases(const std::unordered_map<std::string, std::string>& aliases) {
        import_aliases_ = aliases;
    }
    
    // Set registered modules from type checker
    void set_registered_modules(const std::unordered_map<std::string, LM::Frontend::ModuleInfo>& modules) {
        registered_modules_ = modules;
    }
    
    // Optimization control
    static void set_optimization_enabled(bool enabled) {
        optimization_enabled_ = enabled;
    }
    
    static bool is_optimization_enabled() {
        return optimization_enabled_;
    }
    
    // Debug output control
    static void set_show_optimization_debug(bool show) {
        show_optimization_debug_ = show;
    }
    
    static bool should_show_optimization_debug() {
        return show_optimization_debug_;
    }
    
    // Error handling
    bool has_errors() const;
    std::vector<std::string> get_errors() const;
    
    // Enhanced error handling - access error information
    struct ErrorInfo {
        std::string errorType;
        std::string message;
    };
    const std::unordered_map<Reg, ErrorInfo>& get_error_info_table() const { return error_info_table_; }

private:
    static bool optimization_enabled_;
    static bool show_optimization_debug_;
    
    // Function body lowering (Pass 1)
    void lower_function_bodies(const LM::Frontend::TypeCheckResult& type_check_result);
    void lower_function_body(LM::Frontend::AST::FunctionDeclaration& stmt);

    // Symbol collection (Pass 0)
    void collect_function_signatures(const LM::Frontend::TypeCheckResult& type_check_result);
    void collect_function_signature(LM::Frontend::AST::FunctionDeclaration& stmt, const std::string& name_override = "");
    void lower_trait_declaration(LM::Frontend::AST::TraitDeclaration& trait_decl);
    void lower_trait_method(const std::string& trait_name, LM::Frontend::AST::FunctionDeclaration& method);
    void lower_frame_methods(LM::Frontend::AST::FrameDeclaration& frame_decl);
    void lower_frame_method(const std::string& frame_name, LM::Frontend::AST::FrameMethod& method);
    void lower_frame_init_method(const std::string& frame_name, LM::Frontend::AST::FrameMethod& init_method);
    void lower_frame_deinit_method(const std::string& frame_name, LM::Frontend::AST::FrameMethod& deinit_method);
    void lower_task_body(LM::Frontend::AST::TaskStatement& stmt);
    void lower_worker_body(LM::Frontend::AST::WorkerStatement& stmt);
    void lower_task_bodies_recursive(const std::vector<std::shared_ptr<LM::Frontend::AST::Statement>>& statements);
    
    // Helper methods
    Reg allocate_register();
    void enter_scope();
    void exit_scope();
    void bind_variable(const std::string& name, Reg reg);
    void update_variable_binding(const std::string& name, Reg reg);
    Reg resolve_variable(const std::string& name);
    void set_register_type(Reg reg, TypePtr type);
    TypePtr get_register_type(Reg reg) const;
    
    // New simplified type methods
    void set_register_abi_type(Reg reg, Type abi_type);
    void set_register_language_type(Reg reg, TypePtr lang_type);
    Type get_register_abi_type(Reg reg) const;
    TypePtr get_register_language_type(Reg reg) const;
    
    // Type conversion helpers
    Type language_type_to_abi_type(TypePtr lang_type);
    Type get_expression_abi_type(LM::Frontend::AST::Expression& expr);
    
    void emit_instruction(const LIR_Inst& inst);
    void emit_typed_instruction(const LIR_Inst& inst);
    
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
    void ensure_all_blocks_terminated();
    void finish_cfg_build();
    void remove_unreachable_blocks();
    void flatten_cfg_to_instructions();
    bool validate_cfg(); // CFG validator
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
    
    // LM::Frontend::AST node visitors
    void emit_stmt(LM::Frontend::AST::Statement& stmt);
    Reg emit_expr(LM::Frontend::AST::Expression& expr);
    
    // Specific expression handlers
    Reg emit_literal_expr(LM::Frontend::AST::LiteralExpr& expr, TypePtr expected_type = nullptr);
    Reg emit_variable_expr(LM::Frontend::AST::VariableExpr& expr);
    Reg emit_interpolated_string_expr(LM::Frontend::AST::InterpolatedStringExpr& expr);
    Reg emit_binary_expr(LM::Frontend::AST::BinaryExpr& expr);
    Reg emit_unary_expr(LM::Frontend::AST::UnaryExpr& expr);
    Reg emit_grouping_expr(LM::Frontend::AST::GroupingExpr& expr);
    Reg emit_call_expr(LM::Frontend::AST::CallExpr& expr);
    Reg emit_assign_expr(LM::Frontend::AST::AssignExpr& expr);
    Reg emit_list_expr(LM::Frontend::AST::ListExpr& expr);
    Reg emit_call_closure_expr(LM::Frontend::AST::CallClosureExpr& expr);
    
    // Loop helper methods
    void emit_traditional_for_loop(LM::Frontend::AST::ForStatement& stmt);
    Reg emit_ternary_expr(LM::Frontend::AST::TernaryExpr& expr);
    Reg emit_index_expr(LM::Frontend::AST::IndexExpr& expr);
    Reg emit_member_expr(LM::Frontend::AST::MemberExpr& expr);
    Reg emit_tuple_expr(LM::Frontend::AST::TupleExpr& expr);
    Reg emit_dict_expr(LM::Frontend::AST::DictExpr& expr);
    Reg emit_range_expr(LM::Frontend::AST::RangeExpr& expr);
    Reg emit_lambda_expr(LM::Frontend::AST::LambdaExpr& expr);
    Reg emit_error_construct_expr(LM::Frontend::AST::ErrorConstructExpr& expr);
    Reg emit_ok_construct_expr(LM::Frontend::AST::OkConstructExpr& expr);
    Reg emit_fallible_expr(LM::Frontend::AST::FallibleExpr& expr);
    
    // Channel operation handlers
    Reg emit_channel_offer_expr(LM::Frontend::AST::ChannelOfferExpr& expr);
    Reg emit_channel_poll_expr(LM::Frontend::AST::ChannelPollExpr& expr);
    Reg emit_channel_send_expr(LM::Frontend::AST::ChannelSendExpr& expr);
    Reg emit_channel_recv_expr(LM::Frontend::AST::ChannelRecvExpr& expr);
    
    // Frame system expression handlers
    Reg emit_this_expr(LM::Frontend::AST::ThisExpr& expr);
    
    // Frame system expression handlers
    Reg emit_frame_instantiation_expr(LM::Frontend::AST::FrameInstantiationExpr& expr);
    
    // Specific statement handlers
    void emit_expr_stmt(LM::Frontend::AST::ExprStatement& stmt);
    void emit_print_stmt(LM::Frontend::AST::PrintStatement& stmt);
    void emit_print_value(Reg value);  // Helper for printing single values
    void emit_var_stmt(LM::Frontend::AST::VarDeclaration& stmt);
    void emit_destructuring_var_stmt(LM::Frontend::AST::DestructuringDeclaration& stmt);
    void emit_block_stmt(LM::Frontend::AST::BlockStatement& stmt);
    void emit_if_stmt(LM::Frontend::AST::IfStatement& stmt);
    void emit_if_stmt_cfg(LM::Frontend::AST::IfStatement& stmt);
    void emit_if_stmt_cfg_with_end(LM::Frontend::AST::IfStatement& stmt, LIR_BasicBlock* outer_end_block);
    void emit_if_stmt_linear(LM::Frontend::AST::IfStatement& stmt);
    void emit_while_stmt(LM::Frontend::AST::WhileStatement& stmt);
    void emit_while_stmt_cfg(LM::Frontend::AST::WhileStatement& stmt);
    void emit_while_stmt_linear(LM::Frontend::AST::WhileStatement& stmt);
    void emit_for_stmt(LM::Frontend::AST::ForStatement& stmt);
    void emit_for_stmt_cfg(LM::Frontend::AST::ForStatement& stmt);
    void emit_for_stmt_linear(LM::Frontend::AST::ForStatement& stmt);
    void emit_return_stmt(LM::Frontend::AST::ReturnStatement& stmt);
    void emit_func_stmt(LM::Frontend::AST::FunctionDeclaration& stmt);
    void emit_import_stmt(LM::Frontend::AST::ImportStatement& stmt);
    void emit_contract_stmt(LM::Frontend::AST::ContractStatement& stmt);
    void emit_comptime_stmt(LM::Frontend::AST::ComptimeStatement& stmt);
    void emit_parallel_stmt(LM::Frontend::AST::ParallelStatement& stmt);
    void emit_concurrent_stmt(LM::Frontend::AST::ConcurrentStatement& stmt);
    void emit_task_init_and_step(LM::Frontend::AST::TaskStatement& task, size_t task_id, Reg contexts_reg, Reg channel_reg, Reg counter_reg, int64_t loop_var_value = 0);
    void emit_task_stmt(LM::Frontend::AST::TaskStatement& stmt);
    void create_and_register_task_function(const std::string& task_name, LM::Frontend::AST::TaskStatement* task_stmt, int64_t loop_value);
    void create_and_register_worker_function(const std::string& worker_name, LM::Frontend::AST::WorkerStatement* worker_stmt);
    void create_parallel_work_item(const std::string& work_item_name, std::shared_ptr<LM::Frontend::AST::Statement> stmt);
    void collect_variables_from_statement(LM::Frontend::AST::Statement& stmt, std::set<std::string>& variables);
    void collect_variables_from_expression(LM::Frontend::AST::Expression& expr, std::set<std::string>& variables);
    void emit_concurrent_worker_init(LM::Frontend::AST::WorkerStatement& worker, size_t worker_id, Reg scheduler_reg, Reg channel_reg);
    void emit_worker_stmt(LM::Frontend::AST::WorkerStatement& stmt);
    void emit_iter_stmt(LM::Frontend::AST::IterStatement& stmt);
    void emit_dict_iter_stmt(LM::Frontend::AST::IterStatement& stmt, LM::Frontend::AST::DictExpr& dict_expr);
    void emit_list_iter_stmt(LM::Frontend::AST::IterStatement& stmt, LM::Frontend::AST::ListExpr& list_expr);
    void emit_tuple_iter_stmt(LM::Frontend::AST::IterStatement& stmt, LM::Frontend::AST::TupleExpr& tuple_expr);
    void emit_dict_var_iter_stmt(LM::Frontend::AST::IterStatement& stmt, Reg dict_reg);
    void emit_list_var_iter_stmt(LM::Frontend::AST::IterStatement& stmt, Reg list_reg);
    void emit_tuple_var_iter_stmt(LM::Frontend::AST::IterStatement& stmt, Reg tuple_reg, int64_t tuple_len);
    void emit_break_stmt(LM::Frontend::AST::BreakStatement& stmt);
    void emit_continue_stmt(LM::Frontend::AST::ContinueStatement& stmt);
    void emit_unsafe_stmt(LM::Frontend::AST::UnsafeStatement& stmt);
    void emit_trait_stmt(LM::Frontend::AST::TraitDeclaration& stmt);
    void emit_frame_stmt(LM::Frontend::AST::FrameDeclaration& stmt);
    void emit_match_stmt(LM::Frontend::AST::MatchStatement& stmt);
    void emit_module_stmt(LM::Frontend::AST::ModuleDeclaration& stmt);
    
    // Helper functions
    std::optional<ValuePtr> evaluate_constant_expression(std::shared_ptr<LM::Frontend::AST::Expression> expr);
    uint64_t parse_timeout(const std::string& timeout_str);
    uint64_t parse_grace_period(const std::string& grace_str);
    
    // Error reporting
    void report_error(const std::string& message);
    
    // Member variables
    struct Scope {
        std::unordered_map<std::string, Reg> vars;
        std::vector<std::pair<std::string, Reg>> frame_instances;  // frame_name -> register for deinit tracking
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
    
    // Task counter for generating unique task function names
    size_t task_counter_ = 0;
    // Worker counter for generating unique worker function names
    size_t worker_counter_ = 0;
    uint32_t next_register_ = 0;
    uint32_t next_label_ = 0;
    std::map<std::string, TypePtr> variable_types_;
    std::shared_ptr<TypeSystem> type_system_;
    std::string current_function_name_;
    std::set<std::string> function_names_;
    std::map<std::string, std::shared_ptr<LM::Frontend::AST::Expression>> constant_expressions_;
    std::map<std::string, int64_t> constant_values_;
    std::map<std::string, Reg> variable_registers_;
    std::map<std::string, Reg> channel_registers_;
    std::map<std::string, uint32_t> parallel_block_cell_ids_;
    std::map<std::string, Reg> shared_cell_registers_;
    std::string current_concurrent_block_id_;
    std::map<std::string, uint64_t> task_counters_;
    bool scheduler_initialized_ = false;
    std::unordered_map<Reg, TypePtr> register_types_;
    std::unordered_map<Reg, Type> register_abi_types_;
    std::unordered_map<Reg, TypePtr> register_language_types_;
    std::unordered_map<Reg, ValuePtr> register_values_;
    std::vector<std::string> errors_;
    
    // Error information table for enhanced error handling
    std::unordered_map<Reg, ErrorInfo> error_info_table_;
    
    // Else block context for handling return statements in ? else {} blocks
    struct ElseBlockContext {
        bool in_else_block = false;
        Reg result_register = UINT32_MAX;  // Register to store the result value
    };
    ElseBlockContext else_context_;
    
    // Function symbol table for visibility control
    struct FunctionInfo {
        std::string name;
        std::unique_ptr<LIR_Function> lir_function;  // Separate LIR function
        LM::Frontend::AST::VisibilityLevel visibility;
        size_t param_count;
        size_t optional_param_count;
        bool has_closure;
    };
    std::unordered_map<std::string, FunctionInfo> function_table_;
    std::unordered_map<std::string, std::unique_ptr<LIR_Function>> task_functions_;
    
    // Smart module system with qualified symbol table
    struct ModuleSymbolInfo {
        std::string qualified_name;  // module::symbol
        std::string module_name;
        std::string symbol_name;
        LM::Frontend::AST::VisibilityLevel visibility;
        size_t param_count = 0;
        bool is_function = false;
        bool is_variable = false;
    };
    std::unordered_map<std::string, ModuleSymbolInfo> module_symbol_table_;
    
    // Import alias mapping for current scope
    std::unordered_map<std::string, std::string> import_aliases_;
    std::unordered_map<std::string, LM::Frontend::ModuleInfo> registered_modules_;
    std::string current_module_ = "";  // Current module context
    
    Reg this_register_ = UINT32_MAX;  // Register holding 'this' pointer in methods
    
    // Concurrency context tracking
    int concurrency_nesting_level_ = 0;
    void enter_concurrency_context() { concurrency_nesting_level_++; }
    void exit_concurrency_context() { concurrency_nesting_level_--; }
    bool is_in_concurrency_context() const { return concurrency_nesting_level_ > 0; }

    // Frame system support (modern OOP)
    struct FrameInfo {
        std::string name;
        std::vector<std::pair<std::string, TypePtr>> fields;  // field name -> type
        std::unordered_map<std::string, LM::Frontend::AST::VisibilityLevel> field_visibilities;
        std::vector<std::string> method_names;                // ordered method names
        std::unordered_map<std::string, size_t> field_offsets; // field name -> offset
        std::unordered_map<std::string, size_t> method_indices; // method name -> index
        std::vector<std::string> implements;                  // trait names
        bool has_init = false;
        bool has_deinit = false;
        size_t total_field_size = 0;
        std::shared_ptr<LM::Frontend::AST::FrameDeclaration> declaration;
    };
    std::unordered_map<std::string, FrameInfo> frame_table_;

    struct TraitInfo {
        std::string name;
        std::vector<std::string> extends;
        std::shared_ptr<LM::Frontend::AST::TraitDeclaration> declaration;
    };
    std::unordered_map<std::string, TraitInfo> trait_table_;
    Reg frame_this_register_ = UINT32_MAX;  // Register holding 'this' pointer in frame methods
    
    
    // Channel context for concurrent blocks
    Reg channel_context_ = UINT32_MAX;
    
   
    // Variable capture analysis for concurrent statements
    void find_accessed_variables_in_concurrent(LM::Frontend::AST::ConcurrentStatement& stmt, std::set<std::string>& accessed_variables);
    void find_accessed_variables_recursive(const std::vector<std::shared_ptr<LM::Frontend::AST::Statement>>& statements, std::set<std::string>& accessed_variables);
    void find_accessed_variables_in_expr(const LM::Frontend::AST::Expression& expr, std::set<std::string>& accessed_variables);
    
    // Helper methods
    std::shared_ptr<::Type> convert_ast_type_to_lir_type(const std::shared_ptr<LM::Frontend::AST::TypeAnnotation>& ast_type);
    
    
    // Frame system helper methods
    bool is_visible(LM::Frontend::AST::VisibilityLevel level, const std::string& frame_name);
    void collect_trait_signatures(LM::Frontend::AST::Program& program);
    void collect_trait_signature(std::shared_ptr<LM::Frontend::AST::TraitDeclaration> trait_decl, const std::string& name_override = "");
    void collect_frame_signatures(LM::Frontend::AST::Program& program);
    void collect_frame_signature(std::shared_ptr<LM::Frontend::AST::FrameDeclaration> frame_decl, const std::string& name_override = "");
    void calculate_frame_layout(FrameInfo& frame_info);
    size_t get_frame_field_offset(const std::string& frame_name, const std::string& field_name);
    size_t get_frame_method_index(const std::string& frame_name, const std::string& method_name);
    
    // Smart module system helper methods
    void collect_module_signatures(LM::Frontend::AST::Program& program);
    void collect_module_declaration(LM::Frontend::AST::ModuleDeclaration& module_decl);
    void register_module_symbol(const std::string& module_name, const std::string& symbol_name, 
                                LM::Frontend::AST::VisibilityLevel visibility, bool is_function = false, size_t param_count = 0);
    ModuleSymbolInfo* resolve_module_symbol(const std::string& qualified_name);
    bool can_access_module_symbol(const ModuleSymbolInfo& symbol, const std::string& from_module = "");
};

} // namespace LIR
} // namespace LM

#endif // LIR_GENERATOR_H

#pragma once

#include "../backend/types.hh"
#include "../frontend/ast.hh"
#include "../lir/lir.hh"
#include "../memory/model.hh"
#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

// =============================================================================
// TYPE CHECKER - Runs BEFORE LIR generation
// Implements the mental model: AST -> Typed AST (with memory safety) -> LIR (typed) -> JIT
// =============================================================================

namespace LM {
namespace Frontend {

// Module information structure (public for use in TypeCheckResult)
struct ModuleInfo {
    std::string name;
    std::unordered_map<std::string, TypePtr> symbols;
};

class TypeChecker {
private:
    TypeSystem& type_system;
    std::vector<std::string> errors;
    
    // Symbol table for variable types
    std::unordered_map<std::string, TypePtr> variable_types;
    
    // Track undefined symbols to suppress cascading errors
    std::unordered_set<std::string> undefined_symbols;
    
    // Memory safety tracking
    struct VariableInfo {
        TypePtr type;
        std::string memory_state;  // "owned", "moved", "dropped", "borrowed"
        std::size_t region_id;
        std::size_t alloc_id;
    };
    std::unordered_map<std::string, VariableInfo> variable_memory_info;
    
    // Region and generation tracking for compile-time memory model
    std::size_t current_region_id = 0;
    std::size_t current_generation = 0;
    std::size_t next_alloc_id = 0;
    std::vector<std::size_t> region_stack;
    
    // Function signatures
    struct FunctionSignature {
        std::string name;
        std::vector<TypePtr> param_types;
        TypePtr return_type;
        std::shared_ptr<LM::Frontend::AST::FunctionDeclaration> declaration;
        bool can_fail = false;
        std::vector<std::string> error_types;
        std::vector<bool> optional_params;
        std::vector<bool> has_default_values;
        
        FunctionSignature() = default;
        FunctionSignature(const std::string& n, const std::vector<TypePtr>& params, TypePtr ret, 
                       bool fail = false, const std::vector<std::string>& errors = {}, 
                       int line = 0, const std::vector<bool>& opt = {}, 
                       const std::vector<bool>& defaults = {})
            : name(n), param_types(params), return_type(ret), can_fail(fail), 
              error_types(errors), optional_params(opt), has_default_values(defaults) {}
    };
    std::unordered_map<std::string, FunctionSignature> function_signatures;
    
    // Frame declarations tracking
    struct FrameInfo {
        std::string name;
        std::vector<std::pair<std::string, TypePtr>> fields;  // field name -> type
        std::vector<std::pair<std::string, bool>> field_has_default;  // field name -> has default
        std::shared_ptr<LM::Frontend::AST::FrameDeclaration> declaration;
    };
    std::unordered_map<std::string, FrameInfo> frame_declarations;
    
    // Trait declarations tracking
    struct TraitInfo {
        std::string name;
        std::vector<std::string> extends;
        std::shared_ptr<LM::Frontend::AST::TraitDeclaration> declaration;
    };
    std::unordered_map<std::string, TraitInfo> trait_declarations;

    std::unordered_map<std::string, ModuleInfo> registered_modules;
    std::unordered_map<std::string, std::string> import_aliases;
    std::string current_module_name;

    // Current context
    std::shared_ptr<LM::Frontend::AST::FunctionDeclaration> current_function = nullptr;
    std::shared_ptr<LM::Frontend::AST::FrameDeclaration> current_frame = nullptr;
    TypePtr current_return_type = nullptr;
    bool in_loop = false;
    
    // Source context for error reporting
    std::string current_source;
    std::string current_file_path;
    
    // Linear type reference system
    struct LinearTypeInfo {
        bool is_moved = false;
        int move_line = 0;
        int access_count = 0;
        std::size_t current_generation = 0;
        std::set<std::string> references;
        std::set<std::string> mutable_references;  // Track mutable aliases separately
    };
    
    struct ReferenceInfo {
        std::string target_linear_var;
        int creation_line = 0;
        bool is_valid = true;
        std::size_t created_generation = 0;
        bool is_mutable = false;
        int creation_scope = 0;  // Track scope level where reference was created
    };
    
    std::unordered_map<std::string, LinearTypeInfo> linear_types;
    std::unordered_map<std::string, ReferenceInfo> references;
    
    // Scope tracking for lifetime analysis
    int current_scope_level = 0;
    
    // Map to track which enums define which variants
    std::unordered_map<std::string, std::vector<TypePtr>> variant_owners;
    
    std::shared_ptr<LM::Frontend::AST::Program> current_program_ = nullptr;
    
public:
    explicit TypeChecker(TypeSystem& ts) : type_system(ts) {}
    
    // Main entry point - type check entire program
    bool check_program(std::shared_ptr<LM::Frontend::AST::Program> program);
    
    // Get errors after checking
    const std::vector<std::string>& get_errors() const { return errors; }
    bool has_errors() const { return !errors.empty(); }
    
    // Get the type system (for LIR generator)
    TypeSystem& get_type_system() { return type_system; }
    
    // Get import aliases (for LIR generator)
    const std::unordered_map<std::string, std::string>& get_import_aliases() const { return import_aliases; }
    
    // Get registered modules (for LIR generator)
    const std::unordered_map<std::string, ModuleInfo>& get_registered_modules() const { return registered_modules; }
    
    // Set source context for error reporting
    void set_source_context(const std::string& source, const std::string& file_path) {
        current_source = source;
        current_file_path = file_path;
    }
    
    // Register a builtin function
    void register_builtin_function(const std::string& name, 
                                  const std::vector<TypePtr>& param_types,
                                  TypePtr return_type);
    
private:
    // Enhanced error reporting
    void add_error(const std::string& message, int line = 0);
    void add_error(const std::string& message, int line, int column, const std::string& context, 
                 const std::string& lexeme = "", const std::string& expected_value = "");
    void add_type_error(const std::string& expected, const std::string& found, int line = 0);
    std::string get_code_context(int line);
    void check_assert_call(const std::shared_ptr<LM::Frontend::AST::CallExpr>& expr);
    
    // Linear type reference methods
    void check_linear_type_access(const std::string& var_name, int line);
    void create_reference(const std::string& linear_var, const std::string& ref_var, int line, bool is_mutable = false);
    void move_linear_type(const std::string& var_name, int line);
    void check_reference_validity(const std::string& ref_name, int line);
    
    // Mutable aliasing detection
    void check_mutable_aliasing(const std::string& linear_var, const std::string& ref_var, bool is_mutable, int line);
    
    // Lifetime analysis
    void check_scope_escape(const std::string& ref_name, int target_scope, int line);
    
    // Symbol table management
    void enter_scope();
    void exit_scope();
    void declare_variable(const std::string& name, TypePtr type);
    TypePtr lookup_variable(const std::string& name);
    
    // Memory safety methods
    void enter_memory_region();
    void exit_memory_region();
    void declare_variable_memory(const std::string& name, TypePtr type);
    void check_variable_use(const std::string& name, int line);
    void check_variable_move(const std::string& name);
    void check_variable_drop(const std::string& name);
    void check_borrow_safety(const std::string& var_name);
    void check_escape_analysis(const std::string& var_name, const std::string& target_context);
    void check_memory_leaks(int line);
    void check_use_after_free(const std::string& name, int line);
    void check_dangling_pointer(const std::string& name, int line);
    void check_double_free(const std::string& name, int line);
    void check_multiple_owners(const std::string& name, int line);
    void check_buffer_overflow(const std::string& array_name, const std::string& index_expr, int line);
    void check_uninitialized_use(const std::string& name, int line);
    void check_invalid_type(const std::string& var_name, TypePtr expected_type, TypePtr actual_type, int line);
    void check_misalignment(const std::string& ptr_name, int line);
    void check_heap_corruption(const std::string& operation, int line);
    void check_race_condition(const std::string& shared_var, int line);
    bool is_variable_alive(const std::string& name);
    void mark_variable_moved(const std::string& name);
    void mark_variable_dropped(const std::string& name);
    void mark_variable_initialized(const std::string& name);
    
    // Type checking methods
    TypePtr check_expression(std::shared_ptr<LM::Frontend::AST::Expression> expr, TypePtr expected_type = nullptr);
    TypePtr check_expression_with_expected_type(std::shared_ptr<LM::Frontend::AST::Expression> expr, TypePtr expected_type);
    TypePtr check_statement(std::shared_ptr<LM::Frontend::AST::Statement> stmt);
    TypePtr check_function_declaration(std::shared_ptr<LM::Frontend::AST::FunctionDeclaration> func);
    TypePtr check_var_declaration(std::shared_ptr<LM::Frontend::AST::VarDeclaration> var_decl);
    TypePtr check_destructuring_declaration(std::shared_ptr<LM::Frontend::AST::DestructuringDeclaration> dest_decl);
    TypePtr check_type_declaration(std::shared_ptr<LM::Frontend::AST::TypeDeclaration> type_decl);
    TypePtr check_block_statement(std::shared_ptr<LM::Frontend::AST::BlockStatement> block);
    TypePtr check_if_statement(std::shared_ptr<LM::Frontend::AST::IfStatement> if_stmt);
    TypePtr check_while_statement(std::shared_ptr<LM::Frontend::AST::WhileStatement> while_stmt);
    TypePtr check_for_statement(std::shared_ptr<LM::Frontend::AST::ForStatement> for_stmt);
    TypePtr check_iter_statement(std::shared_ptr<LM::Frontend::AST::IterStatement> iter_stmt);
    TypePtr check_parallel_statement(std::shared_ptr<LM::Frontend::AST::ParallelStatement> parallel_stmt);
    TypePtr check_concurrent_statement(std::shared_ptr<LM::Frontend::AST::ConcurrentStatement> concurrent_stmt);
    TypePtr check_task_statement(std::shared_ptr<LM::Frontend::AST::TaskStatement> task_stmt);
    TypePtr check_worker_statement(std::shared_ptr<LM::Frontend::AST::WorkerStatement> worker_stmt);
    TypePtr check_return_statement(std::shared_ptr<LM::Frontend::AST::ReturnStatement> return_stmt);
    TypePtr check_print_statement(std::shared_ptr<LM::Frontend::AST::PrintStatement> print_stmt);
    TypePtr check_match_statement(std::shared_ptr<LM::Frontend::AST::MatchStatement> match_stmt);
    TypePtr check_contract_statement(std::shared_ptr<LM::Frontend::AST::ContractStatement> contract_stmt);
    
    // Expression type checking
    TypePtr check_literal_expr(std::shared_ptr<LM::Frontend::AST::LiteralExpr> expr, TypePtr expected_type = nullptr);
    TypePtr check_literal_expr_with_expected_type(std::shared_ptr<LM::Frontend::AST::LiteralExpr> expr, TypePtr expected_type);
    TypePtr check_variable_expr(std::shared_ptr<LM::Frontend::AST::VariableExpr> expr, TypePtr expected_type = nullptr);
    TypePtr check_binary_expr(std::shared_ptr<LM::Frontend::AST::BinaryExpr> expr, TypePtr expected_type = nullptr);
    TypePtr check_unary_expr(std::shared_ptr<LM::Frontend::AST::UnaryExpr> expr, TypePtr expected_type = nullptr);
    TypePtr check_call_expr(std::shared_ptr<LM::Frontend::AST::CallExpr> expr, TypePtr expected_type = nullptr);
    TypePtr check_assign_expr(std::shared_ptr<LM::Frontend::AST::AssignExpr> expr);
    TypePtr check_grouping_expr(std::shared_ptr<LM::Frontend::AST::GroupingExpr> expr);
    TypePtr check_member_expr(std::shared_ptr<LM::Frontend::AST::MemberExpr> expr);
    TypePtr check_index_expr(std::shared_ptr<LM::Frontend::AST::IndexExpr> expr);
    TypePtr check_list_expr(std::shared_ptr<LM::Frontend::AST::ListExpr> expr);
    TypePtr check_tuple_expr(std::shared_ptr<LM::Frontend::AST::TupleExpr> expr);
    TypePtr check_dict_expr(std::shared_ptr<LM::Frontend::AST::DictExpr> expr);
    TypePtr check_range_expr(std::shared_ptr<LM::Frontend::AST::RangeExpr> expr);
    TypePtr check_interpolated_string_expr(std::shared_ptr<LM::Frontend::AST::InterpolatedStringExpr> expr);
    TypePtr check_lambda_expr(std::shared_ptr<LM::Frontend::AST::LambdaExpr> expr);
    TypePtr check_error_construct_expr(std::shared_ptr<LM::Frontend::AST::ErrorConstructExpr> expr);
    TypePtr check_ok_construct_expr(std::shared_ptr<LM::Frontend::AST::OkConstructExpr> expr);
    TypePtr check_fallible_expr(std::shared_ptr<LM::Frontend::AST::FallibleExpr> expr);
    TypePtr check_frame_instantiation_expr(std::shared_ptr<LM::Frontend::AST::FrameInstantiationExpr> expr);
    TypePtr check_frame_declaration(std::shared_ptr<LM::Frontend::AST::FrameDeclaration> frame);
    TypePtr check_frame_declaration_with_name(const std::string& name, std::shared_ptr<LM::Frontend::AST::FrameDeclaration> frame);
    TypePtr check_enum_declaration(std::shared_ptr<LM::Frontend::AST::EnumDeclaration> enum_decl);
    TypePtr check_trait_declaration(std::shared_ptr<LM::Frontend::AST::TraitDeclaration> trait);
    TypePtr check_module_declaration(std::shared_ptr<LM::Frontend::AST::ModuleDeclaration> module_decl);
    TypePtr check_import_statement(std::shared_ptr<LM::Frontend::AST::ImportStatement> import_stmt);

    // Type annotation resolution
    TypePtr resolve_type_annotation(std::shared_ptr<LM::Frontend::AST::TypeAnnotation> annotation);
    
    // Type compatibility checking
    bool is_type_compatible(TypePtr expected, TypePtr actual);
    TypePtr get_common_type(TypePtr left, TypePtr right);
    bool can_implicitly_convert(TypePtr from, TypePtr to);
    
    // Function type checking
    bool check_function_call(const std::string& func_name, 
                            const std::vector<TypePtr>& arg_types,
                            TypePtr& result_type,
                            int line = 0);
    bool validate_argument_types(const std::vector<TypePtr>& expected,
                                 const std::vector<TypePtr>& actual,
                                 const std::string& func_name);
    
    // Control flow checking
    void check_return_statement(TypePtr return_type, int line);
    void check_break_statement(int line);
    void check_continue_statement(int line);
    
    // Visibility checking
    bool is_visible(const std::string& frame_name, LM::Frontend::AST::VisibilityLevel visibility, int line);

    // Helper methods
    bool is_numeric_type(TypePtr type);
    bool is_integer_type(TypePtr type);
    bool is_float_type(TypePtr type);
    bool is_boolean_type(TypePtr type);
    bool is_string_type(TypePtr type);
    bool is_optional_type(TypePtr type);
    bool is_error_union_type(TypePtr type);
    bool is_union_type(TypePtr type);
    bool requires_error_handling(TypePtr type);
    TypePtr promote_numeric_types(TypePtr left, TypePtr right);
    
    // Advanced error handling methods
    void validate_function_error_types(const std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>& stmt);
    void validate_function_body_error_types(const std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>& stmt);
    std::vector<std::string> infer_function_error_types(const std::shared_ptr<LM::Frontend::AST::Statement>& body);
    std::vector<std::string> infer_expression_error_types(const std::shared_ptr<LM::Frontend::AST::Expression>& expr);
    bool can_function_produce_error_type(const std::shared_ptr<LM::Frontend::AST::Statement>& body, const std::string& error_type);
    bool can_propagate_error(const std::vector<std::string>& source_errors, const std::vector<std::string>& target_errors);
    bool is_error_union_compatible(TypePtr from, TypePtr to);
    std::string join_error_types(const std::vector<std::string>& error_types);
    
    // Pattern matching methods
    bool is_exhaustive_error_match(const std::vector<std::shared_ptr<LM::Frontend::AST::MatchCase>>& cases, TypePtr type);
    bool is_exhaustive_union_match(TypePtr union_type, const std::vector<std::shared_ptr<LM::Frontend::AST::MatchCase>>& cases);
    bool is_exhaustive_option_match(const std::vector<std::shared_ptr<LM::Frontend::AST::MatchCase>>& cases);
    std::string get_missing_union_variants(TypePtr union_type, const std::vector<std::shared_ptr<LM::Frontend::AST::MatchCase>>& cases);
    void validate_pattern_compatibility(std::shared_ptr<LM::Frontend::AST::Expression> pattern_node, TypePtr match_type, int line);
    
    // Enhanced type inference
    TypePtr infer_lambda_return_type(const std::shared_ptr<LM::Frontend::AST::Statement>& body);
    TypePtr infer_literal_type(const std::shared_ptr<LM::Frontend::AST::LiteralExpr>& expr, TypePtr expected_type = nullptr);
    
    // Scope management
    struct Scope {
        std::unordered_map<std::string, TypePtr> variables;
        std::unique_ptr<Scope> parent;
        
        Scope(std::unique_ptr<Scope> p = nullptr) : parent(std::move(p)) {}
        
        TypePtr lookup(const std::string& name) {
            auto it = variables.find(name);
            if (it != variables.end()) {
                return it->second;
            }
            return parent ? parent->lookup(name) : nullptr;
        }
        
        void declare(const std::string& name, TypePtr type) {
            variables[name] = type;
        }
    };
    
    std::unique_ptr<Scope> current_scope;
};

// =============================================================================
// TYPE CHECKER RESULT - Passed to LIR Generator
// =============================================================================

struct TypeCheckResult {
    std::shared_ptr<LM::Frontend::AST::Program> program;  // AST with inferred_type set
    std::shared_ptr<TypeSystem> type_system;
    bool success;
    std::vector<std::string> errors;
    std::unordered_map<std::string, std::string> import_aliases;  // Module import aliases
    std::unordered_map<std::string, ModuleInfo> registered_modules;  // Module information
    
    TypeCheckResult(std::shared_ptr<LM::Frontend::AST::Program> prog, std::shared_ptr<TypeSystem> ts, bool succ, 
                    const std::vector<std::string>& errs)
        : program(prog), type_system(ts), success(succ), errors(errs) {}
};

// =============================================================================
// TYPE CHECKER FACTORY
// =============================================================================

namespace TypeCheckerFactory {
    // Create and run type checker
    TypeCheckResult check_program(std::shared_ptr<LM::Frontend::AST::Program> program, const std::string& source = "", const std::string& file_path = "");
    
    // Create type checker instance (for testing)
    std::unique_ptr<TypeChecker> create(TypeSystem& type_system);
    
    // Register builtin functions with the type checker
    void register_builtin_functions(TypeChecker& checker);
}

} // namespace Frontend
} // namespace LM

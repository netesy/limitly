#pragma once

#include "../backend/types.hh"
#include "../frontend/ast.hh"
#include "../lir/lir.hh"
#include "../memory/model.hh"
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

// =============================================================================
// TYPE CHECKER - Runs BEFORE LIR generation
// Implements the mental model: AST -> Typed AST (with memory safety) -> LIR (typed) -> JIT
// =============================================================================

class TypeChecker {
private:
    TypeSystem& type_system;
    std::vector<std::string> errors;
    
    // Symbol table for variable types
    std::unordered_map<std::string, TypePtr> variable_types;
    
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
        std::shared_ptr<AST::FunctionDeclaration> declaration;
    };
    std::unordered_map<std::string, FunctionSignature> function_signatures;
    
    // Current context
    std::shared_ptr<AST::FunctionDeclaration> current_function = nullptr;
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
    
public:
    explicit TypeChecker(TypeSystem& ts) : type_system(ts) {}
    
    // Main entry point - type check entire program
    bool check_program(std::shared_ptr<AST::Program> program);
    
    // Get errors after checking
    const std::vector<std::string>& get_errors() const { return errors; }
    bool has_errors() const { return !errors.empty(); }
    
    // Get the type system (for LIR generator)
    TypeSystem& get_type_system() { return type_system; }
    
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
    // Error reporting
    void add_error(const std::string& message, int line = 0);
    void add_type_error(const std::string& expected, const std::string& found, int line = 0);
    
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
    TypePtr check_expression(std::shared_ptr<AST::Expression> expr);
    TypePtr check_statement(std::shared_ptr<AST::Statement> stmt);
    TypePtr check_function_declaration(std::shared_ptr<AST::FunctionDeclaration> func);
    TypePtr check_var_declaration(std::shared_ptr<AST::VarDeclaration> var_decl);
    TypePtr check_block_statement(std::shared_ptr<AST::BlockStatement> block);
    TypePtr check_if_statement(std::shared_ptr<AST::IfStatement> if_stmt);
    TypePtr check_while_statement(std::shared_ptr<AST::WhileStatement> while_stmt);
    TypePtr check_for_statement(std::shared_ptr<AST::ForStatement> for_stmt);
    TypePtr check_return_statement(std::shared_ptr<AST::ReturnStatement> return_stmt);
    TypePtr check_print_statement(std::shared_ptr<AST::PrintStatement> print_stmt);
    
    // Expression type checking
    TypePtr check_literal_expr(std::shared_ptr<AST::LiteralExpr> expr);
    TypePtr check_variable_expr(std::shared_ptr<AST::VariableExpr> expr);
    TypePtr check_binary_expr(std::shared_ptr<AST::BinaryExpr> expr);
    TypePtr check_unary_expr(std::shared_ptr<AST::UnaryExpr> expr);
    TypePtr check_call_expr(std::shared_ptr<AST::CallExpr> expr);
    TypePtr check_assign_expr(std::shared_ptr<AST::AssignExpr> expr);
    TypePtr check_grouping_expr(std::shared_ptr<AST::GroupingExpr> expr);
    TypePtr check_member_expr(std::shared_ptr<AST::MemberExpr> expr);
    TypePtr check_index_expr(std::shared_ptr<AST::IndexExpr> expr);
    TypePtr check_list_expr(std::shared_ptr<AST::ListExpr> expr);
    TypePtr check_tuple_expr(std::shared_ptr<AST::TupleExpr> expr);
    TypePtr check_dict_expr(std::shared_ptr<AST::DictExpr> expr);
    TypePtr check_interpolated_string_expr(std::shared_ptr<AST::InterpolatedStringExpr> expr);
    TypePtr check_lambda_expr(std::shared_ptr<AST::LambdaExpr> expr);
    
    // Type annotation resolution
    TypePtr resolve_type_annotation(std::shared_ptr<AST::TypeAnnotation> annotation);
    
    // Type compatibility checking
    bool is_type_compatible(TypePtr expected, TypePtr actual);
    TypePtr get_common_type(TypePtr left, TypePtr right);
    bool can_implicitly_convert(TypePtr from, TypePtr to);
    
    // Function type checking
    bool check_function_call(const std::string& func_name, 
                            const std::vector<TypePtr>& arg_types,
                            TypePtr& result_type);
    bool validate_argument_types(const std::vector<TypePtr>& expected,
                                 const std::vector<TypePtr>& actual,
                                 const std::string& func_name);
    
    // Control flow checking
    void check_return_statement(TypePtr return_type, int line);
    void check_break_statement(int line);
    void check_continue_statement(int line);
    
    // Helper methods
    bool is_numeric_type(TypePtr type);
    bool is_boolean_type(TypePtr type);
    bool is_string_type(TypePtr type);
    TypePtr promote_numeric_types(TypePtr left, TypePtr right);
    
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
    std::shared_ptr<AST::Program> program;  // AST with inferred_type set
    TypeSystem& type_system;
    bool success;
    std::vector<std::string> errors;
    
    TypeCheckResult(std::shared_ptr<AST::Program> prog, TypeSystem& ts, bool succ, 
                    const std::vector<std::string>& errs)
        : program(prog), type_system(ts), success(succ), errors(errs) {}
};

// =============================================================================
// TYPE CHECKER FACTORY
// =============================================================================

namespace TypeCheckerFactory {
    // Create and run type checker
    TypeCheckResult check_program(std::shared_ptr<AST::Program> program, const std::string& source = "", const std::string& file_path = "");
    
    // Create type checker instance (for testing)
    std::unique_ptr<TypeChecker> create(TypeSystem& type_system);
    
    // Register builtin functions with the type checker
    void register_builtin_functions(TypeChecker& checker);
}

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
#include <cstring>
#include "symbol_database.hh"

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
    struct Scope;


    TypeSystem& type_system;
    SymbolDatabase& symbol_db_;
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
        std::shared_ptr<LM::Frontend::AST::Statement> declaration;
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

    // =========================================================================
    // FRAME MEMORY TRACKING (NEW)
    // =========================================================================
    
    struct FrameFieldMemoryInfo {
        std::string frame_name;
        std::string field_name;
        TypePtr field_type;
        bool is_linear;                           // Is field a linear type?
        bool is_owned;                            // Does field own its value?
        std::unordered_set<std::string> mutable_refs;  // Variables with mutable refs
        bool has_exclusive_ref;                   // Has exclusive mutable reference?
    };
    std::unordered_map<std::string, FrameFieldMemoryInfo> frame_field_memory_info;
    
    struct FrameAllocation {
        std::string frame_name;
        int line;
        int scope_level;
        std::vector<std::string> initialized_fields;
    };
    std::vector<FrameAllocation> frame_allocations_in_scope;

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
    
    // Lambda capture tracking
    std::vector<std::vector<std::string>> lambda_captures_stack;
    std::vector<Scope*> lambda_scope_markers;
    
    // =========================================================================
    // COMPREHENSIVE MEMORY SAFETY INFRASTRUCTURE
    // =========================================================================
    
    // Current line number for error reporting
    int current_line = 0;
    
    // Tracks whether we're currently in a method
    std::string current_method_frame;  // Frame name if in method, empty otherwise
    std::string current_method_name;   // Method name if in method, empty otherwise
    
    // Method-level self tracking
    struct MethodSelfInfo {
        std::string method_name;
        std::string frame_name;
        std::unordered_set<std::string> self_references;  // Variables referencing self
        bool has_self_escape = false;                      // Whether self escapes
        int self_scope_level = 0;
    };
    std::unordered_map<std::string, MethodSelfInfo> method_self_tracking;
    
    // Enum and variant tracking for memory safety
    struct VariantInfo {
        std::string enum_name;
        std::string variant_name;
        std::vector<TypePtr> associated_types;  // Types associated with variant
    };
    std::unordered_map<std::string, VariantInfo> variant_registry;  // variant_name -> VariantInfo
    
    // Concurrency thread safety tracking
    struct ConcurrencyContext {
        bool in_parallel_block = false;
        bool in_concurrent_block = false;
        bool in_task = false;
        std::unordered_set<std::string> shared_variables;  // Variables accessed from multiple threads
    };
    ConcurrencyContext concurrency_context;
    
    // Captures in lambdas and closures
    struct CaptureInfo {
        std::string variable_name;
        bool is_moved = false;              // Is variable moved into closure?
        bool is_mutable_ref = false;        // Is mutable reference?
        int line = 0;
        TypePtr capture_type;
    };
    std::vector<CaptureInfo> current_lambda_captures;
    
    // =========================================================================
    // PHASE 6: EXCEPTION SAFETY TRACKING
    // =========================================================================
    
    // Field initialization tracking for exception safety
    struct FieldInitializationInfo {
        std::string field_name;
        int initialization_line = 0;
        bool is_initialized = false;
        bool has_error_handling = false;  // Field init can fail
        TypePtr field_type;
        int init_order = -1;  // Sequence in initialization
    };
    std::vector<FieldInitializationInfo> current_frame_field_initializations;
    
    // Exception safety context
    struct ExceptionSafetyContext {
        std::string current_frame_name;
        std::vector<FieldInitializationInfo> initialized_fields;
        std::vector<std::string> exit_paths;  // return, break, continue, ?
        bool in_init_method = false;
        bool in_deinit_method = false;
        std::vector<std::string> cleanup_order;  // Reverse init order
    };
    ExceptionSafetyContext exception_safety_context;
    
    // Resource cleanup tracking
    struct ResourceCleanupInfo {
        std::string resource_name;
        std::string acquisition_site;
        int acquisition_line = 0;
        std::vector<std::string> cleanup_sites;
        bool cleanup_guaranteed = false;
    };
    std::unordered_map<std::string, ResourceCleanupInfo> resource_cleanup_tracking;
    
    // Map to track which enums define which variants
    std::unordered_map<std::string, std::vector<TypePtr>> variant_owners;
    
    std::shared_ptr<LM::Frontend::AST::Program> current_program_ = nullptr;
    
public:
    bool is_root = true;

    // Constructor accepting TypeSystem and SymbolDatabase
    explicit TypeChecker(TypeSystem& ts, SymbolDatabase& symbol_db) : type_system(ts), symbol_db_(symbol_db) {}

    // Getter for SymbolDatabase
    SymbolDatabase& get_symbol_db() const { return symbol_db_; }
    
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
    
public:
    // Diagnostic helpers & shared tracking
    static std::unordered_set<std::string> failed_modules;
    static std::unordered_set<std::string> failed_frames;

    static int levenshtein_distance(const std::string& s1, const std::string& s2);
    static std::string find_similar_name(const std::string& name, const std::vector<std::string>& candidates);
    static std::vector<std::string> get_all_available_modules();

    std::vector<std::string> get_visible_variables() const;
    std::vector<std::string> get_visible_types() const;
    std::string get_module_prefix(const std::string& name) const;
    bool is_failed_type(const std::string& name) const;

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
    TypePtr check_match_statement(std::shared_ptr<LM::Frontend::AST::MatchStatement> match_stmt);
    TypePtr check_contract_statement(std::shared_ptr<LM::Frontend::AST::ContractStatement> contract_stmt);
    
    // Expression type checking
    TypePtr check_literal_expr(std::shared_ptr<LM::Frontend::AST::LiteralExpr> expr, TypePtr expected_type = nullptr);
    TypePtr check_literal_expr_with_expected_type(std::shared_ptr<LM::Frontend::AST::LiteralExpr> expr, TypePtr expected_type);
    TypePtr check_variable_expr(std::shared_ptr<LM::Frontend::AST::VariableExpr> expr, TypePtr expected_type = nullptr);
    TypePtr check_binary_expr(std::shared_ptr<LM::Frontend::AST::BinaryExpr> expr, TypePtr expected_type = nullptr);
    TypePtr check_unary_expr(std::shared_ptr<LM::Frontend::AST::UnaryExpr> expr, TypePtr expected_type = nullptr);
    TypePtr check_call_expr(std::shared_ptr<LM::Frontend::AST::CallExpr> expr, TypePtr expected_type = nullptr);
    void resolve_call_arguments(std::shared_ptr<LM::Frontend::AST::CallExpr> expr, const std::string& qualified_name);
    TypePtr check_cast_expr(std::shared_ptr<LM::Frontend::AST::CastExpr> expr);
    TypePtr check_assign_expr(std::shared_ptr<LM::Frontend::AST::AssignExpr> expr);
    TypePtr check_grouping_expr(std::shared_ptr<LM::Frontend::AST::GroupingExpr> expr, TypePtr expected_type = nullptr);
    TypePtr check_member_expr(std::shared_ptr<LM::Frontend::AST::MemberExpr> expr);
    TypePtr check_index_expr(std::shared_ptr<LM::Frontend::AST::IndexExpr> expr);
    TypePtr check_list_expr(std::shared_ptr<LM::Frontend::AST::ListExpr> expr, TypePtr expected_type = nullptr);
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
                                 const std::string& func_name,
                                 int line = 0);
    
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
    bool is_decimal_type(TypePtr type);
    int get_decimal_scale(TypePtr type);
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
    bool should_capture_variable(const std::string& name) const;
    
    // =========================================================================
    // OOP MEMORY SAFETY METHODS (NEW)
    // =========================================================================
    
    // Frame memory safety
    void check_frame_field_mutable_aliasing(
        const std::string& frame_var,
        const std::string& field_name,
        bool is_mutable,
        int line);
    
    void invalidate_frame_field_references(
        const std::string& frame_var,
        const std::string& field_name,
        int line);
    
    void verify_frame_field_exclusive_access(
        const std::string& frame_var,
        const std::string& field_name,
        int line);
    
    // Frame initialization safety
    void register_frame_for_deinit(
        const std::string& frame_name,
        int scope_level);
    
    void verify_frame_full_initialization(
        const std::string& frame_name,
        const std::vector<std::string>& initialized_fields,
        int line);
    
    void check_frame_field_linear_types(
        const std::string& frame_name,
        const std::vector<std::pair<std::string, TypePtr>>& fields);
    
    // Trait implementation verification
    void verify_trait_implementation(
        const std::string& frame_name,
        const std::string& trait_name,
        const FrameInfo& frame_info);
    
    void validate_method_signature_compatibility(
        std::shared_ptr<LM::Frontend::AST::FunctionDeclaration> trait_method,
        std::shared_ptr<LM::Frontend::AST::FunctionDeclaration> frame_method);
    
    // =========================================================================
    // PHASE 2: CONTROL FLOW SAFETY
    // =========================================================================
    
    void check_linear_type_in_loop_body(
        const std::string& loop_var,
        const std::vector<std::shared_ptr<LM::Frontend::AST::Statement>>& body_statements,
        int line);
    
    void validate_break_cleanup(int line);
    void validate_continue_cleanup(int line);
    void validate_scope_cleanup_on_control_flow(const std::string& control_flow_type, int line);
    
    // =========================================================================
    // PHASE 3: LAMBDA & CLOSURE SAFETY
    // =========================================================================
    
    void analyze_lambda_captures(const std::shared_ptr<LM::Frontend::AST::LambdaExpr>& lambda);
    void validate_capture_ownership(const std::string& capture_var, bool is_moved, int line);
    void check_closure_lifetime(const std::string& closure_var, int line);
    void validate_lambda_escape_analysis(const std::shared_ptr<LM::Frontend::AST::LambdaExpr>& lambda);
    
    // =========================================================================
    // PHASE 4: CONCURRENCY SAFETY
    // =========================================================================
    
    void check_parallel_block_thread_safety(const std::vector<std::string>& captured_vars, int line);
    void check_concurrent_block_thread_safety(const std::vector<std::string>& captured_vars, int line);
    void detect_data_races(const std::string& var_name, int line);
    void validate_send_trait(TypePtr type, int line);
    void validate_sync_trait(TypePtr type, int line);
    void check_channel_type_safety(const std::shared_ptr<LM::Frontend::AST::CallExpr>& send_expr, int line);
    
    // =========================================================================
    // PHASE 5: ENUM & PATTERN SAFETY
    // =========================================================================
    
    void register_enum_variant(const std::string& enum_name, const std::string& variant_name, 
                              const std::vector<TypePtr>& associated_types);
    void check_variant_constructor_ownership(const std::string& variant_name, 
                                            const std::vector<TypePtr>& arg_types, int line);
    void validate_pattern_binding_ownership(const std::shared_ptr<LM::Frontend::AST::Expression>& pattern,
                                           TypePtr match_type, int line);
    void check_pattern_linear_type_move(const std::string& binding_var, TypePtr pattern_type, int line);
    
    // =========================================================================
    // PHASE 6: EXCEPTION SAFETY
    // =========================================================================
    
    void validate_frame_init_exception_safety(const std::string& frame_name,
                                             const std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>& init_method,
                                             int line);
    void track_field_initialization_order(const std::string& frame_name);
    void validate_cleanup_on_exception(const std::vector<std::string>& initialized_fields, int line);
    
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
    std::unique_ptr<TypeChecker> create(TypeSystem& type_system, SymbolDatabase& symbol_db);
    
    // Register builtin functions with the type checker
    void register_builtin_functions(TypeChecker& checker);
}

} // namespace Frontend
} // namespace LM

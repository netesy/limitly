#pragma once

#include "ast.hh"
#include "type_checker.hh"
#include "../memory/model.hh"
#include "../memory/compiler.hh"
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>

// =============================================================================
// MEMORY CHECKER - Separate phase after type checking
// Enhanced with generational references and region-aware tracking
// =============================================================================

namespace LM {
namespace Frontend {

// Forward declarations
struct GenerationalRef;
struct ReferenceInfo;

struct MemoryCheckResult {
    bool success;
    std::shared_ptr<AST::Program> program;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
};

// Explicit ownership states to distinguish different semantic operations
enum class OwnershipState {
    Uninitialized,     // Variable declared but not initialized
    Valid,             // Variable owns a valid value, can be read
    Moved,             // Ownership transferred, variable is invalid for ownership-consuming access
    Borrowed,          // Variable is borrowed, immutable access only
    MutablyBorrowed,   // Variable is mutably borrowed, exclusive access
    Escaped,           // Value escaped current region, original region cannot reclaim
    Consumed,          // Value was consumed (e.g., by linear function)
    Invalid            // Variable is in invalid state
};

// Information tracked for each variable's generation
struct GenerationInfo {
    int region_id;
    int generation;
    bool is_linear;
    OwnershipState ownership_state;
    std::vector<std::shared_ptr<GenerationalRef>> active_refs;
    int scope_depth;
};

// Information about a generational reference
struct GenerationalRef {
    std::string ref_id;
    int created_generation;
    int created_region;
    int created_scope;
    bool is_mutable;
    bool is_valid;
    
    GenerationalRef(const std::string& id, int gen, int region, int scope, bool mut = false)
        : ref_id(id), created_generation(gen), created_region(region), 
          created_scope(scope), is_mutable(mut), is_valid(true) {}
};

class MemoryChecker {
public:
    MemoryChecker() = default;
    
    // Main entry point - check memory safety after type checking
    MemoryCheckResult check_program(std::shared_ptr<AST::Program> program, 
                                    const std::string& source = "", 
                                    const std::string& filename = "");

private:
    // Memory tracking state - enhanced with generational tracking
    std::unordered_map<std::string, GenerationInfo> variable_generation_info;
    std::unordered_map<std::string, int> variable_regions;
    std::unordered_set<std::string> moved_variables;
    std::unordered_set<std::string> initialized_variables;
    std::unordered_map<std::string, int> variable_generations;
    std::unordered_map<std::string, int64_t> constant_variables;  // Track variables with constant values
    
    // Generational reference tracking
    std::deque<std::vector<std::shared_ptr<GenerationalRef>>> generation_stack;
    std::unordered_map<std::string, std::vector<std::shared_ptr<GenerationalRef>>> reference_chain;
    std::unordered_map<std::string, std::vector<int>> generation_history;
    
    // Current context
    std::string current_source;
    std::string current_file_path;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
    // Memory regions - enhanced for generation management
    int current_region_id = 0;
    int current_generation = 0;
    int current_scope_depth = 0;
    std::vector<int> region_stack;
    std::vector<int> generation_stack_history;
    
    // Statement checking
    void check_statement(std::shared_ptr<AST::Statement> stmt);
    void check_var_declaration(std::shared_ptr<AST::VarDeclaration> var_decl);
    void check_assignment(std::shared_ptr<AST::AssignExpr> assignment);
    void check_expression(std::shared_ptr<AST::Expression> expr);
    void check_variable_access(std::shared_ptr<AST::VariableExpr> var_expr);
    void check_function_call(std::shared_ptr<AST::CallExpr> call);
    void check_block_statement(std::shared_ptr<AST::BlockStatement> block);
    
    // Arithmetic safety checking
    void check_binary_expression(std::shared_ptr<AST::BinaryExpr> binary);
    void check_arithmetic_safety(std::shared_ptr<AST::BinaryExpr> binary);
    void check_division_safety(std::shared_ptr<AST::BinaryExpr> binary);
    void check_shift_safety(std::shared_ptr<AST::BinaryExpr> binary);
    bool is_constant_expression(std::shared_ptr<AST::Expression> expr);
    int64_t evaluate_constant_int(std::shared_ptr<AST::Expression> expr);
    bool check_overflow(int64_t left, int64_t right, const std::string& op);
    bool check_underflow(int64_t left, int64_t right, const std::string& op);
    
    // Bounds checking
    void check_index_expression(std::shared_ptr<AST::IndexExpr> index);
    void check_list_bounds(std::shared_ptr<AST::IndexExpr> index, std::shared_ptr<AST::ListExpr> list);
    void check_string_bounds(std::shared_ptr<AST::IndexExpr> index, std::shared_ptr<AST::LiteralExpr> str);
    void check_tuple_bounds(std::shared_ptr<AST::IndexExpr> index, std::shared_ptr<AST::TupleExpr> tuple);
    
    // Memory operations (currently disabled - LIR generator manages regions independently)
    void insert_memory_operations(std::shared_ptr<AST::Statement> stmt);
    void insert_make_linear(std::shared_ptr<AST::Expression> expr);
    void insert_make_ref(std::shared_ptr<AST::Expression> expr);
    void insert_move(std::shared_ptr<AST::Expression> expr);
    void insert_drop(std::shared_ptr<AST::Expression> expr);
    
    // Variable tracking
    void mark_variable_initialized(const std::string& name);
    void mark_variable_moved(const std::string& name);
    void mark_variable_copied(const std::string& name);
    void mark_variable_borrowed(const std::string& name, bool is_mutable = false);
    void mark_variable_escaped(const std::string& name);
    void mark_variable_consumed(const std::string& name);
    bool is_variable_initialized(const std::string& name) const;
    bool is_variable_moved(const std::string& name) const;
    OwnershipState get_ownership_state(const std::string& name) const;
    
    // Memory region management
    void enter_memory_region();
    void exit_memory_region();
    
    // Generational reference tracking
    std::shared_ptr<GenerationalRef> create_reference(const std::string& var_name, bool is_mutable = false);
    void invalidate_generation(int generation);
    void invalidate_references_at_scope(int scope_depth);
    bool is_reference_valid(const std::shared_ptr<GenerationalRef>& ref) const;
    void check_reference_lifetime(const std::string& var_name, int ref_generation, int current_generation);
    void check_mutable_aliasing(const std::string& var_name, bool is_mutable);
    void track_generation_transition(const std::string& var_name, int old_gen, int new_gen);
    
    // Enhanced scope management
    void enter_scope();
    void exit_scope();
    void invalidate_scope_references();
    
    // Error reporting
    void add_memory_error(const std::string& error_type, const std::string& variable_name, 
                         const std::string& description, int line = 0);
    void add_error(const std::string& message, int line = 0);
    void add_warning(const std::string& message, int line = 0);
    
    // Debug/diagnostic methods
    std::string get_generation_info(const std::string& var_name) const;
    std::string get_reference_info(const std::string& var_name) const;
    void dump_memory_state() const;
};

// Factory for creating memory checker results
class MemoryCheckerFactory {
public:
    static MemoryCheckResult check_program(std::shared_ptr<AST::Program> program, 
                                          const std::string& source = "", 
                                          const std::string& filename = "");
};

} // namespace Frontend
} // namespace LM

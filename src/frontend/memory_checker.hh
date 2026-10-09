#pragma once

#include "ast.hh"
#include "../memory/model.hh"
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// =============================================================================
// MEMORY CHECKER - Separate phase after type checking
// Validates authoritative ownership facts, bounds, regions and concurrency.
// =============================================================================

namespace LM {
namespace Frontend {

struct MemoryCheckResult {
    bool success;
    std::shared_ptr<AST::Program> program;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
};

class MemoryChecker {
public:
    MemoryChecker() = default;
    
    // Main entry point - check memory safety after type checking
    MemoryCheckResult check_program(std::shared_ptr<AST::Program> program, 
                                    const std::string& source = "", 
                                    const std::string& filename = "");

private:
    std::shared_ptr<const Memory::SemanticFacts> ownership_facts;
    std::unordered_map<std::string, int64_t> constant_variables;  // Track variables with constant values
    std::unordered_set<std::string> atomic_variables;
    
    // Capability tracking
    std::vector<AST::ParallelSliceCapability> active_parallel_slices;

    // Check parallel slice capability disjointness
    bool verify_slice_disjointness(const AST::ParallelSliceCapability& slice, int line);
    void infer_parallel_capabilities(const std::shared_ptr<AST::ParallelStatement>& stmt);
    void validate_concurrent_isolation(const std::shared_ptr<AST::Node>& node,
                                       std::unordered_set<std::string> locals = {});

    // Current context
    std::string current_source;
    std::string current_file_path;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
    // Lexical annotations; dynamic lifetimes are defined by canonical LIR.
    int current_region_id = 0;
    int current_generation = 0;
    // Statement checking
    void check_statement(std::shared_ptr<AST::Statement> stmt);
    void check_var_declaration(std::shared_ptr<AST::VarDeclaration> var_decl);
    void check_assignment(std::shared_ptr<AST::AssignExpr> assignment);
    void check_expression(std::shared_ptr<AST::Expression> expr);
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
    
    // Attach lexical annotations without changing stable semantic identities.
    void insert_memory_operations(std::shared_ptr<AST::Statement> stmt);
    // Lexical region annotations
    void enter_memory_region();

    // Error reporting
    void add_memory_error(const std::string& error_type, const std::string& variable_name, 
                         const std::string& description, int line = 0);
    void add_error(const std::string& message, int line = 0);
    void add_warning(const std::string& message, int line = 0);
    
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

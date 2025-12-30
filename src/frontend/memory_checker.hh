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

// =============================================================================
// MEMORY CHECKER - Separate phase after type checking
// =============================================================================

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
    // Memory tracking state
    std::unordered_map<std::string, int> variable_regions;
    std::unordered_set<std::string> moved_variables;
    std::unordered_set<std::string> initialized_variables;
    std::unordered_map<std::string, int> variable_generations;
    
    // Current context
    std::string current_source;
    std::string current_file_path;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
    // Memory regions
    int current_region_id = 0;
    int current_generation = 0;
    
    // Statement checking
    void check_statement(std::shared_ptr<AST::Statement> stmt);
    void check_var_declaration(std::shared_ptr<AST::VarDeclaration> var_decl);
    void check_assignment(std::shared_ptr<AST::AssignExpr> assignment);
    void check_expression(std::shared_ptr<AST::Expression> expr);
    void check_variable_access(std::shared_ptr<AST::VariableExpr> var_expr);
    void check_function_call(std::shared_ptr<AST::CallExpr> call);
    void check_block_statement(std::shared_ptr<AST::BlockStatement> block);
    
    // Memory operations
    void insert_memory_operations(std::shared_ptr<AST::Statement> stmt);
    void insert_make_linear(std::shared_ptr<AST::Expression> expr);
    void insert_make_ref(std::shared_ptr<AST::Expression> expr);
    void insert_move(std::shared_ptr<AST::Expression> expr);
    void insert_drop(std::shared_ptr<AST::Expression> expr);
    
    // Variable tracking
    void mark_variable_initialized(const std::string& name);
    void mark_variable_moved(const std::string& name);
    bool is_variable_initialized(const std::string& name) const;
    bool is_variable_moved(const std::string& name) const;
    
    // Memory region management
    void enter_memory_region();
    void exit_memory_region();
    
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
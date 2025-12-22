#pragma once

#include "../backend/types.hh"
#include "../frontend/ast.hh"
#include "../lir/lir.hh"
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

// =============================================================================
// TYPE CHECKER - Runs BEFORE LIR generation
// Implements the mental model: AST -> Typed AST -> LIR (typed) -> JIT
// =============================================================================

class TypeChecker {
private:
    TypeSystem& type_system;
    std::vector<std::string> errors;
    
    // Symbol table for variable types
    std::unordered_map<std::string, TypePtr> variable_types;
    
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
    
public:
    explicit TypeChecker(TypeSystem& ts) : type_system(ts) {}
    
    // Main entry point - type check entire program
    bool check_program(std::shared_ptr<AST::Program> program);
    
    // Get errors after checking
    const std::vector<std::string>& get_errors() const { return errors; }
    bool has_errors() const { return !errors.empty(); }
    
    // Get the type system (for LIR generator)
    TypeSystem& get_type_system() { return type_system; }
    
private:
    // Error reporting
    void add_error(const std::string& message, int line = 0);
    void add_type_error(const std::string& expected, const std::string& found, int line = 0);
    
    // Symbol table management
    void enter_scope();
    void exit_scope();
    void declare_variable(const std::string& name, TypePtr type);
    TypePtr lookup_variable(const std::string& name);
    
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
    TypeCheckResult check_program(std::shared_ptr<AST::Program> program);
    
    // Create type checker instance (for testing)
    std::unique_ptr<TypeChecker> create(TypeSystem& type_system);
}

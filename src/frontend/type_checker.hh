#pragma once

#include "type_system.hh"
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
    std::unordered_map<std::string, LanguageType*> variable_types;
    
    // Function signatures
    struct FunctionSignature {
        std::string name;
        std::vector<LanguageType*> param_types;
        LanguageType* return_type;
        std::shared_ptr<AST::FunctionDeclaration> declaration;
    };
    std::unordered_map<std::string, FunctionSignature> function_signatures;
    
    // Current context
    std::shared_ptr<AST::FunctionDeclaration> current_function = nullptr;
    LanguageType* current_return_type = nullptr;
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
    void declare_variable(const std::string& name, LanguageType* type);
    LanguageType* lookup_variable(const std::string& name);
    
    // Type checking methods
    LanguageType* check_expression(std::shared_ptr<AST::Expression> expr);
    LanguageType* check_statement(std::shared_ptr<AST::Statement> stmt);
    LanguageType* check_function_declaration(std::shared_ptr<AST::FunctionDeclaration> func);
    LanguageType* check_var_declaration(std::shared_ptr<AST::VarDeclaration> var_decl);
    LanguageType* check_block_statement(std::shared_ptr<AST::BlockStatement> block);
    LanguageType* check_if_statement(std::shared_ptr<AST::IfStatement> if_stmt);
    LanguageType* check_while_statement(std::shared_ptr<AST::WhileStatement> while_stmt);
    LanguageType* check_for_statement(std::shared_ptr<AST::ForStatement> for_stmt);
    LanguageType* check_return_statement(std::shared_ptr<AST::ReturnStatement> return_stmt);
    LanguageType* check_print_statement(std::shared_ptr<AST::PrintStatement> print_stmt);
    
    // Expression type checking
    LanguageType* check_literal_expr(std::shared_ptr<AST::LiteralExpr> expr);
    LanguageType* check_variable_expr(std::shared_ptr<AST::VariableExpr> expr);
    LanguageType* check_binary_expr(std::shared_ptr<AST::BinaryExpr> expr);
    LanguageType* check_unary_expr(std::shared_ptr<AST::UnaryExpr> expr);
    LanguageType* check_call_expr(std::shared_ptr<AST::CallExpr> expr);
    LanguageType* check_assign_expr(std::shared_ptr<AST::AssignExpr> expr);
    LanguageType* check_grouping_expr(std::shared_ptr<AST::GroupingExpr> expr);
    LanguageType* check_member_expr(std::shared_ptr<AST::MemberExpr> expr);
    LanguageType* check_index_expr(std::shared_ptr<AST::IndexExpr> expr);
    LanguageType* check_list_expr(std::shared_ptr<AST::ListExpr> expr);
    LanguageType* check_tuple_expr(std::shared_ptr<AST::TupleExpr> expr);
    LanguageType* check_dict_expr(std::shared_ptr<AST::DictExpr> expr);
    LanguageType* check_interpolated_string_expr(std::shared_ptr<AST::InterpolatedStringExpr> expr);
    LanguageType* check_lambda_expr(std::shared_ptr<AST::LambdaExpr> expr);
    
    // Type annotation resolution
    LanguageType* resolve_type_annotation(std::shared_ptr<AST::TypeAnnotation> annotation);
    
    // Type compatibility checking
    bool is_type_compatible(LanguageType* expected, LanguageType* actual);
    LanguageType* get_common_type(LanguageType* left, LanguageType* right);
    bool can_implicitly_convert(LanguageType* from, LanguageType* to);
    
    // Function type checking
    bool check_function_call(const std::string& func_name, 
                            const std::vector<LanguageType*>& arg_types,
                            LanguageType*& result_type);
    bool validate_argument_types(const std::vector<LanguageType*>& expected,
                                 const std::vector<LanguageType*>& actual,
                                 const std::string& func_name);
    
    // Control flow checking
    void check_return_statement(LanguageType* return_type, int line);
    void check_break_statement(int line);
    void check_continue_statement(int line);
    
    // Helper methods
    bool is_numeric_type(LanguageType* type);
    bool is_boolean_type(LanguageType* type);
    bool is_string_type(LanguageType* type);
    LanguageType* promote_numeric_types(LanguageType* left, LanguageType* right);
    
    // Scope management
    struct Scope {
        std::unordered_map<std::string, LanguageType*> variables;
        std::unique_ptr<Scope> parent;
        
        Scope(std::unique_ptr<Scope> p = nullptr) : parent(std::move(p)) {}
        
        LanguageType* lookup(const std::string& name) {
            auto it = variables.find(name);
            if (it != variables.end()) {
                return it->second;
            }
            return parent ? parent->lookup(name) : nullptr;
        }
        
        void declare(const std::string& name, LanguageType* type) {
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

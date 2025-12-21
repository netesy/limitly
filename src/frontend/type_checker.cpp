#include "type_checker.hh"
#include <sstream>
#include <stdexcept>

// =============================================================================
// TYPE CHECKER IMPLEMENTATION
// =============================================================================

bool TypeChecker::check_program(std::shared_ptr<AST::Program> program) {
    if (!program) {
        add_error("Null program provided");
        return false;
    }
    
    errors.clear();
    current_scope = std::make_unique<Scope>();
    
    // First pass: collect function declarations
    for (const auto& stmt : program->statements) {
        if (auto func_decl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
            check_function_declaration(func_decl);
        }
    }
    
    // Second pass: check all statements
    for (const auto& stmt : program->statements) {
        check_statement(stmt);
    }
    
    // Set the inferred type on the program node
    // For a program, we could use void type or the type of the last statement
    program->inferred_type = type_system.get_nil_type(); // Programs don't return values
    
    return errors.empty();
}

void TypeChecker::add_error(const std::string& message, int line) {
    std::stringstream ss;
    if (line > 0) {
        ss << "Line " << line << ": ";
    }
    ss << message;
    errors.push_back(ss.str());
}

void TypeChecker::add_type_error(const std::string& expected, const std::string& found, int line) {
    add_error("Type mismatch: expected " + expected + ", found " + found, line);
}

void TypeChecker::enter_scope() {
    current_scope = std::make_unique<Scope>(std::move(current_scope));
}

void TypeChecker::exit_scope() {
    if (current_scope && current_scope->parent) {
        current_scope = std::move(current_scope->parent);
    }
}

void TypeChecker::declare_variable(const std::string& name, LanguageType* type) {
    if (current_scope) {
        current_scope->declare(name, type);
    }
}

LanguageType* TypeChecker::lookup_variable(const std::string& name) {
    return current_scope ? current_scope->lookup(name) : nullptr;
}

LanguageType* TypeChecker::check_statement(std::shared_ptr<AST::Statement> stmt) {
    if (!stmt) return nullptr;
    
    if (auto func_decl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
        return check_function_declaration(func_decl);
    } else if (auto var_decl = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
        return check_var_declaration(var_decl);
    } else if (auto block = std::dynamic_pointer_cast<AST::BlockStatement>(stmt)) {
        return check_block_statement(block);
    } else if (auto if_stmt = std::dynamic_pointer_cast<AST::IfStatement>(stmt)) {
        return check_if_statement(if_stmt);
    } else if (auto while_stmt = std::dynamic_pointer_cast<AST::WhileStatement>(stmt)) {
        return check_while_statement(while_stmt);
    } else if (auto for_stmt = std::dynamic_pointer_cast<AST::ForStatement>(stmt)) {
        return check_for_statement(for_stmt);
    } else if (auto return_stmt = std::dynamic_pointer_cast<AST::ReturnStatement>(stmt)) {
        return check_return_statement(return_stmt);
    } else if (auto print_stmt = std::dynamic_pointer_cast<AST::PrintStatement>(stmt)) {
        return check_print_statement(print_stmt);
    } else if (auto expr_stmt = std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) {
        return check_expression(expr_stmt->expression);
    }
    
    return nullptr;
}

LanguageType* TypeChecker::check_function_declaration(std::shared_ptr<AST::FunctionDeclaration> func) {
    if (!func) return nullptr;
    
    // Resolve return type
    LanguageType* return_type = type_system.get_string_type(); // Default
    if (func->returnType) {
        return_type = resolve_type_annotation(func->returnType);
    }
    
    // Create function signature
    FunctionSignature signature;
    signature.name = func->name;
    signature.return_type = return_type;
    signature.declaration = func;
    
    // Check parameters
    for (const auto& param : func->parameters) {
        LanguageType* param_type = type_system.get_string_type(); // Default
        if (param.type) {
            param_type = resolve_type_annotation(param.type);
        }
        signature.param_types.push_back(param_type);
    }
    
    function_signatures[func->name] = signature;
    
    // Check function body
    current_function = func;
    current_return_type = return_type;
    enter_scope();
    
    // Declare parameters
    for (size_t i = 0; i < func->parameters.size(); ++i) {
        declare_variable(func->parameters[i].name, signature.param_types[i]);
    }
    
    // Check body
    LanguageType* body_type = check_statement(func->body);
    
    exit_scope();
    current_function = nullptr;
    current_return_type = nullptr;
    
    // Set the inferred type on the function declaration
    func->inferred_type = return_type;
    
    return return_type;
}

LanguageType* TypeChecker::check_var_declaration(std::shared_ptr<AST::VarDeclaration> var_decl) {
    if (!var_decl) return nullptr;
    
    LanguageType* declared_type = nullptr;
    if (var_decl->type) {
        declared_type = resolve_type_annotation(var_decl->type);
    }
    
    LanguageType* init_type = nullptr;
    if (var_decl->initializer) {
        init_type = check_expression(var_decl->initializer);
    }
    
    LanguageType* final_type = nullptr;
    
    if (declared_type && init_type) {
        // Both declared and initialized - check compatibility
        if (is_type_compatible(declared_type, init_type)) {
            final_type = declared_type;
        } else {
            add_type_error(declared_type->to_string(), init_type->to_string(), var_decl->line);
            final_type = declared_type; // Use declared type anyway
        }
    } else if (declared_type) {
        // Only declared
        final_type = declared_type;
    } else if (init_type) {
        // Only initialized - infer type
        final_type = init_type;
    } else {
        // Neither - error
        add_error("Variable declaration without type or initializer", var_decl->line);
        final_type = type_system.get_string_type(); // Default
    }
    
    declare_variable(var_decl->name, final_type);
    
    // Set the inferred type on the variable declaration statement
    var_decl->inferred_type = final_type;
    
    return final_type;
}

LanguageType* TypeChecker::check_block_statement(std::shared_ptr<AST::BlockStatement> block) {
    if (!block) return nullptr;
    
    enter_scope();
    
    LanguageType* last_type = nullptr;
    for (const auto& stmt : block->statements) {
        last_type = check_statement(stmt);
    }
    
    exit_scope();
    
    // Set the inferred type on the block statement
    block->inferred_type = last_type;
    
    return last_type;
}

LanguageType* TypeChecker::check_if_statement(std::shared_ptr<AST::IfStatement> if_stmt) {
    if (!if_stmt) return nullptr;
    
    // Check condition
    LanguageType* condition_type = check_expression(if_stmt->condition);
    if (!is_boolean_type(condition_type)) {
        add_type_error("bool", condition_type->to_string(), if_stmt->condition->line);
    }
    
    // Check then branch
    check_statement(if_stmt->thenBranch);
    
    // Check else branch if present
    if (if_stmt->elseBranch) {
        check_statement(if_stmt->elseBranch);
    }
    
    // Set the inferred type on the if statement
    LanguageType* result_type = type_system.get_string_type(); // if statements don't produce a value
    if_stmt->inferred_type = result_type;
    
    return result_type;
}

LanguageType* TypeChecker::check_while_statement(std::shared_ptr<AST::WhileStatement> while_stmt) {
    if (!while_stmt) return nullptr;
    
    // Check condition
    LanguageType* condition_type = check_expression(while_stmt->condition);
    if (!is_boolean_type(condition_type)) {
        add_type_error("bool", condition_type->to_string(), while_stmt->condition->line);
    }
    
    // Check body
    bool was_in_loop = in_loop;
    in_loop = true;
    check_statement(while_stmt->body);
    in_loop = was_in_loop;
    
    // Set the inferred type on the while statement
    LanguageType* result_type = type_system.get_string_type();
    while_stmt->inferred_type = result_type;
    
    return result_type;
}

LanguageType* TypeChecker::check_for_statement(std::shared_ptr<AST::ForStatement> for_stmt) {
    if (!for_stmt) return nullptr;
    
    enter_scope();
    
    // Check initializer
    if (for_stmt->initializer) {
        check_statement(for_stmt->initializer);
    }
    
    // Check condition
    if (for_stmt->condition) {
        LanguageType* condition_type = check_expression(for_stmt->condition);
        if (!is_boolean_type(condition_type)) {
            add_type_error("bool", condition_type->to_string(), for_stmt->condition->line);
        }
    }
    
    // Check increment
    if (for_stmt->increment) {
        check_expression(for_stmt->increment);
    }
    
    // Check body
    bool was_in_loop = in_loop;
    in_loop = true;
    check_statement(for_stmt->body);
    in_loop = was_in_loop;
    
    exit_scope();
    
    // Set the inferred type on the for statement
    LanguageType* result_type = type_system.get_string_type();
    for_stmt->inferred_type = result_type;
    
    return result_type;
}

LanguageType* TypeChecker::check_return_statement(std::shared_ptr<AST::ReturnStatement> return_stmt) {
    if (!return_stmt) return nullptr;
    
    LanguageType* return_type = nullptr;
    if (return_stmt->value) {
        return_type = check_expression(return_stmt->value);
    } else {
        return_type = type_system.get_nil_type();
    }
    
    // Check if return type matches function return type
    if (current_return_type && !is_type_compatible(current_return_type, return_type)) {
        add_type_error(current_return_type->to_string(), return_type->to_string(), return_stmt->line);
    }
    
    // Set the inferred type on the return statement
    return_stmt->inferred_type = return_type;
    
    return return_type;
}

LanguageType* TypeChecker::check_print_statement(std::shared_ptr<AST::PrintStatement> print_stmt) {
    if (!print_stmt) return nullptr;
    
    for (const auto& arg : print_stmt->arguments) {
        check_expression(arg);
    }
    
    // Set the inferred type on the print statement
    LanguageType* result_type = type_system.get_string_type();
    print_stmt->inferred_type = result_type;
    
    return result_type;
}

LanguageType* TypeChecker::check_expression(std::shared_ptr<AST::Expression> expr) {
    if (!expr) return nullptr;
    
    LanguageType* type = nullptr;
    
    if (auto literal = std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) {
        type = check_literal_expr(literal);
    } else if (auto variable = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
        type = check_variable_expr(variable);
    } else if (auto binary = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
        type = check_binary_expr(binary);
    } else if (auto unary = std::dynamic_pointer_cast<AST::UnaryExpr>(expr)) {
        type = check_unary_expr(unary);
    } else if (auto call = std::dynamic_pointer_cast<AST::CallExpr>(expr)) {
        type = check_call_expr(call);
    } else if (auto assign = std::dynamic_pointer_cast<AST::AssignExpr>(expr)) {
        type = check_assign_expr(assign);
    } else if (auto grouping = std::dynamic_pointer_cast<AST::GroupingExpr>(expr)) {
        type = check_grouping_expr(grouping);
    } else if (auto member = std::dynamic_pointer_cast<AST::MemberExpr>(expr)) {
        type = check_member_expr(member);
    } else if (auto index = std::dynamic_pointer_cast<AST::IndexExpr>(expr)) {
        type = check_index_expr(index);
    } else if (auto list = std::dynamic_pointer_cast<AST::ListExpr>(expr)) {
        type = check_list_expr(list);
    } else if (auto tuple = std::dynamic_pointer_cast<AST::TupleExpr>(expr)) {
        type = check_tuple_expr(tuple);
    } else if (auto dict = std::dynamic_pointer_cast<AST::DictExpr>(expr)) {
        type = check_dict_expr(dict);
    } else if (auto interp_string = std::dynamic_pointer_cast<AST::InterpolatedStringExpr>(expr)) {
        type = check_interpolated_string_expr(interp_string);
    } else if (auto lambda = std::dynamic_pointer_cast<AST::LambdaExpr>(expr)) {
        type = check_lambda_expr(lambda);
    }
    
    // Set the inferred type on the expression
    expr->inferred_type = type;
    
    return type;
}

LanguageType* TypeChecker::check_literal_expr(std::shared_ptr<AST::LiteralExpr> expr) {
    if (!expr) return nullptr;
    
    if (std::holds_alternative<bool>(expr->value)) {
        return type_system.get_bool_type();
    } else if (std::holds_alternative<std::nullptr_t>(expr->value)) {
        return type_system.get_nil_type();
    } else if (std::holds_alternative<std::string>(expr->value)) {
        return type_system.get_string_type();
    }
    
    return type_system.get_string_type(); // Default
}

LanguageType* TypeChecker::check_variable_expr(std::shared_ptr<AST::VariableExpr> expr) {
    if (!expr) return nullptr;
    
    LanguageType* type = lookup_variable(expr->name);
    if (!type) {
        add_error("Undefined variable: " + expr->name, expr->line);
        return type_system.get_string_type(); // Default
    }
    
    return type;
}

LanguageType* TypeChecker::check_binary_expr(std::shared_ptr<AST::BinaryExpr> expr) {
    if (!expr) return nullptr;
    
    LanguageType* left_type = check_expression(expr->left);
    LanguageType* right_type = check_expression(expr->right);
    
    switch (expr->op) {
        case TokenType::PLUS:
        case TokenType::MINUS:
        case TokenType::MULTIPLY:
        case TokenType::DIVIDE:
            // Arithmetic operations
            if (is_numeric_type(left_type) && is_numeric_type(right_type)) {
                return promote_numeric_types(left_type, right_type);
            } else if (expr->op == TokenType::PLUS && 
                      (is_string_type(left_type) || is_string_type(right_type))) {
                return type_system.get_string_type();
            }
            add_error("Invalid operand types for arithmetic operation", expr->line);
            return type_system.get_int_type();
            
        case TokenType::EQUAL_EQUAL:
        case TokenType::BANG_EQUAL:
        case TokenType::LESS:
        case TokenType::LESS_EQUAL:
        case TokenType::GREATER:
        case TokenType::GREATER_EQUAL:
            // Comparison operations
            return type_system.get_bool_type();
            
        case TokenType::AND:
        case TokenType::OR:
            // Logical operations
            if (is_boolean_type(left_type) && is_boolean_type(right_type)) {
                return type_system.get_bool_type();
            }
            add_error("Logical operations require boolean operands", expr->line);
            return type_system.get_bool_type();
            
        default:
            add_error("Unsupported binary operator", expr->line);
            return type_system.get_string_type();
    }
}

LanguageType* TypeChecker::check_unary_expr(std::shared_ptr<AST::UnaryExpr> expr) {
    if (!expr) return nullptr;
    
    LanguageType* right_type = check_expression(expr->right);
    
    switch (expr->op) {
        case TokenType::BANG:
            // Logical NOT
            if (!is_boolean_type(right_type)) {
                add_type_error("bool", right_type->to_string(), expr->line);
            }
            return type_system.get_bool_type();
            
        case TokenType::MINUS:
            // Numeric negation
            if (!is_numeric_type(right_type)) {
                add_type_error("numeric", right_type->to_string(), expr->line);
            }
            return right_type;
            
        default:
            add_error("Unsupported unary operator", expr->line);
            return right_type;
    }
}

LanguageType* TypeChecker::check_call_expr(std::shared_ptr<AST::CallExpr> expr) {
    if (!expr) return nullptr;
    
    // Check callee
    LanguageType* callee_type = check_expression(expr->callee);
    
    // Check arguments
    std::vector<LanguageType*> arg_types;
    for (const auto& arg : expr->arguments) {
        arg_types.push_back(check_expression(arg));
    }
    
    // Check if callee is a function
    if (auto var_expr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->callee)) {
        LanguageType* result_type = nullptr;
        if (check_function_call(var_expr->name, arg_types, result_type)) {
            expr->inferred_type = result_type;
            return result_type;
        }
    }
    
    add_error("Cannot call non-function value", expr->line);
    return type_system.get_string_type();
}

LanguageType* TypeChecker::check_assign_expr(std::shared_ptr<AST::AssignExpr> expr) {
    if (!expr) return nullptr;
    
    LanguageType* value_type = check_expression(expr->value);
    
    // For simple variable assignment
    if (!expr->object && !expr->member && !expr->index) {
        LanguageType* var_type = lookup_variable(expr->name);
        if (var_type) {
            if (!is_type_compatible(var_type, value_type)) {
                add_type_error(var_type->to_string(), value_type->to_string(), expr->line);
            }
        } else {
            // Implicit variable declaration
            declare_variable(expr->name, value_type);
        }
    }
    
    return value_type;
}

LanguageType* TypeChecker::check_grouping_expr(std::shared_ptr<AST::GroupingExpr> expr) {
    if (!expr) return nullptr;
    return check_expression(expr->expression);
}

LanguageType* TypeChecker::check_member_expr(std::shared_ptr<AST::MemberExpr> expr) {
    if (!expr) return nullptr;
    
    LanguageType* object_type = check_expression(expr->object);
    
    // For now, assume all member access returns string
    // TODO: Implement proper class/struct type checking
    return type_system.get_string_type();
}

LanguageType* TypeChecker::check_index_expr(std::shared_ptr<AST::IndexExpr> expr) {
    if (!expr) return nullptr;
    
    LanguageType* object_type = check_expression(expr->object);
    LanguageType* index_type = check_expression(expr->index);
    
    // For now, assume all indexing returns string
    // TODO: Implement proper collection type checking
    return type_system.get_string_type();
}

LanguageType* TypeChecker::check_list_expr(std::shared_ptr<AST::ListExpr> expr) {
    if (!expr) return nullptr;
    
    LanguageType* element_type = nullptr;
    for (const auto& elem : expr->elements) {
        LanguageType* elem_type = check_expression(elem);
        if (element_type) {
            element_type = get_common_type(element_type, elem_type);
        } else {
            element_type = elem_type;
        }
    }
    
    // Create list type
    // TODO: Implement proper list type creation
    return type_system.get_string_type();
}

LanguageType* TypeChecker::check_tuple_expr(std::shared_ptr<AST::TupleExpr> expr) {
    if (!expr) return nullptr;
    
    for (const auto& elem : expr->elements) {
        check_expression(elem);
    }
    
    // TODO: Implement proper tuple type creation
    return type_system.get_string_type();
}

LanguageType* TypeChecker::check_dict_expr(std::shared_ptr<AST::DictExpr> expr) {
    if (!expr) return nullptr;
    
    for (const auto& [key, value] : expr->entries) {
        check_expression(key);
        check_expression(value);
    }
    
    // TODO: Implement proper dict type creation
    return type_system.get_string_type();
}

LanguageType* TypeChecker::check_interpolated_string_expr(std::shared_ptr<AST::InterpolatedStringExpr> expr) {
    if (!expr) return nullptr;
    
    for (const auto& part : expr->parts) {
        if (std::holds_alternative<std::shared_ptr<AST::Expression>>(part)) {
            check_expression(std::get<std::shared_ptr<AST::Expression>>(part));
        }
    }
    
    return type_system.get_string_type();
}

LanguageType* TypeChecker::check_lambda_expr(std::shared_ptr<AST::LambdaExpr> expr) {
    if (!expr) return nullptr;
    
    // TODO: Implement proper lambda type checking
    return type_system.get_string_type();
}

LanguageType* TypeChecker::resolve_type_annotation(std::shared_ptr<AST::TypeAnnotation> annotation) {
    if (!annotation) return nullptr;
    
    // Simple type resolution based on type name
    if (annotation->typeName == "int") {
        return type_system.get_int_type();
    } else if (annotation->typeName == "float") {
        return type_system.get_float_type();
    } else if (annotation->typeName == "bool") {
        return type_system.get_bool_type();
    } else if (annotation->typeName == "string") {
        return type_system.get_string_type();
    }
    
    // TODO: Implement more complex type resolution
    return type_system.get_string_type();
}

bool TypeChecker::is_type_compatible(LanguageType* expected, LanguageType* actual) {
    return type_system.are_compatible(expected, actual);
}

LanguageType* TypeChecker::get_common_type(LanguageType* left, LanguageType* right) {
    return type_system.get_common_type(left, right);
}

bool TypeChecker::can_implicitly_convert(LanguageType* from, LanguageType* to) {
    return TypeUtils::can_implicitly_convert(from, to);
}

bool TypeChecker::check_function_call(const std::string& func_name, 
                                     const std::vector<LanguageType*>& arg_types,
                                     LanguageType*& result_type) {
    auto it = function_signatures.find(func_name);
    if (it == function_signatures.end()) {
        add_error("Undefined function: " + func_name);
        return false;
    }
    
    const FunctionSignature& sig = it->second;
    
    if (!validate_argument_types(sig.param_types, arg_types, func_name)) {
        return false;
    }
    
    result_type = sig.return_type;
    return true;
}

bool TypeChecker::validate_argument_types(const std::vector<LanguageType*>& expected,
                                         const std::vector<LanguageType*>& actual,
                                         const std::string& func_name) {
    if (expected.size() != actual.size()) {
        add_error("Function " + func_name + " expects " + 
                 std::to_string(expected.size()) + " arguments, got " + 
                 std::to_string(actual.size()));
        return false;
    }
    
    for (size_t i = 0; i < expected.size(); ++i) {
        if (!is_type_compatible(expected[i], actual[i])) {
            add_error("Argument " + std::to_string(i + 1) + " of function " + 
                     func_name + " expects " + expected[i]->to_string() + 
                     ", got " + actual[i]->to_string());
            return false;
        }
    }
    
    return true;
}

bool TypeChecker::is_numeric_type(LanguageType* type) {
    return TypeUtils::is_numeric(type);
}

bool TypeChecker::is_boolean_type(LanguageType* type) {
    return type && type->tag == LanguageTypeTag::Bool;
}

bool TypeChecker::is_string_type(LanguageType* type) {
    return type && type->tag == LanguageTypeTag::String;
}

LanguageType* TypeChecker::promote_numeric_types(LanguageType* left, LanguageType* right) {
    return get_common_type(left, right);
}

// =============================================================================
// TYPE CHECKER FACTORY IMPLEMENTATION
// =============================================================================

namespace TypeCheckerFactory {

TypeCheckResult check_program(std::shared_ptr<AST::Program> program) {
    TypeSystem type_system;
    type_system.initialize_builtin_types();
    
    TypeChecker checker(type_system);
    bool success = checker.check_program(program);
    
    return TypeCheckResult(program, type_system, success, checker.get_errors());
}

std::unique_ptr<TypeChecker> create(TypeSystem& type_system) {
    return std::make_unique<TypeChecker>(type_system);
}

} // namespace TypeCheckerFactory

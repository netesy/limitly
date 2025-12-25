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
    program->inferred_type = type_system.NIL_TYPE; // Programs don't return values
    
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

void TypeChecker::declare_variable(const std::string& name, TypePtr type) {
    if (current_scope) {
        current_scope->declare(name, type);
    }
}

TypePtr TypeChecker::lookup_variable(const std::string& name) {
    return current_scope ? current_scope->lookup(name) : nullptr;
}

TypePtr TypeChecker::check_statement(std::shared_ptr<AST::Statement> stmt) {
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

TypePtr TypeChecker::check_function_declaration(std::shared_ptr<AST::FunctionDeclaration> func) {
    if (!func) return nullptr;
    
    // Resolve return type
    TypePtr return_type = type_system.STRING_TYPE; // Default
    if (func->returnType) {
        return_type = resolve_type_annotation(func->returnType.value());
    }
    
    // Create function signature
    FunctionSignature signature;
    signature.name = func->name;
    signature.return_type = return_type;
    signature.declaration = func;
    
    // Check parameters
    for (const auto& param : func->params) {
        TypePtr param_type = type_system.STRING_TYPE; // Default
        if (param.second) {
            param_type = resolve_type_annotation(param.second);
        }
        signature.param_types.push_back(param_type);
    }
    
    function_signatures[func->name] = signature;
    
    // Check function body
    current_function = func;
    current_return_type = return_type;
    enter_scope();
    
    // Declare parameters
    for (size_t i = 0; i < func->params.size(); ++i) {
        declare_variable(func->params[i].first, signature.param_types[i]);
    }
    
    // Check body
    TypePtr body_type = check_statement(func->body);
    
    exit_scope();
    current_function = nullptr;
    current_return_type = nullptr;
    
    // Set the inferred type on the function declaration
    func->inferred_type = return_type;
    
    return return_type;
}

TypePtr TypeChecker::check_var_declaration(std::shared_ptr<AST::VarDeclaration> var_decl) {
    if (!var_decl) return nullptr;
    
    TypePtr declared_type = nullptr;
    if (var_decl->type) {
        declared_type = resolve_type_annotation(var_decl->type.value());
    }
    
    TypePtr init_type = nullptr;
    if (var_decl->initializer) {
        init_type = check_expression(var_decl->initializer);
    }
    
    TypePtr final_type = nullptr;
    
    if (declared_type && init_type) {
        // Both declared and initialized - check compatibility
        if (is_type_compatible(declared_type, init_type)) {
            final_type = declared_type;
        } else {
            add_type_error(declared_type->toString(), init_type->toString(), var_decl->line);
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
        final_type = type_system.STRING_TYPE; // Default
    }
    
    declare_variable(var_decl->name, final_type);
    
    // Set the inferred type on the variable declaration statement
    var_decl->inferred_type = final_type;
    
    return final_type;
}

TypePtr TypeChecker::check_block_statement(std::shared_ptr<AST::BlockStatement> block) {
    if (!block) return nullptr;
    
    enter_scope();
    
    TypePtr last_type = nullptr;
    for (const auto& stmt : block->statements) {
        last_type = check_statement(stmt);
    }
    
    exit_scope();
    
    // Set the inferred type on the block statement
    block->inferred_type = last_type;
    
    return last_type;
}

TypePtr TypeChecker::check_if_statement(std::shared_ptr<AST::IfStatement> if_stmt) {
    if (!if_stmt) return nullptr;
    
    // Check condition
    TypePtr condition_type = check_expression(if_stmt->condition);
    if (!is_boolean_type(condition_type)) {
        add_type_error("bool", condition_type->toString(), if_stmt->condition->line);
    }
    
    // Check then branch
    check_statement(if_stmt->thenBranch);
    
    // Check else branch if present
    if (if_stmt->elseBranch) {
        check_statement(if_stmt->elseBranch);
    }
    
    // Set the inferred type on the if statement
    TypePtr result_type = type_system.STRING_TYPE; // if statements don't produce a value
    if_stmt->inferred_type = result_type;
    
    return result_type;
}

TypePtr TypeChecker::check_while_statement(std::shared_ptr<AST::WhileStatement> while_stmt) {
    if (!while_stmt) return nullptr;
    
    // Check condition
    TypePtr condition_type = check_expression(while_stmt->condition);
    if (!is_boolean_type(condition_type)) {
        add_type_error("bool", condition_type->toString(), while_stmt->condition->line);
    }
    
    // Check body
    bool was_in_loop = in_loop;
    in_loop = true;
    check_statement(while_stmt->body);
    in_loop = was_in_loop;
    
    // Set the inferred type on the while statement
    TypePtr result_type = type_system.STRING_TYPE;
    while_stmt->inferred_type = result_type;
    
    return result_type;
}

TypePtr TypeChecker::check_for_statement(std::shared_ptr<AST::ForStatement> for_stmt) {
    if (!for_stmt) return nullptr;
    
    enter_scope();
    
    // Check initializer
    if (for_stmt->initializer) {
        check_statement(for_stmt->initializer);
    }
    
    // Check condition
    if (for_stmt->condition) {
        TypePtr condition_type = check_expression(for_stmt->condition);
        if (!is_boolean_type(condition_type)) {
            add_type_error("bool", condition_type->toString(), for_stmt->condition->line);
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
    TypePtr result_type = type_system.STRING_TYPE;
    for_stmt->inferred_type = result_type;
    
    return result_type;
}

TypePtr TypeChecker::check_return_statement(std::shared_ptr<AST::ReturnStatement> return_stmt) {
    if (!return_stmt) return nullptr;
    
    TypePtr return_type = nullptr;
    if (return_stmt->value) {
        return_type = check_expression(return_stmt->value);
    } else {
        return_type = type_system.NIL_TYPE;
    }
    
    // Check if return type matches function return type
    if (current_return_type && !is_type_compatible(current_return_type, return_type)) {
        add_type_error(current_return_type->toString(), return_type->toString(), return_stmt->line);
    }
    
    // Set the inferred type on the return statement
    return_stmt->inferred_type = return_type;
    
    return return_type;
}

TypePtr TypeChecker::check_print_statement(std::shared_ptr<AST::PrintStatement> print_stmt) {
    if (!print_stmt) return nullptr;
    
    for (const auto& arg : print_stmt->arguments) {
        check_expression(arg);
    }
    
    // Set the inferred type on the print statement
    TypePtr result_type = type_system.STRING_TYPE;
    print_stmt->inferred_type = result_type;
    
    return result_type;
}

TypePtr TypeChecker::check_expression(std::shared_ptr<AST::Expression> expr) {
    if (!expr) return nullptr;
    
    TypePtr type = nullptr;
    
    if (auto literal = std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) {
        type = check_literal_expr(literal);
    } else if (auto call = std::dynamic_pointer_cast<AST::CallExpr>(expr)) {
        type = check_call_expr(call);
    } else if (auto variable = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) {
        type = check_variable_expr(variable);
    } else if (auto binary = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) {
        type = check_binary_expr(binary);
    } else if (auto unary = std::dynamic_pointer_cast<AST::UnaryExpr>(expr)) {
        type = check_unary_expr(unary);
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
    } else if (auto interpolated = std::dynamic_pointer_cast<AST::InterpolatedStringExpr>(expr)) {
        type = check_interpolated_string_expr(interpolated);
    } else if (auto lambda = std::dynamic_pointer_cast<AST::LambdaExpr>(expr)) {
        type = check_lambda_expr(lambda);
    } else {
        add_error("Unknown expression type", expr->line);
        type = type_system.STRING_TYPE; // Default fallback
    }
    
    // Set the inferred type on the expression node
    expr->inferred_type = type;
    
    return type;
}

TypePtr TypeChecker::check_literal_expr(std::shared_ptr<AST::LiteralExpr> expr) {
    if (!expr) return nullptr;
    
    // Set type based on the literal value
    if (std::holds_alternative<std::string>(expr->value)) {
        // Check if it's a numeric string
        const std::string& str = std::get<std::string>(expr->value);
        bool is_numeric = !str.empty() && (str[0] == '-' || str[0] == '+' || 
                          (str[0] >= '0' && str[0] <= '9'));
        for (size_t i = 1; i < str.size() && is_numeric; i++) {
            if (str[i] != '.' && !(str[i] >= '0' && str[i] <= '9')) {
                is_numeric = false;
            }
        }
        
        if (is_numeric) {
            // Check if it contains a decimal point to determine if it's a float
            bool is_float = false;
            for (size_t i = 0; i < str.size(); i++) {
                if (str[i] == '.') {
                    is_float = true;
                    break;
                }
            }
            
            if (is_float) {
                expr->inferred_type = type_system.FLOAT64_TYPE;
                return type_system.FLOAT64_TYPE;
            } else {
                expr->inferred_type = type_system.INT64_TYPE;
                return type_system.INT64_TYPE;
            }
        } else {
            expr->inferred_type = type_system.STRING_TYPE;
            return type_system.STRING_TYPE;
        }
    } else if (std::holds_alternative<bool>(expr->value)) {
        expr->inferred_type = type_system.BOOL_TYPE;
        return type_system.BOOL_TYPE;
    } else if (std::holds_alternative<std::nullptr_t>(expr->value)) {
        expr->inferred_type = type_system.NIL_TYPE;
        return type_system.NIL_TYPE;
    }
    
    expr->inferred_type = type_system.STRING_TYPE;
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_variable_expr(std::shared_ptr<AST::VariableExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr type = lookup_variable(expr->name);
    if (!type) {
        add_error("Undefined variable: " + expr->name, expr->line);
        return type_system.STRING_TYPE; // Default
    }
    
    return type;
}

TypePtr TypeChecker::check_binary_expr(std::shared_ptr<AST::BinaryExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr left_type = check_expression(expr->left);
    TypePtr right_type = check_expression(expr->right);
    
    switch (expr->op) {
        case TokenType::PLUS:
        case TokenType::MINUS:
        case TokenType::STAR:
        case TokenType::SLASH:
            // Arithmetic operations
            if (is_numeric_type(left_type) && is_numeric_type(right_type)) {
                return promote_numeric_types(left_type, right_type);
            } else if (expr->op == TokenType::PLUS && 
                      (is_string_type(left_type) || is_string_type(right_type))) {
                return type_system.STRING_TYPE;
            }
            add_error("Invalid operand types for arithmetic operation", expr->line);
            return type_system.INT_TYPE;
            
        case TokenType::EQUAL_EQUAL:
        case TokenType::BANG_EQUAL:
        case TokenType::LESS:
        case TokenType::LESS_EQUAL:
        case TokenType::GREATER:
        case TokenType::GREATER_EQUAL:
            // Comparison operations
            return type_system.BOOL_TYPE;
            
        case TokenType::AND:
        case TokenType::OR:
            // Logical operations
            if (is_boolean_type(left_type) && is_boolean_type(right_type)) {
                return type_system.BOOL_TYPE;
            }
            add_error("Logical operations require boolean operands", expr->line);
            return type_system.BOOL_TYPE;
            
        case TokenType::MODULUS:
        case TokenType::POWER:
            if (is_numeric_type(left_type) && is_numeric_type(right_type)) {
                return promote_numeric_types(left_type, right_type);
            }
            add_error("Invalid operand types for arithmetic operation", expr->line);
            return type_system.INT_TYPE;
        default:
            add_error("Unsupported binary operator", expr->line);
            return type_system.STRING_TYPE;
    }
}

TypePtr TypeChecker::check_unary_expr(std::shared_ptr<AST::UnaryExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr right_type = check_expression(expr->right);
    
    switch (expr->op) {
        case TokenType::BANG:
            // Logical NOT
            if (!is_boolean_type(right_type)) {
                add_type_error("bool", right_type->toString(), expr->line);
            }
            return type_system.BOOL_TYPE;
            
        case TokenType::MINUS:
        case TokenType::PLUS:
            // Numeric negation
            if (!is_numeric_type(right_type)) {
                add_type_error("numeric", right_type->toString(), expr->line);
            }
            return right_type;
            
        default:
            add_error("Unsupported unary operator", expr->line);
            return right_type;
    }
}

TypePtr TypeChecker::check_call_expr(std::shared_ptr<AST::CallExpr> expr) {
    if (!expr) return nullptr;
    
    // Check arguments first
    std::vector<TypePtr> arg_types;
    for (const auto& arg : expr->arguments) {
        arg_types.push_back(check_expression(arg));
    }
    
    // Check if callee is a function (before checking the callee as an expression)
    if (auto var_expr = std::dynamic_pointer_cast<AST::VariableExpr>(expr->callee)) {
        TypePtr result_type = nullptr;
        if (check_function_call(var_expr->name, arg_types, result_type)) {
            expr->inferred_type = result_type;
            return result_type;
        }
    }
    
    // If not a known function, check the callee as an expression
    TypePtr callee_type = check_expression(expr->callee);
    
    add_error("Cannot call non-function value", expr->line);
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_assign_expr(std::shared_ptr<AST::AssignExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr value_type = check_expression(expr->value);
    
    // For simple variable assignment
    if (!expr->object && !expr->member && !expr->index) {
        TypePtr var_type = lookup_variable(expr->name);
        if (var_type) {
            if (!is_type_compatible(var_type, value_type)) {
                add_type_error(var_type->toString(), value_type->toString(), expr->line);
            }
        } else {
            // Implicit variable declaration
            declare_variable(expr->name, value_type);
        }
    }
    
    return value_type;
}

TypePtr TypeChecker::check_grouping_expr(std::shared_ptr<AST::GroupingExpr> expr) {
    if (!expr) return nullptr;
    return check_expression(expr->expression);
}

TypePtr TypeChecker::check_member_expr(std::shared_ptr<AST::MemberExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr object_type = check_expression(expr->object);
    
    // For now, assume all member access returns string
    // TODO: Implement proper class/struct type checking
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_index_expr(std::shared_ptr<AST::IndexExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr object_type = check_expression(expr->object);
    TypePtr index_type = check_expression(expr->index);
    
    // For now, assume all indexing returns string
    // TODO: Implement proper collection type checking
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_list_expr(std::shared_ptr<AST::ListExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr element_type = nullptr;
    for (const auto& elem : expr->elements) {
        TypePtr elem_type = check_expression(elem);
        if (element_type) {
            element_type = get_common_type(element_type, elem_type);
        } else {
            element_type = elem_type;
        }
    }
    
    // Create list type
    // TODO: Implement proper list type creation
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_tuple_expr(std::shared_ptr<AST::TupleExpr> expr) {
    if (!expr) return nullptr;
    
    for (const auto& elem : expr->elements) {
        check_expression(elem);
    }
    
    // TODO: Implement proper tuple type creation
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_dict_expr(std::shared_ptr<AST::DictExpr> expr) {
    if (!expr) return nullptr;
    
    for (const auto& [key, value] : expr->entries) {
        check_expression(key);
        check_expression(value);
    }
    
    // TODO: Implement proper dict type creation
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_interpolated_string_expr(std::shared_ptr<AST::InterpolatedStringExpr> expr) {
    if (!expr) return nullptr;
    
    for (const auto& part : expr->parts) {
        if (std::holds_alternative<std::shared_ptr<AST::Expression>>(part)) {
            check_expression(std::get<std::shared_ptr<AST::Expression>>(part));
        }
    }
    
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_lambda_expr(std::shared_ptr<AST::LambdaExpr> expr) {
    if (!expr) return nullptr;
    
    // TODO: Implement proper lambda type checking
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::resolve_type_annotation(std::shared_ptr<AST::TypeAnnotation> annotation) {
    if (!annotation) return nullptr;
    
    // Simple type resolution based on type name
    if (annotation->typeName == "int") {
        return type_system.INT_TYPE;
    } else if (annotation->typeName == "i64") {
        return type_system.INT64_TYPE;
    } else if (annotation->typeName == "float") {
        return type_system.FLOAT64_TYPE;
    } else if (annotation->typeName == "bool") {
        return type_system.BOOL_TYPE;
    } else if (annotation->typeName == "string") {
        return type_system.STRING_TYPE;
    } else if (annotation->typeName == "atomic") {
        // atomic is an alias for i64
        return type_system.INT64_TYPE;
    } else if (annotation->typeName == "channel") {
        // channel type is represented as i64 (channel handle)
        return type_system.INT64_TYPE;
    }
    
    // TODO: Implement more complex type resolution
    return type_system.STRING_TYPE;
}

bool TypeChecker::is_type_compatible(TypePtr expected, TypePtr actual) {
    return type_system.isCompatible(expected, actual);
}

TypePtr TypeChecker::get_common_type(TypePtr left, TypePtr right) {
    return type_system.getCommonType(left, right);
}

bool TypeChecker::can_implicitly_convert(TypePtr from, TypePtr to) {
    // Simple conversion check - can be expanded later
    if (!from || !to) return false;
    if (from == to) return true;
    if (to->tag == TypeTag::Any) return true;
    
    // Numeric conversions
    bool from_is_numeric = (from->tag == TypeTag::Int || from->tag == TypeTag::Int8 || 
                           from->tag == TypeTag::Int16 || from->tag == TypeTag::Int32 || 
                           from->tag == TypeTag::Int64 || from->tag == TypeTag::Int128 ||
                           from->tag == TypeTag::UInt || from->tag == TypeTag::UInt8 || 
                           from->tag == TypeTag::UInt16 || from->tag == TypeTag::UInt32 || 
                           from->tag == TypeTag::UInt64 || from->tag == TypeTag::UInt128 ||
                           from->tag == TypeTag::Float32 || from->tag == TypeTag::Float64);
    
    bool to_is_numeric = (to->tag == TypeTag::Int || to->tag == TypeTag::Int8 || 
                         to->tag == TypeTag::Int16 || to->tag == TypeTag::Int32 || 
                         to->tag == TypeTag::Int64 || to->tag == TypeTag::Int128 ||
                         to->tag == TypeTag::UInt || to->tag == TypeTag::UInt8 || 
                         to->tag == TypeTag::UInt16 || to->tag == TypeTag::UInt32 || 
                         to->tag == TypeTag::UInt64 || to->tag == TypeTag::UInt128 ||
                         to->tag == TypeTag::Float32 || to->tag == TypeTag::Float64);
    
    return from_is_numeric && to_is_numeric;
}

bool TypeChecker::check_function_call(const std::string& func_name, 
                                     const std::vector<TypePtr>& arg_types,
                                     TypePtr& result_type) {
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

bool TypeChecker::validate_argument_types(const std::vector<TypePtr>& expected,
                                         const std::vector<TypePtr>& actual,
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
                     func_name + " expects " + expected[i]->toString() +
                     ", got " + actual[i]->toString());
            return false;
        }
    }
    
    return true;
}

bool TypeChecker::is_numeric_type(TypePtr type) {
    return type && (type->tag == TypeTag::Int || type->tag == TypeTag::Int8 || 
                   type->tag == TypeTag::Int16 || type->tag == TypeTag::Int32 || 
                   type->tag == TypeTag::Int64 || type->tag == TypeTag::Int128 ||
                   type->tag == TypeTag::UInt || type->tag == TypeTag::UInt8 || 
                   type->tag == TypeTag::UInt16 || type->tag == TypeTag::UInt32 || 
                   type->tag == TypeTag::UInt64 || type->tag == TypeTag::UInt128 ||
                   type->tag == TypeTag::Float32 || type->tag == TypeTag::Float64);
}

bool TypeChecker::is_boolean_type(TypePtr type) {
    return type && type->tag == TypeTag::Bool;
}

bool TypeChecker::is_string_type(TypePtr type) {
    return type && type->tag == TypeTag::String;
}

TypePtr TypeChecker::promote_numeric_types(TypePtr left, TypePtr right) {
    return get_common_type(left, right);
}

void TypeChecker::register_builtin_function(const std::string& name, 
                                            const std::vector<TypePtr>& param_types,
                                            TypePtr return_type) {
    FunctionSignature sig;
    sig.name = name;
    sig.param_types = param_types;
    sig.return_type = return_type;
    sig.declaration = nullptr; // Builtin functions have no declaration
    
    function_signatures[name] = sig;
}

// =============================================================================
// TYPE CHECKER FACTORY IMPLEMENTATION
// =============================================================================

namespace TypeCheckerFactory {

TypeCheckResult check_program(std::shared_ptr<AST::Program> program) {
    // Create memory manager and region for type system
    static MemoryManager<> memoryManager;
    static MemoryManager<>::Region memoryRegion(memoryManager);
    static TypeSystem type_system(memoryManager, memoryRegion);
    auto checker = create(type_system);
    
    TypeCheckResult result(program, type_system, checker->check_program(program), checker->get_errors());
    
    return result;
}

std::unique_ptr<TypeChecker> create(TypeSystem& type_system) {
    auto checker = std::make_unique<TypeChecker>(type_system);
    
    // Register builtin functions
    register_builtin_functions(*checker);
    
    return checker;
}

void register_builtin_functions(TypeChecker& checker) {
    // Register channel() function
    checker.register_builtin_function("channel", {}, checker.get_type_system().INT_TYPE);
    
    // Add more builtin functions here as needed
}

} // namespace TypeCheckerFactory

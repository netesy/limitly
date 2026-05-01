#include "../type_checker.hh"
#include "../../error/debugger.hh"

using namespace LM::Frontend;

namespace LM {
namespace Frontend {
using namespace LM::Error;

// =============================================================================
// ERROR REPORTING AND UTILITIES
// =============================================================================

std::string TypeChecker::get_code_context(int line) {
    if (current_source.empty() || line <= 0) {
        return "";
    }
    
    std::istringstream stream(current_source);
    std::string currentLine;
    int currentLineNumber = 1;
    
    // Find the target line
    while (std::getline(stream, currentLine) && currentLineNumber < line) {
        currentLineNumber++;
    }
    
    if (currentLineNumber == line) {
        return currentLine;
    }
    
    return "";
}

void TypeChecker::check_assert_call(const std::shared_ptr<LM::Frontend::AST::CallExpr>& expr) {
    if (expr->arguments.size() != 2) {
        add_error("assert() expects exactly 2 arguments: condition (bool) and message (string), got " + 
                std::to_string(expr->arguments.size()), expr->line, 0, 
                get_code_context(expr->line), "assert(...)", "assert(condition, message)");
        return;
    }
    
    // Check first argument (condition) is boolean
    TypePtr conditionType = check_expression(expr->arguments[0]);
    if (!is_boolean_type(conditionType) && conditionType->tag != TypeTag::Any) {
        add_error("assert() first argument must be boolean, got " + conditionType->toString(), 
                expr->line, 0, get_code_context(expr->line), "condition", "boolean expression");
    }
    
    // Check second argument (message) is string
    TypePtr messageType = check_expression(expr->arguments[1]);
    if (!is_string_type(messageType) && messageType->tag != TypeTag::Any) {
        add_error("assert() second argument must be string, got " + messageType->toString(), 
                expr->line, 0, get_code_context(expr->line), "message", "string literal or expression");
    }
}

// =============================================================================
// FUNCTION CALL VALIDATION
// =============================================================================

bool TypeChecker::check_function_call(const std::string& func_name, 
                                     const std::vector<TypePtr>& arg_types,
                                     TypePtr& result_type,
                                     int line) {
    auto it = function_signatures.find(func_name);
    if (it == function_signatures.end()) {
        add_error("Undefined function: " + func_name, line);
        return false;
    }
    
    const auto& sig = it->second;
    
    // Check argument count
    size_t required_args = 0;
    for (size_t i = 0; i < sig.optional_params.size(); ++i) {
        if (!sig.optional_params[i]) {
            required_args++;
        }
    }
    
    if (arg_types.size() < required_args || arg_types.size() > sig.param_types.size()) {
        add_error("Function '" + func_name + "' expects " + std::to_string(required_args) + 
                 " to " + std::to_string(sig.param_types.size()) + " arguments, got " + 
                 std::to_string(arg_types.size()), line);
        return false;
    }
    
    // Check argument types
    if (!validate_argument_types(sig.param_types, arg_types, func_name)) {
        return false;
    }
    
    result_type = sig.return_type;
    return true;
}

bool TypeChecker::validate_argument_types(const std::vector<TypePtr>& expected,
                                         const std::vector<TypePtr>& actual,
                                         const std::string& func_name) {
    for (size_t i = 0; i < actual.size(); ++i) {
        if (i >= expected.size()) {
            add_error("Too many arguments for function '" + func_name + "'");
            return false;
        }
        
        if (!is_type_compatible(expected[i], actual[i])) {
            add_error("Argument " + std::to_string(i + 1) + " type mismatch in call to '" + func_name + 
                     "': expected " + expected[i]->toString() + ", got " + actual[i]->toString());
            return false;
        }
    }
    
    return true;
}

// =============================================================================
// CONTROL FLOW CHECKING
// =============================================================================

void TypeChecker::check_return_statement(TypePtr return_type, int line) {
    if (!current_return_type) {
        add_error("Return statement outside of function", line);
        return;
    }
    
    if (!is_type_compatible(current_return_type, return_type)) {
        add_error("Return type mismatch: expected " + current_return_type->toString() + 
                 ", got " + return_type->toString(), line);
    }
}

void TypeChecker::check_break_statement(int line) {
    if (!in_loop) {
        add_error("Break statement outside of loop", line);
    }
}

void TypeChecker::check_continue_statement(int line) {
    if (!in_loop) {
        add_error("Continue statement outside of loop", line);
    }
}

// =============================================================================
// VISIBILITY CHECKING
// =============================================================================

bool TypeChecker::is_visible(const std::string& frame_name, LM::Frontend::AST::VisibilityLevel visibility, int line) {
    // Public and Const are always visible
    if (visibility == LM::Frontend::AST::VisibilityLevel::Public ||
        visibility == LM::Frontend::AST::VisibilityLevel::Const) {
        return true;
    }
    
    // Private is only visible within the same frame
    if (visibility == LM::Frontend::AST::VisibilityLevel::Private) {
        return current_frame && current_frame->name == frame_name;
    }
    
    // Protected is visible in the same frame and derived frames
    if (visibility == LM::Frontend::AST::VisibilityLevel::Protected) {
        if (current_frame && current_frame->name == frame_name) {
            return true;
        }
        // Check if current frame derives from frame_name
        // This would require tracking inheritance relationships
        return false;
    }
    
    return false;
}

// =============================================================================
// ERROR TYPE INFERENCE
// =============================================================================

std::vector<std::string> TypeChecker::infer_function_error_types(const std::shared_ptr<LM::Frontend::AST::Statement>& body) {
    std::vector<std::string> error_types;
    if (!body) return error_types;
    
    // Infer error types from function body
    if (auto block = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(body)) {
        for (const auto& stmt : block->statements) {
            auto stmt_errors = infer_expression_error_types(nullptr);
            error_types.insert(error_types.end(), stmt_errors.begin(), stmt_errors.end());
        }
    }
    
    return error_types;
}

std::vector<std::string> TypeChecker::infer_expression_error_types(const std::shared_ptr<LM::Frontend::AST::Expression>& expr) {
    std::vector<std::string> error_types;
    if (!expr) return error_types;
    
    // Infer error types from expression
    if (auto call = std::dynamic_pointer_cast<LM::Frontend::AST::CallExpr>(expr)) {
        // Get function name from call expression
        std::string func_name;
        if (auto var = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(call->callee)) {
            func_name = var->name;
        }
        
        if (!func_name.empty()) {
            auto it = function_signatures.find(func_name);
            if (it != function_signatures.end()) {
                error_types = it->second.error_types;
            }
        }
    }
    
    return error_types;
}

bool TypeChecker::can_function_produce_error_type(const std::shared_ptr<LM::Frontend::AST::Statement>& body, const std::string& error_type) {
    if (!body) return false;
    
    // Check if function body can produce the given error type
    auto inferred = infer_function_error_types(body);
    return std::find(inferred.begin(), inferred.end(), error_type) != inferred.end();
}

bool TypeChecker::can_propagate_error(const std::vector<std::string>& source_errors, const std::vector<std::string>& target_errors) {
    // Check if all source errors are in target errors
    for (const auto& source_error : source_errors) {
        if (std::find(target_errors.begin(), target_errors.end(), source_error) == target_errors.end()) {
            return false;
        }
    }
    return true;
}

bool TypeChecker::is_error_union_compatible(TypePtr from, TypePtr to) {
    if (!from || !to) return false;
    
    // Check if from error union is compatible with to error union
    if (from->tag != TypeTag::ErrorUnion || to->tag != TypeTag::ErrorUnion) {
        return false;
    }
    
    // For now, just check if they're the same type
    return from->toString() == to->toString();
}

std::string TypeChecker::join_error_types(const std::vector<std::string>& error_types) {
    if (error_types.empty()) return "";
    
    std::string result = error_types[0];
    for (size_t i = 1; i < error_types.size(); ++i) {
        result += " | " + error_types[i];
    }
    return result;
}

// =============================================================================
// LAMBDA TYPE INFERENCE
// =============================================================================

TypePtr TypeChecker::infer_lambda_return_type(const std::shared_ptr<LM::Frontend::AST::Statement>& body) {
    if (!body) return type_system.NIL_TYPE;
    
    // Infer return type from lambda body
    if (auto block = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(body)) {
        if (!block->statements.empty()) {
            // Return type of last statement
            return check_statement(block->statements.back());
        }
    }
    
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::infer_literal_type(const std::shared_ptr<LM::Frontend::AST::LiteralExpr>& expr, TypePtr expected_type) {
    if (!expr) return type_system.ANY_TYPE;
    
    // Infer type from literal value - LiteralExpr stores value as a variant
    // For now, return ANY_TYPE as we need to check the actual AST structure
    return type_system.ANY_TYPE;
}

bool TypeChecker::should_capture_variable(const std::string& name) {
    // Check if variable should be captured in lambda
    // For now, capture all non-local variables
    return lookup_variable(name) != nullptr;
}

} // namespace Frontend
} // namespace LM

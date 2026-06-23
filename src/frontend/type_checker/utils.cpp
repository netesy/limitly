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
// CONTROL FLOW CHECKING
//
// NOTE: check_function_call and validate_argument_types live in types.cpp
// (the canonical TU for type validation); do not redefine them here.
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

    // Private and Protected require being inside the frame or a subtype
    if (!current_frame) {
        return false;
    }

    // Check if we are inside the same frame
    if (current_frame->name == frame_name) {
        return true;
    }

    // Protected allows access from related frames (those sharing traits)
    if (visibility == LM::Frontend::AST::VisibilityLevel::Protected) {
        auto target_info = type_system.getFrameInfo(frame_name);
        auto current_info = type_system.getFrameInfo(current_frame->name);

        if (target_info && current_info) {
            // Check if current frame inherits from target frame
            if (target_info->name == current_info->name) return true;
            for (const auto& trait_a : target_info->implements) {
                for (const auto& trait_b : current_info->implements) {
                    if (trait_a == trait_b) return true;
                }
            }
        }
        return false;
    }
    return false;
}

// =============================================================================
// ERROR TYPE INFERENCE & LAMBDA/LITERAL TYPE INFERENCE
//
// These helpers (infer_function_error_types, infer_expression_error_types,
// can_function_produce_error_type, can_propagate_error,
// is_error_union_compatible, join_error_types, infer_lambda_return_type,
// infer_literal_type) are defined in their canonical TUs (types.cpp and
// patterns.cpp respectively). They must NOT be redefined here.
// =============================================================================

} // namespace Frontend
} // namespace LM

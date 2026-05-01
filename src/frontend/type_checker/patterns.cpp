#include "../type_checker.hh"

using namespace LM::Frontend;

namespace LM {
namespace Frontend {

void TypeChecker::validate_pattern_compatibility(std::shared_ptr<LM::Frontend::AST::Expression> pattern_node, TypePtr match_type, int line) {
    // Basic pattern compatibility validation
    if (!pattern_node || !match_type) {
        return;
    }
    
    if (auto bindingPattern = std::dynamic_pointer_cast<LM::Frontend::AST::BindingPatternExpr>(pattern_node)) {
        // Check if binding pattern is compatible with match type
        if (bindingPattern->typeName == "val") {
            // val pattern expects success type
            if (is_error_union_type(match_type)) {
                auto* errorUnionPtr = std::get_if<ErrorUnionType>(&match_type->extra);
                if (errorUnionPtr && !bindingPattern->variableNames.empty()) {
                    auto& errorUnion = *errorUnionPtr;
                    // Register the success value binding
                    declare_variable(bindingPattern->variableNames[0], errorUnion.successType);
                }
            } else {
                add_error("val pattern can only be used with error union types", line);
            }
        } else if (bindingPattern->typeName == "err") {
            // err pattern expects error type
            if (!is_error_union_type(match_type)) {
                add_error("err pattern can only be used with error union types", line);
            } else if (!bindingPattern->variableNames.empty()) {
                // Register the error value binding
                declare_variable(bindingPattern->variableNames[0], type_system.NIL_TYPE);
            }
        } else {
            bool variant_resolved = false;
            // 1. Resolve via qualified name or global lookup
            TypePtr constructorType = lookup_variable(bindingPattern->typeName);
            if (!constructorType) {
                auto it = variable_types.find(bindingPattern->typeName);
                if (it != variable_types.end()) {
                    constructorType = it->second;
                }
            }

            // 2. Resolve via expected enum type context (if name is just "Move")
            if (!constructorType && match_type && match_type->tag == TypeTag::Enum) {
                if (auto* et = std::get_if<EnumType>(&match_type->extra)) {
                    std::string qualified = et->name + "." + bindingPattern->typeName;
                    auto it = variable_types.find(qualified);
                    if (it != variable_types.end()) constructorType = it->second;
                }
            }

            if (constructorType) {
                if (constructorType->tag == TypeTag::Function) {
                    auto* funcType = std::get_if<FunctionType>(&constructorType->extra);
                    if (funcType) {
                        if (bindingPattern->variableNames.size() != funcType->paramTypes.size()) {
                            add_error("Pattern '" + bindingPattern->typeName + "' expects " +
                                      std::to_string(funcType->paramTypes.size()) + " values, but found " +
                                      std::to_string(bindingPattern->variableNames.size()), line);
                        } else {
                            for (size_t i = 0; i < bindingPattern->variableNames.size(); ++i) {
                                declare_variable(bindingPattern->variableNames[i], funcType->paramTypes[i]);
                            }
                        }
                        variant_resolved = true;
                    }
                } else if (constructorType->tag == TypeTag::Enum) {
                    if (!bindingPattern->variableNames.empty()) {
                        add_error("Unit variant '" + bindingPattern->typeName + "' cannot have associated values", line);
                    }
                    variant_resolved = true;
                }
            }

            if (!variant_resolved) {
                add_error("Unknown pattern or constructor: " + bindingPattern->typeName, line);
            }
        }
    } else if (auto memberExpr = std::dynamic_pointer_cast<LM::Frontend::AST::MemberExpr>(pattern_node)) {
        TypePtr patternType = check_member_expr(memberExpr);
        if (!is_type_compatible(patternType, match_type)) {
            add_error("Pattern " + patternType->toString() + " does not match match type " + match_type->toString(), line);
        }
    } else if (auto varExpr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(pattern_node)) {
        // Handle variable binding patterns
        if (varExpr->name == "_") {
            // Wildcard pattern - always compatible
            return;
        }
        
        // Check if this is a qualified variant (e.g., Status.Active)
        if (varExpr->name.find('.') != std::string::npos) {
            // Qualified variant pattern
            TypePtr patternType = check_variable_expr(varExpr, match_type);
            if (patternType && !is_type_compatible(patternType, match_type)) {
                add_error("Pattern " + patternType->toString() + " does not match match type " + match_type->toString(), line);
            }
        } else {
            // Simple variable binding pattern - bind the matched value to this variable
            declare_variable(varExpr->name, match_type);
        }
    } else if (auto typePattern = std::dynamic_pointer_cast<LM::Frontend::AST::TypePatternExpr>(pattern_node)) {
        // Type pattern - check compatibility
        if (typePattern->type) {
            TypePtr patternType = resolve_type_annotation(typePattern->type);
            if (!is_type_compatible(patternType, match_type)) {
                add_error("Type pattern type " + patternType->toString() + " does not match match type " + match_type->toString(), line);
            }
        }
    } else if (auto literalPattern = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(pattern_node)) {
        // Literal pattern - check compatibility
        if (std::holds_alternative<std::nullptr_t>(literalPattern->value)) {
            // Wildcard pattern - always compatible
            return;
        }
        TypePtr literalType = check_literal_expr(literalPattern);
        if (!is_type_compatible(literalType, match_type)) {
            add_error("Literal pattern type " + literalType->toString() + " does not match match type " + match_type->toString(), line);
        }
    }
    // Add more pattern type checks as needed
}

// =============================================================================
// ENHANCED TYPE INFERENCE METHODS
// =============================================================================

TypePtr TypeChecker::infer_lambda_return_type(const std::shared_ptr<LM::Frontend::AST::Statement>& body) {
    // Try to infer return type from lambda body
    if (!body) {
        return type_system.NIL_TYPE;
    }
    
    // If body is a block statement, look for return statements
    if (auto blockStmt = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(body)) {
        std::vector<TypePtr> returnTypes;
        
        for (const auto& stmt : blockStmt->statements) {
            if (auto returnStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ReturnStatement>(stmt)) {
                if (returnStmt->value) {
                    TypePtr returnType = check_expression(returnStmt->value);
                    returnTypes.push_back(returnType);
                } else {
                    returnTypes.push_back(type_system.NIL_TYPE);
                }
            }
        }
        
        // If we found return statements, try to find common type
        if (!returnTypes.empty()) {
            TypePtr commonType = returnTypes[0];
            for (size_t i = 1; i < returnTypes.size(); ++i) {
                try {
                    commonType = get_common_type(commonType, returnTypes[i]);
                } catch (const std::exception&) {
                    // If types are incompatible, fall back to ANY_TYPE
                    return type_system.ANY_TYPE;
                }
            }
            return commonType;
        }
        
        // No explicit return statements found, assume NIL return
        return type_system.NIL_TYPE;
    }
    
    // If body is an expression statement, infer from expression
    if (auto exprStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(body)) {
        return check_expression(exprStmt->expression);
    }
    
    // For other statement types, assume NIL return
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::infer_literal_type(const std::shared_ptr<LM::Frontend::AST::LiteralExpr>& expr, TypePtr expected_type) {
    if (!expr) return nullptr;
    
    // Handle string-based literal values with enhanced type inference
    if (std::holds_alternative<std::string>(expr->value)) {
        std::string stringValue = std::get<std::string>(expr->value);
        
        // Try to determine if this string represents a number
        bool isNumeric = false;
        bool isFloat = false;
        
        if (!stringValue.empty()) {
            char first = stringValue[0];
            if (std::isdigit(first) || first == '+' || first == '-' || first == '.') {
                isNumeric = true;
                // Check if it's a float
                if (stringValue.find('.') != std::string::npos || 
                    stringValue.find('e') != std::string::npos || 
                    stringValue.find('E') != std::string::npos) {
                    isFloat = true;
                }
            }
        }
        
        // If we have an expected type context and it's compatible, use it
        if (expected_type && (
            expected_type->tag == TypeTag::Int || expected_type->tag == TypeTag::Int8 ||
            expected_type->tag == TypeTag::Int16 || expected_type->tag == TypeTag::Int32 ||
            expected_type->tag == TypeTag::Int64 || expected_type->tag == TypeTag::Int128 ||
            expected_type->tag == TypeTag::UInt || expected_type->tag == TypeTag::UInt8 ||
            expected_type->tag == TypeTag::UInt16 || expected_type->tag == TypeTag::UInt32 ||
            expected_type->tag == TypeTag::UInt64 || expected_type->tag == TypeTag::UInt128 ||
            expected_type->tag == TypeTag::Float32 || expected_type->tag == TypeTag::Float64)) {
            return expected_type;
        }
        
        if (isNumeric) {
            if (isFloat) {
                // Float values - determine appropriate float type
                try {
                    double floatVal = std::stod(stringValue);
                    if (std::abs(floatVal) <= std::numeric_limits<float>::max()) {
                        float floatVal32 = static_cast<float>(floatVal);
                        if (static_cast<double>(floatVal32) == floatVal) {
                            return type_system.FLOAT32_TYPE;
                        }
                    }
                    return type_system.FLOAT64_TYPE;
                } catch (const std::exception&) {
                    // If parsing fails, treat as string
                    return type_system.NIL_TYPE;
                }
            } else {
                // Integer values - determine appropriate integer type
                try {
                    // Try to fit into the smallest appropriate integer type
                    int64_t intVal = std::stoll(stringValue);
                    
                    if (intVal >= std::numeric_limits<int8_t>::min() && intVal <= std::numeric_limits<int8_t>::max()) {
                        return type_system.INT8_TYPE;
                    } else if (intVal >= std::numeric_limits<int16_t>::min() && intVal <= std::numeric_limits<int16_t>::max()) {
                        return type_system.INT16_TYPE;
                    } else if (intVal >= std::numeric_limits<int32_t>::min() && intVal <= std::numeric_limits<int32_t>::max()) {
                        return type_system.INT32_TYPE;
                    } else {
                        return type_system.INT64_TYPE;
                    }
                } catch (const std::exception&) {
                    // If too large for int64, use Int128
                    return type_system.INT128_TYPE;
                }
            }
        } else {
            // String literal
            return type_system.NIL_TYPE;
        }
    } else if (std::holds_alternative<bool>(expr->value)) {
        return type_system.BOOL_TYPE;
    } else if (std::holds_alternative<std::nullptr_t>(expr->value)) {
        return type_system.NIL_TYPE;
    }
    
    return type_system.NIL_TYPE; // Default fallback
}

} // namespace Frontend
} // namespace LM

// =============================================================================
// CONTRACT STATEMENT CHECKING
// =============================================================================


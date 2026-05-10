#include "../type_checker.hh"

using namespace LM::Frontend;

namespace LM {
namespace Frontend {

TypePtr TypeChecker::check_expression(std::shared_ptr<LM::Frontend::AST::Expression> expr, TypePtr expected_type) {
    if (!expr) return nullptr;
    
    TypePtr type = nullptr;
    
    if (auto literal = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(expr)) {
        type = check_literal_expr(literal, expected_type);
    } else if (auto call = std::dynamic_pointer_cast<LM::Frontend::AST::CallExpr>(expr)) {
        type = check_call_expr(call, expected_type);
    } else if (auto variable = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr)) {
        type = check_variable_expr(variable, expected_type);
    } else if (auto this_expr = std::dynamic_pointer_cast<LM::Frontend::AST::ThisExpr>(expr)) {
        // Handle 'this' reference in frame methods
        if (current_frame) {
            type = type_system.createFrameType(current_frame->name);
        } else {
            add_error("'this' can only be used inside frame methods", expr->line);
            type = type_system.ANY_TYPE;
        }
    } else if (auto binary = std::dynamic_pointer_cast<LM::Frontend::AST::BinaryExpr>(expr)) {
        type = check_binary_expr(binary, expected_type);
    } else if (auto unary = std::dynamic_pointer_cast<LM::Frontend::AST::UnaryExpr>(expr)) {
        type = check_unary_expr(unary, expected_type);
    } else if (auto assign = std::dynamic_pointer_cast<LM::Frontend::AST::AssignExpr>(expr)) {
        type = check_assign_expr(assign);
    } else if (auto grouping = std::dynamic_pointer_cast<LM::Frontend::AST::GroupingExpr>(expr)) {
        type = check_grouping_expr(grouping, expected_type);
    } else if (auto member = std::dynamic_pointer_cast<LM::Frontend::AST::MemberExpr>(expr)) {
        type = check_member_expr(member);
    } else if (auto index = std::dynamic_pointer_cast<LM::Frontend::AST::IndexExpr>(expr)) {
        type = check_index_expr(index);
    } else if (auto list = std::dynamic_pointer_cast<LM::Frontend::AST::ListExpr>(expr)) {
        type = check_list_expr(list);
    } else if (auto tuple = std::dynamic_pointer_cast<LM::Frontend::AST::TupleExpr>(expr)) {
        type = check_tuple_expr(tuple);
    } else if (auto dict = std::dynamic_pointer_cast<LM::Frontend::AST::DictExpr>(expr)) {
        type = check_dict_expr(dict);
    } else if (auto range = std::dynamic_pointer_cast<LM::Frontend::AST::RangeExpr>(expr)) {
        type = check_range_expr(range);
    } else if (auto interpolated = std::dynamic_pointer_cast<LM::Frontend::AST::InterpolatedStringExpr>(expr)) {
        type = check_interpolated_string_expr(interpolated);
    } else if (auto lambda = std::dynamic_pointer_cast<LM::Frontend::AST::LambdaExpr>(expr)) {
        type = check_lambda_expr(lambda);
    } else if (auto error_construct = std::dynamic_pointer_cast<LM::Frontend::AST::ErrorConstructExpr>(expr)) {
        type = check_error_construct_expr(error_construct);
    } else if (auto ok_construct = std::dynamic_pointer_cast<LM::Frontend::AST::OkConstructExpr>(expr)) {
        type = check_ok_construct_expr(ok_construct);
    } else if (auto fallible = std::dynamic_pointer_cast<LM::Frontend::AST::FallibleExpr>(expr)) {
        type = check_fallible_expr(fallible);
    } else if (auto cast = std::dynamic_pointer_cast<LM::Frontend::AST::CastExpr>(expr)) {
        type = check_cast_expr(cast);
    } else if (auto frame_inst = std::dynamic_pointer_cast<LM::Frontend::AST::FrameInstantiationExpr>(expr)) {
        type = check_frame_instantiation_expr(frame_inst);
    } else {
        add_error("Unknown expression type", expr->line);
        type = type_system.NIL_TYPE; // Default fallback
    }
    
    // Set the inferred type on the expression node
    expr->inferred_type = type;
    
    return type;
}

TypePtr TypeChecker::check_expression_with_expected_type(std::shared_ptr<LM::Frontend::AST::Expression> expr, TypePtr expected_type) {
    if (!expr) return nullptr;
    
    TypePtr type = nullptr;
    
    if (auto literal = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(expr)) {
        type = check_literal_expr_with_expected_type(literal, expected_type);
    } else if (auto call = std::dynamic_pointer_cast<LM::Frontend::AST::CallExpr>(expr)) {
        type = check_call_expr(call, expected_type);
    } else if (auto variable = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr)) {
        type = check_variable_expr(variable, expected_type);
    } else if (auto binary = std::dynamic_pointer_cast<LM::Frontend::AST::BinaryExpr>(expr)) {
        type = check_binary_expr(binary, expected_type);
    } else if (auto unary = std::dynamic_pointer_cast<LM::Frontend::AST::UnaryExpr>(expr)) {
        type = check_unary_expr(unary, expected_type);
    } else if (auto assign = std::dynamic_pointer_cast<LM::Frontend::AST::AssignExpr>(expr)) {
        type = check_assign_expr(assign);
    } else if (auto grouping = std::dynamic_pointer_cast<LM::Frontend::AST::GroupingExpr>(expr)) {
        type = check_grouping_expr(grouping, expected_type);
    } else if (auto member = std::dynamic_pointer_cast<LM::Frontend::AST::MemberExpr>(expr)) {
        type = check_member_expr(member);
    } else if (auto index = std::dynamic_pointer_cast<LM::Frontend::AST::IndexExpr>(expr)) {
        type = check_index_expr(index);
    } else if (auto list = std::dynamic_pointer_cast<LM::Frontend::AST::ListExpr>(expr)) {
        type = check_list_expr(list);
    } else if (auto tuple = std::dynamic_pointer_cast<LM::Frontend::AST::TupleExpr>(expr)) {
        type = check_tuple_expr(tuple);
    } else if (auto dict = std::dynamic_pointer_cast<LM::Frontend::AST::DictExpr>(expr)) {
        type = check_dict_expr(dict);
    } else if (auto range = std::dynamic_pointer_cast<LM::Frontend::AST::RangeExpr>(expr)) {
        type = check_range_expr(range);
    } else if (auto interpolated = std::dynamic_pointer_cast<LM::Frontend::AST::InterpolatedStringExpr>(expr)) {
        type = check_interpolated_string_expr(interpolated);
    } else if (auto lambda = std::dynamic_pointer_cast<LM::Frontend::AST::LambdaExpr>(expr)) {
        type = check_lambda_expr(lambda);
    } else if (auto error_construct = std::dynamic_pointer_cast<LM::Frontend::AST::ErrorConstructExpr>(expr)) {
        type = check_error_construct_expr(error_construct);
    } else if (auto ok_construct = std::dynamic_pointer_cast<LM::Frontend::AST::OkConstructExpr>(expr)) {
        type = check_ok_construct_expr(ok_construct);
    } else if (auto fallible = std::dynamic_pointer_cast<LM::Frontend::AST::FallibleExpr>(expr)) {
        type = check_fallible_expr(fallible);
    } else if (auto cast = std::dynamic_pointer_cast<LM::Frontend::AST::CastExpr>(expr)) {
        type = check_cast_expr(cast);
    } else if (auto frame_inst = std::dynamic_pointer_cast<LM::Frontend::AST::FrameInstantiationExpr>(expr)) {
        type = check_frame_instantiation_expr(frame_inst);
    } else {
        add_error("Unknown expression type", expr->line);
        type = type_system.NIL_TYPE; // Default fallback
    }
    
    // Set the inferred type on the expression node
    expr->inferred_type = type;
    
    return type;
}

TypePtr TypeChecker::check_literal_expr(std::shared_ptr<LM::Frontend::AST::LiteralExpr> expr, TypePtr expected_type) {
    if (!expr) return nullptr;
    
    // Set type based on the literal value and token type
    if (std::holds_alternative<std::string>(expr->value)) {
        const std::string& str = std::get<std::string>(expr->value);
        
        // Use the token type to determine the correct type
        switch (expr->literalType) {
            case TokenType::INT_LITERAL:
                if (expected_type && is_decimal_type(expected_type)) {
                    expr->inferred_type = expected_type;
                    return expected_type;
                }
                expr->inferred_type = type_system.INT64_TYPE;
                return type_system.INT64_TYPE;
                
            case TokenType::FLOAT_LITERAL:
            case TokenType::SCIENTIFIC_LITERAL:
                if (expected_type && is_decimal_type(expected_type)) {
                    expr->inferred_type = expected_type;
                    return expected_type;
                }
                expr->inferred_type = type_system.FLOAT64_TYPE;
                return type_system.FLOAT64_TYPE;
                
            default:
                // Non-numeric string literal
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
    
    expr->inferred_type = type_system.NIL_TYPE;
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::check_literal_expr_with_expected_type(std::shared_ptr<LM::Frontend::AST::LiteralExpr> expr, TypePtr expected_type) {
    if (!expr) return nullptr;
    
    // Set type based on the literal value and token type, considering expected type
    if (std::holds_alternative<std::string>(expr->value)) {
        const std::string& str = std::get<std::string>(expr->value);
        
        // Use the token type to determine the correct type
        switch (expr->literalType) {
            case TokenType::INT_LITERAL: {
                // If we have an expected type and it's an integer type or decimal type, use it
                if (expected_type && (is_integer_type(expected_type) || is_decimal_type(expected_type))) {
                    expr->inferred_type = expected_type;
                    return expected_type;
                }
                // Otherwise, default to INT64_TYPE
                expr->inferred_type = type_system.INT64_TYPE;
                return type_system.INT64_TYPE;
            }
                
            case TokenType::FLOAT_LITERAL:
            case TokenType::SCIENTIFIC_LITERAL: {
                // If we have an expected type and it's a float type or decimal type, use it
                if (expected_type && (is_float_type(expected_type) || is_decimal_type(expected_type))) {
                    expr->inferred_type = expected_type;
                    return expected_type;
                }
                // Otherwise, default to FLOAT64_TYPE
                expr->inferred_type = type_system.FLOAT64_TYPE;
                return type_system.FLOAT64_TYPE;
            }
                
            default:
                // Non-numeric string literal
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
    
    expr->inferred_type = type_system.NIL_TYPE;
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::check_variable_expr(std::shared_ptr<LM::Frontend::AST::VariableExpr> expr, TypePtr expected_type) {
    if (!expr) return nullptr;

    // Check for module alias access (e.g., math in math.add)
    if (import_aliases.count(expr->name)) {
        TypePtr type = type_system.createFrameType(expr->name);
        expr->inferred_type = type;
        return type;
    }

    // Check if it's an imported frame or function name (without prefix)
    auto it = current_program_->imported_symbols.find(expr->name);
    if (it != current_program_->imported_symbols.end()) {
        if (auto frame = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(it->second)) {
            TypePtr type = type_system.createFrameType(expr->name);
            expr->inferred_type = type;
            return type;
        }
    }
    
    // Check if this is a reference
    if (references.find(expr->name) != references.end()) {
        check_reference_validity(expr->name, expr->line);
        
        // Get the type from the target linear type
        const auto& ref_info = references[expr->name];
        TypePtr target_type = lookup_variable(ref_info.target_linear_var);
        if (target_type) {
            expr->inferred_type = target_type;
            return target_type;
        }
    }
    
    // Check linear type access
    check_linear_type_access(expr->name, expr->line);
    
    TypePtr type = nullptr;
    // 1. Context-based disambiguation for Enum variants
    TypePtr context_type = expected_type ? expected_type : current_return_type;
    if (context_type && context_type->tag == TypeTag::Enum) {
        if (auto* et = std::get_if<EnumType>(&context_type->extra)) {
            std::string qualified = et->name + "." + expr->name;
            type = lookup_variable(qualified);
        }
    }

    if (!type) type = lookup_variable(expr->name);
    
    // Resolve enum variants
    if (!type) {
        // 1. Try to resolve via expected type context
        if (expected_type && expected_type->tag == TypeTag::Enum) {
            auto enumInfoPtr = std::get_if<EnumType>(&expected_type->extra);
            if (enumInfoPtr) {
                for (const auto& v : enumInfoPtr->values) {
                    if (v == expr->name) {
                        type = expected_type;
                        // But wait! If it's a constructor (has types), we need the constructor type
                        if (!enumInfoPtr->variantTypes.at(v).empty()) {
                            type = variable_types[enumInfoPtr->name + "." + v];
                        }
                        break;
                    }
                }
            }
        }
    }
    
    if (!type) {
        // 2. Try to resolve via variant_owners tracking
        auto it = variant_owners.find(expr->name);
        if (it != variant_owners.end()) {
            if (it->second.size() == 1) {
                // Unambiguous variant from a single enum
                TypePtr owner = it->second[0];
                auto enumInfoPtr = std::get_if<EnumType>(&owner->extra);
                if (!enumInfoPtr->variantTypes.at(expr->name).empty()) {
                    type = variable_types[enumInfoPtr->name + "." + expr->name];
                } else type = owner;
            } else if (it->second.size() > 1) {
                add_error("Ambiguous variant reference: '" + expr->name + "' is defined in multiple enums.", expr->line);
                return nullptr;
            }
        }
    }

    if (!type) {
        // Check if it's a type name or a qualified name
        type = type_system.getType(expr->name);
        if (type && (type->tag == TypeTag::Nil)) type = nullptr;
    }

    // Fallback to global variable lookup (which includes qualified names like Status.Pending)
    if (!type) {
        auto it = variable_types.find(expr->name);
        if (it != variable_types.end()) {
            type = it->second;
        }
    }

    if (!type) {
        undefined_symbols.insert(expr->name);
        add_error("Undefined variable or variant: " + expr->name, expr->line);
        return nullptr;
    }
    
    // Check memory safety before using the variable
    check_variable_use(expr->name, expr->line);

    // Track captures for lambda lowering: only variables resolved from outer scopes
    if (!lambda_captures_stack.empty() && should_capture_variable(expr->name)) {
        auto& captures = lambda_captures_stack.back();
        if (std::find(captures.begin(), captures.end(), expr->name) == captures.end()) {
            captures.push_back(expr->name);
        }
    }
    
    expr->inferred_type = type;
    return type;
}

TypePtr TypeChecker::check_binary_expr(std::shared_ptr<LM::Frontend::AST::BinaryExpr> expr, TypePtr expected_type) {
    if (!expr) return nullptr;
    
    TypePtr left_type = check_expression(expr->left);
    TypePtr right_type = check_expression(expr->right);
    
    // Mandate 7: Automatically unwrap refined types for operations
    TypePtr left_base = type_system.unwrapRefined(left_type);
    TypePtr right_base = type_system.unwrapRefined(right_type);

    // If unwrapped, update the inferred type of operands for the backend
    if (left_type->tag == TypeTag::Refined) expr->left->inferred_type = left_base;
    if (right_type->tag == TypeTag::Refined) expr->right->inferred_type = right_base;

    switch (expr->op) {
        case TokenType::PLUS:
        case TokenType::MINUS:
        case TokenType::STAR:
        case TokenType::SLASH:
            // Arithmetic operations - Mandate 10: promotion rules
            if (left_base->tag == TypeTag::Any || right_base->tag == TypeTag::Any) {
                return type_system.ANY_TYPE;
            }

            if (is_decimal_type(left_base) && is_decimal_type(right_base)) {
                // If both are decimals, promote to largest scale
                int left_scale = get_decimal_scale(left_base);
                int right_scale = get_decimal_scale(right_base);
                if (left_scale >= right_scale) return left_base;
                return right_base;
            }

            if (is_numeric_type(left_base) && is_numeric_type(right_base)) {
                // Mixed decimal/non-decimal arithmetic is disallowed
                if (is_decimal_type(left_base) || is_decimal_type(right_base)) {
                    add_error("Mixed decimal and non-decimal arithmetic is not allowed", expr->line);
                    return type_system.D4_TYPE;
                }
                return promote_numeric_types(left_base, right_base);
            } else if (expr->op == TokenType::PLUS && 
                      (is_string_type(left_base) || is_string_type(right_base))) {
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
            if (is_decimal_type(left_base) || is_decimal_type(right_base)) {
                if (left_base->tag != right_base->tag) {
                    add_error("Decimal comparisons require EXACT scale match. Got " +
                             left_base->toString() + " and " + right_base->toString(), expr->line);
                }
            }
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
            if (left_base->tag == TypeTag::Any || right_base->tag == TypeTag::Any) {
                return type_system.ANY_TYPE;
            }

            if (expr->op == TokenType::MODULUS && (is_decimal_type(left_base) || is_decimal_type(right_base))) {
                if (left_base->tag != right_base->tag) {
                    add_error("Decimal modulo requires EXACT scale match. Got " +
                             left_base->toString() + " and " + right_base->toString(), expr->line);
                }
                return left_base;
            }

            if (is_numeric_type(left_base) && is_numeric_type(right_base)) {
                if (is_decimal_type(left_base) || is_decimal_type(right_base)) {
                    add_error("Mixed decimal and non-decimal arithmetic is not allowed", expr->line);
                    return type_system.D4_TYPE;
                }
                return promote_numeric_types(left_base, right_base);
            }
            add_error("Invalid operand types for arithmetic operation", expr->line);
            return type_system.INT_TYPE;
        default:
            add_error("Unsupported binary operator", expr->line);
            return type_system.NIL_TYPE;
    }
}

TypePtr TypeChecker::check_unary_expr(std::shared_ptr<LM::Frontend::AST::UnaryExpr> expr, TypePtr expected_type) {
    if (!expr) return nullptr;
    
    TypePtr right_type = check_expression(expr->right, expected_type);
    TypePtr right_base = type_system.unwrapRefined(right_type);

    switch (expr->op) {
        case TokenType::BANG:
            // Logical NOT
            if (!is_boolean_type(right_type)) {
                add_type_error("bool", right_type->toString(), expr->line);
            }
            return type_system.BOOL_TYPE;
            
        case TokenType::MINUS:
        case TokenType::PLUS:
            // Numeric negation/affirmation
            if (!is_numeric_type(right_base)) {
                add_type_error("numeric", right_base->toString(), expr->line);
            }
            
            // Special case: Handle large integers that were parsed as float due to overflow
            // but should be integers when negated (e.g., -9223372036854775808 = INT64_MIN)
            if (expr->op == TokenType::MINUS && right_base->tag == TypeTag::Float64) {
                if (auto literal = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(expr->right)) {
                    if (std::holds_alternative<std::string>(literal->value)) {
                        const std::string& str = std::get<std::string>(literal->value);
                        
                        // Only apply this fix to pure integers (no decimal point or scientific notation)
                        bool hasDecimal = str.find('.') != std::string::npos;
                        bool hasScientific = str.find('e') != std::string::npos || str.find('E') != std::string::npos;
                        
                        if (!hasDecimal && !hasScientific) {
                            // Try to parse as unsigned long long to check the range
                            try {
                                unsigned long long value = std::stoull(str);
                                
                                // Check if this value, when negated, fits in int64 range
                                // INT64_MAX = 9223372036854775807
                                // INT64_MIN = -9223372036854775808 (which is INT64_MAX + 1)
                                const unsigned long long INT64_MAX_PLUS_1 = 9223372036854775808ULL;
                                
                                if (value <= INT64_MAX_PLUS_1) {
                                    // This negative value fits in int64
                                    // Update both the type and mark this as an integer literal
                                    literal->inferred_type = type_system.INT64_TYPE;
                                    expr->inferred_type = type_system.INT64_TYPE;
                                    
                                    // Also update the literal's value to ensure it's treated as integer
                                    // Store the negative value as a string to preserve the integer nature
                                    literal->value = "-" + str;
                                    
                                    return type_system.INT64_TYPE;
                                }
                                
                                // Check if it fits in int128 range (for very large numbers)
                                // For now, we'll be conservative and only handle int64 range
                                // Future: could extend to int128 if needed
                                
                            } catch (const std::exception&) {
                                // If parsing fails, keep as float
                            }
                        }
                    }
                }
            }
            if (is_decimal_type(right_base)) {
                expr->inferred_type = right_base;
                return right_base;
            }
            expr->inferred_type = right_type;
            return right_type;
            
        default:
            add_error("Unsupported unary operator", expr->line);
            return right_type;
    }
}

TypePtr TypeChecker::check_call_expr(std::shared_ptr<LM::Frontend::AST::CallExpr> expr, TypePtr expected_type) {
    if (!expr) return nullptr;
    
    // Handle assert() specially to allow decimal comparisons
    if (auto var_callee = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr->callee)) {
        if (var_callee->name == "assert" && !expr->arguments.empty()) {
            if (auto binary = std::dynamic_pointer_cast<LM::Frontend::AST::BinaryExpr>(expr->arguments[0])) {
                // If the first argument is a comparison, check_binary_expr will handle it.
                // We need to re-check it but without special expected type yet,
                // binary checker will use LHS as expected type for RHS.
            }
        }
    }

    // Check positional arguments first
    std::vector<TypePtr> arg_types;
    for (size_t i = 0; i < expr->arguments.size(); ++i) {
        TypePtr arg_expected = nullptr;
        if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr->callee)) {
            auto it = function_signatures.find(var_expr->name);
            if (it != function_signatures.end() && i < it->second.param_types.size()) {
                arg_expected = it->second.param_types[i];
            }
        }
        arg_types.push_back(check_expression(expr->arguments[i], arg_expected));
    }
    
    // Check if callee is a variable (could be function or frame name)
    if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr->callee)) {
        // Check if it's a frame instantiation
        auto frame_it = frame_declarations.find(var_expr->name);
        if (frame_it == frame_declarations.end()) {
            // Try lookup in imported symbols
            auto it = current_program_->imported_symbols.find(var_expr->name);
            if (it != current_program_->imported_symbols.end()) {
                 if (std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(it->second)) {
                     frame_it = frame_declarations.find(var_expr->name);
                 }
            }
        }

        if (frame_it != frame_declarations.end()) {
            const FrameInfo& frame_info = frame_it->second;
            std::string init_name = var_expr->name + ".init";
            auto sig_it = function_signatures.find(init_name);

            // Validate named arguments against both init parameters AND fields
            for (const auto& [arg_name, value] : expr->namedArgs) {
                bool matched = false;
                TypePtr target_type = nullptr;

                // 1. Check init parameters
                if (frame_info.declaration && frame_info.declaration->init) {
                    const auto& init = frame_info.declaration->init;
                    for (const auto& p : init->parameters) {
                        if (p.first == arg_name) { target_type = resolve_type_annotation(p.second); matched = true; break; }
                    }
                    if (!matched) {
                        for (const auto& op : init->optionalParams) {
                            if (op.first == arg_name) { target_type = resolve_type_annotation(op.second.first); matched = true; break; }
                        }
                    }
                }

                // 2. Check fields if not matched in init
                if (!matched) {
                    for (const auto& field : frame_info.fields) {
                        if (field.first == arg_name) { target_type = field.second; matched = true; break; }
                    }
                }

                if (matched) {
                    TypePtr val_type = check_expression(value);
                    if (!is_type_compatible(target_type, val_type)) add_type_error(target_type->toString(), val_type->toString(), expr->line);
                } else {
                    add_error("Frame '" + var_expr->name + "' has no field or init parameter named '" + arg_name + "'", expr->line);
                }
            }

            // Validate positional arguments (passing to init)
            if (!expr->arguments.empty() || sig_it != function_signatures.end()) {
                if (sig_it == function_signatures.end()) {
                    if (!expr->arguments.empty()) add_error("Frame '" + var_expr->name + "' has no init() method to accept positional arguments", expr->line);
                } else {
                    std::vector<TypePtr> expected_params = sig_it->second.param_types;
                    if (!expected_params.empty()) expected_params.erase(expected_params.begin()); // skip 'this'

                    // Count how many required parameters are satisfied by named arguments
                    size_t satisfied_by_named = 0;
                    size_t required_count = 0;
                    if (frame_info.declaration && frame_info.declaration->init) {
                        const auto& init = frame_info.declaration->init;
                        required_count = init->parameters.size();
                        for (size_t i = 0; i < required_count; ++i) {
                            if (expr->namedArgs.count(init->parameters[i].first)) satisfied_by_named++;
                        }
                    } else {
                        required_count = expected_params.size(); // Fallback
                    }

                    if (expr->arguments.size() + satisfied_by_named < required_count) {
                         // Only error if we actually HAVE positional arguments,
                         // otherwise let's assume it's direct field initialization if it matches.
                         if (!expr->arguments.empty()) {
                             add_error("Frame '" + var_expr->name + "' init method requires " + std::to_string(required_count) + " arguments, but only " +
                                      std::to_string(expr->arguments.size() + satisfied_by_named) + " were provided", expr->line);
                         }
                    }
                }
            }

            TypePtr frame_type = type_system.createFrameType(var_expr->name);
            expr->inferred_type = frame_type;
            return frame_type;
        }

        // Check if it's a function call or enum variant constructor
        TypePtr result_type = nullptr;
        std::string target_name = var_expr->name;
        
        // 1. Try context-aware resolution for enum constructors
        TypePtr context_type = expected_type ? expected_type : current_return_type;
        bool resolved = false;
        if (context_type && context_type->tag == TypeTag::Enum) {
            if (auto* et = std::get_if<EnumType>(&context_type->extra)) {
                std::string qualified = et->name + "." + var_expr->name;
                if (function_signatures.count(qualified)) {
                    target_name = qualified;
                    resolved = true;
                }
            }
        }
        
        // 2. Try unambiguous resolution via variant_owners
        if (!resolved) {
            auto it = variant_owners.find(var_expr->name);
            if (it != variant_owners.end()) {
                if (it->second.size() == 1) {
                    TypePtr owner = it->second[0];
                    auto enumInfoPtr = std::get_if<EnumType>(&owner->extra);
                    target_name = enumInfoPtr->name + "." + var_expr->name;
                } else if (it->second.size() > 1) {
                    add_error("Ambiguous variant constructor: '" + var_expr->name + "' is defined in multiple enums.", expr->line);
                    return nullptr;
                }
            }
        }

        if (check_function_call(target_name, arg_types, result_type, expr->line)) {
            expr->inferred_type = result_type;
            return result_type;
        }
    }
    
    // Check if callee is a member expression (method call or module function call)
    if (auto member_expr = std::dynamic_pointer_cast<LM::Frontend::AST::MemberExpr>(expr->callee)) {
        // Check if this is a module member access (e.g., math.add)
        if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(member_expr->object)) {
            std::string qualified_name = var_expr->name + "." + member_expr->name;

            // 1. Check if it's a frame instantiation (e.g., oop.Person())
            auto frame_it = frame_declarations.find(qualified_name);
            if (frame_it != frame_declarations.end()) {
                const FrameInfo& frame_info = frame_it->second;
                std::string init_name = qualified_name + ".init";
                auto sig_it = function_signatures.find(init_name);

                // Validate named arguments against both init parameters AND fields
                for (const auto& [arg_name, value] : expr->namedArgs) {
                    bool matched = false;
                    TypePtr target_type = nullptr;

                    if (frame_info.declaration && frame_info.declaration->init) {
                        const auto& init = frame_info.declaration->init;
                        for (const auto& p : init->parameters) {
                            if (p.first == arg_name) { target_type = resolve_type_annotation(p.second); matched = true; break; }
                        }
                        if (!matched) {
                            for (const auto& op : init->optionalParams) {
                                if (op.first == arg_name) { target_type = resolve_type_annotation(op.second.first); matched = true; break; }
                            }
                        }
                    }

                    if (!matched) {
                        for (const auto& field : frame_info.fields) {
                            if (field.first == arg_name) { target_type = field.second; matched = true; break; }
                        }
                    }

                    if (matched) {
                        TypePtr val_type = check_expression(value);
                        if (!is_type_compatible(target_type, val_type)) add_type_error(target_type->toString(), val_type->toString(), expr->line);
                    } else {
                        add_error("Frame '" + qualified_name + "' has no field or init parameter named '" + arg_name + "'", expr->line);
                    }
                }

                // Validate positional arguments (passing to init)
                if (!expr->arguments.empty() || sig_it != function_signatures.end()) {
                    if (sig_it == function_signatures.end()) {
                        if (!expr->arguments.empty()) add_error("Frame '" + qualified_name + "' has no init() method to accept positional arguments", expr->line);
                    } else {
                        std::vector<TypePtr> expected_params = sig_it->second.param_types;
                        if (!expected_params.empty()) expected_params.erase(expected_params.begin()); // skip 'this'

                        size_t satisfied_by_named = 0;
                        size_t required_count = 0;
                        if (frame_info.declaration && frame_info.declaration->init) {
                            const auto& init = frame_info.declaration->init;
                            required_count = init->parameters.size();
                            for (size_t i = 0; i < required_count; ++i) {
                                if (expr->namedArgs.count(init->parameters[i].first)) satisfied_by_named++;
                            }
                        } else {
                            required_count = expected_params.size();
                        }

                        if (expr->arguments.size() + satisfied_by_named < required_count) {
                             if (!expr->arguments.empty()) {
                                 add_error("Frame '" + qualified_name + "' init method requires " + std::to_string(required_count) + " arguments, but only " +
                                          std::to_string(expr->arguments.size() + satisfied_by_named) + " were provided", expr->line);
                             }
                        }
                    }
                }

                TypePtr frame_type = type_system.createFrameType(qualified_name);
                expr->inferred_type = frame_type;
                return frame_type;
            }

            // 2. Check if it's a module function
            auto sig_it = function_signatures.find(qualified_name);
            if (sig_it == function_signatures.end()) {
                // Try dotted name without :: if LIR generator use .
                sig_it = function_signatures.find(var_expr->name + "." + member_expr->name);
            }
            if (sig_it != function_signatures.end()) {
                validate_argument_types(sig_it->second.param_types, arg_types, qualified_name);
                expr->inferred_type = sig_it->second.return_type;
                return sig_it->second.return_type;
            }

            // 3. Fallback for module alias
            auto alias_it = import_aliases.find(var_expr->name);
            if (alias_it != import_aliases.end()) {
                std::string full_name = alias_it->second + "." + member_expr->name;
                auto sig_it2 = function_signatures.find(full_name);
                if (sig_it2 != function_signatures.end()) {
                    validate_argument_types(sig_it2->second.param_types, arg_types, full_name);
                    expr->inferred_type = sig_it2->second.return_type;
                    return sig_it2->second.return_type;
                }
                add_error("Module '" + alias_it->second + "' has no member '" + member_expr->name + "'", expr->line);
                return type_system.ANY_TYPE;
            }
        }
        
        // Get the object type
        TypePtr object_type = check_expression(member_expr->object);
        
        // Handle frame method calls
        if (object_type && object_type->tag == TypeTag::Frame) {
            // Get the frame name from the FrameType
            auto frameTypeData = std::get_if<FrameType>(&object_type->extra);
            if (!frameTypeData) {
                add_error("Invalid frame type", expr->line);
                return type_system.ANY_TYPE;
            }
            
            std::string frame_name = frameTypeData->name;
            std::string method_name = member_expr->name;
            
            // Look up the frame declaration
            auto frame_it = frame_declarations.find(frame_name);
            if (frame_it == frame_declarations.end()) {
                add_error("Unknown frame type: " + frame_name, expr->line);
                return type_system.ANY_TYPE;
            }
            
            const FrameInfo& frame_info = frame_it->second;
            
            // Find the method in the frame
            std::shared_ptr<LM::Frontend::AST::FrameMethod> method = nullptr;
            for (const auto& m : frame_info.declaration->methods) {
                if (m->name == method_name) {
                    method = m;
                    break;
                }
            }
            
            // Check init and deinit methods
            if (!method && method_name == "init") {
                method = frame_info.declaration->init;
            }
            if (!method && method_name == "deinit") {
                method = frame_info.declaration->deinit;
            }
            
            if (!method) {
                // Not found in frame, check implemented traits recursively
                std::vector<std::string> trait_worklist = frame_info.declaration->implements;
                std::unordered_set<std::string> visited_traits;

                while (!trait_worklist.empty()) {
                    std::string current_trait = trait_worklist.back();
                    trait_worklist.pop_back();

                    if (visited_traits.count(current_trait)) continue;
                    visited_traits.insert(current_trait);

                    auto trait_it = trait_declarations.find(current_trait);
                    if (trait_it != trait_declarations.end()) {
                        for (const auto& tm : trait_it->second.declaration->methods) {
                            if (tm->name == method_name) {
                                // Found in trait hierarchy (static dispatch)
                                TypePtr trait_return_type = tm->returnType ? resolve_type_annotation(tm->returnType.value()) : type_system.NIL_TYPE;
                                expr->inferred_type = trait_return_type;
                                return trait_return_type;
                            }
                        }
                        // Add parent traits to worklist
                        for (const auto& parent : trait_it->second.extends) {
                            trait_worklist.push_back(parent);
                        }
                    }
                }

                add_error("Frame '" + frame_name + "' has no method '" + method_name + "'", expr->line);
                return type_system.ANY_TYPE;
            }
            
            // Check visibility
            if (!is_visible(frame_name, method->visibility, expr->line)) {
                add_error("Cannot access " + LM::Frontend::AST::visibilityToString(method->visibility) +
                         " method '" + method_name + "' of frame '" + frame_name + "'", expr->line);
            }
            
            // Check parameter count and types
            size_t required_params = method->parameters.size();
            size_t optional_params = method->optionalParams.size();
            size_t total_params = required_params + optional_params;
            size_t provided_args = arg_types.size();
            
            if (provided_args < required_params) {
                add_error("Method '" + method_name + "' requires " + std::to_string(required_params) + 
                         " arguments, but " + std::to_string(provided_args) + " were provided", expr->line);
            } else if (provided_args > total_params) {
                add_error("Method '" + method_name + "' accepts at most " + std::to_string(total_params) + 
                         " arguments, but " + std::to_string(provided_args) + " were provided", expr->line);
            }
            
            // Check parameter types
            for (size_t i = 0; i < std::min(provided_args, total_params); ++i) {
                TypePtr expected_type = nullptr;
                if (i < required_params) {
                    expected_type = resolve_type_annotation(method->parameters[i].second);
                } else {
                    expected_type = resolve_type_annotation(method->optionalParams[i - required_params].second.first);
                }
                
                if (!is_type_compatible(expected_type, arg_types[i])) {
                    add_type_error(expected_type->toString(), arg_types[i]->toString(), expr->line);
                }
            }
            
            // Return the method's return type
            if (method->returnType) {
                TypePtr return_type = resolve_type_annotation(method->returnType);
                expr->inferred_type = return_type;
                return return_type;
            } else {
                expr->inferred_type = type_system.NIL_TYPE;
                return type_system.NIL_TYPE;
            }
        }
        
        // For other types, just check the member expression
        TypePtr result_type = check_expression(expr->callee);
        if (result_type) {
            expr->inferred_type = result_type;
            return result_type;
        }
    }
    
    // If not a known function, check the callee as an expression
    // But first check if it's already marked as undefined to avoid cascading errors
    if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr->callee)) {
        if (undefined_symbols.find(var_expr->name) != undefined_symbols.end()) {
            // Already reported as undefined, don't cascade
            return type_system.NIL_TYPE;
        }
    }
    
    TypePtr callee_type = check_expression(expr->callee);
    
    if (callee_type && callee_type->tag == TypeTag::Function) {
        if (auto* func_type = std::get_if<FunctionType>(&callee_type->extra)) {
            // Validate arguments against function type
            if (arg_types.size() != func_type->paramTypes.size()) {
                add_error("Function expects " + std::to_string(func_type->paramTypes.size()) + 
                         " arguments, but " + std::to_string(arg_types.size()) + " were provided", expr->line);
            } else {
                for (size_t i = 0; i < arg_types.size(); ++i) {
                    if (!is_type_compatible(func_type->paramTypes[i], arg_types[i])) {
                        add_type_error(func_type->paramTypes[i]->toString(), arg_types[i]->toString(), expr->line);
                    }
                }
            }
            expr->inferred_type = func_type->returnType;
            return func_type->returnType;
        }
    }

    // Only report error if the callee is not an undefined symbol
    // (to avoid cascading errors)
    if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr->callee)) {
        if (undefined_symbols.find(var_expr->name) == undefined_symbols.end()) {
            add_error("Cannot call non-function value: " + callee_type->toString(), expr->line);
        }
    } else {
        add_error("Cannot call non-function value", expr->line);
    }
    
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::check_assign_expr(std::shared_ptr<LM::Frontend::AST::AssignExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr value_type = check_expression(expr->value);
    
    // Handle member assignment (e.g., obj.field = value)
    if (expr->object && expr->member) {
        TypePtr object_type = check_expression(expr->object);
        
        // Handle frame field assignment
        if (object_type && object_type->tag == TypeTag::Frame) {
            // Get the frame name from the FrameType
            auto frameTypeData = std::get_if<FrameType>(&object_type->extra);
            if (!frameTypeData) {
                add_error("Invalid frame type", expr->line);
                return value_type;
            }
            
            std::string frame_name = frameTypeData->name;
            std::string field_name = *expr->member;
            
            // Look up the frame declaration
            auto frame_it = frame_declarations.find(frame_name);
            if (frame_it == frame_declarations.end()) {
                add_error("Unknown frame type: " + frame_name, expr->line);
                return value_type;
            }
            
            const FrameInfo& frame_info = frame_it->second;
            
            // Find the field
            TypePtr field_type = nullptr;
            for (const auto& [fname, ftype] : frame_info.fields) {
                if (fname == field_name) {
                    field_type = ftype;
                    break;
                }
            }
            
            if (!field_type) {
                add_error("Frame '" + frame_name + "' has no field '" + field_name + "'", expr->line);
                return value_type;
            }
            
            // Check visibility
            if (frame_info.declaration) {
                for (const auto& field : frame_info.declaration->fields) {
                    if (field->name == field_name) {
                        if (!is_visible(frame_name, field->visibility, expr->line)) {
                            add_error("Cannot assign to " + LM::Frontend::AST::visibilityToString(field->visibility) +
                                     " field '" + field_name + "' of frame '" + frame_name + "'", expr->line);
                        }
                        break;
                    }
                }
            }
            if (!is_type_compatible(field_type, value_type)) {
                add_type_error(field_type->toString(), value_type->toString(), expr->line);
            }
            
            return value_type;
        }
        
        // For other types, just return the value type
        return value_type;
    }
    
    // Handle index assignment (e.g., arr[0] = value)
    if (expr->object && expr->index) {
        // Just check the object and index expressions
        check_expression(expr->object);
        check_expression(expr->index);
        return value_type;
    }
    
    // For simple variable assignment
    if (!expr->object && !expr->member && !expr->index) {
        TypePtr var_type = lookup_variable(expr->name);
        if (var_type) {
            if (!is_type_compatible(var_type, value_type) && 
                !(is_string_type(var_type) && is_string_type(value_type))) {
                add_type_error(var_type->toString(), value_type->toString(), expr->line);
            }
            
            // Check if we're assigning from another variable (create reference or move)
            if (auto var_expr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr->value)) {
                TypePtr rhs_type = lookup_variable(var_expr->name);
                bool is_copyable = (rhs_type && rhs_type->tag == TypeTag::Function);
                
                if (!is_copyable && linear_types.find(var_expr->name) != linear_types.end()) {
                    // This is a linear type - move it and increment generation
                    move_linear_type(var_expr->name, var_expr->line);
                    
                    // The target becomes the new owner with updated generation
                    LinearTypeInfo new_linear_info;
                    new_linear_info.is_moved = false;
                    new_linear_info.access_count = 1;
                    new_linear_info.current_generation = linear_types[var_expr->name].current_generation;
                    linear_types[expr->name] = new_linear_info;
                } else {
                    // Regular variable - create reference
                    create_reference(var_expr->name, expr->name, expr->line);
                }
            }
        } else {
            // Implicit variable declaration
            declare_variable(expr->name, value_type);
            declare_variable_memory(expr->name, value_type);  // Track memory for new variable
            
            // New variables are linear types by default
            LinearTypeInfo linear_info;
            linear_info.is_moved = false;
            linear_info.access_count = 0;
            linear_types[expr->name] = linear_info;
        }
    }
    
    return value_type;
}

TypePtr TypeChecker::check_grouping_expr(std::shared_ptr<LM::Frontend::AST::GroupingExpr> expr, TypePtr expected_type) {
    if (!expr) return nullptr;
    return check_expression(expr->expression, expected_type);
}

TypePtr TypeChecker::check_member_expr(std::shared_ptr<LM::Frontend::AST::MemberExpr> expr) {
    if (!expr) return nullptr;
    TypePtr object_type = check_expression(expr->object);
    std::string member_name = expr->name;
    
    // Check for module alias access
    if (object_type && object_type->tag == TypeTag::Frame) {
        auto* fData = std::get_if<FrameType>(&object_type->extra);
        if (fData && import_aliases.count(fData->name)) {
            std::string alias = fData->name;
            auto find_member = [&](const std::string& qname) -> TypePtr {
                if (variable_types.count(qname)) return variable_types[qname];
                std::string q_low = qname; for(char& c : q_low) c = std::tolower(c);
                for (const auto& kv : variable_types) {
                    std::string k_low = kv.first; for(char& c : k_low) c = std::tolower(c);
                    if (k_low == q_low) return kv.second;
                }
                return nullptr;
            };
            TypePtr res = find_member(alias + "." + member_name);
            if (!res) res = find_member(member_name);
            if (!res) for (const auto& kv : variable_types) if (kv.first.ends_with("." + member_name)) { res = kv.second; break; }
            if (res) { expr->inferred_type = res; return res; }
        }
    }
    if (object_type && object_type->tag == TypeTag::Channel) {
        std::string method_name = expr->name;
        
        // Return appropriate types for channel methods
        if (method_name == "offer") {
            return type_system.BOOL_TYPE; // offer() returns bool
        } else if (method_name == "poll") {
            return type_system.ANY_TYPE; // poll() returns Option<T> (represented as any for now)
        } else if (method_name == "send") {
            return type_system.NIL_TYPE; // send() returns nil
        } else if (method_name == "recv") {
            return type_system.ANY_TYPE; // recv() returns T
        } else if (method_name == "close") {
            return type_system.NIL_TYPE; // close() returns nil
        } else {
            add_error("Unknown channel method: " + method_name, expr->line);
            return type_system.ANY_TYPE;
        }
    }
    
    // Handle enum variant access: Color.Red
    if (object_type && object_type->tag == TypeTag::Enum) {
        if (auto var_obj = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(expr->object)) {
            std::string qualified = var_obj->name + "." + expr->name;
            if (variable_types.count(qualified)) {
                TypePtr variantType = variable_types[qualified];
                expr->inferred_type = variantType;
                return variantType;
            }
        }
    }

    // Handle trait member access
    if (object_type && object_type->tag == TypeTag::Trait) {
        auto traitTypeData = std::get_if<TraitType>(&object_type->extra);
        if (traitTypeData) {
            std::string trait_name = traitTypeData->name;
            auto trait_it = trait_declarations.find(trait_name);
            if (trait_it != trait_declarations.end()) {
                for (const auto& method : trait_it->second.declaration->methods) {
                    if (method->name == member_name) {
                        if (method->returnType.has_value()) return resolve_type_annotation(method->returnType.value());
                        return type_system.NIL_TYPE;
                    }
                }
            }
        }
        return type_system.ANY_TYPE;
    }

    // Handle frame member access
    if (object_type && object_type->tag == TypeTag::Frame) {
        // Get the frame name from the FrameType
        auto frameTypeData = std::get_if<FrameType>(&object_type->extra);
        if (!frameTypeData) {
            add_error("Invalid frame type", expr->line);
            return type_system.ANY_TYPE;
        }
        
        std::string frame_name = frameTypeData->name;
        
        // Look up the frame declaration
        auto frame_it = frame_declarations.find(frame_name);
        if (frame_it == frame_declarations.end()) {
            add_error("Unknown frame type: " + frame_name, expr->line);
            return type_system.ANY_TYPE;
        }
        
        const FrameInfo& frame_info = frame_it->second;
        
        // Check if this is a module alias access
        if (import_aliases.count(frame_name)) {
            std::string qualified_name = frame_name + "." + member_name;
            TypePtr member_type = lookup_variable(qualified_name);
            if (member_type && member_type->tag != TypeTag::Nil) {
                expr->inferred_type = member_type;
                return member_type;
            }
            // Check for functions
            if (function_signatures.count(qualified_name)) {
                const auto& sig = function_signatures[qualified_name];
                TypePtr func_type = type_system.createFunctionType(sig.param_types, sig.return_type);
                expr->inferred_type = func_type;
                return func_type;
            }
        }

        if (!frame_info.declaration) {
            // If it's a module alias, we shouldn't fail if we just haven't found the member yet
            // but we should have found it if it exists.
            if (import_aliases.count(frame_name)) {
                add_error("Module '" + frame_name + "' has no member '" + member_name + "'", expr->line);
            } else {
                add_error("Invalid frame declaration for " + frame_name, expr->line);
            }
            return type_system.ANY_TYPE;
        }

        // Check if member is a field
        for (const auto& [field_name, field_type] : frame_info.fields) {
            if (field_name == member_name) {
                // Check visibility
                // Find the field in the frame declaration to get visibility
                for (const auto& field : frame_info.declaration->fields) {
                    if (field->name == member_name) {
                        if (!is_visible(frame_name, field->visibility, expr->line)) {
                            add_error("Cannot access " + LM::Frontend::AST::visibilityToString(field->visibility) +
                                     " field '" + member_name + "' of frame '" + frame_name + "'", expr->line);
                        }
                        expr->inferred_type = field_type;
                        return field_type;
                    }
                }
            }
        }
        
        // Check if member is a method
        for (const auto& method : frame_info.declaration->methods) {
            if (method->name == member_name) {
                // Check visibility
                if (!is_visible(frame_name, method->visibility, expr->line)) {
                    add_error("Cannot access " + LM::Frontend::AST::visibilityToString(method->visibility) +
                             " method '" + member_name + "' of frame '" + frame_name + "'", expr->line);
                }
                
                // Return the method's return type
                if (method->returnType) {
                    TypePtr return_type = resolve_type_annotation(method->returnType);
                    expr->inferred_type = return_type;
                    return return_type;
                } else {
                    // Method has no explicit return type, assume nil
                    expr->inferred_type = type_system.NIL_TYPE;
                    return type_system.NIL_TYPE;
                }
            }
        }
        
        // Check init and deinit methods
        if (member_name == "init" && frame_info.declaration->init) {
            if (frame_info.declaration->init->returnType) {
                TypePtr return_type = resolve_type_annotation(frame_info.declaration->init->returnType);
                expr->inferred_type = return_type;
                return return_type;
            } else {
                expr->inferred_type = type_system.NIL_TYPE;
                return type_system.NIL_TYPE;
            }
        }
        
        if (member_name == "deinit" && frame_info.declaration->deinit) {
            expr->inferred_type = type_system.NIL_TYPE;
            return type_system.NIL_TYPE;
        }
        
        // Member not found
        add_error("Frame '" + frame_name + "' has no member '" + member_name + "'", expr->line);
        return type_system.ANY_TYPE;
    }
    
    // Handle structural type member access
    if (object_type->tag == TypeTag::Structural) {
        auto* structType = std::get_if<StructuralType>(&object_type->extra);
        if (structType) {
            for (const auto& field : structType->fields) {
                if (field.first == member_name) {
                    expr->inferred_type = field.second;
                    return field.second;
                }
            }
        }
        add_error("Structural type has no member " + member_name, expr->line);
        return type_system.ANY_TYPE;
    }
    // Handle other types of member access (e.g. built-in types like String, List)
    if (object_type->tag == TypeTag::String) {
        if (member_name == "len") return type_system.INT_TYPE;
        if (member_name == "upper" || member_name == "lower") return type_system.FUNCTION_TYPE;
    } else if (object_type->tag == TypeTag::List) {
        if (member_name == "len") return type_system.INT_TYPE;
        if (member_name == "append" || member_name == "pop") return type_system.FUNCTION_TYPE;
    } else if (object_type->tag == TypeTag::Dict) {
        if (member_name == "len") return type_system.INT_TYPE;
        if (member_name == "keys" || member_name == "values") return type_system.FUNCTION_TYPE;
    }

    add_error("Type '" + object_type->toString() + "' has no member '" + member_name + "'", expr->line);
    return type_system.ANY_TYPE;
}

TypePtr TypeChecker::check_index_expr(std::shared_ptr<LM::Frontend::AST::IndexExpr> expr) {
    if (!expr) return nullptr;
    
    TypePtr object_type = check_expression(expr->object);
    TypePtr index_type = check_expression(expr->index);
    
    if (object_type->tag == TypeTag::List) {
        if (index_type->tag != TypeTag::Int && index_type->tag != TypeTag::Int64) {
             add_error("List index must be an integer, got " + index_type->toString(), expr->line);
        }
        if (auto lt = std::get_if<ListType>(&object_type->extra)) {
            return lt->elementType;
        }
    } else if (object_type->tag == TypeTag::Dict) {
        if (auto dt = std::get_if<DictType>(&object_type->extra)) {
            if (!is_type_compatible(dt->keyType, index_type)) {
                add_error("Dictionary key type mismatch: expected " + dt->keyType->toString() +
                         ", got " + index_type->toString(), expr->line);
            }
            return dt->valueType;
        }
    } else if (object_type->tag == TypeTag::String) {
        if (index_type->tag != TypeTag::Int && index_type->tag != TypeTag::Int64) {
             add_error("String index must be an integer, got " + index_type->toString(), expr->line);
        }
        return type_system.NIL_TYPE;
    } else if (object_type->tag == TypeTag::Tuple) {
        if (index_type->tag != TypeTag::Int && index_type->tag != TypeTag::Int64) {
             add_error("Tuple index must be an integer, got " + index_type->toString(), expr->line);
        }
        if (auto tt = std::get_if<TupleType>(&object_type->extra)) {
            // Return the type of the indexed element (simplified - could add bounds checking)
            return type_system.ANY_TYPE;
        }
    }

    add_error("Cannot index type '" + object_type->toString() + "'", expr->line);
    return type_system.ANY_TYPE;
}

TypePtr TypeChecker::check_list_expr(std::shared_ptr<LM::Frontend::AST::ListExpr> expr) {
    if (!expr) return nullptr;
    
    if (expr->elements.empty()) {
        // Empty list - return generic list type
        return type_system.createTypedListType(type_system.ANY_TYPE);
    }
    
    // Check all elements and infer common element type
    std::vector<TypePtr> elementTypes;
    for (const auto& elem : expr->elements) {
        TypePtr elemType = check_expression(elem);
        elementTypes.push_back(elemType);
    }
    
    // Enforce strict homogeneous element typing with no implicit widening.
    TypePtr commonElementType = elementTypes[0];
    bool consistent = true;
    for (size_t i = 1; i < elementTypes.size(); ++i) {
        if (!commonElementType || !elementTypes[i] ||
            commonElementType->toString() != elementTypes[i]->toString()) {
            consistent = false;
            break;
        }
    }
    
    if (!consistent) {
        commonElementType = type_system.ANY_TYPE;
    }
    
    TypePtr listType = type_system.createTypedListType(commonElementType);
    expr->inferred_type = listType;
    return listType;
}

TypePtr TypeChecker::check_tuple_expr(std::shared_ptr<LM::Frontend::AST::TupleExpr> expr) {
    if (!expr) return nullptr;
    
    // Check all elements and collect their types
    std::vector<TypePtr> elementTypes;
    for (const auto& elem : expr->elements) {
        TypePtr elemType = check_expression(elem);
        elementTypes.push_back(elemType);
    }
    
    // Create tuple type with the element types
    TypePtr tupleType = type_system.createTupleType(elementTypes);
    expr->inferred_type = tupleType;
    return tupleType;
}

TypePtr TypeChecker::check_dict_expr(std::shared_ptr<LM::Frontend::AST::DictExpr> expr) {
    if (!expr) return nullptr;
    
    if (expr->entries.empty()) {
        // Empty dictionary - return generic dict type
        return type_system.createTypedDictType(type_system.NIL_TYPE, type_system.ANY_TYPE);
    }
    
    // Check all entries and infer common key and value types
    std::vector<TypePtr> keyTypes;
    std::vector<TypePtr> valueTypes;
    
    for (const auto& [keyExpr, valueExpr] : expr->entries) {
        TypePtr keyType = check_expression(keyExpr);
        TypePtr valueType = check_expression(valueExpr);
        keyTypes.push_back(keyType);
        valueTypes.push_back(valueType);
    }
    
    // Enforce strict homogeneous key/value typing with no implicit widening.
    TypePtr commonKeyType = keyTypes[0];
    TypePtr commonValueType = valueTypes[0];
    
    for (size_t i = 1; i < keyTypes.size(); ++i) {
        if (!commonKeyType || !keyTypes[i] ||
            commonKeyType->toString() != keyTypes[i]->toString()) {
            add_error("Inconsistent key types in dictionary literal: expected all keys to be '" +
                    (commonKeyType ? commonKeyType->toString() : "unknown") +
                    "', found '" + (keyTypes[i] ? keyTypes[i]->toString() : "unknown") + "'", expr->line);
            return type_system.createTypedDictType(type_system.NIL_TYPE, type_system.ANY_TYPE);
        }
    }
    
    bool valuesConsistent = true;
    for (size_t i = 1; i < valueTypes.size(); ++i) {
        if (!commonValueType || !valueTypes[i] ||
            commonValueType->toString() != valueTypes[i]->toString()) {
            valuesConsistent = false;
            break;
        }
    }
    
    if (!valuesConsistent) {
        commonValueType = type_system.ANY_TYPE;
    }
    
    TypePtr dictType = type_system.createTypedDictType(commonKeyType, commonValueType);
    expr->inferred_type = dictType;
    return dictType;
}

TypePtr TypeChecker::check_interpolated_string_expr(std::shared_ptr<LM::Frontend::AST::InterpolatedStringExpr> expr) {
    if (!expr) return nullptr;
    
    for (const auto& part : expr->parts) {
        if (std::holds_alternative<std::shared_ptr<LM::Frontend::AST::Expression>>(part)) {
            check_expression(std::get<std::shared_ptr<LM::Frontend::AST::Expression>>(part));
        }
    }
    
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_lambda_expr(std::shared_ptr<LM::Frontend::AST::LambdaExpr> expr) {
    if (!expr) return nullptr;
    
    // Create new scope for lambda parameters
    enter_scope();
    lambda_captures_stack.emplace_back();
    lambda_scope_markers.push_back(current_scope.get());
    
    // Process parameters and add them to scope
    std::vector<TypePtr> paramTypes;
    for (const auto& param : expr->params) {
        TypePtr paramType = type_system.ANY_TYPE;
        if (param.second) {
            paramType = resolve_type_annotation(param.second);
        }
        paramTypes.push_back(paramType);
        declare_variable(param.first, paramType);
    }
    
    // Determine return type
    TypePtr returnType = type_system.ANY_TYPE;
    if (expr->returnType.has_value()) {
        returnType = resolve_type_annotation(expr->returnType.value());
    } else {
        // Enhanced return type inference from lambda body
        returnType = infer_lambda_return_type(expr->body);
    }
    
    // Set up function context for lambda
    auto prevFunction = current_function;
    auto prevReturnType = current_return_type;
    
    // Create a temporary function signature for the lambda
    FunctionSignature lambdaSignature;
    lambdaSignature.name = "<lambda>";
    lambdaSignature.param_types = paramTypes;
    lambdaSignature.return_type = returnType;
    lambdaSignature.can_fail = false;
    lambdaSignature.error_types = {};
    
    current_function = nullptr; // Lambdas don't have function declarations
    current_return_type = returnType;
    
    // Check lambda body
    TypePtr bodyType = check_statement(expr->body);
    
    // Restore previous context
    current_function = prevFunction;
    current_return_type = prevReturnType;

    // Materialize deterministic capture list for backend closure lowering
    expr->capturedVars = lambda_captures_stack.back();
    lambda_captures_stack.pop_back();
    lambda_scope_markers.pop_back();
    
    exit_scope(); // Exit lambda scope
    
    // Create and return function type
    std::vector<std::string> param_names;
    for (const auto& p : expr->params) param_names.push_back(p.first);
    TypePtr functionType = type_system.createFunctionType(param_names, paramTypes, returnType);
    expr->inferred_type = functionType;
    return functionType;
}

bool TypeChecker::should_capture_variable(const std::string& name) const {
    if (lambda_captures_stack.empty() || lambda_scope_markers.empty() || !current_scope) {
        return false;
    }

    // Find the nearest scope that defines this symbol.
    const Scope* defining_scope = nullptr;
    const Scope* scope = current_scope.get();
    while (scope) {
        if (scope->variables.find(name) != scope->variables.end()) {
            defining_scope = scope;
            break;
        }
        scope = scope->parent.get();
    }

    // If it's not in lexical scopes, it's global/module/builtin lookup and should not be captured.
    if (!defining_scope) {
        return false;
    }

    // A capture is a symbol defined outside the current lambda lexical boundary.
    const Scope* lambda_scope = lambda_scope_markers.back();
    scope = current_scope.get();
    while (scope) {
        if (scope == defining_scope) {
            return false; // Defined in lambda scope or nested blocks within it.
        }
        if (scope == lambda_scope) {
            break;
        }
        scope = scope->parent.get();
    }

    return true;
}

TypePtr TypeChecker::check_error_construct_expr(std::shared_ptr<LM::Frontend::AST::ErrorConstructExpr> expr) {
    if (!expr) return nullptr;
    
    // For err() constructs, we need to infer the Type? from the function's return type context
    // If we're in a function that returns Type?, then err() should return that same Type?
    
    TypePtr error_union_type = nullptr;
    
    if (current_return_type && current_return_type->tag == TypeTag::ErrorUnion) {
        // We're in a function that returns a fallible type, use that type
        error_union_type = current_return_type;
    } else if (current_return_type && type_system.isFallibleType(current_return_type)) {
        // We're in a function that returns a fallible type, use that type
        error_union_type = current_return_type;
    } else {
        // Fallback: create a generic error union type
        // This should ideally be inferred from context in a full implementation
        error_union_type = type_system.createFallibleType(type_system.NIL_TYPE);
    }
    
    expr->inferred_type = error_union_type;
    return error_union_type;
}

TypePtr TypeChecker::check_ok_construct_expr(std::shared_ptr<LM::Frontend::AST::OkConstructExpr> expr) {
    if (!expr) return nullptr;
    
    // Check the value expression first
    TypePtr value_type = check_expression(expr->value);
    if (!value_type) {
        add_error("Failed to determine type of ok() value", expr->line);
        return nullptr;
    }
    
    // Create a fallible type (Type?) with the value type as the success type
    // If we're in a function context, try to match the return type
    TypePtr ok_type = nullptr;
    
    if (current_return_type && current_return_type->tag == TypeTag::ErrorUnion) {
        // We're in a function that returns a fallible type
        // Check if the value type is compatible with the expected success type
        TypePtr expected_success_type = type_system.getFallibleSuccessType(current_return_type);
        if (expected_success_type && is_type_compatible(expected_success_type, value_type)) {
            ok_type = current_return_type;
        } else {
            add_error("ok() value type doesn't match function return type", expr->line);
            ok_type = type_system.createFallibleType(value_type);
        }
    } else {
        // Create a new fallible type with the value type
        ok_type = type_system.createFallibleType(value_type);
    }
    
    expr->inferred_type = ok_type;
    return ok_type;
}

TypePtr TypeChecker::check_fallible_expr(std::shared_ptr<LM::Frontend::AST::FallibleExpr> expr) {
    if (!expr) return nullptr;
    
    // Check the expression that might be fallible
    TypePtr expr_type = check_expression(expr->expression);
    if (!expr_type) {
        add_error("Failed to determine type of fallible expression", expr->line);
        return nullptr;
    }
    
    // The expression should be a fallible type (Type?)
    if (!type_system.isFallibleType(expr_type)) {
        add_error("? operator can only be used on fallible types (Type?)", expr->line);
        return nullptr;
    }
    
    // The ? operator unwraps the fallible type, returning the success type
    TypePtr success_type = type_system.getFallibleSuccessType(expr_type);
    if (!success_type) {
        add_error("Failed to extract success type from fallible type", expr->line);
        return type_system.NIL_TYPE;
    }
    
    expr->inferred_type = success_type;
    return success_type;
}

TypePtr TypeChecker::check_cast_expr(std::shared_ptr<LM::Frontend::AST::CastExpr> expr) {
    if (!expr) return nullptr;

    TypePtr source_type = check_expression(expr->expression);
    TypePtr target_type = resolve_type_annotation(expr->targetType);

    // Strict rules for decimals
    if (is_decimal_type(source_type) || is_decimal_type(target_type)) {
        // Only allow decimal to decimal or other numeric to decimal (with caution)
        if (!is_numeric_type(source_type)) {
            add_error("Cannot cast non-numeric type " + source_type->toString() + " to decimal", expr->line);
        }
    }

    expr->inferred_type = target_type;
    return target_type;
}

} // namespace Frontend
} // namespace LM


#include "../generator.hh"
#include "../functions.hh"
#include "../../frontend/module_manager.hh"
#include "../function_registry.hh"
#include "../builtin_functions.hh"
#include "../../frontend/ast.hh"
#include "../../frontend/scanner.hh"
#include <algorithm>
#include <map>
#include <limits>

using namespace LM::LIR;

namespace LM {
namespace LIR {

namespace {
bool resolve_enum_variant_info(TypeSystem* type_system,
                               TypePtr enum_type_hint,
                               const std::string& variant_ref,
                               int64_t& out_tag,
                               size_t& out_arity) {
    TypePtr enum_type = enum_type_hint;
    std::string variant_name = variant_ref;

    auto dot_pos = variant_ref.find('.');
    if (dot_pos != std::string::npos) {
        std::string enum_name = variant_ref.substr(0, dot_pos);
        variant_name = variant_ref.substr(dot_pos + 1);
        if (type_system) {
            enum_type = type_system->getType(enum_name);
        }
    }

    if (!enum_type || enum_type->tag != TypeTag::Enum) {
        return false;
    }

    auto* enum_info = std::get_if<EnumType>(&enum_type->extra);
    if (!enum_info) return false;

    auto it = std::find(enum_info->values.begin(), enum_info->values.end(), variant_name);
    if (it == enum_info->values.end()) return false;

    out_tag = static_cast<int64_t>(std::distance(enum_info->values.begin(), it));
    auto arity_it = enum_info->variantTypes.find(variant_name);
    out_arity = (arity_it != enum_info->variantTypes.end()) ? arity_it->second.size() : 0;
    return true;
}
}

Reg Generator::emit_expr(LM::Frontend::AST::Expression& expr) {
    if (auto literal = dynamic_cast<LM::Frontend::AST::LiteralExpr*>(&expr)) {
        return emit_literal_expr(*literal, nullptr);
    } else if (auto variable = dynamic_cast<LM::Frontend::AST::VariableExpr*>(&expr)) {
        return emit_variable_expr(*variable);
    } else if (auto interpolated = dynamic_cast<LM::Frontend::AST::InterpolatedStringExpr*>(&expr)) {
        return emit_interpolated_string_expr(*interpolated);
    } else if (auto binary = dynamic_cast<LM::Frontend::AST::BinaryExpr*>(&expr)) {
        return emit_binary_expr(*binary);
    } else if (auto unary = dynamic_cast<LM::Frontend::AST::UnaryExpr*>(&expr)) {
        return emit_unary_expr(*unary);
    } else if (auto assign = dynamic_cast<LM::Frontend::AST::AssignExpr*>(&expr)) {
        return emit_assign_expr(*assign);
    } else if (auto call = dynamic_cast<LM::Frontend::AST::CallExpr*>(&expr)) {
        return emit_call_expr(*call);
    } else if (auto closure_call = dynamic_cast<LM::Frontend::AST::CallClosureExpr*>(&expr)) {
        return emit_call_closure_expr(*closure_call);
    } else if (auto list = dynamic_cast<LM::Frontend::AST::ListExpr*>(&expr)) {
        return emit_list_expr(*list);
    } else if (auto grouping = dynamic_cast<LM::Frontend::AST::GroupingExpr*>(&expr)) {
        return emit_grouping_expr(*grouping);
    } else if (auto ternary = dynamic_cast<LM::Frontend::AST::TernaryExpr*>(&expr)) {
        return emit_ternary_expr(*ternary);
    } else if (auto index = dynamic_cast<LM::Frontend::AST::IndexExpr*>(&expr)) {
        return emit_index_expr(*index);
    } else if (auto member = dynamic_cast<LM::Frontend::AST::MemberExpr*>(&expr)) {
        return emit_member_expr(*member);
    } else if (auto tuple = dynamic_cast<LM::Frontend::AST::TupleExpr*>(&expr)) {
        return emit_tuple_expr(*tuple);
    } else if (auto dict = dynamic_cast<LM::Frontend::AST::DictExpr*>(&expr)) {
        return emit_dict_expr(*dict);
    } else if (auto range = dynamic_cast<LM::Frontend::AST::RangeExpr*>(&expr)) {
        return emit_range_expr(*range);
    } else if (auto lambda = dynamic_cast<LM::Frontend::AST::LambdaExpr*>(&expr)) {
        return emit_lambda_expr(*lambda);
    } else if (auto error_construct = dynamic_cast<LM::Frontend::AST::ErrorConstructExpr*>(&expr)) {
        return emit_error_construct_expr(*error_construct);
    } else if (auto ok_construct = dynamic_cast<LM::Frontend::AST::OkConstructExpr*>(&expr)) {
        return emit_ok_construct_expr(*ok_construct);
    } else if (auto fallible = dynamic_cast<LM::Frontend::AST::FallibleExpr*>(&expr)) {
        return emit_fallible_expr(*fallible);
    } else if (auto frame_inst = dynamic_cast<LM::Frontend::AST::FrameInstantiationExpr*>(&expr)) {
        return emit_frame_instantiation_expr(*frame_inst);
    } else if (auto this_expr = dynamic_cast<LM::Frontend::AST::ThisExpr*>(&expr)) {
        return emit_this_expr(*this_expr);
    } else if (auto channel_offer = dynamic_cast<LM::Frontend::AST::ChannelOfferExpr*>(&expr)) {
        return emit_channel_offer_expr(*channel_offer);
    } else if (auto channel_poll = dynamic_cast<LM::Frontend::AST::ChannelPollExpr*>(&expr)) {
        return emit_channel_poll_expr(*channel_poll);
    } else if (auto channel_send = dynamic_cast<LM::Frontend::AST::ChannelSendExpr*>(&expr)) {
        return emit_channel_send_expr(*channel_send);
    } else if (auto channel_recv = dynamic_cast<LM::Frontend::AST::ChannelRecvExpr*>(&expr)) {
        return emit_channel_recv_expr(*channel_recv);
    } else {
        report_error("Unknown expression type");
        return 0;
    }
}


TypePtr Generator::get_promoted_numeric_type(TypePtr left_type, TypePtr right_type) {
    // If either type is null, default to Int64
    if (!left_type || !right_type) {
        return std::make_shared<::Type>(::TypeTag::Int64);
    }
    
    // If either is string, result is string
    if (left_type->tag == ::TypeTag::String || right_type->tag == ::TypeTag::String) {
        return std::make_shared<::Type>(::TypeTag::String);
    }
    
    // If either is float, promote to the larger float type
    bool left_is_float = (left_type->tag == ::TypeTag::Float32 || left_type->tag == ::TypeTag::Float64);
    bool right_is_float = (right_type->tag == ::TypeTag::Float32 || right_type->tag == ::TypeTag::Float64);
    
    if (left_is_float || right_is_float) {
        if (left_type->tag == ::TypeTag::Float64 || right_type->tag == ::TypeTag::Float64) {
            return std::make_shared<::Type>(::TypeTag::Float64);
        }
        return std::make_shared<::Type>(::TypeTag::Float32);
    }
    
    // Both are integers - use the "smaller matches larger" strategy
    int left_rank = get_type_rank(left_type);
    int right_rank = get_type_rank(right_type);
    
    // If ranks are equal, prefer unsigned over signed to preserve unsigned semantics
    if (left_rank == right_rank) {
        bool left_is_unsigned = !is_signed_integer_type(left_type);
        bool right_is_unsigned = !is_signed_integer_type(right_type);
        
        if (left_is_unsigned) return left_type;
        if (right_is_unsigned) return right_type;
        
        // Both signed, return either
        return left_type;
    }
    
    // Return the type with higher rank (larger/more complex type)
    // But if the higher rank type is signed and lower rank is unsigned, 
    // and they're close in rank, prefer unsigned to avoid signed overflow
    TypePtr higher_type = (left_rank > right_rank) ? left_type : right_type;
    TypePtr lower_type = (left_rank > right_rank) ? right_type : left_type;
    
    bool higher_is_unsigned = !is_signed_integer_type(higher_type);
    bool lower_is_unsigned = !is_signed_integer_type(lower_type);
    
    // If lower is unsigned and higher is signed, and ranks are close, use unsigned version of higher
    if (lower_is_unsigned && !higher_is_unsigned && (left_rank - right_rank <= 2 || right_rank - left_rank <= 2)) {
        return get_unsigned_version(higher_type);
    }
    
    return higher_type;
}


int Generator::get_type_rank(TypePtr type) {
    if (!type) return 0;
    
    switch (type->tag) {
        case ::TypeTag::Int8: case ::TypeTag::UInt8: return 1;
        case ::TypeTag::Int16: case ::TypeTag::UInt16: return 2;
        case ::TypeTag::Int32: case ::TypeTag::UInt32: return 3;
        case ::TypeTag::Int: case ::TypeTag::UInt: case ::TypeTag::Int64: case ::TypeTag::UInt64: return 4;
        case ::TypeTag::Int128: case ::TypeTag::UInt128: return 5;
        case ::TypeTag::Float32: return 6;
        case ::TypeTag::Float64: return 7;
        case ::TypeTag::String: return 8;
        case ::TypeTag::Bool: return 0;
        default: return 0;
    }
}


bool Generator::is_signed_integer_type(TypePtr type) {
    if (!type) return false;
    return (type->tag == ::TypeTag::Int || type->tag == ::TypeTag::Int8 || 
            type->tag == ::TypeTag::Int16 || type->tag == ::TypeTag::Int32 || 
            type->tag == ::TypeTag::Int64 || type->tag == ::TypeTag::Int128);
}


TypePtr Generator::get_wider_integer_type(TypePtr left_type, TypePtr right_type) {
    if (!left_type || !right_type) {
        return std::make_shared<::Type>(::TypeTag::Int64);
    }
    
    // Define type precedence (from narrowest to widest)
    std::map<TypeTag, int> type_rank = {
        {::TypeTag::Int8, 1}, {::TypeTag::UInt8, 1},
        {::TypeTag::Int16, 2}, {::TypeTag::UInt16, 2},
        {::TypeTag::Int32, 3}, {::TypeTag::UInt32, 3},
        {::TypeTag::Int, 4}, {::TypeTag::UInt, 4},
        {::TypeTag::Int64, 5}, {::TypeTag::UInt64, 5},
        {::TypeTag::Int128, 6}, {::TypeTag::UInt128, 6}
    };
    
    int left_rank = type_rank[left_type->tag];
    int right_rank = type_rank[right_type->tag];
    
    if (left_rank >= right_rank) {
        return left_type;
    } else {
        return right_type;
    }
}


TypePtr Generator::get_unsigned_version(TypePtr type) {
    if (!type) return std::make_shared<::Type>(::TypeTag::UInt64);
    
    switch (type->tag) {
        case ::TypeTag::Int8: return std::make_shared<::Type>(::TypeTag::UInt8);
        case ::TypeTag::Int16: return std::make_shared<::Type>(::TypeTag::UInt16);
        case ::TypeTag::Int32: return std::make_shared<::Type>(::TypeTag::UInt32);
        case ::TypeTag::Int: 
        case ::TypeTag::Int64: return std::make_shared<::Type>(::TypeTag::UInt64);
        case ::TypeTag::Int128: return std::make_shared<::Type>(::TypeTag::UInt128);
        case ::TypeTag::UInt8: 
        case ::TypeTag::UInt16: 
        case ::TypeTag::UInt32: 
        case ::TypeTag::UInt: 
        case ::TypeTag::UInt64: 
        case ::TypeTag::UInt128: return type; // Already unsigned
        default: return std::make_shared<::Type>(::TypeTag::UInt64);
    }
}


TypePtr Generator::get_best_integer_type(const std::string& value_str, bool prefer_signed) {
    try {
        // Try to parse as unsigned long long to check the magnitude
        unsigned long long ull_val = std::stoull(value_str);
        
        // Check system support for 128-bit integers
        bool has_int128 = false;
#ifdef __SIZEOF_INT128__
        has_int128 = true;
#endif
        
        if (prefer_signed) {
            // For signed integers, check if it fits in various ranges
            if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<int8_t>::max())) {
                return std::make_shared<::Type>(::TypeTag::Int8);
            } else if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<int16_t>::max())) {
                return std::make_shared<::Type>(::TypeTag::Int16);
            } else if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<int32_t>::max())) {
                return std::make_shared<::Type>(::TypeTag::Int32);
            } else if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<int64_t>::max())) {
                return std::make_shared<::Type>(::TypeTag::Int64);
            } else if (has_int128) {
                return std::make_shared<::Type>(::TypeTag::Int128);
            } else {
                // Fallback to unsigned if too large for signed
                return get_best_integer_type(value_str, false);
            }
        } else {
            // For unsigned integers
            if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<uint8_t>::max())) {
                return std::make_shared<::Type>(::TypeTag::UInt8);
            } else if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<uint16_t>::max())) {
                return std::make_shared<::Type>(::TypeTag::UInt16);
            } else if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<uint32_t>::max())) {
                return std::make_shared<::Type>(::TypeTag::UInt32);
            } else if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<uint64_t>::max())) {
                return std::make_shared<::Type>(::TypeTag::UInt64);
            } else if (has_int128) {
                return std::make_shared<::Type>(::TypeTag::UInt128);
            } else {
                // If no 128-bit support, this is an overflow situation
                return std::make_shared<::Type>(::TypeTag::UInt64);
            }
        }
    } catch (const std::exception&) {
        // If parsing fails, default to Int64
        return std::make_shared<::Type>(::TypeTag::Int64);
    }
}


bool Generator::is_numeric_string(const std::string& str) {
    if (str.empty()) return false;
    
    char first = str[0];
    if (!(std::isdigit(first) || first == '+' || first == '-' || first == '.')) {
        return false;
    }
    
    // Check if all characters are valid for a number
    for (char c : str) {
        if (!std::isdigit(c) && c != '.' && c != '+' && c != '-' && 
            c != 'e' && c != 'E' && c != 'u' && c != 'U' && 
            c != 'l' && c != 'L' && c != 'f' && c != 'F') {
            return false;
        }
    }
    return true;
}


bool Generator::types_match(TypePtr type1, TypePtr type2) {
    if (!type1 || !type2) return false;
    return type1->tag == type2->tag;
}

// Expression handlers

Reg Generator::emit_literal_expr(LM::Frontend::AST::LiteralExpr& expr, TypePtr expected_type) {
    Reg dst = allocate_register();
    
    // CRITICAL FIX: Use AST's inferred type first, then expected type, then default inference
    // This ensures that types preserved from constant propagation are respected
    TypePtr target_type = expr.inferred_type ? expr.inferred_type : expected_type;
    
    // Create ValuePtr based on literal value
    ValuePtr const_val;
    
    if (std::holds_alternative<std::string>(expr.value)) {
        std::string stringValue = std::get<std::string>(expr.value);
        
        // Try to determine if this string represents a pure number
        bool isNumeric = false;
        bool isFloat = false;
        
        if (!stringValue.empty()) {
            char first = stringValue[0];
            if (std::isdigit(first) || first == '+' || first == '-' || first == '.') {
                // Check if the ENTIRE string is a valid number
                bool hasInvalidChars = false;
                for (char c : stringValue) {
                    if (!std::isdigit(c) && c != '.' && c != '+' && c != '-' && 
                        c != 'e' && c != 'E' && c != 'u' && c != 'U' && 
                        c != 'l' && c != 'L' && c != 'f' && c != 'F') {
                        hasInvalidChars = true;
                        break;
                    }
                }
                
                if (!hasInvalidChars) {
                    isNumeric = true;
                    // Check if it's a float
                    if (stringValue.find('.') != std::string::npos || 
                        stringValue.find('e') != std::string::npos || 
                        stringValue.find('E') != std::string::npos) {
                        isFloat = true;
                    }
                }
            }
        }
        
        if (isNumeric) {
            if (isFloat) {
                // Create float value
                auto float_type = target_type ? target_type : std::make_shared<::Type>(::TypeTag::Float64);
                try {
                    // For very small or very large numbers, preserve the original string representation
                    // to avoid precision loss during double conversion
                    bool isVerySmallOrLarge = (stringValue.find("e-") != std::string::npos || 
                                             stringValue.find("E-") != std::string::npos ||
                                             stringValue.find("e+") != std::string::npos ||
                                             stringValue.find("E+") != std::string::npos);
                    
                    if (isVerySmallOrLarge) {
                        // Preserve original string representation for scientific notation
                        const_val = std::make_shared<Value>(float_type, stringValue);
                    } else {
                        // For normal numbers, parse and convert
                        long double floatVal = std::stold(stringValue);
                        const_val = std::make_shared<Value>(float_type, floatVal);
                    }
                } catch (const std::exception& e) {
                    // If parsing fails, treat as string
                    auto string_type = std::make_shared<::Type>(::TypeTag::String);
                    const_val = std::make_shared<Value>(string_type, stringValue);
                    current_function_->instructions.back().const_val->type = string_type;
                }
            } else {
                // Create integer value - use target type if provided
                TypePtr int_type = target_type;
                
                if (!int_type) {
                    // Use expected type if available, otherwise infer from the literal value
                    if (expected_type) {
                        int_type = expected_type;
                    } else {
                        // For simple small literals, default to Int64 to avoid type mismatches
                        // This is a conservative approach that works well with mixed operations
                        try {
                            int64_t test_val = std::stoll(stringValue);
                            // If it fits in int64 and is a small number, use Int64
                            if (test_val >= 0 && test_val <= 1000000) {
                                int_type = std::make_shared<::Type>(::TypeTag::Int64);
                            } else {
                                // For larger values, use automatic type selection
                                int_type = get_best_integer_type(stringValue, true);
                            }
                        } catch (const std::exception&) {
                            // If parsing as signed fails, use automatic selection
                            int_type = get_best_integer_type(stringValue, true);
                        }
                    }
                }
                
                try {
                    // Check if it's a negative number
                    if (stringValue[0] == '-') {
                        // Parse as signed integer
                        int64_t intVal = std::stoll(stringValue);
                        const_val = std::make_shared<Value>(int_type, intVal);
                    } else {
                        // Check if the expected type is unsigned
                        bool expectUnsigned = (int_type && 
                                             (int_type->tag == TypeTag::UInt || int_type->tag == TypeTag::UInt8 ||
                                              int_type->tag == TypeTag::UInt16 || int_type->tag == TypeTag::UInt32 ||
                                              int_type->tag == TypeTag::UInt64 || int_type->tag == TypeTag::UInt128));
                        
                        if (expectUnsigned) {
                            // Expected type is unsigned, parse as unsigned
                            uint64_t uintVal = std::stoull(stringValue);
                           // std::cout << "[DEBUG] Parsing unsigned literal '" << stringValue
                           //           << "' as uint64_t: " << uintVal << std::endl;
                            const_val = std::make_shared<Value>(int_type, uintVal);
                           // std::cout << "[DEBUG] Created Value with data: '" << const_val->data 
                           //           << "' and type tag: " << static_cast<int>(const_val->type->tag) << std::endl;
                        } else {
                            // Expected type is signed or no specific expectation
                            uint64_t uintVal = std::stoull(stringValue);
                            
                            // Check if it fits in signed int64 range
                            if (uintVal <= 9223372036854775807ULL) {
                                // Fits in signed range, use as signed
                                int64_t intVal = static_cast<int64_t>(uintVal);
                                const_val = std::make_shared<Value>(int_type, intVal);
                            } else {
                                // Too large for signed, use as unsigned
                                const_val = std::make_shared<Value>(int_type, uintVal);
                            }
                        }
                    }
                } catch (const std::exception& e) {
                    // If parsing fails, treat as string
                    auto string_type = std::make_shared<::Type>(::TypeTag::String);
                    const_val = std::make_shared<Value>(string_type, stringValue);
                    current_function_->instructions.back().const_val->type = string_type;
                }
            }
        } else {
            // String value (already parsed, quotes removed by parser)
            // For quoted string literals from the parser, always treat as string type
            auto string_type = std::make_shared<::Type>(::TypeTag::String);
            const_val = std::make_shared<Value>(string_type, stringValue);
        }
    } else if (std::holds_alternative<bool>(expr.value)) {
        // Create boolean value
        auto bool_type = std::make_shared<::Type>(::TypeTag::Bool);
        bool boolVal = std::get<bool>(expr.value);
        const_val = std::make_shared<Value>(bool_type, boolVal);
    } else if (std::holds_alternative<std::nullptr_t>(expr.value)) {
        // Create nil value
        auto nil_type = std::make_shared<::Type>(::TypeTag::Nil);
        const_val = std::make_shared<Value>(nil_type, std::string("nil"));
    } else {
        // Default to nil
        auto nil_type = std::make_shared<::Type>(::TypeTag::Nil);
        const_val = std::make_shared<Value>(nil_type, "");
    }
    
    // Set type BEFORE emitting so it's available during emit_instruction
    if (const_val) {
        // Use the target type (AST inferred type takes priority)
        TypePtr final_type = target_type ? target_type : const_val->type;
        
        Type abi_type = language_type_to_abi_type(final_type);
        set_register_language_type(dst, final_type);
        set_register_type(dst, final_type);
        
        // Update the const_val type to match the target type
        if (target_type && target_type != const_val->type) {
            const_val->type = target_type;
        }
        
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, abi_type, dst, const_val));
    } else {
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Void, dst, const_val));
    }
    return dst;
}


Reg Generator::emit_variable_expr(LM::Frontend::AST::VariableExpr& expr) {
    // Check if this is a captured variable in a lambda
    if (env_register_ != UINT32_MAX) {
        auto it = std::find(current_lambda_captures_.begin(), current_lambda_captures_.end(), expr.name);
        if (it != current_lambda_captures_.end()) {
            size_t index = std::distance(current_lambda_captures_.begin(), it);
            Reg result = allocate_register();
            
            // In Tuple: (lambda_name, capture0, capture1, ...)
            // Captured variables start at index 1
            Reg idx_reg = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, idx_reg, std::make_shared<Value>(std::make_shared<::Type>(::TypeTag::Int64), (int64_t)(index + 1))));
            
            Type abi_type = Type::I64;
            if (expr.inferred_type) {
                abi_type = language_type_to_abi_type(expr.inferred_type);
            }
            
            emit_instruction(LIR_Inst(LIR_Op::TupleGet, abi_type, result, env_register_, idx_reg));
            
            if (expr.inferred_type) {
                set_register_language_type(result, expr.inferred_type);
            }
            return result;
        }
    }

    // Check if it's a global module variable accessed directly (e.g. within the module itself)
    if (!current_module_.empty() && current_module_ != "root") {
        std::string qualified_name = current_module_ + "." + expr.name;
        Reg reg = resolve_variable(expr.name);
        if (reg != UINT32_MAX) return reg;

        // If not local, try LoadGlobal
        Reg result = allocate_register();
        LIR_Inst load_inst(LIR_Op::LoadGlobal, Type::Ptr, result, 0, 0);
        load_inst.func_name = qualified_name;
        emit_instruction(load_inst);
        if (expr.inferred_type) {
            set_register_language_type(result, expr.inferred_type);
            set_register_abi_type(result, language_type_to_abi_type(expr.inferred_type));
        }
        return result;
    }

    // First check if this is a module variable access (e.g., "math.pi")
    size_t dot_pos = expr.name.find("::");
    if (dot_pos != std::string::npos) {
        std::string module_name = expr.name.substr(0, dot_pos);
        std::string symbol_name = expr.name.substr(dot_pos + 2);
        
        // Check for alias mapping
        auto alias_it = import_aliases_.find(module_name);
        if (alias_it != import_aliases_.end()) {
            module_name = alias_it->second;
        }
        
        // Resolve module symbol
        std::string qualified_name = module_name + "::" + symbol_name;
        ModuleSymbolInfo* symbol = resolve_module_symbol(qualified_name);
        if (symbol && symbol->is_variable) {
            if (!can_access_module_symbol(*symbol, current_module_)) {
                report_error("Cannot access private/protected variable: " + qualified_name);
                return 0;
            }
            
            // Load the actual module variable value
            Reg result = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::Load, Type::Ptr, result, 0, 0));
            // Note: Module variable type information is not available in ModuleSymbolInfo
            // Type information should be obtained from the module's type system
            return result;
        }
    }
    
    // Check regular variable scope
    Reg reg = resolve_variable(expr.name);
    if (reg == UINT32_MAX) {
        // Check if it's a function name used as a value (first-class functions)
        if (function_table_.find(expr.name) != function_table_.end() || 
            LIRFunctionManager::getInstance().hasFunction(expr.name)) {
            
            Reg func_reg = allocate_register();
            auto func_type = std::make_shared<::Type>(::TypeTag::Function);
            // In our LIR/VM, functions are referred to by name strings
            auto string_type = std::make_shared<::Type>(::TypeTag::String);
            ValuePtr name_val = std::make_shared<Value>(string_type, expr.name);
            emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Ptr, func_reg, name_val));
            set_register_language_type(func_reg, func_type);
            set_register_abi_type(func_reg, Type::Ptr);
            return func_reg;
        }

        report_error("Undefined variable: " + expr.name);
        return 0;
    }
    
    // === SHARED CELL TASK BODY HANDLING ===
    // Check if we're in a task body and this variable is a shared variable
    if (!parallel_block_cell_ids_.empty() && parallel_block_cell_ids_.find(expr.name) != parallel_block_cell_ids_.end()) {
        // This is a shared variable in a task body - use SharedCell operations
       // std::cout << "[DEBUG] Task body accessing shared variable '" << expr.name << "' via SharedCell" << std::endl;
        
        // Get the SharedCell ID register for this variable
        Reg cell_id_reg = parallel_block_cell_ids_[expr.name];
        
        // Load the current value from SharedCell
        Reg value_reg = allocate_register();
        emit_instruction(LIR_Inst(LIR_Op::SharedCellLoad, value_reg, cell_id_reg, 0));
        
        // Set type information
        if (expr.inferred_type) {
            set_register_type(value_reg, expr.inferred_type);
            set_register_language_type(value_reg, expr.inferred_type);
            set_register_abi_type(value_reg, language_type_to_abi_type(expr.inferred_type));
        } else {
            auto any_type = std::make_shared<::Type>(::TypeTag::Any);
            set_register_type(value_reg, any_type);
        }
        
        return value_reg;
    }
    
    // Set the type information for the register if available
    if (expr.inferred_type) {
        set_register_type(reg, expr.inferred_type);
        set_register_language_type(reg, expr.inferred_type);
        set_register_abi_type(reg, language_type_to_abi_type(expr.inferred_type));
    } else {
        // Set a default type if no inference is available
        auto any_type = std::make_shared<::Type>(::TypeTag::Any);
        set_register_type(reg, any_type);
    }
    
    return reg;
}


Reg Generator::emit_interpolated_string_expr(LM::Frontend::AST::InterpolatedStringExpr& expr) {
    auto string_type = std::make_shared<::Type>(::TypeTag::String);

    if (expr.parts.empty()) {
        Reg result = allocate_register();
        ValuePtr result_val = std::make_shared<Value>(string_type, std::string(""));
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Ptr, result, result_val));
        set_register_language_type(result, string_type);
        return result;
    }

    // Check for constant folding opportunity
    bool all_parts_are_string_literals = true;
    std::string folded_result = "";
    
    for (const auto& part : expr.parts) {
        if (std::holds_alternative<std::string>(part)) {
            folded_result += std::get<std::string>(part);
        } else {
            all_parts_are_string_literals = false;
            break;
        }
    }
    
    // Constant folding: if all parts are string literals, fold them
    if (all_parts_are_string_literals) {
        Reg result = allocate_register();
        ValuePtr result_val = std::make_shared<Value>(string_type, folded_result);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Ptr, result, result_val));
        set_register_language_type(result, string_type);
        return result;
    }

    // For complex interpolations, use STR_FORMAT
    // Build format string and collect argument registers
    std::string format_string = "";
    std::vector<Reg> arg_regs;
    
    for (const auto& part : expr.parts) {
        if (std::holds_alternative<std::string>(part)) {
            format_string += std::get<std::string>(part);
        } else if (std::holds_alternative<std::shared_ptr<LM::Frontend::AST::Expression>>(part)) {
            format_string += "%s" ; // Use standard format marker
            auto expr_part = std::get<std::shared_ptr<LM::Frontend::AST::Expression>>(part);
            Reg expr_reg = emit_expr(*expr_part);
            arg_regs.push_back(expr_reg);
        }
    }
    
    // Emit STR_FORMAT instruction
    Reg result = allocate_register();
    Reg format_reg = allocate_register();
    ValuePtr format_val = std::make_shared<Value>(string_type, format_string);
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Ptr, format_reg, format_val));
    
    // Handle multiple arguments by chaining STR_FORMAT calls
    Reg current_result = format_reg;
    for (size_t i = 0; i < arg_regs.size(); i++) {
        if (i == 0) {
            // First argument: format with first arg
            emit_instruction(LIR_Inst(LIR_Op::STR_FORMAT, result, format_reg, arg_regs[i]));
            current_result = result;
        } else {
            // Subsequent arguments: format previous result with next arg
            Reg temp_result = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::STR_FORMAT, temp_result, current_result, arg_regs[i]));
            current_result = temp_result;
            if (i == arg_regs.size() - 1) {
                // Final result is in temp_result, move to result register
                emit_instruction(LIR_Inst(LIR_Op::Mov, result, temp_result, 0));
            }
        }
    }
    
    set_register_language_type(result, string_type);
    return result;
}


Reg Generator::emit_binary_expr(LM::Frontend::AST::BinaryExpr& expr) {
    if (expr.op == LM::Frontend::TokenType::AND || expr.op == LM::Frontend::TokenType::OR) {
        LIR_BasicBlock* right_block = create_basic_block("logic_right");
        LIR_BasicBlock* end_block = create_basic_block("logic_end");
        Reg result = allocate_register();
        set_register_language_type(result, std::make_shared<::Type>(::TypeTag::Bool));
        Reg left = emit_expr(*expr.left);
        if (expr.op == LM::Frontend::TokenType::AND) {
            emit_instruction(LIR_Inst(LIR_Op::Mov, Type::Bool, result, left, 0));
            emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, left, 0, end_block->id));
        } else {
            emit_instruction(LIR_Inst(LIR_Op::Mov, Type::Bool, result, left, 0));
            emit_instruction(LIR_Inst(LIR_Op::JumpIf, 0, left, 0, end_block->id));
        }
        add_block_edge(get_current_block(), right_block);
        add_block_edge(get_current_block(), end_block);
        set_current_block(right_block);
        Reg right = emit_expr(*expr.right);
        emit_instruction(LIR_Inst(LIR_Op::Mov, Type::Bool, result, right, 0));
        if (get_current_block() && !get_current_block()->has_terminator()) {
            emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, end_block->id));
            add_block_edge(get_current_block(), end_block);
        }
        set_current_block(end_block);
        return result;
    }

    // Handle PLUS operator - check for string concatenation first
    if (expr.op == LM::Frontend::TokenType::PLUS) {
        // Emit left and right operands FIRST to get their types
        Reg left = emit_expr(*expr.left);
        Reg right = emit_expr(*expr.right);
        
        TypePtr left_type = get_register_type(left);
        TypePtr right_type = get_register_type(right);
        
        // Check if EITHER operand is a string type
        bool left_is_string = (left_type && left_type->tag == ::TypeTag::String);
        bool right_is_string = (right_type && right_type->tag == ::TypeTag::String);
        
        if (left_is_string || right_is_string) {
            // Convert non-string operand to string using ToString
            if (!left_is_string) {
                Reg str_left = allocate_register();
                emit_instruction(LIR_Inst(LIR_Op::ToString, Type::Ptr, str_left, left, 0));
                auto string_type = std::make_shared<::Type>(::TypeTag::String);
                set_register_language_type(str_left, string_type);
                left = str_left;
            }
            if (!right_is_string) {
                Reg str_right = allocate_register();
                emit_instruction(LIR_Inst(LIR_Op::ToString, Type::Ptr, str_right, right, 0));
                auto string_type = std::make_shared<::Type>(::TypeTag::String);
                set_register_language_type(str_right, string_type);
                right = str_right;
            }
            
            // Perform string concatenation
            Reg dst = allocate_register();
            auto string_type = std::make_shared<::Type>(::TypeTag::String);
            set_register_language_type(dst, string_type);
            emit_instruction(LIR_Inst(LIR_Op::STR_CONCAT, Type::Ptr, dst, left, right));
            return dst;
        }
    }
    
    // Handle as arithmetic operation
    Reg left = emit_expr(*expr.left);
    Reg right = emit_expr(*expr.right);
    Reg dst = allocate_register();
    
    // Map operator to LIR operation
    LIR_Op op;
    if (expr.op == LM::Frontend::TokenType::PLUS) op = LIR_Op::Add;
    else if (expr.op == LM::Frontend::TokenType::MINUS) op = LIR_Op::Sub;
    else if (expr.op == LM::Frontend::TokenType::STAR) op = LIR_Op::Mul;
    else if (expr.op == LM::Frontend::TokenType::SLASH) {
        // Handle division with proper type checking
        TypePtr left_type = get_register_type(left);
        TypePtr right_type = get_register_type(right);
        
        bool left_is_int = left_type && 
            (left_type->tag == ::TypeTag::Int || left_type->tag == ::TypeTag::Int64 ||
             left_type->tag == ::TypeTag::Int32 || left_type->tag == ::TypeTag::Int16 ||
             left_type->tag == ::TypeTag::Int8 || left_type->tag == ::TypeTag::UInt ||
             left_type->tag == ::TypeTag::UInt64 || left_type->tag == ::TypeTag::UInt32 ||
             left_type->tag == ::TypeTag::UInt16 || left_type->tag == ::TypeTag::UInt8);
        
        bool right_is_int = right_type && 
            (right_type->tag == ::TypeTag::Int || right_type->tag == ::TypeTag::Int64 ||
             right_type->tag == ::TypeTag::Int32 || right_type->tag == ::TypeTag::Int16 ||
             right_type->tag == ::TypeTag::Int8 || right_type->tag == ::TypeTag::UInt ||
             right_type->tag == ::TypeTag::UInt64 || right_type->tag == ::TypeTag::UInt32 ||
             right_type->tag == ::TypeTag::UInt16 || right_type->tag == ::TypeTag::UInt8);
        
        if (left_is_int && right_is_int) {
            // INTEGER DIVISION: 284/4 = 71 (no decimal)
            op = LIR_Op::Div;
        } else {
            // FLOAT DIVISION: 10/2.847 = 3.512... (with decimal)
            op = LIR_Op::Div;
            
            // Convert integer operands to float for division
            if (left_is_int) {
                Reg float_left = allocate_register();
                emit_instruction(LIR_Inst(LIR_Op::Cast, Type::F64, float_left, left, 0));
                left = float_left;
            }
            if (right_is_int) {
                Reg float_right = allocate_register();
                emit_instruction(LIR_Inst(LIR_Op::Cast, Type::F64, float_right, right, 0));
                right = float_right;
            }
        }
    }
    else if (expr.op == LM::Frontend::TokenType::MODULUS) op = LIR_Op::Mod;
    else if (expr.op == LM::Frontend::TokenType::POWER) {
        Reg res = allocate_register();
        auto float_type = std::make_shared<::Type>(::TypeTag::Float64);
        Reg f_left = left;
        if (get_register_type(left)->tag != ::TypeTag::Float64) {
            f_left = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::Cast, Type::F64, f_left, left, 0));
        }
        Reg f_right = right;
        if (get_register_type(right)->tag != ::TypeTag::Float64) {
            f_right = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::Cast, Type::F64, f_right, right, 0));
        }
        LIR_Inst call_inst(LIR_Op::CallBuiltin, Type::F64, res, 0);
        call_inst.func_name = "pow";
        call_inst.call_args = {f_left, f_right};
        emit_instruction(call_inst);
        set_register_type(res, float_type);
        return res;
    }
    else if (expr.op == LM::Frontend::TokenType::EQUAL_EQUAL) op = LIR_Op::CmpEQ;
    else if (expr.op == LM::Frontend::TokenType::BANG_EQUAL) op = LIR_Op::CmpNEQ;
    else if (expr.op == LM::Frontend::TokenType::LESS) op = LIR_Op::CmpLT;
    else if (expr.op == LM::Frontend::TokenType::LESS_EQUAL) op = LIR_Op::CmpLE;
    else if (expr.op == LM::Frontend::TokenType::GREATER) op = LIR_Op::CmpGT;
    else if (expr.op == LM::Frontend::TokenType::GREATER_EQUAL) op = LIR_Op::CmpGE;


    else if (expr.op == LM::Frontend::TokenType::CARET) op = LIR_Op::Xor;
    else {
        report_error("Unknown binary operator");
        return 0;
    }
    
    // Infer result type based on operands and operation
    TypePtr result_type = nullptr;
    TypePtr left_type = get_register_type(left);
    TypePtr right_type = get_register_type(right);
    
    // For arithmetic operations, determine result type
    if (op == LIR_Op::Add || op == LIR_Op::Sub || op == LIR_Op::Mul || op == LIR_Op::Div || op == LIR_Op::Mod) {
        // If either operand is float, result is float
        if ((left_type && left_type->tag == ::TypeTag::Float64) || 
            (right_type && right_type->tag == ::TypeTag::Float64)) {
            result_type = std::make_shared<::Type>(::TypeTag::Float64);
        } else if ((left_type && left_type->tag == ::TypeTag::Float32) || 
                   (right_type && right_type->tag == ::TypeTag::Float32)) {
            result_type = std::make_shared<::Type>(::TypeTag::Float32);
        } else {
            // For integer operations, preserve signedness and promote to wider type
            result_type = get_promoted_numeric_type(left_type, right_type);
        }
        
        // Check for type mismatches and re-emit if needed
        if (left_type && right_type && result_type) {
            // Implement "smaller matches larger" strategy
            int left_rank = get_type_rank(left_type);
            int right_rank = get_type_rank(right_type);
            
            // Re-emit the smaller/lower rank operand to match the larger one
            if (left_rank < right_rank) {
                if (auto left_literal = dynamic_cast<LM::Frontend::AST::LiteralExpr*>(expr.left.get())) {
                    left = emit_literal_expr(*left_literal, right_type);
                    left_type = right_type;
                }
            } else if (right_rank < left_rank) {
                if (auto right_literal = dynamic_cast<LM::Frontend::AST::LiteralExpr*>(expr.right.get())) {
                    right = emit_literal_expr(*right_literal, left_type);
                    right_type = left_type;
                }
            }
            // If ranks are equal but types differ, prefer signed to avoid unsigned promotion issues
            else if (left_rank == right_rank && !types_match(left_type, right_type)) {
                bool left_is_signed = is_signed_integer_type(left_type);
                bool right_is_signed = is_signed_integer_type(right_type);
                
                if (!left_is_signed && right_is_signed) {
                    auto left_literal = dynamic_cast<LM::Frontend::AST::LiteralExpr*>(expr.left.get());
                    if (left_literal) {
                        left = emit_literal_expr(*left_literal, right_type);
                        left_type = right_type;
                    }
                } else if (left_is_signed && !right_is_signed) {
                    auto right_literal = dynamic_cast<LM::Frontend::AST::LiteralExpr*>(expr.right.get());
                    if (right_literal) {
                        right = emit_literal_expr(*right_literal, left_type);
                        right_type = left_type;
                    }
                }
            }
        }
    } else if (op == LIR_Op::CmpEQ || op == LIR_Op::CmpNEQ || op == LIR_Op::CmpLT || 
               op == LIR_Op::CmpLE || op == LIR_Op::CmpGT || op == LIR_Op::CmpGE) {
        // Comparison operations return bool
        result_type = std::make_shared<::Type>(::TypeTag::Bool);
    } else if (op == LIR_Op::And || op == LIR_Op::Or) {
        // Logical operations return bool
        result_type = std::make_shared<::Type>(::TypeTag::Bool);
    } else if (op == LIR_Op::Xor) {
        // Bitwise XOR should preserve integer types like arithmetic operations
        result_type = get_promoted_numeric_type(left_type, right_type);
    }
    
    // Set type BEFORE emitting so it's available during emit_instruction
    if (result_type) {
        set_register_type(dst, result_type);
        Type abi_type = language_type_to_abi_type(result_type);
        emit_instruction(LIR_Inst(op, abi_type, dst, left, right));
    } else {
        // Fallback for operations without result type
       // std::cout << "[DEBUG] Emitting instruction: op=" << static_cast<int>(op) << " dst=" << dst << " left=" << left << " right=" << right << std::endl;
        emit_instruction(LIR_Inst(op, dst, left, right));
    }
    
    return dst;
}


Reg Generator::emit_unary_expr(LM::Frontend::AST::UnaryExpr& expr) {
    Reg operand = emit_expr(*expr.right);
    Reg dst = allocate_register();
    TypePtr operand_type = get_register_type(operand);
    TypePtr result_type = nullptr;
    
    if (expr.op == LM::Frontend::TokenType::MINUS) {
        // Result type is same as operand type
        result_type = operand_type;
        set_register_type(dst, result_type);
        // Use Neg operation for unary minus (more efficient than Sub from 0)
        emit_instruction(LIR_Inst(LIR_Op::Neg, dst, operand, 0));
    } else if (expr.op == LM::Frontend::TokenType::PLUS) {
        // Result type is same as operand type
        result_type = operand_type;
        set_register_type(dst, result_type);
        // Unary plus - just copy the value (no operation needed)
        emit_instruction(LIR_Inst(LIR_Op::Mov, dst, operand, 0));
    } else if (expr.op == LM::Frontend::TokenType::BANG) {
        // Result type is bool
        result_type = std::make_shared<::Type>(::TypeTag::Bool);
        set_register_type(dst, result_type);
        // Logical NOT - compare with true and negate (operand != true gives us !operand)
        Reg true_reg = allocate_register();
        auto bool_type = std::make_shared<::Type>(::TypeTag::Bool);
        ValuePtr true_val = std::make_shared<Value>(bool_type, true);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Bool, true_reg, true_val));
        set_register_type(true_reg, bool_type);
        emit_instruction(LIR_Inst(LIR_Op::CmpNEQ, dst, operand, true_reg));
    } else if (expr.op == LM::Frontend::TokenType::TILDE) {
        // Result type is int
        auto int_type = std::make_shared<::Type>(::TypeTag::Int);
        result_type = int_type;
        set_register_type(dst, result_type);
        // Bitwise NOT - XOR with all bits set (for 64-bit: -1)
        Reg all_bits = allocate_register();
        ValuePtr neg_one_val = std::make_shared<Value>(int_type, static_cast<int64_t>(-1));
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, all_bits, neg_one_val));
        set_register_type(all_bits, int_type);
        emit_instruction(LIR_Inst(LIR_Op::Xor, dst, operand, all_bits));
    } else if (expr.op == LM::Frontend::TokenType::QUESTION) {
        // Error propagation operator (?)
        // This should check if operand is an error, and if so, return early from the function
        // Pattern: if (is_error(operand)) return operand; else return unwrap(operand);
        
        // Check if operand is an error
        Reg is_error_reg = allocate_register();
        auto bool_type = std::make_shared<::Type>(::TypeTag::Bool);
        set_register_type(is_error_reg, bool_type);
        emit_instruction(LIR_Inst(LIR_Op::IsError, Type::Bool, is_error_reg, operand, 0));
        
        if (cfg_context_.building_cfg) {
            // CFG mode: create blocks for error handling
            LIR_BasicBlock* error_block = create_basic_block("error_propagation");
            LIR_BasicBlock* success_block = create_basic_block("success_unwrap");
            
            // If it's an error, jump to error propagation block
            emit_instruction(LIR_Inst(LIR_Op::JumpIf, Type::Void, 0, is_error_reg, 0, error_block->id));
            
            // Add unconditional jump to success block (fall-through case)
            emit_instruction(LIR_Inst(LIR_Op::Jump, Type::Void, 0, 0, 0, success_block->id));
            
            // Set up CFG edges
            add_block_edge(get_current_block(), error_block);
            add_block_edge(get_current_block(), success_block);
            
            // === Success Block: unwrap the value ===
            set_current_block(success_block);
            
            // Create a register for the unwrapped value
            Reg unwrapped_reg = allocate_register();
            
            // Try to determine the inner type from the Result type
            result_type = operand_type;
            set_register_type(unwrapped_reg, result_type);
            set_register_type(dst, result_type);
            
            // Unwrap the value (this will be the success case)
            emit_instruction(LIR_Inst(LIR_Op::Unwrap, Type::I64, unwrapped_reg, operand, 0));
            
            // Move unwrapped value to destination
            emit_instruction(LIR_Inst(LIR_Op::Mov, Type::I64, dst, unwrapped_reg, 0));
            
            // === Error Block: propagate error by returning ===
            set_current_block(error_block);
            
            // For proper error propagation, return the error value directly
            emit_instruction(LIR_Inst(LIR_Op::Return, Type::Void, operand, 0, 0));
            
            // Mark error block as terminated since it has a return
            error_block->terminated = true;
            
            // Switch back to success block for continuation
            set_current_block(success_block);
            
            // Note: The success block intentionally doesn't have a terminator
            // because it continues with the next statement in the calling context
            
        } else {
            // Linear mode: use labels and jumps
            uint32_t error_label = generate_label();
            uint32_t continue_label = generate_label();
            
            // If it's an error, jump to error propagation
            emit_instruction(LIR_Inst(LIR_Op::JumpIf, Type::Void, 0, is_error_reg, 0, error_label));
            
            // Success path: unwrap the value
            Reg unwrapped_reg = allocate_register();
            
            // Try to determine the inner type from the Result type
            result_type = operand_type;
            set_register_type(unwrapped_reg, result_type);
            set_register_type(dst, result_type);
            
            // Unwrap the value (this will be the success case)
            emit_instruction(LIR_Inst(LIR_Op::Unwrap, Type::I64, unwrapped_reg, operand, 0));
            
            // Move unwrapped value to destination
            emit_instruction(LIR_Inst(LIR_Op::Mov, Type::I64, dst, unwrapped_reg, 0));
            
            // Jump to continue execution
            emit_instruction(LIR_Inst(LIR_Op::Jump, Type::Void, 0, 0, 0, continue_label));
            
            // Error propagation block
            emit_instruction(LIR_Inst(LIR_Op::Label, Type::Void, error_label, 0, 0));
            
            // For proper error propagation, return the error value directly
            emit_instruction(LIR_Inst(LIR_Op::Return, Type::Void, operand, 0, 0));
            
            // Continue execution label
            emit_instruction(LIR_Inst(LIR_Op::Label, Type::Void, continue_label, 0, 0));
        }
        
       // std::cout << "[DEBUG] Generated error propagation (?) for register " << operand 
      //            << " -> " << dst << std::endl;
    } else {
        report_error("Unknown unary operator");
        return 0;
    }
    
    return dst;
}


Reg Generator::emit_call_expr(LM::Frontend::AST::CallExpr& expr) {
    if (auto var_expr = dynamic_cast<LM::Frontend::AST::VariableExpr*>(expr.callee.get())) {
        std::string func_name = var_expr->name;

        // Try looking up in imported symbols to find the actual qualified name
        if (expr.inferred_type && expr.inferred_type->tag == ::TypeTag::Frame) {
            FrameType ft = std::get<FrameType>(expr.inferred_type->extra);
            func_name = ft.name;
        }

        // Check if it's a frame instantiation
        auto frame_it = frame_table_.find(func_name);
        if (frame_it == frame_table_.end()) {
            // Fallback for namespaced functions if not a frame
            if (expr.inferred_type && expr.inferred_type->tag == ::TypeTag::Function) {
                // We might need to check if the function name is qualified
                // For now, if we found it in TypeChecker, it should be in our table under some name
            }
        }

        if (frame_it != frame_table_.end()) {
            // Treat as instantiation
            Reg frame_reg = allocate_register();
            const FrameInfo& frame_info = frame_it->second;

            // NewFrame allocates the object
            LIR_Inst new_frame_inst(LIR_Op::NewFrame, Type::Ptr, frame_reg, 0, 0, static_cast<uint32_t>(frame_info.total_field_size));
            new_frame_inst.func_name = func_name;
            emit_instruction(new_frame_inst);

            // Set frame type
            auto frame_type = std::make_shared<::Type>(::TypeTag::Frame);
            FrameType ft;
            ft.name = func_name;
            frame_type->extra = ft;
            set_register_language_type(frame_reg, frame_type);
            set_register_abi_type(frame_reg, Type::Ptr);

            // 1. Set default values for ALL fields
            if (frame_info.declaration) {
                for (size_t i = 0; i < frame_info.declaration->fields.size(); ++i) {
                    auto field = frame_info.declaration->fields[i];
                    Reg val_reg = 0;
                    if (field->defaultValue) {
                        val_reg = emit_expr(*field->defaultValue);
                    } else {
                        val_reg = allocate_register();
                        ValuePtr nil_val = std::make_shared<Value>(std::make_shared<::Type>(::TypeTag::Nil), "");
                        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Void, val_reg, nil_val));
                    }
                    emit_instruction(LIR_Inst(LIR_Op::FrameSetField, Type::Void, frame_reg, static_cast<uint32_t>(i), val_reg));
                }
            }

            // 2. Overwrite with named arguments
            for (const auto& [name, arg_expr] : expr.namedArgs) {
                auto offset_it = frame_info.field_offsets.find(name);
                if (offset_it != frame_info.field_offsets.end()) {
                    Reg val_reg = emit_expr(*arg_expr);
                    emit_instruction(LIR_Inst(LIR_Op::FrameSetField, Type::Void, frame_reg, static_cast<uint32_t>(offset_it->second), val_reg));
                }
            }

            // 3. Call init if present
            if (frame_info.has_init) {
                std::string init_name = func_name + ".init";
                std::vector<Reg> arg_regs;
                arg_regs.push_back(frame_reg);

                // Track which named arguments are consumed by init
                std::unordered_set<std::string> consumed_named_args;

                // Match arguments to init parameters
                if (frame_info.declaration && frame_info.declaration->init) {
                    const auto& init = frame_info.declaration->init;

                    // 3a. Positional arguments match required parameters
                    size_t pos_idx = 0;
                    for (; pos_idx < expr.arguments.size() && pos_idx < init->parameters.size(); ++pos_idx) {
                        arg_regs.push_back(emit_expr(*expr.arguments[pos_idx]));
                    }

                    // 3b. Remaining required parameters must be matched by named arguments
                    for (; pos_idx < init->parameters.size(); ++pos_idx) {
                        const std::string& param_name = init->parameters[pos_idx].first;
                        auto it = expr.namedArgs.find(param_name);
                        if (it != expr.namedArgs.end()) {
                            arg_regs.push_back(emit_expr(*it->second));
                            consumed_named_args.insert(param_name);
                        } else {
                            // Fallback to nil if missing required parameter (type checker should have caught this)
                            Reg nil_reg = allocate_register();
                            emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Void, nil_reg, std::make_shared<Value>(std::make_shared<::Type>(::TypeTag::Nil), "")));
                            arg_regs.push_back(nil_reg);
                        }
                    }

                    // 3c. Optional parameters matched by remaining positional or named arguments
                    size_t opt_pos_idx = pos_idx - init->parameters.size();
                    for (size_t i = 0; i < init->optionalParams.size(); ++i) {
                        const std::string& param_name = init->optionalParams[i].first;

                        auto it = expr.namedArgs.find(param_name);
                        if (it != expr.namedArgs.end()) {
                            arg_regs.push_back(emit_expr(*it->second));
                            consumed_named_args.insert(param_name);
                        } else if (expr.arguments.size() > pos_idx) {
                            arg_regs.push_back(emit_expr(*expr.arguments[pos_idx++]));
                        } else {
                            // Use default value
                            if (init->optionalParams[i].second.second) {
                                arg_regs.push_back(emit_expr(*init->optionalParams[i].second.second));
                            } else {
                                Reg nil_reg = allocate_register();
                                emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Void, nil_reg, std::make_shared<Value>(std::make_shared<::Type>(::TypeTag::Nil), "")));
                                arg_regs.push_back(nil_reg);
                            }
                        }
                    }
                } else {
                    // Fallback for missing declaration info
                    for (const auto& arg : expr.arguments) arg_regs.push_back(emit_expr(*arg));
                }

                Reg init_result = allocate_register();
                LIR_Inst call_inst(LIR_Op::Call, init_result, init_name, arg_regs);
                for (Reg r : arg_regs) call_inst.call_arg_types.push_back(get_register_abi_type(r));
                emit_instruction(call_inst);

                // 4. Apply remaining named arguments as direct field assignments
                for (const auto& [name, arg_expr] : expr.namedArgs) {
                    if (consumed_named_args.count(name)) continue;
                    auto offset_it = frame_info.field_offsets.find(name);
                    if (offset_it != frame_info.field_offsets.end()) {
                        Reg val_reg = emit_expr(*arg_expr);
                        emit_instruction(LIR_Inst(LIR_Op::FrameSetField, Type::Void, frame_reg, static_cast<uint32_t>(offset_it->second), val_reg));
                    }
                }
            }

            // Track instance for deinit at scope exit
            if (frame_info.has_deinit && !scope_stack_.empty()) {
                scope_stack_.back().frame_instances.push_back({func_name, frame_reg});
            }

            return frame_reg;
        }
        
        // Check if this is a module function call (e.g., "math::add")
        size_t dot_pos = func_name.find("::");
        if (dot_pos != std::string::npos) {
            std::string module_name = func_name.substr(0, dot_pos);
            std::string symbol_name = func_name.substr(dot_pos + 2);
            
            // Check for alias mapping
            auto alias_it = import_aliases_.find(module_name);
            if (alias_it != import_aliases_.end()) {
                module_name = alias_it->second;
            }
            
            // Resolve module symbol
            std::string qualified_name = module_name + "::" + symbol_name;
            ModuleSymbolInfo* symbol = resolve_module_symbol(qualified_name);
            if (symbol && symbol->is_function) {
                if (!can_access_module_symbol(*symbol, current_module_)) {
                    report_error("Cannot access private/protected function: " + qualified_name);
                    return 0;
                }
                
               // std::cout << "[DEBUG] LIR Generator: Generating module function call to '" << qualified_name << "'" << std::endl;
                
                // Evaluate arguments and store them in registers
                std::vector<Reg> arg_regs;
                for (const auto& arg : expr.arguments) {
                    Reg arg_reg = emit_expr(*arg);
                    arg_regs.push_back(arg_reg);
                }
                
                // Allocate result register
                Reg result = allocate_register();
                
                // Set the result type if available from type checking
                if (expr.inferred_type) {
                    set_register_language_type(result, expr.inferred_type);
                    set_register_abi_type(result, language_type_to_abi_type(expr.inferred_type));
                } else {
                    auto any_type = std::make_shared<::Type>(::TypeTag::Any);
                    set_register_language_type(result, any_type);
                    set_register_abi_type(result, language_type_to_abi_type(any_type));
                }
                
                // Generate module function call using new format: call r2, module_func(r0, r1)
                emit_instruction(LIR_Inst(LIR_Op::Call, result, qualified_name, arg_regs));
                
                return result;
            }
        }
        
        if (function_table_.find(func_name) != function_table_.end()) {
           // std::cout << "[DEBUG] LIR Generator: Generating call to user function '" << func_name << "'" << std::endl;
            
            // Evaluate arguments and store them in registers
            std::vector<Reg> arg_regs;
            for (const auto& arg : expr.arguments) {
                Reg arg_reg = emit_expr(*arg);
                arg_regs.push_back(arg_reg);
            }
            
            // Allocate result register
            Reg result = allocate_register();
            
            // Set the result type if available from type checking
            if (expr.inferred_type) {
                set_register_language_type(result, expr.inferred_type);
                set_register_abi_type(result, language_type_to_abi_type(expr.inferred_type));
            } else {
                auto any_type = std::make_shared<::Type>(::TypeTag::Any);
                set_register_language_type(result, any_type);
                set_register_abi_type(result, language_type_to_abi_type(any_type));
            }
            
            // Generate user function call using new format: call r2, user_func(r0, r1, r2, ...)
            emit_instruction(LIR_Inst(LIR_Op::Call, result, func_name, arg_regs));
            
            return result;
        } else if (BuiltinUtils::isBuiltinFunction(func_name)) {
           // std::cout << "[DEBUG] LIR Generator: Generating builtin call to '" << func_name << "'" << std::endl;
            
            // Special handling for channel() function
            if (func_name == "channel") {
               // std::cout << "[DEBUG] Processing channel() builtin function" << std::endl;
                if (!expr.arguments.empty()) {
                   // std::cout << "[DEBUG] channel() has arguments, reporting error" << std::endl;
                    report_error("channel() function takes no arguments");
                    return 0;
                }
                
               // std::cout << "[DEBUG] Allocating result register for channel" << std::endl;
                // Allocate result register
                Reg result = allocate_register();
                
               // std::cout << "[DEBUG] Setting channel type for register " << result << std::endl;
                
                // Set the result type to Channel
                auto channel_type = std::make_shared<::Type>(::TypeTag::Channel);
                set_register_language_type(result, channel_type);
                set_register_abi_type(result, Type::I64); // Channel handles are int64
                
                // Generate ChannelAlloc instruction with default capacity
                emit_instruction(LIR_Inst(LIR_Op::ChannelAlloc, result, 32, 0));
                
               // std::cout << "[DEBUG] Generated ChannelAlloc: channel_alloc r" << result << std::endl;
                return result;
            }
            
            // Evaluate arguments and store them in registers
            std::vector<Reg> arg_regs;
            for (const auto& arg : expr.arguments) {
                Reg arg_reg = emit_expr(*arg);
                arg_regs.push_back(arg_reg);
            }
            
            // Allocate result register
            Reg result = allocate_register();
            
            // Set the result type if available from type checking
            if (expr.inferred_type) {
                set_register_language_type(result, expr.inferred_type);
                set_register_abi_type(result, language_type_to_abi_type(expr.inferred_type));
            } else {
                auto any_type = std::make_shared<::Type>(::TypeTag::Any);
                set_register_language_type(result, any_type);
                set_register_abi_type(result, language_type_to_abi_type(any_type));
            }
            
           // std::cout << "[DEBUG] Builtin function '" << func_name << "' called with " << arg_regs.size() << " arguments" << std::endl;
            
            // Generate builtin call using new format: call r2, builtin_func(r0, r1, r2, ...)
            emit_instruction(LIR_Inst(LIR_Op::Call, result, func_name, arg_regs));
            
           // std::cout << "[DEBUG] Generated call: call r" << result << ", " << func_name << "(...)" << std::endl;
            
            return result;
            
        } else {
            // Check if it's actually a variable holding a function (indirect call)
            Reg var_reg = resolve_variable(func_name);
            if (var_reg != UINT32_MAX) {
                // Redirect to closure call
                LM::Frontend::AST::CallClosureExpr closure_call;
                closure_call.closure = expr.callee;
                closure_call.arguments = expr.arguments;
                closure_call.namedArgs = expr.namedArgs;
                closure_call.inferred_type = expr.inferred_type;
                return emit_call_closure_expr(closure_call);
            }

            report_error("Unknown function: " + func_name);
            return 0;
        }
    } else if (auto member_expr = dynamic_cast<LM::Frontend::AST::MemberExpr*>(expr.callee.get())) {
        // Method call: obj.method(args...) or module function call: module.function(args...)
        std::string method_name = member_expr->name;

        // Enum variant constructor call: EnumName.Variant(payload?)
        if (auto enum_obj = dynamic_cast<LM::Frontend::AST::VariableExpr*>(member_expr->object.get())) {
            int64_t tag = 0;
            size_t expected_arity = 0;
            std::string qualified_variant = enum_obj->name + "." + method_name;
            TypePtr enum_hint = member_expr->object->inferred_type;
            if ((!enum_hint || enum_hint->tag != TypeTag::Enum) && type_system_) {
                enum_hint = type_system_->getType(enum_obj->name);
            }

            if (resolve_enum_variant_info(type_system_.get(), enum_hint, qualified_variant, tag, expected_arity)) {
                Reg result = allocate_register();
                Reg payload = 0;
                if (!expr.arguments.empty()) {
                    payload = emit_expr(*expr.arguments[0]);
                }

                emit_instruction(LIR_Inst(LIR_Op::MakeEnum, Type::Ptr, result, payload, 0, static_cast<uint32_t>(tag)));

                if (expr.inferred_type) {
                    set_register_language_type(result, expr.inferred_type);
                    set_register_abi_type(result, Type::Ptr);
                }
                return result;
            }
        }
        
        // Check if this is a module member access
        if (auto var_expr = dynamic_cast<LM::Frontend::AST::VariableExpr*>(member_expr->object.get())) {
            // Check if the variable is a module alias
            auto alias_it = import_aliases_.find(var_expr->name);
            if (alias_it != import_aliases_.end()) {
                // This is a module function call
                std::string module_path = alias_it->second;
                std::string qualified_name = module_path + "." + method_name;

                // Evaluate arguments
                std::vector<Reg> arg_regs;
                for (const auto& arg : expr.arguments) {
                    Reg arg_reg = emit_expr(*arg);
                    arg_regs.push_back(arg_reg);
                }
                
                // Generate function call
                Reg result = allocate_register();
                
                // Set the result type if available from type checking
                if (expr.inferred_type) {
                    set_register_language_type(result, expr.inferred_type);
                    set_register_abi_type(result, language_type_to_abi_type(expr.inferred_type));
                } else {
                    auto any_type = std::make_shared<::Type>(::TypeTag::Any);
                    set_register_language_type(result, any_type);
                    set_register_abi_type(result, language_type_to_abi_type(any_type));
                }
                
                // Generate function call using the qualified name
                LIR_Inst call_inst(LIR_Op::Call, result, qualified_name, arg_regs);
                
                // Set argument types for the call
                for (Reg arg_reg : arg_regs) {
                    call_inst.call_arg_types.push_back(get_register_abi_type(arg_reg));
                }
                
                emit_instruction(call_inst);
                
                return result;
            }
        }
        
        // Evaluate the object (this will be the first argument)
        Reg object_reg = emit_expr(*member_expr->object);
        
        // Evaluate other arguments
        std::vector<Reg> arg_regs;
        arg_regs.push_back(object_reg); // 'this' is first parameter
        for (const auto& arg : expr.arguments) {
            Reg arg_reg = emit_expr(*arg);
            arg_regs.push_back(arg_reg);
        }
        
        // Get the type of the object to find the correct method
        TypePtr object_type = member_expr->object->inferred_type;
        if (object_type && object_type->tag == TypeTag::Frame) {
            auto frame_type_info = std::get_if<FrameType>(&object_type->extra);
            if (frame_type_info) {
                std::string frame_name = frame_type_info->name;
                auto it = frame_table_.find(frame_name);
                if (it != frame_table_.end()) {
                    const FrameInfo& frame_info = it->second;
                    auto method_it = frame_info.method_indices.find(method_name);
                    if (method_it != frame_info.method_indices.end()) {
                        // Check visibility
                        std::string full_method_name = frame_name + "." + method_name;
                        auto func_it = function_table_.find(full_method_name);
                        if (func_it != function_table_.end()) {
                            if (!is_visible(func_it->second.visibility, frame_name)) {
                                report_error("Cannot access " + LM::Frontend::AST::visibilityToString(func_it->second.visibility) +
                                           " method '" + method_name + "' of frame '" + frame_name + "'");
                                return 0;
                            }
                        }

                        // Found the method - generate frame method call
                        Reg result = allocate_register();

                        // Set the result type if available from type checking
                        if (expr.inferred_type) {
                            set_register_language_type(result, expr.inferred_type);
                            set_register_abi_type(result, language_type_to_abi_type(expr.inferred_type));
                        } else {
                            auto any_type = std::make_shared<::Type>(::TypeTag::Any);
                            set_register_language_type(result, any_type);
                            set_register_abi_type(result, language_type_to_abi_type(any_type));
                        }

                        // Generate frame method call using Call
                        LIR_Inst call_inst(LIR_Op::Call, result, full_method_name, arg_regs);

                        // Set argument types for the call
                        for (Reg arg_reg : arg_regs) {
                            call_inst.call_arg_types.push_back(get_register_abi_type(arg_reg));
                        }

                        emit_instruction(call_inst);

                        return result;
                    }

                    // Check if it's a trait method call recursively
                    std::vector<std::string> trait_worklist = frame_info.implements;
                    std::unordered_set<std::string> visited_traits;

                    while (!trait_worklist.empty()) {
                        std::string current_trait = trait_worklist.back();
                        trait_worklist.pop_back();

                        if (visited_traits.count(current_trait)) continue;
                        visited_traits.insert(current_trait);

                        std::string full_trait_method_name = current_trait + "." + method_name;
                        if (LIRFunctionManager::getInstance().hasFunction(full_trait_method_name)) {
                            // Generate call to trait method (static dispatch)
                            Reg result = allocate_register();
                            if (expr.inferred_type) {
                                set_register_language_type(result, expr.inferred_type);
                                set_register_abi_type(result, language_type_to_abi_type(expr.inferred_type));
                            }
                            
                            LIR_Inst call_inst(LIR_Op::Call, result, full_trait_method_name, arg_regs);
                            for (Reg r : arg_regs) call_inst.call_arg_types.push_back(get_register_abi_type(r));
                            emit_instruction(call_inst);
                            return result;
                        }

                        // Add parent traits to worklist
                        // We need to look up trait info to find parent traits
                        auto trait_it = trait_table_.find(current_trait);
                        if (trait_it != trait_table_.end()) {
                            for (const auto& parent : trait_it->second.extends) {
                                trait_worklist.push_back(parent);
                            }
                        }
                    }
                }
            }
        } else {
            // Fallback for when type inference is missing - still try to find the method in ANY frame
            // This is less safe but better than failing if inference is incomplete
            for (const auto& [frame_name, frame_info] : frame_table_) {
                auto method_it = frame_info.method_indices.find(method_name);
                if (method_it != frame_info.method_indices.end()) {
                    // Found the method - generate frame method call
                    Reg result = allocate_register();

                    // Set the result type if available from type checking
                    if (expr.inferred_type) {
                        set_register_language_type(result, expr.inferred_type);
                        set_register_abi_type(result, language_type_to_abi_type(expr.inferred_type));
                    } else {
                        auto any_type = std::make_shared<::Type>(::TypeTag::Any);
                        set_register_language_type(result, any_type);
                        set_register_abi_type(result, language_type_to_abi_type(any_type));
                    }

                    // Generate frame method call using Call
                    std::string full_method_name = frame_name + "." + method_name;
                    LIR_Inst call_inst(LIR_Op::Call, result, full_method_name, arg_regs);

                    // Set argument types for the call
                    for (Reg arg_reg : arg_regs) {
                        call_inst.call_arg_types.push_back(get_register_abi_type(arg_reg));
                    }

                    emit_instruction(call_inst);

                    return result;
                }
            }
        }
        
        // Check for special channel methods
        if (method_name == "send") {
            if (expr.arguments.size() != 1) {
                report_error("channel.send() requires exactly one argument");
                return 0;
            }
            
            // Evaluate value to send
            Reg value_reg = emit_expr(*expr.arguments[0]);
            
            // Generate ChannelSend instruction (blocking)
            Reg result = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::ChannelSend, result, object_reg, value_reg));
            set_register_type(result, std::make_shared<::Type>(::TypeTag::Nil)); // Void return
            return result;
        }

        if (method_name == "recv") {
            if (expr.arguments.size() != 0) {
                report_error("channel.recv() requires no arguments");
                return 0;
            }
            
            // Generate ChannelRecv instruction (blocking)
            Reg result = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::ChannelRecv, result, object_reg));
            set_register_type(result, std::make_shared<::Type>(::TypeTag::Any)); // Returns T
            return result;
        }        

        if (method_name == "offer") {
            if (expr.arguments.size() != 1) {
                report_error("channel.offer() requires exactly one argument");
                return 0;
            }
            
            // Evaluate value to offer
            Reg value_reg = emit_expr(*expr.arguments[0]);
            
            // Generate ChannelOffer instruction (non-blocking)
            Reg result = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::ChannelOffer, result, object_reg, value_reg));
            set_register_type(result, std::make_shared<::Type>(::TypeTag::Bool)); // Returns success/failure
            return result;
        } 

        if (method_name == "poll") {
            if (expr.arguments.size() != 0) {
                report_error("channel.poll() requires no arguments");
                return 0;
            }
            
            // Generate ChannelPoll instruction (non-blocking)
            Reg result = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::ChannelPoll, result, object_reg));
            set_register_type(result, std::make_shared<::Type>(::TypeTag::Any)); // Returns Option<T>
            return result;
        } 

        if (method_name == "close") {
            if (expr.arguments.size() != 0) {
                report_error("channel.close() requires no arguments");
                return 0;
            }
            
            // Generate ChannelClose instruction
            Reg result = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::ChannelClose, result, object_reg));
            set_register_type(result, std::make_shared<::Type>(::TypeTag::Nil)); // Void return
            return result;
        }         

        // Check for built-in list methods
        if (method_name == "append") {
            if (expr.arguments.size() != 1) {
                report_error("list.append() requires exactly one argument");
                return 0;
            }
            
            // Evaluate the argument to append
            Reg arg_reg = emit_expr(*expr.arguments[0]);
            
            // Generate ListAppend instruction
            Reg result = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::ListAppend, Type::Void, result, object_reg, arg_reg));
            set_register_type(result, std::make_shared<::Type>(::TypeTag::Nil)); // Void return
            return result;
        }
        
        if (method_name == "len") {
            if (expr.arguments.size() != 0) {
                report_error("list.len() requires no arguments");
                return 0;
            }
            
            Reg result = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::ListLen, Type::I64, result, object_reg));
            set_register_type(result, std::make_shared<::Type>(::TypeTag::Int));
            return result;
        }
        
        report_error("Unknown method: " + method_name);
        return 0;
    } else {
        report_error("Complex function calls not yet supported in LIR");
        return 0;
    }
}


Reg Generator::emit_assign_expr(LM::Frontend::AST::AssignExpr& expr) {
    Reg value = emit_expr(*expr.value);

    // Ownership transfer: If we assign a frame instance to a field, 
    // it's no longer managed by the current scope.
    if (expr.object && expr.member) {
        // Find if 'value' corresponds to a frame instance in current scope
        Reg source_reg = value;
        
        // Follow Mov chains to find original allocation
        for (auto it = current_function_->instructions.rbegin(); it != current_function_->instructions.rend(); ++it) {
            if (it->op == LIR_Op::Mov && it->dst == source_reg) {
                source_reg = it->a;
            }
        }

        if (!scope_stack_.empty()) {
            auto& scope = scope_stack_.back();
            for (auto it = scope.frame_instances.begin(); it != scope.frame_instances.end(); ++it) {
                if (it->second == source_reg) {
                    // Transfer ownership to the object field
                    scope.frame_instances.erase(it);
                    break;
                }
            }
        }
    }
    
    // === SHARED CELL TASK BODY ASSIGNMENT HANDLING ===
    // Check if we're in a task body and this variable is a shared variable
    if (!expr.name.empty() && !parallel_block_cell_ids_.empty() && parallel_block_cell_ids_.find(expr.name) != parallel_block_cell_ids_.end()) {
        // This is a shared variable assignment in a task body - use SharedCell operations
       // std::cout << "[DEBUG] Task body assigning to shared variable '" << expr.name << "' via SharedCell" << std::endl;
        
        // Get the SharedCell ID register for this variable
        Reg cell_id_reg = parallel_block_cell_ids_[expr.name];
        
        // Handle compound assignment operators
        if (expr.op != LM::Frontend::TokenType::EQUAL) {
            // For compound assignment (+=, -=, *=, /=, %=), we need to:
            // 1. Load current value from SharedCell
            // 2. Perform operation with new value
            // 3. Store result back to SharedCell
            
            Reg current_value_reg = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::SharedCellLoad, current_value_reg, cell_id_reg, 0));
            
            // Perform the operation
            Reg result_reg = allocate_register();
            switch (expr.op) {
                case LM::Frontend::TokenType::PLUS_EQUAL:
                    emit_instruction(LIR_Inst(LIR_Op::Add, Type::I64, result_reg, current_value_reg, value));
                    break;
                case LM::Frontend::TokenType::MINUS_EQUAL:
                    emit_instruction(LIR_Inst(LIR_Op::Sub, Type::I64, result_reg, current_value_reg, value));
                    break;
                case LM::Frontend::TokenType::STAR_EQUAL:
                    emit_instruction(LIR_Inst(LIR_Op::Mul, Type::I64, result_reg, current_value_reg, value));
                    break;
                case LM::Frontend::TokenType::SLASH_EQUAL:
                    emit_instruction(LIR_Inst(LIR_Op::Div, Type::I64, result_reg, current_value_reg, value));
                    break;
                case LM::Frontend::TokenType::MODULUS_EQUAL:
                    emit_instruction(LIR_Inst(LIR_Op::Mod, Type::I64, result_reg, current_value_reg, value));
                    break;
                default:
                    report_error("Unsupported compound assignment operator for SharedCell");
                    return 0;
            }
            
            // Store result back to SharedCell
            emit_instruction(LIR_Inst(LIR_Op::SharedCellStore, result_reg, cell_id_reg, result_reg, 0));
            
            return result_reg;
        } else {
            // Simple assignment - store value directly to SharedCell
            emit_instruction(LIR_Inst(LIR_Op::SharedCellStore, value, cell_id_reg, value, 0));
            return value;
        }
    }
    
    // For simple variable assignment
    if (!expr.name.empty()) {
        // Get the existing register for this variable
        Reg dst = resolve_variable(expr.name);
        if (dst == UINT32_MAX) {
            // Variable doesn't exist, allocate a new one
            dst = allocate_register();
            bind_variable(expr.name, dst);
        }
        
        // Handle compound assignment operators
        if (expr.op != LM::Frontend::TokenType::EQUAL) {
            // For compound assignment (+=, -=, *=, /=, %=), we need to:
            // 1. Load current value
            // 2. Perform operation with new value
            // 3. Store result back
            
            // Convert the TypePtr to ABI Type for the instruction
            Type abi_type = language_type_to_abi_type(expr.inferred_type);
            
            // Check if this should be string concatenation instead of arithmetic
            if (expr.op == LM::Frontend::TokenType::PLUS_EQUAL) {
                // Get the type of the left operand (current variable value)
                TypePtr dst_type = get_register_type(dst);
                if (dst_type && dst_type->tag == TypeTag::String) {
                    // String += something -> use string concatenation
                    auto string_type = std::make_shared<::Type>(::TypeTag::String);
                    emit_instruction(LIR_Inst(LIR_Op::STR_CONCAT, Type::Ptr, dst, dst, value));
                    set_register_type(dst, string_type);
                    return dst;
                }
            }
            
            switch (expr.op) {
                case LM::Frontend::TokenType::PLUS_EQUAL:
                    emit_instruction(LIR_Inst(LIR_Op::Add, abi_type, dst, dst, value));
                    break;
                case LM::Frontend::TokenType::MINUS_EQUAL:
                    emit_instruction(LIR_Inst(LIR_Op::Sub, abi_type, dst, dst, value));
                    break;
                case LM::Frontend::TokenType::STAR_EQUAL:
                    emit_instruction(LIR_Inst(LIR_Op::Mul, abi_type, dst, dst, value));
                    break;
                case LM::Frontend::TokenType::SLASH_EQUAL:
                    emit_instruction(LIR_Inst(LIR_Op::Div, abi_type, dst, dst, value));
                    break;
                case LM::Frontend::TokenType::MODULUS_EQUAL:
                    emit_instruction(LIR_Inst(LIR_Op::Mod, abi_type, dst, dst, value));
                    break;
                default:
                    report_error("Unsupported compound assignment operator");
                    return 0;
            }
        } else {
            // Simple assignment - just move the value
            // Set type BEFORE emitting so it's available during emit_instruction
            set_register_type(dst, get_register_type(value));
            
            // Convert the TypePtr to ABI Type for the instruction
            Type abi_type = language_type_to_abi_type(expr.inferred_type);
            
            emit_instruction(LIR_Inst(LIR_Op::Mov, abi_type, dst, value, 0));
        }
        // No need to update binding since we're using the existing register
        return dst;
    } else if (expr.object) {
        // For member or index assignment
        if (expr.member.has_value()) {
            // Field assignment: obj.field = value
            Reg object_reg = emit_expr(*expr.object);
            std::string field_name = expr.member.value();
            
            // Get the type of the object to find the correct frame
            TypePtr object_type = expr.object->inferred_type;
            if (object_type && object_type->tag == TypeTag::Frame) {
                auto frame_type_info = std::get_if<FrameType>(&object_type->extra);
                if (frame_type_info) {
                    auto it = frame_table_.find(frame_type_info->name);
                    if (it != frame_table_.end()) {
                        // Check visibility
                        auto vis_it = it->second.field_visibilities.find(field_name);
                        if (vis_it != it->second.field_visibilities.end()) {
                            if (!is_visible(vis_it->second, frame_type_info->name)) {
                                report_error("Cannot access " + LM::Frontend::AST::visibilityToString(vis_it->second) +
                                           " field '" + field_name + "' of frame '" + frame_type_info->name + "'");
                                return 0;
                            }
                        }

                        auto offset_it = it->second.field_offsets.find(field_name);
                        if (offset_it != it->second.field_offsets.end()) {
                            // Found the field - emit FrameSetField
                            LIR_Op set_op = LIR_Op::FrameSetField;
                            if (is_in_concurrency_context()) {
                                if (expr.op == LM::Frontend::TokenType::EQUAL) {
                                    set_op = LIR_Op::FrameSetFieldAtomic;
                                } else if (expr.op == LM::Frontend::TokenType::PLUS_EQUAL) {
                                    set_op = LIR_Op::FrameFieldAtomicAdd;
                                } else if (expr.op == LM::Frontend::TokenType::MINUS_EQUAL) {
                                    set_op = LIR_Op::FrameFieldAtomicSub;
                                }
                            }

                            emit_instruction(LIR_Inst(set_op, Type::Void, object_reg, static_cast<uint32_t>(offset_it->second), value));
                            return value;
                        }
                    }
                }
            } else {
                // Fallback: search all frames
                for (const auto& [frame_name, frame_info] : frame_table_) {
                    auto offset_it = frame_info.field_offsets.find(field_name);
                    if (offset_it != frame_info.field_offsets.end()) {
                        // Found the field - emit FrameSetField
                        emit_instruction(LIR_Inst(LIR_Op::FrameSetField, Type::Void, object_reg, static_cast<uint32_t>(offset_it->second), value));
                        return value;
                    }
                }
            }
            
            report_error("Unknown field for assignment: " + field_name);
            return 0;
        } else {
            // Index assignment - handle dict/list/tuple element assignment
            Reg object_reg = emit_expr(*expr.object);
            Reg index_reg = emit_expr(*expr.index);
            
            // Use DictSet operation for dictionary assignment
            Reg result = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::DictSet, Type::Ptr, object_reg, index_reg, value));
            set_register_type(result, std::make_shared<::Type>(::TypeTag::Nil)); // Void return
            return value;
        }
    } else {
        report_error("Invalid assignment target");
        return 0;
    }
}


Reg Generator::emit_call_closure_expr(LM::Frontend::AST::CallClosureExpr& expr) {
    // Handle closure calls - calling a function stored in a variable
    // This enables first-order functions and closures
    
    // Evaluate the closure expression
    Reg closure_reg = emit_expr(*expr.closure);
    
    // Evaluate all positional arguments
    std::vector<Reg> arg_regs;
    for (const auto& arg : expr.arguments) {
        Reg arg_reg = emit_expr(*arg);
        arg_regs.push_back(arg_reg);
    }
    
    // Handle named arguments
    std::unordered_map<std::string, Reg> named_arg_regs;
    for (const auto& [name, arg] : expr.namedArgs) {
        Reg arg_reg = emit_expr(*arg);
        named_arg_regs[name] = arg_reg;
    }
    
    // Create a result register
    Reg result = allocate_register();
    
    // Emit closure call instruction
    Type abi_type = Type::Void;
    if (expr.inferred_type) {
        abi_type = language_type_to_abi_type(expr.inferred_type);
    }

    if (arg_regs.empty()) {
        emit_instruction(LIR_Inst(LIR_Op::CallIndirect, abi_type, result, closure_reg, 0));
    } else {
        // Pass arguments to CallIndirect using multi-register convention or internal argument stack
        for (const auto& arg : arg_regs) {
            LIR_Inst param_inst(LIR_Op::Param);
            param_inst.a = arg;
            emit_instruction(param_inst);
        }
        emit_instruction(LIR_Inst(LIR_Op::CallIndirect, abi_type, result, closure_reg, 0));
    }
    
    // Set return type based on inference
    if (expr.inferred_type) {
        set_register_type(result, expr.inferred_type);
    } else {
        set_register_type(result, std::make_shared<::Type>(::TypeTag::Int));
    }
    
    return result;
}


Reg Generator::emit_list_expr(LM::Frontend::AST::ListExpr& expr) {
    // Create a new list using ListCreate operation
    Reg list_reg = allocate_register();
    Type abi_type = language_type_to_abi_type(expr.inferred_type);
    
    // Emit ListCreate instruction
    emit_instruction(LIR_Inst(LIR_Op::ListCreate, abi_type, list_reg, 0, 0));
    set_register_type(list_reg, expr.inferred_type);
    
    // Append elements to the list
    for (const auto& element : expr.elements) {
        Reg element_reg = emit_expr(*element);
        Reg temp = allocate_register();
        emit_instruction(LIR_Inst(LIR_Op::ListAppend, Type::Void, temp, list_reg, element_reg));
    }
    
    return list_reg;
}


Reg Generator::emit_grouping_expr(LM::Frontend::AST::GroupingExpr& expr) {
    return emit_expr(*expr.expression);
}


Reg Generator::emit_ternary_expr(LM::Frontend::AST::TernaryExpr& expr) {
    report_error("Ternary expressions not yet implemented");
    return 0;
}


Reg Generator::emit_index_expr(LM::Frontend::AST::IndexExpr& expr) {
    // Evaluate the object (list/dict/tuple)
    Reg object_reg = emit_expr(*expr.object);
    
    // Evaluate the index
    Reg index_reg = emit_expr(*expr.index);
    
    // Determine result type
    TypePtr result_type = nullptr;
    if (expr.inferred_type) {
        result_type = expr.inferred_type;
    } else {
        // Default to any type if not inferred
        result_type = std::make_shared<::Type>(::TypeTag::Any);
    }
    
    // Check the object type to use the appropriate operation
    TypePtr object_type = get_register_language_type(object_reg);
    if (object_type && object_type->tag == ::TypeTag::Tuple) {
        // Use TupleGet for tuples
        Reg result_reg = allocate_register();
        Type abi_type = language_type_to_abi_type(result_type);
        emit_instruction(LIR_Inst(LIR_Op::TupleGet, abi_type, result_reg, object_reg, index_reg));
        set_register_type(result_reg, result_type);
        return result_reg;
    } else if (object_type && object_type->tag == ::TypeTag::Dict) {
        // Use DictGet for dictionaries
        Reg result_reg = allocate_register();
        Type abi_type = language_type_to_abi_type(result_type);
        emit_instruction(LIR_Inst(LIR_Op::DictGet, abi_type, result_reg, object_reg, index_reg));
        set_register_type(result_reg, result_type);
        set_register_language_type(result_reg, result_type);  // Ensure language type is set
        return result_reg;
    } else {
        // Use ListIndex for lists and other types
        Reg result_reg = allocate_register();
        Type abi_type = language_type_to_abi_type(result_type);
        emit_instruction(LIR_Inst(LIR_Op::ListIndex, abi_type, result_reg, object_reg, index_reg));
        set_register_type(result_reg, result_type);
        set_register_language_type(result_reg, result_type);  // Ensure language type is set
        return result_reg;
    }
}


Reg Generator::emit_member_expr(LM::Frontend::AST::MemberExpr& expr) {
    // Enum unit variant access: EnumName.Variant
    if (auto enum_obj = dynamic_cast<LM::Frontend::AST::VariableExpr*>(expr.object.get())) {
        int64_t tag = 0;
        size_t expected_arity = 0;
        std::string qualified_variant = enum_obj->name + "." + expr.name;
        TypePtr enum_hint = expr.object->inferred_type;
        if ((!enum_hint || enum_hint->tag != TypeTag::Enum) && type_system_) {
            enum_hint = type_system_->getType(enum_obj->name);
        }

        if (resolve_enum_variant_info(type_system_.get(), enum_hint, qualified_variant, tag, expected_arity) && expected_arity == 0) {
            Reg result = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::MakeEnum, Type::Ptr, result, 0, 0, static_cast<uint32_t>(tag)));
            if (expr.inferred_type) {
                set_register_language_type(result, expr.inferred_type);
                set_register_abi_type(result, Type::Ptr);
            }
            return result;
        }
    }

    // Check if it's a module alias access (e.g. math.version)
    if (auto var_expr = dynamic_cast<LM::Frontend::AST::VariableExpr*>(expr.object.get())) {
        auto alias_it = import_aliases_.find(var_expr->name);
        if (alias_it != import_aliases_.end()) {
            std::string module_path = alias_it->second;
            std::string qualified_name = module_path + "." + expr.name;

            Reg result = allocate_register();
            LIR_Inst load_inst(LIR_Op::LoadGlobal, Type::Ptr, result, 0, 0);
            load_inst.func_name = qualified_name;
            emit_instruction(load_inst);

            if (expr.inferred_type) {
                set_register_language_type(result, expr.inferred_type);
                set_register_abi_type(result, language_type_to_abi_type(expr.inferred_type));
            } else {
                auto any_type = std::make_shared<::Type>(::TypeTag::Any);
                set_register_language_type(result, any_type);
                set_register_abi_type(result, language_type_to_abi_type(any_type));
            }
            return result;
        }
    }

    // First evaluate the object expression
    Reg object_reg = emit_expr(*expr.object);
    
    // Check for built-in list methods
    if (expr.name == "append") {
        // Return a special marker for append method
        Reg method_marker = allocate_register();
        auto int_type = std::make_shared<::Type>(::TypeTag::Int);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, method_marker, 
                                std::make_shared<Value>(int_type, int64_t(1)))); // Append marker
        set_register_type(method_marker, int_type);
        return method_marker;
    }
    
    if (expr.name == "len") {
        // Return a special marker for len method
        Reg method_marker = allocate_register();
        auto int_type = std::make_shared<::Type>(::TypeTag::Int);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, method_marker, 
                                std::make_shared<Value>(int_type, int64_t(2)))); // Len marker
        set_register_type(method_marker, int_type);
        return method_marker;
    }
    
    // Check for tuple field access (key, value)
    TypePtr object_lang_type = get_register_language_type(object_reg);
    bool is_tuple = object_lang_type && object_lang_type->tag == ::TypeTag::Tuple;

    if (is_tuple && expr.name == "key") {
        // Access first element of tuple (index 0)
        Reg index_reg = allocate_register();
        auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
        ValuePtr zero_val = std::make_shared<Value>(int_type, int64_t(0));
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, index_reg, zero_val));
        set_register_type(index_reg, int_type);
        
        Reg result_reg = allocate_register();
        emit_instruction(LIR_Inst(LIR_Op::TupleGet, Type::Ptr, result_reg, object_reg, index_reg));
        set_register_type(result_reg, std::make_shared<::Type>(::TypeTag::String));
        return result_reg;
    }
    
    if (is_tuple && expr.name == "value") {
        // Access second element of tuple (index 1)
        Reg index_reg = allocate_register();
        auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
        ValuePtr one_val = std::make_shared<Value>(int_type, int64_t(1));
       // std::cout << "[DEBUG] Emitting Dict value: "<< std::endl;
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, index_reg, one_val));
        set_register_type(index_reg, int_type);
        
        Reg result_reg = allocate_register();
        emit_instruction(LIR_Inst(LIR_Op::TupleGet, Type::I64, result_reg, object_reg, index_reg));
        set_register_type(result_reg, int_type);
        return result_reg;
    }
    
    // Get the type of the object to find the correct frame
    TypePtr object_type = expr.object->inferred_type;
    if (object_type && object_type->tag == TypeTag::Frame) {
        auto frame_type_info = std::get_if<FrameType>(&object_type->extra);
        if (frame_type_info) {
            auto it = frame_table_.find(frame_type_info->name);
            if (it != frame_table_.end()) {
                // Check visibility
                auto vis_it = it->second.field_visibilities.find(expr.name);
                if (vis_it != it->second.field_visibilities.end()) {
                    if (!is_visible(vis_it->second, frame_type_info->name)) {
                        report_error("Cannot access " + LM::Frontend::AST::visibilityToString(vis_it->second) +
                                   " field '" + expr.name + "' of frame '" + frame_type_info->name + "'");
                        return 0;
                    }
                }

                auto offset_it = it->second.field_offsets.find(expr.name);
                if (offset_it != it->second.field_offsets.end()) {
                    // Found the field - emit FrameGetField
                    Reg dst = allocate_register();

                    TypePtr field_lang_type = it->second.fields[offset_it->second].second;
                    Type field_abi_type = language_type_to_abi_type(field_lang_type);

                    // Check if we are in a parallel block and need atomic access
                    LIR_Op get_op = LIR_Op::FrameGetField;
                    if (is_in_concurrency_context()) {
                        get_op = LIR_Op::FrameGetFieldAtomic;
                    }

                    emit_instruction(LIR_Inst(get_op, field_abi_type, dst, object_reg, static_cast<uint32_t>(offset_it->second)));

                    // Set field type
                    if (offset_it->second < it->second.fields.size()) {
                        set_register_language_type(dst, field_lang_type);
                    }

                    return dst;
                }
            }
        }
    } else {
        // Fallback: search all frames
        for (const auto& [frame_name, frame_info] : frame_table_) {
            auto offset_it = frame_info.field_offsets.find(expr.name);
            if (offset_it != frame_info.field_offsets.end()) {
                // Found the field - emit FrameGetField
                Reg dst = allocate_register();
                emit_instruction(LIR_Inst(LIR_Op::FrameGetField, Type::Ptr, dst, object_reg, static_cast<uint32_t>(offset_it->second)));

                // Set field type
                if (offset_it->second < frame_info.fields.size()) {
                    set_register_language_type(dst, frame_info.fields[offset_it->second].second);
                }

                return dst;
            }
        }
    }
    
    // If we get here, it's either a method call or unknown field
    // Check for special channel methods
    if (expr.name == "send") {
        // For channel.send(value), we need to return a special marker that this is a method call
        // The actual call will be handled in emit_call_expr
        Reg method_marker = allocate_register();
        auto int_type = std::make_shared<::Type>(::TypeTag::Int);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, method_marker, 
                                std::make_shared<Value>(int_type, int64_t(-1)))); // Special marker
        set_register_type(method_marker, int_type);
        return method_marker;
    }
    
    // For now, we'll treat it as an error
    report_error("Unknown field or method: " + expr.name);
    return 0;
}


Reg Generator::emit_tuple_expr(LM::Frontend::AST::TupleExpr& expr) {
    // Create a new tuple using TupleCreate operation
    Reg tuple_reg = allocate_register();
    Type abi_type = language_type_to_abi_type(expr.inferred_type);
    
    // Emit TupleCreate instruction with the correct size
    emit_instruction(LIR_Inst(LIR_Op::TupleCreate, abi_type, tuple_reg, 0, 0, static_cast<uint32_t>(expr.elements.size())));
    set_register_type(tuple_reg, expr.inferred_type);
    
    // Use TupleSet to add elements to the tuple
    for (size_t i = 0; i < expr.elements.size(); i++) {
        Reg element_reg = emit_expr(*expr.elements[i]);
        Reg index_reg = allocate_register();
        auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
        ValuePtr index_val = std::make_shared<Value>(int_type, int64_t(i));
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, index_reg, index_val));
        set_register_type(index_reg, int_type);
        emit_instruction(LIR_Inst(LIR_Op::TupleSet, Type::Void, tuple_reg, index_reg, element_reg));
    }
    
    return tuple_reg;
}


Reg Generator::emit_dict_expr(LM::Frontend::AST::DictExpr& expr) {
    // Create a new dictionary using DictCreate operation
    Reg dict_reg = allocate_register();
    Type abi_type = language_type_to_abi_type(expr.inferred_type);
    
    // Emit DictCreate instruction with default int hash/compare functions
    emit_instruction(LIR_Inst(LIR_Op::DictCreate, abi_type, dict_reg, 0, 0));
    set_register_type(dict_reg, expr.inferred_type);
    
    // Add key-value pairs to the dictionary
    for (const auto& [key_expr, value_expr] : expr.entries) {
        Reg key_reg = emit_expr(*key_expr);
        Reg value_reg = emit_expr(*value_expr);
        
        // Use DictSet operation to add each pair
        emit_instruction(LIR_Inst(LIR_Op::DictSet, abi_type, dict_reg, key_reg, value_reg));
    }
    
    return dict_reg;
}


Reg Generator::emit_range_expr(LM::Frontend::AST::RangeExpr& expr) {
    report_error("Range expressions not yet implemented");
    return 0;
}


Reg Generator::emit_lambda_expr(LM::Frontend::AST::LambdaExpr& expr) {
    std::string lambda_name = "__lambda_" + std::to_string(lambda_counter_++);
    
    auto fn_decl = std::make_shared<LM::Frontend::AST::FunctionDeclaration>();
    fn_decl->name = lambda_name;
    fn_decl->params = expr.params;
    fn_decl->returnType = expr.returnType;
    fn_decl->body = expr.body;
    fn_decl->inferred_type = expr.inferred_type;
    
    // Set captures for the new function's generation
    auto prev_captures = current_lambda_captures_;
    current_lambda_captures_ = expr.capturedVars;
    
    generate_function(*fn_decl);
    
    current_lambda_captures_ = prev_captures;

    // Create the lambda/closure object
    Reg func_reg = allocate_register();
    auto string_type = std::make_shared<::Type>(::TypeTag::String);
    ValuePtr name_val = std::make_shared<Value>(string_type, lambda_name);
    Reg name_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Ptr, name_reg, name_val));

    if (expr.capturedVars.empty()) {
        // Simple function pointer
        emit_instruction(LIR_Inst(LIR_Op::Mov, Type::Ptr, func_reg, name_reg, 0));
    } else {
        // Bundle into a Tuple: (lambda_name, capture1, capture2, ...)
        Reg closure_tuple = allocate_register();
        uint32_t tuple_size = static_cast<uint32_t>(expr.capturedVars.size() + 1);
        emit_instruction(LIR_Inst(LIR_Op::TupleCreate, Type::Ptr, closure_tuple, 0, 0, tuple_size));
        
        // Set lambda name at index 0
        Reg zero_idx = allocate_register();
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, zero_idx, std::make_shared<Value>(std::make_shared<::Type>(::TypeTag::Int64), (int64_t)0)));
        emit_instruction(LIR_Inst(LIR_Op::TupleSet, Type::Void, closure_tuple, zero_idx, name_reg));

        // Set captured variables
        for (size_t i = 0; i < expr.capturedVars.size(); ++i) {
            Reg val_reg = resolve_variable(expr.capturedVars[i]);
            if (val_reg == UINT32_MAX) {
                // If not found in local scope, it might be in current lambda's env
                if (env_register_ != UINT32_MAX) {
                    auto it = std::find(current_lambda_captures_.begin(), current_lambda_captures_.end(), expr.capturedVars[i]);
                    if (it != current_lambda_captures_.end()) {
                        size_t inner_idx = std::distance(current_lambda_captures_.begin(), it);
                        Reg inner_idx_reg = allocate_register();
                        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, inner_idx_reg, std::make_shared<Value>(std::make_shared<::Type>(::TypeTag::Int64), (int64_t)(inner_idx + 1))));
                        
                        val_reg = allocate_register();
                        emit_instruction(LIR_Inst(LIR_Op::TupleGet, Type::I64, val_reg, env_register_, inner_idx_reg));
                    }
                }
            }
            
            if (val_reg == UINT32_MAX) continue;

            Reg idx_reg = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, idx_reg, std::make_shared<Value>(std::make_shared<::Type>(::TypeTag::Int64), (int64_t)(i + 1))));
            emit_instruction(LIR_Inst(LIR_Op::TupleSet, Type::Void, closure_tuple, idx_reg, val_reg));
        }
        
        emit_instruction(LIR_Inst(LIR_Op::Mov, Type::Ptr, func_reg, closure_tuple, 0));
    }

    auto func_type = std::make_shared<::Type>(::TypeTag::Function);
    set_register_language_type(func_reg, func_type);
    set_register_abi_type(func_reg, Type::Ptr);
    
    return func_reg;
}

// Statement handlers

Reg Generator::emit_error_construct_expr(LM::Frontend::AST::ErrorConstructExpr& expr) {
    Reg dst = allocate_register();
    
    // For the unified Type? system, err() creates a generic error
    auto result_type = std::make_shared<::Type>(::TypeTag::ErrorUnion);
    set_register_type(dst, result_type);
    
    // Enhanced error construction with custom type and message
    std::string errorType = expr.errorType.empty() ? "DefaultError" : expr.errorType;
    std::string errorMessage = "Operation failed";
    
    // If there are arguments, the first one should be the error message
    if (!expr.arguments.empty()) {
        // Handle string literal messages
        if (auto literalExpr = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(expr.arguments[0])) {
            if (std::holds_alternative<std::string>(literalExpr->value)) {
                errorMessage = std::get<std::string>(literalExpr->value);
            }
        }
        // Support dynamic error messages from expressions
        Reg message_reg = emit_expr(*expr.arguments[0]);
        emit_instruction(LIR_Inst(LIR_Op::Param, message_reg, 0, 0));
    }
    
    // Create the instruction with error information in the comment
    LIR_Inst error_inst(LIR_Op::ConstructError, Type::Ptr, dst, 0, 0);
    error_inst.comment = "ERROR_INFO:" + errorType + ":" + errorMessage;
    emit_instruction(error_inst);
    
    return dst;
}


Reg Generator::emit_ok_construct_expr(LM::Frontend::AST::OkConstructExpr& expr) {
    Reg dst = allocate_register();
    
    // First evaluate the value to be wrapped
    Reg value_reg = emit_expr(*expr.value);
    
    // Create ok value using the unified system
    auto result_type = std::make_shared<::Type>(::TypeTag::ErrorUnion);
    set_register_type(dst, result_type);
    
    // Generate ConstructOk instruction with the actual value
    emit_instruction(LIR_Inst(LIR_Op::ConstructOk, Type::Ptr, dst, value_reg, 0));
    return dst;
}


Reg Generator::emit_fallible_expr(LM::Frontend::AST::FallibleExpr& expr) {
    // Evaluate the expression that may return a Result (Type?)
    Reg result_reg = emit_expr(*expr.expression);
    
    // Create a register to hold the error check result
    Reg is_error_reg = allocate_register();
    auto bool_type = std::make_shared<::Type>(::TypeTag::Bool);
    set_register_type(is_error_reg, bool_type);
    
    // Check if the result contains an error
    emit_instruction(LIR_Inst(LIR_Op::IsError, Type::Bool, is_error_reg, result_reg, 0));
    
    if (cfg_context_.building_cfg) {
        // CFG mode: create blocks for error handling
        LIR_BasicBlock* error_block = create_basic_block("error_handling");
        LIR_BasicBlock* success_block = create_basic_block("success_unwrap");
        LIR_BasicBlock* continue_block = create_basic_block("fallible_continue");
        
        // Create a register to hold the final result (either unwrapped value or else block result)
        Reg final_result_reg = allocate_register();
        
        // If it's an error, jump to error handling block
        emit_instruction(LIR_Inst(LIR_Op::JumpIf, Type::Void, 0, is_error_reg, 0, error_block->id));
        
        // Explicit jump to success block to ensure correct control flow
        emit_instruction(LIR_Inst(LIR_Op::Jump, Type::Void, 0, 0, 0, success_block->id));
        
        // Set up CFG edges
        add_block_edge(get_current_block(), error_block);
        add_block_edge(get_current_block(), success_block);
        
        // === Success Block: unwrap the value ===
        set_current_block(success_block);
        
        Reg unwrapped_reg = allocate_register();
        TypePtr fallible_type = get_register_type(result_reg);
        TypePtr success_type = type_system_->STRING_TYPE; // Should extract from ErrorUnion type
        set_register_type(unwrapped_reg, success_type);
        
        emit_instruction(LIR_Inst(LIR_Op::Unwrap, Type::I64, unwrapped_reg, result_reg, 0));
        
        // Move unwrapped value to final result register
        emit_instruction(LIR_Inst(LIR_Op::Mov, Type::I64, final_result_reg, unwrapped_reg, 0));
        
        // Jump to continue block
        emit_instruction(LIR_Inst(LIR_Op::Jump, Type::Void, 0, 0, 0, continue_block->id));
        add_block_edge(success_block, continue_block);
        
        // === Error Block: handle error ===
        set_current_block(error_block);
        
        if (expr.elseHandler) {
            // ? else {} construct - execute the else block instead of propagating          
            // Allocate register for the else block result
            Reg default_reg = allocate_register();
            
            // Set up else block context
            else_context_.in_else_block = true;
            else_context_.result_register = default_reg;
            
            // Execute the else block statements
            emit_stmt(*expr.elseHandler);
            
            // Clear else block context
            else_context_.in_else_block = false;
            else_context_.result_register = UINT32_MAX;
            
            // Move default value to final result register
            emit_instruction(LIR_Inst(LIR_Op::Mov, Type::I64, final_result_reg, default_reg, 0));
            
            // Jump to continue block
            emit_instruction(LIR_Inst(LIR_Op::Jump, Type::Void, 0, 0, 0, continue_block->id));
            add_block_edge(error_block, continue_block);
            
        } else {
            // Simple ? operator - propagate error by returning
            emit_instruction(LIR_Inst(LIR_Op::Return, Type::Void, result_reg, 0, 0));
            // No edge to continue block since we return
        }
        
        // === Continue Block: merge point for both paths ===
        set_current_block(continue_block);
        
        return final_result_reg; // Return the final result register
        
    } else {
        // Non-CFG mode: use labels and jumps
        uint32_t error_label = generate_label();
        uint32_t continue_label = generate_label();
        
        // If it's an error, jump to error handling
        emit_instruction(LIR_Inst(LIR_Op::JumpIf, Type::Void, 0, is_error_reg, 0, error_label));
        
        // Success path: unwrap the value
        Reg unwrapped_reg = allocate_register();
        TypePtr success_type = type_system_->STRING_TYPE;
        set_register_type(unwrapped_reg, success_type);
        
        emit_instruction(LIR_Inst(LIR_Op::Unwrap, Type::I64, unwrapped_reg, result_reg, 0));
        
        // Jump to continue execution
        emit_instruction(LIR_Inst(LIR_Op::Jump, Type::Void, 0, 0, 0, continue_label));
        
        // Error handling block
        emit_instruction(LIR_Inst(LIR_Op::Label, Type::Void, error_label, 0, 0));
        
        if (expr.elseHandler) {
            // ? else {} construct - execute the else block           
            // Set up else block context
            else_context_.in_else_block = true;
            else_context_.result_register = unwrapped_reg;
            
            // Execute the else block statements
            emit_stmt(*expr.elseHandler);
            
            // Clear else block context
            else_context_.in_else_block = false;
            else_context_.result_register = UINT32_MAX;
            
        } else {
            // Simple ? operator - propagate error by returning
            emit_instruction(LIR_Inst(LIR_Op::Return, Type::Void, result_reg, 0, 0));
        }
        
        // Continue label
        emit_instruction(LIR_Inst(LIR_Op::Label, Type::Void, continue_label, 0, 0));
        
        return unwrapped_reg;
    }
}


Reg Generator::emit_this_expr(LM::Frontend::AST::ThisExpr& expr) {
    if (this_register_ == UINT32_MAX) {
        report_error("'this' used outside of method context");
        return 0;
    }
    return this_register_;
}

// Smart module system implementations

Reg Generator::emit_channel_offer_expr(LM::Frontend::AST::ChannelOfferExpr& expr) {

    // Evaluate value to offer
    Reg value_reg = emit_expr(*expr.value);
    
    // Evaluate channel
    Reg channel_reg = emit_expr(*expr.channel);
    
    // Generate ChannelOffer instruction
    Reg result = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::ChannelOffer, result, channel_reg, value_reg));
    set_register_type(result, std::make_shared<::Type>(::TypeTag::Bool));
    
    return result;
}


Reg Generator::emit_channel_poll_expr(LM::Frontend::AST::ChannelPollExpr& expr) {
    // Evaluate channel
    Reg channel_reg = emit_expr(*expr.channel);
    
    // Generate ChannelPoll instruction
    Reg result = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::ChannelPoll, result, channel_reg));
    set_register_type(result, std::make_shared<::Type>(::TypeTag::Any)); // Returns Option<T>
    
    return result;
}


Reg Generator::emit_channel_send_expr(LM::Frontend::AST::ChannelSendExpr& expr) {

    // Evaluate value to send
    Reg value_reg = emit_expr(*expr.value);
    
    // Evaluate channel
    Reg channel_reg = emit_expr(*expr.channel);
    
    // Generate ChannelSend instruction (blocking)
    Reg result = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::ChannelSend, result, channel_reg, value_reg));
    set_register_type(result, std::make_shared<::Type>(::TypeTag::Nil)); // Void return
    
    return result;
}


Reg Generator::emit_channel_recv_expr(LM::Frontend::AST::ChannelRecvExpr& expr) {

    // Evaluate channel
    Reg channel_reg = emit_expr(*expr.channel);
    
    // Generate ChannelRecv instruction (blocking)
    Reg result = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::ChannelRecv, result, channel_reg));
    set_register_type(result, std::make_shared<::Type>(::TypeTag::Any)); // Returns T
    
    return result;
}
// Frame system implementations

Reg Generator::emit_frame_instantiation_expr(LM::Frontend::AST::FrameInstantiationExpr& expr) {
    // Reuse the same logic as emit_call_expr for frame instantiation
    LM::Frontend::AST::CallExpr callExpr;
    callExpr.callee = std::make_shared<LM::Frontend::AST::VariableExpr>();
    static_cast<LM::Frontend::AST::VariableExpr*>(callExpr.callee.get())->name = expr.frameName;
    callExpr.arguments = expr.positionalArgs;
    callExpr.namedArgs = expr.namedArgs;
    callExpr.line = expr.line;
    callExpr.inferred_type = expr.inferred_type;
    
    return emit_call_expr(callExpr);
}


} // namespace LIR
} // namespace LM

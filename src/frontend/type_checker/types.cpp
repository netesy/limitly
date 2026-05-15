#include "../type_checker.hh"

using namespace LM::Frontend;

namespace LM {
namespace Frontend {

TypePtr TypeChecker::resolve_type_annotation(std::shared_ptr<LM::Frontend::AST::TypeAnnotation> annotation) {
    if (!annotation) return nullptr;
    
     // Handle structural types
    if (annotation->isStructural && !annotation->structuralFields.empty()) {
        std::vector<std::pair<std::string, TypePtr>> fields;
        for (const auto& field : annotation->structuralFields) {
            fields.push_back({field.name, resolve_type_annotation(field.type)});
        }
        return type_system.createStructuralType(fields, annotation->hasRest);
    }
    // Handle union types
    if (annotation->isUnion && !annotation->unionTypes.empty()) {
        std::vector<TypePtr> union_member_types;
        
        // Resolve each type in the union
        for (const auto& union_member : annotation->unionTypes) {
            TypePtr member_type = resolve_type_annotation(union_member);
            if (member_type) {
                union_member_types.push_back(member_type);
            }
        }
        
        if (!union_member_types.empty()) {
            // Create a union type using the type system
            return type_system.createUnionType(union_member_types);
        }
    }
    
    // Handle List types (e.g., [int])
    if (annotation->isList) {
        TypePtr elemType = type_system.ANY_TYPE;
        if (annotation->elementType) {
            elemType = resolve_type_annotation(annotation->elementType);
        } else if (!annotation->functionParams.empty()) {
            elemType = resolve_type_annotation(annotation->functionParams[0]);
        }
        return type_system.createTypedListType(elemType);
    }

    // Handle Dict types (e.g., {str: int})
    if (annotation->isDict) {
        TypePtr keyType = type_system.ANY_TYPE;
        TypePtr valType = type_system.ANY_TYPE;
        if (annotation->keyType && annotation->valueType) {
            keyType = resolve_type_annotation(annotation->keyType);
            valType = resolve_type_annotation(annotation->valueType);
        } else if (annotation->functionParams.size() >= 2) {
            keyType = resolve_type_annotation(annotation->functionParams[0]);
            valType = resolve_type_annotation(annotation->functionParams[1]);
        }
        return type_system.createTypedDictType(keyType, valType);
    }

    // Handle Tuple types (e.g., (int, str))
    if (annotation->isTuple) {
        std::vector<TypePtr> elementTypes;
        for (const auto& t : annotation->tupleTypes) {
            elementTypes.push_back(resolve_type_annotation(t));
        }
        return type_system.createTupleType(elementTypes);
    }

    // Handle Function types (e.g., fn(int, int): int)
    if (annotation->isFunction) {
        std::vector<TypePtr> paramTypes;
        std::vector<std::string> paramNames;
        
        // Handle both FunctionTypeAnnotation and generic TypeAnnotation with isFunction=true
        if (auto func_annot = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionTypeAnnotation>(annotation)) {
            for (const auto& p : func_annot->parameters) {
                paramTypes.push_back(resolve_type_annotation(p.type));
                paramNames.push_back(p.name);
            }
            TypePtr returnType = func_annot->returnType ? resolve_type_annotation(func_annot->returnType) : type_system.NIL_TYPE;
            return type_system.createFunctionType(paramNames, paramTypes, returnType);
        } else if (!annotation->functionParameters.empty()) {
            for (const auto& p : annotation->functionParameters) {
                paramTypes.push_back(resolve_type_annotation(p.type));
                paramNames.push_back(p.name);
            }
            TypePtr returnType = annotation->returnType ? resolve_type_annotation(annotation->returnType) : type_system.NIL_TYPE;
            return type_system.createFunctionType(paramNames, paramTypes, returnType);
        } else {
            // Fallback for legacy functionParams
            for (const auto& p : annotation->functionParams) {
                paramTypes.push_back(resolve_type_annotation(p));
                paramNames.push_back("");
            }
            TypePtr returnType = annotation->returnType ? resolve_type_annotation(annotation->returnType) : type_system.NIL_TYPE;
            return type_system.createFunctionType(paramNames, paramTypes, returnType);
        }
    }

    // First try to get the base type from the type system (handles built-in types and aliases)
    TypePtr base_type = type_system.getType(annotation->typeName);
    
    // Check if getType returned NIL_TYPE (which means type not found)
    if (base_type && base_type->tag == TypeTag::Nil) {
        // Type not found, try type alias
        try {
            base_type = type_system.getTypeAlias(annotation->typeName);
        } catch (...) {
            base_type = nullptr;
        }
    }
    
    if (!base_type || base_type->tag == TypeTag::Nil) {
        // Handle special cases that might not be in the type system yet
        if (annotation->typeName == "atomic") {
            // atomic is an alias for i64
            base_type = type_system.INT64_TYPE;
        } else if (annotation->typeName == "channel") {
            // channel type is represented as any (channel handle)
            base_type = type_system.ANY_TYPE;
        } else if (annotation->typeName == "nil") {
            base_type = type_system.NIL_TYPE;
        } else {
            // If it's not a built-in type, it might be a user-defined type alias or enum
            TypePtr custom_type = type_system.getType(annotation->typeName);
            if (custom_type && custom_type->tag != TypeTag::Nil) {
                base_type = custom_type;
            } else {
                add_error("Unknown type: " + annotation->typeName);
                return type_system.NIL_TYPE;
            }
        }
    }
    
    // Handle refinement types (e.g., int where value > 0)
    if (annotation->isRefined && annotation->refinementCondition) {
        // Create new scope to avoid polluting outer scope with 'value'
        enter_scope();
        // Bind 'value' to the base type for condition checking
        declare_variable("value", base_type);

        // Check the refinement condition
        TypePtr conditionType = check_expression(annotation->refinementCondition);
        if (!is_boolean_type(conditionType)) {
            add_error("Refinement condition must be boolean, got " + conditionType->toString(), annotation->refinementCondition->line);
        }

        exit_scope();

        RefinedType refined;
        refined.baseType = base_type;
        refined.condition = annotation->refinementCondition;
        base_type = std::make_shared<::Type>(TypeTag::Refined, refined);
    }

    // Handle optional types (e.g., str?, int?) - unified Type? system
    if (annotation->isOptional) {
        // Create a fallible type (Type?) using the unified error system
        // Type? is syntactic sugar for Result<Type, DefaultError>
        return type_system.createFallibleType(base_type);
    }
    
    return base_type;
}

bool TypeChecker::is_type_compatible(TypePtr expected, TypePtr actual) {
    if (!expected || !actual) return false;
    if (expected->tag == TypeTag::Any || actual->tag == TypeTag::Any) return true;
    if (is_numeric_type(expected) && is_numeric_type(actual)) {
        if (is_decimal_type(expected) || is_decimal_type(actual)) {
            return expected->tag == actual->tag;
        }
        return true;
    }

    auto get_base = [](const std::string& s) {
        size_t dot = s.find_last_of(".");
        return (dot != std::string::npos) ? s.substr(dot+1) : s;
    };

    if (actual->tag == TypeTag::Frame && expected->tag == TypeTag::Trait) {
        auto* fData = std::get_if<FrameType>(&actual->extra);
        auto* tData = std::get_if<TraitType>(&expected->extra);
        if (fData && tData) {
            auto check_methods = [&](const std::string& target_frame, const std::string& target_trait) {
                auto fit = frame_declarations.find(target_frame);
                if (fit == frame_declarations.end()) {
                    for(auto const& [k,v] : frame_declarations) if(get_base(k) == get_base(target_frame)){fit=frame_declarations.find(k); break;}
                }
                auto tit = trait_declarations.find(target_trait);
                if (tit == trait_declarations.end()) {
                    for(auto const& [k,v] : trait_declarations) if(get_base(k) == get_base(target_trait)){tit=trait_declarations.find(k); break;}
                }
                if (fit != frame_declarations.end() && tit != trait_declarations.end()) {
                    for (const auto& imp : fit->second.declaration->implements) if (get_base(imp) == get_base(target_trait)) return true;
                    for (const auto& tm : tit->second.declaration->methods) {
                        bool found = false;
                        for (const auto& fm : fit->second.declaration->methods) if (fm->name == tm->name) { found = true; break; }
                        if (!found) return false;
                    }
                    return true;
                }
                return false;
            };
            if (check_methods(fData->name, tData->name)) return true;
        }
    }
    if (actual->tag == TypeTag::Trait && expected->tag == TypeTag::Trait) {
        auto* aData = std::get_if<TraitType>(&actual->extra);
        auto* eData = std::get_if<TraitType>(&expected->extra);
        if (aData && eData && get_base(aData->name) == get_base(eData->name)) return true;
    }
    if (expected->tag == TypeTag::Refined) {
        if (const auto* refined = std::get_if<RefinedType>(&expected->extra)) return is_type_compatible(refined->baseType, actual);
    }
    if (actual->tag == TypeTag::Refined) {
        if (const auto* refined = std::get_if<RefinedType>(&actual->extra)) return is_type_compatible(expected, refined->baseType);
    }
    return type_system.isCompatible(actual, expected);
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
                                     TypePtr& result_type,
                                     int line) {
    // Check if it's an enum variant constructor
    TypePtr callee_type = lookup_variable(func_name);
    if (callee_type && callee_type->tag == TypeTag::Function) {
        if (auto* func_type = std::get_if<FunctionType>(&callee_type->extra)) {
            if (validate_argument_types(func_type->paramTypes, arg_types, func_name)) {
                result_type = func_type->returnType;
                return true;
            }
        }
    }

    auto it = function_signatures.find(func_name);
    if (it == function_signatures.end()) {
        // Track this as an undefined symbol to suppress cascading errors
        undefined_symbols.insert(func_name);
        add_error("Undefined function: " + func_name, line);
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
    // Check if we have enough arguments
    if (actual.size() > expected.size()) {
        return false;
    }

    // Get function signature to check optional parameters
    auto func_it = function_signatures.find(func_name);
    if (func_it == function_signatures.end()) {
        // Might be a constructor/enum variant, check strictly
        if (actual.size() != expected.size()) return false;
        for (size_t i = 0; i < actual.size(); ++i) {
            if (!is_type_compatible(expected[i], actual[i])) return false;
        }
        return true;
    }
    
    const FunctionSignature& sig = func_it->second;
    auto func_decl = sig.declaration;
    
    if (!func_decl) {
        // Fallback to strict checking if we don't have declaration
        if (expected.size() != actual.size()) {
            add_error("Function " + func_name + " expects " + 
                     std::to_string(expected.size()) + " arguments, got " + 
                     std::to_string(actual.size()));
            return false;
        }
    } else {
        // Check argument count considering optional parameters
        size_t min_args = 0; // Count required parameters
        size_t max_args = expected.size(); // All parameters
        
        // Count required vs optional parameters
        for (size_t i = 0; i < sig.optional_params.size() && i < expected.size(); ++i) {
            if (!sig.optional_params[i]) {
                min_args++; // This is a required parameter
            }
        }
        
        if (actual.size() < min_args || actual.size() > max_args) {
            if (min_args == max_args) {
                add_error("Function " + func_name + " expects " + 
                         std::to_string(min_args) + " arguments, got " + 
                         std::to_string(actual.size()));
            } else {
                add_error("Function " + func_name + " expects " + 
                         std::to_string(min_args) + "-" + std::to_string(max_args) + 
                         " arguments, got " + std::to_string(actual.size()));
            }
            return false;
        }
    }
    
    // Check type compatibility for provided arguments
    for (size_t i = 0; i < actual.size() && i < expected.size(); ++i) {
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
                   type->tag == TypeTag::Float32 || type->tag == TypeTag::Float64 ||
                   type->tag == TypeTag::Decimal2 || type->tag == TypeTag::Decimal4 || type->tag == TypeTag::Decimal6);
}

bool TypeChecker::is_integer_type(TypePtr type) {
    return type && (type->tag == TypeTag::Int || type->tag == TypeTag::Int8 || 
                   type->tag == TypeTag::Int16 || type->tag == TypeTag::Int32 || 
                   type->tag == TypeTag::Int64 || type->tag == TypeTag::Int128 ||
                   type->tag == TypeTag::UInt || type->tag == TypeTag::UInt8 || 
                   type->tag == TypeTag::UInt16 || type->tag == TypeTag::UInt32 || 
                   type->tag == TypeTag::UInt64 || type->tag == TypeTag::UInt128);
}

bool TypeChecker::is_float_type(TypePtr type) {
    return type && (type->tag == TypeTag::Float32 || type->tag == TypeTag::Float64);
}

bool TypeChecker::is_decimal_type(TypePtr type) {
    return type && (type->tag == TypeTag::Decimal2 || type->tag == TypeTag::Decimal4 || type->tag == TypeTag::Decimal6);
}

int TypeChecker::get_decimal_scale(TypePtr type) {
    if (!type) return 0;
    switch (type->tag) {
        case TypeTag::Decimal2: return 2;
        case TypeTag::Decimal4: return 4;
        case TypeTag::Decimal6: return 6;
        default: return 0;
    }
}

bool TypeChecker::is_boolean_type(TypePtr type) {
    if (!type) return false;
    
    // Direct boolean type
    if (type->tag == TypeTag::Bool) {
        return true;
    }
    
    // Union types (including optional types) can be used in boolean contexts
    if (type->tag == TypeTag::Union) {
        return true; // Optional types like str? can be used in if conditions
    }
    
    // ErrorUnion types (fallible types like str?) can be used in boolean contexts
    if (type->tag == TypeTag::ErrorUnion) {
        return true; // Fallible types like str? can be used in if conditions
    }
    
    return false;
}

bool TypeChecker::is_string_type(TypePtr type) {
    return type && type->tag == TypeTag::String;
}

bool TypeChecker::is_optional_type(TypePtr type) {
    if (!type || type->tag != TypeTag::ErrorUnion) {
        return false;
    }
    
    // Both optional types (str?) and fallible types (int?DivisionByZero) 
    // should be allowed in if conditions for null/error checking
    auto* errorUnionPtr = std::get_if<ErrorUnionType>(&type->extra);
    if (!errorUnionPtr) {
        throw std::runtime_error("Missing ErrorUnionType data in ErrorUnion type");
    }
    auto& errorUnion = *errorUnionPtr;
    
    // Optional types: empty error types and marked as generic (str?)
    bool isOptional = errorUnion.errorTypes.empty() && errorUnion.isGenericError;
    
    // Fallible types: have specific error types (int?DivisionByZero)
    bool isFallible = !errorUnion.errorTypes.empty();
    
    return isOptional || isFallible;
}

bool TypeChecker::is_error_union_type(TypePtr type) {
    return type && type->tag == TypeTag::ErrorUnion;
}

bool TypeChecker::is_union_type(TypePtr type) {
    return type && type->tag == TypeTag::Union;
}

bool TypeChecker::requires_error_handling(TypePtr type) {
    return is_error_union_type(type);
}

TypePtr TypeChecker::promote_numeric_types(TypePtr left, TypePtr right) {
    return get_common_type(left, right);
}

// =============================================================================
// ADVANCED ERROR HANDLING METHODS
// =============================================================================

void TypeChecker::validate_function_error_types(const std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>& stmt) {
    // Validate consistency between return type and declared error types
    if (stmt->returnType && *stmt->returnType) {
        auto returnType = resolve_type_annotation(*stmt->returnType);
        
        if (is_error_union_type(returnType)) {
            auto* errorUnionPtr = std::get_if<ErrorUnionType>(&returnType->extra);
            if (!errorUnionPtr) {
                throw std::runtime_error("Missing ErrorUnionType data in ErrorUnion type");
            }
            auto& errorUnion = *errorUnionPtr;
            
            // If function declares specific error types, they should match return type
            if (stmt->canFail && !stmt->declaredErrorTypes.empty()) {
                // Check that declared error types match return type error types
                if (!errorUnion.isGenericError) {
                    for (const auto& declaredError : stmt->declaredErrorTypes) {
                        if (std::find(errorUnion.errorTypes.begin(), errorUnion.errorTypes.end(), declaredError) == errorUnion.errorTypes.end()) {
                            add_error("Function '" + stmt->name + "' declares error type '" + declaredError + 
                                    "' but return type does not include this error type", stmt->line);
                        }
                    }
                    
                    for (const auto& returnError : errorUnion.errorTypes) {
                        if (std::find(stmt->declaredErrorTypes.begin(), stmt->declaredErrorTypes.end(), returnError) == stmt->declaredErrorTypes.end()) {
                            add_error("Function '" + stmt->name + "' return type includes error type '" + returnError + 
                                    "' but it is not declared in function signature", stmt->line);
                        }
                    }
                }
            }
        } else if (stmt->canFail) {
            // Function declares it can fail but return type is not an error union
            add_error("Function '" + stmt->name + "' declares 'throws' but return type is not an error union type", stmt->line);
        }
    } else if (stmt->canFail) {
        // Function declares it can fail but has no return type annotation
        add_error("Function '" + stmt->name + "' declares 'throws' but has no return type annotation. " +
                "Use 'Type?' for generic errors or 'Type?ErrorType1,ErrorType2' for specific error types", stmt->line);
    }
}

void TypeChecker::validate_function_body_error_types(const std::shared_ptr<LM::Frontend::AST::FunctionDeclaration>& stmt) {
    if (!stmt->canFail) {
        return; // No error type validation needed for non-fallible functions
    }
    
    // Infer error types that function body can actually produce
    std::vector<std::string> inferredErrorTypes = infer_function_error_types(stmt->body);
    
    // If function declares specific error types, validate they can be produced
    if (!stmt->declaredErrorTypes.empty()) {
        for (const auto& declaredError : stmt->declaredErrorTypes) {
            if (!can_function_produce_error_type(stmt->body, declaredError)) {
                add_error("Function '" + stmt->name + "' declares error type '" + declaredError + 
                        "' but function body cannot produce this error type", stmt->line);
            }
        }
        
        // Check for undeclared error types that body might produce
        for (const auto& inferredError : inferredErrorTypes) {
            if (std::find(stmt->declaredErrorTypes.begin(), stmt->declaredErrorTypes.end(), inferredError) == stmt->declaredErrorTypes.end()) {
                add_error("Function '" + stmt->name + "' body can produce error type '" + inferredError + 
                        "' but it is not declared in function signature", stmt->line);
            }
        }
    }
}

std::vector<std::string> TypeChecker::infer_function_error_types(const std::shared_ptr<LM::Frontend::AST::Statement>& body) {
    std::vector<std::string> errorTypes;
    
    if (auto blockStmt = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(body)) {
        for (const auto& stmt : blockStmt->statements) {
            auto stmtErrors = infer_function_error_types(stmt);
            errorTypes.insert(errorTypes.end(), stmtErrors.begin(), stmtErrors.end());
        }
    } else if (auto returnStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ReturnStatement>(body)) {
        if (returnStmt->value) {
            auto returnErrors = infer_expression_error_types(returnStmt->value);
            errorTypes.insert(errorTypes.end(), returnErrors.begin(), returnErrors.end());
        }
    } else if (auto ifStmt = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(body)) {
        auto thenErrors = infer_function_error_types(ifStmt->thenBranch);
        errorTypes.insert(errorTypes.end(), thenErrors.begin(), thenErrors.end());
        
        if (ifStmt->elseBranch) {
            auto elseErrors = infer_function_error_types(ifStmt->elseBranch);
            errorTypes.insert(errorTypes.end(), elseErrors.begin(), elseErrors.end());
        }
    } else if (auto exprStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(body)) {
        // Check for fallible expressions that might propagate errors
        auto exprErrors = infer_expression_error_types(exprStmt->expression);
        errorTypes.insert(errorTypes.end(), exprErrors.begin(), exprErrors.end());
    }
    
    // Remove duplicates
    std::sort(errorTypes.begin(), errorTypes.end());
    errorTypes.erase(std::unique(errorTypes.begin(), errorTypes.end()), errorTypes.end());
    
    return errorTypes;
}

std::vector<std::string> TypeChecker::infer_expression_error_types(const std::shared_ptr<LM::Frontend::AST::Expression>& expr) {
    std::vector<std::string> errorTypes;
    
    if (auto errorConstruct = std::dynamic_pointer_cast<LM::Frontend::AST::ErrorConstructExpr>(expr)) {
        // Direct error construction
        errorTypes.push_back(errorConstruct->errorType);
        
    } else if (auto fallibleExpr = std::dynamic_pointer_cast<LM::Frontend::AST::FallibleExpr>(expr)) {
        // Fallible expression with ? operator - propagates errors from inner expression
        auto innerErrors = infer_expression_error_types(fallibleExpr->expression);
        errorTypes.insert(errorTypes.end(), innerErrors.begin(), innerErrors.end());
        
    } else if (auto callExpr = std::dynamic_pointer_cast<LM::Frontend::AST::CallExpr>(expr)) {
        // Function call - check if called function can produce errors
        if (auto varExpr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(callExpr->callee)) {
            auto it = function_signatures.find(varExpr->name);
            if (it != function_signatures.end() && it->second.can_fail) {
                errorTypes.insert(errorTypes.end(), it->second.error_types.begin(), it->second.error_types.end());
            }
        }
        
    } else if (auto binaryExpr = std::dynamic_pointer_cast<LM::Frontend::AST::BinaryExpr>(expr)) {
        // Binary expressions might produce built-in errors (e.g., division by zero)
        if (binaryExpr->op == TokenType::SLASH) {
            errorTypes.push_back("DivisionByZero");
        }
        
        // Also check operands for error propagation
        auto leftErrors = infer_expression_error_types(binaryExpr->left);
        auto rightErrors = infer_expression_error_types(binaryExpr->right);
        errorTypes.insert(errorTypes.end(), leftErrors.begin(), leftErrors.end());
        errorTypes.insert(errorTypes.end(), rightErrors.begin(), rightErrors.end());
        
    } else if (auto indexExpr = std::dynamic_pointer_cast<LM::Frontend::AST::IndexExpr>(expr)) {
        // Array/dict indexing can produce IndexOutOfBounds errors
        errorTypes.push_back("IndexOutOfBounds");
        
        // Also check object and index expressions
        auto objectErrors = infer_expression_error_types(indexExpr->object);
        auto indexErrors = infer_expression_error_types(indexExpr->index);
        errorTypes.insert(errorTypes.end(), objectErrors.begin(), objectErrors.end());
        errorTypes.insert(errorTypes.end(), indexErrors.begin(), indexErrors.end());
    }
    
    // Remove duplicates
    std::sort(errorTypes.begin(), errorTypes.end());
    errorTypes.erase(std::unique(errorTypes.begin(), errorTypes.end()), errorTypes.end());
    
    return errorTypes;
}

bool TypeChecker::can_function_produce_error_type(const std::shared_ptr<LM::Frontend::AST::Statement>& body, 
                                             const std::string& errorType) {
    // Check if function body can produce specified error type
    
    if (auto blockStmt = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(body)) {
        for (const auto& stmt : blockStmt->statements) {
            if (can_function_produce_error_type(stmt, errorType)) {
                return true;
            }
        }
    } else if (auto returnStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ReturnStatement>(body)) {
        if (returnStmt->value) {
            // Check if return expression can produce error type
            auto returnErrors = infer_expression_error_types(returnStmt->value);
            return std::find(returnErrors.begin(), returnErrors.end(), errorType) != returnErrors.end();
        }
    } else if (auto ifStmt = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(body)) {
        return can_function_produce_error_type(ifStmt->thenBranch, errorType) ||
               (ifStmt->elseBranch && can_function_produce_error_type(ifStmt->elseBranch, errorType));
    } else if (auto exprStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(body)) {
        // Check for fallible expressions that might propagate errors
        auto exprErrors = infer_expression_error_types(exprStmt->expression);
        return std::find(exprErrors.begin(), exprErrors.end(), errorType) != exprErrors.end();
    }
    
    return false;
}

bool TypeChecker::can_propagate_error(const std::vector<std::string>& source_errors, 
                                  const std::vector<std::string>& target_errors) {
    // If target allows generic errors, any source is compatible
    if (target_errors.empty()) {
        return true;
    }
    
    // Check that all source errors are in target errors
    for (const auto& sourceError : source_errors) {
        bool found = std::find(target_errors.begin(), target_errors.end(), sourceError) != target_errors.end();
        if (!found) {
            return false;
        }
    }
    
    return true;
}

bool TypeChecker::is_error_union_compatible(TypePtr from, TypePtr to) {
    if (!is_error_union_type(from) || !is_error_union_type(to)) {
        return false;
    }
    
    auto* fromErrorUnionPtr = std::get_if<ErrorUnionType>(&from->extra);
    auto* toErrorUnionPtr = std::get_if<ErrorUnionType>(&to->extra);
    if (!fromErrorUnionPtr || !toErrorUnionPtr) {
        return false;
    }
    auto& fromErrorUnion = *fromErrorUnionPtr;
    auto& toErrorUnion = *toErrorUnionPtr;
    
    // Success types must be compatible
    if (!is_type_compatible(fromErrorUnion.successType, toErrorUnion.successType)) {
        return false;
    }
    
    // Check error type compatibility
    return can_propagate_error(fromErrorUnion.errorTypes, toErrorUnion.errorTypes);
}

std::string TypeChecker::join_error_types(const std::vector<std::string>& errorTypes) {
    if (errorTypes.empty()) {
        return "any error";
    }
    
    std::string result;
    for (size_t i = 0; i < errorTypes.size(); ++i) {
        if (i > 0) result += ", ";
        result += errorTypes[i];
    }
    return result;
}

// =============================================================================
// PATTERN MATCHING METHODS
// =============================================================================

bool TypeChecker::is_exhaustive_error_match(const std::vector<std::shared_ptr<LM::Frontend::AST::MatchCase>>& cases, TypePtr type) {
    if (!is_error_union_type(type)) {
        return true; // Non-error types don't need exhaustive error matching
    }
    
    auto* errorUnionPtr = std::get_if<ErrorUnionType>(&type->extra);
    if (!errorUnionPtr) {
        return false;
    }
    auto& errorUnion = *errorUnionPtr;
    
    bool hasSuccessCase = false;
    bool hasGenericErrorCase = false;
    std::unordered_set<std::string> coveredErrors;
    
    for (const auto& matchCase : cases) {
        // Enhanced pattern analysis for error matching
        if (auto valPattern = std::dynamic_pointer_cast<LM::Frontend::AST::ValPatternExpr>(matchCase->pattern)) {
            hasSuccessCase = true;
        } else if (auto errPattern = std::dynamic_pointer_cast<LM::Frontend::AST::ErrPatternExpr>(matchCase->pattern)) {
            if (errPattern->errorType.has_value()) {
                // Specific error type in err pattern
                coveredErrors.insert(errPattern->errorType.value());
            } else {
                // Generic error pattern
                hasGenericErrorCase = true;
            }
        } else if (auto bindingPattern = std::dynamic_pointer_cast<LM::Frontend::AST::BindingPatternExpr>(matchCase->pattern)) {
            if (bindingPattern->typeName == "val") {
                hasSuccessCase = true;
            } else if (bindingPattern->typeName == "err") {
                hasGenericErrorCase = true;
            } else {
                // Specific error type pattern
                coveredErrors.insert(bindingPattern->typeName);
            }
        } else {
            // Wildcard or other patterns - assume they cover everything
            hasSuccessCase = true;
            hasGenericErrorCase = true;
        }
    }
    
    // For generic error unions, we need at least success and error cases
    if (errorUnion.isGenericError) {
        return hasSuccessCase && hasGenericErrorCase;
    }
    
    // For specific error unions, all error types must be covered plus success case
    bool allErrorsCovered = hasGenericErrorCase || 
                           (coveredErrors.size() >= errorUnion.errorTypes.size() &&
                            std::all_of(errorUnion.errorTypes.begin(), errorUnion.errorTypes.end(),
                                       [&coveredErrors](const std::string& errorType) {
                                           return coveredErrors.find(errorType) != coveredErrors.end();
                                       }));
    
    return hasSuccessCase && allErrorsCovered;
}

bool TypeChecker::is_exhaustive_union_match(TypePtr union_type, const std::vector<std::shared_ptr<LM::Frontend::AST::MatchCase>>& cases) {
    if (!is_union_type(union_type)) {
        return true; // Non-union types don't need union exhaustiveness checking
    }
    
    const auto* unionTypeInfo = std::get_if<UnionType>(&union_type->extra);
    if (!unionTypeInfo) {
        return true;
    }
    
    std::set<std::string> coveredVariantNames;
    bool hasWildcard = false;
    
    for (const auto& matchCase : cases) {
        if (auto bindingPattern = std::dynamic_pointer_cast<LM::Frontend::AST::BindingPatternExpr>(matchCase->pattern)) {
            coveredVariantNames.insert(bindingPattern->typeName);
        } else if (auto literalExpr = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(matchCase->pattern)) {
            if (std::holds_alternative<std::string>(literalExpr->value)) {
                coveredVariantNames.insert(std::get<std::string>(literalExpr->value));
            } else if (std::holds_alternative<std::nullptr_t>(literalExpr->value)) {
                hasWildcard = true;
            }
        } else if (auto varExpr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(matchCase->pattern)) {
            if (varExpr->name == "_") {
                hasWildcard = true;
            } else {
                coveredVariantNames.insert(varExpr->name);
            }
        }
    }
    
    if (hasWildcard) return true;
    
    // Check if all variant names are covered
    for (const auto& name : unionTypeInfo->variantNames) {
        if (coveredVariantNames.find(name) == coveredVariantNames.end()) {
            return false;
        }
    }
    
    return true;
}

bool TypeChecker::is_exhaustive_option_match(const std::vector<std::shared_ptr<LM::Frontend::AST::MatchCase>>& cases) {
    bool hasSomeCase = false;
    bool hasNoneCase = false;
    bool hasWildcard = false;
    
    for (const auto& matchCase : cases) {
        if (auto bindingPattern = std::dynamic_pointer_cast<LM::Frontend::AST::BindingPatternExpr>(matchCase->pattern)) {
            if (bindingPattern->typeName == "Some" || bindingPattern->typeName == "some") {
                hasSomeCase = true;
            } else if (bindingPattern->typeName == "None" || bindingPattern->typeName == "none") {
                hasNoneCase = true;
            } else if (bindingPattern->typeName == "_" || bindingPattern->typeName == "any") {
                hasWildcard = true;
            }
        } else if (auto varExpr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(matchCase->pattern)) {
            if (varExpr->name == "_" || varExpr->name == "any") {
                hasWildcard = true;
            }
        }
    }
    
    // If we have a wildcard, it's exhaustive
    if (hasWildcard) {
        return true;
    }
    
    // Otherwise, need both Some and None cases
    return hasSomeCase && hasNoneCase;
}

std::string TypeChecker::get_missing_union_variants(TypePtr union_type, const std::vector<std::shared_ptr<LM::Frontend::AST::MatchCase>>& cases) {
    if (!is_union_type(union_type)) {
        return "";
    }
    
    const auto* unionTypeInfo = std::get_if<UnionType>(&union_type->extra);
    if (!unionTypeInfo) {
        return "";
    }
    
    std::set<std::string> coveredVariantNames;
    bool hasWildcard = false;
    
    for (const auto& matchCase : cases) {
        if (auto bindingPattern = std::dynamic_pointer_cast<LM::Frontend::AST::BindingPatternExpr>(matchCase->pattern)) {
            coveredVariantNames.insert(bindingPattern->typeName);
        } else if (auto varExpr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(matchCase->pattern)) {
            if (varExpr->name == "_") {
                hasWildcard = true;
            } else {
                coveredVariantNames.insert(varExpr->name);
            }
        }
    }
    
    if (hasWildcard) return "";
    
    std::vector<std::string> missing;
    for (const auto& name : unionTypeInfo->variantNames) {
        if (coveredVariantNames.find(name) == coveredVariantNames.end()) {
            missing.push_back(name);
        }
    }
    
    if (missing.empty()) return "";
    
    std::string result = "Missing patterns for: ";
    for (size_t i = 0; i < missing.size(); ++i) {
        if (i > 0) result += ", ";
        result += missing[i];
    }
    return result;
}

} // namespace Frontend
} // namespace LM


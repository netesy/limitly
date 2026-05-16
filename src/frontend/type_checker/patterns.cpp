#include "../type_checker.hh"
#include <iostream>

using namespace LM::Frontend;

namespace LM {
namespace Frontend {

void TypeChecker::validate_pattern_compatibility(std::shared_ptr<LM::Frontend::AST::Expression> pattern_node, TypePtr match_type, int line) {
    if (!pattern_node) return;
    if (!match_type) match_type = type_system.ANY_TYPE;
    pattern_node->inferred_type = match_type;

    if (auto bindingPattern = std::dynamic_pointer_cast<LM::Frontend::AST::BindingPatternExpr>(pattern_node)) {
        if (bindingPattern->typeName == "val") {
            if (is_error_union_type(match_type)) {
                auto* errorUnionPtr = std::get_if<ErrorUnionType>(&match_type->extra);
                if (errorUnionPtr && !bindingPattern->patterns.empty()) {
                    validate_pattern_compatibility(bindingPattern->patterns[0], errorUnionPtr->successType, line);
                }
            } else if (match_type->tag == TypeTag::Any) {
                 if (!bindingPattern->patterns.empty()) {
                    validate_pattern_compatibility(bindingPattern->patterns[0], type_system.ANY_TYPE, line);
                 }
            } else {
                add_error("val pattern can only be used with error union types " + match_type->toString(), line);
            }
        } else if (bindingPattern->typeName == "err") {
            if (!is_error_union_type(match_type) && match_type->tag != TypeTag::Any) {
                add_error("err pattern can only be used with error union types " + match_type->toString(), line);
            } else if (!bindingPattern->patterns.empty()) {
                validate_pattern_compatibility(bindingPattern->patterns[0], type_system.NIL_TYPE, line);
            }
        } else {
            bool variant_resolved = false;
            TypePtr constructorType = lookup_variable(bindingPattern->typeName);

                        if (!constructorType && bindingPattern->typeName.find('.') == std::string::npos) {
                if (match_type && (match_type->tag == TypeTag::Enum || match_type->tag == TypeTag::UserDefined || match_type->tag == TypeTag::Frame)) {
                    if (auto* et = std::get_if<EnumType>(&match_type->extra)) {
                        std::string qualified = et->name + "." + bindingPattern->typeName;
                        constructorType = lookup_variable(qualified);
                    }
                }
                
                if (!constructorType) {
                    auto it = variant_owners.find(bindingPattern->typeName);
                    if (it != variant_owners.end() && !it->second.empty()) {
                        TypePtr owner = it->second[0];
                        if (owner) {
                            if (auto* enumInfoPtr = std::get_if<EnumType>(&owner->extra)) {
                                std::string qualified = enumInfoPtr->name + "." + bindingPattern->typeName;
                                constructorType = lookup_variable(qualified);
                            }
                        }
                    }
                }

                if (!constructorType) {
                    for (const auto& pair : variable_types) {
                        const std::string& name = pair.first;
                        if (name.length() > bindingPattern->typeName.length() && 
                            name.substr(name.length() - bindingPattern->typeName.length()) == bindingPattern->typeName &&
                            name[name.length() - bindingPattern->typeName.length() - 1] == '.') {
                            constructorType = pair.second;
                            break;
                        }
                    }
                }
            }

            if (constructorType) {
                if (constructorType->tag == TypeTag::Function) {
                    auto* funcType = std::get_if<FunctionType>(&constructorType->extra);
                    if (funcType) {
                        if (bindingPattern->patterns.size() != funcType->paramTypes.size()) {
                            add_error("Pattern '" + bindingPattern->typeName + "' expects " +
                                      std::to_string(funcType->paramTypes.size()) + " values, but found " +
                                      std::to_string(bindingPattern->patterns.size()), line);
                        } else {
                            if (funcType->paramTypes.size() == 1) {
                                bindingPattern->patterns[0]->inferred_type = funcType->paramTypes[0];
                            } else if (!funcType->paramTypes.empty()) {
                                auto payload_tuple = std::make_shared<::Type>(::TypeTag::Tuple);
                                TupleType tuple_extra;
                                tuple_extra.elementTypes = funcType->paramTypes;
                                payload_tuple->extra = tuple_extra;
                                for (auto& nested : bindingPattern->patterns) {
                                    nested->inferred_type = payload_tuple;
                                }
                            }
                            for (size_t i = 0; i < bindingPattern->patterns.size(); ++i) {
                                bindingPattern->patterns[i]->inferred_type = funcType->paramTypes[i];
                                validate_pattern_compatibility(bindingPattern->patterns[i], funcType->paramTypes[i], line);
                            }
                        }
                        variant_resolved = true;
                    }
                } else if (constructorType->tag == TypeTag::Enum || (constructorType->tag == TypeTag::UserDefined && std::get_if<EnumType>(&constructorType->extra))) {
                    if (!bindingPattern->patterns.empty()) {
                        add_error("Unit variant '" + bindingPattern->typeName + "' cannot have associated values", line);
                    }
                    variant_resolved = true;
                }
            }

            if (!variant_resolved && match_type->tag != TypeTag::Any) {
                add_error("Unknown pattern or constructor: " + bindingPattern->typeName, line);
            } else if (match_type->tag == TypeTag::Any && !variant_resolved) {
                for (auto& nested : bindingPattern->patterns) {
                    validate_pattern_compatibility(nested, type_system.ANY_TYPE, line);
                }
            }
        }
    } else if (auto listPattern = std::dynamic_pointer_cast<LM::Frontend::AST::ListPatternExpr>(pattern_node)) {
        if (match_type->tag == TypeTag::List) {
            auto* listType = std::get_if<ListType>(&match_type->extra);
            if (listType) {
                for (auto& elementPattern : listPattern->elements) {
                    validate_pattern_compatibility(elementPattern, listType->elementType, line);
                }
                if (listPattern->restElement.has_value()) {
                    declare_variable(listPattern->restElement.value(), match_type);
                }
            }
        } else if (match_type->tag == TypeTag::Any) {
            for (auto& elementPattern : listPattern->elements) {
                validate_pattern_compatibility(elementPattern, type_system.ANY_TYPE, line);
            }
            if (listPattern->restElement.has_value()) {
                declare_variable(listPattern->restElement.value(), type_system.ANY_TYPE);
            }
        } else {
            add_error("List pattern cannot match non-list type " + match_type->toString(), line);
        }
    } else if (auto tuplePattern = std::dynamic_pointer_cast<LM::Frontend::AST::TuplePatternExpr>(pattern_node)) {
        if (match_type->tag == TypeTag::Tuple) {
            auto* tupleType = std::get_if<TupleType>(&match_type->extra);
            if (tupleType) {
                if (tuplePattern->elements.size() != tupleType->elementTypes.size()) {
                    add_error("Tuple pattern has " + std::to_string(tuplePattern->elements.size()) + 
                              " elements, but expected " + std::to_string(tupleType->elementTypes.size()), line);
                } else {
                    for (size_t i = 0; i < tuplePattern->elements.size(); ++i) {
                        validate_pattern_compatibility(tuplePattern->elements[i], tupleType->elementTypes[i], line);
                    }
                }
            }
        } else if (match_type->tag == TypeTag::Any) {
            for (auto& elementPattern : tuplePattern->elements) {
                validate_pattern_compatibility(elementPattern, type_system.ANY_TYPE, line);
            }
        } else {
            add_error("Tuple pattern cannot match non-tuple type " + match_type->toString(), line);
        }
    } else if (auto dictPattern = std::dynamic_pointer_cast<LM::Frontend::AST::DictPatternExpr>(pattern_node)) {
        if (match_type->tag == TypeTag::Structural) {
            auto* structType = std::get_if<StructuralType>(&match_type->extra);
            if (structType) {
                for (auto& field : dictPattern->fields) {
                    bool found = false;
                    for (auto& structField : structType->fields) {
                        if (structField.first == field.key) {
                            validate_pattern_compatibility(field.pattern, structField.second, line);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        // For structural patterns, we can be more lenient or strict.
                        // Here we just match what we can.
                        validate_pattern_compatibility(field.pattern, type_system.ANY_TYPE, line);
                    }
                }
            }
        } else if (match_type->tag == TypeTag::Dict) {
             auto* dictType = std::get_if<DictType>(&match_type->extra);
             if (dictType) {
                 for (auto& field : dictPattern->fields) {
                     validate_pattern_compatibility(field.pattern, dictType->valueType, line);
                 }
             }
        } else if (match_type->tag == TypeTag::Any) {
            for (auto& field : dictPattern->fields) {
                validate_pattern_compatibility(field.pattern, type_system.ANY_TYPE, line);
            }
            if (dictPattern->restBinding.has_value()) {
                declare_variable(dictPattern->restBinding.value(), type_system.ANY_TYPE);
            }
        } else {
            // For general objects being matched against dictionary patterns
            for (auto& field : dictPattern->fields) {
                validate_pattern_compatibility(field.pattern, type_system.ANY_TYPE, line);
            }
        }
    } else if (auto memberExpr = std::dynamic_pointer_cast<LM::Frontend::AST::MemberExpr>(pattern_node)) {
        TypePtr patternType = check_member_expr(memberExpr);
        if (patternType && !is_type_compatible(patternType, match_type)) {
            // add_error("Pattern " + patternType->toString() + " does not match match type " + match_type->toString(), line);
        }
    } else if (auto varExpr = std::dynamic_pointer_cast<LM::Frontend::AST::VariableExpr>(pattern_node)) {
        if (varExpr->name == "_") return;
        declare_variable(varExpr->name, match_type);
    } else if (auto typePattern = std::dynamic_pointer_cast<LM::Frontend::AST::TypePatternExpr>(pattern_node)) {
        if (typePattern->type) {
            TypePtr patternType = resolve_type_annotation(typePattern->type);
            if (patternType && !is_type_compatible(patternType, match_type)) {
                add_error("Type pattern type " + patternType->toString() + " does not match match type " + match_type->toString(), line);
            }
        }
    } else if (auto literalPattern = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(pattern_node)) {
        if (std::holds_alternative<std::nullptr_t>(literalPattern->value)) return;
        TypePtr literalType = check_literal_expr(literalPattern);
        if (literalType && !is_type_compatible(literalType, match_type)) {
            // add_error("Literal pattern type " + literalType->toString() + " does not match match type " + match_type->toString(), line);
        }
    }
}

TypePtr TypeChecker::infer_lambda_return_type(const std::shared_ptr<LM::Frontend::AST::Statement>& body) {
    if (!body) return type_system.NIL_TYPE;
    if (auto blockStmt = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(body)) {
        std::vector<TypePtr> returnTypes;
        for (const auto& stmt : blockStmt->statements) {
            if (auto returnStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ReturnStatement>(stmt)) {
                if (returnStmt->value) returnTypes.push_back(check_expression(returnStmt->value));
                else returnTypes.push_back(type_system.NIL_TYPE);
            }
        }
        if (!returnTypes.empty()) {
            TypePtr commonType = returnTypes[0];
            for (size_t i = 1; i < returnTypes.size(); ++i) {
                try { commonType = get_common_type(commonType, returnTypes[i]); }
                catch (const std::exception&) { return type_system.ANY_TYPE; }
            }
            return commonType;
        }
        return type_system.NIL_TYPE;
    }
    if (auto exprStmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(body)) return check_expression(exprStmt->expression);
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::infer_literal_type(const std::shared_ptr<LM::Frontend::AST::LiteralExpr>& expr, TypePtr expected_type) {
    if (!expr) return nullptr;
    if (std::holds_alternative<std::string>(expr->value)) {
        std::string stringValue = std::get<std::string>(expr->value);
        bool isNumeric = false, isFloat = false;
        if (!stringValue.empty()) {
            char first = stringValue[0];
            if (std::isdigit(first) || first == '+' || first == '-' || first == '.') {
                isNumeric = true;
                if (stringValue.find('.') != std::string::npos || stringValue.find('e') != std::string::npos || stringValue.find('E') != std::string::npos) isFloat = true;
            }
        }
        if (expected_type && (expected_type->tag == TypeTag::Int || expected_type->tag == TypeTag::Int8 || expected_type->tag == TypeTag::Int16 || expected_type->tag == TypeTag::Int32 || expected_type->tag == TypeTag::Int64 || expected_type->tag == TypeTag::Int128 || expected_type->tag == TypeTag::UInt || expected_type->tag == TypeTag::UInt8 || expected_type->tag == TypeTag::UInt16 || expected_type->tag == TypeTag::UInt32 || expected_type->tag == TypeTag::UInt64 || expected_type->tag == TypeTag::UInt128 || expected_type->tag == TypeTag::Float32 || expected_type->tag == TypeTag::Float64)) return expected_type;
        if (isNumeric) {
            if (isFloat) {
                try {
                    double floatVal = std::stod(stringValue);
                    if (std::abs(floatVal) <= std::numeric_limits<float>::max()) {
                        float floatVal32 = static_cast<float>(floatVal);
                        if (static_cast<double>(floatVal32) == floatVal) return type_system.FLOAT32_TYPE;
                    }
                    return type_system.FLOAT64_TYPE;
                } catch (const std::exception&) { return type_system.NIL_TYPE; }
            } else {
                try {
                    int64_t intVal = std::stoll(stringValue);
                    if (intVal >= std::numeric_limits<int8_t>::min() && intVal <= std::numeric_limits<int8_t>::max()) return type_system.INT8_TYPE;
                    else if (intVal >= std::numeric_limits<int16_t>::min() && intVal <= std::numeric_limits<int16_t>::max()) return type_system.INT16_TYPE;
                    else if (intVal >= std::numeric_limits<int32_t>::min() && intVal <= std::numeric_limits<int32_t>::max()) return type_system.INT32_TYPE;
                    else return type_system.INT64_TYPE;
                } catch (const std::exception&) { return type_system.INT128_TYPE; }
            }
        } else return type_system.STRING_TYPE;
    } else if (std::holds_alternative<bool>(expr->value)) return type_system.BOOL_TYPE;
    else if (std::holds_alternative<std::nullptr_t>(expr->value)) return type_system.NIL_TYPE;
    return type_system.NIL_TYPE;
}

} // namespace Frontend
} // namespace LM

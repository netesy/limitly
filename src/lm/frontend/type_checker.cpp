#include "type_checker.hh"
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include <cmath>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include <sstream>

namespace LM {
namespace Frontend {


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
    
    // PASS 1: Name Registration (Frames, Traits)
    for (const auto& stmt : program->statements) {
        if (auto frame_decl = std::dynamic_pointer_cast<AST::FrameDeclaration>(stmt)) {
            type_system.registerFrame(frame_decl->name, {});
        } else if (auto trait_decl = std::dynamic_pointer_cast<AST::TraitDeclaration>(stmt)) {
            type_system.registerTrait(trait_decl->name, {});
        }
    }

    // PASS 2: Signature Resolution
    for (const auto& stmt : program->statements) {
        if (auto frame_decl = std::dynamic_pointer_cast<AST::FrameDeclaration>(stmt)) {
            LM::Backend::FrameInfo info;
            info.name = frame_decl->name;
            info.declaration = frame_decl;
            info.implements = frame_decl->implements;
            info.hasInit = (frame_decl->init != nullptr);
            info.hasDeinit = (frame_decl->deinit != nullptr);

            size_t offset = 0;
            for (const auto& field : frame_decl->fields) {
                TypePtr field_type = field->type ? resolve_type_annotation(field->type) : type_system.ANY_TYPE;
                info.fields.push_back({field->name, field_type});
                info.fieldVisibilities[field->name] = field->visibility;
                info.fieldOffsets[field->name] = offset++;
            }
            info.totalFieldSize = offset;

            if (frame_decl->init) {
                std::string init_name = frame_decl->name + ".init";
                FunctionSignature sig;
                sig.name = init_name;
                sig.return_type = type_system.NIL_TYPE;
                sig.param_types.push_back(type_system.createFrameType(frame_decl->name));
                for (const auto& p : frame_decl->init->parameters) sig.param_types.push_back(resolve_type_annotation(p.second));
                function_signatures[init_name] = sig;
            }
            for (const auto& m : frame_decl->methods) {
                std::string m_name = frame_decl->name + "." + m->name;
                FunctionSignature sig;
                sig.name = m_name;
                sig.return_type = m->returnType ? resolve_type_annotation(m->returnType.value()) : type_system.NIL_TYPE;
                sig.param_types.push_back(type_system.createFrameType(frame_decl->name));
                for (const auto& p : m->parameters) sig.param_types.push_back(resolve_type_annotation(p.second));
                function_signatures[m_name] = sig;
                info.methodSignatures[m->name] = sig.return_type;
            }
            if (frame_decl->deinit) {
                std::string deinit_name = frame_decl->name + ".deinit";
                FunctionSignature sig;
                sig.name = deinit_name;
                sig.return_type = type_system.NIL_TYPE;
                sig.param_types.push_back(type_system.createFrameType(frame_decl->name));
                function_signatures[deinit_name] = sig;
            }

            type_system.registerFrame(frame_decl->name, info);

            FrameInfo local_info;
            local_info.name = info.name;
            local_info.declaration = frame_decl;
            local_info.fields = info.fields;
            for(const auto& field : frame_decl->fields) {
                local_info.field_has_default.push_back({field->name, field->defaultValue != nullptr});
            }
            frame_declarations[frame_decl->name] = local_info;

        } else if (auto trait_decl = std::dynamic_pointer_cast<AST::TraitDeclaration>(stmt)) {
            LM::Backend::TraitInfo info;
            info.name = trait_decl->name;
            info.declaration = trait_decl;
            info.extends = trait_decl->extends;
            for (const auto& m : trait_decl->methods) {
                std::string m_name = trait_decl->name + "." + m->name;
                FunctionSignature sig;
                sig.name = m_name;
                sig.return_type = m->returnType ? resolve_type_annotation(m->returnType.value()) : type_system.NIL_TYPE;
                sig.param_types.push_back(type_system.ANY_TYPE);
                for (const auto& p : m->params) sig.param_types.push_back(resolve_type_annotation(p.second));
                function_signatures[m_name] = sig;
                info.methodSignatures[m->name] = sig.return_type;
            }
            type_system.registerTrait(trait_decl->name, info);

            TraitInfo local_trait;
            local_trait.name = trait_decl->name;
            local_trait.extends = trait_decl->extends;
            local_trait.declaration = trait_decl;
            trait_declarations[trait_decl->name] = local_trait;

        } else if (auto func_decl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
            FunctionSignature sig;
            sig.name = func_decl->name;
            sig.return_type = func_decl->returnType ? resolve_type_annotation(func_decl->returnType.value()) : type_system.STRING_TYPE;
            sig.declaration = func_decl;
            sig.can_fail = func_decl->canFail || func_decl->throws;
            sig.error_types = func_decl->declaredErrorTypes;
            for (const auto& p : func_decl->params) {
                sig.param_types.push_back(resolve_type_annotation(p.second));
                sig.optional_params.push_back(false);
            }
            for (const auto& op : func_decl->optionalParams) {
                sig.param_types.push_back(resolve_type_annotation(op.second.first));
                sig.optional_params.push_back(true);
            }
            function_signatures[func_decl->name] = sig;
            declare_variable(func_decl->name, type_system.FUNCTION_TYPE);
        } else if (auto type_decl = std::dynamic_pointer_cast<AST::TypeDeclaration>(stmt)) {
            check_type_declaration(type_decl);
        }
    }

    // PASS 3: Body Verification
    for (const auto& stmt : program->statements) {
        check_statement(stmt);
    }
    
    program->inferred_type = type_system.NIL_TYPE;
    
    return errors.empty();
}

void TypeChecker::add_error(const std::string& message, int line) {
    std::string err = "[Semantic Error] Line " + std::to_string(line) + ": " + message;
    errors.push_back(err);
}

void TypeChecker::add_error(const std::string& message, int line, int column, const std::string& context, 
                         const std::string& lexeme, const std::string& expected_value) {
    std::string enhancedMessage = message;
    if (!lexeme.empty()) enhancedMessage += " (at '" + lexeme + "')";
    if (!expected_value.empty()) enhancedMessage += " - expected: " + expected_value;
    add_error(enhancedMessage, line);
}

void TypeChecker::add_type_error(const std::string& expected, const std::string& found, int line) {
    add_error("Type mismatch: expected " + expected + ", found " + found, line);
}

std::string TypeChecker::get_code_context(int line) {
    return "";
}

void TypeChecker::check_assert_call(const std::shared_ptr<AST::CallExpr>& expr) {
    if (expr->arguments.size() < 1 || expr->arguments.size() > 2) {
        add_error("assert() expects 1 or 2 arguments", expr->line);
        return;
    }
    
    TypePtr conditionType = check_expression(expr->arguments[0]);
    if (!is_boolean_type(conditionType) && conditionType->tag != TypeTag::Any) {
        add_error("assert() first argument must be boolean", expr->line);
    }
    
    if (expr->arguments.size() == 2) {
        TypePtr messageType = check_expression(expr->arguments[1]);
        if (!is_string_type(messageType) && messageType->tag != TypeTag::Any) {
            add_error("assert() second argument must be string", expr->line);
        }
    }
}

void TypeChecker::check_linear_type_access(const std::string& var_name, int line) {}
void TypeChecker::create_reference(const std::string& linear_var, const std::string& ref_var, int line, bool is_mutable) {}
void TypeChecker::move_linear_type(const std::string& var_name, int line) {}
void TypeChecker::check_reference_validity(const std::string& ref_name, int line) {}
void TypeChecker::check_mutable_aliasing(const std::string& linear_var, const std::string& ref_var, bool is_mutable, int line) {}
void TypeChecker::check_scope_escape(const std::string& ref_name, int target_scope, int line) {}

void TypeChecker::enter_scope() {
    current_scope_level++;
    current_scope = std::make_unique<Scope>(std::move(current_scope));
}

void TypeChecker::exit_scope() {
    current_scope_level--;
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

// Memory Safety (Placeholders)
void TypeChecker::enter_memory_region() { current_region_id++; }
void TypeChecker::exit_memory_region() {}
void TypeChecker::declare_variable_memory(const std::string& name, TypePtr type) {}
void TypeChecker::check_variable_use(const std::string& name, int line) {}
void TypeChecker::check_variable_move(const std::string& name) {}
void TypeChecker::check_variable_drop(const std::string& name) {}
void TypeChecker::mark_variable_initialized(const std::string& name) {}
void TypeChecker::mark_variable_moved(const std::string& name) {}
void TypeChecker::mark_variable_dropped(const std::string& name) {}
void TypeChecker::check_borrow_safety(const std::string& var_name) {}
void TypeChecker::check_escape_analysis(const std::string& var_name, const std::string& target_context) {}
void TypeChecker::check_memory_leaks(int line) {}
void TypeChecker::check_use_after_free(const std::string& name, int line) {}
void TypeChecker::check_dangling_pointer(const std::string& name, int line) {}
void TypeChecker::check_double_free(const std::string& name, int line) {}
void TypeChecker::check_multiple_owners(const std::string& name, int line) {}
void TypeChecker::check_buffer_overflow(const std::string& array_name, const std::string& index_expr, int line) {}
void TypeChecker::check_uninitialized_use(const std::string& name, int line) {}
void TypeChecker::check_invalid_type(const std::string& var_name, TypePtr expected_type, TypePtr actual_type, int line) {}
void TypeChecker::check_misalignment(const std::string& ptr_name, int line) {}
void TypeChecker::check_heap_corruption(const std::string& operation, int line) {}
void TypeChecker::check_race_condition(const std::string& shared_var, int line) {}
bool TypeChecker::is_variable_alive(const std::string& name) { return lookup_variable(name) != nullptr; }

bool TypeChecker::is_visible(const std::string& frame_name, AST::VisibilityLevel visibility, int line) {
    if (visibility == AST::VisibilityLevel::Public || visibility == AST::VisibilityLevel::Const) return true;
    if (!current_frame) return false;
    if (current_frame->name == frame_name) return true;
    return false;
}

TypePtr TypeChecker::check_statement(std::shared_ptr<AST::Statement> stmt) {
    if (!stmt) return nullptr;
    
    if (auto func_decl = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
        return check_function_declaration(func_decl);
    } else if (auto frame_decl = std::dynamic_pointer_cast<AST::FrameDeclaration>(stmt)) {
        return check_frame_declaration(frame_decl);
    } else if (auto trait_decl = std::dynamic_pointer_cast<AST::TraitDeclaration>(stmt)) {
        return check_trait_declaration(trait_decl);
    } else if (auto var_decl = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
        return check_var_declaration(var_decl);
    } else if (auto block = std::dynamic_pointer_cast<AST::BlockStatement>(stmt)) {
        return check_block_statement(block);
    } else if (auto if_stmt = std::dynamic_pointer_cast<AST::IfStatement>(stmt)) {
        return check_if_statement(if_stmt);
    } else if (auto while_stmt = std::dynamic_pointer_cast<AST::WhileStatement>(stmt)) {
        return check_while_statement(while_stmt);
    } else if (auto return_stmt = std::dynamic_pointer_cast<AST::ReturnStatement>(stmt)) {
        return check_return_statement(return_stmt);
    } else if (auto expr_stmt = std::dynamic_pointer_cast<AST::ExprStatement>(stmt)) {
        return check_expression(expr_stmt->expression);
    }
    
    return nullptr;
}

TypePtr TypeChecker::check_function_declaration(std::shared_ptr<AST::FunctionDeclaration> func) {
    if (!func) return nullptr;
    
    TypePtr return_type = type_system.NIL_TYPE;
    if (func->returnType) {
        return_type = resolve_type_annotation(func->returnType.value());
    }
    
    std::vector<TypePtr> param_types;
    for (const auto& param : func->params) {
        param_types.push_back(resolve_type_annotation(param.second));
    }
    
    current_function = func;
    current_return_type = return_type;
    enter_scope();
    
    for (size_t i = 0; i < func->params.size(); ++i) {
        declare_variable(func->params[i].first, param_types[i]);
    }
    
    if (func->body) check_statement(func->body);
    
    exit_scope();
    current_function = nullptr;
    current_return_type = nullptr;
    
    func->inferred_type = return_type;
    return return_type;
}

TypePtr TypeChecker::check_var_declaration(std::shared_ptr<AST::VarDeclaration> var_decl) {
    TypePtr declared_type = var_decl->type ? resolve_type_annotation(var_decl->type.value()) : nullptr;
    TypePtr init_type = var_decl->initializer ? check_expression(var_decl->initializer) : nullptr;
    
    TypePtr final_type = declared_type ? declared_type : (init_type ? init_type : type_system.ANY_TYPE);
    
    if (declared_type && init_type && !is_type_compatible(init_type, declared_type)) {
        add_type_error(declared_type->toString(), init_type->toString(), var_decl->line);
    }
    
    declare_variable(var_decl->name, final_type);
    var_decl->inferred_type = final_type;
    return final_type;
}

TypePtr TypeChecker::check_type_declaration(std::shared_ptr<AST::TypeDeclaration> type_decl) {
    TypePtr underlying = resolve_type_annotation(type_decl->type);
    type_system.registerTypeAlias(type_decl->name, underlying);
    type_decl->inferred_type = underlying;
    return underlying;
}

TypePtr TypeChecker::check_frame_declaration(std::shared_ptr<AST::FrameDeclaration> frame) {
    if (!frame) return nullptr;
    auto prev_frame = current_frame;
    current_frame = frame;

    // Check trait implementations recursively
    std::vector<std::string> trait_worklist = frame->implements;
    std::unordered_set<std::string> visited_traits;

    while (!trait_worklist.empty()) {
        std::string trait_name = trait_worklist.back();
        trait_worklist.pop_back();
        if (visited_traits.count(trait_name)) continue;
        visited_traits.insert(trait_name);

        auto it = trait_declarations.find(trait_name);
        if (it == trait_declarations.end()) {
            add_error("Frame '" + frame->name + "' implements unknown trait: " + trait_name, frame->line);
            continue;
        }

        for (const auto& tm : it->second.declaration->methods) {
            bool implemented = false;
            for (const auto& fm : frame->methods) {
                if (fm->name == tm->name) { implemented = true; break; }
            }
            if (!implemented && (!tm->body || tm->body->statements.empty())) {
                add_error("Frame '" + frame->name + "' does not implement required trait method: " + tm->name, frame->line);
            }
        }
        for (const auto& parent : it->second.extends) trait_worklist.push_back(parent);
    }

    // Check fields
    for (const auto& field : frame->fields) {
        TypePtr field_type = field->type ? resolve_type_annotation(field->type) : type_system.ANY_TYPE;
        if (field->defaultValue) {
            TypePtr def_type = check_expression(field->defaultValue);
            if (!is_type_compatible(def_type, field_type)) add_type_error(field_type->toString(), def_type->toString(), frame->line);
        }
    }

    // Check methods
    if (frame->init) {
        enter_scope();
        declare_variable("this", type_system.createFrameType(frame->name));
        for (const auto& p : frame->init->parameters) declare_variable(p.first, resolve_type_annotation(p.second));
        if (frame->init->body) check_statement(frame->init->body);
        exit_scope();
    }
    for (const auto& method : frame->methods) {
        enter_scope();
        declare_variable("this", type_system.createFrameType(frame->name));
        for (const auto& p : method->parameters) declare_variable(p.first, resolve_type_annotation(p.second));
        if (method->body) check_statement(method->body);
        exit_scope();
    }

    current_frame = prev_frame;
    TypePtr frame_type = type_system.createFrameType(frame->name);
    frame->inferred_type = frame_type;
    return frame_type;
}

TypePtr TypeChecker::check_trait_declaration(std::shared_ptr<AST::TraitDeclaration> trait) {
    TypePtr trait_type = std::make_shared<LM::Backend::Type>(TypeTag::Trait);
    trait->inferred_type = trait_type;
    return trait_type;
}

TypePtr TypeChecker::check_block_statement(std::shared_ptr<AST::BlockStatement> block) {
    enter_scope();
    TypePtr last = type_system.NIL_TYPE;
    for (const auto& stmt : block->statements) last = check_statement(stmt);
    exit_scope();
    block->inferred_type = last;
    return last;
}

TypePtr TypeChecker::check_if_statement(std::shared_ptr<AST::IfStatement> if_stmt) {
    TypePtr cond = check_expression(if_stmt->condition);
    if (!is_boolean_type(cond)) add_type_error("bool", cond->toString(), if_stmt->line);
    check_statement(if_stmt->thenBranch);
    if (if_stmt->elseBranch) check_statement(if_stmt->elseBranch);
    if_stmt->inferred_type = type_system.NIL_TYPE;
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::check_while_statement(std::shared_ptr<AST::WhileStatement> while_stmt) {
    TypePtr cond = check_expression(while_stmt->condition);
    if (!is_boolean_type(cond)) add_type_error("bool", cond->toString(), while_stmt->line);
    check_statement(while_stmt->body);
    while_stmt->inferred_type = type_system.NIL_TYPE;
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::check_parallel_statement(std::shared_ptr<AST::ParallelStatement> s) { check_statement(s->body); return type_system.NIL_TYPE; }
TypePtr TypeChecker::check_concurrent_statement(std::shared_ptr<AST::ConcurrentStatement> s) { check_statement(s->body); return type_system.NIL_TYPE; }
TypePtr TypeChecker::check_task_statement(std::shared_ptr<AST::TaskStatement> s) { check_statement(s->body); return type_system.NIL_TYPE; }
TypePtr TypeChecker::check_worker_statement(std::shared_ptr<AST::WorkerStatement> s) { check_statement(s->body); return type_system.NIL_TYPE; }

TypePtr TypeChecker::check_return_statement(std::shared_ptr<AST::ReturnStatement> return_stmt) {
    TypePtr val_type = return_stmt->value ? check_expression(return_stmt->value) : type_system.NIL_TYPE;
    if (current_return_type && !is_type_compatible(val_type, current_return_type)) {
        add_type_error(current_return_type->toString(), val_type->toString(), return_stmt->line);
    }
    return_stmt->inferred_type = val_type;
    return val_type;
}

TypePtr TypeChecker::check_print_statement(std::shared_ptr<AST::PrintStatement> print_stmt) {
    for (const auto& arg : print_stmt->arguments) check_expression(arg);
    return type_system.NIL_TYPE;
}

TypePtr TypeChecker::check_expression(std::shared_ptr<AST::Expression> expr) {
    if (!expr) return nullptr;
    TypePtr t = type_system.ANY_TYPE;
    
    if (auto lit = std::dynamic_pointer_cast<AST::LiteralExpr>(expr)) t = check_literal_expr(lit);
    else if (auto var = std::dynamic_pointer_cast<AST::VariableExpr>(expr)) t = check_variable_expr(var);
    else if (auto bin = std::dynamic_pointer_cast<AST::BinaryExpr>(expr)) t = check_binary_expr(bin);
    else if (auto call = std::dynamic_pointer_cast<AST::CallExpr>(expr)) t = check_call_expr(call);
    else if (auto assign = std::dynamic_pointer_cast<AST::AssignExpr>(expr)) t = check_assign_expr(assign);
    else if (auto mem = std::dynamic_pointer_cast<AST::MemberExpr>(expr)) t = check_member_expr(mem);
    else if (auto inst = std::dynamic_pointer_cast<AST::FrameInstantiationExpr>(expr)) t = check_frame_instantiation_expr(inst);
    else if (auto this_expr = std::dynamic_pointer_cast<AST::ThisExpr>(expr)) t = current_frame ? type_system.createFrameType(current_frame->name) : type_system.ANY_TYPE;
    else if (auto unary = std::dynamic_pointer_cast<AST::UnaryExpr>(expr)) t = check_unary_expr(unary);
    else if (auto grouping = std::dynamic_pointer_cast<AST::GroupingExpr>(expr)) t = check_grouping_expr(grouping);
    else if (auto list = std::dynamic_pointer_cast<AST::ListExpr>(expr)) t = check_list_expr(list);
    else if (auto dict = std::dynamic_pointer_cast<AST::DictExpr>(expr)) t = check_dict_expr(dict);
    else if (auto match = std::dynamic_pointer_cast<AST::MatchStatement>(expr)) t = check_match_statement(match);

    expr->inferred_type = t;
    return t;
}

TypePtr TypeChecker::check_literal_expr(std::shared_ptr<AST::LiteralExpr> expr) {
    if (std::holds_alternative<bool>(expr->value)) return type_system.BOOL_TYPE;
    if (std::holds_alternative<std::nullptr_t>(expr->value)) return type_system.NIL_TYPE;
    if (expr->literalType == TokenType::INT_LITERAL) return type_system.INT64_TYPE;
    if (expr->literalType == TokenType::FLOAT_LITERAL) return type_system.FLOAT64_TYPE;
    return type_system.STRING_TYPE;
}

TypePtr TypeChecker::check_literal_expr_with_expected_type(std::shared_ptr<AST::LiteralExpr> expr, TypePtr expected) {
    return check_literal_expr(expr);
}

TypePtr TypeChecker::check_variable_expr(std::shared_ptr<AST::VariableExpr> expr) {
    TypePtr t = lookup_variable(expr->name);
    if (!t) add_error("Undefined variable: " + expr->name, expr->line);
    return t ? t : type_system.ANY_TYPE;
}

TypePtr TypeChecker::check_binary_expr(std::shared_ptr<AST::BinaryExpr> expr) {
    TypePtr l = check_expression(expr->left);
    TypePtr r = check_expression(expr->right);
    return type_system.getCommonType(l, r);
}

TypePtr TypeChecker::check_call_expr(std::shared_ptr<AST::CallExpr> expr) {
    std::vector<TypePtr> arg_types;
    for (const auto& arg : expr->arguments) arg_types.push_back(check_expression(arg));

    if (auto var = std::dynamic_pointer_cast<AST::VariableExpr>(expr->callee)) {
        if (var->name == "assert") { check_assert_call(expr); return type_system.NIL_TYPE; }
        
        auto frame_it = frame_declarations.find(var->name);
        if (frame_it != frame_declarations.end()) {
             // Handle shorthand frame instantiation as call
             std::string init_name = var->name + ".init";
             auto it = function_signatures.find(init_name);
             if (it != function_signatures.end()) {
                 std::vector<TypePtr> expected = it->second.param_types;
                 if (!expected.empty()) expected.erase(expected.begin()); // remove 'this'
                 validate_argument_types(expected, arg_types, init_name);
             }
             return type_system.createFrameType(var->name);
        }

        auto it = function_signatures.find(var->name);
        if (it != function_signatures.end()) return it->second.return_type;
    }
    if (auto mem = std::dynamic_pointer_cast<AST::MemberExpr>(expr->callee)) {
        TypePtr obj_type = check_expression(mem->object);
        if (obj_type && obj_type->tag == TypeTag::Frame) {
            auto ft = std::get_if<LM::Backend::FrameType>(&obj_type->extra);
            if (ft) {
                std::string full_name = ft->name + "." + mem->name;
                auto it = function_signatures.find(full_name);
                if (it != function_signatures.end()) return it->second.return_type;

                // Static dispatch trait methods fallback
                auto frame_info = type_system.getFrameInfo(ft->name);
                if (frame_info) {
                    for (const auto& trait_name : frame_info->implements) {
                        std::string trait_m_name = trait_name + "." + mem->name;
                        auto tit = function_signatures.find(trait_m_name);
                        if (tit != function_signatures.end()) return tit->second.return_type;
                    }
                }
            }
        }
    }
    return type_system.ANY_TYPE;
}

TypePtr TypeChecker::check_assign_expr(std::shared_ptr<AST::AssignExpr> expr) {
    TypePtr val = check_expression(expr->value);
    if (expr->object && expr->member) {
         TypePtr obj_type = check_expression(expr->object);
         if (obj_type && obj_type->tag == TypeTag::Frame) {
             auto ft = std::get_if<LM::Backend::FrameType>(&obj_type->extra);
             auto frame_info = type_system.getFrameInfo(ft->name);
             if (frame_info) {
                 for (const auto& field : frame_info->fields) {
                     if (field.first == *expr->member) {
                         if (!is_type_compatible(val, field.second)) add_type_error(field.second->toString(), val->toString(), expr->line);
                         return val;
                     }
                 }
             }
         }
    }
    TypePtr target = lookup_variable(expr->name);
    if (target && !is_type_compatible(val, target)) add_type_error(target->toString(), val->toString(), expr->line);
    return val;
}

TypePtr TypeChecker::check_member_expr(std::shared_ptr<AST::MemberExpr> expr) {
    TypePtr obj_type = check_expression(expr->object);
    if (obj_type && obj_type->tag == TypeTag::Frame) {
        auto ft = std::get_if<LM::Backend::FrameType>(&obj_type->extra);
        auto frame_info = type_system.getFrameInfo(ft->name);
        if (frame_info) {
            for (const auto& field : frame_info->fields) {
                if (field.first == expr->name) return field.second;
            }
        }
    }
    return type_system.ANY_TYPE;
}

TypePtr TypeChecker::check_frame_instantiation_expr(std::shared_ptr<AST::FrameInstantiationExpr> expr) {
    auto frame_it = frame_declarations.find(expr->frameName);
    if (frame_it == frame_declarations.end()) {
        add_error("Unknown frame type: " + expr->frameName, expr->line);
        return type_system.ANY_TYPE;
    }
    return type_system.createFrameType(expr->frameName);
}

TypePtr TypeChecker::resolve_type_annotation(std::shared_ptr<AST::TypeAnnotation> ann) {
    if (!ann) return type_system.ANY_TYPE;
    TypePtr t = type_system.getType(ann->typeName);
    if (!t) t = type_system.ANY_TYPE;
    if (ann->isOptional) return type_system.createFallibleType(t);
    return t;
}

bool TypeChecker::is_type_compatible(TypePtr actual, TypePtr expected) {
    return type_system.isCompatible(actual, expected);
}

bool TypeChecker::is_boolean_type(TypePtr t) { return t && t->tag == TypeTag::Bool; }
bool is_string_type(TypePtr t) { return t && t->tag == TypeTag::String; }

// Robust implementation of validation methods
bool TypeChecker::check_function_call(const std::string& name, const std::vector<TypePtr>& actual, TypePtr& result) {
    auto it = function_signatures.find(name);
    if (it == function_signatures.end()) return false;
    result = it->second.return_type;
    return validate_argument_types(it->second.param_types, actual, name);
}

bool TypeChecker::validate_argument_types(const std::vector<TypePtr>& expected, const std::vector<TypePtr>& actual, const std::string& name) {
    if (actual.size() < expected.size()) {
        add_error("Too few arguments to function '" + name + "'", 0);
        return false;
    }
    for (size_t i = 0; i < expected.size(); ++i) {
        if (!is_type_compatible(actual[i], expected[i])) {
            add_type_error(expected[i]->toString(), actual[i]->toString(), 0);
        }
    }
    return true;
}

// Remaining placeholders
TypePtr TypeChecker::check_expression_with_expected_type(std::shared_ptr<AST::Expression> e, TypePtr t) { return check_expression(e); }
TypePtr TypeChecker::check_unary_expr(std::shared_ptr<AST::UnaryExpr> e) { return check_expression(e->right); }
TypePtr TypeChecker::check_grouping_expr(std::shared_ptr<AST::GroupingExpr> e) { return check_expression(e->expression); }
TypePtr TypeChecker::check_index_expr(std::shared_ptr<AST::IndexExpr> e) { return type_system.ANY_TYPE; }
TypePtr TypeChecker::check_list_expr(std::shared_ptr<AST::ListExpr> e) { return type_system.createTypedListType(type_system.ANY_TYPE); }
TypePtr TypeChecker::check_tuple_expr(std::shared_ptr<AST::TupleExpr> e) { return type_system.ANY_TYPE; }
TypePtr TypeChecker::check_dict_expr(std::shared_ptr<AST::DictExpr> e) { return type_system.ANY_TYPE; }
TypePtr TypeChecker::check_interpolated_string_expr(std::shared_ptr<AST::InterpolatedStringExpr> e) { return type_system.STRING_TYPE; }
TypePtr TypeChecker::check_lambda_expr(std::shared_ptr<AST::LambdaExpr> e) { return type_system.FUNCTION_TYPE; }
TypePtr TypeChecker::check_error_construct_expr(std::shared_ptr<AST::ErrorConstructExpr> e) { return type_system.ANY_TYPE; }
TypePtr TypeChecker::check_ok_construct_expr(std::shared_ptr<AST::OkConstructExpr> e) { return type_system.ANY_TYPE; }
TypePtr TypeChecker::check_fallible_expr(std::shared_ptr<AST::FallibleExpr> e) { return type_system.ANY_TYPE; }
TypePtr TypeChecker::check_contract_statement(std::shared_ptr<AST::ContractStatement> s) { return type_system.NIL_TYPE; }
TypePtr TypeChecker::check_match_statement(std::shared_ptr<AST::MatchStatement> s) { return type_system.ANY_TYPE; }
void TypeChecker::check_return_statement(TypePtr t, int l) {}
void TypeChecker::check_break_statement(int l) {}
void TypeChecker::check_continue_statement(int l) {}
bool TypeChecker::is_integer_type(TypePtr t) { return t && (t->tag == TypeTag::Int || t->tag == TypeTag::Int64); }
bool TypeChecker::is_float_type(TypePtr t) { return t && t->tag == TypeTag::Float64; }
bool TypeChecker::is_numeric_type(TypePtr t) { return is_integer_type(t) || is_float_type(t); }
bool TypeChecker::is_optional_type(TypePtr t) { return t && t->tag == TypeTag::ErrorUnion; }
bool TypeChecker::is_error_union_type(TypePtr t) { return t && t->tag == TypeTag::ErrorUnion; }
bool TypeChecker::is_union_type(TypePtr t) { return t && t->tag == TypeTag::Union; }
bool TypeChecker::requires_error_handling(TypePtr t) { return false; }
TypePtr TypeChecker::promote_numeric_types(TypePtr l, TypePtr r) { return type_system.getCommonType(l, r); }
void TypeChecker::validate_function_error_types(const std::shared_ptr<AST::FunctionDeclaration>& s) {}
void TypeChecker::validate_function_body_error_types(const std::shared_ptr<AST::FunctionDeclaration>& s) {}
std::vector<std::string> TypeChecker::infer_function_error_types(const std::shared_ptr<AST::Statement>& b) { return {}; }
std::vector<std::string> TypeChecker::infer_expression_error_types(const std::shared_ptr<AST::Expression>& e) { return {}; }
bool TypeChecker::can_function_produce_error_type(const std::shared_ptr<AST::Statement>& b, const std::string& e) { return false; }
bool TypeChecker::can_propagate_error(const std::vector<std::string>& s, const std::vector<std::string>& t) { return true; }
bool TypeChecker::is_error_union_compatible(TypePtr f, TypePtr t) { return true; }
std::string TypeChecker::join_error_types(const std::vector<std::string>& e) { return ""; }
bool TypeChecker::is_exhaustive_error_match(const std::vector<std::shared_ptr<AST::MatchCase>>& c, TypePtr t) { return true; }
bool TypeChecker::is_exhaustive_union_match(TypePtr u, const std::vector<std::shared_ptr<AST::MatchCase>>& c) { return true; }
bool TypeChecker::is_exhaustive_option_match(const std::vector<std::shared_ptr<AST::MatchCase>>& c) { return true; }
std::string TypeChecker::get_missing_union_variants(TypePtr u, const std::vector<std::shared_ptr<AST::MatchCase>>& c) { return ""; }
void TypeChecker::validate_pattern_compatibility(std::shared_ptr<AST::Expression> p, TypePtr m, int l) {}
TypePtr TypeChecker::infer_lambda_return_type(const std::shared_ptr<AST::Statement>& b) { return type_system.ANY_TYPE; }
TypePtr TypeChecker::infer_literal_type(const std::shared_ptr<AST::LiteralExpr>& e, TypePtr ex) { return type_system.ANY_TYPE; }
TypePtr TypeChecker::get_common_type(TypePtr l, TypePtr r) { return type_system.getCommonType(l, r); }
bool TypeChecker::can_implicitly_convert(TypePtr f, TypePtr t) { return type_system.isCompatible(f, t); }

void TypeChecker::register_builtin_function(const std::string& n, const std::vector<TypePtr>& p, TypePtr r) {
    FunctionSignature sig(n, p, r);
    function_signatures[n] = sig;
}

namespace TypeCheckerFactory {
    TypeCheckResult check_program(std::shared_ptr<AST::Program> program, const std::string& source, const std::string& file_path) {
        static std::shared_ptr<TypeSystem> ts = std::make_shared<TypeSystem>();
        TypeChecker checker(*ts);
        bool success = checker.check_program(program);
        return TypeCheckResult(program, ts, success, checker.get_errors());
    }
}

} // namespace Frontend
} // namespace LM

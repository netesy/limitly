#include "memory_checker.hh"
#include "../error/debugger.hh"
#include <sstream>
#include <algorithm>

namespace LM {
namespace Frontend {
using namespace LM::Error;

// =============================================================================
// MAIN MEMORY CHECKING ENTRY POINT
// =============================================================================

MemoryCheckResult MemoryChecker::check_program(std::shared_ptr<LM::Frontend::AST::Program> program, 
                                               const std::string& source, 
                                               const std::string& filename) {
    if (!program) {
        MemoryCheckResult result;
        result.success = false;
        result.program = nullptr;
        result.errors.push_back("Null program provided to memory checker");
        return result;
    }
    
    if (!program->ownership_facts || !program->ownership_facts->verified) {
        MemoryCheckResult result; result.success = false; result.program = program;
        result.errors.push_back("Missing or invalid authoritative ownership facts from semantic analysis");
        return result;
    }

    // Initialize state
    ownership_facts = program->ownership_facts;
    current_source = source;
    current_file_path = filename;
    errors.clear();
    warnings.clear();
    constant_variables.clear();
    atomic_variables.clear();
    active_parallel_slices.clear();
    current_region_id = 0;
    current_generation = 0;
    
    // Don't reset Debugger error state to avoid clearing type checker errors
    
    // Enter initial memory region
    enter_memory_region();
    
    // Check all statements for memory safety
    for (auto& stmt : program->statements) {
        // Declarations are not executions: inspect their bodies after global
        // bindings have been collected, in the isolated invocation context.
        if (!std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt) &&
            !std::dynamic_pointer_cast<AST::FrameDeclaration>(stmt))
            check_statement(stmt);
        // Only attach memory_info to statements that represent actual region boundaries
        // Block statements, function declarations, etc.
        if (auto block = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(stmt)) {
            insert_memory_operations(stmt);
        } else if (auto func = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(stmt)) {
            insert_memory_operations(stmt);
        }
        // TODO: Add other statement types that represent region boundaries
    }
    
    for (const auto& stmt : program->statements) {
        if (std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt) ||
            std::dynamic_pointer_cast<AST::FrameDeclaration>(stmt))
            check_statement(stmt);
    }

    // Exit initial region
    
    // Create result
    MemoryCheckResult result;
    result.success = !Debugger::hasError();
    result.program = program;
    result.errors = errors;
    result.warnings = warnings;
    
    return result;
}

// =============================================================================
// STATEMENT CHECKING
// =============================================================================

void MemoryChecker::check_statement(std::shared_ptr<LM::Frontend::AST::Statement> stmt) {
    if (!stmt) return;
    
    // Analyze callable bodies in an isolated invocation context. Checking a
    // declaration must not execute its ownership effects on enclosing bindings.
    auto check_body = [&](const std::shared_ptr<AST::BlockStatement>& body,
                          const auto& parameters) {
        if (!body) return;
        MemoryChecker invocation = *this;
        const size_t old_errors = invocation.errors.size();
        const size_t old_warnings = invocation.warnings.size();
        invocation.active_parallel_slices.clear();
        invocation.enter_memory_region();
        for (const auto& parameter : parameters) {
            invocation.constant_variables.erase(parameter.first);
            invocation.atomic_variables.erase(parameter.first);
        }
        invocation.check_statement(body);
        errors.insert(errors.end(), invocation.errors.begin() + old_errors, invocation.errors.end());
        warnings.insert(warnings.end(), invocation.warnings.begin() + old_warnings, invocation.warnings.end());
    };
    if (auto function = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
        auto parameters = function->params;
        for (const auto& optional : function->optionalParams)
            parameters.emplace_back(optional.first, optional.second.first);
        check_body(function->body, parameters);
    } else if (auto frame = std::dynamic_pointer_cast<AST::FrameDeclaration>(stmt)) {
        auto check_method = [&](const std::shared_ptr<AST::FrameMethod>& method) {
            if (!method) return;
            auto parameters = method->parameters;
            for (const auto& optional : method->optionalParams)
                parameters.emplace_back(optional.first, optional.second.first);
            check_body(method->body, parameters);
        };
        check_method(frame->init);
        check_method(frame->deinit);
        for (const auto& method : frame->methods) check_method(method);
    } else if (auto unsafe = std::dynamic_pointer_cast<AST::UnsafeStatement>(stmt)) {
        check_statement(unsafe->body);
    } else if (auto var_decl = std::dynamic_pointer_cast<LM::Frontend::AST::VarDeclaration>(stmt)) {
        check_var_declaration(var_decl);
    } else if (auto assignment = std::dynamic_pointer_cast<LM::Frontend::AST::AssignExpr>(stmt)) {
        check_assignment(assignment);
    } else if (auto block = std::dynamic_pointer_cast<LM::Frontend::AST::BlockStatement>(stmt)) {
        check_block_statement(block);
    } else if (auto expr_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ExprStatement>(stmt)) {
        check_expression(expr_stmt->expression);
    } else if (auto if_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::IfStatement>(stmt)) {
        check_expression(if_stmt->condition);
        check_statement(if_stmt->thenBranch);
        if (if_stmt->elseBranch) {
            check_statement(if_stmt->elseBranch);
        }
    } else if (auto while_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::WhileStatement>(stmt)) {
        check_expression(while_stmt->condition);
        check_statement(while_stmt->body);
    } else if (auto for_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ForStatement>(stmt)) {
        if (for_stmt->initializer) check_statement(for_stmt->initializer);
        if (for_stmt->condition) check_expression(for_stmt->condition);
        if (for_stmt->increment) check_expression(for_stmt->increment);
        check_statement(for_stmt->body);
        
        // For loop variables are handled in the initializer statement
        // which should be a variable declaration that check_statement will process
    } else if (auto return_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ReturnStatement>(stmt)) {
        // Handle return statement - ownership transfer from callee to caller
        if (return_stmt->value) {
            check_expression(return_stmt->value);
            
            // If returning a variable, mark it as escaped
        }
    } else if (auto iter_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::IterStatement>(stmt)) {
        // Handle iter statement - check the iterable and body
        check_expression(iter_stmt->iterable);
        
        check_statement(iter_stmt->body);
    } else if (auto staged_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::StagedStatement>(stmt)) {
        if (staged_stmt->declaration) check_statement(staged_stmt->declaration);
        if (staged_stmt->block) check_statement(staged_stmt->block);
        if (staged_stmt->expression) check_expression(staged_stmt->expression);
    } else if (auto staged_block = std::dynamic_pointer_cast<LM::Frontend::AST::StagedBlockStatement>(stmt)) {
        if (staged_block->body) check_statement(staged_block->body);
    } else if (auto contract_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ContractStatement>(stmt)) {
        if (contract_stmt->condition) check_expression(contract_stmt->condition);
        if (contract_stmt->message) check_expression(contract_stmt->message);
    } else if (auto parallel_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ParallelStatement>(stmt)) {
        active_parallel_slices.clear();
        parallel_stmt->slice_capabilities.clear();
        infer_parallel_capabilities(parallel_stmt);
        if (parallel_stmt->body) check_statement(parallel_stmt->body);
        active_parallel_slices.clear();
    } else if (auto task_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::TaskStatement>(stmt)) {
        if (task_stmt->iterable) {
            check_expression(task_stmt->iterable);

        }
        if (task_stmt->body) check_statement(task_stmt->body);
    } else if (auto concurrent_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::ConcurrentStatement>(stmt)) {
        validate_concurrent_isolation(concurrent_stmt->body);
        if (concurrent_stmt->body) check_statement(concurrent_stmt->body);
    } else if (auto worker_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::WorkerStatement>(stmt)) {
        std::unordered_set<std::string> locals;
        if (!worker_stmt->paramName.empty()) locals.insert(worker_stmt->paramName);
        validate_concurrent_isolation(worker_stmt->body, std::move(locals));
        if (worker_stmt->iterable) check_expression(worker_stmt->iterable);
        if (worker_stmt->body) check_statement(worker_stmt->body);
    }
}

void MemoryChecker::check_var_declaration(std::shared_ptr<AST::VarDeclaration> declaration) {
    if (!declaration) return;
    if (declaration->type && declaration->type.value() && declaration->type.value()->typeName == "atomic")
        atomic_variables.insert(declaration->name);
    if (declaration->initializer) {
        check_expression(declaration->initializer);
        if (is_constant_expression(declaration->initializer))
            constant_variables[declaration->name] = evaluate_constant_int(declaration->initializer);
    }
}

void MemoryChecker::check_assignment(std::shared_ptr<AST::AssignExpr> assignment) {
    if (assignment) check_expression(assignment->value);
}

void MemoryChecker::check_expression(std::shared_ptr<LM::Frontend::AST::Expression> expr) {
    if (!expr) return;
    
    if (auto call_expr = std::dynamic_pointer_cast<LM::Frontend::AST::CallExpr>(expr)) {
        check_function_call(call_expr);
    } else if (auto binary_expr = std::dynamic_pointer_cast<LM::Frontend::AST::BinaryExpr>(expr)) {
        check_binary_expression(binary_expr);
    } else if (auto index_expr = std::dynamic_pointer_cast<LM::Frontend::AST::IndexExpr>(expr)) {
        check_index_expression(index_expr);
    } else if (auto unary_expr = std::dynamic_pointer_cast<LM::Frontend::AST::UnaryExpr>(expr)) {
        check_expression(unary_expr->right);
    } else if (auto group_expr = std::dynamic_pointer_cast<LM::Frontend::AST::GroupingExpr>(expr)) {
        check_expression(group_expr->expression);
    } else if (auto staged_expr = std::dynamic_pointer_cast<LM::Frontend::AST::StagedExpr>(expr)) {
        if (staged_expr->expression) check_expression(staged_expr->expression);
        if (staged_expr->block) check_statement(staged_expr->block);
    }
}



void MemoryChecker::check_function_call(std::shared_ptr<AST::CallExpr> call) {
    if (!call) return;
    for (const auto& argument : call->arguments) check_expression(argument);
}

void MemoryChecker::check_binary_expression(std::shared_ptr<LM::Frontend::AST::BinaryExpr> binary) {
    if (!binary) return;
    
    // First check both operands recursively
    check_expression(binary->left);
    check_expression(binary->right);
    
    // Then check arithmetic safety
    check_arithmetic_safety(binary);
}

void MemoryChecker::check_arithmetic_safety(std::shared_ptr<LM::Frontend::AST::BinaryExpr> binary) {
    if (!binary) return;
    
    // Check division by zero
    if (binary->op == TokenType::SLASH || binary->op == TokenType::MODULUS) {
        check_division_safety(binary);
    }
    
    // Check shift operations
    if (binary->op == TokenType::LESS_LESS || binary->op == TokenType::GREATER_GREATER) {
        check_shift_safety(binary);
    }
    
    // Check for overflow/underflow on arithmetic operations
    if (binary->op == TokenType::PLUS || binary->op == TokenType::MINUS || 
        binary->op == TokenType::STAR || binary->op == TokenType::POWER) {
        // Only check constant expressions at compile time
        if (is_constant_expression(binary->left) && is_constant_expression(binary->right)) {
            int64_t left = evaluate_constant_int(binary->left);
            int64_t right = evaluate_constant_int(binary->right);
            
            if (binary->op == TokenType::PLUS) {
                if (check_overflow(left, right, "+")) {
                    add_memory_error("overflow", "", 
                                   "Integer overflow detected in addition operation",
                                   binary->line);
                }
            } else if (binary->op == TokenType::MINUS) {
                if (check_underflow(left, right, "-")) {
                    add_memory_error("overflow", "", 
                                   "Integer underflow detected in subtraction operation",
                                   binary->line);
                }
            } else if (binary->op == TokenType::STAR) {
                if (check_overflow(left, right, "*")) {
                    add_memory_error("overflow", "", 
                                   "Integer overflow detected in multiplication operation",
                                   binary->line);
                }
            } else if (binary->op == TokenType::POWER) {
                // Exponentiation overflow check
                if (right < 0) {
                    add_memory_error("overflow", "", 
                                   "Negative exponent in exponentiation operation",
                                   binary->line);
                } else if (right > 20 && left > 1) {
                    // Conservative check: large exponents likely overflow
                    add_memory_error("overflow", "", 
                                   "Potential overflow in exponentiation operation",
                                   binary->line);
                }
            }
        }
    }
}

void MemoryChecker::check_division_safety(std::shared_ptr<LM::Frontend::AST::BinaryExpr> binary) {
    if (!binary) return;
    
    // Check if divisor is constant zero
    if (is_constant_expression(binary->right)) {
        int64_t divisor = evaluate_constant_int(binary->right);
        if (divisor == 0) {
            add_memory_error("divide_by_zero", "", 
                           "Division by zero detected",
                           binary->line);
        }
    }
}

void MemoryChecker::check_shift_safety(std::shared_ptr<LM::Frontend::AST::BinaryExpr> binary) {
    if (!binary) return;
    
    // Check if shift amount is constant
    if (is_constant_expression(binary->right)) {
        int64_t shift_amount = evaluate_constant_int(binary->right);
        
        if (shift_amount < 0) {
            add_memory_error("shift_error", "", 
                           "Negative shift amount detected",
                           binary->line);
        }
        
        if (shift_amount >= 64) {
            add_memory_error("shift_error", "", 
                           "Shift amount exceeds bit width (>= 64)",
                           binary->line);
        }
    }
}

bool MemoryChecker::is_constant_expression(std::shared_ptr<LM::Frontend::AST::Expression> expr) {
    if (!expr) return false;
    
    // Check for literal expression
    if (auto lit = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(expr)) {
        return true;
    }
    
    // Could extend to check for constant variable references
    // For now, only literals are considered constant
    
    return false;
}

int64_t MemoryChecker::evaluate_constant_int(std::shared_ptr<LM::Frontend::AST::Expression> expr) {
    if (!expr) return 0;
    
    if (auto lit = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(expr)) {
        // Check if the literal holds an integer (stored as string in variant)
        if (std::holds_alternative<std::string>(lit->value)) {
            try {
                return std::stoll(std::get<std::string>(lit->value));
            } catch (...) {
                return 0;
            }
        }
    }
    
    return 0;
}

bool MemoryChecker::check_overflow(int64_t left, int64_t right, const std::string& op) {
    if (op == "+") {
        if (right > 0 && left > INT64_MAX - right) return true;
        if (right < 0 && left < INT64_MIN - right) return true;
    } else if (op == "*") {
        if (left > 0) {
            if (right > 0 && left > INT64_MAX / right) return true;
            if (right < 0 && right < INT64_MIN / left) return true;
        } else if (left < 0) {
            if (right > 0 && left < INT64_MIN / right) return true;
            if (right < 0 && left > INT64_MAX / right) return true;
        }
    }
    
    return false;
}

bool MemoryChecker::check_underflow(int64_t left, int64_t right, const std::string& op) {
    if (op == "-") {
        if (right > 0 && left < INT64_MIN + right) return true;
        if (right < 0 && left > INT64_MAX + right) return true;
    }
    
    return false;
}

void MemoryChecker::check_index_expression(std::shared_ptr<LM::Frontend::AST::IndexExpr> index) {
    if (!index) return;
    
    // First check the object and index expressions recursively
    check_expression(index->object);
    check_expression(index->index);
    
    // Check bounds if we have constant expressions
    if (auto list_expr = std::dynamic_pointer_cast<LM::Frontend::AST::ListExpr>(index->object)) {
        check_list_bounds(index, list_expr);
    } else if (auto str_lit = std::dynamic_pointer_cast<LM::Frontend::AST::LiteralExpr>(index->object)) {
        check_string_bounds(index, str_lit);
    } else if (auto tuple_expr = std::dynamic_pointer_cast<LM::Frontend::AST::TupleExpr>(index->object)) {
        check_tuple_bounds(index, tuple_expr);
    }
}

void MemoryChecker::check_list_bounds(std::shared_ptr<LM::Frontend::AST::IndexExpr> index, std::shared_ptr<LM::Frontend::AST::ListExpr> list) {
    if (!index || !list) return;
    
    // Check if index is constant
    if (is_constant_expression(index->index)) {
        int64_t idx = evaluate_constant_int(index->index);
        int64_t size = list->elements.size();
        
        if (idx < 0) {
            add_memory_error("bounds_error", "", 
                           "Negative list index: " + std::to_string(idx),
                           index->line);
        } else if (idx >= size) {
            add_memory_error("bounds_error", "", 
                           "List index out of bounds: index " + std::to_string(idx) + 
                           " is outside valid range [0, " + std::to_string(size - 1) + "]",
                           index->line);
        }
    }
}

void MemoryChecker::check_string_bounds(std::shared_ptr<LM::Frontend::AST::IndexExpr> index, std::shared_ptr<LM::Frontend::AST::LiteralExpr> str) {
    if (!index || !str) return;
    
    // Check if index is constant
    if (is_constant_expression(index->index)) {
        int64_t idx = evaluate_constant_int(index->index);
        
        // Get string length from literal
        if (std::holds_alternative<std::string>(str->value)) {
            int64_t size = std::get<std::string>(str->value).length();
            
            if (idx < 0) {
                add_memory_error("bounds_error", "", 
                               "Negative string index: " + std::to_string(idx),
                               index->line);
            } else if (idx >= size) {
                add_memory_error("bounds_error", "", 
                               "String index out of bounds: index " + std::to_string(idx) + 
                               " is outside valid range [0, " + std::to_string(size - 1) + "]",
                               index->line);
            }
        }
    }
}

void MemoryChecker::check_tuple_bounds(std::shared_ptr<LM::Frontend::AST::IndexExpr> index, std::shared_ptr<LM::Frontend::AST::TupleExpr> tuple) {
    if (!index || !tuple) return;
    
    // Check if index is constant
    if (is_constant_expression(index->index)) {
        int64_t idx = evaluate_constant_int(index->index);
        int64_t size = tuple->elements.size();
        
        if (idx < 0) {
            add_memory_error("bounds_error", "", 
                           "Negative tuple index: " + std::to_string(idx),
                           index->line);
        } else if (idx >= size) {
            add_memory_error("bounds_error", "", 
                           "Tuple index out of bounds: index " + std::to_string(idx) + 
                           " is outside valid range [0, " + std::to_string(size - 1) + "]",
                           index->line);
        }
    }
}

void MemoryChecker::check_block_statement(std::shared_ptr<AST::BlockStatement> block) {
    if (!block) return;
    enter_memory_region();
    for (const auto& statement : block->statements) check_statement(statement);
}

bool MemoryChecker::verify_slice_disjointness(const AST::ParallelSliceCapability& slice, int line) {
    if (slice.begin < 0 || slice.end <= slice.begin) {
        add_memory_error("Capability Violation", slice.collection,
                         "Data race capability violation: mutable slice range [" +
                         std::to_string(slice.begin) + ", " +
                         std::to_string(slice.end) +
                         ") must be non-negative and non-empty", line);
        return false;
    }
    for (const auto& existing : active_parallel_slices) {
        const bool overlap = slice.collection == existing.collection &&
            (slice.mutable_access || existing.mutable_access) &&
            slice.begin < existing.end && existing.begin < slice.end;
        if (overlap) {
            add_memory_error("Capability Violation", slice.collection,
                             "Overlapping mutable slice capability in parallel worker: range [" +
                             std::to_string(slice.begin) + ", " + std::to_string(slice.end) +
                             ") overlaps with range [" + std::to_string(existing.begin) + ", " +
                             std::to_string(existing.end) + ")", line);
            return false;
        }
    }
    active_parallel_slices.push_back(slice);
    return true;
}

void MemoryChecker::infer_parallel_capabilities(
    const std::shared_ptr<AST::ParallelStatement>& parallel_stmt) {
    if (!parallel_stmt || !parallel_stmt->body) return;

    for (const auto& statement : parallel_stmt->body->statements) {
        auto iteration = std::dynamic_pointer_cast<AST::IterStatement>(statement);
        if (!iteration || iteration->loopVars.size() != 1) continue;

        const std::string& index_name = iteration->loopVars.front();
        std::unordered_set<std::string> written_collections;
        std::function<void(const std::shared_ptr<AST::Node>&)> inspect;
        inspect = [&](const std::shared_ptr<AST::Node>& node) {
            if (!node) return;
            if (auto block = std::dynamic_pointer_cast<AST::BlockStatement>(node)) {
                for (const auto& child : block->statements) inspect(child);
            } else if (auto expression = std::dynamic_pointer_cast<AST::ExprStatement>(node)) {
                inspect(expression->expression);
            } else if (auto assignment = std::dynamic_pointer_cast<AST::AssignExpr>(node)) {
                auto collection = std::dynamic_pointer_cast<AST::VariableExpr>(assignment->object);
                if (!collection || !assignment->index) return;
                auto index = std::dynamic_pointer_cast<AST::VariableExpr>(assignment->index);
                if (!index || index->name != index_name) {
                    add_memory_error("Capability Violation", collection->name,
                                     "Parallel write must be indexed by the iteration variable '" +
                                     index_name + "' to prove exclusive ownership", assignment->line);
                    return;
                }
                written_collections.insert(collection->name);
            } else if (auto conditional = std::dynamic_pointer_cast<AST::IfStatement>(node)) {
                inspect(conditional->thenBranch);
                inspect(conditional->elseBranch);
            } else if (auto loop = std::dynamic_pointer_cast<AST::WhileStatement>(node)) {
                inspect(loop->body);
            } else if (auto loop = std::dynamic_pointer_cast<AST::ForStatement>(node)) {
                inspect(loop->initializer);
                inspect(loop->body);
            } else if (auto loop = std::dynamic_pointer_cast<AST::IterStatement>(node)) {
                inspect(loop->body);
            }
        };
        inspect(iteration->body);

        // Read-only iterations need no exclusive capability and may use
        // dynamically sized iterables. Bounds are required only once a write
        // capability must be minted.
        if (written_collections.empty()) continue;

        auto range = std::dynamic_pointer_cast<AST::RangeExpr>(iteration->iterable);
        if (!range || !is_constant_expression(range->start) ||
            !is_constant_expression(range->end)) {
            add_memory_error("Capability Violation", "",
                             "Parallel mutable iteration requires a statically bounded range",
                             statement->line);
            continue;
        }

        for (const auto& collection : written_collections) {
            AST::ParallelSliceCapability capability;
            capability.collection = collection;
            capability.index_variable = index_name;
            capability.begin = evaluate_constant_int(range->start);
            capability.end = evaluate_constant_int(range->end);
            capability.mutable_access = true;
            CapabilityType formal_type;
            formal_type.region = "parallel@" + std::to_string(parallel_stmt->line);
            formal_type.begin = capability.begin;
            formal_type.end = capability.end;
            formal_type.mutableAccess = true;
            capability.capability_type = std::make_shared<::Type>(TypeTag::Capability, formal_type);
            if (verify_slice_disjointness(capability, statement->line)) {
                parallel_stmt->slice_capabilities.push_back(capability);
            }
        }
    }
}

void MemoryChecker::validate_concurrent_isolation(
    const std::shared_ptr<AST::Node>& node,
    std::unordered_set<std::string> locals) {
    if (!node) return;
    if (auto block = std::dynamic_pointer_cast<AST::BlockStatement>(node)) {
        for (const auto& child : block->statements) {
            if (auto declaration = std::dynamic_pointer_cast<AST::VarDeclaration>(child)) {
                locals.insert(declaration->name);
            }
        }
        for (const auto& child : block->statements) {
            validate_concurrent_isolation(child, locals);
        }
        return;
    }
    if (auto assignment = std::dynamic_pointer_cast<AST::AssignExpr>(node)) {
        std::string target = assignment->name;
        if (target.empty()) {
            if (auto object = std::dynamic_pointer_cast<AST::VariableExpr>(assignment->object)) {
                target = object->name;
            }
        }
        // The authoritative binding identity distinguishes an implicit task-local
        // declaration from a write to an existing outer binding. Unknown facts
        // cannot grant an isolation proof.
        const auto semantic_id = assignment->memory_info.semantic_id;
        const auto fact = ownership_facts->nodes.find(semantic_id);
        const bool task_local_declaration = !assignment->object && !assignment->index &&
            !assignment->member && fact != ownership_facts->nodes.end() &&
            fact->second.binding == semantic_id;
        if (!target.empty() && !task_local_declaration &&
            !locals.count(target) && !atomic_variables.count(target)) {
            add_memory_error("Data race", target,
                             "Concurrent task mutates outer variable '" + target +
                             "'; transfer data through a channel, use task-local state, or declare an atomic scalar",
                             assignment->line);
        }
        return;
    }
    if (auto expression = std::dynamic_pointer_cast<AST::ExprStatement>(node)) {
        validate_concurrent_isolation(expression->expression, std::move(locals));
    } else if (auto task = std::dynamic_pointer_cast<AST::TaskStatement>(node)) {
        if (!task->loopVar.empty()) locals.insert(task->loopVar);
        validate_concurrent_isolation(task->body, std::move(locals));
    } else if (auto worker = std::dynamic_pointer_cast<AST::WorkerStatement>(node)) {
        if (!worker->paramName.empty()) locals.insert(worker->paramName);
        validate_concurrent_isolation(worker->body, std::move(locals));
    } else if (auto conditional = std::dynamic_pointer_cast<AST::IfStatement>(node)) {
        validate_concurrent_isolation(conditional->thenBranch, locals);
        validate_concurrent_isolation(conditional->elseBranch, std::move(locals));
    } else if (auto loop = std::dynamic_pointer_cast<AST::WhileStatement>(node)) {
        validate_concurrent_isolation(loop->body, std::move(locals));
    } else if (auto loop = std::dynamic_pointer_cast<AST::ForStatement>(node)) {
        validate_concurrent_isolation(loop->body, std::move(locals));
    } else if (auto loop = std::dynamic_pointer_cast<AST::IterStatement>(node)) {
        for (const auto& name : loop->loopVars) locals.insert(name);
        validate_concurrent_isolation(loop->body, std::move(locals));
    } else if (auto nested = std::dynamic_pointer_cast<AST::ConcurrentStatement>(node)) {
        validate_concurrent_isolation(nested->body, std::move(locals));
    }
}

// =============================================================================
// MEMORY OPERATIONS
// =============================================================================

// The memory checker attaches memory_info to AST nodes for the LIR generator to use
// This provides a unified region management system instead of independent systems

void MemoryChecker::insert_memory_operations(std::shared_ptr<LM::Frontend::AST::Statement> stmt) {
    if (stmt) {
        const auto binding_identity = stmt->memory_info.semantic_id;
        stmt->memory_info = LM::Frontend::AST::MemoryInfo(current_region_id, current_generation);
        stmt->memory_info.semantic_id = binding_identity;
    }
}

// Lexical region annotations only; ownership generations belong to SemanticFacts.
void MemoryChecker::enter_memory_region() {
    ++current_region_id;
    ++current_generation;
}

// =============================================================================
// ERROR REPORTING
// =============================================================================

void MemoryChecker::add_memory_error(const std::string& error_type, const std::string& variable_name, 
                                    const std::string& description, int line) {
    std::string message = error_type + ": " + description;
    const std::string hint = "Check bounds and task isolation; ownership is inferred from source and verified in canonical LIR.";

    if (line > 0 && !current_source.empty()) {
        Debugger::error(message, line, 0, InterpretationStage::MEMORY, current_source, current_file_path, hint, "");
    } else {
        Debugger::error(message, line, 0, InterpretationStage::MEMORY, "", "", hint, "");
    }
}

void MemoryChecker::add_error(const std::string& message, int line) {
    if (line > 0 && !current_source.empty()) {
        Debugger::error(message, line, 0, InterpretationStage::MEMORY, current_source, current_file_path, "", "");
    } else {
        Debugger::error(message, line, 0, InterpretationStage::MEMORY, "", "", "", "");
    }
}

void MemoryChecker::add_warning(const std::string& message, int line) {
    std::ostringstream oss;
    oss << "Warning: " << message;
    if (line > 0) {
        oss << " (line " << line << ")";
    }
    warnings.push_back(oss.str());
}

// =============================================================================
// FACTORY IMPLEMENTATION
// =============================================================================

MemoryCheckResult MemoryCheckerFactory::check_program(std::shared_ptr<LM::Frontend::AST::Program> program, 
                                                      const std::string& source, 
                                                      const std::string& filename) {
    MemoryChecker checker;
    return checker.check_program(program, source, filename);
}

} // namespace Frontend
} // namespace LM

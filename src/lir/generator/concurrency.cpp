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

void Generator::emit_parallel_stmt(LM::Frontend::AST::ParallelStatement& stmt) {
   // std::cout << "[DEBUG] Emitting ParallelStatement" << std::endl;
    
    auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
    
    // Parse cores parameter
    int num_cores = 3;  // default
    if (!stmt.cores.empty() && stmt.cores != "auto") {
        try {
            num_cores = std::stoi(stmt.cores);
        } catch (...) {
            num_cores = 3;  // fallback
        }
    }
    
    // Parse timeout parameter
    uint64_t timeout_ms = 20000;  // 20 second default
    if (!stmt.timeout.empty()) {
        timeout_ms = parse_timeout(stmt.timeout);
    }
    
    // Parse grace period
    uint64_t grace_ms = 1000;  // 1 second default
    if (!stmt.grace.empty()) {
        grace_ms = parse_grace_period(stmt.grace);
    }
    
    // Parse error handling
    std::string error_strategy = "Stop";  // default
    if (!stmt.on_error.empty()) {
        error_strategy = stmt.on_error;
    }
    
  
    // According to spec: Parallel blocks should NOT use task statements
    // They should use direct code with SharedCell operations and work queue system
    
    // 1. Find variables accessed in the parallel block body that need to be shared
    std::set<std::string> accessed_variables;
    collect_variables_from_statement(*stmt.body, accessed_variables);
    
   // std::cout << "[DEBUG] Found " << accessed_variables.size() << " variables to share via SharedCell" << std::endl;
    
    // 2. Allocate SharedCell IDs for each accessed variable
    parallel_block_cell_ids_.clear();
    for (const auto& var_name : accessed_variables) {
        Reg cell_id_reg = allocate_register();
        emit_instruction(LIR_Inst(LIR_Op::SharedCellAlloc, Type::I64, cell_id_reg, 0, 0));
        parallel_block_cell_ids_[var_name] = cell_id_reg;
        

    }
    
    // 3. Initialize parallel execution system (using available operations)
    Reg parallel_context_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::ParallelInit, parallel_context_reg, num_cores, 0));
    
   // std::cout << "[DEBUG] Initialized parallel execution for " << num_cores << " cores" << std::endl;
    
    // 4. Set up SharedCell context for the parallel block body
    auto saved_parallel_block_cell_ids = parallel_block_cell_ids_;
    enter_concurrency_context();
    
    // 5. Process parallel block body - execute directly with SharedCell context
    if (auto block_stmt = dynamic_cast<LM::Frontend::AST::BlockStatement*>(stmt.body.get())) {
        for (auto& body_stmt : block_stmt->statements) {
            // According to spec: NO task statements in parallel blocks
            if (auto task_stmt = dynamic_cast<LM::Frontend::AST::TaskStatement*>(body_stmt.get())) {
                report_error("Task statements are not allowed in parallel blocks. Use concurrent blocks for task-based parallelism.");
                return;
            }
            
            // For parallel blocks, execute statements directly with SharedCell context
           // std::cout << "[DEBUG] Executing parallel statement directly" << std::endl;
            emit_stmt(*body_stmt);
        }
    }
    
    // 6. Synchronize and complete parallel execution (using available operations)
    emit_instruction(LIR_Inst(LIR_Op::ParallelSync, parallel_context_reg, 0, 0));
    
    // 7. Synchronize SharedCell values back to main thread registers
    for (const auto& var_mapping : parallel_block_cell_ids_) {
        const std::string& var_name = var_mapping.first;
        Reg cell_id_reg = var_mapping.second;
        
        // Load the final value from SharedCell
        Reg current_value_reg = allocate_register();
        emit_instruction(LIR_Inst(LIR_Op::SharedCellLoad, current_value_reg, cell_id_reg, 0));
        
        // Store it back to the original variable
        Reg var_reg = resolve_variable(var_name);
        if (var_reg != UINT32_MAX) {
            emit_instruction(LIR_Inst(LIR_Op::Store, var_reg, current_value_reg, 0));

        }
    }
    
    // Restore SharedCell context
    parallel_block_cell_ids_ = saved_parallel_block_cell_ids;
    
   // std::cout << "[DEBUG] Parallel block completed using SharedCell + direct execution" << std::endl;
}

// Helper functions for parsing timeout and grace period strings

uint64_t Generator::parse_timeout(const std::string& timeout_str) {
    // Simple implementation - assume timeout is in seconds
    if (timeout_str.empty()) return 20000; // 20 seconds default
    
    try {
        if (timeout_str.back() == 's') {
            return static_cast<uint64_t>(std::stod(timeout_str.substr(0, timeout_str.length() - 1)) * 1000);
        } else {
            return static_cast<uint64_t>(std::stod(timeout_str) * 1000);
        }
    } catch (...) {
        return 20000; // fallback
    }
}


uint64_t Generator::parse_grace_period(const std::string& grace_str) {
    // Simple implementation - assume grace period is in milliseconds
    if (grace_str.empty()) return 1000; // 1 second default
    
    try {
        if (grace_str.back() == 's') {
            return static_cast<uint64_t>(std::stod(grace_str.substr(0, grace_str.length() - 1)) * 1000);
        } else {
            return static_cast<uint64_t>(std::stod(grace_str) * 1000);
        }
    } catch (...) {
        return 1000; // fallback
    }
}

std::optional<ValuePtr> Generator::evaluate_constant_expression(std::shared_ptr<LM::Frontend::AST::Expression> expr) {
    if (!expr) return std::nullopt;
    
    // Handle literal expressions
    if (auto literal = dynamic_cast<LM::Frontend::AST::LiteralExpr*>(expr.get())) {
        if (std::holds_alternative<std::string>(literal->value)) {
            // Try to parse string as integer
            std::string str_val = std::get<std::string>(literal->value);
            try {
                int64_t int_val = std::stoll(str_val);
                auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
                return std::make_shared<Value>(int_type, int_val);
            } catch (...) {
                return std::nullopt;
            }
        } else if (std::holds_alternative<bool>(literal->value)) {
            auto bool_type = std::make_shared<::Type>(::TypeTag::Bool);
            return std::make_shared<Value>(bool_type, std::get<bool>(literal->value));
        }
    }
    
    // Handle variable expressions (for now, just return nullopt)
    // In a full implementation, this would look up constant variables
    
    return std::nullopt;
}


void Generator::emit_concurrent_stmt(LM::Frontend::AST::ConcurrentStatement& stmt) {
   // std::cout << "[DEBUG] Processing concurrent statement" << std::endl;
    auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
    scheduler_initialized_ = true;
   // std::cout << "[DEBUG] About to handle channel parameter assignment" << std::endl;
    // Handle channel parameter assignment (e.g., "ch=counts")
   // std::cout << "[DEBUG] Handling channel parameter assignment" << std::endl;
   // std::cout << "[DEBUG] Channel param: '" << stmt.channelParam << "'" << std::endl;
   // std::cout << "[DEBUG] Channel name: '" << stmt.channel << "'" << std::endl;
    Reg channel_reg;
    if (!stmt.channelParam.empty()) {
       // std::cout << "[DEBUG] Channel param is not empty: " << stmt.channelParam << std::endl;
        // We have a parameter assignment: param_name = channel_name
        std::string param_name = stmt.channelParam;
        std::string channel_name = stmt.channel;
        
       // std::cout << "[DEBUG] Resolving existing channel variable: " << channel_name << std::endl;
        // Resolve to existing channel variable
        channel_reg = resolve_variable(channel_name);
        if (channel_reg == UINT32_MAX) {
           // std::cout << "[DEBUG] Channel variable not found: " << channel_name << std::endl;
            report_error("Undefined channel variable: " + channel_name);
            return;
        }
        
       // std::cout << "[DEBUG] Binding parameter name to channel: " << param_name << std::endl;
        // Bind the parameter name to the existing channel
        bind_variable(param_name, channel_reg);
        set_register_type(channel_reg, int_type);
    } else {
       // std::cout << "[DEBUG] No channel param, allocating new channel" << std::endl;
        // Original behavior: allocate new channel
        channel_reg = allocate_register();
        emit_instruction(LIR_Inst(LIR_Op::ChannelAlloc, channel_reg, 32, 0));
        bind_variable(stmt.channel, channel_reg);
        set_register_type(channel_reg, int_type);
    }
    // Set current concurrent block ID for this statement
    current_concurrent_block_id_ = std::to_string(reinterpret_cast<uintptr_t>(&stmt));
    
    // Initialize scheduler for concurrent execution
   // std::cout << "[DEBUG] Initializing scheduler for concurrent block: " << current_concurrent_block_id_ << std::endl;
    Reg scheduler_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::SchedulerInit, scheduler_reg, 0, 0));
    scheduler_initialized_ = true;
    if (stmt.body) {
        // Look for TaskStatement in the body
        if (auto block_stmt = dynamic_cast<LM::Frontend::AST::BlockStatement*>(stmt.body.get())) {
            for (auto& body_stmt : block_stmt->statements) {
                if (auto task_stmt = dynamic_cast<LM::Frontend::AST::TaskStatement*>(body_stmt.get())) {
                    // Set the channel parameter for this task to use main channel
                    task_stmt->channel_param = stmt.channel;
                    
                    // Handle range iteration: task(i in 1..4)
                    if (task_stmt->iterable) {
                        if (auto range_expr = dynamic_cast<LM::Frontend::AST::RangeExpr*>(task_stmt->iterable.get())) {
                            // Evaluate range bounds
                            auto start_val = evaluate_constant_expression(range_expr->start);
                            auto end_val = evaluate_constant_expression(range_expr->end);
                            
                            if (start_val && end_val) {
                                int64_t start = std::stoll((*start_val)->data);
                                int64_t end = std::stoll((*end_val)->data);
                                
                                // Create task for each value in range
                                for (int64_t i = start; i <= end; ++i) {
                                    std::string task_name = "task_" + std::to_string(task_counter_++);
                                    
                                    // Create task function
                                    create_and_register_task_function(task_name, task_stmt, i);
                                    
                                    // Add task to scheduler
                                    Reg task_context_reg = allocate_register();
                                    Reg context_id_reg = allocate_register();
                                    emit_instruction(LIR_Inst(LIR_Op::TaskContextAlloc, task_context_reg, 1, 0));
                                    
                                    // Store context_id for later use in TaskSetField calls
                                    emit_instruction(LIR_Inst(LIR_Op::Mov, context_id_reg, task_context_reg, 0));
                                    
                                    // Set task ID in field 0
                                    Reg task_id_reg = allocate_register();
                                    auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
                                    ValuePtr task_id_val = std::make_shared<Value>(int_type, i);
                                    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, task_id_reg, task_id_val));
                                    emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, task_id_reg, context_id_reg, 0, 0));
                                    
                                    // Set loop variable value in field 1
                                    Reg loop_var_reg = allocate_register();
                                    ValuePtr loop_var_val = std::make_shared<Value>(int_type, i);
                                    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, loop_var_reg, loop_var_val));
                                    emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, loop_var_reg, context_id_reg, 0, 1));
                                    
                                    // Set channel register (use a fresh register to avoid overwriting channel_reg)
                                    Reg channel_copy_reg = allocate_register();
                                    emit_instruction(LIR_Inst(LIR_Op::Mov, channel_copy_reg, channel_reg, 0));
                                    emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, channel_copy_reg, context_id_reg, 0, 2));
                                    
                                    // Set task function name in field 4
                                    Reg task_name_reg = allocate_register();
                                    auto string_type = std::make_shared<::Type>(::TypeTag::String);
                                    ValuePtr task_name_val = std::make_shared<Value>(string_type, task_name);
                                    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Ptr, task_name_reg, task_name_val));
                                    emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, task_name_reg, context_id_reg, 0, 4));
                                    
                                    // Add task to scheduler
                                    emit_instruction(LIR_Inst(LIR_Op::SchedulerAddTask, Type::Void, context_id_reg, task_context_reg, 0));
                                }
                            }
                        }
                    }
                } else if (auto worker_stmt = dynamic_cast<LM::Frontend::AST::WorkerStatement*>(body_stmt.get())) {
                    // Handle worker statement: worker(item from jobs) or worker(item in jobs)
                   // std::cout << "[DEBUG] Processing worker statement with param '" << worker_stmt->paramName << "'" << std::endl;
                    
                    // Set channel parameter for this worker to use main channel
                    worker_stmt->channel_param = stmt.channel;
                   // std::cout << "[DEBUG] Set worker channel_param to: " << worker_stmt->channel_param << std::endl;
                    
                    // Handle worker iteration
                    if (worker_stmt->iterable) {
                       // std::cout << "[DEBUG] Worker has iterable, processing..." << std::endl;
                       // std::cout << "[DEBUG] About to evaluate iterable expression" << std::endl;
                        
                        // For now, create a single worker task that will handle iteration
                        // In a full implementation, this would create multiple workers based on cores
                        std::string worker_name = "worker_" + std::to_string(worker_counter_++);
                       // std::cout << "[DEBUG] Generated worker name: " << worker_name << std::endl;
                        
                        // Create worker function
                       // std::cout << "[DEBUG] About to create worker function" << std::endl;
                        create_and_register_worker_function(worker_name, worker_stmt);
                       // std::cout << "[DEBUG] Worker function created and registered" << std::endl;
                        
                        // Add worker to scheduler
                       // std::cout << "[DEBUG] About to add worker to scheduler" << std::endl;
                        Reg worker_context_reg = allocate_register();
                        Reg context_id_reg = allocate_register();
                        emit_instruction(LIR_Inst(LIR_Op::TaskContextAlloc, worker_context_reg, 1, 0));
                       // std::cout << "[DEBUG] Task context allocated" << std::endl;
                        
                        // Store context_id for later use in TaskSetField calls
                        emit_instruction(LIR_Inst(LIR_Op::Mov, context_id_reg, worker_context_reg, 0));
                        
                        // Set worker ID in field 0
                        Reg worker_id_reg = allocate_register();
                        auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
                        ValuePtr worker_id_val = std::make_shared<Value>(int_type, static_cast<int64_t>(0));
                        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, worker_id_reg, worker_id_val));
                        emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, worker_id_reg, context_id_reg, 0, 0));
                       // std::cout << "[DEBUG] Worker ID set" << std::endl;
                        
                        // Set iterable (channel/array) in field 1 - evaluate iterable expression
                       // std::cout << "[DEBUG] About to evaluate iterable expression" << std::endl;
                        Reg iterable_reg = emit_expr(*worker_stmt->iterable);
                       // std::cout << "[DEBUG] Iterable expression evaluated to register: " << iterable_reg << std::endl;
                        emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, iterable_reg, context_id_reg, 0, 1));
                       // std::cout << "[DEBUG] Iterable field set" << std::endl;
                        
                        // Set channel register (use a fresh register to avoid overwriting channel_reg)
                        Reg channel_copy_reg = allocate_register();
                        emit_instruction(LIR_Inst(LIR_Op::Mov, channel_copy_reg, channel_reg, 0));
                        emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, channel_copy_reg, context_id_reg, 0, 2));
                       // std::cout << "[DEBUG] Channel field set" << std::endl;
                        
                        // Set worker function name in field 4
                        Reg worker_name_reg = allocate_register();
                        auto string_type = std::make_shared<::Type>(::TypeTag::String);
                        ValuePtr worker_name_val = std::make_shared<Value>(string_type, worker_name);
                        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Ptr, worker_name_reg, worker_name_val));
                        emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, worker_name_reg, context_id_reg, 0, 4));
                       // std::cout << "[DEBUG] Worker function name field set" << std::endl;
                        
                        // Add worker to scheduler
                        emit_instruction(LIR_Inst(LIR_Op::SchedulerAddTask, Type::Void, context_id_reg, worker_context_reg, 0));
                       // std::cout << "[DEBUG] Worker added to scheduler" << std::endl;
                    } else {
                       // std::cout << "[DEBUG] Worker has no iterable, creating single worker" << std::endl;
                        // Handle worker without iterable (single execution)
                        std::string worker_name = "worker_" + std::to_string(worker_counter_++);
                        create_and_register_worker_function(worker_name, worker_stmt);
                        
                        // Add to scheduler similar to above but without iterable
                        Reg worker_context_reg = allocate_register();
                        Reg context_id_reg = allocate_register();
                        emit_instruction(LIR_Inst(LIR_Op::TaskContextAlloc, worker_context_reg, 0, 0));
                        emit_instruction(LIR_Inst(LIR_Op::Mov, context_id_reg, worker_context_reg, 0));
                        
                        Reg worker_id_reg = allocate_register();
                        auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
                        ValuePtr worker_id_val = std::make_shared<Value>(int_type, static_cast<int64_t>(0));
                        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, worker_id_reg, worker_id_val));
                        emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, worker_id_reg, context_id_reg, 0, 0));
                        
                        Reg channel_copy_reg = allocate_register();
                        emit_instruction(LIR_Inst(LIR_Op::Mov, channel_copy_reg, channel_reg, 0));
                        emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, channel_copy_reg, context_id_reg, 0, 2));
                        
                        Reg worker_name_reg = allocate_register();
                        auto string_type = std::make_shared<::Type>(::TypeTag::String);
                        ValuePtr worker_name_val = std::make_shared<Value>(string_type, worker_name);
                        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Ptr, worker_name_reg, worker_name_val));
                        emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, worker_name_reg, context_id_reg, 0, 4));
                        
                        emit_instruction(LIR_Inst(LIR_Op::SchedulerAddTask, Type::Void, context_id_reg, worker_context_reg, 0));
                       // std::cout << "[DEBUG] Single worker added to scheduler" << std::endl;
                    }
                   // std::cout << "[DEBUG] Worker processing completed" << std::endl;
                } else {
                    // For non-task statements, emit directly
                    emit_stmt(*body_stmt);
                }
            }
        }
    }
    
    // Run scheduler to execute all tasks
   // std::cout << "[DEBUG] Running scheduler for concurrent block: " << current_concurrent_block_id_ << std::endl;
    emit_instruction(LIR_Inst(LIR_Op::SchedulerRun, scheduler_reg, 0, 0));
    
    exit_concurrency_context();
   // std::cout << "[DEBUG] Concurrent statement processing completed" << std::endl;
}


void Generator::create_parallel_work_item(const std::string& work_item_name, std::shared_ptr<LM::Frontend::AST::Statement> stmt) {
   // std::cout << "[DEBUG] Creating parallel work item: " << work_item_name << std::endl;
    
    // Save current context
    auto saved_function = std::move(current_function_);
    auto saved_cfg_context = cfg_context_;
    auto saved_current_block = cfg_context_.current_block;
    
    // Create new work item function
    current_function_ = std::make_unique<LIR_Function>(work_item_name, 0);
    cfg_context_.building_cfg = false;
    cfg_context_.current_block = nullptr;
    
    // Initialize work item function
    enter_scope();
    
    // Emit the statement directly (no task wrapper)
    emit_stmt(*stmt);
    
    // Add return to work item function
    emit_instruction(LIR_Inst(LIR_Op::Ret, Type::Void, 0, 0, 0));
    
    // Restore context
    exit_scope();
    
    // Register work item function
    auto& func_registry = LIR::FunctionRegistry::getInstance();
    func_registry.registerFunction(work_item_name, std::move(current_function_));
    
    // Restore previous context
    current_function_ = std::move(saved_function);
    cfg_context_ = saved_cfg_context;
    cfg_context_.current_block = saved_current_block;
    
   // std::cout << "[DEBUG] Work item function " << work_item_name << " registered" << std::endl;
}


void Generator::collect_variables_from_statement(LM::Frontend::AST::Statement& stmt, std::set<std::string>& variables) {
    if (auto block_stmt = dynamic_cast<LM::Frontend::AST::BlockStatement*>(&stmt)) {
        for (const auto& body_stmt : block_stmt->statements) {
            collect_variables_from_statement(*body_stmt, variables);
        }
    } else if (auto expr_stmt = dynamic_cast<LM::Frontend::AST::ExprStatement*>(&stmt)) {
        collect_variables_from_expression(*expr_stmt->expression, variables);
    } else if (auto print_stmt = dynamic_cast<LM::Frontend::AST::PrintStatement*>(&stmt)) {
        for (const auto& arg : print_stmt->arguments) {
            collect_variables_from_expression(*arg, variables);
        }
    }
    // Add other statement types as needed
}


void Generator::collect_variables_from_expression(LM::Frontend::AST::Expression& expr, std::set<std::string>& variables) {
    if (auto var_expr = dynamic_cast<LM::Frontend::AST::VariableExpr*>(&expr)) {
        variables.insert(var_expr->name);
    } else if (auto binary_expr = dynamic_cast<LM::Frontend::AST::BinaryExpr*>(&expr)) {
        collect_variables_from_expression(*binary_expr->left, variables);
        collect_variables_from_expression(*binary_expr->right, variables);
    } else if (auto unary_expr = dynamic_cast<LM::Frontend::AST::UnaryExpr*>(&expr)) {
        collect_variables_from_expression(*unary_expr->right, variables);
    }
    // Add other expression types as needed
}


void Generator::create_and_register_task_function(const std::string& task_name, LM::Frontend::AST::TaskStatement* task_stmt, int64_t loop_value) {
   // std::cout << "[DEBUG] Creating task function: " << task_name << " with loop value " << loop_value << std::endl;
    
    // Save current context
    auto saved_function = std::move(current_function_);
    auto saved_cfg_context = cfg_context_;
    auto saved_current_block = cfg_context_.current_block;
    
    // Create new task function
    current_function_ = std::make_unique<LIR_Function>(task_name, 0);
    cfg_context_.building_cfg = false;
    cfg_context_.current_block = nullptr;
    
    // Initialize task function
    enter_scope();
    
    // Bind loop variable if specified
    if (!task_stmt->loopVar.empty()) {
        // For concurrent tasks, the loop variable should come from register 1 (task context field 1)
        // not from a hardcoded constant. Register 1 will be set up by the scheduler.
        Reg loop_var_reg = 1;  // Use register 1 directly
        bind_variable(task_stmt->loopVar, loop_var_reg);
        auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
        set_register_type(loop_var_reg, int_type);
    }
    
    // Bind channel variable if specified
    if (!task_stmt->channel_param.empty()) {
        // For concurrent tasks, the channel should come from register 2 (task context field 2)
        // Register 2 will be set up by the scheduler.
        Reg channel_reg = 2;  // Use register 2 directly
        bind_variable(task_stmt->channel_param, channel_reg);
        auto channel_type = std::make_shared<::Type>(::TypeTag::Channel);
        set_register_type(channel_reg, channel_type);
       // std::cout << "[DEBUG] Bound channel variable '" << task_stmt->channel_param << "' to register " << channel_reg << std::endl;
    }
    
    // Emit task body
    if (task_stmt->body) {
        emit_stmt(*task_stmt->body);
    }
    
    // Add return to task function
    emit_instruction(LIR_Inst(LIR_Op::Ret, Type::Void, 0, 0, 0));
    
    // Restore context
    exit_scope();
    
    // Register task function
    auto& func_registry = LIR::FunctionRegistry::getInstance();
    func_registry.registerFunction(task_name, std::move(current_function_));
    
    // Restore previous context
    current_function_ = std::move(saved_function);
    cfg_context_ = saved_cfg_context;
    cfg_context_.current_block = saved_current_block;
    
   // std::cout << "[DEBUG] Task function " << task_name << " registered" << std::endl;
}


void Generator::create_and_register_worker_function(const std::string& worker_name, LM::Frontend::AST::WorkerStatement* worker_stmt) {
   // std::cout << "[DEBUG] Creating worker function: " << worker_name << std::endl;
   // std::cout << "[DEBUG] Worker param name: '" << worker_stmt->paramName << "'" << std::endl;
   // std::cout << "[DEBUG] Worker has iterable: " << (worker_stmt->iterable ? "YES" : "NO") << std::endl;
   // std::cout << "[DEBUG] Worker channel_param: '" << worker_stmt->channel_param << "'" << std::endl;
    
    // Save current context
    auto saved_function = std::move(current_function_);
    auto saved_cfg_context = cfg_context_;
    auto saved_current_block = cfg_context_.current_block;
    
    // Create new worker function
    current_function_ = std::make_unique<LIR_Function>(worker_name, 0);
    cfg_context_.building_cfg = false;
    cfg_context_.current_block = nullptr;
    
    // Initialize worker function
    enter_scope();
    
    // Bind worker parameter name if specified
    if (!worker_stmt->paramName.empty()) {
        // For concurrent workers, parameter should come from register 1 (task context field 1)
        // which will contain the current item from iteration
        Reg param_reg = 1;  // Use register 1 directly
        bind_variable(worker_stmt->paramName, param_reg);
        auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
        set_register_type(param_reg, int_type);
       // std::cout << "[DEBUG] Bound worker parameter '" << worker_stmt->paramName << "' to register " << param_reg << std::endl;
    }
    
    // Bind channel variable if specified
    if (!worker_stmt->channel_param.empty()) {
        // For concurrent workers, channel should come from register 2 (task context field 2)
        Reg channel_reg = 2;  // Use register 2 directly
        bind_variable(worker_stmt->channel_param, channel_reg);
        auto channel_type = std::make_shared<::Type>(::TypeTag::Channel);
        set_register_type(channel_reg, channel_type);
       // std::cout << "[DEBUG] Bound channel variable '" << worker_stmt->channel_param << "' to register " << channel_reg << std::endl;
    }
    
    // Bind iterable if available (for worker iteration logic)
    if (worker_stmt->iterable) {
        // Iterable should be available in register 1 (same as parameter for iteration)
        // This allows the worker to access the source iterable for iteration
        Reg iterable_reg = 1;  // Use register 1 for iterable access
        auto iterable_type = std::make_shared<::Type>(::TypeTag::Channel); // Default to channel type
        set_register_type(iterable_reg, iterable_type);
       // std::cout << "[DEBUG] Bound iterable to register " << iterable_reg << std::endl;
    }
    
    // Emit worker body directly (worker will be called in a loop by scheduler)
    if (worker_stmt->body) {
       // std::cout << "[DEBUG] About to emit worker body with " << worker_stmt->body->statements.size() << " statements" << std::endl;
        emit_stmt(*worker_stmt->body);
       // std::cout << "[DEBUG] Worker body emitted successfully" << std::endl;
    }
    
    // Add return to worker function
    emit_instruction(LIR_Inst(LIR_Op::Ret, Type::Void, 0, 0, 0));
    
    // Restore context
    exit_scope();
    
    // Register worker function
    auto& func_registry = LIR::FunctionRegistry::getInstance();
    func_registry.registerFunction(worker_name, std::move(current_function_));
    
    // Restore previous context
    current_function_ = std::move(saved_function);
    cfg_context_ = saved_cfg_context;
    cfg_context_.current_block = saved_current_block;
    
   // std::cout << "[DEBUG] Worker function " << worker_name << " registered" << std::endl;
}


void Generator::emit_task_stmt(LM::Frontend::AST::TaskStatement& stmt) {
   // std::cout << "[DEBUG] Processing TaskStatement" << std::endl;
    
    // Check if we're in a concurrent block - if so, convert to iter for direct execution
    if (!current_concurrent_block_id_.empty()) {
       // std::cout << "[DEBUG] Converting task to iter in concurrent block" << std::endl;
        
        // Create a temporary IterStatement to reuse existing iter logic
        auto temp_iter_stmt = std::make_unique<LM::Frontend::AST::IterStatement>();
        temp_iter_stmt->loopVars = {stmt.loopVar};
        temp_iter_stmt->iterable = stmt.iterable;
        temp_iter_stmt->body = stmt.body;
        
        // Emit as iter statement (direct execution)
        emit_iter_stmt(*temp_iter_stmt);
        return;
    }

    // Check if we're in a parallel block (SharedCell context) or concurrent block
    if (!parallel_block_cell_ids_.empty()) {
       // std::cout << "[DEBUG] TaskStatement within parallel block - using SharedCell approach" << std::endl;
        
        // For task statements within parallel blocks, emit the body directly
        // SharedCell operations will handle variable access automatically
        if (stmt.body) {
            emit_stmt(*stmt.body);
        }
    } else {
       // std::cout << "[DEBUG] TaskStatement within concurrent block - using task function approach" << std::endl;
        
        // For task statements within concurrent blocks, create separate task functions
        if (stmt.body) {
            emit_stmt(*stmt.body);
        }
    }
}


void Generator::emit_task_init_and_step(LM::Frontend::AST::TaskStatement& task, size_t task_id, Reg contexts_reg, Reg channel_reg, Reg counter_reg, int64_t loop_var_value) {
    auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
    
    // Load task_id as the context register value
    Reg task_context_reg = allocate_register();
    ValuePtr task_id_val = std::make_shared<Value>(int_type, int64_t(task_id));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, task_context_reg, task_id_val));
    set_register_type(task_context_reg, int_type);
    
    // Initialize task context
    emit_instruction(LIR_Inst(LIR_Op::TaskContextInit, task_context_reg, task_context_reg, 0));
    
    // Set task ID in context (field 0)
    Reg task_id_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, task_id_reg, task_id_val));
    set_register_type(task_id_reg, int_type);
    emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, task_id_reg, task_context_reg, 0, 0));
    
    // Set loop variable value in context (field 1)
    ValuePtr loop_var_val = std::make_shared<Value>(int_type, int64_t(loop_var_value));
    Reg loop_var_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, loop_var_reg, loop_var_val));
    set_register_type(loop_var_reg, int_type);
    emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, loop_var_reg, task_context_reg, 0, 1));
    
    // Bind the loop variable in the current scope
    if (!task.loopVar.empty()) {
        bind_variable(task.loopVar, loop_var_reg);
    }
    
    // Set channel index in context (field 2)
    emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, channel_reg, task_context_reg, 0, 2));
    
    // Load current shared counter value and set it in context (field 3)
    Reg current_counter_reg = allocate_register();
    // Load current shared counter from global storage
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, current_counter_reg, 
                              std::make_shared<Value>(int_type, int64_t(0))));
    emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, current_counter_reg, task_context_reg, 0, 3));
    
    // Instead of copying task function instructions, store the task function name
    // The scheduler will call the task function directly from the FunctionRegistry
    if (!task.task_function_name.empty()) {
        auto& func_registry = LIR::FunctionRegistry::getInstance();
        if (func_registry.hasFunction(task.task_function_name)) {
            
            // Store the task function name in the task context for the scheduler to call
            Reg func_name_reg = allocate_register();
            auto string_type = std::make_shared<::Type>(::TypeTag::String);
            ValuePtr func_name_val = std::make_shared<Value>(string_type, task.task_function_name);
            emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::Ptr, func_name_reg, func_name_val));
            set_register_type(func_name_reg, string_type);
            
            // Store the function name in task context field 4 (after task_id, loop_var, channel, shared_counter)
            emit_instruction(LIR_Inst(LIR_Op::TaskSetField, 0, task_context_reg, func_name_reg, 4));
            
        } else {
           // std::cout << "[ERROR] Task function '" << task.task_function_name << "' not found in FunctionRegistry" << std::endl;
        }
    } else {
       // std::cout << "[ERROR] No task function name for task " << task_id << std::endl;
    }
}


void Generator::emit_worker_stmt(LM::Frontend::AST::WorkerStatement& stmt) {
    // Workers are handled during the lowering phase, similar to tasks
    // This function should not be called during normal statement emission
   // std::cout << "[DEBUG] Worker statement encountered during emission - should be handled in lowering phase" << std::endl;
}


void Generator::lower_task_body(LM::Frontend::AST::TaskStatement& stmt) {
    // Create separate LIR function for this task body
    std::string task_func_name = "_task_" + std::to_string(reinterpret_cast<uintptr_t>(&stmt));
    
    // Task functions use fixed parameter layout: task_id, loop_var, channel, shared_cell_id
    uint32_t param_count = 4;
    
    auto func = std::make_unique<LIR_Function>(task_func_name, param_count);
    
    // Save current context
    auto saved_function = std::move(current_function_);
    auto saved_next_register = next_register_;
    auto saved_scope_stack = std::move(scope_stack_);
    auto saved_register_types = std::move(register_types_);
    
    // Set up function context
    current_function_ = std::move(func);
    next_register_ = param_count;  // Start after all parameters
    scope_stack_.clear();
    register_types_.clear();
    
    // Enter function scope
    enter_scope();
    
    // Bind task parameters to registers
    bind_variable("_task_id", static_cast<Reg>(0));
    bind_variable("_loop_var", static_cast<Reg>(1));
    bind_variable("_channel", static_cast<Reg>(2));
    bind_variable("_shared_cell_id", static_cast<Reg>(3));  // Contains SharedCell ID
    
    // Bind loop variable name if specified
    if (!stmt.loopVar.empty()) {
        bind_variable(stmt.loopVar, static_cast<Reg>(1));
    }
    
    auto saved_parallel_block_cell_ids = parallel_block_cell_ids_;
    // Emit task body from AST
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Restore SharedCell context
    parallel_block_cell_ids_ = saved_parallel_block_cell_ids;
    
    // Ensure function has a return instruction
    if (current_function_->instructions.empty() || 
        !current_function_->instructions.back().isReturn()) {
        // Implicit return of 0 if no explicit return
        Reg return_reg = allocate_register();
        auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
        ValuePtr zero_val = std::make_shared<Value>(int_type, int64_t(0));
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, return_reg, zero_val));
        emit_instruction(LIR_Inst(LIR_Op::Ret, return_reg, 0, 0));
    }
    
    exit_scope();
    
    // Register the task function with the FunctionRegistry instead of storing locally
    auto& func_registry = LIR::FunctionRegistry::getInstance();
    func_registry.registerFunction(task_func_name, std::move(current_function_));
    
    // Store the task function name for later reference
    stmt.task_function_name = task_func_name;

    // Restore context
    current_function_ = std::move(saved_function);
    next_register_ = saved_next_register;
    scope_stack_ = std::move(saved_scope_stack);
    register_types_ = std::move(saved_register_types);
}


void Generator::lower_worker_body(LM::Frontend::AST::WorkerStatement& stmt) {
    // Create separate LIR function for this worker body
    std::string worker_func_name = "_worker_" + std::to_string(reinterpret_cast<uintptr_t>(&stmt));
    auto func = std::make_unique<LIR_Function>(worker_func_name, 4); // task_id, loop_var, channel, shared_counter
    
    // Save current context
    auto saved_function = std::move(current_function_);
    auto saved_next_register = next_register_;
    auto saved_scope_stack = std::move(scope_stack_);
    auto saved_register_types = std::move(register_types_);
    
    // Set up function context
    current_function_ = std::move(func);
    next_register_ = 4;  // Start after parameters
    scope_stack_.clear();
    register_types_.clear();
    
    // Enter function scope
    enter_scope();
    
    // Bind worker parameters to registers
    bind_variable("_task_id", static_cast<Reg>(0));
    bind_variable("_loop_var", static_cast<Reg>(1));
    bind_variable("_channel", static_cast<Reg>(2));
    bind_variable("_shared_counter", static_cast<Reg>(3));
    
   
    // Bind worker parameter name if specified
    if (!stmt.paramName.empty()) {
        bind_variable(stmt.paramName, static_cast<Reg>(1)); // Use loop_var register for worker parameter
    }
    
    // Bind iterable if available for iteration
    if (stmt.iterable) {

        // For now, bind the iterable to a special variable that the worker can access
        // In a full implementation, this would involve proper iteration setup
        bind_variable("_iterable", static_cast<Reg>(1));
    }
    
    // Emit worker body from AST
    if (stmt.body) {
       // std::cout << "[DEBUG] Emitting worker body with " << stmt.body->statements.size() << " statements" << std::endl;
        emit_stmt(*stmt.body);
       // std::cout << "[DEBUG] Worker body emitted, function has " << current_function_->instructions.size() << " instructions" << std::endl;
    }
    
    // Ensure function has a return instruction
    if (current_function_->instructions.empty() || 
        !current_function_->instructions.back().isReturn()) {
        // Implicit return of 0 if no explicit return
        Reg return_reg = allocate_register();
        auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
        ValuePtr zero_val = std::make_shared<Value>(int_type, int64_t(0));
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, return_reg, zero_val));
        emit_instruction(LIR_Inst(LIR_Op::Ret, return_reg, 0, 0));
    }
    
    exit_scope();
    
    // Register the worker function with the FunctionRegistry
    auto& func_registry = LIR::FunctionRegistry::getInstance();
    func_registry.registerFunction(worker_func_name, std::move(current_function_));
    
    // Store the worker function name for later reference
    stmt.worker_function_name = worker_func_name;
    
   // std::cout << "[DEBUG] Worker function '" << worker_func_name << "' registered with FunctionRegistry" << std::endl;
    
    // Restore context
    current_function_ = std::move(saved_function);
    next_register_ = saved_next_register;
    scope_stack_ = std::move(saved_scope_stack);
    register_types_ = std::move(saved_register_types);
}

// Error and Result type expression handlers - Unified Type? system

void Generator::find_accessed_variables_in_concurrent(LM::Frontend::AST::ConcurrentStatement& stmt, std::set<std::string>& accessed_variables) {
   // std::cout << "[DEBUG] find_accessed_variables_in_concurrent started" << std::endl;
    if (stmt.body) {
       // std::cout << "[DEBUG] Statement has body with " << stmt.body->statements.size() << " statements" << std::endl;
        find_accessed_variables_recursive(stmt.body->statements, accessed_variables);
       // std::cout << "[DEBUG] find_accessed_variables_recursive completed" << std::endl;
    }
   // std::cout << "[DEBUG] find_accessed_variables_in_concurrent completed" << std::endl;
}


void Generator::find_accessed_variables_recursive(const std::vector<std::shared_ptr<LM::Frontend::AST::Statement>>& statements, std::set<std::string>& accessed_variables) {
    static int recursion_depth = 0;
    recursion_depth++;
   // std::cout << "[DEBUG] find_accessed_variables_recursive started with " << statements.size() << " statements, depth: " << recursion_depth << std::endl;
    
    if (recursion_depth > 10) {
       // std::cout << "[DEBUG] RECURSION DEPTH TOO HIGH, ABORTING" << std::endl;
        recursion_depth--;
        return;
    }
    
    for (const auto& stmt : statements) {
       // std::cout << "[DEBUG] Processing statement type: " << typeid(*stmt.get()).name() << std::endl;
        if (auto task_stmt = dynamic_cast<LM::Frontend::AST::TaskStatement*>(stmt.get())) {
           // std::cout << "[DEBUG] Found TaskStatement" << std::endl;
            if (task_stmt->body) {
                find_accessed_variables_recursive(task_stmt->body->statements, accessed_variables);
            }
        } else if (auto expr_stmt = dynamic_cast<LM::Frontend::AST::ExprStatement*>(stmt.get())) {
           // std::cout << "[DEBUG] Found ExprStatement" << std::endl;
            if (expr_stmt->expression) {
                find_accessed_variables_in_expr(*expr_stmt->expression, accessed_variables);
            }
        } else if (auto block_stmt = dynamic_cast<LM::Frontend::AST::BlockStatement*>(stmt.get())) {
           // std::cout << "[DEBUG] Found BlockStatement" << std::endl;
            find_accessed_variables_recursive(block_stmt->statements, accessed_variables);
        } else {
           // std::cout << "[DEBUG] Statement type not handled: " << typeid(*stmt.get()).name() << std::endl;
        }
        // Add other statement types as needed
    }
    
   // std::cout << "[DEBUG] find_accessed_variables_recursive completed, depth: " << recursion_depth << std::endl;
    recursion_depth--;
}


void Generator::find_accessed_variables_in_expr(const LM::Frontend::AST::Expression& expr, std::set<std::string>& accessed_variables) {
    if (auto var_expr = dynamic_cast<const LM::Frontend::AST::VariableExpr*>(&expr)) {
        // Check if this variable is defined in the current scope or outer scope
        // For now, we'll capture all variable expressions
        accessed_variables.insert(var_expr->name);
    } else if (auto assign_expr = dynamic_cast<const LM::Frontend::AST::AssignExpr*>(&expr)) {
        // Capture both the target variable and the right-hand side expression
        accessed_variables.insert(assign_expr->name);
        if (assign_expr->value) {
            find_accessed_variables_in_expr(*assign_expr->value, accessed_variables);
        }
    } else if (auto binary_expr = dynamic_cast<const LM::Frontend::AST::BinaryExpr*>(&expr)) {
        if (binary_expr->left) {
            find_accessed_variables_in_expr(*binary_expr->left, accessed_variables);
        }
        if (binary_expr->right) {
            find_accessed_variables_in_expr(*binary_expr->right, accessed_variables);
        }
    } else if (auto call_expr = dynamic_cast<const LM::Frontend::AST::CallExpr*>(&expr)) {
        if (call_expr->callee) {
            find_accessed_variables_in_expr(*call_expr->callee, accessed_variables);
        }
        for (const auto& arg : call_expr->arguments) {
            if (arg) {
                find_accessed_variables_in_expr(*arg, accessed_variables);
            }
        }
    } else if (auto interp_expr = dynamic_cast<const LM::Frontend::AST::InterpolatedStringExpr*>(&expr)) {
        for (const auto& part : interp_expr->parts) {
            if (std::holds_alternative<std::shared_ptr<LM::Frontend::AST::Expression>>(part)) {
                auto expr_part = std::get<std::shared_ptr<LM::Frontend::AST::Expression>>(part);
                if (expr_part) {
                    find_accessed_variables_in_expr(*expr_part, accessed_variables);
                }
            }
        }
    }
}


void Generator::emit_concurrent_worker_init(LM::Frontend::AST::WorkerStatement& worker, size_t worker_id, Reg scheduler_reg, Reg channel_reg) {
    auto int_type = std::make_shared<::Type>(::TypeTag::Int64);
    
    // Create worker context for scheduler
    Reg worker_context_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::TaskContextAlloc, worker_context_reg, 0, 0));
    
    // Set worker ID
    Reg worker_id_reg = allocate_register();
    ValuePtr worker_id_val = std::make_shared<Value>(int_type, static_cast<int64_t>(worker_id));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, worker_id_reg, worker_id_val));
    emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, 0, worker_context_reg, worker_id_reg, 0));
    
    // Set parameter name if specified
    if (!worker.paramName.empty()) {
        Reg param_reg = allocate_register();
        ValuePtr param_val = std::make_shared<Value>(int_type, static_cast<int64_t>(0));
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, Type::I64, param_reg, param_val));
        emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, 0, worker_context_reg, param_reg, 1));
    }
    
    // Set channel register
    emit_instruction(LIR_Inst(LIR_Op::TaskSetField, Type::Void, 0, worker_context_reg, channel_reg, 2));
    
    // Add worker to scheduler
    emit_instruction(LIR_Inst(LIR_Op::SchedulerAddTask, Type::Void, scheduler_reg, worker_context_reg, 0));
    
}

// Frame system visibility helper

} // namespace LIR
} // namespace LM

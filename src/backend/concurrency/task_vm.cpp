#include "task_vm.hh"
#include "concurrency_state.hh"
#include "../vm.hh"
#include <stdexcept>
#include <chrono>
#include <future>

// TaskVM Implementation

TaskVM::TaskVM(std::unique_ptr<TaskContext> ctx,
               std::shared_ptr<ConcurrentErrorCollector> error_collector,
               std::shared_ptr<Channel<ValuePtr>> result_channel,
               std::shared_ptr<Channel<ErrorValue>> error_channel)
    : VM(false), // Don't create runtime for task VMs
      context_(std::move(ctx)),
      error_collector_(error_collector),
      result_channel_(result_channel),
      error_channel_(error_channel) {
    
    if (!context_) {
        throw std::invalid_argument("TaskContext cannot be null");
    }
    
    if (!error_collector_) {
        throw std::invalid_argument("ConcurrentErrorCollector cannot be null");
    }
    
    // Set up task environment and error context
    setupTaskEnvironment();
    copyErrorFrames();
}

TaskVM::~TaskVM() {
    cleanupTaskResources();
}

ValuePtr TaskVM::executeTask() {
    if (task_cancelled_.load()) {
        return nullptr;
    }
    
    start_time_ = std::chrono::steady_clock::now();
    
    try {
        // Check for cancellation before starting
        if (shouldCancel()) {
            cancelTask();
            return nullptr;
        }
        
        // Compile and execute the task body
        ValuePtr result = nullptr;
        if (context_->task_body) {
            // Compile the task body AST to bytecode
            result = compileAndExecuteTaskBody();
        } else if (!context_->task_bytecode.empty()) {
            // Fallback to pre-compiled bytecode
            result = execute(context_->task_bytecode);
        } else {
            // Create a simple default task that prints the loop variable
            result = executeDefaultTask();
        }
        
        // Check for cancellation after execution
        if (shouldCancel()) {
            cancelTask();
            return nullptr;
        }
        
        // Complete the task successfully
        completeTask(result);
        return result;
        
    } catch (const std::exception& e) {
        // Handle task execution error
        ErrorValue error;
        error.errorType = "TaskExecutionError";
        error.message = e.what();
        error.sourceLocation = 0; // Could be enhanced with actual location
        
        handleTaskError(error);
        completeTask(nullptr);
        return nullptr;
    }
}

std::future<ValuePtr> TaskVM::executeTaskAsync() {
    return std::async(std::launch::async, [this]() {
        return executeTask();
    });
}

void TaskVM::cancelTask() {
    if (!task_cancelled_.exchange(true)) {
        // First time cancelling
        end_time_ = std::chrono::steady_clock::now();
        
        // Send cancellation error if error channel is configured
        if (error_channel_) {
            ErrorValue error;
            error.errorType = "TaskCancelled";
            error.message = "Task was cancelled";
            sendError(error);
        }
        
        cleanupTaskResources();
    }
}

size_t TaskVM::getTaskId() const {
    return context_->task_id;
}

const std::string& TaskVM::getLoopVariable() const {
    return context_->loop_var;
}

ValuePtr TaskVM::getIterationValue() const {
    return context_->iteration_value;
}

std::chrono::milliseconds TaskVM::getExecutionDuration() const {
    if (start_time_.time_since_epoch().count() == 0) {
        return std::chrono::milliseconds(0);
    }
    
    auto end = task_completed_.load() ? end_time_ : std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start_time_);
}

void TaskVM::handleTaskError(const ErrorValue& error) {
    // Add error to the shared error collector
    if (error_collector_) {
        error_collector_->addError(error);
    }
    
    // Send error to error channel if configured
    sendError(error);
    
    // Handle error according to the task's error strategy
    switch (context_->error_strategy) {
        case ErrorHandlingStrategy::Stop:
            // For Stop strategy, the error will cause block termination
            // This is handled at the block level
            break;
            
        case ErrorHandlingStrategy::Auto:
            // For Auto strategy, continue with other tasks
            // Error is collected but doesn't stop execution
            break;
            
        case ErrorHandlingStrategy::Retry:
            // For Retry strategy, the task scheduler will handle retries
            // This is handled at the block level
            break;
    }
}

void TaskVM::setupTaskEnvironment() {
    // Create isolated environment for this task
    if (context_->task_env) {
        environment = context_->task_env;
    } else {
        // Create new isolated environment
        context_->task_env = std::make_shared<Environment>(globals);
        environment = context_->task_env;
    }
    
    // Set up loop variable if specified
    if (!context_->loop_var.empty() && context_->iteration_value) {
        environment->define(context_->loop_var, context_->iteration_value);
    }
}

void TaskVM::copyErrorFrames() {
    // Copy error frames from the task context to this VM
    // This ensures that error handling context is preserved across thread boundaries
    for (const auto& frame : context_->error_frames) {
        pushErrorFrame(frame.handlerAddress, frame.expectedErrorType, frame.functionName);
    }
}

ValuePtr TaskVM::compileAndExecuteTaskBody() {
    if (!context_->task_body) {
        return nullptr;
    }
    
    std::cout << "[DEBUG] TaskVM: Compiling and executing task body AST" << std::endl;
    
    // TODO: Implement AST to bytecode compilation in TaskVM
    // For now, fall back to default task
    return executeDefaultTask();
}

ValuePtr TaskVM::executeDefaultTask() {
    // Create simple bytecode that prints the loop variable
    std::vector<Instruction> taskBytecode;
    
    // Push "Task with i = "
    Instruction pushString;
    pushString.opcode = Opcode::PUSH_STRING;
    pushString.stringValue = "Task with " + context_->loop_var + " = ";
    taskBytecode.push_back(pushString);
    
    // Push the iteration value as string
    Instruction pushValue;
    pushValue.opcode = Opcode::PUSH_STRING;
    pushValue.stringValue = context_->iteration_value->toString();
    taskBytecode.push_back(pushValue);
    
    // Concatenate
    Instruction concat;
    concat.opcode = Opcode::CONCAT;
    taskBytecode.push_back(concat);
    
    // Print
    Instruction print;
    print.opcode = Opcode::PRINT;
    taskBytecode.push_back(print);
    
    // Execute the bytecode
    return execute(taskBytecode);
}

void TaskVM::cleanupTaskResources() {
    // Clean up any task-specific resources
    // This is called automatically in the destructor
    
    // Clear the task environment to release references
    if (context_ && context_->task_env) {
        // Don't clear the environment as it might be needed for result access
        // Just ensure we don't hold unnecessary references
    }
    
    // Clear bytecode to free memory
    if (context_) {
        context_->task_bytecode.clear();
        context_->error_frames.clear();
    }
    
    // Close channels if we're the last reference
    if (result_channel_) {
        // Don't close here as other tasks might still be using it
        result_channel_.reset();
    }
    
    if (error_channel_) {
        // Don't close here as other tasks might still be using it
        error_channel_.reset();
    }
    
    // Clear completion callback to avoid holding references
    completion_callback_ = nullptr;
}

void TaskVM::sendResult(ValuePtr result) {
    if (result_channel_ && result) {
        try {
            result_channel_->send(result);
        } catch (const std::exception& e) {
            // Log error but don't fail the task
            // Could be enhanced with proper logging
        }
    }
}

void TaskVM::sendError(const ErrorValue& error) {
    if (error_channel_) {
        try {
            error_channel_->send(error);
        } catch (const std::exception& e) {
            // Log error but don't fail the task
            // Could be enhanced with proper logging
        }
    }
}

void TaskVM::completeTask(ValuePtr result) {
    if (!task_completed_.exchange(true)) {
        // First time completing
        end_time_ = std::chrono::steady_clock::now();
        task_result_ = result;
        
        // Send result to channel if configured
        sendResult(result);
        
        // Mark task as completed in the context
        context_->completed.store(true);
        
        // Call completion callback if set
        if (completion_callback_) {
            completion_callback_(getTaskId(), result, result != nullptr);
        }
    }
}

void TaskVM::setCompletionCallback(std::function<void(size_t task_id, ValuePtr result, bool success)> callback) {
    completion_callback_ = std::move(callback);
}

bool TaskVM::shouldCancel() const {
    // Check if task was explicitly cancelled
    if (task_cancelled_.load()) {
        return true;
    }
    
    // Check if context indicates cancellation
    if (context_->cancelled.load()) {
        return true;
    }
    
    // Could add timeout checking here if needed
    // For now, rely on external cancellation mechanisms
    
    return false;
}

// EnhancedTaskContext Implementation

EnhancedTaskContext::EnhancedTaskContext(std::unique_ptr<TaskContext> base)
    : base_context_(std::move(base)) {
    
    if (!base_context_) {
        throw std::invalid_argument("Base TaskContext cannot be null");
    }
}

EnhancedTaskContext::~EnhancedTaskContext() {
    executeCleanup();
}

void EnhancedTaskContext::setupIsolatedEnvironment(std::shared_ptr<Environment> parent_env) {
    // Create isolated environment that inherits from parent but is separate
    isolated_environment_ = std::make_shared<Environment>(parent_env);
    
    // Set up the loop variable in the isolated environment
    if (!base_context_->loop_var.empty() && base_context_->iteration_value) {
        isolated_environment_->define(base_context_->loop_var, base_context_->iteration_value);
    }
    
    // Update the base context to use the isolated environment
    base_context_->task_env = isolated_environment_;
}

void EnhancedTaskContext::compileBytecode(const std::vector<Instruction>& instructions,
                                        size_t start_ip, size_t end_ip) {
    // Extract the relevant portion of bytecode for this task
    if (start_ip >= instructions.size() || end_ip > instructions.size() || start_ip >= end_ip) {
        throw std::invalid_argument("Invalid bytecode range");
    }
    
    compiled_bytecode_.clear();
    compiled_bytecode_.reserve(end_ip - start_ip);
    
    for (size_t i = start_ip; i < end_ip; ++i) {
        compiled_bytecode_.push_back(instructions[i]);
    }
    
    // Update the base context with compiled bytecode
    base_context_->task_bytecode = compiled_bytecode_;
}

void EnhancedTaskContext::addCleanupFunction(std::function<void()> cleanup) {
    std::lock_guard<std::mutex> lock(cleanup_mutex_);
    cleanup_functions_.push_back(std::move(cleanup));
}

void EnhancedTaskContext::executeCleanup() {
    std::lock_guard<std::mutex> lock(cleanup_mutex_);
    
    // Execute cleanup functions in reverse order (LIFO)
    for (auto it = cleanup_functions_.rbegin(); it != cleanup_functions_.rend(); ++it) {
        try {
            (*it)();
        } catch (const std::exception& e) {
            // Log error but continue with other cleanup functions
            // Could be enhanced with proper logging
        }
    }
    
    cleanup_functions_.clear();
}

// TaskVMFactory Implementation

std::unique_ptr<TaskVM> TaskVMFactory::createTaskVM(
    std::unique_ptr<TaskContext> context,
    std::shared_ptr<ConcurrentErrorCollector> error_collector,
    std::shared_ptr<Channel<ValuePtr>> result_channel,
    std::shared_ptr<Channel<ErrorValue>> error_channel) {
    
    return std::make_unique<TaskVM>(
        std::move(context),
        error_collector,
        result_channel,
        error_channel
    );
}

std::vector<std::unique_ptr<TaskVM>> TaskVMFactory::createTaskVMs(
    std::vector<std::unique_ptr<TaskContext>> contexts,
    std::shared_ptr<ConcurrentErrorCollector> error_collector,
    std::shared_ptr<Channel<ValuePtr>> result_channel,
    std::shared_ptr<Channel<ErrorValue>> error_channel) {
    
    std::vector<std::unique_ptr<TaskVM>> task_vms;
    task_vms.reserve(contexts.size());
    
    for (auto& context : contexts) {
        task_vms.push_back(createTaskVM(
            std::move(context),
            error_collector,
            result_channel,
            error_channel
        ));
    }
    
    return task_vms;
}
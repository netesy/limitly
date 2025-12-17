#ifndef TASK_VM_H
#define TASK_VM_H

#include "../vm/vm.hh"
#include "concurrency_state.hh"
#include "concurrency_runtime.hh"
#include <memory>
#include <future>

// Forward declarations
class Environment;
struct TaskContext;

/**
 * Isolated VM instance for executing tasks in concurrent/parallel blocks
 * 
 * TaskVM provides complete isolation for task execution, including:
 * - Separate environment and variable scope
 * - Independent error handling context
 * - Task-specific resource management
 * - Thread-safe result collection
 */
class TaskVM : public VM {
private:
    std::unique_ptr<TaskContext> context_;
    std::shared_ptr<ConcurrentErrorCollector> error_collector_;
    std::shared_ptr<Channel<ValuePtr>> result_channel_;
    std::shared_ptr<Channel<ErrorValue>> error_channel_;
    
    // Task execution state
    std::atomic<bool> task_completed_{false};
    std::atomic<bool> task_cancelled_{false};
    ValuePtr task_result_;
    std::exception_ptr task_exception_;
    
    // Completion callback
    std::function<void(size_t task_id, ValuePtr result, bool success)> completion_callback_;
    
    // Performance tracking
    std::chrono::steady_clock::time_point start_time_;
    std::chrono::steady_clock::time_point end_time_;

public:
    /**
     * Constructor for TaskVM
     * @param ctx Task context with execution parameters
     * @param error_collector Shared error collector for the block
     * @param result_channel Optional channel for sending results
     * @param error_channel Optional channel for sending errors
     */
    TaskVM(std::unique_ptr<TaskContext> ctx,
           std::shared_ptr<ConcurrentErrorCollector> error_collector,
           std::shared_ptr<Channel<ValuePtr>> result_channel = nullptr,
           std::shared_ptr<Channel<ErrorValue>> error_channel = nullptr);

    /**
     * Destructor - ensures proper cleanup
     */
    ~TaskVM();

    // Non-copyable
    TaskVM(const TaskVM&) = delete;
    TaskVM& operator=(const TaskVM&) = delete;

    /**
     * Execute the task bytecode and return the result
     * This is the main entry point for task execution
     * @return Task execution result or nullptr on error
     */
    ValuePtr executeTask();

    /**
     * Execute the task asynchronously and return a future
     * @return Future containing the task result
     */
    std::future<ValuePtr> executeTaskAsync();

    /**
     * Cancel the task execution
     */
    void cancelTask();

    /**
     * Check if the task has completed
     */
    bool isCompleted() const noexcept { return task_completed_.load(); }

    /**
     * Check if the task was cancelled
     */
    bool isCancelled() const noexcept { return task_cancelled_.load(); }

    /**
     * Get the task ID
     */
    size_t getTaskId() const;

    /**
     * Get the loop variable name for this task
     */
    const std::string& getLoopVariable() const;

    /**
     * Get the iteration value for this task
     */
    ValuePtr getIterationValue() const;

    /**
     * Get task execution duration (only valid after completion)
     */
    std::chrono::milliseconds getExecutionDuration() const;

    /**
     * Handle task-specific errors
     * @param error The error that occurred
     */
    void handleTaskError(const ErrorValue& error);

    /**
     * Set completion callback for task result handling
     * @param callback Function to call when task completes
     */
    void setCompletionCallback(std::function<void(size_t task_id, ValuePtr result, bool success)> callback);

    /**
     * Handle task completion (success or failure)
     */
    void completeTask(ValuePtr result = nullptr);

private:
    /**
     * Set up the task environment with loop variables and isolation
     */
    void setupTaskEnvironment();

    /**
     * Copy error frames from the main VM context to this task
     */
    void copyErrorFrames();

    /**
     * Clean up task resources after execution
     */
    void cleanupTaskResources();

    /**
     * Compile and execute the task body AST
     */
    ValuePtr compileAndExecuteTaskBody();

    /**
     * Execute a default task that prints the loop variable
     */
    ValuePtr executeDefaultTask();

    /**
     * Send result to result channel if configured
     */
    void sendResult(ValuePtr result);

    /**
     * Send error to error channel if configured
     */
    void sendError(const ErrorValue& error);

private:
    /**
     * Check if task should be cancelled (timeout, external cancellation)
     */
    bool shouldCancel() const;
};

/**
 * Enhanced TaskContext with additional execution support
 */
class EnhancedTaskContext {
private:
    std::unique_ptr<TaskContext> base_context_;
    
    // Additional execution state
    std::shared_ptr<Environment> isolated_environment_;
    std::vector<Instruction> compiled_bytecode_;
    
    // Resource tracking
    std::vector<std::function<void()>> cleanup_functions_;
    mutable std::mutex cleanup_mutex_;

public:
    /**
     * Constructor from base TaskContext
     */
    explicit EnhancedTaskContext(std::unique_ptr<TaskContext> base);

    /**
     * Destructor - executes cleanup functions
     */
    ~EnhancedTaskContext();

    // Non-copyable
    EnhancedTaskContext(const EnhancedTaskContext&) = delete;
    EnhancedTaskContext& operator=(const EnhancedTaskContext&) = delete;

    /**
     * Get the base task context
     */
    TaskContext* getBaseContext() { return base_context_.get(); }
    const TaskContext* getBaseContext() const { return base_context_.get(); }

    /**
     * Set up isolated environment for task execution
     */
    void setupIsolatedEnvironment(std::shared_ptr<Environment> parent_env);

    /**
     * Get the isolated environment
     */
    std::shared_ptr<Environment> getIsolatedEnvironment() { return isolated_environment_; }

    /**
     * Compile task bytecode from instruction stream
     */
    void compileBytecode(const std::vector<Instruction>& instructions, 
                        size_t start_ip, size_t end_ip);

    /**
     * Get compiled bytecode
     */
    const std::vector<Instruction>& getBytecode() const { return compiled_bytecode_; }

    /**
     * Add a cleanup function to be called on destruction
     */
    void addCleanupFunction(std::function<void()> cleanup);

    /**
     * Execute all cleanup functions immediately
     */
    void executeCleanup();
};

/**
 * Factory for creating TaskVM instances
 */
class TaskVMFactory {
public:
    /**
     * Create a TaskVM instance for the given context
     */
    static std::unique_ptr<TaskVM> createTaskVM(
        std::unique_ptr<TaskContext> context,
        std::shared_ptr<ConcurrentErrorCollector> error_collector,
        std::shared_ptr<Channel<ValuePtr>> result_channel = nullptr,
        std::shared_ptr<Channel<ErrorValue>> error_channel = nullptr);

    /**
     * Create multiple TaskVM instances for batch execution
     */
    static std::vector<std::unique_ptr<TaskVM>> createTaskVMs(
        std::vector<std::unique_ptr<TaskContext>> contexts,
        std::shared_ptr<ConcurrentErrorCollector> error_collector,
        std::shared_ptr<Channel<ValuePtr>> result_channel = nullptr,
        std::shared_ptr<Channel<ErrorValue>> error_channel = nullptr);
};

#endif // TASK_VM_H
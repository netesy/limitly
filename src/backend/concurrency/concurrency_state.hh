#ifndef CONCURRENCY_STATE_H
#define CONCURRENCY_STATE_H

#include "concurrency_runtime.hh"
#include "../value.hh"
#include "../../frontend/ast.hh"
#include <memory>
#include <stack>
#include <vector>
#include <string>
#include <chrono>
#include <atomic>

// Forward declarations
class Environment;
struct Instruction;
struct Type;
using TypePtr = std::shared_ptr<Type>;

// ErrorFrame from VM - we'll use a forward declaration to avoid circular dependency
struct ErrorFrame {
    size_t handlerAddress;      // Bytecode address of error handler
    size_t stackBase;           // Stack position when frame created
    TypePtr expectedErrorType;  // Expected error type for this frame
    std::string functionName;   // Function name for debugging
    
    ErrorFrame(size_t addr, size_t base, TypePtr type, const std::string& name = "")
        : handlerAddress(addr), stackBase(base), expectedErrorType(type), functionName(name) {}
};

/**
 * Execution modes for concurrent/parallel blocks
 */
enum class ExecutionMode {
    Batch,   // Execute all tasks and wait for completion
    Stream,  // Process input stream through workers
    Async    // Asynchronous execution with futures
};

/**
 * Block types for concurrent execution
 */
enum class BlockType {
    Parallel,    // CPU-bound parallel execution
    Concurrent   // I/O-bound concurrent execution
};

/**
 * Task context for isolated task execution
 */
struct TaskContext {
    size_t task_id;
    std::string loop_var;
    ValuePtr iteration_value;
    std::shared_ptr<Environment> task_env;
    std::vector<Instruction> task_bytecode;
    
    // Task body AST for compilation in TaskVM
    std::shared_ptr<AST::BlockStatement> task_body;
    
    // Error handling context
    std::vector<struct ErrorFrame> error_frames;
    ErrorHandlingStrategy error_strategy;
    std::shared_ptr<Channel<ErrorValue>> error_channel;
    
    // Task lifecycle
    std::atomic<bool> completed{false};
    std::atomic<bool> cancelled{false};
    
    TaskContext(size_t id, const std::string& var, ValuePtr value)
        : task_id(id), loop_var(var), iteration_value(value),
          error_strategy(ErrorHandlingStrategy::Stop) {}
};

/**
 * State for managing concurrent/parallel block execution
 */
struct BlockExecutionState {
    BlockType type;
    ExecutionMode mode = ExecutionMode::Batch;
    size_t cores = 0; // 0 = auto-detect
    ErrorHandlingStrategy error_strategy = ErrorHandlingStrategy::Stop;
    std::chrono::milliseconds timeout{0}; // 0 = no timeout
    std::chrono::milliseconds grace_period{500};
    TimeoutAction timeout_action = TimeoutAction::Partial;
    
    // Communication
    std::shared_ptr<Channel<ValuePtr>> output_channel;
    std::string output_channel_name;
    
    // Task management
    std::vector<std::unique_ptr<TaskContext>> tasks;
    std::atomic<size_t> completed_tasks{0};
    std::atomic<size_t> failed_tasks{0};
    std::atomic<size_t> total_tasks{0};
    
    // Timing
    std::chrono::steady_clock::time_point start_time;
    std::chrono::steady_clock::time_point timeout_deadline;
    
    // Results collection
    std::vector<ValuePtr> results;
    mutable std::mutex results_mutex;
    
    BlockExecutionState(BlockType block_type) : type(block_type) {
        start_time = std::chrono::steady_clock::now();
    }
    
    /**
     * Set timeout and calculate deadline
     */
    void setTimeout(std::chrono::milliseconds timeout_ms) {
        timeout = timeout_ms;
        if (timeout.count() > 0) {
            timeout_deadline = start_time + timeout;
        }
    }
    
    /**
     * Check if timeout has been reached
     */
    bool isTimedOut() const {
        if (timeout.count() == 0) return false;
        return std::chrono::steady_clock::now() >= timeout_deadline;
    }
    
    /**
     * Add a result in a thread-safe manner
     */
    void addResult(ValuePtr result) {
        std::lock_guard<std::mutex> lock(results_mutex);
        results.push_back(result);
    }
    
    /**
     * Get all results (returns a copy for thread safety)
     */
    std::vector<ValuePtr> getResults() const {
        std::lock_guard<std::mutex> lock(results_mutex);
        return results;
    }
    
    /**
     * Check if all tasks are completed
     */
    bool allTasksCompleted() const {
        return completed_tasks.load() >= total_tasks.load();
    }
    
    /**
     * Get completion percentage (0.0 to 1.0)
     */
    double getCompletionPercentage() const {
        size_t total = total_tasks.load();
        if (total == 0) return 1.0;
        return static_cast<double>(completed_tasks.load()) / total;
    }
};

/**
 * Performance and debugging statistics for concurrency execution
 */
struct ConcurrencyStats {
    std::atomic<size_t> tasks_executed{0};
    std::atomic<size_t> tasks_failed{0};
    std::atomic<size_t> blocks_executed{0};
    std::atomic<size_t> errors_handled{0};
    std::atomic<size_t> timeouts_occurred{0};
    std::atomic<size_t> channels_created{0};
    
    void reset() {
        tasks_executed.store(0);
        tasks_failed.store(0);
        blocks_executed.store(0);
        errors_handled.store(0);
        timeouts_occurred.store(0);
        channels_created.store(0);
    }
    
    double getSuccessRate() const {
        size_t total = tasks_executed.load();
        if (total == 0) return 1.0;
        size_t successful = total - tasks_failed.load();
        return static_cast<double>(successful) / total;
    }
};

/**
 * Main concurrency state for VM integration
 */
struct ConcurrencyState {
    // Core runtime
    std::unique_ptr<ConcurrencyRuntime> runtime;
    
    // Execution state stack for nested blocks
    std::stack<std::unique_ptr<BlockExecutionState>> block_stack;
    
    // Performance monitoring
    ConcurrencyStats stats;
    
    // Current task iteration state (for task statements)
    std::string current_task_loop_var;
    ValuePtr current_task_iterable;
    
    ConcurrencyState() : runtime(std::make_unique<ConcurrencyRuntime>()) {
        runtime->start();
    }
    
    ~ConcurrencyState() {
        if (runtime) {
            runtime->stop();
        }
    }
    
    // Non-copyable
    ConcurrencyState(const ConcurrencyState&) = delete;
    ConcurrencyState& operator=(const ConcurrencyState&) = delete;
    
    /**
     * Get the current block execution state (top of stack)
     */
    BlockExecutionState* getCurrentBlock() {
        if (block_stack.empty()) return nullptr;
        return block_stack.top().get();
    }
    
    /**
     * Push a new block execution state
     */
    void pushBlock(std::unique_ptr<BlockExecutionState> state) {
        runtime->incrementActiveBlocks();
        block_stack.push(std::move(state));
        stats.blocks_executed.fetch_add(1);
    }
    
    /**
     * Pop the current block execution state
     */
    std::unique_ptr<BlockExecutionState> popBlock() {
        if (block_stack.empty()) return nullptr;
        
        auto state = std::move(const_cast<std::unique_ptr<BlockExecutionState>&>(block_stack.top()));
        block_stack.pop();
        runtime->decrementActiveBlocks();
        return state;
    }
    
    /**
     * Check if we're currently inside a concurrent/parallel block
     */
    bool isInConcurrentBlock() const {
        return !block_stack.empty();
    }
    
    /**
     * Get nesting level of concurrent blocks
     */
    size_t getBlockNestingLevel() const {
        return block_stack.size();
    }
};

#endif // CONCURRENCY_STATE_H
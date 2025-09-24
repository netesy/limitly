# Design Document

## Overview

This design implements VM execution support for concurrent and parallel blocks with integrated error handling. The implementation builds upon the existing concurrency infrastructure (Scheduler, ThreadPool, EventLoop) and error handling system (ErrorValue, ErrorUnion, error frames) to provide a complete concurrency runtime.

The design focuses on:
- **Zero-cost abstractions** for the success path in concurrent operations
- **Thread-safe error propagation** across task boundaries
- **Efficient resource management** with automatic cleanup
- **Flexible execution modes** (batch, stream, async) for different workload types

## Architecture

### Core Components

#### 1. Concurrency Runtime Manager
```cpp
class ConcurrencyRuntime {
    std::shared_ptr<Scheduler> scheduler;
    std::shared_ptr<ThreadPool> thread_pool;
    std::shared_ptr<EventLoop> event_loop;
    std::unordered_map<std::string, std::shared_ptr<Channel<ValuePtr>>> channels;
    std::atomic<size_t> active_blocks{0};
    
    // Error handling integration
    std::mutex error_mutex;
    std::vector<ErrorValue> collected_errors;
    ErrorHandlingStrategy current_strategy = ErrorHandlingStrategy::Stop;
};
```

#### 2. Task Execution Context
```cpp
struct TaskContext {
    size_t task_id;
    std::string loop_var;
    ValuePtr iteration_value;
    std::shared_ptr<Environment> task_env;
    std::vector<Instruction> task_bytecode;
    
    // Error handling context
    std::vector<ErrorFrame> error_frames;
    ErrorHandlingStrategy error_strategy;
    std::shared_ptr<Channel<ErrorValue>> error_channel;
};
```

#### 3. Block Execution State
```cpp
struct BlockExecutionState {
    enum class Mode { Batch, Stream, Async };
    enum class BlockType { Parallel, Concurrent };
    
    BlockType type;
    Mode mode = Mode::Batch;
    size_t cores = 0; // 0 = auto
    ErrorHandlingStrategy error_strategy = ErrorHandlingStrategy::Stop;
    std::chrono::milliseconds timeout{0};
    std::chrono::milliseconds grace_period{500};
    TimeoutAction timeout_action = TimeoutAction::Partial;
    
    std::shared_ptr<Channel<ValuePtr>> output_channel;
    std::vector<std::unique_ptr<TaskContext>> tasks;
    std::atomic<size_t> completed_tasks{0};
    std::atomic<size_t> failed_tasks{0};
};
```

### Error Handling Integration

#### 1. Error Propagation Strategy
```cpp
enum class ErrorHandlingStrategy {
    Stop,    // Terminate all tasks on first error
    Auto,    // Continue with remaining tasks, collect errors
    Retry    // Retry failed tasks up to limit
};

enum class TimeoutAction {
    Partial,  // Return partial results
    Error     // Treat timeout as error
};
```

#### 2. Thread-Safe Error Collection
```cpp
class ConcurrentErrorCollector {
    std::mutex mutex;
    std::vector<ErrorValue> errors;
    std::atomic<bool> has_errors{false};
    
public:
    void addError(const ErrorValue& error);
    std::vector<ErrorValue> getErrors() const;
    bool hasErrors() const noexcept { return has_errors.load(); }
    void clear();
};
```

#### 3. Error Frame Management
- Each task maintains its own error frame stack
- Error frames are copied to task contexts during task creation
- Errors are propagated back to the main thread through error channels

### Execution Flow

#### 1. Concurrent Block Execution
```
1. Parse block parameters (mode, cores, error strategy, etc.)
2. Create BlockExecutionState with configuration
3. Create output channel if specified
4. For each task statement:
   a. Create TaskContext with iteration values
   b. Copy current error frames to task context
   c. Generate task bytecode
   d. Submit task to scheduler
5. Wait for task completion based on mode
6. Collect results and handle errors
7. Clean up resources
```

#### 2. Task Execution
```
1. Create isolated VM instance for task
2. Set up task environment with iteration variables
3. Install error handlers from task context
4. Execute task bytecode
5. Handle any errors according to strategy
6. Send results to output channel
7. Send errors to error channel if any
8. Clean up task resources
```

#### 3. Error Handling Flow
```
1. Task encounters error during execution
2. Check current error handling strategy
3. If Stop: signal all tasks to terminate
4. If Auto: continue execution, collect error
5. If Retry: retry task up to limit, then collect error
6. Propagate error to main thread via error channel
7. Main thread decides whether to continue or abort
```

## Components and Interfaces

### 1. VM Integration

#### New VM Methods
```cpp
class VM {
    // Concurrency execution methods
    void handleBeginParallel(const Instruction& instruction);
    void handleBeginConcurrent(const Instruction& instruction);
    void handleBeginTask(const Instruction& instruction);
    void handleBeginWorker(const Instruction& instruction);
    void handleSpawnIteratingTasks(const Instruction& instruction);
    
    // Task management
    std::unique_ptr<TaskContext> createTaskContext(const std::string& loopVar, 
                                                   ValuePtr iterationValue);
    void executeTaskInThread(std::unique_ptr<TaskContext> context);
    
    // Error handling integration
    void propagateTaskError(const ErrorValue& error, ErrorHandlingStrategy strategy);
    void collectTaskResults(BlockExecutionState& state);
    
    // Resource management
    void cleanupConcurrencyResources();
};
```

#### Instruction Handlers
```cpp
// Parallel block: parallel(ch=output, mode=batch, cores=4, on_error=Stop)
void VM::handleBeginParallel(const Instruction& instruction) {
    auto state = std::make_unique<BlockExecutionState>();
    state->type = BlockExecutionState::BlockType::Parallel;
    parseBlockParameters(instruction.stringValue, *state);
    
    // Push state onto concurrency stack
    concurrency_stack.push(std::move(state));
}

// Task statement: task(i in 1..10)
void VM::handleBeginTask(const Instruction& instruction) {
    auto& state = *concurrency_stack.top();
    
    // Create task contexts for iteration
    if (currentTaskIterable) {
        auto iterator = createIterator(currentTaskIterable);
        while (hasNext(iterator)) {
            auto value = next(iterator);
            auto context = createTaskContext(currentTaskLoopVar, value);
            state.tasks.push_back(std::move(context));
        }
    } else {
        // Single task without iteration
        auto context = createTaskContext("", nullptr);
        state.tasks.push_back(std::move(context));
    }
}
```

### 2. Channel Integration

#### Channel Creation and Management
```cpp
class ChannelManager {
    std::unordered_map<std::string, std::shared_ptr<Channel<ValuePtr>>> channels;
    std::mutex channels_mutex;
    
public:
    std::shared_ptr<Channel<ValuePtr>> createChannel(const std::string& name);
    std::shared_ptr<Channel<ValuePtr>> getChannel(const std::string& name);
    void closeChannel(const std::string& name);
    void closeAllChannels();
};
```

#### Channel Operations in VM
```cpp
// Channel creation during block setup
if (!state->output_channel && !channelName.empty()) {
    state->output_channel = channel_manager.createChannel(channelName);
    environment->define(channelName, std::make_shared<Value>(
        std::make_shared<Type>(TypeTag::Channel), 
        state->output_channel
    ));
}

// Task result sending
void TaskContext::sendResult(ValuePtr result) {
    if (output_channel) {
        output_channel->send(result);
    }
}
```

### 3. Atomic Operations

#### Atomic Value Operations
```cpp
// Enhanced atomic operations for concurrent access
struct AtomicOperations {
    static ValuePtr atomicAdd(ValuePtr atomic_val, ValuePtr operand);
    static ValuePtr atomicSubtract(ValuePtr atomic_val, ValuePtr operand);
    static ValuePtr atomicCompareExchange(ValuePtr atomic_val, ValuePtr expected, ValuePtr desired);
    static ValuePtr atomicLoad(ValuePtr atomic_val);
    static void atomicStore(ValuePtr atomic_val, ValuePtr value);
};

// VM instruction handler for atomic operations
void VM::handleDefineAtomic(const Instruction& instruction) {
    auto atomic_val = std::make_shared<Value>(
        std::make_shared<Type>(TypeTag::Int), 
        AtomicValue(0)
    );
    environment->define(instruction.stringValue, atomic_val);
}
```

## Data Models

### 1. Concurrency State Management
```cpp
// Global concurrency state in VM
struct ConcurrencyState {
    std::stack<std::unique_ptr<BlockExecutionState>> block_stack;
    std::unique_ptr<ConcurrencyRuntime> runtime;
    std::unique_ptr<ChannelManager> channel_manager;
    std::unique_ptr<ConcurrentErrorCollector> error_collector;
    
    // Performance monitoring
    struct Stats {
        std::atomic<size_t> tasks_executed{0};
        std::atomic<size_t> tasks_failed{0};
        std::atomic<size_t> blocks_executed{0};
        std::atomic<size_t> errors_handled{0};
    } stats;
};
```

### 2. Task Isolation
```cpp
// Each task gets isolated execution environment
class TaskVM : public VM {
    std::unique_ptr<TaskContext> context;
    std::shared_ptr<ConcurrentErrorCollector> error_collector;
    
public:
    TaskVM(std::unique_ptr<TaskContext> ctx, 
           std::shared_ptr<ConcurrentErrorCollector> errors);
    
    ValuePtr executeTask();
    void handleTaskError(const ErrorValue& error);
};
```

### 3. Resource Tracking
```cpp
// Automatic resource cleanup
class ResourceTracker {
    std::vector<std::function<void()>> cleanup_functions;
    std::mutex cleanup_mutex;
    
public:
    void addCleanup(std::function<void()> cleanup);
    void executeCleanup();
    ~ResourceTracker() { executeCleanup(); }
};
```

## Error Handling

### 1. Error Propagation Across Threads
```cpp
// Thread-safe error propagation
class ThreadSafeErrorPropagator {
    std::shared_ptr<Channel<ErrorValue>> error_channel;
    std::atomic<bool> should_stop{false};
    
public:
    void propagateError(const ErrorValue& error, ErrorHandlingStrategy strategy);
    void signalStop();
    bool shouldStop() const { return should_stop.load(); }
};
```

### 2. Error Recovery Strategies
```cpp
// Retry mechanism for failed tasks
class TaskRetryManager {
    struct RetryInfo {
        size_t attempt_count = 0;
        std::chrono::steady_clock::time_point last_attempt;
        ErrorValue last_error;
    };
    
    std::unordered_map<size_t, RetryInfo> retry_info;
    size_t max_retries = 3;
    std::chrono::milliseconds retry_delay{100};
    
public:
    bool shouldRetry(size_t task_id, const ErrorValue& error);
    void recordFailure(size_t task_id, const ErrorValue& error);
    void reset();
};
```

### 3. Error Context Preservation
```cpp
// Preserve error context across thread boundaries
struct ErrorContext {
    std::vector<ErrorFrame> error_frames;
    std::string function_name;
    size_t source_location;
    std::thread::id thread_id;
    std::chrono::steady_clock::time_point timestamp;
    
    ErrorValue createContextualError(const std::string& error_type, 
                                   const std::string& message) const;
};
```

## Testing Strategy

### 1. Unit Testing
- **Atomic Operations**: Test thread-safe atomic value operations
- **Channel Communication**: Test message passing between tasks
- **Error Propagation**: Test error handling strategies
- **Resource Cleanup**: Test automatic resource management

### 2. Integration Testing
- **Concurrent Block Execution**: Test complete concurrent block workflows
- **Parallel Block Execution**: Test CPU-bound parallel processing
- **Mixed Workloads**: Test concurrent and parallel blocks together
- **Error Scenarios**: Test error handling in concurrent contexts

### 3. Performance Testing
- **Scalability**: Test performance with varying numbers of tasks and cores
- **Memory Usage**: Test memory efficiency and leak detection
- **Error Overhead**: Verify zero-cost success path performance
- **Channel Throughput**: Test channel communication performance

### 4. Stress Testing
- **High Task Count**: Test with thousands of concurrent tasks
- **Error Storms**: Test behavior under high error rates
- **Resource Exhaustion**: Test behavior under resource constraints
- **Long-Running Tasks**: Test timeout and grace period handling

## Implementation Phases

### Phase 1: Basic Concurrent Block Support
1. Implement `handleBeginConcurrent` and `handleEndConcurrent`
2. Add task context creation and management
3. Implement basic task execution in thread pool
4. Add channel creation and communication

### Phase 2: Parallel Block Support
1. Implement `handleBeginParallel` and `handleEndParallel`
2. Add work-stealing thread pool integration
3. Implement CPU-bound task distribution
4. Add core count management

### Phase 3: Error Handling Integration
1. Implement thread-safe error propagation
2. Add error handling strategies (Stop, Auto, Retry)
3. Implement error collection and reporting
4. Add timeout and grace period support

### Phase 4: Advanced Features
1. Implement async/await support
2. Add stream processing mode
3. Implement worker statements
4. Add performance monitoring and debugging

### Phase 5: Optimization and Polish
1. Optimize success path performance
2. Add comprehensive error messages
3. Implement resource usage monitoring
4. Add debugging and profiling tools
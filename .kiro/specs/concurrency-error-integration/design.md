# Design Document

## Overview

This design implements a hybrid concurrency system with bare metal compilation and optional runtime support through a pluggable system layer. The runtime acts as a thin compatibility layer providing implementations for Luminar's concurrency hooks, memory hooks, and optionally I/O hooks - not as a virtual machine.

The design focuses on:
- **Bare metal performance** - Direct compilation to native threads with zero runtime overhead for simple cases
- **Pluggable runtime layer** - Optional system layer that provides advanced concurrency features when needed
- **Automatic mode selection** - Compiler chooses between bare metal and runtime-assisted execution
- **Hook-based architecture** - Clean separation between language semantics and system implementation
- **Minimal overhead** - Runtime layer is thin and only used when advanced features are required

## Architecture

### Core Components

#### 1. Execution Mode Selection
```cpp
enum class ConcurrencyMode {
    BareMetal,    // Direct native thread compilation
    RuntimeAssisted  // Uses pluggable runtime layer
};

class ConcurrencyModeAnalyzer {
public:
    ConcurrencyMode analyzeBlock(const ConcurrentBlock& block);
    bool requiresRuntime(const ConcurrentBlock& block);
    bool hasComplexFeatures(const ConcurrentBlock& block);
};
```

#### 2. Hook-Based Architecture
```cpp
// Concurrency hooks that can be implemented by runtime layer
struct ConcurrencyHooks {
    // Task management hooks
    void (*spawn_task)(TaskDescriptor* task);
    void (*join_tasks)(TaskHandle* handles, size_t count);
    void (*cancel_tasks)(TaskHandle* handles, size_t count);
    
    // Channel communication hooks
    ChannelHandle (*create_channel)(size_t capacity);
    void (*send_channel)(ChannelHandle ch, void* data);
    bool (*recv_channel)(ChannelHandle ch, void* data);
    void (*close_channel)(ChannelHandle ch);
    
    // Error handling hooks
    void (*propagate_error)(ErrorContext* ctx);
    void (*collect_errors)(ErrorCollector* collector);
    
    // Memory management hooks
    void* (*allocate_shared)(size_t size);
    void (*deallocate_shared)(void* ptr);
    
    // Optional I/O hooks
    void (*async_read)(IOHandle handle, void* buffer, size_t size);
    void (*async_write)(IOHandle handle, const void* buffer, size_t size);
};
```

#### 3. Bare Metal Code Generation
```cpp
class BareMetalConcurrencyGenerator {
public:
    // Generate native thread creation code
    void generateParallelBlock(const ParallelBlock& block, CodeBuilder& builder);
    void generateConcurrentBlock(const ConcurrentBlock& block, CodeBuilder& builder);
    
    // Generate work distribution code
    void generateWorkPartitioning(const TaskList& tasks, size_t thread_count, CodeBuilder& builder);
    void generateThreadJoining(const TaskList& tasks, CodeBuilder& builder);
    
    // Generate atomic operations
    void generateAtomicOperations(const AtomicVariable& var, CodeBuilder& builder);
};
```

#### 4. Runtime Layer Interface
```cpp
class RuntimeLayer {
    ConcurrencyHooks hooks;
    
public:
    // Initialize runtime with specific implementation
    bool initialize(const RuntimeConfig& config);
    void shutdown();
    
    // Hook registration
    void registerConcurrencyHooks(const ConcurrencyHooks& hooks);
    void registerMemoryHooks(const MemoryHooks& hooks);
    void registerIOHooks(const IOHooks& hooks);
    
    // Runtime services (only when needed)
    TaskScheduler* getTaskScheduler();
    ChannelManager* getChannelManager();
    ErrorCollector* getErrorCollector();
};
```

### Execution Mode Selection Logic

#### 1. Bare Metal Mode Criteria
```cpp
bool ConcurrencyModeAnalyzer::requiresBareMetal(const ConcurrentBlock& block) {
    return !block.hasChannels() &&
           !block.hasComplexErrorHandling() &&
           !block.hasStreamProcessing() &&
           !block.hasMonitoring() &&
           block.hasSimpleTaskIteration() &&
           block.getTaskCount() < MAX_BARE_METAL_TASKS;
}
```

#### 2. Runtime Mode Criteria
```cpp
bool ConcurrencyModeAnalyzer::requiresRuntime(const ConcurrentBlock& block) {
    return block.hasChannels() ||
           block.hasComplexErrorHandling() ||
           block.hasStreamProcessing() ||
           block.hasWorkerStatements() ||
           block.hasMonitoring() ||
           block.hasDynamicTaskCreation() ||
           block.requiresLoadBalancing();
}
```

#### 3. Code Generation Strategy
```cpp
class ConcurrencyCodeGenerator {
public:
    void generateConcurrencyCode(const ConcurrentBlock& block, CodeBuilder& builder) {
        ConcurrencyMode mode = analyzer.analyzeBlock(block);
        
        if (mode == ConcurrencyMode::BareMetal) {
            generateBareMetalCode(block, builder);
        } else {
            generateRuntimeAssistedCode(block, builder);
        }
    }
    
private:
    void generateBareMetalCode(const ConcurrentBlock& block, CodeBuilder& builder);
    void generateRuntimeAssistedCode(const ConcurrentBlock& block, CodeBuilder& builder);
};
```

### Execution Flow

#### 1. Bare Metal Execution Flow
```
1. Analyze concurrent block at compile time
2. Determine if bare metal mode is suitable
3. Generate native thread creation code:
   a. Calculate work distribution
   b. Generate thread creation with work partitions
   c. Generate atomic operations for shared state
   d. Generate thread joining code
4. Compile to native executable with direct thread calls
5. Execute with zero runtime overhead
```

#### 2. Runtime-Assisted Execution Flow
```
1. Analyze concurrent block at compile time
2. Determine runtime features needed
3. Generate code that calls runtime hooks:
   a. Initialize runtime layer if not already active
   b. Register required hooks (concurrency, memory, I/O)
   c. Generate calls to runtime hook functions
   d. Generate cleanup calls to runtime layer
4. Runtime layer provides implementations for:
   a. Task scheduling and management
   b. Channel communication
   c. Error propagation and collection
   d. Advanced memory management
   e. I/O operations (if needed)
```

#### 3. Hybrid Execution Flow
```
1. Some blocks use bare metal mode (simple parallel loops)
2. Other blocks use runtime mode (complex concurrent operations)
3. Runtime layer is initialized only when first needed
4. Bare metal blocks continue with zero overhead
5. Runtime blocks use pluggable system layer
6. Clean transitions between modes within same program
```

## Components and Interfaces

### 1. Compiler Integration

#### Concurrency Analysis Pass
```cpp
class ConcurrencyAnalysisPass {
public:
    void analyzeConcurrentBlocks(AST::Program& program);
    ConcurrencyMode determineModeForBlock(const AST::ConcurrentBlock& block);
    std::vector<RuntimeFeature> getRequiredFeatures(const AST::ConcurrentBlock& block);
    
private:
    bool hasSimpleTaskPattern(const AST::ConcurrentBlock& block);
    bool requiresAdvancedFeatures(const AST::ConcurrentBlock& block);
    size_t estimateTaskComplexity(const AST::ConcurrentBlock& block);
};
```

#### Code Generation
```cpp
class ConcurrencyCodeGen {
public:
    void generateBareMetalConcurrency(const AST::ConcurrentBlock& block, CodeBuilder& builder);
    void generateRuntimeAssistedConcurrency(const AST::ConcurrentBlock& block, CodeBuilder& builder);
    
private:
    // Bare metal generation
    void generateNativeThreads(const TaskList& tasks, CodeBuilder& builder);
    void generateWorkPartitioning(const TaskList& tasks, size_t cores, CodeBuilder& builder);
    void generateAtomicOperations(const AtomicVarList& atomics, CodeBuilder& builder);
    
    // Runtime-assisted generation
    void generateRuntimeHookCalls(const AST::ConcurrentBlock& block, CodeBuilder& builder);
    void generateChannelOperations(const ChannelList& channels, CodeBuilder& builder);
    void generateErrorHandlingHooks(const ErrorHandlingConfig& config, CodeBuilder& builder);
};
```

#### Generated Code Examples
```cpp
// Bare metal parallel block generates:
void parallel_block_1() {
    const size_t num_threads = std::min(4u, std::thread::hardware_concurrency());
    std::vector<std::thread> threads;
    std::atomic<int> shared_counter{0};
    
    for (size_t t = 0; t < num_threads; ++t) {
        threads.emplace_back([&, t]() {
            size_t start = t * (work_size / num_threads);
            size_t end = (t + 1) * (work_size / num_threads);
            for (size_t i = start; i < end; ++i) {
                // Task body
                shared_counter.fetch_add(process_item(i));
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
}

// Runtime-assisted concurrent block generates:
void concurrent_block_1() {
    if (!runtime_initialized) {
        luminar_runtime_init(&runtime_config);
        runtime_initialized = true;
    }
    
    ChannelHandle output_ch = luminar_create_channel(100);
    TaskHandle tasks[10];
    
    for (int i = 0; i < 10; ++i) {
        TaskDescriptor desc = {
            .task_func = task_function_1,
            .task_data = &task_data[i],
            .output_channel = output_ch
        };
        tasks[i] = luminar_spawn_task(&desc);
    }
    
    luminar_join_tasks(tasks, 10);
    luminar_close_channel(output_ch);
}
```

### 2. Runtime Layer Implementation

#### Hook Interface Definition
```cpp
// C-compatible interface for runtime implementations
extern "C" {
    // Concurrency hooks
    typedef struct TaskDescriptor {
        void (*task_func)(void* data);
        void* task_data;
        ChannelHandle output_channel;
        ErrorHandler error_handler;
    } TaskDescriptor;
    
    typedef void* TaskHandle;
    typedef void* ChannelHandle;
    
    // Hook function signatures
    TaskHandle luminar_spawn_task(TaskDescriptor* desc);
    void luminar_join_tasks(TaskHandle* handles, size_t count);
    void luminar_cancel_tasks(TaskHandle* handles, size_t count);
    
    ChannelHandle luminar_create_channel(size_t capacity);
    bool luminar_send_channel(ChannelHandle ch, void* data, size_t size);
    bool luminar_recv_channel(ChannelHandle ch, void* data, size_t size);
    void luminar_close_channel(ChannelHandle ch);
    
    // Memory hooks
    void* luminar_alloc_shared(size_t size);
    void luminar_free_shared(void* ptr);
    
    // Error hooks
    void luminar_propagate_error(ErrorContext* ctx);
    void luminar_collect_errors(ErrorCollector* collector);
    
    // Runtime lifecycle
    bool luminar_runtime_init(RuntimeConfig* config);
    void luminar_runtime_shutdown();
}
```

#### Default Runtime Implementation
```cpp
// Simple default implementation using standard library
class DefaultRuntimeImpl {
    std::unique_ptr<ThreadPool> thread_pool;
    std::unordered_map<ChannelHandle, std::unique_ptr<Channel>> channels;
    std::mutex channels_mutex;
    
public:
    TaskHandle spawnTask(TaskDescriptor* desc);
    void joinTasks(TaskHandle* handles, size_t count);
    ChannelHandle createChannel(size_t capacity);
    bool sendChannel(ChannelHandle ch, void* data, size_t size);
    bool recvChannel(ChannelHandle ch, void* data, size_t size);
};

// Advanced runtime implementations can provide:
// - Work-stealing schedulers
// - NUMA-aware memory allocation
// - High-performance channels
// - Advanced error handling
// - Monitoring and profiling
```

### 3. Atomic Operations (Both Modes)

#### Bare Metal Atomic Generation
```cpp
// Generates direct std::atomic operations
class BareMetalAtomicGen {
public:
    void generateAtomicDeclaration(const AtomicVariable& var, CodeBuilder& builder) {
        builder.addLine(f"std::atomic<{var.type}> {var.name}{{{var.initial_value}}};");
    }
    
    void generateAtomicOperation(const AtomicOperation& op, CodeBuilder& builder) {
        switch (op.type) {
            case AtomicOpType::Load:
                builder.addLine(f"{op.result} = {op.atomic_var}.load();");
                break;
            case AtomicOpType::Store:
                builder.addLine(f"{op.atomic_var}.store({op.value});");
                break;
            case AtomicOpType::Add:
                builder.addLine(f"{op.result} = {op.atomic_var}.fetch_add({op.value});");
                break;
            case AtomicOpType::CompareExchange:
                builder.addLine(f"{op.result} = {op.atomic_var}.compare_exchange_weak({op.expected}, {op.desired});");
                break;
        }
    }
};
```

#### Runtime-Assisted Atomic Operations
```cpp
// Uses runtime hooks for atomic operations (allows custom implementations)
extern "C" {
    typedef void* AtomicHandle;
    
    AtomicHandle luminar_create_atomic(size_t size, void* initial_value);
    void luminar_atomic_load(AtomicHandle handle, void* result);
    void luminar_atomic_store(AtomicHandle handle, void* value);
    void luminar_atomic_add(AtomicHandle handle, void* operand, void* result);
    bool luminar_atomic_compare_exchange(AtomicHandle handle, void* expected, void* desired);
    void luminar_destroy_atomic(AtomicHandle handle);
}
```

## Data Models

### 1. Compilation-Time Analysis
```cpp
// Analysis results for concurrency blocks
struct ConcurrencyAnalysis {
    ConcurrencyMode execution_mode;
    std::vector<RuntimeFeature> required_features;
    size_t estimated_task_count;
    bool has_channels;
    bool has_complex_error_handling;
    bool has_atomic_operations;
    bool requires_load_balancing;
    
    // Performance estimates
    size_t estimated_thread_count;
    bool is_cpu_bound;
    bool is_io_bound;
};

enum class RuntimeFeature {
    TaskScheduling,
    ChannelCommunication,
    ErrorPropagation,
    LoadBalancing,
    StreamProcessing,
    AsyncIO,
    Monitoring
};
```

### 2. Runtime Configuration
```cpp
// Configuration for runtime layer
struct RuntimeConfig {
    // Threading configuration
    size_t max_threads = 0; // 0 = auto-detect
    bool use_work_stealing = true;
    bool enable_numa_awareness = false;
    
    // Channel configuration
    size_t default_channel_capacity = 100;
    bool use_lock_free_channels = true;
    
    // Error handling configuration
    bool collect_error_statistics = false;
    bool enable_error_recovery = true;
    
    // Memory configuration
    bool use_custom_allocator = false;
    size_t shared_memory_pool_size = 0; // 0 = no pool
    
    // Monitoring configuration
    bool enable_profiling = false;
    bool enable_task_tracing = false;
};
```

### 3. Generated Code Metadata
```cpp
// Metadata about generated concurrency code
struct ConcurrencyCodeMetadata {
    struct BareMetal {
        size_t thread_count;
        std::vector<std::string> atomic_variables;
        bool uses_work_partitioning;
    };
    
    struct RuntimeAssisted {
        std::vector<RuntimeFeature> used_features;
        std::vector<std::string> channel_names;
        std::vector<std::string> hook_functions;
    };
    
    ConcurrencyMode mode;
    union {
        BareMetal bare_metal;
        RuntimeAssisted runtime_assisted;
    };
};
```

## Error Handling

### 1. Bare Metal Error Handling
```cpp
// Simple error handling for bare metal mode
class BareMetalErrorGen {
public:
    void generateErrorHandling(const ErrorHandlingConfig& config, CodeBuilder& builder) {
        if (config.strategy == ErrorStrategy::Stop) {
            // Generate atomic flag for early termination
            builder.addLine("std::atomic<bool> should_stop{false};");
            builder.addLine("std::mutex error_mutex;");
            builder.addLine("std::vector<std::string> errors;");
            
            // Generate error checking in task loops
            generateStopOnErrorChecks(builder);
        } else if (config.strategy == ErrorStrategy::Collect) {
            // Generate thread-safe error collection
            generateErrorCollection(builder);
        }
    }
    
private:
    void generateStopOnErrorChecks(CodeBuilder& builder);
    void generateErrorCollection(CodeBuilder& builder);
};
```

### 2. Runtime-Assisted Error Handling
```cpp
// Error handling through runtime hooks
extern "C" {
    typedef struct ErrorContext {
        const char* error_type;
        const char* message;
        const char* file;
        int line;
        void* user_data;
    } ErrorContext;
    
    typedef void (*ErrorHandler)(ErrorContext* ctx);
    
    void luminar_set_error_handler(ErrorHandler handler);
    void luminar_propagate_error(ErrorContext* ctx);
    void luminar_collect_error(ErrorContext* ctx);
    bool luminar_has_errors();
    size_t luminar_get_error_count();
    void luminar_clear_errors();
}
```

### 3. Error Strategy Implementation
```cpp
// Compile-time error strategy selection
enum class ErrorStrategy {
    Stop,      // Terminate all tasks on first error (bare metal: atomic flag)
    Collect,   // Collect all errors and continue (bare metal: thread-safe vector)
    Ignore,    // Ignore errors and continue (bare metal: no error handling)
    Runtime    // Use runtime error handling hooks
};

class ErrorStrategyGenerator {
public:
    void generateErrorStrategy(ErrorStrategy strategy, CodeBuilder& builder) {
        switch (strategy) {
            case ErrorStrategy::Stop:
                generateStopStrategy(builder);
                break;
            case ErrorStrategy::Collect:
                generateCollectStrategy(builder);
                break;
            case ErrorStrategy::Runtime:
                generateRuntimeStrategy(builder);
                break;
        }
    }
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

### Phase 1: Concurrency Analysis and Mode Selection
1. Implement `ConcurrencyModeAnalyzer` to determine execution mode
2. Add analysis pass to identify required runtime features
3. Implement decision logic for bare metal vs runtime-assisted execution
4. Add metadata generation for concurrency blocks

### Phase 2: Bare Metal Code Generation
1. Implement `BareMetalConcurrencyGenerator` for simple concurrent/parallel blocks
2. Add native thread creation and work partitioning code generation
3. Implement atomic operations code generation using std::atomic
4. Add simple error handling code generation (atomic flags, thread-safe collections)

### Phase 3: Runtime Hook Interface
1. Define C-compatible hook interface for runtime implementations
2. Implement default runtime using standard library (ThreadPool, channels)
3. Add runtime initialization and lifecycle management
4. Implement hook registration and dynamic loading

### Phase 4: Runtime-Assisted Code Generation
1. Implement code generation that calls runtime hooks
2. Add channel operations through runtime interface
3. Implement complex error handling through runtime hooks
4. Add support for advanced features (stream processing, monitoring)

### Phase 5: Integration and Optimization
1. Integrate both modes into the compiler pipeline
2. Add automatic mode selection based on block complexity
3. Implement seamless transitions between modes within same program
4. Add performance monitoring and debugging support

### Phase 6: Advanced Runtime Features
1. Implement work-stealing scheduler for runtime mode
2. Add NUMA-aware memory allocation hooks
3. Implement high-performance lock-free channels
4. Add monitoring, profiling, and debugging hooks
#ifndef CONCURRENCY_RUNTIME_H
#define CONCURRENCY_RUNTIME_H

#include "scheduler.hh"
#include "thread_pool.hh"
#include "event_loop.hh"
#include "channel.hh"
#include "../value.hh"
#include <memory>
#include <unordered_map>
#include <mutex>
#include <atomic>
#include <vector>
#include <string>

// Forward declarations
struct ErrorValue;

/**
 * Error handling strategies for concurrent execution
 */
enum class ErrorHandlingStrategy {
    Stop,    // Terminate all tasks on first error
    Auto,    // Continue with remaining tasks, collect errors
    Retry    // Retry failed tasks up to limit
};

/**
 * Timeout action when concurrent blocks exceed time limit
 */
enum class TimeoutAction {
    Partial,  // Return partial results
    Error     // Treat timeout as error
};

/**
 * Thread-safe error collection for concurrent tasks
 */
class ConcurrentErrorCollector {
private:
    mutable std::mutex mutex_;
    std::vector<ErrorValue> errors_;
    std::atomic<bool> has_errors_{false};

public:
    /**
     * Add an error to the collection in a thread-safe manner
     */
    void addError(const ErrorValue& error);

    /**
     * Get all collected errors (returns a copy for thread safety)
     */
    std::vector<ErrorValue> getErrors() const;

    /**
     * Check if any errors have been collected
     */
    bool hasErrors() const noexcept { return has_errors_.load(); }

    /**
     * Clear all collected errors
     */
    void clear();

    /**
     * Get the number of errors collected
     */
    size_t getErrorCount() const;
};

/**
 * Thread-safe channel manager for creating and managing channels
 */
class ChannelManager {
private:
    std::unordered_map<std::string, std::shared_ptr<Channel<ValuePtr>>> channels_;
    mutable std::mutex channels_mutex_;

public:
    /**
     * Create a new channel with the given name
     * @param name Channel name for identification
     * @return Shared pointer to the created channel
     */
    std::shared_ptr<Channel<ValuePtr>> createChannel(const std::string& name);

    /**
     * Get an existing channel by name
     * @param name Channel name
     * @return Shared pointer to the channel, or nullptr if not found
     */
    std::shared_ptr<Channel<ValuePtr>> getChannel(const std::string& name);

    /**
     * Close a channel by name
     * @param name Channel name
     */
    void closeChannel(const std::string& name);

    /**
     * Close all managed channels
     */
    void closeAllChannels();

    /**
     * Remove a channel from management (does not close it)
     * @param name Channel name
     */
    void removeChannel(const std::string& name);

    /**
     * Get all channel names currently managed
     */
    std::vector<std::string> getChannelNames() const;
};

/**
 * Main concurrency runtime that integrates scheduler, thread pool, and event loop
 */
class ConcurrencyRuntime {
private:
    std::shared_ptr<Scheduler> scheduler_;
    std::shared_ptr<ThreadPool> thread_pool_;
    std::shared_ptr<EventLoop> event_loop_;
    std::unique_ptr<ChannelManager> channel_manager_;
    std::unique_ptr<ConcurrentErrorCollector> error_collector_;
    
    std::atomic<size_t> active_blocks_{0};
    std::atomic<bool> shutdown_requested_{false};
    
    // Current error handling configuration
    ErrorHandlingStrategy current_strategy_ = ErrorHandlingStrategy::Stop;
    mutable std::mutex strategy_mutex_;

public:
    /**
     * Constructor - initializes all concurrency components
     * @param num_threads Number of worker threads (0 = auto-detect)
     */
    explicit ConcurrencyRuntime(size_t num_threads = 0);

    /**
     * Destructor - ensures clean shutdown
     */
    ~ConcurrencyRuntime();

    // Non-copyable
    ConcurrencyRuntime(const ConcurrencyRuntime&) = delete;
    ConcurrencyRuntime& operator=(const ConcurrencyRuntime&) = delete;

    /**
     * Start the runtime components
     */
    void start();

    /**
     * Stop the runtime components
     */
    void stop();

    /**
     * Request shutdown of all components
     */
    void requestShutdown();

    /**
     * Check if shutdown has been requested
     */
    bool isShutdownRequested() const noexcept { return shutdown_requested_.load(); }

    // Component accessors
    std::shared_ptr<Scheduler> getScheduler() { return scheduler_; }
    std::shared_ptr<ThreadPool> getThreadPool() { return thread_pool_; }
    std::shared_ptr<EventLoop> getEventLoop() { return event_loop_; }
    ChannelManager& getChannelManager() { return *channel_manager_; }
    ConcurrentErrorCollector& getErrorCollector() { return *error_collector_; }

    /**
     * Set the current error handling strategy
     */
    void setErrorHandlingStrategy(ErrorHandlingStrategy strategy);

    /**
     * Get the current error handling strategy
     */
    ErrorHandlingStrategy getErrorHandlingStrategy() const;

    /**
     * Increment active block count
     */
    void incrementActiveBlocks() { active_blocks_.fetch_add(1); }

    /**
     * Decrement active block count
     */
    void decrementActiveBlocks() { active_blocks_.fetch_sub(1); }

    /**
     * Get current active block count
     */
    size_t getActiveBlockCount() const noexcept { return active_blocks_.load(); }

    /**
     * Wait for all active blocks to complete
     */
    void waitForActiveBlocks();
};

#endif // CONCURRENCY_RUNTIME_H
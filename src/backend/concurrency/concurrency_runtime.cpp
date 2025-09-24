#include "concurrency_runtime.hh"
#include "../value.hh"
#include <thread>
#include <chrono>
#include <algorithm>

// ConcurrentErrorCollector implementation
void ConcurrentErrorCollector::addError(const ErrorValue& error) {
    std::lock_guard<std::mutex> lock(mutex_);
    errors_.push_back(error);
    has_errors_.store(true);
}

std::vector<ErrorValue> ConcurrentErrorCollector::getErrors() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return errors_; // Return a copy for thread safety
}

void ConcurrentErrorCollector::clear() {
    std::lock_guard<std::mutex> lock(mutex_);
    errors_.clear();
    has_errors_.store(false);
}

size_t ConcurrentErrorCollector::getErrorCount() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return errors_.size();
}

// ChannelManager implementation
std::shared_ptr<Channel<ValuePtr>> ChannelManager::createChannel(const std::string& name) {
    std::lock_guard<std::mutex> lock(channels_mutex_);
    
    // Check if channel already exists
    auto it = channels_.find(name);
    if (it != channels_.end()) {
        return it->second;
    }
    
    // Create new channel
    auto channel = std::make_shared<Channel<ValuePtr>>();
    channels_[name] = channel;
    return channel;
}

std::shared_ptr<Channel<ValuePtr>> ChannelManager::getChannel(const std::string& name) {
    std::lock_guard<std::mutex> lock(channels_mutex_);
    
    auto it = channels_.find(name);
    if (it != channels_.end()) {
        return it->second;
    }
    
    return nullptr;
}

void ChannelManager::closeChannel(const std::string& name) {
    std::lock_guard<std::mutex> lock(channels_mutex_);
    
    auto it = channels_.find(name);
    if (it != channels_.end()) {
        it->second->close();
    }
}

void ChannelManager::closeAllChannels() {
    std::lock_guard<std::mutex> lock(channels_mutex_);
    
    for (auto& [name, channel] : channels_) {
        channel->close();
    }
}

void ChannelManager::removeChannel(const std::string& name) {
    std::lock_guard<std::mutex> lock(channels_mutex_);
    channels_.erase(name);
}

std::vector<std::string> ChannelManager::getChannelNames() const {
    std::lock_guard<std::mutex> lock(channels_mutex_);
    
    std::vector<std::string> names;
    names.reserve(channels_.size());
    
    for (const auto& [name, channel] : channels_) {
        names.push_back(name);
    }
    
    return names;
}

// ConcurrencyRuntime implementation
ConcurrencyRuntime::ConcurrencyRuntime(size_t num_threads) 
    : channel_manager_(std::make_unique<ChannelManager>()),
      error_collector_(std::make_unique<ConcurrentErrorCollector>()) {
    
    // Initialize scheduler
    scheduler_ = std::make_shared<Scheduler>();
    
    // Determine number of threads
    if (num_threads == 0) {
        num_threads = std::thread::hardware_concurrency();
        if (num_threads == 0) {
            num_threads = 2; // Fallback if hardware_concurrency fails
        }
    }
    
    // Initialize thread pool
    thread_pool_ = std::make_shared<ThreadPool>(num_threads, scheduler_);
    
    // Initialize event loop
    event_loop_ = std::make_shared<EventLoop>();
}

ConcurrencyRuntime::~ConcurrencyRuntime() {
    stop();
}

void ConcurrencyRuntime::start() {
    if (shutdown_requested_.load()) {
        return; // Don't start if shutdown was requested
    }
    
    // Start thread pool
    if (thread_pool_) {
        thread_pool_->start();
    }
    
    // Event loop is started on-demand when needed
}

void ConcurrencyRuntime::stop() {
    requestShutdown();
    
    // Wait for active blocks to complete (with timeout)
    auto start_time = std::chrono::steady_clock::now();
    const auto timeout = std::chrono::seconds(5); // 5 second timeout
    
    while (active_blocks_.load() > 0) {
        auto elapsed = std::chrono::steady_clock::now() - start_time;
        if (elapsed > timeout) {
            break; // Force shutdown after timeout
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    // Close all channels
    if (channel_manager_) {
        channel_manager_->closeAllChannels();
    }
    
    // Stop event loop
    if (event_loop_) {
        event_loop_->stop();
    }
    
    // Stop thread pool
    if (thread_pool_) {
        thread_pool_->stop();
    }
    
    // Shutdown scheduler
    if (scheduler_) {
        scheduler_->shutdown();
    }
}

void ConcurrencyRuntime::requestShutdown() {
    shutdown_requested_.store(true);
}

void ConcurrencyRuntime::setErrorHandlingStrategy(ErrorHandlingStrategy strategy) {
    std::lock_guard<std::mutex> lock(strategy_mutex_);
    current_strategy_ = strategy;
}

ErrorHandlingStrategy ConcurrencyRuntime::getErrorHandlingStrategy() const {
    std::lock_guard<std::mutex> lock(strategy_mutex_);
    return current_strategy_;
}

void ConcurrencyRuntime::waitForActiveBlocks() {
    while (active_blocks_.load() > 0 && !shutdown_requested_.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
#ifndef CHANNEL_H
#define CHANNEL_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <stdexcept>

template<typename T>
class Channel {
public:
    Channel() = default;

    // Deleted copy constructor and assignment operator
    Channel(const Channel&) = delete;
    Channel& operator=(const Channel&) = delete;

    void send(T value) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (closed_) {
            throw std::runtime_error("send on closed channel");
        }
        queue_.push(std::move(value));
        cv_.notify_one();
    }

    bool receive(T& value) {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this] { return !queue_.empty() || closed_; });

        if (queue_.empty() && closed_) {
            return false;
        }

        value = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    void close() {
        std::lock_guard<std::mutex> lock(mtx_);
        closed_ = true;
        cv_.notify_all();
    }

private:
    std::mutex mtx_;
    std::condition_variable cv_;
    std::queue<T> queue_;
    bool closed_ = false;
};

#endif // CHANNEL_H

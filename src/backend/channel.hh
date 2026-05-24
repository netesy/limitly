#ifndef CHANNEL_H
#define CHANNEL_H
#include "task.hh"
#include "fiber.hh"
#include "scheduler.hh"
#include <queue>
#include <deque>
#include <cstddef>
#include <mutex>
namespace LM {
namespace Backend {
struct Channel {
    mutable std::mutex mtx;
    std::queue<RegisterValue> buffer;
    size_t capacity;
    bool closed = false;
    std::deque<Fiber*> waiting_senders;
    std::deque<Fiber*> waiting_receivers;
    Channel(size_t cap) : capacity(cap) {}
    bool offer(const RegisterValue& value) {
        std::lock_guard<std::mutex> lock(mtx);
        if (closed || buffer.size() >= capacity) return false;
        buffer.push(value);
        if (!waiting_receivers.empty()) { Fiber* f = waiting_receivers.front(); waiting_receivers.pop_front(); f->resume(); }
        return true;
    }
    bool poll(RegisterValue& out_value) {
        std::lock_guard<std::mutex> lock(mtx);
        if (buffer.empty()) return false;
        out_value = buffer.front(); buffer.pop();
        if (!waiting_senders.empty()) { Fiber* f = waiting_senders.front(); waiting_senders.pop_front(); f->resume(); }
        return true;
    }
    void send(const RegisterValue& value, Fiber* current_fiber) {
        std::lock_guard<std::mutex> lock(mtx);
        if (closed) return;
        if (buffer.size() >= capacity) { waiting_senders.push_back(current_fiber); current_fiber->suspend(); return; }
        buffer.push(value);
        if (!waiting_receivers.empty()) { Fiber* f = waiting_receivers.front(); waiting_receivers.pop_front(); f->resume(); }
    }
    RegisterValue recv(Fiber* current_fiber) {
        std::lock_guard<std::mutex> lock(mtx);
        if (buffer.empty()) { if (closed) return RegisterValue(); waiting_receivers.push_back(current_fiber); current_fiber->suspend(); return RegisterValue(); }
        RegisterValue val = buffer.front(); buffer.pop();
        if (!waiting_senders.empty()) { Fiber* f = waiting_senders.front(); waiting_senders.pop_front(); f->resume(); }
        return val;
    }
    void close() {
        std::lock_guard<std::mutex> lock(mtx);
        closed = true;
        while (!waiting_receivers.empty()) { Fiber* f = waiting_receivers.front(); waiting_receivers.pop_front(); f->resume(); }
        while (!waiting_senders.empty()) { Fiber* f = waiting_senders.front(); waiting_senders.pop_front(); f->resume(); }
    }
    bool has_data() const { std::lock_guard<std::mutex> lock(mtx); return !buffer.empty(); }
};
} }
#endif

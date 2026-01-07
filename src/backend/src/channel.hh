#pragma once
#include <queue>
#include <deque>
#include "task.hh"
#include "scheduler.hh"

// Forward declarations
struct Fiber;


// Modern Channel for Limitly concurrency
namespace Register {
struct Channel {
    std::queue<RegisterValue> buffer;
    size_t capacity;
    bool closed = false;            // channel closed flag
    std::deque<Fiber*> waiting_senders;   // fibers waiting to send
    std::deque<Fiber*> waiting_receivers; // fibers waiting to receive

    // Constructor
    Channel(size_t cap) : capacity(cap) {}

    // Blocking send: suspend fiber if full
    void send(const RegisterValue& value, Fiber* current_fiber) {
        while (buffer.size() >= capacity) {
            // suspend this fiber until there is space
            waiting_senders.push_back(current_fiber);
            Scheduler::suspend_current();
        }
        buffer.push(value);

        // wake up one waiting receiver if exists
        if (!waiting_receivers.empty()) {
            Fiber* f = waiting_receivers.front();
            waiting_receivers.pop_front();
            Scheduler::resume(f);
        }
    }

    // Blocking receive: suspend fiber if empty
    RegisterValue recv(Fiber* current_fiber) {
        while (buffer.empty()) {
            if (closed) {
                // return an invalid marker if channel closed
                return RegisterValue();
            }
            // suspend this fiber until data arrives
            waiting_receivers.push_back(current_fiber);
            Scheduler::suspend_current();
        }
        RegisterValue val = buffer.front();
        buffer.pop();

        // wake up one waiting sender if exists
        if (!waiting_senders.empty()) {
            Fiber* f = waiting_senders.front();
            waiting_senders.pop_front();
            Scheduler::resume(f);
        }
        return val;
    }

    // Non-blocking send (offer)
    bool offer(const RegisterValue& value) {
        if (closed) return false;
        if (buffer.size() >= capacity) return false;
        buffer.push(value);

        if (!waiting_receivers.empty()) {
            Fiber* f = waiting_receivers.front();
            waiting_receivers.pop_front();
            Scheduler::resume(f);
        }
        return true;
    }

    // Non-blocking receive (poll)
    bool poll(RegisterValue& out_value) {
        if (buffer.empty()) return false;
        out_value = buffer.front();
        buffer.pop();

        if (!waiting_senders.empty()) {
            Fiber* f = waiting_senders.front();
            waiting_senders.pop_front();
            Scheduler::resume(f);
        }
        return true;
    }

    // Close channel
    void close() {
        closed = true;

        // resume all waiting receivers so they can detect closure
        while (!waiting_receivers.empty()) {
            Fiber* f = waiting_receivers.front();
            waiting_receivers.pop_front();
            Scheduler::resume(f);
        }
    }

    bool has_data() const {
        return !buffer.empty();
    }

    size_t size() const {
        return buffer.size();
    }
};
} // namespace Register

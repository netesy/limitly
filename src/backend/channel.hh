#ifndef CHANNEL_H
#define CHANNEL_H

#include "task.hh"
#include "fiber.hh"
#include "scheduler.hh"
#include <queue>
#include <deque>
#include <cstddef>

namespace LM {
namespace Backend {

// Modern Channel for Limitly concurrency
struct Channel {
    std::queue<RegisterValue> buffer;
    size_t capacity;
    bool closed = false;            // channel closed flag
    std::deque<Fiber*> waiting_senders;   // fibers waiting to send (blocking send)
    std::deque<Fiber*> waiting_receivers; // fibers waiting to receive (blocking recv)

    // Constructor
    Channel(size_t cap) : capacity(cap) {}

    // Non-blocking send (offer) - NEVER suspends fiber
    bool offer(const RegisterValue& value) {
        if (closed) return false;
        if (buffer.size() >= capacity) return false;
        
        buffer.push(value);

        // Wake up one waiting receiver if exists (from blocking recv)
        if (!waiting_receivers.empty()) {
            Fiber* f = waiting_receivers.front();
            waiting_receivers.pop_front();
            f->resume();
        }
        return true;
    }

    // Non-blocking receive (poll) - NEVER suspends fiber
    bool poll(RegisterValue& out_value) {
        if (buffer.empty()) return false;
        
        out_value = buffer.front();
        buffer.pop();

        // Wake up one waiting sender if exists (from blocking send)
        if (!waiting_senders.empty()) {
            Fiber* f = waiting_senders.front();
            waiting_senders.pop_front();
            f->resume();
        }
        return true;
    }

    // Blocking send - MAY suspend fiber (for explicit send statements)
    void send(const RegisterValue& value, Fiber* current_fiber) {
        while (buffer.size() >= capacity && !closed) {
            // Suspend this fiber until there is space
            waiting_senders.push_back(current_fiber);
            current_fiber->suspend();
            // Note: Scheduler will resume this fiber when space becomes available
            return; // Actual suspension handled by scheduler
        }
        
        if (!closed) {
            buffer.push(value);

            // Wake up one waiting receiver if exists
            if (!waiting_receivers.empty()) {
                Fiber* f = waiting_receivers.front();
                waiting_receivers.pop_front();
                f->resume();
            }
        }
    }

    // Blocking receive - MAY suspend fiber (for explicit recv statements)
    RegisterValue recv(Fiber* current_fiber) {
        while (buffer.empty() && !closed) {
            // Suspend this fiber until data arrives
            waiting_receivers.push_back(current_fiber);
            current_fiber->suspend();
            // Note: Scheduler will resume this fiber when data becomes available
            return RegisterValue(); // Return early, actual suspension handled by scheduler
        }
        
        if (buffer.empty()) {
            // Channel is closed and empty
            return RegisterValue(); 
        }
        
        RegisterValue val = buffer.front();
        buffer.pop();

        // Wake up one waiting sender if exists
        if (!waiting_senders.empty()) {
            Fiber* f = waiting_senders.front();
            waiting_senders.pop_front();
            f->resume();
        }
        return val;
    }

    // Close channel
    void close() {
        closed = true;

        // Resume all waiting receivers so they can detect closure
        while (!waiting_receivers.empty()) {
            Fiber* f = waiting_receivers.front();
            waiting_receivers.pop_front();
            f->resume();
        }
        
        // Resume all waiting senders so they can detect closure
        while (!waiting_senders.empty()) {
            Fiber* f = waiting_senders.front();
            waiting_senders.pop_front();
            f->resume();
        }
    }

    bool has_data() const {
        return !buffer.empty();
    }

    size_t size() const {
        return buffer.size();
    }
    
    bool is_closed() const {
        return closed;
    }
};

} // namespace Backend
} // namespace LM

#endif // CHANNEL_H

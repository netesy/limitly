#include "channel.hh"
#include "scheduler.hh"

// Channel implementation

void Channel::send(const RegisterValue& value, Fiber* current_fiber) {
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

RegisterValue Channel::recv(Fiber* current_fiber) {
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

bool Channel::offer(const RegisterValue& value) {
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

bool Channel::poll(RegisterValue& out_value) {
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

void Channel::close() {
    closed = true;

    // resume all waiting receivers so they can detect closure
    while (!waiting_receivers.empty()) {
        Fiber* f = waiting_receivers.front();
        waiting_receivers.pop_front();
        Scheduler::resume(f);
    }
}

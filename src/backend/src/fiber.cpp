#include "fiber.hh"

// Fiber implementation - simple functional version

void Fiber::suspend() {
    // Simple functional implementation - just mark state
    state = SUSPENDED;
}

void Fiber::resume() {
    // Simple functional implementation - just mark state  
    state = READY;
}

#include "scheduler.hh"
#include "fiber.hh"
#include <iostream>

// Scheduler implementation

void Scheduler::suspend_current() {
    // Simple functional implementation
    // In the previous working version, this was a no-op that just
    // allowed the channel operations to work without real fiber switching
    std::cout << "[DEBUG] Fiber suspended (no-op implementation)" << std::endl;
}

void Scheduler::resume(Fiber* fiber) {
    // Simple functional implementation  
    // In the previous working version, this was a no-op
    std::cout << "[DEBUG] Fiber resumed (no-op implementation)" << std::endl;
}

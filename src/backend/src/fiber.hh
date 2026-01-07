#pragma once
#include <cstdint>
#include <vector>
#include "task.hh"

struct Fiber {
    enum State { READY, RUNNING, SUSPENDED, FINISHED } state;

    // VM execution info
    size_t pc;                    // program counter
    std::vector<RegisterValue> stack;  // local registers
    // optional: reference to function/code object
    void* function;

    // Suspend/resume bookkeeping
    void suspend();
    void resume();
};

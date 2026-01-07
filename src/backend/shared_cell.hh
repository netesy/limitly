#ifndef SHARED_CELL_H
#define SHARED_CELL_H

#include <cstdint>
#include <atomic>

namespace Register {

// SharedCell structure for parallel execution
struct SharedCell {
    uint32_t id;
    std::atomic<int64_t> value;
    
    SharedCell(uint32_t cell_id, int64_t initial_value) 
        : id(cell_id), value(initial_value) {}
};

} // namespace Register

#endif // SHARED_CELL_H

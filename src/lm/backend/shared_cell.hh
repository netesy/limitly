#ifndef LM_LM_BACKEND_HH
#define SHARED_CELL_H

#include <cstdint>
#include <atomic>

namespace LM {
namespace Backend {


namespace Register {

// SharedCell structure for parallel execution
struct SharedCell {
    uint32_t id;
    std::atomic<int64_t> value;
    
    SharedCell(uint32_t cell_id, int64_t initial_value) 
        : id(cell_id), value(initial_value) {}
};

} // namespace Register




} // namespace LM
} // namespace Backend

#endif // LM_LM_BACKEND_HH

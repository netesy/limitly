#ifndef CALLSTACK_H
#define CALLSTACK_H

#include "../../lir/lir.hh"
#include "../../runtime/runtime_value_base.h"
#include <vector>
#include <memory>
#include <cstdint>
#include <unordered_map>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

// Call frame representing a single function call in the call stack
struct CallFrame {
    uint64_t frame_id;                    // Unique frame identifier
    uint64_t parent_frame_id;              // Parent frame ID (0 if none)
    uint64_t return_address;              // Return address (instruction index)
    LIR::Reg return_reg;                  // Register for return value
    std::vector<LmValue> saved_registers; // Saved register state
    std::vector<LmValue> local_registers; // Local registers for this frame
    std::string function_name;            // Function name for debugging
    uint32_t param_count;                 // Number of parameters
    uint32_t register_count;             // Number of registers used
    
    CallFrame(uint64_t id, uint64_t parent_id, const std::string& func_name, 
              uint32_t params, uint32_t regs)
        : frame_id(id), parent_frame_id(parent_id), return_address(0),
          return_reg(0), function_name(func_name), param_count(params),
          register_count(regs) {
        local_registers.resize(regs, VAL_NIL);
    }
    
    // Save register state
    void save_registers(const std::vector<LmValue>& vm_registers) {
        saved_registers = vm_registers;
    }
    
    // Restore register state
    void restore_registers(std::vector<LmValue>& vm_registers) const {
        if (saved_registers.size() == vm_registers.size()) {
            vm_registers = saved_registers;
        }
    }
    
    // Get local register value
    LmValue get_local_register(LIR::Reg reg) const {
        if (reg < local_registers.size()) {
            return local_registers[reg];
        }
        return VAL_NIL;
    }
    
    // Set local register value
    void set_local_register(LIR::Reg reg, LmValue value) {
        if (reg >= local_registers.size()) {
            local_registers.resize(reg + 1, VAL_NIL);
        }
        local_registers[reg] = value;
    }
};

// Call stack managing the hierarchy of function calls
class CallStack {
public:
    CallStack();
    
    // Push a new frame onto the call stack
    uint64_t push_frame(const std::string& function_name, uint32_t param_count, 
                        uint32_t register_count, uint64_t return_address, 
                        LIR::Reg return_reg);
    
    // Pop the current frame from the call stack
    bool pop_frame();
    
    // Get the current frame
    CallFrame* get_current_frame();
    
    // Get a frame by ID
    CallFrame* get_frame(uint64_t frame_id);
    
    // Get the parent frame of the current frame
    CallFrame* get_parent_frame();
    
    // Get the current frame depth
    size_t get_depth() const;
    
    // Check if the call stack is empty
    bool is_empty() const;
    
    // Clear the call stack
    void clear();
    
    // Get the maximum depth reached
    size_t get_max_depth() const;
    
private:
    std::vector<std::unique_ptr<CallFrame>> frames;
    uint64_t next_frame_id;
    size_t max_depth;
};

// Call stack implementation
inline CallStack::CallStack() : next_frame_id(1), max_depth(0) {}

inline uint64_t CallStack::push_frame(const std::string& function_name, 
                                       uint32_t param_count, uint32_t register_count,
                                       uint64_t return_address, LIR::Reg return_reg) {
    uint64_t parent_id = frames.empty() ? 0 : frames.back()->frame_id;
    auto frame = std::make_unique<CallFrame>(next_frame_id, parent_id, function_name,
                                              param_count, register_count);
    frame->return_address = return_address;
    frame->return_reg = return_reg;
    
    frames.push_back(std::move(frame));
    
    if (frames.size() > max_depth) {
        max_depth = frames.size();
    }
    
    return next_frame_id++;
}

inline bool CallStack::pop_frame() {
    if (frames.empty()) {
        return false;
    }
    frames.pop_back();
    return true;
}

inline CallFrame* CallStack::get_current_frame() {
    return frames.empty() ? nullptr : frames.back().get();
}

inline CallFrame* CallStack::get_frame(uint64_t frame_id) {
    for (auto& frame : frames) {
        if (frame->frame_id == frame_id) {
            return frame.get();
        }
    }
    return nullptr;
}

inline CallFrame* CallStack::get_parent_frame() {
    if (frames.size() < 2) {
        return nullptr;
    }
    return frames[frames.size() - 2].get();
}

inline size_t CallStack::get_depth() const {
    return frames.size();
}

inline bool CallStack::is_empty() const {
    return frames.empty();
}

inline void CallStack::clear() {
    frames.clear();
    next_frame_id = 1;
}

inline size_t CallStack::get_max_depth() const {
    return max_depth;
}

// Register snapshot for VM state management
struct RegisterSnapshot {
    std::vector<LmValue> registers;
    uint64_t instruction_pointer;
    uint64_t current_frame_id;
    uint64_t timestamp;
    
    RegisterSnapshot() : instruction_pointer(0), current_frame_id(0), timestamp(0) {}
    
    RegisterSnapshot(const std::vector<LmValue>& regs, uint64_t ip, uint64_t frame_id)
        : registers(regs), instruction_pointer(ip), current_frame_id(frame_id),
          timestamp(0) {}
};

// VM state manager for saving and restoring complete VM state
class VMStateManager {
public:
    VMStateManager();
    
    // Save current VM state
    uint64_t save_state(const std::vector<LmValue>& registers, uint64_t ip, 
                        uint64_t frame_id);
    
    // Restore VM state by snapshot ID
    bool restore_state(uint64_t snapshot_id, std::vector<LmValue>& registers,
                       uint64_t& ip, uint64_t& frame_id);
    
    // Get a snapshot by ID
    RegisterSnapshot* get_snapshot(uint64_t snapshot_id);
    
    // Delete a snapshot
    bool delete_snapshot(uint64_t snapshot_id);
    
    // Clear all snapshots
    void clear();
    
    // Get the number of snapshots
    size_t get_snapshot_count() const;
    
private:
    std::unordered_map<uint64_t, RegisterSnapshot> snapshots;
    uint64_t next_snapshot_id;
};

inline VMStateManager::VMStateManager() : next_snapshot_id(1) {}

inline uint64_t VMStateManager::save_state(const std::vector<LmValue>& registers,
                                           uint64_t ip, uint64_t frame_id) {
    RegisterSnapshot snapshot(registers, ip, frame_id);
    snapshots[next_snapshot_id] = snapshot;
    return next_snapshot_id++;
}

inline bool VMStateManager::restore_state(uint64_t snapshot_id,
                                          std::vector<LmValue>& registers,
                                          uint64_t& ip, uint64_t& frame_id) {
    auto it = snapshots.find(snapshot_id);
    if (it == snapshots.end()) {
        return false;
    }
    
    const RegisterSnapshot& snapshot = it->second;
    if (snapshot.registers.size() == registers.size()) {
        registers = snapshot.registers;
        ip = snapshot.instruction_pointer;
        frame_id = snapshot.current_frame_id;
        return true;
    }
    
    return false;
}

inline RegisterSnapshot* VMStateManager::get_snapshot(uint64_t snapshot_id) {
    auto it = snapshots.find(snapshot_id);
    return (it != snapshots.end()) ? &it->second : nullptr;
}

inline bool VMStateManager::delete_snapshot(uint64_t snapshot_id) {
    return snapshots.erase(snapshot_id) > 0;
}

inline void VMStateManager::clear() {
    snapshots.clear();
    next_snapshot_id = 1;
}

inline size_t VMStateManager::get_snapshot_count() const {
    return snapshots.size();
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM

#endif // CALLSTACK_H

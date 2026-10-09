#pragma once
#include "register.hh"
#include "vm_value.hh"
#include "../../memory/reference_flags.hh"
#include <stdexcept>

namespace LM::Backend::VM::Register {
// The VM and hosted native modules execute the same canonical reference modes.
struct ReferenceOperations {
    static uint64_t create(RegisterVM& vm, RegisterValue value, uint64_t mode) {
        if (mode & ~(Memory::ReferenceWritable | Memory::ReferenceNullable))
            throw std::runtime_error("Invalid reference mode");
        if (IS_NIL(value) && (mode & Memory::ReferenceNullable)) return 0;
        return vm.borrow_memory(value, (mode & Memory::ReferenceWritable) != 0);
    }
    static RegisterValue resolve(RegisterVM& vm, uint64_t token, uint64_t mode) {
        if (mode & ~(Memory::ReferenceWritable | Memory::ReferenceNullable))
            throw std::runtime_error("Invalid reference mode");
        if (!token && (mode & Memory::ReferenceNullable)) return VAL_NIL;
        return vm.resolve_memory(token, (mode & Memory::ReferenceWritable) != 0);
    }
    static uint64_t move(RegisterVM& vm, uint64_t token, uint64_t target) {
        if (target & ~Memory::ReferenceMoveMask)
            throw std::runtime_error("Invalid reference move mode");
        if (!token && (target & Memory::ReferenceMoveNullable)) return 0;
        return vm.move_memory_reference(token, static_cast<uint32_t>(target & Memory::ReferenceRegionMask));
    }
    static void release(RegisterVM& vm, uint64_t token, uint64_t mode) {
        if (mode & ~Memory::ReferenceNullable)
            throw std::runtime_error("Invalid reference release mode");
        if (!token && (mode & Memory::ReferenceNullable)) return;
        vm.release_memory_borrow(token);
    }
};
}

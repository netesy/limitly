#include "capability_mapper.hh"
#include "vendor/fyra/include/target/capabilities/Capabilities.h"
#include <iostream>

namespace LM {
namespace Backend {
namespace Fyra {

std::optional<CapabilityDescriptor> CapabilityMapper::map(LIR::LIR_Op op) {
    switch (op) {
        // Memory Operations
        case LIR::LIR_Op::MemoryAlloc:
            return CapabilityDescriptor{"memory.alloc", 1, 1, true, true};
        case LIR::LIR_Op::MemoryFree:
            return CapabilityDescriptor{"memory.free", 1, 1, false, false};
        case LIR::LIR_Op::MemoryResize:
            return CapabilityDescriptor{"memory.resize", 2, 2, true, true};
        case LIR::LIR_Op::MemoryCopy:
            return CapabilityDescriptor{"memory.copy", 3, 3, false, false};
        case LIR::LIR_Op::MemoryFill:
            return CapabilityDescriptor{"memory.fill", 3, 3, false, false};
        case LIR::LIR_Op::MemoryCompare:
            return CapabilityDescriptor{"memory.compare", 3, 3, true, false};
        
        // Dynamic Linking Operations
        case LIR::LIR_Op::LibraryLoad:
            return CapabilityDescriptor{"module.load", 1, 1, true, true};
        case LIR::LIR_Op::LibraryUnload:
            return CapabilityDescriptor{"module.unload", 1, 1, false, false};
        case LIR::LIR_Op::LibrarySymbol:
            return CapabilityDescriptor{"module.resolve", 2, 2, true, true};
        
        // Pointer Operations - no capability mapping, use Fyra IR arithmetic directly
        case LIR::LIR_Op::PtrAdd:
        case LIR::LIR_Op::PtrSub:
        case LIR::LIR_Op::PtrDiff:
        case LIR::LIR_Op::PtrAlign:
        case LIR::LIR_Op::PtrIsAligned:
            return std::nullopt;
        
        // Foreign Call Operations - handled directly via createCall/createExternCall
        case LIR::LIR_Op::ForeignCall:
        case LIR::LIR_Op::ForeignCallDirect:
        case LIR::LIR_Op::CallbackCreate:
        case LIR::LIR_Op::CallbackDestroy:
        case LIR::LIR_Op::RegionEnter:
        case LIR::LIR_Op::RegionExit:
        case LIR::LIR_Op::RegionMove:
            return std::nullopt;
        
        default:
            return std::nullopt;
    }
}

} // namespace Fyra
} // namespace Backend
} // namespace LM

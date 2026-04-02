#include "codegen/InstructionFusion.h"

namespace codegen {
namespace target {

FusionCoordinator::FusionCoordinator() {
    // Stub implementation
}

void FusionCoordinator::setTargetArchitecture(const std::string& arch) {
    // Stub implementation
}

void FusionCoordinator::optimizeFunction(ir::Function& func) {
    // Stub implementation
}

void FusionCoordinator::optimizeBasicBlock(ir::BasicBlock& bb) {
    // Stub implementation
}

void FusionCoordinator::setOptimizationLevel(unsigned level) {
    // Stub implementation
    (void)level;
}

} // namespace target
} // namespace codegen

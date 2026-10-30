#pragma once
#include "lir/lir.hh"
#include <string>
#include <vector>
namespace LM::Backend::Native {
// Compile host shared modules with canonical tagged values. Other Fyra targets
// retain their existing target-specific lowering. `native_objects` are
// toolchain-compiled foreign objects (roadmap item 2a) linked into the module.
bool emit_shared_module(const LIR::LIR_Function &, const std::string &module,
                        const std::string &output, int optimization,
                        std::string &error,
                        const std::vector<std::string> &native_objects = {});
} // namespace LM::Backend::Native

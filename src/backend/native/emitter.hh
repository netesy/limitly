#pragma once
#include "lir/lir.hh"
#include <string>
namespace LM::Backend::Native {
// Compile host shared modules with canonical tagged values. Other Fyra targets
// retain their existing target-specific lowering.
bool emit_shared_module(const LIR::LIR_Function &, const std::string &module,
                        const std::string &output, int optimization,
                        std::string &error);
} // namespace LM::Backend::Native

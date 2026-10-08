#pragma once
#include "fyra.hh"
#include "fyra/BackendBuilder.h"
#include "target/core/TargetDescriptor.h"

namespace LM::Backend::Fyra {
::fyra::BuildResult link_standalone_runtime(::fyra::BackendBuilder& backend,
    const FyraCompileOptions& options, const target::TargetDescriptor& target,
    const std::vector<std::string>& libraries);
}

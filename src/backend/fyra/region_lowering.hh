#pragma once
#include <unordered_map>
#include <cstdint>
#include <string>
namespace ir { class Module; }
namespace LM::Backend::Fyra {
void lower_region_ownership(ir::Module& module, const std::unordered_map<std::string, uint64_t>& region_free = {});
}

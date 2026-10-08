#pragma once
namespace ir { class Module; }
namespace LM::Backend::Fyra {
void lower_region_ownership(ir::Module& module);
}

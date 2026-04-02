// builder.hh - LIR to Fyra IR Conversion Builder
#pragma once

#include "../../lir/lir.hh"
#include "ir/Module.h"
#include "ir/Function.h"
#include "ir/IRBuilder.h"
#include "ir/IRContext.h"
#include "ir/Type.h"
#include "ir/Value.h"
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace LM::Backend::Fyra {

class LIRToFyraIRBuilder {
public:
    LIRToFyraIRBuilder(std::shared_ptr<ir::IRContext> context);

    std::shared_ptr<ir::Module> build(const LIR::LIR_Function& lir_func);

    const std::vector<std::string>& get_errors() const { return errors_; }
    bool has_errors() const { return !errors_.empty(); }

private:
    std::shared_ptr<ir::IRContext> context_;
    std::shared_ptr<ir::Module> current_module_;
    std::unique_ptr<ir::IRBuilder> builder_;
    std::unordered_set<std::string> used_builtins_;
    std::vector<std::string> errors_;
    int label_counter_ = 0;

    ir::Type* lir_type_to_fyra_type(LIR::Type lir_type);
    std::string generate_label();
};

} // namespace LM::Backend::Fyra

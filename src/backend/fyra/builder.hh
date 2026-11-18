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

    std::shared_ptr<ir::Module> build(const LIR::LIR_Function& lir_func,
                                      const std::string& exported_module = "");

    const std::vector<std::string>& get_errors() const { return errors_; }
    bool has_errors() const { return !errors_.empty(); }

private:
    std::shared_ptr<ir::IRContext> context_;
    std::shared_ptr<ir::Module> current_module_;
    std::unique_ptr<ir::IRBuilder> builder_;
    std::unordered_set<std::string> used_builtins_;
    std::unordered_map<std::string, int> global_decimal_scales_;
    std::unordered_map<std::string, LIR::Type> global_types_;
    std::vector<std::string> errors_;
    int label_counter_ = 0;
    // Trait dispatch dedupe: one shared helper per (trait, method, arity)
    // instead of inlining the frame_matches candidate chain at every call site.
    std::unordered_map<std::string, ir::Function*> trait_dispatch_helpers_;
    // Frames with a reachable NewFrame instruction. Structural-trait dispatch
    // candidates are restricted to these frames: an unconstructed frame can
    // never be a trait receiver, so its methods can be tree-shaken.
    std::unordered_set<std::string> constructed_frames_;

    ir::Type* lir_type_to_fyra_type(LIR::Type lir_type);
    std::string generate_label();
    void build_function_body(ir::Function* main_fn, const LIR::LIR_Function& lir_func);
};

} // namespace LM::Backend::Fyra

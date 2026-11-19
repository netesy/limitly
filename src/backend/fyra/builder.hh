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
    void set_fs_capabilities(bool enabled) { fs_capabilities_ = enabled; }
    // Syscall targets (Linux/macOS/FreeBSD) cannot express mkdir -p inline in
    // the binary assembler, so their fs.mkdirp capability lowers to a call to
    // the module-level `fyra_mkdir_p` IR helper this builder emits on demand.
    void set_fs_mkdirp_helper(bool enabled) { fs_mkdirp_helper_ = enabled; }

private:
    std::shared_ptr<ir::IRContext> context_;
    std::shared_ptr<ir::Module> current_module_;
    std::unique_ptr<ir::IRBuilder> builder_;
    std::unordered_set<std::string> used_builtins_;
    std::unordered_map<std::string, int> global_decimal_scales_;
    std::unordered_map<std::string, LIR::Type> global_types_;
    std::vector<std::string> errors_;
    int label_counter_ = 0;
    // Windows AOT targets lower std.fs resource ops to native Win32 capability
    // calls (fs.get_attrs/fs.mkdir_p/fs.rename/fs.remove/fs.rmdir) instead of
    // the runtime file service, keeping std::filesystem out of the image.
    bool fs_capabilities_ = false;
    bool fs_mkdirp_helper_ = false;
    bool needs_service_dispatch_ = false;
    bool needs_fs_dispatch_ = false;
    bool needs_mkdirp_helper_ = false;
    // Trait dispatch dedupe: one shared helper per (trait, method, arity)
    // instead of inlining the frame_matches candidate chain at every call site.
    std::unordered_map<std::string, ir::Function*> trait_dispatch_helpers_;
    // Frames with a reachable NewFrame instruction. Structural-trait dispatch
    // candidates are restricted to these frames: an unconstructed frame can
    // never be a trait receiver, so its methods can be tree-shaken.
    std::unordered_set<std::string> constructed_frames_;
    // Reachable function set captured after the worklist fixpoint; used
    // by codegen to omit calls into tree-shaken (pure, unneeded) __init__s.
    std::unordered_set<std::string> reachable_funcs_;
    // String literals occurring in reachable code. Indirect-call dispatch
    // compares runtime callee names against candidate function names; every
    // name that can reach a CallIndirect (fn values, lambdas, task/callback
    // targets) materializes as a LoadConst string literal, so candidates whose
    // qualified or unqualified name never appears as a literal can never
    // match and are omitted from the dispatch chain.
    std::unordered_set<std::string> indirect_literals_;

    ir::Type* lir_type_to_fyra_type(LIR::Type lir_type);
    std::string generate_label();
    void build_function_body(ir::Function* main_fn, const LIR::LIR_Function& lir_func);
};

} // namespace LM::Backend::Fyra

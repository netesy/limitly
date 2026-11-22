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
    // C ABI for direct `import "c:"` struct-by-value lowering: Win64 on
    // Windows targets, SysV AMD64 elsewhere. Non-x64 targets should leave
    // struct signatures on the libffi wrapper path.
    void set_c_abi_windows(bool enabled) { c_abi_windows_ = enabled; }

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
    bool c_abi_windows_ = true;
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

    // `.direct` flattened-ABI variants of eligible LIR functions. Tuple
    // parameters/returns are passed as per-element scalar words (f64 for
    // float elements, i64 otherwise) so small cross-module calls avoid the
    // tagged heap-tuple ABI. The VM is unaffected: this is AOT-only lowering.
    struct DirectParamMap { uint32_t orig; int32_t elem; int32_t domain; };
    struct DirectFnCtx {
        bool sret_return = false;
        bool ret_frame = false; // sret payload is a virtual record, not a tuple
        std::vector<int> ret_domains; // element domains for sret returns
        std::vector<DirectParamMap> params; // per ir::Function parameter
        // orig LIR reg -> field domains for INOUT record params (elem == -2).
        std::unordered_map<uint32_t, std::vector<int>> inout_domains;
    };
    // Per-original-parameter element domains for tuple/record params (empty =
    // scalar passthrough). Domains use the VDom encoding from builder.cpp.
    // param_inout[i] != 0 marks a record param passed as a pointer to a
    // caller-owned field buffer so callee mutations propagate back.
    struct DirectFnSig {
        bool eligible = false;
        std::vector<std::vector<int>> param_elem_domains;
        std::vector<char> param_inout;
        bool ret_sret = false;
        bool ret_frame = false;
        std::vector<int> ret_domains;
        bool ret_float = false;
        // Callee returns nil: the .direct result is the constant VAL_NIL (2),
        // so callers can store a provably-scalar constant instead of the call
        // result and skip the region edge on the destination slot.
        bool ret_nil = false;
    };

    ir::Type* lir_type_to_fyra_type(LIR::Type lir_type);
    std::string generate_label();
    void build_function_body(ir::Function* main_fn, const LIR::LIR_Function& lir_func,
                             const DirectFnCtx* dctx = nullptr);
    const DirectFnSig* direct_sig_for(const std::string& name);
    // Virtual-tuple safety proof for one LIR function under one lowering
    // mode (sig != nullptr ⇒ `.direct` flattened ABI). safe[r] is true when
    // register r is guaranteed to remain a virtual tuple — every use is
    // virtual-compatible, so no heap tuple is ever materialized and
    // RegionMove on it emits nothing. def_inst_idx maps each defined
    // register to its last defining instruction index.
    struct VtSafeInfo {
        std::unordered_map<uint32_t, bool> safe;
        std::unordered_map<uint32_t, size_t> def_inst_idx;
        // Loop-variant virtual tuples: register -> canonical element spill
        // registers (+ their VDom domains). Single-pass lowering cannot
        // represent the phi at a CFG back-edge, so every definition stores
        // element values into these slots and every use reloads them.
        std::unordered_map<uint32_t, std::vector<uint32_t>> canon_regs;
        std::unordered_map<uint32_t, std::vector<int>> canon_domains;
    };
    VtSafeInfo compute_vt_safe(const LIR::LIR_Function& fn, const DirectFnSig* sig);
    // Frame field-domain table: LIR FrameType extras never carry field
    // types, so domains are recovered from FrameGetField/FrameSetField
    // evidence across all registered functions plus NewFrame field counts.
    struct FrameFieldInfo {
        int field_count = -1;
        std::vector<int> domains; // VDom per field; VDOM_INVALID = conflict
        bool deinit = false;
    };
    void build_frame_field_table();
    const FrameFieldInfo* frame_field_info(const std::string& name);
    // Resolve flattenable field domains or nullptr (unknown/oversized/
    // conflicting/deinit). Unobserved fields degrade to VDOM_TAGGED.
    static const std::vector<int>* frame_flat_domains(const FrameFieldInfo* info,
                                                      std::vector<int>& scratch);
    std::unordered_map<std::string, DirectFnSig> direct_sigs_;
    std::unordered_map<std::string, DirectFnCtx> direct_contexts_;
    std::unordered_map<std::string, FrameFieldInfo> frame_fields_;
    bool frame_fields_built_ = false;
};

} // namespace LM::Backend::Fyra

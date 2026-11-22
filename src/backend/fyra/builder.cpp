#include "../../memory/reference_flags.hh"
#include "../../memory/region_analysis.hh"
#include <cstring>
#include <cstdlib>
#include <iostream>
// builder.cpp - LIR to Fyra IR Conversion Implementation
#include "builder.hh"
#include "../../lir/lir.hh"
#include "capability_mapper.hh"
#include "ir/Module.h"
#include "ir/Function.h"
#include "ir/IRBuilder.h"
#include "ir/IRContext.h"
#include "ir/Type.h"
#include "ir/Value.h"
#include "ir/Constant.h"
#include "fyra_builtin_functions.hh"
#include "region_lowering.hh"
#include "backend/vm/vm_value.hh"
#include "backend/vm/vm_value_base.hh"
#include "backend/vm/vm_runtime.hh"
#include <unordered_map>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "../../lir/function_registry.hh"
#include "../../lir/builtin_functions.hh"
#include "../../lir/builtin_callable.hh"
#include "../../frontend/module_manager.hh"
#include "backend/native/binding_generator.hh"

namespace LM::Backend::Fyra {

// Element domains for virtual (unboxed) tuple values and the `.direct`
// flattened call ABI. Every domain occupies exactly one 8-byte slot:
// Float -> f64 bits, Int/Bool -> raw i64, Ptr -> raw address, Tagged ->
// tagged LmValue word. Invalid marks types that cannot cross the boundary.
enum VDom : int { VDOM_INT = 0, VDOM_FLOAT = 1, VDOM_BOOL = 2, VDOM_PTR = 3, VDOM_TAGGED = 4, VDOM_INVALID = 5 };

static VDom vdom_of_type(const TypePtr& t, LIR::Type fallback = LIR::Type::Void) {
    if (!t) {
        if (fallback == LIR::Type::F64 || fallback == LIR::Type::F32) return VDOM_FLOAT;
        if (fallback == LIR::Type::Bool) return VDOM_BOOL;
        if (fallback == LIR::Type::Ptr) return VDOM_PTR;
        return VDOM_INT;
    }
    switch (t->tag) {
        case ::TypeTag::Float32: case ::TypeTag::Float64: return VDOM_FLOAT;
        case ::TypeTag::Bool: return VDOM_BOOL;
        case ::TypeTag::Int: case ::TypeTag::Int8: case ::TypeTag::Int16:
        case ::TypeTag::Int32: case ::TypeTag::Int64:
        case ::TypeTag::UInt: case ::TypeTag::UInt8: case ::TypeTag::UInt16:
        case ::TypeTag::UInt32: case ::TypeTag::UInt64: return VDOM_INT;
        case ::TypeTag::Any: case ::TypeTag::Union: case ::TypeTag::ErrorUnion:
        case ::TypeTag::Sum: case ::TypeTag::Function: case ::TypeTag::Closure:
        case ::TypeTag::Module: case ::TypeTag::Range: case ::TypeTag::Channel:
        case ::TypeTag::Nil: return VDOM_TAGGED;
        case ::TypeTag::String: case ::TypeTag::List: case ::TypeTag::Dict:
        case ::TypeTag::Frame: case ::TypeTag::Enum: case ::TypeTag::Trait:
        case ::TypeTag::TraitObject: case ::TypeTag::UserDefined:
        case ::TypeTag::Tuple: return VDOM_PTR;
        default: return VDOM_INVALID;
    }
}

// Recover per-field domains for a named frame from LIR evidence: NewFrame
// carries the field count in imm; FrameGetField/FrameSetField carry the
// field index and the accessed value's language/ABI type. Names may be
// module-qualified or bare depending on which module declared the access,
// so lookups fall back to a unique unqualified-tail match.
void LIRToFyraIRBuilder::build_frame_field_table() {
    if (frame_fields_built_) return;
    frame_fields_built_ = true;
    auto& registry = LIR::FunctionRegistry::getInstance();
    auto frame_name_of = [](const LIR::LIR_Function& f, uint32_t r) -> std::string {
        if (r == UINT32_MAX) return {};
        auto it = f.register_language_types.find(r);
        if (it == f.register_language_types.end() || !it->second ||
            it->second->tag != ::TypeTag::Frame) return {};
        auto* ft = std::get_if<FrameType>(&it->second->extra);
        return ft ? ft->name : std::string{};
    };
    auto reg_vdom = [](const LIR::LIR_Function& f, uint32_t r, LIR::Type fb) -> int {
        auto it = f.register_language_types.find(r);
        if (it != f.register_language_types.end() && it->second)
            return vdom_of_type(it->second, fb);
        return vdom_of_type(TypePtr(), fb);
    };
    // evidence slots: -1 = never observed (resolves to VDOM_TAGGED, the safe
    // boxed-word domain); otherwise a bitmask of observed domains (bit d set
    // when domain d was seen). Conflicting observations are resolved in
    // frame_flat_domains: a set containing VDOM_TAGGED collapses to TAGGED
    // (every domain normalizes to an LmValue word through tag_word on store
    // and erased/union reads always consume a word); scalar-only conflicts
    // reject flattening.
    auto note_domain = [&](const std::string& fname, uint32_t idx, int dom) {
        if (fname.empty() || idx == UINT32_MAX) return;
        auto& info = frame_fields_[fname];
        if (info.field_count == -2 ||
            (info.field_count >= 0 && idx >= static_cast<uint32_t>(info.field_count))) {
            if (info.domains.size() <= idx) info.domains.resize(idx + 1, -1);
            info.domains[idx] = 1 << VDOM_INVALID;
            return;
        }
        if (info.domains.size() <= idx) info.domains.resize(idx + 1, -1);
        int& slot = info.domains[idx];
        if (slot == -1) slot = 0;
        slot |= 1 << dom;
    };
    auto names = registry.getFunctionNames();
    for (const auto& fname : names) {
        auto* f = registry.getFunction(fname);
        if (!f) continue;
        for (const auto& in : f->instructions) {
            switch (in.op) {
                case LIR::LIR_Op::NewFrame: {
                    std::string nm = !in.type_name.empty() ? in.type_name : in.func_name;
                    if (nm.empty()) break;
                    auto& info = frame_fields_[nm];
                    int cnt = static_cast<int>(in.imm);
                    if (info.field_count < 0) info.field_count = cnt;
                    else if (info.field_count != cnt) info.field_count = -2; // conflict
                    break;
                }
                case LIR::LIR_Op::FrameSetField: {
                    std::string nm = frame_name_of(*f, in.dst);
                    int dom = reg_vdom(*f, in.b, in.type_b);
                    note_domain(nm, in.a, dom);
                    break;
                }
                case LIR::LIR_Op::FrameGetField: {
                    std::string nm = frame_name_of(*f, in.a);
                    uint32_t idx = (in.b != UINT32_MAX) ? in.b : in.imm;
                    int dom = reg_vdom(*f, in.dst, in.result_type);
                    note_domain(nm, idx, dom);
                    break;
                }
                default: break;
            }
        }
    }
    // Deinit frames can never be virtualized: scope-exit cleanup must run on
    // a real object. Function names are `<frame>.deinit`; match on the full
    // name and on the unqualified tail to cover alias spellings.
    auto tail_of = [](const std::string& n) {
        size_t d = n.rfind('.');
        return d == std::string::npos ? n : n.substr(d + 1);
    };
    std::vector<std::string> tails;
    for (const auto& [k, v] : frame_fields_) tails.push_back(tail_of(k));
    for (const auto& fname : names) {
        const std::string suf = ".deinit";
        if (fname.size() <= suf.size() || fname.compare(fname.size() - suf.size(), suf.size(), suf) != 0) continue;
        std::string base = fname.substr(0, fname.size() - suf.size());
        std::string btail = tail_of(base);
        for (size_t i = 0; i < tails.size(); ++i) {
            // Deliberately over-approximate: a same-tail deinit in any module
            // disqualifies the frame (safe direction).
            (void)i;
        }
        for (auto& [k, info] : frame_fields_) {
            if (k == base || tail_of(k) == btail) info.deinit = true;
        }
        // The deinit frame may have no other evidence yet; record it anyway.
        frame_fields_[base].deinit = true;
    }
}

// Resolve a frame's flattenable field domains: nullptr when the frame is
// unknown, oversized, has conflicting/non-scalar field evidence, or has a
// deinit. Unobserved fields degrade to VDOM_TAGGED (boxed LmValue words).
const std::vector<int>* LIRToFyraIRBuilder::frame_flat_domains(const FrameFieldInfo* info,
                                                             std::vector<int>& scratch) {
    if (!info || info->field_count < 1 || info->field_count > 8 || info->deinit ||
        info->field_count == -2) return nullptr;
    scratch.clear();
    scratch.reserve(info->field_count);
    for (int i = 0; i < info->field_count; ++i) {
        int mask = (i < static_cast<int>(info->domains.size())) ? info->domains[i] : -1;
        int d;
        if (mask == -1) {
            d = VDOM_TAGGED; // never observed: boxed-word domain
        } else if (mask & (1 << VDOM_INVALID)) {
            return nullptr; // out-of-range or unclassifiable evidence
        } else if (mask & (1 << VDOM_TAGGED)) {
            // `any`/union field seen with mixed representations: every store
            // normalizes through tag_word and erased reads consume the word,
            // so the tagged domain is always the correct common denominator.
            d = VDOM_TAGGED;
        } else if ((mask & (mask - 1)) == 0) {
            d = __builtin_ctz(static_cast<unsigned>(mask)); // single domain
        } else {
            return nullptr; // genuine scalar conflict (e.g. int vs float)
        }
        // PTR fields hold raw object addresses; the pointee stays a normal
        // heap value and canon-slot stores keep their region edge, so they
        // scalarize like scalars. TAGGED covers `any`/union erased words.
        if (d != VDOM_INT && d != VDOM_FLOAT && d != VDOM_BOOL &&
            d != VDOM_TAGGED && d != VDOM_PTR)
            return nullptr;
        scratch.push_back(d);
    }
    return &scratch;
}

const LIRToFyraIRBuilder::FrameFieldInfo* LIRToFyraIRBuilder::frame_field_info(const std::string& name) {
    build_frame_field_table();
    auto it = frame_fields_.find(name);
    if (it != frame_fields_.end()) return &it->second;
    // Unique unqualified-tail fallback for alias/qualified name mismatches.
    std::string tail = name;
    size_t d = name.rfind('.');
    if (d != std::string::npos) tail = name.substr(d + 1);
    const FrameFieldInfo* found = nullptr;
    for (const auto& [k, info] : frame_fields_) {
        std::string kt = k;
        size_t kd = k.rfind('.');
        if (kd != std::string::npos) kt = k.substr(kd + 1);
        if (kt == tail) {
            if (found) return nullptr; // ambiguous tail: refuse to guess
            found = &info;
        }
    }
    return found;
}

// One element of a virtual tuple: either a direct SSA value (function
// parameters of `.direct` variants and sret loads) or a reference to the
// source register whose slot is reloaded at each use (keeps loads
// control-flow correct across CFG joins).
struct VTupleElem {
    ir::Value* direct_v = nullptr;
    uint32_t src_reg = UINT32_MAX;
    LIR::Type src_type = LIR::Type::Void;
    int domain = VDOM_INT;
    bool has = false;
    // Canonical spill-slot element: src_reg is a pseudo register whose slot
    // every definition writes and every use reloads (loop-variant tuples).
    // Virtual records always use this form so `var q = p` shares the same
    // element slots and field writes stay visible through every alias.
    bool canon_elem = false;
    // INOUT record-parameter element: the value lives in the caller-owned
    // field buffer at mem_base + mem_idx * 8 so callee FrameSetField writes
    // propagate back to the caller's slots after the call.
    ir::Value* mem_base = nullptr;
    uint32_t mem_idx = 0;
};

// Register-domain classification, factored out of build_function_body so the
// region-purity analysis can compute the same pointer/tagged sets for callee
// functions (each function's RegionMove neutrality must use its own sets).
static bool s_lang_type_is_erased(const LIR::LIR_Function& f, uint32_t reg) {
    auto it = f.register_language_types.find(reg);
    if (it == f.register_language_types.end() || !it->second) return false;
    switch (it->second->tag) {
        case ::TypeTag::Any: case ::TypeTag::Union: case ::TypeTag::ErrorUnion:
        case ::TypeTag::Nil: case ::TypeTag::String: case ::TypeTag::List:
        case ::TypeTag::Dict: case ::TypeTag::Tuple: case ::TypeTag::Frame:
        case ::TypeTag::Enum: case ::TypeTag::Trait: case ::TypeTag::TraitObject:
        case ::TypeTag::Sum: case ::TypeTag::Function: case ::TypeTag::Closure:
        case ::TypeTag::Module: case ::TypeTag::Range: case ::TypeTag::Channel:
        case ::TypeTag::Int128: case ::TypeTag::UInt128:
            return true;
        default:
            return false;
    }
}

// True when the register's language type is an aggregate record (frame or
// tuple): such registers may hold a virtual container whose elements live
// in scalar slots, so they never need the erased tagged word a plain
// `any`/union destination would.
static bool s_lang_type_is_record(const LIR::LIR_Function& f, uint32_t reg) {
    auto it = f.register_language_types.find(reg);
    if (it == f.register_language_types.end() || !it->second) return false;
    return it->second->tag == ::TypeTag::Frame || it->second->tag == ::TypeTag::Tuple;
}

static bool s_lang_type_holds_tagged_word(const LIR::LIR_Function& f, uint32_t reg) {
    auto it = f.register_language_types.find(reg);
    if (it == f.register_language_types.end() || !it->second) return false;
    switch (it->second->tag) {
        case ::TypeTag::Any: case ::TypeTag::Union: case ::TypeTag::ErrorUnion:
        case ::TypeTag::Sum: case ::TypeTag::Function: case ::TypeTag::Closure:
        case ::TypeTag::Module: case ::TypeTag::Range: case ::TypeTag::Channel:
        case ::TypeTag::Int128: case ::TypeTag::UInt128:
            return true;
        default:
            return false;
    }
}

static bool s_is_typed_primitive_list(const LIR::LIR_Function& f, uint32_t r) {
    auto it = f.register_language_types.find(r);
    if (it != f.register_language_types.end() && it->second && it->second->tag == ::TypeTag::List) {
        auto* lt = std::get_if<ListType>(&it->second->extra);
        if (lt && lt->elementType) {
            auto etag = lt->elementType->tag;
            if (etag != ::TypeTag::List && etag != ::TypeTag::String &&
                etag != ::TypeTag::Frame && etag != ::TypeTag::Dict &&
                etag != ::TypeTag::Tuple && etag != ::TypeTag::Any &&
                etag != ::TypeTag::Enum && etag != ::TypeTag::Trait &&
                etag != ::TypeTag::TraitObject &&
                etag != ::TypeTag::Union && etag != ::TypeTag::ErrorUnion &&
                etag != ::TypeTag::Nil &&
                etag != ::TypeTag::Float32 &&
                etag != ::TypeTag::Decimal2 && etag != ::TypeTag::Decimal4 &&
                etag != ::TypeTag::Decimal6) {
                return true;
            }
        }
    }
    return false;
}

static uint64_t s_typed_list_element_kind(const LIR::LIR_Function& f, uint32_t r) {
    if (!s_is_typed_primitive_list(f, r)) return 0;
    auto it = f.register_language_types.find(r);
    if (it == f.register_language_types.end() || !it->second) return 0;
    auto* lt = std::get_if<ListType>(&it->second->extra);
    if (!lt || !lt->elementType) return 0;
    switch (lt->elementType->tag) {
        case ::TypeTag::Bool: return 2;
        case ::TypeTag::Int: case ::TypeTag::Int8: case ::TypeTag::Int16:
        case ::TypeTag::Int32: case ::TypeTag::Int64:
        case ::TypeTag::UInt: case ::TypeTag::UInt8: case ::TypeTag::UInt16:
        case ::TypeTag::UInt32: case ::TypeTag::UInt64:
            return 1;
        case ::TypeTag::Float64:
            return 3;
        default: return 0;
    }
}

static bool s_bitwise_operand_erased(const LIR::LIR_Function& f, uint32_t reg, LIR::Type type) {
    if (reg == UINT32_MAX) return false;
    if (type == LIR::Type::Ptr) return true;
    auto rt = f.register_types.find(reg);
    if (rt != f.register_types.end() && rt->second == LIR::Type::Ptr) return true;
    auto lt = f.register_language_types.find(reg);
    if (lt != f.register_language_types.end() && lt->second &&
        (lt->second->tag == ::TypeTag::Int128 || lt->second->tag == ::TypeTag::UInt128)) return true;
    return false;
}

static bool s_declared_scalar(const LIR::LIR_Function& f, uint32_t reg) {
    auto it = f.register_language_types.find(reg);
    if (it != f.register_language_types.end() && it->second) {
        switch (it->second->tag) {
            case ::TypeTag::Bool:
            case ::TypeTag::Int: case ::TypeTag::Int8: case ::TypeTag::Int16:
            case ::TypeTag::Int32: case ::TypeTag::Int64:
            case ::TypeTag::UInt: case ::TypeTag::UInt8: case ::TypeTag::UInt16:
            case ::TypeTag::UInt32: case ::TypeTag::UInt64:
            case ::TypeTag::Float32: case ::TypeTag::Float64:
            case ::TypeTag::Decimal2: case ::TypeTag::Decimal4: case ::TypeTag::Decimal6:
                return true;
            default: break;
        }
    }
    return false;
}

static bool s_lang_type_is_pointerish(const LIR::LIR_Function& f, uint32_t reg) {
    auto it = f.register_language_types.find(reg);
    if (it != f.register_language_types.end() && it->second) {
        auto tag = it->second->tag;
        if (tag == ::TypeTag::List || tag == ::TypeTag::String || tag == ::TypeTag::Frame ||
            tag == ::TypeTag::Dict || tag == ::TypeTag::Tuple || tag == ::TypeTag::Any ||
            tag == ::TypeTag::Enum || tag == ::TypeTag::Trait || tag == ::TypeTag::TraitObject ||
            tag == ::TypeTag::Union || tag == ::TypeTag::ErrorUnion || tag == ::TypeTag::Sum ||
            tag == ::TypeTag::Function || tag == ::TypeTag::Closure || tag == ::TypeTag::Module ||
            tag == ::TypeTag::Range || tag == ::TypeTag::Channel ||
            tag == ::TypeTag::Nil || tag == ::TypeTag::Int128 || tag == ::TypeTag::UInt128)
            return true;
    }
    auto it2 = f.register_types.find(reg);
    if (it2 != f.register_types.end() && it2->second == LIR::Type::Ptr) return true;
    return false;
}

struct RegDomainSets {
    std::unordered_set<uint32_t> pointer_assigned;
    std::unordered_set<uint32_t> tagged_word;
};

// Pointer/tagged-word register classification for one LIR function. Mirrors
// the prepass inside build_function_body verbatim; kept in sync by sharing
// the s_* helpers above.
static RegDomainSets compute_reg_domain_sets(const LIR::LIR_Function& lir_func) {
    RegDomainSets out;
    auto& pointer_assigned_regs = out.pointer_assigned;
    auto& tagged_word_regs = out.tagged_word;
    auto lang_type_is_erased = [&](uint32_t reg) -> bool { return s_lang_type_is_erased(lir_func, reg); };
    auto lang_type_holds_tagged_word = [&](uint32_t reg) -> bool { return s_lang_type_holds_tagged_word(lir_func, reg); };
    auto is_typed_primitive_list = [&](uint32_t r) -> bool { return s_is_typed_primitive_list(lir_func, r); };
    auto bitwise_operand_erased = [&](uint32_t reg, LIR::Type type) { return s_bitwise_operand_erased(lir_func, reg, type); };
    auto declared_scalar = [&](uint32_t reg) -> bool { return s_declared_scalar(lir_func, reg); };
    for (const auto& inst : lir_func.instructions) {
        if (inst.dst == UINT32_MAX) continue;
        switch (inst.op) {
            case LIR::LIR_Op::ListCreate:
            case LIR::LIR_Op::TupleCreate:
            case LIR::LIR_Op::DictCreate:
            case LIR::LIR_Op::RefCreate:
            case LIR::LIR_Op::RefResolve:
            case LIR::LIR_Op::RefMove:
            case LIR::LIR_Op::NewFrame:
            case LIR::LIR_Op::MakeEnum:
            case LIR::LIR_Op::ToString:
            case LIR::LIR_Op::STR_CONCAT:
            case LIR::LIR_Op::STR_FORMAT:
            case LIR::LIR_Op::StringIndex:
            case LIR::LIR_Op::ConstructError:
            case LIR::LIR_Op::ConstructOk:
            case LIR::LIR_Op::Unwrap:
            case LIR::LIR_Op::UnwrapOr:
            case LIR::LIR_Op::DictItems:
            case LIR::LIR_Op::ResourceCreate:
            case LIR::LIR_Op::ChannelAlloc:
            case LIR::LIR_Op::MemoryAlloc:
            case LIR::LIR_Op::MemoryResize:
            case LIR::LIR_Op::LibraryLoad:
            case LIR::LIR_Op::LibrarySymbol:
            case LIR::LIR_Op::ForeignCall:
            case LIR::LIR_Op::CallbackCreate:
                pointer_assigned_regs.insert(inst.dst);
                if (inst.op == LIR::LIR_Op::LibraryLoad ||
                    inst.op == LIR::LIR_Op::LibrarySymbol ||
                    (inst.op == LIR::LIR_Op::CallbackCreate && inst.imm == 1))
                    tagged_word_regs.insert(inst.dst);
                break;
            case LIR::LIR_Op::MemoryLoad:
                if (inst.imm >= 8) pointer_assigned_regs.insert(inst.dst);
                break;
            case LIR::LIR_Op::LoadGlobal: {
                auto lt = lir_func.register_language_types.find(inst.dst);
                bool scalar_global = false;
                if (lt != lir_func.register_language_types.end() && lt->second) {
                    switch (lt->second->tag) {
                        case ::TypeTag::Bool:
                        case ::TypeTag::Int: case ::TypeTag::Int8: case ::TypeTag::Int16:
                        case ::TypeTag::Int32: case ::TypeTag::Int64: case ::TypeTag::Int128:
                        case ::TypeTag::UInt: case ::TypeTag::UInt8: case ::TypeTag::UInt16:
                        case ::TypeTag::UInt32: case ::TypeTag::UInt64: case ::TypeTag::UInt128:
                        case ::TypeTag::Float32: case ::TypeTag::Float64:
                        case ::TypeTag::Decimal2: case ::TypeTag::Decimal4: case ::TypeTag::Decimal6:
                            scalar_global = true;
                            break;
                        default:
                            break;
                    }
                }
                if (!scalar_global) {
                    pointer_assigned_regs.insert(inst.dst);
                    if (lang_type_is_erased(inst.dst)) tagged_word_regs.insert(inst.dst);
                }
                break;
            }
            case LIR::LIR_Op::LoadConst:
                if (IS_PTR(inst.const_val)) pointer_assigned_regs.insert(inst.dst);
                break;
            case LIR::LIR_Op::Cast:
                if (inst.result_type == LIR::Type::Ptr) pointer_assigned_regs.insert(inst.dst);
                break;
            case LIR::LIR_Op::DictGet:
            case LIR::LIR_Op::TupleGet:
            case LIR::LIR_Op::FrameGetField:
                if (lang_type_is_erased(inst.dst)) {
                    pointer_assigned_regs.insert(inst.dst);
                    if (lang_type_holds_tagged_word(inst.dst)) tagged_word_regs.insert(inst.dst);
                }
                break;
            case LIR::LIR_Op::ListIndex:
                if (!is_typed_primitive_list(inst.a) && lang_type_holds_tagged_word(inst.dst)) {
                    pointer_assigned_regs.insert(inst.dst);
                    tagged_word_regs.insert(inst.dst);
                }
                break;
            case LIR::LIR_Op::IAdd_Unchecked:
            case LIR::LIR_Op::Add:
            case LIR::LIR_Op::Sub:
            case LIR::LIR_Op::Mul:
            case LIR::LIR_Op::Div:
            case LIR::LIR_Op::Mod:
            case LIR::LIR_Op::Neg: {
                auto operand_may_be_erased = [&](uint32_t reg, LIR::Type type) {
                    if (reg == UINT32_MAX) return false;
                    if (type == LIR::Type::Ptr || type == LIR::Type::U64) return true;
                    auto rt = lir_func.register_types.find(reg);
                    if (rt != lir_func.register_types.end() &&
                        (rt->second == LIR::Type::Ptr || rt->second == LIR::Type::U64)) return true;
                    auto lt = lir_func.register_language_types.find(reg);
                    if (lt != lir_func.register_language_types.end() && lt->second) {
                        if (lt->second->tag == ::TypeTag::Int128 || lt->second->tag == ::TypeTag::UInt128)
                            return true;
                        switch (lt->second->tag) {
                            case ::TypeTag::Any: case ::TypeTag::Union: case ::TypeTag::ErrorUnion:
                            case ::TypeTag::Sum: case ::TypeTag::Function: case ::TypeTag::Closure:
                            case ::TypeTag::Module: case ::TypeTag::Range: case ::TypeTag::Channel:
                                return true;
                            default: break;
                        }
                    }
                    return false;
                };
                if ((operand_may_be_erased(inst.a, inst.type_a) ||
                     operand_may_be_erased(inst.b, inst.type_b)) &&
                    lang_type_holds_tagged_word(inst.dst)) {
                    pointer_assigned_regs.insert(inst.dst);
                    tagged_word_regs.insert(inst.dst);
                }
                break;
            }
            case LIR::LIR_Op::Shl:
            case LIR::LIR_Op::Shr:
            case LIR::LIR_Op::And:
            case LIR::LIR_Op::Or:
            case LIR::LIR_Op::Xor:
            case LIR::LIR_Op::IAnd_Unchecked:
            case LIR::LIR_Op::IOr_Unchecked:
            case LIR::LIR_Op::IXor_Unchecked:
                if ((bitwise_operand_erased(inst.a, inst.type_a) ||
                     bitwise_operand_erased(inst.b, inst.type_b) ||
                     bitwise_operand_erased(inst.dst, LIR::Type::I64)) &&
                    lang_type_holds_tagged_word(inst.dst)) {
                    pointer_assigned_regs.insert(inst.dst);
                    tagged_word_regs.insert(inst.dst);
                }
                break;
            case LIR::LIR_Op::ChannelPop:
            case LIR::LIR_Op::ChannelRecv:
            case LIR::LIR_Op::ChannelPoll:
                if (lang_type_holds_tagged_word(inst.dst))
                    tagged_word_regs.insert(inst.dst);
                break;
            case LIR::LIR_Op::Call:
            case LIR::LIR_Op::CallVoid: {
                if (!inst.func_name.empty()) {
                    if (auto* cf = LIR::FunctionRegistry::getInstance().getFunction(inst.func_name)) {
                        auto* rt = cf->return_language_type.get();
                        if (rt) {
                            switch (rt->tag) {
                                case ::TypeTag::Int: case ::TypeTag::Int8: case ::TypeTag::Int16:
                                case ::TypeTag::Int32: case ::TypeTag::Int64:
                                case ::TypeTag::UInt: case ::TypeTag::UInt8: case ::TypeTag::UInt16:
                                case ::TypeTag::UInt32: case ::TypeTag::UInt64:
                                case ::TypeTag::Bool:
                                case ::TypeTag::Float32: case ::TypeTag::Float64:
                                case ::TypeTag::Decimal2: case ::TypeTag::Decimal4: case ::TypeTag::Decimal6:
                                    break;
                                default:
                                    tagged_word_regs.insert(inst.dst);
                                    break;
                            }
                        }
                    }
                }
                break;
            }
            default:
                if (inst.result_type == LIR::Type::Ptr || lang_type_is_erased(inst.dst))
                    pointer_assigned_regs.insert(inst.dst);
                break;
        }
        if (inst.op == LIR::LIR_Op::Unwrap || inst.op == LIR::LIR_Op::UnwrapOr) {
            if (lang_type_holds_tagged_word(inst.dst))
                tagged_word_regs.insert(inst.dst);
        }
    }
    bool moved = true;
    while (moved) {
        moved = false;
        for (const auto& inst : lir_func.instructions) {
            if (inst.op == LIR::LIR_Op::Mov && inst.dst != UINT32_MAX) {
                bool dst_erased = false;
                auto dlt = lir_func.register_language_types.find(inst.dst);
                if (dlt != lir_func.register_language_types.end() && dlt->second &&
                    lang_type_is_erased(inst.dst)) dst_erased = true;
                if ((inst.a != UINT32_MAX && tagged_word_regs.count(inst.a)) || dst_erased) {
                    if (tagged_word_regs.insert(inst.dst).second) moved = true;
                }
            }
            if (inst.dst == UINT32_MAX || pointer_assigned_regs.count(inst.dst) || declared_scalar(inst.dst)) continue;
            bool propagate = false;
            if (inst.op == LIR::LIR_Op::Mov) {
                propagate = inst.a != UINT32_MAX && pointer_assigned_regs.count(inst.a);
            } else if (inst.op == LIR::LIR_Op::IAdd_Unchecked || inst.op == LIR::LIR_Op::Add ||
                       inst.op == LIR::LIR_Op::Sub || inst.op == LIR::LIR_Op::Mul ||
                       inst.op == LIR::LIR_Op::Div || inst.op == LIR::LIR_Op::Mod ||
                       inst.op == LIR::LIR_Op::Neg) {
                propagate = (inst.a != UINT32_MAX && pointer_assigned_regs.count(inst.a)) ||
                            (inst.b != UINT32_MAX && pointer_assigned_regs.count(inst.b));
            }
            if (propagate) {
                pointer_assigned_regs.insert(inst.dst);
                moved = true;
            }
        }
    }
    for (auto it = pointer_assigned_regs.begin(); it != pointer_assigned_regs.end();) {
        if (declared_scalar(*it)) it = pointer_assigned_regs.erase(it);
        else ++it;
    }
    return out;
}

namespace {
// Byte size of a scalar CType, mirroring the header parser's struct layout
// (used for SysV eightbyte classification of struct fields).
uint32_t c_scalar_size(const LM::Backend::Native::CType& t) {
    using LM::Backend::Native::CType;
    switch (t.kind) {
        case CType::Bool: case CType::Char: return 1;
        case CType::Short: return 2;
        case CType::Int: case CType::Float: return 4;
        case CType::Long: case CType::LongLong: case CType::Double:
        case CType::Ptr: return 8;
        case CType::FixedWidth: return t.width > 0 ? uint32_t((t.width + 7) / 8) : 8;
        default: return 8;
    }
}
} // namespace

// Private assembler symbols must be injective in the canonical LIR identity.
// Replacing dots with underscores also merges a.b_c with a_b.c.
static std::string global_symbol(const std::string& canonical) {
    std::string symbol="__lymar_global_";
    const char* hex="0123456789abcdef";
    for(unsigned char character:canonical) {
        if((character>='a' && character<='z') || (character>='A' && character<='Z') ||
           (character>='0' && character<='9')) symbol+=character;
        else if(character=='_') symbol+="_u";
        else if(character=='.') symbol+="_d";
        else {symbol+="_x";symbol+=hex[character>>4];symbol+=hex[character&15];}
    }
    return symbol;
}

static inline uint32_t get_frame_field_offset(uint32_t field_index) {
    constexpr uint32_t header_size = 8;
    constexpr uint32_t field_stride = 8;
    return header_size + (field_index * field_stride);
}

static inline uint32_t get_frame_type_size(uint32_t field_count) {
    constexpr uint32_t header_size = 8;
    constexpr uint32_t field_stride = 8;
    uint32_t effective_fields = (field_count > 0) ? field_count : 2;
    return header_size + (effective_fields * field_stride);
}

LIRToFyraIRBuilder::LIRToFyraIRBuilder(std::shared_ptr<ir::IRContext> context)
    : context_(context), builder_(std::make_unique<ir::IRBuilder>(context)) {
}

ir::Type* LIRToFyraIRBuilder::lir_type_to_fyra_type(LIR::Type lir_type) {
    switch (lir_type) {
        case LIR::Type::Void: return context_->getIntegerType(64);
        case LIR::Type::I64:
        case LIR::Type::Bool: return context_->getIntegerType(64);
        case LIR::Type::F64: return context_->getDoubleType();
        case LIR::Type::Ptr: return context_->getPointerType(context_->getIntegerType(8));
        default: return context_->getIntegerType(64);
    }
}

std::string LIRToFyraIRBuilder::generate_label() {
    return "label_" + std::to_string(label_counter_++);
}

std::shared_ptr<ir::Module> LIRToFyraIRBuilder::build(const LIR::LIR_Function& lir_func,
                                                   const std::string& exported_module) {
    LIR::LIRBuiltinFunctions::getInstance().initialize();
    current_module_ = std::make_shared<ir::Module>(lir_func.name, context_);
    builder_->setModule(current_module_.get());
    used_builtins_.clear();

    auto& registry = LIR::FunctionRegistry::getInstance();

    // Perform reachability analysis starting from entry and exported module symbols
    std::unordered_set<std::string> reachable_funcs;
    std::vector<std::string> worklist;

    if (!lir_func.name.empty()) {
        reachable_funcs.insert(lir_func.name);
        worklist.push_back(lir_func.name);
    }

    if (lir_func.name == "__top_level_wrapper__" && registry.getFunction("main")) {
        reachable_funcs.insert("main");
        worklist.push_back("main");
    }

    // Exported module functions and module initialization entry points act as reachability roots.
    // Identify target module prefixes (modules whose .__init__ function is present)
    std::vector<std::string> mod_prefixes;
    for (const auto& fname : registry.getFunctionNames()) {
        if (fname.ends_with(".__init__")) {
            std::string prefix = fname.substr(0, fname.length() - std::string(".__init__").size());
            // Dependencies are reached through calls, not through all their
            // unused exports. Only the library being built is an export root.
            if (!prefix.empty() && prefix == exported_module) mod_prefixes.push_back(prefix);
        }
    }

        // Also add all functions matching module prefixes or non-std functions
        for (const auto& fname : registry.getFunctionNames()) {
            for (const auto& pfx : mod_prefixes) {
                if (fname.rfind(pfx + ".", 0) == 0) {
                    if (!reachable_funcs.count(fname)) {
                        reachable_funcs.insert(fname);
                        worklist.push_back(fname);
                    }
                }
            }
        }

    for (const auto& pfx : mod_prefixes) {
        std::string init_sym = pfx + ".__init__";
        if (registry.getFunction(init_sym) && !reachable_funcs.count(init_sym)) {
            reachable_funcs.insert(init_sym);
            worklist.push_back(init_sym);
        }
        auto mod = LM::Frontend::ModuleManager::getInstance().get_module(pfx);
        if (mod) {
            for (const auto& pub_sym : mod->public_symbols) {
                std::string full_sym = pfx + "." + pub_sym;
                if (registry.getFunction(full_sym) && !reachable_funcs.count(full_sym)) {
                    reachable_funcs.insert(full_sym);
                    worklist.push_back(full_sym);
                }
            }
        } else {
            for (const auto& fname : registry.getFunctionNames()) {
                if (fname.rfind(pfx + ".", 0) == 0 && !reachable_funcs.count(fname)) {
                    reachable_funcs.insert(fname);
                    worklist.push_back(fname);
                }
            }
        }
    }

    // GPU stage functions are dispatch entry points, not call-graph callees:
    // gpu_dispatch references them by name string, so reachability must seed
    // them explicitly or they would be dropped from the module entirely.
    for (const auto& fname : registry.getFunctionNames()) {
        auto* gf = registry.getFunction(fname);
        if (gf && gf->gpu_stage != 0 && reachable_funcs.insert(fname).second)
            worklist.push_back(fname);
    }

    // Devirtualization support: a frame that is never constructed cannot be
    // a trait receiver, so structural/declared trait dispatch candidates are
    // restricted to frames whose NewFrame appears in reachable code. The set
    // grows as the worklist drains; trait sites are re-seeded each round
    // until the constructed set stops changing (fixpoint).
    std::unordered_set<std::string> constructed_frames;
    size_t constructed_version = 0;
    std::set<std::pair<std::string, std::string>> trait_sites;

    // method name -> candidate frame names, precomputed once so re-seeding
    // rounds do not rescan the whole registry per trait call site.
    std::unordered_map<std::string, std::vector<std::string>> trait_method_frames;
    {
        const auto& fmethods = LM::Frontend::ModuleManager::getInstance().frame_method_names();
        if (!fmethods.empty()) {
            for (const auto& fm : fmethods) {
                auto dot = fm.rfind('.');
                if (dot == std::string::npos || dot + 1 >= fm.size()) continue;
                trait_method_frames[fm.substr(dot + 1)].push_back(fm.substr(0, dot));
            }
        } else {
            // LIR-cache hit: no frame-method metadata; fall back to the
            // registry-wide suffix scan (unfiltered, as before).
            for (const auto& fname : registry.getFunctionNames()) {
                auto dot = fname.rfind('.');
                if (dot == std::string::npos || dot + 1 >= fname.size()) continue;
                trait_method_frames[fname.substr(dot + 1)].push_back(fname.substr(0, dot));
            }
        }
    }

    auto try_seed_trait_candidates = [&](const std::string& type_name, const std::string& method_name) {
        const auto& impls = LM::Frontend::ModuleManager::getInstance().trait_implementors();
        auto iit = impls.find(type_name);
        if (iit != impls.end()) {
            for (const auto& frame_name : iit->second) {
                // Only frames with a reachable constructor can be receivers.
                if (!constructed_frames.count(frame_name)) continue;
                std::string target = frame_name + "." + method_name;
                if (registry.getFunction(target) && reachable_funcs.insert(target).second)
                    worklist.push_back(target);
            }
            std::string def = type_name + "." + method_name;
            if (registry.getFunction(def) && reachable_funcs.insert(def).second)
                worklist.push_back(def);
            return;
        }
        auto mit = trait_method_frames.find(method_name);
        if (mit == trait_method_frames.end()) return;
        for (const auto& frame_name : mit->second) {
            if (!constructed_frames.count(frame_name)) continue;
            std::string target = frame_name + "." + method_name;
            if (registry.getFunction(target) && reachable_funcs.insert(target).second)
                worklist.push_back(target);
        }
    };

    // Module-init pruning: a pure __init__ (only data/global initialization,
    // no calls except other pure inits) is seeded only when its module
    // contributes reachable functions or referenced globals. Impure inits
    // always run so import side effects are preserved. Purity is transitive
    // over __init__ -> __init__ call edges.
    auto all_modules = LM::Frontend::ModuleManager::getInstance().get_all_modules();
    std::vector<std::string> module_paths;
    module_paths.reserve(all_modules.size());
    for (const auto& kv : all_modules) module_paths.push_back(kv.first);
    std::sort(module_paths.begin(), module_paths.end(),
              [](const std::string& a, const std::string& b) { return a.size() > b.size(); });
    auto module_of = [&](const std::string& name) -> std::string {
        for (const auto& m : module_paths) {
            if (name == m) return m;
            if (name.size() > m.size() && name.compare(0, m.size(), m) == 0 && name[m.size()] == '.')
                return m;
        }
        return "";
    };

    auto init_op_is_safe = [](LIR::LIR_Op op) -> bool {
        switch (op) {
            case LIR::LIR_Op::Mov: case LIR::LIR_Op::LoadConst:
            case LIR::LIR_Op::LoadGlobal: case LIR::LIR_Op::StoreGlobal:
            case LIR::LIR_Op::Add: case LIR::LIR_Op::Sub: case LIR::LIR_Op::Mul:
            case LIR::LIR_Op::Div: case LIR::LIR_Op::Mod: case LIR::LIR_Op::Neg:
            case LIR::LIR_Op::And: case LIR::LIR_Op::Or: case LIR::LIR_Op::Xor:
            case LIR::LIR_Op::Shl: case LIR::LIR_Op::Shr:
            case LIR::LIR_Op::CmpEQ: case LIR::LIR_Op::CmpNEQ:
            case LIR::LIR_Op::CmpLT: case LIR::LIR_Op::CmpLE:
            case LIR::LIR_Op::CmpGT: case LIR::LIR_Op::CmpGE:
            case LIR::LIR_Op::StringIndex:
            case LIR::LIR_Op::Jump: case LIR::LIR_Op::JumpIfFalse:
            case LIR::LIR_Op::JumpIf: case LIR::LIR_Op::Label:
            case LIR::LIR_Op::Nop: case LIR::LIR_Op::Load:
            case LIR::LIR_Op::Store: case LIR::LIR_Op::Cast:
            case LIR::LIR_Op::Copy: case LIR::LIR_Op::ToString:
            case LIR::LIR_Op::STR_CONCAT: case LIR::LIR_Op::STR_FORMAT:
            case LIR::LIR_Op::IAdd_Unchecked: case LIR::LIR_Op::IXor_Unchecked:
            case LIR::LIR_Op::IAnd_Unchecked: case LIR::LIR_Op::IOr_Unchecked:
            case LIR::LIR_Op::DecAdd: case LIR::LIR_Op::DecSub:
            case LIR::LIR_Op::DecMul: case LIR::LIR_Op::DecDiv:
            case LIR::LIR_Op::DecMod: case LIR::LIR_Op::DecNeg:
            case LIR::LIR_Op::DecRescale:
            case LIR::LIR_Op::ListCreate: case LIR::LIR_Op::ListAppend:
            case LIR::LIR_Op::ListIndex: case LIR::LIR_Op::ListSet:
            case LIR::LIR_Op::ListLen:
            case LIR::LIR_Op::DictCreate: case LIR::LIR_Op::DictSet:
            case LIR::LIR_Op::DictGet: case LIR::LIR_Op::DictHas:
            case LIR::LIR_Op::DictLen: case LIR::LIR_Op::DictItems:
            case LIR::LIR_Op::TupleCreate: case LIR::LIR_Op::TupleGet:
            case LIR::LIR_Op::TupleSet: case LIR::LIR_Op::TupleLen:
            case LIR::LIR_Op::MakeEnum: case LIR::LIR_Op::GetTag:
            case LIR::LIR_Op::GetPayload:
            case LIR::LIR_Op::ConstructError: case LIR::LIR_Op::ConstructOk:
            case LIR::LIR_Op::IsError: case LIR::LIR_Op::Unwrap:
            case LIR::LIR_Op::UnwrapOr:
            case LIR::LIR_Op::NewFrame:
            case LIR::LIR_Op::FrameGetField: case LIR::LIR_Op::FrameSetField:
            case LIR::LIR_Op::FrameGetFieldAtomic:
            case LIR::LIR_Op::FrameSetFieldAtomic:
            case LIR::LIR_Op::FrameFieldAtomicAdd:
            case LIR::LIR_Op::FrameFieldAtomicSub:
            case LIR::LIR_Op::Return: case LIR::LIR_Op::Ret:
            case LIR::LIR_Op::AtomicLoad: case LIR::LIR_Op::AtomicStore:
            case LIR::LIR_Op::AtomicFetchAdd:
            case LIR::LIR_Op::VaStart: case LIR::LIR_Op::VaArg:
            case LIR::LIR_Op::VaEnd:
            // Region/ownership/ref plumbing: memory-model bookkeeping with
            // no observable side effects beyond the init's own stores.
            case LIR::LIR_Op::RegionEnter: case LIR::LIR_Op::RegionExit:
            case LIR::LIR_Op::RegionMove:
            case LIR::LIR_Op::RefCreate: case LIR::LIR_Op::RefResolve:
            case LIR::LIR_Op::RefRelease: case LIR::LIR_Op::RefMove:
            case LIR::LIR_Op::OwnershipConsume:
                return true;
            default:
                return false;
        }
    };
    auto is_init_name = [](const std::string& n) -> bool {
        return n.size() > 9 && n.compare(n.size() - 9, 9, ".__init__") == 0;
    };

    // Pure-data builtins: collection/string/math services with no
    // observable side effects. Anything else (print, input, assert, sleep,
    // file_*, FFI, ...) keeps the init impure.
    auto builtin_is_pure = [](const std::string& n) -> bool {
        static const std::unordered_set<std::string> pure_exact = {
            "len", "length", "_builtin_length", "typeof",
            "abs", "sqrt", "sin", "cos", "tan", "asin", "acos", "atan",
            "log", "log10", "exp", "ceil", "floor", "round",
            "lm_to_string", "lm_error_new", "lm_key_eq"
        };
        if (pure_exact.count(n)) return true;
        static const char* pure_prefixes[] = {
            "lm_list_", "lm_dict_", "lm_tuple_", "lm_str_",
            "lm_box_", "jit_dict_", "_builtin_"
        };
        for (const char* pfx : pure_prefixes)
            if (n.rfind(pfx, 0) == 0) return true;
        return false;
    };
    // Runtime memory/region plumbing — no observable side effects beyond
    // the init's own stores. Excludes ffi/io/concurrency/OS services.
    auto runtime_call_is_pure = [](const std::string& n) -> bool {
        if (n.rfind("lymar_aot_", 0) != 0) return false;
        static const char* bad[] = {
            "ffi", "io_", "file", "print", "input", "sleep", "time",
            "random", "channel", "task", "sched", "worker", "parallel",
            "callback", "resource", "window", "event", "gpu", "native",
            "d3d", "vulkan", "sokol", "console", "process", "thread",
            "mutex", "lock", "socket", "http", "net", "env", "exit",
            "signal", "pipe", "dir", "watch"
        };
        for (const char* b : bad)
            if (n.find(b) != std::string::npos) return false;
        return true;
    };

    // Calls to other __init__ functions are neutral: they only express
    // import ordering, which the topological init sequence already
    // guarantees, and each dep init is seeded/skipped on its own merits.
    std::unordered_map<std::string, bool> init_pure;
    for (const auto& fname : registry.getFunctionNames()) {
        if (!is_init_name(fname)) continue;
        auto* f = registry.getFunction(fname);
        if (!f) continue;
        bool pure = true;
        for (const auto& inst : f->instructions) {
            if (inst.op == LIR::LIR_Op::Call || inst.op == LIR::LIR_Op::CallVoid) {
                if (is_init_name(inst.func_name) || runtime_call_is_pure(inst.func_name)) continue;
                if (std::getenv("LYMAR_DEBUG_INIT"))
                    std::cerr << "IMPURE " << fname << ": call " << inst.func_name << std::endl;
                pure = false;
                break;
            }
            if (inst.op == LIR::LIR_Op::CallBuiltin) {
                if (builtin_is_pure(inst.func_name)) continue;
                if (std::getenv("LYMAR_DEBUG_INIT"))
                    std::cerr << "IMPURE " << fname << ": CallBuiltin " << inst.func_name << std::endl;
                pure = false;
                break;
            }
            if ((inst.op == LIR::LIR_Op::LoadGlobal || inst.op == LIR::LIR_Op::StoreGlobal) &&
                !inst.func_name.empty()) {
                // Cross-module global access can mutate shared state in
                // place (append/set on a loaded collection) without any
                // call — treat as impure so the init always runs.
                std::string own_mod = fname.substr(0, fname.size() - 9);
                std::string gmod = module_of(inst.func_name);
                if (!gmod.empty() && gmod != own_mod) {
                    if (std::getenv("LYMAR_DEBUG_INIT"))
                        std::cerr << "IMPURE " << fname << ": xglobal " << inst.func_name << std::endl;
                    pure = false;
                    break;
                }
            }
            if (!init_op_is_safe(inst.op)) {
                if (std::getenv("LYMAR_DEBUG_INIT"))
                    std::cerr << "IMPURE " << fname << ": op " << (int)inst.op << " fn=" << inst.func_name << std::endl;
                pure = false;
                break;
            }
        }
        init_pure[fname] = pure;
    }

    std::set<std::string> pending_pure_inits;
    std::set<std::string> referenced_globals;

    auto inspect_instructions = [&](const LIR::LIR_Function& f) {
        // ffi.create_callback resolves its target by name string at runtime,
        // so the callee is invisible to the call graph — same problem gpu
        // stage entries solve by explicit seeding. Track string literals per
        // register and seed any literal passed as the callback name.
        std::unordered_map<uint32_t, std::string> literal_regs;
        auto literal_of = [](const LIR::LIR_Inst& inst) -> std::string {
            if (!inst.const_val || !IS_PTR(inst.const_val)) return "";
            ObjHeader* h = (ObjHeader*)UNBOX_PTR(inst.const_val);
            if (h->type_id == TYPE_STRING) return ((LmStringHeader*)h)->data;
            if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING)
                return static_cast<const char*>(((LmBox*)h)->value.as_ptr);
            return "";
        };
        for (const auto& inst : f.instructions) {
            if (inst.op == LIR::LIR_Op::LoadConst) {
                auto lit = literal_of(inst);
                if (!lit.empty()) literal_regs[inst.dst] = lit;
            } else if (inst.op == LIR::LIR_Op::Mov && literal_regs.count(inst.a)) {
                literal_regs[inst.dst] = literal_regs[inst.a];
            }
            if ((inst.op == LIR::LIR_Op::Call || inst.op == LIR::LIR_Op::CallVoid) &&
                (inst.func_name == "std.ffi.create_callback" || inst.func_name == "ffi.create_callback") &&
                !inst.call_args.empty() && literal_regs.count(inst.call_args[0])) {
                const std::string& target = literal_regs[inst.call_args[0]];
                if (registry.getFunction(target) && reachable_funcs.insert(target).second)
                    worklist.push_back(target);
            }
        }
        for (const auto& inst : f.instructions) {
            if ((inst.op == LIR::LIR_Op::LoadGlobal || inst.op == LIR::LIR_Op::StoreGlobal) &&
                !inst.func_name.empty())
                referenced_globals.insert(inst.func_name);
            if (inst.op == LIR::LIR_Op::NewFrame) {
                auto name = !inst.type_name.empty() ? inst.type_name : inst.func_name;
                if (!name.empty() && constructed_frames.insert(name).second) constructed_version++;
                auto finalizer = name + ".deinit";
                if (registry.getFunction(finalizer) && reachable_funcs.insert(finalizer).second)
                    worklist.push_back(finalizer);
            }
            std::string callee = inst.func_name;
            if (callee.empty() && inst.const_val && IS_PTR(inst.const_val)) {
                ObjHeader* h = (ObjHeader*)UNBOX_PTR(inst.const_val);
                if (h->type_id == TYPE_STRING) callee = ((LmStringHeader*)h)->data;
                else if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING)
                    callee = static_cast<const char*>(((LmBox*)h)->value.as_ptr);
            }
            if (inst.op == LIR::LIR_Op::TraitCallMethod && !inst.func_name.empty()) {
                // Record the site; candidates are (re)seeded by
                // try_seed_trait_candidates, restricted to frames with a
                // reachable NewFrame. Re-seeding happens each fixpoint round
                // because later-discovered constructions unlock more frames.
                trait_sites.insert({inst.type_name, inst.func_name});
                try_seed_trait_candidates(inst.type_name, inst.func_name);
            }
            // ForeignCallDirect call-site lowering carries the c-import
            // registry key in type_name; keep the generated wrapper reachable
            // so struct signatures the native ABI packing cannot express can
            // still fall back to it.
            if (inst.op == LIR::LIR_Op::ForeignCallDirect && !inst.type_name.empty() &&
                registry.getFunction(inst.type_name) && reachable_funcs.insert(inst.type_name).second)
                worklist.push_back(inst.type_name);
            if (!callee.empty() && registry.getFunction(callee)) {
                if (is_init_name(callee)) {
                    auto pit = init_pure.find(callee);
                    if (std::getenv("LYMAR_DEBUG_INIT") && callee.find("calendar") != std::string::npos)
                        std::cerr << "INIT-SEED " << callee << " pure=" << (pit != init_pure.end() ? (pit->second ? 1 : 0) : -1) << std::endl;
                    if (pit != init_pure.end() && pit->second) {
                        // Pure init: defer until we know its module is needed.
                        pending_pure_inits.insert(callee);
                    } else if (reachable_funcs.insert(callee).second) {
                        // Impure/unknown init: side effects must run.
                        worklist.push_back(callee);
                    }
                } else if (reachable_funcs.find(callee) == reachable_funcs.end()) {
                    reachable_funcs.insert(callee);
                    worklist.push_back(callee);
                }
            }
            if (inst.op == LIR::LIR_Op::LoadConst && LIR::BuiltinUtils::isBuiltinFunction(callee))
                for (const auto& candidate : registry.getFunctionNames())
                    if (LIR::builtin_callable_target(candidate) == callee && reachable_funcs.insert(candidate).second)
                        worklist.push_back(candidate);
        }
    };

    size_t work_idx = 0;
    size_t seeded_constructed_version = 0;
    while (true) {
        while (work_idx < worklist.size()) {
            std::string fname = worklist[work_idx++];
            if (fname == lir_func.name) {
                inspect_instructions(lir_func);
            } else {
                auto* f = registry.getFunction(fname);
                if (f) inspect_instructions(*f);
            }
        }
        size_t reachable_before = reachable_funcs.size();
        // Fixpoint: newly discovered constructions can unlock trait
        // candidates skipped in earlier rounds; re-seed every recorded
        // site and drain again until the constructed set stops growing.
        if (constructed_version != seeded_constructed_version) {
            seeded_constructed_version = constructed_version;
            for (const auto& site : trait_sites) {
                try_seed_trait_candidates(site.first, site.second);
            }
        }
        // Module-init pruning: seed a deferred pure __init__ only when its
        // module contributes a reachable function or a referenced global.
        // Newly reached init bodies can reference more globals, so this
        // recomputes each round until no new function becomes reachable.
        std::unordered_set<std::string> needed_modules;
        for (const auto& fn : reachable_funcs) {
            auto m = module_of(fn);
            if (!m.empty()) needed_modules.insert(m);
        }
        for (const auto& g : referenced_globals) {
            auto m = module_of(g);
            if (!m.empty()) needed_modules.insert(m);
        }
        for (const auto& init : pending_pure_inits) {
            if (reachable_funcs.count(init)) continue;
            std::string mod = init.substr(0, init.size() - 9);
            if (needed_modules.count(mod)) {
                if (std::getenv("LYMAR_DEBUG_INIT") && mod.find("calendar") != std::string::npos) {
                    for (const auto& fn : reachable_funcs)
                        if (fn.rfind(mod + ".", 0) == 0 || fn == mod)
                            std::cerr << "NEEDED-FN " << fn << std::endl;
                    for (const auto& g : referenced_globals)
                        if (g.rfind(mod + ".", 0) == 0 || g == mod)
                            std::cerr << "NEEDED-GLOBAL " << g << std::endl;
                }
                reachable_funcs.insert(init);
                worklist.push_back(init);
            }
        }
        if (reachable_funcs.size() == reachable_before) break;
    }
    if (std::getenv("LYMAR_DEBUG_INIT")) {
        std::cerr << "REACHABLE=" << reachable_funcs.size()
                  << " cal_init=" << reachable_funcs.count("std.ui.widgets.calendar.__init__")
                  << " pending=" << pending_pure_inits.size()
                  << " pure_map=" << init_pure.size() << std::endl;
        auto pit = init_pure.find("std.ui.widgets.calendar.__init__");
        std::cerr << "cal_pure=" << (pit == init_pure.end() ? -1 : (pit->second ? 1 : 0)) << std::endl;
    }
    constructed_frames_ = constructed_frames;
    reachable_funcs_ = reachable_funcs;
    direct_sigs_.clear();
    direct_contexts_.clear();

    // Collect every string literal in reachable code. Indirect-call callee
    // names (fn values, closures, task/callback targets) always originate as
    // LoadConst string literals, so this set bounds the names the shared
    // dispatch helpers could ever match.
    indirect_literals_.clear();
    auto collect_literals = [&](const LIR::LIR_Function& f) {
        for (const auto& inst : f.instructions) {
            if (inst.op != LIR::LIR_Op::LoadConst || !inst.const_val || !IS_PTR(inst.const_val)) continue;
            ObjHeader* h = (ObjHeader*)UNBOX_PTR(inst.const_val);
            if (h->type_id == TYPE_STRING) {
                indirect_literals_.insert(((LmStringHeader*)h)->data);
            } else if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                indirect_literals_.insert(static_cast<const char*>(((LmBox*)h)->value.as_ptr));
            }
        }
    };
    collect_literals(lir_func);
    for (const auto& func_name : registry.getFunctionNames()) {
        if (func_name == lir_func.name || reachable_funcs.find(func_name) == reachable_funcs.end()) continue;
        if (auto* f = registry.getFunction(func_name)) collect_literals(*f);
    }

    auto is_func_ret_float = [](const LIR::LIR_Function* f) -> bool {
        if (!f) return false;
        for (const auto& inst : f->instructions) {
            if (inst.op == LIR::LIR_Op::Return || inst.op == LIR::LIR_Op::Ret) {
                if (inst.a != UINT32_MAX) {
                    if (inst.type_a == LIR::Type::F64 || inst.type_a == LIR::Type::F32) return true;
                    if (f->register_types.count(inst.a) && (f->register_types.at(inst.a) == LIR::Type::F64 || f->register_types.at(inst.a) == LIR::Type::F32)) return true;
                    if (f->register_language_types.count(inst.a)) {
                        auto lt = f->register_language_types.at(inst.a);
                        if (lt && (lt->tag == ::TypeTag::Float64 || lt->tag == ::TypeTag::Float32)) return true;
                    }
                }
            }
        }
        return false;
    };

    std::string main_name = lir_func.name;
    if (main_name == "__top_level_wrapper__") main_name = "main";
    std::vector<ir::Type*> main_param_types;
    for (size_t i = 0; i < lir_func.param_count; ++i) {
        ir::Type* pty = context_->getIntegerType(64);
        auto it = lir_func.register_language_types.find(i);
        if (it != lir_func.register_language_types.end() && it->second) {
            if (it->second->tag == ::TypeTag::Float64 || it->second->tag == ::TypeTag::Float32) pty = context_->getDoubleType();
        }
        {
            auto it2 = lir_func.register_types.find(i);
            if (it2 != lir_func.register_types.end() && (it2->second == LIR::Type::F64 || it2->second == LIR::Type::F32)) {
                pty = context_->getDoubleType();
            }
        }
        main_param_types.push_back(pty);
    }
    ir::Type* main_ret_type = context_->getIntegerType(64);
    if (is_func_ret_float(&lir_func)) {
        main_ret_type = context_->getDoubleType();
    }
    ir::Function* main_fn = builder_->createFunction(main_name, main_ret_type, main_param_types);

    // 1. Declare only reachable registered functions
    for (const auto& func_name : registry.getFunctionNames()) {
        if (func_name == lir_func.name) continue;
        if (LIR::BuiltinUtils::isBuiltinFunction(func_name)) continue;
        if (reachable_funcs.find(func_name) == reachable_funcs.end()) continue;
        auto* f = registry.getFunction(func_name);
        if (!f) continue;

        std::string ir_name = func_name;
        if (func_name == "main" && lir_func.name == "__top_level_wrapper__") {
            ir_name = "__user_main";
        }

        std::vector<ir::Type*> param_types;
        for (size_t i = 0; i < f->param_count; ++i) {
            ir::Type* pty = context_->getIntegerType(64);
            auto it = f->register_language_types.find(i);
            if (it != f->register_language_types.end() && it->second) {
                if (it->second->tag == ::TypeTag::Float64 || it->second->tag == ::TypeTag::Float32) pty = context_->getDoubleType();
            }
            {
                auto it2 = f->register_types.find(i);
                if (it2 != f->register_types.end() && (it2->second == LIR::Type::F64 || it2->second == LIR::Type::F32)) {
                    pty = context_->getDoubleType();
                }
            }
            param_types.push_back(pty);
        }

        ir::Type* ret_type = context_->getIntegerType(64);
        if (is_func_ret_float(f)) {
            ret_type = context_->getDoubleType();
        }
        builder_->createFunction(ir_name, ret_type, param_types);

        // `.direct` flattened-ABI variant: tuple params become per-element
        // scalar parameters and tuple returns take a hidden sret buffer, so
        // eligible cross-module calls skip the tagged heap-tuple ABI.
        const DirectFnSig* dsig = direct_sig_for(func_name);
        if (dsig->eligible) {
            DirectFnCtx dctx;
            dctx.sret_return = dsig->ret_sret;
            dctx.ret_frame = dsig->ret_frame;
            dctx.ret_domains = dsig->ret_domains;
            std::vector<ir::Type*> dpts;
            for (size_t pi = 0; pi < f->param_count; ++pi) {
                const auto& doms = dsig->param_elem_domains[pi];
                const bool inout = pi < dsig->param_inout.size() && dsig->param_inout[pi] == 2;
                if (doms.empty()) {
                    ir::Type* pty = context_->getIntegerType(64);
                    auto lt = f->register_language_types.find(pi);
                    if (lt != f->register_language_types.end() && lt->second &&
                        (lt->second->tag == ::TypeTag::Float64 || lt->second->tag == ::TypeTag::Float32))
                        pty = context_->getDoubleType();
                    {
                        auto rt = f->register_types.find(pi);
                        if (rt != f->register_types.end() && (rt->second == LIR::Type::F64 || rt->second == LIR::Type::F32))
                            pty = context_->getDoubleType();
                    }
                    dpts.push_back(pty);
                    dctx.params.push_back({static_cast<uint32_t>(pi), -1, VDOM_INT});
                } else if (inout) {
                    // Record param passed as a pointer to a caller-owned field
                    // buffer; the callee's virtual record reads/writes it in
                    // place so mutations propagate back after the call.
                    dpts.push_back(context_->getIntegerType(64));
                    dctx.params.push_back({static_cast<uint32_t>(pi), -2, VDOM_PTR});
                    dctx.inout_domains[static_cast<uint32_t>(pi)] = doms;
                } else {
                    for (size_t ei = 0; ei < doms.size(); ++ei) {
                        dpts.push_back(doms[ei] == VDOM_FLOAT
                            ? static_cast<ir::Type*>(context_->getDoubleType())
                            : static_cast<ir::Type*>(context_->getIntegerType(64)));
                        dctx.params.push_back({static_cast<uint32_t>(pi), static_cast<int32_t>(ei), doms[ei]});
                    }
                }
            }
            if (dsig->ret_sret) dpts.push_back(context_->getIntegerType(64));
            ir::Type* dret = context_->getIntegerType(64);
            if (!dsig->ret_sret && dsig->ret_float) dret = context_->getDoubleType();
            builder_->createFunction(func_name + ".direct", dret, dpts);
            direct_contexts_[func_name] = dctx;
        }
    }

    auto is_instruction_float = [](const LIR::LIR_Function* f_func, uint32_t reg) -> bool {
        if (!f_func) return false;
        if (f_func->register_types.count(reg)) {
            LIR::Type t = f_func->register_types.at(reg);
            if (t == LIR::Type::F64 || t == LIR::Type::F32) return true;
        }
        if (f_func->register_language_types.count(reg)) {
            auto lt = f_func->register_language_types.at(reg);
            if (lt && (lt->tag == ::TypeTag::Float64 || lt->tag == ::TypeTag::Float32)) return true;
        }
        for (const auto& in : f_func->instructions) {
            if (in.dst == reg) {
                if (in.result_type == LIR::Type::F64 || in.result_type == LIR::Type::F32) return true;
                if (in.type_name == "float" || in.type_name == "f64" || in.type_name == "f32") return true;
                if (in.op == LIR::LIR_Op::LoadConst && is_float(in.const_val)) return true;
            }
        }
        return false;
    };

    // 1b. Pre-scan global variable types across reachable functions
    for (const auto& func_name : registry.getFunctionNames()) {
        if (reachable_funcs.find(func_name) == reachable_funcs.end()) continue;
        auto* f = registry.getFunction(func_name);
        if (!f) continue;
        for (const auto& inst : f->instructions) {
            if (inst.op == LIR::LIR_Op::StoreGlobal) {
                std::string gname = inst.func_name.empty() ? ("global_" + std::to_string(inst.dst)) : inst.func_name;
                gname = global_symbol(gname);
                if (inst.type_a == LIR::Type::F64 || inst.type_a == LIR::Type::F32 || is_instruction_float(f, inst.a)) {
                    global_types_[gname] = LIR::Type::F64;
                }
            }
        }
    }

    // 2. Build the bodies of reachable registered functions
    for (const auto& func_name : registry.getFunctionNames()) {
        if (func_name == lir_func.name) continue;
        if (LIR::BuiltinUtils::isBuiltinFunction(func_name)) continue;
        if (reachable_funcs.find(func_name) == reachable_funcs.end()) continue;
        auto* f = registry.getFunction(func_name);
        if (!f) continue;

        std::string ir_name = func_name;
        if (func_name == "main" && lir_func.name == "__top_level_wrapper__") {
            ir_name = "__user_main";
        }

        ir::Function* fn = current_module_->getFunction(ir_name);
        if (fn) {
            build_function_body(fn, *f);
        }
    }

    // 2b. Bodies of `.direct` flattened-ABI variants.
    for (const auto& [dname, dctx] : direct_contexts_) {
        auto* f = registry.getFunction(dname);
        if (!f) continue;
        auto* fn = current_module_->getFunction(dname + ".direct");
        if (fn) build_function_body(fn, *f, &dctx);
    }

    // 3. Build the top-level main function body
    build_function_body(main_fn, lir_func);

    // GPU stage manifest: ir::Function carries no attribute/metadata channel,
    // so stage kind, workgroup size, and mesh limits are encoded here for the
    // vendor/fyra lowering to recover. One line per gpu function:
    //   "<function name>|<task|vertex|pixel|mesh>|<tx>,<ty>,<tz>|<max_vertices>,<max_primitives>"
    {
        std::string gpu_table;
        for (const auto& fname : registry.getFunctionNames()) {
            auto* gf = registry.getFunction(fname);
            if (!gf || gf->gpu_stage == 0) continue;
            if (reachable_funcs.find(fname) == reachable_funcs.end()) continue;
            const char* stage = gf->gpu_stage == 1 ? "task" :
                                gf->gpu_stage == 2 ? "vertex" :
                                gf->gpu_stage == 3 ? "pixel" : "mesh";
            gpu_table += fname + "|" + stage + "|" +
                std::to_string(gf->gpu_threads[0]) + "," +
                std::to_string(gf->gpu_threads[1]) + "," +
                std::to_string(gf->gpu_threads[2]) + "|" +
                std::to_string(gf->gpu_max_vertices) + "," +
                std::to_string(gf->gpu_max_primitives) + "\n";
        }
        if (!gpu_table.empty()) {
            FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(),
                "__lymar_gpu_stages", gpu_table);
        }
    }

    bool callbacks_needed=false;
    bool gpu_tasks_needed=false;
    for(const auto& name:reachable_funcs) {
        auto* function=registry.getFunction(name);
        if(function && function->gpu_stage!=0) gpu_tasks_needed=true;
        if(function) for(const auto& instruction:function->instructions)
            if(instruction.op==LIR::LIR_Op::CallbackCreate && instruction.imm!=1) callbacks_needed=true;
    }
    for(const auto& instruction:lir_func.instructions)
        if(instruction.op==LIR::LIR_Op::CallbackCreate && instruction.imm!=1) callbacks_needed=true;
    if(callbacks_needed || gpu_tasks_needed) {
        auto* entry=main_fn->getBasicBlocks().front().get();
        auto first_new=entry->getInstructions().size();
        builder_->setInsertPoint(entry);
        for(const auto& name:reachable_funcs) {
            auto* target=current_module_->getFunction(name=="main" && lir_func.name=="__top_level_wrapper__"?"__user_main":name);
            if(!target || target==main_fn || target->getBasicBlocks().empty() || target->getParameters().size()>64) continue;
            auto* gf=registry.getFunction(name);
            // Float-ness comes from the LIR register types: every Fyra
            // parameter is an i64 word, so the IR type cannot distinguish
            // float params. LIR params occupy registers 0..param_count-1.
            uint64_t floating=0;size_t index=0;
            for(const auto& parameter:target->getParameters()) {
                if(gf && index<gf->param_count) {
                    auto rt=gf->register_types.find(index);
                    if(rt!=gf->register_types.end() &&
                       (rt->second==LIR::Type::F64 || rt->second==LIR::Type::F32))
                        floating|=uint64_t(1)<<index;
                }
                ++index;
            }
            // Machine-level truth: an IR double return arrives in xmm0, so
            // FFI callers must read F64; integer returns are tagged i64 words.
            const bool float_return=target->getReturnType() && target->getReturnType()->isFloatingPoint();
            auto* text=FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(),builder_.get(),"ffi_name_"+std::to_string(label_counter_++),name);
            auto* copy=builder_->createExternCall("lymar_aot_copy_constant",{text,context_->getConstantInt(context_->getIntegerType(64),25+name.size())},context_->getIntegerType(64));
            if(callbacks_needed)
                builder_->createExternCall("lymar_aot_ffi_register",{copy,target,context_->getConstantInt(context_->getIntegerType(64),index),context_->getConstantInt(context_->getIntegerType(64),floating),context_->getConstantInt(context_->getIntegerType(64),float_return)},context_->getVoidType());
            if(gf && gf->gpu_stage!=0) {
                builder_->createExternCall("lymar_aot_gpu_register",{copy,target,
                    context_->getConstantInt(context_->getIntegerType(64),index),
                    context_->getConstantInt(context_->getIntegerType(64),floating),
                    context_->getConstantInt(context_->getIntegerType(64),float_return),
                    context_->getConstantInt(context_->getIntegerType(64),gf->gpu_stage),
                    context_->getConstantInt(context_->getIntegerType(64),gf->gpu_threads[0]),
                    context_->getConstantInt(context_->getIntegerType(64),gf->gpu_threads[1]),
                    context_->getConstantInt(context_->getIntegerType(64),gf->gpu_threads[2]),
                    context_->getConstantInt(context_->getIntegerType(64),gf->gpu_max_vertices),
                    context_->getConstantInt(context_->getIntegerType(64),gf->gpu_max_primitives)},
                    context_->getVoidType());
            }
        }
        auto begin=entry->getInstructions().begin();std::advance(begin,first_new);
        entry->getInstructions().splice(entry->getInstructions().begin(),entry->getInstructions(),begin,entry->getInstructions().end());
    }
    FyraBuiltinFunctions::emit_used_builtins(current_module_.get(), builder_.get(), used_builtins_);
    // fyrA_fs_dispatch(handle, op, count, args): runtime op dispatch for
    // resource calls on capability-enabled targets. Filesystem ops
    // (OP_MKDIR=30, OP_RENAME=32, OP_EXISTS=33, OP_DELETE=34 — see
    // std/internal/runtime.lm) lower to native capability compositions;
    // every other op forwards to lymar_aot_resource_call unchanged. The op
    // arrives as a runtime value through res._call/call, so dispatch is a
    // compare chain, not a compile-time decision. Result words match the
    // runtime contract: capability arms produce 0/1, the fallback returns
    // whatever lymar_aot_resource_call produces.
    if (needs_service_dispatch_ || needs_fs_dispatch_) {
        auto* dfn = current_module_->getFunction("fyrA_service_dispatch");
        if (!dfn) dfn = current_module_->getFunction("fyrA_fs_dispatch");
        if (dfn && dfn->getBasicBlocks().empty()) {
            auto* i64ty = context_->getIntegerType(64);
            auto* fn = dfn;
            auto pit = fn->getParameters().begin();
            ir::Value* handle = pit->get(); ++pit;
            ir::Value* op = pit->get(); ++pit;
            ir::Value* count = pit->get(); ++pit;
            ir::Value* args = pit->get();
            auto c64 = [&](uint64_t v) { return context_->getConstantInt(i64ty, v); };
            auto blk = [&](const char* n) { return builder_->createBasicBlock(n, fn); };
            auto* b_entry = blk("sd_entry");
            auto* b_c32 = blk("sd_c32");
            auto* b_c34 = blk("sd_c34");
            auto* b_c30 = blk("sd_c30");
            auto* b_c49 = blk("sd_c49");
            auto* b_c50 = blk("sd_c50");
            auto* b_c51 = blk("sd_c51");
            auto* b_c52 = blk("sd_c52");
            auto* b_c71 = blk("sd_c71");
            auto* b_c72 = blk("sd_c72");
            auto* b_c73 = blk("sd_c73");
            auto* b_exists = blk("sd_exists");
            auto* b_rename = blk("sd_rename");
            auto* b_delete = blk("sd_delete");
            auto* b_mkdir = blk("sd_mkdir");
            auto* b_env_get = blk("sd_env_get");
            auto* b_env_set = blk("sd_env_set");
            auto* b_env_unset = blk("sd_env_unset");
            auto* b_env_list = blk("sd_env_list");
            auto* b_time_now = blk("sd_time_now");
            auto* b_time_mono = blk("sd_time_mono");
            auto* b_time_sleep = blk("sd_time_sleep");
            auto* b_fallback = blk("sd_fallback");

            auto saved_ip = builder_->getInsertPoint();
            auto u32 = [&](ir::Value* v) { return builder_->createAnd(v, c64(0xFFFFFFFFULL)); };
            auto is1 = [&](ir::Value* v) { return builder_->createCast(builder_->createCeq(u32(v), c64(1)), i64ty); };
            auto is_nonzero = [&](ir::Value* v) { return builder_->createCast(builder_->createCne(u32(v), c64(0)), i64ty); };
            auto str_arg = [&](uint64_t n) {
                return builder_->createExternCall("lymar_aot_resource_str_arg",
                    {args, count, c64(n)}, i64ty);
            };
            auto booleanize = [&](ir::Value* v) {
                return builder_->createExternCall("lymar_aot_tag_bool", {v}, i64ty);
            };

            builder_->setInsertPoint(b_entry);
            builder_->createBr(builder_->createCeq(op, c64(33)), b_exists, b_c32);

            builder_->setInsertPoint(b_c32);
            builder_->createBr(builder_->createCeq(op, c64(32)), b_rename, b_c34);
            builder_->setInsertPoint(b_c34);
            builder_->createBr(builder_->createCeq(op, c64(34)), b_delete, b_c30);
            builder_->setInsertPoint(b_c30);
            builder_->createBr(builder_->createCeq(op, c64(30)), b_mkdir, b_c49);

            builder_->setInsertPoint(b_c49);
            builder_->createBr(builder_->createCeq(op, c64(49)), b_env_get, b_c50);
            builder_->setInsertPoint(b_c50);
            builder_->createBr(builder_->createCeq(op, c64(50)), b_env_set, b_c51);
            builder_->setInsertPoint(b_c51);
            builder_->createBr(builder_->createCeq(op, c64(51)), b_env_unset, b_c52);
            builder_->setInsertPoint(b_c52);
            builder_->createBr(builder_->createCeq(op, c64(52)), b_env_list, b_c71);

            builder_->setInsertPoint(b_c71);
            builder_->createBr(builder_->createCeq(op, c64(71)), b_time_now, b_c72);
            builder_->setInsertPoint(b_c72);
            builder_->createBr(builder_->createCeq(op, c64(72)), b_time_mono, b_c73);
            builder_->setInsertPoint(b_c73);
            builder_->createBr(builder_->createCeq(op, c64(73)), b_time_sleep, b_fallback);

            // OP_EXISTS: attributes != INVALID sentinel.
            builder_->setInsertPoint(b_exists);
            {
                auto* attrs = builder_->createExternCall("fs.getattrs", {str_arg(0)}, i64ty);
                auto* word = builder_->createCast(builder_->createCne(u32(attrs), c64(0xFFFFFFFFULL)), i64ty);
                builder_->createRet(booleanize(word));
            }

            // OP_RENAME: capability returns exactly 1 on success.
            builder_->setInsertPoint(b_rename);
            {
                auto* ret = builder_->createExternCall("fs.rename", {str_arg(0), str_arg(1)}, i64ty);
                builder_->createRet(booleanize(is1(ret)));
            }

            // OP_DELETE: file or empty directory — either primitive succeeding
            // counts as success.
            builder_->setInsertPoint(b_delete);
            {
                auto* a0 = str_arg(0);
                auto* del = builder_->createExternCall("fs.remove", {a0}, i64ty);
                auto* rmdir = builder_->createExternCall("fs.rmdir", {a0}, i64ty);
                builder_->createRet(booleanize(builder_->createOr(is1(del), is1(rmdir))));
            }

            // OP_MKDIR: mkdir -p; the directory must be missing beforehand and
            // fs.mkdirp must report success (0).
            builder_->setInsertPoint(b_mkdir);
            {
                auto* a0 = str_arg(0);
                auto* attrs = builder_->createExternCall("fs.getattrs", {a0}, i64ty);
                auto* missing = builder_->createCast(builder_->createCeq(u32(attrs), c64(0xFFFFFFFFULL)), i64ty);
                auto* hr = builder_->createExternCall("fs.mkdirp", {a0, c64(0)}, i64ty);
                auto* ok = builder_->createCast(builder_->createCeq(u32(hr), c64(0)), i64ty);
                builder_->createRet(booleanize(builder_->createAnd(missing, ok)));
            }

            // OP_ENV_GET (49): get environment variable.
            builder_->setInsertPoint(b_env_get);
            {
                auto* buf = builder_->createAlloc(c64(32768), context_->getIntegerType(8));
                auto* k = str_arg(0);
                std::vector<ir::Value*> env_args{k, buf, c64(32768)};
                auto* len = builder_->createExternCall("env.get", env_args, i64ty);
                std::vector<ir::Value*> res_args{buf, len};
                auto* ret = builder_->createExternCall("lymar_aot_env_get_result", res_args, i64ty);
                builder_->createRet(ret);
            }

            // OP_ENV_SET (50): set environment variable.
            builder_->setInsertPoint(b_env_set);
            {
                auto* k = str_arg(0);
                auto* v = str_arg(1);
                std::vector<ir::Value*> env_args{k, v};
                auto* ret = builder_->createExternCall("env.set", env_args, i64ty);
                builder_->createRet(booleanize(is_nonzero(ret)));
            }

            // OP_ENV_UNSET (51): unset environment variable.
            builder_->setInsertPoint(b_env_unset);
            {
                auto* k = str_arg(0);
                std::vector<ir::Value*> env_args{k, c64(0)};
                auto* ret = builder_->createExternCall("env.set", env_args, i64ty);
                builder_->createRet(booleanize(is_nonzero(ret)));
            }

            // OP_ENV_LIST (52): list environment variables.
            builder_->setInsertPoint(b_env_list);
            {
                auto* block = builder_->createExternCall("env.list", {}, i64ty);
                std::vector<ir::Value*> list_args{block};
                auto* list = builder_->createExternCall("lymar_aot_make_env_list", list_args, i64ty);
                builder_->createRet(list);
            }

            // OP_TIME_NOW (71): current time.
            builder_->setInsertPoint(b_time_now);
            {
                auto* now = builder_->createExternCall("time.now", {}, i64ty);
                builder_->createRet(now);
            }

            // OP_TIME_MONOTONIC (72): monotonic time.
            builder_->setInsertPoint(b_time_mono);
            {
                auto* mono = builder_->createExternCall("time.monotonic", {}, i64ty);
                builder_->createRet(mono);
            }

            // OP_TIME_SLEEP (73): sleep.
            builder_->setInsertPoint(b_time_sleep);
            {
                auto* ms_val = builder_->createLoad(args);
                std::vector<ir::Value*> sleep_args{ms_val};
                builder_->createExternCall("time.sleep", sleep_args, context_->getVoidType());
                builder_->createRet(c64(0));
            }

            builder_->setInsertPoint(b_fallback);
            builder_->createRet(builder_->createExternCall("lymar_aot_resource_call",
                {handle, op, count, args}, i64ty));
            if (saved_ip) builder_->setInsertPoint(saved_ip);
        }
    }
    // fs.mkdirp on syscall targets lowers to a call to this helper: recursive
    // directory creation needs a loop, which inline capability emission cannot
    // express in binary mode. The body composes the fs.mkdir/fs.getattrs
    // capabilities, so every syscall still stays inside the OS capability
    // layer. Contract: returns 0 on success, nonzero on failure (matching the
    // Windows SHCreateDirectoryExA S_OK convention the builder compares).
    if (fs_capabilities_ && fs_mkdirp_helper_ && needs_mkdirp_helper_ &&
        !current_module_->getFunction("fyra_mkdir_p")) {
        auto* i64ty = context_->getIntegerType(64);
        auto* fn = builder_->createFunction("fyra_mkdir_p", i64ty, {i64ty});
        auto* path = fn->getParameters().front().get();
        auto c64 = [&](uint64_t v) { return context_->getConstantInt(i64ty, v); };
        // Stack buffer: [0..8191] NUL-terminated path copy, [8192] copy index,
        // [8200] component-scan index (all byte-addressed). The alloc must be
        // created after setInsertPoint(b_entry) — creating it earlier would
        // place the instruction in the previously lowered function's block.
        ir::Value* buf = nullptr;
        auto slot = [&](uint64_t off) { return builder_->createAdd(buf, c64(off)); };
        auto blk = [&](const char* n) { return builder_->createBasicBlock(n, fn); };
        auto* b_entry = blk("mp_entry");
        auto* b_copy = blk("mp_copy");
        auto* b_cnext = blk("mp_cnext");
        auto* b_cdone = blk("mp_cdone");
        auto* b_scan = blk("mp_scan");
        auto* b_snext = blk("mp_snext");
        auto* b_pref = blk("mp_prefix");
        auto* b_restore = blk("mp_restore");
        auto* b_adv = blk("mp_adv");
        auto* b_fin = blk("mp_final");
        auto* b_fail = blk("mp_fail");
        auto* b_ok = blk("mp_ok");

        builder_->setInsertPoint(b_entry);
        buf = builder_->createAlloc(c64(8208), i64ty);
        builder_->createStorel(c64(0), slot(8192));
        builder_->createBr(builder_->createCeq(path, c64(0)), b_fail, b_copy);

        // Copy loop: buf[i] = path[i] until NUL or the 8191-byte bound.
        builder_->setInsertPoint(b_copy);
        auto* i = builder_->createLoadl(slot(8192));
        auto* c = builder_->createLoadub(builder_->createAdd(path, i));
        builder_->createStoreb(c, builder_->createAdd(buf, i));
        builder_->createBr(builder_->createCeq(c, c64(0)), b_cdone, b_cnext);

        builder_->setInsertPoint(b_cnext);
        auto* ni = builder_->createAdd(i, c64(1));
        builder_->createStorel(ni, slot(8192));
        builder_->createBr(builder_->createCult(c64(8191), ni), b_cdone, b_copy);

        builder_->setInsertPoint(b_cdone);
        builder_->createStoreb(c64(0), builder_->createAdd(buf, c64(8191)));
        builder_->createStorel(c64(0), slot(8200));
        builder_->createJmp(b_scan);

        // Scan loop: on each '/' past position 0, temporarily terminate the
        // buffer, mkdir + verify the prefix, then restore the separator.
        builder_->setInsertPoint(b_scan);
        auto* idx = builder_->createLoadl(slot(8200));
        auto* sc = builder_->createLoadub(builder_->createAdd(buf, idx));
        auto* s_nul = builder_->createCeq(sc, c64(0));
        // Accept both '/' and '\\' separators: Windows paths may carry either.
        auto* s_sep = builder_->createOr(builder_->createCeq(sc, c64(47)),
                                       builder_->createCeq(sc, c64(92)));
        auto* s_pos = builder_->createCslt(c64(0), idx);
        auto* do_pref = builder_->createAnd(s_sep, s_pos);
        builder_->createBr(s_nul, b_fin, b_snext);

        builder_->setInsertPoint(b_snext);
        builder_->createBr(do_pref, b_pref, b_adv);

        builder_->setInsertPoint(b_pref);
        auto* paddr = builder_->createAdd(buf, idx);
        auto* saved = builder_->createLoadub(paddr);
        builder_->createStoreb(c64(0), paddr);
        builder_->createExternCall("fs.mkdir", {buf, c64(511)}, i64ty); // mode 0777; result ignored
        auto* pattrs = builder_->createExternCall("fs.getattrs", {buf}, i64ty);
        builder_->createBr(builder_->createCeq(pattrs, c64(0xFFFFFFFFULL)), b_fail, b_restore);

        builder_->setInsertPoint(b_restore);
        builder_->createStoreb(saved, paddr);
        builder_->createJmp(b_adv);

        builder_->setInsertPoint(b_adv);
        builder_->createStorel(builder_->createAdd(idx, c64(1)), slot(8200));
        builder_->createJmp(b_scan);

        // Final component: mkdir + verify; any missing piece fails the call.
        builder_->setInsertPoint(b_fin);
        builder_->createExternCall("fs.mkdir", {buf, c64(511)}, i64ty);
        auto* fattrs = builder_->createExternCall("fs.getattrs", {buf}, i64ty);
        builder_->createBr(builder_->createCeq(fattrs, c64(0xFFFFFFFFULL)), b_fail, b_ok);

        builder_->setInsertPoint(b_fail);
        builder_->createRet(c64(1));
        builder_->setInsertPoint(b_ok);
        builder_->createRet(c64(0));
    }
    std::unordered_map<std::string, uint64_t> region_free;
    if (Memory::runtime_regions_proven_unnecessary(lir_func))
        region_free[main_fn->getName()] = static_cast<uint64_t>(*Memory::scalar_return_kind(lir_func));
    for (const auto& name : registry.getFunctionNames()) {
        auto* function = registry.getFunction(name);
        if (function && Memory::runtime_regions_proven_unnecessary(*function))
            region_free[name == "main" && lir_func.name == "__top_level_wrapper__" ? "__user_main" : name] =
                static_cast<uint64_t>(*Memory::scalar_return_kind(*function));
    }
    lower_region_ownership(*current_module_, region_free);
    bool has_scheduler=false;
    for (const auto& function : current_module_->getFunctions())
        if (function->getName().starts_with("__lymar_task_entry_")) has_scheduler=true;
    if (has_scheduler) lower_worker_failures(*current_module_);
    if (std::getenv("LYMAR_DUMP_FYRA_IR")) current_module_->print(std::cerr);
    return current_module_;
}

const LIRToFyraIRBuilder::DirectFnSig* LIRToFyraIRBuilder::direct_sig_for(const std::string& name) {
    auto it = direct_sigs_.find(name);
    if (it != direct_sigs_.end()) return &it->second;
    DirectFnSig sig;
    direct_sigs_.emplace(name, sig);
    auto& out = direct_sigs_[name];

    if (name == "main" || name == "__user_main" || name == "__top_level_wrapper__") return &out;
    if (LIR::BuiltinUtils::isBuiltinFunction(name)) return &out;
    auto* f = LIR::FunctionRegistry::getInstance().getFunction(name);
    if (!f || reachable_funcs_.find(name) == reachable_funcs_.end()) return &out;
    if (f->gpu_stage != 0) return &out;

    auto tuple_domains = [](const TypePtr& lt, std::vector<int>& domains) -> bool {
        if (!lt || lt->tag != ::TypeTag::Tuple) return false;
        auto* tt = std::get_if<TupleType>(&lt->extra);
        if (!tt || tt->elementTypes.empty() || tt->elementTypes.size() > 8) return true;
        domains.clear();
        for (const auto& et : tt->elementTypes) {
            int d = vdom_of_type(et);
            if (d == VDOM_INVALID) return false;
            domains.push_back(d);
        }
        return true;
    };

    // Frame params flatten like tuples when the callee treats the record
    // read-only (FLAT: per-field scalar args) or only mutates fields without
    // letting the object escape (INOUT: one pointer to a caller-owned field
    // buffer). Anything else keeps the boxed pointer ABI so mutations and
    // identity semantics stay intact.
    auto frame_param_mode = [&](uint32_t p, const TypePtr& lt,
                                std::vector<int>& doms) -> int {
        if (!lt || lt->tag != ::TypeTag::Frame) return 0;
        auto* ft = std::get_if<FrameType>(&lt->extra);
        if (std::getenv("LYMAR_DEBUG_VT2"))
            std::cerr << "[FPM] " << f->name << " p" << p << " ft=" << (ft != nullptr)
                      << " name=" << (ft ? ft->name : std::string("?")) << "\n";
        if (!ft) return 0;
        const FrameFieldInfo* info = frame_field_info(ft->name);
        std::vector<int> scratch;
        const std::vector<int>* fd = frame_flat_domains(info, scratch);
        if (std::getenv("LYMAR_DEBUG_VT2"))
            std::cerr << "[FPM] " << f->name << " p" << p << " info=" << (info != nullptr)
                      << " fd=" << (fd != nullptr) << "\n";
        if (!fd) return 0;
        doms = *fd;
        // A redefined param register cannot stay virtual.
        for (const auto& in : f->instructions) {
            if (in.dst == p && in.result_type != LIR::Type::Void &&
                in.op != LIR::LIR_Op::Return && in.op != LIR::LIR_Op::Ret &&
                in.op != LIR::LIR_Op::RegionMove && in.op != LIR::LIR_Op::RegionEnter &&
                in.op != LIR::LIR_Op::RegionExit && in.op != LIR::LIR_Op::Nop &&
                in.op != LIR::LIR_Op::Label && in.op != LIR::LIR_Op::Jump &&
                in.op != LIR::LIR_Op::JumpIf && in.op != LIR::LIR_Op::JumpIfFalse &&
                in.op != LIR::LIR_Op::FuncDef && in.op != LIR::LIR_Op::Param &&
                !(in.op == LIR::LIR_Op::TupleSet || in.op == LIR::LIR_Op::DictSet ||
                  in.op == LIR::LIR_Op::ListSet || in.op == LIR::LIR_Op::ListAppend ||
                  in.op == LIR::LIR_Op::FrameSetField || in.op == LIR::LIR_Op::FrameSetFieldAtomic ||
                  in.op == LIR::LIR_Op::FrameFieldAtomicAdd || in.op == LIR::LIR_Op::FrameFieldAtomicSub ||
                  in.op == LIR::LIR_Op::TaskSetField || in.op == LIR::LIR_Op::TaskSetState))
                return 0;
        }
        // Alias closure: the param plus every Mov/Copy destination reachable
        // from it. Mutations or escapes through any alias disqualify FLAT.
        std::unordered_set<uint32_t> alias{p};
        bool grew = true;
        while (grew) {
            grew = false;
            for (const auto& in : f->instructions) {
                if ((in.op == LIR::LIR_Op::Mov || in.op == LIR::LIR_Op::Copy) &&
                    in.a != UINT32_MAX && alias.count(in.a) && in.dst != UINT32_MAX &&
                    !alias.count(in.dst)) {
                    alias.insert(in.dst);
                    grew = true;
                }
            }
        }
        bool mutates = false;
        for (const auto& in : f->instructions) {
            auto uses_alias = [&](uint32_t r) { return r != UINT32_MAX && alias.count(r); };
            switch (in.op) {
                case LIR::LIR_Op::RegionEnter: case LIR::LIR_Op::RegionExit:
                case LIR::LIR_Op::Nop: case LIR::LIR_Op::Label:
                case LIR::LIR_Op::Jump: case LIR::LIR_Op::JumpIf:
                case LIR::LIR_Op::JumpIfFalse: case LIR::LIR_Op::RegionMove:
                    break;
                case LIR::LIR_Op::FrameGetField:
                    // Field read; the index operand is a constant, not a reg.
                    break;
                case LIR::LIR_Op::FrameSetField:
                    if (uses_alias(in.dst)) mutates = true;
                    break;
                case LIR::LIR_Op::Mov: case LIR::LIR_Op::Copy:
                    break; // alias propagation already accounted for
                case LIR::LIR_Op::NewFrame:
                    break; // a/b are ctor zeros, not register operands
                case LIR::LIR_Op::Return: case LIR::LIR_Op::Ret: {
                    // `a` carries the returned value only for aggregate
                    // returns; scalar/void returns leave ctor-garbage that
                    // must not alias-match (self is often register 0). The
                    // declared return type is the only reliable signal —
                    // `a`'s register type can alias param 0 on void returns.
                    bool ret_agg = f->return_language_type &&
                        (f->return_language_type->tag == ::TypeTag::Frame ||
                         f->return_language_type->tag == ::TypeTag::Tuple);
                    if (ret_agg && uses_alias(in.a)) return 0;
                    break;
                }
                case LIR::LIR_Op::TupleCreate: case LIR::LIR_Op::DictCreate:
                case LIR::LIR_Op::ListCreate:
                    // Elements arrive via call_args; storing the record into
                    // a container is an escape.
                    for (auto ar : in.call_args)
                        if (uses_alias(ar)) return 0;
                    break;
                case LIR::LIR_Op::Call: case LIR::LIR_Op::CallVoid:
                default: {
                    // Any other use of an alias — call args, returns, stores,
                    // comparisons, atomics, container writes — is an escape or
                    // a mutation the flattened ABI cannot express.
                    bool bad = uses_alias(in.a) || uses_alias(in.b) || uses_alias(in.dst);
                    for (auto ar : in.call_args) bad = bad || uses_alias(ar);
                    if (bad) return 0;
                    break;
                }
            }
        }
        return mutates ? 2 : 1;
    };

    out.param_elem_domains.assign(f->param_count, {});
    out.param_inout.assign(f->param_count, 0);
    std::vector<int> fd_scratch;
    for (uint32_t i = 0; i < f->param_count; ++i) {
        auto lt_it = f->register_language_types.find(i);
        const TypePtr& lt = (lt_it != f->register_language_types.end()) ? lt_it->second : TypePtr();
        if (lt && lt->tag == ::TypeTag::Tuple) {
            std::vector<int> doms;
            if (!tuple_domains(lt, doms)) return &out; // nested/oversized/invalid
            out.param_elem_domains[i] = std::move(doms);
        } else if (lt && lt->tag == ::TypeTag::Frame) {
            std::vector<int> doms;
            int mode = frame_param_mode(i, lt, doms);
            if (mode) {
                out.param_elem_domains[i] = std::move(doms);
                out.param_inout[i] = static_cast<char>(mode);
            }
        }
    }

    // Return shape: tuple returns use a caller-allocated sret buffer appended
    // as the last flattened parameter; everything else returns one word.
    const TypePtr* ret_lt = nullptr;
    TypePtr ret_owned;
    if (f->return_language_type) {
        ret_owned = f->return_language_type;
        ret_lt = &ret_owned;
    } else {
        for (const auto& inst : f->instructions) {
            if ((inst.op == LIR::LIR_Op::Return || inst.op == LIR::LIR_Op::Ret) &&
                inst.a != UINT32_MAX) {
                auto rit = f->register_language_types.find(inst.a);
                if (rit != f->register_language_types.end() && rit->second &&
                    (rit->second->tag == ::TypeTag::Tuple || rit->second->tag == ::TypeTag::Frame)) {
                    ret_owned = rit->second;
                    ret_lt = &ret_owned;
                }
                break;
            }
        }
    }
    if (ret_lt && (*ret_lt)->tag == ::TypeTag::Frame) {
        auto* ft = std::get_if<FrameType>(&(*ret_lt)->extra);
        const FrameFieldInfo* info = ft ? frame_field_info(ft->name) : nullptr;
        std::vector<int> scratch;
        const std::vector<int>* fd = frame_flat_domains(info, scratch);
        if (!fd || fd->empty()) return &out;
        out.ret_sret = true;
        out.ret_frame = true;
        out.ret_domains = *fd;
    } else if (ret_lt && (*ret_lt)->tag == ::TypeTag::Tuple) {
        std::vector<int> doms;
        if (!tuple_domains(*ret_lt, doms) || doms.empty()) return &out;
        out.ret_sret = true;
        out.ret_domains = std::move(doms);
    } else if (ret_lt) {
        auto tag = (*ret_lt)->tag;
        if (tag == ::TypeTag::Float32 || tag == ::TypeTag::Float64) out.ret_float = true;
        if (tag == ::TypeTag::Nil) out.ret_nil = true;
    } else {
        for (const auto& inst : f->instructions) {
            if (inst.op != LIR::LIR_Op::Return && inst.op != LIR::LIR_Op::Ret) continue;
            if (inst.type_a == LIR::Type::F64 || inst.type_a == LIR::Type::F32) { out.ret_float = true; break; }
            auto rt = f->register_types.find(inst.a);
            if (rt != f->register_types.end() && (rt->second == LIR::Type::F64 || rt->second == LIR::Type::F32)) { out.ret_float = true; break; }
        }
    }

    // Nil-returning functions (`: nil` lowers to Any; implicit fallthrough
    // returns the nil word): when every Return/Ret yields nil — or there are
    // no value returns at all — the .direct result is the constant VAL_NIL,
    // letting callers store a provably-scalar constant and skip the edge.
    if (!out.ret_sret && !out.ret_float && !out.ret_nil) {
        bool all_nil = true;
        for (const auto& inst : f->instructions) {
            if (inst.op != LIR::LIR_Op::Return && inst.op != LIR::LIR_Op::Ret) continue;
            if (inst.a == UINT32_MAX) continue;
            auto lt = f->register_language_types.find(inst.a);
            if (lt != f->register_language_types.end() && lt->second) {
                if (lt->second->tag != ::TypeTag::Nil) { all_nil = false; break; }
                continue; // explicitly nil-typed return value
            }
            auto rt = f->register_types.find(inst.a);
            // Without language-type evidence only an explicit void operand
            // proves nil; a bare pointer could be a real returned object.
            if (rt == f->register_types.end() || rt->second != LIR::Type::Void) {
                all_nil = false;
                break;
            }
        }
        out.ret_nil = all_nil;
    }

    // Varargs entry points keep the standard ABI.
    for (const auto& inst : f->instructions) {
        if (inst.op == LIR::LIR_Op::VaStart || inst.op == LIR::LIR_Op::VaArg || inst.op == LIR::LIR_Op::VaEnd)
            return &out;
    }

    out.eligible = true;
    return &out;
}

LIRToFyraIRBuilder::VtSafeInfo LIRToFyraIRBuilder::compute_vt_safe(
    const LIR::LIR_Function& fn, const DirectFnSig* sig) {
    VtSafeInfo out;
    // def_counts must count only true redefinitions: void-result ops
    // (RegionEnter/Exit/Move, jumps, returns, Nop) are emitted with dst=0 —
    // a valid parameter register! — and container ops (TupleSet/DictSet/
    // ListSet/...) carry the mutated container in dst. Neither produces a
    // new value for the register.
    auto container_dst_use = [](LIR::LIR_Op op) -> bool {
        switch (op) {
            case LIR::LIR_Op::TupleSet: case LIR::LIR_Op::DictSet:
            case LIR::LIR_Op::ListSet: case LIR::LIR_Op::ListAppend:
            case LIR::LIR_Op::FrameSetField: case LIR::LIR_Op::FrameSetFieldAtomic:
            case LIR::LIR_Op::FrameFieldAtomicAdd: case LIR::LIR_Op::FrameFieldAtomicSub:
            case LIR::LIR_Op::TaskSetField: case LIR::LIR_Op::TaskSetState:
                return true;
            default: return false;
        }
    };
    // Ops that never produce a fresh register value: their dst field is
    // either the ctor default 0 (a valid parameter register!) or a mutated
    // container. Return/Ret carry the value in `a`, RegionMove/Enter/Exit
    // are bookkeeping, and the rest are control/meta ops.
    auto non_defining_op = [](LIR::LIR_Op op) -> bool {
        switch (op) {
            case LIR::LIR_Op::Return: case LIR::LIR_Op::Ret:
            case LIR::LIR_Op::RegionMove: case LIR::LIR_Op::RegionEnter:
            case LIR::LIR_Op::RegionExit: case LIR::LIR_Op::Nop:
            case LIR::LIR_Op::Label: case LIR::LIR_Op::Jump:
            case LIR::LIR_Op::JumpIf: case LIR::LIR_Op::JumpIfFalse:
            case LIR::LIR_Op::FuncDef: case LIR::LIR_Op::Param:
                return true;
            default: return false;
        }
    };
    // defs_of collects every defining instruction per register. Call counts
    // as a definition even when its LIR result_type is Void: sret `.direct`
    // results are real register definitions the lowering tracks.
    std::unordered_map<uint32_t, std::vector<size_t>> defs_of;
    for (size_t i = 0; i < fn.instructions.size(); ++i) {
        const auto& in = fn.instructions[i];
        if (in.dst == UINT32_MAX) continue;
        if (in.result_type == LIR::Type::Void && in.op != LIR::LIR_Op::Call) continue;
        if (non_defining_op(in.op) || container_dst_use(in.op)) continue;
        defs_of[in.dst].push_back(i);
        out.def_inst_idx[in.dst] = i;
    }
    const bool sret_ret = sig && sig->ret_sret;

    // Candidates: registers that can hold a virtual tuple.
    //  - TupleCreate results (single def, tuple-typed, valid element domains)
    //  - flattened `.direct` parameters (never redefined)
    //  - sret results of `.direct` calls (single def, mirrors Call lowering)
    //  - Mov/Copy destinations whose EVERY definition is a Mov/Copy (the
    //    virtual-ness then propagates from whatever the sources are)
    std::unordered_set<uint32_t> cand;
    std::unordered_map<uint32_t, std::vector<uint32_t>> mov_srcs;
    auto dc_of = [&](uint32_t r) -> int {
        auto it = defs_of.find(r);
        return it == defs_of.end() ? 0 : (int)it->second.size();
    };
    for (const auto& in : fn.instructions) {
        if (in.dst == UINT32_MAX) continue;
        if (in.op == LIR::LIR_Op::TupleCreate) {
            if (dc_of(in.dst) != 1) continue;
            auto lt = fn.register_language_types.find(in.dst);
            if (lt == fn.register_language_types.end() || !lt->second ||
                lt->second->tag != ::TypeTag::Tuple) continue;
            auto* tt = std::get_if<TupleType>(&lt->second->extra);
            if (!tt || tt->elementTypes.empty() || tt->elementTypes.size() > 8) continue;
            bool ok = true;
            for (const auto& et : tt->elementTypes)
                if (vdom_of_type(et) == VDOM_INVALID) { ok = false; break; }
            if (ok) cand.insert(in.dst);
        } else if (in.op == LIR::LIR_Op::NewFrame) {
            // Small primitive-field records virtualize like tuples; the field
            // domains come from the recovered frame table.
            if (dc_of(in.dst) != 1) continue;
            auto lt = fn.register_language_types.find(in.dst);
            if (lt == fn.register_language_types.end() || !lt->second ||
                lt->second->tag != ::TypeTag::Frame) continue;
            auto* ft = std::get_if<FrameType>(&lt->second->extra);
            if (!ft) continue;
            const FrameFieldInfo* info = frame_field_info(ft->name);
            std::vector<int> scratch;
            if (frame_flat_domains(info, scratch)) cand.insert(in.dst);
        } else if (in.op == LIR::LIR_Op::Call && !in.func_name.empty()) {
            // sret results of `.direct` calls arrive as virtual tuples. The
            // condition mirrors the Call lowering exactly: reachable callee,
            // eligible flattened signature, declared `.direct` IR function,
            // and matching argument count.
            auto* cf = LIR::FunctionRegistry::getInstance().getFunction(in.func_name);
            if (!cf || in.call_args.size() != cf->param_count) continue;
            if (!reachable_funcs_.count(in.func_name)) continue;
            const DirectFnSig* csig = direct_sig_for(in.func_name);
            if (!csig->eligible || !csig->ret_sret) continue;
            if (!current_module_->getFunction(in.func_name + ".direct")) continue;
            if (dc_of(in.dst) == 1) cand.insert(in.dst);
        }
    }
    if (sig) {
        for (size_t p = 0; p < fn.param_count && p < sig->param_elem_domains.size(); ++p) {
            if (sig->param_elem_domains[p].empty()) continue;
            // A param register written anywhere in the body is redefined;
            // its vtuple slot would not survive to later RegionMoves.
            if (dc_of(static_cast<uint32_t>(p)) != 0) continue;
            cand.insert(static_cast<uint32_t>(p));
        }
    }
    // Mov/Copy-propagated candidates: every def must be a Mov/Copy so the
    // register is virtual exactly when its sources are.
    for (const auto& [r, didx] : defs_of) {
        if (cand.count(r) || didx.empty()) continue;
        std::vector<uint32_t> srcs;
        bool allmov = true;
        for (size_t i : didx) {
            const auto& in = fn.instructions[i];
            if (in.op != LIR::LIR_Op::Mov && in.op != LIR::LIR_Op::Copy) { allmov = false; break; }
            if (in.a != UINT32_MAX) srcs.push_back(in.a);
        }
        if (allmov) { cand.insert(r); mov_srcs[r] = std::move(srcs); }
    }
    if (cand.empty()) return out;

    // Element count for virtual-container candidacy: tuples use their type's
    // element list; frames use the recovered field count (0 when unknown —
    // unflattenable frames are never candidates anyway).
    auto vrecord_elem_count = [&](uint32_t r) -> size_t {
        auto lt = fn.register_language_types.find(r);
        if (lt == fn.register_language_types.end() || !lt->second) return 0;
        if (lt->second->tag == ::TypeTag::Tuple) {
            auto* tt = std::get_if<TupleType>(&lt->second->extra);
            return tt ? tt->elementTypes.size() : 0;
        }
        if (lt->second->tag == ::TypeTag::Frame) {
            auto* ft = std::get_if<FrameType>(&lt->second->extra);
            if (!ft) return 0;
            const FrameFieldInfo* info = frame_field_info(ft->name);
            if (!info || info->field_count < 1) return 0;
            std::vector<int> scratch;
            return frame_flat_domains(info, scratch) ? static_cast<size_t>(info->field_count) : 0;
        }
        return 0;
    };

    // uses_ok[r]: false when some use of r forces materialization or moves
    // the value through the tagged/managed ABI. This is a static property —
    // it does not depend on which other registers are virtual.
    std::unordered_map<uint32_t, bool> uses_ok;
    for (uint32_t r : cand) uses_ok[r] = true;
    size_t dbg_idx = 0;
    auto unsafe_use = [&](uint32_t r) {
        if (r != UINT32_MAX && uses_ok.count(r) && uses_ok[r]) {
            uses_ok[r] = false;
            if (std::getenv("LYMAR_DEBUG_VT2"))
                std::cerr << "[VTU] " << fn.name << " r" << r << " unset by op "
                          << (int)fn.instructions[dbg_idx].op << " @" << dbg_idx
                          << " dst=" << fn.instructions[dbg_idx].dst
                          << " a=" << fn.instructions[dbg_idx].a
                          << " b=" << fn.instructions[dbg_idx].b
                          << " fn=" << fn.instructions[dbg_idx].func_name << "\n";
        }
    };
    for (size_t ii = 0; ii < fn.instructions.size(); ++ii) {
        const auto& in = fn.instructions[ii];
        dbg_idx = ii;
        switch (in.op) {
            case LIR::LIR_Op::RegionEnter: case LIR::LIR_Op::RegionExit:
            case LIR::LIR_Op::TupleGet: case LIR::LIR_Op::TupleLen:
            case LIR::LIR_Op::RegionMove: case LIR::LIR_Op::Nop:
            case LIR::LIR_Op::Label: case LIR::LIR_Op::Jump:
            case LIR::LIR_Op::JumpIf: case LIR::LIR_Op::JumpIfFalse:
            case LIR::LIR_Op::NewFrame:
            case LIR::LIR_Op::Mov: case LIR::LIR_Op::Copy:
                // Mov/Copy propagate virtual slots to their destination;
                // record aliases share canonical element slots so field
                // writes stay visible through every name. An erased
                // (`any`/union) destination still needs the tagged word, so
                // the source must materialize — except record-typed
                // destinations, which stay virtual themselves.
                if ((in.op == LIR::LIR_Op::Mov || in.op == LIR::LIR_Op::Copy) &&
                    in.dst != UINT32_MAX && s_lang_type_is_erased(fn, in.dst) &&
                    !s_lang_type_is_record(fn, in.dst))
                    unsafe_use(in.a);
                break;
            case LIR::LIR_Op::TupleSet:
                // Container mutation keeps the tuple virtual; the stored
                // value materializes if it is itself a vtuple.
                unsafe_use(in.b);
                break;
            case LIR::LIR_Op::TupleCreate:
                // a/b are ctor-default zeros; elements arrive via call_args.
                for (auto ar : in.call_args) unsafe_use(ar);
                break;
            case LIR::LIR_Op::FrameGetField:
                // Virtual field read; `b` is the constant field index.
                break;
            case LIR::LIR_Op::FrameSetField:
                // Virtual field write on the container in `dst`; only the
                // stored value (b) must materialize if virtual. `a` is the
                // constant field index.
                unsafe_use(in.b);
                break;
            case LIR::LIR_Op::FrameGetFieldAtomic:
                // Atomic access needs the real object; `b` is a constant.
                unsafe_use(in.a);
                break;
            case LIR::LIR_Op::FrameSetFieldAtomic:
            case LIR::LIR_Op::FrameFieldAtomicAdd:
            case LIR::LIR_Op::FrameFieldAtomicSub:
                unsafe_use(in.dst);
                unsafe_use(in.b);
                break;
            case LIR::LIR_Op::Return: case LIR::LIR_Op::Ret:
                // Value is in `a`; safe only for sret `.direct` returns.
                // Void returns carry ctor-garbage operands — never a use.
                if (!sret_ret && in.result_type != LIR::Type::Void) unsafe_use(in.a);
                break;
            case LIR::LIR_Op::Call: case LIR::LIR_Op::CallVoid: {
                // Per-argument safety: a flattened `.direct` callee keeps
                // tuple arguments virtual only when element counts match;
                // scalar/tagged parameters force load_reg, which
                // materializes any vtuple arg.
                const DirectFnSig* csig = nullptr;
                const LIR::LIR_Function* cf = nullptr;
                if (!in.func_name.empty()) {
                    cf = LIR::FunctionRegistry::getInstance().getFunction(in.func_name);
                    if (cf && in.call_args.size() == cf->param_count) {
                        const DirectFnSig* s = direct_sig_for(in.func_name);
                        if (s->eligible) csig = s;
                    }
                }
                for (size_t ai = 0; ai < in.call_args.size(); ++ai) {
                    uint32_t ar = in.call_args[ai];
                    bool osafe = false;
                    if (csig && ai < csig->param_elem_domains.size()) {
                        const auto& doms = csig->param_elem_domains[ai];
                        osafe = doms.empty()
                            ? vrecord_elem_count(ar) == 0
                            : vrecord_elem_count(ar) == doms.size();
                        if (std::getenv("LYMAR_DEBUG_VT2") && uses_ok.count(ar))
                            std::cerr << "[VTU] " << fn.name << " call " << in.func_name
                                      << " arg" << ai << " r" << ar << " cnt="
                                      << vrecord_elem_count(ar) << " doms=" << doms.size()
                                      << " csig=" << (csig != nullptr) << "\n";
                    }
                    if (ar != UINT32_MAX && !osafe) unsafe_use(ar);
                }
                break;
            }
            default:
                // a/b are register operands for all remaining ops; container
                // ops additionally read their container from dst.
                unsafe_use(in.a);
                unsafe_use(in.b);
                for (auto ar : in.call_args) unsafe_use(ar);
                if (container_dst_use(in.op)) unsafe_use(in.dst);
                break;
        }
    }

    // Fixpoint: a candidate stays virtual iff all its uses are virtual-safe
    // AND every Mov/Copy source feeding it is itself virtual-safe.
    for (uint32_t r : cand) out.safe[r] = true;
    bool changed = true;
    while (changed) {
        changed = false;
        for (uint32_t r : cand) {
            if (!out.safe[r]) continue;
            bool ok = uses_ok[r];
            if (ok) {
                auto mi = mov_srcs.find(r);
                if (mi != mov_srcs.end()) {
                    for (uint32_t s : mi->second) {
                        auto si = out.safe.find(s);
                        if (si == out.safe.end() || !si->second) { ok = false; break; }
                    }
                }
            }
            if (!ok) {
                if (std::getenv("LYMAR_DEBUG_VT"))
                    std::cerr << "[VT] " << fn.name << " unset r" << r
                              << " uses_ok=" << uses_ok[r] << "\n";
                out.safe[r] = false;
                changed = true;
            }
        }
    }
    for (auto it = out.safe.begin(); it != out.safe.end();) {
        if (!it->second) it = out.safe.erase(it); else ++it;
    }

    // Canonical element slots for loop-variant candidates: a register whose
    // first use precedes its last definition may carry a different tuple
    // value around a CFG back-edge than the single-pass lowering saw at the
    // use. Element values then live in spill slots that every definition
    // writes and every use reloads.
    {
        std::unordered_map<uint32_t, size_t> first_use;
        auto note_use = [&](uint32_t r, size_t i) {
            if (r == UINT32_MAX || !cand.count(r)) return;
            auto it = first_use.find(r);
            if (it == first_use.end() || i < it->second) first_use[r] = i;
        };
        for (size_t i = 0; i < fn.instructions.size(); ++i) {
            const auto& in = fn.instructions[i];
            note_use(in.a, i);
            note_use(in.b, i);
            for (auto ar : in.call_args) note_use(ar, i);
            if (container_dst_use(in.op) || in.isReturn() ||
                in.op == LIR::LIR_Op::JumpIf || in.op == LIR::LIR_Op::JumpIfFalse)
                note_use(in.dst, i);
        }
        uint32_t next_pseudo = 0x40000000u;
        for (uint32_t r : cand) {
            auto ld = defs_of.find(r);
            if (ld == defs_of.end() || ld->second.empty()) continue; // params: no defs
            auto lt = fn.register_language_types.find(r);
            if (lt == fn.register_language_types.end() || !lt->second) continue;
            std::vector<int> doms;
            if (lt->second->tag == ::TypeTag::Frame) {
                // Virtual records always spill elements to canonical slots:
                // `var q = p` then shares the same slots, preserving frame
                // reference semantics (field writes visible via every alias).
                auto* ft = std::get_if<FrameType>(&lt->second->extra);
                if (!ft) continue;
                const FrameFieldInfo* info = frame_field_info(ft->name);
                std::vector<int> scratch;
                const std::vector<int>* fd = frame_flat_domains(info, scratch);
                if (!fd) continue;
                doms = *fd;
            } else {
                if (lt->second->tag != ::TypeTag::Tuple) continue;
                auto fu = first_use.find(r);
                if (fu == first_use.end()) continue;
                size_t last_def = ld->second.back();
                if (fu->second >= last_def) continue; // defs all precede uses
                auto* tt = std::get_if<TupleType>(&lt->second->extra);
                if (!tt || tt->elementTypes.empty() || tt->elementTypes.size() > 8) continue;
                bool ok = true;
                for (const auto& et : tt->elementTypes) {
                    int d = vdom_of_type(et);
                    if (d == VDOM_INVALID) { ok = false; break; }
                    doms.push_back(d);
                }
                if (!ok) continue;
            }
            std::vector<uint32_t> preds;
            for (size_t j = 0; j < doms.size(); ++j) preds.push_back(next_pseudo++);
            out.canon_regs[r] = std::move(preds);
            out.canon_domains[r] = std::move(doms);
        }
    }
    if (std::getenv("LYMAR_DEBUG_VT")) {
        std::cerr << "[VT] " << fn.name << " sig=" << (sig ? 1 : 0) << " sret=" << sret_ret << " safe:";
        for (auto& [r, v] : out.safe) std::cerr << " r" << r << "=" << v;
        std::cerr << "\n";
    }
    return out;
}

void LIRToFyraIRBuilder::build_function_body(ir::Function* main_fn, const LIR::LIR_Function& lir_func,
                                             const LIRToFyraIRBuilder::DirectFnCtx* dctx) {
    if (std::getenv("LYMAR_DUMP_LIR")) std::cerr << "=== LIR " << lir_func.name << " ===\n" << LIR::Disassembler(lir_func).disassemble();
    ir::BasicBlock* entry_bb = builder_->createBasicBlock("entry", main_fn);
    builder_->setInsertPoint(entry_bb);
    // Lazy: only materialize the region_current call when a RegionMove (or
    // other consumer) actually needs it — pure `.direct` functions with all
    // moves elided must not carry a call that would block inlining.
    ir::Value* caller_region = nullptr;
    auto get_caller_region = [&]() -> ir::Value* {
        if (!caller_region) {
            if (Memory::runtime_regions_proven_unnecessary(lir_func)) {
                caller_region = static_cast<ir::Value*>(
                    context_->getConstantInt(context_->getIntegerType(64), 0));
            } else {
                // Emit at the entry block so the call is hoisted out of loops.
                auto saved_ip = builder_->getInsertPoint();
                auto& einstrs = entry_bb->getInstructions();
                if (!einstrs.empty() && einstrs.back()->getOpcode() <= ir::Instruction::Hlt)
                    builder_->setInsertPoint(entry_bb, std::prev(einstrs.end()));
                else
                    builder_->setInsertPoint(entry_bb);
                caller_region = builder_->createExternCall("lymar_aot_region_current", {},
                    context_->getIntegerType(64));
                builder_->setInsertPoint(saved_ip);
            }
        }
        return caller_region;
    };

    std::unordered_map<uint32_t, size_t> label_to_index;
    for (size_t i = 0; i < lir_func.instructions.size(); ++i) {
        if (lir_func.instructions[i].op == LIR::LIR_Op::Label) {
            label_to_index[lir_func.instructions[i].imm] = i;
        }
    }

    std::unordered_set<size_t> leaders;
    leaders.insert(0);
    for (size_t i = 0; i < lir_func.instructions.size(); ++i) {
        const auto& inst = lir_func.instructions[i];
        if (inst.op == LIR::LIR_Op::Jump || inst.op == LIR::LIR_Op::JumpIf || inst.op == LIR::LIR_Op::JumpIfFalse) {
            if (label_to_index.count(inst.imm)) {
                leaders.insert(label_to_index[inst.imm]);
            } else if (inst.imm < lir_func.instructions.size()) {
                leaders.insert(inst.imm);
            }
            if (i + 1 < lir_func.instructions.size()) {
                leaders.insert(i + 1);
            }
        } else if (inst.op == LIR::LIR_Op::Label) {
            leaders.insert(i);
        }
    }

    std::unordered_map<size_t, ir::BasicBlock*> block_map;
    for (size_t i = 0; i < lir_func.instructions.size(); ++i) {
        if (leaders.count(i)) {
            std::string block_name = "block_" + std::to_string(i);
            block_map[i] = builder_->createBasicBlock(block_name, main_fn);
        }
    }

    ir::BasicBlock* exit_bb = nullptr;
    auto get_target_block = [&](uint32_t target_imm, size_t current_inst_index) -> ir::BasicBlock* {
        if (label_to_index.count(target_imm)) {
            size_t idx = label_to_index[target_imm];
            if (block_map.count(idx)) {
                return block_map.at(idx);
            }
        }
        if (block_map.count(target_imm)) {
            return block_map.at(target_imm);
        }
        if (target_imm >= lir_func.instructions.size()) {
            if (!exit_bb) {
                exit_bb = builder_->createBasicBlock("exit_block", main_fn);
                auto saved_ip = builder_->getInsertPoint();
                builder_->setInsertPoint(exit_bb);
                builder_->createRet(context_->getConstantInt(context_->getIntegerType(64), 0));
                if (saved_ip) builder_->setInsertPoint(saved_ip);
            }
            return exit_bb;
        }
        return nullptr;
    };

    std::unordered_map<uint32_t, ir::Value*> regs;
    std::unordered_map<uint32_t, ir::BasicBlock*> register_definitions;
    std::unordered_map<uint32_t, LIR::Type> reg_types;
    std::unordered_map<uint32_t, int> reg_decimal_scales;
    std::unordered_map<uint32_t, int64_t> reg_int_values;
    std::unordered_map<uint32_t, double> reg_float_values;
    std::unordered_map<uint32_t, std::string> reg_string_literals;

    auto decimal_scale_for_reg = [&](uint32_t r) -> int {
        if (reg_decimal_scales.count(r)) return reg_decimal_scales[r];
        auto it = lir_func.register_language_types.find(r);
        if (it != lir_func.register_language_types.end() && it->second) {
            int scale = it->second->getDecimalScale();
            if (scale > 0) return scale;
        }
        return -1;
    };

    auto decimal_scale_for_inst = [&](const LIR::LIR_Inst& dec_inst) -> int {
        int dst_scale = decimal_scale_for_reg(dec_inst.dst);
        if (dst_scale > 0) return dst_scale;
        int a_scale = decimal_scale_for_reg(dec_inst.a);
        int b_scale = decimal_scale_for_reg(dec_inst.b);
        if (a_scale > 0 && b_scale > 0) return std::max(a_scale, b_scale);
        if (a_scale > 0) return a_scale;
        if (b_scale > 0) return b_scale;
        return 4;
    };

    auto pow10_i64 = [](int n) -> int64_t {
        int64_t value = 1;
        for (int i = 0; i < n; ++i) value *= 10;
        return value;
    };


    auto is_float_op = [&](const LIR::LIR_Inst& inst) -> bool {
        auto is_dec = [&](uint32_t r) {
            return r != UINT32_MAX && reg_decimal_scales.count(r) && reg_decimal_scales[r] > 0;
        };
        if (is_dec(inst.a) || is_dec(inst.b) || is_dec(inst.dst)) return false;

        if (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32) return true;
        if (inst.type_a == LIR::Type::F64 || inst.type_a == LIR::Type::F32) return true;
        if (inst.type_b == LIR::Type::F64 || inst.type_b == LIR::Type::F32) return true;
        if (inst.a != UINT32_MAX && reg_types.count(inst.a) && (reg_types[inst.a] == LIR::Type::F64 || reg_types[inst.a] == LIR::Type::F32)) return true;
        if (inst.b != UINT32_MAX && reg_types.count(inst.b) && (reg_types[inst.b] == LIR::Type::F64 || reg_types[inst.b] == LIR::Type::F32)) return true;

        auto is_reg_float = [&](uint32_t r) {
            if (r == UINT32_MAX) return false;
            auto it = lir_func.register_language_types.find(r);
            if (it != lir_func.register_language_types.end() && it->second) {
                return it->second->tag == ::TypeTag::Float64 || it->second->tag == ::TypeTag::Float32;
            }
            auto it2 = lir_func.register_types.find(r);
            if (it2 != lir_func.register_types.end()) {
                return it2->second == LIR::Type::F64 || it2->second == LIR::Type::F32;
            }
            return false;
        };

        if (is_reg_float(inst.a) || is_reg_float(inst.b) || is_reg_float(inst.dst)) return true;
        return false;
    };

    std::unordered_set<uint32_t> reassigned_parameters;
    size_t max_reg = lir_func.register_count;
    for (const auto& inst : lir_func.instructions) {
        // Control-flow ops carry dst=0 padding and never write a register;
        // counting them would mark parameter 0 as reassigned in every
        // function containing a jump or return.
        bool writes_dst = true;
        switch (inst.op) {
            case LIR::LIR_Op::Jump: case LIR::LIR_Op::JumpIfFalse: case LIR::LIR_Op::JumpIf:
            case LIR::LIR_Op::Label: case LIR::LIR_Op::Nop: case LIR::LIR_Op::Return:
            case LIR::LIR_Op::Ret:
                writes_dst = false;
                break;
            default: break;
        }
        if (writes_dst && inst.result_type != LIR::Type::Void && inst.dst < lir_func.param_count)
            reassigned_parameters.insert(inst.dst);
        if (inst.dst != UINT32_MAX) max_reg = std::max(max_reg, (size_t)inst.dst);
        // Scheduler cores and deadline are immediate configuration, not
        // register operands. A duration must never size the register frame.
        if (inst.op != LIR::LIR_Op::SchedulerInit && inst.op != LIR::LIR_Op::ParallelInit) {
            if (inst.a != UINT32_MAX) max_reg = std::max(max_reg, (size_t)inst.a);
            if (inst.b != UINT32_MAX) max_reg = std::max(max_reg, (size_t)inst.b);
        }
        for (auto arg : inst.call_args) max_reg = std::max(max_reg, (size_t)arg);
    }
    std::unordered_set<uint32_t> pointer_assigned_regs;
    // Registers whose slot content is already a tagged LmValue word (SMI,
    // immediate, or heap pointer produced by an erased-domain runtime call).
    // Distinct from pointer_assigned_regs: foreign/raw pointers are
    // pointer-assigned but NOT tagged — they still need tag_pointer boxing
    // when they cross into an erased slot.
    std::unordered_set<uint32_t> tagged_word_regs;
    // A register whose declared language type is erased/dynamic (any, union,
    // optional, nil, aggregate) holds a tagged LmValue word even when its LIR
    // result_type is a scalar i64 — e.g. `var x: any = int_call()`. Without
    // this, the Call/Mov dst stays scalar-classified and word_kind reports 0,
    // so tagged SMIs reach consumers as "raw" ints (print shows 73 for 9).
    auto lang_type_is_erased = [&](uint32_t reg) -> bool { return s_lang_type_is_erased(lir_func, reg); };
    // Registers whose content is still a tagged LmValue word after lowering.
    // This is exactly the set untag_word passes through unchanged; scalar
    // destinations (untag_int/untag_bool/to_float/untag_ptr outputs) hold raw
    // domain values and must NOT be marked or tag_word would skip encoding.
    auto lang_type_holds_tagged_word = [&](uint32_t reg) -> bool { return s_lang_type_holds_tagged_word(lir_func, reg); };
    auto is_typed_primitive_list = [&](uint32_t r) -> bool { return s_is_typed_primitive_list(lir_func, r); };
    // Typed primitive lists store raw scalar elements; the list header's high
    // bits record the element-storage kind (0=tagged, 1=raw int, 2=raw bool)
    // so runtime formatting can decode elements without a kind sidecar.
    auto typed_list_element_kind = [&](uint32_t r) -> uint64_t { return s_typed_list_element_kind(lir_func, r); };
    {
        auto _doms = compute_reg_domain_sets(lir_func);
        pointer_assigned_regs = std::move(_doms.pointer_assigned);
        tagged_word_regs = std::move(_doms.tagged_word);
    }

    // Virtual-tuple safety + canonical-slot analysis, computed before
    // parameter initialization so `.direct` tuple params can be backed by
    // canonical spill slots when the register is loop-variant.
    const DirectFnSig* self_sig = dctx ? direct_sig_for(lir_func.name) : nullptr;
    if (self_sig && !self_sig->eligible) self_sig = nullptr;
    auto vt_info = compute_vt_safe(lir_func, self_sig);

    std::unordered_map<uint32_t, ir::Instruction*> reg_slots;
    // Virtual tuples: registers holding tuple values whose elements are kept
    // as scalar SSA/slot values instead of a heap-allocated lm_tuple. Escapes
    // (any use outside TupleGet/TupleSet/TupleLen/direct-call args/sret
    // returns) materialize the real tuple lazily at the use point.
    std::unordered_map<uint32_t, std::vector<VTupleElem>> vtuples;
    // Registers whose virtual container is a named record (frame) rather than
    // a tuple: materialization builds an LmFrame and Mov propagation shares
    // canonical element slots to preserve reference semantics.
    std::unordered_set<uint32_t> vframes;
    std::function<void(uint32_t)> materialize_vtuple;
    // `.direct` flattened-ABI variants of branch-free functions are pure
    // scalar SSA: no CFG joins or back-edges exist, so spill slots are
    // unnecessary and their Alloc instructions would block inlining.
    bool branch_free = dctx != nullptr;
    if (branch_free) {
        for (const auto& inst : lir_func.instructions) {
            if (inst.op == LIR::LIR_Op::Label || inst.op == LIR::LIR_Op::Jump ||
                inst.op == LIR::LIR_Op::JumpIf || inst.op == LIR::LIR_Op::JumpIfFalse) {
                branch_free = false;
                break;
            }
        }
    }
    const bool scalar_registers = (Memory::runtime_regions_proven_unnecessary(lir_func) &&
        Memory::proven_scalar_leaf(lir_func)) || branch_free;
    auto is_pointer_lang_type = [&](uint32_t reg) -> bool { return s_lang_type_is_pointerish(lir_func, reg); };

    for (size_t r = 0; !scalar_registers && r <= max_reg + 10; ++r) {
        reg_slots[r] = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), context_->getIntegerType(64));
        bool is_proven_scalar = (pointer_assigned_regs.count(r) == 0) && !is_pointer_lang_type(r);
        if (is_proven_scalar) {
            reg_slots[r]->setName("scalar_slot_r" + std::to_string(r));
        } else {
            reg_slots[r]->setName("slot_r" + std::to_string(r));
        }
        builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), reg_slots[r]);
    }

    auto entry_alloc = [&](ir::Type* type = nullptr, ir::Value* size = nullptr) -> ir::Instruction* {
        auto saved_ip = builder_->getInsertPoint();
        auto& instrs = entry_bb->getInstructions();
        if (!instrs.empty() && instrs.back()->getOpcode() <= ir::Instruction::Hlt) {
            builder_->setInsertPoint(entry_bb, std::prev(instrs.end()));
        } else {
            builder_->setInsertPoint(entry_bb);
        }
        if (!size) size = context_->getConstantInt(context_->getIntegerType(64), 8);
        auto* inst = builder_->createAlloc(size, type ? type : context_->getIntegerType(64));
        if (saved_ip) builder_->setInsertPoint(saved_ip);
        return inst;
    };

    // Canonical element spill slots for loop-variant virtual tuples. Each
    // pseudo register gets an entry-block slot; definitions store element
    // values and uses reload them, preserving values across back-edges.
    for (const auto& [cr, preds] : vt_info.canon_regs) {
        const auto& cdoms = vt_info.canon_domains[cr];
        for (size_t j = 0; j < preds.size(); ++j) {
            auto* slot = entry_alloc(nullptr,
                context_->getConstantInt(context_->getIntegerType(64), 8));
            slot->setName("vt_slot_r" + std::to_string(cr) + "_e" + std::to_string(j));
            // Tagged-domain record fields hold nil until first written, like
            // a real frame's fields array; scalar domains read as zero.
            ir::Value* init_v = (j < cdoms.size() && cdoms[j] == VDOM_TAGGED)
                ? builder_->createExternCall("lymar_aot_nil", {}, context_->getIntegerType(64))
                : static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64), 0));
            builder_->createStore(init_v, slot);
            reg_slots[preds[j]] = slot;
            reg_types[preds[j]] = (j < cdoms.size() && cdoms[j] == VDOM_FLOAT)
                ? LIR::Type::F64 : LIR::Type::I64;
        }
    }

    // Initialize registers from function parameters. In `.direct` mode the
    // ir::Function parameters are flattened: scalar params map back to their
    // original LIR register and tuple elements accumulate into vtuples.
    ir::Value* sret_buf_val = nullptr;
    {
        size_t param_idx = 0;
        size_t np = main_fn->getParameters().size();
        for (const auto& param : main_fn->getParameters()) {
            uint32_t orig = static_cast<uint32_t>(param_idx);
            int32_t elem = -1;
            int32_t domain = VDOM_INT;
            if (dctx && param_idx < dctx->params.size()) {
                orig = dctx->params[param_idx].orig;
                elem = dctx->params[param_idx].elem;
                domain = dctx->params[param_idx].domain;
            }
            if (elem == -2) {
                // INOUT record param: `param` is the caller's field buffer.
                // Elements read/write it in place so mutations propagate.
                auto dit = dctx->inout_domains.find(orig);
                if (dit != dctx->inout_domains.end()) {
                    for (size_t j = 0; j < dit->second.size(); ++j) {
                        VTupleElem ve;
                        ve.mem_base = param.get();
                        ve.mem_idx = static_cast<uint32_t>(j);
                        ve.domain = dit->second[j];
                        ve.has = true;
                        vtuples[orig].push_back(ve);
                    }
                    vframes.insert(orig);
                }
                param_idx++;
                continue;
            }
            if (elem >= 0) {
                VTupleElem ve;
                ve.direct_v = param.get();
                ve.domain = domain;
                ve.has = true;
                vtuples[orig].push_back(ve);
                // A flattened record param is still a virtual frame.
                auto lt = lir_func.register_language_types.find(orig);
                if (lt != lir_func.register_language_types.end() && lt->second &&
                    lt->second->tag == ::TypeTag::Frame)
                    vframes.insert(orig);
                param_idx++;
                continue;
            }
            if (dctx && dctx->sret_return && param_idx + 1 == np) {
                sret_buf_val = param.get();
                param_idx++;
                continue;
            }
            if (!scalar_registers && reg_slots.count(orig)) builder_->createStore(param.get(), reg_slots[orig]);
            regs[orig] = param.get();
            register_definitions[orig] = nullptr;
            if (param->getType() && (param->getType()->isDoubleTy() || param->getType()->isFloatTy())) {
                reg_types[orig] = LIR::Type::F64;
            } else {
                auto it = lir_func.register_types.find(orig);
                if (it != lir_func.register_types.end()) {
                    reg_types[orig] = it->second;
                }
            }
            param_idx++;
        }
    }

    // A hoisted element-buffer pointer is only sound when nothing in the
    // function can mutate the list behind the compiler's back. Ownership
    // moves prevent local aliasing, but calls, FFI, indirect dispatch, raw
    // memory writes, and cross-task handoff can all reach the list without
    // a ListAppend/ListSet on this register (e.g. `iter (x in xs) { bump(xs) }`
    // reallocs mid-loop). When any such op exists, skip the entry-block
    // hoist; per-access loads still see the current header.
    bool may_mutate_lists = false;
    for (const auto& inst : lir_func.instructions) {
        switch (inst.op) {
            case LIR::LIR_Op::Call: case LIR::LIR_Op::CallVoid:
            case LIR::LIR_Op::CallIndirect: case LIR::LIR_Op::CallBuiltin:
            case LIR::LIR_Op::CallVariadic:
            case LIR::LIR_Op::ForeignCall: case LIR::LIR_Op::ForeignCallDirect:
            // ListAppend can realloc the element buffer (words[1]); a cached
            // entry-block data pointer would go stale on the next iteration.
            case LIR::LIR_Op::ListAppend:
            case LIR::LIR_Op::FrameCallMethod: case LIR::LIR_Op::TraitCallMethod:
            case LIR::LIR_Op::ResourceCall:
            case LIR::LIR_Op::MemoryStore: case LIR::LIR_Op::MemoryCopy:
            case LIR::LIR_Op::MemoryFill: case LIR::LIR_Op::MemoryResize:
            case LIR::LIR_Op::ChannelPush: case LIR::LIR_Op::ChannelSend:
            case LIR::LIR_Op::ChannelOffer: case LIR::LIR_Op::ParallelInit:
            case LIR::LIR_Op::ParallelSync: case LIR::LIR_Op::SchedulerRun:
            case LIR::LIR_Op::SchedulerTick:
                may_mutate_lists = true;
                break;
            default: break;
        }
        if (may_mutate_lists) break;
    }

    std::unordered_map<uint32_t, ir::Value*> hoisted_data_ptrs;
    size_t num_params = main_fn->getParameters().size();
    for (size_t p = 0; p < num_params && !may_mutate_lists && !dctx; ++p) {
        if (is_typed_primitive_list(p) && !reassigned_parameters.count(p)) {
            ir::Value* p_val = regs[p];
            ir::Value* unboxed = builder_->createAnd(p_val, context_->getConstantInt(context_->getIntegerType(64), ~7ULL));
            ir::Instruction* dptr = builder_->createLoadl(builder_->createAdd(unboxed, context_->getConstantInt(context_->getIntegerType(64), 8)));
            dptr->setName("hoisted_data_ptr_r" + std::to_string(p));
            hoisted_data_ptrs[p] = dptr;
        }
    }

    if (main_fn->getName() == "main" && lir_func.name == "__top_level_wrapper__") {
        auto& registry = LIR::FunctionRegistry::getInstance();
        for (const auto& func_name : registry.getFunctionNames()) {
            if (func_name.ends_with(".__init__")) {
                // Tree-shaken pure inits are not emitted; only call the
                // ones reachability kept (needed modules + impure inits).
                if (reachable_funcs_.find(func_name) == reachable_funcs_.end()) continue;
                ir::Function* init_fn = current_module_->getFunction(func_name);
                if (!init_fn) {
                    init_fn = builder_->createFunction(func_name, context_->getVoidType(), {});
                }
                builder_->createCall(init_fn, {});
            }
        }
    }

    if (block_map.count(0)) {
        builder_->createJmp(block_map.at(0));
    }

    auto load_reg = [&](uint32_t r, LIR::Type t) -> ir::Value* {
        // A virtual tuple has no slot value; any read outside the dedicated
        // TupleGet/TupleSet/TupleLen/direct-call paths materializes it first.
        if (vtuples.count(r)) materialize_vtuple(r);
        // The stack slot is the authoritative, control-flow-correct home for a
        // register's value whenever one exists: every store writes the slot and
        // every read reloads it, so a value carried across a loop back-edge or a
        // CFG join (e.g. an outer accumulator mutated in a nested loop, or a
        // counter reassigned in a `for` body reached through a `continue`) is
        // always observed correctly. It also fixes reused virtual registers that
        // hold pointers to heap allocations (string literals): the cached SSA
        // value can be the copy_constant result of an EARLIER assignment to the
        // same vreg, so a later `print` would hand the runtime a stale (and
        // possibly collected) pointer. Registers with no slot are true
        // straight-line SSA temporaries (scalar-leaf mode, loop-free by
        // construction) and keep the cached-value fast path.
        if (reg_slots.count(r)) {
            // The slot representation is fixed by the register's class, not by
            // the most recent store's annotation: object-classified registers
            // always hold erased words (floats are boxed on store).
            const auto actual = (pointer_assigned_regs.count(r) || is_pointer_lang_type(r))
                ? LIR::Type::Ptr : (reg_types.count(r) ? reg_types[r] : t);
            auto* load = (actual == LIR::Type::F64 || actual == LIR::Type::F32)
                ? builder_->createLoadd(reg_slots[r]) : builder_->createLoadl(reg_slots[r]);
            load->setName("load_r" + std::to_string(r) + "_" + std::to_string(label_counter_++));
            return load;
        }
        // Use a dominating SSA value within its defining block. This also avoids
        // redundant store/load pairs for immutable parameters and straight-line
        // expressions. Mutable parameters need their slot at CFG joins/loops;
        // the original SSA argument does not reflect later assignments.
        if (regs.count(r) && register_definitions.count(r) &&
            ((!register_definitions[r] && !reassigned_parameters.count(r)) ||
             register_definitions[r] == builder_->getInsertPoint())) {
            return regs[r];
        }
        if (regs.count(r)) return regs[r];
        ir::Type* fty = lir_type_to_fyra_type(t);
        if (t == LIR::Type::F64 || t == LIR::Type::F32) {
            return context_->getConstantFP(context_->getDoubleType(), 0.0);
        }
        if (fty->isIntegerTy()) {
            return context_->getConstantInt(static_cast<ir::IntegerType*>(fty), 0);
        }
        return context_->getConstantInt(context_->getIntegerType(64), 0);
    };

    auto tag_word = [&](ir::Value* value, uint32_t reg = UINT32_MAX, LIR::Type type = LIR::Type::Void) -> ir::Value* {
        if (!value) return context_->getConstantInt(context_->getIntegerType(64), 0);
        if (value->getType()->isFloatingPoint()) {
            return builder_->createExternCall("lymar_aot_box_float", {value}, context_->getIntegerType(64));
        }
        if (value->getType() != context_->getIntegerType(64)) {
            value = builder_->createCast(value, context_->getIntegerType(64));
        }
        if (reg != UINT32_MAX && tagged_word_regs.count(reg)) {
            // Producer already emitted a tagged LmValue word; re-encoding
            // would double-tag (SMI -> foreign box or shifted SMI).
            return value;
        }
        if (reg != UINT32_MAX) {
            auto it = lir_func.register_language_types.find(reg);
            if (it != lir_func.register_language_types.end() && it->second) {
                auto tag = it->second->tag;
                if (tag == ::TypeTag::Bool) {
                    return builder_->createExternCall("lymar_aot_tag_bool", {value}, context_->getIntegerType(64));
                }
                if (tag == ::TypeTag::Nil) {
                    // VAL_NIL is self-describing in the tagged LmValue domain.
                    return context_->getConstantInt(context_->getIntegerType(64), VAL_NIL);
                }
                if (tag == ::TypeTag::Int || tag == ::TypeTag::Int8 || tag == ::TypeTag::Int16 ||
                    tag == ::TypeTag::Int32 || tag == ::TypeTag::Int64 ||
                    tag == ::TypeTag::UInt || tag == ::TypeTag::UInt8 || tag == ::TypeTag::UInt16 ||
                    tag == ::TypeTag::UInt32 || tag == ::TypeTag::UInt64) {
                    return builder_->createExternCall("lymar_aot_tag_int", {value}, context_->getIntegerType(64));
                }
                if (tag == ::TypeTag::Float32 || tag == ::TypeTag::Float64 ||
                    tag == ::TypeTag::Decimal2 || tag == ::TypeTag::Decimal4 || tag == ::TypeTag::Decimal6) {
                    return value;
                }
                if (tag == ::TypeTag::String || tag == ::TypeTag::List || tag == ::TypeTag::Frame ||
                    tag == ::TypeTag::Dict || tag == ::TypeTag::Tuple || tag == ::TypeTag::Trait ||
                    tag == ::TypeTag::TraitObject) {
                    return builder_->createExternCall("lymar_aot_tag_pointer", {value}, context_->getIntegerType(64));
                }
                if (tag == ::TypeTag::Any || tag == ::TypeTag::Union || tag == ::TypeTag::ErrorUnion ||
                    tag == ::TypeTag::Sum || tag == ::TypeTag::Function || tag == ::TypeTag::Closure ||
                    tag == ::TypeTag::Module || tag == ::TypeTag::Range || tag == ::TypeTag::Channel ||
                    tag == ::TypeTag::Int128 || tag == ::TypeTag::UInt128) {
                    // Erased words and boxed 128-bit integers already carry
                    // LmValue tags; re-encoding would double-tag them.
                    return value;
                }
            }
        }
        if (type == LIR::Type::Bool) {
            return builder_->createExternCall("lymar_aot_tag_bool", {value}, context_->getIntegerType(64));
        }
        if (type == LIR::Type::Ptr || (reg != UINT32_MAX && pointer_assigned_regs.count(reg))) {
            return builder_->createExternCall("lymar_aot_tag_pointer", {value}, context_->getIntegerType(64));
        }
        if (type == LIR::Type::I64 || type == LIR::Type::I32 || type == LIR::Type::I16 || type == LIR::Type::I8 ||
            type == LIR::Type::U64 || type == LIR::Type::U32 || type == LIR::Type::U16 || type == LIR::Type::U8) {
            return builder_->createExternCall("lymar_aot_tag_int", {value}, context_->getIntegerType(64));
        }
        if (reg != UINT32_MAX && !is_pointer_lang_type(reg)) {
            return builder_->createExternCall("lymar_aot_tag_int", {value}, context_->getIntegerType(64));
        }
        return value;
    };

    auto untag_word = [&](ir::Value* word, uint32_t dst_reg = UINT32_MAX, LIR::Type target_type = LIR::Type::Void) -> ir::Value* {
        if (!word) return word;
        if (dst_reg != UINT32_MAX) {
            auto it = lir_func.register_language_types.find(dst_reg);
            if (it != lir_func.register_language_types.end() && it->second) {
                auto tag = it->second->tag;
                if (tag == ::TypeTag::Bool) {
                    return builder_->createExternCall("lymar_aot_untag_bool", {word}, context_->getIntegerType(64));
                }
                if (tag == ::TypeTag::Int || tag == ::TypeTag::Int8 || tag == ::TypeTag::Int16 ||
                    tag == ::TypeTag::Int32 || tag == ::TypeTag::Int64 ||
                    tag == ::TypeTag::UInt || tag == ::TypeTag::UInt8 || tag == ::TypeTag::UInt16 ||
                    tag == ::TypeTag::UInt32 || tag == ::TypeTag::UInt64) {
                    return builder_->createExternCall("lymar_aot_untag_int", {word}, context_->getIntegerType(64));
                }
                if (tag == ::TypeTag::Float32 || tag == ::TypeTag::Float64 ||
                    tag == ::TypeTag::Decimal2 || tag == ::TypeTag::Decimal4 || tag == ::TypeTag::Decimal6) {
                    return builder_->createExternCall("lymar_aot_to_float", {word}, context_->getDoubleType());
                }
                if (tag == ::TypeTag::String || tag == ::TypeTag::List || tag == ::TypeTag::Frame ||
                    tag == ::TypeTag::Dict || tag == ::TypeTag::Tuple || tag == ::TypeTag::Trait ||
                    tag == ::TypeTag::TraitObject) {
                    return builder_->createExternCall("lymar_aot_untag_ptr", {word}, context_->getIntegerType(64));
                }
                if (tag == ::TypeTag::Any || tag == ::TypeTag::Union || tag == ::TypeTag::ErrorUnion ||
                    tag == ::TypeTag::Sum || tag == ::TypeTag::Function || tag == ::TypeTag::Closure ||
                    tag == ::TypeTag::Module || tag == ::TypeTag::Range || tag == ::TypeTag::Channel) {
                    return word;
                }
            }
        }
        if (target_type == LIR::Type::Bool) {
            return builder_->createExternCall("lymar_aot_untag_bool", {word}, context_->getIntegerType(64));
        }
        if (target_type == LIR::Type::F32 || target_type == LIR::Type::F64) {
            return builder_->createExternCall("lymar_aot_to_float", {word}, context_->getDoubleType());
        }
        if (target_type == LIR::Type::Ptr) {
            return builder_->createExternCall("lymar_aot_untag_ptr", {word}, context_->getIntegerType(64));
        }
        if (target_type == LIR::Type::I64 || target_type == LIR::Type::I32 || target_type == LIR::Type::I16 || target_type == LIR::Type::I8 ||
            target_type == LIR::Type::U64 || target_type == LIR::Type::U32 || target_type == LIR::Type::U16 || target_type == LIR::Type::U8) {
            return builder_->createExternCall("lymar_aot_untag_int", {word}, context_->getIntegerType(64));
        }
        if (dst_reg != UINT32_MAX && !is_pointer_lang_type(dst_reg) && pointer_assigned_regs.count(dst_reg) == 0) {
            return builder_->createExternCall("lymar_aot_untag_int", {word}, context_->getIntegerType(64));
        }
        return word;
    };

    auto erased_word = [&](ir::Value* value) -> ir::Value* {
        return tag_word(value);
    };

    auto store_reg = [&](uint32_t r, ir::Value* v, LIR::Type t, bool preserve_kind = false) {
        // Redefining a register kills its virtual tuple; the old value is dead.
        if (vtuples.count(r)) { vtuples.erase(r); vframes.erase(r); }
        // Object-classified registers have a uniform erased-word slot. A float
        // local that ever joins an erased value (frame field, `any`, boxed
        // arithmetic) must store a boxed word on every path: otherwise a loop
        // back-edge can leave raw double bits in the slot where an earlier
        // Loadl+to_float consumer reads them as a box pointer.
        if (v && (t == LIR::Type::F64 || t == LIR::Type::F32) &&
            (pointer_assigned_regs.count(r) || is_pointer_lang_type(r))) {
            if (v->getType()->isFloatingPoint())
                v = builder_->createExternCall("lymar_aot_box_float", {v}, context_->getIntegerType(64));
            t = LIR::Type::Ptr;
        }
        if (v && t == LIR::Type::Ptr) v = erased_word(v);
        if (v && (t == LIR::Type::F64 || t == LIR::Type::F32) && !v->getType()->isFloatingPoint())
            v = builder_->createExternCall("lymar_aot_to_float", {v}, context_->getDoubleType());
        if (v && t == LIR::Type::Bool && !preserve_kind) {
            if (v->getType() != context_->getIntegerType(64)) v = builder_->createCast(v, context_->getIntegerType(64));
            // Inlined lymar_aot_boolean (no external call or runtime mutex)
        }
        if (v && v->getType() && v->getType()->isInteger() && v->getType() != context_->getIntegerType(64)) {
            v = builder_->createCast(v, context_->getIntegerType(64));
        }
        if (v) {
            if (v->getName().empty() && !dynamic_cast<ir::Constant*>(v)) {
                v->setName("r" + std::to_string(r));
            }
            if (reg_slots.count(r)) {
                builder_->createStore(v, reg_slots[r]);
            }
        }
        regs[r] = v;
        register_definitions[r] = builder_->getInsertPoint();
        reg_types[r] = t;
    };

    // ---- Virtual tuple support -------------------------------------------
    // Tuple values whose elements stay in scalar slots/registers. Element
    // domains match the canonical post-untag representation: Float=f64,
    // Int/Bool=raw i64, Ptr=raw address, Tagged=tagged LmValue word.
    auto vdom_of_reg = [&](uint32_t r, LIR::Type t) -> int {
        auto lt = lir_func.register_language_types.find(r);
        if (lt != lir_func.register_language_types.end() && lt->second)
            return vdom_of_type(lt->second, t);
        return vdom_of_type(TypePtr(), t);
    };
    auto velem_value = [&](const VTupleElem& e) -> ir::Value* {
        if (e.direct_v) return e.direct_v;
        if (e.mem_base) {
            // INOUT record element: raw domain value inside the caller's
            // field buffer at mem_base + mem_idx * 8.
            auto* i64ty = context_->getIntegerType(64);
            ir::Value* addr = builder_->createAdd(e.mem_base,
                context_->getConstantInt(i64ty, static_cast<long long>(e.mem_idx * 8)));
            return (e.domain == VDOM_FLOAT)
                ? static_cast<ir::Value*>(builder_->createLoadd(addr))
                : static_cast<ir::Value*>(builder_->createLoadl(addr));
        }
        // load_reg already selects Loadd for float-typed registers, so the
        // raw f64 domain value comes back directly.
        return load_reg(e.src_reg, e.src_type);
    };
    // Canonical spill-slot helpers for loop-variant virtual tuples.
    auto canon_elems = [&](uint32_t r) -> std::vector<VTupleElem> {
        std::vector<VTupleElem> es;
        auto ri = vt_info.canon_regs.find(r);
        auto di = vt_info.canon_domains.find(r);
        if (ri == vt_info.canon_regs.end() || di == vt_info.canon_domains.end()) return es;
        for (size_t j = 0; j < ri->second.size(); ++j) {
            VTupleElem e;
            e.src_reg = ri->second[j];
            e.domain = (j < di->second.size()) ? di->second[j] : VDOM_INT;
            e.src_type = (e.domain == VDOM_FLOAT) ? LIR::Type::F64 : LIR::Type::I64;
            e.has = true;
            e.canon_elem = true;
            es.push_back(e);
        }
        return es;
    };
    auto canon_slot_for = [&](uint32_t r, size_t j) -> ir::Instruction* {
        return reg_slots[vt_info.canon_regs.at(r)[j]];
    };
    auto canon_store_val = [&](uint32_t r, size_t j, ir::Value* v) {
        if (!v) return;
        int dom = vt_info.canon_domains.at(r)[j];
        auto* i64ty = context_->getIntegerType(64);
        if (dom == VDOM_FLOAT) {
            if (!v->getType()->isFloatingPoint())
                v = builder_->createExternCall("lymar_aot_to_float", {v}, context_->getDoubleType());
        } else if (v->getType() != i64ty) {
            v = builder_->createCast(v, i64ty);
        }
        auto* st = builder_->createStore(v, canon_slot_for(r, j));
        // FLOAT/INT/BOOL element slots can never hold a managed heap word;
        // naming them scalar lets region lowering skip the per-store edge
        // call, which would otherwise pin the slot to memory.
        if (dom == VDOM_FLOAT || dom == VDOM_INT || dom == VDOM_BOOL)
            st->setName("scalar_store_vt");
    };
    // Store a raw domain value into an element's backing location: canonical
    // pseudo-register slot or INOUT buffer slot. Used by FrameSetField so
    // writes through any alias land in the shared backing store.
    auto canon_store_elem = [&](const VTupleElem& e, ir::Value* v) {
        if (!v) return;
        int dom = e.domain;
        auto* i64ty = context_->getIntegerType(64);
        if (dom == VDOM_FLOAT) {
            if (!v->getType()->isFloatingPoint())
                v = builder_->createExternCall("lymar_aot_to_float", {v}, context_->getDoubleType());
        } else if (v->getType() != i64ty) {
            v = builder_->createCast(v, i64ty);
        }
        ir::Instruction* st = nullptr;
        if (e.canon_elem) {
            st = builder_->createStore(v, reg_slots[e.src_reg]);
        } else if (e.mem_base) {
            ir::Value* addr = builder_->createAdd(e.mem_base,
                context_->getConstantInt(i64ty, static_cast<long long>(e.mem_idx * 8)));
            st = builder_->createStore(v, addr);
        } else {
            return;
        }
        if (dom == VDOM_FLOAT || dom == VDOM_INT || dom == VDOM_BOOL)
            st->setName("scalar_store_vt");
    };
    // Capture the current element values of `src_elems` into r's canonical
    // slots, then re-point r's vtuple at the pseudo registers.
    auto canon_capture = [&](uint32_t r, const std::vector<VTupleElem>& src_elems) {
        size_t n = std::min(src_elems.size(), vt_info.canon_regs.at(r).size());
        for (size_t j = 0; j < n; ++j)
            canon_store_val(r, j, velem_value(src_elems[j]));
        vtuples[r] = canon_elems(r);
    };
    materialize_vtuple = [&](uint32_t r) {
        auto vit = vtuples.find(r);
        if (vit == vtuples.end()) return;
        auto elems = std::move(vit->second);
        vtuples.erase(r);
        const bool was_frame = vframes.count(r) != 0;
        vframes.erase(r);
        auto* i64ty = context_->getIntegerType(64);
        if (was_frame) {
            // Materialize a real LmFrame: same layout NewFrame emits —
            // header/type id, name, fields array of tagged LmValue words.
            std::string fname;
            auto lt = lir_func.register_language_types.find(r);
            if (lt != lir_func.register_language_types.end() && lt->second &&
                lt->second->tag == ::TypeTag::Frame) {
                if (auto* ft = std::get_if<FrameType>(&lt->second->extra)) fname = ft->name;
            }
            if (fname.empty()) fname = "Frame";
            ir::Value* frame_ptr = builder_->createExternCall("memory.alloc",
                {context_->getConstantInt(i64ty, 40)}, lir_type_to_fyra_type(LIR::Type::Ptr));
            builder_->createStore(context_->getConstantInt(i64ty, 15), frame_ptr);
            ir::GlobalVariable* gv_name = FyraBuiltinFunctions::get_or_create_global_str(
                current_module_.get(), builder_.get(),
                "fr_name_" + fname + "_" + std::to_string(label_counter_++), fname);
            ir::Value* name_addr = builder_->createAdd(frame_ptr,
                context_->getConstantInt(i64ty, 8));
            auto* name_copy = builder_->createExternCall("lymar_aot_copy_constant",
                {gv_name, context_->getConstantInt(i64ty, 24 + fname.size() + 1)}, i64ty);
            builder_->createStore(name_copy, name_addr);
            uint32_t nfields = static_cast<uint32_t>(elems.size());
            uint32_t field_bytes = (nfields > 0 ? nfields : 2) * 8;
            ir::Value* fields_array = builder_->createExternCall("memory.alloc",
                {context_->getConstantInt(i64ty, field_bytes)}, lir_type_to_fyra_type(LIR::Type::Ptr));
            auto* initial_nil = builder_->createExternCall("lymar_aot_nil", {}, i64ty);
            for (uint32_t fi = 0; fi < (nfields > 0 ? nfields : 2); ++fi) {
                ir::Value* f_addr = builder_->createAdd(fields_array,
                    context_->getConstantInt(i64ty, fi * 8));
                builder_->createStore(initial_nil, f_addr);
            }
            ir::Value* fields_ptr_addr = builder_->createAdd(frame_ptr,
                context_->getConstantInt(i64ty, 16));
            builder_->createStore(fields_array, fields_ptr_addr);
            builder_->createExternCall("lymar_aot_edge", {fields_ptr_addr, fields_array},
                context_->getVoidType());
            ir::Value* cnt_addr = builder_->createAdd(frame_ptr,
                context_->getConstantInt(i64ty, 24));
            builder_->createStore(context_->getConstantInt(i64ty, nfields), cnt_addr);
            for (size_t j = 0; j < elems.size(); ++j) {
                const auto& e = elems[j];
                ir::Value* v = e.has ? velem_value(e)
                    : (e.domain == VDOM_FLOAT)
                        ? static_cast<ir::Value*>(context_->getConstantFP(context_->getDoubleType(), 0.0))
                        : static_cast<ir::Value*>(context_->getConstantInt(i64ty, 0));
                // Unset record fields hold nil in a real frame — preserve
                // that exactly so erased reads (`== nil`) stay equivalent.
                ir::Value* tagged = !e.has
                    ? builder_->createExternCall("lymar_aot_nil", {}, i64ty)
                    : [&]() -> ir::Value* {
                        switch (e.domain) {
                            case VDOM_FLOAT: return tag_word(v);
                            case VDOM_INT:
                                return builder_->createExternCall("lymar_aot_tag_int", {v}, i64ty);
                            case VDOM_BOOL:
                                return builder_->createExternCall("lymar_aot_tag_bool", {v}, i64ty);
                            case VDOM_PTR:
                                return builder_->createExternCall("lymar_aot_tag_pointer", {v}, i64ty);
                            default: return v; // VDOM_TAGGED: already a word
                        }
                    }();
                builder_->createExternCall("lymar_aot_frame_set_field",
                    {frame_ptr, context_->getConstantInt(i64ty, static_cast<long long>(j)), tagged},
                    context_->getVoidType());
            }
            store_reg(r, frame_ptr, LIR::Type::Ptr);
            return;
        }
        used_builtins_.insert("lm_tuple_new");
        ir::Function* tfn = current_module_->getFunction("lm_tuple_new");
        if (!tfn) tfn = builder_->createFunction("lm_tuple_new", i64ty, {i64ty});
        ir::Value* tuple = builder_->createCall(tfn,
            {context_->getConstantInt(i64ty, static_cast<long long>(elems.size()))}, i64ty);
        used_builtins_.insert("lm_tuple_set");
        ir::Function* sfn = current_module_->getFunction("lm_tuple_set");
        if (!sfn) sfn = builder_->createFunction("lm_tuple_set", context_->getVoidType(), {i64ty, i64ty, i64ty});
        for (size_t j = 0; j < elems.size(); ++j) {
            const auto& e = elems[j];
            ir::Value* v;
            if (e.has) {
                v = velem_value(e);
            } else {
                v = (e.domain == VDOM_FLOAT)
                    ? static_cast<ir::Value*>(context_->getConstantFP(context_->getDoubleType(), 0.0))
                    : static_cast<ir::Value*>(context_->getConstantInt(i64ty, 0));
            }
            ir::Value* tagged;
            if (e.src_reg != UINT32_MAX && !e.canon_elem) {
                // Replay exactly what the real TupleSet emits: tag_word with
                // the source register's language type.
                tagged = tag_word(v, e.src_reg, e.src_type);
            } else {
                switch (e.domain) {
                    case VDOM_FLOAT:
                        tagged = tag_word(v);
                        break;
                    case VDOM_INT:
                        tagged = builder_->createExternCall("lymar_aot_tag_int", {v}, i64ty);
                        break;
                    case VDOM_BOOL:
                        tagged = builder_->createExternCall("lymar_aot_tag_bool", {v}, i64ty);
                        break;
                    case VDOM_PTR:
                        tagged = builder_->createExternCall("lymar_aot_tag_pointer", {v}, i64ty);
                        break;
                    default:
                        tagged = v; // VDOM_TAGGED is already an LmValue word
                        break;
                }
            }
            builder_->createCall(sfn, {tuple, context_->getConstantInt(i64ty, static_cast<long long>(j)), tagged});
        }
        store_reg(r, tuple, LIR::Type::Ptr);
    };

    // Constant-int register values (tuple indices) and per-register def counts
    // (virtual-tuple element stability: a source register written more than
    // once cannot be reloaded at an arbitrary later use point).
    std::unordered_map<uint32_t, int64_t> const_ints;
    std::unordered_map<uint32_t, uint32_t> def_counts;
    for (const auto& in : lir_func.instructions) {
        if (in.dst != UINT32_MAX) def_counts[in.dst]++;
        if (in.op == LIR::LIR_Op::LoadConst && !IS_PTR(in.const_val) && IS_INT(in.const_val) &&
            (((in.const_val >> 3) << 3) | TAG_INT) == in.const_val) {
            const_ints[in.dst] = UNBOX_INT(in.const_val);
        }
    }
    auto const_index_of = [&](uint32_t r) -> int64_t {
        if (const_ints.count(r)) return const_ints[r];
        if (reg_int_values.count(r)) return reg_int_values[r];
        return -1;
    };
    // Element sources must be write-once SSA-ish registers: params flagged
    // reassigned and multiply-defined regs are rejected so a later TupleGet
    // never observes a overwritten slot.
    auto elem_src_stable = [&](uint32_t r) -> bool {
        if (r == UINT32_MAX) return false;
        if (reassigned_parameters.count(r)) return false;
        auto dc = def_counts.find(r);
        return dc == def_counts.end() || dc->second <= 1;
    };

    // lymar_aot_numeric_binary / lymar_aot_bitwise return tagged LmValue words
    // (SMI or heap box). Erased destinations keep the tagged word object-
    // classified; scalar destinations must untag exactly once or the SMI
    // encoding leaks into raw-int consumers (and gets tagged a second time).
    auto store_arith_word = [&](const LIR::LIR_Inst& inst, ir::Value* tagged) {
        if (lang_type_holds_tagged_word(inst.dst)) {
            store_reg(inst.dst, tagged, LIR::Type::Ptr, true);
        } else {
            store_reg(inst.dst, untag_word(tagged, inst.dst, inst.result_type), inst.result_type);
        }
    };

    // CallIndirect dispatch contract: the result slot always holds a tagged
    // LmValue word. A callee whose declared return type is scalar (int family,
    // bool, float) hands back a raw domain value, so each matched target's
    // result must be re-tagged per that callee's own return type. Callees with
    // erased return types already produce tagged words (Return lowering) and
    // pass through unchanged; unknown/untyped callees are assumed tagged.
    auto tag_indirect_result = [&](ir::Value* value, const std::string& fname) -> ir::Value* {
        if (!value) return value;
        auto* lf = LIR::FunctionRegistry::getInstance().getFunction(fname);
        if (!lf || !lf->return_language_type) return erased_word(value);
        switch (lf->return_language_type->tag) {
            case ::TypeTag::Bool:
                return builder_->createExternCall("lymar_aot_tag_bool", {value}, context_->getIntegerType(64));
            case ::TypeTag::Int: case ::TypeTag::Int8: case ::TypeTag::Int16:
            case ::TypeTag::Int32: case ::TypeTag::Int64:
            case ::TypeTag::UInt: case ::TypeTag::UInt8: case ::TypeTag::UInt16:
            case ::TypeTag::UInt32: case ::TypeTag::UInt64:
                if (value->getType()->isFloatingPoint())
                    return builder_->createExternCall("lymar_aot_box_float", {value}, context_->getIntegerType(64));
                return builder_->createExternCall("lymar_aot_tag_int", {value}, context_->getIntegerType(64));
            case ::TypeTag::Float32: case ::TypeTag::Float64:
                if (value->getType()->isFloatingPoint())
                    return builder_->createExternCall("lymar_aot_box_float", {value}, context_->getIntegerType(64));
                return value;
            default:
                return erased_word(value);
        }
    };

    auto load_float_reg = [&](uint32_t r, LIR::Type t) -> ir::Value* {
        // Cached SSA values may be erased even when the source register is
        // numerically typed. Convert the actual value, not just its annotation.
        ir::Value* v = load_reg(r, t);
        if (v && !v->getType()->isFloatingPoint()) {
            return builder_->createExternCall("lymar_aot_to_float", {v}, context_->getDoubleType());
        }
        return v;
    };

    auto erased_arithmetic = [&](const LIR::LIR_Inst& instruction) {
        auto erased=[&](uint32_t reg,LIR::Type type) {
            if(reg_types.count(reg)) type=reg_types.at(reg);
            if(type==LIR::Type::Ptr || type==LIR::Type::U64) return true;
            // i128/u128 values are always boxed words (or raw words carrying a
            // dynamic kind) -- their ABI type collapses to I64, so the LIR type
            // alone cannot tell them apart from plain integers.
            auto lt=lir_func.register_language_types.find(reg);
            if(lt!=lir_func.register_language_types.end() && lt->second &&
               (lt->second->tag==::TypeTag::Int128 || lt->second->tag==::TypeTag::UInt128)) return true;
            return false;
        };
        return erased(instruction.a,instruction.type_a) || erased(instruction.b,instruction.type_b);
    };
    // Bitwise/shift lowering routes to lymar_aot_bitwise for erased words
    // (boxed i128/u128, `any`, pointer-classified results). Plain u64 stays
    // native: its raw-word form already matches the hardware ops.
    auto bitwise_erased = [&](const LIR::LIR_Inst& instruction) {
        auto operand_erased=[&](uint32_t reg,LIR::Type type) {
            if(reg==UINT32_MAX) return false;
            if(reg_types.count(reg) && reg_types[reg]==LIR::Type::Ptr) return true;
            if(type==LIR::Type::Ptr) return true;
            auto lt=lir_func.register_language_types.find(reg);
            if(lt!=lir_func.register_language_types.end() && lt->second &&
               (lt->second->tag==::TypeTag::Int128 || lt->second->tag==::TypeTag::UInt128)) return true;
            return false;
        };
        return operand_erased(instruction.a,instruction.type_a) ||
               operand_erased(instruction.b,instruction.type_b) ||
               operand_erased(instruction.dst,LIR::Type::I64);
    };
    auto store_float_reg = [&](uint32_t r, ir::Value* fval) {
        store_reg(r, fval, LIR::Type::F64);
    };

    auto lower_runtime_builtin = [&](const std::string& name, const std::vector<ir::Value*>& args) -> ir::Value* {
        auto* zero = context_->getConstantInt(context_->getIntegerType(64), 0);
        if ((name == "clock" || name == "time.clock") && args.empty()) {
            auto* ms = builder_->createExternCall("time.monotonic", {}, context_->getIntegerType(64));
            auto* fms = builder_->createSltof(ms, context_->getDoubleType());
            return builder_->createFDiv(fms, context_->getConstantFP(context_->getDoubleType(), 1000.0));
        }
        if (name == "time" && args.empty())
            return builder_->createExternCall("time.now", {}, context_->getIntegerType(64));
        if (name == "_builtin_string_hash_bytes" && args.size() == 1)
            return builder_->createExternCall("lymar_aot_string_hash", {erased_word(args[0])},
                context_->getIntegerType(64));
        if (name == "_builtin_list_slice" && args.size() == 3)
            return builder_->createExternCall("lymar_aot_list_slice",
                {erased_word(args[0]), erased_word(args[1]), erased_word(args[2])},
                context_->getIntegerType(64));
        // String slice/case/trim builtins: the emit_*_ir versions miscompile
        // under Fyra (alloc-slot + loop shapes), so they lower to runtime
        // calls that allocate through the tracked AOT heap instead.
        auto leaf = name.substr(name.find_last_of('.') == std::string::npos ? 0 : name.find_last_of('.') + 1);
        if ((leaf == "_builtin_substring" || leaf == "substring") && args.size() >= 3)
            return builder_->createExternCall("lymar_aot_substring",
                {erased_word(args[0]), erased_word(args[1]), erased_word(args[2])},
                context_->getIntegerType(64));
        if ((leaf == "_builtin_string_to_lower" || leaf == "to_lower") && args.size() >= 1)
            return builder_->createExternCall("lymar_aot_string_case",
                {erased_word(args[0]), zero}, context_->getIntegerType(64));
        if ((leaf == "_builtin_string_to_upper" || leaf == "to_upper") && args.size() >= 1)
            return builder_->createExternCall("lymar_aot_string_case",
                {erased_word(args[0]), context_->getConstantInt(context_->getIntegerType(64), 1)},
                context_->getIntegerType(64));
        if ((leaf == "_builtin_string_trim" || leaf == "trim") && args.size() >= 1)
            return builder_->createExternCall("lymar_aot_string_trim",
                {erased_word(args[0])}, context_->getIntegerType(64));
        // input(prompt?) — the VM builtin reads one stdin line. No IR lowering
        // exists; string literals named "input" also materialize callable
        // adapters that route here.
        if (name == "input" || leaf == "_builtin_input")
            return builder_->createExternCall("lymar_aot_input",
                {args.empty() ? zero : erased_word(args[0])}, context_->getIntegerType(64));
        return nullptr;
    };

    // GPU intrinsics/dispatch lower to lymar_aot_gpu_* runtime calls in
    // aot_ffi.cpp — the software-emulation oracle shared with the register
    // VM (ops/gpu.cpp). Thread-space builtins return real [x,y,z] lists;
    // gpu_dispatch resolves the task by name through the gpu_functions
    // registry populated by lymar_aot_gpu_register below. Returns true when
    // `name` is a gpu builtin (call emitted, result stored).
    auto lower_gpu_builtin = [&](const std::string& name, const std::vector<ir::Value*>& args,
                                 const LIR::LIR_Inst& inst) -> bool {
        static const std::unordered_map<std::string, const char*> gpu_rt = {
            {"gpu_thread_id",       "lymar_aot_gpu_thread_id"},
            {"gpu_local_id",        "lymar_aot_gpu_local_id"},
            {"gpu_group_id",        "lymar_aot_gpu_group_id"},
            {"gpu_num_groups",      "lymar_aot_gpu_num_groups"},
            {"gpu_sync",            "lymar_aot_gpu_sync"},
            {"gpu_set_mesh_counts", "lymar_aot_gpu_set_mesh_counts"},
            {"gpu_dispatch",        "lymar_aot_gpu_dispatch"},
        };
        auto git = gpu_rt.find(name);
        if (git == gpu_rt.end()) return false;
        std::vector<ir::Value*> gargs;
        for (auto* a : args) gargs.push_back(erased_word(a));
        ir::Value* gres = builder_->createExternCall(git->second, gargs,
            static_cast<ir::Type*>(context_->getIntegerType(64)));
        if (inst.dst != UINT32_MAX && gres->getType() &&
            gres->getType()->getTypeID() != ir::Type::VoidTyID) {
            store_reg(inst.dst, gres, inst.result_type);
        }
        return true;
    };

    bool terminated = false;
    // Region-pair elision: RegionEnter/RegionExit pairs whose enclosed
    // instructions are provably free of managed effects (no allocation, no
    // calls except to provably-pure `.direct` callees, no memory/global ops)
    // are skipped entirely — an empty region's enter/exit only mutates region
    // bookkeeping. Purity is computed interprocedurally over the LIR, with
    // each function judged under its OWN register classification and
    // virtual-tuple proof and under the same lowering mode its call sites
    // will use (`.direct` flattened ABI when eligible, boxed ABI otherwise).
    std::unordered_set<size_t> region_skip;
    // vt_safe is hoisted out of the analysis block: the RegionMove lowering
    // below skips its runtime call under exactly this proof.
    // vt_info (safe set, def indices, canonical slots) was computed before
    // parameter initialization; reuse it here for region purity analysis.
    const auto& vt_safe = vt_info.safe;
    {
        const auto& self_def_idx = vt_info.def_inst_idx;

        struct PureInfo {
            const LIR::LIR_Function* fn = nullptr;
            const DirectFnSig* sig = nullptr; // non-null ⇒ `.direct` lowering
            RegDomainSets doms;
            std::unordered_map<uint32_t, bool> vt;
            std::unordered_map<uint32_t, size_t> def_idx;
        };
        std::map<std::pair<const LIR::LIR_Function*, bool>, PureInfo> infos;
        auto info_for = [&](const LIR::LIR_Function* f, bool as_dir) -> PureInfo& {
            auto key = std::make_pair(f, as_dir);
            auto it = infos.find(key);
            if (it != infos.end()) return it->second;
            PureInfo pi;
            pi.fn = f;
            if (as_dir) {
                const DirectFnSig* s = direct_sig_for(f->name);
                pi.sig = s->eligible ? s : nullptr;
            }
            pi.doms = compute_reg_domain_sets(*f);
            auto vt2 = compute_vt_safe(*f, pi.sig);
            pi.vt = std::move(vt2.safe);
            pi.def_idx = std::move(vt2.def_inst_idx);
            return infos.emplace(key, std::move(pi)).first->second;
        };
        // Seed the caller's own context from the sets already computed for
        // this lowering (identical inputs, avoids duplicate analysis).
        {
            PureInfo self_pi;
            self_pi.fn = &lir_func;
            self_pi.sig = self_sig;
            self_pi.doms.pointer_assigned = pointer_assigned_regs;
            self_pi.doms.tagged_word = tagged_word_regs;
            self_pi.vt = vt_safe;
            self_pi.def_idx = self_def_idx;
            infos[std::make_pair(&lir_func, self_sig != nullptr)] = std::move(self_pi);
        }

        std::map<std::pair<const LIR::LIR_Function*, bool>, int> purity; // 1=pure,2=impure
        std::set<std::pair<const LIR::LIR_Function*, bool>> visiting;
        std::function<bool(const PureInfo&, const LIR::LIR_Inst&)> region_neutral =
        [&](const PureInfo& pi, const LIR::LIR_Inst& in) -> bool {
            const auto* fn = pi.fn;
            switch (in.op) {
                case LIR::LIR_Op::Nop: case LIR::LIR_Op::Label:
                case LIR::LIR_Op::Jump: case LIR::LIR_Op::JumpIf:
                case LIR::LIR_Op::JumpIfFalse: case LIR::LIR_Op::Return:
                case LIR::LIR_Op::Ret: case LIR::LIR_Op::Copy:
                case LIR::LIR_Op::Mov:
                case LIR::LIR_Op::IAdd_Unchecked: case LIR::LIR_Op::IXor_Unchecked:
                case LIR::LIR_Op::IAnd_Unchecked: case LIR::LIR_Op::IOr_Unchecked:
                case LIR::LIR_Op::Add: case LIR::LIR_Op::Sub: case LIR::LIR_Op::Mul:
                case LIR::LIR_Op::Div: case LIR::LIR_Op::Mod: case LIR::LIR_Op::Neg:
                case LIR::LIR_Op::And: case LIR::LIR_Op::Or: case LIR::LIR_Op::Xor:
                case LIR::LIR_Op::Shl: case LIR::LIR_Op::Shr:
                case LIR::LIR_Op::CmpEQ: case LIR::LIR_Op::CmpNEQ: case LIR::LIR_Op::CmpLT:
                case LIR::LIR_Op::CmpLE: case LIR::LIR_Op::CmpGT: case LIR::LIR_Op::CmpGE:
                case LIR::LIR_Op::Cast: case LIR::LIR_Op::LoadConst:
                case LIR::LIR_Op::Load:
                case LIR::LIR_Op::TupleCreate: case LIR::LIR_Op::TupleGet:
                case LIR::LIR_Op::TupleSet: case LIR::LIR_Op::TupleLen:
                case LIR::LIR_Op::RegionEnter: case LIR::LIR_Op::RegionExit:
                    return true;
                case LIR::LIR_Op::NewFrame:
                    // A proven-virtual record allocates nothing; a
                    // materialized frame is a heap object that needs the
                    // region it was created in.
                    return pi.vt.count(in.dst) && pi.vt.at(in.dst);
                case LIR::LIR_Op::FrameGetField:
                    // Virtual field reads are plain slot loads plus pure
                    // untag decodes — no allocation, region-neutral.
                    return pi.vt.count(in.a) && pi.vt.at(in.a);
                case LIR::LIR_Op::FrameSetField: {
                    // Virtual writes store raw domain values; only TAGGED
                    // fields can allocate (tag_word boxing), so scalar/PTR
                    // domains stay neutral.
                    if (!pi.vt.count(in.dst) || !pi.vt.at(in.dst)) return false;
                    if (in.b != UINT32_MAX && pi.vt.count(in.b) && pi.vt.at(in.b))
                        return false; // stored value materializes → alloc
                    auto lt = fn->register_language_types.find(in.dst);
                    if (lt == fn->register_language_types.end() || !lt->second ||
                        lt->second->tag != ::TypeTag::Frame) return false;
                    auto* ft = std::get_if<FrameType>(&lt->second->extra);
                    const FrameFieldInfo* info = ft ? frame_field_info(ft->name) : nullptr;
                    std::vector<int> scratch;
                    const std::vector<int>* fd = frame_flat_domains(info, scratch);
                    if (!fd || in.a >= fd->size()) return false;
                    int d = (*fd)[in.a];
                    return d == VDOM_INT || d == VDOM_FLOAT || d == VDOM_BOOL || d == VDOM_PTR;
                }
                case LIR::LIR_Op::RegionMove: {
                    // Neutral exactly when lowering emits nothing: the scalar
                    // gate below, or a source register whose tuple is
                    // guaranteed to stay virtual (no heap word exists).
                    LIR::Type mvt = in.type_a != LIR::Type::Void ? in.type_a : LIR::Type::I64;
                    if (mvt == LIR::Type::I64 || mvt == LIR::Type::Void) {
                        auto rt = fn->register_types.find(in.a);
                        if (rt != fn->register_types.end()) mvt = rt->second;
                    }
                    const bool mscalar =
                        (mvt == LIR::Type::F64 || mvt == LIR::Type::F32 || mvt == LIR::Type::Bool ||
                         mvt == LIR::Type::I8 || mvt == LIR::Type::U8 ||
                         mvt == LIR::Type::I16 || mvt == LIR::Type::U16 ||
                         mvt == LIR::Type::I32 || mvt == LIR::Type::U32 ||
                         mvt == LIR::Type::I64) &&
                        !pi.doms.pointer_assigned.count(in.a) &&
                        !s_lang_type_is_pointerish(*fn, in.a) &&
                        !pi.doms.tagged_word.count(in.a);
                    if (mscalar) return true;
                    auto di = pi.def_idx.find(in.a);
                    return di != pi.def_idx.end() && pi.vt.count(in.a) && pi.vt.at(in.a);
                }
                case LIR::LIR_Op::Call: case LIR::LIR_Op::CallVoid: {
                    std::string name = in.func_name;
                    if (name.empty() && in.const_val) {
                        if (IS_PTR(in.const_val)) {
                            ObjHeader* h = (ObjHeader*)UNBOX_PTR(in.const_val);
                            if (h->type_id == TYPE_STRING) {
                                name = ((LmStringHeader*)h)->data;
                            } else if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                                name = (char*)((LmBox*)h)->value.as_ptr;
                            }
                        }
                    }
                    if (name.empty()) return false;
                    auto* cf = LIR::FunctionRegistry::getInstance().getFunction(name);
                    if (!cf) return false;
                    // Mirror the lowering's `.direct` selection: eligible
                    // signature AND matching LIR arity take the flattened
                    // path; anything else lowers through the boxed ABI.
                    const DirectFnSig* csig = nullptr;
                    if (in.call_args.size() == cf->param_count) {
                        const DirectFnSig* s = direct_sig_for(name);
                        if (s->eligible) csig = s;
                    }
                    auto key = std::make_pair(cf, csig != nullptr);
                    auto pit = purity.find(key);
                    if (pit == purity.end()) {
                        if (visiting.count(key)) return false;
                        visiting.insert(key);
                        PureInfo& cpi = info_for(cf, csig != nullptr);
                        bool p = true;
                        for (const auto& ci : cf->instructions) {
                            if (!region_neutral(cpi, ci)) { p = false; break; }
                        }
                        visiting.erase(key);
                        purity[key] = p ? 1 : 2;
                        pit = purity.find(key);
                    }
                    return pit->second == 1;
                }
                default:
                    return false;
            }
        };
        PureInfo& self_pi = info_for(&lir_func, self_sig != nullptr);
        std::vector<size_t> rstack;
        for (size_t i = 0; i < lir_func.instructions.size(); ++i) {
            const auto& in = lir_func.instructions[i];
            if (in.op == LIR::LIR_Op::RegionEnter) { rstack.push_back(i); continue; }
            if (in.op != LIR::LIR_Op::RegionExit || rstack.empty()) continue;
            size_t enter_idx = rstack.back(); rstack.pop_back();
            bool clean = true;
            for (size_t j = enter_idx + 1; j < i; ++j) {
                if (!region_neutral(self_pi, lir_func.instructions[j])) {
                    if (std::getenv("LYMAR_DEBUG_REGIONS"))
                        std::cerr << "[REGION] " << lir_func.name << " impure op " << (int)lir_func.instructions[j].op
                                  << " dst=" << lir_func.instructions[j].dst << " a=" << lir_func.instructions[j].a
                                  << " b=" << lir_func.instructions[j].b << " fn=" << lir_func.instructions[j].func_name << "\n";
                    clean = false; break;
                }
            }
            if (clean) { region_skip.insert(enter_idx); region_skip.insert(i); }
        }
    }

    for (size_t i = 0; i < lir_func.instructions.size(); ++i) {
        const auto& inst = lir_func.instructions[i];

        if (region_skip.count(i)) continue;

        if (block_map.count(i)) {
            if (!terminated && builder_->getInsertPoint() && i > 0 && builder_->getInsertPoint() != block_map.at(i)) {
                builder_->createJmp(block_map.at(i));
            }
            builder_->setInsertPoint(block_map.at(i));
            terminated = false;
        }

        if (inst.op == LIR::LIR_Op::Label) {
            continue;
        }

        if (terminated) continue;

        switch (inst.op) {
            case LIR::LIR_Op::RefCreate:
            case LIR::LIR_Op::RefResolve: {
                auto name = inst.op == LIR::LIR_Op::RefCreate ? "lymar_aot_ref_create" : "lymar_aot_ref_resolve";
                auto value = builder_->createExternCall(name, {load_reg(inst.a, inst.type_a),
                    context_->getConstantInt(context_->getIntegerType(64), inst.imm)}, context_->getIntegerType(64));
                store_reg(inst.dst, value, inst.result_type);
                break;
            }
            case LIR::LIR_Op::RefMove: {
                auto value = builder_->createExternCall("lymar_aot_ref_move", {load_reg(inst.a, inst.type_a),
                    context_->getConstantInt(context_->getIntegerType(64), inst.imm), get_caller_region()}, context_->getIntegerType(64));
                store_reg(inst.dst, value, inst.result_type); break;
            }
            case LIR::LIR_Op::RefRelease:
            case LIR::LIR_Op::OwnershipConsume:
                builder_->createExternCall(inst.op == LIR::LIR_Op::RefRelease ? (inst.imm & Memory::ReferenceNullable ? "lymar_aot_ref_release_nullable" : "lymar_aot_ref_release") : "lymar_aot_consume",
                    {load_reg(inst.a, inst.type_a)}, nullptr); break;
            case LIR::LIR_Op::RegionEnter:
            case LIR::LIR_Op::RegionExit:
                builder_->createExternCall(inst.op == LIR::LIR_Op::RegionEnter ? "lymar_aot_region_enter" : "lymar_aot_region_exit",
                    {context_->getConstantInt(context_->getIntegerType(64), inst.imm)}, nullptr);
                break;
            case LIR::LIR_Op::RegionMove: {
                // Skip only under the vt_safe proof: the tuple is guaranteed
                // to NEVER materialize, so no heap word exists to promote.
                // A merely-currently-virtual tuple may materialize later
                // inside this region; skipping the move would then leave the
                // heap object in a region that exits before it is consumed.
                // For those, load_reg materializes first and the move runs
                // on the real heap word, preserving boxed-ABI semantics.
                if (vt_safe.count(inst.a) && vt_safe.at(inst.a)) break;
                // Escape analysis: region_move only promotes heap words
                // (is_heap_word gate in the runtime). A register whose slot
                // holds a raw scalar — unboxed int/float/bool — can never be
                // a heap word, so the call (and the box_float the boundary
                // normalization would insert for the float argument) is pure
                // overhead. U64 stays dynamic: 128-bit boxing routes heap
                // boxes through it. Pointer-assigned, tagged-word, and
                // pointer-language registers may still carry pubptr/raw
                // addresses and heap objects and keep the call for region
                // validation + promotion.
                LIR::Type mv_type = inst.type_a != LIR::Type::Void ? inst.type_a : LIR::Type::I64;
                if (mv_type == LIR::Type::I64 || mv_type == LIR::Type::Void) {
                    auto rt = lir_func.register_types.find(inst.a);
                    if (rt != lir_func.register_types.end()) mv_type = rt->second;
                }
                const bool mv_scalar =
                    (mv_type == LIR::Type::F64 || mv_type == LIR::Type::F32 || mv_type == LIR::Type::Bool ||
                     mv_type == LIR::Type::I8 || mv_type == LIR::Type::U8 ||
                     mv_type == LIR::Type::I16 || mv_type == LIR::Type::U16 ||
                     mv_type == LIR::Type::I32 || mv_type == LIR::Type::U32 ||
                     mv_type == LIR::Type::I64) &&
                    !pointer_assigned_regs.count(inst.a) && !is_pointer_lang_type(inst.a) &&
                    !tagged_word_regs.count(inst.a);
                if (!mv_scalar) {
                    builder_->createExternCall("lymar_aot_region_move", {load_reg(inst.a, inst.type_a),
                        context_->getConstantInt(context_->getIntegerType(64), inst.imm), get_caller_region()}, nullptr);
                }
                break;
            }
            case LIR::LIR_Op::FrameCallDeinit:
                builder_->createExternCall("lymar_aot_finalize", {load_reg(inst.a, inst.type_a)}, nullptr);
                break;
            case LIR::LIR_Op::Mov: {
                auto dst_lang_it = lir_func.register_language_types.find(inst.dst);
                const bool dst_is_erased = dst_lang_it != lir_func.register_language_types.end() && dst_lang_it->second &&
                    (dst_lang_it->second->tag == ::TypeTag::Any || dst_lang_it->second->tag == ::TypeTag::Union ||
                     dst_lang_it->second->tag == ::TypeTag::ErrorUnion);
                // Scalar constant-folding metadata describes the raw domain.
                // An erased destination holds a tagged LmValue word, so
                // inheriting e.g. reg_int_values would make print/arithmetic
                // consumers read the SMI encoding as a raw integer.
                if (!dst_is_erased) {
                    if (reg_decimal_scales.count(inst.a)) reg_decimal_scales[inst.dst] = reg_decimal_scales[inst.a];
                    if (reg_int_values.count(inst.a)) reg_int_values[inst.dst] = reg_int_values[inst.a];
                    if (reg_float_values.count(inst.a)) reg_float_values[inst.dst] = reg_float_values[inst.a];
                }
                if (reg_string_literals.count(inst.a)) reg_string_literals[inst.dst] = reg_string_literals[inst.a];
                if (reg_types.count(inst.a)) reg_types[inst.dst] = reg_types[inst.a];
                else if (inst.type_a != LIR::Type::Void) reg_types[inst.dst] = inst.type_a;
                auto destination_type = reg_types.count(inst.dst) ? reg_types[inst.dst] : inst.result_type;
                // Virtual tuple propagation: a move of an unmaterialized
                // tuple copies its scalar element slots instead of forcing
                // a heap allocation. Erased destinations still need the
                // tagged word — except record-typed (frame/tuple) ones,
                // which propagate the virtual container itself.
                const bool dst_is_record = s_lang_type_is_record(lir_func, inst.dst);
                if ((!dst_is_erased || dst_is_record) && inst.a != UINT32_MAX && vtuples.count(inst.a)) {
                    // Frame aliases share backing element slots (canonical
                    // pseudo registers or INOUT buffers) so field writes
                    // through one name are visible through every other —
                    // preserving reference semantics. Non-shareable element
                    // descriptors (read-only flattened params) fall back to
                    // capturing values into the destination's own slots.
                    bool share = vframes.count(inst.a) != 0;
                    if (share) {
                        for (const auto& e : vtuples[inst.a]) {
                            if (!e.canon_elem && !e.mem_base) { share = false; break; }
                        }
                    }
                    if (share) {
                        vtuples[inst.dst] = vtuples[inst.a];
                        vframes.insert(inst.dst);
                    } else if (vt_info.canon_regs.count(inst.dst)) {
                        canon_capture(inst.dst, vtuples[inst.a]);
                        if (vframes.count(inst.a)) vframes.insert(inst.dst);
                    } else {
                        vtuples[inst.dst] = vtuples[inst.a];
                        if (vframes.count(inst.a)) vframes.insert(inst.dst);
                    }
                    if (reg_types.count(inst.a)) reg_types[inst.dst] = reg_types[inst.a];
                    else if (inst.type_a != LIR::Type::Void) reg_types[inst.dst] = inst.type_a;
                    break;
                }
                ir::Value* mov_value = load_reg(inst.a, inst.type_a);
                if (dst_is_erased) {
                    // `any`/union registers hold tagged LmValue words: tag scalar
                    // sources on entry; erased sources already carry tags and
                    // pass through unchanged. A pointer-assigned source is
                    // already an erased word — routing it through tag_word's
                    // Ptr branch would tag_pointer() a tagged SMI into a
                    // bogus TYPE_FOREIGN_PTR box.
                    const bool src_is_erased_word = inst.a != UINT32_MAX &&
                        tagged_word_regs.count(inst.a);
                    mov_value = src_is_erased_word ? mov_value
                        : tag_word(mov_value, inst.a, inst.type_a);
                    // The destination now always holds a tagged LmValue word
                    // (scalar sources were encoded above, erased sources pass
                    // through), so erased arithmetic/bitwise lowering must see
                    // the Ptr word domain regardless of the source's scalar
                    // type.
                    destination_type = LIR::Type::Ptr;
                } else if (inst.a != UINT32_MAX && tagged_word_regs.count(inst.a)) {
                    // Tagged LmValue word flowing into a scalar-typed
                    // destination must be decoded back to the raw domain;
                    // copying it verbatim would leak the SMI/tag bits into
                    // int/float consumers (and double-tag on re-entry).
                    mov_value = untag_word(mov_value, inst.dst, inst.type_a);
                    if (inst.result_type != LIR::Type::Void) destination_type = inst.result_type;
                }
                // A move copies the value and its dynamic kind. In particular,
                // a missing typed-container lookup remains nil through aliases.
                store_reg(inst.dst, mov_value, destination_type, true);
                break;
            }
            case LIR::LIR_Op::LoadConst: {
                if (inst.type_name == "d2" || inst.type_name == "decimal") reg_decimal_scales[inst.dst] = 2;
                else if (inst.type_name == "d4") reg_decimal_scales[inst.dst] = 4;
                else if (inst.type_name == "d6") reg_decimal_scales[inst.dst] = 6;

                // Erased (`any`/union) destinations hold tagged LmValue words.
                // Scalar constants must be encoded (SMI/bool/immediate) or boxed
                // (out-of-range int) here — a raw i64 like 2^60 aliases TAG_PTR
                // and crashes erased-domain consumers.
                auto dst_lang_it = lir_func.register_language_types.find(inst.dst);
                const bool dst_erased = dst_lang_it != lir_func.register_language_types.end() && dst_lang_it->second &&
                    (dst_lang_it->second->tag == ::TypeTag::Any || dst_lang_it->second->tag == ::TypeTag::Union ||
                     dst_lang_it->second->tag == ::TypeTag::ErrorUnion);
                auto erased_const = [&](ir::Value* scalar, LIR::Type scalar_type) -> ir::Value* {
                    return dst_erased ? tag_word(scalar, UINT32_MAX, scalar_type) : scalar;
                };

                LmValue val = inst.const_val;
                bool is_float_const = (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32 || is_float_op(inst));
                if (!is_float_const && IS_PTR(val)) {
                    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
                    if (h && h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_FLOAT) {
                        is_float_const = true;
                    }
                }
                if (is_float_const) {
                    double fval = 0.0;
                    if (IS_PTR(val)) {
                        fval = as_float(val);
                    } else {
                        memcpy(&fval, &val, sizeof(double));
                    }
                    ir::Value* c = context_->getConstantFP(context_->getDoubleType(), fval);
                    reg_types[inst.dst] = LIR::Type::F64;
                    reg_float_values[inst.dst] = fval;
                    store_reg(inst.dst, c, LIR::Type::F64);
                } else if (IS_NIL(val) || val == 0) {
                    ir::Value* c = builder_->createExternCall("lymar_aot_nil", {}, context_->getIntegerType(64));
                    reg_types[inst.dst] = LIR::Type::Ptr;
                    store_reg(inst.dst, c, LIR::Type::Ptr);
                } else if (IS_INT(val) && (((val >> 3) << 3) | TAG_INT) == val) {
                    int64_t actual_val = UNBOX_INT(val);
                    ir::Value* c = erased_const(context_->getConstantInt(context_->getIntegerType(64), actual_val), LIR::Type::I64);
                    if (dst_erased) {
                        // The slot holds a tagged LmValue word, not a raw i64;
                        // recording I64 would route consumers to the raw-int
                        // print/arithmetic paths and leak the SMI encoding.
                        reg_types[inst.dst] = LIR::Type::Ptr;
                        store_reg(inst.dst, c, LIR::Type::Ptr);
                    } else {
                        reg_int_values[inst.dst] = actual_val;
                        reg_types[inst.dst] = LIR::Type::I64;
                        store_reg(inst.dst, c, LIR::Type::I64);
                    }
                } else if (IS_BOOL(val)) {
                    uint64_t actual_val = UNBOX_BOOL(val) ? 1 : 0;
                    ir::Value* c = erased_const(context_->getConstantInt(context_->getIntegerType(64), actual_val), LIR::Type::Bool);
                    store_reg(inst.dst, c, LIR::Type::Bool);
                } else if (IS_PTR(val)) {
                    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
                    if (h->type_id == TYPE_I64 || (h->type_id == TYPE_U64 && as_u128(val) <= INT64_MAX)) {
                        auto number = as_i64(val);
                        if (dst_erased) {
                            reg_types[inst.dst] = LIR::Type::Ptr;
                            store_reg(inst.dst, erased_const(context_->getConstantInt(context_->getIntegerType(64), number), LIR::Type::I64), LIR::Type::Ptr);
                        } else {
                            reg_int_values[inst.dst] = number;
                            store_reg(inst.dst, erased_const(context_->getConstantInt(context_->getIntegerType(64), number), LIR::Type::I64), LIR::Type::I64);
                        }
                    } else if (h->type_id == TYPE_I128 || h->type_id == TYPE_U128 || h->type_id == TYPE_U64) {
                        auto size = h->type_id == TYPE_U64 ? 16 : 32;
                        auto offset = h->type_id == TYPE_U64 ? 8 : 16;
                        auto* object = builder_->createExternCall("lymar_aot_alloc",
                            {context_->getConstantInt(context_->getIntegerType(64), size)}, context_->getIntegerType(64));
                        builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), h->type_id), object);
                        auto number = as_u128(val);
                        builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), static_cast<uint64_t>(number)),
                            builder_->createAdd(object, context_->getConstantInt(context_->getIntegerType(64), offset)));
                        if (size == 32) builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), static_cast<uint64_t>(number >> 64)),
                            builder_->createAdd(object, context_->getConstantInt(context_->getIntegerType(64), offset + 8)));
                        store_reg(inst.dst, object, LIR::Type::Ptr);
                    } else if (h->type_id == TYPE_STRING) {
                        const char* s = ((LmStringHeader*)h)->data;
                        uint64_t s_len = ((LmStringHeader*)h)->len;
                        reg_string_literals[inst.dst] = s;
                        reg_types[inst.dst] = LIR::Type::Ptr;

                        auto i8_ty  = context_->getIntegerType(8);

                        std::vector<ir::Constant*> elems;
                        auto add_u32 = [&](uint32_t val) {
                            elems.push_back(context_->getConstantInt(i8_ty, (uint8_t)(val & 0xFF)));
                            elems.push_back(context_->getConstantInt(i8_ty, (uint8_t)((val >> 8) & 0xFF)));
                            elems.push_back(context_->getConstantInt(i8_ty, (uint8_t)((val >> 16) & 0xFF)));
                            elems.push_back(context_->getConstantInt(i8_ty, (uint8_t)((val >> 24) & 0xFF)));
                        };
                        auto add_u64 = [&](uint64_t val) {
                            for (int b = 0; b < 8; ++b) {
                                elems.push_back(context_->getConstantInt(i8_ty, (uint8_t)((val >> (b * 8)) & 0xFF)));
                            }
                        };

                        add_u32(11); // TYPE_STRING
                        add_u32(0);  // metadata
                        add_u64(s_len);
                        add_u64(s_len);

                        for (size_t i = 0; i <= s_len; ++i) {
                            elems.push_back(context_->getConstantInt(i8_ty, (uint8_t)s[i]));
                        }

                        auto arr_ty = context_->getArrayType(i8_ty, elems.size());
                        ir::Value* arr_const = context_->getConstantArray(arr_ty, elems);
                        std::string name = "str_hdr_" + std::to_string(label_counter_++);
                        auto gv = std::make_unique<ir::GlobalVariable>(
                            context_->getPointerType(i8_ty),
                            name, static_cast<ir::Constant*>(arr_const), false, ".data"
                        );
                        ir::Value* raw_str_ptr = gv.get();
                        current_module_->addGlobalVariable(std::move(gv));
                        auto* owned_string = builder_->createExternCall("lymar_aot_copy_constant",
                            {raw_str_ptr, context_->getConstantInt(context_->getIntegerType(64), elems.size())}, context_->getIntegerType(64));
                        store_reg(inst.dst, owned_string, LIR::Type::Ptr);
                    } else if (h->type_id == TYPE_BOX) {
                        LmBox* box = (LmBox*)h;
                        if (box->type == LM_BOX_STRING) {
                            const char* s = (char*)box->value.as_ptr;
                            uint64_t s_len = strlen(s);
                            reg_string_literals[inst.dst] = s;
                            reg_types[inst.dst] = LIR::Type::Ptr;

                            std::string gv_name = "str_data_" + std::to_string(label_counter_++);
                            ir::GlobalVariable* gv_bytes = FyraBuiltinFunctions::get_or_create_global_str(
                                current_module_.get(), builder_.get(), gv_name, s
                            );
                            store_reg(inst.dst, gv_bytes, LIR::Type::Ptr);
                        } else if (box->type == LM_BOX_INT) {
                            uint64_t actual_val = (inst.result_type == LIR::Type::I64) ? box->value.as_int : BOX_INT(box->value.as_int);
                            if (inst.result_type == LIR::Type::I64) reg_int_values[inst.dst] = box->value.as_int;
                            // BOX_INT already yields a tagged SMI word; only the
                            // raw i64 form needs erased-domain encoding.
                            ir::Value* c = (inst.result_type == LIR::Type::I64)
                                ? erased_const(context_->getConstantInt(context_->getIntegerType(64), actual_val), LIR::Type::I64)
                                : context_->getConstantInt(context_->getIntegerType(64), actual_val);
                            store_reg(inst.dst, c, inst.result_type);
                        } else if (box->type == LM_BOX_FLOAT) {
                            double fval = box->value.as_float;
                            ir::Value* c = context_->getConstantFP(context_->getDoubleType(), fval);
                            reg_types[inst.dst] = LIR::Type::F64;
                            reg_float_values[inst.dst] = fval;
                            store_reg(inst.dst, c, LIR::Type::F64);
                        } else if (box->type == LM_BOX_BOOL) {
                            ir::Value* c = erased_const(context_->getConstantInt(context_->getIntegerType(64), box->value.as_bool ? 1 : 0), LIR::Type::Bool);
                            store_reg(inst.dst, c, LIR::Type::Bool);
                        } else {
                            ir::Value* c = builder_->createExternCall("lymar_aot_nil", {}, context_->getIntegerType(64));
                            store_reg(inst.dst, c, inst.result_type);
                        }
                    } else if (h->type_id == TYPE_FLOAT) {
                        double fval = ((ObjFloat*)h)->value;
                        ir::Value* c = context_->getConstantFP(context_->getDoubleType(), fval);
                        reg_types[inst.dst] = LIR::Type::F64;
                        reg_float_values[inst.dst] = fval;
                        store_reg(inst.dst, c, LIR::Type::F64);
                    } else {
                        ir::Value* c = builder_->createExternCall("lymar_aot_nil", {}, context_->getIntegerType(64));
                        store_reg(inst.dst, c, inst.result_type);
                    }
                } else {
                    if (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32) {
                        double fval;
                        memcpy(&fval, &val, sizeof(double));
                        ir::Value* c = context_->getConstantFP(context_->getDoubleType(), fval);
                        reg_types[inst.dst] = inst.result_type;
                        reg_float_values[inst.dst] = fval;
                        store_reg(inst.dst, c, inst.result_type);
                    } else {
                        ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), val);
                        store_reg(inst.dst, c, inst.result_type);
                    }
                }
                break;
            }
            case LIR::LIR_Op::StoreGlobal: {
                std::string gname = inst.func_name.empty() ? ("global_" + std::to_string(inst.dst)) : inst.func_name;
                gname = global_symbol(gname);
                ir::GlobalVariable* gv = nullptr;
                for (const auto& item : current_module_->getGlobalVariables()) {
                    if (item->getName() == gname) { gv = item.get(); break; }
                }
                auto lang_is_float = [&](uint32_t reg) {
                    auto it = lir_func.register_language_types.find(reg);
                    return it != lir_func.register_language_types.end() && it->second &&
                        (it->second->tag == ::TypeTag::Float64 || it->second->tag == ::TypeTag::Float32);
                };
                bool is_float_g = (inst.type_a == LIR::Type::F64 || inst.type_a == LIR::Type::F32 ||
                                  lang_is_float(inst.a) ||
                                  (reg_types.count(inst.a) && (reg_types[inst.a] == LIR::Type::F64 || reg_types[inst.a] == LIR::Type::F32)) ||
                                  (global_types_.count(gname) && (global_types_[gname] == LIR::Type::F64 || global_types_[gname] == LIR::Type::F32)));
                if (!gv) {
                    ir::Type* gv_type = is_float_g ? (ir::Type*)context_->getDoubleType() : (ir::Type*)context_->getIntegerType(64);
                    ir::Constant* init_val = is_float_g ? (ir::Constant*)context_->getConstantFP(context_->getDoubleType(), 0.0) : (ir::Constant*)context_->getConstantInt(context_->getIntegerType(64), 0);
                    auto new_gv = std::make_unique<ir::GlobalVariable>(
                        gv_type, gname, init_val, false, ".data"
                    );
                    ir::GlobalVariable* raw_gv = new_gv.get();
                    current_module_->addGlobalVariable(std::move(new_gv));
                    gv = raw_gv;
                }
                if (is_float_g) {
                    builder_->createStore(load_float_reg(inst.a, inst.type_a), gv);
                    global_types_[gname] = LIR::Type::F64;
                } else if (lang_type_is_erased(inst.a)) {
                    // Erased-typed globals hold tagged LmValue words; raw
                    // scalars/pointers must be encoded at the store boundary.
                    builder_->createStore(tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a), gv);
                } else {
                    builder_->createStore(load_reg(inst.a, inst.type_a), gv);
                }
                if (reg_decimal_scales.count(inst.a)) {
                    global_decimal_scales_[gname] = reg_decimal_scales[inst.a];
                }
                if (reg_types.count(inst.a)) {
                    global_types_[gname] = reg_types[inst.a];
                } else if (inst.type_a == LIR::Type::F64 || inst.type_a == LIR::Type::F32) {
                    global_types_[gname] = inst.type_a;
                }
                break;
            }
            case LIR::LIR_Op::LoadGlobal: {
                std::string gname = inst.func_name.empty() ? ("global_" + std::to_string(inst.a)) : inst.func_name;
                gname = global_symbol(gname);
                ir::GlobalVariable* gv = nullptr;
                for (const auto& item : current_module_->getGlobalVariables()) {
                    if (item->getName() == gname) { gv = item.get(); break; }
                }
                auto dst_lang = lir_func.register_language_types.find(inst.dst);
                bool dst_is_float = dst_lang != lir_func.register_language_types.end() && dst_lang->second &&
                    (dst_lang->second->tag == ::TypeTag::Float64 || dst_lang->second->tag == ::TypeTag::Float32);
                bool is_float_g = (dst_is_float ||
                                  (global_types_.count(gname) && (global_types_[gname] == LIR::Type::F64 || global_types_[gname] == LIR::Type::F32)) ||
                                  inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32);
                if (!gv) {
                    ir::Type* gv_type = is_float_g ? (ir::Type*)context_->getDoubleType() : (ir::Type*)context_->getIntegerType(64);
                    ir::Constant* init_val = is_float_g ? (ir::Constant*)context_->getConstantFP(context_->getDoubleType(), 0.0) : (ir::Constant*)context_->getConstantInt(context_->getIntegerType(64), 0);
                    auto new_gv = std::make_unique<ir::GlobalVariable>(
                        gv_type, gname, init_val, false, ".data"
                    );
                    ir::GlobalVariable* raw_gv = new_gv.get();
                    current_module_->addGlobalVariable(std::move(new_gv));
                    gv = raw_gv;
                }
                ir::Value* loaded = is_float_g ? static_cast<ir::Value*>(builder_->createLoadd(gv)) : builder_->createLoadl(gv);
                LIR::Type loaded_type = inst.result_type;
                if (global_types_.count(gname)) {
                    loaded_type = global_types_[gname];
                }
                if (is_float_g) {
                    store_reg(inst.dst, loaded, LIR::Type::F64);
                } else {
                    store_reg(inst.dst, loaded, loaded_type);
                }
                if (global_decimal_scales_.count(gname)) {
                    reg_decimal_scales[inst.dst] = global_decimal_scales_[gname];
                }
                break;
            }
            // IAdd_Unchecked / IAnd_Unchecked / IOr_Unchecked / IXor_Unchecked are the
            // generator's statically-typed-integer variants. "Unchecked" only removes
            // the VM's runtime representation/trap checks; numerically they are identical
            // to their checked counterparts. AOT integers are raw 64-bit values, so the
            // correct lowering is the exact same instruction -- fall through to the
            // checked case to guarantee cross-backend equivalence (AGENTS.md conformance).
            case LIR::LIR_Op::IAdd_Unchecked:
            case LIR::LIR_Op::Add:
                if (is_float_op(inst)) {
                    store_float_reg(inst.dst, builder_->createFAdd(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b)));
                } else if(erased_arithmetic(inst)) {
                    auto* result=builder_->createExternCall("lymar_aot_numeric_binary",{tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a),tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b),context_->getConstantInt(context_->getIntegerType(64),0)},context_->getIntegerType(64));
                    // The result is an erased word: raw integer or heap box with
                    // a runtime-tracked kind. Ptr keeps it object-classified so
                    // slots carry the dynamic kind instead of reading the box
                    // pointer as a scalar.
                    store_arith_word(inst,result);
                } else {
                    store_reg(inst.dst, builder_->createAdd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::Sub:
                if (is_float_op(inst)) {
                    store_float_reg(inst.dst, builder_->createFSub(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b)));
                } else if(erased_arithmetic(inst)) {
                    auto* result=builder_->createExternCall("lymar_aot_numeric_binary",{tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a),tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b),context_->getConstantInt(context_->getIntegerType(64),1)},context_->getIntegerType(64));
                    store_arith_word(inst,result);
                } else {
                    store_reg(inst.dst, builder_->createSub(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::Mul:
                if (is_float_op(inst)) {
                    store_float_reg(inst.dst, builder_->createFMul(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b)));
                } else if(erased_arithmetic(inst)) {
                    auto* result=builder_->createExternCall("lymar_aot_numeric_binary",{tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a),tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b),context_->getConstantInt(context_->getIntegerType(64),2)},context_->getIntegerType(64));
                    store_arith_word(inst,result);
                } else {
                    store_reg(inst.dst, builder_->createMul(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::Div:
                if (is_float_op(inst)) {
                    store_float_reg(inst.dst, builder_->createFDiv(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b)));
                } else if(erased_arithmetic(inst)) {
                    auto* result=builder_->createExternCall("lymar_aot_numeric_binary",{tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a),tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b),context_->getConstantInt(context_->getIntegerType(64),3)},context_->getIntegerType(64));
                    store_arith_word(inst,result);
                } else {
                    ir::Value* num = load_reg(inst.a, inst.type_a);
                    ir::Value* den = load_reg(inst.b, inst.type_b);
                    ir::Value* is_zero = builder_->createCeq(den, context_->getConstantInt(context_->getIntegerType(64), 0));

                    std::string div_id = std::to_string(label_counter_++);
                    ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                    ir::BasicBlock* b_safe = builder_->createBasicBlock("div_safe_" + div_id, cur_fn);
                    ir::BasicBlock* b_zero = builder_->createBasicBlock("div_zero_" + div_id, cur_fn);
                    ir::BasicBlock* b_done = builder_->createBasicBlock("div_done_" + div_id, cur_fn);

                    builder_->createBr(is_zero, b_zero, b_safe);

                    builder_->setInsertPoint(b_zero);
                    store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                    builder_->createJmp(b_done);

                    builder_->setInsertPoint(b_safe);
                    store_reg(inst.dst, builder_->createDiv(num, den), inst.result_type);
                    builder_->createJmp(b_done);

                    builder_->setInsertPoint(b_done);
                }
                break;
            case LIR::LIR_Op::Mod: {
                if(erased_arithmetic(inst)) {
                    auto* result=builder_->createExternCall("lymar_aot_numeric_binary",{tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a),tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b),context_->getConstantInt(context_->getIntegerType(64),4)},context_->getIntegerType(64));
                    store_arith_word(inst,result);
                    break;
                }
                ir::Value* num = load_reg(inst.a, inst.type_a);
                ir::Value* den = load_reg(inst.b, inst.type_b);
                ir::Value* is_zero = builder_->createCeq(den, context_->getConstantInt(context_->getIntegerType(64), 0));

                std::string mod_id = std::to_string(label_counter_++);
                ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                ir::BasicBlock* b_safe = builder_->createBasicBlock("mod_safe_" + mod_id, cur_fn);
                ir::BasicBlock* b_zero = builder_->createBasicBlock("mod_zero_" + mod_id, cur_fn);
                ir::BasicBlock* b_done = builder_->createBasicBlock("mod_done_" + mod_id, cur_fn);

                builder_->createBr(is_zero, b_zero, b_safe);

                builder_->setInsertPoint(b_zero);
                store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                builder_->createJmp(b_done);

                builder_->setInsertPoint(b_safe);
                store_reg(inst.dst, builder_->createRem(num, den), inst.result_type);
                builder_->createJmp(b_done);

                builder_->setInsertPoint(b_done);
                break;
            }
            case LIR::LIR_Op::Neg:
                if (reg_int_values.count(inst.a)) reg_int_values[inst.dst] = -reg_int_values[inst.a];
                if (reg_float_values.count(inst.a)) reg_float_values[inst.dst] = -reg_float_values[inst.a];
                if (is_float_op(inst)) {
                    store_float_reg(inst.dst, builder_->createFSub(context_->getConstantFP(context_->getDoubleType(), 0.0), load_float_reg(inst.a, inst.type_a)));
                } else if(erased_arithmetic(inst)) {
                    // Negate through numeric_binary as 0 - x so boxed i128/u128
                    // words are unboxed, negated in 128 bits, and reboxed.
                    // numeric_binary consumes tagged LmValue words only — a raw
                    // 0 decodes as TAG_PTR/nil and the op returns VAL_NIL.
                    auto* zero=tag_word(context_->getConstantInt(context_->getIntegerType(64),0),UINT32_MAX,LIR::Type::I64);
                    auto* result=builder_->createExternCall("lymar_aot_numeric_binary",{zero,tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a),context_->getConstantInt(context_->getIntegerType(64),1)},context_->getIntegerType(64));
                    store_arith_word(inst,result);
                } else {
                    store_reg(inst.dst, builder_->createNeg(load_reg(inst.a, inst.type_a)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::DecAdd:
                reg_decimal_scales[inst.dst] = decimal_scale_for_inst(inst);
                if (reg_int_values.count(inst.a) && reg_int_values.count(inst.b)) reg_int_values[inst.dst] = reg_int_values[inst.a] + reg_int_values[inst.b];
                store_reg(inst.dst, builder_->createAdd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::DecSub:
                reg_decimal_scales[inst.dst] = decimal_scale_for_inst(inst);
                if (reg_int_values.count(inst.a) && reg_int_values.count(inst.b)) reg_int_values[inst.dst] = reg_int_values[inst.a] - reg_int_values[inst.b];
                store_reg(inst.dst, builder_->createSub(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::DecMul: {
                int scale = decimal_scale_for_inst(inst);
                reg_decimal_scales[inst.dst] = scale;
                if (reg_int_values.count(inst.a) && reg_int_values.count(inst.b)) reg_int_values[inst.dst] = (reg_int_values[inst.a] * reg_int_values[inst.b]) / pow10_i64(scale);
                ir::Value* product = builder_->createMul(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b));
                store_reg(inst.dst, builder_->createDiv(product, context_->getConstantInt(context_->getIntegerType(64), pow10_i64(scale))), inst.result_type);
                break;
            }
            case LIR::LIR_Op::DecDiv: {
                int scale = decimal_scale_for_inst(inst);
                reg_decimal_scales[inst.dst] = scale;
                if (reg_int_values.count(inst.a) && reg_int_values.count(inst.b) && reg_int_values[inst.b] != 0) reg_int_values[inst.dst] = (reg_int_values[inst.a] * pow10_i64(scale)) / reg_int_values[inst.b];
                ir::Value* numerator = builder_->createMul(load_reg(inst.a, inst.type_a), context_->getConstantInt(context_->getIntegerType(64), pow10_i64(scale)));
                store_reg(inst.dst, builder_->createDiv(numerator, load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::DecMod:
                reg_decimal_scales[inst.dst] = decimal_scale_for_inst(inst);
                if (reg_int_values.count(inst.a) && reg_int_values.count(inst.b) && reg_int_values[inst.b] != 0) reg_int_values[inst.dst] = reg_int_values[inst.a] % reg_int_values[inst.b];
                store_reg(inst.dst, builder_->createRem(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::DecNeg:
                if (reg_decimal_scales.count(inst.a)) reg_decimal_scales[inst.dst] = reg_decimal_scales[inst.a];
                if (reg_int_values.count(inst.a)) reg_int_values[inst.dst] = -reg_int_values[inst.a];
                store_reg(inst.dst, builder_->createNeg(load_reg(inst.a, inst.type_a)), inst.result_type);
                break;
            case LIR::LIR_Op::Shl:
            case LIR::LIR_Op::Shr: {
                if (bitwise_erased(inst)) {
                    store_arith_word(inst, builder_->createExternCall("lymar_aot_bitwise",
                        {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a), tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b),
                         context_->getConstantInt(context_->getIntegerType(64), inst.op == LIR::LIR_Op::Shl ? 3 : 4)}, context_->getIntegerType(64)));
                } else if (inst.op == LIR::LIR_Op::Shl) {
                    store_reg(inst.dst, builder_->createShl(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                } else {
                    store_reg(inst.dst, builder_->createShr(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            }
            case LIR::LIR_Op::IAnd_Unchecked:
            case LIR::LIR_Op::And:
                if (bitwise_erased(inst)) {
                    store_arith_word(inst, builder_->createExternCall("lymar_aot_bitwise",
                        {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a), tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b),
                         context_->getConstantInt(context_->getIntegerType(64), 0)}, context_->getIntegerType(64)));
                } else {
                    store_reg(inst.dst, builder_->createAnd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::IOr_Unchecked:
            case LIR::LIR_Op::Or:
                if (bitwise_erased(inst)) {
                    store_arith_word(inst, builder_->createExternCall("lymar_aot_bitwise",
                        {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a), tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b),
                         context_->getConstantInt(context_->getIntegerType(64), 1)}, context_->getIntegerType(64)));
                } else {
                    store_reg(inst.dst, builder_->createOr(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::IXor_Unchecked:
            case LIR::LIR_Op::Xor:
                if (bitwise_erased(inst)) {
                    store_arith_word(inst, builder_->createExternCall("lymar_aot_bitwise",
                        {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a), tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b),
                         context_->getConstantInt(context_->getIntegerType(64), 2)}, context_->getIntegerType(64)));
                } else {
                    store_reg(inst.dst, builder_->createXor(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::CmpEQ:
            case LIR::LIR_Op::CmpNEQ: {
                // value_equal consumes tagged LmValue words only; raw scalar
                // operands must be SMI/immediate-tagged first or small ints
                // alias VAL_NIL/VAL_FALSE (e.g. raw 2 == nil).
                auto* equal = builder_->createExternCall("lymar_aot_value_equal",
                    {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a),
                     tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b)},
                    context_->getIntegerType(64));
                store_reg(inst.dst, inst.op == LIR::LIR_Op::CmpEQ ? static_cast<ir::Value*>(equal)
                    : builder_->createCeq(equal, context_->getConstantInt(context_->getIntegerType(64), 0)), LIR::Type::Bool);
                break;
            }
            case LIR::LIR_Op::CmpLT: {
                auto is_known_int = [&](uint32_t r, LIR::Type t) {
                    // Erased words (boxed i128/u128, pointer-classified arithmetic
                    // results, `any`-sourced values) carry a runtime kind; a raw
                    // integer compare would order heap-box addresses instead.
                    if (reg_types.count(r) && reg_types[r] == LIR::Type::Ptr) return false;
                    {
                        auto lt0 = lir_func.register_language_types.find(r);
                        if (lt0 != lir_func.register_language_types.end() && lt0->second &&
                            (lt0->second->tag == ::TypeTag::Int128 || lt0->second->tag == ::TypeTag::UInt128))
                            return false;
                    }
                    if (t == LIR::Type::I64 || t == LIR::Type::I32 || t == LIR::Type::U64 || t == LIR::Type::Bool) return true;
                    if (reg_int_values.count(r)) return true;
                    auto it = lir_func.register_language_types.find(r);
                    if (it != lir_func.register_language_types.end() && it->second) {
                        auto tag = it->second->tag;
                        if (tag == ::TypeTag::String || tag == ::TypeTag::Frame || tag == ::TypeTag::Any) return false;
                        if (tag == ::TypeTag::Int || tag == ::TypeTag::Int64 || tag == ::TypeTag::Int32 || tag == ::TypeTag::UInt || tag == ::TypeTag::UInt64 || tag == ::TypeTag::UInt32 || tag == ::TypeTag::Bool) return true;
                    }
                    if (reg_types.count(r) && (reg_types[r] == LIR::Type::I64 || reg_types[r] == LIR::Type::I32 || reg_types[r] == LIR::Type::Bool)) return true;
                    if (it != lir_func.register_language_types.end() && it->second) {
                        auto tag = it->second->tag;
                        if (tag == ::TypeTag::String || tag == ::TypeTag::Frame || tag == ::TypeTag::Any) return false;
                    }
                    return true;
                };
                if (is_float_op(inst)) {
                    ir::Value* c = builder_->createClt(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                } else if (is_known_int(inst.a, inst.type_a) && is_known_int(inst.b, inst.type_b)) {
                    ir::Value* c = builder_->createCslt(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                } else {
                    auto* compared = builder_->createExternCall("lymar_aot_numeric_compare",
                        {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a), tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b)}, context_->getIntegerType(64));
                    store_reg(inst.dst, builder_->createCslt(compared, context_->getConstantInt(context_->getIntegerType(64), 0)), LIR::Type::Bool);
                }
                break;
            }
            case LIR::LIR_Op::CmpLE: {
                auto is_known_int = [&](uint32_t r, LIR::Type t) {
                    // Erased words (boxed i128/u128, pointer-classified arithmetic
                    // results, `any`-sourced values) carry a runtime kind; a raw
                    // integer compare would order heap-box addresses instead.
                    if (reg_types.count(r) && reg_types[r] == LIR::Type::Ptr) return false;
                    {
                        auto lt0 = lir_func.register_language_types.find(r);
                        if (lt0 != lir_func.register_language_types.end() && lt0->second &&
                            (lt0->second->tag == ::TypeTag::Int128 || lt0->second->tag == ::TypeTag::UInt128))
                            return false;
                    }
                    if (t == LIR::Type::I64 || t == LIR::Type::I32 || t == LIR::Type::U64 || t == LIR::Type::Bool) return true;
                    if (reg_int_values.count(r)) return true;
                    auto it = lir_func.register_language_types.find(r);
                    if (it != lir_func.register_language_types.end() && it->second) {
                        auto tag = it->second->tag;
                        if (tag == ::TypeTag::String || tag == ::TypeTag::Frame || tag == ::TypeTag::Any) return false;
                        if (tag == ::TypeTag::Int || tag == ::TypeTag::Int64 || tag == ::TypeTag::Int32 || tag == ::TypeTag::UInt || tag == ::TypeTag::UInt64 || tag == ::TypeTag::UInt32 || tag == ::TypeTag::Bool) return true;
                    }
                    if (reg_types.count(r) && (reg_types[r] == LIR::Type::I64 || reg_types[r] == LIR::Type::I32 || reg_types[r] == LIR::Type::Bool)) return true;
                    if (it != lir_func.register_language_types.end() && it->second) {
                        auto tag = it->second->tag;
                        if (tag == ::TypeTag::String || tag == ::TypeTag::Frame || tag == ::TypeTag::Any) return false;
                    }
                    return true;
                };
                if (is_float_op(inst)) {
                    ir::Value* c = builder_->createCle(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                } else if (is_known_int(inst.a, inst.type_a) && is_known_int(inst.b, inst.type_b)) {
                    ir::Value* c = builder_->createCsle(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                } else {
                    auto* compared = builder_->createExternCall("lymar_aot_numeric_compare",
                        {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a), tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b)}, context_->getIntegerType(64));
                    store_reg(inst.dst, builder_->createCsle(compared, context_->getConstantInt(context_->getIntegerType(64), 0)), LIR::Type::Bool);
                }
                break;
            }
            case LIR::LIR_Op::CmpGT: {
                auto is_known_int = [&](uint32_t r, LIR::Type t) {
                    // Erased words (boxed i128/u128, pointer-classified arithmetic
                    // results, `any`-sourced values) carry a runtime kind; a raw
                    // integer compare would order heap-box addresses instead.
                    if (reg_types.count(r) && reg_types[r] == LIR::Type::Ptr) return false;
                    {
                        auto lt0 = lir_func.register_language_types.find(r);
                        if (lt0 != lir_func.register_language_types.end() && lt0->second &&
                            (lt0->second->tag == ::TypeTag::Int128 || lt0->second->tag == ::TypeTag::UInt128))
                            return false;
                    }
                    if (t == LIR::Type::I64 || t == LIR::Type::I32 || t == LIR::Type::U64 || t == LIR::Type::Bool) return true;
                    if (reg_int_values.count(r)) return true;
                    auto it = lir_func.register_language_types.find(r);
                    if (it != lir_func.register_language_types.end() && it->second) {
                        auto tag = it->second->tag;
                        if (tag == ::TypeTag::String || tag == ::TypeTag::Frame || tag == ::TypeTag::Any) return false;
                        if (tag == ::TypeTag::Int || tag == ::TypeTag::Int64 || tag == ::TypeTag::Int32 || tag == ::TypeTag::UInt || tag == ::TypeTag::UInt64 || tag == ::TypeTag::UInt32 || tag == ::TypeTag::Bool) return true;
                    }
                    if (reg_types.count(r) && (reg_types[r] == LIR::Type::I64 || reg_types[r] == LIR::Type::I32 || reg_types[r] == LIR::Type::Bool)) return true;
                    if (it != lir_func.register_language_types.end() && it->second) {
                        auto tag = it->second->tag;
                        if (tag == ::TypeTag::String || tag == ::TypeTag::Frame || tag == ::TypeTag::Any) return false;
                    }
                    return true;
                };
                if (is_float_op(inst)) {
                    ir::Value* c = builder_->createCgt(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                } else if (is_known_int(inst.a, inst.type_a) && is_known_int(inst.b, inst.type_b)) {
                    ir::Value* c = builder_->createCsgt(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                } else {
                    auto* compared = builder_->createExternCall("lymar_aot_numeric_compare",
                        {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a), tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b)}, context_->getIntegerType(64));
                    store_reg(inst.dst, builder_->createCsgt(compared, context_->getConstantInt(context_->getIntegerType(64), 0)), LIR::Type::Bool);
                }
                break;
            }
            case LIR::LIR_Op::CmpGE: {
                auto is_known_int = [&](uint32_t r, LIR::Type t) {
                    // Erased words (boxed i128/u128, pointer-classified arithmetic
                    // results, `any`-sourced values) carry a runtime kind; a raw
                    // integer compare would order heap-box addresses instead.
                    if (reg_types.count(r) && reg_types[r] == LIR::Type::Ptr) return false;
                    {
                        auto lt0 = lir_func.register_language_types.find(r);
                        if (lt0 != lir_func.register_language_types.end() && lt0->second &&
                            (lt0->second->tag == ::TypeTag::Int128 || lt0->second->tag == ::TypeTag::UInt128))
                            return false;
                    }
                    if (t == LIR::Type::I64 || t == LIR::Type::I32 || t == LIR::Type::U64 || t == LIR::Type::Bool) return true;
                    if (reg_int_values.count(r)) return true;
                    auto it = lir_func.register_language_types.find(r);
                    if (it != lir_func.register_language_types.end() && it->second) {
                        auto tag = it->second->tag;
                        if (tag == ::TypeTag::String || tag == ::TypeTag::Frame || tag == ::TypeTag::Any) return false;
                        if (tag == ::TypeTag::Int || tag == ::TypeTag::Int64 || tag == ::TypeTag::Int32 || tag == ::TypeTag::UInt || tag == ::TypeTag::UInt64 || tag == ::TypeTag::UInt32 || tag == ::TypeTag::Bool) return true;
                    }
                    if (reg_types.count(r) && (reg_types[r] == LIR::Type::I64 || reg_types[r] == LIR::Type::I32 || reg_types[r] == LIR::Type::Bool)) return true;
                    if (it != lir_func.register_language_types.end() && it->second) {
                        auto tag = it->second->tag;
                        if (tag == ::TypeTag::String || tag == ::TypeTag::Frame || tag == ::TypeTag::Any) return false;
                    }
                    return true;
                };
                if (is_float_op(inst)) {
                    ir::Value* c = builder_->createCge(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                } else if (is_known_int(inst.a, inst.type_a) && is_known_int(inst.b, inst.type_b)) {
                    ir::Value* c = builder_->createCsge(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b));
                    store_reg(inst.dst, builder_->createCast(c, context_->getIntegerType(64)), LIR::Type::Bool);
                } else {
                    auto* compared = builder_->createExternCall("lymar_aot_numeric_compare",
                        {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a), tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b)}, context_->getIntegerType(64));
                    store_reg(inst.dst, builder_->createCsge(compared, context_->getConstantInt(context_->getIntegerType(64), 0)), LIR::Type::Bool);
                }
                break;
            }
            case LIR::LIR_Op::Jump: {
                ir::BasicBlock* target = get_target_block(inst.imm, i);
                if (target) {
                    builder_->createJmp(target);
                    terminated = true;
                } else errors_.push_back("Jump to unknown target: " + std::to_string(inst.imm));
                break;
            }
            case LIR::LIR_Op::JumpIf:
            case LIR::LIR_Op::JumpIfFalse: {
                ir::BasicBlock* target = get_target_block(inst.imm, i);
                if (target) {
                    ir::BasicBlock* fallthrough = nullptr;
                    if (block_map.count(i + 1)) {
                        fallthrough = block_map.at(i + 1);
                    } else {
                        std::string block_name = "block_" + std::to_string(i + 1);
                        fallthrough = builder_->createBasicBlock(block_name, main_fn);
                        block_map[i + 1] = fallthrough;
                    }
                    ir::Value* cond = load_reg(inst.a, inst.type_a);
                    ir::Value* is_truthy = nullptr;
                    bool is_bool = (inst.type_a == LIR::Type::Bool ||
                                    (reg_types.count(inst.a) && reg_types[inst.a] == LIR::Type::Bool));
                    if (is_bool) {
                        is_truthy = cond;
                    } else {
                        ir::Value* is_not_zero = builder_->createCne(cond, context_->getConstantInt(context_->getIntegerType(64), 0));
                        ir::Value* is_not_vfalse = builder_->createCne(cond, context_->getConstantInt(context_->getIntegerType(64), VAL_FALSE));
                        ir::Value* is_not_vnil = builder_->createCne(cond, context_->getConstantInt(context_->getIntegerType(64), VAL_NIL));
                        is_truthy = builder_->createAnd(is_not_zero, builder_->createAnd(is_not_vfalse, is_not_vnil));
                    }

                    if (inst.op == LIR::LIR_Op::JumpIfFalse) builder_->createBr(is_truthy, fallthrough, target);
                    else builder_->createBr(is_truthy, target, fallthrough);
                    builder_->setInsertPoint(fallthrough);
                    terminated = false;
                } else errors_.push_back("Cond jump to unknown target: " + std::to_string(inst.imm));
                break;
            }
            case LIR::LIR_Op::Call:
            case LIR::LIR_Op::CallVoid: {
                std::string name = inst.func_name; 
                if (name.empty() && inst.const_val) {
                    if (IS_PTR(inst.const_val)) {
                        ObjHeader* h = (ObjHeader*)UNBOX_PTR(inst.const_val);
                        if (h->type_id == TYPE_STRING) {
                            name = ((LmStringHeader*)h)->data;
                        } else if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                            name = (char*)((LmBox*)h)->value.as_ptr;
                        }
                    }
                }
                if (name.empty()) {
                    if (LIR::BuiltinUtils::isBuiltinFunction(lir_func.name)) {
                        name = lir_func.name;
                    }
                }

                // Tree-shaken pure module inits emit no call; the result
                // register is defined as 0 (init return values are unused).
                if (name.size() > 9 && name.compare(name.size() - 9, 9, ".__init__") == 0 &&
                    reachable_funcs_.find(name) == reachable_funcs_.end()) {
                    if (inst.dst != UINT32_MAX)
                        store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                    break;
                }

                if (name == "channel") {
                    // The standalone scheduler uses the same queue representation
                    // as ChannelAlloc/Send/Recv; source constructors must agree.
                    used_builtins_.insert("lm_list_new");
                    auto* queue = current_module_->getFunction("lm_list_new");
                    if (!queue) queue = builder_->createFunction("lm_list_new", context_->getIntegerType(64),
                        {context_->getIntegerType(64)});
                    store_reg(inst.dst, builder_->createCall(queue,
                        {context_->getConstantInt(context_->getIntegerType(64), 16)}, context_->getIntegerType(64)), LIR::Type::Ptr);
                    break;
                }

                // `.direct` flattened-ABI call: eligible module functions with
                // tuple params/returns bypass the tagged heap-tuple ABI. Args
                // are per-element scalar words; tuple returns arrive through a
                // caller-allocated sret buffer and become a virtual tuple.
                const DirectFnSig* dsig = nullptr;
                const LIR::LIR_Function* dcallee = nullptr;
                if (!name.empty()) {
                    if (auto* cf = LIR::FunctionRegistry::getInstance().getFunction(name)) {
                        if (reachable_funcs_.count(name)) { dsig = direct_sig_for(name); dcallee = cf; }
                    }
                }
                auto* dfn = (dsig && dsig->eligible) ? current_module_->getFunction(name + ".direct") : nullptr;
                if (dfn && dcallee && inst.call_args.size() == dcallee->param_count) {
                    auto* i64ty = context_->getIntegerType(64);
                    std::vector<ir::Value*> dargs;
                    bool direct_ok = true;
                    // INOUT record params: caller-owned field buffers whose
                    // contents the callee may mutate; written back after the
                    // call — into shared virtual-record slots for virtual
                    // args, or via lymar_aot_frame_set_field for real ones.
                    struct InoutWriteback { uint32_t argreg; ir::Value* buf; bool real_frame; ir::Value* frame_ptr; const std::vector<int>* doms; };
                    std::vector<InoutWriteback> inout_writebacks;
                    auto buf_store = [&](ir::Value* buf, size_t j, int dom, ir::Value* v) {
                        if (dom == VDOM_FLOAT) {
                            if (!v->getType()->isFloatingPoint())
                                v = builder_->createExternCall("lymar_aot_to_float", {v}, context_->getDoubleType());
                        } else if (v->getType() != i64ty) {
                            v = builder_->createCast(v, i64ty);
                        }
                        ir::Value* addr = builder_->createAdd(buf,
                            context_->getConstantInt(i64ty, static_cast<long long>(j * 8)));
                        auto* st = builder_->createStore(v, addr);
                        if (dom == VDOM_FLOAT || dom == VDOM_INT || dom == VDOM_BOOL)
                            st->setName("scalar_store_vt");
                    };
                    auto buf_load = [&](ir::Value* buf, size_t j, int dom) -> ir::Value* {
                        ir::Value* addr = builder_->createAdd(buf,
                            context_->getConstantInt(i64ty, static_cast<long long>(j * 8)));
                        return (dom == VDOM_FLOAT)
                            ? static_cast<ir::Value*>(builder_->createLoadd(addr))
                            : static_cast<ir::Value*>(builder_->createLoadl(addr));
                    };
                    auto param_is_frame = [&](size_t pi) -> bool {
                        auto lt = dcallee->register_language_types.find(static_cast<uint32_t>(pi));
                        return lt != dcallee->register_language_types.end() && lt->second &&
                            lt->second->tag == ::TypeTag::Frame;
                    };
                    for (size_t pi = 0; pi < dcallee->param_count && direct_ok; ++pi) {
                        const auto& doms = dsig->param_elem_domains[pi];
                        const bool inout = pi < dsig->param_inout.size() && dsig->param_inout[pi] == 2;
                        uint32_t argreg = inst.call_args[pi];
                        if (doms.empty()) {
                            LIR::Type at = (pi < inst.call_arg_types.size()) ? inst.call_arg_types[pi] : LIR::Type::I64;
                            if (reg_types.count(argreg)) {
                                LIR::Type rt = reg_types[argreg];
                                if (rt == LIR::Type::F64 || rt == LIR::Type::F32) at = rt;
                            }
                            ir::Value* av = (at == LIR::Type::F64 || at == LIR::Type::F32)
                                ? load_float_reg(argreg, at) : load_reg(argreg, at);
                            auto lt = dcallee->register_language_types.find(pi);
                            if (av && lt != dcallee->register_language_types.end() && lt->second) {
                                switch (lt->second->tag) {
                                    case ::TypeTag::Any: case ::TypeTag::Union: case ::TypeTag::ErrorUnion:
                                        av = tag_word(av, argreg, at);
                                        break;
                                    default: break;
                                }
                            }
                            dargs.push_back(av);
                        } else if (inout) {
                            // Record param by in/out buffer: copy current field
                            // values in; the callee's FrameSetField writes land
                            // in the buffer and are copied back after the call.
                            ir::Value* buf = entry_alloc(nullptr,
                                context_->getConstantInt(i64ty, static_cast<long long>(doms.size() * 8)));
                            // Virtual args must back every element with
                            // shared storage (canon slot or INOUT buffer) or
                            // post-call write-back cannot reach the value.
                            bool shareable = vtuples.count(argreg) &&
                                vtuples[argreg].size() == doms.size();
                            if (shareable) {
                                const auto& elems = vtuples[argreg];
                                for (size_t ei = 0; ei < elems.size(); ++ei) {
                                    const auto& e = elems[ei];
                                    if ((!e.canon_elem && !e.mem_base) || e.domain != doms[ei]) {
                                        shareable = false; break;
                                    }
                                }
                            }
                            bool real_frame = !shareable;
                            ir::Value* frame_ptr = nullptr;
                            if (real_frame) frame_ptr = load_reg(argreg, LIR::Type::Ptr);
                            for (size_t ei = 0; ei < doms.size(); ++ei) {
                                ir::Value* fv = nullptr;
                                if (!real_frame) {
                                    const auto& e = vtuples[argreg][ei];
                                    fv = e.has ? velem_value(e)
                                        : (e.domain == VDOM_FLOAT)
                                            ? static_cast<ir::Value*>(context_->getConstantFP(context_->getDoubleType(), 0.0))
                                            : static_cast<ir::Value*>(context_->getConstantInt(i64ty, 0));
                                } else {
                                    ir::Value* raw = builder_->createExternCall("lymar_aot_frame_get_field",
                                        {frame_ptr, context_->getConstantInt(i64ty, static_cast<long long>(ei))}, i64ty);
                                    int d = doms[ei];
                                    if (d == VDOM_FLOAT) fv = untag_word(raw, UINT32_MAX, LIR::Type::F64);
                                    else if (d == VDOM_INT) fv = untag_word(raw, UINT32_MAX, LIR::Type::I64);
                                    else if (d == VDOM_BOOL) fv = untag_word(raw, UINT32_MAX, LIR::Type::Bool);
                                    else fv = raw; // VDOM_TAGGED: already a word
                                }
                                buf_store(buf, ei, doms[ei], fv);
                            }
                            dargs.push_back(buf);
                            inout_writebacks.push_back({argreg, buf, real_frame, frame_ptr, &doms});
                        } else if (vtuples.count(argreg)) {
                            const auto& elems = vtuples[argreg];
                            bool doms_match = elems.size() == doms.size();
                            for (size_t ei = 0; doms_match && ei < elems.size(); ++ei)
                                doms_match = elems[ei].domain == doms[ei];
                            if (doms_match) {
                                for (size_t ei = 0; ei < doms.size(); ++ei)
                                    dargs.push_back(velem_value(elems[ei]));
                            } else {
                                direct_ok = false;
                            }
                        } else {
                            if (vtuples.count(argreg)) materialize_vtuple(argreg);
                            ir::Value* obj = load_reg(argreg, LIR::Type::Ptr);
                            for (size_t ei = 0; ei < doms.size(); ++ei) {
                                ir::Value* raw;
                                if (param_is_frame(pi)) {
                                    raw = builder_->createExternCall("lymar_aot_frame_get_field",
                                        {obj, context_->getConstantInt(i64ty, static_cast<long long>(ei))}, i64ty);
                                } else {
                                    used_builtins_.insert("lm_tuple_get");
                                    ir::Function* gfn = current_module_->getFunction("lm_tuple_get");
                                    if (!gfn) gfn = builder_->createFunction("lm_tuple_get", i64ty, {i64ty, i64ty});
                                    raw = builder_->createCall(gfn,
                                        {obj, context_->getConstantInt(i64ty, static_cast<long long>(ei))}, i64ty);
                                }
                                int d = doms[ei];
                                if (d == VDOM_FLOAT) dargs.push_back(untag_word(raw, UINT32_MAX, LIR::Type::F64));
                                else if (d == VDOM_INT) dargs.push_back(untag_word(raw, UINT32_MAX, LIR::Type::I64));
                                else if (d == VDOM_BOOL) dargs.push_back(untag_word(raw, UINT32_MAX, LIR::Type::Bool));
                                else if (d == VDOM_PTR) dargs.push_back(untag_word(raw, UINT32_MAX, LIR::Type::Ptr));
                                else dargs.push_back(raw);
                            }
                        }
                    }
                    auto emit_inout_writebacks = [&]() {
                        for (const auto& wb : inout_writebacks) {
                            if (wb.real_frame) {
                                for (size_t j = 0; j < wb.doms->size(); ++j) {
                                    ir::Value* v = buf_load(wb.buf, j, (*wb.doms)[j]);
                                    ir::Value* tagged;
                                    switch ((*wb.doms)[j]) {
                                        case VDOM_FLOAT: tagged = tag_word(v); break;
                                        case VDOM_INT:
                                            tagged = builder_->createExternCall("lymar_aot_tag_int", {v}, i64ty);
                                            break;
                                        case VDOM_BOOL:
                                            tagged = builder_->createExternCall("lymar_aot_tag_bool", {v}, i64ty);
                                            break;
                                        case VDOM_PTR:
                                            tagged = builder_->createExternCall("lymar_aot_tag_pointer", {v}, i64ty);
                                            break;
                                        default: tagged = v; break;
                                    }
                                    builder_->createExternCall("lymar_aot_frame_set_field",
                                        {wb.frame_ptr, context_->getConstantInt(i64ty, static_cast<long long>(j)), tagged},
                                        context_->getVoidType());
                                }
                            } else if (vtuples.count(wb.argreg) && vtuples[wb.argreg].size() == wb.doms->size()) {
                                for (size_t j = 0; j < wb.doms->size(); ++j) {
                                    canon_store_elem(vtuples[wb.argreg][j], buf_load(wb.buf, j, (*wb.doms)[j]));
                                }
                            }
                        }
                    };
                    if (direct_ok && dsig->ret_sret) {
                        ir::Value* buf = entry_alloc(nullptr,
                            context_->getConstantInt(i64ty, static_cast<long long>(dsig->ret_domains.size() * 8)));
                        dargs.push_back(buf);
                        builder_->createCall(dfn, dargs);
                        emit_inout_writebacks();
                        if (inst.op == LIR::LIR_Op::Call && inst.dst != UINT32_MAX) {
                            std::vector<VTupleElem> relem(dsig->ret_domains.size());
                            for (size_t ei = 0; ei < relem.size(); ++ei) {
                                ir::Value* addr = builder_->createAdd(buf,
                                    context_->getConstantInt(i64ty, static_cast<long long>(ei * 8)));
                                VTupleElem ve;
                                ve.direct_v = (dsig->ret_domains[ei] == VDOM_FLOAT)
                                    ? static_cast<ir::Value*>(builder_->createLoadd(addr))
                                    : static_cast<ir::Value*>(builder_->createLoadl(addr));
                                ve.domain = dsig->ret_domains[ei];
                                ve.has = true;
                                relem[ei] = ve;
                            }
                            if (vt_info.canon_regs.count(inst.dst)) {
                                canon_capture(inst.dst, relem);
                            } else {
                                vtuples[inst.dst] = std::move(relem);
                            }
                            if (dsig->ret_frame) vframes.insert(inst.dst);
                            reg_types[inst.dst] = LIR::Type::Ptr;
                        }
                    } else if (direct_ok) {
                        ir::Value* res = builder_->createCall(dfn, dargs);
                        emit_inout_writebacks();
                        if (inst.op == LIR::LIR_Op::Call && inst.dst != UINT32_MAX) {
                            if (dsig->ret_nil) {
                                // The .direct callee returns the constant
                                // VAL_NIL word; storing the constant keeps the
                                // slot store provably scalar (no region edge).
                                store_reg(inst.dst,
                                    context_->getConstantInt(i64ty, 2), LIR::Type::Ptr, true);
                                break;
                            }
                            LIR::Type res_t = dsig->ret_float ? LIR::Type::F64 : inst.result_type;
                            if (res_t == LIR::Type::F64 || res_t == LIR::Type::F32) {
                                store_float_reg(inst.dst, res);
                            } else {
                                const bool erased_boolean = res_t == LIR::Type::Bool &&
                                    !Memory::proven_closed_boolean_boundary(*dcallee);
                                store_reg(inst.dst, res, erased_boolean ? LIR::Type::Ptr : res_t, true);
                            }
                        }
                    }
                    if (direct_ok) break;
                }

                std::vector<ir::Value*> args;
                // Erased (`any`/union/error-union) parameters hold tagged
                // LmValue words. Scalar arguments must be encoded here or the
                // callee's erased consumers read raw bits as tag payloads
                // (e.g. `map.put(k, 42)` stored raw 42 = tag-2 immediate).
                const LIR::LIR_Function* callee_lir = nullptr;
                if (auto* cf = LIR::FunctionRegistry::getInstance().getFunction(name))
                    callee_lir = cf;
                auto param_takes_erased_word = [&](size_t idx) -> bool {
                    if (!callee_lir || idx >= callee_lir->param_count) return false;
                    auto it = callee_lir->register_language_types.find(static_cast<uint32_t>(idx));
                    if (it == callee_lir->register_language_types.end() || !it->second) return false;
                    switch (it->second->tag) {
                        case ::TypeTag::Any: case ::TypeTag::Union: case ::TypeTag::ErrorUnion:
                            return true;
                        default: return false;
                    }
                };
                for (size_t ai = 0; ai < inst.call_args.size(); ++ai) {
                    LIR::Type at = (ai < inst.call_arg_types.size()) ? inst.call_arg_types[ai] : LIR::Type::I64;
                    if (ai < inst.call_args.size() && reg_types.count(inst.call_args[ai])) {
                        LIR::Type rt = reg_types[inst.call_args[ai]];
                        if (rt == LIR::Type::F64 || rt == LIR::Type::F32) at = rt;
                    }
                    ir::Value* arg_val;
                    if (at == LIR::Type::F64 || at == LIR::Type::F32) {
                        arg_val = load_float_reg(inst.call_args[ai], at);
                    } else {
                        arg_val = load_reg(inst.call_args[ai], at);
                    }
                    if (param_takes_erased_word(ai) && arg_val)
                        arg_val = tag_word(arg_val, inst.call_args[ai], at);
                    args.push_back(arg_val);
                }

                // See CallBuiltin below: generic len() must not lower to the
                // list-only lm_list_len; route it through the kind-checked
                // runtime so scalars/i128 get the VM's error instead of a
                // wild offset-16 read.
                if (name == "len" && args.size() == 1 && !inst.call_args.empty()) {
                    auto* len_res = builder_->createExternCall("lymar_aot_length",
                        {erased_word(args[0])},
                        context_->getIntegerType(64));
                    if (inst.dst != UINT32_MAX)
                        store_reg(inst.dst, len_res, inst.result_type);
                    break;
                }

                if (auto* value = lower_runtime_builtin(name, args)) {
                    if (inst.dst != UINT32_MAX) {
                        if (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32 || (value && value->getType()->isFloatingPoint()))
                            store_float_reg(inst.dst, value);
                        else
                            store_reg(inst.dst, value, inst.result_type);
                    }
                    break;
                }
                if (lower_gpu_builtin(name, args, inst)) break;
                if (name == "print") {
                    for (size_t ai = 0; ai < args.size(); ++ai) {
                        if (ai > 0) {
                            ir::GlobalVariable* gv_sp = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "str_space", " ");
                            builder_->createExternCall("io.write", {
                                context_->getConstantInt(context_->getIntegerType(64), 1),
                                builder_->createAdd(gv_sp, context_->getConstantInt(context_->getIntegerType(64), 24)),
                                context_->getConstantInt(context_->getIntegerType(64), 1)
                            }, context_->getIntegerType(64));
                        }
                        LIR::Type arg_type = (ai < inst.call_arg_types.size()) ? inst.call_arg_types[ai] : LIR::Type::I64;
                        if (ai < inst.call_args.size() && reg_types.count(inst.call_args[ai])) {
                            LIR::Type reg_t = reg_types[inst.call_args[ai]];
                            if (reg_t == LIR::Type::Bool || reg_t == LIR::Type::Ptr || reg_t == LIR::Type::F64 || reg_t == LIR::Type::F32) {
                                arg_type = reg_t;
                            }
                        }
                        if (ai < inst.call_args.size() && reg_string_literals.count(inst.call_args[ai])) {
                            arg_type = LIR::Type::Ptr;
                        }
                        if (ai < inst.call_args.size() && reg_int_values.count(inst.call_args[ai])) {
                            arg_type = LIR::Type::I64;
                        }
                        if (arg_type == LIR::Type::I64 && (inst.call_arg_types.size() > ai && inst.call_arg_types[ai] == LIR::Type::Bool)) {
                            arg_type = LIR::Type::Bool;
                        }
                        std::string prid = std::to_string(ai) + "_" + std::to_string(label_counter_++);
                        ir::Function* cur_fn = builder_->getInsertPoint()->getParent();

                        uint32_t arg_r = (ai < inst.call_args.size()) ? inst.call_args[ai] : UINT32_MAX;
                        bool is_known_i64 = (arg_r != UINT32_MAX && (reg_int_values.count(arg_r) || (reg_types.count(arg_r) && reg_types[arg_r] == LIR::Type::I64)));
                        if (std::getenv("LYMAR_DEBUG_PRINT") && name == "print")
                            std::cerr << "[PRINT] arg_r=" << arg_r << " arg_type=" << (int)arg_type
                                      << " reg_t=" << (reg_types.count(arg_r) ? (int)reg_types[arg_r] : -1)
                                      << " cat=" << (inst.call_arg_types.size() > ai ? (int)inst.call_arg_types[ai] : -1)
                                      << " tagged=" << (arg_r != UINT32_MAX && tagged_word_regs.count(arg_r))
                                      << " lang=" << (arg_r != UINT32_MAX && lir_func.register_language_types.count(arg_r) && lir_func.register_language_types.at(arg_r) ? (int)lir_func.register_language_types.at(arg_r)->tag : -1) << "\n";

                        if (ai < inst.call_args.size() && decimal_scale_for_reg(inst.call_args[ai]) > 0) {
                            FyraBuiltinFunctions::emit_print_decimal_inline(current_module_.get(), builder_.get(), args[ai], decimal_scale_for_reg(inst.call_args[ai]));
                        } else if (arg_type == LIR::Type::I64 || is_known_i64) {
                            builder_->createExternCall("lymar_aot_print_integer", {args[ai]}, context_->getVoidType());
                        } else if (arg_type == LIR::Type::Ptr) {
                            builder_->createExternCall("lymar_aot_print_value", {erased_word(args[ai])}, context_->getVoidType());
                        } else if (arg_type == LIR::Type::Bool) {
                            FyraBuiltinFunctions::emit_print_bool_inline(current_module_.get(), builder_.get(), args[ai]);
                        } else if (arg_type == LIR::Type::F64 || arg_type == LIR::Type::F32) {
                            builder_->createExternCall("lymar_aot_print_float", {args[ai]}, context_->getVoidType());
                        } else {
                            builder_->createExternCall("lymar_aot_print_integer", {args[ai]}, context_->getVoidType());
                        }
                    }
                    ir::GlobalVariable* gv_nl = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "nl", "\n");
                    builder_->createExternCall("io.write", {
                        context_->getConstantInt(context_->getIntegerType(64), 1),
                        builder_->createAdd(gv_nl, context_->getConstantInt(context_->getIntegerType(64), 24)),
                        context_->getConstantInt(context_->getIntegerType(64), 1)
                    }, context_->getIntegerType(64));

                    if (inst.op == LIR::LIR_Op::Call) store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                    break;
                } else if (name == "sleep" || name == "time.sleep" || name == "sleep_ms" || name == "time_sleep") {
                    auto* i64ty = context_->getIntegerType(64);
                    ir::Value* ms = nullptr;
                    if (!args.empty()) {
                        if (args[0]->getType() == context_->getDoubleType() || args[0]->getType() == context_->getFloatType()) {
                            auto* mul = builder_->createFMul(args[0], context_->getConstantFP(context_->getDoubleType(), 1000.0));
                            ms = builder_->createExternCall("lymar_aot_float_to_integer", {mul}, i64ty);
                        } else {
                            if (name == "sleep_ms") {
                                ms = args[0];
                            } else {
                                ms = builder_->createMul(args[0], context_->getConstantInt(i64ty, 1000));
                            }
                        }
                    } else {
                        ms = context_->getConstantInt(i64ty, 0);
                    }
                    std::vector<ir::Value*> sleep_args{ms};
                    builder_->createExternCall("time.sleep", sleep_args, context_->getVoidType());
                    if (inst.op == LIR::LIR_Op::Call && inst.dst != UINT32_MAX) store_reg(inst.dst, context_->getConstantInt(i64ty, 0), inst.result_type);
                    break;
                } else if (FyraBuiltinFunctions::is_builtin(name)) {
                    name = FyraBuiltinFunctions::get_internal_name(name);
                } else if (name == "main" && lir_func.name == "__top_level_wrapper__" && LIR::FunctionRegistry::getInstance().hasFunction("main")) {
                    name = "__user_main";
                }

                used_builtins_.insert(name);

                if (name.empty()) {
                    // Unresolved call target: the VM has no name to dispatch
                    // either, so this is a frontend/LIR bug — fail loudly here
                    // instead of emitting a call to a nonexistent `dummy_fn`.
                    errors_.push_back("unresolved call target in function " + lir_func.name);
                    if (inst.dst != UINT32_MAX)
                        store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                    break;
                }
                ir::Function* func = current_module_->getFunction(name);
                if (!func) {
                    std::vector<ir::Type*> pts;
                    for (size_t k = 0; k < args.size(); ++k) pts.push_back(args[k]->getType());
                    func = builder_->createFunction(name, lir_type_to_fyra_type(inst.result_type), pts);
                }
                LIR::Type res_t = inst.result_type;
                if (func && func->getType() && (func->getReturnType()->isDoubleTy() || func->getReturnType()->isFloatTy())) {
                    res_t = LIR::Type::F64;
                }
                // region_lowering decodes string-builtin index operands with
                // lymar_aot_string_index, which expects tagged LmValue words;
                // scalar args arrive raw and must be encoded here first.
                if (name == "_builtin_string_byte_at" || name == "_builtin_substring" || name == "substring") {
                    for (size_t ai = 1; ai < args.size(); ++ai) {
                        if (param_takes_erased_word(ai)) continue;
                        LIR::Type at = (ai < inst.call_arg_types.size()) ? inst.call_arg_types[ai] : LIR::Type::I64;
                        uint32_t ar = (ai < inst.call_args.size()) ? inst.call_args[ai] : UINT32_MAX;
                        args[ai] = tag_word(args[ai], ar, at);
                    }
                }
                ir::Value* res = func ? static_cast<ir::Value*>(builder_->createCall(func, args)) : static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64), 0));
                if (inst.op == LIR::LIR_Op::Call) {
                    reg_types[inst.dst] = res_t;
                    if (res_t == LIR::Type::F64 || res_t == LIR::Type::F32) {
                        store_float_reg(inst.dst, res);
                    } else {
                        const bool user_result = LIR::FunctionRegistry::getInstance().hasFunction(inst.func_name) &&
                            !LIR::BuiltinUtils::isBuiltinFunction(inst.func_name);
                        auto* contract = LIR::FunctionRegistry::getInstance().getFunction(inst.func_name);
                        const bool erased_boolean = user_result && res_t == LIR::Type::Bool &&
                            !Memory::proven_closed_boolean_boundary(*contract);
                        // A nominal boolean return can carry an erased alias.
                        // Preserve its dynamic kind rather than asserting Bool.
                        store_reg(inst.dst, res, erased_boolean ? LIR::Type::Ptr : res_t, user_result);
                    }
                }
                break;
            }
            case LIR::LIR_Op::CallIndirect: {
                std::vector<ir::Value*> args;
                for (size_t ai = 0; ai < inst.call_args.size(); ++ai) {
                    LIR::Type at = (ai < inst.call_arg_types.size()) ? inst.call_arg_types[ai] : LIR::Type::I64;
                    if (ai < inst.call_args.size() && reg_types.count(inst.call_args[ai])) {
                        LIR::Type rt = reg_types[inst.call_args[ai]];
                        if (rt == LIR::Type::F64 || rt == LIR::Type::F32) at = rt;
                    }
                    if (at == LIR::Type::F64 || at == LIR::Type::F32) {
                        args.push_back(load_float_reg(inst.call_args[ai], at));
                    } else {
                        args.push_back(load_reg(inst.call_args[ai], at));
                    }
                }
                // Share the dispatch CFG by native argument signature. Repeating
                // every reachable target at each call site creates quadratic IR
                // in imported higher-order/UI programs. The helper retains the
                // same checked receiver and dynamic kind/cleanup protocol.
                // The callee operand is already an erased callable word
                // (frame field, closure tuple, or fn-name string). Reg
                // language types are not populated for temporary FrameGetField
                // destinations, so tag_word would SMI-encode the pointer.
                std::vector<ir::Value*> site_args{load_reg(inst.a, inst.type_a)};
                site_args.insert(site_args.end(), args.begin(), args.end());
                std::string dispatch_name = "__lymar_indirect_dispatch_w";
                std::vector<ir::Type*> dispatch_types{context_->getIntegerType(64)};
                for (auto* argument : args) {
                    bool floating = argument->getType()->isFloatingPoint();
                    dispatch_name += floating ? "f" : "w";
                    dispatch_types.push_back(floating ? static_cast<ir::Type*>(context_->getDoubleType()) : static_cast<ir::Type*>(context_->getIntegerType(64)));
                }
                auto* dispatch = current_module_->getFunction(dispatch_name);
                if (!dispatch) {
                    auto* site_block = builder_->getInsertPoint();
                    dispatch = builder_->createFunction(dispatch_name, context_->getIntegerType(64), dispatch_types);
                    builder_->setInsertPoint(builder_->createBasicBlock("entry", dispatch));
                    auto parameter = dispatch->getParameters().begin();
                    ir::Value* raw_callee = parameter->get(); ++parameter;
                    args.clear();
                    for (; parameter != dispatch->getParameters().end(); ++parameter) args.push_back(parameter->get());
                raw_callee = builder_->createExternCall("lymar_aot_callable_receiver",
                    {erased_word(raw_callee)},
                    context_->getIntegerType(64));

                std::string cid = std::to_string(label_counter_++);
                ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                ir::BasicBlock* b_dispatch = builder_->createBasicBlock("ind_disp_" + cid, cur_fn);
                ir::BasicBlock* b_raw_call = builder_->createBasicBlock("ind_raw_" + cid, cur_fn);
                ir::BasicBlock* b_done = builder_->createBasicBlock("ind_done_" + cid, cur_fn);

                ir::Instruction* res_slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), context_->getIntegerType(64));
                builder_->createStore(builder_->createExternCall("lymar_aot_nil", {}, context_->getIntegerType(64)), res_slot);

                ir::Value* is_non_null = builder_->createCne(raw_callee, context_->getConstantInt(context_->getIntegerType(64), 0));
                builder_->createBr(is_non_null, b_dispatch, b_done);

                builder_->setInsertPoint(b_dispatch);
                ir::Instruction* callee_slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), context_->getIntegerType(64));
                builder_->createStore(raw_callee, callee_slot);

                ir::BasicBlock* b_is_box = builder_->createBasicBlock("ind_box_" + cid, cur_fn);
                ir::BasicBlock* b_read_callee = builder_->createBasicBlock("ind_rd_callee_" + cid, cur_fn);

                ir::Value* first_word = builder_->createLoadl(raw_callee);
                ir::Value* first_u32 = builder_->createAnd(first_word, context_->getConstantInt(context_->getIntegerType(64), 0xFFFFFFFF));
                ir::Value* is_box_type = builder_->createCeq(first_u32, context_->getConstantInt(context_->getIntegerType(64), 0)); // TYPE_BOX = 0
                ir::Value* is_foreign_box = builder_->createCeq(first_u32, context_->getConstantInt(context_->getIntegerType(64), 13)); // TYPE_FOREIGN_PTR = 13
                ir::Value* is_any_box = builder_->createOr(is_box_type, is_foreign_box);

                builder_->createBr(is_any_box, b_is_box, b_read_callee);

                builder_->setInsertPoint(b_is_box);
                ir::Value* unboxed_ptr = builder_->createLoadl(builder_->createAdd(raw_callee, context_->getConstantInt(context_->getIntegerType(64), 8)));
                builder_->createStore(unboxed_ptr, callee_slot);
                builder_->createJmp(b_read_callee);

                builder_->setInsertPoint(b_read_callee);
                ir::Value* callee = builder_->createLoadl(callee_slot);

                ir::Value* magic = builder_->createLoadl(callee);
                ir::Value* type_id = builder_->createAnd(magic, context_->getConstantInt(context_->getIntegerType(64), 0xFFFFFFFF));
                ir::Value* is_str = builder_->createCeq(type_id, context_->getConstantInt(context_->getIntegerType(64), 11)); // TYPE_STRING = 11

                ir::BasicBlock* b_str_dispatch = builder_->createBasicBlock("ind_str_" + cid, cur_fn);
                ir::BasicBlock* b_closure_dispatch = builder_->createBasicBlock("ind_cls_" + cid, cur_fn);
                builder_->createBr(is_str, b_str_dispatch, b_closure_dispatch);

                // Closure Tuple Dispatch: callee is a tuple ptr (element 0 = fn name or string, extra elements = captures)
                builder_->setInsertPoint(b_closure_dispatch);
                used_builtins_.insert("lm_tuple_get");
                ir::Function* fn_tget = current_module_->getFunction("lm_tuple_get");
                if (!fn_tget) fn_tget = builder_->createFunction("lm_tuple_get", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                ir::Value* fn_obj = builder_->createCall(fn_tget, {callee, context_->getConstantInt(context_->getIntegerType(64), 0)});

                std::vector<ir::Function*> cand_funcs;
                for (const auto& f : current_module_->getFunctions()) {
                    // A source callable name cannot grant access to linker or
                    // private runtime symbols that have no canonical contract.
                    if (LIR::FunctionRegistry::getInstance().hasFunction(f->getName()) &&
                        f->getName() != "main" && !f->getName().starts_with("lm_") && !f->getName().starts_with("_builtin_")) {
                        // A callee name can only reach this dispatch as a string
                        // literal collected above; skip candidates whose qualified
                        // or unqualified name never appears as one. This keeps
                        // the shared dispatch chain proportional to the number of
                        // functions actually used as callables, not the module size.
                        const std::string& fname = f->getName();
                        static const bool no_filter = std::getenv("LYMAR_NO_INDIRECT_FILTER") != nullptr;
                        bool name_reachable = no_filter || indirect_literals_.count(fname) != 0;
                        if (!name_reachable) {
                            size_t dot_p = fname.rfind('.');
                            if (dot_p != std::string::npos &&
                                indirect_literals_.count(fname.substr(dot_p + 1)))
                                name_reachable = true;
                        }
                        if (!name_reachable) continue;
                        auto builtin = LIR::builtin_callable_target(f->getName());
                        if (!builtin.empty() && LIR::LIRBuiltinFunctions::getInstance().getFunction(builtin)->acceptsArgumentCount(args.size()) &&
                            f->getParameters().size() != args.size()) continue;
                        cand_funcs.push_back(f.get());
                    }
                }

                ir::BasicBlock* cur_cls_chk = b_closure_dispatch;
                for (size_t fi = 0; fi < cand_funcs.size(); ++fi) {
                    ir::Function* target_f = cand_funcs[fi];
                    std::string f_name = target_f->getName();

                    builder_->setInsertPoint(cur_cls_chk);
                    ir::GlobalVariable* gv_fname = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "cls_str_" + f_name + "_" + cid, f_name);
                    ir::Value* eq_res = builder_->createExternCall("lymar_aot_string_name_eq", {fn_obj, gv_fname, context_->getConstantInt(context_->getIntegerType(64), f_name.size())}, context_->getIntegerType(64));
                    ir::Value* is_match = builder_->createCne(eq_res, context_->getConstantInt(context_->getIntegerType(64), 0));

                    size_t dot_p = f_name.rfind('.');
                    if (dot_p != std::string::npos) {
                        std::string unq_name = f_name.substr(dot_p + 1);
                        ir::GlobalVariable* gv_unq = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "cls_unq_" + unq_name + "_" + cid + "_" + std::to_string(fi), unq_name);
                        ir::Value* unq_eq = builder_->createExternCall("lymar_aot_string_name_eq", {fn_obj, gv_unq, context_->getConstantInt(context_->getIntegerType(64), unq_name.size())}, context_->getIntegerType(64));
                        ir::Value* unq_match = builder_->createCne(unq_eq, context_->getConstantInt(context_->getIntegerType(64), 0));
                        is_match = builder_->createOr(is_match, unq_match);
                    }

                    ir::BasicBlock* b_match = builder_->createBasicBlock("cls_m_" + std::to_string(fi) + "_" + cid, cur_fn);
                    ir::BasicBlock* b_next_check = builder_->createBasicBlock("cls_next_" + std::to_string(fi) + "_" + cid, cur_fn);

                    builder_->createBr(is_match, b_match, b_next_check);

                    builder_->setInsertPoint(b_match);
                    if (!LIR::builtin_callable_target(f_name).empty() && target_f->getParameters().size() != args.size()) {
                        builder_->createExternCall("lymar_aot_builtin_arity_error", {}, context_->getVoidType());
                        builder_->createJmp(b_done);
                        cur_cls_chk = b_next_check;
                        continue;
                    }
                    std::vector<ir::Value*> call_args_matching;
                    size_t target_param_cnt = target_f->getParameters().size();

                    if (target_param_cnt == args.size() + 1) {
                        for (size_t k = 0; k < args.size(); ++k) call_args_matching.push_back(args[k]);
                        call_args_matching.push_back(callee);
                    } else if (target_param_cnt == args.size()) {
                        for (size_t k = 0; k < args.size(); ++k) call_args_matching.push_back(args[k]);
                    } else {
                        for (size_t k = 0; k < target_param_cnt; ++k) {
                            if (k < args.size()) call_args_matching.push_back(args[k]);
                            else if (k == args.size()) call_args_matching.push_back(callee);
                            else call_args_matching.push_back(context_->getConstantInt(context_->getIntegerType(64), 0));
                        }
                    }
                    while (call_args_matching.size() < target_param_cnt) {
                        call_args_matching.push_back(context_->getConstantInt(context_->getIntegerType(64), 0));
                    }
                    ir::Value* call_res = builder_->createCall(target_f, call_args_matching);
                    builder_->createStore(tag_indirect_result(call_res, f_name), res_slot);
                    builder_->createJmp(b_done);

                    cur_cls_chk = b_next_check;
                }

                builder_->setInsertPoint(cur_cls_chk);
                builder_->createJmp(b_raw_call);

                // String Name Direct Dispatch
                builder_->setInsertPoint(b_str_dispatch);
                ir::BasicBlock* cur_check_bb = b_str_dispatch;
                for (size_t fi = 0; fi < cand_funcs.size(); ++fi) {
                    ir::Function* target_f = cand_funcs[fi];
                    std::string f_name = target_f->getName();

                    builder_->setInsertPoint(cur_check_bb);
                    ir::GlobalVariable* gv_fname = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "fn_str_" + f_name + "_" + cid, f_name);
                    ir::Value* eq_res = builder_->createExternCall("lymar_aot_string_name_eq", {callee, gv_fname, context_->getConstantInt(context_->getIntegerType(64), f_name.size())}, context_->getIntegerType(64));
                    ir::Value* is_match = builder_->createCne(eq_res, context_->getConstantInt(context_->getIntegerType(64), 0));

                    size_t dot_p = f_name.rfind('.');
                    if (dot_p != std::string::npos) {
                        std::string unq_name = f_name.substr(dot_p + 1);
                        ir::GlobalVariable* gv_unq = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "fn_unq_" + unq_name + "_" + cid + "_" + std::to_string(fi), unq_name);
                        ir::Value* unq_eq = builder_->createExternCall("lymar_aot_string_name_eq", {callee, gv_unq, context_->getConstantInt(context_->getIntegerType(64), unq_name.size())}, context_->getIntegerType(64));
                        ir::Value* unq_match = builder_->createCne(unq_eq, context_->getConstantInt(context_->getIntegerType(64), 0));
                        is_match = builder_->createOr(is_match, unq_match);
                    }

                    ir::BasicBlock* b_match = builder_->createBasicBlock("ind_m_" + std::to_string(fi) + "_" + cid, cur_fn);
                    ir::BasicBlock* b_next_check = builder_->createBasicBlock("ind_next_" + std::to_string(fi) + "_" + cid, cur_fn);

                    builder_->createBr(is_match, b_match, b_next_check);

                    builder_->setInsertPoint(b_match);
                    if (!LIR::builtin_callable_target(f_name).empty() && target_f->getParameters().size() != args.size()) {
                        builder_->createExternCall("lymar_aot_builtin_arity_error", {}, context_->getVoidType());
                        builder_->createJmp(b_done);
                        cur_check_bb = b_next_check;
                        continue;
                    }
                    std::vector<ir::Value*> call_args_matching;
                    size_t target_param_cnt = target_f->getParameters().size();
                    if (target_param_cnt == args.size() + 1) {
                        for (size_t k = 0; k < args.size(); ++k) call_args_matching.push_back(args[k]);
                        call_args_matching.push_back(callee);
                    } else if (target_param_cnt == args.size()) {
                        for (size_t k = 0; k < args.size(); ++k) call_args_matching.push_back(args[k]);
                    } else {
                        for (size_t k = 0; k < target_param_cnt; ++k) {
                            if (k < args.size()) call_args_matching.push_back(args[k]);
                            else if (k == args.size()) call_args_matching.push_back(callee);
                            else call_args_matching.push_back(context_->getConstantInt(context_->getIntegerType(64), 0));
                        }
                    }
                    while (call_args_matching.size() < target_param_cnt) {
                        call_args_matching.push_back(context_->getConstantInt(context_->getIntegerType(64), 0));
                    }
                    ir::Value* call_res = builder_->createCall(target_f, call_args_matching);
                    builder_->createStore(tag_indirect_result(call_res, f_name), res_slot);
                    builder_->createJmp(b_done);

                    cur_check_bb = b_next_check;
                }

                builder_->setInsertPoint(cur_check_bb);
                builder_->createJmp(b_raw_call);

                builder_->setInsertPoint(b_raw_call);
                // Unresolved names and malformed callables return nil in VM.
                // They are not permission to execute an arbitrary data address.
                builder_->createJmp(b_done);

                builder_->setInsertPoint(b_done);
                ir::Value* final_res = builder_->createLoadl(res_slot);
                builder_->createRet(final_res);
                    builder_->setInsertPoint(site_block);
                }
                auto* dispatched_result = builder_->createCall(dispatch, site_args);
                if (inst.dst != UINT32_MAX) {
                    reg_types[inst.dst] = inst.result_type;
                    // The shared dispatch returns canonical tagged LmValue
                    // words; scalar destinations untag exactly once.
                    store_reg(inst.dst, untag_word(dispatched_result, inst.dst, inst.result_type), inst.result_type, true);
                }
                break;
            }
            case LIR::LIR_Op::CallBuiltin: {
                std::string name = inst.func_name; 
                if (name.empty() && inst.const_val) {
                    if (IS_PTR(inst.const_val)) {
                        ObjHeader* h = (ObjHeader*)UNBOX_PTR(inst.const_val);
                        if (h->type_id == TYPE_STRING) {
                            name = ((LmStringHeader*)h)->data;
                        } else if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
                            name = (char*)((LmBox*)h)->value.as_ptr;
                        }
                    }
                }
                if (name.empty()) {
                    if (LIR::BuiltinUtils::isBuiltinFunction(lir_func.name)) {
                        name = lir_func.name;
                    }
                }

                std::vector<ir::Value*> args;
                for (auto r : inst.call_args) args.push_back(load_reg(r, LIR::Type::I64));

                // len() is type-agnostic in Lymar (str/list/dict/frame/nil);
                // the lm_list_len IR builtin reads a raw offset-16 word and
                // returns garbage/segfaults on scalars and i128 boxes. The
                // runtime validates the erased kind sidecar and rejects
                // unsupported receivers the same way the VM does.
                if (name == "len" && args.size() == 1 && !inst.call_args.empty()) {
                    auto* len_res = builder_->createExternCall("lymar_aot_length",
                        {erased_word(args[0])},
                        context_->getIntegerType(64));
                    if (inst.dst != UINT32_MAX)
                        store_reg(inst.dst, len_res, inst.result_type);
                    break;
                }

                if (auto* value = lower_runtime_builtin(name, args)) {
                    if (inst.dst != UINT32_MAX) {
                        if (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32 || (value && value->getType()->isFloatingPoint()))
                            store_float_reg(inst.dst, value);
                        else
                            store_reg(inst.dst, value, inst.result_type);
                    }
                    break;
                }
                if (lower_gpu_builtin(name, args, inst)) break;
                if (name == "print") {
                    for (size_t ai = 0; ai < args.size(); ++ai) {
                        if (ai > 0) {
                            ir::GlobalVariable* gv_sp = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "str_space", " ");
                            builder_->createExternCall("io.write", {
                                context_->getConstantInt(context_->getIntegerType(64), 1),
                                builder_->createAdd(gv_sp, context_->getConstantInt(context_->getIntegerType(64), 24)),
                                context_->getConstantInt(context_->getIntegerType(64), 1)
                            }, context_->getIntegerType(64));
                        }
                        LIR::Type arg_type = (ai < inst.call_arg_types.size()) ? inst.call_arg_types[ai] : LIR::Type::I64;
                        if (ai < inst.call_args.size() && reg_types.count(inst.call_args[ai])) {
                            LIR::Type reg_t = reg_types[inst.call_args[ai]];
                            if (reg_t == LIR::Type::Bool || reg_t == LIR::Type::Ptr || reg_t == LIR::Type::F64 || reg_t == LIR::Type::F32) {
                                arg_type = reg_t;
                            }
                        }
                        if (ai < inst.call_args.size() && reg_string_literals.count(inst.call_args[ai])) {
                            arg_type = LIR::Type::Ptr;
                        }
                        if (ai < inst.call_args.size() && (reg_int_values.count(inst.call_args[ai]) || (inst.call_arg_types.size() > ai && inst.call_arg_types[ai] == LIR::Type::I64 && !reg_types.count(inst.call_args[ai])))) {
                            arg_type = LIR::Type::I64;
                        }
                        if (arg_type == LIR::Type::I64 && (inst.call_arg_types.size() > ai && inst.call_arg_types[ai] == LIR::Type::Bool)) {
                            arg_type = LIR::Type::Bool;
                        }
                        std::string prid = std::to_string(ai) + "_" + std::to_string(label_counter_++);
                        ir::Function* cur_fn = builder_->getInsertPoint()->getParent();

                        uint32_t arg_r = (ai < inst.call_args.size()) ? inst.call_args[ai] : UINT32_MAX;
                        bool is_known_i64 = (arg_r != UINT32_MAX && (reg_int_values.count(arg_r) || (reg_types.count(arg_r) && reg_types[arg_r] == LIR::Type::I64)));
                        if (std::getenv("LYMAR_DEBUG_PRINT") && name == "print")
                            std::cerr << "[PRINT] arg_r=" << arg_r << " arg_type=" << (int)arg_type
                                      << " reg_t=" << (reg_types.count(arg_r) ? (int)reg_types[arg_r] : -1)
                                      << " cat=" << (inst.call_arg_types.size() > ai ? (int)inst.call_arg_types[ai] : -1)
                                      << " tagged=" << (arg_r != UINT32_MAX && tagged_word_regs.count(arg_r))
                                      << " lang=" << (arg_r != UINT32_MAX && lir_func.register_language_types.count(arg_r) && lir_func.register_language_types.at(arg_r) ? (int)lir_func.register_language_types.at(arg_r)->tag : -1) << "\n";

                        if (ai < inst.call_args.size() && decimal_scale_for_reg(inst.call_args[ai]) > 0) {
                            FyraBuiltinFunctions::emit_print_decimal_inline(current_module_.get(), builder_.get(), args[ai], decimal_scale_for_reg(inst.call_args[ai]));
                        } else if (arg_type == LIR::Type::I64 || is_known_i64) {
                            builder_->createExternCall("lymar_aot_print_integer", {args[ai]}, context_->getVoidType());
                        } else if (arg_type == LIR::Type::Ptr) {
                            builder_->createExternCall("lymar_aot_print_value", {erased_word(args[ai])}, context_->getVoidType());
                        } else if (arg_type == LIR::Type::Bool) {
                            FyraBuiltinFunctions::emit_print_bool_inline(current_module_.get(), builder_.get(), args[ai]);
                        } else if (arg_type == LIR::Type::F64 || arg_type == LIR::Type::F32) {
                            builder_->createExternCall("lymar_aot_print_float", {args[ai]}, context_->getVoidType());
                        } else {
                            builder_->createExternCall("lymar_aot_print_integer", {args[ai]}, context_->getVoidType());
                        }
                    }
                    ir::GlobalVariable* gv_nl = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "nl", "\n");
                    builder_->createExternCall("io.write", {
                        context_->getConstantInt(context_->getIntegerType(64), 1),
                        builder_->createAdd(gv_nl, context_->getConstantInt(context_->getIntegerType(64), 24)),
                        context_->getConstantInt(context_->getIntegerType(64), 1)
                    }, context_->getIntegerType(64));

                    if (inst.dst != UINT32_MAX) store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                    break;
                } else if (name == "assert" && !args.empty()) {
                    auto* message=args.size()>1?erased_word(args[1]):static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64),2));
                    builder_->createExternCall("lymar_aot_assert",{args[0],message},nullptr);
                    if(inst.dst!=UINT32_MAX) store_reg(inst.dst,context_->getConstantInt(context_->getIntegerType(64),0),inst.result_type);
                    break;
                } else if (FyraBuiltinFunctions::is_builtin(name)) {
                    name = FyraBuiltinFunctions::get_internal_name(name);
                } else if (name == "main" && lir_func.name == "__top_level_wrapper__" && LIR::FunctionRegistry::getInstance().hasFunction("main")) {
                    name = "__user_main";
                }

                used_builtins_.insert(name);

                if (name.empty()) {
                    errors_.push_back("unresolved call target in function " + lir_func.name);
                    if (inst.dst != UINT32_MAX)
                        store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), inst.result_type);
                    break;
                }
                ir::Function* func = current_module_->getFunction(name);
                if (!func) {
                    std::vector<ir::Type*> pts;
                    for (size_t k = 0; k < args.size(); ++k) pts.push_back(args[k]->getType());
                    func = builder_->createFunction(name, lir_type_to_fyra_type(inst.result_type), pts);
                }
                // region_lowering decodes string-builtin index operands with
                // lymar_aot_string_index, which expects tagged LmValue words;
                // scalar args arrive raw and must be encoded here first.
                if (name == "_builtin_string_byte_at" || name == "_builtin_substring" || name == "substring") {
                    for (size_t ai = 1; ai < args.size(); ++ai) {
                        uint32_t ar = (ai < inst.call_args.size()) ? inst.call_args[ai] : UINT32_MAX;
                        args[ai] = tag_word(args[ai], ar, LIR::Type::I64);
                    }
                }
                if (func) store_reg(inst.dst, builder_->createCall(func, args), inst.result_type);
                break;
            }
            case LIR::LIR_Op::Load: store_reg(inst.dst, builder_->createLoadl(load_reg(inst.a, inst.type_a)), inst.result_type); break;
            case LIR::LIR_Op::Store: builder_->createStore(load_reg(inst.b, inst.type_b), load_reg(inst.a, inst.type_a)); break;
            case LIR::LIR_Op::Cast: {
                auto* value = load_reg(inst.a, inst.type_a);
                auto actual = reg_types.count(inst.a) ? reg_types[inst.a] : inst.type_a;
                // The conversion helpers below consume tagged LmValue words;
                // scalar sources must be encoded first or small raw ints alias
                // SMI/immediate tags (raw 1 -> SMI 0, raw 2 -> VAL_NIL).
                auto* tagged_src = tag_word(value, inst.a, inst.type_a);
                if (inst.result_type == LIR::Type::Ptr) {
                    auto destination = lir_func.get_register_language_type(inst.dst);
                    if (destination && destination->tag == TypeTag::String) {
                        auto src_lang = lir_func.get_register_language_type(inst.a);
                        if (src_lang && src_lang->tag == TypeTag::Bool) {
                            store_reg(inst.dst, builder_->createExternCall("lymar_aot_bool_to_string",
                                {tagged_src}, context_->getIntegerType(64)), LIR::Type::Ptr);
                        } else if (src_lang && src_lang->tag == TypeTag::Enum) {
                            used_builtins_.insert("lm_enum_to_str");
                            ir::Function* etfn = current_module_->getFunction("lm_enum_to_str");
                            if (!etfn) etfn = builder_->createFunction("lm_enum_to_str", context_->getIntegerType(64), {context_->getIntegerType(64)});
                            store_reg(inst.dst, builder_->createCall(etfn, {tagged_src}), LIR::Type::Ptr);
                        } else {
                            store_reg(inst.dst, builder_->createExternCall("lymar_aot_scalar_to_string",
                                {tagged_src}, context_->getIntegerType(64)), LIR::Type::Ptr);
                        }
                    }
                    else store_reg(inst.dst, tagged_src, LIR::Type::Ptr);
                } else if (inst.result_type == LIR::Type::Bool) {
                    store_reg(inst.dst, builder_->createExternCall("lymar_aot_to_boolean",
                        {tagged_src}, context_->getIntegerType(64)), LIR::Type::Bool);
                } else if (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32) {
                    if (value->getType()->isFloatingPoint()) store_float_reg(inst.dst, value);
                    else store_float_reg(inst.dst, builder_->createExternCall("lymar_aot_to_float",
                        {tagged_src}, context_->getDoubleType()));
                } else if (inst.result_type == LIR::Type::I64) {
                    if (value->getType()->isFloatingPoint())
                        store_reg(inst.dst, builder_->createExternCall("lymar_aot_float_to_integer",
                            {value}, context_->getIntegerType(64)), LIR::Type::I64);
                    else store_reg(inst.dst, builder_->createExternCall("lymar_aot_to_integer",
                        {tagged_src}, context_->getIntegerType(64)), LIR::Type::I64);
                } else store_reg(inst.dst, builder_->createCast(value, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::DecRescale: {
                int src_scale = decimal_scale_for_reg(inst.a);
                int dst_scale = decimal_scale_for_reg(inst.dst);
                if (src_scale <= 0) {
                    auto it = lir_func.register_language_types.find(inst.a);
                    if (it != lir_func.register_language_types.end() && it->second) src_scale = it->second->getDecimalScale();
                }
                if (dst_scale <= 0) {
                    auto it = lir_func.register_language_types.find(inst.dst);
                    if (it != lir_func.register_language_types.end() && it->second) dst_scale = it->second->getDecimalScale();
                }
                if (dst_scale > 0 && src_scale <= 0) src_scale = (dst_scale == 6) ? 4 : 2;
                if (src_scale > 0 && dst_scale <= 0) dst_scale = (src_scale == 2) ? 4 : 6;
                if (src_scale <= 0) src_scale = 2;
                if (dst_scale <= 0) dst_scale = 4;

                ir::Value* value = load_reg(inst.a, inst.type_a);
                if (src_scale > 0 && dst_scale > 0 && src_scale != dst_scale) {
                    int delta = dst_scale - src_scale;
                    int64_t factor = pow10_i64(std::abs(delta));
                    if (reg_int_values.count(inst.a)) reg_int_values[inst.dst] = (delta > 0) ? (reg_int_values[inst.a] * factor) : (reg_int_values[inst.a] / factor);
                    if (delta > 0) value = builder_->createMul(value, context_->getConstantInt(context_->getIntegerType(64), factor));
                    else value = builder_->createDiv(value, context_->getConstantInt(context_->getIntegerType(64), factor));
                }
                if (src_scale == dst_scale && reg_int_values.count(inst.a)) reg_int_values[inst.dst] = reg_int_values[inst.a];
                if (dst_scale > 0) reg_decimal_scales[inst.dst] = dst_scale;
                store_reg(inst.dst, value, inst.result_type);
                break;
            }
            case LIR::LIR_Op::ToString: {
                LIR::Type a_type = reg_types.count(inst.a) ? reg_types[inst.a] : inst.type_a;
                if (a_type == LIR::Type::F64 || a_type == LIR::Type::F32) {
                    store_reg(inst.dst, FyraBuiltinFunctions::emit_float_to_str_inline(current_module_.get(), builder_.get(), load_float_reg(inst.a, inst.type_a)), LIR::Type::Ptr);
                } else {
                    store_reg(inst.dst, builder_->createExternCall("lymar_aot_format_argument",
                        {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a)},
                        context_->getIntegerType(64)), inst.result_type);
                }
                break;
            }
            case LIR::LIR_Op::STR_CONCAT: {
                FyraBuiltinFunctions::emit_str_concat_ir(current_module_.get(), builder_.get());
                ir::Function* fn = current_module_->getFunction("lm_str_concat");
                ir::Value* arg_a = load_reg(inst.a, inst.type_a);
                ir::Value* arg_b = load_reg(inst.b, inst.type_b);
                LIR::Type a_type = reg_types.count(inst.a) ? reg_types[inst.a] : inst.type_a;
                LIR::Type b_type = reg_types.count(inst.b) ? reg_types[inst.b] : inst.type_b;
                if (a_type == LIR::Type::F64 || a_type == LIR::Type::F32) {
                    arg_a = FyraBuiltinFunctions::emit_float_to_str_inline(current_module_.get(), builder_.get(), load_float_reg(inst.a, inst.type_a));
                }
                if (b_type == LIR::Type::F64 || b_type == LIR::Type::F32) {
                    arg_b = FyraBuiltinFunctions::emit_float_to_str_inline(current_module_.get(), builder_.get(), load_float_reg(inst.b, inst.type_b));
                }
                store_reg(inst.dst, builder_->createCall(fn, {arg_a, arg_b}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::STR_FORMAT: {
                used_builtins_.insert("lm_rt_str_format");
                ir::Function* fn = current_module_->getFunction("lm_rt_str_format");
                if (!fn) fn = builder_->createFunction("lm_rt_str_format", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                ir::Value* fmt_arg = load_reg(inst.a, inst.type_a);
                ir::Value* value_arg = load_reg(inst.b, inst.type_b);
                LIR::Type b_type = reg_types.count(inst.b) ? reg_types[inst.b] : inst.type_b;
                if (b_type != LIR::Type::Bool) {
                    auto it = lir_func.register_language_types.find(inst.b);
                    if (it != lir_func.register_language_types.end() && it->second && it->second->tag == ::TypeTag::Bool) {
                        b_type = LIR::Type::Bool;
                    } else {
                        auto it2 = lir_func.register_types.find(inst.b);
                        if (it2 != lir_func.register_types.end() && it2->second == LIR::Type::Bool) {
                            b_type = LIR::Type::Bool;
                        }
                    }
                }
                if (b_type == LIR::Type::F64 || b_type == LIR::Type::F32) {
                    value_arg = FyraBuiltinFunctions::emit_float_to_str_inline(current_module_.get(), builder_.get(), load_float_reg(inst.b, inst.type_b));
                } else if (reg_decimal_scales.count(inst.b) && reg_decimal_scales[inst.b] > 0) {
                    value_arg = FyraBuiltinFunctions::emit_decimal_to_str_inline(current_module_.get(), builder_.get(), value_arg, reg_decimal_scales[inst.b]);
                } else if (b_type == LIR::Type::Bool) {
                    value_arg = FyraBuiltinFunctions::emit_bool_to_str_inline(current_module_.get(), builder_.get(), value_arg);
                } else {
                    value_arg = builder_->createExternCall("lymar_aot_format_argument",
                        {tag_word(value_arg, inst.b, inst.type_b)},
                        context_->getIntegerType(64));
                }
                LIR::Type res_t = (inst.result_type != LIR::Type::Void) ? inst.result_type : LIR::Type::Ptr;
                store_reg(inst.dst, builder_->createCall(fn, {fmt_arg, value_arg}, lir_type_to_fyra_type(res_t)), res_t);
                break;
            }
            case LIR::LIR_Op::Param:
                builder_->createExternCall("lymar_aot_param_push", {load_reg(inst.dst, inst.result_type)}, nullptr);
                break;
            case LIR::LIR_Op::ConstructError: {
                ir::Value* payload = (inst.a != UINT32_MAX) ? tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a) : context_->getConstantInt(context_->getIntegerType(64), VAL_NIL);
                payload = builder_->createExternCall("lymar_aot_param_pop", {payload}, context_->getIntegerType(64));
                ir::Value* err_box = builder_->createExternCall("memory.alloc", {context_->getConstantInt(context_->getIntegerType(64), 32)}, context_->getIntegerType(64));
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0x4C594D41524F4B21LL), err_box);
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 1), builder_->createAdd(err_box, context_->getConstantInt(context_->getIntegerType(64), 8)));
                ir::Value* payload_addr = builder_->createAdd(err_box, context_->getConstantInt(context_->getIntegerType(64), 16));
                builder_->createStore(payload, payload_addr);
                // The payload slot always holds a tagged LmValue word
                // (tag_word output), so its kind is the erased domain —
                // word_kind(inst.a) would report the *source* scalar kind
                // and consumers would read the SMI tag bits as a raw int.
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 1), builder_->createAdd(err_box, context_->getConstantInt(context_->getIntegerType(64), 24)));
                store_reg(inst.dst, err_box, inst.result_type);
                break;
            }
            case LIR::LIR_Op::ConstructOk: {
                ir::Value* payload = tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a);
                ir::Value* ok_box = builder_->createExternCall("memory.alloc", {context_->getConstantInt(context_->getIntegerType(64), 32)}, context_->getIntegerType(64));
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0x4C594D41524F4B21LL), ok_box);
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), builder_->createAdd(ok_box, context_->getConstantInt(context_->getIntegerType(64), 8)));
                ir::Value* payload_addr = builder_->createAdd(ok_box, context_->getConstantInt(context_->getIntegerType(64), 16));
                builder_->createStore(payload, payload_addr);
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 1), builder_->createAdd(ok_box, context_->getConstantInt(context_->getIntegerType(64), 24)));
                store_reg(inst.dst, ok_box, inst.result_type);
                break;
            }
            case LIR::LIR_Op::IsError: {
                ir::Value* container = load_reg(inst.a, inst.type_a);
                store_reg(inst.dst, builder_->createExternCall("lymar_aot_union_is_error", {container}, context_->getIntegerType(64)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::Unwrap: {
                ir::Value* container = load_reg(inst.a, inst.type_a);
                ir::Value* unwrapped = builder_->createExternCall("lymar_aot_union_unwrap", {container}, context_->getIntegerType(64));
                unwrapped = untag_word(unwrapped, inst.dst, inst.result_type);
                store_reg(inst.dst, unwrapped, inst.result_type);
                break;
            }
            case LIR::LIR_Op::UnwrapOr: {
                ir::Value* container = load_reg(inst.a, inst.type_a);
                ir::Value* is_err = builder_->createExternCall("lymar_aot_union_is_error", {container}, context_->getIntegerType(64));

                ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                std::string uoid = std::to_string(label_counter_++);
                ir::BasicBlock* b_err = builder_->createBasicBlock("uor_err_" + uoid, cur_fn);
                ir::BasicBlock* b_ok  = builder_->createBasicBlock("uor_ok_" + uoid, cur_fn);
                ir::BasicBlock* b_done = builder_->createBasicBlock("uor_done_" + uoid, cur_fn);

                ir::Instruction* res_slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), context_->getIntegerType(64));
                builder_->createBr(is_err, b_err, b_ok);

                builder_->setInsertPoint(b_err);
                ir::Value* fallback = (inst.b != UINT32_MAX) ? load_reg(inst.b, inst.type_b) : context_->getConstantInt(context_->getIntegerType(64), VAL_NIL);
                builder_->createStore(fallback, res_slot);
                builder_->createJmp(b_done);

                builder_->setInsertPoint(b_ok);
                builder_->createStore(builder_->createExternCall("lymar_aot_union_unwrap", {container}, context_->getIntegerType(64)), res_slot);
                builder_->createJmp(b_done);

                builder_->setInsertPoint(b_done);
                ir::Value* unwrapped = builder_->createLoadl(res_slot);
                unwrapped = untag_word(unwrapped, inst.dst, inst.result_type);
                store_reg(inst.dst, unwrapped, inst.result_type);
                break;
            }
            case LIR::LIR_Op::ListCreate: {
                used_builtins_.insert("lm_list_new");
                ir::Function* fn = current_module_->getFunction("lm_list_new");
                if (!fn) fn = builder_->createFunction("lm_list_new", context_->getIntegerType(64), {context_->getIntegerType(64)});
                ir::Value* new_list = builder_->createCall(fn, {context_->getConstantInt(context_->getIntegerType(64), (long long)inst.imm)});
                uint64_t elem_kind = typed_list_element_kind(inst.dst);
                if (elem_kind)
                    builder_->createExternCall("lymar_aot_list_set_element_kind",
                        {new_list, context_->getConstantInt(context_->getIntegerType(64), elem_kind)}, context_->getVoidType());
                store_reg(inst.dst, new_list, inst.result_type);
                break;
            }
            case LIR::LIR_Op::ListAppend: {
                ir::Value* list_val = load_reg(inst.a, inst.type_a);
                ir::Value* elem_val = load_reg(inst.b, inst.type_b);
                uint64_t elem_kind = typed_list_element_kind(inst.a);
                if (elem_kind)
                    builder_->createExternCall("lymar_aot_list_set_element_kind",
                        {list_val, context_->getConstantInt(context_->getIntegerType(64), elem_kind)}, context_->getVoidType());
                // A typed-primitive list still needs the kind-aware append when
                // the appended register holds a tagged LmValue word (erased
                // `any`/union element): storing it raw would leak SMI/box tag
                // bits into the raw element slot.
                if (!is_typed_primitive_list(inst.a) || lang_type_holds_tagged_word(inst.b)) {
                    elem_val = tag_word(elem_val, inst.b, inst.type_b);
                    builder_->createExternCall("lymar_aot_list_append_tagged", {list_val, elem_val}, context_->getVoidType());
                } else if (elem_kind == 3) {
                    // Raw f64 storage: pass the double directly so the runtime
                    // stores IEEE-754 bits with no box and no edge barrier.
                    ir::Value* fval = elem_val;
                    if (fval->getType() != context_->getDoubleType())
                        fval = builder_->createCast(fval, context_->getDoubleType());
                    builder_->createExternCall("lymar_aot_list_append_f64", {list_val, fval}, context_->getVoidType());
                } else {
                    builder_->createExternCall("lymar_aot_list_append", {list_val, elem_val}, context_->getVoidType());
                }
                hoisted_data_ptrs.erase(inst.a);
                break;
            }
            case LIR::LIR_Op::ListIndex: {
                ir::Value* list_val = load_reg(inst.a, inst.type_a);
                ir::Value* idx_val = load_reg(inst.b, inst.type_b);
                if (std::getenv("LYMAR_DEBUG_LIDX")) {
                    builder_->createExternCall("lymar_aot_dbg_lidx", {list_val, idx_val}, context_->getVoidType());
                }
                std::string lidx_id = std::to_string(label_counter_++);

                // Bound-proven hint (iter loops): skip the null/type/bounds
                // CFG and lm_list_get fallback — the loop header re-reads
                // ListLen and compares index < len immediately before each
                // fetch, so 0 <= index < len always holds. Registers with a
                // hoisted entry-block data pointer reuse it; everyone else
                // re-loads the header field per access so mid-loop mutation
                // through calls stays correct.
                const bool bound_proven = (inst.imm & 0x1u) != 0u;
                // The unchecked primitive load is only sound for bound-proven
                // accesses: without the hint an out-of-range index must fall
                // through to the bounds CFG below (VM parity: xs[10] -> nil).
                if (bound_proven && (hoisted_data_ptrs.count(inst.a) || is_typed_primitive_list(inst.a))) {
                    if (std::getenv("LYMAR_DEBUG_LIDX")) {
                        builder_->createExternCall("lymar_aot_dbg_lidx", {list_val, idx_val}, context_->getVoidType());
                    }
                    ir::Value* data_ptr = nullptr;
                    if (hoisted_data_ptrs.count(inst.a)) {
                        data_ptr = hoisted_data_ptrs[inst.a];
                    } else {
                        // Fresh load per access: a lazily cached SSA value
                        // defined inside a loop body is not guaranteed to
                        // dominate later uses in sibling blocks, and an
                        // entry-block hoist is unsound when the function can
                        // mutate the list through a call (see may_mutate_lists).
                        ir::Value* unboxed = builder_->createAnd(list_val, context_->getConstantInt(context_->getIntegerType(64), ~7ULL));
                        data_ptr = builder_->createLoadl(builder_->createAdd(unboxed, context_->getConstantInt(context_->getIntegerType(64), 8)));
                    }
                    ir::Value* offset = builder_->createMul(idx_val, context_->getConstantInt(context_->getIntegerType(64), 8));
                    ir::Value* elem_addr = builder_->createAdd(data_ptr, offset);
                    // Kind-3 ([float]/[f64]) lists store raw IEEE-754 doubles:
                    // load them as f64 directly — no decode call, no box, and
                    // erased destinations re-box through lymar_aot_box_float.
                    if (typed_list_element_kind(inst.a) == 3) {
                        ir::Instruction* felem = builder_->createLoadd(elem_addr);
                        felem->setName("scalar_elem_" + lidx_id);
                        if (lang_type_holds_tagged_word(inst.dst)) {
                            ir::Value* boxed = builder_->createExternCall("lymar_aot_box_float",
                                {felem}, context_->getIntegerType(64));
                            store_reg(inst.dst, boxed, inst.result_type);
                        } else {
                            store_reg(inst.dst, felem, LIR::Type::F64);
                        }
                        break;
                    }
                    ir::Instruction* elem = builder_->createLoadl(elem_addr);
                    elem->setName("scalar_elem_" + lidx_id);
                    // The typed-primitive fast path loads the raw unboxed word.
                    // Stamp the destination with the element's real scalar kind
                    // so downstream consumers (print, arithmetic) do not treat
                    // an integer word as an object pointer and misclassify it
                    // (e.g. value 1 rendering as "true", 2 as "nil").
                    LIR::Type elem_type = inst.result_type;
                    auto lit = lir_func.register_language_types.find(inst.a);
                    if (lit != lir_func.register_language_types.end() && lit->second &&
                        lit->second->tag == ::TypeTag::List) {
                        if (auto* lt = std::get_if<ListType>(&lit->second->extra); lt && lt->elementType) {
                            switch (lt->elementType->tag) {
                                case ::TypeTag::Int:
                                case ::TypeTag::Int8: case ::TypeTag::Int16:
                                case ::TypeTag::Int32: case ::TypeTag::Int64:
                                case ::TypeTag::UInt:
                                case ::TypeTag::UInt8: case ::TypeTag::UInt16:
                                case ::TypeTag::UInt32: case ::TypeTag::UInt64:
                                    elem_type = LIR::Type::I64; break;
                                case ::TypeTag::Float32:
                                case ::TypeTag::Float64:
                                    elem_type = LIR::Type::F64; break;
                                default: break;
                            }
                        }
                    }
                    if (elem_type == LIR::Type::F64 || elem_type == LIR::Type::F32) {
                        ir::Value* fval = builder_->createExternCall("lymar_aot_to_float", {elem}, context_->getDoubleType());
                        store_reg(inst.dst, fval, elem_type);
                    } else if (lang_type_holds_tagged_word(inst.dst)) {
                        // Erased destination: the raw stored element must cross
                        // the boundary as a tagged LmValue word.
                        uint64_t ekind = typed_list_element_kind(inst.a);
                        ir::Value* decoded = builder_->createExternCall("lymar_aot_list_elem_decode",
                            {elem, context_->getConstantInt(context_->getIntegerType(64), ekind)}, context_->getIntegerType(64));
                        store_reg(inst.dst, decoded, inst.result_type);
                    } else {
                        store_reg(inst.dst, elem, elem_type);
                    }
                    break;
                }

                if (bound_proven) {
                    // Straight-line fetch: the producer proved 0 <= index < len
                    // for this access (iter loop header re-reads ListLen and
                    // compares immediately before the fetch; stream_fusion
                    // rejects mutating pipelines), so the null/type/bounds CFG
                    // and lm_list_get fallback are dead weight. Element-storage
                    // kind still gates decoding: kind 0 (tagged-word storage —
                    // every non-primitive list) is the identity decode, while
                    // kinds 1/2 (raw int/bool) still need the runtime helper.
                    ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                    ir::BasicBlock* b_k0 = builder_->createBasicBlock("lidx_pb_k0_" + lidx_id, cur_fn);
                    ir::BasicBlock* b_dec = builder_->createBasicBlock("lidx_pb_dec_" + lidx_id, cur_fn);
                    ir::BasicBlock* b_pdone = builder_->createBasicBlock("lidx_pb_done_" + lidx_id, cur_fn);

                    ir::Value* unboxed = builder_->createAnd(list_val, context_->getConstantInt(context_->getIntegerType(64), ~7ULL));
                    ir::Instruction* hdr_val = builder_->createLoadl(unboxed);
                    hdr_val->setName("lpb_hdr_" + lidx_id);
                    ir::Value* elem_kind = builder_->createShr(hdr_val, context_->getConstantInt(context_->getIntegerType(64), 32));
                    ir::Value* data_ptr = builder_->createLoadl(builder_->createAdd(unboxed, context_->getConstantInt(context_->getIntegerType(64), 8)));
                    ir::Value* offset = builder_->createMul(idx_val, context_->getConstantInt(context_->getIntegerType(64), 8));
                    ir::Value* elem_addr = builder_->createAdd(data_ptr, offset);
                    ir::Instruction* elem = builder_->createLoadl(elem_addr);
                    elem->setName("lpb_elem_" + lidx_id);

                    ir::Value* is_tagged = builder_->createCeq(elem_kind, context_->getConstantInt(context_->getIntegerType(64), 0));
                    builder_->createBr(is_tagged, b_k0, b_dec);

                    builder_->setInsertPoint(b_k0);
                    store_reg(inst.dst, untag_word(elem, inst.dst, inst.result_type), inst.result_type);
                    builder_->createJmp(b_pdone);

                    builder_->setInsertPoint(b_dec);
                    ir::Value* decoded = builder_->createExternCall("lymar_aot_list_elem_decode",
                        {elem, elem_kind}, context_->getIntegerType(64));
                    store_reg(inst.dst, untag_word(decoded, inst.dst, inst.result_type), inst.result_type);
                    builder_->createJmp(b_pdone);

                    builder_->setInsertPoint(b_pdone);
                    break;
                }

                used_builtins_.insert("lm_list_get");
                ir::Function* fn = current_module_->getFunction("lm_list_get");
                if (!fn) fn = builder_->createFunction("lm_list_get", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});

                ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                ir::BasicBlock* b_chk_hdr = builder_->createBasicBlock("lidx_chk_hdr_" + lidx_id, cur_fn);
                ir::BasicBlock* b_fast = builder_->createBasicBlock("lidx_fast_" + lidx_id, cur_fn);
                ir::BasicBlock* b_slow = builder_->createBasicBlock("lidx_slow_" + lidx_id, cur_fn);
                ir::BasicBlock* b_done = builder_->createBasicBlock("lidx_done_" + lidx_id, cur_fn);

                // Step 1: Check non-null and non-nil before unboxing pointer
                ir::Value* is_not_null = builder_->createCne(list_val, context_->getConstantInt(context_->getIntegerType(64), 0));
                ir::Value* is_not_nil = builder_->createCne(list_val, context_->getConstantInt(context_->getIntegerType(64), VAL_NIL));
                ir::Value* is_valid_ptr = builder_->createAnd(is_not_null, is_not_nil);

                builder_->createBr(is_valid_ptr, b_chk_hdr, b_slow);

                // Step 2: In b_chk_hdr, safely unbox pointer, load header type_id and size
                builder_->setInsertPoint(b_chk_hdr);
                ir::Value* unboxed_ptr = builder_->createAnd(list_val, context_->getConstantInt(context_->getIntegerType(64), ~7ULL));
                ir::Instruction* hdr_val = builder_->createLoadl(unboxed_ptr);
                hdr_val->setName("scalar_hdr_" + lidx_id);
                ir::Value* type_id = builder_->createAnd(hdr_val, context_->getConstantInt(context_->getIntegerType(64), 0xFFFFFFFF));
                ir::Value* is_list_type = builder_->createCeq(type_id, context_->getConstantInt(context_->getIntegerType(64), TYPE_LIST));

                ir::Value* size_addr = builder_->createAdd(unboxed_ptr, context_->getConstantInt(context_->getIntegerType(64), 16));
                ir::Instruction* list_size = builder_->createLoadl(size_addr);
                list_size->setName("scalar_size_" + lidx_id);
                ir::Value* non_neg = builder_->createCsge(idx_val, context_->getConstantInt(context_->getIntegerType(64), 0));
                ir::Value* in_upper = builder_->createCslt(idx_val, list_size);
                ir::Value* valid_idx = builder_->createAnd(non_neg, in_upper);

                ir::Value* is_fast = builder_->createAnd(is_list_type, valid_idx);
                builder_->createBr(is_fast, b_fast, b_slow);

                // Step 3: Fast path array access
                builder_->setInsertPoint(b_fast);
                ir::Value* data_addr = builder_->createAdd(unboxed_ptr, context_->getConstantInt(context_->getIntegerType(64), 8));
                ir::Instruction* data_ptr = builder_->createLoadl(data_addr);
                data_ptr->setName("lidx_data_ptr_" + lidx_id);
                ir::Value* offset = builder_->createMul(idx_val, context_->getConstantInt(context_->getIntegerType(64), 8));
                ir::Value* elem_addr = builder_->createAdd(data_ptr, offset);
                ir::Instruction* elem = builder_->createLoadl(elem_addr);
                elem->setName("lidx_elem_" + lidx_id);
                // Primitive-storage lists keep raw int/bool elements; decode them
                // into tagged LmValue words using the header's element kind before
                // the destination-domain untag decides the final representation.
                // Kind 0 (tagged-word storage) is the identity decode, so the
                // common erased-view case skips the extern call entirely.
                ir::Value* elem_kind = builder_->createShr(hdr_val, context_->getConstantInt(context_->getIntegerType(64), 32));
                ir::BasicBlock* b_k0 = builder_->createBasicBlock("lidx_k0_" + lidx_id, cur_fn);
                ir::BasicBlock* b_dec = builder_->createBasicBlock("lidx_dec_" + lidx_id, cur_fn);
                ir::BasicBlock* b_fused = builder_->createBasicBlock("lidx_fused_" + lidx_id, cur_fn);
                ir::Value* is_tagged = builder_->createCeq(elem_kind, context_->getConstantInt(context_->getIntegerType(64), 0));
                builder_->createBr(is_tagged, b_k0, b_dec);

                builder_->setInsertPoint(b_k0);
                store_reg(inst.dst, untag_word(elem, inst.dst, inst.result_type), inst.result_type);
                builder_->createJmp(b_fused);

                builder_->setInsertPoint(b_dec);
                ir::Value* decoded = builder_->createExternCall("lymar_aot_list_elem_decode",
                    {elem, elem_kind}, context_->getIntegerType(64));
                store_reg(inst.dst, untag_word(decoded, inst.dst, inst.result_type), inst.result_type);
                builder_->createJmp(b_fused);

                builder_->setInsertPoint(b_fused);
                builder_->createJmp(b_done);

                // Step 4: Slow path fallback
                builder_->setInsertPoint(b_slow);
                ir::Value* slow_res = builder_->createCall(fn, {list_val, idx_val});
                slow_res = untag_word(slow_res, inst.dst, inst.result_type);
                store_reg(inst.dst, slow_res, inst.result_type);
                builder_->createJmp(b_done);

                builder_->setInsertPoint(b_done);
                break;
            }
            case LIR::LIR_Op::ListSet: {
                ir::Value* list_val = load_reg(inst.dst, inst.result_type);
                ir::Value* idx_val = load_reg(inst.a, inst.type_a);
                ir::Value* elem_val = load_reg(inst.b, inst.type_b);
                std::string lset_id = std::to_string(label_counter_++);

                // Bound-proven store (imm&1): the range-loop header re-reads
                // ListLen and compares index < len immediately before the
                // body, and the generator proved neither register is
                // rewritten in between, so 0 <= index < len always holds —
                // the null/type/bounds CFG is dead weight. Storage kind still
                // gates encoding: typed-primitive ([int]/[bool]) lists take a
                // straight raw store with no edge; everything else dispatches
                // on the header's element kind — kind 0 stores the tagged
                // LmValue word (edge barrier preserved for heap refs), kinds
                // 1/2 go through the kind-aware encode helper.
                if ((inst.imm & 0x1u) != 0u) {
                    ir::Value* unboxed = builder_->createAnd(list_val,
                        context_->getConstantInt(context_->getIntegerType(64), ~7ULL));
                    auto proven_data_ptr = [&]() -> ir::Value* {
                        auto hit = hoisted_data_ptrs.find(inst.dst);
                        if (hit != hoisted_data_ptrs.end()) return hit->second;
                        return builder_->createLoadl(builder_->createAdd(unboxed,
                            context_->getConstantInt(context_->getIntegerType(64), 8)));
                    };
                    if (is_typed_primitive_list(inst.dst) && !lang_type_holds_tagged_word(inst.b)) {
                        ir::Value* data_ptr = proven_data_ptr();
                        ir::Value* offset = builder_->createMul(idx_val,
                            context_->getConstantInt(context_->getIntegerType(64), 8));
                        ir::Value* elem_addr = builder_->createAdd(data_ptr, offset);
                        if (auto* add_inst = dynamic_cast<ir::Instruction*>(elem_addr))
                            add_inst->setName("scalar_elem_" + lset_id);
                        ir::Value* raw = elem_val;
                        auto* raw_ty = raw->getType();
                        if (raw_ty == context_->getFloatType())
                            raw = builder_->createCast(raw, context_->getDoubleType());
                        else if (raw_ty != context_->getDoubleType() &&
                                 raw_ty != context_->getIntegerType(64))
                            raw = builder_->createCast(raw, context_->getIntegerType(64));
                        auto* store_inst = builder_->createStore(raw, elem_addr);
                        store_inst->setName("scalar_store_" + lset_id);
                        break;
                    }
                    ir::Instruction* hdr_val = builder_->createLoadl(unboxed);
                    hdr_val->setName("scalar_hdr_set_" + lset_id);
                    ir::Value* elem_kind = builder_->createShr(hdr_val,
                        context_->getConstantInt(context_->getIntegerType(64), 32));
                    ir::Value* data_ptr = proven_data_ptr();
                    ir::Value* offset = builder_->createMul(idx_val,
                        context_->getConstantInt(context_->getIntegerType(64), 8));
                    ir::Value* elem_addr = builder_->createAdd(data_ptr, offset);
                    ir::Value* tagged = tag_word(elem_val, inst.b, inst.type_b);

                    ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                    ir::BasicBlock* b_tag = builder_->createBasicBlock("lset_pb_tag_" + lset_id, cur_fn);
                    ir::BasicBlock* b_enc = builder_->createBasicBlock("lset_pb_enc_" + lset_id, cur_fn);
                    ir::BasicBlock* b_done = builder_->createBasicBlock("lset_pb_done_" + lset_id, cur_fn);
                    ir::Value* is_tagged_kind = builder_->createCeq(elem_kind,
                        context_->getConstantInt(context_->getIntegerType(64), 0));
                    builder_->createBr(is_tagged_kind, b_tag, b_enc);

                    builder_->setInsertPoint(b_tag);
                    // Unnamed store: region lowering emits the edge barrier,
                    // which tagged heap references (boxed floats, strings,
                    // frames) still require.
                    builder_->createStore(tagged, elem_addr);
                    builder_->createJmp(b_done);

                    builder_->setInsertPoint(b_enc);
                    builder_->createExternCall("lymar_aot_list_elem_store",
                        {elem_addr, tagged, elem_kind}, context_->getVoidType());
                    builder_->createJmp(b_done);

                    builder_->setInsertPoint(b_done);
                    break;
                }

                // Set may fall through to lm_list_set which reallocates; drop any
                // cached data_ptr for this register so a subsequent ListIndex
                // re-loads from the (possibly new) header. (The bound-proven
                // path above stores in place and never reallocates.)
                hoisted_data_ptrs.erase(inst.dst);

                // Unproven stores always take the bounds-checked CFG below:
                // the raw typed-primitive store is only sound when the
                // producer proved 0 <= index < len (handled above), because
                // an out-of-range store must reach lm_list_set's grow path —
                // a bare data+idx*8 write would silently corrupt or drop the
                // length update.
                used_builtins_.insert("lm_list_set");
                ir::Function* fn = current_module_->getFunction("lm_list_set");
                if (!fn) fn = builder_->createFunction("lm_list_set", context_->getVoidType(), {context_->getIntegerType(64), context_->getIntegerType(64), context_->getIntegerType(64)});

                ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                ir::BasicBlock* b_chk_hdr = builder_->createBasicBlock("lset_chk_hdr_" + lset_id, cur_fn);
                ir::BasicBlock* b_fast = builder_->createBasicBlock("lset_fast_" + lset_id, cur_fn);
                ir::BasicBlock* b_slow = builder_->createBasicBlock("lset_slow_" + lset_id, cur_fn);
                ir::BasicBlock* b_done = builder_->createBasicBlock("lset_done_" + lset_id, cur_fn);

                // Step 1: Check non-null and non-nil before unboxing pointer
                ir::Value* is_not_null = builder_->createCne(list_val, context_->getConstantInt(context_->getIntegerType(64), 0));
                ir::Value* is_not_nil = builder_->createCne(list_val, context_->getConstantInt(context_->getIntegerType(64), VAL_NIL));
                ir::Value* is_valid_ptr = builder_->createAnd(is_not_null, is_not_nil);

                builder_->createBr(is_valid_ptr, b_chk_hdr, b_slow);

                // Step 2: Unbox ptr & inspect header / size safely
                builder_->setInsertPoint(b_chk_hdr);
                ir::Value* unboxed_ptr = builder_->createAnd(list_val, context_->getConstantInt(context_->getIntegerType(64), ~7ULL));
                ir::Instruction* hdr_val = builder_->createLoadl(unboxed_ptr);
                hdr_val->setName("scalar_hdr_set_" + lset_id);
                ir::Value* type_id = builder_->createAnd(hdr_val, context_->getConstantInt(context_->getIntegerType(64), 0xFFFFFFFF));
                ir::Value* is_list_type = builder_->createCeq(type_id, context_->getConstantInt(context_->getIntegerType(64), TYPE_LIST));

                ir::Value* size_addr = builder_->createAdd(unboxed_ptr, context_->getConstantInt(context_->getIntegerType(64), 16));
                ir::Instruction* list_size = builder_->createLoadl(size_addr);
                list_size->setName("scalar_size_set_" + lset_id);
                ir::Value* non_neg = builder_->createCsge(idx_val, context_->getConstantInt(context_->getIntegerType(64), 0));
                ir::Value* in_upper = builder_->createCslt(idx_val, list_size);
                ir::Value* valid_idx = builder_->createAnd(non_neg, in_upper);

                ir::Value* is_fast = builder_->createAnd(is_list_type, valid_idx);
                builder_->createBr(is_fast, b_fast, b_slow);

                // Step 3: Fast path array store
                builder_->setInsertPoint(b_fast);
                ir::Value* data_addr = builder_->createAdd(unboxed_ptr, context_->getConstantInt(context_->getIntegerType(64), 8));
                ir::Instruction* data_ptr = builder_->createLoadl(data_addr);
                data_ptr->setName("lset_data_ptr_" + lset_id);
                ir::Value* offset = builder_->createMul(idx_val, context_->getConstantInt(context_->getIntegerType(64), 8));
                ir::Value* elem_addr = builder_->createAdd(data_ptr, offset);

                bool is_scalar_elem = is_typed_primitive_list(inst.dst) && !lang_type_holds_tagged_word(inst.b);

                if (is_scalar_elem) {
                    if (auto* add_inst = dynamic_cast<ir::Instruction*>(elem_addr)) {
                        add_inst->setName("scalar_elem_" + lset_id);
                    }
                    auto* store_inst = builder_->createStore(elem_val, elem_addr);
                    store_inst->setName("scalar_store_" + lset_id);
                } else {
                    // Erased-view write: encode the tagged value into the list's
                    // element-storage kind (raw int/bool for primitive lists,
                    // tagged word otherwise) and record edges only for tagged
                    // heap references.
                    ir::Value* elem_kind = builder_->createShr(hdr_val, context_->getConstantInt(context_->getIntegerType(64), 32));
                    builder_->createExternCall("lymar_aot_list_elem_store",
                        {elem_addr, tag_word(elem_val, inst.b, inst.type_b), elem_kind}, context_->getVoidType());
                }
                builder_->createJmp(b_done);

                // Step 4: Slow path
                builder_->setInsertPoint(b_slow);
                builder_->createCall(fn, {list_val, idx_val, tag_word(elem_val, inst.b, inst.type_b)});
                builder_->createJmp(b_done);

                builder_->setInsertPoint(b_done);
                break;
            }
            case LIR::LIR_Op::StringIndex: {
                // region_lowering converts index operands with
                // lymar_aot_string_index, which expects a tagged LmValue —
                // raw scalar ints must be SMI-tagged here first.
                ir::Value* idx_word = tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b);
                if (inst.result_type == LIR::Type::Ptr) {
                    FyraBuiltinFunctions::emit_substring_ir(current_module_.get(), builder_.get());
                    ir::Function* fn = current_module_->getFunction("_builtin_substring");
                    ir::Value* idx_val = load_reg(inst.b, inst.type_b);
                    ir::Value* end_val = builder_->createAdd(idx_val, context_->getConstantInt(context_->getIntegerType(64), 1));
                    store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), idx_word,
                        tag_word(end_val, inst.b, inst.type_b)}), LIR::Type::Ptr);
                } else {
                    used_builtins_.insert("_builtin_string_byte_at");
                    ir::Function* fn = current_module_->getFunction("_builtin_string_byte_at");
                    if (!fn) fn = builder_->createFunction("_builtin_string_byte_at", context_->getIntegerType(64), {context_->getPointerType(context_->getIntegerType(8)), context_->getIntegerType(64)});
                    store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), idx_word}), inst.result_type);
                }
                break;
            }
            case LIR::LIR_Op::ListLen: {
                // Inline the lm_list_len body: unbox the tagged word and load
                // the header size field at +16. The builtin performs no type
                // checks, so this is semantically identical but avoids a call
                // per iteration in `iter` loops (ListLen is re-emitted in the
                // loop header to preserve live-view semantics).
                used_builtins_.insert("lm_list_len");
                ir::Value* raw = load_reg(inst.a, inst.type_a);
                ir::Value* unboxed = builder_->createAnd(raw, context_->getConstantInt(context_->getIntegerType(64), ~7ULL));
                ir::Value* len_addr = builder_->createAdd(unboxed, context_->getConstantInt(context_->getIntegerType(64), 16));
                ir::Instruction* len = builder_->createLoadl(len_addr);
                len->setName("list_len_" + std::to_string(label_counter_++));
                store_reg(inst.dst, len, inst.result_type);
                break;
            }
            case LIR::LIR_Op::TupleCreate: {
                // Virtual tuple: keep elements in scalar slots. Element domains
                // come from the tuple's declared language type; without it the
                // real heap tuple is required.
                auto lt = lir_func.register_language_types.find(inst.dst);
                if (lt != lir_func.register_language_types.end() && lt->second &&
                    lt->second->tag == ::TypeTag::Tuple) {
                    auto* tt = std::get_if<TupleType>(&lt->second->extra);
                    if (tt && !tt->elementTypes.empty() && tt->elementTypes.size() <= 8) {
                        std::vector<VTupleElem> elems(tt->elementTypes.size());
                        bool ok = true;
                        for (size_t ei = 0; ei < elems.size(); ++ei) {
                            int d = vdom_of_type(tt->elementTypes[ei]);
                            if (d == VDOM_INVALID) { ok = false; break; }
                            elems[ei].domain = d;
                        }
                        if (ok) {
                            if (vt_info.canon_regs.count(inst.dst))
                                vtuples[inst.dst] = canon_elems(inst.dst);
                            else
                                vtuples[inst.dst] = std::move(elems);
                            break;
                        }
                    }
                }
                used_builtins_.insert("lm_tuple_new");
                ir::Function* fn = current_module_->getFunction("lm_tuple_new");
                if (!fn) fn = builder_->createFunction("lm_tuple_new", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {context_->getConstantInt(context_->getIntegerType(64), (long long)inst.imm)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::TupleSet: {
                if (vtuples.count(inst.dst)) {
                    int64_t idx = const_index_of(inst.a);
                    if (std::getenv("LYMAR_DEBUG_VT") && inst.dst == 2)
                        std::cerr << "[VT] TupleSet dst=r" << inst.dst << " idx=" << idx
                                  << " a=" << inst.a << " b=" << inst.b << "\n";
                    if (idx >= 0 && static_cast<size_t>(idx) < vtuples[inst.dst].size()) {
                        // A tuple-typed value stored into a tuple is itself a
                        // pointer-domain element; materialize nested vtuples.
                        if (vtuples.count(inst.b)) materialize_vtuple(inst.b);
                        int dom = vdom_of_reg(inst.b, inst.type_b);
                        // Canonical spill slot: capture the value immediately;
                        // element stability of the source register is
                        // irrelevant because the slot holds the value itself.
                        auto ci = vt_info.canon_regs.find(inst.dst);
                        if (ci != vt_info.canon_regs.end() &&
                            static_cast<size_t>(idx) < ci->second.size() &&
                            dom == vt_info.canon_domains.at(inst.dst)[static_cast<size_t>(idx)]) {
                            canon_store_val(inst.dst, static_cast<size_t>(idx),
                                load_reg(inst.b, inst.type_b));
                            break;
                        }
                        if (std::getenv("LYMAR_DEBUG_VT") && inst.dst == 2)
                            std::cerr << "[VT]   dom=" << dom << " stable=" << elem_src_stable(inst.b)
                                      << " type_b=" << (int)inst.type_b << "\n";
                        if (dom != VDOM_INVALID && elem_src_stable(inst.b)) {
                            auto& slot = vtuples[inst.dst][static_cast<size_t>(idx)];
                            slot.src_reg = inst.b;
                            slot.src_type = (inst.type_b != LIR::Type::Void) ? inst.type_b
                                : (reg_types.count(inst.b) ? reg_types[inst.b] : LIR::Type::I64);
                            slot.domain = dom;
                            slot.has = true;
                            slot.direct_v = nullptr;
                            break;
                        }
                        materialize_vtuple(inst.dst);
                        // Fall through: emit the real lm_tuple_set on the
                        // materialized tuple.
                    }
                    materialize_vtuple(inst.dst);
                }
                used_builtins_.insert("lm_tuple_set");
                ir::Function* fn = current_module_->getFunction("lm_tuple_set");
                if (!fn) fn = builder_->createFunction("lm_tuple_set", context_->getVoidType(), {context_->getIntegerType(64), context_->getIntegerType(64), context_->getIntegerType(64)});
                ir::Value* val = tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b);
                builder_->createCall(fn, {load_reg(inst.dst, inst.result_type), load_reg(inst.a, inst.type_a), val});
                break;
            }
            case LIR::LIR_Op::TupleGet: {
                if (vtuples.count(inst.a)) {
                    int64_t idx = const_index_of(inst.b);
                    if (idx >= 0 && static_cast<size_t>(idx) < vtuples[inst.a].size()) {
                        const auto& e = vtuples[inst.a][static_cast<size_t>(idx)];
                        if (e.has) {
                            store_reg(inst.dst, velem_value(e), inst.result_type);
                            break;
                        }
                        // Unset element: real tuples read uninitialized
                        // memory; emit a typed zero instead.
                        ir::Value* zv = (e.domain == VDOM_FLOAT)
                            ? static_cast<ir::Value*>(context_->getConstantFP(context_->getDoubleType(), 0.0))
                            : static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64), 0));
                        store_reg(inst.dst, zv, inst.result_type);
                        break;
                    }
                    materialize_vtuple(inst.a);
                }
                used_builtins_.insert("lm_tuple_get");
                ir::Function* fn = current_module_->getFunction("lm_tuple_get");
                if (!fn) fn = builder_->createFunction("lm_tuple_get", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                ir::Value* raw = builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}, context_->getIntegerType(64));
                raw = untag_word(raw, inst.dst, inst.result_type);
                store_reg(inst.dst, raw, inst.result_type);
                break;
            }
            case LIR::LIR_Op::TupleLen: {
                if (vtuples.count(inst.a)) {
                    store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64),
                        static_cast<long long>(vtuples[inst.a].size())), inst.result_type);
                    break;
                }
                // Canonical tuple header: kind, elements, size, capacity.
                ir::Value* len = builder_->createExternCall("lymar_aot_tuple_length",
                    {load_reg(inst.a, inst.type_a)}, context_->getIntegerType(64));
                store_reg(inst.dst, len, inst.result_type);
                break;
            }
            case LIR::LIR_Op::ProbeKind: {
                ir::Value* kind = builder_->createExternCall("lymar_aot_probe_kind",
                    {load_reg(inst.a, inst.type_a)}, context_->getIntegerType(64));
                store_reg(inst.dst, kind, inst.result_type);
                break;
            }
            case LIR::LIR_Op::DictCreate: {
                used_builtins_.insert("lm_dict_new");
                ir::Function* fn = current_module_->getFunction("lm_dict_new");
                if (!fn) fn = builder_->createFunction("lm_dict_new", context_->getIntegerType(64), {});
                auto* dictionary = builder_->createCall(fn, {}, lir_type_to_fyra_type(inst.result_type));
                store_reg(inst.dst, builder_->createExternCall("lymar_aot_mark_dictionary", {dictionary}, context_->getIntegerType(64)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::DictSet: {
                used_builtins_.insert("lm_dict_set");
                ir::Function* fn = current_module_->getFunction("lm_dict_set");
                if (!fn) fn = builder_->createFunction("lm_dict_set", context_->getVoidType(), {context_->getIntegerType(64), context_->getIntegerType(64), context_->getIntegerType(64)});
                ir::Value* key = tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a);
                ir::Value* val = tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b);
                builder_->createCall(fn, {load_reg(inst.dst, inst.result_type), key, val});
                break;
            }
            case LIR::LIR_Op::DictGet: {
                used_builtins_.insert("lm_dict_get");
                ir::Function* fn = current_module_->getFunction("lm_dict_get");
                if (!fn) fn = builder_->createFunction("lm_dict_get", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                ir::Value* key = tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b);
                ir::Value* raw = builder_->createCall(fn, {load_reg(inst.a, inst.type_a), key}, context_->getIntegerType(64));
                raw = untag_word(raw, inst.dst, inst.result_type);
                store_reg(inst.dst, raw, inst.result_type, true);
                break;
            }
            case LIR::LIR_Op::DictLen: {
                ir::Value* count = builder_->createLoadl(load_reg(inst.a, inst.type_a));
                store_reg(inst.dst, count, inst.result_type);
                break;
            }
            case LIR::LIR_Op::DictHas: {
                used_builtins_.insert("lm_dict_has");
                ir::Function* fn = current_module_->getFunction("lm_dict_has");
                if (!fn) fn = builder_->createFunction("lm_dict_has", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                ir::Value* key = tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b);
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), key}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::DictItems: {
                used_builtins_.insert("lm_dict_items");
                uint32_t dict_reg = (inst.a != UINT32_MAX && inst.a != 0) ? inst.a : (!inst.call_args.empty() ? inst.call_args[0] : UINT32_MAX);
                ir::Function* fn = current_module_->getFunction("lm_dict_items");
                if (!fn) fn = builder_->createFunction("lm_dict_items", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(dict_reg, LIR::Type::Ptr)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::MakeEnum: {
                used_builtins_.insert("lm_enum_new");
                ir::Function* fn = current_module_->getFunction("lm_enum_new");
                if (!fn) fn = builder_->createFunction("lm_enum_new", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64), context_->getIntegerType(64)});
                ir::Value* tag_val = context_->getConstantInt(context_->getIntegerType(64), static_cast<long long>(inst.imm));
                ir::Value* payload_val = (inst.a != UINT32_MAX) ? load_reg(inst.a, inst.type_a) : builder_->createExternCall("lymar_aot_nil", {}, context_->getIntegerType(64));
                if (inst.a != UINT32_MAX && (inst.type_a == LIR::Type::F64 || inst.type_a == LIR::Type::F32)) {
                    payload_val = builder_->createCast(payload_val, context_->getIntegerType(64));
                }
                ir::GlobalVariable* vname_gv = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "vname_" + inst.func_name, inst.func_name);
                auto* variant_name = builder_->createExternCall("lymar_aot_copy_constant", {vname_gv,
                    context_->getConstantInt(context_->getIntegerType(64), 24 + inst.func_name.size() + 1)}, context_->getIntegerType(64));
                store_reg(inst.dst, builder_->createCall(fn, {tag_val, payload_val, variant_name}), inst.result_type);
                break;
            }
            case LIR::LIR_Op::GetTag: {
                used_builtins_.insert("lm_enum_tag");
                ir::Function* fn = current_module_->getFunction("lm_enum_tag");
                if (!fn) fn = builder_->createFunction("lm_enum_tag", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a)}), inst.result_type);
                break;
            }
            case LIR::LIR_Op::GetPayload: {
                used_builtins_.insert("lm_enum_payload");
                ir::Function* fn = current_module_->getFunction("lm_enum_payload");
                if (!fn) fn = builder_->createFunction("lm_enum_payload", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a)}), inst.result_type);
                break;
            }
            case LIR::LIR_Op::NewFrame: {
                // Virtual record: small primitive-field frames whose value
                // never escapes stay as canonical element slots — no heap
                // LmFrame is allocated unless a use materializes it.
                {
                    auto nlt = lir_func.register_language_types.find(inst.dst);
                    if (nlt != lir_func.register_language_types.end() && nlt->second &&
                        nlt->second->tag == ::TypeTag::Frame && vt_info.safe.count(inst.dst)) {
                        auto* nft = std::get_if<FrameType>(&nlt->second->extra);
                        const FrameFieldInfo* ninfo = nft ? frame_field_info(nft->name) : nullptr;
                        std::vector<int> nscratch;
                        const std::vector<int>* ndoms = frame_flat_domains(ninfo, nscratch);
                        if (ndoms && !ndoms->empty()) {
                            if (vt_info.canon_regs.count(inst.dst)) {
                                vtuples[inst.dst] = canon_elems(inst.dst);
                            } else {
                                std::vector<VTupleElem> elems(ndoms->size());
                                for (size_t j = 0; j < elems.size(); ++j) {
                                    elems[j].domain = (*ndoms)[j];
                                    elems[j].has = false;
                                }
                                vtuples[inst.dst] = std::move(elems);
                            }
                            vframes.insert(inst.dst);
                            reg_types[inst.dst] = LIR::Type::Ptr;
                            break;
                        }
                    }
                }
                std::string name = !inst.type_name.empty() ? inst.type_name : (!inst.func_name.empty() ? inst.func_name : "Frame");
                uint32_t fields = static_cast<uint32_t>(inst.imm);
                // LmFrame layout:
                // Offset 0: ObjHeader (8 bytes: type_id + metadata)
                // Offset 8: char* name (8 bytes)
                // Offset 16: LmValue* fields (8 bytes pointer)
                // Offset 24: int field_count (4 bytes + 4 bytes padding)
                // Offset 32: void* mutex (8 bytes)
                ir::Value* frame_ptr = builder_->createExternCall("memory.alloc", {context_->getConstantInt(context_->getIntegerType(64), 40)}, lir_type_to_fyra_type(inst.result_type));
                // Set header.type_id = TYPE_FRAME (15)
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 15), frame_ptr);
                
                // Set name
                ir::GlobalVariable* gv_name = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(), "fr_name_" + name + "_" + std::to_string(label_counter_++), name);
                ir::Value* name_addr = builder_->createAdd(frame_ptr, context_->getConstantInt(context_->getIntegerType(64), 8));
                auto* name_copy = builder_->createExternCall("lymar_aot_copy_constant", {gv_name,
                    context_->getConstantInt(context_->getIntegerType(64), 24 + name.size() + 1)}, context_->getIntegerType(64));
                builder_->createStore(name_copy, name_addr);

                // Allocate fields array: fields * 8 bytes
                uint32_t field_bytes = (fields > 0 ? fields : 2) * 8;
                ir::Value* fields_array = builder_->createExternCall("memory.alloc", {context_->getConstantInt(context_->getIntegerType(64), field_bytes)}, lir_type_to_fyra_type(inst.result_type));
                auto* initial_nil = builder_->createExternCall("lymar_aot_nil", {}, context_->getIntegerType(64));
                for (uint32_t f_idx = 0; f_idx < (fields > 0 ? fields : 2); ++f_idx) {
                    ir::Value* f_addr = builder_->createAdd(fields_array, context_->getConstantInt(context_->getIntegerType(64), f_idx * 8));
                    builder_->createStore(initial_nil, f_addr);
                }

                // Store fields array pointer at offset 16
                ir::Value* fields_ptr_addr = builder_->createAdd(frame_ptr, context_->getConstantInt(context_->getIntegerType(64), 16));
                builder_->createStore(fields_array, fields_ptr_addr);
                builder_->createExternCall("lymar_aot_edge", {fields_ptr_addr, fields_array}, context_->getVoidType());

                // Store field_count at offset 24
                ir::Value* cnt_addr = builder_->createAdd(frame_ptr, context_->getConstantInt(context_->getIntegerType(64), 24));
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), fields), cnt_addr);

                store_reg(inst.dst, frame_ptr, inst.result_type);
                if (auto* finalizer = current_module_->getFunction(name + ".deinit"))
                    builder_->createExternCall("lymar_aot_set_finalizer", {frame_ptr, finalizer}, nullptr);
                break;
            }
            case LIR::LIR_Op::FrameGetFieldAtomic: {
                auto value = builder_->createExternCall("lymar_aot_atomic_load", {
                    load_reg(inst.a, LIR::Type::Ptr), context_->getConstantInt(context_->getIntegerType(64), inst.b)},
                    context_->getIntegerType(64));
                store_reg(inst.dst, value, inst.result_type, true);
                break;
            }
            case LIR::LIR_Op::FrameGetField: {
                // Virtual record field read: element domains already hold the
                // post-untag representation, so the value flows straight into
                // the same store_reg shape the boxed path produces.
                if (vtuples.count(inst.a)) {
                    uint32_t field_idx = (inst.b != UINT32_MAX) ? inst.b : static_cast<uint32_t>(inst.imm);
                    if (field_idx < vtuples[inst.a].size()) {
                        const auto& e = vtuples[inst.a][static_cast<size_t>(field_idx)];
                        const bool float_result = inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32;
                        const bool dst_erased = lang_type_is_erased(inst.dst);
                        LIR::Type store_t = float_result && !dst_erased ? inst.result_type
                            : (float_result ? LIR::Type::Ptr : inst.result_type);
                        if (e.has) {
                            store_reg(inst.dst, velem_value(e), store_t, true);
                        } else {
                            // Unset field: a real frame reads nil; push it
                            // through the same untag path boxed reads take.
                            ir::Value* word = builder_->createExternCall("lymar_aot_nil", {},
                                context_->getIntegerType(64));
                            word = untag_word(word, inst.dst, inst.result_type);
                            store_reg(inst.dst, word, store_t, true);
                        }
                        break;
                    }
                    materialize_vtuple(inst.a);
                }
                uint32_t field_idx = (inst.b != UINT32_MAX) ? inst.b : static_cast<uint32_t>(inst.imm);
                ir::Value* frame_ptr = load_reg(inst.a, LIR::Type::Ptr);
                ir::Value* word = builder_->createExternCall("lymar_aot_frame_get_field",
                    {frame_ptr, context_->getConstantInt(context_->getIntegerType(64), field_idx)}, context_->getIntegerType(64));
                word = untag_word(word, inst.dst, inst.result_type);
                // Float results unbox to native f64 via untag_word. Only
                // erased-typed destinations keep the boxed/object word —
                // storing a box pointer into a scalar float local's slot
                // while later assignments write raw f64 bits leaves the slot
                // with a mixed representation (reads see pointer bits as
                // doubles).
                const bool float_result = inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32;
                const bool dst_erased = lang_type_is_erased(inst.dst);
                store_reg(inst.dst, word,
                    float_result && !dst_erased ? inst.result_type : (float_result ? LIR::Type::Ptr : inst.result_type), true);
                break;
            }
            case LIR::LIR_Op::FrameSetFieldAtomic:
            case LIR::LIR_Op::FrameFieldAtomicAdd:
            case LIR::LIR_Op::FrameFieldAtomicSub: {
                std::vector<ir::Value*> arguments{load_reg(inst.dst, LIR::Type::Ptr),
                    context_->getConstantInt(context_->getIntegerType(64), inst.a), tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b)};
                if (inst.op != LIR::LIR_Op::FrameSetFieldAtomic)
                    arguments.push_back(context_->getConstantInt(context_->getIntegerType(64), inst.op == LIR::LIR_Op::FrameFieldAtomicSub));
                builder_->createExternCall(inst.op == LIR::LIR_Op::FrameSetFieldAtomic ? "lymar_aot_atomic_store" : "lymar_aot_atomic_update", arguments, context_->getVoidType());
                break;
            }
            case LIR::LIR_Op::FrameSetField: {
                // Virtual record field write: store into the element's
                // backing slot (canonical pseudo register or INOUT buffer)
                // so every alias observes the mutation.
                if (vtuples.count(inst.dst)) {
                    if (vtuples.count(inst.b)) materialize_vtuple(inst.b);
                    uint32_t field_idx = inst.a;
                    if (field_idx < vtuples[inst.dst].size()) {
                        auto& elem = vtuples[inst.dst][static_cast<size_t>(field_idx)];
                        if (elem.canon_elem || elem.mem_base) {
                            // Canonical slots keep each domain's raw
                            // representation: scalars unboxed, TAGGED fields
                            // as LmValue words (same word the boxed path
                            // stores), PTR fields as raw addresses.
                            ir::Value* fv = load_reg(inst.b, inst.type_b);
                            if (elem.domain == VDOM_TAGGED) {
                                fv = tag_word(fv, inst.b, inst.type_b);
                            } else if (elem.domain == VDOM_PTR) {
                                fv = untag_word(tag_word(fv, inst.b, inst.type_b),
                                                inst.b, LIR::Type::Ptr);
                            }
                            canon_store_elem(elem, fv);
                            break;
                        }
                    }
                    materialize_vtuple(inst.dst);
                }
                ir::Value* frame_ptr = load_reg(inst.dst, LIR::Type::Ptr);
                uint32_t field_idx = inst.a;
                ir::Value* val = tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b);
                // tag_word always yields a tagged LmValue word (SMI, immediate,
                // heap pointer, or >SMI box). The slot kind must describe that
                // tagged domain — word_kind(inst.b) would report the *source*
                // scalar kind, so a boxed >SMI int would be stored with kind 0
                // and never promoted into the frame's region (dangling box).
                builder_->createExternCall("lymar_aot_frame_set_field",
                    {frame_ptr, context_->getConstantInt(context_->getIntegerType(64), field_idx), val}, context_->getVoidType());
                break;
            }
            case LIR::LIR_Op::TraitCallMethod: {
                ir::Value* receiver = load_reg(inst.call_args[0], LIR::Type::Ptr);
                
                std::string method_name = inst.func_name;
                auto& registry = LIR::FunctionRegistry::getInstance();
                std::string method_suffix = "." + method_name;
                
                std::vector<std::pair<std::string, ir::Function*>> candidates;
                const auto& impls = LM::Frontend::ModuleManager::getInstance().trait_implementors();
                auto iit = impls.find(inst.type_name);
                if (iit != impls.end()) {
                    // Verified implementors only: one frame_matches probe per
                    // real candidate instead of every same-named function.
                    for (const auto& frame_name : iit->second) {
                        // An unconstructed frame can never be the receiver.
                        if (!constructed_frames_.empty() && !constructed_frames_.count(frame_name)) continue;
                        std::string fname = frame_name + "." + method_name;
                        ir::Function* target_fn = current_module_->getFunction(fname);
                        if (target_fn) {
                            candidates.push_back({frame_name, target_fn});
                        }
                    }
                } else {
                    const auto& frame_methods = LM::Frontend::ModuleManager::getInstance().frame_method_names();
                    for (const auto& fname : registry.getFunctionNames()) {
                        if (fname.size() > method_suffix.size() &&
                            fname.compare(fname.size() - method_suffix.size(), method_suffix.size(), method_suffix) == 0 &&
                            (frame_methods.empty() || frame_methods.count(fname))) {
                            std::string fr_name = fname.substr(0, fname.size() - method_suffix.size());
                            if (!constructed_frames_.empty() && !constructed_frames_.count(fr_name)) continue;
                            ir::Function* target_fn = current_module_->getFunction(fname);
                            if (target_fn) {
                                candidates.push_back({fr_name, target_fn});
                            }
                        }
                    }
                }
                
                LIR::Type res_t = inst.result_type;
                if (res_t == LIR::Type::Void && !candidates.empty()) {
                    if (candidates[0].second->getReturnType()->isPointerTy()) {
                        res_t = LIR::Type::Ptr;
                    }
                }
                auto it_lang = lir_func.register_language_types.find(inst.dst);
                if (it_lang != lir_func.register_language_types.end() && it_lang->second && it_lang->second->tag == ::TypeTag::String) {
                    res_t = LIR::Type::Ptr;
                }

                // A trait default method (type_name.method) is the fallback when
                // no concrete frame-name candidate matches the receiver.
                std::string trait_default_name = inst.type_name + "." + method_name;
                ir::Function* trait_default_fn = inst.type_name.empty() ? nullptr : current_module_->getFunction(trait_default_name);
                ir::Function* sig_source_fn = !candidates.empty() ? candidates[0].second : trait_default_fn;

                if (candidates.empty() && !trait_default_fn) {
                    store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), 0), res_t);
                    break;
                }

                std::vector<ir::Value*> call_args;
                // TraitCallMethod carries no call_arg_types; the callee's
                // declared parameter types are the contract (all candidates
                // share the trait signature). Float parameters take native
                // doubles, so erased-word registers must unbox first.
                auto& sig_params = sig_source_fn->getParameters();
                for (size_t ai = 0; ai < inst.call_args.size(); ++ai) {
                    ir::Type* pty = nullptr;
                    if (!sig_params.empty()) {
                        auto pit = sig_params.begin();
                        std::advance(pit, std::min(ai, sig_params.size() - 1));
                        pty = (*pit)->getType();
                    }
                    uint32_t arg_reg = inst.call_args[ai];
                    if (pty && pty->isFloatingPoint()) {
                        call_args.push_back(load_float_reg(arg_reg, LIR::Type::F64));
                    } else {
                        call_args.push_back(load_reg(arg_reg, LIR::Type::I64));
                    }
                }

                // Dedupe: the frame_matches candidate chain is pure dispatch —
                // identical (trait, method, arity) inputs give identical results,
                // so emit it once as a shared helper and call it from each site.
                std::string dispatch_key = "__trait_dispatch_" + inst.type_name + "_" +
                    inst.func_name + "_" + std::to_string(inst.call_args.size());
                auto dit = trait_dispatch_helpers_.find(dispatch_key);
                ir::Function* dispatch_fn = dit != trait_dispatch_helpers_.end() ? dit->second : nullptr;
                if (!dispatch_fn) {
                    std::vector<ir::Type*> helper_param_types;
                    for (size_t ai = 0; ai < inst.call_args.size(); ++ai) {
                        ir::Type* pty = nullptr;
                        if (!sig_params.empty()) {
                            auto pit = sig_params.begin();
                            std::advance(pit, std::min(ai, sig_params.size() - 1));
                            pty = (*pit)->getType();
                        }
                        helper_param_types.push_back((pty && pty->isFloatingPoint())
                            ? static_cast<ir::Type*>(context_->getDoubleType())
                            : static_cast<ir::Type*>(context_->getIntegerType(64)));
                    }
                    dispatch_fn = builder_->createFunction(dispatch_key, context_->getIntegerType(64), helper_param_types);
                    trait_dispatch_helpers_[dispatch_key] = dispatch_fn;

                    auto* saved_ip = builder_->getInsertPoint();
                    ir::BasicBlock* h_entry = builder_->createBasicBlock(dispatch_key + "_entry", dispatch_fn);
                    builder_->setInsertPoint(h_entry);

                    std::vector<ir::Value*> h_args;
                    for (auto& hp : dispatch_fn->getParameters()) h_args.push_back(hp.get());
                    ir::Value* h_receiver = h_args.empty() ? nullptr : h_args[0];

                    ir::BasicBlock* b_join = builder_->createBasicBlock("trait_join_" + std::to_string(label_counter_++), dispatch_fn);
                    ir::Instruction* res_slot = builder_->createAlloc(context_->getConstantInt(context_->getIntegerType(64), 8), context_->getIntegerType(64));
                    builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), res_slot);
                    ir::BasicBlock* b_fallback = trait_default_fn ? builder_->createBasicBlock("trait_default_" + std::to_string(label_counter_++), dispatch_fn) : nullptr;

                    for (size_t ci = 0; ci < candidates.size(); ++ci) {
                        ir::BasicBlock* b_match = builder_->createBasicBlock("trait_match_" + std::to_string(label_counter_++), dispatch_fn);
                        ir::BasicBlock* b_next = (ci + 1 < candidates.size()) ? builder_->createBasicBlock("trait_next_" + std::to_string(label_counter_++), dispatch_fn)
                                               : (b_fallback ? b_fallback : b_join);

                        auto* expected_name = FyraBuiltinFunctions::get_or_create_global_str(current_module_.get(), builder_.get(),
                            "trait_receiver_" + candidates[ci].first, candidates[ci].first);
                        ir::Value* is_cand = builder_->createExternCall("lymar_aot_frame_matches", {h_receiver, expected_name,
                            context_->getConstantInt(context_->getIntegerType(64), candidates[ci].first.size())}, context_->getIntegerType(64));
                        builder_->createBr(is_cand, b_match, b_next);

                        builder_->setInsertPoint(b_match);
                        ir::Value* call_res = builder_->createCall(candidates[ci].second, h_args);
                        builder_->createStore(tag_indirect_result(call_res, candidates[ci].first), res_slot);
                        builder_->createJmp(b_join);

                        if (ci + 1 < candidates.size()) {
                            builder_->setInsertPoint(b_next);
                        }
                    }

                    if (candidates.empty() && b_fallback) {
                        builder_->createJmp(b_fallback);
                    }
                    if (b_fallback) {
                        builder_->setInsertPoint(b_fallback);
                        ir::Value* fb_res = builder_->createCall(trait_default_fn, h_args);
                        builder_->createStore(erased_word(fb_res), res_slot);
                        builder_->createJmp(b_join);
                    }

                    builder_->setInsertPoint(b_join);
                    ir::Value* joined = builder_->createLoadl(res_slot);
                    builder_->createRet(joined);
                    if (saved_ip) builder_->setInsertPoint(saved_ip);
                }

                ir::Value* joined = builder_->createCall(dispatch_fn, call_args);
                if (res_t == LIR::Type::F64 || res_t == LIR::Type::F32) {
                    // erased_word boxed the callee's double return; unbox it.
                    store_float_reg(inst.dst, builder_->createExternCall("lymar_aot_to_float",
                        {joined}, context_->getDoubleType()));
                } else {
                    store_reg(inst.dst, joined, res_t, true);
                }
                break;
            }
            case LIR::LIR_Op::Return:
            case LIR::LIR_Op::Ret:
                if (dctx && dctx->sret_return && sret_buf_val) {
                    // `.direct` tuple return: store element words into the
                    // caller's sret buffer — no heap tuple is materialized.
                    auto* i64ty = context_->getIntegerType(64);
                    const size_t n = dctx->ret_domains.size();
                    auto vit = vtuples.find(inst.a);
                    const bool have_vt = vit != vtuples.end() && vit->second.size() == n;
                    if (vit != vtuples.end() && !have_vt) materialize_vtuple(inst.a);
                    ir::Value* tup = nullptr;
                    ir::Function* gfn = nullptr;
                    if (!have_vt && inst.a != UINT32_MAX) {
                        tup = load_reg(inst.a, inst.type_a);
                        if (dctx->ret_frame) {
                            // Real (materialized) frame: read fields through
                            // the same tagged-word accessor boxed code uses.
                        } else {
                            used_builtins_.insert("lm_tuple_get");
                            gfn = current_module_->getFunction("lm_tuple_get");
                            if (!gfn) gfn = builder_->createFunction("lm_tuple_get", i64ty, {i64ty, i64ty});
                        }
                    }
                    for (size_t j = 0; j < n; ++j) {
                        int dom = dctx->ret_domains[j];
                        ir::Value* ev = nullptr;
                        if (have_vt) {
                            const auto& e = vit->second[j];
                            if (e.has) ev = velem_value(e);
                            else ev = (e.domain == VDOM_FLOAT)
                                ? static_cast<ir::Value*>(context_->getConstantFP(context_->getDoubleType(), 0.0))
                                : static_cast<ir::Value*>(context_->getConstantInt(i64ty, 0));
                        } else if (tup) {
                            ir::Value* raw;
                            if (dctx->ret_frame) {
                                raw = builder_->createExternCall("lymar_aot_frame_get_field",
                                    {tup, context_->getConstantInt(i64ty, static_cast<long long>(j))}, i64ty);
                            } else {
                                raw = builder_->createCall(gfn,
                                    {tup, context_->getConstantInt(i64ty, static_cast<long long>(j))}, i64ty);
                            }
                            if (dom == VDOM_FLOAT) ev = untag_word(raw, UINT32_MAX, LIR::Type::F64);
                            else if (dom == VDOM_INT) ev = untag_word(raw, UINT32_MAX, LIR::Type::I64);
                            else if (dom == VDOM_BOOL) ev = untag_word(raw, UINT32_MAX, LIR::Type::Bool);
                            else if (dom == VDOM_PTR) ev = untag_word(raw, UINT32_MAX, LIR::Type::Ptr);
                            else ev = raw;
                        }
                        if (!ev) ev = context_->getConstantInt(i64ty, 0);
                        ir::Value* addr = builder_->createAdd(sret_buf_val,
                            context_->getConstantInt(i64ty, static_cast<long long>(j * 8)));
                        // Scalar-domain sret slots can never hold a managed
                        // heap word, so region lowering may skip the edge.
                        // PTR/TAGGED elements keep the barrier.
                        const bool scalar_dom = dom == VDOM_FLOAT || dom == VDOM_INT || dom == VDOM_BOOL;
                        if (dom == VDOM_FLOAT) {
                            if (!ev->getType()->isFloatingPoint())
                                ev = builder_->createExternCall("lymar_aot_to_float", {ev}, context_->getDoubleType());
                            auto* st = builder_->createStore(ev, addr);
                            if (scalar_dom) st->setName("scalar_store_sret");
                        } else {
                            if (ev->getType() != i64ty) ev = builder_->createCast(ev, i64ty);
                            auto* st = builder_->createStore(ev, addr);
                            if (scalar_dom) st->setName("scalar_store_sret");
                        }
                    }
                    if (have_vt) { vtuples.erase(inst.a); vframes.erase(inst.a); }
                    builder_->createRet(context_->getConstantInt(i64ty, 0));
                    terminated = true;
                    break;
                }
                if (main_fn->getName() == "main") {
                    builder_->createRet(context_->getConstantInt(context_->getIntegerType(64), 0));
                } else if (inst.a != UINT32_MAX) {
                    ir::Value* ret_val = load_reg(inst.a, inst.type_a);
                    // Erased-word registers (container/frame gets stored as
                    // words even when the language type is float) returned
                    // from float functions must unbox to the declared double.
                    if (ret_val && !ret_val->getType()->isFloatingPoint() && main_fn->getReturnType() &&
                        (main_fn->getReturnType()->isDoubleTy() || main_fn->getReturnType()->isFloatTy()))
                        ret_val = builder_->createExternCall("lymar_aot_to_float",
                            {ret_val}, context_->getDoubleType());
                    // Erased-typed return expressions carry tagged LmValue
                    // words. When the declared return type is scalar the
                    // callee slot must hold the raw domain value — untag
                    // exactly once, mirroring the erased-side tag_word below.
                    // Only fires when the source register is provably erased
                    // (lang_type_holds_tagged_word); raw scalar returns are
                    // already domain values and untag_int would corrupt them.
                    if (ret_val && lir_func.return_language_type &&
                        lang_type_holds_tagged_word(inst.a) &&
                        !ret_val->getType()->isFloatingPoint()) {
                        switch (lir_func.return_language_type->tag) {
                            case ::TypeTag::Bool:
                                ret_val = builder_->createExternCall("lymar_aot_untag_bool", {ret_val}, context_->getIntegerType(64));
                                break;
                            case ::TypeTag::Int: case ::TypeTag::Int8: case ::TypeTag::Int16:
                            case ::TypeTag::Int32: case ::TypeTag::Int64:
                            case ::TypeTag::UInt: case ::TypeTag::UInt8: case ::TypeTag::UInt16:
                            case ::TypeTag::UInt32: case ::TypeTag::UInt64:
                                ret_val = builder_->createExternCall("lymar_aot_untag_int", {ret_val}, context_->getIntegerType(64));
                                break;
                            case ::TypeTag::Float32: case ::TypeTag::Float64:
                            case ::TypeTag::Decimal2: case ::TypeTag::Decimal4: case ::TypeTag::Decimal6:
                                ret_val = builder_->createExternCall("lymar_aot_to_float", {ret_val}, context_->getDoubleType());
                                break;
                            default: break;
                        }
                    }
                    // Functions declared with an erased return type (any,
                    // unions, error unions, containers, frames) return tagged
                    // LmValue words. A raw scalar return must be tagged here
                    // or it aliases VAL_NIL/SMI patterns in the callee slot.
                    if (ret_val && lir_func.return_language_type &&
                        !ret_val->getType()->isFloatingPoint()) {
                        switch (lir_func.return_language_type->tag) {
                            case ::TypeTag::Any: case ::TypeTag::Union: case ::TypeTag::Sum:
                            case ::TypeTag::ErrorUnion: case ::TypeTag::Nil:
                            case ::TypeTag::String: case ::TypeTag::List: case ::TypeTag::Dict:
                            case ::TypeTag::Tuple: case ::TypeTag::Frame: case ::TypeTag::Enum:
                            case ::TypeTag::Trait: case ::TypeTag::TraitObject:
                            case ::TypeTag::Function: case ::TypeTag::Closure:
                            case ::TypeTag::Module: case ::TypeTag::Range:
                            case ::TypeTag::Channel: case ::TypeTag::UserDefined:
                            case ::TypeTag::Int128: case ::TypeTag::UInt128:
                                ret_val = tag_word(ret_val, inst.a, inst.type_a);
                                break;
                            default: break;
                        }
                    }
                    builder_->createRet(ret_val);
                } else {
                    // VAL_NIL is the constant word 2; `.direct` variants emit
                    // it directly so `: nil` functions stay call-free and
                    // inlinable (lymar_aot_nil() just returns 2).
                    builder_->createRet(dctx
                        ? static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64), 2))
                        : builder_->createExternCall("lymar_aot_nil", {}, context_->getIntegerType(64)));
                }
                terminated = true;
                break;
            case LIR::LIR_Op::Nop: break;
            // Structured concurrency operations
            case LIR::LIR_Op::TaskContextAlloc: {
                ir::Value* ctx_ptr = builder_->createExternCall("memory.alloc", {context_->getConstantInt(context_->getIntegerType(64), std::max(uint32_t(8),inst.imm) * 8)}, lir_type_to_fyra_type(inst.result_type));
                for (uint32_t f_idx = 0; f_idx < std::max(uint32_t(8),inst.imm); ++f_idx) {
                    ir::Value* addr = builder_->createAdd(ctx_ptr, context_->getConstantInt(context_->getIntegerType(64), f_idx * 8));
                    builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), addr);
                }
                store_reg(inst.dst, ctx_ptr, inst.result_type);
                break;
            }
            case LIR::LIR_Op::TaskContextInit: {
                if (inst.dst != UINT32_MAX) store_reg(inst.dst, load_reg(inst.a, inst.type_a), inst.result_type);
                break;
            }
            case LIR::LIR_Op::TaskSetField: {
                uint32_t ctx_reg = (inst.b != UINT32_MAX && inst.b != 0) ? inst.b : inst.a;
                uint32_t val_reg = (inst.a != UINT32_MAX && inst.a != ctx_reg) ? inst.a : (inst.dst != UINT32_MAX && inst.dst != ctx_reg ? inst.dst : inst.b);
                ir::Value* ctx_ptr = load_reg(ctx_reg, LIR::Type::Ptr);
                ir::Value* val = erased_word(load_reg(val_reg, LIR::Type::I64));
                uint32_t field_idx = inst.imm;
                if (field_idx == 4) {
                    auto literal = reg_string_literals.find(val_reg);
                    if (literal == reg_string_literals.end()) throw std::runtime_error("Native task requires a canonical call target");
                    auto* target = current_module_->getFunction(literal->second);
                    if (!target) throw std::runtime_error("Missing native task target: " + literal->second);
                    auto thunk_name = "__lymar_task_entry_" + target->getName();
                    auto* thunk = current_module_->getFunction(thunk_name);
                    if (!thunk) {
                        auto* saved_block = builder_->getInsertPoint();
                        auto* word = context_->getIntegerType(64);
                        thunk = builder_->createFunction(thunk_name,word,{word,word});
                        builder_->setInsertPoint(builder_->createBasicBlock("entry",thunk));
                        auto parameters=thunk->getParameters().begin();
                        ir::Value* context=parameters->get(); ++parameters;
                        ir::Value* item=parameters->get();
                        std::vector<ir::Value*> arguments;
                        size_t index=0;
                        for (auto& parameter : target->getParameters()) {
                            ir::Value* value;
                            if (index==0) value=context;
                            else if(index==1) value=item;
                            else {
                                auto field=index==2?2:8+index;
                                auto* address=builder_->createAdd(context,context_->getConstantInt(word,field*8));
                                value=builder_->createLoadl(address);
                                if (parameter->getType()->isFloatingPoint())
                                    value=builder_->createExternCall("lymar_aot_to_float",{value},context_->getDoubleType());
                            }
                            arguments.push_back(value); ++index;
                        }
                        builder_->createCall(target,arguments);
                        builder_->createRet(context_->getConstantInt(word,0));
                        builder_->setInsertPoint(saved_block);
                    }
                    val=thunk;
                }
                ir::Value* addr = builder_->createAdd(ctx_ptr, context_->getConstantInt(context_->getIntegerType(64), (long long)field_idx * 8));
                builder_->createStore(val, addr);
                break;
            }
            case LIR::LIR_Op::TaskGetField: {
                ir::Value* ctx_ptr = load_reg(inst.a, LIR::Type::Ptr);
                uint32_t field_idx = inst.imm;
                ir::Value* addr = builder_->createAdd(ctx_ptr, context_->getConstantInt(context_->getIntegerType(64), (long long)field_idx * 8));
                store_reg(inst.dst, builder_->createLoadl(addr), inst.result_type, true);
                break;
            }
            case LIR::LIR_Op::CapabilityAcquire: {
                // Capabilities are proven by the frontend; retain an explicit
                // linear token in Fyra IR so optimization cannot erase the
                // split/join ordering boundary.
                store_reg(inst.dst, load_reg(inst.a, LIR::Type::Ptr), inst.result_type);
                break;
            }
            case LIR::LIR_Op::CapabilityRelease:
                break;
            case LIR::LIR_Op::ParallelInit:
            case LIR::LIR_Op::SchedulerInit: {
                auto* word=context_->getIntegerType(64);
                store_reg(inst.dst,builder_->createExternCall("lymar_aot_scheduler_new",{
                    context_->getConstantInt(word,inst.a),context_->getConstantInt(word,inst.b),
                    context_->getConstantInt(word,inst.imm)},word),inst.result_type);
                break;
            }
            case LIR::LIR_Op::SchedulerAddTask: {
                auto* word=context_->getIntegerType(64);
                uint32_t scheduler = (inst.dst != UINT32_MAX && inst.dst != 0) ? inst.dst : inst.a;
                uint32_t task = (inst.a != UINT32_MAX && inst.a != scheduler) ? inst.a : inst.b;
                builder_->createExternCall("lymar_aot_channel_push",{load_reg(scheduler,LIR::Type::Ptr),load_reg(task,LIR::Type::Ptr)},nullptr);
                break;
            }
            case LIR::LIR_Op::SchedulerRun: {
                uint32_t scheduler = (inst.a != UINT32_MAX && inst.a != 0) ? inst.a : inst.dst;
                builder_->createExternCall("lymar_aot_scheduler_run",{load_reg(scheduler,LIR::Type::Ptr)},nullptr);
                break;
            }
            case LIR::LIR_Op::ParallelSync: break;
            case LIR::LIR_Op::ResourceCreate: {
                // Concurrency lowering encodes a channel constructor in imm,
                // unlike the generic resource_create intrinsic's register args.
                if (inst.imm == 5 && inst.a == 0 && inst.b == 0) {
                    store_reg(inst.dst,builder_->createExternCall("lymar_aot_channel_new",{},context_->getIntegerType(64)),LIR::Type::Ptr);
                    break;
                }
                auto* i64 = context_->getIntegerType(64);
                auto* args = inst.b == UINT32_MAX ? static_cast<ir::Value*>(context_->getConstantInt(i64, VAL_NIL)) : load_reg(inst.b, inst.type_b);
                store_reg(inst.dst, builder_->createExternCall("lymar_aot_resource_create",
                    {load_reg(inst.a, inst.type_a), args}, i64), inst.result_type);
                break;
            }
            case LIR::LIR_Op::ResourceCall: {
                auto* i64 = context_->getIntegerType(64);
                // On capability-enabled targets every resource call routes
                // through the module-level fyrA_fs_dispatch helper: the op is
                // a runtime value (it flows through res._call/call as a
                // parameter), so the helper compares it against the filesystem
                // op numbers and lowers those to native capability calls,
                // falling back to lymar_aot_resource_call for everything else.
                if (fs_capabilities_ && inst.call_args.size() >= 2) {
                    needs_service_dispatch_ = true;
                    if (fs_mkdirp_helper_) needs_mkdirp_helper_ = true;
                    auto* dfn = current_module_->getFunction("fyrA_service_dispatch");
                    if (!dfn) dfn = builder_->createFunction("fyrA_service_dispatch", i64, {i64, i64, i64, i64});
                    const size_t count = inst.call_args.size() - 2;
                    auto* args = entry_alloc(i64, context_->getConstantInt(i64, std::max(size_t(1), count) * 8));
                    for (size_t n = 0; n < count; ++n)
                        builder_->createStore(load_reg(inst.call_args[n + 2], LIR::Type::Ptr),
                            builder_->createAdd(args, context_->getConstantInt(i64, n * 8)));
                    auto* operation = inst.b == UINT32_MAX
                        ? static_cast<ir::Value*>(context_->getConstantInt(i64, inst.imm))
                        : load_reg(inst.b, inst.type_b);
                    store_reg(inst.dst, builder_->createCall(dfn,
                        {load_reg(inst.a, inst.type_a), operation,
                         context_->getConstantInt(i64, count), args}, i64), inst.result_type);
                    break;
                }
                const size_t count = inst.call_args.size() > 2 ? inst.call_args.size() - 2 : 0;
                auto* args = entry_alloc(i64, context_->getConstantInt(i64, std::max(size_t(1), count) * 8));
                for (size_t n = 0; n < count; ++n)
                    builder_->createStore(load_reg(inst.call_args[n + 2], LIR::Type::Ptr),
                        builder_->createAdd(args, context_->getConstantInt(i64, n * 8)));
                auto* operation = inst.b == UINT32_MAX ? static_cast<ir::Value*>(context_->getConstantInt(i64, inst.imm)) : load_reg(inst.b, inst.type_b);
                store_reg(inst.dst, builder_->createExternCall("lymar_aot_resource_call",
                    {load_reg(inst.a, inst.type_a), operation, context_->getConstantInt(i64, count), args}, i64), inst.result_type);
                break;
            }
            case LIR::LIR_Op::ResourceDestroy:
                builder_->createExternCall("lymar_aot_resource_destroy", {load_reg(inst.a, inst.type_a)}, nullptr);
                break;
            case LIR::LIR_Op::ChannelAlloc:
                store_reg(inst.dst,builder_->createExternCall("lymar_aot_channel_new",{},context_->getIntegerType(64)),inst.result_type);
                break;
            case LIR::LIR_Op::ChannelSend:
            case LIR::LIR_Op::ChannelOffer:
            case LIR::LIR_Op::ChannelPush: {
                auto* channel = (inst.a != UINT32_MAX && inst.a != 0) ? load_reg(inst.a,LIR::Type::Ptr) : load_reg(inst.dst,LIR::Type::Ptr);
                auto* value = (inst.b != UINT32_MAX) ? tag_word(load_reg(inst.b,inst.type_b), inst.b, inst.type_b) : tag_word(load_reg(inst.a,inst.type_a), inst.a, inst.type_a);
                builder_->createExternCall("lymar_aot_channel_push",{channel,value},nullptr);
                if(inst.dst != UINT32_MAX && inst.dst != inst.a) store_reg(inst.dst,context_->getConstantInt(context_->getIntegerType(64),1),inst.result_type);
                break;
            }
            case LIR::LIR_Op::ChannelRecv:
            case LIR::LIR_Op::ChannelPop:
            case LIR::LIR_Op::ChannelPoll: {
                auto* channel = (inst.a != UINT32_MAX && inst.a != 0) ? load_reg(inst.a,LIR::Type::Ptr) : load_reg(inst.dst,LIR::Type::Ptr);
                ir::Value* popped = builder_->createExternCall("lymar_aot_channel_pop",{channel},context_->getIntegerType(64));
                popped = untag_word(popped, inst.dst, inst.result_type);
                store_reg(inst.dst, popped, inst.result_type, true);
                break;
            }
            case LIR::LIR_Op::ChannelHasData: {
                auto* channel = (inst.a != UINT32_MAX && inst.a != 0) ? load_reg(inst.a,LIR::Type::Ptr) : load_reg(inst.dst,LIR::Type::Ptr);
                store_reg(inst.dst,builder_->createExternCall("lymar_aot_channel_has_data",{channel},context_->getIntegerType(64)),inst.result_type);
                break;
            }
            case LIR::LIR_Op::ChannelClose:
                builder_->createExternCall("lymar_aot_channel_close",{load_reg(inst.a,LIR::Type::Ptr)},nullptr);
                break;
            // Memory Operations
            case LIR::LIR_Op::MemoryLoad: {
                if (inst.imm > 10)
                    throw std::runtime_error("Invalid MemoryLoad element kind");
                // Raw fast path: integer/pointer operands already hold the
                // untagged address (pubptr is an int alias; tagging only
                // happens at extern boundaries), so i64/u64/f64 loads lower
                // to a native load behind the same null->nil guard the
                // runtime extern provides, instead of paying RuntimeGuard +
                // tag decode + memcpy + float box on every access. Narrower
                // kinds and f32 keep the extern path (no fp narrowing opcode).
                // Intrinsic MemoryLoad/Store leave type_a/type_b Void; the
                // operand ABI type lives in register_types instead.
                auto operand_type = [&](uint32_t r, LIR::Type declared) -> LIR::Type {
                    if (declared != LIR::Type::Void) return declared;
                    auto it = lir_func.register_types.find(r);
                    return it != lir_func.register_types.end() ? it->second : LIR::Type::I64;
                };
                const LIR::Type eff_a = operand_type(inst.a, inst.type_a);
                const bool raw_ptr_a =
                    (eff_a == LIR::Type::Ptr || eff_a == LIR::Type::I64 ||
                     eff_a == LIR::Type::U64 || eff_a == LIR::Type::I32 ||
                     eff_a == LIR::Type::U32 || eff_a == LIR::Type::I16 ||
                     eff_a == LIR::Type::U16 || eff_a == LIR::Type::I8 ||
                     eff_a == LIR::Type::U8) && !lang_type_holds_tagged_word(inst.a);
                if (raw_ptr_a && inst.imm != 8 && inst.imm != 10) {
                    auto* i64ty = context_->getIntegerType(64);
                    auto* i32ty = context_->getIntegerType(32);
                    ir::Value* addr = load_reg(inst.a, eff_a);
                    ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                    std::string mid = "mload_" + std::to_string(label_counter_++);
                    ir::BasicBlock* b_ok = builder_->createBasicBlock(mid + "_ok", cur_fn);
                    ir::BasicBlock* b_nil = builder_->createBasicBlock(mid + "_nil", cur_fn);
                    ir::BasicBlock* b_done = builder_->createBasicBlock(mid + "_done", cur_fn);
                    builder_->createBr(builder_->createCeq(addr, context_->getConstantInt(i64ty, 0)), b_nil, b_ok);
                    builder_->setInsertPoint(b_nil);
                    if (inst.imm == 9) {
                        // Nil must match the slot representation store_reg
                        // fixes for this register: erased slots take the
                        // VAL_NIL word, scalar float slots take 0.0 (the
                        // same value to_float(VAL_NIL) yields in the VM).
                        if (pointer_assigned_regs.count(inst.dst) || is_pointer_lang_type(inst.dst))
                            store_reg(inst.dst, context_->getConstantInt(i64ty, VAL_NIL), LIR::Type::Ptr);
                        else
                            store_reg(inst.dst, context_->getConstantFP(context_->getDoubleType(), 0.0), LIR::Type::F64);
                    } else {
                        store_reg(inst.dst, context_->getConstantInt(i64ty, VAL_NIL), inst.result_type);
                    }
                    builder_->createJmp(b_done);
                    builder_->setInsertPoint(b_ok);
                    ir::Value* v = nullptr;
                    switch (inst.imm) {
                        case 0: v = builder_->createExtSW(builder_->createLoadsb(addr), i64ty); break;
                        case 1: v = builder_->createExtUW(builder_->createLoadub(addr), i64ty); break;
                        case 2: v = builder_->createExtSW(builder_->createLoadsh(addr), i64ty); break;
                        case 3: v = builder_->createExtUW(builder_->createLoaduh(addr), i64ty); break;
                        case 4: v = builder_->createExtSW(builder_->createLoaduw(addr), i64ty); break;
                        case 5: v = builder_->createExtUW(builder_->createLoaduw(addr), i64ty); break;
                        case 6: case 7: v = builder_->createLoadl(addr); break;
                        case 9: {
                            // store_reg applies the standard float discipline:
                            // raw double for scalar float slots, boxed tagged
                            // word only when the destination is erased.
                            store_reg(inst.dst, builder_->createLoadd(addr), LIR::Type::F64);
                            v = nullptr;
                            break;
                        }
                    }
                    if (v) store_reg(inst.dst, v, inst.result_type);
                    builder_->createJmp(b_done);
                    builder_->setInsertPoint(b_done);
                    break;
                }
                auto* value = builder_->createExternCall("lymar_aot_memory_load",
                    {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a), context_->getConstantInt(context_->getIntegerType(64), inst.imm)},
                    context_->getIntegerType(64));
                // Float loads use an erased word at the runtime boundary. Kind
                // propagation supplies the conversion and ownership facts.
                // A nullable float load must retain nil until an operation
                // actually requests a numeric conversion (as in the VM).
                store_reg(inst.dst, value, inst.imm >= 8 ? LIR::Type::Ptr : inst.result_type);
                break;
            }
            case LIR::LIR_Op::MemoryStore: {
                if (inst.imm > 10)
                    throw std::runtime_error("Invalid MemoryStore element kind");
                // Raw fast path mirrors MemoryLoad: Ptr address + raw scalar
                // value (untagged, non-erased) lowers to a native store behind
                // the null no-op guard. f32 stores and tagged values keep the
                // extern path which performs numeric conversion/tag decoding.
                auto operand_type = [&](uint32_t r, LIR::Type declared) -> LIR::Type {
                    if (declared != LIR::Type::Void) return declared;
                    auto it = lir_func.register_types.find(r);
                    return it != lir_func.register_types.end() ? it->second : LIR::Type::I64;
                };
                const LIR::Type eff_a = operand_type(inst.a, inst.type_a);
                const LIR::Type eff_b = operand_type(inst.b, inst.type_b);
                const bool raw_int_val =
                    eff_b == LIR::Type::I64 || eff_b == LIR::Type::U64 ||
                    eff_b == LIR::Type::I32 || eff_b == LIR::Type::U32 ||
                    eff_b == LIR::Type::I16 || eff_b == LIR::Type::U16 ||
                    eff_b == LIR::Type::I8 || eff_b == LIR::Type::U8 ||
                    eff_b == LIR::Type::Ptr;
                const bool raw_ptr_a =
                    (eff_a == LIR::Type::Ptr || eff_a == LIR::Type::I64 ||
                     eff_a == LIR::Type::U64 || eff_a == LIR::Type::I32 ||
                     eff_a == LIR::Type::U32 || eff_a == LIR::Type::I16 ||
                     eff_a == LIR::Type::U16 || eff_a == LIR::Type::I8 ||
                     eff_a == LIR::Type::U8) && !lang_type_holds_tagged_word(inst.a);
                const bool raw_store = raw_ptr_a &&
                    !lang_type_holds_tagged_word(inst.b) &&
                    (((inst.imm <= 7) && raw_int_val) ||
                     (inst.imm == 9 && eff_b == LIR::Type::F64));
                if (raw_store) {
                    auto* i64ty = context_->getIntegerType(64);
                    auto* i32ty = context_->getIntegerType(32);
                    ir::Value* addr = load_reg(inst.a, eff_a);
                    ir::Value* val = load_reg(inst.b, eff_b);
                    if (val->getType() != i64ty && inst.imm != 9)
                        val = builder_->createCast(val, i64ty);
                    ir::Function* cur_fn = builder_->getInsertPoint()->getParent();
                    std::string mid = "mstore_" + std::to_string(label_counter_++);
                    ir::BasicBlock* b_ok = builder_->createBasicBlock(mid + "_ok", cur_fn);
                    ir::BasicBlock* b_done = builder_->createBasicBlock(mid + "_done", cur_fn);
                    builder_->createBr(builder_->createCeq(addr, context_->getConstantInt(i64ty, 0)), b_done, b_ok);
                    builder_->setInsertPoint(b_ok);
                    switch (inst.imm) {
                        case 0: case 1: builder_->createStoreb(val, addr); break;
                        case 2: case 3: builder_->createStoreh(val, addr); break;
                        case 4: case 5: builder_->createStore(builder_->createSToSI(val, i32ty), addr); break;
                        case 6: case 7: builder_->createStorel(val, addr); break;
                        case 9: builder_->createStored(val, addr); break;
                    }
                    builder_->createJmp(b_done);
                    builder_->setInsertPoint(b_done);
                    break;
                }
                builder_->createExternCall("lymar_aot_memory_store",
                    {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a), tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b),
                     context_->getConstantInt(context_->getIntegerType(64), inst.imm)}, nullptr);
                break;
            }
            case LIR::LIR_Op::MemoryAlloc:
                store_reg(inst.dst, builder_->createExternCall("lymar_aot_raw_alloc",
                    {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a)},
                    context_->getIntegerType(64)), LIR::Type::Ptr);
                break;
            case LIR::LIR_Op::MemoryFree:
                builder_->createExternCall("lymar_aot_raw_free",
                    {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a)}, nullptr);
                break;
            case LIR::LIR_Op::MemoryResize:
                store_reg(inst.dst, builder_->createExternCall("lymar_aot_raw_resize",
                    {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a), tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b)},
                    context_->getIntegerType(64)), LIR::Type::Ptr);
                break;
            case LIR::LIR_Op::MemoryCopy:
            case LIR::LIR_Op::MemoryFill:
            case LIR::LIR_Op::MemoryCompare: {
                auto* i64 = context_->getIntegerType(64);
                auto* size = inst.call_args.empty() ? static_cast<ir::Value*>(context_->getConstantInt(i64, 0)) :
                    erased_word(load_reg(inst.call_args[inst.call_args.size() >= 3 ? 2 : 0], LIR::Type::I64));
                const char* name = inst.op == LIR::LIR_Op::MemoryCopy ? "lymar_aot_raw_copy_checked" :
                    inst.op == LIR::LIR_Op::MemoryFill ? "lymar_aot_raw_fill_checked" : "lymar_aot_raw_compare_checked";
                auto* result = builder_->createExternCall(name,
                    {tag_word(load_reg(inst.a, inst.type_a), inst.a, inst.type_a), tag_word(load_reg(inst.b, inst.type_b), inst.b, inst.type_b), size},
                    inst.op == LIR::LIR_Op::MemoryCompare ? i64 : nullptr);
                if (inst.op == LIR::LIR_Op::MemoryCompare) store_reg(inst.dst, result, LIR::Type::I64);
                break;
            }
            // Pointer Operations - use Fyra IR arithmetic directly
            case LIR::LIR_Op::PtrAdd:
                store_reg(inst.dst, builder_->createAdd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::PtrSub:
                store_reg(inst.dst, builder_->createSub(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::PtrDiff:
                store_reg(inst.dst, builder_->createSub(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                break;
            case LIR::LIR_Op::PtrAlign: {
                // Alignment: (ptr + (alignment - 1)) & ~(alignment - 1)
                ir::Value* align_minus_one = builder_->createSub(load_reg(inst.b, inst.type_b), context_->getConstantInt(context_->getIntegerType(64), 1));
                ir::Value* aligned = builder_->createAdd(load_reg(inst.a, inst.type_a), align_minus_one);
                ir::Value* mask = builder_->createXor(align_minus_one, context_->getConstantInt(context_->getIntegerType(64), -1));
                store_reg(inst.dst, builder_->createAnd(aligned, mask), inst.result_type);
                break;
            }
            case LIR::LIR_Op::PtrIsAligned: {
                // Check if (ptr & (alignment - 1)) == 0
                ir::Value* align_minus_one = builder_->createSub(load_reg(inst.b, inst.type_b), context_->getConstantInt(context_->getIntegerType(64), 1));
                ir::Value* masked = builder_->createAnd(load_reg(inst.a, inst.type_a), align_minus_one);
                store_reg(inst.dst, builder_->createCeq(masked, context_->getConstantInt(context_->getIntegerType(64), 0)), inst.result_type);
                break;
            }
            // Native FFI uses the shared platform ABI engine, not capability no-ops.
            case LIR::LIR_Op::LibraryLoad:
                store_reg(inst.dst,builder_->createExternCall("lymar_aot_library_open",{load_reg(inst.a,inst.type_a)},context_->getIntegerType(64)),inst.result_type,true);break;
            case LIR::LIR_Op::LibraryUnload:
                builder_->createExternCall("lymar_aot_library_close",{load_reg(inst.a,inst.type_a)},context_->getVoidType());break;
            case LIR::LIR_Op::LibrarySymbol:
                store_reg(inst.dst,builder_->createExternCall("lymar_aot_library_symbol",{load_reg(inst.a,inst.type_a),load_reg(inst.b,inst.type_b)},context_->getIntegerType(64)),inst.result_type,true);break;
            case LIR::LIR_Op::ForeignCall: {
                auto* zero=context_->getConstantInt(context_->getIntegerType(64),0);
                ir::Value* result=nullptr;
                if(inst.func_name=="std.ffi.foreign_call" || inst.func_name=="ffi.foreign_call") {
                    if(inst.call_args.size()!=4 && inst.call_args.size()!=5) throw std::runtime_error("Malformed canonical foreign_call arguments");
                    // 5th arg (optional) is the struct-return result buffer.
                    ir::Value* ret_buf = inst.call_args.size()==5
                        ? load_reg(inst.call_args[4],LIR::Type::I64)
                        : static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64),0));
                    result=builder_->createExternCall("lymar_aot_foreign_call_list",{load_reg(inst.call_args[0],LIR::Type::Ptr),load_reg(inst.call_args[1],LIR::Type::Ptr),load_reg(inst.call_args[2],LIR::Type::I64),load_reg(inst.call_args[3],LIR::Type::Ptr),ret_buf},context_->getIntegerType(64));
                } else {
                    if(inst.call_args.empty()) throw std::runtime_error("Foreign call missing target");
                    size_t count=inst.call_args.size()-1;
                    auto* size=context_->getConstantInt(context_->getIntegerType(64),std::max<size_t>(8,count*8));
                    auto* values=entry_alloc(context_->getPointerType(context_->getIntegerType(64)), size);auto* types=entry_alloc(context_->getPointerType(context_->getIntegerType(64)), size);
                    auto ffi_type=[](LIR::Type type)->uint64_t {switch(type) {
                        case LIR::Type::I8:return 0;case LIR::Type::U8:case LIR::Type::Bool:return 1;case LIR::Type::I16:return 2;case LIR::Type::U16:return 3;
                        case LIR::Type::I32:return 4;case LIR::Type::U32:return 5;case LIR::Type::I64:return 6;case LIR::Type::U64:return 7;
                        case LIR::Type::F32:return 8;case LIR::Type::F64:return 9;case LIR::Type::Ptr:return 10;case LIR::Type::Void:return 12;
                        default:throw std::runtime_error("Unsupported canonical FFI scalar type");}};
                    for(size_t index=0;index<count;++index) {
                        auto type=index+1<inst.call_arg_types.size()?inst.call_arg_types[index+1]:LIR::Type::Void;
                        auto* original=load_reg(inst.call_args[index+1],type);
                        bool inferred=type==LIR::Type::Void;
                        if(inferred) type=original->getType()->isFloatingPoint()?LIR::Type::F64:LIR::Type::I64;
                        auto* value=erased_word(original);auto* offset=context_->getConstantInt(context_->getIntegerType(64),index*8);
                        builder_->createStore(value,builder_->createAdd(values,offset));
                        auto* type_id=inferred?builder_->createExternCall("lymar_aot_ffi_infer_type",{value},context_->getIntegerType(64)):static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64),ffi_type(type)));
                        builder_->createStore(type_id,builder_->createAdd(types,offset));
                    }
                    result=builder_->createExternCall("lymar_aot_foreign_call",{load_reg(inst.call_args[0],LIR::Type::Ptr),values,types,context_->getConstantInt(context_->getIntegerType(64),count),context_->getConstantInt(context_->getIntegerType(64),ffi_type(inst.result_type))},context_->getIntegerType(64));
                }
                // lymar_aot_foreign_call*/foreign_call_impl always return a
                // tagged LmValue word (SMI, float box, string, ffi ptr box, or
                // nil). Erased destinations keep the tagged word; scalar and
                // object destinations must untag exactly once or the SMI
                // encoding leaks into raw-int consumers (and gets tagged a
                // second time on the next erased boundary).
                if(inst.dst!=UINT32_MAX) {
                    if (lang_type_holds_tagged_word(inst.dst)) {
                        store_reg(inst.dst, result, inst.result_type, true);
                    } else {
                        store_reg(inst.dst, untag_word(result, inst.dst, inst.result_type), inst.result_type);
                    }
                }
                break;
            }
            case LIR::LIR_Op::CallbackCreate: {
                ir::Value* result=nullptr;
                if(inst.imm==1) result=builder_->createExternCall("lymar_aot_callback_pointer",{load_reg(inst.a,LIR::Type::I64)},context_->getIntegerType(64));
                else {
                    if(inst.call_args.size()!=3) throw std::runtime_error("Malformed callback_create arguments");
                    result=builder_->createExternCall("lymar_aot_callback_create",{load_reg(inst.call_args[0],LIR::Type::Ptr),load_reg(inst.call_args[1],LIR::Type::Ptr),load_reg(inst.call_args[2],LIR::Type::I64)},context_->getIntegerType(64));
                }
                if(inst.dst!=UINT32_MAX) store_reg(inst.dst,result,inst.result_type,true);
                break;
            }
            case LIR::LIR_Op::CallbackDestroy:
                builder_->createExternCall("lymar_aot_callback_destroy",{load_reg(inst.a,LIR::Type::I64)},context_->getVoidType());break;
            case LIR::LIR_Op::ForeignCallDirect: {
                // Direct C-extern call (`import "c:"`). Two shapes share this op:
                //  - type_a == Void: wrapper path (c_call_* intrinsic inside the
                //    generated binding). The extern is declared i64/f64 and the
                //    wrapper body performs any narrow-return fixup in Lymar.
                //  - type_a != Void: call-site lowering of a registered c-import
                //    wrapper (AOT). type_a carries the precise C return type so
                //    the extern gets the true ABI width and the raw result is
                //    masked/sign-extended into the Lymar i64 word here.
                const bool precise_ret = inst.type_a != LIR::Type::Void;
                auto c_ret_ty = [&](LIR::Type t) -> ir::Type* {
                    switch (t) {
                        case LIR::Type::Void: return context_->getVoidType();
                        case LIR::Type::F32:  return context_->getFloatType();
                        case LIR::Type::F64:  return context_->getDoubleType();
                        case LIR::Type::I64:
                        case LIR::Type::U64:
                        case LIR::Type::Ptr:  return context_->getIntegerType(64);
                        default:              return context_->getIntegerType(32);
                    }
                };
                auto c_param_ty = [&](LIR::Type t) -> ir::Type* {
                    switch (t) {
                        case LIR::Type::F32:  return context_->getFloatType();
                        case LIR::Type::F64:  return context_->getDoubleType();
                        default:              return context_->getIntegerType(64);
                    }
                };
                // Non-precise (wrapper-path) calls declare the extern return
                // from the Lymar result type; an f32 stub still needs a true
                // `float` return so the ABI reads xmm0, not rax.
                ir::Type* ret_ty = precise_ret ? c_ret_ty(inst.type_a)
                    : (inst.result_type == LIR::Type::F32 ? context_->getFloatType()
                                                         : lir_type_to_fyra_type(inst.result_type));

                // Struct-by-value signatures (`import "c:"` with flat C
                // structs): type_name holds the c-direct registry key so the
                // full C signature (field layouts) is recoverable here.
                const auto* csig = precise_ret && !inst.type_name.empty()
                    ? LM::Backend::Native::find_c_direct_signature(inst.type_name) : nullptr;
                bool sig_has_struct = false;
                if (csig) {
                    using CType = LM::Backend::Native::CType;
                    if (csig->return_type.kind == CType::Struct) sig_has_struct = true;
                    for (const auto& at : csig->arg_types)
                        if (at.kind == CType::Struct) sig_has_struct = true;
                }

                ir::Function* cfn = nullptr;
                std::vector<ir::Value*> args;
                ir::Value* res = nullptr;
                ir::Value* struct_out = nullptr; // non-null: result already a pubptr word
                if (sig_has_struct) {
                    using CType = LM::Backend::Native::CType;
                    using CStructDef = LM::Backend::Native::CStructDef;
                    auto i64ty = context_->getIntegerType(64);
                    auto f64ty = context_->getDoubleType();
                    auto c64 = [&](uint64_t v) -> ir::Value* {
                        return static_cast<ir::Value*>(context_->getConstantInt(i64ty, v));
                    };
                    const CType& cret = csig->return_type;
                    const bool ret_st = cret.kind == CType::Struct && cret.def && cret.def->supported;
                    // Exact-byte struct copy via widest-aligned chunks.
                    // (ir::Blit has no x64 lowering, so emit load/store pairs.)
                    auto struct_copy = [&](ir::Value* dst, ir::Value* src, uint32_t sz) {
                        uint32_t off = 0;
                        while (off < sz) {
                            uint32_t rem = sz - off;
                            ir::Value* dp = off ? builder_->createAdd(dst, c64(off)) : dst;
                            ir::Value* sp2 = off ? builder_->createAdd(src, c64(off)) : src;
                            if (rem >= 8) {
                                builder_->createStorel(builder_->createLoadl(sp2), dp);
                                off += 8;
                            } else if (rem >= 4) {
                                builder_->createStore(builder_->createLoaduw(sp2), dp);
                                off += 4;
                            } else if (rem >= 2) {
                                builder_->createStoreh(builder_->createLoaduh(sp2), dp);
                                off += 2;
                            } else {
                                builder_->createStoreb(builder_->createLoadub(sp2), dp);
                                off += 1;
                            }
                        }
                    };
                    // SysV >8B aggregate returns use register pairs or sret
                    // depending on eightbyte classes; only <=8B is modeled
                    // natively, larger struct returns stay on the wrapper.
                    const bool native_ok = c_abi_windows_ || !ret_st || cret.def->size <= 8;
                    if (!native_ok) {
                        // Fallback: call the generated ffi.foreign_call wrapper
                        // (kept reachable via the type_name call edge).
                        ir::Function* wf = current_module_->getFunction(inst.type_name);
                        if (!wf) {
                            std::vector<ir::Type*> wpts;
                            for (const auto& at : csig->arg_types)
                                wpts.push_back((at.kind == CType::Double || at.kind == CType::Float)
                                    ? static_cast<ir::Type*>(f64ty) : static_cast<ir::Type*>(i64ty));
                            wf = builder_->createFunction(inst.type_name,
                                lir_type_to_fyra_type(inst.result_type), wpts);
                        }
                        std::vector<ir::Value*> wargs;
                        for (size_t i = 0; i < inst.call_args.size(); ++i) {
                            const CType& at = csig->arg_types[i];
                            if (at.kind == CType::Double || at.kind == CType::Float)
                                wargs.push_back(load_reg(inst.call_args[i], LIR::Type::F64));
                            else
                                wargs.push_back(load_reg(inst.call_args[i], LIR::Type::I64));
                        }
                        ir::Value* wres = builder_->createCall(wf, wargs);
                        if (inst.dst != UINT32_MAX && inst.result_type != LIR::Type::Void)
                            store_reg(inst.dst, wres, inst.result_type);
                        break;
                    }

                    // SysV eightbyte classification: INTEGER (GP reg) unless
                    // every field touching the eightbyte is float/double.
                    auto eightbyte_is_sse = [](const CStructDef& d, int eb) -> bool {
                        bool has_int = false, has_flt = false;
                        for (const auto& f : d.fields) {
                            bool flt = f.type.kind == CType::Float || f.type.kind == CType::Double;
                            uint32_t fsz = c_scalar_size(f.type);
                            for (uint32_t b = f.offset; b < f.offset + fsz; ++b) {
                                if (int(b / 8) != eb) continue;
                                if (flt) has_flt = true; else has_int = true;
                            }
                        }
                        return !has_int && has_flt;
                    };

                    // Win64 sret: aggregates >8B or with size not in {1,2,4,8}
                    // take a hidden pointer first parameter.
                    bool need_sret = false;
                    ir::Value* sret_buf = nullptr;
                    if (ret_st && c_abi_windows_) {
                        uint32_t rsz = cret.def->size;
                        need_sret = !(rsz == 1 || rsz == 2 || rsz == 4 || rsz == 8);
                    }
                    std::vector<ir::Type*> ptypes;
                    if (need_sret) {
                        sret_buf = builder_->createExternCall("memory.alloc", {c64(cret.def->size)}, i64ty);
                        ptypes.push_back(i64ty);
                        args.push_back(sret_buf);
                    }
                    for (size_t i = 0; i < inst.call_args.size(); ++i) {
                        const CType& at = csig->arg_types[i];
                        uint32_t r = inst.call_args[i];
                        if (at.kind != CType::Struct) {
                            LIR::Type lat = i < inst.call_arg_types.size() ? inst.call_arg_types[i] : LIR::Type::I64;
                            ptypes.push_back(c_param_ty(lat));
                            if (lat == LIR::Type::F32 || lat == LIR::Type::F64) {
                                ir::Value* fv = load_reg(r, LIR::Type::F64);
                                args.push_back(lat == LIR::Type::F32
                                    ? builder_->createCast(fv, context_->getFloatType()) : fv);
                            } else {
                                args.push_back(load_reg(r, LIR::Type::I64));
                            }
                            continue;
                        }
                        const auto& sd = *at.def;
                        uint32_t sz = sd.size;
                        ir::Value* sp = load_reg(r, LIR::Type::I64);
                        if (c_abi_windows_) {
                            if (sz == 8) {
                                ptypes.push_back(i64ty);
                                args.push_back(builder_->createLoadl(sp));
                            } else if (sz == 4 || sz == 2 || sz == 1) {
                                ptypes.push_back(i64ty);
                                ir::Value* v = sz == 4 ? builder_->createLoaduw(sp)
                                    : sz == 2 ? builder_->createLoaduh(sp)
                                              : builder_->createLoadub(sp);
                                args.push_back(builder_->createExtUW(v, i64ty));
                            } else {
                                // 3,5,6,7,9..16 bytes: passed by reference to a
                                // caller-owned copy (byval semantics).
                                auto* tmp = entry_alloc(i64ty, c64(sz));
                                struct_copy(tmp, sp, sz);
                                ptypes.push_back(i64ty);
                                args.push_back(tmp);
                            }
                        } else if (sz > 16) {
                            // SysV MEMORY class: aggregates over 16 bytes are
                            // passed by invisible reference to a caller copy.
                            auto* tmp = entry_alloc(i64ty, c64(sz));
                            struct_copy(tmp, sp, sz);
                            ptypes.push_back(i64ty);
                            args.push_back(tmp);
                        } else {
                            // SysV: one IR param per eightbyte, INTEGER->i64,
                            // SSE->f64. Copy into a 16B temp first so full
                            // eightbyte loads stay in bounds for odd sizes.
                            auto* tmp = entry_alloc(i64ty, c64(16));
                            struct_copy(tmp, sp, sz);
                            int ne = int((sz + 7) / 8);
                            for (int eb = 0; eb < ne; ++eb) {
                                ir::Value* ep = eb ? builder_->createAdd(tmp, c64(8)) : tmp;
                                if (eightbyte_is_sse(sd, eb)) {
                                    ptypes.push_back(f64ty);
                                    args.push_back(builder_->createLoadd(ep));
                                } else {
                                    ptypes.push_back(i64ty);
                                    args.push_back(builder_->createLoadl(ep));
                                }
                            }
                        }
                    }
                    // Extern return type: sret echoes the buffer ptr (i64,
                    // ignored); Win64 small structs return in rax (i64);
                    // SysV <=8B returns in rax (INTEGER) or xmm0 (SSE).
                    ir::Type* cret_ty = ret_ty;
                    if (ret_st) {
                        if (need_sret) cret_ty = i64ty;
                        else if (c_abi_windows_) cret_ty = i64ty;
                        else cret_ty = eightbyte_is_sse(*cret.def, 0)
                            ? static_cast<ir::Type*>(f64ty) : static_cast<ir::Type*>(i64ty);
                    }
                    cfn = current_module_->getFunction(inst.func_name);
                    if (!cfn) {
                        auto created = std::make_unique<ir::Function>(cret_ty, inst.func_name, current_module_.get());
                        for (size_t pi = 0; pi < ptypes.size(); ++pi) {
                            created->addParameter(std::make_unique<ir::Parameter>(
                                ptypes[pi], "s" + std::to_string(pi)));
                        }
                        current_module_->addFunction(std::move(created));
                        cfn = current_module_->getFunction(inst.func_name);
                    }
                    res = builder_->createCall(cfn, args);
                    if (need_sret) {
                        struct_out = sret_buf;
                    } else if (ret_st) {
                        // Register return: copy the raw register bytes into a
                        // fresh 8-byte buffer (struct_size <= 8 here).
                        ir::Value* rbuf = builder_->createExternCall("memory.alloc", {c64(8)}, i64ty);
                        if (res->getType() && res->getType()->isFloatingPoint())
                            builder_->createStored(res, rbuf);
                        else
                            builder_->createStorel(res, rbuf);
                        struct_out = rbuf;
                    }
                } else {
                cfn = current_module_->getFunction(inst.func_name);
                if (!cfn) {
                    auto created = std::make_unique<ir::Function>(ret_ty, inst.func_name, current_module_.get());
                    cfn = created.get();
                    for (size_t i = 0; i < inst.call_args.size(); ++i) {
                        LIR::Type at = i < inst.call_arg_types.size() ? inst.call_arg_types[i] : LIR::Type::I64;
                        cfn->addParameter(std::make_unique<ir::Parameter>(
                            c_param_ty(at), "a" + std::to_string(i)));
                    }
                    current_module_->addFunction(std::move(created));
                }
                for (size_t i = 0; i < inst.call_args.size(); ++i) {
                    LIR::Type at = i < inst.call_arg_types.size() ? inst.call_arg_types[i] : LIR::Type::I64;
                    if (at == LIR::Type::F32 || at == LIR::Type::F64) {
                        // Float-family registers always hold f64 words in AOT;
                        // C `float` params get a real f32 via cvtsd2ss.
                        ir::Value* fv = load_reg(inst.call_args[i], LIR::Type::F64);
                        args.push_back(at == LIR::Type::F32
                            ? builder_->createCast(fv, context_->getFloatType()) : fv);
                    } else {
                        args.push_back(load_reg(inst.call_args[i], LIR::Type::I64));
                    }
                }
                res = builder_->createCall(cfn, args);
                }
                if (inst.dst != UINT32_MAX && res && inst.result_type != LIR::Type::Void) {
                    ir::Value* out = struct_out ? struct_out : res;
                    if (precise_ret && !struct_out) {
                        // Narrow C returns leave undefined bits above the return
                        // width in rax: mask to the width, then extend to the
                        // Lymar i64 word (signed types sign-extend).
                        auto i64ty = context_->getIntegerType(64);
                        auto i32ty = context_->getIntegerType(32);
                        auto c32 = [&](uint64_t v) {
                            return static_cast<ir::Value*>(context_->getConstantInt(i32ty, v));
                        };
                        switch (inst.type_a) {
                            case LIR::Type::I64: case LIR::Type::U64:
                            case LIR::Type::Ptr: case LIR::Type::F64:
                                break; // already the Lymar word width
                            case LIR::Type::F32:
                                break; // float result widened below
                            case LIR::Type::I32:
                                out = builder_->createExtSW(res, i64ty); break;
                            case LIR::Type::U32:
                                out = builder_->createExtUW(res, i64ty); break;
                            case LIR::Type::I16: {
                                auto* m = builder_->createAnd(res, c32(0xFFFF));
                                out = builder_->createExtSH(m, i64ty); break;
                            }
                            case LIR::Type::U16: {
                                auto* m = builder_->createAnd(res, c32(0xFFFF));
                                out = builder_->createExtUH(m, i64ty); break;
                            }
                            case LIR::Type::I8: {
                                auto* m = builder_->createAnd(res, c32(0xFF));
                                out = builder_->createExtSB(m, i64ty); break;
                            }
                            case LIR::Type::U8: {
                                auto* m = builder_->createAnd(res, c32(0xFF));
                                out = builder_->createExtUB(m, i64ty); break;
                            }
                            case LIR::Type::Bool: {
                                auto* m = builder_->createAnd(res, c32(1));
                                out = builder_->createExtUW(m, i64ty); break;
                            }
                            default:
                                out = builder_->createCast(res, i64ty); break;
                        }
                    }
                    // C `float` returns arrive as f32 in xmm0; AOT float
                    // registers hold f64 words, so widen before storing.
                    if (out->getType() && out->getType()->isFloatTy())
                        out = builder_->createCast(out, context_->getDoubleType());
                    store_reg(inst.dst, out, inst.result_type);
                }
                break;
            }
            default:
                throw std::runtime_error("Fyra lowering does not implement LIR opcode " +
                    LIR::lir_op_to_string(inst.op) + " in " + lir_func.name);
        }
    }
    if (!terminated && builder_->getInsertPoint())
        builder_->createRet(main_fn->getName() == "main" || dctx
            ? static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64),
                main_fn->getName() == "main" ? 0 : 2))
            : builder_->createExternCall("lymar_aot_nil", {}, context_->getIntegerType(64)));
}

} // namespace LM::Backend::Fyra

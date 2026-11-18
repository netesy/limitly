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
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "../../lir/function_registry.hh"
#include "../../lir/builtin_functions.hh"
#include "../../lir/builtin_callable.hh"
#include "../../frontend/module_manager.hh"

namespace LM::Backend::Fyra {

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
            if (!callee.empty() && registry.getFunction(callee)) {
                if (reachable_funcs.find(callee) == reachable_funcs.end()) {
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
        // Fixpoint: newly discovered constructions can unlock trait
        // candidates skipped in earlier rounds; re-seed every recorded
        // site and drain again until the constructed set stops growing.
        if (constructed_version == seeded_constructed_version) break;
        seeded_constructed_version = constructed_version;
        for (const auto& site : trait_sites) {
            try_seed_trait_candidates(site.first, site.second);
        }
    }
    constructed_frames_ = constructed_frames;

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
        if (reachable_funcs.find(func_name) == reachable_funcs.end() && !func_name.ends_with(".__init__")) continue;
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
        if (reachable_funcs.find(func_name) == reachable_funcs.end() && !func_name.ends_with(".__init__")) continue;
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

void LIRToFyraIRBuilder::build_function_body(ir::Function* main_fn, const LIR::LIR_Function& lir_func) {
    ir::BasicBlock* entry_bb = builder_->createBasicBlock("entry", main_fn);
    builder_->setInsertPoint(entry_bb);
    ir::Value* caller_region = Memory::runtime_regions_proven_unnecessary(lir_func)
        ? static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64), 0))
        : builder_->createExternCall("lymar_aot_region_current", {}, context_->getIntegerType(64));

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
        if (inst.dst < lir_func.param_count) reassigned_parameters.insert(inst.dst);
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
    // Bitwise/shift ops route through lymar_aot_bitwise only for erased-word
    // operands: boxed i128/u128 words (Ptr-classified or 128-bit language
    // types). Plain u64 stays on the native path -- its raw-word representation
    // already matches the hardware ops and the runtime helper's i64-fitting
    // fast path would mis-box high-bit results.
    auto bitwise_operand_erased = [&](uint32_t reg, LIR::Type type) {
        if (reg == UINT32_MAX) return false;
        if (pointer_assigned_regs.count(reg)) return true;
        if (type == LIR::Type::Ptr) return true;
        auto rt = lir_func.register_types.find(reg);
        if (rt != lir_func.register_types.end() && rt->second == LIR::Type::Ptr) return true;
        auto lt = lir_func.register_language_types.find(reg);
        if (lt != lir_func.register_language_types.end() && lt->second &&
            (lt->second->tag == ::TypeTag::Int128 || lt->second->tag == ::TypeTag::UInt128)) return true;
        return false;
    };
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
                break;
            case LIR::LIR_Op::LoadGlobal: {
                // Global cells are untyped: result_type is always Ptr, so the
                // default case would object-classify every load. The value's
                // kind must come from the variable's declared type recorded on
                // dst by the generator. Only provably-scalar globals escape
                // object classification; unknown/pointer-ish types stay object
                // so strings/frames/`any` keep working. Without this,
                // `var g: int = 0` loads (0, object-kind) which is_nil treats
                // as nil.
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
                if (!scalar_global) pointer_assigned_regs.insert(inst.dst);
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
                // Container/frame reads return erased words: floats are heap
                // boxes and misses yield the nil word, so an F64/F32 result is
                // an object word, not a native double. Marking it keeps nil
                // comparisons (raw word == lymar_aot_nil()) and kind=1 float
                // unboxing correct.
                if (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32)
                    pointer_assigned_regs.insert(inst.dst);
                break;
            case LIR::LIR_Op::IAdd_Unchecked:
            case LIR::LIR_Op::Add:
            case LIR::LIR_Op::Sub:
            case LIR::LIR_Op::Mul:
            case LIR::LIR_Op::Div:
            case LIR::LIR_Op::Mod:
            case LIR::LIR_Op::Neg: {
                // Erased arithmetic lowers to lymar_aot_numeric_binary, whose
                // result is an erased word (raw int or heap box, kind tracked
                // dynamically). When either operand can be erased the result
                // must stay object-classified or downstream consumers read the
                // box pointer as a raw integer.
                auto operand_may_be_erased = [&](uint32_t reg, LIR::Type type) {
                    if (reg == UINT32_MAX) return false;
                    if (pointer_assigned_regs.count(reg)) return true;
                    if (type == LIR::Type::Ptr || type == LIR::Type::U64) return true;
                    auto rt = lir_func.register_types.find(reg);
                    if (rt != lir_func.register_types.end() &&
                        (rt->second == LIR::Type::Ptr || rt->second == LIR::Type::U64)) return true;
                    auto lt = lir_func.register_language_types.find(reg);
                    if (lt != lir_func.register_language_types.end() && lt->second &&
                        (lt->second->tag == ::TypeTag::Int128 || lt->second->tag == ::TypeTag::UInt128))
                        return true;
                    return false;
                };
                if (operand_may_be_erased(inst.a, inst.type_a) ||
                    operand_may_be_erased(inst.b, inst.type_b))
                    pointer_assigned_regs.insert(inst.dst);
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
                if (bitwise_operand_erased(inst.a, inst.type_a) ||
                    bitwise_operand_erased(inst.b, inst.type_b) ||
                    bitwise_operand_erased(inst.dst, LIR::Type::I64))
                    pointer_assigned_regs.insert(inst.dst);
                break;
            default:
                if (inst.result_type == LIR::Type::Ptr) pointer_assigned_regs.insert(inst.dst);
                break;
        }
    }
    // A `Mov` copies the value *and* its dynamic kind (store_reg is called with
    // preserve_kind), but the static scan above only marks the producer. Without
    // propagation, `var r = ffi.foreign_call(...)` lands in a scalar-classified
    // slot and every later load reports kind=0 — boxed FFI results (PTR/F64/
    // CString) then surface as raw addresses. Propagate to a fixpoint so move
    // chains (`var a = f(); var b = a;`) stay object-classified.
    bool moved = true;
    while (moved) {
        moved = false;
        for (const auto& inst : lir_func.instructions) {
            if (inst.dst == UINT32_MAX || pointer_assigned_regs.count(inst.dst)) continue;
            bool propagate = false;
            if (inst.op == LIR::LIR_Op::Mov) {
                // Mov's source is `a` only (registers[dst] = registers[a]); `b` is
                // an unused operand emitted as literal 0, which is a valid register
                // number — checking it would false-positive on r0.
                propagate = inst.a != UINT32_MAX && pointer_assigned_regs.count(inst.a);
            } else if (inst.op == LIR::LIR_Op::IAdd_Unchecked || inst.op == LIR::LIR_Op::Add ||
                       inst.op == LIR::LIR_Op::Sub || inst.op == LIR::LIR_Op::Mul ||
                       inst.op == LIR::LIR_Op::Div || inst.op == LIR::LIR_Op::Mod ||
                       inst.op == LIR::LIR_Op::Neg) {
                // Same erased-word propagation as the prepass scan, for operand
                // definitions that appear later in the instruction stream.
                propagate = (inst.a != UINT32_MAX && pointer_assigned_regs.count(inst.a)) ||
                            (inst.b != UINT32_MAX && pointer_assigned_regs.count(inst.b));
            }
            if (propagate) {
                pointer_assigned_regs.insert(inst.dst);
                moved = true;
            }
        }
    }

    std::unordered_map<uint32_t, ir::Instruction*> reg_slots;
    const bool scalar_registers = Memory::runtime_regions_proven_unnecessary(lir_func) && Memory::proven_scalar_leaf(lir_func);
    auto is_pointer_lang_type = [&](uint32_t reg) -> bool {
        auto it = lir_func.register_language_types.find(reg);
        if (it != lir_func.register_language_types.end() && it->second) {
            auto tag = it->second->tag;
            if (tag == ::TypeTag::List || tag == ::TypeTag::String || tag == ::TypeTag::Frame ||
                tag == ::TypeTag::Dict || tag == ::TypeTag::Tuple || tag == ::TypeTag::Any ||
                tag == ::TypeTag::Enum || tag == ::TypeTag::Trait || tag == ::TypeTag::TraitObject ||
                tag == ::TypeTag::Union || tag == ::TypeTag::ErrorUnion ||
                tag == ::TypeTag::Nil || tag == ::TypeTag::Int128 || tag == ::TypeTag::UInt128)
                return true;
        }
        auto it2 = lir_func.register_types.find(reg);
        if (it2 != lir_func.register_types.end() && it2->second == LIR::Type::Ptr) return true;
        return false;
    };

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
        builder_->setInsertPoint(entry_bb);
        if (!size) size = context_->getConstantInt(context_->getIntegerType(64), 8);
        auto* inst = builder_->createAlloc(size, type ? type : context_->getIntegerType(64));
        if (saved_ip) builder_->setInsertPoint(saved_ip);
        return inst;
    };

    // Initialize registers from function parameters
    size_t param_idx = 0;
    for (const auto& param : main_fn->getParameters()) {
        if (!scalar_registers) builder_->createStore(param.get(), reg_slots[param_idx]);
        regs[param_idx] = param.get();
        register_definitions[param_idx] = nullptr;
        if (param->getType() && (param->getType()->isDoubleTy() || param->getType()->isFloatTy())) {
            reg_types[param_idx] = LIR::Type::F64;
        } else {
            auto it = lir_func.register_types.find(param_idx);
            if (it != lir_func.register_types.end()) {
                reg_types[param_idx] = it->second;
            }
        }
        param_idx++;
    }

    auto is_typed_primitive_list = [&](uint32_t r) -> bool {
        auto it = lir_func.register_language_types.find(r);
        if (it != lir_func.register_language_types.end() && it->second && it->second->tag == ::TypeTag::List) {
            auto* lt = std::get_if<ListType>(&it->second->extra);
            if (lt && lt->elementType) {
                auto etag = lt->elementType->tag;
                if (etag != ::TypeTag::List && etag != ::TypeTag::String &&
                    etag != ::TypeTag::Frame && etag != ::TypeTag::Dict &&
                    etag != ::TypeTag::Tuple && etag != ::TypeTag::Any &&
                    etag != ::TypeTag::Enum && etag != ::TypeTag::Trait &&
                    etag != ::TypeTag::TraitObject &&
                    // Floats/decimals box to heap objects — element stores need
                    // ownership edges, so they are not "primitive" lists.
                    etag != ::TypeTag::Float32 && etag != ::TypeTag::Float64 &&
                    etag != ::TypeTag::Decimal2 && etag != ::TypeTag::Decimal4 &&
                    etag != ::TypeTag::Decimal6) {
                    return true;
                }
            }
        }
        return false;
    };

    std::unordered_map<uint32_t, ir::Value*> hoisted_data_ptrs;
    size_t num_params = main_fn->getParameters().size();
    for (size_t p = 0; p < num_params; ++p) {
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

    auto erased_word = [&](ir::Value* value) -> ir::Value* {
        if (value->getType()->isFloatingPoint())
            return builder_->createExternCall("lymar_aot_box_float", {value}, context_->getIntegerType(64));
        return value;
    };

    // Kind argument for lymar_aot_to_float/to_integer/scalar_to_string: 1
    // (object) when the register holds an erased word that may be a heap box
    // or the nil word, 0 (scalar) for raw integers/doubles.
    auto word_kind = [&](uint32_t r) -> ir::Value* {
        bool object = pointer_assigned_regs.count(r) || is_pointer_lang_type(r);
        return context_->getConstantInt(context_->getIntegerType(64), object ? 1 : 0);
    };

    auto store_reg = [&](uint32_t r, ir::Value* v, LIR::Type t, bool preserve_kind = false) {
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
            v = builder_->createExternCall("lymar_aot_to_float", {v, word_kind(r)}, context_->getDoubleType());
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

    auto load_float_reg = [&](uint32_t r, LIR::Type t) -> ir::Value* {
        // Cached SSA values may be erased even when the source register is
        // numerically typed. Convert the actual value, not just its annotation.
        ir::Value* v = load_reg(r, t);
        if (v && !v->getType()->isFloatingPoint()) {
            return builder_->createExternCall("lymar_aot_to_float", {v, word_kind(r)}, context_->getDoubleType());
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
        if ((name == "clock" || name == "time.clock") && args.empty())
            return builder_->createExternCall("lymar_aot_clock", {}, context_->getDoubleType());
        if(name=="time" && args.empty())
            return builder_->createExternCall("lymar_aot_time",{},context_->getIntegerType(64));
        if (name == "_builtin_string_hash_bytes" && args.size() == 1)
            return builder_->createExternCall("lymar_aot_string_hash", {erased_word(args[0]), zero},
                context_->getIntegerType(64));
        if (name == "_builtin_list_slice" && args.size() == 3)
            return builder_->createExternCall("lymar_aot_list_slice",
                {erased_word(args[0]), erased_word(args[1]), erased_word(args[2]), zero, zero, zero},
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
    for (size_t i = 0; i < lir_func.instructions.size(); ++i) {
        const auto& inst = lir_func.instructions[i];

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
                    context_->getConstantInt(context_->getIntegerType(64), inst.imm), caller_region}, context_->getIntegerType(64));
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
            case LIR::LIR_Op::RegionMove:
                builder_->createExternCall("lymar_aot_region_move", {load_reg(inst.a, inst.type_a),
                    context_->getConstantInt(context_->getIntegerType(64), inst.imm), caller_region,
                    context_->getConstantInt(context_->getIntegerType(64), 0)}, nullptr);
                break;
            case LIR::LIR_Op::FrameCallDeinit:
                builder_->createExternCall("lymar_aot_finalize", {load_reg(inst.a, inst.type_a)}, nullptr);
                break;
            case LIR::LIR_Op::Mov: {
                if (reg_decimal_scales.count(inst.a)) reg_decimal_scales[inst.dst] = reg_decimal_scales[inst.a];
                if (reg_int_values.count(inst.a)) reg_int_values[inst.dst] = reg_int_values[inst.a];
                if (reg_float_values.count(inst.a)) reg_float_values[inst.dst] = reg_float_values[inst.a];
                if (reg_string_literals.count(inst.a)) reg_string_literals[inst.dst] = reg_string_literals[inst.a];
                if (reg_types.count(inst.a)) reg_types[inst.dst] = reg_types[inst.a];
                else if (inst.type_a != LIR::Type::Void) reg_types[inst.dst] = inst.type_a;
                auto destination_type = reg_types.count(inst.dst) ? reg_types[inst.dst] : inst.result_type;
                if (auto info = lir_func.register_language_types.find(inst.dst); info != lir_func.register_language_types.end() && info->second && info->second->tag == ::TypeTag::Any) {
                    // An `any` binding must still carry the dynamic kind of a
                    // concrete scalar source (e.g. a typed-list iter element):
                    // the raw word is not a pointer, and object-kind consumers
                    // would misread it. Erase to Ptr only for non-scalar sources.
                    auto src = reg_types.find(inst.a);
                    const bool src_is_scalar = src != reg_types.end() &&
                        src->second != LIR::Type::Ptr && src->second != LIR::Type::Void;
                    if (!src_is_scalar) destination_type = LIR::Type::Ptr;
                }
                // A move copies the value and its dynamic kind. In particular,
                // a missing typed-container lookup remains nil through aliases.
                store_reg(inst.dst, load_reg(inst.a, inst.type_a), destination_type, true);
                break;
            }
            case LIR::LIR_Op::LoadConst: {
                if (inst.type_name == "d2" || inst.type_name == "decimal") reg_decimal_scales[inst.dst] = 2;
                else if (inst.type_name == "d4") reg_decimal_scales[inst.dst] = 4;
                else if (inst.type_name == "d6") reg_decimal_scales[inst.dst] = 6;

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
                    ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), actual_val);
                    reg_int_values[inst.dst] = actual_val;
                    reg_types[inst.dst] = LIR::Type::I64;
                    store_reg(inst.dst, c, LIR::Type::I64);
                } else if (IS_BOOL(val)) {
                    uint64_t actual_val = UNBOX_BOOL(val) ? 1 : 0;
                    ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), actual_val);
                    store_reg(inst.dst, c, LIR::Type::Bool);
                } else if (IS_PTR(val)) {
                    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
                    if (h->type_id == TYPE_I64 || (h->type_id == TYPE_U64 && as_u128(val) <= INT64_MAX)) {
                        auto number = as_i64(val);
                        reg_int_values[inst.dst] = number;
                        store_reg(inst.dst, context_->getConstantInt(context_->getIntegerType(64), number), LIR::Type::I64);
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
                            ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), actual_val);
                            store_reg(inst.dst, c, inst.result_type);
                        } else if (box->type == LM_BOX_FLOAT) {
                            double fval = box->value.as_float;
                            ir::Value* c = context_->getConstantFP(context_->getDoubleType(), fval);
                            reg_types[inst.dst] = LIR::Type::F64;
                            reg_float_values[inst.dst] = fval;
                            store_reg(inst.dst, c, LIR::Type::F64);
                        } else if (box->type == LM_BOX_BOOL) {
                            ir::Value* c = context_->getConstantInt(context_->getIntegerType(64), box->value.as_bool ? 1 : 0);
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
                bool is_float_g = (inst.type_a == LIR::Type::F64 || inst.type_a == LIR::Type::F32 ||
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
                bool is_float_g = ((global_types_.count(gname) && (global_types_[gname] == LIR::Type::F64 || global_types_[gname] == LIR::Type::F32)) ||
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
                    store_reg(inst.dst, loaded, inst.result_type);
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
                    auto* result=builder_->createExternCall("lymar_aot_numeric_binary",{erased_word(load_reg(inst.a,inst.type_a)),erased_word(load_reg(inst.b,inst.type_b)),context_->getConstantInt(context_->getIntegerType(64),0),context_->getConstantInt(context_->getIntegerType(64),0),context_->getConstantInt(context_->getIntegerType(64),0)},context_->getIntegerType(64));
                    // The result is an erased word: raw integer or heap box with
                    // a runtime-tracked kind. Ptr keeps it object-classified so
                    // slots carry the dynamic kind instead of reading the box
                    // pointer as a scalar.
                    store_reg(inst.dst,result,LIR::Type::Ptr,true);
                } else {
                    store_reg(inst.dst, builder_->createAdd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::Sub:
                if (is_float_op(inst)) {
                    store_float_reg(inst.dst, builder_->createFSub(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b)));
                } else if(erased_arithmetic(inst)) {
                    auto* result=builder_->createExternCall("lymar_aot_numeric_binary",{erased_word(load_reg(inst.a,inst.type_a)),erased_word(load_reg(inst.b,inst.type_b)),context_->getConstantInt(context_->getIntegerType(64),1),context_->getConstantInt(context_->getIntegerType(64),0),context_->getConstantInt(context_->getIntegerType(64),0)},context_->getIntegerType(64));
                    store_reg(inst.dst,result,LIR::Type::Ptr,true);
                } else {
                    store_reg(inst.dst, builder_->createSub(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::Mul:
                if (is_float_op(inst)) {
                    store_float_reg(inst.dst, builder_->createFMul(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b)));
                } else if(erased_arithmetic(inst)) {
                    auto* result=builder_->createExternCall("lymar_aot_numeric_binary",{erased_word(load_reg(inst.a,inst.type_a)),erased_word(load_reg(inst.b,inst.type_b)),context_->getConstantInt(context_->getIntegerType(64),2),context_->getConstantInt(context_->getIntegerType(64),0),context_->getConstantInt(context_->getIntegerType(64),0)},context_->getIntegerType(64));
                    store_reg(inst.dst,result,LIR::Type::Ptr,true);
                } else {
                    store_reg(inst.dst, builder_->createMul(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::Div:
                if (is_float_op(inst)) {
                    store_float_reg(inst.dst, builder_->createFDiv(load_float_reg(inst.a, inst.type_a), load_float_reg(inst.b, inst.type_b)));
                } else if(erased_arithmetic(inst)) {
                    auto* result=builder_->createExternCall("lymar_aot_numeric_binary",{erased_word(load_reg(inst.a,inst.type_a)),erased_word(load_reg(inst.b,inst.type_b)),context_->getConstantInt(context_->getIntegerType(64),3),context_->getConstantInt(context_->getIntegerType(64),0),context_->getConstantInt(context_->getIntegerType(64),0)},context_->getIntegerType(64));
                    store_reg(inst.dst,result,LIR::Type::Ptr,true);
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
                    auto* result=builder_->createExternCall("lymar_aot_numeric_binary",{erased_word(load_reg(inst.a,inst.type_a)),erased_word(load_reg(inst.b,inst.type_b)),context_->getConstantInt(context_->getIntegerType(64),4),context_->getConstantInt(context_->getIntegerType(64),0),context_->getConstantInt(context_->getIntegerType(64),0)},context_->getIntegerType(64));
                    store_reg(inst.dst,result,LIR::Type::Ptr,true);
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
                    auto* zero=context_->getConstantInt(context_->getIntegerType(64),0);
                    auto* result=builder_->createExternCall("lymar_aot_numeric_binary",{zero,erased_word(load_reg(inst.a,inst.type_a)),context_->getConstantInt(context_->getIntegerType(64),1),context_->getConstantInt(context_->getIntegerType(64),0),context_->getConstantInt(context_->getIntegerType(64),0)},context_->getIntegerType(64));
                    store_reg(inst.dst,result,LIR::Type::Ptr,true);
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
                    store_reg(inst.dst, builder_->createExternCall("lymar_aot_bitwise",
                        {erased_word(load_reg(inst.a, inst.type_a)), erased_word(load_reg(inst.b, inst.type_b)),
                         context_->getConstantInt(context_->getIntegerType(64), inst.op == LIR::LIR_Op::Shl ? 3 : 4),
                         word_kind(inst.a), word_kind(inst.b)}, context_->getIntegerType(64)), inst.result_type);
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
                    store_reg(inst.dst, builder_->createExternCall("lymar_aot_bitwise",
                        {erased_word(load_reg(inst.a, inst.type_a)), erased_word(load_reg(inst.b, inst.type_b)),
                         context_->getConstantInt(context_->getIntegerType(64), 0),
                         word_kind(inst.a), word_kind(inst.b)}, context_->getIntegerType(64)), inst.result_type);
                } else {
                    store_reg(inst.dst, builder_->createAnd(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::IOr_Unchecked:
            case LIR::LIR_Op::Or:
                if (bitwise_erased(inst)) {
                    store_reg(inst.dst, builder_->createExternCall("lymar_aot_bitwise",
                        {erased_word(load_reg(inst.a, inst.type_a)), erased_word(load_reg(inst.b, inst.type_b)),
                         context_->getConstantInt(context_->getIntegerType(64), 1),
                         word_kind(inst.a), word_kind(inst.b)}, context_->getIntegerType(64)), inst.result_type);
                } else {
                    store_reg(inst.dst, builder_->createOr(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::IXor_Unchecked:
            case LIR::LIR_Op::Xor:
                if (bitwise_erased(inst)) {
                    store_reg(inst.dst, builder_->createExternCall("lymar_aot_bitwise",
                        {erased_word(load_reg(inst.a, inst.type_a)), erased_word(load_reg(inst.b, inst.type_b)),
                         context_->getConstantInt(context_->getIntegerType(64), 2),
                         word_kind(inst.a), word_kind(inst.b)}, context_->getIntegerType(64)), inst.result_type);
                } else {
                    store_reg(inst.dst, builder_->createXor(load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)), inst.result_type);
                }
                break;
            case LIR::LIR_Op::CmpEQ:
            case LIR::LIR_Op::CmpNEQ: {
                auto* equal = builder_->createExternCall("lymar_aot_value_equal",
                    {erased_word(load_reg(inst.a, inst.type_a)), erased_word(load_reg(inst.b, inst.type_b)),
                     context_->getConstantInt(context_->getIntegerType(64), 0), context_->getConstantInt(context_->getIntegerType(64), 0)},
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
                        {erased_word(load_reg(inst.a, inst.type_a)), erased_word(load_reg(inst.b, inst.type_b)),
                         context_->getConstantInt(context_->getIntegerType(64), 0), context_->getConstantInt(context_->getIntegerType(64), 0)}, context_->getIntegerType(64));
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
                        {erased_word(load_reg(inst.a, inst.type_a)), erased_word(load_reg(inst.b, inst.type_b)),
                         context_->getConstantInt(context_->getIntegerType(64), 0), context_->getConstantInt(context_->getIntegerType(64), 0)}, context_->getIntegerType(64));
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
                        {erased_word(load_reg(inst.a, inst.type_a)), erased_word(load_reg(inst.b, inst.type_b)),
                         context_->getConstantInt(context_->getIntegerType(64), 0), context_->getConstantInt(context_->getIntegerType(64), 0)}, context_->getIntegerType(64));
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
                        {erased_word(load_reg(inst.a, inst.type_a)), erased_word(load_reg(inst.b, inst.type_b)),
                         context_->getConstantInt(context_->getIntegerType(64), 0), context_->getConstantInt(context_->getIntegerType(64), 0)}, context_->getIntegerType(64));
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

                // See CallBuiltin below: generic len() must not lower to the
                // list-only lm_list_len; route it through the kind-checked
                // runtime so scalars/i128 get the VM's error instead of a
                // wild offset-16 read.
                if (name == "len" && args.size() == 1 && !inst.call_args.empty()) {
                    auto* len_res = builder_->createExternCall("lymar_aot_length",
                        {erased_word(args[0]), word_kind(inst.call_args[0])},
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

                        if (ai < inst.call_args.size() && decimal_scale_for_reg(inst.call_args[ai]) > 0) {
                            FyraBuiltinFunctions::emit_print_decimal_inline(current_module_.get(), builder_.get(), args[ai], decimal_scale_for_reg(inst.call_args[ai]));
                        } else if (arg_type == LIR::Type::I64 || is_known_i64) {
                            builder_->createExternCall("lymar_aot_print_integer", {args[ai], context_->getConstantInt(context_->getIntegerType(64), 0)}, context_->getVoidType());
                        } else if (arg_type == LIR::Type::Ptr) {
                            builder_->createExternCall("lymar_aot_print_value", {erased_word(args[ai]), context_->getConstantInt(context_->getIntegerType(64), 0)}, context_->getVoidType());
                        } else if (arg_type == LIR::Type::Bool) {
                            FyraBuiltinFunctions::emit_print_bool_inline(current_module_.get(), builder_.get(), args[ai]);
                        } else if (arg_type == LIR::Type::F64 || arg_type == LIR::Type::F32) {
                            builder_->createExternCall("lymar_aot_print_float", {args[ai]}, context_->getVoidType());
                        } else {
                            builder_->createExternCall("lymar_aot_print_integer", {args[ai], context_->getConstantInt(context_->getIntegerType(64), 0)}, context_->getVoidType());
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
                    ir::Value* res = builder_->createExternCall("process.sleep", args, lir_type_to_fyra_type(inst.result_type));
                    if (inst.op == LIR::LIR_Op::Call && inst.dst != UINT32_MAX) store_reg(inst.dst, res, inst.result_type);
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
                std::vector<ir::Value*> site_args{erased_word(load_reg(inst.a, inst.type_a))};
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
                    {erased_word(raw_callee), context_->getConstantInt(context_->getIntegerType(64), 0)},
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
                    builder_->createStore(erased_word(call_res), res_slot);
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
                    builder_->createStore(erased_word(call_res), res_slot);
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
                    store_reg(inst.dst, dispatched_result, inst.result_type, true);
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
                        {erased_word(args[0]), word_kind(inst.call_args[0])},
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

                        if (ai < inst.call_args.size() && decimal_scale_for_reg(inst.call_args[ai]) > 0) {
                            FyraBuiltinFunctions::emit_print_decimal_inline(current_module_.get(), builder_.get(), args[ai], decimal_scale_for_reg(inst.call_args[ai]));
                        } else if (arg_type == LIR::Type::I64 || is_known_i64) {
                            builder_->createExternCall("lymar_aot_print_integer", {args[ai], context_->getConstantInt(context_->getIntegerType(64), 0)}, context_->getVoidType());
                        } else if (arg_type == LIR::Type::Ptr) {
                            builder_->createExternCall("lymar_aot_print_value", {erased_word(args[ai]), context_->getConstantInt(context_->getIntegerType(64), 0)}, context_->getVoidType());
                        } else if (arg_type == LIR::Type::Bool) {
                            FyraBuiltinFunctions::emit_print_bool_inline(current_module_.get(), builder_.get(), args[ai]);
                        } else if (arg_type == LIR::Type::F64 || arg_type == LIR::Type::F32) {
                            builder_->createExternCall("lymar_aot_print_float", {args[ai]}, context_->getVoidType());
                        } else {
                            builder_->createExternCall("lymar_aot_print_integer", {args[ai], context_->getConstantInt(context_->getIntegerType(64), 0)}, context_->getVoidType());
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
                if (func) store_reg(inst.dst, builder_->createCall(func, args), inst.result_type);
                break;
            }
            case LIR::LIR_Op::Load: store_reg(inst.dst, builder_->createLoadl(load_reg(inst.a, inst.type_a)), inst.result_type); break;
            case LIR::LIR_Op::Store: builder_->createStore(load_reg(inst.b, inst.type_b), load_reg(inst.a, inst.type_a)); break;
            case LIR::LIR_Op::Cast: {
                auto* value = load_reg(inst.a, inst.type_a);
                auto actual = reg_types.count(inst.a) ? reg_types[inst.a] : inst.type_a;
                // Erased-word sources (containers, frames, `any`) need object
                // kind so boxed floats unbox and nil reads as false/0; scalar
                // registers keep kind 0.
                auto* value_kind = word_kind(inst.a);
                if (inst.result_type == LIR::Type::Ptr) {
                    auto destination = lir_func.get_register_language_type(inst.dst);
                    if (destination && destination->tag == TypeTag::String) {
                        auto src_lang = lir_func.get_register_language_type(inst.a);
                        if (src_lang && src_lang->tag == TypeTag::Bool) {
                            // Bool slots record kind 0 on the dynamic sidecar;
                            // a dedicated entry point avoids the kind channel.
                            store_reg(inst.dst, builder_->createExternCall("lymar_aot_bool_to_string",
                                {erased_word(value)}, context_->getIntegerType(64)), LIR::Type::Ptr);
                        } else {
                            store_reg(inst.dst, builder_->createExternCall("lymar_aot_scalar_to_string",
                                {erased_word(value), value_kind}, context_->getIntegerType(64)), LIR::Type::Ptr);
                        }
                    }
                    else store_reg(inst.dst, erased_word(value), LIR::Type::Ptr);
                } else if (inst.result_type == LIR::Type::Bool) {
                    store_reg(inst.dst, builder_->createExternCall("lymar_aot_to_boolean",
                        {erased_word(value), value_kind}, context_->getIntegerType(64)), LIR::Type::Bool);
                } else if (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32) {
                    if (value->getType()->isFloatingPoint()) store_float_reg(inst.dst, value);
                    else store_float_reg(inst.dst, builder_->createExternCall("lymar_aot_to_float",
                        {value, value_kind}, context_->getDoubleType()));
                } else if (inst.result_type == LIR::Type::I64) {
                    if (value->getType()->isFloatingPoint())
                        store_reg(inst.dst, builder_->createExternCall("lymar_aot_float_to_integer",
                            {value}, context_->getIntegerType(64)), LIR::Type::I64);
                    else store_reg(inst.dst, builder_->createExternCall("lymar_aot_to_integer",
                        {value, value_kind}, context_->getIntegerType(64)), LIR::Type::I64);
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
                        {erased_word(load_reg(inst.a, inst.type_a)), word_kind(inst.a)},
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
                        {erased_word(value_arg), word_kind(inst.b)},
                        context_->getIntegerType(64));
                }
                LIR::Type res_t = (inst.result_type != LIR::Type::Void) ? inst.result_type : LIR::Type::Ptr;
                store_reg(inst.dst, builder_->createCall(fn, {fmt_arg, value_arg}, lir_type_to_fyra_type(res_t)), res_t);
                break;
            }
            case LIR::LIR_Op::Param:
                builder_->createExternCall("lymar_aot_param_push", {load_reg(inst.dst, inst.result_type),
                    context_->getConstantInt(context_->getIntegerType(64), 0)}, nullptr);
                break;
            case LIR::LIR_Op::ConstructError: {
                ir::Value* payload = (inst.a != UINT32_MAX) ? load_reg(inst.a, inst.type_a) : context_->getConstantInt(context_->getIntegerType(64), VAL_NIL);
                payload = builder_->createExternCall("lymar_aot_param_pop", {payload,
                    context_->getConstantInt(context_->getIntegerType(64), 0)}, context_->getIntegerType(64));
                ir::Value* err_box = builder_->createExternCall("memory.alloc", {context_->getConstantInt(context_->getIntegerType(64), 32)}, context_->getIntegerType(64));
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0x4C594D41524F4B21LL), err_box);
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 1), builder_->createAdd(err_box, context_->getConstantInt(context_->getIntegerType(64), 8)));
                ir::Value* payload_addr = builder_->createAdd(err_box, context_->getConstantInt(context_->getIntegerType(64), 16));
                builder_->createStore(payload, payload_addr);
                builder_->createStore(word_kind(inst.a), builder_->createAdd(err_box, context_->getConstantInt(context_->getIntegerType(64), 24)));
                store_reg(inst.dst, err_box, inst.result_type);
                break;
            }
            case LIR::LIR_Op::ConstructOk: {
                ir::Value* payload = load_reg(inst.a, inst.type_a);
                ir::Value* ok_box = builder_->createExternCall("memory.alloc", {context_->getConstantInt(context_->getIntegerType(64), 32)}, context_->getIntegerType(64));
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0x4C594D41524F4B21LL), ok_box);
                builder_->createStore(context_->getConstantInt(context_->getIntegerType(64), 0), builder_->createAdd(ok_box, context_->getConstantInt(context_->getIntegerType(64), 8)));
                ir::Value* payload_addr = builder_->createAdd(ok_box, context_->getConstantInt(context_->getIntegerType(64), 16));
                builder_->createStore(payload, payload_addr);
                builder_->createStore(word_kind(inst.a), builder_->createAdd(ok_box, context_->getConstantInt(context_->getIntegerType(64), 24)));
                store_reg(inst.dst, ok_box, inst.result_type);
                break;
            }
            case LIR::LIR_Op::IsError: {
                ir::Value* container = load_reg(inst.a, inst.type_a);
                store_reg(inst.dst, builder_->createExternCall("lymar_aot_union_is_error", {container, word_kind(inst.a)}, context_->getIntegerType(64)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::Unwrap: {
                ir::Value* container = load_reg(inst.a, inst.type_a);
                store_reg(inst.dst, builder_->createExternCall("lymar_aot_union_unwrap", {container, word_kind(inst.a)}, context_->getIntegerType(64)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::UnwrapOr: {
                ir::Value* container = load_reg(inst.a, inst.type_a);
                ir::Value* is_err = builder_->createExternCall("lymar_aot_union_is_error", {container, word_kind(inst.a)}, context_->getIntegerType(64));

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
                builder_->createStore(builder_->createExternCall("lymar_aot_union_unwrap", {container, word_kind(inst.a)}, context_->getIntegerType(64)), res_slot);
                builder_->createJmp(b_done);

                builder_->setInsertPoint(b_done);
                store_reg(inst.dst, builder_->createLoadl(res_slot), inst.result_type);
                break;
            }
            case LIR::LIR_Op::ListCreate: {
                used_builtins_.insert("lm_list_new");
                ir::Function* fn = current_module_->getFunction("lm_list_new");
                if (!fn) fn = builder_->createFunction("lm_list_new", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {context_->getConstantInt(context_->getIntegerType(64), (long long)inst.imm)}), inst.result_type);
                break;
            }
            case LIR::LIR_Op::ListAppend: {
                used_builtins_.insert("lm_list_append");
                ir::Function* fn = current_module_->getFunction("lm_list_append");
                if (!fn) fn = builder_->createFunction("lm_list_append", context_->getVoidType(), {context_->getIntegerType(64), context_->getIntegerType(64)});
                builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)});
                // Append can reallocate `data`, invalidating any cached data_ptr
                // for the receiver. Drop it so a subsequent ListIndex re-loads
                // the current pointer.
                hoisted_data_ptrs.erase(inst.a);
                break;
            }
            case LIR::LIR_Op::ListIndex: {
                ir::Value* list_val = load_reg(inst.a, inst.type_a);
                ir::Value* idx_val = load_reg(inst.b, inst.type_b);
                std::string lidx_id = std::to_string(label_counter_++);

                // Bound-proven hint (stream_fusion scope): lazily cache the
                // unboxed data pointer for this register so subsequent in-loop
                // accesses reuse it and Fyra's LoopVectorizer sees a single
                // affine load per iteration instead of the CFG-wrapped check.
                // The hint is only set inside a synthesized stream-fusion block,
                // which rejects pipelines whose body would grow/shrink the
                // source; the append/set handlers below still drop the cache on
                // mutation as a defense in depth.
                const bool bound_proven = (inst.imm & 0x1u) != 0u;
                if (hoisted_data_ptrs.count(inst.a) || is_typed_primitive_list(inst.a)) {
                    ir::Value* data_ptr = nullptr;
                    if (hoisted_data_ptrs.count(inst.a)) {
                        data_ptr = hoisted_data_ptrs[inst.a];
                    } else if (bound_proven) {
                        ir::Value* unboxed = builder_->createAnd(list_val, context_->getConstantInt(context_->getIntegerType(64), ~7ULL));
                        ir::Instruction* dptr = builder_->createLoadl(builder_->createAdd(unboxed, context_->getConstantInt(context_->getIntegerType(64), 8)));
                        dptr->setName("hoisted_data_ptr_r" + std::to_string(inst.a) + "_lazy");
                        hoisted_data_ptrs[inst.a] = dptr;
                        data_ptr = dptr;
                    } else {
                        ir::Value* unboxed = builder_->createAnd(list_val, context_->getConstantInt(context_->getIntegerType(64), ~7ULL));
                        data_ptr = builder_->createLoadl(builder_->createAdd(unboxed, context_->getConstantInt(context_->getIntegerType(64), 8)));
                    }
                    ir::Value* offset = builder_->createMul(idx_val, context_->getConstantInt(context_->getIntegerType(64), 8));
                    ir::Value* elem_addr = builder_->createAdd(data_ptr, offset);
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
                        ir::Value* fval = builder_->createExternCall("lymar_aot_to_float", {elem, context_->getConstantInt(context_->getIntegerType(64), 1)}, context_->getDoubleType());
                        store_reg(inst.dst, fval, elem_type);
                    } else {
                        store_reg(inst.dst, elem, elem_type);
                    }
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
                ir::Value* final_elem = elem;
                if (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32) {
                    final_elem = builder_->createExternCall("lymar_aot_to_float", {elem, context_->getConstantInt(context_->getIntegerType(64), 1)}, context_->getDoubleType());
                }
                store_reg(inst.dst, final_elem, inst.result_type);
                builder_->createJmp(b_done);

                // Step 4: Slow path fallback
                builder_->setInsertPoint(b_slow);
                ir::Value* slow_res = builder_->createCall(fn, {list_val, idx_val});
                if (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32) {
                    slow_res = builder_->createExternCall("lymar_aot_to_float", {slow_res, context_->getConstantInt(context_->getIntegerType(64), 1)}, context_->getDoubleType());
                }
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
                // Set may fall through to lm_list_set which reallocates; drop any
                // cached data_ptr for this register so a subsequent ListIndex
                // re-loads from the (possibly new) header.
                hoisted_data_ptrs.erase(inst.dst);

                if (hoisted_data_ptrs.count(inst.dst) || is_typed_primitive_list(inst.dst)) {
                    ir::Value* data_ptr = nullptr;
                    if (hoisted_data_ptrs.count(inst.dst)) {
                        data_ptr = hoisted_data_ptrs[inst.dst];
                    } else {
                        ir::Value* unboxed = builder_->createAnd(list_val, context_->getConstantInt(context_->getIntegerType(64), ~7ULL));
                        data_ptr = builder_->createLoadl(builder_->createAdd(unboxed, context_->getConstantInt(context_->getIntegerType(64), 8)));
                    }
                    ir::Value* offset = builder_->createMul(idx_val, context_->getConstantInt(context_->getIntegerType(64), 8));
                    ir::Value* elem_addr = builder_->createAdd(data_ptr, offset);
                    if (auto* add_inst = dynamic_cast<ir::Instruction*>(elem_addr)) {
                        add_inst->setName("scalar_elem_" + lset_id);
                    }
                    auto* store_inst = builder_->createStore(erased_word(elem_val), elem_addr);
                    store_inst->setName("scalar_store_" + lset_id);
                    break;
                }

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

                // Scalar elements are stored as raw words needing no ownership
                // edge. Floats/decimals box to heap objects (erased_word /
                // box_float), so they must take the object path or the stored
                // box dies with the enclosing region, leaving a dangling
                // element — the [float]-param corruption.
                auto lir_scalar = [](LIR::Type t) {
                    return t != LIR::Type::Ptr && t != LIR::Type::Void &&
                           t != LIR::Type::F32 && t != LIR::Type::F64;
                };
                // A [float]/[decimal] (or nested) element always stores a boxed
                // heap object via erased_word — decide this from the *element*
                // type first so value-type heuristics cannot reclassify it as a
                // raw scalar word and skip the ownership edge.
                auto elem_boxes_impl = [&](const auto* t, auto&& self) -> bool {
                    if (!t) return false;
                    switch (t->tag) {
                        case ::TypeTag::Float32: case ::TypeTag::Float64:
                        case ::TypeTag::Decimal2: case ::TypeTag::Decimal4:
                        case ::TypeTag::Decimal6:
                            return true;
                        case ::TypeTag::List: {
                            auto* lt = std::get_if<ListType>(&t->extra);
                            return lt && lt->elementType && self(lt->elementType.get(), self);
                        }
                        default: return false;
                    }
                };
                auto elem_boxes = [&](const auto* t) { return elem_boxes_impl(t, elem_boxes_impl); };
                bool elem_may_box = false;
                {
                    auto it_list = lir_func.register_language_types.find(inst.dst);
                    if (it_list != lir_func.register_language_types.end() && it_list->second &&
                        it_list->second->tag == ::TypeTag::List) {
                        auto* lt = std::get_if<ListType>(&it_list->second->extra);
                        if (lt && lt->elementType) elem_may_box = elem_boxes(lt->elementType.get());
                    }
                }
                if (!elem_may_box) {
                    auto it_b = lir_func.register_language_types.find(inst.b);
                    if (it_b != lir_func.register_language_types.end() && it_b->second)
                        elem_may_box = elem_boxes(it_b->second.get());
                }
                if (!elem_may_box) {
                    auto it_rv = lir_func.register_types.find(inst.b);
                    if (it_rv != lir_func.register_types.end() &&
                        (it_rv->second == LIR::Type::F32 || it_rv->second == LIR::Type::F64))
                        elem_may_box = true;
                }
                bool is_scalar_elem = !elem_may_box && lir_scalar(inst.type_b);
                if (!is_scalar_elem) {
                    auto it_b = lir_func.register_types.find(inst.b);
                    if (it_b != lir_func.register_types.end() && lir_scalar(it_b->second)) {
                        is_scalar_elem = true;
                    }
                }
                if (!is_scalar_elem) {
                    auto it_list = lir_func.register_language_types.find(inst.dst);
                    if (it_list != lir_func.register_language_types.end() && it_list->second && it_list->second->tag == ::TypeTag::List) {
                        auto* lt = std::get_if<ListType>(&it_list->second->extra);
                        if (lt && lt->elementType) {
                            auto etag = lt->elementType->tag;
                            if (etag != ::TypeTag::List && etag != ::TypeTag::String &&
                                etag != ::TypeTag::Frame && etag != ::TypeTag::Dict &&
                                etag != ::TypeTag::Tuple && etag != ::TypeTag::Any &&
                                etag != ::TypeTag::Enum && etag != ::TypeTag::Trait &&
                                etag != ::TypeTag::TraitObject &&
                                etag != ::TypeTag::Float32 && etag != ::TypeTag::Float64 &&
                                etag != ::TypeTag::Decimal2 && etag != ::TypeTag::Decimal4 &&
                                etag != ::TypeTag::Decimal6) {
                                is_scalar_elem = true;
                            }
                        }
                    }
                }
                if (!is_scalar_elem && pointer_assigned_regs.count(inst.b) == 0 && !is_pointer_lang_type(inst.b)) {
                    // Boxed scalar language types (float/decimal) produce heap
                    // objects via erased_word — they are not raw scalar words.
                    auto it_lv = lir_func.register_language_types.find(inst.b);
                    bool boxed_scalar = it_lv != lir_func.register_language_types.end() && it_lv->second &&
                        (it_lv->second->tag == ::TypeTag::Float32 || it_lv->second->tag == ::TypeTag::Float64 ||
                         it_lv->second->tag == ::TypeTag::Decimal2 || it_lv->second->tag == ::TypeTag::Decimal4 ||
                         it_lv->second->tag == ::TypeTag::Decimal6);
                    auto it_rv = lir_func.register_types.find(inst.b);
                    boxed_scalar = boxed_scalar ||
                        (it_rv != lir_func.register_types.end() &&
                         (it_rv->second == LIR::Type::F32 || it_rv->second == LIR::Type::F64));
                    if (!boxed_scalar) is_scalar_elem = true;
                }

                if (is_scalar_elem) {
                    if (auto* add_inst = dynamic_cast<ir::Instruction*>(elem_addr)) {
                        add_inst->setName("scalar_elem_" + lset_id);
                    }
                    auto* store_inst = builder_->createStore(erased_word(elem_val), elem_addr);
                    store_inst->setName("scalar_store_" + lset_id);
                } else {
                    builder_->createStore(erased_word(elem_val), elem_addr);
                }
                builder_->createJmp(b_done);

                // Step 4: Slow path
                builder_->setInsertPoint(b_slow);
                builder_->createCall(fn, {list_val, idx_val, elem_val});
                builder_->createJmp(b_done);

                builder_->setInsertPoint(b_done);
                break;
            }
            case LIR::LIR_Op::StringIndex: {
                if (inst.result_type == LIR::Type::Ptr) {
                    FyraBuiltinFunctions::emit_substring_ir(current_module_.get(), builder_.get());
                    ir::Function* fn = current_module_->getFunction("_builtin_substring");
                    ir::Value* idx_val = load_reg(inst.b, inst.type_b);
                    ir::Value* end_val = builder_->createAdd(idx_val, context_->getConstantInt(context_->getIntegerType(64), 1));
                    store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), idx_val, end_val}), LIR::Type::Ptr);
                } else {
                    used_builtins_.insert("_builtin_string_byte_at");
                    ir::Function* fn = current_module_->getFunction("_builtin_string_byte_at");
                    if (!fn) fn = builder_->createFunction("_builtin_string_byte_at", context_->getIntegerType(64), {context_->getPointerType(context_->getIntegerType(8)), context_->getIntegerType(64)});
                    store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}), inst.result_type);
                }
                break;
            }
            case LIR::LIR_Op::ListLen: {
                used_builtins_.insert("lm_list_len");
                ir::Function* fn = current_module_->getFunction("lm_list_len");
                if (!fn) fn = builder_->createFunction("lm_list_len", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::TupleCreate: {
                used_builtins_.insert("lm_tuple_new");
                ir::Function* fn = current_module_->getFunction("lm_tuple_new");
                if (!fn) fn = builder_->createFunction("lm_tuple_new", context_->getIntegerType(64), {context_->getIntegerType(64)});
                store_reg(inst.dst, builder_->createCall(fn, {context_->getConstantInt(context_->getIntegerType(64), (long long)inst.imm)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
                break;
            }
            case LIR::LIR_Op::TupleSet: {
                used_builtins_.insert("lm_tuple_set");
                ir::Function* fn = current_module_->getFunction("lm_tuple_set");
                if (!fn) fn = builder_->createFunction("lm_tuple_set", context_->getVoidType(), {context_->getIntegerType(64), context_->getIntegerType(64), context_->getIntegerType(64)});
                // Float elements box to heap objects, matching DictSet — raw
                // double bits in the tuple word are misread on TupleGet.
                LIR::Type vt = inst.type_b;
                if (reg_types.count(inst.b)) vt = reg_types[inst.b];
                ir::Value* val = (vt == LIR::Type::F64 || vt == LIR::Type::F32)
                    ? builder_->createExternCall("lymar_aot_box_float", {load_float_reg(inst.b, vt)}, context_->getIntegerType(64))
                    : load_reg(inst.b, inst.type_b);
                builder_->createCall(fn, {load_reg(inst.dst, inst.result_type), load_reg(inst.a, inst.type_a), val});
                break;
            }
            case LIR::LIR_Op::TupleGet: {
                used_builtins_.insert("lm_tuple_get");
                ir::Function* fn = current_module_->getFunction("lm_tuple_get");
                if (!fn) fn = builder_->createFunction("lm_tuple_get", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                // lm_tuple_get returns a raw i64 word (boxed float / scalar /
                // nil). Store it unconverted: coercing to double here loses
                // nil and bit-reinterprets box pointers. Float consumers
                // unbox via word_kind=1 in load_float_reg/store_reg.
                ir::Value* raw = builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}, context_->getIntegerType(64));
                store_reg(inst.dst, raw, (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32) ? LIR::Type::Ptr : inst.result_type);
                break;
            }
            case LIR::LIR_Op::TupleLen: {
                // Canonical tuple header: kind, elements, size, capacity.
                ir::Value* len = builder_->createExternCall("lymar_aot_tuple_length",
                    {load_reg(inst.a, inst.type_a), context_->getConstantInt(context_->getIntegerType(64), 0)}, context_->getIntegerType(64));
                store_reg(inst.dst, len, inst.result_type);
                break;
            }
            case LIR::LIR_Op::ProbeKind: {
                ir::Value* kind = builder_->createExternCall("lymar_aot_probe_kind",
                    {load_reg(inst.a, inst.type_a), context_->getConstantInt(context_->getIntegerType(64), 0)}, context_->getIntegerType(64));
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
                // Float values must be heap-boxed before entering the dict:
                // storing raw double bits makes DictGet return an int-word that
                // `as float`/print misinterpret (denormal garbage).
                LIR::Type vt = inst.type_b;
                if (reg_types.count(inst.b)) vt = reg_types[inst.b];
                ir::Value* val = (vt == LIR::Type::F64 || vt == LIR::Type::F32)
                    ? builder_->createExternCall("lymar_aot_box_float", {load_float_reg(inst.b, vt)}, context_->getIntegerType(64))
                    : load_reg(inst.b, inst.type_b);
                builder_->createCall(fn, {load_reg(inst.dst, inst.result_type), load_reg(inst.a, inst.type_a), val});
                break;
            }
            case LIR::LIR_Op::DictGet: {
                used_builtins_.insert("lm_dict_get");
                ir::Function* fn = current_module_->getFunction("lm_dict_get");
                if (!fn) fn = builder_->createFunction("lm_dict_get", context_->getIntegerType(64), {context_->getIntegerType(64), context_->getIntegerType(64)});
                // A typed dictionary lookup can still return nil for a missing
                // key. Preserve the returned slot kind instead of asserting
                // the dictionary's nominal Boolean element type.
                // lm_dict_get returns a raw i64 word (pointer/scalar/nil), never
                // a double — declaring the call's return type from result_type
                // made F64 gets bit-reinterpret the word as a double (denormal
                // garbage). Store the word unconverted so a missing key keeps
                // the nil word (== lymar_aot_nil()); boxed floats unbox later
                // via word_kind=1 in load_float_reg/store_reg/Cast.
                ir::Value* raw = builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}, context_->getIntegerType(64));
                store_reg(inst.dst, raw, (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32) ? LIR::Type::Ptr : inst.result_type, true);
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
                store_reg(inst.dst, builder_->createCall(fn, {load_reg(inst.a, inst.type_a), load_reg(inst.b, inst.type_b)}, lir_type_to_fyra_type(inst.result_type)), inst.result_type);
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
                uint32_t field_idx = (inst.b != UINT32_MAX) ? inst.b : static_cast<uint32_t>(inst.imm);
                ir::Value* frame_ptr = load_reg(inst.a, LIR::Type::Ptr);
                ir::Value* addr = builder_->createExternCall("lymar_aot_frame_field_address",
                    {frame_ptr, context_->getConstantInt(context_->getIntegerType(64), field_idx)}, context_->getIntegerType(64));
                // Field words are erased (floats are boxed by FrameSetField's
                // erased_word, nil fields hold the nil word). Store the word
                // unconverted so nil survives; float consumers unbox via
                // word_kind=1 in load_float_reg/store_reg/Cast.
                ir::Value* word = builder_->createLoadl(addr);
                store_reg(inst.dst, word, (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32) ? LIR::Type::Ptr : inst.result_type, true);
                break;
            }
            case LIR::LIR_Op::FrameSetFieldAtomic:
            case LIR::LIR_Op::FrameFieldAtomicAdd:
            case LIR::LIR_Op::FrameFieldAtomicSub: {
                std::vector<ir::Value*> arguments{load_reg(inst.dst, LIR::Type::Ptr),
                    context_->getConstantInt(context_->getIntegerType(64), inst.a), erased_word(load_reg(inst.b, inst.type_b)),
                    context_->getConstantInt(context_->getIntegerType(64), 0)};
                if (inst.op != LIR::LIR_Op::FrameSetFieldAtomic)
                    arguments.push_back(context_->getConstantInt(context_->getIntegerType(64), inst.op == LIR::LIR_Op::FrameFieldAtomicSub));
                builder_->createExternCall(inst.op == LIR::LIR_Op::FrameSetFieldAtomic ? "lymar_aot_atomic_store" : "lymar_aot_atomic_update", arguments, context_->getVoidType());
                break;
            }
            case LIR::LIR_Op::FrameSetField: {
                ir::Value* frame_ptr = load_reg(inst.dst, LIR::Type::Ptr);
                uint32_t field_idx = inst.a;
                ir::Value* addr = builder_->createExternCall("lymar_aot_frame_field_address",
                    {frame_ptr, context_->getConstantInt(context_->getIntegerType(64), field_idx)}, context_->getIntegerType(64));
                builder_->createStore(erased_word(load_reg(inst.b, inst.type_b)), addr);
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
                        builder_->createStore(erased_word(call_res), res_slot);
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
                        {joined, context_->getConstantInt(context_->getIntegerType(64), 1)}, context_->getDoubleType()));
                } else {
                    store_reg(inst.dst, joined, res_t, true);
                }
                break;
            }
            case LIR::LIR_Op::Return:
            case LIR::LIR_Op::Ret:
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
                            {ret_val, word_kind(inst.a)}, context_->getDoubleType());
                    builder_->createRet(ret_val);
                } else {
                    builder_->createRet(builder_->createExternCall("lymar_aot_nil", {}, context_->getIntegerType(64)));
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
                                    value=builder_->createExternCall("lymar_aot_to_float",{value,builder_->createExternCall("lymar_aot_slot_pointer",{address},word)},context_->getDoubleType());
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
                builder_->createExternCall("lymar_aot_channel_push",{load_reg(scheduler,LIR::Type::Ptr),load_reg(task,LIR::Type::Ptr),context_->getConstantInt(word,1)},nullptr);
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
                auto* value = (inst.b != UINT32_MAX) ? erased_word(load_reg(inst.b,inst.type_b)) : erased_word(load_reg(inst.a,inst.type_a));
                builder_->createExternCall("lymar_aot_channel_push",{channel,value,context_->getConstantInt(context_->getIntegerType(64),0)},nullptr);
                if(inst.dst != UINT32_MAX && inst.dst != inst.a) store_reg(inst.dst,context_->getConstantInt(context_->getIntegerType(64),1),inst.result_type);
                break;
            }
            case LIR::LIR_Op::ChannelRecv:
            case LIR::LIR_Op::ChannelPop:
            case LIR::LIR_Op::ChannelPoll: {
                auto* channel = (inst.a != UINT32_MAX && inst.a != 0) ? load_reg(inst.a,LIR::Type::Ptr) : load_reg(inst.dst,LIR::Type::Ptr);
                store_reg(inst.dst,builder_->createExternCall("lymar_aot_channel_pop",{channel},context_->getIntegerType(64)),inst.result_type,true);
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
                auto* value = builder_->createExternCall("lymar_aot_memory_load",
                    {load_reg(inst.a, inst.type_a), context_->getConstantInt(context_->getIntegerType(64), inst.imm),
                     context_->getConstantInt(context_->getIntegerType(64), 0)},
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
                builder_->createExternCall("lymar_aot_memory_store",
                    {load_reg(inst.a, inst.type_a), erased_word(load_reg(inst.b, inst.type_b)),
                     context_->getConstantInt(context_->getIntegerType(64), inst.imm),
                     context_->getConstantInt(context_->getIntegerType(64), 0),
                     context_->getConstantInt(context_->getIntegerType(64), 0)}, nullptr);
                break;
            }
            case LIR::LIR_Op::MemoryAlloc:
                store_reg(inst.dst, builder_->createExternCall("lymar_aot_raw_alloc",
                    {erased_word(load_reg(inst.a, inst.type_a)), context_->getConstantInt(context_->getIntegerType(64), 0)},
                    context_->getIntegerType(64)), LIR::Type::Ptr);
                break;
            case LIR::LIR_Op::MemoryFree:
                builder_->createExternCall("lymar_aot_raw_free",
                    {erased_word(load_reg(inst.a, inst.type_a)), context_->getConstantInt(context_->getIntegerType(64), 0)}, nullptr);
                break;
            case LIR::LIR_Op::MemoryResize:
                store_reg(inst.dst, builder_->createExternCall("lymar_aot_raw_resize",
                    {erased_word(load_reg(inst.a, inst.type_a)), erased_word(load_reg(inst.b, inst.type_b)),
                     context_->getConstantInt(context_->getIntegerType(64), 0), context_->getConstantInt(context_->getIntegerType(64), 0)},
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
                    {erased_word(load_reg(inst.a, inst.type_a)), erased_word(load_reg(inst.b, inst.type_b)), size,
                     context_->getConstantInt(i64, 0), context_->getConstantInt(i64, 0), context_->getConstantInt(i64, 0)},
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
                    if(inst.call_args.size()!=4) throw std::runtime_error("Malformed canonical foreign_call arguments");
                    result=builder_->createExternCall("lymar_aot_foreign_call_list",{load_reg(inst.call_args[0],LIR::Type::Ptr),load_reg(inst.call_args[1],LIR::Type::Ptr),load_reg(inst.call_args[2],LIR::Type::I64),load_reg(inst.call_args[3],LIR::Type::Ptr),zero},context_->getIntegerType(64));
                } else {
                    if(inst.call_args.empty()) throw std::runtime_error("Foreign call missing target");
                    size_t count=inst.call_args.size()-1;
                    auto* size=context_->getConstantInt(context_->getIntegerType(64),std::max<size_t>(8,count*8));
                    auto* values=entry_alloc(context_->getPointerType(context_->getIntegerType(64)), size);auto* kinds=entry_alloc(context_->getPointerType(context_->getIntegerType(64)), size);auto* types=entry_alloc(context_->getPointerType(context_->getIntegerType(64)), size);
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
                        auto* kind=builder_->createExternCall("lymar_aot_ffi_kind",{value,zero},context_->getIntegerType(64));
                        builder_->createStore(kind,builder_->createAdd(kinds,offset));
                        auto* type_id=inferred?builder_->createExternCall("lymar_aot_ffi_infer_type",{value,zero},context_->getIntegerType(64)):static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64),ffi_type(type)));
                        builder_->createStore(type_id,builder_->createAdd(types,offset));
                    }
                    result=builder_->createExternCall("lymar_aot_foreign_call",{load_reg(inst.call_args[0],LIR::Type::Ptr),values,kinds,types,context_->getConstantInt(context_->getIntegerType(64),count),context_->getConstantInt(context_->getIntegerType(64),ffi_type(inst.result_type)),zero},context_->getIntegerType(64));
                }
                if(inst.dst!=UINT32_MAX) store_reg(inst.dst,result,inst.result_type,true);
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
                std::vector<ir::Value*> args;
                for (auto r : inst.call_args) args.push_back(load_reg(r, LIR::Type::I64));
                ir::Value* res = builder_->createExternCall(inst.func_name, args, lir_type_to_fyra_type(inst.result_type));
                if (inst.dst != UINT32_MAX) store_reg(inst.dst, res, inst.result_type);
                break;
            }
            default:
                throw std::runtime_error("Fyra lowering does not implement LIR opcode " +
                    LIR::lir_op_to_string(inst.op) + " in " + lir_func.name);
        }
    }
    if (!terminated && builder_->getInsertPoint())
        builder_->createRet(main_fn->getName() == "main"
            ? static_cast<ir::Value*>(context_->getConstantInt(context_->getIntegerType(64), 0))
            : builder_->createExternCall("lymar_aot_nil", {}, context_->getIntegerType(64)));
}

} // namespace LM::Backend::Fyra

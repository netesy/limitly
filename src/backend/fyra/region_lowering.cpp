#include "region_lowering.hh"
#include "memory/aot_value_kind.hh"
#include "ir/Module.h"
#include "ir/Instruction.h"
#include "ir/Use.h"
#include "ir/Constant.h"
#include "ir/PhiNode.h"
#include "transforms/CFGBuilder.h"
#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace LM::Backend::Fyra {
void lower_region_ownership(ir::Module& module, const std::unordered_map<std::string, uint64_t>& candidates) {
    auto region_free = candidates;
    // Indirect callers use the dynamic value-kind side channel. Keep their
    // callable boundary even when the callee itself allocates nothing.
    for (auto& function : module.getFunctions()) {
        for (auto& block : function->getBasicBlocks()) {
            for (auto& instruction : block->getInstructions()) {
                size_t index = 0;
                for (auto& operand : instruction->getOperands()) {
                    auto* target = dynamic_cast<ir::Function*>(operand->get());
                    if (target && (instruction->getOpcode() != ir::Instruction::Call || index != 0))
                        region_free.erase(target->getName());
                    ++index;
                }
            }
        }
    }
    auto ctx = module.getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto void_type = ctx->getVoidType();
    auto zero = ctx->getConstantInt(i64, 0);
    auto one = ctx->getConstantInt(i64, static_cast<uint64_t>(Memory::AOTValueKind::Object));
    auto boolean = ctx->getConstantInt(i64, static_cast<uint64_t>(Memory::AOTValueKind::Boolean));
    std::unordered_map<std::string, ir::Function*> helpers;
    auto declare = [&](const std::string& name, size_t argc, ir::Type* result, ir::Type* argument_type = nullptr) {
        auto* fn = module.getFunction(name);
        if (!fn) {
            auto created = std::make_unique<ir::Function>(result, name, &module);
            fn = created.get();
            for (size_t i = 0; i < argc; ++i)
                fn->addParameter(std::make_unique<ir::Parameter>(argument_type ? argument_type : i64, "a" + std::to_string(i)));
            module.addFunction(std::move(created));
        }
        helpers[name] = fn;
    };
    declare("lymar_aot_frame_field_address", 2, i64);
    declare("lymar_aot_atomic_load", 2, i64);
    declare("lymar_aot_atomic_store", 4, void_type);
    declare("lymar_aot_atomic_update", 5, void_type);
    declare("lymar_aot_builtin_arity_error", 0, void_type);
    declare("lymar_aot_ref_create", 2, i64);
    declare("lymar_aot_ref_create_checked", 3, i64);
    declare("lymar_aot_nil", 0, i64);
    declare("lymar_aot_boolean", 1, i64);
    declare("lymar_aot_print_float", 1, void_type, ctx->getDoubleType());
    declare("lymar_aot_scalar_to_string", 2, i64);
    declare("lymar_aot_box_float", 1, i64, ctx->getDoubleType());
    declare("lymar_aot_to_float", 2, ctx->getDoubleType());
    declare("lymar_aot_to_integer", 2, i64);
    declare("lymar_aot_float_to_integer", 1, i64, ctx->getDoubleType());
    declare("lymar_aot_to_boolean", 2, i64);
    declare("lymar_aot_value_equal", 4, i64);
    declare("lymar_aot_is_print_object", 2, i64);
    declare("lymar_aot_is_nil", 2, i64);
    declare("lymar_aot_is_object", 2, i64);
    declare("lymar_aot_string_receiver", 2, i64);
    declare("lymar_aot_callable_receiver", 2, i64);
    declare("lymar_aot_string_index", 2, i64);
    declare("lymar_aot_print_integer", 2, void_type);
    declare("lymar_aot_copy_constant", 2, i64);
    declare("lymar_aot_ref_resolve", 2, i64);
    declare("lymar_aot_ref_move", 3, i64);
    declare("lymar_aot_ref_release", 1, void_type);
    declare("lymar_aot_ref_release_nullable", 1, void_type);
    declare("lymar_aot_consume", 1, void_type);
    declare("lymar_aot_call_enter", 0, i64);
    declare("lymar_aot_call_leave", 1, void_type);
    declare("lymar_aot_arg_set", 2, void_type);
    declare("lymar_aot_arg_get", 1, i64);
    declare("lymar_aot_arg_kind", 2, i64);
    declare("lymar_aot_return_pointer", 0, i64);
    declare("lymar_aot_param_push", 2, void_type);
    declare("lymar_aot_param_pop", 2, i64);
    declare("lymar_aot_slot_pointer", 1, i64);
    declare("lymar_aot_edge", 3, void_type);
    declare("lymar_aot_global_edge", 3, void_type);
    declare("lymar_aot_alloc", 1, i64);
    declare("lymar_aot_free", 1, void_type);
    declare("lymar_aot_memory_load", 3, i64);
    declare("lymar_aot_memory_load_kind", 3, i64);
    declare("lymar_aot_memory_store", 5, void_type);
    declare("lymar_aot_raw_alloc", 2, i64);
    declare("lymar_aot_raw_free", 2, void_type);
    declare("lymar_aot_raw_resize", 4, i64);
    declare("lymar_aot_raw_copy_checked", 6, void_type);
    declare("lymar_aot_raw_fill_checked", 6, void_type);
    declare("lymar_aot_raw_compare_checked", 6, i64);
    declare("lymar_aot_channel_length", 2, i64);
    declare("lymar_aot_assert",2,void_type);
    declare("lymar_aot_channel_new",0,i64);
    declare("lymar_aot_channel_push",3,void_type);
    declare("lymar_aot_channel_pop",1,i64);
    declare("lymar_aot_channel_has_data",1,i64);
    declare("lymar_aot_channel_close",1,void_type);
    declare("lymar_aot_scheduler_new",3,i64);
    declare("lymar_aot_scheduler_run",1,void_type);
    declare("lymar_aot_resize", 2, i64);
    declare("lymar_aot_copy", 3, void_type);
    declare("lymar_aot_raw_copy", 3, void_type);
    declare("lymar_aot_raw_fill", 3, void_type);
    declare("lymar_aot_raw_compare", 3, i64);
    declare("lymar_aot_region_current", 0, i64);
    declare("lymar_aot_region_enter", 1, void_type);
    declare("lymar_aot_region_exit", 1, void_type);
    declare("lymar_aot_region_move", 4, void_type);
    declare("lymar_aot_finalize", 1, void_type);
    declare("lymar_aot_set_finalizer", 2, void_type);
    declare("lymar_aot_exit", 1, void_type);
    declare("lymar_aot_resource_create", 2, i64);
    declare("lymar_aot_resource_call", 4, i64);
    declare("lymar_aot_resource_destroy", 1, void_type);
    const std::unordered_map<std::string, std::string> memory_helpers{
        {"memory.alloc", "lymar_aot_alloc"}, {"memory.free", "lymar_aot_free"},
        {"memory.resize", "lymar_aot_resize"}, {"memory.copy", "lymar_aot_copy"},
        {"memory.fill", "lymar_aot_raw_fill"}, {"memory.compare", "lymar_aot_raw_compare"},
        {"process.exit", "lymar_aot_exit"}};

    for (auto& fn : module.getFunctions()) {
        if (fn->getBasicBlocks().empty()) continue;
        if (region_free.count(fn->getName())) {
            // External capability normalization is executable lowering, not
            // memory bookkeeping. Boolean markers are identities here.
            for (auto& owner : fn->getBasicBlocks()) {
                auto* block = owner.get();
                for (auto it = block->getInstructions().begin(); it != block->getInstructions().end();) {
                    auto* inst = it->get();
                    auto* external = dynamic_cast<ir::ExternCallInstruction*>(inst);
                    if (!external) { ++it; continue; }
                    auto name = external->getCapability();
                    if (name.starts_with("lymar.aot."))
                        for (auto& c : name) if (c == '.') c = '_';
                    if (name == "lymar_aot_boolean") {
                        inst->replaceAllUsesWith(inst->getOperands().at(0)->get());
                        it = block->getInstructions().erase(it);
                        continue;
                    }
                    auto helper = helpers.find(name);
                    if (helper == helpers.end()) throw std::runtime_error("Unlowered scalar capability: " + name);
                    std::vector<ir::Value*> args{helper->second};
                    for (auto& operand : inst->getOperands()) args.push_back(operand->get());
                    auto call = std::make_unique<ir::Instruction>(inst->getType(), ir::Instruction::Call, args, block);
                    call->setName(inst->getName());
                    inst->replaceAllUsesWith(call.get());
                    *it = std::move(call);
                    ++it;
                }
            }
            continue;
        }
        std::unordered_map<ir::Value*, ir::Value*> flags;
        auto flag = [&](ir::Value* value) -> ir::Value* {
            if (auto found = flags.find(value); found != flags.end()) return found->second;
            if (value->getType()->isPointerTy() || dynamic_cast<ir::GlobalVariable*>(value) || dynamic_cast<ir::Function*>(value)) return one;
            return zero;
        };
        auto emit = [&](ir::BasicBlock* block, ir::BasicBlock::instr_iterator where,
                        const std::string& name, const std::vector<ir::Value*>& args) {
            std::vector<ir::Value*> operands{helpers.at(name)};
            operands.insert(operands.end(), args.begin(), args.end());
            auto call = std::make_unique<ir::Instruction>(helpers.at(name)->getType(), ir::Instruction::Call, operands, block);
            auto* result = call.get();
            result->setName("region_meta_" + std::to_string(flags.size()) + "_" + std::to_string(block->getInstructions().size()));
            block->getInstructions().insert(where, std::move(call));
            return result;
        };
        auto* entry = fn->getBasicBlocks().front().get();
        auto beginning = entry->getInstructions().begin();
        emit(entry, beginning, "lymar_aot_call_enter", {});
        size_t parameter_index = 0;
        for (auto& param : fn->getParameters()) {
            flags[param.get()] = emit(entry, beginning, "lymar_aot_arg_kind",
                {ctx->getConstantInt(i64, parameter_index), param->getType()->isPointerTy() ? static_cast<ir::Value*>(one) : zero});
            ++parameter_index;
        }
        for (auto& block_owner : fn->getBasicBlocks()) {
            auto* block = block_owner.get();
            for (auto it = block->getInstructions().begin(); it != block->getInstructions().end(); ++it) {

                auto* inst = it->get();
                auto after = std::next(it);
                auto& operands = inst->getOperands();
                if (auto* external = dynamic_cast<ir::ExternCallInstruction*>(inst)) {
                    auto target = memory_helpers.find(external->getCapability());
                    auto name = target != memory_helpers.end() ? target->second : external->getCapability();
                    // Fyra capability constructors normalize underscores to dots.
                    // Private runtime symbols must be restored before direct calls.
                    if (name.starts_with("lymar.aot."))
                        for (auto& c : name) if (c == '.') c = '_';
                    if (target != memory_helpers.end() || name.starts_with("lymar_aot_")) {
                        std::vector<ir::Value*> args{helpers.at(name)};
                        for (auto& operand : operands) args.push_back(operand->get());
                        auto call = std::make_unique<ir::Instruction>(inst->getType(), ir::Instruction::Call, args, block);
                        call->setName(inst->getName());
                        inst->replaceAllUsesWith(call.get());
                        inst = call.get();
                        *it = std::move(call);
                        if (name == "lymar_aot_channel_new" || name == "lymar_aot_scheduler_new" || name == "lymar_aot_alloc" || name == "lymar_aot_resize" || name == "lymar_aot_raw_alloc" || name == "lymar_aot_raw_resize" || name == "lymar_aot_ref_resolve" || name == "lymar_aot_nil" || name == "lymar_aot_copy_constant" || name == "lymar_aot_box_float" || name == "lymar_aot_scalar_to_string") flags[inst] = one;
                        if (name == "lymar_aot_boolean") flags[inst] = boolean;
                        if (name == "lymar_aot_callable_receiver") flags[inst] = one;
                    }
                }
                auto& current_operands = inst->getOperands();
                if (inst->getOpcode() == ir::Instruction::Call && !current_operands.empty()) {
                    auto* callee = dynamic_cast<ir::Function*>(current_operands[0]->get());
                    if (callee && current_operands.size() > 1 &&
                        (callee->getName() == "_builtin_string_byte_at" ||
                         callee->getName() == "_builtin_substring" || callee->getName() == "substring")) {
                        auto* receiver = current_operands[1]->get();
                        auto* checked = emit(block, it, "lymar_aot_string_receiver", {receiver, flag(receiver)});
                        flags[checked] = one;
                        current_operands[1]->set(checked);
                        for (size_t index = 2; index < current_operands.size(); ++index) {
                            auto* argument = current_operands[index]->get();
                            // Native floats are boxed before integer conversion;
                            // pointer/nil/boolean kinds must not become raw indices.
                            if (argument->getType()->isFloatingPoint()) {
                                argument = emit(block, it, "lymar_aot_box_float", {argument});
                                flags[argument] = one;
                            }
                            auto* converted = emit(block, it, "lymar_aot_string_index", {argument, flag(argument)});
                            flags[converted] = zero;
                            current_operands[index]->set(converted);
                        }
                    }
                    // Normalize erased arguments at the call boundary, using the
                    // declared IR signature, before publishing their value kinds.
                    if (callee) {
                        size_t index = 1;
                        for (auto& parameter : callee->getParameters()) {
                            if (index >= current_operands.size()) break;
                            auto* argument = current_operands[index]->get();
                            if (argument->getType()->isFloatingPoint() && !parameter->getType()->isFloatingPoint()) {
                                auto* boxed = emit(block, it, "lymar_aot_box_float", {argument});
                                flags[boxed] = one;
                                current_operands[index]->set(boxed);
                            } else if (!argument->getType()->isFloatingPoint() && parameter->getType()->isFloatingPoint()) {
                                auto* number = emit(block, it, "lymar_aot_to_float", {argument, flag(argument)});
                                flags[number] = zero;
                                current_operands[index]->set(number);
                            }
                            ++index;
                        }
                    }
                    if (callee && callee->getName() == "lymar_aot_ref_create") {
                        std::vector<ir::Value*> args{helpers.at("lymar_aot_ref_create_checked"), current_operands[1]->get(),
                            current_operands[2]->get(), flag(current_operands[1]->get())};
                        auto checked = std::make_unique<ir::Instruction>(inst->getType(), ir::Instruction::Call, args, block);
                        checked->setName(inst->getName());
                        inst->replaceAllUsesWith(checked.get());
                        *it = std::move(checked);
                    } else if (callee && (callee->getName() == "lymar_aot_string_index" || callee->getName() == "lymar_aot_callable_receiver" || callee->getName() == "lymar_aot_is_nil" || callee->getName() == "lymar_aot_is_object" || callee->getName() == "lymar_aot_is_print_object" || callee->getName() == "lymar_aot_to_float" || callee->getName() == "lymar_aot_to_integer" || callee->getName() == "lymar_aot_to_boolean" || callee->getName() == "lymar_aot_print_integer" || callee->getName() == "lymar_aot_scalar_to_string")) {
                        current_operands[2]->set(flag(current_operands[1]->get()));
                    } else if (callee && (callee->getName() == "lymar_aot_raw_alloc" || callee->getName() == "lymar_aot_raw_free")) {
                        current_operands[2]->set(flag(current_operands[1]->get()));
                    } else if (callee && callee->getName() == "lymar_aot_raw_resize") {
                        current_operands[3]->set(flag(current_operands[1]->get()));
                        current_operands[4]->set(flag(current_operands[2]->get()));
                    } else if (callee && (callee->getName() == "lymar_aot_raw_copy_checked" || callee->getName() == "lymar_aot_raw_fill_checked" || callee->getName() == "lymar_aot_raw_compare_checked")) {
                        for (size_t argument = 1; argument <= 3; ++argument)
                            current_operands[argument + 3]->set(flag(current_operands[argument]->get()));
                    } else if (callee && callee->getName() == "lymar_aot_channel_push") {
                        current_operands[3]->set(flag(current_operands[2]->get()));
                    } else if (callee && callee->getName() == "lymar_aot_channel_pop") {
                        flags[inst] = emit(block, after, "lymar_aot_return_pointer", {});
                    } else if (callee && (callee->getName() == "lymar_aot_atomic_store" || callee->getName() == "lymar_aot_atomic_update")) {
                        current_operands[4]->set(flag(current_operands[3]->get()));
                    } else if (callee && callee->getName() == "lymar_aot_atomic_load") {
                        flags[inst] = emit(block, after, "lymar_aot_return_pointer", {});
                    } else if (callee && callee->getName() == "lymar_aot_memory_store") {
                        current_operands[4]->set(flag(current_operands[2]->get()));
                        current_operands[5]->set(flag(current_operands[1]->get()));
                    } else if (callee && callee->getName() == "lymar_aot_memory_load") {
                        current_operands[3]->set(flag(current_operands[1]->get()));
                        flags[inst] = emit(block, after, "lymar_aot_memory_load_kind",
                            {current_operands[1]->get(), current_operands[2]->get(), current_operands[3]->get()});
                    } else if (callee && callee->getName() == "lymar_aot_value_equal") {
                        current_operands[3]->set(flag(current_operands[1]->get()));
                        current_operands[4]->set(flag(current_operands[2]->get()));
                    } else if (callee && callee->getName() == "lymar_aot_region_move") {
                        current_operands[4]->set(flag(current_operands[1]->get()));
                    } else if (callee && (callee->getName() == "lymar_aot_param_push" || callee->getName() == "lymar_aot_param_pop")) {
                        current_operands[2]->set(flag(current_operands[1]->get()));
                        if (callee->getName() == "lymar_aot_param_pop")
                            flags[inst] = emit(block, after, "lymar_aot_return_pointer", {});
                    } else if (callee && callee->getName() == "lymar_aot_resource_call") {
                        flags[inst] = emit(block, after, "lymar_aot_return_pointer", {});
                    } else if (!callee || (!callee->getName().starts_with("lymar_aot_") && !callee->getBasicBlocks().empty())) {
                        if (callee && region_free.count(callee->getName())) {
                            // Closed boolean leaves need neither argument-kind
                            // staging nor a dynamic return-kind side channel.
                            flags[inst] = ctx->getConstantInt(i64, region_free.at(callee->getName()));
                            continue;
                        }
                        for (size_t arg = 1; arg < current_operands.size(); ++arg)
                            emit(block, it, "lymar_aot_arg_set", {ctx->getConstantInt(i64, arg - 1), flag(current_operands[arg]->get())});
                        if (!inst->getType()->isVoidTy()) flags[inst] = emit(block, after, "lymar_aot_return_pointer", {});
                    }
                } else if ((inst->getOpcode() == ir::Instruction::Load || inst->getOpcode() == ir::Instruction::Loadl) && !current_operands.empty()) {
                    flags[inst] = emit(block, after, "lymar_aot_slot_pointer", {current_operands[0]->get()});
                } else if (inst->getOpcode() == ir::Instruction::Store || inst->getOpcode() == ir::Instruction::Stored) {
                    auto* value = current_operands[0]->get();
                    auto* address = current_operands[1]->get();
                    emit(block, after, dynamic_cast<ir::GlobalVariable*>(address) ? "lymar_aot_global_edge" : "lymar_aot_edge",
                         {address, value->getType()->isFloatingPoint() ? static_cast<ir::Value*>(zero) : value,
                          value->getType()->isFloatingPoint() ? static_cast<ir::Value*>(zero) : flag(value)});
                } else if (inst->getOpcode() == ir::Instruction::Ret) {
                    if (!current_operands.empty()) {
                        auto* value = current_operands[0]->get();
                        if (value->getType()->isFloatingPoint() && !fn->getType()->isFloatingPoint()) {
                            auto* boxed = emit(block, it, "lymar_aot_box_float", {value});
                            flags[boxed] = one;
                            current_operands[0]->set(boxed);
                        } else if (!value->getType()->isFloatingPoint() && fn->getType()->isFloatingPoint()) {
                            auto* number = emit(block, it, "lymar_aot_to_float", {value, flag(value)});
                            flags[number] = zero;
                            current_operands[0]->set(number);
                        }
                    }
                    emit(block, it, "lymar_aot_call_leave", {current_operands.empty() ? static_cast<ir::Value*>(zero) : flag(current_operands[0]->get())});
                } else if ((inst->getOpcode() == ir::Instruction::Copy || inst->getOpcode() == ir::Instruction::Cast) && !current_operands.empty()) {
                    flags[inst] = flag(current_operands[0]->get());
                } else if (inst->getOpcode() == ir::Instruction::Add && current_operands.size() == 2) {
                    // Address arithmetic preserves pointer identity; numeric values have flag zero.
                    flags[inst] = flag(current_operands[0]->get());
                }
                // Skip helper calls inserted after this original instruction.
                if (after != block->getInstructions().end()) it = std::prev(after);
                else break;
            }
        }
    }
}

// AOT workers propagate failures explicitly: no C++ unwinding across machine
// code generated without portable exception-unwind metadata is required.
void lower_worker_failures(ir::Module& module) {
    auto ctx=module.getContextShared();auto* word=ctx->getIntegerType(64);
    auto declare=[&](const char* name,ir::Type* type) {
        auto* function=module.getFunction(name);
        if(!function) {auto value=std::make_unique<ir::Function>(type,name,&module);function=value.get();module.addFunction(std::move(value));}
        return function;
    };
    auto* failed=declare("lymar_aot_worker_failed",word);
    auto* abort=declare("lymar_aot_call_abort",ctx->getVoidType());
    std::unordered_set<ir::Function*> reachable;
    std::vector<ir::Function*> pending;
    auto root = [&](ir::Function* function) {
        if (function && !function->getBasicBlocks().empty() && reachable.insert(function).second)
            pending.push_back(function);
    };
    for (auto& owner : module.getFunctions()) {
        if (owner->getName().starts_with("__lymar_task_entry_")) root(owner.get());
        for (auto& block : owner->getBasicBlocks()) for (auto& instruction : block->getInstructions()) {
            const auto& operands = instruction->getOperands();
            for (size_t index = 0; index < operands.size(); ++index) {
                // Every address-taken definition is a conservative indirect
                // worker target, including closures and finalizer callbacks.
                // A direct callee alone is reached by the worklist below.
                if (instruction->getOpcode() == ir::Instruction::Call && index == 0) continue;
                root(dynamic_cast<ir::Function*>(operands[index]->get()));
            }
        }
    }
    for(size_t index=0;index<pending.size();++index)
        for(auto& block:pending[index]->getBasicBlocks()) for(auto& instruction:block->getInstructions())
            for(auto& operand:instruction->getOperands())
                if(auto* target=dynamic_cast<ir::Function*>(operand->get());target && !target->getBasicBlocks().empty() && reachable.insert(target).second) pending.push_back(target);
    for(auto& owner:module.getFunctions()) {
        auto& function=*owner;
        if(!reachable.count(&function)) continue;
        bool invocation=false;
        std::vector<ir::Instruction*> checks;
        for(auto& block:function.getBasicBlocks()) for(auto& instruction:block->getInstructions()) {
            auto op=instruction->getOpcode();
            if(op==ir::Instruction::Call) {
                auto* target=dynamic_cast<ir::Function*>(instruction->getOperands()[0]->get());
                const auto name=target?target->getName():"";
                if(name=="lymar_aot_call_enter") invocation=true;
                if(name=="lymar_aot_call_enter" || name=="lymar_aot_call_leave" || name=="lymar_aot_worker_failed" || name=="lymar_aot_call_abort") continue;
                // Value-kind reads and constant markers cannot report a modeled
                // worker failure. Do not split CFG after pure metadata queries.
                if (name=="lymar_aot_slot_pointer" || name=="lymar_aot_return_pointer" || name=="lymar_aot_arg_get" || name=="lymar_aot_arg_kind" || name=="lymar_aot_nil" || name=="lymar_aot_boolean" || name=="lymar_aot_region_current") continue;
                if (name=="lymar_aot_arg_set") continue; // Staging is discharged by the following call boundary.
                if (name=="lymar_aot_edge" && instruction->getOperands().size()>1) {
                    auto* address=dynamic_cast<ir::Instruction*>(instruction->getOperands()[1]->get());
                    if(address && address->getOpcode()==ir::Instruction::Alloc) continue; // Compiler stack slots carry no region edge.
                }


                checks.push_back(instruction.get());
            } else if(op==ir::Instruction::ExternCall || op==ir::Instruction::Jmp || op==ir::Instruction::Jnz || op==ir::Instruction::Jz) checks.push_back(instruction.get());
        }
        if(checks.empty()) continue;
        auto exit=std::make_unique<ir::BasicBlock>(&function,"worker_failure");auto* failure=exit.get();
        if(invocation) failure->addInstruction(std::make_unique<ir::Instruction>(ctx->getVoidType(),ir::Instruction::Call,std::vector<ir::Value*>{abort},failure));
        std::vector<ir::Value*> returned;
        if(!function.getType()->isVoidTy()) returned.push_back(function.getType()->isFloatingPoint()?static_cast<ir::Value*>(ctx->getConstantFP(ctx->getDoubleType(),0.0)):static_cast<ir::Value*>(ctx->getConstantInt(word,0)));
        failure->addInstruction(std::make_unique<ir::Instruction>(ctx->getVoidType(),ir::Instruction::Ret,returned,failure));
        function.addBasicBlock(std::move(exit));
        unsigned sequence=0;
        for(auto* instruction:checks) {
            auto* block=instruction->getParent();auto& list=block->getInstructions();
            auto where=std::find_if(list.begin(),list.end(),[&](auto& item){return item.get()==instruction;});
            const auto op=instruction->getOpcode();
            if(op==ir::Instruction::Call || op==ir::Instruction::ExternCall) ++where;
            auto continuation=std::make_unique<ir::BasicBlock>(&function,"worker_continue_"+std::to_string(sequence++));
            auto* next=continuation.get();
            next->getInstructions().splice(next->getInstructions().end(),list,where,list.end());
            for(auto& moved:next->getInstructions()) moved->setParent(next);
            // The transferred terminator now contributes incoming Phi values
            // from the continuation rather than its original predecessor.
            if (!next->getInstructions().empty()) {
                auto* terminator = next->getInstructions().back().get();
                std::unordered_set<ir::BasicBlock*> successors;
                for (auto& operand : terminator->getOperands())
                    if (auto* successor = dynamic_cast<ir::BasicBlock*>(operand->get())) successors.insert(successor);
                for (auto* successor : successors) for (auto& phi : successor->getInstructions()) {
                    if (!dynamic_cast<ir::PhiNode*>(phi.get())) continue;
                    for (auto& operand : phi->getOperands()) if (operand->get() == block) operand->set(next);
                }
            }
            auto call=std::make_unique<ir::Instruction>(word,ir::Instruction::Call,std::vector<ir::Value*>{failed},block);
            auto* condition=call.get();list.push_back(std::move(call));
            list.push_back(std::make_unique<ir::Instruction>(ctx->getVoidType(),ir::Instruction::Jnz,std::vector<ir::Value*>{condition,failure,next},block));
            function.addBasicBlock(std::move(continuation));
        }
        transforms::CFGBuilder::run(function);
    }
}

}

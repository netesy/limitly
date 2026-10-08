#include "region_lowering.hh"
#include "ir/Module.h"
#include "ir/Instruction.h"
#include "ir/Use.h"
#include "ir/Constant.h"
#include <unordered_map>
#include <vector>

namespace LM::Backend::Fyra {
void lower_region_ownership(ir::Module& module) {
    auto ctx = module.getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto void_type = ctx->getVoidType();
    auto zero = ctx->getConstantInt(i64, 0);
    auto one = ctx->getConstantInt(i64, 1);
    std::unordered_map<std::string, ir::Function*> helpers;
    auto declare = [&](const std::string& name, size_t argc, ir::Type* result) {
        auto* fn = module.getFunction(name);
        if (!fn) {
            auto created = std::make_unique<ir::Function>(result, name, &module);
            fn = created.get();
            for (size_t i = 0; i < argc; ++i)
                fn->addParameter(std::make_unique<ir::Parameter>(i64, "a" + std::to_string(i)));
            module.addFunction(std::move(created));
        }
        helpers[name] = fn;
    };
    declare("lymar_aot_call_enter", 0, i64);
    declare("lymar_aot_call_leave", 1, void_type);
    declare("lymar_aot_arg_set", 2, void_type);
    declare("lymar_aot_arg_get", 1, i64);
    declare("lymar_aot_return_pointer", 0, i64);
    declare("lymar_aot_slot_pointer", 1, i64);
    declare("lymar_aot_edge", 3, void_type);
    declare("lymar_aot_global_edge", 3, void_type);
    declare("lymar_aot_alloc", 1, i64);
    declare("lymar_aot_free", 1, void_type);
    declare("lymar_aot_resize", 2, i64);
    declare("lymar_aot_copy", 3, void_type);
    declare("lymar_aot_region_current", 0, i64);
    declare("lymar_aot_region_enter", 1, void_type);
    declare("lymar_aot_region_exit", 1, void_type);
    declare("lymar_aot_region_move", 4, void_type);
    declare("lymar_aot_finalize", 1, void_type);
    declare("lymar_aot_set_finalizer", 2, void_type);
    declare("lymar_aot_exit", 1, void_type);
    const std::unordered_map<std::string, std::string> memory_helpers{
        {"memory.alloc", "lymar_aot_alloc"}, {"memory.free", "lymar_aot_free"},
        {"memory.resize", "lymar_aot_resize"}, {"memory.copy", "lymar_aot_copy"},
        {"process.exit", "lymar_aot_exit"}};

    for (auto& fn : module.getFunctions()) {
        if (fn->getBasicBlocks().empty()) continue;
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
            flags[param.get()] = param->getType()->isPointerTy() ? static_cast<ir::Value*>(one)
                : emit(entry, beginning, "lymar_aot_arg_get", {ctx->getConstantInt(i64, parameter_index)});
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
                        if (name == "lymar_aot_alloc" || name == "lymar_aot_resize") flags[inst] = one;
                    }
                }
                auto& current_operands = inst->getOperands();
                if (inst->getOpcode() == ir::Instruction::Call && !current_operands.empty()) {
                    auto* callee = dynamic_cast<ir::Function*>(current_operands[0]->get());
                    if (callee && callee->getName() == "lymar_aot_region_move") {
                        current_operands[4]->set(flag(current_operands[1]->get()));
                    } else if (!callee || (!callee->getName().starts_with("lymar_aot_") && !callee->getBasicBlocks().empty())) {
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
}

#include "codegen/CodeGen.h"
#include "codegen/execgen/Assembler.h"
#include "ir/Constant.h"
#include "ir/GlobalValue.h"
#include "ir/Function.h"
#include "ir/Type.h"
#include "ir/Use.h"
#include "ir/PhiNode.h"
#include "ir/BasicBlock.h"
#include "ir/Module.h"
#include "codegen/debug/DWARFGenerator.h"
#include <algorithm>
#include "codegen/InstructionFusion.h"
#include "codegen/target/Wasm32.h"
#include "codegen/target/SystemV_x64.h"
#include "codegen/target/Windows_x64.h"
#include "codegen/target/MacOS_x64.h"
#include "codegen/target/AArch64.h"
#include "codegen/target/RiscV64.h"
#include <cstring>
#include <iostream>
#include <sstream>

namespace codegen {

CodeGen::CodeGen(ir::Module& module, std::unique_ptr<target::TargetInfo> ti, std::ostream* os)
    : module(module), targetInfo(std::move(ti)),
      assembler(std::make_unique<execgen::Assembler>()),
      rodataAssembler(std::make_unique<execgen::Assembler>()), os(os),
      fusionCoordinator(std::make_unique<target::FusionCoordinator>()),
      debugInfoManager(std::make_unique<debug::DebugInfoManager>()),
      validator_(std::make_unique<validation::ASMValidator>()),
      objectGenerator_(std::make_unique<objectgen::ObjectFileGenerator>()) {
    initializeInstructionPatterns();
    auto& intRegs = targetInfo->getRegisters(target::RegisterClass::Integer);
    availableRegisters.insert(availableRegisters.end(), intRegs.begin(), intRegs.end());
    for (const auto& reg : availableRegisters) registerUsage[reg] = false;
    fusionCoordinator->setTargetArchitecture(targetInfo->getName());
}

CodeGen::~CodeGen() = default;

void CodeGen::emit(bool forExecutable) {
    usesHeap = false; usesFPNeg = false;
    for (auto& func : module.getFunctions()) {
        for (auto& bb : func->getBasicBlocks()) {
            for (auto& instr : bb->getInstructions()) {
                if (instr->getOpcode() == ir::Instruction::Alloc) usesHeap = true;
                if (instr->getOpcode() == ir::Instruction::Neg && instr->getType()->isFloatingPoint()) usesFPNeg = true;
            }
        }
    }
    if (targetInfo->getName() == "wasm32" && !os) {
        auto* wasmTarget = static_cast<target::Wasm32*>(targetInfo.get());
        for (auto& func : module.getFunctions()) emitFunction(*func);
        wasmTarget->emitHeader(*this); wasmTarget->emitTypeSection(*this);
        wasmTarget->emitFunctionSection(*this); wasmTarget->emitExportSection(*this);
        wasmTarget->emitCodeSection(*this);
    } else {
        emitTargetSpecificHeader(); emitDataSection(); emitTextSection();
        if (forExecutable) targetInfo->emitStartFunction(*this);
        for (auto& func : module.getFunctions()) emitFunction(*func);
    }
}

void CodeGen::emitFunction(ir::Function& func) {
    currentFunction = &func;
    stackOffsets.clear();
    if (targetInfo->getName() == "wasm32" && !os) {
        auto funcBodyAsm = std::make_unique<execgen::Assembler>();
        auto oldAsm = std::move(assembler); assembler = std::move(funcBodyAsm);
        for (auto& bb : func.getBasicBlocks()) emitBasicBlock(*bb);
        wasmFunctionBodies.push_back(assembler->getCode());
        assembler = std::move(oldAsm);
    } else {
        if (os) *os << "\n" << func.getName() << ":\n";
        targetInfo->emitFunctionPrologue(*this, func);
        for (auto& bb : func.getBasicBlocks()) emitBasicBlock(*bb);
        targetInfo->emitFunctionEpilogue(*this, func);
    }
}

void CodeGen::emitBasicBlock(ir::BasicBlock& bb) {
    if (os) *os << bb.getParent()->getName() << "_" << bb.getName() << ":\n";
    for (auto& instr : bb.getInstructions()) emitInstruction(*instr);
}

void CodeGen::emitInstruction(ir::Instruction& instr) {
    switch (instr.getOpcode()) {
        case ir::Instruction::Ret: targetInfo->emitRet(*this, instr); break;
        case ir::Instruction::Add: targetInfo->emitAdd(*this, instr); break;
        case ir::Instruction::Sub: targetInfo->emitSub(*this, instr); break;
        case ir::Instruction::Mul: targetInfo->emitMul(*this, instr); break;
        case ir::Instruction::Div: case ir::Instruction::Udiv: targetInfo->emitDiv(*this, instr); break;
        case ir::Instruction::Rem: case ir::Instruction::Urem: targetInfo->emitRem(*this, instr); break;
        case ir::Instruction::And: targetInfo->emitAnd(*this, instr); break;
        case ir::Instruction::Or: targetInfo->emitOr(*this, instr); break;
        case ir::Instruction::Xor: targetInfo->emitXor(*this, instr); break;
        case ir::Instruction::Shl: targetInfo->emitShl(*this, instr); break;
        case ir::Instruction::Shr: targetInfo->emitShr(*this, instr); break;
        case ir::Instruction::Sar: targetInfo->emitSar(*this, instr); break;
        case ir::Instruction::Neg: targetInfo->emitNeg(*this, instr); break;
        case ir::Instruction::Not: targetInfo->emitNot(*this, instr); break;
        case ir::Instruction::Copy: targetInfo->emitCopy(*this, instr); break;
        case ir::Instruction::Syscall: targetInfo->emitSyscall(*this, instr); break;
        case ir::Instruction::Call: targetInfo->emitCall(*this, instr); break;
        case ir::Instruction::Jmp: targetInfo->emitJmp(*this, instr); break;
        case ir::Instruction::Br: case ir::Instruction::Jnz: targetInfo->emitBr(*this, instr); break;
        case ir::Instruction::Load: targetInfo->emitLoad(*this, instr); break;
        case ir::Instruction::Store: targetInfo->emitStore(*this, instr); break;
        case ir::Instruction::Alloc: targetInfo->emitAlloc(*this, instr); break;
        case ir::Instruction::Ceq: case ir::Instruction::Cne: case ir::Instruction::Cslt:
        case ir::Instruction::Csle: case ir::Instruction::Csgt: case ir::Instruction::Csge:
        case ir::Instruction::Cult: case ir::Instruction::Cule: case ir::Instruction::Cugt:
        case ir::Instruction::Cuge: targetInfo->emitCmp(*this, instr); break;
        default: break;
    }
}

std::string CodeGen::getValueAsOperand(const ir::Value* value) {
    if (!value) return "null";
    if (auto* instr = dynamic_cast<const ir::Instruction*>(value)) {
        if (instr->hasPhysicalRegister()) {
            auto& regs = targetInfo->getRegisters(target::RegisterClass::Integer);
            return targetInfo->getRegisterName(regs[instr->getPhysicalRegister()], instr->getType());
        }
        if (currentFunction && currentFunction->hasStackSlot(const_cast<ir::Instruction*>(instr)))
            return targetInfo->formatStackOperand(-currentFunction->getStackSlotForVreg(const_cast<ir::Instruction*>(instr)) - 8);
    }
    if (auto* ci = dynamic_cast<const ir::ConstantInt*>(value)) return targetInfo->formatConstant(ci);
    if (auto* bb = dynamic_cast<const ir::BasicBlock*>(value)) return bb->getParent()->getName() + "_" + bb->getName();
    if (auto* gv = dynamic_cast<const ir::GlobalVariable*>(value)) return targetInfo->formatGlobalOperand(gv->getName());
    if (auto* f = dynamic_cast<const ir::Function*>(value)) return f->getName();
    if (stackOffsets.count(const_cast<ir::Value*>(value))) return targetInfo->formatStackOperand(stackOffsets[const_cast<ir::Value*>(value)]);
    if (auto* p = dynamic_cast<const ir::Parameter*>(value)) { if (stackOffsets.count(const_cast<ir::Value*>(value))) return targetInfo->formatStackOperand(stackOffsets.at(const_cast<ir::Value*>(value))); } return "$" + value->getName();
}

int32_t CodeGen::getStackOffset(ir::Value* val) const { return targetInfo->getStackOffset(*this, val); }

CodeGen::CompilationResult CodeGen::compileToObject(const std::string& outputPrefix, bool validateASM, bool generateObject, bool) {
    CompilationTimer timer; CompilationResult result; result.targetName = targetInfo->getName();
    std::stringstream ss; std::ostream* old_os = os; os = &ss; emit(false); os = old_os;
    std::string assembly = ss.str();
    std::string assemblyPath = outputPrefix + targetInfo->getAssemblyFileExtension();
    result.assemblyPath = writeAssemblyToFile(assembly, assemblyPath);
    if (validateASM && validator_) result.validation = validator_->validateAssembly(assembly, targetInfo->getName());
    if (generateObject && !result.hasValidationErrors()) {
        result.objGen = objectGenerator_->generateObject(result.assemblyPath, outputPrefix, targetInfo->getName());
        if (result.objGen.success) result.objectPath = result.objGen.objectPath;
    }
    result.success = !result.hasValidationErrors() && (!generateObject || result.objGen.success);
    result.totalTimeMs = timer.getElapsedMs(); return result;
}

CodeGen::CompilationResult CodeGen::compileToAssembly(const std::string& outputPath, bool validateASM) {
    CompilationTimer timer; CompilationResult result; result.targetName = targetInfo->getName();
    std::stringstream ss; std::ostream* old_os = os; os = &ss; emit(false); os = old_os;
    std::string assembly = ss.str();
    result.assemblyPath = writeAssemblyToFile(assembly, outputPath);
    if (validateASM && validator_) result.validation = validator_->validateAssembly(assembly, targetInfo->getName());
    result.success = !result.hasValidationErrors(); result.totalTimeMs = timer.getElapsedMs(); return result;
}

std::string CodeGen::writeAssemblyToFile(const std::string& assembly, const std::string& path) {
    std::ofstream file(path); if (!file.is_open()) return ""; file << assembly; file.close(); return path;
}

bool CodeGen::CompilationResult::hasObjectGenerationErrors() const { return !objGen.success; }
std::vector<std::string> CodeGen::CompilationResult::getAllErrors() const {
    std::vector<std::string> errors;
    for (const auto& error : validation.errors) errors.push_back("[Validation] " + error.message);
    if (!objGen.success) errors.push_back("[ObjectGen] " + objGen.errorOutput);
    return errors;
}

void CodeGen::setValidationLevel(validation::ValidationLevel level) { if (validator_) validator_->setValidationLevel(level); }
void CodeGen::enableVerboseOutput(bool enable) { verboseOutput_ = enable; if (validator_) validator_->enableDetailedReporting(enable); }

std::unique_ptr<CodeGen> CodeGenFactory::create(ir::Module& module, const std::string& targetName) {
    auto ti = createTargetInfo(targetName); if (!ti) return nullptr;
    return std::make_unique<CodeGen>(module, std::move(ti));
}

std::unique_ptr<target::TargetInfo> CodeGenFactory::createTargetInfo(const std::string& targetName) {
    std::string n = targetName; std::transform(n.begin(), n.end(), n.begin(), ::tolower);
    if (n == "linux" || n == "systemv") return std::make_unique<target::SystemV_x64>();
    if (n == "windows" || n == "win64") return std::make_unique<target::Windows_x64>();
    if (n == "macos" || n == "darwin") return std::make_unique<target::MacOS_x64>();
    if (n == "wasm32") return std::make_unique<target::Wasm32>();
    if (n == "aarch64") return std::make_unique<target::AArch64>();
    if (n == "riscv64") return std::make_unique<target::RiscV64>();
    return nullptr;
}

void CodeGen::initializeInstructionPatterns() {}
void CodeGen::performTargetOptimizations(ir::Function&) {}
std::string CodeGen::allocateRegister(ir::Value*) { return ""; }
void CodeGen::deallocateRegister(const std::string&) {}
void CodeGen::emitTargetSpecificHeader() {
    if (os) {
        if (targetInfo->getName() == "x86_64") *os << ".att_syntax prefix\n";
        else if (targetInfo->getName() == "win64") *os << ".intel_syntax noprefix\n";
    }
}
void CodeGen::emitDataSection() {}
void CodeGen::emitTextSection() { if (os) *os << ".text\n.globl main\n"; }
void CodeGen::emitFunctionAlignment() {}
void CodeGen::performInstructionFusion(ir::Function&) {}
void CodeGen::applyFusionOptimizations(ir::BasicBlock&) {}
void CodeGen::enableDebugInfo(bool) {}
void CodeGen::setCurrentLocation(const std::string&, unsigned) {}
void CodeGen::emitDebugInfo() {}
void CodeGen::selectInstruction(ir::Instruction&) {}
bool CodeGen::matchPattern(ir::Instruction&, const InstructionPattern&) { return false; }
void CodeGen::selectArithmeticInstruction(ir::Instruction&) {}
void CodeGen::selectMemoryInstruction(ir::Instruction&) {}
void CodeGen::selectComparisonInstruction(ir::Instruction&) {}
void CodeGen::selectControlFlowInstruction(ir::Instruction&) {}
void CodeGen::emitBasicBlockContent(ir::BasicBlock& bb) { for (auto& instr : bb.getInstructions()) emitInstruction(*instr); }
bool CodeGen::isImmediateValue(ir::Value*, int64_t&) { return false; }
bool CodeGen::canFoldIntoMemoryOperand(ir::Value*) { return false; }
std::string CodeGen::getOptimizedOperand(ir::Value* v) { return getValueAsOperand(v); }
void CodeGen::emitWasmFunctionSignature(ir::Function&) {}
std::string CodeGen::getWasmValueAsOperand(const ir::Value*) { return ""; }

} // namespace codegen

namespace codegen {

CodeGenPipeline::CodeGenPipeline() {}

CodeGenPipeline::PipelineResult CodeGenPipeline::execute(ir::Module& module, const PipelineConfig& config) {
    PipelineResult result;
    for (const auto& t : config.targetPlatforms) {
        auto tr = executeForTarget(module, t, config);
        result.targetResults[t] = tr.targetResults[t];
    }
    result.success = true;
    return result;
}

CodeGenPipeline::PipelineResult CodeGenPipeline::executeForTarget(ir::Module& module, const std::string& t, const PipelineConfig& config) {
    PipelineResult result;
    auto cg = CodeGenFactory::create(module, t);
    if (!cg) { result.success = false; return result; }
    result.targetResults[t] = cg->compileToObject(config.outputPrefix + "_" + t, config.enableValidation, config.enableObjectGeneration);
    result.success = result.targetResults[t].success;
    return result;
}

} // namespace codegen

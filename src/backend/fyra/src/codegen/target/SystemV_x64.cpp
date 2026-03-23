#include "codegen/target/SystemV_x64.h"
#include "codegen/CodeGen.h"
#include "ir/Instruction.h"
#include "ir/Use.h"
#include "ir/Type.h"
#include "ir/Function.h"
#include "ir/Constant.h"
#include <ostream>
#include <algorithm>

using namespace ir;
using namespace codegen;
using namespace codegen::target;

namespace {
    std::string getSuffix(const ir::Type* type) {
        if (!type || type->isPointerTy()) return "q";
        if (auto* it = dynamic_cast<const ir::IntegerType*>(type)) {
            if (it->getBitwidth() == 8) return "b";
            if (it->getBitwidth() == 16) return "w";
            if (it->getBitwidth() == 32) return "l";
        }
        return "q";
    }
}

namespace codegen {
namespace target {

void SystemV_x64::initRegisters() {
    integerRegs = {"%rax", "%rcx", "%rdx", "%rsi", "%rdi", "%r8", "%r9", "%r10", "%r11", "%rbx", "%r12", "%r13", "%r14", "%r15"};
    floatRegs = {"%xmm0", "%xmm1", "%xmm2", "%xmm3", "%xmm4", "%xmm5", "%xmm6", "%xmm7"};
    integerArgRegs = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    floatArgRegs = {"%xmm0", "%xmm1", "%xmm2", "%xmm3", "%xmm4", "%xmm5", "%xmm6", "%xmm7"};
    intReturnReg = "%rax";
    floatReturnReg = "%xmm0";
    stackPtrReg = "rsp";
    framePtrReg = "rbp";
    callerSaved = { {"%rax",true}, {"%rcx",true}, {"%rdx",true}, {"%rsi",true}, {"%rdi",true}, {"%r8",true}, {"%r9",true}, {"%r10",true}, {"%r11",true} };
    calleeSaved = { {"%rbx",true}, {"%r12",true}, {"%r13",true}, {"%r14",true}, {"%r15",true}, {"%rbp",true} };
}

SystemV_x64::SystemV_x64() : X86_64Base() { initRegisters(); }

void SystemV_x64::emitFunctionPrologue(CodeGen& cg, ir::Function& func) {
    currentStackOffset = 0;
    for (auto& param : func.getParameters()) {
        currentStackOffset -= 8;
        cg.getStackOffsets()[param.get()] = currentStackOffset;
    }
    
    int locals_size = func.getStackFrameSize();
    int total_locals = locals_size + (-currentStackOffset);
    emitPrologue(cg, total_locals);

    if (auto* os = cg.getTextStream()) {
        int i = 0;
        for (auto& param : func.getParameters()) {
            if (i < 6) *os << "  movq " << integerArgRegs[i] << ", " << cg.getStackOffset(param.get()) << "(%rbp)\n";
            i++;
        }
    }
}

void SystemV_x64::emitFunctionEpilogue(CodeGen&, ir::Function&) {}

void SystemV_x64::emitPassArgument(CodeGen& cg, size_t argIndex, const std::string& value, const ir::Type* type) {
    if (auto* os = cg.getTextStream()) {
        if (argIndex < 6) {
            *os << "  mov" << getSuffix(type) << " " << value << ", " << integerArgRegs[argIndex] << "\n";
        }
    }
}

void SystemV_x64::emitGetArgument(CodeGen& cg, size_t argIndex, const std::string& dest, const ir::Type* type) {
    if (auto* os = cg.getTextStream()) {
        if (argIndex < 6) {
            *os << "  mov" << getSuffix(type) << " " << integerArgRegs[argIndex] << ", " << dest << "\n";
        }
    }
}

void SystemV_x64::emitRet(CodeGen& cg, ir::Instruction& instr) {
    if (auto* os = cg.getTextStream()) {
        if (!instr.getOperands().empty()) {
            ir::Value* val = instr.getOperands()[0]->get();
            if (auto* ci = dynamic_cast<ir::ConstantInt*>(val)) {
                if (ci->getValue() == 0) {
                    *os << "  xorl %eax, %eax\n";
                } else {
                    *os << "  movl $" << ci->getValue() << ", %eax\n";
                }
            } else {
                std::string src = cg.getValueAsOperand(val);
                std::string reg = getRegisterName("%rax", val->getType());
                if (src != reg) *os << "  mov" << getSuffix(val->getType()) << " " << src << ", " << reg << "\n";
            }
        }
        emitEpilogue(cg);
    }
}

void SystemV_x64::emitAdd(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), l = cg.getValueAsOperand(i.getOperands()[0]->get()), r = cg.getValueAsOperand(i.getOperands()[1]->get()), s = getSuffix(i.getType());
        if (d != l) *os << "  mov" << s << " " << l << ", " << d << "\n";
        *os << "  add" << s << " " << r << ", " << d << "\n";
    }
}
void SystemV_x64::emitSub(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), l = cg.getValueAsOperand(i.getOperands()[0]->get()), r = cg.getValueAsOperand(i.getOperands()[1]->get()), s = getSuffix(i.getType());
        if (d != l) *os << "  mov" << s << " " << l << ", " << d << "\n";
        *os << "  sub" << s << " " << r << ", " << d << "\n";
    }
}
void SystemV_x64::emitMul(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), l = cg.getValueAsOperand(i.getOperands()[0]->get()), r = cg.getValueAsOperand(i.getOperands()[1]->get()), s = getSuffix(i.getType());
        if (d != l) *os << "  mov" << s << " " << l << ", " << d << "\n";
        *os << "  imul" << s << " " << r << ", " << d << "\n";
    }
}
void SystemV_x64::emitDiv(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), l = cg.getValueAsOperand(i.getOperands()[0]->get()), r = cg.getValueAsOperand(i.getOperands()[1]->get()), s = getSuffix(i.getType());
        *os << "  mov" << s << " " << l << ", %rax\n";
        if (s == "l") *os << "  cltd\n"; else if (s == "q") *os << "  cqto\n";
        *os << "  idiv" << s << " " << r << "\n  mov" << s << " %rax, " << d << "\n";
    }
}
void SystemV_x64::emitRem(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), l = cg.getValueAsOperand(i.getOperands()[0]->get()), r = cg.getValueAsOperand(i.getOperands()[1]->get()), s = getSuffix(i.getType());
        *os << "  mov" << s << " " << l << ", %rax\n";
        if (s == "l") *os << "  cltd\n"; else if (s == "q") *os << "  cqto\n";
        *os << "  idiv" << s << " " << r << "\n  mov" << s << (s == "l" ? " %edx, " : " %rdx, ") << d << "\n";
    }
}
void SystemV_x64::emitAnd(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), l = cg.getValueAsOperand(i.getOperands()[0]->get()), r = cg.getValueAsOperand(i.getOperands()[1]->get()), s = getSuffix(i.getType());
        if (d != l) *os << "  mov" << s << " " << l << ", " << d << "\n";
        *os << "  and" << s << " " << r << ", " << d << "\n";
    }
}
void SystemV_x64::emitOr(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), l = cg.getValueAsOperand(i.getOperands()[0]->get()), r = cg.getValueAsOperand(i.getOperands()[1]->get()), s = getSuffix(i.getType());
        if (d != l) *os << "  mov" << s << " " << l << ", " << d << "\n";
        *os << "  or" << s << " " << r << ", " << d << "\n";
    }
}
void SystemV_x64::emitXor(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), l = cg.getValueAsOperand(i.getOperands()[0]->get()), r = cg.getValueAsOperand(i.getOperands()[1]->get()), s = getSuffix(i.getType());
        if (d != l) *os << "  mov" << s << " " << l << ", " << d << "\n";
        *os << "  xor" << s << " " << r << ", " << d << "\n";
    }
}
void SystemV_x64::emitShl(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), l = cg.getValueAsOperand(i.getOperands()[0]->get()), s = getSuffix(i.getType());
        if (d != l) *os << "  mov" << s << " " << l << ", " << d << "\n";
        if (auto* ci = dynamic_cast<ir::ConstantInt*>(i.getOperands()[1]->get())) *os << "  shl" << s << " $" << ci->getValue() << ", " << d << "\n";
        else { *os << "  movb " << cg.getValueAsOperand(i.getOperands()[1]->get()) << ", %cl\n  shl" << s << " %cl, " << d << "\n"; }
    }
}
void SystemV_x64::emitShr(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), l = cg.getValueAsOperand(i.getOperands()[0]->get()), s = getSuffix(i.getType());
        if (d != l) *os << "  mov" << s << " " << l << ", " << d << "\n";
        if (auto* ci = dynamic_cast<ir::ConstantInt*>(i.getOperands()[1]->get())) *os << "  shr" << s << " $" << ci->getValue() << ", " << d << "\n";
        else { *os << "  movb " << cg.getValueAsOperand(i.getOperands()[1]->get()) << ", %cl\n  shr" << s << " %cl, " << d << "\n"; }
    }
}
void SystemV_x64::emitSar(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), l = cg.getValueAsOperand(i.getOperands()[0]->get()), s = getSuffix(i.getType());
        if (d != l) *os << "  mov" << s << " " << l << ", " << d << "\n";
        if (auto* ci = dynamic_cast<ir::ConstantInt*>(i.getOperands()[1]->get())) *os << "  sar" << s << " $" << ci->getValue() << ", " << d << "\n";
        else { *os << "  movb " << cg.getValueAsOperand(i.getOperands()[1]->get()) << ", %cl\n  sar" << s << " %cl, " << d << "\n"; }
    }
}
void SystemV_x64::emitNeg(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), s = getSuffix(i.getType());
        if (d != cg.getValueAsOperand(i.getOperands()[0]->get())) *os << "  mov" << s << " " << cg.getValueAsOperand(i.getOperands()[0]->get()) << ", " << d << "\n";
        *os << "  neg" << s << " " << d << "\n";
    }
}
void SystemV_x64::emitNot(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), s = getSuffix(i.getType());
        if (d != cg.getValueAsOperand(i.getOperands()[0]->get())) *os << "  mov" << s << " " << cg.getValueAsOperand(i.getOperands()[0]->get()) << ", " << d << "\n";
        *os << "  not" << s << " " << d << "\n";
    }
}
void SystemV_x64::emitCopy(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), s = getSuffix(i.getType()), src = cg.getValueAsOperand(i.getOperands()[0]->get());
        if (d != src) *os << "  mov" << s << " " << src << ", " << d << "\n";
    }
}
void SystemV_x64::emitCall(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        for (size_t j = 1; j < std::min(i.getOperands().size(), (size_t)7); ++j)
            *os << "  movq " << cg.getValueAsOperand(i.getOperands()[j]->get()) << ", " << integerArgRegs[j-1] << "\n";
        *os << "  call " << i.getOperands()[0]->get()->getName() << "\n";
        if (!i.getType()->isVoidTy()) *os << "  movq %rax, " << cg.getValueAsOperand(&i) << "\n";
    }
}
void SystemV_x64::emitCmp(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string l = cg.getValueAsOperand(i.getOperands()[0]->get()), r = cg.getValueAsOperand(i.getOperands()[1]->get()), s = getSuffix(i.getOperands()[0]->get()->getType());
        std::string reg = (s == "q") ? "%rax" : "%eax";
        *os << "  mov" << s << " " << l << ", " << reg << "\n  cmp" << s << " " << r << ", " << reg << "\n";
        std::string set;
        switch (i.getOpcode()) {
            case ir::Instruction::Ceq: set = "sete"; break; case ir::Instruction::Cne: set = "setne"; break;
            case ir::Instruction::Cslt: set = "setl"; break; case ir::Instruction::Csle: set = "setle"; break;
            case ir::Instruction::Csgt: set = "setg"; break; case ir::Instruction::Csge: set = "setge"; break;
            default: set = "sete"; break;
        }
        *os << "  " << set << " %al\n  movzbl %al, %eax\n  movl %eax, " << cg.getValueAsOperand(&i) << "\n";
    }
}
void SystemV_x64::emitLoad(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string d = cg.getValueAsOperand(&i), p = cg.getValueAsOperand(i.getOperands()[0]->get()), s = getSuffix(i.getType());
        if (p.find("%") != std::string::npos) *os << "  mov" << s << " (" << p << "), " << d << "\n";
        else { *os << "  movq " << p << ", %rax\n  mov" << s << " (%rax), " << d << "\n"; }
    }
}
void SystemV_x64::emitStore(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        std::string v = cg.getValueAsOperand(i.getOperands()[0]->get()), p = cg.getValueAsOperand(i.getOperands()[1]->get()), s = getSuffix(i.getOperands()[0]->get()->getType());
        if (p.find("%") != std::string::npos) *os << "  mov" << s << " " << v << ", (" << p << ")\n";
        else { *os << "  movq " << p << ", %rdx\n  mov" << s << " " << v << ", (%rdx)\n"; }
    }
}
void SystemV_x64::emitBr(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) {
        *os << "  cmpl $0, " << cg.getValueAsOperand(i.getOperands()[0]->get()) << "\n  jne " << cg.getValueAsOperand(i.getOperands()[1]->get()) << "\n";
        if (i.getOperands().size() > 2) *os << "  jmp " << cg.getValueAsOperand(i.getOperands()[2]->get()) << "\n";
    }
}
void SystemV_x64::emitJmp(CodeGen& cg, ir::Instruction& i) { if (auto* os = cg.getTextStream()) *os << "  jmp " << cg.getValueAsOperand(i.getOperands()[0]->get()) << "\n"; }
void SystemV_x64::emitAlloc(CodeGen& cg, ir::Instruction& i) {
    if (auto* os = cg.getTextStream()) *os << "  movq __heap_ptr(%rip), %rax\n  movq %rax, " << cg.getValueAsOperand(&i) << "\n  addq $8, __heap_ptr(%rip)\n";
}
void SystemV_x64::emitSyscall(CodeGen& cg, ir::Instruction& i) { (void)cg; (void)i; }
uint64_t SystemV_x64::getSyscallNumber(ir::SyscallId) const { return 0; }
void SystemV_x64::emitVAStart(CodeGen&, ir::Instruction&) {}
void SystemV_x64::emitVAArg(CodeGen&, ir::Instruction&) {}
void SystemV_x64::emitStartFunction(CodeGen& cg) { (void)cg; }
void SystemV_x64::emitFAdd(CodeGen&, ir::Instruction&) {}
void SystemV_x64::emitFSub(CodeGen&, ir::Instruction&) {}
void SystemV_x64::emitFMul(CodeGen&, ir::Instruction&) {}
void SystemV_x64::emitFDiv(CodeGen&, ir::Instruction&) {}
void SystemV_x64::emitCast(CodeGen&, ir::Instruction&, const ir::Type*, const ir::Type*) {}

} // namespace target
} // namespace codegen

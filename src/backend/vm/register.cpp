#include "register.hh"
#include <iostream>
#include <cmath>
#include <cstring>
#include "../fiber.hh"

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

RegisterVM::RegisterVM() {
    registers.resize(256, VAL_NIL);
    instruction_count = 0;
}

void RegisterVM::execute_function(const LIR::LIR_Function& function) {
    current_function_ = &function;
    execute_instructions(function, 0, function.instructions.size());
}

void RegisterVM::execute_instructions(const LIR::LIR_Function& function, size_t start_pc, size_t end_pc) {
    const LIR::LIR_Inst* instructions_ptr = function.instructions.data();
    const LIR::LIR_Inst* pc = instructions_ptr + start_pc;
    const LIR::LIR_Inst* end = instructions_ptr + end_pc;
    
    while (pc < end) {
        instruction_count++;
        if (instruction_count > MAX_INSTRUCTIONS) { std::cerr << "Instruction limit exceeded" << std::endl; return; }
        switch (pc->op) {
            case LIR::LIR_Op::LoadConst: {
                if (pc->const_val == VAL_NIL) {
                    registers[pc->dst] = VAL_NIL;
                } else {
                    registers[pc->dst] = pc->const_val;
                }
                break;
            }
            case LIR::LIR_Op::Add:
            case LIR::LIR_Op::Sub:
            case LIR::LIR_Op::Mul:
            case LIR::LIR_Op::Div:
            case LIR::LIR_Op::Mod:
            case LIR::LIR_Op::Neg:
            case LIR::LIR_Op::DecAdd:
            case LIR::LIR_Op::DecSub:
            case LIR::LIR_Op::DecMul:
            case LIR::LIR_Op::DecDiv:
            case LIR::LIR_Op::DecMod:
            case LIR::LIR_Op::DecNeg:
            case LIR::LIR_Op::DecRescale:
                execute_arithmetic(pc);
                break;
            case LIR::LIR_Op::CmpEQ:
            case LIR::LIR_Op::CmpNEQ:
            case LIR::LIR_Op::CmpLT:
            case LIR::LIR_Op::CmpLE:
            case LIR::LIR_Op::CmpGT:
            case LIR::LIR_Op::CmpGE:
                execute_comparison(pc);
                break;
            case LIR::LIR_Op::ListCreate:
            case LIR::LIR_Op::ListAppend:
            case LIR::LIR_Op::ListLen:
            case LIR::LIR_Op::ListIndex:
            case LIR::LIR_Op::DictCreate:
            case LIR::LIR_Op::DictSet:
            case LIR::LIR_Op::DictGet:
            case LIR::LIR_Op::DictHas:
            case LIR::LIR_Op::DictLen:
            case LIR::LIR_Op::DictItems:
            case LIR::LIR_Op::TupleCreate:
            case LIR::LIR_Op::TupleSet:
            case LIR::LIR_Op::TupleGet:
            case LIR::LIR_Op::TupleLen:
                execute_collections(pc);
                break;
            case LIR::LIR_Op::NewFrame:
            case LIR::LIR_Op::ConstructError:
            case LIR::LIR_Op::ConstructOk:
            case LIR::LIR_Op::IsError:
            case LIR::LIR_Op::Unwrap:
            case LIR::LIR_Op::FrameGetField:
            case LIR::LIR_Op::FrameSetField:
            case LIR::LIR_Op::FrameGetFieldAtomic:
            case LIR::LIR_Op::FrameSetFieldAtomic:
                execute_frames(pc);
                break;
            case LIR::LIR_Op::Jump:
            case LIR::LIR_Op::JumpIf:
            case LIR::LIR_Op::JumpIfFalse:
                execute_control_flow(pc, function);
                break;
            case LIR::LIR_Op::PrintInt:
            case LIR::LIR_Op::PrintUint:
            case LIR::LIR_Op::PrintFloat:
            case LIR::LIR_Op::PrintBool:
            case LIR::LIR_Op::PrintString:
                execute_io(pc);
                break;
            case LIR::LIR_Op::And:
            case LIR::LIR_Op::Or:
            case LIR::LIR_Op::Xor:
                execute_bitwise(pc);
                break;
            case LIR::LIR_Op::ChannelAlloc:
            case LIR::LIR_Op::ChannelSend:
            case LIR::LIR_Op::ChannelOffer:
            case LIR::LIR_Op::ChannelRecv:
            case LIR::LIR_Op::ChannelPoll:
            case LIR::LIR_Op::ChannelClose:
            case LIR::LIR_Op::ChannelHasData:
                execute_concurrency(pc);
                break;
            case LIR::LIR_Op::LoadGlobal:
            case LIR::LIR_Op::StoreGlobal:
                execute_modules(pc);
                break;
            case LIR::LIR_Op::MakeEnum:
            case LIR::LIR_Op::GetTag:
            case LIR::LIR_Op::GetPayload:
                execute_objects(pc);
                break;
            case LIR::LIR_Op::StringIndex:
            case LIR::LIR_Op::ToString:
            case LIR::LIR_Op::STR_CONCAT:
            case LIR::LIR_Op::STR_FORMAT:
                execute_strings(pc);
                break;
            case LIR::LIR_Op::Call:
            case LIR::LIR_Op::CallIndirect:
            case LIR::LIR_Op::CallBuiltin:
                execute_calls(pc);
                break;
            case LIR::LIR_Op::Cast:
                execute_cast(pc);
                break;
            case LIR::LIR_Op::Mov:
                registers[pc->dst] = registers[pc->a];
                break;
            case LIR::LIR_Op::Return:
            case LIR::LIR_Op::Ret: {
                if (pc->a != UINT32_MAX) {
                    registers[0] = registers[pc->a];
                }
                return;
            }
            default:
                execute_ffi(pc);
                break;
        }
        pc++;
    }
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM

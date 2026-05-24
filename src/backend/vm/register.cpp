#include "../../lir/lir.hh"
#include "../../lir/functions.hh"
#include "../../lir/function_registry.hh"
#include "../../lir/builtin_functions.hh"
#include "register.hh"
#include "../../runtime/runtime.h"
#include "../../runtime/runtime_list.h"
#include "../../runtime/runtime_dict.h"
#include "../../runtime/runtime_tuple.h"
#include "../../runtime/runtime_value.h"
#include <iostream>
#include <memory>
#include <cstring>
#include <cstdint>
#include <string>
#include <charconv>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

extern void* box_register_value(const RegisterValue& value);
extern RegisterValue unbox_register_value(void* boxed_value);

std::string RegisterVM::to_string(const RegisterValue& value) const {
    LmString s = lm_value_to_string(value);
    std::string result(s.data ? s.data : "nil");
    lm_string_free(s);
    return result;
}

bool RegisterVM::isErrorValue(LIR::Reg reg) const {
    auto& value = registers[reg];
    if (is_integer(value)) {
        int64_t int_val = as_i64(value);
        return int_val <= -1000000;
    }
    return false;
}

RegisterVM::RegisterVM() 
    : type_system(std::make_unique<TypeSystem>()) {
    registers.resize(1024, VAL_NIL);
    scheduler = std::make_unique<Scheduler>();
    current_time = 0;
    current_function_ = nullptr;
    
    shared_variables.emplace(std::piecewise_construct, 
        std::forward_as_tuple("shared_counter"), 
        std::forward_as_tuple(0));
}

void RegisterVM::reset() {
    std::fill(registers.begin(), registers.end(), VAL_NIL);
    argument_stack.clear();
    task_contexts.clear();
    channels.clear();
    scheduler = std::make_unique<Scheduler>();
    current_time = 0;
    current_function_ = nullptr;
    
    shared_variables.clear();
    shared_variables.emplace(std::piecewise_construct, 
        std::forward_as_tuple("shared_counter"), 
        std::forward_as_tuple(0));
    
    shared_cells.clear();
    default_atomic.store(0);
    work_queues.clear();
    work_queue_counter.store(0);
    instruction_count = 0;
}

static __int128 parse_i128(const std::string& s) {
    __int128 result = 0;
    bool neg = false;
    size_t i = 0;
    if (s.empty()) return 0;
    if (s[0] == '-') { neg = true; i = 1; }
    for (; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9')
            result = result * 10 + (s[i] - '0');
    }
    return neg ? -result : result;
}

static unsigned __int128 parse_u128(const std::string& s) {
    unsigned __int128 result = 0;
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9')
            result = result * 10 + (s[i] - '0');
    }
    return result;
}

void RegisterVM::execute_instructions(const LIR::LIR_Function& function, size_t start_pc, size_t end_pc) {
    const LIR::LIR_Inst* pc = function.instructions.data() + start_pc;
    const LIR::LIR_Inst* end = function.instructions.data() + end_pc;
    
    while (pc < end) {
        instruction_count++;
        if (instruction_count > MAX_INSTRUCTIONS) { std::cerr << "Instruction limit exceeded" << std::endl; return; }
        switch (pc->op) {
            case LIR::LIR_Op::LoadConst: {
                // Use the more robust constant loader logic
                if (pc->const_val == VAL_NIL) {
                    registers[pc->dst] = VAL_NIL;
                } else {
                    // Assuming const_val is already an LmValue/RegisterValue
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
            case LIR::LIR_Op::ToString:
            case LIR::LIR_Op::STR_CONCAT:
                execute_strings(pc);
                break;
            case LIR::LIR_Op::Call:
            case LIR::LIR_Op::CallVoid:
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
                if (pc->op == LIR::LIR_Op::Ret) registers[0] = registers[pc->a];
                return;
            }
            default:
                break;
        }
        pc++;
    }
}

void RegisterVM::execute_function(const LIR::LIR_Function& function) {
    execute_instructions(function, 0, function.instructions.size());
}

void RegisterVM::execute_lir_function(const LIR::LIRFunction& function) {
    LIR::LIR_Function temp_wrapper(function.getName(), 0);
    temp_wrapper.instructions = function.getInstructions();
    execute_instructions(temp_wrapper, 0, temp_wrapper.instructions.size());
}

LM::Backend::Fiber* RegisterVM::get_current_fiber() {
    static LM::Backend::Fiber dummy_fiber(0, nullptr);
    return &dummy_fiber;
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM

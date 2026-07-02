#include "lir.hh"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace LM {
namespace LIR {


// LIR_Inst implementations
std::string LIR_Inst::to_string() const {
    std::ostringstream oss;
    oss << lir_op_to_string(op);
    
    // Format based on operation type
    switch (op) {
        case LIR_Op::Mov:
            oss << " r" << dst << ", r" << a;
            break;
        case LIR_Op::LoadConst:
            if (IS_INT(const_val)) {
                oss << " r" << dst << ", " << UNBOX_INT(const_val);
            } else if (IS_NIL(const_val)) {
                oss << " r" << dst << ", nil";
            } else if (IS_BOOL(const_val)) {
                oss << " r" << dst << ", " << (UNBOX_BOOL(const_val) ? "true" : "false");
            } else {
                oss << " r" << dst << ", [boxed:" << std::hex << const_val << std::dec << "]";
            }
            break;
        case LIR_Op::Add:
        case LIR_Op::Sub:
        case LIR_Op::Mul:
        case LIR_Op::Div:
        case LIR_Op::Mod:
        case LIR_Op::And:
        case LIR_Op::Or:
        case LIR_Op::Xor:
        case LIR_Op::Shl:
        case LIR_Op::Shr:
        case LIR_Op::CmpEQ:
        case LIR_Op::CmpNEQ:
        case LIR_Op::CmpLT:
        case LIR_Op::CmpLE:
        case LIR_Op::CmpGT:
        case LIR_Op::CmpGE:
            oss << " r" << dst << ", r" << a << ", r" << b;
            break;
        case LIR_Op::Jump:
            oss << " " << imm;
            break;
        case LIR_Op::JumpIfFalse:
            oss << " r" << a << ", " << imm;
            break;
        case LIR_Op::Call:
            // Clear and rebuild to avoid "callcall" issue
            oss.str("");
            oss.clear();
            oss << "call ";
            if (dst != 0) {
                oss << "r" << dst << ", ";
            }
            oss << func_name << "(";
            for (size_t i = 0; i < call_args.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << "r" << call_args[i];
            }
            oss << ")";
            break;
        case LIR_Op::Param:
            oss << " r" << a;
            break;
        case LIR_Op::FuncDef:
            // Follow clean format: fn r2, add(r0, r1) or fn print(r0)
            oss << "fn ";
            if (dst != 0) {
                oss << "r" << dst << ", ";
            }
            oss << func_name << "(";
            for (size_t i = 0; i < call_args.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << "r" << call_args[i];
            }
            oss << ") {";
            break;
        case LIR_Op::Return:
            if (a != 0) {
                oss << " r" << a;
            } else if (dst != 0) {
                oss << " r" << dst;
            }
            break;
        case LIR_Op::Ret:
            if (a != 0) {
                oss << " r" << a;
            } else {
                oss << " r" << dst;
            }
            break;
        case LIR_Op::Load:
        case LIR_Op::Store:
            oss << " r" << dst << ", r" << a;
            if (b != 0) oss << ", r" << b;
            break;
        case LIR_Op::Cast:
            oss << " r" << dst << ", r" << a;
            break;
        case LIR_Op::ToString:
            oss << " r" << dst << ", r" << a; // Convert to string
            break;
        case LIR_Op::STR_CONCAT:
        case LIR_Op::STR_FORMAT:
            oss << " r" << dst << ", r" << a << ", r" << b;
            break;
        case LIR_Op::ListCreate:
            oss << " r" << dst;
            break;
        case LIR_Op::ListAppend:
            oss << " r" << dst << ", r" << a << ", r" << b;
            break;
        case LIR_Op::ListIndex:
            oss << " r" << dst << ", r" << a << ", r" << b;
            break;
        case LIR_Op::ListLen:
            oss << " r" << dst << ", r" << a;
            break;
        case LIR_Op::DictCreate:
            oss << " r" << dst;
            break;
        case LIR_Op::DictSet:
            oss << " r" << dst << ", r" << a << ", r" << b;
            break;
        case LIR_Op::DictGet:
        case LIR_Op::DictHas:
        case LIR_Op::DictLen:
            oss << " r" << dst << ", r" << a << ", r" << b;
            break;
        case LIR_Op::DictItems:
            oss << " r" << dst << ", r" << a;
            break;
        case LIR_Op::TupleCreate:
            oss << " r" << dst << ", " << imm;
            break;
        case LIR_Op::TupleGet:
        case LIR_Op::TupleLen:
            oss << " r" << dst << ", r" << a << ", r" << b;
            break;
        case LIR_Op::TupleSet:
            oss << " r" << dst << ", r" << a << ", r" << b;
            break;
        case LIR_Op::MakeEnum:
            oss << " r" << dst << ", " << imm;
            if (a != 0) {
                oss << ", r" << a;
            }
            break;
        case LIR_Op::GetTag:
        case LIR_Op::GetPayload:
            oss << " r" << dst << ", r" << a;
            break;
        case LIR_Op::NewFrame:
            oss << " r" << dst << ", " << func_name << ", fields=" << imm;
            break;
        case LIR_Op::FrameGetField:
            oss << " r" << dst << ", r" << a << ", offset=" << b;
            break;
        case LIR_Op::FrameSetField:
            oss << " r" << dst << ", offset=" << a << ", r" << b;
            break;
        case LIR_Op::FrameCallMethod:
            oss << " r" << dst << ", r" << a << ", " << func_name << "(";
            for (size_t i = 0; i < call_args.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << "r" << call_args[i];
            }
            oss << ")";
            break;
        case LIR_Op::FrameCallInit:
            oss << " r" << dst << ", " << func_name << ".init()";
            break;
        case LIR_Op::FrameCallDeinit:
            oss << " r" << dst << ", " << func_name << ".deinit()";
            break;
        case LIR_Op::TraitCallMethod:
            oss << " r" << dst << ", trait=" << type_name << ", method=" << func_name << "(";
            for (size_t i = 0; i < call_args.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << "r" << call_args[i];
            }
            oss << ")";
            break;
        case LIR_Op::MakeTraitObject:
            oss << " r" << dst << ", instance=r" << a << ", frame=" << func_name << ", trait=" << type_name;
            break;
        case LIR_Op::Nop:
            // No operands
            break;
        default:
            // Generic format for other operations
            if (dst != 0) oss << " r" << dst;
            if (a != 0) oss << ", r" << a;
            if (b != 0) oss << ", r" << b;
            if (imm != 0) oss << ", " << imm;
            break;
    }
    
    if (!comment.empty()) {
        oss << " ; " << comment;
    }
    
    return oss.str();
}

// LIR_Function implementations
std::string LIR_Function::to_string() const {
    std::ostringstream oss;
    oss << "function " << name << "(" << param_count << " params, " << register_count << " registers):\n";
    
    for (const auto& inst : instructions) {
        oss << "  " << inst.to_string() << "\n";
    }
    
    return oss.str();
}

// Utility function implementations
//
// Uses the LIR_OP_LIST X-macro so that every opcode in the enum has a
// matching stringifier.  This eliminates the "unknown" fall-through that the
// old hand-written switch silently hit for ~150 of 228 opcodes.  Whenever a
// new opcode is added to LIR_Op, it MUST also be added to LIR_OP_LIST in
// lir.hh; the static_assert below catches divergence at compile time.
namespace {
// Counts entries in LIR_OP_LIST (each X(name) bumps the counter by 1).
constexpr size_t lir_op_list_size() {
    size_t n = 0;
#define X(name) ++n;
    LIR_OP_LIST(X)
#undef X
    return n;
}
// Last entry of LIR_Op (used to derive the enum's cardinality, since no
// explicit values are assigned and entries are sequential).  Keep this name
// in sync with the enum.
constexpr size_t kLirOpCount_Enum = static_cast<size_t>(LIR_Op::FFIGetABIInfo) + 1;
static_assert(lir_op_list_size() == kLirOpCount_Enum,
              "LIR_OP_LIST is out of sync with LIR_Op enum — update both in lir.hh");
} // namespace

std::string lir_op_to_string(LIR_Op op) {
    switch (op) {
    #define X(name) case LIR_Op::name: return #name;
    LIR_OP_LIST(X)
    #undef X
    }
    return "unknown"; // unreachable if LIR_OP_LIST is complete
}

// CFG validation implementation
bool LIR_CFG::validate() const {
    // Check entry block exists
    if (entry_block_id >= blocks.size() || !blocks[entry_block_id]) {
        std::cerr << "CFG Error: Invalid entry block ID " << entry_block_id << std::endl;
        return false;
    }
    
    // Each block should have at most one terminator
    for (const auto& block : blocks) {
        if (!block) continue;
        
        int terminator_count = 0;
        for (const auto& inst : block->instructions) {
            if (inst.op == LIR_Op::Jump || 
                inst.op == LIR_Op::JumpIfFalse || 
                inst.op == LIR_Op::JumpIf || 
                inst.op == LIR_Op::Return ||
                inst.op == LIR_Op::Ret) {
                terminator_count++;
            }
        }
        
        if (terminator_count > 1) {
            std::cerr << "CFG Error: Block " << block->id << " has " << terminator_count << " terminators" << std::endl;
            return false; // Multiple terminators
        }
    }
    
    // Check all successor/predecessor relationships are valid
    for (const auto& block : blocks) {
        if (!block) continue;
        
        for (uint32_t succ_id : block->successors) {
            if (succ_id >= blocks.size() || !blocks[succ_id]) {
                std::cerr << "CFG Error: Block " << block->id << " has invalid successor " << succ_id << std::endl;
                return false; // Invalid successor
            }
        }
        
        for (uint32_t pred_id : block->predecessors) {
            if (pred_id >= blocks.size() || !blocks[pred_id]) {
                std::cerr << "CFG Error: Block " << block->id << " has invalid predecessor " << pred_id << std::endl;
                return false; // Invalid predecessor
            }
        }
    }
    
    // Check that jump targets match successors
    for (const auto& block : blocks) {
        if (!block) continue;
        
        if (!block->instructions.empty()) {
            const auto& last_inst = block->instructions.back();
            
            if (last_inst.op == LIR_Op::Jump) {
                uint32_t target = last_inst.imm;
                if (std::find(block->successors.begin(), block->successors.end(), target) == block->successors.end()) {
                    std::cerr << "CFG Error: Jump target " << target << " not in successors list for block " << block->id << std::endl;
                    return false;
                }
            } else if (last_inst.op == LIR_Op::JumpIfFalse) {
                uint32_t target = last_inst.imm;
                // JumpIfFalse should have two successors: target and fall-through
                if (block->successors.size() != 2) {
                    std::cerr << "CFG Error: JumpIfFalse block should have exactly 2 successors, has " << block->successors.size() << std::endl;
                    return false;
                }
                if (std::find(block->successors.begin(), block->successors.end(), target) == block->successors.end()) {
                    std::cerr << "CFG Error: JumpIfFalse target " << target << " not in successors list for block " << block->id << std::endl;
                    return false;
                }
            } else if (last_inst.op == LIR_Op::JumpIf) {
                uint32_t target = last_inst.imm;
                // JumpIf should have two successors: target and fall-through
                if (block->successors.size() != 2) {
                    std::cerr << "CFG Error: JumpIf block should have exactly 2 successors, has " << block->successors.size() << std::endl;
                    return false;
                }
                if (std::find(block->successors.begin(), block->successors.end(), target) == block->successors.end()) {
                    std::cerr << "CFG Error: JumpIf target " << target << " not in successors list for block " << block->id << std::endl;
                    return false;
                }
            }
        }
    }
    
    return true;
}

void LIR_CFG::dump_dot() const {
    std::cout << "digraph CFG {" << std::endl;
    std::cout << "  node [shape=box];" << std::endl;
    
    // Dump blocks
    for (const auto& block : blocks) {
        if (!block) continue;
        
        std::string label = block->label.empty() ? 
            "block_" + std::to_string(block->id) : block->label;
        
        std::cout << "  " << block->id << " [label=\"" << label << "\"];" << std::endl;
    }
    
    // Dump edges
    for (const auto& block : blocks) {
        if (!block) continue;
        
        for (uint32_t succ_id : block->successors) {
            std::cout << "  " << block->id << " -> " << succ_id << ";" << std::endl;
        }
    }
    
    std::cout << "}" << std::endl;
}

} // namespace LIR
} // namespace LM

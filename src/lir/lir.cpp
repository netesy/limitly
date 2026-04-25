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
            oss << " r" << dst << ", " << const_val->toString();
            break;
        case LIR_Op::Add:
        case LIR_Op::Sub:
        case LIR_Op::Mul:
        case LIR_Op::Div:
        case LIR_Op::Mod:
        case LIR_Op::And:
        case LIR_Op::Or:
        case LIR_Op::Xor:
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
        case LIR_Op::PrintInt:
        case LIR_Op::PrintUint:
        case LIR_Op::PrintFloat:
        case LIR_Op::PrintBool:
        case LIR_Op::PrintString:
            oss << " r" << a;
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
            oss << " r" << dst << ", r" << a << ", r" << b;
            break;
        case LIR_Op::DictItems:
            oss << " r" << dst << ", r" << a;
            break;
        case LIR_Op::TupleCreate:
            oss << " r" << dst << ", " << imm;
            break;
        case LIR_Op::TupleGet:
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
std::string lir_op_to_string(LIR_Op op) {
    switch (op) {
        case LIR_Op::Mov: return "mov";
        case LIR_Op::LoadConst: return "load_const";
        case LIR_Op::Add: return "add";
        case LIR_Op::Sub: return "sub";
        case LIR_Op::Mul: return "mul";
        case LIR_Op::Div: return "div";
        case LIR_Op::Mod: return "mod";
        case LIR_Op::Neg: return "neg";
        case LIR_Op::And: return "and";
        case LIR_Op::Or: return "or";
        case LIR_Op::Xor: return "xor";
        case LIR_Op::CmpEQ: return "cmpeq";
        case LIR_Op::CmpNEQ: return "cmpneq";
        case LIR_Op::CmpLT: return "cmplt";
        case LIR_Op::CmpLE: return "cmple";
        case LIR_Op::CmpGT: return "cmpgt";
        case LIR_Op::CmpGE: return "cmpge";
        case LIR_Op::Jump: return "jump";
        case LIR_Op::JumpIfFalse: return "jmp_if_false";
        case LIR_Op::JumpIf: return "jmp_if";
        case LIR_Op::Label: return "label";
        case LIR_Op::Call: return "call";
        case LIR_Op::CallVoid: return "call_void";
        case LIR_Op::CallIndirect: return "call_indirect";
        case LIR_Op::CallBuiltin: return "call_builtin";
        case LIR_Op::CallVariadic: return "call_variadic";
        case LIR_Op::FuncDef: return "fn";
        case LIR_Op::Param: return "param";
        case LIR_Op::Ret: return "ret";
        case LIR_Op::Return: return "return";
        case LIR_Op::VaStart: return "vastart";
        case LIR_Op::VaArg: return "vaarg";
        case LIR_Op::VaEnd: return "vaend";
        case LIR_Op::Copy: return "copy";
        case LIR_Op::PrintInt: return "print_int";
        case LIR_Op::PrintUint: return "print_uint";
        case LIR_Op::PrintFloat: return "print_float";
        case LIR_Op::PrintBool: return "print_bool";
        case LIR_Op::PrintString: return "print_string";
        case LIR_Op::Nop: return "nop";
        case LIR_Op::Load: return "load";
        case LIR_Op::Store: return "store";
        case LIR_Op::Cast: return "cast";
        case LIR_Op::ToString: return "to_string";
        case LIR_Op::STR_CONCAT: return "str_concat";
        case LIR_Op::STR_FORMAT: return "str_format";
        case LIR_Op::ConstructError: return "error";
        case LIR_Op::ConstructOk: return "ok";
        case LIR_Op::IsError: return "is_error";
        case LIR_Op::Unwrap: return "unwrap";
        case LIR_Op::UnwrapOr: return "unwrap_or";
        case LIR_Op::MakeEnum: return "make_enum";
        case LIR_Op::GetTag: return "get_tag";
        case LIR_Op::GetPayload: return "get_payload";

        //  === ATOMIC OPERATIONS ===
        case LIR_Op::AtomicLoad: return "atomic_load";
        case LIR_Op::AtomicStore: return "atomic_store";
        case LIR_Op::AtomicFetchAdd: return "atomic_fetch_add";
        case LIR_Op::Await: return "await";
        case LIR_Op::AsyncCall: return "async_call";

        //  === CHANNEL OPERATIONS ===
        case LIR_Op::ChannelOffer: return "channel_offer";
        case LIR_Op::ChannelPush: return "channel_push";
        case LIR_Op::ChannelPop: return "channel_pop";
        case LIR_Op::ChannelRecv: return "channel_recv";
        case LIR_Op::ChannelPoll: return "channel_poll";
        case LIR_Op::ChannelClose: return "channel_close";
        case LIR_Op::ChannelAlloc: return "channel_alloc";
        case LIR_Op::ChannelSend: return "channel_send";
        case LIR_Op::ChannelHasData: return "channel_has_data";
        
        // === THREADLESS CONCURRENCY ===
        case LIR_Op::TaskContextAlloc: return "task_context_alloc";
        case LIR_Op::TaskContextInit: return "task_context_init";
        case LIR_Op::TaskGetState: return "task_get_state";
        case LIR_Op::TaskSetState: return "task_set_state";
        case LIR_Op::TaskSetField: return "task_set_field";
        case LIR_Op::TaskGetField: return "task_get_field";
        case LIR_Op::SchedulerInit: return "scheduler_init";
        case LIR_Op::SchedulerRun: return "scheduler_run";
        case LIR_Op::SchedulerTick: return "scheduler_tick";
        case LIR_Op::SchedulerAddTask: return "scheduler_add_task";
        case LIR_Op::GetTickCount: return "get_tick_count";
        case LIR_Op::DelayUntil: return "delay_until";
        case LIR_Op::ParallelInit: return "parallel_init";
        case LIR_Op::ParallelSync: return "parallel_sync";
        
        // === LOCK-FREE PARALLEL OPERATIONS ===
        case LIR_Op::ListCreate: return "list_create";
        case LIR_Op::ListAppend: return "list_append";
        case LIR_Op::ListIndex: return "list_index";
        case LIR_Op::ListLen: return "list_len";
        case LIR_Op::DictCreate: return "dict_create";
        case LIR_Op::DictSet: return "dict_set";
        case LIR_Op::DictGet: return "dict_get";
        case LIR_Op::DictItems: return "dict_items";
        case LIR_Op::TupleCreate: return "tuple_create";
        case LIR_Op::TupleGet: return "tuple_get";
        case LIR_Op::TupleSet: return "tuple_set";
        case LIR_Op::NewFrame: return "new_frame";
        case LIR_Op::FrameGetField: return "frame_get_field";
        case LIR_Op::FrameSetField: return "frame_set_field";
        case LIR_Op::FrameCallMethod: return "frame_call_method";
        case LIR_Op::FrameCallInit: return "frame_call_init";
        case LIR_Op::FrameCallDeinit: return "frame_call_deinit";
        case LIR_Op::TraitCallMethod: return "trait_call_method";
        case LIR_Op::MakeTraitObject: return "make_trait_object";
        case LIR_Op::ImportModule: return "import_module";
        case LIR_Op::ExportSymbol: return "export_symbol";
        case LIR_Op::BeginModule: return "begin_module";
        case LIR_Op::EndModule: return "end_module";
        case LIR_Op::LoadGlobal: return "load_global";
        case LIR_Op::StoreGlobal: return "store_global";
        
        // === SHARED CELL OPERATIONS ===
        case LIR_Op::SharedCellAlloc: return "shared_cell_alloc";
        case LIR_Op::SharedCellLoad: return "shared_cell_load";
        case LIR_Op::SharedCellStore: return "shared_cell_store";
        case LIR_Op::SharedCellAdd: return "shared_cell_add";
        case LIR_Op::SharedCellSub: return "shared_cell_sub";
    }
    return "unknown";
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
                inst.op == LIR_Op::Return) {
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

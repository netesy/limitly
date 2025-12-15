#include "lir.hh"
#include <sstream>
#include <iomanip>

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
            oss << " r" << dst << ", r" << a;
            break;
        case LIR_Op::Print:
            oss << " r" << a;
            break;
        case LIR_Op::Return:
            if (dst != 0) {
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
        case LIR_Op::Concat:
            oss << " r" << dst << ", r" << a << ", r" << b;
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
        case LIR_Op::Jump: return "jmp";
        case LIR_Op::JumpIfFalse: return "jmp_if_false";
        case LIR_Op::Call: return "call";
        case LIR_Op::Return: return "ret";
        case LIR_Op::Print: return "print";
        case LIR_Op::Nop: return "nop";
        case LIR_Op::Load: return "load";
        case LIR_Op::Store: return "store";
        case LIR_Op::Cast: return "cast";
        case LIR_Op::Concat: return "concat";
        case LIR_Op::ConstructError: return "error";
        case LIR_Op::ConstructOk: return "ok";
        case LIR_Op::AtomicLoad: return "atomic_load";
        case LIR_Op::AtomicStore: return "atomic_store";
        case LIR_Op::AtomicFetchAdd: return "atomic_fetch_add";
        case LIR_Op::Await: return "await";
        case LIR_Op::AsyncCall: return "async_call";
        case LIR_Op::ListCreate: return "list_create";
        case LIR_Op::ListAppend: return "list_append";
        case LIR_Op::ListIndex: return "list_index";
        case LIR_Op::NewObject: return "new";
        case LIR_Op::GetField: return "get_field";
        case LIR_Op::SetField: return "set_field";
        case LIR_Op::ImportModule: return "import_module";
        case LIR_Op::ExportSymbol: return "export_symbol";
        case LIR_Op::BeginModule: return "begin_module";
        case LIR_Op::EndModule: return "end_module";
    }
    return "unknown";
}

} // namespace LIR

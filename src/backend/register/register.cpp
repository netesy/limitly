#include "register.hh"
#include "../../lir/lir.hh"
#include "../types.hh"
#include <iostream>
#include <cstring>

namespace Register {

RegisterVM::RegisterVM() 
    : memoryRegion(memoryManager), 
      type_system(std::make_unique<TypeSystem>(memoryManager, memoryRegion)) {
    registers.resize(1024, nullptr);
    scheduler = std::make_unique<Scheduler>();
    current_time = 0;
    current_function_ = nullptr;
    
    // Initialize shared variables
    shared_variables.emplace(std::piecewise_construct, 
        std::forward_as_tuple("shared_counter"), 
        std::forward_as_tuple(0));
}

void RegisterVM::reset() {
    std::fill(registers.begin(), registers.end(), nullptr);
    task_contexts.clear();
    channels.clear();
    scheduler = std::make_unique<Scheduler>();
    current_time = 0;
    current_function_ = nullptr;
    
    // Reset shared variables
    shared_variables.clear();
    shared_variables.emplace(std::piecewise_construct, 
        std::forward_as_tuple("shared_counter"), 
        std::forward_as_tuple(0));
    
    // Reset atomic variables and work queues
    default_atomic.store(0);
    work_queues.clear();
    work_queue_counter.store(0);
    instruction_count = 0;
}

void RegisterVM::execute_instructions(const LIR::LIR_Function& function, size_t start_pc, size_t end_pc) {
    std::cout << "[DEBUG] execute_instructions: range " << start_pc << " to " << end_pc 
              << " (total instructions: " << function.instructions.size() << ")" << std::endl;
    
    // Debug: Print all instructions in the function
    for (size_t i = 0; i < function.instructions.size(); i++) {
        const auto& inst = function.instructions[i];
        std::cout << "[DEBUG] Instruction " << i << ": op=" << static_cast<int>(inst.op) 
                  << " dst=" << inst.dst << " a=" << inst.a << " b=" << inst.b << std::endl;
    }
    
    const LIR::LIR_Inst* pc = function.instructions.data() + start_pc;
    const LIR::LIR_Inst* end = function.instructions.data() + end_pc;
    
    // Dispatch table for computed goto - using runtime initialization
    void* dispatch_table[256] = {nullptr};
    dispatch_table[static_cast<int>(LIR::LIR_Op::Nop)] = &&OP_NOP;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Mov)] = &&OP_MOV;
    dispatch_table[static_cast<int>(LIR::LIR_Op::LoadConst)] = &&OP_LOADCONST;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Add)] = &&OP_ADD;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Sub)] = &&OP_SUB;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Mul)] = &&OP_MUL;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Div)] = &&OP_DIV;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Mod)] = &&OP_MOD;
    dispatch_table[static_cast<int>(LIR::LIR_Op::And)] = &&OP_AND;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Or)] = &&OP_OR;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Xor)] = &&OP_XOR;
    dispatch_table[static_cast<int>(LIR::LIR_Op::CmpEQ)] = &&OP_CMPEQ;
    dispatch_table[static_cast<int>(LIR::LIR_Op::CmpNEQ)] = &&OP_CMPNEQ;
    dispatch_table[static_cast<int>(LIR::LIR_Op::CmpLT)] = &&OP_CMPLT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::CmpLE)] = &&OP_CMPLE;
    dispatch_table[static_cast<int>(LIR::LIR_Op::CmpGT)] = &&OP_CMPGT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::CmpGE)] = &&OP_CMPGE;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Jump)] = &&OP_JUMP;
    dispatch_table[static_cast<int>(LIR::LIR_Op::JumpIfFalse)] = &&OP_JUMPIFFALSE;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Return)] = &&OP_RETURN;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Call)] = &&OP_CALL;
    dispatch_table[static_cast<int>(LIR::LIR_Op::PrintInt)] = &&OP_PRINTINT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::PrintUint)] = &&OP_PRINTUINT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::PrintFloat)] = &&OP_PRINTFLOAT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::PrintBool)] = &&OP_PRINTBOOL;
    dispatch_table[static_cast<int>(LIR::LIR_Op::PrintString)] = &&OP_PRINTSTRING;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ToString)] = &&OP_TOSTRING;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Concat)] = &&OP_CONCAT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::STR_CONCAT)] = &&OP_STR_CONCAT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::STR_FORMAT)] = &&OP_STR_FORMAT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Cast)] = &&OP_CAST;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Load)] = &&OP_LOAD;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Store)] = &&OP_STORE;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ListCreate)] = &&OP_LISTCREATE;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ListAppend)] = &&OP_LISTAPPEND;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ListIndex)] = &&OP_LISTINDEX;
    dispatch_table[static_cast<int>(LIR::LIR_Op::NewObject)] = &&OP_NEWOBJECT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::GetField)] = &&OP_GETFIELD;
    dispatch_table[static_cast<int>(LIR::LIR_Op::SetField)] = &&OP_SETFIELD;
    
    // Threadless Concurrency Operations
    dispatch_table[static_cast<int>(LIR::LIR_Op::TaskContextAlloc)] = &&OP_TASK_CONTEXT_ALLOC;
    dispatch_table[static_cast<int>(LIR::LIR_Op::TaskContextInit)] = &&OP_TASK_CONTEXT_INIT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::TaskGetState)] = &&OP_TASK_GET_STATE;
    dispatch_table[static_cast<int>(LIR::LIR_Op::TaskSetState)] = &&OP_TASK_SET_STATE;
    dispatch_table[static_cast<int>(LIR::LIR_Op::TaskSetField)] = &&OP_TASK_SET_FIELD;
    dispatch_table[static_cast<int>(LIR::LIR_Op::TaskGetField)] = &&OP_TASK_GET_FIELD;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ChannelAlloc)] = &&OP_CHANNEL_ALLOC;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ChannelPush)] = &&OP_CHANNEL_PUSH;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ChannelPop)] = &&OP_CHANNEL_POP;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ChannelHasData)] = &&OP_CHANNEL_HAS_DATA;
    dispatch_table[static_cast<int>(LIR::LIR_Op::SchedulerInit)] = &&OP_SCHEDULER_INIT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::SchedulerRun)] = &&OP_SCHEDULER_RUN;
    dispatch_table[static_cast<int>(LIR::LIR_Op::SchedulerTick)] = &&OP_SCHEDULER_TICK;
    dispatch_table[static_cast<int>(LIR::LIR_Op::GetTickCount)] = &&OP_GET_TICK_COUNT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::DelayUntil)] = &&OP_DELAY_UNTIL;
    
    // Additional missing operations
    dispatch_table[static_cast<int>(LIR::LIR_Op::Neg)] = &&OP_NEG;
    dispatch_table[static_cast<int>(LIR::LIR_Op::JumpIf)] = &&OP_JUMPIF;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Label)] = &&OP_LABEL;
    dispatch_table[static_cast<int>(LIR::LIR_Op::FuncDef)] = &&OP_FUNCDEF;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Param)] = &&OP_PARAM;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Ret)] = &&OP_RET;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ConstructError)] = &&OP_CONSTRUCTERROR;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ConstructOk)] = &&OP_CONSTRUCTOK;
    dispatch_table[static_cast<int>(LIR::LIR_Op::IsError)] = &&OP_ISERROR;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Unwrap)] = &&OP_UNWRAP;
    dispatch_table[static_cast<int>(LIR::LIR_Op::UnwrapOr)] = &&OP_UNWRAPOR;
    dispatch_table[static_cast<int>(LIR::LIR_Op::AtomicLoad)] = &&OP_ATOMICLOAD;
    dispatch_table[static_cast<int>(LIR::LIR_Op::AtomicStore)] = &&OP_ATOMICSTORE;
    dispatch_table[static_cast<int>(LIR::LIR_Op::AtomicFetchAdd)] = &&OP_ATOMICFETCHADD;
    dispatch_table[static_cast<int>(LIR::LIR_Op::Await)] = &&OP_AWAIT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::AsyncCall)] = &&OP_ASYNCCALL;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ImportModule)] = &&OP_IMPORTMODULE;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ExportSymbol)] = &&OP_EXPORTSYMBOL;
    dispatch_table[static_cast<int>(LIR::LIR_Op::BeginModule)] = &&OP_BEGINMODULE;
    dispatch_table[static_cast<int>(LIR::LIR_Op::EndModule)] = &&OP_ENDMODULE;
    
    // === LOCK-FREE PARALLEL OPERATIONS ===
    dispatch_table[static_cast<int>(LIR::LIR_Op::WorkQueueAlloc)] = &&OP_WORK_QUEUE_ALLOC;
    dispatch_table[static_cast<int>(LIR::LIR_Op::WorkQueuePush)] = &&OP_WORK_QUEUE_PUSH;
    dispatch_table[static_cast<int>(LIR::LIR_Op::WorkQueuePop)] = &&OP_WORK_QUEUE_POP;
    dispatch_table[static_cast<int>(LIR::LIR_Op::WorkerSignal)] = &&OP_WORKER_SIGNAL;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ParallelWaitComplete)] = &&OP_PARALLEL_WAIT_COMPLETE;
    dispatch_table[static_cast<int>(LIR::LIR_Op::TaskSetCode)] = &&OP_TASK_SET_CODE;
    
    // Dispatch macro - jumps to next instruction handler
    #define DISPATCH() \
        do { \
            pc++; \
            if (pc >= end) { \
                return; \
            } \
            instruction_count++; \
            if (instruction_count > MAX_INSTRUCTIONS) { \
                std::cerr << "Error: Instruction limit exceeded (" << MAX_INSTRUCTIONS << ") - possible infinite loop" << std::endl; \
                return; \
            } \
            goto *dispatch_table[static_cast<int>(pc->op)]; \
        } while(0)
    
    #define DISPATCH_JUMP(target) \
        pc = function.instructions.data() + (target); \
        if (pc >= end) return; \
        goto *dispatch_table[static_cast<int>(pc->op)]
    
    // Temporary variables declared outside all handlers to avoid destructor issues
    const RegisterValue* temp_a;
    const RegisterValue* temp_b;
    double double_result;
    int64_t int_result;
    bool bool_result;
    ValuePtr cv;
    
    // Start execution
    goto *dispatch_table[static_cast<int>(pc->op)];
    
    // ============ INSTRUCTION HANDLERS ============
    
OP_NOP:
    DISPATCH();

OP_MOV:
    registers[pc->dst] = registers[pc->a];
    DISPATCH();

OP_LOADCONST:
    cv = pc->const_val;
    if (!cv) {
        registers[pc->dst] = nullptr;
    } else {
        // Use the TypeSystem to handle type conversion properly
        TypePtr target_type;
        switch (pc->const_val->type->tag) {
            case TypeTag::Int8:
            case TypeTag::Int16:
            case TypeTag::Int32:
                target_type = type_system->INT32_TYPE;
                break;
            case TypeTag::Int:    
            case TypeTag::Int64:
                target_type = type_system->INT64_TYPE;
                break;
            case TypeTag::UInt8:
            case TypeTag::UInt16:
            case TypeTag::UInt32:
                target_type = type_system->UINT32_TYPE;
                break;
            case TypeTag::UInt:    
            case TypeTag::UInt64:
                target_type = type_system->UINT64_TYPE;
                break;    
            case TypeTag::Float32:
            case TypeTag::Float64:
                target_type = type_system->FLOAT64_TYPE;
                break;
            case TypeTag::Bool:
                target_type = type_system->BOOL_TYPE;
                break;
            case TypeTag::String:
                target_type = type_system->STRING_TYPE;
                break;
            default:
                target_type = type_system->NIL_TYPE;
                break;
        }
        
        // Create a typed value and convert to register representation
        ValuePtr typed_value = type_system->createValue(target_type);
        typed_value->data = cv->data;
        
        // Convert to register value representation
        if (target_type->tag == TypeTag::Int32 || target_type->tag == TypeTag::Int64) {
            registers[pc->dst] = static_cast<int64_t>(std::stoll(cv->data));
        } else if (target_type->tag == TypeTag::Float32) {
            registers[pc->dst] = std::stof(cv->data);
        } else if (target_type->tag == TypeTag::Float64) {
            registers[pc->dst] = std::stod(cv->data);
        } else if (target_type->tag == TypeTag::Bool) {
            registers[pc->dst] = static_cast<bool>(cv->data == "true");
        } else if (target_type->tag == TypeTag::String) {
            registers[pc->dst] = std::string(static_cast<const char*>(cv->data.c_str()));
        } else {
            registers[pc->dst] = nullptr;
        }
    }
    DISPATCH();

OP_ADD:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        TypePtr result_type = (pc->result_type == LIR::Type::F64) ? 
                              type_system->FLOAT64_TYPE : type_system->INT64_TYPE;
        
        bool a_is_float = std::holds_alternative<double>(*temp_a);
        bool b_is_float = std::holds_alternative<double>(*temp_b);
        
        if (result_type->tag == TypeTag::Float32 || result_type->tag == TypeTag::Float64 || a_is_float || b_is_float) {
            registers[pc->dst] = to_float(*temp_a) + to_float(*temp_b);
        } else {
            int64_t left = to_int(*temp_a);
            int64_t right = to_int(*temp_b);
            int64_t int_result = left + right;
            registers[pc->dst] = int_result;
            std::cout << "[DEBUG] ADD: " << left << " + " << right << " = " << int_result << std::endl;
        }
    } else {
        registers[pc->dst] = nullptr;
    }
    DISPATCH();

OP_SUB:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        TypePtr result_type = (pc->result_type == LIR::Type::F64) ? 
                              type_system->FLOAT64_TYPE : type_system->INT64_TYPE;
        
        bool a_is_float = std::holds_alternative<double>(*temp_a);
        bool b_is_float = std::holds_alternative<double>(*temp_b);
        
        if (result_type->tag == TypeTag::Float32 || result_type->tag == TypeTag::Float64 || a_is_float || b_is_float) {
            registers[pc->dst] = to_float(*temp_a) - to_float(*temp_b);
        } else {
            int64_t int_result = to_int(*temp_a) - to_int(*temp_b);
            registers[pc->dst] = int_result;
        }
    } else {
        registers[pc->dst] = nullptr;
    }
    DISPATCH();

OP_MUL:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        TypePtr result_type = (pc->result_type == LIR::Type::F64) ? 
                              type_system->FLOAT64_TYPE : type_system->INT64_TYPE;
        
        bool a_is_float = std::holds_alternative<double>(*temp_a);
        bool b_is_float = std::holds_alternative<double>(*temp_b);
        
        if (result_type->tag == TypeTag::Float32 || result_type->tag == TypeTag::Float64 || a_is_float || b_is_float) {
            registers[pc->dst] = to_float(*temp_a) * to_float(*temp_b);
        } else {
            int64_t int_result = to_int(*temp_a) * to_int(*temp_b);
            registers[pc->dst] = int_result;
        }
    } else {
        registers[pc->dst] = nullptr;
    }
    DISPATCH();

OP_DIV:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        TypePtr result_type = (pc->result_type == LIR::Type::F64) ? 
                              type_system->FLOAT64_TYPE : type_system->INT64_TYPE;
        
        bool a_is_float = std::holds_alternative<double>(*temp_a);
        bool b_is_float = std::holds_alternative<double>(*temp_b);
        
        if (result_type->tag == TypeTag::Float32 || result_type->tag == TypeTag::Float64 || a_is_float || b_is_float) {
            double double_result = to_float(*temp_b);
            if (double_result != 0.0) {
                registers[pc->dst] = to_float(*temp_a) / double_result;
            } else {
                registers[pc->dst] = std::numeric_limits<double>::infinity();
            }
        } else {
            int64_t int_result = to_int(*temp_b);
            if (int_result != 0) {
                registers[pc->dst] = to_int(*temp_a) / int_result;
            } else {
                registers[pc->dst] = 0;
            }
        }
    } else {
        registers[pc->dst] = nullptr;
    }
    DISPATCH();

OP_MOD:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        int_result = to_int(*temp_b);
        registers[pc->dst] = (int_result != 0) ? to_int(*temp_a) % int_result : 0;
    } else {
        registers[pc->dst] = nullptr;
    }
    DISPATCH();

OP_AND:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        registers[pc->dst] = to_int(*temp_a) & to_int(*temp_b);
    } else {
        registers[pc->dst] = to_bool(*temp_a) && to_bool(*temp_b);
    }
    DISPATCH();

OP_OR:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        registers[pc->dst] = to_int(*temp_a) | to_int(*temp_b);
    } else {
        registers[pc->dst] = to_bool(*temp_a) || to_bool(*temp_b);
    }
    DISPATCH();

OP_XOR:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        registers[pc->dst] = to_int(*temp_a) ^ to_int(*temp_b);
    } else {
        registers[pc->dst] = nullptr;
    }
    DISPATCH();

OP_CMPEQ:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    bool_result = false;
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        bool_result = to_float(*temp_a) == to_float(*temp_b);
    } else if (std::holds_alternative<std::string>(*temp_a) && std::holds_alternative<std::string>(*temp_b)) {
        bool_result = std::get<std::string>(*temp_a) == std::get<std::string>(*temp_b);
    }
    registers[pc->dst] = bool_result;
    DISPATCH();

OP_CMPNEQ:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    bool_result = false;
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        bool_result = to_float(*temp_a) != to_float(*temp_b);
    } else if (std::holds_alternative<std::string>(*temp_a) && std::holds_alternative<std::string>(*temp_b)) {
        bool_result = std::get<std::string>(*temp_a) != std::get<std::string>(*temp_b);
    }
    registers[pc->dst] = bool_result;
    DISPATCH();

OP_CMPLT:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    bool_result = false;
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        bool_result = to_float(*temp_a) < to_float(*temp_b);
    } else if (std::holds_alternative<std::string>(*temp_a) && std::holds_alternative<std::string>(*temp_b)) {
        bool_result = std::get<std::string>(*temp_a) < std::get<std::string>(*temp_b);
    }
    registers[pc->dst] = bool_result;
    DISPATCH();

OP_CMPLE:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    bool_result = false;
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        bool_result = to_float(*temp_a) <= to_float(*temp_b);
    } else if (std::holds_alternative<std::string>(*temp_a) && std::holds_alternative<std::string>(*temp_b)) {
        bool_result = std::get<std::string>(*temp_a) <= std::get<std::string>(*temp_b);
    }
    registers[pc->dst] = bool_result;
    DISPATCH();

OP_CMPGT:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    bool_result = false;
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        bool_result = to_float(*temp_a) > to_float(*temp_b);
    } else if (std::holds_alternative<std::string>(*temp_a) && std::holds_alternative<std::string>(*temp_b)) {
        bool_result = std::get<std::string>(*temp_a) > std::get<std::string>(*temp_b);
    }
    registers[pc->dst] = bool_result;
    DISPATCH();

OP_CMPGE:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    bool_result = false;
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        bool_result = to_float(*temp_a) >= to_float(*temp_b);
    } else if (std::holds_alternative<std::string>(*temp_a) && std::holds_alternative<std::string>(*temp_b)) {
        bool_result = std::get<std::string>(*temp_a) >= std::get<std::string>(*temp_b);
    }
    registers[pc->dst] = bool_result;
    DISPATCH();

OP_JUMP:
    DISPATCH_JUMP(pc->imm);

OP_JUMPIFFALSE:
    if (!to_bool(registers[pc->a])) {
        DISPATCH_JUMP(pc->imm);
    }
    DISPATCH();

OP_RETURN:
    return;

OP_CALL:
    // Handle builtin function calls
    {
        auto int_type = std::make_shared<Type>(TypeTag::Int64);
        
        // Create a channel and return its ID
        auto channel = std::make_unique<Channel>(32); // Default capacity 32
        uint64_t channel_id = channels.size();
        channels.push_back(std::move(channel));
        registers[pc->dst] = static_cast<int64_t>(channel_id);
    }
    DISPATCH();

OP_PRINTINT:
    std::cout << to_int(registers[pc->a]) << std::endl;
    DISPATCH();

OP_PRINTUINT:
    std::cout << to_int(registers[pc->a]) << std::endl;
    DISPATCH();

OP_PRINTFLOAT:
    std::cout << to_float(registers[pc->a]) << std::endl;
    DISPATCH();

OP_PRINTBOOL:
    std::cout << (to_bool(registers[pc->a]) ? "true" : "false") << std::endl;
    DISPATCH();

OP_PRINTSTRING:
    std::cout << to_string(registers[pc->a]) << std::endl;
    DISPATCH();

OP_TOSTRING:
    registers[pc->dst] = to_string(registers[pc->a]);
    DISPATCH();

OP_CONCAT:
    registers[pc->dst] = to_string(registers[pc->a]) + to_string(registers[pc->b]);
    DISPATCH();

OP_STR_CONCAT:
    registers[pc->dst] = to_string(registers[pc->a]) + to_string(registers[pc->b]);
    DISPATCH();

OP_STR_FORMAT:
    {
        std::string format = to_string(registers[pc->a]);
        std::string arg = to_string(registers[pc->b]);
        size_t pos = format.find("%s");
        if (pos != std::string::npos) {
            format.replace(pos, 2, arg);
        } else {
            format += arg;
        }
        registers[pc->dst] = format;
    }
    DISPATCH();

OP_CAST:
    registers[pc->dst] = registers[pc->a];
    DISPATCH();

OP_LOAD:
OP_STORE:
OP_LISTCREATE:
OP_LISTAPPEND:
OP_LISTINDEX:
OP_NEWOBJECT:
OP_GETFIELD:
OP_SETFIELD:
    registers[pc->dst] = nullptr;
    DISPATCH();

// ============ THREADLESS CONCURRENCY OPERATIONS ============

OP_TASK_CONTEXT_ALLOC:
    {
        uint64_t count = static_cast<uint64_t>(to_int(registers[pc->a]));
        uint64_t start_context_id = task_contexts.size();
        
        for (uint64_t i = 0; i < count; i++) {
            auto task_context = std::make_unique<TaskContext>();
            task_contexts.push_back(std::move(task_context));
        }
        
        registers[pc->dst] = static_cast<int64_t>(start_context_id);
    }
    DISPATCH();

OP_TASK_CONTEXT_INIT:
    {
        uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        if (context_id < task_contexts.size()) {
            auto& ctx = task_contexts[context_id];
            ctx->state = TaskState::INIT;
            ctx->task_id = context_id;
            registers[pc->dst] = static_cast<int64_t>(context_id);
        } else {
            registers[pc->dst] = static_cast<int64_t>(0);
        }
    }
    DISPATCH();

OP_TASK_GET_STATE:
    {
        uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        if (context_id < scheduler->tasks.size()) {
            registers[pc->dst] = static_cast<int64_t>(scheduler->tasks[context_id]->state);
        } else {
            registers[pc->dst] = static_cast<int64_t>(TaskState::INIT);
        }
    }
    DISPATCH();

OP_TASK_SET_STATE:
    {
        uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        TaskState new_state = static_cast<TaskState>(to_int(registers[pc->b]));
        if (context_id < scheduler->tasks.size()) {
            scheduler->tasks[context_id]->state = new_state;
            registers[pc->dst] = static_cast<int64_t>(1);
        } else {
            registers[pc->dst] = static_cast<int64_t>(0);
        }
    }
    DISPATCH();

OP_TASK_SET_FIELD:
    {
        uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        int field_index = static_cast<int>(to_int(registers[pc->b]));
        RegisterValue field_value = registers[pc->dst];

        if (pc->imm != 0) {
            field_index = static_cast<int>(pc->imm);
            field_value = registers[pc->b];
        }

        std::cout << "[DEBUG] task_set_field: context=" << context_id
                  << " field=" << field_index
                  << " value=" << to_int(field_value) << std::endl;

        if (context_id < task_contexts.size()) {
            auto& ctx = task_contexts[context_id];
            ctx->fields[field_index] = field_value;

            if (field_index == 2) {
                ctx->channel_ptr = field_value;
                std::cout << "[DEBUG] Set channel_ptr to " << to_int(field_value) << std::endl;
            } else if (field_index == 3) {
                ctx->counter = to_int(field_value);
            }

            registers[pc->dst] = static_cast<int64_t>(1);
        } else {
            registers[pc->dst] = static_cast<int64_t>(0);
        }
    }
    DISPATCH();

OP_TASK_GET_FIELD:
    {
        uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        int field_index = static_cast<int>(to_int(registers[pc->b]));
        if (context_id < scheduler->tasks.size()) {
            auto it = scheduler->tasks[context_id]->fields.find(field_index);
            if (it != scheduler->tasks[context_id]->fields.end()) {
                registers[pc->dst] = it->second;
            } else {
                registers[pc->dst] = static_cast<int64_t>(0);
            }
        } else {
            registers[pc->dst] = static_cast<int64_t>(0);
        }
    }
    DISPATCH();

OP_CHANNEL_ALLOC:
    {
        size_t capacity = static_cast<size_t>(to_int(registers[pc->a]));
        if (capacity == 0) capacity = 32;
        auto channel = std::make_unique<Channel>(capacity);
        uint64_t channel_id = channels.size();
        channels.push_back(std::move(channel));
        registers[pc->dst] = static_cast<int64_t>(channel_id);
    }
    DISPATCH();

OP_CHANNEL_PUSH:
    {
        uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        RegisterValue value = registers[pc->b];
        if (channel_id < channels.size()) {
            bool success = channels[channel_id]->push(value);
            registers[pc->dst] = static_cast<int64_t>(success ? 1 : 0);
        } else {
            registers[pc->dst] = static_cast<int64_t>(0);
        }
    }
    DISPATCH();

OP_CHANNEL_POP:
    {
        uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        if (channel_id < channels.size()) {
            RegisterValue value;
            bool success = channels[channel_id]->pop(value);
            if (success) {
                registers[pc->dst] = value;
            } else {
                registers[pc->dst] = nullptr;
            }
        } else {
            registers[pc->dst] = nullptr;
        }
    }
    DISPATCH();

OP_CHANNEL_HAS_DATA:
    {
        uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        if (channel_id < channels.size()) {
            registers[pc->dst] = static_cast<bool>(channels[channel_id]->has_data());
        } else {
            registers[pc->dst] = static_cast<bool>(false);
        }
    }
    DISPATCH();

OP_SCHEDULER_INIT:
    scheduler = std::make_unique<Scheduler>();
    current_time = 0;
    registers[pc->dst] = static_cast<int64_t>(1);
    DISPATCH();

OP_SCHEDULER_RUN:
    {
        for (auto& ctx : task_contexts) {
            if (!ctx) continue;

            if (ctx->state == TaskState::INIT) {
                ctx->state = TaskState::RUNNING;
                scheduler->add_task(std::make_unique<TaskContext>(*ctx));
            }
        }

        for (auto& task : scheduler->tasks) {
            if (task->state == TaskState::RUNNING) {
                std::cout << "Task " << task->task_id << " running" << std::endl;

                if (task->body_start_pc >= 0 && task->body_end_pc >= 0 && current_function_) {
                    execute_task_body(task.get(), *current_function_);
                }

                // Update shared counter from task's local register (register 3)
                auto shared_counter_reg = registers[3];
                if (!std::holds_alternative<std::nullptr_t>(shared_counter_reg)) {
                    int64_t updated_counter = to_int(shared_counter_reg);
                    std::cout << "[DEBUG] Task " << task->task_id << " register 3 = " << updated_counter << std::endl;
                    shared_variables["shared_counter"].store(updated_counter);
                    
                    std::cout << "[DEBUG] Updated shared_counter to " << updated_counter << std::endl;
                }

                if (!std::holds_alternative<std::nullptr_t>(task->channel_ptr)) {
                    uint64_t channel_id = static_cast<uint64_t>(to_int(task->channel_ptr));
                    int64_t new_counter_value = shared_variables["shared_counter"].load();

                    std::cout << "[DEBUG] Pushing to channel " << channel_id 
                              << " value " << new_counter_value << std::endl;

                    if (channel_id < channels.size()) {
                        channels[channel_id]->push(new_counter_value);
                    }
                }

                task->state = TaskState::COMPLETED;
            }
        }

        registers[pc->dst] = static_cast<int64_t>(1);
    }
    DISPATCH();

OP_SCHEDULER_TICK:
    scheduler->tick();
    current_time++;
    registers[pc->dst] = static_cast<int64_t>(1);
    DISPATCH();

OP_GET_TICK_COUNT:
    registers[pc->dst] = static_cast<int64_t>(current_time);
    DISPATCH();

OP_DELAY_UNTIL:
    {
        uint64_t target_time = static_cast<uint64_t>(to_int(registers[pc->a]));
        registers[pc->dst] = static_cast<bool>(current_time >= target_time);
    }
    DISPATCH();

// ============ ADDITIONAL MISSING OPERATIONS ============

OP_NEG:
    temp_a = &registers[pc->a];
    if (is_numeric(*temp_a)) {
        registers[pc->dst] = -to_float(*temp_a);
    } else {
        registers[pc->dst] = nullptr;
    }
    DISPATCH();

OP_JUMPIF:
    if (to_bool(registers[pc->a])) {
        DISPATCH_JUMP(pc->imm);
    }
    DISPATCH();

OP_LABEL:
    DISPATCH();

OP_FUNCDEF:
    DISPATCH();

OP_PARAM:
    DISPATCH();

OP_RET:
    return;

OP_CONSTRUCTERROR:
    registers[pc->dst] = nullptr;
    DISPATCH();

OP_CONSTRUCTOK:
    registers[pc->dst] = registers[pc->a];
    DISPATCH();

OP_ISERROR:
    registers[pc->dst] = static_cast<bool>(std::holds_alternative<std::nullptr_t>(registers[pc->a]));
    DISPATCH();

OP_UNWRAP:
    if (std::holds_alternative<std::nullptr_t>(registers[pc->a])) {
        registers[pc->dst] = nullptr;
    } else {
        registers[pc->dst] = registers[pc->a];
    }
    DISPATCH();

OP_UNWRAPOR:
    if (std::holds_alternative<std::nullptr_t>(registers[pc->a])) {
        registers[pc->dst] = registers[pc->b];
    } else {
        registers[pc->dst] = registers[pc->a];
    }
    DISPATCH();

OP_ATOMICLOAD:
    registers[pc->dst] = default_atomic.load();
    DISPATCH();

OP_ATOMICSTORE:
    {
        int64_t value = to_int(registers[pc->a]);
        default_atomic.store(value);
        registers[pc->dst] = static_cast<int64_t>(1);
    }
    DISPATCH();

OP_ATOMICFETCHADD:
    {
        int64_t addend = to_int(registers[pc->b]);
        int64_t old_value = default_atomic.fetch_add(addend);
        registers[pc->dst] = old_value;
    }
    DISPATCH();

OP_AWAIT:
    registers[pc->dst] = registers[pc->a];
    DISPATCH();

OP_ASYNCCALL:
    registers[pc->dst] = nullptr;
    DISPATCH();

OP_IMPORTMODULE:
    registers[pc->dst] = static_cast<int64_t>(1);
    DISPATCH();

OP_EXPORTSYMBOL:
    registers[pc->dst] = static_cast<int64_t>(1);
    DISPATCH();

OP_BEGINMODULE:
    DISPATCH();

OP_ENDMODULE:
    DISPATCH();

// === LOCK-FREE PARALLEL OPERATIONS ===

OP_WORK_QUEUE_ALLOC:
    {
        uint64_t size = static_cast<uint64_t>(to_int(registers[pc->a]));
        uint64_t queue_id = work_queue_counter.fetch_add(1);
        
        if (queue_id >= work_queues.size()) {
            work_queues.resize(queue_id + 1);
        }
        
        work_queues[queue_id] = std::queue<uint64_t>();
        registers[pc->dst] = static_cast<int64_t>(queue_id);
    }
    DISPATCH();

OP_WORK_QUEUE_PUSH:
    {
        uint64_t queue_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        uint64_t task_context = static_cast<uint64_t>(to_int(registers[pc->b]));
        
        if (queue_id < work_queues.size()) {
            work_queues[queue_id].push(task_context);
            registers[pc->dst] = static_cast<int64_t>(1);
        } else {
            registers[pc->dst] = static_cast<int64_t>(0);
        }
    }
    DISPATCH();

OP_WORK_QUEUE_POP:
    {
        uint64_t queue_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        
        if (queue_id < work_queues.size() && !work_queues[queue_id].empty()) {
            uint64_t task_context = work_queues[queue_id].front();
            work_queues[queue_id].pop();
            registers[pc->dst] = static_cast<int64_t>(task_context);
        } else {
            registers[pc->dst] = static_cast<int64_t>(0);
        }
    }
    DISPATCH();

OP_WORKER_SIGNAL:
    {
        uint64_t work_available = static_cast<uint64_t>(to_int(registers[pc->a]));
        uint64_t num_workers = static_cast<uint64_t>(to_int(registers[pc->b]));
        
        std::cout << "[DEBUG] WorkerSignal: Processing work queue" << std::endl;
        
        default_atomic.store(0);
        
        for (auto& queue : work_queues) {
            while (!queue.empty()) {
                uint64_t task_context = queue.front();
                queue.pop();
                
                if (task_context < task_contexts.size()) {
                    auto& task = task_contexts[task_context];
                    if (task->state == TaskState::RUNNING || task->state == TaskState::INIT) {
                        std::cout << "[DEBUG] Executing task " << task->task_id << std::endl;
                        
                        if (task->body_start_pc >= 0 && task->body_end_pc >= 0) {
                            execute_task_body(task.get(), *current_function_);
                        }
                        
                        task->state = TaskState::COMPLETED;
                    }
                }
            }
        }
        
        std::cout << "[DEBUG] All work complete" << std::endl;
        registers[pc->dst] = static_cast<int64_t>(1);
    }
    DISPATCH();

OP_PARALLEL_WAIT_COMPLETE:
    {
        uint64_t queue_handle = static_cast<uint64_t>(to_int(registers[pc->a]));
        uint64_t timeout_ms = static_cast<uint64_t>(to_int(registers[pc->b]));
        
        registers[pc->dst] = static_cast<int64_t>(1);
    }
    DISPATCH();

OP_TASK_SET_CODE:
    {
        uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        int64_t body_start = static_cast<int64_t>(to_int(registers[pc->b]));
        int64_t body_end = pc->imm;
        
        std::cout << "[DEBUG] task_set_code: context=" << context_id 
                  << " body_start=" << body_start 
                  << " body_end=" << body_end << std::endl;
        
        if (context_id < task_contexts.size()) {
            task_contexts[context_id]->body_start_pc = body_start;
            task_contexts[context_id]->body_end_pc = body_end;
            registers[pc->dst] = static_cast<int64_t>(1);
        } else {
            registers[pc->dst] = static_cast<int64_t>(0);
        }
    }
    DISPATCH();
    
    #undef DISPATCH
    #undef DISPATCH_JUMP
}

void RegisterVM::execute_task_body(TaskContext* task, const LIR::LIR_Function& function) {
    std::cout << "[DEBUG] Executing task body: PC " << task->body_start_pc 
              << " to " << task->body_end_pc << std::endl;
    
    // Set up task context parameters
    if (task) {
        // Set loop variable value from task context field 1
        auto loop_var_it = task->fields.find(1);
        if (loop_var_it != task->fields.end()) {
            registers[1] = loop_var_it->second;
            std::cout << "[DEBUG] Set loop variable r1 = " << to_int(loop_var_it->second) << std::endl;
        }
        
        // Set up other task context fields in registers
        auto task_id_it = task->fields.find(0);
        if (task_id_it != task->fields.end()) {
            registers[0] = task_id_it->second;
        }
        
        auto channel_it = task->fields.find(2);
        if (channel_it != task->fields.end()) {
            registers[2] = channel_it->second;
        }
        
        // Initialize shared counter with current global value (override task field)
        int64_t current_shared_counter = shared_variables["shared_counter"].load();
        registers[3] = current_shared_counter;
        std::cout << "[DEBUG] Task " << task->task_id << " starting with shared_counter = " << current_shared_counter << " (overriding task field)" << std::endl;
    }
    
    // Execute the task body using the shared instruction executor
    execute_instructions(function, task->body_start_pc, task->body_end_pc);
}

void RegisterVM::execute_function(const LIR::LIR_Function& function) {
    // Set current function for task execution
    current_function_ = &function;
    
    // Reset register file and initialize
    registers.resize(1024);
    for (auto& reg : registers) {
        reg = nullptr;
    }
    
    // Execute from start to end of function
    execute_instructions(function, 0, function.instructions.size());
}

std::string RegisterVM::to_string(const RegisterValue& value) const {
    if (std::holds_alternative<int64_t>(value)) {
        return std::to_string(std::get<int64_t>(value));
    } else if (std::holds_alternative<double>(value)) {
        return std::to_string(std::get<double>(value));
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? "true" : "false";
    } else if (std::holds_alternative<std::string>(value)) {
        return std::get<std::string>(value);
    }
    return "nil";
}

} // namespace Register
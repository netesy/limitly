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
    current_function = nullptr;
}

void RegisterVM::reset() {
    std::fill(registers.begin(), registers.end(), nullptr);
    task_contexts.clear();
    channels.clear();
    scheduler = std::make_unique<Scheduler>();
    current_time = 0;
    current_function = nullptr;
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

void RegisterVM::execute_function(const LIR::LIR_Function& function) {
    reset();
    
    // Store reference to function for type information access
    current_function = &function;
    
    const LIR::LIR_Inst* pc = function.instructions.data();
    const LIR::LIR_Inst* end = pc + function.instructions.size();
    
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
    
    // Dispatch macro - jumps to next instruction handler
    #define DISPATCH() \
        do { \
            pc++; \
            if (pc >= end) { \
                return; \
            } \
            goto *dispatch_table[static_cast<int>(pc->op)]; \
        } while (0)
    
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
        switch (pc->result_type) {
            case LIR::Type::I32:
                target_type = type_system->INT32_TYPE;
                break;
            case LIR::Type::I64:
                target_type = type_system->INT64_TYPE;
                break;
            case LIR::Type::F64:
                target_type = type_system->FLOAT64_TYPE;
                break;
            case LIR::Type::Bool:
                target_type = type_system->BOOL_TYPE;
                break;
            case LIR::Type::Ptr:
                // For pointer types, store as string (e.g., string literals)
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
        // Use TypeSystem to determine proper result type
        TypePtr result_type = (pc->result_type == LIR::Type::F64) ? 
                              type_system->FLOAT64_TYPE : type_system->INT64_TYPE;
        
        if (result_type->tag == TypeTag::Float64) {
            registers[pc->dst] = to_float(*temp_a) + to_float(*temp_b);
        } else {
            // For integer types (I32, I64)
            int64_t int_result = to_int(*temp_a) + to_int(*temp_b);
            registers[pc->dst] = int_result;
        }
    } else {
        registers[pc->dst] = nullptr;
    }
    DISPATCH();

OP_SUB:
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        // Use result_type to determine if we should return int or float
        if (pc->result_type == LIR::Type::F64) {
            registers[pc->dst] = to_float(*temp_a) - to_float(*temp_b);
        } else {
            // For integer types (I32, I64)
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
        // Use result_type to determine if we should return int or float
        if (pc->result_type == LIR::Type::F64) {
            registers[pc->dst] = to_float(*temp_a) * to_float(*temp_b);
        } else {
            // For integer types (I32, I64)
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
        double_result = to_float(*temp_b);
        if (double_result != 0.0) {
            // Use result_type to determine if we should return int or float
            if (pc->result_type == LIR::Type::F64) {
                registers[pc->dst] = to_float(*temp_a) / double_result;
            } else {
                // For integer types (I32, I64), perform integer division
                int_result = to_int(*temp_a) / to_int(*temp_b);
                registers[pc->dst] = int_result;
            }
        } else {
            registers[pc->dst] = 0; // Division by zero protection
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
        // For now, handle the channel() builtin specifically
        // pc->a contains the function to call, pc->dst contains the result register
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
    // String concatenation - store directly in register
    registers[pc->dst] = to_string(registers[pc->a]) + to_string(registers[pc->b]);
    DISPATCH();

OP_STR_CONCAT:
    // Explicit string concatenation - store directly in register
    registers[pc->dst] = to_string(registers[pc->a]) + to_string(registers[pc->b]);
    DISPATCH();

OP_STR_FORMAT:
    // String formatting - use snprintf-like behavior
    {
        std::string format = to_string(registers[pc->a]);
        std::string arg = to_string(registers[pc->b]);
        // Simple %s replacement for now
        size_t pos = format.find("%s");
        if (pos != std::string::npos) {
            format.replace(pos, 2, arg);
        } else {
            format += arg; // Fallback: append
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
    // Allocate task context array - pc->a contains count
    {
        uint64_t count = static_cast<uint64_t>(to_int(registers[pc->a]));
        uint64_t start_context_id = task_contexts.size();
        
        // Create 'count' number of task contexts
        for (uint64_t i = 0; i < count; i++) {
            auto task_context = std::make_unique<TaskContext>();
            task_contexts.push_back(std::move(task_context));
        }
        
        registers[pc->dst] = static_cast<int64_t>(start_context_id);
    }
    DISPATCH();

OP_TASK_CONTEXT_INIT:
    // Initialize task context - pc->a contains task_id
    {
        uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        if (context_id < task_contexts.size()) {
            task_contexts[context_id]->state = TaskState::RUNNING; // Set to RUNNING instead of INIT
            task_contexts[context_id]->task_id = context_id;
            // Add a copy to the scheduler, don't move the original
            auto task_copy = std::make_unique<TaskContext>(*task_contexts[context_id]);
            scheduler->add_task(std::move(task_copy));
            registers[pc->dst] = static_cast<int64_t>(1); // Success
        } else {
            registers[pc->dst] = static_cast<int64_t>(0); // Failure
        }
    }
    DISPATCH();

OP_TASK_GET_STATE:
    // Get task state - pc->a contains task context pointer
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
    // Set task state - pc->a contains context, pc->b contains new state
    {
        uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        TaskState new_state = static_cast<TaskState>(to_int(registers[pc->b]));
        if (context_id < scheduler->tasks.size()) {
            scheduler->tasks[context_id]->state = new_state;
            registers[pc->dst] = static_cast<int64_t>(1); // Success
        } else {
            registers[pc->dst] = static_cast<int64_t>(0); // Failure
        }
    }
    DISPATCH();

OP_TASK_SET_FIELD:
    // Set task field - pc->a contains context, pc->b contains field index or value, imm contains field index in some cases
    {
        uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        int field_index = static_cast<int>(to_int(registers[pc->b])); // Default to register b
        RegisterValue field_value = registers[pc->dst]; // Value to store
        
        // Check if we should use imm as field index (when b is used for value)
        if (pc->imm != 0) {
            field_index = static_cast<int>(pc->imm);
            field_value = registers[pc->b]; // Use register b as value
        }
        
        std::cout << "[DEBUG] task_set_field: context=" << context_id << " field=" << field_index << " value=" << to_int(field_value) << std::endl;
        
        if (context_id < scheduler->tasks.size()) {
            // Store the value in the task's fields
            scheduler->tasks[context_id]->fields[field_index] = field_value;
            
            // Special handling for channel pointer (field index 2)
            if (field_index == 2) {
                scheduler->tasks[context_id]->channel_ptr = field_value;
                std::cout << "[DEBUG] Set channel_ptr to " << to_int(field_value) << std::endl;
            }
            // Special handling for counter (field index 3) 
            else if (field_index == 3) {
                scheduler->tasks[context_id]->counter = to_int(field_value);
            }
            
            registers[pc->dst] = static_cast<int64_t>(1); // Success
        } else {
            registers[pc->dst] = static_cast<int64_t>(0); // Failure
        }
    }
    DISPATCH();

OP_TASK_GET_FIELD:
    // Get task field - pc->a contains context, pc->b contains field index
    {
        uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        int field_index = static_cast<int>(to_int(registers[pc->b]));
        if (context_id < scheduler->tasks.size()) {
            auto it = scheduler->tasks[context_id]->fields.find(field_index);
            if (it != scheduler->tasks[context_id]->fields.end()) {
                registers[pc->dst] = it->second;
            } else {
                registers[pc->dst] = static_cast<int64_t>(0); // Default value
            }
        } else {
            registers[pc->dst] = static_cast<int64_t>(0); // Default value
        }
    }
    DISPATCH();

OP_CHANNEL_ALLOC:
    // Allocate channel - pc->a contains capacity
    {
        size_t capacity = static_cast<size_t>(to_int(registers[pc->a]));
        if (capacity == 0) capacity = 32; // Default capacity if 0
        auto channel = std::make_unique<Channel>(capacity);
        uint64_t channel_id = channels.size();
        channels.push_back(std::move(channel));
        registers[pc->dst] = static_cast<int64_t>(channel_id);
    }
    DISPATCH();

OP_CHANNEL_PUSH:
    // Push to channel - pc->a contains channel pointer, pc->b contains value
    {
        uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        RegisterValue value = registers[pc->b];
        if (channel_id < channels.size()) {
            bool success = channels[channel_id]->push(value);
            registers[pc->dst] = static_cast<int64_t>(success ? 1 : 0);
        } else {
            registers[pc->dst] = static_cast<int64_t>(0); // Failure
        }
    }
    DISPATCH();

OP_CHANNEL_POP:
    // Pop from channel - pc->a contains channel pointer
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
    // Check if channel has data - pc->a contains channel pointer
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
    // Initialize scheduler
    scheduler = std::make_unique<Scheduler>();
    current_time = 0;
    registers[pc->dst] = static_cast<int64_t>(1); // Success
    DISPATCH();

OP_SCHEDULER_RUN:
    // Run scheduler - pc->a contains scheduler pointer
    {
        // Execute tasks based on their context setup from LIR
        for (auto& task : scheduler->tasks) {
            if (task->state == TaskState::INIT || task->state == TaskState::RUNNING) {
                // Execute the task based on its context
                // The LIR has set up the task context with:
                // - field 0: task_id
                // - field 1: loop_var  
                // - field 2: channel
                // - field 3: counter
                
                // Print task info
                std::cout << "Task " << task->task_id << " running" << std::endl;
                
                // Simulate task work - increment counter
                task->counter++;
                
                // Send counter to channel if channel is set
                std::cout << "[DEBUG] Task channel_ptr type: ";
                if (std::holds_alternative<std::nullptr_t>(task->channel_ptr)) {
                    std::cout << "nullptr" << std::endl;
                } else if (std::holds_alternative<int64_t>(task->channel_ptr)) {
                    std::cout << "int64_t = " << std::get<int64_t>(task->channel_ptr) << std::endl;
                } else if (std::holds_alternative<double>(task->channel_ptr)) {
                    std::cout << "double = " << std::get<double>(task->channel_ptr) << std::endl;
                } else {
                    std::cout << "unknown" << std::endl;
                }
                
                if (!std::holds_alternative<std::nullptr_t>(task->channel_ptr)) {
                    uint64_t channel_id = static_cast<uint64_t>(to_int(task->channel_ptr));
                    std::cout << "[DEBUG] Pushing to channel " << channel_id << " value " << task->counter << std::endl;
                    if (channel_id < channels.size()) {
                        channels[channel_id]->push(static_cast<int64_t>(task->counter));
                        std::cout << "[DEBUG] Push successful" << std::endl;
                    } else {
                        std::cout << "[DEBUG] Channel " << channel_id << " out of range (max " << channels.size() << ")" << std::endl;
                    }
                } else {
                    std::cout << "[DEBUG] No channel pointer set" << std::endl;
                }
                
                // Mark task as completed
                task->state = TaskState::COMPLETED;
            }
        }
        
        registers[pc->dst] = static_cast<int64_t>(1); // Success
    }
    DISPATCH();

OP_SCHEDULER_TICK:
    // Single scheduler tick - pc->a contains scheduler pointer
    scheduler->tick();
    current_time++;
    registers[pc->dst] = static_cast<int64_t>(1); // Success
    DISPATCH();

OP_GET_TICK_COUNT:
    // Get current tick count - use the scheduler's time
    registers[pc->dst] = static_cast<int64_t>(current_time);
    DISPATCH();

OP_DELAY_UNTIL:
    // Check if delay until time has passed - pc->a contains target time
    {
        uint64_t target_time = static_cast<uint64_t>(to_int(registers[pc->a]));
        registers[pc->dst] = static_cast<bool>(current_time >= target_time);
    }
    DISPATCH();

// ============ ADDITIONAL MISSING OPERATIONS ============

OP_NEG:
    // Negate operation - pc->a contains source, dst contains result
    temp_a = &registers[pc->a];
    if (is_numeric(*temp_a)) {
        registers[pc->dst] = -to_float(*temp_a);
    } else {
        registers[pc->dst] = nullptr;
    }
    DISPATCH();

OP_JUMPIF:
    // Jump if condition is true
    if (to_bool(registers[pc->a])) {
        DISPATCH_JUMP(pc->imm);
    }
    DISPATCH();

OP_LABEL:
    // Label definition - no operation, just continue
    DISPATCH();

OP_FUNCDEF:
    // Function definition - no operation for now
    DISPATCH();

OP_PARAM:
    // Parameter definition - no operation for now
    DISPATCH();

OP_RET:
    // Function return with register - similar to Return but may return a value
    // For now, just return like Return
    return;

OP_CONSTRUCTERROR:
    // Construct error result
    registers[pc->dst] = nullptr; // Placeholder for error
    DISPATCH();

OP_CONSTRUCTOK:
    // Construct ok result
    registers[pc->dst] = registers[pc->a]; // Wrap value in ok result
    DISPATCH();

OP_ISERROR:
    // Check if result contains error
    registers[pc->dst] = static_cast<bool>(std::holds_alternative<std::nullptr_t>(registers[pc->a]));
    DISPATCH();

OP_UNWRAP:
    // Unwrap result value (panic if error)
    if (std::holds_alternative<std::nullptr_t>(registers[pc->a])) {
        // Panic - for now just return null
        registers[pc->dst] = nullptr;
    } else {
        registers[pc->dst] = registers[pc->a];
    }
    DISPATCH();

OP_UNWRAPOR:
    // Unwrap with default value
    if (std::holds_alternative<std::nullptr_t>(registers[pc->a])) {
        registers[pc->dst] = registers[pc->b]; // Use default
    } else {
        registers[pc->dst] = registers[pc->a];
    }
    DISPATCH();

OP_ATOMICLOAD:
    // Atomic load - placeholder
    registers[pc->dst] = registers[pc->a];
    DISPATCH();

OP_ATOMICSTORE:
    // Atomic store - placeholder
    registers[pc->dst] = registers[pc->a];
    DISPATCH();

OP_ATOMICFETCHADD:
    // Atomic fetch and add - placeholder
    temp_a = &registers[pc->a];
    temp_b = &registers[pc->b];
    if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        registers[pc->dst] = to_int(*temp_a) + to_int(*temp_b);
    } else {
        registers[pc->dst] = nullptr;
    }
    DISPATCH();

OP_AWAIT:
    // Await operation - placeholder
    registers[pc->dst] = registers[pc->a];
    DISPATCH();

OP_ASYNCCALL:
    // Async call - placeholder
    registers[pc->dst] = nullptr;
    DISPATCH();

OP_IMPORTMODULE:
    // Import module - placeholder
    registers[pc->dst] = static_cast<int64_t>(1); // Success
    DISPATCH();

OP_EXPORTSYMBOL:
    // Export symbol - placeholder
    registers[pc->dst] = static_cast<int64_t>(1); // Success
    DISPATCH();

OP_BEGINMODULE:
    // Begin module - placeholder
    DISPATCH();

OP_ENDMODULE:
    // End module - placeholder
    DISPATCH();

// === LOCK-FREE PARALLEL OPERATIONS ===

OP_WORK_QUEUE_ALLOC:
    // Allocate lock-free work queue
    {
        uint64_t size = static_cast<uint64_t>(to_int(registers[pc->a]));
        // For now, just return a handle (simplified implementation)
        static uint64_t queue_handle = 1000; // Simple handle allocation
        registers[pc->dst] = static_cast<int64_t>(queue_handle++);
    }
    DISPATCH();

OP_WORK_QUEUE_PUSH:
    // Push task to work queue (atomic)
    {
        uint64_t queue_handle = static_cast<uint64_t>(to_int(registers[pc->a]));
        uint64_t task_context = static_cast<uint64_t>(to_int(registers[pc->b]));
        
        // Simplified: just store in a global vector (real implementation would use lock-free queue)
        static std::vector<uint64_t> work_queue;
        work_queue.push_back(task_context);
        
        registers[pc->dst] = static_cast<int64_t>(1); // Success
    }
    DISPATCH();

OP_WORK_QUEUE_POP:
    // Pop task from work queue (atomic)
    {
        uint64_t queue_handle = static_cast<uint64_t>(to_int(registers[pc->a]));
        
        // Simplified: pop from global vector
        static std::vector<uint64_t> work_queue;
        if (!work_queue.empty()) {
            uint64_t task_context = work_queue.back();
            work_queue.pop_back();
            registers[pc->dst] = static_cast<int64_t>(task_context);
        } else {
            registers[pc->dst] = static_cast<int64_t>(0); // Empty
        }
    }
    DISPATCH();

OP_WORKER_SIGNAL:
    // Signal workers to start (atomic store)
    {
        uint64_t work_available = static_cast<uint64_t>(to_int(registers[pc->a]));
        uint64_t active_workers = static_cast<uint64_t>(to_int(registers[pc->b]));
        
        // Set global flag (simplified)
        static uint64_t global_work_available = 0;
        static uint64_t global_active_workers = 0;
        
        global_work_available = work_available;
        global_active_workers = active_workers;
        
        registers[pc->dst] = static_cast<int64_t>(1); // Success
    }
    DISPATCH();

OP_PARALLEL_WAIT_COMPLETE:
    // Wait for all workers to complete
    {
        uint64_t queue_handle = static_cast<uint64_t>(to_int(registers[pc->a]));
        uint64_t timeout_ms = static_cast<uint64_t>(to_int(registers[pc->b]));
        
        // Simplified: just return success (real implementation would wait with timeout)
        registers[pc->dst] = static_cast<int64_t>(1); // Success
    }
    DISPATCH();
    
    #undef DISPATCH
    #undef DISPATCH_JUMP
}

} // namespace Register
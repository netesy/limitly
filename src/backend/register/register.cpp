#include "register.hh"
#include "../../lir/lir.hh"
#include "../../lir/functions.hh"
#include "../../lir/builtin_functions.hh"
#include "../types.hh"
#include "../value.hh"
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
        } else if (target_type->tag == TypeTag::UInt32 || target_type->tag == TypeTag::UInt64) {
            registers[pc->dst] = static_cast<uint64_t>(std::stoull(cv->data));
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
    
    // Handle nullptr comparisons (for optional types)
    if (std::holds_alternative<std::nullptr_t>(*temp_a) || std::holds_alternative<std::nullptr_t>(*temp_b)) {
        // nullptr is considered equal to 0 and false, different from everything else
        bool a_is_null = std::holds_alternative<std::nullptr_t>(*temp_a);
        bool b_is_null = std::holds_alternative<std::nullptr_t>(*temp_b);
        
        if (a_is_null && b_is_null) {
            bool_result = false; // nullptr == nullptr
        } else if (a_is_null) {
            // nullptr compared with b
            if (is_numeric(*temp_b)) {
                bool_result = (to_int(*temp_b) != 0); // nullptr != 0 is false, nullptr != non-zero is true
            } else {
                bool_result = true; // nullptr != non-numeric is true
            }
        } else if (b_is_null) {
            // a compared with nullptr
            if (is_numeric(*temp_a)) {
                bool_result = (to_int(*temp_a) != 0); // 0 != nullptr is false, non-zero != nullptr is true
            } else {
                bool_result = true; // non-numeric != nullptr is true
            }
        }
    } else if (is_numeric(*temp_a) && is_numeric(*temp_b)) {
        bool_result = to_float(*temp_a) != to_float(*temp_b);
    } else if (std::holds_alternative<std::string>(*temp_a) && std::holds_alternative<std::string>(*temp_b)) {
        bool_result = std::get<std::string>(*temp_a) != std::get<std::string>(*temp_b);
    } else {
        // Mixed type comparison - for optional types, non-null values are != 0
        if (is_numeric(*temp_a) && std::holds_alternative<std::string>(*temp_b)) {
            // number != string: true unless number is 0 and string is empty
            bool_result = true;
        } else if (std::holds_alternative<std::string>(*temp_a) && is_numeric(*temp_b)) {
            // string != number: true unless string is empty and number is 0
            bool_result = true;
        } else {
            // Other mixed types: generally not equal
            bool_result = true;
        }
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
    // Copy return value from specified register to register 0 (standard return register)
    if (pc->dst != 0) {
        registers[0] = registers[pc->dst];
    }
    return;

OP_CALL:
    // Handle both builtin and user function calls using new LIR format
    {
        // Check if this instruction uses the new format (has func_name and call_args)
        if (!pc->func_name.empty()) {
            // New format: call r2, add(r0, r1)
            std::string func_name = pc->func_name;
            const auto& arg_regs = pc->call_args;
            
            //std::cout << "[DEBUG] New format call to '" << func_name << "' with " << arg_regs.size() << " arguments" << std::endl;
            
            // First try builtin functions
            if (LIR::BuiltinUtils::isBuiltinFunction(func_name)) {
                // Collect arguments from the specified registers
                std::vector<ValuePtr> args;
                
                for (size_t i = 0; i < arg_regs.size(); ++i) {
                    auto reg_value = registers[arg_regs[i]];
                    
                  
                    // Convert register value to ValuePtr
                    ValuePtr arg_value;
                    if (std::holds_alternative<int64_t>(reg_value)) {
                        auto int_type = std::make_shared<::Type>(TypeTag::Int);
                        arg_value = std::make_shared<Value>(int_type, std::get<int64_t>(reg_value));
                    } else if (std::holds_alternative<double>(reg_value)) {
                        auto float_type = std::make_shared<::Type>(TypeTag::Float64);
                        arg_value = std::make_shared<Value>(float_type, std::get<double>(reg_value));
                    } else if (std::holds_alternative<bool>(reg_value)) {
                        auto bool_type = std::make_shared<::Type>(TypeTag::Bool);
                        arg_value = std::make_shared<Value>(bool_type, std::get<bool>(reg_value));
                    } else if (std::holds_alternative<std::string>(reg_value)) {
                        auto string_type = std::make_shared<::Type>(TypeTag::String);
                        arg_value = std::make_shared<Value>(string_type, std::get<std::string>(reg_value));
                    } else {
                        auto nil_type = std::make_shared<::Type>(TypeTag::Nil);
                        arg_value = std::make_shared<Value>(nil_type);
                    }
                    args.push_back(arg_value);
                }
                
                try {
                    // Call builtin function
                    ValuePtr result = LIR::BuiltinUtils::callBuiltinFunction(func_name, args);
                    
                    //std::cout << "[DEBUG] Builtin function '" << func_name << "' returned: ";
                    if (result && result->type) {
                        //std::cout << "type=" << static_cast<int>(result->type->tag) << std::endl;
                    } else {
                        //std::cout << "nullptr" << std::endl;
                    }
                    
                    // Convert result back to register value
                    if (result && result->type) {
                        switch (result->type->tag) {
                            case TypeTag::Int:
                            case TypeTag::Int64:
                                registers[pc->dst] = result->as<int64_t>();
                                break;
                            case TypeTag::Float32:
                            case TypeTag::Float64:
                                registers[pc->dst] = result->as<double>();
                                break;
                            case TypeTag::Bool:
                                registers[pc->dst] = result->as<bool>();
                                break;
                            case TypeTag::String:
                                registers[pc->dst] = result->as<std::string>();
                                break;
                            default:
                                registers[pc->dst] = nullptr;
                                break;
                        }
                    } else {
                        registers[pc->dst] = nullptr;
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error calling builtin function " << func_name << ": " << e.what() << std::endl;
                    registers[pc->dst] = nullptr;
                }
                
                DISPATCH();
            }
            
            // Then try user-defined functions
            auto& func_manager = LIR::LIRFunctionManager::getInstance();
            if (func_manager.hasFunction(func_name)) {
                auto func = func_manager.getFunction(func_name);
                
                if (func) {
                    //std::cout << "[DEBUG] Calling user function '" << func_name << "' with " << arg_regs.size() << " arguments" << std::endl;
                    
                    // Save current context
                    auto saved_registers = registers;
                    
                    // Set up parameters (copy arguments to parameter registers r0, r1, r2, ...)
                   // std::cout << "[DEBUG] Setting up " << func->getParameters().size() << " parameters for function '" << func_name << "'" << std::endl;
                   // std::cout << "[DEBUG] Provided arguments: " << arg_regs.size() << std::endl;
                    
                    for (size_t i = 0; i < func->getParameters().size(); ++i) {
                        if (i < arg_regs.size()) {
                            // Copy provided argument
                            registers[i] = registers[arg_regs[i]];
                        //    // std::cout << "[DEBUG] Parameter " << i << " (r" << i << ") = register r" << arg_regs[i];
                            
                        //     // Debug: show the actual value
                        //     auto& val = registers[i];
                        //     if (std::holds_alternative<std::string>(val)) {
                        //         std::cout << " (string: '" << std::get<std::string>(val) << "')";
                        //     } else if (std::holds_alternative<std::nullptr_t>(val)) {
                        //         std::cout << " (nullptr)";
                        //     } else if (std::holds_alternative<int64_t>(val)) {
                        //         std::cout << " (int: " << std::get<int64_t>(val) << ")";
                        //     }
                        //     std::cout << std::endl;
                        } else {
                                registers[i] = nullptr;

                        }
                    }
                    
                    // Execute function directly without resetting registers
                    // Create a temporary LIR_Function wrapper to reuse existing execution logic
                    LIR::LIR_Function temp_wrapper(func->getName(), func->getParameters().size());
                    temp_wrapper.instructions = func->getInstructions();
                    execute_instructions(temp_wrapper, 0, temp_wrapper.instructions.size());
                    
                    // Get return value from register 0 (standard return register)
                    auto return_value = registers[0];
                  
                  
                    // Restore caller's registers
                    registers = saved_registers;
                    
                    // Set return value in destination register
                    registers[pc->dst] = return_value;
                    
                    DISPATCH();
                }
            }
            
            // Function not found
            std::cerr << "Error: Function '" << func_name << "' not found" << std::endl;
            registers[pc->dst] = nullptr;
            DISPATCH();
        }
        
        // Legacy format fallback (for backward compatibility)
        // Get function index from operand b (immediate value)
        int64_t func_index = static_cast<int64_t>(pc->b);
        
        // Get argument count from operand a (immediate value)
        int arg_count = static_cast<int>(pc->a);
        
        // First try builtin functions
        auto builtin_names = LIR::BuiltinUtils::getBuiltinFunctionNames();
       
        
        // Then try user-defined functions
        auto& func_manager = LIR::LIRFunctionManager::getInstance();
        auto function_names = func_manager.getFunctionNames();
        
        // Adjust index for user functions (subtract builtin count)
        int64_t user_func_index = func_index - builtin_names.size();
        
        if (user_func_index >= 0 && user_func_index < function_names.size()) {
            auto func_name = function_names[user_func_index];
            auto func = func_manager.getFunction(func_name);
            
            if (func) {
                // Save current context
                auto saved_registers = registers;
                auto saved_pc = pc;
                
                // Set up parameters (move from caller's parameter registers to callee's parameter registers)
                int arg_count = static_cast<int>(pc->b);
                for (int i = 0; i < func->getParameters().size(); ++i) {
                    if (i < arg_count) {
                        // Copy provided argument
                        registers[i] = registers[pc->b + i + 1];
                    } else {
                        // Initialize missing optional parameter to nullptr (nil)
                        registers[i] = nullptr;
                    }
                }
                
                // Execute function
                execute_lir_function(*func);
                
                // Get return value from register 0 (standard return register)
                auto return_value = registers[0];
                
                // Restore caller's registers
                registers = saved_registers;
                
                // Set return value in destination register
                registers[pc->dst] = return_value;
                
                DISPATCH();
            }
        }
        
        // Function not found
        registers[pc->dst] = nullptr;
        DISPATCH();
    }

OP_PRINTINT:
    std::cout << to_int(registers[pc->a]) << std::endl;
    DISPATCH();

OP_PRINTUINT:
    std::cout << to_uint(registers[pc->a]) << std::endl;
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

        if (context_id < task_contexts.size()) {
            auto& ctx = task_contexts[context_id];
            ctx->fields[field_index] = field_value;

            if (field_index == 2) {
                ctx->channel_ptr = field_value;
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
                    shared_variables["shared_counter"].store(updated_counter);
                }

                if (!std::holds_alternative<std::nullptr_t>(task->channel_ptr)) {
                    uint64_t channel_id = static_cast<uint64_t>(to_int(task->channel_ptr));
                    int64_t new_counter_value = shared_variables["shared_counter"].load();

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
    {
        // Parse error information from instruction comment
        std::string errorType = "DefaultError";
        std::string errorMessage = "Operation failed";
        
        // Check if the current instruction has error info in the comment
        if (!pc->comment.empty() && pc->comment.find("ERROR_INFO:") == 0) {
            // Parse format: "ERROR_INFO:ErrorType:Error message"
            std::string info = pc->comment.substr(11); // Skip "ERROR_INFO:"
            size_t colon_pos = info.find(':');
            if (colon_pos != std::string::npos) {
                errorType = info.substr(0, colon_pos);
                errorMessage = info.substr(colon_pos + 1);
            }
        }
        
        // Create an error ID using a tagged integer approach
        // Error IDs are negative numbers starting from -1000000 to avoid conflicts
        static int64_t next_error_id = -1000000;
        int64_t error_id = next_error_id--;
        
        // Store error information in our error table
        ErrorInfo error_info;
        error_info.errorType = errorType;
        error_info.message = errorMessage;
        error_info.isError = true;
        error_table[error_id] = error_info;
        
        // Store the error ID in the register (primitive int64_t)
        registers[pc->dst] = error_id;
    }
    DISPATCH();

OP_CONSTRUCTOK:
    {
        // For success values, just pass through the original value
        // The type system at the LIR level knows this is wrapped in ErrorUnion
        registers[pc->dst] = registers[pc->a];
        
        // Clear any error information for this register
        // (in case it was previously an error)
        auto reg_value = registers[pc->a];
        if (std::holds_alternative<int64_t>(reg_value)) {
            int64_t value = std::get<int64_t>(reg_value);
            if (value <= -1000000) {
                error_table.erase(value);
            }
        }
    }
    DISPATCH();

OP_ISERROR:
    {
        // Check if the value is an error using our proper error detection
        bool is_error = isErrorValue(pc->a);
        registers[pc->dst] = is_error;
    }
    DISPATCH();

OP_UNWRAP:
    {
        auto& value = registers[pc->a];
        
        // Check if it's an error value using proper error detection
        if (isErrorValue(pc->a)) {
            // Error case - this should panic in a real implementation
            std::cerr << "Runtime Error: Attempted to unwrap an error value" << std::endl;
            
            // Get the actual error message from error table
            if (std::holds_alternative<int64_t>(value)) {
                int64_t error_id = std::get<int64_t>(value);
                auto it = error_table.find(error_id);
                if (it != error_table.end()) {
                    std::cerr << "Error details: " << it->second.errorType << " - " << it->second.message << std::endl;
                }
            }
            
            // Legacy error storage check
            auto legacy_it = error_storage.find(pc->a);
            if (legacy_it != error_storage.end()) {
                std::cerr << "Error details: " << legacy_it->second->errorType << " - " << legacy_it->second->message << std::endl;
            }
            
            registers[pc->dst] = nullptr;
        } else {
            // Success case - unwrap the value (just pass it through)
            registers[pc->dst] = value;
        }
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
        
        default_atomic.store(0);
        
        for (auto& queue : work_queues) {
            while (!queue.empty()) {
                uint64_t task_context = queue.front();
                queue.pop();
                
                if (task_context < task_contexts.size()) {
                    auto& task = task_contexts[task_context];
                    if (task->state == TaskState::RUNNING || task->state == TaskState::INIT) {
                        if (task->body_start_pc >= 0 && task->body_end_pc >= 0) {
                            execute_task_body(task.get(), *current_function_);
                        }
                        
                        task->state = TaskState::COMPLETED;
                    }
                }
            }
        }
        
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
    // Set up task context parameters
    if (task) {
        // Set loop variable value from task context field 1
        auto loop_var_it = task->fields.find(1);
        if (loop_var_it != task->fields.end()) {
            registers[1] = loop_var_it->second;
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

void RegisterVM::execute_lir_function(const LIR::LIRFunction& function) {
    // Get the instructions from the LIRFunction
    const auto& instructions = function.getInstructions();
    
    // Create a temporary LIR_Function wrapper to reuse existing execution logic
    LIR::LIR_Function temp_wrapper(function.getName(), function.getSignature().parameters.size());
    temp_wrapper.instructions = instructions;
    
    // Execute using the existing method
    execute_function(temp_wrapper);
}

std::string RegisterVM::to_string(const RegisterValue& value) const {
    if (std::holds_alternative<int64_t>(value)) {
        int64_t intValue = std::get<int64_t>(value);
        
        // Check if it's an error ID
        if (intValue <= -1000000) {
            auto it = error_table.find(intValue);
            if (it != error_table.end() && it->second.isError) {
                return "Error(" + it->second.errorType + ": " + it->second.message + ")";
            }
        }
        
        return std::to_string(intValue);
    } else if (std::holds_alternative<uint64_t>(value)) {
        return std::to_string(std::get<uint64_t>(value));
    } else if (std::holds_alternative<double>(value)) {
        return std::to_string(std::get<double>(value));
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? "true" : "false";
    } else if (std::holds_alternative<std::string>(value)) {
        return std::get<std::string>(value);
    }
    return "nil";
}

// Error handling methods implementation
ValuePtr RegisterVM::createErrorValue(const std::string& errorType, const std::string& message) {
    // Create error value using the same approach as the old VM
    ErrorValue errorVal(errorType, message, {}, 0); // No source location for now
    
    // Create error union type
    ErrorUnionType errorUnionDetails;
    errorUnionDetails.successType = type_system->NIL_TYPE;
    errorUnionDetails.errorTypes = {errorType};
    errorUnionDetails.isGenericError = (errorType == "DefaultError");
    
    auto errorUnionType = std::make_shared<Type>(TypeTag::ErrorUnion, errorUnionDetails);
    
    // Create the final value with the error union type
    ValuePtr result = type_system->createValue(errorUnionType);
    result->complexData = errorVal;
    
    return result;
}

ValuePtr RegisterVM::createSuccessValue(const RegisterValue& value) {
    // Convert RegisterValue to ValuePtr
    ValuePtr successValue;
    
    if (std::holds_alternative<int64_t>(value)) {
        successValue = type_system->createValue(type_system->INT64_TYPE);
        successValue->data = std::get<int64_t>(value);
    } else if (std::holds_alternative<double>(value)) {
        successValue = type_system->createValue(type_system->FLOAT64_TYPE);
        successValue->data = std::get<double>(value);
    } else if (std::holds_alternative<bool>(value)) {
        successValue = type_system->createValue(type_system->BOOL_TYPE);
        successValue->data = std::get<bool>(value) ? 1 : 0;
    } else if (std::holds_alternative<std::string>(value)) {
        successValue = type_system->createValue(type_system->STRING_TYPE);
        successValue->data = std::get<std::string>(value);
    } else {
        successValue = type_system->createValue(type_system->NIL_TYPE);
    }
    
    // Create error union type for the success value
    ErrorUnionType errorUnionDetails;
    errorUnionDetails.successType = successValue->type;
    errorUnionDetails.isGenericError = true; // Generic for Type? syntax
    
    auto errorUnionType = std::make_shared<Type>(TypeTag::ErrorUnion, errorUnionDetails);
    
    // Create the union value containing the success value
    ValuePtr result = type_system->createValue(errorUnionType);
    result->data = successValue->data;
    result->complexData = successValue->complexData;
    
    return result;
}

bool RegisterVM::isErrorValue(LIR::Reg reg) const {
    const auto& regValue = registers[reg];
    
    // Check if it's an error ID (negative number in error range)
    if (std::holds_alternative<int64_t>(regValue)) {
        int64_t value = std::get<int64_t>(regValue);
        if (value <= -1000000) {
            // Check if this error ID exists in our error table
            auto it = error_table.find(value);
            return it != error_table.end() && it->second.isError;
        }
    }
    
    // Legacy: Check if this register contains an error value in error storage
    auto it = error_storage.find(reg);
    if (it != error_storage.end()) {
        return true; // Has stored error
    }
    
    return false;
}

} // namespace Register
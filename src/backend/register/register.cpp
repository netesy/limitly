#include "register.hh"
#include "../../lir/lir.hh"
#include "../../lir/functions.hh"
#include "../../lir/function_registry.hh"
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
    
    // Reset SharedCell operations
    shared_cells.clear();
    
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
    dispatch_table[static_cast<int>(LIR::LIR_Op::ChannelSend)] = &&OP_CHANNEL_SEND;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ChannelOffer)] = &&OP_CHANNEL_OFFER;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ChannelRecv)] = &&OP_CHANNEL_RECV;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ChannelPoll)] = &&OP_CHANNEL_POLL;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ChannelClose)] = &&OP_CHANNEL_CLOSE;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ChannelHasData)] = &&OP_CHANNEL_HAS_DATA;
    dispatch_table[static_cast<int>(LIR::LIR_Op::SchedulerInit)] = &&OP_SCHEDULER_INIT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::SchedulerRun)] = &&OP_SCHEDULER_RUN;
    dispatch_table[static_cast<int>(LIR::LIR_Op::SchedulerTick)] = &&OP_SCHEDULER_TICK;
    dispatch_table[static_cast<int>(LIR::LIR_Op::SchedulerAddTask)] = &&OP_SCHEDULER_ADD_TASK;
    dispatch_table[static_cast<int>(LIR::LIR_Op::GetTickCount)] = &&OP_GET_TICK_COUNT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::DelayUntil)] = &&OP_DELAY_UNTIL;
    
    // Parallel execution operations
    dispatch_table[static_cast<int>(LIR::LIR_Op::ParallelInit)] = &&OP_PARALLEL_INIT;
    dispatch_table[static_cast<int>(LIR::LIR_Op::ParallelSync)] = &&OP_PARALLEL_SYNC;
    
    // SharedCell operations
    dispatch_table[static_cast<int>(LIR::LIR_Op::SharedCellAlloc)] = &&OP_SHARED_CELL_ALLOC;
    dispatch_table[static_cast<int>(LIR::LIR_Op::SharedCellLoad)] = &&OP_SHARED_CELL_LOAD;
    dispatch_table[static_cast<int>(LIR::LIR_Op::SharedCellStore)] = &&OP_SHARED_CELL_STORE;
    dispatch_table[static_cast<int>(LIR::LIR_Op::SharedCellAdd)] = &&OP_SHARED_CELL_ADD;
    dispatch_table[static_cast<int>(LIR::LIR_Op::SharedCellSub)] = &&OP_SHARED_CELL_SUB;
    
    // Additional missing operations
    // dispatch_table[static_cast<int>(LIR::LIR_Op::CallVoid)] = &&OP_CALLVOID;
    // dispatch_table[static_cast<int>(LIR::LIR_Op::CallIndirect)] = &&OP_CALLINDIRECT;
    // dispatch_table[static_cast<int>(LIR::LIR_Op::CallBuiltin)] = &&OP_CALLBUILTIN;
    // dispatch_table[static_cast<int>(LIR::LIR_Op::CallVariadic)] = &&OP_CALLVARIADIC;
    // dispatch_table[static_cast<int>(LIR::LIR_Op::VaStart)] = &&OP_VASTART;
    // dispatch_table[static_cast<int>(LIR::LIR_Op::VaArg)] = &&OP_VAARG;
    // dispatch_table[static_cast<int>(LIR::LIR_Op::VaEnd)] = &&OP_VAEND;
    // dispatch_table[static_cast<int>(LIR::LIR_Op::Copy)] = &&OP_COPY;
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
    
    std::string func_name;
    std::vector<ValuePtr> args;
    int64_t func_index;
    int arg_count;
    auto saved_registers = registers;
    auto saved_pc = pc;
    RegisterValue return_value;
    LIR::LIRFunction temp_wrapper(function.getName(), function.getParameters(), std::nullopt, LIR::LIRFunctionBody(function.getInstructions())); // Fix LIRFunction constructor call
    std::vector<std::string> builtin_names;
    std::vector<std::string> function_names;
    std::shared_ptr<LIR::LIRFunction> func;
    
    TaskContext* ctx = nullptr; // Add missing ctx variable
    uint64_t count;
    uint64_t start_context_id;
    uint64_t context_id;
    uint64_t channel_id;
    int field_index;
    RegisterValue field_value;
    size_t capacity;
    bool success;
    RegisterValue value;
    TaskState new_state;
    uint64_t target_time;
    std::string format;
    std::string arg;
    size_t pos;
    std::shared_ptr<LIR::LIRFunction> task_func;
    std::string task_func_name;
    std::unordered_map<int, RegisterValue>::iterator func_name_it;
    std::unordered_map<int, RegisterValue>::iterator loop_var_it;
    std::unordered_map<int, RegisterValue>::iterator channel_it;
    auto& func_manager = LIR::LIRFunctionManager::getInstance();
    auto& func_registry = LIR::FunctionRegistry::getInstance();
    auto& scheduler_ref = scheduler;
    std::vector<RegisterValue> saved_registers_task;
    const LIR::LIR_Function* saved_function_task = nullptr;
    std::shared_ptr<TaskContext> ctx_task;
    std::unordered_map<int, RegisterValue>::iterator it;
    std::unique_ptr<Channel> channel;
    std::unique_ptr<Scheduler> scheduler_ptr;
    
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
            func_name = pc->func_name;
            const auto& arg_regs = pc->call_args;
        
        //std::cout << "[DEBUG] New format call to '" << func_name << "' with " << arg_regs.size() << " arguments" << std::endl;
        
        // First try builtin functions
        if (LIR::BuiltinUtils::isBuiltinFunction(func_name)) {
            // Collect arguments from the specified registers
            args.clear();
            
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
            func = func_manager.getFunction(func_name);
            
            if (func) {
                //std::cout << "[DEBUG] Calling user function '" << func_name << "' with " << arg_regs.size() << " arguments" << std::endl;
                
                // Save current context
                saved_registers = registers;
                
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
                LIR::LIRFunction temp_wrapper(func->getName(), func->getParameters().size());
                temp_wrapper.instructions = func->getInstructions();
                execute_instructions(temp_wrapper, 0, func->getInstructions().size());
                
                // Get return value from register 0 (standard return register)
                return_value = registers[0];
              
              
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
    
      
    // Function not found
    std::cerr << "Error: Function '" << func_name << "' not found" << std::endl;
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
    count = static_cast<uint64_t>(pc->a);  // Read count from immediate value in 'a' field
    start_context_id = task_contexts.size();
    
    std::cout << "[DEBUG] OP_TASK_CONTEXT_ALLOC called with count: " << count << std::endl;
    std::cout << "[DEBUG] Starting context ID: " << start_context_id << std::endl;
    
    for (uint64_t i = 0; i < count; i++) {
        auto task_ctx = std::make_unique<TaskContext>();
        task_contexts.push_back(std::move(task_ctx));
        std::cout << "[DEBUG] Created task context " << (start_context_id + i) << std::endl;
    }
    
    std::cout << "[DEBUG] Total task_contexts.size(): " << task_contexts.size() << std::endl;
    registers[pc->dst] = static_cast<int64_t>(start_context_id);
}
DISPATCH();

OP_TASK_CONTEXT_INIT:
{
    uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
    if (context_id < task_contexts.size()) {
        ctx = task_contexts[context_id].get();
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
    if (context_id < scheduler->fibers.size()) {
        registers[pc->dst] = static_cast<int64_t>(scheduler->fibers[context_id]->state);
    } else {
        registers[pc->dst] = static_cast<int64_t>(TaskState::INIT);
    }
}
DISPATCH();

OP_TASK_SET_STATE:
{
    uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
    TaskState new_state = static_cast<TaskState>(to_int(registers[pc->b]));
    if (context_id < scheduler->fibers.size()) {
        scheduler->fibers[context_id]->state = static_cast<FiberState>(new_state);
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
    }

    std::cout << "[DEBUG] TaskSetField: context_id=" << context_id << " field_index=" << field_index << " imm=" << pc->imm << " value_reg=" << pc->dst << std::endl;

    if (context_id < scheduler->fibers.size()) {
        auto& fiber = scheduler->fibers[context_id];
        fiber->task_context->fields[field_index] = field_value;

        // Note: Fiber doesn't have channel_ptr or counter members
        // These would need to be added to Fiber struct if needed
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
    if (context_id < scheduler->fibers.size()) {
        auto it = scheduler->fibers[context_id]->task_context->fields.find(field_index);
        if (it != scheduler->fibers[context_id]->task_context->fields.end()) {
            registers[pc->dst] = it->second;
        } else {
            registers[pc->dst] = static_cast<int64_t>(0);
        }
    }
}  
    DISPATCH();

OP_CHANNEL_ALLOC:
    {
        size_t capacity = static_cast<size_t>(to_int(registers[pc->a]));
        if (capacity == 0) capacity = 32;
        channel = std::make_unique<Channel>(capacity);
        uint64_t channel_id = channels.size();
        channels.push_back(std::move(channel));
        registers[pc->dst] = static_cast<int64_t>(channel_id);
    }
    DISPATCH();

OP_CHANNEL_SEND:
    {
        uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        RegisterValue value = registers[pc->b];
        if (channel_id < channels.size()) {
            // For now, use non-blocking offer. TODO: Implement proper blocking send with fiber suspension
            bool success = channels[channel_id]->offer(value);
            registers[pc->dst] = static_cast<int64_t>(success ? 1 : 0);
    } else {
        registers[pc->dst] = static_cast<int64_t>(0);
    }
}
DISPATCH();

OP_CHANNEL_OFFER:
    {
        uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        RegisterValue value = registers[pc->b];
        if (channel_id < channels.size()) {
            bool success = channels[channel_id]->offer(value);
            registers[pc->dst] = static_cast<int64_t>(success ? 1 : 0);
        } else {
            registers[pc->dst] = static_cast<int64_t>(0);
        }
    }
    DISPATCH();

OP_CHANNEL_RECV:
    {
        uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        if (channel_id < channels.size()) {
            // For now, use non-blocking poll. TODO: Implement proper blocking recv with fiber suspension
            RegisterValue value;
            bool success = channels[channel_id]->poll(value);
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

OP_CHANNEL_POLL:
    {
        uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        if (channel_id < channels.size()) {
            RegisterValue value;
            bool success = channels[channel_id]->poll(value);
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

OP_CHANNEL_CLOSE:
    {
        uint64_t channel_id = static_cast<uint64_t>(to_int(registers[pc->a]));
        if (channel_id < channels.size()) {
            channels[channel_id]->close();
            registers[pc->dst] = static_cast<int64_t>(1);
        } else {
            registers[pc->dst] = static_cast<int64_t>(0);
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
    std::cout << "[DEBUG] Scheduler initialized" << std::endl;
    registers[pc->dst] = static_cast<int64_t>(1);
    DISPATCH();

OP_SCHEDULER_ADD_TASK:
{
    uint64_t context_id = static_cast<uint64_t>(to_int(registers[pc->a]));
    std::cout << "[DEBUG] OP_SCHEDULER_ADD_TASK called with context_id: " << context_id << std::endl;
    std::cout << "[DEBUG] task_contexts.size(): " << task_contexts.size() << std::endl;

    if (context_id < task_contexts.size()) {
        ctx = task_contexts[context_id].get();
        if (ctx) {
            // Copy task context to the scheduler
            scheduler->add_fiber(std::make_unique<TaskContext>(*ctx));
            std::cout << "[DEBUG] Added task " << context_id << " to scheduler" << std::endl;
            std::cout << "[DEBUG] Scheduler now has " << scheduler->fibers.size() << " tasks" << std::endl;
            registers[pc->dst] = static_cast<int64_t>(1);
        } else {
            std::cout << "[DEBUG] Task context " << context_id << " is null" << std::endl;
            registers[pc->dst] = static_cast<int64_t>(0);
        }
    } else {
        std::cout << "[DEBUG] Context ID " << context_id << " out of range (max: " << task_contexts.size() - 1 << ")" << std::endl;
        registers[pc->dst] = static_cast<int64_t>(0);
    }
}
DISPATCH();

OP_SCHEDULER_RUN:
{
    std::cout << "[DEBUG] Scheduler running with " << scheduler->fibers.size() << " tasks" << std::endl;

    // Execute all running tasks (they should already be in scheduler via OP_SCHEDULER_ADD_TASK)
    for (size_t i = 0; i < scheduler->fibers.size(); ++i) {
        auto& fiber = scheduler->fibers[i];

        if (fiber->state == FiberState::CREATED) {
            fiber->state = FiberState::RUNNING;
        }

        if (fiber->state == FiberState::RUNNING) {
            std::cout << "[DEBUG] Executing task " << (fiber->fiber_id + 1) << std::endl;

            // Get task function name from task context field 4
            auto func_name_it = fiber->task_context->fields.find(4);
            if (func_name_it == fiber->task_context->fields.end()) {
                std::cerr << "[ERROR] Task function name not found in task context" << std::endl;
                fiber->state = FiberState::COMPLETED;
                continue;
            }

            // Extract function name from register value
            std::string task_func_name;
            if (std::holds_alternative<std::string>(func_name_it->second)) {
                task_func_name = std::get<std::string>(func_name_it->second);
            } else {
                std::cerr << "[ERROR] Task function name is not a string" << std::endl;
                fiber->state = FiberState::COMPLETED;
                continue;
            }

            // Get task function from registry
            auto& func_registry = LIR::FunctionRegistry::getInstance();
            LIR::LIR_Function* task_func = func_registry.getFunction(task_func_name);
            if (!task_func) {
                std::cerr << "[ERROR] Task function '" << task_func_name << "' not found in registry" << std::endl;
                fiber->state = FiberState::COMPLETED;
                continue;
            }

            std::cout << "Task " << (fiber->fiber_id + 1) << " calling function: " << task_func_name << std::endl;

            // Save current register state
            auto saved_registers = registers;

            // Initialize a fresh register context for this task
            registers.clear();
            registers.resize(1024);
            for (auto& reg : registers) {
                reg = nullptr;
            }

            // Set up task context parameters in fresh register space
            if (fiber) {
                // Set task ID from task context field 0
                auto task_id_it = fiber->task_context->fields.find(0);
                if (task_id_it != fiber->task_context->fields.end()) {
                    registers[0] = task_id_it->second;
                }

                // Set loop variable value from task context field 1
                auto loop_var_it = fiber->task_context->fields.find(1);
                if (loop_var_it != fiber->task_context->fields.end()) {
                    registers[1] = loop_var_it->second;
                }

                // Set channel from task context field 2
                auto channel_it = fiber->task_context->fields.find(2);
                if (channel_it != fiber->task_context->fields.end()) {
                    registers[2] = channel_it->second;
                }
            }

            // Execute task function
            current_function_ = task_func;
            execute_instructions(*task_func, 0, task_func->instructions.size());
                
                // Restore register state and current function
                registers = saved_registers;
                current_function_ = nullptr;
                
                fiber->state = FiberState::COMPLETED;
                std::cout << "[DEBUG] Task " << (fiber->fiber_id + 1) << " completed" << std::endl;
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

// ============ PARALLEL EXECUTION OPERATIONS ============

OP_PARALLEL_INIT:
    {
        // Initialize parallel execution context
        // For now, just return success (1)
        // In a real implementation, this would set up worker threads
        std::cout << "[DEBUG] Parallel execution initialized" << std::endl;
        registers[pc->dst] = static_cast<int64_t>(1);
    }
    DISPATCH();

OP_PARALLEL_SYNC:
    {
        // Synchronize and complete parallel execution
        // For now, just return success (1)
        // In a real implementation, this would wait for all workers to complete
        std::cout << "[DEBUG] Parallel execution synchronized" << std::endl;
        registers[pc->dst] = static_cast<int64_t>(1);
    }
    DISPATCH();

// ============ SHARED CELL OPERATIONS ============

OP_SHARED_CELL_ALLOC:
    {
        // Allocate a new SharedCell ID
        // For now, use a simple incrementing ID
        static uint32_t next_cell_id = 1;
        uint32_t cell_id = next_cell_id++;
        
        // Initialize SharedCell with value 0
        shared_cells[cell_id] = std::make_unique<SharedCell>(cell_id, 0);
        
        std::cout << "[DEBUG] Allocated SharedCell ID " << cell_id << std::endl;
        registers[pc->dst] = static_cast<int64_t>(cell_id);
    }
    DISPATCH();

OP_SHARED_CELL_LOAD:
    {
        // Load value from SharedCell: dst = shared_cells[cell_id].value
        uint32_t cell_id = static_cast<uint32_t>(to_int(registers[pc->a]));
        
        if (shared_cells.find(cell_id) != shared_cells.end()) {
            int64_t value = shared_cells[cell_id]->value.load();
            registers[pc->dst] = value;
            std::cout << "[DEBUG] Loaded " << value << " from SharedCell " << cell_id << std::endl;
        } else {
            std::cerr << "[ERROR] SharedCell ID " << cell_id << " not found" << std::endl;
            registers[pc->dst] = static_cast<int64_t>(0);
        }
    }
    DISPATCH();

OP_SHARED_CELL_STORE:
    {
        // Store value to SharedCell: shared_cells[cell_id].value = src
        uint32_t cell_id = static_cast<uint32_t>(to_int(registers[pc->a]));
        int64_t value = to_int(registers[pc->b]);
        
        if (shared_cells.find(cell_id) != shared_cells.end()) {
            shared_cells[cell_id]->value.store(value);
            std::cout << "[DEBUG] Stored " << value << " to SharedCell " << cell_id << std::endl;
            registers[pc->dst] = value;
        } else {
            std::cerr << "[ERROR] SharedCell ID " << cell_id << " not found" << std::endl;
            registers[pc->dst] = static_cast<int64_t>(0);
        }
    }
    DISPATCH();

OP_SHARED_CELL_ADD:
    {
        // Atomic add to SharedCell: shared_cells[cell_id].value += src
        uint32_t cell_id = static_cast<uint32_t>(to_int(registers[pc->a]));
        int64_t value = to_int(registers[pc->b]);
        
        if (shared_cells.find(cell_id) != shared_cells.end()) {
            int64_t old_value = shared_cells[cell_id]->value.fetch_add(value);
            int64_t new_value = old_value + value;
            std::cout << "[DEBUG] Added " << value << " to SharedCell " << cell_id 
                      << " (old: " << old_value << ", new: " << new_value << ")" << std::endl;
            registers[pc->dst] = new_value;
        } else {
            std::cerr << "[ERROR] SharedCell ID " << cell_id << " not found" << std::endl;
            registers[pc->dst] = static_cast<int64_t>(0);
        }
    }
    DISPATCH();

OP_SHARED_CELL_SUB:
    {
        // Atomic sub from SharedCell: shared_cells[cell_id].value -= src
        uint32_t cell_id = static_cast<uint32_t>(to_int(registers[pc->a]));
        int64_t value = to_int(registers[pc->b]);
        
        if (shared_cells.find(cell_id) != shared_cells.end()) {
            int64_t old_value = shared_cells[cell_id]->value.fetch_sub(value);
            int64_t new_value = old_value - value;
            std::cout << "[DEBUG] Subtracted " << value << " from SharedCell " << cell_id 
                      << " (old: " << old_value << ", new: " << new_value << ")" << std::endl;
            registers[pc->dst] = new_value;
        } else {
            std::cerr << "[ERROR] SharedCell ID " << cell_id << " not found" << std::endl;
            registers[pc->dst] = static_cast<int64_t>(0);
        }
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
  
    #undef DISPATCH
    #undef DISPATCH_JUMP
}

void RegisterVM::execute_task_body(TaskContext* task, const LIR::LIR_Function& function) {
    // Get the task function name from task context field 4
    auto func_name_it = task->fields.find(4);
    if (func_name_it == task->fields.end()) {
        std::cerr << "Error: Task function name not found in task context" << std::endl;
        return;
    }
    
    // Extract function name from register value
    std::string task_func_name;
    if (std::holds_alternative<std::string>(func_name_it->second)) {
        task_func_name = std::get<std::string>(func_name_it->second);
    } else {
        std::cerr << "Error: Task function name is not a string" << std::endl;
        return;
    }
    
    // Get the task function from the registry
    auto& func_registry = LIR::FunctionRegistry::getInstance();
    LIR::LIR_Function* task_func = func_registry.getFunction(task_func_name);
    if (!task_func) {
        std::cerr << "Error: Task function '" << task_func_name << "' not found in registry" << std::endl;
        return;
    }
    
    std::cout << "Task " << (task->task_id + 1) << " calling function: " << task_func_name << std::endl;
    
    // Save current register state
    auto saved_registers = registers;
    
    // Initialize a fresh register context for this task
    registers.clear();
    registers.resize(1024);
    for (auto& reg : registers) {
        reg = nullptr;
    }
    
    // Set up task context parameters in the fresh register space
    if (task) {
        // Set task ID from task context field 0
        auto task_id_it = task->fields.find(0);
        if (task_id_it != task->fields.end()) {
            registers[0] = task_id_it->second;
        }
        
        // Set loop variable value from task context field 1
        auto loop_var_it = task->fields.find(1);
        if (loop_var_it != task->fields.end()) {
            registers[1] = loop_var_it->second;
        }
        
        // Set channel from task context field 2
        auto channel_it = task->fields.find(2);
        if (channel_it != task->fields.end()) {
            registers[2] = channel_it->second;
        }
        
        // Initialize shared counter with current global value
        int64_t current_shared_counter = shared_variables["shared_counter"].load();
        registers[3] = current_shared_counter;
        
        std::cout << "Task " << (task->task_id + 1) << " starting with shared counter = " << current_shared_counter << std::endl;
    }
    
    // Execute the task function using the shared instruction executor
    execute_instructions(*task_func, 0, task_func->instructions.size());
    
    // Update the shared counter with the task's result
    if (std::holds_alternative<int64_t>(registers[3])) {
        int64_t new_counter_value = std::get<int64_t>(registers[3]);
        shared_variables["shared_counter"].store(new_counter_value);
        std::cout << "Task " << (task->task_id + 1) << " updated shared counter to " << new_counter_value << std::endl;
    }
    
    // Preserve the task result (register 3 contains the updated counter)
    auto task_result = registers[3];
    
    // Restore the original register state
    registers = saved_registers;
    
    // Store the task result back in register 3 for the scheduler to read
    registers[3] = task_result;
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
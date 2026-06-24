#include "frontend/value.hh"
#ifndef LIR_H
#define LIR_H

#include <vector>
#include <string>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "../backend/value.hh"
#include "../backend/types.hh"

namespace LM {
namespace LIR {

using Reg = uint32_t;
using Imm = uint32_t;

enum class Type : uint8_t {
    I8, U8, I16, U16, I32, U32, I64, U64, F32, F64, Bool, Ptr, Void
};
std::string type_to_string(Type type);

// === Metadata Encoding for Generic Operations ===
// Used to encode type information and calling conventions in the 'imm' field

namespace Metadata {
    // Marshal type encoding: source and target types for data conversions
    enum class MarshalType : uint16_t {
        StringToCString  = 0,
        CStringToString  = 1,
        PtrToBuffer      = 2,
        BufferToPtr      = 3,
        IntToFloat       = 4,
        FloatToInt       = 5,
        // Expand as needed for other conversions
    };
    
    inline uint32_t make_marshal_imm(MarshalType type) {
        return static_cast<uint32_t>(type);
    }
    
    inline MarshalType extract_marshal_type(uint32_t imm) {
        return static_cast<MarshalType>(imm & 0xFFFF);
    }
    
    // Calling convention encoding for ForeignCall operations
    enum class CallingConvention : uint8_t {
        SystemV_x64      = 0,    // System V AMD64 ABI (Linux/BSD)
        Windows_x64      = 1,    // Windows x64 calling convention
        ARM64_EABI       = 2,    // ARM64 EABI
        Default          = SystemV_x64,
    };
    
    inline uint32_t make_calling_convention_imm(CallingConvention cc) {
        return static_cast<uint32_t>(cc);
    }
    
    inline CallingConvention extract_calling_convention(uint32_t imm) {
        return static_cast<CallingConvention>(imm & 0xFF);
    }
}

// NOTE: This enum must stay in sync with the mirror in
// src/backend/vm/resource_types.hh
enum class ResourceType : uint32_t {
    FILE = 0, SOCKET = 1, WINDOW = 2, SURFACE = 3, PROCESS = 4, CHANNEL = 5,
    TIMER = 6, TASK = 7, LIBRARY = 8, STDOUT = 9, STDERR = 10, MEMORY = 11,
    ENTROPY = 12, DNS_RESOLVER = 13, UDP_SOCKET = 14, WEBSOCKET = 15, HASH_ENGINE = 16
};

enum class ResourceOperation : uint32_t {
    OPEN = 0, CLOSE = 1, READ = 2, WRITE = 3, SEND = 4, RECEIVE = 5,
    CONNECT = 6, DRAW_RECT = 7, DRAW_TEXT = 8, SPAWN = 9, POLL = 10,
    PUSH = 11, POP = 12, GET_STATE = 13, SET_STATE = 14, COPY = 15,
    FILL = 16, COMPARE = 17, ADD_PTR = 18, SUB_PTR = 19, PTR_DIFF = 20,
    ALIGN_PTR = 21, IS_ALIGNED = 22, BIND = 23, LISTEN = 24, ACCEPT = 25,
    RESOLVE = 26, SEND_TO = 27, RECV_FROM = 28
};

enum class LIR_Op : uint8_t {
    // === Core Operations ===
    Mov, LoadConst, Add, Sub, Mul, Div, Mod, Neg, And, Or, Xor, Shl, Shr,
    CmpEQ, CmpNEQ, CmpLT, CmpLE, CmpGT, CmpGE, StringIndex,
    Jump, JumpIfFalse, JumpIf, Label,
    Call, CallVoid, CallIndirect, CallBuiltin, CallVariadic,
    Return, FuncDef, Param, Ret, VaStart, VaArg, VaEnd, Copy,
    PrintInt, PrintUint, PrintFloat, PrintBool, PrintString,
    Nop, Load, Store, Cast, ToString, STR_CONCAT, STR_FORMAT,
    
    // === Decimal Operations ===
    DecAdd, DecSub, DecMul, DecDiv, DecMod, DecNeg, DecRescale,
    
    // === Error Handling ===
    ConstructError, ConstructOk, IsError, Unwrap, UnwrapOr,
    
    // === Type Operations ===
    MakeEnum, GetTag, GetPayload,
    
    // === Atomic Operations ===
    AtomicLoad, AtomicStore, AtomicFetchAdd,
    
    // === Async Operations ===
    Await, AsyncCall,
    
    // === Concurrency ===
    TaskContextAlloc, TaskContextInit, TaskGetState, TaskSetState, TaskSetField, TaskGetField,
    ChannelAlloc, ChannelPush, ChannelPop, ChannelHasData,
    ChannelSend, ChannelOffer, ChannelRecv, ChannelPoll, ChannelClose,
    SchedulerInit, SchedulerRun, SchedulerTick, SchedulerAddTask,
    GetTickCount, DelayUntil, ParallelInit, ParallelSync,
    
    // === Collections ===
    ListCreate, ListAppend, ListIndex, ListLen,
    DictCreate, DictSet, DictGet, DictHas, DictLen, DictItems,
    TupleCreate, TupleGet, TupleSet, TupleLen,
    
    // === Object-Oriented ===
    NewFrame, FrameGetField, FrameSetField, FrameGetFieldAtomic, FrameSetFieldAtomic,
    FrameFieldAtomicAdd, FrameFieldAtomicSub, FrameCallMethod, FrameCallInit, FrameCallDeinit,
    TraitCallMethod, MakeTraitObject,
    
    // === Module System ===
    ImportModule, ExportSymbol, BeginModule, EndModule, LoadGlobal, StoreGlobal,
    
    // === Shared Memory ===
    SharedCellAlloc, SharedCellLoad, SharedCellStore, SharedCellAdd, SharedCellSub,
    
    // === Legacy Resource Operations (deprecated, kept for compatibility) ===
    ResourceCreate, ResourceDestroy, ResourceCall,
    
    // === REDESIGNED: Memory Operations (generic with type dispatch via result_type) ===
    MemoryAlloc,        // malloc(size)
    MemoryFree,         // free(ptr)
    MemoryResize,       // realloc(ptr, size)
    MemoryLoad,         // Load from memory: result_type controls interpretation
    MemoryStore,        // Store to memory: type_a controls interpretation
    MemoryCopy,         // memcpy(dst, src, size)
    MemoryFill,         // memset(dst, value, size)
    MemoryCompare,      // memcmp(lhs, rhs, size) -> result
    
    // === REDESIGNED: Pointer Operations (renamed from FFI*Ptr) ===
    PtrAdd,             // ptr + offset
    PtrSub,             // ptr - offset
    PtrDiff,            // ptr1 - ptr2
    PtrAlign,           // align_to(ptr, alignment)
    PtrIsAligned,       // (ptr % alignment) == 0 ? true : false
    
    // === REDESIGNED: Marshaling Operations (data conversions) ===
    Marshal,            // Convert value (from_type, to_type in imm field)
    Unmarshal,          // Reverse conversion (to_type, from_type in imm field)
    BufferView,         // Create buffer view of memory range
    BufferCreate,       // Allocate new buffer
    BufferResize,       // Resize existing buffer
    
    // === REDESIGNED: Dynamic Linking (genuine C boundary crossing) ===
    LibraryLoad,        // dlopen(path)
    LibraryUnload,      // dlclose(handle)
    LibrarySymbol,      // dlsym(handle, symbol)
    
    // === REDESIGNED: Foreign Calls (generic with args in call_args vector) ===
    ForeignCall,        // Indirect: call function pointer with args
    ForeignCallDirect,  // Direct: call known function (func_name field)
    
    // === REDESIGNED: Callbacks (genuine C boundary crossing) ===
    CallbackCreate,     // Create callback wrapper returning callback ID
    CallbackDestroy,    // Destroy callback wrapper
    
    // === DEPRECATED: Old type-specific FFI opcodes (kept for compatibility during migration) ===
    // Do NOT use these - they will be removed after Phase 4 testing
    FFIAlloc, FFIFree, FFIRealloc, FFIMemcpy, FFIMemset, FFIMemcmp,
    FFIAddPtr, FFISubPtr, FFIPtrDiff, FFIAlignPtr, FFIIsAligned,
    FFILoadInt8, FFILoadUInt8, FFILoadInt16, FFILoadUInt16, FFILoadInt32, FFILoadUInt32,
    FFILoadInt64, FFILoadUInt64, FFILoadFloat, FFILoadDouble, FFILoadPtr,
    FFIStoreInt8, FFIStoreUInt8, FFIStoreInt16, FFIStoreUInt16, FFIStoreInt32, FFIStoreUInt32,
    FFIStoreInt64, FFIStoreUInt64, FFIStoreFloat, FFIStoreDouble, FFIStorePtr,
    FFIToCString, FFIFromCString, FFIFreeCString, FFICStringPtr, FFICStringFromPtr,
    FFIBufferAlloc, FFIBufferFromPtr, FFIBufferFree, FFIBufferResize, FFIBufferRead, FFIBufferWrite,
    FFIBufferSize, FFIBufferCapacity, FFIBufferAsPtr,
    FFICallPtr, FFICallPtr0, FFICallPtr1, FFICallPtr2, FFICallPtr3, FFICallPtr4, FFICallPtr5,
    FFILibraryLoad, FFILibraryUnload, FFILibraryGetSymbol,
    FFIRegisterCallback, FFIUnregisterCallback, FFIGetCallbackPtr,
    FFICCallFrameCreate, FFICCallFrameDestroy, FFICCallFrameSetReg, FFICCallFrameGetReg,
    FFICCallFrameSetStackArg, FFICCallFrameGetStackArg,
    FFIVMSave, FFIVMRestore, FFICCallExecute,
    FFICalcStructLayout, FFIGetABIInfo
};

// ============================================================================
// LIR_OP_LIST — X-macro enumerating every opcode in `LIR_Op`, in declaration
// order.  Used to derive `lir_op_to_string()` and any other per-opcode tables
// without risking the "unknown opcode" fall-through that plagues hand-written
// switch statements.
//
// To use:
//   #define X(name) ...
//   LIR_OP_LIST(X)
//   #undef X
//
// IMPORTANT: keep this list in lock-step with the enum above.
// ============================================================================
#define LIR_OP_LIST(X) \
    /* === Core Operations === */ \
    X(Mov) X(LoadConst) X(Add) X(Sub) X(Mul) X(Div) X(Mod) X(Neg) \
    X(And) X(Or) X(Xor) X(Shl) X(Shr) \
    X(CmpEQ) X(CmpNEQ) X(CmpLT) X(CmpLE) X(CmpGT) X(CmpGE) X(StringIndex) \
    X(Jump) X(JumpIfFalse) X(JumpIf) X(Label) \
    X(Call) X(CallVoid) X(CallIndirect) X(CallBuiltin) X(CallVariadic) \
    X(Return) X(FuncDef) X(Param) X(Ret) \
    X(VaStart) X(VaArg) X(VaEnd) X(Copy) \
    X(PrintInt) X(PrintUint) X(PrintFloat) X(PrintBool) X(PrintString) \
    X(Nop) X(Load) X(Store) X(Cast) X(ToString) X(STR_CONCAT) X(STR_FORMAT) \
    /* === Decimal Operations === */ \
    X(DecAdd) X(DecSub) X(DecMul) X(DecDiv) X(DecMod) X(DecNeg) X(DecRescale) \
    /* === Error Handling === */ \
    X(ConstructError) X(ConstructOk) X(IsError) X(Unwrap) X(UnwrapOr) \
    /* === Type Operations === */ \
    X(MakeEnum) X(GetTag) X(GetPayload) \
    /* === Atomic Operations === */ \
    X(AtomicLoad) X(AtomicStore) X(AtomicFetchAdd) \
    /* === Async Operations === */ \
    X(Await) X(AsyncCall) \
    /* === Concurrency === */ \
    X(TaskContextAlloc) X(TaskContextInit) X(TaskGetState) X(TaskSetState) \
    X(TaskSetField) X(TaskGetField) \
    X(ChannelAlloc) X(ChannelPush) X(ChannelPop) X(ChannelHasData) \
    X(ChannelSend) X(ChannelOffer) X(ChannelRecv) X(ChannelPoll) X(ChannelClose) \
    X(SchedulerInit) X(SchedulerRun) X(SchedulerTick) X(SchedulerAddTask) \
    X(GetTickCount) X(DelayUntil) X(ParallelInit) X(ParallelSync) \
    /* === Collections === */ \
    X(ListCreate) X(ListAppend) X(ListIndex) X(ListLen) \
    X(DictCreate) X(DictSet) X(DictGet) X(DictHas) X(DictLen) X(DictItems) \
    X(TupleCreate) X(TupleGet) X(TupleSet) X(TupleLen) \
    /* === Object-Oriented === */ \
    X(NewFrame) X(FrameGetField) X(FrameSetField) \
    X(FrameGetFieldAtomic) X(FrameSetFieldAtomic) \
    X(FrameFieldAtomicAdd) X(FrameFieldAtomicSub) \
    X(FrameCallMethod) X(FrameCallInit) X(FrameCallDeinit) \
    X(TraitCallMethod) X(MakeTraitObject) \
    /* === Module System === */ \
    X(ImportModule) X(ExportSymbol) X(BeginModule) X(EndModule) \
    X(LoadGlobal) X(StoreGlobal) \
    /* === Shared Memory === */ \
    X(SharedCellAlloc) X(SharedCellLoad) X(SharedCellStore) \
    X(SharedCellAdd) X(SharedCellSub) \
    /* === Legacy Resource Operations (deprecated, kept for compatibility) === */ \
    X(ResourceCreate) X(ResourceDestroy) X(ResourceCall) \
    /* === REDESIGNED: Memory Operations === */ \
    X(MemoryAlloc) X(MemoryFree) X(MemoryResize) \
    X(MemoryLoad) X(MemoryStore) X(MemoryCopy) X(MemoryFill) X(MemoryCompare) \
    /* === REDESIGNED: Pointer Operations === */ \
    X(PtrAdd) X(PtrSub) X(PtrDiff) X(PtrAlign) X(PtrIsAligned) \
    /* === REDESIGNED: Marshaling Operations === */ \
    X(Marshal) X(Unmarshal) X(BufferView) X(BufferCreate) X(BufferResize) \
    /* === REDESIGNED: Dynamic Linking === */ \
    X(LibraryLoad) X(LibraryUnload) X(LibrarySymbol) \
    /* === REDESIGNED: Foreign Calls === */ \
    X(ForeignCall) X(ForeignCallDirect) \
    /* === REDESIGNED: Callbacks === */ \
    X(CallbackCreate) X(CallbackDestroy) \
    /* === DEPRECATED: Old type-specific FFI opcodes (kept during migration) === */ \
    X(FFIAlloc) X(FFIFree) X(FFIRealloc) X(FFIMemcpy) X(FFIMemset) X(FFIMemcmp) \
    X(FFIAddPtr) X(FFISubPtr) X(FFIPtrDiff) X(FFIAlignPtr) X(FFIIsAligned) \
    X(FFILoadInt8) X(FFILoadUInt8) X(FFILoadInt16) X(FFILoadUInt16) \
    X(FFILoadInt32) X(FFILoadUInt32) X(FFILoadInt64) X(FFILoadUInt64) \
    X(FFILoadFloat) X(FFILoadDouble) X(FFILoadPtr) \
    X(FFIStoreInt8) X(FFIStoreUInt8) X(FFIStoreInt16) X(FFIStoreUInt16) \
    X(FFIStoreInt32) X(FFIStoreUInt32) X(FFIStoreInt64) X(FFIStoreUInt64) \
    X(FFIStoreFloat) X(FFIStoreDouble) X(FFIStorePtr) \
    X(FFIToCString) X(FFIFromCString) X(FFIFreeCString) X(FFICStringPtr) X(FFICStringFromPtr) \
    X(FFIBufferAlloc) X(FFIBufferFromPtr) X(FFIBufferFree) X(FFIBufferResize) \
    X(FFIBufferRead) X(FFIBufferWrite) X(FFIBufferSize) X(FFIBufferCapacity) X(FFIBufferAsPtr) \
    X(FFICallPtr) X(FFICallPtr0) X(FFICallPtr1) X(FFICallPtr2) \
    X(FFICallPtr3) X(FFICallPtr4) X(FFICallPtr5) \
    X(FFILibraryLoad) X(FFILibraryUnload) X(FFILibraryGetSymbol) \
    X(FFIRegisterCallback) X(FFIUnregisterCallback) X(FFIGetCallbackPtr) \
    X(FFICCallFrameCreate) X(FFICCallFrameDestroy) \
    X(FFICCallFrameSetReg) X(FFICCallFrameGetReg) \
    X(FFICCallFrameSetStackArg) X(FFICCallFrameGetStackArg) \
    X(FFIVMSave) X(FFIVMRestore) X(FFICCallExecute) \
    X(FFICalcStructLayout) X(FFIGetABIInfo)

struct LIR_SourceLoc {
    std::string file;
    uint32_t line;
    uint32_t column;
};

struct LIR_Inst {
    LIR_Op op;
    Type result_type;
    Type type_a;
    Type type_b;
    Reg dst;
    Reg a;
    Reg b;
    Imm imm;
    Backend::Value const_val;
    std::string func_name;
    std::string type_name;
    std::vector<Reg> call_args;
    std::vector<Type> call_arg_types;
    std::string comment;
    LIR_SourceLoc loc;
    
    LIR_Inst() : op(LIR_Op::Nop), result_type(Type::Void), type_a(Type::Void), type_b(Type::Void),
                dst(UINT32_MAX), a(UINT32_MAX), b(UINT32_MAX), imm(0), const_val(VAL_NIL) {}
    
    LIR_Inst(LIR_Op op, Type res_type, Reg dst = 0, Reg a = 0, Reg b = 0, Imm imm = 0,
             Type type_a = Type::Void, Type type_b = Type::Void)
        : op(op), result_type(res_type), type_a(type_a), type_b(type_b),
          dst(dst), a(a), b(b), imm(imm), const_val(VAL_NIL) {}

    LIR_Inst(LIR_Op op, Reg dst = 0, Reg a = 0, Reg b = 0, Imm imm = 0)
        : op(op), result_type(Type::I64), type_a(Type::Void), type_b(Type::Void),
          dst(dst), a(a), b(b), imm(imm), const_val(VAL_NIL) {}
          
    LIR_Inst(LIR_Op op, Type result_type, Reg dst, Backend::Value constant)
        : op(op), result_type(result_type), type_a(Type::Void), type_b(Type::Void),
          dst(dst), a(UINT32_MAX), b(UINT32_MAX), imm(0), const_val(constant) {}

    LIR_Inst(LIR_Op op, Reg dst, Backend::Value constant)
        : op(op), result_type(Type::I64), type_a(Type::Void), type_b(Type::Void),
          dst(dst), a(UINT32_MAX), b(UINT32_MAX), imm(0), const_val(constant) {}

    LIR_Inst(LIR_Op op, Reg dst, const std::string& func, const std::vector<Reg>& args,
             const std::vector<Type>& arg_types = {})
        : op(op), result_type(Type::I64), type_a(Type::Void), type_b(Type::Void),
          dst(dst), a(UINT32_MAX), b(UINT32_MAX), imm(0), const_val(VAL_NIL),
          func_name(func), call_args(args), call_arg_types(arg_types) {}

    LIR_Inst(LIR_Op op, const std::string& func, const std::vector<Reg>& args,
             const std::vector<Type>& arg_types = {})
        : op(op), result_type(Type::Void), type_a(Type::Void), type_b(Type::Void),
          dst(UINT32_MAX), a(UINT32_MAX), b(UINT32_MAX), imm(0), const_val(VAL_NIL),
          func_name(func), call_args(args), call_arg_types(arg_types) {}

    LIR_Inst(LIR_Op op, const std::string& func, const std::vector<Reg>& params, Reg return_reg,
             const std::vector<Type>& param_types = {})
        : op(op), result_type(Type::Void), type_a(Type::Void), type_b(Type::Void),
          dst(return_reg), a(UINT32_MAX), b(UINT32_MAX), imm(0), const_val(VAL_NIL),
          func_name(func), call_args(params), call_arg_types(param_types) {}

    std::string to_string() const;
    bool isReturn() const { return op == LIR_Op::Return || op == LIR_Op::Ret; }
};

struct LIR_BasicBlock {
    uint32_t id;
    std::string label;
    std::vector<LIR_Inst> instructions;
    std::vector<uint32_t> successors;
    std::vector<uint32_t> predecessors;
    bool is_entry;
    bool is_exit;
    bool terminated;
    
    LIR_BasicBlock(uint32_t id, const std::string& label = "") 
        : id(id), label(label), is_entry(false), is_exit(false), terminated(false) {}
    
    void add_instruction(const LIR_Inst& inst) { instructions.push_back(inst); }
    bool has_terminator() const {
        if (terminated) return true;
        if (instructions.empty()) return false;
        const auto& last = instructions.back();
        return last.op == LIR_Op::Jump || last.op == LIR_Op::Return || last.op == LIR_Op::Ret;
    }
};

class LIR_CFG {
public:
    std::vector<std::unique_ptr<LIR_BasicBlock>> blocks;
    uint32_t entry_block_id;
    uint32_t exit_block_id;
    uint32_t next_block_id;
    LIR_CFG() : entry_block_id(0), exit_block_id(UINT32_MAX), next_block_id(0) {}
    LIR_BasicBlock* create_block(const std::string& label = "") {
        auto block = std::make_unique<LIR_BasicBlock>(next_block_id++, label);
        LIR_BasicBlock* block_ptr = block.get();
        blocks.push_back(std::move(block));
        return block_ptr;
    }
    LIR_BasicBlock* get_block(uint32_t id) { return (id < blocks.size()) ? blocks[id].get() : nullptr; }
    void add_edge(uint32_t from_id, uint32_t to_id) {
        LIR_BasicBlock* from = get_block(from_id);
        LIR_BasicBlock* to = get_block(to_id);
        if (from && to) { 
            from->successors.push_back(to_id); 
            to->predecessors.push_back(from_id); 
        }
    }
    bool validate() const;
    void dump_dot() const;
};

struct LIR_DebugInfo {
    std::string function_name;
    LIR_SourceLoc loc;
    std::unordered_map<uint32_t, std::string> var_names;
    std::unordered_map<uint32_t, LIR_SourceLoc> reg_defs;
};

struct OptimizationFlags {
    bool enable_peephole : 1;
    bool enable_const_fold : 1;
    bool enable_dead_code_elim : 1;
    OptimizationFlags() : enable_peephole(false), enable_const_fold(false), enable_dead_code_elim(false) {}
};

class LIR_Function {
public:
    std::string name;
    std::vector<LIR_Inst> instructions;
    std::unique_ptr<LIR_CFG> cfg;
    uint32_t param_count;
    uint32_t register_count;
    LIR_DebugInfo debug_info;
    OptimizationFlags optimizations;
    std::unordered_map<std::string, Reg> variable_to_reg;
    std::unordered_map<Reg, Type> register_types;
    std::unordered_map<Reg, TypePtr> register_language_types;

    LIR_Function(const std::string& name, uint32_t param_count = 0)
        : name(name), cfg(std::make_unique<LIR_CFG>()), param_count(param_count), register_count(0) {}
    
    LIR_Function(const LIR_Function& other) 
        : name(other.name), instructions(other.instructions), cfg(std::make_unique<LIR_CFG>()),
          param_count(other.param_count), register_count(other.register_count),
          debug_info(other.debug_info), optimizations(other.optimizations),
          variable_to_reg(other.variable_to_reg), register_types(other.register_types),
          register_language_types(other.register_language_types) {}
          
    LIR_Function& operator=(const LIR_Function& other) {
        if (this != &other) {
            name = other.name; instructions = other.instructions; cfg = std::make_unique<LIR_CFG>();
            param_count = other.param_count; register_count = other.register_count;
            debug_info = other.debug_info; optimizations = other.optimizations;
            variable_to_reg = other.variable_to_reg; register_types = other.register_types;
            register_language_types = other.register_language_types;
        }
        return *this;
    }
    
    Reg allocate_register() { return register_count++; }
    Reg get_variable_register(const std::string& name) const {
        auto it = variable_to_reg.find(name); return (it != variable_to_reg.end()) ? it->second : UINT32_MAX;
    }
    void set_variable_register(const std::string& name, Reg reg) { variable_to_reg[name] = reg; }
    void set_register_abi_type(Reg reg, Type abi_type) { register_types[reg] = abi_type; }
    void set_register_language_type(Reg reg, TypePtr lang_type) { register_language_types[reg] = lang_type; }
    Type get_register_abi_type(Reg reg) const {
        auto it = register_types.find(reg); return (it != register_types.end()) ? it->second : Type::Void;
    }
    TypePtr get_register_language_type(Reg reg) const {
        auto it = register_language_types.find(reg); return (it != register_language_types.end()) ? it->second : nullptr;
    }
    void add_instruction(const LIR_Inst& inst) { instructions.push_back(inst); }
    std::string to_string() const;
};

class Disassembler {
    const LIR_Function& func; bool show_debug_info;
public:
    Disassembler(const LIR_Function& f, bool debug = false) : func(f), show_debug_info(debug) {}
    std::string disassemble() const;
    std::string disassemble_instruction(const LIR_Inst& inst) const;
};

size_t get_type_size(Type type);
size_t get_type_alignment(Type type);
bool is_integer_type(Type type);
bool is_unsigned_type(Type type);
bool is_float_type(Type type);
std::string lir_op_to_string(LIR_Op op);
Type language_type_to_abi_type(TypePtr lang_type);

} // namespace LIR
} // namespace LM

#endif

// =============================================================================
// tests/lir/test_round_trip.cpp
//
// Round-trip test for the LIR tagged binary serializer (C17).
//
// Builds an LIR_Function with instructions that exercise every field of
// LIR_Inst — op, result_type/type_a/type_b, dst/a/b, imm, const_val of every
// tagged-union variant, func_name, type_name, call_args, call_arg_types, loc,
// and comment — then serializes it to bytes and deserializes it back, and
// asserts that every field round-trips byte-for-byte.
//
// Build & run:
// make lir-test
// =============================================================================
#include "../../src/lir/lir.hh"
#include "../../src/lir/optimizer.hh"
#include "../../src/lir/functions.hh"
#include "../../src/lir/function_registry.hh"
#include "../../src/lir/verifier.hh"
#include "../../src/lir/metrics.hh"
#include "../../src/lir/serializer.hh"
#include "../../src/backend/vm/vm_value.hh"
#include "../../src/backend/vm/vm_runtime.hh"
#include "../../src/backend/vm/register.hh"

#include <cassert>
#include <cstdint>
#include <cstring>
#include "backend/vm/vm_string.hh"
#include <iostream>
#include <string>
#include <vector>

using namespace LM::LIR;

// -----------------------------------------------------------------------------
// Failure reporting helpers
// -----------------------------------------------------------------------------
static int g_failures = 0;

#define CHECK(cond, msg) \
 do { \
 if (!(cond)) { \
 std::cerr << "FAIL: " << (msg) << " (line " << __LINE__ << ")\n"; \
 ++g_failures; \
 } \
 } while (0)

// -----------------------------------------------------------------------------
// Value comparison helpers (Backend::Value is a tagged uint64_t; some payload
// bits live on the heap, so we compare structurally rather than by raw bits).
// -----------------------------------------------------------------------------
static bool values_equal(LM::Backend::Value a, LM::Backend::Value b) {
 // Immediate sentinels first.
 if (a == VAL_NIL && b == VAL_NIL) return true;
 if (a == VAL_TRUE && b == VAL_TRUE) return true;
 if (a == VAL_FALSE && b == VAL_FALSE) return true;
 // Smi (immediate ints) compare by their boxed payload.
 if (IS_INT(a) && IS_INT(b)) {
 return UNBOX_INT(a) == UNBOX_INT(b);
 }
 // Heap objects: must both be pointers, then compare by header type and
 // payload.
 if (!IS_PTR(a) || !IS_PTR(b)) {
 // Mismatched representations (e.g. nil vs heap) -> not equal.
 return (a == b);
 }
 ObjHeader* ha = static_cast<ObjHeader*>(UNBOX_PTR(a));
 ObjHeader* hb = static_cast<ObjHeader*>(UNBOX_PTR(b));
 if (!ha || !hb) return (ha == hb);
 if (ha->type_id != hb->type_id) return false;

 switch (ha->type_id) {
 case TYPE_STRING: {
 auto* sa = reinterpret_cast<LmStringHeader*>(ha); auto* sb = reinterpret_cast<LmStringHeader*>(hb);
 return sa->len == sb->len && std::memcmp(sa->data, sb->data, sa->len) == 0;
 }
 case TYPE_I64:
 return reinterpret_cast<ObjI64*>(ha)->value ==
 reinterpret_cast<ObjI64*>(hb)->value;
 case TYPE_U64:
 return reinterpret_cast<ObjU64*>(ha)->value ==
 reinterpret_cast<ObjU64*>(hb)->value;
 case TYPE_I128:
 return reinterpret_cast<ObjI128*>(ha)->value ==
 reinterpret_cast<ObjI128*>(hb)->value;
 case TYPE_U128:
 return reinterpret_cast<ObjU128*>(ha)->value ==
 reinterpret_cast<ObjU128*>(hb)->value;
 case TYPE_FLOAT:
 return reinterpret_cast<ObjFloat*>(ha)->value ==
 reinterpret_cast<ObjFloat*>(hb)->value;
 case TYPE_BOX: {
 LmBox* ba = reinterpret_cast<LmBox*>(ha);
 LmBox* bb = reinterpret_cast<LmBox*>(hb);
 if (ba->type != bb->type) return false;
 switch (ba->type) {
 case LM_BOX_INT:
 return ba->value.as_int == bb->value.as_int;
 case LM_BOX_FLOAT:
 return ba->value.as_float == bb->value.as_float;
 case LM_BOX_BOOL:
 return ba->value.as_bool == bb->value.as_bool;
 case LM_BOX_STRING: {
 const char* sa = static_cast<const char*>(ba->value.as_ptr);
 const char* sb = static_cast<const char*>(bb->value.as_ptr);
 if (!sa || !sb) return sa == sb;
 return std::strcmp(sa, sb) == 0;
 }
 case LM_BOX_NULLPTR:
 return true;
 default:
 return false;
 }
 }
 default:
 // We don't model other heap kinds in the serializer's ConstTag
 // table — these get dropped to NIL on serialize. Anything that
 // makes it here is unexpected.
 return false;
 }
}

// -----------------------------------------------------------------------------
// Instruction-level comparison
// -----------------------------------------------------------------------------
//
// Note: LIR_Inst's constructors do not value-initialize the POD members of
// LIR_SourceLoc (line/column). The serializer drops `loc` entirely when
// `loc.file` is empty, so two instructions with different uninitialized
// loc.line/column but the same (empty) loc.file still serialize to the same
// bytes and must be considered equal. We normalize accordingly here.
static LIR_SourceLoc normalize_loc(const LIR_SourceLoc& l) {
 if (l.file.empty()) return LIR_SourceLoc{"", 0, 0};
 return l;
}

static bool instructions_equal(const LIR_Inst& a, const LIR_Inst& b) {
 if (a.op != b.op) {
 std::cerr << " op mismatch: " << lir_op_to_string(a.op) << " vs "
 << lir_op_to_string(b.op) << "\n";
 return false;
 }
 if (a.result_type != b.result_type) return false;
 if (a.type_a != b.type_a) return false;
 if (a.type_b != b.type_b) return false;
 if (a.dst != b.dst) return false;
 if (a.a != b.a) return false;
 if (a.b != b.b) return false;
 if (a.imm != b.imm) return false;
 if (!values_equal(a.const_val, b.const_val)) return false;
 if (a.func_name != b.func_name) return false;
 if (a.type_name != b.type_name) return false;
 if (a.call_args != b.call_args) return false;
 if (a.call_arg_types != b.call_arg_types) return false;
 if (a.comment != b.comment) return false;
 LIR_SourceLoc la = normalize_loc(a.loc);
 LIR_SourceLoc lb = normalize_loc(b.loc);
 if (la.file != lb.file) return false;
 if (la.line != lb.line) return false;
 if (la.column != lb.column) return false;
 return true;
}

static bool functions_equal(const LIR_Function& a, const LIR_Function& b) {
 if (a.name != b.name) {
 std::cerr << " function name mismatch: '" << a.name << "' vs '"
 << b.name << "'\n";
 return false;
 }
 if (a.param_count != b.param_count) {
 std::cerr << " param_count mismatch: " << a.param_count << " vs "
 << b.param_count << "\n";
 return false;
 }
 if (a.register_count != b.register_count) {
 std::cerr << " register_count mismatch: " << a.register_count
 << " vs " << b.register_count << "\n";
 return false;
 }
 if (a.instructions.size() != b.instructions.size()) {
 std::cerr << " instruction count mismatch: " << a.instructions.size()
 << " vs " << b.instructions.size() << "\n";
 return false;
 }
 for (size_t i = 0; i < a.instructions.size(); ++i) {
 if (!instructions_equal(a.instructions[i], b.instructions[i])) {
 std::cerr << " instruction " << i << " ("
 << lir_op_to_string(a.instructions[i].op)
 << ") differs after round-trip\n";
 return false;
 }
 }
 return true;
}

// =============================================================================
// Test cases
// =============================================================================

// Build a function exercising every ConstTag variant in the serializer.
static LIR_Function build_const_val_function() {
 LIR_Function f("const_zoo", /*param_count=*/0);
 f.register_count = 4;

 auto add = [&](LIR_Op op, LM::Backend::Value v) {
 LIR_Inst inst(op, LM::LIR::Type::I64, /*dst=*/0, v);
 // LIR_Inst's constructors don't value-init LIR_SourceLoc, so force
 // zero-init here to keep the round-trip comparison deterministic.
 inst.loc = LIR_SourceLoc{"", 0, 0};
 f.instructions.push_back(inst);
 };

 add(LIR_Op::LoadConst, VAL_NIL);
 add(LIR_Op::LoadConst, VAL_TRUE);
 add(LIR_Op::LoadConst, VAL_FALSE);
 add(LIR_Op::LoadConst, BOX_INT(0));
 add(LIR_Op::LoadConst, BOX_INT(42));
 add(LIR_Op::LoadConst, BOX_INT(-123456789));
 add(LIR_Op::LoadConst, lm_alloc_i64(INT64_C(-9007199254740993))); // outside Smi range
 add(LIR_Op::LoadConst, lm_alloc_i64(INT64_C(9007199254740992)));
 add(LIR_Op::LoadConst, lm_alloc_u64(UINT64_C(18446744073709551615)));
 add(LIR_Op::LoadConst, lm_alloc_float(3.141592653589793));
 add(LIR_Op::LoadConst, lm_alloc_float(-0.0));
 {
 __int128 big = static_cast<__int128>(1) << 100;
 add(LIR_Op::LoadConst, lm_alloc_i128(big));
 }
 {
 unsigned __int128 ubig = static_cast<unsigned __int128>(1) << 110;
 add(LIR_Op::LoadConst, lm_alloc_u128(ubig));
 }
 add(LIR_Op::LoadConst, BOX_PTR(lm_box_int(9876543210LL)));
 add(LIR_Op::LoadConst, BOX_PTR(lm_box_float(2.718281828459045)));
 add(LIR_Op::LoadConst, BOX_PTR(lm_box_bool(1)));
 add(LIR_Op::LoadConst, BOX_PTR(lm_box_bool(0)));
 add(LIR_Op::LoadConst, BOX_PTR(lm_str_from_bytes("closure\0target",14)));
 add(LIR_Op::LoadConst, BOX_PTR(lm_box_string("hello, lir!")));
 add(LIR_Op::LoadConst, BOX_PTR(lm_box_string(""))); // empty string
 add(LIR_Op::LoadConst, BOX_PTR(lm_box_string("multi\1\2\3byte")));
 add(LIR_Op::LoadConst, BOX_PTR(lm_box_nullptr()));

 return f;
}

// Build a function exercising call_args / call_arg_types / func_name / type_name
// / loc / comment / imm.
static LIR_Function build_metadata_function() {
 LIR_Function f("meta_func", /*param_count=*/2);
 f.register_count = 8;

 // FuncDef with func_name + a typed call signature in call_args / call_arg_types.
 {
 LIR_Inst inst(LIR_Op::Call, /*dst=*/0, std::string("printf"),
 std::vector<Reg>{1, 2, 3},
 std::vector<LM::LIR::Type>{LM::LIR::Type::Ptr, LM::LIR::Type::I32, LM::LIR::Type::F64});
 inst.imm = 3;
 inst.result_type = LM::LIR::Type::I32;
 inst.comment = "call printf(fmt, count, val)";
 inst.loc.file = "tests/basic/hello.lm";
 inst.loc.line = 17;
 inst.loc.column = 4;
 f.instructions.push_back(inst);
 }

 // CallIndirect with no func_name, only call_args.
 {
 LIR_Inst inst(LIR_Op::CallIndirect, std::string(""),
 std::vector<Reg>{0, 1});
 inst.call_arg_types = {LM::LIR::Type::I64, LM::LIR::Type::I64};
 inst.result_type = LM::LIR::Type::Void;
 f.instructions.push_back(inst);
 }

 // MakeEnum with type_name set.
 {
 LIR_Inst inst(LIR_Op::MakeEnum, LM::LIR::Type::I64, /*dst=*/5, /*a=*/6, /*b=*/0,
 /*imm=*/7);
 inst.type_name = "Color";
 inst.comment = "color.Red(7)";
 f.instructions.push_back(inst);
 }

 // Jump with imm = label id and no func_name.
 {
 LIR_Inst inst(LIR_Op::Jump, /*dst=*/UINT32_MAX, /*a=*/UINT32_MAX,
 /*b=*/UINT32_MAX, /*imm=*/static_cast<int64_t>(f.instructions.size()+1));
 f.instructions.push_back(inst);
 }

 // Label marker (imm = label id).
 {
 LIR_Inst inst(LIR_Op::Label, /*dst=*/UINT32_MAX, /*a=*/UINT32_MAX,
 /*b=*/UINT32_MAX, /*imm=*/static_cast<int64_t>(f.instructions.size()));
 f.instructions.push_back(inst);
 }

 // Return.
 {
 LIR_Inst inst(LIR_Op::Return, /*dst=*/0);
 f.instructions.push_back(inst);
 }

 return f;
}

// Build a tiny "real" function that mixes everything.
static LIR_Function build_mixed_function() {
 LIR_Function f("mixed", /*param_count=*/1);
 f.register_count = 6;

 {
 LIR_Inst inst(LIR_Op::LoadConst, LM::LIR::Type::I64, /*dst=*/1, BOX_INT(10));
 inst.loc = {"src.lm", 1, 1};
 f.instructions.push_back(inst);
 }
 {
 LIR_Inst inst(LIR_Op::LoadConst, LM::LIR::Type::I64, /*dst=*/2, BOX_INT(20));
 inst.loc = {"src.lm", 2, 1};
 f.instructions.push_back(inst);
 }
 {
 LIR_Inst inst(LIR_Op::Add, LM::LIR::Type::I64, /*dst=*/3, /*a=*/1, /*b=*/2);
 inst.loc = {"src.lm", 3, 1};
 inst.comment = "3 = 1 + 2";
 f.instructions.push_back(inst);
 }
 {
 LIR_Inst inst(LIR_Op::Call, /*dst=*/4, std::string("print_int"),
 std::vector<Reg>{3}, std::vector<LM::LIR::Type>{LM::LIR::Type::I64});
 inst.result_type = LM::LIR::Type::Void;
 inst.loc = {"src.lm", 4, 1};
 f.instructions.push_back(inst);
 }
 {
 LIR_Inst inst(LIR_Op::Return, /*dst=*/4);
 f.instructions.push_back(inst);
 }

 return f;
}

// =============================================================================
// main
// =============================================================================
int main() {
 std::cout << "=== LIR serializer round-trip test (C17) ===\n";

 {
 auto fn = std::make_shared<LIRFunction>("registration_memory_contract",
     std::vector<LIRParameter>{{"owner", LM::LIR::Type::Ptr}}, LM::LIR::Type::Ptr, nullptr);
 fn->register_count_ = 7;
 fn->memory_effects_.parameters = {LM::Memory::Ownership::ReadBorrow};
 fn->memory_effects_.result = LM::Memory::Ownership::ReadBorrow;
 fn->memory_effects_.borrowed_parameter = 0;
 LIRFunctionManager::getInstance().registerFunction(fn);
 auto* registered = FunctionRegistry::getInstance().getFunction(fn->getName());
 CHECK(registered != nullptr, "function registration missing");
 if (registered) {
 CHECK(registered->register_count == 7, "registration lost register count");
 CHECK(registered->memory_effects.parameters == fn->memory_effects_.parameters, "registration lost parameter effects");
 CHECK(registered->memory_effects.borrowed_parameter == 0, "registration lost alias provenance");
 }

 }
 {
 int64_t memory=0;
 LIR_Function f("alias_probe",0); f.register_count=5;
 f.instructions.emplace_back(LIR_Op::LoadConst,LM::LIR::Type::I64,0,make_i64(reinterpret_cast<uintptr_t>(&memory)));
 f.instructions.emplace_back(LIR_Op::Mov,LM::LIR::Type::I64,1,0,UINT32_MAX);
 f.instructions.emplace_back(LIR_Op::LoadConst,LM::LIR::Type::I64,2,make_i64(1));
 f.instructions.emplace_back(LIR_Op::LoadConst,LM::LIR::Type::I64,3,make_i64(2));
 f.instructions.emplace_back(LIR_Op::MemoryStore,LM::LIR::Type::Void,UINT32_MAX,0,2,6);
 f.instructions.emplace_back(LIR_Op::MemoryStore,LM::LIR::Type::Void,UINT32_MAX,1,3,6);
 f.instructions.emplace_back(LIR_Op::MemoryLoad,LM::LIR::Type::I64,4,0,UINT32_MAX,6);
 LIR_Inst store(LIR_Op::StoreGlobal,LM::LIR::Type::Void,UINT32_MAX,4,UINT32_MAX); store.func_name="result";f.instructions.push_back(store);
 f.instructions.emplace_back(LIR_Op::Return,LM::LIR::Type::I64,UINT32_MAX,4,UINT32_MAX);
 LM::Backend::VM::Register::RegisterVM vm;
 vm.execute(f);
 CHECK(as_i64(vm.get_global("result")) == 2, "optimizer_alias baseline result");
 vm.reset();
 Optimizer optimizer(f);
 CHECK(!optimizer.redundant_memory_elimination(), "unsafe pass remains quarantined");
 vm.execute(f);
 CHECK(as_i64(vm.get_global("result")) == 2, "optimizer_alias changed observable output");
 }
 {
 int64_t memory=0;
 LIR_Function f("alias_probe",0); f.register_count=5;
 f.instructions.emplace_back(LIR_Op::LoadConst,LM::LIR::Type::I64,0,make_i64(reinterpret_cast<uintptr_t>(&memory)));
 f.register_count=6;
 f.instructions.emplace_back(LIR_Op::LoadConst,LM::LIR::Type::I64,1,make_i64(0));
 f.instructions.emplace_back(LIR_Op::LoadConst,LM::LIR::Type::I64,2,make_i64(2));
 f.instructions.emplace_back(LIR_Op::LoadConst,LM::LIR::Type::I64,3,make_i64(1));
 f.instructions.emplace_back(LIR_Op::Label,LM::LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX,4);
 f.instructions.emplace_back(LIR_Op::CmpLT,LM::LIR::Type::Bool,4,1,2);
 f.instructions.emplace_back(LIR_Op::JumpIfFalse,LM::LIR::Type::Void,UINT32_MAX,4,UINT32_MAX,12);
 f.instructions.emplace_back(LIR_Op::MemoryStore,LM::LIR::Type::Void,UINT32_MAX,0,1,6);
 f.instructions.emplace_back(LIR_Op::MemoryLoad,LM::LIR::Type::I64,5,0,UINT32_MAX,6);
 LIR_Inst store(LIR_Op::StoreGlobal,LM::LIR::Type::Void,UINT32_MAX,5,UINT32_MAX);store.func_name="result";f.instructions.push_back(store);
 f.instructions.emplace_back(LIR_Op::Add,LM::LIR::Type::I64,1,1,3);
 f.instructions.emplace_back(LIR_Op::Jump,LM::LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX,4);
 f.instructions.emplace_back(LIR_Op::Label,LM::LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX,12);
 f.instructions.emplace_back(LIR_Op::Return,LM::LIR::Type::I64,UINT32_MAX,5,UINT32_MAX);
 LM::Backend::VM::Register::RegisterVM vm;
 vm.execute(f);
 CHECK(as_i64(vm.get_global("result")) == 1, "optimizer_licm baseline result");
 vm.reset();
 Optimizer optimizer(f);
 CHECK(!optimizer.loop_invariant_code_motion(), "unsafe pass remains quarantined");
 vm.execute(f);
 CHECK(as_i64(vm.get_global("result")) == 1, "optimizer_licm changed observable output");
 }
 {
 for (int failure = 0; failure < 3; ++failure) {
 LIR_Function region("invalid_region_exit", 0);
 region.register_count = 1;
 if (failure != 0) region.instructions.emplace_back(LIR_Op::RegionEnter, 0, 0, 0, 17);
 if (failure != 1) region.instructions.emplace_back(LIR_Op::RegionExit, 0, 0, 0, failure == 2 ? 18 : 17);
 region.instructions.emplace_back(LIR_Op::Ret, LM::LIR::Type::Void, UINT32_MAX, UINT32_MAX, UINT32_MAX);
 std::vector<std::string> errors;
 CHECK(!Verifier::verify_memory_regions(region, errors), "invalid region cleanup accepted");
 }
 LIR_Function balanced("balanced_regions", 0);
 balanced.instructions.emplace_back(LIR_Op::RegionEnter, 0, 0, 0, 17);
 balanced.instructions.emplace_back(LIR_Op::RegionExit, 0, 0, 0, 17);
 balanced.instructions.emplace_back(LIR_Op::Ret, LM::LIR::Type::Void, UINT32_MAX, UINT32_MAX, UINT32_MAX);
 std::vector<std::string> errors;
 CHECK(Verifier::verify_memory_regions(balanced, errors), "balanced regions rejected");
 LIR_Function branching("numeric_branch_regions", 0);
 branching.register_count = 1;
 branching.instructions.emplace_back(LIR_Op::LoadConst, LM::LIR::Type::Bool, 0, VAL_TRUE);
 branching.instructions.emplace_back(LIR_Op::RegionEnter, 0, 0, 0, 17);
 branching.instructions.emplace_back(LIR_Op::JumpIfFalse, LM::LIR::Type::Void, UINT32_MAX, 0, UINT32_MAX, 5);
 branching.instructions.emplace_back(LIR_Op::RegionExit, 0, 0, 0, 17);
 branching.instructions.emplace_back(LIR_Op::Jump, LM::LIR::Type::Void, UINT32_MAX, UINT32_MAX, UINT32_MAX, 6);
 branching.instructions.emplace_back(LIR_Op::RegionExit, 0, 0, 0, 17);
 branching.instructions.emplace_back(LIR_Op::Ret, LM::LIR::Type::Void, UINT32_MAX, UINT32_MAX, UINT32_MAX);
 errors.clear();
 CHECK(Verifier::verify_memory_regions(branching, errors), "numeric CFG successors lost");
 branching.instructions[5] = LIR_Inst(LIR_Op::Nop);
 errors.clear();
 CHECK(!Verifier::verify_memory_regions(branching, errors), "cleanup bypass at CFG join accepted");
 bool registration_rejected = false;
 try { FunctionRegistry::getInstance().registerFunction(branching.name, std::make_unique<LIR_Function>(branching)); }
 catch (const std::exception&) { registration_rejected = true; }
 CHECK(registration_rejected, "registration bypassed region verification");
 }
 {
 LIR_Function contract("memory_contract", 1);
 contract.register_count = 3;
 contract.memory_effects.parameters = {LM::Memory::Ownership::ReadBorrow};
 contract.memory_effects.result = LM::Memory::Ownership::ReadBorrow;
 contract.memory_effects.borrowed_parameter = 0;
 LIR_Inst call(LIR_Op::Call, 1, "borrowed", std::vector<Reg>{0});
 call.call_arg_ownership = {LM::Memory::Ownership::ReadBorrow};
 contract.instructions.push_back(call);
 auto encoded = Serializer::serialize(contract);
 auto decoded = Serializer::deserialize(encoded);
 CHECK(decoded.memory_effects.parameters == contract.memory_effects.parameters, "parameter effects lost");
 CHECK(decoded.memory_effects.result == contract.memory_effects.result, "return effect lost");
 CHECK(decoded.memory_effects.borrowed_parameter == 0, "borrow origin lost");
 CHECK(decoded.instructions[0].call_arg_ownership == call.call_arg_ownership, "call effects lost");
 encoded.push_back(0);
 bool threw = false;
 try { (void)Serializer::deserialize(encoded); } catch (const std::exception&) { threw = true; }
 CHECK(threw, "trailing bytes accepted");
 }
 {
 for (int malformed = 0; malformed < 3; ++malformed) {
 LIR_Function invalid("invalid_capability", 0); invalid.register_count = 2;
 LIR_Inst ref(LIR_Op::RefCreate, LM::LIR::Type::U64, 1, 0, UINT32_MAX);
 if (malformed == 0) ref.imm = 4; // Bits 0/1 encode writable/nullable; all others are invalid.
 if (malformed == 1) ref.result_type = LM::LIR::Type::F64;
 if (malformed == 2) ref.dst = UINT32_MAX;
 invalid.instructions.push_back(ref);
 bool rejected = false;
 try { (void)Serializer::deserialize(Serializer::serialize(invalid)); }
 catch (const std::exception&) { rejected = true; }
 CHECK(rejected, "malformed capability accepted from precompiled LIR");
 }
 }
 // --- Test 1: empty function round-trips -------------------------------
 {
 LIR_Function empty("empty", 0);
 auto buf = Serializer::serialize(empty);
 CHECK(!buf.empty(), "serialize(empty) returned empty buffer");
 CHECK(buf.size() >= 5, "serialize(empty) too small for header");
 CHECK(std::memcmp(buf.data(), "LIR1", 4) == 0,
 "serialize(empty) missing 'LIR1' magic");
 CHECK(buf[4] == 1, "serialize(empty) wrong version byte");
 auto back = Serializer::deserialize(buf);
 CHECK(functions_equal(empty, back),
 "empty function did not round-trip");
 }

 // --- Test 2: const_val zoo (every ConstTag variant) -------------------
 {
 auto f = build_const_val_function();
 auto buf = Serializer::serialize(f);
 CHECK(!buf.empty(), "serialize(const_zoo) returned empty buffer");
 auto back = Serializer::deserialize(buf);
 CHECK(functions_equal(f, back),
 "const_val zoo function did not round-trip");
 }

 // --- Test 3: metadata (func_name / type_name / call_args / loc / ...) -
 {
 auto f = build_metadata_function();
 auto buf = Serializer::serialize(f);
 CHECK(!buf.empty(), "serialize(meta_func) returned empty buffer");
 auto back = Serializer::deserialize(buf);
 CHECK(functions_equal(f, back),
 "metadata function did not round-trip");
 }

 // --- Test 4: mixed function (realistic shape) -------------------------
 {
 auto f = build_mixed_function();
 auto buf = Serializer::serialize(f);
 CHECK(!buf.empty(), "serialize(mixed) returned empty buffer");
 auto back = Serializer::deserialize(buf);
 CHECK(functions_equal(f, back),
 "mixed function did not round-trip");
 }

 // --- Test 5: deserialize rejects bad magic ----------------------------
 {
 std::vector<uint8_t> bad = {'B', 'A', 'D', '!', 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
 bool threw = false;
 try {
 (void)Serializer::deserialize(bad);
 } catch (const std::runtime_error&) {
 threw = true;
 }
 CHECK(threw, "deserialize(bad magic) should throw");
 }

 // --- Test 6: deserialize rejects bad version --------------------------
 {
 LIR_Function empty("v", 0);
 auto buf = Serializer::serialize(empty);
 buf[4] = 99; // bad version
 bool threw = false;
 try {
 (void)Serializer::deserialize(buf);
 } catch (const std::runtime_error&) {
 threw = true;
 }
 CHECK(threw, "deserialize(bad version) should throw");
 }

 // --- Test 7: deserialize rejects truncated buffer ---------------------
 {
 LIR_Function f("trunc", 0);
 f.register_count = 1;
 f.instructions.push_back(LIR_Inst(LIR_Op::Nop));
 auto buf = Serializer::serialize(f);
 // Truncate to just past the header.
 buf.resize(5 + 4 + 4 + 4 + 4);
 bool threw = false;
 try {
 (void)Serializer::deserialize(buf);
 } catch (const std::runtime_error&) {
 threw = true;
 }
 CHECK(threw, "deserialize(truncated buffer) should throw");
 }

 // --- Test 8: round-trip preserves call_arg_types ordering -------------
 {
 LIR_Function f("argtypes", 0);
 f.register_count = 3;
 LIR_Inst inst(LIR_Op::Call, /*dst=*/0, std::string("fn"),
 std::vector<Reg>{1, 2},
 std::vector<LM::LIR::Type>{LM::LIR::Type::F32, LM::LIR::Type::Bool, LM::LIR::Type::U8});
 f.instructions.push_back(inst);
 auto buf = Serializer::serialize(f);
 auto back = Serializer::deserialize(buf);
 const auto& back_inst = back.instructions.at(0);
 CHECK(back_inst.call_arg_types.size() == 3,
 "call_arg_types count lost in round-trip");
 if (back_inst.call_arg_types.size() == 3) {
 CHECK(back_inst.call_arg_types[0] == LM::LIR::Type::F32,
 "call_arg_types[0] lost");
 CHECK(back_inst.call_arg_types[1] == LM::LIR::Type::Bool,
 "call_arg_types[1] lost");
 CHECK(back_inst.call_arg_types[2] == LM::LIR::Type::U8,
 "call_arg_types[2] lost");
 }
 }

 // --- Test 9: metrics & OptimizationReport unit test ---------------------
 {
 LIR_Function f("opt_test", 0);
 f.register_count = 5;

 // Inst 0: LoadConst 10 -> r0
 f.instructions.push_back(LIR_Inst(LIR_Op::LoadConst, LM::LIR::Type::I64, 0, BOX_INT(10)));
 // Inst 1: LoadConst 20 -> r1
 f.instructions.push_back(LIR_Inst(LIR_Op::LoadConst, LM::LIR::Type::I64, 1, BOX_INT(20)));
 // Inst 2: Add r0, r1 -> r2
 f.instructions.push_back(LIR_Inst(LIR_Op::Add, LM::LIR::Type::I64, 2, 0, 1));
 // Inst 3: LoadConst 0 -> r3
 f.instructions.push_back(LIR_Inst(LIR_Op::LoadConst, LM::LIR::Type::I64, 3, BOX_INT(0)));
 // Inst 4: Add r2, r3 -> r4 (Strength reduction: x + 0 -> x)
 f.instructions.push_back(LIR_Inst(LIR_Op::Add, LM::LIR::Type::I64, 4, 2, 3));
 // Inst 5: Ret r4
 f.instructions.push_back(LIR_Inst(LIR_Op::Ret, 4));

 size_t initial_mem_ops = MetricsCollector::count_memory_ops(f);
 size_t initial_inst_count = f.instructions.size();
 CHECK(initial_inst_count == 6, "Initial instruction count should be 6");
 CHECK(initial_mem_ops == 0, "Initial memory ops should be 0");

 Optimizer opt(f);
 bool opt_res = opt.optimize();
 CHECK(opt_res, "Optimizer should optimize test function");

 const auto& report = opt.get_report();
 CHECK(report.initial_instructions == initial_inst_count, "Report initial instructions baseline must be immutable");
 CHECK(report.final_instructions < report.initial_instructions, "Report final instructions should be less than initial");
 CHECK(report.passes.size() > 0, "Report should contain recorded pass records");
 }

 {
 // Gate B facts must survive serialization and manager registration.
 LIR_Function facts("ownership_metadata", 1); facts.register_count = 2;
 facts.ownership_parameters = {100}; facts.inferred_effects.parameters = {LM::Memory::Read | LM::Memory::Retain};
 facts.inferred_effects.return_projections = {0};
 LIR_Inst marker(LIR_Op::Nop); marker.ownership.reads = {100}; marker.ownership.defines = {101}; marker.ownership.aliases = {{101,100}};
 facts.instructions.push_back(marker);
 facts.instructions.emplace_back(LIR_Op::Ret, LM::LIR::Type::Void, UINT32_MAX, UINT32_MAX, UINT32_MAX);
 LM::Memory::NodeOwnership provenance; provenance.binding = 101; provenance.managed = true; provenance.origins = {200};
 facts.ownership_provenance[1] = provenance;
 auto decoded = Serializer::deserialize(Serializer::serialize(facts));
 CHECK(decoded.inferred_effects == facts.inferred_effects, "semantic effects lost in serialization");
 CHECK(decoded.ownership_parameters == facts.ownership_parameters, "binding identities lost in serialization");
 CHECK(decoded.instructions[0].ownership == marker.ownership, "ownership events lost in serialization");
 CHECK(decoded.ownership_provenance.at(1).origins == provenance.origins, "allocation provenance lost in serialization");
 FunctionRegistry::getInstance().registerFunction(decoded.name, std::make_unique<LIR_Function>(decoded));
 CHECK(FunctionRegistry::getInstance().getFunction(decoded.name)->inferred_effects == facts.inferred_effects, "registration lost inferred effects");
 }
 {
 // A released, moved, expired, or read-only reference cannot satisfy a
 // statically contradicted validity obligation, including after deserialization.
 for (int failure = 0; failure < 6; ++failure) {
 LIR_Function invalid("invalid_reference_flow",0); invalid.register_count = 4;
 invalid.instructions.emplace_back(LIR_Op::RegionEnter,LM::LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX,1);
 invalid.instructions.emplace_back(LIR_Op::ListCreate,LM::LIR::Type::Ptr,0,UINT32_MAX,UINT32_MAX);
 invalid.instructions.emplace_back(LIR_Op::RefCreate,LM::LIR::Type::U64,1,0,UINT32_MAX,failure==5 ? 2 : 0);
 if (failure == 0) invalid.instructions.emplace_back(LIR_Op::RefRelease,LM::LIR::Type::Void,UINT32_MAX,1,UINT32_MAX);
 if (failure == 1 || failure == 4) invalid.instructions.emplace_back(LIR_Op::RefMove,LM::LIR::Type::U64,2,1,UINT32_MAX,0);
 if (failure == 2) invalid.instructions.emplace_back(LIR_Op::RegionExit,LM::LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX,1);
 invalid.instructions.emplace_back(LIR_Op::RefResolve,LM::LIR::Type::Ptr,3,failure==4 ? 2 : 1,UINT32_MAX,failure==5 ? 3 : failure>=3 ? 1 : 0);
 if (failure != 2) invalid.instructions.emplace_back(LIR_Op::RegionExit,LM::LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX,1);
 invalid.instructions.emplace_back(LIR_Op::Ret,LM::LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX);
 std::vector<std::string> errors;
 CHECK(!Verifier::verify_ownership(invalid,errors),"invalid reference dataflow accepted");
 bool rejected = false;
 try { (void)Serializer::deserialize(Serializer::serialize(invalid)); } catch(const std::exception&) {rejected=true;}
 CHECK(rejected,"deserialization bypassed reference/lifetime verification");
 }
 }
 // Sparse reference facts must retain all future reads, including stores and
 // reads whose results are unused. Only overwritten/dead facts may disappear.
 for (int variant = 0; variant < 5; ++variant) {
 LIR_Function joined("reference_live_join", 1); joined.register_count = 6;
 auto emit = [&](LIR_Op op, LM::LIR::Type type, Reg dst, Reg a, Reg b, int64_t imm=0) {
     joined.instructions.emplace_back(op,type,dst,a,b,imm);
 };
 emit(LIR_Op::RegionEnter,LM::LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX,1);
 emit(LIR_Op::ListCreate,LM::LIR::Type::Ptr,1,UINT32_MAX,UINT32_MAX);
 emit(LIR_Op::RefCreate,LM::LIR::Type::U64,2,1,UINT32_MAX);
 if (variant==2) {
     emit(LIR_Op::RefResolve,LM::LIR::Type::Ptr,4,2,UINT32_MAX);
     emit(LIR_Op::Mov,LM::LIR::Type::Ptr,5,4,UINT32_MAX);
 }
 emit(LIR_Op::JumpIfFalse,LM::LIR::Type::Void,UINT32_MAX,0,UINT32_MAX,11);
 if (variant==1 || variant==2 || variant==4)
     emit(LIR_Op::RefRelease,LM::LIR::Type::Void,UINT32_MAX,2,UINT32_MAX);
 emit(LIR_Op::Jump,LM::LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX,12);
 emit(LIR_Op::Label,LM::LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX,11);
 emit(LIR_Op::Nop,LM::LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX);
 emit(LIR_Op::Label,LM::LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX,12);
 if (variant==4) emit(LIR_Op::RefCreate,LM::LIR::Type::U64,2,1,UINT32_MAX,1);
 if (variant==2) emit(LIR_Op::FrameSetField,LM::LIR::Type::Void,5,UINT32_MAX,0);
 else emit(LIR_Op::RefResolve,LM::LIR::Type::Ptr,4,2,UINT32_MAX,variant>=3 ? 1 : 0);
 emit(LIR_Op::RegionExit,LM::LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX,1);
 emit(LIR_Op::Ret,LM::LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX);
 std::map<int64_t,size_t> labels;
 for (size_t index=0; index<joined.instructions.size(); ++index)
     if (joined.instructions[index].op==LIR_Op::Label) labels[joined.instructions[index].imm]=index;
 for (auto& inst : joined.instructions)
     if (inst.op==LIR_Op::Label || inst.op==LIR_Op::Jump || inst.op==LIR_Op::JumpIfFalse) inst.imm=labels.at(inst.imm);
 std::vector<std::string> errors;
 CHECK(Verifier::verify_memory_regions(joined,errors),"reference liveness fixture has invalid region/CFG structure");
 errors.clear();
 CHECK(Verifier::verify_ownership(joined,errors)==(variant==0 || variant==4),"sparse reference join lost a validity or permission obligation");
 bool restored = true;
 try { (void)Serializer::deserialize(Serializer::serialize(joined)); } catch(const std::exception& e) {restored=false; if(variant==0 || variant==4) std::cerr << e.what() << "\n";}
 CHECK(restored==(variant==0 || variant==4),"restored reference join changed verification");
 }
 if (g_failures == 0) {
 std::cout << "\nALL CHECKS PASSED [x]\n";
 return 0;
 }
 std::cout << "\n" << g_failures << " CHECK(S) FAILED [ ]\n";
 return 1;
}

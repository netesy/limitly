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
//   make lir-test
// =============================================================================
#include "../../src/lir/lir.hh"
#include "../../src/lir/serializer.hh"
#include "../../src/runtime/runtime.h"
#include "../../src/runtime/runtime_value.h"

#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace LM::LIR;

// -----------------------------------------------------------------------------
// Failure reporting helpers
// -----------------------------------------------------------------------------
static int g_failures = 0;

#define CHECK(cond, msg)                                                     \
    do {                                                                     \
        if (!(cond)) {                                                       \
            std::cerr << "FAIL: " << (msg) << " (line " << __LINE__ << ")\n"; \
            ++g_failures;                                                    \
        }                                                                    \
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
        // Mismatched representations (e.g. nil vs heap) → not equal.
        return (a == b);
    }
    ObjHeader* ha = static_cast<ObjHeader*>(UNBOX_PTR(a));
    ObjHeader* hb = static_cast<ObjHeader*>(UNBOX_PTR(b));
    if (!ha || !hb) return (ha == hb);
    if (ha->type_id != hb->type_id) return false;

    switch (ha->type_id) {
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
        std::cerr << "  op mismatch: " << lir_op_to_string(a.op) << " vs "
                  << lir_op_to_string(b.op) << "\n";
        return false;
    }
    if (a.result_type != b.result_type) return false;
    if (a.type_a      != b.type_a)      return false;
    if (a.type_b      != b.type_b)      return false;
    if (a.dst         != b.dst)         return false;
    if (a.a           != b.a)           return false;
    if (a.b           != b.b)           return false;
    if (a.imm         != b.imm)         return false;
    if (!values_equal(a.const_val, b.const_val)) return false;
    if (a.func_name      != b.func_name)      return false;
    if (a.type_name      != b.type_name)      return false;
    if (a.call_args      != b.call_args)      return false;
    if (a.call_arg_types != b.call_arg_types) return false;
    if (a.comment        != b.comment)        return false;
    LIR_SourceLoc la = normalize_loc(a.loc);
    LIR_SourceLoc lb = normalize_loc(b.loc);
    if (la.file   != lb.file)   return false;
    if (la.line   != lb.line)   return false;
    if (la.column != lb.column) return false;
    return true;
}

static bool functions_equal(const LIR_Function& a, const LIR_Function& b) {
    if (a.name != b.name) {
        std::cerr << "  function name mismatch: '" << a.name << "' vs '"
                  << b.name << "'\n";
        return false;
    }
    if (a.param_count != b.param_count) {
        std::cerr << "  param_count mismatch: " << a.param_count << " vs "
                  << b.param_count << "\n";
        return false;
    }
    if (a.register_count != b.register_count) {
        std::cerr << "  register_count mismatch: " << a.register_count
                  << " vs " << b.register_count << "\n";
        return false;
    }
    if (a.instructions.size() != b.instructions.size()) {
        std::cerr << "  instruction count mismatch: " << a.instructions.size()
                  << " vs " << b.instructions.size() << "\n";
        return false;
    }
    for (size_t i = 0; i < a.instructions.size(); ++i) {
        if (!instructions_equal(a.instructions[i], b.instructions[i])) {
            std::cerr << "  instruction " << i << " ("
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
        inst.loc.file   = "tests/basic/hello.lm";
        inst.loc.line   = 17;
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
                      /*b=*/UINT32_MAX, /*imm=*/42);
        f.instructions.push_back(inst);
    }

    // Label marker (imm = label id).
    {
        LIR_Inst inst(LIR_Op::Label, /*dst=*/UINT32_MAX, /*a=*/UINT32_MAX,
                      /*b=*/UINT32_MAX, /*imm=*/42);
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

    if (g_failures == 0) {
        std::cout << "\nALL CHECKS PASSED ✅\n";
        return 0;
    }
    std::cout << "\n" << g_failures << " CHECK(S) FAILED ❌\n";
    return 1;
}

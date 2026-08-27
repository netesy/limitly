#include "fyra_builtin_functions.hh"
#include "backend/vm/vm_string.hh"
#include "backend/vm/vm_list.hh"
#include "backend/utf8.hh"
#include "ir/IRBuilder.h"
#include "ir/IRContext.h"
#include "ir/PhiNode.h"
#include <cstring>
#include "ir/Constant.h"
#include "ir/Type.h"
#include "ir/PhiNode.h"

namespace LM::Backend::Fyra {

// FyraString is defined in fyra_builtin_functions.hh

// ============================================================================
// Legacy VM String ABI (being phased out)
// ============================================================================
// These constants are only used during migration and will be removed
namespace StringABI {
    constexpr uint32_t TYPE_ID = 11;           // TYPE_STRING from vm_value_base.hh
    constexpr uint64_t LEN_OFFSET = 8;         // Offset of len field in LmStringHeader
    constexpr uint64_t CAP_OFFSET = 16;        // Offset of cap field in LmStringHeader
    constexpr uint64_t DATA_OFFSET = 24;       // Offset of data[] in LmStringHeader
    constexpr uint64_t HEADER_SIZE = 24;       // sizeof(ObjHeader) + sizeof(uint64_t) + sizeof(uint64_t)
}

bool FyraBuiltinFunctions::is_builtin(const std::string& name) {
    static const std::unordered_set<std::string> builtins = {
        "print", "assert", "abs", "sqrt", "sin", "cos", "tan", "asin", "acos", "atan",
        "log", "log10", "exp", "ceil", "floor", "round", "len", "input", "time", "sleep", "typeof",
        "file_open", "file_read", "file_write", "file_close", "file_exists", "file_delete",
        "lm_box_string", "lm_list_new", "lm_list_append", "lm_list_get", "lm_list_set", "lm_list_len",
        "lm_tuple_new", "lm_tuple_set", "lm_tuple_get",
        "jit_dict_new", "lm_dict_set", "lm_dict_get"
    };
    return builtins.count(name) > 0;
}

std::string FyraBuiltinFunctions::get_internal_name(const std::string& name) {
    if (name == "print")  return "lm_print";
    if (name == "assert") return "lm_assert";
    if (name == "len")    return "lm_list_len";
    return name;
}

void FyraBuiltinFunctions::emit_used_builtins(ir::Module* module,
                                              ir::IRBuilder* builder,
                                              const std::unordered_set<std::string>& used_builtins) {
    if (used_builtins.count("lm_str_alloc")) emit_str_alloc_ir(module, builder);
    if (used_builtins.count("lm_str_concat")) emit_str_concat_ir(module, builder);
    if (used_builtins.count("lm_rt_str_format")) emit_str_format_ir(module, builder);
    if (used_builtins.count("_builtin_substring") || used_builtins.count("substring")) emit_substring_ir(module, builder);
    if (used_builtins.count("_builtin_string_byte_len")) emit_string_byte_len_ir(module, builder);
    if (used_builtins.count("_builtin_string_decode_next")) emit_string_decode_next_ir(module, builder);
    if (used_builtins.count("_builtin_string_byte_at")) emit_string_byte_at_ir(module, builder);
    if (used_builtins.count("_builtin_string_index_of")) emit_string_index_of_ir(module, builder);
    if (used_builtins.count("_builtin_string_contains")) emit_string_contains_ir(module, builder);
    if (used_builtins.count("_builtin_string_starts_with")) emit_string_starts_with_ir(module, builder);
    if (used_builtins.count("_builtin_string_ends_with")) emit_string_ends_with_ir(module, builder);
    if (used_builtins.count("_builtin_string_trim")) emit_string_trim_ir(module, builder);
    if (used_builtins.count("_builtin_string_to_lower")) emit_string_to_lower_ir(module, builder);
    if (used_builtins.count("_builtin_string_to_upper")) emit_string_to_upper_ir(module, builder);
    if (used_builtins.count("_builtin_string_replace")) emit_string_replace_ir(module, builder);
    if (used_builtins.count("_builtin_string_from_bytes")) emit_string_from_bytes_ir(module, builder);
    if (used_builtins.count("lm_to_string")) emit_to_string_ir(module, builder);
    if (used_builtins.count("lm_error_new")) emit_error_new_ir(module, builder);
    if (used_builtins.count("lm_key_eq")) emit_dict_ir(module, builder);
    if (used_builtins.count("lm_assert")) emit_assert(module, builder);
    if (used_builtins.count("abs"))       emit_abs(module, builder);

    bool needs_list  = false;
    bool needs_tuple = false;
    bool needs_dict  = false;
    bool needs_enum  = false;
    bool needs_math  = false;

    for (const auto& name : used_builtins) {
        if (name.find("list")  != std::string::npos) needs_list  = true;
        if (name.find("tuple") != std::string::npos) needs_tuple = true;
        if (name.find("dict")  != std::string::npos) needs_dict  = true;
        if (name.find("enum")  != std::string::npos) needs_enum  = true;
        if (name == "sqrt" || name == "sin" || name == "cos" || name == "tan" ||
            name == "asin" || name == "acos" || name == "atan" || name == "log" ||
            name == "log10" || name == "exp" || name == "ceil" || name == "floor" ||
            name == "round") needs_math = true;
    }

    if (needs_list)  emit_list_ir(module, builder);
    if (needs_tuple) emit_tuple_ir(module, builder);
    if (needs_dict)  emit_dict_ir(module, builder);
    if (needs_enum)  emit_enum_ir(module, builder);
    if (needs_math)  decl_runtime_math(module, builder);
}

// ---------------------------------------------------------------------------
// Helper: create a 16-byte FyraString struct header { ptr: i8*, len: i64 } on heap
// ---------------------------------------------------------------------------
ir::Value* FyraBuiltinFunctions::create_string_header(ir::Module* module, ir::IRBuilder* builder, ir::Value* data_ptr, ir::Value* len_val) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    ir::Instruction* hdr = builder->createExternCall("memory.alloc", {ctx->getConstantInt(i64, FyraString::STRUCT_SIZE)}, ctx->getPointerType(ctx->getIntegerType(8)));
    builder->createStore(data_ptr, hdr); // ptr at offset 0
    builder->createStore(len_val, builder->createAdd(hdr, ctx->getConstantInt(i64, FyraString::LEN_OFFSET))); // len at offset 8
    return hdr;
}

ir::Value* FyraBuiltinFunctions::create_string_header(ir::Module* module, ir::IRBuilder* builder, ir::Value* data_ptr, uint64_t len) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    return create_string_header(module, builder, data_ptr, ctx->getConstantInt(i64, len));
}

// ---------------------------------------------------------------------------
// Helper: look-up or create a global string constant.
// ---------------------------------------------------------------------------
ir::GlobalVariable* FyraBuiltinFunctions::get_or_create_global_str(ir::Module* module,
                                                      ir::IRBuilder* builder,
                                                      const std::string& name,
                                                      const std::string& value) {
    auto ctx = module->getContextShared();
    for (auto& gv : module->getGlobalVariables())
        if (gv->getName() == name) return gv.get();

    auto i8_ty  = ctx->getIntegerType(8);

    uint64_t s_len = value.length();
    std::vector<ir::Constant*> elems;
    
    auto add_u32 = [&](uint32_t val) {
        elems.push_back(ctx->getConstantInt(i8_ty, (uint8_t)(val & 0xFF)));
        elems.push_back(ctx->getConstantInt(i8_ty, (uint8_t)((val >> 8) & 0xFF)));
        elems.push_back(ctx->getConstantInt(i8_ty, (uint8_t)((val >> 16) & 0xFF)));
        elems.push_back(ctx->getConstantInt(i8_ty, (uint8_t)((val >> 24) & 0xFF)));
    };

    auto add_u64 = [&](uint64_t val) {
        for (int b = 0; b < 8; ++b) {
            elems.push_back(ctx->getConstantInt(i8_ty, (uint8_t)((val >> (b * 8)) & 0xFF)));
        }
    };

    add_u32(StringABI::TYPE_ID); // type_id at offset 0
    add_u32(0);  // metadata at offset 4
    add_u64(s_len); // len at LEN_OFFSET (8)
    add_u64(s_len); // cap at CAP_OFFSET (16)

    for (size_t i = 0; i <= s_len; ++i) {
        elems.push_back(ctx->getConstantInt(i8_ty, (uint8_t)value[i]));
    }

    auto arr_ty = ctx->getArrayType(i8_ty, elems.size());
    ir::Value* arr_const = ctx->getConstantArray(arr_ty, elems);
    auto gv = std::make_unique<ir::GlobalVariable>(
        ctx->getPointerType(i8_ty), name,
        static_cast<ir::Constant*>(arr_const), false, ".data");
    auto* ptr = gv.get();
    module->addGlobalVariable(std::move(gv));
    return ptr;
}

// ---------------------------------------------------------------------------
// emit_print_str_inline - inline io.write for LmStringHeader*
// ---------------------------------------------------------------------------
static int g_print_str_counter = 0;
static int g_print_int_counter = 0;

void FyraBuiltinFunctions::emit_print_str_inline(
        ir::Module* module, ir::IRBuilder* builder, ir::Value* str_hdr_ptr) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);

    ir::Value* len_val = builder->createLoad(builder->createAdd(str_hdr_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    ir::Value* data_ptr = builder->createAdd(str_hdr_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));

    builder->createExternCall("io.write", {
        ctx->getConstantInt(i64, 1),
        data_ptr,
        len_val
    }, i64);
}

void FyraBuiltinFunctions::emit_print_int_inline(
        ir::Module* module, ir::IRBuilder* builder, ir::Value* val) {
    auto ctx = module->getContextShared();
    ir::Function* fn = builder->getInsertPoint()->getParent();
    std::string id = std::to_string(++g_print_int_counter);
    ir::Value* str_hdr = emit_int_to_str_inline(module, builder, val);
    emit_print_str_inline(module, builder, str_hdr);
}
// ---------------------------------------------------------------------------
// lm_assert  ?  kept as a function (branch logic is awkward to inline)
void FyraBuiltinFunctions::emit_print_bool_inline(ir::Module* module,
                                                 ir::IRBuilder* builder,
                                                 ir::Value* val) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    int uid = ++g_print_str_counter;
    std::string s_uid = std::to_string(uid);

    ir::BasicBlock* cur_bb = builder->getInsertPoint();
    ir::Function* cur_fn = cur_bb->getParent();

    ir::BasicBlock* b_true  = builder->createBasicBlock("pb_true_" + s_uid, cur_fn);
    ir::BasicBlock* b_false = builder->createBasicBlock("pb_false_" + s_uid, cur_fn);
    ir::BasicBlock* b_done  = builder->createBasicBlock("pb_done_" + s_uid, cur_fn);

    ir::Value* cond = builder->createCne(val, ctx->getConstantInt(i64, 0));
    builder->createBr(cond, b_true, b_false);

    builder->setInsertPoint(b_true);
    ir::GlobalVariable* gv_true = get_or_create_global_str(module, builder, "str_true", "true");
    builder->createExternCall("io.write", {
        ctx->getConstantInt(i64, 1),
        builder->createAdd(gv_true, ctx->getConstantInt(i64, StringABI::DATA_OFFSET)),
        ctx->getConstantInt(i64, 4)
    }, i64);
    builder->createJmp(b_done);

    builder->setInsertPoint(b_false);
    ir::GlobalVariable* gv_false = get_or_create_global_str(module, builder, "str_false", "false");
    builder->createExternCall("io.write", {
        ctx->getConstantInt(i64, 1),
        builder->createAdd(gv_false, ctx->getConstantInt(i64, StringABI::DATA_OFFSET)),
        ctx->getConstantInt(i64, 5)
    }, i64);
    builder->createJmp(b_done);

    builder->setInsertPoint(b_done);
}

void FyraBuiltinFunctions::emit_print_nil_inline(ir::Module* module,
                                                 ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);

    ir::GlobalVariable* gv_nil = get_or_create_global_str(module, builder, "str_nil", "nil");
    builder->createExternCall("io.write", {
        ctx->getConstantInt(i64, 1),
        builder->createAdd(gv_nil, ctx->getConstantInt(i64, StringABI::DATA_OFFSET)),
        ctx->getConstantInt(i64, 3)
    }, i64);
}

void FyraBuiltinFunctions::emit_print_float_inline(ir::Module* module,
                                                   ir::IRBuilder* builder,
                                                   ir::Value* val) {
    auto ctx = module->getContextShared();
    ir::Value* str_hdr = emit_float_to_str_inline(module, builder, val);
    emit_print_str_inline(module, builder, str_hdr);
}

// ---------------------------------------------------------------------------
void FyraBuiltinFunctions::emit_print_decimal_inline(ir::Module* module,
                                                   ir::IRBuilder* builder,
                                                   ir::Value* val,
                                                   int scale) {
    auto ctx = module->getContextShared();
    ir::Value* str_hdr = emit_decimal_to_str_inline(module, builder, val, scale);
    emit_print_str_inline(module, builder, str_hdr);
}

// ---------------------------------------------------------------------------
static int g_d2s_counter = 0;
static int g_i2s_counter = 0;
static int g_b2s_counter = 0;

ir::Value* FyraBuiltinFunctions::emit_decimal_to_str_inline(ir::Module* module,
                                                            ir::IRBuilder* builder,
                                                            ir::Value* val,
                                                            int scale) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto i8 = ctx->getIntegerType(8);
    auto i32 = ctx->getIntegerType(32);

    int uid = ++g_d2s_counter;
    std::string s_uid = std::to_string(uid);

    ir::BasicBlock* cur_bb = builder->getInsertPoint();
    ir::Function* cur_fn = cur_bb->getParent();

    ir::Instruction* buf_ptr = builder->createExternCall("memory.alloc", {ctx->getConstantInt(i64, 64)}, i64);
    builder->createStore(ctx->getConstantInt(i32, StringABI::TYPE_ID), buf_ptr); // type_id at offset 0
    builder->createStore(ctx->getConstantInt(i32, 0), builder->createAdd(buf_ptr, ctx->getConstantInt(i64, 4))); // metadata at offset 4
    ir::Value* p_end = builder->createAdd(buf_ptr, ctx->getConstantInt(i64, 63));
    builder->createStoreb(ctx->getConstantInt(i8, 0), p_end); // null terminator at end of buffer

    ir::Instruction* v_cur_ptr = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(p_end, v_cur_ptr);

    ir::Instruction* v_whole = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* v_frac = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* v_scale_count = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* v_is_neg = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);

    ir::BasicBlock* b_neg  = builder->createBasicBlock("d2s_neg_" + s_uid, cur_fn);
    ir::BasicBlock* b_abs  = builder->createBasicBlock("d2s_abs_" + s_uid, cur_fn);
    ir::BasicBlock* b_prep = builder->createBasicBlock("d2s_prep_" + s_uid, cur_fn);
    ir::BasicBlock* b_frac_loop = builder->createBasicBlock("d2s_frac_loop_" + s_uid, cur_fn);
    ir::BasicBlock* b_dot  = builder->createBasicBlock("d2s_dot_" + s_uid, cur_fn);
    ir::BasicBlock* b_whole_loop = builder->createBasicBlock("d2s_whole_loop_" + s_uid, cur_fn);
    ir::BasicBlock* b_sign_check = builder->createBasicBlock("d2s_sign_" + s_uid, cur_fn);
    ir::BasicBlock* b_add_minus = builder->createBasicBlock("d2s_minus_" + s_uid, cur_fn);
    ir::BasicBlock* b_done = builder->createBasicBlock("d2s_done_" + s_uid, cur_fn);

    ir::Value* is_neg = builder->createCslt(val, ctx->getConstantInt(i64, 0));
    builder->createBr(is_neg, b_neg, b_abs);

    builder->setInsertPoint(b_neg);
    builder->createStore(ctx->getConstantInt(i64, 1), v_is_neg);
    ir::Value* neg_v = builder->createNeg(val);
    builder->createStore(neg_v, v_whole);
    builder->createJmp(b_prep);

    builder->setInsertPoint(b_abs);
    builder->createStore(ctx->getConstantInt(i64, 0), v_is_neg);
    builder->createStore(val, v_whole);
    builder->createJmp(b_prep);

    builder->setInsertPoint(b_prep);
    ir::Value* abs_v = builder->createLoad(v_whole);

    int64_t divisor_val = 1;
    for (int i = 0; i < scale; ++i) divisor_val *= 10;
    ir::Value* divisor = ctx->getConstantInt(i64, divisor_val);

    ir::Value* whole = builder->createDiv(abs_v, divisor);
    ir::Value* frac = builder->createRem(abs_v, divisor);

    builder->createStore(whole, v_whole);
    builder->createStore(frac, v_frac);
    builder->createStore(ctx->getConstantInt(i64, scale), v_scale_count);
    builder->createJmp(b_frac_loop);

    // Frac loop
    builder->setInsertPoint(b_frac_loop);
    ir::Value* f_val = builder->createLoad(v_frac);
    ir::Value* f_d = builder->createRem(f_val, ctx->getConstantInt(i64, 10));
    ir::Value* f_next = builder->createDiv(f_val, ctx->getConstantInt(i64, 10));
    builder->createStore(f_next, v_frac);

    ir::Value* f_char = builder->createAdd(f_d, ctx->getConstantInt(i64, 48));
    ir::Value* cur_p1 = builder->createLoad(v_cur_ptr);
    ir::Value* new_p1 = builder->createSub(cur_p1, ctx->getConstantInt(i64, 1));
    builder->createStoreb(f_char, new_p1);
    builder->createStore(new_p1, v_cur_ptr);

    ir::Value* sc = builder->createLoad(v_scale_count);
    ir::Value* next_sc = builder->createSub(sc, ctx->getConstantInt(i64, 1));
    builder->createStore(next_sc, v_scale_count);
    ir::Value* sc_more = builder->createCsgt(next_sc, ctx->getConstantInt(i64, 0));
    builder->createBr(sc_more, b_frac_loop, b_dot);

    // Place '.'
    builder->setInsertPoint(b_dot);
    ir::Value* cur_p2 = builder->createLoad(v_cur_ptr);
    ir::Value* new_p2 = builder->createSub(cur_p2, ctx->getConstantInt(i64, 1));
    builder->createStoreb(ctx->getConstantInt(i8, 46), new_p2);
    builder->createStore(new_p2, v_cur_ptr);
    builder->createJmp(b_whole_loop);

    // Whole loop
    builder->setInsertPoint(b_whole_loop);
    ir::Value* w_val = builder->createLoad(v_whole);
    ir::Value* w_d = builder->createRem(w_val, ctx->getConstantInt(i64, 10));
    ir::Value* w_next = builder->createDiv(w_val, ctx->getConstantInt(i64, 10));
    builder->createStore(w_next, v_whole);

    ir::Value* w_char = builder->createAdd(w_d, ctx->getConstantInt(i64, 48));
    ir::Value* cur_p3 = builder->createLoad(v_cur_ptr);
    ir::Value* new_p3 = builder->createSub(cur_p3, ctx->getConstantInt(i64, 1));
    builder->createStoreb(w_char, new_p3);
    builder->createStore(new_p3, v_cur_ptr);

    ir::Value* w_more = builder->createCsge(w_next, ctx->getConstantInt(i64, 1));
    builder->createBr(w_more, b_whole_loop, b_sign_check);

    builder->setInsertPoint(b_sign_check);
    ir::Value* was_neg = builder->createLoad(v_is_neg);
    ir::Value* neg_cond = builder->createCeq(was_neg, ctx->getConstantInt(i64, 1));
    builder->createBr(neg_cond, b_add_minus, b_done);

    builder->setInsertPoint(b_add_minus);
    ir::Value* cur_p4 = builder->createLoad(v_cur_ptr);
    ir::Value* new_p4 = builder->createSub(cur_p4, ctx->getConstantInt(i64, 1));
    builder->createStoreb(ctx->getConstantInt(i8, 45), new_p4);
    builder->createStore(new_p4, v_cur_ptr);
    builder->createJmp(b_done);

    builder->setInsertPoint(b_done);
    ir::Value* str_start = builder->createLoad(v_cur_ptr);
    ir::Value* str_len = builder->createSub(p_end, str_start);
    
    builder->createStore(str_len, builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET))); // len
    builder->createStore(str_len, builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::CAP_OFFSET))); // cap
    
    ir::Value* dst_start_d = builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Instruction* copy_idx_d = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), copy_idx_d);
    ir::Value* copy_len_d = builder->createAdd(str_len, ctx->getConstantInt(i64, 1));

    ir::BasicBlock* b_copy_loop_d = builder->createBasicBlock("d2s_copy_loop_" + s_uid, cur_fn);
    ir::BasicBlock* b_copy_body_d = builder->createBasicBlock("d2s_copy_body_" + s_uid, cur_fn);
    ir::BasicBlock* b_copy_done_d = builder->createBasicBlock("d2s_copy_done_" + s_uid, cur_fn);

    builder->createJmp(b_copy_loop_d);

    builder->setInsertPoint(b_copy_loop_d);
    ir::Value* c_i_d = builder->createLoad(copy_idx_d);
    ir::Value* c_cond_d = builder->createCslt(c_i_d, copy_len_d);
    builder->createBr(c_cond_d, b_copy_body_d, b_copy_done_d);

    builder->setInsertPoint(b_copy_body_d);
    ir::Value* ch_d = builder->createLoadub(builder->createAdd(str_start, c_i_d));
    builder->createStoreb(ch_d, builder->createAdd(dst_start_d, c_i_d));
    builder->createStore(builder->createAdd(c_i_d, ctx->getConstantInt(i64, 1)), copy_idx_d);
    builder->createJmp(b_copy_loop_d);

    builder->setInsertPoint(b_copy_done_d);
    ir::Value* dst_start = builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Instruction* copy_idx = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), copy_idx);
    ir::Value* copy_len = builder->createAdd(str_len, ctx->getConstantInt(i64, 1));

    ir::BasicBlock* b_copy_loop = builder->createBasicBlock("i2s_copy_loop_" + s_uid, cur_fn);
    ir::BasicBlock* b_copy_body = builder->createBasicBlock("i2s_copy_body_" + s_uid, cur_fn);
    ir::BasicBlock* b_copy_done = builder->createBasicBlock("i2s_copy_done_" + s_uid, cur_fn);

    builder->createJmp(b_copy_loop);

    builder->setInsertPoint(b_copy_loop);
    ir::Value* c_i = builder->createLoad(copy_idx);
    ir::Value* c_cond = builder->createCslt(c_i, copy_len);
    builder->createBr(c_cond, b_copy_body, b_copy_done);

    builder->setInsertPoint(b_copy_body);
    ir::Value* ch_i = builder->createLoadub(builder->createAdd(str_start, c_i));
    builder->createStoreb(ch_i, builder->createAdd(dst_start, c_i));
    builder->createStore(builder->createAdd(c_i, ctx->getConstantInt(i64, 1)), copy_idx);
    builder->createJmp(b_copy_loop);

    builder->setInsertPoint(b_copy_done);

    return buf_ptr;
}

ir::Value* FyraBuiltinFunctions::emit_int_to_str_inline(ir::Module* module,
                                                     ir::IRBuilder* builder,
                                                     ir::Value* val) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto i8 = ctx->getIntegerType(8);
    auto i32 = ctx->getIntegerType(32);

    int uid = ++g_i2s_counter;
    std::string s_uid = std::to_string(uid);

    ir::BasicBlock* cur_bb = builder->getInsertPoint();
    ir::Function* cur_fn = cur_bb->getParent();

    // Allocate buffer with header + space for digits
    ir::Instruction* buf_ptr = builder->createExternCall("memory.alloc", {ctx->getConstantInt(i64, 64)}, i64);
    builder->createStore(ctx->getConstantInt(i32, StringABI::TYPE_ID), buf_ptr); // type_id at offset 0
    builder->createStore(ctx->getConstantInt(i32, 0), builder->createAdd(buf_ptr, ctx->getConstantInt(i64, 4))); // metadata at offset 4
    ir::Value* p_end = builder->createAdd(buf_ptr, ctx->getConstantInt(i64, 63));
    builder->createStoreb(ctx->getConstantInt(i8, 0), p_end); // null terminator at end of buffer

    ir::Instruction* v_cur_ptr = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(p_end, v_cur_ptr);

    ir::Instruction* v_val = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* v_is_neg = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);

    ir::BasicBlock* b_neg = builder->createBasicBlock("i2s_neg_" + s_uid, cur_fn);
    ir::BasicBlock* b_pos = builder->createBasicBlock("i2s_pos_" + s_uid, cur_fn);
    ir::BasicBlock* b_loop = builder->createBasicBlock("i2s_loop_" + s_uid, cur_fn);
    ir::BasicBlock* b_sign_check = builder->createBasicBlock("i2s_sign_" + s_uid, cur_fn);
    ir::BasicBlock* b_add_minus = builder->createBasicBlock("i2s_minus_" + s_uid, cur_fn);
    ir::BasicBlock* b_done = builder->createBasicBlock("i2s_done_" + s_uid, cur_fn);

    ir::Value* is_neg = builder->createCslt(val, ctx->getConstantInt(i64, 0));
    builder->createBr(is_neg, b_neg, b_pos);

    builder->setInsertPoint(b_neg);
    builder->createStore(ctx->getConstantInt(i64, 1), v_is_neg);
    builder->createStore(builder->createNeg(val), v_val);
    builder->createJmp(b_loop);

    builder->setInsertPoint(b_pos);
    builder->createStore(ctx->getConstantInt(i64, 0), v_is_neg);
    builder->createStore(val, v_val);
    builder->createJmp(b_loop);

    builder->setInsertPoint(b_loop);
    ir::Value* cur_n = builder->createLoad(v_val);
    ir::Value* d = builder->createRem(cur_n, ctx->getConstantInt(i64, 10));
    ir::Value* next_n = builder->createDiv(cur_n, ctx->getConstantInt(i64, 10));
    builder->createStore(next_n, v_val);

    ir::Value* ch = builder->createAdd(d, ctx->getConstantInt(i64, 48));
    ir::Value* cur_p = builder->createLoad(v_cur_ptr);
    ir::Value* new_p = builder->createSub(cur_p, ctx->getConstantInt(i64, 1));
    builder->createStoreb(ch, new_p);
    builder->createStore(new_p, v_cur_ptr);

    ir::Value* more = builder->createCsge(cur_n, ctx->getConstantInt(i64, 10));
    builder->createBr(more, b_loop, b_sign_check);

    builder->setInsertPoint(b_sign_check);
    ir::Value* was_neg = builder->createLoad(v_is_neg);
    ir::Value* neg_cond = builder->createCeq(was_neg, ctx->getConstantInt(i64, 1));
    builder->createBr(neg_cond, b_add_minus, b_done);

    builder->setInsertPoint(b_add_minus);
    ir::Value* cur_p2 = builder->createLoad(v_cur_ptr);
    ir::Value* new_p2 = builder->createSub(cur_p2, ctx->getConstantInt(i64, 1));
    builder->createStoreb(ctx->getConstantInt(i8, 45), new_p2);
    builder->createStore(new_p2, v_cur_ptr);
    builder->createJmp(b_done);

    builder->setInsertPoint(b_done);
    ir::Value* str_start = builder->createLoad(v_cur_ptr);
    ir::Value* str_len = builder->createSub(p_end, str_start);
    
    builder->createStore(str_len, builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET))); // len
    builder->createStore(str_len, builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::CAP_OFFSET))); // cap
    
    ir::Value* dst_start_d = builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Instruction* copy_idx_d = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), copy_idx_d);
    ir::Value* copy_len_d = builder->createAdd(str_len, ctx->getConstantInt(i64, 1));

    ir::BasicBlock* b_copy_loop_d = builder->createBasicBlock("d2s_copy_loop_" + s_uid, cur_fn);
    ir::BasicBlock* b_copy_body_d = builder->createBasicBlock("d2s_copy_body_" + s_uid, cur_fn);
    ir::BasicBlock* b_copy_done_d = builder->createBasicBlock("d2s_copy_done_" + s_uid, cur_fn);

    builder->createJmp(b_copy_loop_d);

    builder->setInsertPoint(b_copy_loop_d);
    ir::Value* c_i_d = builder->createLoad(copy_idx_d);
    ir::Value* c_cond_d = builder->createCslt(c_i_d, copy_len_d);
    builder->createBr(c_cond_d, b_copy_body_d, b_copy_done_d);

    builder->setInsertPoint(b_copy_body_d);
    ir::Value* ch_d = builder->createLoadub(builder->createAdd(str_start, c_i_d));
    builder->createStoreb(ch_d, builder->createAdd(dst_start_d, c_i_d));
    builder->createStore(builder->createAdd(c_i_d, ctx->getConstantInt(i64, 1)), copy_idx_d);
    builder->createJmp(b_copy_loop_d);

    builder->setInsertPoint(b_copy_done_d);
    ir::Value* dst_start = builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Instruction* copy_idx = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), copy_idx);
    ir::Value* copy_len = builder->createAdd(str_len, ctx->getConstantInt(i64, 1));

    ir::BasicBlock* b_copy_loop = builder->createBasicBlock("i2s_copy_loop_" + s_uid, cur_fn);
    ir::BasicBlock* b_copy_body = builder->createBasicBlock("i2s_copy_body_" + s_uid, cur_fn);
    ir::BasicBlock* b_copy_done = builder->createBasicBlock("i2s_copy_done_" + s_uid, cur_fn);

    builder->createJmp(b_copy_loop);

    builder->setInsertPoint(b_copy_loop);
    ir::Value* c_i = builder->createLoad(copy_idx);
    ir::Value* c_cond = builder->createCslt(c_i, copy_len);
    builder->createBr(c_cond, b_copy_body, b_copy_done);

    builder->setInsertPoint(b_copy_body);
    ir::Value* ch_i = builder->createLoadub(builder->createAdd(str_start, c_i));
    builder->createStoreb(ch_i, builder->createAdd(dst_start, c_i));
    builder->createStore(builder->createAdd(c_i, ctx->getConstantInt(i64, 1)), copy_idx);
    builder->createJmp(b_copy_loop);

    builder->setInsertPoint(b_copy_done);

    return buf_ptr;
}

extern "C" char* lm_float_to_str(uint64_t bits) {
    double d;
    memcpy(&d, &bits, sizeof(d));
    char* buf = (char*)malloc(64);
    snprintf(buf, 64, "%g", d);
    if (strchr(buf, '.') == NULL && strchr(buf, 'e') == NULL && strchr(buf, 'E') == NULL) {
        strcat(buf, ".0");
    }
    return buf;
}

ir::Value* FyraBuiltinFunctions::emit_float_to_str_inline(ir::Module* module,
                                                       ir::IRBuilder* builder,
                                                       ir::Value* val) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto i8 = ctx->getIntegerType(8);
    auto i32 = ctx->getIntegerType(32);

    ir::Function* cur_fn = builder->getInsertPoint()->getParent();
    static int f2s_cnt = 0;
    std::string s_uid = std::to_string(++f2s_cnt);

    ir::Instruction* buf_ptr = builder->createExternCall("memory.alloc", {ctx->getConstantInt(i64, 64)}, i64);
    builder->createStore(ctx->getConstantInt(i32, StringABI::TYPE_ID), buf_ptr); // type_id at offset 0
    builder->createStore(ctx->getConstantInt(i32, 0), builder->createAdd(buf_ptr, ctx->getConstantInt(i64, 4))); // metadata at offset 4

    ir::Value* p_end = builder->createAdd(buf_ptr, ctx->getConstantInt(i64, 63));
    builder->createStoreb(ctx->getConstantInt(i8, 0), p_end); // null terminator

    ir::Instruction* v_cur_ptr = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(p_end, v_cur_ptr);

    ir::Value* is_neg = builder->createCne(builder->createAnd(builder->createShr(val, ctx->getConstantInt(i64, 63)), ctx->getConstantInt(i64, 1)), ctx->getConstantInt(i64, 0));
    ir::Value* exp_raw = builder->createAnd(builder->createShr(val, ctx->getConstantInt(i64, 52)), ctx->getConstantInt(i64, 0x7FF));
    ir::Value* mant = builder->createAnd(val, ctx->getConstantInt(i64, 0x000FFFFFFFFFFFFF));

    ir::BasicBlock* b_zero = builder->createBasicBlock("f2s_zero_" + s_uid, cur_fn);
    ir::BasicBlock* b_special = builder->createBasicBlock("f2s_spec_" + s_uid, cur_fn);
    ir::BasicBlock* b_normal = builder->createBasicBlock("f2s_norm_" + s_uid, cur_fn);
    ir::BasicBlock* b_done = builder->createBasicBlock("f2s_done_" + s_uid, cur_fn);

    ir::Value* is_zero_exp = builder->createCeq(exp_raw, ctx->getConstantInt(i64, 0));
    ir::Value* is_zero_mant = builder->createCeq(mant, ctx->getConstantInt(i64, 0));
    ir::Value* is_zero = builder->createAnd(is_zero_exp, is_zero_mant);

    ir::Value* is_spec = builder->createCeq(exp_raw, ctx->getConstantInt(i64, 0x7FF));

    builder->createBr(is_zero, b_zero, b_special);

    // Branch: Zero (0.0 or -0.0)
    builder->setInsertPoint(b_zero);
    ir::BasicBlock* b_z_neg = builder->createBasicBlock("f2s_z_neg_" + s_uid, cur_fn);
    ir::BasicBlock* b_z_pos = builder->createBasicBlock("f2s_z_pos_" + s_uid, cur_fn);
    builder->createBr(is_neg, b_z_neg, b_z_pos);

    builder->setInsertPoint(b_z_neg);
    ir::Value* dst_zneg = builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    builder->createStore(ctx->getConstantInt(i64, 4), builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    builder->createStore(ctx->getConstantInt(i64, 4), builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::CAP_OFFSET)));
    for (int k = 0; k < 5; ++k) {
        builder->createStoreb(ctx->getConstantInt(i8, "-0.0"[k]), builder->createAdd(dst_zneg, ctx->getConstantInt(i64, k)));
    }
    builder->createJmp(b_done);

    builder->setInsertPoint(b_z_pos);
    ir::Value* dst_zpos = builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    builder->createStore(ctx->getConstantInt(i64, 3), builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    builder->createStore(ctx->getConstantInt(i64, 3), builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::CAP_OFFSET)));
    for (int k = 0; k < 4; ++k) {
        builder->createStoreb(ctx->getConstantInt(i8, "0.0"[k]), builder->createAdd(dst_zpos, ctx->getConstantInt(i64, k)));
    }
    builder->createJmp(b_done);

    // Branch: Special (NaN / Inf) or Normal
    builder->setInsertPoint(b_special);
    ir::BasicBlock* b_inf = builder->createBasicBlock("f2s_inf_" + s_uid, cur_fn);
    ir::BasicBlock* b_nan = builder->createBasicBlock("f2s_nan_" + s_uid, cur_fn);

    ir::Value* is_inf = builder->createCeq(mant, ctx->getConstantInt(i64, 0));
    builder->createBr(is_spec, b_inf, b_normal);

    builder->setInsertPoint(b_inf);
    ir::Value* dst_inf = builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    builder->createStore(ctx->getConstantInt(i64, 3), builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    builder->createStore(ctx->getConstantInt(i64, 3), builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::CAP_OFFSET)));
    builder->createStoreb(ctx->getConstantInt(i8, 'i'), builder->createAdd(dst_inf, ctx->getConstantInt(i64, 0)));
    builder->createStoreb(ctx->getConstantInt(i8, 'n'), builder->createAdd(dst_inf, ctx->getConstantInt(i64, 1)));
    builder->createStoreb(ctx->getConstantInt(i8, 'f'), builder->createAdd(dst_inf, ctx->getConstantInt(i64, 2)));
    builder->createStoreb(ctx->getConstantInt(i8, 0), builder->createAdd(dst_inf, ctx->getConstantInt(i64, 3)));
    builder->createJmp(b_done);

    builder->setInsertPoint(b_nan);
    ir::Value* dst_nan = builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    builder->createStore(ctx->getConstantInt(i64, 3), builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    builder->createStore(ctx->getConstantInt(i64, 3), builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::CAP_OFFSET)));
    builder->createStoreb(ctx->getConstantInt(i8, 'n'), builder->createAdd(dst_nan, ctx->getConstantInt(i64, 0)));
    builder->createStoreb(ctx->getConstantInt(i8, 'a'), builder->createAdd(dst_nan, ctx->getConstantInt(i64, 1)));
    builder->createStoreb(ctx->getConstantInt(i8, 'n'), builder->createAdd(dst_nan, ctx->getConstantInt(i64, 2)));
    builder->createStoreb(ctx->getConstantInt(i8, 0), builder->createAdd(dst_nan, ctx->getConstantInt(i64, 3)));
    builder->createJmp(b_done);

    // Branch: Normal numbers
    builder->setInsertPoint(b_normal);
    ir::Instruction* v_whole = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* v_frac  = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);

    ir::Value* exp = builder->createSub(exp_raw, ctx->getConstantInt(i64, 1023));
    ir::Value* frac_bits = builder->createOr(mant, ctx->getConstantInt(i64, 0x0010000000000000));

    ir::BasicBlock* b_exp_ge0 = builder->createBasicBlock("f2s_exp_ge0_" + s_uid, cur_fn);
    ir::BasicBlock* b_exp_lt0 = builder->createBasicBlock("f2s_exp_lt0_" + s_uid, cur_fn);
    ir::BasicBlock* b_fmt_digits = builder->createBasicBlock("f2s_fmt_" + s_uid, cur_fn);

    ir::Value* is_exp_ge0 = builder->createCsge(exp, ctx->getConstantInt(i64, 0));
    builder->createBr(is_exp_ge0, b_exp_ge0, b_exp_lt0);

    // Sub-branch exp >= 0
    builder->setInsertPoint(b_exp_ge0);
    ir::BasicBlock* b_exp_ge52 = builder->createBasicBlock("f2s_exp_ge52_" + s_uid, cur_fn);
    ir::BasicBlock* b_exp_lt52 = builder->createBasicBlock("f2s_exp_lt52_" + s_uid, cur_fn);
    ir::Value* is_exp_ge52 = builder->createCsge(exp, ctx->getConstantInt(i64, 52));
    builder->createBr(is_exp_ge52, b_exp_ge52, b_exp_lt52);

    builder->setInsertPoint(b_exp_ge52);
    builder->createStore(builder->createShl(frac_bits, builder->createSub(exp, ctx->getConstantInt(i64, 52))), v_whole);
    builder->createStore(ctx->getConstantInt(i64, 0), v_frac);
    builder->createJmp(b_fmt_digits);

    builder->setInsertPoint(b_exp_lt52);
    ir::Value* shift1 = builder->createSub(ctx->getConstantInt(i64, 52), exp);
    builder->createStore(builder->createShr(frac_bits, shift1), v_whole);
    ir::Value* mask1 = builder->createSub(builder->createShl(ctx->getConstantInt(i64, 1), shift1), ctx->getConstantInt(i64, 1));
    ir::Value* rem1 = builder->createAnd(mant, mask1);

    ir::Instruction* v_r = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(rem1, v_r);
    ir::Instruction* v_frac_acc = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), v_frac_acc);

    for (int k = 0; k < 6; ++k) {
        ir::Value* cur_r = builder->createMul(builder->createLoad(v_r), ctx->getConstantInt(i64, 10));
        ir::Value* digit = builder->createShr(cur_r, shift1);
        ir::Value* next_r = builder->createAnd(cur_r, mask1);
        builder->createStore(next_r, v_r);
        ir::Value* cur_acc = builder->createLoad(v_frac_acc);
        ir::Value* next_acc = builder->createAdd(builder->createMul(cur_acc, ctx->getConstantInt(i64, 10)), digit);
        builder->createStore(next_acc, v_frac_acc);
    }
    // 7th digit for rounding
    ir::Value* cur_r7 = builder->createMul(builder->createLoad(v_r), ctx->getConstantInt(i64, 10));
    ir::Value* digit7 = builder->createShr(cur_r7, shift1);
    ir::Value* is_r7_ge5 = builder->createCsge(digit7, ctx->getConstantInt(i64, 5));

    ir::BasicBlock* b_round_up = builder->createBasicBlock("f2s_round_up_" + s_uid, cur_fn);
    ir::BasicBlock* b_round_done = builder->createBasicBlock("f2s_round_done_" + s_uid, cur_fn);
    builder->createBr(is_r7_ge5, b_round_up, b_round_done);

    builder->setInsertPoint(b_round_up);
    builder->createStore(builder->createAdd(builder->createLoad(v_frac_acc), ctx->getConstantInt(i64, 1)), v_frac_acc);
    builder->createJmp(b_round_done);

    builder->setInsertPoint(b_round_done);
    builder->createStore(builder->createLoad(v_frac_acc), v_frac);
    builder->createJmp(b_fmt_digits);

    // Sub-branch exp < 0
    builder->setInsertPoint(b_exp_lt0);
    builder->createStore(ctx->getConstantInt(i64, 0), v_whole);
    ir::Value* shift2 = builder->createSub(ctx->getConstantInt(i64, 52), exp);
    ir::Value* is_shift_lt62 = builder->createCslt(shift2, ctx->getConstantInt(i64, 62));

    ir::BasicBlock* b_s_lt62 = builder->createBasicBlock("f2s_s_lt62_" + s_uid, cur_fn);
    ir::BasicBlock* b_s_ge62 = builder->createBasicBlock("f2s_s_ge62_" + s_uid, cur_fn);
    builder->createBr(is_shift_lt62, b_s_lt62, b_s_ge62);

    builder->setInsertPoint(b_s_lt62);
    ir::Value* mask2 = builder->createSub(builder->createShl(ctx->getConstantInt(i64, 1), shift2), ctx->getConstantInt(i64, 1));
    ir::Instruction* v_r2 = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(frac_bits, v_r2);
    ir::Instruction* v_frac_acc2 = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), v_frac_acc2);

    for (int k = 0; k < 6; ++k) {
        ir::Value* cur_r = builder->createMul(builder->createLoad(v_r2), ctx->getConstantInt(i64, 10));
        ir::Value* digit = builder->createShr(cur_r, shift2);
        ir::Value* next_r = builder->createAnd(cur_r, mask2);
        builder->createStore(next_r, v_r2);
        ir::Value* cur_acc = builder->createLoad(v_frac_acc2);
        ir::Value* next_acc = builder->createAdd(builder->createMul(cur_acc, ctx->getConstantInt(i64, 10)), digit);
        builder->createStore(next_acc, v_frac_acc2);
    }
    builder->createStore(builder->createLoad(v_frac_acc2), v_frac);
    builder->createJmp(b_fmt_digits);

    builder->setInsertPoint(b_s_ge62);
    builder->createStore(ctx->getConstantInt(i64, 0), v_frac);
    builder->createJmp(b_fmt_digits);

    // Formatting digits into buffer
    builder->setInsertPoint(b_fmt_digits);
    ir::Instruction* v_f_rem = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(builder->createLoad(v_frac), v_f_rem);

    ir::Instruction* v_digit_cnt = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 6), v_digit_cnt);

    ir::Instruction* v_has_non_zero = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), v_has_non_zero);

    ir::BasicBlock* b_frac_loop = builder->createBasicBlock("f2s_frac_loop_" + s_uid, cur_fn);
    ir::BasicBlock* b_frac_body = builder->createBasicBlock("f2s_frac_body_" + s_uid, cur_fn);
    ir::BasicBlock* b_dot = builder->createBasicBlock("f2s_dot_" + s_uid, cur_fn);

    builder->createJmp(b_frac_loop);

    builder->setInsertPoint(b_frac_loop);
    ir::Value* dc = builder->createLoad(v_digit_cnt);
    ir::Value* dc_more = builder->createCsgt(dc, ctx->getConstantInt(i64, 0));
    builder->createBr(dc_more, b_frac_body, b_dot);

    builder->setInsertPoint(b_frac_body);
    ir::Value* fr_v = builder->createLoad(v_f_rem);
    ir::Value* fd = builder->createRem(fr_v, ctx->getConstantInt(i64, 10));
    ir::Value* fr_next = builder->createDiv(fr_v, ctx->getConstantInt(i64, 10));
    builder->createStore(fr_next, v_f_rem);

    ir::Value* is_fd_nz = builder->createCne(fd, ctx->getConstantInt(i64, 0));
    ir::Value* is_dc_1 = builder->createCeq(dc, ctx->getConstantInt(i64, 1));
    ir::Value* is_first_digit = builder->createOr(is_fd_nz, is_dc_1);

    ir::Value* cur_has_nz = builder->createLoad(v_has_non_zero);
    ir::Value* new_has_nz = builder->createOr(cur_has_nz, is_first_digit);
    builder->createStore(new_has_nz, v_has_non_zero);

    ir::BasicBlock* b_emit_f_digit = builder->createBasicBlock("f2s_emit_fd_" + s_uid, cur_fn);
    ir::BasicBlock* b_skip_f_digit = builder->createBasicBlock("f2s_skip_fd_" + s_uid, cur_fn);

    builder->createBr(new_has_nz, b_emit_f_digit, b_skip_f_digit);

    builder->setInsertPoint(b_emit_f_digit);
    ir::Value* f_char = builder->createAdd(fd, ctx->getConstantInt(i64, 48));
    ir::Value* cur_p1 = builder->createLoad(v_cur_ptr);
    ir::Value* new_p1 = builder->createSub(cur_p1, ctx->getConstantInt(i64, 1));
    builder->createStoreb(f_char, new_p1);
    builder->createStore(new_p1, v_cur_ptr);
    builder->createJmp(b_skip_f_digit);

    builder->setInsertPoint(b_skip_f_digit);
    builder->createStore(builder->createSub(dc, ctx->getConstantInt(i64, 1)), v_digit_cnt);
    builder->createJmp(b_frac_loop);

    // Place '.'
    builder->setInsertPoint(b_dot);
    ir::Value* cur_p2 = builder->createLoad(v_cur_ptr);
    ir::Value* new_p2 = builder->createSub(cur_p2, ctx->getConstantInt(i64, 1));
    builder->createStoreb(ctx->getConstantInt(i8, 46), new_p2); // '.'
    builder->createStore(new_p2, v_cur_ptr);

    // Format whole part
    ir::BasicBlock* b_whole_loop = builder->createBasicBlock("f2s_w_loop_" + s_uid, cur_fn);
    ir::BasicBlock* b_whole_body = builder->createBasicBlock("f2s_w_body_" + s_uid, cur_fn);
    ir::BasicBlock* b_sign_check = builder->createBasicBlock("f2s_sign_" + s_uid, cur_fn);
    ir::BasicBlock* b_minus = builder->createBasicBlock("f2s_minus_" + s_uid, cur_fn);
    ir::BasicBlock* b_copy_out = builder->createBasicBlock("f2s_copy_out_" + s_uid, cur_fn);

    builder->createJmp(b_whole_loop);

    builder->setInsertPoint(b_whole_loop);
    ir::Value* wv = builder->createLoad(v_whole);
    ir::Value* wd = builder->createRem(wv, ctx->getConstantInt(i64, 10));
    ir::Value* w_next = builder->createDiv(wv, ctx->getConstantInt(i64, 10));
    builder->createStore(w_next, v_whole);

    ir::Value* w_char = builder->createAdd(wd, ctx->getConstantInt(i64, 48));
    ir::Value* cur_p3 = builder->createLoad(v_cur_ptr);
    ir::Value* new_p3 = builder->createSub(cur_p3, ctx->getConstantInt(i64, 1));
    builder->createStoreb(w_char, new_p3);
    builder->createStore(new_p3, v_cur_ptr);

    ir::Value* w_more = builder->createCsge(w_next, ctx->getConstantInt(i64, 1));
    builder->createBr(w_more, b_whole_loop, b_sign_check);

    builder->setInsertPoint(b_sign_check);
    builder->createBr(is_neg, b_minus, b_copy_out);

    builder->setInsertPoint(b_minus);
    ir::Value* cur_p4 = builder->createLoad(v_cur_ptr);
    ir::Value* new_p4 = builder->createSub(cur_p4, ctx->getConstantInt(i64, 1));
    builder->createStoreb(ctx->getConstantInt(i8, 45), new_p4); // '-'
    builder->createStore(new_p4, v_cur_ptr);
    builder->createJmp(b_copy_out);

    // Copy to buf_ptr + DATA_OFFSET
    builder->setInsertPoint(b_copy_out);
    ir::Value* str_start = builder->createLoad(v_cur_ptr);
    ir::Value* str_len = builder->createSub(p_end, str_start);

    builder->createStore(str_len, builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    builder->createStore(str_len, builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::CAP_OFFSET)));

    ir::Value* dst_data = builder->createAdd(buf_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));

    ir::Instruction* copy_idx = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), copy_idx);
    ir::Value* copy_len = builder->createAdd(str_len, ctx->getConstantInt(i64, 1));

    ir::BasicBlock* b_c_loop = builder->createBasicBlock("f2s_c_loop_" + s_uid, cur_fn);
    ir::BasicBlock* b_c_body = builder->createBasicBlock("f2s_c_body_" + s_uid, cur_fn);
    ir::BasicBlock* b_c_done = builder->createBasicBlock("f2s_c_done_" + s_uid, cur_fn);

    builder->createJmp(b_c_loop);

    builder->setInsertPoint(b_c_loop);
    ir::Value* ci = builder->createLoad(copy_idx);
    ir::Value* c_cond = builder->createCslt(ci, copy_len);
    builder->createBr(c_cond, b_c_body, b_c_done);

    builder->setInsertPoint(b_c_body);
    ir::Value* ch = builder->createLoadub(builder->createAdd(str_start, ci));
    builder->createStoreb(ch, builder->createAdd(dst_data, ci));
    builder->createStore(builder->createAdd(ci, ctx->getConstantInt(i64, 1)), copy_idx);
    builder->createJmp(b_c_loop);

    builder->setInsertPoint(b_c_done);
    builder->createJmp(b_done);

    builder->setInsertPoint(b_done);
    return buf_ptr;
}

ir::Value* FyraBuiltinFunctions::emit_bool_to_str_inline(ir::Module* module,
                                                      ir::IRBuilder* builder,
                                                      ir::Value* val) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    ir::GlobalVariable* gv_true = get_or_create_global_str(module, builder, "str_true", "true");
    ir::GlobalVariable* gv_false = get_or_create_global_str(module, builder, "str_false", "false");

    ir::Function* cur_fn = builder->getInsertPoint()->getParent();
    int uid = ++g_print_str_counter;
    std::string s_uid = std::to_string(uid);

    ir::BasicBlock* b_true = builder->createBasicBlock("b2s_t_" + s_uid, cur_fn);
    ir::BasicBlock* b_false = builder->createBasicBlock("b2s_f_" + s_uid, cur_fn);
    ir::BasicBlock* b_done = builder->createBasicBlock("b2s_d_" + s_uid, cur_fn);

    ir::Value* cond = builder->createCne(val, ctx->getConstantInt(i64, 0));
    builder->createBr(cond, b_true, b_false);

    builder->setInsertPoint(b_true);
    builder->createJmp(b_done);

    builder->setInsertPoint(b_false);
    builder->createJmp(b_done);

    builder->setInsertPoint(b_done);
    ir::PhiNode* phi = builder->createPhi(ctx->getIntegerType(64), 2, nullptr);
    phi->addIncoming(gv_true, b_true);
    phi->addIncoming(gv_false, b_false);
    return phi;
}

// ---------------------------------------------------------------------------
void FyraBuiltinFunctions::emit_assert(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    ir::Function* fn = module->getFunction("lm_assert");
    if (!fn)
        fn = builder->createFunction("lm_assert", ctx->getVoidType(),
                                     {i64, i64});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* a_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* a_fail  = builder->createBasicBlock("fail",  fn);
    ir::BasicBlock* a_pass  = builder->createBasicBlock("pass",  fn);

    builder->setInsertPoint(a_entry);
    ir::Value* cond = fn->getParameters().front().get();
    ir::Value* is_true = builder->createCeq(cond, ctx->getConstantInt(i64, 18)); // VAL_TRUE
    ir::Value* is_one  = builder->createCeq(cond, ctx->getConstantInt(i64, 1));  // raw bool 1
    ir::Value* is_pass = builder->createOr(is_true, is_one);
    builder->createBr(is_pass, a_pass, a_fail);

    builder->setInsertPoint(a_fail);
    const std::string fail_msg = "Assertion failed\n";
    ir::GlobalVariable* gv = get_or_create_global_str(module, builder, "assert_fail", fail_msg);
    builder->createExternCall("io.write", {
        ctx->getConstantInt(i64, 1),
        builder->createAdd(gv, ctx->getConstantInt(i64, StringABI::DATA_OFFSET)),
        ctx->getConstantInt(i64, (int64_t)fail_msg.length())
    }, i64);
    builder->createExternCall("process.exit", {
        ctx->getConstantInt(i64, 1)
    }, i64);
    builder->createRet(nullptr);

    builder->setInsertPoint(a_pass);
    builder->createRet(nullptr);
}

// ---------------------------------------------------------------------------
// emit_abs  ?  abs(i64): if val < 0, negate it
// ---------------------------------------------------------------------------
void FyraBuiltinFunctions::emit_abs(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    ir::Function* fn = module->getFunction("abs");
    if (!fn)
        fn = builder->createFunction("abs", ctx->getIntegerType(64), {ctx->getIntegerType(64)});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* b_neg   = builder->createBasicBlock("neg",   fn);
    ir::BasicBlock* b_ret   = builder->createBasicBlock("ret",   fn);

    builder->setInsertPoint(b_entry);
    ir::Value* v = fn->getParameters().front().get();
    ir::Value* is_neg = builder->createCslt(v, ctx->getConstantInt(ctx->getIntegerType(64), 0));
    builder->createBr(is_neg, b_neg, b_ret);

    builder->setInsertPoint(b_neg);
    ir::Instruction* slot = builder->createAlloc(
        ctx->getConstantInt(ctx->getIntegerType(64), 8), ctx->getIntegerType(64));
    builder->createStore(builder->createNeg(v), slot);
    builder->createRet(builder->createLoad(slot));

    builder->setInsertPoint(b_ret);
    builder->createRet(v);
}

// ---------------------------------------------------------------------------
// Native Collections (List, Tuple) lowered to Fyra IR using memory.alloc
// ---------------------------------------------------------------------------
void FyraBuiltinFunctions::emit_list_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto void_ty = ctx->getVoidType();
    ir::BasicBlock* old_bb = builder->getInsertPoint();

    // 1. lm_list_new(cap_hint: i64) -> i64
    ir::Function* fn_new = module->getFunction("lm_list_new");
    if (!fn_new) fn_new = builder->createFunction("lm_list_new", i64, {i64});
    if (fn_new->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_new);
        ir::BasicBlock* b_default_cap = builder->createBasicBlock("def_cap", fn_new);
        ir::BasicBlock* b_alloc = builder->createBasicBlock("alloc", fn_new);

        builder->setInsertPoint(b_entry);
        ir::Value* hint = fn_new->getParameters().front().get();
        ir::Instruction* cap_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        builder->createStore(hint, cap_slot);
        ir::Value* is_zero = builder->createCsle(hint, ctx->getConstantInt(i64, 0));
        builder->createBr(is_zero, b_default_cap, b_alloc);

        builder->setInsertPoint(b_default_cap);
        builder->createStore(ctx->getConstantInt(i64, 8), cap_slot);
        builder->createJmp(b_alloc);

        builder->setInsertPoint(b_alloc);
        ir::Value* cap = builder->createLoad(cap_slot);
        // Header: 24 bytes (len: i64, cap: i64, data_ptr: i64)
        ir::Instruction* header = builder->createExternCall("memory.alloc", {ctx->getConstantInt(i64, 24)}, i64);
        // Data buffer: cap * 8 bytes
        ir::Value* data_bytes = builder->createMul(cap, ctx->getConstantInt(i64, 8));
        ir::Instruction* data = builder->createExternCall("memory.alloc", {data_bytes}, i64);

        // header[0] = len (0)
        builder->createStore(ctx->getConstantInt(i64, 0), header);
        // header[1] = cap
        ir::Value* cap_ptr = builder->createAdd(header, ctx->getConstantInt(i64, 8));
        builder->createStore(cap, cap_ptr);
        // header[2] = data
        ir::Value* data_ptr_slot = builder->createAdd(header, ctx->getConstantInt(i64, 16));
        builder->createStore(data, data_ptr_slot);

        builder->createRet(header);
    }

    // 2. lm_list_len(list_ptr: i64) -> i64
    ir::Function* fn_len = module->getFunction("lm_list_len");
    if (!fn_len) fn_len = builder->createFunction("lm_list_len", i64, {i64});
    if (fn_len->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_len);
        builder->setInsertPoint(b_entry);
        ir::Value* list_ptr = fn_len->getParameters().front().get();
        ir::Value* len = builder->createLoad(list_ptr);
        builder->createRet(len);
    }

    // 3. lm_list_get(list_ptr: i64, index: i64) -> i64
    ir::Function* fn_get = module->getFunction("lm_list_get");
    if (!fn_get) fn_get = builder->createFunction("lm_list_get", i64, {i64, i64});
    if (fn_get->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_get);
        builder->setInsertPoint(b_entry);
        auto it = fn_get->getParameters().begin();
        ir::Value* list_ptr = it->get();
        it++;
        ir::Value* index = it->get();

        ir::Value* data_ptr_slot = builder->createAdd(list_ptr, ctx->getConstantInt(i64, 16));
        ir::Value* data = builder->createLoad(data_ptr_slot);
        ir::Value* is_tuple = builder->createCult(data, ctx->getConstantInt(i64, 65536));

        ir::BasicBlock* b_list = builder->createBasicBlock("get_list", fn_get);
        ir::BasicBlock* b_tuple = builder->createBasicBlock("get_tuple", fn_get);
        builder->createBr(is_tuple, b_tuple, b_list);

        builder->setInsertPoint(b_list);
        ir::Value* offset = builder->createMul(index, ctx->getConstantInt(i64, 8));
        ir::Value* elem_ptr = builder->createAdd(data, offset);
        ir::Value* val = builder->createLoad(elem_ptr);
        builder->createRet(val);

        builder->setInsertPoint(b_tuple);
        ir::Value* slot_idx = builder->createAdd(index, ctx->getConstantInt(i64, 1));
        ir::Value* t_offset = builder->createMul(slot_idx, ctx->getConstantInt(i64, 8));
        ir::Value* t_elem_ptr = builder->createAdd(list_ptr, t_offset);
        ir::Value* t_val = builder->createLoad(t_elem_ptr);
        builder->createRet(t_val);
    }

    // 4. lm_list_set(list_ptr: i64, index: i64, val: i64) -> void
    ir::Function* fn_set = module->getFunction("lm_list_set");
    if (!fn_set) fn_set = builder->createFunction("lm_list_set", void_ty, {i64, i64, i64});
    if (fn_set->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_set);
        ir::BasicBlock* b_realloc = builder->createBasicBlock("set_realloc", fn_set);
        ir::BasicBlock* b_copy_loop = builder->createBasicBlock("set_copy_loop", fn_set);
        ir::BasicBlock* b_copy_body = builder->createBasicBlock("set_copy_body", fn_set);
        ir::BasicBlock* b_copy_done = builder->createBasicBlock("set_copy_done", fn_set);
        ir::BasicBlock* b_update_len = builder->createBasicBlock("set_update_len", fn_set);
        ir::BasicBlock* b_store_elem = builder->createBasicBlock("set_store_elem", fn_set);

        builder->setInsertPoint(b_entry);
        auto it = fn_set->getParameters().begin();
        ir::Value* list_ptr = it->get(); it++;
        ir::Value* index = it->get(); it++;
        ir::Value* val = it->get();

        ir::Value* len = builder->createLoad(list_ptr);
        ir::Value* cap_ptr = builder->createAdd(list_ptr, ctx->getConstantInt(i64, 8));
        ir::Value* cap = builder->createLoad(cap_ptr);

        ir::Value* need_grow = builder->createCsge(index, cap);
        builder->createBr(need_grow, b_realloc, b_update_len);

        // Grow buffer
        builder->setInsertPoint(b_realloc);
        ir::Value* double_cap = builder->createMul(cap, ctx->getConstantInt(i64, 2));
        ir::Value* idx_plus_one = builder->createAdd(index, ctx->getConstantInt(i64, 1));
        ir::Value* is_double_larger = builder->createCsgt(double_cap, idx_plus_one);
        ir::Instruction* new_cap_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        builder->createStore(double_cap, new_cap_slot);

        ir::BasicBlock* b_cap_double = builder->createBasicBlock("cap_double", fn_set);
        ir::BasicBlock* b_cap_idx = builder->createBasicBlock("cap_idx", fn_set);
        builder->createBr(is_double_larger, b_cap_double, b_cap_idx);

        builder->setInsertPoint(b_cap_idx);
        builder->createStore(idx_plus_one, new_cap_slot);
        builder->createJmp(b_cap_double);

        builder->setInsertPoint(b_cap_double);
        ir::Value* new_cap = builder->createLoad(new_cap_slot);
        ir::Value* new_bytes = builder->createMul(new_cap, ctx->getConstantInt(i64, 8));
        ir::Instruction* new_data = builder->createExternCall("memory.alloc", {new_bytes}, i64);

        ir::Value* data_ptr_slot = builder->createAdd(list_ptr, ctx->getConstantInt(i64, 16));
        ir::Value* old_data = builder->createLoad(data_ptr_slot);

        ir::Instruction* k_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        builder->createStore(ctx->getConstantInt(i64, 0), k_slot);
        builder->createJmp(b_copy_loop);

        builder->setInsertPoint(b_copy_loop);
        ir::Value* k = builder->createLoad(k_slot);
        ir::Value* cond = builder->createCslt(k, len);
        builder->createBr(cond, b_copy_body, b_copy_done);

        builder->setInsertPoint(b_copy_body);
        ir::Value* k_off = builder->createMul(k, ctx->getConstantInt(i64, 8));
        ir::Value* src_p = builder->createAdd(old_data, k_off);
        ir::Value* item = builder->createLoad(src_p);
        ir::Value* dst_p = builder->createAdd(new_data, k_off);
        builder->createStore(item, dst_p);
        ir::Value* k_next = builder->createAdd(k, ctx->getConstantInt(i64, 1));
        builder->createStore(k_next, k_slot);
        builder->createJmp(b_copy_loop);

        builder->setInsertPoint(b_copy_done);
        builder->createStore(new_cap, cap_ptr);
        builder->createStore(new_data, data_ptr_slot);
        builder->createJmp(b_update_len);

        // Update len
        builder->setInsertPoint(b_update_len);
        ir::Value* cur_len = builder->createLoad(list_ptr);
        ir::Value* len_needed = builder->createAdd(index, ctx->getConstantInt(i64, 1));
        ir::Value* need_len_update = builder->createCsge(index, cur_len);

        ir::BasicBlock* b_do_update_len = builder->createBasicBlock("do_update_len", fn_set);
        builder->createBr(need_len_update, b_do_update_len, b_store_elem);

        builder->setInsertPoint(b_do_update_len);
        builder->createStore(len_needed, list_ptr);
        builder->createJmp(b_store_elem);

        builder->setInsertPoint(b_store_elem);
        ir::Value* cur_data_slot = builder->createAdd(list_ptr, ctx->getConstantInt(i64, 16));
        ir::Value* cur_data = builder->createLoad(cur_data_slot);
        ir::Value* ins_off = builder->createMul(index, ctx->getConstantInt(i64, 8));
        ir::Value* ins_ptr = builder->createAdd(cur_data, ins_off);
        builder->createStore(val, ins_ptr);
        builder->createRet(nullptr);
    }

    // 5. lm_list_append(list_ptr: i64, val: i64) -> void
    ir::Function* fn_app = module->getFunction("lm_list_append");
    if (!fn_app) fn_app = builder->createFunction("lm_list_append", void_ty, {i64, i64});
    if (fn_app->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_app);
        ir::BasicBlock* b_realloc = builder->createBasicBlock("realloc", fn_app);
        ir::BasicBlock* b_copy_loop = builder->createBasicBlock("copy_loop", fn_app);
        ir::BasicBlock* b_copy_body = builder->createBasicBlock("copy_body", fn_app);
        ir::BasicBlock* b_copy_done = builder->createBasicBlock("copy_done", fn_app);
        ir::BasicBlock* b_insert = builder->createBasicBlock("insert", fn_app);

        builder->setInsertPoint(b_entry);
        auto it = fn_app->getParameters().begin();
        ir::Value* list_ptr = it->get();
        it++;
        ir::Value* val = it->get();

        ir::Value* len = builder->createLoad(list_ptr);
        ir::Value* cap_ptr = builder->createAdd(list_ptr, ctx->getConstantInt(i64, 8));
        ir::Value* cap = builder->createLoad(cap_ptr);

        ir::Value* need_grow = builder->createCsge(len, cap);
        builder->createBr(need_grow, b_realloc, b_insert);

        // Grow buffer: new_cap = cap * 2
        builder->setInsertPoint(b_realloc);
        ir::Value* new_cap = builder->createMul(cap, ctx->getConstantInt(i64, 2));
        ir::Value* new_bytes = builder->createMul(new_cap, ctx->getConstantInt(i64, 8));
        ir::Instruction* new_data = builder->createExternCall("memory.alloc", {new_bytes}, i64);

        ir::Value* data_ptr_slot = builder->createAdd(list_ptr, ctx->getConstantInt(i64, 16));
        ir::Value* old_data = builder->createLoad(data_ptr_slot);

        ir::Instruction* k_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        builder->createStore(ctx->getConstantInt(i64, 0), k_slot);
        builder->createJmp(b_copy_loop);

        builder->setInsertPoint(b_copy_loop);
        ir::Value* k = builder->createLoad(k_slot);
        ir::Value* cond = builder->createCslt(k, len);
        builder->createBr(cond, b_copy_body, b_copy_done);

        builder->setInsertPoint(b_copy_body);
        ir::Value* k_off = builder->createMul(k, ctx->getConstantInt(i64, 8));
        ir::Value* src_p = builder->createAdd(old_data, k_off);
        ir::Value* item = builder->createLoad(src_p);
        ir::Value* dst_p = builder->createAdd(new_data, k_off);
        builder->createStore(item, dst_p);
        ir::Value* k_next = builder->createAdd(k, ctx->getConstantInt(i64, 1));
        builder->createStore(k_next, k_slot);
        builder->createJmp(b_copy_loop);

        builder->setInsertPoint(b_copy_done);
        builder->createStore(new_cap, cap_ptr);
        builder->createStore(new_data, data_ptr_slot);
        builder->createJmp(b_insert);

        builder->setInsertPoint(b_insert);
        ir::Value* cur_len = builder->createLoad(list_ptr);
        ir::Value* cur_data_slot = builder->createAdd(list_ptr, ctx->getConstantInt(i64, 16));
        ir::Value* cur_data = builder->createLoad(cur_data_slot);
        ir::Value* ins_off = builder->createMul(cur_len, ctx->getConstantInt(i64, 8));
        ir::Value* ins_ptr = builder->createAdd(cur_data, ins_off);
        builder->createStore(val, ins_ptr);
        ir::Value* next_len = builder->createAdd(cur_len, ctx->getConstantInt(i64, 1));
        builder->createStore(next_len, list_ptr);
        builder->createRet(nullptr);
    }

    // 5b. lm_channel_pop(list_ptr: i64) -> i64
    ir::Function* fn_pop = module->getFunction("lm_channel_pop");
    if (!fn_pop) fn_pop = builder->createFunction("lm_channel_pop", i64, {i64});
    if (fn_pop->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_pop);
        ir::BasicBlock* b_empty = builder->createBasicBlock("empty", fn_pop);
        ir::BasicBlock* b_pop   = builder->createBasicBlock("pop", fn_pop);
        ir::BasicBlock* b_shift_loop = builder->createBasicBlock("shift_loop", fn_pop);
        ir::BasicBlock* b_shift_body = builder->createBasicBlock("shift_body", fn_pop);
        ir::BasicBlock* b_shift_done = builder->createBasicBlock("shift_done", fn_pop);

        builder->setInsertPoint(b_entry);
        ir::Value* list_ptr = fn_pop->getParameters().front().get();

        ir::Value* len = builder->createLoad(list_ptr);
        ir::Value* is_empty = builder->createCsle(len, ctx->getConstantInt(i64, 0));
        builder->createBr(is_empty, b_empty, b_pop);

        builder->setInsertPoint(b_empty);
        // Return VAL_NIL (0x7FFFFFFFFFFFFFFF) when empty
        builder->createRet(ctx->getConstantInt(i64, 0x7FFFFFFFFFFFFFFF));

        builder->setInsertPoint(b_pop);
        ir::Value* data_ptr_slot = builder->createAdd(list_ptr, ctx->getConstantInt(i64, 16));
        ir::Value* data = builder->createLoad(data_ptr_slot);
        ir::Value* ret_val = builder->createLoad(data);

        ir::Value* new_len = builder->createSub(len, ctx->getConstantInt(i64, 1));
        builder->createStore(new_len, list_ptr);

        ir::Instruction* k_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        builder->createStore(ctx->getConstantInt(i64, 0), k_slot);
        builder->createJmp(b_shift_loop);

        builder->setInsertPoint(b_shift_loop);
        ir::Value* k = builder->createLoad(k_slot);
        ir::Value* cond = builder->createCslt(k, new_len);
        builder->createBr(cond, b_shift_body, b_shift_done);

        builder->setInsertPoint(b_shift_body);
        ir::Value* src_idx = builder->createAdd(k, ctx->getConstantInt(i64, 1));
        ir::Value* src_off = builder->createMul(src_idx, ctx->getConstantInt(i64, 8));
        ir::Value* src_ptr = builder->createAdd(data, src_off);
        ir::Value* item = builder->createLoad(src_ptr);

        ir::Value* dst_off = builder->createMul(k, ctx->getConstantInt(i64, 8));
        ir::Value* dst_ptr = builder->createAdd(data, dst_off);
        builder->createStore(item, dst_ptr);

        ir::Value* next_k = builder->createAdd(k, ctx->getConstantInt(i64, 1));
        builder->createStore(next_k, k_slot);
        builder->createJmp(b_shift_loop);

        builder->setInsertPoint(b_shift_done);
        builder->createRet(ret_val);
    }

    // 6. lm_list_to_str(list_ptr: i64) -> i64
    ir::Function* fn_l2s = module->getFunction("lm_list_to_str");
    if (!fn_l2s) fn_l2s = builder->createFunction("lm_list_to_str", i64, {i64});
    if (fn_l2s->getBasicBlocks().empty()) {
        emit_str_concat_ir(module, builder);
        ir::Function* fn_concat = module->getFunction("lm_str_concat");

        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_l2s);
        ir::BasicBlock* b_loop = builder->createBasicBlock("loop", fn_l2s);
        ir::BasicBlock* b_body = builder->createBasicBlock("body", fn_l2s);
        ir::BasicBlock* b_next = builder->createBasicBlock("next", fn_l2s);
        ir::BasicBlock* b_done = builder->createBasicBlock("done", fn_l2s);

        builder->setInsertPoint(b_entry);
        ir::Value* list_ptr = fn_l2s->getParameters().front().get();

        ir::Instruction* res_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        ir::Instruction* i_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        ir::Instruction* elem_str_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);

        ir::Value* count = builder->createLoad(list_ptr);
        ir::Value* data_slot = builder->createAdd(list_ptr, ctx->getConstantInt(i64, 16));
        ir::Value* data = builder->createLoad(data_slot);

        ir::GlobalVariable* gv_lbracket = get_or_create_global_str(module, builder, "list_lbracket", "[");
        builder->createStore(gv_lbracket, res_slot);
        builder->createStore(ctx->getConstantInt(i64, 0), i_slot);
        builder->createJmp(b_loop);

        builder->setInsertPoint(b_loop);
        ir::Value* i = builder->createLoad(i_slot);
        ir::Value* cond = builder->createCslt(i, count);
        builder->createBr(cond, b_body, b_done);

        builder->setInsertPoint(b_body);
        ir::BasicBlock* b_sep = builder->createBasicBlock("sep", fn_l2s);
        ir::BasicBlock* b_elem = builder->createBasicBlock("elem", fn_l2s);

        ir::Value* is_first = builder->createCeq(i, ctx->getConstantInt(i64, 0));
        builder->createBr(is_first, b_elem, b_sep);

        builder->setInsertPoint(b_sep);
        ir::GlobalVariable* gv_comma = get_or_create_global_str(module, builder, "list_comma", ", ");
        ir::Value* cur_res = builder->createLoad(res_slot);
        ir::Value* new_res = builder->createCall(fn_concat, {cur_res, gv_comma});
        builder->createStore(new_res, res_slot);
        builder->createJmp(b_elem);

        builder->setInsertPoint(b_elem);
        ir::Value* elem_off = builder->createMul(i, ctx->getConstantInt(i64, 8));
        ir::Value* elem_addr = builder->createAdd(data, elem_off);
        ir::Value* elem_val = builder->createLoad(elem_addr);

        ir::BasicBlock* b_e_num = builder->createBasicBlock("e_num", fn_l2s);
        ir::BasicBlock* b_e_ptr = builder->createBasicBlock("e_ptr", fn_l2s);
        ir::BasicBlock* b_e_done = builder->createBasicBlock("e_done", fn_l2s);

        ir::Value* is_ge_ptr = builder->createCuge(elem_val, ctx->getConstantInt(i64, 65536));
        ir::Value* high_bits = builder->createShr(elem_val, ctx->getConstantInt(i64, 48));
        ir::Value* high_zero = builder->createCeq(high_bits, ctx->getConstantInt(i64, 0));
        ir::Value* is_not_smi = builder->createCeq(builder->createAnd(elem_val, ctx->getConstantInt(i64, 1)), ctx->getConstantInt(i64, 0));
        ir::Value* is_valid_ptr = builder->createAnd(builder->createAnd(is_ge_ptr, high_zero), is_not_smi);

        builder->createBr(is_valid_ptr, b_e_ptr, b_e_num);

        builder->setInsertPoint(b_e_num);
        ir::Value* estr_num = emit_int_to_str_inline(module, builder, elem_val);
        builder->createStore(estr_num, elem_str_slot);
        builder->createJmp(b_e_done);

        builder->setInsertPoint(b_e_ptr);
        ir::BasicBlock* b_e_enum = builder->createBasicBlock("e_enum", fn_l2s);
        ir::BasicBlock* b_e_str = builder->createBasicBlock("e_str", fn_l2s);

        ir::Value* e_magic = builder->createLoad(elem_val);
        ir::Value* e_is_enum = builder->createCeq(e_magic, ctx->getConstantInt(i64, 0x454E554D));
        builder->createBr(e_is_enum, b_e_enum, b_e_str);

        builder->setInsertPoint(b_e_enum);
        ir::Function* fn_enum_to_str = module->getFunction("lm_enum_to_str");
        if (fn_enum_to_str) {
            ir::Value* estr_enum = builder->createCall(fn_enum_to_str, {elem_val});
            builder->createStore(estr_enum, elem_str_slot);
        } else {
            builder->createStore(elem_val, elem_str_slot);
        }
        builder->createJmp(b_e_done);

        builder->setInsertPoint(b_e_str);
        builder->createStore(elem_val, elem_str_slot);
        builder->createJmp(b_e_done);

        builder->setInsertPoint(b_e_done);
        ir::Value* formatted_elem = builder->createLoad(elem_str_slot);
        ir::Value* acc_res = builder->createLoad(res_slot);
        ir::Value* combined = builder->createCall(fn_concat, {acc_res, formatted_elem});
        builder->createStore(combined, res_slot);
        builder->createJmp(b_next);

        builder->setInsertPoint(b_next);
        ir::Value* next_i = builder->createAdd(i, ctx->getConstantInt(i64, 1));
        builder->createStore(next_i, i_slot);
        builder->createJmp(b_loop);

        builder->setInsertPoint(b_done);
        ir::GlobalVariable* gv_rbracket = get_or_create_global_str(module, builder, "list_rbracket", "]");
        ir::Value* final_res = builder->createCall(fn_concat, {builder->createLoad(res_slot), gv_rbracket});
        builder->createRet(final_res);
    }

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_tuple_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto void_ty = ctx->getVoidType();
    ir::BasicBlock* old_bb = builder->getInsertPoint();

    // 1. lm_tuple_new(size: i64) -> i64
    ir::Function* fn_new = module->getFunction("lm_tuple_new");
    if (!fn_new) fn_new = builder->createFunction("lm_tuple_new", i64, {i64});
    if (fn_new->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_new);
        builder->setInsertPoint(b_entry);
        ir::Value* size = fn_new->getParameters().front().get();
        ir::Value* total_slots = builder->createAdd(size, ctx->getConstantInt(i64, 1));
        ir::Value* total_bytes = builder->createMul(total_slots, ctx->getConstantInt(i64, 8));
        ir::Instruction* ptr = builder->createExternCall("memory.alloc", {total_bytes}, i64);
        builder->createStore(size, ptr);
        builder->createRet(ptr);
    }

    // 2. lm_tuple_get(tuple_ptr: i64, index: i64) -> i64
    ir::Function* fn_get = module->getFunction("lm_tuple_get");
    if (!fn_get) fn_get = builder->createFunction("lm_tuple_get", i64, {i64, i64});
    if (fn_get->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_get);
        builder->setInsertPoint(b_entry);
        auto it = fn_get->getParameters().begin();
        ir::Value* tuple_ptr = it->get();
        it++;
        ir::Value* index = it->get();
        ir::Value* slot_idx = builder->createAdd(index, ctx->getConstantInt(i64, 1));
        ir::Value* offset = builder->createMul(slot_idx, ctx->getConstantInt(i64, 8));
        ir::Value* elem_ptr = builder->createAdd(tuple_ptr, offset);
        ir::Value* val = builder->createLoad(elem_ptr);
        builder->createRet(val);
    }

    // 3. lm_tuple_set(tuple_ptr: i64, index: i64, val: i64) -> void
    ir::Function* fn_set = module->getFunction("lm_tuple_set");
    if (!fn_set) fn_set = builder->createFunction("lm_tuple_set", void_ty, {i64, i64, i64});
    if (fn_set->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_set);
        builder->setInsertPoint(b_entry);
        auto it = fn_set->getParameters().begin();
        ir::Value* tuple_ptr = it->get();
        it++;
        ir::Value* index = it->get();
        it++;
        ir::Value* val = it->get();
        ir::Value* slot_idx = builder->createAdd(index, ctx->getConstantInt(i64, 1));
        ir::Value* offset = builder->createMul(slot_idx, ctx->getConstantInt(i64, 8));
        ir::Value* elem_ptr = builder->createAdd(tuple_ptr, offset);
        builder->createStore(val, elem_ptr);
        builder->createRet(nullptr);
    }

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_dict_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto void_ty = ctx->getVoidType();
    ir::BasicBlock* old_bb = builder->getInsertPoint();

    // 0. lm_key_eq(k1: i64, k2: i64) -> i64 (bool)
    ir::Function* fn_eq = module->getFunction("lm_key_eq");
    if (!fn_eq) fn_eq = builder->createFunction("lm_key_eq", i64, {i64, i64});
    if (fn_eq->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_eq);
        ir::BasicBlock* b_ptrcmp = builder->createBasicBlock("ptrcmp", fn_eq);
        ir::BasicBlock* b_loop_init = builder->createBasicBlock("loop_init", fn_eq);
        ir::BasicBlock* b_loop_cond = builder->createBasicBlock("loop_cond", fn_eq);
        ir::BasicBlock* b_check_end = builder->createBasicBlock("check_end", fn_eq);
        ir::BasicBlock* b_advance = builder->createBasicBlock("advance", fn_eq);
        ir::BasicBlock* b_ret_true = builder->createBasicBlock("ret_true", fn_eq);
        ir::BasicBlock* b_ret_false = builder->createBasicBlock("ret_false", fn_eq);

        builder->setInsertPoint(b_entry);
        auto it = fn_eq->getParameters().begin();
        ir::Value* k1 = it->get(); it++;
        ir::Value* k2 = it->get();

        ir::Value* ptr_eq = builder->createCeq(k1, k2);
        builder->createBr(ptr_eq, b_ret_true, b_ptrcmp);

        builder->setInsertPoint(b_ptrcmp);
        ir::Value* k1_ge = builder->createCuge(k1, ctx->getConstantInt(i64, 65536));
        ir::Value* k1_pos = builder->createCsgt(k1, ctx->getConstantInt(i64, 0));
        ir::Value* k1_not_nil = builder->createCne(k1, ctx->getConstantInt(i64, 0x7FFFFFFFFFFFFFFF));
        ir::Value* is_ptr1 = builder->createAnd(builder->createAnd(k1_ge, k1_pos), k1_not_nil);

        ir::Value* k2_ge = builder->createCuge(k2, ctx->getConstantInt(i64, 65536));
        ir::Value* k2_pos = builder->createCsgt(k2, ctx->getConstantInt(i64, 0));
        ir::Value* k2_not_nil = builder->createCne(k2, ctx->getConstantInt(i64, 0x7FFFFFFFFFFFFFFF));
        ir::Value* is_ptr2 = builder->createAnd(builder->createAnd(k2_ge, k2_pos), k2_not_nil);

        ir::Value* both_ptr = builder->createAnd(is_ptr1, is_ptr2);
        ir::BasicBlock* b_chk_enum = builder->createBasicBlock("chk_enum", fn_eq);
        builder->createBr(both_ptr, b_chk_enum, b_ret_false);

        builder->setInsertPoint(b_chk_enum);
        ir::Value* t1_raw = builder->createLoad(k1);
        ir::Value* t2_raw = builder->createLoad(k2);
        ir::Value* type1  = builder->createAnd(t1_raw, ctx->getConstantInt(i64, 0xFFFFFFFF));
        ir::Value* type2  = builder->createAnd(t2_raw, ctx->getConstantInt(i64, 0xFFFFFFFF));

        ir::Value* is_str1 = builder->createCeq(type1, ctx->getConstantInt(i64, 11));
        ir::Value* is_str2 = builder->createCeq(type2, ctx->getConstantInt(i64, 11));
        ir::Value* both_str = builder->createAnd(is_str1, is_str2);

        ir::BasicBlock* b_str_cmp = builder->createBasicBlock("str_hdr_cmp", fn_eq);
        ir::BasicBlock* b_enum_chk = builder->createBasicBlock("enum_chk", fn_eq);
        builder->createBr(both_str, b_str_cmp, b_enum_chk);

        // String Header Comparison
        builder->setInsertPoint(b_str_cmp);
        ir::Value* slen1 = builder->createLoad(builder->createAdd(k1, ctx->getConstantInt(i64, 8)));
        ir::Value* slen2 = builder->createLoad(builder->createAdd(k2, ctx->getConstantInt(i64, 8)));
        ir::Value* lens_eq = builder->createCeq(slen1, slen2);
        
        ir::BasicBlock* b_str_bytes = builder->createBasicBlock("str_hdr_bytes", fn_eq);
        builder->createBr(lens_eq, b_str_bytes, b_ret_false);

        builder->setInsertPoint(b_str_bytes);
        ir::Instruction* sidx_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        builder->createStore(ctx->getConstantInt(i64, 0), sidx_slot);
        
        ir::BasicBlock* b_sloop = builder->createBasicBlock("str_hdr_loop", fn_eq);
        ir::BasicBlock* b_sbody = builder->createBasicBlock("str_hdr_body", fn_eq);
        builder->createJmp(b_sloop);

        builder->setInsertPoint(b_sloop);
        ir::Value* si = builder->createLoad(sidx_slot);
        ir::Value* sdone = builder->createCsge(si, slen1);
        builder->createBr(sdone, b_ret_true, b_sbody);

        builder->setInsertPoint(b_sbody);
        ir::Value* sc1 = builder->createLoadub(builder->createAdd(builder->createAdd(k1, ctx->getConstantInt(i64, 24)), si));
        ir::Value* sc2 = builder->createLoadub(builder->createAdd(builder->createAdd(k2, ctx->getConstantInt(i64, 24)), si));
        ir::Value* sdiff = builder->createCne(sc1, sc2);
        builder->createStore(builder->createAdd(si, ctx->getConstantInt(i64, 1)), sidx_slot);
        builder->createBr(sdiff, b_ret_false, b_sloop);

        // Enum / Fallback comparison
        builder->setInsertPoint(b_enum_chk);
        ir::Value* is_enum1 = builder->createCeq(t1_raw, ctx->getConstantInt(i64, 0x454E554D));
        ir::Value* is_enum2 = builder->createCeq(t2_raw, ctx->getConstantInt(i64, 0x454E554D));
        ir::Value* both_enum = builder->createAnd(is_enum1, is_enum2);
        ir::Value* either_enum = builder->createOr(is_enum1, is_enum2);

        ir::BasicBlock* b_enum_only = builder->createBasicBlock("enum_only", fn_eq);
        builder->createBr(either_enum, b_enum_only, b_loop_init);

        builder->setInsertPoint(b_enum_only);
        ir::BasicBlock* b_enum_cmp = builder->createBasicBlock("enum_cmp", fn_eq);
        builder->createBr(both_enum, b_enum_cmp, b_ret_false);

        builder->setInsertPoint(b_enum_cmp);
        ir::Value* tag1 = builder->createLoad(builder->createAdd(k1, ctx->getConstantInt(i64, 8)));
        ir::Value* tag2 = builder->createLoad(builder->createAdd(k2, ctx->getConstantInt(i64, 8)));
        ir::Value* tags_eq = builder->createCeq(tag1, tag2);

        ir::BasicBlock* b_pay_cmp = builder->createBasicBlock("pay_cmp", fn_eq);
        builder->createBr(tags_eq, b_pay_cmp, b_ret_false);

        builder->setInsertPoint(b_pay_cmp);
        ir::Value* pay1 = builder->createLoad(builder->createAdd(k1, ctx->getConstantInt(i64, 16)));
        ir::Value* pay2 = builder->createLoad(builder->createAdd(k2, ctx->getConstantInt(i64, 16)));
        ir::Value* pays_eq = builder->createCeq(pay1, pay2);
        builder->createRet(pays_eq);

        builder->setInsertPoint(b_loop_init);
        ir::Instruction* idx_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        builder->createStore(ctx->getConstantInt(i64, 0), idx_slot);
        builder->createJmp(b_loop_cond);

        builder->setInsertPoint(b_loop_cond);
        ir::Value* idx = builder->createLoad(idx_slot);
        ir::Value* p1 = builder->createAdd(k1, idx);
        ir::Value* p2 = builder->createAdd(k2, idx);
        ir::Value* c1 = builder->createLoadub(p1);
        ir::Value* c2 = builder->createLoadub(p2);
        ir::Value* chars_diff = builder->createCne(c1, c2);
        builder->createBr(chars_diff, b_ret_false, b_check_end);

        builder->setInsertPoint(b_check_end);
        ir::Value* is_end = builder->createCeq(c1, ctx->getConstantInt(ctx->getIntegerType(8), 0));
        builder->createBr(is_end, b_ret_true, b_advance);

        builder->setInsertPoint(b_advance);
        ir::Value* next_idx = builder->createAdd(idx, ctx->getConstantInt(i64, 1));
        builder->createStore(next_idx, idx_slot);
        builder->createJmp(b_loop_cond);

        builder->setInsertPoint(b_ret_true);
        builder->createRet(ctx->getConstantInt(i64, 1));

        builder->setInsertPoint(b_ret_false);
        builder->createRet(ctx->getConstantInt(i64, 0));
    }

    // 1. lm_dict_new() -> i64
    ir::Function* fn_new = module->getFunction("lm_dict_new");
    if (!fn_new) fn_new = builder->createFunction("lm_dict_new", i64, {});
    if (fn_new->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_new);
        ir::BasicBlock* b_init_loop = builder->createBasicBlock("init_loop", fn_new);
        ir::BasicBlock* b_init_body = builder->createBasicBlock("init_body", fn_new);
        ir::BasicBlock* b_done = builder->createBasicBlock("init_done", fn_new);

        builder->setInsertPoint(b_entry);
        // Header: 32 bytes (count, cap, keys_ptr, vals_ptr)
        ir::Instruction* header = builder->createExternCall("memory.alloc", {ctx->getConstantInt(i64, 32)}, i64);
        // Buffers: 32 entries * 8 bytes = 256 bytes
        ir::Instruction* keys = builder->createExternCall("memory.alloc", {ctx->getConstantInt(i64, 256)}, i64);
        ir::Instruction* vals = builder->createExternCall("memory.alloc", {ctx->getConstantInt(i64, 256)}, i64);

        // header[0] = 0 (count)
        builder->createStore(ctx->getConstantInt(i64, 0), header);
        // header[1] = 32 (cap)
        ir::Value* cap_ptr = builder->createAdd(header, ctx->getConstantInt(i64, 8));
        builder->createStore(ctx->getConstantInt(i64, 32), cap_ptr);
        // header[2] = keys
        ir::Value* keys_slot = builder->createAdd(header, ctx->getConstantInt(i64, 16));
        builder->createStore(keys, keys_slot);
        // header[3] = vals
        ir::Value* vals_slot = builder->createAdd(header, ctx->getConstantInt(i64, 24));
        builder->createStore(vals, vals_slot);

        ir::Instruction* i_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        builder->createStore(ctx->getConstantInt(i64, 0), i_slot);
        builder->createJmp(b_init_loop);

        builder->setInsertPoint(b_init_loop);
        ir::Value* i = builder->createLoad(i_slot);
        ir::Value* cond = builder->createCslt(i, ctx->getConstantInt(i64, 32));
        builder->createBr(cond, b_init_body, b_done);

        builder->setInsertPoint(b_init_body);
        ir::Value* k_off = builder->createMul(i, ctx->getConstantInt(i64, 8));
        ir::Value* k_dst = builder->createAdd(keys, k_off);
        builder->createStore(ctx->getConstantInt(i64, 0), k_dst);
        ir::Value* next_i = builder->createAdd(i, ctx->getConstantInt(i64, 1));
        builder->createStore(next_i, i_slot);
        builder->createJmp(b_init_loop);

        builder->setInsertPoint(b_done);
        builder->createRet(header);
    }

    // 2. lm_dict_set(dict_ptr: i64, key: i64, val: i64) -> void
    ir::Function* fn_set = module->getFunction("lm_dict_set");
    if (!fn_set) fn_set = builder->createFunction("lm_dict_set", void_ty, {i64, i64, i64});
    if (fn_set->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_set);
        ir::BasicBlock* b_loop = builder->createBasicBlock("loop", fn_set);
        ir::BasicBlock* b_check = builder->createBasicBlock("check", fn_set);
        ir::BasicBlock* b_update = builder->createBasicBlock("update", fn_set);
        ir::BasicBlock* b_next = builder->createBasicBlock("next", fn_set);
        ir::BasicBlock* b_insert = builder->createBasicBlock("insert", fn_set);
        ir::BasicBlock* b_done = builder->createBasicBlock("done", fn_set);

        builder->setInsertPoint(b_entry);
        auto it = fn_set->getParameters().begin();
        ir::Value* dict_ptr = it->get(); it++;
        ir::Value* key = it->get(); it++;
        ir::Value* val = it->get();

        ir::Value* dict_is_null = builder->createCeq(dict_ptr, ctx->getConstantInt(i64, 0));
        ir::BasicBlock* b_valid_dict = builder->createBasicBlock("valid_dict", fn_set);
        builder->createBr(dict_is_null, b_done, b_valid_dict);

        builder->setInsertPoint(b_valid_dict);
        ir::Value* count = builder->createLoad(dict_ptr);
        ir::Value* keys_slot = builder->createAdd(dict_ptr, ctx->getConstantInt(i64, 16));
        ir::Value* keys = builder->createLoad(keys_slot);
        ir::Value* vals_slot = builder->createAdd(dict_ptr, ctx->getConstantInt(i64, 24));
        ir::Value* vals = builder->createLoad(vals_slot);

        ir::Instruction* i_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        builder->createStore(ctx->getConstantInt(i64, 0), i_slot);
        builder->createJmp(b_loop);

        builder->setInsertPoint(b_loop);
        ir::Value* i = builder->createLoad(i_slot);
        ir::Value* cond = builder->createCslt(i, count);
        builder->createBr(cond, b_check, b_insert);

        builder->setInsertPoint(b_check);
        ir::Value* k_off = builder->createMul(i, ctx->getConstantInt(i64, 8));
        ir::Value* k_addr = builder->createAdd(keys, k_off);
        ir::Value* curr_k = builder->createLoad(k_addr);

        ir::Value* is_match = builder->createCall(fn_eq, {curr_k, key});
        builder->createBr(is_match, b_update, b_next);

        builder->setInsertPoint(b_update);
        ir::Value* v_addr_upd = builder->createAdd(vals, k_off);
        builder->createStore(val, v_addr_upd);
        builder->createRet(nullptr);

        builder->setInsertPoint(b_next);
        ir::Value* next_i = builder->createAdd(i, ctx->getConstantInt(i64, 1));
        builder->createStore(next_i, i_slot);
        builder->createJmp(b_loop);

        // Insertion at slot = count (insertion-order)
        builder->setInsertPoint(b_insert);
        ir::Value* ins_off = builder->createMul(count, ctx->getConstantInt(i64, 8));
        ir::Value* ins_k_addr = builder->createAdd(keys, ins_off);
        ir::Value* ins_v_addr = builder->createAdd(vals, ins_off);
        builder->createStore(key, ins_k_addr);
        builder->createStore(val, ins_v_addr);

        ir::Value* new_cnt = builder->createAdd(count, ctx->getConstantInt(i64, 1));
        builder->createStore(new_cnt, dict_ptr);
        builder->createRet(nullptr);

        builder->setInsertPoint(b_done);
        builder->createRet(nullptr);
    }

    // 3. lm_dict_get(dict_ptr: i64, key: i64) -> i64
    ir::Function* fn_get = module->getFunction("lm_dict_get");
    if (!fn_get) fn_get = builder->createFunction("lm_dict_get", i64, {i64, i64});
    if (fn_get->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_get);
        ir::BasicBlock* b_loop = builder->createBasicBlock("loop", fn_get);
        ir::BasicBlock* b_check = builder->createBasicBlock("check", fn_get);
        ir::BasicBlock* b_found = builder->createBasicBlock("found", fn_get);
        ir::BasicBlock* b_next = builder->createBasicBlock("next", fn_get);
        ir::BasicBlock* b_not_found = builder->createBasicBlock("not_found", fn_get);

        builder->setInsertPoint(b_entry);
        auto it = fn_get->getParameters().begin();
        ir::Value* dict_ptr = it->get(); it++;
        ir::Value* key = it->get();

        ir::Value* get_dict_null = builder->createCeq(dict_ptr, ctx->getConstantInt(i64, 0));
        ir::BasicBlock* b_valid_get = builder->createBasicBlock("valid_get", fn_get);
        builder->createBr(get_dict_null, b_not_found, b_valid_get);

        builder->setInsertPoint(b_valid_get);
        ir::Value* keys_slot = builder->createAdd(dict_ptr, ctx->getConstantInt(i64, 16));
        ir::Value* keys = builder->createLoad(keys_slot);
        ir::Value* vals_slot = builder->createAdd(dict_ptr, ctx->getConstantInt(i64, 24));
        ir::Value* vals = builder->createLoad(vals_slot);
        ir::Value* cap_ptr = builder->createAdd(dict_ptr, ctx->getConstantInt(i64, 8));
        ir::Value* cap = builder->createLoad(cap_ptr);

        ir::Instruction* i_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        builder->createStore(ctx->getConstantInt(i64, 0), i_slot);
        builder->createJmp(b_loop);

        builder->setInsertPoint(b_loop);
        ir::Value* i = builder->createLoad(i_slot);
        ir::Value* cond = builder->createCslt(i, cap);
        builder->createBr(cond, b_check, b_not_found);

        builder->setInsertPoint(b_check);
        ir::Value* k_off = builder->createMul(i, ctx->getConstantInt(i64, 8));
        ir::Value* k_addr = builder->createAdd(keys, k_off);
        ir::Value* curr_k = builder->createLoad(k_addr);

        ir::Value* is_null = builder->createCeq(curr_k, ctx->getConstantInt(i64, 0));
        ir::BasicBlock* b_cmp = builder->createBasicBlock("dict_get_cmp", fn_get);
        builder->createBr(is_null, b_next, b_cmp);

        builder->setInsertPoint(b_cmp);
        ir::Value* is_match = builder->createCall(fn_eq, {curr_k, key});
        builder->createBr(is_match, b_found, b_next);

        builder->setInsertPoint(b_found);
        ir::Value* v_addr = builder->createAdd(vals, k_off);
        ir::Value* val = builder->createLoad(v_addr);
        builder->createRet(val);

        builder->setInsertPoint(b_next);
        ir::Value* next_i = builder->createAdd(i, ctx->getConstantInt(i64, 1));
        builder->createStore(next_i, i_slot);
        builder->createJmp(b_loop);

        builder->setInsertPoint(b_not_found);
        builder->createRet(ctx->getConstantInt(i64, 0));
    }

    // 4. lm_dict_has(dict_ptr: i64, key: i64) -> i64
    ir::Function* fn_has = module->getFunction("lm_dict_has");
    if (!fn_has) fn_has = builder->createFunction("lm_dict_has", i64, {i64, i64});
    if (fn_has->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_has);
        ir::BasicBlock* b_loop = builder->createBasicBlock("loop", fn_has);
        ir::BasicBlock* b_check = builder->createBasicBlock("check", fn_has);
        ir::BasicBlock* b_found = builder->createBasicBlock("found", fn_has);
        ir::BasicBlock* b_next = builder->createBasicBlock("next", fn_has);
        ir::BasicBlock* b_not_found = builder->createBasicBlock("not_found", fn_has);

        builder->setInsertPoint(b_entry);
        auto it = fn_has->getParameters().begin();
        ir::Value* dict_ptr = it->get(); it++;
        ir::Value* key = it->get();

        ir::Value* keys_slot = builder->createAdd(dict_ptr, ctx->getConstantInt(i64, 16));
        ir::Value* keys = builder->createLoad(keys_slot);
        ir::Value* cap_ptr = builder->createAdd(dict_ptr, ctx->getConstantInt(i64, 8));
        ir::Value* cap = builder->createLoad(cap_ptr);

        ir::Instruction* i_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        builder->createStore(ctx->getConstantInt(i64, 0), i_slot);
        builder->createJmp(b_loop);

        builder->setInsertPoint(b_loop);
        ir::Value* i = builder->createLoad(i_slot);
        ir::Value* cond = builder->createCslt(i, cap);
        builder->createBr(cond, b_check, b_not_found);

        builder->setInsertPoint(b_check);
        ir::Value* k_off = builder->createMul(i, ctx->getConstantInt(i64, 8));
        ir::Value* k_addr = builder->createAdd(keys, k_off);
        ir::Value* curr_k = builder->createLoad(k_addr);

        ir::Value* is_null = builder->createCeq(curr_k, ctx->getConstantInt(i64, 0));
        ir::BasicBlock* b_cmp = builder->createBasicBlock("dict_has_cmp", fn_has);
        builder->createBr(is_null, b_next, b_cmp);

        builder->setInsertPoint(b_cmp);
        ir::Value* is_match = builder->createCall(fn_eq, {curr_k, key});
        builder->createBr(is_match, b_found, b_next);

        builder->setInsertPoint(b_found);
        builder->createRet(ctx->getConstantInt(i64, 1));

        builder->setInsertPoint(b_next);
        ir::Value* next_i = builder->createAdd(i, ctx->getConstantInt(i64, 1));
        builder->createStore(next_i, i_slot);
        builder->createJmp(b_loop);

        builder->setInsertPoint(b_not_found);
        builder->createRet(ctx->getConstantInt(i64, 0));
    }

    // 5. lm_dict_items(dict_ptr: i64) -> i64
    ir::Function* fn_items = module->getFunction("lm_dict_items");
    if (!fn_items) fn_items = builder->createFunction("lm_dict_items", i64, {i64});
    if (fn_items->getBasicBlocks().empty()) {
        emit_list_ir(module, builder);
        emit_tuple_ir(module, builder);

        ir::Function* fn_list_new = module->getFunction("lm_list_new");
        if (!fn_list_new) fn_list_new = builder->createFunction("lm_list_new", i64, {i64});
        ir::Function* fn_list_app = module->getFunction("lm_list_append");
        if (!fn_list_app) fn_list_app = builder->createFunction("lm_list_append", void_ty, {i64, i64});
        ir::Function* fn_tup_new = module->getFunction("lm_tuple_new");
        if (!fn_tup_new) fn_tup_new = builder->createFunction("lm_tuple_new", i64, {i64});
        ir::Function* fn_tup_set = module->getFunction("lm_tuple_set");
        if (!fn_tup_set) fn_tup_set = builder->createFunction("lm_tuple_set", void_ty, {i64, i64, i64});

        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_items);
        ir::BasicBlock* b_loop = builder->createBasicBlock("loop", fn_items);
        ir::BasicBlock* b_check = builder->createBasicBlock("check", fn_items);
        ir::BasicBlock* b_add_item = builder->createBasicBlock("add_item", fn_items);
        ir::BasicBlock* b_next = builder->createBasicBlock("next", fn_items);
        ir::BasicBlock* b_done = builder->createBasicBlock("done", fn_items);

        builder->setInsertPoint(b_entry);
        ir::Value* dict_ptr = fn_items->getParameters().front().get();

        ir::Value* count = builder->createLoad(dict_ptr);
        ir::Value* list_ptr = builder->createCall(fn_list_new, {count});

        ir::Value* cap_ptr = builder->createAdd(dict_ptr, ctx->getConstantInt(i64, 8));
        ir::Value* cap = builder->createLoad(cap_ptr);
        ir::Value* keys_slot = builder->createAdd(dict_ptr, ctx->getConstantInt(i64, 16));
        ir::Value* keys = builder->createLoad(keys_slot);
        ir::Value* vals_slot = builder->createAdd(dict_ptr, ctx->getConstantInt(i64, 24));
        ir::Value* vals = builder->createLoad(vals_slot);

        ir::Instruction* i_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        builder->createStore(ctx->getConstantInt(i64, 0), i_slot);
        builder->createJmp(b_loop);

        builder->setInsertPoint(b_loop);
        ir::Value* i = builder->createLoad(i_slot);
        ir::Value* cond = builder->createCslt(i, count);
        builder->createBr(cond, b_check, b_done);

        builder->setInsertPoint(b_check);
        ir::Value* k_off = builder->createMul(i, ctx->getConstantInt(i64, 8));
        ir::Value* k_addr = builder->createAdd(keys, k_off);
        ir::Value* curr_k = builder->createLoad(k_addr);

        ir::Value* is_null = builder->createCeq(curr_k, ctx->getConstantInt(i64, 0));
        builder->createBr(is_null, b_next, b_add_item);

        builder->setInsertPoint(b_add_item);
        ir::Value* v_addr = builder->createAdd(vals, k_off);
        ir::Value* curr_v = builder->createLoad(v_addr);

        ir::Value* tup_ptr = builder->createCall(fn_tup_new, {ctx->getConstantInt(i64, 2)});
        builder->createCall(fn_tup_set, {tup_ptr, ctx->getConstantInt(i64, 0), curr_k});
        builder->createCall(fn_tup_set, {tup_ptr, ctx->getConstantInt(i64, 1), curr_v});

        builder->createCall(fn_list_app, {list_ptr, tup_ptr});
        builder->createJmp(b_next);

        builder->setInsertPoint(b_next);
        ir::Value* next_i = builder->createAdd(i, ctx->getConstantInt(i64, 1));
        builder->createStore(next_i, i_slot);
        builder->createJmp(b_loop);

        builder->setInsertPoint(b_done);
        builder->createRet(list_ptr);
    }

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_enum_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    ir::BasicBlock* old_bb = builder->getInsertPoint();

    // 1. lm_enum_new(tag: i64, payload: i64, vname: i64) -> i64
    ir::Function* fn_new = module->getFunction("lm_enum_new");
    if (!fn_new) fn_new = builder->createFunction("lm_enum_new", i64, {i64, i64, i64});
    if (fn_new->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_new);
        builder->setInsertPoint(b_entry);
        auto it = fn_new->getParameters().begin();
        ir::Value* tag = it->get(); it++;
        ir::Value* payload = it->get(); it++;
        ir::Value* vname = it->get();

        // Enum header: 32 bytes (magic: 0x454E554D, tag: i64, payload: i64, vname: i64)
        ir::Instruction* ptr = builder->createExternCall("memory.alloc", {ctx->getConstantInt(i64, 32)}, i64);
        builder->createStore(ctx->getConstantInt(i64, 0x454E554D), ptr);
        ir::Value* tag_ptr = builder->createAdd(ptr, ctx->getConstantInt(i64, 8));
        builder->createStore(tag, tag_ptr);
        ir::Value* pay_ptr = builder->createAdd(ptr, ctx->getConstantInt(i64, 16));
        builder->createStore(payload, pay_ptr);
        ir::Value* vn_ptr = builder->createAdd(ptr, ctx->getConstantInt(i64, 24));
        builder->createStore(vname, vn_ptr);
        builder->createRet(ptr);
    }

    // 2. lm_enum_tag(enum_ptr: i64) -> i64
    ir::Function* fn_tag = module->getFunction("lm_enum_tag");
    if (!fn_tag) fn_tag = builder->createFunction("lm_enum_tag", i64, {i64});
    if (fn_tag->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_tag);
        builder->setInsertPoint(b_entry);
        ir::Value* enum_ptr = fn_tag->getParameters().front().get();
        ir::Value* tag_ptr = builder->createAdd(enum_ptr, ctx->getConstantInt(i64, 8));
        ir::Value* tag = builder->createLoad(tag_ptr);
        builder->createRet(tag);
    }

    // 3. lm_enum_payload(enum_ptr: i64) -> i64
    ir::Function* fn_payload = module->getFunction("lm_enum_payload");
    if (!fn_payload) fn_payload = builder->createFunction("lm_enum_payload", i64, {i64});
    if (fn_payload->getBasicBlocks().empty()) {
        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_payload);
        builder->setInsertPoint(b_entry);
        ir::Value* enum_ptr = fn_payload->getParameters().front().get();
        ir::Value* pay_ptr = builder->createAdd(enum_ptr, ctx->getConstantInt(i64, 16));
        ir::Value* payload = builder->createLoad(pay_ptr);
        builder->createRet(payload);
    }

    // 4. lm_enum_to_str(enum_ptr: i64) -> i64
    ir::Function* fn_to_str = module->getFunction("lm_enum_to_str");
    if (!fn_to_str) fn_to_str = builder->createFunction("lm_enum_to_str", i64, {i64});
    if (fn_to_str->getBasicBlocks().empty()) {
        emit_str_concat_ir(module, builder);

        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn_to_str);
        ir::BasicBlock* b_no_pay = builder->createBasicBlock("no_pay", fn_to_str);
        ir::BasicBlock* b_has_vname = builder->createBasicBlock("has_vname", fn_to_str);
        ir::BasicBlock* b_no_vname = builder->createBasicBlock("no_vname", fn_to_str);
        ir::BasicBlock* b_has_pay = builder->createBasicBlock("has_pay", fn_to_str);
        ir::BasicBlock* b_pay_int = builder->createBasicBlock("pay_int", fn_to_str);
        ir::BasicBlock* b_pay_ptr = builder->createBasicBlock("pay_ptr", fn_to_str);
        ir::BasicBlock* b_pay_enum = builder->createBasicBlock("pay_enum", fn_to_str);
        ir::BasicBlock* b_pay_rawstr = builder->createBasicBlock("pay_rawstr", fn_to_str);
        ir::BasicBlock* b_build_pay = builder->createBasicBlock("build_pay", fn_to_str);

        builder->setInsertPoint(b_entry);
        ir::Value* enum_ptr = fn_to_str->getParameters().front().get();
        ir::Instruction* pay_str_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);

        ir::Value* tag_ptr = builder->createAdd(enum_ptr, ctx->getConstantInt(i64, 8));
        ir::Value* tag = builder->createLoad(tag_ptr);
        ir::Value* pay_ptr_loc = builder->createAdd(enum_ptr, ctx->getConstantInt(i64, 16));
        ir::Value* payload = builder->createLoad(pay_ptr_loc);
        ir::Value* vn_ptr_loc = builder->createAdd(enum_ptr, ctx->getConstantInt(i64, 24));
        ir::Value* vname = builder->createLoad(vn_ptr_loc);

        ir::Value* is_no_pay1 = builder->createCeq(payload, ctx->getConstantInt(i64, 0));
        ir::Value* is_no_pay2 = builder->createCeq(payload, ctx->getConstantInt(i64, UINT64_MAX));
        ir::Value* is_no_pay = builder->createOr(is_no_pay1, is_no_pay2);
        builder->createBr(is_no_pay, b_no_pay, b_has_pay);

        builder->setInsertPoint(b_no_pay);
        ir::Value* has_vn = builder->createCne(vname, ctx->getConstantInt(i64, 0));
        builder->createBr(has_vn, b_has_vname, b_no_vname);

        builder->setInsertPoint(b_has_vname);
        builder->createRet(vname);

        builder->setInsertPoint(b_no_vname);
        ir::Value* tag_str = emit_int_to_str_inline(module, builder, tag);
        builder->createRet(tag_str);

        builder->setInsertPoint(b_has_pay);
        ir::BasicBlock* b_pay_float = builder->createBasicBlock("pay_float", fn_to_str);
        ir::BasicBlock* b_pay_i64 = builder->createBasicBlock("pay_i64", fn_to_str);

        ir::Value* is_large_enough = builder->createCuge(payload, ctx->getConstantInt(i64, 65536));
        ir::Value* high_bits = builder->createShr(payload, ctx->getConstantInt(i64, 48));
        ir::Value* high_is_zero = builder->createCeq(high_bits, ctx->getConstantInt(i64, 0));
        ir::Value* is_pay_ptr = builder->createAnd(is_large_enough, high_is_zero);
        builder->createBr(is_pay_ptr, b_pay_ptr, b_pay_int);

        builder->setInsertPoint(b_pay_int);
        ir::Value* is_float = builder->createCne(high_bits, ctx->getConstantInt(i64, 0));
        builder->createBr(is_float, b_pay_float, b_pay_i64);

        builder->setInsertPoint(b_pay_float);
        ir::Value* pay_str_float = emit_float_to_str_inline(module, builder, payload);
        builder->createStore(pay_str_float, pay_str_slot);
        builder->createJmp(b_build_pay);

        builder->setInsertPoint(b_pay_i64);
        ir::Value* pay_str_int = emit_int_to_str_inline(module, builder, payload);
        builder->createStore(pay_str_int, pay_str_slot);
        builder->createJmp(b_build_pay);

        builder->setInsertPoint(b_pay_ptr);
        ir::Value* magic = builder->createLoad(payload);
        ir::Value* is_enum = builder->createCeq(magic, ctx->getConstantInt(i64, 0x454E554D));
        builder->createBr(is_enum, b_pay_enum, b_pay_rawstr);

        builder->setInsertPoint(b_pay_enum);
        ir::Value* pay_str_enum = builder->createCall(fn_to_str, {payload});
        builder->createStore(pay_str_enum, pay_str_slot);
        builder->createJmp(b_build_pay);

        builder->setInsertPoint(b_pay_rawstr);
        builder->createStore(payload, pay_str_slot);
        builder->createJmp(b_build_pay);

        builder->setInsertPoint(b_build_pay);
        ir::Value* pay_str_val = builder->createLoad(pay_str_slot);
        builder->createRet(pay_str_val);
    }

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::decl_runtime_math(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto f64 = ctx->getDoubleType();
    auto decl = [&](const std::string& name) {
        if (!module->getFunction(name)) builder->createFunction(name, f64, {f64});
    };
    decl("sqrt"); decl("sin"); decl("cos"); decl("tan");
    decl("asin"); decl("acos"); decl("atan");
    decl("log");  decl("log10"); decl("exp");
    decl("ceil"); decl("floor"); decl("round");
}

void FyraBuiltinFunctions::emit_str_alloc_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto i32 = ctx->getIntegerType(32);
    auto i8  = ctx->getIntegerType(8);
    auto ptr_i8 = ctx->getPointerType(i8);

    ir::Function* fn = module->getFunction("lm_str_alloc");
    if (!fn) fn = builder->createFunction("lm_str_alloc", ptr_i8, {i64});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    builder->setInsertPoint(b_entry);
    ir::Value* cap = fn->getParameters().front().get();

    // alloc_size = HEADER_SIZE + cap + 1 (header + payload + null byte)
    ir::Value* alloc_size = builder->createAdd(cap, ctx->getConstantInt(i64, StringABI::HEADER_SIZE + 1));
    ir::Instruction* ptr = builder->createExternCall("memory.alloc", {alloc_size}, ptr_i8);

    // type_id at offset 0
    builder->createStore(ctx->getConstantInt(i32, StringABI::TYPE_ID), ptr);
    // metadata = 0 at offset 4
    builder->createStore(ctx->getConstantInt(i32, 0), builder->createAdd(ptr, ctx->getConstantInt(i64, 4)));
    // len = 0 at LEN_OFFSET
    builder->createStore(ctx->getConstantInt(i64, 0), builder->createAdd(ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    // cap at CAP_OFFSET
    builder->createStore(cap, builder->createAdd(ptr, ctx->getConstantInt(i64, StringABI::CAP_OFFSET)));
    // data[0] = \0 at DATA_OFFSET
    builder->createStoreb(ctx->getConstantInt(i8, 0), builder->createAdd(ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET)));

    builder->createRet(ptr);

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_str_concat_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    ir::Function* fn = module->getFunction("lm_str_concat");
    if (!fn)
        fn = builder->createFunction("lm_str_concat", ctx->getPointerType(ctx->getIntegerType(8)), {ctx->getPointerType(ctx->getIntegerType(8)), ctx->getPointerType(ctx->getIntegerType(8))});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();

    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* b_done = builder->createBasicBlock("done", fn);

    builder->setInsertPoint(b_entry);
    auto it = fn->getParameters().begin();
    ir::Value* s1 = it->get();
    it++;
    ir::Value* s2 = it->get();

    auto i64 = ctx->getIntegerType(64);
    auto i32 = ctx->getIntegerType(32);

    ir::Function* cur_fn = builder->getInsertPoint()->getParent();
    static int concat_cnt = 0;
    std::string cid = std::to_string(++concat_cnt);

    ir::Instruction* s1_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* s2_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);

    ir::BasicBlock* b_s1_chk = builder->createBasicBlock("cat_s1_chk_" + cid, cur_fn);
    ir::BasicBlock* b_s1_i   = builder->createBasicBlock("cat_s1_i_" + cid, cur_fn);
    ir::BasicBlock* b_s1_str = builder->createBasicBlock("cat_s1_str_" + cid, cur_fn);

    ir::Value* is_ge1 = builder->createCuge(s1, ctx->getConstantInt(i64, 65536));
    ir::Value* hi1 = builder->createShr(s1, ctx->getConstantInt(i64, 48));
    ir::Value* hi_z1 = builder->createCeq(hi1, ctx->getConstantInt(i64, 0));
    ir::Value* is_ptr1 = builder->createAnd(is_ge1, hi_z1);
    builder->createBr(is_ptr1, b_s1_str, b_s1_i);

    builder->setInsertPoint(b_s1_i);
    ir::Value* s1_conv = emit_int_to_str_inline(module, builder, s1);
    builder->createStore(s1_conv, s1_slot);
    builder->createJmp(b_s1_chk);

    builder->setInsertPoint(b_s1_str);
    builder->createStore(s1, s1_slot);
    builder->createJmp(b_s1_chk);

    builder->setInsertPoint(b_s1_chk);
    ir::BasicBlock* b_s2_chk = builder->createBasicBlock("cat_s2_chk_" + cid, cur_fn);
    ir::BasicBlock* b_s2_i   = builder->createBasicBlock("cat_s2_i_" + cid, cur_fn);
    ir::BasicBlock* b_s2_str = builder->createBasicBlock("cat_s2_str_" + cid, cur_fn);

    ir::Value* is_ge2 = builder->createCuge(s2, ctx->getConstantInt(i64, 65536));
    ir::Value* hi2 = builder->createShr(s2, ctx->getConstantInt(i64, 48));
    ir::Value* hi_z2 = builder->createCeq(hi2, ctx->getConstantInt(i64, 0));
    ir::Value* is_ptr2 = builder->createAnd(is_ge2, hi_z2);
    builder->createBr(is_ptr2, b_s2_str, b_s2_i);

    builder->setInsertPoint(b_s2_i);
    ir::Value* s2_conv = emit_int_to_str_inline(module, builder, s2);
    builder->createStore(s2_conv, s2_slot);
    builder->createJmp(b_s2_chk);

    builder->setInsertPoint(b_s2_str);
    builder->createStore(s2, s2_slot);
    builder->createJmp(b_s2_chk);

    builder->setInsertPoint(b_s2_chk);
    ir::Value* s1_actual = builder->createLoad(s1_slot);
    ir::Value* s2_actual = builder->createLoad(s2_slot);

    ir::Value* len1 = builder->createLoad(builder->createAdd(s1_actual, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    ir::Value* len2 = builder->createLoad(builder->createAdd(s2_actual, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    ir::Value* final_len = builder->createAdd(len1, len2);
    ir::Value* alloc_size = builder->createAdd(final_len, ctx->getConstantInt(i64, StringABI::HEADER_SIZE + 1)); // header + final_len + 1 null terminator

    ir::Instruction* out = builder->createExternCall("memory.alloc", {alloc_size}, ctx->getPointerType(ctx->getIntegerType(8)));
    builder->createStore(ctx->getConstantInt(i32, StringABI::TYPE_ID), out); // type_id
    builder->createStore(final_len, builder->createAdd(out, ctx->getConstantInt(i64, StringABI::LEN_OFFSET))); // len
    builder->createStore(final_len, builder->createAdd(out, ctx->getConstantInt(i64, StringABI::CAP_OFFSET))); // cap

    ir::Value* out_data = builder->createAdd(out, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Value* s1_data = builder->createAdd(s1_actual, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Value* s2_data = builder->createAdd(s2_actual, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));

    ir::Instruction* ci = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), ci);

    ir::BasicBlock* b_c1_loop = builder->createBasicBlock("concat_c1_loop", fn);
    ir::BasicBlock* b_c1_body = builder->createBasicBlock("concat_c1_body", fn);
    ir::BasicBlock* b_c1_done = builder->createBasicBlock("concat_c1_done", fn);

    builder->createJmp(b_c1_loop);

    builder->setInsertPoint(b_c1_loop);
    ir::Value* idx1 = builder->createLoad(ci);
    ir::Value* cond1 = builder->createCslt(idx1, len1);
    builder->createBr(cond1, b_c1_body, b_c1_done);

    builder->setInsertPoint(b_c1_body);
    ir::Value* ch1 = builder->createLoadub(builder->createAdd(s1_data, idx1));
    builder->createStoreb(ch1, builder->createAdd(out_data, idx1));
    builder->createStore(builder->createAdd(idx1, ctx->getConstantInt(i64, 1)), ci);
    builder->createJmp(b_c1_loop);

    builder->setInsertPoint(b_c1_done);
    builder->createStore(ctx->getConstantInt(i64, 0), ci);

    ir::BasicBlock* b_c2_loop = builder->createBasicBlock("concat_c2_loop", fn);
    ir::BasicBlock* b_c2_body = builder->createBasicBlock("concat_c2_body", fn);
    ir::BasicBlock* b_c2_done = builder->createBasicBlock("concat_c2_done", fn);

    builder->createJmp(b_c2_loop);

    builder->setInsertPoint(b_c2_loop);
    ir::Value* idx2 = builder->createLoad(ci);
    ir::Value* cond2 = builder->createCslt(idx2, len2);
    builder->createBr(cond2, b_c2_body, b_c2_done);

    builder->setInsertPoint(b_c2_body);
    ir::Value* ch2 = builder->createLoadub(builder->createAdd(s2_data, idx2));
    builder->createStoreb(ch2, builder->createAdd(out_data, builder->createAdd(len1, idx2)));
    builder->createStore(builder->createAdd(idx2, ctx->getConstantInt(i64, 1)), ci);
    builder->createJmp(b_c2_loop);

    builder->setInsertPoint(b_c2_done);
    builder->createStoreb(ctx->getConstantInt(ctx->getIntegerType(8), 0), builder->createAdd(out_data, final_len));
    builder->createJmp(b_done);

    builder->setInsertPoint(b_done);
    builder->createRet(out);

    if (old_bb) {
        builder->setInsertPoint(old_bb);
    }
}

void FyraBuiltinFunctions::emit_str_format_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto i8 = ctx->getIntegerType(8);

    ir::Function* fn = module->getFunction("lm_rt_str_format");
    if (!fn)
        fn = builder->createFunction("lm_rt_str_format", i64, {i64, i64});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);

    builder->setInsertPoint(b_entry);
    auto it = fn->getParameters().begin();
    ir::Value* fmt_val = it->get(); it++;
    ir::Value* arg_val = it->get();

    // Convert arg_val to a string pointer if it is an integer (< 65536 and >= 0)
    // First, allocate 32 bytes for converted arg string if arg is an int
    ir::Instruction* arg_str_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* arg_len_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);

    ir::BasicBlock* b_is_num = builder->createBasicBlock("fmt_is_num", fn);
    ir::BasicBlock* b_is_float = builder->createBasicBlock("fmt_is_float", fn);
    ir::BasicBlock* b_is_int = builder->createBasicBlock("fmt_is_int", fn);
    ir::BasicBlock* b_is_str = builder->createBasicBlock("fmt_is_str", fn);
    ir::BasicBlock* b_fmt_proc = builder->createBasicBlock("fmt_proc", fn);
    ir::BasicBlock* b_slen_prep = builder->createBasicBlock("fmt_slen_prep", fn);

    ir::Value* is_large_enough = builder->createCuge(arg_val, ctx->getConstantInt(i64, 65536));
    ir::Value* high_bits = builder->createShr(arg_val, ctx->getConstantInt(i64, 48));
    ir::Value* high_is_zero = builder->createCeq(high_bits, ctx->getConstantInt(i64, 0));
    ir::Value* is_valid_ptr = builder->createAnd(is_large_enough, high_is_zero);
    builder->createBr(is_valid_ptr, b_is_str, b_is_num);

    builder->setInsertPoint(b_is_num);
    ir::Value* is_ffff = builder->createCeq(high_bits, ctx->getConstantInt(i64, 0xFFFF));
    ir::Value* is_zero_hb = builder->createCeq(high_bits, ctx->getConstantInt(i64, 0));
    ir::Value* is_int_hb = builder->createOr(is_ffff, is_zero_hb);
    builder->createBr(is_int_hb, b_is_int, b_is_float);

    builder->setInsertPoint(b_is_float);
    ir::Value* float_str = emit_float_to_str_inline(module, builder, arg_val);
    builder->createStore(float_str, arg_str_slot);
    builder->createJmp(b_slen_prep);

    // Number conversion branch: format integer arg_val into ASCII buffer
    builder->setInsertPoint(b_is_int);
    ir::Value* int_str = emit_int_to_str_inline(module, builder, arg_val);
    builder->createStore(int_str, arg_str_slot);
    builder->createJmp(b_slen_prep);

    // String / Heap object branch: arg_val is String, Enum, or List pointer
    builder->setInsertPoint(b_is_str);
    ir::BasicBlock* b_fmt_enum_proc = builder->createBasicBlock("fmt_is_enum_p", fn);
    ir::BasicBlock* b_fmt_enum_chk  = builder->createBasicBlock("fmt_is_enum_c", fn);
    ir::BasicBlock* b_fmt_list     = builder->createBasicBlock("fmt_is_list", fn);
    ir::BasicBlock* b_fmt_rawstr   = builder->createBasicBlock("fmt_is_rawstr", fn);

    ir::Value* magic_fmt = builder->createLoad(arg_val);
    ir::Value* type_id_fmt = builder->createAnd(magic_fmt, ctx->getConstantInt(i64, 0xFFFFFFFF));
    ir::Value* is_str_type = builder->createCeq(type_id_fmt, ctx->getConstantInt(i64, 11));
    builder->createBr(is_str_type, b_fmt_rawstr, b_fmt_enum_chk);

    builder->setInsertPoint(b_fmt_enum_chk);
    ir::Value* is_enum_fmt = builder->createCeq(magic_fmt, ctx->getConstantInt(i64, 0x454E554D));
    builder->createBr(is_enum_fmt, b_fmt_enum_proc, b_fmt_list);

    builder->setInsertPoint(b_fmt_enum_proc);
    ir::Function* fn_enum_str = module->getFunction("lm_enum_to_str");
    if (fn_enum_str) {
        ir::Value* enum_str_fmt = builder->createCall(fn_enum_str, {arg_val});
        builder->createStore(enum_str_fmt, arg_str_slot);
    } else {
        builder->createStore(arg_val, arg_str_slot);
    }
    builder->createJmp(b_slen_prep);

    builder->setInsertPoint(b_fmt_list);
    ir::Function* fn_list_str = module->getFunction("lm_list_to_str");
    if (fn_list_str) {
        ir::Value* list_str_fmt = builder->createCall(fn_list_str, {arg_val});
        builder->createStore(list_str_fmt, arg_str_slot);
    } else {
        builder->createStore(arg_val, arg_str_slot);
    }
    builder->createJmp(b_slen_prep);

    builder->setInsertPoint(b_fmt_rawstr);
    ir::Value* raw_data_ptr = builder->createAdd(arg_val, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Value* raw_len_val  = builder->createLoad(builder->createAdd(arg_val, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    builder->createStore(raw_data_ptr, arg_str_slot);
    builder->createStore(raw_len_val, arg_len_slot);
    builder->createJmp(b_fmt_proc);

    builder->setInsertPoint(b_slen_prep);
    // target_str_ptr points to the LmStringHeader itself. 
    // We need to extract the length from LEN_OFFSET, and the payload from DATA_OFFSET.
    ir::Value* target_str_hdr = builder->createLoad(arg_str_slot);
    ir::Value* target_len = builder->createLoad(builder->createAdd(target_str_hdr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    ir::Value* target_data = builder->createAdd(target_str_hdr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    
    builder->createStore(target_data, arg_str_slot);
    builder->createStore(target_len, arg_len_slot);
    builder->createJmp(b_fmt_proc);

    // Main formatting: scan fmt_val for "%s" or "{}"
    builder->setInsertPoint(b_fmt_proc);
    ir::Instruction* pos_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), pos_slot);

    ir::Value* fmt_data = builder->createAdd(fmt_val, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Value* fmt_total_len = builder->createLoad(builder->createAdd(fmt_val, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));

    ir::BasicBlock* b_scan_loop = builder->createBasicBlock("fmt_scan_loop", fn);
    ir::BasicBlock* b_check_s   = builder->createBasicBlock("fmt_check_s", fn);
    ir::BasicBlock* b_scan_next = builder->createBasicBlock("fmt_scan_next", fn);
    ir::BasicBlock* b_no_pct    = builder->createBasicBlock("fmt_no_pct", fn);
    ir::BasicBlock* b_do_replace = builder->createBasicBlock("fmt_do_replace", fn);

    builder->createJmp(b_scan_loop);

    builder->setInsertPoint(b_scan_loop);
    ir::Value* cur_pos = builder->createLoad(pos_slot);
    ir::Value* is_end = builder->createCsge(cur_pos, fmt_total_len);
    builder->createBr(is_end, b_no_pct, b_check_s);

    builder->setInsertPoint(b_check_s);
    ir::Value* c1 = builder->createLoadub(builder->createAdd(fmt_data, cur_pos));
    ir::Value* is_pct = builder->createCeq(c1, ctx->getConstantInt(i8, 37)); // '%'
    ir::Value* c2 = builder->createLoadub(builder->createAdd(fmt_data, builder->createAdd(cur_pos, ctx->getConstantInt(i64, 1))));
    ir::Value* is_s = builder->createCeq(c2, ctx->getConstantInt(i8, 115)); // 's'
    ir::Value* is_pct_s = builder->createAnd(is_pct, is_s);

    ir::Value* is_lb = builder->createCeq(c1, ctx->getConstantInt(i8, 123)); // '{'
    ir::Value* is_rb = builder->createCeq(c2, ctx->getConstantInt(i8, 125)); // '}'
    ir::Value* is_braces = builder->createAnd(is_lb, is_rb);

    ir::Value* is_match = builder->createOr(is_pct_s, is_braces);
    builder->createBr(is_match, b_do_replace, b_scan_next);

    builder->setInsertPoint(b_scan_next);
    ir::Value* next_pos = builder->createAdd(cur_pos, ctx->getConstantInt(i64, 1));
    builder->createStore(next_pos, pos_slot);
    builder->createJmp(b_scan_loop);

    builder->setInsertPoint(b_no_pct);
    builder->createRet(fmt_val);

    // Do replace branch: copy fmt_data[0..pos] + arg_str + fmt_data[pos+2..end]
    builder->setInsertPoint(b_do_replace);
    ir::Value* match_pos = cur_pos;
    ir::Value* arg_str_ptr = builder->createLoad(arg_str_slot);
    ir::Value* arg_len_val = builder->createLoad(arg_len_slot);

    ir::Value* suffix_len = builder->createSub(fmt_total_len, builder->createAdd(match_pos, ctx->getConstantInt(i64, 2)));
    ir::Value* total_out_len = builder->createAdd(builder->createAdd(match_pos, arg_len_val), suffix_len);

    emit_str_alloc_ir(module, builder);
    ir::Function* alloc_fn = module->getFunction("lm_str_alloc");
    ir::Value* new_hdr = builder->createCall(alloc_fn, {total_out_len});
    ir::Value* out_p = builder->createAdd(new_hdr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));

    // Copy prefix: fmt_data[0..match_pos]
    ir::Instruction* ci = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), ci);
    ir::BasicBlock* b_c1_loop = builder->createBasicBlock("fmt_c1_loop", fn);
    ir::BasicBlock* b_c1_body = builder->createBasicBlock("fmt_c1_body", fn);
    ir::BasicBlock* b_c1_done = builder->createBasicBlock("fmt_c1_done", fn);
    builder->createJmp(b_c1_loop);

    builder->setInsertPoint(b_c1_loop);
    ir::Value* idx1 = builder->createLoad(ci);
    ir::Value* cond1 = builder->createCslt(idx1, match_pos);
    builder->createBr(cond1, b_c1_body, b_c1_done);

    builder->setInsertPoint(b_c1_body);
    ir::Value* ch1 = builder->createLoadub(builder->createAdd(fmt_data, idx1));
    builder->createStoreb(ch1, builder->createAdd(out_p, idx1));
    builder->createStore(builder->createAdd(idx1, ctx->getConstantInt(i64, 1)), ci);
    builder->createJmp(b_c1_loop);

    builder->setInsertPoint(b_c1_done);
    // Copy arg_str
    builder->createStore(ctx->getConstantInt(i64, 0), ci);
    ir::BasicBlock* b_c2_loop = builder->createBasicBlock("fmt_c2_loop", fn);
    ir::BasicBlock* b_c2_body = builder->createBasicBlock("fmt_c2_body", fn);
    ir::BasicBlock* b_c2_done = builder->createBasicBlock("fmt_c2_done", fn);
    builder->createJmp(b_c2_loop);

    builder->setInsertPoint(b_c2_loop);
    ir::Value* idx2 = builder->createLoad(ci);
    ir::Value* cond2 = builder->createCslt(idx2, arg_len_val);
    builder->createBr(cond2, b_c2_body, b_c2_done);

    builder->setInsertPoint(b_c2_body);
    ir::Value* ch2 = builder->createLoadub(builder->createAdd(arg_str_ptr, idx2));
    ir::Value* dst2 = builder->createAdd(out_p, builder->createAdd(match_pos, idx2));
    builder->createStoreb(ch2, dst2);
    builder->createStore(builder->createAdd(idx2, ctx->getConstantInt(i64, 1)), ci);
    builder->createJmp(b_c2_loop);

    builder->setInsertPoint(b_c2_done);
    // Copy suffix
    builder->createStore(ctx->getConstantInt(i64, 0), ci);
    ir::BasicBlock* b_c3_loop = builder->createBasicBlock("fmt_c3_loop", fn);
    ir::BasicBlock* b_c3_body = builder->createBasicBlock("fmt_c3_body", fn);
    ir::BasicBlock* b_c3_done = builder->createBasicBlock("fmt_c3_done", fn);
    builder->createJmp(b_c3_loop);

    builder->setInsertPoint(b_c3_loop);
    ir::Value* idx3 = builder->createLoad(ci);
    ir::Value* cond3 = builder->createCslt(idx3, suffix_len);
    builder->createBr(cond3, b_c3_body, b_c3_done);

    builder->setInsertPoint(b_c3_body);
    ir::Value* src3 = builder->createAdd(fmt_data, builder->createAdd(builder->createAdd(match_pos, ctx->getConstantInt(i64, 2)), idx3));
    ir::Value* ch3 = builder->createLoadub(src3);
    ir::Value* dst3 = builder->createAdd(out_p, builder->createAdd(builder->createAdd(match_pos, arg_len_val), idx3));
    builder->createStoreb(ch3, dst3);
    builder->createStore(builder->createAdd(idx3, ctx->getConstantInt(i64, 1)), ci);
    builder->createJmp(b_c3_loop);

    builder->setInsertPoint(b_c3_done);
    builder->createStoreb(ctx->getConstantInt(i8, 0), builder->createAdd(out_p, total_out_len));
    builder->createStore(total_out_len, builder->createAdd(new_hdr, ctx->getConstantInt(i64, 8)));
    builder->createRet(new_hdr);

    if (old_bb) builder->setInsertPoint(old_bb);
}

static ir::Value* unbox_i64(ir::IRBuilder* builder, std::shared_ptr<ir::IRContext> ctx, ir::Value* val) {
    (void)builder;
    (void)ctx;
    return val;
}

void FyraBuiltinFunctions::emit_substring_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    emit_str_alloc_ir(module, builder);
    ir::Function* alloc_fn = module->getFunction("lm_str_alloc");

    auto make_sub = [&](const std::string& name) {
        ir::Function* fn = module->getFunction(name);
        if (!fn) fn = builder->createFunction(name, ptr_i8, {ptr_i8, i64, i64});
        if (!fn->getBasicBlocks().empty()) return;

        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
        builder->setInsertPoint(b_entry);
        auto it = fn->getParameters().begin();
        ir::Value* str_ptr = it->get(); it++;
        ir::Value* raw_start = it->get(); it++;
        ir::Value* raw_end   = it->get();

        ir::Value* start = unbox_i64(builder, ctx, raw_start);
        ir::Value* end   = unbox_i64(builder, ctx, raw_end);

        ir::Instruction* len_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        ir::Value* diff = builder->createSub(end, start);
        ir::Value* zero = ctx->getConstantInt(i64, 0);

        ir::BasicBlock* b_neg_len = builder->createBasicBlock("sub_neg_len", fn);
        ir::BasicBlock* b_pos_len = builder->createBasicBlock("sub_pos_len", fn);
        ir::BasicBlock* b_alloc_sub = builder->createBasicBlock("sub_alloc", fn);

        ir::Value* is_neg = builder->createCslt(diff, zero);
        builder->createBr(is_neg, b_neg_len, b_pos_len);

        builder->setInsertPoint(b_neg_len);
        builder->createStore(zero, len_slot);
        builder->createJmp(b_alloc_sub);

        builder->setInsertPoint(b_pos_len);
        builder->createStore(diff, len_slot);
        builder->createJmp(b_alloc_sub);

        builder->setInsertPoint(b_alloc_sub);
        ir::Value* sub_len = builder->createLoad(len_slot);
        ir::Value* new_hdr = builder->createCall(alloc_fn, {sub_len});
        ir::Value* src_data = builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
        ir::Value* dst_data = builder->createAdd(new_hdr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));

        ir::Instruction* i_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
        builder->createStore(zero, i_slot);

        ir::BasicBlock* b_loop = builder->createBasicBlock("sub_loop", fn);
        ir::BasicBlock* b_body = builder->createBasicBlock("sub_body", fn);
        ir::BasicBlock* b_done = builder->createBasicBlock("sub_done", fn);

        builder->createJmp(b_loop);

        builder->setInsertPoint(b_loop);
        ir::Value* i = builder->createLoad(i_slot);
        ir::Value* cond = builder->createCslt(i, sub_len);
        builder->createBr(cond, b_body, b_done);

        builder->setInsertPoint(b_body);
        ir::Value* src_idx = builder->createAdd(start, i);
        ir::Value* ch = builder->createLoadub(builder->createAdd(src_data, src_idx));
        builder->createStoreb(ch, builder->createAdd(dst_data, i));
        builder->createStore(builder->createAdd(i, ctx->getConstantInt(i64, 1)), i_slot);
        builder->createJmp(b_loop);

        builder->setInsertPoint(b_done);
        builder->createStoreb(ctx->getConstantInt(ctx->getIntegerType(8), 0), builder->createAdd(dst_data, sub_len));
        builder->createStore(sub_len, builder->createAdd(new_hdr, ctx->getConstantInt(i64, 8))); // update len
        builder->createRet(new_hdr);
    };

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    make_sub("_builtin_substring");
    make_sub("substring");
    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_string_byte_len_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    ir::Function* fn = module->getFunction("_builtin_string_byte_len");
    if (!fn) fn = builder->createFunction("_builtin_string_byte_len", i64, {ptr_i8});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    builder->setInsertPoint(b_entry);
    ir::Value* str_ptr = fn->getParameters().front().get();

    ir::Value* raw_len = builder->createLoad(builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    builder->createRet(raw_len);

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_string_byte_at_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    ir::Function* fn = module->getFunction("_builtin_string_byte_at");
    if (!fn) fn = builder->createFunction("_builtin_string_byte_at", i64, {ptr_i8, i64});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    builder->setInsertPoint(b_entry);
    auto it = fn->getParameters().begin();
    ir::Value* str_ptr = it->get(); it++;
    ir::Value* raw_idx = it->get();

    ir::Value* idx = unbox_i64(builder, ctx, raw_idx);
    ir::Value* data_ptr = builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Value* ch = builder->createLoadub(builder->createAdd(data_ptr, idx));
    ir::Value* raw_ch = builder->createCast(ch, i64);
    builder->createRet(raw_ch);

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_string_decode_next_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    ir::Function* fn = module->getFunction("_builtin_string_decode_next");
    if (!fn) fn = builder->createFunction("_builtin_string_decode_next", i64, {ptr_i8, i64});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* b_ascii = builder->createBasicBlock("ascii", fn);
    ir::BasicBlock* b_utf   = builder->createBasicBlock("utf_multibyte", fn);
    ir::BasicBlock* b_2b    = builder->createBasicBlock("utf_2b", fn);
    ir::BasicBlock* b_34b   = builder->createBasicBlock("utf_34b", fn);
    ir::BasicBlock* b_3b    = builder->createBasicBlock("utf_3b", fn);
    ir::BasicBlock* b_4b    = builder->createBasicBlock("utf_4b", fn);
    ir::BasicBlock* b_done  = builder->createBasicBlock("done", fn);

    builder->setInsertPoint(b_entry);
    auto it = fn->getParameters().begin();
    ir::Value* str_ptr = it->get(); it++;
    ir::Value* raw_off = it->get();

    ir::Value* offset  = unbox_i64(builder, ctx, raw_off);
    ir::Value* data_ptr = builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Instruction* res_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), res_slot);

    ir::Value* b0_raw = builder->createLoadub(builder->createAdd(data_ptr, offset));
    ir::Value* b0     = builder->createCast(b0_raw, i64);
    ir::Value* is_null = builder->createCeq(b0, ctx->getConstantInt(i64, 0));

    ir::Value* is_ascii = builder->createCslt(b0, ctx->getConstantInt(i64, 128));
    builder->createBr(is_ascii, b_ascii, b_utf);

    builder->setInsertPoint(b_ascii);
    ir::Value* ascii_val = builder->createOr(builder->createShl(b0, ctx->getConstantInt(i64, 8)), ctx->getConstantInt(i64, 1));
    ir::BasicBlock* b_asc_null = builder->createBasicBlock("asc_null", fn);
    ir::BasicBlock* b_asc_val  = builder->createBasicBlock("asc_val", fn);
    builder->createBr(is_null, b_asc_null, b_asc_val);

    builder->setInsertPoint(b_asc_null);
    builder->createStore(ctx->getConstantInt(i64, 0), res_slot);
    builder->createJmp(b_done);

    builder->setInsertPoint(b_asc_val);
    builder->createStore(ascii_val, res_slot);
    builder->createJmp(b_done);

    builder->setInsertPoint(b_utf);
    ir::Value* mask_e0 = builder->createAnd(b0, ctx->getConstantInt(i64, 0xE0));
    ir::Value* is_2b   = builder->createCeq(mask_e0, ctx->getConstantInt(i64, 0xC0));
    builder->createBr(is_2b, b_2b, b_34b);

    builder->setInsertPoint(b_2b);
    ir::Value* b1_2b_raw = builder->createLoadub(builder->createAdd(data_ptr, builder->createAdd(offset, ctx->getConstantInt(i64, 1))));
    ir::Value* b1_2b     = builder->createCast(b1_2b_raw, i64);
    ir::Value* cp2 = builder->createOr(builder->createShl(builder->createAnd(b0, ctx->getConstantInt(i64, 0x1F)), ctx->getConstantInt(i64, 6)), builder->createAnd(b1_2b, ctx->getConstantInt(i64, 0x3F)));
    ir::Value* res2 = builder->createOr(builder->createShl(cp2, ctx->getConstantInt(i64, 8)), ctx->getConstantInt(i64, 2));
    builder->createStore(res2, res_slot);
    builder->createJmp(b_done);

    builder->setInsertPoint(b_34b);
    ir::Value* mask_f0 = builder->createAnd(b0, ctx->getConstantInt(i64, 0xF0));
    ir::Value* is_3b   = builder->createCeq(mask_f0, ctx->getConstantInt(i64, 0xE0));
    builder->createBr(is_3b, b_3b, b_4b);

    builder->setInsertPoint(b_3b);
    ir::Value* b1_3b_raw = builder->createLoadub(builder->createAdd(data_ptr, builder->createAdd(offset, ctx->getConstantInt(i64, 1))));
    ir::Value* b2_3b_raw = builder->createLoadub(builder->createAdd(data_ptr, builder->createAdd(offset, ctx->getConstantInt(i64, 2))));
    ir::Value* b1_3b     = builder->createCast(b1_3b_raw, i64);
    ir::Value* b2_3b     = builder->createCast(b2_3b_raw, i64);
    ir::Value* cp3 = builder->createOr(builder->createOr(builder->createShl(builder->createAnd(b0, ctx->getConstantInt(i64, 0x0F)), ctx->getConstantInt(i64, 12)), builder->createShl(builder->createAnd(b1_3b, ctx->getConstantInt(i64, 0x3F)), ctx->getConstantInt(i64, 6))), builder->createAnd(b2_3b, ctx->getConstantInt(i64, 0x3F)));
    ir::Value* res3 = builder->createOr(builder->createShl(cp3, ctx->getConstantInt(i64, 8)), ctx->getConstantInt(i64, 3));
    builder->createStore(res3, res_slot);
    builder->createJmp(b_done);

    builder->setInsertPoint(b_4b);
    ir::Value* b1_4b_raw = builder->createLoadub(builder->createAdd(data_ptr, builder->createAdd(offset, ctx->getConstantInt(i64, 1))));
    ir::Value* b2_4b_raw = builder->createLoadub(builder->createAdd(data_ptr, builder->createAdd(offset, ctx->getConstantInt(i64, 2))));
    ir::Value* b3_4b_raw = builder->createLoadub(builder->createAdd(data_ptr, builder->createAdd(offset, ctx->getConstantInt(i64, 3))));
    ir::Value* b1_4b     = builder->createCast(b1_4b_raw, i64);
    ir::Value* b2_4b     = builder->createCast(b2_4b_raw, i64);
    ir::Value* b3_4b     = builder->createCast(b3_4b_raw, i64);
    ir::Value* cp4 = builder->createOr(builder->createOr(builder->createShl(builder->createAnd(b0, ctx->getConstantInt(i64, 0x07)), ctx->getConstantInt(i64, 18)), builder->createShl(builder->createAnd(b1_4b, ctx->getConstantInt(i64, 0x3F)), ctx->getConstantInt(i64, 12))), builder->createOr(builder->createShl(builder->createAnd(b2_4b, ctx->getConstantInt(i64, 0x3F)), ctx->getConstantInt(i64, 6)), builder->createAnd(b3_4b, ctx->getConstantInt(i64, 0x3F))));
    ir::Value* res4 = builder->createOr(builder->createShl(cp4, ctx->getConstantInt(i64, 8)), ctx->getConstantInt(i64, 4));
    builder->createStore(res4, res_slot);
    builder->createJmp(b_done);

    builder->setInsertPoint(b_done);
    ir::Value* final_res = builder->createLoad(res_slot);
    builder->createRet(final_res);

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_string_starts_with_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    ir::Function* fn = module->getFunction("_builtin_string_starts_with");
    if (!fn) fn = builder->createFunction("_builtin_string_starts_with", i64, {ptr_i8, ptr_i8});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* b_loop  = builder->createBasicBlock("sw_loop", fn);
    ir::BasicBlock* b_body  = builder->createBasicBlock("sw_body", fn);
    ir::BasicBlock* b_true  = builder->createBasicBlock("sw_true", fn);
    ir::BasicBlock* b_false = builder->createBasicBlock("sw_false", fn);

    builder->setInsertPoint(b_entry);
    auto it = fn->getParameters().begin();
    ir::Value* str_ptr = it->get(); it++;
    ir::Value* pre_ptr = it->get();

    ir::Value* len_str = builder->createLoad(builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    ir::Value* len_pre = builder->createLoad(builder->createAdd(pre_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));

    ir::Instruction* idx_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), idx_slot);

    ir::Value* pre_too_long = builder->createCslt(len_str, len_pre);
    builder->createBr(pre_too_long, b_false, b_loop);

    builder->setInsertPoint(b_loop);

    ir::Value* str_data = builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Value* pre_data = builder->createAdd(pre_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Value* idx = builder->createLoad(idx_slot);
    ir::Value* is_done = builder->createCsge(idx, len_pre);
    builder->createBr(is_done, b_true, b_body);

    builder->setInsertPoint(b_body);
    ir::Value* c_str = builder->createLoadub(builder->createAdd(str_data, idx));
    ir::Value* c_pre = builder->createLoadub(builder->createAdd(pre_data, idx));
    ir::Value* diff  = builder->createCne(c_str, c_pre);
    builder->createStore(builder->createAdd(idx, ctx->getConstantInt(i64, 1)), idx_slot);
    builder->createBr(diff, b_false, b_loop);

    builder->setInsertPoint(b_true);
    builder->createRet(ctx->getConstantInt(i64, 1));

    builder->setInsertPoint(b_false);
    builder->createRet(ctx->getConstantInt(i64, 0));

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_string_index_of_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    ir::Function* fn = module->getFunction("_builtin_string_index_of");
    if (!fn) fn = builder->createFunction("_builtin_string_index_of", i64, {ptr_i8, ptr_i8});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* b_outer = builder->createBasicBlock("io_outer", fn);
    ir::BasicBlock* b_inner = builder->createBasicBlock("io_inner", fn);
    ir::BasicBlock* b_in_chk= builder->createBasicBlock("io_in_chk", fn);
    ir::BasicBlock* b_in_nxt= builder->createBasicBlock("io_in_nxt", fn);
    ir::BasicBlock* b_found = builder->createBasicBlock("io_found", fn);
    ir::BasicBlock* b_notfd = builder->createBasicBlock("io_notfd", fn);
    ir::BasicBlock* b_out_nxt=builder->createBasicBlock("io_out_nxt", fn);

    builder->setInsertPoint(b_entry);
    auto it = fn->getParameters().begin();
    ir::Value* str_ptr = it->get(); it++;
    ir::Value* sub_ptr = it->get();

    ir::Value* len_str = builder->createLoad(builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    ir::Value* len_sub = builder->createLoad(builder->createAdd(sub_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));

    ir::Value* str_data = builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Value* sub_data = builder->createAdd(sub_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));

    ir::Instruction* i_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* j_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), i_slot);
    builder->createJmp(b_outer);

    builder->setInsertPoint(b_outer);
    ir::Value* i = builder->createLoad(i_slot);
    ir::Value* max_i = builder->createSub(len_str, len_sub);
    ir::Value* out_done = builder->createCsgt(i, max_i);
    builder->createBr(out_done, b_notfd, b_inner);

    builder->setInsertPoint(b_inner);
    builder->createStore(ctx->getConstantInt(i64, 0), j_slot);
    builder->createJmp(b_in_chk);

    builder->setInsertPoint(b_in_chk);
    ir::Value* j = builder->createLoad(j_slot);
    ir::Value* j_done = builder->createCsge(j, len_sub);
    builder->createBr(j_done, b_found, b_in_nxt);

    builder->setInsertPoint(b_in_nxt);
    ir::Value* c_str = builder->createLoadub(builder->createAdd(str_data, builder->createAdd(i, j)));
    ir::Value* c_sub = builder->createLoadub(builder->createAdd(sub_data, j));
    ir::Value* diff  = builder->createCne(c_str, c_sub);
    builder->createStore(builder->createAdd(j, ctx->getConstantInt(i64, 1)), j_slot);
    builder->createBr(diff, b_out_nxt, b_in_chk);

    builder->setInsertPoint(b_out_nxt);
    builder->createStore(builder->createAdd(i, ctx->getConstantInt(i64, 1)), i_slot);
    builder->createJmp(b_outer);

    builder->setInsertPoint(b_found);
    builder->createRet(i);

    builder->setInsertPoint(b_notfd);
    builder->createRet(ctx->getConstantInt(i64, -1));

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_string_contains_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    emit_string_index_of_ir(module, builder);
    ir::Function* fn = module->getFunction("_builtin_string_contains");
    if (!fn) fn = builder->createFunction("_builtin_string_contains", i64, {ptr_i8, ptr_i8});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* b_true  = builder->createBasicBlock("cont_true", fn);
    ir::BasicBlock* b_false = builder->createBasicBlock("cont_false", fn);

    builder->setInsertPoint(b_entry);
    auto it = fn->getParameters().begin();
    ir::Value* str_ptr = it->get(); it++;
    ir::Value* sub_ptr = it->get();

    ir::Function* io_fn = module->getFunction("_builtin_string_index_of");
    ir::Value* idx = builder->createCall(io_fn, {str_ptr, sub_ptr});

    ir::Value* not_found = builder->createCeq(idx, ctx->getConstantInt(i64, -1));
    builder->createBr(not_found, b_false, b_true);

    builder->setInsertPoint(b_true);
    builder->createRet(ctx->getConstantInt(i64, 1));

    builder->setInsertPoint(b_false);
    builder->createRet(ctx->getConstantInt(i64, 0));

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_string_ends_with_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    ir::Function* fn = module->getFunction("_builtin_string_ends_with");
    if (!fn) fn = builder->createFunction("_builtin_string_ends_with", i64, {ptr_i8, ptr_i8});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* b_cmp   = builder->createBasicBlock("ew_cmp", fn);
    ir::BasicBlock* b_loop  = builder->createBasicBlock("ew_loop", fn);
    ir::BasicBlock* b_body  = builder->createBasicBlock("ew_body", fn);
    ir::BasicBlock* b_true  = builder->createBasicBlock("ew_true", fn);
    ir::BasicBlock* b_false = builder->createBasicBlock("ew_false", fn);

    builder->setInsertPoint(b_entry);
    auto it = fn->getParameters().begin();
    ir::Value* str_ptr = it->get(); it++;
    ir::Value* sfx_ptr = it->get();

    ir::Value* len_str = builder->createLoad(builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    ir::Value* len_sfx = builder->createLoad(builder->createAdd(sfx_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));

    ir::Value* sfx_too_long = builder->createCslt(len_str, len_sfx);
    builder->createBr(sfx_too_long, b_false, b_cmp);

    builder->setInsertPoint(b_cmp);
    ir::Value* offset = builder->createSub(len_str, len_sfx);
    ir::Instruction* i_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), i_slot);

    ir::Value* str_data = builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Value* sfx_data = builder->createAdd(sfx_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    builder->createJmp(b_loop);

    builder->setInsertPoint(b_loop);
    ir::Value* i = builder->createLoad(i_slot);
    ir::Value* loop_done = builder->createCsge(i, len_sfx);
    builder->createBr(loop_done, b_true, b_body);

    builder->setInsertPoint(b_body);
    ir::Value* c_str = builder->createLoadub(builder->createAdd(str_data, builder->createAdd(offset, i)));
    ir::Value* c_sfx = builder->createLoadub(builder->createAdd(sfx_data, i));
    ir::Value* diff  = builder->createCne(c_str, c_sfx);
    builder->createStore(builder->createAdd(i, ctx->getConstantInt(i64, 1)), i_slot);
    builder->createBr(diff, b_false, b_loop);

    builder->setInsertPoint(b_true);
    builder->createRet(ctx->getConstantInt(i64, 1));

    builder->setInsertPoint(b_false);
    builder->createRet(ctx->getConstantInt(i64, 0));

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_string_trim_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    emit_string_byte_len_ir(module, builder);
    emit_substring_ir(module, builder);

    ir::Function* fn = module->getFunction("_builtin_string_trim");
    if (!fn) fn = builder->createFunction("_builtin_string_trim", ptr_i8, {ptr_i8});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* b_s_loop= builder->createBasicBlock("trim_s_loop", fn);
    ir::BasicBlock* b_s_chk = builder->createBasicBlock("trim_s_chk", fn);
    ir::BasicBlock* b_e_prep= builder->createBasicBlock("trim_e_prep", fn);
    ir::BasicBlock* b_e_loop= builder->createBasicBlock("trim_e_loop", fn);
    ir::BasicBlock* b_e_chk = builder->createBasicBlock("trim_e_chk", fn);
    ir::BasicBlock* b_sub   = builder->createBasicBlock("trim_sub", fn);

    builder->setInsertPoint(b_entry);
    ir::Value* str_ptr = fn->getParameters().front().get();

    ir::Function* len_fn = module->getFunction("_builtin_string_byte_len");
    ir::Value* len = builder->createCall(len_fn, {str_ptr});
    ir::Value* str_data = builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));

    ir::Instruction* start_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* end_slot   = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), start_slot);
    builder->createStore(len, end_slot);

    builder->createJmp(b_s_loop);

    builder->setInsertPoint(b_s_loop);
    ir::Value* s = builder->createLoad(start_slot);
    ir::Value* s_at_end = builder->createCsge(s, len);
    builder->createBr(s_at_end, b_sub, b_s_chk);

    builder->setInsertPoint(b_s_chk);
    ir::Value* ch_s = builder->createLoadub(builder->createAdd(str_data, s));
    ir::Value* is_sp_s = builder->createCeq(ch_s, ctx->getConstantInt(ctx->getIntegerType(8), 32));
    ir::Value* is_tb_s = builder->createCeq(ch_s, ctx->getConstantInt(ctx->getIntegerType(8), 9));
    ir::Value* is_nl_s = builder->createCeq(ch_s, ctx->getConstantInt(ctx->getIntegerType(8), 10));
    ir::Value* is_cr_s = builder->createCeq(ch_s, ctx->getConstantInt(ctx->getIntegerType(8), 13));
    ir::Value* is_ws_s = builder->createOr(builder->createOr(is_sp_s, is_tb_s), builder->createOr(is_nl_s, is_cr_s));

    ir::BasicBlock* b_s_inc = builder->createBasicBlock("trim_s_inc", fn);
    builder->createBr(is_ws_s, b_s_inc, b_e_prep);

    builder->setInsertPoint(b_s_inc);
    builder->createStore(builder->createAdd(s, ctx->getConstantInt(i64, 1)), start_slot);
    builder->createJmp(b_s_loop);

    builder->setInsertPoint(b_e_prep);
    builder->createJmp(b_e_loop);

    builder->setInsertPoint(b_e_loop);
    ir::Value* e = builder->createLoad(end_slot);
    ir::Value* s_curr = builder->createLoad(start_slot);
    ir::Value* e_at_s = builder->createCsle(e, s_curr);
    builder->createBr(e_at_s, b_sub, b_e_chk);

    builder->setInsertPoint(b_e_chk);
    ir::Value* e_minus_1 = builder->createSub(e, ctx->getConstantInt(i64, 1));
    ir::Value* ch_e = builder->createLoadub(builder->createAdd(str_data, e_minus_1));
    ir::Value* is_sp_e = builder->createCeq(ch_e, ctx->getConstantInt(ctx->getIntegerType(8), 32));
    ir::Value* is_tb_e = builder->createCeq(ch_e, ctx->getConstantInt(ctx->getIntegerType(8), 9));
    ir::Value* is_nl_e = builder->createCeq(ch_e, ctx->getConstantInt(ctx->getIntegerType(8), 10));
    ir::Value* is_cr_e = builder->createCeq(ch_e, ctx->getConstantInt(ctx->getIntegerType(8), 13));
    ir::Value* is_ws_e = builder->createOr(builder->createOr(is_sp_e, is_tb_e), builder->createOr(is_nl_e, is_cr_e));

    ir::BasicBlock* b_e_dec = builder->createBasicBlock("trim_e_dec", fn);
    builder->createBr(is_ws_e, b_e_dec, b_sub);

    builder->setInsertPoint(b_e_dec);
    builder->createStore(e_minus_1, end_slot);
    builder->createJmp(b_e_loop);

    builder->setInsertPoint(b_sub);
    ir::Value* final_s = builder->createLoad(start_slot);
    ir::Value* final_e = builder->createLoad(end_slot);

    ir::Function* sub_fn = module->getFunction("_builtin_substring");
    if (!sub_fn) sub_fn = module->getFunction("substring");
    ir::Value* res = builder->createCall(sub_fn, {str_ptr, final_s, final_e});
    builder->createRet(res);

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_string_to_lower_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    emit_str_alloc_ir(module, builder);
    ir::Function* alloc_fn = module->getFunction("lm_str_alloc");

    ir::Function* fn = module->getFunction("_builtin_string_to_lower");
    if (!fn) fn = builder->createFunction("_builtin_string_to_lower", ptr_i8, {ptr_i8});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* b_loop  = builder->createBasicBlock("tl_loop", fn);
    ir::BasicBlock* b_body  = builder->createBasicBlock("tl_body", fn);
    ir::BasicBlock* b_upper = builder->createBasicBlock("tl_upper", fn);
    ir::BasicBlock* b_next  = builder->createBasicBlock("tl_next", fn);
    ir::BasicBlock* b_done  = builder->createBasicBlock("tl_done", fn);

    builder->setInsertPoint(b_entry);
    ir::Value* str_ptr = fn->getParameters().front().get();

    ir::Value* len = builder->createLoad(builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    ir::Value* new_hdr = builder->createCall(alloc_fn, {len});

    ir::Value* src_data = builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Value* dst_data = builder->createAdd(new_hdr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));

    ir::Instruction* i_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), i_slot);
    builder->createJmp(b_loop);

    builder->setInsertPoint(b_loop);
    ir::Value* i = builder->createLoad(i_slot);
    ir::Value* loop_done = builder->createCsge(i, len);
    builder->createBr(loop_done, b_done, b_body);

    builder->setInsertPoint(b_body);
    ir::Value* ch = builder->createLoadub(builder->createAdd(src_data, i));
    ir::Value* is_ge_A = builder->createCsge(ch, ctx->getConstantInt(ctx->getIntegerType(8), 65));
    ir::Value* is_le_Z = builder->createCsle(ch, ctx->getConstantInt(ctx->getIntegerType(8), 90));
    ir::Value* is_upper = builder->createAnd(is_ge_A, is_le_Z);
    builder->createBr(is_upper, b_upper, b_next);

    builder->setInsertPoint(b_upper);
    ir::Value* lower_ch = builder->createAdd(ch, ctx->getConstantInt(ctx->getIntegerType(8), 32));
    builder->createStoreb(lower_ch, builder->createAdd(dst_data, i));
    builder->createJmp(b_next);

    builder->setInsertPoint(b_next);
    ir::PhiNode* ch_phi = builder->createPhi(ctx->getIntegerType(8), 2, nullptr);
    ch_phi->addIncoming(lower_ch, b_upper);
    ch_phi->addIncoming(ch, b_body);
    builder->createStoreb(ch_phi, builder->createAdd(dst_data, i));
    builder->createStore(builder->createAdd(i, ctx->getConstantInt(i64, 1)), i_slot);
    builder->createJmp(b_loop);

    builder->setInsertPoint(b_done);
    builder->createStoreb(ctx->getConstantInt(ctx->getIntegerType(8), 0), builder->createAdd(dst_data, len));
    builder->createStore(len, builder->createAdd(new_hdr, ctx->getConstantInt(i64, 8)));
    builder->createRet(new_hdr);

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_string_to_upper_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    emit_str_alloc_ir(module, builder);
    ir::Function* alloc_fn = module->getFunction("lm_str_alloc");

    ir::Function* fn = module->getFunction("_builtin_string_to_upper");
    if (!fn) fn = builder->createFunction("_builtin_string_to_upper", ptr_i8, {ptr_i8});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* b_loop  = builder->createBasicBlock("tu_loop", fn);
    ir::BasicBlock* b_body  = builder->createBasicBlock("tu_body", fn);
    ir::BasicBlock* b_lower = builder->createBasicBlock("tu_lower", fn);
    ir::BasicBlock* b_next  = builder->createBasicBlock("tu_next", fn);
    ir::BasicBlock* b_done  = builder->createBasicBlock("tu_done", fn);

    builder->setInsertPoint(b_entry);
    ir::Value* str_ptr = fn->getParameters().front().get();

    ir::Value* len = builder->createLoad(builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    ir::Value* new_hdr = builder->createCall(alloc_fn, {len});

    ir::Value* src_data = builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Value* dst_data = builder->createAdd(new_hdr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));

    ir::Instruction* i_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), i_slot);
    builder->createJmp(b_loop);

    builder->setInsertPoint(b_loop);
    ir::Value* i = builder->createLoad(i_slot);
    ir::Value* loop_done = builder->createCsge(i, len);
    builder->createBr(loop_done, b_done, b_body);

    builder->setInsertPoint(b_body);
    ir::Value* ch = builder->createLoadub(builder->createAdd(src_data, i));
    ir::Value* is_ge_a = builder->createCsge(ch, ctx->getConstantInt(ctx->getIntegerType(8), 97));
    ir::Value* is_le_z = builder->createCsle(ch, ctx->getConstantInt(ctx->getIntegerType(8), 122));
    ir::Value* is_lower = builder->createAnd(is_ge_a, is_le_z);
    builder->createBr(is_lower, b_lower, b_next);

    builder->setInsertPoint(b_lower);
    ir::Value* upper_ch = builder->createSub(ch, ctx->getConstantInt(ctx->getIntegerType(8), 32));
    builder->createJmp(b_next);

    builder->setInsertPoint(b_next);
    ir::PhiNode* ch_phi = builder->createPhi(ctx->getIntegerType(8), 2, nullptr);
    ch_phi->addIncoming(upper_ch, b_lower);
    ch_phi->addIncoming(ch, b_body);
    builder->createStoreb(ch_phi, builder->createAdd(dst_data, i));
    builder->createStore(builder->createAdd(i, ctx->getConstantInt(i64, 1)), i_slot);
    builder->createJmp(b_loop);

    builder->setInsertPoint(b_done);
    builder->createStoreb(ctx->getConstantInt(ctx->getIntegerType(8), 0), builder->createAdd(dst_data, len));
    builder->createStore(len, builder->createAdd(new_hdr, ctx->getConstantInt(i64, 8)));
    builder->createRet(new_hdr);

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_string_replace_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    emit_str_alloc_ir(module, builder);
    ir::Function* alloc_fn = module->getFunction("lm_str_alloc");

    ir::Function* fn = module->getFunction("_builtin_string_replace");
    if (!fn) fn = builder->createFunction("_builtin_string_replace", ptr_i8, {ptr_i8, ptr_i8, ptr_i8});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* b_c_loop= builder->createBasicBlock("rep_c_loop", fn);
    ir::BasicBlock* b_c_chk = builder->createBasicBlock("rep_c_chk", fn);
    ir::BasicBlock* b_c_m_loop= builder->createBasicBlock("rep_c_m_loop", fn);
    ir::BasicBlock* b_c_m_body= builder->createBasicBlock("rep_c_m_body", fn);
    ir::BasicBlock* b_c_m_found= builder->createBasicBlock("rep_c_m_found", fn);
    ir::BasicBlock* b_c_inc = builder->createBasicBlock("rep_c_inc", fn);
    ir::BasicBlock* b_c_next= builder->createBasicBlock("rep_c_next", fn);
    ir::BasicBlock* b_alloc = builder->createBasicBlock("rep_alloc", fn);
    ir::BasicBlock* b_b_loop= builder->createBasicBlock("rep_b_loop", fn);
    ir::BasicBlock* b_b_match=builder->createBasicBlock("rep_b_match", fn);
    ir::BasicBlock* b_b_copy =builder->createBasicBlock("rep_b_copy", fn);
    ir::BasicBlock* b_cp_loop = builder->createBasicBlock("rep_cp_loop", fn);
    ir::BasicBlock* b_cp_body = builder->createBasicBlock("rep_cp_body", fn);
    ir::BasicBlock* b_cp_done = builder->createBasicBlock("rep_cp_done", fn);
    ir::BasicBlock* b_b_char =builder->createBasicBlock("rep_b_char", fn);
    ir::BasicBlock* b_done  = builder->createBasicBlock("rep_done", fn);

    builder->setInsertPoint(b_entry);
    auto it = fn->getParameters().begin();
    ir::Value* str_ptr = it->get(); it++;
    ir::Value* old_ptr = it->get(); it++;
    ir::Value* new_ptr = it->get();

    ir::Instruction* count_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* i_slot     = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* src_pos   = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* dst_pos   = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* k_slot     = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* m_slot     = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* m2_slot    = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);

    ir::Value* len_str = builder->createLoad(builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    ir::Value* len_old = builder->createLoad(builder->createAdd(old_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    ir::Value* len_new = builder->createLoad(builder->createAdd(new_ptr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));

    ir::Value* str_data = builder->createAdd(str_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Value* old_data = builder->createAdd(old_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));
    ir::Value* new_data = builder->createAdd(new_ptr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));

    // Phase 1: count matches
    builder->createStore(ctx->getConstantInt(i64, 0), count_slot);
    builder->createStore(ctx->getConstantInt(i64, 0), i_slot);

    ir::Value* old_empty = builder->createCeq(len_old, ctx->getConstantInt(i64, 0));
    builder->createBr(old_empty, b_alloc, b_c_loop);

    builder->setInsertPoint(b_c_loop);
    ir::Value* i = builder->createLoad(i_slot);
    ir::Value* max_i = builder->createSub(len_str, len_old);
    ir::Value* loop_end = builder->createCsgt(i, max_i);
    builder->createBr(loop_end, b_alloc, b_c_chk);

    builder->setInsertPoint(b_c_chk);
    builder->createStore(ctx->getConstantInt(i64, 0), m_slot);
    builder->createJmp(b_c_m_loop);

    builder->setInsertPoint(b_c_m_loop);
    ir::Value* m = builder->createLoad(m_slot);
    ir::Value* m_end = builder->createCsge(m, len_old);
    builder->createBr(m_end, b_c_m_found, b_c_m_body);

    builder->setInsertPoint(b_c_m_body);
    ir::Value* c_s = builder->createLoadub(builder->createAdd(str_data, builder->createAdd(i, m)));
    ir::Value* c_o = builder->createLoadub(builder->createAdd(old_data, m));
    ir::Value* diff = builder->createCne(c_s, c_o);
    builder->createStore(builder->createAdd(m, ctx->getConstantInt(i64, 1)), m_slot);
    builder->createBr(diff, b_c_next, b_c_m_loop);

    builder->setInsertPoint(b_c_m_found);
    ir::Value* cnt = builder->createLoad(count_slot);
    builder->createStore(builder->createAdd(cnt, ctx->getConstantInt(i64, 1)), count_slot);
    builder->createStore(builder->createAdd(i, len_old), i_slot);
    builder->createJmp(b_c_loop);

    builder->setInsertPoint(b_c_next);
    builder->createStore(builder->createAdd(i, ctx->getConstantInt(i64, 1)), i_slot);
    builder->createJmp(b_c_loop);

    // Phase 2: Allocate & Build
    builder->setInsertPoint(b_alloc);
    ir::Value* cnt_final = builder->createLoad(count_slot);
    ir::Value* delta = builder->createSub(len_new, len_old);
    ir::Value* extra_len = builder->createMul(cnt_final, delta);
    ir::Value* res_len = builder->createAdd(len_str, extra_len);

    ir::Value* new_hdr = builder->createCall(alloc_fn, {res_len});
    ir::Value* dst_data = builder->createAdd(new_hdr, ctx->getConstantInt(i64, 24));

    builder->createStore(ctx->getConstantInt(i64, 0), src_pos);
    builder->createStore(ctx->getConstantInt(i64, 0), dst_pos);
    builder->createJmp(b_b_loop);

    builder->setInsertPoint(b_b_loop);
    ir::Value* sp = builder->createLoad(src_pos);
    ir::Value* b_done_cond = builder->createCsge(sp, len_str);
    builder->createBr(b_done_cond, b_done, b_b_match);

    builder->setInsertPoint(b_b_match);
    builder->createStore(ctx->getConstantInt(i64, 0), m2_slot);

    ir::BasicBlock* b_m2_loop = builder->createBasicBlock("rep_m2_loop", fn);
    ir::BasicBlock* b_m2_body = builder->createBasicBlock("rep_m2_body", fn);

    builder->createJmp(b_m2_loop);

    builder->setInsertPoint(b_m2_loop);
    ir::Value* m2 = builder->createLoad(m2_slot);
    ir::Value* m2_end = builder->createCsge(m2, len_old);
    builder->createBr(m2_end, b_b_copy, b_m2_body);

    builder->setInsertPoint(b_m2_body);
    ir::Value* c2_s = builder->createLoadub(builder->createAdd(str_data, builder->createAdd(sp, m2)));
    ir::Value* c2_o = builder->createLoadub(builder->createAdd(old_data, m2));
    ir::Value* diff2 = builder->createCne(c2_s, c2_o);
    builder->createStore(builder->createAdd(m2, ctx->getConstantInt(i64, 1)), m2_slot);
    builder->createBr(diff2, b_b_char, b_m2_loop);

    builder->setInsertPoint(b_b_copy);
    builder->createStore(ctx->getConstantInt(i64, 0), k_slot);
    builder->createJmp(b_cp_loop);

    builder->setInsertPoint(b_cp_loop);
    ir::Value* k = builder->createLoad(k_slot);
    ir::Value* cp_done = builder->createCsge(k, len_new);
    builder->createBr(cp_done, b_cp_done, b_cp_body);

    builder->setInsertPoint(b_cp_body);
    ir::Value* dp = builder->createLoad(dst_pos);
    ir::Value* ch_new = builder->createLoadub(builder->createAdd(new_data, k));
    builder->createStoreb(ch_new, builder->createAdd(dst_data, dp));
    builder->createStore(builder->createAdd(dp, ctx->getConstantInt(i64, 1)), dst_pos);
    builder->createStore(builder->createAdd(k, ctx->getConstantInt(i64, 1)), k_slot);
    builder->createJmp(b_cp_loop);

    builder->setInsertPoint(b_cp_done);
    builder->createStore(builder->createAdd(sp, len_old), src_pos);
    builder->createJmp(b_b_loop);

    builder->setInsertPoint(b_b_char);
    ir::Value* dp2 = builder->createLoad(dst_pos);
    ir::Value* ch_str = builder->createLoadub(builder->createAdd(str_data, sp));
    builder->createStoreb(ch_str, builder->createAdd(dst_data, dp2));
    builder->createStore(builder->createAdd(dp2, ctx->getConstantInt(i64, 1)), dst_pos);
    builder->createStore(builder->createAdd(sp, ctx->getConstantInt(i64, 1)), src_pos);
    builder->createJmp(b_b_loop);

    builder->setInsertPoint(b_done);
    ir::Value* final_dp = builder->createLoad(dst_pos);
    builder->createStoreb(ctx->getConstantInt(ctx->getIntegerType(8), 0), builder->createAdd(dst_data, final_dp));
    builder->createStore(final_dp, builder->createAdd(new_hdr, ctx->getConstantInt(i64, 8)));
    builder->createRet(new_hdr);

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_string_from_bytes_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    emit_str_alloc_ir(module, builder);
    ir::Function* alloc_fn = module->getFunction("lm_str_alloc");

    ir::Function* fn = module->getFunction("_builtin_string_from_bytes");
    if (!fn) fn = builder->createFunction("_builtin_string_from_bytes", ptr_i8, {i64});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* b_loop  = builder->createBasicBlock("sfb_loop", fn);
    ir::BasicBlock* b_body  = builder->createBasicBlock("sfb_body", fn);
    ir::BasicBlock* b_done  = builder->createBasicBlock("sfb_done", fn);

    builder->setInsertPoint(b_entry);
    ir::Value* list_ptr = fn->getParameters().front().get();

    ir::Value* count = builder->createLoad(list_ptr);
    ir::Value* data_slot = builder->createAdd(list_ptr, ctx->getConstantInt(i64, 16));
    ir::Value* data_buf = builder->createLoad(data_slot);

    ir::Value* new_hdr = builder->createCall(alloc_fn, {count});
    ir::Value* dst_data = builder->createAdd(new_hdr, ctx->getConstantInt(i64, StringABI::DATA_OFFSET));

    ir::Instruction* i_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), i_slot);

    builder->createJmp(b_loop);

    builder->setInsertPoint(b_loop);
    ir::Value* i = builder->createLoad(i_slot);
    ir::Value* loop_done = builder->createCsge(i, count);
    builder->createBr(loop_done, b_done, b_body);

    builder->setInsertPoint(b_body);
    ir::Value* elem_off = builder->createMul(i, ctx->getConstantInt(i64, 8));
    ir::Value* elem_addr = builder->createAdd(data_buf, elem_off);
    ir::Value* elem_val = builder->createLoad(elem_addr);
    ir::Value* byte_val = builder->createCast(elem_val, ctx->getIntegerType(8));

    builder->createStoreb(byte_val, builder->createAdd(dst_data, i));
    builder->createStore(builder->createAdd(i, ctx->getConstantInt(i64, 1)), i_slot);
    builder->createJmp(b_loop);

    builder->setInsertPoint(b_done);
    builder->createStoreb(ctx->getConstantInt(ctx->getIntegerType(8), 0), builder->createAdd(dst_data, count));
    builder->createStore(count, builder->createAdd(new_hdr, ctx->getConstantInt(i64, StringABI::LEN_OFFSET)));
    builder->createRet(new_hdr);

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_to_string_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    ir::Function* fn = module->getFunction("lm_to_string");
    if (!fn) fn = builder->createFunction("lm_to_string", ptr_i8, {i64});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    builder->setInsertPoint(b_entry);
    ir::Value* val = fn->getParameters().front().get();

    // If val is pointer (>= 65536 or negative or points to string), return val
    // Else format integer val into a 32-byte string buffer
    ir::Instruction* buf = builder->createExternCall("memory.alloc", {ctx->getConstantInt(i64, 32)}, ptr_i8);
    // Simple placeholder string conversion
    builder->createRet(val);

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_error_new_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto i8 = ctx->getIntegerType(8);

    ir::Function* fn = module->getFunction("lm_error_new");
    if (!fn) fn = builder->createFunction("lm_error_new", i64, {i64});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    builder->setInsertPoint(b_entry);
    ir::Value* err_code = fn->getParameters().front().get();

    // Return err_code or tagged error value
    builder->createRet(err_code);

    if (old_bb) builder->setInsertPoint(old_bb);
}
} // namespace LM::Backend::Fyra

extern "C" {
uint64_t lm_string_byte_at_ffi(const char* str, uint64_t index) {
    if (!str) return 0;
    size_t len = strlen(str);
    if (index >= len) return 0;
    return (uint8_t)str[index];
}

void* lm_string_to_codepoint_list(const char* str) {
    LmList* list = lm_list_new();
    if (!str) return list;
    uint64_t len = strlen(str);
    uint64_t offset = 0;
    uint32_t cp = 0;
    uint8_t consumed = 0;
    while (offset < len) {
        if (!utf8_decode_next(str, len, &offset, &cp, &consumed)) break;
        lm_list_append(list, BOX_INT((int64_t)cp));
    }
    return list;
}
}

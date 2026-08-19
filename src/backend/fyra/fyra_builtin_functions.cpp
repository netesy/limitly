#include "fyra_builtin_functions.hh"
#include "ir/Constant.h"
#include "ir/Type.h"
#include "ir/PhiNode.h"

namespace LM::Backend::Fyra {

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
    if (used_builtins.count("lm_str_concat")) emit_str_concat_ir(module, builder);
    if (used_builtins.count("lm_rt_str_format")) emit_str_format_ir(module, builder);
    if (used_builtins.count("_builtin_substring") || used_builtins.count("substring")) emit_substring_ir(module, builder);
    if (used_builtins.count("lm_to_string")) emit_to_string_ir(module, builder);
    if (used_builtins.count("lm_error_new")) emit_error_new_ir(module, builder);
    if (used_builtins.count("lm_key_eq")) emit_dict_ir(module, builder);
    if (used_builtins.count("lm_assert")) emit_assert(module, builder);
    if (used_builtins.count("abs"))       emit_abs(module, builder);

    bool needs_list  = false;
    bool needs_tuple = false;
    bool needs_dict  = false;
    bool needs_math  = false;

    for (const auto& name : used_builtins) {
        if (name.find("list")  != std::string::npos) needs_list  = true;
        if (name.find("tuple") != std::string::npos) needs_tuple = true;
        if (name.find("dict")  != std::string::npos) needs_dict  = true;
        if (name == "sqrt" || name == "sin" || name == "cos" || name == "tan" ||
            name == "asin" || name == "acos" || name == "atan" || name == "log" ||
            name == "log10" || name == "exp" || name == "ceil" || name == "floor" ||
            name == "round") needs_math = true;
    }

    if (needs_list)  emit_list_ir(module, builder);
    if (needs_tuple) emit_tuple_ir(module, builder);
    if (needs_dict)  emit_dict_ir(module, builder);
    if (needs_math)  decl_runtime_math(module, builder);
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
    auto gv = std::make_unique<ir::GlobalVariable>(
        ctx->getPointerType(ctx->getIntegerType(8)), name,
        ctx->getConstantString(value), false, ".data");
    auto* ptr = gv.get();
    module->addGlobalVariable(std::move(gv));
    return ptr;
}

// ---------------------------------------------------------------------------
// emit_print_str_inline  ?  inline io.write for a raw char* (no box)
// Emits: strlen loop + io.write(1, ptr, len) + io.write(1, "\n", 1)
// Call this FROM builder.cpp at the print call site.
// ---------------------------------------------------------------------------
static int g_print_str_counter = 0;
static int g_print_int_counter = 0;

void FyraBuiltinFunctions::emit_print_str_inline(
        ir::Module* module, ir::IRBuilder* builder, ir::Value* char_ptr) {
    auto ctx = module->getContextShared();
    ir::Function* fn = builder->getInsertPoint()->getParent();
    std::string id = std::to_string(++g_print_str_counter);
    ir::BasicBlock* current_bb = builder->getInsertPoint();
    ir::BasicBlock* b_loop = builder->createBasicBlock("ps_loop_" + id, fn);
    ir::BasicBlock* b_done = builder->createBasicBlock("ps_done_" + id, fn);

    builder->createJmp(b_loop);

    builder->setInsertPoint(b_loop);
    ir::PhiNode* len_phi = builder->createPhi(ctx->getIntegerType(64), 2, nullptr);
    len_phi->addIncoming(ctx->getConstantInt(ctx->getIntegerType(64), 0), current_bb);

    ir::Value* char_ptr2 = builder->createAdd(char_ptr, len_phi);
    ir::Value* ch        = builder->createLoadub(char_ptr2);
    ir::Value* is_null   = builder->createCeq(ch, ctx->getConstantInt(ctx->getIntegerType(8), 0));
    ir::Value* next_len  = builder->createAdd(len_phi, ctx->getConstantInt(ctx->getIntegerType(64), 1));
    len_phi->addIncoming(next_len, b_loop);
    builder->createBr(is_null, b_done, b_loop);

    builder->setInsertPoint(b_done);
    ir::Value* actual_len = len_phi;

    // io.write(1, char_ptr, actual_len)
    builder->createExternCall("io.write", {
        ctx->getConstantInt(ctx->getIntegerType(64), 1),
        char_ptr,
        actual_len
    }, ctx->getIntegerType(64));
}

void FyraBuiltinFunctions::emit_print_int_inline(
        ir::Module* module, ir::IRBuilder* builder, ir::Value* val) {
    auto ctx = module->getContextShared();
    ir::Function* fn = builder->getInsertPoint()->getParent();
    std::string id = std::to_string(++g_print_int_counter);

    ir::BasicBlock* current_bb = builder->getInsertPoint();
    ir::BasicBlock* b_neg  = builder->createBasicBlock("pi_neg_" + id,  fn);
    ir::BasicBlock* b_abs  = builder->createBasicBlock("pi_abs_" + id,  fn);
    ir::BasicBlock* b_loop = builder->createBasicBlock("pi_loop_" + id, fn);
    ir::BasicBlock* b_emit = builder->createBasicBlock("pi_emit_" + id, fn);

    // Static 64-byte print buffer in global BSS
    ir::GlobalVariable* buf = get_or_create_global_str(module, builder, "print_int_buf_" + id, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
    ir::Value* end_ptr = builder->createAdd(buf, ctx->getConstantInt(ctx->getIntegerType(64), 31));
    builder->createStoreb(ctx->getConstantInt(ctx->getIntegerType(8), 0), end_ptr);

    ir::Value* is_neg = builder->createCslt(val, ctx->getConstantInt(ctx->getIntegerType(64), 0));
    builder->createBr(is_neg, b_neg, b_abs);

    // negative branch: print '-', negate
    builder->setInsertPoint(b_neg);
    ir::GlobalVariable* gv_minus = get_or_create_global_str(module, builder, "str_minus", "-");
    builder->createExternCall("io.write", {
        ctx->getConstantInt(ctx->getIntegerType(64), 1),
        gv_minus,
        ctx->getConstantInt(ctx->getIntegerType(64), 1)
    }, ctx->getIntegerType(64));
    ir::Value* abs_v = builder->createNeg(val);
    builder->createJmp(b_loop);

    builder->setInsertPoint(b_abs);
    builder->createJmp(b_loop);

    // digit extraction loop with PhiNodes
    builder->setInsertPoint(b_loop);
    ir::PhiNode* val_phi = builder->createPhi(ctx->getIntegerType(64), 2, nullptr);
    val_phi->addIncoming(abs_v, b_neg);
    val_phi->addIncoming(val, b_abs);

    ir::PhiNode* ptr_phi = builder->createPhi(ctx->getIntegerType(64), 2, nullptr);
    ptr_phi->addIncoming(end_ptr, b_neg);
    ptr_phi->addIncoming(end_ptr, b_abs);

    ir::Value* next_val = builder->createDiv(val_phi, ctx->getConstantInt(ctx->getIntegerType(64), 10));
    ir::Value* rem      = builder->createRem(val_phi, ctx->getConstantInt(ctx->getIntegerType(64), 10));
    ir::Value* ascii    = builder->createAdd(rem, ctx->getConstantInt(ctx->getIntegerType(64), 48));
    ir::Value* next_ptr = builder->createSub(ptr_phi, ctx->getConstantInt(ctx->getIntegerType(64), 1));
    builder->createStoreb(ascii, next_ptr);

    val_phi->addIncoming(next_val, b_loop);
    ptr_phi->addIncoming(next_ptr, b_loop);
    ir::Value* cond = builder->createCuge(next_val, ctx->getConstantInt(ctx->getIntegerType(64), 1));
    builder->createBr(cond, b_loop, b_emit);

    ir::BasicBlock* b_done = builder->createBasicBlock("pi_done_" + id, fn);

    builder->setInsertPoint(b_emit);
    ir::Value* final_ptr  = next_ptr;
    ir::Value* full_end   = builder->createAdd(buf, ctx->getConstantInt(ctx->getIntegerType(64), 31));
    ir::Value* len = builder->createSub(full_end, final_ptr);
    builder->createExternCall("io.write", {
        ctx->getConstantInt(ctx->getIntegerType(64), 1),
        final_ptr,
        len
    }, ctx->getIntegerType(64));
    builder->createJmp(b_done);

    builder->setInsertPoint(b_done);
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
        gv_true,
        ctx->getConstantInt(i64, 4)
    }, i64);
    builder->createJmp(b_done);

    builder->setInsertPoint(b_false);
    ir::GlobalVariable* gv_false = get_or_create_global_str(module, builder, "str_false", "false");
    builder->createExternCall("io.write", {
        ctx->getConstantInt(i64, 1),
        gv_false,
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
        gv_nil,
        ctx->getConstantInt(i64, 3)
    }, i64);
}

void FyraBuiltinFunctions::emit_print_float_inline(ir::Module* module,
                                                   ir::IRBuilder* builder,
                                                   ir::Value* val) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    ir::Instruction* buf_ptr = builder->createAlloc(ctx->getConstantInt(i64, 64), i64);
    ir::GlobalVariable* fmt_gv = get_or_create_global_str(module, builder, "fmt_float", "%g");
    
    // snprintf(buf_ptr, 64, "%g", val)
    builder->createExternCall("snprintf", {
        buf_ptr,
        ctx->getConstantInt(i64, 64),
        fmt_gv,
        val
    }, i64);

    emit_print_str_inline(module, builder, buf_ptr);
}

// ---------------------------------------------------------------------------
void FyraBuiltinFunctions::emit_print_decimal_inline(ir::Module* module,
                                                   ir::IRBuilder* builder,
                                                   ir::Value* val,
                                                   int scale) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto i8 = ctx->getIntegerType(8);

    int uid = ++g_print_str_counter;
    std::string s_uid = std::to_string(uid);

    ir::BasicBlock* cur_bb = builder->getInsertPoint();
    ir::Function* cur_fn = cur_bb->getParent();

    // 1. Allocate buffer and all local slots upfront
    ir::Instruction* buf_ptr = builder->createAlloc(ctx->getConstantInt(i64, 64), i64);
    ir::Value* p_end = builder->createAdd(buf_ptr, ctx->getConstantInt(i64, 64));

    ir::Instruction* v_cur_ptr = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(p_end, v_cur_ptr);

    ir::Instruction* v_whole = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* v_frac = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* v_scale_count = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);

    // 2. Create basic blocks
    ir::BasicBlock* b_neg  = builder->createBasicBlock("pd_neg_" + s_uid, cur_fn);
    ir::BasicBlock* b_abs  = builder->createBasicBlock("pd_abs_" + s_uid, cur_fn);
    ir::BasicBlock* b_prep = builder->createBasicBlock("pd_prep_" + s_uid, cur_fn);
    ir::BasicBlock* b_frac_loop = builder->createBasicBlock("pd_frac_loop_" + s_uid, cur_fn);
    ir::BasicBlock* b_dot  = builder->createBasicBlock("pd_dot_" + s_uid, cur_fn);
    ir::BasicBlock* b_whole_loop = builder->createBasicBlock("pd_whole_loop_" + s_uid, cur_fn);
    ir::BasicBlock* b_emit = builder->createBasicBlock("pd_emit_" + s_uid, cur_fn);

    ir::Value* is_neg = builder->createCslt(val, ctx->getConstantInt(i64, 0));
    builder->createBr(is_neg, b_neg, b_abs);

    builder->setInsertPoint(b_neg);
    ir::GlobalVariable* gv_minus = get_or_create_global_str(module, builder, "str_minus", "-");
    builder->createExternCall("io.write", {
        ctx->getConstantInt(i64, 1),
        gv_minus,
        ctx->getConstantInt(i64, 1)
    }, i64);
    ir::Value* neg_v = builder->createNeg(val);
    builder->createStore(neg_v, v_whole);
    builder->createJmp(b_prep);

    builder->setInsertPoint(b_abs);
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
    builder->createBr(w_more, b_whole_loop, b_emit);

    ir::BasicBlock* b_done = builder->createBasicBlock("pd_done_" + s_uid, cur_fn);

    // Emit WriteFile
    builder->setInsertPoint(b_emit);
    ir::Value* final_start = builder->createLoad(v_cur_ptr);
    ir::Value* end_limit = builder->createAdd(buf_ptr, ctx->getConstantInt(i64, 64));
    ir::Value* len = builder->createSub(end_limit, final_start);

    builder->createExternCall("io.write", {
        ctx->getConstantInt(i64, 1),
        final_start,
        len
    }, i64);
    builder->createJmp(b_done);

    builder->setInsertPoint(b_done);
}

// ---------------------------------------------------------------------------
void FyraBuiltinFunctions::emit_assert(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    ir::Function* fn = module->getFunction("lm_assert");
    if (!fn)
        fn = builder->createFunction("lm_assert", ctx->getVoidType(),
                                     {ctx->getIntegerType(64), ctx->getIntegerType(64)});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* a_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* a_fail  = builder->createBasicBlock("fail",  fn);
    ir::BasicBlock* a_pass  = builder->createBasicBlock("pass",  fn);

    builder->setInsertPoint(a_entry);
    ir::Value* cond = fn->getParameters().front().get();
    builder->createBr(cond, a_pass, a_fail);

    builder->setInsertPoint(a_fail);
    const std::string fail_msg = "Assertion failed\n";
    ir::GlobalVariable* gv = get_or_create_global_str(module, builder, "assert_fail", fail_msg);
    builder->createExternCall("io.write", {
        ctx->getConstantInt(ctx->getIntegerType(64), 1),
        gv,
        ctx->getConstantInt(ctx->getIntegerType(64), (int64_t)fail_msg.length())
    }, ctx->getIntegerType(64));
    builder->createExternCall("process.exit", {
        ctx->getConstantInt(ctx->getIntegerType(64), 1)
    }, ctx->getIntegerType(64));
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
        builder->setInsertPoint(b_entry);
        auto it = fn_set->getParameters().begin();
        ir::Value* list_ptr = it->get();
        it++;
        ir::Value* index = it->get();
        it++;
        ir::Value* val = it->get();
        ir::Value* data_ptr_slot = builder->createAdd(list_ptr, ctx->getConstantInt(i64, 16));
        ir::Value* data = builder->createLoad(data_ptr_slot);
        ir::Value* offset = builder->createMul(index, ctx->getConstantInt(i64, 8));
        ir::Value* elem_ptr = builder->createAdd(data, offset);
        builder->createStore(val, elem_ptr);
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
        ir::Value* k1_small = builder->createCult(k1, ctx->getConstantInt(i64, 65536));
        ir::Value* k2_small = builder->createCult(k2, ctx->getConstantInt(i64, 65536));
        ir::Value* either_small = builder->createOr(k1_small, k2_small);
        builder->createBr(either_small, b_ret_false, b_loop_init);

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
        ir::BasicBlock* b_store = builder->createBasicBlock("store", fn_set);
        ir::BasicBlock* b_next = builder->createBasicBlock("next", fn_set);
        ir::BasicBlock* b_done = builder->createBasicBlock("done", fn_set);

        builder->setInsertPoint(b_entry);
        auto it = fn_set->getParameters().begin();
        ir::Value* dict_ptr = it->get(); it++;
        ir::Value* key = it->get(); it++;
        ir::Value* val = it->get();

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
        builder->createBr(cond, b_check, b_done);

        builder->setInsertPoint(b_check);
        ir::Value* k_off = builder->createMul(i, ctx->getConstantInt(i64, 8));
        ir::Value* k_addr = builder->createAdd(keys, k_off);
        ir::Value* curr_k = builder->createLoad(k_addr);

        ir::Value* is_match = builder->createCall(fn_eq, {curr_k, key});
        ir::Value* is_empty = builder->createCeq(curr_k, ctx->getConstantInt(i64, 0));
        ir::Value* should_store = builder->createOr(is_match, is_empty);
        builder->createBr(should_store, b_store, b_next);

        builder->setInsertPoint(b_store);
        builder->createStore(key, k_addr);
        ir::Value* v_addr = builder->createAdd(vals, k_off);
        builder->createStore(val, v_addr);
        builder->createRet(nullptr);

        builder->setInsertPoint(b_next);
        ir::Value* next_i = builder->createAdd(i, ctx->getConstantInt(i64, 1));
        builder->createStore(next_i, i_slot);
        builder->createJmp(b_loop);

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

void FyraBuiltinFunctions::emit_str_concat_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    ir::Function* fn = module->getFunction("lm_str_concat");
    if (!fn)
        fn = builder->createFunction("lm_str_concat", ctx->getPointerType(ctx->getIntegerType(8)), {ctx->getPointerType(ctx->getIntegerType(8)), ctx->getPointerType(ctx->getIntegerType(8))});
    if (!fn->getBasicBlocks().empty()) return;

    ir::BasicBlock* old_bb = builder->getInsertPoint();

    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
    ir::BasicBlock* b_l1 = builder->createBasicBlock("l1", fn);
    ir::BasicBlock* b_l1d = builder->createBasicBlock("l1d", fn);
    ir::BasicBlock* b_l2 = builder->createBasicBlock("l2", fn);
    ir::BasicBlock* b_l2d = builder->createBasicBlock("l2d", fn);
    ir::BasicBlock* b_alloc = builder->createBasicBlock("alloc", fn);
    ir::BasicBlock* b_c1c = builder->createBasicBlock("c1c", fn);
    ir::BasicBlock* b_c1a = builder->createBasicBlock("c1a", fn);
    ir::BasicBlock* b_c2i = builder->createBasicBlock("c2i", fn);
    ir::BasicBlock* b_c2c = builder->createBasicBlock("c2c", fn);
    ir::BasicBlock* b_c2a = builder->createBasicBlock("c2a", fn);
    ir::BasicBlock* b_done = builder->createBasicBlock("done", fn);

    builder->setInsertPoint(b_entry);
    auto it = fn->getParameters().begin();
    ir::Value* s1 = it->get();
    it++;
    ir::Value* s2 = it->get();
    ir::Instruction* l1 = builder->createAlloc(ctx->getConstantInt(ctx->getIntegerType(64), 8), ctx->getIntegerType(64));
    ir::Instruction* l2 = builder->createAlloc(ctx->getConstantInt(ctx->getIntegerType(64), 8), ctx->getIntegerType(64));
    builder->createStore(ctx->getConstantInt(ctx->getIntegerType(64), 0), l1);
    builder->createStore(ctx->getConstantInt(ctx->getIntegerType(64), 0), l2);
    builder->createJmp(b_l1);

    builder->setInsertPoint(b_l1);
    ir::Value* cl1 = builder->createLoad(l1);
    ir::Value* ch1 = builder->createLoadub(builder->createAdd(s1, cl1));
    builder->createStore(builder->createAdd(cl1, ctx->getConstantInt(ctx->getIntegerType(64), 1)), l1);
    builder->createBr(builder->createCeq(ch1, ctx->getConstantInt(ctx->getIntegerType(8), 0)), b_l1d, b_l1);

    builder->setInsertPoint(b_l1d);
    builder->createStore(builder->createSub(builder->createLoad(l1), ctx->getConstantInt(ctx->getIntegerType(64), 1)), l1);
    builder->createJmp(b_l2);

    builder->setInsertPoint(b_l2);
    ir::Value* cl2 = builder->createLoad(l2);
    ir::Value* ch2 = builder->createLoadub(builder->createAdd(s2, cl2));
    builder->createStore(builder->createAdd(cl2, ctx->getConstantInt(ctx->getIntegerType(64), 1)), l2);
    builder->createBr(builder->createCeq(ch2, ctx->getConstantInt(ctx->getIntegerType(8), 0)), b_l2d, b_l2);

    builder->setInsertPoint(b_l2d);
    builder->createStore(builder->createSub(builder->createLoad(l2), ctx->getConstantInt(ctx->getIntegerType(64), 1)), l2);
    builder->createJmp(b_alloc);

    builder->setInsertPoint(b_alloc);
    ir::Instruction* out = builder->createExternCall("memory.alloc", {builder->createAdd(builder->createAdd(builder->createLoad(l1), builder->createLoad(l2)), ctx->getConstantInt(ctx->getIntegerType(64), 1))}, ctx->getPointerType(ctx->getIntegerType(8)));
    ir::Instruction* i = builder->createAlloc(ctx->getConstantInt(ctx->getIntegerType(64), 8), ctx->getIntegerType(64));
    builder->createStore(ctx->getConstantInt(ctx->getIntegerType(64), 0), i);
    builder->createJmp(b_c1c);

    builder->setInsertPoint(b_c1c);
    builder->createBr(builder->createCeq(builder->createLoad(i), builder->createLoad(l1)), b_c2i, b_c1a);

    builder->setInsertPoint(b_c1a);
    ir::Value* ci1 = builder->createLoad(i);
    builder->createStoreb(builder->createLoadub(builder->createAdd(s1, ci1)), builder->createAdd(out, ci1));
    builder->createStore(builder->createAdd(ci1, ctx->getConstantInt(ctx->getIntegerType(64), 1)), i);
    builder->createJmp(b_c1c);

    builder->setInsertPoint(b_c2i);
    builder->createStore(ctx->getConstantInt(ctx->getIntegerType(64), 0), i);
    builder->createJmp(b_c2c);

    builder->setInsertPoint(b_c2c);
    builder->createBr(builder->createCeq(builder->createLoad(i), builder->createLoad(l2)), b_done, b_c2a);

    builder->setInsertPoint(b_c2a);
    ir::Value* ci2 = builder->createLoad(i);
    ir::Value* out_offset = builder->createAdd(builder->createLoad(l1), ci2);
    builder->createStoreb(builder->createLoadub(builder->createAdd(s2, ci2)), builder->createAdd(out, out_offset));
    builder->createStore(builder->createAdd(ci2, ctx->getConstantInt(ctx->getIntegerType(64), 1)), i);
    builder->createJmp(b_c2c);

    builder->setInsertPoint(b_done);
    ir::Value* final_len = builder->createAdd(builder->createLoad(l1), builder->createLoad(l2));
    builder->createStoreb(ctx->getConstantInt(ctx->getIntegerType(8), 0), builder->createAdd(out, final_len));
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
    ir::BasicBlock* b_is_str = builder->createBasicBlock("fmt_is_str", fn);
    ir::BasicBlock* b_fmt_proc = builder->createBasicBlock("fmt_proc", fn);

    ir::Value* is_small = builder->createCslt(arg_val, ctx->getConstantInt(i64, 65536));
    ir::Value* is_nonneg = builder->createCsge(arg_val, ctx->getConstantInt(i64, 0));
    ir::Value* is_int_arg = builder->createAnd(is_small, is_nonneg);
    builder->createBr(is_int_arg, b_is_num, b_is_str);

    // Number conversion branch: format integer arg_val into ASCII buffer
    builder->setInsertPoint(b_is_num);
    ir::Instruction* num_buf = builder->createExternCall("memory.alloc", {ctx->getConstantInt(i64, 32)}, i64);
    ir::Value* num_end = builder->createAdd(num_buf, ctx->getConstantInt(i64, 31));
    builder->createStoreb(ctx->getConstantInt(i8, 0), num_end);

    ir::Instruction* v_num = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    ir::Instruction* v_ptr = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(arg_val, v_num);
    builder->createStore(num_end, v_ptr);

    ir::BasicBlock* b_num_loop = builder->createBasicBlock("fmt_num_loop", fn);
    ir::BasicBlock* b_num_done = builder->createBasicBlock("fmt_num_done", fn);
    builder->createJmp(b_num_loop);

    builder->setInsertPoint(b_num_loop);
    ir::Value* cur_n = builder->createLoad(v_num);
    ir::Value* rem = builder->createRem(cur_n, ctx->getConstantInt(i64, 10));
    ir::Value* next_n = builder->createDiv(cur_n, ctx->getConstantInt(i64, 10));
    ir::Value* ascii_ch = builder->createAdd(rem, ctx->getConstantInt(i64, 48));
    ir::Value* cur_p = builder->createLoad(v_ptr);
    ir::Value* next_p = builder->createSub(cur_p, ctx->getConstantInt(i64, 1));
    builder->createStoreb(ascii_ch, next_p);
    builder->createStore(next_n, v_num);
    builder->createStore(next_p, v_ptr);
    ir::Value* num_cond = builder->createCuge(next_n, ctx->getConstantInt(i64, 1));
    builder->createBr(num_cond, b_num_loop, b_num_done);

    builder->setInsertPoint(b_num_done);
    ir::Value* final_num_str = builder->createLoad(v_ptr);
    ir::Value* num_len = builder->createSub(num_end, final_num_str);
    builder->createStore(final_num_str, arg_str_slot);
    builder->createStore(num_len, arg_len_slot);
    builder->createJmp(b_fmt_proc);

    // String branch: arg_val is already an i8* string pointer
    builder->setInsertPoint(b_is_str);
    builder->createStore(arg_val, arg_str_slot);
    // Find length of arg_val string
    ir::Instruction* slen_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), slen_slot);
    ir::BasicBlock* b_slen_loop = builder->createBasicBlock("fmt_slen_loop", fn);
    ir::BasicBlock* b_slen_done = builder->createBasicBlock("fmt_slen_done", fn);
    builder->createJmp(b_slen_loop);

    builder->setInsertPoint(b_slen_loop);
    ir::Value* cur_slen = builder->createLoad(slen_slot);
    ir::Value* slen_ch = builder->createLoadub(builder->createAdd(arg_val, cur_slen));
    builder->createStore(builder->createAdd(cur_slen, ctx->getConstantInt(i64, 1)), slen_slot);
    builder->createBr(builder->createCeq(slen_ch, ctx->getConstantInt(i8, 0)), b_slen_done, b_slen_loop);

    builder->setInsertPoint(b_slen_done);
    ir::Value* actual_slen = builder->createSub(builder->createLoad(slen_slot), ctx->getConstantInt(i64, 1));
    builder->createStore(actual_slen, arg_len_slot);
    builder->createJmp(b_fmt_proc);

    // Main formatting: scan fmt_val for "%s"
    builder->setInsertPoint(b_fmt_proc);
    ir::Instruction* pos_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), pos_slot);

    ir::BasicBlock* b_scan_loop = builder->createBasicBlock("fmt_scan_loop", fn);
    ir::BasicBlock* b_check_s   = builder->createBasicBlock("fmt_check_s", fn);
    ir::BasicBlock* b_scan_next = builder->createBasicBlock("fmt_scan_next", fn);
    ir::BasicBlock* b_no_pct    = builder->createBasicBlock("fmt_no_pct", fn);
    ir::BasicBlock* b_do_replace = builder->createBasicBlock("fmt_do_replace", fn);

    builder->createJmp(b_scan_loop);

    builder->setInsertPoint(b_scan_loop);
    ir::Value* cur_pos = builder->createLoad(pos_slot);
    ir::Value* c1 = builder->createLoadub(builder->createAdd(fmt_val, cur_pos));
    ir::Value* is_end = builder->createCeq(c1, ctx->getConstantInt(i8, 0));
    builder->createBr(is_end, b_no_pct, b_check_s);

    builder->setInsertPoint(b_check_s);
    ir::Value* is_pct = builder->createCeq(c1, ctx->getConstantInt(i8, 37)); // '%'
    ir::Value* c2 = builder->createLoadub(builder->createAdd(fmt_val, builder->createAdd(cur_pos, ctx->getConstantInt(i64, 1))));
    ir::Value* is_s = builder->createCeq(c2, ctx->getConstantInt(i8, 115)); // 's'
    ir::Value* is_match = builder->createAnd(is_pct, is_s);
    builder->createBr(is_match, b_do_replace, b_scan_next);

    builder->setInsertPoint(b_scan_next);
    ir::Value* next_pos = builder->createAdd(cur_pos, ctx->getConstantInt(i64, 1));
    builder->createStore(next_pos, pos_slot);
    builder->createJmp(b_scan_loop);

    builder->setInsertPoint(b_no_pct);
    builder->createRet(fmt_val);

    // Do replace branch: copy fmt_val[0..pos] + arg_str + fmt_val[pos+2..end]
    builder->setInsertPoint(b_do_replace);
    ir::Value* match_pos = cur_pos;
    ir::Value* arg_str_ptr = builder->createLoad(arg_str_slot);
    ir::Value* arg_len_val = builder->createLoad(arg_len_slot);

    // Calculate strlen(fmt_val)
    ir::Instruction* fmt_len_slot = builder->createAlloc(ctx->getConstantInt(i64, 8), i64);
    builder->createStore(ctx->getConstantInt(i64, 0), fmt_len_slot);
    ir::BasicBlock* b_flen_loop = builder->createBasicBlock("fmt_flen_loop", fn);
    ir::BasicBlock* b_flen_done = builder->createBasicBlock("fmt_flen_done", fn);
    builder->createJmp(b_flen_loop);

    builder->setInsertPoint(b_flen_loop);
    ir::Value* cur_flen = builder->createLoad(fmt_len_slot);
    ir::Value* flen_ch = builder->createLoadub(builder->createAdd(fmt_val, cur_flen));
    builder->createStore(builder->createAdd(cur_flen, ctx->getConstantInt(i64, 1)), fmt_len_slot);
    builder->createBr(builder->createCeq(flen_ch, ctx->getConstantInt(i8, 0)), b_flen_done, b_flen_loop);

    builder->setInsertPoint(b_flen_done);
    ir::Value* fmt_total_len = builder->createSub(builder->createLoad(fmt_len_slot), ctx->getConstantInt(i64, 1));
    ir::Value* suffix_len = builder->createSub(fmt_total_len, builder->createAdd(match_pos, ctx->getConstantInt(i64, 2)));

    ir::Value* total_out_len = builder->createAdd(builder->createAdd(match_pos, arg_len_val), suffix_len);
    ir::Value* alloc_out_size = builder->createAdd(total_out_len, ctx->getConstantInt(i64, 1));
    ir::Instruction* out_p = builder->createExternCall("memory.alloc", {alloc_out_size}, i64);

    // Copy prefix: fmt_val[0..match_pos]
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
    ir::Value* ch1 = builder->createLoadub(builder->createAdd(fmt_val, idx1));
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
    ir::Value* src3 = builder->createAdd(fmt_val, builder->createAdd(builder->createAdd(match_pos, ctx->getConstantInt(i64, 2)), idx3));
    ir::Value* ch3 = builder->createLoadub(src3);
    ir::Value* dst3 = builder->createAdd(out_p, builder->createAdd(builder->createAdd(match_pos, arg_len_val), idx3));
    builder->createStoreb(ch3, dst3);
    builder->createStore(builder->createAdd(idx3, ctx->getConstantInt(i64, 1)), ci);
    builder->createJmp(b_c3_loop);

    builder->setInsertPoint(b_c3_done);
    builder->createStoreb(ctx->getConstantInt(i8, 0), builder->createAdd(out_p, total_out_len));
    builder->createRet(out_p);

    if (old_bb) builder->setInsertPoint(old_bb);
}

void FyraBuiltinFunctions::emit_substring_ir(ir::Module* module, ir::IRBuilder* builder) {
    auto ctx = module->getContextShared();
    auto i64 = ctx->getIntegerType(64);
    auto ptr_i8 = ctx->getPointerType(ctx->getIntegerType(8));

    auto make_sub = [&](const std::string& name) {
        ir::Function* fn = module->getFunction(name);
        if (!fn) fn = builder->createFunction(name, ptr_i8, {ptr_i8, i64, i64});
        if (!fn->getBasicBlocks().empty()) return;

        ir::BasicBlock* b_entry = builder->createBasicBlock("entry", fn);
        builder->setInsertPoint(b_entry);
        auto it = fn->getParameters().begin();
        ir::Value* str_ptr = it->get(); it++;
        ir::Value* start = it->get(); it++;
        ir::Value* end = it->get();

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
        ir::Value* alloc_size = builder->createAdd(sub_len, ctx->getConstantInt(i64, 1));
        ir::Instruction* new_str = builder->createExternCall("memory.alloc", {alloc_size}, ptr_i8);

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
        ir::Value* ch = builder->createLoadub(builder->createAdd(str_ptr, src_idx));
        builder->createStoreb(ch, builder->createAdd(new_str, i));
        builder->createStore(builder->createAdd(i, ctx->getConstantInt(i64, 1)), i_slot);
        builder->createJmp(b_loop);

        builder->setInsertPoint(b_done);
        builder->createStoreb(ctx->getConstantInt(ctx->getIntegerType(8), 0), builder->createAdd(new_str, sub_len));
        builder->createRet(new_str);
    };

    ir::BasicBlock* old_bb = builder->getInsertPoint();
    make_sub("_builtin_substring");
    make_sub("substring");
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

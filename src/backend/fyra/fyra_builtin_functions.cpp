// fyra_builtin_functions.cpp - Built-in functions implemented in Fyra IR

#include "fyra_builtin_functions.hh"
#include "ir/Constant.h"
#include "ir/Type.h"
#include "ir/Syscall.h"

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
    if (name == "print") return "lm_print"; 
    if (name == "assert") return "lm_assert";
    if (name == "len") return "lm_list_len"; // Or lm_print_str length if we want.
    return name;
}

void FyraBuiltinFunctions::emit_used_builtins(ir::Module* module,
                                             ir::IRBuilder* builder,
                                             const std::unordered_set<std::string>& used_builtins) {
    if (used_builtins.count("lm_print_int")) emit_print_int(module, builder);
    if (used_builtins.count("lm_print_str")) emit_print_str(module, builder);
    if (used_builtins.count("lm_assert")) emit_assert(module, builder);
    if (used_builtins.count("lm_box_string")) emit_box_string(module, builder);
    if (used_builtins.count("abs")) emit_abs(module, builder);

    // External Runtime Declarations - only emit if used
    bool needs_list = false;
    bool needs_tuple = false;
    bool needs_dict = false;
    bool needs_math = false;

    for (const auto& name : used_builtins) {
        if (name.find("list") != std::string::npos) needs_list = true;
        if (name.find("tuple") != std::string::npos) needs_tuple = true;
        if (name.find("dict") != std::string::npos) needs_dict = true;
        if (name == "sqrt" || name == "sin" || name == "cos" || name == "tan" ||
            name == "asin" || name == "acos" || name == "atan" || name == "log" ||
            name == "log10" || name == "exp" || name == "ceil" || name == "floor" ||
            name == "round") needs_math = true;
    }

    if (needs_list) decl_runtime_list(module, builder);
    if (needs_tuple) decl_runtime_tuple(module, builder);
    if (needs_dict) decl_runtime_dict(module, builder);
    if (needs_math) decl_runtime_math(module, builder);
}

void FyraBuiltinFunctions::emit_print_int(ir::Module* module, ir::IRBuilder* builder) {
    ir::Function* print_int = module->getFunction("lm_print_int");
    auto context = module->getContextShared();
    if (!print_int) {
        print_int = builder->createFunction("lm_print_int", context->getVoidType(), {context->getIntegerType(64)});
    }
    if (!print_int->getBasicBlocks().empty()) return;

    ir::BasicBlock* b_entry = builder->createBasicBlock("entry", print_int);
    ir::BasicBlock* b_neg = builder->createBasicBlock("neg", print_int);
    ir::BasicBlock* b_abs = builder->createBasicBlock("abs", print_int);
    ir::BasicBlock* b_loop = builder->createBasicBlock("loop", print_int);
    ir::BasicBlock* b_done = builder->createBasicBlock("done", print_int);

    builder->setInsertPoint(b_entry);
    ir::Value* val = print_int->getParameters().front().get();
    val->setName("val");

    ir::Value* buf = builder->createAlloc(context->getConstantInt(context->getIntegerType(64), 32), context->getIntegerType(64));
    buf->setName("buf");

    ir::Value* ptr = builder->createAdd(buf, context->getConstantInt(context->getIntegerType(64), 31));
    ptr->setName("ptr");

    builder->createStoreb(context->getConstantInt(context->getIntegerType(8), 10), ptr);

    ir::Instruction* val_slot = builder->createAlloc(context->getConstantInt(context->getIntegerType(64), 8), context->getIntegerType(64));
    val_slot->setName("val_slot");

    ir::Instruction* ptr_slot = builder->createAlloc(context->getConstantInt(context->getIntegerType(64), 8), context->getIntegerType(64));
    ptr_slot->setName("ptr_slot");

    builder->createStore(ptr, ptr_slot);

    ir::Value* is_neg = builder->createCslt(val, context->getConstantInt(context->getIntegerType(64), 0));
    is_neg->setName("is_neg");
    builder->createBr(is_neg, b_neg, b_abs);

    builder->setInsertPoint(b_neg);
    ir::GlobalVariable* gv_minus_ptr = nullptr;
    for (auto& gv : module->getGlobalVariables()) {
        if (gv->getName() == "str_minus") {
            gv_minus_ptr = gv.get();
            break;
        }
    }
    if (!gv_minus_ptr) {
        auto gv_minus = std::make_unique<ir::GlobalVariable>(context->getPointerType(context->getIntegerType(8)), "str_minus", context->getConstantString("-"), false, ".data");
        gv_minus_ptr = gv_minus.get();
        module->addGlobalVariable(std::move(gv_minus));
    }

    std::vector<ir::Value*> neg_sys_args = {
        context->getConstantInt(context->getIntegerType(64), 1), // stdout
        gv_minus_ptr,
        context->getConstantInt(context->getIntegerType(64), 1)
    };
    ir::Value* write_neg = builder->createExternCall("io.write", neg_sys_args, context->getIntegerType(64));
    write_neg->setName("write_neg");

    ir::Value* abs_v = builder->createNeg(val);
    abs_v->setName("abs_v");
    builder->createStore(abs_v, val_slot);
    builder->createJmp(b_loop);

    builder->setInsertPoint(b_abs);
    builder->createStore(val, val_slot);
    builder->createJmp(b_loop);

    builder->setInsertPoint(b_loop);
    ir::Value* curr_val = builder->createLoad(val_slot);
    curr_val->setName("curr_val");

    ir::Value* next_val = builder->createDiv(curr_val, context->getConstantInt(context->getIntegerType(64), 10));
    next_val->setName("next_val");

    ir::Value* rem = builder->createRem(curr_val, context->getConstantInt(context->getIntegerType(64), 10));
    rem->setName("rem");

    ir::Value* ascii = builder->createAdd(rem, context->getConstantInt(context->getIntegerType(64), 48));
    ascii->setName("ascii");

    ir::Value* curr_ptr = builder->createLoad(ptr_slot);
    curr_ptr->setName("curr_ptr");

    ir::Value* next_ptr = builder->createSub(curr_ptr, context->getConstantInt(context->getIntegerType(64), 1));
    next_ptr->setName("next_ptr");

    ir::Value* cast_ascii = builder->createCast(ascii, context->getIntegerType(8));
    cast_ascii->setName("cast_ascii");
    builder->createStoreb(cast_ascii, next_ptr);

    builder->createStore(next_val, val_slot);
    builder->createStore(next_ptr, ptr_slot);

    ir::Value* cond = builder->createCuge(next_val, context->getConstantInt(context->getIntegerType(64), 1));
    cond->setName("cond");
    builder->createBr(cond, b_loop, b_done);

    builder->setInsertPoint(b_done);
    ir::Value* final_ptr = builder->createLoad(ptr_slot);
    final_ptr->setName("final_ptr");

    ir::Value* end_ptr = builder->createAdd(buf, context->getConstantInt(context->getIntegerType(64), 32));
    end_ptr->setName("end_ptr");

    ir::Value* len = builder->createSub(end_ptr, final_ptr);
    len->setName("len");

    std::vector<ir::Value*> done_sys_args = {
        context->getConstantInt(context->getIntegerType(64), 1), // stdout
        final_ptr,
        len
    };
    ir::Value* write_done = builder->createExternCall("io.write", done_sys_args, context->getIntegerType(64));
    write_done->setName("write_done");
    builder->createRet(nullptr);
}

void FyraBuiltinFunctions::emit_print_str(ir::Module* module, ir::IRBuilder* builder) {
    ir::Function* print_str = module->getFunction("lm_print_str");
    auto context = module->getContextShared();
    if (!print_str) {
        print_str = builder->createFunction("lm_print_str", context->getVoidType(), {context->getPointerType(context->getIntegerType(8))});
    }
    if (!print_str->getBasicBlocks().empty()) return;

    ir::BasicBlock* ps_entry = builder->createBasicBlock("entry", print_str);
    ir::BasicBlock* ps_loop = builder->createBasicBlock("loop", print_str);
    ir::BasicBlock* ps_done = builder->createBasicBlock("done", print_str);

    builder->setInsertPoint(ps_entry);
    ir::Value* s_val = print_str->getParameters().front().get();
    s_val->setName("s_val");

    ir::Instruction* len_slot = builder->createAlloc(context->getConstantInt(context->getIntegerType(64), 8), context->getIntegerType(64));
    len_slot->setName("len_slot");
    builder->createStore(context->getConstantInt(context->getIntegerType(64), 0), len_slot);
    builder->createJmp(ps_loop);

    builder->setInsertPoint(ps_loop);
    ir::Value* curr_len = builder->createLoad(len_slot);
    curr_len->setName("curr_len");

    ir::Value* ps_curr_ptr = builder->createAdd(s_val, curr_len);
    ps_curr_ptr->setName("ps_curr_ptr");

    ir::Value* curr_char = builder->createLoadub(ps_curr_ptr);
    curr_char->setName("curr_char");

    ir::Value* is_null = builder->createCeq(curr_char, context->getConstantInt(context->getIntegerType(8), 0));
    is_null->setName("is_null");

    ir::Value* next_len = builder->createAdd(curr_len, context->getConstantInt(context->getIntegerType(64), 1));
    next_len->setName("next_len");
    builder->createStore(next_len, len_slot);
    builder->createBr(is_null, ps_done, ps_loop);

    builder->setInsertPoint(ps_done);
    ir::Value* final_len = builder->createLoad(len_slot);
    final_len->setName("final_len");

    ir::Value* actual_len = builder->createSub(final_len, context->getConstantInt(context->getIntegerType(64), 1));
    actual_len->setName("actual_len");

    std::vector<ir::Value*> ps_sys_args = {
        context->getConstantInt(context->getIntegerType(64), 1), // stdout
        s_val,
        actual_len
    };
    ir::Value* write_res = builder->createExternCall("io.write", ps_sys_args, context->getIntegerType(64));
    write_res->setName("write_res");
    
    ir::GlobalVariable* gv_nl_ptr = nullptr;
    for (auto& gv : module->getGlobalVariables()) {
        if (gv->getName() == "nl") {
            gv_nl_ptr = gv.get();
            break;
        }
    }
    if (!gv_nl_ptr) {
        auto gv_nl = std::make_unique<ir::GlobalVariable>(context->getPointerType(context->getIntegerType(8)), "nl", context->getConstantString("\n"), false, ".data");
        gv_nl_ptr = gv_nl.get();
        module->addGlobalVariable(std::move(gv_nl));
    }
    std::vector<ir::Value*> nl_sys_args = {
        context->getConstantInt(context->getIntegerType(64), 1), // stdout
        gv_nl_ptr,
        context->getConstantInt(context->getIntegerType(64), 1)
    };
    ir::Value* write_res2 = builder->createExternCall("io.write", nl_sys_args, context->getIntegerType(64));
    write_res2->setName("write_res");

    builder->createRet(nullptr);
}

void FyraBuiltinFunctions::emit_assert(ir::Module* module, ir::IRBuilder* builder) {
    ir::Function* lm_assert = module->getFunction("lm_assert");
    auto context = module->getContextShared();
    if (!lm_assert) {
        lm_assert = builder->createFunction("lm_assert", context->getVoidType(), {context->getIntegerType(64), context->getIntegerType(64)});
    }
    if (!lm_assert->getBasicBlocks().empty()) return;

    ir::BasicBlock* a_entry = builder->createBasicBlock("entry", lm_assert);
    ir::BasicBlock* a_fail = builder->createBasicBlock("fail", lm_assert);
    ir::BasicBlock* a_pass = builder->createBasicBlock("pass", lm_assert);

    builder->setInsertPoint(a_entry);
    ir::Value* a_cond = lm_assert->getParameters().front().get();
    a_cond->setName("a_cond");
    ir::Value* a_msg = lm_assert->getParameters().back().get();
    a_msg->setName("a_msg");
    builder->createBr(a_cond, a_pass, a_fail);

    builder->setInsertPoint(a_fail);
    // Print "Assertion failed: " message before exiting
    std::string fail_msg = "Assertion failed\n";
    ir::GlobalVariable* assert_fail_gv = nullptr;
    for (auto& gv : module->getGlobalVariables()) {
        if (gv->getName() == "assert_fail") {
            assert_fail_gv = gv.get();
            break;
        }
    }
    if (!assert_fail_gv) {
        auto gv = std::make_unique<ir::GlobalVariable>(
            context->getPointerType(context->getIntegerType(8)),
            "assert_fail",
            context->getConstantString(fail_msg),
            false,
            ".data"
        );
        assert_fail_gv = gv.get();
        module->addGlobalVariable(std::move(gv));
    }
    std::vector<ir::Value*> fail_print_args = {
        context->getConstantInt(context->getIntegerType(64), 1), // stdout
        assert_fail_gv,
        context->getConstantInt(context->getIntegerType(64), fail_msg.length())
    };
    ir::Value* fail_write = builder->createExternCall("io.write", fail_print_args, context->getIntegerType(64));
    fail_write->setName("fail_write");
    
    std::vector<ir::Value*> fail_sys_args = {
        context->getConstantInt(context->getIntegerType(64), 1) // exit status
    };
    ir::Value* fail_exit = builder->createExternCall("process.exit", fail_sys_args, context->getIntegerType(64));
    fail_exit->setName("fail_exit");
    builder->createRet(nullptr);

    builder->setInsertPoint(a_pass);
    builder->createRet(nullptr);
}

void FyraBuiltinFunctions::emit_box_string(ir::Module* module, ir::IRBuilder* builder) {
    if (module->getFunction("lm_box_string")) return;
    auto context = module->getContextShared();
    ir::Function* box_string = builder->createFunction("lm_box_string", context->getIntegerType(64), {context->getIntegerType(64)});
    ir::BasicBlock* s_entry = builder->createBasicBlock("entry", box_string);
    builder->setInsertPoint(s_entry);
    ir::Value* param = box_string->getParameters().front().get();
    param->setName("str");
    builder->createRet(param);
}

void FyraBuiltinFunctions::emit_abs(ir::Module* module, ir::IRBuilder* builder) {
    if (module->getFunction("abs")) return;
    auto context = module->getContextShared();
    ir::Function* abs_f = builder->createFunction("abs", context->getIntegerType(64), {context->getIntegerType(64)});
    ir::BasicBlock* entry = builder->createBasicBlock("entry", abs_f);
    ir::BasicBlock* is_neg = builder->createBasicBlock("is_neg", abs_f);
    ir::BasicBlock* is_pos = builder->createBasicBlock("is_pos", abs_f);

    builder->setInsertPoint(entry);
    ir::Value* val = abs_f->getParameters().front().get();
    val->setName("val");
    ir::Value* cond = builder->createCslt(val, context->getConstantInt(context->getIntegerType(64), 0));
    cond->setName("cond");
    builder->createBr(cond, is_neg, is_pos);

    builder->setInsertPoint(is_neg);
    ir::Value* neg_val = builder->createNeg(val);
    neg_val->setName("neg_val");
    builder->createRet(neg_val);

    builder->setInsertPoint(is_pos);
    builder->createRet(val);
}

void FyraBuiltinFunctions::decl_runtime_list(ir::Module* module, ir::IRBuilder* builder) {
    auto context = module->getContextShared();
    if (!module->getFunction("lm_list_new"))
        builder->createFunction("lm_list_new", context->getIntegerType(64), {});
    if (!module->getFunction("lm_list_append"))
        builder->createFunction("lm_list_append", context->getVoidType(), {context->getIntegerType(64), context->getIntegerType(64)});
    if (!module->getFunction("lm_list_get"))
        builder->createFunction("lm_list_get", context->getIntegerType(64), {context->getIntegerType(64), context->getIntegerType(64)});
    if (!module->getFunction("lm_list_set"))
        builder->createFunction("lm_list_set", context->getVoidType(), {context->getIntegerType(64), context->getIntegerType(64), context->getIntegerType(64)});
    if (!module->getFunction("lm_list_len"))
        builder->createFunction("lm_list_len", context->getIntegerType(64), {context->getIntegerType(64)});
}

void FyraBuiltinFunctions::decl_runtime_dict(ir::Module* module, ir::IRBuilder* builder) {
    auto context = module->getContextShared();
    if (!module->getFunction("jit_dict_new"))
        builder->createFunction("jit_dict_new", context->getIntegerType(64), {});
    if (!module->getFunction("lm_dict_set"))
        builder->createFunction("lm_dict_set", context->getVoidType(), {context->getIntegerType(64), context->getIntegerType(64), context->getIntegerType(64)});
    if (!module->getFunction("lm_dict_get"))
        builder->createFunction("lm_dict_get", context->getIntegerType(64), {context->getIntegerType(64), context->getIntegerType(64)});
}

void FyraBuiltinFunctions::decl_runtime_tuple(ir::Module* module, ir::IRBuilder* builder) {
    auto context = module->getContextShared();
    if (!module->getFunction("lm_tuple_new"))
        builder->createFunction("lm_tuple_new", context->getIntegerType(64), {context->getIntegerType(64)});
    if (!module->getFunction("lm_tuple_set"))
        builder->createFunction("lm_tuple_set", context->getVoidType(), {context->getIntegerType(64), context->getIntegerType(64), context->getIntegerType(64)});
    if (!module->getFunction("lm_tuple_get"))
        builder->createFunction("lm_tuple_get", context->getIntegerType(64), {context->getIntegerType(64), context->getIntegerType(64)});
}

void FyraBuiltinFunctions::decl_runtime_math(ir::Module* module, ir::IRBuilder* builder) {
    auto context = module->getContextShared();
    std::vector<std::string> math_funcs = {"sqrt", "sin", "cos", "tan", "asin", "acos", "atan", "log", "log10", "exp", "ceil", "floor"};
    for (const auto& name : math_funcs) {
        if (!module->getFunction(name))
            builder->createFunction(name, context->getDoubleType(), {context->getDoubleType()});
    }
    if (!module->getFunction("round"))
        builder->createFunction("round", context->getDoubleType(), {context->getDoubleType(), context->getIntegerType(64)});
}

void FyraBuiltinFunctions::decl_runtime_string(ir::Module* module, ir::IRBuilder* builder) {
    auto context = module->getContextShared();
    if (!module->getFunction("concat"))
        builder->createFunction("concat", context->getPointerType(context->getIntegerType(8)), {context->getPointerType(context->getIntegerType(8)), context->getPointerType(context->getIntegerType(8))});
    if (!module->getFunction("length"))
        builder->createFunction("length", context->getIntegerType(64), {context->getPointerType(context->getIntegerType(8))});
    if (!module->getFunction("substring"))
        builder->createFunction("substring", context->getPointerType(context->getIntegerType(8)), {context->getPointerType(context->getIntegerType(8)), context->getIntegerType(64), context->getIntegerType(64)});
    if (!module->getFunction("str_format"))
        builder->createFunction("str_format", context->getPointerType(context->getIntegerType(8)), {context->getPointerType(context->getIntegerType(8)), context->getIntegerType(64)});
}

void FyraBuiltinFunctions::decl_runtime_utility(ir::Module* module, ir::IRBuilder* builder) {
    auto context = module->getContextShared();
    if (!module->getFunction("typeof"))
        builder->createFunction("typeof", context->getPointerType(context->getIntegerType(8)), {context->getIntegerType(64)});
    if (!module->getFunction("clock"))
        builder->createFunction("clock", context->getDoubleType(), {});
    if (!module->getFunction("sleep"))
        builder->createFunction("sleep", context->getVoidType(), {context->getDoubleType()});
    if (!module->getFunction("channel"))
        builder->createFunction("channel", context->getIntegerType(64), {});
    if (!module->getFunction("time"))
        builder->createFunction("time", context->getIntegerType(64), {});
    if (!module->getFunction("date"))
        builder->createFunction("date", context->getPointerType(context->getIntegerType(8)), {});
    if (!module->getFunction("now"))
        builder->createFunction("now", context->getPointerType(context->getIntegerType(8)), {});
}

} // namespace LM::Backend::Fyra

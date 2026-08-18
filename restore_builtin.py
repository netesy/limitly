import sys

with open('src/backend/fyra/fyra_builtin_functions.cpp', 'r') as f:
    content = f.read()

# Replace emit_box_string
old_box_string = """void FyraBuiltinFunctions::emit_box_string(ir::Module* module, ir::IRBuilder* builder) {
    if (module->getFunction("lm_box_string")) return;
    auto context = module->getContextShared();
    ir::Function* box_string = builder->createFunction("lm_box_string", context->getIntegerType(64), {context->getIntegerType(64)});
    ir::BasicBlock* s_entry = builder->createBasicBlock("entry", box_string);
    builder->setInsertPoint(s_entry);
    builder->createRet(box_string->getParameters().front().get());
}"""

new_box_string = """void FyraBuiltinFunctions::emit_box_string(ir::Module* module, ir::IRBuilder* builder) {
    ir::Function* box_string = module->getFunction("lm_box_string");
    auto context = module->getContextShared();
    if (!box_string) box_string = builder->createFunction("lm_box_string", context->getIntegerType(64), {context->getIntegerType(64)});
    if (!box_string->getBasicBlocks().empty()) return;

    ir::BasicBlock* s_entry = builder->createBasicBlock("entry", box_string);
    builder->setInsertPoint(s_entry);

    ir::Value* str_ptr = box_string->getParameters().front().get();

    // Allocate 24 bytes
    ir::Value* alloc_size = context->getConstantInt(context->getIntegerType(64), 24);
    ir::Value* obj_ptr = builder->createMemoryAlloc(alloc_size, ir::MemoryAllocInst::AllocType::Bump);

    // Type tag = 2 (String)
    ir::Value* type_val = context->getConstantInt(context->getIntegerType(64), 2);
    builder->createStore(type_val, obj_ptr);

    // Length = 3 (dummy length for now, print_str relies on null terminator anyway)
    ir::Value* len_val = context->getConstantInt(context->getIntegerType(64), 3);
    ir::Value* len_ptr = builder->createAdd(obj_ptr, context->getConstantInt(context->getIntegerType(64), 8));
    builder->createStore(len_val, len_ptr);

    // Raw string ptr
    ir::Value* data_ptr = builder->createAdd(obj_ptr, context->getConstantInt(context->getIntegerType(64), 16));
    builder->createStore(str_ptr, data_ptr);

    builder->createRet(obj_ptr);
}"""

content = content.replace(old_box_string, new_box_string)

# Replace emit_abs and add emit_box_float_from_bits
old_abs = """void FyraBuiltinFunctions::emit_abs(ir::Module* module, ir::IRBuilder* builder) {
    if (module->getFunction("abs")) return;
    auto context = module->getContextShared();
    ir::Function* abs_f = builder->createFunction("abs", context->getIntegerType(64), {context->getIntegerType(64)});
    ir::BasicBlock* entry = builder->createBasicBlock("entry", abs_f);
    ir::BasicBlock* is_neg = builder->createBasicBlock("is_neg", abs_f);
    ir::BasicBlock* is_pos = builder->createBasicBlock("is_pos", abs_f);

    builder->setInsertPoint(entry);
    ir::Value* val = abs_f->getParameters().front().get();
    ir::Value* cond = builder->createCslt(val, context->getConstantInt(context->getIntegerType(64), 0));
    builder->createBr(cond, is_neg, is_pos);

    builder->setInsertPoint(is_neg);
    builder->createRet(builder->createNeg(val));

    builder->setInsertPoint(is_pos);
    builder->createRet(val);
}"""

new_abs = """void FyraBuiltinFunctions::emit_box_float_from_bits(ir::Module* module, ir::IRBuilder* builder) {
    ir::Function* box_f = module->getFunction("lm_box_float_from_bits");
    auto context = module->getContextShared();
    if (!box_f) box_f = builder->createFunction("lm_box_float_from_bits", context->getIntegerType(64), {context->getIntegerType(64)});
    if (!box_f->getBasicBlocks().empty()) return;

    ir::BasicBlock* entry = builder->createBasicBlock("entry", box_f);
    builder->setInsertPoint(entry);

    ir::Value* bits = box_f->getParameters().front().get();

    // Allocate 16 bytes
    ir::Value* alloc_size = context->getConstantInt(context->getIntegerType(64), 16);
    ir::Value* obj_ptr = builder->createMemoryAlloc(alloc_size, ir::MemoryAllocInst::AllocType::Bump);

    // Type tag = 3 (Float)
    ir::Value* type_val = context->getConstantInt(context->getIntegerType(64), 3);
    builder->createStore(type_val, obj_ptr);

    // Float bits
    ir::Value* data_ptr = builder->createAdd(obj_ptr, context->getConstantInt(context->getIntegerType(64), 8));
    builder->createStore(bits, data_ptr);

    builder->createRet(obj_ptr);
}

void FyraBuiltinFunctions::emit_abs(ir::Module* module, ir::IRBuilder* builder) {
    ir::Function* abs_f = module->getFunction("abs");
    auto context = module->getContextShared();
    if (!abs_f) abs_f = builder->createFunction("abs", context->getIntegerType(64), {context->getIntegerType(64)});
    if (!abs_f->getBasicBlocks().empty()) return;

    ir::BasicBlock* entry = builder->createBasicBlock("entry", abs_f);
    ir::BasicBlock* is_neg = builder->createBasicBlock("is_neg", abs_f);
    ir::BasicBlock* is_pos = builder->createBasicBlock("is_pos", abs_f);

    builder->setInsertPoint(entry);
    ir::Value* val = abs_f->getParameters().front().get();
    ir::Value* cond = builder->createCslt(val, context->getConstantInt(context->getIntegerType(64), 0));
    builder->createBr(cond, is_neg, is_pos);

    builder->setInsertPoint(is_neg);
    builder->createRet(builder->createNeg(val));

    builder->setInsertPoint(is_pos);
    builder->createRet(val);
}"""

content = content.replace(old_abs, new_abs)

# Make sure emit_used_builtins calls emit_box_float_from_bits
content = content.replace(
    'if (used_builtins.count("lm_box_string")) emit_box_string(module, builder);',
    'if (used_builtins.count("lm_box_string")) emit_box_string(module, builder);\n    if (used_builtins.count("lm_box_float_from_bits")) emit_box_float_from_bits(module, builder);'
)

# And fix emit_print_str for Windows WriteFile
old_str = """    std::vector<ir::Value*> ps_sys_args = {
        context->getConstantInt(context->getIntegerType(64), 1), // stdout
        s_val,
        actual_len
    };
    builder->createExternCall("io.write", ps_sys_args, context->getIntegerType(64));
    
    ir::GlobalVariable* gv_nl_ptr = nullptr;
    for (auto& gv : module->getGlobalVariables()) {
        if (gv->getName() == "nl") {
            gv_nl_ptr = gv.get();
            break;
        }
    }
    if (!gv_nl_ptr) {
        auto gv_nl = std::make_unique<ir::GlobalVariable>(context->getPointerType(context->getIntegerType(8)), "nl", context->getConstantString("\\n"), false, ".data");
        gv_nl_ptr = gv_nl.get();
        module->addGlobalVariable(std::move(gv_nl));
    }
    std::vector<ir::Value*> nl_sys_args = {
        context->getConstantInt(context->getIntegerType(64), 1), // stdout
        gv_nl_ptr,
        context->getConstantInt(context->getIntegerType(64), 1)
    };
    builder->createExternCall("io.write", nl_sys_args, context->getIntegerType(64));"""

new_str = """    ir::GlobalVariable* gv_nl_ptr = nullptr;
    for (auto& gv : module->getGlobalVariables()) {
        if (gv->getName() == "nl") {
            gv_nl_ptr = gv.get();
            break;
        }
    }
    if (!gv_nl_ptr) {
        auto gv_nl = std::make_unique<ir::GlobalVariable>(context->getPointerType(context->getIntegerType(8)), "nl", context->getConstantString("\\n"), false, ".data");
        gv_nl_ptr = gv_nl.get();
        module->addGlobalVariable(std::move(gv_nl));
    }
#ifdef _WIN32
    ir::Function* get_std_handle = module->getFunction("GetStdHandle");
    if (!get_std_handle) get_std_handle = builder->createFunction("GetStdHandle", context->getPointerType(context->getIntegerType(8)), {context->getIntegerType(32)});
    ir::Function* write_file = module->getFunction("WriteFile");
    if (!write_file) write_file = builder->createFunction("WriteFile", context->getIntegerType(32), {context->getPointerType(context->getIntegerType(8)), context->getPointerType(context->getIntegerType(8)), context->getIntegerType(32), context->getPointerType(context->getIntegerType(32)), context->getPointerType(context->getIntegerType(8))});
    
    ir::Value* stdout_handle = builder->createCall(get_std_handle, {context->getConstantInt(context->getIntegerType(32), -11)});
    ir::Value* null_ptr = context->getConstantInt(context->getIntegerType(64), 0);
    ir::Value* dword_null = builder->createCast(null_ptr, context->getPointerType(context->getIntegerType(32)));
    ir::Value* ptr_null = builder->createCast(null_ptr, context->getPointerType(context->getIntegerType(8)));
    
    builder->createCall(write_file, {stdout_handle, s_val, builder->createCast(actual_len, context->getIntegerType(32)), dword_null, ptr_null});
    builder->createCall(write_file, {stdout_handle, gv_nl_ptr, context->getConstantInt(context->getIntegerType(32), 1), dword_null, ptr_null});
#else
    std::vector<ir::Value*> ps_sys_args = {
        context->getConstantInt(context->getIntegerType(64), 1), // stdout
        s_val,
        actual_len
    };
    builder->createExternCall("io.write", ps_sys_args, context->getIntegerType(64));

    std::vector<ir::Value*> nl_sys_args = {
        context->getConstantInt(context->getIntegerType(64), 1), // stdout
        gv_nl_ptr,
        context->getConstantInt(context->getIntegerType(64), 1)
    };
    builder->createExternCall("io.write", nl_sys_args, context->getIntegerType(64));
#endif"""

content = content.replace(old_str, new_str)

with open('src/backend/fyra/fyra_builtin_functions.cpp', 'w') as f:
    f.write(content)
print("Done")

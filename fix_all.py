import sys

with open('src/backend/fyra/fyra_builtin_functions.cpp', 'r') as f:
    content = f.read()

# Fix 1: check getBasicBlocks() for lm_box_string
content = content.replace(
    'if (module->getFunction("lm_box_string")) return;\n    auto context = module->getContextShared();\n    ir::Function* box_string = builder->createFunction("lm_box_string", context->getIntegerType(64), {context->getIntegerType(64)});',
    'auto context = module->getContextShared();\n    ir::Function* box_string = module->getFunction("lm_box_string");\n    if (!box_string) box_string = builder->createFunction("lm_box_string", context->getIntegerType(64), {context->getIntegerType(64)});\n    if (!box_string->getBasicBlocks().empty()) return;'
)

# Fix 2: check getBasicBlocks() for lm_box_float_from_bits
content = content.replace(
    'if (module->getFunction("lm_box_float_from_bits")) return;\n    auto context = module->getContextShared();\n    ir::Function* box_f = builder->createFunction("lm_box_float_from_bits", context->getIntegerType(64), {context->getIntegerType(64)});',
    'auto context = module->getContextShared();\n    ir::Function* box_f = module->getFunction("lm_box_float_from_bits");\n    if (!box_f) box_f = builder->createFunction("lm_box_float_from_bits", context->getIntegerType(64), {context->getIntegerType(64)});\n    if (!box_f->getBasicBlocks().empty()) return;'
)

# Fix 3: check getBasicBlocks() for abs
content = content.replace(
    'if (module->getFunction("abs")) return;\n    auto context = module->getContextShared();\n    ir::Function* abs_f = builder->createFunction("abs", context->getIntegerType(64), {context->getIntegerType(64)});',
    'auto context = module->getContextShared();\n    ir::Function* abs_f = module->getFunction("abs");\n    if (!abs_f) abs_f = builder->createFunction("abs", context->getIntegerType(64), {context->getIntegerType(64)});\n    if (!abs_f->getBasicBlocks().empty()) return;'
)

# Fix 4: call emit_box_float_from_bits
content = content.replace(
    'if (used_builtins.count("lm_box_string")) emit_box_string(module, builder);',
    'if (used_builtins.count("lm_box_string")) emit_box_string(module, builder);\n    if (used_builtins.count("lm_box_float_from_bits")) emit_box_float_from_bits(module, builder);'
)

# Fix 5: WriteFile for Windows
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

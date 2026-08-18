import sys

with open('src/backend/fyra/fyra_builtin_functions.cpp', 'r') as f:
    content = f.read()

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

if old_str in content:
    content = content.replace(old_str, new_str)
    with open('src/backend/fyra/fyra_builtin_functions.cpp', 'w') as f:
        f.write(content)
    print("Success")
else:
    print("Old string not found")

import sys

with open('src/backend/fyra/fyra_builtin_functions.cpp', 'r') as f:
    content = f.read()

# Fix context declaration ordering
content = content.replace(
    'ir::Function* box_string = module->getFunction("lm_box_string");\n    if (!box_string) box_string = builder->createFunction("lm_box_string", context->getIntegerType(64), {context->getIntegerType(64)});\n    if (!box_string->getBasicBlocks().empty()) return;\n    auto context = module->getContextShared();',
    'auto context = module->getContextShared();\n    ir::Function* box_string = module->getFunction("lm_box_string");\n    if (!box_string) box_string = builder->createFunction("lm_box_string", context->getIntegerType(64), {context->getIntegerType(64)});\n    if (!box_string->getBasicBlocks().empty()) return;'
)

content = content.replace(
    'ir::Function* box_f = module->getFunction("lm_box_float_from_bits");\n    if (!box_f) box_f = builder->createFunction("lm_box_float_from_bits", context->getIntegerType(64), {context->getIntegerType(64)});\n    if (!box_f->getBasicBlocks().empty()) return;\n    auto context = module->getContextShared();',
    'auto context = module->getContextShared();\n    ir::Function* box_f = module->getFunction("lm_box_float_from_bits");\n    if (!box_f) box_f = builder->createFunction("lm_box_float_from_bits", context->getIntegerType(64), {context->getIntegerType(64)});\n    if (!box_f->getBasicBlocks().empty()) return;'
)

content = content.replace(
    'ir::Function* abs_f = module->getFunction("abs");\n    if (!abs_f) abs_f = builder->createFunction("abs", context->getIntegerType(64), {context->getIntegerType(64)});\n    if (!abs_f->getBasicBlocks().empty()) return;\n    auto context = module->getContextShared();',
    'auto context = module->getContextShared();\n    ir::Function* abs_f = module->getFunction("abs");\n    if (!abs_f) abs_f = builder->createFunction("abs", context->getIntegerType(64), {context->getIntegerType(64)});\n    if (!abs_f->getBasicBlocks().empty()) return;'
)

with open('src/backend/fyra/fyra_builtin_functions.cpp', 'w') as f:
    f.write(content)
print("Done")

import os

def patch_fyra_repo(repo_path):
    func_cpp_path = os.path.join(repo_path, "src", "ir", "Function.cpp")
    if os.path.exists(func_cpp_path):
        content = open(func_cpp_path).read()
        if "unnamed_counter" not in content:
            search_str = "void Function::print(std::ostream& os) const {"
            replace_str = """void Function::print(std::ostream& os) const {
    int unnamed_counter = 0;
    // Pre-pass to name all unnamed instructions

    for (const auto& param : parameters) {
        if (param && param->getName().empty()) {
            param->setName(std::to_string(unnamed_counter++));
        }
    }

    for (const auto& bb : basicBlocks) {
        if (bb) {
            for (const auto& inst : bb->getInstructions()) {
                if (inst && inst->getName().empty()) {
                    inst->setName(std::to_string(unnamed_counter++));
                }
            }
        }
    }"""
            content = content.replace(search_str, replace_str)
            open(func_cpp_path, "w").write(content)

    inst_cpp_path = os.path.join(repo_path, "src", "ir", "Instruction.cpp")
    if os.path.exists(inst_cpp_path):
        content = open(inst_cpp_path).read()
        if "getType() && !getType()->isVoidTy()" not in content:
            search_str1 = "if (!getName().empty()) {"
            replace_str1 = "if (!getName().empty() && getType() && !getType()->isVoidTy()) {"
            content = content.replace(search_str1, replace_str1)

            search_str2 = """    for (const auto& operand : getOperands()) {
        os << " ";
        if (operand) printValue(os, operand->get());
        else os << "null_use";
    }
}"""
            replace_str2 = """    for (const auto& operand : getOperands()) {
        os << " ";
        if (operand) printValue(os, operand->get());
        else os << "null_use";
    }
    if (getType() && !getType()->isVoidTy()) {
        os << " : " << getType()->toString();
    }
}"""
            content = content.replace(search_str2, replace_str2)

            search_str3 = """    os << ")";
}"""
            replace_str3 = """    os << ")";
    if (getType() && !getType()->isVoidTy()) {
        os << " : " << getType()->toString();
    }
}"""
            content = content.replace(search_str3, replace_str3)
            open(inst_cpp_path, "w").write(content)

    module_cpp_path = os.path.join(repo_path, "src", "ir", "Module.cpp")
    if os.path.exists(module_cpp_path):
        content = open(module_cpp_path).read()
        if "void Module::print(std::ostream& os) const" not in content:
            replace_str = """} // namespace ir
#include <iostream>
namespace ir {

void Module::print(std::ostream& os) const {
    for (const auto& gv : globalVariables) {
        os << "global %" << gv->getName() << " = ";
        if (auto* cs = dynamic_cast<ConstantString*>(gv->getInitializer())) {
            os << "\\"" << cs->getValue() << "\\"";
        } else {
            os << "unsupported_global";
        }
        os << "\\n";
    }
    for (const auto& func : functions) {
        func->print(os);
        os << "\\n";
    }
}"""
            content = content.replace("} // namespace ir", replace_str, 1)
            open(module_cpp_path, "w").write(content)

    module_h_path = os.path.join(repo_path, "include", "ir", "Module.h")
    if os.path.exists(module_h_path):
        content = open(module_h_path).read()
        if "void print(std::ostream& os) const;" not in content:
            content = content.replace("void addType(const std::string& name, Type* type);", "void addType(const std::string& name, Type* type);\\n    void print(std::ostream& os) const;")
            open(module_h_path, "w").write(content)

    print("Fyra vendor patched successfully!")

if __name__ == "__main__":
    import sys
    patch_fyra_repo(sys.argv[1] if len(sys.argv) > 1 else "vendor/fyra")

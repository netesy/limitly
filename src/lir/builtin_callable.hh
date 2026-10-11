#pragma once
#include "builtin_functions.hh"
#include "function_registry.hh"
#include "../backend/vm/vm_string.hh"
#include <set>

namespace LM::LIR {
inline constexpr const char* builtin_callable_prefix = "__lymar_callable_";
inline std::string builtin_callable_name(const std::string& name, size_t arity) {
    return std::string(builtin_callable_prefix) + std::to_string(arity) + "." + name;
}
inline std::string builtin_callable_target(const std::string& name) {
    if (!name.starts_with(builtin_callable_prefix)) return {};
    auto dot = name.find('.');
    return dot == std::string::npos ? std::string{} : name.substr(dot + 1);
}
// Canonical adapters give builtin values the same registration, serialization,
// lifetime and lowering path as user callables. No runtime symbol is exposed.
inline void materialize_builtin_callables(const LIR_Function& root) {
    auto& registry = FunctionRegistry::getInstance();
    std::set<std::string> names;
    std::set<size_t> arities;
    auto inspect = [&](const LIR_Function& fn) {
        for (const auto& in : fn.instructions) {
            if (in.op == LIR_Op::CallIndirect) arities.insert(in.call_args.size());
            if (in.op == LIR_Op::LoadConst && IS_PTR(in.const_val)) {
                auto* header = static_cast<ObjHeader*>(UNBOX_PTR(in.const_val));
                if (header->type_id == TYPE_STRING) {
                    auto* string = reinterpret_cast<LmStringHeader*>(header);
                    std::string name(string->data, string->len);
                    if (BuiltinUtils::isBuiltinFunction(name)) names.insert(name);
                }
            }
        }
    };
    inspect(root);
    for (const auto& name : registry.getFunctionNames())
        if (!BuiltinUtils::isBuiltinFunction(name)) inspect(*registry.getFunction(name));
    for (const auto& name : names) {
        auto builtin = LIRBuiltinFunctions::getInstance().getFunction(name);
        const auto fixed = builtin->getParameterTypes().size();
        auto sizes = name == "print" ? arities : name == "input" ? std::set<size_t>{0,1} : std::set<size_t>{fixed};
        for (auto arity : sizes) {
            auto adapter_name = builtin_callable_name(name, arity);
            if (registry.hasFunction(adapter_name)) continue;
            std::vector<LIRParameter> parameters;
            std::vector<Reg> arguments;
            for (Reg p = 0; p < arity; ++p) {
                parameters.push_back({"arg" + std::to_string(p), Type::Ptr});
                arguments.push_back(p);
            }
            auto tag = builtin->getReturnType();
            Type result = tag == TypeTag::String ? Type::Ptr : tag == TypeTag::Bool ? Type::Bool :
                tag == TypeTag::Float64 || tag == TypeTag::Float32 ? Type::F64 : Type::I64;
            auto fn = std::make_shared<LIRFunction>(adapter_name, parameters, result, nullptr);
            std::unordered_map<Reg, TypePtr> language_types;
            for (Reg p = 0; p < arity; ++p) language_types[p] = std::make_shared<::Type>(TypeTag::Any);
            fn->setRegisterLanguageTypes(language_types);
            fn->register_count_ = arity + 1;
            // A synthesized adapter cannot invent frontend ownership proofs.
            fn->inferred_effects_.parameters.assign(arity, Memory::Read | Memory::Opaque);
            fn->inferred_effects_.unknown_result = true;
            std::vector<LIR_Inst> instructions;
            LIR_Inst call(LIR_Op::CallBuiltin, arity, name, arguments);
            call.result_type = result;
            instructions.push_back(call);
            if (tag == TypeTag::Nil) instructions.emplace_back(LIR_Op::LoadConst, Type::I64, arity, VAL_NIL);
            instructions.emplace_back(LIR_Op::Return, result, UINT32_MAX, arity, UINT32_MAX);
            fn->setInstructions(instructions);
            LIRFunctionManager::getInstance().registerFunction(fn);
        }
    }
}
}

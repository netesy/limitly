// fyra_ir_generator.cpp - Direct AST to Fyra IR Code Generation

#include "fyra_ir_generator.hh"

#include <sstream>

namespace LM::Backend::Fyra {

std::string FyraInstruction::to_string() const {
    std::stringstream ss;
    ss << "  ";
    if (!result.empty()) {
        ss << "%" << result << " = ";
    }
    ss << op;
    if (!operands.empty()) {
        ss << " ";
        for (size_t i = 0; i < operands.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << "%" << operands[i];
        }
    }
    ss << " : " << static_cast<int>(result_type);
    if (!comment.empty()) {
        ss << "  ; " << comment;
    }
    return ss.str();
}

std::string FyraIRFunction::to_ir_string() const {
    std::stringstream ss;
    ss << "fn " << name << "(";
    for (size_t i = 0; i < parameters.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << "%" << parameters[i].first << " : " << static_cast<int>(parameters[i].second);
    }
    ss << ") -> " << static_cast<int>(return_type) << " {\n";
    for (const auto& inst : instructions) {
        ss << inst.to_string() << "\n";
    }
    ss << "}\n";
    return ss.str();
}

FyraIRGenerator::FyraIRGenerator() = default;

std::shared_ptr<FyraIRFunction> FyraIRGenerator::generate_from_ast(
    const std::shared_ptr<Frontend::AST::Program>& program) {
    auto out = std::make_shared<FyraIRFunction>();
    out->name = "module";
    out->return_type = FyraType::Void;

    if (!program) {
        errors_.push_back("null AST program passed to FyraIRGenerator");
        return out;
    }

    emit_instruction("module_begin", "", {}, FyraType::Void, "direct AST lowering placeholder");

    for (const auto& stmt : program->statements) {
        auto fn = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt);
        if (fn) {
            emit_instruction("declare_fn", "", {fn->name}, FyraType::Void, "function declaration");
        }
    }

    emit_instruction("module_end", "", {}, FyraType::Void);

    out->instructions = current_instructions_;
    out->local_vars = current_locals_;
    return out;
}

std::shared_ptr<FyraIRFunction> FyraIRGenerator::generate_function(
    const std::shared_ptr<Frontend::AST::FunctionDeclaration>& func_decl) {
    auto out = std::make_shared<FyraIRFunction>();
    if (!func_decl) {
        errors_.push_back("null function declaration passed to FyraIRGenerator");
        out->name = "invalid";
        out->return_type = FyraType::Void;
        return out;
    }

    out->name = func_decl->name;
    out->return_type = FyraType::Void;
    for (const auto& param : func_decl->params) {
        out->parameters.push_back({param.first, FyraType::I64});
    }
    out->instructions.push_back({"fn_begin", "", {}, FyraType::Void, "placeholder body"});
    out->instructions.push_back({"ret", "", {}, FyraType::Void, "implicit return"});
    return out;
}

std::string FyraIRGenerator::get_ir_string() const {
    std::stringstream ss;
    for (const auto& inst : current_instructions_) {
        ss << inst.to_string() << "\n";
    }
    return ss.str();
}

FyraType FyraIRGenerator::ast_type_to_fyra_type(const std::string& ast_type) {
    if (ast_type == "i32") return FyraType::I32;
    if (ast_type == "i64" || ast_type == "int") return FyraType::I64;
    if (ast_type == "f64" || ast_type == "float") return FyraType::F64;
    if (ast_type == "bool") return FyraType::Bool;
    if (ast_type == "ptr") return FyraType::Ptr;
    if (ast_type == "void") return FyraType::Void;
    return FyraType::I64;
}

std::string FyraIRGenerator::fyra_type_to_string(FyraType type) {
    switch (type) {
        case FyraType::I32: return "i32";
        case FyraType::I64: return "i64";
        case FyraType::F64: return "f64";
        case FyraType::Bool: return "bool";
        case FyraType::Ptr: return "ptr";
        case FyraType::Void: return "void";
        case FyraType::Struct: return "struct";
        case FyraType::Array: return "array";
        case FyraType::Function: return "function";
    }
    return "unknown";
}

void FyraIRGenerator::emit_instruction(const std::string& op, const std::string& result,
                                      const std::vector<std::string>& operands,
                                      FyraType result_type, const std::string& comment) {
    FyraInstruction inst;
    inst.op = op;
    inst.result = result;
    inst.operands = operands;
    inst.result_type = result_type;
    inst.comment = comment;
    current_instructions_.push_back(std::move(inst));
}

} // namespace LM::Backend::Fyra

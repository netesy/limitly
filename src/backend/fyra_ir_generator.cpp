// fyra_ir_generator.cpp - Direct AST to Fyra IR Code Generation

#include "fyra_ir_generator.hh"
#include <iostream>
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

std::string FyraIRGenerator::generate_temp_var() {
    return "t" + std::to_string(temp_counter_++);
}

std::string FyraIRGenerator::generate_label() {
    return "L" + std::to_string(label_counter_++);
}

std::shared_ptr<FyraIRFunction> FyraIRGenerator::generate_from_ast(
    const std::shared_ptr<Frontend::AST::Program>& program) {
    
    if (!program) {
        errors_.push_back("Program is null");
        return nullptr;
    }
    
    // Create main function
    auto main_func = std::make_shared<FyraIRFunction>();
    main_func->name = "main";
    main_func->return_type = FyraType::I64;
    
    current_instructions_.clear();
    current_locals_.clear();
    
    // Process all statements in the program
    for (const auto& stmt : program->statements) {
        emit_statement(stmt);
    }
    
    // Add implicit return 0
    emit_instruction("ret", "", {"0"}, FyraType::I64, "implicit return");
    
    main_func->instructions = current_instructions_;
    main_func->local_vars = current_locals_;
    
    return main_func;
}

std::shared_ptr<FyraIRFunction> FyraIRGenerator::generate_function(
    const std::shared_ptr<Frontend::AST::FunctionDeclaration>& func_decl) {
    
    if (!func_decl) {
        errors_.push_back("Function declaration is null");
        return nullptr;
    }
    
    auto fyra_func = std::make_shared<FyraIRFunction>();
    fyra_func->name = func_decl->name;
    
    current_instructions_.clear();
    current_locals_.clear();
    
    // Convert parameters
    for (const auto& param : func_decl->params) {
        std::string param_name = param.first;
        std::string type_name = param.second ? param.second->typeName : "int";
        FyraType param_type = ast_type_to_fyra_type(type_name);
        fyra_func->parameters.push_back({param_name, param_type});
        current_locals_[param_name] = param_type;
    }
    
    // Convert return type
    std::string ret_type_name = func_decl->returnType.has_value() ? func_decl->returnType.value()->typeName : "void";
    fyra_func->return_type = ast_type_to_fyra_type(ret_type_name);
    
    // Process function body
    if (func_decl->body) {
        emit_statement(func_decl->body);
    }
    
    fyra_func->instructions = current_instructions_;
    fyra_func->local_vars = current_locals_;
    
    return fyra_func;
}

std::string FyraIRGenerator::get_ir_string() const {
    std::stringstream ss;
    ss << "; Fyra IR generated from Limit AST\n\n";
    
    // This would be populated with all generated functions
    // For now, return placeholder
    ss << "; IR generation in progress\n";
    
    return ss.str();
}

std::string FyraIRGenerator::emit_expression(
    const std::shared_ptr<Frontend::AST::Expression>& expr) {
    
    if (!expr) {
        errors_.push_back("Expression is null");
        return "";
    }
    
    // Dispatch based on expression type
    if (auto binary = std::dynamic_pointer_cast<Frontend::AST::BinaryExpr>(expr)) {
        return emit_binary_expr(binary);
    } else if (auto unary = std::dynamic_pointer_cast<Frontend::AST::UnaryExpr>(expr)) {
        return emit_unary_expr(unary);
    } else if (auto literal = std::dynamic_pointer_cast<Frontend::AST::LiteralExpr>(expr)) {
        return emit_literal_expr(literal);
    } else if (auto variable = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(expr)) {
        return emit_variable_expr(variable);
    } else if (auto call = std::dynamic_pointer_cast<Frontend::AST::CallExpr>(expr)) {
        return emit_call_expr(call);
    } else if (auto assign = std::dynamic_pointer_cast<Frontend::AST::AssignExpr>(expr)) {
        return emit_assign_expr(assign);
    } else if (auto index = std::dynamic_pointer_cast<Frontend::AST::IndexExpr>(expr)) {
        return emit_index_expr(index);
    } else if (auto member = std::dynamic_pointer_cast<Frontend::AST::MemberExpr>(expr)) {
        return emit_member_expr(member);
    } else if (auto list = std::dynamic_pointer_cast<Frontend::AST::ListExpr>(expr)) {
        return emit_list_expr(list);
    } else if (auto dict = std::dynamic_pointer_cast<Frontend::AST::DictExpr>(expr)) {
        return emit_dict_expr(dict);
    } else if (auto range = std::dynamic_pointer_cast<Frontend::AST::RangeExpr>(expr)) {
        return emit_range_expr(range);
    }
    
    errors_.push_back("Unknown expression type");
    return "";
}

void FyraIRGenerator::emit_statement(
    const std::shared_ptr<Frontend::AST::Statement>& stmt) {
    
    if (!stmt) {
        errors_.push_back("Statement is null");
        return;
    }
    
    // Dispatch based on statement type
    if (auto var_decl = std::dynamic_pointer_cast<Frontend::AST::VarDeclaration>(stmt)) {
        emit_var_declaration(var_decl);
    } else if (auto func_decl = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(stmt)) {
        emit_function_declaration(func_decl);
    } else if (auto block = std::dynamic_pointer_cast<Frontend::AST::BlockStatement>(stmt)) {
        emit_block_statement(block);
    } else if (auto if_stmt = std::dynamic_pointer_cast<Frontend::AST::IfStatement>(stmt)) {
        emit_if_statement(if_stmt);
    } else if (auto while_stmt = std::dynamic_pointer_cast<Frontend::AST::WhileStatement>(stmt)) {
        emit_while_statement(while_stmt);
    } else if (auto for_stmt = std::dynamic_pointer_cast<Frontend::AST::ForStatement>(stmt)) {
        emit_for_statement(for_stmt);
    } else if (auto iter_stmt = std::dynamic_pointer_cast<Frontend::AST::IterStatement>(stmt)) {
        emit_iter_statement(iter_stmt);
    } else if (auto ret_stmt = std::dynamic_pointer_cast<Frontend::AST::ReturnStatement>(stmt)) {
        emit_return_statement(ret_stmt);
    } else if (auto print_stmt = std::dynamic_pointer_cast<Frontend::AST::PrintStatement>(stmt)) {
        emit_print_statement(print_stmt);
    } else if (auto parallel = std::dynamic_pointer_cast<Frontend::AST::ParallelStatement>(stmt)) {
        emit_parallel_statement(parallel);
    } else if (auto concurrent = std::dynamic_pointer_cast<Frontend::AST::ConcurrentStatement>(stmt)) {
        emit_concurrent_statement(concurrent);
    }
}

std::string FyraIRGenerator::emit_binary_expr(
    const std::shared_ptr<Frontend::AST::BinaryExpr>& expr) {
    
    std::string left = emit_expression(expr->left);
    std::string right = emit_expression(expr->right);
    std::string result = generate_temp_var();
    
    std::string op;
    switch (expr->op) {
        case Frontend::TokenType::PLUS: op = "add"; break;
        case Frontend::TokenType::MINUS: op = "sub"; break;
        case Frontend::TokenType::STAR: op = "mul"; break;
        case Frontend::TokenType::SLASH: op = "div"; break;
        case Frontend::TokenType::MODULUS: op = "mod"; break;
        case Frontend::TokenType::EQUAL_EQUAL: op = "eq"; break;
        case Frontend::TokenType::BANG_EQUAL: op = "neq"; break;
        case Frontend::TokenType::LESS: op = "lt"; break;
        case Frontend::TokenType::LESS_EQUAL: op = "le"; break;
        case Frontend::TokenType::GREATER: op = "gt"; break;
        case Frontend::TokenType::GREATER_EQUAL: op = "ge"; break;
        case Frontend::TokenType::AMPERSAND: op = "and"; break;
        case Frontend::TokenType::PIPE: op = "or"; break;
        case Frontend::TokenType::CARET: op = "xor"; break;
        default: op = "unknown"; break;
    }
    
    emit_instruction(op, result, {left, right}, FyraType::I64);
    return result;
}

std::string FyraIRGenerator::emit_unary_expr(
    const std::shared_ptr<Frontend::AST::UnaryExpr>& expr) {
    
    std::string operand = emit_expression(expr->right);
    std::string result = generate_temp_var();
    
    std::string op;
    switch (expr->op) {
        case Frontend::TokenType::MINUS: op = "neg"; break;
        case Frontend::TokenType::BANG: op = "not"; break;
        default: op = "unknown"; break;
    }
    
    emit_instruction(op, result, {operand}, FyraType::I64);
    return result;
}

std::string FyraIRGenerator::emit_literal_expr(
    const std::shared_ptr<Frontend::AST::LiteralExpr>& expr) {
    
    std::string result = generate_temp_var();
    std::string value_str;
    if (std::holds_alternative<std::string>(expr->value)) {
        value_str = std::get<std::string>(expr->value);
    } else if (std::holds_alternative<bool>(expr->value)) {
        value_str = std::get<bool>(expr->value) ? "true" : "false";
    } else {
        value_str = "nil";
    }
    emit_instruction("const", result, {value_str}, FyraType::I64, "literal: " + value_str);
    return result;
}

std::string FyraIRGenerator::emit_variable_expr(
    const std::shared_ptr<Frontend::AST::VariableExpr>& expr) {
    
    return expr->name;
}

std::string FyraIRGenerator::emit_call_expr(
    const std::shared_ptr<Frontend::AST::CallExpr>& expr) {
    
    std::string result = generate_temp_var();
    std::vector<std::string> args;
    
    for (const auto& arg : expr->arguments) {
        args.push_back(emit_expression(arg));
    }
    
    std::string func_name = "unknown";
    if (auto var = std::dynamic_pointer_cast<Frontend::AST::VariableExpr>(expr->callee)) {
        func_name = var->name;
    }
    emit_instruction("call", result, args, FyraType::I64, "call " + func_name);
    return result;
}

std::string FyraIRGenerator::emit_assign_expr(
    const std::shared_ptr<Frontend::AST::AssignExpr>& expr) {
    
    std::string value = emit_expression(expr->value);
    std::string var_name = expr->name;
    
    emit_instruction("mov", var_name, {value}, FyraType::I64, "assign to " + var_name);
    return var_name;
}

std::string FyraIRGenerator::emit_index_expr(
    const std::shared_ptr<Frontend::AST::IndexExpr>& expr) {
    
    std::string object = emit_expression(expr->object);
    std::string index = emit_expression(expr->index);
    std::string result = generate_temp_var();
    
    emit_instruction("load", result, {object, index}, FyraType::I64, "index access");
    return result;
}

std::string FyraIRGenerator::emit_member_expr(
    const std::shared_ptr<Frontend::AST::MemberExpr>& expr) {
    
    std::string object = emit_expression(expr->object);
    std::string result = generate_temp_var();
    
    emit_instruction("member", result, {object}, FyraType::I64, "member: " + expr->name);
    return result;
}

std::string FyraIRGenerator::emit_list_expr(
    const std::shared_ptr<Frontend::AST::ListExpr>& expr) {
    
    std::string result = generate_temp_var();
    std::vector<std::string> elements;
    
    for (const auto& elem : expr->elements) {
        elements.push_back(emit_expression(elem));
    }
    
    emit_instruction("list", result, elements, FyraType::Array, "list literal");
    return result;
}

std::string FyraIRGenerator::emit_dict_expr(
    const std::shared_ptr<Frontend::AST::DictExpr>& expr) {
    
    std::string result = generate_temp_var();
    emit_instruction("dict", result, {}, FyraType::Struct, "dict literal");
    return result;
}

std::string FyraIRGenerator::emit_range_expr(
    const std::shared_ptr<Frontend::AST::RangeExpr>& expr) {
    
    std::string start = emit_expression(expr->start);
    std::string end = emit_expression(expr->end);
    std::string result = generate_temp_var();
    
    emit_instruction("range", result, {start, end}, FyraType::Array, "range");
    return result;
}

void FyraIRGenerator::emit_var_declaration(
    const std::shared_ptr<Frontend::AST::VarDeclaration>& decl) {
    
    std::string type_name = "int";
    if (decl->type.has_value() && decl->type.value()) {
        type_name = decl->type.value()->typeName;
    }
    FyraType var_type = ast_type_to_fyra_type(type_name);
    current_locals_[decl->name] = var_type;
    
    if (decl->initializer) {
        std::string value = emit_expression(decl->initializer);
        emit_instruction("mov", decl->name, {value}, var_type, "var init: " + decl->name);
    }
}

void FyraIRGenerator::emit_function_declaration(
    const std::shared_ptr<Frontend::AST::FunctionDeclaration>& decl) {
    
    // Functions are typically handled separately, not inline
    // This is a placeholder for nested function support
}

void FyraIRGenerator::emit_block_statement(
    const std::shared_ptr<Frontend::AST::BlockStatement>& stmt) {
    
    for (const auto& s : stmt->statements) {
        emit_statement(s);
    }
}

void FyraIRGenerator::emit_if_statement(
    const std::shared_ptr<Frontend::AST::IfStatement>& stmt) {
    
    std::string cond = emit_expression(stmt->condition);
    std::string else_label = generate_label();
    std::string end_label = generate_label();
    
    emit_instruction("jmpif", "", {cond, else_label}, FyraType::Void, "if condition");
    
    emit_statement(stmt->thenBranch);
    emit_instruction("jmp", "", {end_label}, FyraType::Void, "if then branch");
    
    emit_instruction("label", else_label, {}, FyraType::Void, "else label");
    if (stmt->elseBranch) {
        emit_statement(stmt->elseBranch);
    }
    
    emit_instruction("label", end_label, {}, FyraType::Void, "if end");
}

void FyraIRGenerator::emit_while_statement(
    const std::shared_ptr<Frontend::AST::WhileStatement>& stmt) {
    
    std::string loop_label = generate_label();
    std::string end_label = generate_label();
    
    emit_instruction("label", loop_label, {}, FyraType::Void, "while loop");
    
    std::string cond = emit_expression(stmt->condition);
    emit_instruction("jmpif", "", {cond, end_label}, FyraType::Void, "while condition");
    
    emit_statement(stmt->body);
    emit_instruction("jmp", "", {loop_label}, FyraType::Void, "while loop back");
    
    emit_instruction("label", end_label, {}, FyraType::Void, "while end");
}

void FyraIRGenerator::emit_for_statement(
    const std::shared_ptr<Frontend::AST::ForStatement>& stmt) {
    
    // Emit initializer
    if (stmt->initializer) {
        emit_statement(stmt->initializer);
    }
    
    std::string loop_label = generate_label();
    std::string end_label = generate_label();
    
    emit_instruction("label", loop_label, {}, FyraType::Void, "for loop");
    
    // Emit condition
    if (stmt->condition) {
        std::string cond = emit_expression(stmt->condition);
        emit_instruction("jmpif", "", {cond, end_label}, FyraType::Void, "for condition");
    }
    
    // Emit body
    emit_statement(stmt->body);
    
    // Emit increment
    if (stmt->increment) {
        emit_expression(stmt->increment);
    }
    
    emit_instruction("jmp", "", {loop_label}, FyraType::Void, "for loop back");
    emit_instruction("label", end_label, {}, FyraType::Void, "for end");
}

void FyraIRGenerator::emit_iter_statement(
    const std::shared_ptr<Frontend::AST::IterStatement>& stmt) {
    
    std::string iterable = emit_expression(stmt->iterable);
    std::string loop_label = generate_label();
    std::string end_label = generate_label();
    
    emit_instruction("label", loop_label, {}, FyraType::Void, "iter loop");
    std::string loopVar = stmt->loopVars.empty() ? "unused" : stmt->loopVars[0];
    emit_instruction("iter", loopVar, {iterable}, FyraType::I64, "iterate");
    emit_statement(stmt->body);
    emit_instruction("jmp", "", {loop_label}, FyraType::Void, "iter loop back");
    emit_instruction("label", end_label, {}, FyraType::Void, "iter end");
}

void FyraIRGenerator::emit_return_statement(
    const std::shared_ptr<Frontend::AST::ReturnStatement>& stmt) {
    
    if (stmt->value) {
        std::string value = emit_expression(stmt->value);
        emit_instruction("ret", "", {value}, FyraType::I64, "return");
    } else {
        emit_instruction("ret", "", {"0"}, FyraType::I64, "return void");
    }
}

void FyraIRGenerator::emit_print_statement(
    const std::shared_ptr<Frontend::AST::PrintStatement>& stmt) {
    
    for (const auto& expr : stmt->arguments) {
        std::string value = emit_expression(expr);
        emit_instruction("print", "", {value}, FyraType::Void, "print");
    }
}

void FyraIRGenerator::emit_parallel_statement(
    const std::shared_ptr<Frontend::AST::ParallelStatement>& stmt) {
    
    emit_instruction("parallel", "", {}, FyraType::Void, "parallel block");
    if (stmt->body) {
        emit_statement(stmt->body);
    }
}

void FyraIRGenerator::emit_concurrent_statement(
    const std::shared_ptr<Frontend::AST::ConcurrentStatement>& stmt) {
    
    emit_instruction("concurrent", "", {}, FyraType::Void, "concurrent block");
    if (stmt->body) {
        emit_statement(stmt->body);
    }
}

FyraType FyraIRGenerator::ast_type_to_fyra_type(const std::string& ast_type) {
    if (ast_type == "int" || ast_type == "i32" || ast_type == "i64") {
        return FyraType::I64;
    } else if (ast_type == "float" || ast_type == "f64") {
        return FyraType::F64;
    } else if (ast_type == "bool") {
        return FyraType::Bool;
    } else if (ast_type == "str" || ast_type == "string") {
        return FyraType::Ptr;
    } else if (ast_type == "void") {
        return FyraType::Void;
    }
    return FyraType::I64;  // Default
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
        case FyraType::Function: return "fn";
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
    
    current_instructions_.push_back(inst);
}

} // namespace LM::Backend::Fyra

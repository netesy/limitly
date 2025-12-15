#include "generator.hh"
#include "../backend/value.hh"
#include "../backend/types.hh"

namespace LIR {

Generator::Generator() : next_register_(0) {}

std::unique_ptr<LIR_Function> Generator::generate_program(AST::Program& program) {
    // Create a main function
    current_function_ = std::make_unique<LIR_Function>("main", 0);
    variable_registers_.clear();
    next_register_ = 0;
    
    // Process all statements
    for (const auto& stmt : program.statements) {
        emit_stmt(*stmt);
    }
    
    // Add implicit return if none exists
    if (current_function_->instructions.empty() || 
        current_function_->instructions.back().op != LIR_Op::Return) {
        emit_instruction(LIR_Inst(LIR_Op::Return));
    }
    
    auto result = std::move(current_function_);
    current_function_ = nullptr;
    return result;
}

std::unique_ptr<LIR_Function> Generator::generate_function(AST::FunctionDeclaration& fn) {
    // Create function with parameters
    current_function_ = std::make_unique<LIR_Function>(fn.name, fn.params.size());
    variable_registers_.clear();
    next_register_ = fn.params.size();
    
    // Register parameters
    for (size_t i = 0; i < fn.params.size(); ++i) {
        set_variable_register(fn.params[i].first, static_cast<Reg>(i));
    }
    
    // Emit function body
    if (fn.body) {
        emit_stmt(*fn.body);
    }
    
    // Add implicit return if none exists
    if (current_function_->instructions.empty() || 
        current_function_->instructions.back().op != LIR_Op::Return) {
        emit_instruction(LIR_Inst(LIR_Op::Return));
    }
    
    auto result = std::move(current_function_);
    current_function_ = nullptr;
    return result;
}

// Helper methods
Reg Generator::allocate_register() {
    return next_register_++;
}

void Generator::set_variable_register(const std::string& name, Reg reg) {
    variable_registers_[name] = reg;
}

Reg Generator::get_variable_register(const std::string& name) {
    auto it = variable_registers_.find(name);
    return (it != variable_registers_.end()) ? it->second : UINT32_MAX;
}

void Generator::emit_instruction(const LIR_Inst& inst) {
    if (current_function_) {
        current_function_->instructions.push_back(inst);
    }
}

// Error handling
bool Generator::has_errors() const {
    return !errors_.empty();
}

std::vector<std::string> Generator::get_errors() const {
    return errors_;
}

void Generator::report_error(const std::string& message) {
    errors_.push_back(message);
}

// AST node visitors
void Generator::emit_stmt(AST::Statement& stmt) {
    if (auto expr_stmt = dynamic_cast<AST::ExprStatement*>(&stmt)) {
        emit_expr_stmt(*expr_stmt);
    } else if (auto print_stmt = dynamic_cast<AST::PrintStatement*>(&stmt)) {
        emit_print_stmt(*print_stmt);
    } else if (auto var_stmt = dynamic_cast<AST::VarDeclaration*>(&stmt)) {
        emit_var_stmt(*var_stmt);
    } else if (auto block_stmt = dynamic_cast<AST::BlockStatement*>(&stmt)) {
        emit_block_stmt(*block_stmt);
    } else if (auto if_stmt = dynamic_cast<AST::IfStatement*>(&stmt)) {
        emit_if_stmt(*if_stmt);
    } else if (auto while_stmt = dynamic_cast<AST::WhileStatement*>(&stmt)) {
        emit_while_stmt(*while_stmt);
    } else if (auto for_stmt = dynamic_cast<AST::ForStatement*>(&stmt)) {
        emit_for_stmt(*for_stmt);
    } else if (auto return_stmt = dynamic_cast<AST::ReturnStatement*>(&stmt)) {
        emit_return_stmt(*return_stmt);
    } else if (auto func_stmt = dynamic_cast<AST::FunctionDeclaration*>(&stmt)) {
        emit_func_stmt(*func_stmt);
    } else if (auto import_stmt = dynamic_cast<AST::ImportStatement*>(&stmt)) {
        emit_import_stmt(*import_stmt);
    } else if (auto match_stmt = dynamic_cast<AST::MatchStatement*>(&stmt)) {
        emit_match_stmt(*match_stmt);
    } else if (auto contract_stmt = dynamic_cast<AST::ContractStatement*>(&stmt)) {
        emit_contract_stmt(*contract_stmt);
    } else if (auto comptime_stmt = dynamic_cast<AST::ComptimeStatement*>(&stmt)) {
        emit_comptime_stmt(*comptime_stmt);
    } else if (auto parallel_stmt = dynamic_cast<AST::ParallelStatement*>(&stmt)) {
        emit_parallel_stmt(*parallel_stmt);
    } else if (auto concurrent_stmt = dynamic_cast<AST::ConcurrentStatement*>(&stmt)) {
        emit_concurrent_stmt(*concurrent_stmt);
    } else if (auto task_stmt = dynamic_cast<AST::TaskStatement*>(&stmt)) {
        emit_task_stmt(*task_stmt);
    } else if (auto worker_stmt = dynamic_cast<AST::WorkerStatement*>(&stmt)) {
        emit_worker_stmt(*worker_stmt);
    } else if (auto iter_stmt = dynamic_cast<AST::IterStatement*>(&stmt)) {
        emit_iter_stmt(*iter_stmt);
    } else if (auto unsafe_stmt = dynamic_cast<AST::UnsafeStatement*>(&stmt)) {
        emit_unsafe_stmt(*unsafe_stmt);
    } else {
        report_error("Unknown statement type");
    }
}

Reg Generator::emit_expr(AST::Expression& expr) {
    if (auto literal = dynamic_cast<AST::LiteralExpr*>(&expr)) {
        return emit_literal_expr(*literal);
    } else if (auto variable = dynamic_cast<AST::VariableExpr*>(&expr)) {
        return emit_variable_expr(*variable);
    } else if (auto binary = dynamic_cast<AST::BinaryExpr*>(&expr)) {
        return emit_binary_expr(*binary);
    } else if (auto unary = dynamic_cast<AST::UnaryExpr*>(&expr)) {
        return emit_unary_expr(*unary);
    } else if (auto call = dynamic_cast<AST::CallExpr*>(&expr)) {
        return emit_call_expr(*call);
    } else if (auto assign = dynamic_cast<AST::AssignExpr*>(&expr)) {
        return emit_assign_expr(*assign);
    } else if (auto grouping = dynamic_cast<AST::GroupingExpr*>(&expr)) {
        return emit_grouping_expr(*grouping);
    } else if (auto ternary = dynamic_cast<AST::TernaryExpr*>(&expr)) {
        return emit_ternary_expr(*ternary);
    } else if (auto index = dynamic_cast<AST::IndexExpr*>(&expr)) {
        return emit_index_expr(*index);
    } else if (auto member = dynamic_cast<AST::MemberExpr*>(&expr)) {
        return emit_member_expr(*member);
    } else {
        report_error("Unknown expression type");
        return 0;
    }
}

// Expression handlers
Reg Generator::emit_literal_expr(AST::LiteralExpr& expr) {
    Reg dst = allocate_register();
    
    // Create ValuePtr based on literal value
    ValuePtr const_val;
    
    if (std::holds_alternative<std::string>(expr.value)) {
        std::string stringValue = std::get<std::string>(expr.value);
        
        // Try to determine if this string represents a number
        bool isNumeric = false;
        bool isFloat = false;
        
        if (!stringValue.empty()) {
            char first = stringValue[0];
            if (std::isdigit(first) || first == '+' || first == '-' || first == '.') {
                isNumeric = true;
                // Check if it's a float
                if (stringValue.find('.') != std::string::npos || 
                    stringValue.find('e') != std::string::npos || 
                    stringValue.find('E') != std::string::npos) {
                    isFloat = true;
                }
            }
        }
        
        if (isNumeric) {
            if (isFloat) {
                // Create float value
                auto float_type = std::make_shared<Type>(TypeTag::Float64);
                try {
                    double floatVal = std::stod(stringValue);
                    const_val = std::make_shared<Value>(float_type, floatVal);
                } catch (const std::exception&) {
                    // If parsing fails, treat as string
                    auto string_type = std::make_shared<Type>(TypeTag::String);
                    const_val = std::make_shared<Value>(string_type, stringValue);
                }
            } else {
                // Create integer value
                auto int_type = std::make_shared<Type>(TypeTag::Int);
                try {
                    int64_t intVal = std::stoll(stringValue);
                    const_val = std::make_shared<Value>(int_type, intVal);
                } catch (const std::exception&) {
                    // If parsing fails, treat as string
                    auto string_type = std::make_shared<Type>(TypeTag::String);
                    const_val = std::make_shared<Value>(string_type, stringValue);
                }
            }
        } else {
            // String value (already parsed, quotes removed by parser)
            auto string_type = std::make_shared<Type>(TypeTag::String);
            const_val = std::make_shared<Value>(string_type, stringValue);
        }
    } else if (std::holds_alternative<bool>(expr.value)) {
        // Create boolean value
        auto bool_type = std::make_shared<Type>(TypeTag::Bool);
        bool boolVal = std::get<bool>(expr.value);
        const_val = std::make_shared<Value>(bool_type, boolVal);
    } else if (std::holds_alternative<std::nullptr_t>(expr.value)) {
        // Create nil value
        auto nil_type = std::make_shared<Type>(TypeTag::Nil);
        const_val = std::make_shared<Value>(nil_type, "");
    } else {
        // Default to nil
        auto nil_type = std::make_shared<Type>(TypeTag::Nil);
        const_val = std::make_shared<Value>(nil_type, "");
    }
    
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, dst, const_val));
    return dst;
}

Reg Generator::emit_variable_expr(AST::VariableExpr& expr) {
    Reg reg = get_variable_register(expr.name);
    if (reg == UINT32_MAX) {
        report_error("Undefined variable: " + expr.name);
        return 0;
    }
    return reg;
}

Reg Generator::emit_binary_expr(AST::BinaryExpr& expr) {
    Reg left = emit_expr(*expr.left);
    Reg right = emit_expr(*expr.right);
    Reg dst = allocate_register();
    
    // Map operator to LIR operation
    LIR_Op op;
    if (expr.op == TokenType::PLUS) op = LIR_Op::Add;
    else if (expr.op == TokenType::MINUS) op = LIR_Op::Sub;
    else if (expr.op == TokenType::STAR) op = LIR_Op::Mul;
    else if (expr.op == TokenType::SLASH) op = LIR_Op::Div;
    else if (expr.op == TokenType::MODULUS) op = LIR_Op::Mod;
    else if (expr.op == TokenType::EQUAL_EQUAL) op = LIR_Op::CmpEQ;
    else if (expr.op == TokenType::BANG_EQUAL) op = LIR_Op::CmpNEQ;
    else if (expr.op == TokenType::LESS) op = LIR_Op::CmpLT;
    else if (expr.op == TokenType::LESS_EQUAL) op = LIR_Op::CmpLE;
    else if (expr.op == TokenType::GREATER) op = LIR_Op::CmpGT;
    else if (expr.op == TokenType::GREATER_EQUAL) op = LIR_Op::CmpGE;
    else if (expr.op == TokenType::AND) op = LIR_Op::And;
    else if (expr.op == TokenType::OR) op = LIR_Op::Or;
    else {
        report_error("Unknown binary operator");
        return 0;
    }
    
    emit_instruction(LIR_Inst(op, dst, left, right));
    return dst;
}

Reg Generator::emit_unary_expr(AST::UnaryExpr& expr) {
    Reg operand = emit_expr(*expr.right);
    Reg dst = allocate_register();
    
    if (expr.op == TokenType::MINUS) {
        emit_instruction(LIR_Inst(LIR_Op::Sub, dst, 0, operand));
    } else if (expr.op == TokenType::BANG) {
        emit_instruction(LIR_Inst(LIR_Op::CmpEQ, dst, operand, 0));
    } else {
        report_error("Unknown unary operator");
        return 0;
    }
    
    return dst;
}

Reg Generator::emit_call_expr(AST::CallExpr& expr) {
    // For now, just return 0 as a placeholder
    report_error("Function calls not yet implemented");
    return 0;
}

Reg Generator::emit_assign_expr(AST::AssignExpr& expr) {
    Reg value = emit_expr(*expr.value);
    
    // For simple variable assignment
    if (!expr.name.empty()) {
        set_variable_register(expr.name, value);
        return value;
    } else if (expr.object) {
        // For member or index assignment - not yet implemented
        report_error("Member/index assignment not yet implemented");
        return 0;
    } else {
        report_error("Invalid assignment target");
        return 0;
    }
}

Reg Generator::emit_grouping_expr(AST::GroupingExpr& expr) {
    return emit_expr(*expr.expression);
}

Reg Generator::emit_ternary_expr(AST::TernaryExpr& expr) {
    report_error("Ternary expressions not yet implemented");
    return 0;
}

Reg Generator::emit_index_expr(AST::IndexExpr& expr) {
    report_error("Index expressions not yet implemented");
    return 0;
}

Reg Generator::emit_member_expr(AST::MemberExpr& expr) {
    report_error("Member expressions not yet implemented");
    return 0;
}

// Statement handlers
void Generator::emit_expr_stmt(AST::ExprStatement& stmt) {
    emit_expr(*stmt.expression);
}

void Generator::emit_print_stmt(AST::PrintStatement& stmt) {
    // For now, just handle the first argument
    if (!stmt.arguments.empty()) {
        Reg value = emit_expr(*stmt.arguments[0]);
        // Emit print instruction
        emit_instruction(LIR_Inst(LIR_Op::Print, 0, value, 0));
    }
}

void Generator::emit_var_stmt(AST::VarDeclaration& stmt) {
    if (stmt.initializer) {
        Reg value = emit_expr(*stmt.initializer);
        set_variable_register(stmt.name, value);
    } else {
        // Initialize with nil
        Reg dst = allocate_register();
        auto nil_type = std::make_shared<Type>(TypeTag::Nil);
        ValuePtr nil_val = std::make_shared<Value>(nil_type, "");
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, dst, nil_val));
        set_variable_register(stmt.name, dst);
    }
}

void Generator::emit_block_stmt(AST::BlockStatement& stmt) {
    for (const auto& block_stmt : stmt.statements) {
        emit_stmt(*block_stmt);
    }
}

void Generator::emit_if_stmt(AST::IfStatement& stmt) {
    report_error("If statements not yet implemented");
}

void Generator::emit_while_stmt(AST::WhileStatement& stmt) {
    report_error("While statements not yet implemented");
}

void Generator::emit_for_stmt(AST::ForStatement& stmt) {
    report_error("For statements not yet implemented");
}

void Generator::emit_return_stmt(AST::ReturnStatement& stmt) {
    if (stmt.value) {
        Reg value = emit_expr(*stmt.value);
        emit_instruction(LIR_Inst(LIR_Op::Return, value));
    } else {
        emit_instruction(LIR_Inst(LIR_Op::Return));
    }
}

void Generator::emit_func_stmt(AST::FunctionDeclaration& stmt) {
    report_error("Nested function declarations not yet implemented");
}

void Generator::emit_import_stmt(AST::ImportStatement& stmt) {
    report_error("Import statements not yet implemented");
}

void Generator::emit_match_stmt(AST::MatchStatement& stmt) {
    report_error("Match statements not yet implemented");
}

void Generator::emit_contract_stmt(AST::ContractStatement& stmt) {
    report_error("Contract statements not yet implemented");
}

void Generator::emit_comptime_stmt(AST::ComptimeStatement& stmt) {
    report_error("Comptime statements not yet implemented");
}

void Generator::emit_parallel_stmt(AST::ParallelStatement& stmt) {
    report_error("Parallel statements not yet implemented");
}

void Generator::emit_concurrent_stmt(AST::ConcurrentStatement& stmt) {
    report_error("Concurrent statements not yet implemented");
}

void Generator::emit_task_stmt(AST::TaskStatement& stmt) {
    report_error("Task statements not yet implemented");
}

void Generator::emit_worker_stmt(AST::WorkerStatement& stmt) {
    report_error("Worker statements not yet implemented");
}

void Generator::emit_iter_stmt(AST::IterStatement& stmt) {
    report_error("Iter statements not yet implemented");
}

void Generator::emit_unsafe_stmt(AST::UnsafeStatement& stmt) {
    report_error("Unsafe statements not yet implemented");
}

} // namespace LIR

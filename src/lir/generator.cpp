#include "generator.hh"
#include "../backend/value.hh"
#include "../backend/types.hh"
#include <algorithm>

namespace LIR {

Generator::Generator()
    : next_register_(0) {}

std::unique_ptr<LIR_Function> Generator::generate_program(AST::Program& program) {
    // Create a main function
    current_function_ = std::make_unique<LIR_Function>("main", 0);
    next_register_ = 0;
    scope_stack_.clear();
    register_types_.clear();
    enter_scope();
    
    // Process all statements
    for (const auto& stmt : program.statements) {
        emit_stmt(*stmt);
    }
    
    // Add implicit return if none exists
    if (current_function_->instructions.empty() || 
        current_function_->instructions.back().op != LIR_Op::Return) {
        emit_instruction(LIR_Inst(LIR_Op::Return));
    }

    exit_scope();

    auto result = std::move(current_function_);
    current_function_ = nullptr;
    scope_stack_.clear();
    register_types_.clear();
    return result;
}

std::unique_ptr<LIR_Function> Generator::generate_function(AST::FunctionDeclaration& fn) {
    // Create function with parameters
    current_function_ = std::make_unique<LIR_Function>(fn.name, fn.params.size());
    next_register_ = fn.params.size();
    scope_stack_.clear();
    register_types_.clear();
    enter_scope();
    
    // Register parameters
    for (size_t i = 0; i < fn.params.size(); ++i) {
        bind_variable(fn.params[i].first, static_cast<Reg>(i));
        set_register_type(static_cast<Reg>(i), nullptr);
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

void Generator::enter_scope() {
    scope_stack_.push_back(Scope{});
}

void Generator::exit_scope() {
    if (!scope_stack_.empty()) {
        scope_stack_.pop_back();
    }
}

void Generator::bind_variable(const std::string& name, Reg reg) {
    if (scope_stack_.empty()) {
        enter_scope();
    }
    scope_stack_.back().vars[name] = reg;
}

void Generator::update_variable_binding(const std::string& name, Reg reg) {
    for (auto it = scope_stack_.rbegin(); it != scope_stack_.rend(); ++it) {
        auto found = it->vars.find(name);
        if (found != it->vars.end()) {
            found->second = reg;
            return;
        }
    }
    bind_variable(name, reg);
}

Reg Generator::resolve_variable(const std::string& name) {
    for (auto it = scope_stack_.rbegin(); it != scope_stack_.rend(); ++it) {
        auto found = it->vars.find(name);
        if (found != it->vars.end()) {
            return found->second;
        }
    }
    return UINT32_MAX;
}

void Generator::set_register_type(Reg reg, TypePtr type) {
    register_types_[reg] = type;
}

TypePtr Generator::get_register_type(Reg reg) const {
    auto it = register_types_.find(reg);
    if (it != register_types_.end()) {
        return it->second;
    }
    return nullptr;
}

void Generator::emit_instruction(const LIR_Inst& inst) {
    if (current_function_) {
        current_function_->instructions.push_back(inst);
        current_function_->register_count = std::max(current_function_->register_count, next_register_);
        if (inst.dst != UINT32_MAX) {
            auto type = get_register_type(inst.dst);
            if (type) {
                current_function_->set_register_type(inst.dst, type);
            }
        }
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
    } else if (auto interpolated = dynamic_cast<AST::InterpolatedStringExpr*>(&expr)) {
        return emit_interpolated_string_expr(*interpolated);
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
                    current_function_->instructions.back().const_val->type = string_type;
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
                    current_function_->instructions.back().const_val->type = string_type;
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
        const_val = std::make_shared<Value>(nil_type, std::string("nil"));
    } else {
        // Default to nil
        auto nil_type = std::make_shared<Type>(TypeTag::Nil);
        const_val = std::make_shared<Value>(nil_type, "");
    }
    
    // Set type BEFORE emitting so it's available during emit_instruction
    set_register_type(dst, const_val ? const_val->type : nullptr);
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, dst, const_val));
    return dst;
}

Reg Generator::emit_variable_expr(AST::VariableExpr& expr) {
    Reg reg = resolve_variable(expr.name);
    if (reg == UINT32_MAX) {
        report_error("Undefined variable: " + expr.name);
        return 0;
    }
    return reg;
}

Reg Generator::emit_interpolated_string_expr(AST::InterpolatedStringExpr& expr) {
    auto string_type = std::make_shared<Type>(TypeTag::String);

    if (expr.parts.empty()) {
        Reg result = allocate_register();
        ValuePtr result_val = std::make_shared<Value>(string_type, std::string(""));
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, result, result_val));
        set_register_type(result, string_type);
        return result;
    }

    Reg sb_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::SBCreate, sb_reg, 0, 0));

    for (const auto& part : expr.parts) {
        if (std::holds_alternative<std::string>(part)) {
            std::string literal = std::get<std::string>(part);
            ValuePtr literal_val = std::make_shared<Value>(string_type, literal);
            Reg literal_reg = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::LoadConst, literal_reg, literal_val));
            set_register_type(literal_reg, string_type);
            emit_instruction(LIR_Inst(LIR_Op::SBAppend, sb_reg, literal_reg, 0));

        } else if (std::holds_alternative<std::shared_ptr<AST::Expression>>(part)) {
            auto expr_part = std::get<std::shared_ptr<AST::Expression>>(part);
            Reg expr_reg = emit_expr(*expr_part);

            Reg str_reg = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::ToString, str_reg, expr_reg, 0));
            set_register_type(str_reg, string_type);
            emit_instruction(LIR_Inst(LIR_Op::SBAppend, sb_reg, str_reg, 0));
        }
    }

    Reg result_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::SBFinish, result_reg, sb_reg, 0));
    set_register_type(result_reg, string_type);
    return result_reg;
}

Reg Generator::emit_binary_expr(AST::BinaryExpr& expr) {
    // For string concatenation, handle at generation time
    if (expr.op == TokenType::PLUS) {
        // Check if this is string concatenation by examining operands
        bool left_is_string = false;
        bool right_is_string = false;
        std::string left_str, right_str;
        
        // Check left operand
        if (auto left_literal = dynamic_cast<AST::LiteralExpr*>(expr.left.get())) {
            if (std::holds_alternative<std::string>(left_literal->value)) {
                left_str = std::get<std::string>(left_literal->value);
                // Check if it's actually a non-numeric string
                bool is_numeric = false;
                if (!left_str.empty()) {
                    char first = left_str[0];
                    if (std::isdigit(first) || first == '+' || first == '-' || first == '.') {
                        is_numeric = true;
                        if (left_str.find('.') != std::string::npos || 
                            left_str.find('e') != std::string::npos || 
                            left_str.find('E') != std::string::npos) {
                            // Float - treat as numeric
                        } else {
                            // Integer - treat as numeric  
                        }
                    }
                }
                left_is_string = !is_numeric;
            }
        }
        
        // Check right operand
        if (auto right_literal = dynamic_cast<AST::LiteralExpr*>(expr.right.get())) {
            if (std::holds_alternative<std::string>(right_literal->value)) {
                right_str = std::get<std::string>(right_literal->value);
                // Check if it's actually a non-numeric string
                bool is_numeric = false;
                if (!right_str.empty()) {
                    char first = right_str[0];
                    if (std::isdigit(first) || first == '+' || first == '-' || first == '.') {
                        is_numeric = true;
                        if (right_str.find('.') != std::string::npos || 
                            right_str.find('e') != std::string::npos || 
                            right_str.find('E') != std::string::npos) {
                            // Float - treat as numeric
                        } else {
                            // Integer - treat as numeric  
                        }
                    }
                }
                right_is_string = !is_numeric;
            }
        }
        
        // If either operand is a non-numeric string, treat as concatenation
        if (left_is_string || right_is_string) {
            // For string literals, concatenate at generation time
            if (left_is_string && right_is_string) {
                // Both are string literals - concatenate now
                std::string result = left_str + right_str;
                Reg dst = allocate_register();
                auto string_type = std::make_shared<Type>(TypeTag::String);
                ValuePtr result_val = std::make_shared<Value>(string_type, result);
                emit_instruction(LIR_Inst(LIR_Op::LoadConst, dst, result_val));
                return dst;
            } else {
                // Mixed types - for now, treat as arithmetic
                // TODO: Better type analysis for mixed concatenation
                Reg left = emit_expr(*expr.left);
                Reg right = emit_expr(*expr.right);
                Reg dst = allocate_register();
                emit_instruction(LIR_Inst(LIR_Op::Add, dst, left, right));
                return dst;
            }
        }
    }
    
    // Handle as arithmetic operation
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
    else if (expr.op == TokenType::POWER) {
        // Power operation - for now, use multiplication (a * a for simple cases)
        // TODO: Implement proper power operation or call to math library
        emit_instruction(LIR_Inst(LIR_Op::Mul, dst, left, left));
        return dst;
    }
    else if (expr.op == TokenType::EQUAL_EQUAL) op = LIR_Op::CmpEQ;
    else if (expr.op == TokenType::BANG_EQUAL) op = LIR_Op::CmpNEQ;
    else if (expr.op == TokenType::LESS) op = LIR_Op::CmpLT;
    else if (expr.op == TokenType::LESS_EQUAL) op = LIR_Op::CmpLE;
    else if (expr.op == TokenType::GREATER) op = LIR_Op::CmpGT;
    else if (expr.op == TokenType::GREATER_EQUAL) op = LIR_Op::CmpGE;
    else if (expr.op == TokenType::AND) op = LIR_Op::And;
    else if (expr.op == TokenType::OR) op = LIR_Op::Or;
    else if (expr.op == TokenType::CARET) op = LIR_Op::Xor;
    else {
        report_error("Unknown binary operator");
        return 0;
    }
    
    // Infer result type based on operands and operation
    TypePtr result_type = nullptr;
    TypePtr left_type = get_register_type(left);
    TypePtr right_type = get_register_type(right);
    
    // For arithmetic operations, determine result type
    if (op == LIR_Op::Add || op == LIR_Op::Sub || op == LIR_Op::Mul || op == LIR_Op::Div || op == LIR_Op::Mod) {
        // If either operand is float, result is float
        if ((left_type && left_type->tag == TypeTag::Float64) || 
            (right_type && right_type->tag == TypeTag::Float64)) {
            result_type = std::make_shared<Type>(TypeTag::Float64);
        } else if ((left_type && left_type->tag == TypeTag::Float32) || 
                   (right_type && right_type->tag == TypeTag::Float32)) {
            result_type = std::make_shared<Type>(TypeTag::Float32);
        } else {
            // Default to int for integer operations
            result_type = std::make_shared<Type>(TypeTag::Int);
        }
    } else if (op == LIR_Op::CmpEQ || op == LIR_Op::CmpNEQ || op == LIR_Op::CmpLT || 
               op == LIR_Op::CmpLE || op == LIR_Op::CmpGT || op == LIR_Op::CmpGE) {
        // Comparison operations return bool
        result_type = std::make_shared<Type>(TypeTag::Bool);
    } else if (op == LIR_Op::And || op == LIR_Op::Or) {
        // Logical operations return bool
        result_type = std::make_shared<Type>(TypeTag::Bool);
    } else if (op == LIR_Op::Xor) {
        // Bitwise XOR returns int
        result_type = std::make_shared<Type>(TypeTag::Int);
    }
    
    // Set type BEFORE emitting so it's available during emit_instruction
    if (result_type) {
        set_register_type(dst, result_type);
    }
    
    emit_instruction(LIR_Inst(op, dst, left, right));
    
    return dst;
}

Reg Generator::emit_unary_expr(AST::UnaryExpr& expr) {
    Reg operand = emit_expr(*expr.right);
    Reg dst = allocate_register();
    TypePtr operand_type = get_register_type(operand);
    TypePtr result_type = nullptr;
    
    if (expr.op == TokenType::MINUS) {
        // Result type is same as operand type
        result_type = operand_type;
        set_register_type(dst, result_type);
        // Use Neg operation for unary minus (more efficient than Sub from 0)
        emit_instruction(LIR_Inst(LIR_Op::Neg, dst, operand, 0));
    } else if (expr.op == TokenType::PLUS) {
        // Result type is same as operand type
        result_type = operand_type;
        set_register_type(dst, result_type);
        // Unary plus - just copy the value (no operation needed)
        emit_instruction(LIR_Inst(LIR_Op::Mov, dst, operand, 0));
    } else if (expr.op == TokenType::BANG) {
        // Result type is bool
        result_type = std::make_shared<Type>(TypeTag::Bool);
        set_register_type(dst, result_type);
        // Logical NOT - compare with true and negate (operand != true gives us !operand)
        Reg true_reg = allocate_register();
        auto bool_type = std::make_shared<Type>(TypeTag::Bool);
        ValuePtr true_val = std::make_shared<Value>(bool_type, true);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, true_reg, true_val));
        set_register_type(true_reg, bool_type);
        emit_instruction(LIR_Inst(LIR_Op::CmpNEQ, dst, operand, true_reg));
    } else if (expr.op == TokenType::TILDE) {
        // Result type is int
        auto int_type = std::make_shared<Type>(TypeTag::Int);
        result_type = int_type;
        set_register_type(dst, result_type);
        // Bitwise NOT - XOR with all bits set (for 64-bit: -1)
        Reg all_bits = allocate_register();
        ValuePtr neg_one_val = std::make_shared<Value>(int_type, static_cast<int64_t>(-1));
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, all_bits, neg_one_val));
        set_register_type(all_bits, int_type);
        emit_instruction(LIR_Inst(LIR_Op::Xor, dst, operand, all_bits));
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
        Reg dst = allocate_register();
        emit_instruction(LIR_Inst(LIR_Op::Mov, dst, value, 0));
        set_register_type(dst, get_register_type(value));
        update_variable_binding(expr.name, dst);
        return dst;
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
        
        // First, check the register type that we tracked
        TypePtr reg_type = get_register_type(value);
        if (reg_type) {
            switch (reg_type->tag) {
                case TypeTag::Int:
                case TypeTag::Int8:
                case TypeTag::Int16:
                case TypeTag::Int32:
                case TypeTag::Int64:
                case TypeTag::UInt:
                case TypeTag::UInt8:
                case TypeTag::UInt16:
                case TypeTag::UInt32:
                case TypeTag::UInt64:
                    emit_instruction(LIR_Inst(LIR_Op::PrintInt, 0, value, 0));
                    return;
                case TypeTag::Float32:
                case TypeTag::Float64:
                    emit_instruction(LIR_Inst(LIR_Op::PrintFloat, 0, value, 0));
                    return;
                case TypeTag::Bool:
                    emit_instruction(LIR_Inst(LIR_Op::PrintBool, 0, value, 0));
                    return;
                case TypeTag::String:
                    emit_instruction(LIR_Inst(LIR_Op::PrintString, 0, value, 0));
                    return;
                default:
                    break;
            }
        }
        
        // Fallback: Check what type of value we actually have in the register
        // Look at the last instruction to determine the type
        if (!current_function_->instructions.empty()) {
            const auto& last_inst = current_function_->instructions.back();
            if (last_inst.dst == value) {
                if (last_inst.const_val) {
                    // This is a LoadConst instruction - check the constant's type
                    if (last_inst.const_val->type) {
                        switch (last_inst.const_val->type->tag) {
                            case TypeTag::Int:
                            case TypeTag::Int8:
                            case TypeTag::Int16:
                            case TypeTag::Int32:
                            case TypeTag::Int64:
                                emit_instruction(LIR_Inst(LIR_Op::PrintInt, 0, value, 0));
                                return;
                            case TypeTag::Float32:
                            case TypeTag::Float64:
                                emit_instruction(LIR_Inst(LIR_Op::PrintFloat, 0, value, 0));
                                return;
                            case TypeTag::Bool:
                                emit_instruction(LIR_Inst(LIR_Op::PrintBool, 0, value, 0));
                                return;
                            case TypeTag::String:
                                emit_instruction(LIR_Inst(LIR_Op::PrintString, 0, value, 0));
                                return;
                            case TypeTag::Nil:
                            default:
                                // For nil and other types, convert to string and print
                                auto string_type = std::make_shared<Type>(TypeTag::String);
                                ValuePtr nil_str = std::make_shared<Value>(string_type, std::string("nil"));
                                Reg nil_reg = allocate_register();
                                emit_instruction(LIR_Inst(LIR_Op::LoadConst, nil_reg, nil_str));
                                emit_instruction(LIR_Inst(LIR_Op::PrintString, 0, nil_reg, 0));
                                return;
                        }
                    }
                } else if (last_inst.op == LIR_Op::Concat || last_inst.op == LIR_Op::ToString) {
                    // This is a string operation - treat as string
                    emit_instruction(LIR_Inst(LIR_Op::PrintString, 0, value, 0));
                    return;
                }
            }
        }
        
        // Fallback: check if it's a literal primitive to determine print type
        if (auto literal = dynamic_cast<AST::LiteralExpr*>(stmt.arguments[0].get())) {
            if (std::holds_alternative<std::string>(literal->value)) {
                std::string str_val = std::get<std::string>(literal->value);
                // Check if it's a numeric string
                if (!str_val.empty() && (std::isdigit(str_val[0]) || str_val[0] == '+' || str_val[0] == '-' || str_val[0] == '.')) {
                    if (str_val.find('.') != std::string::npos || str_val.find('e') != std::string::npos || str_val.find('E') != std::string::npos) {
                        emit_instruction(LIR_Inst(LIR_Op::PrintFloat, 0, value, 0));
                    } else {
                        emit_instruction(LIR_Inst(LIR_Op::PrintInt, 0, value, 0));
                    }
                } else {
                    // String literal - print directly
                    emit_instruction(LIR_Inst(LIR_Op::PrintString, 0, value, 0));
                }
            } else if (std::holds_alternative<bool>(literal->value)) {
                emit_instruction(LIR_Inst(LIR_Op::PrintBool, 0, value, 0));
            } else {
                // nil - convert to string constant and print
                auto string_type = std::make_shared<Type>(TypeTag::String);
                ValuePtr nil_str = std::make_shared<Value>(string_type, std::string("nil"));
                Reg nil_reg = allocate_register();
                emit_instruction(LIR_Inst(LIR_Op::LoadConst, nil_reg, nil_str));
                emit_instruction(LIR_Inst(LIR_Op::PrintString, 0, nil_reg, 0));
            }
        } else if (auto interpolated = dynamic_cast<AST::InterpolatedStringExpr*>(stmt.arguments[0].get())) {
            // This is an interpolated string - treat as string
            emit_instruction(LIR_Inst(LIR_Op::PrintString, 0, value, 0));
        } else {
            // For expressions, determine type at generation time and emit appropriate print
            // For now, default to PrintInt for arithmetic expressions
            // TODO: Better type inference for expressions
            emit_instruction(LIR_Inst(LIR_Op::PrintInt, 0, value, 0));
        }
    }
}

void Generator::emit_var_stmt(AST::VarDeclaration& stmt) {
    Reg value_reg;
    if (stmt.initializer) {
        Reg value = emit_expr(*stmt.initializer);
        value_reg = allocate_register();
        emit_instruction(LIR_Inst(LIR_Op::Mov, value_reg, value, 0));
        set_register_type(value_reg, get_register_type(value));
    } else {
        // Initialize with nil
        value_reg = allocate_register();
        auto nil_type = std::make_shared<Type>(TypeTag::Nil);
        ValuePtr nil_val = std::make_shared<Value>(nil_type, "");
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, value_reg, nil_val));
        set_register_type(value_reg, nil_type);
    }
    bind_variable(stmt.name, value_reg);
}

void Generator::emit_block_stmt(AST::BlockStatement& stmt) {
    enter_scope();
    for (const auto& block_stmt : stmt.statements) {
        emit_stmt(*block_stmt);
    }
    exit_scope();
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

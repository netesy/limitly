#include "generator.hh"
#include "../backend/value.hh"
#include "../backend/types.hh"
#include <algorithm>
#include <unordered_set>

namespace LIR {

Generator::Generator()
    : next_register_(0), next_label_(0), current_memory_region_(nullptr) {
    // Initialize memory manager with audit mode disabled for performance
    memory_manager_.setAuditMode(false);
}

std::unique_ptr<LIR_Function> Generator::generate_program(AST::Program& program) {
    // Create a main function
    current_function_ = std::make_unique<LIR_Function>("main", 0);
    next_register_ = 0;
    next_label_ = 0;
    scope_stack_.clear();
    loop_stack_.clear();
    register_types_.clear();
    enter_scope();
    enter_memory_region();
    
    // Start CFG building
    start_cfg_build();
    
    // Process all statements
    for (const auto& stmt : program.statements) {
        emit_stmt(*stmt);
    }
    
    // Add implicit return if none exists
    if (get_current_block() && !get_current_block()->has_terminator()) {
        emit_instruction(LIR_Inst(LIR_Op::Return));
    }

    // Finish CFG building
    finish_cfg_build();

    exit_scope();
    exit_memory_region();

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
    next_label_ = 0;
    scope_stack_.clear();
    loop_stack_.clear();
    register_types_.clear();
    enter_scope();
    enter_memory_region();
    
    // Start CFG building
    start_cfg_build();
    
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
    if (get_current_block() && !get_current_block()->has_terminator()) {
        emit_instruction(LIR_Inst(LIR_Op::Return));
    }
    
    // Finish CFG building
    finish_cfg_build();

    exit_scope();
    exit_memory_region();
    
    auto result = std::move(current_function_);
    current_function_ = nullptr;
    return result;
}

// Helper methods
Reg Generator::allocate_register() {
    return next_register_++;
}

void Generator::enter_scope() {
    scope_stack_.push_back({});
    // Create memory region for this scope
    scope_stack_.back().memory_region = new MemoryManager<>::Region(memory_manager_);
}

void Generator::exit_scope() {
    if (!scope_stack_.empty()) {
        // Clean up memory region for this scope
        if (scope_stack_.back().memory_region) {
            delete scope_stack_.back().memory_region;
        }
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
        // If CFG building is active, emit to current CFG block
        if (cfg_context_.building_cfg && cfg_context_.current_block) {
            // Don't emit instructions to a terminated block
            if (cfg_context_.current_block->terminated) {
                return;
            }
            cfg_context_.current_block->add_instruction(inst);
        } else {
            // Fallback: emit to linear instruction stream for non-CFG mode
            current_function_->instructions.push_back(inst);
        }
        
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
    } else if (auto iter_stmt = dynamic_cast<AST::IterStatement*>(&stmt)) {
        emit_iter_stmt(*iter_stmt);
    } else if (auto break_stmt = dynamic_cast<AST::BreakStatement*>(&stmt)) {
        emit_break_stmt(*break_stmt);
    } else if (auto continue_stmt = dynamic_cast<AST::ContinueStatement*>(&stmt)) {
        emit_continue_stmt(*continue_stmt);
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
    } else if (auto list = dynamic_cast<AST::ListExpr*>(&expr)) {
        return emit_list_expr(*list);
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
        // Get the existing register for this variable
        Reg dst = resolve_variable(expr.name);
        if (dst == UINT32_MAX) {
            // Variable doesn't exist, allocate a new one
            dst = allocate_register();
            bind_variable(expr.name, dst);
        }
        // Set type BEFORE emitting so it's available during emit_instruction
        set_register_type(dst, get_register_type(value));
        emit_instruction(LIR_Inst(LIR_Op::Mov, dst, value, 0));
        // No need to update binding since we're using the existing register
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

Reg Generator::emit_list_expr(AST::ListExpr& expr) {
    // For now, create a simple list representation
    // TODO: Implement proper list creation with ListCreate operations
    Reg list_reg = allocate_register();
    
    // Create a nil/empty list for now
    auto nil_type = std::make_shared<Type>(TypeTag::Nil);
    ValuePtr nil_val = std::make_shared<Value>(nil_type, std::string(""));
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, list_reg, nil_val));
    set_register_type(list_reg, nil_type);
    
    return list_reg;
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
    // Create CFG blocks for the if statement
    LIR_BasicBlock* then_block = create_basic_block("if_then");
    LIR_BasicBlock* else_block = stmt.elseBranch ? create_basic_block("if_else") : nullptr;
    LIR_BasicBlock* end_block = create_basic_block("if_end");
    
    // Emit condition check in current block
    Reg condition = emit_expr(*stmt.condition);
    Reg condition_bool = allocate_register();
    
    // For boolean conditions, use them directly
    TypePtr condition_type = get_register_type(condition);
    if (condition_type && condition_type->tag == TypeTag::Bool) {
        condition_bool = condition;
    } else {
        // Convert non-boolean condition to boolean
        Reg zero_reg = allocate_register();
        auto int_type = std::make_shared<Type>(TypeTag::Int);
        ValuePtr zero_val = std::make_shared<Value>(int_type, (int64_t)0);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, zero_reg, zero_val));
        set_register_type(zero_reg, int_type);
        emit_instruction(LIR_Inst(LIR_Op::CmpNEQ, condition_bool, condition, zero_reg));
        set_register_type(condition_bool, std::make_shared<Type>(TypeTag::Bool));
    }
    
    // Conditional jump: if false, go to else (or end if no else)
    uint32_t false_target = else_block ? else_block->id : end_block->id;
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, condition_bool, 0, false_target));
    
    // Jump to then branch
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, then_block->id));
    
    // Set up edges from current block
    add_block_edge(get_current_block(), then_block);
    if (else_block) {
        add_block_edge(get_current_block(), else_block);
    } else {
        add_block_edge(get_current_block(), end_block);
    }
    
    // === Then Block ===
    set_current_block(then_block);
    
    // Emit then branch
    if (stmt.thenBranch) {
        emit_stmt(*stmt.thenBranch);
    }
    
    // Jump to end after then branch (only if no terminator already exists)
    if (get_current_block() && !get_current_block()->has_terminator()) {
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, end_block->id));
        add_block_edge(then_block, end_block);
    }
    
    // === Else Block (if present) ===
    if (else_block) {
        set_current_block(else_block);
        
        // Emit else branch
        emit_stmt(*stmt.elseBranch);
        
        // Jump to end after else branch (only if no terminator already exists)
        if (get_current_block() && !get_current_block()->has_terminator()) {
            emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, end_block->id));
            add_block_edge(else_block, end_block);
        }
    }
    
    // === End Block: continuation ===
    set_current_block(end_block);
}

void Generator::emit_while_stmt(AST::WhileStatement& stmt) {
    // Create CFG blocks for the while loop
    LIR_BasicBlock* header_block = create_basic_block("while_header");
    LIR_BasicBlock* body_block = create_basic_block("while_body");
    LIR_BasicBlock* exit_block = create_basic_block("while_exit");
    
    // Enter loop context for break/continue
    enter_loop();
    set_loop_labels(header_block->id, exit_block->id, header_block->id);
    
    // Jump from current block to header
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(get_current_block(), header_block);
    
    // === Header Block: condition check ===
    set_current_block(header_block);
    
    // Emit condition
    Reg condition = emit_expr(*stmt.condition);
    Reg condition_bool = allocate_register();
    
    // For boolean conditions, use them directly
    TypePtr condition_type = get_register_type(condition);
    if (condition_type && condition_type->tag == TypeTag::Bool) {
        condition_bool = condition;
    } else {
        // Convert non-boolean condition to boolean
        Reg zero_reg = allocate_register();
        auto int_type = std::make_shared<Type>(TypeTag::Int);
        ValuePtr zero_val = std::make_shared<Value>(int_type, (int64_t)0);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, zero_reg, zero_val));
        set_register_type(zero_reg, int_type);
        emit_instruction(LIR_Inst(LIR_Op::CmpNEQ, condition_bool, condition, zero_reg));
        set_register_type(condition_bool, std::make_shared<Type>(TypeTag::Bool));
    }
    
    // Conditional jump: if false, go to exit; if true, go to body
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, condition_bool, 0, exit_block->id));
    add_block_edge(header_block, exit_block);
    add_block_edge(header_block, body_block);
    
    // === Body Block: loop body ===
    set_current_block(body_block);
    
    // Emit loop body
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Jump back to header
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(body_block, header_block);
    
    // === Exit Block: continuation ===
    set_current_block(exit_block);
    
    // Exit loop context
    exit_loop();
}

void Generator::emit_for_stmt(AST::ForStatement& stmt) {
    if (stmt.isIterableLoop) {
        // Handle iterable loops: for (var in collection)
        emit_iterable_for_loop(stmt);
    } else {
        // Handle traditional C-style for loops: for (init; condition; increment)
        emit_traditional_for_loop(stmt);
    }
}

void Generator::emit_traditional_for_loop(AST::ForStatement& stmt) {
    // Create CFG blocks for the for loop
    LIR_BasicBlock* header_block = create_basic_block("for_header");
    LIR_BasicBlock* body_block = create_basic_block("for_body");
    LIR_BasicBlock* increment_block = create_basic_block("for_increment");
    LIR_BasicBlock* exit_block = create_basic_block("for_exit");
    
    // Enter loop context for break/continue
    enter_loop();
    set_loop_labels(header_block->id, exit_block->id, increment_block->id);
    
    // Emit initialization in current block
    if (stmt.initializer) {
        emit_stmt(*stmt.initializer);
    }
    
    // Jump from current block to header
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(get_current_block(), header_block);
    
    // === Header Block: condition check ===
    set_current_block(header_block);
    
    if (stmt.condition) {
        // Emit condition
        Reg condition = emit_expr(*stmt.condition);
        Reg condition_bool = allocate_register();
        
        // For boolean conditions, use them directly
        TypePtr condition_type = get_register_type(condition);
        if (condition_type && condition_type->tag == TypeTag::Bool) {
            condition_bool = condition;
        } else {
            // Convert non-boolean condition to boolean
            Reg zero_reg = allocate_register();
            auto int_type = std::make_shared<Type>(TypeTag::Int);
            ValuePtr zero_val = std::make_shared<Value>(int_type, (int64_t)0);
            emit_instruction(LIR_Inst(LIR_Op::LoadConst, zero_reg, zero_val));
            set_register_type(zero_reg, int_type);
            emit_instruction(LIR_Inst(LIR_Op::CmpNEQ, condition_bool, condition, zero_reg));
            set_register_type(condition_bool, std::make_shared<Type>(TypeTag::Bool));
        }
        
        // Conditional jump: if false, go to exit; if true, go to body
        emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, condition_bool, 0, exit_block->id));
        add_block_edge(header_block, exit_block);
    } else {
        // No condition - always jump to body
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, body_block->id));
    }
    add_block_edge(header_block, body_block);
    
    // === Body Block: loop body ===
    set_current_block(body_block);
    
    // Emit loop body
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Jump to increment block
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, increment_block->id));
    add_block_edge(body_block, increment_block);
    
    // === Increment Block: increment expression ===
    set_current_block(increment_block);
    
    // Emit increment if present
    if (stmt.increment) {
        emit_expr(*stmt.increment); // Evaluate increment expression
    }
    
    // Jump back to header
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(increment_block, header_block);
    
    // === Exit Block: continuation ===
    set_current_block(exit_block);
    
    // Exit loop context
    exit_loop();
}

void Generator::emit_iterable_for_loop(AST::ForStatement& stmt) {
    // Generate labels for the loop
    uint32_t loop_check_label = generate_label();
    uint32_t loop_body_label = generate_label();
    uint32_t loop_end_label = generate_label();
    
    // Enter loop context
    enter_loop();
    set_loop_labels(loop_check_label, loop_end_label, loop_check_label);
    
    // Create a new scope for the loop variables
    enter_scope();
    
    // Initialize index to 0
    auto int_type = std::make_shared<Type>(TypeTag::Int);
    ValuePtr zero_val = std::make_shared<Value>(int_type, (int64_t)0);
    Reg index_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, index_reg, zero_val));
    set_register_type(index_reg, int_type);
    
    // Load collection
    Reg collection_reg = emit_expr(*stmt.iterable);
    
    // Jump to loop condition check first
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, loop_check_label));
    
    // Emit loop body - get item at index (using ListIndex)
    Reg item_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::ListIndex, item_reg, collection_reg, index_reg));
    
    // Store the item in the loop variable(s)
    for (const auto& var_name : stmt.loopVars) {
        bind_variable(var_name, item_reg);
    }
    
    // Emit loop body statements
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Increment index
    ValuePtr one_val = std::make_shared<Value>(int_type, (int64_t)1);
    Reg one_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, one_reg, one_val));
    set_register_type(one_reg, int_type);
    
    Reg new_index_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::Add, new_index_reg, index_reg, one_reg));
    set_register_type(new_index_reg, int_type);
    
    // Update index register
    emit_instruction(LIR_Inst(LIR_Op::Mov, index_reg, new_index_reg, 0));
    
    // Jump back to loop condition check
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, loop_check_label));
    
    // Emit loop condition check
    
    // For now, use a simple condition - assume we iterate 3 times (placeholder)
    // TODO: Implement proper Length operation when available
    Reg condition_reg = allocate_register();
    ValuePtr three_val = std::make_shared<Value>(int_type, (int64_t)3); // placeholder
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, condition_reg, three_val));
    set_register_type(condition_reg, int_type);
    
    Reg cmp_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::CmpLT, cmp_reg, index_reg, condition_reg));
    set_register_type(cmp_reg, std::make_shared<Type>(TypeTag::Bool));
    
    // Jump to loop body if condition is true, otherwise fall through to end
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp_reg, 0, loop_end_label));
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, loop_body_label));
    
    // Exit scope and loop context
    exit_scope();
    exit_loop();
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
    // Generate labels for the loop
    uint32_t start_label = generate_label();
    uint32_t end_label = generate_label();
    uint32_t continue_label = generate_label();
    
    // Enter loop context
    enter_loop();
    set_loop_labels(start_label, end_label, continue_label);
    
    // Create a new scope for the loop variables
    enter_scope();
    
    // For now, implement a basic version that assumes the iterable is a range
    // TODO: Implement proper iterator protocol
    
    // Get the iterable expression
    Reg iterable_reg = emit_expr(*stmt.iterable);
    
    // Initialize loop variables (simplified - assumes range-like behavior)
    for (const auto& var_name : stmt.loopVars) {
        Reg var_reg = allocate_register();
        bind_variable(var_name, var_reg);
        
        // Initialize with zero for now (proper implementation would get from iterator)
        auto int_type = std::make_shared<Type>(TypeTag::Int);
        ValuePtr zero_val = std::make_shared<Value>(int_type, (int64_t)0);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, var_reg, zero_val));
        set_register_type(var_reg, int_type);
    }
    
    // Emit condition check (simplified - assumes fixed iteration count)
    // TODO: Proper iterator protocol with hasNext() check
    Reg condition = allocate_register();
    auto int_type = std::make_shared<Type>(TypeTag::Int);
    ValuePtr condition_val = std::make_shared<Value>(int_type, (int64_t)1); // Always true for now
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, condition, condition_val));
    set_register_type(condition, int_type);
    
    Reg condition_bool = allocate_register();
    Reg zero_reg = allocate_register();
    ValuePtr zero_val = std::make_shared<Value>(int_type, (int64_t)0);
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, zero_reg, zero_val));
    set_register_type(zero_reg, int_type);
    emit_instruction(LIR_Inst(LIR_Op::CmpNEQ, condition_bool, condition, zero_reg)); // condition != 0
    
    // Jump to end if condition is false
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, condition_bool, 0, end_label));
    
    // Emit loop body
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Emit continue point
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, continue_label));
    
    // Increment loop variables (simplified)
    for (const auto& var_name : stmt.loopVars) {
        Reg var_reg = resolve_variable(var_name);
        Reg one_reg = allocate_register();
        ValuePtr one_val = std::make_shared<Value>(int_type, (int64_t)1);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, one_reg, one_val));
        emit_instruction(LIR_Inst(LIR_Op::Add, var_reg, var_reg, one_reg));
    }
    
    // Jump back to start
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, start_label));
    
    // Exit loop scope (cleans up memory)
    exit_scope();
    
    // Exit loop context
    exit_loop();
}

void Generator::emit_break_stmt(AST::BreakStatement& stmt) {
    uint32_t break_label = get_break_label();
    if (break_label != 0) {
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, break_label));
        // Add edge to break target block
        LIR_BasicBlock* break_target = current_function_->cfg->get_block(break_label);
        if (break_target) {
            add_block_edge(get_current_block(), break_target);
        }
        // Mark current block as terminated to prevent further instruction generation
        if (get_current_block()) {
            get_current_block()->terminated = true;
        }
    }
}

void Generator::emit_continue_stmt(AST::ContinueStatement& stmt) {
    uint32_t continue_label = get_continue_label();
    if (continue_label != 0) {
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, continue_label));
        // Add edge to continue target block
        LIR_BasicBlock* continue_target = current_function_->cfg->get_block(continue_label);
        if (continue_target) {
            add_block_edge(get_current_block(), continue_target);
        }
        // Mark current block as terminated to prevent further instruction generation
        if (get_current_block()) {
            get_current_block()->terminated = true;
        }
    }
}

void Generator::emit_unsafe_stmt(AST::UnsafeStatement& stmt) {
    report_error("Unsafe statements not yet implemented");
}

// Memory management methods
void Generator::enter_memory_region() {
    if (!current_memory_region_) {
        current_memory_region_ = new MemoryManager<>::Region(memory_manager_);
    }
}

void Generator::exit_memory_region() {
    if (current_memory_region_) {
        delete current_memory_region_;
        current_memory_region_ = nullptr;
    }
}

void* Generator::allocate_in_region(size_t size, size_t alignment) {
    if (scope_stack_.empty()) {
        enter_scope();
    }
    auto& current_scope = scope_stack_.back();
    if (!current_scope.memory_region) {
        current_scope.memory_region = new MemoryManager<>::Region(memory_manager_);
    }
    return memory_manager_.allocate(size, alignment);
}

template<typename T, typename... Args>
T* Generator::create_object(Args&&... args) {
    if (scope_stack_.empty()) {
        enter_scope();
    }
    auto& current_scope = scope_stack_.back();
    if (!current_scope.memory_region) {
        current_scope.memory_region = new MemoryManager<>::Region(memory_manager_);
    }
    return current_scope.memory_region->create<T>(std::forward<Args>(args)...);
}

void Generator::cleanup_memory() {
    exit_memory_region();
    memory_manager_.analyzeMemoryUsage();
}

// Loop management methods
uint32_t Generator::generate_label() {
    return next_label_++;
}

void Generator::enter_loop() {
    loop_stack_.push_back({0, 0, 0}); // Placeholder, will be set by set_loop_labels
}

void Generator::exit_loop() {
    if (!loop_stack_.empty()) {
        loop_stack_.pop_back();
    }
}

void Generator::set_loop_labels(uint32_t start_label, uint32_t end_label, uint32_t continue_label) {
    if (!loop_stack_.empty()) {
        loop_stack_.back().start_label = start_label;
        loop_stack_.back().end_label = end_label;
        loop_stack_.back().continue_label = continue_label;
    }
}

uint32_t Generator::get_break_label() {
    if (loop_stack_.empty()) {
        report_error("break statement not in loop");
        return 0;
    }
    return loop_stack_.back().end_label;
}

uint32_t Generator::get_continue_label() {
    if (loop_stack_.empty()) {
        report_error("continue statement not in loop");
        return 0;
    }
    return loop_stack_.back().continue_label;
}

bool Generator::in_loop() const {
    return !loop_stack_.empty();
}

// CFG building methods
void Generator::start_cfg_build() {
    cfg_context_.building_cfg = true;
    cfg_context_.entry_block = create_basic_block("entry");
    cfg_context_.exit_block = create_basic_block("exit");
    set_current_block(cfg_context_.entry_block);
    
    // Set entry and exit in CFG
    current_function_->cfg->entry_block_id = cfg_context_.entry_block->id;
    current_function_->cfg->exit_block_id = cfg_context_.exit_block->id;
    
    cfg_context_.entry_block->is_entry = true;
    cfg_context_.exit_block->is_exit = true;
}

void Generator::finish_cfg_build() {
    cfg_context_.building_cfg = false;
    
    // If current block doesn't have terminator, add jump to exit
    if (cfg_context_.current_block && !cfg_context_.current_block->has_terminator()) {
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, cfg_context_.exit_block->id));
        add_block_edge(cfg_context_.current_block, cfg_context_.exit_block);
    }
    
    // Remove unreachable blocks before flattening
    remove_unreachable_blocks();
    
    // Flatten CFG blocks into linear instruction stream for JIT consumption
    flatten_cfg_to_instructions();
    
    cfg_context_.current_block = nullptr;
    cfg_context_.entry_block = nullptr;
    cfg_context_.exit_block = nullptr;
}

void Generator::remove_unreachable_blocks() {
    if (!current_function_ || !current_function_->cfg) {
        return;
    }
    
    // Perform reachability analysis from entry block
    std::unordered_set<uint32_t> reachable_blocks;
    std::vector<uint32_t> worklist;
    
    // Start from entry block
    if (current_function_->cfg->entry_block_id != UINT32_MAX) {
        worklist.push_back(current_function_->cfg->entry_block_id);
        reachable_blocks.insert(current_function_->cfg->entry_block_id);
    }
    
    // DFS to find all reachable blocks
    while (!worklist.empty()) {
        uint32_t current_id = worklist.back();
        worklist.pop_back();
        
        auto current_block = current_function_->cfg->get_block(current_id);
        if (!current_block) continue;
        
        // Add all successor blocks to worklist
        for (uint32_t successor_id : current_block->successors) {
            if (reachable_blocks.find(successor_id) == reachable_blocks.end()) {
                reachable_blocks.insert(successor_id);
                worklist.push_back(successor_id);
            }
        }
    }
    
    // Remove unreachable blocks
    auto& blocks = current_function_->cfg->blocks;
    for (auto it = blocks.begin(); it != blocks.end(); ) {
        if (*it && reachable_blocks.find((*it)->id) == reachable_blocks.end()) {
            // This block is unreachable, remove it
            it = blocks.erase(it);
        } else {
            ++it;
        }
    }
}

void Generator::flatten_cfg_to_instructions() {
    if (!current_function_ || !current_function_->cfg) {
        return;
    }
    
    // Clear existing linear instructions
    current_function_->instructions.clear();
    
    // Create a map from block ID to instruction position (label)
    std::unordered_map<uint32_t, size_t> block_positions;
    
    // First pass: calculate positions for each block
    size_t current_pos = 0;
    for (const auto& block : current_function_->cfg->blocks) {
        if (block) {
            block_positions[block->id] = current_pos;
            current_pos += block->instructions.size();
        }
    }
    
    // Second pass: emit instructions with proper label targets
    for (const auto& block : current_function_->cfg->blocks) {
        if (!block) continue;
        
        // Emit all instructions in this block
        for (const auto& inst : block->instructions) {
            LIR_Inst modified_inst = inst;
            
            // Update jump targets to use instruction positions as labels
            if (inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIfFalse) {
                auto it = block_positions.find(inst.imm);
                if (it != block_positions.end()) {
                    modified_inst.imm = it->second; // Use instruction position as label
                }
            }
            
            current_function_->instructions.push_back(modified_inst);
        }
    }
}

LIR_BasicBlock* Generator::create_basic_block(const std::string& label) {
    if (!cfg_context_.building_cfg) {
        report_error("Cannot create basic block outside of CFG build");
        return nullptr;
    }
    
    LIR_BasicBlock* block = current_function_->cfg->create_block(label);
    return block;
}

void Generator::set_current_block(LIR_BasicBlock* block) {
    cfg_context_.current_block = block;
}

void Generator::add_block_edge(LIR_BasicBlock* from, LIR_BasicBlock* to) {
    if (from && to) {
        current_function_->cfg->add_edge(from->id, to->id);
    }
}

LIR_BasicBlock* Generator::get_current_block() const {
    return cfg_context_.current_block;
}

} // namespace LIR

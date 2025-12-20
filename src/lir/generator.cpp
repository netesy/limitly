#include "generator.hh"
#include "functions.hh"
#include "builtin_functions.hh"
#include "../frontend/ast.hh"
#include <algorithm>
#include <map>
#include <limits>

namespace LIR {

Generator::Generator() : current_function_(nullptr), next_register_(0), next_label_(0) {
    // Initialize LIR function system
    FunctionUtils::initializeFunctions();
}

std::unique_ptr<LIR_Function> Generator::generate_program(AST::Program& program) {
    // PASS 0: Collect function, class, and module signatures only
    collect_function_signatures(program);
    collect_class_signatures(program);
    collect_module_signatures(program);
    
    // PASS 1: Lower function bodies into separate LIR functions
    lower_function_bodies(program);
    
    // PASS 2: Generate main function with top-level code only
    current_function_ = std::make_unique<LIR_Function>("main", 0);
    next_register_ = 0;
    next_label_ = 0;
    scope_stack_.clear();
    loop_stack_.clear();
    register_types_.clear();
    enter_scope();
    enter_memory_region();
    
    // Use linear mode for main/top-level code (not CFG)
    cfg_context_.building_cfg = false;
    cfg_context_.current_block = nullptr;
    
    // But create minimal CFG for JIT compatibility
    start_cfg_build();
    
    // Generate top-level statements (excluding function definitions)
    for (const auto& stmt : program.statements) {
        if (auto func_stmt = dynamic_cast<AST::FunctionDeclaration*>(stmt.get())) {
            // Skip function definitions - they're already lowered
            continue;
        }
        emit_stmt(*stmt);
    }
    
    // Add implicit return if none exists
    if (cfg_context_.building_cfg && get_current_block() && !get_current_block()->has_terminator()) {
        emit_instruction(LIR_Inst(LIR_Op::Return));
    }

    // Finish CFG building for main (only if CFG was used)
    if (cfg_context_.building_cfg) {
        finish_cfg_build();
    }

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

void Generator::set_register_value(Reg reg, ValuePtr value) {
    register_values_[reg] = value;
    // Also set the type for consistency
    if (value) {
        set_register_type(reg, value->type);
    }
}

ValuePtr Generator::get_register_value(Reg reg) {
    // First check if we have a stored value
    auto it = register_values_.find(reg);
    if (it != register_values_.end()) {
        return it->second;
    }
    
    // If no stored value, try to create one from the type
    TypePtr type = get_register_type(reg);
    if (type) {
        if (type->tag == TypeTag::Int) {
            return std::make_shared<Value>(type, static_cast<int64_t>(0));
        } else if (type->tag == TypeTag::Float32) {
            return std::make_shared<Value>(type, 0.0);
        } else if (type->tag == TypeTag::Bool) {
            return std::make_shared<Value>(type, false);
        } else if (type->tag == TypeTag::String) {
            return std::make_shared<Value>(type, std::string(""));
        }
    }
    
    // Fallback: return an int value
    auto int_type = std::make_shared<Type>(TypeTag::Int);
    return std::make_shared<Value>(int_type, static_cast<int64_t>(0));
}

void Generator::emit_instruction(const LIR_Inst& inst) {
    if (current_function_) {
        if (cfg_context_.building_cfg && cfg_context_.current_block) {
            if (cfg_context_.current_block->has_terminator()) {
                // If the block is already terminated, create a new block for subsequent instructions
                LIR_BasicBlock* new_block = create_basic_block("unreachable");
                set_current_block(new_block);
            }
            cfg_context_.current_block->add_instruction(inst);
        } else {
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
    } else if (auto unsafe_stmt = dynamic_cast<AST::UnsafeStatement*>(&stmt)) {
        emit_unsafe_stmt(*unsafe_stmt);
    } else if (auto class_stmt = dynamic_cast<AST::ClassDeclaration*>(&stmt)) {
        emit_class_stmt(*class_stmt);
    } else if (auto match_stmt = dynamic_cast<AST::MatchStatement*>(&stmt)) {
        emit_match_stmt(*match_stmt);
    } else if (auto module_stmt = dynamic_cast<AST::ModuleDeclaration*>(&stmt)) {
        emit_module_stmt(*module_stmt);
    } else {
        report_error("Unsupported statement type in LIR generator");
    }
}

Reg Generator::emit_expr(AST::Expression& expr) {
    if (auto literal = dynamic_cast<AST::LiteralExpr*>(&expr)) {
        return emit_literal_expr(*literal, nullptr);
    } else if (auto variable = dynamic_cast<AST::VariableExpr*>(&expr)) {
        return emit_variable_expr(*variable);
    } else if (auto interpolated = dynamic_cast<AST::InterpolatedStringExpr*>(&expr)) {
        return emit_interpolated_string_expr(*interpolated);
    } else if (auto binary = dynamic_cast<AST::BinaryExpr*>(&expr)) {
        return emit_binary_expr(*binary);
    } else if (auto unary = dynamic_cast<AST::UnaryExpr*>(&expr)) {
        return emit_unary_expr(*unary);
    } else if (auto assign = dynamic_cast<AST::AssignExpr*>(&expr)) {
        return emit_assign_expr(*assign);
    } else if (auto call = dynamic_cast<AST::CallExpr*>(&expr)) {
        return emit_call_expr(*call);
    } else if (auto closure_call = dynamic_cast<AST::CallClosureExpr*>(&expr)) {
        return emit_call_closure_expr(*closure_call);
    } else if (auto list = dynamic_cast<AST::ListExpr*>(&expr)) {
        return emit_list_expr(*list);
    } else if (auto grouping = dynamic_cast<AST::GroupingExpr*>(&expr)) {
        return emit_grouping_expr(*grouping);
    } else if (auto ternary = dynamic_cast<AST::TernaryExpr*>(&expr)) {
        return emit_ternary_expr(*ternary);
    } else if (auto index = dynamic_cast<AST::IndexExpr*>(&expr)) {
        return emit_index_expr(*index);
    } else if (auto member = dynamic_cast<AST::MemberExpr*>(&expr)) {
        return emit_member_expr(*member);
    } else if (auto tuple = dynamic_cast<AST::TupleExpr*>(&expr)) {
        return emit_tuple_expr(*tuple);
    } else if (auto dict = dynamic_cast<AST::DictExpr*>(&expr)) {
        return emit_dict_expr(*dict);
    } else if (auto range = dynamic_cast<AST::RangeExpr*>(&expr)) {
        return emit_range_expr(*range);
    } else if (auto lambda = dynamic_cast<AST::LambdaExpr*>(&expr)) {
        return emit_lambda_expr(*lambda);
    } else if (auto error_construct = dynamic_cast<AST::ErrorConstructExpr*>(&expr)) {
        return emit_error_construct_expr(*error_construct);
    } else if (auto ok_construct = dynamic_cast<AST::OkConstructExpr*>(&expr)) {
        return emit_ok_construct_expr(*ok_construct);
    } else if (auto fallible = dynamic_cast<AST::FallibleExpr*>(&expr)) {
        return emit_fallible_expr(*fallible);
    } else if (auto object_literal = dynamic_cast<AST::ObjectLiteralExpr*>(&expr)) {
        return emit_object_literal_expr(*object_literal);
    } else if (auto this_expr = dynamic_cast<AST::ThisExpr*>(&expr)) {
        return emit_this_expr(*this_expr);
    } else {
        report_error("Unknown expression type");
        return 0;
    }
}

TypePtr Generator::get_promoted_numeric_type(TypePtr left_type, TypePtr right_type) {
    // If either type is null, default to Int64
    if (!left_type || !right_type) {
        return std::make_shared<Type>(TypeTag::Int64);
    }
    
    // If either is string, result is string
    if (left_type->tag == TypeTag::String || right_type->tag == TypeTag::String) {
        return std::make_shared<Type>(TypeTag::String);
    }
    
    // If either is float, promote to the larger float type
    bool left_is_float = (left_type->tag == TypeTag::Float32 || left_type->tag == TypeTag::Float64);
    bool right_is_float = (right_type->tag == TypeTag::Float32 || right_type->tag == TypeTag::Float64);
    
    if (left_is_float || right_is_float) {
        if (left_type->tag == TypeTag::Float64 || right_type->tag == TypeTag::Float64) {
            return std::make_shared<Type>(TypeTag::Float64);
        }
        return std::make_shared<Type>(TypeTag::Float32);
    }
    
    // Both are integers - use the "smaller matches larger" strategy
    int left_rank = get_type_rank(left_type);
    int right_rank = get_type_rank(right_type);
    
    // If ranks are equal, prefer unsigned over signed to preserve unsigned semantics
    if (left_rank == right_rank) {
        bool left_is_unsigned = !is_signed_integer_type(left_type);
        bool right_is_unsigned = !is_signed_integer_type(right_type);
        
        if (left_is_unsigned) return left_type;
        if (right_is_unsigned) return right_type;
        
        // Both signed, return either
        return left_type;
    }
    
    // Return the type with higher rank (larger/more complex type)
    // But if the higher rank type is signed and lower rank is unsigned, 
    // and they're close in rank, prefer unsigned to avoid signed overflow
    TypePtr higher_type = (left_rank > right_rank) ? left_type : right_type;
    TypePtr lower_type = (left_rank > right_rank) ? right_type : left_type;
    
    bool higher_is_unsigned = !is_signed_integer_type(higher_type);
    bool lower_is_unsigned = !is_signed_integer_type(lower_type);
    
    // If lower is unsigned and higher is signed, and ranks are close, use unsigned version of higher
    if (lower_is_unsigned && !higher_is_unsigned && (left_rank - right_rank <= 2 || right_rank - left_rank <= 2)) {
        return get_unsigned_version(higher_type);
    }
    
    return higher_type;
}

int Generator::get_type_rank(TypePtr type) {
    if (!type) return 0;
    
    switch (type->tag) {
        case TypeTag::Int8: case TypeTag::UInt8: return 1;
        case TypeTag::Int16: case TypeTag::UInt16: return 2;
        case TypeTag::Int32: case TypeTag::UInt32: return 3;
        case TypeTag::Int: case TypeTag::UInt: case TypeTag::Int64: case TypeTag::UInt64: return 4;
        case TypeTag::Int128: case TypeTag::UInt128: return 5;
        case TypeTag::Float32: return 6;
        case TypeTag::Float64: return 7;
        case TypeTag::String: return 8;
        case TypeTag::Bool: return 0;
        default: return 0;
    }
}

bool Generator::is_signed_integer_type(TypePtr type) {
    if (!type) return false;
    return (type->tag == TypeTag::Int || type->tag == TypeTag::Int8 || 
            type->tag == TypeTag::Int16 || type->tag == TypeTag::Int32 || 
            type->tag == TypeTag::Int64 || type->tag == TypeTag::Int128);
}

TypePtr Generator::get_wider_integer_type(TypePtr left_type, TypePtr right_type) {
    if (!left_type || !right_type) {
        return std::make_shared<Type>(TypeTag::Int64);
    }
    
    // Define type precedence (from narrowest to widest)
    std::map<TypeTag, int> type_rank = {
        {TypeTag::Int8, 1}, {TypeTag::UInt8, 1},
        {TypeTag::Int16, 2}, {TypeTag::UInt16, 2},
        {TypeTag::Int32, 3}, {TypeTag::UInt32, 3},
        {TypeTag::Int, 4}, {TypeTag::UInt, 4},
        {TypeTag::Int64, 5}, {TypeTag::UInt64, 5},
        {TypeTag::Int128, 6}, {TypeTag::UInt128, 6}
    };
    
    int left_rank = type_rank[left_type->tag];
    int right_rank = type_rank[right_type->tag];
    
    if (left_rank >= right_rank) {
        return left_type;
    } else {
        return right_type;
    }
}

TypePtr Generator::get_unsigned_version(TypePtr type) {
    if (!type) return std::make_shared<Type>(TypeTag::UInt64);
    
    switch (type->tag) {
        case TypeTag::Int8: return std::make_shared<Type>(TypeTag::UInt8);
        case TypeTag::Int16: return std::make_shared<Type>(TypeTag::UInt16);
        case TypeTag::Int32: return std::make_shared<Type>(TypeTag::UInt32);
        case TypeTag::Int: 
        case TypeTag::Int64: return std::make_shared<Type>(TypeTag::UInt64);
        case TypeTag::Int128: return std::make_shared<Type>(TypeTag::UInt128);
        case TypeTag::UInt8: 
        case TypeTag::UInt16: 
        case TypeTag::UInt32: 
        case TypeTag::UInt: 
        case TypeTag::UInt64: 
        case TypeTag::UInt128: return type; // Already unsigned
        default: return std::make_shared<Type>(TypeTag::UInt64);
    }
}

TypePtr Generator::get_best_integer_type(const std::string& value_str, bool prefer_signed) {
    try {
        // Try to parse as unsigned long long to check the magnitude
        unsigned long long ull_val = std::stoull(value_str);
        
        // Check system support for 128-bit integers
        bool has_int128 = false;
#ifdef __SIZEOF_INT128__
        has_int128 = true;
#endif
        
        if (prefer_signed) {
            // For signed integers, check if it fits in various ranges
            if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<int8_t>::max())) {
                return std::make_shared<Type>(TypeTag::Int8);
            } else if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<int16_t>::max())) {
                return std::make_shared<Type>(TypeTag::Int16);
            } else if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<int32_t>::max())) {
                return std::make_shared<Type>(TypeTag::Int32);
            } else if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<int64_t>::max())) {
                return std::make_shared<Type>(TypeTag::Int64);
            } else if (has_int128) {
                return std::make_shared<Type>(TypeTag::Int128);
            } else {
                // Fallback to unsigned if too large for signed
                return get_best_integer_type(value_str, false);
            }
        } else {
            // For unsigned integers
            if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<uint8_t>::max())) {
                return std::make_shared<Type>(TypeTag::UInt8);
            } else if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<uint16_t>::max())) {
                return std::make_shared<Type>(TypeTag::UInt16);
            } else if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<uint32_t>::max())) {
                return std::make_shared<Type>(TypeTag::UInt32);
            } else if (ull_val <= static_cast<unsigned long long>(std::numeric_limits<uint64_t>::max())) {
                return std::make_shared<Type>(TypeTag::UInt64);
            } else if (has_int128) {
                return std::make_shared<Type>(TypeTag::UInt128);
            } else {
                // If no 128-bit support, this is an overflow situation
                return std::make_shared<Type>(TypeTag::UInt64);
            }
        }
    } catch (const std::exception&) {
        // If parsing fails, default to Int64
        return std::make_shared<Type>(TypeTag::Int64);
    }
}

bool Generator::is_numeric_string(const std::string& str) {
    if (str.empty()) return false;
    
    char first = str[0];
    if (!(std::isdigit(first) || first == '+' || first == '-' || first == '.')) {
        return false;
    }
    
    // Check if all characters are valid for a number
    for (char c : str) {
        if (!std::isdigit(c) && c != '.' && c != '+' && c != '-' && 
            c != 'e' && c != 'E' && c != 'u' && c != 'U' && 
            c != 'l' && c != 'L' && c != 'f' && c != 'F') {
            return false;
        }
    }
    return true;
}

bool Generator::types_match(TypePtr type1, TypePtr type2) {
    if (!type1 || !type2) return false;
    return type1->tag == type2->tag;
}

// Expression handlers
Reg Generator::emit_literal_expr(AST::LiteralExpr& expr, TypePtr expected_type) {
    Reg dst = allocate_register();
    
    // Create ValuePtr based on literal value
    ValuePtr const_val;
    
    if (std::holds_alternative<std::string>(expr.value)) {
        std::string stringValue = std::get<std::string>(expr.value);
        
        // Try to determine if this string represents a pure number
        bool isNumeric = false;
        bool isFloat = false;
        
        if (!stringValue.empty()) {
            char first = stringValue[0];
            if (std::isdigit(first) || first == '+' || first == '-' || first == '.') {
                // Check if the ENTIRE string is a valid number
                bool hasInvalidChars = false;
                for (char c : stringValue) {
                    if (!std::isdigit(c) && c != '.' && c != '+' && c != '-' && 
                        c != 'e' && c != 'E' && c != 'u' && c != 'U' && 
                        c != 'l' && c != 'L' && c != 'f' && c != 'F') {
                        hasInvalidChars = true;
                        break;
                    }
                }
                
                if (!hasInvalidChars) {
                    isNumeric = true;
                    // Check if it's a float
                    if (stringValue.find('.') != std::string::npos || 
                        stringValue.find('e') != std::string::npos || 
                        stringValue.find('E') != std::string::npos) {
                        isFloat = true;
                    }
                }
            }
        }
        
        if (isNumeric) {
            if (isFloat) {
                // Create float value
                auto float_type = expected_type ? expected_type : std::make_shared<Type>(TypeTag::Float64);
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
                // Create integer value - use expected type if provided
                std::shared_ptr<Type> int_type = expected_type;
                
                if (!int_type) {
                    // For simple small literals, default to Int64 to avoid type mismatches
                    // This is a conservative approach that works well with mixed operations
                    try {
                        int64_t test_val = std::stoll(stringValue);
                        // If it fits in int64 and is a small number, use Int64
                        if (test_val >= 0 && test_val <= 1000000) {
                            int_type = std::make_shared<Type>(TypeTag::Int64);
                        } else {
                            // For larger values, use automatic type selection
                            int_type = get_best_integer_type(stringValue, true);
                        }
                    } catch (const std::exception&) {
                        // If parsing as signed fails, use automatic selection
                        int_type = get_best_integer_type(stringValue, true);
                    }
                }
                
                try {
                    int64_t intVal = std::stoll(stringValue);
                    const_val = std::make_shared<Value>(int_type, intVal);
                } catch (const std::exception&) {
                    // If parsing as signed fails, try unsigned
                    try {
                        uint64_t uintVal = std::stoull(stringValue);
                        const_val = std::make_shared<Value>(int_type, uintVal);
                    } catch (const std::exception&) {
                        // If parsing fails, treat as string
                        auto string_type = std::make_shared<Type>(TypeTag::String);
                        const_val = std::make_shared<Value>(string_type, stringValue);
                        current_function_->instructions.back().const_val->type = string_type;
                    }
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
    // First check if this is a module variable access (e.g., "math.pi")
    size_t dot_pos = expr.name.find("::");
    if (dot_pos != std::string::npos) {
        std::string module_name = expr.name.substr(0, dot_pos);
        std::string symbol_name = expr.name.substr(dot_pos + 2);
        
        // Check for alias mapping
        auto alias_it = import_aliases_.find(module_name);
        if (alias_it != import_aliases_.end()) {
            module_name = alias_it->second;
        }
        
        // Resolve module symbol
        std::string qualified_name = module_name + "::" + symbol_name;
        ModuleSymbolInfo* symbol = resolve_module_symbol(qualified_name);
        if (symbol && symbol->is_variable) {
            if (!can_access_module_symbol(*symbol, current_module_)) {
                report_error("Cannot access private/protected variable: " + qualified_name);
                return 0;
            }
            
            // For now, return a placeholder - in a full implementation,
            // we'd need to load the actual module variable value
            Reg result = allocate_register();
            auto var_type = std::make_shared<Type>(TypeTag::Any);
            set_register_type(result, var_type);
            return result;
        }
    }
    
    // Check regular variable scope
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

    // Check for constant folding opportunity
    bool all_parts_are_string_literals = true;
    std::string folded_result = "";
    
    for (const auto& part : expr.parts) {
        if (std::holds_alternative<std::string>(part)) {
            folded_result += std::get<std::string>(part);
        } else {
            all_parts_are_string_literals = false;
            break;
        }
    }
    
    // Constant folding: if all parts are string literals, fold them
    if (all_parts_are_string_literals) {
        Reg result = allocate_register();
        ValuePtr result_val = std::make_shared<Value>(string_type, folded_result);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, result, result_val));
        set_register_type(result, string_type);
        return result;
    }

    // For complex interpolations, use STR_FORMAT
    // Build format string and collect argument registers
    std::string format_string = "";
    std::vector<Reg> arg_regs;
    
    for (const auto& part : expr.parts) {
        if (std::holds_alternative<std::string>(part)) {
            format_string += std::get<std::string>(part);
        } else if (std::holds_alternative<std::shared_ptr<AST::Expression>>(part)) {
            format_string += "%s"; // Simple placeholder for now
            auto expr_part = std::get<std::shared_ptr<AST::Expression>>(part);
            Reg expr_reg = emit_expr(*expr_part);
            arg_regs.push_back(expr_reg);
        }
    }
    
    // Emit STR_FORMAT instruction
    Reg result = allocate_register();
    Reg format_reg = allocate_register();
    ValuePtr format_val = std::make_shared<Value>(string_type, format_string);
    emit_instruction(LIR_Inst(LIR_Op::LoadConst, format_reg, format_val));
    
    // Handle multiple arguments by chaining STR_FORMAT calls
    Reg current_result = format_reg;
    for (size_t i = 0; i < arg_regs.size(); i++) {
        if (i == 0) {
            // First argument: format with first arg
            emit_instruction(LIR_Inst(LIR_Op::STR_FORMAT, result, format_reg, arg_regs[i]));
            current_result = result;
        } else {
            // Subsequent arguments: format previous result with next arg
            Reg temp_result = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::STR_FORMAT, temp_result, current_result, arg_regs[i]));
            current_result = temp_result;
            if (i == arg_regs.size() - 1) {
                // Final result is in temp_result, move to result register
                emit_instruction(LIR_Inst(LIR_Op::Mov, result, temp_result, 0));
            }
        }
    }
    
    set_register_type(result, string_type);
    return result;
}

Reg Generator::emit_binary_expr(AST::BinaryExpr& expr) {
    // Handle explicit string concatenation (+) with STR_CONCAT
    if (expr.op == TokenType::PLUS) {
        // Check if this is string concatenation by examining operand types
        bool left_is_string = false;
        bool right_is_string = false;
        std::string left_str, right_str;
        
        // Check left operand for string literal or variable
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
        } else if (auto left_var = dynamic_cast<AST::VariableExpr*>(expr.left.get())) {
            // Check if variable is known to be a string type
            Reg left_reg = resolve_variable(left_var->name);
            if (left_reg != UINT32_MAX) {
                TypePtr left_type = get_register_type(left_reg);
                if (left_type && left_type->tag == TypeTag::String) {
                    left_is_string = true;
                }
            }
        }
        
        // Check right operand for string literal or variable
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
        } else if (auto right_var = dynamic_cast<AST::VariableExpr*>(expr.right.get())) {
            // Check if variable is known to be a string type
            Reg right_reg = resolve_variable(right_var->name);
            if (right_reg != UINT32_MAX) {
                TypePtr right_type = get_register_type(right_reg);
                if (right_type && right_type->tag == TypeTag::String) {
                    right_is_string = true;
                }
            }
        }
        
        // If either operand is a non-numeric string, use STR_CONCAT
        if (left_is_string || right_is_string) {
            Reg left = emit_expr(*expr.left);
            Reg right = emit_expr(*expr.right);
            Reg dst = allocate_register();
            
            // Use STR_CONCAT for explicit string addition
            emit_instruction(LIR_Inst(LIR_Op::STR_CONCAT, dst, left, right));
            
            // Set result type as string
            auto string_type = std::make_shared<Type>(TypeTag::String);
            set_register_type(dst, string_type);
            return dst;
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
            // For integer operations, preserve signedness and promote to wider type
            result_type = get_promoted_numeric_type(left_type, right_type);
        }
        
        // Check for type mismatches and re-emit if needed
        if (left_type && right_type && result_type) {
            // Implement "smaller matches larger" strategy
            int left_rank = get_type_rank(left_type);
            int right_rank = get_type_rank(right_type);
            
            // Re-emit the smaller/lower rank operand to match the larger one
            if (left_rank < right_rank) {
                if (auto left_literal = dynamic_cast<AST::LiteralExpr*>(expr.left.get())) {
                    left = emit_literal_expr(*left_literal, right_type);
                    left_type = right_type;
                }
            } else if (right_rank < left_rank) {
                if (auto right_literal = dynamic_cast<AST::LiteralExpr*>(expr.right.get())) {
                    right = emit_literal_expr(*right_literal, left_type);
                    right_type = left_type;
                }
            }
            // If ranks are equal but types differ, prefer signed to avoid unsigned promotion issues
            else if (left_rank == right_rank && !types_match(left_type, right_type)) {
                bool left_is_signed = is_signed_integer_type(left_type);
                bool right_is_signed = is_signed_integer_type(right_type);
                
                if (!left_is_signed && right_is_signed) {
                    auto left_literal = dynamic_cast<AST::LiteralExpr*>(expr.left.get());
                    if (left_literal) {
                        left = emit_literal_expr(*left_literal, right_type);
                        left_type = right_type;
                    }
                } else if (left_is_signed && !right_is_signed) {
                    auto right_literal = dynamic_cast<AST::LiteralExpr*>(expr.right.get());
                    if (right_literal) {
                        right = emit_literal_expr(*right_literal, left_type);
                        right_type = left_type;
                    }
                }
            }
        }
    } else if (op == LIR_Op::CmpEQ || op == LIR_Op::CmpNEQ || op == LIR_Op::CmpLT || 
               op == LIR_Op::CmpLE || op == LIR_Op::CmpGT || op == LIR_Op::CmpGE) {
        // Comparison operations return bool
        result_type = std::make_shared<Type>(TypeTag::Bool);
    } else if (op == LIR_Op::And || op == LIR_Op::Or) {
        // Logical operations return bool
        result_type = std::make_shared<Type>(TypeTag::Bool);
    } else if (op == LIR_Op::Xor) {
        // Bitwise XOR should preserve integer types like arithmetic operations
        result_type = get_promoted_numeric_type(left_type, right_type);
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
    // Generate proper Call instruction with function ID
    // The JIT will resolve and call the function at runtime
    
    if (auto var_expr = dynamic_cast<AST::VariableExpr*>(expr.callee.get())) {
        std::string func_name = var_expr->name;
        
        // Check if this is a module function call (e.g., "math.add")
        size_t dot_pos = func_name.find("::");
        if (dot_pos != std::string::npos) {
            std::string module_name = func_name.substr(0, dot_pos);
            std::string symbol_name = func_name.substr(dot_pos + 2);
            
            // Check for alias mapping
            auto alias_it = import_aliases_.find(module_name);
            if (alias_it != import_aliases_.end()) {
                module_name = alias_it->second;
            }
            
            // Resolve module symbol
            std::string qualified_name = module_name + "::" + symbol_name;
            ModuleSymbolInfo* symbol = resolve_module_symbol(qualified_name);
            if (symbol && symbol->is_function) {
                if (!can_access_module_symbol(*symbol, current_module_)) {
                    report_error("Cannot access private/protected function: " + qualified_name);
                    return 0;
                }
                
                std::cout << "[DEBUG] LIR Generator: Generating module function call to '" << qualified_name << "'" << std::endl;
                
                // Evaluate arguments and store them in registers
                std::vector<Reg> arg_regs;
                for (const auto& arg : expr.arguments) {
                    Reg arg_reg = emit_expr(*arg);
                    arg_regs.push_back(arg_reg);
                }
                
                // Allocate result register
                Reg result = allocate_register();
                
                // Generate module function call
                emit_instruction(LIR_Inst(LIR_Op::Call, result, static_cast<Reg>(arg_regs.size()), static_cast<Reg>(0)));
                set_register_type(result, std::make_shared<Type>(TypeTag::Any));
                
                return result;
            }
        }
        
        if (BuiltinUtils::isBuiltinFunction(func_name)) {
            std::cout << "[DEBUG] LIR Generator: Generating builtin call to '" << func_name << "'" << std::endl;
            
            // Evaluate arguments and store them in registers
            std::vector<Reg> arg_regs;
            for (const auto& arg : expr.arguments) {
                Reg arg_reg = emit_expr(*arg);
                arg_regs.push_back(arg_reg);
            }
            
            // Allocate result register
            Reg result = allocate_register();
            
            // Generate builtin call instruction with function ID
            // For now, use a special ID for builtins (negative numbers)
            int32_t builtin_id = -1; // Will be resolved by function name
            emit_instruction(LIR_Inst(LIR_Op::Call, result, static_cast<Reg>(arg_regs.size()), static_cast<Reg>(builtin_id)));
            set_register_type(result, std::make_shared<Type>(TypeTag::Any));
            
            return result;
            
        } else if (function_table_.find(func_name) != function_table_.end()) {
            std::cout << "[DEBUG] LIR Generator: Generating call to user function '" << func_name << "'" << std::endl;
            
            // Evaluate arguments and store them in registers
            std::vector<Reg> arg_regs;
            for (const auto& arg : expr.arguments) {
                Reg arg_reg = emit_expr(*arg);
                arg_regs.push_back(arg_reg);
            }
            
            // Allocate result register
            Reg result = allocate_register();
            
            // Generate call instruction - function will be resolved by JIT
            emit_instruction(LIR_Inst(LIR_Op::Call, result, static_cast<Reg>(arg_regs.size()), static_cast<Reg>(0)));
            set_register_type(result, std::make_shared<Type>(TypeTag::Any));
            
            return result;
            
        } else {
            report_error("Unknown function: " + func_name);
            return 0;
        }
    } else if (auto member_expr = dynamic_cast<AST::MemberExpr*>(expr.callee.get())) {
        // Method call: obj.method(args...)
        std::string method_name = member_expr->name;
        
        // Evaluate the object (this will be the first argument)
        Reg object_reg = emit_expr(*member_expr->object);
        
        // Try to find the method in any class
        for (const auto& [class_name, class_info] : class_table_) {
            auto method_it = class_info.method_indices.find(method_name);
            if (method_it != class_info.method_indices.end()) {
                // Found the method - generate method call
                std::vector<Reg> arg_regs;
                arg_regs.push_back(object_reg); // 'this' is first parameter
                
                // Evaluate other arguments
                for (const auto& arg : expr.arguments) {
                    Reg arg_reg = emit_expr(*arg);
                    arg_regs.push_back(arg_reg);
                }
                
                // Allocate result register
                Reg result = allocate_register();
                
                // Generate method call using V-Table dispatch
                // For now, we'll use a simple approach - in a full implementation,
                // we'd load the V-Table and do dynamic dispatch
                std::string full_method_name = class_name + "." + method_name;
                if (function_table_.find(full_method_name) != function_table_.end()) {
                    emit_instruction(LIR_Inst(LIR_Op::Call, result, static_cast<Reg>(arg_regs.size()), static_cast<Reg>(0)));
                    set_register_type(result, std::make_shared<Type>(TypeTag::Any));
                    return result;
                }
            }
        }
        
        report_error("Unknown method: " + method_name);
        return 0;
    } else {
        report_error("Complex function calls not yet supported in LIR");
        return 0;
    }
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
        // For member or index assignment
        if (expr.member.has_value()) {
            // Field assignment: obj.field = value
            Reg object_reg = emit_expr(*expr.object);
            std::string field_name = expr.member.value();
            
            // Find field offset
            for (const auto& [class_name, class_info] : class_table_) {
                auto offset_it = class_info.field_offsets.find(field_name);
                if (offset_it != class_info.field_offsets.end()) {
                    // Found the field - emit SetField
                    emit_instruction(LIR_Inst(LIR_Op::SetField, object_reg, offset_it->second, value));
                    return value;
                }
            }
            
            report_error("Unknown field for assignment: " + field_name);
            return 0;
        } else {
            // Index assignment - not yet implemented
            report_error("Index assignment not yet implemented");
            return 0;
        }
    } else {
        report_error("Invalid assignment target");
        return 0;
    }
}

Reg Generator::emit_call_closure_expr(AST::CallClosureExpr& expr) {
    // Handle closure calls - calling a function stored in a variable
    // This enables first-order functions and closures
    
    // Evaluate the closure expression
    Reg closure_reg = emit_expr(*expr.closure);
    
    // Evaluate all positional arguments
    std::vector<Reg> arg_regs;
    for (const auto& arg : expr.arguments) {
        Reg arg_reg = emit_expr(*arg);
        arg_regs.push_back(arg_reg);
    }
    
    // Handle named arguments
    std::unordered_map<std::string, Reg> named_arg_regs;
    for (const auto& [name, arg] : expr.namedArgs) {
        Reg arg_reg = emit_expr(*arg);
        named_arg_regs[name] = arg_reg;
    }
    
    // Create a result register
    Reg result = allocate_register();
    
    // Emit closure call instruction
    // TODO: Implement proper closure calling with captured environment
    emit_instruction(LIR_Inst(LIR_Op::Call, result, closure_reg, 0));
    
    // Set default return type (for now)
    set_register_type(result, std::make_shared<Type>(TypeTag::Int));
    
    return result;
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
    // First evaluate the object expression
    Reg object_reg = emit_expr(*expr.object);
    
    // For now, we'll handle simple field access
    // In a full implementation, we'd need to determine if this is a field access or method call
    
    // Try to find field offset by checking all classes
    // This is a simplified approach - a full implementation would need proper type tracking
    for (const auto& [class_name, class_info] : class_table_) {
        auto offset_it = class_info.field_offsets.find(expr.name);
        if (offset_it != class_info.field_offsets.end()) {
            // Found the field - emit GetField
            Reg dst = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::GetField, dst, object_reg, offset_it->second));
            
            // Set the field type
            if (offset_it->second < class_info.fields.size()) {
                set_register_type(dst, class_info.fields[offset_it->second].second);
            }
            
            return dst;
        }
    }
    
    // If we get here, it's either a method call or unknown field
    // For now, we'll treat it as an error
    report_error("Unknown field or method: " + expr.name);
    return 0;
}

Reg Generator::emit_tuple_expr(AST::TupleExpr& expr) {
    report_error("Tuple expressions not yet implemented");
    return 0;
}

Reg Generator::emit_dict_expr(AST::DictExpr& expr) {
    report_error("Dict expressions not yet implemented");
    return 0;
}

Reg Generator::emit_range_expr(AST::RangeExpr& expr) {
    report_error("Range expressions not yet implemented");
    return 0;
}

Reg Generator::emit_lambda_expr(AST::LambdaExpr& expr) {
    report_error("Lambda expressions not yet implemented");
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
                    emit_instruction(LIR_Inst(LIR_Op::PrintInt, 0, value, 0));
                    return;
                case TypeTag::UInt:
                case TypeTag::UInt8:
                case TypeTag::UInt16:
                case TypeTag::UInt32:
                case TypeTag::UInt64:
                    emit_instruction(LIR_Inst(LIR_Op::PrintUint, 0, value, 0));
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
                            case TypeTag::UInt:
                            case TypeTag::UInt8:
                            case TypeTag::UInt16:
                            case TypeTag::UInt32:
                            case TypeTag::UInt64:
                                emit_instruction(LIR_Inst(LIR_Op::PrintUint, 0, value, 0));
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
        
        // Use the declared type if available, otherwise use the initializer's type
        TypePtr declared_type = nullptr;
        if (stmt.type.has_value()) {
            // Convert TypeAnnotation to Type - handle all basic types including 128-bit
            auto type_annotation = *stmt.type.value();
            if (type_annotation.typeName == "u32") {
                declared_type = std::make_shared<Type>(TypeTag::UInt32);
            } else if (type_annotation.typeName == "u16") {
                declared_type = std::make_shared<Type>(TypeTag::UInt16);
            } else if (type_annotation.typeName == "u8") {
                declared_type = std::make_shared<Type>(TypeTag::UInt8);
            } else if (type_annotation.typeName == "u64") {
                declared_type = std::make_shared<Type>(TypeTag::UInt64);
            } else if (type_annotation.typeName == "u128") {
                declared_type = std::make_shared<Type>(TypeTag::UInt128);
            } else if (type_annotation.typeName == "int") {
                declared_type = std::make_shared<Type>(TypeTag::Int64);
            } else if (type_annotation.typeName == "i64") {
                declared_type = std::make_shared<Type>(TypeTag::Int64);
            } else if (type_annotation.typeName == "i32") {
                declared_type = std::make_shared<Type>(TypeTag::Int32);
            } else if (type_annotation.typeName == "i16") {
                declared_type = std::make_shared<Type>(TypeTag::Int16);
            } else if (type_annotation.typeName == "i8") {
                declared_type = std::make_shared<Type>(TypeTag::Int8);
            } else if (type_annotation.typeName == "i128") {
                declared_type = std::make_shared<Type>(TypeTag::Int128);
            } else if (type_annotation.typeName == "f64") {
                declared_type = std::make_shared<Type>(TypeTag::Float64);
            } else if (type_annotation.typeName == "f32") {
                declared_type = std::make_shared<Type>(TypeTag::Float32);
            } else if (type_annotation.typeName == "bool") {
                declared_type = std::make_shared<Type>(TypeTag::Bool);
            } else if (type_annotation.typeName == "str" || type_annotation.typeName == "string") {
                declared_type = std::make_shared<Type>(TypeTag::String);
            }
        }
        
        if (declared_type) {
            set_register_type(value_reg, declared_type);
        } else {
            set_register_type(value_reg, get_register_type(value));
        }
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
    if (cfg_context_.building_cfg) {
        // CFG mode: create basic blocks
        emit_if_stmt_cfg(stmt);
    } else {
        // Linear mode: use conditional jumps
        emit_if_stmt_linear(stmt);
    }
}

void Generator::emit_if_stmt_cfg(AST::IfStatement& stmt) {
    // CFG mode: create basic blocks
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
        add_block_edge(then_block, end_block);  // Add CFG edge
    }
    
    // === Else Block (if present) ===
    if (else_block) {
        set_current_block(else_block);
        
        // Emit else branch
        if (stmt.elseBranch) {
            emit_stmt(*stmt.elseBranch);
        }
        
        // Jump to end after else branch (only if no terminator already exists)
        if (get_current_block() && !get_current_block()->has_terminator()) {
            emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, end_block->id));
            add_block_edge(else_block, end_block);  // Add CFG edge
        }
    }
    
    // === End Block: continuation ===
    set_current_block(end_block);
    
    // Don't mark end_block as terminated - it's a continuation point for subsequent statements
    // Only mark as terminated if it has explicit terminator instructions
    if (end_block && end_block->has_terminator()) {
        end_block->terminated = true;
    }
}

void Generator::emit_if_stmt_linear(AST::IfStatement& stmt) {
    // Emit condition
    Reg condition = emit_expr(*stmt.condition);
    Reg condition_bool = allocate_register();
    
    // Convert condition to boolean if needed
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
    
    // For linear mode, we'll simplify: just emit the then branch for now
    // TODO: Implement proper conditional jumps for linear mode
    emit_stmt(*stmt.thenBranch);
    
    if (stmt.elseBranch) {
        emit_stmt(*stmt.elseBranch);
    }
}

void Generator::emit_while_stmt(AST::WhileStatement& stmt) {
    if (cfg_context_.building_cfg) {
        // CFG mode: create basic blocks
        emit_while_stmt_cfg(stmt);
    } else {
        // Linear mode: use loop instructions
        emit_while_stmt_linear(stmt);
    }
}

void Generator::emit_while_stmt_cfg(AST::WhileStatement& stmt) {
    // CFG mode: create basic blocks for while loop
    enter_scope();
    enter_loop();
    
    LIR_BasicBlock* header_block = create_basic_block("while_header");
    LIR_BasicBlock* body_block = create_basic_block("while_body");
    LIR_BasicBlock* end_block = create_basic_block("while_end");
    
    // Set loop labels for break/continue
    set_loop_labels(header_block->id, end_block->id, header_block->id);
    
    // Connect current block to header block
    add_block_edge(get_current_block(), header_block);
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    
    // Emit condition check in header block
    set_current_block(header_block);
    
    // Emit loop condition
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
    
    // Conditional jump: if false, exit loop
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, condition_bool, 0, end_block->id));
    
    // Set up edges from header block
    add_block_edge(header_block, body_block);  // Continue if true
    add_block_edge(header_block, end_block);   // Exit if false
    
    // === Body Block ===
    set_current_block(body_block);
    
    // Emit loop body
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Jump back to header to continue loop
    if (get_current_block() && !get_current_block()->has_terminator()) {
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
        add_block_edge(body_block, header_block);
    }
    
    // === End Block: continuation ===
    set_current_block(end_block);
    
    exit_loop();
    exit_scope();
    
    // Don't mark end_block as terminated - it's a continuation point for subsequent statements
    // Only mark as terminated if it has explicit terminator instructions
    if (end_block && end_block->has_terminator()) {
        end_block->terminated = true;
    }
}

void Generator::emit_while_stmt_linear(AST::WhileStatement& stmt) {
    // For linear mode, implement a simple while loop
    // TODO: This is a simplified version - proper implementation needs labels/jumps
    
    // For now, just emit the body once (simplified)
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
}

void Generator::emit_for_stmt(AST::ForStatement& stmt) {
    if (cfg_context_.building_cfg) {
        // CFG mode: create basic blocks
        emit_for_stmt_cfg(stmt);
    } else {
        // Linear mode: use loop instructions
        emit_for_stmt_linear(stmt);
    }
}

void Generator::emit_for_stmt_cfg(AST::ForStatement& stmt) {
    // CFG mode: create basic blocks for for loop
    enter_scope();
    enter_loop();
    
    LIR_BasicBlock* init_block = create_basic_block("for_init");
    LIR_BasicBlock* header_block = create_basic_block("for_header");
    LIR_BasicBlock* body_block = create_basic_block("for_body");
    LIR_BasicBlock* increment_block = create_basic_block("for_increment");
    LIR_BasicBlock* end_block = create_basic_block("for_end");
    
    // Set loop labels for break/continue
    set_loop_labels(header_block->id, end_block->id, increment_block->id);
    
    // Connect current block to init block
    add_block_edge(get_current_block(), init_block);
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, init_block->id));
    
    // === Init Block (executed only once) ===
    set_current_block(init_block);
    
    if (stmt.initializer) {
        emit_stmt(*stmt.initializer);
    }
    
    // Jump to header after initialization
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(init_block, header_block);
    
    // === Header Block (executed each iteration) ===
    set_current_block(header_block);
    
    // Emit condition check
    Reg condition = allocate_register();
    if (stmt.condition) {
        Reg condition_expr = emit_expr(*stmt.condition);
        
        // For boolean conditions, use them directly
        TypePtr condition_type = get_register_type(condition_expr);
        if (condition_type && condition_type->tag == TypeTag::Bool) {
            condition = condition_expr;
        } else {
            // Convert non-boolean condition to boolean
            Reg zero_reg = allocate_register();
            auto int_type = std::make_shared<Type>(TypeTag::Int);
            ValuePtr zero_val = std::make_shared<Value>(int_type, (int64_t)0);
            emit_instruction(LIR_Inst(LIR_Op::LoadConst, zero_reg, zero_val));
            set_register_type(zero_reg, int_type);
            emit_instruction(LIR_Inst(LIR_Op::CmpNEQ, condition, condition_expr, zero_reg));
            set_register_type(condition, std::make_shared<Type>(TypeTag::Bool));
        }
    } else {
        // No condition - always true
        auto bool_type = std::make_shared<Type>(TypeTag::Bool);
        ValuePtr true_val = std::make_shared<Value>(bool_type, true);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, condition, true_val));
        set_register_type(condition, bool_type);
    }
    
    // Conditional jump: if false, exit loop
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, condition, 0, end_block->id));
    
    // Set up edges from header block
    add_block_edge(header_block, body_block);  // Continue if true
    add_block_edge(header_block, end_block);   // Exit if false
    
    // === Body Block ===
    set_current_block(body_block);
    
    // Emit loop body
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Jump to increment block
    if (get_current_block() && !get_current_block()->has_terminator()) {
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, increment_block->id));
        add_block_edge(body_block, increment_block);
    }
    
    // === Increment Block ===
    set_current_block(increment_block);
    
    // Emit increment - for loop increment is typically an assignment expression
    if (stmt.increment) {
        // Create an expression statement from increment expression
        AST::ExprStatement expr_stmt;
        expr_stmt.expression = stmt.increment;
        emit_stmt(expr_stmt);
    }
    
    // Jump back to header to continue loop
    if (get_current_block() && !get_current_block()->has_terminator()) {
        emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
        add_block_edge(increment_block, header_block);
    }
    
    // === End Block: continuation ===
    set_current_block(end_block);
    
    exit_loop();
    exit_scope();
    
    // Don't mark end_block as terminated - it's a continuation point for subsequent statements
    // Only mark as terminated if it has explicit terminator instructions
    if (end_block && end_block->has_terminator()) {
        end_block->terminated = true;
    }
}

void Generator::emit_for_stmt_linear(AST::ForStatement& stmt) {
    // For linear mode, implement a simple for loop
    // TODO: This is a simplified version - proper implementation needs labels/jumps
    
    // Emit initialization
    if (stmt.initializer) {
        emit_stmt(*stmt.initializer);
    }
    
    // For now, just emit body once (simplified)
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Emit increment
    if (stmt.increment) {
        emit_expr(*stmt.increment); // increment is an Expression, not Statement
    }
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
    std::cout << "[DEBUG] LIR Generator: Pass 1 - Processing function '" << stmt.name << "'" << std::endl;
    
    // Generate proper LIR instructions for function body
    // Save current context
    auto saved_function = std::move(current_function_);
    auto saved_next_register = next_register_;
    auto saved_cfg_context = cfg_context_;
    
    // Create a new function for this function body
    auto func = std::make_unique<LIR_Function>(stmt.name, stmt.params.size());
    current_function_ = std::move(func);
    next_register_ = stmt.params.size();  // Start after parameters
    
    // Disable CFG building for function bodies (use linear instructions)
    cfg_context_.building_cfg = false;
    cfg_context_.current_block = nullptr;
    
    // Enter function scope for parameter bindings
    enter_scope();
    
    // Bind parameters to registers
    for (size_t i = 0; i < stmt.params.size(); ++i) {
        bind_variable(stmt.params[i].first, static_cast<Reg>(i));
        set_register_type(static_cast<Reg>(i), nullptr);
    }
    
    // Emit function body from AST
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Ensure function has a return instruction
    if (current_function_->instructions.empty() || 
        !current_function_->instructions.back().isReturn()) {
        // If no explicit return, add implicit return of 0
        Reg return_reg = allocate_register();
        auto int_type = std::make_shared<Type>(TypeTag::Int64);
        ValuePtr zero_val = std::make_shared<Value>(int_type, int64_t(0));
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, return_reg, zero_val));
        emit_instruction(LIR_Inst(LIR_Op::Ret, return_reg, 0, 0));
    }
    
    // Exit function scope
    exit_scope();
    
    // Create function metadata for registration
    std::vector<LIRParameter> params;
    for (size_t i = 0; i < stmt.params.size(); ++i) {
        LIRParameter lir_param;
        lir_param.name = stmt.params[i].first;
        auto param_type = convert_ast_type_to_lir_type(stmt.params[i].second);
        lir_param.type = param_type ? param_type : std::make_shared<Type>(TypeTag::Any);
        params.push_back(lir_param);
    }
    
    auto return_type = stmt.returnType ? convert_ast_type_to_lir_type(stmt.returnType.value()) : nullptr;
    if (!return_type) {
        return_type = std::make_shared<Type>(TypeTag::Int64);
    }
    
    // Create a simple lambda that delegates to JIT execution
    std::string func_name = stmt.name;
    LIRFunctionBody jit_body = [func_name](const std::vector<ValuePtr>& args) -> ValuePtr {
        // This lambda will be replaced by actual JIT execution
        // For now, return a default value
        auto int_type = std::make_shared<Type>(TypeTag::Int64);
        return std::make_shared<Value>(int_type, int64_t(0));
    };
    
    // Create the LIR function with the generated instructions
    auto lir_func = std::make_shared<LIRFunction>(func_name, params, return_type, jit_body);
    
    // Store the generated instructions in the LIRFunction
    lir_func->setInstructions(current_function_->instructions);
    
    // Debug asserts to ensure function invariants
    assert(!current_function_->instructions.empty() && "Function must have at least one instruction");
    assert(current_function_->instructions.back().isReturn() && "Function must end with a return instruction");
    
    std::cout << "[DEBUG] Generated " << current_function_->instructions.size() << " LIR instructions for function '" << stmt.name << "'" << std::endl;
    
    // Register function with LIRFunctionManager
    LIRFunctionManager::getInstance().registerFunction(lir_func);
    std::cout << "[DEBUG] Function registered successfully" << std::endl;
    
    // Restore context
    current_function_ = std::move(saved_function);
    next_register_ = saved_next_register;
    cfg_context_ = saved_cfg_context;
    
    std::cout << "[DEBUG] LIR Generator: Pass 1 complete - Function '" << stmt.name << "' updated with LIR implementation" << std::endl;
}

void Generator::emit_import_stmt(AST::ImportStatement& stmt) {
    // Smart import resolution - just update alias map, no LIR emission
    std::string alias = stmt.alias.value_or(stmt.modulePath);
    import_aliases_[alias] = stmt.modulePath;
    
    std::cout << "[DEBUG] Import registered: " << alias << " -> " << stmt.modulePath << std::endl;
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
    auto range_expr = dynamic_cast<AST::RangeExpr*>(stmt.iterable.get());
    if (!range_expr) {
        report_error("iter statement only supports range expressions for now");
        return;
    }

    if (stmt.loopVars.size() != 1) {
        report_error("iter statement currently supports only one loop variable");
        return;
    }
    const std::string& loop_var_name = stmt.loopVars[0];

    LIR_BasicBlock* header_block = create_basic_block("iter_header");
    LIR_BasicBlock* body_block = create_basic_block("iter_body");
    LIR_BasicBlock* increment_block = create_basic_block("iter_increment");
    LIR_BasicBlock* exit_block = create_basic_block("iter_exit");

    enter_scope();
    enter_loop();
    set_loop_labels(header_block->id, exit_block->id, increment_block->id);

    Reg loop_var_reg = allocate_register();
    bind_variable(loop_var_name, loop_var_reg);

    Reg start_reg = emit_expr(*range_expr->start);
    emit_instruction(LIR_Inst(LIR_Op::Mov, loop_var_reg, start_reg, 0));
    set_register_type(loop_var_reg, get_register_type(start_reg));

    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(get_current_block(), header_block);

    set_current_block(header_block);
    Reg end_reg = emit_expr(*range_expr->end);
    Reg cmp_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::CmpLT, cmp_reg, loop_var_reg, end_reg));
    set_register_type(cmp_reg, std::make_shared<Type>(TypeTag::Bool));
    emit_instruction(LIR_Inst(LIR_Op::JumpIfFalse, 0, cmp_reg, 0, exit_block->id));
    add_block_edge(header_block, body_block);
    add_block_edge(header_block, exit_block);

    set_current_block(body_block);
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, increment_block->id));
    add_block_edge(body_block, increment_block);

    set_current_block(increment_block);
    Reg step_reg;
    if (range_expr->step) {
        step_reg = emit_expr(*range_expr->step);
    } else {
        step_reg = allocate_register();
        auto int_type = std::make_shared<Type>(TypeTag::Int64);
        ValuePtr one_val = std::make_shared<Value>(int_type, (int64_t)1);
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, step_reg, one_val));
        set_register_type(step_reg, int_type);
    }
    Reg new_val_reg = allocate_register();
    emit_instruction(LIR_Inst(LIR_Op::Add, new_val_reg, loop_var_reg, step_reg));
    emit_instruction(LIR_Inst(LIR_Op::Mov, loop_var_reg, new_val_reg, 0));
    emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, header_block->id));
    add_block_edge(increment_block, header_block);

    set_current_block(exit_block);
    exit_loop();
    exit_scope();
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
        if (loop_stack_.back().start_label == 0) {
            loop_stack_.back().start_label = start_label;
        }
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
            it = blocks.erase(it);  // Remove unreachable block
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

std::shared_ptr<Type> Generator::convert_ast_type_to_lir_type(const std::shared_ptr<AST::TypeAnnotation>& ast_type) {
    if (!ast_type) {
        return nullptr;
    }
    
    // Convert AST type to LIR type
    if (ast_type->isPrimitive || ast_type->typeName == "int" || ast_type->typeName == "float" || 
        ast_type->typeName == "bool" || ast_type->typeName == "string" || ast_type->typeName == "void") {
        if (ast_type->typeName == "int") {
            return std::make_shared<Type>(TypeTag::Int);
        } else if (ast_type->typeName == "float") {
            return std::make_shared<Type>(TypeTag::Float32);
        } else if (ast_type->typeName == "bool") {
            return std::make_shared<Type>(TypeTag::Bool);
        } else if (ast_type->typeName == "string") {
            return std::make_shared<Type>(TypeTag::String);
        } else if (ast_type->typeName == "void") {
            return std::make_shared<Type>(TypeTag::Nil);
        }
    }
    
    // Default to Any type for complex or unknown types
    return std::make_shared<Type>(TypeTag::Any);
}

// Symbol collection methods (Pass 0)
void Generator::collect_function_signatures(AST::Program& program) {
    for (const auto& stmt : program.statements) {
        if (auto func_stmt = dynamic_cast<AST::FunctionDeclaration*>(stmt.get())) {
            collect_function_signature(*func_stmt);
        }
    }
}

void Generator::collect_function_signature(AST::FunctionDeclaration& stmt) {
    // Store function info in table - body will be lowered in Pass 1
    FunctionInfo info;
    info.name = stmt.name;
    info.param_count = stmt.params.size();
    info.optional_param_count = 0;
    info.has_closure = false;
    info.visibility = stmt.visibility;
    info.lir_function = nullptr;  // Will be created in Pass 1
    
    function_table_[stmt.name] = std::move(info);
}

void Generator::lower_function_bodies(AST::Program& program) {
    for (const auto& stmt : program.statements) {
        if (auto func_stmt = dynamic_cast<AST::FunctionDeclaration*>(stmt.get())) {
            lower_function_body(*func_stmt);
        }
    }
}

void Generator::lower_function_body(AST::FunctionDeclaration& stmt) {
    // Create separate LIR function for this function body
    auto func = std::make_unique<LIR_Function>(stmt.name, stmt.params.size());
    
    // Save current context
    auto saved_function = std::move(current_function_);
    auto saved_next_register = next_register_;
    auto saved_scope_stack = scope_stack_;
    auto saved_register_types = register_types_;
    
    // Set up function context
    current_function_ = std::move(func);
    next_register_ = stmt.params.size();  // Start after parameters
    scope_stack_.clear();
    register_types_.clear();
    
    // Enter function scope
    enter_scope();
    
    // Bind parameters to registers (no explicit param instructions needed)
    for (size_t i = 0; i < stmt.params.size(); ++i) {
        bind_variable(stmt.params[i].first, static_cast<Reg>(i));
        set_register_type(static_cast<Reg>(i), nullptr);
    }
    
    // Emit function body from AST
    if (stmt.body) {
        emit_stmt(*stmt.body);
    }
    
    // Ensure function has a return instruction
    if (current_function_->instructions.empty() || 
        !current_function_->instructions.back().isReturn()) {
        // Implicit return of 0 if no explicit return
        Reg return_reg = allocate_register();
        auto int_type = std::make_shared<Type>(TypeTag::Int64);
        ValuePtr zero_val = std::make_shared<Value>(int_type, int64_t(0));
        emit_instruction(LIR_Inst(LIR_Op::LoadConst, return_reg, zero_val));
        emit_instruction(LIR_Inst(LIR_Op::Ret, return_reg, 0, 0));
    }
    
    exit_scope();
    
    // Store the completed LIR function in the function table
    auto& func_info = function_table_[stmt.name];
    func_info.lir_function = std::move(current_function_);
    
    // Restore context
    current_function_ = std::move(saved_function);
    next_register_ = saved_next_register;
    scope_stack_ = std::move(saved_scope_stack);
    register_types_ = std::move(saved_register_types);
}

// Error and Result type expression handlers
Reg Generator::emit_error_construct_expr(AST::ErrorConstructExpr& expr) {
    Reg dst = allocate_register();
    
    // Create error value based on error type and arguments
    auto result_type = std::make_shared<Type>(TypeTag::ErrorUnion); // Generic Result type
    
    // For now, create a simple error value - in a full implementation,
    // this would use the errorType and arguments to create a proper error object
    auto error_val = std::make_shared<Value>(result_type, std::string("error"));
    
    set_register_type(dst, result_type);
    emit_instruction(LIR_Inst(LIR_Op::ConstructError, dst, error_val));
    return dst;
}

Reg Generator::emit_ok_construct_expr(AST::OkConstructExpr& expr) {
    Reg dst = allocate_register();
    
    // First evaluate the value to be wrapped
    Reg value_reg = emit_expr(*expr.value);
    
    // Create Result type wrapping the value
    auto result_type = std::make_shared<Type>(TypeTag::ErrorUnion);
    
    // For now, create a simple ok value - in a full implementation,
    // this would properly wrap the value from value_reg
    auto ok_val = std::make_shared<Value>(result_type, std::string("ok"));
    
    set_register_type(dst, result_type);
    emit_instruction(LIR_Inst(LIR_Op::ConstructOk, dst, ok_val));
    return dst;
}

Reg Generator::emit_fallible_expr(AST::FallibleExpr& expr) {
    // Evaluate the expression that may return a Result
    Reg result_reg = emit_expr(*expr.expression);
    
    // For the ? operator, we need to:
    // 1. Check if the result is an error using IsError
    // 2. If it's an error, jump to error handler or return early
    // 3. If it's ok, unwrap the value using Unwrap
    
    // Create a register to hold the error check result
    Reg is_error_reg = allocate_register();
    auto bool_type = std::make_shared<Type>(TypeTag::Bool);
    set_register_type(is_error_reg, bool_type);
    
    // Check if the result contains an error
    emit_instruction(LIR_Inst(LIR_Op::IsError, is_error_reg, result_reg, 0));
    
    // Create labels for error handling
    uint32_t error_label = generate_label();
    uint32_t continue_label = generate_label();
    
    // If it's an error, jump to error handling
    emit_instruction(LIR_Inst(LIR_Op::JumpIf, error_label, is_error_reg, 0));
    
    // If we get here, it's not an error, so unwrap the value
    Reg unwrapped_reg = allocate_register();
    set_register_type(unwrapped_reg, get_register_type(result_reg));
    emit_instruction(LIR_Inst(LIR_Op::Unwrap, unwrapped_reg, result_reg, 0));
    
    // Jump to continue label
    emit_instruction(LIR_Inst(LIR_Op::Jump, continue_label, 0, 0));
    
    // Error handling block
    emit_instruction(LIR_Inst(LIR_Op::Label, error_label, 0, 0));
    
    // For now, we'll just return the error result
    // In a full implementation, this would handle the elseHandler if present
    // or propagate the error up the call stack
    
    // Jump to continue label
    emit_instruction(LIR_Inst(LIR_Op::Jump, continue_label, 0, 0));
    
    // Continue label
    emit_instruction(LIR_Inst(LIR_Op::Label, continue_label, 0, 0));
    
    // Return the unwrapped value (or the error if it was an error)
    // For simplicity, we'll return the unwrapped_reg for now
    return unwrapped_reg;
}

// Class system implementations
void Generator::collect_class_signatures(AST::Program& program) {
    for (const auto& stmt : program.statements) {
        if (auto class_decl = dynamic_cast<AST::ClassDeclaration*>(stmt.get())) {
            collect_class_signature(*class_decl);
        }
    }
}

void Generator::collect_class_signature(AST::ClassDeclaration& class_decl) {
    ClassInfo class_info;
    class_info.name = class_decl.name;
    class_info.super_class_name = class_decl.superClassName;
    
    // Collect field information
    for (const auto& field : class_decl.fields) {
        TypePtr field_type = nullptr; // TODO: Convert from AST type annotation
        class_info.fields.push_back({field->name, field_type});
    }
    
    // Collect method information
    for (const auto& method : class_decl.methods) {
        class_info.method_names.push_back(method->name);
        class_info.method_indices[method->name] = class_info.method_names.size() - 1;
        
        // Register method in function table
        FunctionInfo func_info;
        func_info.name = class_decl.name + "." + method->name;
        func_info.param_count = method->params.size() + 1; // +1 for 'this'
        func_info.visibility = AST::VisibilityLevel::Public; // TODO: Get from method
        func_info.has_closure = false;
        function_table_[func_info.name] = std::move(func_info);
    }
    
    // Calculate field offsets and total size
    calculate_class_layout(class_info);
    
    // Store class information
    class_table_[class_decl.name] = class_info;
}

void Generator::calculate_class_layout(ClassInfo& class_info) {
    size_t offset = 0;
    
    // First field is V-Table pointer for classes with methods
    if (!class_info.method_names.empty()) {
        offset++; // Reserve space for V-Table pointer
    }
    
    // Calculate field offsets
    for (auto& field : class_info.fields) {
        class_info.field_offsets[field.first] = offset;
        offset++; // Simple layout - each field is one register slot
    }
    
    class_info.total_field_size = offset;
}

size_t Generator::get_field_offset(const std::string& class_name, const std::string& field_name) {
    auto it = class_table_.find(class_name);
    if (it == class_table_.end()) {
        report_error("Unknown class: " + class_name);
        return UINT32_MAX;
    }
    
    auto offset_it = it->second.field_offsets.find(field_name);
    if (offset_it == it->second.field_offsets.end()) {
        report_error("Unknown field '" + field_name + "' in class '" + class_name + "'");
        return UINT32_MAX;
    }
    
    return offset_it->second;
}

size_t Generator::get_method_index(const std::string& class_name, const std::string& method_name) {
    auto it = class_table_.find(class_name);
    if (it == class_table_.end()) {
        report_error("Unknown class: " + class_name);
        return UINT32_MAX;
    }
    
    auto index_it = it->second.method_indices.find(method_name);
    if (index_it == it->second.method_indices.end()) {
        report_error("Unknown method '" + method_name + "' in class '" + class_name + "'");
        return UINT32_MAX;
    }
    
    return index_it->second;
}

void Generator::emit_class_stmt(AST::ClassDeclaration& stmt) {
    // Class declarations are handled in Pass 0 (signature collection)
    // This function is called during Pass 2 but doesn't need to emit anything
    // since the class layout and methods are already registered
}

Reg Generator::emit_object_literal_expr(AST::ObjectLiteralExpr& expr) {
    Reg dst = allocate_register();
    
    // Create new object
    emit_instruction(LIR_Inst(LIR_Op::NewObject, dst, 0, 0));
    
    // Set each property
    size_t field_index = 0;
    for (const auto& [prop_name, prop_value] : expr.properties) {
        Reg value_reg = emit_expr(*prop_value);
        emit_instruction(LIR_Inst(LIR_Op::SetField, dst, field_index, value_reg));
        field_index++;
    }
    
    // Set object type (could be enhanced to track actual class type)
    auto obj_type = std::make_shared<Type>(TypeTag::UserDefined);
    set_register_type(dst, obj_type);
    
    return dst;
}

Reg Generator::emit_this_expr(AST::ThisExpr& expr) {
    if (this_register_ == UINT32_MAX) {
        report_error("'this' used outside of method context");
        return 0;
    }
    return this_register_;
}

// Smart module system implementations
void Generator::collect_module_signatures(AST::Program& program) {
    for (const auto& stmt : program.statements) {
        if (auto module_decl = dynamic_cast<AST::ModuleDeclaration*>(stmt.get())) {
            collect_module_declaration(*module_decl);
        }
    }
}

void Generator::collect_module_declaration(AST::ModuleDeclaration& module_decl) {
    std::string saved_module = current_module_;
    current_module_ = module_decl.name;
    
    // Process public members
    for (const auto& member : module_decl.publicMembers) {
        if (auto func_decl = dynamic_cast<AST::FunctionDeclaration*>(member.get())) {
            register_module_symbol(module_decl.name, func_decl->name, AST::VisibilityLevel::Public, 
                                true, func_decl->params.size());
        } else if (auto var_decl = dynamic_cast<AST::VarDeclaration*>(member.get())) {
            register_module_symbol(module_decl.name, var_decl->name, AST::VisibilityLevel::Public, false);
        }
    }
    
    // Process protected members
    for (const auto& member : module_decl.protectedMembers) {
        if (auto func_decl = dynamic_cast<AST::FunctionDeclaration*>(member.get())) {
            register_module_symbol(module_decl.name, func_decl->name, AST::VisibilityLevel::Protected, 
                                true, func_decl->params.size());
        } else if (auto var_decl = dynamic_cast<AST::VarDeclaration*>(member.get())) {
            register_module_symbol(module_decl.name, var_decl->name, AST::VisibilityLevel::Protected, false);
        }
    }
    
    // Process private members
    for (const auto& member : module_decl.privateMembers) {
        if (auto func_decl = dynamic_cast<AST::FunctionDeclaration*>(member.get())) {
            register_module_symbol(module_decl.name, func_decl->name, AST::VisibilityLevel::Private, 
                                true, func_decl->params.size());
        } else if (auto var_decl = dynamic_cast<AST::VarDeclaration*>(member.get())) {
            register_module_symbol(module_decl.name, var_decl->name, AST::VisibilityLevel::Private, false);
        }
    }
    
    current_module_ = saved_module;
}

void Generator::register_module_symbol(const std::string& module_name, const std::string& symbol_name, 
                                       AST::VisibilityLevel visibility, bool is_function, size_t param_count) {
    ModuleSymbolInfo symbol_info;
    symbol_info.qualified_name = module_name + "::" + symbol_name;
    symbol_info.module_name = module_name;
    symbol_info.symbol_name = symbol_name;
    symbol_info.visibility = visibility;
    symbol_info.is_function = is_function;
    symbol_info.is_variable = !is_function;
    symbol_info.param_count = param_count;
    
    module_symbol_table_[symbol_info.qualified_name] = symbol_info;
}

Generator::ModuleSymbolInfo* Generator::resolve_module_symbol(const std::string& qualified_name) {
    auto it = module_symbol_table_.find(qualified_name);
    if (it != module_symbol_table_.end()) {
        return &it->second;
    }
    return nullptr;
}

bool Generator::can_access_module_symbol(const ModuleSymbolInfo& symbol, const std::string& from_module) {
    // Public symbols are always accessible
    if (symbol.visibility == AST::VisibilityLevel::Public) {
        return true;
    }
    
    // Protected and private symbols are only accessible from the same module
    return from_module == symbol.module_name;
}

void Generator::emit_match_stmt(AST::MatchStatement& stmt) {
    // Evaluate the value to match
    Reg value_reg = emit_expr(*stmt.value);
    
    // Generate labels for match cases
    std::vector<uint32_t> case_labels;
    uint32_t end_label = generate_label();
    
    // Create labels for each case
    for (size_t i = 0; i < stmt.cases.size(); i++) {
        case_labels.push_back(generate_label());
    }
    
    // Generate match cases
    for (size_t i = 0; i < stmt.cases.size(); i++) {
        const auto& match_case = stmt.cases[i];
        
        // For simple literal patterns, emit comparison
        if (auto literal = dynamic_cast<AST::LiteralExpr*>(match_case.pattern.get())) {
            Reg pattern_reg = emit_expr(*literal);
            Reg compare_reg = allocate_register();
            
            // Compare value with pattern
            emit_instruction(LIR_Inst(LIR_Op::CmpEQ, compare_reg, value_reg, pattern_reg));
            
            // Jump to case if match, otherwise jump to next case
            uint32_t next_label = (i + 1 < stmt.cases.size()) ? case_labels[i + 1] : end_label;
            emit_instruction(LIR_Inst(LIR_Op::JumpIf, compare_reg, case_labels[i], 0));
            emit_instruction(LIR_Inst(LIR_Op::Jump, next_label, 0, 0));
        } else {
            // For complex patterns, just jump to next case for now
            uint32_t next_label = (i + 1 < stmt.cases.size()) ? case_labels[i + 1] : end_label;
            emit_instruction(LIR_Inst(LIR_Op::Jump, next_label, 0, 0));
        }
        
        // Emit case label
        emit_instruction(LIR_Inst(LIR_Op::Label, case_labels[i], 0, 0));
        
        // Emit case body
        if (match_case.body) {
            emit_stmt(*match_case.body);
        }
        
        // Jump to end after case body
        emit_instruction(LIR_Inst(LIR_Op::Jump, end_label, 0, 0));
    }
    
    // Emit end label
    emit_instruction(LIR_Inst(LIR_Op::Label, end_label, 0, 0));
}

void Generator::emit_module_stmt(AST::ModuleDeclaration& stmt) {
    // Module declarations are handled in Pass 0 (signature collection)
    // This function is called during Pass 2 but doesn't emit LIR
    // since modules are handled through the symbol resolution system
}

} // namespace LIR

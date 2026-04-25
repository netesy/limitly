#include "../generator.hh"
#include "../functions.hh"
#include "../../frontend/module_manager.hh"
#include "../function_registry.hh"
#include "../builtin_functions.hh"
#include "../../frontend/ast.hh"
#include "../../frontend/scanner.hh"
#include <algorithm>
#include <map>
#include <limits>

using namespace LM::LIR;

namespace LM {
namespace LIR {

// Static member initialization
bool Generator::optimization_enabled_ = true;
bool Generator::show_optimization_debug_ = false;
size_t Generator::lambda_counter_ = 0;

Generator::Generator() : current_function_(nullptr), next_register_(0), next_label_(0) {
    // Initialize LIR function system
    FunctionUtils::initializeFunctions();
}


std::unique_ptr<LIR_Function> Generator::generate_program(const LM::Frontend::TypeCheckResult& type_check_result) {
    try {
        // Set type system reference BEFORE Pass 0
        type_system_ = type_check_result.type_system;
        
        // PASS 0: Collect function, frame, and module signatures only
        collect_trait_signatures(*type_check_result.program);
        collect_frame_signatures(*type_check_result.program);
        collect_function_signatures(type_check_result);
        collect_module_signatures(*type_check_result.program);
        
        // PASS 1: Lower function bodies into separate LIR functions
        lower_function_bodies(type_check_result);
    
    // PASS 2: Generate main function with top-level code only
    current_module_ = "root";
    current_function_ = std::make_unique<LIR_Function>("__top_level_wrapper__", 0);
    next_register_ = 0;
    next_label_ = 0;
    scope_stack_.clear();
    loop_stack_.clear();
    register_types_.clear();
    register_abi_types_.clear();
    register_language_types_.clear();
    
    start_cfg_build();
    enter_scope();
    
    // 1. Module Initializations in Topological Order
    auto& manager = LM::Frontend::ModuleManager::getInstance();
    auto sorted_modules = manager.get_topological_order();
    
    for (const auto& module_path : sorted_modules) {
        // Skip root as it is the current program
        if (module_path == "root") continue;

        std::string init_func_name = module_path + ".__init__";
        if (LIRFunctionManager::getInstance().hasFunction(init_func_name) || function_table_.count(init_func_name)) {
            std::vector<Reg> empty_args;
            Reg dummy_res = allocate_register();
            emit_instruction(LIR_Inst(LIR_Op::Call, dummy_res, init_func_name, empty_args));
        }
    }

    // 2. Generate top-level statements
    for (const auto& stmt : type_check_result.program->statements) {
        if (!stmt) continue;
        if (auto func_stmt = dynamic_cast<LM::Frontend::AST::FunctionDeclaration*>(stmt.get())) {
            continue;
        }
        emit_stmt(*stmt);
    }
    
    // Call exit_scope BEFORE implicit return to ensure deinitializers are called
    exit_scope();
    current_module_ = "";

    // Add implicit return if none exists
    if (get_current_block() && !get_current_block()->has_terminator()) {
        // For main function, use halt instead of return for proper termination
        if (current_function_->name == "__top_level_wrapper__") {
            emit_instruction(LIR_Inst(LIR_Op::Ret, Type::Void, 0, 0, 0)); // Use Ret for main termination
        } else {
            emit_instruction(LIR_Inst(LIR_Op::Return, Type::Void, 0, 0, 0));
        }
    }

    // Finish CFG building for main
    finish_cfg_build();

    // Optimize the generated LIR (but NOT for top-level wrapper)
    if (current_function_->name != "__top_level_wrapper__") {
        Optimizer optimizer(*current_function_);
        optimizer.optimize();
    }

    // Collect metrics
    auto metrics = MetricsCollector::collect(*current_function_);
    if (type_check_result.program->statements.size() > 0) {
        // Only print metrics if there's actual code
        // metrics.print();
    }

    auto result = std::move(current_function_);
    current_function_ = nullptr;
    scope_stack_.clear();
    register_types_.clear();
    
    return result;
    } catch (const std::exception& e) {
        std::cerr << "ERROR in LIR generate_program: " << e.what() << "\n";
        return nullptr;
    } catch (...) {
        std::cerr << "ERROR: Unknown exception in LIR generate_program\n";
        return nullptr;
    }
}


void Generator::generate_function(LM::Frontend::AST::FunctionDeclaration& fn) {
    auto& func_manager = LIRFunctionManager::getInstance();
    
    // Save current function state to allow recursive calls (e.g. lambdas)
    auto saved_function = std::move(current_function_);
    uint32_t saved_next_reg = next_register_;
    uint32_t saved_next_label = next_label_;
    auto saved_scope_stack = std::move(scope_stack_);
    auto saved_loop_stack = std::move(loop_stack_);
    auto saved_reg_types = std::move(register_types_);
    auto saved_reg_abi_types = std::move(register_abi_types_);
    auto saved_reg_lang_types = std::move(register_language_types_);
    auto saved_cfg_context = cfg_context_;

    // Create function with parameters (including optional parameters)
    size_t total_params = fn.params.size() + fn.optionalParams.size();
    
    // Add hidden environment parameter if this is a closure
    bool is_closure = !current_lambda_captures_.empty();
    if (is_closure) {
        total_params++;
    }

    current_function_ = std::make_unique<LIR_Function>(fn.name, total_params);
    next_register_ = total_params;

    if (is_closure) {
        env_register_ = static_cast<Reg>(total_params - 1);
    } else {
        env_register_ = UINT32_MAX;
    }
    next_label_ = 0;
    scope_stack_.clear();
    loop_stack_.clear();
    register_types_.clear();
    
    start_cfg_build();
    enter_scope();
    
    // Register regular parameters
    for (size_t i = 0; i < fn.params.size(); ++i) {
        bind_variable(fn.params[i].first, static_cast<Reg>(i));
        set_register_type(static_cast<Reg>(i), nullptr);
    }
    
    // Register optional parameters
    for (size_t i = 0; i < fn.optionalParams.size(); ++i) {
        size_t reg_index = fn.params.size() + i;
        bind_variable(fn.optionalParams[i].first, static_cast<Reg>(reg_index));
        set_register_type(static_cast<Reg>(reg_index), nullptr);
    }
    
    // Emit function body
    if (fn.body) {
        emit_stmt(*fn.body);
    }
    
    // Call exit_scope BEFORE implicit return to ensure deinitializers are called
    exit_scope();

    // Add implicit return if none exists
    if (get_current_block() && !get_current_block()->has_terminator()) {
        emit_instruction(LIR_Inst(LIR_Op::Return));
    }
    
    finish_cfg_build();
    
    // Convert LIR_Function to LIRFunction and update the registration
    auto result = std::move(current_function_);
    current_function_ = nullptr;
    
    // Create proper LIRFunction from our LIR_Function
    std::vector<LIRParameter> params;
    for (const auto& param : fn.params) {
        LIRParameter lir_param;
        lir_param.name = param.first;
        lir_param.type = Type::I64;
        params.push_back(lir_param);
    }
    for (const auto& optional_param : fn.optionalParams) {
        LIRParameter lir_param;
        lir_param.name = optional_param.first;
        lir_param.type = Type::I64;
        params.push_back(lir_param);
    }
    
    Type return_abi_type = Type::I64;
    if (fn.returnType.has_value()) {
        auto lang_type = convert_ast_type_to_lir_type(fn.returnType.value());
        return_abi_type = language_type_to_abi_type(lang_type);
    }

    auto lir_func = std::make_shared<LIRFunction>(fn.name, params, return_abi_type, nullptr);
    lir_func->setInstructions(result->instructions);
    
    // Optimize the generated LIR for this function
    if (Generator::is_optimization_enabled()) {
        Optimizer optimizer(*result);
        optimizer.optimize();
        lir_func->setInstructions(result->instructions);
    }

    // Register with manager AFTER instructions and optimization are complete
    func_manager.registerFunction(lir_func);

    // Restore previous state
    current_function_ = std::move(saved_function);
    next_register_ = saved_next_reg;
    next_label_ = saved_next_label;
    scope_stack_ = std::move(saved_scope_stack);
    loop_stack_ = std::move(saved_loop_stack);
    register_types_ = std::move(saved_reg_types);
    register_abi_types_ = std::move(saved_reg_abi_types);
    register_language_types_ = std::move(saved_reg_lang_types);
    cfg_context_ = saved_cfg_context;
}


Reg Generator::allocate_register() {
    return next_register_++;
}


void Generator::enter_scope() {
    scope_stack_.push_back({});
}


void Generator::exit_scope() {
    if (!scope_stack_.empty()) {
        // Emit deinit calls for all frame instances in this scope (in reverse order)
        const auto& scope = scope_stack_.back();
        for (auto it = scope.frame_instances.rbegin(); it != scope.frame_instances.rend(); ++it) {
            const auto& [frame_name, frame_reg] = *it;

            // Generate FrameCallDeinit instruction
            LIR_Inst deinit_inst(LIR_Op::FrameCallDeinit, Type::Void, frame_reg, 0, 0);
            deinit_inst.comment = "Auto-deinit for " + frame_name;
            emit_instruction(deinit_inst);
        }

        scope_stack_.pop_back();
    }
}


void Generator::bind_variable(const std::string& name, Reg reg) {
    //// std::cout << "[DEBUG] Binding variable '" << name << "' to register " << reg << std::endl;
    if (scope_stack_.empty()) {
        //// std::cout << "[DEBUG] Creating new scope for variable binding" << std::endl;
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
   // std::cout << "[DEBUG] Resolving variable '" << name << "' in " << scope_stack_.size() << " scopes" << std::endl;
    for (auto it = scope_stack_.rbegin(); it != scope_stack_.rend(); ++it) {
        auto found = it->vars.find(name);
        if (found != it->vars.end()) {
           // std::cout << "[DEBUG] Found variable '" << name << "' -> register " << found->second << std::endl;
            return found->second;
        }
    }
   // std::cout << "[DEBUG] Variable '" << name << "' not found" << std::endl;
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

// New simplified type methods

void Generator::set_register_abi_type(Reg reg, Type abi_type) {
    register_abi_types_[reg] = abi_type;
    if (current_function_) {
        current_function_->set_register_abi_type(reg, abi_type);
    }
}


void Generator::set_register_language_type(Reg reg, TypePtr lang_type) {
    register_language_types_[reg] = lang_type;
    if (current_function_) {
        current_function_->set_register_language_type(reg, lang_type);
    }
    
    // Also set the ABI type
    if (lang_type && type_system_) {
        Type abi_type = language_type_to_abi_type(lang_type);
        set_register_abi_type(reg, abi_type);
    }
}


Type Generator::get_register_abi_type(Reg reg) const {
    auto it = register_abi_types_.find(reg);
    if (it != register_abi_types_.end()) {
        return it->second;
    }
    return Type::Void;
}


TypePtr Generator::get_register_language_type(Reg reg) const {
    auto it = register_language_types_.find(reg);
    if (it != register_language_types_.end()) {
        return it->second;
    }
    return nullptr;
}


Type Generator::language_type_to_abi_type(TypePtr lang_type) {
    if (!type_system_ || !lang_type) return Type::Void;
    return LIR::language_type_to_abi_type(lang_type);
}


Type Generator::get_expression_abi_type(LM::Frontend::AST::Expression& expr) {
    if (expr.inferred_type && type_system_) {
        return language_type_to_abi_type(expr.inferred_type);
    }
    return Type::Void;
}


void Generator::emit_typed_instruction(const LIR_Inst& inst) {
    // Set the ABI type for the destination register if not already set
    if (inst.dst != UINT32_MAX && inst.result_type != Type::Void) {
        set_register_abi_type(inst.dst, inst.result_type);
    }
    
    // Emit the instruction
    emit_instruction(inst);
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
        if (type->tag == ::TypeTag::Int) {
            return std::make_shared<Value>(type, static_cast<int64_t>(0));
        } else if (type->tag == ::TypeTag::Float32) {
            return std::make_shared<Value>(type, 0.0);
        } else if (type->tag == ::TypeTag::Bool) {
            return std::make_shared<Value>(type, false);
        } else if (type->tag == ::TypeTag::String) {
            return std::make_shared<Value>(type, std::string(""));
        }
    }
    
    // Fallback: return an int value
    auto int_type = std::make_shared<::Type>(::TypeTag::Int);
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
                // Use the ABI type conversion instead of legacy method
                Type abi_type = language_type_to_abi_type(type);
                current_function_->set_register_abi_type(inst.dst, abi_type);
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

void Generator::cleanup_memory() {
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


void Generator::ensure_all_blocks_terminated() {
    if (!current_function_ || !current_function_->cfg) {
        return;
    }
    
    // Ensure all blocks have proper terminators
    for (const auto& block : current_function_->cfg->blocks) {
        if (!block) continue;
        
        // Check if block has a terminator
        if (!block->has_terminator()) {
            // Only add terminator if the block is not the exit block
            if (cfg_context_.exit_block && block.get() != cfg_context_.exit_block) {
                // Temporarily set this block as current to emit instruction
                auto saved_current = cfg_context_.current_block;
                cfg_context_.current_block = block.get();
                
                emit_instruction(LIR_Inst(LIR_Op::Jump, 0, 0, 0, cfg_context_.exit_block->id));
                add_block_edge(block.get(), cfg_context_.exit_block);
                
                // Restore current block
                cfg_context_.current_block = saved_current;
            } else if (block.get() == cfg_context_.exit_block) {
                // Exit block should have a return statement
                auto saved_current = cfg_context_.current_block;
                cfg_context_.current_block = block.get();
                
                emit_instruction(LIR_Inst(LIR_Op::Ret, 0, 0, 0));
                
                // Restore current block
                cfg_context_.current_block = saved_current;
            }
        }
    }
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
    for (auto& block : blocks) {
        if (block && reachable_blocks.find(block->id) == reachable_blocks.end()) {
            block.reset();  // Set to nullptr to maintain index consistency
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
    
    // Use DFS to find a linearization (Reverse Post-Order is best)
    std::vector<LIR_BasicBlock*> sorted_blocks;
    std::unordered_set<uint32_t> visited;
    
    std::function<void(uint32_t)> visit = [&](uint32_t block_id) {
        if (visited.count(block_id)) return;
        visited.insert(block_id);
        
        auto block = current_function_->cfg->get_block(block_id);
        if (!block) return;
        
        // Visit successors (in reverse order often helps with linear layout)
        for (auto it = block->successors.rbegin(); it != block->successors.rend(); ++it) {
            visit(*it);
        }
        
        sorted_blocks.push_back(block);
    };

    if (current_function_->cfg->entry_block_id != UINT32_MAX) {
        visit(current_function_->cfg->entry_block_id);
    }
    
    // Reverse to get topological/linear order
    std::reverse(sorted_blocks.begin(), sorted_blocks.end());
    
    // Safety check: ensure ALL blocks are present if they are referenced anywhere
    std::unordered_set<uint32_t> referenced_blocks;
    for (const auto& block : current_function_->cfg->blocks) {
        if (!block) continue;
        for (const auto& inst : block->instructions) {
            if (inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) {
                referenced_blocks.insert(inst.imm);
            }
        }
    }

    for (uint32_t ref_id : referenced_blocks) {
        if (visited.find(ref_id) == visited.end()) {
            auto block = current_function_->cfg->get_block(ref_id);
            if (block) {
                // If a referenced block was missed (e.g. by jump optimization), force it in
                visit(ref_id);
            }
        }
    }

    // Reachable blocks only are in sorted_blocks at this point.
    // We intentionally don't add remaining blocks as they are unreachable.
    
    // Calculate positions for each block
    size_t current_pos = 0;
    for (const auto* block : sorted_blocks) {
        block_positions[block->id] = current_pos;
        current_pos += block->instructions.size();
    }
    
    // Second pass: emit instructions with proper label targets
    for (const auto* block : sorted_blocks) {
        // Emit all instructions in this block
        for (const auto& inst : block->instructions) {
            LIR_Inst modified_inst = inst;
            
            // Update jump targets to use instruction positions as labels
            if (inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) {
                auto it = block_positions.find(inst.imm);
                if (it != block_positions.end()) {
                    modified_inst.imm = it->second; // Use instruction position as label
                } else {
                    // Block not found - this might be an error
                    std::cerr << "Warning: Jump target block " << inst.imm << " not found in block_positions" << std::endl;
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


bool Generator::validate_cfg() {
    if (!current_function_ || !current_function_->cfg) {
        report_error("CFG validation: No CFG to validate");
        return false;
    }
    
    bool is_valid = true;
    
    // Check 1: Entry block exists and is reachable
    if (current_function_->cfg->entry_block_id == UINT32_MAX) {
        report_error("CFG validation: No entry block defined");
        is_valid = false;
    } else {
        auto entry_block = current_function_->cfg->get_block(current_function_->cfg->entry_block_id);
        if (!entry_block) {
            report_error("CFG validation: Entry block not found");
            is_valid = false;
        }
    }
    
    // Check 2: All blocks have proper terminators or valid successors
    for (const auto& block : current_function_->cfg->blocks) {
        if (!block) continue;
        
        bool has_terminator = block->has_terminator();
        bool has_successors = !block->successors.empty();
        
        // A block must either have a terminator (return/jump) or successors
        // Exception: success_unwrap blocks in error propagation can continue without terminators
        // Exception: entry blocks in simple functions can fall through without explicit terminators
        // Exception: continuation blocks (fallible_continue, if_end, etc.) can continue without terminators
        if (!has_terminator && !has_successors && !block->is_exit) {
            // Allow success_unwrap blocks to not have terminators (they continue execution)
            if (block->label.find("success_unwrap") == std::string::npos &&
                // Allow entry blocks in simple functions to fall through
                !(block->is_entry && current_function_->cfg->blocks.size() <= 2) &&
                // Allow continuation blocks to not have terminators
                block->label.find("_continue") == std::string::npos &&
                block->label.find("_end") == std::string::npos) {
                report_error("CFG validation: Block " + std::to_string(block->id) + 
                            " (" + block->label + ") has no terminator and no successors");
                is_valid = false;
            }
        }
        
        // Check that all successor blocks exist
        for (uint32_t successor_id : block->successors) {
            auto successor_block = current_function_->cfg->get_block(successor_id);
            if (!successor_block) {
                report_error("CFG validation: Block " + std::to_string(block->id) + 
                            " references non-existent successor " + std::to_string(successor_id));
                is_valid = false;
            }
        }
        
        // Check that predecessor/successor relationships are symmetric
        for (uint32_t successor_id : block->successors) {
            auto successor_block = current_function_->cfg->get_block(successor_id);
            if (successor_block) {
                bool found_back_edge = false;
                for (uint32_t pred_id : successor_block->predecessors) {
                    if (pred_id == block->id) {
                        found_back_edge = true;
                        break;
                    }
                }
                if (!found_back_edge) {
                    report_error("CFG validation: Asymmetric edge from block " + 
                                std::to_string(block->id) + " to " + std::to_string(successor_id));
                    is_valid = false;
                }
            }
        }
    }
    
    // Check 3: Error propagation blocks must terminate with return
    for (const auto& block : current_function_->cfg->blocks) {
        if (!block) continue;
        
        if (block->label.find("error_propagation") != std::string::npos) {
            if (!block->has_terminator()) {
                report_error("CFG validation: Error propagation block " + std::to_string(block->id) + 
                            " must terminate with return");
                is_valid = false;
            } else {
                // Check that the last instruction is a return
                if (!block->instructions.empty()) {
                    const auto& last_inst = block->instructions.back();
                    if (last_inst.op != LIR_Op::Return && last_inst.op != LIR_Op::Ret) {
                        report_error("CFG validation: Error propagation block " + std::to_string(block->id) + 
                                    " must end with return instruction");
                        is_valid = false;
                    }
                }
            }
        }
    }
    
    // Check 4: Main function must have proper termination after unwrap
    if (current_function_->name == "main") {
        // Look for unwrap instructions followed by proper termination
        for (const auto& block : current_function_->cfg->blocks) {
            if (!block) continue;
            
            for (size_t i = 0; i < block->instructions.size(); ++i) {
                const auto& inst = block->instructions[i];
                if (inst.op == LIR_Op::Unwrap) {
                    // After unwrap, we should either:
                    // 1. Have a return/halt in the same block
                    // 2. Have successors that lead to proper termination
                    bool has_proper_termination = false;
                    
                    // Check remaining instructions in this block
                    for (size_t j = i + 1; j < block->instructions.size(); ++j) {
                        const auto& next_inst = block->instructions[j];
                        if (next_inst.op == LIR_Op::Return || next_inst.op == LIR_Op::Ret) {
                            has_proper_termination = true;
                            break;
                        }
                    }
                    
                    // If no termination in this block, check if block has terminator
                    if (!has_proper_termination && block->has_terminator()) {
                        has_proper_termination = true;
                    }
                    
                    if (!has_proper_termination) {
                        report_error("CFG validation: Main function unwrap at block " + 
                                    std::to_string(block->id) + " must be followed by proper termination");
                        is_valid = false;
                    }
                }
            }
        }
    }
    
    return is_valid;
}


std::shared_ptr<::Type> Generator::convert_ast_type_to_lir_type(const std::shared_ptr<LM::Frontend::AST::TypeAnnotation>& ast_type) {
    if (!ast_type) {
        return nullptr;
    }
    
    // Convert AST type to LIR type
    std::string typeName = ast_type->typeName;
    if (ast_type->isPrimitive || typeName == "int" || typeName == "uint" ||
        typeName == "float" || typeName == "bool" || typeName == "str" ||
        typeName == "string" || typeName == "void") {

        if (typeName == "int" || typeName == "i64") {
            return std::make_shared<::Type>(::TypeTag::Int64);
        } else if (typeName == "uint" || typeName == "u64") {
            return std::make_shared<::Type>(::TypeTag::UInt64);
        } else if (typeName == "float" || typeName == "f64") {
            return std::make_shared<::Type>(::TypeTag::Float64);
        } else if (typeName == "bool") {
            return std::make_shared<::Type>(::TypeTag::Bool);
        } else if (typeName == "str" || typeName == "string") {
            return std::make_shared<::Type>(::TypeTag::String);
        } else if (typeName == "void") {
            return std::make_shared<::Type>(::TypeTag::Nil);
        }
    }
    
    // Check if it's a frame type
    if (frame_table_.find(typeName) != frame_table_.end()) {
        auto type = std::make_shared<::Type>(::TypeTag::Frame);
        FrameType ft;
        ft.name = typeName;
        type->extra = ft;
        return type;
    }

    // Default to Any type for complex or unknown types
    return std::make_shared<::Type>(::TypeTag::Any);
}

// Symbol collection methods (Pass 0)

bool Generator::is_visible(LM::Frontend::AST::VisibilityLevel level, const std::string& frame_name) {
    if (level == LM::Frontend::AST::VisibilityLevel::Public) return true;

    // If current_function_ is null, we are in top-level code (main function)
    // Only public members are visible here
    if (!current_function_) {
        return level == LM::Frontend::AST::VisibilityLevel::Public;
    }

    // Check if we are inside a method of the same frame
    if (current_function_->name.find(frame_name + ".") == 0) {
        return true;
    }

    // Check for init and deinit methods too
    if (current_function_->name == frame_name + ".init" ||
        current_function_->name == frame_name + ".deinit") {
        return true;
    }

    // Handle inheritance (Protected) when implemented
    if (level == LM::Frontend::AST::VisibilityLevel::Protected) {
        auto* target_info = type_system_->getFrameInfo(frame_name);
        if (target_info) {
            for (const auto& trait : target_info->implements) {
                // If current frame context is also a method of a frame implementing same trait
                // We need to extract current frame name from current_function_->name
                auto dot_pos = current_function_->name.find(".");
                if (dot_pos != std::string::npos) {
                    std::string current_frame_name = current_function_->name.substr(0, dot_pos);
                    auto* current_info = type_system_->getFrameInfo(current_frame_name);
                    if (current_info) {
                        for (const auto& ctrait : current_info->implements) {
                            if (trait == ctrait) return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

// Channel operation implementations

} // namespace LIR
} // namespace LM

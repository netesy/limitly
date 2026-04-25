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

void Generator::collect_function_signatures(const LM::Frontend::TypeCheckResult& type_check_result) {
    
    for (const auto& stmt : type_check_result.program->statements) {
        if (auto func_stmt = dynamic_cast<LM::Frontend::AST::FunctionDeclaration*>(stmt.get())) {
            collect_function_signature(*func_stmt);
        }
    }
    
    // Also collect signatures from imported symbols
    for (const auto& [qualified_name, stmt] : type_check_result.program->imported_symbols) {
        if (auto func_decl = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(stmt)) {
            collect_function_signature(*func_decl, qualified_name);
        }
    }
    
}


void Generator::collect_function_signature(LM::Frontend::AST::FunctionDeclaration& stmt, const std::string& name_override) {
    // Store function info in table - body will be lowered in Pass 1
    FunctionInfo info;
    info.name = name_override.empty() ? stmt.name : name_override;
    info.param_count = stmt.params.size();
    info.optional_param_count = 0;
    info.has_closure = false;
    info.visibility = stmt.visibility;
    info.lir_function = nullptr;  // Will be created in Pass 1
    
    function_table_[info.name] = std::move(info);
}


void Generator::lower_function_bodies(const LM::Frontend::TypeCheckResult& type_check_result) {
    auto& manager = LM::Frontend::ModuleManager::getInstance();
    
    // Lower root program symbols
    if (type_check_result.program && type_check_result.program->statements.size() > 0) {
        for (const auto& stmt : type_check_result.program->statements) {
            if (!stmt) continue;
            if (auto func_stmt = dynamic_cast<LM::Frontend::AST::FunctionDeclaration*>(stmt.get())) {
                 lower_function_body(*func_stmt);
            } else if (auto trait_stmt = dynamic_cast<LM::Frontend::AST::TraitDeclaration*>(stmt.get())) {
                lower_trait_declaration(*trait_stmt);
            } else if (auto frame_stmt = dynamic_cast<LM::Frontend::AST::FrameDeclaration*>(stmt.get())) {
                lower_frame_methods(*frame_stmt);
            }
        }
    }

    // Lower all module symbols and generate .__init__ functions
    auto modules = manager.get_all_modules();
    for (const auto& [path, module] : modules) {
        if (path == "root" || !module || !module->ast) continue;

        std::string prev_mod = current_module_;
        current_module_ = path;

        // 1. Lower module symbols
        for (const auto& stmt : module->ast->statements) {
            if (auto func_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::FunctionDeclaration>(stmt)) {
                std::string original_name = func_stmt->name;
                func_stmt->name = path + "." + original_name;
                generate_function(*func_stmt);
                func_stmt->name = original_name;
            } else if (auto frame_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) {
                std::string original_name = frame_stmt->name;
                frame_stmt->name = path + "." + original_name;
                lower_frame_methods(*frame_stmt);
                frame_stmt->name = original_name;
            } else if (auto trait_stmt = std::dynamic_pointer_cast<LM::Frontend::AST::TraitDeclaration>(stmt)) {
                std::string original_name = trait_stmt->name;
                trait_stmt->name = path + "." + original_name;
                lower_trait_declaration(*trait_stmt);
                trait_stmt->name = original_name;
            }
        }

        // 2. Generate .__init__ function for this module
        std::string init_func_name = path + ".__init__";
        current_function_ = std::make_unique<LIR_Function>(init_func_name, 0);
        next_register_ = 0;
        scope_stack_.clear();
        enter_scope();

        for (const auto& stmt : module->ast->statements) {
            if (dynamic_cast<LM::Frontend::AST::FunctionDeclaration*>(stmt.get()) ||
                dynamic_cast<LM::Frontend::AST::FrameDeclaration*>(stmt.get()) ||
                dynamic_cast<LM::Frontend::AST::TraitDeclaration*>(stmt.get())) {
                continue;
            }
            emit_stmt(*stmt);
        }

        if (current_function_->instructions.empty() || !current_function_->instructions.back().isReturn()) {
            emit_instruction(LIR_Inst(LIR_Op::Return, Type::Void, 0, 0, 0));
        }

        auto result = std::move(current_function_);
        current_function_ = nullptr;

        // Register with LIRFunctionManager to ensure it's found during Call execution
        std::vector<LIRParameter> params;
        auto lir_func = LIRFunctionManager::getInstance().createFunction(init_func_name, params, Type::Void, nullptr);
        lir_func->setInstructions(result->instructions);

        current_module_ = prev_mod;
    }

    // Bodies from imported symbols are already lowered in the module loop above.

    lower_task_bodies_recursive(type_check_result.program->statements);
}


void Generator::lower_task_bodies_recursive(const std::vector<std::shared_ptr<LM::Frontend::AST::Statement>>& statements) {
    for (const auto& stmt : statements) {
        if (!stmt) continue;

        if (auto concurrent_stmt = dynamic_cast<LM::Frontend::AST::ConcurrentStatement*>(stmt.get())) {
            if (concurrent_stmt->body) {
                lower_task_bodies_recursive(concurrent_stmt->body->statements);
            }
        } else if (auto parallel_stmt = dynamic_cast<LM::Frontend::AST::ParallelStatement*>(stmt.get())) {
            if (parallel_stmt->body) {
                lower_task_bodies_recursive(parallel_stmt->body->statements);
            }
        } else if (auto task_stmt = dynamic_cast<LM::Frontend::AST::TaskStatement*>(stmt.get())) {
            lower_task_body(*task_stmt);
            if (task_stmt->body) {
                lower_task_bodies_recursive(task_stmt->body->statements);
            }
        } else if (auto worker_stmt = dynamic_cast<LM::Frontend::AST::WorkerStatement*>(stmt.get())) {
            lower_worker_body(*worker_stmt);
            if (worker_stmt->body) {
                lower_task_bodies_recursive(worker_stmt->body->statements);
            }
        } else if (auto block_stmt = dynamic_cast<LM::Frontend::AST::BlockStatement*>(stmt.get())) {
            lower_task_bodies_recursive(block_stmt->statements);
        } else if (auto iter_stmt = dynamic_cast<LM::Frontend::AST::IterStatement*>(stmt.get())) {
            if (iter_stmt->body) {
                 std::vector<std::shared_ptr<LM::Frontend::AST::Statement>> stmts = {iter_stmt->body};
                 lower_task_bodies_recursive(stmts);
            }
        } else if (auto for_stmt = dynamic_cast<LM::Frontend::AST::ForStatement*>(stmt.get())) {
            if (for_stmt->body) {
                 std::vector<std::shared_ptr<LM::Frontend::AST::Statement>> stmts = {for_stmt->body};
                 lower_task_bodies_recursive(stmts);
            }
        } else if (auto while_stmt = dynamic_cast<LM::Frontend::AST::WhileStatement*>(stmt.get())) {
            if (while_stmt->body) {
                 std::vector<std::shared_ptr<LM::Frontend::AST::Statement>> stmts = {while_stmt->body};
                 lower_task_bodies_recursive(stmts);
            }
        } else if (auto if_stmt = dynamic_cast<LM::Frontend::AST::IfStatement*>(stmt.get())) {
            if (if_stmt->thenBranch) {
                 std::vector<std::shared_ptr<LM::Frontend::AST::Statement>> stmts = {if_stmt->thenBranch};
                 lower_task_bodies_recursive(stmts);
            }
            if (if_stmt->elseBranch) {
                 std::vector<std::shared_ptr<LM::Frontend::AST::Statement>> stmts = {if_stmt->elseBranch};
                 lower_task_bodies_recursive(stmts);
            }
        } else if (auto match_stmt = dynamic_cast<LM::Frontend::AST::MatchStatement*>(stmt.get())) {
            for (auto& match_case : match_stmt->cases) {
                if (match_case.body) {
                    std::vector<std::shared_ptr<LM::Frontend::AST::Statement>> stmts = {match_case.body};
                    lower_task_bodies_recursive(stmts);
                }
            }
        }
    }
}


void Generator::lower_function_body(LM::Frontend::AST::FunctionDeclaration& stmt) {
    // Use generate_function to create and register the function properly
    generate_function(stmt);
    
    // The function is now registered with FunctionRegistry
    // Store a reference in the function table for later use
    auto& func_info = function_table_[stmt.name];
    func_info.lir_function = nullptr; // Not needed since FunctionRegistry manages it
}


void Generator::collect_frame_signatures(LM::Frontend::AST::Program& program) {
    
    for (const auto& stmt : program.statements) {
        if (auto frame_decl = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) {
            collect_frame_signature(frame_decl);
        }
    }

    // Also collect signatures from imported symbols
    for (const auto& [qualified_name, stmt] : program.imported_symbols) {
        if (auto frame_decl = std::dynamic_pointer_cast<LM::Frontend::AST::FrameDeclaration>(stmt)) {
            collect_frame_signature(frame_decl, qualified_name);
        }
    }
}


void Generator::collect_frame_signature(std::shared_ptr<LM::Frontend::AST::FrameDeclaration> frame_decl, const std::string& name_override) {
    if (!frame_decl) return;

    std::string frame_name = name_override.empty() ? frame_decl->name : name_override;

    FrameInfo frame_info;
    frame_info.declaration = frame_decl;
    frame_info.name = frame_name;
    frame_info.implements = frame_decl->implements;
    frame_info.has_init = (frame_decl->init != nullptr);
    frame_info.has_deinit = (frame_decl->deinit != nullptr);
    
    // Collect field information
    for (const auto& field : frame_decl->fields) {
        TypePtr field_type = nullptr;
        // Convert AST type annotation to TypePtr if available
        if (field->type) {
            field_type = convert_ast_type_to_lir_type(field->type);
        } else {
            // Default to Any if no type annotation
            field_type = std::make_shared<::Type>(::TypeTag::Any);
        }
        frame_info.fields.push_back({field->name, field_type});
        frame_info.field_visibilities[field->name] = field->visibility;
    }
    
    // Collect method information
    for (const auto& method : frame_decl->methods) {
        frame_info.method_names.push_back(method->name);
        frame_info.method_indices[method->name] = frame_info.method_names.size() - 1;
        
        // Register method in function table
        FunctionInfo func_info;
        func_info.name = frame_name + "." + method->name;
        func_info.param_count = method->parameters.size() + 1; // +1 for 'this'
        func_info.visibility = method->visibility;
        func_info.has_closure = false;
        function_table_[func_info.name] = std::move(func_info);
    }
    
    // Register init method if present
    if (frame_decl->init) {
        FunctionInfo init_info;
        init_info.name = frame_name + ".init";
        init_info.param_count = frame_decl->init->parameters.size() + 1; // +1 for 'this'
        init_info.visibility = frame_decl->init->visibility;
        init_info.has_closure = false;
        function_table_[init_info.name] = std::move(init_info);
    }
    
    // Register deinit method if present
    if (frame_decl->deinit) {
        FunctionInfo deinit_info;
        deinit_info.name = frame_name + ".deinit";
        deinit_info.param_count = 1; // Only 'this'
        deinit_info.visibility = frame_decl->deinit->visibility;
        deinit_info.has_closure = false;
        function_table_[deinit_info.name] = std::move(deinit_info);
    }
    
    // Calculate field offsets and total size
    calculate_frame_layout(frame_info);
    
    // Store frame information
    frame_table_[frame_name] = frame_info;
}


void Generator::calculate_frame_layout(FrameInfo& frame_info) {
    size_t offset = 0;
    
    // Calculate field offsets
    for (auto& field : frame_info.fields) {
        frame_info.field_offsets[field.first] = offset;
        offset++; // Simple layout - each field is one register slot
    }
    
    frame_info.total_field_size = offset;
}


size_t Generator::get_frame_field_offset(const std::string& frame_name, const std::string& field_name) {
    auto it = frame_table_.find(frame_name);
    if (it == frame_table_.end()) {
        report_error("Unknown frame: " + frame_name);
        return UINT32_MAX;
    }
    
    auto offset_it = it->second.field_offsets.find(field_name);
    if (offset_it == it->second.field_offsets.end()) {
        report_error("Unknown field '" + field_name + "' in frame '" + frame_name + "'");
        return UINT32_MAX;
    }
    
    return offset_it->second;
}


size_t Generator::get_frame_method_index(const std::string& frame_name, const std::string& method_name) {
    auto it = frame_table_.find(frame_name);
    if (it == frame_table_.end()) {
        report_error("Unknown frame: " + frame_name);
        return UINT32_MAX;
    }
    
    auto index_it = it->second.method_indices.find(method_name);
    if (index_it == it->second.method_indices.end()) {
        report_error("Unknown method '" + method_name + "' in frame '" + frame_name + "'");
        return UINT32_MAX;
    }
    
    return index_it->second;
}


void Generator::collect_trait_signatures(LM::Frontend::AST::Program& program) {
    for (const auto& stmt : program.statements) {
        if (auto trait_decl = std::dynamic_pointer_cast<LM::Frontend::AST::TraitDeclaration>(stmt)) {
            collect_trait_signature(trait_decl);
        }
    }

    // Also collect signatures from imported symbols
    for (const auto& [qualified_name, stmt] : program.imported_symbols) {
        if (auto trait_decl = std::dynamic_pointer_cast<LM::Frontend::AST::TraitDeclaration>(stmt)) {
            collect_trait_signature(trait_decl, qualified_name);
        }
    }
}


void Generator::collect_trait_signature(std::shared_ptr<LM::Frontend::AST::TraitDeclaration> trait_decl, const std::string& name_override) {
    if (!trait_decl) return;

    std::string trait_name = name_override.empty() ? trait_decl->name : name_override;

    TraitInfo info;
    info.name = trait_name;
    info.extends = trait_decl->extends;
    info.declaration = trait_decl;
    trait_table_[trait_name] = info;

    // Register methods in function table
    for (const auto& method : trait_decl->methods) {
        // Only register if it has a body (default implementation)
        if (method->body && !method->body->statements.empty()) {
            FunctionInfo func_info;
            func_info.name = trait_decl->name + "." + method->name;
            func_info.param_count = method->params.size() + 1; // +1 for 'this'
            func_info.visibility = LM::Frontend::AST::VisibilityLevel::Public;
            func_info.has_closure = false;
            function_table_[func_info.name] = std::move(func_info);
        }
    }
}


} // namespace LIR
} // namespace LM

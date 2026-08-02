#include "../type_checker.hh"
#include "../../error/debugger.hh"
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

using namespace LM::Frontend;

namespace LM {
namespace Frontend {

// Initialize static members
std::unordered_set<std::string> TypeChecker::failed_modules;
std::unordered_set<std::string> TypeChecker::failed_frames;

int TypeChecker::levenshtein_distance(const std::string& s1, const std::string& s2) {
    int m = s1.length();
    int n = s2.length();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int j = 0; j <= n; ++j) dp[0][j] = j;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (std::tolower(s1[i - 1]) == std::tolower(s2[j - 1])) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }
    return dp[m][n];
}

std::string TypeChecker::find_similar_name(const std::string& name, const std::vector<std::string>& candidates) {
    if (candidates.empty() || name.empty()) return "";
    int best_dist = 999;
    std::string best_cand = "";
    for (const auto& cand : candidates) {
        if (cand == name) continue;
        int dist = levenshtein_distance(name, cand);
        if (dist < best_dist) {
            best_dist = dist;
            best_cand = cand;
        }
    }

    int max_allowed_dist = 2;
    if (name.length() > 6 && name.length() <= 10) max_allowed_dist = 3;
    else if (name.length() > 10) max_allowed_dist = 4;

    if (best_dist <= max_allowed_dist) {
        return best_cand;
    }
    return "";
}

std::vector<std::string> TypeChecker::get_all_available_modules() {
    std::vector<std::string> modules = {
        "std.algorithm", "std.collections", "std.config", "std.core", "std.crypto",
        "std.csv", "std.encoding", "std.env", "std.format", "std.fs", "std.graphics",
        "std.html", "std.http", "std.io", "std.iterator", "std.json", "std.math",
        "std.mime", "std.net", "std.parse", "std.process", "std.random", "std.regex",
        "std.scene", "std.string", "std.time", "std.toml", "std.ui", "std.unicode",
        "std.url", "std.uuid", "std.validation", "std.wss", "std.xml", "std.yaml",
        "std.regex.index", "std.string.builder", "std.path", "std.path.index", "std.time.index",
        "std.format.index", "std.random.index"
    };
    try {
        if (fs::exists("std") && fs::is_directory("std")) {
            for (const auto& entry : fs::recursive_directory_iterator("std")) {
                if (entry.is_regular_file() && entry.path().extension() == ".lm") {
                    std::string p = entry.path().string();
                    std::replace(p.begin(), p.end(), '/', '.');
                    std::replace(p.begin(), p.end(), '\\', '.');
                    if (p.ends_with(".lm")) {
                        p = p.substr(0, p.length() - 3);
                    }
                    modules.push_back(p);

                    size_t last_dot = p.find_last_of('.');
                    if (last_dot != std::string::npos) {
                        modules.push_back(p.substr(0, last_dot));
                    }
                }
            }
        }
    } catch (...) {}

    std::sort(modules.begin(), modules.end());
    modules.erase(std::unique(modules.begin(), modules.end()), modules.end());
    return modules;
}

std::vector<std::string> TypeChecker::get_visible_variables() const {
    std::vector<std::string> vars;
    const Scope* scope = current_scope.get();
    while (scope) {
        for (const auto& pair : scope->variables) {
            vars.push_back(pair.first);
        }
        scope = scope->parent.get();
    }
    if (current_function) {
        for (const auto& p : current_function->params) {
            vars.push_back(p.first);
        }
        for (const auto& op : current_function->optionalParams) {
            vars.push_back(op.first);
        }
    }
    if (current_program_) {
        for (const auto& pair : current_program_->imported_symbols) {
            vars.push_back(pair.first);
            size_t dot_pos = pair.first.find_last_of('.');
            if (dot_pos != std::string::npos) {
                vars.push_back(pair.first.substr(dot_pos + 1));
            }
        }
    }
    for (const auto& pair : function_signatures) {
        vars.push_back(pair.first);
    }
    for (const auto& pair : frame_declarations) {
        vars.push_back(pair.first);
    }
    for (const auto& pair : trait_declarations) {
        vars.push_back(pair.first);
    }
    if (current_program_) {
        for (const auto& stmt : current_program_->statements) {
            if (auto func = std::dynamic_pointer_cast<AST::FunctionDeclaration>(stmt)) {
                vars.push_back(func->name);
            } else if (auto var = std::dynamic_pointer_cast<AST::VarDeclaration>(stmt)) {
                vars.push_back(var->name);
            } else if (auto frame = std::dynamic_pointer_cast<AST::FrameDeclaration>(stmt)) {
                vars.push_back(frame->name);
            } else if (auto trait = std::dynamic_pointer_cast<AST::TraitDeclaration>(stmt)) {
                vars.push_back(trait->name);
            } else if (auto enm = std::dynamic_pointer_cast<AST::EnumDeclaration>(stmt)) {
                vars.push_back(enm->name);
            }
        }
    }
    std::sort(vars.begin(), vars.end());
    vars.erase(std::unique(vars.begin(), vars.end()), vars.end());
    return vars;
}

std::vector<std::string> TypeChecker::get_visible_types() const {
    std::vector<std::string> types = {
        "int", "int8", "int16", "int32", "int64", "int128",
        "uint", "uint8", "uint16", "uint32", "uint64", "uint128",
        "float32", "float64", "decimal", "d2", "d4", "d6",
        "str", "String", "bool", "any", "nil", "void"
    };
    for (const auto& pair : frame_declarations) {
        types.push_back(pair.first);
    }
    for (const auto& pair : trait_declarations) {
        types.push_back(pair.first);
    }
    if (current_program_) {
        for (const auto& pair : current_program_->imported_symbols) {
            types.push_back(pair.first);
        }
        for (const auto& stmt : current_program_->statements) {
            if (auto enm = std::dynamic_pointer_cast<AST::EnumDeclaration>(stmt)) {
                types.push_back(enm->name);
            } else if (auto td = std::dynamic_pointer_cast<AST::TypeDeclaration>(stmt)) {
                types.push_back(td->name);
            }
        }
    }
    std::sort(types.begin(), types.end());
    types.erase(std::unique(types.begin(), types.end()), types.end());
    return types;
}

std::string TypeChecker::get_module_prefix(const std::string& name) const {
    size_t last_dot = name.find_last_of('.');
    if (last_dot != std::string::npos) {
        return name.substr(0, last_dot);
    }
    return "";
}

bool TypeChecker::is_failed_type(const std::string& name) const {
    if (failed_frames.count(name)) return true;
    std::string mod_prefix = get_module_prefix(name);
    if (!mod_prefix.empty() && failed_modules.count(mod_prefix)) return true;

    // Check if the name matches any failed module + unqualified name
    for (const auto& failed_mod : failed_modules) {
        if (failed_mod + "." + name == name) continue;
        if (frame_declarations.count(failed_mod + "." + name)) {
            return true;
        }
    }
    return false;
}

} // namespace Frontend
} // namespace LM

namespace LM {
namespace Frontend {
using namespace LM::Error;

// =============================================================================
// ERROR REPORTING AND UTILITIES
// =============================================================================

std::string TypeChecker::get_code_context(int line) {
    if (current_source.empty() || line <= 0) {
        return "";
    }
    
    std::istringstream stream(current_source);
    std::string currentLine;
    int currentLineNumber = 1;
    
    // Find the target line
    while (std::getline(stream, currentLine) && currentLineNumber < line) {
        currentLineNumber++;
    }
    
    if (currentLineNumber == line) {
        return currentLine;
    }
    
    return "";
}

void TypeChecker::check_assert_call(const std::shared_ptr<LM::Frontend::AST::CallExpr>& expr) {
    if (expr->arguments.size() != 2) {
        add_error("assert() expects exactly 2 arguments: condition (bool) and message (string), got " + 
                std::to_string(expr->arguments.size()), expr->line, 0, 
                get_code_context(expr->line), "assert(...)", "assert(condition, message)");
        return;
    }
    
    // Check first argument (condition) is boolean
    TypePtr conditionType = check_expression(expr->arguments[0]);
    if (!is_boolean_type(conditionType) && conditionType->tag != TypeTag::Any) {
        add_error("assert() first argument must be boolean, got " + conditionType->toString(), 
                expr->line, 0, get_code_context(expr->line), "condition", "boolean expression");
    }
    
    // Check second argument (message) is string
    TypePtr messageType = check_expression(expr->arguments[1]);
    if (!is_string_type(messageType) && messageType->tag != TypeTag::Any) {
        add_error("assert() second argument must be string, got " + messageType->toString(), 
                expr->line, 0, get_code_context(expr->line), "message", "string literal or expression");
    }
}

// =============================================================================
// CONTROL FLOW CHECKING
//
// NOTE: check_function_call and validate_argument_types live in types.cpp
// (the canonical TU for type validation); do not redefine them here.
// =============================================================================

void TypeChecker::check_return_statement(TypePtr return_type, int line) {
    if (!current_return_type) {
        add_error("Return statement outside of function", line);
        return;
    }
    
    if (!is_type_compatible(current_return_type, return_type)) {
        add_error("Return type mismatch: expected " + current_return_type->toString() + 
                 ", got " + return_type->toString(), line);
    }
}

void TypeChecker::check_break_statement(int line) {
    if (!in_loop) {
        add_error("Break statement outside of loop", line);
    }
}

void TypeChecker::check_continue_statement(int line) {
    if (!in_loop) {
        add_error("Continue statement outside of loop", line);
    }
}

// =============================================================================
// VISIBILITY CHECKING
// =============================================================================

bool TypeChecker::is_visible(const std::string& frame_name, LM::Frontend::AST::VisibilityLevel visibility, int line) {
    // Public and Const are always visible
    if (visibility == LM::Frontend::AST::VisibilityLevel::Public ||
        visibility == LM::Frontend::AST::VisibilityLevel::Const) {
        return true;
    }

    // Private and Protected require being inside the frame or a subtype
    if (!current_frame) {
        return false;
    }

    // Check if we are inside the same frame
    std::string cur_frame_name = current_frame->name;
    if (!current_module_name.empty() && cur_frame_name.find('.') == std::string::npos) {
        cur_frame_name = current_module_name + "." + cur_frame_name;
    }
    if (cur_frame_name == frame_name) {
        return true;
    }

    // Protected allows access from related frames (those sharing traits)
    if (visibility == LM::Frontend::AST::VisibilityLevel::Protected) {
        auto target_info = type_system.getFrameInfo(frame_name);
        auto current_info = type_system.getFrameInfo(current_frame->name);

        if (target_info && current_info) {
            // Check if current frame inherits from target frame
            if (target_info->name == current_info->name) return true;
            for (const auto& trait_a : target_info->implements) {
                for (const auto& trait_b : current_info->implements) {
                    if (trait_a == trait_b) return true;
                }
            }
        }
        return false;
    }
    return false;
}

// =============================================================================
// ERROR TYPE INFERENCE & LAMBDA/LITERAL TYPE INFERENCE
//
// These helpers (infer_function_error_types, infer_expression_error_types,
// can_function_produce_error_type, can_propagate_error,
// is_error_union_compatible, join_error_types, infer_lambda_return_type,
// infer_literal_type) are defined in their canonical TUs (types.cpp and
// patterns.cpp respectively). They must NOT be redefined here.
// =============================================================================

} // namespace Frontend
} // namespace LM

// fyra_builtin_functions.hh - Built-in functions implemented in Fyra IR

#pragma once

#include "ir/Module.h"
#include "ir/IRBuilder.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <memory>

namespace LM::Backend::Fyra {

class FyraBuiltinFunctions {
public:
    static void emit_used_builtins(ir::Module* module, 
                                 ir::IRBuilder* builder,
                                 const std::unordered_set<std::string>& used_builtins);
    
    static bool is_builtin(const std::string& name);
    static std::string get_internal_name(const std::string& name);

private:
    static void emit_print_int(ir::Module* module, ir::IRBuilder* builder);
    static void emit_print_str(ir::Module* module, ir::IRBuilder* builder);
    static void emit_assert(ir::Module* module, ir::IRBuilder* builder);
    static void emit_box_string(ir::Module* module, ir::IRBuilder* builder);
    static void emit_abs(ir::Module* module, ir::IRBuilder* builder);
    
    // External Runtime Declarations
    static void decl_runtime_list(ir::Module* module, ir::IRBuilder* builder);
    static void decl_runtime_dict(ir::Module* module, ir::IRBuilder* builder);
    static void decl_runtime_tuple(ir::Module* module, ir::IRBuilder* builder);
    static void decl_runtime_math(ir::Module* module, ir::IRBuilder* builder);
    static void decl_runtime_string(ir::Module* module, ir::IRBuilder* builder);
    static void decl_runtime_utility(ir::Module* module, ir::IRBuilder* builder);
};

} // namespace LM::Backend::Fyra

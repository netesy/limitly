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

    static ir::GlobalVariable* get_or_create_global_str(ir::Module* module, ir::IRBuilder* builder, const std::string& name, const std::string& str_val);

    static void emit_print_str_inline(ir::Module* module, ir::IRBuilder* builder, ir::Value* char_ptr);
    static void emit_print_int_inline(ir::Module* module, ir::IRBuilder* builder, ir::Value* val);
    static void emit_print_bool_inline(ir::Module* module, ir::IRBuilder* builder, ir::Value* val);
    static void emit_print_nil_inline(ir::Module* module, ir::IRBuilder* builder);
    static void emit_print_float_inline(ir::Module* module, ir::IRBuilder* builder, ir::Value* val);
    static void emit_print_decimal_inline(ir::Module* module, ir::IRBuilder* builder, ir::Value* val, int scale);
    static ir::Value* emit_decimal_to_str_inline(ir::Module* module, ir::IRBuilder* builder, ir::Value* val, int scale);
    static ir::Value* emit_int_to_str_inline(ir::Module* module, ir::IRBuilder* builder, ir::Value* val);
    static ir::Value* emit_float_to_str_inline(ir::Module* module, ir::IRBuilder* builder, ir::Value* val);
    static ir::Value* emit_bool_to_str_inline(ir::Module* module, ir::IRBuilder* builder, ir::Value* val);
    static void emit_str_concat_ir(ir::Module* module, ir::IRBuilder* builder);
    static void emit_str_eq_ir(ir::Module* module, ir::IRBuilder* builder);
    static void emit_str_format_ir(ir::Module* module, ir::IRBuilder* builder);
    static void emit_substring_ir(ir::Module* module, ir::IRBuilder* builder);
    static void emit_to_string_ir(ir::Module* module, ir::IRBuilder* builder);
    static void emit_error_new_ir(ir::Module* module, ir::IRBuilder* builder);
    static void emit_list_ir(ir::Module* module, ir::IRBuilder* builder);
    static void emit_tuple_ir(ir::Module* module, ir::IRBuilder* builder);
    static void emit_dict_ir(ir::Module* module, ir::IRBuilder* builder);

private:
    static void emit_assert(ir::Module* module, ir::IRBuilder* builder);
    static void emit_abs(ir::Module* module, ir::IRBuilder* builder);
    
    // External Runtime Declarations
    static void decl_runtime_math(ir::Module* module, ir::IRBuilder* builder);
};

} // namespace LM::Backend::Fyra

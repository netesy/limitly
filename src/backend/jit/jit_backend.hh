#ifndef JIT_BACKEND_H
#define JIT_BACKEND_H

#include "../frontend/ast.hh"
#include <libgccjit++.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <variant>
#include "memory.hh"
#include "functions.hh"
#include "../common/builtin_functions.hh"
#include "symbol_table.hh"
#include "string_builder.hh"

class JitBackend {
public:
    JitBackend();
    ~JitBackend();

    void process(const std::vector<std::shared_ptr<AST::Program>>& programs);
    void compile(const char* output_filename);
    int compile_and_run(); // Debug mode: compile and run directly without saving

private:
    void visit(const std::shared_ptr<AST::Statement>& stmt);
    void visit(const std::shared_ptr<AST::Expression>& expr);
    void visit(const std::shared_ptr<AST::VarDeclaration>& stmt);
    void visit(const std::shared_ptr<AST::ExprStatement>& stmt);
    void visit(const std::shared_ptr<AST::ForStatement>& stmt);
    void visit(const std::shared_ptr<AST::WhileStatement>& stmt);
    void visit(const std::shared_ptr<AST::BlockStatement>& stmt);
    void visit(const std::shared_ptr<AST::IfStatement>& stmt);
    void visit(const std::shared_ptr<AST::PrintStatement>& stmt);
    void visit(const std::shared_ptr<AST::BreakStatement>& stmt);
    void visit(const std::shared_ptr<AST::ContinueStatement>& stmt);
    void visit(const std::shared_ptr<AST::IterStatement>& stmt);
    void visit(const std::shared_ptr<AST::MatchStatement>& stmt);
    void visit(const std::shared_ptr<AST::FunctionDeclaration>& stmt);
    void visit(const std::shared_ptr<AST::ReturnStatement>& stmt);
    void visit(const std::shared_ptr<AST::ClassDeclaration>& stmt);
    void visit(const std::shared_ptr<AST::ParallelStatement>& stmt);
    void visit(const std::shared_ptr<AST::ModuleDeclaration>& stmt);
    void visit(const std::shared_ptr<AST::ImportStatement>& stmt);

    gccjit::type get_jit_type(const std::shared_ptr<AST::TypeAnnotation>& type);

    gccjit::rvalue visit_expr(const std::shared_ptr<AST::Expression>& expr);
    gccjit::rvalue visit_expr(const std::shared_ptr<AST::BinaryExpr>& expr);
    gccjit::rvalue visit_expr(const std::shared_ptr<AST::UnaryExpr>& expr);
    gccjit::rvalue visit_expr(const std::shared_ptr<AST::LiteralExpr>& expr);
    gccjit::rvalue visit_expr(const std::shared_ptr<AST::LiteralExpr>& expr, gccjit::type target_type);
    gccjit::rvalue visit_expr(const std::shared_ptr<AST::InterpolatedStringExpr>& expr);
    gccjit::rvalue visit_expr(const std::shared_ptr<AST::VariableExpr>& expr);
    gccjit::rvalue visit_expr(const std::shared_ptr<AST::AssignExpr>& expr);
    gccjit::rvalue visit_expr(const std::shared_ptr<AST::CallExpr>& expr);
    gccjit::rvalue visit_expr(const std::shared_ptr<AST::LambdaExpr>& expr);
    gccjit::rvalue visit_expr(const std::shared_ptr<AST::GroupingExpr>& expr);
    gccjit::rvalue visit_expr(const std::shared_ptr<AST::MemberExpr>& expr);

    gccjit::context m_context;
    gccjit::function m_main_func;
    gccjit::function m_current_func;
    gccjit::block m_current_block;
    
    // Memory management
    MemoryManager<> m_mem_manager;
    std::unique_ptr<MemoryManager<>::Region> m_region;
    
    // Symbol table for compile-time information
    SymbolTable m_symbol_table;
    
    // JIT variable mapping (name -> lvalue)
    std::unordered_map<std::string, gccjit::lvalue> m_variable_lvalues;

    // Types
    std::map<std::string, std::string> m_type_names;
    std::map<std::string, std::vector<std::string>> m_struct_field_names;
    std::unordered_map<std::string, std::vector<gccjit::field>> m_class_fields;
    gccjit::type m_void_type;
    gccjit::type m_int_type;
    gccjit::type m_double_type;
    gccjit::type m_bool_type;
    gccjit::type m_const_char_ptr_type;
    gccjit::type m_void_ptr_type;
    gccjit::type m_int8_type;
    gccjit::type m_int16_type;
    gccjit::type m_int32_type;
    gccjit::type m_int64_type;
    gccjit::type m_uint8_type;
    gccjit::type m_uint16_type;
    gccjit::type m_uint32_type;
    gccjit::type m_uint64_type;
    gccjit::type m_float_type;
    gccjit::type m_long_double_type;
    gccjit::type m_closure_type;
    std::vector<gccjit::field> m_closure_fields;

    // String functions
    gccjit::function m_strlen_func;
    gccjit::function m_strcpy_func;
    gccjit::function m_strcat_func;
    gccjit::function m_strcmp_func;
    // Standard library functions
    gccjit::function m_printf_func;
    gccjit::function m_sprintf_func;
    gccjit::function m_snprintf_func;
    gccjit::function m_free_func;
    gccjit::function m_malloc_func;
    gccjit::function m_memset_func;
    
    // JIT string builder functions
    gccjit::function m_jit_sb_create_func;
    gccjit::function m_jit_sb_destroy_func;
    gccjit::function m_jit_sb_finish_func;
    gccjit::function m_jit_sb_append_cstr_func;
    gccjit::function m_jit_sb_append_int_func;
    gccjit::function m_jit_sb_append_float_func;
    gccjit::function m_jit_sb_append_bool_func;
    
    // String builder for code generation
    limitly_string_builder m_sb;
    
    std::unordered_map<std::string, gccjit::function> m_functions;

    // Loop handling
    std::vector<std::pair<gccjit::block, gccjit::block>> m_loop_blocks;

    // Module handling
    std::string m_current_module_name;
    std::string mangle(const std::string& name);

    // Type handling helpers
    bool is_arithmetic_op(TokenType op);
    gccjit::type get_common_type(gccjit::type type1, gccjit::type type2);
    
    // String conversion helper
    gccjit::rvalue convert_expr_to_string(const std::shared_ptr<AST::Expression>& expr);
    
    // Builtin functions integration
    void register_builtin_functions();
    gccjit::type convert_builtin_type(TypeTag tag);
    
    // Type conversion helpers
    TypePtr convert_ast_type(const std::shared_ptr<AST::TypeAnnotation>& ast_type);
    TypePtr convert_jit_type(gccjit::type jit_type);
    gccjit::type create_closure_type();

    // Class handling
    std::unordered_map<std::string, gcc_jit_struct*> m_class_structs;
    std::unordered_map<std::string, gcc_jit_type*> m_class_types;
};

#endif // JIT_BACKEND_H

#ifndef JIT_BACKEND_H
#define JIT_BACKEND_H

#include "../frontend/ast.hh"
#include "libgccjit++.h"
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "memory.hh"

class JitBackend {
public:
    JitBackend();
    ~JitBackend() = default;

    void process(const std::vector<std::shared_ptr<AST::Program>>& programs);
    void compile(const char* output_filename);

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
    std::vector<std::unordered_map<std::string, gccjit::lvalue>> m_scopes;

    // Types
    std::map<gccjit::type, std::string> m_type_names;
    std::map<gccjit::struct_, std::vector<std::string>> m_struct_field_names;
    gccjit::type m_void_type;
    gccjit::type m_int_type;
    gccjit::type m_double_type;
    gccjit::type m_bool_type;
    gccjit::type m_const_char_ptr_type;
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

    // Functions
    gccjit::function m_printf_func;
    gccjit::function m_strcmp_func;
    gccjit::function m_malloc_func;
    std::unordered_map<std::string, gccjit::function> m_functions;

    // Loop handling
    std::vector<std::pair<gccjit::block, gccjit::block>> m_loop_blocks;

    // Memory management
    MemoryManager<> m_mem_manager;
    MemoryManager<>::Region m_region;

    // Module handling
    std::string m_current_module_name;
    std::string mangle(const std::string& name);

    // Class handling
    std::unordered_map<std::string, gcc_jit_struct*> m_class_structs;
    std::unordered_map<std::string, gcc_jit_type*> m_class_types;
};

#endif // JIT_BACKEND_H

#ifndef JIT_BACKEND_H
#define JIT_BACKEND_H

#include "../frontend/ast.hh"
#include <libgccjit.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "memory.hh"

class JitBackend {
public:
    JitBackend();
    ~JitBackend();

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

    gcc_jit_type* get_jit_type(const std::shared_ptr<AST::TypeAnnotation>& type);

    gcc_jit_rvalue* visit_expr(const std::shared_ptr<AST::Expression>& expr);
    gcc_jit_rvalue* visit_expr(const std::shared_ptr<AST::BinaryExpr>& expr);
    gcc_jit_rvalue* visit_expr(const std::shared_ptr<AST::UnaryExpr>& expr);
    gcc_jit_rvalue* visit_expr(const std::shared_ptr<AST::LiteralExpr>& expr);
    gcc_jit_rvalue* visit_expr(const std::shared_ptr<AST::VariableExpr>& expr);
    gcc_jit_rvalue* visit_expr(const std::shared_ptr<AST::AssignExpr>& expr);
    gcc_jit_rvalue* visit_expr(const std::shared_ptr<AST::CallExpr>& expr);
    gcc_jit_rvalue* visit_expr(const std::shared_ptr<AST::LambdaExpr>& expr);
    gcc_jit_rvalue* visit_expr(const std::shared_ptr<AST::GroupingExpr>& expr);
    gcc_jit_rvalue* visit_expr(const std::shared_ptr<AST::MemberExpr>& expr);

    gcc_jit_context* m_context;
    gcc_jit_function* m_main_func;
    gcc_jit_function* m_current_func;
    gcc_jit_block* m_current_block;
    std::vector<std::unordered_map<std::string, gcc_jit_lvalue*>> m_scopes;

    // Types
    gcc_jit_type* m_void_type;
    gcc_jit_type* m_int_type;
    gcc_jit_type* m_double_type;
    gcc_jit_type* m_bool_type;
    gcc_jit_type* m_const_char_ptr_type;

    // Functions
    gcc_jit_function* m_printf_func;
    gcc_jit_function* m_strcmp_func;
    gcc_jit_function* m_malloc_func;
    std::unordered_map<std::string, gcc_jit_function*> m_functions;

    // Loop handling
    std::vector<std::pair<gcc_jit_block*, gcc_jit_block*>> m_loop_blocks;

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

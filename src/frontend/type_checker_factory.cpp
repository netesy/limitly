#include "type_checker.hh"
#include "module_manager.hh"
#include "module_graph.hh"
#include "symbol_database.hh"
#include "declaration_resolver.hh"
#include "trait_resolver.hh"
#include <functional>
#include <set>

namespace LM {
namespace Frontend {
namespace TypeCheckerFactory {

// Declaration
TypeCheckResult check_program(std::shared_ptr<LM::Frontend::AST::Program> program,
                               const std::string& source,
                               const std::string& file_path);

std::unique_ptr<TypeChecker> create(TypeSystem& type_system, SymbolDatabase& symbol_db);

void register_builtin_functions(TypeChecker& checker);

} // namespace TypeCheckerFactory
} // namespace Frontend
} // namespace LM

// Implementation
namespace LM {
namespace Frontend {
namespace TypeCheckerFactory {

std::unique_ptr<TypeChecker> create(TypeSystem& type_system, SymbolDatabase& symbol_db) {
    auto checker = std::make_unique<TypeChecker>(type_system, symbol_db);
    register_builtin_functions(*checker);
    return checker;
}

TypeCheckResult check_program(std::shared_ptr<LM::Frontend::AST::Program> program,
                              const std::string& source,
                              const std::string& file_path) {
    // Resolve all modules once at the beginning
    auto& manager = ModuleManager::getInstance();
    manager.clear();
    manager.resolve_all(program, "root");

    // Build dependency graph and detect cycles
    ModuleGraph graph(manager.get_all_modules());
    if (graph.has_cycle()) {
        return TypeCheckResult(program, nullptr, false, {});
    }

    // Verify declared dependencies exist
    std::vector<std::string> missing_dep_errors;
    for (const auto& [mod_name, mod_ptr] : manager.get_all_modules()) {
        for (const auto& dep : mod_ptr->dependencies) {
            if (!manager.get_module(dep)) {
                missing_dep_errors.push_back("Missing dependency '" + dep + "' required by module '" + mod_name + "'");
            }
        }
    }
    if (!missing_dep_errors.empty()) {
        return TypeCheckResult(program, nullptr, false, missing_dep_errors);
    }

    // Global declaration resolution
    SymbolDatabase symbol_db;
    DeclarationResolver decl_resolver(symbol_db);
    decl_resolver.resolve_all(manager);

    // Detect unreachable modules (not reachable from root)
    std::set<std::string> visited;
    std::vector<std::string> stack;

    // Find the root module. Since ModuleManager::resolve_all is called with "root",
    // and it registers the root_program under that name, we look for "root".
    const std::string root_name = "root";
    auto all_modules = manager.get_all_modules();

    if (all_modules.count(root_name)) {
        stack.push_back(root_name);
        while (!stack.empty()) {
            std::string cur = stack.back();
            stack.pop_back();
            if (visited.count(cur)) continue;
            visited.insert(cur);

            auto it = all_modules.find(cur);
            if (it != all_modules.end()) {
                for (const auto& dep : it->second->dependencies) {
                    if (!visited.count(dep)) stack.push_back(dep);
                }
            }
        }
    }
    for (const auto& kv : manager.get_all_modules()) {
        if (!visited.count(kv.first)) {
            missing_dep_errors.push_back("Unreachable module '" + kv.first + "' (not reachable from root)");
        }
    }
    if (!missing_dep_errors.empty()) {
        return TypeCheckResult(program, nullptr, false, missing_dep_errors);
    }

    // Create type system and checker
    auto type_system = std::make_shared<TypeSystem>();
    auto checker = create(*type_system, symbol_db);
    checker->set_source_context(source, file_path);
    bool success = checker->check_program(program);
    TypeCheckResult result(program, type_system, success, checker->get_errors());
    result.import_aliases = checker->get_import_aliases();
    result.registered_modules = checker->get_registered_modules();
    return result;
}

void register_builtin_functions(TypeChecker& checker) {
    auto& ts = checker.get_type_system();
    // String functions
    checker.register_builtin_function("concat", {ts.STRING_TYPE, ts.STRING_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("length", {ts.STRING_TYPE}, ts.INT_TYPE);
    checker.register_builtin_function("substring", {ts.STRING_TYPE, ts.INT_TYPE, ts.INT_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("_builtin_substring", {ts.STRING_TYPE, ts.INT_TYPE, ts.INT_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("str_format", {ts.STRING_TYPE, ts.ANY_TYPE}, ts.STRING_TYPE);
    // Utility len functions
    checker.register_builtin_function("len", {ts.STRING_TYPE}, ts.INT_TYPE);
    checker.register_builtin_function("len", {ts.createTypedListType(ts.ANY_TYPE)}, ts.INT_TYPE);
    checker.register_builtin_function("len", {ts.createTypedListType(ts.INT_TYPE)}, ts.INT_TYPE);
    checker.register_builtin_function("len", {ts.ANY_TYPE}, ts.INT_TYPE);
    // Misc utilities
    checker.register_builtin_function("typeof", {ts.ANY_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("clock", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("sleep", {ts.FLOAT64_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("time", {}, ts.INT64_TYPE);
    checker.register_builtin_function("date", {}, ts.STRING_TYPE);
    checker.register_builtin_function("now", {}, ts.STRING_TYPE);
    checker.register_builtin_function("assert", {ts.BOOL_TYPE, ts.STRING_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("print", {ts.ANY_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("print", {ts.ANY_TYPE, ts.ANY_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("print", {ts.ANY_TYPE, ts.ANY_TYPE, ts.ANY_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("print", {ts.ANY_TYPE, ts.ANY_TYPE, ts.ANY_TYPE, ts.ANY_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("print", {ts.ANY_TYPE, ts.ANY_TYPE, ts.ANY_TYPE, ts.ANY_TYPE, ts.ANY_TYPE}, ts.NIL_TYPE);
    // Collection functions
    auto function_type = ts.createFunctionType({}, ts.ANY_TYPE);
    checker.register_builtin_function("map", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.createTypedListType(ts.ANY_TYPE));
    checker.register_builtin_function("filter", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.createTypedListType(ts.ANY_TYPE));
    checker.register_builtin_function("reduce", {function_type, ts.createTypedListType(ts.ANY_TYPE), ts.ANY_TYPE}, ts.ANY_TYPE);
    checker.register_builtin_function("forEach", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.NIL_TYPE);
    checker.register_builtin_function("find", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.ANY_TYPE);
    checker.register_builtin_function("some", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.BOOL_TYPE);
    checker.register_builtin_function("every", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.BOOL_TYPE);
    // Function composition utilities
    checker.register_builtin_function("compose", {function_type, function_type}, function_type);
    checker.register_builtin_function("curry", {function_type}, function_type);
    checker.register_builtin_function("partial", {function_type, ts.ANY_TYPE}, function_type);
    // Channel
    checker.register_builtin_function("channel", {}, ts.CHANNEL_TYPE);
    // Backend utilities
    checker.register_builtin_function("typeOf", {ts.ANY_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("debug", {ts.ANY_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("input", {ts.STRING_TYPE}, ts.STRING_TYPE);
    // Unified Resource System
    checker.register_builtin_function("resource_create", {ts.INT_TYPE, ts.createTypedListType(ts.ANY_TYPE)}, ts.INT64_TYPE);
    checker.register_builtin_function("resource_create", {ts.INT_TYPE}, ts.INT64_TYPE);
    checker.register_builtin_function("resource_call", {ts.INT64_TYPE, ts.INT_TYPE, ts.createTypedListType(ts.ANY_TYPE)}, ts.ANY_TYPE);
    checker.register_builtin_function("resource_destroy", {ts.INT64_TYPE}, ts.NIL_TYPE);
    // File I/O intrinsics
    checker.register_builtin_function("file_exists", {ts.STRING_TYPE}, ts.BOOL_TYPE);
    checker.register_builtin_function("file_delete", {ts.STRING_TYPE}, ts.BOOL_TYPE);
}

} // namespace TypeCheckerFactory
} // namespace Frontend
} // namespace LM

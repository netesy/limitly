#include "type_checker.hh"
#include "module_manager.hh"
#include <functional>
#include <set>

namespace LM {
namespace Frontend {
namespace TypeCheckerFactory {

TypeCheckResult check_program(std::shared_ptr<LM::Frontend::AST::Program> program, const std::string& source, const std::string& file_path) {
    // Resolve all modules once at the beginning
    auto& manager = ModuleManager::getInstance();
    manager.clear();
    manager.resolve_all(program, "root");

    // Create type system
    auto type_system = std::make_shared<TypeSystem>();
    auto checker = create(*type_system);
    
    // Set source context for error reporting
    checker->set_source_context(source, file_path);
    
    bool success = checker->check_program(program);
    TypeCheckResult result(program, type_system, success, checker->get_errors());
    result.import_aliases = checker->get_import_aliases();  // Copy import aliases from checker
    result.registered_modules = checker->get_registered_modules();  // Copy registered modules from checker
    
    return result;
}

std::unique_ptr<TypeChecker> create(TypeSystem& type_system) {
    auto checker = std::make_unique<TypeChecker>(type_system);
    
    // Register builtin functions
    register_builtin_functions(*checker);
    
    return checker;
}

void register_builtin_functions(TypeChecker& checker) {
    auto& ts = checker.get_type_system();
    
    // Math functions are implemented in the std.math library
    
    // String functions
    checker.register_builtin_function("concat", {ts.STRING_TYPE, ts.STRING_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("length", {ts.STRING_TYPE}, ts.INT_TYPE);
    checker.register_builtin_function("substring", {ts.STRING_TYPE, ts.INT_TYPE, ts.INT_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("str_format", {ts.STRING_TYPE, ts.ANY_TYPE}, ts.STRING_TYPE);
    
    // Utility functions - len must be registered before other builtins that might depend on it
    checker.register_builtin_function("len", {ts.STRING_TYPE}, ts.INT_TYPE);
    checker.register_builtin_function("len", {ts.createTypedListType(ts.ANY_TYPE)}, ts.INT_TYPE);
    checker.register_builtin_function("len", {ts.createTypedListType(ts.INT_TYPE)}, ts.INT_TYPE);
    checker.register_builtin_function("len", {ts.ANY_TYPE}, ts.INT_TYPE);
    
    checker.register_builtin_function("typeof", {ts.ANY_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("clock", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("sleep", {ts.FLOAT64_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("time", {}, ts.INT64_TYPE);
    checker.register_builtin_function("date", {}, ts.STRING_TYPE);
    checker.register_builtin_function("now", {}, ts.STRING_TYPE);
    checker.register_builtin_function("assert", {ts.BOOL_TYPE, ts.STRING_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("print", {ts.ANY_TYPE, ts.ANY_TYPE, ts.ANY_TYPE, ts.ANY_TYPE, ts.ANY_TYPE}, ts.NIL_TYPE);
    
    
    // Collection functions (enhanced)
    auto function_type = ts.createFunctionType({}, ts.ANY_TYPE); // Simple function type
    checker.register_builtin_function("map", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.createTypedListType(ts.ANY_TYPE));
    checker.register_builtin_function("filter", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.createTypedListType(ts.ANY_TYPE));
    checker.register_builtin_function("reduce", {function_type, ts.createTypedListType(ts.ANY_TYPE), ts.ANY_TYPE}, ts.ANY_TYPE);
    checker.register_builtin_function("forEach", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.NIL_TYPE);
    checker.register_builtin_function("find", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.ANY_TYPE);
    checker.register_builtin_function("some", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.BOOL_TYPE);
    checker.register_builtin_function("every", {function_type, ts.createTypedListType(ts.ANY_TYPE)}, ts.BOOL_TYPE);
    
    // Function composition
    checker.register_builtin_function("compose", {function_type, function_type}, function_type);
    checker.register_builtin_function("curry", {function_type}, function_type);
    checker.register_builtin_function("partial", {function_type, ts.ANY_TYPE}, function_type);
    
    // Channel function
    checker.register_builtin_function("channel", {}, ts.CHANNEL_TYPE);
    
    // Additional utility functions from backend
    checker.register_builtin_function("typeOf", {ts.ANY_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("debug", {ts.ANY_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("input", {ts.STRING_TYPE}, ts.STRING_TYPE);

    // Unified Resource System
    // Core overloads
    checker.register_builtin_function("resource_create", {ts.INT_TYPE, ts.ANY_TYPE, ts.ANY_TYPE}, ts.INT64_TYPE);
    checker.register_builtin_function("resource_create", {ts.INT_TYPE}, ts.INT64_TYPE); // overload for type only
    checker.register_builtin_function("resource_call", {ts.INT64_TYPE, ts.INT_TYPE, ts.ANY_TYPE, ts.ANY_TYPE, ts.ANY_TYPE}, ts.ANY_TYPE);
    checker.register_builtin_function("resource_call", {ts.INT64_TYPE, ts.INT_TYPE}, ts.ANY_TYPE); // overload for no extra args
    checker.register_builtin_function("resource_call", {ts.INT64_TYPE, ts.INT_TYPE, ts.ANY_TYPE}, ts.ANY_TYPE); // overload for one arg
    checker.register_builtin_function("resource_call", {ts.INT64_TYPE, ts.INT_TYPE, ts.ANY_TYPE, ts.ANY_TYPE}, ts.ANY_TYPE); // overload for two args
    checker.register_builtin_function("resource_destroy", {ts.INT64_TYPE}, ts.NIL_TYPE);

    // File I/O intrinsics
    checker.register_builtin_function("file_exists", {ts.STRING_TYPE}, ts.BOOL_TYPE);
    checker.register_builtin_function("file_delete", {ts.STRING_TYPE}, ts.BOOL_TYPE);
}

} // namespace TypeCheckerFactory
} // namespace Frontend
} // namespace LM

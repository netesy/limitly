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
    
    // Math functions
    checker.register_builtin_function("abs", {ts.INT_TYPE}, ts.INT_TYPE);
    checker.register_builtin_function("fabs", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("sqrt", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("cbrt", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("pow", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("exp", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("exp2", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("log", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("log10", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("log2", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    
    // Trigonometric functions
    checker.register_builtin_function("sin", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("cos", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("tan", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("asin", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("acos", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("atan", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("atan2", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    
    // Hyperbolic functions
    checker.register_builtin_function("sinh", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("cosh", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("tanh", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("asinh", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("acosh", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("atanh", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    
    // Rounding functions
    checker.register_builtin_function("ceil", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("floor", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("trunc", {ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("round", {ts.FLOAT64_TYPE, ts.INT_TYPE}, ts.FLOAT64_TYPE);
    
    // Other math functions
    checker.register_builtin_function("fmod", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("remainder", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("fmax", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("fmin", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("fdim", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    checker.register_builtin_function("hypot", {ts.FLOAT32_TYPE, ts.FLOAT32_TYPE}, ts.FLOAT32_TYPE);
    
    // String functions
    checker.register_builtin_function("concat", {ts.STRING_TYPE, ts.STRING_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("length", {ts.STRING_TYPE}, ts.INT_TYPE);
    checker.register_builtin_function("substring", {ts.STRING_TYPE, ts.INT_TYPE, ts.INT_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("str_format", {ts.STRING_TYPE, ts.ANY_TYPE}, ts.STRING_TYPE);
    
    // Utility functions
    checker.register_builtin_function("typeof", {ts.ANY_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("clock", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("sleep", {ts.FLOAT64_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("len", {ts.ANY_TYPE}, ts.INT_TYPE);
    checker.register_builtin_function("time", {}, ts.INT64_TYPE);
    checker.register_builtin_function("date", {}, ts.STRING_TYPE);
    checker.register_builtin_function("now", {}, ts.STRING_TYPE);
    checker.register_builtin_function("assert", {ts.BOOL_TYPE, ts.STRING_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("print", {ts.ANY_TYPE}, ts.NIL_TYPE);
    
    // Math constants (as functions)
    checker.register_builtin_function("pi", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("e", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("ln2", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("ln10", {}, ts.FLOAT64_TYPE);
    checker.register_builtin_function("sqrt2", {}, ts.FLOAT64_TYPE);
    
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

    // File I/O intrinsics
    checker.register_builtin_function("file_open", {ts.STRING_TYPE, ts.STRING_TYPE}, ts.INT64_TYPE);
    checker.register_builtin_function("file_read", {ts.INT64_TYPE}, ts.STRING_TYPE);
    checker.register_builtin_function("file_write", {ts.INT64_TYPE, ts.STRING_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("file_close", {ts.INT64_TYPE}, ts.NIL_TYPE);
    checker.register_builtin_function("file_exists", {ts.STRING_TYPE}, ts.BOOL_TYPE);
    checker.register_builtin_function("file_delete", {ts.STRING_TYPE}, ts.BOOL_TYPE);
}

} // namespace TypeCheckerFactory
} // namespace Frontend
} // namespace LM

#include "frontend/parser.hh"
#include "frontend/type_checker.hh"
#include "frontend/memory_checker.hh"
#include "lir/generator.hh"
#include "lir/function_registry.hh"
#include "lir/serializer.hh"
#include "lir/verifier.hh"
#include "backend/vm/register.hh"
#include "backend/fyra/fyra.hh"
#include <cassert>
#include <filesystem>
#include <iostream>
#include <set>
using namespace LM;
int main(int argc, char** argv) {
    assert(argc == 2);
    const std::string source = R"(
type Hook=fn([int]):nil;
frame Box {pub var cb:Hook; pub var data:[int]; pub fn invoke(){self.cb(self.data);}}
fn pending(box:Box):fn():nil {return fn():nil {box.invoke();};}
fn element(xs:[[int]]):[int] {return xs[0];}
fn factory(x:[int]):fn():int {return fn():int {return x[0];};}
var xs=[[7]]; var child=element(xs); print(child[0]);
{var ys=[[9]]; child=element(ys);} print(child[0]);
var observer=factory(child); print(observer());
var absent={} as {str:[int]}; var maybe=absent["x"] as [int];
{maybe=absent["y"] as [int];} if(maybe==nil){maybe=[11];} print(maybe[0]);
fn identity(x:any):any {return x;}
var erased=identity(2); print(erased==nil); print(identity(true)); print(identity(2.5));
)";
    Frontend::Scanner scanner(source); scanner.scanTokens();
    Frontend::Parser parser(scanner, false);
    auto ast = parser.parse(); assert(ast);
    auto typed = Frontend::TypeCheckerFactory::check_program(ast,source,"source_ownership.lm");
    assert(typed.success && typed.errors.empty());
    auto facts = ast->ownership_facts; assert(facts && facts->verified);
    std::map<const Frontend::AST::Node*, Memory::Identity> declaration_identities;
    for (const auto& statement : ast->statements)
        if (auto function = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(statement)) {
            declaration_identities[function.get()] = function->memory_info.semantic_id;
            declaration_identities[function->body.get()] = function->body->memory_info.semantic_id;
        }
    auto checked = Frontend::MemoryCheckerFactory::check_program(ast,source,"source_ownership.lm");
    for (const auto& [declaration, identity] : declaration_identities)
        assert(identity && declaration->memory_info.semantic_id == identity);
    assert(checked.success && ast->ownership_facts == facts);
    LIR::Generator generator; generator.set_import_aliases(typed.import_aliases);
    generator.set_registered_modules(typed.registered_modules);
    auto wrapper = generator.generate_program(typed); assert(wrapper && !generator.has_errors());
    auto& registry = LIR::FunctionRegistry::getInstance();
    auto lookup = [&](const std::string& suffix) -> LIR::LIR_Function* {
        for (const auto& name : registry.getFunctionNames())
            if (name == suffix || name.ends_with("." + suffix)) return registry.getFunction(name);
        return nullptr;
    };
    auto* element = lookup("element"); assert(element);
    assert(element->inferred_effects.return_projections == std::set<uint32_t>{0});
    auto* factory = lookup("factory"); assert(factory);
    assert(!factory->inferred_effects.returned_callables.empty());
    assert(!factory->inferred_effects.returned_capture_parameters.empty());
    bool captured_obligation = false;
    for (const auto& name : registry.getFunctionNames()) {
        auto* function = registry.getFunction(name);
        if (!function || function->instructions.empty()) continue;
        captured_obligation |= !function->inferred_effects.captures_opaque.empty();
        auto restored = LIR::Serializer::deserialize(LIR::Serializer::serialize(*function));
        assert(restored.inferred_effects == function->inferred_effects);
        assert(restored.ownership_parameters == function->ownership_parameters);
        assert(restored.ownership_captures == function->ownership_captures);
        assert(restored.instructions.size() == function->instructions.size());
        for (size_t i=0;i<restored.instructions.size();++i) { assert(restored.instructions[i].ownership == function->instructions[i].ownership); assert(restored.instructions[i].imm == function->instructions[i].imm); }
        registry.registerFunction(name,std::make_unique<LIR::LIR_Function>(std::move(restored)));
    }
    assert(captured_obligation);
    auto restored = LIR::Serializer::deserialize(LIR::Serializer::serialize(*wrapper));
    std::set<LIR::LIR_Op> operations;
    for (const auto& instruction : restored.instructions) operations.insert(instruction.op);
    for (auto op : {LIR::LIR_Op::RefCreate,LIR::LIR_Op::RefResolve,LIR::LIR_Op::RefRelease,LIR::LIR_Op::RefMove}) assert(operations.count(op));
    Backend::VM::Register::RegisterVM vm; vm.execute(restored); vm.reset();
#if defined(FYRA_AVAILABLE) && defined(__linux__) && defined(__x86_64__)
    for (int level=0;level<3;++level) {
        Backend::Fyra::FyraCompiler compiler;
        auto output = (std::filesystem::path(argv[1]) / ("source-o"+std::to_string(level))).string();
        auto result = compiler.compile_aot(restored,output,Backend::Fyra::Platform::Linux,
            Backend::Fyra::Architecture::X86_64,static_cast<Backend::Fyra::OptimizationLevel>(level));
        if (!result.success) throw std::runtime_error(result.error_message);
    }
#endif
    std::cout << "Source ownership serialization and execution passed\n";
}

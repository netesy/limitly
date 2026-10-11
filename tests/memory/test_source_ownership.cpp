#include "frontend/parser.hh"
#include "frontend/type_checker.hh"
#include "frontend/memory_checker.hh"
#include "lir/generator.hh"
#include "lir/function_registry.hh"
#include "lir/serializer.hh"
#include "lir/verifier.hh"
#include "memory/region_analysis.hh"
#include "memory/lir_analysis.hh"
#include "backend/vm/register.hh"
#include "backend/fyra/fyra.hh"
#include <cassert>
#include <filesystem>
#include <iostream>
#include <set>
#include <chrono>
#include <cstdlib>
using namespace LM;
int main(int argc, char** argv) {
    assert(argc == 2);
    const auto started = std::chrono::steady_clock::now();
    auto stage = [&](const char* name) {
        if (std::getenv("LYMAR_TEST_TRACE_STAGES"))
            std::cerr << name << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now()-started).count() << "ms\n";
    };
    {
        LIR::LIR_Function invalid_raw("invalid_raw_kind", 0);
        invalid_raw.instructions.emplace_back(LIR::LIR_Op::MemoryLoad, LIR::Type::I64, 1, 0, UINT32_MAX, 11);
        std::vector<std::string> errors;
        assert(!LIR::Verifier::verify_memory_regions(invalid_raw, errors));
        assert(!errors.empty());
        LIR::LIR_Function erased("erased_scalar_parameter", 1);
        erased.register_types[0] = LIR::Type::Bool;
        Memory::infer_lir_effects(erased);
        assert(erased.memory_effects.parameters[0] == Memory::Ownership::Unspecified);
        erased.inferred_effects.parameters = {Memory::Consume};
        Memory::infer_lir_effects(erased);
        assert(erased.memory_effects.parameters[0] == Memory::Ownership::Owned);
        erased.memory_effects.borrowed_parameter = 0;
        erased.memory_effects.result = Memory::Ownership::ReadBorrow;
        erased.inferred_effects.parameters.clear();
        Memory::infer_lir_effects(erased);
        assert(erased.memory_effects.borrowed_parameter == 0);
    }

    {
        LIR::LIR_Function partial("partial_boolean", 0);
        partial.register_count = 1;
        partial.register_types[0] = LIR::Type::Bool;
        partial.instructions.emplace_back(LIR::LIR_Op::LoadConst, LIR::Type::Bool, 0, VAL_TRUE);
        partial.instructions.emplace_back(LIR::LIR_Op::JumpIf, LIR::Type::Void, UINT32_MAX, 0, UINT32_MAX, 3);
        partial.instructions.emplace_back(LIR::LIR_Op::Return, LIR::Type::Bool, UINT32_MAX, 0, UINT32_MAX);
        partial.instructions.emplace_back(LIR::LIR_Op::Nop, LIR::Type::Void, UINT32_MAX);
        assert(!Memory::proven_scalar_leaf(partial)); // A reachable exit falls off as nil.
    }
    {
        LIR::LIR_Function invalid_capture("invalid_capture_contract",0);
        invalid_capture.inferred_effects.captures_mutated.insert(123);
        invalid_capture.instructions.emplace_back(LIR::LIR_Op::Return,LIR::Type::Void,UINT32_MAX,UINT32_MAX,UINT32_MAX);
        std::vector<std::string> errors;assert(!LIR::Verifier::verify(invalid_capture,errors));
        assert(std::any_of(errors.begin(),errors.end(),[](const auto& error){return error.find("Undeclared mutated capture")!=std::string::npos;}));
    }
    const std::string source = R"(
fn scalar(flag:bool):bool { if(flag){return true;}else{return false;} }
fn closed_scalar():bool { return false; }
fn closed_integer():int {return 2;}
fn closed_assign():bool {var answer=true;answer=false;return answer;}
fn closed_loop():bool {var running=true;while(running){running=false;}return running;}
fn closed_branch():bool {if(true){return false;}else{return true;}}
fn equals(flag:bool):bool { return flag==true; }
fn reassigned(flag:bool):bool {var answer=flag;if(flag){answer=false;}else{answer=true;}return answer;}
fn opaque(flag:bool):bool { print(flag); return flag; }
assert(scalar(true)); assert(scalar(false)==false);
assert(closed_scalar()==false);assert(closed_branch()==false);assert(closed_integer()==2);assert(closed_assign()==false);assert(closed_loop()==false);
var closed_alias=closed_scalar;assert(closed_alias()==false);
assert(equals(true));assert(equals(false)==false);
assert(reassigned(true)==false);assert(reassigned(false));
var scalar_alias=scalar; assert(scalar_alias(false)==false);
type Hook=fn([int]):nil;
frame Box {pub var cb:Hook; pub var data:[int]; pub fn invoke(){self.cb(self.data);}}
fn pending(box:Box):fn():nil {return fn():nil {box.invoke();};}
fn element(xs:[[int]]):[int] {return xs[0];}
fn lease_reuse(xs:[[int]]):int {
    var first=element(xs);first[0]=7;var prior=first[0];
    var second=element(xs);second[0]=7;return prior+second[0];
}
assert(lease_reuse([[7]])==14);
fn captured_lease_workers():int {
    var child:[int];var values=[[7]];child=element(values);var output=channel();
    concurrent(cores=4){task(i in 1..2){output.send(child[0]);}}
    var total=0;iter(value in output){total=total+value;}return total;
}
assert(captured_lease_workers()==14);
fn shared_scalar_workers():int {
    var count:atomic=0;var increment=fn(){count+=1;};
    concurrent(cores=2){task(i in 1..2){increment();}}
    return count;
}
assert(shared_scalar_workers()==2);
fn mutate_local_capture() {
    var values=[1];var change=fn(){values[0]=2;};change();assert(values[0]==2);
}
mutate_local_capture();

fn factory(x:[int]):fn():int {return fn():int {return x[0];};}
var xs=[[7]]; var child=element(xs); print(child[0]);
{var ys=[[9]]; child=element(ys);} print(child[0]);
child[0]=9;assert(child[0]==9);
var observer=factory(child); print(observer());
var absent={} as {str:[int]}; var maybe=absent["x"] as [int];
{maybe=absent["y"] as [int];} if(maybe==nil){maybe=[11];} print(maybe[0]);
fn identity(x:any):any {return x;}
var builtin_byte=_builtin_string_byte_at;
assert(builtin_byte("ABC",1)==66);
var builtin_slice=_builtin_substring;
assert(builtin_slice("ABC",1,3)=="BC");
fn invoke_builtin(action:any):int {return action("ABC",2);}
assert(invoke_builtin(builtin_byte)==67);
var erased=identity(2); print(erased==nil); print(identity(true)); print(identity(2.5));
)";
    Frontend::Scanner scanner(source); scanner.scanTokens();
    Frontend::Parser parser(scanner, false);
    auto ast = parser.parse(); assert(ast);
    auto typed = Frontend::TypeCheckerFactory::check_program(ast,source,"source_ownership.lm");
    stage("typechecking");
    assert(typed.success && typed.errors.empty());
    auto facts = ast->ownership_facts; assert(facts && facts->verified);
    std::map<const Frontend::AST::Node*, Memory::Identity> declaration_identities;
    for (const auto& statement : ast->statements)
        if (auto function = std::dynamic_pointer_cast<Frontend::AST::FunctionDeclaration>(statement)) {
            declaration_identities[function.get()] = function->memory_info.semantic_id;
            declaration_identities[function->body.get()] = function->body->memory_info.semantic_id;
        }
    auto checked = Frontend::MemoryCheckerFactory::check_program(ast,source,"source_ownership.lm");
    stage("memory checking");
    for (const auto& [declaration, identity] : declaration_identities)
        assert(identity && declaration->memory_info.semantic_id == identity);
    assert(checked.success && ast->ownership_facts == facts);
    LIR::Generator generator; generator.set_import_aliases(typed.import_aliases);
    generator.set_registered_modules(typed.registered_modules);
    auto wrapper = generator.generate_program(typed); assert(wrapper && !generator.has_errors());
    stage("LIR generation");
    auto& registry = LIR::FunctionRegistry::getInstance();
    auto lookup = [&](const std::string& suffix) -> LIR::LIR_Function* {
        for (const auto& name : registry.getFunctionNames())
            if (name == suffix || name.ends_with("." + suffix)) return registry.getFunction(name);
        return nullptr;
    };
    auto* element = lookup("element"); assert(element);
    auto* lease_reuse = lookup("lease_reuse"); assert(lease_reuse);
    bool first_created = false, first_released = false, reused = false;
    LIR::Reg first_handle = UINT32_MAX;
    for (const auto& instruction : lease_reuse->instructions) {
        if (instruction.op == LIR::LIR_Op::RefCreate) {
            if (!first_created) {first_created=true;first_handle=instruction.dst;}
            else reused |= first_released;
        }
        if (instruction.op == LIR::LIR_Op::RefRelease && instruction.a == first_handle) first_released = true;
    }
    assert(first_created && first_released && reused);
    auto* scalar = lookup("scalar"); assert(scalar);
    assert(!Memory::proven_scalar_leaf(*scalar));
    auto* closed_scalar = lookup("closed_scalar"); assert(closed_scalar);
    assert(Memory::runtime_regions_proven_unnecessary(*closed_scalar));
    auto* closed_integer = lookup("closed_integer"); assert(closed_integer);
    assert(Memory::runtime_regions_proven_unnecessary(*closed_integer));
    assert(Memory::scalar_return_kind(*closed_integer) == Memory::AOTValueKind::Integer);
    auto* closed_assign = lookup("closed_assign"); assert(closed_assign);
    assert(Memory::runtime_regions_proven_unnecessary(*closed_assign));
    assert(!Memory::proven_scalar_leaf(*closed_assign)); // Memory proof does not imply SSA placement.
    auto* closed_loop = lookup("closed_loop"); assert(closed_loop);
    assert(Memory::runtime_regions_proven_unnecessary(*closed_loop));
    auto* opaque = lookup("opaque"); assert(opaque);
    assert(!Memory::proven_scalar_leaf(*opaque));
    auto* reassigned = lookup("reassigned"); assert(reassigned);
    assert(!Memory::proven_scalar_leaf(*reassigned));
    assert(!Memory::proven_scalar_leaf(*element));
    assert(element->inferred_effects.return_projections == std::set<uint32_t>{0});
    auto* factory = lookup("factory"); assert(factory);
    assert(!factory->inferred_effects.returned_callables.empty());
    assert(!factory->inferred_effects.returned_capture_parameters.empty());
    bool captured_obligation = false, captured_mutation = false;
    for (const auto& name : registry.getFunctionNames()) {
        auto* function = registry.getFunction(name);
        if (!function || function->instructions.empty()) continue;
        captured_obligation |= !function->inferred_effects.captures_opaque.empty();
        captured_mutation |= !function->inferred_effects.captures_mutated.empty();
        auto restored = LIR::Serializer::deserialize(LIR::Serializer::serialize(*function));
        assert(restored.inferred_effects == function->inferred_effects);
        assert(restored.ownership_parameters == function->ownership_parameters);
        assert(restored.ownership_captures == function->ownership_captures);
        assert(restored.instructions.size() == function->instructions.size());
        for (size_t i=0;i<restored.instructions.size();++i) { assert(restored.instructions[i].op == function->instructions[i].op); assert(restored.instructions[i].ownership == function->instructions[i].ownership); assert(restored.instructions[i].imm == function->instructions[i].imm); }
        registry.registerFunction(name,std::make_unique<LIR::LIR_Function>(std::move(restored)));
    }
    assert(captured_obligation);
    assert(captured_mutation);
    auto restored = LIR::Serializer::deserialize(LIR::Serializer::serialize(*wrapper));
    std::set<LIR::LIR_Op> operations;
    for (const auto& instruction : restored.instructions) operations.insert(instruction.op);
    for (auto op : {LIR::LIR_Op::RefCreate,LIR::LIR_Op::RefResolve,LIR::LIR_Op::RefRelease,LIR::LIR_Op::RefMove}) assert(operations.count(op));
    Backend::VM::Register::RegisterVM vm; vm.execute(restored); vm.reset();
    stage("serialized VM execution");
#if defined(FYRA_AVAILABLE) && defined(__linux__) && defined(__x86_64__)
    for (int level=0;level<3;++level) {
        Backend::Fyra::FyraCompiler compiler;
        auto output = (std::filesystem::path(argv[1]) / ("source-o"+std::to_string(level))).string();
        auto result = compiler.compile_aot(restored,output,Backend::Fyra::Platform::Linux,
            Backend::Fyra::Architecture::X86_64,static_cast<Backend::Fyra::OptimizationLevel>(level));
        if (!result.success) throw std::runtime_error(result.error_message);
        stage(("Fyra O"+std::to_string(level)).c_str());
    }
#endif
    std::cout << "Source ownership serialization and execution passed\n";
}

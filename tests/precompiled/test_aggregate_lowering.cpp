#include "backend/native/aggregate_lowering.hh"
#include <cassert>
#include <iostream>
using namespace LM::LIR;
using namespace LM::Backend::Native;
int main() {
    LIR_Function factory("pair_factory", 2);
    factory.instructions.emplace_back(LIR_Op::TupleCreate, LM::LIR::Type::Ptr, 2, UINT32_MAX, UINT32_MAX, 2);
    factory.instructions.emplace_back(LIR_Op::LoadConst, LM::LIR::Type::I64, 3, BOX_INT(0));
    factory.instructions.emplace_back(LIR_Op::TupleSet, LM::LIR::Type::Void, 2, 3, 0);
    factory.instructions.emplace_back(LIR_Op::LoadConst, LM::LIR::Type::I64, 4, BOX_INT(1));
    factory.instructions.emplace_back(LIR_Op::TupleSet, LM::LIR::Type::Void, 2, 4, 1);
    factory.instructions.emplace_back(LIR_Op::Return, LM::LIR::Type::Ptr, UINT32_MAX, 2, UINT32_MAX);
    assert(immediate_pair_factory(factory));
    auto mutated = factory;
    mutated.instructions.insert(mutated.instructions.end()-1,
        LIR_Inst(LIR_Op::TupleSet, LM::LIR::Type::Void, 2, 4, 0));
    assert(!immediate_pair_factory(mutated));
    auto exposed = factory;
    LIR_Inst call(LIR_Op::Call, LM::LIR::Type::Void, UINT32_MAX, UINT32_MAX, UINT32_MAX);
    call.func_name="opaque"; call.call_args={2};
    exposed.instructions.insert(exposed.instructions.end()-1, call);
    assert(!immediate_pair_factory(exposed));

    LIR_Function caller("project", 0);
    LIR_Inst make(LIR_Op::Call, LM::LIR::Type::Ptr, 0, UINT32_MAX, UINT32_MAX);
    make.func_name="pair_factory";
    caller.instructions.push_back(make);
    caller.instructions.emplace_back(LIR_Op::Mov, LM::LIR::Type::Ptr, 1, 0, UINT32_MAX);
    caller.instructions.emplace_back(LIR_Op::LoadConst, LM::LIR::Type::I64, 2, BOX_INT(0));
    caller.instructions.emplace_back(LIR_Op::TupleGet, LM::LIR::Type::I64, 3, 1, 2);
    caller.instructions.emplace_back(LIR_Op::Return, LM::LIR::Type::I64, UINT32_MAX, 3, UINT32_MAX);
    assert(pair_result_is_projected(caller, 0));
    auto escaped=caller;
    escaped.instructions.back().a=1;
    assert(!pair_result_is_projected(escaped, 0));
    auto referenced=caller;
    referenced.instructions.insert(referenced.instructions.end()-1,
        LIR_Inst(LIR_Op::RefCreate, LM::LIR::Type::U64, 4, 1, UINT32_MAX));
    assert(!pair_result_is_projected(referenced, 0));
    auto overwritten=caller;
    overwritten.instructions.insert(overwritten.instructions.end()-1,
        LIR_Inst(LIR_Op::Mov, LM::LIR::Type::Ptr, 1, 0, UINT32_MAX));
    assert(!pair_result_is_projected(overwritten, 0));
    std::cout << "Pair proof rejects mutation, opaque exposure, escapes, references and reassignment\n";
}

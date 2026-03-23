#pragma once

#include "TransformPass.h"
#include "ir/Function.h"
#include "ir/Instruction.h"
#include "ir/Constant.h"
#include <map>
#include <set>
#include <vector>
#include <limits>
#include <memory>

namespace transforms {

class SCCP : public TransformPass {
public:
    explicit SCCP(std::shared_ptr<ErrorReporter> error_reporter = nullptr)
        : TransformPass("Enhanced SCCP", error_reporter) {}

    bool run(ir::Function& func) {
        return TransformPass::run(func);
    }

protected:
    bool performTransformation(ir::Function& func) override;
    bool validatePreconditions(ir::Function& func) override;

private:
    enum LatticeValue {
        Top,
        Constant,
        Bottom
    };

    struct LatticeEntry {
        LatticeValue type = Top;
        ir::Constant* constant = nullptr;
    };

    void initialize(ir::Function& func);
    void visit(ir::Instruction* instr, std::set<std::pair<ir::BasicBlock*, ir::BasicBlock*>>& executableEdges, std::set<ir::BasicBlock*>& executableBlocks);
    LatticeEntry getLatticeValue(ir::Value* val);
    void setLatticeValue(ir::Instruction* instr, LatticeEntry new_val);
    
    std::map<ir::Value*, LatticeEntry> lattice;
    std::vector<ir::Instruction*> instructionWorklist;
    std::vector<ir::BasicBlock*> blockWorklist;
};

} // namespace transforms

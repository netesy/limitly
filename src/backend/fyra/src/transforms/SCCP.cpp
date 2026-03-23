#include "transforms/SCCP.h"
#include "ir/BasicBlock.h"
#include "ir/Use.h"
#include "ir/Type.h"
#include "ir/Instruction.h"
#include "ir/Constant.h"
#include "ir/Module.h"
#include "ir/PhiNode.h"
#include <iostream>
#include <set>
#include <map>
#include <vector>

namespace transforms {

bool SCCP::performTransformation(ir::Function& func) {
    this->initialize(func);
    
    std::set<ir::BasicBlock*> executableBlocks;
    std::set<std::pair<ir::BasicBlock*, ir::BasicBlock*>> executableEdges;
    
    if (func.getBasicBlocks().empty()) return false;
    ir::BasicBlock* entry = func.getBasicBlocks().front().get();
    if (!entry) return false;
    
    blockWorklist.push_back(entry);

    while (!blockWorklist.empty() || !instructionWorklist.empty()) {
        while (!blockWorklist.empty()) {
            ir::BasicBlock* bb = blockWorklist.back();
            blockWorklist.pop_back();
            
            if (executableBlocks.insert(bb).second) {
                for (auto& instr : bb->getInstructions()) {
                    if (instr) this->visit(instr.get(), executableEdges, executableBlocks);
                }
            }
        }
        
        if (!instructionWorklist.empty()) {
            ir::Instruction* instr = instructionWorklist.back();
            instructionWorklist.pop_back();
            if (instr && instr->getParent() && executableBlocks.count(instr->getParent())) {
                this->visit(instr, executableEdges, executableBlocks);
            }
        }
    }

    bool changed = false;
    for (auto& bb_ptr : func.getBasicBlocks()) {
        ir::BasicBlock* bb = bb_ptr.get();
        if (!bb || !executableBlocks.count(bb)) continue;
        
        auto& instrs = bb->getInstructions();
        auto it = instrs.begin();
        while (it != instrs.end()) {
            ir::Instruction* instr = it->get();
            if (!instr) { it = instrs.erase(it); continue; }
            
            ir::Instruction::Opcode op = instr->getOpcode();
            if (op == ir::Instruction::Ret || op == ir::Instruction::Br || 
                op == ir::Instruction::Jmp || op == ir::Instruction::Jnz || 
                op == ir::Instruction::Jz || op == ir::Instruction::Phi) {
                ++it;
                continue;
            }

            auto entry = getLatticeValue(instr);
            if (entry.type == Constant && entry.constant) {
                if (instr->getType() && !instr->getType()->isVoidTy()) {
                    instr->replaceAllUsesWith(entry.constant);
                    it = instrs.erase(it);
                    changed = true;
                    continue;
                }
            }
            ++it;
        }
    }
    return changed;
}

void SCCP::initialize(ir::Function& func) {
    lattice.clear();
    instructionWorklist.clear();
    blockWorklist.clear();
    for (auto& bb_ptr : func.getBasicBlocks()) {
        ir::BasicBlock* bb = bb_ptr.get();
        if (!bb) continue;
        for (auto& instr : bb->getInstructions()) {
            if (instr && instr->getType() && !instr->getType()->isVoidTy()) {
                lattice[instr.get()] = LatticeEntry{Top, nullptr};
            }
        }
    }
}

SCCP::LatticeEntry SCCP::getLatticeValue(ir::Value* val) {
    if (!val) return LatticeEntry{Bottom, nullptr};
    if (auto* ci = dynamic_cast<ir::ConstantInt*>(val)) return LatticeEntry{Constant, ci};
    if (auto* cf = dynamic_cast<ir::ConstantFP*>(val)) return LatticeEntry{Constant, cf};
    auto it = lattice.find(val);
    if (it != lattice.end()) return it->second;
    return LatticeEntry{Bottom, nullptr};
}

void SCCP::setLatticeValue(ir::Instruction* instr, LatticeEntry new_val) {
    if (!instr || !instr->getType() || instr->getType()->isVoidTy()) return;
    
    LatticeEntry old_val = LatticeEntry{Top, nullptr};
    auto it = lattice.find(instr);
    if (it != lattice.end()) old_val = it->second;
    else lattice[instr] = old_val;

    if (old_val.type == Bottom) return;
    if (new_val.type == Top) return;
    if (old_val.type == Constant && new_val.type == Top) return;
    if (old_val.type == new_val.type && old_val.constant == new_val.constant) return;

    if (new_val.type == Top) return;
    if (old_val.type == Bottom) return;
    if (old_val.type == Constant && new_val.type == Constant) {
        auto* ci1 = dynamic_cast<ir::ConstantInt*>(old_val.constant);
        auto* ci2 = dynamic_cast<ir::ConstantInt*>(new_val.constant);
        if (ci1 && ci2 && ci1->getValue() == ci2->getValue()) return;
    }
    lattice[instr] = new_val;
    for (auto& use : instr->getUseList()) {
        if (use && use->getUser()) {
            if (auto* user_instr = dynamic_cast<ir::Instruction*>(use->getUser())) {
                bool found = false;
                // Speed up check with a limit or a set if it gets too slow
                for (auto* item : instructionWorklist) if (item == user_instr) { found = true; break; }
                if (!found) instructionWorklist.push_back(user_instr);
            }
        }
    }
}

void SCCP::visit(ir::Instruction* instr, std::set<std::pair<ir::BasicBlock*, ir::BasicBlock*>>& executableEdges, std::set<ir::BasicBlock*>& executableBlocks) {
    if (!instr) return;
    switch (instr->getOpcode()) {
        case ir::Instruction::Phi: {
            ir::PhiNode* phi = dynamic_cast<ir::PhiNode*>(instr);
            if (!phi) break;
            LatticeEntry res = LatticeEntry{Top, nullptr};
            auto& ops = phi->getOperands();
            bool hasExecutablePredecessor = false;
            for (size_t i = 0; i + 1 < ops.size(); i += 2) {
                ir::BasicBlock* pred = dynamic_cast<ir::BasicBlock*>(ops[i]->get());
                if (pred && executableEdges.count({pred, phi->getParent()})) {
                    hasExecutablePredecessor = true;
                    auto val = getLatticeValue(ops[i+1]->get());
                    if (val.type == Bottom) { res = LatticeEntry{Bottom, nullptr}; break; }
                    if (val.type == Constant && val.constant) {
                        if (res.type == Top) res = val;
                        else if (res.constant != val.constant) {
                            auto* ci1 = dynamic_cast<ir::ConstantInt*>(res.constant);
                            auto* ci2 = dynamic_cast<ir::ConstantInt*>(val.constant);
                            if (ci1 && ci2 && ci1->getValue() == ci2->getValue()) {
                                // Same value, stay constant
                            } else {
                                res = LatticeEntry{Bottom, nullptr}; break;
                            }
                        }
                    }
                }
            }
            if (!hasExecutablePredecessor) res = LatticeEntry{Top, nullptr};
            setLatticeValue(instr, res);
            break;
        }
        case ir::Instruction::Copy:
            if (!instr->getOperands().empty() && instr->getOperands()[0]) {
                setLatticeValue(instr, getLatticeValue(instr->getOperands()[0]->get()));
            }
            break;
        case ir::Instruction::Add:
        case ir::Instruction::Sub:
        case ir::Instruction::Mul:
        case ir::Instruction::Div:
        case ir::Instruction::Udiv:
        case ir::Instruction::Rem:
        case ir::Instruction::Urem:
        case ir::Instruction::And:
        case ir::Instruction::Or:
        case ir::Instruction::Xor:
        case ir::Instruction::Shl:
        case ir::Instruction::Shr:
        case ir::Instruction::Sar:
        case ir::Instruction::Ceq:
        case ir::Instruction::Cne:
        case ir::Instruction::Cslt:
        case ir::Instruction::Csle:
        case ir::Instruction::Csgt:
        case ir::Instruction::Csge:
        case ir::Instruction::Cult:
        case ir::Instruction::Cule:
        case ir::Instruction::Cugt:
        case ir::Instruction::Cuge:
        {
            if (instr->getOperands().size() < 2 || !instr->getOperands()[0] || !instr->getOperands()[1]) {
                if (instr->getType() && !instr->getType()->isVoidTy()) setLatticeValue(instr, LatticeEntry{Bottom, nullptr});
                break;
            }
            auto l = getLatticeValue(instr->getOperands()[0]->get());
            auto r = getLatticeValue(instr->getOperands()[1]->get());
            
            if (l.type == Bottom || r.type == Bottom) {
                setLatticeValue(instr, LatticeEntry{Bottom, nullptr});
            } else if (l.type == Constant && r.type == Constant) {
                auto* lc = dynamic_cast<ir::ConstantInt*>(l.constant);
                auto* rc = dynamic_cast<ir::ConstantInt*>(r.constant);
                if (lc && rc) {
                    int64_t v = 0;
                    bool possible = true;
                    ir::Instruction::Opcode op = instr->getOpcode();
                    switch (op) {
                        case ir::Instruction::Add: v = lc->getValue() + rc->getValue(); break;
                        case ir::Instruction::Sub: v = lc->getValue() - rc->getValue(); break;
                        case ir::Instruction::Mul: v = lc->getValue() * rc->getValue(); break;
                        case ir::Instruction::Div: if (rc->getValue() != 0) v = lc->getValue() / rc->getValue(); else possible = false; break;
                        case ir::Instruction::Udiv: if (rc->getValue() != 0) v = (uint64_t)lc->getValue() / (uint64_t)rc->getValue(); else possible = false; break;
                        case ir::Instruction::Rem: if (rc->getValue() != 0) v = lc->getValue() % rc->getValue(); else possible = false; break;
                        case ir::Instruction::Urem: if (rc->getValue() != 0) v = (uint64_t)lc->getValue() % (uint64_t)rc->getValue(); else possible = false; break;
                        case ir::Instruction::And: v = lc->getValue() & rc->getValue(); break;
                        case ir::Instruction::Or:  v = lc->getValue() | rc->getValue(); break;
                        case ir::Instruction::Xor: v = lc->getValue() ^ rc->getValue(); break;
                        case ir::Instruction::Shl: v = lc->getValue() << (rc->getValue() & 63); break;
                        case ir::Instruction::Shr: v = (uint64_t)lc->getValue() >> (rc->getValue() & 63); break;
                        case ir::Instruction::Sar: v = lc->getValue() >> (rc->getValue() & 63); break;
                        case ir::Instruction::Ceq: v = lc->getValue() == rc->getValue(); break;
                        case ir::Instruction::Cne: v = lc->getValue() != rc->getValue(); break;
                        case ir::Instruction::Cslt: v = lc->getValue() < rc->getValue(); break;
                        case ir::Instruction::Csle: v = lc->getValue() <= rc->getValue(); break;
                        case ir::Instruction::Csgt: v = lc->getValue() > rc->getValue(); break;
                        case ir::Instruction::Csge: v = lc->getValue() >= rc->getValue(); break;
                        case ir::Instruction::Cult: v = (uint64_t)lc->getValue() < (uint64_t)rc->getValue(); break;
                        case ir::Instruction::Cule: v = (uint64_t)lc->getValue() <= (uint64_t)rc->getValue(); break;
                        case ir::Instruction::Cugt: v = (uint64_t)lc->getValue() > (uint64_t)rc->getValue(); break;
                        case ir::Instruction::Cuge: v = (uint64_t)lc->getValue() >= (uint64_t)rc->getValue(); break;
                        default: break;
                    }
                    if (possible) setLatticeValue(instr, LatticeEntry{Constant, ir::ConstantInt::get(static_cast<ir::IntegerType*>(instr->getType()), v)});
                    else setLatticeValue(instr, LatticeEntry{Bottom, nullptr});
                } else setLatticeValue(instr, LatticeEntry{Bottom, nullptr});
            }
            break;
        }
        case ir::Instruction::Jmp: {
            if (instr->getOperands().empty() || !instr->getOperands()[0]) break;
            ir::BasicBlock* target = dynamic_cast<ir::BasicBlock*>(instr->getOperands()[0]->get());
            if (target) {
                if (executableEdges.insert({instr->getParent(), target}).second) {
                    if (executableBlocks.count(target)) {
                        for (auto& t_instr : target->getInstructions()) {
                            if (t_instr && t_instr->getOpcode() == ir::Instruction::Phi) {
                                bool found = false;
                                for (auto* item : instructionWorklist) if (item == t_instr.get()) { found = true; break; }
                                if (!found) instructionWorklist.push_back(t_instr.get());
                            }
                            else break;
                        }
                    } else blockWorklist.push_back(target);
                }
            }
            break;
        }
        case ir::Instruction::Br:
        case ir::Instruction::Jnz:
        case ir::Instruction::Jz: {
            if (instr->getOperands().empty() || !instr->getOperands()[0]) break;
            auto cond = getLatticeValue(instr->getOperands()[0]->get());
            ir::BasicBlock* trueDest = (instr->getOperands().size() > 1) ? dynamic_cast<ir::BasicBlock*>(instr->getOperands()[1]->get()) : nullptr;
            ir::BasicBlock* falseDest = (instr->getOperands().size() > 2) ? dynamic_cast<ir::BasicBlock*>(instr->getOperands()[2]->get()) : nullptr;
            
            auto mark = [&](ir::BasicBlock* d) {
                if (d && executableEdges.insert({instr->getParent(), d}).second) {
                    if (executableBlocks.count(d)) {
                        for (auto& t_instr : d->getInstructions()) {
                            if (t_instr && t_instr->getOpcode() == ir::Instruction::Phi) {
                                bool found = false;
                                for (auto* item : instructionWorklist) if (item == t_instr.get()) { found = true; break; }
                                if (!found) instructionWorklist.push_back(t_instr.get());
                            }
                            else break;
                        }
                    } else blockWorklist.push_back(d);
                }
            };

            if (cond.type == Constant && cond.constant) {
                auto* cc = dynamic_cast<ir::ConstantInt*>(cond.constant);
                if (cc) {
                    bool condition = cc->getValue() != 0;
                    if (instr->getOpcode() == ir::Instruction::Jz) condition = !condition;
                    
                    if (condition) mark(trueDest);
                    else mark(falseDest);
                }
            } else if (cond.type == Bottom) {
                mark(trueDest);
                mark(falseDest);
            }
            break;
        }
        default:
            if (instr->getType() && !instr->getType()->isVoidTy()) setLatticeValue(instr, LatticeEntry{Bottom, nullptr});
            break;
    }
}

bool SCCP::validatePreconditions(ir::Function& f) { return !f.getBasicBlocks().empty(); }

} // namespace transforms

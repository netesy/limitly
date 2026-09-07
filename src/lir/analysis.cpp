#include "analysis.hh"
#include <queue>
#include <algorithm>

namespace LM {
namespace LIR {

// ============================================================================
// CFGAnalysis Implementation
// ============================================================================

CFGAnalysis::CFGAnalysis(const LIR_Function& func) : func_(func) {}

void CFGAnalysis::analyze() {
    blocks_.clear();
    inst_to_block_.clear();
    label_imm_to_block_.clear();

    const auto& insts = func_.instructions;
    if (insts.empty()) return;

    inst_to_block_.resize(insts.size(), UINT32_MAX);

    // Step 1: Identify basic block boundaries
    std::unordered_set<size_t> block_starts;
    block_starts.insert(0);

    for (size_t i = 0; i < insts.size(); ++i) {
        const auto& inst = insts[i];
        if (inst.op == LIR_Op::Label) {
            block_starts.insert(i);
        } else if (inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse) {
            if (i + 1 < insts.size()) block_starts.insert(i + 1);
        } else if (inst.op == LIR_Op::Return || inst.op == LIR_Op::Ret) {
            if (i + 1 < insts.size()) block_starts.insert(i + 1);
        }
    }

    std::vector<size_t> sorted_starts(block_starts.begin(), block_starts.end());
    std::sort(sorted_starts.begin(), sorted_starts.end());

    // Step 2: Construct basic blocks
    for (size_t b = 0; b < sorted_starts.size(); ++b) {
        size_t start = sorted_starts[b];
        size_t end = (b + 1 < sorted_starts.size()) ? sorted_starts[b + 1] : insts.size();

        AnalysisBlock ab;
        ab.id = static_cast<uint32_t>(b);
        ab.start_inst_idx = start;
        ab.end_inst_idx = end;

        if (insts[start].op == LIR_Op::Label) {
            ab.label = std::to_string(insts[start].imm);
            label_imm_to_block_[static_cast<uint32_t>(insts[start].imm)] = ab.id;
        }

        for (size_t i = start; i < end; ++i) {
            inst_to_block_[i] = ab.id;
        }

        blocks_.push_back(ab);
    }

    if (!blocks_.empty()) {
        blocks_[0].is_entry = true;
    }

    // Map labels that might appear inside blocks if any (or first inst)
    for (size_t i = 0; i < insts.size(); ++i) {
        if (insts[i].op == LIR_Op::Label) {
            label_imm_to_block_[static_cast<uint32_t>(insts[i].imm)] = inst_to_block_[i];
        }
    }

    // Step 3: Compute successors & predecessors
    for (auto& block : blocks_) {
        if (block.start_inst_idx >= block.end_inst_idx) continue;
        const auto& last_inst = insts[block.end_inst_idx - 1];

        if (last_inst.op == LIR_Op::Jump) {
            uint32_t target_label = static_cast<uint32_t>(last_inst.imm);
            uint32_t target_block = get_block_by_label_imm(target_label);
            if (target_block != UINT32_MAX) {
                block.successors.push_back(target_block);
            }
        } else if (last_inst.op == LIR_Op::JumpIf || last_inst.op == LIR_Op::JumpIfFalse) {
            uint32_t target_label = static_cast<uint32_t>(last_inst.imm);
            uint32_t target_block = get_block_by_label_imm(target_label);
            if (target_block != UINT32_MAX) {
                block.successors.push_back(target_block);
            }
            if (block.id + 1 < blocks_.size()) {
                block.successors.push_back(block.id + 1);
            }
        } else if (last_inst.op == LIR_Op::Return || last_inst.op == LIR_Op::Ret) {
            block.is_exit = true;
        } else {
            // Linear fallthrough
            if (block.id + 1 < blocks_.size()) {
                block.successors.push_back(block.id + 1);
            } else {
                block.is_exit = true;
            }
        }
    }

    for (const auto& block : blocks_) {
        for (uint32_t succ_id : block.successors) {
            if (succ_id < blocks_.size()) {
                blocks_[succ_id].predecessors.push_back(block.id);
            }
        }
    }

    // Step 4: Reachability
    if (!blocks_.empty()) {
        std::queue<uint32_t> q;
        q.push(0);
        blocks_[0].reachable = true;

        while (!q.empty()) {
            uint32_t curr = q.front();
            q.pop();

            for (uint32_t succ : blocks_[curr].successors) {
                if (!blocks_[succ].reachable) {
                    blocks_[succ].reachable = true;
                    q.push(succ);
                }
            }
        }
    }
}

// ============================================================================
// DominatorAnalysis Implementation
// ============================================================================

DominatorAnalysis::DominatorAnalysis(const LIR_Function& func, const CFGAnalysis& cfg)
    : func_(func), cfg_(cfg) {}

void DominatorAnalysis::analyze() {
    const auto& blocks = cfg_.get_blocks();
    size_t n = blocks.size();
    idom_.assign(n, UINT32_MAX);
    dom_tree_.assign(n, {});
    rpo_number_.assign(n, UINT32_MAX);
    rpo_order_.clear();

    if (n == 0 || !blocks[0].reachable) return;

    // Compute Reverse Post-Order (RPO)
    std::vector<bool> visited(n, false);
    std::vector<uint32_t> post_order;

    auto dfs = [&](auto& self, uint32_t b) -> void {
        visited[b] = true;
        for (uint32_t succ : blocks[b].successors) {
            if (!visited[succ] && blocks[succ].reachable) {
                self(self, succ);
            }
        }
        post_order.push_back(b);
    };

    dfs(dfs, 0);

    for (auto it = post_order.rbegin(); it != post_order.rend(); ++it) {
        rpo_number_[*it] = static_cast<uint32_t>(rpo_order_.size());
        rpo_order_.push_back(*it);
    }

    // Iterative Cooper-Harvey-Kennedy dominator tree computation using RPO numbers
    idom_[0] = 0;

    auto intersect = [&](uint32_t b1, uint32_t b2) {
        uint32_t finger1 = b1;
        uint32_t finger2 = b2;
        while (finger1 != finger2) {
            while (rpo_number_[finger1] > rpo_number_[finger2]) finger1 = idom_[finger1];
            while (rpo_number_[finger2] > rpo_number_[finger1]) finger2 = idom_[finger2];
        }
        return finger1;
    };

    bool changed = true;
    while (changed) {
        changed = false;
        for (uint32_t b : rpo_order_) {
            if (b == 0) continue;

            uint32_t new_idom = UINT32_MAX;
            for (uint32_t pred : blocks[b].predecessors) {
                if (idom_[pred] != UINT32_MAX) {
                    if (new_idom == UINT32_MAX) {
                        new_idom = pred;
                    } else {
                        new_idom = intersect(pred, new_idom);
                    }
                }
            }

            if (new_idom != UINT32_MAX && idom_[b] != new_idom) {
                idom_[b] = new_idom;
                changed = true;
            }
        }
    }

    for (size_t i = 1; i < n; ++i) {
        if (idom_[i] != UINT32_MAX && idom_[i] != i) {
            dom_tree_[idom_[i]].push_back(static_cast<uint32_t>(i));
        }
    }
}

bool DominatorAnalysis::dominates(uint32_t a, uint32_t b) const {
    if (a == b) return true;
    if (b >= idom_.size() || idom_[b] == UINT32_MAX) return false;

    uint32_t curr = b;
    while (curr != 0 && curr != UINT32_MAX) {
        if (curr == a) return true;
        uint32_t next = idom_[curr];
        if (next == curr) break;
        curr = next;
    }
    return curr == a;
}

uint32_t DominatorAnalysis::get_idom(uint32_t b) const {
    return (b < idom_.size()) ? idom_[b] : UINT32_MAX;
}

const std::vector<uint32_t>& DominatorAnalysis::get_dom_tree_children(uint32_t b) const {
    static const std::vector<uint32_t> empty;
    return (b < dom_tree_.size()) ? dom_tree_[b] : empty;
}

// ============================================================================
// LoopAnalysis Implementation
// ============================================================================

LoopAnalysis::LoopAnalysis(const LIR_Function& func, const CFGAnalysis& cfg, const DominatorAnalysis& dom)
    : func_(func), cfg_(cfg), dom_(dom) {}

void LoopAnalysis::analyze() {
    loops_.clear();
    block_to_loop_.clear();

    const auto& blocks = cfg_.get_blocks();
    std::unordered_map<uint32_t, std::vector<uint32_t>> header_back_edges;

    // Detect back-edges (succ dominates pred)
    for (const auto& block : blocks) {
        if (!block.reachable) continue;
        for (uint32_t succ : block.successors) {
            if (dom_.dominates(succ, block.id)) {
                header_back_edges[succ].push_back(block.id);
            }
        }
    }

    // Construct natural loop for each header
    for (const auto& [header_id, back_preds] : header_back_edges) {
        LoopInfo loop;
        loop.header_id = header_id;
        loop.body_blocks.insert(header_id);

        for (uint32_t pred : back_preds) {
            loop.back_edges.push_back({pred, header_id});
            loop.body_blocks.insert(pred);

            std::queue<uint32_t> q;
            q.push(pred);

            while (!q.empty()) {
                uint32_t curr = q.front();
                q.pop();

                const auto* curr_block = cfg_.get_block(curr);
                if (!curr_block) continue;

                for (uint32_t p : curr_block->predecessors) {
                    if (loop.body_blocks.find(p) == loop.body_blocks.end()) {
                        loop.body_blocks.insert(p);
                        q.push(p);
                    }
                }
            }
        }

        loops_.push_back(loop);
    }

    // Determine nesting hierarchy
    for (size_t i = 0; i < loops_.size(); ++i) {
        for (size_t j = 0; j < loops_.size(); ++j) {
            if (i == j) continue;
            bool contains = true;
            for (uint32_t b : loops_[j].body_blocks) {
                if (loops_[i].body_blocks.find(b) == loops_[i].body_blocks.end()) {
                    contains = false;
                    break;
                }
            }
            if (contains) {
                if (loops_[j].parent_loop_id == -1 ||
                    loops_[loops_[j].parent_loop_id].body_blocks.size() > loops_[i].body_blocks.size()) {
                    loops_[j].parent_loop_id = static_cast<int>(i);
                }
            }
        }
    }

    for (size_t i = 0; i < loops_.size(); ++i) {
        if (loops_[i].parent_loop_id != -1) {
            loops_[loops_[i].parent_loop_id].sub_loops.push_back(static_cast<int>(i));
        }
    }

    for (size_t i = 0; i < loops_.size(); ++i) {
        for (uint32_t b : loops_[i].body_blocks) {
            if (block_to_loop_.find(b) == block_to_loop_.end() ||
                loops_[block_to_loop_[b]].body_blocks.size() > loops_[i].body_blocks.size()) {
                block_to_loop_[b] = static_cast<int>(i);
            }
        }
    }
}

bool LoopAnalysis::is_in_loop(uint32_t b) const {
    return block_to_loop_.find(b) != block_to_loop_.end();
}

int LoopAnalysis::get_loop_for_block(uint32_t b) const {
    auto it = block_to_loop_.find(b);
    return (it != block_to_loop_.end()) ? it->second : -1;
}

// ============================================================================
// DefUseAnalysis Implementation
// ============================================================================

DefUseAnalysis::DefUseAnalysis(const LIR_Function& func) : func_(func) {}

void DefUseAnalysis::analyze() {
    defs_.clear();
    uses_.clear();

    const auto& insts = func_.instructions;
    for (size_t i = 0; i < insts.size(); ++i) {
        const auto& inst = insts[i];

        if (inst.dst != UINT32_MAX && !inst.isReturn() &&
            inst.op != LIR_Op::Jump && inst.op != LIR_Op::JumpIf && inst.op != LIR_Op::JumpIfFalse) {
            defs_[inst.dst] = DefInfo{i, inst.dst, inst.op};
        }

        if (inst.a != UINT32_MAX) {
            uses_[inst.a].push_back(UseInfo{i, inst.a, UseInfo::Role::OperandA});
        }
        if (inst.b != UINT32_MAX) {
            uses_[inst.b].push_back(UseInfo{i, inst.b, UseInfo::Role::OperandB});
        }
        for (Reg arg : inst.call_args) {
            if (arg != UINT32_MAX) {
                uses_[arg].push_back(UseInfo{i, arg, UseInfo::Role::CallArg});
            }
        }
        if ((inst.op == LIR_Op::JumpIf || inst.op == LIR_Op::JumpIfFalse || inst.isReturn()) && inst.dst != UINT32_MAX) {
            uses_[inst.dst].push_back(UseInfo{i, inst.dst, UseInfo::Role::Condition});
        }
    }
}

bool DefUseAnalysis::has_definition(Reg reg) const {
    return defs_.find(reg) != defs_.end();
}

const DefInfo* DefUseAnalysis::get_definition(Reg reg) const {
    auto it = defs_.find(reg);
    return (it != defs_.end()) ? &it->second : nullptr;
}

const std::vector<UseInfo>& DefUseAnalysis::get_uses(Reg reg) const {
    static const std::vector<UseInfo> empty;
    auto it = uses_.find(reg);
    return (it != uses_.end()) ? it->second : empty;
}

size_t DefUseAnalysis::get_use_count(Reg reg) const {
    auto it = uses_.find(reg);
    return (it != uses_.end()) ? it->second.size() : 0;
}

bool DefUseAnalysis::has_side_effects(const LIR_Inst& inst) {
    return (
        inst.op == LIR_Op::Call || inst.op == LIR_Op::CallVoid ||
        inst.op == LIR_Op::CallIndirect || inst.op == LIR_Op::CallBuiltin ||
        inst.op == LIR_Op::CallVariadic ||
        inst.op == LIR_Op::Return || inst.op == LIR_Op::Ret ||
        inst.op == LIR_Op::Jump || inst.op == LIR_Op::JumpIf ||
        inst.op == LIR_Op::JumpIfFalse ||
        inst.op == LIR_Op::Label || inst.op == LIR_Op::Store ||
        inst.op == LIR_Op::MemoryStore ||
        inst.op == LIR_Op::ChannelSend || inst.op == LIR_Op::ChannelRecv ||
        inst.op == LIR_Op::ChannelClose || inst.op == LIR_Op::Await ||
        inst.op == LIR_Op::AsyncCall
    );
}

bool DefUseAnalysis::is_pure(const LIR_Inst& inst) {
    return !has_side_effects(inst);
}

// ============================================================================
// AnalysisManager Implementation
// ============================================================================

const CFGAnalysis& AnalysisManager::get_cfg() {
    if (!cfg_valid_ || !cfg_) {
        cfg_ = std::make_unique<CFGAnalysis>(func_);
        cfg_->analyze();
        cfg_valid_ = true;
    }
    return *cfg_;
}

const DominatorAnalysis& AnalysisManager::get_dom() {
    if (!dom_valid_ || !dom_) {
        dom_ = std::make_unique<DominatorAnalysis>(func_, get_cfg());
        dom_->analyze();
        dom_valid_ = true;
    }
    return *dom_;
}

const LoopAnalysis& AnalysisManager::get_loops() {
    if (!loops_valid_ || !loops_) {
        loops_ = std::make_unique<LoopAnalysis>(func_, get_cfg(), get_dom());
        loops_->analyze();
        loops_valid_ = true;
    }
    return *loops_;
}

const DefUseAnalysis& AnalysisManager::get_def_use() {
    if (!def_use_valid_ || !def_use_) {
        def_use_ = std::make_unique<DefUseAnalysis>(func_);
        def_use_->analyze();
        def_use_valid_ = true;
    }
    return *def_use_;
}

} // namespace LIR
} // namespace LM

#pragma once

#include "lir.hh"
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <memory>
#include <iostream>

namespace LM {
namespace LIR {

// ============================================================================
// CFG Analysis
// ============================================================================

struct AnalysisBlock {
    uint32_t id;
    std::string label;
    size_t start_inst_idx;
    size_t end_inst_idx; // exclusive
    std::vector<uint32_t> successors;
    std::vector<uint32_t> predecessors;
    bool is_entry = false;
    bool is_exit = false;
    bool reachable = false;
};

class CFGAnalysis {
public:
    explicit CFGAnalysis(const LIR_Function& func);

    void analyze();

    const std::vector<AnalysisBlock>& get_blocks() const { return blocks_; }
    const AnalysisBlock* get_block(uint32_t id) const {
        return (id < blocks_.size()) ? &blocks_[id] : nullptr;
    }
    uint32_t get_block_for_inst(size_t inst_idx) const {
        if (inst_idx < inst_to_block_.size()) return inst_to_block_[inst_idx];
        return UINT32_MAX;
    }
    uint32_t get_block_by_label_imm(uint32_t label_imm) const {
        auto it = label_imm_to_block_.find(label_imm);
        return (it != label_imm_to_block_.end()) ? it->second : UINT32_MAX;
    }

private:
    const LIR_Function& func_;
    std::vector<AnalysisBlock> blocks_;
    std::vector<uint32_t> inst_to_block_;
    std::unordered_map<uint32_t, uint32_t> label_imm_to_block_;
};

// ============================================================================
// Dominator Analysis
// ============================================================================

class DominatorAnalysis {
public:
    DominatorAnalysis(const LIR_Function& func, const CFGAnalysis& cfg);

    void analyze();

    bool dominates(uint32_t block_a, uint32_t block_b) const;
    uint32_t get_idom(uint32_t block_id) const;
    const std::vector<uint32_t>& get_dom_tree_children(uint32_t block_id) const;

private:
    const LIR_Function& func_;
    const CFGAnalysis& cfg_;
    std::vector<uint32_t> idom_;
    std::vector<std::vector<uint32_t>> dom_tree_;
    std::vector<uint32_t> rpo_number_;
    std::vector<uint32_t> rpo_order_;
};

// ============================================================================
// Loop Analysis
// ============================================================================

struct LoopInfo {
    uint32_t header_id;
    std::unordered_set<uint32_t> body_blocks;
    std::vector<std::pair<uint32_t, uint32_t>> back_edges; // (from, header)
    int parent_loop_id = -1;
    std::vector<int> sub_loops;
};

class LoopAnalysis {
public:
    LoopAnalysis(const LIR_Function& func, const CFGAnalysis& cfg, const DominatorAnalysis& dom);

    void analyze();

    const std::vector<LoopInfo>& get_loops() const { return loops_; }
    bool is_in_loop(uint32_t block_id) const;
    int get_loop_for_block(uint32_t block_id) const;

private:
    const LIR_Function& func_;
    const CFGAnalysis& cfg_;
    const DominatorAnalysis& dom_;
    std::vector<LoopInfo> loops_;
    std::unordered_map<uint32_t, int> block_to_loop_;
};

// ============================================================================
// Def-Use Analysis & Side-Effect Safety Classification
// ============================================================================

struct DefInfo {
    size_t inst_idx;
    Reg reg;
    LIR_Op op;
};

struct UseInfo {
    size_t inst_idx;
    Reg reg;
    enum class Role { OperandA, OperandB, CallArg, Condition } role;
};

class DefUseAnalysis {
public:
    explicit DefUseAnalysis(const LIR_Function& func);

    void analyze();

    bool has_definition(Reg reg) const;
    const DefInfo* get_definition(Reg reg) const;
    const std::vector<UseInfo>& get_uses(Reg reg) const;
    size_t get_use_count(Reg reg) const;

    static bool is_pure(const LIR_Inst& inst);
    static bool has_side_effects(const LIR_Inst& inst);

private:
    const LIR_Function& func_;
    std::unordered_map<Reg, DefInfo> defs_;
    std::unordered_map<Reg, std::vector<UseInfo>> uses_;
};

// ============================================================================
// Analysis Manager
// ============================================================================

class AnalysisManager {
public:
    explicit AnalysisManager(const LIR_Function& func) : func_(func) {}

    const CFGAnalysis& get_cfg();
    const DominatorAnalysis& get_dom();
    const LoopAnalysis& get_loops();
    const DefUseAnalysis& get_def_use();

    void invalidate_cfg() { cfg_valid_ = dom_valid_ = loops_valid_ = false; }
    void invalidate_def_use() { def_use_valid_ = false; }
    void invalidate_all() { cfg_valid_ = dom_valid_ = loops_valid_ = def_use_valid_ = false; }

private:
    const LIR_Function& func_;

    bool cfg_valid_ = false;
    bool dom_valid_ = false;
    bool loops_valid_ = false;
    bool def_use_valid_ = false;

    std::unique_ptr<CFGAnalysis> cfg_;
    std::unique_ptr<DominatorAnalysis> dom_;
    std::unique_ptr<LoopAnalysis> loops_;
    std::unique_ptr<DefUseAnalysis> def_use_;
};

} // namespace LIR
} // namespace LM

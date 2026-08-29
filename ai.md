# AI Codebase Analysis & Humanisation Report

This document provides a comprehensive audit of AI-written code, AI support infrastructure, prompt artifacts, synthetic test suites, and documentation tropes present in the codebase (including historical commit records). It also includes actionable humanisation recommendations and references the Python script `clean_ai_history.py` created to automate the cleaning down to git history.

---

## 1. Executive Summary

The Limitly codebase exhibits extensive evidence of being iteratively developed, audited, and maintained with AI assistance (via AI agents, Kiro IDE, Cursor, and LLM coding models). AI involvement spans system instructions, IDE steering rules, prompt residue in source C++ comments, duplicate synthetic test trees, build outputs committed to git, and verbose self-auditing markdown logs.

---

## 2. Discovered AI-Written Code, AI Support, and Steering Files

Below is the complete inventory of all files and directories identified with AI-written text, prompt artifacts, or AI support structures:

### 2.1 AI Agent Guidelines & System Prompts
- **`AGENTS.md`**: AI agent prompt guidelines file containing instructions on language keywords, generic constraints, and submodule rules.
- **`Limitly.creator`**: Qt Creator project file where the first 270 lines were prepended with the full text of `AGENTS.md`.
- **Git History Injections**: `AGENTS.md`, `Limitly.creator`, and `src/backend/vm/vm_value_base.hh` were committed together across historical commits (`27570d1`, `08c901e`, `0eb4e85`, `147d26b`).

### 2.2 AI IDE Steering & Architectural Context (`.kiro/`)
- **`.kiro/steering/`** (11 files):
  - `.kiro/steering/fyra_integration.md`
  - `.kiro/steering/fyra_ir_architecture.md`
  - `.kiro/steering/fyra_targets_comparison.md`
  - `.kiro/steering/language_design.md`
  - `.kiro/steering/product.md`
  - `.kiro/steering/structure.md`
  - `.kiro/steering/syntax.md`
  - `.kiro/steering/tech.md`
  - `.kiro/steering/testing.md`
  - `.kiro/steering/vm_implementation.md`
  - `.kiro/steering/workflow.md`
- **`.kiro/specs/`** (12 spec directories + 7 audit summary reports):
  - `.kiro/specs/AUDIT_REPORT.md`
  - `.kiro/specs/COMPREHENSIVE_AUDIT.md`
  - `.kiro/specs/MASTER_AUDIT_SUMMARY.md`
  - `.kiro/specs/README_AUDIT.md`
  - `.kiro/specs/SPECS_STATUS.md`
  - `.kiro/specs/SPEC_AUDIT_SUMMARY.md`
  - `.kiro/specs/UPDATE_PLAN.md`
  - `.kiro/specs/advanced-module-system/`
  - `.kiro/specs/advanced-pattern-matching/`
  - `.kiro/specs/closures-higher-order-functions/`
  - `.kiro/specs/complete-class-integration/`
  - `.kiro/specs/concurrency-error-integration/`
  - `.kiro/specs/enhanced-error-messages/`
  - `.kiro/specs/enhanced-pattern-matching-loops/`
  - `.kiro/specs/frames-oop-system/`
  - `.kiro/specs/limit-language-formalization/`
  - `.kiro/specs/limit-tooling-ecosystem/`
  - `.kiro/specs/standard-library-core/`
  - `.kiro/specs/type-system-refinement/`

### 2.3 Direct LLM Prompt Residue in Code
- **`src/backend/vm/vm_value_base.hh`** (Lines 13–15):
  ```cpp
  // For backward compatibility or if the name 'Value' is strictly required by the prompt instructions in some contexts,
  // but we must avoid clash with Backend::Value.
  // The prompt said: using Value = uint64_t;
  ```

### 2.4 Synthetic AI Test Trees, Stray Files & Assembly Dumps
- **Duplicate Synthetic Test Directories**:
  - `tests/tl_stdlib/` (all files and subdirectories)
  - `tests/tl_stdlib_orig/` (all files and subdirectories)
  - `tests/stdlib/2` (scratchpad test file)
- **Stray File Artifacts**:
  - `std/ffi copy.lm`
  - `std/empty.lm`
- **Generated Assembly Files (`.exe.s`) & Memory Dumps (`.dump`) Committed to Git**:
  - Over 50 `.exe.s` files across `tests/` and `tests/stdlib/` (e.g. `tests/types/basic.exe.s`, `tests/stdlib/mime_test.exe.s`).
  - `tests/str_test4.dump`

### 2.5 Verbose AI Tracking Logs & Documentation Tropes
- **`todo.md` & `TODO.md`**: Verbose checklists featuring AI presentation tropes (`MAJOR MILESTONE 🎉`, `COMPLETE! 🎉`, `CRITICAL FIX`).
- **`unneeded.md`**: Self-generated AI list cataloging redundant files.
- **`actions.md`**, **`activities.md`**, **`results.md`**, **`test_failures_summary.md`**, **`REGRESSION_FIXES.md`**, **`IMPLEMENTATION_COMPLETE.md`**.

---

## 3. How to Humanise These Discovered Areas

### 3.1 Source Code Comments (`src/backend/vm/vm_value_base.hh`)
- **Action**: Replace references to "prompt instructions" with standard C++ technical documentation explaining the type alias definition.

### 3.2 IDE Guidelines & Config Files (`AGENTS.md` & `Limitly.creator`)
- **Action**: Strip out the 270 lines of Markdown prepended to `Limitly.creator`. Convert `AGENTS.md` into developer-facing `CONTRIBUTING.md` / `ARCHITECTURE.md`.

### 3.3 Steering & Metadata (`.kiro/`)
- **Action**: Add `.kiro/` to `.gitignore` or migrate valid technical specs to standard `docs/` paths.

### 3.4 Duplicate Test Suites & Artifacts
- **Action**: Remove `tests/tl_stdlib/`, `tests/tl_stdlib_orig/`, `tests/stdlib/2`, `std/ffi copy.lm`, `std/empty.lm`, and all `.exe.s` / `.dump` files. Update `.gitignore` to exclude build/assembly artifacts.

### 3.5 Documentation Tropes
- **Action**: Replace multi-layered verbose task logs with a single concise `ROADMAP.md` and standard GitHub issues.

---

## 4. Automated Cleaning & History Scrubbing Script (`clean_ai_history.py`)

To fix these areas in the working directory as well as clean Git history down to previous commits, run the automated Python script `clean_ai_history.py` included in the root directory.

### Running the Python Script:
```bash
# Clean working tree artifacts (files, comments, config lines)
python3 clean_ai_history.py --clean-working-tree

# Purge AI artifacts down to Git history (rewrites past commits using git filter-repo / filter-branch)
python3 clean_ai_history.py --clean-git-history
```

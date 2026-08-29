#!/usr/bin/env python3
"""
clean_ai_history.py - Script to humanise codebase and clean AI artifacts down to Git history.

Usage:
  python3 clean_ai_history.py --clean-working-tree
  python3 clean_ai_history.py --clean-git-history
"""

import sys
import os
import re
import shutil
import subprocess
import argparse

# List of redundant AI-generated / stray files and directories to remove in working tree
FILES_TO_REMOVE = [
    "std/ffi copy.lm",
    "std/empty.lm",
    "tests/stdlib/2",
    "unneeded.md",
    "results.md",
    "test_failures_summary.md",
    "activities.md",
    "actions.md",
    "REGRESSION_FIXES.md",
    "IMPLEMENTATION_COMPLETE.md",
]

DIRS_TO_REMOVE = [
    "tests/tl_stdlib",
    "tests/tl_stdlib_orig",
]

# Patterns for assembly dumps and build artifacts to purge
FILE_PATTERNS_TO_REMOVE = [
    r".*\.exe\.s$",
    r".*\.dump$",
]

def clean_source_comments():
    """Scrub prompt residue comments from source files."""
    vm_val_file = "src/backend/vm/vm_value_base.hh"
    if os.path.exists(vm_val_file):
        with open(vm_val_file, "r") as f:
            content = f.read()

        # Scrub prompt instruction comments in vm_value_base.hh
        prompt_comment_pattern = r"// For backward compatibility or if the name 'Value' is strictly required by the prompt instructions.*?\n// I will use LmValue internally in runtime and try to keep RegisterValue as Value if possible,\n// but Backend::Value is a struct\.\n"
        cleaned_content = re.sub(prompt_comment_pattern, "// Canonical 64-bit runtime execution value\n", content, flags=re.DOTALL)

        if content != cleaned_content:
            with open(vm_val_file, "w") as f:
                f.write(cleaned_content)
            print(f"[+] Scrubbed prompt comments from {vm_val_file}")

def clean_limitly_creator():
    """Remove prepended AGENTS.md content from Limitly.creator project file."""
    creator_file = "Limitly.creator"
    if os.path.exists(creator_file):
        with open(creator_file, "r") as f:
            lines = f.readlines()

        # Keep lines starting from standard creator entries or strip AGENTS.md markdown header
        cleaned_lines = []
        skip = False
        for line in lines:
            if line.startswith("# Limitly Language - AI Agent Guidelines"):
                skip = True
            elif skip and not line.startswith("#") and not line.strip().endswith(".cpp") and not line.strip().endswith(".hh") and not line.strip().endswith(".lm"):
                if line.strip() == "" or line.startswith("src/") or line.startswith("std/"):
                    skip = False
            if not skip:
                cleaned_lines.append(line)

        with open(creator_file, "w") as f:
            f.writelines(cleaned_lines)
        print(f"[+] Humanised {creator_file} by stripping prepended prompt guidelines.")

def clean_working_tree():
    """Remove identified AI-generated files, stray assembly dumps, and clean source comments."""
    print("=== Cleaning Working Tree AI Artifacts ===")

    # 1. Clean source code comments
    clean_source_comments()

    # 2. Clean Limitly.creator
    clean_limitly_creator()

    # 3. Remove specified files
    for filepath in FILES_TO_REMOVE:
        if os.path.exists(filepath):
            os.remove(filepath)
            print(f"[+] Removed file: {filepath}")

    # 4. Remove specified directories
    for dirpath in DIRS_TO_REMOVE:
        if os.path.exists(dirpath):
            shutil.rmtree(dirpath)
            print(f"[+] Removed directory: {dirpath}")

    # 5. Remove matching file patterns (.exe.s, .dump)
    for root, _, files in os.walk("."):
        if ".git" in root:
            continue
        for file in files:
            for pattern in FILE_PATTERNS_TO_REMOVE:
                if re.match(pattern, file):
                    full_path = os.path.join(root, file)
                    try:
                        os.remove(full_path)
                        print(f"[+] Removed assembly/dump artifact: {full_path}")
                    except Exception as e:
                        print(f"[-] Failed to remove {full_path}: {e}")

    print("[+] Working tree cleaning complete.")

def clean_git_history():
    """Output commands and execute git filter-branch / git filter-repo to clean history down to past commits."""
    print("=== Git History Cleaning Information ===")
    print("To purge AI artifacts down to past git history across all commits, run the following commands:\n")
    print("1. Using git filter-repo (Recommended):")
    print("   git filter-repo --invert-paths \\")
    print("     --path tests/tl_stdlib \\")
    print("     --path tests/tl_stdlib_orig \\")
    print("     --path unneeded.md \\")
    print("     --path-glob '*.exe.s'\n")
    print("2. Using git filter-branch:")
    print("   git filter-branch --force --index-filter \\")
    print("     'git rm -r --cached --ignore-unmatch tests/tl_stdlib tests/tl_stdlib_orig *.exe.s' \\")
    print("     --prune-empty --tag-name-filter cat -- --all\n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Humanise codebase and clean AI artifacts down to Git history.")
    parser.add_argument("--clean-working-tree", action="store_true", help="Clean AI artifacts, prompt comments, and duplicate test files in current working tree.")
    parser.add_argument("--clean-git-history", action="store_true", help="Show/execute git commands to purge AI artifacts down to Git history.")

    args = parser.parse_args()

    if not args.clean_working_tree and not args.clean_git_history:
        parser.print_help()
        sys.exit(1)

    if args.clean_working_tree:
        clean_working_tree()

    if args.clean_git_history:
        clean_git_history()

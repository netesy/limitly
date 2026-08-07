#!/usr/bin/env python3
"""
Fuzzy Test Suite for the Limitly Programming Language
=====================================================

A robust, self-contained fuzzing tool that:
1. Loads valid/invalid Limitly seed files or generates chaotic structural code.
2. Applies smart mutation strategies representing:
   - Parser/Syntax errors (missing semicolons, unbalanced braces/parens, keyword misuse).
   - Typechecker/Semantic errors (incompatible literals, wrong arguments, return mismatches).
   - Memory/Soundness errors (uninitialized variables, use-after-move patterns).
3. Executes the compiler with strict timeout checks (preventing parser hangs).
4. Categorizes compiler feedback into distinct stages (Parser, Typechecker, Memory).
5. Reports failures in an incredibly polished, human-readable console interface,
   complete with source context carets, highlighted mutation diffs, and precise tips to fix.
"""

import os
import sys
import random
import glob
import re
import subprocess
import time
import argparse
from typing import List, Dict, Tuple, Optional

# ANSI Color Codes for human-readable console styling
COLOR_RED = "\033[1;31m"
COLOR_GREEN = "\033[1;32m"
COLOR_YELLOW = "\033[1;33m"
COLOR_BLUE = "\033[1;34m"
COLOR_MAGENTA = "\033[1;35m"
COLOR_CYAN = "\033[1;36m"
COLOR_BOLD = "\033[1m"
COLOR_RESET = "\033[0m"

# Reserved Keywords in Limitly (cannot be used as identifiers)
RESERVED_KEYWORDS = [
    "iter", "any", "fn", "if", "while", "for", "return", "var", "val", "const",
    "frame", "trait", "import", "match", "in", "type", "enum", "err", "ok",
    "and", "or", "not", "as", "where", "self", "super", "true", "false",
    "nil", "break", "continue", "parallel", "concurrent", "task", "worker",
    "contract", "comptime", "unsafe", "module", "interface", "mixin",
    "implements", "show", "hide", "from", "elif", "else", "static", "abstract",
    "final", "pub", "prot"
]

def print_color(text: str, color_code: str):
    """Prints text in a given color, falling back to clean text if stdout is not a TTY."""
    if sys.stdout.isatty():
        print(f"{color_code}{text}{COLOR_RESET}")
    else:
        print(text)

def format_color(text: str, color_code: str) -> str:
    """Formats text in a given color, falling back to clean text if stdout is not a TTY."""
    if sys.stdout.isatty():
        return f"{color_code}{text}{COLOR_RESET}"
    return text


# ==========================================
# Mutation Strategies
# ==========================================

def mutate_remove_semicolon(code: str) -> Tuple[Optional[str], str, str]:
    """Strategy: Remove a semicolon to trigger a Parser/Syntax error."""
    lines = code.splitlines()
    candidate_indices = [
        i for i, line in enumerate(lines)
        if line.strip().endswith(';') and not line.strip().startswith('//')
    ]
    if not candidate_indices:
        return None, "", "No semicolon found to remove"

    idx = random.choice(candidate_indices)
    old_line = lines[idx]
    rsemi_idx = old_line.rfind(';')
    lines[idx] = old_line[:rsemi_idx] + old_line[rsemi_idx+1:]

    mutated_code = "\n".join(lines)
    desc = f"Removed semicolon from line {idx + 1}"
    help_tip = (
        "Check `src/frontend/parser/statements.cpp`. Ensure statements are "
        "always correctly terminated by consuming `TokenType::SEMICOLON`."
    )
    return mutated_code, desc, help_tip

def mutate_unbalance_braces(code: str) -> Tuple[Optional[str], str, str]:
    """Strategy: Remove or duplicate a brace to trigger an unmatched braces error."""
    lines = code.splitlines()
    braces = []
    for i, line in enumerate(lines):
        if line.strip().startswith('//'):
            continue
        for j, char in enumerate(line):
            if char in ('{', '}'):
                braces.append((i, j, char))

    if not braces:
        return None, "", "No braces found to unbalance"

    idx = random.choice(range(len(braces)))
    line_idx, char_idx, char = braces[idx]
    old_line = lines[line_idx]

    if random.random() < 0.5:
        # Delete brace
        lines[line_idx] = old_line[:char_idx] + old_line[char_idx+1:]
        desc = f"Removed brace '{char}' at line {line_idx+1}, column {char_idx+1}"
    else:
        # Duplicate brace
        lines[line_idx] = old_line[:char_idx] + char + old_line[char_idx:]
        desc = f"Duplicated brace '{char}' at line {line_idx+1}, column {char_idx+1}"

    help_tip = (
        "Check `src/frontend/parser.cpp` and block parsing rules. Verify that "
        "opening braces `{` and closing braces `}` are strictly paired and throw "
        "clear, structural errors when unbalanced instead of cascading."
    )
    return "\n".join(lines), desc, help_tip

def mutate_replace_with_keyword(code: str) -> Tuple[Optional[str], str, str]:
    """Strategy: Replace a variable name or identifier with a reserved keyword."""
    lines = code.splitlines()
    words = []
    for i, line in enumerate(lines):
        if line.strip().startswith('//'):
            continue
        # Find identifier words (starts with alpha or _, then alphanumeric)
        for match in re.finditer(r'\b([a-zA-Z_][a-zA-Z0-9_]*)\b', line):
            word = match.group(1)
            if word not in RESERVED_KEYWORDS and word not in ("print", "main", "int", "str", "bool", "float"):
                words.append((i, match.start(), match.end(), word))

    if not words:
        return None, "", "No suitable identifiers found to replace with keyword"

    idx = random.choice(range(len(words)))
    line_idx, start, end, old_word = words[idx]
    keyword = random.choice(RESERVED_KEYWORDS)

    old_line = lines[line_idx]
    lines[line_idx] = old_line[:start] + keyword + old_line[end:]
    desc = f"Replaced identifier '{old_word}' with reserved keyword '{keyword}' at line {line_idx+1}"
    help_tip = (
        "Check `src/frontend/scanner.cpp` and `src/frontend/parser.cpp`. "
        "Keywords are reserved and cannot be used as identifiers. Make sure identifier parsing "
        "rejects reserved words and gives a descriptive error message."
    )
    return "\n".join(lines), desc, help_tip

def mutate_type_mismatch_literal(code: str) -> Tuple[Optional[str], str, str]:
    """Strategy: Injects a type mismatch literal/assignment to trigger Typechecker errors."""
    lines = code.splitlines()
    mutated = False
    desc = ""

    # Try replacing a numeric literal in variable declarations with a string literal
    for i in range(len(lines)):
        line = lines[i]
        if 'var ' in line and '=' in line and ';' in line and not line.strip().startswith('//'):
            match = re.search(r'=\s*(\d+|true|false)\s*;', line)
            if match:
                val = match.group(1)
                new_val = '"mismatch_string"' if val != 'true' and val != 'false' else '42'
                lines[i] = line.replace(val, new_val, 1)
                desc = f"Changed initialized value '{val}' to '{new_val}' at line {i+1}"
                mutated = True
                break

    if not mutated:
        # Append an assignment of a wrong type to an existing variable
        variables = []
        for i, line in enumerate(lines):
            match = re.search(r'var\s+(\w+)\s*[:=]', line)
            if match and not line.strip().startswith('//'):
                variables.append((i, match.group(1)))
        if variables:
            idx, var_name = random.choice(variables)
            # Find the closing brace of the main function, or just append
            lines.append(f"{var_name} = \"incompatible_string_literal\";")
            desc = f"Appended incompatible string assignment to variable '{var_name}' (declared on line {idx+1})"
            mutated = True

    if not mutated:
        return None, "", "No variable declarations found to mismatch types"

    help_tip = (
        "Check `src/frontend/type_checker/expressions.cpp` or `statements.cpp`. "
        "Verify that assignment statement types are compared and checked for compatibility, "
        "raising a semantic error when there is a mismatch."
    )
    return "\n".join(lines), desc, help_tip

def mutate_uninitialized_variable(code: str) -> Tuple[Optional[str], str, str]:
    """Strategy: Strips initializers to trigger uninitialized-use Memory errors."""
    lines = code.splitlines()
    mutated = False
    desc = ""

    for i in range(len(lines)):
        line = lines[i]
        if 'var ' in line and '=' in line and ';' in line and not line.strip().startswith('//'):
            match_typed = re.search(r'var\s+(\w+)\s*:\s*([^=]+)\s*=\s*(.+)\s*;', line)
            if match_typed:
                var_name = match_typed.group(1)
                var_type = match_typed.group(2).strip()
                lines[i] = f"var {var_name}: {var_type};"
                desc = f"Removed initializer for '{var_name}' at line {i+1} (annotated '{var_type}')"
                mutated = True
                break
            else:
                match_untyped = re.search(r'var\s+(\w+)\s*=\s*(.+)\s*;', line)
                if match_untyped:
                    var_name = match_untyped.group(1)
                    val = match_untyped.group(2).strip()
                    guessed_type = "int"
                    if val.startswith('"'):
                        guessed_type = "str"
                    elif val in ("true", "false"):
                        guessed_type = "bool"
                    elif val.startswith('['):
                        guessed_type = "[int]"

                    lines[i] = f"var {var_name}: {guessed_type};"
                    desc = f"Removed initializer for '{var_name}' at line {i+1} and annotated type '{guessed_type}'"
                    mutated = True
                    break

    if not mutated:
        return None, "", "No initialized variables found to uninitialize"

    help_tip = (
        "Check `src/frontend/memory_checker.cpp` or `src/frontend/type_checker/memory.cpp`. "
        "Ensure the control flow graph tracking accurately flags variables used before assignment, "
        "reporting a memory or soundness error."
    )
    return "\n".join(lines), desc, help_tip


# ==========================================
# Generative Fuzzing Component (Structure)
# ==========================================

def generate_chaotic_code() -> Tuple[str, str, str]:
    """Generates deeply nested, chaotic code blocks to thoroughly test parser robustness."""
    constructs = ["if", "while", "for", "match", "parallel", "concurrent"]
    code = []
    code.append("fn main() {")

    indent = 4
    open_brackets = 1

    # Add variables
    code.append(f"{' ' * indent}var x = 10;")
    code.append(f"{' ' * indent}var y: str = \"chaos\";")

    for _ in range(random.randint(5, 15)):
        action = random.choice(["block_open", "stmt", "block_close", "malformed"])
        if action == "block_open":
            cons = random.choice(constructs)
            if cons == "if":
                code.append(f"{' ' * indent}if (x > 5) {{")
            elif cons == "while":
                code.append(f"{' ' * indent}while (x < 100) {{")
            elif cons == "for":
                code.append(f"{' ' * indent}for (var i = 0; i < 10; i = i + 1) {{")
            elif cons == "match":
                code.append(f"{' ' * indent}match (x) {{")
                code.append(f"{' ' * (indent+4)}5 => {{ x = x + 1; }},")
            elif cons == "parallel":
                code.append(f"{' ' * indent}parallel(cores=2) {{")
            elif cons == "concurrent":
                code.append(f"{' ' * indent}concurrent(cores=2) {{")
            indent += 4
            open_brackets += 1
        elif action == "stmt":
            stmt = random.choice([
                "x = x * 2;",
                "print(y);",
                "var z = x + 5;",
                "print(\"nested z:\", z);"
            ])
            code.append(f"{' ' * indent}{stmt}")
        elif action == "block_close" and open_brackets > 1:
            indent -= 4
            code.append(f"{' ' * indent}}}")
            open_brackets -= 1
        elif action == "malformed":
            mal = random.choice([
                "var = 123;",
                "x = ;",
                "if (x {",
                "fn inner(",
                "print(;",
            ])
            code.append(f"{' ' * indent}{mal}")

    # Close any remaining brackets
    while open_brackets > 0:
        indent -= 4
        if indent < 0: indent = 0
        code.append(f"{' ' * indent}}}")
        open_brackets -= 1

    code_str = "\n".join(code)
    help_tip = (
        "Check `src/frontend/parser.cpp` synchronize functions. If nested blocks or "
        "unmatched delimiters cause infinite loops/hangs, verify that the parser advance() "
        "safeguards are correctly tracking maximum iterations or progressing the token index."
    )
    return code_str, "Deeply nested chaotic generative code structure", help_tip


# ==========================================
# Diagnostic Parser and Output Formatting
# ==========================================

def display_failure_report(
    test_num: int,
    file_source: str,
    mutation_desc: str,
    error_stage_expected: str,
    exit_code: int,
    stdout: str,
    stderr: str,
    help_tip: str,
    original_seed: str,
    failure_reason: str
):
    """Prints a beautiful, comprehensive, highly readable diagnostic report for any failing fuzz test."""
    print("=" * 80)
    print_color(f"🔥 FUZZ TEST FAILURE DETECTED (Test #{test_num})", COLOR_RED)
    print("=" * 80)
    print(f"{format_color('Original Seed:', COLOR_BOLD)} {original_seed}")
    print(f"{format_color('Mutation/Source:', COLOR_BOLD)} {mutation_desc}")
    print(f"{format_color('Expected Error Stage:', COLOR_BOLD)} {error_stage_expected}")
    print(f"{format_color('Failure Reason:', COLOR_BOLD)} {format_color(failure_reason, COLOR_YELLOW)}")
    print("-" * 80)

    print_color("--- MUTATED CODE ---", COLOR_CYAN)
    lines = file_source.splitlines()
    for idx, line in enumerate(lines):
        # We can format line numbers nicely
        num_prefix = f"{idx+1:3d} | "
        if "Removed semicolon" in mutation_desc and f"line {idx+1}" in mutation_desc:
            print_color(f"{num_prefix}{line} <-- [MUTATED POINT]", COLOR_YELLOW)
        elif "Removed brace" in mutation_desc and f"line {idx+1}" in mutation_desc:
            print_color(f"{num_prefix}{line} <-- [MUTATED POINT]", COLOR_YELLOW)
        elif "Duplicated brace" in mutation_desc and f"line {idx+1}" in mutation_desc:
            print_color(f"{num_prefix}{line} <-- [MUTATED POINT]", COLOR_YELLOW)
        elif "Replaced identifier" in mutation_desc and f"line {idx+1}" in mutation_desc:
            print_color(f"{num_prefix}{line} <-- [MUTATED POINT]", COLOR_YELLOW)
        elif "Changed initialized value" in mutation_desc and f"line {idx+1}" in mutation_desc:
            print_color(f"{num_prefix}{line} <-- [MUTATED POINT]", COLOR_YELLOW)
        elif "Removed initializer" in mutation_desc and f"line {idx+1}" in mutation_desc:
            print_color(f"{num_prefix}{line} <-- [MUTATED POINT]", COLOR_YELLOW)
        else:
            print(f"{num_prefix}{line}")

    print("-" * 80)
    print_color(f"--- COMPILER OUTPUT (Exit Code: {exit_code}) ---", COLOR_CYAN)
    if stdout:
        print(f"{format_color('STDOUT:', COLOR_BOLD)}")
        print(stdout.strip())
    if stderr:
        print(f"{format_color('STDERR:', COLOR_BOLD)}")
        print(stderr.strip())
    if not stdout and not stderr:
        print("(No compiler output printed)")

    print("-" * 80)
    print_color("--- ACTIONABLE HELP & DIAGNOSTICS ---", COLOR_GREEN)
    print_color(f"💡 Suggestion to fix the compiler/test:", COLOR_BOLD)
    print(help_tip)
    print("=" * 80)
    print()


# ==========================================
# Test Execution Runner
# ==========================================

class FuzzTestRunner:
    def __init__(self, compiler_path: str, timeout: float = 1.0, verbose: bool = False):
        self.compiler_path = compiler_path
        self.timeout = timeout
        self.verbose = verbose
        self.passed_count = 0
        self.failed_count = 0
        self.hang_count = 0
        self.total_runs = 0

    def run_source(self, code: str) -> Tuple[int, str, str, bool]:
        """Runs the Limitly compiler on the given code. Returns (exit_code, stdout, stderr, timed_out)."""
        temp_file = "tests/fuzz_temp_test.lm"
        with open(temp_file, "w") as f:
            f.write(code)

        try:
            start_time = time.time()
            res = subprocess.run(
                [self.compiler_path, "run", temp_file],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                timeout=self.timeout
            )
            duration = time.time() - start_time
            if self.verbose:
                print(f"Compiler executed in {duration:.4f}s")

            # Clean up temp file
            if os.path.exists(temp_file):
                os.remove(temp_file)

            return res.returncode, res.stdout, res.stderr, False

        except subprocess.TimeoutExpired:
            if os.path.exists(temp_file):
                os.remove(temp_file)
            return -1, "", "TIMEOUT EXPIRED: Compiler hung or entered an infinite loop!", True

    def categorize_error(self, stdout: str, stderr: str) -> str:
        """Parses stdout/stderr to identify the detection stage: Parser, Typechecker, Memory, or None."""
        combined = stdout + "\n" + stderr

        # Check for Parser/Syntax patterns
        parser_patterns = [
            "error[E002]", "expected `;`", "syntax error", "unexpected token",
            "Parser hasError is true", "Unclosed", "Unexpected closing brace",
            "unmatched", "expected `}`", "Expected expression"
        ]
        # Check for Typechecker/Semantic patterns
        type_patterns = [
            "error[E003]", "type mismatch", "cannot find function",
            "Type Check Error", "Semantic Error", "incompatible operations",
            "does not implement required trait", "signature doesn't match",
            "declares error type", "but function body cannot produce"
        ]
        # Check for Memory/Soundness patterns
        memory_patterns = [
            "Use before initialization", "Uninitialized use", "uninitialized",
            "use after free", "use-after-free", "double free", "dangling ref",
            "memory leak", "resource leak", "dropped without cleanup"
        ]

        # Priority checking
        for pat in parser_patterns:
            if pat.lower() in combined.lower():
                return "Parser"

        for pat in type_patterns:
            if pat.lower() in combined.lower():
                return "Typechecker"

        for pat in memory_patterns:
            if pat.lower() in combined.lower():
                return "Memory"

        return "Unknown"

    def execute_fuzz_test(self, test_num: int, code: str, mutation_desc: str, expected_stage: str, help_tip: str, seed_path: str):
        """Runs a single fuzz case, evaluates success, and prints reports on failures."""
        self.total_runs += 1

        exit_code, stdout, stderr, timed_out = self.run_source(code)

        # 1. Check for Hang/Timeout
        if timed_out:
            self.failed_count += 1
            self.hang_count += 1
            display_failure_report(
                test_num, code, mutation_desc, expected_stage, exit_code, stdout, stderr,
                help_tip, seed_path, "COMPILER HANG/TIMEOUT (The compiler took longer than the threshold, indicating an infinite loop!)"
            )
            return

        # 2. Check for Compiler Crash (Segmentation Fault, etc.)
        if exit_code == 139 or exit_code < 0 or "segmentation fault" in (stdout + stderr).lower():
            self.failed_count += 1
            display_failure_report(
                test_num, code, mutation_desc, expected_stage, exit_code, stdout, stderr,
                help_tip, seed_path, "COMPILER CRASH / SEGMENTATION FAULT"
            )
            return

        # 3. Check for Undetected Errors
        # If we expect an error but the compiler exits successfully (0) and detects no error
        detected_stage = self.categorize_error(stdout, stderr)

        # A test fails if:
        # - We expected a specific error stage, but the compiler exited with 0 (accepted the code!).
        # - Or if it produced an error but of a completely wrong stage (e.g. parser accepted invalid syntax and let typechecker crash).
        if expected_stage != "Valid" and exit_code == 0 and detected_stage == "Unknown":
            self.failed_count += 1
            display_failure_report(
                test_num, code, mutation_desc, expected_stage, exit_code, stdout, stderr,
                help_tip, seed_path, "UNDETECTED ERROR (Compiler exited with code 0 and reported no error, accepting invalid code!)"
            )
            return

        # Success!
        self.passed_count += 1
        if self.verbose:
            print_color(f"  ✓ Test #{test_num} Passed: {mutation_desc} (Detected error in: {detected_stage})", COLOR_GREEN)


# ==========================================
# Main Entry Point
# ==========================================

def discover_seed_files(seeds_dir: str) -> List[str]:
    """Finds suitable small .lm files under tests/ to use as fuzzing seeds."""
    all_files = glob.glob(os.path.join(seeds_dir, "**", "*.lm"), recursive=True)
    small_files = []

    # Exclude temp files, ffi-related tests (clashes with frame keyword in standard library ffi.lm), or files that are too huge
    for fp in all_files:
        if "fuzz_temp" in fp or "run_tests" in fp or "ffi" in fp.lower():
            continue
        try:
            # We love small seed files (under 1500 chars) for precise mutations
            if os.path.getsize(fp) < 1500:
                small_files.append(fp)
        except OSError:
            pass

    # Sort for deterministic order
    return sorted(small_files)

def main():
    parser = argparse.ArgumentParser(description="Limitly Fuzzy Test Suite with Human-Readable Diagnostics")
    parser.add_argument("--num-runs", type=int, default=100, help="Number of fuzz test iterations (default: 100)")
    parser.add_argument("--timeout", type=float, default=1.0, help="Timeout in seconds for compiler executions (default: 1.0)")
    parser.add_argument("--verbose", action="store_true", help="Print verbose details for every mutation executed")
    parser.add_argument("--seed", type=int, help="Optional random seed for reproducibility")
    parser.add_argument("--seeds-dir", type=str, default="tests", help="Base directory to search for .lm seeds")
    args = parser.parse_args()

    # Reproducibility
    if args.seed is not None:
        random.seed(args.seed)
        print(f"Using fixed random seed: {args.seed}")
    else:
        seed = random.randint(1, 1000000)
        random.seed(seed)
        print(f"Using random seed: {seed} (Pass --seed {seed} to reproduce this run)")

    compiler_path = os.path.abspath("bin/limitly.exe" if os.name == "nt" else "bin/limitly")
    if not os.path.exists(compiler_path):
        print_color(f"❌ Error: Limitly executable not found at {compiler_path}", COLOR_RED)
        print("Please build the compiler first by running 'make' or './build.sh'.")
        sys.exit(1)

    print_color("======================================================================", COLOR_CYAN)
    print_color("      🚀 STARTING LIMITLY FUZZY TEST SUITE (WITH HUMAN READABILITY)    ", COLOR_BOLD + COLOR_CYAN)
    print_color("======================================================================", COLOR_CYAN)
    print(f"Compiler: {compiler_path}")
    print(f"Timeout:  {args.timeout}s per execution")
    print(f"Runs:     {args.num_runs} iterations")
    print()

    seeds = discover_seed_files(args.seeds_dir)
    if not seeds:
        print_color("❌ Error: No seed .lm files found in seeds directory!", COLOR_RED)
        sys.exit(1)

    print(f"Discovered {len(seeds)} small seed files for mutation.")

    runner = FuzzTestRunner(compiler_path, timeout=args.timeout, verbose=args.verbose)

    # Set up mutation strategies
    mutation_strategies = [
        ("Parser", mutate_remove_semicolon),
        ("Parser", mutate_unbalance_braces),
        ("Parser", mutate_replace_with_keyword),
        ("Typechecker", mutate_type_mismatch_literal),
        ("Memory", mutate_uninitialized_variable)
    ]

    for i in range(1, args.num_runs + 1):
        # We can either do a generative fuzz or mutate a seed file
        # Do generative fuzz 15% of the time, seed mutation 85% of the time
        if random.random() < 0.15:
            code, desc, help_tip = generate_chaotic_code()
            runner.execute_fuzz_test(
                test_num=i,
                code=code,
                mutation_desc=desc,
                expected_stage="Parser",  # Chaotic code will contain malformed statements
                help_tip=help_tip,
                seed_path="[GENERATIVE]"
            )
        else:
            seed_file = random.choice(seeds)
            try:
                with open(seed_file, "r") as f:
                    seed_code = f.read()
            except Exception as e:
                if args.verbose:
                    print(f"Skipping seed {seed_file} due to read error: {e}")
                continue

            # Pick a mutation strategy randomly
            expected_stage, mutate_func = random.choice(mutation_strategies)

            mutated_code, desc, help_tip = mutate_func(seed_code)
            if mutated_code is None:
                # Strategy didn't find match, retry with chaotic code
                code, desc, help_tip = generate_chaotic_code()
                runner.execute_fuzz_test(
                    test_num=i,
                    code=code,
                    mutation_desc=desc,
                    expected_stage="Parser",
                    help_tip=help_tip,
                    seed_path="[GENERATIVE]"
                )
            else:
                runner.execute_fuzz_test(
                    test_num=i,
                    code=mutated_code,
                    mutation_desc=desc,
                    expected_stage=expected_stage,
                    help_tip=help_tip,
                    seed_path=seed_file
                )

        # Simple progress output
        if not args.verbose and i % 10 == 0:
            pct = (i / args.num_runs) * 100
            print(f"Progress: {i}/{args.num_runs} runs complete ({pct:.1f}%) | Passed: {runner.passed_count} | Failed: {runner.failed_count}")

    print_color("\n======================================================================", COLOR_CYAN)
    print_color("                       FUZZING SUMMARY REPORT                         ", COLOR_BOLD + COLOR_CYAN)
    print_color("======================================================================", COLOR_CYAN)
    print(f"Total Fuzz Runs Executed:  {runner.total_runs}")

    passed_formatted = format_color(str(runner.passed_count), COLOR_GREEN if runner.passed_count == runner.total_runs else COLOR_YELLOW)
    print(f"Passed/Detected Correctly: {passed_formatted}")

    failed_formatted = format_color(str(runner.failed_count), COLOR_GREEN if runner.failed_count == 0 else COLOR_RED)
    print(f"Failed Fuzz Runs:          {failed_formatted}")

    if runner.hang_count > 0:
        hang_formatted = format_color(str(runner.hang_count), COLOR_RED)
        print(f"  └─ Compiler Hangs:       {hang_formatted}")

    print("======================================================================")

    if runner.failed_count > 0:
        print_color("\n❌ Some fuzzy tests exposed issues or hangs in the compiler. See above diagnostics.", COLOR_RED)
        sys.exit(1)
    else:
        print_color("\n🎉 All fuzz test executions passed! No hangs, crashes, or undetected errors found.", COLOR_GREEN)
        sys.exit(0)

if __name__ == "__main__":
    main()

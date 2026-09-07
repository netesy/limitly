#!/usr/bin/env bash
set -e

echo "================================================================================"
echo "                   LIMITLY LIR OPTIMIZATION BENCHMARK SUITE                     "
echo "================================================================================"
echo

BENCHMARKS=(
    "tests/basic/variables.lm"
    "tests/basic/control_flow.lm"
    "tests/expressions/arithmetic.lm"
    "tests/expressions/logical.lm"
    "tests/loops/for_loops.lm"
    "tests/loops/while_loops.lm"
    "tests/functions/basic.lm"
)

printf "%-32s %-12s %-12s %-12s %-10s\n" "Benchmark" "Baseline(s)" "Optimized(s)" "Delta(s)" "Speedup"
echo "--------------------------------------------------------------------------------"

for bm in "${BENCHMARKS[@]}"; do
    if [ ! -f "$bm" ]; then
        continue
    fi

    # Run baseline (unoptimized)
    start_time=$(date +%s%N)
    ./bin/limitly "$bm" > /dev/null 2>&1
    end_time=$(date +%s%N)
    baseline_ms=$(( (end_time - start_time) / 1000000 ))
    baseline_sec=$(awk -v ms="$baseline_ms" 'BEGIN { printf "%.3f", ms/1000 }')

    # Run optimized
    start_time=$(date +%s%N)
    LIMITLY_PRINT_OPT_REPORT=1 ./bin/limitly "$bm" > /dev/null 2>&1
    end_time=$(date +%s%N)
    opt_ms=$(( (end_time - start_time) / 1000000 ))
    opt_sec=$(awk -v ms="$opt_ms" 'BEGIN { printf "%.3f", ms/1000 }')

    delta_sec=$(awk -v b="$baseline_sec" -v o="$opt_sec" 'BEGIN { printf "%.3f", b - o }')
    speedup=$(awk -v b="$baseline_sec" -v o="$opt_sec" 'BEGIN { if (b > 0) printf "%.2f%%", ((b - o)/b)*100; else printf "0.00%%" }')

    printf "%-32s %-12s %-12s %-12s %-10s\n" "$bm" "${baseline_sec}s" "${opt_sec}s" "${delta_sec}s" "$speedup"
done

echo "================================================================================"

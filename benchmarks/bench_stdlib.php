<?php
ini_set('memory_limit', '2048M');
function get_time_ms() {
    return microtime(true) * 1000.0;
}

function get_rss_kb() {
    return memory_get_peak_usage(true) / 1024;
}

function bench_string_ops() {
    $t0 = get_time_ms();
    $s = "";
    for ($i = 0; $i < 100000; $i++) {
        $s .= "a";
    }
    $pos = strpos($s, str_repeat("a", 50));
    $t1 = get_time_ms();
    return [$t1 - $t0, strlen($s)];
}

function bench_collections() {
    $t0 = get_time_ms();
    $lst = [];
    for ($i = 0; $i < 1000000; $i++) {
        $lst[] = $i;
    }
    $total = 0;
    for ($i = 0; $i < 1000000; $i++) {
        $total += $lst[$i];
    }
    $t1 = get_time_ms();
    return [$t1 - $t0, $total];
}

function bench_stream_pipeline() {
    $t0 = get_time_ms();
    $data = range(0, 4999999);
    $step1 = array_map(fn($x) => $x * 3 + 1, $data);
    $step2 = array_filter($step1, fn($x) => $x % 2 == 0);
    $step3 = array_map(fn($x) => (int)($x / 2), $step2);
    $res = array_reduce($step3, fn($acc, $x) => $acc + $x, 0);
    $t1 = get_time_ms();
    return [$t1 - $t0, $res];
}

function bench_numeric_loop() {
    $t0 = get_time_ms();
    $acc = 0;
    for ($i = 0; $i < 10000000; $i++) {
        $acc = ($acc + $i) ^ ($i & 0xFF);
    }
    $t1 = get_time_ms();
    return [$t1 - $t0, $acc];
}

list($t_str, $r_str) = bench_string_ops();
list($t_vec, $r_vec) = bench_collections();
list($t_pipe, $r_pipe) = bench_stream_pipeline();
list($t_num, $r_num) = bench_numeric_loop();
$rss = get_rss_kb();

echo "PHP_STRING_MS=" . number_format($t_str, 2, '.', '') . "\n";
echo "PHP_VEC_MS=" . number_format($t_vec, 2, '.', '') . "\n";
echo "PHP_PIPE_MS=" . number_format($t_pipe, 2, '.', '') . "\n";
echo "PHP_NUMERIC_MS=" . number_format($t_num, 2, '.', '') . "\n";
echo "PHP_RSS_KB=" . (int)$rss . "\n";
?>

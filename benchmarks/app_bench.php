<?php
// PHP Application Benchmark (1,000,000 element Quicksort + Hash Reduction)
error_reporting(0);
ini_set('memory_limit', '1024M');

function quicksort(&$arr, $left, $right) {
    $i = $left;
    $j = $right;
    $pivot = $arr[(int)(($left + $right) / 2)];
    while ($i <= $j) {
        while ($arr[$i] < $pivot) { $i++; }
        while ($arr[$j] > $pivot) { $j--; }
        if ($i <= $j) {
            $tmp = $arr[$i];
            $arr[$i] = $arr[$j];
            $arr[$j] = $tmp;
            $i++;
            $j--;
        }
    }
    if ($left < $j) { quicksort($arr, $left, $j); }
    if ($i < $right) { quicksort($arr, $i, $right); }
}

function main() {
    $N = 1000000;
    $data = [];

    $t0 = microtime(true);

    $seed = 12345;
    for ($i = 0; $i < $N; $i++) {
        $seed = ($seed * 1103515245 + 12345) & 2147483647;
        $data[] = $seed % 1000000;
    }

    quicksort($data, 0, $N - 1);

    $hash = 0;
    for ($i = 0; $i < $N; $i++) {
        $hash = ($hash * 31 + $data[$i]) & 0x7FFFFFFFFFFFFFFF;
    }

    $t1 = microtime(true);
    $dur_ms = ($t1 - $t0) * 1000.0;
    $rss_kb = memory_get_peak_usage(true) / 1024;

    echo "PHP_APP_RUNTIME_MS=" . number_format($dur_ms, 2, '.', '') . "\n";
    echo "PHP_APP_HASH=" . $hash . "\n";
    echo "PHP_APP_RSS_KB=" . (int)$rss_kb . "\n";
}

main();

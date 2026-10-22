# Python Stdlib Benchmark Suite for Comparison with Lymar and PHP
import time
import os
import resource

def get_time_ms():
    return time.monotonic() * 1000.0

def get_rss_kb():
    return resource.getrusage(resource.RUSAGE_SELF).ru_maxrss

def bench_string_ops():
    # String Concatenation and Search
    s = ""
    t0 = get_time_ms()
    for i in range(100000):
        s += "a"
    pos = s.find("a" * 50)
    t1 = get_time_ms()
    return t1 - t0, len(s)

def bench_collections():
    # List append & lookup
    t0 = get_time_ms()
    lst = []
    for i in range(1000000):
        lst.append(i)
    total = 0
    for i in range(1000000):
        total += lst[i]
    t1 = get_time_ms()
    return t1 - t0, total

def bench_stream_pipeline():
    # Stream pipeline map/filter/fold
    t0 = get_time_ms()
    data = list(range(5000000))
    res = sum(map(lambda x: x // 2, filter(lambda x: x % 2 == 0, map(lambda x: x * 3 + 1, data))))
    t1 = get_time_ms()
    return t1 - t0, res

def bench_numeric_loop():
    t0 = get_time_ms()
    acc = 0
    for i in range(10000000):
        acc = (acc + i) ^ (i & 0xFF)
    t1 = get_time_ms()
    return t1 - t0, acc

if __name__ == "__main__":
    t_str, r_str = bench_string_ops()
    t_vec, r_vec = bench_collections()
    t_pipe, r_pipe = bench_stream_pipeline()
    t_num, r_num = bench_numeric_loop()
    rss = get_rss_kb()

    print(f"PYTHON_STRING_MS={t_str:.2f}")
    print(f"PYTHON_VEC_MS={t_vec:.2f}")
    print(f"PYTHON_PIPE_MS={t_pipe:.2f}")
    print(f"PYTHON_NUMERIC_MS={t_num:.2f}")
    print(f"PYTHON_RSS_KB={rss}")

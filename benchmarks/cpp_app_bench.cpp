#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sys/resource.h>

static double get_time_ms() {
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(now.time_since_epoch()).count();
}

static long get_rss_kb() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

int main() {
    int N = 1000000;
    std::vector<long> data(N);

    double t0 = get_time_ms();

    // 1. Generate pseudo-random numbers
    long seed = 12345;
    for (int i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7fffffff;
        data[i] = seed % 1000000;
    }

    // 2. std::sort
    std::sort(data.begin(), data.end());

    // 3. Compute reduction hash
    long hash = 0;
    for (int i = 0; i < N; i++) {
        hash = (hash * 31 + data[i]) & 0x7fffffffffffffffL;
    }

    double t1 = get_time_ms();
    long rss = get_rss_kb();

    std::cout << "CPP_APP_RUNTIME_MS=" << (t1 - t0) << "\n";
    std::cout << "CPP_APP_HASH=" << hash << "\n";
    std::cout << "CPP_APP_RSS_KB=" << rss << "\n";

    return 0;
}

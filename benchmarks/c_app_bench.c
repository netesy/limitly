#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

static double get_time_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1000000.0;
}

static long get_rss_kb(void) {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

static void quicksort(long* arr, int left, int right) {
    int i = left, j = right;
    long pivot = arr[(left + right) / 2];
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            long tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    if (left < j) quicksort(arr, left, j);
    if (i < right) quicksort(arr, i, right);
}

int main(void) {
    int N = 1000000;
    long* data = (long*)malloc(N * sizeof(long));

    double t0 = get_time_ms();

    // 1. Generate pseudo-random numbers
    long seed = 12345;
    for (int i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7fffffff;
        data[i] = seed % 1000000;
    }

    // 2. Sort array
    quicksort(data, 0, N - 1);

    // 3. Compute reduction hash
    long hash = 0;
    for (int i = 0; i < N; i++) {
        hash = (hash * 31 + data[i]) & 0x7fffffffffffffffL;
    }

    double t1 = get_time_ms();
    long rss = get_rss_kb();

    printf("C_APP_RUNTIME_MS=%.2f\n", t1 - t0);
    printf("C_APP_HASH=%ld\n", hash);
    printf("C_APP_RSS_KB=%ld\n", rss);

    free(data);
    return 0;
}

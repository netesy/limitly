# Python Application Benchmark (1,000,000 element Quicksort + Hash Reduction)
import time
import sys

sys.setrecursionlimit(200000)

def quicksort(arr, left, right):
    i = left
    j = right
    pivot = arr[(left + right) // 2]
    while i <= j:
        while arr[i] < pivot:
            i += 1
        while arr[j] > pivot:
            j -= 1
        if i <= j:
            arr[i], arr[j] = arr[j], arr[i]
            i += 1
            j -= 1
    if left < j:
        quicksort(arr, left, j)
    if i < right:
        quicksort(arr, i, right)

def main():
    N = 1000000
    data = []

    t0 = time.perf_counter()

    seed = 12345
    for _ in range(N):
        seed = (seed * 1103515245 + 12345) & 2147483647
        data.append(seed % 1000000)

    quicksort(data, 0, N - 1)

    h = 0
    for val in data:
        h = (h * 31 + val) & 0x7FFFFFFFFFFFFFFF

    t1 = time.perf_counter()
    dur_ms = (t1 - t0) * 1000.0

    print(f"PYTHON_APP_RUNTIME_MS={dur_ms:.2f}")
    print(f"PYTHON_APP_HASH={h}")

if __name__ == "__main__":
    main()

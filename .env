# benchmarks/loop_benchmark.py

import time

def main():
    # Test 1: For loop
    print("Starting for loop benchmark...")
    start_time = time.time()

    for i in range(20000000):
        b = i -2
        # print(b)

    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"For loop elapsed time: {elapsed_time} seconds")

    print("")

    # # Test 2: Iterator loop (using range is idiomatic)
    # print("Starting iterator loop benchmark...")
    # start_time = time.time()

    # # In Python, `for i in range(...)` is the standard way to iterate,
    # # and it's already optimized. We'll run the same code again to
    # # demonstrate its performance.
    # for i in range(2000000000):
    #     pass

    # end_time = time.time()
    # elapsed_time = end_time - start_time
    # print(f"Iterator loop elapsed time: {elapsed_time} seconds")

if __name__ == "__main__":
    main()

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


if __name__ == "__main__":
    main()

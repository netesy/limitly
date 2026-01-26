# Concurrent Blocks Test Analysis

## Status: PARTIAL SUCCESS

The concurrent_blocks.lm test is partially working but has issues with worker iteration over channels.

## Working Features ✅

1. **Basic concurrent task execution**: Tasks with range iteration work correctly
   - `task(i in 1..3)` executes 3 tasks concurrently
   - Output: "Concurrent task 1/2/3 running" and "Received result: Task X completed"

2. **Channel close operation**: `channel.close()` now works correctly
   - Bytecode shows `channel_close r105, r88` and `channel_close r142, r127`
   - No more "Unknown LIR operation: 63" errors

3. **Multiple concurrent blocks**: Sequential execution of multiple concurrent blocks works
   - First concurrent block completes successfully
   - Second concurrent block starts and executes

## Issues ❌

### Worker Iteration Over Channels

**Problem**: Workers receiving data from channels are getting corrupted values instead of actual data

**Example**:
```
Expected: "Processing event: info1"
Actual:   "Processing event: 2241963245024"

Expected: "Final result: Processed: job1"
Actual:   "Final result: Processed: 3"

Expected: "Seeded result: Handled: bootstrap-1"
Actual:   "Seeded result: Handled: 5"
```

**Root Cause**: The scheduler is not properly implementing worker iteration over channels. When a worker is created with `worker(item from jobs)`, the scheduler needs to:

1. Detect that the worker has a channel iterable (field 1)
2. Poll the channel for data
3. Extract the actual data value
4. Pass it to the worker as register 1
5. Repeat until the channel is closed

Currently, the scheduler is passing the channel ID or some other corrupted value instead of the actual data.

**Code Location**: 
- LIR Generator: `src/lir/generator.cpp` lines 3002-3050 (worker task context setup)
- VM Scheduler: `src/backend/register/register.cpp` (scheduler_run implementation)

### What Needs to Be Fixed

The VM's scheduler needs to implement worker iteration logic:

```cpp
// Pseudo-code for what needs to happen
while (channel_has_data(field_1)) {
    data_item = channel_poll(field_1);
    if (data_item != nil) {
        registers[1] = data_item;  // Pass data to worker
        call_worker_function();
    }
}
```

## Test Output

### First Concurrent Block (WORKING)
```
=== Concurrent Block Tests ===
Concurrent task 1 running
Concurrent task 2 running
Concurrent task 3 running
Received result: Task 1 completed
Received result: Task 2 completed
Received result: Task 3 completed
Concurrent block finished
```

### Second Concurrent Block (PARTIALLY WORKING)
```
Processing event: 2241963245024  ❌ (should be "info1", "info2", or "info3")
Result: Handled 2241963245024    ❌ (corrupted data)
```

### Third Concurrent Block (PARTIALLY WORKING)
```
Final result: Processed: 3       ❌ (should be "Processed: job1", etc.)
```

### Fourth Concurrent Block (PARTIALLY WORKING)
```
Seeded result: Handled: 5        ❌ (should be "Handled: bootstrap-1" or "bootstrap-2")
```

## Recommendations

1. **Implement worker channel iteration in the scheduler**
   - Add logic to detect when a worker has a channel iterable
   - Poll the channel and extract data before each worker invocation
   - Handle channel closure gracefully

2. **Add debug output to track data flow**
   - Log what data is being extracted from channels
   - Verify that the correct values are being passed to workers

3. **Test with simpler cases first**
   - Test worker with single data item
   - Test worker with multiple data items
   - Test worker with channel closure

4. **Consider alternative approaches**
   - Implement worker iteration as a special case in the LIR generator
   - Generate explicit channel polling code in the worker function
   - Use a different mechanism for passing data to workers

## Next Steps

1. Fix the scheduler's worker iteration logic
2. Re-run the concurrent_blocks.lm test
3. Verify that all worker outputs are correct
4. Add comprehensive tests for worker channel iteration

# JIT Implementation Reference Guide

## Quick Reference: Operation Implementation Patterns

### Single Argument Operations
```cpp
case LIR::LIR_Op::ListLen: {
    gccjit::rvalue list = get_jit_register(inst.a);
    
    std::vector<gccjit::param> params;
    params.push_back(m_context.new_param(m_void_ptr_type, "list"));
    gccjit::function func = m_context.new_function(
        GCC_JIT_FUNCTION_IMPORTED, m_context.get_type(GCC_JIT_TYPE_UINT64_T), 
        "lm_list_len", params, 0);
    
    gccjit::rvalue result = m_current_block.add_call(func, list);
    gccjit::lvalue dst = get_jit_register(inst.dst, m_context.get_type(GCC_JIT_TYPE_UINT64_T));
    m_current_block.add_assignment(dst, result);
    return result;
}
```

### Two Argument Operations
```cpp
case LIR::LIR_Op::ListAppend: {
    gccjit::rvalue list = get_jit_register(inst.a);
    gccjit::rvalue value = get_jit_register(inst.b);
    
    std::vector<gccjit::param> params;
    params.push_back(m_context.new_param(m_void_ptr_type, "list"));
    params.push_back(m_context.new_param(m_void_ptr_type, "value"));
    gccjit::function func = m_context.new_function(
        GCC_JIT_FUNCTION_IMPORTED, m_void_type, "lm_list_append", params, 0);
    
    m_current_block.add_call(func, list, value);
    return list;
}
```

### Three Argument Operations
```cpp
case LIR::LIR_Op::TupleSet: {
    gccjit::rvalue tuple = get_jit_register(inst.dst);
    gccjit::rvalue index = get_jit_register(inst.a);
    gccjit::rvalue value = get_jit_register(inst.b);
    
    std::vector<gccjit::param> params;
    params.push_back(m_context.new_param(m_void_ptr_type, "tuple"));
    params.push_back(m_context.new_param(m_context.get_type(GCC_JIT_TYPE_UINT64_T), "index"));
    params.push_back(m_context.new_param(m_void_ptr_type, "value"));
    gccjit::function func = m_context.new_function(
        GCC_JIT_FUNCTION_IMPORTED, m_void_type, "lm_tuple_set", params, 0);
    
    m_current_block.add_call(func, tuple, 
        m_context.new_cast(index, m_context.get_type(GCC_JIT_TYPE_UINT64_T)), value);
    
    return tuple;
}
```

### No Argument Operations
```cpp
case LIR::LIR_Op::ListCreate: {
    std::vector<gccjit::param> params;
    gccjit::function func = m_context.new_function(
        GCC_JIT_FUNCTION_IMPORTED, m_void_ptr_type, "lm_list_new", params, 0);
    
    gccjit::rvalue result = m_current_block.add_call(func);
    gccjit::lvalue dst = get_jit_register(inst.dst, m_void_ptr_type);
    m_current_block.add_assignment(dst, result);
    return result;
}
```

## Type Mappings

| C Type | libgccjit++ Type |
|--------|------------------|
| `void` | `m_void_type` |
| `int` | `m_int_type` |
| `uint64_t` | `m_context.get_type(GCC_JIT_TYPE_UINT64_T)` |
| `double` | `m_double_type` |
| `bool` | `m_bool_type` |
| `void*` | `m_void_ptr_type` |
| `const char*` | `m_const_char_ptr_type` |
| `size_t` | `m_size_t_type` |

## Common Operations

### Type Casting
```cpp
gccjit::rvalue casted = m_context.new_cast(value, target_type);
```

### Getting Registers
```cpp
gccjit::rvalue input = get_jit_register(inst.a);
gccjit::lvalue output = get_jit_register(inst.dst, m_void_ptr_type);
```

### Assigning Values
```cpp
m_current_block.add_assignment(dst, value);
```

### Function Calls (1-4 args)
```cpp
m_current_block.add_call(func);                    // 0 args
m_current_block.add_call(func, arg1);              // 1 arg
m_current_block.add_call(func, arg1, arg2);        // 2 args
m_current_block.add_call(func, arg1, arg2, arg3);  // 3 args
m_current_block.add_call(func, arg1, arg2, arg3, arg4); // 4 args
```

### Function Calls (5+ args)
```cpp
std::vector<gccjit::rvalue> args = {arg1, arg2, arg3, arg4, arg5};
m_context.new_call(func, args);
```

## Runtime Function Signatures

### Collection Functions
```c
void* lm_list_new(void);
void lm_list_append(void* list, void* value);
void* lm_list_get(void* list, uint64_t index);
uint64_t lm_list_len(void* list);

void* lm_dict_new(void);
void lm_dict_set(void* dict, void* key, void* value);
void* lm_dict_get(void* dict, void* key);
void* lm_dict_items(void* dict);

void* lm_tuple_new(uint64_t size);
void* lm_tuple_get(void* tuple, uint64_t index);
void lm_tuple_set(void* tuple, uint64_t index, void* value);
```

### Channel Functions
```c
void lm_channel_send(void* channel, void* value);
void* lm_channel_recv(void* channel);
int lm_channel_offer(void* channel, void* value);
void* lm_channel_poll(void* channel);
void lm_channel_close(void* channel);
```

### Task/Scheduler Functions
```c
uint64_t lm_task_context_alloc(uint64_t count);
void lm_task_context_init(uint64_t context_id);
int lm_task_get_state(uint64_t context_id);
void lm_task_set_state(uint64_t context_id, int state);
void lm_task_set_field(uint64_t context_id, int field_index, void* value);
void* lm_task_get_field(uint64_t context_id, int field_index);
void lm_scheduler_init(void);
void lm_scheduler_add_task(uint64_t context_id);
void lm_scheduler_run(void);
```

## Debugging Tips

### Check Function Signature
Ensure the function signature matches the C runtime function exactly:
- Parameter count
- Parameter types
- Return type

### Type Casting Issues
If you get type mismatch errors, explicitly cast:
```cpp
gccjit::rvalue casted_index = m_context.new_cast(index, m_context.get_type(GCC_JIT_TYPE_UINT64_T));
```

### Function Call Errors
- Use `add_call` for 0-4 arguments
- Use `new_call` with vector for 5+ arguments
- Never use `add_call` with a vector

### Return Value Handling
- Void functions: Don't assign return value
- Non-void functions: Always assign to destination register

## Testing Checklist

- [ ] Compilation succeeds without errors
- [ ] All collection operations work with `--jit` flag
- [ ] All channel operations work with `--jit` flag
- [ ] All task/scheduler operations work with `--jit` flag
- [ ] Results match `--vm` execution
- [ ] No memory leaks or crashes
- [ ] Performance is acceptable

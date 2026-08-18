.section .data
.align 8
heap_ptr:
  .quad __fyra_heap
.section .bss
.align 16
__fyra_heap:
  .zero 1048576
.text

.data
.align 16
__heap_base:
  .zero 1048576
.align 8
__heap_ptr:
  .quad __heap_base
.align 8
str_const_0:
  .string "Testing Transform..."
.align 8
str_const_1:
  .string "add_ten"
.align 8
str_const_2:
  .string "map 0 failed"
.align 8
str_const_3:
  .string "map 1 failed"
.align 8
str_const_4:
  .string "map 2 failed"
.align 8
str_const_5:
  .string "a"
.align 8
str_const_6:
  .string "b"
.align 8
str_const_7:
  .string "zip left failed"
.align 8
str_const_8:
  .string "a"
.align 8
str_const_9:
  .string "zip right failed"
.align 8
str_const_10:
  .string "unzip left 0 failed"
.align 8
str_const_11:
  .string "a"
.align 8
str_const_12:
  .string "unzip right 0 failed"
.align 8
str_const_13:
  .string "Testing Shuffle..."
.align 8
str_const_14:
  .string "shuffle length changed failed"
.align 8
str_const_15:
  .string "shuffle lost elements failed"
.align 8
str_const_16:
  .string "Testing Reduce..."
.align 8
str_const_17:
  .string "sum_reducer"
.align 8
str_const_18:
  .string "reduce failed"
.align 8
str_const_19:
  .string "sum_reducer"
.align 8
str_const_20:
  .string "fold failed"
.align 8
str_const_21:
  .string "Testing Search..."
.align 8
str_const_22:
  .string "find failed"
.align 8
str_const_23:
  .string "find not found failed"
.align 8
str_const_24:
  .string "is_even"
.align 8
str_const_25:
  .string "find_if failed"
.align 8
str_const_26:
  .string "is_even"
.align 8
str_const_27:
  .string "any_match true failed"
.align 8
str_const_28:
  .string "is_even"
.align 8
str_const_29:
  .string "any_match false failed"
.align 8
str_const_30:
  .string "is_even"
.align 8
str_const_31:
  .string "none true failed"
.align 8
str_const_32:
  .string "is_even"
.align 8
str_const_33:
  .string "none failed"
.align 8
str_const_34:
  .string "is_even"
.align 8
str_const_35:
  .string "all true failed"
.align 8
str_const_36:
  .string "is_even"
.align 8
str_const_37:
  .string "all false failed"
.align 8
str_const_38:
  .string "count failed"
.align 8
str_const_39:
  .string "linear_search failed"
.align 8
str_const_40:
  .string "Testing Binary Search..."
.align 8
str_const_41:
  .string "binary_search failed"
.align 8
str_const_42:
  .string "binary_search not found failed"
.align 8
str_const_43:
  .string "lower_bound failed"
.align 8
str_const_44:
  .string "upper_bound failed"
.align 8
str_const_45:
  .string "equal_range lower failed"
.align 8
str_const_46:
  .string "equal_range upper failed"
.align 8
str_const_47:
  .string "=== Algorithm Module Test Suite ==="
.align 8
str_const_48:
  .string "Search test failed"
.align 8
str_const_49:
  .string "Sort test failed"
.align 8
str_const_50:
  .string "Partition test failed"
.align 8
str_const_51:
  .string "Transform test failed"
.align 8
str_const_52:
  .string "Reduce test failed"
.align 8
str_const_53:
  .string "Filter test failed"
.align 8
str_const_54:
  .string "Unique test failed"
.align 8
str_const_55:
  .string "Shuffle test failed"
.align 8
str_const_56:
  .string "Binary Search test failed"
.align 8
str_const_57:
  .string "All algorithm tests passed successfully."
.align 8
str_const_58:
  .string "Testing Unique..."
.align 8
str_const_59:
  .string "unique length failed"
.align 8
str_const_60:
  .string "unique 0 failed"
.align 8
str_const_61:
  .string "unique 1 failed"
.align 8
str_const_62:
  .string "unique 2 failed"
.align 8
str_const_63:
  .string "unique 3 failed"
.align 8
str_const_64:
  .string "Testing Sort..."
.align 8
str_const_65:
  .string "sort index 0 failed"
.align 8
str_const_66:
  .string "sort index 1 failed"
.align 8
str_const_67:
  .string "sort index 2 failed"
.align 8
str_const_68:
  .string "sort index 3 failed"
.align 8
str_const_69:
  .string "sort index 4 failed"
.align 8
str_const_70:
  .string "quicksort descending failed"
.align 8
str_const_71:
  .string "mergesort failed"
.align 8
str_const_72:
  .string "heapsort failed"
.align 8
str_const_73:
  .string "insertion_sort failed"
.align 8
str_const_74:
  .string "Testing Filter..."
.align 8
str_const_75:
  .string "is_even"
.align 8
str_const_76:
  .string "filter length failed"
.align 8
str_const_77:
  .string "filter 0 failed"
.align 8
str_const_78:
  .string "filter 1 failed"
.align 8
str_const_79:
  .string "filter 2 failed"
.align 8
str_const_80:
  .string "is_even"
.align 8
str_const_81:
  .string "remove_if length failed"
.align 8
str_const_82:
  .string "remove_if 0 failed"
.align 8
str_const_83:
  .string "Testing Partition..."
.align 8
str_const_84:
  .string "is_even"
.align 8
str_const_85:
  .string "partition left failed"
.align 8
str_const_86:
  .string "partition right failed"
.align 8
nl:
  .string "
"
.align 8
assert_fail:
  .string "Assertion failed
"
.text
.globl main
.globl _start
_start:
  and %rsp, -16
  and rsp, -16
  subq $32, %rsp
  call main
  addq $32, %rsp
  mov rcx, rax
  subq $32, %rsp
  call ExitProcess
  addq $32, %rsp

.globl main
main:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 248
main_entry:
main_block_0:
  call std.algorithm.index.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  call test_search
  movq $r2, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_sort
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  call test_partition
  movq $r12, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  call test_transform
  movq $r17, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  call test_reduce
  movq $r22, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  call test_filter
  movq $r27, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  call test_unique
  movq $r32, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  call test_shuffle
  movq $r37, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  call test_binary_search
  movq $r42, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  addq $16, rax
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  mov rax, [rax]
  movq rax, [rbp + -264]
  movq [rbp + -264], rcx
  call lm_print_str
  movq $1, rax
  jmp main_epilogue
main_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_main:

.globl std.algorithm.binary_search.__init__
std.algorithm.binary_search.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.algorithm.binary_search.__init___entry:
  movq $0, rax
  jmp std.algorithm.binary_search.__init___epilogue
std.algorithm.binary_search.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.binary_search.__init__:

.globl std.algorithm.binary_search.lower_bound
std.algorithm.binary_search.lower_bound:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 104
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.binary_search.lower_bound_entry:
std.algorithm.binary_search.lower_bound_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.algorithm.binary_search.lower_bound_block_4
std.algorithm.binary_search.lower_bound_block_4:
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.binary_search.lower_bound_block_6
  jmp std.algorithm.binary_search.lower_bound_block_21
std.algorithm.binary_search.lower_bound_block_6:
  jmp std.algorithm.binary_search.lower_bound_block_6
  movq $1, rax
  addq $r3, rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call lm_list_get
  movq $r11, rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.algorithm.binary_search.lower_bound_block_13
  jmp std.algorithm.binary_search.lower_bound_block_18
std.algorithm.binary_search.lower_bound_block_13:
  jmp std.algorithm.binary_search.lower_bound_block_13
  movq [rbp + -96], rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.algorithm.binary_search.lower_bound_block_20
std.algorithm.binary_search.lower_bound_block_18:
  jmp std.algorithm.binary_search.lower_bound_block_20
std.algorithm.binary_search.lower_bound_block_20:
  jmp std.algorithm.binary_search.lower_bound_block_4
std.algorithm.binary_search.lower_bound_block_21:
  movq [rbp + -112], rax
  jmp std.algorithm.binary_search.lower_bound_epilogue
std.algorithm.binary_search.lower_bound_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.binary_search.lower_bound:

.globl std.algorithm.binary_search.binary_search
std.algorithm.binary_search.binary_search:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 120
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.binary_search.binary_search_entry:
std.algorithm.binary_search.binary_search_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  subq $9, rax
  movq rax, $r5
  jmp std.algorithm.binary_search.binary_search_block_6
std.algorithm.binary_search.binary_search_block_6:
  movq $1, rax
  cmpq $r5, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.binary_search.binary_search_block_8
  jmp std.algorithm.binary_search.binary_search_block_29
std.algorithm.binary_search.binary_search_block_8:
  jmp std.algorithm.binary_search.binary_search_block_8
  movq $1, rax
  addq $r5, rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call lm_list_get
  movq $r13, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.algorithm.binary_search.binary_search_block_15
  jmp std.algorithm.binary_search.binary_search_block_16
std.algorithm.binary_search.binary_search_block_15:
  jmp std.algorithm.binary_search.binary_search_block_15
  movq [rbp + -96], rax
  jmp std.algorithm.binary_search.binary_search_epilogue
std.algorithm.binary_search.binary_search_block_16:
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call lm_list_get
  movq $r16, rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.algorithm.binary_search.binary_search_block_19
  jmp std.algorithm.binary_search.binary_search_block_24
std.algorithm.binary_search.binary_search_block_19:
  jmp std.algorithm.binary_search.binary_search_block_19
  movq [rbp + -96], rax
  addq $9, rax
  movq rax, [rbp + -120]
  jmp std.algorithm.binary_search.binary_search_block_28
std.algorithm.binary_search.binary_search_block_24:
  movq [rbp + -96], rax
  subq $9, rax
  movq rax, [rbp + -128]
  jmp std.algorithm.binary_search.binary_search_block_28
std.algorithm.binary_search.binary_search_block_28:
  jmp std.algorithm.binary_search.binary_search_block_6
std.algorithm.binary_search.binary_search_block_29:
  movq $9, rax
  negq rax
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp std.algorithm.binary_search.binary_search_epilogue
std.algorithm.binary_search.binary_search_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.binary_search.binary_search:

.globl std.sort.quicksort
std.sort.quicksort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.sort.quicksort_entry:
std.sort.quicksort_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  cmpq $9, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.sort.quicksort_block_4
  jmp std.sort.quicksort_block_10
std.sort.quicksort_block_4:
  jmp std.sort.quicksort_block_4
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r8, rax
  subq $9, rax
  movq rax, $r10
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $r10, r8
  movq [rbp + -72], r9
  call std.sort._quicksort_range
  jmp std.sort.quicksort_block_10
std.sort.quicksort_block_10:
  movq $0, rax
  jmp std.sort.quicksort_epilogue
std.sort.quicksort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort.quicksort:

.globl std.search.lower_bound
std.search.lower_bound:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 104
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.search.lower_bound_entry:
std.search.lower_bound_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.search.lower_bound_block_4
std.search.lower_bound_block_4:
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.search.lower_bound_block_6
  jmp std.search.lower_bound_block_21
std.search.lower_bound_block_6:
  jmp std.search.lower_bound_block_6
  movq $1, rax
  addq $r3, rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call lm_list_get
  movq $r11, rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.search.lower_bound_block_13
  jmp std.search.lower_bound_block_18
std.search.lower_bound_block_13:
  jmp std.search.lower_bound_block_13
  movq [rbp + -96], rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.search.lower_bound_block_20
std.search.lower_bound_block_18:
  jmp std.search.lower_bound_block_20
std.search.lower_bound_block_20:
  jmp std.search.lower_bound_block_4
std.search.lower_bound_block_21:
  movq [rbp + -112], rax
  jmp std.search.lower_bound_epilogue
std.search.lower_bound_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.search.lower_bound:

.globl std.search.binary_search
std.search.binary_search:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 120
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.search.binary_search_entry:
std.search.binary_search_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  subq $9, rax
  movq rax, $r5
  jmp std.search.binary_search_block_6
std.search.binary_search_block_6:
  movq $1, rax
  cmpq $r5, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.search.binary_search_block_8
  jmp std.search.binary_search_block_29
std.search.binary_search_block_8:
  jmp std.search.binary_search_block_8
  movq $1, rax
  addq $r5, rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call lm_list_get
  movq $r13, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.search.binary_search_block_15
  jmp std.search.binary_search_block_16
std.search.binary_search_block_15:
  jmp std.search.binary_search_block_15
  movq [rbp + -96], rax
  jmp std.search.binary_search_epilogue
std.search.binary_search_block_16:
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call lm_list_get
  movq $r16, rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.search.binary_search_block_19
  jmp std.search.binary_search_block_24
std.search.binary_search_block_19:
  jmp std.search.binary_search_block_19
  movq [rbp + -96], rax
  addq $9, rax
  movq rax, [rbp + -120]
  jmp std.search.binary_search_block_28
std.search.binary_search_block_24:
  movq [rbp + -96], rax
  subq $9, rax
  movq rax, [rbp + -128]
  jmp std.search.binary_search_block_28
std.search.binary_search_block_28:
  jmp std.search.binary_search_block_6
std.search.binary_search_block_29:
  movq $9, rax
  negq rax
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp std.search.binary_search_epilogue
std.search.binary_search_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.search.binary_search:

.globl std.algorithm.index.count
std.algorithm.index.count:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.count_entry:
std.algorithm.index.count_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.search.count
  movq $r2, rax
  jmp std.algorithm.index.count_epilogue
std.algorithm.index.count_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.count:

.globl std.algorithm.search.find_if
std.algorithm.search.find_if:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.search.find_if_entry:
std.algorithm.search.find_if_block_0:
  jmp std.algorithm.search.find_if_block_2
std.algorithm.search.find_if_block_2:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.search.find_if_block_5
  jmp std.algorithm.search.find_if_block_14
std.algorithm.search.find_if_block_5:
  jmp std.algorithm.search.find_if_block_5
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r6, rcx
  call 
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.algorithm.search.find_if_block_8
  jmp std.algorithm.search.find_if_block_9
std.algorithm.search.find_if_block_8:
  jmp std.algorithm.search.find_if_block_8
  movq $1, rax
  jmp std.algorithm.search.find_if_epilogue
std.algorithm.search.find_if_block_9:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  jmp std.algorithm.search.find_if_block_2
std.algorithm.search.find_if_block_14:
  movq $9, rax
  negq rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  jmp std.algorithm.search.find_if_epilogue
std.algorithm.search.find_if_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.search.find_if:

.globl std.search.interpolation_search
std.search.interpolation_search:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 200
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.search.interpolation_search_entry:
std.search.interpolation_search_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  subq $9, rax
  movq rax, $r5
  jmp std.search.interpolation_search_block_6
std.search.interpolation_search_block_6:
  movq $1, rax
  cmpq $r5, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.search.interpolation_search_block_9
  jmp std.search.interpolation_search_block_13
std.search.interpolation_search_block_9:
  jmp std.search.interpolation_search_block_9
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -72], rax
  cmpq $r10, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -88]
  jmp std.search.interpolation_search_block_13
std.search.interpolation_search_block_13:
  movq [rbp + -88], rax
  testq rax, rax
  jne std.search.interpolation_search_block_15
  jmp std.search.interpolation_search_block_19
std.search.interpolation_search_block_15:
  jmp std.search.interpolation_search_block_15
  movq [rbp + -64], rcx
  movq $r5, rdx
  call lm_list_get
  movq [rbp + -72], rax
  cmpq $r12, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -96]
  jmp std.search.interpolation_search_block_19
std.search.interpolation_search_block_19:
  movq [rbp + -96], rax
  testq rax, rax
  jne std.search.interpolation_search_block_20
  jmp std.search.interpolation_search_block_64
std.search.interpolation_search_block_20:
  jmp std.search.interpolation_search_block_20
  movq $1, rax
  cmpq $r5, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.search.interpolation_search_block_22
  jmp std.search.interpolation_search_block_29
std.search.interpolation_search_block_22:
  jmp std.search.interpolation_search_block_22
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r17, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.search.interpolation_search_block_25
  jmp std.search.interpolation_search_block_26
std.search.interpolation_search_block_25:
  jmp std.search.interpolation_search_block_25
  movq $1, rax
  jmp std.search.interpolation_search_epilogue
std.search.interpolation_search_block_26:
  movq $9, rax
  negq rax
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  jmp std.search.interpolation_search_epilogue
std.search.interpolation_search_block_29:
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -72], rax
  subq $r22, rax
  movq rax, [rbp + -128]
  movq $r5, rax
  subq $1, rax
  movq rax, $r24
  movq [rbp + -128], rax
  imulq $r24, rax
  movq rax, [rbp + -136]
  movq [rbp + -64], rcx
  movq $r5, rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r26, rax
  subq $r27, rax
  movq rax, $r28
  movq [rbp + -136], rax
  cqto
  movq $r28, rcx
  idivq rcx
  movq rax, [rbp + -144]
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -72], rax
  subq $r30, rax
  movq rax, [rbp + -152]
  movq $r5, rax
  subq $1, rax
  movq rax, $r32
  movq [rbp + -152], rax
  imulq $r32, rax
  movq rax, [rbp + -160]
  movq [rbp + -64], rcx
  movq $r5, rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r34, rax
  subq $r35, rax
  movq rax, $r36
  movq [rbp + -160], rax
  cqto
  movq $r36, rcx
  idivq rcx
  movq rax, [rbp + -168]
  movq $1, rax
  addq [rbp + -168], rax
  movq rax, [rbp + -176]
  movq [rbp + -64], rcx
  movq [rbp + -176], rdx
  call lm_list_get
  movq $r40, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  testq rax, rax
  jne std.search.interpolation_search_block_50
  jmp std.search.interpolation_search_block_51
std.search.interpolation_search_block_50:
  jmp std.search.interpolation_search_block_50
  movq [rbp + -176], rax
  jmp std.search.interpolation_search_epilogue
std.search.interpolation_search_block_51:
  movq [rbp + -64], rcx
  movq [rbp + -176], rdx
  call lm_list_get
  movq $r43, rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  testq rax, rax
  jne std.search.interpolation_search_block_54
  jmp std.search.interpolation_search_block_59
std.search.interpolation_search_block_54:
  jmp std.search.interpolation_search_block_54
  movq [rbp + -176], rax
  addq $9, rax
  movq rax, [rbp + -200]
  jmp std.search.interpolation_search_block_63
std.search.interpolation_search_block_59:
  movq [rbp + -176], rax
  subq $9, rax
  movq rax, [rbp + -208]
  jmp std.search.interpolation_search_block_63
std.search.interpolation_search_block_63:
  jmp std.search.interpolation_search_block_6
std.search.interpolation_search_block_64:
  movq $9, rax
  negq rax
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  jmp std.search.interpolation_search_epilogue
std.search.interpolation_search_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.search.interpolation_search:

.globl std.algorithm.index.upper_bound
std.algorithm.index.upper_bound:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.upper_bound_entry:
std.algorithm.index.upper_bound_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.binary_search.upper_bound
  movq $r2, rax
  jmp std.algorithm.index.upper_bound_epilogue
std.algorithm.index.upper_bound_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.upper_bound:

.globl std.search.upper_bound
std.search.upper_bound:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 104
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.search.upper_bound_entry:
std.search.upper_bound_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.search.upper_bound_block_4
std.search.upper_bound_block_4:
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.search.upper_bound_block_6
  jmp std.search.upper_bound_block_21
std.search.upper_bound_block_6:
  jmp std.search.upper_bound_block_6
  movq $1, rax
  addq $r3, rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call lm_list_get
  movq $r11, rax
  cmpq [rbp + -72], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.search.upper_bound_block_13
  jmp std.search.upper_bound_block_18
std.search.upper_bound_block_13:
  jmp std.search.upper_bound_block_13
  movq [rbp + -96], rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.search.upper_bound_block_20
std.search.upper_bound_block_18:
  jmp std.search.upper_bound_block_20
std.search.upper_bound_block_20:
  jmp std.search.upper_bound_block_4
std.search.upper_bound_block_21:
  movq [rbp + -112], rax
  jmp std.search.upper_bound_epilogue
std.search.upper_bound_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.search.upper_bound:

.globl std.algorithm.filter.remove_if
std.algorithm.filter.remove_if:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.filter.remove_if_entry:
std.algorithm.filter.remove_if_block_0:
  movq $0, rcx
  call lm_list_new
  jmp std.algorithm.filter.remove_if_block_4
std.algorithm.filter.remove_if_block_4:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.filter.remove_if_block_7
  jmp std.algorithm.filter.remove_if_block_20
std.algorithm.filter.remove_if_block_7:
  jmp std.algorithm.filter.remove_if_block_7
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r8, rcx
  call 
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.algorithm.filter.remove_if_block_12
  jmp std.algorithm.filter.remove_if_block_15
std.algorithm.filter.remove_if_block_12:
  jmp std.algorithm.filter.remove_if_block_12
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r2, rcx
  movq $r13, rdx
  call lm_list_append
  jmp std.algorithm.filter.remove_if_block_15
std.algorithm.filter.remove_if_block_15:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.algorithm.filter.remove_if_block_4
std.algorithm.filter.remove_if_block_20:
  movq $r2, rax
  jmp std.algorithm.filter.remove_if_epilogue
std.algorithm.filter.remove_if_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.filter.remove_if:

.globl std.sort.partial_sort
std.sort.partial_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.sort.partial_sort_entry:
std.sort.partial_sort_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -80], rdx
  movq [rbp + -88], r8
  call std.sort.quicksort
  movq [rbp + -72], rax
  cmpq $1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.sort.partial_sort_block_4
  jmp std.sort.partial_sort_block_5
std.sort.partial_sort_block_4:
  jmp std.sort.partial_sort_block_4
  movq $0, rax
  jmp std.sort.partial_sort_epilogue
std.sort.partial_sort_block_5:
  movq $0, rax
  jmp std.sort.partial_sort_epilogue
std.sort.partial_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort.partial_sort:

.globl std.algorithm.index.radix_sort
std.algorithm.index.radix_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.index.radix_sort_entry:
std.algorithm.index.radix_sort_block_0:
  movq [rbp + -64], rcx
  call std.algorithm.sort.radix_sort
  movq $0, rax
  jmp std.algorithm.index.radix_sort_epilogue
std.algorithm.index.radix_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.radix_sort:

.globl std.sort.heapsort
std.sort.heapsort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 120
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.sort.heapsort_entry:
std.sort.heapsort_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  cmpq $9, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.sort.heapsort_block_5
  jmp std.sort.heapsort_block_6
std.sort.heapsort_block_5:
  jmp std.sort.heapsort_block_5
  movq $0, rax
  jmp std.sort.heapsort_epilogue
std.sort.heapsort_block_6:
  movq $r3, rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rax, $r9
  movq $r9, rax
  subq $9, rax
  movq rax, $r11
  jmp std.sort.heapsort_block_12
std.sort.heapsort_block_12:
  movq $r11, rax
  cmpq $1, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.sort.heapsort_block_15
  jmp std.sort.heapsort_block_20
std.sort.heapsort_block_15:
  jmp std.sort.heapsort_block_15
  movq [rbp + -64], rcx
  movq $r3, rdx
  movq $r11, r8
  movq [rbp + -72], r9
  call std.sort._heapify
  movq $r11, rax
  subq $9, rax
  movq rax, $r18
  jmp std.sort.heapsort_block_12
std.sort.heapsort_block_20:
  movq $r3, rax
  subq $9, rax
  movq rax, $r20
  jmp std.sort.heapsort_block_24
std.sort.heapsort_block_24:
  movq $r20, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.sort.heapsort_block_27
  jmp std.sort.heapsort_block_35
std.sort.heapsort_block_27:
  jmp std.sort.heapsort_block_27
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $r20, r8
  call std.sort._swap
  movq [rbp + -64], rcx
  movq $r20, rdx
  movq $1, r8
  movq [rbp + -72], r9
  call std.sort._heapify
  movq $r20, rax
  subq $9, rax
  movq rax, $r29
  jmp std.sort.heapsort_block_24
std.sort.heapsort_block_35:
  movq [rbp + -72], rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.sort.heapsort_block_38
  jmp std.sort.heapsort_block_39
std.sort.heapsort_block_38:
  jmp std.sort.heapsort_block_38
  movq $0, rax
  jmp std.sort.heapsort_epilogue
std.sort.heapsort_block_39:
  movq $r3, rax
  subq $9, rax
  movq rax, $r35
  jmp std.sort.heapsort_block_44
std.sort.heapsort_block_44:
  movq $1, rax
  cmpq $r35, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.sort.heapsort_block_46
  jmp std.sort.heapsort_block_55
std.sort.heapsort_block_46:
  jmp std.sort.heapsort_block_46
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $r35, r8
  call std.sort._swap
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -128]
  movq $r35, rax
  subq $9, rax
  movq rax, $r44
  jmp std.sort.heapsort_block_44
std.sort.heapsort_block_55:
  movq $0, rax
  jmp std.sort.heapsort_epilogue
std.sort.heapsort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort.heapsort:

.globl std.sort._heapify
std.sort._heapify:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 168
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.sort._heapify_entry:
std.sort._heapify_block_0:
  movq $17, rax
  imulq [rbp + -80], rax
  movq rax, [rbp + -104]
  movq $17, rax
  imulq [rbp + -80], rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  addq $9, rax
  movq rax, [rbp + -120]
  movq $17, rax
  imulq [rbp + -80], rax
  movq rax, [rbp + -128]
  movq $17, rax
  imulq [rbp + -80], rax
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  addq $17, rax
  movq rax, [rbp + -144]
  movq [rbp + -120], rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne std.sort._heapify_block_20
  jmp std.sort._heapify_block_27
std.sort._heapify_block_20:
  jmp std.sort._heapify_block_20
  movq [rbp + -64], rcx
  movq [rbp + -120], rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq [rbp + -80], rdx
  call lm_list_get
  movq $r24, rcx
  movq $r25, rdx
  movq [rbp + -88], r8
  movq [rbp + -96], r9
  call std.sort._compare
  movq $r26, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -160]
  jmp std.sort._heapify_block_27
std.sort._heapify_block_27:
  movq [rbp + -160], rax
  testq rax, rax
  jne std.sort._heapify_block_28
  jmp std.sort._heapify_block_30
std.sort._heapify_block_28:
  jmp std.sort._heapify_block_28
  jmp std.sort._heapify_block_30
std.sort._heapify_block_30:
  movq [rbp + -144], rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  testq rax, rax
  jne std.sort._heapify_block_33
  jmp std.sort._heapify_block_40
std.sort._heapify_block_33:
  jmp std.sort._heapify_block_33
  movq [rbp + -64], rcx
  movq [rbp + -144], rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq [rbp + -120], rdx
  call lm_list_get
  movq $r32, rcx
  movq $r33, rdx
  movq [rbp + -88], r8
  movq [rbp + -96], r9
  call std.sort._compare
  movq $r34, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -176]
  jmp std.sort._heapify_block_40
std.sort._heapify_block_40:
  movq [rbp + -176], rax
  testq rax, rax
  jne std.sort._heapify_block_41
  jmp std.sort._heapify_block_43
std.sort._heapify_block_41:
  jmp std.sort._heapify_block_41
  jmp std.sort._heapify_block_43
std.sort._heapify_block_43:
  movq [rbp + -144], rax
  cmpq [rbp + -80], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  testq rax, rax
  jne std.sort._heapify_block_45
  jmp std.sort._heapify_block_48
std.sort._heapify_block_45:
  jmp std.sort._heapify_block_45
  movq [rbp + -64], rcx
  movq [rbp + -80], rdx
  movq [rbp + -144], r8
  call std.sort._swap
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -144], r8
  movq [rbp + -88], r9
  call std.sort._heapify
  jmp std.sort._heapify_block_48
std.sort._heapify_block_48:
  movq $0, rax
  jmp std.sort._heapify_epilogue
std.sort._heapify_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort._heapify:

.globl std.sort._mergesort_range
std.sort._mergesort_range:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 120
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.sort._mergesort_range_entry:
std.sort._mergesort_range_block_0:
  movq [rbp + -72], rax
  cmpq [rbp + -80], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.sort._mergesort_range_block_2
  jmp std.sort._mergesort_range_block_13
std.sort._mergesort_range_block_2:
  jmp std.sort._mergesort_range_block_2
  movq [rbp + -72], rax
  addq [rbp + -80], rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rax, [rbp + -120]
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -120], r8
  movq [rbp + -88], r9
  call std.sort._mergesort_range
  movq [rbp + -120], rax
  addq $9, rax
  movq rax, [rbp + -128]
  movq [rbp + -64], rcx
  movq [rbp + -128], rdx
  movq [rbp + -80], r8
  movq [rbp + -88], r9
  call std.sort._mergesort_range
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -120], r8
  movq [rbp + -80], r9
  call std.sort._merge
  jmp std.sort._mergesort_range_block_13
std.sort._mergesort_range_block_13:
  movq $0, rax
  jmp std.sort._mergesort_range_epilogue
std.sort._mergesort_range_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort._mergesort_range:

.globl std.sort.insertion_sort
std.sort.insertion_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 136
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.sort.insertion_sort_entry:
std.sort.insertion_sort_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.sort.insertion_sort_block_4
std.sort.insertion_sort_block_4:
  movq $9, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.sort.insertion_sort_block_6
  jmp std.sort.insertion_sort_block_41
std.sort.insertion_sort_block_6:
  jmp std.sort.insertion_sort_block_6
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  movq $9, rax
  subq $9, rax
  movq rax, [rbp + -96]
  jmp std.sort.insertion_sort_block_12
std.sort.insertion_sort_block_12:
  movq [rbp + -96], rax
  cmpq $1, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.sort.insertion_sort_block_16
  jmp std.sort.insertion_sort_block_22
std.sort.insertion_sort_block_16:
  jmp std.sort.insertion_sort_block_16
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call lm_list_get
  movq $r16, rcx
  movq $r8, rdx
  movq [rbp + -72], r8
  movq [rbp + -80], r9
  call std.sort._compare
  movq $r17, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -112]
  jmp std.sort.insertion_sort_block_22
std.sort.insertion_sort_block_22:
  movq [rbp + -112], rax
  testq rax, rax
  jne std.sort.insertion_sort_block_23
  jmp std.sort.insertion_sort_block_32
std.sort.insertion_sort_block_23:
  jmp std.sort.insertion_sort_block_23
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call lm_list_get
  movq [rbp + -96], rax
  addq $9, rax
  movq rax, [rbp + -120]
  movq [rbp + -96], rax
  subq $9, rax
  movq rax, [rbp + -128]
  jmp std.sort.insertion_sort_block_12
std.sort.insertion_sort_block_32:
  movq [rbp + -128], rax
  addq $9, rax
  movq rax, [rbp + -136]
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.sort.insertion_sort_block_4
std.sort.insertion_sort_block_41:
  movq $0, rax
  jmp std.sort.insertion_sort_epilogue
std.sort.insertion_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort.insertion_sort:

.globl sum_reducer
sum_reducer:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
sum_reducer_entry:
sum_reducer_block_0:
  movq [rbp + -64], rax
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  movq rax, [rbp + -88]
  movq [rbp + -80], rax
  addq [rbp + -88], rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp sum_reducer_epilogue
sum_reducer_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_sum_reducer:

.globl std.algorithm.partition.partition
std.algorithm.partition.partition:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 136
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.partition.partition_entry:
std.algorithm.partition.partition_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  subq $9, rax
  movq rax, $r5
  jmp std.algorithm.partition.partition_block_6
std.algorithm.partition.partition_block_6:
  movq $1, rax
  cmpq $r5, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.partition.partition_block_8
  jmp std.algorithm.partition.partition_block_53
std.algorithm.partition.partition_block_8:
  jmp std.algorithm.partition.partition_block_8
  jmp std.algorithm.partition.partition_block_9
std.algorithm.partition.partition_block_9:
  movq $1, rax
  cmpq $r5, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.algorithm.partition.partition_block_12
  jmp std.algorithm.partition.partition_block_16
std.algorithm.partition.partition_block_12:
  jmp std.algorithm.partition.partition_block_12
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r11, rcx
  call 
  movq rax, [rbp + -96]
  jmp std.algorithm.partition.partition_block_16
std.algorithm.partition.partition_block_16:
  movq [rbp + -96], rax
  testq rax, rax
  jne std.algorithm.partition.partition_block_17
  jmp std.algorithm.partition.partition_block_22
std.algorithm.partition.partition_block_17:
  jmp std.algorithm.partition.partition_block_17
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.algorithm.partition.partition_block_9
std.algorithm.partition.partition_block_22:
  jmp std.algorithm.partition.partition_block_23
std.algorithm.partition.partition_block_23:
  movq [rbp + -104], rax
  cmpq $r5, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.algorithm.partition.partition_block_26
  jmp std.algorithm.partition.partition_block_32
std.algorithm.partition.partition_block_26:
  jmp std.algorithm.partition.partition_block_26
  movq [rbp + -64], rcx
  movq $r5, rdx
  call lm_list_get
  movq $r19, rcx
  call 
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -128]
  jmp std.algorithm.partition.partition_block_32
std.algorithm.partition.partition_block_32:
  movq [rbp + -128], rax
  testq rax, rax
  jne std.algorithm.partition.partition_block_33
  jmp std.algorithm.partition.partition_block_37
std.algorithm.partition.partition_block_33:
  jmp std.algorithm.partition.partition_block_33
  movq $r5, rax
  subq $9, rax
  movq rax, $r25
  jmp std.algorithm.partition.partition_block_23
std.algorithm.partition.partition_block_37:
  movq [rbp + -104], rax
  cmpq $r25, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne std.algorithm.partition.partition_block_39
  jmp std.algorithm.partition.partition_block_52
std.algorithm.partition.partition_block_39:
  jmp std.algorithm.partition.partition_block_39
  movq [rbp + -64], rcx
  movq [rbp + -104], rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq $r25, rdx
  call lm_list_get
  movq [rbp + -104], rax
  addq $9, rax
  movq rax, [rbp + -144]
  movq $r25, rax
  subq $9, rax
  movq rax, $r37
  jmp std.algorithm.partition.partition_block_52
std.algorithm.partition.partition_block_52:
  jmp std.algorithm.partition.partition_block_6
std.algorithm.partition.partition_block_53:
  movq [rbp + -144], rax
  jmp std.algorithm.partition.partition_epilogue
std.algorithm.partition.partition_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.partition.partition:

.globl std.algorithm.sort.counting_sort
std.algorithm.sort.counting_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.sort.counting_sort_entry:
std.algorithm.sort.counting_sort_block_0:
  movq [rbp + -64], rcx
  movq $10, rdx
  call std.sort.counting_sort
  movq $0, rax
  jmp std.algorithm.sort.counting_sort_epilogue
std.algorithm.sort.counting_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.sort.counting_sort:

.globl std.algorithm.search.none
std.algorithm.search.none:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.search.none_entry:
std.algorithm.search.none_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.search.any_match
  movq $r2, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.algorithm.search.none_epilogue
std.algorithm.search.none_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.search.none:

.globl test_transform
test_transform:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 248
test_transform_entry:
test_transform_block_0:
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $r2, rcx
  movq $9, rdx
  call lm_list_append
  movq $r2, rcx
  movq $17, rdx
  call lm_list_append
  movq $r2, rcx
  movq $25, rdx
  call lm_list_append
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r2, rcx
  movq [rbp + -96], rdx
  call std.algorithm.index.map
  movq $r11, rcx
  movq $1, rdx
  call lm_list_get
  movq $r14, rax
  cmpq $89, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq $r11, rcx
  movq $9, rdx
  call lm_list_get
  movq $r20, rax
  cmpq $97, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq $r11, rcx
  movq $17, rdx
  call lm_list_get
  movq $r26, rax
  cmpq $105, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  movq $0, rcx
  call lm_list_new
  movq $r31, rcx
  movq $9, rdx
  call lm_list_append
  movq $r31, rcx
  movq $17, rdx
  call lm_list_append
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq $r36, rcx
  movq [rbp + -152], rdx
  call lm_list_append
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq $r36, rcx
  movq [rbp + -160], rdx
  call lm_list_append
  movq $r31, rcx
  movq $r36, rdx
  call std.algorithm.index.zip
  movq $r41, rcx
  movq $1, rdx
  call lm_list_get
  movq $r44, rax
  movq rax, [rbp + -168]
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq $0, rax
  cmpq [rbp + -192], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -200], rcx
  movq [rbp + -208], rdx
  call lm_assert
  movq $r41, rcx
  call std.algorithm.index.unzip
  movq $0, rax
  movq rax, [rbp + -216]
  movq $0, rax
  movq rax, [rbp + -224]
  movq [rbp + -216], rcx
  movq $1, rdx
  call lm_list_get
  movq $r70, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rcx
  movq [rbp + -240], rdx
  call lm_assert
  movq [rbp + -224], rcx
  movq $1, rdx
  call lm_list_get
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq $r76, rax
  cmpq [rbp + -248], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -256], rcx
  movq [rbp + -264], rdx
  call lm_assert
  movq $9, rax
  jmp test_transform_epilogue
test_transform_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_transform:

.globl std.algorithm.search.__init__
std.algorithm.search.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.algorithm.search.__init___entry:
  movq $0, rax
  jmp std.algorithm.search.__init___epilogue
std.algorithm.search.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.search.__init__:

.globl std.algorithm.index.partition_copy
std.algorithm.index.partition_copy:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.partition_copy_entry:
std.algorithm.index.partition_copy_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.partition.partition_copy
  movq $r2, rax
  jmp std.algorithm.index.partition_copy_epilogue
std.algorithm.index.partition_copy_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.partition_copy:

.globl std.algorithm.unique.__init__
std.algorithm.unique.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.algorithm.unique.__init___entry:
  movq $0, rax
  jmp std.algorithm.unique.__init___epilogue
std.algorithm.unique.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.unique.__init__:

.globl std.algorithm.search.count
std.algorithm.search.count:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.search.count_entry:
std.algorithm.search.count_block_0:
  jmp std.algorithm.search.count_block_3
std.algorithm.search.count_block_3:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r4, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.search.count_block_6
  jmp std.algorithm.search.count_block_19
std.algorithm.search.count_block_6:
  jmp std.algorithm.search.count_block_6
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r7, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.algorithm.search.count_block_9
  jmp std.algorithm.search.count_block_14
std.algorithm.search.count_block_9:
  jmp std.algorithm.search.count_block_9
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  jmp std.algorithm.search.count_block_14
std.algorithm.search.count_block_14:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.algorithm.search.count_block_3
std.algorithm.search.count_block_19:
  movq [rbp + -96], rax
  jmp std.algorithm.search.count_epilogue
std.algorithm.search.count_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.search.count:

.globl std.sort._quicksort_range
std.sort._quicksort_range:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.sort._quicksort_range_entry:
std.sort._quicksort_range_block_0:
  movq [rbp + -72], rax
  cmpq [rbp + -80], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.sort._quicksort_range_block_2
  jmp std.sort._quicksort_range_block_12
std.sort._quicksort_range_block_2:
  jmp std.sort._quicksort_range_block_2
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  movq [rbp + -88], r9
  call std.sort._partition
  movq $r7, rax
  subq $9, rax
  movq rax, $r10
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq $r10, r8
  movq [rbp + -88], r9
  call std.sort._quicksort_range
  movq $r7, rax
  addq $9, rax
  movq rax, $r14
  movq [rbp + -64], rcx
  movq $r14, rdx
  movq [rbp + -80], r8
  movq [rbp + -88], r9
  call std.sort._quicksort_range
  jmp std.sort._quicksort_range_block_12
std.sort._quicksort_range_block_12:
  movq $0, rax
  jmp std.sort._quicksort_range_epilogue
std.sort._quicksort_range_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort._quicksort_range:

.globl std.algorithm.filter.__init__
std.algorithm.filter.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.algorithm.filter.__init___entry:
  movq $0, rax
  jmp std.algorithm.filter.__init___epilogue
std.algorithm.filter.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.filter.__init__:

.globl std.sort.stable_sort
std.sort.stable_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.sort.stable_sort_entry:
std.sort.stable_sort_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.sort.mergesort
  movq $0, rax
  jmp std.sort.stable_sort_epilogue
std.sort.stable_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort.stable_sort:

.globl test_shuffle
test_shuffle:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 104
test_shuffle_entry:
test_shuffle_block_0:
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $r2, rcx
  movq $9, rdx
  call lm_list_append
  movq $r2, rcx
  movq $17, rdx
  call lm_list_append
  movq $r2, rcx
  movq $25, rdx
  call lm_list_append
  movq $r2, rcx
  movq $33, rdx
  call lm_list_append
  movq $r2, rcx
  movq $41, rdx
  call lm_list_append
  movq $r2, rcx
  movq $49, rdx
  call lm_list_append
  movq $r2, rcx
  movq $57, rdx
  call lm_list_append
  movq $r2, rcx
  movq $65, rdx
  call lm_list_append
  movq $r2, rcx
  movq $73, rdx
  call lm_list_append
  movq $r2, rcx
  movq $81, rdx
  call lm_list_append
  movq $r2, rcx
  call std.algorithm.index.shuffle
  movq $r2, rcx
  call lm_list_len
  movq $r25, rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  movq $r2, rcx
  movq $41, rdx
  call std.algorithm.index.count
  movq $r31, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq $9, rax
  jmp test_shuffle_epilogue
test_shuffle_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_shuffle:

.globl std.algorithm.index.find_if
std.algorithm.index.find_if:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.find_if_entry:
std.algorithm.index.find_if_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.search.find_if
  movq $r2, rax
  jmp std.algorithm.index.find_if_epilogue
std.algorithm.index.find_if_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.find_if:

.globl std.algorithm.index.none
std.algorithm.index.none:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.none_entry:
std.algorithm.index.none_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.search.none
  movq $r2, rax
  jmp std.algorithm.index.none_epilogue
std.algorithm.index.none_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.none:

.globl std.algorithm.search.find
std.algorithm.search.find:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.search.find_entry:
std.algorithm.search.find_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.search.linear_search
  movq $r2, rax
  jmp std.algorithm.search.find_epilogue
std.algorithm.search.find_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.search.find:

.globl std.sort.__init__
std.sort.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.sort.__init___entry:
  movq $0, rax
  jmp std.sort.__init___epilogue
std.sort.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort.__init__:

.globl std.sort._merge
std.sort._merge:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 200
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.sort._merge_entry:
std.sort._merge_block_0:
  movq $0, rcx
  call lm_list_new
  movq [rbp + -80], rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.sort._merge_block_8
std.sort._merge_block_8:
  movq [rbp + -72], rax
  cmpq [rbp + -80], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.sort._merge_block_11
  jmp std.sort._merge_block_14
std.sort._merge_block_11:
  jmp std.sort._merge_block_11
  movq [rbp + -112], rax
  cmpq [rbp + -88], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -128]
  jmp std.sort._merge_block_14
std.sort._merge_block_14:
  movq [rbp + -128], rax
  testq rax, rax
  jne std.sort._merge_block_15
  jmp std.sort._merge_block_36
std.sort._merge_block_15:
  jmp std.sort._merge_block_15
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq [rbp + -112], rdx
  call lm_list_get
  movq $r17, rcx
  movq $r18, rdx
  movq [rbp + -96], r8
  movq [rbp + -104], r9
  call std.sort._compare
  movq $r19, rax
  cmpq $1, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne std.sort._merge_block_21
  jmp std.sort._merge_block_28
std.sort._merge_block_21:
  jmp std.sort._merge_block_21
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call lm_list_get
  movq $r6, rcx
  movq $r23, rdx
  call lm_list_append
  movq [rbp + -72], rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.sort._merge_block_35
std.sort._merge_block_28:
  movq [rbp + -64], rcx
  movq [rbp + -112], rdx
  call lm_list_get
  movq $r6, rcx
  movq $r29, rdx
  call lm_list_append
  movq [rbp + -112], rax
  addq $9, rax
  movq rax, [rbp + -152]
  jmp std.sort._merge_block_35
std.sort._merge_block_35:
  jmp std.sort._merge_block_8
std.sort._merge_block_36:
  jmp std.sort._merge_block_37
std.sort._merge_block_37:
  movq [rbp + -144], rax
  cmpq [rbp + -80], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  testq rax, rax
  jne std.sort._merge_block_39
  jmp std.sort._merge_block_46
std.sort._merge_block_39:
  jmp std.sort._merge_block_39
  movq [rbp + -64], rcx
  movq [rbp + -144], rdx
  call lm_list_get
  movq $r6, rcx
  movq $r37, rdx
  call lm_list_append
  movq [rbp + -144], rax
  addq $9, rax
  movq rax, [rbp + -168]
  jmp std.sort._merge_block_37
std.sort._merge_block_46:
  jmp std.sort._merge_block_47
std.sort._merge_block_47:
  movq [rbp + -152], rax
  cmpq [rbp + -88], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne std.sort._merge_block_49
  jmp std.sort._merge_block_56
std.sort._merge_block_49:
  jmp std.sort._merge_block_49
  movq [rbp + -64], rcx
  movq [rbp + -152], rdx
  call lm_list_get
  movq $r6, rcx
  movq $r45, rdx
  call lm_list_append
  movq [rbp + -152], rax
  addq $9, rax
  movq rax, [rbp + -184]
  jmp std.sort._merge_block_47
std.sort._merge_block_56:
  jmp std.sort._merge_block_58
std.sort._merge_block_58:
  movq $r6, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r52, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  testq rax, rax
  jne std.sort._merge_block_61
  jmp std.sort._merge_block_69
std.sort._merge_block_61:
  jmp std.sort._merge_block_61
  movq $r6, rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -72], rax
  addq $1, rax
  movq rax, [rbp + -200]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -208]
  jmp std.sort._merge_block_58
std.sort._merge_block_69:
  movq $0, rax
  jmp std.sort._merge_epilogue
std.sort._merge_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort._merge:

.globl std.algorithm.index.unzip
std.algorithm.index.unzip:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.index.unzip_entry:
std.algorithm.index.unzip_block_0:
  movq [rbp + -64], rcx
  call std.algorithm.transform.unzip
  movq $r1, rax
  jmp std.algorithm.index.unzip_epilogue
std.algorithm.index.unzip_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.unzip:

.globl add_ten
add_ten:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
add_ten_entry:
add_ten_block_0:
  movq [rbp + -64], rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  addq $81, rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp add_ten_epilogue
add_ten_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_add_ten:

.globl std.algorithm.index.sort
std.algorithm.index.sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.index.sort_entry:
std.algorithm.index.sort_block_0:
  movq [rbp + -64], rcx
  call std.algorithm.sort.sort
  movq $0, rax
  jmp std.algorithm.index.sort_epilogue
std.algorithm.index.sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.sort:

.globl std.algorithm.search.all
std.algorithm.search.all:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.search.all_entry:
std.algorithm.search.all_block_0:
  jmp std.algorithm.search.all_block_2
std.algorithm.search.all_block_2:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.search.all_block_5
  jmp std.algorithm.search.all_block_17
std.algorithm.search.all_block_5:
  jmp std.algorithm.search.all_block_5
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r6, rcx
  call 
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.algorithm.search.all_block_10
  jmp std.algorithm.search.all_block_12
std.algorithm.search.all_block_10:
  jmp std.algorithm.search.all_block_10
  movq $10, rax
  jmp std.algorithm.search.all_epilogue
std.algorithm.search.all_block_12:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.algorithm.search.all_block_2
std.algorithm.search.all_block_17:
  movq $18, rax
  jmp std.algorithm.search.all_epilogue
std.algorithm.search.all_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.search.all:

.globl test_reduce
test_reduce:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 120
test_reduce_entry:
test_reduce_block_0:
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $r2, rcx
  movq $9, rdx
  call lm_list_append
  movq $r2, rcx
  movq $17, rdx
  call lm_list_append
  movq $r2, rcx
  movq $25, rdx
  call lm_list_append
  movq $r2, rcx
  movq $33, rdx
  call lm_list_append
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r2, rcx
  movq [rbp + -96], rdx
  movq $1, r8
  call std.algorithm.index.reduce
  movq $r14, rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq $r2, rcx
  movq $81, rdx
  movq [rbp + -120], r8
  call std.algorithm.index.fold
  movq $r22, rax
  cmpq $161, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq $9, rax
  jmp test_reduce_epilogue
test_reduce_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_reduce:

.globl std.search.linear_search
std.search.linear_search:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.search.linear_search_entry:
std.search.linear_search_block_0:
  jmp std.search.linear_search_block_1
std.search.linear_search_block_1:
  jmp std.search.linear_search_block_3
std.search.linear_search_block_3:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r4, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.search.linear_search_block_6
  jmp std.search.linear_search_block_16
std.search.linear_search_block_6:
  jmp std.search.linear_search_block_6
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r6, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.search.linear_search_block_9
  jmp std.search.linear_search_block_10
std.search.linear_search_block_9:
  jmp std.search.linear_search_block_9
  movq $1, rax
  jmp std.search.linear_search_epilogue
std.search.linear_search_block_10:
  jmp std.search.linear_search_block_11
std.search.linear_search_block_11:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  jmp std.search.linear_search_block_3
std.search.linear_search_block_16:
  movq $9, rax
  negq rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  jmp std.search.linear_search_epilogue
std.search.linear_search_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.search.linear_search:

.globl std.sort.mergesort
std.sort.mergesort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.sort.mergesort_entry:
std.sort.mergesort_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  cmpq $9, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.sort.mergesort_block_4
  jmp std.sort.mergesort_block_10
std.sort.mergesort_block_4:
  jmp std.sort.mergesort_block_4
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r8, rax
  subq $9, rax
  movq rax, $r10
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $r10, r8
  movq [rbp + -72], r9
  call std.sort._mergesort_range
  jmp std.sort.mergesort_block_10
std.sort.mergesort_block_10:
  movq $0, rax
  jmp std.sort.mergesort_epilogue
std.sort.mergesort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort.mergesort:

.globl std.algorithm.sort.mergesort
std.algorithm.sort.mergesort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.sort.mergesort_entry:
std.algorithm.sort.mergesort_block_0:
  movq [rbp + -64], rcx
  movq $10, rdx
  movq $2, r8
  call std.sort.mergesort
  movq $0, rax
  jmp std.algorithm.sort.mergesort_epilogue
std.algorithm.sort.mergesort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.sort.mergesort:

.globl std.algorithm.sort.partial_sort
std.algorithm.sort.partial_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.sort.partial_sort_entry:
std.algorithm.sort.partial_sort_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq $10, r8
  movq $2, r9
  call std.sort.partial_sort
  movq $0, rax
  jmp std.algorithm.sort.partial_sort_epilogue
std.algorithm.sort.partial_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.sort.partial_sort:

.globl std.algorithm.index.reduce
std.algorithm.index.reduce:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.algorithm.index.reduce_entry:
std.algorithm.index.reduce_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.algorithm.reduce.reduce
  movq $r3, rax
  jmp std.algorithm.index.reduce_epilogue
std.algorithm.index.reduce_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.reduce:

.globl test_search
test_search:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 312
test_search_entry:
test_search_block_0:
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $r2, rcx
  movq $9, rdx
  call lm_list_append
  movq $r2, rcx
  movq $17, rdx
  call lm_list_append
  movq $r2, rcx
  movq $25, rdx
  call lm_list_append
  movq $r2, rcx
  movq $33, rdx
  call lm_list_append
  movq $r2, rcx
  movq $41, rdx
  call lm_list_append
  movq $r2, rcx
  movq $25, rdx
  call std.algorithm.index.find
  movq $r15, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  movq $r2, rcx
  movq $81, rdx
  call std.algorithm.index.find
  movq $9, rax
  negq rax
  movq rax, [rbp + -112]
  movq $r21, rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r2, rcx
  movq [rbp + -136], rdx
  call std.algorithm.index.find_if
  movq $r28, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq $r2, rcx
  movq [rbp + -160], rdx
  call std.algorithm.index.any_match
  movq $r34, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call lm_assert
  movq $0, rcx
  call lm_list_new
  movq $r39, rcx
  movq $9, rdx
  call lm_list_append
  movq $r39, rcx
  movq $25, rdx
  call lm_list_append
  movq $r39, rcx
  movq $41, rdx
  call lm_list_append
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq $r39, rcx
  movq [rbp + -184], rdx
  call std.algorithm.index.any_match
  movq $r47, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq $0, rcx
  call lm_list_new
  movq $r52, rcx
  movq $9, rdx
  call lm_list_append
  movq $r52, rcx
  movq $25, rdx
  call lm_list_append
  movq $r52, rcx
  movq $41, rdx
  call lm_list_append
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq $r52, rcx
  movq [rbp + -208], rdx
  call std.algorithm.index.none
  movq $r60, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -216]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -216], rcx
  movq [rbp + -224], rdx
  call lm_assert
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq $r2, rcx
  movq [rbp + -232], rdx
  call std.algorithm.index.none
  movq $r66, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq $0, rcx
  call lm_list_new
  movq $r71, rcx
  movq $17, rdx
  call lm_list_append
  movq $r71, rcx
  movq $33, rdx
  call lm_list_append
  movq $r71, rcx
  movq $49, rdx
  call lm_list_append
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq $r71, rcx
  movq [rbp + -256], rdx
  call std.algorithm.index.all
  movq $r79, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -264]
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -264], rcx
  movq [rbp + -272], rdx
  call lm_assert
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq $r2, rcx
  movq [rbp + -280], rdx
  call std.algorithm.index.all
  movq $r85, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -288]
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -288], rcx
  movq [rbp + -296], rdx
  call lm_assert
  movq $0, rcx
  call lm_list_new
  movq $r90, rcx
  movq $9, rdx
  call lm_list_append
  movq $r90, rcx
  movq $17, rdx
  call lm_list_append
  movq $r90, rcx
  movq $17, rdx
  call lm_list_append
  movq $r90, rcx
  movq $25, rdx
  call lm_list_append
  movq $r90, rcx
  movq $17, rdx
  call lm_list_append
  movq $r90, rcx
  movq $17, rdx
  call std.algorithm.index.count
  movq $r102, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -304]
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -304], rcx
  movq [rbp + -312], rdx
  call lm_assert
  movq $r2, rcx
  movq $33, rdx
  call std.algorithm.index.linear_search
  movq $r108, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -320]
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -320], rcx
  movq [rbp + -328], rdx
  call lm_assert
  movq $9, rax
  jmp test_search_epilogue
test_search_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_search:

.globl std.algorithm.sort.quicksort_descending
std.algorithm.sort.quicksort_descending:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.sort.quicksort_descending_entry:
std.algorithm.sort.quicksort_descending_block_0:
  movq [rbp + -64], rcx
  movq $18, rdx
  movq $2, r8
  call std.sort.quicksort
  movq $0, rax
  jmp std.algorithm.sort.quicksort_descending_epilogue
std.algorithm.sort.quicksort_descending_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.sort.quicksort_descending:

.globl test_binary_search
test_binary_search:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 184
test_binary_search_entry:
test_binary_search_block_0:
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $r2, rcx
  movq $9, rdx
  call lm_list_append
  movq $r2, rcx
  movq $25, rdx
  call lm_list_append
  movq $r2, rcx
  movq $41, rdx
  call lm_list_append
  movq $r2, rcx
  movq $41, rdx
  call lm_list_append
  movq $r2, rcx
  movq $57, rdx
  call lm_list_append
  movq $r2, rcx
  movq $73, rdx
  call lm_list_append
  movq $r2, rcx
  movq $41, rdx
  call std.algorithm.index.binary_search
  movq $r18, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne test_binary_search_block_28
  jmp test_binary_search_block_22
test_binary_search_block_22:
  jmp test_binary_search_block_22
  movq $r2, rcx
  movq $41, rdx
  call std.algorithm.index.binary_search
  movq $r22, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  jmp test_binary_search_block_28
test_binary_search_block_28:
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq $r2, rcx
  movq $49, rdx
  call std.algorithm.index.binary_search
  movq $9, rax
  negq rax
  movq rax, [rbp + -120]
  movq $r28, rax
  cmpq [rbp + -120], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq $r2, rcx
  movq $41, rdx
  call std.algorithm.index.lower_bound
  movq $r35, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $r2, rcx
  movq $41, rdx
  call std.algorithm.index.upper_bound
  movq $r41, rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq $r2, rcx
  movq $41, rdx
  call std.algorithm.index.equal_range
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq $0, rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq $9, rax
  jmp test_binary_search_epilogue
test_binary_search_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_binary_search:

.globl std.algorithm.index.lower_bound
std.algorithm.index.lower_bound:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.lower_bound_entry:
std.algorithm.index.lower_bound_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.binary_search.lower_bound
  movq $r2, rax
  jmp std.algorithm.index.lower_bound_epilogue
std.algorithm.index.lower_bound_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.lower_bound:

.globl std.sort.sort
std.sort.sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.sort.sort_entry:
std.sort.sort_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.sort.quicksort
  movq $0, rax
  jmp std.sort.sort_epilogue
std.sort.sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort.sort:

.globl std.search.equal_range
std.search.equal_range:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.search.equal_range_entry:
std.search.equal_range_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.search.lower_bound
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.search.upper_bound
  movq $0, rax
  jmp std.search.equal_range_epilogue
std.search.equal_range_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.search.equal_range:

.globl std.algorithm.sort.stable_sort
std.algorithm.sort.stable_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.sort.stable_sort_entry:
std.algorithm.sort.stable_sort_block_0:
  movq [rbp + -64], rcx
  movq $10, rdx
  movq $2, r8
  call std.sort.stable_sort
  movq $0, rax
  jmp std.algorithm.sort.stable_sort_epilogue
std.algorithm.sort.stable_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.sort.stable_sort:

.globl test_unique
test_unique:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 152
test_unique_entry:
test_unique_block_0:
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $r2, rcx
  movq $9, rdx
  call lm_list_append
  movq $r2, rcx
  movq $17, rdx
  call lm_list_append
  movq $r2, rcx
  movq $17, rdx
  call lm_list_append
  movq $r2, rcx
  movq $25, rdx
  call lm_list_append
  movq $r2, rcx
  movq $9, rdx
  call lm_list_append
  movq $r2, rcx
  movq $33, rdx
  call lm_list_append
  movq $r2, rcx
  call std.algorithm.index.unique
  movq $r16, rcx
  call lm_list_len
  movq $r18, rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  movq $r16, rcx
  movq $1, rdx
  call lm_list_get
  movq $r24, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq $r16, rcx
  movq $9, rdx
  call lm_list_get
  movq $r30, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq $r16, rcx
  movq $17, rdx
  call lm_list_get
  movq $r36, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $r16, rcx
  movq $25, rdx
  call lm_list_get
  movq $r42, rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq $9, rax
  jmp test_unique_epilogue
test_unique_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_unique:

.globl std.algorithm.partition.partition_copy
std.algorithm.partition.partition_copy:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.partition.partition_copy_entry:
std.algorithm.partition.partition_copy_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  call lm_list_new
  jmp std.algorithm.partition.partition_copy_block_6
std.algorithm.partition.partition_copy_block_6:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r7, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.partition.partition_copy_block_9
  jmp std.algorithm.partition.partition_copy_block_23
std.algorithm.partition.partition_copy_block_9:
  jmp std.algorithm.partition.partition_copy_block_9
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r10, rcx
  call 
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.algorithm.partition.partition_copy_block_12
  jmp std.algorithm.partition.partition_copy_block_15
std.algorithm.partition.partition_copy_block_12:
  jmp std.algorithm.partition.partition_copy_block_12
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r2, rcx
  movq $r13, rdx
  call lm_list_append
  jmp std.algorithm.partition.partition_copy_block_18
std.algorithm.partition.partition_copy_block_15:
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r4, rcx
  movq $r16, rdx
  call lm_list_append
  jmp std.algorithm.partition.partition_copy_block_18
std.algorithm.partition.partition_copy_block_18:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  jmp std.algorithm.partition.partition_copy_block_6
std.algorithm.partition.partition_copy_block_23:
  movq $0, rax
  jmp std.algorithm.partition.partition_copy_epilogue
std.algorithm.partition.partition_copy_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.partition.partition_copy:

.globl std.algorithm.filter.filter
std.algorithm.filter.filter:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.filter.filter_entry:
std.algorithm.filter.filter_block_0:
  movq $0, rcx
  call lm_list_new
  jmp std.algorithm.filter.filter_block_4
std.algorithm.filter.filter_block_4:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.filter.filter_block_7
  jmp std.algorithm.filter.filter_block_18
std.algorithm.filter.filter_block_7:
  jmp std.algorithm.filter.filter_block_7
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r8, rcx
  call 
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.algorithm.filter.filter_block_10
  jmp std.algorithm.filter.filter_block_13
std.algorithm.filter.filter_block_10:
  jmp std.algorithm.filter.filter_block_10
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r2, rcx
  movq $r11, rdx
  call lm_list_append
  jmp std.algorithm.filter.filter_block_13
std.algorithm.filter.filter_block_13:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  jmp std.algorithm.filter.filter_block_4
std.algorithm.filter.filter_block_18:
  movq $r2, rax
  jmp std.algorithm.filter.filter_epilogue
std.algorithm.filter.filter_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.filter.filter:

.globl std.algorithm.transform.unzip
std.algorithm.transform.unzip:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
std.algorithm.transform.unzip_entry:
std.algorithm.transform.unzip_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  call lm_list_new
  jmp std.algorithm.transform.unzip_block_6
std.algorithm.transform.unzip_block_6:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r6, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.algorithm.transform.unzip_block_9
  jmp std.algorithm.transform.unzip_block_23
std.algorithm.transform.unzip_block_9:
  jmp std.algorithm.transform.unzip_block_9
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r9, rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rcx
  movq $1, rdx
  call lm_list_get
  movq $r1, rcx
  movq $r13, rdx
  call lm_list_append
  movq [rbp + -80], rcx
  movq $9, rdx
  call lm_list_get
  movq $r3, rcx
  movq $r17, rdx
  call lm_list_append
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -88]
  jmp std.algorithm.transform.unzip_block_6
std.algorithm.transform.unzip_block_23:
  movq $0, rax
  jmp std.algorithm.transform.unzip_epilogue
std.algorithm.transform.unzip_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.transform.unzip:

.globl std.algorithm.transform.__init__
std.algorithm.transform.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.algorithm.transform.__init___entry:
  movq $0, rax
  jmp std.algorithm.transform.__init___epilogue
std.algorithm.transform.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.transform.__init__:

.globl test_sort
test_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 216
test_sort_entry:
test_sort_block_0:
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $r2, rcx
  movq $41, rdx
  call lm_list_append
  movq $r2, rcx
  movq $25, rdx
  call lm_list_append
  movq $r2, rcx
  movq $65, rdx
  call lm_list_append
  movq $r2, rcx
  movq $9, rdx
  call lm_list_append
  movq $r2, rcx
  movq $33, rdx
  call lm_list_append
  movq $r2, rcx
  call std.algorithm.index.sort
  movq $r2, rcx
  movq $1, rdx
  call lm_list_get
  movq $r16, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  movq $r2, rcx
  movq $9, rdx
  call lm_list_get
  movq $r22, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq $r2, rcx
  movq $17, rdx
  call lm_list_get
  movq $r28, rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq $r2, rcx
  movq $25, rdx
  call lm_list_get
  movq $r34, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $r2, rcx
  movq $33, rdx
  call lm_list_get
  movq $r40, rax
  cmpq $65, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_69], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq $0, rcx
  call lm_list_new
  movq $r45, rcx
  movq $41, rdx
  call lm_list_append
  movq $r45, rcx
  movq $25, rdx
  call lm_list_append
  movq $r45, rcx
  movq $65, rdx
  call lm_list_append
  movq $r45, rcx
  movq $9, rdx
  call lm_list_append
  movq $r45, rcx
  movq $33, rdx
  call lm_list_append
  movq $r45, rcx
  call std.algorithm.index.quicksort_descending
  movq $r45, rcx
  movq $1, rdx
  call lm_list_get
  movq $r59, rax
  cmpq $65, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_70], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq $0, rcx
  call lm_list_new
  movq $r64, rcx
  movq $41, rdx
  call lm_list_append
  movq $r64, rcx
  movq $25, rdx
  call lm_list_append
  movq $r64, rcx
  movq $65, rdx
  call lm_list_append
  movq $r64, rcx
  movq $9, rdx
  call lm_list_append
  movq $r64, rcx
  movq $33, rdx
  call lm_list_append
  movq $r64, rcx
  call std.algorithm.index.mergesort
  movq $r64, rcx
  movq $1, rdx
  call lm_list_get
  movq $r78, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_71], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq $0, rcx
  call lm_list_new
  movq $r83, rcx
  movq $41, rdx
  call lm_list_append
  movq $r83, rcx
  movq $25, rdx
  call lm_list_append
  movq $r83, rcx
  movq $65, rdx
  call lm_list_append
  movq $r83, rcx
  movq $9, rdx
  call lm_list_append
  movq $r83, rcx
  movq $33, rdx
  call lm_list_append
  movq $r83, rcx
  call std.algorithm.index.heapsort
  movq $r83, rcx
  movq $1, rdx
  call lm_list_get
  movq $r97, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_72], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq $0, rcx
  call lm_list_new
  movq $r102, rcx
  movq $41, rdx
  call lm_list_append
  movq $r102, rcx
  movq $25, rdx
  call lm_list_append
  movq $r102, rcx
  movq $65, rdx
  call lm_list_append
  movq $r102, rcx
  movq $9, rdx
  call lm_list_append
  movq $r102, rcx
  movq $33, rdx
  call lm_list_append
  movq $r102, rcx
  call std.algorithm.index.insertion_sort
  movq $r102, rcx
  movq $1, rdx
  call lm_list_get
  movq $r116, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_73], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  movq $9, rax
  jmp test_sort_epilogue
test_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_sort:

.globl test_filter
test_filter:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 184
test_filter_entry:
test_filter_block_0:
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $r2, rcx
  movq $9, rdx
  call lm_list_append
  movq $r2, rcx
  movq $17, rdx
  call lm_list_append
  movq $r2, rcx
  movq $25, rdx
  call lm_list_append
  movq $r2, rcx
  movq $33, rdx
  call lm_list_append
  movq $r2, rcx
  movq $41, rdx
  call lm_list_append
  movq $r2, rcx
  movq $49, rdx
  call lm_list_append
  movq [rel str_const_75], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r2, rcx
  movq [rbp + -96], rdx
  call std.algorithm.index.filter
  movq $r17, rcx
  call lm_list_len
  movq $r19, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq $r17, rcx
  movq $1, rdx
  call lm_list_get
  movq $r25, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_77], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq $r17, rcx
  movq $9, rdx
  call lm_list_get
  movq $r31, rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_78], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  movq $r17, rcx
  movq $17, rdx
  call lm_list_get
  movq $r37, rax
  cmpq $49, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_79], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq [rel str_const_80], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq $r2, rcx
  movq [rbp + -168], rdx
  call std.algorithm.index.remove_if
  movq $r43, rcx
  call lm_list_len
  movq $r45, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_81], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq $r43, rcx
  movq $1, rdx
  call lm_list_get
  movq $r51, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_82], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq $9, rax
  jmp test_filter_epilogue
test_filter_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_filter:

.globl std.sort._compare
std.sort._compare:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 136
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.sort._compare_entry:
std.sort._compare_block_0:
  movq [rbp + -88], rax
  cmpq $2, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.sort._compare_block_4
  jmp std.sort._compare_block_9
std.sort._compare_block_4:
  jmp std.sort._compare_block_4
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call 
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  movq rax, [rbp + -112]
  jmp std.sort._compare_block_25
std.sort._compare_block_9:
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.sort._compare_block_11
  jmp std.sort._compare_block_15
std.sort._compare_block_11:
  jmp std.sort._compare_block_11
  movq $9, rax
  negq rax
  movq rax, [rbp + -128]
  jmp std.sort._compare_block_24
std.sort._compare_block_15:
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  setg al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne std.sort._compare_block_17
  jmp std.sort._compare_block_20
std.sort._compare_block_17:
  jmp std.sort._compare_block_17
  jmp std.sort._compare_block_23
std.sort._compare_block_20:
  jmp std.sort._compare_block_23
std.sort._compare_block_23:
  jmp std.sort._compare_block_24
std.sort._compare_block_24:
  jmp std.sort._compare_block_25
std.sort._compare_block_25:
  movq [rbp + -80], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  testq rax, rax
  jne std.sort._compare_block_28
  jmp std.sort._compare_block_31
std.sort._compare_block_28:
  jmp std.sort._compare_block_28
  movq $1, rax
  subq $1, rax
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  jmp std.sort._compare_epilogue
std.sort._compare_block_31:
  movq $1, rax
  jmp std.sort._compare_epilogue
std.sort._compare_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort._compare:

.globl std.algorithm.search.linear_search
std.algorithm.search.linear_search:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.search.linear_search_entry:
std.algorithm.search.linear_search_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.search.find
  movq $r2, rax
  jmp std.algorithm.search.linear_search_epilogue
std.algorithm.search.linear_search_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.search.linear_search:

.globl std.algorithm.unique.unique
std.algorithm.unique.unique:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 104
  mov [rbp + -64], rcx
std.algorithm.unique.unique_entry:
std.algorithm.unique.unique_block_0:
  movq $0, rcx
  call lm_list_new
  jmp std.algorithm.unique.unique_block_4
std.algorithm.unique.unique_block_4:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r4, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.algorithm.unique.unique_block_7
  jmp std.algorithm.unique.unique_block_36
std.algorithm.unique.unique_block_7:
  jmp std.algorithm.unique.unique_block_7
  jmp std.algorithm.unique.unique_block_10
std.algorithm.unique.unique_block_10:
  movq $r1, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r9, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.unique.unique_block_13
  jmp std.algorithm.unique.unique_block_25
std.algorithm.unique.unique_block_13:
  jmp std.algorithm.unique.unique_block_13
  movq $r1, rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r12, rax
  cmpq $r13, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.algorithm.unique.unique_block_17
  jmp std.algorithm.unique.unique_block_20
std.algorithm.unique.unique_block_17:
  jmp std.algorithm.unique.unique_block_17
  jmp std.algorithm.unique.unique_block_20
std.algorithm.unique.unique_block_20:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  jmp std.algorithm.unique.unique_block_10
std.algorithm.unique.unique_block_25:
  movq $18, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.algorithm.unique.unique_block_28
  jmp std.algorithm.unique.unique_block_31
std.algorithm.unique.unique_block_28:
  jmp std.algorithm.unique.unique_block_28
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r1, rcx
  movq $r23, rdx
  call lm_list_append
  jmp std.algorithm.unique.unique_block_31
std.algorithm.unique.unique_block_31:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.algorithm.unique.unique_block_4
std.algorithm.unique.unique_block_36:
  movq $r1, rax
  jmp std.algorithm.unique.unique_epilogue
std.algorithm.unique.unique_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.unique.unique:

.globl std.algorithm.index.all
std.algorithm.index.all:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.all_entry:
std.algorithm.index.all_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.search.all
  movq $r2, rax
  jmp std.algorithm.index.all_epilogue
std.algorithm.index.all_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.all:

.globl std.algorithm.shuffle.shuffle
std.algorithm.shuffle.shuffle:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 120
  mov [rbp + -64], rcx
std.algorithm.shuffle.shuffle_entry:
std.algorithm.shuffle.shuffle_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  cmpq $9, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.algorithm.shuffle.shuffle_block_5
  jmp std.algorithm.shuffle.shuffle_block_6
std.algorithm.shuffle.shuffle_block_5:
  jmp std.algorithm.shuffle.shuffle_block_5
  movq $0, rax
  jmp std.algorithm.shuffle.shuffle_epilogue
std.algorithm.shuffle.shuffle_block_6:
  movq $r1, rax
  subq $9, rax
  movq rax, $r8
  jmp std.algorithm.shuffle.shuffle_block_11
std.algorithm.shuffle.shuffle_block_11:
  movq $r8, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.shuffle.shuffle_block_14
  jmp std.algorithm.shuffle.shuffle_block_45
std.algorithm.shuffle.shuffle_block_14:
  jmp std.algorithm.shuffle.shuffle_block_14
  movq $987654313, rax
  imulq $8828121961, rax
  movq rax, [rbp + -88]
  movq $987654313, rax
  imulq $8828121961, rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  addq $98761, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  cqto
  movq $17179869185, rcx
  idivq rcx
  movq rdx, [rbp + -112]
  movq [rbp + -112], rax
  cmpq $1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.algorithm.shuffle.shuffle_block_28
  jmp std.algorithm.shuffle.shuffle_block_31
std.algorithm.shuffle.shuffle_block_28:
  jmp std.algorithm.shuffle.shuffle_block_28
  movq [rbp + -112], rax
  negq rax
  movq rax, [rbp + -128]
  jmp std.algorithm.shuffle.shuffle_block_31
std.algorithm.shuffle.shuffle_block_31:
  movq $r8, rax
  addq $9, rax
  movq rax, $r29
  movq [rbp + -128], rax
  cqto
  movq $r29, rcx
  idivq rcx
  movq rdx, [rbp + -136]
  movq [rbp + -64], rcx
  movq $r8, rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq [rbp + -136], rdx
  call lm_list_get
  movq $r8, rax
  subq $9, rax
  movq rax, $r38
  jmp std.algorithm.shuffle.shuffle_block_11
std.algorithm.shuffle.shuffle_block_45:
  movq $0, rax
  jmp std.algorithm.shuffle.shuffle_epilogue
std.algorithm.shuffle.shuffle_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.shuffle.shuffle:

.globl std.algorithm.sort.sort
std.algorithm.sort.sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.sort.sort_entry:
std.algorithm.sort.sort_block_0:
  movq [rbp + -64], rcx
  movq $10, rdx
  movq $2, r8
  call std.sort.sort
  movq $0, rax
  jmp std.algorithm.sort.sort_epilogue
std.algorithm.sort.sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.sort.sort:

.globl std.algorithm.sort.quicksort
std.algorithm.sort.quicksort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.sort.quicksort_entry:
std.algorithm.sort.quicksort_block_0:
  movq [rbp + -64], rcx
  movq $10, rdx
  movq $2, r8
  call std.sort.quicksort
  movq $0, rax
  jmp std.algorithm.sort.quicksort_epilogue
std.algorithm.sort.quicksort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.sort.quicksort:

.globl std.sort.counting_sort
std.sort.counting_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 168
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.sort.counting_sort_entry:
std.sort.counting_sort_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r2, rax
  cmpq $9, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.sort.counting_sort_block_5
  jmp std.sort.counting_sort_block_6
std.sort.counting_sort_block_5:
  jmp std.sort.counting_sort_block_5
  movq $0, rax
  jmp std.sort.counting_sort_epilogue
std.sort.counting_sort_block_6:
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  jmp std.sort.counting_sort_block_14
std.sort.counting_sort_block_14:
  movq $9, rax
  cmpq $r2, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.sort.counting_sort_block_16
  jmp std.sort.counting_sort_block_33
std.sort.counting_sort_block_16:
  jmp std.sort.counting_sort_block_16
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  movq $r16, rax
  cmpq $r8, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.sort.counting_sort_block_19
  jmp std.sort.counting_sort_block_22
std.sort.counting_sort_block_19:
  jmp std.sort.counting_sort_block_19
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  jmp std.sort.counting_sort_block_22
std.sort.counting_sort_block_22:
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  movq $r20, rax
  cmpq $r11, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.sort.counting_sort_block_25
  jmp std.sort.counting_sort_block_28
std.sort.counting_sort_block_25:
  jmp std.sort.counting_sort_block_25
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  jmp std.sort.counting_sort_block_28
std.sort.counting_sort_block_28:
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.sort.counting_sort_block_14
std.sort.counting_sort_block_33:
  movq $0, rcx
  call lm_list_new
  jmp std.sort.counting_sort_block_38
std.sort.counting_sort_block_38:
  movq $r23, rax
  subq $r19, rax
  movq rax, $r30
  movq $1, rax
  cmpq $r30, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.sort.counting_sort_block_41
  jmp std.sort.counting_sort_block_48
std.sort.counting_sort_block_41:
  jmp std.sort.counting_sort_block_41
  movq $r27, rcx
  movq $1, rdx
  call lm_list_append
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -128]
  jmp std.sort.counting_sort_block_38
std.sort.counting_sort_block_48:
  jmp std.sort.counting_sort_block_51
std.sort.counting_sort_block_51:
  movq $1, rax
  cmpq $r2, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne std.sort.counting_sort_block_53
  jmp std.sort.counting_sort_block_70
std.sort.counting_sort_block_53:
  jmp std.sort.counting_sort_block_53
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r42, rax
  subq $r19, rax
  movq rax, $r43
  movq $r27, rcx
  movq $r43, rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r46, rax
  subq $r19, rax
  movq rax, $r47
  movq $r27, rcx
  movq $r47, rdx
  call lm_list_get
  movq $r48, rax
  addq $9, rax
  movq rax, $r50
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r51, rax
  subq $r19, rax
  movq rax, $r52
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.sort.counting_sort_block_51
std.sort.counting_sort_block_70:
  jmp std.sort.counting_sort_block_73
std.sort.counting_sort_block_73:
  movq $0, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r59, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne std.sort.counting_sort_block_76
  jmp std.sort.counting_sort_block_104
std.sort.counting_sort_block_76:
  jmp std.sort.counting_sort_block_76
  jmp std.sort.counting_sort_block_77
std.sort.counting_sort_block_77:
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq $r62, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  testq rax, rax
  jne std.sort.counting_sort_block_81
  jmp std.sort.counting_sort_block_99
std.sort.counting_sort_block_81:
  jmp std.sort.counting_sort_block_81
  movq [rbp + -72], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  testq rax, rax
  jne std.sort.counting_sort_block_84
  jmp std.sort.counting_sort_block_87
std.sort.counting_sort_block_84:
  jmp std.sort.counting_sort_block_84
  movq $r23, rax
  subq $1, rax
  movq rax, $r69
  jmp std.sort.counting_sort_block_90
std.sort.counting_sort_block_87:
  movq $r19, rax
  addq $1, rax
  movq rax, $r71
  jmp std.sort.counting_sort_block_90
std.sort.counting_sort_block_90:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -176]
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq $r76, rax
  subq $9, rax
  movq rax, $r78
  jmp std.sort.counting_sort_block_77
std.sort.counting_sort_block_99:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -184]
  jmp std.sort.counting_sort_block_73
std.sort.counting_sort_block_104:
  movq $0, rax
  jmp std.sort.counting_sort_epilogue
std.sort.counting_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort.counting_sort:

.globl std.algorithm.sort.heapsort
std.algorithm.sort.heapsort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.sort.heapsort_entry:
std.algorithm.sort.heapsort_block_0:
  movq [rbp + -64], rcx
  movq $10, rdx
  movq $2, r8
  call std.sort.heapsort
  movq $0, rax
  jmp std.algorithm.sort.heapsort_epilogue
std.algorithm.sort.heapsort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.sort.heapsort:

.globl std.algorithm.sort.insertion_sort
std.algorithm.sort.insertion_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.sort.insertion_sort_entry:
std.algorithm.sort.insertion_sort_block_0:
  movq [rbp + -64], rcx
  movq $10, rdx
  movq $2, r8
  call std.sort.insertion_sort
  movq $0, rax
  jmp std.algorithm.sort.insertion_sort_epilogue
std.algorithm.sort.insertion_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.sort.insertion_sort:

.globl std.algorithm.sort.radix_sort
std.algorithm.sort.radix_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.sort.radix_sort_entry:
std.algorithm.sort.radix_sort_block_0:
  movq [rbp + -64], rcx
  movq $10, rdx
  call std.sort.radix_sort
  movq $0, rax
  jmp std.algorithm.sort.radix_sort_epilogue
std.algorithm.sort.radix_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.sort.radix_sort:

.globl std.algorithm.sort.timsort
std.algorithm.sort.timsort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.sort.timsort_entry:
std.algorithm.sort.timsort_block_0:
  movq [rbp + -64], rcx
  movq $10, rdx
  movq $2, r8
  call std.sort.timsort
  movq $0, rax
  jmp std.algorithm.sort.timsort_epilogue
std.algorithm.sort.timsort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.sort.timsort:

.globl std.algorithm.reduce.reduce
std.algorithm.reduce.reduce:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.algorithm.reduce.reduce_entry:
std.algorithm.reduce.reduce_block_0:
  jmp std.algorithm.reduce.reduce_block_3
std.algorithm.reduce.reduce_block_3:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.algorithm.reduce.reduce_block_6
  jmp std.algorithm.reduce.reduce_block_14
std.algorithm.reduce.reduce_block_6:
  jmp std.algorithm.reduce.reduce_block_6
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -80], rcx
  movq $r8, rdx
  call 
  movq rax, [rbp + -96]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.algorithm.reduce.reduce_block_3
std.algorithm.reduce.reduce_block_14:
  movq [rbp + -96], rax
  jmp std.algorithm.reduce.reduce_epilogue
std.algorithm.reduce.reduce_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.reduce.reduce:

.globl std.algorithm.reduce.fold
std.algorithm.reduce.fold:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.algorithm.reduce.fold_entry:
std.algorithm.reduce.fold_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -80], rdx
  movq [rbp + -72], r8
  call std.algorithm.reduce.reduce
  movq $r3, rax
  jmp std.algorithm.reduce.fold_epilogue
std.algorithm.reduce.fold_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.reduce.fold:

.globl std.algorithm.binary_search.equal_range
std.algorithm.binary_search.equal_range:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.binary_search.equal_range_entry:
std.algorithm.binary_search.equal_range_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.binary_search.lower_bound
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.binary_search.upper_bound
  movq $0, rax
  jmp std.algorithm.binary_search.equal_range_epilogue
std.algorithm.binary_search.equal_range_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.binary_search.equal_range:

.globl std.algorithm.reduce.__init__
std.algorithm.reduce.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.algorithm.reduce.__init___entry:
  movq $0, rax
  jmp std.algorithm.reduce.__init___epilogue
std.algorithm.reduce.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.reduce.__init__:

.globl std.algorithm.transform.map
std.algorithm.transform.map:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.transform.map_entry:
std.algorithm.transform.map_block_0:
  movq $0, rcx
  call lm_list_new
  jmp std.algorithm.transform.map_block_4
std.algorithm.transform.map_block_4:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.transform.map_block_7
  jmp std.algorithm.transform.map_block_15
std.algorithm.transform.map_block_7:
  jmp std.algorithm.transform.map_block_7
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r8, rcx
  call 
  movq rax, [rbp + -88]
  movq $r2, rcx
  movq [rbp + -88], rdx
  call lm_list_append
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  jmp std.algorithm.transform.map_block_4
std.algorithm.transform.map_block_15:
  movq $r2, rax
  jmp std.algorithm.transform.map_epilogue
std.algorithm.transform.map_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.transform.map:

.globl std.search.__init__
std.search.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.search.__init___entry:
  movq $0, rax
  jmp std.search.__init___epilogue
std.search.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.search.__init__:

.globl std.algorithm.partition.is_partitioned
std.algorithm.partition.is_partitioned:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.partition.is_partitioned_entry:
std.algorithm.partition.is_partitioned_block_0:
  jmp std.algorithm.partition.is_partitioned_block_3
std.algorithm.partition.is_partitioned_block_3:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r4, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.partition.is_partitioned_block_6
  jmp std.algorithm.partition.is_partitioned_block_21
std.algorithm.partition.is_partitioned_block_6:
  jmp std.algorithm.partition.is_partitioned_block_6
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r7, rcx
  call 
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.algorithm.partition.is_partitioned_block_9
  jmp std.algorithm.partition.is_partitioned_block_13
std.algorithm.partition.is_partitioned_block_9:
  jmp std.algorithm.partition.is_partitioned_block_9
  movq $10, rax
  testq rax, rax
  jne std.algorithm.partition.is_partitioned_block_10
  jmp std.algorithm.partition.is_partitioned_block_12
std.algorithm.partition.is_partitioned_block_10:
  jmp std.algorithm.partition.is_partitioned_block_10
  movq $10, rax
  jmp std.algorithm.partition.is_partitioned_epilogue
std.algorithm.partition.is_partitioned_block_12:
  jmp std.algorithm.partition.is_partitioned_block_16
std.algorithm.partition.is_partitioned_block_13:
  jmp std.algorithm.partition.is_partitioned_block_16
std.algorithm.partition.is_partitioned_block_16:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  jmp std.algorithm.partition.is_partitioned_block_3
std.algorithm.partition.is_partitioned_block_21:
  movq $18, rax
  jmp std.algorithm.partition.is_partitioned_epilogue
std.algorithm.partition.is_partitioned_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.partition.is_partitioned:

.globl std.algorithm.partition.__init__
std.algorithm.partition.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.algorithm.partition.__init___entry:
  movq $0, rax
  jmp std.algorithm.partition.__init___epilogue
std.algorithm.partition.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.partition.__init__:

.globl std.algorithm.transform.zip
std.algorithm.transform.zip:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.transform.zip_entry:
std.algorithm.transform.zip_block_0:
  movq $0, rcx
  call lm_list_new
  movq [rbp + -64], rcx
  call lm_list_len
  movq [rbp + -72], rcx
  call lm_list_len
  movq $r7, rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.transform.zip_block_8
  jmp std.algorithm.transform.zip_block_11
std.algorithm.transform.zip_block_8:
  jmp std.algorithm.transform.zip_block_8
  movq [rbp + -72], rcx
  call lm_list_len
  jmp std.algorithm.transform.zip_block_11
std.algorithm.transform.zip_block_11:
  jmp std.algorithm.transform.zip_block_12
std.algorithm.transform.zip_block_12:
  movq $1, rax
  cmpq $r10, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.algorithm.transform.zip_block_14
  jmp std.algorithm.transform.zip_block_27
std.algorithm.transform.zip_block_14:
  jmp std.algorithm.transform.zip_block_14
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -72], rcx
  movq $1, rdx
  call lm_list_get
  movq $r2, rcx
  movq $0, rdx
  call lm_list_append
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  jmp std.algorithm.transform.zip_block_12
std.algorithm.transform.zip_block_27:
  movq $r2, rax
  jmp std.algorithm.transform.zip_epilogue
std.algorithm.transform.zip_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.transform.zip:

.globl std.algorithm.index.any_match
std.algorithm.index.any_match:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.any_match_entry:
std.algorithm.index.any_match_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.search.any_match
  movq $r2, rax
  jmp std.algorithm.index.any_match_epilogue
std.algorithm.index.any_match_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.any_match:

.globl std.algorithm.index.find
std.algorithm.index.find:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.find_entry:
std.algorithm.index.find_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.search.find
  movq $r2, rax
  jmp std.algorithm.index.find_epilogue
std.algorithm.index.find_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.find:

.globl std.algorithm.index.quicksort
std.algorithm.index.quicksort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.index.quicksort_entry:
std.algorithm.index.quicksort_block_0:
  movq [rbp + -64], rcx
  call std.algorithm.sort.quicksort
  movq $0, rax
  jmp std.algorithm.index.quicksort_epilogue
std.algorithm.index.quicksort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.quicksort:

.globl std.algorithm.index.insertion_sort
std.algorithm.index.insertion_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.index.insertion_sort_entry:
std.algorithm.index.insertion_sort_block_0:
  movq [rbp + -64], rcx
  call std.algorithm.sort.insertion_sort
  movq $0, rax
  jmp std.algorithm.index.insertion_sort_epilogue
std.algorithm.index.insertion_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.insertion_sort:

.globl std.algorithm.index.quicksort_descending
std.algorithm.index.quicksort_descending:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.index.quicksort_descending_entry:
std.algorithm.index.quicksort_descending_block_0:
  movq [rbp + -64], rcx
  call std.algorithm.sort.quicksort_descending
  movq $0, rax
  jmp std.algorithm.index.quicksort_descending_epilogue
std.algorithm.index.quicksort_descending_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.quicksort_descending:

.globl std.algorithm.search.any_match
std.algorithm.search.any_match:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.search.any_match_entry:
std.algorithm.search.any_match_block_0:
  jmp std.algorithm.search.any_match_block_2
std.algorithm.search.any_match_block_2:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.search.any_match_block_5
  jmp std.algorithm.search.any_match_block_15
std.algorithm.search.any_match_block_5:
  jmp std.algorithm.search.any_match_block_5
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r6, rcx
  call 
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.algorithm.search.any_match_block_8
  jmp std.algorithm.search.any_match_block_10
std.algorithm.search.any_match_block_8:
  jmp std.algorithm.search.any_match_block_8
  movq $18, rax
  jmp std.algorithm.search.any_match_epilogue
std.algorithm.search.any_match_block_10:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  jmp std.algorithm.search.any_match_block_2
std.algorithm.search.any_match_block_15:
  movq $10, rax
  jmp std.algorithm.search.any_match_epilogue
std.algorithm.search.any_match_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.search.any_match:

.globl std.algorithm.index.mergesort
std.algorithm.index.mergesort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.index.mergesort_entry:
std.algorithm.index.mergesort_block_0:
  movq [rbp + -64], rcx
  call std.algorithm.sort.mergesort
  movq $0, rax
  jmp std.algorithm.index.mergesort_epilogue
std.algorithm.index.mergesort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.mergesort:

.globl std.sort._partition
std.sort._partition:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 136
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.sort._partition_entry:
std.sort._partition_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -80], rdx
  call lm_list_get
  movq [rbp + -72], rax
  subq $9, rax
  movq rax, [rbp + -104]
  jmp std.sort._partition_block_7
std.sort._partition_block_7:
  movq [rbp + -72], rax
  cmpq [rbp + -80], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.sort._partition_block_9
  jmp std.sort._partition_block_25
std.sort._partition_block_9:
  jmp std.sort._partition_block_9
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call lm_list_get
  movq $r13, rcx
  movq $r5, rdx
  movq [rbp + -88], r8
  movq [rbp + -96], r9
  call std.sort._compare
  movq $r14, rax
  cmpq $1, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.sort._partition_block_14
  jmp std.sort._partition_block_20
std.sort._partition_block_14:
  jmp std.sort._partition_block_14
  movq [rbp + -104], rax
  addq $9, rax
  movq rax, [rbp + -128]
  movq [rbp + -64], rcx
  movq [rbp + -128], rdx
  movq [rbp + -72], r8
  call std.sort._swap
  jmp std.sort._partition_block_20
std.sort._partition_block_20:
  movq [rbp + -72], rax
  addq $9, rax
  movq rax, [rbp + -136]
  jmp std.sort._partition_block_7
std.sort._partition_block_25:
  movq [rbp + -128], rax
  addq $9, rax
  movq rax, [rbp + -144]
  movq [rbp + -64], rcx
  movq [rbp + -144], rdx
  movq [rbp + -80], r8
  call std.sort._swap
  movq [rbp + -128], rax
  addq $9, rax
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  jmp std.sort._partition_epilogue
std.sort._partition_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort._partition:

.globl test_partition
test_partition:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 152
test_partition_entry:
test_partition_block_0:
  movq [rel str_const_83], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $r2, rcx
  movq $9, rdx
  call lm_list_append
  movq $r2, rcx
  movq $17, rdx
  call lm_list_append
  movq $r2, rcx
  movq $25, rdx
  call lm_list_append
  movq $r2, rcx
  movq $33, rdx
  call lm_list_append
  movq $r2, rcx
  movq $41, rdx
  call lm_list_append
  movq $r2, rcx
  movq $49, rdx
  call lm_list_append
  movq [rel str_const_84], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r2, rcx
  movq [rbp + -96], rdx
  call std.algorithm.index.partition
  jmp test_partition_block_21
test_partition_block_21:
  movq $1, rax
  cmpq $r17, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne test_partition_block_23
  jmp test_partition_block_34
test_partition_block_23:
  jmp test_partition_block_23
  movq $r2, rcx
  movq $1, rdx
  call lm_list_get
  movq $r22, rcx
  call is_even
  movq $r23, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_85], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -128]
  jmp test_partition_block_21
test_partition_block_34:
  jmp test_partition_block_35
test_partition_block_35:
  movq $r2, rcx
  call lm_list_len
  movq [rbp + -128], rax
  cmpq $r31, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne test_partition_block_38
  jmp test_partition_block_49
test_partition_block_38:
  jmp test_partition_block_38
  movq $r2, rcx
  movq [rbp + -128], rdx
  call lm_list_get
  movq $r34, rcx
  call is_even
  movq $r35, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_86], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rbp + -128], rax
  addq $9, rax
  movq rax, [rbp + -160]
  jmp test_partition_block_35
test_partition_block_49:
  movq $9, rax
  jmp test_partition_epilogue
test_partition_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_partition:

.globl std.algorithm.index.heapsort
std.algorithm.index.heapsort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.index.heapsort_entry:
std.algorithm.index.heapsort_block_0:
  movq [rbp + -64], rcx
  call std.algorithm.sort.heapsort
  movq $0, rax
  jmp std.algorithm.index.heapsort_epilogue
std.algorithm.index.heapsort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.heapsort:

.globl std.algorithm.index.counting_sort
std.algorithm.index.counting_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.index.counting_sort_entry:
std.algorithm.index.counting_sort_block_0:
  movq [rbp + -64], rcx
  call std.algorithm.sort.counting_sort
  movq $0, rax
  jmp std.algorithm.index.counting_sort_epilogue
std.algorithm.index.counting_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.counting_sort:

.globl std.algorithm.index.timsort
std.algorithm.index.timsort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.index.timsort_entry:
std.algorithm.index.timsort_block_0:
  movq [rbp + -64], rcx
  call std.algorithm.sort.timsort
  movq $0, rax
  jmp std.algorithm.index.timsort_epilogue
std.algorithm.index.timsort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.timsort:

.globl std.sort._swap
std.sort._swap:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.sort._swap_entry:
std.sort._swap_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq [rbp + -80], rdx
  call lm_list_get
  movq $0, rax
  jmp std.sort._swap_epilogue
std.sort._swap_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort._swap:

.globl std.algorithm.sort.__init__
std.algorithm.sort.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.algorithm.sort.__init___entry:
  movq $0, rax
  jmp std.algorithm.sort.__init___epilogue
std.algorithm.sort.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.sort.__init__:

.globl std.algorithm.index.stable_sort
std.algorithm.index.stable_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.index.stable_sort_entry:
std.algorithm.index.stable_sort_block_0:
  movq [rbp + -64], rcx
  call std.algorithm.sort.stable_sort
  movq $0, rax
  jmp std.algorithm.index.stable_sort_epilogue
std.algorithm.index.stable_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.stable_sort:

.globl std.algorithm.index.partial_sort
std.algorithm.index.partial_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.partial_sort_entry:
std.algorithm.index.partial_sort_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.sort.partial_sort
  movq $0, rax
  jmp std.algorithm.index.partial_sort_epilogue
std.algorithm.index.partial_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.partial_sort:

.globl std.algorithm.index.is_partitioned
std.algorithm.index.is_partitioned:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.is_partitioned_entry:
std.algorithm.index.is_partitioned_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.partition.is_partitioned
  movq $r2, rax
  jmp std.algorithm.index.is_partitioned_epilogue
std.algorithm.index.is_partitioned_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.is_partitioned:

.globl std.algorithm.index.partition
std.algorithm.index.partition:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.partition_entry:
std.algorithm.index.partition_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.partition.partition
  movq $r2, rax
  jmp std.algorithm.index.partition_epilogue
std.algorithm.index.partition_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.partition:

.globl std.algorithm.index.map
std.algorithm.index.map:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.map_entry:
std.algorithm.index.map_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.transform.map
  movq $r2, rax
  jmp std.algorithm.index.map_epilogue
std.algorithm.index.map_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.map:

.globl std.algorithm.binary_search.upper_bound
std.algorithm.binary_search.upper_bound:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 104
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.binary_search.upper_bound_entry:
std.algorithm.binary_search.upper_bound_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.algorithm.binary_search.upper_bound_block_4
std.algorithm.binary_search.upper_bound_block_4:
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.algorithm.binary_search.upper_bound_block_6
  jmp std.algorithm.binary_search.upper_bound_block_21
std.algorithm.binary_search.upper_bound_block_6:
  jmp std.algorithm.binary_search.upper_bound_block_6
  movq $1, rax
  addq $r3, rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call lm_list_get
  movq $r11, rax
  cmpq [rbp + -72], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.algorithm.binary_search.upper_bound_block_13
  jmp std.algorithm.binary_search.upper_bound_block_18
std.algorithm.binary_search.upper_bound_block_13:
  jmp std.algorithm.binary_search.upper_bound_block_13
  movq [rbp + -96], rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.algorithm.binary_search.upper_bound_block_20
std.algorithm.binary_search.upper_bound_block_18:
  jmp std.algorithm.binary_search.upper_bound_block_20
std.algorithm.binary_search.upper_bound_block_20:
  jmp std.algorithm.binary_search.upper_bound_block_4
std.algorithm.binary_search.upper_bound_block_21:
  movq [rbp + -112], rax
  jmp std.algorithm.binary_search.upper_bound_epilogue
std.algorithm.binary_search.upper_bound_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.binary_search.upper_bound:

.globl std.algorithm.index.zip
std.algorithm.index.zip:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.zip_entry:
std.algorithm.index.zip_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.transform.zip
  movq $r2, rax
  jmp std.algorithm.index.zip_epilogue
std.algorithm.index.zip_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.zip:

.globl std.algorithm.index.fold
std.algorithm.index.fold:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.algorithm.index.fold_entry:
std.algorithm.index.fold_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.algorithm.reduce.fold
  movq $r3, rax
  jmp std.algorithm.index.fold_epilogue
std.algorithm.index.fold_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.fold:

.globl is_even
is_even:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
is_even_entry:
is_even_block_0:
  movq [rbp + -64], rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rdx, [rbp + -80]
  movq [rbp + -80], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp is_even_epilogue
is_even_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_is_even:

.globl std.algorithm.index.filter
std.algorithm.index.filter:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.filter_entry:
std.algorithm.index.filter_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.filter.filter
  movq $r2, rax
  jmp std.algorithm.index.filter_epilogue
std.algorithm.index.filter_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.filter:

.globl std.sort.timsort
std.sort.timsort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.sort.timsort_entry:
std.sort.timsort_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.sort.stable_sort
  movq $0, rax
  jmp std.sort.timsort_epilogue
std.sort.timsort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort.timsort:

.globl std.algorithm.index.__init__
std.algorithm.index.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.algorithm.index.__init___entry:
  movq $0, rax
  jmp std.algorithm.index.__init___epilogue
std.algorithm.index.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.__init__:

.globl std.algorithm.index.remove_if
std.algorithm.index.remove_if:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.remove_if_entry:
std.algorithm.index.remove_if_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.filter.remove_if
  movq $r2, rax
  jmp std.algorithm.index.remove_if_epilogue
std.algorithm.index.remove_if_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.remove_if:

.globl std.algorithm.index.unique
std.algorithm.index.unique:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.index.unique_entry:
std.algorithm.index.unique_block_0:
  movq [rbp + -64], rcx
  call std.algorithm.unique.unique
  movq $r1, rax
  jmp std.algorithm.index.unique_epilogue
std.algorithm.index.unique_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.unique:

.globl std.sort.radix_sort
std.sort.radix_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.sort.radix_sort_entry:
std.sort.radix_sort_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.sort.counting_sort
  movq $0, rax
  jmp std.sort.radix_sort_epilogue
std.sort.radix_sort_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.sort.radix_sort:

.globl std.algorithm.index.shuffle
std.algorithm.index.shuffle:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.algorithm.index.shuffle_entry:
std.algorithm.index.shuffle_block_0:
  movq [rbp + -64], rcx
  call std.algorithm.shuffle.shuffle
  movq $0, rax
  jmp std.algorithm.index.shuffle_epilogue
std.algorithm.index.shuffle_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.shuffle:

.globl std.algorithm.index.linear_search
std.algorithm.index.linear_search:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.linear_search_entry:
std.algorithm.index.linear_search_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.search.linear_search
  movq $r2, rax
  jmp std.algorithm.index.linear_search_epilogue
std.algorithm.index.linear_search_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.linear_search:

.globl std.algorithm.shuffle.__init__
std.algorithm.shuffle.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.algorithm.shuffle.__init___entry:
  movq $0, rax
  jmp std.algorithm.shuffle.__init___epilogue
std.algorithm.shuffle.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.shuffle.__init__:

.globl std.algorithm.index.binary_search
std.algorithm.index.binary_search:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.binary_search_entry:
std.algorithm.index.binary_search_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.binary_search.binary_search
  movq $r2, rax
  jmp std.algorithm.index.binary_search_epilogue
std.algorithm.index.binary_search_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.binary_search:

.globl std.algorithm.index.equal_range
std.algorithm.index.equal_range:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.algorithm.index.equal_range_entry:
std.algorithm.index.equal_range_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.algorithm.binary_search.equal_range
  movq $r2, rax
  jmp std.algorithm.index.equal_range_epilogue
std.algorithm.index.equal_range_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.algorithm.index.equal_range:

.globl lm_box_string
lm_box_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
lm_box_string_entry:
  # Bump Allocation: 24 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 24
  mov [rel heap_ptr], rax
  movq $2, rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  addq $8, rax
  movq rax, [rbp + -80]
  movq $3, rax
  movq [rbp + -80], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  addq $16, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  jmp lm_box_string_epilogue
lm_box_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_lm_box_string:

.globl lm_print_str
lm_print_str:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 136
  mov [rbp + -64], rcx
lm_print_str_entry:
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 8
  mov [rel heap_ptr], rax
  movq $0, rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  jmp lm_print_str_loop
lm_print_str_loop:
  movq [rbp + -72], rax
  mov rax, [rax]
  movq rax, [rbp + -80]
  movq [rbp + -64], rax
  addq [rbp + -80], rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  cmpq $0, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -80], rax
  addq $1, rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  movq [rbp + -104], rax
  testq rax, rax
  jne lm_print_str_done
  jmp lm_print_str_loop
lm_print_str_done:
  movq [rbp + -72], rax
  mov rax, [rax]
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  subq $1, rax
  movq rax, [rbp + -128]
  subq $32, %rsp
  movq $1, rcx
  movq [rbp + -64], rdx
  movq [rbp + -128], r8
  call _write
  addq $32, %rsp
  subq $32, %rsp
  movq $1, rcx
  movq [rel nl], rdx
  movq $1, r8
  call _write
  addq $32, %rsp
  movq $0, rax
  jmp lm_print_str_epilogue
lm_print_str_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_lm_print_str:

.globl lm_assert
lm_assert:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
lm_assert_entry:
  movq [rbp + -64], rax
  testq rax, rax
  jne lm_assert_pass
  jmp lm_assert_fail
lm_assert_fail:
  subq $32, %rsp
  movq $1, rcx
  movq [rel assert_fail], rdx
  movq $17, r8
  call _write
  addq $32, %rsp
  movq $50397203, rax
  movq rax, [rbp + -88]
  movq $0, rax
  jmp lm_assert_epilogue
lm_assert_pass:
  movq $0, rax
  jmp lm_assert_epilogue
lm_assert_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_lm_assert:

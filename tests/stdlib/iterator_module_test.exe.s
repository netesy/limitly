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
  .string "Testing Iterator Basics..."
.align 8
str_const_1:
  .string "next failed"
.align 8
str_const_2:
  .string "next failed"
.align 8
str_const_3:
  .string "next failed"
.align 8
str_const_4:
  .string "next past end failed"
.align 8
str_const_5:
  .string "collect length failed"
.align 8
str_const_6:
  .string "collect element 0 failed"
.align 8
str_const_7:
  .string "=== Iterator Module Test Suite ==="
.align 8
str_const_8:
  .string "basics failed"
.align 8
str_const_9:
  .string "map failed"
.align 8
str_const_10:
  .string "filter failed"
.align 8
str_const_11:
  .string "take failed"
.align 8
str_const_12:
  .string "skip failed"
.align 8
str_const_13:
  .string "zip failed"
.align 8
str_const_14:
  .string "chain failed"
.align 8
str_const_15:
  .string "enumerate failed"
.align 8
str_const_16:
  .string "All iterator tests passed successfully."
.align 8
str_const_17:
  .string "Testing Chain Iterator..."
.align 8
str_const_18:
  .string "chain 1 failed"
.align 8
str_const_19:
  .string "chain 2 failed"
.align 8
str_const_20:
  .string "chain 3 failed"
.align 8
str_const_21:
  .string "chain 4 failed"
.align 8
str_const_22:
  .string "chain past end failed"
.align 8
str_const_23:
  .string "Testing Enumerate Iterator..."
.align 8
str_const_24:
  .string "a"
.align 8
str_const_25:
  .string "b"
.align 8
str_const_26:
  .string "enumerate 1 index failed"
.align 8
str_const_27:
  .string "a"
.align 8
str_const_28:
  .string "enumerate 1 val failed"
.align 8
str_const_29:
  .string "enumerate 2 index failed"
.align 8
str_const_30:
  .string "b"
.align 8
str_const_31:
  .string "enumerate 2 val failed"
.align 8
str_const_32:
  .string "enumerate past end failed"
.align 8
str_const_33:
  .string "Testing Zip Iterator..."
.align 8
str_const_34:
  .string "a"
.align 8
str_const_35:
  .string "b"
.align 8
str_const_36:
  .string "zip pair 1 left failed"
.align 8
str_const_37:
  .string "a"
.align 8
str_const_38:
  .string "zip pair 1 right failed"
.align 8
str_const_39:
  .string "zip pair 2 left failed"
.align 8
str_const_40:
  .string "b"
.align 8
str_const_41:
  .string "zip pair 2 right failed"
.align 8
str_const_42:
  .string "zip past end failed"
.align 8
str_const_43:
  .string "Testing Take Iterator..."
.align 8
str_const_44:
  .string "take 1 failed"
.align 8
str_const_45:
  .string "take 2 failed"
.align 8
str_const_46:
  .string "take 3 failed"
.align 8
str_const_47:
  .string "take past limit failed"
.align 8
str_const_48:
  .string "Testing Filter Iterator..."
.align 8
str_const_49:
  .string "is_odd"
.align 8
str_const_50:
  .string "filter 1 failed"
.align 8
str_const_51:
  .string "filter 3 failed"
.align 8
str_const_52:
  .string "filter 5 failed"
.align 8
str_const_53:
  .string "filter past end failed"
.align 8
str_const_54:
  .string "Testing Skip Iterator..."
.align 8
str_const_55:
  .string "skip 1 failed"
.align 8
str_const_56:
  .string "skip 2 failed"
.align 8
str_const_57:
  .string "skip 3 failed"
.align 8
str_const_58:
  .string "skip past end failed"
.align 8
str_const_59:
  .string "Testing Map Iterator..."
.align 8
str_const_60:
  .string "square"
.align 8
str_const_61:
  .string "map 1 failed"
.align 8
str_const_62:
  .string "map 2 failed"
.align 8
str_const_63:
  .string "map 3 failed"
.align 8
str_const_64:
  .string "map past end failed"
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
  sub rsp, 232
main_entry:
main_block_0:
  call std.iterator.index.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq [rel str_const_7], rcx
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
  call test_iterator_basics
  movq $r2, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_map
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  call test_filter
  movq $r12, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  call test_take
  movq $r17, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  call test_skip
  movq $r22, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  call test_zip
  movq $r27, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  call test_chain
  movq $r32, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  call test_enumerate
  movq $r37, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  addq $16, rax
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  mov rax, [rax]
  movq rax, [rbp + -248]
  movq [rbp + -248], rcx
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

.globl std.iterator.index.__init__
std.iterator.index.__init__:
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
std.iterator.index.__init___entry:
  movq $0, rax
  jmp std.iterator.index.__init___epilogue
std.iterator.index.__init___epilogue:
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
.Lfunc_end_std.iterator.index.__init__:

.globl std.iterator.index.take
std.iterator.index.take:
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
std.iterator.index.take_entry:
std.iterator.index.take_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.iterator.take.take
  movq $r2, rax
  jmp std.iterator.index.take_epilogue
std.iterator.index.take_epilogue:
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
.Lfunc_end_std.iterator.index.take:

.globl std.iterator.index.filter
std.iterator.index.filter:
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
std.iterator.index.filter_entry:
std.iterator.index.filter_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.iterator.filter.filter
  movq $r2, rax
  jmp std.iterator.index.filter_epilogue
std.iterator.index.filter_epilogue:
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
.Lfunc_end_std.iterator.index.filter:

.globl std.iterator.index.map
std.iterator.index.map:
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
std.iterator.index.map_entry:
std.iterator.index.map_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.iterator.map.map
  movq $r2, rax
  jmp std.iterator.index.map_epilogue
std.iterator.index.map_epilogue:
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
.Lfunc_end_std.iterator.index.map:

.globl std.iterator.index.collect
std.iterator.index.collect:
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
std.iterator.index.collect_entry:
std.iterator.index.collect_block_0:
  movq [rbp + -64], rcx
  call std.iterator.iterator.collect
  movq $r1, rax
  jmp std.iterator.index.collect_epilogue
std.iterator.index.collect_epilogue:
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
.Lfunc_end_std.iterator.index.collect:

.globl std.iterator.iterable.__init__
std.iterator.iterable.__init__:
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
std.iterator.iterable.__init___entry:
  movq $0, rax
  jmp std.iterator.iterable.__init___epilogue
std.iterator.iterable.__init___epilogue:
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
.Lfunc_end_std.iterator.iterable.__init__:

.globl std.iterator.map.map
std.iterator.map.map:
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
std.iterator.map.map_entry:
std.iterator.map.map_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.iterator.map.MapIterator.init
  movq [rbp + -80], rax
  jmp std.iterator.map.map_epilogue
std.iterator.map.map_epilogue:
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
.Lfunc_end_std.iterator.map.map:

.globl std.iterator.map.MapIterator.init
std.iterator.map.MapIterator.init:
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
std.iterator.map.MapIterator.init_entry:
  movq $0, rax
  jmp std.iterator.map.MapIterator.init_epilogue
std.iterator.map.MapIterator.init_epilogue:
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
.Lfunc_end_std.iterator.map.MapIterator.init:

.globl std.iterator.map.MapIterator.next
std.iterator.map.MapIterator.next:
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
std.iterator.map.MapIterator.next_entry:
  movq $0, rax
  jmp std.iterator.map.MapIterator.next_epilogue
std.iterator.map.MapIterator.next_epilogue:
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
.Lfunc_end_std.iterator.map.MapIterator.next:

.globl test_iterator_basics
test_iterator_basics:
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
test_iterator_basics_entry:
test_iterator_basics_block_0:
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
  movq $r2, rcx
  call std.iterator.index.iterator
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq $0, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $r2, rcx
  call std.iterator.index.iterator
  movq $r32, rcx
  call std.iterator.index.collect
  movq $r34, rcx
  call lm_list_len
  movq $r36, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq $r34, rcx
  movq $1, rdx
  call lm_list_get
  movq $r42, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq $9, rax
  jmp test_iterator_basics_epilogue
test_iterator_basics_epilogue:
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
.Lfunc_end_test_iterator_basics:

.globl std.iterator.index.iterator
std.iterator.index.iterator:
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
std.iterator.index.iterator_entry:
std.iterator.index.iterator_block_0:
  movq [rbp + -64], rcx
  call std.iterator.iterator.iterator
  movq $r1, rax
  jmp std.iterator.index.iterator_epilogue
std.iterator.index.iterator_epilogue:
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
.Lfunc_end_std.iterator.index.iterator:

.globl test_chain
test_chain:
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
test_chain_entry:
test_chain_block_0:
  movq [rel str_const_17], rcx
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
  movq $0, rcx
  call lm_list_new
  movq $r8, rcx
  movq $25, rdx
  call lm_list_append
  movq $r8, rcx
  movq $33, rdx
  call lm_list_append
  movq $r2, rcx
  call std.iterator.index.iterator
  movq $r8, rcx
  call std.iterator.index.iterator
  movq $r14, rcx
  movq $r16, rdx
  call std.iterator.index.chain
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq $0, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq $0, rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq $9, rax
  jmp test_chain_epilogue
test_chain_epilogue:
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
.Lfunc_end_test_chain:

.globl std.iterator.index.chain
std.iterator.index.chain:
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
std.iterator.index.chain_entry:
std.iterator.index.chain_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.iterator.chain.chain
  movq $r2, rax
  jmp std.iterator.index.chain_epilogue
std.iterator.index.chain_epilogue:
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
.Lfunc_end_std.iterator.index.chain:

.globl test_enumerate
test_enumerate:
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
test_enumerate_entry:
test_enumerate_block_0:
  movq [rel str_const_23], rcx
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
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r2, rcx
  movq [rbp + -96], rdx
  call lm_list_append
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r2, rcx
  movq [rbp + -104], rdx
  call lm_list_append
  movq $r2, rcx
  call std.iterator.index.iterator
  movq $r8, rcx
  call std.iterator.index.enumerate
  movq $0, rax
  movq rax, [rbp + -112]
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $0, rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $0, rax
  movq rax, [rbp + -160]
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call lm_assert
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq $0, rax
  cmpq [rbp + -184], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq $9, rax
  jmp test_enumerate_epilogue
test_enumerate_epilogue:
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
.Lfunc_end_test_enumerate:

.globl std.iterator.iterator.PeekableIterator.next
std.iterator.iterator.PeekableIterator.next:
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
std.iterator.iterator.PeekableIterator.next_entry:
  movq $0, rax
  jmp std.iterator.iterator.PeekableIterator.next_epilogue
std.iterator.iterator.PeekableIterator.next_epilogue:
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
.Lfunc_end_std.iterator.iterator.PeekableIterator.next:

.globl test_zip
test_zip:
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
test_zip_entry:
test_zip_block_0:
  movq [rel str_const_33], rcx
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
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r8, rcx
  movq [rbp + -96], rdx
  call lm_list_append
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r8, rcx
  movq [rbp + -104], rdx
  call lm_list_append
  movq $r2, rcx
  call std.iterator.index.iterator
  movq $r8, rcx
  call std.iterator.index.iterator
  movq $r14, rcx
  movq $r16, rdx
  call std.iterator.index.zip
  movq $0, rax
  movq rax, [rbp + -112]
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $0, rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $0, rax
  movq rax, [rbp + -160]
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call lm_assert
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq $0, rax
  cmpq [rbp + -184], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq $9, rax
  jmp test_zip_epilogue
test_zip_epilogue:
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
.Lfunc_end_test_zip:

.globl test_take
test_take:
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
test_take_entry:
test_take_block_0:
  movq [rel str_const_43], rcx
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
  call std.iterator.index.iterator
  movq $r14, rcx
  movq $25, rdx
  call std.iterator.index.take
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq $0, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $9, rax
  jmp test_take_epilogue
test_take_epilogue:
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
.Lfunc_end_test_take:

.globl std.iterator.map.__init__
std.iterator.map.__init__:
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
std.iterator.map.__init___entry:
  movq $0, rax
  jmp std.iterator.map.__init___epilogue
std.iterator.map.__init___epilogue:
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
.Lfunc_end_std.iterator.map.__init__:

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
  sub rsp, 152
test_filter_entry:
test_filter_block_0:
  movq [rel str_const_48], rcx
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
  call std.iterator.index.iterator
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r14, rcx
  movq [rbp + -96], rdx
  call std.iterator.index.filter
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq $0, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq $0, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
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

.globl std.iterator.index.skip
std.iterator.index.skip:
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
std.iterator.index.skip_entry:
std.iterator.index.skip_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.iterator.skip.skip
  movq $r2, rax
  jmp std.iterator.index.skip_epilogue
std.iterator.index.skip_epilogue:
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
.Lfunc_end_std.iterator.index.skip:

.globl std.iterator.enumerate.EnumerateIterator.next
std.iterator.enumerate.EnumerateIterator.next:
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
std.iterator.enumerate.EnumerateIterator.next_entry:
  movq $0, rax
  jmp std.iterator.enumerate.EnumerateIterator.next_epilogue
std.iterator.enumerate.EnumerateIterator.next_epilogue:
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
.Lfunc_end_std.iterator.enumerate.EnumerateIterator.next:

.globl square
square:
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
square_entry:
square_block_0:
  movq [rbp + -64], rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  imulq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp square_epilogue
square_epilogue:
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
.Lfunc_end_square:

.globl std.iterator.index.zip
std.iterator.index.zip:
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
std.iterator.index.zip_entry:
std.iterator.index.zip_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.iterator.zip.zip
  movq $r2, rax
  jmp std.iterator.index.zip_epilogue
std.iterator.index.zip_epilogue:
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
.Lfunc_end_std.iterator.index.zip:

.globl std.iterator.index.enumerate
std.iterator.index.enumerate:
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
std.iterator.index.enumerate_entry:
std.iterator.index.enumerate_block_0:
  movq [rbp + -64], rcx
  call std.iterator.enumerate.enumerate
  movq $r1, rax
  jmp std.iterator.index.enumerate_epilogue
std.iterator.index.enumerate_epilogue:
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
.Lfunc_end_std.iterator.index.enumerate:

.globl std.iterator.zip.__init__
std.iterator.zip.__init__:
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
std.iterator.zip.__init___entry:
  movq $0, rax
  jmp std.iterator.zip.__init___epilogue
std.iterator.zip.__init___epilogue:
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
.Lfunc_end_std.iterator.zip.__init__:

.globl std.iterator.iterator.ListIterator.init
std.iterator.iterator.ListIterator.init:
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
std.iterator.iterator.ListIterator.init_entry:
  movq $0, rax
  jmp std.iterator.iterator.ListIterator.init_epilogue
std.iterator.iterator.ListIterator.init_epilogue:
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
.Lfunc_end_std.iterator.iterator.ListIterator.init:

.globl std.iterator.iterator.collect
std.iterator.iterator.collect:
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
std.iterator.iterator.collect_entry:
std.iterator.iterator.collect_block_0:
  movq $0, rcx
  call lm_list_new
  jmp std.iterator.iterator.collect_block_5
std.iterator.iterator.collect_block_5:
  movq $0, rax
  cmpq $2, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.iterator.iterator.collect_block_8
  jmp std.iterator.iterator.collect_block_12
std.iterator.iterator.collect_block_8:
  jmp std.iterator.iterator.collect_block_8
  movq $r1, rcx
  movq $0, rdx
  call lm_list_append
  jmp std.iterator.iterator.collect_block_5
std.iterator.iterator.collect_block_12:
  movq $r1, rax
  jmp std.iterator.iterator.collect_epilogue
std.iterator.iterator.collect_epilogue:
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
.Lfunc_end_std.iterator.iterator.collect:

.globl test_skip
test_skip:
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
test_skip_entry:
test_skip_block_0:
  movq [rel str_const_54], rcx
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
  call std.iterator.index.iterator
  movq $r14, rcx
  movq $17, rdx
  call std.iterator.index.skip
  movq $0, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  movq $0, rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq $0, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $9, rax
  jmp test_skip_epilogue
test_skip_epilogue:
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
.Lfunc_end_test_skip:

.globl std.iterator.filter.__init__
std.iterator.filter.__init__:
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
std.iterator.filter.__init___entry:
  movq $0, rax
  jmp std.iterator.filter.__init___epilogue
std.iterator.filter.__init___epilogue:
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
.Lfunc_end_std.iterator.filter.__init__:

.globl std.iterator.chain.__init__
std.iterator.chain.__init__:
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
std.iterator.chain.__init___entry:
  movq $0, rax
  jmp std.iterator.chain.__init___epilogue
std.iterator.chain.__init___epilogue:
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
.Lfunc_end_std.iterator.chain.__init__:

.globl std.iterator.skip.SkipIterator.next
std.iterator.skip.SkipIterator.next:
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
std.iterator.skip.SkipIterator.next_entry:
  movq $0, rax
  jmp std.iterator.skip.SkipIterator.next_epilogue
std.iterator.skip.SkipIterator.next_epilogue:
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
.Lfunc_end_std.iterator.skip.SkipIterator.next:

.globl std.iterator.skip.skip
std.iterator.skip.skip:
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
std.iterator.skip.skip_entry:
std.iterator.skip.skip_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.iterator.skip.SkipIterator.init
  movq [rbp + -80], rax
  jmp std.iterator.skip.skip_epilogue
std.iterator.skip.skip_epilogue:
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
.Lfunc_end_std.iterator.skip.skip:

.globl std.iterator.enumerate.EnumerateIterator.init
std.iterator.enumerate.EnumerateIterator.init:
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
std.iterator.enumerate.EnumerateIterator.init_entry:
  movq $0, rax
  jmp std.iterator.enumerate.EnumerateIterator.init_epilogue
std.iterator.enumerate.EnumerateIterator.init_epilogue:
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
.Lfunc_end_std.iterator.enumerate.EnumerateIterator.init:

.globl std.iterator.zip.ZipIterator.next
std.iterator.zip.ZipIterator.next:
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
std.iterator.zip.ZipIterator.next_entry:
  movq $0, rax
  jmp std.iterator.zip.ZipIterator.next_epilogue
std.iterator.zip.ZipIterator.next_epilogue:
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
.Lfunc_end_std.iterator.zip.ZipIterator.next:

.globl std.iterator.zip.ZipIterator.init
std.iterator.zip.ZipIterator.init:
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
std.iterator.zip.ZipIterator.init_entry:
  movq $0, rax
  jmp std.iterator.zip.ZipIterator.init_epilogue
std.iterator.zip.ZipIterator.init_epilogue:
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
.Lfunc_end_std.iterator.zip.ZipIterator.init:

.globl std.iterator.iterator.iterator
std.iterator.iterator.iterator:
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
std.iterator.iterator.iterator_entry:
std.iterator.iterator.iterator_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.iterator.iterator.ListIterator.init
  movq [rbp + -72], rax
  jmp std.iterator.iterator.iterator_epilogue
std.iterator.iterator.iterator_epilogue:
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
.Lfunc_end_std.iterator.iterator.iterator:

.globl std.iterator.enumerate.enumerate
std.iterator.enumerate.enumerate:
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
std.iterator.enumerate.enumerate_entry:
std.iterator.enumerate.enumerate_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.iterator.enumerate.EnumerateIterator.init
  movq [rbp + -72], rax
  jmp std.iterator.enumerate.enumerate_epilogue
std.iterator.enumerate.enumerate_epilogue:
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
.Lfunc_end_std.iterator.enumerate.enumerate:

.globl is_odd
is_odd:
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
is_odd_entry:
is_odd_block_0:
  movq [rbp + -64], rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rdx, [rbp + -80]
  movq [rbp + -80], rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp is_odd_epilogue
is_odd_epilogue:
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
.Lfunc_end_is_odd:

.globl std.iterator.enumerate.__init__
std.iterator.enumerate.__init__:
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
std.iterator.enumerate.__init___entry:
  movq $0, rax
  jmp std.iterator.enumerate.__init___epilogue
std.iterator.enumerate.__init___epilogue:
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
.Lfunc_end_std.iterator.enumerate.__init__:

.globl test_map
test_map:
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
test_map_entry:
test_map_block_0:
  movq [rel str_const_59], rcx
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
  call std.iterator.index.iterator
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r10, rcx
  movq [rbp + -96], rdx
  call std.iterator.index.map
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq $0, rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq $0, rax
  cmpq $73, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq $9, rax
  jmp test_map_epilogue
test_map_epilogue:
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
.Lfunc_end_test_map:

.globl std.iterator.filter.FilterIterator.next
std.iterator.filter.FilterIterator.next:
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
std.iterator.filter.FilterIterator.next_entry:
  movq $0, rax
  jmp std.iterator.filter.FilterIterator.next_epilogue
std.iterator.filter.FilterIterator.next_epilogue:
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
.Lfunc_end_std.iterator.filter.FilterIterator.next:

.globl std.iterator.iterator.PeekableIterator.init
std.iterator.iterator.PeekableIterator.init:
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
std.iterator.iterator.PeekableIterator.init_entry:
  movq $0, rax
  jmp std.iterator.iterator.PeekableIterator.init_epilogue
std.iterator.iterator.PeekableIterator.init_epilogue:
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
.Lfunc_end_std.iterator.iterator.PeekableIterator.init:

.globl std.iterator.filter.FilterIterator.init
std.iterator.filter.FilterIterator.init:
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
std.iterator.filter.FilterIterator.init_entry:
  movq $0, rax
  jmp std.iterator.filter.FilterIterator.init_epilogue
std.iterator.filter.FilterIterator.init_epilogue:
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
.Lfunc_end_std.iterator.filter.FilterIterator.init:

.globl std.iterator.filter.filter
std.iterator.filter.filter:
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
std.iterator.filter.filter_entry:
std.iterator.filter.filter_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.iterator.filter.FilterIterator.init
  movq [rbp + -80], rax
  jmp std.iterator.filter.filter_epilogue
std.iterator.filter.filter_epilogue:
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
.Lfunc_end_std.iterator.filter.filter:

.globl std.iterator.take.__init__
std.iterator.take.__init__:
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
std.iterator.take.__init___entry:
  movq $0, rax
  jmp std.iterator.take.__init___epilogue
std.iterator.take.__init___epilogue:
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
.Lfunc_end_std.iterator.take.__init__:

.globl std.iterator.iterator.ListIterator.next
std.iterator.iterator.ListIterator.next:
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
std.iterator.iterator.ListIterator.next_entry:
  movq $0, rax
  jmp std.iterator.iterator.ListIterator.next_epilogue
std.iterator.iterator.ListIterator.next_epilogue:
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
.Lfunc_end_std.iterator.iterator.ListIterator.next:

.globl std.iterator.iterator.PeekableIterator.peek
std.iterator.iterator.PeekableIterator.peek:
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
std.iterator.iterator.PeekableIterator.peek_entry:
  movq $0, rax
  jmp std.iterator.iterator.PeekableIterator.peek_epilogue
std.iterator.iterator.PeekableIterator.peek_epilogue:
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
.Lfunc_end_std.iterator.iterator.PeekableIterator.peek:

.globl std.iterator.chain.chain
std.iterator.chain.chain:
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
std.iterator.chain.chain_entry:
std.iterator.chain.chain_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.iterator.chain.ChainIterator.init
  movq [rbp + -80], rax
  jmp std.iterator.chain.chain_epilogue
std.iterator.chain.chain_epilogue:
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
.Lfunc_end_std.iterator.chain.chain:

.globl std.iterator.take.TakeIterator.next
std.iterator.take.TakeIterator.next:
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
std.iterator.take.TakeIterator.next_entry:
  movq $0, rax
  jmp std.iterator.take.TakeIterator.next_epilogue
std.iterator.take.TakeIterator.next_epilogue:
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
.Lfunc_end_std.iterator.take.TakeIterator.next:

.globl std.iterator.skip.SkipIterator.init
std.iterator.skip.SkipIterator.init:
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
std.iterator.skip.SkipIterator.init_entry:
  movq $0, rax
  jmp std.iterator.skip.SkipIterator.init_epilogue
std.iterator.skip.SkipIterator.init_epilogue:
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
.Lfunc_end_std.iterator.skip.SkipIterator.init:

.globl std.iterator.iterator.__init__
std.iterator.iterator.__init__:
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
std.iterator.iterator.__init___entry:
  movq $0, rax
  jmp std.iterator.iterator.__init___epilogue
std.iterator.iterator.__init___epilogue:
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
.Lfunc_end_std.iterator.iterator.__init__:

.globl std.iterator.chain.ChainIterator.init
std.iterator.chain.ChainIterator.init:
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
std.iterator.chain.ChainIterator.init_entry:
  movq $0, rax
  jmp std.iterator.chain.ChainIterator.init_epilogue
std.iterator.chain.ChainIterator.init_epilogue:
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
.Lfunc_end_std.iterator.chain.ChainIterator.init:

.globl std.iterator.zip.zip
std.iterator.zip.zip:
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
std.iterator.zip.zip_entry:
std.iterator.zip.zip_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.iterator.zip.ZipIterator.init
  movq [rbp + -80], rax
  jmp std.iterator.zip.zip_epilogue
std.iterator.zip.zip_epilogue:
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
.Lfunc_end_std.iterator.zip.zip:

.globl std.iterator.take.TakeIterator.init
std.iterator.take.TakeIterator.init:
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
std.iterator.take.TakeIterator.init_entry:
  movq $0, rax
  jmp std.iterator.take.TakeIterator.init_epilogue
std.iterator.take.TakeIterator.init_epilogue:
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
.Lfunc_end_std.iterator.take.TakeIterator.init:

.globl std.iterator.skip.__init__
std.iterator.skip.__init__:
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
std.iterator.skip.__init___entry:
  movq $0, rax
  jmp std.iterator.skip.__init___epilogue
std.iterator.skip.__init___epilogue:
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
.Lfunc_end_std.iterator.skip.__init__:

.globl std.iterator.chain.ChainIterator.next
std.iterator.chain.ChainIterator.next:
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
std.iterator.chain.ChainIterator.next_entry:
  movq $0, rax
  jmp std.iterator.chain.ChainIterator.next_epilogue
std.iterator.chain.ChainIterator.next_epilogue:
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
.Lfunc_end_std.iterator.chain.ChainIterator.next:

.globl std.iterator.take.take
std.iterator.take.take:
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
std.iterator.take.take_entry:
std.iterator.take.take_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.iterator.take.TakeIterator.init
  movq [rbp + -80], rax
  jmp std.iterator.take.take_epilogue
std.iterator.take.take_epilogue:
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
.Lfunc_end_std.iterator.take.take:

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

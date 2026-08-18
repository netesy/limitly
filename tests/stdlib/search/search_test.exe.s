.section .data
.align 8
heap_ptr:
  .quad __fyra_heap
.section .bss
.align 16
__fyra_heap:
  .zero 1048576
.text
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
  sub rsp, 88
main_entry:
main_block_0:
  call std.search.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq $0, rcx
  call lm_list_new
  movq $r0, rcx
  movq $9, rdx
  call lm_list_append
  movq $r0, rcx
  movq $17, rdx
  call lm_list_append
  movq $r0, rcx
  movq $17, rdx
  call lm_list_append
  movq $r0, rcx
  movq $25, rdx
  call lm_list_append
  movq $r0, rcx
  movq $33, rdx
  call lm_list_append
  movq $r0, rcx
  movq $25, rdx
  call std.search.linear_search
  movq $r13, rax
  cmpq $25, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  testq rax, rax
  jne main_block_17
  jmp main_block_19
main_block_17:
  jmp main_block_17
  movq $9, rax
  jmp main_epilogue
main_block_19:
  movq $r0, rcx
  movq $33, rdx
  call std.search.binary_search
  movq $r19, rax
  cmpq $33, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne main_block_24
  jmp main_block_26
main_block_24:
  jmp main_block_24
  movq $17, rax
  jmp main_epilogue
main_block_26:
  movq $r0, rcx
  movq $17, rdx
  call std.search.lower_bound
  movq $r25, rax
  cmpq $9, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne main_block_31
  jmp main_block_33
main_block_31:
  jmp main_block_31
  movq $25, rax
  jmp main_epilogue
main_block_33:
  movq $r0, rcx
  movq $17, rdx
  call std.search.upper_bound
  movq $r31, rax
  cmpq $25, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne main_block_38
  jmp main_block_40
main_block_38:
  jmp main_block_38
  movq $33, rax
  jmp main_epilogue
main_block_40:
  movq $r0, rcx
  movq $17, rdx
  call std.search.equal_range
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
  movq $r39, rcx
  movq $57, rdx
  call lm_list_append
  movq $r39, rcx
  movq $41, rdx
  call std.search.interpolation_search
  movq $r49, rax
  cmpq $17, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne main_block_57
  jmp main_block_59
main_block_57:
  jmp main_block_57
  movq $41, rax
  jmp main_epilogue
main_block_59:
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

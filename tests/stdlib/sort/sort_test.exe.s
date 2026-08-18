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
  .string "reverse_cmp"
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
  call std.sort.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq $0, rcx
  call lm_list_new
  movq $r0, rcx
  movq $25, rdx
  call lm_list_append
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
  movq $10, rdx
  movq $2, r8
  call std.sort.stable_sort
  movq $r0, rcx
  movq $1, rdx
  call lm_list_get
  movq $r14, rax
  cmpq $9, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  testq rax, rax
  jne main_block_18
  jmp main_block_20
main_block_18:
  jmp main_block_18
  movq $9, rax
  jmp main_epilogue
main_block_20:
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $r0, rcx
  movq $10, rdx
  movq [rbp + -72], r8
  call std.sort.quicksort
  movq $r0, rcx
  movq $1, rdx
  call lm_list_get
  movq $r23, rax
  cmpq $25, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne main_block_28
  jmp main_block_30
main_block_28:
  jmp main_block_28
  movq $17, rax
  jmp main_epilogue
main_block_30:
  movq $0, rcx
  call lm_list_new
  movq $r28, rcx
  movq $73, rdx
  call lm_list_append
  movq $r28, rcx
  movq $1, rdx
  call lm_list_append
  movq $r28, rcx
  movq $25, rdx
  call lm_list_append
  movq $r28, rcx
  movq $25, rdx
  call lm_list_append
  movq $r28, rcx
  movq $10, rdx
  call std.sort.counting_sort
  movq $r28, rcx
  movq $1, rdx
  call lm_list_get
  movq $r41, rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne main_block_47
  jmp main_block_49
main_block_47:
  jmp main_block_47
  movq $25, rax
  jmp main_epilogue
main_block_49:
  movq $r28, rcx
  movq $18, rdx
  call std.sort.radix_sort
  movq $r28, rcx
  movq $1, rdx
  call lm_list_get
  movq $r49, rax
  cmpq $73, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne main_block_56
  jmp main_block_58
main_block_56:
  jmp main_block_56
  movq $33, rax
  jmp main_epilogue
main_block_58:
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

.globl reverse_cmp
reverse_cmp:
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
reverse_cmp_entry:
reverse_cmp_block_0:
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  setg al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne reverse_cmp_block_2
  jmp reverse_cmp_block_5
reverse_cmp_block_2:
  jmp reverse_cmp_block_2
  movq $9, rax
  negq rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp reverse_cmp_epilogue
reverse_cmp_block_5:
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne reverse_cmp_block_7
  jmp reverse_cmp_block_9
reverse_cmp_block_7:
  jmp reverse_cmp_block_7
  movq $9, rax
  jmp reverse_cmp_epilogue
reverse_cmp_block_9:
  movq $1, rax
  jmp reverse_cmp_epilogue
reverse_cmp_epilogue:
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
.Lfunc_end_reverse_cmp:

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

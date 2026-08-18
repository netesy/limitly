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
  .string "LinkedList length: %s"
.align 8
str_const_1:
  .string "LinkedList length should be 3"
.align 8
str_const_2:
  .string "Pop front should return 0"
.align 8
str_const_3:
  .string "Pop back should return 2"
.align 8
str_const_4:
  .string "Pop back should return 1"
.align 8
str_const_5:
  .string "Pop back on empty list should return nil"
.align 8
str_const_6:
  .string "List should be empty"
.align 8
str_const_7:
  .string "First element from iterator should be 10"
.align 8
str_const_8:
  .string "Second element from iterator should be 20"
.align 8
str_const_9:
  .string "Iterator should be exhausted"
.align 8
str_const_10:
  .string "LinkedList tests passed!"
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
  sub rsp, 264
main_entry:
main_block_0:
  call std.collections.linkedlist.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.collections.linkedlist.LinkedList.init
  movq [rbp + -64], rcx
  movq $9, rdx
  call std.collections.linkedlist.LinkedList.push_back
  movq [rbp + -64], rcx
  movq $17, rdx
  call std.collections.linkedlist.LinkedList.push_back
  movq [rbp + -64], rcx
  movq $1, rdx
  call std.collections.linkedlist.LinkedList.push_front
  movq [rbp + -64], rcx
  call std.collections.linkedlist.LinkedList.length
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -72], rcx
  movq $r9, rdx
  call lm_rt_str_format
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  addq $16, rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  mov rax, [rax]
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  call lm_print_str
  movq [rbp + -64], rcx
  call std.collections.linkedlist.LinkedList.length
  movq $r13, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq [rbp + -64], rcx
  call std.collections.linkedlist.LinkedList.pop_front
  movq $r18, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rbp + -64], rcx
  call std.collections.linkedlist.LinkedList.pop_back
  movq $r23, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rbp + -64], rcx
  call std.collections.linkedlist.LinkedList.pop_back
  movq $r28, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq [rbp + -64], rcx
  call std.collections.linkedlist.LinkedList.pop_back
  movq $r33, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq [rbp + -64], rcx
  call std.collections.linkedlist.LinkedList.is_empty
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq $r38, rcx
  movq [rbp + -192], rdx
  call lm_assert
  movq [rbp + -64], rcx
  movq $81, rdx
  call std.collections.linkedlist.LinkedList.push_back
  movq [rbp + -64], rcx
  movq $161, rdx
  call std.collections.linkedlist.LinkedList.push_back
  movq [rbp + -64], rcx
  call std.collections.linkedlist.LinkedList.iterator
  movq $r45, rcx
  call std.collections.linkedlist.Iterator.next
  movq $r47, rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -200], rcx
  movq [rbp + -208], rdx
  call lm_assert
  movq $r45, rcx
  call std.collections.linkedlist.Iterator.next
  movq $r52, rax
  cmpq $161, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -216]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -216], rcx
  movq [rbp + -224], rdx
  call lm_assert
  movq $r45, rcx
  call std.collections.linkedlist.Iterator.next
  movq $r57, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rcx
  movq [rbp + -240], rdx
  call lm_assert
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  addq $16, rax
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  mov rax, [rax]
  movq rax, [rbp + -272]
  movq [rbp + -272], rcx
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

.globl std.collections.linkedlist.__init__
std.collections.linkedlist.__init__:
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
std.collections.linkedlist.__init___entry:
  movq $0, rax
  jmp std.collections.linkedlist.__init___epilogue
std.collections.linkedlist.__init___epilogue:
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
.Lfunc_end_std.collections.linkedlist.__init__:

.globl std.collections.linkedlist.LinkedList.push_front
std.collections.linkedlist.LinkedList.push_front:
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
std.collections.linkedlist.LinkedList.push_front_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.push_front_epilogue
std.collections.linkedlist.LinkedList.push_front_epilogue:
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
.Lfunc_end_std.collections.linkedlist.LinkedList.push_front:

.globl std.collections.linkedlist.Iterator.next
std.collections.linkedlist.Iterator.next:
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
std.collections.linkedlist.Iterator.next_entry:
  movq $0, rax
  jmp std.collections.linkedlist.Iterator.next_epilogue
std.collections.linkedlist.Iterator.next_epilogue:
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
.Lfunc_end_std.collections.linkedlist.Iterator.next:

.globl std.collections.linkedlist.LinkedList.length
std.collections.linkedlist.LinkedList.length:
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
std.collections.linkedlist.LinkedList.length_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.length_epilogue
std.collections.linkedlist.LinkedList.length_epilogue:
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
.Lfunc_end_std.collections.linkedlist.LinkedList.length:

.globl std.collections.linkedlist.LinkedList.pop_back
std.collections.linkedlist.LinkedList.pop_back:
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
std.collections.linkedlist.LinkedList.pop_back_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.pop_back_epilogue
std.collections.linkedlist.LinkedList.pop_back_epilogue:
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
.Lfunc_end_std.collections.linkedlist.LinkedList.pop_back:

.globl std.collections.linkedlist.LinkedList.is_empty
std.collections.linkedlist.LinkedList.is_empty:
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
std.collections.linkedlist.LinkedList.is_empty_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.is_empty_epilogue
std.collections.linkedlist.LinkedList.is_empty_epilogue:
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
.Lfunc_end_std.collections.linkedlist.LinkedList.is_empty:

.globl std.collections.linkedlist.LinkedList.iterator
std.collections.linkedlist.LinkedList.iterator:
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
std.collections.linkedlist.LinkedList.iterator_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.iterator_epilogue
std.collections.linkedlist.LinkedList.iterator_epilogue:
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
.Lfunc_end_std.collections.linkedlist.LinkedList.iterator:

.globl std.collections.linkedlist.Iterator.init
std.collections.linkedlist.Iterator.init:
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
std.collections.linkedlist.Iterator.init_entry:
  movq $0, rax
  jmp std.collections.linkedlist.Iterator.init_epilogue
std.collections.linkedlist.Iterator.init_epilogue:
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
.Lfunc_end_std.collections.linkedlist.Iterator.init:

.globl std.collections.linkedlist.LinkedList.pop_front
std.collections.linkedlist.LinkedList.pop_front:
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
std.collections.linkedlist.LinkedList.pop_front_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.pop_front_epilogue
std.collections.linkedlist.LinkedList.pop_front_epilogue:
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
.Lfunc_end_std.collections.linkedlist.LinkedList.pop_front:

.globl std.collections.linkedlist.Node.init
std.collections.linkedlist.Node.init:
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
std.collections.linkedlist.Node.init_entry:
  movq $0, rax
  jmp std.collections.linkedlist.Node.init_epilogue
std.collections.linkedlist.Node.init_epilogue:
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
.Lfunc_end_std.collections.linkedlist.Node.init:

.globl std.collections.linkedlist.LinkedList.push_back
std.collections.linkedlist.LinkedList.push_back:
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
std.collections.linkedlist.LinkedList.push_back_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.push_back_epilogue
std.collections.linkedlist.LinkedList.push_back_epilogue:
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
.Lfunc_end_std.collections.linkedlist.LinkedList.push_back:

.globl std.collections.linkedlist.LinkedList.len
std.collections.linkedlist.LinkedList.len:
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
std.collections.linkedlist.LinkedList.len_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.len_epilogue
std.collections.linkedlist.LinkedList.len_epilogue:
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
.Lfunc_end_std.collections.linkedlist.LinkedList.len:

.globl std.collections.linkedlist.LinkedList.init
std.collections.linkedlist.LinkedList.init:
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
std.collections.linkedlist.LinkedList.init_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.init_epilogue
std.collections.linkedlist.LinkedList.init_epilogue:
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
.Lfunc_end_std.collections.linkedlist.LinkedList.init:

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

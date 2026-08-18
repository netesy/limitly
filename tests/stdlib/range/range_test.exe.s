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
  call std.range.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq $9, rcx
  movq $17, rdx
  movq $9, r8
  call std.range.inclusive
  movq $r3, rcx
  call std.range.Range.iterator
  movq $r4, rcx
  call std.range.RangeIterator.next
  movq $r6, rax
  cmpq $9, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  testq rax, rax
  jne main_block_10
  jmp main_block_12
main_block_10:
  jmp main_block_10
  movq $9, rax
  jmp main_epilogue
main_block_12:
  movq $r4, rcx
  call std.range.RangeIterator.next
  movq $r11, rax
  cmpq $17, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne main_block_16
  jmp main_block_18
main_block_16:
  jmp main_block_16
  movq $17, rax
  jmp main_epilogue
main_block_18:
  movq $r4, rcx
  call std.range.RangeIterator.next
  movq $r16, rax
  cmpq $2, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne main_block_22
  jmp main_block_24
main_block_22:
  jmp main_block_22
  movq $25, rax
  jmp main_epilogue
main_block_24:
  movq $9, rax
  negq rax
  movq rax, [rbp + -88]
  movq $25, rcx
  movq $9, rdx
  movq [rbp + -88], r8
  call std.range.reverse
  movq $r25, rcx
  call std.range.Range.iterator
  movq $r26, rcx
  call std.range.RangeIterator.next
  movq $r28, rax
  cmpq $25, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne main_block_35
  jmp main_block_37
main_block_35:
  jmp main_block_35
  movq $33, rax
  jmp main_epilogue
main_block_37:
  movq $81, rcx
  movq $17, rdx
  call std.range.infinite
  movq $r35, rcx
  call std.range.Range.iterator
  movq $r36, rcx
  call std.range.RangeIterator.next
  movq $r38, rax
  cmpq $81, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne main_block_46
  jmp main_block_48
main_block_46:
  jmp main_block_46
  movq $41, rax
  jmp main_epilogue
main_block_48:
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

.globl std.range.reverse
std.range.reverse:
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
std.range.reverse_entry:
std.range.reverse_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  movq [rbp + -80], r9
  call std.range.Range.init
  movq [rbp + -88], rax
  jmp std.range.reverse_epilogue
std.range.reverse_epilogue:
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
.Lfunc_end_std.range.reverse:

.globl std.range.inclusive
std.range.inclusive:
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
std.range.inclusive_entry:
std.range.inclusive_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  movq [rbp + -80], r9
  call std.range.Range.init
  movq [rbp + -88], rax
  jmp std.range.inclusive_epilogue
std.range.inclusive_epilogue:
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
.Lfunc_end_std.range.inclusive:

.globl std.range.exclusive
std.range.exclusive:
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
std.range.exclusive_entry:
std.range.exclusive_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  movq [rbp + -80], r9
  call std.range.Range.init
  movq [rbp + -88], rax
  jmp std.range.exclusive_epilogue
std.range.exclusive_epilogue:
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
.Lfunc_end_std.range.exclusive:

.globl std.range.RangeIterator.init
std.range.RangeIterator.init:
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
std.range.RangeIterator.init_entry:
  movq $0, rax
  jmp std.range.RangeIterator.init_epilogue
std.range.RangeIterator.init_epilogue:
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
.Lfunc_end_std.range.RangeIterator.init:

.globl std.range.Range.iterator
std.range.Range.iterator:
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
std.range.Range.iterator_entry:
  movq $0, rax
  jmp std.range.Range.iterator_epilogue
std.range.Range.iterator_epilogue:
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
.Lfunc_end_std.range.Range.iterator:

.globl std.range.infinite
std.range.infinite:
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
std.range.infinite_entry:
std.range.infinite_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq $1, r8
  movq [rbp + -72], r9
  call std.range.Range.init
  movq [rbp + -80], rax
  jmp std.range.infinite_epilogue
std.range.infinite_epilogue:
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
.Lfunc_end_std.range.infinite:

.globl std.range.Range.init
std.range.Range.init:
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
std.range.Range.init_entry:
  movq $0, rax
  jmp std.range.Range.init_epilogue
std.range.Range.init_epilogue:
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
.Lfunc_end_std.range.Range.init:

.globl std.range.__init__
std.range.__init__:
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
std.range.__init___entry:
  movq $0, rax
  jmp std.range.__init___epilogue
std.range.__init___epilogue:
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
.Lfunc_end_std.range.__init__:

.globl std.range.stepped
std.range.stepped:
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
std.range.stepped_entry:
std.range.stepped_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  movq [rbp + -80], r9
  call std.range.Range.init
  movq [rbp + -88], rax
  jmp std.range.stepped_epilogue
std.range.stepped_epilogue:
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
.Lfunc_end_std.range.stepped:

.globl std.range.RangeIterator.next
std.range.RangeIterator.next:
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
std.range.RangeIterator.next_entry:
  movq $0, rax
  jmp std.range.RangeIterator.next_epilogue
std.range.RangeIterator.next_epilogue:
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
.Lfunc_end_std.range.RangeIterator.next:

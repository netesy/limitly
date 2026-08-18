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
  .string "Counter should be 2"
.align 8
str_const_1:
  .string "Frame method test passed!"
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
  and rsp, -16
  sub rsp, 32
  call main
  add rsp, 32
  mov rcx, rax
  sub rsp, 32
  call ExitProcess
  add rsp, 32

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
  sub rsp, 184
main_entry:
main_block_0:
  call main
  mov [rbp + -64], rax
  mov rax, 0
  jmp main_epilogue
main_entry:
main_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  mov rcx, [rbp + -72]
  call Counter.init
  mov [rbp + -80], rax
  mov rcx, [rbp + -72]
  call Counter.inc
  mov [rbp + -88], rax
  mov rcx, [rbp + -72]
  call Counter.inc
  mov [rbp + -96], rax
  mov rcx, [rbp + -72]
  call Counter.get
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  cmp rax, 2
  sete al
  movzx eax, al
  mov [rbp + -112], rax
  mov rcx, [rbp + -112]
  lea rdx, [rel str_const_0]
  call lm_assert
  mov [rbp + -120], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -128], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -128]
  mov [rdx], rax
  jmp main_ps_loop_1
main_ps_loop_1:
  mov rax, [rbp + -128]
  mov rax, [rax]
  mov [rbp + -136], rax
  lea rax, [rel str_const_1]
  add rax, [rbp + -136]
  mov [rbp + -144], rax
  mov rax, [rbp + -144]
  movzx rax, byte ptr [rax]
  mov [rbp + -152], rax
  mov rax, [rbp + -152]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -160], rax
  mov rax, [rbp + -136]
  add rax, 1
  mov [rbp + -168], rax
  mov rax, [rbp + -168]
  mov rdx, [rbp + -128]
  mov [rdx], rax
  mov rax, [rbp + -160]
  test rax, rax
  jne main_ps_done_1
  jmp main_ps_loop_1
main_ps_done_1:
  mov rax, [rbp + -128]
  mov rax, [rax]
  mov [rbp + -176], rax
  mov rax, [rbp + -176]
  sub rax, 1
  mov [rbp + -184], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_1]
  mov r8d, dword ptr [rbp + -184]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -192], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel nl]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -200], rax
  mov rax, 0
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

.globl Counter.init
Counter.init:
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
Counter.init_entry:
  mov rax, 0
  jmp Counter.init_epilogue
Counter.init_epilogue:
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
.Lfunc_end_Counter.init:

.globl Counter.get
Counter.get:
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
Counter.get_entry:
  mov rax, 0
  jmp Counter.get_epilogue
Counter.get_epilogue:
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
.Lfunc_end_Counter.get:

.globl Counter.inc
Counter.inc:
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
Counter.inc_entry:
  mov rax, 0
  jmp Counter.inc_epilogue
Counter.inc_epilogue:
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
.Lfunc_end_Counter.inc:

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
  mov rax, [rbp + -64]
  test rax, rax
  jne lm_assert_pass
  jmp lm_assert_fail
lm_assert_fail:
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel assert_fail]
  mov r8d, dword ptr 17
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -80], rax
  movq $50397203, rax
  movq rax, [rbp + -88]
  mov rax, 0
  jmp lm_assert_epilogue
lm_assert_pass:
  mov rax, 0
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

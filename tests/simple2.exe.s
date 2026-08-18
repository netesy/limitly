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
str_minus:
  .string "-"
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
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -64]
  add rax, 31
  mov [rbp + -72], rax
  mov rax, 10
  mov rdx, [rbp + -72]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -72]
  mov rdx, [rbp + -88]
  mov [rdx], rax
  mov rax, 1
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -96], rax
  mov rax, [rbp + -96]
  test rax, rax
  jne main_pi_neg_1
  jmp main_pi_abs_1
main_pi_neg_1:
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_minus]
  mov r8d, dword ptr 1
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -104], rax
  mov rax, 1
  neg rax
  mov [rbp + -112], rax
  mov rax, [rbp + -112]
  mov rdx, [rbp + -80]
  mov [rdx], rax
  jmp main_pi_loop_1
main_pi_abs_1:
  mov rax, 1
  mov rdx, [rbp + -80]
  mov [rdx], rax
  jmp main_pi_loop_1
main_pi_loop_1:
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -120], rax
  mov rax, [rbp + -120]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -128], rax
  mov rax, [rbp + -120]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -136], rdx
  mov rax, [rbp + -136]
  add rax, 48
  mov [rbp + -144], rax
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -152], rax
  mov rax, [rbp + -152]
  sub rax, 1
  mov [rbp + -160], rax
  mov rax, [rbp + -144]
  mov rdx, [rbp + -160]
  mov byte ptr [rdx], al
  mov rax, [rbp + -128]
  mov rdx, [rbp + -80]
  mov [rdx], rax
  mov rax, [rbp + -160]
  mov rdx, [rbp + -88]
  mov [rdx], rax
  mov rax, [rbp + -128]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -168], rax
  mov rax, [rbp + -168]
  test rax, rax
  jne main_pi_loop_1
  jmp main_pi_emit_1
main_pi_emit_1:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -176], rax
  mov rax, [rbp + -64]
  add rax, 32
  mov [rbp + -184], rax
  mov rax, [rbp + -184]
  sub rax, [rbp + -176]
  mov [rbp + -192], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -176]
  mov r8d, dword ptr [rbp + -192]
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

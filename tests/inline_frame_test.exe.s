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
  .string "Simple X: "
.align 8
nl:
  .string "
"
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
  sub rsp, 296
main_entry:
main_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  mov rax, [rbp + -64]
  add rax, 0
  mov [rbp + -72], rax
  mov rax, [rbp + -64]
  mov rdx, [rbp + -72]
  mov [rdx], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -80]
  mov [rdx], rax
  jmp main_ps_loop_1
main_ps_loop_1:
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -88], rax
  lea rax, [rel str_const_0]
  add rax, [rbp + -88]
  mov [rbp + -96], rax
  mov rax, [rbp + -96]
  movzx rax, byte ptr [rax]
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -112], rax
  mov rax, [rbp + -88]
  add rax, 1
  mov [rbp + -120], rax
  mov rax, [rbp + -120]
  mov rdx, [rbp + -80]
  mov [rdx], rax
  mov rax, [rbp + -112]
  test rax, rax
  jne main_ps_done_1
  jmp main_ps_loop_1
main_ps_done_1:
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -128], rax
  mov rax, [rbp + -128]
  sub rax, 1
  mov [rbp + -136], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_0]
  mov r8d, dword ptr [rbp + -136]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -144], rax
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
  mov [rbp + -152], rax
  mov rax, [rbp + -64]
  add rax, 0
  mov [rbp + -160], rax
  mov rax, [rbp + -160]
  mov rax, [rax]
  mov [rbp + -168], rax
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -176], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -176]
  add rax, 31
  mov [rbp + -184], rax
  mov rax, 10
  mov rdx, [rbp + -184]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -192], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -200], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -184]
  mov rdx, [rbp + -200]
  mov [rdx], rax
  mov rax, [rbp + -168]
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -208], rax
  mov rax, [rbp + -208]
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
  mov [rbp + -216], rax
  mov rax, [rbp + -168]
  neg rax
  mov [rbp + -224], rax
  mov rax, [rbp + -224]
  mov rdx, [rbp + -192]
  mov [rdx], rax
  jmp main_pi_loop_1
main_pi_abs_1:
  mov rax, [rbp + -168]
  mov rdx, [rbp + -192]
  mov [rdx], rax
  jmp main_pi_loop_1
main_pi_loop_1:
  mov rax, [rbp + -192]
  mov rax, [rax]
  mov [rbp + -232], rax
  mov rax, [rbp + -232]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -240], rax
  mov rax, [rbp + -232]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -248], rdx
  mov rax, [rbp + -248]
  add rax, 48
  mov [rbp + -256], rax
  mov rax, [rbp + -200]
  mov rax, [rax]
  mov [rbp + -264], rax
  mov rax, [rbp + -264]
  sub rax, 1
  mov [rbp + -272], rax
  mov rax, [rbp + -256]
  mov rdx, [rbp + -272]
  mov byte ptr [rdx], al
  mov rax, [rbp + -240]
  mov rdx, [rbp + -192]
  mov [rdx], rax
  mov rax, [rbp + -272]
  mov rdx, [rbp + -200]
  mov [rdx], rax
  mov rax, [rbp + -240]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -280], rax
  mov rax, [rbp + -280]
  test rax, rax
  jne main_pi_loop_1
  jmp main_pi_emit_1
main_pi_emit_1:
  mov rax, [rbp + -200]
  mov rax, [rax]
  mov [rbp + -288], rax
  mov rax, [rbp + -176]
  add rax, 32
  mov [rbp + -296], rax
  mov rax, [rbp + -296]
  sub rax, [rbp + -288]
  mov [rbp + -304], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -288]
  mov r8d, dword ptr [rbp + -304]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -312], rax
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

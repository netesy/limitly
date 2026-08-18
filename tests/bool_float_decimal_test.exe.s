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
str_true:
  .string "true
"
.align 8
str_false:
  .string "false
"
.align 8
str_float_0:
  .string "3.14"
.align 8
nl:
  .string "
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
  sub rsp, 168
main_entry:
main_block_0:
  mov rax, 1
  cmp rax, 0
  setne al
  movzx eax, al
  mov [rbp + -64], rax
  mov rax, [rbp + -64]
  test rax, rax
  jne main_pb_true_1
  jmp main_pb_false_1
main_pb_true_1:
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_true]
  mov r8d, dword ptr 5
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -72], rax
  jmp main_pb_done_1
main_pb_false_1:
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_false]
  mov r8d, dword ptr 6
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -80], rax
  jmp main_pb_done_1
main_pb_done_1:
  mov rax, 0
  cmp rax, 0
  setne al
  movzx eax, al
  mov [rbp + -88], rax
  mov rax, [rbp + -88]
  test rax, rax
  jne main_pb_true_2
  jmp main_pb_false_2
main_pb_true_2:
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_true]
  mov r8d, dword ptr 5
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -96], rax
  jmp main_pb_done_2
main_pb_false_2:
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_false]
  mov r8d, dword ptr 6
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -104], rax
  jmp main_pb_done_2
main_pb_done_2:
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -112], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -112]
  mov [rdx], rax
  jmp main_ps_loop_3
main_ps_loop_3:
  mov rax, [rbp + -112]
  mov rax, [rax]
  mov [rbp + -120], rax
  lea rax, [rel str_float_0]
  add rax, [rbp + -120]
  mov [rbp + -128], rax
  mov rax, [rbp + -128]
  movzx rax, byte ptr [rax]
  mov [rbp + -136], rax
  mov rax, [rbp + -136]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -144], rax
  mov rax, [rbp + -120]
  add rax, 1
  mov [rbp + -152], rax
  mov rax, [rbp + -152]
  mov rdx, [rbp + -112]
  mov [rdx], rax
  mov rax, [rbp + -144]
  test rax, rax
  jne main_ps_done_3
  jmp main_ps_loop_3
main_ps_done_3:
  mov rax, [rbp + -112]
  mov rax, [rax]
  mov [rbp + -160], rax
  mov rax, [rbp + -160]
  sub rax, 1
  mov [rbp + -168], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_float_0]
  mov r8d, dword ptr [rbp + -168]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -176], rax
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
  mov [rbp + -184], rax
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

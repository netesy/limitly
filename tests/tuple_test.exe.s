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
  sub rsp, 376
main_entry:
main_block_0:
  mov rcx, 2
  call lm_tuple_new
  mov [rbp + -64], rax
  mov rcx, [rbp + -64]
  mov rdx, 0
  mov r8, 42
  call lm_tuple_set
  mov [rbp + -72], rax
  mov rcx, [rbp + -64]
  mov rdx, 1
  mov r8, 99
  call lm_tuple_set
  mov [rbp + -80], rax
  mov rcx, [rbp + -64]
  mov rdx, 0
  call lm_tuple_get
  mov [rbp + -88], rax
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -96], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -96]
  add rax, 31
  mov [rbp + -104], rax
  mov rax, 10
  mov rdx, [rbp + -104]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -112], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -120], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -104]
  mov rdx, [rbp + -120]
  mov [rdx], rax
  mov rax, [rbp + -88]
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -128], rax
  mov rax, [rbp + -128]
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
  mov [rbp + -136], rax
  mov rax, [rbp + -88]
  neg rax
  mov [rbp + -144], rax
  mov rax, [rbp + -144]
  mov rdx, [rbp + -112]
  mov [rdx], rax
  jmp main_pi_loop_1
main_pi_abs_1:
  mov rax, [rbp + -88]
  mov rdx, [rbp + -112]
  mov [rdx], rax
  jmp main_pi_loop_1
main_pi_loop_1:
  mov rax, [rbp + -112]
  mov rax, [rax]
  mov [rbp + -152], rax
  mov rax, [rbp + -152]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -160], rax
  mov rax, [rbp + -152]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -168], rdx
  mov rax, [rbp + -168]
  add rax, 48
  mov [rbp + -176], rax
  mov rax, [rbp + -120]
  mov rax, [rax]
  mov [rbp + -184], rax
  mov rax, [rbp + -184]
  sub rax, 1
  mov [rbp + -192], rax
  mov rax, [rbp + -176]
  mov rdx, [rbp + -192]
  mov byte ptr [rdx], al
  mov rax, [rbp + -160]
  mov rdx, [rbp + -112]
  mov [rdx], rax
  mov rax, [rbp + -192]
  mov rdx, [rbp + -120]
  mov [rdx], rax
  mov rax, [rbp + -160]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -200], rax
  mov rax, [rbp + -200]
  test rax, rax
  jne main_pi_loop_1
  jmp main_pi_emit_1
main_pi_emit_1:
  mov rax, [rbp + -120]
  mov rax, [rax]
  mov [rbp + -208], rax
  mov rax, [rbp + -96]
  add rax, 32
  mov [rbp + -216], rax
  mov rax, [rbp + -216]
  sub rax, [rbp + -208]
  mov [rbp + -224], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -208]
  mov r8d, dword ptr [rbp + -224]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -232], rax
  mov rcx, [rbp + -64]
  mov rdx, 1
  call lm_tuple_get
  mov [rbp + -240], rax
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -248], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -248]
  add rax, 31
  mov [rbp + -256], rax
  mov rax, 10
  mov rdx, [rbp + -256]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -264], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -272], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -256]
  mov rdx, [rbp + -272]
  mov [rdx], rax
  mov rax, [rbp + -240]
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -280], rax
  mov rax, [rbp + -280]
  test rax, rax
  jne main_pi_neg_2
  jmp main_pi_abs_2
main_pi_neg_2:
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
  mov [rbp + -288], rax
  mov rax, [rbp + -240]
  neg rax
  mov [rbp + -296], rax
  mov rax, [rbp + -296]
  mov rdx, [rbp + -264]
  mov [rdx], rax
  jmp main_pi_loop_2
main_pi_abs_2:
  mov rax, [rbp + -240]
  mov rdx, [rbp + -264]
  mov [rdx], rax
  jmp main_pi_loop_2
main_pi_loop_2:
  mov rax, [rbp + -264]
  mov rax, [rax]
  mov [rbp + -304], rax
  mov rax, [rbp + -304]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -312], rax
  mov rax, [rbp + -304]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -320], rdx
  mov rax, [rbp + -320]
  add rax, 48
  mov [rbp + -328], rax
  mov rax, [rbp + -272]
  mov rax, [rax]
  mov [rbp + -336], rax
  mov rax, [rbp + -336]
  sub rax, 1
  mov [rbp + -344], rax
  mov rax, [rbp + -328]
  mov rdx, [rbp + -344]
  mov byte ptr [rdx], al
  mov rax, [rbp + -312]
  mov rdx, [rbp + -264]
  mov [rdx], rax
  mov rax, [rbp + -344]
  mov rdx, [rbp + -272]
  mov [rdx], rax
  mov rax, [rbp + -312]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -352], rax
  mov rax, [rbp + -352]
  test rax, rax
  jne main_pi_loop_2
  jmp main_pi_emit_2
main_pi_emit_2:
  mov rax, [rbp + -272]
  mov rax, [rax]
  mov [rbp + -360], rax
  mov rax, [rbp + -248]
  add rax, 32
  mov [rbp + -368], rax
  mov rax, [rbp + -368]
  sub rax, [rbp + -360]
  mov [rbp + -376], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -360]
  mov r8d, dword ptr [rbp + -376]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -384], rax
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

.globl lm_tuple_new
lm_tuple_new:
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
lm_tuple_new_entry:
  mov rax, [rbp + -64]
  add rax, 1
  mov [rbp + -72], rax
  mov rax, [rbp + -72]
  imul rax, 8
  mov [rbp + -80], rax
  sub rsp, 48
  mov rcx, 0
  mov rdx, [rbp + -80]
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -88], rax
  add rsp, 48
  mov [rbp + -88], rax
  mov rax, [rbp + -64]
  mov rdx, [rbp + -88]
  mov [rdx], rax
  mov rax, [rbp + -88]
  jmp lm_tuple_new_epilogue
lm_tuple_new_epilogue:
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
.Lfunc_end_lm_tuple_new:

.globl lm_tuple_set
lm_tuple_set:
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
lm_tuple_set_entry:
  mov rax, [rbp + -72]
  add rax, 1
  mov [rbp + -88], rax
  mov rax, [rbp + -88]
  imul rax, 8
  mov [rbp + -96], rax
  mov rax, [rbp + -64]
  add rax, [rbp + -96]
  mov [rbp + -104], rax
  mov rax, [rbp + -80]
  mov rdx, [rbp + -104]
  mov [rdx], rax
  mov rax, 0
  jmp lm_tuple_set_epilogue
lm_tuple_set_epilogue:
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
.Lfunc_end_lm_tuple_set:

.globl lm_tuple_get
lm_tuple_get:
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
lm_tuple_get_entry:
  mov rax, [rbp + -72]
  add rax, 1
  mov [rbp + -80], rax
  mov rax, [rbp + -80]
  imul rax, 8
  mov [rbp + -88], rax
  mov rax, [rbp + -64]
  add rax, [rbp + -88]
  mov [rbp + -96], rax
  mov rax, [rbp + -96]
  mov rax, [rax]
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  jmp lm_tuple_get_epilogue
lm_tuple_get_epilogue:
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
.Lfunc_end_lm_tuple_get:

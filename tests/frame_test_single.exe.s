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
  .string "P.x: "
.align 8
nl:
  .string "
"
.align 8
str_minus:
  .string "-"
.align 8
str_const_1:
  .string "P.x after set: "
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
  sub rsp, 552
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
  mov rax, [rbp + -64]
  add rax, 0
  mov [rbp + -80], rax
  mov rax, 10
  mov rdx, [rbp + -80]
  mov [rdx], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -88]
  mov [rdx], rax
  jmp main_ps_loop_1
main_ps_loop_1:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -96], rax
  lea rax, [rel str_const_0]
  add rax, [rbp + -96]
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  movzx rax, byte ptr [rax]
  mov [rbp + -112], rax
  mov rax, [rbp + -112]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -120], rax
  mov rax, [rbp + -96]
  add rax, 1
  mov [rbp + -128], rax
  mov rax, [rbp + -128]
  mov rdx, [rbp + -88]
  mov [rdx], rax
  mov rax, [rbp + -120]
  test rax, rax
  jne main_ps_done_1
  jmp main_ps_loop_1
main_ps_done_1:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -136], rax
  mov rax, [rbp + -136]
  sub rax, 1
  mov [rbp + -144], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_0]
  mov r8d, dword ptr [rbp + -144]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -152], rax
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
  mov [rbp + -160], rax
  mov rax, [rbp + -64]
  add rax, 0
  mov [rbp + -168], rax
  mov rax, [rbp + -168]
  mov rax, [rax]
  mov [rbp + -176], rax
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -184], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -184]
  add rax, 31
  mov [rbp + -192], rax
  mov rax, 10
  mov rdx, [rbp + -192]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -200], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -208], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -192]
  mov rdx, [rbp + -208]
  mov [rdx], rax
  mov rax, [rbp + -176]
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -216], rax
  mov rax, [rbp + -216]
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
  mov [rbp + -224], rax
  mov rax, [rbp + -176]
  neg rax
  mov [rbp + -232], rax
  mov rax, [rbp + -232]
  mov rdx, [rbp + -200]
  mov [rdx], rax
  jmp main_pi_loop_1
main_pi_abs_1:
  mov rax, [rbp + -176]
  mov rdx, [rbp + -200]
  mov [rdx], rax
  jmp main_pi_loop_1
main_pi_loop_1:
  mov rax, [rbp + -200]
  mov rax, [rax]
  mov [rbp + -240], rax
  mov rax, [rbp + -240]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -248], rax
  mov rax, [rbp + -240]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -256], rdx
  mov rax, [rbp + -256]
  add rax, 48
  mov [rbp + -264], rax
  mov rax, [rbp + -208]
  mov rax, [rax]
  mov [rbp + -272], rax
  mov rax, [rbp + -272]
  sub rax, 1
  mov [rbp + -280], rax
  mov rax, [rbp + -264]
  mov rdx, [rbp + -280]
  mov byte ptr [rdx], al
  mov rax, [rbp + -248]
  mov rdx, [rbp + -200]
  mov [rdx], rax
  mov rax, [rbp + -280]
  mov rdx, [rbp + -208]
  mov [rdx], rax
  mov rax, [rbp + -248]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -288], rax
  mov rax, [rbp + -288]
  test rax, rax
  jne main_pi_loop_1
  jmp main_pi_emit_1
main_pi_emit_1:
  mov rax, [rbp + -208]
  mov rax, [rax]
  mov [rbp + -296], rax
  mov rax, [rbp + -184]
  add rax, 32
  mov [rbp + -304], rax
  mov rax, [rbp + -304]
  sub rax, [rbp + -296]
  mov [rbp + -312], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -296]
  mov r8d, dword ptr [rbp + -312]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -320], rax
  mov rax, [rbp + -64]
  add rax, 0
  mov [rbp + -328], rax
  mov rax, [rbp + -64]
  mov rdx, [rbp + -328]
  mov [rdx], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -336], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -336]
  mov [rdx], rax
  jmp main_ps_loop_2
main_ps_loop_2:
  mov rax, [rbp + -336]
  mov rax, [rax]
  mov [rbp + -344], rax
  lea rax, [rel str_const_1]
  add rax, [rbp + -344]
  mov [rbp + -352], rax
  mov rax, [rbp + -352]
  movzx rax, byte ptr [rax]
  mov [rbp + -360], rax
  mov rax, [rbp + -360]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -368], rax
  mov rax, [rbp + -344]
  add rax, 1
  mov [rbp + -376], rax
  mov rax, [rbp + -376]
  mov rdx, [rbp + -336]
  mov [rdx], rax
  mov rax, [rbp + -368]
  test rax, rax
  jne main_ps_done_2
  jmp main_ps_loop_2
main_ps_done_2:
  mov rax, [rbp + -336]
  mov rax, [rax]
  mov [rbp + -384], rax
  mov rax, [rbp + -384]
  sub rax, 1
  mov [rbp + -392], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_1]
  mov r8d, dword ptr [rbp + -392]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -400], rax
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
  mov [rbp + -408], rax
  mov rax, [rbp + -64]
  add rax, 0
  mov [rbp + -416], rax
  mov rax, [rbp + -416]
  mov rax, [rax]
  mov [rbp + -424], rax
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -432], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -432]
  add rax, 31
  mov [rbp + -440], rax
  mov rax, 10
  mov rdx, [rbp + -440]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -448], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -456], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -440]
  mov rdx, [rbp + -456]
  mov [rdx], rax
  mov rax, [rbp + -424]
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -464], rax
  mov rax, [rbp + -464]
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
  mov [rbp + -472], rax
  mov rax, [rbp + -424]
  neg rax
  mov [rbp + -480], rax
  mov rax, [rbp + -480]
  mov rdx, [rbp + -448]
  mov [rdx], rax
  jmp main_pi_loop_2
main_pi_abs_2:
  mov rax, [rbp + -424]
  mov rdx, [rbp + -448]
  mov [rdx], rax
  jmp main_pi_loop_2
main_pi_loop_2:
  mov rax, [rbp + -448]
  mov rax, [rax]
  mov [rbp + -488], rax
  mov rax, [rbp + -488]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -496], rax
  mov rax, [rbp + -488]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -504], rdx
  mov rax, [rbp + -504]
  add rax, 48
  mov [rbp + -512], rax
  mov rax, [rbp + -456]
  mov rax, [rax]
  mov [rbp + -520], rax
  mov rax, [rbp + -520]
  sub rax, 1
  mov [rbp + -528], rax
  mov rax, [rbp + -512]
  mov rdx, [rbp + -528]
  mov byte ptr [rdx], al
  mov rax, [rbp + -496]
  mov rdx, [rbp + -448]
  mov [rdx], rax
  mov rax, [rbp + -528]
  mov rdx, [rbp + -456]
  mov [rdx], rax
  mov rax, [rbp + -496]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -536], rax
  mov rax, [rbp + -536]
  test rax, rax
  jne main_pi_loop_2
  jmp main_pi_emit_2
main_pi_emit_2:
  mov rax, [rbp + -456]
  mov rax, [rax]
  mov [rbp + -544], rax
  mov rax, [rbp + -432]
  add rax, 32
  mov [rbp + -552], rax
  mov rax, [rbp + -552]
  sub rax, [rbp + -544]
  mov [rbp + -560], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -544]
  mov r8d, dword ptr [rbp + -560]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -568], rax
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

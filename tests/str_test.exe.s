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
  .string "world"
.align 8
str_const_1:
  .string "hello "
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
  sub rsp, 136
main_entry:
main_block_0:
  lea rcx, [rel str_const_1]
  lea rdx, [rel str_const_0]
  call lm_str_concat
  mov [rbp + -64], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -72]
  mov [rdx], rax
  jmp main_ps_loop_1
main_ps_loop_1:
  mov rax, [rbp + -72]
  mov rax, [rax]
  mov [rbp + -80], rax
  mov rax, [rbp + -64]
  add rax, [rbp + -80]
  mov [rbp + -88], rax
  mov rax, [rbp + -88]
  movzx rax, byte ptr [rax]
  mov [rbp + -96], rax
  mov rax, [rbp + -96]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -104], rax
  mov rax, [rbp + -80]
  add rax, 1
  mov [rbp + -112], rax
  mov rax, [rbp + -112]
  mov rdx, [rbp + -72]
  mov [rdx], rax
  mov rax, [rbp + -104]
  test rax, rax
  jne main_ps_done_1
  jmp main_ps_loop_1
main_ps_done_1:
  mov rax, [rbp + -72]
  mov rax, [rax]
  mov [rbp + -120], rax
  mov rax, [rbp + -120]
  sub rax, 1
  mov [rbp + -128], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -64]
  mov r8d, dword ptr [rbp + -128]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -136], rax
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
  mov [rbp + -144], rax
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

.globl lm_str_concat
lm_str_concat:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 408
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
lm_str_concat_entry:
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
  mov rax, 0
  mov rdx, [rbp + -80]
  mov [rdx], rax
  mov rax, 0
  mov rdx, [rbp + -88]
  mov [rdx], rax
  jmp lm_str_concat_l1
lm_str_concat_l1:
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -96], rax
  mov rax, [rbp + -64]
  add rax, [rbp + -96]
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  movzx rax, byte ptr [rax]
  mov [rbp + -112], rax
  mov rax, [rbp + -96]
  add rax, 1
  mov [rbp + -120], rax
  mov rax, [rbp + -120]
  mov rdx, [rbp + -80]
  mov [rdx], rax
  mov rax, [rbp + -112]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -128], rax
  mov rax, [rbp + -128]
  test rax, rax
  jne lm_str_concat_l1d
  jmp lm_str_concat_l1
lm_str_concat_l1d:
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -136], rax
  mov rax, [rbp + -136]
  sub rax, 1
  mov [rbp + -144], rax
  mov rax, [rbp + -144]
  mov rdx, [rbp + -80]
  mov [rdx], rax
  jmp lm_str_concat_l2
lm_str_concat_l2:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -152], rax
  mov rax, [rbp + -72]
  add rax, [rbp + -152]
  mov [rbp + -160], rax
  mov rax, [rbp + -160]
  movzx rax, byte ptr [rax]
  mov [rbp + -168], rax
  mov rax, [rbp + -152]
  add rax, 1
  mov [rbp + -176], rax
  mov rax, [rbp + -176]
  mov rdx, [rbp + -88]
  mov [rdx], rax
  mov rax, [rbp + -168]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -184], rax
  mov rax, [rbp + -184]
  test rax, rax
  jne lm_str_concat_l2d
  jmp lm_str_concat_l2
lm_str_concat_l2d:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -192], rax
  mov rax, [rbp + -192]
  sub rax, 1
  mov [rbp + -200], rax
  mov rax, [rbp + -200]
  mov rdx, [rbp + -88]
  mov [rdx], rax
  jmp lm_str_concat_alloc
lm_str_concat_alloc:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -208], rax
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -216], rax
  mov rax, [rbp + -216]
  add rax, [rbp + -208]
  mov [rbp + -224], rax
  mov rax, [rbp + -224]
  add rax, 1
  mov [rbp + -232], rax
  sub rsp, 48
  mov rcx, 0
  mov rdx, [rbp + -232]
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -240], rax
  add rsp, 48
  mov [rbp + -240], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -248], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -248]
  mov [rdx], rax
  jmp lm_str_concat_c1c
lm_str_concat_c1c:
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -256], rax
  mov rax, [rbp + -248]
  mov rax, [rax]
  mov [rbp + -264], rax
  mov rax, [rbp + -264]
  cmp rax, [rbp + -256]
  sete al
  movzx eax, al
  mov [rbp + -272], rax
  mov rax, [rbp + -272]
  test rax, rax
  jne lm_str_concat_c2i
  jmp lm_str_concat_c1a
lm_str_concat_c1a:
  mov rax, [rbp + -248]
  mov rax, [rax]
  mov [rbp + -280], rax
  mov rax, [rbp + -240]
  add rax, [rbp + -280]
  mov [rbp + -288], rax
  mov rax, [rbp + -64]
  add rax, [rbp + -280]
  mov [rbp + -296], rax
  mov rax, [rbp + -296]
  movzx rax, byte ptr [rax]
  mov [rbp + -304], rax
  mov rax, [rbp + -304]
  mov rdx, [rbp + -288]
  mov byte ptr [rdx], al
  mov rax, [rbp + -280]
  add rax, 1
  mov [rbp + -312], rax
  mov rax, [rbp + -312]
  mov rdx, [rbp + -248]
  mov [rdx], rax
  jmp lm_str_concat_c1c
lm_str_concat_c2i:
  mov rax, 0
  mov rdx, [rbp + -248]
  mov [rdx], rax
  jmp lm_str_concat_c2c
lm_str_concat_c2c:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -320], rax
  mov rax, [rbp + -248]
  mov rax, [rax]
  mov [rbp + -328], rax
  mov rax, [rbp + -328]
  cmp rax, [rbp + -320]
  sete al
  movzx eax, al
  mov [rbp + -336], rax
  mov rax, [rbp + -336]
  test rax, rax
  jne lm_str_concat_done
  jmp lm_str_concat_c2a
lm_str_concat_c2a:
  mov rax, [rbp + -248]
  mov rax, [rax]
  mov [rbp + -344], rax
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -352], rax
  mov rax, [rbp + -352]
  add rax, [rbp + -344]
  mov [rbp + -360], rax
  mov rax, [rbp + -240]
  add rax, [rbp + -360]
  mov [rbp + -368], rax
  mov rax, [rbp + -72]
  add rax, [rbp + -344]
  mov [rbp + -376], rax
  mov rax, [rbp + -376]
  movzx rax, byte ptr [rax]
  mov [rbp + -384], rax
  mov rax, [rbp + -384]
  mov rdx, [rbp + -368]
  mov byte ptr [rdx], al
  mov rax, [rbp + -344]
  add rax, 1
  mov [rbp + -392], rax
  mov rax, [rbp + -392]
  mov rdx, [rbp + -248]
  mov [rdx], rax
  jmp lm_str_concat_c2c
lm_str_concat_done:
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -400], rax
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -408], rax
  mov rax, [rbp + -408]
  add rax, [rbp + -400]
  mov [rbp + -416], rax
  mov rax, [rbp + -240]
  add rax, [rbp + -416]
  mov [rbp + -424], rax
  mov rax, 0
  mov rdx, [rbp + -424]
  mov byte ptr [rdx], al
  mov rax, [rbp + -240]
  jmp lm_str_concat_epilogue
lm_str_concat_epilogue:
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
.Lfunc_end_lm_str_concat:

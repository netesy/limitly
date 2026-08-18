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
  sub rsp, 232
main_entry:
main_block_0:
  mov rcx, 0
  call lm_list_new
  mov [rbp + -64], rax
  mov rcx, [rbp + -64]
  mov rdx, 10
  call lm_list_append
  mov [rbp + -72], rax
  mov rcx, [rbp + -64]
  mov rdx, 20
  call lm_list_append
  mov [rbp + -80], rax
  mov rcx, [rbp + -64]
  mov rdx, 30
  call lm_list_append
  mov [rbp + -88], rax
  mov rcx, [rbp + -64]
  mov rdx, 1
  call lm_list_get
  mov [rbp + -96], rax
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -104], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -104]
  add rax, 31
  mov [rbp + -112], rax
  mov rax, 10
  mov rdx, [rbp + -112]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -120], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -128], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -112]
  mov rdx, [rbp + -128]
  mov [rdx], rax
  mov rax, [rbp + -96]
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -136], rax
  mov rax, [rbp + -136]
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
  mov [rbp + -144], rax
  mov rax, [rbp + -96]
  neg rax
  mov [rbp + -152], rax
  mov rax, [rbp + -152]
  mov rdx, [rbp + -120]
  mov [rdx], rax
  jmp main_pi_loop_1
main_pi_abs_1:
  mov rax, [rbp + -96]
  mov rdx, [rbp + -120]
  mov [rdx], rax
  jmp main_pi_loop_1
main_pi_loop_1:
  mov rax, [rbp + -120]
  mov rax, [rax]
  mov [rbp + -160], rax
  mov rax, [rbp + -160]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -168], rax
  mov rax, [rbp + -160]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -176], rdx
  mov rax, [rbp + -176]
  add rax, 48
  mov [rbp + -184], rax
  mov rax, [rbp + -128]
  mov rax, [rax]
  mov [rbp + -192], rax
  mov rax, [rbp + -192]
  sub rax, 1
  mov [rbp + -200], rax
  mov rax, [rbp + -184]
  mov rdx, [rbp + -200]
  mov byte ptr [rdx], al
  mov rax, [rbp + -168]
  mov rdx, [rbp + -120]
  mov [rdx], rax
  mov rax, [rbp + -200]
  mov rdx, [rbp + -128]
  mov [rdx], rax
  mov rax, [rbp + -168]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -208], rax
  mov rax, [rbp + -208]
  test rax, rax
  jne main_pi_loop_1
  jmp main_pi_emit_1
main_pi_emit_1:
  mov rax, [rbp + -128]
  mov rax, [rax]
  mov [rbp + -216], rax
  mov rax, [rbp + -104]
  add rax, 32
  mov [rbp + -224], rax
  mov rax, [rbp + -224]
  sub rax, [rbp + -216]
  mov [rbp + -232], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -216]
  mov r8d, dword ptr [rbp + -232]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -240], rax
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

.globl lm_list_new
lm_list_new:
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
lm_list_new_entry:
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -64]
  mov rdx, [rbp + -72]
  mov [rdx], rax
  mov rax, [rbp + -64]
  cmp rax, 0
  setle al
  movzx eax, al
  mov [rbp + -80], rax
  mov rax, [rbp + -80]
  test rax, rax
  jne lm_list_new_def_cap
  jmp lm_list_new_alloc
lm_list_new_def_cap:
  mov rax, 8
  mov rdx, [rbp + -72]
  mov [rdx], rax
  jmp lm_list_new_alloc
lm_list_new_alloc:
  mov rax, [rbp + -72]
  mov rax, [rax]
  mov [rbp + -88], rax
  sub rsp, 48
  mov rcx, 0
  mov rdx, 24
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -96], rax
  add rsp, 48
  mov [rbp + -96], rax
  mov rax, [rbp + -88]
  imul rax, 8
  mov [rbp + -104], rax
  sub rsp, 48
  mov rcx, 0
  mov rdx, [rbp + -104]
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -112], rax
  add rsp, 48
  mov [rbp + -112], rax
  mov rax, 0
  mov rdx, [rbp + -96]
  mov [rdx], rax
  mov rax, [rbp + -96]
  add rax, 8
  mov [rbp + -120], rax
  mov rax, [rbp + -88]
  mov rdx, [rbp + -120]
  mov [rdx], rax
  mov rax, [rbp + -96]
  add rax, 16
  mov [rbp + -128], rax
  mov rax, [rbp + -112]
  mov rdx, [rbp + -128]
  mov [rdx], rax
  mov rax, [rbp + -96]
  jmp lm_list_new_epilogue
lm_list_new_epilogue:
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
.Lfunc_end_lm_list_new:

.globl lm_list_append
lm_list_append:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 248
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
lm_list_append_entry:
  mov rax, [rbp + -64]
  mov rax, [rax]
  mov [rbp + -80], rax
  mov rax, [rbp + -64]
  add rax, 8
  mov [rbp + -88], rax
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -96], rax
  mov rax, [rbp + -80]
  cmp rax, [rbp + -96]
  setge al
  movzx eax, al
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  test rax, rax
  jne lm_list_append_realloc
  jmp lm_list_append_insert
lm_list_append_realloc:
  mov rax, [rbp + -96]
  imul rax, 2
  mov [rbp + -112], rax
  mov rax, [rbp + -112]
  imul rax, 8
  mov [rbp + -120], rax
  sub rsp, 48
  mov rcx, 0
  mov rdx, [rbp + -120]
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -128], rax
  add rsp, 48
  mov [rbp + -128], rax
  mov rax, [rbp + -64]
  add rax, 16
  mov [rbp + -136], rax
  mov rax, [rbp + -136]
  mov rax, [rax]
  mov [rbp + -144], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -152], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -152]
  mov [rdx], rax
  jmp lm_list_append_copy_loop
lm_list_append_copy_loop:
  mov rax, [rbp + -152]
  mov rax, [rax]
  mov [rbp + -160], rax
  mov rax, [rbp + -160]
  cmp rax, [rbp + -80]
  setl al
  movzx eax, al
  mov [rbp + -168], rax
  mov rax, [rbp + -168]
  test rax, rax
  jne lm_list_append_copy_body
  jmp lm_list_append_copy_done
lm_list_append_copy_body:
  mov rax, [rbp + -160]
  imul rax, 8
  mov [rbp + -176], rax
  mov rax, [rbp + -144]
  add rax, [rbp + -176]
  mov [rbp + -184], rax
  mov rax, [rbp + -184]
  mov rax, [rax]
  mov [rbp + -192], rax
  mov rax, [rbp + -128]
  add rax, [rbp + -176]
  mov [rbp + -200], rax
  mov rax, [rbp + -192]
  mov rdx, [rbp + -200]
  mov [rdx], rax
  mov rax, [rbp + -160]
  add rax, 1
  mov [rbp + -208], rax
  mov rax, [rbp + -208]
  mov rdx, [rbp + -152]
  mov [rdx], rax
  jmp lm_list_append_copy_loop
lm_list_append_copy_done:
  mov rax, [rbp + -112]
  mov rdx, [rbp + -88]
  mov [rdx], rax
  mov rax, [rbp + -128]
  mov rdx, [rbp + -136]
  mov [rdx], rax
  jmp lm_list_append_insert
lm_list_append_insert:
  mov rax, [rbp + -64]
  mov rax, [rax]
  mov [rbp + -216], rax
  mov rax, [rbp + -64]
  add rax, 16
  mov [rbp + -224], rax
  mov rax, [rbp + -224]
  mov rax, [rax]
  mov [rbp + -232], rax
  mov rax, [rbp + -216]
  imul rax, 8
  mov [rbp + -240], rax
  mov rax, [rbp + -232]
  add rax, [rbp + -240]
  mov [rbp + -248], rax
  mov rax, [rbp + -72]
  mov rdx, [rbp + -248]
  mov [rdx], rax
  mov rax, [rbp + -216]
  add rax, 1
  mov [rbp + -256], rax
  mov rax, [rbp + -256]
  mov rdx, [rbp + -64]
  mov [rdx], rax
  mov rax, 0
  jmp lm_list_append_epilogue
lm_list_append_epilogue:
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
.Lfunc_end_lm_list_append:

.globl lm_list_get
lm_list_get:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 104
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
lm_list_get_entry:
  mov rax, [rbp + -64]
  add rax, 16
  mov [rbp + -80], rax
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -88], rax
  mov rax, [rbp + -72]
  imul rax, 8
  mov [rbp + -96], rax
  mov rax, [rbp + -88]
  add rax, [rbp + -96]
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  mov rax, [rax]
  mov [rbp + -112], rax
  mov rax, [rbp + -112]
  jmp lm_list_get_epilogue
lm_list_get_epilogue:
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
.Lfunc_end_lm_list_get:

.globl lm_list_len
lm_list_len:
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
lm_list_len_entry:
  mov rax, [rbp + -64]
  mov rax, [rax]
  mov [rbp + -72], rax
  mov rax, [rbp + -72]
  jmp lm_list_len_epilogue
lm_list_len_epilogue:
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
.Lfunc_end_lm_list_len:

.globl lm_list_set
lm_list_set:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 104
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
lm_list_set_entry:
  mov rax, [rbp + -64]
  add rax, 16
  mov [rbp + -88], rax
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -96], rax
  mov rax, [rbp + -72]
  imul rax, 8
  mov [rbp + -104], rax
  mov rax, [rbp + -96]
  add rax, [rbp + -104]
  mov [rbp + -112], rax
  mov rax, [rbp + -80]
  mov rdx, [rbp + -112]
  mov [rdx], rax
  mov rax, 0
  jmp lm_list_set_epilogue
lm_list_set_epilogue:
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
.Lfunc_end_lm_list_set:

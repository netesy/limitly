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
  .string "a"
.align 8
str_const_1:
  .string "b"
.align 8
str_const_2:
  .string "a"
.align 8
str_minus:
  .string "-"
.align 8
str_const_3:
  .string "b"
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
  call lm_dict_new
  mov [rbp + -64], rax
  mov rcx, [rbp + -64]
  lea rdx, [rel str_const_0]
  mov r8, 100
  call lm_dict_set
  mov [rbp + -72], rax
  mov rcx, [rbp + -64]
  lea rdx, [rel str_const_1]
  mov r8, 200
  call lm_dict_set
  mov [rbp + -80], rax
  mov rcx, [rbp + -64]
  lea rdx, [rel str_const_2]
  call lm_dict_get
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
  lea rdx, [rel str_const_3]
  call lm_dict_get
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

.globl lm_dict_new
lm_dict_new:
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
lm_dict_new_entry:
  sub rsp, 48
  mov rcx, 0
  mov rdx, 32
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -64], rax
  add rsp, 48
  mov [rbp + -64], rax
  sub rsp, 48
  mov rcx, 0
  mov rdx, 256
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -72], rax
  add rsp, 48
  mov [rbp + -72], rax
  sub rsp, 48
  mov rcx, 0
  mov rdx, 256
  mov r8d, 12288
  mov r9d, 4
  call VirtualAlloc
  mov [rbp + -80], rax
  add rsp, 48
  mov [rbp + -80], rax
  mov rax, 0
  mov rdx, [rbp + -64]
  mov [rdx], rax
  mov rax, [rbp + -64]
  add rax, 8
  mov [rbp + -88], rax
  mov rax, 32
  mov rdx, [rbp + -88]
  mov [rdx], rax
  mov rax, [rbp + -64]
  add rax, 16
  mov [rbp + -96], rax
  mov rax, [rbp + -72]
  mov rdx, [rbp + -96]
  mov [rdx], rax
  mov rax, [rbp + -64]
  add rax, 24
  mov [rbp + -104], rax
  mov rax, [rbp + -80]
  mov rdx, [rbp + -104]
  mov [rdx], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -112], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -112]
  mov [rdx], rax
  jmp lm_dict_new_init_loop
lm_dict_new_init_loop:
  mov rax, [rbp + -112]
  mov rax, [rax]
  mov [rbp + -120], rax
  mov rax, [rbp + -120]
  cmp rax, 32
  setl al
  movzx eax, al
  mov [rbp + -128], rax
  mov rax, [rbp + -128]
  test rax, rax
  jne lm_dict_new_init_body
  jmp lm_dict_new_init_done
lm_dict_new_init_body:
  mov rax, [rbp + -120]
  imul rax, 8
  mov [rbp + -136], rax
  mov rax, [rbp + -72]
  add rax, [rbp + -136]
  mov [rbp + -144], rax
  mov rax, 0
  mov rdx, [rbp + -144]
  mov [rdx], rax
  mov rax, [rbp + -120]
  add rax, 1
  mov [rbp + -152], rax
  mov rax, [rbp + -152]
  mov rdx, [rbp + -112]
  mov [rdx], rax
  jmp lm_dict_new_init_loop
lm_dict_new_init_done:
  mov rax, [rbp + -64]
  jmp lm_dict_new_epilogue
lm_dict_new_epilogue:
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
.Lfunc_end_lm_dict_new:

.globl lm_dict_set
lm_dict_set:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 200
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
lm_dict_set_entry:
  mov rax, [rbp + -64]
  add rax, 16
  mov [rbp + -88], rax
  mov rax, [rbp + -88]
  mov rax, [rax]
  mov [rbp + -96], rax
  mov rax, [rbp + -64]
  add rax, 24
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  mov rax, [rax]
  mov [rbp + -112], rax
  mov rax, [rbp + -64]
  add rax, 8
  mov [rbp + -120], rax
  mov rax, [rbp + -120]
  mov rax, [rax]
  mov [rbp + -128], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -136], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -136]
  mov [rdx], rax
  jmp lm_dict_set_loop
lm_dict_set_loop:
  mov rax, [rbp + -136]
  mov rax, [rax]
  mov [rbp + -144], rax
  mov rax, [rbp + -144]
  cmp rax, [rbp + -128]
  setl al
  movzx eax, al
  mov [rbp + -152], rax
  mov rax, [rbp + -152]
  test rax, rax
  jne lm_dict_set_check
  jmp lm_dict_set_done
lm_dict_set_check:
  mov rax, [rbp + -144]
  imul rax, 8
  mov [rbp + -160], rax
  mov rax, [rbp + -96]
  add rax, [rbp + -160]
  mov [rbp + -168], rax
  mov rax, [rbp + -168]
  mov rax, [rax]
  mov [rbp + -176], rax
  mov rcx, [rbp + -176]
  mov rdx, [rbp + -72]
  call lm_key_eq
  mov [rbp + -184], rax
  mov rax, [rbp + -176]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -192], rax
  mov rax, [rbp + -184]
  or rax, [rbp + -192]
  mov [rbp + -200], rax
  mov rax, [rbp + -200]
  test rax, rax
  jne lm_dict_set_store
  jmp lm_dict_set_next
lm_dict_set_store:
  mov rax, [rbp + -72]
  mov rdx, [rbp + -168]
  mov [rdx], rax
  mov rax, [rbp + -112]
  add rax, [rbp + -160]
  mov [rbp + -208], rax
  mov rax, [rbp + -80]
  mov rdx, [rbp + -208]
  mov [rdx], rax
  mov rax, 0
  jmp lm_dict_set_epilogue
lm_dict_set_next:
  mov rax, [rbp + -144]
  add rax, 1
  mov [rbp + -216], rax
  mov rax, [rbp + -216]
  mov rdx, [rbp + -136]
  mov [rdx], rax
  jmp lm_dict_set_loop
lm_dict_set_done:
  mov rax, 0
  jmp lm_dict_set_epilogue
lm_dict_set_epilogue:
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
.Lfunc_end_lm_dict_set:

.globl lm_dict_get
lm_dict_get:
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
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
lm_dict_get_entry:
  mov rax, [rbp + -64]
  add rax, 16
  mov [rbp + -80], rax
  mov rax, [rbp + -80]
  mov rax, [rax]
  mov [rbp + -88], rax
  mov rax, [rbp + -64]
  add rax, 24
  mov [rbp + -96], rax
  mov rax, [rbp + -96]
  mov rax, [rax]
  mov [rbp + -104], rax
  mov rax, [rbp + -64]
  add rax, 8
  mov [rbp + -112], rax
  mov rax, [rbp + -112]
  mov rax, [rax]
  mov [rbp + -120], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -128], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -128]
  mov [rdx], rax
  jmp lm_dict_get_loop
lm_dict_get_loop:
  mov rax, [rbp + -128]
  mov rax, [rax]
  mov [rbp + -136], rax
  mov rax, [rbp + -136]
  cmp rax, [rbp + -120]
  setl al
  movzx eax, al
  mov [rbp + -144], rax
  mov rax, [rbp + -144]
  test rax, rax
  jne lm_dict_get_check
  jmp lm_dict_get_not_found
lm_dict_get_check:
  mov rax, [rbp + -136]
  imul rax, 8
  mov [rbp + -152], rax
  mov rax, [rbp + -88]
  add rax, [rbp + -152]
  mov [rbp + -160], rax
  mov rax, [rbp + -160]
  mov rax, [rax]
  mov [rbp + -168], rax
  mov rcx, [rbp + -168]
  mov rdx, [rbp + -72]
  call lm_key_eq
  mov [rbp + -176], rax
  mov rax, [rbp + -176]
  test rax, rax
  jne lm_dict_get_found
  jmp lm_dict_get_next
lm_dict_get_found:
  mov rax, [rbp + -104]
  add rax, [rbp + -152]
  mov [rbp + -184], rax
  mov rax, [rbp + -184]
  mov rax, [rax]
  mov [rbp + -192], rax
  mov rax, [rbp + -192]
  jmp lm_dict_get_epilogue
lm_dict_get_next:
  mov rax, [rbp + -136]
  add rax, 1
  mov [rbp + -200], rax
  mov rax, [rbp + -200]
  mov rdx, [rbp + -128]
  mov [rdx], rax
  jmp lm_dict_get_loop
lm_dict_get_not_found:
  mov rax, 0
  jmp lm_dict_get_epilogue
lm_dict_get_epilogue:
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
.Lfunc_end_lm_dict_get:

.globl lm_key_eq
lm_key_eq:
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
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
lm_key_eq_entry:
  mov rax, [rbp + -64]
  cmp rax, [rbp + -72]
  sete al
  movzx eax, al
  mov [rbp + -80], rax
  mov rax, [rbp + -80]
  test rax, rax
  jne lm_key_eq_ret_true
  jmp lm_key_eq_ptrcmp
lm_key_eq_ptrcmp:
  mov rax, [rbp + -64]
  cmp rax, 65536
  setl al
  movzx eax, al
  mov [rbp + -88], rax
  mov rax, [rbp + -72]
  cmp rax, 65536
  setl al
  movzx eax, al
  mov [rbp + -96], rax
  mov rax, [rbp + -88]
  or rax, [rbp + -96]
  mov [rbp + -104], rax
  mov rax, [rbp + -104]
  test rax, rax
  jne lm_key_eq_ret_false
  jmp lm_key_eq_loop_init
lm_key_eq_loop_init:
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -112], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -112]
  mov [rdx], rax
  jmp lm_key_eq_loop_cond
lm_key_eq_loop_cond:
  mov rax, [rbp + -112]
  mov rax, [rax]
  mov [rbp + -120], rax
  mov rax, [rbp + -64]
  add rax, [rbp + -120]
  mov [rbp + -128], rax
  mov rax, [rbp + -72]
  add rax, [rbp + -120]
  mov [rbp + -136], rax
  mov rax, [rbp + -128]
  movzx rax, byte ptr [rax]
  mov [rbp + -144], rax
  mov rax, [rbp + -136]
  movzx rax, byte ptr [rax]
  mov [rbp + -152], rax
  mov rax, [rbp + -144]
  cmp rax, [rbp + -152]
  setne al
  movzx eax, al
  mov [rbp + -160], rax
  mov rax, [rbp + -160]
  test rax, rax
  jne lm_key_eq_ret_false
  jmp lm_key_eq_check_end
lm_key_eq_check_end:
  mov rax, [rbp + -144]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -168], rax
  mov rax, [rbp + -168]
  test rax, rax
  jne lm_key_eq_ret_true
  jmp lm_key_eq_advance
lm_key_eq_advance:
  mov rax, [rbp + -120]
  add rax, 1
  mov [rbp + -176], rax
  mov rax, [rbp + -176]
  mov rdx, [rbp + -112]
  mov [rdx], rax
  jmp lm_key_eq_loop_cond
lm_key_eq_ret_true:
  mov rax, 1
  jmp lm_key_eq_epilogue
lm_key_eq_ret_false:
  mov rax, 0
  jmp lm_key_eq_epilogue
lm_key_eq_epilogue:
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
.Lfunc_end_lm_key_eq:

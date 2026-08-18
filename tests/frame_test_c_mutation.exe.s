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
.align 8
str_const_0:
  .string "Method should mutate the original object"
.align 8
str_const_1:
  .string "Test C - Member Mutation: PASSED"
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
  sub rsp, 344
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
  call Foo.init
  mov [rbp + -80], rax
  mov rcx, [rbp + -72]
  call Foo.inc
  mov [rbp + -88], rax
  mov rax, [rbp + -72]
  add rax, 0
  mov [rbp + -96], rax
  mov rax, [rbp + -96]
  mov rax, [rax]
  mov [rbp + -104], rax
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -112], rax
  add rax, 32
  mov [rel heap_ptr], rax
  mov rax, [rbp + -112]
  add rax, 31
  mov [rbp + -120], rax
  mov rax, 10
  mov rdx, [rbp + -120]
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -128], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -136], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, [rbp + -120]
  mov rdx, [rbp + -136]
  mov [rdx], rax
  mov rax, [rbp + -104]
  cmp rax, 0
  setl al
  movzx eax, al
  mov [rbp + -144], rax
  mov rax, [rbp + -144]
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
  mov [rbp + -152], rax
  mov rax, [rbp + -104]
  neg rax
  mov [rbp + -160], rax
  mov rax, [rbp + -160]
  mov rdx, [rbp + -128]
  mov [rdx], rax
  jmp main_pi_loop_1
main_pi_abs_1:
  mov rax, [rbp + -104]
  mov rdx, [rbp + -128]
  mov [rdx], rax
  jmp main_pi_loop_1
main_pi_loop_1:
  mov rax, [rbp + -128]
  mov rax, [rax]
  mov [rbp + -168], rax
  mov rax, [rbp + -168]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -176], rax
  mov rax, [rbp + -168]
  cqo
  mov rcx, 10
  idiv rcx
  mov [rbp + -184], rdx
  mov rax, [rbp + -184]
  add rax, 48
  mov [rbp + -192], rax
  mov rax, [rbp + -136]
  mov rax, [rax]
  mov [rbp + -200], rax
  mov rax, [rbp + -200]
  sub rax, 1
  mov [rbp + -208], rax
  mov rax, [rbp + -192]
  mov rdx, [rbp + -208]
  mov byte ptr [rdx], al
  mov rax, [rbp + -176]
  mov rdx, [rbp + -128]
  mov [rdx], rax
  mov rax, [rbp + -208]
  mov rdx, [rbp + -136]
  mov [rdx], rax
  mov rax, [rbp + -176]
  cmp rax, 1
  setae al
  movzx eax, al
  mov [rbp + -216], rax
  mov rax, [rbp + -216]
  test rax, rax
  jne main_pi_loop_1
  jmp main_pi_emit_1
main_pi_emit_1:
  mov rax, [rbp + -136]
  mov rax, [rax]
  mov [rbp + -224], rax
  mov rax, [rbp + -112]
  add rax, 32
  mov [rbp + -232], rax
  mov rax, [rbp + -232]
  sub rax, [rbp + -224]
  mov [rbp + -240], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  mov rdx, [rbp + -224]
  mov r8d, dword ptr [rbp + -240]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -248], rax
  mov rax, [rbp + -72]
  add rax, 0
  mov [rbp + -256], rax
  mov rax, [rbp + -256]
  mov rax, [rax]
  mov [rbp + -264], rax
  mov rax, [rbp + -264]
  cmp rax, 1
  sete al
  movzx eax, al
  mov [rbp + -272], rax
  mov rcx, [rbp + -272]
  lea rdx, [rel str_const_0]
  call lm_assert
  mov [rbp + -280], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -288], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -288]
  mov [rdx], rax
  jmp main_ps_loop_1
main_ps_loop_1:
  mov rax, [rbp + -288]
  mov rax, [rax]
  mov [rbp + -296], rax
  lea rax, [rel str_const_1]
  add rax, [rbp + -296]
  mov [rbp + -304], rax
  mov rax, [rbp + -304]
  movzx rax, byte ptr [rax]
  mov [rbp + -312], rax
  mov rax, [rbp + -312]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -320], rax
  mov rax, [rbp + -296]
  add rax, 1
  mov [rbp + -328], rax
  mov rax, [rbp + -328]
  mov rdx, [rbp + -288]
  mov [rdx], rax
  mov rax, [rbp + -320]
  test rax, rax
  jne main_ps_done_1
  jmp main_ps_loop_1
main_ps_done_1:
  mov rax, [rbp + -288]
  mov rax, [rax]
  mov [rbp + -336], rax
  mov rax, [rbp + -336]
  sub rax, 1
  mov [rbp + -344], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_1]
  mov r8d, dword ptr [rbp + -344]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -352], rax
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
  mov [rbp + -360], rax
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

.globl Foo.init
Foo.init:
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
Foo.init_entry:
  mov rax, 0
  jmp Foo.init_epilogue
Foo.init_epilogue:
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
.Lfunc_end_Foo.init:

.globl Foo.inc
Foo.inc:
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
Foo.inc_entry:
  mov rax, 0
  jmp Foo.inc_epilogue
Foo.inc_epilogue:
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
.Lfunc_end_Foo.inc:

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

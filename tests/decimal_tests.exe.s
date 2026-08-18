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
  .string "Running decimal tests..."
.align 8
nl:
  .string "
"
.align 8
str_const_1:
  .string "Decimal tests passed!"
.align 8
str_const_2:
  .string "d2 + d4 should be 15.5000 (d4)"
.align 8
str_const_3:
  .string "d2 + d6 should be 10.250001 (d6)"
.align 8
str_const_4:
  .string "d2 + d2 should be 16.00"
.align 8
str_const_5:
  .string "d4 + d4 should be 2.0000"
.align 8
str_const_6:
  .string "10.0000 / 3.0000 should be 3.3333"
.align 8
str_const_7:
  .string "10.0000 % 3.0000 should be 1.0000"
.align 8
str_const_8:
  .string "10.25 == 10.25"
.align 8
str_const_9:
  .string "a as d4 == 10.2500"
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
  sub rsp, 248
main_entry:
main_block_0:
  call main
  mov [rbp + -64], rax
  mov rax, 0
  jmp main_epilogue
main_entry:
main_block_0:
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
  lea rax, [rel str_const_0]
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
  lea rdx, [rel str_const_0]
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
  call test_same_scale
  mov [rbp + -152], rax
  call test_mixed_scale
  mov [rbp + -160], rax
  call test_comparison
  mov [rbp + -168], rax
  call test_arithmetic
  mov [rbp + -176], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -184], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -184]
  mov [rdx], rax
  jmp main_ps_loop_2
main_ps_loop_2:
  mov rax, [rbp + -184]
  mov rax, [rax]
  mov [rbp + -192], rax
  lea rax, [rel str_const_1]
  add rax, [rbp + -192]
  mov [rbp + -200], rax
  mov rax, [rbp + -200]
  movzx rax, byte ptr [rax]
  mov [rbp + -208], rax
  mov rax, [rbp + -208]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -216], rax
  mov rax, [rbp + -192]
  add rax, 1
  mov [rbp + -224], rax
  mov rax, [rbp + -224]
  mov rdx, [rbp + -184]
  mov [rdx], rax
  mov rax, [rbp + -216]
  test rax, rax
  jne main_ps_done_2
  jmp main_ps_loop_2
main_ps_done_2:
  mov rax, [rbp + -184]
  mov rax, [rax]
  mov [rbp + -232], rax
  mov rax, [rbp + -232]
  sub rax, 1
  mov [rbp + -240], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_1]
  mov r8d, dword ptr [rbp + -240]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -248], rax
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
  mov [rbp + -256], rax
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

.globl test_mixed_scale
test_mixed_scale:
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
test_mixed_scale_entry:
test_mixed_scale_block_0:
  movq 2, rax
  movq rax, [rbp + -64]
  mov rax, 0
  cmp rax, 2
  sete al
  movzx eax, al
  mov [rbp + -72], rax
  mov rcx, [rbp + -72]
  lea rdx, [rel str_const_2]
  call lm_assert
  mov [rbp + -80], rax
  movq 2, rax
  movq rax, [rbp + -88]
  mov rax, 0
  cmp rax, 2
  sete al
  movzx eax, al
  mov [rbp + -96], rax
  mov rcx, [rbp + -96]
  lea rdx, [rel str_const_3]
  call lm_assert
  mov [rbp + -104], rax
  mov rax, 0
  jmp test_mixed_scale_epilogue
test_mixed_scale_epilogue:
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
.Lfunc_end_test_mixed_scale:

.globl test_narrowing_trap
test_narrowing_trap:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
test_narrowing_trap_entry:
test_narrowing_trap_block_0:
  mov rax, 0
  jmp test_narrowing_trap_epilogue
test_narrowing_trap_epilogue:
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
.Lfunc_end_test_narrowing_trap:

.globl test_same_scale
test_same_scale:
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
test_same_scale_entry:
test_same_scale_block_0:
  mov rax, 0
  cmp rax, 2
  sete al
  movzx eax, al
  mov [rbp + -64], rax
  mov rcx, [rbp + -64]
  lea rdx, [rel str_const_4]
  call lm_assert
  mov [rbp + -72], rax
  mov rax, 0
  cmp rax, 2
  sete al
  movzx eax, al
  mov [rbp + -80], rax
  mov rcx, [rbp + -80]
  lea rdx, [rel str_const_5]
  call lm_assert
  mov [rbp + -88], rax
  mov rax, 0
  jmp test_same_scale_epilogue
test_same_scale_epilogue:
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
.Lfunc_end_test_same_scale:

.globl test_arithmetic
test_arithmetic:
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
test_arithmetic_entry:
test_arithmetic_block_0:
  mov rax, 0
  cmp rax, 2
  sete al
  movzx eax, al
  mov [rbp + -64], rax
  mov rcx, [rbp + -64]
  lea rdx, [rel str_const_6]
  call lm_assert
  mov [rbp + -72], rax
  mov rax, 0
  cmp rax, 2
  sete al
  movzx eax, al
  mov [rbp + -80], rax
  mov rcx, [rbp + -80]
  lea rdx, [rel str_const_7]
  call lm_assert
  mov [rbp + -88], rax
  mov rax, 0
  jmp test_arithmetic_epilogue
test_arithmetic_epilogue:
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
.Lfunc_end_test_arithmetic:

.globl test_comparison
test_comparison:
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
test_comparison_entry:
test_comparison_block_0:
  mov rax, 2
  cmp rax, 2
  sete al
  movzx eax, al
  mov [rbp + -64], rax
  mov rcx, [rbp + -64]
  lea rdx, [rel str_const_8]
  call lm_assert
  mov [rbp + -72], rax
  movq 2, rax
  movq rax, [rbp + -80]
  mov rax, [rbp + -80]
  cmp rax, 2
  sete al
  movzx eax, al
  mov [rbp + -88], rax
  mov rcx, [rbp + -88]
  lea rdx, [rel str_const_9]
  call lm_assert
  mov [rbp + -96], rax
  mov rax, 0
  jmp test_comparison_epilogue
test_comparison_epilogue:
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
.Lfunc_end_test_comparison:

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

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
  .string "Value should persist across method calls"
.align 8
str_const_1:
  .string "Getter should return updated value"
.align 8
str_const_2:
  .string "Test D - Reference Identity: PASSED"
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
  sub rsp, 216
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
  mov rdx, 42
  call Foo.set
  mov [rbp + -88], rax
  mov rcx, [rbp + -72]
  call Foo.get
  mov [rbp + -96], rax
  mov rax, [rbp + -96]
  cmp rax, 42
  sete al
  movzx eax, al
  mov [rbp + -104], rax
  mov rcx, [rbp + -104]
  lea rdx, [rel str_const_0]
  call lm_assert
  mov [rbp + -112], rax
  mov rcx, [rbp + -72]
  mov rdx, 100
  call Foo.set
  mov [rbp + -120], rax
  mov rcx, [rbp + -72]
  call Foo.get
  mov [rbp + -128], rax
  mov rax, [rbp + -128]
  cmp rax, 100
  sete al
  movzx eax, al
  mov [rbp + -136], rax
  mov rcx, [rbp + -136]
  lea rdx, [rel str_const_1]
  call lm_assert
  mov [rbp + -144], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -152], rax
  add rax, 8
  mov [rel heap_ptr], rax
  mov rax, 0
  mov rdx, [rbp + -152]
  mov [rdx], rax
  jmp main_ps_loop_1
main_ps_loop_1:
  mov rax, [rbp + -152]
  mov rax, [rax]
  mov [rbp + -160], rax
  lea rax, [rel str_const_2]
  add rax, [rbp + -160]
  mov [rbp + -168], rax
  mov rax, [rbp + -168]
  movzx rax, byte ptr [rax]
  mov [rbp + -176], rax
  mov rax, [rbp + -176]
  cmp rax, 0
  sete al
  movzx eax, al
  mov [rbp + -184], rax
  mov rax, [rbp + -160]
  add rax, 1
  mov [rbp + -192], rax
  mov rax, [rbp + -192]
  mov rdx, [rbp + -152]
  mov [rdx], rax
  mov rax, [rbp + -184]
  test rax, rax
  jne main_ps_done_1
  jmp main_ps_loop_1
main_ps_done_1:
  mov rax, [rbp + -152]
  mov rax, [rax]
  mov [rbp + -200], rax
  mov rax, [rbp + -200]
  sub rax, 1
  mov [rbp + -208], rax
  sub rsp, 32
  mov ecx, 0xFFFFFFF5
  call GetStdHandle
  add rsp, 32
  sub rsp, 48
  mov rcx, rax
  lea rdx, [rel str_const_2]
  mov r8d, dword ptr [rbp + -208]
  lea r9, [rsp + 40]
  mov qword ptr [rsp + 32], 0
  call WriteFile
  add rsp, 48
  mov [rbp + -216], rax
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
  mov [rbp + -224], rax
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

.globl Foo.get
Foo.get:
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
Foo.get_entry:
  mov rax, 0
  jmp Foo.get_epilogue
Foo.get_epilogue:
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
.Lfunc_end_Foo.get:

.globl Foo.set
Foo.set:
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
  mov [rbp + -72], rdx
Foo.set_entry:
  mov rax, 0
  jmp Foo.set_epilogue
Foo.set_epilogue:
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
.Lfunc_end_Foo.set:

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

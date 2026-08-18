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
  .string "=== Alias Import Test ==="
.align 8
str_const_1:
  .string "Test 2.1: Access aliased module variable"
.align 8
str_const_2:
  .string "PI = %s"
.align 8
str_const_3:
  .string "Module alias should provide access to variables"
.align 8
str_const_4:
  .string "Test 2.2: Call aliased module function"
.align 8
str_const_5:
  .string "5 squared = %s"
.align 8
str_const_6:
  .string "Module alias should provide access to functions"
.align 8
str_const_7:
  .string "Test 2.3: Call complex aliased function"
.align 8
str_const_8:
  .string "Test 2.4: Call recursive function through alias"
.align 8
str_const_9:
  .string "5! = %s"
.align 8
str_const_10:
  .string "Module alias should provide access to recursive functions: 5! = 120"
.align 8
str_const_11:
  .string "=== Alias Import Test Complete ==="
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
  and %rsp, -16
  and rsp, -16
  subq $32, %rsp
  call main
  addq $32, %rsp
  mov rcx, rax
  subq $32, %rsp
  call ExitProcess
  addq $32, %rsp

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
  sub rsp, 408
main_entry:
main_block_0:
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  call tests.modules.math_module.__init__
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  addq $16, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  mov rax, [rax]
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  call lm_print_str
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  addq $16, rax
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  mov rax, [rax]
  movq rax, [rbp + -160]
  movq [rbp + -160], rcx
  call lm_print_str
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call lm_assert
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  addq $16, rax
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  mov rax, [rax]
  movq rax, [rbp + -208]
  movq [rbp + -208], rcx
  call lm_print_str
  movq $41, rcx
  call tests.modules.math_module.square
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -216], rcx
  movq $r17, rdx
  call lm_rt_str_format
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  addq $16, rax
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  mov rax, [rax]
  movq rax, [rbp + -248]
  movq [rbp + -248], rcx
  call lm_print_str
  movq $r17, rax
  cmpq $201, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -256], rcx
  movq [rbp + -264], rdx
  call lm_assert
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  addq $16, rax
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  movq rax, [rbp + -288]
  movq [rbp + -288], rax
  mov rax, [rax]
  movq rax, [rbp + -296]
  movq [rbp + -296], rcx
  call lm_print_str
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  addq $16, rax
  movq rax, [rbp + -312]
  movq [rbp + -312], rax
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  mov rax, [rax]
  movq rax, [rbp + -328]
  movq [rbp + -328], rcx
  call lm_print_str
  movq $41, rcx
  call tests.modules.math_module.factorial
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -336], rcx
  movq $r31, rdx
  call lm_rt_str_format
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  addq $16, rax
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  movq rax, [rbp + -360]
  movq [rbp + -360], rax
  mov rax, [rax]
  movq rax, [rbp + -368]
  movq [rbp + -368], rcx
  call lm_print_str
  movq $r31, rax
  cmpq $961, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -376]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -376], rcx
  movq [rbp + -384], rdx
  call lm_assert
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  addq $16, rax
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  movq rax, [rbp + -408]
  movq [rbp + -408], rax
  mov rax, [rax]
  movq rax, [rbp + -416]
  movq [rbp + -416], rcx
  call lm_print_str
  movq $0, rax
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

.globl tests.modules.math_module.is_prime
tests.modules.math_module.is_prime:
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
tests.modules.math_module.is_prime_entry:
tests.modules.math_module.is_prime_block_0:
  movq [rbp + -64], rax
  cmpq $9, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne tests.modules.math_module.is_prime_block_3
  jmp tests.modules.math_module.is_prime_block_5
tests.modules.math_module.is_prime_block_3:
  jmp tests.modules.math_module.is_prime_block_3
  movq $10, rax
  jmp tests.modules.math_module.is_prime_epilogue
tests.modules.math_module.is_prime_block_5:
  movq [rbp + -64], rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne tests.modules.math_module.is_prime_block_8
  jmp tests.modules.math_module.is_prime_block_10
tests.modules.math_module.is_prime_block_8:
  jmp tests.modules.math_module.is_prime_block_8
  movq $18, rax
  jmp tests.modules.math_module.is_prime_epilogue
tests.modules.math_module.is_prime_block_10:
  movq [rbp + -64], rcx
  call tests.modules.math_module.is_even
  movq $r9, rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne tests.modules.math_module.is_prime_block_14
  jmp tests.modules.math_module.is_prime_block_16
tests.modules.math_module.is_prime_block_14:
  jmp tests.modules.math_module.is_prime_block_14
  movq $10, rax
  jmp tests.modules.math_module.is_prime_epilogue
tests.modules.math_module.is_prime_block_16:
  jmp tests.modules.math_module.is_prime_block_18
tests.modules.math_module.is_prime_block_18:
  movq $25, rax
  imulq $25, rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  cmpq [rbp + -64], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne tests.modules.math_module.is_prime_block_21
  jmp tests.modules.math_module.is_prime_block_30
tests.modules.math_module.is_prime_block_21:
  jmp tests.modules.math_module.is_prime_block_21
  movq [rbp + -64], rax
  cqto
  movq $25, rcx
  idivq rcx
  movq rdx, [rbp + -112]
  movq [rbp + -112], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne tests.modules.math_module.is_prime_block_25
  jmp tests.modules.math_module.is_prime_block_27
tests.modules.math_module.is_prime_block_25:
  jmp tests.modules.math_module.is_prime_block_25
  movq $10, rax
  jmp tests.modules.math_module.is_prime_epilogue
tests.modules.math_module.is_prime_block_27:
  movq $25, rax
  addq $17, rax
  movq rax, [rbp + -128]
  jmp tests.modules.math_module.is_prime_block_18
tests.modules.math_module.is_prime_block_30:
  movq $18, rax
  jmp tests.modules.math_module.is_prime_epilogue
tests.modules.math_module.is_prime_epilogue:
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
.Lfunc_end_tests.modules.math_module.is_prime:

.globl tests.modules.math_module.is_odd
tests.modules.math_module.is_odd:
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
tests.modules.math_module.is_odd_entry:
tests.modules.math_module.is_odd_block_0:
  movq [rbp + -64], rcx
  call tests.modules.math_module.is_even
  movq $r1, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp tests.modules.math_module.is_odd_epilogue
tests.modules.math_module.is_odd_epilogue:
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
.Lfunc_end_tests.modules.math_module.is_odd:

.globl tests.modules.math_module.is_even
tests.modules.math_module.is_even:
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
tests.modules.math_module.is_even_entry:
tests.modules.math_module.is_even_block_0:
  movq [rbp + -64], rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rdx, [rbp + -72]
  movq [rbp + -72], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp tests.modules.math_module.is_even_epilogue
tests.modules.math_module.is_even_epilogue:
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
.Lfunc_end_tests.modules.math_module.is_even:

.globl tests.modules.math_module.subtract
tests.modules.math_module.subtract:
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
tests.modules.math_module.subtract_entry:
tests.modules.math_module.subtract_block_0:
  movq [rbp + -64], rax
  subq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp tests.modules.math_module.subtract_epilogue
tests.modules.math_module.subtract_epilogue:
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
.Lfunc_end_tests.modules.math_module.subtract:

.globl tests.modules.math_module.factorial
tests.modules.math_module.factorial:
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
tests.modules.math_module.factorial_entry:
tests.modules.math_module.factorial_block_0:
  movq [rbp + -64], rax
  cmpq $9, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne tests.modules.math_module.factorial_block_3
  jmp tests.modules.math_module.factorial_block_5
tests.modules.math_module.factorial_block_3:
  jmp tests.modules.math_module.factorial_block_3
  movq $9, rax
  jmp tests.modules.math_module.factorial_epilogue
tests.modules.math_module.factorial_block_5:
  movq [rbp + -64], rax
  subq $9, rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rcx
  call tests.modules.math_module.factorial
  movq [rbp + -64], rax
  imulq $r7, rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp tests.modules.math_module.factorial_epilogue
tests.modules.math_module.factorial_epilogue:
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
.Lfunc_end_tests.modules.math_module.factorial:

.globl tests.modules.math_module.cube
tests.modules.math_module.cube:
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
tests.modules.math_module.cube_entry:
tests.modules.math_module.cube_block_0:
  movq [rbp + -64], rax
  imulq [rbp + -64], rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  imulq [rbp + -64], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp tests.modules.math_module.cube_epilogue
tests.modules.math_module.cube_epilogue:
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
.Lfunc_end_tests.modules.math_module.cube:

.globl tests.modules.math_module.multiply
tests.modules.math_module.multiply:
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
tests.modules.math_module.multiply_entry:
tests.modules.math_module.multiply_block_0:
  movq [rbp + -64], rax
  imulq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp tests.modules.math_module.multiply_epilogue
tests.modules.math_module.multiply_epilogue:
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
.Lfunc_end_tests.modules.math_module.multiply:

.globl tests.modules.math_module.add
tests.modules.math_module.add:
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
tests.modules.math_module.add_entry:
tests.modules.math_module.add_block_0:
  movq [rbp + -64], rax
  addq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp tests.modules.math_module.add_epilogue
tests.modules.math_module.add_epilogue:
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
.Lfunc_end_tests.modules.math_module.add:

.globl tests.modules.math_module.__init__
tests.modules.math_module.__init__:
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
tests.modules.math_module.__init___entry:
  movq $0, rax
  jmp tests.modules.math_module.__init___epilogue
tests.modules.math_module.__init___epilogue:
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
.Lfunc_end_tests.modules.math_module.__init__:

.globl tests.modules.math_module.square
tests.modules.math_module.square:
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
tests.modules.math_module.square_entry:
tests.modules.math_module.square_block_0:
  movq [rbp + -64], rax
  imulq [rbp + -64], rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp tests.modules.math_module.square_epilogue
tests.modules.math_module.square_epilogue:
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
.Lfunc_end_tests.modules.math_module.square:

.globl lm_box_string
lm_box_string:
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
lm_box_string_entry:
  # Bump Allocation: 24 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 24
  mov [rel heap_ptr], rax
  movq $2, rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  addq $8, rax
  movq rax, [rbp + -80]
  movq $3, rax
  movq [rbp + -80], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  addq $16, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  jmp lm_box_string_epilogue
lm_box_string_epilogue:
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
.Lfunc_end_lm_box_string:

.globl lm_print_str
lm_print_str:
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
  mov [rbp + -64], rcx
lm_print_str_entry:
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 8
  mov [rel heap_ptr], rax
  movq $0, rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  jmp lm_print_str_loop
lm_print_str_loop:
  movq [rbp + -72], rax
  mov rax, [rax]
  movq rax, [rbp + -80]
  movq [rbp + -64], rax
  addq [rbp + -80], rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  cmpq $0, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -80], rax
  addq $1, rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  movq [rbp + -104], rax
  testq rax, rax
  jne lm_print_str_done
  jmp lm_print_str_loop
lm_print_str_done:
  movq [rbp + -72], rax
  mov rax, [rax]
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  subq $1, rax
  movq rax, [rbp + -128]
  subq $32, %rsp
  movq $1, rcx
  movq [rbp + -64], rdx
  movq [rbp + -128], r8
  call _write
  addq $32, %rsp
  subq $32, %rsp
  movq $1, rcx
  movq [rel nl], rdx
  movq $1, r8
  call _write
  addq $32, %rsp
  movq $0, rax
  jmp lm_print_str_epilogue
lm_print_str_epilogue:
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
.Lfunc_end_lm_print_str:

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
  movq [rbp + -64], rax
  testq rax, rax
  jne lm_assert_pass
  jmp lm_assert_fail
lm_assert_fail:
  subq $32, %rsp
  movq $1, rcx
  movq [rel assert_fail], rdx
  movq $17, r8
  call _write
  addq $32, %rsp
  movq $50397203, rax
  movq rax, [rbp + -88]
  movq $0, rax
  jmp lm_assert_epilogue
lm_assert_pass:
  movq $0, rax
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

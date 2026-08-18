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
  .string "Alice"
.align 8
str_const_1:
  .string "alice@example.com"
.align 8
str_const_2:
  .string "default"
.align 8
str_const_3:
  .string "Hello, Alice"
.align 8
str_const_4:
  .string "Frame method should work correctly"
.align 8
str_const_5:
  .string "Frame method should work: 10 + 20 = 30"
.align 8
str_const_6:
  .string "Frame default value should work"
.align 8
str_const_7:
  .string "Frame default value should work"
.align 8
str_const_8:
  .string "Frame method should work: 5 + 3 = 8"
.align 8
str_const_9:
  .string "Frame init should work correctly"
.align 8
str_minus:
  .string "-"
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
  sub rsp, 360
main_entry:
main_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  addq $0, rax
  movq rax, [rbp + -80]
  movq [rbp + -64], rax
  movq [rbp + -80], rdx
  mov [rdx], rax
  movq [rbp + -64], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -72], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -64], rax
  addq $0, rax
  movq rax, [rbp + -104]
  movq $241, rax
  movq [rbp + -104], rdx
  mov [rdx], rax
  movq [rbp + -64], rcx
  call Person.greet
  movq $r5, rax
  addq $16, rax
  movq rax, $
  movq $, rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  mov rax, [rax]
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  call lm_print_str
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -128], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -128], rcx
  movq $81, rdx
  movq $161, r8
  call Point.init
  movq [rbp + -128], rcx
  call Point.distance
  movq $r12, rcx
  call lm_print_int
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -136], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -136], rax
  addq $0, rax
  movq rax, [rbp + -144]
  movq [rbp + -64], rax
  movq [rbp + -144], rdx
  mov [rdx], rax
  movq [rbp + -136], rax
  addq $0, rax
  movq rax, [rbp + -152]
  movq [rbp + -72], rax
  movq [rbp + -152], rdx
  mov [rdx], rax
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -136], rax
  addq $0, rax
  movq rax, [rbp + -168]
  movq $241, rax
  movq [rbp + -168], rdx
  mov [rdx], rax
  movq [rbp + -136], rax
  addq $0, rax
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  mov rax, [rax]
  movq rax, [rbp + -184]
  movq [rbp + -184], rcx
  call lm_print_int
  movq [rbp + -136], rax
  addq $0, rax
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  mov rax, [rax]
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  call lm_print_int
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -208], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -208], rcx
  movq $41, rdx
  movq $25, r8
  call Calculator.add
  movq $r27, rcx
  call lm_print_int
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -216], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -216], rcx
  movq $985, rdx
  call Resource.init
  movq [rbp + -64], rcx
  call Person.greet
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq $r33, rax
  cmpq [rbp + -224], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rcx
  movq [rbp + -240], rdx
  call lm_assert
  movq [rbp + -128], rcx
  call Point.distance
  movq $r38, rax
  cmpq $241, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -248], rcx
  movq [rbp + -256], rdx
  call lm_assert
  movq [rbp + -136], rax
  addq $0, rax
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  mov rax, [rax]
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -280]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -280], rcx
  movq [rbp + -288], rdx
  call lm_assert
  movq [rbp + -136], rax
  addq $0, rax
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  mov rax, [rax]
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  cmpq $241, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -312]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -312], rcx
  movq [rbp + -320], rdx
  call lm_assert
  movq [rbp + -208], rcx
  movq $41, rdx
  movq $25, r8
  call Calculator.add
  movq $r55, rax
  cmpq $65, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -328]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -328], rcx
  movq [rbp + -336], rdx
  call lm_assert
  movq [rbp + -216], rax
  addq $0, rax
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  mov rax, [rax]
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  cmpq $985, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -360], rcx
  movq [rbp + -368], rdx
  call lm_assert
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

.globl Calculator.subtract
Calculator.subtract:
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
  mov [rbp + -80], r8
Calculator.subtract_entry:
  movq $0, rax
  jmp Calculator.subtract_epilogue
Calculator.subtract_epilogue:
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
.Lfunc_end_Calculator.subtract:

.globl Resource.deinit
Resource.deinit:
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
Resource.deinit_entry:
  movq $0, rax
  jmp Resource.deinit_epilogue
Resource.deinit_epilogue:
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
.Lfunc_end_Resource.deinit:

.globl Point.init
Point.init:
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
  mov [rbp + -80], r8
Point.init_entry:
  movq $0, rax
  jmp Point.init_epilogue
Point.init_epilogue:
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
.Lfunc_end_Point.init:

.globl Person.greet
Person.greet:
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
Person.greet_entry:
  movq $0, rax
  jmp Person.greet_epilogue
Person.greet_epilogue:
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
.Lfunc_end_Person.greet:

.globl Calculator.add
Calculator.add:
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
  mov [rbp + -80], r8
Calculator.add_entry:
  movq $0, rax
  jmp Calculator.add_epilogue
Calculator.add_epilogue:
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
.Lfunc_end_Calculator.add:

.globl BankAccount.deposit
BankAccount.deposit:
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
BankAccount.deposit_entry:
  movq $0, rax
  jmp BankAccount.deposit_epilogue
BankAccount.deposit_epilogue:
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
.Lfunc_end_BankAccount.deposit:

.globl Resource.init
Resource.init:
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
Resource.init_entry:
  movq $0, rax
  jmp Resource.init_epilogue
Resource.init_epilogue:
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
.Lfunc_end_Resource.init:

.globl Calculator.multiply
Calculator.multiply:
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
  mov [rbp + -80], r8
Calculator.multiply_entry:
  movq $0, rax
  jmp Calculator.multiply_epilogue
Calculator.multiply_epilogue:
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
.Lfunc_end_Calculator.multiply:

.globl Person.birthday
Person.birthday:
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
Person.birthday_entry:
  movq $0, rax
  jmp Person.birthday_epilogue
Person.birthday_epilogue:
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
.Lfunc_end_Person.birthday:

.globl BankAccount.calculateInterest
BankAccount.calculateInterest:
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
BankAccount.calculateInterest_entry:
  movq $0, rax
  jmp BankAccount.calculateInterest_epilogue
BankAccount.calculateInterest_epilogue:
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
.Lfunc_end_BankAccount.calculateInterest:

.globl Point.distance
Point.distance:
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
Point.distance_entry:
  movq $0, rax
  jmp Point.distance_epilogue
Point.distance_epilogue:
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
.Lfunc_end_Point.distance:

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

.globl lm_print_int
lm_print_int:
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
lm_print_int_entry:
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 32
  mov [rel heap_ptr], rax
  movq [rbp + -72], rax
  addq $31, rax
  movq rax, [rbp + -80]
  movq $10, rax
  movq [rbp + -80], rdx
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -96], rax
  add rax, 8
  mov [rel heap_ptr], rax
  movq [rbp + -80], rax
  movq [rbp + -96], rdx
  mov [rdx], rax
  movq [rbp + -64], rax
  cmpq $0, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne lm_print_int_neg
  jmp lm_print_int_abs
lm_print_int_neg:
  subq $32, %rsp
  movq $1, rcx
  movq [rel str_minus], rdx
  movq $1, r8
  call _write
  addq $32, %rsp
  movq [rbp + -64], rax
  negq rax
  movq rax, $
  movq $, rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  jmp lm_print_int_loop
lm_print_int_abs:
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  jmp lm_print_int_loop
lm_print_int_loop:
  movq [rbp + -88], rax
  mov rax, [rax]
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  cqto
  movq $10, rcx
  idivq rcx
  movq rax, [rbp + -128]
  movq [rbp + -120], rax
  cqto
  movq $10, rcx
  idivq rcx
  movq rdx, [rbp + -136]
  movq [rbp + -136], rax
  addq $48, rax
  movq rax, [rbp + -144]
  movq [rbp + -96], rax
  mov rax, [rax]
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  subq $1, rax
  movq rax, [rbp + -160]
  movq [rbp + -144], rax
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  movq [rbp + -160], rdx
  mov byte ptr [rdx], al
  movq [rbp + -128], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rbp + -160], rax
  movq [rbp + -96], rdx
  mov [rdx], rax
  movq [rbp + -128], rax
  cmpq $1, rax
  setae al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne lm_print_int_loop
  jmp lm_print_int_done
lm_print_int_done:
  movq [rbp + -96], rax
  mov rax, [rax]
  movq rax, [rbp + -184]
  movq [rbp + -72], rax
  addq $32, rax
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  subq [rbp + -184], rax
  movq rax, [rbp + -200]
  subq $32, %rsp
  movq $1, rcx
  movq [rbp + -184], rdx
  movq [rbp + -200], r8
  call _write
  addq $32, %rsp
  movq $0, rax
  jmp lm_print_int_epilogue
lm_print_int_epilogue:
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
.Lfunc_end_lm_print_int:

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

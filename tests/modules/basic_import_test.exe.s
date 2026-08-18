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
  .string "=== Basic Import Test ==="
.align 8
str_const_1:
  .string "Test 1.1: Access module variable"
.align 8
str_const_2:
  .string "Test 1.2: Access module number"
.align 8
str_const_3:
  .string "Test 1.3: Call module function"
.align 8
str_const_4:
  .string "Test 1.4: Call function with parameters"
.align 8
str_const_5:
  .string "5 + 3 = "
.align 8
str_const_6:
  .string "Test 1.5: Call function that returns module variable "
.align 8
str_const_7:
  .string "Module variable via function: "
.align 8
str_const_8:
  .string "Hello from basic module"
.align 8
str_const_9:
  .string "Module variable should be accessible"
.align 8
str_const_10:
  .string "Module number should be accessible"
.align 8
str_const_11:
  .string "Module function should work: 5 + 3 = 8"
.align 8
str_const_12:
  .string "Hello from basic module"
.align 8
str_const_13:
  .string "Module function should return correct variable"
.align 8
str_const_14:
  .string "=== Basic Import Test Complete ==="
.align 8
str_const_15:
  .string "Greetings from basic module!"
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
  sub rsp, 488
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
  call tests.modules.basic_module.__init__
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
  movq $0, rax
  addq $16, rax
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  mov rax, [rax]
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  call lm_print_str
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  addq $16, rax
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  mov rax, [rax]
  movq rax, [rbp + -176]
  movq [rbp + -176], rcx
  call lm_print_str
  movq $0, rax
  addq $16, rax
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  mov rax, [rax]
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  call lm_print_str
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  addq $16, rax
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  mov rax, [rax]
  movq rax, [rbp + -232]
  movq [rbp + -232], rcx
  call lm_print_str
  call tests.modules.basic_module.greet
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  addq $16, rax
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  mov rax, [rax]
  movq rax, [rbp + -264]
  movq [rbp + -264], rcx
  call lm_print_str
  movq $41, rcx
  movq $25, rdx
  call tests.modules.basic_module.add
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq $r18, rcx
  call lm_to_string
  movq rax, [rbp + -280]
  movq [rbp + -272], rcx
  movq [rbp + -280], rdx
  call lm_str_concat
  movq rax, [rbp + -288]
  movq [rbp + -288], rax
  addq $16, rax
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  mov rax, [rax]
  movq rax, [rbp + -312]
  movq [rbp + -312], rcx
  call lm_print_str
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  addq $16, rax
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  movq rax, [rbp + -336]
  movq [rbp + -336], rax
  mov rax, [rax]
  movq rax, [rbp + -344]
  movq [rbp + -344], rcx
  call lm_print_str
  call tests.modules.basic_module.getModuleVar
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -352], rcx
  movq $r26, rdx
  call lm_str_concat
  movq rax, [rbp + -360]
  movq [rbp + -360], rax
  addq $16, rax
  movq rax, [rbp + -368]
  movq [rbp + -368], rax
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  mov rax, [rax]
  movq rax, [rbp + -384]
  movq [rbp + -384], rcx
  call lm_print_str
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq $0, rax
  cmpq [rbp + -392], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -400]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -400], rcx
  movq [rbp + -408], rdx
  call lm_assert
  movq $0, rax
  cmpq $337, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -416]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -416], rcx
  movq [rbp + -424], rdx
  call lm_assert
  movq $r18, rax
  cmpq $65, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -432]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rbp + -432], rcx
  movq [rbp + -440], rdx
  call lm_assert
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq $r26, rax
  cmpq [rbp + -448], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -456]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq [rbp + -456], rcx
  movq [rbp + -464], rdx
  call lm_assert
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -472], rax
  addq $16, rax
  movq rax, [rbp + -480]
  movq [rbp + -480], rax
  movq rax, [rbp + -488]
  movq [rbp + -488], rax
  mov rax, [rax]
  movq rax, [rbp + -496]
  movq [rbp + -496], rcx
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

.globl tests.modules.basic_module.greet
tests.modules.basic_module.greet:
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
tests.modules.basic_module.greet_entry:
tests.modules.basic_module.greet_block_0:
  movq [rel str_const_15], rcx
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
  movq $0, rax
  jmp tests.modules.basic_module.greet_epilogue
tests.modules.basic_module.greet_epilogue:
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
.Lfunc_end_tests.modules.basic_module.greet:

.globl tests.modules.basic_module.add
tests.modules.basic_module.add:
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
tests.modules.basic_module.add_entry:
tests.modules.basic_module.add_block_0:
  movq [rbp + -64], rax
  addq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp tests.modules.basic_module.add_epilogue
tests.modules.basic_module.add_epilogue:
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
.Lfunc_end_tests.modules.basic_module.add:

.globl tests.modules.basic_module.__init__
tests.modules.basic_module.__init__:
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
tests.modules.basic_module.__init___entry:
  movq $0, rax
  jmp tests.modules.basic_module.__init___epilogue
tests.modules.basic_module.__init___epilogue:
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
.Lfunc_end_tests.modules.basic_module.__init__:

.globl tests.modules.basic_module.getModuleVar
tests.modules.basic_module.getModuleVar:
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
tests.modules.basic_module.getModuleVar_entry:
tests.modules.basic_module.getModuleVar_block_0:
  movq $0, rax
  jmp tests.modules.basic_module.getModuleVar_epilogue
tests.modules.basic_module.getModuleVar_epilogue:
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
.Lfunc_end_tests.modules.basic_module.getModuleVar:

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

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
  .string "=== Scientific Notation Tests ==="
.align 8
str_const_1:
  .string "Scientific notation test:"
.align 8
str_const_2:
  .string "Small:"
.align 8
str_const_3:
  .string "Large:"
.align 8
str_const_4:
  .string "Negative:"
.align 8
str_const_5:
  .string "Small scientific notation should parse correctly"
.align 8
str_const_6:
  .string "Large scientific notation should parse correctly"
.align 8
str_const_7:
  .string "Negative scientific notation should parse correctly"
.align 8
str_const_8:
  .string "Capital E notation:"
.align 8
str_const_9:
  .string "Capital E positive:"
.align 8
str_const_10:
  .string "Capital E negative:"
.align 8
str_const_11:
  .string "Capital E positive should work"
.align 8
str_const_12:
  .string "Capital E negative should work"
.align 8
str_const_13:
  .string "Integer scientific notation:"
.align 8
str_const_14:
  .string "Int scientific:"
.align 8
str_const_15:
  .string "Int scientific negative:"
.align 8
str_const_16:
  .string "Integer scientific notation should work"
.align 8
str_const_17:
  .string "Integer scientific notation negative should work"
.align 8
str_const_18:
  .string "Edge cases:"
.align 8
str_const_19:
  .string "Zero:"
.align 8
str_const_20:
  .string "One:"
.align 8
str_const_21:
  .string "Zero scientific notation should be 0"
.align 8
str_const_22:
  .string "One scientific notation should be 1"
.align 8
str_const_23:
  .string "Expression result:"
.align 8
str_const_24:
  .string "Scientific notation in expressions should work"
.align 8
str_const_25:
  .string "1.5e3 + 2.5e2 should equal 1750.0"
.align 8
str_const_26:
  .string "Arithmetic operations:"
.align 8
str_const_27:
  .string "Multiply: 2e3 * 3e2 = %s"
.align 8
str_const_28:
  .string "Divide: 6e6 / 2e3 = %s"
.align 8
str_const_29:
  .string "Subtract: 5e4 - 1e4 = %s"
.align 8
str_const_30:
  .string "2e3 * 3e2 should equal 6e5"
.align 8
str_const_31:
  .string "6e6 / 2e3 should equal 3e3"
.align 8
str_const_32:
  .string "5e4 - 1e4 should equal 4e4"
.align 8
str_const_33:
  .string "=== Scientific Notation Tests Complete ==="
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
  sub rsp, 968
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
  movq [rbp + -128], rax
  addq $16, rax
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  mov rax, [rax]
  movq rax, [rbp + -152]
  movq [rbp + -152], rcx
  movq $2, rdx
  call lm_print_str
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  addq $16, rax
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  mov rax, [rax]
  movq rax, [rbp + -184]
  movq [rbp + -184], rcx
  movq $2, rdx
  call lm_print_str
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  addq $16, rax
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  mov rax, [rax]
  movq rax, [rbp + -216]
  movq [rbp + -216], rcx
  movq $2, rdx
  call lm_print_str
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -256], rcx
  movq [rbp + -264], rdx
  call lm_assert
  movq [rel str_const_8], rcx
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
  movq [rel str_const_9], rcx
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
  movq $2, rdx
  call lm_print_str
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -336], rax
  addq $16, rax
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  mov rax, [rax]
  movq rax, [rbp + -360]
  movq [rbp + -360], rcx
  movq $2, rdx
  call lm_print_str
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -368]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -368], rcx
  movq [rbp + -376], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -384]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq [rbp + -384], rcx
  movq [rbp + -392], rdx
  call lm_assert
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  addq $16, rax
  movq rax, [rbp + -408]
  movq [rbp + -408], rax
  movq rax, [rbp + -416]
  movq [rbp + -416], rax
  mov rax, [rax]
  movq rax, [rbp + -424]
  movq [rbp + -424], rcx
  call lm_print_str
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rbp + -432], rax
  addq $16, rax
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  movq rax, [rbp + -448]
  movq [rbp + -448], rax
  mov rax, [rax]
  movq rax, [rbp + -456]
  movq [rbp + -456], rcx
  movq $2, rdx
  call lm_print_str
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq [rbp + -464], rax
  addq $16, rax
  movq rax, [rbp + -472]
  movq [rbp + -472], rax
  movq rax, [rbp + -480]
  movq [rbp + -480], rax
  mov rax, [rax]
  movq rax, [rbp + -488]
  movq [rbp + -488], rcx
  movq $2, rdx
  call lm_print_str
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -496]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -496], rcx
  movq [rbp + -504], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -512]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -512], rcx
  movq [rbp + -520], rdx
  call lm_assert
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -528], rax
  addq $16, rax
  movq rax, [rbp + -536]
  movq [rbp + -536], rax
  movq rax, [rbp + -544]
  movq [rbp + -544], rax
  mov rax, [rax]
  movq rax, [rbp + -552]
  movq [rbp + -552], rcx
  call lm_print_str
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -560]
  movq [rbp + -560], rax
  addq $16, rax
  movq rax, [rbp + -568]
  movq [rbp + -568], rax
  movq rax, [rbp + -576]
  movq [rbp + -576], rax
  mov rax, [rax]
  movq rax, [rbp + -584]
  movq [rbp + -584], rcx
  movq $2, rdx
  call lm_print_str
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -592]
  movq [rbp + -592], rax
  addq $16, rax
  movq rax, [rbp + -600]
  movq [rbp + -600], rax
  movq rax, [rbp + -608]
  movq [rbp + -608], rax
  mov rax, [rax]
  movq rax, [rbp + -616]
  movq [rbp + -616], rcx
  movq $2, rdx
  call lm_print_str
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -624]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -632]
  movq [rbp + -624], rcx
  movq [rbp + -632], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -640]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -648]
  movq [rbp + -640], rcx
  movq [rbp + -648], rdx
  call lm_assert
  movq $2, rax
  addq $2, rax
  movq rax, [rbp + -656]
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -664]
  movq [rbp + -664], rax
  addq $16, rax
  movq rax, [rbp + -672]
  movq [rbp + -672], rax
  movq rax, [rbp + -680]
  movq [rbp + -680], rax
  mov rax, [rax]
  movq rax, [rbp + -688]
  movq [rbp + -688], rcx
  movq [rbp + -656], rdx
  call lm_print_str
  movq $2, rax
  addq $2, rax
  movq rax, [rbp + -696]
  movq [rbp + -656], rax
  cmpq [rbp + -696], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -704]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -712]
  movq [rbp + -704], rcx
  movq [rbp + -712], rdx
  call lm_assert
  movq [rbp + -656], rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -720]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -728]
  movq [rbp + -720], rcx
  movq [rbp + -728], rdx
  call lm_assert
  movq $2, rax
  imulq $2, rax
  movq rax, [rbp + -736]
  movq $2, rax
  cqto
  movq $2, rcx
  idivq rcx
  movq rax, [rbp + -744]
  movq $2, rax
  subq $2, rax
  movq rax, [rbp + -752]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -760]
  movq [rbp + -760], rax
  addq $16, rax
  movq rax, [rbp + -768]
  movq [rbp + -768], rax
  movq rax, [rbp + -776]
  movq [rbp + -776], rax
  mov rax, [rax]
  movq rax, [rbp + -784]
  movq [rbp + -784], rcx
  call lm_print_str
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -792]
  movq [rbp + -792], rcx
  movq [rbp + -736], rdx
  call lm_rt_str_format
  movq rax, [rbp + -800]
  movq [rbp + -800], rax
  addq $16, rax
  movq rax, [rbp + -808]
  movq [rbp + -808], rax
  movq rax, [rbp + -816]
  movq [rbp + -816], rax
  mov rax, [rax]
  movq rax, [rbp + -824]
  movq [rbp + -824], rcx
  call lm_print_str
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -832]
  movq [rbp + -832], rcx
  movq [rbp + -744], rdx
  call lm_rt_str_format
  movq rax, [rbp + -840]
  movq [rbp + -840], rax
  addq $16, rax
  movq rax, [rbp + -848]
  movq [rbp + -848], rax
  movq rax, [rbp + -856]
  movq [rbp + -856], rax
  mov rax, [rax]
  movq rax, [rbp + -864]
  movq [rbp + -864], rcx
  call lm_print_str
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -872]
  movq [rbp + -872], rcx
  movq [rbp + -752], rdx
  call lm_rt_str_format
  movq rax, [rbp + -880]
  movq [rbp + -880], rax
  addq $16, rax
  movq rax, [rbp + -888]
  movq [rbp + -888], rax
  movq rax, [rbp + -896]
  movq [rbp + -896], rax
  mov rax, [rax]
  movq rax, [rbp + -904]
  movq [rbp + -904], rcx
  call lm_print_str
  movq [rbp + -736], rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -912]
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -920]
  movq [rbp + -912], rcx
  movq [rbp + -920], rdx
  call lm_assert
  movq [rbp + -744], rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -928]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -936]
  movq [rbp + -928], rcx
  movq [rbp + -936], rdx
  call lm_assert
  movq [rbp + -752], rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -944]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -952]
  movq [rbp + -944], rcx
  movq [rbp + -952], rdx
  call lm_assert
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -960]
  movq [rbp + -960], rax
  addq $16, rax
  movq rax, [rbp + -968]
  movq [rbp + -968], rax
  movq rax, [rbp + -976]
  movq [rbp + -976], rax
  mov rax, [rax]
  movq rax, [rbp + -984]
  movq [rbp + -984], rcx
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

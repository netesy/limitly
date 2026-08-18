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
  .string "=== Arithmetic Expression Tests ==="
.align 8
str_const_1:
  .string "Addition: %s + %s = %s"
.align 8
str_const_2:
  .string "Subtraction: %s - %s = %s"
.align 8
str_const_3:
  .string "Multiplication: %s * %s = %s"
.align 8
str_const_4:
  .string "Division: %s / %s = %s"
.align 8
str_const_5:
  .string "Modulo: %s % %s = %s"
.align 8
str_const_6:
  .string "10 + 3 should equal 13"
.align 8
str_const_7:
  .string "10 - 3 should equal 7"
.align 8
str_const_8:
  .string "10 * 3 should equal 30"
.align 8
str_const_9:
  .string "10 / 3 should equal 3"
.align 8
str_const_10:
  .string "10 % 3 should equal 1"
.align 8
str_const_11:
  .string "Negation: -%s = %s"
.align 8
str_const_12:
  .string "Positive: +%s = %s"
.align 8
str_const_13:
  .string "-10 should equal -10"
.align 8
str_const_14:
  .string "+10 should equal 10"
.align 8
str_const_15:
  .string "Complex: (%s + %s) * 2 - %s / %s = %s"
.align 8
str_const_16:
  .string "(10 + 3) * 2 - 10 / 3 should equal 23"
.align 8
str_const_17:
  .string "Precedence: %s + %s * 2 = %s"
.align 8
str_const_18:
  .string "10 + 3 * 2 should equal 16 (multiplication first)"
.align 8
str_const_19:
  .string "Float arithmetic: %s + %s = %s"
.align 8
str_const_20:
  .string "Float division: %s / %s = %s"
.align 8
str_const_21:
  .string "3.14 + 2.0 should equal approximately 5.14"
.align 8
str_const_22:
  .string "3.14 / 2.0 should equal approximately 1.57"
.align 8
str_const_23:
  .string "=== Arithmetic Expression Tests Complete ==="
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
  sub rsp, 1048
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
  movq $81, rax
  addq $25, rax
  movq rax, [rbp + -96]
  movq $81, rax
  subq $25, rax
  movq rax, [rbp + -104]
  movq $81, rax
  imulq $25, rax
  movq rax, [rbp + -112]
  movq $81, rax
  cqto
  movq $25, rcx
  idivq rcx
  movq rax, [rbp + -120]
  movq $81, rax
  cqto
  movq $25, rcx
  idivq rcx
  movq rdx, [rbp + -128]
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  movq $25, rdx
  call lm_rt_str_format
  movq rax, [rbp + -152]
  movq [rbp + -152], rcx
  movq [rbp + -96], rdx
  call lm_rt_str_format
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
  call lm_print_str
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -192], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  movq $25, rdx
  call lm_rt_str_format
  movq rax, [rbp + -208]
  movq [rbp + -208], rcx
  movq [rbp + -104], rdx
  call lm_rt_str_format
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  addq $16, rax
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  mov rax, [rax]
  movq rax, [rbp + -240]
  movq [rbp + -240], rcx
  call lm_print_str
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -248], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -256]
  movq [rbp + -256], rcx
  movq $25, rdx
  call lm_rt_str_format
  movq rax, [rbp + -264]
  movq [rbp + -264], rcx
  movq [rbp + -112], rdx
  call lm_rt_str_format
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
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -304], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -312]
  movq [rbp + -312], rcx
  movq $25, rdx
  call lm_rt_str_format
  movq rax, [rbp + -320]
  movq [rbp + -320], rcx
  movq [rbp + -120], rdx
  call lm_rt_str_format
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  addq $16, rax
  movq rax, [rbp + -336]
  movq [rbp + -336], rax
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  mov rax, [rax]
  movq rax, [rbp + -352]
  movq [rbp + -352], rcx
  call lm_print_str
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -360], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -368]
  movq [rbp + -368], rcx
  movq $25, rdx
  call lm_rt_str_format
  movq rax, [rbp + -376]
  movq [rbp + -376], rcx
  movq [rbp + -128], rdx
  call lm_rt_str_format
  movq rax, [rbp + -384]
  movq [rbp + -384], rax
  addq $16, rax
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  mov rax, [rax]
  movq rax, [rbp + -408]
  movq [rbp + -408], rcx
  call lm_print_str
  movq [rbp + -96], rax
  cmpq $105, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -416]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -416], rcx
  movq [rbp + -424], rdx
  call lm_assert
  movq [rbp + -104], rax
  cmpq $57, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -432]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rbp + -432], rcx
  movq [rbp + -440], rdx
  call lm_assert
  movq [rbp + -112], rax
  cmpq $241, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -448]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq [rbp + -448], rcx
  movq [rbp + -456], rdx
  call lm_assert
  movq [rbp + -120], rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -464]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -464], rcx
  movq [rbp + -472], rdx
  call lm_assert
  movq [rbp + -128], rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -480]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -488]
  movq [rbp + -480], rcx
  movq [rbp + -488], rdx
  call lm_assert
  movq $81, rax
  negq rax
  movq rax, [rbp + -496]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -504], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -512]
  movq [rbp + -512], rcx
  movq [rbp + -496], rdx
  call lm_rt_str_format
  movq rax, [rbp + -520]
  movq [rbp + -520], rax
  addq $16, rax
  movq rax, [rbp + -528]
  movq [rbp + -528], rax
  movq rax, [rbp + -536]
  movq [rbp + -536], rax
  mov rax, [rax]
  movq rax, [rbp + -544]
  movq [rbp + -544], rcx
  call lm_print_str
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -552]
  movq [rbp + -552], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -560]
  movq [rbp + -560], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -568]
  movq [rbp + -568], rax
  addq $16, rax
  movq rax, [rbp + -576]
  movq [rbp + -576], rax
  movq rax, [rbp + -584]
  movq [rbp + -584], rax
  mov rax, [rax]
  movq rax, [rbp + -592]
  movq [rbp + -592], rcx
  call lm_print_str
  movq $81, rax
  negq rax
  movq rax, [rbp + -600]
  movq [rbp + -496], rax
  cmpq [rbp + -600], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -608]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -608], rcx
  movq [rbp + -616], rdx
  call lm_assert
  movq $81, rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -624]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -632]
  movq [rbp + -624], rcx
  movq [rbp + -632], rdx
  call lm_assert
  movq $81, rax
  addq $25, rax
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  imulq $17, rax
  movq rax, [rbp + -648]
  movq $81, rax
  cqto
  movq $25, rcx
  idivq rcx
  movq rax, [rbp + -656]
  movq [rbp + -648], rax
  subq [rbp + -656], rax
  movq rax, [rbp + -664]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -672]
  movq [rbp + -672], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -680]
  movq [rbp + -680], rcx
  movq $25, rdx
  call lm_rt_str_format
  movq rax, [rbp + -688]
  movq [rbp + -688], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -696]
  movq [rbp + -696], rcx
  movq $25, rdx
  call lm_rt_str_format
  movq rax, [rbp + -704]
  movq [rbp + -704], rcx
  movq [rbp + -664], rdx
  call lm_rt_str_format
  movq rax, [rbp + -712]
  movq [rbp + -712], rax
  addq $16, rax
  movq rax, [rbp + -720]
  movq [rbp + -720], rax
  movq rax, [rbp + -728]
  movq [rbp + -728], rax
  mov rax, [rax]
  movq rax, [rbp + -736]
  movq [rbp + -736], rcx
  call lm_print_str
  movq [rbp + -664], rax
  cmpq $185, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -744]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -752]
  movq [rbp + -744], rcx
  movq [rbp + -752], rdx
  call lm_assert
  movq $25, rax
  imulq $17, rax
  movq rax, [rbp + -760]
  movq $25, rax
  imulq $17, rax
  movq rax, [rbp + -768]
  movq $81, rax
  addq [rbp + -768], rax
  movq rax, [rbp + -776]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -784]
  movq [rbp + -784], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -792]
  movq [rbp + -792], rcx
  movq $25, rdx
  call lm_rt_str_format
  movq rax, [rbp + -800]
  movq [rbp + -800], rcx
  movq [rbp + -776], rdx
  call lm_rt_str_format
  movq rax, [rbp + -808]
  movq [rbp + -808], rax
  addq $16, rax
  movq rax, [rbp + -816]
  movq [rbp + -816], rax
  movq rax, [rbp + -824]
  movq [rbp + -824], rax
  mov rax, [rax]
  movq rax, [rbp + -832]
  movq [rbp + -832], rcx
  call lm_print_str
  movq [rbp + -776], rax
  cmpq $129, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -840]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -848]
  movq [rbp + -840], rcx
  movq [rbp + -848], rdx
  call lm_assert
  movq $2, rax
  addq $2, rax
  movq rax, [rbp + -856]
  movq $2, rax
  cqto
  movq $2, rcx
  idivq rcx
  movq rax, [rbp + -864]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -872]
  movq [rbp + -872], rcx
  movq $2, rdx
  call lm_rt_str_format
  movq rax, [rbp + -880]
  movq [rbp + -880], rcx
  movq $2, rdx
  call lm_rt_str_format
  movq rax, [rbp + -888]
  movq [rbp + -888], rcx
  movq [rbp + -856], rdx
  call lm_rt_str_format
  movq rax, [rbp + -896]
  movq [rbp + -896], rax
  addq $16, rax
  movq rax, [rbp + -904]
  movq [rbp + -904], rax
  movq rax, [rbp + -912]
  movq [rbp + -912], rax
  mov rax, [rax]
  movq rax, [rbp + -920]
  movq [rbp + -920], rcx
  call lm_print_str
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -928]
  movq [rbp + -928], rcx
  movq $2, rdx
  call lm_rt_str_format
  movq rax, [rbp + -936]
  movq [rbp + -936], rcx
  movq $2, rdx
  call lm_rt_str_format
  movq rax, [rbp + -944]
  movq [rbp + -944], rcx
  movq [rbp + -864], rdx
  call lm_rt_str_format
  movq rax, [rbp + -952]
  movq [rbp + -952], rax
  addq $16, rax
  movq rax, [rbp + -960]
  movq [rbp + -960], rax
  movq rax, [rbp + -968]
  movq [rbp + -968], rax
  mov rax, [rax]
  movq rax, [rbp + -976]
  movq [rbp + -976], rcx
  call lm_print_str
  movq [rbp + -856], rax
  cmpq $2, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -984]
  movq [rbp + -984], rax
  testq rax, rax
  jne main_block_143
  jmp main_block_147
main_block_143:
  jmp main_block_143
  movq [rbp + -856], rax
  cmpq $2, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -992]
  jmp main_block_147
main_block_147:
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -1000]
  movq [rbp + -992], rcx
  movq [rbp + -1000], rdx
  call lm_assert
  movq [rbp + -864], rax
  cmpq $2, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -1008]
  movq [rbp + -1008], rax
  testq rax, rax
  jne main_block_153
  jmp main_block_157
main_block_153:
  jmp main_block_153
  movq [rbp + -864], rax
  cmpq $2, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -1016]
  jmp main_block_157
main_block_157:
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -1024]
  movq [rbp + -1016], rcx
  movq [rbp + -1024], rdx
  call lm_assert
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -1032]
  movq [rbp + -1032], rax
  addq $16, rax
  movq rax, [rbp + -1040]
  movq [rbp + -1040], rax
  movq rax, [rbp + -1048]
  movq [rbp + -1048], rax
  mov rax, [rax]
  movq rax, [rbp + -1056]
  movq [rbp + -1056], rcx
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

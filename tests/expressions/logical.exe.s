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
  .string "=== Logical Expression Tests ==="
.align 8
str_const_1:
  .string "AND operations:"
.align 8
str_const_2:
  .string "%s and %s: %s"
.align 8
str_const_3:
  .string "%s and %s: %s"
.align 8
str_const_4:
  .string "%s and %s: %s"
.align 8
str_const_5:
  .string "%s and %s: %s"
.align 8
str_const_6:
  .string "true and true should be true"
.align 8
str_const_7:
  .string "true and false should be false"
.align 8
str_const_8:
  .string "false and true should be false"
.align 8
str_const_9:
  .string "false and false should be false"
.align 8
str_const_10:
  .string "OR operations:"
.align 8
str_const_11:
  .string "%s or %s: %s"
.align 8
str_const_12:
  .string "%s or %s: %s"
.align 8
str_const_13:
  .string "%s or %s: %s"
.align 8
str_const_14:
  .string "%s or %s: %s"
.align 8
str_const_15:
  .string "true or true should be true"
.align 8
str_const_16:
  .string "true or false should be true"
.align 8
str_const_17:
  .string "false or true should be true"
.align 8
str_const_18:
  .string "false or false should be false"
.align 8
str_const_19:
  .string "NOT operations:"
.align 8
str_const_20:
  .string "!%s: %s"
.align 8
str_const_21:
  .string "!%s: %s"
.align 8
str_const_22:
  .string "!true should be false"
.align 8
str_const_23:
  .string "!false should be true"
.align 8
str_const_24:
  .string "Complex: (%s < %s) and (%s > 0) = %s"
.align 8
str_const_25:
  .string "Complex: (%s > %s) or (%s == 5) = %s"
.align 8
str_const_26:
  .string "(5 < 10) and (10 > 0) should be true"
.align 8
str_const_27:
  .string "(5 > 10) or (5 == 5) should be true"
.align 8
str_const_28:
  .string "Short-circuit tests:"
.align 8
str_const_29:
  .string "Safe division with and: %s"
.align 8
str_const_30:
  .string "Short-circuit should prevent division by zero"
.align 8
str_const_31:
  .string "=== Logical Expression Tests Complete ==="
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
  sub rsp, 1224
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
  movq $18, rax
  testq rax, rax
  jne main_block_8
  jmp main_block_10
main_block_8:
  jmp main_block_8
  jmp main_block_10
main_block_10:
  movq $18, rax
  testq rax, rax
  jne main_block_13
  jmp main_block_15
main_block_13:
  jmp main_block_13
  jmp main_block_15
main_block_15:
  movq $10, rax
  testq rax, rax
  jne main_block_18
  jmp main_block_20
main_block_18:
  jmp main_block_18
  jmp main_block_20
main_block_20:
  movq $10, rax
  testq rax, rax
  jne main_block_23
  jmp main_block_25
main_block_23:
  jmp main_block_23
  jmp main_block_25
main_block_25:
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  movq $18, rdx
  call lm_rt_str_format
  movq rax, [rbp + -136]
  movq [rbp + -136], rcx
  movq $18, rdx
  call lm_rt_str_format
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  movq $18, rdx
  call lm_rt_str_format
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
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -184], rcx
  movq $18, rdx
  call lm_rt_str_format
  movq rax, [rbp + -192]
  movq [rbp + -192], rcx
  movq $10, rdx
  call lm_rt_str_format
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  movq $10, rdx
  call lm_rt_str_format
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
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -240], rcx
  movq $10, rdx
  call lm_rt_str_format
  movq rax, [rbp + -248]
  movq [rbp + -248], rcx
  movq $18, rdx
  call lm_rt_str_format
  movq rax, [rbp + -256]
  movq [rbp + -256], rcx
  movq $18, rdx
  call lm_rt_str_format
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  addq $16, rax
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  mov rax, [rax]
  movq rax, [rbp + -288]
  movq [rbp + -288], rcx
  call lm_print_str
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -296], rcx
  movq $10, rdx
  call lm_rt_str_format
  movq rax, [rbp + -304]
  movq [rbp + -304], rcx
  movq $10, rdx
  call lm_rt_str_format
  movq rax, [rbp + -312]
  movq [rbp + -312], rcx
  movq $10, rdx
  call lm_rt_str_format
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
  movq $18, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -352]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -352], rcx
  movq [rbp + -360], rdx
  call lm_assert
  movq $10, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -368]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -368], rcx
  movq [rbp + -376], rdx
  call lm_assert
  movq $18, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -384]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq [rbp + -384], rcx
  movq [rbp + -392], rdx
  call lm_assert
  movq $10, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -400]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -400], rcx
  movq [rbp + -408], rdx
  call lm_assert
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -416], rax
  addq $16, rax
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  movq rax, [rbp + -432]
  movq [rbp + -432], rax
  mov rax, [rax]
  movq rax, [rbp + -440]
  movq [rbp + -440], rcx
  call lm_print_str
  movq $18, rax
  testq rax, rax
  jne main_block_72
  jmp main_block_70
main_block_70:
  jmp main_block_70
  jmp main_block_72
main_block_72:
  movq $18, rax
  testq rax, rax
  jne main_block_77
  jmp main_block_75
main_block_75:
  jmp main_block_75
  jmp main_block_77
main_block_77:
  movq $10, rax
  testq rax, rax
  jne main_block_82
  jmp main_block_80
main_block_80:
  jmp main_block_80
  jmp main_block_82
main_block_82:
  movq $10, rax
  testq rax, rax
  jne main_block_87
  jmp main_block_85
main_block_85:
  jmp main_block_85
  jmp main_block_87
main_block_87:
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -448], rcx
  movq $18, rdx
  call lm_rt_str_format
  movq rax, [rbp + -456]
  movq [rbp + -456], rcx
  movq $18, rdx
  call lm_rt_str_format
  movq rax, [rbp + -464]
  movq [rbp + -464], rcx
  movq $18, rdx
  call lm_rt_str_format
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
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -504], rcx
  movq $18, rdx
  call lm_rt_str_format
  movq rax, [rbp + -512]
  movq [rbp + -512], rcx
  movq $10, rdx
  call lm_rt_str_format
  movq rax, [rbp + -520]
  movq [rbp + -520], rcx
  movq $10, rdx
  call lm_rt_str_format
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
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -560]
  movq [rbp + -560], rcx
  movq $10, rdx
  call lm_rt_str_format
  movq rax, [rbp + -568]
  movq [rbp + -568], rcx
  movq $18, rdx
  call lm_rt_str_format
  movq rax, [rbp + -576]
  movq [rbp + -576], rcx
  movq $18, rdx
  call lm_rt_str_format
  movq rax, [rbp + -584]
  movq [rbp + -584], rax
  addq $16, rax
  movq rax, [rbp + -592]
  movq [rbp + -592], rax
  movq rax, [rbp + -600]
  movq [rbp + -600], rax
  mov rax, [rax]
  movq rax, [rbp + -608]
  movq [rbp + -608], rcx
  call lm_print_str
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -616], rcx
  movq $10, rdx
  call lm_rt_str_format
  movq rax, [rbp + -624]
  movq [rbp + -624], rcx
  movq $10, rdx
  call lm_rt_str_format
  movq rax, [rbp + -632]
  movq [rbp + -632], rcx
  movq $10, rdx
  call lm_rt_str_format
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  addq $16, rax
  movq rax, [rbp + -648]
  movq [rbp + -648], rax
  movq rax, [rbp + -656]
  movq [rbp + -656], rax
  mov rax, [rax]
  movq rax, [rbp + -664]
  movq [rbp + -664], rcx
  call lm_print_str
  movq $18, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -672]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -680]
  movq [rbp + -672], rcx
  movq [rbp + -680], rdx
  call lm_assert
  movq $10, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -688]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -696]
  movq [rbp + -688], rcx
  movq [rbp + -696], rdx
  call lm_assert
  movq $18, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -704]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -712]
  movq [rbp + -704], rcx
  movq [rbp + -712], rdx
  call lm_assert
  movq $10, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -720]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -728]
  movq [rbp + -720], rcx
  movq [rbp + -728], rdx
  call lm_assert
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -736]
  movq [rbp + -736], rax
  addq $16, rax
  movq rax, [rbp + -744]
  movq [rbp + -744], rax
  movq rax, [rbp + -752]
  movq [rbp + -752], rax
  mov rax, [rax]
  movq rax, [rbp + -760]
  movq [rbp + -760], rcx
  call lm_print_str
  movq $18, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -768]
  movq $10, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -776]
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -784]
  movq [rbp + -784], rcx
  movq $18, rdx
  call lm_rt_str_format
  movq rax, [rbp + -792]
  movq [rbp + -792], rcx
  movq [rbp + -768], rdx
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
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -832]
  movq [rbp + -832], rcx
  movq $10, rdx
  call lm_rt_str_format
  movq rax, [rbp + -840]
  movq [rbp + -840], rcx
  movq [rbp + -776], rdx
  call lm_rt_str_format
  movq rax, [rbp + -848]
  movq [rbp + -848], rax
  addq $16, rax
  movq rax, [rbp + -856]
  movq [rbp + -856], rax
  movq rax, [rbp + -864]
  movq [rbp + -864], rax
  mov rax, [rax]
  movq rax, [rbp + -872]
  movq [rbp + -872], rcx
  call lm_print_str
  movq [rbp + -768], rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -880]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -888]
  movq [rbp + -880], rcx
  movq [rbp + -888], rdx
  call lm_assert
  movq [rbp + -776], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -896]
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -904]
  movq [rbp + -896], rcx
  movq [rbp + -904], rdx
  call lm_assert
  movq $41, rax
  cmpq $81, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -912]
  movq [rbp + -912], rax
  testq rax, rax
  jne main_block_159
  jmp main_block_163
main_block_159:
  jmp main_block_159
  movq $81, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -920]
  jmp main_block_163
main_block_163:
  movq $41, rax
  cmpq $81, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -928]
  movq [rbp + -928], rax
  testq rax, rax
  jne main_block_171
  jmp main_block_167
main_block_167:
  jmp main_block_167
  movq $41, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -936]
  jmp main_block_171
main_block_171:
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -944]
  movq [rbp + -944], rcx
  movq $41, rdx
  call lm_rt_str_format
  movq rax, [rbp + -952]
  movq [rbp + -952], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -960]
  movq [rbp + -960], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -968]
  movq [rbp + -968], rcx
  movq [rbp + -920], rdx
  call lm_rt_str_format
  movq rax, [rbp + -976]
  movq [rbp + -976], rax
  addq $16, rax
  movq rax, [rbp + -984]
  movq [rbp + -984], rax
  movq rax, [rbp + -992]
  movq [rbp + -992], rax
  mov rax, [rax]
  movq rax, [rbp + -1000]
  movq [rbp + -1000], rcx
  call lm_print_str
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -1008]
  movq [rbp + -1008], rcx
  movq $41, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1016]
  movq [rbp + -1016], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1024]
  movq [rbp + -1024], rcx
  movq $41, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1032]
  movq [rbp + -1032], rcx
  movq [rbp + -936], rdx
  call lm_rt_str_format
  movq rax, [rbp + -1040]
  movq [rbp + -1040], rax
  addq $16, rax
  movq rax, [rbp + -1048]
  movq [rbp + -1048], rax
  movq rax, [rbp + -1056]
  movq [rbp + -1056], rax
  mov rax, [rax]
  movq rax, [rbp + -1064]
  movq [rbp + -1064], rcx
  call lm_print_str
  movq [rbp + -920], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1072]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -1080]
  movq [rbp + -1072], rcx
  movq [rbp + -1080], rdx
  call lm_assert
  movq [rbp + -936], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1088]
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -1096]
  movq [rbp + -1088], rcx
  movq [rbp + -1096], rdx
  call lm_assert
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -1104]
  movq [rbp + -1104], rax
  addq $16, rax
  movq rax, [rbp + -1112]
  movq [rbp + -1112], rax
  movq rax, [rbp + -1120]
  movq [rbp + -1120], rax
  mov rax, [rax]
  movq rax, [rbp + -1128]
  movq [rbp + -1128], rcx
  call lm_print_str
  movq $1, rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -1136]
  movq [rbp + -1136], rax
  testq rax, rax
  jne main_block_201
  jmp main_block_207
main_block_201:
  jmp main_block_201
  movq $81, rax
  cqto
  movq $1, rcx
  idivq rcx
  movq rax, [rbp + -1144]
  movq [rbp + -1144], rax
  cmpq $9, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -1152]
  jmp main_block_207
main_block_207:
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -1160]
  movq [rbp + -1160], rcx
  movq [rbp + -1152], rdx
  call lm_rt_str_format
  movq rax, [rbp + -1168]
  movq [rbp + -1168], rax
  addq $16, rax
  movq rax, [rbp + -1176]
  movq [rbp + -1176], rax
  movq rax, [rbp + -1184]
  movq [rbp + -1184], rax
  mov rax, [rax]
  movq rax, [rbp + -1192]
  movq [rbp + -1192], rcx
  call lm_print_str
  movq [rbp + -1152], rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1200]
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -1208]
  movq [rbp + -1200], rcx
  movq [rbp + -1208], rdx
  call lm_assert
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -1216]
  movq [rbp + -1216], rax
  addq $16, rax
  movq rax, [rbp + -1224]
  movq [rbp + -1224], rax
  movq rax, [rbp + -1232]
  movq [rbp + -1232], rax
  mov rax, [rax]
  movq rax, [rbp + -1240]
  movq [rbp + -1240], rcx
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

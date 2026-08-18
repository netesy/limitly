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
  .string "=== While Loop Tests ==="
.align 8
str_const_1:
  .string "Basic while loop:"
.align 8
str_const_2:
  .string "i = %s"
.align 8
str_const_3:
  .string "Basic while loop should iterate 5 times"
.align 8
str_const_4:
  .string "Sum of 0+1+2+3+4 should be 10"
.align 8
str_const_5:
  .string "Loop variable should end at 5"
.align 8
str_const_6:
  .string "While with complex condition:"
.align 8
str_const_7:
  .string "x = %s, x² = %s"
.align 8
str_const_8:
  .string "Complex while should iterate 9 times (1-9)"
.align 8
str_const_9:
  .string "Sum of 1+2+...+9 should be 45"
.align 8
str_const_10:
  .string "x should end at 10 (10² = 100 >= 100)"
.align 8
str_const_11:
  .string "Nested while loops:"
.align 8
str_const_12:
  .string "(%s, %s)"
.align 8
str_const_13:
  .string "pair of Sum should be %s"
.align 8
str_const_14:
  .string "Nested while should iterate 6 times (2x3)"
.align 8
str_const_15:
  .string "Outer should end at 2"
.align 8
str_const_16:
  .string "Sum of pairs should be 9"
.align 8
str_const_17:
  .string "While with early termination:"
.align 8
str_const_18:
  .string "count = %s"
.align 8
str_const_19:
  .string "While loop should execute 6 times (skip 3, break at 7)"
.align 8
str_const_20:
  .string "Count should be 7 when loop breaks"
.align 8
str_const_21:
  .string "While loop with decrement:"
.align 8
str_const_22:
  .string "countdown = %s"
.align 8
str_const_23:
  .string "Countdown while should iterate 5 times"
.align 8
str_const_24:
  .string "Sum of 5+4+3+2+1 should be 15"
.align 8
str_const_25:
  .string "Countdown should end at 0"
.align 8
str_const_26:
  .string "While with boolean condition:"
.align 8
str_const_27:
  .string "Boolean iteration: %s"
.align 8
str_const_28:
  .string "Boolean while should iterate 4 times"
.align 8
str_const_29:
  .string "Flag should be false at end"
.align 8
str_const_30:
  .string "=== While Loop Tests Complete ==="
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
  sub rsp, 1096
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
  jmp main_block_8
main_block_8:
  movq $1, rax
  cmpq $41, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne main_block_11
  jmp main_block_20
main_block_11:
  jmp main_block_11
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rcx
  movq $1, rdx
  call lm_rt_str_format
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  addq $16, rax
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  mov rax, [rax]
  movq rax, [rbp + -168]
  movq [rbp + -168], rcx
  call lm_print_str
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -176]
  movq $1, rax
  addq $1, rax
  movq rax, [rbp + -184]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -192]
  jmp main_block_8
main_block_20:
  movq [rbp + -176], rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -200], rcx
  movq [rbp + -208], rdx
  call lm_assert
  movq [rbp + -184], rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -216]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -216], rcx
  movq [rbp + -224], rdx
  call lm_assert
  movq [rbp + -192], rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rcx
  movq [rbp + -240], rdx
  call lm_assert
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  addq $16, rax
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  mov rax, [rax]
  movq rax, [rbp + -272]
  movq [rbp + -272], rcx
  call lm_print_str
  jmp main_block_38
main_block_38:
  movq $9, rax
  imulq $9, rax
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  cmpq $801, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -288]
  movq [rbp + -288], rax
  testq rax, rax
  jne main_block_42
  jmp main_block_54
main_block_42:
  jmp main_block_42
  movq $9, rax
  imulq $9, rax
  movq rax, [rbp + -296]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -304], rcx
  movq $9, rdx
  call lm_rt_str_format
  movq rax, [rbp + -312]
  movq [rbp + -312], rcx
  movq [rbp + -296], rdx
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
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -352]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -360]
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -368]
  jmp main_block_38
main_block_54:
  movq [rbp + -352], rax
  cmpq $73, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -376]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -376], rcx
  movq [rbp + -384], rdx
  call lm_assert
  movq [rbp + -360], rax
  cmpq $361, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -392], rcx
  movq [rbp + -400], rdx
  call lm_assert
  movq [rbp + -368], rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -408]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -408], rcx
  movq [rbp + -416], rdx
  call lm_assert
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  addq $16, rax
  movq rax, [rbp + -432]
  movq [rbp + -432], rax
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  mov rax, [rax]
  movq rax, [rbp + -448]
  movq [rbp + -448], rcx
  call lm_print_str
  jmp main_block_72
main_block_72:
  movq $1, rax
  cmpq $17, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -456]
  movq [rbp + -456], rax
  testq rax, rax
  jne main_block_75
  jmp main_block_95
main_block_75:
  jmp main_block_75
  jmp main_block_77
main_block_77:
  movq $1, rax
  cmpq $25, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -464]
  movq [rbp + -464], rax
  testq rax, rax
  jne main_block_80
  jmp main_block_92
main_block_80:
  jmp main_block_80
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -472], rcx
  movq $1, rdx
  call lm_rt_str_format
  movq rax, [rbp + -480]
  movq [rbp + -480], rcx
  movq $1, rdx
  call lm_rt_str_format
  movq rax, [rbp + -488]
  movq [rbp + -488], rax
  addq $16, rax
  movq rax, [rbp + -496]
  movq [rbp + -496], rax
  movq rax, [rbp + -504]
  movq [rbp + -504], rax
  mov rax, [rax]
  movq rax, [rbp + -512]
  movq [rbp + -512], rcx
  call lm_print_str
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -520]
  movq $1, rax
  addq $1, rax
  movq rax, [rbp + -528]
  movq $1, rax
  addq [rbp + -528], rax
  movq rax, [rbp + -536]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -544]
  jmp main_block_77
main_block_92:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -552]
  jmp main_block_72
main_block_95:
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -560]
  movq [rbp + -560], rcx
  movq [rbp + -536], rdx
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
  movq [rbp + -520], rax
  cmpq $49, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -600]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -608]
  movq [rbp + -600], rcx
  movq [rbp + -608], rdx
  call lm_assert
  movq [rbp + -552], rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -616]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rbp + -616], rcx
  movq [rbp + -624], rdx
  call lm_assert
  movq [rbp + -536], rax
  cmpq $73, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -632]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -632], rcx
  movq [rbp + -640], rdx
  call lm_assert
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -648]
  movq [rbp + -648], rax
  addq $16, rax
  movq rax, [rbp + -656]
  movq [rbp + -656], rax
  movq rax, [rbp + -664]
  movq [rbp + -664], rax
  mov rax, [rax]
  movq rax, [rbp + -672]
  movq [rbp + -672], rcx
  call lm_print_str
  jmp main_block_115
main_block_115:
  movq $1, rax
  cmpq $81, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -680]
  movq [rbp + -680], rax
  testq rax, rax
  jne main_block_118
  jmp main_block_136
main_block_118:
  jmp main_block_118
  movq $1, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -688]
  movq [rbp + -688], rax
  testq rax, rax
  jne main_block_121
  jmp main_block_124
main_block_121:
  jmp main_block_121
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -696]
  jmp main_block_115
main_block_124:
  movq [rbp + -696], rax
  cmpq $57, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -704]
  movq [rbp + -704], rax
  testq rax, rax
  jne main_block_127
  jmp main_block_128
main_block_127:
  jmp main_block_127
  jmp main_block_136
main_block_128:
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -712]
  movq [rbp + -712], rcx
  movq [rbp + -696], rdx
  call lm_rt_str_format
  movq rax, [rbp + -720]
  movq [rbp + -720], rax
  addq $16, rax
  movq rax, [rbp + -728]
  movq [rbp + -728], rax
  movq rax, [rbp + -736]
  movq [rbp + -736], rax
  mov rax, [rax]
  movq rax, [rbp + -744]
  movq [rbp + -744], rcx
  call lm_print_str
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -752]
  movq [rbp + -696], rax
  addq $9, rax
  movq rax, [rbp + -760]
  jmp main_block_115
main_block_136:
  movq [rbp + -752], rax
  cmpq $49, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -768]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -776]
  movq [rbp + -768], rcx
  movq [rbp + -776], rdx
  call lm_assert
  movq [rbp + -760], rax
  cmpq $57, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -784]
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -792]
  movq [rbp + -784], rcx
  movq [rbp + -792], rdx
  call lm_assert
  movq [rel str_const_21], rcx
  call lm_box_string
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
  jmp main_block_150
main_block_150:
  movq $41, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -832]
  movq [rbp + -832], rax
  testq rax, rax
  jne main_block_153
  jmp main_block_162
main_block_153:
  jmp main_block_153
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -840]
  movq [rbp + -840], rcx
  movq $41, rdx
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
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -880]
  movq $1, rax
  addq $41, rax
  movq rax, [rbp + -888]
  movq $41, rax
  subq $9, rax
  movq rax, [rbp + -896]
  jmp main_block_150
main_block_162:
  movq [rbp + -880], rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -904]
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -912]
  movq [rbp + -904], rcx
  movq [rbp + -912], rdx
  call lm_assert
  movq [rbp + -888], rax
  cmpq $121, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -920]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -928]
  movq [rbp + -920], rcx
  movq [rbp + -928], rdx
  call lm_assert
  movq [rbp + -896], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -936]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -944]
  movq [rbp + -936], rcx
  movq [rbp + -944], rdx
  call lm_assert
  movq [rel str_const_26], rcx
  call lm_box_string
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
  jmp main_block_180
main_block_180:
  movq $18, rax
  testq rax, rax
  jne main_block_181
  jmp main_block_195
main_block_181:
  jmp main_block_181
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -984]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -992]
  movq [rbp + -992], rax
  cmpq $33, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -1000]
  movq [rbp + -1000], rax
  testq rax, rax
  jne main_block_188
  jmp main_block_191
main_block_188:
  jmp main_block_188
  jmp main_block_191
main_block_191:
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -1008]
  movq [rbp + -1008], rcx
  movq [rbp + -984], rdx
  call lm_rt_str_format
  movq rax, [rbp + -1016]
  movq [rbp + -1016], rax
  addq $16, rax
  movq rax, [rbp + -1024]
  movq [rbp + -1024], rax
  movq rax, [rbp + -1032]
  movq [rbp + -1032], rax
  mov rax, [rax]
  movq rax, [rbp + -1040]
  movq [rbp + -1040], rcx
  call lm_print_str
  jmp main_block_180
main_block_195:
  movq [rbp + -984], rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1048]
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -1056]
  movq [rbp + -1048], rcx
  movq [rbp + -1056], rdx
  call lm_assert
  movq $10, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1064]
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -1072]
  movq [rbp + -1064], rcx
  movq [rbp + -1072], rdx
  call lm_assert
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -1080]
  movq [rbp + -1080], rax
  addq $16, rax
  movq rax, [rbp + -1088]
  movq [rbp + -1088], rax
  movq rax, [rbp + -1096]
  movq [rbp + -1096], rax
  mov rax, [rax]
  movq rax, [rbp + -1104]
  movq [rbp + -1104], rcx
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

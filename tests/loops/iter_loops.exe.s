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
  .string "=== Iter Loop Tests ==="
.align 8
str_const_1:
  .string "Basic range (1 to 5):"
.align 8
str_const_2:
  .string "i = %s"
.align 8
str_const_3:
  .string "Basic iter should iterate 5 times (1-5)"
.align 8
str_const_4:
  .string "Sum of 1+2+3+4+5 should be 15"
.align 8
str_const_5:
  .string "Range (0 to 3):"
.align 8
str_const_6:
  .string "x = %s"
.align 8
str_const_7:
  .string "Range iter should iterate 4 times (0-3)"
.align 8
str_const_8:
  .string "Sum of 0+1+2+3 should be 6"
.align 8
str_const_9:
  .string "Nested iter loops:"
.align 8
str_const_10:
  .string "Outer %s"
.align 8
str_const_11:
  .string "(%s, %s)"
.align 8
str_const_12:
  .string "Nested iter should iterate 6 times (2x3)"
.align 8
str_const_13:
  .string "Mixed loops (for outer, iter inner):"
.align 8
str_const_14:
  .string "for-iter: (%s, %s)"
.align 8
str_const_15:
  .string "Mixed for-iter should iterate 6 times (2x3)"
.align 8
str_const_16:
  .string "Mixed loops (iter outer, for inner):"
.align 8
str_const_17:
  .string "iter-for: (%s, %s)"
.align 8
str_const_18:
  .string "Mixed iter-for should iterate 6 times (2x3)"
.align 8
str_const_19:
  .string "Range with variables (%s to %s):"
.align 8
str_const_20:
  .string "k = %s"
.align 8
str_const_21:
  .string "Variable range should iterate 3 times (2-4)"
.align 8
str_const_22:
  .string "Sum of 2+3+4 should be 9"
.align 8
str_const_23:
  .string "Iter loop with break/continue:"
.align 8
str_const_24:
  .string "Iter value: %s"
.align 8
str_const_25:
  .string "Iter loop should execute 6 times (skip 3, break at 7)"
.align 8
str_const_26:
  .string "Sum should be 0+1+2+4+5+6 = 18"
.align 8
str_const_27:
  .string "Iter over calculated range:"
.align 8
str_const_28:
  .string "Calculated: %s"
.align 8
str_const_29:
  .string "Calculated range should iterate 3 times"
.align 8
str_const_30:
  .string "Sum of 10+11+12 should be 33"
.align 8
str_const_31:
  .string "=== Iter Loop Tests Complete ==="
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
  sub rsp, 1336
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
  jmp main_block_9
main_block_9:
  movq $9, rax
  cmpq $49, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne main_block_12
  jmp main_block_23
main_block_12:
  jmp main_block_12
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rcx
  movq $9, rdx
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
  addq $9, rax
  movq rax, [rbp + -184]
  jmp main_block_19
main_block_19:
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -192]
  jmp main_block_9
main_block_23:
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
  cmpq $121, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -216]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -216], rcx
  movq [rbp + -224], rdx
  call lm_assert
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  addq $16, rax
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  mov rax, [rax]
  movq rax, [rbp + -256]
  movq [rbp + -256], rcx
  call lm_print_str
  jmp main_block_38
main_block_38:
  movq $1, rax
  cmpq $33, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  testq rax, rax
  jne main_block_41
  jmp main_block_52
main_block_41:
  jmp main_block_41
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -272], rcx
  movq $1, rdx
  call lm_rt_str_format
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  addq $16, rax
  movq rax, [rbp + -288]
  movq [rbp + -288], rax
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  mov rax, [rax]
  movq rax, [rbp + -304]
  movq [rbp + -304], rcx
  call lm_print_str
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -312]
  movq $1, rax
  addq $1, rax
  movq rax, [rbp + -320]
  jmp main_block_48
main_block_48:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -328]
  jmp main_block_38
main_block_52:
  movq [rbp + -312], rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -336]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -336], rcx
  movq [rbp + -344], rdx
  call lm_assert
  movq [rbp + -320], rax
  cmpq $49, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -352]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -352], rcx
  movq [rbp + -360], rdx
  call lm_assert
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -368], rax
  addq $16, rax
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  movq rax, [rbp + -384]
  movq [rbp + -384], rax
  mov rax, [rax]
  movq rax, [rbp + -392]
  movq [rbp + -392], rcx
  call lm_print_str
  jmp main_block_67
main_block_67:
  movq $9, rax
  cmpq $25, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  testq rax, rax
  jne main_block_70
  jmp main_block_102
main_block_70:
  jmp main_block_70
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -408], rcx
  movq $9, rdx
  call lm_rt_str_format
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
  jmp main_block_76
main_block_76:
  movq $81, rax
  cmpq $105, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -448]
  movq [rbp + -448], rax
  testq rax, rax
  jne main_block_79
  jmp main_block_97
main_block_79:
  jmp main_block_79
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq [rbp + -456], rcx
  movq $9, rdx
  call lm_rt_str_format
  movq rax, [rbp + -464]
  movq [rbp + -464], rcx
  movq $81, rdx
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
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -504]
  movq $9, rax
  imulq $801, rax
  movq rax, [rbp + -512]
  movq $9, rax
  imulq $801, rax
  movq rax, [rbp + -520]
  movq [rbp + -520], rax
  addq $81, rax
  movq rax, [rbp + -528]
  movq $1, rax
  addq [rbp + -528], rax
  movq rax, [rbp + -536]
  jmp main_block_93
main_block_93:
  movq $81, rax
  addq $9, rax
  movq rax, [rbp + -544]
  jmp main_block_76
main_block_97:
  jmp main_block_98
main_block_98:
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -552]
  jmp main_block_67
main_block_102:
  movq [rbp + -504], rax
  cmpq $49, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -560]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -568]
  movq [rbp + -560], rcx
  movq [rbp + -568], rdx
  call lm_assert
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -576], rax
  addq $16, rax
  movq rax, [rbp + -584]
  movq [rbp + -584], rax
  movq rax, [rbp + -592]
  movq [rbp + -592], rax
  mov rax, [rax]
  movq rax, [rbp + -600]
  movq [rbp + -600], rcx
  call lm_print_str
  jmp main_block_111
main_block_111:
  jmp main_block_113
main_block_113:
  movq $1, rax
  cmpq $33, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -608]
  movq [rbp + -608], rax
  testq rax, rax
  jne main_block_116
  jmp main_block_140
main_block_116:
  jmp main_block_116
  jmp main_block_119
main_block_119:
  movq $41, rax
  cmpq $65, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -616]
  movq [rbp + -616], rax
  testq rax, rax
  jne main_block_122
  jmp main_block_136
main_block_122:
  jmp main_block_122
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rbp + -624], rcx
  movq $1, rdx
  call lm_rt_str_format
  movq rax, [rbp + -632]
  movq [rbp + -632], rcx
  movq $41, rdx
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
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -672]
  movq $1, rax
  addq $41, rax
  movq rax, [rbp + -680]
  movq $1, rax
  addq [rbp + -680], rax
  movq rax, [rbp + -688]
  jmp main_block_132
main_block_132:
  movq $41, rax
  addq $9, rax
  movq rax, [rbp + -696]
  jmp main_block_119
main_block_136:
  jmp main_block_137
main_block_137:
  movq $1, rax
  addq $17, rax
  movq rax, [rbp + -704]
  jmp main_block_113
main_block_140:
  movq [rbp + -672], rax
  cmpq $49, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -712]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -720]
  movq [rbp + -712], rcx
  movq [rbp + -720], rdx
  call lm_assert
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -728]
  movq [rbp + -728], rax
  addq $16, rax
  movq rax, [rbp + -736]
  movq [rbp + -736], rax
  movq rax, [rbp + -744]
  movq [rbp + -744], rax
  mov rax, [rax]
  movq rax, [rbp + -752]
  movq [rbp + -752], rcx
  call lm_print_str
  jmp main_block_151
main_block_151:
  movq $9, rax
  cmpq $25, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -760]
  movq [rbp + -760], rax
  testq rax, rax
  jne main_block_154
  jmp main_block_178
main_block_154:
  jmp main_block_154
  jmp main_block_155
main_block_155:
  jmp main_block_157
main_block_157:
  movq $1, rax
  cmpq $41, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -768]
  movq [rbp + -768], rax
  testq rax, rax
  jne main_block_160
  jmp main_block_173
main_block_160:
  jmp main_block_160
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -776]
  movq [rbp + -776], rcx
  movq $9, rdx
  call lm_rt_str_format
  movq rax, [rbp + -784]
  movq [rbp + -784], rcx
  movq $1, rdx
  call lm_rt_str_format
  movq rax, [rbp + -792]
  movq [rbp + -792], rax
  addq $16, rax
  movq rax, [rbp + -800]
  movq [rbp + -800], rax
  movq rax, [rbp + -808]
  movq [rbp + -808], rax
  mov rax, [rax]
  movq rax, [rbp + -816]
  movq [rbp + -816], rcx
  call lm_print_str
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -824]
  movq $9, rax
  imulq $1, rax
  movq rax, [rbp + -832]
  movq $1, rax
  addq [rbp + -832], rax
  movq rax, [rbp + -840]
  jmp main_block_170
main_block_170:
  movq $1, rax
  addq $17, rax
  movq rax, [rbp + -848]
  jmp main_block_157
main_block_173:
  jmp main_block_174
main_block_174:
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -856]
  jmp main_block_151
main_block_178:
  movq [rbp + -824], rax
  cmpq $49, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -864]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -872]
  movq [rbp + -864], rcx
  movq [rbp + -872], rdx
  call lm_assert
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -880]
  movq [rbp + -880], rcx
  movq $17, rdx
  call lm_rt_str_format
  movq rax, [rbp + -888]
  movq [rbp + -888], rcx
  movq $41, rdx
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
  jmp main_block_193
main_block_193:
  movq $17, rax
  cmpq $41, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -928]
  movq [rbp + -928], rax
  testq rax, rax
  jne main_block_195
  jmp main_block_206
main_block_195:
  jmp main_block_195
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -936]
  movq [rbp + -936], rcx
  movq $17, rdx
  call lm_rt_str_format
  movq rax, [rbp + -944]
  movq [rbp + -944], rax
  addq $16, rax
  movq rax, [rbp + -952]
  movq [rbp + -952], rax
  movq rax, [rbp + -960]
  movq [rbp + -960], rax
  mov rax, [rax]
  movq rax, [rbp + -968]
  movq [rbp + -968], rcx
  call lm_print_str
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -976]
  movq $1, rax
  addq $17, rax
  movq rax, [rbp + -984]
  jmp main_block_202
main_block_202:
  movq $17, rax
  addq $9, rax
  movq rax, [rbp + -992]
  jmp main_block_193
main_block_206:
  movq [rbp + -976], rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1000]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -1008]
  movq [rbp + -1000], rcx
  movq [rbp + -1008], rdx
  call lm_assert
  movq [rbp + -984], rax
  cmpq $73, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1016]
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
  jmp main_block_221
main_block_221:
  movq $1, rax
  cmpq $81, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -1064]
  movq [rbp + -1064], rax
  testq rax, rax
  jne main_block_224
  jmp main_block_243
main_block_224:
  jmp main_block_224
  movq $1, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1072]
  movq [rbp + -1072], rax
  testq rax, rax
  jne main_block_227
  jmp main_block_228
main_block_227:
  jmp main_block_227
  jmp main_block_239
main_block_228:
  movq $1, rax
  cmpq $57, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1080]
  movq [rbp + -1080], rax
  testq rax, rax
  jne main_block_231
  jmp main_block_232
main_block_231:
  jmp main_block_231
  jmp main_block_243
main_block_232:
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -1088]
  movq [rbp + -1088], rcx
  movq $1, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1096]
  movq [rbp + -1096], rax
  addq $16, rax
  movq rax, [rbp + -1104]
  movq [rbp + -1104], rax
  movq rax, [rbp + -1112]
  movq [rbp + -1112], rax
  mov rax, [rax]
  movq rax, [rbp + -1120]
  movq [rbp + -1120], rcx
  call lm_print_str
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -1128]
  movq $1, rax
  addq $1, rax
  movq rax, [rbp + -1136]
  jmp main_block_239
main_block_239:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -1144]
  jmp main_block_221
main_block_243:
  movq [rbp + -1128], rax
  cmpq $49, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1152]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -1160]
  movq [rbp + -1152], rcx
  movq [rbp + -1160], rdx
  call lm_assert
  movq [rbp + -1136], rax
  cmpq $145, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1168]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -1176]
  movq [rbp + -1168], rcx
  movq [rbp + -1176], rdx
  call lm_assert
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -1184]
  movq [rbp + -1184], rax
  addq $16, rax
  movq rax, [rbp + -1192]
  movq [rbp + -1192], rax
  movq rax, [rbp + -1200]
  movq [rbp + -1200], rax
  mov rax, [rax]
  movq rax, [rbp + -1208]
  movq [rbp + -1208], rcx
  call lm_print_str
  jmp main_block_259
main_block_259:
  movq $81, rax
  addq $25, rax
  movq rax, [rbp + -1216]
  movq $81, rax
  cmpq [rbp + -1216], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -1224]
  movq [rbp + -1224], rax
  testq rax, rax
  jne main_block_262
  jmp main_block_273
main_block_262:
  jmp main_block_262
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -1232]
  movq [rbp + -1232], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1240]
  movq [rbp + -1240], rax
  addq $16, rax
  movq rax, [rbp + -1248]
  movq [rbp + -1248], rax
  movq rax, [rbp + -1256]
  movq [rbp + -1256], rax
  mov rax, [rax]
  movq rax, [rbp + -1264]
  movq [rbp + -1264], rcx
  call lm_print_str
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -1272]
  movq $1, rax
  addq $81, rax
  movq rax, [rbp + -1280]
  jmp main_block_269
main_block_269:
  movq $81, rax
  addq $9, rax
  movq rax, [rbp + -1288]
  jmp main_block_259
main_block_273:
  movq [rbp + -1272], rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1296]
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -1304]
  movq [rbp + -1296], rcx
  movq [rbp + -1304], rdx
  call lm_assert
  movq [rbp + -1280], rax
  cmpq $265, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1312]
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -1320]
  movq [rbp + -1312], rcx
  movq [rbp + -1320], rdx
  call lm_assert
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -1328]
  movq [rbp + -1328], rax
  addq $16, rax
  movq rax, [rbp + -1336]
  movq [rbp + -1336], rax
  movq rax, [rbp + -1344]
  movq [rbp + -1344], rax
  mov rax, [rax]
  movq rax, [rbp + -1352]
  movq [rbp + -1352], rcx
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

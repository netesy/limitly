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
  .string "=== For Loop Tests ==="
.align 8
str_const_1:
  .string "Basic for loop (0 to 4):"
.align 8
str_const_2:
  .string "i = %s"
.align 8
str_const_3:
  .string "Basic for loop should iterate 5 times"
.align 8
str_const_4:
  .string "Sum of 0+1+2+3+4 should be 10"
.align 8
str_const_5:
  .string "For loop with increment 2:"
.align 8
str_const_6:
  .string "j = %s"
.align 8
str_const_7:
  .string "Increment loop should iterate 5 times (0,2,4,6,8)"
.align 8
str_const_8:
  .string "Sum of 0+2+4+6+8 should be 20"
.align 8
str_const_9:
  .string "Countdown loop:"
.align 8
str_const_10:
  .string "k = %s"
.align 8
str_const_11:
  .string "Countdown should iterate 5 times (5,4,3,2,1)"
.align 8
str_const_12:
  .string "Sum of 5+4+3+2+1 should be 15"
.align 8
str_const_13:
  .string "Complex condition:"
.align 8
str_const_14:
  .string "x = %s, x² = %s"
.align 8
str_const_15:
  .string "Complex condition should iterate 4 times (1,2,3,4)"
.align 8
str_const_16:
  .string "Sum of 1+2+3+4 should be 10"
.align 8
str_const_17:
  .string "Nested for loops (2x3 grid):"
.align 8
str_const_18:
  .string "(%s, %s)"
.align 8
str_const_19:
  .string "Nested loops should iterate 9 times (3x3)"
.align 8
str_const_20:
  .string "Variable scope test:"
.align 8
str_const_21:
  .string "outer: %s, inner: %s"
.align 8
str_const_22:
  .string "Outer variable should remain constant"
.align 8
str_const_23:
  .string "Inner variable should be calculated correctly"
.align 8
str_const_24:
  .string "Scope loop should iterate 4 times"
.align 8
str_const_25:
  .string "Sum of inner values should be 0+10+20+30"
.align 8
str_const_26:
  .string "Break and continue test:"
.align 8
str_const_27:
  .string "Loop value: %s"
.align 8
str_const_28:
  .string "Loop should execute 6 times (skip 3, break at 7)"
.align 8
str_const_29:
  .string "=== For Loop Tests Complete ==="
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
  sub rsp, 1160
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
  jmp main_block_7
main_block_7:
  jmp main_block_9
main_block_9:
  movq $1, rax
  cmpq $41, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne main_block_12
  jmp main_block_22
main_block_12:
  jmp main_block_12
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
  jmp main_block_19
main_block_19:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -192]
  jmp main_block_9
main_block_22:
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
  jmp main_block_35
main_block_35:
  jmp main_block_37
main_block_37:
  movq $1, rax
  cmpq $81, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  testq rax, rax
  jne main_block_40
  jmp main_block_50
main_block_40:
  jmp main_block_40
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
  jmp main_block_47
main_block_47:
  movq $1, rax
  addq $17, rax
  movq rax, [rbp + -328]
  jmp main_block_37
main_block_50:
  movq [rbp + -312], rax
  cmpq $41, rax
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
  cmpq $161, rax
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
  jmp main_block_63
main_block_63:
  jmp main_block_65
main_block_65:
  movq $41, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  testq rax, rax
  jne main_block_68
  jmp main_block_78
main_block_68:
  jmp main_block_68
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -408], rcx
  movq $41, rdx
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
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -448]
  movq $1, rax
  addq $41, rax
  movq rax, [rbp + -456]
  jmp main_block_75
main_block_75:
  movq $41, rax
  subq $9, rax
  movq rax, [rbp + -464]
  jmp main_block_65
main_block_78:
  movq [rbp + -448], rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -472]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq [rbp + -472], rcx
  movq [rbp + -480], rdx
  call lm_assert
  movq [rbp + -456], rax
  cmpq $121, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -488]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -488], rcx
  movq [rbp + -496], rdx
  call lm_assert
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -504], rax
  addq $16, rax
  movq rax, [rbp + -512]
  movq [rbp + -512], rax
  movq rax, [rbp + -520]
  movq [rbp + -520], rax
  mov rax, [rax]
  movq rax, [rbp + -528]
  movq [rbp + -528], rcx
  call lm_print_str
  jmp main_block_91
main_block_91:
  jmp main_block_93
main_block_93:
  movq $9, rax
  imulq $9, rax
  movq rax, [rbp + -536]
  movq [rbp + -536], rax
  cmpq $161, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -544]
  movq [rbp + -544], rax
  testq rax, rax
  jne main_block_97
  jmp main_block_110
main_block_97:
  jmp main_block_97
  movq $9, rax
  imulq $9, rax
  movq rax, [rbp + -552]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -560]
  movq [rbp + -560], rcx
  movq $9, rdx
  call lm_rt_str_format
  movq rax, [rbp + -568]
  movq [rbp + -568], rcx
  movq [rbp + -552], rdx
  call lm_rt_str_format
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
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -608]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -616]
  jmp main_block_107
main_block_107:
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -624]
  jmp main_block_93
main_block_110:
  movq [rbp + -608], rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -632]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -632], rcx
  movq [rbp + -640], rdx
  call lm_assert
  movq [rbp + -616], rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -648]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -656]
  movq [rbp + -648], rcx
  movq [rbp + -656], rdx
  call lm_assert
  movq [rel str_const_17], rcx
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
  call lm_print_str
  jmp main_block_123
main_block_123:
  jmp main_block_125
main_block_125:
  movq $1, rax
  cmpq $17, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -696]
  movq [rbp + -696], rax
  testq rax, rax
  jne main_block_128
  jmp main_block_155
main_block_128:
  jmp main_block_128
  jmp main_block_129
main_block_129:
  jmp main_block_131
main_block_131:
  movq $1, rax
  cmpq $25, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -704]
  movq [rbp + -704], rax
  testq rax, rax
  jne main_block_134
  jmp main_block_151
main_block_134:
  jmp main_block_134
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -712]
  movq [rbp + -712], rcx
  movq $1, rdx
  call lm_rt_str_format
  movq rax, [rbp + -720]
  movq [rbp + -720], rcx
  movq $1, rdx
  call lm_rt_str_format
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
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -760]
  movq $1, rax
  imulq $81, rax
  movq rax, [rbp + -768]
  movq $1, rax
  imulq $81, rax
  movq rax, [rbp + -776]
  movq [rbp + -776], rax
  addq $1, rax
  movq rax, [rbp + -784]
  movq $1, rax
  addq [rbp + -784], rax
  movq rax, [rbp + -792]
  jmp main_block_148
main_block_148:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -800]
  jmp main_block_131
main_block_151:
  jmp main_block_152
main_block_152:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -808]
  jmp main_block_125
main_block_155:
  movq [rbp + -760], rax
  cmpq $73, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -816]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -824]
  movq [rbp + -816], rcx
  movq [rbp + -824], rdx
  call lm_assert
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -832]
  movq [rbp + -832], rax
  addq $16, rax
  movq rax, [rbp + -840]
  movq [rbp + -840], rax
  movq rax, [rbp + -848]
  movq [rbp + -848], rax
  mov rax, [rax]
  movq rax, [rbp + -856]
  movq [rbp + -856], rcx
  call lm_print_str
  jmp main_block_165
main_block_165:
  jmp main_block_167
main_block_167:
  movq $1, rax
  cmpq $33, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -864]
  movq [rbp + -864], rax
  testq rax, rax
  jne main_block_170
  jmp main_block_194
main_block_170:
  jmp main_block_170
  movq $1, rax
  imulq $81, rax
  movq rax, [rbp + -872]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -880]
  movq [rbp + -880], rcx
  movq $801, rdx
  call lm_rt_str_format
  movq rax, [rbp + -888]
  movq [rbp + -888], rcx
  movq [rbp + -872], rdx
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
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -928]
  movq $1, rax
  addq [rbp + -872], rax
  movq rax, [rbp + -936]
  movq $801, rax
  cmpq $801, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -944]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -952]
  movq [rbp + -944], rcx
  movq [rbp + -952], rdx
  call lm_assert
  movq $1, rax
  imulq $81, rax
  movq rax, [rbp + -960]
  movq [rbp + -872], rax
  cmpq [rbp + -960], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -968]
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -976]
  movq [rbp + -968], rcx
  movq [rbp + -976], rdx
  call lm_assert
  jmp main_block_191
main_block_191:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -984]
  jmp main_block_167
main_block_194:
  movq [rbp + -928], rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -992]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -1000]
  movq [rbp + -992], rcx
  movq [rbp + -1000], rdx
  call lm_assert
  movq [rbp + -936], rax
  cmpq $481, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1008]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -1016]
  movq [rbp + -1008], rcx
  movq [rbp + -1016], rdx
  call lm_assert
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -1024]
  movq [rbp + -1024], rax
  addq $16, rax
  movq rax, [rbp + -1032]
  movq [rbp + -1032], rax
  movq rax, [rbp + -1040]
  movq [rbp + -1040], rax
  mov rax, [rax]
  movq rax, [rbp + -1048]
  movq [rbp + -1048], rcx
  call lm_print_str
  jmp main_block_206
main_block_206:
  jmp main_block_208
main_block_208:
  movq $1, rax
  cmpq $81, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -1056]
  movq [rbp + -1056], rax
  testq rax, rax
  jne main_block_211
  jmp main_block_228
main_block_211:
  jmp main_block_211
  movq $1, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1064]
  movq [rbp + -1064], rax
  testq rax, rax
  jne main_block_214
  jmp main_block_215
main_block_214:
  jmp main_block_214
  jmp main_block_225
main_block_215:
  movq $1, rax
  cmpq $57, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1072]
  movq [rbp + -1072], rax
  testq rax, rax
  jne main_block_218
  jmp main_block_219
main_block_218:
  jmp main_block_218
  jmp main_block_228
main_block_219:
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -1080]
  movq [rbp + -1080], rcx
  movq $1, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1088]
  movq [rbp + -1088], rax
  addq $16, rax
  movq rax, [rbp + -1096]
  movq [rbp + -1096], rax
  movq rax, [rbp + -1104]
  movq [rbp + -1104], rax
  mov rax, [rax]
  movq rax, [rbp + -1112]
  movq [rbp + -1112], rcx
  call lm_print_str
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -1120]
  jmp main_block_225
main_block_225:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -1128]
  jmp main_block_208
main_block_228:
  movq [rbp + -1120], rax
  cmpq $49, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1136]
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -1144]
  movq [rbp + -1136], rcx
  movq [rbp + -1144], rdx
  call lm_assert
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -1152]
  movq [rbp + -1152], rax
  addq $16, rax
  movq rax, [rbp + -1160]
  movq [rbp + -1160], rax
  movq rax, [rbp + -1168]
  movq [rbp + -1168], rax
  mov rax, [rax]
  movq rax, [rbp + -1176]
  movq [rbp + -1176], rcx
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

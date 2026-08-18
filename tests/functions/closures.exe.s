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
  .string "=== Closure Tests ==="
.align 8
str_const_1:
  .string "
--- Test 1: Simple Closure ---"
.align 8
str_const_2:
  .string "Hello"
.align 8
str_const_3:
  .string "Goodbye"
.align 8
str_const_4:
  .string "World"
.align 8
str_const_5:
  .string "Friend"
.align 8
str_const_6:
  .string "sayHello('World') = %s"
.align 8
str_const_7:
  .string "sayGoodbye('Friend') = %s"
.align 8
str_const_8:
  .string "Hello, World!"
.align 8
str_const_9:
  .string "Closure should capture greeting and format correctly"
.align 8
str_const_10:
  .string "Goodbye, Friend!"
.align 8
str_const_11:
  .string "Closure should maintain separate captured state"
.align 8
str_const_12:
  .string "
--- Test 2: Counter Closure ---"
.align 8
str_const_13:
  .string "counter1: %s, %s, %s"
.align 8
str_const_14:
  .string "counter2: %s, %s"
.align 8
str_const_15:
  .string "First counter should start at 1"
.align 8
str_const_16:
  .string "First counter should increment to 2"
.align 8
str_const_17:
  .string "First counter should increment to 3"
.align 8
str_const_18:
  .string "Second counter should be independent and start at 1"
.align 8
str_const_19:
  .string "Second counter should increment independently to 2"
.align 8
str_const_20:
  .string "
--- Test 3: Multiple Variable Capture ---"
.align 8
str_const_21:
  .string "Calculator starting at 10: +5=%s, +3=%s, +7=%s"
.align 8
str_const_22:
  .string "Calculator should add 5 to initial 10"
.align 8
str_const_23:
  .string "Calculator should add 3 to previous 15"
.align 8
str_const_24:
  .string "Calculator should add 7 to previous 18"
.align 8
str_const_25:
  .string "
--- Test 4: Nested Closures ---"
.align 8
str_const_26:
  .string "inner1: %s, %s"
.align 8
str_const_27:
  .string "inner2: %s, %s"
.align 8
str_const_28:
  .string "First inner closure should start at outerCount+1 (10+1)"
.align 8
str_const_29:
  .string "First inner closure should increment to 12"
.align 8
str_const_30:
  .string "Second inner closure should start at new outerCount+1 (20+1)"
.align 8
str_const_31:
  .string "Second inner closure should increment to 22"
.align 8
str_const_32:
  .string "
--- Test 5: Arithmetic Closures ---"
.align 8
str_const_33:
  .string "add5(7) = %s"
.align 8
str_const_34:
  .string "mult3(4) = %s"
.align 8
str_const_35:
  .string "Adder closure should add 5 to 7"
.align 8
str_const_36:
  .string "Multiplier closure should multiply 4 by 3"
.align 8
str_const_37:
  .string "
--- Test 6: Closure Memory Management ---"
.align 8
str_const_38:
  .string "Temporary closure %s result: %s"
.align 8
str_const_39:
  .string "Temporary closure should double captured value"
.align 8
str_const_40:
  .string "
--- Test 7: Conditional Closures ---"
.align 8
str_const_41:
  .string "Above threshold: 15 > 10"
.align 8
str_const_42:
  .string "Conditional closure should detect above threshold"
.align 8
str_const_43:
  .string "Below threshold: 5 <= 10"
.align 8
str_const_44:
  .string "Conditional closure should detect below threshold"
.align 8
str_const_45:
  .string "
=== Closure Tests Complete ==="
.align 8
str_const_46:
  .string "__lambda_7"
.align 8
str_const_47:
  .string "__lambda_2"
.align 8
str_const_48:
  .string "__lambda_8"
.align 8
str_const_49:
  .string "Above threshold: %s > %s"
.align 8
str_const_50:
  .string "Below threshold: %s <= %s"
.align 8
str_const_51:
  .string "__lambda_3"
.align 8
str_const_52:
  .string "__lambda_1"
.align 8
str_const_53:
  .string "__lambda_4"
.align 8
str_const_54:
  .string "__lambda_0"
.align 8
str_const_55:
  .string "__lambda_5"
.align 8
str_const_56:
  .string ", "
.align 8
str_const_57:
  .string "!"
.align 8
str_const_58:
  .string "__lambda_6"
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
  sub rsp, 1400
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
  movq [rbp + -128], rcx
  call createGreeter
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rcx
  call createGreeter
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  call r5
  movq rax, [rbp + -152]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rcx
  call r8
  movq rax, [rbp + -168]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -176], rcx
  movq [rbp + -152], rdx
  call lm_rt_str_format
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
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -216], rcx
  movq [rbp + -168], rdx
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
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -152], rax
  cmpq [rbp + -256], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -264]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -264], rcx
  movq [rbp + -272], rdx
  call lm_assert
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -168], rax
  cmpq [rbp + -280], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -288]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -288], rcx
  movq [rbp + -296], rdx
  call lm_assert
  movq [rel str_const_12], rcx
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
  call createCounter
  call createCounter
  call r32
  movq rax, [rbp + -336]
  call r32
  movq rax, [rbp + -344]
  call r32
  movq rax, [rbp + -352]
  call r34
  movq rax, [rbp + -360]
  call r34
  movq rax, [rbp + -368]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -376], rcx
  movq [rbp + -336], rdx
  call lm_rt_str_format
  movq rax, [rbp + -384]
  movq [rbp + -384], rcx
  movq [rbp + -344], rdx
  call lm_rt_str_format
  movq rax, [rbp + -392]
  movq [rbp + -392], rcx
  movq [rbp + -352], rdx
  call lm_rt_str_format
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
  movq [rbp + -432], rcx
  movq [rbp + -360], rdx
  call lm_rt_str_format
  movq rax, [rbp + -440]
  movq [rbp + -440], rcx
  movq [rbp + -368], rdx
  call lm_rt_str_format
  movq rax, [rbp + -448]
  movq [rbp + -448], rax
  addq $16, rax
  movq rax, [rbp + -456]
  movq [rbp + -456], rax
  movq rax, [rbp + -464]
  movq [rbp + -464], rax
  mov rax, [rax]
  movq rax, [rbp + -472]
  movq [rbp + -472], rcx
  call lm_print_str
  movq [rbp + -336], rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -480]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -488]
  movq [rbp + -480], rcx
  movq [rbp + -488], rdx
  call lm_assert
  movq [rbp + -344], rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -496]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -496], rcx
  movq [rbp + -504], rdx
  call lm_assert
  movq [rbp + -352], rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -512]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -512], rcx
  movq [rbp + -520], rdx
  call lm_assert
  movq [rbp + -360], rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -528]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -536]
  movq [rbp + -528], rcx
  movq [rbp + -536], rdx
  call lm_assert
  movq [rbp + -368], rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -544]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -552]
  movq [rbp + -544], rcx
  movq [rbp + -552], rdx
  call lm_assert
  movq [rel str_const_20], rcx
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
  call lm_print_str
  movq $81, rcx
  call createCalculator
  movq $41, rcx
  call r78
  movq rax, [rbp + -592]
  movq $25, rcx
  call r78
  movq rax, [rbp + -600]
  movq $57, rcx
  call r78
  movq rax, [rbp + -608]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -616], rcx
  movq [rbp + -592], rdx
  call lm_rt_str_format
  movq rax, [rbp + -624]
  movq [rbp + -624], rcx
  movq [rbp + -600], rdx
  call lm_rt_str_format
  movq rax, [rbp + -632]
  movq [rbp + -632], rcx
  movq [rbp + -608], rdx
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
  movq [rbp + -592], rax
  cmpq $121, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -672]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -680]
  movq [rbp + -672], rcx
  movq [rbp + -680], rdx
  call lm_assert
  movq [rbp + -600], rax
  cmpq $145, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -688]
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -696]
  movq [rbp + -688], rcx
  movq [rbp + -696], rdx
  call lm_assert
  movq [rbp + -608], rax
  cmpq $201, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -704]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -712]
  movq [rbp + -704], rcx
  movq [rbp + -712], rdx
  call lm_assert
  movq [rel str_const_25], rcx
  call lm_box_string
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
  movq $81, rcx
  call createNestedCounter
  call r109
  movq rax, [rbp + -752]
  call r109
  movq rax, [rbp + -760]
  call r111
  movq rax, [rbp + -768]
  call r111
  movq rax, [rbp + -776]
  call r113
  movq rax, [rbp + -784]
  call r113
  movq rax, [rbp + -792]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -800]
  movq [rbp + -800], rcx
  movq [rbp + -768], rdx
  call lm_rt_str_format
  movq rax, [rbp + -808]
  movq [rbp + -808], rcx
  movq [rbp + -776], rdx
  call lm_rt_str_format
  movq rax, [rbp + -816]
  movq [rbp + -816], rax
  addq $16, rax
  movq rax, [rbp + -824]
  movq [rbp + -824], rax
  movq rax, [rbp + -832]
  movq [rbp + -832], rax
  mov rax, [rax]
  movq rax, [rbp + -840]
  movq [rbp + -840], rcx
  call lm_print_str
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -848]
  movq [rbp + -848], rcx
  movq [rbp + -784], rdx
  call lm_rt_str_format
  movq rax, [rbp + -856]
  movq [rbp + -856], rcx
  movq [rbp + -792], rdx
  call lm_rt_str_format
  movq rax, [rbp + -864]
  movq [rbp + -864], rax
  addq $16, rax
  movq rax, [rbp + -872]
  movq [rbp + -872], rax
  movq rax, [rbp + -880]
  movq [rbp + -880], rax
  mov rax, [rax]
  movq rax, [rbp + -888]
  movq [rbp + -888], rcx
  call lm_print_str
  movq [rbp + -768], rax
  cmpq $89, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -896]
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -904]
  movq [rbp + -896], rcx
  movq [rbp + -904], rdx
  call lm_assert
  movq [rbp + -776], rax
  cmpq $97, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -912]
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -920]
  movq [rbp + -912], rcx
  movq [rbp + -920], rdx
  call lm_assert
  movq [rbp + -784], rax
  cmpq $169, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -928]
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -936]
  movq [rbp + -928], rcx
  movq [rbp + -936], rdx
  call lm_assert
  movq [rbp + -792], rax
  cmpq $177, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -944]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -952]
  movq [rbp + -944], rcx
  movq [rbp + -952], rdx
  call lm_assert
  movq [rel str_const_32], rcx
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
  movq $41, rcx
  call createAdder
  movq $25, rcx
  call createMultiplier
  movq $57, rcx
  call r150
  movq rax, [rbp + -992]
  movq $33, rcx
  call r153
  movq rax, [rbp + -1000]
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -1008]
  movq [rbp + -1008], rcx
  movq [rbp + -992], rdx
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
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -1048]
  movq [rbp + -1048], rcx
  movq [rbp + -1000], rdx
  call lm_rt_str_format
  movq rax, [rbp + -1056]
  movq [rbp + -1056], rax
  addq $16, rax
  movq rax, [rbp + -1064]
  movq [rbp + -1064], rax
  movq rax, [rbp + -1072]
  movq [rbp + -1072], rax
  mov rax, [rax]
  movq rax, [rbp + -1080]
  movq [rbp + -1080], rcx
  call lm_print_str
  movq [rbp + -992], rax
  cmpq $97, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1088]
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -1096]
  movq [rbp + -1088], rcx
  movq [rbp + -1096], rdx
  call lm_assert
  movq [rbp + -1000], rax
  cmpq $97, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1104]
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -1112]
  movq [rbp + -1104], rcx
  movq [rbp + -1112], rdx
  call lm_assert
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -1120]
  movq [rbp + -1120], rax
  addq $16, rax
  movq rax, [rbp + -1128]
  movq [rbp + -1128], rax
  movq rax, [rbp + -1136]
  movq [rbp + -1136], rax
  mov rax, [rax]
  movq rax, [rbp + -1144]
  movq [rbp + -1144], rcx
  call lm_print_str
  jmp main_block_183
main_block_183:
  jmp main_block_185
main_block_185:
  movq $9, rax
  cmpq $41, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -1152]
  movq [rbp + -1152], rax
  testq rax, rax
  jne main_block_188
  jmp main_block_206
main_block_188:
  jmp main_block_188
  movq $9, rcx
  call createTemporaryClosure
  call r181
  movq rax, [rbp + -1160]
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -1168]
  movq [rbp + -1168], rcx
  movq $9, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1176]
  movq [rbp + -1176], rcx
  movq [rbp + -1160], rdx
  call lm_rt_str_format
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
  movq $9, rax
  imulq $17, rax
  movq rax, [rbp + -1216]
  movq [rbp + -1160], rax
  cmpq [rbp + -1216], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1224]
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -1232]
  movq [rbp + -1224], rcx
  movq [rbp + -1232], rdx
  call lm_assert
  jmp main_block_203
main_block_203:
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -1240]
  jmp main_block_185
main_block_206:
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -1248]
  movq [rbp + -1248], rax
  addq $16, rax
  movq rax, [rbp + -1256]
  movq [rbp + -1256], rax
  movq rax, [rbp + -1264]
  movq [rbp + -1264], rax
  mov rax, [rax]
  movq rax, [rbp + -1272]
  movq [rbp + -1272], rcx
  call lm_print_str
  movq $81, rcx
  call createConditionalClosure
  movq $121, rcx
  call r198
  movq rax, [rbp + -1280]
  movq $41, rcx
  call r198
  movq rax, [rbp + -1288]
  movq [rbp + -1280], rax
  addq $16, rax
  movq rax, [rbp + -1296]
  movq [rbp + -1296], rax
  movq rax, [rbp + -1304]
  movq [rbp + -1304], rax
  mov rax, [rax]
  movq rax, [rbp + -1312]
  movq [rbp + -1312], rcx
  call lm_print_str
  movq [rbp + -1288], rax
  addq $16, rax
  movq rax, [rbp + -1320]
  movq [rbp + -1320], rax
  movq rax, [rbp + -1328]
  movq [rbp + -1328], rax
  mov rax, [rax]
  movq rax, [rbp + -1336]
  movq [rbp + -1336], rcx
  call lm_print_str
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -1344]
  movq [rbp + -1280], rax
  cmpq [rbp + -1344], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1352]
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -1360]
  movq [rbp + -1352], rcx
  movq [rbp + -1360], rdx
  call lm_assert
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -1368]
  movq [rbp + -1288], rax
  cmpq [rbp + -1368], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1376]
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -1384]
  movq [rbp + -1376], rcx
  movq [rbp + -1384], rdx
  call lm_assert
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -1392]
  movq [rbp + -1392], rax
  addq $16, rax
  movq rax, [rbp + -1400]
  movq [rbp + -1400], rax
  movq rax, [rbp + -1408]
  movq [rbp + -1408], rax
  mov rax, [rax]
  movq rax, [rbp + -1416]
  movq [rbp + -1416], rcx
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

.globl createTemporaryClosure
createTemporaryClosure:
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
createTemporaryClosure_entry:
createTemporaryClosure_block_0:
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $0, rax
  jmp createTemporaryClosure_epilogue
createTemporaryClosure_epilogue:
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
.Lfunc_end_createTemporaryClosure:

.globl __lambda_7
__lambda_7:
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
__lambda_7_entry:
__lambda_7_block_0:
  movq $0, rax
  imulq $17, rax
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  jmp __lambda_7_epilogue
__lambda_7_epilogue:
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
.Lfunc_end___lambda_7:

.globl createCalculator
createCalculator:
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
createCalculator_entry:
createCalculator_block_0:
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $0, rax
  jmp createCalculator_epilogue
createCalculator_epilogue:
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
.Lfunc_end_createCalculator:

.globl createConditionalClosure
createConditionalClosure:
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
createConditionalClosure_entry:
createConditionalClosure_block_0:
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $0, rax
  jmp createConditionalClosure_epilogue
createConditionalClosure_epilogue:
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
.Lfunc_end_createConditionalClosure:

.globl __lambda_1
__lambda_1:
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
__lambda_1_entry:
__lambda_1_block_0:
  movq $0, rax
  addq $9, rax
  movq rax, [rbp + -64]
  movq $0, rax
  jmp __lambda_1_epilogue
__lambda_1_epilogue:
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
.Lfunc_end___lambda_1:

.globl __lambda_4
__lambda_4:
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
__lambda_4_entry:
__lambda_4_block_0:
  movq $0, rax
  addq $9, rax
  movq rax, [rbp + -64]
  movq $0, rax
  jmp __lambda_4_epilogue
__lambda_4_epilogue:
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
.Lfunc_end___lambda_4:

.globl __lambda_8
__lambda_8:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 104
  mov [rbp + -64], rcx
__lambda_8_entry:
__lambda_8_block_0:
  movq [rbp + -64], rax
  cmpq $0, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne __lambda_8_block_4
  jmp __lambda_8_block_11
__lambda_8_block_4:
  jmp __lambda_8_block_4
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  call lm_rt_str_format
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp __lambda_8_epilogue
__lambda_8_block_11:
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  movq [rbp + -64], rdx
  call lm_rt_str_format
  movq rax, [rbp + -112]
  movq [rbp + -112], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  jmp __lambda_8_epilogue
__lambda_8_epilogue:
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
.Lfunc_end___lambda_8:

.globl createNestedCounter
createNestedCounter:
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
createNestedCounter_entry:
createNestedCounter_block_0:
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $0, rax
  jmp createNestedCounter_epilogue
createNestedCounter_epilogue:
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
.Lfunc_end_createNestedCounter:

.globl __lambda_2
__lambda_2:
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
__lambda_2_entry:
__lambda_2_block_0:
  movq $0, rax
  addq [rbp + -64], rax
  movq rax, [rbp + -72]
  movq $0, rax
  jmp __lambda_2_epilogue
__lambda_2_epilogue:
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
.Lfunc_end___lambda_2:

.globl createCounter
createCounter:
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
createCounter_entry:
createCounter_block_0:
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq $0, rax
  jmp createCounter_epilogue
createCounter_epilogue:
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
.Lfunc_end_createCounter:

.globl __lambda_3
__lambda_3:
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
__lambda_3_entry:
__lambda_3_block_0:
  movq $0, rax
  addq $0, rax
  movq rax, [rbp + -64]
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $0, rax
  jmp __lambda_3_epilogue
__lambda_3_epilogue:
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
.Lfunc_end___lambda_3:

.globl createGreeter
createGreeter:
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
createGreeter_entry:
createGreeter_block_0:
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $0, rax
  jmp createGreeter_epilogue
createGreeter_epilogue:
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
.Lfunc_end_createGreeter:

.globl __lambda_5
__lambda_5:
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
__lambda_5_entry:
__lambda_5_block_0:
  movq $0, rax
  addq [rbp + -64], rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp __lambda_5_epilogue
__lambda_5_epilogue:
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
.Lfunc_end___lambda_5:

.globl createAdder
createAdder:
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
createAdder_entry:
createAdder_block_0:
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $0, rax
  jmp createAdder_epilogue
createAdder_epilogue:
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
.Lfunc_end_createAdder:

.globl __lambda_0
__lambda_0:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
__lambda_0_entry:
__lambda_0_block_0:
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $0, rcx
  movq [rbp + -72], rdx
  call lm_str_concat
  movq rax, [rbp + -80]
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  call lm_str_concat
  movq rax, [rbp + -88]
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -88], rcx
  movq [rbp + -96], rdx
  call lm_str_concat
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  jmp __lambda_0_epilogue
__lambda_0_epilogue:
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
.Lfunc_end___lambda_0:

.globl __lambda_6
__lambda_6:
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
__lambda_6_entry:
__lambda_6_block_0:
  movq [rbp + -64], rax
  imulq $0, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp __lambda_6_epilogue
__lambda_6_epilogue:
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
.Lfunc_end___lambda_6:

.globl createMultiplier
createMultiplier:
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
createMultiplier_entry:
createMultiplier_block_0:
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $0, rax
  jmp createMultiplier_epilogue
createMultiplier_epilogue:
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
.Lfunc_end_createMultiplier:

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

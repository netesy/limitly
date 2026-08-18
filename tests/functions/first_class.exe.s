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
  .string " === First - Class Function Tests === "
.align 8
str_const_1:
  .string "
 --- Test 1: Functions as Variables --- "
.align 8
str_const_2:
  .string "add"
.align 8
str_const_3:
  .string "multiply"
.align 8
str_const_4:
  .string "addFunc(3, 4) = %s"
.align 8
str_const_5:
  .string "multFunc(3, 4) = %s"
.align 8
str_const_6:
  .string "Function stored in variable should work correctly"
.align 8
str_const_7:
  .string "Function stored in variable should work correctly"
.align 8
str_const_8:
  .string "
 --- Test 2: Functions as Parameters --- "
.align 8
str_const_9:
  .string "add"
.align 8
str_const_10:
  .string "multiply"
.align 8
str_const_11:
  .string "applyOperation(6, 7, add) = %s"
.align 8
str_const_12:
  .string "applyOperation(6, 7, multiply) = %s"
.align 8
str_const_13:
  .string "Function passed as parameter should work correctly"
.align 8
str_const_14:
  .string "Function passed as parameter should work correctly"
.align 8
str_const_15:
  .string "
 --- Test 3: Functions Returning Functions --- "
.align 8
str_const_16:
  .string "addFive(3) = %s"
.align 8
str_const_17:
  .string "addTen(7) = %s"
.align 8
str_const_18:
  .string "Function returning function should work correctly"
.align 8
str_const_19:
  .string "Function returning function should work correctly"
.align 8
str_const_20:
  .string "
 --- Test 4: Lambda Expressions --- "
.align 8
str_const_21:
  .string "__lambda_8"
.align 8
str_const_22:
  .string "__lambda_9"
.align 8
str_const_23:
  .string "doubler(5) = %s"
.align 8
str_const_24:
  .string "tripler(5) = %s"
.align 8
str_const_25:
  .string "Lambda expression should work correctly"
.align 8
str_const_26:
  .string "Lambda expression should work correctly"
.align 8
str_const_27:
  .string "
 --- Test 5: Function Composition --- "
.align 8
str_const_28:
  .string "increment"
.align 8
str_const_29:
  .string "square"
.align 8
str_const_30:
  .string "square"
.align 8
str_const_31:
  .string "increment"
.align 8
str_const_32:
  .string "squareThenIncrement(4) = %s"
.align 8
str_const_33:
  .string "incrementThenSquare(4) = %s"
.align 8
str_const_34:
  .string "Function composition should work: (4^2)+1 = 17"
.align 8
str_const_35:
  .string "Function composition should work: (4+1)^2 = 25"
.align 8
str_const_36:
  .string "
 --- Test 6: Function Collections --- "
.align 8
str_const_37:
  .string "func1(5) = %s"
.align 8
str_const_38:
  .string "func2(5) = %s"
.align 8
str_const_39:
  .string "func3(5) = %s"
.align 8
str_const_40:
  .string "Function from tuple should work: 5+1 = 6"
.align 8
str_const_41:
  .string "Function from tuple should work: 5*2 = 10"
.align 8
str_const_42:
  .string "Function from tuple should work: 5*5 = 25"
.align 8
str_const_43:
  .string "
 --- Test 7: Conditional Function Selection --- "
.align 8
str_const_44:
  .string "addOp(3, 4) = %s"
.align 8
str_const_45:
  .string "multOp(3, 4) = %s"
.align 8
str_const_46:
  .string "Conditional function selection should return add function"
.align 8
str_const_47:
  .string "Conditional function selection should return multiply function"
.align 8
str_const_48:
  .string "
 --- Test 8: Function Factory --- "
.align 8
str_const_49:
  .string "Result"
.align 8
str_const_50:
  .string "Value"
.align 8
str_const_51:
  .string "Result: 20"
.align 8
str_const_52:
  .string "Function factory should work correctly"
.align 8
str_const_53:
  .string "Value: 15"
.align 8
str_const_54:
  .string "Function factory should work correctly"
.align 8
str_const_55:
  .string "
 === First - Class Function Tests Complete === "
.align 8
str_const_56:
  .string "__lambda_7"
.align 8
str_const_57:
  .string "__lambda_5"
.align 8
str_const_58:
  .string "__lambda_6"
.align 8
str_const_59:
  .string "__lambda_0"
.align 8
str_const_60:
  .string "%s: %s"
.align 8
str_const_61:
  .string "__lambda_1"
.align 8
str_const_62:
  .string "__lambda_2"
.align 8
str_const_63:
  .string "__lambda_3"
.align 8
str_const_64:
  .string "__lambda_4"
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
  sub rsp, 1512
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
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $25, rcx
  movq $33, rdx
  call r4
  movq rax, [rbp + -144]
  movq $25, rcx
  movq $33, rdx
  call r6
  movq rax, [rbp + -152]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rcx
  movq [rbp + -144], rdx
  call lm_rt_str_format
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  addq $16, rax
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  mov rax, [rax]
  movq rax, [rbp + -192]
  movq [rbp + -192], rcx
  call lm_print_str
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  movq [rbp + -152], rdx
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
  movq [rbp + -144], rax
  cmpq $57, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq [rbp + -152], rax
  cmpq $97, rax
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
  movq $49, rcx
  movq $57, rdx
  movq [rbp + -304], r8
  call applyOperation
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq $49, rcx
  movq $57, rdx
  movq [rbp + -312], r8
  call applyOperation
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -320], rcx
  movq $r35, rdx
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
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -360], rcx
  movq $r40, rdx
  call lm_rt_str_format
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
  movq $r35, rax
  cmpq $105, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -400]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -400], rcx
  movq [rbp + -408], rdx
  call lm_assert
  movq $r40, rax
  cmpq $337, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -416]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -416], rcx
  movq [rbp + -424], rdx
  call lm_assert
  movq [rel str_const_15], rcx
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
  call lm_print_str
  movq $41, rcx
  call createAdder
  movq $81, rcx
  call createAdder
  movq $25, rcx
  call r59
  movq rax, [rbp + -464]
  movq $57, rcx
  call r62
  movq rax, [rbp + -472]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq [rbp + -480], rcx
  movq [rbp + -464], rdx
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
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -520], rcx
  movq [rbp + -472], rdx
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
  movq [rbp + -464], rax
  cmpq $65, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -560]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -568]
  movq [rbp + -560], rcx
  movq [rbp + -568], rdx
  call lm_assert
  movq [rbp + -472], rax
  cmpq $137, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -576]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -584]
  movq [rbp + -576], rcx
  movq [rbp + -584], rdx
  call lm_assert
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
  call lm_print_str
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -632]
  movq $41, rcx
  call r87
  movq rax, [rbp + -640]
  movq $41, rcx
  call r90
  movq rax, [rbp + -648]
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -656]
  movq [rbp + -656], rcx
  movq [rbp + -640], rdx
  call lm_rt_str_format
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
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -696]
  movq [rbp + -696], rcx
  movq [rbp + -648], rdx
  call lm_rt_str_format
  movq rax, [rbp + -704]
  movq [rbp + -704], rax
  addq $16, rax
  movq rax, [rbp + -712]
  movq [rbp + -712], rax
  movq rax, [rbp + -720]
  movq [rbp + -720], rax
  mov rax, [rax]
  movq rax, [rbp + -728]
  movq [rbp + -728], rcx
  call lm_print_str
  movq [rbp + -640], rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -736]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -744]
  movq [rbp + -736], rcx
  movq [rbp + -744], rdx
  call lm_assert
  movq [rbp + -648], rax
  cmpq $121, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -752]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -760]
  movq [rbp + -752], rcx
  movq [rbp + -760], rdx
  call lm_assert
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -768]
  movq [rbp + -768], rax
  addq $16, rax
  movq rax, [rbp + -776]
  movq [rbp + -776], rax
  movq rax, [rbp + -784]
  movq [rbp + -784], rax
  mov rax, [rax]
  movq rax, [rbp + -792]
  movq [rbp + -792], rcx
  call lm_print_str
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -800]
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -808]
  movq [rbp + -800], rcx
  movq [rbp + -808], rdx
  call compose
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -816]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -824]
  movq [rbp + -816], rcx
  movq [rbp + -824], rdx
  call compose
  movq $33, rcx
  call r116
  movq rax, [rbp + -832]
  movq $33, rcx
  call r120
  movq rax, [rbp + -840]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -848]
  movq [rbp + -848], rcx
  movq [rbp + -832], rdx
  call lm_rt_str_format
  movq rax, [rbp + -856]
  movq [rbp + -856], rax
  addq $16, rax
  movq rax, [rbp + -864]
  movq [rbp + -864], rax
  movq rax, [rbp + -872]
  movq [rbp + -872], rax
  mov rax, [rax]
  movq rax, [rbp + -880]
  movq [rbp + -880], rcx
  call lm_print_str
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -888]
  movq [rbp + -888], rcx
  movq [rbp + -840], rdx
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
  movq [rbp + -832], rax
  cmpq $137, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -928]
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -936]
  movq [rbp + -928], rcx
  movq [rbp + -936], rdx
  call lm_assert
  movq [rbp + -840], rax
  cmpq $201, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -944]
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -952]
  movq [rbp + -944], rcx
  movq [rbp + -952], rdx
  call lm_assert
  movq [rel str_const_36], rcx
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
  call createFunctionSet
  movq $41, rcx
  call 
  movq rax, [rbp + -992]
  movq $41, rcx
  call 
  movq rax, [rbp + -1000]
  movq $41, rcx
  call 
  movq rax, [rbp + -1008]
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -1016]
  movq [rbp + -1016], rcx
  movq [rbp + -992], rdx
  call lm_rt_str_format
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
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -1056]
  movq [rbp + -1056], rcx
  movq [rbp + -1000], rdx
  call lm_rt_str_format
  movq rax, [rbp + -1064]
  movq [rbp + -1064], rax
  addq $16, rax
  movq rax, [rbp + -1072]
  movq [rbp + -1072], rax
  movq rax, [rbp + -1080]
  movq [rbp + -1080], rax
  mov rax, [rax]
  movq rax, [rbp + -1088]
  movq [rbp + -1088], rcx
  call lm_print_str
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -1096]
  movq [rbp + -1096], rcx
  movq [rbp + -1008], rdx
  call lm_rt_str_format
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
  movq [rbp + -992], rax
  cmpq $49, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1136]
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -1144]
  movq [rbp + -1136], rcx
  movq [rbp + -1144], rdx
  call lm_assert
  movq [rbp + -1000], rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1152]
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -1160]
  movq [rbp + -1152], rcx
  movq [rbp + -1160], rdx
  call lm_assert
  movq [rbp + -1008], rax
  cmpq $201, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1168]
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -1176]
  movq [rbp + -1168], rcx
  movq [rbp + -1176], rdx
  call lm_assert
  movq [rel str_const_43], rcx
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
  movq $18, rcx
  call selectOperation
  movq $10, rcx
  call selectOperation
  movq $25, rcx
  movq $33, rdx
  call r184
  movq rax, [rbp + -1216]
  movq $25, rcx
  movq $33, rdx
  call r187
  movq rax, [rbp + -1224]
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -1232]
  movq [rbp + -1232], rcx
  movq [rbp + -1216], rdx
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
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -1272]
  movq [rbp + -1272], rcx
  movq [rbp + -1224], rdx
  call lm_rt_str_format
  movq rax, [rbp + -1280]
  movq [rbp + -1280], rax
  addq $16, rax
  movq rax, [rbp + -1288]
  movq [rbp + -1288], rax
  movq rax, [rbp + -1296]
  movq [rbp + -1296], rax
  mov rax, [rax]
  movq rax, [rbp + -1304]
  movq [rbp + -1304], rcx
  call lm_print_str
  movq [rbp + -1216], rax
  cmpq $57, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1312]
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -1320]
  movq [rbp + -1312], rcx
  movq [rbp + -1320], rdx
  call lm_assert
  movq [rbp + -1224], rax
  cmpq $97, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1328]
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -1336]
  movq [rbp + -1328], rcx
  movq [rbp + -1336], rdx
  call lm_assert
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -1344]
  movq [rbp + -1344], rax
  addq $16, rax
  movq rax, [rbp + -1352]
  movq [rbp + -1352], rax
  movq rax, [rbp + -1360]
  movq [rbp + -1360], rax
  mov rax, [rax]
  movq rax, [rbp + -1368]
  movq [rbp + -1368], rcx
  call lm_print_str
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -1376]
  movq [rbp + -1376], rcx
  movq $17, rdx
  call createProcessor
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -1384]
  movq [rbp + -1384], rcx
  movq $41, rdx
  call createProcessor
  movq $81, rcx
  call r215
  movq rax, [rbp + -1392]
  movq $25, rcx
  call r219
  movq rax, [rbp + -1400]
  movq [rbp + -1392], rax
  addq $16, rax
  movq rax, [rbp + -1408]
  movq [rbp + -1408], rax
  movq rax, [rbp + -1416]
  movq [rbp + -1416], rax
  mov rax, [rax]
  movq rax, [rbp + -1424]
  movq [rbp + -1424], rcx
  call lm_print_str
  movq [rbp + -1400], rax
  addq $16, rax
  movq rax, [rbp + -1432]
  movq [rbp + -1432], rax
  movq rax, [rbp + -1440]
  movq [rbp + -1440], rax
  mov rax, [rax]
  movq rax, [rbp + -1448]
  movq [rbp + -1448], rcx
  call lm_print_str
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -1456]
  movq [rbp + -1392], rax
  cmpq [rbp + -1456], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1464]
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -1472]
  movq [rbp + -1464], rcx
  movq [rbp + -1472], rdx
  call lm_assert
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -1480]
  movq [rbp + -1400], rax
  cmpq [rbp + -1480], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1488]
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -1496]
  movq [rbp + -1488], rcx
  movq [rbp + -1496], rdx
  call lm_assert
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -1504]
  movq [rbp + -1504], rax
  addq $16, rax
  movq rax, [rbp + -1512]
  movq [rbp + -1512], rax
  movq rax, [rbp + -1520]
  movq [rbp + -1520], rax
  mov rax, [rax]
  movq rax, [rbp + -1528]
  movq [rbp + -1528], rcx
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

.globl createProcessor
createProcessor:
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
createProcessor_entry:
createProcessor_block_0:
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq $0, rax
  jmp createProcessor_epilogue
createProcessor_epilogue:
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
.Lfunc_end_createProcessor:

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
  sub rsp, 56
  mov [rbp + -64], rcx
__lambda_8_entry:
__lambda_8_block_0:
  movq [rbp + -64], rax
  imulq $17, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
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

.globl selectOperation
selectOperation:
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
selectOperation_entry:
selectOperation_block_0:
  movq [rbp + -64], rax
  testq rax, rax
  jne selectOperation_block_1
  jmp selectOperation_block_4
selectOperation_block_1:
  jmp selectOperation_block_1
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp selectOperation_epilogue
selectOperation_block_4:
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp selectOperation_epilogue
selectOperation_epilogue:
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
.Lfunc_end_selectOperation:

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
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
__lambda_5_entry:
__lambda_5_block_0:
  movq [rbp + -64], rax
  addq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
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
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
__lambda_6_entry:
__lambda_6_block_0:
  movq [rbp + -64], rax
  imulq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
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
  sub rsp, 56
  mov [rbp + -64], rcx
__lambda_0_entry:
__lambda_0_block_0:
  movq [rbp + -64], rax
  addq $0, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
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

.globl increment
increment:
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
increment_entry:
increment_block_0:
  movq [rbp + -64], rax
  addq $9, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp increment_epilogue
increment_epilogue:
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
.Lfunc_end_increment:

.globl multiply
multiply:
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
multiply_entry:
multiply_block_0:
  movq [rbp + -64], rax
  imulq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp multiply_epilogue
multiply_epilogue:
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
.Lfunc_end_multiply:

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
  sub rsp, 72
  mov [rbp + -64], rcx
__lambda_1_entry:
__lambda_1_block_0:
  movq [rbp + -64], rcx
  call 
  movq rax, [rbp + -72]
  movq [rbp + -72], rcx
  call 
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
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
  mov [rbp + -64], rcx
__lambda_4_entry:
__lambda_4_block_0:
  movq [rbp + -64], rax
  imulq [rbp + -64], rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
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

.globl __lambda_9
__lambda_9:
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
__lambda_9_entry:
__lambda_9_block_0:
  movq [rbp + -64], rax
  imulq $25, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp __lambda_9_epilogue
__lambda_9_epilogue:
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
.Lfunc_end___lambda_9:

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
  movq [rbp + -64], rax
  addq $9, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
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

.globl add
add:
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
add_entry:
add_block_0:
  movq [rbp + -64], rax
  addq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp add_epilogue
add_epilogue:
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
.Lfunc_end_add:

.globl applyOperation
applyOperation:
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
applyOperation_entry:
applyOperation_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call 
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp applyOperation_epilogue
applyOperation_epilogue:
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
.Lfunc_end_applyOperation:

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
  movq [rel str_const_59], rcx
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
  sub rsp, 88
  mov [rbp + -64], rcx
__lambda_7_entry:
__lambda_7_block_0:
  movq [rbp + -64], rax
  imulq $0, rax
  movq rax, [rbp + -72]
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -80], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  movq [rbp + -72], rdx
  call lm_rt_str_format
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
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

.globl compose
compose:
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
compose_entry:
compose_block_0:
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq $0, rax
  jmp compose_epilogue
compose_epilogue:
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
.Lfunc_end_compose:

.globl square
square:
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
square_entry:
square_block_0:
  movq [rbp + -64], rax
  imulq [rbp + -64], rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp square_epilogue
square_epilogue:
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
.Lfunc_end_square:

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
  mov [rbp + -64], rcx
__lambda_3_entry:
__lambda_3_block_0:
  movq [rbp + -64], rax
  imulq $17, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
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

.globl createFunctionSet
createFunctionSet:
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
createFunctionSet_entry:
createFunctionSet_block_0:
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq $0, rax
  jmp createFunctionSet_epilogue
createFunctionSet_epilogue:
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
.Lfunc_end_createFunctionSet:

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

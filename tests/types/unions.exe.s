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
  .string "=== Union Type Tests ==="
.align 8
str_const_1:
  .string "
--- Test 1: Basic Union Types ---"
.align 8
str_const_2:
  .string "hello"
.align 8
str_const_3:
  .string "NumberOrString (int): %s"
.align 8
str_const_4:
  .string "NumberOrString (str): %s"
.align 8
str_const_5:
  .string "BoolOrFloat (bool): %s"
.align 8
str_const_6:
  .string "BoolOrFloat (float): %s"
.align 8
str_const_7:
  .string "Union type should accept int value"
.align 8
str_const_8:
  .string "hello"
.align 8
str_const_9:
  .string "Union type should accept str value"
.align 8
str_const_10:
  .string "Union type should accept bool value"
.align 8
str_const_11:
  .string "Union type should accept float value"
.align 8
str_const_12:
  .string "
--- Test 2: Multi-variant Union Types ---"
.align 8
str_const_13:
  .string "Red"
.align 8
str_const_14:
  .string "Green"
.align 8
str_const_15:
  .string "Blue"
.align 8
str_const_16:
  .string "Success"
.align 8
str_const_17:
  .string "Warning"
.align 8
str_const_18:
  .string "Error"
.align 8
str_const_19:
  .string "Colors: %s, %s, %s"
.align 8
str_const_20:
  .string "Statuses: %s, %s, %s"
.align 8
str_const_21:
  .string "Red"
.align 8
str_const_22:
  .string "Union type alias should work for colors"
.align 8
str_const_23:
  .string "Green"
.align 8
str_const_24:
  .string "Union type alias should work for colors"
.align 8
str_const_25:
  .string "Blue"
.align 8
str_const_26:
  .string "Union type alias should work for colors"
.align 8
str_const_27:
  .string "Success"
.align 8
str_const_28:
  .string "Union type alias should work for statuses"
.align 8
str_const_29:
  .string "Warning"
.align 8
str_const_30:
  .string "Union type alias should work for statuses"
.align 8
str_const_31:
  .string "Error"
.align 8
str_const_32:
  .string "Union type alias should work for statuses"
.align 8
str_const_33:
  .string "
--- Test 3: Primitive Union Types ---"
.align 8
str_const_34:
  .string "test"
.align 8
str_const_35:
  .string "Value (int): %s"
.align 8
str_const_36:
  .string "Value (float): %s"
.align 8
str_const_37:
  .string "Value (str): %s"
.align 8
str_const_38:
  .string "Value (bool): %s"
.align 8
str_const_39:
  .string "Multi-variant union should accept int"
.align 8
str_const_40:
  .string "Multi-variant union should accept float"
.align 8
str_const_41:
  .string "test"
.align 8
str_const_42:
  .string "Multi-variant union should accept str"
.align 8
str_const_43:
  .string "Multi-variant union should accept bool"
.align 8
str_const_44:
  .string "
--- Test 4: Nested Union Types ---"
.align 8
str_const_45:
  .string "text"
.align 8
str_const_46:
  .string "Nested (int): %s"
.align 8
str_const_47:
  .string "Nested (str): %s"
.align 8
str_const_48:
  .string "Nested (bool): %s"
.align 8
str_const_49:
  .string "Nested union should accept int"
.align 8
str_const_50:
  .string "text"
.align 8
str_const_51:
  .string "Nested union should accept str"
.align 8
str_const_52:
  .string "Nested union should accept bool"
.align 8
str_const_53:
  .string "
--- Test 5: Union Type Compatibility ---"
.align 8
str_const_54:
  .string "shared"
.align 8
str_const_55:
  .string "IntOrStr: %s"
.align 8
str_const_56:
  .string "StrOrBool: %s"
.align 8
str_const_57:
  .string "Union compatibility should work"
.align 8
str_const_58:
  .string "shared"
.align 8
str_const_59:
  .string "Union compatibility should work"
.align 8
str_const_60:
  .string "
--- Test 6: Union Types in Functions ---"
.align 8
str_const_61:
  .string "Process result 1: %s"
.align 8
str_const_62:
  .string "Process result 2: %s"
.align 8
str_const_63:
  .string "Function with union return should work: 5*2 = 10"
.align 8
str_const_64:
  .string "Invalid input"
.align 8
str_const_65:
  .string "Function with union return should work for negative input"
.align 8
str_const_66:
  .string "
--- Test 7: Complex Union Combinations ---"
.align 8
str_const_67:
  .string "data"
.align 8
str_const_68:
  .string "Data 1 (int): %s"
.align 8
str_const_69:
  .string "Data 2 (float): %s"
.align 8
str_const_70:
  .string "Data 3 (str): %s"
.align 8
str_const_71:
  .string "Data 4 (bool): %s"
.align 8
str_const_72:
  .string "Complex union should accept int"
.align 8
str_const_73:
  .string "Complex union should accept float"
.align 8
str_const_74:
  .string "data"
.align 8
str_const_75:
  .string "Complex union should accept str"
.align 8
str_const_76:
  .string "Complex union should accept bool"
.align 8
str_const_77:
  .string "
=== Union Type Tests Complete ==="
.align 8
str_const_78:
  .string "Invalid input"
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
  sub rsp, 1800
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
  movq [rbp + -136], rcx
  movq $337, rdx
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
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -176], rcx
  movq [rbp + -128], rdx
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
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -216], rcx
  movq $18, rdx
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
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -256], rcx
  movq $2, rdx
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
  movq $337, rax
  cmpq $337, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -296], rcx
  movq [rbp + -304], rdx
  call lm_assert
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -128], rax
  cmpq [rbp + -312], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -320]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -320], rcx
  movq [rbp + -328], rdx
  call lm_assert
  movq $18, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -336]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -336], rcx
  movq [rbp + -344], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -352]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -352], rcx
  movq [rbp + -360], rdx
  call lm_assert
  movq [rel str_const_12], rcx
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
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -448], rcx
  movq [rbp + -400], rdx
  call lm_rt_str_format
  movq rax, [rbp + -456]
  movq [rbp + -456], rcx
  movq [rbp + -408], rdx
  call lm_rt_str_format
  movq rax, [rbp + -464]
  movq [rbp + -464], rcx
  movq [rbp + -416], rdx
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
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -504], rcx
  movq [rbp + -424], rdx
  call lm_rt_str_format
  movq rax, [rbp + -512]
  movq [rbp + -512], rcx
  movq [rbp + -432], rdx
  call lm_rt_str_format
  movq rax, [rbp + -520]
  movq [rbp + -520], rcx
  movq [rbp + -440], rdx
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
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -560]
  movq [rbp + -400], rax
  cmpq [rbp + -560], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -568]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -568], rcx
  movq [rbp + -576], rdx
  call lm_assert
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -584]
  movq [rbp + -408], rax
  cmpq [rbp + -584], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -592]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -600]
  movq [rbp + -592], rcx
  movq [rbp + -600], rdx
  call lm_assert
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -608]
  movq [rbp + -416], rax
  cmpq [rbp + -608], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -616]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rbp + -616], rcx
  movq [rbp + -624], rdx
  call lm_assert
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -632]
  movq [rbp + -424], rax
  cmpq [rbp + -632], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -640]
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -648]
  movq [rbp + -640], rcx
  movq [rbp + -648], rdx
  call lm_assert
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -656]
  movq [rbp + -432], rax
  cmpq [rbp + -656], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -664]
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -672]
  movq [rbp + -664], rcx
  movq [rbp + -672], rdx
  call lm_assert
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -680]
  movq [rbp + -440], rax
  cmpq [rbp + -680], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -688]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -696]
  movq [rbp + -688], rcx
  movq [rbp + -696], rdx
  call lm_assert
  movq [rel str_const_33], rcx
  call lm_box_string
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
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -736]
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -744]
  movq [rbp + -744], rcx
  movq $985, rdx
  call lm_rt_str_format
  movq rax, [rbp + -752]
  movq [rbp + -752], rax
  addq $16, rax
  movq rax, [rbp + -760]
  movq [rbp + -760], rax
  movq rax, [rbp + -768]
  movq [rbp + -768], rax
  mov rax, [rax]
  movq rax, [rbp + -776]
  movq [rbp + -776], rcx
  call lm_print_str
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -784]
  movq [rbp + -784], rcx
  movq $2, rdx
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
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -824]
  movq [rbp + -824], rcx
  movq [rbp + -736], rdx
  call lm_rt_str_format
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
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -864]
  movq [rbp + -864], rcx
  movq $18, rdx
  call lm_rt_str_format
  movq rax, [rbp + -872]
  movq [rbp + -872], rax
  addq $16, rax
  movq rax, [rbp + -880]
  movq [rbp + -880], rax
  movq rax, [rbp + -888]
  movq [rbp + -888], rax
  mov rax, [rax]
  movq rax, [rbp + -896]
  movq [rbp + -896], rcx
  call lm_print_str
  movq $985, rax
  cmpq $985, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -904]
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -912]
  movq [rbp + -904], rcx
  movq [rbp + -912], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -920]
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -928]
  movq [rbp + -920], rcx
  movq [rbp + -928], rdx
  call lm_assert
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -936]
  movq [rbp + -736], rax
  cmpq [rbp + -936], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -944]
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -952]
  movq [rbp + -944], rcx
  movq [rbp + -952], rdx
  call lm_assert
  movq $18, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -960]
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -968]
  movq [rbp + -960], rcx
  movq [rbp + -968], rdx
  call lm_assert
  movq [rel str_const_44], rcx
  call lm_box_string
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
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -1008]
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -1016]
  movq [rbp + -1016], rcx
  movq $337, rdx
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
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -1056]
  movq [rbp + -1056], rcx
  movq [rbp + -1008], rdx
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
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -1096]
  movq [rbp + -1096], rcx
  movq $10, rdx
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
  movq $337, rax
  cmpq $337, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1136]
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -1144]
  movq [rbp + -1136], rcx
  movq [rbp + -1144], rdx
  call lm_assert
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -1152]
  movq [rbp + -1008], rax
  cmpq [rbp + -1152], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1160]
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -1168]
  movq [rbp + -1160], rcx
  movq [rbp + -1168], rdx
  call lm_assert
  movq $10, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1176]
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -1184]
  movq [rbp + -1176], rcx
  movq [rbp + -1184], rdx
  call lm_assert
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -1192]
  movq [rbp + -1192], rax
  addq $16, rax
  movq rax, [rbp + -1200]
  movq [rbp + -1200], rax
  movq rax, [rbp + -1208]
  movq [rbp + -1208], rax
  mov rax, [rax]
  movq rax, [rbp + -1216]
  movq [rbp + -1216], rcx
  call lm_print_str
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -1224]
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -1232]
  movq [rbp + -1232], rcx
  movq $801, rdx
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
  movq [rel str_const_56], rcx
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
  movq $801, rax
  cmpq $801, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1312]
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -1320]
  movq [rbp + -1312], rcx
  movq [rbp + -1320], rdx
  call lm_assert
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -1328]
  movq [rbp + -1224], rax
  cmpq [rbp + -1328], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1336]
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -1344]
  movq [rbp + -1336], rcx
  movq [rbp + -1344], rdx
  call lm_assert
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -1352]
  movq [rbp + -1352], rax
  addq $16, rax
  movq rax, [rbp + -1360]
  movq [rbp + -1360], rax
  movq rax, [rbp + -1368]
  movq [rbp + -1368], rax
  mov rax, [rax]
  movq rax, [rbp + -1376]
  movq [rbp + -1376], rcx
  call lm_print_str
  movq $41, rcx
  call processValue
  movq $9, rax
  negq rax
  movq rax, [rbp + -1384]
  movq [rbp + -1384], rcx
  call processValue
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -1392]
  movq [rbp + -1392], rcx
  movq $r159, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1400]
  movq [rbp + -1400], rax
  addq $16, rax
  movq rax, [rbp + -1408]
  movq [rbp + -1408], rax
  movq rax, [rbp + -1416]
  movq [rbp + -1416], rax
  mov rax, [rax]
  movq rax, [rbp + -1424]
  movq [rbp + -1424], rcx
  call lm_print_str
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -1432]
  movq [rbp + -1432], rcx
  movq $r163, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1440]
  movq [rbp + -1440], rax
  addq $16, rax
  movq rax, [rbp + -1448]
  movq [rbp + -1448], rax
  movq rax, [rbp + -1456]
  movq [rbp + -1456], rax
  mov rax, [rax]
  movq rax, [rbp + -1464]
  movq [rbp + -1464], rcx
  call lm_print_str
  movq $r159, rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1472]
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -1480]
  movq [rbp + -1472], rcx
  movq [rbp + -1480], rdx
  call lm_assert
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -1488]
  movq $r163, rax
  cmpq [rbp + -1488], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1496]
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -1504]
  movq [rbp + -1496], rcx
  movq [rbp + -1504], rdx
  call lm_assert
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -1512]
  movq [rbp + -1512], rax
  addq $16, rax
  movq rax, [rbp + -1520]
  movq [rbp + -1520], rax
  movq rax, [rbp + -1528]
  movq [rbp + -1528], rax
  mov rax, [rax]
  movq rax, [rbp + -1536]
  movq [rbp + -1536], rcx
  call lm_print_str
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -1544]
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -1552]
  movq [rbp + -1552], rcx
  movq $337, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1560]
  movq [rbp + -1560], rax
  addq $16, rax
  movq rax, [rbp + -1568]
  movq [rbp + -1568], rax
  movq rax, [rbp + -1576]
  movq [rbp + -1576], rax
  mov rax, [rax]
  movq rax, [rbp + -1584]
  movq [rbp + -1584], rcx
  call lm_print_str
  movq [rel str_const_69], rcx
  call lm_box_string
  movq rax, [rbp + -1592]
  movq [rbp + -1592], rcx
  movq $2, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1600]
  movq [rbp + -1600], rax
  addq $16, rax
  movq rax, [rbp + -1608]
  movq [rbp + -1608], rax
  movq rax, [rbp + -1616]
  movq [rbp + -1616], rax
  mov rax, [rax]
  movq rax, [rbp + -1624]
  movq [rbp + -1624], rcx
  call lm_print_str
  movq [rel str_const_70], rcx
  call lm_box_string
  movq rax, [rbp + -1632]
  movq [rbp + -1632], rcx
  movq [rbp + -1544], rdx
  call lm_rt_str_format
  movq rax, [rbp + -1640]
  movq [rbp + -1640], rax
  addq $16, rax
  movq rax, [rbp + -1648]
  movq [rbp + -1648], rax
  movq rax, [rbp + -1656]
  movq [rbp + -1656], rax
  mov rax, [rax]
  movq rax, [rbp + -1664]
  movq [rbp + -1664], rcx
  call lm_print_str
  movq [rel str_const_71], rcx
  call lm_box_string
  movq rax, [rbp + -1672]
  movq [rbp + -1672], rcx
  movq $18, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1680]
  movq [rbp + -1680], rax
  addq $16, rax
  movq rax, [rbp + -1688]
  movq [rbp + -1688], rax
  movq rax, [rbp + -1696]
  movq [rbp + -1696], rax
  mov rax, [rax]
  movq rax, [rbp + -1704]
  movq [rbp + -1704], rcx
  call lm_print_str
  movq $337, rax
  cmpq $337, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1712]
  movq [rel str_const_72], rcx
  call lm_box_string
  movq rax, [rbp + -1720]
  movq [rbp + -1712], rcx
  movq [rbp + -1720], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1728]
  movq [rel str_const_73], rcx
  call lm_box_string
  movq rax, [rbp + -1736]
  movq [rbp + -1728], rcx
  movq [rbp + -1736], rdx
  call lm_assert
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -1744]
  movq [rbp + -1544], rax
  cmpq [rbp + -1744], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1752]
  movq [rel str_const_75], rcx
  call lm_box_string
  movq rax, [rbp + -1760]
  movq [rbp + -1752], rcx
  movq [rbp + -1760], rdx
  call lm_assert
  movq $18, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1768]
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -1776]
  movq [rbp + -1768], rcx
  movq [rbp + -1776], rdx
  call lm_assert
  movq [rel str_const_77], rcx
  call lm_box_string
  movq rax, [rbp + -1784]
  movq [rbp + -1784], rax
  addq $16, rax
  movq rax, [rbp + -1792]
  movq [rbp + -1792], rax
  movq rax, [rbp + -1800]
  movq [rbp + -1800], rax
  mov rax, [rax]
  movq rax, [rbp + -1808]
  movq [rbp + -1808], rcx
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

.globl processValue
processValue:
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
processValue_entry:
processValue_block_0:
  movq [rbp + -64], rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne processValue_block_3
  jmp processValue_block_6
processValue_block_3:
  jmp processValue_block_3
  movq [rbp + -64], rax
  imulq $17, rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp processValue_epilogue
processValue_block_6:
  movq [rel str_const_78], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp processValue_epilogue
processValue_epilogue:
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
.Lfunc_end_processValue:

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

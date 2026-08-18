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
  .string "=== Refined Type Tests ==="
.align 8
str_const_1:
  .string "
--- Test 1: Basic Refined Type with Arithmetic Condition ---"
.align 8
str_const_2:
  .string "Positive int 1: %s"
.align 8
str_const_3:
  .string "Positive int 2: %s"
.align 8
str_const_4:
  .string "Positive int 3: %s"
.align 8
str_const_5:
  .string "
--- Test 2: Refined Type with Comparison Operators ---"
.align 8
str_const_6:
  .string "Even number 1: %s"
.align 8
str_const_7:
  .string "Even number 2: %s"
.align 8
str_const_8:
  .string "Odd number 1: %s"
.align 8
str_const_9:
  .string "Odd number 2: %s"
.align 8
str_const_10:
  .string "
--- Test 3: Refined Type with Complex Arithmetic ---"
.align 8
str_const_11:
  .string "Double digit 1: %s"
.align 8
str_const_12:
  .string "Double digit 2: %s"
.align 8
str_const_13:
  .string "Triple digit 1: %s"
.align 8
str_const_14:
  .string "
--- Test 4: Refined String Types ---"
.align 8
str_const_15:
  .string "hello"
.align 8
str_const_16:
  .string "self is a long string"
.align 8
str_const_17:
  .string "hi"
.align 8
str_const_18:
  .string "Non-empty string: %s"
.align 8
str_const_19:
  .string "Long string: %s"
.align 8
str_const_20:
  .string "Short string: %s"
.align 8
str_const_21:
  .string "
--- Test 5: Refined Type in Function Parameters ---"
.align 8
str_const_22:
  .string "Process positive result: %s"
.align 8
str_const_23:
  .string "Process large result: %s"
.align 8
str_const_24:
  .string "
--- Test 6: Refined Type in Function Return ---"
.align 8
str_const_25:
  .string "Positive number: %s"
.align 8
str_const_26:
  .string "Large number: %s"
.align 8
str_const_27:
  .string "
--- Test 7: Refined Type with Logical Operators ---"
.align 8
str_const_28:
  .string "Valid age 1: %s"
.align 8
str_const_29:
  .string "Valid age 2: %s"
.align 8
str_const_30:
  .string "Working age 1: %s"
.align 8
str_const_31:
  .string "Working age 2: %s"
.align 8
str_const_32:
  .string "
--- Test 8: Refined Type Compatibility ---"
.align 8
str_const_33:
  .string "Base positive: %s"
.align 8
str_const_34:
  .string "Strict positive: %s"
.align 8
str_const_35:
  .string "
--- Test 9: Refined Type in Collections ---"
.align 8
str_const_36:
  .string "Positives: %s"
.align 8
str_const_37:
  .string "Larges: %s"
.align 8
str_const_38:
  .string "Evens: %s"
.align 8
str_const_39:
  .string "
--- Test 10: Refined Type with Arithmetic Expressions ---"
.align 8
str_const_40:
  .string "Power of two 1: %s"
.align 8
str_const_41:
  .string "Power of two 2: %s"
.align 8
str_const_42:
  .string "Divisible 1: %s"
.align 8
str_const_43:
  .string "Divisible 2: %s"
.align 8
str_const_44:
  .string "In bounds: %s"
.align 8
str_const_45:
  .string "
--- Test 11: Refined Type Aliases ---"
.align 8
str_const_46:
  .string "Refined alias 1: %s"
.align 8
str_const_47:
  .string "Refined alias 2: %s"
.align 8
str_const_48:
  .string "
--- Test 12: Refined Type with Function Calls ---"
.align 8
str_const_49:
  .string "Is positive: %s"
.align 8
str_const_50:
  .string "Is large: %s"
.align 8
str_const_51:
  .string "
--- Test 13: Refined Type with Division ---"
.align 8
str_const_52:
  .string "Non-zero 1: %s"
.align 8
str_const_53:
  .string "Non-zero 2: %s"
.align 8
str_const_54:
  .string "High value: %s"
.align 8
str_const_55:
  .string "
--- Test 14: Refined Type with Modulo ---"
.align 8
str_const_56:
  .string "Multiple 1: %s"
.align 8
str_const_57:
  .string "Multiple 2: %s"
.align 8
str_const_58:
  .string "Not multiple 1: %s"
.align 8
str_const_59:
  .string "Not multiple 2: %s"
.align 8
str_const_60:
  .string "
--- Test 15: Refined Type in Dictionaries ---"
.align 8
str_const_61:
  .string "Alice"
.align 8
str_const_62:
  .string "Bob"
.align 8
str_const_63:
  .string "Charlie"
.align 8
str_const_64:
  .string "player1"
.align 8
str_const_65:
  .string "player2"
.align 8
str_const_66:
  .string "Age map: %s"
.align 8
str_const_67:
  .string "Score map: %s"
.align 8
str_const_68:
  .string "
--- Test 16: Refined Type with Subtraction ---"
.align 8
str_const_69:
  .string "Above zero: %s"
.align 8
str_const_70:
  .string "Below hundred: %s"
.align 8
str_const_71:
  .string "
--- Test 17: Refined Type with Addition ---"
.align 8
str_const_72:
  .string "Sum positive: %s"
.align 8
str_const_73:
  .string "Sum large: %s"
.align 8
str_const_74:
  .string "
--- Test 18: Refined Type with Multiplication ---"
.align 8
str_const_75:
  .string "Product large: %s"
.align 8
str_const_76:
  .string "Product small: %s"
.align 8
str_const_77:
  .string "
--- Test 19: Refined Type in Function with Conditionals ---"
.align 8
str_const_78:
  .string "Validate 1: %s"
.align 8
str_const_79:
  .string "Validate 2: %s"
.align 8
str_const_80:
  .string "Validate 3: %s"
.align 8
str_const_81:
  .string "
--- Test 20: Refined Type Comprehensive Coverage ---"
.align 8
str_const_82:
  .string "Refined result 1: %s"
.align 8
str_const_83:
  .string "Refined result 2: %s"
.align 8
str_const_84:
  .string "
=== Refined Type Tests Complete ==="
.align 8
str_const_85:
  .string "Large positive"
.align 8
str_const_86:
  .string "Medium positive"
.align 8
str_const_87:
  .string "Small positive"
.align 8
nl:
  .string "
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
  sub rsp, 3016
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
  movq $41, rdx
  call lm_rt_str_format
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  addq $16, rax
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  mov rax, [rax]
  movq rax, [rbp + -160]
  movq [rbp + -160], rcx
  call lm_print_str
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -168], rcx
  movq $337, rdx
  call lm_rt_str_format
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  addq $16, rax
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  mov rax, [rax]
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  call lm_print_str
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -208], rcx
  movq $8001, rdx
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
  movq [rel str_const_5], rcx
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
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -280], rcx
  movq $17, rdx
  call lm_rt_str_format
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
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -320], rcx
  movq $801, rdx
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
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -360], rcx
  movq $25, rdx
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
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -400], rcx
  movq $793, rdx
  call lm_rt_str_format
  movq rax, [rbp + -408]
  movq [rbp + -408], rax
  addq $16, rax
  movq rax, [rbp + -416]
  movq [rbp + -416], rax
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  mov rax, [rax]
  movq rax, [rbp + -432]
  movq [rbp + -432], rcx
  call lm_print_str
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  addq $16, rax
  movq rax, [rbp + -448]
  movq [rbp + -448], rax
  movq rax, [rbp + -456]
  movq [rbp + -456], rax
  mov rax, [rax]
  movq rax, [rbp + -464]
  movq [rbp + -464], rcx
  call lm_print_str
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -472], rcx
  movq $169, rdx
  call lm_rt_str_format
  movq rax, [rbp + -480]
  movq [rbp + -480], rax
  addq $16, rax
  movq rax, [rbp + -488]
  movq [rbp + -488], rax
  movq rax, [rbp + -496]
  movq [rbp + -496], rax
  mov rax, [rax]
  movq rax, [rbp + -504]
  movq [rbp + -504], rcx
  call lm_print_str
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -512]
  movq [rbp + -512], rcx
  movq $7993, rdx
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
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -552]
  movq [rbp + -552], rcx
  movq $1609, rdx
  call lm_rt_str_format
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
  movq [rel str_const_14], rcx
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
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -632]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -648]
  movq [rbp + -648], rcx
  movq [rbp + -624], rdx
  call lm_rt_str_format
  movq rax, [rbp + -656]
  movq [rbp + -656], rax
  addq $16, rax
  movq rax, [rbp + -664]
  movq [rbp + -664], rax
  movq rax, [rbp + -672]
  movq [rbp + -672], rax
  mov rax, [rax]
  movq rax, [rbp + -680]
  movq [rbp + -680], rcx
  call lm_print_str
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -688]
  movq [rbp + -688], rcx
  movq [rbp + -632], rdx
  call lm_rt_str_format
  movq rax, [rbp + -696]
  movq [rbp + -696], rax
  addq $16, rax
  movq rax, [rbp + -704]
  movq [rbp + -704], rax
  movq rax, [rbp + -712]
  movq [rbp + -712], rax
  mov rax, [rax]
  movq rax, [rbp + -720]
  movq [rbp + -720], rcx
  call lm_print_str
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -728]
  movq [rbp + -728], rcx
  movq [rbp + -640], rdx
  call lm_rt_str_format
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
  movq [rel str_const_21], rcx
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
  movq $81, rcx
  call processPositive
  movq $1201, rcx
  call processLarge
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -800]
  movq [rbp + -800], rcx
  movq $r65, rdx
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
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -840]
  movq [rbp + -840], rcx
  movq $r68, rdx
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
  movq [rel str_const_24], rcx
  call lm_box_string
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
  call getPositiveNumber
  call getLargeNumber
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -912]
  movq [rbp + -912], rcx
  movq $r78, rdx
  call lm_rt_str_format
  movq rax, [rbp + -920]
  movq [rbp + -920], rax
  addq $16, rax
  movq rax, [rbp + -928]
  movq [rbp + -928], rax
  movq rax, [rbp + -936]
  movq [rbp + -936], rax
  mov rax, [rax]
  movq rax, [rbp + -944]
  movq [rbp + -944], rcx
  call lm_print_str
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -952]
  movq [rbp + -952], rcx
  movq $r80, rdx
  call lm_rt_str_format
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
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -992]
  movq [rbp + -992], rax
  addq $16, rax
  movq rax, [rbp + -1000]
  movq [rbp + -1000], rax
  movq rax, [rbp + -1008]
  movq [rbp + -1008], rax
  mov rax, [rax]
  movq rax, [rbp + -1016]
  movq [rbp + -1016], rcx
  call lm_print_str
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -1024]
  movq [rbp + -1024], rcx
  movq $201, rdx
  call lm_rt_str_format
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
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -1064]
  movq [rbp + -1064], rcx
  movq $801, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1072]
  movq [rbp + -1072], rax
  addq $16, rax
  movq rax, [rbp + -1080]
  movq [rbp + -1080], rax
  movq rax, [rbp + -1088]
  movq [rbp + -1088], rax
  mov rax, [rax]
  movq rax, [rbp + -1096]
  movq [rbp + -1096], rcx
  call lm_print_str
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -1104]
  movq [rbp + -1104], rcx
  movq $241, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1112]
  movq [rbp + -1112], rax
  addq $16, rax
  movq rax, [rbp + -1120]
  movq [rbp + -1120], rax
  movq rax, [rbp + -1128]
  movq [rbp + -1128], rax
  mov rax, [rax]
  movq rax, [rbp + -1136]
  movq [rbp + -1136], rcx
  call lm_print_str
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -1144]
  movq [rbp + -1144], rcx
  movq $521, rdx
  call lm_rt_str_format
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
  movq [rel str_const_32], rcx
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
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -1216]
  movq [rbp + -1216], rcx
  movq $41, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1224]
  movq [rbp + -1224], rax
  addq $16, rax
  movq rax, [rbp + -1232]
  movq [rbp + -1232], rax
  movq rax, [rbp + -1240]
  movq [rbp + -1240], rax
  mov rax, [rax]
  movq rax, [rbp + -1248]
  movq [rbp + -1248], rcx
  call lm_print_str
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -1256]
  movq [rbp + -1256], rcx
  movq $161, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1264]
  movq [rbp + -1264], rax
  addq $16, rax
  movq rax, [rbp + -1272]
  movq [rbp + -1272], rax
  movq rax, [rbp + -1280]
  movq [rbp + -1280], rax
  mov rax, [rax]
  movq rax, [rbp + -1288]
  movq [rbp + -1288], rcx
  call lm_print_str
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -1296]
  movq [rbp + -1296], rax
  addq $16, rax
  movq rax, [rbp + -1304]
  movq [rbp + -1304], rax
  movq rax, [rbp + -1312]
  movq [rbp + -1312], rax
  mov rax, [rax]
  movq rax, [rbp + -1320]
  movq [rbp + -1320], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $r118, rcx
  movq $9, rdx
  call lm_list_append
  movq $r118, rcx
  movq $17, rdx
  call lm_list_append
  movq $r118, rcx
  movq $25, rdx
  call lm_list_append
  movq $r118, rcx
  movq $33, rdx
  call lm_list_append
  movq $r118, rcx
  movq $41, rdx
  call lm_list_append
  movq $0, rcx
  call lm_list_new
  movq $r130, rcx
  movq $809, rdx
  call lm_list_append
  movq $r130, rcx
  movq $1601, rdx
  call lm_list_append
  movq $r130, rcx
  movq $4001, rdx
  call lm_list_append
  movq $0, rcx
  call lm_list_new
  movq $r138, rcx
  movq $17, rdx
  call lm_list_append
  movq $r138, rcx
  movq $33, rdx
  call lm_list_append
  movq $r138, rcx
  movq $49, rdx
  call lm_list_append
  movq $r138, rcx
  movq $65, rdx
  call lm_list_append
  movq $r138, rcx
  movq $81, rdx
  call lm_list_append
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -1328]
  movq [rbp + -1328], rcx
  movq $r118, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1336]
  movq [rbp + -1336], rax
  addq $16, rax
  movq rax, [rbp + -1344]
  movq [rbp + -1344], rax
  movq rax, [rbp + -1352]
  movq [rbp + -1352], rax
  mov rax, [rax]
  movq rax, [rbp + -1360]
  movq [rbp + -1360], rcx
  call lm_print_str
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -1368]
  movq [rbp + -1368], rcx
  movq $r130, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1376]
  movq [rbp + -1376], rax
  addq $16, rax
  movq rax, [rbp + -1384]
  movq [rbp + -1384], rax
  movq rax, [rbp + -1392]
  movq [rbp + -1392], rax
  mov rax, [rax]
  movq rax, [rbp + -1400]
  movq [rbp + -1400], rcx
  call lm_print_str
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -1408]
  movq [rbp + -1408], rcx
  movq $r138, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1416]
  movq [rbp + -1416], rax
  addq $16, rax
  movq rax, [rbp + -1424]
  movq [rbp + -1424], rax
  movq rax, [rbp + -1432]
  movq [rbp + -1432], rax
  mov rax, [rax]
  movq rax, [rbp + -1440]
  movq [rbp + -1440], rcx
  call lm_print_str
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -1448]
  movq [rbp + -1448], rax
  addq $16, rax
  movq rax, [rbp + -1456]
  movq [rbp + -1456], rax
  movq rax, [rbp + -1464]
  movq [rbp + -1464], rax
  mov rax, [rax]
  movq rax, [rbp + -1472]
  movq [rbp + -1472], rcx
  call lm_print_str
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -1480]
  movq [rbp + -1480], rcx
  movq $17, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1488]
  movq [rbp + -1488], rax
  addq $16, rax
  movq rax, [rbp + -1496]
  movq [rbp + -1496], rax
  movq rax, [rbp + -1504]
  movq [rbp + -1504], rax
  mov rax, [rax]
  movq rax, [rbp + -1512]
  movq [rbp + -1512], rcx
  call lm_print_str
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -1520]
  movq [rbp + -1520], rcx
  movq $513, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1528]
  movq [rbp + -1528], rax
  addq $16, rax
  movq rax, [rbp + -1536]
  movq [rbp + -1536], rax
  movq rax, [rbp + -1544]
  movq [rbp + -1544], rax
  mov rax, [rax]
  movq rax, [rbp + -1552]
  movq [rbp + -1552], rcx
  call lm_print_str
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -1560]
  movq [rbp + -1560], rcx
  movq $73, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1568]
  movq [rbp + -1568], rax
  addq $16, rax
  movq rax, [rbp + -1576]
  movq [rbp + -1576], rax
  movq rax, [rbp + -1584]
  movq [rbp + -1584], rax
  mov rax, [rax]
  movq rax, [rbp + -1592]
  movq [rbp + -1592], rcx
  call lm_print_str
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -1600]
  movq [rbp + -1600], rcx
  movq $241, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1608]
  movq [rbp + -1608], rax
  addq $16, rax
  movq rax, [rbp + -1616]
  movq [rbp + -1616], rax
  movq rax, [rbp + -1624]
  movq [rbp + -1624], rax
  mov rax, [rax]
  movq rax, [rbp + -1632]
  movq [rbp + -1632], rcx
  call lm_print_str
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -1640]
  movq [rbp + -1640], rcx
  movq $4001, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1648]
  movq [rbp + -1648], rax
  addq $16, rax
  movq rax, [rbp + -1656]
  movq [rbp + -1656], rax
  movq rax, [rbp + -1664]
  movq [rbp + -1664], rax
  mov rax, [rax]
  movq rax, [rbp + -1672]
  movq [rbp + -1672], rcx
  call lm_print_str
  movq [rel str_const_45], rcx
  call lm_box_string
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
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -1712]
  movq [rbp + -1712], rcx
  movq $401, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1720]
  movq [rbp + -1720], rax
  addq $16, rax
  movq rax, [rbp + -1728]
  movq [rbp + -1728], rax
  movq rax, [rbp + -1736]
  movq [rbp + -1736], rax
  mov rax, [rax]
  movq rax, [rbp + -1744]
  movq [rbp + -1744], rcx
  call lm_print_str
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -1752]
  movq [rbp + -1752], rcx
  movq $793, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1760]
  movq [rbp + -1760], rax
  addq $16, rax
  movq rax, [rbp + -1768]
  movq [rbp + -1768], rax
  movq rax, [rbp + -1776]
  movq [rbp + -1776], rax
  mov rax, [rax]
  movq rax, [rbp + -1784]
  movq [rbp + -1784], rcx
  call lm_print_str
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -1792]
  movq [rbp + -1792], rax
  addq $16, rax
  movq rax, [rbp + -1800]
  movq [rbp + -1800], rax
  movq rax, [rbp + -1808]
  movq [rbp + -1808], rax
  mov rax, [rax]
  movq rax, [rbp + -1816]
  movq [rbp + -1816], rcx
  call lm_print_str
  movq $337, rcx
  call isPositive
  movq $4001, rcx
  call isLarge
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -1824]
  movq [rbp + -1824], rcx
  movq $r194, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1832]
  movq [rbp + -1832], rax
  addq $16, rax
  movq rax, [rbp + -1840]
  movq [rbp + -1840], rax
  movq rax, [rbp + -1848]
  movq [rbp + -1848], rax
  mov rax, [rax]
  movq rax, [rbp + -1856]
  movq [rbp + -1856], rcx
  call lm_print_str
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -1864]
  movq [rbp + -1864], rcx
  movq $r197, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1872]
  movq [rbp + -1872], rax
  addq $16, rax
  movq rax, [rbp + -1880]
  movq [rbp + -1880], rax
  movq rax, [rbp + -1888]
  movq [rbp + -1888], rax
  mov rax, [rax]
  movq rax, [rbp + -1896]
  movq [rbp + -1896], rcx
  call lm_print_str
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -1904]
  movq [rbp + -1904], rax
  addq $16, rax
  movq rax, [rbp + -1912]
  movq [rbp + -1912], rax
  movq rax, [rbp + -1920]
  movq [rbp + -1920], rax
  mov rax, [rax]
  movq rax, [rbp + -1928]
  movq [rbp + -1928], rcx
  call lm_print_str
  movq $81, rax
  negq rax
  movq rax, [rbp + -1936]
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -1944]
  movq [rbp + -1944], rcx
  movq $41, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1952]
  movq [rbp + -1952], rax
  addq $16, rax
  movq rax, [rbp + -1960]
  movq [rbp + -1960], rax
  movq rax, [rbp + -1968]
  movq [rbp + -1968], rax
  mov rax, [rax]
  movq rax, [rbp + -1976]
  movq [rbp + -1976], rcx
  call lm_print_str
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -1984]
  movq [rbp + -1984], rcx
  movq [rbp + -1936], rdx
  call lm_rt_str_format
  movq rax, [rbp + -1992]
  movq [rbp + -1992], rax
  addq $16, rax
  movq rax, [rbp + -2000]
  movq [rbp + -2000], rax
  movq rax, [rbp + -2008]
  movq [rbp + -2008], rax
  mov rax, [rax]
  movq rax, [rbp + -2016]
  movq [rbp + -2016], rcx
  call lm_print_str
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -2024]
  movq [rbp + -2024], rcx
  movq $16001, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2032]
  movq [rbp + -2032], rax
  addq $16, rax
  movq rax, [rbp + -2040]
  movq [rbp + -2040], rax
  movq rax, [rbp + -2048]
  movq [rbp + -2048], rax
  mov rax, [rax]
  movq rax, [rbp + -2056]
  movq [rbp + -2056], rcx
  call lm_print_str
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -2064]
  movq [rbp + -2064], rax
  addq $16, rax
  movq rax, [rbp + -2072]
  movq [rbp + -2072], rax
  movq rax, [rbp + -2080]
  movq [rbp + -2080], rax
  mov rax, [rax]
  movq rax, [rbp + -2088]
  movq [rbp + -2088], rcx
  call lm_print_str
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -2096]
  movq [rbp + -2096], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2104]
  movq [rbp + -2104], rax
  addq $16, rax
  movq rax, [rbp + -2112]
  movq [rbp + -2112], rax
  movq rax, [rbp + -2120]
  movq [rbp + -2120], rax
  mov rax, [rax]
  movq rax, [rbp + -2128]
  movq [rbp + -2128], rcx
  call lm_print_str
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -2136]
  movq [rbp + -2136], rcx
  movq $201, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2144]
  movq [rbp + -2144], rax
  addq $16, rax
  movq rax, [rbp + -2152]
  movq [rbp + -2152], rax
  movq rax, [rbp + -2160]
  movq [rbp + -2160], rax
  mov rax, [rax]
  movq rax, [rbp + -2168]
  movq [rbp + -2168], rcx
  call lm_print_str
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -2176]
  movq [rbp + -2176], rcx
  movq $57, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2184]
  movq [rbp + -2184], rax
  addq $16, rax
  movq rax, [rbp + -2192]
  movq [rbp + -2192], rax
  movq rax, [rbp + -2200]
  movq [rbp + -2200], rax
  mov rax, [rax]
  movq rax, [rbp + -2208]
  movq [rbp + -2208], rcx
  call lm_print_str
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -2216]
  movq [rbp + -2216], rcx
  movq $105, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2224]
  movq [rbp + -2224], rax
  addq $16, rax
  movq rax, [rbp + -2232]
  movq [rbp + -2232], rax
  movq rax, [rbp + -2240]
  movq [rbp + -2240], rax
  mov rax, [rax]
  movq rax, [rbp + -2248]
  movq [rbp + -2248], rcx
  call lm_print_str
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -2256]
  movq [rbp + -2256], rax
  addq $16, rax
  movq rax, [rbp + -2264]
  movq [rbp + -2264], rax
  movq rax, [rbp + -2272]
  movq [rbp + -2272], rax
  mov rax, [rax]
  movq rax, [rbp + -2280]
  movq [rbp + -2280], rcx
  call lm_print_str
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -2288]
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -2296]
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -2304]
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -2312]
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -2320]
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -2328]
  movq [rbp + -2328], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2336]
  movq [rbp + -2336], rax
  addq $16, rax
  movq rax, [rbp + -2344]
  movq [rbp + -2344], rax
  movq rax, [rbp + -2352]
  movq [rbp + -2352], rax
  mov rax, [rax]
  movq rax, [rbp + -2360]
  movq [rbp + -2360], rcx
  call lm_print_str
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -2368]
  movq [rbp + -2368], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2376]
  movq [rbp + -2376], rax
  addq $16, rax
  movq rax, [rbp + -2384]
  movq [rbp + -2384], rax
  movq rax, [rbp + -2392]
  movq [rbp + -2392], rax
  mov rax, [rax]
  movq rax, [rbp + -2400]
  movq [rbp + -2400], rcx
  call lm_print_str
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -2408]
  movq [rbp + -2408], rax
  addq $16, rax
  movq rax, [rbp + -2416]
  movq [rbp + -2416], rax
  movq rax, [rbp + -2424]
  movq [rbp + -2424], rax
  mov rax, [rax]
  movq rax, [rbp + -2432]
  movq [rbp + -2432], rcx
  call lm_print_str
  movq [rel str_const_69], rcx
  call lm_box_string
  movq rax, [rbp + -2440]
  movq [rbp + -2440], rcx
  movq $401, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2448]
  movq [rbp + -2448], rax
  addq $16, rax
  movq rax, [rbp + -2456]
  movq [rbp + -2456], rax
  movq rax, [rbp + -2464]
  movq [rbp + -2464], rax
  mov rax, [rax]
  movq rax, [rbp + -2472]
  movq [rbp + -2472], rcx
  call lm_print_str
  movq [rel str_const_70], rcx
  call lm_box_string
  movq rax, [rbp + -2480]
  movq [rbp + -2480], rcx
  movq $601, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2488]
  movq [rbp + -2488], rax
  addq $16, rax
  movq rax, [rbp + -2496]
  movq [rbp + -2496], rax
  movq rax, [rbp + -2504]
  movq [rbp + -2504], rax
  mov rax, [rax]
  movq rax, [rbp + -2512]
  movq [rbp + -2512], rcx
  call lm_print_str
  movq [rel str_const_71], rcx
  call lm_box_string
  movq rax, [rbp + -2520]
  movq [rbp + -2520], rax
  addq $16, rax
  movq rax, [rbp + -2528]
  movq [rbp + -2528], rax
  movq rax, [rbp + -2536]
  movq [rbp + -2536], rax
  mov rax, [rax]
  movq rax, [rbp + -2544]
  movq [rbp + -2544], rcx
  call lm_print_str
  movq [rel str_const_72], rcx
  call lm_box_string
  movq rax, [rbp + -2552]
  movq [rbp + -2552], rcx
  movq $121, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2560]
  movq [rbp + -2560], rax
  addq $16, rax
  movq rax, [rbp + -2568]
  movq [rbp + -2568], rax
  movq rax, [rbp + -2576]
  movq [rbp + -2576], rax
  mov rax, [rax]
  movq rax, [rbp + -2584]
  movq [rbp + -2584], rcx
  call lm_print_str
  movq [rel str_const_73], rcx
  call lm_box_string
  movq rax, [rbp + -2592]
  movq [rbp + -2592], rcx
  movq $2001, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2600]
  movq [rbp + -2600], rax
  addq $16, rax
  movq rax, [rbp + -2608]
  movq [rbp + -2608], rax
  movq rax, [rbp + -2616]
  movq [rbp + -2616], rax
  mov rax, [rax]
  movq rax, [rbp + -2624]
  movq [rbp + -2624], rcx
  call lm_print_str
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -2632]
  movq [rbp + -2632], rax
  addq $16, rax
  movq rax, [rbp + -2640]
  movq [rbp + -2640], rax
  movq rax, [rbp + -2648]
  movq [rbp + -2648], rax
  mov rax, [rax]
  movq rax, [rbp + -2656]
  movq [rbp + -2656], rcx
  call lm_print_str
  movq [rel str_const_75], rcx
  call lm_box_string
  movq rax, [rbp + -2664]
  movq [rbp + -2664], rcx
  movq $1201, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2672]
  movq [rbp + -2672], rax
  addq $16, rax
  movq rax, [rbp + -2680]
  movq [rbp + -2680], rax
  movq rax, [rbp + -2688]
  movq [rbp + -2688], rax
  mov rax, [rax]
  movq rax, [rbp + -2696]
  movq [rbp + -2696], rcx
  call lm_print_str
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -2704]
  movq [rbp + -2704], rcx
  movq $161, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2712]
  movq [rbp + -2712], rax
  addq $16, rax
  movq rax, [rbp + -2720]
  movq [rbp + -2720], rax
  movq rax, [rbp + -2728]
  movq [rbp + -2728], rax
  mov rax, [rax]
  movq rax, [rbp + -2736]
  movq [rbp + -2736], rcx
  call lm_print_str
  movq [rel str_const_77], rcx
  call lm_box_string
  movq rax, [rbp + -2744]
  movq [rbp + -2744], rax
  addq $16, rax
  movq rax, [rbp + -2752]
  movq [rbp + -2752], rax
  movq rax, [rbp + -2760]
  movq [rbp + -2760], rax
  mov rax, [rax]
  movq rax, [rbp + -2768]
  movq [rbp + -2768], rcx
  call lm_print_str
  movq $41, rcx
  call validatePositive
  movq $201, rcx
  call validatePositive
  movq $801, rcx
  call validatePositive
  movq [rel str_const_78], rcx
  call lm_box_string
  movq rax, [rbp + -2776]
  movq [rbp + -2776], rcx
  movq $r294, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2784]
  movq [rbp + -2784], rax
  addq $16, rax
  movq rax, [rbp + -2792]
  movq [rbp + -2792], rax
  movq rax, [rbp + -2800]
  movq [rbp + -2800], rax
  mov rax, [rax]
  movq rax, [rbp + -2808]
  movq [rbp + -2808], rcx
  call lm_print_str
  movq [rel str_const_79], rcx
  call lm_box_string
  movq rax, [rbp + -2816]
  movq [rbp + -2816], rcx
  movq $r297, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2824]
  movq [rbp + -2824], rax
  addq $16, rax
  movq rax, [rbp + -2832]
  movq [rbp + -2832], rax
  movq rax, [rbp + -2840]
  movq [rbp + -2840], rax
  mov rax, [rax]
  movq rax, [rbp + -2848]
  movq [rbp + -2848], rcx
  call lm_print_str
  movq [rel str_const_80], rcx
  call lm_box_string
  movq rax, [rbp + -2856]
  movq [rbp + -2856], rcx
  movq $r300, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2864]
  movq [rbp + -2864], rax
  addq $16, rax
  movq rax, [rbp + -2872]
  movq [rbp + -2872], rax
  movq rax, [rbp + -2880]
  movq [rbp + -2880], rax
  mov rax, [rax]
  movq rax, [rbp + -2888]
  movq [rbp + -2888], rcx
  call lm_print_str
  movq [rel str_const_81], rcx
  call lm_box_string
  movq rax, [rbp + -2896]
  movq [rbp + -2896], rax
  addq $16, rax
  movq rax, [rbp + -2904]
  movq [rbp + -2904], rax
  movq rax, [rbp + -2912]
  movq [rbp + -2912], rax
  mov rax, [rax]
  movq rax, [rbp + -2920]
  movq [rbp + -2920], rcx
  call lm_print_str
  movq $81, rcx
  movq $4001, rdx
  movq $1601, r8
  call processRefined
  movq $401, rcx
  movq $7201, rdx
  movq $2401, r8
  call processRefined
  movq [rel str_const_82], rcx
  call lm_box_string
  movq rax, [rbp + -2928]
  movq [rbp + -2928], rcx
  movq $r316, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2936]
  movq [rbp + -2936], rax
  addq $16, rax
  movq rax, [rbp + -2944]
  movq [rbp + -2944], rax
  movq rax, [rbp + -2952]
  movq [rbp + -2952], rax
  mov rax, [rax]
  movq rax, [rbp + -2960]
  movq [rbp + -2960], rcx
  call lm_print_str
  movq [rel str_const_83], rcx
  call lm_box_string
  movq rax, [rbp + -2968]
  movq [rbp + -2968], rcx
  movq $r321, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2976]
  movq [rbp + -2976], rax
  addq $16, rax
  movq rax, [rbp + -2984]
  movq [rbp + -2984], rax
  movq rax, [rbp + -2992]
  movq [rbp + -2992], rax
  mov rax, [rax]
  movq rax, [rbp + -3000]
  movq [rbp + -3000], rcx
  call lm_print_str
  movq [rel str_const_84], rcx
  call lm_box_string
  movq rax, [rbp + -3008]
  movq [rbp + -3008], rax
  addq $16, rax
  movq rax, [rbp + -3016]
  movq [rbp + -3016], rax
  movq rax, [rbp + -3024]
  movq [rbp + -3024], rax
  mov rax, [rax]
  movq rax, [rbp + -3032]
  movq [rbp + -3032], rcx
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

.globl processRefined
processRefined:
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
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
processRefined_entry:
processRefined_block_0:
  movq [rbp + -64], rax
  addq [rbp + -72], rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  addq [rbp + -72], rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  addq [rbp + -80], rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  jmp processRefined_epilogue
processRefined_epilogue:
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
.Lfunc_end_processRefined:

.globl getLargeNumber
getLargeNumber:
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
getLargeNumber_entry:
getLargeNumber_block_0:
  movq $0, rax
  jmp getLargeNumber_epilogue
getLargeNumber_epilogue:
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
.Lfunc_end_getLargeNumber:

.globl processLarge
processLarge:
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
processLarge_entry:
processLarge_block_0:
  movq [rbp + -64], rax
  addq $401, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp processLarge_epilogue
processLarge_epilogue:
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
.Lfunc_end_processLarge:

.globl getPositiveNumber
getPositiveNumber:
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
getPositiveNumber_entry:
getPositiveNumber_block_0:
  movq $0, rax
  jmp getPositiveNumber_epilogue
getPositiveNumber_epilogue:
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
.Lfunc_end_getPositiveNumber:

.globl processPositive
processPositive:
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
processPositive_entry:
processPositive_block_0:
  movq [rbp + -64], rax
  imulq $17, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp processPositive_epilogue
processPositive_epilogue:
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
.Lfunc_end_processPositive:

.globl isLarge
isLarge:
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
isLarge_entry:
isLarge_block_0:
  movq [rbp + -64], rax
  cmpq $801, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp isLarge_epilogue
isLarge_epilogue:
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
.Lfunc_end_isLarge:

.globl isPositive
isPositive:
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
isPositive_entry:
isPositive_block_0:
  movq [rbp + -64], rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp isPositive_epilogue
isPositive_epilogue:
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
.Lfunc_end_isPositive:

.globl validatePositive
validatePositive:
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
validatePositive_entry:
validatePositive_block_0:
  movq [rbp + -64], rax
  cmpq $401, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne validatePositive_block_3
  jmp validatePositive_block_5
validatePositive_block_3:
  jmp validatePositive_block_3
  movq [rel str_const_85], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp validatePositive_epilogue
validatePositive_block_5:
  movq [rbp + -64], rax
  cmpq $81, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne validatePositive_block_8
  jmp validatePositive_block_10
validatePositive_block_8:
  jmp validatePositive_block_8
  movq [rel str_const_86], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp validatePositive_epilogue
validatePositive_block_10:
  movq [rel str_const_87], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  jmp validatePositive_epilogue
validatePositive_epilogue:
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
.Lfunc_end_validatePositive:

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

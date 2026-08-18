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
  .string "=== Enum Type Tests ==="
.align 8
str_const_1:
  .string "
--- Test 1: Basic Enum Declaration ---"
.align 8
str_const_2:
  .string "Color 1: %s"
.align 8
str_const_3:
  .string "Color 2: %s"
.align 8
str_const_4:
  .string "Color 3: %s"
.align 8
str_const_5:
  .string "
--- Test 2: Enum with Associated Values ---"
.align 8
str_const_6:
  .string "Operation completed"
.align 8
str_const_7:
  .string "Something went wrong"
.align 8
str_const_8:
  .string "Result 1: %s"
.align 8
str_const_9:
  .string "Result 2: %s"
.align 8
str_const_10:
  .string "Result 3: %s"
.align 8
str_const_11:
  .string "
--- Test 3: Enum Pattern Matching ---"
.align 8
str_const_12:
  .string "Description 1: %s"
.align 8
str_const_13:
  .string "Description 2: %s"
.align 8
str_const_14:
  .string "Description 3: %s"
.align 8
str_const_15:
  .string "
--- Test 4: Enum with Multiple Variants ---"
.align 8
str_const_16:
  .string "Status 1: %s"
.align 8
str_const_17:
  .string "Status 2: %s"
.align 8
str_const_18:
  .string "Status 3: %s"
.align 8
str_const_19:
  .string "Status 4: %s"
.align 8
str_const_20:
  .string "Status 5: %s"
.align 8
str_const_21:
  .string "
--- Test 5: Enum in Function Parameters ---"
.align 8
str_const_22:
  .string "Is Active 1: %s"
.align 8
str_const_23:
  .string "Is Active 2: %s"
.align 8
str_const_24:
  .string "Is Active 3: %s"
.align 8
str_const_25:
  .string "
--- Test 6: Enum with Numeric Association ---"
.align 8
str_const_26:
  .string "Priority 1: %s"
.align 8
str_const_27:
  .string "Priority 2: %s"
.align 8
str_const_28:
  .string "Priority 3: %s"
.align 8
str_const_29:
  .string "
--- Test 7: Enum Type Compatibility ---"
.align 8
str_const_30:
  .string "Color variable: %s"
.align 8
str_const_31:
  .string "Status variable: %s"
.align 8
str_const_32:
  .string "
--- Test 8: Enum in Collections ---"
.align 8
str_const_33:
  .string "Colors list: %s"
.align 8
str_const_34:
  .string "Statuses list: %s"
.align 8
str_const_35:
  .string "
--- Test 9: Enum Exhaustiveness ---"
.align 8
str_const_36:
  .string "
--- Test 7: Complex Enum with Mixed Variants ---"
.align 8
str_const_37:
  .string "Hello World"
.align 8
str_const_38:
  .string "
--- Test 8: Nested Enum Usage ---"
.align 8
str_const_39:
  .string "
--- Test 9: Enum Ambiguity Handling ---"
.align 8
str_const_40:
  .string "State: %s"
.align 8
str_const_41:
  .string "Status: %s"
.align 8
str_const_42:
  .string "Result: %s"
.align 8
str_const_43:
  .string "
--- Test 10: Wildcards in Matching ---"
.align 8
str_const_44:
  .string "
=== Enum Type Tests Complete ==="
.align 8
str_const_45:
  .string "Not active (%s)"
.align 8
str_const_46:
  .string "Connected and active"
.align 8
str_const_47:
  .string "Shape is hidden"
.align 8
str_const_48:
  .string "Visible Rectangle with %sx%s"
.align 8
str_const_49:
  .string "Visible Circle with radius %s"
.align 8
str_const_50:
  .string "The color blue"
.align 8
str_const_51:
  .string "The color green"
.align 8
str_const_52:
  .string "The color red"
.align 8
str_const_53:
  .string "Changing color to RGB(%s, %s, %s)"
.align 8
str_const_54:
  .string "Writing: %s"
.align 8
str_const_55:
  .string "Moving to (%s, %s)"
.align 8
str_const_56:
  .string "Quitting..."
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
  sub rsp, 1624
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
  movq $0, rdx
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
  movq $0, rdx
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
  movq $0, rdx
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
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -296], rcx
  movq $0, rdx
  call lm_rt_str_format
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
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -336], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  addq $16, rax
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  movq rax, [rbp + -360]
  movq [rbp + -360], rax
  mov rax, [rax]
  movq rax, [rbp + -368]
  movq [rbp + -368], rcx
  call lm_print_str
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -376], rcx
  movq $0, rdx
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
  movq [rel str_const_11], rcx
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
  movq $0, rcx
  call describeColor
  movq $0, rcx
  call describeColor
  movq $0, rcx
  call describeColor
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -448], rcx
  movq $r43, rdx
  call lm_rt_str_format
  movq rax, [rbp + -456]
  movq [rbp + -456], rax
  addq $16, rax
  movq rax, [rbp + -464]
  movq [rbp + -464], rax
  movq rax, [rbp + -472]
  movq [rbp + -472], rax
  mov rax, [rax]
  movq rax, [rbp + -480]
  movq [rbp + -480], rcx
  call lm_print_str
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -488]
  movq [rbp + -488], rcx
  movq $r46, rdx
  call lm_rt_str_format
  movq rax, [rbp + -496]
  movq [rbp + -496], rax
  addq $16, rax
  movq rax, [rbp + -504]
  movq [rbp + -504], rax
  movq rax, [rbp + -512]
  movq [rbp + -512], rax
  mov rax, [rax]
  movq rax, [rbp + -520]
  movq [rbp + -520], rcx
  call lm_print_str
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -528], rcx
  movq $r49, rdx
  call lm_rt_str_format
  movq rax, [rbp + -536]
  movq [rbp + -536], rax
  addq $16, rax
  movq rax, [rbp + -544]
  movq [rbp + -544], rax
  movq rax, [rbp + -552]
  movq [rbp + -552], rax
  mov rax, [rax]
  movq rax, [rbp + -560]
  movq [rbp + -560], rcx
  call lm_print_str
  movq [rel str_const_15], rcx
  call lm_box_string
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
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -600]
  movq [rbp + -600], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -608]
  movq [rbp + -608], rax
  addq $16, rax
  movq rax, [rbp + -616]
  movq [rbp + -616], rax
  movq rax, [rbp + -624]
  movq [rbp + -624], rax
  mov rax, [rax]
  movq rax, [rbp + -632]
  movq [rbp + -632], rcx
  call lm_print_str
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -640], rcx
  movq $0, rdx
  call lm_rt_str_format
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
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -680]
  movq [rbp + -680], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -688]
  movq [rbp + -688], rax
  addq $16, rax
  movq rax, [rbp + -696]
  movq [rbp + -696], rax
  movq rax, [rbp + -704]
  movq [rbp + -704], rax
  mov rax, [rax]
  movq rax, [rbp + -712]
  movq [rbp + -712], rcx
  call lm_print_str
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -720]
  movq [rbp + -720], rcx
  movq $0, rdx
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
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -760]
  movq [rbp + -760], rcx
  movq $0, rdx
  call lm_rt_str_format
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
  movq $0, rcx
  call isActive
  movq $0, rcx
  call isActive
  movq $0, rcx
  call isActive
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -832]
  movq [rbp + -832], rcx
  movq $r90, rdx
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
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -872]
  movq [rbp + -872], rcx
  movq $r93, rdx
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
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -912]
  movq [rbp + -912], rcx
  movq $r96, rdx
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
  movq [rel str_const_25], rcx
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
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -984]
  movq [rbp + -984], rcx
  movq $0, rdx
  call lm_rt_str_format
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
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -1024]
  movq [rbp + -1024], rcx
  movq $0, rdx
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
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -1064]
  movq [rbp + -1064], rcx
  movq $0, rdx
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
  movq [rel str_const_29], rcx
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
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -1136]
  movq [rbp + -1136], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1144]
  movq [rbp + -1144], rax
  addq $16, rax
  movq rax, [rbp + -1152]
  movq [rbp + -1152], rax
  movq rax, [rbp + -1160]
  movq [rbp + -1160], rax
  mov rax, [rax]
  movq rax, [rbp + -1168]
  movq [rbp + -1168], rcx
  call lm_print_str
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -1176]
  movq [rbp + -1176], rcx
  movq $0, rdx
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
  movq [rel str_const_32], rcx
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
  movq $0, rcx
  call lm_list_new
  movq $r144, rcx
  movq $0, rdx
  call lm_list_append
  movq $r144, rcx
  movq $0, rdx
  call lm_list_append
  movq $r144, rcx
  movq $0, rdx
  call lm_list_append
  movq $r144, rcx
  movq $0, rdx
  call lm_list_append
  movq $r144, rcx
  movq $0, rdx
  call lm_list_append
  movq $0, rcx
  call lm_list_new
  movq $r156, rcx
  movq $0, rdx
  call lm_list_append
  movq $r156, rcx
  movq $0, rdx
  call lm_list_append
  movq $r156, rcx
  movq $0, rdx
  call lm_list_append
  movq $r156, rcx
  movq $0, rdx
  call lm_list_append
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -1248]
  movq [rbp + -1248], rcx
  movq $r144, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1256]
  movq [rbp + -1256], rax
  addq $16, rax
  movq rax, [rbp + -1264]
  movq [rbp + -1264], rax
  movq rax, [rbp + -1272]
  movq [rbp + -1272], rax
  mov rax, [rax]
  movq rax, [rbp + -1280]
  movq [rbp + -1280], rcx
  call lm_print_str
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -1288]
  movq [rbp + -1288], rcx
  movq $r156, rdx
  call lm_rt_str_format
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
  movq [rel str_const_35], rcx
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
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -1360]
  movq [rbp + -1360], rax
  addq $16, rax
  movq rax, [rbp + -1368]
  movq [rbp + -1368], rax
  movq rax, [rbp + -1376]
  movq [rbp + -1376], rax
  mov rax, [rax]
  movq rax, [rbp + -1384]
  movq [rbp + -1384], rcx
  call lm_print_str
  movq $0, rcx
  call processMessage
  movq $0, rcx
  call processMessage
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -1392]
  movq $0, rcx
  call processMessage
  movq $0, rcx
  call processMessage
  movq [rel str_const_38], rcx
  call lm_box_string
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
  movq $0, rcx
  call describeShapeStatus
  movq $0, rcx
  call describeShapeStatus
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -1432]
  movq [rbp + -1432], rax
  addq $16, rax
  movq rax, [rbp + -1440]
  movq [rbp + -1440], rax
  movq rax, [rbp + -1448]
  movq [rbp + -1448], rax
  mov rax, [rax]
  movq rax, [rbp + -1456]
  movq [rbp + -1456], rcx
  call lm_print_str
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -1464]
  movq [rbp + -1464], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1472]
  movq [rbp + -1472], rax
  addq $16, rax
  movq rax, [rbp + -1480]
  movq [rbp + -1480], rax
  movq rax, [rbp + -1488]
  movq [rbp + -1488], rax
  mov rax, [rax]
  movq rax, [rbp + -1496]
  movq [rbp + -1496], rcx
  call lm_print_str
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -1504]
  movq [rbp + -1504], rcx
  movq $0, rdx
  call lm_rt_str_format
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
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -1544]
  movq [rbp + -1544], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1552]
  movq [rbp + -1552], rax
  addq $16, rax
  movq rax, [rbp + -1560]
  movq [rbp + -1560], rax
  movq rax, [rbp + -1568]
  movq [rbp + -1568], rax
  mov rax, [rax]
  movq rax, [rbp + -1576]
  movq [rbp + -1576], rcx
  call lm_print_str
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -1584]
  movq [rbp + -1584], rax
  addq $16, rax
  movq rax, [rbp + -1592]
  movq [rbp + -1592], rax
  movq rax, [rbp + -1600]
  movq [rbp + -1600], rax
  mov rax, [rax]
  movq rax, [rbp + -1608]
  movq [rbp + -1608], rcx
  call lm_print_str
  movq $0, rcx
  call checkConnectivity
  movq $0, rcx
  call checkConnectivity
  movq $0, rcx
  call checkConnectivity
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -1616]
  movq [rbp + -1616], rax
  addq $16, rax
  movq rax, [rbp + -1624]
  movq [rbp + -1624], rax
  movq rax, [rbp + -1632]
  movq [rbp + -1632], rax
  mov rax, [rax]
  movq rax, [rbp + -1640]
  movq [rbp + -1640], rcx
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

.globl checkConnectivity
checkConnectivity:
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
checkConnectivity_entry:
checkConnectivity_block_0:
  jmp checkConnectivity_block_1
checkConnectivity_block_1:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne checkConnectivity_block_5
  jmp checkConnectivity_block_6
checkConnectivity_block_5:
  jmp checkConnectivity_block_5
  jmp checkConnectivity_block_11
checkConnectivity_block_6:
  jmp checkConnectivity_block_7
checkConnectivity_block_7:
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  call lm_rt_str_format
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  addq $16, rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  mov rax, [rax]
  movq rax, [rbp + -112]
  movq [rbp + -112], rcx
  call lm_print_str
  jmp checkConnectivity_block_14
checkConnectivity_block_11:
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  addq $16, rax
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  mov rax, [rax]
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  call lm_print_str
  jmp checkConnectivity_block_14
checkConnectivity_block_14:
  movq $0, rax
  jmp checkConnectivity_epilogue
checkConnectivity_epilogue:
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
.Lfunc_end_checkConnectivity:

.globl describeShapeStatus
describeShapeStatus:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 200
  mov [rbp + -64], rcx
describeShapeStatus_entry:
describeShapeStatus_block_0:
  jmp describeShapeStatus_block_1
describeShapeStatus_block_1:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne describeShapeStatus_block_5
  jmp describeShapeStatus_block_7
describeShapeStatus_block_5:
  jmp describeShapeStatus_block_5
  jmp describeShapeStatus_block_15
describeShapeStatus_block_7:
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne describeShapeStatus_block_11
  jmp describeShapeStatus_block_50
describeShapeStatus_block_11:
  jmp describeShapeStatus_block_11
  jmp describeShapeStatus_block_12
describeShapeStatus_block_12:
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  addq $16, rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  mov rax, [rax]
  movq rax, [rbp + -112]
  movq [rbp + -112], rcx
  call lm_print_str
  jmp describeShapeStatus_block_50
describeShapeStatus_block_15:
  jmp describeShapeStatus_block_17
describeShapeStatus_block_17:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne describeShapeStatus_block_21
  jmp describeShapeStatus_block_23
describeShapeStatus_block_21:
  jmp describeShapeStatus_block_21
  jmp describeShapeStatus_block_44
describeShapeStatus_block_23:
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne describeShapeStatus_block_27
  jmp describeShapeStatus_block_49
describeShapeStatus_block_27:
  jmp describeShapeStatus_block_27
  jmp describeShapeStatus_block_33
describeShapeStatus_block_33:
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  movq $0, rdx
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
  jmp describeShapeStatus_block_49
describeShapeStatus_block_44:
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -184], rcx
  movq $0, rdx
  call lm_rt_str_format
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
  call lm_print_str
  jmp describeShapeStatus_block_49
describeShapeStatus_block_49:
  jmp describeShapeStatus_block_50
describeShapeStatus_block_50:
  movq $0, rax
  jmp describeShapeStatus_epilogue
describeShapeStatus_epilogue:
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
.Lfunc_end_describeShapeStatus:

.globl describeColor
describeColor:
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
describeColor_entry:
describeColor_block_0:
  jmp describeColor_block_1
describeColor_block_1:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne describeColor_block_5
  jmp describeColor_block_6
describeColor_block_5:
  jmp describeColor_block_5
  jmp describeColor_block_21
describeColor_block_6:
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne describeColor_block_10
  jmp describeColor_block_11
describeColor_block_10:
  jmp describeColor_block_10
  jmp describeColor_block_19
describeColor_block_11:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne describeColor_block_15
  jmp describeColor_block_16
describeColor_block_15:
  jmp describeColor_block_15
  jmp describeColor_block_17
describeColor_block_16:
  movq $0, rax
  jmp describeColor_epilogue
describeColor_block_17:
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp describeColor_epilogue
describeColor_block_19:
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  jmp describeColor_epilogue
describeColor_block_21:
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp describeColor_epilogue
describeColor_epilogue:
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
.Lfunc_end_describeColor:

.globl processMessage
processMessage:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 264
  mov [rbp + -64], rcx
processMessage_entry:
processMessage_block_0:
  jmp processMessage_block_1
processMessage_block_1:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne processMessage_block_5
  jmp processMessage_block_6
processMessage_block_5:
  jmp processMessage_block_5
  jmp processMessage_block_64
processMessage_block_6:
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne processMessage_block_10
  jmp processMessage_block_16
processMessage_block_10:
  jmp processMessage_block_10
  jmp processMessage_block_53
processMessage_block_16:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne processMessage_block_20
  jmp processMessage_block_22
processMessage_block_20:
  jmp processMessage_block_20
  jmp processMessage_block_48
processMessage_block_22:
  movq $0, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne processMessage_block_26
  jmp processMessage_block_67
processMessage_block_26:
  jmp processMessage_block_26
  jmp processMessage_block_34
processMessage_block_34:
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -112]
  movq [rbp + -112], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  movq $0, rdx
  call lm_rt_str_format
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
  call lm_print_str
  jmp processMessage_block_67
processMessage_block_48:
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rcx
  movq $0, rdx
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
  jmp processMessage_block_67
processMessage_block_53:
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -208]
  movq [rbp + -208], rcx
  movq $0, rdx
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
  jmp processMessage_block_67
processMessage_block_64:
  movq [rel str_const_56], rcx
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
  jmp processMessage_block_67
processMessage_block_67:
  movq $0, rax
  jmp processMessage_epilogue
processMessage_epilogue:
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
.Lfunc_end_processMessage:

.globl isActive
isActive:
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
isActive_entry:
isActive_block_0:
  jmp isActive_block_1
isActive_block_1:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne isActive_block_5
  jmp isActive_block_6
isActive_block_5:
  jmp isActive_block_5
  jmp isActive_block_9
isActive_block_6:
  jmp isActive_block_7
isActive_block_7:
  movq $10, rax
  jmp isActive_epilogue
isActive_block_9:
  movq $18, rax
  jmp isActive_epilogue
isActive_epilogue:
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
.Lfunc_end_isActive:

.globl getColorCode
getColorCode:
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
getColorCode_entry:
getColorCode_block_0:
  jmp getColorCode_block_1
getColorCode_block_1:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne getColorCode_block_5
  jmp getColorCode_block_6
getColorCode_block_5:
  jmp getColorCode_block_5
  jmp getColorCode_block_21
getColorCode_block_6:
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne getColorCode_block_10
  jmp getColorCode_block_11
getColorCode_block_10:
  jmp getColorCode_block_10
  jmp getColorCode_block_19
getColorCode_block_11:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne getColorCode_block_15
  jmp getColorCode_block_16
getColorCode_block_15:
  jmp getColorCode_block_15
  jmp getColorCode_block_17
getColorCode_block_16:
  movq $0, rax
  jmp getColorCode_epilogue
getColorCode_block_17:
  movq $513, rax
  jmp getColorCode_epilogue
getColorCode_block_19:
  movq $1025, rax
  jmp getColorCode_epilogue
getColorCode_block_21:
  movq $2041, rax
  jmp getColorCode_epilogue
getColorCode_epilogue:
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
.Lfunc_end_getColorCode:

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

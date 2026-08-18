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
  .string "=== Advanced Type Tests ==="
.align 8
str_const_1:
  .string "
--- Test 1: Complex Type Alias Chains ---"
.align 8
str_const_2:
  .string "Base ID: %s"
.align 8
str_const_3:
  .string "User ID: %s"
.align 8
str_const_4:
  .string "Admin ID: %s"
.align 8
str_const_5:
  .string "Super Admin ID: %s"
.align 8
str_const_6:
  .string "
--- Test 2: Union Type Combinations ---"
.align 8
str_const_7:
  .string "text"
.align 8
str_const_8:
  .string "All types 1 (int): %s"
.align 8
str_const_9:
  .string "All types 2 (float): %s"
.align 8
str_const_10:
  .string "All types 3 (str): %s"
.align 8
str_const_11:
  .string "All types 4 (bool): %s"
.align 8
str_const_12:
  .string "
--- Test 3: Function Parameter Compatibility ---"
.align 8
str_const_13:
  .string "hello"
.align 8
str_const_14:
  .string "Format output 1: %s"
.align 8
str_const_15:
  .string "Format output 2: %s"
.align 8
str_const_16:
  .string "
--- Test 4: Recursive-like Type Structures ---"
.align 8
str_const_17:
  .string "leaf"
.align 8
str_const_18:
  .string "Node 1: %s"
.align 8
str_const_19:
  .string "Node 2: %s"
.align 8
str_const_20:
  .string "
--- Test 5: Type Inference with Unions ---"
.align 8
str_const_21:
  .string "test"
.align 8
str_const_22:
  .string "Infer 1: %s"
.align 8
str_const_23:
  .string "Infer 2: %s"
.align 8
str_const_24:
  .string "Infer 3: %s"
.align 8
str_const_25:
  .string "
--- Test 6: Union Return Types ---"
.align 8
str_const_26:
  .string "Process 1: %s"
.align 8
str_const_27:
  .string "Process 2: %s"
.align 8
str_const_28:
  .string "Process 3: %s"
.align 8
str_const_29:
  .string "
--- Test 7: Complex Type Alias Unions ---"
.align 8
str_const_30:
  .string "combined"
.align 8
str_const_31:
  .string "Combined 1 (int): %s"
.align 8
str_const_32:
  .string "Combined 2 (str): %s"
.align 8
str_const_33:
  .string "Combined 3 (bool): %s"
.align 8
str_const_34:
  .string "Combined 4 (float): %s"
.align 8
str_const_35:
  .string "
--- Test 8: Type System Stress Test ---"
.align 8
str_const_36:
  .string "stress"
.align 8
str_const_37:
  .string "Stress 1: %s"
.align 8
str_const_38:
  .string "Stress 2: %s"
.align 8
str_const_39:
  .string "Stress 3: %s"
.align 8
str_const_40:
  .string "Stress 4: %s"
.align 8
str_const_41:
  .string "
--- Test 9: Typed Collections (Lists) ---"
.align 8
str_const_42:
  .string "hello"
.align 8
str_const_43:
  .string "world"
.align 8
str_const_44:
  .string "test"
.align 8
str_const_45:
  .string "Numbers: %s"
.align 8
str_const_46:
  .string "Words: %s"
.align 8
str_const_47:
  .string "Flags: %s"
.align 8
str_const_48:
  .string "Scores: %s"
.align 8
str_const_49:
  .string "
--- Test 10: Typed Collections (Dictionaries) ---"
.align 8
str_const_50:
  .string "Alice"
.align 8
str_const_51:
  .string "Bob"
.align 8
str_const_52:
  .string "Charlie"
.align 8
str_const_53:
  .string "First"
.align 8
str_const_54:
  .string "Second"
.align 8
str_const_55:
  .string "Third"
.align 8
str_const_56:
  .string "Age map: %s"
.align 8
str_const_57:
  .string "Price map: %s"
.align 8
str_const_58:
  .string "Name map: %s"
.align 8
str_const_59:
  .string "
--- Test 11: Nested Collections ---"
.align 8
str_const_60:
  .string "Alice"
.align 8
str_const_61:
  .string "Bob"
.align 8
str_const_62:
  .string "Matrix: %s"
.align 8
str_const_63:
  .string "Student grades: %s"
.align 8
str_const_64:
  .string "
--- Test 12: Structural Types ---"
.align 8
str_const_65:
  .string "Structural types defined successfully"
.align 8
str_const_66:
  .string "
=== Advanced Type Tests Complete ==="
.align 8
str_const_67:
  .string "processed"
.align 8
str_const_68:
  .string "Type inferred for: %s"
.align 8
str_const_69:
  .string "Formatted: %s"
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
  sub rsp, 2056
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
  movq $8001, rdx
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
  movq $16001, rdx
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
  movq $24001, rdx
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
  movq [rbp + -248], rcx
  movq $32001, rdx
  call lm_rt_str_format
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  addq $16, rax
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  mov rax, [rax]
  movq rax, [rbp + -280]
  movq [rbp + -280], rcx
  call lm_print_str
  movq [rel str_const_6], rcx
  call lm_box_string
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
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -328], rcx
  movq $337, rdx
  call lm_rt_str_format
  movq rax, [rbp + -336]
  movq [rbp + -336], rax
  addq $16, rax
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  mov rax, [rax]
  movq rax, [rbp + -360]
  movq [rbp + -360], rcx
  call lm_print_str
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -368], rcx
  movq $2, rdx
  call lm_rt_str_format
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  addq $16, rax
  movq rax, [rbp + -384]
  movq [rbp + -384], rax
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  mov rax, [rax]
  movq rax, [rbp + -400]
  movq [rbp + -400], rcx
  call lm_print_str
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -408], rcx
  movq [rbp + -320], rdx
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
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -448], rcx
  movq $18, rdx
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
  movq [rel str_const_12], rcx
  call lm_box_string
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
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq $985, rcx
  call formatInput
  movq [rbp + -520], rcx
  call formatInput
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -528], rcx
  movq $r42, rdx
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
  movq [rbp + -568], rcx
  movq $r44, rdx
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
  movq [rel str_const_16], rcx
  call lm_box_string
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
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -648]
  movq [rbp + -648], rcx
  movq $801, rdx
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
  movq [rbp + -640], rdx
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
  movq $337, rcx
  call inferType
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -760]
  movq [rbp + -760], rcx
  call inferType
  movq $18, rcx
  call inferType
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -768]
  movq [rbp + -768], rcx
  movq $r65, rdx
  call lm_rt_str_format
  movq rax, [rbp + -776]
  movq [rbp + -776], rax
  addq $16, rax
  movq rax, [rbp + -784]
  movq [rbp + -784], rax
  movq rax, [rbp + -792]
  movq [rbp + -792], rax
  mov rax, [rax]
  movq rax, [rbp + -800]
  movq [rbp + -800], rcx
  call lm_print_str
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -808]
  movq [rbp + -808], rcx
  movq $r68, rdx
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
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -848]
  movq [rbp + -848], rcx
  movq $r71, rdx
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
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -888]
  movq [rbp + -888], rax
  addq $16, rax
  movq rax, [rbp + -896]
  movq [rbp + -896], rax
  movq rax, [rbp + -904]
  movq [rbp + -904], rax
  mov rax, [rax]
  movq rax, [rbp + -912]
  movq [rbp + -912], rcx
  call lm_print_str
  movq $9, rcx
  call processData
  movq $17, rcx
  call processData
  movq $25, rcx
  call processData
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -920]
  movq [rbp + -920], rcx
  movq $r85, rdx
  call lm_rt_str_format
  movq rax, [rbp + -928]
  movq [rbp + -928], rax
  addq $16, rax
  movq rax, [rbp + -936]
  movq [rbp + -936], rax
  movq rax, [rbp + -944]
  movq [rbp + -944], rax
  mov rax, [rax]
  movq rax, [rbp + -952]
  movq [rbp + -952], rcx
  call lm_print_str
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -960]
  movq [rbp + -960], rcx
  movq $r88, rdx
  call lm_rt_str_format
  movq rax, [rbp + -968]
  movq [rbp + -968], rax
  addq $16, rax
  movq rax, [rbp + -976]
  movq [rbp + -976], rax
  movq rax, [rbp + -984]
  movq [rbp + -984], rax
  mov rax, [rax]
  movq rax, [rbp + -992]
  movq [rbp + -992], rcx
  call lm_print_str
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -1000]
  movq [rbp + -1000], rcx
  movq $r91, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1008]
  movq [rbp + -1008], rax
  addq $16, rax
  movq rax, [rbp + -1016]
  movq [rbp + -1016], rax
  movq rax, [rbp + -1024]
  movq [rbp + -1024], rax
  mov rax, [rax]
  movq rax, [rbp + -1032]
  movq [rbp + -1032], rcx
  call lm_print_str
  movq [rel str_const_29], rcx
  call lm_box_string
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
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -1072]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -1080]
  movq [rbp + -1080], rcx
  movq $985, rdx
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
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -1120]
  movq [rbp + -1120], rcx
  movq [rbp + -1072], rdx
  call lm_rt_str_format
  movq rax, [rbp + -1128]
  movq [rbp + -1128], rax
  addq $16, rax
  movq rax, [rbp + -1136]
  movq [rbp + -1136], rax
  movq rax, [rbp + -1144]
  movq [rbp + -1144], rax
  mov rax, [rax]
  movq rax, [rbp + -1152]
  movq [rbp + -1152], rcx
  call lm_print_str
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -1160]
  movq [rbp + -1160], rcx
  movq $18, rdx
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
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -1200]
  movq [rbp + -1200], rcx
  movq $2, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1208]
  movq [rbp + -1208], rax
  addq $16, rax
  movq rax, [rbp + -1216]
  movq [rbp + -1216], rax
  movq rax, [rbp + -1224]
  movq [rbp + -1224], rax
  mov rax, [rax]
  movq rax, [rbp + -1232]
  movq [rbp + -1232], rcx
  call lm_print_str
  movq [rel str_const_35], rcx
  call lm_box_string
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
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -1272]
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -1280]
  movq [rbp + -1280], rcx
  movq $7993, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1288]
  movq [rbp + -1288], rax
  addq $16, rax
  movq rax, [rbp + -1296]
  movq [rbp + -1296], rax
  movq rax, [rbp + -1304]
  movq [rbp + -1304], rax
  mov rax, [rax]
  movq rax, [rbp + -1312]
  movq [rbp + -1312], rcx
  call lm_print_str
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -1320]
  movq [rbp + -1320], rcx
  movq [rbp + -1272], rdx
  call lm_rt_str_format
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
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -1360]
  movq [rbp + -1360], rcx
  movq $10, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1368]
  movq [rbp + -1368], rax
  addq $16, rax
  movq rax, [rbp + -1376]
  movq [rbp + -1376], rax
  movq rax, [rbp + -1384]
  movq [rbp + -1384], rax
  mov rax, [rax]
  movq rax, [rbp + -1392]
  movq [rbp + -1392], rcx
  call lm_print_str
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -1400]
  movq [rbp + -1400], rcx
  movq $2, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1408]
  movq [rbp + -1408], rax
  addq $16, rax
  movq rax, [rbp + -1416]
  movq [rbp + -1416], rax
  movq rax, [rbp + -1424]
  movq [rbp + -1424], rax
  mov rax, [rax]
  movq rax, [rbp + -1432]
  movq [rbp + -1432], rcx
  call lm_print_str
  movq [rel str_const_41], rcx
  call lm_box_string
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
  movq $0, rcx
  call lm_list_new
  movq $r140, rcx
  movq $9, rdx
  call lm_list_append
  movq $r140, rcx
  movq $17, rdx
  call lm_list_append
  movq $r140, rcx
  movq $25, rdx
  call lm_list_append
  movq $r140, rcx
  movq $33, rdx
  call lm_list_append
  movq $r140, rcx
  movq $41, rdx
  call lm_list_append
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -1472]
  movq $r152, rcx
  movq [rbp + -1472], rdx
  call lm_list_append
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -1480]
  movq $r152, rcx
  movq [rbp + -1480], rdx
  call lm_list_append
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -1488]
  movq $r152, rcx
  movq [rbp + -1488], rdx
  call lm_list_append
  movq $0, rcx
  call lm_list_new
  movq $r160, rcx
  movq $18, rdx
  call lm_list_append
  movq $r160, rcx
  movq $10, rdx
  call lm_list_append
  movq $r160, rcx
  movq $18, rdx
  call lm_list_append
  movq $0, rcx
  call lm_list_new
  movq $r168, rcx
  movq $2, rdx
  call lm_list_append
  movq $r168, rcx
  movq $2, rdx
  call lm_list_append
  movq $r168, rcx
  movq $2, rdx
  call lm_list_append
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -1496]
  movq [rbp + -1496], rcx
  movq $r140, rdx
  call lm_rt_str_format
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
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -1536]
  movq [rbp + -1536], rcx
  movq $r152, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1544]
  movq [rbp + -1544], rax
  addq $16, rax
  movq rax, [rbp + -1552]
  movq [rbp + -1552], rax
  movq rax, [rbp + -1560]
  movq [rbp + -1560], rax
  mov rax, [rax]
  movq rax, [rbp + -1568]
  movq [rbp + -1568], rcx
  call lm_print_str
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -1576]
  movq [rbp + -1576], rcx
  movq $r160, rdx
  call lm_rt_str_format
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
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -1616]
  movq [rbp + -1616], rcx
  movq $r168, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1624]
  movq [rbp + -1624], rax
  addq $16, rax
  movq rax, [rbp + -1632]
  movq [rbp + -1632], rax
  movq rax, [rbp + -1640]
  movq [rbp + -1640], rax
  mov rax, [rax]
  movq rax, [rbp + -1648]
  movq [rbp + -1648], rcx
  call lm_print_str
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -1656]
  movq [rbp + -1656], rax
  addq $16, rax
  movq rax, [rbp + -1664]
  movq [rbp + -1664], rax
  movq rax, [rbp + -1672]
  movq [rbp + -1672], rax
  mov rax, [rax]
  movq rax, [rbp + -1680]
  movq [rbp + -1680], rcx
  call lm_print_str
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -1688]
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -1696]
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -1704]
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -1712]
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -1720]
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -1728]
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -1736]
  movq [rbp + -1736], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1744]
  movq [rbp + -1744], rax
  addq $16, rax
  movq rax, [rbp + -1752]
  movq [rbp + -1752], rax
  movq rax, [rbp + -1760]
  movq [rbp + -1760], rax
  mov rax, [rax]
  movq rax, [rbp + -1768]
  movq [rbp + -1768], rcx
  call lm_print_str
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -1776]
  movq [rbp + -1776], rcx
  movq $0, rdx
  call lm_rt_str_format
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
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -1816]
  movq [rbp + -1816], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1824]
  movq [rbp + -1824], rax
  addq $16, rax
  movq rax, [rbp + -1832]
  movq [rbp + -1832], rax
  movq rax, [rbp + -1840]
  movq [rbp + -1840], rax
  mov rax, [rax]
  movq rax, [rbp + -1848]
  movq [rbp + -1848], rcx
  call lm_print_str
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -1856]
  movq [rbp + -1856], rax
  addq $16, rax
  movq rax, [rbp + -1864]
  movq [rbp + -1864], rax
  movq rax, [rbp + -1872]
  movq [rbp + -1872], rax
  mov rax, [rax]
  movq rax, [rbp + -1880]
  movq [rbp + -1880], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  call lm_list_new
  movq $r226, rcx
  movq $9, rdx
  call lm_list_append
  movq $r226, rcx
  movq $17, rdx
  call lm_list_append
  movq $r225, rcx
  movq $r226, rdx
  call lm_list_append
  movq $0, rcx
  call lm_list_new
  movq $r232, rcx
  movq $25, rdx
  call lm_list_append
  movq $r232, rcx
  movq $33, rdx
  call lm_list_append
  movq $r225, rcx
  movq $r232, rdx
  call lm_list_append
  movq $0, rcx
  call lm_list_new
  movq $r238, rcx
  movq $41, rdx
  call lm_list_append
  movq $r238, rcx
  movq $49, rdx
  call lm_list_append
  movq $r225, rcx
  movq $r238, rdx
  call lm_list_append
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -1888]
  movq $0, rcx
  call lm_list_new
  movq $r247, rcx
  movq $2, rdx
  call lm_list_append
  movq $r247, rcx
  movq $2, rdx
  call lm_list_append
  movq $r247, rcx
  movq $2, rdx
  call lm_list_append
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -1896]
  movq $0, rcx
  call lm_list_new
  movq $r255, rcx
  movq $2, rdx
  call lm_list_append
  movq $r255, rcx
  movq $2, rdx
  call lm_list_append
  movq $r255, rcx
  movq $2, rdx
  call lm_list_append
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -1904]
  movq [rbp + -1904], rcx
  movq $r225, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1912]
  movq [rbp + -1912], rax
  addq $16, rax
  movq rax, [rbp + -1920]
  movq [rbp + -1920], rax
  movq rax, [rbp + -1928]
  movq [rbp + -1928], rax
  mov rax, [rax]
  movq rax, [rbp + -1936]
  movq [rbp + -1936], rcx
  call lm_print_str
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -1944]
  movq [rbp + -1944], rcx
  movq $0, rdx
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
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -1984]
  movq [rbp + -1984], rax
  addq $16, rax
  movq rax, [rbp + -1992]
  movq [rbp + -1992], rax
  movq rax, [rbp + -2000]
  movq [rbp + -2000], rax
  mov rax, [rax]
  movq rax, [rbp + -2008]
  movq [rbp + -2008], rcx
  call lm_print_str
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -2016]
  movq [rbp + -2016], rax
  addq $16, rax
  movq rax, [rbp + -2024]
  movq [rbp + -2024], rax
  movq rax, [rbp + -2032]
  movq [rbp + -2032], rax
  mov rax, [rax]
  movq rax, [rbp + -2040]
  movq [rbp + -2040], rcx
  call lm_print_str
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -2048]
  movq [rbp + -2048], rax
  addq $16, rax
  movq rax, [rbp + -2056]
  movq [rbp + -2056], rax
  movq rax, [rbp + -2064]
  movq [rbp + -2064], rax
  mov rax, [rax]
  movq rax, [rbp + -2072]
  movq [rbp + -2072], rcx
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

.globl processData
processData:
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
processData_entry:
processData_block_0:
  movq [rbp + -64], rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne processData_block_3
  jmp processData_block_5
processData_block_3:
  jmp processData_block_3
  movq $337, rax
  jmp processData_epilogue
processData_block_5:
  movq [rbp + -64], rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne processData_block_8
  jmp processData_block_10
processData_block_8:
  jmp processData_block_8
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp processData_epilogue
processData_block_10:
  movq $18, rax
  jmp processData_epilogue
processData_epilogue:
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
.Lfunc_end_processData:

.globl inferType
inferType:
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
inferType_entry:
inferType_block_0:
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call lm_rt_str_format
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp inferType_epilogue
inferType_epilogue:
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
.Lfunc_end_inferType:

.globl formatInput
formatInput:
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
formatInput_entry:
formatInput_block_0:
  movq [rel str_const_69], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call lm_rt_str_format
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp formatInput_epilogue
formatInput_epilogue:
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
.Lfunc_end_formatInput:

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

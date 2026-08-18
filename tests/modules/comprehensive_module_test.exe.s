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
  .string "========================================"
.align 8
str_const_1:
  .string "Comprehensive Module System Test Suite"
.align 8
str_const_2:
  .string "========================================"
.align 8
str_const_3:
  .string ""
.align 8
str_const_4:
  .string "Test 1: Basic Import and Variable Access"
.align 8
str_const_5:
  .string "----------------------------------------"
.align 8
str_const_6:
  .string "✓ Module imported successfully"
.align 8
str_const_7:
  .string "✓ Module variable access: "
.align 8
str_const_8:
  .string "✓ Module number access: "
.align 8
str_const_9:
  .string "Hello from basic module"
.align 8
str_const_10:
  .string "Module variable should be accessible"
.align 8
str_const_11:
  .string "Module number should be accessible"
.align 8
str_const_12:
  .string ""
.align 8
str_const_13:
  .string "Test 2: Simple Function Calls"
.align 8
str_const_14:
  .string "------------------------------"
.align 8
str_const_15:
  .string "✓ Simple function call successful"
.align 8
str_const_16:
  .string "Module function call should work"
.align 8
str_const_17:
  .string ""
.align 8
str_const_18:
  .string "Test 3: Module Aliasing"
.align 8
str_const_19:
  .string "-----------------------"
.align 8
str_const_20:
  .string "✓ Module imported with alias"
.align 8
str_const_21:
  .string "✓ Aliased variable access: PI = "
.align 8
str_const_22:
  .string "Module alias should work correctly"
.align 8
str_const_23:
  .string ""
.align 8
str_const_24:
  .string "Test 4: Multiple Module Imports"
.align 8
str_const_25:
  .string "-------------------------------"
.align 8
str_const_26:
  .string "✓ Multiple modules imported"
.align 8
str_const_27:
  .string "✓ First module still accessible: "
.align 8
str_const_28:
  .string "✓ Second module accessible: PI = "
.align 8
str_const_29:
  .string "✓ Third module accessible: "
.align 8
str_const_30:
  .string "Hello from basic module"
.align 8
str_const_31:
  .string "Multiple imports should preserve access"
.align 8
str_const_32:
  .string "Multiple imports should preserve access"
.align 8
str_const_33:
  .string "Hello"
.align 8
str_const_34:
  .string "Multiple imports should preserve access"
.align 8
str_const_35:
  .string ""
.align 8
str_const_36:
  .string "Test 5: Nested Directory Import"
.align 8
str_const_37:
  .string "-------------------------------"
.align 8
str_const_38:
  .string "✓ Nested module imported"
.align 8
str_const_39:
  .string "✓ Nested module variable: "
.align 8
str_const_40:
  .string "I'm deep in the directory structure"
.align 8
str_const_41:
  .string "Nested module import should work"
.align 8
str_const_42:
  .string ""
.align 8
str_const_43:
  .string "Test 6: Show Filter"
.align 8
str_const_44:
  .string "-------------------"
.align 8
str_const_45:
  .string "✓ Module imported with show filter"
.align 8
str_const_46:
  .string "✓ Shown variable accessible: "
.align 8
str_const_47:
  .string "Hello"
.align 8
str_const_48:
  .string "Show filter should work"
.align 8
str_const_49:
  .string ""
.align 8
str_const_50:
  .string "Test 7: Hide Filter"
.align 8
str_const_51:
  .string "-------------------"
.align 8
str_const_52:
  .string "✓ Module imported with hide filter"
.align 8
str_const_53:
  .string "✓ Non-hidden variable accessible: "
.align 8
str_const_54:
  .string "Hello"
.align 8
str_const_55:
  .string "Hide filter should work"
.align 8
str_const_56:
  .string ""
.align 8
str_const_57:
  .string "Test Suite Complete!"
.align 8
str_const_58:
  .string "Greetings from basic module!"
.align 8
str_const_59:
  .string "Called from deep module"
.align 8
str_const_60:
  .string ", "
.align 8
str_const_61:
  .string "!"
.align 8
str_const_62:
  .string ", "
.align 8
str_const_63:
  .string "!"
.align 8
str_const_64:
  .string ""
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
  sub rsp, 1736
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
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  addq $16, rax
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  mov rax, [rax]
  movq rax, [rbp + -184]
  movq [rbp + -184], rcx
  call lm_print_str
  movq [rel str_const_4], rcx
  call lm_box_string
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
  movq [rel str_const_5], rcx
  call lm_box_string
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
  call tests.modules.basic_module.__init__
  movq [rel str_const_6], rcx
  call lm_box_string
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
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq $0, rcx
  call lm_to_string
  movq rax, [rbp + -296]
  movq [rbp + -288], rcx
  movq [rbp + -296], rdx
  call lm_str_concat
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
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq $0, rcx
  call lm_to_string
  movq rax, [rbp + -344]
  movq [rbp + -336], rcx
  movq [rbp + -344], rdx
  call lm_str_concat
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  addq $16, rax
  movq rax, [rbp + -360]
  movq [rbp + -360], rax
  movq rax, [rbp + -368]
  movq [rbp + -368], rax
  mov rax, [rax]
  movq rax, [rbp + -376]
  movq [rbp + -376], rcx
  call lm_print_str
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq $0, rax
  cmpq [rbp + -384], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -392], rcx
  movq [rbp + -400], rdx
  call lm_assert
  movq $0, rax
  cmpq $337, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -408]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -408], rcx
  movq [rbp + -416], rdx
  call lm_assert
  movq [rel str_const_12], rcx
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
  movq [rel str_const_13], rcx
  call lm_box_string
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
  movq [rel str_const_14], rcx
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
  call tests.modules.basic_module.greet
  movq [rel str_const_15], rcx
  call lm_box_string
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
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -552]
  movq $18, rcx
  movq [rbp + -552], rdx
  call lm_assert
  movq [rel str_const_17], rcx
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
  movq [rel str_const_18], rcx
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
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rbp + -624], rax
  addq $16, rax
  movq rax, [rbp + -632]
  movq [rbp + -632], rax
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  mov rax, [rax]
  movq rax, [rbp + -648]
  movq [rbp + -648], rcx
  call lm_print_str
  call tests.modules.math_module.__init__
  movq [rel str_const_20], rcx
  call lm_box_string
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
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -688]
  movq $0, rcx
  call lm_to_string
  movq rax, [rbp + -696]
  movq [rbp + -688], rcx
  movq [rbp + -696], rdx
  call lm_str_concat
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
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -736]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -744]
  movq [rbp + -736], rcx
  movq [rbp + -744], rdx
  call lm_assert
  movq [rel str_const_23], rcx
  call lm_box_string
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
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -784]
  movq [rbp + -784], rax
  addq $16, rax
  movq rax, [rbp + -792]
  movq [rbp + -792], rax
  movq rax, [rbp + -800]
  movq [rbp + -800], rax
  mov rax, [rax]
  movq rax, [rbp + -808]
  movq [rbp + -808], rcx
  call lm_print_str
  movq [rel str_const_25], rcx
  call lm_box_string
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
  call tests.modules.string_module.__init__
  movq [rel str_const_26], rcx
  call lm_box_string
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
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -880]
  movq $0, rcx
  call lm_to_string
  movq rax, [rbp + -888]
  movq [rbp + -880], rcx
  movq [rbp + -888], rdx
  call lm_str_concat
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
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -928]
  movq $0, rcx
  call lm_to_string
  movq rax, [rbp + -936]
  movq [rbp + -928], rcx
  movq [rbp + -936], rdx
  call lm_str_concat
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
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -976]
  movq $0, rcx
  call lm_to_string
  movq rax, [rbp + -984]
  movq [rbp + -976], rcx
  movq [rbp + -984], rdx
  call lm_str_concat
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
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -1024]
  movq $0, rax
  cmpq [rbp + -1024], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1032]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -1040]
  movq [rbp + -1032], rcx
  movq [rbp + -1040], rdx
  call lm_assert
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1048]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -1056]
  movq [rbp + -1048], rcx
  movq [rbp + -1056], rdx
  call lm_assert
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -1064]
  movq $0, rax
  cmpq [rbp + -1064], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1072]
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -1080]
  movq [rbp + -1072], rcx
  movq [rbp + -1080], rdx
  call lm_assert
  movq [rel str_const_35], rcx
  call lm_box_string
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
  movq [rel str_const_36], rcx
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
  movq [rel str_const_37], rcx
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
  call tests.modules.nested.deep_module.__init__
  movq [rel str_const_38], rcx
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
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -1216]
  movq $0, rcx
  call lm_to_string
  movq rax, [rbp + -1224]
  movq [rbp + -1216], rcx
  movq [rbp + -1224], rdx
  call lm_str_concat
  movq rax, [rbp + -1232]
  movq [rbp + -1232], rax
  addq $16, rax
  movq rax, [rbp + -1240]
  movq [rbp + -1240], rax
  movq rax, [rbp + -1248]
  movq [rbp + -1248], rax
  mov rax, [rax]
  movq rax, [rbp + -1256]
  movq [rbp + -1256], rcx
  call lm_print_str
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -1264]
  movq $0, rax
  cmpq [rbp + -1264], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1272]
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -1280]
  movq [rbp + -1272], rcx
  movq [rbp + -1280], rdx
  call lm_assert
  movq [rel str_const_42], rcx
  call lm_box_string
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
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -1320]
  movq [rbp + -1320], rax
  addq $16, rax
  movq rax, [rbp + -1328]
  movq [rbp + -1328], rax
  movq rax, [rbp + -1336]
  movq [rbp + -1336], rax
  mov rax, [rax]
  movq rax, [rbp + -1344]
  movq [rbp + -1344], rcx
  call lm_print_str
  movq [rel str_const_44], rcx
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
  call tests.modules.string_module.__init__
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -1384]
  movq [rbp + -1384], rax
  addq $16, rax
  movq rax, [rbp + -1392]
  movq [rbp + -1392], rax
  movq rax, [rbp + -1400]
  movq [rbp + -1400], rax
  mov rax, [rax]
  movq rax, [rbp + -1408]
  movq [rbp + -1408], rcx
  call lm_print_str
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -1416]
  movq $0, rcx
  call lm_to_string
  movq rax, [rbp + -1424]
  movq [rbp + -1416], rcx
  movq [rbp + -1424], rdx
  call lm_str_concat
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
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -1464]
  movq $0, rax
  cmpq [rbp + -1464], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1472]
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -1480]
  movq [rbp + -1472], rcx
  movq [rbp + -1480], rdx
  call lm_assert
  movq [rel str_const_49], rcx
  call lm_box_string
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
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -1520]
  movq [rbp + -1520], rax
  addq $16, rax
  movq rax, [rbp + -1528]
  movq [rbp + -1528], rax
  movq rax, [rbp + -1536]
  movq [rbp + -1536], rax
  mov rax, [rax]
  movq rax, [rbp + -1544]
  movq [rbp + -1544], rcx
  call lm_print_str
  movq [rel str_const_51], rcx
  call lm_box_string
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
  call tests.modules.string_module.__init__
  movq [rel str_const_52], rcx
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
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -1616]
  movq $0, rcx
  call lm_to_string
  movq rax, [rbp + -1624]
  movq [rbp + -1616], rcx
  movq [rbp + -1624], rdx
  call lm_str_concat
  movq rax, [rbp + -1632]
  movq [rbp + -1632], rax
  addq $16, rax
  movq rax, [rbp + -1640]
  movq [rbp + -1640], rax
  movq rax, [rbp + -1648]
  movq [rbp + -1648], rax
  mov rax, [rax]
  movq rax, [rbp + -1656]
  movq [rbp + -1656], rcx
  call lm_print_str
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -1664]
  movq $0, rax
  cmpq [rbp + -1664], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1672]
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -1680]
  movq [rbp + -1672], rcx
  movq [rbp + -1680], rdx
  call lm_assert
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -1688]
  movq [rbp + -1688], rax
  addq $16, rax
  movq rax, [rbp + -1696]
  movq [rbp + -1696], rax
  movq rax, [rbp + -1704]
  movq [rbp + -1704], rax
  mov rax, [rax]
  movq rax, [rbp + -1712]
  movq [rbp + -1712], rcx
  call lm_print_str
  movq [rel str_const_57], rcx
  call lm_box_string
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

.globl tests.modules.basic_module.__init__
tests.modules.basic_module.__init__:
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
tests.modules.basic_module.__init___entry:
  movq $0, rax
  jmp tests.modules.basic_module.__init___epilogue
tests.modules.basic_module.__init___epilogue:
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
.Lfunc_end_tests.modules.basic_module.__init__:

.globl tests.modules.basic_module.greet
tests.modules.basic_module.greet:
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
tests.modules.basic_module.greet_entry:
tests.modules.basic_module.greet_block_0:
  movq [rel str_const_58], rcx
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
  movq $0, rax
  jmp tests.modules.basic_module.greet_epilogue
tests.modules.basic_module.greet_epilogue:
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
.Lfunc_end_tests.modules.basic_module.greet:

.globl tests.modules.nested.deep_module.deep_function
tests.modules.nested.deep_module.deep_function:
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
tests.modules.nested.deep_module.deep_function_entry:
tests.modules.nested.deep_module.deep_function_block_0:
  movq [rel str_const_59], rcx
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
  movq $0, rax
  jmp tests.modules.nested.deep_module.deep_function_epilogue
tests.modules.nested.deep_module.deep_function_epilogue:
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
.Lfunc_end_tests.modules.nested.deep_module.deep_function:

.globl tests.modules.math_module.square
tests.modules.math_module.square:
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
tests.modules.math_module.square_entry:
tests.modules.math_module.square_block_0:
  movq [rbp + -64], rax
  imulq [rbp + -64], rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp tests.modules.math_module.square_epilogue
tests.modules.math_module.square_epilogue:
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
.Lfunc_end_tests.modules.math_module.square:

.globl tests.modules.string_module.say_hello
tests.modules.string_module.say_hello:
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
tests.modules.string_module.say_hello_entry:
tests.modules.string_module.say_hello_block_0:
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $0, rcx
  movq [rbp + -72], rdx
  call lm_str_concat
  movq rax, [rbp + -80]
  movq [rbp + -64], rcx
  call lm_to_string
  movq rax, [rbp + -88]
  movq [rbp + -80], rcx
  movq [rbp + -88], rdx
  call lm_str_concat
  movq rax, [rbp + -96]
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_str_concat
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp tests.modules.string_module.say_hello_epilogue
tests.modules.string_module.say_hello_epilogue:
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
.Lfunc_end_tests.modules.string_module.say_hello:

.globl tests.modules.string_module.say_goodbye
tests.modules.string_module.say_goodbye:
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
tests.modules.string_module.say_goodbye_entry:
tests.modules.string_module.say_goodbye_block_0:
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $0, rcx
  movq [rbp + -72], rdx
  call lm_str_concat
  movq rax, [rbp + -80]
  movq [rbp + -64], rcx
  call lm_to_string
  movq rax, [rbp + -88]
  movq [rbp + -80], rcx
  movq [rbp + -88], rdx
  call lm_str_concat
  movq rax, [rbp + -96]
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_str_concat
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp tests.modules.string_module.say_goodbye_epilogue
tests.modules.string_module.say_goodbye_epilogue:
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
.Lfunc_end_tests.modules.string_module.say_goodbye:

.globl tests.modules.basic_module.add
tests.modules.basic_module.add:
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
tests.modules.basic_module.add_entry:
tests.modules.basic_module.add_block_0:
  movq [rbp + -64], rax
  addq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp tests.modules.basic_module.add_epilogue
tests.modules.basic_module.add_epilogue:
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
.Lfunc_end_tests.modules.basic_module.add:

.globl tests.modules.string_module.__init__
tests.modules.string_module.__init__:
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
tests.modules.string_module.__init___entry:
  movq $0, rax
  jmp tests.modules.string_module.__init___epilogue
tests.modules.string_module.__init___epilogue:
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
.Lfunc_end_tests.modules.string_module.__init__:

.globl tests.modules.math_module.add
tests.modules.math_module.add:
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
tests.modules.math_module.add_entry:
tests.modules.math_module.add_block_0:
  movq [rbp + -64], rax
  addq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp tests.modules.math_module.add_epilogue
tests.modules.math_module.add_epilogue:
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
.Lfunc_end_tests.modules.math_module.add:

.globl tests.modules.basic_module.getModuleVar
tests.modules.basic_module.getModuleVar:
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
tests.modules.basic_module.getModuleVar_entry:
tests.modules.basic_module.getModuleVar_block_0:
  movq $0, rax
  jmp tests.modules.basic_module.getModuleVar_epilogue
tests.modules.basic_module.getModuleVar_epilogue:
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
.Lfunc_end_tests.modules.basic_module.getModuleVar:

.globl tests.modules.nested.deep_module.__init__
tests.modules.nested.deep_module.__init__:
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
tests.modules.nested.deep_module.__init___entry:
  movq $0, rax
  jmp tests.modules.nested.deep_module.__init___epilogue
tests.modules.nested.deep_module.__init___epilogue:
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
.Lfunc_end_tests.modules.nested.deep_module.__init__:

.globl tests.modules.math_module.multiply
tests.modules.math_module.multiply:
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
tests.modules.math_module.multiply_entry:
tests.modules.math_module.multiply_block_0:
  movq [rbp + -64], rax
  imulq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp tests.modules.math_module.multiply_epilogue
tests.modules.math_module.multiply_epilogue:
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
.Lfunc_end_tests.modules.math_module.multiply:

.globl tests.modules.math_module.__init__
tests.modules.math_module.__init__:
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
tests.modules.math_module.__init___entry:
  movq $0, rax
  jmp tests.modules.math_module.__init___epilogue
tests.modules.math_module.__init___epilogue:
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
.Lfunc_end_tests.modules.math_module.__init__:

.globl tests.modules.math_module.cube
tests.modules.math_module.cube:
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
tests.modules.math_module.cube_entry:
tests.modules.math_module.cube_block_0:
  movq [rbp + -64], rax
  imulq [rbp + -64], rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  imulq [rbp + -64], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp tests.modules.math_module.cube_epilogue
tests.modules.math_module.cube_epilogue:
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
.Lfunc_end_tests.modules.math_module.cube:

.globl tests.modules.math_module.factorial
tests.modules.math_module.factorial:
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
tests.modules.math_module.factorial_entry:
tests.modules.math_module.factorial_block_0:
  movq [rbp + -64], rax
  cmpq $9, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne tests.modules.math_module.factorial_block_3
  jmp tests.modules.math_module.factorial_block_5
tests.modules.math_module.factorial_block_3:
  jmp tests.modules.math_module.factorial_block_3
  movq $9, rax
  jmp tests.modules.math_module.factorial_epilogue
tests.modules.math_module.factorial_block_5:
  movq [rbp + -64], rax
  subq $9, rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rcx
  call tests.modules.math_module.factorial
  movq [rbp + -64], rax
  imulq $r7, rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp tests.modules.math_module.factorial_epilogue
tests.modules.math_module.factorial_epilogue:
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
.Lfunc_end_tests.modules.math_module.factorial:

.globl tests.modules.math_module.subtract
tests.modules.math_module.subtract:
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
tests.modules.math_module.subtract_entry:
tests.modules.math_module.subtract_block_0:
  movq [rbp + -64], rax
  subq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp tests.modules.math_module.subtract_epilogue
tests.modules.math_module.subtract_epilogue:
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
.Lfunc_end_tests.modules.math_module.subtract:

.globl tests.modules.math_module.is_odd
tests.modules.math_module.is_odd:
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
tests.modules.math_module.is_odd_entry:
tests.modules.math_module.is_odd_block_0:
  movq [rbp + -64], rcx
  call tests.modules.math_module.is_even
  movq $r1, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp tests.modules.math_module.is_odd_epilogue
tests.modules.math_module.is_odd_epilogue:
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
.Lfunc_end_tests.modules.math_module.is_odd:

.globl tests.modules.math_module.is_prime
tests.modules.math_module.is_prime:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 120
  mov [rbp + -64], rcx
tests.modules.math_module.is_prime_entry:
tests.modules.math_module.is_prime_block_0:
  movq [rbp + -64], rax
  cmpq $9, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne tests.modules.math_module.is_prime_block_3
  jmp tests.modules.math_module.is_prime_block_5
tests.modules.math_module.is_prime_block_3:
  jmp tests.modules.math_module.is_prime_block_3
  movq $10, rax
  jmp tests.modules.math_module.is_prime_epilogue
tests.modules.math_module.is_prime_block_5:
  movq [rbp + -64], rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne tests.modules.math_module.is_prime_block_8
  jmp tests.modules.math_module.is_prime_block_10
tests.modules.math_module.is_prime_block_8:
  jmp tests.modules.math_module.is_prime_block_8
  movq $18, rax
  jmp tests.modules.math_module.is_prime_epilogue
tests.modules.math_module.is_prime_block_10:
  movq [rbp + -64], rcx
  call tests.modules.math_module.is_even
  movq $r9, rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne tests.modules.math_module.is_prime_block_14
  jmp tests.modules.math_module.is_prime_block_16
tests.modules.math_module.is_prime_block_14:
  jmp tests.modules.math_module.is_prime_block_14
  movq $10, rax
  jmp tests.modules.math_module.is_prime_epilogue
tests.modules.math_module.is_prime_block_16:
  jmp tests.modules.math_module.is_prime_block_18
tests.modules.math_module.is_prime_block_18:
  movq $25, rax
  imulq $25, rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  cmpq [rbp + -64], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne tests.modules.math_module.is_prime_block_21
  jmp tests.modules.math_module.is_prime_block_30
tests.modules.math_module.is_prime_block_21:
  jmp tests.modules.math_module.is_prime_block_21
  movq [rbp + -64], rax
  cqto
  movq $25, rcx
  idivq rcx
  movq rdx, [rbp + -112]
  movq [rbp + -112], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne tests.modules.math_module.is_prime_block_25
  jmp tests.modules.math_module.is_prime_block_27
tests.modules.math_module.is_prime_block_25:
  jmp tests.modules.math_module.is_prime_block_25
  movq $10, rax
  jmp tests.modules.math_module.is_prime_epilogue
tests.modules.math_module.is_prime_block_27:
  movq $25, rax
  addq $17, rax
  movq rax, [rbp + -128]
  jmp tests.modules.math_module.is_prime_block_18
tests.modules.math_module.is_prime_block_30:
  movq $18, rax
  jmp tests.modules.math_module.is_prime_epilogue
tests.modules.math_module.is_prime_epilogue:
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
.Lfunc_end_tests.modules.math_module.is_prime:

.globl tests.modules.math_module.is_even
tests.modules.math_module.is_even:
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
tests.modules.math_module.is_even_entry:
tests.modules.math_module.is_even_block_0:
  movq [rbp + -64], rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rdx, [rbp + -72]
  movq [rbp + -72], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp tests.modules.math_module.is_even_epilogue
tests.modules.math_module.is_even_epilogue:
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
.Lfunc_end_tests.modules.math_module.is_even:

.globl tests.modules.string_module.repeat_string
tests.modules.string_module.repeat_string:
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
  mov [rbp + -72], rdx
tests.modules.string_module.repeat_string_entry:
tests.modules.string_module.repeat_string_block_0:
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  jmp tests.modules.string_module.repeat_string_block_4
tests.modules.string_module.repeat_string_block_4:
  movq $9, rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne tests.modules.string_module.repeat_string_block_6
  jmp tests.modules.string_module.repeat_string_block_14
tests.modules.string_module.repeat_string_block_6:
  jmp tests.modules.string_module.repeat_string_block_6
  movq [rbp + -64], rcx
  call lm_to_string
  movq rax, [rbp + -96]
  movq [rbp + -80], rcx
  movq [rbp + -96], rdx
  call lm_str_concat
  movq rax, [rbp + -104]
  jmp tests.modules.string_module.repeat_string_block_10
tests.modules.string_module.repeat_string_block_10:
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp tests.modules.string_module.repeat_string_block_4
tests.modules.string_module.repeat_string_block_14:
  movq [rbp + -104], rax
  jmp tests.modules.string_module.repeat_string_epilogue
tests.modules.string_module.repeat_string_epilogue:
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
.Lfunc_end_tests.modules.string_module.repeat_string:

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

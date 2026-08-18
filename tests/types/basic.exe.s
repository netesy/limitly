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
  .string "=== Basic Type Tests ==="
.align 8
str_const_1:
  .string "
--- Test 1: Basic Type Aliases ---"
.align 8
str_const_2:
  .string "Alice"
.align 8
str_const_3:
  .string "User ID: %s"
.align 8
str_const_4:
  .string "User Name: %s"
.align 8
str_const_5:
  .string "User Age: %s"
.align 8
str_const_6:
  .string "User Score: %s"
.align 8
str_const_7:
  .string "Is Active: %s"
.align 8
str_const_8:
  .string "Type alias should work for uint"
.align 8
str_const_9:
  .string "Alice"
.align 8
str_const_10:
  .string "Type alias should work for str"
.align 8
str_const_11:
  .string "Type alias should work for int"
.align 8
str_const_12:
  .string "Type alias should work for float"
.align 8
str_const_13:
  .string "Type alias should work for bool"
.align 8
str_const_14:
  .string "
--- Test 2: Primitive Type Aliases ---"
.align 8
str_const_15:
  .string "hello"
.align 8
str_const_16:
  .string "Int: %s"
.align 8
str_const_17:
  .string "UInt: %s"
.align 8
str_const_18:
  .string "String: %s"
.align 8
str_const_19:
  .string "Bool: %s"
.align 8
str_const_20:
  .string "Float: %s"
.align 8
str_const_21:
  .string "Primitive type alias should work for int"
.align 8
str_const_22:
  .string "Primitive type alias should work for uint"
.align 8
str_const_23:
  .string "hello"
.align 8
str_const_24:
  .string "Primitive type alias should work for str"
.align 8
str_const_25:
  .string "Primitive type alias should work for bool"
.align 8
str_const_26:
  .string "Primitive type alias should work for float"
.align 8
str_const_27:
  .string "
--- Test 3: Type Alias Compatibility ---"
.align 8
str_const_28:
  .string "User ID: %s"
.align 8
str_const_29:
  .string "Product ID: %s"
.align 8
str_const_30:
  .string "Type alias compatibility should work"
.align 8
str_const_31:
  .string "Type alias compatibility should work"
.align 8
str_const_32:
  .string "
--- Test 4: Type Aliases in Functions ---"
.align 8
str_const_33:
  .string "Distance: %s"
.align 8
str_const_34:
  .string "Time: %s"
.align 8
str_const_35:
  .string "Speed: %s"
.align 8
str_const_36:
  .string "Function with type aliases should work: 100.0/2.0 = 50.0"
.align 8
str_const_37:
  .string "
--- Test 5: Nested Type Usage ---"
.align 8
str_const_38:
  .string "John"
.align 8
str_const_39:
  .string "Doe"
.align 8
str_const_40:
  .string "First Name: %s"
.align 8
str_const_41:
  .string "Last Name: %s"
.align 8
str_const_42:
  .string "Full Name: %s"
.align 8
str_const_43:
  .string "John Doe"
.align 8
str_const_44:
  .string "Function with type aliases should work correctly"
.align 8
str_const_45:
  .string "
--- Test 6: Type Alias Scopes ---"
.align 8
str_const_46:
  .string "local"
.align 8
str_const_47:
  .string "Global in local scope: %s"
.align 8
str_const_48:
  .string "Local variable: %s"
.align 8
str_const_49:
  .string "Global type alias should work in local scope"
.align 8
str_const_50:
  .string "local"
.align 8
str_const_51:
  .string "Local variable should work correctly"
.align 8
str_const_52:
  .string "Another global: %s"
.align 8
str_const_53:
  .string "Global type alias should work outside local scope"
.align 8
str_const_54:
  .string "
=== Basic Type Tests Complete ==="
.align 8
str_const_55:
  .string " "
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
  sub rsp, 1480
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
  movq $98761, rdx
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
  movq $201, rdx
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
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -296], rcx
  movq $18, rdx
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
  movq $98761, rax
  cmpq $98761, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -336]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -336], rcx
  movq [rbp + -344], rdx
  call lm_assert
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -128], rax
  cmpq [rbp + -352], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -360], rcx
  movq [rbp + -368], rdx
  call lm_assert
  movq $201, rax
  cmpq $201, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -376]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -376], rcx
  movq [rbp + -384], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -392], rcx
  movq [rbp + -400], rdx
  call lm_assert
  movq $18, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -408]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -408], rcx
  movq [rbp + -416], rdx
  call lm_assert
  movq [rel str_const_14], rcx
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
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq [rbp + -464], rcx
  movq $337, rdx
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
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -504], rcx
  movq $801, rdx
  call lm_rt_str_format
  movq rax, [rbp + -512]
  movq [rbp + -512], rax
  addq $16, rax
  movq rax, [rbp + -520]
  movq [rbp + -520], rax
  movq rax, [rbp + -528]
  movq [rbp + -528], rax
  mov rax, [rax]
  movq rax, [rbp + -536]
  movq [rbp + -536], rcx
  call lm_print_str
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -544]
  movq [rbp + -544], rcx
  movq [rbp + -456], rdx
  call lm_rt_str_format
  movq rax, [rbp + -552]
  movq [rbp + -552], rax
  addq $16, rax
  movq rax, [rbp + -560]
  movq [rbp + -560], rax
  movq rax, [rbp + -568]
  movq [rbp + -568], rax
  mov rax, [rax]
  movq rax, [rbp + -576]
  movq [rbp + -576], rcx
  call lm_print_str
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -584]
  movq [rbp + -584], rcx
  movq $18, rdx
  call lm_rt_str_format
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
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rbp + -624], rcx
  movq $2, rdx
  call lm_rt_str_format
  movq rax, [rbp + -632]
  movq [rbp + -632], rax
  addq $16, rax
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  movq rax, [rbp + -648]
  movq [rbp + -648], rax
  mov rax, [rax]
  movq rax, [rbp + -656]
  movq [rbp + -656], rcx
  call lm_print_str
  movq $337, rax
  cmpq $337, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -664]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -672]
  movq [rbp + -664], rcx
  movq [rbp + -672], rdx
  call lm_assert
  movq $801, rax
  cmpq $801, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -680]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -688]
  movq [rbp + -680], rcx
  movq [rbp + -688], rdx
  call lm_assert
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -696]
  movq [rbp + -456], rax
  cmpq [rbp + -696], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -704]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -712]
  movq [rbp + -704], rcx
  movq [rbp + -712], rdx
  call lm_assert
  movq $18, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -720]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -728]
  movq [rbp + -720], rcx
  movq [rbp + -728], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -736]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -744]
  movq [rbp + -736], rcx
  movq [rbp + -744], rdx
  call lm_assert
  movq [rel str_const_27], rcx
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
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -784]
  movq [rbp + -784], rcx
  movq $8009, rdx
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
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -824]
  movq [rbp + -824], rcx
  movq $16017, rdx
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
  movq $8009, rax
  cmpq $8009, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -864]
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -872]
  movq [rbp + -864], rcx
  movq [rbp + -872], rdx
  call lm_assert
  movq $16017, rax
  cmpq $16017, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -880]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -888]
  movq [rbp + -880], rcx
  movq [rbp + -888], rdx
  call lm_assert
  movq [rel str_const_32], rcx
  call lm_box_string
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
  movq $2, rcx
  movq $2, rdx
  call calculateSpeed
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -928]
  movq [rbp + -928], rcx
  movq $2, rdx
  call lm_rt_str_format
  movq rax, [rbp + -936]
  movq [rbp + -936], rax
  addq $16, rax
  movq rax, [rbp + -944]
  movq [rbp + -944], rax
  movq rax, [rbp + -952]
  movq [rbp + -952], rax
  mov rax, [rax]
  movq rax, [rbp + -960]
  movq [rbp + -960], rcx
  call lm_print_str
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -968]
  movq [rbp + -968], rcx
  movq $2, rdx
  call lm_rt_str_format
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
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -1008]
  movq [rbp + -1008], rcx
  movq $r110, rdx
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
  movq $r110, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1048]
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -1056]
  movq [rbp + -1048], rcx
  movq [rbp + -1056], rdx
  call lm_assert
  movq [rel str_const_37], rcx
  call lm_box_string
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
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -1096]
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -1104]
  movq [rbp + -1096], rcx
  movq [rbp + -1104], rdx
  call createFullName
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -1112]
  movq [rbp + -1112], rcx
  movq [rbp + -1096], rdx
  call lm_rt_str_format
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
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -1152]
  movq [rbp + -1152], rcx
  movq [rbp + -1104], rdx
  call lm_rt_str_format
  movq rax, [rbp + -1160]
  movq [rbp + -1160], rax
  addq $16, rax
  movq rax, [rbp + -1168]
  movq [rbp + -1168], rax
  movq rax, [rbp + -1176]
  movq [rbp + -1176], rax
  mov rax, [rax]
  movq rax, [rbp + -1184]
  movq [rbp + -1184], rcx
  call lm_print_str
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -1192]
  movq [rbp + -1192], rcx
  movq $r129, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1200]
  movq [rbp + -1200], rax
  addq $16, rax
  movq rax, [rbp + -1208]
  movq [rbp + -1208], rax
  movq rax, [rbp + -1216]
  movq [rbp + -1216], rax
  mov rax, [rax]
  movq rax, [rbp + -1224]
  movq [rbp + -1224], rcx
  call lm_print_str
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -1232]
  movq $r129, rax
  cmpq [rbp + -1232], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1240]
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -1248]
  movq [rbp + -1240], rcx
  movq [rbp + -1248], rdx
  call lm_assert
  movq [rel str_const_45], rcx
  call lm_box_string
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
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -1288]
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -1296]
  movq [rbp + -1296], rcx
  movq $7993, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1304]
  movq [rbp + -1304], rax
  addq $16, rax
  movq rax, [rbp + -1312]
  movq [rbp + -1312], rax
  movq rax, [rbp + -1320]
  movq [rbp + -1320], rax
  mov rax, [rax]
  movq rax, [rbp + -1328]
  movq [rbp + -1328], rcx
  call lm_print_str
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -1336]
  movq [rbp + -1336], rcx
  movq [rbp + -1288], rdx
  call lm_rt_str_format
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
  movq $7993, rax
  cmpq $7993, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1376]
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -1384]
  movq [rbp + -1376], rcx
  movq [rbp + -1384], rdx
  call lm_assert
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -1392]
  movq [rbp + -1288], rax
  cmpq [rbp + -1392], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1400]
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -1408]
  movq [rbp + -1400], rcx
  movq [rbp + -1408], rdx
  call lm_assert
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -1416]
  movq [rbp + -1416], rcx
  movq $7105, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1424]
  movq [rbp + -1424], rax
  addq $16, rax
  movq rax, [rbp + -1432]
  movq [rbp + -1432], rax
  movq rax, [rbp + -1440]
  movq [rbp + -1440], rax
  mov rax, [rax]
  movq rax, [rbp + -1448]
  movq [rbp + -1448], rcx
  call lm_print_str
  movq $7105, rax
  cmpq $7105, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1456]
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -1464]
  movq [rbp + -1456], rcx
  movq [rbp + -1464], rdx
  call lm_assert
  movq [rel str_const_54], rcx
  call lm_box_string
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

.globl createFullName
createFullName:
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
createFullName_entry:
createFullName_block_0:
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -64], rcx
  movq [rbp + -80], rdx
  call lm_str_concat
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  movq [rbp + -72], rdx
  call lm_str_concat
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp createFullName_epilogue
createFullName_epilogue:
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
.Lfunc_end_createFullName:

.globl calculateSpeed
calculateSpeed:
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
calculateSpeed_entry:
calculateSpeed_block_0:
  movq [rbp + -72], rax
  cmpq $2, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne calculateSpeed_block_3
  jmp calculateSpeed_block_5
calculateSpeed_block_3:
  jmp calculateSpeed_block_3
  movq [rbp + -64], rax
  cqto
  movq [rbp + -72], rcx
  idivq rcx
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp calculateSpeed_epilogue
calculateSpeed_block_5:
  movq $2, rax
  jmp calculateSpeed_epilogue
calculateSpeed_epilogue:
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
.Lfunc_end_calculateSpeed:

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

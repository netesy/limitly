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
  .string "=== String Interpolation Tests ==="
.align 8
str_const_1:
  .string "World"
.align 8
str_const_2:
  .string "World"
.align 8
str_const_3:
  .string "Variable name should be 'World'"
.align 8
str_const_4:
  .string "Variable age should be 25"
.align 8
str_const_5:
  .string "Variable pi should be 3.14159"
.align 8
str_const_6:
  .string "Hello, %s!"
.align 8
str_const_7:
  .string "Age: %s"
.align 8
str_const_8:
  .string "Pi: %s"
.align 8
str_const_9:
  .string "Hello, World!"
.align 8
str_const_10:
  .string "Basic interpolation should work"
.align 8
str_const_11:
  .string "Age: 25"
.align 8
str_const_12:
  .string "Integer interpolation should work"
.align 8
str_const_13:
  .string "Pi: 3.14159"
.align 8
str_const_14:
  .string "Float interpolation should work"
.align 8
str_const_15:
  .string "Next year: %s"
.align 8
str_const_16:
  .string "Next year: 26"
.align 8
str_const_17:
  .string "Expression interpolation should work"
.align 8
str_const_18:
  .string "Area of circle: %s"
.align 8
str_const_19:
  .string "Area of circle: 12.5664"
.align 8
str_const_20:
  .string "Math expression interpolation should work"
.align 8
str_const_21:
  .string "Name: %s, Age: %s"
.align 8
str_const_22:
  .string "%s is %s years old"
.align 8
str_const_23:
  .string "Name: World, Age: 25"
.align 8
str_const_24:
  .string "Multiple interpolation should work"
.align 8
str_const_25:
  .string "World is 25 years old"
.align 8
str_const_26:
  .string "Multiple interpolation should work"
.align 8
str_const_27:
  .string "%s says hello"
.align 8
str_const_28:
  .string "%s is the age"
.align 8
str_const_29:
  .string "World says hello"
.align 8
str_const_30:
  .string "Start interpolation should work"
.align 8
str_const_31:
  .string "25 is the age"
.align 8
str_const_32:
  .string "Start interpolation should work"
.align 8
str_const_33:
  .string "Math: %s + %s = %s"
.align 8
str_const_34:
  .string "Comparison: %s > %s is %s"
.align 8
str_const_35:
  .string "Math: 10 + 5 = 15"
.align 8
str_const_36:
  .string "Complex math interpolation should work"
.align 8
str_const_37:
  .string "Comparison: 10 > 5 is true"
.align 8
str_const_38:
  .string "Comparison interpolation should work"
.align 8
str_const_39:
  .string "Complex: %s"
.align 8
str_const_40:
  .string "Complex: 29"
.align 8
str_const_41:
  .string "Nested expression interpolation should work"
.align 8
str_const_42:
  .string "Hello, %s! You are %s."
.align 8
str_const_43:
  .string "Hello, World! You are 25."
.align 8
str_const_44:
  .string "String with interpolation should work"
.align 8
str_const_45:
  .string "=== String Interpolation Tests Complete ==="
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
  sub rsp, 1128
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
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rax
  cmpq [rbp + -104], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq $201, rax
  cmpq $201, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rcx
  movq [rbp + -96], rdx
  call lm_rt_str_format
  movq rax, [rbp + -168]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -176], rcx
  movq $201, rdx
  call lm_rt_str_format
  movq rax, [rbp + -184]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -192], rcx
  movq $2, rdx
  call lm_rt_str_format
  movq rax, [rbp + -200]
  movq [rbp + -168], rax
  addq $16, rax
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  mov rax, [rax]
  movq rax, [rbp + -224]
  movq [rbp + -224], rcx
  call lm_print_str
  movq [rbp + -184], rax
  addq $16, rax
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  mov rax, [rax]
  movq rax, [rbp + -248]
  movq [rbp + -248], rcx
  call lm_print_str
  movq [rbp + -200], rax
  addq $16, rax
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  mov rax, [rax]
  movq rax, [rbp + -272]
  movq [rbp + -272], rcx
  call lm_print_str
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -168], rax
  cmpq [rbp + -280], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -288]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -288], rcx
  movq [rbp + -296], rdx
  call lm_assert
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -184], rax
  cmpq [rbp + -304], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -312]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -312], rcx
  movq [rbp + -320], rdx
  call lm_assert
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -200], rax
  cmpq [rbp + -328], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -336]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -336], rcx
  movq [rbp + -344], rdx
  call lm_assert
  movq $201, rax
  addq $9, rax
  movq rax, [rbp + -352]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -360], rcx
  movq [rbp + -352], rdx
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
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -368], rax
  cmpq [rbp + -400], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -408]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -408], rcx
  movq [rbp + -416], rdx
  call lm_assert
  movq $2, rax
  imulq $17, rax
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  imulq $17, rax
  movq rax, [rbp + -432]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rbp + -440], rcx
  movq [rbp + -432], rdx
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
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq [rbp + -448], rax
  cmpq [rbp + -480], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -488]
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -488], rcx
  movq [rbp + -496], rdx
  call lm_assert
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -504], rcx
  movq [rbp + -96], rdx
  call lm_rt_str_format
  movq rax, [rbp + -512]
  movq [rbp + -512], rcx
  movq $201, rdx
  call lm_rt_str_format
  movq rax, [rbp + -520]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -528], rcx
  movq [rbp + -96], rdx
  call lm_rt_str_format
  movq rax, [rbp + -536]
  movq [rbp + -536], rcx
  movq $201, rdx
  call lm_rt_str_format
  movq rax, [rbp + -544]
  movq [rbp + -520], rax
  addq $16, rax
  movq rax, [rbp + -552]
  movq [rbp + -552], rax
  movq rax, [rbp + -560]
  movq [rbp + -560], rax
  mov rax, [rax]
  movq rax, [rbp + -568]
  movq [rbp + -568], rcx
  call lm_print_str
  movq [rbp + -544], rax
  addq $16, rax
  movq rax, [rbp + -576]
  movq [rbp + -576], rax
  movq rax, [rbp + -584]
  movq [rbp + -584], rax
  mov rax, [rax]
  movq rax, [rbp + -592]
  movq [rbp + -592], rcx
  call lm_print_str
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -600]
  movq [rbp + -520], rax
  cmpq [rbp + -600], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -608]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -608], rcx
  movq [rbp + -616], rdx
  call lm_assert
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rbp + -544], rax
  cmpq [rbp + -624], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -632]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -632], rcx
  movq [rbp + -640], rdx
  call lm_assert
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -648]
  movq [rbp + -648], rcx
  movq [rbp + -96], rdx
  call lm_rt_str_format
  movq rax, [rbp + -656]
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -664]
  movq [rbp + -664], rcx
  movq $201, rdx
  call lm_rt_str_format
  movq rax, [rbp + -672]
  movq [rbp + -656], rax
  addq $16, rax
  movq rax, [rbp + -680]
  movq [rbp + -680], rax
  movq rax, [rbp + -688]
  movq [rbp + -688], rax
  mov rax, [rax]
  movq rax, [rbp + -696]
  movq [rbp + -696], rcx
  call lm_print_str
  movq [rbp + -672], rax
  addq $16, rax
  movq rax, [rbp + -704]
  movq [rbp + -704], rax
  movq rax, [rbp + -712]
  movq [rbp + -712], rax
  mov rax, [rax]
  movq rax, [rbp + -720]
  movq [rbp + -720], rcx
  call lm_print_str
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -728]
  movq [rbp + -656], rax
  cmpq [rbp + -728], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -736]
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -744]
  movq [rbp + -736], rcx
  movq [rbp + -744], rdx
  call lm_assert
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -752]
  movq [rbp + -672], rax
  cmpq [rbp + -752], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -760]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -768]
  movq [rbp + -760], rcx
  movq [rbp + -768], rdx
  call lm_assert
  movq $81, rax
  addq $41, rax
  movq rax, [rbp + -776]
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -784]
  movq [rbp + -784], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -792]
  movq [rbp + -792], rcx
  movq $41, rdx
  call lm_rt_str_format
  movq rax, [rbp + -800]
  movq [rbp + -800], rcx
  movq [rbp + -776], rdx
  call lm_rt_str_format
  movq rax, [rbp + -808]
  movq $81, rax
  cmpq $41, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -816]
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -824]
  movq [rbp + -824], rcx
  movq $81, rdx
  call lm_rt_str_format
  movq rax, [rbp + -832]
  movq [rbp + -832], rcx
  movq $41, rdx
  call lm_rt_str_format
  movq rax, [rbp + -840]
  movq [rbp + -840], rcx
  movq [rbp + -816], rdx
  call lm_rt_str_format
  movq rax, [rbp + -848]
  movq [rbp + -808], rax
  addq $16, rax
  movq rax, [rbp + -856]
  movq [rbp + -856], rax
  movq rax, [rbp + -864]
  movq [rbp + -864], rax
  mov rax, [rax]
  movq rax, [rbp + -872]
  movq [rbp + -872], rcx
  call lm_print_str
  movq [rbp + -848], rax
  addq $16, rax
  movq rax, [rbp + -880]
  movq [rbp + -880], rax
  movq rax, [rbp + -888]
  movq [rbp + -888], rax
  mov rax, [rax]
  movq rax, [rbp + -896]
  movq [rbp + -896], rcx
  call lm_print_str
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -904]
  movq [rbp + -808], rax
  cmpq [rbp + -904], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -912]
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -920]
  movq [rbp + -912], rcx
  movq [rbp + -920], rdx
  call lm_assert
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -928]
  movq [rbp + -848], rax
  cmpq [rbp + -928], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -936]
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -944]
  movq [rbp + -936], rcx
  movq [rbp + -944], rdx
  call lm_assert
  movq $81, rax
  addq $41, rax
  movq rax, [rbp + -952]
  movq [rbp + -952], rax
  imulq $17, rax
  movq rax, [rbp + -960]
  movq [rbp + -960], rax
  subq $9, rax
  movq rax, [rbp + -968]
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -976]
  movq [rbp + -976], rcx
  movq [rbp + -968], rdx
  call lm_rt_str_format
  movq rax, [rbp + -984]
  movq [rbp + -984], rax
  addq $16, rax
  movq rax, [rbp + -992]
  movq [rbp + -992], rax
  movq rax, [rbp + -1000]
  movq [rbp + -1000], rax
  mov rax, [rax]
  movq rax, [rbp + -1008]
  movq [rbp + -1008], rcx
  call lm_print_str
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -1016]
  movq [rbp + -984], rax
  cmpq [rbp + -1016], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1024]
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -1032]
  movq [rbp + -1024], rcx
  movq [rbp + -1032], rdx
  call lm_assert
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -1040]
  movq [rbp + -1040], rcx
  movq [rbp + -96], rdx
  call lm_rt_str_format
  movq rax, [rbp + -1048]
  movq [rbp + -1048], rcx
  movq $201, rdx
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
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -1088]
  movq [rbp + -1056], rax
  cmpq [rbp + -1088], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1096]
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -1104]
  movq [rbp + -1096], rcx
  movq [rbp + -1104], rdx
  call lm_assert
  movq [rel str_const_45], rcx
  call lm_box_string
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

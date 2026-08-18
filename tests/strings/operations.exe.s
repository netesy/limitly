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
  .string "=== String Operations Tests ==="
.align 8
str_const_1:
  .string "Hello"
.align 8
str_const_2:
  .string "World"
.align 8
str_const_3:
  .string " "
.align 8
str_const_4:
  .string "Hello"
.align 8
str_const_5:
  .string "str1 should be 'Hello'"
.align 8
str_const_6:
  .string "World"
.align 8
str_const_7:
  .string "str2 should be 'World'"
.align 8
str_const_8:
  .string " "
.align 8
str_const_9:
  .string "space should be a single space"
.align 8
str_const_10:
  .string "Concatenation: %s + %s + %s = %s"
.align 8
str_const_11:
  .string "Hello World"
.align 8
str_const_12:
  .string "String concatenation should work"
.align 8
str_const_13:
  .string "String comparisons:"
.align 8
str_const_14:
  .string "%s == %s: %s"
.align 8
str_const_15:
  .string "%s != %s: %s"
.align 8
str_const_16:
  .string "'Hello' should not equal 'World'"
.align 8
str_const_17:
  .string "'Hello' should not equal 'World' (not equal)"
.align 8
str_const_18:
  .string "42"
.align 8
str_const_19:
  .string "String vs number: %s == %s: %s"
.align 8
str_const_20:
  .string "String '42' should not equal number 42"
.align 8
str_const_21:
  .string ""
.align 8
str_const_22:
  .string ""
.align 8
str_const_23:
  .string "Empty string: '%s'"
.align 8
str_const_24:
  .string "Empty length check: %s"
.align 8
str_const_25:
  .string ""
.align 8
str_const_26:
  .string "Empty string should be empty"
.align 8
str_const_27:
  .string "Two empty strings should be equal"
.align 8
str_const_28:
  .string "Line 1
Line 2	Tabbed"
.align 8
str_const_29:
  .string "Special chars: %s"
.align 8
str_const_30:
  .string "Line 1
Line 2	Tabbed"
.align 8
str_const_31:
  .string "Special characters should be preserved"
.align 8
str_const_32:
  .string "He said "Hello""
.align 8
str_const_33:
  .string "Quoted: %s"
.align 8
str_const_34:
  .string "He said "Hello""
.align 8
str_const_35:
  .string "Quoted strings should work"
.align 8
str_const_36:
  .string "Limit"
.align 8
str_const_37:
  .string "L"
.align 8
str_const_38:
  .string "First character should be 'L'"
.align 8
str_const_39:
  .string "t"
.align 8
str_const_40:
  .string "Last character should be 't'"
.align 8
str_const_41:
  .string "String 'Limit' first char: %s, last char: %s"
.align 8
str_const_42:
  .string "=== String Operations Tests Complete ==="
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
  sub rsp, 984
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
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -96], rax
  cmpq [rbp + -120], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -104], rax
  cmpq [rbp + -144], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -112], rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq [rbp + -96], rcx
  movq [rbp + -112], rdx
  call lm_str_concat
  movq rax, [rbp + -192]
  movq [rbp + -192], rcx
  movq [rbp + -104], rdx
  call lm_str_concat
  movq rax, [rbp + -200]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -208], rcx
  movq [rbp + -96], rdx
  call lm_rt_str_format
  movq rax, [rbp + -216]
  movq [rbp + -216], rcx
  movq [rbp + -112], rdx
  call lm_rt_str_format
  movq rax, [rbp + -224]
  movq [rbp + -224], rcx
  movq [rbp + -104], rdx
  call lm_rt_str_format
  movq rax, [rbp + -232]
  movq [rbp + -232], rcx
  movq [rbp + -200], rdx
  call lm_rt_str_format
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  addq $16, rax
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  mov rax, [rax]
  movq rax, [rbp + -264]
  movq [rbp + -264], rcx
  call lm_print_str
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -200], rax
  cmpq [rbp + -272], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -280]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -280], rcx
  movq [rbp + -288], rdx
  call lm_assert
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  addq $16, rax
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  movq rax, [rbp + -312]
  movq [rbp + -312], rax
  mov rax, [rax]
  movq rax, [rbp + -320]
  movq [rbp + -320], rcx
  call lm_print_str
  movq [rbp + -96], rax
  cmpq [rbp + -104], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -328]
  movq [rbp + -96], rax
  cmpq [rbp + -104], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -336]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -344], rcx
  movq [rbp + -96], rdx
  call lm_rt_str_format
  movq rax, [rbp + -352]
  movq [rbp + -352], rcx
  movq [rbp + -104], rdx
  call lm_rt_str_format
  movq rax, [rbp + -360]
  movq [rbp + -360], rcx
  movq [rbp + -328], rdx
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
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -400], rcx
  movq [rbp + -96], rdx
  call lm_rt_str_format
  movq rax, [rbp + -408]
  movq [rbp + -408], rcx
  movq [rbp + -104], rdx
  call lm_rt_str_format
  movq rax, [rbp + -416]
  movq [rbp + -416], rcx
  movq [rbp + -336], rdx
  call lm_rt_str_format
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
  movq [rbp + -328], rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -456]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq [rbp + -456], rcx
  movq [rbp + -464], rdx
  call lm_assert
  movq [rbp + -336], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -472]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq [rbp + -472], rcx
  movq [rbp + -480], rdx
  call lm_assert
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -488]
  movq [rbp + -488], rax
  cmpq $337, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -496]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -504], rcx
  movq [rbp + -488], rdx
  call lm_rt_str_format
  movq rax, [rbp + -512]
  movq [rbp + -512], rcx
  movq $337, rdx
  call lm_rt_str_format
  movq rax, [rbp + -520]
  movq [rbp + -520], rcx
  movq [rbp + -496], rdx
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
  movq [rbp + -496], rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -560]
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -568]
  movq [rbp + -560], rcx
  movq [rbp + -568], rdx
  call lm_assert
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -584]
  movq [rbp + -576], rax
  cmpq [rbp + -584], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -592]
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -600]
  movq [rbp + -600], rcx
  movq [rbp + -576], rdx
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
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -640], rcx
  movq [rbp + -592], rdx
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
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -680]
  movq [rbp + -576], rax
  cmpq [rbp + -680], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -688]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -696]
  movq [rbp + -688], rcx
  movq [rbp + -696], rdx
  call lm_assert
  movq [rbp + -592], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -704]
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -712]
  movq [rbp + -704], rcx
  movq [rbp + -712], rdx
  call lm_assert
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -720]
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -728]
  movq [rbp + -728], rcx
  movq [rbp + -720], rdx
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
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -768]
  movq [rbp + -720], rax
  cmpq [rbp + -768], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -776]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -784]
  movq [rbp + -776], rcx
  movq [rbp + -784], rdx
  call lm_assert
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -792]
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -800]
  movq [rbp + -800], rcx
  movq [rbp + -792], rdx
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
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -840]
  movq [rbp + -792], rax
  cmpq [rbp + -840], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -848]
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -856]
  movq [rbp + -848], rcx
  movq [rbp + -856], rdx
  call lm_assert
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -864]
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -872]
  movq $0, rax
  cmpq [rbp + -872], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -880]
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -888]
  movq [rbp + -880], rcx
  movq [rbp + -888], rdx
  call lm_assert
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -896]
  movq $0, rax
  cmpq [rbp + -896], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -904]
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -912]
  movq [rbp + -904], rcx
  movq [rbp + -912], rdx
  call lm_assert
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -920]
  movq [rbp + -920], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -928]
  movq [rbp + -928], rcx
  movq $0, rdx
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
  movq [rel str_const_42], rcx
  call lm_box_string
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

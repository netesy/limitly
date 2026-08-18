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
  .string " === Control Flow Tests === "
.align 8
str_const_1:
  .string "Variable x should be 10"
.align 8
str_const_2:
  .string "Variable y should be 5"
.align 8
str_const_3:
  .string "If statement tests: "
.align 8
str_const_4:
  .string "x is greater than y"
.align 8
str_const_5:
  .string "x should be greater than y"
.align 8
str_const_6:
  .string "This should not print"
.align 8
str_const_7:
  .string "This branch should not execute"
.align 8
str_const_8:
  .string "x is not less than y"
.align 8
str_const_9:
  .string "x should not be less than y"
.align 8
str_const_10:
  .string "Score should be 75"
.align 8
str_const_11:
  .string "Grade calculation: "
.align 8
str_const_12:
  .string ""
.align 8
str_const_13:
  .string "A"
.align 8
str_const_14:
  .string "Score 75 should not get grade A"
.align 8
str_const_15:
  .string "B"
.align 8
str_const_16:
  .string "Score 75 should not get grade B"
.align 8
str_const_17:
  .string "C"
.align 8
str_const_18:
  .string "Score 75 should get grade C"
.align 8
str_const_19:
  .string "F"
.align 8
str_const_20:
  .string "Score 75 should not get grade F"
.align 8
str_const_21:
  .string "C"
.align 8
str_const_22:
  .string "Score 75 should result in grade C"
.align 8
str_const_23:
  .string "Grade: %s"
.align 8
str_const_24:
  .string "Nested if test: "
.align 8
str_const_25:
  .string "Variable a should be 15"
.align 8
str_const_26:
  .string "a is greater than 10"
.align 8
str_const_27:
  .string "a should be greater than 10"
.align 8
str_const_28:
  .string "a is also greater than 20"
.align 8
str_const_29:
  .string "a should not be greater than 20"
.align 8
str_const_30:
  .string "but a is not greater than 20"
.align 8
str_const_31:
  .string "a should not be greater than 20"
.align 8
str_const_32:
  .string "isActive should be true"
.align 8
str_const_33:
  .string "isValid should be false"
.align 8
str_const_34:
  .string "Active but not valid"
.align 8
str_const_35:
  .string "Should be active but not valid"
.align 8
str_const_36:
  .string "At least one is true"
.align 8
str_const_37:
  .string "At least one should be true"
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
  sub rsp, 856
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
  movq $81, rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  movq $41, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq [rel str_const_3], rcx
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
  movq $81, rax
  cmpq $41, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  testq rax, rax
  jne main_block_16
  jmp main_block_22
main_block_16:
  jmp main_block_16
  movq [rel str_const_4], rcx
  call lm_box_string
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
  movq $81, rax
  cmpq $41, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -200], rcx
  movq [rbp + -208], rdx
  call lm_assert
  jmp main_block_22
main_block_22:
  movq $81, rax
  cmpq $41, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  testq rax, rax
  jne main_block_24
  jmp main_block_30
main_block_24:
  jmp main_block_24
  movq [rel str_const_6], rcx
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
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq $10, rcx
  movq [rbp + -256], rdx
  call lm_assert
  jmp main_block_38
main_block_30:
  movq [rel str_const_8], rcx
  call lm_box_string
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
  movq $81, rax
  cmpq $41, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -304]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -304], rcx
  movq [rbp + -312], rdx
  call lm_assert
  jmp main_block_38
main_block_38:
  movq $601, rax
  cmpq $601, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -320]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -320], rcx
  movq [rbp + -328], rdx
  call lm_assert
  movq [rel str_const_11], rcx
  call lm_box_string
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
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq $601, rax
  cmpq $721, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  testq rax, rax
  jne main_block_49
  jmp main_block_55
main_block_49:
  jmp main_block_49
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq $10, rcx
  movq [rbp + -392], rdx
  call lm_assert
  jmp main_block_82
main_block_55:
  movq $601, rax
  cmpq $641, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  testq rax, rax
  jne main_block_58
  jmp main_block_64
main_block_58:
  jmp main_block_58
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq $10, rcx
  movq [rbp + -416], rdx
  call lm_assert
  jmp main_block_81
main_block_64:
  movq $601, rax
  cmpq $561, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  testq rax, rax
  jne main_block_67
  jmp main_block_74
main_block_67:
  jmp main_block_67
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq $601, rax
  cmpq $561, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -440]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -440], rcx
  movq [rbp + -448], rdx
  call lm_assert
  jmp main_block_80
main_block_74:
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq $10, rcx
  movq [rbp + -464], rdx
  call lm_assert
  jmp main_block_80
main_block_80:
  jmp main_block_81
main_block_81:
  jmp main_block_82
main_block_82:
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -456], rax
  cmpq [rbp + -472], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -480]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -488]
  movq [rbp + -480], rcx
  movq [rbp + -488], rdx
  call lm_assert
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -496], rcx
  movq [rbp + -456], rdx
  call lm_rt_str_format
  movq rax, [rbp + -504]
  movq [rbp + -504], rax
  addq $16, rax
  movq rax, [rbp + -512]
  movq [rbp + -512], rax
  movq rax, [rbp + -520]
  movq [rbp + -520], rax
  mov rax, [rax]
  movq rax, [rbp + -528]
  movq [rbp + -528], rcx
  call lm_print_str
  movq [rel str_const_24], rcx
  call lm_box_string
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
  movq $121, rax
  cmpq $121, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -568]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -568], rcx
  movq [rbp + -576], rdx
  call lm_assert
  movq $121, rax
  cmpq $81, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -584]
  movq [rbp + -584], rax
  testq rax, rax
  jne main_block_99
  jmp main_block_124
main_block_99:
  jmp main_block_99
  movq [rel str_const_26], rcx
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
  movq $121, rax
  cmpq $81, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -624]
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -632]
  movq [rbp + -624], rcx
  movq [rbp + -632], rdx
  call lm_assert
  movq $121, rax
  cmpq $161, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  testq rax, rax
  jne main_block_108
  jmp main_block_114
main_block_108:
  jmp main_block_108
  movq [rel str_const_28], rcx
  call lm_box_string
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
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -680]
  movq $10, rcx
  movq [rbp + -680], rdx
  call lm_assert
  jmp main_block_123
main_block_114:
  movq [rel str_const_30], rcx
  call lm_box_string
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
  movq $121, rax
  cmpq $161, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -720]
  movq [rbp + -720], rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -728]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -736]
  movq [rbp + -728], rcx
  movq [rbp + -736], rdx
  call lm_assert
  jmp main_block_123
main_block_123:
  jmp main_block_124
main_block_124:
  movq $18, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -744]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -752]
  movq [rbp + -744], rcx
  movq [rbp + -752], rdx
  call lm_assert
  movq $10, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -760]
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -768]
  movq [rbp + -760], rcx
  movq [rbp + -768], rdx
  call lm_assert
  movq $18, rax
  testq rax, rax
  jne main_block_136
  jmp main_block_140
main_block_136:
  jmp main_block_136
  movq $10, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -776]
  jmp main_block_140
main_block_140:
  movq [rbp + -776], rax
  testq rax, rax
  jne main_block_141
  jmp main_block_152
main_block_141:
  jmp main_block_141
  movq [rel str_const_34], rcx
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
  movq $18, rax
  testq rax, rax
  jne main_block_145
  jmp main_block_149
main_block_145:
  jmp main_block_145
  movq $10, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -816]
  jmp main_block_149
main_block_149:
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -824]
  movq [rbp + -816], rcx
  movq [rbp + -824], rdx
  call lm_assert
  jmp main_block_152
main_block_152:
  movq $18, rax
  testq rax, rax
  jne main_block_156
  jmp main_block_154
main_block_154:
  jmp main_block_154
  jmp main_block_156
main_block_156:
  movq $10, rax
  testq rax, rax
  jne main_block_157
  jmp main_block_166
main_block_157:
  jmp main_block_157
  movq [rel str_const_36], rcx
  call lm_box_string
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
  movq $18, rax
  testq rax, rax
  jne main_block_163
  jmp main_block_161
main_block_161:
  jmp main_block_161
  jmp main_block_163
main_block_163:
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -864]
  movq $10, rcx
  movq [rbp + -864], rdx
  call lm_assert
  jmp main_block_166
main_block_166:
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

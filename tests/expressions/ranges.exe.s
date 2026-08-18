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
  .string "=== Range Expression Tests ==="
.align 8
str_const_1:
  .string "Range 1..5:"
.align 8
str_const_2:
  .string "Range 1..5 should iterate 4 times (1,2,3,4)"
.align 8
str_const_3:
  .string "Sum of 1+2+3+4 should be 10"
.align 8
str_const_4:
  .string "Range 0..3:"
.align 8
str_const_5:
  .string "Range 0..3 should iterate 3 times (0,1,2)"
.align 8
str_const_6:
  .string "Sum of 0+1+2 should be 3"
.align 8
str_const_7:
  .string "Variable range %s..%s:"
.align 8
str_const_8:
  .string "Range 5..8 should iterate 3 times (5,6,7)"
.align 8
str_const_9:
  .string "Sum of 5+6+7 should be 18"
.align 8
str_const_10:
  .string "Expression range %s..%s:"
.align 8
str_const_11:
  .string "Range 2..5 should iterate 3 times (2,3,4)"
.align 8
str_const_12:
  .string "Sum of 2+3+4 should be 9"
.align 8
str_const_13:
  .string "Nested ranges:"
.align 8
str_const_14:
  .string "Outer: %s"
.align 8
str_const_15:
  .string "  Inner: %s"
.align 8
str_const_16:
  .string "Each inner range should iterate 2 times"
.align 8
str_const_17:
  .string "Outer range should iterate 2 times (1,2)"
.align 8
str_const_18:
  .string "Total inner iterations should be 4"
.align 8
str_const_19:
  .string "Empty range (5..5):"
.align 8
str_const_20:
  .string "This should not print: %s"
.align 8
str_const_21:
  .string "Empty range should not iterate"
.align 8
str_const_22:
  .string "Empty range test complete"
.align 8
str_const_23:
  .string "=== Range Expression Tests Complete ==="
.align 8
str_minus:
  .string "-"
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
  sub rsp, 936
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
  jmp main_block_9
main_block_9:
  movq $9, rax
  cmpq $41, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne main_block_12
  jmp main_block_21
main_block_12:
  jmp main_block_12
  movq $9, rcx
  call lm_print_int
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -136]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp main_block_17
main_block_17:
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -152]
  jmp main_block_9
main_block_21:
  movq [rbp + -136], rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq [rbp + -144], rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
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
  jmp main_block_36
main_block_36:
  movq $1, rax
  cmpq $25, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  testq rax, rax
  jne main_block_39
  jmp main_block_48
main_block_39:
  jmp main_block_39
  movq $1, rcx
  call lm_print_int
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -232]
  movq $1, rax
  addq $1, rax
  movq rax, [rbp + -240]
  jmp main_block_44
main_block_44:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -248]
  jmp main_block_36
main_block_48:
  movq [rbp + -232], rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -256], rcx
  movq [rbp + -264], rdx
  call lm_assert
  movq [rbp + -240], rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -272]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -272], rcx
  movq [rbp + -280], rdx
  call lm_assert
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -288], rcx
  movq $41, rdx
  call lm_rt_str_format
  movq rax, [rbp + -296]
  movq [rbp + -296], rcx
  movq $65, rdx
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
  jmp main_block_67
main_block_67:
  movq $41, rax
  cmpq $65, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -336]
  movq [rbp + -336], rax
  testq rax, rax
  jne main_block_69
  jmp main_block_78
main_block_69:
  jmp main_block_69
  movq $41, rcx
  call lm_print_int
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -344]
  movq $1, rax
  addq $41, rax
  movq rax, [rbp + -352]
  jmp main_block_74
main_block_74:
  movq $41, rax
  addq $9, rax
  movq rax, [rbp + -360]
  jmp main_block_67
main_block_78:
  movq [rbp + -344], rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -368]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -368], rcx
  movq [rbp + -376], rdx
  call lm_assert
  movq [rbp + -352], rax
  cmpq $145, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -384]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq [rbp + -384], rcx
  movq [rbp + -392], rdx
  call lm_assert
  movq $17, rax
  addq $25, rax
  movq rax, [rbp + -400]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -408], rcx
  movq $17, rdx
  call lm_rt_str_format
  movq rax, [rbp + -416]
  movq [rbp + -416], rcx
  movq [rbp + -400], rdx
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
  jmp main_block_99
main_block_99:
  movq $17, rax
  addq $25, rax
  movq rax, [rbp + -456]
  movq $17, rax
  cmpq [rbp + -456], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -464]
  movq [rbp + -464], rax
  testq rax, rax
  jne main_block_104
  jmp main_block_113
main_block_104:
  jmp main_block_104
  movq $17, rcx
  call lm_print_int
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -472]
  movq $1, rax
  addq $17, rax
  movq rax, [rbp + -480]
  jmp main_block_109
main_block_109:
  movq $17, rax
  addq $9, rax
  movq rax, [rbp + -488]
  jmp main_block_99
main_block_113:
  movq [rbp + -472], rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -496]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -496], rcx
  movq [rbp + -504], rdx
  call lm_assert
  movq [rbp + -480], rax
  cmpq $73, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -512]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -512], rcx
  movq [rbp + -520], rdx
  call lm_assert
  movq [rel str_const_13], rcx
  call lm_box_string
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
  jmp main_block_128
main_block_128:
  movq $9, rax
  cmpq $25, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -560]
  movq [rbp + -560], rax
  testq rax, rax
  jne main_block_131
  jmp main_block_171
main_block_131:
  jmp main_block_131
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -568]
  movq [rbp + -568], rcx
  movq $9, rdx
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
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -608]
  movq $9, rax
  imulq $81, rax
  movq rax, [rbp + -616]
  jmp main_block_141
main_block_141:
  movq $9, rax
  imulq $81, rax
  movq rax, [rbp + -624]
  movq $9, rax
  imulq $81, rax
  movq rax, [rbp + -632]
  movq [rbp + -632], rax
  addq $17, rax
  movq rax, [rbp + -640]
  movq [rbp + -616], rax
  cmpq [rbp + -640], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -648]
  movq [rbp + -648], rax
  testq rax, rax
  jne main_block_150
  jmp main_block_162
main_block_150:
  jmp main_block_150
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -656]
  movq [rbp + -656], rcx
  movq [rbp + -616], rdx
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
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -696]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -704]
  jmp main_block_158
main_block_158:
  movq [rbp + -616], rax
  addq $9, rax
  movq rax, [rbp + -712]
  jmp main_block_141
main_block_162:
  movq [rbp + -696], rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -720]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -728]
  movq [rbp + -720], rcx
  movq [rbp + -728], rdx
  call lm_assert
  jmp main_block_167
main_block_167:
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -736]
  jmp main_block_128
main_block_171:
  movq [rbp + -608], rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -744]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -752]
  movq [rbp + -744], rcx
  movq [rbp + -752], rdx
  call lm_assert
  movq [rbp + -704], rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -760]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -768]
  movq [rbp + -760], rcx
  movq [rbp + -768], rdx
  call lm_assert
  movq [rel str_const_19], rcx
  call lm_box_string
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
  jmp main_block_185
main_block_185:
  movq $41, rax
  cmpq $41, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -808]
  movq [rbp + -808], rax
  testq rax, rax
  jne main_block_188
  jmp main_block_198
main_block_188:
  jmp main_block_188
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -816]
  movq [rbp + -816], rcx
  movq $41, rdx
  call lm_rt_str_format
  movq rax, [rbp + -824]
  movq [rbp + -824], rax
  addq $16, rax
  movq rax, [rbp + -832]
  movq [rbp + -832], rax
  movq rax, [rbp + -840]
  movq [rbp + -840], rax
  mov rax, [rax]
  movq rax, [rbp + -848]
  movq [rbp + -848], rcx
  call lm_print_str
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -856]
  jmp main_block_194
main_block_194:
  movq $41, rax
  addq $9, rax
  movq rax, [rbp + -864]
  jmp main_block_185
main_block_198:
  movq [rbp + -856], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -872]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -880]
  movq [rbp + -872], rcx
  movq [rbp + -880], rdx
  call lm_assert
  movq [rel str_const_22], rcx
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
  movq [rel str_const_23], rcx
  call lm_box_string
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

.globl lm_print_int
lm_print_int:
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
lm_print_int_entry:
  # Bump Allocation: 32 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 32
  mov [rel heap_ptr], rax
  movq [rbp + -72], rax
  addq $31, rax
  movq rax, [rbp + -80]
  movq $10, rax
  movq [rbp + -80], rdx
  mov byte ptr [rdx], al
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 8
  mov [rel heap_ptr], rax
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -96], rax
  add rax, 8
  mov [rel heap_ptr], rax
  movq [rbp + -80], rax
  movq [rbp + -96], rdx
  mov [rdx], rax
  movq [rbp + -64], rax
  cmpq $0, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne lm_print_int_neg
  jmp lm_print_int_abs
lm_print_int_neg:
  subq $32, %rsp
  movq $1, rcx
  movq [rel str_minus], rdx
  movq $1, r8
  call _write
  addq $32, %rsp
  movq [rbp + -64], rax
  negq rax
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  jmp lm_print_int_loop
lm_print_int_abs:
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  jmp lm_print_int_loop
lm_print_int_loop:
  movq [rbp + -88], rax
  mov rax, [rax]
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  cqto
  movq $10, rcx
  idivq rcx
  movq rax, [rbp + -136]
  movq [rbp + -128], rax
  cqto
  movq $10, rcx
  idivq rcx
  movq rdx, [rbp + -144]
  movq [rbp + -144], rax
  addq $48, rax
  movq rax, [rbp + -152]
  movq [rbp + -96], rax
  mov rax, [rax]
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  subq $1, rax
  movq rax, [rbp + -168]
  movq [rbp + -152], rax
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  movq [rbp + -168], rdx
  mov byte ptr [rdx], al
  movq [rbp + -136], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rbp + -168], rax
  movq [rbp + -96], rdx
  mov [rdx], rax
  movq [rbp + -136], rax
  cmpq $1, rax
  setae al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  testq rax, rax
  jne lm_print_int_loop
  jmp lm_print_int_done
lm_print_int_done:
  movq [rbp + -96], rax
  mov rax, [rax]
  movq rax, [rbp + -192]
  movq [rbp + -72], rax
  addq $32, rax
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  subq [rbp + -192], rax
  movq rax, [rbp + -208]
  subq $32, %rsp
  movq $1, rcx
  movq [rbp + -192], rdx
  movq [rbp + -208], r8
  call _write
  addq $32, %rsp
  movq $0, rax
  jmp lm_print_int_epilogue
lm_print_int_epilogue:
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
.Lfunc_end_lm_print_int:

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

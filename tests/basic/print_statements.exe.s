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
  .string "=== Print Statement Tests ==="
.align 8
str_const_1:
  .string "Hello, World!"
.align 8
str_const_2:
  .string "Limit"
.align 8
str_const_3:
  .string "Limit"
.align 8
str_const_4:
  .string "Variable name should be 'Limit'"
.align 8
str_const_5:
  .string "Variable version should be 1.0"
.align 8
str_const_6:
  .string "Result: "
.align 8
str_const_7:
  .string "Success"
.align 8
str_const_8:
  .string "2 + 3 should equal 5"
.align 8
str_const_9:
  .string "10 > 5 should be true"
.align 8
str_const_10:
  .string "Result: Success"
.align 8
str_const_11:
  .string "String concatenation should work"
.align 8
str_const_12:
  .string "Variable x should be 42"
.align 8
str_const_13:
  .string "The answer is %s"
.align 8
str_const_14:
  .string ""
.align 8
str_const_15:
  .string "Boolean true should be true"
.align 8
str_const_16:
  .string "Boolean false should be false"
.align 8
str_const_17:
  .string "Nil value should be nil"
.align 8
str_const_18:
  .string "Zero should be 0"
.align 8
str_const_19:
  .string ""
.align 8
str_const_20:
  .string "Empty string should be empty"
.align 8
str_const_21:
  .string "Variable a should be 5"
.align 8
str_const_22:
  .string "Variable b should be 3"
.align 8
str_const_23:
  .string "5 + 3 should equal 8"
.align 8
str_const_24:
  .string "5 > 3 should be true"
.align 8
str_const_25:
  .string "Math: %s + %s = %s"
.align 8
str_const_26:
  .string "Logic: %s > %s is %s"
.align 8
str_const_27:
  .string "Numbers 1-3:"
.align 8
str_const_28:
  .string "Number: %s"
.align 8
str_const_29:
  .string "Loop should execute 3 times"
.align 8
str_const_30:
  .string "Line 1
Line 2"
.align 8
str_const_31:
  .string "Tab	Separated"
.align 8
str_const_32:
  .string "Quote: "Hello""
.align 8
str_const_33:
  .string "Line 1
Line 2"
.align 8
str_const_34:
  .string "Line string should contain newline"
.align 8
str_const_35:
  .string "Tab	Separated"
.align 8
str_const_36:
  .string "Tab string should contain tab"
.align 8
str_const_37:
  .string "Quote: "Hello""
.align 8
str_const_38:
  .string "Quote string should contain quotes"
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
  sub rsp, 952
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
  movq [rbp + -128], rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq [rbp + -128], rax
  addq $16, rax
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  mov rax, [rax]
  movq rax, [rbp + -192]
  movq [rbp + -192], rcx
  call lm_print_str
  movq $2, rcx
  call lm_print_int
  movq $17, rax
  addq $25, rax
  movq rax, [rbp + -200]
  movq $81, rax
  cmpq $41, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -216], rcx
  movq [rbp + -224], rdx
  call lm_str_concat
  movq rax, [rbp + -232]
  movq [rbp + -200], rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq [rbp + -208], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -256], rcx
  movq [rbp + -264], rdx
  call lm_assert
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -232], rax
  cmpq [rbp + -272], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -280]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -280], rcx
  movq [rbp + -288], rdx
  call lm_assert
  movq [rbp + -200], rcx
  call lm_print_int
  movq [rbp + -208], rcx
  call lm_print_int
  movq [rbp + -232], rax
  addq $16, rax
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  mov rax, [rax]
  movq rax, [rbp + -312]
  movq [rbp + -312], rcx
  call lm_print_str
  movq $337, rax
  cmpq $337, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -320]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -320], rcx
  movq [rbp + -328], rdx
  call lm_assert
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -336], rcx
  movq $337, rdx
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
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq $18, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -384]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq [rbp + -384], rcx
  movq [rbp + -392], rdx
  call lm_assert
  movq $10, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -400]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -400], rcx
  movq [rbp + -408], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -416]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -416], rcx
  movq [rbp + -424], rdx
  call lm_assert
  movq $1, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -432]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rbp + -432], rcx
  movq [rbp + -440], rdx
  call lm_assert
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -376], rax
  cmpq [rbp + -448], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -456]
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq [rbp + -456], rcx
  movq [rbp + -464], rdx
  call lm_assert
  movq $18, rcx
  call lm_print_int
  movq $10, rcx
  call lm_print_int
  movq $2, rcx
  call lm_print_int
  movq $1, rcx
  call lm_print_int
  movq [rbp + -376], rax
  addq $16, rax
  movq rax, [rbp + -472]
  movq [rbp + -472], rax
  movq rax, [rbp + -480]
  movq [rbp + -480], rax
  mov rax, [rax]
  movq rax, [rbp + -488]
  movq [rbp + -488], rcx
  call lm_print_str
  movq $41, rax
  addq $25, rax
  movq rax, [rbp + -496]
  movq $41, rax
  cmpq $25, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -504]
  movq $41, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -512]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -512], rcx
  movq [rbp + -520], rdx
  call lm_assert
  movq $25, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -528]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -536]
  movq [rbp + -528], rcx
  movq [rbp + -536], rdx
  call lm_assert
  movq [rbp + -496], rax
  cmpq $65, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -544]
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -552]
  movq [rbp + -544], rcx
  movq [rbp + -552], rdx
  call lm_assert
  movq [rbp + -504], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -560]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -568]
  movq [rbp + -560], rcx
  movq [rbp + -568], rdx
  call lm_assert
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -576], rcx
  movq $41, rdx
  call lm_rt_str_format
  movq rax, [rbp + -584]
  movq [rbp + -584], rcx
  movq $25, rdx
  call lm_rt_str_format
  movq rax, [rbp + -592]
  movq [rbp + -592], rcx
  movq [rbp + -496], rdx
  call lm_rt_str_format
  movq rax, [rbp + -600]
  movq [rbp + -600], rax
  addq $16, rax
  movq rax, [rbp + -608]
  movq [rbp + -608], rax
  movq rax, [rbp + -616]
  movq [rbp + -616], rax
  mov rax, [rax]
  movq rax, [rbp + -624]
  movq [rbp + -624], rcx
  call lm_print_str
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -632]
  movq [rbp + -632], rcx
  movq $41, rdx
  call lm_rt_str_format
  movq rax, [rbp + -640]
  movq [rbp + -640], rcx
  movq $25, rdx
  call lm_rt_str_format
  movq rax, [rbp + -648]
  movq [rbp + -648], rcx
  movq [rbp + -504], rdx
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
  movq [rel str_const_27], rcx
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
  jmp main_block_121
main_block_121:
  jmp main_block_123
main_block_123:
  movq $9, rax
  cmpq $25, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -720]
  movq [rbp + -720], rax
  testq rax, rax
  jne main_block_126
  jmp main_block_135
main_block_126:
  jmp main_block_126
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -728]
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -736]
  movq [rbp + -736], rcx
  movq $9, rdx
  call lm_rt_str_format
  movq rax, [rbp + -744]
  movq [rbp + -744], rax
  addq $16, rax
  movq rax, [rbp + -752]
  movq [rbp + -752], rax
  movq rax, [rbp + -760]
  movq [rbp + -760], rax
  mov rax, [rax]
  movq rax, [rbp + -768]
  movq [rbp + -768], rcx
  call lm_print_str
  jmp main_block_132
main_block_132:
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -776]
  jmp main_block_123
main_block_135:
  movq [rbp + -728], rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -784]
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -792]
  movq [rbp + -784], rcx
  movq [rbp + -792], rdx
  call lm_assert
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -800]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -808]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -816]
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -824]
  movq [rbp + -800], rax
  cmpq [rbp + -824], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -832]
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -840]
  movq [rbp + -832], rcx
  movq [rbp + -840], rdx
  call lm_assert
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -848]
  movq [rbp + -808], rax
  cmpq [rbp + -848], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -856]
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -864]
  movq [rbp + -856], rcx
  movq [rbp + -864], rdx
  call lm_assert
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -872]
  movq [rbp + -816], rax
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
  movq [rbp + -800], rax
  addq $16, rax
  movq rax, [rbp + -896]
  movq [rbp + -896], rax
  movq rax, [rbp + -904]
  movq [rbp + -904], rax
  mov rax, [rax]
  movq rax, [rbp + -912]
  movq [rbp + -912], rcx
  call lm_print_str
  movq [rbp + -808], rax
  addq $16, rax
  movq rax, [rbp + -920]
  movq [rbp + -920], rax
  movq rax, [rbp + -928]
  movq [rbp + -928], rax
  mov rax, [rax]
  movq rax, [rbp + -936]
  movq [rbp + -936], rcx
  call lm_print_str
  movq [rbp + -816], rax
  addq $16, rax
  movq rax, [rbp + -944]
  movq [rbp + -944], rax
  movq rax, [rbp + -952]
  movq [rbp + -952], rax
  mov rax, [rax]
  movq rax, [rbp + -960]
  movq [rbp + -960], rcx
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

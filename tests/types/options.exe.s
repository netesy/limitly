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
  .string "=== Option Type Tests ==="
.align 8
str_const_1:
  .string "
--- Test 1: Basic Option Types ---"
.align 8
str_const_2:
  .string "
--- Test 2: Option-like Union Types ---"
.align 8
str_const_3:
  .string "None"
.align 8
str_const_4:
  .string "hello"
.align 8
str_const_5:
  .string "Maybe int (value): %s"
.align 8
str_const_6:
  .string "Maybe string (value): %s"
.align 8
str_const_7:
  .string "None representation: %s"
.align 8
str_const_8:
  .string "
--- Test 3: Optional Parameter Simulation ---"
.align 8
str_const_9:
  .string "Alice"
.align 8
str_const_10:
  .string "
--- Test 4: Option-like Return Types ---"
.align 8
str_const_11:
  .string "Search result (found): %s"
.align 8
str_const_12:
  .string "Search result (not found): %s"
.align 8
str_const_13:
  .string "
--- Test 5: Chained Optional Operations ---"
.align 8
str_const_14:
  .string "Chain result 1: %s"
.align 8
str_const_15:
  .string "Chain result 2: %s"
.align 8
str_const_16:
  .string "
--- Test 6: Error Handling Compatibility ---"
.align 8
str_const_17:
  .string "Safe divide (success): %s"
.align 8
str_const_18:
  .string "Safe divide (error): %s"
.align 8
str_const_19:
  .string "
--- Test 7: Nested Option-like Types ---"
.align 8
str_const_20:
  .string "nested"
.align 8
str_const_21:
  .string "Nested option 1: %s"
.align 8
str_const_22:
  .string "Nested option 2: %s"
.align 8
str_const_23:
  .string "Nested option 3: %s"
.align 8
str_const_24:
  .string "
=== Option Type Tests Complete ==="
.align 8
str_const_25:
  .string "division by zero"
.align 8
str_const_26:
  .string "too small"
.align 8
str_const_27:
  .string "Hello, %s!"
.align 8
str_const_28:
  .string "Hello, stranger!"
.align 8
str_const_29:
  .string "not found"
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
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -176], rcx
  movq $337, rdx
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
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -216], rcx
  movq [rbp + -168], rdx
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
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -256], rcx
  movq [rbp + -160], rdx
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
  movq [rel str_const_8], rcx
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
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -328], rcx
  call greetOptional
  movq [rel str_const_10], rcx
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
  movq $41, rcx
  call findInArray
  movq $9, rax
  negq rax
  movq rax, [rbp + -368]
  movq [rbp + -368], rcx
  call findInArray
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -376], rcx
  movq $r25, rdx
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
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -416], rcx
  movq $r29, rdx
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
  movq $121, rcx
  call chainOptional
  movq $41, rcx
  call chainOptional
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -488]
  movq [rbp + -488], rcx
  movq $r40, rdx
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
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -528], rcx
  movq $r43, rdx
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
  movq [rel str_const_16], rcx
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
  movq $81, rcx
  movq $17, rdx
  call safeDivide
  movq $81, rcx
  movq $1, rdx
  call safeDivide
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -600]
  movq [rbp + -600], rcx
  movq $r55, rdx
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
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -640], rcx
  movq $r59, rdx
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
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -680]
  movq [rbp + -680], rax
  addq $16, rax
  movq rax, [rbp + -688]
  movq [rbp + -688], rax
  movq rax, [rbp + -696]
  movq [rbp + -696], rax
  mov rax, [rax]
  movq rax, [rbp + -704]
  movq [rbp + -704], rcx
  call lm_print_str
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -712]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -720]
  movq [rbp + -720], rcx
  movq $337, rdx
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
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -760]
  movq [rbp + -760], rcx
  movq [rbp + -712], rdx
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
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -800]
  movq [rbp + -800], rcx
  movq $18, rdx
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
  movq [rel str_const_24], rcx
  call lm_box_string
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

.globl safeDivide
safeDivide:
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
safeDivide_entry:
safeDivide_block_0:
  movq [rbp + -72], rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne safeDivide_block_3
  jmp safeDivide_block_5
safeDivide_block_3:
  jmp safeDivide_block_3
  movq [rbp + -64], rax
  cqto
  movq [rbp + -72], rcx
  idivq rcx
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp safeDivide_epilogue
safeDivide_block_5:
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp safeDivide_epilogue
safeDivide_epilogue:
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
.Lfunc_end_safeDivide:

.globl chainOptional
chainOptional:
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
chainOptional_entry:
chainOptional_block_0:
  movq [rbp + -64], rcx
  call processOptional
  movq $r1, rax
  jmp chainOptional_epilogue
chainOptional_epilogue:
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
.Lfunc_end_chainOptional:

.globl processOptional
processOptional:
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
processOptional_entry:
processOptional_block_0:
  movq [rbp + -64], rax
  cmpq $81, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne processOptional_block_3
  jmp processOptional_block_6
processOptional_block_3:
  jmp processOptional_block_3
  movq [rbp + -64], rax
  imulq $17, rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp processOptional_epilogue
processOptional_block_6:
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp processOptional_epilogue
processOptional_epilogue:
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
.Lfunc_end_processOptional:

.globl greetOptional
greetOptional:
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
greetOptional_entry:
greetOptional_block_0:
  movq [rbp + -64], rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne greetOptional_block_3
  jmp greetOptional_block_7
greetOptional_block_3:
  jmp greetOptional_block_3
  movq [rel str_const_27], rcx
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
  jmp greetOptional_block_10
greetOptional_block_7:
  movq [rel str_const_28], rcx
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
  jmp greetOptional_block_10
greetOptional_block_10:
  movq $0, rax
  jmp greetOptional_epilogue
greetOptional_epilogue:
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
.Lfunc_end_greetOptional:

.globl findInArray
findInArray:
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
findInArray_entry:
findInArray_block_0:
  movq [rbp + -64], rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne findInArray_block_3
  jmp findInArray_block_4
findInArray_block_3:
  jmp findInArray_block_3
  movq $0, rax
  jmp findInArray_epilogue
findInArray_block_4:
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp findInArray_epilogue
findInArray_epilogue:
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
.Lfunc_end_findInArray:

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

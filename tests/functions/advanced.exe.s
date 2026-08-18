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
  .string "=== Advanced Function Tests ==="
.align 8
str_const_1:
  .string "
--- Test 1: Optional Parameters ---"
.align 8
str_const_2:
  .string "Charlie"
.align 8
str_const_3:
  .string "
--- Test 2: Default Parameters ---"
.align 8
str_const_4:
  .string "World"
.align 8
str_const_5:
  .string "Alice"
.align 8
str_const_6:
  .string "
--- Test 3: Multiple Optional Parameters ---"
.align 8
str_const_7:
  .string "Bob"
.align 8
str_const_8:
  .string "Charlie"
.align 8
str_const_9:
  .string "Diana"
.align 8
str_const_10:
  .string "
--- Test 4: Optional Math Parameters ---"
.align 8
str_const_11:
  .string "power(3) = %s"
.align 8
str_const_12:
  .string "power(3, 4) = %s"
.align 8
str_const_13:
  .string "
--- Test 5: Complex Signatures ---"
.align 8
str_const_14:
  .string "test"
.align 8
str_const_15:
  .string "test"
.align 8
str_const_16:
  .string "test"
.align 8
str_const_17:
  .string "processData('test') = %s"
.align 8
str_const_18:
  .string "processData('test', true) = %s"
.align 8
str_const_19:
  .string "processData('test', false, 2) = %s"
.align 8
str_const_20:
  .string "
--- Test 6: Function Variants ---"
.align 8
str_const_21:
  .string "
--- Test 7: Nested Function Calls ---"
.align 8
str_const_22:
  .string "double(addOne(5)) = %s"
.align 8
str_const_23:
  .string "addOne(double(5)) = %s"
.align 8
str_const_24:
  .string "
=== Advanced Function Tests Complete ==="
.align 8
str_const_25:
  .string "Boolean: %s"
.align 8
str_const_26:
  .string "TRANSFORMED: "
.align 8
str_const_27:
  .string " "
.align 8
str_const_28:
  .string "Hello, %s!"
.align 8
str_const_29:
  .string "Hello, %s!"
.align 8
str_const_30:
  .string "Hello, stranger!"
.align 8
str_const_31:
  .string "Number: %s"
.align 8
str_const_32:
  .string "User: %s, Age: %s, Active: %s"
.align 8
str_const_33:
  .string "Float: %s"
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
  sub rsp, 728
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
  call greetOptional
  movq $2, rcx
  call greetOptional
  movq [rel str_const_3], rcx
  call lm_box_string
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
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -168], rcx
  call greetWithDefault
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -176], rcx
  call greetWithDefault
  movq [rel str_const_6], rcx
  call lm_box_string
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
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -216], rcx
  movq $145, rdx
  movq $18, r8
  call createUser
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -224], rcx
  movq $201, rdx
  movq $18, r8
  call createUser
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -232], rcx
  movq $241, rdx
  movq $10, r8
  call createUser
  movq [rel str_const_10], rcx
  call lm_box_string
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
  movq $25, rcx
  movq $17, rdx
  call power
  movq $25, rcx
  movq $33, rdx
  call power
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -272], rcx
  movq $r32, rdx
  call lm_rt_str_format
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  addq $16, rax
  movq rax, [rbp + -288]
  movq [rbp + -288], rax
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  mov rax, [rax]
  movq rax, [rbp + -304]
  movq [rbp + -304], rcx
  call lm_print_str
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -312], rcx
  movq $r36, rdx
  call lm_rt_str_format
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  addq $16, rax
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  movq rax, [rbp + -336]
  movq [rbp + -336], rax
  mov rax, [rax]
  movq rax, [rbp + -344]
  movq [rbp + -344], rcx
  call lm_print_str
  movq [rel str_const_13], rcx
  call lm_box_string
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
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -384], rcx
  movq $10, rdx
  movq $9, r8
  call processData
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq [rbp + -392], rcx
  movq $18, rdx
  movq $9, r8
  call processData
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -400], rcx
  movq $10, rdx
  movq $17, r8
  call processData
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -408], rcx
  movq $r49, rdx
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
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -448], rcx
  movq $r54, rdx
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
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -488]
  movq [rbp + -488], rcx
  movq $r59, rdx
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
  movq [rel str_const_20], rcx
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
  movq $337, rcx
  call formatNumber
  movq $2, rcx
  call formatFloat
  movq $18, rcx
  call formatBool
  movq $r73, rax
  addq $16, rax
  movq rax, $
  movq $, rax
  movq rax, [rbp + -560]
  movq [rbp + -560], rax
  mov rax, [rax]
  movq rax, [rbp + -568]
  movq [rbp + -568], rcx
  call lm_print_str
  movq $r76, rax
  addq $16, rax
  movq rax, $
  movq $, rax
  movq rax, [rbp + -576]
  movq [rbp + -576], rax
  mov rax, [rax]
  movq rax, [rbp + -584]
  movq [rbp + -584], rcx
  call lm_print_str
  movq $r79, rax
  addq $16, rax
  movq rax, $
  movq $, rax
  movq rax, [rbp + -592]
  movq [rbp + -592], rax
  mov rax, [rax]
  movq rax, [rbp + -600]
  movq [rbp + -600], rcx
  call lm_print_str
  movq [rel str_const_21], rcx
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
  movq $41, rcx
  call addOne
  movq $r87, rcx
  call double
  movq $41, rcx
  call double
  movq $r91, rcx
  call addOne
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -640], rcx
  movq $r88, rdx
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
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -680]
  movq [rbp + -680], rcx
  movq $r92, rdx
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
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -720]
  movq [rbp + -720], rax
  addq $16, rax
  movq rax, [rbp + -728]
  movq [rbp + -728], rax
  movq rax, [rbp + -736]
  movq [rbp + -736], rax
  mov rax, [rax]
  movq rax, [rbp + -744]
  movq [rbp + -744], rcx
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

.globl double
double:
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
double_entry:
double_block_0:
  movq [rbp + -64], rax
  imulq $17, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp double_epilogue
double_epilogue:
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
.Lfunc_end_double:

.globl formatBool
formatBool:
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
formatBool_entry:
formatBool_block_0:
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call lm_rt_str_format
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp formatBool_epilogue
formatBool_epilogue:
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
.Lfunc_end_formatBool:

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
  sub rsp, 136
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
processData_entry:
processData_block_0:
  movq [rbp + -72], rax
  testq rax, rax
  jne processData_block_2
  jmp processData_block_6
processData_block_2:
  jmp processData_block_2
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  movq [rbp + -64], rdx
  call lm_str_concat
  movq rax, [rbp + -96]
  jmp processData_block_6
processData_block_6:
  movq [rbp + -80], rax
  cmpq $9, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne processData_block_9
  jmp processData_block_25
processData_block_9:
  jmp processData_block_9
  jmp processData_block_13
processData_block_13:
  movq $17, rax
  cmpq [rbp + -80], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne processData_block_15
  jmp processData_block_24
processData_block_15:
  jmp processData_block_15
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -96], rcx
  movq [rbp + -120], rdx
  call lm_str_concat
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  movq [rbp + -96], rdx
  call lm_str_concat
  movq rax, [rbp + -136]
  jmp processData_block_20
processData_block_20:
  movq $17, rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp processData_block_13
processData_block_24:
  jmp processData_block_25
processData_block_25:
  movq [rbp + -136], rax
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

.globl power
power:
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
power_entry:
power_block_0:
  jmp power_block_4
power_block_4:
  movq $9, rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne power_block_6
  jmp power_block_13
power_block_6:
  jmp power_block_6
  movq $9, rax
  imulq [rbp + -64], rax
  movq rax, [rbp + -88]
  jmp power_block_9
power_block_9:
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -96]
  jmp power_block_4
power_block_13:
  movq [rbp + -88], rax
  jmp power_epilogue
power_epilogue:
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
.Lfunc_end_power:

.globl greetWithDefault
greetWithDefault:
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
greetWithDefault_entry:
greetWithDefault_block_0:
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call lm_rt_str_format
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  addq $16, rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  mov rax, [rax]
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  call lm_print_str
  movq $0, rax
  jmp greetWithDefault_epilogue
greetWithDefault_epilogue:
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
.Lfunc_end_greetWithDefault:

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
  movq [rel str_const_29], rcx
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
  movq [rel str_const_30], rcx
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

.globl formatNumber
formatNumber:
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
formatNumber_entry:
formatNumber_block_0:
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call lm_rt_str_format
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp formatNumber_epilogue
formatNumber_epilogue:
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
.Lfunc_end_formatNumber:

.globl createUser
createUser:
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
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
createUser_entry:
createUser_block_0:
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  movq [rbp + -64], rdx
  call lm_rt_str_format
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  movq [rbp + -72], rdx
  call lm_rt_str_format
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  movq [rbp + -80], rdx
  call lm_rt_str_format
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  addq $16, rax
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  mov rax, [rax]
  movq rax, [rbp + -136]
  movq [rbp + -136], rcx
  call lm_print_str
  movq $0, rax
  jmp createUser_epilogue
createUser_epilogue:
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
.Lfunc_end_createUser:

.globl addOne
addOne:
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
addOne_entry:
addOne_block_0:
  movq [rbp + -64], rax
  addq $9, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp addOne_epilogue
addOne_epilogue:
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
.Lfunc_end_addOne:

.globl formatFloat
formatFloat:
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
formatFloat_entry:
formatFloat_block_0:
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call lm_rt_str_format
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp formatFloat_epilogue
formatFloat_epilogue:
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
.Lfunc_end_formatFloat:

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

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
  .string "=== Variable Declaration Tests ==="
.align 8
str_const_1:
  .string "Limit"
.align 8
str_const_2:
  .string "Variable x should be 42"
.align 8
str_const_3:
  .string "Variable y should be 3.14"
.align 8
str_const_4:
  .string "Limit"
.align 8
str_const_5:
  .string "Variable name should be 'Limit'"
.align 8
str_const_6:
  .string "Variable isActive should be true"
.align 8
str_const_7:
  .string "Integer: %s"
.align 8
str_const_8:
  .string "Float: %s"
.align 8
str_const_9:
  .string "String: %s"
.align 8
str_const_10:
  .string "Boolean: %s"
.align 8
str_const_11:
  .string "Language"
.align 8
str_const_12:
  .string "Reassigned x should be 100"
.align 8
str_const_13:
  .string "Reassigned y should be 2.71"
.align 8
str_const_14:
  .string "Language"
.align 8
str_const_15:
  .string "Reassigned name should be 'Language'"
.align 8
str_const_16:
  .string "Reassigned isActive should be false"
.align 8
str_const_17:
  .string "After reassignment:"
.align 8
str_const_18:
  .string "Integer: %s"
.align 8
str_const_19:
  .string "Float: %s"
.align 8
str_const_20:
  .string "String: %s"
.align 8
str_const_21:
  .string "Boolean: %s"
.align 8
str_const_22:
  .string "Variable a should be 1"
.align 8
str_const_23:
  .string "Variable b should be 2"
.align 8
str_const_24:
  .string "Variable c should be 3"
.align 8
str_const_25:
  .string "Multiple declarations: a=%s, b=%s, c=%s"
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
  sub rsp, 696
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
  movq $337, rax
  cmpq $337, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -96], rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $18, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq [rel str_const_7], rcx
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
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -216], rcx
  movq $2, rdx
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
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -256], rcx
  movq [rbp + -96], rdx
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
  movq [rel str_const_10], rcx
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
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq $801, rax
  cmpq $801, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -344]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -344], rcx
  movq [rbp + -352], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -360], rcx
  movq [rbp + -368], rdx
  call lm_assert
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -336], rax
  cmpq [rbp + -376], rax
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
  movq [rel str_const_17], rcx
  call lm_box_string
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
  movq $801, rdx
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
  movq $2, rdx
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
  movq [rbp + -528], rcx
  movq [rbp + -336], rdx
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
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -568]
  movq [rbp + -568], rcx
  movq $10, rdx
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
  movq $9, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -608]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -608], rcx
  movq [rbp + -616], rdx
  call lm_assert
  movq $17, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -624]
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -632]
  movq [rbp + -624], rcx
  movq [rbp + -632], rdx
  call lm_assert
  movq $25, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -640]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -648]
  movq [rbp + -640], rcx
  movq [rbp + -648], rdx
  call lm_assert
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -656]
  movq [rbp + -656], rcx
  movq $9, rdx
  call lm_rt_str_format
  movq rax, [rbp + -664]
  movq [rbp + -664], rcx
  movq $17, rdx
  call lm_rt_str_format
  movq rax, [rbp + -672]
  movq [rbp + -672], rcx
  movq $25, rdx
  call lm_rt_str_format
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

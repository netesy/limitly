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
  .string "=== Literal Value Tests ==="
.align 8
str_const_1:
  .string "Integers:"
.align 8
str_const_2:
  .string "Integer literal 0 should be 0"
.align 8
str_const_3:
  .string "Integer literal 42 should be 42"
.align 8
str_const_4:
  .string "Integer literal -17 should be -17"
.align 8
str_const_5:
  .string "Integer literal 999999 should be 999999"
.align 8
str_const_6:
  .string "Floats:"
.align 8
str_const_7:
  .string ""
.align 8
str_const_8:
  .string "Float literal 0.0 should be 0.0"
.align 8
str_const_9:
  .string "Float literal 3.14159 should be 3.14159"
.align 8
str_const_10:
  .string "Float literal -2.71828 should be -2.71828"
.align 8
str_const_11:
  .string "Float literal 1.23e-14 should be 1.23e-14"
.align 8
str_const_12:
  .string ""
.align 8
str_const_13:
  .string "Empty string should be empty"
.align 8
str_const_14:
  .string "Strings:"
.align 8
str_const_15:
  .string "Hello, World!"
.align 8
str_const_16:
  .string ""
.align 8
str_const_17:
  .string "Special chars: 
	\""
.align 8
str_const_18:
  .string "Hello, World!"
.align 8
str_const_19:
  .string "String literal should match"
.align 8
str_const_20:
  .string ""
.align 8
str_const_21:
  .string "Empty string should be empty"
.align 8
str_const_22:
  .string "Special chars: 
	\""
.align 8
str_const_23:
  .string "Special chars string should match"
.align 8
str_const_24:
  .string "Booleans:"
.align 8
str_const_25:
  .string "Boolean literal true should be true"
.align 8
str_const_26:
  .string "Boolean literal false should be false"
.align 8
str_const_27:
  .string "Nil:"
.align 8
str_const_28:
  .string "Nil literal should be nil"
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
  sub rsp, 664
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
  movq $137, rax
  negq rax
  movq rax, [rbp + -128]
  movq $1, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  movq $337, rax
  cmpq $337, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq $137, rax
  negq rax
  movq rax, [rbp + -168]
  movq [rbp + -128], rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq $7999993, rax
  cmpq $7999993, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq $1, rcx
  call lm_print_int
  movq $337, rcx
  call lm_print_int
  movq [rbp + -128], rcx
  call lm_print_int
  movq $7999993, rcx
  call lm_print_int
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  addq $16, rax
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  mov rax, [rax]
  movq rax, [rbp + -232]
  movq [rbp + -232], rcx
  call lm_print_str
  movq $2, rax
  negq rax
  movq rax, [rbp + -240]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -256], rcx
  movq [rbp + -264], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -272]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -272], rcx
  movq [rbp + -280], rdx
  call lm_assert
  movq $2, rax
  negq rax
  movq rax, [rbp + -288]
  movq [rbp + -240], rax
  cmpq [rbp + -288], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -296], rcx
  movq [rbp + -304], rdx
  call lm_assert
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -312]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -312], rcx
  movq [rbp + -320], rdx
  call lm_assert
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -248], rax
  cmpq [rbp + -328], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -336]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -336], rcx
  movq [rbp + -344], rdx
  call lm_assert
  movq $2, rcx
  call lm_print_int
  movq $2, rcx
  call lm_print_int
  movq [rbp + -240], rcx
  call lm_print_int
  movq $2, rcx
  call lm_print_int
  movq [rbp + -248], rax
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
  movq [rbp + -376], rax
  addq $16, rax
  movq rax, [rbp + -384]
  movq [rbp + -384], rax
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  mov rax, [rax]
  movq rax, [rbp + -400]
  movq [rbp + -400], rcx
  call lm_print_str
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rbp + -408], rax
  cmpq [rbp + -432], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -440]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -440], rcx
  movq [rbp + -448], rdx
  call lm_assert
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq [rbp + -416], rax
  cmpq [rbp + -456], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -464]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -464], rcx
  movq [rbp + -472], rdx
  call lm_assert
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq [rbp + -424], rax
  cmpq [rbp + -480], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -488]
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -488], rcx
  movq [rbp + -496], rdx
  call lm_assert
  movq [rbp + -408], rax
  addq $16, rax
  movq rax, [rbp + -504]
  movq [rbp + -504], rax
  movq rax, [rbp + -512]
  movq [rbp + -512], rax
  mov rax, [rax]
  movq rax, [rbp + -520]
  movq [rbp + -520], rcx
  call lm_print_str
  movq [rbp + -416], rax
  addq $16, rax
  movq rax, [rbp + -528]
  movq [rbp + -528], rax
  movq rax, [rbp + -536]
  movq [rbp + -536], rax
  mov rax, [rax]
  movq rax, [rbp + -544]
  movq [rbp + -544], rcx
  call lm_print_str
  movq [rbp + -424], rax
  addq $16, rax
  movq rax, [rbp + -552]
  movq [rbp + -552], rax
  movq rax, [rbp + -560]
  movq [rbp + -560], rax
  mov rax, [rax]
  movq rax, [rbp + -568]
  movq [rbp + -568], rcx
  call lm_print_str
  movq [rel str_const_24], rcx
  call lm_box_string
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
  movq $18, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -608]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -608], rcx
  movq [rbp + -616], rdx
  call lm_assert
  movq $10, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -624]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -632]
  movq [rbp + -624], rcx
  movq [rbp + -632], rdx
  call lm_assert
  movq $18, rcx
  call lm_print_int
  movq $10, rcx
  call lm_print_int
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  addq $16, rax
  movq rax, [rbp + -648]
  movq [rbp + -648], rax
  movq rax, [rbp + -656]
  movq [rbp + -656], rax
  mov rax, [rax]
  movq rax, [rbp + -664]
  movq [rbp + -664], rcx
  call lm_print_str
  movq $2, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -672]
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -680]
  movq [rbp + -672], rcx
  movq [rbp + -680], rdx
  call lm_assert
  movq $2, rcx
  call lm_print_int
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

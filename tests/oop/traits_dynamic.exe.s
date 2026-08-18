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
  .string "Circle"
.align 8
str_const_1:
  .string "Trait method should work for Circle"
.align 8
str_const_2:
  .string "Circle area should be 3*5*5 = 75"
.align 8
str_const_3:
  .string "Square"
.align 8
str_const_4:
  .string "Trait method should work for Square"
.align 8
str_const_5:
  .string "Square area should be 10*10 = 100"
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
  sub rsp, 152
main_entry:
main_block_0:
  call main
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rax
  addq $0, rax
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rbp + -64], rcx
  call print_shape_info
  movq [rbp + -80], rcx
  call print_shape_info
  movq [rbp + -64], rcx
  call Circle.name
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r8, rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq [rbp + -64], rcx
  call Circle.area
  movq $r13, rax
  cmpq $601, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq [rbp + -80], rcx
  call Square.name
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r18, rax
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
  movq [rbp + -80], rcx
  call Square.area
  movq $r23, rax
  cmpq $801, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
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

.globl print_shape_info
print_shape_info:
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
print_shape_info_entry:
print_shape_info_block_0:
  movq $0, rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  movq $0, rcx
  call lm_print_int
  movq $0, rax
  jmp print_shape_info_epilogue
print_shape_info_epilogue:
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
.Lfunc_end_print_shape_info:

.globl Square.area
Square.area:
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
Square.area_entry:
  movq $0, rax
  jmp Square.area_epilogue
Square.area_epilogue:
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
.Lfunc_end_Square.area:

.globl Circle.name
Circle.name:
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
Circle.name_entry:
  movq $0, rax
  jmp Circle.name_epilogue
Circle.name_epilogue:
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
.Lfunc_end_Circle.name:

.globl Circle.area
Circle.area:
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
Circle.area_entry:
  movq $0, rax
  jmp Circle.area_epilogue
Circle.area_epilogue:
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
.Lfunc_end_Circle.area:

.globl Square.name
Square.name:
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
Square.name_entry:
  movq $0, rax
  jmp Square.name_epilogue
Square.name_epilogue:
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
.Lfunc_end_Square.name:

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

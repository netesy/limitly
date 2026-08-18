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
  .string "a"
.align 8
str_const_1:
  .string "b"
.align 8
str_const_2:
  .string "Collection literals: OK"
.align 8
str_const_3:
  .string "a"
.align 8
str_const_4:
  .string "b"
.align 8
str_const_5:
  .string "hello"
.align 8
str_const_6:
  .string "Collection type annotations: OK"
.align 8
str_const_7:
  .string "primary"
.align 8
str_const_8:
  .string "secondary"
.align 8
str_const_9:
  .string "Enum compatibility with collections: OK"
.align 8
str_const_10:
  .string "list/dict/array as identifiers: OK"
.align 8
str_const_11:
  .string "list = "
.align 8
str_const_12:
  .string "dict = "
.align 8
str_const_13:
  .string "array = "
.align 8
str_const_14:
  .string "Generic syntax correctly unsupported: OK"
.align 8
str_const_15:
  .string "All ownership refactor tests passed!"
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
  sub rsp, 392
main_entry:
main_block_0:
  movq $0, rcx
  call lm_list_new
  movq $r0, rcx
  movq $9, rdx
  call lm_list_append
  movq $r0, rcx
  movq $17, rdx
  call lm_list_append
  movq $r0, rcx
  movq $25, rdx
  call lm_list_append
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rel str_const_2], rcx
  call lm_box_string
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
  movq $0, rcx
  call lm_list_new
  movq $r22, rcx
  movq $9, rdx
  call lm_list_append
  movq $r22, rcx
  movq $17, rdx
  call lm_list_append
  movq $r22, rcx
  movq $25, rdx
  call lm_list_append
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rel str_const_6], rcx
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
  movq $0, rcx
  call lm_list_new
  movq $r44, rcx
  movq $0, rdx
  call lm_list_append
  movq $r44, rcx
  movq $0, rdx
  call lm_list_append
  movq $r44, rcx
  movq $0, rdx
  call lm_list_append
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rel str_const_9], rcx
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
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  addq $16, rax
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  mov rax, [rax]
  movq rax, [rbp + -240]
  movq [rbp + -240], rcx
  call lm_print_str
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  addq $16, rax
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  mov rax, [rax]
  movq rax, [rbp + -272]
  movq [rbp + -272], rcx
  movq $41, rdx
  call lm_print_str
  movq [rel str_const_12], rcx
  call lm_box_string
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
  movq $81, rdx
  call lm_print_str
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -312], rax
  addq $16, rax
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  mov rax, [rax]
  movq rax, [rbp + -336]
  movq [rbp + -336], rcx
  movq $121, rdx
  call lm_print_str
  movq [rel str_const_14], rcx
  call lm_box_string
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
  movq [rel str_const_15], rcx
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

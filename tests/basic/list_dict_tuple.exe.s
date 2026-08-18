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
  .string "=== List, Dict, Tuple Tests ==="
.align 8
str_const_1:
  .string "Apple"
.align 8
str_const_2:
  .string "Banana"
.align 8
str_const_3:
  .string "Cherrys"
.align 8
str_const_4:
  .string "Apple"
.align 8
str_const_5:
  .string "First fruit should be Apple"
.align 8
str_const_6:
  .string "Banana"
.align 8
str_const_7:
  .string "Second fruit should be Banana"
.align 8
str_const_8:
  .string "Cherrys"
.align 8
str_const_9:
  .string "Third fruit should be Cherrys"
.align 8
str_const_10:
  .string "Loop should iterate 3 times"
.align 8
str_const_11:
  .string "Apples"
.align 8
str_const_12:
  .string "Bananas"
.align 8
str_const_13:
  .string "Cherries"
.align 8
str_const_14:
  .string "Apples"
.align 8
str_const_15:
  .string "First tuple element should be Apples"
.align 8
str_const_16:
  .string "Bananas"
.align 8
str_const_17:
  .string "Second tuple element should be Bananas"
.align 8
str_const_18:
  .string "Cherries"
.align 8
str_const_19:
  .string "Third tuple element should be Cherries"
.align 8
str_const_20:
  .string "at"
.align 8
str_const_21:
  .string "bi"
.align 8
str_const_22:
  .string "ce"
.align 8
str_const_23:
  .string "de"
.align 8
str_const_24:
  .string "at"
.align 8
str_const_25:
  .string "Key 'at' should map to 1"
.align 8
str_const_26:
  .string "bi"
.align 8
str_const_27:
  .string "Key 'bi' should map to 12"
.align 8
str_const_28:
  .string "ce"
.align 8
str_const_29:
  .string "Key 'ce' should map to 78"
.align 8
str_const_30:
  .string "de"
.align 8
str_const_31:
  .string "Key 'de' should map to 28"
.align 8
str_const_32:
  .string "%s: %s"
.align 8
str_const_33:
  .string "Dictionary loop should iterate 4 times"
.align 8
str_const_34:
  .string "=== List, Dict, Tuple Tests Complete ==="
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
  sub rsp, 648
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
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r2, rcx
  movq [rbp + -96], rdx
  call lm_list_append
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r2, rcx
  movq [rbp + -104], rdx
  call lm_list_append
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r2, rcx
  movq [rbp + -112], rdx
  call lm_list_append
  movq $r2, rcx
  movq $1, rdx
  call lm_list_get
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq $r11, rax
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
  movq $r2, rcx
  movq $9, rdx
  call lm_list_get
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq $r17, rax
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
  movq $r2, rcx
  movq $17, rdx
  call lm_list_get
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq $r23, rax
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
  jmp main_block_31
main_block_31:
  movq $r2, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r31, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  testq rax, rax
  jne main_block_34
  jmp main_block_43
main_block_34:
  jmp main_block_34
  movq $r2, rcx
  movq $1, rdx
  call lm_list_get
  movq $r33, rax
  addq $16, rax
  movq rax, $
  movq $, rax
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  mov rax, [rax]
  movq rax, [rbp + -208]
  movq [rbp + -208], rcx
  call lm_print_str
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -216]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -224]
  jmp main_block_31
main_block_43:
  movq [rbp + -216], rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rcx
  movq [rbp + -240], rdx
  call lm_assert
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq $0, rax
  cmpq [rbp + -272], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -280]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -280], rcx
  movq [rbp + -288], rdx
  call lm_assert
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq $0, rax
  cmpq [rbp + -296], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -304]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -304], rcx
  movq [rbp + -312], rdx
  call lm_assert
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq $0, rax
  cmpq [rbp + -320], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -328]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -328], rcx
  movq [rbp + -336], rdx
  call lm_assert
  movq $0, rax
  addq $16, rax
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  mov rax, [rax]
  movq rax, [rbp + -360]
  movq [rbp + -360], rcx
  call lm_print_str
  movq $0, rax
  addq $16, rax
  movq rax, [rbp + -368]
  movq [rbp + -368], rax
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  mov rax, [rax]
  movq rax, [rbp + -384]
  movq [rbp + -384], rcx
  call lm_print_str
  movq $0, rax
  addq $16, rax
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  mov rax, [rax]
  movq rax, [rbp + -408]
  movq [rbp + -408], rcx
  call lm_print_str
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -456]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq [rbp + -456], rcx
  movq [rbp + -464], rdx
  call lm_assert
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq $0, rax
  cmpq $97, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -480]
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -488]
  movq [rbp + -480], rcx
  movq [rbp + -488], rdx
  call lm_assert
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq $0, rax
  cmpq $625, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -504]
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -512]
  movq [rbp + -504], rcx
  movq [rbp + -512], rdx
  call lm_assert
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq $0, rax
  cmpq $225, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -528]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -536]
  movq [rbp + -528], rcx
  movq [rbp + -536], rdx
  call lm_assert
  jmp main_block_127
main_block_127:
  movq $0, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r116, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -544]
  movq [rbp + -544], rax
  testq rax, rax
  jne main_block_130
  jmp main_block_146
main_block_130:
  jmp main_block_130
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -552]
  movq [rbp + -552], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -560]
  movq [rbp + -560], rcx
  movq $0, rdx
  call lm_rt_str_format
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
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -600]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -608]
  jmp main_block_127
main_block_146:
  movq [rbp + -600], rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -616]
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rbp + -616], rcx
  movq [rbp + -624], rdx
  call lm_assert
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -632]
  movq [rbp + -632], rax
  addq $16, rax
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  movq rax, [rbp + -648]
  movq [rbp + -648], rax
  mov rax, [rax]
  movq rax, [rbp + -656]
  movq [rbp + -656], rcx
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

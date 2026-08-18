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
  .string "=== Parallel Block Tests ==="
.align 8
str_const_1:
  .string "Parallel processing complete"
.align 8
str_const_2:
  .string "Counter: %s"
.align 8
str_const_3:
  .string "Results collected: %s"
.align 8
str_const_4:
  .string "First result: %s"
.align 8
str_const_5:
  .string "Last result: %s"
.align 8
str_const_6:
  .string "Parallel block should execute range 0..99 iterations"
.align 8
str_const_7:
  .string "All range results should be collected"
.align 8
str_const_8:
  .string "First result should be 0*2 = 0"
.align 8
str_const_9:
  .string "Last result should be 98*2 = 196"
.align 8
str_const_10:
  .string "Second parallel block complete"
.align 8
str_const_11:
  .string "Tasks executed: %s"
.align 8
str_const_12:
  .string "Sum of results: %s"
.align 8
str_const_13:
  .string "Second parallel block should execute range 0..199 iterations"
.align 8
str_const_14:
  .string "Sum should be sum of i*3 for i=0..198 = 59103"
.align 8
str_const_15:
  .string "Third parallel block complete"
.align 8
str_const_16:
  .string "  Result: %s"
.align 8
str_const_17:
  .string "Third parallel block should execute range 0..9 iterations"
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
  sub rsp, 712
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
  call channel
  jmp main_block_9
main_block_9:
  movq $1, rax
  cmpq $793, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne main_block_12
  jmp main_block_24
main_block_12:
  jmp main_block_12
  movq $1, rax
  imulq $17, rax
  movq rax, [rbp + -104]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp main_block_20
main_block_20:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -120]
  jmp main_block_9
main_block_24:
  movq [rel str_const_1], rcx
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
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rcx
  movq [rbp + -112], rdx
  call lm_rt_str_format
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
  jmp main_block_34
main_block_34:
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  testq rax, rax
  jne main_block_50
  jmp main_block_38
main_block_38:
  jmp main_block_38
  movq $1, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  testq rax, rax
  jne main_block_42
  jmp main_block_44
main_block_42:
  jmp main_block_42
  jmp main_block_44
main_block_44:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -216]
  jmp main_block_34
main_block_50:
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -224], rcx
  movq [rbp + -216], rdx
  call lm_rt_str_format
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  addq $16, rax
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  mov rax, [rax]
  movq rax, [rbp + -256]
  movq [rbp + -256], rcx
  call lm_print_str
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -264], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  addq $16, rax
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  movq rax, [rbp + -288]
  movq [rbp + -288], rax
  mov rax, [rax]
  movq rax, [rbp + -296]
  movq [rbp + -296], rcx
  call lm_print_str
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -304], rcx
  movq $0, rdx
  call lm_rt_str_format
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
  call lm_print_str
  movq [rbp + -112], rax
  cmpq $793, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -344]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -344], rcx
  movq [rbp + -352], rdx
  call lm_assert
  movq [rbp + -216], rax
  cmpq $793, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -360], rcx
  movq [rbp + -368], rdx
  call lm_assert
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -376]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -376], rcx
  movq [rbp + -384], rdx
  call lm_assert
  movq $0, rax
  cmpq $1569, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -392], rcx
  movq [rbp + -400], rdx
  call lm_assert
  call channel
  jmp main_block_82
main_block_82:
  movq $1, rax
  cmpq $1593, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -408]
  movq [rbp + -408], rax
  testq rax, rax
  jne main_block_85
  jmp main_block_97
main_block_85:
  jmp main_block_85
  movq $1, rax
  imulq $25, rax
  movq rax, [rbp + -416]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -424]
  jmp main_block_93
main_block_93:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -432]
  jmp main_block_82
main_block_97:
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  addq $16, rax
  movq rax, [rbp + -448]
  movq [rbp + -448], rax
  movq rax, [rbp + -456]
  movq [rbp + -456], rax
  mov rax, [rax]
  movq rax, [rbp + -464]
  movq [rbp + -464], rcx
  call lm_print_str
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -472], rcx
  movq [rbp + -424], rdx
  call lm_rt_str_format
  movq rax, [rbp + -480]
  movq [rbp + -480], rax
  addq $16, rax
  movq rax, [rbp + -488]
  movq [rbp + -488], rax
  movq rax, [rbp + -496]
  movq [rbp + -496], rax
  mov rax, [rax]
  movq rax, [rbp + -504]
  movq [rbp + -504], rcx
  call lm_print_str
  jmp main_block_105
main_block_105:
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -512]
  movq [rbp + -512], rax
  testq rax, rax
  jne main_block_113
  jmp main_block_109
main_block_109:
  jmp main_block_109
  movq $1, rax
  addq $0, rax
  movq rax, [rbp + -520]
  jmp main_block_105
main_block_113:
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -528], rcx
  movq [rbp + -520], rdx
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
  movq [rbp + -424], rax
  cmpq $1593, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -568]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -568], rcx
  movq [rbp + -576], rdx
  call lm_assert
  movq [rbp + -520], rax
  cmpq $472825, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -584]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -592]
  movq [rbp + -584], rcx
  movq [rbp + -592], rdx
  call lm_assert
  call channel
  jmp main_block_130
main_block_130:
  movq $1, rax
  cmpq $73, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -600]
  movq [rbp + -600], rax
  testq rax, rax
  jne main_block_133
  jmp main_block_141
main_block_133:
  jmp main_block_133
  movq $1, rax
  imulq $81, rax
  movq rax, [rbp + -608]
  jmp main_block_137
main_block_137:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -616]
  jmp main_block_130
main_block_141:
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rbp + -624], rax
  addq $16, rax
  movq rax, [rbp + -632]
  movq [rbp + -632], rax
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  mov rax, [rax]
  movq rax, [rbp + -648]
  movq [rbp + -648], rcx
  call lm_print_str
  jmp main_block_146
main_block_146:
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -656]
  movq [rbp + -656], rax
  testq rax, rax
  jne main_block_159
  jmp main_block_150
main_block_150:
  jmp main_block_150
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -664]
  movq [rbp + -664], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -672]
  movq [rbp + -672], rax
  addq $16, rax
  movq rax, [rbp + -680]
  movq [rbp + -680], rax
  movq rax, [rbp + -688]
  movq [rbp + -688], rax
  mov rax, [rax]
  movq rax, [rbp + -696]
  movq [rbp + -696], rcx
  call lm_print_str
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -704]
  jmp main_block_146
main_block_159:
  movq [rbp + -704], rax
  cmpq $73, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -712]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -720]
  movq [rbp + -712], rcx
  movq [rbp + -720], rdx
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

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
  .string "=== Random Module Test Suite ==="
.align 8
str_const_1:
  .string "Random frame test failed"
.align 8
str_const_2:
  .string "Distributions test failed"
.align 8
str_const_3:
  .string "Random helpers test failed"
.align 8
str_const_4:
  .string "All random tests passed successfully."
.align 8
str_const_5:
  .string "Testing Random Frame..."
.align 8
str_const_6:
  .string "next_int failed"
.align 8
str_const_7:
  .string "next_float failed"
.align 8
str_const_8:
  .string "next_bool failed"
.align 8
str_const_9:
  .string "range_int failed"
.align 8
str_const_10:
  .string "range_float failed"
.align 8
str_const_11:
  .string "next_bytes failed"
.align 8
str_const_12:
  .string "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
.align 8
str_const_13:
  .string "next_string failed"
.align 8
str_const_14:
  .string "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
.align 8
str_const_15:
  .string "Testing Distributions..."
.align 8
str_const_16:
  .string "Uniform sample failed"
.align 8
str_const_17:
  .string "Testing Random Helpers..."
.align 8
str_const_18:
  .string "random_int helper failed"
.align 8
str_const_19:
  .string "random_float helper failed"
.align 8
str_const_20:
  .string "random_bool helper failed"
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
  call std.random.index.__init__
  call main
  movq $0, rax
  jmp main_epilogue
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
  call test_random_frame
  movq $r2, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_distributions
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  call test_random_helpers
  movq $r12, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  addq $16, rax
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  mov rax, [rax]
  movq rax, [rbp + -168]
  movq [rbp + -168], rcx
  call lm_print_str
  movq $1, rax
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

.globl std.random.index.__init__
std.random.index.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.random.index.__init___entry:
  movq $0, rax
  jmp std.random.index.__init___epilogue
std.random.index.__init___epilogue:
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
.Lfunc_end_std.random.index.__init__:

.globl std.random.index.random_string
std.random.index.random_string:
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
std.random.index.random_string_entry:
std.random.index.random_string_block_0:
  movq [rbp + -64], rcx
  call std.random.random.random_string
  movq $r1, rax
  jmp std.random.index.random_string_epilogue
std.random.index.random_string_epilogue:
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
.Lfunc_end_std.random.index.random_string:

.globl std.random.index.random_int
std.random.index.random_int:
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
  mov [rbp + -72], rdx
std.random.index.random_int_entry:
std.random.index.random_int_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.random.random.random_int
  movq $r2, rax
  jmp std.random.index.random_int_epilogue
std.random.index.random_int_epilogue:
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
.Lfunc_end_std.random.index.random_int:

.globl std.random.index.Random
std.random.index.Random:
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
std.random.index.Random_entry:
std.random.index.Random_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.random.random.Random.init
  movq [rbp + -72], rax
  jmp std.random.index.Random_epilogue
std.random.index.Random_epilogue:
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
.Lfunc_end_std.random.index.Random:

.globl std.random.distributions.__init__
std.random.distributions.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.random.distributions.__init___entry:
  movq $0, rax
  jmp std.random.distributions.__init___epilogue
std.random.distributions.__init___epilogue:
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
.Lfunc_end_std.random.distributions.__init__:

.globl std.random.distributions.Uniform.init
std.random.distributions.Uniform.init:
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
  mov [rbp + -80], r8
std.random.distributions.Uniform.init_entry:
  movq $0, rax
  jmp std.random.distributions.Uniform.init_epilogue
std.random.distributions.Uniform.init_epilogue:
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
.Lfunc_end_std.random.distributions.Uniform.init:

.globl std.random.random.__init__
std.random.random.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.random.random.__init___entry:
  movq $0, rax
  jmp std.random.random.__init___epilogue
std.random.random.__init___epilogue:
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
.Lfunc_end_std.random.random.__init__:

.globl std.random.random.random_bool
std.random.random.random_bool:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.random.random.random_bool_entry:
std.random.random.random_bool_block_0:
  movq $0, rcx
  call std.random.random.Random.next_bool
  movq $r1, rax
  jmp std.random.random.random_bool_epilogue
std.random.random.random_bool_epilogue:
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
.Lfunc_end_std.random.random.random_bool:

.globl std.random.random.random_float
std.random.random.random_float:
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
  mov [rbp + -72], rdx
std.random.random.random_float_entry:
std.random.random.random_float_block_0:
  movq $0, rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.random.random.Random.range_float
  movq $r3, rax
  jmp std.random.random.random_float_epilogue
std.random.random.random_float_epilogue:
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
.Lfunc_end_std.random.random.random_float:

.globl std.random.random.SecureRandom.next_bytes
std.random.random.SecureRandom.next_bytes:
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
  mov [rbp + -72], rdx
std.random.random.SecureRandom.next_bytes_entry:
  movq $0, rax
  jmp std.random.random.SecureRandom.next_bytes_epilogue
std.random.random.SecureRandom.next_bytes_epilogue:
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
.Lfunc_end_std.random.random.SecureRandom.next_bytes:

.globl std.random.random.SecureRandom.next_float
std.random.random.SecureRandom.next_float:
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
std.random.random.SecureRandom.next_float_entry:
  movq $0, rax
  jmp std.random.random.SecureRandom.next_float_epilogue
std.random.random.SecureRandom.next_float_epilogue:
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
.Lfunc_end_std.random.random.SecureRandom.next_float:

.globl std.random.random.SecureRandom.next_int
std.random.random.SecureRandom.next_int:
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
std.random.random.SecureRandom.next_int_entry:
  movq $0, rax
  jmp std.random.random.SecureRandom.next_int_epilogue
std.random.random.SecureRandom.next_int_epilogue:
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
.Lfunc_end_std.random.random.SecureRandom.next_int:

.globl std.random.distributions.Uniform.sample
std.random.distributions.Uniform.sample:
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
  mov [rbp + -72], rdx
std.random.distributions.Uniform.sample_entry:
  movq $0, rax
  jmp std.random.distributions.Uniform.sample_epilogue
std.random.distributions.Uniform.sample_epilogue:
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
.Lfunc_end_std.random.distributions.Uniform.sample:

.globl std.random.random.Random.init
std.random.random.Random.init:
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
  mov [rbp + -72], rdx
std.random.random.Random.init_entry:
  movq $0, rax
  jmp std.random.random.Random.init_epilogue
std.random.random.Random.init_epilogue:
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
.Lfunc_end_std.random.random.Random.init:

.globl std.random.random.Random.next_string
std.random.random.Random.next_string:
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
  mov [rbp + -80], r8
std.random.random.Random.next_string_entry:
  movq $0, rax
  jmp std.random.random.Random.next_string_epilogue
std.random.random.Random.next_string_epilogue:
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
.Lfunc_end_std.random.random.Random.next_string:

.globl std.random.random.Random.next_bytes
std.random.random.Random.next_bytes:
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
  mov [rbp + -72], rdx
std.random.random.Random.next_bytes_entry:
  movq $0, rax
  jmp std.random.random.Random.next_bytes_epilogue
std.random.random.Random.next_bytes_epilogue:
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
.Lfunc_end_std.random.random.Random.next_bytes:

.globl std.random.random.Random.range_int
std.random.random.Random.range_int:
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
  mov [rbp + -80], r8
std.random.random.Random.range_int_entry:
  movq $0, rax
  jmp std.random.random.Random.range_int_epilogue
std.random.random.Random.range_int_epilogue:
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
.Lfunc_end_std.random.random.Random.range_int:

.globl std.random.index.Uniform
std.random.index.Uniform:
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
std.random.index.Uniform_entry:
std.random.index.Uniform_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.random.distributions.Uniform.init
  movq [rbp + -80], rax
  jmp std.random.index.Uniform_epilogue
std.random.index.Uniform_epilogue:
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
.Lfunc_end_std.random.index.Uniform:

.globl std.resource.Resource._handle
std.resource.Resource._handle:
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
std.resource.Resource._handle_entry:
  movq $0, rax
  jmp std.resource.Resource._handle_epilogue
std.resource.Resource._handle_epilogue:
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
.Lfunc_end_std.resource.Resource._handle:

.globl test_random_frame
test_random_frame:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 232
test_random_frame_entry:
test_random_frame_block_0:
  movq [rel str_const_5], rcx
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
  movq $987654313, rcx
  call std.random.index.Random
  movq $r3, rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.random.random.Random.next_int
  movq $r6, rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.random.random.Random.next_float
  movq $r12, rax
  cmpq $2, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne test_random_frame_block_18
  jmp test_random_frame_block_22
test_random_frame_block_18:
  jmp test_random_frame_block_18
  movq $r12, rax
  cmpq $2, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -128]
  jmp test_random_frame_block_22
test_random_frame_block_22:
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.random.random.Random.next_bool
  movq $r21, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  testq rax, rax
  jne test_random_frame_block_34
  jmp test_random_frame_block_30
test_random_frame_block_30:
  jmp test_random_frame_block_30
  movq $r21, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  jmp test_random_frame_block_34
test_random_frame_block_34:
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq [rbp + -96], rcx
  movq $9, rdx
  movq $81, r8
  call std.random.random.Random.range_int
  movq $r32, rax
  cmpq $9, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  testq rax, rax
  jne test_random_frame_block_44
  jmp test_random_frame_block_48
test_random_frame_block_44:
  jmp test_random_frame_block_44
  movq $r32, rax
  cmpq $81, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -176]
  jmp test_random_frame_block_48
test_random_frame_block_48:
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq [rbp + -96], rcx
  movq $2, rdx
  movq $2, r8
  call std.random.random.Random.range_float
  movq $r43, rax
  cmpq $2, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  testq rax, rax
  jne test_random_frame_block_58
  jmp test_random_frame_block_62
test_random_frame_block_58:
  jmp test_random_frame_block_58
  movq $r43, rax
  cmpq $2, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -200]
  jmp test_random_frame_block_62
test_random_frame_block_62:
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -200], rcx
  movq [rbp + -208], rdx
  call lm_assert
  movq [rbp + -96], rcx
  movq $41, rdx
  call std.random.random.Random.next_bytes
  movq $r53, rcx
  call lm_list_len
  movq $r55, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -216]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -216], rcx
  movq [rbp + -224], rdx
  call lm_assert
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -96], rcx
  movq $41, rdx
  movq [rbp + -232], r8
  call std.random.random.Random.next_string
  movq $r62, rcx
  call lm_list_len
  movq $r64, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq $9, rax
  jmp test_random_frame_epilogue
test_random_frame_epilogue:
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
.Lfunc_end_test_random_frame:

.globl std.resource.Connector.connect
std.resource.Connector.connect:
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
  mov [rbp + -72], rdx
std.resource.Connector.connect_entry:
  movq $0, rax
  jmp std.resource.Connector.connect_epilogue
std.resource.Connector.connect_epilogue:
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
.Lfunc_end_std.resource.Connector.connect:

.globl std.resource.Accepter.accept
std.resource.Accepter.accept:
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
std.resource.Accepter.accept_entry:
  movq $0, rax
  jmp std.resource.Accepter.accept_epilogue
std.resource.Accepter.accept_epilogue:
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
.Lfunc_end_std.resource.Accepter.accept:

.globl std.random.index.SecureRandom
std.random.index.SecureRandom:
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
std.random.index.SecureRandom_entry:
std.random.index.SecureRandom_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.random.random.SecureRandom.init
  movq $0, rax
  jmp std.random.index.SecureRandom_epilogue
std.random.index.SecureRandom_epilogue:
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
.Lfunc_end_std.random.index.SecureRandom:

.globl std.resource.Resource.close
std.resource.Resource.close:
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
std.resource.Resource.close_entry:
  movq $0, rax
  jmp std.resource.Resource.close_epilogue
std.resource.Resource.close_epilogue:
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
.Lfunc_end_std.resource.Resource.close:

.globl std.random.index.random_float
std.random.index.random_float:
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
  mov [rbp + -72], rdx
std.random.index.random_float_entry:
std.random.index.random_float_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.random.random.random_float
  movq $r2, rax
  jmp std.random.index.random_float_epilogue
std.random.index.random_float_epilogue:
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
.Lfunc_end_std.random.index.random_float:

.globl std.resource.ResourceWriter.write
std.resource.ResourceWriter.write:
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
  mov [rbp + -72], rdx
std.resource.ResourceWriter.write_entry:
  movq $0, rax
  jmp std.resource.ResourceWriter.write_epilogue
std.resource.ResourceWriter.write_epilogue:
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
.Lfunc_end_std.resource.ResourceWriter.write:

.globl std.resource.create
std.resource.create:
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
std.resource.create_entry:
std.resource.create_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -80]
  movq $r2, rax
  cmpq [rbp + -80], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.resource.create_block_6
  jmp std.resource.create_block_8
std.resource.create_block_6:
  jmp std.resource.create_block_6
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp std.resource.create_epilogue
std.resource.create_block_8:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -104], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -104], rcx
  movq $r2, rdx
  movq [rbp + -64], r8
  call std.resource.Resource.init
  movq [rbp + -104], rax
  jmp std.resource.create_epilogue
std.resource.create_epilogue:
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
.Lfunc_end_std.resource.create:

.globl std.random.random.Random.range_float
std.random.random.Random.range_float:
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
  mov [rbp + -80], r8
std.random.random.Random.range_float_entry:
  movq $0, rax
  jmp std.random.random.Random.range_float_epilogue
std.random.random.Random.range_float_epilogue:
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
.Lfunc_end_std.random.random.Random.range_float:

.globl std.random.random.random_string
std.random.random.random_string:
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
std.random.random.random_string_entry:
std.random.random.random_string_block_0:
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $0, rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.random.random.Random.next_string
  movq $r3, rax
  jmp std.random.random.random_string_epilogue
std.random.random.random_string_epilogue:
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
.Lfunc_end_std.random.random.random_string:

.globl std.resource.create_socket
std.resource.create_socket:
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
std.resource.create_socket_entry:
std.resource.create_socket_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_socket_block_8
  jmp std.resource.create_socket_block_10
std.resource.create_socket_block_8:
  jmp std.resource.create_socket_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_socket_epilogue
std.resource.create_socket_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_socket_epilogue
std.resource.create_socket_epilogue:
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
.Lfunc_end_std.resource.create_socket:

.globl std.resource.Resource.init
std.resource.Resource.init:
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
  mov [rbp + -80], r8
std.resource.Resource.init_entry:
  movq $0, rax
  jmp std.resource.Resource.init_epilogue
std.resource.Resource.init_epilogue:
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
.Lfunc_end_std.resource.Resource.init:

.globl std.random.random.SecureRandom.init
std.random.random.SecureRandom.init:
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
std.random.random.SecureRandom.init_entry:
  movq $0, rax
  jmp std.random.random.SecureRandom.init_epilogue
std.random.random.SecureRandom.init_epilogue:
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
.Lfunc_end_std.random.random.SecureRandom.init:

.globl std.internal.runtime.call
std.internal.runtime.call:
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
  mov [rbp + -80], r8
std.internal.runtime.call_entry:
std.internal.runtime.call_block_0:
  movq $0, rax
  jmp std.internal.runtime.call_epilogue
std.internal.runtime.call_epilogue:
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
.Lfunc_end_std.internal.runtime.call:

.globl std.resource.create_udp_socket
std.resource.create_udp_socket:
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
std.resource.create_udp_socket_entry:
std.resource.create_udp_socket_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_udp_socket_block_8
  jmp std.resource.create_udp_socket_block_10
std.resource.create_udp_socket_block_8:
  jmp std.resource.create_udp_socket_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_udp_socket_epilogue
std.resource.create_udp_socket_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_udp_socket_epilogue
std.resource.create_udp_socket_epilogue:
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
.Lfunc_end_std.resource.create_udp_socket:

.globl std.random.random.random_bytes
std.random.random.random_bytes:
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
std.random.random.random_bytes_entry:
std.random.random.random_bytes_block_0:
  movq $0, rcx
  movq [rbp + -64], rdx
  call std.random.random.Random.next_bytes
  movq $r2, rax
  jmp std.random.random.random_bytes_epilogue
std.random.random.random_bytes_epilogue:
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
.Lfunc_end_std.random.random.random_bytes:

.globl std.internal.runtime.create
std.internal.runtime.create:
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
  mov [rbp + -72], rdx
std.internal.runtime.create_entry:
std.internal.runtime.create_block_0:
  movq $0, rax
  jmp std.internal.runtime.create_epilogue
std.internal.runtime.create_epilogue:
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
.Lfunc_end_std.internal.runtime.create:

.globl std.resource.Pollable.init
std.resource.Pollable.init:
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
  mov [rbp + -72], rdx
std.resource.Pollable.init_entry:
  movq $0, rax
  jmp std.resource.Pollable.init_epilogue
std.resource.Pollable.init_epilogue:
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
.Lfunc_end_std.resource.Pollable.init:

.globl std.resource.Poller.poll
std.resource.Poller.poll:
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
std.resource.Poller.poll_entry:
  movq $0, rax
  jmp std.resource.Poller.poll_epilogue
std.resource.Poller.poll_epilogue:
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
.Lfunc_end_std.resource.Poller.poll:

.globl std.random.index.random_bool
std.random.index.random_bool:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.random.index.random_bool_entry:
std.random.index.random_bool_block_0:
  call std.random.random.random_bool
  movq $0, rax
  jmp std.random.index.random_bool_epilogue
std.random.index.random_bool_epilogue:
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
.Lfunc_end_std.random.index.random_bool:

.globl std.random.random.Random.next_bool
std.random.random.Random.next_bool:
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
std.random.random.Random.next_bool_entry:
  movq $0, rax
  jmp std.random.random.Random.next_bool_epilogue
std.random.random.Random.next_bool_epilogue:
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
.Lfunc_end_std.random.random.Random.next_bool:

.globl std.resource.Resource.is_open
std.resource.Resource.is_open:
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
std.resource.Resource.is_open_entry:
  movq $0, rax
  jmp std.resource.Resource.is_open_epilogue
std.resource.Resource.is_open_epilogue:
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
.Lfunc_end_std.resource.Resource.is_open:

.globl std.internal.runtime.__init__
std.internal.runtime.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.internal.runtime.__init___entry:
  movq $0, rax
  jmp std.internal.runtime.__init___epilogue
std.internal.runtime.__init___epilogue:
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
.Lfunc_end_std.internal.runtime.__init__:

.globl std.resource.ResourceReader.init
std.resource.ResourceReader.init:
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
  mov [rbp + -72], rdx
std.resource.ResourceReader.init_entry:
  movq $0, rax
  jmp std.resource.ResourceReader.init_epilogue
std.resource.ResourceReader.init_epilogue:
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
.Lfunc_end_std.resource.ResourceReader.init:

.globl std.internal.runtime.destroy
std.internal.runtime.destroy:
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
std.internal.runtime.destroy_entry:
std.internal.runtime.destroy_block_0:
  movq $0, rax
  jmp std.internal.runtime.destroy_epilogue
std.internal.runtime.destroy_epilogue:
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
.Lfunc_end_std.internal.runtime.destroy:

.globl std.resource.ResourceWriter.init
std.resource.ResourceWriter.init:
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
  mov [rbp + -72], rdx
std.resource.ResourceWriter.init_entry:
  movq $0, rax
  jmp std.resource.ResourceWriter.init_epilogue
std.resource.ResourceWriter.init_epilogue:
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
.Lfunc_end_std.resource.ResourceWriter.init:

.globl std.resource.Pollable.poll
std.resource.Pollable.poll:
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
std.resource.Pollable.poll_entry:
  movq $0, rax
  jmp std.resource.Pollable.poll_epilogue
std.resource.Pollable.poll_epilogue:
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
.Lfunc_end_std.resource.Pollable.poll:

.globl std.resource.Poller.init
std.resource.Poller.init:
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
  mov [rbp + -72], rdx
std.resource.Poller.init_entry:
  movq $0, rax
  jmp std.resource.Poller.init_epilogue
std.resource.Poller.init_epilogue:
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
.Lfunc_end_std.resource.Poller.init:

.globl std.resource.Connector.init
std.resource.Connector.init:
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
  mov [rbp + -72], rdx
std.resource.Connector.init_entry:
  movq $0, rax
  jmp std.resource.Connector.init_epilogue
std.resource.Connector.init_epilogue:
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
.Lfunc_end_std.resource.Connector.init:

.globl std.resource.Binder.bind
std.resource.Binder.bind:
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
  mov [rbp + -72], rdx
std.resource.Binder.bind_entry:
  movq $0, rax
  jmp std.resource.Binder.bind_epilogue
std.resource.Binder.bind_epilogue:
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
.Lfunc_end_std.resource.Binder.bind:

.globl test_distributions
test_distributions:
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
test_distributions_entry:
test_distributions_block_0:
  movq [rel str_const_15], rcx
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
  movq $987654313, rcx
  call std.random.index.Random
  movq $r3, rax
  movq rax, [rbp + -96]
  movq $2, rcx
  movq $2, rdx
  call std.random.index.Uniform
  movq $r8, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  movq [rbp + -96], rdx
  call std.random.distributions.Uniform.sample
  movq $r11, rax
  cmpq $2, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne test_distributions_block_17
  jmp test_distributions_block_21
test_distributions_block_17:
  jmp test_distributions_block_17
  movq $r11, rax
  cmpq $2, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -120]
  jmp test_distributions_block_21
test_distributions_block_21:
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq $9, rax
  jmp test_distributions_epilogue
test_distributions_epilogue:
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
.Lfunc_end_test_distributions:

.globl std.resource.create_hash_engine
std.resource.create_hash_engine:
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
std.resource.create_hash_engine_entry:
std.resource.create_hash_engine_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_hash_engine_block_8
  jmp std.resource.create_hash_engine_block_10
std.resource.create_hash_engine_block_8:
  jmp std.resource.create_hash_engine_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_hash_engine_epilogue
std.resource.create_hash_engine_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_hash_engine_epilogue
std.resource.create_hash_engine_epilogue:
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
.Lfunc_end_std.resource.create_hash_engine:

.globl std.resource.Binder.init
std.resource.Binder.init:
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
  mov [rbp + -72], rdx
std.resource.Binder.init_entry:
  movq $0, rax
  jmp std.resource.Binder.init_epilogue
std.resource.Binder.init_epilogue:
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
.Lfunc_end_std.resource.Binder.init:

.globl std.resource.Listener.listen
std.resource.Listener.listen:
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
  mov [rbp + -72], rdx
std.resource.Listener.listen_entry:
  movq $0, rax
  jmp std.resource.Listener.listen_epilogue
std.resource.Listener.listen_epilogue:
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
.Lfunc_end_std.resource.Listener.listen:

.globl std.resource.Listener.init
std.resource.Listener.init:
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
  mov [rbp + -72], rdx
std.resource.Listener.init_entry:
  movq $0, rax
  jmp std.resource.Listener.init_epilogue
std.resource.Listener.init_epilogue:
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
.Lfunc_end_std.resource.Listener.init:

.globl std.resource.Accepter.init
std.resource.Accepter.init:
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
  mov [rbp + -72], rdx
std.resource.Accepter.init_entry:
  movq $0, rax
  jmp std.resource.Accepter.init_epilogue
std.resource.Accepter.init_epilogue:
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
.Lfunc_end_std.resource.Accepter.init:

.globl std.resource.ResourceReader.read
std.resource.ResourceReader.read:
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
  mov [rbp + -72], rdx
std.resource.ResourceReader.read_entry:
  movq $0, rax
  jmp std.resource.ResourceReader.read_epilogue
std.resource.ResourceReader.read_epilogue:
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
.Lfunc_end_std.resource.ResourceReader.read:

.globl test_random_helpers
test_random_helpers:
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
test_random_helpers_entry:
test_random_helpers_block_0:
  movq [rel str_const_17], rcx
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
  movq $9, rcx
  movq $81, rdx
  call std.random.index.random_int
  movq $r4, rax
  cmpq $9, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne test_random_helpers_block_10
  jmp test_random_helpers_block_14
test_random_helpers_block_10:
  jmp test_random_helpers_block_10
  movq $r4, rax
  cmpq $81, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -104]
  jmp test_random_helpers_block_14
test_random_helpers_block_14:
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq $2, rcx
  movq $2, rdx
  call std.random.index.random_float
  movq $r15, rax
  cmpq $2, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne test_random_helpers_block_24
  jmp test_random_helpers_block_28
test_random_helpers_block_24:
  jmp test_random_helpers_block_24
  movq $r15, rax
  cmpq $2, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -128]
  jmp test_random_helpers_block_28
test_random_helpers_block_28:
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  call std.random.index.random_bool
  movq $r24, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  testq rax, rax
  jne test_random_helpers_block_40
  jmp test_random_helpers_block_36
test_random_helpers_block_36:
  jmp test_random_helpers_block_36
  movq $r24, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  jmp test_random_helpers_block_40
test_random_helpers_block_40:
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq $9, rax
  jmp test_random_helpers_epilogue
test_random_helpers_epilogue:
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
.Lfunc_end_test_random_helpers:

.globl std.resource.create_dns_resolver
std.resource.create_dns_resolver:
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
std.resource.create_dns_resolver_entry:
std.resource.create_dns_resolver_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_dns_resolver_block_8
  jmp std.resource.create_dns_resolver_block_10
std.resource.create_dns_resolver_block_8:
  jmp std.resource.create_dns_resolver_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_dns_resolver_epilogue
std.resource.create_dns_resolver_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_dns_resolver_epilogue
std.resource.create_dns_resolver_epilogue:
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
.Lfunc_end_std.resource.create_dns_resolver:

.globl std.random.index.random_bytes
std.random.index.random_bytes:
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
std.random.index.random_bytes_entry:
std.random.index.random_bytes_block_0:
  movq [rbp + -64], rcx
  call std.random.random.random_bytes
  movq $r1, rax
  jmp std.random.index.random_bytes_epilogue
std.random.index.random_bytes_epilogue:
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
.Lfunc_end_std.random.index.random_bytes:

.globl std.resource.create_websocket
std.resource.create_websocket:
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
std.resource.create_websocket_entry:
std.resource.create_websocket_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_websocket_block_8
  jmp std.resource.create_websocket_block_10
std.resource.create_websocket_block_8:
  jmp std.resource.create_websocket_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_websocket_epilogue
std.resource.create_websocket_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_websocket_epilogue
std.resource.create_websocket_epilogue:
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
.Lfunc_end_std.resource.create_websocket:

.globl std.resource.open_file
std.resource.open_file:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 104
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.resource.open_file_entry:
std.resource.open_file_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r3, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -80]
  movq $r4, rax
  cmpq [rbp + -80], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.resource.open_file_block_8
  jmp std.resource.open_file_block_10
std.resource.open_file_block_8:
  jmp std.resource.open_file_block_8
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp std.resource.open_file_epilogue
std.resource.open_file_block_10:
  movq $0, rcx
  call lm_list_new
  movq $r12, rcx
  movq [rbp + -64], rdx
  call lm_list_append
  movq $r12, rcx
  movq [rbp + -72], rdx
  call lm_list_append
  movq $r4, rcx
  movq $0, rdx
  movq $r12, r8
  call std.internal.runtime.call
  movq $r15, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.resource.open_file_block_19
  jmp std.resource.open_file_block_22
std.resource.open_file_block_19:
  jmp std.resource.open_file_block_19
  movq $r4, rcx
  call std.internal.runtime.destroy
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp std.resource.open_file_epilogue
std.resource.open_file_block_22:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -120], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -120], rcx
  movq $r4, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -120], rax
  jmp std.resource.open_file_epilogue
std.resource.open_file_epilogue:
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
.Lfunc_end_std.resource.open_file:

.globl std.resource.create_entropy
std.resource.create_entropy:
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
std.resource.create_entropy_entry:
std.resource.create_entropy_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_entropy_block_8
  jmp std.resource.create_entropy_block_10
std.resource.create_entropy_block_8:
  jmp std.resource.create_entropy_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_entropy_epilogue
std.resource.create_entropy_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_entropy_epilogue
std.resource.create_entropy_epilogue:
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
.Lfunc_end_std.resource.create_entropy:

.globl std.random.random.random_int
std.random.random.random_int:
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
  mov [rbp + -72], rdx
std.random.random.random_int_entry:
std.random.random.random_int_block_0:
  movq $0, rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.random.random.Random.range_int
  movq $r3, rax
  jmp std.random.random.random_int_epilogue
std.random.random.random_int_epilogue:
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
.Lfunc_end_std.random.random.random_int:

.globl std.resource.adopt_socket
std.resource.adopt_socket:
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
std.resource.adopt_socket_entry:
std.resource.adopt_socket_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -72], rax
  jmp std.resource.adopt_socket_epilogue
std.resource.adopt_socket_epilogue:
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
.Lfunc_end_std.resource.adopt_socket:

.globl std.resource.create_fs_resource
std.resource.create_fs_resource:
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
std.resource.create_fs_resource_entry:
std.resource.create_fs_resource_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_fs_resource_block_8
  jmp std.resource.create_fs_resource_block_10
std.resource.create_fs_resource_block_8:
  jmp std.resource.create_fs_resource_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_fs_resource_epilogue
std.resource.create_fs_resource_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_fs_resource_epilogue
std.resource.create_fs_resource_epilogue:
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
.Lfunc_end_std.resource.create_fs_resource:

.globl std.resource._call
std.resource._call:
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
  mov [rbp + -80], r8
std.resource._call_entry:
std.resource._call_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.internal.runtime.call
  movq $r3, rax
  jmp std.resource._call_epilogue
std.resource._call_epilogue:
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
.Lfunc_end_std.resource._call:

.globl std.resource.__init__
std.resource.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.resource.__init___entry:
  movq $0, rax
  jmp std.resource.__init___epilogue
std.resource.__init___epilogue:
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
.Lfunc_end_std.resource.__init__:

.globl std.random.random.Random.next_int
std.random.random.Random.next_int:
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
std.random.random.Random.next_int_entry:
  movq $0, rax
  jmp std.random.random.Random.next_int_epilogue
std.random.random.Random.next_int_epilogue:
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
.Lfunc_end_std.random.random.Random.next_int:

.globl std.random.random.Random.next_float
std.random.random.Random.next_float:
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
std.random.random.Random.next_float_entry:
  movq $0, rax
  jmp std.random.random.Random.next_float_epilogue
std.random.random.Random.next_float_epilogue:
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
.Lfunc_end_std.random.random.Random.next_float:

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

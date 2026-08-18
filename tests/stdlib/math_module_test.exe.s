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
  .string "=== Math Module Test Suite ==="
.align 8
str_const_1:
  .string "Constants test failed"
.align 8
str_const_2:
  .string "Arithmetic test failed"
.align 8
str_const_3:
  .string "Trigonometry test failed"
.align 8
str_const_4:
  .string "Statistics test failed"
.align 8
str_const_5:
  .string "Random test failed"
.align 8
str_const_6:
  .string "Vectors test failed"
.align 8
str_const_7:
  .string "Quaternion and Matrix test failed"
.align 8
str_const_8:
  .string "All math tests passed successfully."
.align 8
str_const_9:
  .string "Testing Statistics..."
.align 8
str_const_10:
  .string "sum failed"
.align 8
str_const_11:
  .string "mean failed"
.align 8
str_const_12:
  .string "median failed"
.align 8
str_const_13:
  .string "variance failed"
.align 8
str_const_14:
  .string "stddev failed"
.align 8
str_const_15:
  .string "Testing Quaternion and Matrix..."
.align 8
str_const_16:
  .string "quaternion scale failed"
.align 8
str_const_17:
  .string "matrix identity get failed"
.align 8
str_const_18:
  .string "matrix set/get failed"
.align 8
str_const_19:
  .string "Testing Vectors..."
.align 8
str_const_20:
  .string "vector2 add failed"
.align 8
str_const_21:
  .string "vector2 mag failed"
.align 8
str_const_22:
  .string "vector3 cross failed"
.align 8
str_const_23:
  .string "vector4 scale failed"
.align 8
str_const_24:
  .string "Testing Trigonometry..."
.align 8
str_const_25:
  .string "sin failed"
.align 8
str_const_26:
  .string "cos failed"
.align 8
str_const_27:
  .string "tan failed"
.align 8
str_const_28:
  .string "Testing Constants..."
.align 8
str_const_29:
  .string "PI failed"
.align 8
str_const_30:
  .string "E failed"
.align 8
str_const_31:
  .string "TAU failed"
.align 8
str_const_32:
  .string "Testing Arithmetic..."
.align 8
str_const_33:
  .string "abs failed"
.align 8
str_const_34:
  .string "abs_int failed"
.align 8
str_const_35:
  .string "gcd failed"
.align 8
str_const_36:
  .string "lcm failed"
.align 8
str_const_37:
  .string "factorial failed"
.align 8
str_const_38:
  .string "permutations failed"
.align 8
str_const_39:
  .string "combinations failed"
.align 8
str_const_40:
  .string "min failed"
.align 8
str_const_41:
  .string "max failed"
.align 8
str_const_42:
  .string "clamp high failed"
.align 8
str_const_43:
  .string "clamp low failed"
.align 8
str_const_44:
  .string "sign failed"
.align 8
str_const_45:
  .string "lerp failed"
.align 8
str_const_46:
  .string "floor failed"
.align 8
str_const_47:
  .string "ceil failed"
.align 8
str_const_48:
  .string "round high failed"
.align 8
str_const_49:
  .string "trunc failed"
.align 8
str_const_50:
  .string "fract failed"
.align 8
str_const_51:
  .string "sqrt failed"
.align 8
str_const_52:
  .string "cbrt failed"
.align 8
str_const_53:
  .string "hypot failed"
.align 8
str_const_54:
  .string "exp failed"
.align 8
str_const_55:
  .string "Testing Random..."
.align 8
str_const_56:
  .string "random_int range failed"
.align 8
str_const_57:
  .string "random_float range failed"
.align 8
str_const_58:
  .string "random_bool failed"
.align 8
str_const_59:
  .string "random_string len failed"
.align 8
str_const_60:
  .string "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
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
  sub rsp, 216
main_entry:
main_block_0:
  call std.math.index.__init__
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
  call test_constants
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
  call test_arithmetic
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
  call test_trigonometry
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
  call test_statistics
  movq $r17, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  call test_random
  movq $r22, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  call test_vectors
  movq $r27, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  call test_quaternion_and_matrix
  movq $r32, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq [rel str_const_8], rcx
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

.globl std.math.random.random_bytes
std.math.random.random_bytes:
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
std.math.random.random_bytes_entry:
std.math.random.random_bytes_block_0:
  movq $0, rcx
  movq [rbp + -64], rdx
  call std.math.random.Random.next_bytes
  movq $r2, rax
  jmp std.math.random.random_bytes_epilogue
std.math.random.random_bytes_epilogue:
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
.Lfunc_end_std.math.random.random_bytes:

.globl std.math.random.random_float
std.math.random.random_float:
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
std.math.random.random_float_entry:
std.math.random.random_float_block_0:
  movq $0, rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.math.random.Random.range_float
  movq $r3, rax
  jmp std.math.random.random_float_epilogue
std.math.random.random_float_epilogue:
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
.Lfunc_end_std.math.random.random_float:

.globl std.math.trigonometry.tan
std.math.trigonometry.tan:
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
std.math.trigonometry.tan_entry:
std.math.trigonometry.tan_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.trigonometry.TrigFloat.init
  movq [rbp + -72], rcx
  call std.math.trigonometry.TrigFloat.tan
  movq $r3, rax
  jmp std.math.trigonometry.tan_epilogue
std.math.trigonometry.tan_epilogue:
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
.Lfunc_end_std.math.trigonometry.tan:

.globl std.sort._partition
std.sort._partition:
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
  mov [rbp + -88], r9
std.sort._partition_entry:
std.sort._partition_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -80], rdx
  call lm_list_get
  movq [rbp + -72], rax
  subq $9, rax
  movq rax, [rbp + -104]
  jmp std.sort._partition_block_7
std.sort._partition_block_7:
  movq [rbp + -72], rax
  cmpq [rbp + -80], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.sort._partition_block_9
  jmp std.sort._partition_block_25
std.sort._partition_block_9:
  jmp std.sort._partition_block_9
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call lm_list_get
  movq $r13, rcx
  movq $r5, rdx
  movq [rbp + -88], r8
  movq [rbp + -96], r9
  call std.sort._compare
  movq $r14, rax
  cmpq $1, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.sort._partition_block_14
  jmp std.sort._partition_block_20
std.sort._partition_block_14:
  jmp std.sort._partition_block_14
  movq [rbp + -104], rax
  addq $9, rax
  movq rax, [rbp + -128]
  movq [rbp + -64], rcx
  movq [rbp + -128], rdx
  movq [rbp + -72], r8
  call std.sort._swap
  jmp std.sort._partition_block_20
std.sort._partition_block_20:
  movq [rbp + -72], rax
  addq $9, rax
  movq rax, [rbp + -136]
  jmp std.sort._partition_block_7
std.sort._partition_block_25:
  movq [rbp + -128], rax
  addq $9, rax
  movq rax, [rbp + -144]
  movq [rbp + -64], rcx
  movq [rbp + -144], rdx
  movq [rbp + -80], r8
  call std.sort._swap
  movq [rbp + -128], rax
  addq $9, rax
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  jmp std.sort._partition_epilogue
std.sort._partition_epilogue:
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
.Lfunc_end_std.sort._partition:

.globl std.math.trigonometry.cos
std.math.trigonometry.cos:
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
std.math.trigonometry.cos_entry:
std.math.trigonometry.cos_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.trigonometry.TrigFloat.init
  movq [rbp + -72], rcx
  call std.math.trigonometry.TrigFloat.cos
  movq $r3, rax
  jmp std.math.trigonometry.cos_epilogue
std.math.trigonometry.cos_epilogue:
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
.Lfunc_end_std.math.trigonometry.cos:

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

.globl std.math.index.variance
std.math.index.variance:
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
std.math.index.variance_entry:
std.math.index.variance_block_0:
  movq [rbp + -64], rcx
  call std.math.statistics.variance
  movq $r1, rax
  jmp std.math.index.variance_epilogue
std.math.index.variance_epilogue:
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
.Lfunc_end_std.math.index.variance:

.globl std.math.vector3.Vector3.normalize
std.math.vector3.Vector3.normalize:
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
std.math.vector3.Vector3.normalize_entry:
  movq $0, rax
  jmp std.math.vector3.Vector3.normalize_epilogue
std.math.vector3.Vector3.normalize_epilogue:
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
.Lfunc_end_std.math.vector3.Vector3.normalize:

.globl std.math.trigonometry.TrigFloat.init
std.math.trigonometry.TrigFloat.init:
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
std.math.trigonometry.TrigFloat.init_entry:
  movq $0, rax
  jmp std.math.trigonometry.TrigFloat.init_epilogue
std.math.trigonometry.TrigFloat.init_epilogue:
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
.Lfunc_end_std.math.trigonometry.TrigFloat.init:

.globl std.math.trigonometry.TrigFloat.cos
std.math.trigonometry.TrigFloat.cos:
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
std.math.trigonometry.TrigFloat.cos_entry:
  movq $0, rax
  jmp std.math.trigonometry.TrigFloat.cos_epilogue
std.math.trigonometry.TrigFloat.cos_epilogue:
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
.Lfunc_end_std.math.trigonometry.TrigFloat.cos:

.globl std.math.trigonometry.tanh
std.math.trigonometry.tanh:
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
std.math.trigonometry.tanh_entry:
std.math.trigonometry.tanh_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.trigonometry.TrigFloat.init
  movq [rbp + -72], rcx
  call std.math.trigonometry.TrigFloat.tanh
  movq $r3, rax
  jmp std.math.trigonometry.tanh_epilogue
std.math.trigonometry.tanh_epilogue:
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
.Lfunc_end_std.math.trigonometry.tanh:

.globl std.math.index.sinh
std.math.index.sinh:
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
std.math.index.sinh_entry:
std.math.index.sinh_block_0:
  movq [rbp + -64], rcx
  call std.math.trigonometry.sinh
  movq $r1, rax
  jmp std.math.index.sinh_epilogue
std.math.index.sinh_epilogue:
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
.Lfunc_end_std.math.index.sinh:

.globl std.math.arithmetic.exp2
std.math.arithmetic.exp2:
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
std.math.arithmetic.exp2_entry:
std.math.arithmetic.exp2_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -72], rcx
  call std.math.arithmetic.Float.exp2
  movq $r3, rax
  jmp std.math.arithmetic.exp2_epilogue
std.math.arithmetic.exp2_epilogue:
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
.Lfunc_end_std.math.arithmetic.exp2:

.globl std.math.arithmetic.log10
std.math.arithmetic.log10:
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
std.math.arithmetic.log10_entry:
std.math.arithmetic.log10_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -72], rcx
  call std.math.arithmetic.Float.log10
  movq $r3, rax
  jmp std.math.arithmetic.log10_epilogue
std.math.arithmetic.log10_epilogue:
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
.Lfunc_end_std.math.arithmetic.log10:

.globl std.math.arithmetic.sqrt
std.math.arithmetic.sqrt:
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
std.math.arithmetic.sqrt_entry:
std.math.arithmetic.sqrt_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -72], rcx
  call std.math.arithmetic.Float.sqrt
  movq $r3, rax
  jmp std.math.arithmetic.sqrt_epilogue
std.math.arithmetic.sqrt_epilogue:
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
.Lfunc_end_std.math.arithmetic.sqrt:

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

.globl std.math.index.gcd
std.math.index.gcd:
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
std.math.index.gcd_entry:
std.math.index.gcd_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.math.arithmetic.gcd
  movq $r2, rax
  jmp std.math.index.gcd_epilogue
std.math.index.gcd_epilogue:
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
.Lfunc_end_std.math.index.gcd:

.globl std.math.arithmetic.fract
std.math.arithmetic.fract:
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
std.math.arithmetic.fract_entry:
std.math.arithmetic.fract_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -72], rcx
  call std.math.arithmetic.Float.fract
  movq $r3, rax
  jmp std.math.arithmetic.fract_epilogue
std.math.arithmetic.fract_epilogue:
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
.Lfunc_end_std.math.arithmetic.fract:

.globl std.math.vector3.Vector3.sub
std.math.vector3.Vector3.sub:
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
std.math.vector3.Vector3.sub_entry:
  movq $0, rax
  jmp std.math.vector3.Vector3.sub_epilogue
std.math.vector3.Vector3.sub_epilogue:
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
.Lfunc_end_std.math.vector3.Vector3.sub:

.globl std.math.arithmetic.trunc
std.math.arithmetic.trunc:
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
std.math.arithmetic.trunc_entry:
std.math.arithmetic.trunc_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -72], rcx
  call std.math.arithmetic.Float.trunc
  movq $r3, rax
  jmp std.math.arithmetic.trunc_epilogue
std.math.arithmetic.trunc_epilogue:
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
.Lfunc_end_std.math.arithmetic.trunc:

.globl std.math.random.random_int
std.math.random.random_int:
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
std.math.random.random_int_entry:
std.math.random.random_int_block_0:
  movq $0, rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.math.random.Random.range_int
  movq $r3, rax
  jmp std.math.random.random_int_epilogue
std.math.random.random_int_epilogue:
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
.Lfunc_end_std.math.random.random_int:

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

.globl std.math.arithmetic.abs
std.math.arithmetic.abs:
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
std.math.arithmetic.abs_entry:
std.math.arithmetic.abs_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -72], rcx
  call std.math.arithmetic.Float.abs
  movq $r3, rax
  jmp std.math.arithmetic.abs_epilogue
std.math.arithmetic.abs_epilogue:
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
.Lfunc_end_std.math.arithmetic.abs:

.globl std.math.arithmetic.floor
std.math.arithmetic.floor:
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
std.math.arithmetic.floor_entry:
std.math.arithmetic.floor_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -72], rcx
  call std.math.arithmetic.Float.floor
  movq $r3, rax
  jmp std.math.arithmetic.floor_epilogue
std.math.arithmetic.floor_epilogue:
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
.Lfunc_end_std.math.arithmetic.floor:

.globl std.math.arithmetic.Float.log2
std.math.arithmetic.Float.log2:
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
std.math.arithmetic.Float.log2_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.log2_epilogue
std.math.arithmetic.Float.log2_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.log2:

.globl std.math.vector2.Vector2.sub
std.math.vector2.Vector2.sub:
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
std.math.vector2.Vector2.sub_entry:
  movq $0, rax
  jmp std.math.vector2.Vector2.sub_epilogue
std.math.vector2.Vector2.sub_epilogue:
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
.Lfunc_end_std.math.vector2.Vector2.sub:

.globl std.math.arithmetic.Float.round
std.math.arithmetic.Float.round:
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
std.math.arithmetic.Float.round_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.round_epilogue
std.math.arithmetic.Float.round_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.round:

.globl std.math.trigonometry.cosh
std.math.trigonometry.cosh:
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
std.math.trigonometry.cosh_entry:
std.math.trigonometry.cosh_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.trigonometry.TrigFloat.init
  movq [rbp + -72], rcx
  call std.math.trigonometry.TrigFloat.cosh
  movq $r3, rax
  jmp std.math.trigonometry.cosh_epilogue
std.math.trigonometry.cosh_epilogue:
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
.Lfunc_end_std.math.trigonometry.cosh:

.globl std.math.statistics.median
std.math.statistics.median:
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
std.math.statistics.median_entry:
std.math.statistics.median_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.math.statistics.median_block_5
  jmp std.math.statistics.median_block_7
std.math.statistics.median_block_5:
  jmp std.math.statistics.median_block_5
  movq $2, rax
  jmp std.math.statistics.median_epilogue
std.math.statistics.median_block_7:
  movq $0, rcx
  call lm_list_new
  jmp std.math.statistics.median_block_11
std.math.statistics.median_block_11:
  jmp std.math.statistics.median_block_13
std.math.statistics.median_block_13:
  movq $1, rax
  cmpq $r1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.math.statistics.median_block_15
  jmp std.math.statistics.median_block_23
std.math.statistics.median_block_15:
  jmp std.math.statistics.median_block_15
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r7, rcx
  movq $r13, rdx
  call lm_list_append
  jmp std.math.statistics.median_block_18
std.math.statistics.median_block_18:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -88]
  jmp std.math.statistics.median_block_13
std.math.statistics.median_block_23:
  movq $r7, rcx
  movq $10, rdx
  movq $2, r8
  call std.sort.sort
  movq $r1, rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rdx, $r23
  movq $r23, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.math.statistics.median_block_31
  jmp std.math.statistics.median_block_36
std.math.statistics.median_block_31:
  jmp std.math.statistics.median_block_31
  movq $r1, rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rax, $r28
  movq $r7, rcx
  movq $r28, rdx
  call lm_list_get
  movq $r29, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  jmp std.math.statistics.median_epilogue
std.math.statistics.median_block_36:
  movq $r1, rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rax, $r32
  movq $r32, rax
  subq $9, rax
  movq rax, $r34
  movq $r7, rcx
  movq $r34, rdx
  call lm_list_get
  movq $r35, rax
  movq rax, [rbp + -112]
  movq $r1, rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rax, $r39
  movq $r7, rcx
  movq $r39, rdx
  call lm_list_get
  movq $r40, rax
  movq rax, [rbp + -120]
  movq [rbp + -112], rax
  addq [rbp + -120], rax
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  cqto
  movq $2, rcx
  idivq rcx
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp std.math.statistics.median_epilogue
std.math.statistics.median_epilogue:
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
.Lfunc_end_std.math.statistics.median:

.globl std.math.index.tan
std.math.index.tan:
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
std.math.index.tan_entry:
std.math.index.tan_block_0:
  movq [rbp + -64], rcx
  call std.math.trigonometry.tan
  movq $r1, rax
  jmp std.math.index.tan_epilogue
std.math.index.tan_epilogue:
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
.Lfunc_end_std.math.index.tan:

.globl std.math.arithmetic.min
std.math.arithmetic.min:
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
std.math.arithmetic.min_entry:
std.math.arithmetic.min_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -80], rcx
  movq [rbp + -72], rdx
  call std.math.arithmetic.Float.min
  movq $r4, rax
  jmp std.math.arithmetic.min_epilogue
std.math.arithmetic.min_epilogue:
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
.Lfunc_end_std.math.arithmetic.min:

.globl std.math.arithmetic.combinations
std.math.arithmetic.combinations:
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
std.math.arithmetic.combinations_entry:
std.math.arithmetic.combinations_block_0:
  movq [rbp + -72], rax
  cmpq $1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.math.arithmetic.combinations_block_7
  jmp std.math.arithmetic.combinations_block_4
std.math.arithmetic.combinations_block_4:
  jmp std.math.arithmetic.combinations_block_4
  movq [rbp + -72], rax
  cmpq [rbp + -64], rax
  setg al
  movzx eax, al
  movq rax, [rbp + -88]
  jmp std.math.arithmetic.combinations_block_7
std.math.arithmetic.combinations_block_7:
  movq [rbp + -88], rax
  testq rax, rax
  jne std.math.arithmetic.combinations_block_8
  jmp std.math.arithmetic.combinations_block_10
std.math.arithmetic.combinations_block_8:
  jmp std.math.arithmetic.combinations_block_8
  movq $1, rax
  jmp std.math.arithmetic.combinations_epilogue
std.math.arithmetic.combinations_block_10:
  movq [rbp + -64], rcx
  call std.math.arithmetic.factorial
  movq [rbp + -72], rcx
  call std.math.arithmetic.factorial
  movq [rbp + -64], rax
  subq [rbp + -72], rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.math.arithmetic.factorial
  movq $r9, rax
  imulq $r11, rax
  movq rax, $r12
  movq $r12, rax
  movq rax, [rbp + -104]
  movq $r8, rax
  cqto
  movq [rbp + -104], rcx
  idivq rcx
  movq rax, $r13
  movq $r13, rax
  jmp std.math.arithmetic.combinations_epilogue
std.math.arithmetic.combinations_epilogue:
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
.Lfunc_end_std.math.arithmetic.combinations:

.globl std.math.arithmetic.permutations
std.math.arithmetic.permutations:
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
std.math.arithmetic.permutations_entry:
std.math.arithmetic.permutations_block_0:
  movq [rbp + -72], rax
  cmpq $1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.math.arithmetic.permutations_block_7
  jmp std.math.arithmetic.permutations_block_4
std.math.arithmetic.permutations_block_4:
  jmp std.math.arithmetic.permutations_block_4
  movq [rbp + -72], rax
  cmpq [rbp + -64], rax
  setg al
  movzx eax, al
  movq rax, [rbp + -88]
  jmp std.math.arithmetic.permutations_block_7
std.math.arithmetic.permutations_block_7:
  movq [rbp + -88], rax
  testq rax, rax
  jne std.math.arithmetic.permutations_block_8
  jmp std.math.arithmetic.permutations_block_10
std.math.arithmetic.permutations_block_8:
  jmp std.math.arithmetic.permutations_block_8
  movq $1, rax
  jmp std.math.arithmetic.permutations_epilogue
std.math.arithmetic.permutations_block_10:
  movq [rbp + -64], rcx
  call std.math.arithmetic.factorial
  movq [rbp + -64], rax
  subq [rbp + -72], rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.math.arithmetic.factorial
  movq $r8, rax
  cqto
  movq $r10, rcx
  idivq rcx
  movq rax, $r11
  movq $r11, rax
  jmp std.math.arithmetic.permutations_epilogue
std.math.arithmetic.permutations_epilogue:
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
.Lfunc_end_std.math.arithmetic.permutations:

.globl std.math.arithmetic.lcm
std.math.arithmetic.lcm:
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
std.math.arithmetic.lcm_entry:
std.math.arithmetic.lcm_block_0:
  movq [rbp + -64], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.math.arithmetic.lcm_block_8
  jmp std.math.arithmetic.lcm_block_4
std.math.arithmetic.lcm_block_4:
  jmp std.math.arithmetic.lcm_block_4
  movq [rbp + -72], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  jmp std.math.arithmetic.lcm_block_8
std.math.arithmetic.lcm_block_8:
  movq [rbp + -88], rax
  testq rax, rax
  jne std.math.arithmetic.lcm_block_9
  jmp std.math.arithmetic.lcm_block_11
std.math.arithmetic.lcm_block_9:
  jmp std.math.arithmetic.lcm_block_9
  movq $1, rax
  jmp std.math.arithmetic.lcm_epilogue
std.math.arithmetic.lcm_block_11:
  movq [rbp + -64], rax
  imulq [rbp + -72], rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.math.arithmetic.abs_int
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.math.arithmetic.gcd
  movq $r10, rax
  cqto
  movq $r11, rcx
  idivq rcx
  movq rax, $r12
  movq $r12, rax
  jmp std.math.arithmetic.lcm_epilogue
std.math.arithmetic.lcm_epilogue:
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
.Lfunc_end_std.math.arithmetic.lcm:

.globl std.math.arithmetic.round
std.math.arithmetic.round:
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
std.math.arithmetic.round_entry:
std.math.arithmetic.round_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -72], rcx
  call std.math.arithmetic.Float.round
  movq $r3, rax
  jmp std.math.arithmetic.round_epilogue
std.math.arithmetic.round_epilogue:
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
.Lfunc_end_std.math.arithmetic.round:

.globl std.math.arithmetic.pow
std.math.arithmetic.pow:
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
std.math.arithmetic.pow_entry:
std.math.arithmetic.pow_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -80], rcx
  movq [rbp + -72], rdx
  call std.math.arithmetic.Float.pow
  movq $r4, rax
  jmp std.math.arithmetic.pow_epilogue
std.math.arithmetic.pow_epilogue:
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
.Lfunc_end_std.math.arithmetic.pow:

.globl std.math.arithmetic.Float.hypot
std.math.arithmetic.Float.hypot:
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
std.math.arithmetic.Float.hypot_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.hypot_epilogue
std.math.arithmetic.Float.hypot_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.hypot:

.globl std.sort._merge
std.sort._merge:
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
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.sort._merge_entry:
std.sort._merge_block_0:
  movq $0, rcx
  call lm_list_new
  movq [rbp + -80], rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.sort._merge_block_8
std.sort._merge_block_8:
  movq [rbp + -72], rax
  cmpq [rbp + -80], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.sort._merge_block_11
  jmp std.sort._merge_block_14
std.sort._merge_block_11:
  jmp std.sort._merge_block_11
  movq [rbp + -112], rax
  cmpq [rbp + -88], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -128]
  jmp std.sort._merge_block_14
std.sort._merge_block_14:
  movq [rbp + -128], rax
  testq rax, rax
  jne std.sort._merge_block_15
  jmp std.sort._merge_block_36
std.sort._merge_block_15:
  jmp std.sort._merge_block_15
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq [rbp + -112], rdx
  call lm_list_get
  movq $r17, rcx
  movq $r18, rdx
  movq [rbp + -96], r8
  movq [rbp + -104], r9
  call std.sort._compare
  movq $r19, rax
  cmpq $1, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne std.sort._merge_block_21
  jmp std.sort._merge_block_28
std.sort._merge_block_21:
  jmp std.sort._merge_block_21
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call lm_list_get
  movq $r6, rcx
  movq $r23, rdx
  call lm_list_append
  movq [rbp + -72], rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.sort._merge_block_35
std.sort._merge_block_28:
  movq [rbp + -64], rcx
  movq [rbp + -112], rdx
  call lm_list_get
  movq $r6, rcx
  movq $r29, rdx
  call lm_list_append
  movq [rbp + -112], rax
  addq $9, rax
  movq rax, [rbp + -152]
  jmp std.sort._merge_block_35
std.sort._merge_block_35:
  jmp std.sort._merge_block_8
std.sort._merge_block_36:
  jmp std.sort._merge_block_37
std.sort._merge_block_37:
  movq [rbp + -144], rax
  cmpq [rbp + -80], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  testq rax, rax
  jne std.sort._merge_block_39
  jmp std.sort._merge_block_46
std.sort._merge_block_39:
  jmp std.sort._merge_block_39
  movq [rbp + -64], rcx
  movq [rbp + -144], rdx
  call lm_list_get
  movq $r6, rcx
  movq $r37, rdx
  call lm_list_append
  movq [rbp + -144], rax
  addq $9, rax
  movq rax, [rbp + -168]
  jmp std.sort._merge_block_37
std.sort._merge_block_46:
  jmp std.sort._merge_block_47
std.sort._merge_block_47:
  movq [rbp + -152], rax
  cmpq [rbp + -88], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne std.sort._merge_block_49
  jmp std.sort._merge_block_56
std.sort._merge_block_49:
  jmp std.sort._merge_block_49
  movq [rbp + -64], rcx
  movq [rbp + -152], rdx
  call lm_list_get
  movq $r6, rcx
  movq $r45, rdx
  call lm_list_append
  movq [rbp + -152], rax
  addq $9, rax
  movq rax, [rbp + -184]
  jmp std.sort._merge_block_47
std.sort._merge_block_56:
  jmp std.sort._merge_block_58
std.sort._merge_block_58:
  movq $r6, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r52, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  testq rax, rax
  jne std.sort._merge_block_61
  jmp std.sort._merge_block_69
std.sort._merge_block_61:
  jmp std.sort._merge_block_61
  movq $r6, rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -72], rax
  addq $1, rax
  movq rax, [rbp + -200]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -208]
  jmp std.sort._merge_block_58
std.sort._merge_block_69:
  movq $0, rax
  jmp std.sort._merge_epilogue
std.sort._merge_epilogue:
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
.Lfunc_end_std.sort._merge:

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

.globl std.math.vector3.Vector3.add
std.math.vector3.Vector3.add:
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
std.math.vector3.Vector3.add_entry:
  movq $0, rax
  jmp std.math.vector3.Vector3.add_epilogue
std.math.vector3.Vector3.add_epilogue:
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
.Lfunc_end_std.math.vector3.Vector3.add:

.globl std.math.arithmetic.Float.pow
std.math.arithmetic.Float.pow:
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
std.math.arithmetic.Float.pow_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.pow_epilogue
std.math.arithmetic.Float.pow_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.pow:

.globl std.math.index.abs
std.math.index.abs:
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
std.math.index.abs_entry:
std.math.index.abs_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.abs
  movq $r1, rax
  jmp std.math.index.abs_epilogue
std.math.index.abs_epilogue:
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
.Lfunc_end_std.math.index.abs:

.globl std.math.trigonometry.atan2
std.math.trigonometry.atan2:
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
std.math.trigonometry.atan2_entry:
std.math.trigonometry.atan2_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  call std.math.trigonometry.TrigFloat.init
  movq [rbp + -80], rcx
  movq [rbp + -72], rdx
  call std.math.trigonometry.TrigFloat.atan2
  movq $r4, rax
  jmp std.math.trigonometry.atan2_epilogue
std.math.trigonometry.atan2_epilogue:
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
.Lfunc_end_std.math.trigonometry.atan2:

.globl std.math.trigonometry.TrigFloat.atan
std.math.trigonometry.TrigFloat.atan:
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
std.math.trigonometry.TrigFloat.atan_entry:
  movq $0, rax
  jmp std.math.trigonometry.TrigFloat.atan_epilogue
std.math.trigonometry.TrigFloat.atan_epilogue:
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
.Lfunc_end_std.math.trigonometry.TrigFloat.atan:

.globl std.math.matrix.__init__
std.math.matrix.__init__:
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
std.math.matrix.__init___entry:
  movq $0, rax
  jmp std.math.matrix.__init___epilogue
std.math.matrix.__init___epilogue:
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
.Lfunc_end_std.math.matrix.__init__:

.globl std.math.arithmetic.Float.cbrt
std.math.arithmetic.Float.cbrt:
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
std.math.arithmetic.Float.cbrt_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.cbrt_epilogue
std.math.arithmetic.Float.cbrt_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.cbrt:

.globl std.math.arithmetic.hypot
std.math.arithmetic.hypot:
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
std.math.arithmetic.hypot_entry:
std.math.arithmetic.hypot_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -80], rcx
  movq [rbp + -72], rdx
  call std.math.arithmetic.Float.hypot
  movq $r4, rax
  jmp std.math.arithmetic.hypot_epilogue
std.math.arithmetic.hypot_epilogue:
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
.Lfunc_end_std.math.arithmetic.hypot:

.globl std.math.arithmetic.Float.trunc
std.math.arithmetic.Float.trunc:
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
std.math.arithmetic.Float.trunc_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.trunc_epilogue
std.math.arithmetic.Float.trunc_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.trunc:

.globl std.math.arithmetic.Float.fract
std.math.arithmetic.Float.fract:
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
std.math.arithmetic.Float.fract_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.fract_epilogue
std.math.arithmetic.Float.fract_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.fract:

.globl std.math.trigonometry.TrigFloat.tanh
std.math.trigonometry.TrigFloat.tanh:
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
std.math.trigonometry.TrigFloat.tanh_entry:
  movq $0, rax
  jmp std.math.trigonometry.TrigFloat.tanh_epilogue
std.math.trigonometry.TrigFloat.tanh_epilogue:
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
.Lfunc_end_std.math.trigonometry.TrigFloat.tanh:

.globl std.math.index.acos
std.math.index.acos:
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
std.math.index.acos_entry:
std.math.index.acos_block_0:
  movq [rbp + -64], rcx
  call std.math.trigonometry.acos
  movq $r1, rax
  jmp std.math.index.acos_epilogue
std.math.index.acos_epilogue:
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
.Lfunc_end_std.math.index.acos:

.globl std.math.arithmetic.clamp
std.math.arithmetic.clamp:
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
  mov [rbp + -80], r8
std.math.arithmetic.clamp_entry:
std.math.arithmetic.clamp_block_0:
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.math.arithmetic.clamp_block_2
  jmp std.math.arithmetic.clamp_block_3
std.math.arithmetic.clamp_block_2:
  jmp std.math.arithmetic.clamp_block_2
  movq [rbp + -72], rax
  jmp std.math.arithmetic.clamp_epilogue
std.math.arithmetic.clamp_block_3:
  movq [rbp + -64], rax
  cmpq [rbp + -80], rax
  setg al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.math.arithmetic.clamp_block_5
  jmp std.math.arithmetic.clamp_block_6
std.math.arithmetic.clamp_block_5:
  jmp std.math.arithmetic.clamp_block_5
  movq [rbp + -80], rax
  jmp std.math.arithmetic.clamp_epilogue
std.math.arithmetic.clamp_block_6:
  movq $0, rax
  jmp std.math.arithmetic.clamp_epilogue
std.math.arithmetic.clamp_epilogue:
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
.Lfunc_end_std.math.arithmetic.clamp:

.globl std.math.arithmetic.Float.floor
std.math.arithmetic.Float.floor:
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
std.math.arithmetic.Float.floor_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.floor_epilogue
std.math.arithmetic.Float.floor_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.floor:

.globl std.math.arithmetic.Float.max
std.math.arithmetic.Float.max:
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
std.math.arithmetic.Float.max_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.max_epilogue
std.math.arithmetic.Float.max_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.max:

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

.globl std.math.arithmetic.Float.abs
std.math.arithmetic.Float.abs:
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
std.math.arithmetic.Float.abs_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.abs_epilogue
std.math.arithmetic.Float.abs_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.abs:

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

.globl std.math.trigonometry.atan
std.math.trigonometry.atan:
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
std.math.trigonometry.atan_entry:
std.math.trigonometry.atan_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.trigonometry.TrigFloat.init
  movq [rbp + -72], rcx
  call std.math.trigonometry.TrigFloat.atan
  movq $r3, rax
  jmp std.math.trigonometry.atan_epilogue
std.math.trigonometry.atan_epilogue:
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
.Lfunc_end_std.math.trigonometry.atan:

.globl test_statistics
test_statistics:
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
test_statistics_entry:
test_statistics_block_0:
  movq [rel str_const_9], rcx
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
  movq $r2, rcx
  movq $2, rdx
  call lm_list_append
  movq $r2, rcx
  movq $2, rdx
  call lm_list_append
  movq $r2, rcx
  movq $2, rdx
  call lm_list_append
  movq $r2, rcx
  movq $2, rdx
  call lm_list_append
  movq $r2, rcx
  movq $2, rdx
  call lm_list_append
  movq $r2, rcx
  call std.math.index.sum
  movq $r14, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r16, rcx
  movq [rbp + -96], rdx
  call lm_assert
  movq $r2, rcx
  call std.math.index.mean
  movq $r19, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r21, rcx
  movq [rbp + -104], rdx
  call lm_assert
  movq $r2, rcx
  call std.math.index.median
  movq $r24, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r26, rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq $r2, rcx
  call std.math.index.variance
  movq $r29, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq $r31, rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq $r2, rcx
  call std.math.index.stddev
  movq $r34, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq $r36, rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq $9, rax
  jmp test_statistics_epilogue
test_statistics_epilogue:
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
.Lfunc_end_test_statistics:

.globl std.math.index.log
std.math.index.log:
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
std.math.index.log_entry:
std.math.index.log_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.log
  movq $r1, rax
  jmp std.math.index.log_epilogue
std.math.index.log_epilogue:
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
.Lfunc_end_std.math.index.log:

.globl std.math.arithmetic.lerp
std.math.arithmetic.lerp:
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
  mov [rbp + -80], r8
std.math.arithmetic.lerp_entry:
std.math.arithmetic.lerp_block_0:
  movq [rbp + -72], rax
  subq [rbp + -64], rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  imulq [rbp + -80], rax
  movq rax, [rbp + -96]
  movq [rbp + -72], rax
  subq [rbp + -64], rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  imulq [rbp + -80], rax
  movq rax, [rbp + -112]
  movq [rbp + -64], rax
  addq [rbp + -112], rax
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  jmp std.math.arithmetic.lerp_epilogue
std.math.arithmetic.lerp_epilogue:
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
.Lfunc_end_std.math.arithmetic.lerp:

.globl std.math.arithmetic.Float.ceil
std.math.arithmetic.Float.ceil:
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
std.math.arithmetic.Float.ceil_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.ceil_epilogue
std.math.arithmetic.Float.ceil_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.ceil:

.globl std.math.index.stddev
std.math.index.stddev:
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
std.math.index.stddev_entry:
std.math.index.stddev_block_0:
  movq [rbp + -64], rcx
  call std.math.statistics.stddev
  movq $r1, rax
  jmp std.math.index.stddev_epilogue
std.math.index.stddev_epilogue:
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
.Lfunc_end_std.math.index.stddev:

.globl std.sort.mergesort
std.sort.mergesort:
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
std.sort.mergesort_entry:
std.sort.mergesort_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  cmpq $9, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.sort.mergesort_block_4
  jmp std.sort.mergesort_block_10
std.sort.mergesort_block_4:
  jmp std.sort.mergesort_block_4
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r8, rax
  subq $9, rax
  movq rax, $r10
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $r10, r8
  movq [rbp + -72], r9
  call std.sort._mergesort_range
  jmp std.sort.mergesort_block_10
std.sort.mergesort_block_10:
  movq $0, rax
  jmp std.sort.mergesort_epilogue
std.sort.mergesort_epilogue:
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
.Lfunc_end_std.sort.mergesort:

.globl std.math.arithmetic.Float.exp
std.math.arithmetic.Float.exp:
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
std.math.arithmetic.Float.exp_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.exp_epilogue
std.math.arithmetic.Float.exp_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.exp:

.globl std.math.arithmetic.Float.min
std.math.arithmetic.Float.min:
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
std.math.arithmetic.Float.min_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.min_epilogue
std.math.arithmetic.Float.min_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.min:

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

.globl std.math.arithmetic.max
std.math.arithmetic.max:
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
std.math.arithmetic.max_entry:
std.math.arithmetic.max_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -80], rcx
  movq [rbp + -72], rdx
  call std.math.arithmetic.Float.max
  movq $r4, rax
  jmp std.math.arithmetic.max_epilogue
std.math.arithmetic.max_epilogue:
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
.Lfunc_end_std.math.arithmetic.max:

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

.globl std.math.index.exp2
std.math.index.exp2:
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
std.math.index.exp2_entry:
std.math.index.exp2_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.exp2
  movq $r1, rax
  jmp std.math.index.exp2_epilogue
std.math.index.exp2_epilogue:
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
.Lfunc_end_std.math.index.exp2:

.globl std.math.arithmetic.Int.init
std.math.arithmetic.Int.init:
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
std.math.arithmetic.Int.init_entry:
  movq $0, rax
  jmp std.math.arithmetic.Int.init_epilogue
std.math.arithmetic.Int.init_epilogue:
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
.Lfunc_end_std.math.arithmetic.Int.init:

.globl std.math.index.random_bytes
std.math.index.random_bytes:
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
std.math.index.random_bytes_entry:
std.math.index.random_bytes_block_0:
  movq [rbp + -64], rcx
  call std.math.random.random_bytes
  movq $r1, rax
  jmp std.math.index.random_bytes_epilogue
std.math.index.random_bytes_epilogue:
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
.Lfunc_end_std.math.index.random_bytes:

.globl std.math.arithmetic.factorial
std.math.arithmetic.factorial:
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
std.math.arithmetic.factorial_entry:
std.math.arithmetic.factorial_block_0:
  movq [rbp + -64], rax
  cmpq $1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.math.arithmetic.factorial_block_3
  jmp std.math.arithmetic.factorial_block_5
std.math.arithmetic.factorial_block_3:
  jmp std.math.arithmetic.factorial_block_3
  movq $1, rax
  jmp std.math.arithmetic.factorial_epilogue
std.math.arithmetic.factorial_block_5:
  movq [rbp + -64], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.math.arithmetic.factorial_block_8
  jmp std.math.arithmetic.factorial_block_10
std.math.arithmetic.factorial_block_8:
  jmp std.math.arithmetic.factorial_block_8
  movq $9, rax
  jmp std.math.arithmetic.factorial_epilogue
std.math.arithmetic.factorial_block_10:
  jmp std.math.arithmetic.factorial_block_13
std.math.arithmetic.factorial_block_13:
  movq $9, rax
  cmpq [rbp + -64], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.math.arithmetic.factorial_block_15
  jmp std.math.arithmetic.factorial_block_22
std.math.arithmetic.factorial_block_15:
  jmp std.math.arithmetic.factorial_block_15
  movq $9, rax
  imulq $9, rax
  movq rax, [rbp + -96]
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.math.arithmetic.factorial_block_13
std.math.arithmetic.factorial_block_22:
  movq [rbp + -96], rax
  jmp std.math.arithmetic.factorial_epilogue
std.math.arithmetic.factorial_epilogue:
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
.Lfunc_end_std.math.arithmetic.factorial:

.globl nearly_equal
nearly_equal:
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
nearly_equal_entry:
nearly_equal_block_0:
  movq [rbp + -64], rax
  subq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  cmpq $2, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne nearly_equal_block_5
  jmp nearly_equal_block_8
nearly_equal_block_5:
  jmp nearly_equal_block_5
  movq [rbp + -80], rax
  negq rax
  movq rax, [rbp + -96]
  jmp nearly_equal_block_8
nearly_equal_block_8:
  movq [rbp + -96], rax
  cmpq $2, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  jmp nearly_equal_epilogue
nearly_equal_epilogue:
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
.Lfunc_end_nearly_equal:

.globl std.math.trigonometry.TrigFloat.sinh
std.math.trigonometry.TrigFloat.sinh:
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
std.math.trigonometry.TrigFloat.sinh_entry:
  movq $0, rax
  jmp std.math.trigonometry.TrigFloat.sinh_epilogue
std.math.trigonometry.TrigFloat.sinh_epilogue:
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
.Lfunc_end_std.math.trigonometry.TrigFloat.sinh:

.globl std.math.arithmetic.Float.sqrt
std.math.arithmetic.Float.sqrt:
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
std.math.arithmetic.Float.sqrt_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.sqrt_epilogue
std.math.arithmetic.Float.sqrt_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.sqrt:

.globl std.math.vector3.Vector3.scale
std.math.vector3.Vector3.scale:
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
std.math.vector3.Vector3.scale_entry:
  movq $0, rax
  jmp std.math.vector3.Vector3.scale_epilogue
std.math.vector3.Vector3.scale_epilogue:
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
.Lfunc_end_std.math.vector3.Vector3.scale:

.globl std.math.index.sqrt
std.math.index.sqrt:
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
std.math.index.sqrt_entry:
std.math.index.sqrt_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.sqrt
  movq $r1, rax
  jmp std.math.index.sqrt_epilogue
std.math.index.sqrt_epilogue:
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
.Lfunc_end_std.math.index.sqrt:

.globl std.math.quaternion.__init__
std.math.quaternion.__init__:
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
std.math.quaternion.__init___entry:
  movq $0, rax
  jmp std.math.quaternion.__init___epilogue
std.math.quaternion.__init___epilogue:
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
.Lfunc_end_std.math.quaternion.__init__:

.globl std.math.arithmetic.Float.log
std.math.arithmetic.Float.log:
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
std.math.arithmetic.Float.log_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.log_epilogue
std.math.arithmetic.Float.log_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.log:

.globl std.math.quaternion.Quaternion.scale
std.math.quaternion.Quaternion.scale:
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
std.math.quaternion.Quaternion.scale_entry:
  movq $0, rax
  jmp std.math.quaternion.Quaternion.scale_epilogue
std.math.quaternion.Quaternion.scale_epilogue:
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
.Lfunc_end_std.math.quaternion.Quaternion.scale:

.globl std.math.statistics.mean
std.math.statistics.mean:
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
std.math.statistics.mean_entry:
std.math.statistics.mean_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.math.statistics.mean_block_4
  jmp std.math.statistics.mean_block_6
std.math.statistics.mean_block_4:
  jmp std.math.statistics.mean_block_4
  movq $2, rax
  jmp std.math.statistics.mean_epilogue
std.math.statistics.mean_block_6:
  movq [rbp + -64], rcx
  call std.math.statistics.sum
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r7, rax
  movq rax, [rbp + -80]
  movq $r6, rax
  cqto
  movq [rbp + -80], rcx
  idivq rcx
  movq rax, $r9
  movq $r9, rax
  jmp std.math.statistics.mean_epilogue
std.math.statistics.mean_epilogue:
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
.Lfunc_end_std.math.statistics.mean:

.globl std.math.arithmetic.Float.exp2
std.math.arithmetic.Float.exp2:
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
std.math.arithmetic.Float.exp2_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.exp2_epilogue
std.math.arithmetic.Float.exp2_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.exp2:

.globl std.math.arithmetic.__init__
std.math.arithmetic.__init__:
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
std.math.arithmetic.__init___entry:
  movq $0, rax
  jmp std.math.arithmetic.__init___epilogue
std.math.arithmetic.__init___epilogue:
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
.Lfunc_end_std.math.arithmetic.__init__:

.globl test_quaternion_and_matrix
test_quaternion_and_matrix:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 168
test_quaternion_and_matrix_entry:
test_quaternion_and_matrix_block_0:
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
  movq $2, rcx
  movq $2, rdx
  movq $2, r8
  movq $2, r9
  call std.math.index.Quaternion
  movq $r6, rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  movq $2, rdx
  call std.math.quaternion.Quaternion.scale
  movq $r10, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  call std.math.index.Matrix
  movq $r18, rax
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  movq $1, rdx
  movq $1, r8
  call std.math.matrix.Matrix.get
  movq $r23, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq [rbp + -144], rcx
  movq $1, rdx
  movq $9, r8
  movq $2, r9
  call std.math.matrix.Matrix.set
  movq [rbp + -144], rcx
  movq $1, rdx
  movq $9, r8
  call std.math.matrix.Matrix.get
  movq $r34, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call lm_assert
  movq $9, rax
  jmp test_quaternion_and_matrix_epilogue
test_quaternion_and_matrix_epilogue:
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
.Lfunc_end_test_quaternion_and_matrix:

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

.globl test_vectors
test_vectors:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 344
test_vectors_entry:
test_vectors_block_0:
  movq [rel str_const_19], rcx
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
  movq $2, rcx
  movq $2, rdx
  call std.math.index.Vector2
  movq $r4, rax
  movq rax, [rbp + -96]
  movq $2, rcx
  movq $2, rdx
  call std.math.index.Vector2
  movq $r9, rax
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call std.math.vector2.Vector2.add
  movq $r12, rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  addq $0, rax
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne test_vectors_block_20
  jmp test_vectors_block_25
test_vectors_block_20:
  jmp test_vectors_block_20
  movq [rbp + -112], rax
  addq $0, rax
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  jmp test_vectors_block_25
test_vectors_block_25:
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.math.vector2.Vector2.mag
  movq $r24, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq $r26, rcx
  movq [rbp + -176], rdx
  call lm_assert
  movq $2, rcx
  movq $2, rdx
  movq $2, r8
  call std.math.index.Vector3
  movq $r32, rax
  movq rax, [rbp + -184]
  movq $2, rcx
  movq $2, rdx
  movq $2, r8
  call std.math.index.Vector3
  movq $r38, rax
  movq rax, [rbp + -192]
  movq [rbp + -184], rcx
  movq [rbp + -192], rdx
  call std.math.vector3.Vector3.cross
  movq $r41, rax
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  addq $0, rax
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  testq rax, rax
  jne test_vectors_block_52
  jmp test_vectors_block_57
test_vectors_block_52:
  jmp test_vectors_block_52
  movq [rbp + -200], rax
  addq $0, rax
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  jmp test_vectors_block_57
test_vectors_block_57:
  movq [rbp + -248], rax
  testq rax, rax
  jne test_vectors_block_59
  jmp test_vectors_block_64
test_vectors_block_59:
  jmp test_vectors_block_59
  movq [rbp + -200], rax
  addq $0, rax
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -272]
  jmp test_vectors_block_64
test_vectors_block_64:
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -272], rcx
  movq [rbp + -280], rdx
  call lm_assert
  movq $2, rcx
  movq $2, rdx
  movq $2, r8
  movq $2, r9
  call std.math.index.Vector4
  movq $r61, rax
  movq rax, [rbp + -288]
  movq [rbp + -288], rcx
  movq $2, rdx
  call std.math.vector4.Vector4.scale
  movq $r65, rax
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  addq $0, rax
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -312]
  movq [rbp + -312], rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  testq rax, rax
  jne test_vectors_block_82
  jmp test_vectors_block_87
test_vectors_block_82:
  jmp test_vectors_block_82
  movq [rbp + -296], rax
  addq $0, rax
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -336]
  movq [rbp + -336], rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -344]
  jmp test_vectors_block_87
test_vectors_block_87:
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -344], rcx
  movq [rbp + -352], rdx
  call lm_assert
  movq $9, rax
  jmp test_vectors_epilogue
test_vectors_epilogue:
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
.Lfunc_end_test_vectors:

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

.globl std.math.arithmetic.Float.log10
std.math.arithmetic.Float.log10:
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
std.math.arithmetic.Float.log10_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.log10_epilogue
std.math.arithmetic.Float.log10_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.log10:

.globl std.math.arithmetic.abs_int
std.math.arithmetic.abs_int:
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
std.math.arithmetic.abs_int_entry:
std.math.arithmetic.abs_int_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Int.init
  movq [rbp + -72], rcx
  call std.math.arithmetic.Int.abs
  movq $r3, rax
  jmp std.math.arithmetic.abs_int_epilogue
std.math.arithmetic.abs_int_epilogue:
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
.Lfunc_end_std.math.arithmetic.abs_int:

.globl std.math.index.lerp
std.math.index.lerp:
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
std.math.index.lerp_entry:
std.math.index.lerp_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.math.arithmetic.lerp
  movq $r3, rax
  jmp std.math.index.lerp_epilogue
std.math.index.lerp_epilogue:
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
.Lfunc_end_std.math.index.lerp:

.globl std.math.arithmetic.Float.init
std.math.arithmetic.Float.init:
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
std.math.arithmetic.Float.init_entry:
  movq $0, rax
  jmp std.math.arithmetic.Float.init_epilogue
std.math.arithmetic.Float.init_epilogue:
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
.Lfunc_end_std.math.arithmetic.Float.init:

.globl std.math.arithmetic.cbrt
std.math.arithmetic.cbrt:
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
std.math.arithmetic.cbrt_entry:
std.math.arithmetic.cbrt_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -72], rcx
  call std.math.arithmetic.Float.cbrt
  movq $r3, rax
  jmp std.math.arithmetic.cbrt_epilogue
std.math.arithmetic.cbrt_epilogue:
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
.Lfunc_end_std.math.arithmetic.cbrt:

.globl std.math.random.SecureRandom.next_int
std.math.random.SecureRandom.next_int:
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
std.math.random.SecureRandom.next_int_entry:
  movq $0, rax
  jmp std.math.random.SecureRandom.next_int_epilogue
std.math.random.SecureRandom.next_int_epilogue:
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
.Lfunc_end_std.math.random.SecureRandom.next_int:

.globl std.math.trigonometry.TrigFloat.normalize_angle
std.math.trigonometry.TrigFloat.normalize_angle:
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
std.math.trigonometry.TrigFloat.normalize_angle_entry:
  movq $0, rax
  jmp std.math.trigonometry.TrigFloat.normalize_angle_epilogue
std.math.trigonometry.TrigFloat.normalize_angle_epilogue:
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
.Lfunc_end_std.math.trigonometry.TrigFloat.normalize_angle:

.globl std.math.index.min
std.math.index.min:
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
std.math.index.min_entry:
std.math.index.min_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.math.arithmetic.min
  movq $r2, rax
  jmp std.math.index.min_epilogue
std.math.index.min_epilogue:
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
.Lfunc_end_std.math.index.min:

.globl std.math.trigonometry.sin
std.math.trigonometry.sin:
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
std.math.trigonometry.sin_entry:
std.math.trigonometry.sin_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.trigonometry.TrigFloat.init
  movq [rbp + -72], rcx
  call std.math.trigonometry.TrigFloat.sin
  movq $r3, rax
  jmp std.math.trigonometry.sin_epilogue
std.math.trigonometry.sin_epilogue:
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
.Lfunc_end_std.math.trigonometry.sin:

.globl test_trigonometry
test_trigonometry:
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
test_trigonometry_entry:
test_trigonometry_block_0:
  movq [rel str_const_24], rcx
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
  movq $2, rcx
  call std.math.index.sin
  movq $r3, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r5, rcx
  movq [rbp + -96], rdx
  call lm_assert
  movq $2, rcx
  call std.math.index.cos
  movq $r9, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r11, rcx
  movq [rbp + -104], rdx
  call lm_assert
  movq $2, rcx
  call std.math.index.tan
  movq $r15, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r17, rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq $9, rax
  jmp test_trigonometry_epilogue
test_trigonometry_epilogue:
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
.Lfunc_end_test_trigonometry:

.globl std.math.index.combinations
std.math.index.combinations:
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
std.math.index.combinations_entry:
std.math.index.combinations_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.math.arithmetic.combinations
  movq $r2, rax
  jmp std.math.index.combinations_epilogue
std.math.index.combinations_epilogue:
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
.Lfunc_end_std.math.index.combinations:

.globl std.math.trigonometry.asin
std.math.trigonometry.asin:
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
std.math.trigonometry.asin_entry:
std.math.trigonometry.asin_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.trigonometry.TrigFloat.init
  movq [rbp + -72], rcx
  call std.math.trigonometry.TrigFloat.asin
  movq $r3, rax
  jmp std.math.trigonometry.asin_epilogue
std.math.trigonometry.asin_epilogue:
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
.Lfunc_end_std.math.trigonometry.asin:

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

.globl std.math.random.SecureRandom.init
std.math.random.SecureRandom.init:
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
std.math.random.SecureRandom.init_entry:
  movq $0, rax
  jmp std.math.random.SecureRandom.init_epilogue
std.math.random.SecureRandom.init_epilogue:
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
.Lfunc_end_std.math.random.SecureRandom.init:

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

.globl std.math.statistics.variance
std.math.statistics.variance:
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
std.math.statistics.variance_entry:
std.math.statistics.variance_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  cmpq $17, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.math.statistics.variance_block_5
  jmp std.math.statistics.variance_block_7
std.math.statistics.variance_block_5:
  jmp std.math.statistics.variance_block_5
  movq $2, rax
  jmp std.math.statistics.variance_epilogue
std.math.statistics.variance_block_7:
  movq [rbp + -64], rcx
  call std.math.statistics.mean
  jmp std.math.statistics.variance_block_11
std.math.statistics.variance_block_11:
  jmp std.math.statistics.variance_block_13
std.math.statistics.variance_block_13:
  movq $1, rax
  cmpq $r1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.math.statistics.variance_block_15
  jmp std.math.statistics.variance_block_29
std.math.statistics.variance_block_15:
  jmp std.math.statistics.variance_block_15
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r13, rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  subq $r7, rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  imulq [rbp + -96], rax
  movq rax, [rbp + -104]
  movq [rbp + -96], rax
  imulq [rbp + -96], rax
  movq rax, [rbp + -112]
  movq $2, rax
  addq [rbp + -112], rax
  movq rax, [rbp + -120]
  jmp std.math.statistics.variance_block_24
std.math.statistics.variance_block_24:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -128]
  jmp std.math.statistics.variance_block_13
std.math.statistics.variance_block_29:
  movq $r1, rax
  movq rax, [rbp + -136]
  movq [rbp + -120], rax
  cqto
  movq [rbp + -136], rcx
  idivq rcx
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  jmp std.math.statistics.variance_epilogue
std.math.statistics.variance_epilogue:
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
.Lfunc_end_std.math.statistics.variance:

.globl std.math.quaternion.Quaternion.normalize
std.math.quaternion.Quaternion.normalize:
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
std.math.quaternion.Quaternion.normalize_entry:
  movq $0, rax
  jmp std.math.quaternion.Quaternion.normalize_epilogue
std.math.quaternion.Quaternion.normalize_epilogue:
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
.Lfunc_end_std.math.quaternion.Quaternion.normalize:

.globl std.math.trigonometry.acos
std.math.trigonometry.acos:
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
std.math.trigonometry.acos_entry:
std.math.trigonometry.acos_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.trigonometry.TrigFloat.init
  movq [rbp + -72], rcx
  call std.math.trigonometry.TrigFloat.acos
  movq $r3, rax
  jmp std.math.trigonometry.acos_epilogue
std.math.trigonometry.acos_epilogue:
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
.Lfunc_end_std.math.trigonometry.acos:

.globl std.math.arithmetic.Int.min
std.math.arithmetic.Int.min:
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
std.math.arithmetic.Int.min_entry:
  movq $0, rax
  jmp std.math.arithmetic.Int.min_epilogue
std.math.arithmetic.Int.min_epilogue:
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
.Lfunc_end_std.math.arithmetic.Int.min:

.globl std.math.trigonometry.TrigFloat.tan
std.math.trigonometry.TrigFloat.tan:
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
std.math.trigonometry.TrigFloat.tan_entry:
  movq $0, rax
  jmp std.math.trigonometry.TrigFloat.tan_epilogue
std.math.trigonometry.TrigFloat.tan_epilogue:
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
.Lfunc_end_std.math.trigonometry.TrigFloat.tan:

.globl std.math.trigonometry.TrigFloat.sin
std.math.trigonometry.TrigFloat.sin:
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
std.math.trigonometry.TrigFloat.sin_entry:
  movq $0, rax
  jmp std.math.trigonometry.TrigFloat.sin_epilogue
std.math.trigonometry.TrigFloat.sin_epilogue:
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
.Lfunc_end_std.math.trigonometry.TrigFloat.sin:

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

.globl std.math.index.median
std.math.index.median:
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
std.math.index.median_entry:
std.math.index.median_block_0:
  movq [rbp + -64], rcx
  call std.math.statistics.median
  movq $r1, rax
  jmp std.math.index.median_epilogue
std.math.index.median_epilogue:
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
.Lfunc_end_std.math.index.median:

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

.globl std.math.arithmetic.Int.abs
std.math.arithmetic.Int.abs:
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
std.math.arithmetic.Int.abs_entry:
  movq $0, rax
  jmp std.math.arithmetic.Int.abs_epilogue
std.math.arithmetic.Int.abs_epilogue:
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
.Lfunc_end_std.math.arithmetic.Int.abs:

.globl std.sort.quicksort
std.sort.quicksort:
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
std.sort.quicksort_entry:
std.sort.quicksort_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  cmpq $9, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.sort.quicksort_block_4
  jmp std.sort.quicksort_block_10
std.sort.quicksort_block_4:
  jmp std.sort.quicksort_block_4
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r8, rax
  subq $9, rax
  movq rax, $r10
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $r10, r8
  movq [rbp + -72], r9
  call std.sort._quicksort_range
  jmp std.sort.quicksort_block_10
std.sort.quicksort_block_10:
  movq $0, rax
  jmp std.sort.quicksort_epilogue
std.sort.quicksort_epilogue:
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
.Lfunc_end_std.sort.quicksort:

.globl std.math.index.sign
std.math.index.sign:
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
std.math.index.sign_entry:
std.math.index.sign_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.sign
  movq $r1, rax
  jmp std.math.index.sign_epilogue
std.math.index.sign_epilogue:
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
.Lfunc_end_std.math.index.sign:

.globl std.math.trigonometry.TrigFloat.acos
std.math.trigonometry.TrigFloat.acos:
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
std.math.trigonometry.TrigFloat.acos_entry:
  movq $0, rax
  jmp std.math.trigonometry.TrigFloat.acos_epilogue
std.math.trigonometry.TrigFloat.acos_epilogue:
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
.Lfunc_end_std.math.trigonometry.TrigFloat.acos:

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

.globl std.math.random.Random.next_float
std.math.random.Random.next_float:
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
std.math.random.Random.next_float_entry:
  movq $0, rax
  jmp std.math.random.Random.next_float_epilogue
std.math.random.Random.next_float_epilogue:
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
.Lfunc_end_std.math.random.Random.next_float:

.globl std.math.arithmetic.ceil
std.math.arithmetic.ceil:
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
std.math.arithmetic.ceil_entry:
std.math.arithmetic.ceil_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -72], rcx
  call std.math.arithmetic.Float.ceil
  movq $r3, rax
  jmp std.math.arithmetic.ceil_epilogue
std.math.arithmetic.ceil_epilogue:
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
.Lfunc_end_std.math.arithmetic.ceil:

.globl std.math.arithmetic.exp
std.math.arithmetic.exp:
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
std.math.arithmetic.exp_entry:
std.math.arithmetic.exp_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -72], rcx
  call std.math.arithmetic.Float.exp
  movq $r3, rax
  jmp std.math.arithmetic.exp_epilogue
std.math.arithmetic.exp_epilogue:
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
.Lfunc_end_std.math.arithmetic.exp:

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

.globl std.sort._mergesort_range
std.sort._mergesort_range:
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
  mov [rbp + -88], r9
std.sort._mergesort_range_entry:
std.sort._mergesort_range_block_0:
  movq [rbp + -72], rax
  cmpq [rbp + -80], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.sort._mergesort_range_block_2
  jmp std.sort._mergesort_range_block_13
std.sort._mergesort_range_block_2:
  jmp std.sort._mergesort_range_block_2
  movq [rbp + -72], rax
  addq [rbp + -80], rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rax, [rbp + -120]
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -120], r8
  movq [rbp + -88], r9
  call std.sort._mergesort_range
  movq [rbp + -120], rax
  addq $9, rax
  movq rax, [rbp + -128]
  movq [rbp + -64], rcx
  movq [rbp + -128], rdx
  movq [rbp + -80], r8
  movq [rbp + -88], r9
  call std.sort._mergesort_range
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -120], r8
  movq [rbp + -80], r9
  call std.sort._merge
  jmp std.sort._mergesort_range_block_13
std.sort._mergesort_range_block_13:
  movq $0, rax
  jmp std.sort._mergesort_range_epilogue
std.sort._mergesort_range_epilogue:
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
.Lfunc_end_std.sort._mergesort_range:

.globl std.math.random.Random.next_bytes
std.math.random.Random.next_bytes:
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
std.math.random.Random.next_bytes_entry:
  movq $0, rax
  jmp std.math.random.Random.next_bytes_epilogue
std.math.random.Random.next_bytes_epilogue:
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
.Lfunc_end_std.math.random.Random.next_bytes:

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

.globl std.math.arithmetic.sign
std.math.arithmetic.sign:
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
std.math.arithmetic.sign_entry:
std.math.arithmetic.sign_block_0:
  movq [rbp + -64], rax
  cmpq $2, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.math.arithmetic.sign_block_3
  jmp std.math.arithmetic.sign_block_5
std.math.arithmetic.sign_block_3:
  jmp std.math.arithmetic.sign_block_3
  movq $2, rax
  jmp std.math.arithmetic.sign_epilogue
std.math.arithmetic.sign_block_5:
  movq [rbp + -64], rax
  cmpq $2, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.math.arithmetic.sign_block_8
  jmp std.math.arithmetic.sign_block_11
std.math.arithmetic.sign_block_8:
  jmp std.math.arithmetic.sign_block_8
  movq $2, rax
  negq rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.math.arithmetic.sign_epilogue
std.math.arithmetic.sign_block_11:
  movq $2, rax
  jmp std.math.arithmetic.sign_epilogue
std.math.arithmetic.sign_epilogue:
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
.Lfunc_end_std.math.arithmetic.sign:

.globl std.math.vector4.Vector4.mag
std.math.vector4.Vector4.mag:
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
std.math.vector4.Vector4.mag_entry:
  movq $0, rax
  jmp std.math.vector4.Vector4.mag_epilogue
std.math.vector4.Vector4.mag_epilogue:
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
.Lfunc_end_std.math.vector4.Vector4.mag:

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

.globl std.math.index.sin
std.math.index.sin:
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
std.math.index.sin_entry:
std.math.index.sin_block_0:
  movq [rbp + -64], rcx
  call std.math.trigonometry.sin
  movq $r1, rax
  jmp std.math.index.sin_epilogue
std.math.index.sin_epilogue:
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
.Lfunc_end_std.math.index.sin:

.globl std.sort.sort
std.sort.sort:
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
std.sort.sort_entry:
std.sort.sort_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.sort.quicksort
  movq $0, rax
  jmp std.sort.sort_epilogue
std.sort.sort_epilogue:
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
.Lfunc_end_std.sort.sort:

.globl std.math.arithmetic.gcd
std.math.arithmetic.gcd:
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
std.math.arithmetic.gcd_entry:
std.math.arithmetic.gcd_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.abs_int
  movq [rbp + -72], rcx
  call std.math.arithmetic.abs_int
  jmp std.math.arithmetic.gcd_block_5
std.math.arithmetic.gcd_block_5:
  movq $r4, rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.math.arithmetic.gcd_block_8
  jmp std.math.arithmetic.gcd_block_13
std.math.arithmetic.gcd_block_8:
  jmp std.math.arithmetic.gcd_block_8
  movq $r2, rax
  cqto
  movq $r4, rcx
  idivq rcx
  movq rdx, $r10
  jmp std.math.arithmetic.gcd_block_5
std.math.arithmetic.gcd_block_13:
  movq $r4, rax
  jmp std.math.arithmetic.gcd_epilogue
std.math.arithmetic.gcd_epilogue:
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
.Lfunc_end_std.math.arithmetic.gcd:

.globl std.math.arithmetic.log
std.math.arithmetic.log:
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
std.math.arithmetic.log_entry:
std.math.arithmetic.log_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -72], rcx
  call std.math.arithmetic.Float.log
  movq $r3, rax
  jmp std.math.arithmetic.log_epilogue
std.math.arithmetic.log_epilogue:
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
.Lfunc_end_std.math.arithmetic.log:

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

.globl std.math.vector4.__init__
std.math.vector4.__init__:
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
std.math.vector4.__init___entry:
  movq $0, rax
  jmp std.math.vector4.__init___epilogue
std.math.vector4.__init___epilogue:
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
.Lfunc_end_std.math.vector4.__init__:

.globl std.sort._quicksort_range
std.sort._quicksort_range:
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
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.sort._quicksort_range_entry:
std.sort._quicksort_range_block_0:
  movq [rbp + -72], rax
  cmpq [rbp + -80], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.sort._quicksort_range_block_2
  jmp std.sort._quicksort_range_block_12
std.sort._quicksort_range_block_2:
  jmp std.sort._quicksort_range_block_2
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  movq [rbp + -88], r9
  call std.sort._partition
  movq $r7, rax
  subq $9, rax
  movq rax, $r10
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq $r10, r8
  movq [rbp + -88], r9
  call std.sort._quicksort_range
  movq $r7, rax
  addq $9, rax
  movq rax, $r14
  movq [rbp + -64], rcx
  movq $r14, rdx
  movq [rbp + -80], r8
  movq [rbp + -88], r9
  call std.sort._quicksort_range
  jmp std.sort._quicksort_range_block_12
std.sort._quicksort_range_block_12:
  movq $0, rax
  jmp std.sort._quicksort_range_epilogue
std.sort._quicksort_range_epilogue:
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
.Lfunc_end_std.sort._quicksort_range:

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

.globl std.math.trigonometry.__init__
std.math.trigonometry.__init__:
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
std.math.trigonometry.__init___entry:
  movq $0, rax
  jmp std.math.trigonometry.__init___epilogue
std.math.trigonometry.__init___epilogue:
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
.Lfunc_end_std.math.trigonometry.__init__:

.globl std.sort.__init__
std.sort.__init__:
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
std.sort.__init___entry:
  movq $0, rax
  jmp std.sort.__init___epilogue
std.sort.__init___epilogue:
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
.Lfunc_end_std.sort.__init__:

.globl std.math.quaternion.Quaternion.add
std.math.quaternion.Quaternion.add:
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
std.math.quaternion.Quaternion.add_entry:
  movq $0, rax
  jmp std.math.quaternion.Quaternion.add_epilogue
std.math.quaternion.Quaternion.add_epilogue:
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
.Lfunc_end_std.math.quaternion.Quaternion.add:

.globl std.math.quaternion.Quaternion.sub
std.math.quaternion.Quaternion.sub:
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
std.math.quaternion.Quaternion.sub_entry:
  movq $0, rax
  jmp std.math.quaternion.Quaternion.sub_epilogue
std.math.quaternion.Quaternion.sub_epilogue:
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
.Lfunc_end_std.math.quaternion.Quaternion.sub:

.globl std.math.random.__init__
std.math.random.__init__:
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
std.math.random.__init___entry:
  movq $0, rax
  jmp std.math.random.__init___epilogue
std.math.random.__init___epilogue:
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
.Lfunc_end_std.math.random.__init__:

.globl std.math.quaternion.Quaternion.mag
std.math.quaternion.Quaternion.mag:
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
std.math.quaternion.Quaternion.mag_entry:
  movq $0, rax
  jmp std.math.quaternion.Quaternion.mag_epilogue
std.math.quaternion.Quaternion.mag_epilogue:
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
.Lfunc_end_std.math.quaternion.Quaternion.mag:

.globl std.math.index.atan
std.math.index.atan:
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
std.math.index.atan_entry:
std.math.index.atan_block_0:
  movq [rbp + -64], rcx
  call std.math.trigonometry.atan
  movq $r1, rax
  jmp std.math.index.atan_epilogue
std.math.index.atan_epilogue:
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
.Lfunc_end_std.math.index.atan:

.globl std.math.quaternion.Quaternion.init
std.math.quaternion.Quaternion.init:
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
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.math.quaternion.Quaternion.init_entry:
  movq $0, rax
  jmp std.math.quaternion.Quaternion.init_epilogue
std.math.quaternion.Quaternion.init_epilogue:
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
.Lfunc_end_std.math.quaternion.Quaternion.init:

.globl std.math.vector2.Vector2.dot
std.math.vector2.Vector2.dot:
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
std.math.vector2.Vector2.dot_entry:
  movq $0, rax
  jmp std.math.vector2.Vector2.dot_epilogue
std.math.vector2.Vector2.dot_epilogue:
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
.Lfunc_end_std.math.vector2.Vector2.dot:

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

.globl std.math.index.Quaternion
std.math.index.Quaternion:
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
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.math.index.Quaternion_entry:
std.math.index.Quaternion_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -96], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -96], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  movq [rbp + -80], r9
  call std.math.quaternion.Quaternion.init
  movq [rbp + -96], rax
  jmp std.math.index.Quaternion_epilogue
std.math.index.Quaternion_epilogue:
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
.Lfunc_end_std.math.index.Quaternion:

.globl std.math.trigonometry.TrigFloat.asin
std.math.trigonometry.TrigFloat.asin:
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
std.math.trigonometry.TrigFloat.asin_entry:
  movq $0, rax
  jmp std.math.trigonometry.TrigFloat.asin_epilogue
std.math.trigonometry.TrigFloat.asin_epilogue:
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
.Lfunc_end_std.math.trigonometry.TrigFloat.asin:

.globl std.math.index.ceil
std.math.index.ceil:
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
std.math.index.ceil_entry:
std.math.index.ceil_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.ceil
  movq $r1, rax
  jmp std.math.index.ceil_epilogue
std.math.index.ceil_epilogue:
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
.Lfunc_end_std.math.index.ceil:

.globl std.sort.timsort
std.sort.timsort:
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
std.sort.timsort_entry:
std.sort.timsort_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.sort.stable_sort
  movq $0, rax
  jmp std.sort.timsort_epilogue
std.sort.timsort_epilogue:
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
.Lfunc_end_std.sort.timsort:

.globl std.math.trigonometry.TrigFloat.atan2
std.math.trigonometry.TrigFloat.atan2:
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
std.math.trigonometry.TrigFloat.atan2_entry:
  movq $0, rax
  jmp std.math.trigonometry.TrigFloat.atan2_epilogue
std.math.trigonometry.TrigFloat.atan2_epilogue:
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
.Lfunc_end_std.math.trigonometry.TrigFloat.atan2:

.globl std.math.vector3.Vector3.dot
std.math.vector3.Vector3.dot:
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
std.math.vector3.Vector3.dot_entry:
  movq $0, rax
  jmp std.math.vector3.Vector3.dot_epilogue
std.math.vector3.Vector3.dot_epilogue:
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
.Lfunc_end_std.math.vector3.Vector3.dot:

.globl std.math.random.SecureRandom.next_float
std.math.random.SecureRandom.next_float:
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
std.math.random.SecureRandom.next_float_entry:
  movq $0, rax
  jmp std.math.random.SecureRandom.next_float_epilogue
std.math.random.SecureRandom.next_float_epilogue:
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
.Lfunc_end_std.math.random.SecureRandom.next_float:

.globl std.math.index.log10
std.math.index.log10:
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
std.math.index.log10_entry:
std.math.index.log10_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.log10
  movq $r1, rax
  jmp std.math.index.log10_epilogue
std.math.index.log10_epilogue:
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
.Lfunc_end_std.math.index.log10:

.globl std.math.random.random_bool
std.math.random.random_bool:
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
std.math.random.random_bool_entry:
std.math.random.random_bool_block_0:
  movq $0, rcx
  call std.math.random.Random.next_bool
  movq $r1, rax
  jmp std.math.random.random_bool_epilogue
std.math.random.random_bool_epilogue:
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
.Lfunc_end_std.math.random.random_bool:

.globl std.math.vector3.Vector3.cross
std.math.vector3.Vector3.cross:
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
std.math.vector3.Vector3.cross_entry:
  movq $0, rax
  jmp std.math.vector3.Vector3.cross_epilogue
std.math.vector3.Vector3.cross_epilogue:
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
.Lfunc_end_std.math.vector3.Vector3.cross:

.globl std.math.vector4.Vector4.sub
std.math.vector4.Vector4.sub:
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
std.math.vector4.Vector4.sub_entry:
  movq $0, rax
  jmp std.math.vector4.Vector4.sub_epilogue
std.math.vector4.Vector4.sub_epilogue:
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
.Lfunc_end_std.math.vector4.Vector4.sub:

.globl std.math.vector3.__init__
std.math.vector3.__init__:
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
std.math.vector3.__init___entry:
  movq $0, rax
  jmp std.math.vector3.__init___epilogue
std.math.vector3.__init___epilogue:
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
.Lfunc_end_std.math.vector3.__init__:

.globl std.math.statistics.stddev
std.math.statistics.stddev:
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
std.math.statistics.stddev_entry:
std.math.statistics.stddev_block_0:
  movq [rbp + -64], rcx
  call std.math.statistics.variance
  movq $r1, rcx
  call std.math.arithmetic.sqrt
  movq $r2, rax
  jmp std.math.statistics.stddev_epilogue
std.math.statistics.stddev_epilogue:
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
.Lfunc_end_std.math.statistics.stddev:

.globl std.math.statistics.__init__
std.math.statistics.__init__:
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
std.math.statistics.__init___entry:
  movq $0, rax
  jmp std.math.statistics.__init___epilogue
std.math.statistics.__init___epilogue:
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
.Lfunc_end_std.math.statistics.__init__:

.globl std.math.vector2.Vector2.add
std.math.vector2.Vector2.add:
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
std.math.vector2.Vector2.add_entry:
  movq $0, rax
  jmp std.math.vector2.Vector2.add_epilogue
std.math.vector2.Vector2.add_epilogue:
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
.Lfunc_end_std.math.vector2.Vector2.add:

.globl std.math.random.Random.range_float
std.math.random.Random.range_float:
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
std.math.random.Random.range_float_entry:
  movq $0, rax
  jmp std.math.random.Random.range_float_epilogue
std.math.random.Random.range_float_epilogue:
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
.Lfunc_end_std.math.random.Random.range_float:

.globl std.math.vector2.Vector2.scale
std.math.vector2.Vector2.scale:
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
std.math.vector2.Vector2.scale_entry:
  movq $0, rax
  jmp std.math.vector2.Vector2.scale_epilogue
std.math.vector2.Vector2.scale_epilogue:
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
.Lfunc_end_std.math.vector2.Vector2.scale:

.globl std.math.vector3.Vector3.mag
std.math.vector3.Vector3.mag:
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
std.math.vector3.Vector3.mag_entry:
  movq $0, rax
  jmp std.math.vector3.Vector3.mag_epilogue
std.math.vector3.Vector3.mag_epilogue:
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
.Lfunc_end_std.math.vector3.Vector3.mag:

.globl std.math.vector2.Vector2.mag
std.math.vector2.Vector2.mag:
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
std.math.vector2.Vector2.mag_entry:
  movq $0, rax
  jmp std.math.vector2.Vector2.mag_epilogue
std.math.vector2.Vector2.mag_epilogue:
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
.Lfunc_end_std.math.vector2.Vector2.mag:

.globl std.math.vector2.Vector2.normalize
std.math.vector2.Vector2.normalize:
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
std.math.vector2.Vector2.normalize_entry:
  movq $0, rax
  jmp std.math.vector2.Vector2.normalize_epilogue
std.math.vector2.Vector2.normalize_epilogue:
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
.Lfunc_end_std.math.vector2.Vector2.normalize:

.globl std.math.vector2.Vector2.init
std.math.vector2.Vector2.init:
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
std.math.vector2.Vector2.init_entry:
  movq $0, rax
  jmp std.math.vector2.Vector2.init_epilogue
std.math.vector2.Vector2.init_epilogue:
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
.Lfunc_end_std.math.vector2.Vector2.init:

.globl test_constants
test_constants:
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
test_constants_entry:
test_constants_block_0:
  movq [rel str_const_28], rcx
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
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r4, rcx
  movq [rbp + -96], rdx
  call lm_assert
  movq $0, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r9, rcx
  movq [rbp + -104], rdx
  call lm_assert
  movq $0, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r14, rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq $9, rax
  jmp test_constants_epilogue
test_constants_epilogue:
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
.Lfunc_end_test_constants:

.globl test_arithmetic
test_arithmetic:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 424
test_arithmetic_entry:
test_arithmetic_block_0:
  movq [rel str_const_32], rcx
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
  movq $2, rax
  negq rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.math.index.abs
  movq $r4, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq $81, rax
  negq rax
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  call std.math.index.abs_int
  movq $r11, rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq $97, rcx
  movq $145, rdx
  call std.math.index.gcd
  movq $r18, rax
  cmpq $49, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $97, rcx
  movq $145, rdx
  call std.math.index.lcm
  movq $r25, rax
  cmpq $289, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq $41, rcx
  call std.math.index.factorial
  movq $r31, rax
  cmpq $961, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq $41, rcx
  movq $17, rdx
  call std.math.index.permutations
  movq $r38, rax
  cmpq $161, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq $41, rcx
  movq $17, rdx
  call std.math.index.combinations
  movq $r45, rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq $2, rcx
  movq $2, rdx
  call std.math.index.min
  movq $r52, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  movq $2, rcx
  movq $2, rdx
  call std.math.index.max
  movq $r59, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq $2, rcx
  movq $2, rdx
  movq $2, r8
  call std.math.index.clamp
  movq $r67, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -256], rcx
  movq [rbp + -264], rdx
  call lm_assert
  movq $2, rax
  negq rax
  movq rax, [rbp + -272]
  movq [rbp + -272], rcx
  movq $2, rdx
  movq $2, r8
  call std.math.index.clamp
  movq $r76, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -280]
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -280], rcx
  movq [rbp + -288], rdx
  call lm_assert
  movq $2, rax
  negq rax
  movq rax, [rbp + -296]
  movq [rbp + -296], rcx
  call std.math.index.sign
  movq $2, rax
  negq rax
  movq rax, [rbp + -304]
  movq $r83, rax
  cmpq [rbp + -304], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -312]
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -312], rcx
  movq [rbp + -320], rdx
  call lm_assert
  movq $2, rcx
  movq $2, rdx
  movq $2, r8
  call std.math.index.lerp
  movq $r92, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -328]
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -328], rcx
  movq [rbp + -336], rdx
  call lm_assert
  movq $2, rcx
  call std.math.index.floor
  movq $r98, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -344]
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -344], rcx
  movq [rbp + -352], rdx
  call lm_assert
  movq $2, rcx
  call std.math.index.ceil
  movq $r104, rax
  cmpq $49, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -360], rcx
  movq [rbp + -368], rdx
  call lm_assert
  movq $2, rcx
  call std.math.index.round
  movq $r110, rax
  cmpq $49, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -376]
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -376], rcx
  movq [rbp + -384], rdx
  call lm_assert
  movq $2, rcx
  call std.math.index.trunc
  movq $r116, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -392], rcx
  movq [rbp + -400], rdx
  call lm_assert
  movq $2, rcx
  call std.math.index.fract
  movq $r122, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq $r124, rcx
  movq [rbp + -408], rdx
  call lm_assert
  movq $2, rcx
  call std.math.index.sqrt
  movq $r128, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq $r130, rcx
  movq [rbp + -416], rdx
  call lm_assert
  movq $2, rcx
  call std.math.index.cbrt
  movq $r134, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq $r136, rcx
  movq [rbp + -424], rdx
  call lm_assert
  movq $2, rcx
  movq $2, rdx
  call std.math.index.hypot
  movq $r141, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq $r143, rcx
  movq [rbp + -432], rdx
  call lm_assert
  movq $2, rcx
  call std.math.index.exp
  movq $r147, rcx
  movq $2, rdx
  call nearly_equal
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq $r149, rcx
  movq [rbp + -440], rdx
  call lm_assert
  movq $9, rax
  jmp test_arithmetic_epilogue
test_arithmetic_epilogue:
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
.Lfunc_end_test_arithmetic:

.globl std.math.vector2.__init__
std.math.vector2.__init__:
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
std.math.vector2.__init___entry:
  movq $0, rax
  jmp std.math.vector2.__init___epilogue
std.math.vector2.__init___epilogue:
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
.Lfunc_end_std.math.vector2.__init__:

.globl std.math.vector4.Vector4.add
std.math.vector4.Vector4.add:
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
std.math.vector4.Vector4.add_entry:
  movq $0, rax
  jmp std.math.vector4.Vector4.add_epilogue
std.math.vector4.Vector4.add_epilogue:
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
.Lfunc_end_std.math.vector4.Vector4.add:

.globl std.math.vector4.Vector4.scale
std.math.vector4.Vector4.scale:
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
std.math.vector4.Vector4.scale_entry:
  movq $0, rax
  jmp std.math.vector4.Vector4.scale_epilogue
std.math.vector4.Vector4.scale_epilogue:
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
.Lfunc_end_std.math.vector4.Vector4.scale:

.globl std.math.vector4.Vector4.init
std.math.vector4.Vector4.init:
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
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.math.vector4.Vector4.init_entry:
  movq $0, rax
  jmp std.math.vector4.Vector4.init_epilogue
std.math.vector4.Vector4.init_epilogue:
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
.Lfunc_end_std.math.vector4.Vector4.init:

.globl std.math.matrix.Matrix.get
std.math.matrix.Matrix.get:
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
std.math.matrix.Matrix.get_entry:
  movq $0, rax
  jmp std.math.matrix.Matrix.get_epilogue
std.math.matrix.Matrix.get_epilogue:
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
.Lfunc_end_std.math.matrix.Matrix.get:

.globl std.sort._compare
std.sort._compare:
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
  mov [rbp + -88], r9
std.sort._compare_entry:
std.sort._compare_block_0:
  movq [rbp + -88], rax
  cmpq $2, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.sort._compare_block_4
  jmp std.sort._compare_block_9
std.sort._compare_block_4:
  jmp std.sort._compare_block_4
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call 
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  movq rax, [rbp + -112]
  jmp std.sort._compare_block_25
std.sort._compare_block_9:
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.sort._compare_block_11
  jmp std.sort._compare_block_15
std.sort._compare_block_11:
  jmp std.sort._compare_block_11
  movq $9, rax
  negq rax
  movq rax, [rbp + -128]
  jmp std.sort._compare_block_24
std.sort._compare_block_15:
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  setg al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne std.sort._compare_block_17
  jmp std.sort._compare_block_20
std.sort._compare_block_17:
  jmp std.sort._compare_block_17
  jmp std.sort._compare_block_23
std.sort._compare_block_20:
  jmp std.sort._compare_block_23
std.sort._compare_block_23:
  jmp std.sort._compare_block_24
std.sort._compare_block_24:
  jmp std.sort._compare_block_25
std.sort._compare_block_25:
  movq [rbp + -80], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  testq rax, rax
  jne std.sort._compare_block_28
  jmp std.sort._compare_block_31
std.sort._compare_block_28:
  jmp std.sort._compare_block_28
  movq $1, rax
  subq $1, rax
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  jmp std.sort._compare_epilogue
std.sort._compare_block_31:
  movq $1, rax
  jmp std.sort._compare_epilogue
std.sort._compare_epilogue:
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
.Lfunc_end_std.sort._compare:

.globl std.math.matrix.Matrix.set
std.math.matrix.Matrix.set:
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
  mov [rbp + -88], r9
std.math.matrix.Matrix.set_entry:
  movq $0, rax
  jmp std.math.matrix.Matrix.set_epilogue
std.math.matrix.Matrix.set_epilogue:
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
.Lfunc_end_std.math.matrix.Matrix.set:

.globl std.math.matrix.Matrix.init
std.math.matrix.Matrix.init:
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
std.math.matrix.Matrix.init_entry:
  movq $0, rax
  jmp std.math.matrix.Matrix.init_epilogue
std.math.matrix.Matrix.init_epilogue:
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
.Lfunc_end_std.math.matrix.Matrix.init:

.globl std.math.index.cbrt
std.math.index.cbrt:
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
std.math.index.cbrt_entry:
std.math.index.cbrt_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.cbrt
  movq $r1, rax
  jmp std.math.index.cbrt_epilogue
std.math.index.cbrt_epilogue:
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
.Lfunc_end_std.math.index.cbrt:

.globl std.math.index.__init__
std.math.index.__init__:
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
std.math.index.__init___entry:
  movq $0, rax
  jmp std.math.index.__init___epilogue
std.math.index.__init___epilogue:
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
.Lfunc_end_std.math.index.__init__:

.globl std.math.constants.__init__
std.math.constants.__init__:
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
std.math.constants.__init___entry:
  movq $0, rax
  jmp std.math.constants.__init___epilogue
std.math.constants.__init___epilogue:
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
.Lfunc_end_std.math.constants.__init__:

.globl std.math.index.permutations
std.math.index.permutations:
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
std.math.index.permutations_entry:
std.math.index.permutations_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.math.arithmetic.permutations
  movq $r2, rax
  jmp std.math.index.permutations_epilogue
std.math.index.permutations_epilogue:
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
.Lfunc_end_std.math.index.permutations:

.globl std.math.trigonometry.sinh
std.math.trigonometry.sinh:
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
std.math.trigonometry.sinh_entry:
std.math.trigonometry.sinh_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.trigonometry.TrigFloat.init
  movq [rbp + -72], rcx
  call std.math.trigonometry.TrigFloat.sinh
  movq $r3, rax
  jmp std.math.trigonometry.sinh_epilogue
std.math.trigonometry.sinh_epilogue:
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
.Lfunc_end_std.math.trigonometry.sinh:

.globl std.math.index.trunc
std.math.index.trunc:
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
std.math.index.trunc_entry:
std.math.index.trunc_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.trunc
  movq $r1, rax
  jmp std.math.index.trunc_epilogue
std.math.index.trunc_epilogue:
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
.Lfunc_end_std.math.index.trunc:

.globl std.math.index.random_float
std.math.index.random_float:
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
std.math.index.random_float_entry:
std.math.index.random_float_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.math.random.random_float
  movq $r2, rax
  jmp std.math.index.random_float_epilogue
std.math.index.random_float_epilogue:
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
.Lfunc_end_std.math.index.random_float:

.globl std.math.vector3.Vector3.init
std.math.vector3.Vector3.init:
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
  mov [rbp + -88], r9
std.math.vector3.Vector3.init_entry:
  movq $0, rax
  jmp std.math.vector3.Vector3.init_epilogue
std.math.vector3.Vector3.init_epilogue:
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
.Lfunc_end_std.math.vector3.Vector3.init:

.globl std.math.index.Vector2
std.math.index.Vector2:
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
std.math.index.Vector2_entry:
std.math.index.Vector2_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.math.vector2.Vector2.init
  movq [rbp + -80], rax
  jmp std.math.index.Vector2_epilogue
std.math.index.Vector2_epilogue:
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
.Lfunc_end_std.math.index.Vector2:

.globl std.math.index.Vector3
std.math.index.Vector3:
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
std.math.index.Vector3_entry:
std.math.index.Vector3_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  movq [rbp + -80], r9
  call std.math.vector3.Vector3.init
  movq [rbp + -88], rax
  jmp std.math.index.Vector3_epilogue
std.math.index.Vector3_epilogue:
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
.Lfunc_end_std.math.index.Vector3:

.globl std.math.index.Vector4
std.math.index.Vector4:
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
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.math.index.Vector4_entry:
std.math.index.Vector4_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -96], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -96], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  movq [rbp + -80], r9
  call std.math.vector4.Vector4.init
  movq [rbp + -96], rax
  jmp std.math.index.Vector4_epilogue
std.math.index.Vector4_epilogue:
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
.Lfunc_end_std.math.index.Vector4:

.globl std.math.index.abs_int
std.math.index.abs_int:
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
std.math.index.abs_int_entry:
std.math.index.abs_int_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.abs_int
  movq $r1, rax
  jmp std.math.index.abs_int_epilogue
std.math.index.abs_int_epilogue:
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
.Lfunc_end_std.math.index.abs_int:

.globl std.math.index.lcm
std.math.index.lcm:
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
std.math.index.lcm_entry:
std.math.index.lcm_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.math.arithmetic.lcm
  movq $r2, rax
  jmp std.math.index.lcm_epilogue
std.math.index.lcm_epilogue:
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
.Lfunc_end_std.math.index.lcm:

.globl std.math.index.cos
std.math.index.cos:
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
std.math.index.cos_entry:
std.math.index.cos_block_0:
  movq [rbp + -64], rcx
  call std.math.trigonometry.cos
  movq $r1, rax
  jmp std.math.index.cos_epilogue
std.math.index.cos_epilogue:
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
.Lfunc_end_std.math.index.cos:

.globl std.math.index.factorial
std.math.index.factorial:
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
std.math.index.factorial_entry:
std.math.index.factorial_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.factorial
  movq $r1, rax
  jmp std.math.index.factorial_epilogue
std.math.index.factorial_epilogue:
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
.Lfunc_end_std.math.index.factorial:

.globl std.math.trigonometry.TrigFloat.cosh
std.math.trigonometry.TrigFloat.cosh:
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
std.math.trigonometry.TrigFloat.cosh_entry:
  movq $0, rax
  jmp std.math.trigonometry.TrigFloat.cosh_epilogue
std.math.trigonometry.TrigFloat.cosh_epilogue:
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
.Lfunc_end_std.math.trigonometry.TrigFloat.cosh:

.globl std.math.vector4.Vector4.dot
std.math.vector4.Vector4.dot:
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
std.math.vector4.Vector4.dot_entry:
  movq $0, rax
  jmp std.math.vector4.Vector4.dot_epilogue
std.math.vector4.Vector4.dot_epilogue:
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
.Lfunc_end_std.math.vector4.Vector4.dot:

.globl std.math.index.max
std.math.index.max:
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
std.math.index.max_entry:
std.math.index.max_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.math.arithmetic.max
  movq $r2, rax
  jmp std.math.index.max_epilogue
std.math.index.max_epilogue:
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
.Lfunc_end_std.math.index.max:

.globl std.math.index.Matrix
std.math.index.Matrix:
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
std.math.index.Matrix_entry:
std.math.index.Matrix_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.math.matrix.Matrix.init
  movq $0, rax
  jmp std.math.index.Matrix_epilogue
std.math.index.Matrix_epilogue:
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
.Lfunc_end_std.math.index.Matrix:

.globl std.sort.stable_sort
std.sort.stable_sort:
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
std.sort.stable_sort_entry:
std.sort.stable_sort_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.sort.mergesort
  movq $0, rax
  jmp std.sort.stable_sort_epilogue
std.sort.stable_sort_epilogue:
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
.Lfunc_end_std.sort.stable_sort:

.globl std.math.index.clamp
std.math.index.clamp:
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
std.math.index.clamp_entry:
std.math.index.clamp_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.math.arithmetic.clamp
  movq $r3, rax
  jmp std.math.index.clamp_epilogue
std.math.index.clamp_epilogue:
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
.Lfunc_end_std.math.index.clamp:

.globl std.math.index.floor
std.math.index.floor:
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
std.math.index.floor_entry:
std.math.index.floor_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.floor
  movq $r1, rax
  jmp std.math.index.floor_epilogue
std.math.index.floor_epilogue:
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
.Lfunc_end_std.math.index.floor:

.globl std.math.index.round
std.math.index.round:
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
std.math.index.round_entry:
std.math.index.round_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.round
  movq $r1, rax
  jmp std.math.index.round_epilogue
std.math.index.round_epilogue:
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
.Lfunc_end_std.math.index.round:

.globl std.math.index.pow
std.math.index.pow:
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
std.math.index.pow_entry:
std.math.index.pow_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.math.arithmetic.pow
  movq $r2, rax
  jmp std.math.index.pow_epilogue
std.math.index.pow_epilogue:
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
.Lfunc_end_std.math.index.pow:

.globl std.math.index.random_string
std.math.index.random_string:
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
std.math.index.random_string_entry:
std.math.index.random_string_block_0:
  movq [rbp + -64], rcx
  call std.math.random.random_string
  movq $r1, rax
  jmp std.math.index.random_string_epilogue
std.math.index.random_string_epilogue:
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
.Lfunc_end_std.math.index.random_string:

.globl std.math.arithmetic.Int.max
std.math.arithmetic.Int.max:
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
std.math.arithmetic.Int.max_entry:
  movq $0, rax
  jmp std.math.arithmetic.Int.max_epilogue
std.math.arithmetic.Int.max_epilogue:
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
.Lfunc_end_std.math.arithmetic.Int.max:

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

.globl std.math.index.fract
std.math.index.fract:
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
std.math.index.fract_entry:
std.math.index.fract_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.fract
  movq $r1, rax
  jmp std.math.index.fract_epilogue
std.math.index.fract_epilogue:
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
.Lfunc_end_std.math.index.fract:

.globl std.math.index.hypot
std.math.index.hypot:
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
std.math.index.hypot_entry:
std.math.index.hypot_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.math.arithmetic.hypot
  movq $r2, rax
  jmp std.math.index.hypot_epilogue
std.math.index.hypot_epilogue:
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
.Lfunc_end_std.math.index.hypot:

.globl std.math.index.log2
std.math.index.log2:
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
std.math.index.log2_entry:
std.math.index.log2_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.log2
  movq $r1, rax
  jmp std.math.index.log2_epilogue
std.math.index.log2_epilogue:
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
.Lfunc_end_std.math.index.log2:

.globl std.math.random.Random.range_int
std.math.random.Random.range_int:
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
std.math.random.Random.range_int_entry:
  movq $0, rax
  jmp std.math.random.Random.range_int_epilogue
std.math.random.Random.range_int_epilogue:
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
.Lfunc_end_std.math.random.Random.range_int:

.globl std.math.index.exp
std.math.index.exp:
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
std.math.index.exp_entry:
std.math.index.exp_block_0:
  movq [rbp + -64], rcx
  call std.math.arithmetic.exp
  movq $r1, rax
  jmp std.math.index.exp_epilogue
std.math.index.exp_epilogue:
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
.Lfunc_end_std.math.index.exp:

.globl std.math.index.asin
std.math.index.asin:
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
std.math.index.asin_entry:
std.math.index.asin_block_0:
  movq [rbp + -64], rcx
  call std.math.trigonometry.asin
  movq $r1, rax
  jmp std.math.index.asin_epilogue
std.math.index.asin_epilogue:
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
.Lfunc_end_std.math.index.asin:

.globl std.math.index.atan2
std.math.index.atan2:
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
std.math.index.atan2_entry:
std.math.index.atan2_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.math.trigonometry.atan2
  movq $r2, rax
  jmp std.math.index.atan2_epilogue
std.math.index.atan2_epilogue:
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
.Lfunc_end_std.math.index.atan2:

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

.globl std.math.index.cosh
std.math.index.cosh:
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
std.math.index.cosh_entry:
std.math.index.cosh_block_0:
  movq [rbp + -64], rcx
  call std.math.trigonometry.cosh
  movq $r1, rax
  jmp std.math.index.cosh_epilogue
std.math.index.cosh_epilogue:
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
.Lfunc_end_std.math.index.cosh:

.globl std.math.index.tanh
std.math.index.tanh:
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
std.math.index.tanh_entry:
std.math.index.tanh_block_0:
  movq [rbp + -64], rcx
  call std.math.trigonometry.tanh
  movq $r1, rax
  jmp std.math.index.tanh_epilogue
std.math.index.tanh_epilogue:
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
.Lfunc_end_std.math.index.tanh:

.globl test_random
test_random:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 168
test_random_entry:
test_random_block_0:
  movq [rel str_const_55], rcx
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
  call std.math.index.random_int
  movq $r4, rax
  cmpq $9, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne test_random_block_10
  jmp test_random_block_14
test_random_block_10:
  jmp test_random_block_10
  movq $r4, rax
  cmpq $81, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -104]
  jmp test_random_block_14
test_random_block_14:
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq $2, rcx
  movq $2, rdx
  call std.math.index.random_float
  movq $r15, rax
  cmpq $2, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne test_random_block_24
  jmp test_random_block_28
test_random_block_24:
  jmp test_random_block_24
  movq $r15, rax
  cmpq $2, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -128]
  jmp test_random_block_28
test_random_block_28:
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  call std.math.index.random_bool
  movq $r24, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  testq rax, rax
  jne test_random_block_40
  jmp test_random_block_36
test_random_block_36:
  jmp test_random_block_36
  movq $r24, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  jmp test_random_block_40
test_random_block_40:
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq $41, rcx
  call std.math.index.random_string
  movq $r34, rcx
  call lm_list_len
  movq $r36, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call lm_assert
  movq $9, rax
  jmp test_random_epilogue
test_random_epilogue:
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
.Lfunc_end_test_random:

.globl std.math.index.sum
std.math.index.sum:
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
std.math.index.sum_entry:
std.math.index.sum_block_0:
  movq [rbp + -64], rcx
  call std.math.statistics.sum
  movq $r1, rax
  jmp std.math.index.sum_epilogue
std.math.index.sum_epilogue:
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
.Lfunc_end_std.math.index.sum:

.globl std.math.index.mean
std.math.index.mean:
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
std.math.index.mean_entry:
std.math.index.mean_block_0:
  movq [rbp + -64], rcx
  call std.math.statistics.mean
  movq $r1, rax
  jmp std.math.index.mean_epilogue
std.math.index.mean_epilogue:
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
.Lfunc_end_std.math.index.mean:

.globl std.math.index.random_int
std.math.index.random_int:
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
std.math.index.random_int_entry:
std.math.index.random_int_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.math.random.random_int
  movq $r2, rax
  jmp std.math.index.random_int_epilogue
std.math.index.random_int_epilogue:
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
.Lfunc_end_std.math.index.random_int:

.globl std.math.index.random_bool
std.math.index.random_bool:
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
std.math.index.random_bool_entry:
std.math.index.random_bool_block_0:
  call std.math.random.random_bool
  movq $0, rax
  jmp std.math.index.random_bool_epilogue
std.math.index.random_bool_epilogue:
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
.Lfunc_end_std.math.index.random_bool:

.globl std.sort._swap
std.sort._swap:
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
std.sort._swap_entry:
std.sort._swap_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq [rbp + -80], rdx
  call lm_list_get
  movq $0, rax
  jmp std.sort._swap_epilogue
std.sort._swap_epilogue:
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
.Lfunc_end_std.sort._swap:

.globl std.sort.insertion_sort
std.sort.insertion_sort:
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
std.sort.insertion_sort_entry:
std.sort.insertion_sort_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.sort.insertion_sort_block_4
std.sort.insertion_sort_block_4:
  movq $9, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.sort.insertion_sort_block_6
  jmp std.sort.insertion_sort_block_41
std.sort.insertion_sort_block_6:
  jmp std.sort.insertion_sort_block_6
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  movq $9, rax
  subq $9, rax
  movq rax, [rbp + -96]
  jmp std.sort.insertion_sort_block_12
std.sort.insertion_sort_block_12:
  movq [rbp + -96], rax
  cmpq $1, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.sort.insertion_sort_block_16
  jmp std.sort.insertion_sort_block_22
std.sort.insertion_sort_block_16:
  jmp std.sort.insertion_sort_block_16
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call lm_list_get
  movq $r16, rcx
  movq $r8, rdx
  movq [rbp + -72], r8
  movq [rbp + -80], r9
  call std.sort._compare
  movq $r17, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -112]
  jmp std.sort.insertion_sort_block_22
std.sort.insertion_sort_block_22:
  movq [rbp + -112], rax
  testq rax, rax
  jne std.sort.insertion_sort_block_23
  jmp std.sort.insertion_sort_block_32
std.sort.insertion_sort_block_23:
  jmp std.sort.insertion_sort_block_23
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call lm_list_get
  movq [rbp + -96], rax
  addq $9, rax
  movq rax, [rbp + -120]
  movq [rbp + -96], rax
  subq $9, rax
  movq rax, [rbp + -128]
  jmp std.sort.insertion_sort_block_12
std.sort.insertion_sort_block_32:
  movq [rbp + -128], rax
  addq $9, rax
  movq rax, [rbp + -136]
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.sort.insertion_sort_block_4
std.sort.insertion_sort_block_41:
  movq $0, rax
  jmp std.sort.insertion_sort_epilogue
std.sort.insertion_sort_epilogue:
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
.Lfunc_end_std.sort.insertion_sort:

.globl std.sort._heapify
std.sort._heapify:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 168
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.sort._heapify_entry:
std.sort._heapify_block_0:
  movq $17, rax
  imulq [rbp + -80], rax
  movq rax, [rbp + -104]
  movq $17, rax
  imulq [rbp + -80], rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  addq $9, rax
  movq rax, [rbp + -120]
  movq $17, rax
  imulq [rbp + -80], rax
  movq rax, [rbp + -128]
  movq $17, rax
  imulq [rbp + -80], rax
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  addq $17, rax
  movq rax, [rbp + -144]
  movq [rbp + -120], rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne std.sort._heapify_block_20
  jmp std.sort._heapify_block_27
std.sort._heapify_block_20:
  jmp std.sort._heapify_block_20
  movq [rbp + -64], rcx
  movq [rbp + -120], rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq [rbp + -80], rdx
  call lm_list_get
  movq $r24, rcx
  movq $r25, rdx
  movq [rbp + -88], r8
  movq [rbp + -96], r9
  call std.sort._compare
  movq $r26, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -160]
  jmp std.sort._heapify_block_27
std.sort._heapify_block_27:
  movq [rbp + -160], rax
  testq rax, rax
  jne std.sort._heapify_block_28
  jmp std.sort._heapify_block_30
std.sort._heapify_block_28:
  jmp std.sort._heapify_block_28
  jmp std.sort._heapify_block_30
std.sort._heapify_block_30:
  movq [rbp + -144], rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  testq rax, rax
  jne std.sort._heapify_block_33
  jmp std.sort._heapify_block_40
std.sort._heapify_block_33:
  jmp std.sort._heapify_block_33
  movq [rbp + -64], rcx
  movq [rbp + -144], rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq [rbp + -120], rdx
  call lm_list_get
  movq $r32, rcx
  movq $r33, rdx
  movq [rbp + -88], r8
  movq [rbp + -96], r9
  call std.sort._compare
  movq $r34, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -176]
  jmp std.sort._heapify_block_40
std.sort._heapify_block_40:
  movq [rbp + -176], rax
  testq rax, rax
  jne std.sort._heapify_block_41
  jmp std.sort._heapify_block_43
std.sort._heapify_block_41:
  jmp std.sort._heapify_block_41
  jmp std.sort._heapify_block_43
std.sort._heapify_block_43:
  movq [rbp + -144], rax
  cmpq [rbp + -80], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  testq rax, rax
  jne std.sort._heapify_block_45
  jmp std.sort._heapify_block_48
std.sort._heapify_block_45:
  jmp std.sort._heapify_block_45
  movq [rbp + -64], rcx
  movq [rbp + -80], rdx
  movq [rbp + -144], r8
  call std.sort._swap
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -144], r8
  movq [rbp + -88], r9
  call std.sort._heapify
  jmp std.sort._heapify_block_48
std.sort._heapify_block_48:
  movq $0, rax
  jmp std.sort._heapify_epilogue
std.sort._heapify_epilogue:
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
.Lfunc_end_std.sort._heapify:

.globl std.math.random.random_string
std.math.random.random_string:
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
std.math.random.random_string_entry:
std.math.random.random_string_block_0:
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $0, rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.math.random.Random.next_string
  movq $r3, rax
  jmp std.math.random.random_string_epilogue
std.math.random.random_string_epilogue:
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
.Lfunc_end_std.math.random.random_string:

.globl std.sort.heapsort
std.sort.heapsort:
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
std.sort.heapsort_entry:
std.sort.heapsort_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  cmpq $9, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.sort.heapsort_block_5
  jmp std.sort.heapsort_block_6
std.sort.heapsort_block_5:
  jmp std.sort.heapsort_block_5
  movq $0, rax
  jmp std.sort.heapsort_epilogue
std.sort.heapsort_block_6:
  movq $r3, rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rax, $r9
  movq $r9, rax
  subq $9, rax
  movq rax, $r11
  jmp std.sort.heapsort_block_12
std.sort.heapsort_block_12:
  movq $r11, rax
  cmpq $1, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.sort.heapsort_block_15
  jmp std.sort.heapsort_block_20
std.sort.heapsort_block_15:
  jmp std.sort.heapsort_block_15
  movq [rbp + -64], rcx
  movq $r3, rdx
  movq $r11, r8
  movq [rbp + -72], r9
  call std.sort._heapify
  movq $r11, rax
  subq $9, rax
  movq rax, $r18
  jmp std.sort.heapsort_block_12
std.sort.heapsort_block_20:
  movq $r3, rax
  subq $9, rax
  movq rax, $r20
  jmp std.sort.heapsort_block_24
std.sort.heapsort_block_24:
  movq $r20, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.sort.heapsort_block_27
  jmp std.sort.heapsort_block_35
std.sort.heapsort_block_27:
  jmp std.sort.heapsort_block_27
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $r20, r8
  call std.sort._swap
  movq [rbp + -64], rcx
  movq $r20, rdx
  movq $1, r8
  movq [rbp + -72], r9
  call std.sort._heapify
  movq $r20, rax
  subq $9, rax
  movq rax, $r29
  jmp std.sort.heapsort_block_24
std.sort.heapsort_block_35:
  movq [rbp + -72], rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.sort.heapsort_block_38
  jmp std.sort.heapsort_block_39
std.sort.heapsort_block_38:
  jmp std.sort.heapsort_block_38
  movq $0, rax
  jmp std.sort.heapsort_epilogue
std.sort.heapsort_block_39:
  movq $r3, rax
  subq $9, rax
  movq rax, $r35
  jmp std.sort.heapsort_block_44
std.sort.heapsort_block_44:
  movq $1, rax
  cmpq $r35, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.sort.heapsort_block_46
  jmp std.sort.heapsort_block_55
std.sort.heapsort_block_46:
  jmp std.sort.heapsort_block_46
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $r35, r8
  call std.sort._swap
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -128]
  movq $r35, rax
  subq $9, rax
  movq rax, $r44
  jmp std.sort.heapsort_block_44
std.sort.heapsort_block_55:
  movq $0, rax
  jmp std.sort.heapsort_epilogue
std.sort.heapsort_epilogue:
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
.Lfunc_end_std.sort.heapsort:

.globl std.sort.counting_sort
std.sort.counting_sort:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 168
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.sort.counting_sort_entry:
std.sort.counting_sort_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r2, rax
  cmpq $9, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.sort.counting_sort_block_5
  jmp std.sort.counting_sort_block_6
std.sort.counting_sort_block_5:
  jmp std.sort.counting_sort_block_5
  movq $0, rax
  jmp std.sort.counting_sort_epilogue
std.sort.counting_sort_block_6:
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  jmp std.sort.counting_sort_block_14
std.sort.counting_sort_block_14:
  movq $9, rax
  cmpq $r2, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.sort.counting_sort_block_16
  jmp std.sort.counting_sort_block_33
std.sort.counting_sort_block_16:
  jmp std.sort.counting_sort_block_16
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  movq $r16, rax
  cmpq $r8, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.sort.counting_sort_block_19
  jmp std.sort.counting_sort_block_22
std.sort.counting_sort_block_19:
  jmp std.sort.counting_sort_block_19
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  jmp std.sort.counting_sort_block_22
std.sort.counting_sort_block_22:
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  movq $r20, rax
  cmpq $r11, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.sort.counting_sort_block_25
  jmp std.sort.counting_sort_block_28
std.sort.counting_sort_block_25:
  jmp std.sort.counting_sort_block_25
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  jmp std.sort.counting_sort_block_28
std.sort.counting_sort_block_28:
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.sort.counting_sort_block_14
std.sort.counting_sort_block_33:
  movq $0, rcx
  call lm_list_new
  jmp std.sort.counting_sort_block_38
std.sort.counting_sort_block_38:
  movq $r23, rax
  subq $r19, rax
  movq rax, $r30
  movq $1, rax
  cmpq $r30, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.sort.counting_sort_block_41
  jmp std.sort.counting_sort_block_48
std.sort.counting_sort_block_41:
  jmp std.sort.counting_sort_block_41
  movq $r27, rcx
  movq $1, rdx
  call lm_list_append
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -128]
  jmp std.sort.counting_sort_block_38
std.sort.counting_sort_block_48:
  jmp std.sort.counting_sort_block_51
std.sort.counting_sort_block_51:
  movq $1, rax
  cmpq $r2, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne std.sort.counting_sort_block_53
  jmp std.sort.counting_sort_block_70
std.sort.counting_sort_block_53:
  jmp std.sort.counting_sort_block_53
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r42, rax
  subq $r19, rax
  movq rax, $r43
  movq $r27, rcx
  movq $r43, rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r46, rax
  subq $r19, rax
  movq rax, $r47
  movq $r27, rcx
  movq $r47, rdx
  call lm_list_get
  movq $r48, rax
  addq $9, rax
  movq rax, $r50
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $r51, rax
  subq $r19, rax
  movq rax, $r52
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.sort.counting_sort_block_51
std.sort.counting_sort_block_70:
  jmp std.sort.counting_sort_block_73
std.sort.counting_sort_block_73:
  movq $0, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r59, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne std.sort.counting_sort_block_76
  jmp std.sort.counting_sort_block_104
std.sort.counting_sort_block_76:
  jmp std.sort.counting_sort_block_76
  jmp std.sort.counting_sort_block_77
std.sort.counting_sort_block_77:
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq $r62, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  testq rax, rax
  jne std.sort.counting_sort_block_81
  jmp std.sort.counting_sort_block_99
std.sort.counting_sort_block_81:
  jmp std.sort.counting_sort_block_81
  movq [rbp + -72], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  testq rax, rax
  jne std.sort.counting_sort_block_84
  jmp std.sort.counting_sort_block_87
std.sort.counting_sort_block_84:
  jmp std.sort.counting_sort_block_84
  movq $r23, rax
  subq $1, rax
  movq rax, $r69
  jmp std.sort.counting_sort_block_90
std.sort.counting_sort_block_87:
  movq $r19, rax
  addq $1, rax
  movq rax, $r71
  jmp std.sort.counting_sort_block_90
std.sort.counting_sort_block_90:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -176]
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq $r76, rax
  subq $9, rax
  movq rax, $r78
  jmp std.sort.counting_sort_block_77
std.sort.counting_sort_block_99:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -184]
  jmp std.sort.counting_sort_block_73
std.sort.counting_sort_block_104:
  movq $0, rax
  jmp std.sort.counting_sort_epilogue
std.sort.counting_sort_epilogue:
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
.Lfunc_end_std.sort.counting_sort:

.globl std.sort.radix_sort
std.sort.radix_sort:
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
std.sort.radix_sort_entry:
std.sort.radix_sort_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.sort.counting_sort
  movq $0, rax
  jmp std.sort.radix_sort_epilogue
std.sort.radix_sort_epilogue:
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
.Lfunc_end_std.sort.radix_sort:

.globl std.math.statistics.sum
std.math.statistics.sum:
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
std.math.statistics.sum_entry:
std.math.statistics.sum_block_0:
  jmp std.math.statistics.sum_block_2
std.math.statistics.sum_block_2:
  jmp std.math.statistics.sum_block_4
std.math.statistics.sum_block_4:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r4, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.math.statistics.sum_block_7
  jmp std.math.statistics.sum_block_18
std.math.statistics.sum_block_7:
  jmp std.math.statistics.sum_block_7
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $2, rax
  addq $r7, rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  movq rax, [rbp + -88]
  jmp std.math.statistics.sum_block_13
std.math.statistics.sum_block_13:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  jmp std.math.statistics.sum_block_4
std.math.statistics.sum_block_18:
  movq [rbp + -88], rax
  jmp std.math.statistics.sum_epilogue
std.math.statistics.sum_epilogue:
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
.Lfunc_end_std.math.statistics.sum:

.globl std.sort.partial_sort
std.sort.partial_sort:
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
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.sort.partial_sort_entry:
std.sort.partial_sort_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -80], rdx
  movq [rbp + -88], r8
  call std.sort.quicksort
  movq [rbp + -72], rax
  cmpq $1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.sort.partial_sort_block_4
  jmp std.sort.partial_sort_block_5
std.sort.partial_sort_block_4:
  jmp std.sort.partial_sort_block_4
  movq $0, rax
  jmp std.sort.partial_sort_epilogue
std.sort.partial_sort_block_5:
  movq $0, rax
  jmp std.sort.partial_sort_epilogue
std.sort.partial_sort_epilogue:
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
.Lfunc_end_std.sort.partial_sort:

.globl std.math.arithmetic.log2
std.math.arithmetic.log2:
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
std.math.arithmetic.log2_entry:
std.math.arithmetic.log2_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.arithmetic.Float.init
  movq [rbp + -72], rcx
  call std.math.arithmetic.Float.log2
  movq $r3, rax
  jmp std.math.arithmetic.log2_epilogue
std.math.arithmetic.log2_epilogue:
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
.Lfunc_end_std.math.arithmetic.log2:

.globl std.math.random.Random.next_int
std.math.random.Random.next_int:
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
std.math.random.Random.next_int_entry:
  movq $0, rax
  jmp std.math.random.Random.next_int_epilogue
std.math.random.Random.next_int_epilogue:
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
.Lfunc_end_std.math.random.Random.next_int:

.globl std.math.vector4.Vector4.normalize
std.math.vector4.Vector4.normalize:
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
std.math.vector4.Vector4.normalize_entry:
  movq $0, rax
  jmp std.math.vector4.Vector4.normalize_epilogue
std.math.vector4.Vector4.normalize_epilogue:
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
.Lfunc_end_std.math.vector4.Vector4.normalize:

.globl std.math.random.Random.next_bool
std.math.random.Random.next_bool:
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
std.math.random.Random.next_bool_entry:
  movq $0, rax
  jmp std.math.random.Random.next_bool_epilogue
std.math.random.Random.next_bool_epilogue:
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
.Lfunc_end_std.math.random.Random.next_bool:

.globl std.math.random.Random.next_string
std.math.random.Random.next_string:
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
std.math.random.Random.next_string_entry:
  movq $0, rax
  jmp std.math.random.Random.next_string_epilogue
std.math.random.Random.next_string_epilogue:
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
.Lfunc_end_std.math.random.Random.next_string:

.globl std.math.random.Random.init
std.math.random.Random.init:
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
std.math.random.Random.init_entry:
  movq $0, rax
  jmp std.math.random.Random.init_epilogue
std.math.random.Random.init_epilogue:
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
.Lfunc_end_std.math.random.Random.init:

.globl std.math.random.SecureRandom.next_bytes
std.math.random.SecureRandom.next_bytes:
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
std.math.random.SecureRandom.next_bytes_entry:
  movq $0, rax
  jmp std.math.random.SecureRandom.next_bytes_epilogue
std.math.random.SecureRandom.next_bytes_epilogue:
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
.Lfunc_end_std.math.random.SecureRandom.next_bytes:

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

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
  .string "Math tests passed!"
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
  sub rsp, 72
main_entry:
main_block_0:
  call std.math.__init__
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

.globl std.math.is_inf
std.math.is_inf:
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
std.math.is_inf_entry:
std.math.is_inf_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.is_inf
  movq $r3, rax
  jmp std.math.is_inf_epilogue
std.math.is_inf_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.is_inf:

.globl std.math.is_nan
std.math.is_nan:
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
std.math.is_nan_entry:
std.math.is_nan_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.is_nan
  movq $r3, rax
  jmp std.math.is_nan_epilogue
std.math.is_nan_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.is_nan:

.globl std.math.sinh
std.math.sinh:
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
std.math.sinh_entry:
std.math.sinh_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.sinh
  movq $r3, rax
  jmp std.math.sinh_epilogue
std.math.sinh_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.sinh:

.globl std.math.atan2
std.math.atan2:
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
std.math.atan2_entry:
std.math.atan2_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -80], rcx
  movq [rbp + -72], rdx
  call std.math.Float.atan2
  movq $r4, rax
  jmp std.math.atan2_epilogue
std.math.atan2_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.atan2:

.globl std.math.acos
std.math.acos:
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
std.math.acos_entry:
std.math.acos_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.acos
  movq $r3, rax
  jmp std.math.acos_epilogue
std.math.acos_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.acos:

.globl std.math.is_finite
std.math.is_finite:
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
std.math.is_finite_entry:
std.math.is_finite_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.is_finite
  movq $r3, rax
  jmp std.math.is_finite_epilogue
std.math.is_finite_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.is_finite:

.globl std.math.asin
std.math.asin:
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
std.math.asin_entry:
std.math.asin_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.asin
  movq $r3, rax
  jmp std.math.asin_epilogue
std.math.asin_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.asin:

.globl std.math.tan
std.math.tan:
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
std.math.tan_entry:
std.math.tan_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.tan
  movq $r3, rax
  jmp std.math.tan_epilogue
std.math.tan_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.tan:

.globl std.math.__init__
std.math.__init__:
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
std.math.__init___entry:
  movq $0, rax
  jmp std.math.__init___epilogue
std.math.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.__init__:

.globl std.math.cos
std.math.cos:
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
std.math.cos_entry:
std.math.cos_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.cos
  movq $r3, rax
  jmp std.math.cos_epilogue
std.math.cos_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.cos:

.globl std.math.sin
std.math.sin:
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
std.math.sin_entry:
std.math.sin_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.sin
  movq $r3, rax
  jmp std.math.sin_epilogue
std.math.sin_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.sin:

.globl std.math.exp2
std.math.exp2:
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
std.math.exp2_entry:
std.math.exp2_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.exp2
  movq $r3, rax
  jmp std.math.exp2_epilogue
std.math.exp2_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.exp2:

.globl std.math.log10
std.math.log10:
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
std.math.log10_entry:
std.math.log10_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.log10
  movq $r3, rax
  jmp std.math.log10_epilogue
std.math.log10_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.log10:

.globl std.math.log
std.math.log:
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
std.math.log_entry:
std.math.log_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.log
  movq $r3, rax
  jmp std.math.log_epilogue
std.math.log_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.log:

.globl std.math.hypot
std.math.hypot:
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
std.math.hypot_entry:
std.math.hypot_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -80], rcx
  movq [rbp + -72], rdx
  call std.math.Float.hypot
  movq $r4, rax
  jmp std.math.hypot_epilogue
std.math.hypot_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.hypot:

.globl std.math.cbrt
std.math.cbrt:
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
std.math.cbrt_entry:
std.math.cbrt_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.cbrt
  movq $r3, rax
  jmp std.math.cbrt_epilogue
std.math.cbrt_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.cbrt:

.globl std.math.sqrt
std.math.sqrt:
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
std.math.sqrt_entry:
std.math.sqrt_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.sqrt
  movq $r3, rax
  jmp std.math.sqrt_epilogue
std.math.sqrt_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.sqrt:

.globl std.math.round
std.math.round:
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
std.math.round_entry:
std.math.round_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.round
  movq $r3, rax
  jmp std.math.round_epilogue
std.math.round_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.round:

.globl std.math.sign
std.math.sign:
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
std.math.sign_entry:
std.math.sign_block_0:
  movq [rbp + -64], rax
  cmpq $2, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.math.sign_block_3
  jmp std.math.sign_block_5
std.math.sign_block_3:
  jmp std.math.sign_block_3
  movq $2, rax
  jmp std.math.sign_epilogue
std.math.sign_block_5:
  movq [rbp + -64], rax
  cmpq $2, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.math.sign_block_8
  jmp std.math.sign_block_11
std.math.sign_block_8:
  jmp std.math.sign_block_8
  movq $2, rax
  negq rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.math.sign_epilogue
std.math.sign_block_11:
  movq $2, rax
  jmp std.math.sign_epilogue
std.math.sign_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.sign:

.globl std.math.exp
std.math.exp:
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
std.math.exp_entry:
std.math.exp_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.exp
  movq $r3, rax
  jmp std.math.exp_epilogue
std.math.exp_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.exp:

.globl std.math.clamp
std.math.clamp:
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
std.math.clamp_entry:
std.math.clamp_block_0:
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.math.clamp_block_2
  jmp std.math.clamp_block_3
std.math.clamp_block_2:
  jmp std.math.clamp_block_2
  movq [rbp + -72], rax
  jmp std.math.clamp_epilogue
std.math.clamp_block_3:
  movq [rbp + -64], rax
  cmpq [rbp + -80], rax
  setg al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.math.clamp_block_5
  jmp std.math.clamp_block_6
std.math.clamp_block_5:
  jmp std.math.clamp_block_5
  movq [rbp + -80], rax
  jmp std.math.clamp_epilogue
std.math.clamp_block_6:
  movq $0, rax
  jmp std.math.clamp_epilogue
std.math.clamp_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.clamp:

.globl std.math.max
std.math.max:
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
std.math.max_entry:
std.math.max_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -80], rcx
  movq [rbp + -72], rdx
  call std.math.Float.max
  movq $r4, rax
  jmp std.math.max_epilogue
std.math.max_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.max:

.globl std.math.ceil
std.math.ceil:
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
std.math.ceil_entry:
std.math.ceil_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.ceil
  movq $r3, rax
  jmp std.math.ceil_epilogue
std.math.ceil_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.ceil:

.globl std.math.min
std.math.min:
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
std.math.min_entry:
std.math.min_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -80], rcx
  movq [rbp + -72], rdx
  call std.math.Float.min
  movq $r4, rax
  jmp std.math.min_epilogue
std.math.min_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.min:

.globl std.math.combinations
std.math.combinations:
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
std.math.combinations_entry:
std.math.combinations_block_0:
  movq [rbp + -72], rax
  cmpq $1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.math.combinations_block_7
  jmp std.math.combinations_block_4
std.math.combinations_block_4:
  jmp std.math.combinations_block_4
  movq [rbp + -72], rax
  cmpq [rbp + -64], rax
  setg al
  movzx eax, al
  movq rax, [rbp + -88]
  jmp std.math.combinations_block_7
std.math.combinations_block_7:
  movq [rbp + -88], rax
  testq rax, rax
  jne std.math.combinations_block_8
  jmp std.math.combinations_block_10
std.math.combinations_block_8:
  jmp std.math.combinations_block_8
  movq $1, rax
  jmp std.math.combinations_epilogue
std.math.combinations_block_10:
  movq [rbp + -64], rcx
  call std.math.factorial
  movq [rbp + -72], rcx
  call std.math.factorial
  movq [rbp + -64], rax
  subq [rbp + -72], rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.math.factorial
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
  jmp std.math.combinations_epilogue
std.math.combinations_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.combinations:

.globl std.math.Float.fract
std.math.Float.fract:
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
std.math.Float.fract_entry:
  movq $0, rax
  jmp std.math.Float.fract_epilogue
std.math.Float.fract_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.fract:

.globl std.math.Float.cos
std.math.Float.cos:
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
std.math.Float.cos_entry:
  movq $0, rax
  jmp std.math.Float.cos_epilogue
std.math.Float.cos_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.cos:

.globl std.math.cosh
std.math.cosh:
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
std.math.cosh_entry:
std.math.cosh_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.cosh
  movq $r3, rax
  jmp std.math.cosh_epilogue
std.math.cosh_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.cosh:

.globl std.math.gcd
std.math.gcd:
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
std.math.gcd_entry:
std.math.gcd_block_0:
  movq [rbp + -64], rcx
  call std.math.abs_int
  movq [rbp + -72], rcx
  call std.math.abs_int
  jmp std.math.gcd_block_5
std.math.gcd_block_5:
  movq $r4, rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.math.gcd_block_8
  jmp std.math.gcd_block_13
std.math.gcd_block_8:
  jmp std.math.gcd_block_8
  movq $r2, rax
  cqto
  movq $r4, rcx
  idivq rcx
  movq rdx, $r10
  jmp std.math.gcd_block_5
std.math.gcd_block_13:
  movq $r4, rax
  jmp std.math.gcd_epilogue
std.math.gcd_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.gcd:

.globl std.math.nearly_equal
std.math.nearly_equal:
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
std.math.nearly_equal_entry:
std.math.nearly_equal_block_0:
  movq [rbp + -64], rax
  subq [rbp + -72], rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call std.math.abs
  movq $r4, rax
  cmpq [rbp + -80], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp std.math.nearly_equal_epilogue
std.math.nearly_equal_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.nearly_equal:

.globl std.math.Float.round
std.math.Float.round:
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
std.math.Float.round_entry:
  movq $0, rax
  jmp std.math.Float.round_epilogue
std.math.Float.round_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.round:

.globl std.math.Float.max
std.math.Float.max:
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
std.math.Float.max_entry:
  movq $0, rax
  jmp std.math.Float.max_epilogue
std.math.Float.max_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.max:

.globl std.math.pow
std.math.pow:
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
std.math.pow_entry:
std.math.pow_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -80], rcx
  movq [rbp + -72], rdx
  call std.math.Float.pow
  movq $r4, rax
  jmp std.math.pow_epilogue
std.math.pow_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.pow:

.globl std.math.Int.max
std.math.Int.max:
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
std.math.Int.max_entry:
  movq $0, rax
  jmp std.math.Int.max_epilogue
std.math.Int.max_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Int.max:

.globl std.math.abs_int
std.math.abs_int:
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
std.math.abs_int_entry:
std.math.abs_int_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Int.init
  movq [rbp + -72], rcx
  call std.math.Int.abs
  movq $r3, rax
  jmp std.math.abs_int_epilogue
std.math.abs_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.abs_int:

.globl std.math.Int.init
std.math.Int.init:
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
std.math.Int.init_entry:
  movq $0, rax
  jmp std.math.Int.init_epilogue
std.math.Int.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Int.init:

.globl std.math.trunc
std.math.trunc:
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
std.math.trunc_entry:
std.math.trunc_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.trunc
  movq $r3, rax
  jmp std.math.trunc_epilogue
std.math.trunc_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.trunc:

.globl std.math.Float.sinh
std.math.Float.sinh:
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
std.math.Float.sinh_entry:
  movq $0, rax
  jmp std.math.Float.sinh_epilogue
std.math.Float.sinh_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.sinh:

.globl std.math.Int.min
std.math.Int.min:
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
std.math.Int.min_entry:
  movq $0, rax
  jmp std.math.Int.min_epilogue
std.math.Int.min_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Int.min:

.globl std.math.Float.log2
std.math.Float.log2:
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
std.math.Float.log2_entry:
  movq $0, rax
  jmp std.math.Float.log2_epilogue
std.math.Float.log2_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.log2:

.globl std.math.fract
std.math.fract:
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
std.math.fract_entry:
std.math.fract_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.fract
  movq $r3, rax
  jmp std.math.fract_epilogue
std.math.fract_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.fract:

.globl std.math.Float.min
std.math.Float.min:
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
std.math.Float.min_entry:
  movq $0, rax
  jmp std.math.Float.min_epilogue
std.math.Float.min_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.min:

.globl std.math.floor
std.math.floor:
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
std.math.floor_entry:
std.math.floor_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.floor
  movq $r3, rax
  jmp std.math.floor_epilogue
std.math.floor_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.floor:

.globl std.math.Int.abs
std.math.Int.abs:
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
std.math.Int.abs_entry:
  movq $0, rax
  jmp std.math.Int.abs_epilogue
std.math.Int.abs_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Int.abs:

.globl std.math.Float.atan2
std.math.Float.atan2:
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
std.math.Float.atan2_entry:
  movq $0, rax
  jmp std.math.Float.atan2_epilogue
std.math.Float.atan2_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.atan2:

.globl std.math.Float.floor
std.math.Float.floor:
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
std.math.Float.floor_entry:
  movq $0, rax
  jmp std.math.Float.floor_epilogue
std.math.Float.floor_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.floor:

.globl std.math.lerp
std.math.lerp:
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
std.math.lerp_entry:
std.math.lerp_block_0:
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
  jmp std.math.lerp_epilogue
std.math.lerp_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.lerp:

.globl std.math.log2
std.math.log2:
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
std.math.log2_entry:
std.math.log2_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.log2
  movq $r3, rax
  jmp std.math.log2_epilogue
std.math.log2_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.log2:

.globl std.math.abs
std.math.abs:
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
std.math.abs_entry:
std.math.abs_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.abs
  movq $r3, rax
  jmp std.math.abs_epilogue
std.math.abs_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.abs:

.globl std.math.Float.ceil
std.math.Float.ceil:
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
std.math.Float.ceil_entry:
  movq $0, rax
  jmp std.math.Float.ceil_epilogue
std.math.Float.ceil_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.ceil:

.globl std.math.lcm
std.math.lcm:
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
std.math.lcm_entry:
std.math.lcm_block_0:
  movq [rbp + -64], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.math.lcm_block_8
  jmp std.math.lcm_block_4
std.math.lcm_block_4:
  jmp std.math.lcm_block_4
  movq [rbp + -72], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  jmp std.math.lcm_block_8
std.math.lcm_block_8:
  movq [rbp + -88], rax
  testq rax, rax
  jne std.math.lcm_block_9
  jmp std.math.lcm_block_11
std.math.lcm_block_9:
  jmp std.math.lcm_block_9
  movq $1, rax
  jmp std.math.lcm_epilogue
std.math.lcm_block_11:
  movq [rbp + -64], rax
  imulq [rbp + -72], rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.math.abs_int
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.math.gcd
  movq $r10, rax
  cqto
  movq $r11, rcx
  idivq rcx
  movq rax, $r12
  movq $r12, rax
  jmp std.math.lcm_epilogue
std.math.lcm_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.lcm:

.globl std.math.Float.sqrt
std.math.Float.sqrt:
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
std.math.Float.sqrt_entry:
  movq $0, rax
  jmp std.math.Float.sqrt_epilogue
std.math.Float.sqrt_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.sqrt:

.globl std.math.Float.exp
std.math.Float.exp:
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
std.math.Float.exp_entry:
  movq $0, rax
  jmp std.math.Float.exp_epilogue
std.math.Float.exp_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.exp:

.globl std.math.Float.log
std.math.Float.log:
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
std.math.Float.log_entry:
  movq $0, rax
  jmp std.math.Float.log_epilogue
std.math.Float.log_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.log:

.globl std.math.tanh
std.math.tanh:
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
std.math.tanh_entry:
std.math.tanh_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.tanh
  movq $r3, rax
  jmp std.math.tanh_epilogue
std.math.tanh_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.tanh:

.globl std.math.Float.atan
std.math.Float.atan:
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
std.math.Float.atan_entry:
  movq $0, rax
  jmp std.math.Float.atan_epilogue
std.math.Float.atan_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.atan:

.globl std.math.Float.is_finite
std.math.Float.is_finite:
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
std.math.Float.is_finite_entry:
  movq $0, rax
  jmp std.math.Float.is_finite_epilogue
std.math.Float.is_finite_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.is_finite:

.globl std.math.Float.cbrt
std.math.Float.cbrt:
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
std.math.Float.cbrt_entry:
  movq $0, rax
  jmp std.math.Float.cbrt_epilogue
std.math.Float.cbrt_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.cbrt:

.globl std.math.Float.log10
std.math.Float.log10:
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
std.math.Float.log10_entry:
  movq $0, rax
  jmp std.math.Float.log10_epilogue
std.math.Float.log10_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.log10:

.globl std.math.factorial
std.math.factorial:
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
std.math.factorial_entry:
std.math.factorial_block_0:
  movq [rbp + -64], rax
  cmpq $1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.math.factorial_block_3
  jmp std.math.factorial_block_5
std.math.factorial_block_3:
  jmp std.math.factorial_block_3
  movq $1, rax
  jmp std.math.factorial_epilogue
std.math.factorial_block_5:
  movq [rbp + -64], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.math.factorial_block_8
  jmp std.math.factorial_block_10
std.math.factorial_block_8:
  jmp std.math.factorial_block_8
  movq $9, rax
  jmp std.math.factorial_epilogue
std.math.factorial_block_10:
  jmp std.math.factorial_block_13
std.math.factorial_block_13:
  movq $9, rax
  cmpq [rbp + -64], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.math.factorial_block_15
  jmp std.math.factorial_block_22
std.math.factorial_block_15:
  jmp std.math.factorial_block_15
  movq $9, rax
  imulq $9, rax
  movq rax, [rbp + -96]
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.math.factorial_block_13
std.math.factorial_block_22:
  movq [rbp + -96], rax
  jmp std.math.factorial_epilogue
std.math.factorial_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.factorial:

.globl std.math.Float.exp2
std.math.Float.exp2:
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
std.math.Float.exp2_entry:
  movq $0, rax
  jmp std.math.Float.exp2_epilogue
std.math.Float.exp2_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.exp2:

.globl std.math.Float.pow
std.math.Float.pow:
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
std.math.Float.pow_entry:
  movq $0, rax
  jmp std.math.Float.pow_epilogue
std.math.Float.pow_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.pow:

.globl std.math.Float.trunc
std.math.Float.trunc:
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
std.math.Float.trunc_entry:
  movq $0, rax
  jmp std.math.Float.trunc_epilogue
std.math.Float.trunc_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.trunc:

.globl std.math.Float.abs
std.math.Float.abs:
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
std.math.Float.abs_entry:
  movq $0, rax
  jmp std.math.Float.abs_epilogue
std.math.Float.abs_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.abs:

.globl std.math.permutations
std.math.permutations:
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
std.math.permutations_entry:
std.math.permutations_block_0:
  movq [rbp + -72], rax
  cmpq $1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.math.permutations_block_7
  jmp std.math.permutations_block_4
std.math.permutations_block_4:
  jmp std.math.permutations_block_4
  movq [rbp + -72], rax
  cmpq [rbp + -64], rax
  setg al
  movzx eax, al
  movq rax, [rbp + -88]
  jmp std.math.permutations_block_7
std.math.permutations_block_7:
  movq [rbp + -88], rax
  testq rax, rax
  jne std.math.permutations_block_8
  jmp std.math.permutations_block_10
std.math.permutations_block_8:
  jmp std.math.permutations_block_8
  movq $1, rax
  jmp std.math.permutations_epilogue
std.math.permutations_block_10:
  movq [rbp + -64], rcx
  call std.math.factorial
  movq [rbp + -64], rax
  subq [rbp + -72], rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.math.factorial
  movq $r8, rax
  cqto
  movq $r10, rcx
  idivq rcx
  movq rax, $r11
  movq $r11, rax
  jmp std.math.permutations_epilogue
std.math.permutations_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.permutations:

.globl std.math.Float.hypot
std.math.Float.hypot:
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
std.math.Float.hypot_entry:
  movq $0, rax
  jmp std.math.Float.hypot_epilogue
std.math.Float.hypot_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.hypot:

.globl std.math.Float.sin
std.math.Float.sin:
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
std.math.Float.sin_entry:
  movq $0, rax
  jmp std.math.Float.sin_epilogue
std.math.Float.sin_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.sin:

.globl std.math.atan
std.math.atan:
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
std.math.atan_entry:
std.math.atan_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.math.Float.init
  movq [rbp + -72], rcx
  call std.math.Float.atan
  movq $r3, rax
  jmp std.math.atan_epilogue
std.math.atan_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.atan:

.globl std.math.Float.tanh
std.math.Float.tanh:
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
std.math.Float.tanh_entry:
  movq $0, rax
  jmp std.math.Float.tanh_epilogue
std.math.Float.tanh_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.tanh:

.globl std.math.Float.tan
std.math.Float.tan:
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
std.math.Float.tan_entry:
  movq $0, rax
  jmp std.math.Float.tan_epilogue
std.math.Float.tan_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.tan:

.globl std.math.Float.asin
std.math.Float.asin:
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
std.math.Float.asin_entry:
  movq $0, rax
  jmp std.math.Float.asin_epilogue
std.math.Float.asin_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.asin:

.globl std.math.Float.acos
std.math.Float.acos:
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
std.math.Float.acos_entry:
  movq $0, rax
  jmp std.math.Float.acos_epilogue
std.math.Float.acos_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.acos:

.globl std.math.Float.cosh
std.math.Float.cosh:
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
std.math.Float.cosh_entry:
  movq $0, rax
  jmp std.math.Float.cosh_epilogue
std.math.Float.cosh_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.cosh:

.globl std.math.Float.normalize_angle
std.math.Float.normalize_angle:
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
std.math.Float.normalize_angle_entry:
  movq $0, rax
  jmp std.math.Float.normalize_angle_epilogue
std.math.Float.normalize_angle_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.normalize_angle:

.globl std.math.Float.is_nan
std.math.Float.is_nan:
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
std.math.Float.is_nan_entry:
  movq $0, rax
  jmp std.math.Float.is_nan_epilogue
std.math.Float.is_nan_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.is_nan:

.globl std.math.Float.is_inf
std.math.Float.is_inf:
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
std.math.Float.is_inf_entry:
  movq $0, rax
  jmp std.math.Float.is_inf_epilogue
std.math.Float.is_inf_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.is_inf:

.globl std.math.Float.init
std.math.Float.init:
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
std.math.Float.init_entry:
  movq $0, rax
  jmp std.math.Float.init_epilogue
std.math.Float.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.math.Float.init:

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

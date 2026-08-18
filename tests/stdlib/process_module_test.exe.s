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
  .string "Testing Pipe Frame..."
.align 8
str_const_1:
  .string "hello"
.align 8
str_const_2:
  .string ""
.align 8
str_const_3:
  .string "pipe read failed"
.align 8
str_const_4:
  .string "Testing Process Frame..."
.align 8
str_const_5:
  .string "id failed"
.align 8
str_const_6:
  .string "echo hello"
.align 8
str_const_7:
  .string "run failed"
.align 8
str_const_8:
  .string "=== Process Module Test Suite ==="
.align 8
str_const_9:
  .string "Process frame test failed"
.align 8
str_const_10:
  .string "Command frame test failed"
.align 8
str_const_11:
  .string "Pipe frame test failed"
.align 8
str_const_12:
  .string "All process tests passed successfully."
.align 8
str_const_13:
  .string "Testing Command Frame..."
.align 8
str_const_14:
  .string "echo"
.align 8
str_const_15:
  .string "hello"
.align 8
str_const_16:
  .string "echo"
.align 8
str_const_17:
  .string "program failed"
.align 8
str_const_18:
  .string "args failed"
.align 8
str_const_19:
  .string "execute failed"
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
  call std.process.index.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq [rel str_const_8], rcx
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
  call test_process_frame
  movq $r2, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_command_frame
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  call test_pipe_frame
  movq $r12, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rel str_const_12], rcx
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

.globl std.process.index.__init__
std.process.index.__init__:
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
std.process.index.__init___entry:
  movq $0, rax
  jmp std.process.index.__init___epilogue
std.process.index.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.index.__init__:

.globl std.process.index.id
std.process.index.id:
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
std.process.index.id_entry:
std.process.index.id_block_0:
  call std.process.process.id
  movq $0, rax
  jmp std.process.index.id_epilogue
std.process.index.id_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.index.id:

.globl std.process.index.exit
std.process.index.exit:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.process.index.exit_entry:
std.process.index.exit_block_0:
  movq [rbp + -64], rcx
  call std.process.process.exit
  movq $r1, rax
  jmp std.process.index.exit_epilogue
std.process.index.exit_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.index.exit:

.globl std.process.index.Process.init
std.process.index.Process.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.process.index.Process.init_entry:
  movq $0, rax
  jmp std.process.index.Process.init_epilogue
std.process.index.Process.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.index.Process.init:

.globl std.process.index.Process.run
std.process.index.Process.run:
  push rbp
  mov rbp, rsp
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
std.process.index.Process.run_entry:
  movq $0, rax
  jmp std.process.index.Process.run_epilogue
std.process.index.Process.run_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.index.Process.run:

.globl std.process.index.Pipe
std.process.index.Pipe:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.process.index.Pipe_entry:
std.process.index.Pipe_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.process.pipe.Pipe.init
  movq $0, rax
  jmp std.process.index.Pipe_epilogue
std.process.index.Pipe_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.index.Pipe:

.globl std.process.index.Command
std.process.index.Command:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.process.index.Command_entry:
std.process.index.Command_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.process.command.Command.init
  movq [rbp + -72], rax
  jmp std.process.index.Command_epilogue
std.process.index.Command_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.index.Command:

.globl std.process.process.id
std.process.process.id:
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
std.process.process.id_entry:
std.process.process.id_block_0:
  movq $0, rax
  jmp std.process.process.id_epilogue
std.process.process.id_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.process.id:

.globl std.process.process.__init__
std.process.process.__init__:
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
std.process.process.__init___entry:
  movq $0, rax
  jmp std.process.process.__init___epilogue
std.process.process.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.process.__init__:

.globl std.process.command.__init__
std.process.command.__init__:
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
std.process.command.__init___entry:
  movq $0, rax
  jmp std.process.command.__init___epilogue
std.process.command.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.command.__init__:

.globl std.process.command.Command.init
std.process.command.Command.init:
  push rbp
  mov rbp, rsp
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
std.process.command.Command.init_entry:
  movq $0, rax
  jmp std.process.command.Command.init_epilogue
std.process.command.Command.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.command.Command.init:

.globl std.process.process.exit
std.process.process.exit:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.process.process.exit_entry:
std.process.process.exit_block_0:
  movq $2, rax
  jmp std.process.process.exit_epilogue
std.process.process.exit_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.process.exit:

.globl std.process.index.Process.exit
std.process.index.Process.exit:
  push rbp
  mov rbp, rsp
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
std.process.index.Process.exit_entry:
  movq $0, rax
  jmp std.process.index.Process.exit_epilogue
std.process.index.Process.exit_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.index.Process.exit:

.globl std.process.process.run
std.process.process.run:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.process.process.run_entry:
std.process.process.run_block_0:
  movq $1, rax
  jmp std.process.process.run_epilogue
std.process.process.run_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.process.run:

.globl test_pipe_frame
test_pipe_frame:
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
test_pipe_frame_entry:
test_pipe_frame_block_0:
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
  call std.process.index.Pipe
  movq $r2, rax
  movq rax, [rbp + -96]
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call std.process.pipe.Pipe.write
  movq [rbp + -96], rcx
  call std.process.pipe.Pipe.read
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r7, rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq $9, rax
  jmp test_pipe_frame_epilogue
test_pipe_frame_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_pipe_frame:

.globl test_process_frame
test_process_frame:
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
test_process_frame_entry:
test_process_frame_block_0:
  movq [rel str_const_4], rcx
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
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -96], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -96], rcx
  call std.process.index.Process.init
  movq [rbp + -96], rcx
  call std.process.index.Process.id
  movq $r6, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -96], rcx
  movq [rbp + -120], rdx
  call std.process.index.Process.run
  movq $r12, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq $9, rax
  jmp test_process_frame_epilogue
test_process_frame_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_process_frame:

.globl std.process.index.Process.id
std.process.index.Process.id:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.process.index.Process.id_entry:
  movq $0, rax
  jmp std.process.index.Process.id_epilogue
std.process.index.Process.id_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.index.Process.id:

.globl test_command_frame
test_command_frame:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 184
test_command_frame_entry:
test_command_frame_block_0:
  movq [rel str_const_13], rcx
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
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.process.index.Command
  movq $r3, rax
  movq rax, [rbp + -104]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call std.process.command.Command.arg
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -128]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -168]
  movq [rbp + -168], rcx
  call lm_list_len
  movq $r14, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq [rbp + -104], rcx
  call std.process.command.Command.execute
  movq $r19, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq $9, rax
  jmp test_command_frame_epilogue
test_command_frame_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_command_frame:

.globl std.process.pipe.Pipe.init
std.process.pipe.Pipe.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.process.pipe.Pipe.init_entry:
  movq $0, rax
  jmp std.process.pipe.Pipe.init_epilogue
std.process.pipe.Pipe.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.pipe.Pipe.init:

.globl std.process.command.Command.execute
std.process.command.Command.execute:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.process.command.Command.execute_entry:
  movq $0, rax
  jmp std.process.command.Command.execute_epilogue
std.process.command.Command.execute_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.command.Command.execute:

.globl std.process.command.Command.arg
std.process.command.Command.arg:
  push rbp
  mov rbp, rsp
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
std.process.command.Command.arg_entry:
  movq $0, rax
  jmp std.process.command.Command.arg_epilogue
std.process.command.Command.arg_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.command.Command.arg:

.globl std.process.pipe.Pipe.read
std.process.pipe.Pipe.read:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.process.pipe.Pipe.read_entry:
  movq $0, rax
  jmp std.process.pipe.Pipe.read_epilogue
std.process.pipe.Pipe.read_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.pipe.Pipe.read:

.globl std.process.index.run
std.process.index.run:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.process.index.run_entry:
std.process.index.run_block_0:
  movq [rbp + -64], rcx
  call std.process.process.run
  movq $r1, rax
  jmp std.process.index.run_epilogue
std.process.index.run_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.index.run:

.globl std.process.pipe.Pipe.write
std.process.pipe.Pipe.write:
  push rbp
  mov rbp, rsp
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
std.process.pipe.Pipe.write_entry:
  movq $0, rax
  jmp std.process.pipe.Pipe.write_epilogue
std.process.pipe.Pipe.write_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.pipe.Pipe.write:

.globl std.process.pipe.__init__
std.process.pipe.__init__:
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
std.process.pipe.__init___entry:
  movq $0, rax
  jmp std.process.pipe.__init___epilogue
std.process.pipe.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.process.pipe.__init__:

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

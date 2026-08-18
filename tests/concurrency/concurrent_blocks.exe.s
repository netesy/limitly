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
  .string " === Concurrent Block Tests === "
.align 8
str_const_1:
  .string "task_0"
.align 8
str_const_2:
  .string "task_1"
.align 8
str_const_3:
  .string "task_2"
.align 8
str_const_4:
  .string "Received result: %s"
.align 8
str_const_5:
  .string "Concurrent block finished"
.align 8
str_const_6:
  .string "Concurrent block should execute 3 tasks"
.align 8
str_const_7:
  .string "job1"
.align 8
str_const_8:
  .string "job2"
.align 8
str_const_9:
  .string "job3"
.align 8
str_const_10:
  .string "worker_0"
.align 8
str_const_11:
  .string "Final result: %s"
.align 8
str_const_12:
  .string "Worker should process 3 jobs"
.align 8
str_const_13:
  .string " === Tasks seeding a worker stream === "
.align 8
str_const_14:
  .string "bootstrap - 1"
.align 8
str_const_15:
  .string "bootstrap - 2"
.align 8
str_const_16:
  .string "worker_1"
.align 8
str_const_17:
  .string "Seeded result: %s"
.align 8
str_const_18:
  .string "Seeded worker should process 2 items"
.align 8
str_const_19:
  .string " === Tasks seeding a worker stream === "
.align 8
str_const_20:
  .string "bootstrap - 1"
.align 8
str_const_21:
  .string "bootstrap - 2"
.align 8
str_const_22:
  .string "worker_2"
.align 8
str_const_23:
  .string "Seeded result: %s"
.align 8
str_const_24:
  .string "Second seeded worker should process 2 items"
.align 8
str_const_25:
  .string "Handled: %s"
.align 8
str_const_26:
  .string "Handled: %s"
.align 8
str_const_27:
  .string "Concurrent task %s running"
.align 8
str_const_28:
  .string "Task %s completed"
.align 8
str_const_29:
  .string "Concurrent task %s running"
.align 8
str_const_30:
  .string "Task %s completed"
.align 8
str_const_31:
  .string "Handled: %s"
.align 8
str_const_32:
  .string "Concurrent task %s running"
.align 8
str_const_33:
  .string "Task %s completed"
.align 8
str_const_34:
  .string "Processed: %s"
.align 8
str_const_35:
  .string "Handled: %s"
.align 8
str_const_36:
  .string "Processed: %s"
.align 8
str_const_37:
  .string "Concurrent task %s running"
.align 8
str_const_38:
  .string "Task %s completed"
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
  sub rsp, 568
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
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  jmp main_block_41
main_block_41:
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne main_block_54
  jmp main_block_45
main_block_45:
  jmp main_block_45
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  movq $0, rdx
  call lm_rt_str_format
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
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -168]
  jmp main_block_41
main_block_54:
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  addq $16, rax
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  mov rax, [rax]
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  call lm_print_str
  movq [rbp + -168], rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  call channel
  call channel
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  jmp main_block_85
main_block_85:
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  testq rax, rax
  jne main_block_98
  jmp main_block_89
main_block_89:
  jmp main_block_89
  movq [rel str_const_11], rcx
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
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -304]
  jmp main_block_85
main_block_98:
  movq [rbp + -304], rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -312]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -312], rcx
  movq [rbp + -320], rdx
  call lm_assert
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  addq $16, rax
  movq rax, [rbp + -336]
  movq [rbp + -336], rax
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  mov rax, [rax]
  movq rax, [rbp + -352]
  movq [rbp + -352], rcx
  call lm_print_str
  call channel
  call channel
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  jmp main_block_127
main_block_127:
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -384]
  movq [rbp + -384], rax
  testq rax, rax
  jne main_block_140
  jmp main_block_131
main_block_131:
  jmp main_block_131
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq [rbp + -392], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  addq $16, rax
  movq rax, [rbp + -408]
  movq [rbp + -408], rax
  movq rax, [rbp + -416]
  movq [rbp + -416], rax
  mov rax, [rax]
  movq rax, [rbp + -424]
  movq [rbp + -424], rcx
  call lm_print_str
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -432]
  jmp main_block_127
main_block_140:
  movq [rbp + -432], rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -440]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -440], rcx
  movq [rbp + -448], rdx
  call lm_assert
  movq [rel str_const_19], rcx
  call lm_box_string
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
  call channel
  call channel
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -488]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  jmp main_block_169
main_block_169:
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -512]
  movq [rbp + -512], rax
  testq rax, rax
  jne main_block_182
  jmp main_block_173
main_block_173:
  jmp main_block_173
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -520], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -528]
  movq [rbp + -528], rax
  addq $16, rax
  movq rax, [rbp + -536]
  movq [rbp + -536], rax
  movq rax, [rbp + -544]
  movq [rbp + -544], rax
  mov rax, [rax]
  movq rax, [rbp + -552]
  movq [rbp + -552], rcx
  call lm_print_str
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -560]
  jmp main_block_169
main_block_182:
  movq [rbp + -560], rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -568]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -568], rcx
  movq [rbp + -576], rdx
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

.globl worker_2
worker_2:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
worker_2_entry:
worker_2_block_0:
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -72]
  movq $0, rax
  jmp worker_2_epilogue
worker_2_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_worker_2:

.globl worker_1
worker_1:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
worker_1_entry:
worker_1_block_0:
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -72]
  movq $0, rax
  jmp worker_1_epilogue
worker_1_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_worker_1:

.globl task_2
task_2:
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
task_2_entry:
task_2_block_0:
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  addq $16, rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  mov rax, [rax]
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call lm_print_str
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -112]
  movq $0, rax
  jmp task_2_epilogue
task_2_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_task_2:

.globl task_1
task_1:
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
task_1_entry:
task_1_block_0:
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  addq $16, rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  mov rax, [rax]
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call lm_print_str
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -112]
  movq $0, rax
  jmp task_1_epilogue
task_1_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_task_1:

.globl _worker_2088375278320
_worker_2088375278320:
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
_worker_2088375278320_entry:
_worker_2088375278320_block_0:
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  movq [rbp + -72], rdx
  call lm_rt_str_format
  movq rax, [rbp + -104]
  movq $0, rax
  jmp _worker_2088375278320_epilogue
_worker_2088375278320_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end__worker_2088375278320:

.globl _task_2088375389360
_task_2088375389360:
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
_task_2088375389360_entry:
_task_2088375389360_block_0:
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  movq [rbp + -72], rdx
  call lm_rt_str_format
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  addq $16, rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  mov rax, [rax]
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  call lm_print_str
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rcx
  movq [rbp + -72], rdx
  call lm_rt_str_format
  movq rax, [rbp + -144]
  movq $0, rax
  jmp _task_2088375389360_epilogue
_task_2088375389360_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end__task_2088375389360:

.globl _worker_2088375410656
_worker_2088375410656:
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
_worker_2088375410656_entry:
_worker_2088375410656_block_0:
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  movq [rbp + -72], rdx
  call lm_rt_str_format
  movq rax, [rbp + -104]
  movq $0, rax
  jmp _worker_2088375410656_epilogue
_worker_2088375410656_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end__worker_2088375410656:

.globl _worker_2088375275376
_worker_2088375275376:
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
_worker_2088375275376_entry:
_worker_2088375275376_block_0:
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  movq [rbp + -72], rdx
  call lm_rt_str_format
  movq rax, [rbp + -104]
  movq $0, rax
  jmp _worker_2088375275376_epilogue
_worker_2088375275376_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end__worker_2088375275376:

.globl worker_0
worker_0:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
worker_0_entry:
worker_0_block_0:
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -72]
  movq $0, rax
  jmp worker_0_epilogue
worker_0_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_worker_0:

.globl task_0
task_0:
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
task_0_entry:
task_0_block_0:
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  addq $16, rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  mov rax, [rax]
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call lm_print_str
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -112]
  movq $0, rax
  jmp task_0_epilogue
task_0_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_task_0:

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

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
  .string "Queue length should be 2"
.align 8
str_const_1:
  .string "Peek should return 1"
.align 8
str_const_2:
  .string "Dequeue should return 1"
.align 8
str_const_3:
  .string "Dequeue should return 2"
.align 8
str_const_4:
  .string "Dequeue on empty queue should return nil"
.align 8
str_const_5:
  .string "Stack length should be 2"
.align 8
str_const_6:
  .string "Peek should return 2"
.align 8
str_const_7:
  .string "Pop should return 2"
.align 8
str_const_8:
  .string "Pop should return 1"
.align 8
str_const_9:
  .string "Pop on empty stack should return nil"
.align 8
str_const_10:
  .string "BitSet should contain bit 10"
.align 8
str_const_11:
  .string "BitSet should contain bit 20"
.align 8
str_const_12:
  .string "BitSet should not contain bit 15"
.align 8
str_const_13:
  .string "BitSet count should be 2"
.align 8
str_const_14:
  .string "BitSet should not contain bit 10 after unset"
.align 8
str_const_15:
  .string "Iterator should return bit 20"
.align 8
str_const_16:
  .string "Iterator should be exhausted"
.align 8
str_const_17:
  .string "Queue/Stack/BitSet tests passed!"
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
  sub rsp, 360
main_entry:
main_block_0:
  call std.collections.queue.__init__
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
  movq [rbp + -64], rcx
  call std.collections.queue.Queue.init
  movq [rbp + -64], rcx
  movq $9, rdx
  call std.collections.queue.Queue.enqueue
  movq [rbp + -64], rcx
  movq $17, rdx
  call std.collections.queue.Queue.enqueue
  movq [rbp + -64], rcx
  call std.collections.queue.Queue.length
  movq $r7, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rcx
  movq [rbp + -80], rdx
  call lm_assert
  movq [rbp + -64], rcx
  call std.collections.queue.Queue.peek
  movq $r12, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -88], rcx
  movq [rbp + -96], rdx
  call lm_assert
  movq [rbp + -64], rcx
  call std.collections.queue.Queue.dequeue
  movq $r17, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq [rbp + -64], rcx
  call std.collections.queue.Queue.dequeue
  movq $r22, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq [rbp + -64], rcx
  call std.collections.queue.Queue.dequeue
  movq $r27, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -152], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -152], rcx
  call std.collections.queue.Stack.init
  movq [rbp + -152], rcx
  movq $9, rdx
  call std.collections.queue.Stack.push
  movq [rbp + -152], rcx
  movq $17, rdx
  call std.collections.queue.Stack.push
  movq [rbp + -152], rcx
  call std.collections.queue.Stack.length
  movq $r39, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq [rbp + -152], rcx
  call std.collections.queue.Stack.peek
  movq $r44, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq [rbp + -152], rcx
  call std.collections.queue.Stack.pop
  movq $r49, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq [rbp + -152], rcx
  call std.collections.queue.Stack.pop
  movq $r54, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq [rbp + -152], rcx
  call std.collections.queue.Stack.pop
  movq $r59, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -240], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -240], rcx
  movq $801, rdx
  call std.collections.queue.BitSet.init
  movq [rbp + -240], rcx
  movq $81, rdx
  call std.collections.queue.BitSet.toggle
  movq [rbp + -240], rcx
  movq $161, rdx
  call std.collections.queue.BitSet.toggle
  movq [rbp + -240], rcx
  movq $81, rdx
  call std.collections.queue.BitSet.contains
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq $r73, rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq [rbp + -240], rcx
  movq $161, rdx
  call std.collections.queue.BitSet.contains
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq $r77, rcx
  movq [rbp + -256], rdx
  call lm_assert
  movq [rbp + -240], rcx
  movq $121, rdx
  call std.collections.queue.BitSet.contains
  movq $r81, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -264]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -264], rcx
  movq [rbp + -272], rdx
  call lm_assert
  movq [rbp + -240], rcx
  call std.collections.queue.BitSet.count
  movq $r86, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -280]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -280], rcx
  movq [rbp + -288], rdx
  call lm_assert
  movq [rbp + -240], rcx
  movq $81, rdx
  call std.collections.queue.BitSet.unset
  movq [rbp + -240], rcx
  movq $81, rdx
  call std.collections.queue.BitSet.contains
  movq $r94, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -296], rcx
  movq [rbp + -304], rdx
  call lm_assert
  movq [rbp + -240], rcx
  call std.collections.queue.BitSet.iterator
  movq $r99, rcx
  call std.collections.queue.BitSetIterator.next
  movq $r101, rax
  cmpq $161, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -312]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -312], rcx
  movq [rbp + -320], rdx
  call lm_assert
  movq $r99, rcx
  call std.collections.queue.BitSetIterator.next
  movq $r106, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -328]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -328], rcx
  movq [rbp + -336], rdx
  call lm_assert
  movq [rel str_const_17], rcx
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

.globl std.collections.queue.__init__
std.collections.queue.__init__:
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
std.collections.queue.__init___entry:
  movq $0, rax
  jmp std.collections.queue.__init___epilogue
std.collections.queue.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.__init__:

.globl std.collections.queue.BitSet.init
std.collections.queue.BitSet.init:
  push rbp
  mov rbp, rsp
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
std.collections.queue.BitSet.init_entry:
  movq $0, rax
  jmp std.collections.queue.BitSet.init_epilogue
std.collections.queue.BitSet.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.BitSet.init:

.globl std.collections.queue.BitSet.iterator
std.collections.queue.BitSet.iterator:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.BitSet.iterator_entry:
  movq $0, rax
  jmp std.collections.queue.BitSet.iterator_epilogue
std.collections.queue.BitSet.iterator_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.BitSet.iterator:

.globl std.collections.queue.BitSet.get_size
std.collections.queue.BitSet.get_size:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.BitSet.get_size_entry:
  movq $0, rax
  jmp std.collections.queue.BitSet.get_size_epilogue
std.collections.queue.BitSet.get_size_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.BitSet.get_size:

.globl std.collections.queue.BitSet.get
std.collections.queue.BitSet.get:
  push rbp
  mov rbp, rsp
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
std.collections.queue.BitSet.get_entry:
  movq $0, rax
  jmp std.collections.queue.BitSet.get_epilogue
std.collections.queue.BitSet.get_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.BitSet.get:

.globl std.collections.queue.BitSet.contains
std.collections.queue.BitSet.contains:
  push rbp
  mov rbp, rsp
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
std.collections.queue.BitSet.contains_entry:
  movq $0, rax
  jmp std.collections.queue.BitSet.contains_epilogue
std.collections.queue.BitSet.contains_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.BitSet.contains:

.globl std.collections.queue.BitSet.toggle
std.collections.queue.BitSet.toggle:
  push rbp
  mov rbp, rsp
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
std.collections.queue.BitSet.toggle_entry:
  movq $0, rax
  jmp std.collections.queue.BitSet.toggle_epilogue
std.collections.queue.BitSet.toggle_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.BitSet.toggle:

.globl std.collections.vector.Vector.get
std.collections.vector.Vector.get:
  push rbp
  mov rbp, rsp
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
std.collections.vector.Vector.get_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.get_epilogue
std.collections.vector.Vector.get_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.get:

.globl std.collections.vector.RingBuffer.init
std.collections.vector.RingBuffer.init:
  push rbp
  mov rbp, rsp
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
std.collections.vector.RingBuffer.init_entry:
  movq $0, rax
  jmp std.collections.vector.RingBuffer.init_epilogue
std.collections.vector.RingBuffer.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.RingBuffer.init:

.globl std.collections.vector.ArrayList.remove
std.collections.vector.ArrayList.remove:
  push rbp
  mov rbp, rsp
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
std.collections.vector.ArrayList.remove_entry:
  movq $0, rax
  jmp std.collections.vector.ArrayList.remove_epilogue
std.collections.vector.ArrayList.remove_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.ArrayList.remove:

.globl std.iterator.collect
std.iterator.collect:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.collect_entry:
std.iterator.collect_block_0:
  movq $0, rcx
  call lm_list_new
  jmp std.iterator.collect_block_5
std.iterator.collect_block_5:
  movq $0, rax
  cmpq $2, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.iterator.collect_block_8
  jmp std.iterator.collect_block_12
std.iterator.collect_block_8:
  jmp std.iterator.collect_block_8
  movq $r1, rcx
  movq $0, rdx
  call lm_list_append
  jmp std.iterator.collect_block_5
std.iterator.collect_block_12:
  movq $r1, rax
  jmp std.iterator.collect_epilogue
std.iterator.collect_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.collect:

.globl std.collections.vector.Vector.push
std.collections.vector.Vector.push:
  push rbp
  mov rbp, rsp
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
std.collections.vector.Vector.push_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.push_epilogue
std.collections.vector.Vector.push_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.push:

.globl std.iterator.cycle
std.iterator.cycle:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.cycle_entry:
std.iterator.cycle_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.iterator.CycleIterator.init
  movq [rbp + -72], rax
  jmp std.iterator.cycle_epilogue
std.iterator.cycle_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.cycle:

.globl std.iterator.filter
std.iterator.filter:
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
std.iterator.filter_entry:
std.iterator.filter_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.iterator.FilterIterator.init
  movq [rbp + -80], rax
  jmp std.iterator.filter_epilogue
std.iterator.filter_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.filter:

.globl std.iterator.iterator
std.iterator.iterator:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.iterator_entry:
std.iterator.iterator_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.iterator.ListIterator.init
  movq [rbp + -72], rax
  jmp std.iterator.iterator_epilogue
std.iterator.iterator_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.iterator:

.globl std.collections.vector.Vector.append
std.collections.vector.Vector.append:
  push rbp
  mov rbp, rsp
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
std.collections.vector.Vector.append_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.append_epilogue
std.collections.vector.Vector.append_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.append:

.globl std.iterator.ListIterator.next
std.iterator.ListIterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.ListIterator.next_entry:
  movq $0, rax
  jmp std.iterator.ListIterator.next_epilogue
std.iterator.ListIterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.ListIterator.next:

.globl std.iterator.CycleIterator.init
std.iterator.CycleIterator.init:
  push rbp
  mov rbp, rsp
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
std.iterator.CycleIterator.init_entry:
  movq $0, rax
  jmp std.iterator.CycleIterator.init_epilogue
std.iterator.CycleIterator.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.CycleIterator.init:

.globl std.iterator.ChunkIterator.init
std.iterator.ChunkIterator.init:
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
std.iterator.ChunkIterator.init_entry:
  movq $0, rax
  jmp std.iterator.ChunkIterator.init_epilogue
std.iterator.ChunkIterator.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.ChunkIterator.init:

.globl std.iterator.PeekableIterator.peek
std.iterator.PeekableIterator.peek:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.PeekableIterator.peek_entry:
  movq $0, rax
  jmp std.iterator.PeekableIterator.peek_epilogue
std.iterator.PeekableIterator.peek_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.PeekableIterator.peek:

.globl std.iterator.ChunkIterator.next
std.iterator.ChunkIterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.ChunkIterator.next_entry:
  movq $0, rax
  jmp std.iterator.ChunkIterator.next_epilogue
std.iterator.ChunkIterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.ChunkIterator.next:

.globl std.iterator.MapIterator.init
std.iterator.MapIterator.init:
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
std.iterator.MapIterator.init_entry:
  movq $0, rax
  jmp std.iterator.MapIterator.init_epilogue
std.iterator.MapIterator.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.MapIterator.init:

.globl std.iterator.StepByIterator.next
std.iterator.StepByIterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.StepByIterator.next_entry:
  movq $0, rax
  jmp std.iterator.StepByIterator.next_epilogue
std.iterator.StepByIterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.StepByIterator.next:

.globl std.collections.queue.BitSet._mask
std.collections.queue.BitSet._mask:
  push rbp
  mov rbp, rsp
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
std.collections.queue.BitSet._mask_entry:
  movq $0, rax
  jmp std.collections.queue.BitSet._mask_epilogue
std.collections.queue.BitSet._mask_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.BitSet._mask:

.globl std.collections.vector.Vector.pop
std.collections.vector.Vector.pop:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Vector.pop_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.pop_epilogue
std.collections.vector.Vector.pop_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.pop:

.globl std.collections.vector.Deque.pop_front
std.collections.vector.Deque.pop_front:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Deque.pop_front_entry:
  movq $0, rax
  jmp std.collections.vector.Deque.pop_front_epilogue
std.collections.vector.Deque.pop_front_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Deque.pop_front:

.globl std.iterator.SkipIterator.init
std.iterator.SkipIterator.init:
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
std.iterator.SkipIterator.init_entry:
  movq $0, rax
  jmp std.iterator.SkipIterator.init_epilogue
std.iterator.SkipIterator.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.SkipIterator.init:

.globl std.iterator.ListIterator.init
std.iterator.ListIterator.init:
  push rbp
  mov rbp, rsp
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
std.iterator.ListIterator.init_entry:
  movq $0, rax
  jmp std.iterator.ListIterator.init_epilogue
std.iterator.ListIterator.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.ListIterator.init:

.globl std.collections.queue.Queue.peek
std.collections.queue.Queue.peek:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.Queue.peek_entry:
  movq $0, rax
  jmp std.collections.queue.Queue.peek_epilogue
std.collections.queue.Queue.peek_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.Queue.peek:

.globl std.collections.queue.PriorityQueue._sift_up
std.collections.queue.PriorityQueue._sift_up:
  push rbp
  mov rbp, rsp
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
std.collections.queue.PriorityQueue._sift_up_entry:
  movq $0, rax
  jmp std.collections.queue.PriorityQueue._sift_up_epilogue
std.collections.queue.PriorityQueue._sift_up_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.PriorityQueue._sift_up:

.globl std.collections.queue.BitSetIterator.next
std.collections.queue.BitSetIterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.BitSetIterator.next_entry:
  movq $0, rax
  jmp std.collections.queue.BitSetIterator.next_epilogue
std.collections.queue.BitSetIterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.BitSetIterator.next:

.globl std.collections.vector.Vector._copy_without
std.collections.vector.Vector._copy_without:
  push rbp
  mov rbp, rsp
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
std.collections.vector.Vector._copy_without_entry:
  movq $0, rax
  jmp std.collections.vector.Vector._copy_without_epilogue
std.collections.vector.Vector._copy_without_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector._copy_without:

.globl std.collections.vector.Deque.length
std.collections.vector.Deque.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Deque.length_entry:
  movq $0, rax
  jmp std.collections.vector.Deque.length_epilogue
std.collections.vector.Deque.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Deque.length:

.globl std.collections.vector.Deque.size
std.collections.vector.Deque.size:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Deque.size_entry:
  movq $0, rax
  jmp std.collections.vector.Deque.size_epilogue
std.collections.vector.Deque.size_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Deque.size:

.globl std.iterator.PeekableIterator.next
std.iterator.PeekableIterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.PeekableIterator.next_entry:
  movq $0, rax
  jmp std.iterator.PeekableIterator.next_epilogue
std.iterator.PeekableIterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.PeekableIterator.next:

.globl std.iterator.MapIterator.next
std.iterator.MapIterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.MapIterator.next_entry:
  movq $0, rax
  jmp std.iterator.MapIterator.next_epilogue
std.iterator.MapIterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.MapIterator.next:

.globl std.iterator.SkipIterator.next
std.iterator.SkipIterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.SkipIterator.next_entry:
  movq $0, rax
  jmp std.iterator.SkipIterator.next_epilogue
std.iterator.SkipIterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.SkipIterator.next:

.globl std.collections.vector.Vector.len
std.collections.vector.Vector.len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Vector.len_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.len_epilogue
std.collections.vector.Vector.len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.len:

.globl std.iterator.chunk
std.iterator.chunk:
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
std.iterator.chunk_entry:
std.iterator.chunk_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.iterator.ChunkIterator.init
  movq [rbp + -80], rax
  jmp std.iterator.chunk_epilogue
std.iterator.chunk_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.chunk:

.globl std.collections.vector.Vector.size
std.collections.vector.Vector.size:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Vector.size_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.size_epilogue
std.collections.vector.Vector.size_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.size:

.globl std.iterator.map
std.iterator.map:
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
std.iterator.map_entry:
std.iterator.map_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.iterator.MapIterator.init
  movq [rbp + -80], rax
  jmp std.iterator.map_epilogue
std.iterator.map_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.map:

.globl std.collections.vector.__init__
std.collections.vector.__init__:
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
std.collections.vector.__init___entry:
  movq $0, rax
  jmp std.collections.vector.__init___epilogue
std.collections.vector.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.__init__:

.globl std.collections.vector.Vector._grow_for
std.collections.vector.Vector._grow_for:
  push rbp
  mov rbp, rsp
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
std.collections.vector.Vector._grow_for_entry:
  movq $0, rax
  jmp std.collections.vector.Vector._grow_for_epilogue
std.collections.vector.Vector._grow_for_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector._grow_for:

.globl std.iterator.ZipIterator.init
std.iterator.ZipIterator.init:
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
std.iterator.ZipIterator.init_entry:
  movq $0, rax
  jmp std.iterator.ZipIterator.init_epilogue
std.iterator.ZipIterator.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.ZipIterator.init:

.globl std.collections.vector.Deque.iterator
std.collections.vector.Deque.iterator:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Deque.iterator_entry:
  movq $0, rax
  jmp std.collections.vector.Deque.iterator_epilogue
std.collections.vector.Deque.iterator_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Deque.iterator:

.globl std.collections.queue.Queue.init
std.collections.queue.Queue.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.Queue.init_entry:
  movq $0, rax
  jmp std.collections.queue.Queue.init_epilogue
std.collections.queue.Queue.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.Queue.init:

.globl std.collections.vector.Vector.is_empty
std.collections.vector.Vector.is_empty:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Vector.is_empty_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.is_empty_epilogue
std.collections.vector.Vector.is_empty_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.is_empty:

.globl std.iterator.TakeIterator.init
std.iterator.TakeIterator.init:
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
std.iterator.TakeIterator.init_entry:
  movq $0, rax
  jmp std.iterator.TakeIterator.init_epilogue
std.iterator.TakeIterator.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.TakeIterator.init:

.globl std.collections.queue.PriorityQueue._sift_down
std.collections.queue.PriorityQueue._sift_down:
  push rbp
  mov rbp, rsp
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
std.collections.queue.PriorityQueue._sift_down_entry:
  movq $0, rax
  jmp std.collections.queue.PriorityQueue._sift_down_epilogue
std.collections.queue.PriorityQueue._sift_down_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.PriorityQueue._sift_down:

.globl std.collections.vector.Deque.push_back
std.collections.vector.Deque.push_back:
  push rbp
  mov rbp, rsp
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
std.collections.vector.Deque.push_back_entry:
  movq $0, rax
  jmp std.collections.vector.Deque.push_back_epilogue
std.collections.vector.Deque.push_back_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Deque.push_back:

.globl std.collections.vector.ArrayList.init
std.collections.vector.ArrayList.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.ArrayList.init_entry:
  movq $0, rax
  jmp std.collections.vector.ArrayList.init_epilogue
std.collections.vector.ArrayList.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.ArrayList.init:

.globl std.collections.vector.Vector.set
std.collections.vector.Vector.set:
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
std.collections.vector.Vector.set_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.set_epilogue
std.collections.vector.Vector.set_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.set:

.globl std.iterator.EnumerateIterator.next
std.iterator.EnumerateIterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.EnumerateIterator.next_entry:
  movq $0, rax
  jmp std.iterator.EnumerateIterator.next_epilogue
std.iterator.EnumerateIterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.EnumerateIterator.next:

.globl std.iterator.CycleIterator.next
std.iterator.CycleIterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.CycleIterator.next_entry:
  movq $0, rax
  jmp std.iterator.CycleIterator.next_epilogue
std.iterator.CycleIterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.CycleIterator.next:

.globl std.collections.queue.BitSet.unset
std.collections.queue.BitSet.unset:
  push rbp
  mov rbp, rsp
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
std.collections.queue.BitSet.unset_entry:
  movq $0, rax
  jmp std.collections.queue.BitSet.unset_epilogue
std.collections.queue.BitSet.unset_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.BitSet.unset:

.globl std.collections.queue.BitSet.count
std.collections.queue.BitSet.count:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.BitSet.count_entry:
  movq $0, rax
  jmp std.collections.queue.BitSet.count_epilogue
std.collections.queue.BitSet.count_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.BitSet.count:

.globl std.collections.vector.Vector.remove
std.collections.vector.Vector.remove:
  push rbp
  mov rbp, rsp
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
std.collections.vector.Vector.remove_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.remove_epilogue
std.collections.vector.Vector.remove_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.remove:

.globl std.iterator.ChainIterator.init
std.iterator.ChainIterator.init:
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
std.iterator.ChainIterator.init_entry:
  movq $0, rax
  jmp std.iterator.ChainIterator.init_epilogue
std.iterator.ChainIterator.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.ChainIterator.init:

.globl std.collections.vector.Vector.peek
std.collections.vector.Vector.peek:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Vector.peek_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.peek_epilogue
std.collections.vector.Vector.peek_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.peek:

.globl std.iterator.TakeIterator.next
std.iterator.TakeIterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.TakeIterator.next_entry:
  movq $0, rax
  jmp std.iterator.TakeIterator.next_epilogue
std.iterator.TakeIterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.TakeIterator.next:

.globl std.collections.vector.Deque.peek_back
std.collections.vector.Deque.peek_back:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Deque.peek_back_entry:
  movq $0, rax
  jmp std.collections.vector.Deque.peek_back_epilogue
std.collections.vector.Deque.peek_back_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Deque.peek_back:

.globl std.collections.queue.Queue.dequeue
std.collections.queue.Queue.dequeue:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.Queue.dequeue_entry:
  movq $0, rax
  jmp std.collections.queue.Queue.dequeue_epilogue
std.collections.queue.Queue.dequeue_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.Queue.dequeue:

.globl std.iterator.FilterIterator.init
std.iterator.FilterIterator.init:
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
std.iterator.FilterIterator.init_entry:
  movq $0, rax
  jmp std.iterator.FilterIterator.init_epilogue
std.iterator.FilterIterator.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.FilterIterator.init:

.globl std.iterator.PeekableIterator.init
std.iterator.PeekableIterator.init:
  push rbp
  mov rbp, rsp
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
std.iterator.PeekableIterator.init_entry:
  movq $0, rax
  jmp std.iterator.PeekableIterator.init_epilogue
std.iterator.PeekableIterator.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.PeekableIterator.init:

.globl std.collections.vector.ArrayList.set
std.collections.vector.ArrayList.set:
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
std.collections.vector.ArrayList.set_entry:
  movq $0, rax
  jmp std.collections.vector.ArrayList.set_epilogue
std.collections.vector.ArrayList.set_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.ArrayList.set:

.globl std.collections.vector.RingBuffer.pop
std.collections.vector.RingBuffer.pop:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.RingBuffer.pop_entry:
  movq $0, rax
  jmp std.collections.vector.RingBuffer.pop_epilogue
std.collections.vector.RingBuffer.pop_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.RingBuffer.pop:

.globl std.collections.vector.Vector.insert
std.collections.vector.Vector.insert:
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
std.collections.vector.Vector.insert_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.insert_epilogue
std.collections.vector.Vector.insert_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.insert:

.globl std.iterator.EnumerateIterator.init
std.iterator.EnumerateIterator.init:
  push rbp
  mov rbp, rsp
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
std.iterator.EnumerateIterator.init_entry:
  movq $0, rax
  jmp std.iterator.EnumerateIterator.init_epilogue
std.iterator.EnumerateIterator.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.EnumerateIterator.init:

.globl std.collections.vector.RingBuffer.length
std.collections.vector.RingBuffer.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.RingBuffer.length_entry:
  movq $0, rax
  jmp std.collections.vector.RingBuffer.length_epilogue
std.collections.vector.RingBuffer.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.RingBuffer.length:

.globl std.collections.vector.Deque.len
std.collections.vector.Deque.len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Deque.len_entry:
  movq $0, rax
  jmp std.collections.vector.Deque.len_epilogue
std.collections.vector.Deque.len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Deque.len:

.globl std.iterator.FilterIterator.next
std.iterator.FilterIterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.FilterIterator.next_entry:
  movq $0, rax
  jmp std.iterator.FilterIterator.next_epilogue
std.iterator.FilterIterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.FilterIterator.next:

.globl std.collections.queue.PriorityQueue.length
std.collections.queue.PriorityQueue.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.PriorityQueue.length_entry:
  movq $0, rax
  jmp std.collections.queue.PriorityQueue.length_epilogue
std.collections.queue.PriorityQueue.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.PriorityQueue.length:

.globl std.iterator.ZipIterator.next
std.iterator.ZipIterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.ZipIterator.next_entry:
  movq $0, rax
  jmp std.iterator.ZipIterator.next_epilogue
std.iterator.ZipIterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.ZipIterator.next:

.globl std.iterator.ChainIterator.next
std.iterator.ChainIterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.iterator.ChainIterator.next_entry:
  movq $0, rax
  jmp std.iterator.ChainIterator.next_epilogue
std.iterator.ChainIterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.ChainIterator.next:

.globl std.collections.vector.Vector.reserve
std.collections.vector.Vector.reserve:
  push rbp
  mov rbp, rsp
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
std.collections.vector.Vector.reserve_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.reserve_epilogue
std.collections.vector.Vector.reserve_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.reserve:

.globl std.collections.vector.Vector.clear
std.collections.vector.Vector.clear:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Vector.clear_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.clear_epilogue
std.collections.vector.Vector.clear_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.clear:

.globl std.collections.vector.Vector.iterator
std.collections.vector.Vector.iterator:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Vector.iterator_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.iterator_epilogue
std.collections.vector.Vector.iterator_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.iterator:

.globl std.collections.queue.PriorityQueue.insert
std.collections.queue.PriorityQueue.insert:
  push rbp
  mov rbp, rsp
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
std.collections.queue.PriorityQueue.insert_entry:
  movq $0, rax
  jmp std.collections.queue.PriorityQueue.insert_epilogue
std.collections.queue.PriorityQueue.insert_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.PriorityQueue.insert:

.globl std.collections.queue.PriorityQueue.pop
std.collections.queue.PriorityQueue.pop:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.PriorityQueue.pop_entry:
  movq $0, rax
  jmp std.collections.queue.PriorityQueue.pop_epilogue
std.collections.queue.PriorityQueue.pop_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.PriorityQueue.pop:

.globl std.collections.vector.Vector.init
std.collections.vector.Vector.init:
  push rbp
  mov rbp, rsp
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
std.collections.vector.Vector.init_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.init_epilogue
std.collections.vector.Vector.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.init:

.globl std.collections.vector.VectorIterator.next
std.collections.vector.VectorIterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.VectorIterator.next_entry:
  movq $0, rax
  jmp std.collections.vector.VectorIterator.next_epilogue
std.collections.vector.VectorIterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.VectorIterator.next:

.globl std.collections.queue.BitSet._word_value
std.collections.queue.BitSet._word_value:
  push rbp
  mov rbp, rsp
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
std.collections.queue.BitSet._word_value_entry:
  movq $0, rax
  jmp std.collections.queue.BitSet._word_value_epilogue
std.collections.queue.BitSet._word_value_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.BitSet._word_value:

.globl std.collections.vector.VectorIterator.init
std.collections.vector.VectorIterator.init:
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
std.collections.vector.VectorIterator.init_entry:
  movq $0, rax
  jmp std.collections.vector.VectorIterator.init_epilogue
std.collections.vector.VectorIterator.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.VectorIterator.init:

.globl std.collections.vector.Deque.peek_front
std.collections.vector.Deque.peek_front:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Deque.peek_front_entry:
  movq $0, rax
  jmp std.collections.vector.Deque.peek_front_epilogue
std.collections.vector.Deque.peek_front_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Deque.peek_front:

.globl std.collections.vector.Deque.push_front
std.collections.vector.Deque.push_front:
  push rbp
  mov rbp, rsp
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
std.collections.vector.Deque.push_front_entry:
  movq $0, rax
  jmp std.collections.vector.Deque.push_front_epilogue
std.collections.vector.Deque.push_front_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Deque.push_front:

.globl std.collections.queue.Stack.init
std.collections.queue.Stack.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.Stack.init_entry:
  movq $0, rax
  jmp std.collections.queue.Stack.init_epilogue
std.collections.queue.Stack.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.Stack.init:

.globl std.collections.vector.Deque.pop_back
std.collections.vector.Deque.pop_back:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Deque.pop_back_entry:
  movq $0, rax
  jmp std.collections.vector.Deque.pop_back_epilogue
std.collections.vector.Deque.pop_back_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Deque.pop_back:

.globl std.collections.vector.Deque.init
std.collections.vector.Deque.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Deque.init_entry:
  movq $0, rax
  jmp std.collections.vector.Deque.init_epilogue
std.collections.vector.Deque.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Deque.init:

.globl std.iterator.StepByIterator.init
std.iterator.StepByIterator.init:
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
std.iterator.StepByIterator.init_entry:
  movq $0, rax
  jmp std.iterator.StepByIterator.init_epilogue
std.iterator.StepByIterator.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.StepByIterator.init:

.globl std.collections.vector.ArrayList.push
std.collections.vector.ArrayList.push:
  push rbp
  mov rbp, rsp
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
std.collections.vector.ArrayList.push_entry:
  movq $0, rax
  jmp std.collections.vector.ArrayList.push_epilogue
std.collections.vector.ArrayList.push_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.ArrayList.push:

.globl std.collections.vector.ArrayList.pop
std.collections.vector.ArrayList.pop:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.ArrayList.pop_entry:
  movq $0, rax
  jmp std.collections.vector.ArrayList.pop_epilogue
std.collections.vector.ArrayList.pop_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.ArrayList.pop:

.globl std.collections.vector.ArrayList.resize
std.collections.vector.ArrayList.resize:
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
std.collections.vector.ArrayList.resize_entry:
  movq $0, rax
  jmp std.collections.vector.ArrayList.resize_epilogue
std.collections.vector.ArrayList.resize_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.ArrayList.resize:

.globl std.collections.vector.ArrayList.len
std.collections.vector.ArrayList.len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.ArrayList.len_entry:
  movq $0, rax
  jmp std.collections.vector.ArrayList.len_epilogue
std.collections.vector.ArrayList.len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.ArrayList.len:

.globl std.collections.vector.ArrayList.length
std.collections.vector.ArrayList.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.ArrayList.length_entry:
  movq $0, rax
  jmp std.collections.vector.ArrayList.length_epilogue
std.collections.vector.ArrayList.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.ArrayList.length:

.globl std.collections.vector.ArrayList.iterator
std.collections.vector.ArrayList.iterator:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.ArrayList.iterator_entry:
  movq $0, rax
  jmp std.collections.vector.ArrayList.iterator_epilogue
std.collections.vector.ArrayList.iterator_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.ArrayList.iterator:

.globl std.collections.queue.PriorityQueue.len
std.collections.queue.PriorityQueue.len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.PriorityQueue.len_entry:
  movq $0, rax
  jmp std.collections.queue.PriorityQueue.len_epilogue
std.collections.queue.PriorityQueue.len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.PriorityQueue.len:

.globl std.collections.vector.RingBuffer.push
std.collections.vector.RingBuffer.push:
  push rbp
  mov rbp, rsp
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
std.collections.vector.RingBuffer.push_entry:
  movq $0, rax
  jmp std.collections.vector.RingBuffer.push_epilogue
std.collections.vector.RingBuffer.push_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.RingBuffer.push:

.globl std.collections.queue.Queue.enqueue
std.collections.queue.Queue.enqueue:
  push rbp
  mov rbp, rsp
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
std.collections.queue.Queue.enqueue_entry:
  movq $0, rax
  jmp std.collections.queue.Queue.enqueue_epilogue
std.collections.queue.Queue.enqueue_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.Queue.enqueue:

.globl std.collections.vector.Vector.length
std.collections.vector.Vector.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.Vector.length_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.length_epilogue
std.collections.vector.Vector.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.length:

.globl std.collections.vector.RingBuffer.len
std.collections.vector.RingBuffer.len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.RingBuffer.len_entry:
  movq $0, rax
  jmp std.collections.vector.RingBuffer.len_epilogue
std.collections.vector.RingBuffer.len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.RingBuffer.len:

.globl std.collections.vector.Vector.resize
std.collections.vector.Vector.resize:
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
std.collections.vector.Vector.resize_entry:
  movq $0, rax
  jmp std.collections.vector.Vector.resize_epilogue
std.collections.vector.Vector.resize_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.Vector.resize:

.globl std.collections.vector.RingBuffer.size
std.collections.vector.RingBuffer.size:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.RingBuffer.size_entry:
  movq $0, rax
  jmp std.collections.vector.RingBuffer.size_epilogue
std.collections.vector.RingBuffer.size_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.RingBuffer.size:

.globl std.collections.vector.ArrayList.size
std.collections.vector.ArrayList.size:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.vector.ArrayList.size_entry:
  movq $0, rax
  jmp std.collections.vector.ArrayList.size_epilogue
std.collections.vector.ArrayList.size_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.ArrayList.size:

.globl std.collections.queue.Queue.len
std.collections.queue.Queue.len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.Queue.len_entry:
  movq $0, rax
  jmp std.collections.queue.Queue.len_epilogue
std.collections.queue.Queue.len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.Queue.len:

.globl std.collections.queue.PriorityQueue.push
std.collections.queue.PriorityQueue.push:
  push rbp
  mov rbp, rsp
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
std.collections.queue.PriorityQueue.push_entry:
  movq $0, rax
  jmp std.collections.queue.PriorityQueue.push_epilogue
std.collections.queue.PriorityQueue.push_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.PriorityQueue.push:

.globl std.collections.queue.PriorityQueue.peek
std.collections.queue.PriorityQueue.peek:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.PriorityQueue.peek_entry:
  movq $0, rax
  jmp std.collections.queue.PriorityQueue.peek_epilogue
std.collections.queue.PriorityQueue.peek_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.PriorityQueue.peek:

.globl std.iterator.__init__
std.iterator.__init__:
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
std.iterator.__init___entry:
  movq $0, rax
  jmp std.iterator.__init___epilogue
std.iterator.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.iterator.__init__:

.globl std.collections.queue.PriorityQueue.remove
std.collections.queue.PriorityQueue.remove:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.PriorityQueue.remove_entry:
  movq $0, rax
  jmp std.collections.queue.PriorityQueue.remove_epilogue
std.collections.queue.PriorityQueue.remove_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.PriorityQueue.remove:

.globl std.collections.queue.PriorityQueue._compare
std.collections.queue.PriorityQueue._compare:
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
std.collections.queue.PriorityQueue._compare_entry:
  movq $0, rax
  jmp std.collections.queue.PriorityQueue._compare_epilogue
std.collections.queue.PriorityQueue._compare_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.PriorityQueue._compare:

.globl std.collections.queue.PriorityQueue.init
std.collections.queue.PriorityQueue.init:
  push rbp
  mov rbp, rsp
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
std.collections.queue.PriorityQueue.init_entry:
  movq $0, rax
  jmp std.collections.queue.PriorityQueue.init_epilogue
std.collections.queue.PriorityQueue.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.PriorityQueue.init:

.globl std.collections.vector.ArrayList.get
std.collections.vector.ArrayList.get:
  push rbp
  mov rbp, rsp
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
std.collections.vector.ArrayList.get_entry:
  movq $0, rax
  jmp std.collections.vector.ArrayList.get_epilogue
std.collections.vector.ArrayList.get_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.vector.ArrayList.get:

.globl std.collections.queue.Stack.push
std.collections.queue.Stack.push:
  push rbp
  mov rbp, rsp
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
std.collections.queue.Stack.push_entry:
  movq $0, rax
  jmp std.collections.queue.Stack.push_epilogue
std.collections.queue.Stack.push_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.Stack.push:

.globl std.collections.queue.Stack.pop
std.collections.queue.Stack.pop:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.Stack.pop_entry:
  movq $0, rax
  jmp std.collections.queue.Stack.pop_epilogue
std.collections.queue.Stack.pop_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.Stack.pop:

.globl std.collections.queue.Queue.length
std.collections.queue.Queue.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.Queue.length_entry:
  movq $0, rax
  jmp std.collections.queue.Queue.length_epilogue
std.collections.queue.Queue.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.Queue.length:

.globl std.collections.queue.BitSet._valid
std.collections.queue.BitSet._valid:
  push rbp
  mov rbp, rsp
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
std.collections.queue.BitSet._valid_entry:
  movq $0, rax
  jmp std.collections.queue.BitSet._valid_epilogue
std.collections.queue.BitSet._valid_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.BitSet._valid:

.globl std.collections.queue.Stack.peek
std.collections.queue.Stack.peek:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.Stack.peek_entry:
  movq $0, rax
  jmp std.collections.queue.Stack.peek_epilogue
std.collections.queue.Stack.peek_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.Stack.peek:

.globl std.collections.queue.Stack.len
std.collections.queue.Stack.len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.Stack.len_entry:
  movq $0, rax
  jmp std.collections.queue.Stack.len_epilogue
std.collections.queue.Stack.len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.Stack.len:

.globl std.collections.queue.Stack.length
std.collections.queue.Stack.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.queue.Stack.length_entry:
  movq $0, rax
  jmp std.collections.queue.Stack.length_epilogue
std.collections.queue.Stack.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.Stack.length:

.globl std.collections.queue.BitSet._set_word
std.collections.queue.BitSet._set_word:
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
std.collections.queue.BitSet._set_word_entry:
  movq $0, rax
  jmp std.collections.queue.BitSet._set_word_epilogue
std.collections.queue.BitSet._set_word_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.BitSet._set_word:

.globl std.collections.queue.BitSet.set
std.collections.queue.BitSet.set:
  push rbp
  mov rbp, rsp
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
std.collections.queue.BitSet.set_entry:
  movq $0, rax
  jmp std.collections.queue.BitSet.set_epilogue
std.collections.queue.BitSet.set_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.queue.BitSet.set:

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

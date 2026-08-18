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
  .string "ERR"
.align 8
str_const_1:
  .string ""
.align 8
str_const_2:
  .string ""
.align 8
str_const_3:
  .string ""
.align 8
str_const_4:
  .string ""
.align 8
str_const_5:
  .string ""
.align 8
str_const_6:
  .string "ERR"
.align 8
str_const_7:
  .string "ERR"
.align 8
str_const_8:
  .string ""
.align 8
str_const_9:
  .string ""
.align 8
str_const_10:
  .string "ERR"
.align 8
str_const_11:
  .string ""
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
  sub rsp, 88
main_entry:
main_block_0:
  call std.collections.index.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  call std.collections.index.Queue
  movq $r0, rcx
  movq $9, rdx
  call std.collections.queue.Queue.enqueue
  movq $r0, rcx
  movq $17, rdx
  call std.collections.queue.Queue.enqueue
  movq $r0, rcx
  call std.collections.queue.Queue.peek
  movq $r6, rax
  cmpq $9, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  testq rax, rax
  jne main_block_10
  jmp main_block_12
main_block_10:
  jmp main_block_10
  movq $9, rax
  jmp main_epilogue
main_block_12:
  movq $r0, rcx
  call std.collections.queue.Queue.dequeue
  movq $r11, rax
  cmpq $9, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne main_block_16
  jmp main_block_18
main_block_16:
  jmp main_block_16
  movq $17, rax
  jmp main_epilogue
main_block_18:
  call std.collections.index.Stack
  movq $r16, rcx
  movq $25, rdx
  call std.collections.stack.Stack.push
  movq $r16, rcx
  movq $33, rdx
  call std.collections.stack.Stack.push
  movq $r16, rcx
  call std.collections.stack.Stack.peek
  movq $r22, rax
  cmpq $33, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne main_block_28
  jmp main_block_30
main_block_28:
  jmp main_block_28
  movq $25, rax
  jmp main_epilogue
main_block_30:
  movq $r16, rcx
  call std.collections.stack.Stack.pop
  movq $r27, rax
  cmpq $33, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne main_block_34
  jmp main_block_36
main_block_34:
  jmp main_block_34
  movq $33, rax
  jmp main_epilogue
main_block_36:
  movq $1041, rcx
  call std.collections.index.BitSet
  movq $r33, rcx
  movq $513, rdx
  call std.collections.queue.BitSet.toggle
  movq $r33, rcx
  movq $513, rdx
  call std.collections.queue.BitSet.contains
  movq $r38, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne main_block_46
  jmp main_block_48
main_block_46:
  jmp main_block_46
  movq $41, rax
  jmp main_epilogue
main_block_48:
  movq $r33, rcx
  movq $513, rdx
  call std.collections.queue.BitSet.toggle
  movq $r33, rcx
  movq $513, rdx
  call std.collections.queue.BitSet.contains
  movq $r46, rax
  testq rax, rax
  jne main_block_53
  jmp main_block_55
main_block_53:
  jmp main_block_53
  movq $49, rax
  jmp main_epilogue
main_block_55:
  movq $r33, rcx
  movq $25, rdx
  call std.collections.queue.BitSet.toggle
  movq $r33, rcx
  movq $25, rdx
  call std.collections.queue.BitSet.unset
  movq $r33, rcx
  call std.collections.queue.BitSet.count
  movq $r53, rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne main_block_63
  jmp main_block_65
main_block_63:
  jmp main_block_63
  movq $57, rax
  jmp main_epilogue
main_block_65:
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

.globl std.collections.index.BloomFilter
std.collections.index.BloomFilter:
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
std.collections.index.BloomFilter_entry:
std.collections.index.BloomFilter_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.collections.bloom_filter.BloomFilter.init
  movq [rbp + -80], rax
  jmp std.collections.index.BloomFilter_epilogue
std.collections.index.BloomFilter_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.BloomFilter:

.globl std.collections.index.BitSet
std.collections.index.BitSet:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.index.BitSet_entry:
std.collections.index.BitSet_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.collections.bitset.BitSetWrapper.init
  movq [rbp + -72], rax
  jmp std.collections.index.BitSet_epilogue
std.collections.index.BitSet_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.BitSet:

.globl std.collections.index.PriorityQueue
std.collections.index.PriorityQueue:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.index.PriorityQueue_entry:
std.collections.index.PriorityQueue_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.collections.priority_queue.PriorityQueueWrapper.init
  movq [rbp + -72], rax
  jmp std.collections.index.PriorityQueue_epilogue
std.collections.index.PriorityQueue_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.PriorityQueue:

.globl std.collections.index.HashMap
std.collections.index.HashMap:
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
std.collections.index.HashMap_entry:
std.collections.index.HashMap_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq $0, rcx
  call lm_list_new
  movq [rbp + -64], rax
  addq $0, rax
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  movq $0, rcx
  call lm_list_new
  movq [rbp + -64], rax
  addq $0, rax
  movq rax, [rbp + -80]
  movq $r1, rax
  movq [rbp + -80], rdx
  mov [rdx], rax
  movq $0, rax
  jmp std.collections.index.HashMap_epilogue
std.collections.index.HashMap_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.HashMap:

.globl std.collections.index.Map
std.collections.index.Map:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.collections.index.Map_entry:
std.collections.index.Map_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.collections.map.HashMapWrapper.init
  movq $0, rax
  jmp std.collections.index.Map_epilogue
std.collections.index.Map_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.Map:

.globl std.collections.index.LinkedList
std.collections.index.LinkedList:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.collections.index.LinkedList_entry:
std.collections.index.LinkedList_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.collections.linked_list.DLL.init
  movq $0, rax
  jmp std.collections.index.LinkedList_epilogue
std.collections.index.LinkedList_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.LinkedList:

.globl std.collections.index.Vector
std.collections.index.Vector:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.index.Vector_entry:
std.collections.index.Vector_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.collections.vector.Vector.init
  movq [rbp + -72], rax
  jmp std.collections.index.Vector_epilogue
std.collections.index.Vector_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.Vector:

.globl std.collections.linkedlist.LinkedList.init
std.collections.linkedlist.LinkedList.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.linkedlist.LinkedList.init_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.init_epilogue
std.collections.linkedlist.LinkedList.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linkedlist.LinkedList.init:

.globl std.collections.linkedlist.LinkedList.pop_front
std.collections.linkedlist.LinkedList.pop_front:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.linkedlist.LinkedList.pop_front_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.pop_front_epilogue
std.collections.linkedlist.LinkedList.pop_front_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linkedlist.LinkedList.pop_front:

.globl std.collections.linkedlist.LinkedList.push_front
std.collections.linkedlist.LinkedList.push_front:
  push rbp
  mov rbp, rsp
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
std.collections.linkedlist.LinkedList.push_front_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.push_front_epilogue
std.collections.linkedlist.LinkedList.push_front_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linkedlist.LinkedList.push_front:

.globl std.collections.linkedlist.LinkedList.iterator
std.collections.linkedlist.LinkedList.iterator:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.linkedlist.LinkedList.iterator_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.iterator_epilogue
std.collections.linkedlist.LinkedList.iterator_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linkedlist.LinkedList.iterator:

.globl std.collections.linkedlist.LinkedList.push_back
std.collections.linkedlist.LinkedList.push_back:
  push rbp
  mov rbp, rsp
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
std.collections.linkedlist.LinkedList.push_back_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.push_back_epilogue
std.collections.linkedlist.LinkedList.push_back_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linkedlist.LinkedList.push_back:

.globl std.collections.linkedlist.Node.init
std.collections.linkedlist.Node.init:
  push rbp
  mov rbp, rsp
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
std.collections.linkedlist.Node.init_entry:
  movq $0, rax
  jmp std.collections.linkedlist.Node.init_epilogue
std.collections.linkedlist.Node.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linkedlist.Node.init:

.globl std.collections.linked_list.__init__
std.collections.linked_list.__init__:
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
std.collections.linked_list.__init___entry:
  movq $0, rax
  jmp std.collections.linked_list.__init___epilogue
std.collections.linked_list.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linked_list.__init__:

.globl std.collections.linked_list.DLL.is_empty
std.collections.linked_list.DLL.is_empty:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.linked_list.DLL.is_empty_entry:
  movq $0, rax
  jmp std.collections.linked_list.DLL.is_empty_epilogue
std.collections.linked_list.DLL.is_empty_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linked_list.DLL.is_empty:

.globl std.collections.linked_list.DLL.length
std.collections.linked_list.DLL.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.linked_list.DLL.length_entry:
  movq $0, rax
  jmp std.collections.linked_list.DLL.length_epilogue
std.collections.linked_list.DLL.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linked_list.DLL.length:

.globl std.collections.linked_list.DLL.pop_front
std.collections.linked_list.DLL.pop_front:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.linked_list.DLL.pop_front_entry:
  movq $0, rax
  jmp std.collections.linked_list.DLL.pop_front_epilogue
std.collections.linked_list.DLL.pop_front_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linked_list.DLL.pop_front:

.globl std.collections.linked_list.DLL.pop_back
std.collections.linked_list.DLL.pop_back:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.linked_list.DLL.pop_back_entry:
  movq $0, rax
  jmp std.collections.linked_list.DLL.pop_back_epilogue
std.collections.linked_list.DLL.pop_back_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linked_list.DLL.pop_back:

.globl std.collections.linked_list.DLL.push_front
std.collections.linked_list.DLL.push_front:
  push rbp
  mov rbp, rsp
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
std.collections.linked_list.DLL.push_front_entry:
  movq $0, rax
  jmp std.collections.linked_list.DLL.push_front_epilogue
std.collections.linked_list.DLL.push_front_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linked_list.DLL.push_front:

.globl std.collections.linkedlist.LinkedList.len
std.collections.linkedlist.LinkedList.len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.linkedlist.LinkedList.len_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.len_epilogue
std.collections.linkedlist.LinkedList.len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linkedlist.LinkedList.len:

.globl std.collections.set.set_from_array
std.collections.set.set_from_array:
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
std.collections.set.set_from_array_entry:
std.collections.set.set_from_array_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq $0, rcx
  call lm_list_new
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -80]
  movq [rbp + -64], rax
  movq [rbp + -80], rdx
  mov [rdx], rax
  jmp std.collections.set.set_from_array_block_7
std.collections.set.set_from_array_block_7:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r6, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.collections.set.set_from_array_block_10
  jmp std.collections.set.set_from_array_block_18
std.collections.set.set_from_array_block_10:
  jmp std.collections.set.set_from_array_block_10
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -72], rcx
  movq $r9, rdx
  call std.collections.set.Set.add
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  jmp std.collections.set.set_from_array_block_7
std.collections.set.set_from_array_block_18:
  movq $r10, rax
  jmp std.collections.set.set_from_array_epilogue
std.collections.set.set_from_array_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.set_from_array:

.globl std.collections.set.Set.max
std.collections.set.Set.max:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.set.Set.max_entry:
  movq $0, rax
  jmp std.collections.set.Set.max_epilogue
std.collections.set.Set.max_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.max:

.globl std.collections.set.Set.min
std.collections.set.Set.min:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.set.Set.min_entry:
  movq $0, rax
  jmp std.collections.set.Set.min_epilogue
std.collections.set.Set.min_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.min:

.globl __lambda_1
__lambda_1:
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
__lambda_1_entry:
__lambda_1_block_0:
  movq [rbp + -64], rax
  imulq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp __lambda_1_epilogue
__lambda_1_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end___lambda_1:

.globl std.collections.set.Set.product
std.collections.set.Set.product:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.set.Set.product_entry:
  movq $0, rax
  jmp std.collections.set.Set.product_epilogue
std.collections.set.Set.product_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.product:

.globl __lambda_0
__lambda_0:
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
__lambda_0_entry:
__lambda_0_block_0:
  movq [rbp + -64], rax
  addq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp __lambda_0_epilogue
__lambda_0_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end___lambda_0:

.globl std.collections.set.Set.for_each
std.collections.set.Set.for_each:
  push rbp
  mov rbp, rsp
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
std.collections.set.Set.for_each_entry:
  movq $0, rax
  jmp std.collections.set.Set.for_each_epilogue
std.collections.set.Set.for_each_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.for_each:

.globl std.collections.set.Set.fold
std.collections.set.Set.fold:
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
std.collections.set.Set.fold_entry:
  movq $0, rax
  jmp std.collections.set.Set.fold_epilogue
std.collections.set.Set.fold_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.fold:

.globl std.collections.set.Set.filter
std.collections.set.Set.filter:
  push rbp
  mov rbp, rsp
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
std.collections.set.Set.filter_entry:
  movq $0, rax
  jmp std.collections.set.Set.filter_epilogue
std.collections.set.Set.filter_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.filter:

.globl std.collections.set.Set.map
std.collections.set.Set.map:
  push rbp
  mov rbp, rsp
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
std.collections.set.Set.map_entry:
  movq $0, rax
  jmp std.collections.set.Set.map_epilogue
std.collections.set.Set.map_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.map:

.globl std.collections.set.Set.is_subset
std.collections.set.Set.is_subset:
  push rbp
  mov rbp, rsp
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
std.collections.set.Set.is_subset_entry:
  movq $0, rax
  jmp std.collections.set.Set.is_subset_epilogue
std.collections.set.Set.is_subset_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.is_subset:

.globl std.collections.set.Set.difference
std.collections.set.Set.difference:
  push rbp
  mov rbp, rsp
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
std.collections.set.Set.difference_entry:
  movq $0, rax
  jmp std.collections.set.Set.difference_epilogue
std.collections.set.Set.difference_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.difference:

.globl std.collections.set.Set.union
std.collections.set.Set.union:
  push rbp
  mov rbp, rsp
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
std.collections.set.Set.union_entry:
  movq $0, rax
  jmp std.collections.set.Set.union_epilogue
std.collections.set.Set.union_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.union:

.globl std.collections.index.Stack
std.collections.index.Stack:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.collections.index.Stack_entry:
std.collections.index.Stack_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.collections.stack.Stack.init
  movq $0, rax
  jmp std.collections.index.Stack_epilogue
std.collections.index.Stack_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.Stack:

.globl std.collections.set.Set.clear
std.collections.set.Set.clear:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.set.Set.clear_entry:
  movq $0, rax
  jmp std.collections.set.Set.clear_epilogue
std.collections.set.Set.clear_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.clear:

.globl std.collections.set.Set.is_empty
std.collections.set.Set.is_empty:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.set.Set.is_empty_entry:
  movq $0, rax
  jmp std.collections.set.Set.is_empty_epilogue
std.collections.set.Set.is_empty_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.is_empty:

.globl std.collections.set.Set.len
std.collections.set.Set.len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.set.Set.len_entry:
  movq $0, rax
  jmp std.collections.set.Set.len_epilogue
std.collections.set.Set.len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.len:

.globl std.collections.set.Set.size
std.collections.set.Set.size:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.set.Set.size_entry:
  movq $0, rax
  jmp std.collections.set.Set.size_epilogue
std.collections.set.Set.size_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.size:

.globl std.collections.set.Set.contains
std.collections.set.Set.contains:
  push rbp
  mov rbp, rsp
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
std.collections.set.Set.contains_entry:
  movq $0, rax
  jmp std.collections.set.Set.contains_epilogue
std.collections.set.Set.contains_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.contains:

.globl std.collections.set.Set.intersection
std.collections.set.Set.intersection:
  push rbp
  mov rbp, rsp
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
std.collections.set.Set.intersection_entry:
  movq $0, rax
  jmp std.collections.set.Set.intersection_epilogue
std.collections.set.Set.intersection_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.intersection:

.globl std.collections.set.Set.remove
std.collections.set.Set.remove:
  push rbp
  mov rbp, rsp
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
std.collections.set.Set.remove_entry:
  movq $0, rax
  jmp std.collections.set.Set.remove_epilogue
std.collections.set.Set.remove_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.remove:

.globl std.collections.set.Set.add
std.collections.set.Set.add:
  push rbp
  mov rbp, rsp
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
std.collections.set.Set.add_entry:
  movq $0, rax
  jmp std.collections.set.Set.add_epilogue
std.collections.set.Set.add_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.add:

.globl std.collections.btreeset.__init__
std.collections.btreeset.__init__:
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
std.collections.btreeset.__init___entry:
  movq $0, rax
  jmp std.collections.btreeset.__init___epilogue
std.collections.btreeset.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.btreeset.__init__:

.globl std.collections.btreeset.BTreeSetWrapper.init
std.collections.btreeset.BTreeSetWrapper.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.btreeset.BTreeSetWrapper.init_entry:
  movq $0, rax
  jmp std.collections.btreeset.BTreeSetWrapper.init_epilogue
std.collections.btreeset.BTreeSetWrapper.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.btreeset.BTreeSetWrapper.init:

.globl std.collections.btreeset.BTreeSetWrapper.add
std.collections.btreeset.BTreeSetWrapper.add:
  push rbp
  mov rbp, rsp
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
std.collections.btreeset.BTreeSetWrapper.add_entry:
  movq $0, rax
  jmp std.collections.btreeset.BTreeSetWrapper.add_epilogue
std.collections.btreeset.BTreeSetWrapper.add_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.btreeset.BTreeSetWrapper.add:

.globl std.collections.hashset.__init__
std.collections.hashset.__init__:
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
std.collections.hashset.__init___entry:
  movq $0, rax
  jmp std.collections.hashset.__init___epilogue
std.collections.hashset.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashset.__init__:

.globl std.collections.hashset.HashSetWrapper.length
std.collections.hashset.HashSetWrapper.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.hashset.HashSetWrapper.length_entry:
  movq $0, rax
  jmp std.collections.hashset.HashSetWrapper.length_epilogue
std.collections.hashset.HashSetWrapper.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashset.HashSetWrapper.length:

.globl std.collections.hashset.HashSetWrapper.remove
std.collections.hashset.HashSetWrapper.remove:
  push rbp
  mov rbp, rsp
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
std.collections.hashset.HashSetWrapper.remove_entry:
  movq $0, rax
  jmp std.collections.hashset.HashSetWrapper.remove_epilogue
std.collections.hashset.HashSetWrapper.remove_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashset.HashSetWrapper.remove:

.globl std.collections.hashset.HashSetWrapper.contains
std.collections.hashset.HashSetWrapper.contains:
  push rbp
  mov rbp, rsp
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
std.collections.hashset.HashSetWrapper.contains_entry:
  movq $0, rax
  jmp std.collections.hashset.HashSetWrapper.contains_epilogue
std.collections.hashset.HashSetWrapper.contains_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashset.HashSetWrapper.contains:

.globl std.collections.hashset.HashSetWrapper.add
std.collections.hashset.HashSetWrapper.add:
  push rbp
  mov rbp, rsp
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
std.collections.hashset.HashSetWrapper.add_entry:
  movq $0, rax
  jmp std.collections.hashset.HashSetWrapper.add_epilogue
std.collections.hashset.HashSetWrapper.add_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashset.HashSetWrapper.add:

.globl std.collections.priority_queue.__init__
std.collections.priority_queue.__init__:
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
std.collections.priority_queue.__init___entry:
  movq $0, rax
  jmp std.collections.priority_queue.__init___epilogue
std.collections.priority_queue.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.priority_queue.__init__:

.globl std.collections.priority_queue.PriorityQueueWrapper.pop
std.collections.priority_queue.PriorityQueueWrapper.pop:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.priority_queue.PriorityQueueWrapper.pop_entry:
  movq $0, rax
  jmp std.collections.priority_queue.PriorityQueueWrapper.pop_epilogue
std.collections.priority_queue.PriorityQueueWrapper.pop_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.priority_queue.PriorityQueueWrapper.pop:

.globl std.collections.stack.__init__
std.collections.stack.__init__:
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
std.collections.stack.__init___entry:
  movq $0, rax
  jmp std.collections.stack.__init___epilogue
std.collections.stack.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.stack.__init__:

.globl std.collections.stack.Stack.init
std.collections.stack.Stack.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.stack.Stack.init_entry:
  movq $0, rax
  jmp std.collections.stack.Stack.init_epilogue
std.collections.stack.Stack.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.stack.Stack.init:

.globl std.collections.stack.Stack.clear
std.collections.stack.Stack.clear:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.stack.Stack.clear_entry:
  movq $0, rax
  jmp std.collections.stack.Stack.clear_epilogue
std.collections.stack.Stack.clear_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.stack.Stack.clear:

.globl std.collections.index.HashSet
std.collections.index.HashSet:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.collections.index.HashSet_entry:
std.collections.index.HashSet_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.collections.hashset.HashSetWrapper.init
  movq $0, rax
  jmp std.collections.index.HashSet_epilogue
std.collections.index.HashSet_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.HashSet:

.globl std.collections.linked_list.DLL.init
std.collections.linked_list.DLL.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.linked_list.DLL.init_entry:
  movq $0, rax
  jmp std.collections.linked_list.DLL.init_epilogue
std.collections.linked_list.DLL.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linked_list.DLL.init:

.globl std.collections.stack.Stack.is_empty
std.collections.stack.Stack.is_empty:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.stack.Stack.is_empty_entry:
  movq $0, rax
  jmp std.collections.stack.Stack.is_empty_epilogue
std.collections.stack.Stack.is_empty_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.stack.Stack.is_empty:

.globl std.collections.hashset.HashSetWrapper.init
std.collections.hashset.HashSetWrapper.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.hashset.HashSetWrapper.init_entry:
  movq $0, rax
  jmp std.collections.hashset.HashSetWrapper.init_epilogue
std.collections.hashset.HashSetWrapper.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashset.HashSetWrapper.init:

.globl std.collections.stack.Stack.peek
std.collections.stack.Stack.peek:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.stack.Stack.peek_entry:
  movq $0, rax
  jmp std.collections.stack.Stack.peek_epilogue
std.collections.stack.Stack.peek_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.stack.Stack.peek:

.globl std.collections.stack.Stack.pop
std.collections.stack.Stack.pop:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.stack.Stack.pop_entry:
  movq $0, rax
  jmp std.collections.stack.Stack.pop_epilogue
std.collections.stack.Stack.pop_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.stack.Stack.pop:

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

.globl std.collections.tree.BTree.len
std.collections.tree.BTree.len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.tree.BTree.len_entry:
  movq $0, rax
  jmp std.collections.tree.BTree.len_epilogue
std.collections.tree.BTree.len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.BTree.len:

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

.globl std.collections.linkedlist.LinkedList.is_empty
std.collections.linkedlist.LinkedList.is_empty:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.linkedlist.LinkedList.is_empty_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.is_empty_epilogue
std.collections.linkedlist.LinkedList.is_empty_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linkedlist.LinkedList.is_empty:

.globl std.collections.bloom_filter.BloomFilter.add
std.collections.bloom_filter.BloomFilter.add:
  push rbp
  mov rbp, rsp
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
std.collections.bloom_filter.BloomFilter.add_entry:
  movq $0, rax
  jmp std.collections.bloom_filter.BloomFilter.add_epilogue
std.collections.bloom_filter.BloomFilter.add_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bloom_filter.BloomFilter.add:

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

.globl std.core.some_str
std.core.some_str:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.some_str_entry:
std.core.some_str_block_0:
  movq $0, rax
  jmp std.core.some_str_epilogue
std.core.some_str_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.some_str:

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

.globl std.core.ResultInt.unwrap_or
std.core.ResultInt.unwrap_or:
  push rbp
  mov rbp, rsp
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
std.core.ResultInt.unwrap_or_entry:
  movq $0, rax
  jmp std.core.ResultInt.unwrap_or_epilogue
std.core.ResultInt.unwrap_or_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ResultInt.unwrap_or:

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

.globl std.collections.bitset.BitSetWrapper.set
std.collections.bitset.BitSetWrapper.set:
  push rbp
  mov rbp, rsp
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
std.collections.bitset.BitSetWrapper.set_entry:
  movq $0, rax
  jmp std.collections.bitset.BitSetWrapper.set_epilogue
std.collections.bitset.BitSetWrapper.set_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bitset.BitSetWrapper.set:

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

.globl std.collections.set.Set.sum
std.collections.set.Set.sum:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.set.Set.sum_entry:
  movq $0, rax
  jmp std.collections.set.Set.sum_epilogue
std.collections.set.Set.sum_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.sum:

.globl std.collections.tree.TreeMap.init
std.collections.tree.TreeMap.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.tree.TreeMap.init_entry:
  movq $0, rax
  jmp std.collections.tree.TreeMap.init_epilogue
std.collections.tree.TreeMap.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeMap.init:

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

.globl std.collections.index.Queue
std.collections.index.Queue:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.collections.index.Queue_entry:
std.collections.index.Queue_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.collections.queue.Queue.init
  movq $0, rax
  jmp std.collections.index.Queue_epilogue
std.collections.index.Queue_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.Queue:

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

.globl std.collections.deque.DoubleEndedQueue.init
std.collections.deque.DoubleEndedQueue.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.deque.DoubleEndedQueue.init_entry:
  movq $0, rax
  jmp std.collections.deque.DoubleEndedQueue.init_epilogue
std.collections.deque.DoubleEndedQueue.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.deque.DoubleEndedQueue.init:

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

.globl std.collections.bitset.BitSetWrapper.count
std.collections.bitset.BitSetWrapper.count:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.bitset.BitSetWrapper.count_entry:
  movq $0, rax
  jmp std.collections.bitset.BitSetWrapper.count_epilogue
std.collections.bitset.BitSetWrapper.count_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bitset.BitSetWrapper.count:

.globl std.core.ResultInt.unwrap
std.core.ResultInt.unwrap:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.ResultInt.unwrap_entry:
  movq $0, rax
  jmp std.core.ResultInt.unwrap_epilogue
std.core.ResultInt.unwrap_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ResultInt.unwrap:

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

.globl std.collections.btreemap.__init__
std.collections.btreemap.__init__:
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
std.collections.btreemap.__init___entry:
  movq $0, rax
  jmp std.collections.btreemap.__init___epilogue
std.collections.btreemap.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.btreemap.__init__:

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

.globl std.collections.bitset.BitSetWrapper.unset
std.collections.bitset.BitSetWrapper.unset:
  push rbp
  mov rbp, rsp
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
std.collections.bitset.BitSetWrapper.unset_entry:
  movq $0, rax
  jmp std.collections.bitset.BitSetWrapper.unset_epilogue
std.collections.bitset.BitSetWrapper.unset_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bitset.BitSetWrapper.unset:

.globl std.collections.index.__init__
std.collections.index.__init__:
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
std.collections.index.__init___entry:
  movq $0, rax
  jmp std.collections.index.__init___epilogue
std.collections.index.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.__init__:

.globl std.collections.index.BTreeMap
std.collections.index.BTreeMap:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.collections.index.BTreeMap_entry:
std.collections.index.BTreeMap_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.collections.btreemap.BTreeMapWrapper.init
  movq $0, rax
  jmp std.collections.index.BTreeMap_epilogue
std.collections.index.BTreeMap_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.BTreeMap:

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

.globl std.collections.priority_queue.PriorityQueueWrapper.peek
std.collections.priority_queue.PriorityQueueWrapper.peek:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.priority_queue.PriorityQueueWrapper.peek_entry:
  movq $0, rax
  jmp std.collections.priority_queue.PriorityQueueWrapper.peek_epilogue
std.collections.priority_queue.PriorityQueueWrapper.peek_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.priority_queue.PriorityQueueWrapper.peek:

.globl std.collections.tree.TreeSet.contains
std.collections.tree.TreeSet.contains:
  push rbp
  mov rbp, rsp
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
std.collections.tree.TreeSet.contains_entry:
  movq $0, rax
  jmp std.collections.tree.TreeSet.contains_epilogue
std.collections.tree.TreeSet.contains_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeSet.contains:

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

.globl std.collections.bloom_filter.BloomFilter.contains
std.collections.bloom_filter.BloomFilter.contains:
  push rbp
  mov rbp, rsp
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
std.collections.bloom_filter.BloomFilter.contains_entry:
  movq $0, rax
  jmp std.collections.bloom_filter.BloomFilter.contains_epilogue
std.collections.bloom_filter.BloomFilter.contains_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bloom_filter.BloomFilter.contains:

.globl std.collections.map.HashMapWrapper.remove
std.collections.map.HashMapWrapper.remove:
  push rbp
  mov rbp, rsp
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
std.collections.map.HashMapWrapper.remove_entry:
  movq $0, rax
  jmp std.collections.map.HashMapWrapper.remove_epilogue
std.collections.map.HashMapWrapper.remove_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.map.HashMapWrapper.remove:

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

.globl std.collections.linkedlist.__init__
std.collections.linkedlist.__init__:
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
std.collections.linkedlist.__init___entry:
  movq $0, rax
  jmp std.collections.linkedlist.__init___epilogue
std.collections.linkedlist.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linkedlist.__init__:

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

.globl std.collections.set.Set.is_superset
std.collections.set.Set.is_superset:
  push rbp
  mov rbp, rsp
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
std.collections.set.Set.is_superset_entry:
  movq $0, rax
  jmp std.collections.set.Set.is_superset_epilogue
std.collections.set.Set.is_superset_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.is_superset:

.globl std.collections.hashmap.HashMap.filter
std.collections.hashmap.HashMap.filter:
  push rbp
  mov rbp, rsp
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
std.collections.hashmap.HashMap.filter_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.filter_epilogue
std.collections.hashmap.HashMap.filter_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.filter:

.globl std.collections.btreeset.BTreeSetWrapper.contains
std.collections.btreeset.BTreeSetWrapper.contains:
  push rbp
  mov rbp, rsp
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
std.collections.btreeset.BTreeSetWrapper.contains_entry:
  movq $0, rax
  jmp std.collections.btreeset.BTreeSetWrapper.contains_epilogue
std.collections.btreeset.BTreeSetWrapper.contains_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.btreeset.BTreeSetWrapper.contains:

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

.globl std.core.ResultStr.is_ok
std.core.ResultStr.is_ok:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.ResultStr.is_ok_entry:
  movq $0, rax
  jmp std.core.ResultStr.is_ok_epilogue
std.core.ResultStr.is_ok_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ResultStr.is_ok:

.globl std.collections.linkedlist.Iterator.next
std.collections.linkedlist.Iterator.next:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.linkedlist.Iterator.next_entry:
  movq $0, rax
  jmp std.collections.linkedlist.Iterator.next_epilogue
std.collections.linkedlist.Iterator.next_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linkedlist.Iterator.next:

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

.globl std.collections.hashmap.HashMap.contains_key
std.collections.hashmap.HashMap.contains_key:
  push rbp
  mov rbp, rsp
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
std.collections.hashmap.HashMap.contains_key_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.contains_key_epilogue
std.collections.hashmap.HashMap.contains_key_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.contains_key:

.globl std.collections.list.List.set
std.collections.list.List.set:
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
std.collections.list.List.set_entry:
  movq $0, rax
  jmp std.collections.list.List.set_epilogue
std.collections.list.List.set_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.list.List.set:

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

.globl std.collections.index.List
std.collections.index.List:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.collections.index.List_entry:
std.collections.index.List_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.collections.list.List.init
  movq $0, rax
  jmp std.collections.index.List_epilogue
std.collections.index.List_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.List:

.globl std.collections.list.List.get
std.collections.list.List.get:
  push rbp
  mov rbp, rsp
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
std.collections.list.List.get_entry:
  movq $0, rax
  jmp std.collections.list.List.get_epilogue
std.collections.list.List.get_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.list.List.get:

.globl std.core.ResultStr.is_err
std.core.ResultStr.is_err:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.ResultStr.is_err_entry:
  movq $0, rax
  jmp std.core.ResultStr.is_err_epilogue
std.core.ResultStr.is_err_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ResultStr.is_err:

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

.globl std.collections.set.Set.to_string
std.collections.set.Set.to_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.set.Set.to_string_entry:
  movq $0, rax
  jmp std.collections.set.Set.to_string_epilogue
std.collections.set.Set.to_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.to_string:

.globl std.collections.btreeset.BTreeSetWrapper.length
std.collections.btreeset.BTreeSetWrapper.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.btreeset.BTreeSetWrapper.length_entry:
  movq $0, rax
  jmp std.collections.btreeset.BTreeSetWrapper.length_epilogue
std.collections.btreeset.BTreeSetWrapper.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.btreeset.BTreeSetWrapper.length:

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

.globl std.collections.map.HashMapWrapper.is_empty
std.collections.map.HashMapWrapper.is_empty:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.map.HashMapWrapper.is_empty_entry:
  movq $0, rax
  jmp std.collections.map.HashMapWrapper.is_empty_epilogue
std.collections.map.HashMapWrapper.is_empty_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.map.HashMapWrapper.is_empty:

.globl std.collections.priority_queue.PriorityQueueWrapper.push
std.collections.priority_queue.PriorityQueueWrapper.push:
  push rbp
  mov rbp, rsp
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
std.collections.priority_queue.PriorityQueueWrapper.push_entry:
  movq $0, rax
  jmp std.collections.priority_queue.PriorityQueueWrapper.push_epilogue
std.collections.priority_queue.PriorityQueueWrapper.push_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.priority_queue.PriorityQueueWrapper.push:

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

.globl std.collections.list.List.len
std.collections.list.List.len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.list.List.len_entry:
  movq $0, rax
  jmp std.collections.list.List.len_epilogue
std.collections.list.List.len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.list.List.len:

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

.globl std.collections.set.Set.to_array
std.collections.set.Set.to_array:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.set.Set.to_array_entry:
  movq $0, rax
  jmp std.collections.set.Set.to_array_epilogue
std.collections.set.Set.to_array_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.to_array:

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

.globl std.collections.set.Set.symmetric_difference
std.collections.set.Set.symmetric_difference:
  push rbp
  mov rbp, rsp
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
std.collections.set.Set.symmetric_difference_entry:
  movq $0, rax
  jmp std.collections.set.Set.symmetric_difference_epilogue
std.collections.set.Set.symmetric_difference_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.symmetric_difference:

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

.globl std.collections.index.BTreeSet
std.collections.index.BTreeSet:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.collections.index.BTreeSet_entry:
std.collections.index.BTreeSet_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.collections.btreeset.BTreeSetWrapper.init
  movq $0, rax
  jmp std.collections.index.BTreeSet_epilogue
std.collections.index.BTreeSet_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.BTreeSet:

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

.globl std.collections.hashmap.HashMap.find_key_index
std.collections.hashmap.HashMap.find_key_index:
  push rbp
  mov rbp, rsp
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
std.collections.hashmap.HashMap.find_key_index_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.find_key_index_epilogue
std.collections.hashmap.HashMap.find_key_index_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.find_key_index:

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

.globl std.collections.tree.TreeSet.length
std.collections.tree.TreeSet.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.tree.TreeSet.length_entry:
  movq $0, rax
  jmp std.collections.tree.TreeSet.length_epilogue
std.collections.tree.TreeSet.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeSet.length:

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

.globl std.collections.map.HashMapWrapper.put
std.collections.map.HashMapWrapper.put:
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
std.collections.map.HashMapWrapper.put_entry:
  movq $0, rax
  jmp std.collections.map.HashMapWrapper.put_epilogue
std.collections.map.HashMapWrapper.put_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.map.HashMapWrapper.put:

.globl std.collections.list.List.init
std.collections.list.List.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.list.List.init_entry:
  movq $0, rax
  jmp std.collections.list.List.init_epilogue
std.collections.list.List.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.list.List.init:

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

.globl std.collections.list.List.clear
std.collections.list.List.clear:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.list.List.clear_entry:
  movq $0, rax
  jmp std.collections.list.List.clear_epilogue
std.collections.list.List.clear_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.list.List.clear:

.globl std.collections.priority_queue.PriorityQueueWrapper.length
std.collections.priority_queue.PriorityQueueWrapper.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.priority_queue.PriorityQueueWrapper.length_entry:
  movq $0, rax
  jmp std.collections.priority_queue.PriorityQueueWrapper.length_epilogue
std.collections.priority_queue.PriorityQueueWrapper.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.priority_queue.PriorityQueueWrapper.length:

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

.globl std.collections.bloom_filter.BloomFilter.init
std.collections.bloom_filter.BloomFilter.init:
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
std.collections.bloom_filter.BloomFilter.init_entry:
  movq $0, rax
  jmp std.collections.bloom_filter.BloomFilter.init_epilogue
std.collections.bloom_filter.BloomFilter.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bloom_filter.BloomFilter.init:

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

.globl std.collections.set.Set.find_index
std.collections.set.Set.find_index:
  push rbp
  mov rbp, rsp
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
std.collections.set.Set.find_index_entry:
  movq $0, rax
  jmp std.collections.set.Set.find_index_epilogue
std.collections.set.Set.find_index_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.find_index:

.globl std.collections.bitset.__init__
std.collections.bitset.__init__:
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
std.collections.bitset.__init___entry:
  movq $0, rax
  jmp std.collections.bitset.__init___epilogue
std.collections.bitset.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bitset.__init__:

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

.globl std.collections.list.List.append
std.collections.list.List.append:
  push rbp
  mov rbp, rsp
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
std.collections.list.List.append_entry:
  movq $0, rax
  jmp std.collections.list.List.append_epilogue
std.collections.list.List.append_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.list.List.append:

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

.globl std.collections.set.__init__
std.collections.set.__init__:
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
std.collections.set.__init___entry:
  movq $0, rax
  jmp std.collections.set.__init___epilogue
std.collections.set.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.__init__:

.globl std.collections.tree.TreeMap.get
std.collections.tree.TreeMap.get:
  push rbp
  mov rbp, rsp
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
std.collections.tree.TreeMap.get_entry:
  movq $0, rax
  jmp std.collections.tree.TreeMap.get_epilogue
std.collections.tree.TreeMap.get_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeMap.get:

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

.globl std.collections.map.HashMapWrapper.init
std.collections.map.HashMapWrapper.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.map.HashMapWrapper.init_entry:
  movq $0, rax
  jmp std.collections.map.HashMapWrapper.init_epilogue
std.collections.map.HashMapWrapper.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.map.HashMapWrapper.init:

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

.globl std.collections.linkedlist.Iterator.init
std.collections.linkedlist.Iterator.init:
  push rbp
  mov rbp, rsp
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
std.collections.linkedlist.Iterator.init_entry:
  movq $0, rax
  jmp std.collections.linkedlist.Iterator.init_epilogue
std.collections.linkedlist.Iterator.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linkedlist.Iterator.init:

.globl std.collections.deque.DoubleEndedQueue.peek_front
std.collections.deque.DoubleEndedQueue.peek_front:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.deque.DoubleEndedQueue.peek_front_entry:
  movq $0, rax
  jmp std.collections.deque.DoubleEndedQueue.peek_front_epilogue
std.collections.deque.DoubleEndedQueue.peek_front_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.deque.DoubleEndedQueue.peek_front:

.globl std.collections.map.HashMapWrapper.get
std.collections.map.HashMapWrapper.get:
  push rbp
  mov rbp, rsp
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
std.collections.map.HashMapWrapper.get_entry:
  movq $0, rax
  jmp std.collections.map.HashMapWrapper.get_epilogue
std.collections.map.HashMapWrapper.get_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.map.HashMapWrapper.get:

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

.globl std.core.err_str
std.core.err_str:
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
std.core.err_str_entry:
std.core.err_str_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -96]
  movq [rbp + -72], rax
  movq [rbp + -96], rdx
  mov [rdx], rax
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -104], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -112]
  movq [rbp + -64], rax
  movq [rbp + -112], rdx
  mov [rdx], rax
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -128]
  movq [rbp + -72], rax
  movq [rbp + -128], rdx
  mov [rdx], rax
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -136]
  movq [rbp + -80], rax
  movq [rbp + -136], rdx
  mov [rdx], rax
  movq [rbp + -104], rax
  jmp std.core.err_str_epilogue
std.core.err_str_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.err_str:

.globl std.collections.deque.DoubleEndedQueue.pop_back
std.collections.deque.DoubleEndedQueue.pop_back:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.deque.DoubleEndedQueue.pop_back_entry:
  movq $0, rax
  jmp std.collections.deque.DoubleEndedQueue.pop_back_epilogue
std.collections.deque.DoubleEndedQueue.pop_back_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.deque.DoubleEndedQueue.pop_back:

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

.globl std.collections.btreemap.BTreeMapWrapper.length
std.collections.btreemap.BTreeMapWrapper.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.btreemap.BTreeMapWrapper.length_entry:
  movq $0, rax
  jmp std.collections.btreemap.BTreeMapWrapper.length_epilogue
std.collections.btreemap.BTreeMapWrapper.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.btreemap.BTreeMapWrapper.length:

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

.globl std.collections.hashmap.HashMap.from_pairs
std.collections.hashmap.HashMap.from_pairs:
  push rbp
  mov rbp, rsp
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
std.collections.hashmap.HashMap.from_pairs_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.from_pairs_epilogue
std.collections.hashmap.HashMap.from_pairs_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.from_pairs:

.globl std.core.OptionInt.unwrap
std.core.OptionInt.unwrap:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.OptionInt.unwrap_entry:
  movq $0, rax
  jmp std.core.OptionInt.unwrap_epilogue
std.core.OptionInt.unwrap_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.OptionInt.unwrap:

.globl std.collections.hashmap.HashMap.contains_value
std.collections.hashmap.HashMap.contains_value:
  push rbp
  mov rbp, rsp
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
std.collections.hashmap.HashMap.contains_value_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.contains_value_epilogue
std.collections.hashmap.HashMap.contains_value_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.contains_value:

.globl std.collections.bitset.BitSetWrapper.init
std.collections.bitset.BitSetWrapper.init:
  push rbp
  mov rbp, rsp
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
std.collections.bitset.BitSetWrapper.init_entry:
  movq $0, rax
  jmp std.collections.bitset.BitSetWrapper.init_epilogue
std.collections.bitset.BitSetWrapper.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bitset.BitSetWrapper.init:

.globl std.collections.hashmap.HashMap.get
std.collections.hashmap.HashMap.get:
  push rbp
  mov rbp, rsp
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
std.collections.hashmap.HashMap.get_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.get_epilogue
std.collections.hashmap.HashMap.get_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.get:

.globl std.collections.hashmap.HashMap.remove
std.collections.hashmap.HashMap.remove:
  push rbp
  mov rbp, rsp
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
std.collections.hashmap.HashMap.remove_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.remove_epilogue
std.collections.hashmap.HashMap.remove_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.remove:

.globl std.collections.deque.__init__
std.collections.deque.__init__:
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
std.collections.deque.__init___entry:
  movq $0, rax
  jmp std.collections.deque.__init___epilogue
std.collections.deque.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.deque.__init__:

.globl std.core.ResultStr.map
std.core.ResultStr.map:
  push rbp
  mov rbp, rsp
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
std.core.ResultStr.map_entry:
  movq $0, rax
  jmp std.core.ResultStr.map_epilogue
std.core.ResultStr.map_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ResultStr.map:

.globl std.collections.hashmap.HashMap.is_empty
std.collections.hashmap.HashMap.is_empty:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.hashmap.HashMap.is_empty_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.is_empty_epilogue
std.collections.hashmap.HashMap.is_empty_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.is_empty:

.globl std.collections.hashmap.HashMap.clear
std.collections.hashmap.HashMap.clear:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.hashmap.HashMap.clear_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.clear_epilogue
std.collections.hashmap.HashMap.clear_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.clear:

.globl std.collections.hashmap.HashMap.keys
std.collections.hashmap.HashMap.keys:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.hashmap.HashMap.keys_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.keys_epilogue
std.collections.hashmap.HashMap.keys_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.keys:

.globl std.collections.hashmap.HashMap.values
std.collections.hashmap.HashMap.values:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.hashmap.HashMap.values_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.values_epilogue
std.collections.hashmap.HashMap.values_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.values:

.globl std.collections.hashmap.HashMap.entries
std.collections.hashmap.HashMap.entries:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.hashmap.HashMap.entries_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.entries_epilogue
std.collections.hashmap.HashMap.entries_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.entries:

.globl std.collections.hashmap.HashMap.put
std.collections.hashmap.HashMap.put:
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
std.collections.hashmap.HashMap.put_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.put_epilogue
std.collections.hashmap.HashMap.put_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.put:

.globl std.collections.hashmap.HashMap.map_values
std.collections.hashmap.HashMap.map_values:
  push rbp
  mov rbp, rsp
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
std.collections.hashmap.HashMap.map_values_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.map_values_epilogue
std.collections.hashmap.HashMap.map_values_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.map_values:

.globl std.collections.hashmap.HashMap.to_string
std.collections.hashmap.HashMap.to_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.hashmap.HashMap.to_string_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.to_string_epilogue
std.collections.hashmap.HashMap.to_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.to_string:

.globl std.core.ResultInt.map_err
std.core.ResultInt.map_err:
  push rbp
  mov rbp, rsp
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
std.core.ResultInt.map_err_entry:
  movq $0, rax
  jmp std.core.ResultInt.map_err_epilogue
std.core.ResultInt.map_err_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ResultInt.map_err:

.globl std.collections.hashmap.__init__
std.collections.hashmap.__init__:
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
std.collections.hashmap.__init___entry:
  movq $0, rax
  jmp std.collections.hashmap.__init___epilogue
std.collections.hashmap.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.__init__:

.globl std.collections.stack.Stack.length
std.collections.stack.Stack.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.stack.Stack.length_entry:
  movq $0, rax
  jmp std.collections.stack.Stack.length_epilogue
std.collections.stack.Stack.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.stack.Stack.length:

.globl std.collections.tree.AVLNode.init
std.collections.tree.AVLNode.init:
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
std.collections.tree.AVLNode.init_entry:
  movq $0, rax
  jmp std.collections.tree.AVLNode.init_epilogue
std.collections.tree.AVLNode.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.AVLNode.init:

.globl std.collections.stack.Stack.len
std.collections.stack.Stack.len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.stack.Stack.len_entry:
  movq $0, rax
  jmp std.collections.stack.Stack.len_epilogue
std.collections.stack.Stack.len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.stack.Stack.len:

.globl std.collections.tree.TreeMap.put
std.collections.tree.TreeMap.put:
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
std.collections.tree.TreeMap.put_entry:
  movq $0, rax
  jmp std.collections.tree.TreeMap.put_epilogue
std.collections.tree.TreeMap.put_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeMap.put:

.globl std.collections.tree.TreeMap.len
std.collections.tree.TreeMap.len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.tree.TreeMap.len_entry:
  movq $0, rax
  jmp std.collections.tree.TreeMap.len_epilogue
std.collections.tree.TreeMap.len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeMap.len:

.globl std.collections.tree.TreeMap.length
std.collections.tree.TreeMap.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.tree.TreeMap.length_entry:
  movq $0, rax
  jmp std.collections.tree.TreeMap.length_epilogue
std.collections.tree.TreeMap.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeMap.length:

.globl std.collections.linkedlist.LinkedList.length
std.collections.linkedlist.LinkedList.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.linkedlist.LinkedList.length_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.length_epilogue
std.collections.linkedlist.LinkedList.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linkedlist.LinkedList.length:

.globl std.collections.tree.TreeMap._get_height
std.collections.tree.TreeMap._get_height:
  push rbp
  mov rbp, rsp
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
std.collections.tree.TreeMap._get_height_entry:
  movq $0, rax
  jmp std.collections.tree.TreeMap._get_height_epilogue
std.collections.tree.TreeMap._get_height_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeMap._get_height:

.globl std.collections.tree.TreeMap._get_balance
std.collections.tree.TreeMap._get_balance:
  push rbp
  mov rbp, rsp
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
std.collections.tree.TreeMap._get_balance_entry:
  movq $0, rax
  jmp std.collections.tree.TreeMap._get_balance_epilogue
std.collections.tree.TreeMap._get_balance_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeMap._get_balance:

.globl std.collections.tree.TreeMap._update_height
std.collections.tree.TreeMap._update_height:
  push rbp
  mov rbp, rsp
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
std.collections.tree.TreeMap._update_height_entry:
  movq $0, rax
  jmp std.collections.tree.TreeMap._update_height_epilogue
std.collections.tree.TreeMap._update_height_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeMap._update_height:

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

.globl std.collections.tree.TreeMap._rotate_right
std.collections.tree.TreeMap._rotate_right:
  push rbp
  mov rbp, rsp
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
std.collections.tree.TreeMap._rotate_right_entry:
  movq $0, rax
  jmp std.collections.tree.TreeMap._rotate_right_epilogue
std.collections.tree.TreeMap._rotate_right_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeMap._rotate_right:

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

.globl std.collections.tree.TreeMap._rotate_left
std.collections.tree.TreeMap._rotate_left:
  push rbp
  mov rbp, rsp
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
std.collections.tree.TreeMap._rotate_left_entry:
  movq $0, rax
  jmp std.collections.tree.TreeMap._rotate_left_epilogue
std.collections.tree.TreeMap._rotate_left_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeMap._rotate_left:

.globl std.core.ok_bool
std.core.ok_bool:
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
std.core.ok_bool_entry:
std.core.ok_bool_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -104]
  movq [rbp + -72], rax
  movq [rbp + -104], rdx
  mov [rdx], rax
  movq [rbp + -64], rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.core.ok_bool_block_9
  jmp std.core.ok_bool_block_16
std.core.ok_bool_block_9:
  jmp std.core.ok_bool_block_9
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -120], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -120], rax
  addq $0, rax
  movq rax, [rbp + -128]
  movq [rbp + -64], rax
  movq [rbp + -128], rdx
  mov [rdx], rax
  movq [rbp + -120], rax
  addq $0, rax
  movq rax, [rbp + -136]
  movq [rbp + -72], rax
  movq [rbp + -136], rdx
  mov [rdx], rax
  movq [rbp + -120], rax
  addq $0, rax
  movq rax, [rbp + -144]
  movq [rbp + -80], rax
  movq [rbp + -144], rdx
  mov [rdx], rax
  movq [rbp + -120], rax
  jmp std.core.ok_bool_epilogue
std.core.ok_bool_block_16:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -152], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -152], rax
  addq $0, rax
  movq rax, [rbp + -160]
  movq [rbp + -64], rax
  movq [rbp + -160], rdx
  mov [rdx], rax
  movq [rbp + -152], rax
  addq $0, rax
  movq rax, [rbp + -168]
  movq [rbp + -72], rax
  movq [rbp + -168], rdx
  mov [rdx], rax
  movq [rbp + -152], rax
  addq $0, rax
  movq rax, [rbp + -176]
  movq [rbp + -80], rax
  movq [rbp + -176], rdx
  mov [rdx], rax
  movq [rbp + -152], rax
  jmp std.core.ok_bool_epilogue
std.core.ok_bool_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ok_bool:

.globl std.collections.tree.TreeMap._insert
std.collections.tree.TreeMap._insert:
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
std.collections.tree.TreeMap._insert_entry:
  movq $0, rax
  jmp std.collections.tree.TreeMap._insert_epilogue
std.collections.tree.TreeMap._insert_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeMap._insert:

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

.globl std.core.ok_int
std.core.ok_int:
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
std.core.ok_int_entry:
std.core.ok_int_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -104]
  movq [rbp + -72], rax
  movq [rbp + -104], rdx
  mov [rdx], rax
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -112], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -112], rax
  addq $0, rax
  movq rax, [rbp + -120]
  movq [rbp + -64], rax
  movq [rbp + -120], rdx
  mov [rdx], rax
  movq [rbp + -112], rax
  addq $0, rax
  movq rax, [rbp + -128]
  movq [rbp + -72], rax
  movq [rbp + -128], rdx
  mov [rdx], rax
  movq [rbp + -112], rax
  addq $0, rax
  movq rax, [rbp + -136]
  movq [rbp + -80], rax
  movq [rbp + -136], rdx
  mov [rdx], rax
  movq [rbp + -112], rax
  jmp std.core.ok_int_epilogue
std.core.ok_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ok_int:

.globl std.collections.tree.TreeSet.add
std.collections.tree.TreeSet.add:
  push rbp
  mov rbp, rsp
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
std.collections.tree.TreeSet.add_entry:
  movq $0, rax
  jmp std.collections.tree.TreeSet.add_epilogue
std.collections.tree.TreeSet.add_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeSet.add:

.globl std.collections.list.__init__
std.collections.list.__init__:
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
std.collections.list.__init___entry:
  movq $0, rax
  jmp std.collections.list.__init___epilogue
std.collections.list.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.list.__init__:

.globl std.collections.tree.TreeSet.len
std.collections.tree.TreeSet.len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.tree.TreeSet.len_entry:
  movq $0, rax
  jmp std.collections.tree.TreeSet.len_epilogue
std.collections.tree.TreeSet.len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeSet.len:

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

.globl std.collections.tree.TreeSet.init
std.collections.tree.TreeSet.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.tree.TreeSet.init_entry:
  movq $0, rax
  jmp std.collections.tree.TreeSet.init_epilogue
std.collections.tree.TreeSet.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.TreeSet.init:

.globl std.collections.map.HashMapWrapper.clear
std.collections.map.HashMapWrapper.clear:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.map.HashMapWrapper.clear_entry:
  movq $0, rax
  jmp std.collections.map.HashMapWrapper.clear_epilogue
std.collections.map.HashMapWrapper.clear_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.map.HashMapWrapper.clear:

.globl std.collections.tree.BTree.put
std.collections.tree.BTree.put:
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
std.collections.tree.BTree.put_entry:
  movq $0, rax
  jmp std.collections.tree.BTree.put_epilogue
std.collections.tree.BTree.put_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.BTree.put:

.globl std.collections.tree.BTree.get
std.collections.tree.BTree.get:
  push rbp
  mov rbp, rsp
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
std.collections.tree.BTree.get_entry:
  movq $0, rax
  jmp std.collections.tree.BTree.get_epilogue
std.collections.tree.BTree.get_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.BTree.get:

.globl std.collections.priority_queue.PriorityQueueWrapper.init
std.collections.priority_queue.PriorityQueueWrapper.init:
  push rbp
  mov rbp, rsp
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
std.collections.priority_queue.PriorityQueueWrapper.init_entry:
  movq $0, rax
  jmp std.collections.priority_queue.PriorityQueueWrapper.init_epilogue
std.collections.priority_queue.PriorityQueueWrapper.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.priority_queue.PriorityQueueWrapper.init:

.globl std.collections.tree.BTree.length
std.collections.tree.BTree.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.tree.BTree.length_entry:
  movq $0, rax
  jmp std.collections.tree.BTree.length_epilogue
std.collections.tree.BTree.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.BTree.length:

.globl std.collections.tree.BTree.init
std.collections.tree.BTree.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.tree.BTree.init_entry:
  movq $0, rax
  jmp std.collections.tree.BTree.init_epilogue
std.collections.tree.BTree.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.BTree.init:

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

.globl std.collections.list.List.pop
std.collections.list.List.pop:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.list.List.pop_entry:
  movq $0, rax
  jmp std.collections.list.List.pop_epilogue
std.collections.list.List.pop_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.list.List.pop:

.globl std.collections.tree.__init__
std.collections.tree.__init__:
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
std.collections.tree.__init___entry:
  movq $0, rax
  jmp std.collections.tree.__init___epilogue
std.collections.tree.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.tree.__init__:

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

.globl std.core.some_int
std.core.some_int:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.some_int_entry:
std.core.some_int_block_0:
  movq $0, rax
  jmp std.core.some_int_epilogue
std.core.some_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.some_int:

.globl std.collections.bloom_filter.BloomFilter.hash
std.collections.bloom_filter.BloomFilter.hash:
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
std.collections.bloom_filter.BloomFilter.hash_entry:
  movq $0, rax
  jmp std.collections.bloom_filter.BloomFilter.hash_epilogue
std.collections.bloom_filter.BloomFilter.hash_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bloom_filter.BloomFilter.hash:

.globl std.collections.index.Set
std.collections.index.Set:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.collections.index.Set_entry:
std.collections.index.Set_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq $0, rcx
  call lm_list_new
  movq [rbp + -64], rax
  addq $0, rax
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  movq $0, rax
  jmp std.collections.index.Set_epilogue
std.collections.index.Set_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.Set:

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

.globl std.collections.bloom_filter.BloomFilter._byte_ord
std.collections.bloom_filter.BloomFilter._byte_ord:
  push rbp
  mov rbp, rsp
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
std.collections.bloom_filter.BloomFilter._byte_ord_entry:
  movq $0, rax
  jmp std.collections.bloom_filter.BloomFilter._byte_ord_epilogue
std.collections.bloom_filter.BloomFilter._byte_ord_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bloom_filter.BloomFilter._byte_ord:

.globl std.collections.bloom_filter.__init__
std.collections.bloom_filter.__init__:
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
std.collections.bloom_filter.__init___entry:
  movq $0, rax
  jmp std.collections.bloom_filter.__init___epilogue
std.collections.bloom_filter.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bloom_filter.__init__:

.globl std.collections.btreemap.BTreeMapWrapper.put
std.collections.btreemap.BTreeMapWrapper.put:
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
std.collections.btreemap.BTreeMapWrapper.put_entry:
  movq $0, rax
  jmp std.collections.btreemap.BTreeMapWrapper.put_epilogue
std.collections.btreemap.BTreeMapWrapper.put_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.btreemap.BTreeMapWrapper.put:

.globl std.collections.btreemap.BTreeMapWrapper.get
std.collections.btreemap.BTreeMapWrapper.get:
  push rbp
  mov rbp, rsp
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
std.collections.btreemap.BTreeMapWrapper.get_entry:
  movq $0, rax
  jmp std.collections.btreemap.BTreeMapWrapper.get_epilogue
std.collections.btreemap.BTreeMapWrapper.get_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.btreemap.BTreeMapWrapper.get:

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

.globl std.collections.hashmap.HashMap.size
std.collections.hashmap.HashMap.size:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.hashmap.HashMap.size_entry:
  movq $0, rax
  jmp std.collections.hashmap.HashMap.size_epilogue
std.collections.hashmap.HashMap.size_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.hashmap.HashMap.size:

.globl std.collections.btreemap.BTreeMapWrapper.init
std.collections.btreemap.BTreeMapWrapper.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.btreemap.BTreeMapWrapper.init_entry:
  movq $0, rax
  jmp std.collections.btreemap.BTreeMapWrapper.init_epilogue
std.collections.btreemap.BTreeMapWrapper.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.btreemap.BTreeMapWrapper.init:

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

.globl std.core.OptionInt.is_some
std.core.OptionInt.is_some:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.OptionInt.is_some_entry:
  movq $0, rax
  jmp std.core.OptionInt.is_some_epilogue
std.core.OptionInt.is_some_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.OptionInt.is_some:

.globl std.core.OptionStr.is_none
std.core.OptionStr.is_none:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.OptionStr.is_none_entry:
  movq $0, rax
  jmp std.core.OptionStr.is_none_epilogue
std.core.OptionStr.is_none_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.OptionStr.is_none:

.globl std.collections.linked_list.DLL.push_back
std.collections.linked_list.DLL.push_back:
  push rbp
  mov rbp, rsp
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
std.collections.linked_list.DLL.push_back_entry:
  movq $0, rax
  jmp std.collections.linked_list.DLL.push_back_epilogue
std.collections.linked_list.DLL.push_back_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linked_list.DLL.push_back:

.globl std.core.OptionInt.is_none
std.core.OptionInt.is_none:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.OptionInt.is_none_entry:
  movq $0, rax
  jmp std.core.OptionInt.is_none_epilogue
std.core.OptionInt.is_none_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.OptionInt.is_none:

.globl std.core.OptionInt.unwrap_or
std.core.OptionInt.unwrap_or:
  push rbp
  mov rbp, rsp
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
std.core.OptionInt.unwrap_or_entry:
  movq $0, rax
  jmp std.core.OptionInt.unwrap_or_epilogue
std.core.OptionInt.unwrap_or_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.OptionInt.unwrap_or:

.globl std.core.OptionStr.is_some
std.core.OptionStr.is_some:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.OptionStr.is_some_entry:
  movq $0, rax
  jmp std.core.OptionStr.is_some_epilogue
std.core.OptionStr.is_some_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.OptionStr.is_some:

.globl std.core.OptionStr.unwrap
std.core.OptionStr.unwrap:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.OptionStr.unwrap_entry:
  movq $0, rax
  jmp std.core.OptionStr.unwrap_epilogue
std.core.OptionStr.unwrap_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.OptionStr.unwrap:

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

.globl std.core.ResultInt.is_ok
std.core.ResultInt.is_ok:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.ResultInt.is_ok_entry:
  movq $0, rax
  jmp std.core.ResultInt.is_ok_epilogue
std.core.ResultInt.is_ok_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ResultInt.is_ok:

.globl std.collections.bitset.BitSetWrapper.contains
std.collections.bitset.BitSetWrapper.contains:
  push rbp
  mov rbp, rsp
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
std.collections.bitset.BitSetWrapper.contains_entry:
  movq $0, rax
  jmp std.collections.bitset.BitSetWrapper.contains_epilogue
std.collections.bitset.BitSetWrapper.contains_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bitset.BitSetWrapper.contains:

.globl std.core.OptionStr.unwrap_or
std.core.OptionStr.unwrap_or:
  push rbp
  mov rbp, rsp
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
std.core.OptionStr.unwrap_or_entry:
  movq $0, rax
  jmp std.core.OptionStr.unwrap_or_epilogue
std.core.OptionStr.unwrap_or_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.OptionStr.unwrap_or:

.globl std.core.ResultInt.is_err
std.core.ResultInt.is_err:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.ResultInt.is_err_entry:
  movq $0, rax
  jmp std.core.ResultInt.is_err_epilogue
std.core.ResultInt.is_err_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ResultInt.is_err:

.globl std.core.ResultInt.map
std.core.ResultInt.map:
  push rbp
  mov rbp, rsp
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
std.core.ResultInt.map_entry:
  movq $0, rax
  jmp std.core.ResultInt.map_epilogue
std.core.ResultInt.map_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ResultInt.map:

.globl std.core.ResultStr.unwrap
std.core.ResultStr.unwrap:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.ResultStr.unwrap_entry:
  movq $0, rax
  jmp std.core.ResultStr.unwrap_epilogue
std.core.ResultStr.unwrap_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ResultStr.unwrap:

.globl std.core.ResultStr.unwrap_or
std.core.ResultStr.unwrap_or:
  push rbp
  mov rbp, rsp
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
std.core.ResultStr.unwrap_or_entry:
  movq $0, rax
  jmp std.core.ResultStr.unwrap_or_epilogue
std.core.ResultStr.unwrap_or_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ResultStr.unwrap_or:

.globl std.core.err_int
std.core.err_int:
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
std.core.err_int_entry:
std.core.err_int_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -96]
  movq [rbp + -72], rax
  movq [rbp + -96], rdx
  mov [rdx], rax
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -104], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -112]
  movq [rbp + -64], rax
  movq [rbp + -112], rdx
  mov [rdx], rax
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -120]
  movq [rbp + -72], rax
  movq [rbp + -120], rdx
  mov [rdx], rax
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -128]
  movq [rbp + -80], rax
  movq [rbp + -128], rdx
  mov [rdx], rax
  movq [rbp + -104], rax
  jmp std.core.err_int_epilogue
std.core.err_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.err_int:

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

.globl std.core.ResultStr.map_err
std.core.ResultStr.map_err:
  push rbp
  mov rbp, rsp
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
std.core.ResultStr.map_err_entry:
  movq $0, rax
  jmp std.core.ResultStr.map_err_epilogue
std.core.ResultStr.map_err_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ResultStr.map_err:

.globl std.collections.set.Set.is_disjoint
std.collections.set.Set.is_disjoint:
  push rbp
  mov rbp, rsp
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
std.collections.set.Set.is_disjoint_entry:
  movq $0, rax
  jmp std.collections.set.Set.is_disjoint_epilogue
std.collections.set.Set.is_disjoint_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.set.Set.is_disjoint:

.globl std.core.make_err_int
std.core.make_err_int:
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
std.core.make_err_int_entry:
std.core.make_err_int_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -96]
  movq [rbp + -72], rax
  movq [rbp + -96], rdx
  mov [rdx], rax
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -104], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -112]
  movq [rbp + -64], rax
  movq [rbp + -112], rdx
  mov [rdx], rax
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -120]
  movq [rbp + -72], rax
  movq [rbp + -120], rdx
  mov [rdx], rax
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -128]
  movq [rbp + -80], rax
  movq [rbp + -128], rdx
  mov [rdx], rax
  movq [rbp + -104], rax
  jmp std.core.make_err_int_epilogue
std.core.make_err_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.make_err_int:

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

.globl std.core.ok_str
std.core.ok_str:
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
std.core.ok_str_entry:
std.core.ok_str_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -104]
  movq [rbp + -72], rax
  movq [rbp + -104], rdx
  mov [rdx], rax
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -112], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -112], rax
  addq $0, rax
  movq rax, [rbp + -120]
  movq [rbp + -64], rax
  movq [rbp + -120], rdx
  mov [rdx], rax
  movq [rbp + -112], rax
  addq $0, rax
  movq rax, [rbp + -128]
  movq [rbp + -72], rax
  movq [rbp + -128], rdx
  mov [rdx], rax
  movq [rbp + -112], rax
  addq $0, rax
  movq rax, [rbp + -136]
  movq [rbp + -80], rax
  movq [rbp + -136], rdx
  mov [rdx], rax
  movq [rbp + -112], rax
  jmp std.core.ok_str_epilogue
std.core.ok_str_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.ok_str:

.globl std.core.make_err_str
std.core.make_err_str:
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
std.core.make_err_str_entry:
std.core.make_err_str_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -96]
  movq [rbp + -72], rax
  movq [rbp + -96], rdx
  mov [rdx], rax
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -104], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -112]
  movq [rbp + -64], rax
  movq [rbp + -112], rdx
  mov [rdx], rax
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -128]
  movq [rbp + -72], rax
  movq [rbp + -128], rdx
  mov [rdx], rax
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -136]
  movq [rbp + -80], rax
  movq [rbp + -136], rdx
  mov [rdx], rax
  movq [rbp + -104], rax
  jmp std.core.make_err_str_epilogue
std.core.make_err_str_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.make_err_str:

.globl std.collections.index.main
std.collections.index.main:
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
std.collections.index.main_entry:
std.collections.index.main_block_0:
  movq $0, rax
  jmp std.collections.index.main_epilogue
std.collections.index.main_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.main:

.globl std.core.__init__
std.core.__init__:
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
std.core.__init___entry:
  movq $0, rax
  jmp std.core.__init___epilogue
std.core.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.__init__:

.globl std.collections.bitset.BitSetWrapper.toggle
std.collections.bitset.BitSetWrapper.toggle:
  push rbp
  mov rbp, rsp
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
std.collections.bitset.BitSetWrapper.toggle_entry:
  movq $0, rax
  jmp std.collections.bitset.BitSetWrapper.toggle_epilogue
std.collections.bitset.BitSetWrapper.toggle_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bitset.BitSetWrapper.toggle:

.globl std.collections.map.HashMapWrapper.length
std.collections.map.HashMapWrapper.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.map.HashMapWrapper.length_entry:
  movq $0, rax
  jmp std.collections.map.HashMapWrapper.length_epilogue
std.collections.map.HashMapWrapper.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.map.HashMapWrapper.length:

.globl std.collections.index.Deque
std.collections.index.Deque:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.collections.index.Deque_entry:
std.collections.index.Deque_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.collections.deque.DoubleEndedQueue.init
  movq $0, rax
  jmp std.collections.index.Deque_epilogue
std.collections.index.Deque_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.index.Deque:

.globl std.collections.bitset.BitSetWrapper.get
std.collections.bitset.BitSetWrapper.get:
  push rbp
  mov rbp, rsp
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
std.collections.bitset.BitSetWrapper.get_entry:
  movq $0, rax
  jmp std.collections.bitset.BitSetWrapper.get_epilogue
std.collections.bitset.BitSetWrapper.get_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bitset.BitSetWrapper.get:

.globl std.collections.bitset.BitSetWrapper.get_size
std.collections.bitset.BitSetWrapper.get_size:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.bitset.BitSetWrapper.get_size_entry:
  movq $0, rax
  jmp std.collections.bitset.BitSetWrapper.get_size_epilogue
std.collections.bitset.BitSetWrapper.get_size_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.bitset.BitSetWrapper.get_size:

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

.globl std.collections.list.List.push
std.collections.list.List.push:
  push rbp
  mov rbp, rsp
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
std.collections.list.List.push_entry:
  movq $0, rax
  jmp std.collections.list.List.push_epilogue
std.collections.list.List.push_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.list.List.push:

.globl std.collections.list.List.length
std.collections.list.List.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.list.List.length_entry:
  movq $0, rax
  jmp std.collections.list.List.length_epilogue
std.collections.list.List.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.list.List.length:

.globl std.collections.linkedlist.LinkedList.pop_back
std.collections.linkedlist.LinkedList.pop_back:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.linkedlist.LinkedList.pop_back_entry:
  movq $0, rax
  jmp std.collections.linkedlist.LinkedList.pop_back_epilogue
std.collections.linkedlist.LinkedList.pop_back_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.linkedlist.LinkedList.pop_back:

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

.globl std.collections.map.HashMapWrapper.contains_key
std.collections.map.HashMapWrapper.contains_key:
  push rbp
  mov rbp, rsp
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
std.collections.map.HashMapWrapper.contains_key_entry:
  movq $0, rax
  jmp std.collections.map.HashMapWrapper.contains_key_epilogue
std.collections.map.HashMapWrapper.contains_key_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.map.HashMapWrapper.contains_key:

.globl std.collections.deque.DoubleEndedQueue.push_front
std.collections.deque.DoubleEndedQueue.push_front:
  push rbp
  mov rbp, rsp
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
std.collections.deque.DoubleEndedQueue.push_front_entry:
  movq $0, rax
  jmp std.collections.deque.DoubleEndedQueue.push_front_epilogue
std.collections.deque.DoubleEndedQueue.push_front_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.deque.DoubleEndedQueue.push_front:

.globl std.collections.map.HashMapWrapper.size
std.collections.map.HashMapWrapper.size:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.map.HashMapWrapper.size_entry:
  movq $0, rax
  jmp std.collections.map.HashMapWrapper.size_epilogue
std.collections.map.HashMapWrapper.size_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.map.HashMapWrapper.size:

.globl std.collections.map.__init__
std.collections.map.__init__:
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
std.collections.map.__init___entry:
  movq $0, rax
  jmp std.collections.map.__init___epilogue
std.collections.map.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.map.__init__:

.globl std.collections.deque.DoubleEndedQueue.push_back
std.collections.deque.DoubleEndedQueue.push_back:
  push rbp
  mov rbp, rsp
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
std.collections.deque.DoubleEndedQueue.push_back_entry:
  movq $0, rax
  jmp std.collections.deque.DoubleEndedQueue.push_back_epilogue
std.collections.deque.DoubleEndedQueue.push_back_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.deque.DoubleEndedQueue.push_back:

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

.globl std.collections.deque.DoubleEndedQueue.pop_front
std.collections.deque.DoubleEndedQueue.pop_front:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.deque.DoubleEndedQueue.pop_front_entry:
  movq $0, rax
  jmp std.collections.deque.DoubleEndedQueue.pop_front_epilogue
std.collections.deque.DoubleEndedQueue.pop_front_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.deque.DoubleEndedQueue.pop_front:

.globl std.collections.deque.DoubleEndedQueue.peek_back
std.collections.deque.DoubleEndedQueue.peek_back:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.deque.DoubleEndedQueue.peek_back_entry:
  movq $0, rax
  jmp std.collections.deque.DoubleEndedQueue.peek_back_epilogue
std.collections.deque.DoubleEndedQueue.peek_back_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.deque.DoubleEndedQueue.peek_back:

.globl std.collections.deque.DoubleEndedQueue.length
std.collections.deque.DoubleEndedQueue.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.collections.deque.DoubleEndedQueue.length_entry:
  movq $0, rax
  jmp std.collections.deque.DoubleEndedQueue.length_epilogue
std.collections.deque.DoubleEndedQueue.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.deque.DoubleEndedQueue.length:

.globl std.collections.stack.Stack.push
std.collections.stack.Stack.push:
  push rbp
  mov rbp, rsp
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
std.collections.stack.Stack.push_entry:
  movq $0, rax
  jmp std.collections.stack.Stack.push_epilogue
std.collections.stack.Stack.push_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.collections.stack.Stack.push:

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

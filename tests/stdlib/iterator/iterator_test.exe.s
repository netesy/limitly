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
  .string "twice"
.align 8
str_const_1:
  .string "even"
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
  call std.iterator.__init__
  call main
  movq $0, rax
  jmp main_epilogue
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
  movq $r0, rcx
  call std.iterator.iterator
  movq $0, rax
  cmpq $9, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  testq rax, rax
  jne main_block_13
  jmp main_block_15
main_block_13:
  jmp main_block_13
  movq $9, rax
  jmp main_epilogue
main_block_15:
  movq $0, rcx
  call lm_list_new
  movq $r14, rcx
  movq $9, rdx
  call lm_list_append
  movq $r14, rcx
  movq $17, rdx
  call lm_list_append
  movq $r14, rcx
  call std.iterator.iterator
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $r19, rcx
  movq [rbp + -72], rdx
  call std.iterator.map
  movq $r21, rcx
  call std.iterator.collect
  movq $r23, rcx
  movq $9, rdx
  call lm_list_get
  movq $r26, rax
  cmpq $33, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne main_block_31
  jmp main_block_33
main_block_31:
  jmp main_block_31
  movq $17, rax
  jmp main_epilogue
main_block_33:
  movq $0, rcx
  call lm_list_new
  movq $r31, rcx
  movq $9, rdx
  call lm_list_append
  movq $r31, rcx
  movq $17, rdx
  call lm_list_append
  movq $r31, rcx
  movq $25, rdx
  call lm_list_append
  movq $r31, rcx
  call std.iterator.iterator
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $r38, rcx
  movq [rbp + -88], rdx
  call std.iterator.filter
  movq $0, rax
  cmpq $17, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne main_block_48
  jmp main_block_50
main_block_48:
  jmp main_block_48
  movq $25, rax
  jmp main_epilogue
main_block_50:
  movq $0, rcx
  call lm_list_new
  movq $r47, rcx
  movq $9, rdx
  call lm_list_append
  movq $r47, rcx
  movq $17, rdx
  call lm_list_append
  movq $r47, rcx
  movq $25, rdx
  call lm_list_append
  movq $r47, rcx
  call std.iterator.iterator
  movq $r54, rcx
  movq $17, rdx
  call std.iterator.chunk
  movq $0, rcx
  call lm_list_new
  movq $r60, rcx
  movq $41, rdx
  call lm_list_append
  movq $r60, rcx
  call std.iterator.cycle
  movq $0, rax
  cmpq $41, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne main_block_72
  jmp main_block_74
main_block_72:
  jmp main_block_72
  movq $33, rax
  jmp main_epilogue
main_block_74:
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

.globl twice
twice:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
twice_entry:
twice_block_0:
  movq [rbp + -64], rax
  imulq $17, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp twice_epilogue
twice_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_twice:

.globl even
even:
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
even_entry:
even_block_0:
  movq [rbp + -64], rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rdx, [rbp + -72]
  movq [rbp + -72], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp even_epilogue
even_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_even:

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

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
  .string ""
.align 8
str_const_1:
  .string ""
.align 8
str_const_2:
  .string "ERR"
.align 8
str_const_3:
  .string ""
.align 8
str_const_4:
  .string "ERR"
.align 8
str_const_5:
  .string ""
.align 8
str_const_6:
  .string "ERR"
.align 8
str_const_7:
  .string ""
.align 8
str_const_8:
  .string ""
.align 8
str_const_9:
  .string "Testing BitSet..."
.align 8
str_const_10:
  .string "BitSet size should be 128"
.align 8
str_const_11:
  .string "BitSet get(10) incorrect"
.align 8
str_const_12:
  .string "BitSet get(11) incorrect"
.align 8
str_const_13:
  .string "BitSet get(10) after unset incorrect"
.align 8
str_const_14:
  .string "BitSet get(15) after toggle incorrect"
.align 8
str_const_15:
  .string "Testing PriorityQueue..."
.align 8
str_const_16:
  .string "compare_ints"
.align 8
str_const_17:
  .string "PriorityQueue peek should be 3"
.align 8
str_const_18:
  .string "PriorityQueue pop should be 3"
.align 8
str_const_19:
  .string "PriorityQueue pop should be 5"
.align 8
str_const_20:
  .string "PriorityQueue pop should be 10"
.align 8
str_const_21:
  .string "=== Collections Module Test Suite ==="
.align 8
str_const_22:
  .string "List test failed"
.align 8
str_const_23:
  .string "Deque test failed"
.align 8
str_const_24:
  .string "LinkedList test failed"
.align 8
str_const_25:
  .string "Maps test failed"
.align 8
str_const_26:
  .string "Sets test failed"
.align 8
str_const_27:
  .string "Queue/Stack test failed"
.align 8
str_const_28:
  .string "PriorityQueue test failed"
.align 8
str_const_29:
  .string "BitSet test failed"
.align 8
str_const_30:
  .string "BloomFilter test failed"
.align 8
str_const_31:
  .string "All collections tests passed successfully."
.align 8
str_const_32:
  .string "Testing Deque..."
.align 8
str_const_33:
  .string "Deque should be empty initially"
.align 8
str_const_34:
  .string "back1"
.align 8
str_const_35:
  .string "front1"
.align 8
str_const_36:
  .string "Deque length should be 2"
.align 8
str_const_37:
  .string "front1"
.align 8
str_const_38:
  .string "Front peek incorrect"
.align 8
str_const_39:
  .string "back1"
.align 8
str_const_40:
  .string "Back peek incorrect"
.align 8
str_const_41:
  .string "front1"
.align 8
str_const_42:
  .string "Pop front incorrect"
.align 8
str_const_43:
  .string "Deque length incorrect after pop_front"
.align 8
str_const_44:
  .string "back1"
.align 8
str_const_45:
  .string "Pop back incorrect"
.align 8
str_const_46:
  .string "Deque length incorrect after pop_back"
.align 8
str_const_47:
  .string "Testing BloomFilter..."
.align 8
str_const_48:
  .string "hello"
.align 8
str_const_49:
  .string "world"
.align 8
str_const_50:
  .string "hello"
.align 8
str_const_51:
  .string "BloomFilter should contain 'hello'"
.align 8
str_const_52:
  .string "world"
.align 8
str_const_53:
  .string "BloomFilter should contain 'world'"
.align 8
str_const_54:
  .string "not_added"
.align 8
str_const_55:
  .string "BloomFilter should not contain 'not_added'"
.align 8
str_const_56:
  .string "Testing List..."
.align 8
str_const_57:
  .string "List should be empty initially"
.align 8
str_const_58:
  .string "first"
.align 8
str_const_59:
  .string "second"
.align 8
str_const_60:
  .string "List length should be 2"
.align 8
str_const_61:
  .string "first"
.align 8
str_const_62:
  .string "First element should be 'first'"
.align 8
str_const_63:
  .string "second"
.align 8
str_const_64:
  .string "Second element should be 'second'"
.align 8
str_const_65:
  .string "updated"
.align 8
str_const_66:
  .string "updated"
.align 8
str_const_67:
  .string "Set should update element"
.align 8
str_const_68:
  .string "updated"
.align 8
str_const_69:
  .string "Pop should return last element"
.align 8
str_const_70:
  .string "List length should be 1 after pop"
.align 8
str_const_71:
  .string "List length should be 0 after clear"
.align 8
str_const_72:
  .string "Testing Sets..."
.align 8
str_const_73:
  .string "item1"
.align 8
str_const_74:
  .string "item1"
.align 8
str_const_75:
  .string "HashSet contains incorrect"
.align 8
str_const_76:
  .string "item1"
.align 8
str_const_77:
  .string "item1"
.align 8
str_const_78:
  .string "HashSet contains after remove incorrect"
.align 8
str_const_79:
  .string "bitem"
.align 8
str_const_80:
  .string "bitem"
.align 8
str_const_81:
  .string "BTreeSet contains incorrect"
.align 8
str_const_82:
  .string "Testing LinkedList..."
.align 8
str_const_83:
  .string "LinkedList instantiated"
.align 8
str_const_84:
  .string "LinkedList should be empty"
.align 8
str_const_85:
  .string "back1"
.align 8
str_const_86:
  .string "push_back back1"
.align 8
str_const_87:
  .string "front1"
.align 8
str_const_88:
  .string "push_front front1"
.align 8
str_const_89:
  .string "LinkedList length should be 2"
.align 8
str_const_90:
  .string "popped front: %s"
.align 8
str_const_91:
  .string "front1"
.align 8
str_const_92:
  .string "Pop front incorrect"
.align 8
str_const_93:
  .string "popped back: %s"
.align 8
str_const_94:
  .string "back1"
.align 8
str_const_95:
  .string "Pop back incorrect"
.align 8
str_const_96:
  .string "Testing Queue and Stack..."
.align 8
str_const_97:
  .string "q1"
.align 8
str_const_98:
  .string "q1"
.align 8
str_const_99:
  .string "Queue peek incorrect"
.align 8
str_const_100:
  .string "q1"
.align 8
str_const_101:
  .string "Queue dequeue incorrect"
.align 8
str_const_102:
  .string "s1"
.align 8
str_const_103:
  .string "s1"
.align 8
str_const_104:
  .string "Stack peek incorrect"
.align 8
str_const_105:
  .string "s1"
.align 8
str_const_106:
  .string "Stack pop incorrect"
.align 8
str_const_107:
  .string ""
.align 8
str_const_108:
  .string ""
.align 8
str_const_109:
  .string "Testing Maps..."
.align 8
str_const_110:
  .string "key1"
.align 8
str_const_111:
  .string "key1"
.align 8
str_const_112:
  .string "Failed to get key1"
.align 8
str_const_113:
  .string "Map get incorrect"
.align 8
str_const_114:
  .string "key2"
.align 8
str_const_115:
  .string "key2"
.align 8
str_const_116:
  .string "Failed to get key2"
.align 8
str_const_117:
  .string "HashMap get incorrect"
.align 8
str_const_118:
  .string "bkey"
.align 8
str_const_119:
  .string "bval"
.align 8
str_const_120:
  .string "bkey"
.align 8
str_const_121:
  .string "bval"
.align 8
str_const_122:
  .string "BTreeMap get incorrect"
.align 8
str_const_123:
  .string "ERR"
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
  sub rsp, 248
main_entry:
main_block_0:
  call std.collections.list.__init__
  call std.collections.deque.__init__
  call std.collections.linked_list.__init__
  call std.collections.map.__init__
  call std.collections.hashmap.__init__
  call std.collections.hashset.__init__
  call std.collections.btreemap.__init__
  call std.collections.btreeset.__init__
  call std.collections.queue.__init__
  call std.collections.stack.__init__
  call std.collections.priority_queue.__init__
  call std.collections.bitset.__init__
  call std.collections.bloom_filter.__init__
  call std.collections.index.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq [rel str_const_21], rcx
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
  call test_list
  movq $r2, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_deque
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  call test_linked_list
  movq $r12, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  call test_maps
  movq $r17, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  call test_sets
  movq $r22, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  call test_queue_stack
  movq $r27, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  call test_priority_queue
  movq $r32, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  call test_bitset
  movq $r37, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  call test_bloom_filter
  movq $r42, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  addq $16, rax
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  mov rax, [rax]
  movq rax, [rbp + -264]
  movq [rbp + -264], rcx
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
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_1], rcx
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
  movq [rel str_const_2], rcx
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
  movq [rel str_const_3], rcx
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
  movq [rel str_const_4], rcx
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
  movq [rel str_const_5], rcx
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

.globl compare_ints
compare_ints:
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
compare_ints_entry:
compare_ints_block_0:
  movq [rbp + -64], rax
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  movq rax, [rbp + -88]
  movq [rbp + -80], rax
  cmpq [rbp + -88], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne compare_ints_block_6
  jmp compare_ints_block_9
compare_ints_block_6:
  jmp compare_ints_block_6
  movq $9, rax
  negq rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  jmp compare_ints_epilogue
compare_ints_block_9:
  movq [rbp + -80], rax
  cmpq [rbp + -88], rax
  setg al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne compare_ints_block_11
  jmp compare_ints_block_13
compare_ints_block_11:
  jmp compare_ints_block_11
  movq $9, rax
  jmp compare_ints_epilogue
compare_ints_block_13:
  movq $1, rax
  jmp compare_ints_epilogue
compare_ints_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_compare_ints:

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
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_8], rcx
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

.globl test_bitset
test_bitset:
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
test_bitset_entry:
test_bitset_block_0:
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
  movq $1025, rcx
  call std.collections.index.BitSet
  movq $r3, rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.collections.bitset.BitSetWrapper.get_size
  movq $r6, rax
  cmpq $1025, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq [rbp + -96], rcx
  movq $81, rdx
  call std.collections.bitset.BitSetWrapper.set
  movq [rbp + -96], rcx
  movq $81, rdx
  call std.collections.bitset.BitSetWrapper.get
  movq $r14, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq [rbp + -96], rcx
  movq $89, rdx
  call std.collections.bitset.BitSetWrapper.get
  movq $r20, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  movq [rbp + -96], rcx
  movq $81, rdx
  call std.collections.bitset.BitSetWrapper.unset
  movq [rbp + -96], rcx
  movq $81, rdx
  call std.collections.bitset.BitSetWrapper.get
  movq $r28, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq [rbp + -96], rcx
  movq $121, rdx
  call std.collections.bitset.BitSetWrapper.toggle
  movq [rbp + -96], rcx
  movq $121, rdx
  call std.collections.bitset.BitSetWrapper.get
  movq $r36, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call lm_assert
  movq $9, rax
  jmp test_bitset_epilogue
test_bitset_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_bitset:

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

.globl test_priority_queue
test_priority_queue:
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
test_priority_queue_entry:
test_priority_queue_block_0:
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
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.collections.index.PriorityQueue
  movq $r3, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  movq $41, rdx
  call std.collections.priority_queue.PriorityQueueWrapper.push
  movq [rbp + -104], rcx
  movq $25, rdx
  call std.collections.priority_queue.PriorityQueueWrapper.push
  movq [rbp + -104], rcx
  movq $81, rdx
  call std.collections.priority_queue.PriorityQueueWrapper.push
  movq [rbp + -104], rcx
  call std.collections.priority_queue.PriorityQueueWrapper.peek
  movq $r12, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq [rbp + -104], rcx
  call std.collections.priority_queue.PriorityQueueWrapper.pop
  movq $r17, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rbp + -104], rcx
  call std.collections.priority_queue.PriorityQueueWrapper.pop
  movq $r22, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rbp + -104], rcx
  call std.collections.priority_queue.PriorityQueueWrapper.pop
  movq $r27, rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq $9, rax
  jmp test_priority_queue_epilogue
test_priority_queue_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_priority_queue:

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

.globl test_deque
test_deque:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 264
test_deque_entry:
test_deque_block_0:
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
  call std.collections.index.Deque
  movq $r2, rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.collections.deque.DoubleEndedQueue.length
  movq $r5, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -96], rcx
  movq [rbp + -120], rdx
  call std.collections.deque.DoubleEndedQueue.push_back
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -96], rcx
  movq [rbp + -128], rdx
  call std.collections.deque.DoubleEndedQueue.push_front
  movq [rbp + -96], rcx
  call std.collections.deque.DoubleEndedQueue.length
  movq $r14, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.collections.deque.DoubleEndedQueue.peek_front
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq $r19, rax
  cmpq [rbp + -152], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.collections.deque.DoubleEndedQueue.peek_back
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq $r24, rax
  cmpq [rbp + -176], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -184], rcx
  movq [rbp + -192], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.collections.deque.DoubleEndedQueue.pop_front
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq $r29, rax
  cmpq [rbp + -200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.collections.deque.DoubleEndedQueue.length
  movq $r35, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.collections.deque.DoubleEndedQueue.pop_back
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq $r40, rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -248], rcx
  movq [rbp + -256], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.collections.deque.DoubleEndedQueue.length
  movq $r46, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -264]
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -264], rcx
  movq [rbp + -272], rdx
  call lm_assert
  movq $9, rax
  jmp test_deque_epilogue
test_deque_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_deque:

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

.globl test_bloom_filter
test_bloom_filter:
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
test_bloom_filter_entry:
test_bloom_filter_block_0:
  movq [rel str_const_47], rcx
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
  movq $4097, rcx
  movq $25, rdx
  call std.collections.index.BloomFilter
  movq $r4, rax
  movq rax, [rbp + -96]
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call std.collections.bloom_filter.BloomFilter.add
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -96], rcx
  movq [rbp + -112], rdx
  call std.collections.bloom_filter.BloomFilter.add
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -96], rcx
  movq [rbp + -120], rdx
  call std.collections.bloom_filter.BloomFilter.contains
  movq $r12, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -96], rcx
  movq [rbp + -144], rdx
  call std.collections.bloom_filter.BloomFilter.contains
  movq $r18, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -96], rcx
  movq [rbp + -168], rdx
  call std.collections.bloom_filter.BloomFilter.contains
  movq $r24, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq $9, rax
  jmp test_bloom_filter_epilogue
test_bloom_filter_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_bloom_filter:

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

.globl test_list
test_list:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 264
test_list_entry:
test_list_block_0:
  movq [rel str_const_56], rcx
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
  call std.collections.index.List
  movq $r2, rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.collections.list.List.length
  movq $r5, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -96], rcx
  movq [rbp + -120], rdx
  call std.collections.list.List.append
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -96], rcx
  movq [rbp + -128], rdx
  call std.collections.list.List.push
  movq [rbp + -96], rcx
  call std.collections.list.List.length
  movq $r14, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  movq [rbp + -96], rcx
  movq $1, rdx
  call std.collections.list.List.get
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq $r20, rax
  cmpq [rbp + -152], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq [rbp + -96], rcx
  movq $9, rdx
  call std.collections.list.List.get
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq $r26, rax
  cmpq [rbp + -176], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -184], rcx
  movq [rbp + -192], rdx
  call lm_assert
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -96], rcx
  movq $9, rdx
  movq [rbp + -200], r8
  call std.collections.list.List.set
  movq [rbp + -96], rcx
  movq $9, rdx
  call std.collections.list.List.get
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq $r35, rax
  cmpq [rbp + -208], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -216]
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -216], rcx
  movq [rbp + -224], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.collections.list.List.pop
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq $r40, rax
  cmpq [rbp + -232], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_69], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.collections.list.List.length
  movq $r46, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rel str_const_70], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -256], rcx
  movq [rbp + -264], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.collections.list.List.clear
  movq [rbp + -96], rcx
  call std.collections.list.List.length
  movq $r52, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -272]
  movq [rel str_const_71], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -272], rcx
  movq [rbp + -280], rdx
  call lm_assert
  movq $9, rax
  jmp test_list_epilogue
test_list_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_list:

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

.globl test_sets
test_sets:
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
test_sets_entry:
test_sets_block_0:
  movq [rel str_const_72], rcx
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
  call std.collections.index.HashSet
  movq $r2, rax
  movq rax, [rbp + -96]
  movq [rel str_const_73], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call std.collections.hashset.HashSetWrapper.add
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -96], rcx
  movq [rbp + -112], rdx
  call std.collections.hashset.HashSetWrapper.contains
  movq $r8, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_75], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -96], rcx
  movq [rbp + -136], rdx
  call std.collections.hashset.HashSetWrapper.remove
  movq [rel str_const_77], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -96], rcx
  movq [rbp + -144], rdx
  call std.collections.hashset.HashSetWrapper.contains
  movq $r16, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_78], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  call std.collections.index.BTreeSet
  movq $r21, rax
  movq rax, [rbp + -168]
  movq [rel str_const_79], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call std.collections.btreeset.BTreeSetWrapper.add
  movq [rel str_const_80], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -168], rcx
  movq [rbp + -184], rdx
  call std.collections.btreeset.BTreeSetWrapper.contains
  movq $r27, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_81], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq $9, rax
  jmp test_sets_epilogue
test_sets_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_sets:

.globl test_linked_list
test_linked_list:
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
test_linked_list_entry:
test_linked_list_block_0:
  movq [rel str_const_82], rcx
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
  call std.collections.index.LinkedList
  movq $r2, rax
  movq rax, [rbp + -96]
  movq [rel str_const_83], rcx
  call lm_box_string
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
  movq [rbp + -96], rcx
  call std.collections.linked_list.DLL.length
  movq $r7, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_84], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  movq [rel str_const_85], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -96], rcx
  movq [rbp + -152], rdx
  call std.collections.linked_list.DLL.push_back
  movq [rel str_const_86], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  addq $16, rax
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  mov rax, [rax]
  movq rax, [rbp + -184]
  movq [rbp + -184], rcx
  call lm_print_str
  movq [rel str_const_87], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -96], rcx
  movq [rbp + -192], rdx
  call std.collections.linked_list.DLL.push_front
  movq [rel str_const_88], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  addq $16, rax
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  mov rax, [rax]
  movq rax, [rbp + -224]
  movq [rbp + -224], rcx
  call lm_print_str
  movq [rbp + -96], rcx
  call std.collections.linked_list.DLL.length
  movq $r20, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  movq [rel str_const_89], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rcx
  movq [rbp + -240], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.collections.linked_list.DLL.pop_front
  movq [rel str_const_90], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -248], rcx
  movq $r25, rdx
  call lm_rt_str_format
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  addq $16, rax
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  mov rax, [rax]
  movq rax, [rbp + -280]
  movq [rbp + -280], rcx
  call lm_print_str
  movq [rel str_const_91], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq $r25, rax
  cmpq [rbp + -288], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rel str_const_92], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -296], rcx
  movq [rbp + -304], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.collections.linked_list.DLL.pop_back
  movq [rel str_const_93], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -312], rcx
  movq $r34, rdx
  call lm_rt_str_format
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  addq $16, rax
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  movq rax, [rbp + -336]
  movq [rbp + -336], rax
  mov rax, [rax]
  movq rax, [rbp + -344]
  movq [rbp + -344], rcx
  call lm_print_str
  movq [rel str_const_94], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq $r34, rax
  cmpq [rbp + -352], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rel str_const_95], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -360], rcx
  movq [rbp + -368], rdx
  call lm_assert
  movq $9, rax
  jmp test_linked_list_epilogue
test_linked_list_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_linked_list:

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

.globl test_queue_stack
test_queue_stack:
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
test_queue_stack_entry:
test_queue_stack_block_0:
  movq [rel str_const_96], rcx
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
  call std.collections.index.Queue
  movq $r2, rax
  movq rax, [rbp + -96]
  movq [rel str_const_97], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call std.collections.queue.Queue.enqueue
  movq [rbp + -96], rcx
  call std.collections.queue.Queue.peek
  movq [rel str_const_98], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r7, rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_99], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.collections.queue.Queue.dequeue
  movq [rel str_const_100], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r12, rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_101], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  call std.collections.index.Stack
  movq $r17, rax
  movq rax, [rbp + -160]
  movq [rel str_const_102], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call std.collections.stack.Stack.push
  movq [rbp + -160], rcx
  call std.collections.stack.Stack.peek
  movq [rel str_const_103], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq $r22, rax
  cmpq [rbp + -176], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rel str_const_104], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -184], rcx
  movq [rbp + -192], rdx
  call lm_assert
  movq [rbp + -160], rcx
  call std.collections.stack.Stack.pop
  movq [rel str_const_105], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq $r27, rax
  cmpq [rbp + -200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_106], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq $9, rax
  jmp test_queue_stack_epilogue
test_queue_stack_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_queue_stack:

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
  movq [rel str_const_107], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_108], rcx
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

.globl test_maps
test_maps:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 248
test_maps_entry:
test_maps_block_0:
  movq [rel str_const_109], rcx
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
  call std.collections.index.Map
  movq $r2, rax
  movq rax, [rbp + -96]
  movq [rel str_const_110], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  movq $337, r8
  call std.collections.map.HashMapWrapper.put
  movq [rel str_const_111], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -96], rcx
  movq [rbp + -112], rdx
  call std.collections.map.HashMapWrapper.get
  movq $r9, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne test_maps_block_13
  jmp test_maps_block_12
test_maps_block_12:
  jmp test_maps_block_12
  jmp test_maps_block_20
test_maps_block_13:
  movq [rel str_const_112], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq $10, rcx
  movq [rbp + -128], rdx
  call lm_assert
  jmp test_maps_block_23
test_maps_block_20:
  jmp test_maps_block_23
test_maps_block_23:
  movq $r9, rax
  cmpq $337, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_113], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  call std.collections.index.HashMap
  movq $r23, rax
  movq rax, [rbp + -152]
  movq [rel str_const_114], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  movq $801, r8
  call std.collections.hashmap.HashMap.put
  movq [rel str_const_115], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq $r28, rcx
  movq [rbp + -168], rdx
  call std.collections.hashmap.HashMap.get
  movq $r30, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne test_maps_block_40
  jmp test_maps_block_39
test_maps_block_39:
  jmp test_maps_block_39
  jmp test_maps_block_47
test_maps_block_40:
  movq [rel str_const_116], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq $10, rcx
  movq [rbp + -184], rdx
  call lm_assert
  jmp test_maps_block_50
test_maps_block_47:
  jmp test_maps_block_50
test_maps_block_50:
  movq $r30, rax
  cmpq $801, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_117], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  call std.collections.index.BTreeMap
  movq $r44, rax
  movq rax, [rbp + -208]
  movq [rel str_const_118], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rel str_const_119], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  movq [rbp + -224], r8
  call std.collections.btreemap.BTreeMapWrapper.put
  movq [rel str_const_120], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -208], rcx
  movq [rbp + -232], rdx
  call std.collections.btreemap.BTreeMapWrapper.get
  movq [rel str_const_121], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq $r51, rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  movq [rel str_const_122], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -248], rcx
  movq [rbp + -256], rdx
  call lm_assert
  movq $9, rax
  jmp test_maps_epilogue
test_maps_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_maps:

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
  movq [rel str_const_123], rcx
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

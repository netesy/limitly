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
  .string "=== Advanced Match Statement Tests ==="
.align 8
str_const_1:
  .string "
--- Test 1: Record Destructuring (Dictionaries) ---"
.align 8
str_const_2:
  .string "name"
.align 8
str_const_3:
  .string "John"
.align 8
str_const_4:
  .string "age"
.align 8
str_const_5:
  .string "name"
.align 8
str_const_6:
  .string "Joan"
.align 8
str_const_7:
  .string "age"
.align 8
str_const_8:
  .string "city"
.align 8
str_const_9:
  .string "New York"
.align 8
str_const_10:
  .string "Name: John, Age: 30"
.align 8
str_const_11:
  .string "Record destructuring with 2 fields failed"
.align 8
str_const_12:
  .string "Name: Joan, Age: 26, City: New York"
.align 8
str_const_13:
  .string "Record destructuring with 3 fields failed"
.align 8
str_const_14:
  .string "Result 1: %s"
.align 8
str_const_15:
  .string "Result 2: %s"
.align 8
str_const_16:
  .string "
--- Test 2: List Destructuring ---"
.align 8
str_const_17:
  .string "Empty list"
.align 8
str_const_18:
  .string "Empty list destructuring failed"
.align 8
str_const_19:
  .string "One element: 1"
.align 8
str_const_20:
  .string "Single element list destructuring failed"
.align 8
str_const_21:
  .string "Two elements: 1, 2"
.align 8
str_const_22:
  .string "Two element list destructuring failed"
.align 8
str_const_23:
  .string "Head: 1, Tail: [2, 3, 4, 5]"
.align 8
str_const_24:
  .string "List with spread destructuring failed"
.align 8
str_const_25:
  .string "Empty: %s"
.align 8
str_const_26:
  .string "One: %s"
.align 8
str_const_27:
  .string "Two: %s"
.align 8
str_const_28:
  .string "Many: %s"
.align 8
str_const_29:
  .string "
--- Test 3: Tuple Destructuring ---"
.align 8
str_const_30:
  .string "Tuple: (10, 20)"
.align 8
str_const_31:
  .string "2-tuple destructuring failed"
.align 8
str_const_32:
  .string "3-tuple: (1, 2, 3)"
.align 8
str_const_33:
  .string "3-tuple destructuring failed"
.align 8
str_const_34:
  .string "2-tuple: %s"
.align 8
str_const_35:
  .string "3-tuple: %s"
.align 8
str_const_36:
  .string "
--- Test 4: Nested Destructuring ---"
.align 8
str_const_37:
  .string "name"
.align 8
str_const_38:
  .string "Alice"
.align 8
str_const_39:
  .string "scores"
.align 8
str_const_40:
  .string "Nested: x=100, a=10, b=20"
.align 8
str_const_41:
  .string "Tuple+List nested destructuring failed"
.align 8
str_const_42:
  .string "Record with list: Alice, scores: 95, 87"
.align 8
str_const_43:
  .string "Record with list destructuring failed"
.align 8
str_const_44:
  .string "Nested 1: %s"
.align 8
str_const_45:
  .string "Nested 2: %s"
.align 8
str_const_46:
  .string "
--- Test 5: Mixed Pattern Types ---"
.align 8
str_const_47:
  .string "Circle with radius 5"
.align 8
str_const_48:
  .string "Circle shape description failed"
.align 8
str_const_49:
  .string "Rectangle 10x20"
.align 8
str_const_50:
  .string "Rectangle shape description failed"
.align 8
str_const_51:
  .string "Point at (3, 4)"
.align 8
str_const_52:
  .string "Point shape description failed"
.align 8
str_const_53:
  .string "Circle: %s"
.align 8
str_const_54:
  .string "Rectangle: %s"
.align 8
str_const_55:
  .string "Point: %s"
.align 8
str_const_56:
  .string "
--- Test 6: Destructuring with Guards ---"
.align 8
str_const_57:
  .string "name"
.align 8
str_const_58:
  .string "Alice"
.align 8
str_const_59:
  .string "age"
.align 8
str_const_60:
  .string "name"
.align 8
str_const_61:
  .string "Bob"
.align 8
str_const_62:
  .string "age"
.align 8
str_const_63:
  .string "Alice is an adult (25)"
.align 8
str_const_64:
  .string "Adult guard test failed"
.align 8
str_const_65:
  .string "Bob is a minor (16)"
.align 8
str_const_66:
  .string "Minor guard test failed"
.align 8
str_const_67:
  .string "Adult: %s"
.align 8
str_const_68:
  .string "Minor: %s"
.align 8
str_const_69:
  .string "
--- Test 7: List Destructuring with Spread ---"
.align 8
str_const_70:
  .string "First: 1, Rest: [2, 3, 4, 5]"
.align 8
str_const_71:
  .string "Spread destructuring with multiple elements failed"
.align 8
str_const_72:
  .string "First: 100, Rest: []"
.align 8
str_const_73:
  .string "Spread destructuring with single element failed"
.align 8
str_const_74:
  .string "Spread 1: %s"
.align 8
str_const_75:
  .string "Spread 2: %s"
.align 8
str_const_76:
  .string "
--- Test 8: Tuple with Nested List ---"
.align 8
str_const_77:
  .string "Tuple+List: x=99, [a,b,c]=[1,2,3]"
.align 8
str_const_78:
  .string "Nested tuple+list destructuring failed"
.align 8
str_const_79:
  .string "Nested: %s"
.align 8
str_const_80:
  .string "
--- Test 9: Record with Optional Fields ---"
.align 8
str_const_81:
  .string "name"
.align 8
str_const_82:
  .string "John"
.align 8
str_const_83:
  .string "age"
.align 8
str_const_84:
  .string "city"
.align 8
str_const_85:
  .string "NYC"
.align 8
str_const_86:
  .string "name"
.align 8
str_const_87:
  .string "Jane"
.align 8
str_const_88:
  .string "age"
.align 8
str_const_89:
  .string "John, 30, NYC"
.align 8
str_const_90:
  .string "Record with city failed"
.align 8
str_const_91:
  .string "Jane, 25 (no city)"
.align 8
str_const_92:
  .string "Record without city failed"
.align 8
str_const_93:
  .string "With city: %s"
.align 8
str_const_94:
  .string "Without city: %s"
.align 8
str_const_95:
  .string "
--- Test 10: Complex Nested Patterns ---"
.align 8
str_const_96:
  .string "name"
.align 8
str_const_97:
  .string "test"
.align 8
str_const_98:
  .string "values"
.align 8
str_const_99:
  .string "Complex: x=42, name=test, values=[10,20]"
.align 8
str_const_100:
  .string "Complex nested pattern failed"
.align 8
str_const_101:
  .string "Complex: %s"
.align 8
str_const_102:
  .string "
--- Test 11: Enum with Multiple Payloads ---"
.align 8
str_const_103:
  .string "Move to (10, 20)"
.align 8
str_const_104:
  .string "Move command failed"
.align 8
str_const_105:
  .string "Resize to 100x200"
.align 8
str_const_106:
  .string "Resize command failed"
.align 8
str_const_107:
  .string "Color RGB(255, 128, 64)"
.align 8
str_const_108:
  .string "Color command failed"
.align 8
str_const_109:
  .string "Move: %s"
.align 8
str_const_110:
  .string "Resize: %s"
.align 8
str_const_111:
  .string "Color: %s"
.align 8
str_const_112:
  .string "
--- Test 12: Destructuring in Nested Match ---"
.align 8
str_const_113:
  .string "Nested: x=100, a=1, b=20"
.align 8
str_const_114:
  .string "Nested match with a=1 failed"
.align 8
str_const_115:
  .string "Nested: x=200, a=2, b=30"
.align 8
str_const_116:
  .string "Nested match with a=2 failed"
.align 8
str_const_117:
  .string "Nested: x=300, a=5, b=40"
.align 8
str_const_118:
  .string "Nested match with a=5 failed"
.align 8
str_const_119:
  .string "Nested 1: %s"
.align 8
str_const_120:
  .string "Nested 2: %s"
.align 8
str_const_121:
  .string "Nested 3: %s"
.align 8
str_const_122:
  .string "
=== Advanced Match Statement Tests Complete ==="
.align 8
str_const_123:
  .string "Nested: x=%s, a=%s, b=%s"
.align 8
str_const_124:
  .string "Nested: x=%s, a=2, b=%s"
.align 8
str_const_125:
  .string "Nested: x=%s, a=1, b=%s"
.align 8
str_const_126:
  .string "name"
.align 8
str_const_127:
  .string "age"
.align 8
str_const_128:
  .string "name"
.align 8
str_const_129:
  .string "age"
.align 8
str_const_130:
  .string "%s is an adult (%s)"
.align 8
str_const_131:
  .string "name"
.align 8
str_const_132:
  .string "age"
.align 8
str_const_133:
  .string "name"
.align 8
str_const_134:
  .string "age"
.align 8
str_const_135:
  .string "%s is a minor (%s)"
.align 8
str_const_136:
  .string "Empty list"
.align 8
str_const_137:
  .string "First: %s, Rest: %s"
.align 8
str_const_138:
  .string "name"
.align 8
str_const_139:
  .string "scores"
.align 8
str_const_140:
  .string "name"
.align 8
str_const_141:
  .string "scores"
.align 8
str_const_142:
  .string "Record with list: %s, scores: %s, %s"
.align 8
str_const_143:
  .string "Nested: x=%s, a=%s, b=%s"
.align 8
str_const_144:
  .string "3-tuple: (%s, %s, %s)"
.align 8
str_const_145:
  .string "Tuple: (%s, %s)"
.align 8
str_const_146:
  .string "Head: %s, Tail: %s"
.align 8
str_const_147:
  .string "Two elements: %s, %s"
.align 8
str_const_148:
  .string "One element: %s"
.align 8
str_const_149:
  .string "Empty list"
.align 8
str_const_150:
  .string "name"
.align 8
str_const_151:
  .string "age"
.align 8
str_const_152:
  .string "name"
.align 8
str_const_153:
  .string "age"
.align 8
str_const_154:
  .string "city"
.align 8
str_const_155:
  .string "name"
.align 8
str_const_156:
  .string "age"
.align 8
str_const_157:
  .string "city"
.align 8
str_const_158:
  .string "Name: %s, Age: %s, City: %s"
.align 8
str_const_159:
  .string "name"
.align 8
str_const_160:
  .string "age"
.align 8
str_const_161:
  .string "Name: %s, Age: %s"
.align 8
str_const_162:
  .string "Color RGB(%s, %s, %s)"
.align 8
str_const_163:
  .string "Resize to %sx%s"
.align 8
str_const_164:
  .string "Move to (%s, %s)"
.align 8
str_const_165:
  .string "name"
.align 8
str_const_166:
  .string "values"
.align 8
str_const_167:
  .string "name"
.align 8
str_const_168:
  .string "values"
.align 8
str_const_169:
  .string "Complex: x=%s, name=%s, values=[%s,%s]"
.align 8
str_const_170:
  .string "name"
.align 8
str_const_171:
  .string "age"
.align 8
str_const_172:
  .string "city"
.align 8
str_const_173:
  .string "name"
.align 8
str_const_174:
  .string "age"
.align 8
str_const_175:
  .string "name"
.align 8
str_const_176:
  .string "age"
.align 8
str_const_177:
  .string "%s, %s (no city)"
.align 8
str_const_178:
  .string "name"
.align 8
str_const_179:
  .string "age"
.align 8
str_const_180:
  .string "city"
.align 8
str_const_181:
  .string "%s, %s, %s"
.align 8
str_const_182:
  .string "Point at (%s, %s)"
.align 8
str_const_183:
  .string "Rectangle %sx%s"
.align 8
str_const_184:
  .string "Circle with radius %s"
.align 8
str_const_185:
  .string "Tuple+List: x=%s, [a,b,c]=[%s,%s,%s]"
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
  sub rsp, 2440
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
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  addq $16, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  mov rax, [rax]
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  call lm_print_str
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq $0, rcx
  call testRecordDestructuring
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq $0, rcx
  call testRecordDestructuring
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq $r9, rax
  cmpq [rbp + -192], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -200], rcx
  movq [rbp + -208], rdx
  call lm_assert
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq $r18, rax
  cmpq [rbp + -216], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -240], rcx
  movq $r9, rdx
  call lm_rt_str_format
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  addq $16, rax
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  mov rax, [rax]
  movq rax, [rbp + -272]
  movq [rbp + -272], rcx
  call lm_print_str
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -280], rcx
  movq $r18, rdx
  call lm_rt_str_format
  movq rax, [rbp + -288]
  movq [rbp + -288], rax
  addq $16, rax
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  mov rax, [rax]
  movq rax, [rbp + -312]
  movq [rbp + -312], rcx
  call lm_print_str
  movq [rel str_const_16], rcx
  call lm_box_string
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
  movq $0, rcx
  call lm_list_new
  movq $r36, rcx
  call testListDestructuring
  movq $0, rcx
  call lm_list_new
  movq $r39, rcx
  movq $9, rdx
  call lm_list_append
  movq $r39, rcx
  call testListDestructuring
  movq $0, rcx
  call lm_list_new
  movq $r44, rcx
  movq $9, rdx
  call lm_list_append
  movq $r44, rcx
  movq $17, rdx
  call lm_list_append
  movq $r44, rcx
  call testListDestructuring
  movq $0, rcx
  call lm_list_new
  movq $r51, rcx
  movq $9, rdx
  call lm_list_append
  movq $r51, rcx
  movq $17, rdx
  call lm_list_append
  movq $r51, rcx
  movq $25, rdx
  call lm_list_append
  movq $r51, rcx
  movq $33, rdx
  call lm_list_append
  movq $r51, rcx
  movq $41, rdx
  call lm_list_append
  movq $r51, rcx
  call testListDestructuring
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq $r37, rax
  cmpq [rbp + -352], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -360], rcx
  movq [rbp + -368], rdx
  call lm_assert
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq $r42, rax
  cmpq [rbp + -376], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -384]
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq [rbp + -384], rcx
  movq [rbp + -392], rdx
  call lm_assert
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq $r49, rax
  cmpq [rbp + -400], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -408]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -408], rcx
  movq [rbp + -416], rdx
  call lm_assert
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq $r62, rax
  cmpq [rbp + -424], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -432]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rbp + -432], rcx
  movq [rbp + -440], rdx
  call lm_assert
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -448], rcx
  movq $r37, rdx
  call lm_rt_str_format
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
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -488]
  movq [rbp + -488], rcx
  movq $r42, rdx
  call lm_rt_str_format
  movq rax, [rbp + -496]
  movq [rbp + -496], rax
  addq $16, rax
  movq rax, [rbp + -504]
  movq [rbp + -504], rax
  movq rax, [rbp + -512]
  movq [rbp + -512], rax
  mov rax, [rax]
  movq rax, [rbp + -520]
  movq [rbp + -520], rcx
  call lm_print_str
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -528], rcx
  movq $r49, rdx
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
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -568]
  movq [rbp + -568], rcx
  movq $r62, rdx
  call lm_rt_str_format
  movq rax, [rbp + -576]
  movq [rbp + -576], rax
  addq $16, rax
  movq rax, [rbp + -584]
  movq [rbp + -584], rax
  movq rax, [rbp + -592]
  movq [rbp + -592], rax
  mov rax, [rax]
  movq rax, [rbp + -600]
  movq [rbp + -600], rcx
  call lm_print_str
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -608]
  movq [rbp + -608], rax
  addq $16, rax
  movq rax, [rbp + -616]
  movq [rbp + -616], rax
  movq rax, [rbp + -624]
  movq [rbp + -624], rax
  mov rax, [rax]
  movq rax, [rbp + -632]
  movq [rbp + -632], rcx
  call lm_print_str
  movq $0, rcx
  call testTupleDestructuring
  movq $0, rcx
  call testTupleDestructuring
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq $r99, rax
  cmpq [rbp + -640], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -648]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -656]
  movq [rbp + -648], rcx
  movq [rbp + -656], rdx
  call lm_assert
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -664]
  movq $r108, rax
  cmpq [rbp + -664], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -672]
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -680]
  movq [rbp + -672], rcx
  movq [rbp + -680], rdx
  call lm_assert
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -688]
  movq [rbp + -688], rcx
  movq $r99, rdx
  call lm_rt_str_format
  movq rax, [rbp + -696]
  movq [rbp + -696], rax
  addq $16, rax
  movq rax, [rbp + -704]
  movq [rbp + -704], rax
  movq rax, [rbp + -712]
  movq [rbp + -712], rax
  mov rax, [rax]
  movq rax, [rbp + -720]
  movq [rbp + -720], rcx
  call lm_print_str
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -728]
  movq [rbp + -728], rcx
  movq $r108, rdx
  call lm_rt_str_format
  movq rax, [rbp + -736]
  movq [rbp + -736], rax
  addq $16, rax
  movq rax, [rbp + -744]
  movq [rbp + -744], rax
  movq rax, [rbp + -752]
  movq [rbp + -752], rax
  mov rax, [rax]
  movq rax, [rbp + -760]
  movq [rbp + -760], rcx
  call lm_print_str
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -768]
  movq [rbp + -768], rax
  addq $16, rax
  movq rax, [rbp + -776]
  movq [rbp + -776], rax
  movq rax, [rbp + -784]
  movq [rbp + -784], rax
  mov rax, [rax]
  movq rax, [rbp + -792]
  movq [rbp + -792], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $r129, rcx
  movq $81, rdx
  call lm_list_append
  movq $r129, rcx
  movq $161, rdx
  call lm_list_append
  movq $0, rcx
  call testNestedDestructuring
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -800]
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -808]
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -816]
  movq $0, rcx
  call lm_list_new
  movq $r141, rcx
  movq $761, rdx
  call lm_list_append
  movq $r141, rcx
  movq $697, rdx
  call lm_list_append
  movq $0, rcx
  call testNestedDestructuring
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -824]
  movq $r135, rax
  cmpq [rbp + -824], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -832]
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -840]
  movq [rbp + -832], rcx
  movq [rbp + -840], rdx
  call lm_assert
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -848]
  movq $r146, rax
  cmpq [rbp + -848], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -856]
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -864]
  movq [rbp + -856], rcx
  movq [rbp + -864], rdx
  call lm_assert
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -872]
  movq [rbp + -872], rcx
  movq $r135, rdx
  call lm_rt_str_format
  movq rax, [rbp + -880]
  movq [rbp + -880], rax
  addq $16, rax
  movq rax, [rbp + -888]
  movq [rbp + -888], rax
  movq rax, [rbp + -896]
  movq [rbp + -896], rax
  mov rax, [rax]
  movq rax, [rbp + -904]
  movq [rbp + -904], rcx
  call lm_print_str
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -912]
  movq [rbp + -912], rcx
  movq $r146, rdx
  call lm_rt_str_format
  movq rax, [rbp + -920]
  movq [rbp + -920], rax
  addq $16, rax
  movq rax, [rbp + -928]
  movq [rbp + -928], rax
  movq rax, [rbp + -936]
  movq [rbp + -936], rax
  mov rax, [rax]
  movq rax, [rbp + -944]
  movq [rbp + -944], rcx
  call lm_print_str
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -952]
  movq [rbp + -952], rax
  addq $16, rax
  movq rax, [rbp + -960]
  movq [rbp + -960], rax
  movq rax, [rbp + -968]
  movq [rbp + -968], rax
  mov rax, [rax]
  movq rax, [rbp + -976]
  movq [rbp + -976], rcx
  call lm_print_str
  movq $0, rcx
  call describeShape
  movq $0, rcx
  call describeShape
  movq $0, rcx
  call describeShape
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -984]
  movq $r167, rax
  cmpq [rbp + -984], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -992]
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -1000]
  movq [rbp + -992], rcx
  movq [rbp + -1000], rdx
  call lm_assert
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -1008]
  movq $r175, rax
  cmpq [rbp + -1008], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1016]
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -1024]
  movq [rbp + -1016], rcx
  movq [rbp + -1024], rdx
  call lm_assert
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -1032]
  movq $r183, rax
  cmpq [rbp + -1032], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1040]
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -1048]
  movq [rbp + -1040], rcx
  movq [rbp + -1048], rdx
  call lm_assert
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -1056]
  movq [rbp + -1056], rcx
  movq $r167, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1064]
  movq [rbp + -1064], rax
  addq $16, rax
  movq rax, [rbp + -1072]
  movq [rbp + -1072], rax
  movq rax, [rbp + -1080]
  movq [rbp + -1080], rax
  mov rax, [rax]
  movq rax, [rbp + -1088]
  movq [rbp + -1088], rcx
  call lm_print_str
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -1096]
  movq [rbp + -1096], rcx
  movq $r175, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1104]
  movq [rbp + -1104], rax
  addq $16, rax
  movq rax, [rbp + -1112]
  movq [rbp + -1112], rax
  movq rax, [rbp + -1120]
  movq [rbp + -1120], rax
  mov rax, [rax]
  movq rax, [rbp + -1128]
  movq [rbp + -1128], rcx
  call lm_print_str
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -1136]
  movq [rbp + -1136], rcx
  movq $r183, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1144]
  movq [rbp + -1144], rax
  addq $16, rax
  movq rax, [rbp + -1152]
  movq [rbp + -1152], rax
  movq rax, [rbp + -1160]
  movq [rbp + -1160], rax
  mov rax, [rax]
  movq rax, [rbp + -1168]
  movq [rbp + -1168], rcx
  call lm_print_str
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -1176]
  movq [rbp + -1176], rax
  addq $16, rax
  movq rax, [rbp + -1184]
  movq [rbp + -1184], rax
  movq rax, [rbp + -1192]
  movq [rbp + -1192], rax
  mov rax, [rax]
  movq rax, [rbp + -1200]
  movq [rbp + -1200], rcx
  call lm_print_str
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -1208]
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -1216]
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -1224]
  movq $0, rcx
  call testDestructuringWithGuards
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -1232]
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -1240]
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -1248]
  movq $0, rcx
  call testDestructuringWithGuards
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -1256]
  movq $r213, rax
  cmpq [rbp + -1256], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1264]
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -1272]
  movq [rbp + -1264], rcx
  movq [rbp + -1272], rdx
  call lm_assert
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -1280]
  movq $r220, rax
  cmpq [rbp + -1280], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1288]
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -1296]
  movq [rbp + -1288], rcx
  movq [rbp + -1296], rdx
  call lm_assert
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -1304]
  movq [rbp + -1304], rcx
  movq $r213, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1312]
  movq [rbp + -1312], rax
  addq $16, rax
  movq rax, [rbp + -1320]
  movq [rbp + -1320], rax
  movq rax, [rbp + -1328]
  movq [rbp + -1328], rax
  mov rax, [rax]
  movq rax, [rbp + -1336]
  movq [rbp + -1336], rcx
  call lm_print_str
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -1344]
  movq [rbp + -1344], rcx
  movq $r220, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1352]
  movq [rbp + -1352], rax
  addq $16, rax
  movq rax, [rbp + -1360]
  movq [rbp + -1360], rax
  movq rax, [rbp + -1368]
  movq [rbp + -1368], rax
  mov rax, [rax]
  movq rax, [rbp + -1376]
  movq [rbp + -1376], rcx
  call lm_print_str
  movq [rel str_const_69], rcx
  call lm_box_string
  movq rax, [rbp + -1384]
  movq [rbp + -1384], rax
  addq $16, rax
  movq rax, [rbp + -1392]
  movq [rbp + -1392], rax
  movq rax, [rbp + -1400]
  movq [rbp + -1400], rax
  mov rax, [rax]
  movq rax, [rbp + -1408]
  movq [rbp + -1408], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $r238, rcx
  movq $9, rdx
  call lm_list_append
  movq $r238, rcx
  movq $17, rdx
  call lm_list_append
  movq $r238, rcx
  movq $25, rdx
  call lm_list_append
  movq $r238, rcx
  movq $33, rdx
  call lm_list_append
  movq $r238, rcx
  movq $41, rdx
  call lm_list_append
  movq $r238, rcx
  call testSpreadDestructuring
  movq $0, rcx
  call lm_list_new
  movq $r251, rcx
  movq $801, rdx
  call lm_list_append
  movq $r251, rcx
  call testSpreadDestructuring
  movq [rel str_const_70], rcx
  call lm_box_string
  movq rax, [rbp + -1416]
  movq $r249, rax
  cmpq [rbp + -1416], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1424]
  movq [rel str_const_71], rcx
  call lm_box_string
  movq rax, [rbp + -1432]
  movq [rbp + -1424], rcx
  movq [rbp + -1432], rdx
  call lm_assert
  movq [rel str_const_72], rcx
  call lm_box_string
  movq rax, [rbp + -1440]
  movq $r254, rax
  cmpq [rbp + -1440], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1448]
  movq [rel str_const_73], rcx
  call lm_box_string
  movq rax, [rbp + -1456]
  movq [rbp + -1448], rcx
  movq [rbp + -1456], rdx
  call lm_assert
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -1464]
  movq [rbp + -1464], rcx
  movq $r249, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1472]
  movq [rbp + -1472], rax
  addq $16, rax
  movq rax, [rbp + -1480]
  movq [rbp + -1480], rax
  movq rax, [rbp + -1488]
  movq [rbp + -1488], rax
  mov rax, [rax]
  movq rax, [rbp + -1496]
  movq [rbp + -1496], rcx
  call lm_print_str
  movq [rel str_const_75], rcx
  call lm_box_string
  movq rax, [rbp + -1504]
  movq [rbp + -1504], rcx
  movq $r254, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1512]
  movq [rbp + -1512], rax
  addq $16, rax
  movq rax, [rbp + -1520]
  movq [rbp + -1520], rax
  movq rax, [rbp + -1528]
  movq [rbp + -1528], rax
  mov rax, [rax]
  movq rax, [rbp + -1536]
  movq [rbp + -1536], rcx
  call lm_print_str
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -1544]
  movq [rbp + -1544], rax
  addq $16, rax
  movq rax, [rbp + -1552]
  movq [rbp + -1552], rax
  movq rax, [rbp + -1560]
  movq [rbp + -1560], rax
  mov rax, [rax]
  movq rax, [rbp + -1568]
  movq [rbp + -1568], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $r275, rcx
  movq $9, rdx
  call lm_list_append
  movq $r275, rcx
  movq $17, rdx
  call lm_list_append
  movq $r275, rcx
  movq $25, rdx
  call lm_list_append
  movq $0, rcx
  call testNestedTupleList
  movq [rel str_const_77], rcx
  call lm_box_string
  movq rax, [rbp + -1576]
  movq $r283, rax
  cmpq [rbp + -1576], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1584]
  movq [rel str_const_78], rcx
  call lm_box_string
  movq rax, [rbp + -1592]
  movq [rbp + -1584], rcx
  movq [rbp + -1592], rdx
  call lm_assert
  movq [rel str_const_79], rcx
  call lm_box_string
  movq rax, [rbp + -1600]
  movq [rbp + -1600], rcx
  movq $r283, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1608]
  movq [rbp + -1608], rax
  addq $16, rax
  movq rax, [rbp + -1616]
  movq [rbp + -1616], rax
  movq rax, [rbp + -1624]
  movq [rbp + -1624], rax
  mov rax, [rax]
  movq rax, [rbp + -1632]
  movq [rbp + -1632], rcx
  call lm_print_str
  movq [rel str_const_80], rcx
  call lm_box_string
  movq rax, [rbp + -1640]
  movq [rbp + -1640], rax
  addq $16, rax
  movq rax, [rbp + -1648]
  movq [rbp + -1648], rax
  movq rax, [rbp + -1656]
  movq [rbp + -1656], rax
  mov rax, [rax]
  movq rax, [rbp + -1664]
  movq [rbp + -1664], rcx
  call lm_print_str
  movq [rel str_const_81], rcx
  call lm_box_string
  movq rax, [rbp + -1672]
  movq [rel str_const_82], rcx
  call lm_box_string
  movq rax, [rbp + -1680]
  movq [rel str_const_83], rcx
  call lm_box_string
  movq rax, [rbp + -1688]
  movq [rel str_const_84], rcx
  call lm_box_string
  movq rax, [rbp + -1696]
  movq [rel str_const_85], rcx
  call lm_box_string
  movq rax, [rbp + -1704]
  movq $0, rcx
  call testOptionalFields
  movq [rel str_const_86], rcx
  call lm_box_string
  movq rax, [rbp + -1712]
  movq [rel str_const_87], rcx
  call lm_box_string
  movq rax, [rbp + -1720]
  movq [rel str_const_88], rcx
  call lm_box_string
  movq rax, [rbp + -1728]
  movq $0, rcx
  call testOptionalFields
  movq [rel str_const_89], rcx
  call lm_box_string
  movq rax, [rbp + -1736]
  movq $r301, rax
  cmpq [rbp + -1736], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1744]
  movq [rel str_const_90], rcx
  call lm_box_string
  movq rax, [rbp + -1752]
  movq [rbp + -1744], rcx
  movq [rbp + -1752], rdx
  call lm_assert
  movq [rel str_const_91], rcx
  call lm_box_string
  movq rax, [rbp + -1760]
  movq $r308, rax
  cmpq [rbp + -1760], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1768]
  movq [rel str_const_92], rcx
  call lm_box_string
  movq rax, [rbp + -1776]
  movq [rbp + -1768], rcx
  movq [rbp + -1776], rdx
  call lm_assert
  movq [rel str_const_93], rcx
  call lm_box_string
  movq rax, [rbp + -1784]
  movq [rbp + -1784], rcx
  movq $r301, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1792]
  movq [rbp + -1792], rax
  addq $16, rax
  movq rax, [rbp + -1800]
  movq [rbp + -1800], rax
  movq rax, [rbp + -1808]
  movq [rbp + -1808], rax
  mov rax, [rax]
  movq rax, [rbp + -1816]
  movq [rbp + -1816], rcx
  call lm_print_str
  movq [rel str_const_94], rcx
  call lm_box_string
  movq rax, [rbp + -1824]
  movq [rbp + -1824], rcx
  movq $r308, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1832]
  movq [rbp + -1832], rax
  addq $16, rax
  movq rax, [rbp + -1840]
  movq [rbp + -1840], rax
  movq rax, [rbp + -1848]
  movq [rbp + -1848], rax
  mov rax, [rax]
  movq rax, [rbp + -1856]
  movq [rbp + -1856], rcx
  call lm_print_str
  movq [rel str_const_95], rcx
  call lm_box_string
  movq rax, [rbp + -1864]
  movq [rbp + -1864], rax
  addq $16, rax
  movq rax, [rbp + -1872]
  movq [rbp + -1872], rax
  movq rax, [rbp + -1880]
  movq [rbp + -1880], rax
  mov rax, [rax]
  movq rax, [rbp + -1888]
  movq [rbp + -1888], rcx
  call lm_print_str
  movq [rel str_const_96], rcx
  call lm_box_string
  movq rax, [rbp + -1896]
  movq [rel str_const_97], rcx
  call lm_box_string
  movq rax, [rbp + -1904]
  movq [rel str_const_98], rcx
  call lm_box_string
  movq rax, [rbp + -1912]
  movq $0, rcx
  call lm_list_new
  movq $r333, rcx
  movq $81, rdx
  call lm_list_append
  movq $r333, rcx
  movq $161, rdx
  call lm_list_append
  movq $0, rcx
  call testComplexNested
  movq [rel str_const_99], rcx
  call lm_box_string
  movq rax, [rbp + -1920]
  movq $r339, rax
  cmpq [rbp + -1920], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1928]
  movq [rel str_const_100], rcx
  call lm_box_string
  movq rax, [rbp + -1936]
  movq [rbp + -1928], rcx
  movq [rbp + -1936], rdx
  call lm_assert
  movq [rel str_const_101], rcx
  call lm_box_string
  movq rax, [rbp + -1944]
  movq [rbp + -1944], rcx
  movq $r339, rdx
  call lm_rt_str_format
  movq rax, [rbp + -1952]
  movq [rbp + -1952], rax
  addq $16, rax
  movq rax, [rbp + -1960]
  movq [rbp + -1960], rax
  movq rax, [rbp + -1968]
  movq [rbp + -1968], rax
  mov rax, [rax]
  movq rax, [rbp + -1976]
  movq [rbp + -1976], rcx
  call lm_print_str
  movq [rel str_const_102], rcx
  call lm_box_string
  movq rax, [rbp + -1984]
  movq [rbp + -1984], rax
  addq $16, rax
  movq rax, [rbp + -1992]
  movq [rbp + -1992], rax
  movq rax, [rbp + -2000]
  movq [rbp + -2000], rax
  mov rax, [rax]
  movq rax, [rbp + -2008]
  movq [rbp + -2008], rcx
  call lm_print_str
  movq $0, rcx
  call processCommand
  movq $0, rcx
  call processCommand
  movq $0, rcx
  call processCommand
  movq [rel str_const_103], rcx
  call lm_box_string
  movq rax, [rbp + -2016]
  movq $r356, rax
  cmpq [rbp + -2016], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -2024]
  movq [rel str_const_104], rcx
  call lm_box_string
  movq rax, [rbp + -2032]
  movq [rbp + -2024], rcx
  movq [rbp + -2032], rdx
  call lm_assert
  movq [rel str_const_105], rcx
  call lm_box_string
  movq rax, [rbp + -2040]
  movq $r364, rax
  cmpq [rbp + -2040], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -2048]
  movq [rel str_const_106], rcx
  call lm_box_string
  movq rax, [rbp + -2056]
  movq [rbp + -2048], rcx
  movq [rbp + -2056], rdx
  call lm_assert
  movq [rel str_const_107], rcx
  call lm_box_string
  movq rax, [rbp + -2064]
  movq $r374, rax
  cmpq [rbp + -2064], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -2072]
  movq [rel str_const_108], rcx
  call lm_box_string
  movq rax, [rbp + -2080]
  movq [rbp + -2072], rcx
  movq [rbp + -2080], rdx
  call lm_assert
  movq [rel str_const_109], rcx
  call lm_box_string
  movq rax, [rbp + -2088]
  movq [rbp + -2088], rcx
  movq $r356, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2096]
  movq [rbp + -2096], rax
  addq $16, rax
  movq rax, [rbp + -2104]
  movq [rbp + -2104], rax
  movq rax, [rbp + -2112]
  movq [rbp + -2112], rax
  mov rax, [rax]
  movq rax, [rbp + -2120]
  movq [rbp + -2120], rcx
  call lm_print_str
  movq [rel str_const_110], rcx
  call lm_box_string
  movq rax, [rbp + -2128]
  movq [rbp + -2128], rcx
  movq $r364, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2136]
  movq [rbp + -2136], rax
  addq $16, rax
  movq rax, [rbp + -2144]
  movq [rbp + -2144], rax
  movq rax, [rbp + -2152]
  movq [rbp + -2152], rax
  mov rax, [rax]
  movq rax, [rbp + -2160]
  movq [rbp + -2160], rcx
  call lm_print_str
  movq [rel str_const_111], rcx
  call lm_box_string
  movq rax, [rbp + -2168]
  movq [rbp + -2168], rcx
  movq $r374, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2176]
  movq [rbp + -2176], rax
  addq $16, rax
  movq rax, [rbp + -2184]
  movq [rbp + -2184], rax
  movq rax, [rbp + -2192]
  movq [rbp + -2192], rax
  mov rax, [rax]
  movq rax, [rbp + -2200]
  movq [rbp + -2200], rcx
  call lm_print_str
  movq [rel str_const_112], rcx
  call lm_box_string
  movq rax, [rbp + -2208]
  movq [rbp + -2208], rax
  addq $16, rax
  movq rax, [rbp + -2216]
  movq [rbp + -2216], rax
  movq rax, [rbp + -2224]
  movq [rbp + -2224], rax
  mov rax, [rax]
  movq rax, [rbp + -2232]
  movq [rbp + -2232], rcx
  call lm_print_str
  movq $0, rcx
  call lm_list_new
  movq $r402, rcx
  movq $9, rdx
  call lm_list_append
  movq $r402, rcx
  movq $161, rdx
  call lm_list_append
  movq $0, rcx
  call testNestedDestructure
  movq $0, rcx
  call lm_list_new
  movq $r413, rcx
  movq $17, rdx
  call lm_list_append
  movq $r413, rcx
  movq $241, rdx
  call lm_list_append
  movq $0, rcx
  call testNestedDestructure
  movq $0, rcx
  call lm_list_new
  movq $r424, rcx
  movq $41, rdx
  call lm_list_append
  movq $r424, rcx
  movq $321, rdx
  call lm_list_append
  movq $0, rcx
  call testNestedDestructure
  movq [rel str_const_113], rcx
  call lm_box_string
  movq rax, [rbp + -2240]
  movq $r408, rax
  cmpq [rbp + -2240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -2248]
  movq [rel str_const_114], rcx
  call lm_box_string
  movq rax, [rbp + -2256]
  movq [rbp + -2248], rcx
  movq [rbp + -2256], rdx
  call lm_assert
  movq [rel str_const_115], rcx
  call lm_box_string
  movq rax, [rbp + -2264]
  movq $r419, rax
  cmpq [rbp + -2264], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -2272]
  movq [rel str_const_116], rcx
  call lm_box_string
  movq rax, [rbp + -2280]
  movq [rbp + -2272], rcx
  movq [rbp + -2280], rdx
  call lm_assert
  movq [rel str_const_117], rcx
  call lm_box_string
  movq rax, [rbp + -2288]
  movq $r430, rax
  cmpq [rbp + -2288], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -2296]
  movq [rel str_const_118], rcx
  call lm_box_string
  movq rax, [rbp + -2304]
  movq [rbp + -2296], rcx
  movq [rbp + -2304], rdx
  call lm_assert
  movq [rel str_const_119], rcx
  call lm_box_string
  movq rax, [rbp + -2312]
  movq [rbp + -2312], rcx
  movq $r408, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2320]
  movq [rbp + -2320], rax
  addq $16, rax
  movq rax, [rbp + -2328]
  movq [rbp + -2328], rax
  movq rax, [rbp + -2336]
  movq [rbp + -2336], rax
  mov rax, [rax]
  movq rax, [rbp + -2344]
  movq [rbp + -2344], rcx
  call lm_print_str
  movq [rel str_const_120], rcx
  call lm_box_string
  movq rax, [rbp + -2352]
  movq [rbp + -2352], rcx
  movq $r419, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2360]
  movq [rbp + -2360], rax
  addq $16, rax
  movq rax, [rbp + -2368]
  movq [rbp + -2368], rax
  movq rax, [rbp + -2376]
  movq [rbp + -2376], rax
  mov rax, [rax]
  movq rax, [rbp + -2384]
  movq [rbp + -2384], rcx
  call lm_print_str
  movq [rel str_const_121], rcx
  call lm_box_string
  movq rax, [rbp + -2392]
  movq [rbp + -2392], rcx
  movq $r430, rdx
  call lm_rt_str_format
  movq rax, [rbp + -2400]
  movq [rbp + -2400], rax
  addq $16, rax
  movq rax, [rbp + -2408]
  movq [rbp + -2408], rax
  movq rax, [rbp + -2416]
  movq [rbp + -2416], rax
  mov rax, [rax]
  movq rax, [rbp + -2424]
  movq [rbp + -2424], rcx
  call lm_print_str
  movq [rel str_const_122], rcx
  call lm_box_string
  movq rax, [rbp + -2432]
  movq [rbp + -2432], rax
  addq $16, rax
  movq rax, [rbp + -2440]
  movq [rbp + -2440], rax
  movq rax, [rbp + -2448]
  movq [rbp + -2448], rax
  mov rax, [rax]
  movq rax, [rbp + -2456]
  movq [rbp + -2456], rcx
  call lm_print_str
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

.globl testNestedDestructure
testNestedDestructure:
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
testNestedDestructure_entry:
testNestedDestructure_block_0:
  jmp testNestedDestructure_block_1
testNestedDestructure_block_1:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne testNestedDestructure_block_5
  jmp testNestedDestructure_block_18
testNestedDestructure_block_5:
  jmp testNestedDestructure_block_5
  movq $0, rcx
  call lm_list_len
  movq $r8, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne testNestedDestructure_block_13
  jmp testNestedDestructure_block_18
testNestedDestructure_block_13:
  jmp testNestedDestructure_block_13
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq $0, rcx
  movq $9, rdx
  call lm_list_get
  jmp testNestedDestructure_block_19
testNestedDestructure_block_18:
  movq $0, rax
  jmp testNestedDestructure_epilogue
testNestedDestructure_block_19:
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq $0, rcx
  movq $9, rdx
  call lm_list_get
  jmp testNestedDestructure_block_28
testNestedDestructure_block_28:
  movq $r20, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne testNestedDestructure_block_31
  jmp testNestedDestructure_block_32
testNestedDestructure_block_31:
  jmp testNestedDestructure_block_31
  jmp testNestedDestructure_block_48
testNestedDestructure_block_32:
  movq $r20, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne testNestedDestructure_block_35
  jmp testNestedDestructure_block_36
testNestedDestructure_block_35:
  jmp testNestedDestructure_block_35
  jmp testNestedDestructure_block_43
testNestedDestructure_block_36:
  jmp testNestedDestructure_block_37
testNestedDestructure_block_37:
  movq [rel str_const_123], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -112]
  movq [rbp + -112], rcx
  movq $r20, rdx
  call lm_rt_str_format
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  movq $r22, rdx
  call lm_rt_str_format
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  jmp testNestedDestructure_epilogue
testNestedDestructure_block_43:
  movq [rel str_const_124], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  movq $r22, rdx
  call lm_rt_str_format
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  jmp testNestedDestructure_epilogue
testNestedDestructure_block_48:
  movq [rel str_const_125], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -168]
  movq [rbp + -168], rcx
  movq $r22, rdx
  call lm_rt_str_format
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  jmp testNestedDestructure_epilogue
testNestedDestructure_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_testNestedDestructure:

.globl testDestructuringWithGuards
testDestructuringWithGuards:
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
testDestructuringWithGuards_entry:
testDestructuringWithGuards_block_0:
  jmp testDestructuringWithGuards_block_1
testDestructuringWithGuards_block_1:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne testDestructuringWithGuards_block_5
  jmp testDestructuringWithGuards_block_25
testDestructuringWithGuards_block_5:
  jmp testDestructuringWithGuards_block_5
  movq [rel str_const_126], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq $0, rax
  testq rax, rax
  jne testDestructuringWithGuards_block_8
  jmp testDestructuringWithGuards_block_25
testDestructuringWithGuards_block_8:
  jmp testDestructuringWithGuards_block_8
  movq [rel str_const_127], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $0, rax
  testq rax, rax
  jne testDestructuringWithGuards_block_12
  jmp testDestructuringWithGuards_block_25
testDestructuringWithGuards_block_12:
  jmp testDestructuringWithGuards_block_12
  movq $0, rax
  cmpq $145, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne testDestructuringWithGuards_block_16
  jmp testDestructuringWithGuards_block_25
testDestructuringWithGuards_block_16:
  jmp testDestructuringWithGuards_block_16
  movq [rel str_const_128], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rel str_const_129], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rel str_const_130], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp testDestructuringWithGuards_epilogue
testDestructuringWithGuards_block_25:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  testq rax, rax
  jne testDestructuringWithGuards_block_29
  jmp testDestructuringWithGuards_block_49
testDestructuringWithGuards_block_29:
  jmp testDestructuringWithGuards_block_29
  movq [rel str_const_131], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq $0, rax
  testq rax, rax
  jne testDestructuringWithGuards_block_32
  jmp testDestructuringWithGuards_block_49
testDestructuringWithGuards_block_32:
  jmp testDestructuringWithGuards_block_32
  movq [rel str_const_132], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq $0, rax
  testq rax, rax
  jne testDestructuringWithGuards_block_36
  jmp testDestructuringWithGuards_block_49
testDestructuringWithGuards_block_36:
  jmp testDestructuringWithGuards_block_36
  movq $0, rax
  cmpq $145, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  testq rax, rax
  jne testDestructuringWithGuards_block_40
  jmp testDestructuringWithGuards_block_49
testDestructuringWithGuards_block_40:
  jmp testDestructuringWithGuards_block_40
  movq [rel str_const_133], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rel str_const_134], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rel str_const_135], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -192], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  jmp testDestructuringWithGuards_epilogue
testDestructuringWithGuards_block_49:
  movq $0, rax
  jmp testDestructuringWithGuards_epilogue
testDestructuringWithGuards_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_testDestructuringWithGuards:

.globl testSpreadDestructuring
testSpreadDestructuring:
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
testSpreadDestructuring_entry:
testSpreadDestructuring_block_0:
  jmp testSpreadDestructuring_block_1
testSpreadDestructuring_block_1:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  cmpq $9, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne testSpreadDestructuring_block_5
  jmp testSpreadDestructuring_block_8
testSpreadDestructuring_block_5:
  jmp testSpreadDestructuring_block_5
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  jmp testSpreadDestructuring_block_16
testSpreadDestructuring_block_8:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r19, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne testSpreadDestructuring_block_12
  jmp testSpreadDestructuring_block_13
testSpreadDestructuring_block_12:
  jmp testSpreadDestructuring_block_12
  jmp testSpreadDestructuring_block_14
testSpreadDestructuring_block_13:
  movq $0, rax
  jmp testSpreadDestructuring_epilogue
testSpreadDestructuring_block_14:
  movq [rel str_const_136], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp testSpreadDestructuring_epilogue
testSpreadDestructuring_block_16:
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $0, rcx
  call lm_list_new
  movq [rbp + -64], rcx
  call lm_list_len
  jmp testSpreadDestructuring_block_22
testSpreadDestructuring_block_22:
  movq $9, rax
  cmpq $r9, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne testSpreadDestructuring_block_24
  jmp testSpreadDestructuring_block_30
testSpreadDestructuring_block_24:
  jmp testSpreadDestructuring_block_24
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  movq $r8, rcx
  movq $r12, rdx
  call lm_list_append
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp testSpreadDestructuring_block_22
testSpreadDestructuring_block_30:
  movq [rel str_const_137], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -112], rcx
  movq $r7, rdx
  call lm_rt_str_format
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  movq $r8, rdx
  call lm_rt_str_format
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  jmp testSpreadDestructuring_epilogue
testSpreadDestructuring_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_testSpreadDestructuring:

.globl testNestedDestructuring
testNestedDestructuring:
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
  mov [rbp + -64], rcx
testNestedDestructuring_entry:
testNestedDestructuring_block_0:
  jmp testNestedDestructuring_block_1
testNestedDestructuring_block_1:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne testNestedDestructuring_block_5
  jmp testNestedDestructuring_block_18
testNestedDestructuring_block_5:
  jmp testNestedDestructuring_block_5
  movq $0, rcx
  call lm_list_len
  movq $r8, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne testNestedDestructuring_block_13
  jmp testNestedDestructuring_block_18
testNestedDestructuring_block_13:
  jmp testNestedDestructuring_block_13
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq $0, rcx
  movq $9, rdx
  call lm_list_get
  jmp testNestedDestructuring_block_54
testNestedDestructuring_block_18:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne testNestedDestructuring_block_22
  jmp testNestedDestructuring_block_39
testNestedDestructuring_block_22:
  jmp testNestedDestructuring_block_22
  movq [rel str_const_138], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $0, rax
  testq rax, rax
  jne testNestedDestructuring_block_25
  jmp testNestedDestructuring_block_39
testNestedDestructuring_block_25:
  jmp testNestedDestructuring_block_25
  movq [rel str_const_139], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $0, rax
  testq rax, rax
  jne testNestedDestructuring_block_29
  jmp testNestedDestructuring_block_39
testNestedDestructuring_block_29:
  jmp testNestedDestructuring_block_29
  movq $0, rcx
  call lm_list_len
  movq $r36, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne testNestedDestructuring_block_34
  jmp testNestedDestructuring_block_39
testNestedDestructuring_block_34:
  jmp testNestedDestructuring_block_34
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq $0, rcx
  movq $9, rdx
  call lm_list_get
  jmp testNestedDestructuring_block_40
testNestedDestructuring_block_39:
  movq $0, rax
  jmp testNestedDestructuring_epilogue
testNestedDestructuring_block_40:
  movq [rel str_const_140], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rel str_const_141], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq $0, rcx
  movq $9, rdx
  call lm_list_get
  movq [rel str_const_142], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  movq $r48, rdx
  call lm_rt_str_format
  movq rax, [rbp + -152]
  movq [rbp + -152], rcx
  movq $r50, rdx
  call lm_rt_str_format
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  jmp testNestedDestructuring_epilogue
testNestedDestructuring_block_54:
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq $0, rcx
  movq $9, rdx
  call lm_list_get
  movq [rel str_const_143], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -168], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -176]
  movq [rbp + -176], rcx
  movq $r20, rdx
  call lm_rt_str_format
  movq rax, [rbp + -184]
  movq [rbp + -184], rcx
  movq $r22, rdx
  call lm_rt_str_format
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  jmp testNestedDestructuring_epilogue
testNestedDestructuring_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_testNestedDestructuring:

.globl testTupleDestructuring
testTupleDestructuring:
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
testTupleDestructuring_entry:
testTupleDestructuring_block_0:
  jmp testTupleDestructuring_block_1
testTupleDestructuring_block_1:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne testTupleDestructuring_block_5
  jmp testTupleDestructuring_block_10
testTupleDestructuring_block_5:
  jmp testTupleDestructuring_block_5
  jmp testTupleDestructuring_block_34
testTupleDestructuring_block_10:
  movq $0, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne testTupleDestructuring_block_14
  jmp testTupleDestructuring_block_21
testTupleDestructuring_block_14:
  jmp testTupleDestructuring_block_14
  jmp testTupleDestructuring_block_22
testTupleDestructuring_block_21:
  movq $0, rax
  jmp testTupleDestructuring_epilogue
testTupleDestructuring_block_22:
  movq [rel str_const_144], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp testTupleDestructuring_epilogue
testTupleDestructuring_block_34:
  movq [rel str_const_145], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp testTupleDestructuring_epilogue
testTupleDestructuring_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_testTupleDestructuring:

.globl testListDestructuring
testListDestructuring:
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
testListDestructuring_entry:
testListDestructuring_block_0:
  jmp testListDestructuring_block_1
testListDestructuring_block_1:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne testListDestructuring_block_5
  jmp testListDestructuring_block_6
testListDestructuring_block_5:
  jmp testListDestructuring_block_5
  jmp testListDestructuring_block_63
testListDestructuring_block_6:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r5, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne testListDestructuring_block_10
  jmp testListDestructuring_block_13
testListDestructuring_block_10:
  jmp testListDestructuring_block_10
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  jmp testListDestructuring_block_58
testListDestructuring_block_13:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r14, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne testListDestructuring_block_17
  jmp testListDestructuring_block_22
testListDestructuring_block_17:
  jmp testListDestructuring_block_17
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  jmp testListDestructuring_block_49
testListDestructuring_block_22:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r28, rax
  cmpq $9, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne testListDestructuring_block_26
  jmp testListDestructuring_block_29
testListDestructuring_block_26:
  jmp testListDestructuring_block_26
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  jmp testListDestructuring_block_30
testListDestructuring_block_29:
  movq $0, rax
  jmp testListDestructuring_epilogue
testListDestructuring_block_30:
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq $0, rcx
  call lm_list_new
  movq [rbp + -64], rcx
  call lm_list_len
  jmp testListDestructuring_block_36
testListDestructuring_block_36:
  movq $9, rax
  cmpq $r36, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne testListDestructuring_block_38
  jmp testListDestructuring_block_44
testListDestructuring_block_38:
  jmp testListDestructuring_block_38
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  movq $r35, rcx
  movq $r39, rdx
  call lm_list_append
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp testListDestructuring_block_36
testListDestructuring_block_44:
  movq [rel str_const_146], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  movq $r34, rdx
  call lm_rt_str_format
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  movq $r35, rdx
  call lm_rt_str_format
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp testListDestructuring_epilogue
testListDestructuring_block_49:
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  movq [rel str_const_147], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  movq $r22, rdx
  call lm_rt_str_format
  movq rax, [rbp + -152]
  movq [rbp + -152], rcx
  movq $r24, rdx
  call lm_rt_str_format
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  jmp testListDestructuring_epilogue
testListDestructuring_block_58:
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  movq [rel str_const_148], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -168], rcx
  movq $r11, rdx
  call lm_rt_str_format
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  jmp testListDestructuring_epilogue
testListDestructuring_block_63:
  movq [rel str_const_149], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  jmp testListDestructuring_epilogue
testListDestructuring_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_testListDestructuring:

.globl testRecordDestructuring
testRecordDestructuring:
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
testRecordDestructuring_entry:
testRecordDestructuring_block_0:
  jmp testRecordDestructuring_block_1
testRecordDestructuring_block_1:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne testRecordDestructuring_block_5
  jmp testRecordDestructuring_block_14
testRecordDestructuring_block_5:
  jmp testRecordDestructuring_block_5
  movq [rel str_const_150], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq $0, rax
  testq rax, rax
  jne testRecordDestructuring_block_8
  jmp testRecordDestructuring_block_14
testRecordDestructuring_block_8:
  jmp testRecordDestructuring_block_8
  movq [rel str_const_151], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $0, rax
  testq rax, rax
  jne testRecordDestructuring_block_12
  jmp testRecordDestructuring_block_14
testRecordDestructuring_block_12:
  jmp testRecordDestructuring_block_12
  jmp testRecordDestructuring_block_44
testRecordDestructuring_block_14:
  movq $0, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne testRecordDestructuring_block_18
  jmp testRecordDestructuring_block_31
testRecordDestructuring_block_18:
  jmp testRecordDestructuring_block_18
  movq [rel str_const_152], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $0, rax
  testq rax, rax
  jne testRecordDestructuring_block_21
  jmp testRecordDestructuring_block_31
testRecordDestructuring_block_21:
  jmp testRecordDestructuring_block_21
  movq [rel str_const_153], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $0, rax
  testq rax, rax
  jne testRecordDestructuring_block_25
  jmp testRecordDestructuring_block_31
testRecordDestructuring_block_25:
  jmp testRecordDestructuring_block_25
  movq [rel str_const_154], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq $0, rax
  testq rax, rax
  jne testRecordDestructuring_block_29
  jmp testRecordDestructuring_block_31
testRecordDestructuring_block_29:
  jmp testRecordDestructuring_block_29
  jmp testRecordDestructuring_block_32
testRecordDestructuring_block_31:
  movq $0, rax
  jmp testRecordDestructuring_epilogue
testRecordDestructuring_block_32:
  movq [rel str_const_155], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rel str_const_156], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rel str_const_157], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rel str_const_158], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -152], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -160]
  movq [rbp + -160], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -168]
  movq [rbp + -168], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  jmp testRecordDestructuring_epilogue
testRecordDestructuring_block_44:
  movq [rel str_const_159], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rel str_const_160], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rel str_const_161], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -208]
  movq [rbp + -208], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  jmp testRecordDestructuring_epilogue
testRecordDestructuring_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_testRecordDestructuring:

.globl processCommand
processCommand:
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
  mov [rbp + -64], rcx
processCommand_entry:
processCommand_block_0:
  jmp processCommand_block_1
processCommand_block_1:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne processCommand_block_5
  jmp processCommand_block_11
processCommand_block_5:
  jmp processCommand_block_5
  jmp processCommand_block_57
processCommand_block_11:
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne processCommand_block_15
  jmp processCommand_block_21
processCommand_block_15:
  jmp processCommand_block_15
  jmp processCommand_block_47
processCommand_block_21:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne processCommand_block_25
  jmp processCommand_block_33
processCommand_block_25:
  jmp processCommand_block_25
  jmp processCommand_block_34
processCommand_block_33:
  movq $0, rax
  jmp processCommand_epilogue
processCommand_block_34:
  movq [rel str_const_162], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -112]
  movq [rbp + -112], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  jmp processCommand_epilogue
processCommand_block_47:
  movq [rel str_const_163], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -136]
  movq [rbp + -136], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  jmp processCommand_epilogue
processCommand_block_57:
  movq [rel str_const_164], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -152], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -160]
  movq [rbp + -160], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  jmp processCommand_epilogue
processCommand_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_processCommand:

.globl testComplexNested
testComplexNested:
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
  mov [rbp + -64], rcx
testComplexNested_entry:
testComplexNested_block_0:
  jmp testComplexNested_block_1
testComplexNested_block_1:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne testComplexNested_block_5
  jmp testComplexNested_block_30
testComplexNested_block_5:
  jmp testComplexNested_block_5
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne testComplexNested_block_13
  jmp testComplexNested_block_30
testComplexNested_block_13:
  jmp testComplexNested_block_13
  movq [rel str_const_165], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $0, rax
  testq rax, rax
  jne testComplexNested_block_16
  jmp testComplexNested_block_30
testComplexNested_block_16:
  jmp testComplexNested_block_16
  movq [rel str_const_166], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $0, rax
  testq rax, rax
  jne testComplexNested_block_20
  jmp testComplexNested_block_30
testComplexNested_block_20:
  jmp testComplexNested_block_20
  movq $0, rcx
  call lm_list_len
  movq $r17, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne testComplexNested_block_25
  jmp testComplexNested_block_30
testComplexNested_block_25:
  jmp testComplexNested_block_25
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq $0, rcx
  movq $9, rdx
  call lm_list_get
  jmp testComplexNested_block_31
testComplexNested_block_30:
  movq $0, rax
  jmp testComplexNested_epilogue
testComplexNested_block_31:
  movq [rel str_const_167], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rel str_const_168], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq $0, rcx
  movq $9, rdx
  call lm_list_get
  movq [rel str_const_169], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -136]
  movq [rbp + -136], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  movq $r33, rdx
  call lm_rt_str_format
  movq rax, [rbp + -152]
  movq [rbp + -152], rcx
  movq $r35, rdx
  call lm_rt_str_format
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  jmp testComplexNested_epilogue
testComplexNested_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_testComplexNested:

.globl testOptionalFields
testOptionalFields:
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
testOptionalFields_entry:
testOptionalFields_block_0:
  jmp testOptionalFields_block_1
testOptionalFields_block_1:
  movq $0, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne testOptionalFields_block_5
  jmp testOptionalFields_block_18
testOptionalFields_block_5:
  jmp testOptionalFields_block_5
  movq [rel str_const_170], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq $0, rax
  testq rax, rax
  jne testOptionalFields_block_8
  jmp testOptionalFields_block_18
testOptionalFields_block_8:
  jmp testOptionalFields_block_8
  movq [rel str_const_171], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $0, rax
  testq rax, rax
  jne testOptionalFields_block_12
  jmp testOptionalFields_block_18
testOptionalFields_block_12:
  jmp testOptionalFields_block_12
  movq [rel str_const_172], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $0, rax
  testq rax, rax
  jne testOptionalFields_block_16
  jmp testOptionalFields_block_18
testOptionalFields_block_16:
  jmp testOptionalFields_block_16
  jmp testOptionalFields_block_41
testOptionalFields_block_18:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne testOptionalFields_block_22
  jmp testOptionalFields_block_31
testOptionalFields_block_22:
  jmp testOptionalFields_block_22
  movq [rel str_const_173], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $0, rax
  testq rax, rax
  jne testOptionalFields_block_25
  jmp testOptionalFields_block_31
testOptionalFields_block_25:
  jmp testOptionalFields_block_25
  movq [rel str_const_174], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq $0, rax
  testq rax, rax
  jne testOptionalFields_block_29
  jmp testOptionalFields_block_31
testOptionalFields_block_29:
  jmp testOptionalFields_block_29
  jmp testOptionalFields_block_32
testOptionalFields_block_31:
  movq $0, rax
  jmp testOptionalFields_epilogue
testOptionalFields_block_32:
  movq [rel str_const_175], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rel str_const_176], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rel str_const_177], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -152]
  movq [rbp + -152], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  jmp testOptionalFields_epilogue
testOptionalFields_block_41:
  movq [rel str_const_178], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rel str_const_179], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rel str_const_180], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rel str_const_181], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -192], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -208]
  movq [rbp + -208], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  jmp testOptionalFields_epilogue
testOptionalFields_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_testOptionalFields:

.globl describeShape
describeShape:
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
describeShape_entry:
describeShape_block_0:
  jmp describeShape_block_1
describeShape_block_1:
  movq $0, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne describeShape_block_5
  jmp describeShape_block_7
describeShape_block_5:
  jmp describeShape_block_5
  jmp describeShape_block_48
describeShape_block_7:
  movq $0, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne describeShape_block_11
  jmp describeShape_block_17
describeShape_block_11:
  jmp describeShape_block_11
  jmp describeShape_block_38
describeShape_block_17:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne describeShape_block_21
  jmp describeShape_block_27
describeShape_block_21:
  jmp describeShape_block_21
  jmp describeShape_block_28
describeShape_block_27:
  movq $0, rax
  jmp describeShape_epilogue
describeShape_block_28:
  movq [rel str_const_182], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp describeShape_epilogue
describeShape_block_38:
  movq [rel str_const_183], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp describeShape_epilogue
describeShape_block_48:
  movq [rel str_const_184], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  jmp describeShape_epilogue
describeShape_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_describeShape:

.globl testNestedTupleList
testNestedTupleList:
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
testNestedTupleList_entry:
testNestedTupleList_block_0:
  jmp testNestedTupleList_block_1
testNestedTupleList_block_1:
  movq $0, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne testNestedTupleList_block_5
  jmp testNestedTupleList_block_20
testNestedTupleList_block_5:
  jmp testNestedTupleList_block_5
  movq $0, rcx
  call lm_list_len
  movq $r8, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne testNestedTupleList_block_13
  jmp testNestedTupleList_block_20
testNestedTupleList_block_13:
  jmp testNestedTupleList_block_13
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq $0, rcx
  movq $9, rdx
  call lm_list_get
  movq $0, rcx
  movq $17, rdx
  call lm_list_get
  jmp testNestedTupleList_block_21
testNestedTupleList_block_20:
  movq $0, rax
  jmp testNestedTupleList_epilogue
testNestedTupleList_block_21:
  movq $0, rcx
  movq $1, rdx
  call lm_list_get
  movq $0, rcx
  movq $9, rdx
  call lm_list_get
  movq $0, rcx
  movq $17, rdx
  call lm_list_get
  movq [rel str_const_185], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  movq $0, rdx
  call lm_rt_str_format
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  movq $r22, rdx
  call lm_rt_str_format
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  movq $r24, rdx
  call lm_rt_str_format
  movq rax, [rbp + -112]
  movq [rbp + -112], rcx
  movq $r26, rdx
  call lm_rt_str_format
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  jmp testNestedTupleList_epilogue
testNestedTupleList_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_testNestedTupleList:

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

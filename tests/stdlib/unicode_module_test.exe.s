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
  .string "A"
.align 8
str_const_3:
  .string "a"
.align 8
str_const_4:
  .string "B"
.align 8
str_const_5:
  .string "b"
.align 8
str_const_6:
  .string "C"
.align 8
str_const_7:
  .string "c"
.align 8
str_const_8:
  .string "D"
.align 8
str_const_9:
  .string "d"
.align 8
str_const_10:
  .string "E"
.align 8
str_const_11:
  .string "e"
.align 8
str_const_12:
  .string "F"
.align 8
str_const_13:
  .string "f"
.align 8
str_const_14:
  .string "G"
.align 8
str_const_15:
  .string "g"
.align 8
str_const_16:
  .string "H"
.align 8
str_const_17:
  .string "h"
.align 8
str_const_18:
  .string "I"
.align 8
str_const_19:
  .string "i"
.align 8
str_const_20:
  .string "J"
.align 8
str_const_21:
  .string "j"
.align 8
str_const_22:
  .string "K"
.align 8
str_const_23:
  .string "k"
.align 8
str_const_24:
  .string "L"
.align 8
str_const_25:
  .string "l"
.align 8
str_const_26:
  .string "M"
.align 8
str_const_27:
  .string "m"
.align 8
str_const_28:
  .string "N"
.align 8
str_const_29:
  .string "n"
.align 8
str_const_30:
  .string "O"
.align 8
str_const_31:
  .string "o"
.align 8
str_const_32:
  .string "P"
.align 8
str_const_33:
  .string "p"
.align 8
str_const_34:
  .string "Q"
.align 8
str_const_35:
  .string "q"
.align 8
str_const_36:
  .string "R"
.align 8
str_const_37:
  .string "r"
.align 8
str_const_38:
  .string "S"
.align 8
str_const_39:
  .string "s"
.align 8
str_const_40:
  .string "T"
.align 8
str_const_41:
  .string "t"
.align 8
str_const_42:
  .string "U"
.align 8
str_const_43:
  .string "u"
.align 8
str_const_44:
  .string "V"
.align 8
str_const_45:
  .string "v"
.align 8
str_const_46:
  .string "W"
.align 8
str_const_47:
  .string "w"
.align 8
str_const_48:
  .string "X"
.align 8
str_const_49:
  .string "x"
.align 8
str_const_50:
  .string "Y"
.align 8
str_const_51:
  .string "y"
.align 8
str_const_52:
  .string "Z"
.align 8
str_const_53:
  .string "z"
.align 8
str_const_54:
  .string "a"
.align 8
str_const_55:
  .string "A"
.align 8
str_const_56:
  .string "b"
.align 8
str_const_57:
  .string "B"
.align 8
str_const_58:
  .string "c"
.align 8
str_const_59:
  .string "C"
.align 8
str_const_60:
  .string "d"
.align 8
str_const_61:
  .string "D"
.align 8
str_const_62:
  .string "e"
.align 8
str_const_63:
  .string "E"
.align 8
str_const_64:
  .string "f"
.align 8
str_const_65:
  .string "F"
.align 8
str_const_66:
  .string "g"
.align 8
str_const_67:
  .string "G"
.align 8
str_const_68:
  .string "h"
.align 8
str_const_69:
  .string "H"
.align 8
str_const_70:
  .string "i"
.align 8
str_const_71:
  .string "I"
.align 8
str_const_72:
  .string "j"
.align 8
str_const_73:
  .string "J"
.align 8
str_const_74:
  .string "k"
.align 8
str_const_75:
  .string "K"
.align 8
str_const_76:
  .string "l"
.align 8
str_const_77:
  .string "L"
.align 8
str_const_78:
  .string "m"
.align 8
str_const_79:
  .string "M"
.align 8
str_const_80:
  .string "n"
.align 8
str_const_81:
  .string "N"
.align 8
str_const_82:
  .string "o"
.align 8
str_const_83:
  .string "O"
.align 8
str_const_84:
  .string "p"
.align 8
str_const_85:
  .string "P"
.align 8
str_const_86:
  .string "q"
.align 8
str_const_87:
  .string "Q"
.align 8
str_const_88:
  .string "r"
.align 8
str_const_89:
  .string "R"
.align 8
str_const_90:
  .string "s"
.align 8
str_const_91:
  .string "S"
.align 8
str_const_92:
  .string "t"
.align 8
str_const_93:
  .string "T"
.align 8
str_const_94:
  .string "u"
.align 8
str_const_95:
  .string "U"
.align 8
str_const_96:
  .string "v"
.align 8
str_const_97:
  .string "V"
.align 8
str_const_98:
  .string "w"
.align 8
str_const_99:
  .string "W"
.align 8
str_const_100:
  .string "x"
.align 8
str_const_101:
  .string "X"
.align 8
str_const_102:
  .string "y"
.align 8
str_const_103:
  .string "Y"
.align 8
str_const_104:
  .string "z"
.align 8
str_const_105:
  .string "Z"
.align 8
str_const_106:
  .string "Testing Rune..."
.align 8
str_const_107:
  .string "a"
.align 8
str_const_108:
  .string "b"
.align 8
str_const_109:
  .string "a"
.align 8
str_const_110:
  .string "a"
.align 8
str_const_111:
  .string "Rune to_string failed"
.align 8
str_const_112:
  .string "Rune compare less failed"
.align 8
str_const_113:
  .string "Rune compare greater failed"
.align 8
str_const_114:
  .string "Rune compare equal failed"
.align 8
str_const_115:
  .string "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
.align 8
str_const_116:
  .string " "
.align 8
str_const_117:
  .string "	"
.align 8
str_const_118:
  .string "
"
.align 8
str_const_119:
  .string ""
.align 8
str_const_120:
  .string "Testing Categories..."
.align 8
str_const_121:
  .string "A"
.align 8
str_const_122:
  .string "is_upper A failed"
.align 8
str_const_123:
  .string "a"
.align 8
str_const_124:
  .string "is_upper a failed"
.align 8
str_const_125:
  .string "a"
.align 8
str_const_126:
  .string "is_lower a failed"
.align 8
str_const_127:
  .string "A"
.align 8
str_const_128:
  .string "is_lower A failed"
.align 8
str_const_129:
  .string "5"
.align 8
str_const_130:
  .string "is_digit 5 failed"
.align 8
str_const_131:
  .string "a"
.align 8
str_const_132:
  .string "is_digit a failed"
.align 8
str_const_133:
  .string "a"
.align 8
str_const_134:
  .string "is_alpha a failed"
.align 8
str_const_135:
  .string "5"
.align 8
str_const_136:
  .string "is_alpha 5 failed"
.align 8
str_const_137:
  .string "a"
.align 8
str_const_138:
  .string "is_alphanumeric a failed"
.align 8
str_const_139:
  .string "5"
.align 8
str_const_140:
  .string "is_alphanumeric 5 failed"
.align 8
str_const_141:
  .string "!"
.align 8
str_const_142:
  .string "is_alphanumeric ! failed"
.align 8
str_const_143:
  .string " "
.align 8
str_const_144:
  .string "is_whitespace space failed"
.align 8
str_const_145:
  .string "
"
.align 8
str_const_146:
  .string "is_whitespace newline failed"
.align 8
str_const_147:
  .string "a"
.align 8
str_const_148:
  .string "is_whitespace a failed"
.align 8
str_const_149:
  .string "Testing Normalize..."
.align 8
str_const_150:
  .string "hello"
.align 8
str_const_151:
  .string "HELLO"
.align 8
str_const_152:
  .string "to_upper failed"
.align 8
str_const_153:
  .string "WORLD"
.align 8
str_const_154:
  .string "world"
.align 8
str_const_155:
  .string "to_lower failed"
.align 8
str_const_156:
  .string " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
.align 8
str_const_157:
  .string "=== Unicode Module Test Suite ==="
.align 8
str_const_158:
  .string "Rune test failed"
.align 8
str_const_159:
  .string "Categories test failed"
.align 8
str_const_160:
  .string "Normalize test failed"
.align 8
str_const_161:
  .string "All unicode tests passed successfully."
.align 8
str_const_162:
  .string "abcdefghijklmnopqrstuvwxyz"
.align 8
str_const_163:
  .string "123456789"
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
  call std.unicode.index.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq [rel str_const_157], rcx
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
  call test_rune
  movq $r2, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_158], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_categories
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_159], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  call test_normalize
  movq $r12, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_160], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rel str_const_161], rcx
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

.globl std.unicode.normalize.__init__
std.unicode.normalize.__init__:
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
std.unicode.normalize.__init___entry:
  movq $0, rax
  jmp std.unicode.normalize.__init___epilogue
std.unicode.normalize.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.normalize.__init__:

.globl std.unicode.normalize.to_upper
std.unicode.normalize.to_upper:
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
std.unicode.normalize.to_upper_entry:
std.unicode.normalize.to_upper_block_0:
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.unicode.normalize.to_upper_block_5
std.unicode.normalize.to_upper_block_5:
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.unicode.normalize.to_upper_block_7
  jmp std.unicode.normalize.to_upper_block_20
std.unicode.normalize.to_upper_block_7:
  jmp std.unicode.normalize.to_upper_block_7
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -88], r8
  call substring
  movq $r10, rcx
  call std.unicode.normalize._char_to_upper
  movq $r11, rcx
  call lm_to_string
  movq rax, [rbp + -96]
  movq [rbp + -72], rcx
  movq [rbp + -96], rdx
  call lm_str_concat
  movq rax, [rbp + -104]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.unicode.normalize.to_upper_block_5
std.unicode.normalize.to_upper_block_20:
  movq [rbp + -104], rax
  jmp std.unicode.normalize.to_upper_epilogue
std.unicode.normalize.to_upper_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.normalize.to_upper:

.globl std.unicode.normalize.to_lower
std.unicode.normalize.to_lower:
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
std.unicode.normalize.to_lower_entry:
std.unicode.normalize.to_lower_block_0:
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.unicode.normalize.to_lower_block_5
std.unicode.normalize.to_lower_block_5:
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.unicode.normalize.to_lower_block_7
  jmp std.unicode.normalize.to_lower_block_20
std.unicode.normalize.to_lower_block_7:
  jmp std.unicode.normalize.to_lower_block_7
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -88], r8
  call substring
  movq $r10, rcx
  call std.unicode.normalize._char_to_lower
  movq $r11, rcx
  call lm_to_string
  movq rax, [rbp + -96]
  movq [rbp + -72], rcx
  movq [rbp + -96], rdx
  call lm_str_concat
  movq rax, [rbp + -104]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.unicode.normalize.to_lower_block_5
std.unicode.normalize.to_lower_block_20:
  movq [rbp + -104], rax
  jmp std.unicode.normalize.to_lower_epilogue
std.unicode.normalize.to_lower_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.normalize.to_lower:

.globl std.unicode.normalize._char_to_lower
std.unicode.normalize._char_to_lower:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 680
  mov [rbp + -64], rcx
std.unicode.normalize._char_to_lower_entry:
std.unicode.normalize._char_to_lower_block_0:
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_3
  jmp std.unicode.normalize._char_to_lower_block_5
std.unicode.normalize._char_to_lower_block_3:
  jmp std.unicode.normalize._char_to_lower_block_3
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_5:
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -64], rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_8
  jmp std.unicode.normalize._char_to_lower_block_10
std.unicode.normalize._char_to_lower_block_8:
  jmp std.unicode.normalize._char_to_lower_block_8
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_10:
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -64], rax
  cmpq [rbp + -120], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_13
  jmp std.unicode.normalize._char_to_lower_block_15
std.unicode.normalize._char_to_lower_block_13:
  jmp std.unicode.normalize._char_to_lower_block_13
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_15:
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -64], rax
  cmpq [rbp + -144], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_18
  jmp std.unicode.normalize._char_to_lower_block_20
std.unicode.normalize._char_to_lower_block_18:
  jmp std.unicode.normalize._char_to_lower_block_18
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_20:
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -64], rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_23
  jmp std.unicode.normalize._char_to_lower_block_25
std.unicode.normalize._char_to_lower_block_23:
  jmp std.unicode.normalize._char_to_lower_block_23
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_25:
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -64], rax
  cmpq [rbp + -192], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_28
  jmp std.unicode.normalize._char_to_lower_block_30
std.unicode.normalize._char_to_lower_block_28:
  jmp std.unicode.normalize._char_to_lower_block_28
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_30:
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -64], rax
  cmpq [rbp + -216], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_33
  jmp std.unicode.normalize._char_to_lower_block_35
std.unicode.normalize._char_to_lower_block_33:
  jmp std.unicode.normalize._char_to_lower_block_33
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_35:
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -64], rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_38
  jmp std.unicode.normalize._char_to_lower_block_40
std.unicode.normalize._char_to_lower_block_38:
  jmp std.unicode.normalize._char_to_lower_block_38
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_40:
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -64], rax
  cmpq [rbp + -264], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_43
  jmp std.unicode.normalize._char_to_lower_block_45
std.unicode.normalize._char_to_lower_block_43:
  jmp std.unicode.normalize._char_to_lower_block_43
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_45:
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -64], rax
  cmpq [rbp + -288], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_48
  jmp std.unicode.normalize._char_to_lower_block_50
std.unicode.normalize._char_to_lower_block_48:
  jmp std.unicode.normalize._char_to_lower_block_48
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_50:
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -64], rax
  cmpq [rbp + -312], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_53
  jmp std.unicode.normalize._char_to_lower_block_55
std.unicode.normalize._char_to_lower_block_53:
  jmp std.unicode.normalize._char_to_lower_block_53
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_55:
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -64], rax
  cmpq [rbp + -336], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_58
  jmp std.unicode.normalize._char_to_lower_block_60
std.unicode.normalize._char_to_lower_block_58:
  jmp std.unicode.normalize._char_to_lower_block_58
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_60:
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -64], rax
  cmpq [rbp + -360], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -368]
  movq [rbp + -368], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_63
  jmp std.unicode.normalize._char_to_lower_block_65
std.unicode.normalize._char_to_lower_block_63:
  jmp std.unicode.normalize._char_to_lower_block_63
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_65:
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -64], rax
  cmpq [rbp + -384], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_68
  jmp std.unicode.normalize._char_to_lower_block_70
std.unicode.normalize._char_to_lower_block_68:
  jmp std.unicode.normalize._char_to_lower_block_68
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_70:
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -64], rax
  cmpq [rbp + -408], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -416]
  movq [rbp + -416], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_73
  jmp std.unicode.normalize._char_to_lower_block_75
std.unicode.normalize._char_to_lower_block_73:
  jmp std.unicode.normalize._char_to_lower_block_73
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_75:
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rbp + -64], rax
  cmpq [rbp + -432], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_78
  jmp std.unicode.normalize._char_to_lower_block_80
std.unicode.normalize._char_to_lower_block_78:
  jmp std.unicode.normalize._char_to_lower_block_78
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -448], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_80:
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq [rbp + -64], rax
  cmpq [rbp + -456], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -464]
  movq [rbp + -464], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_83
  jmp std.unicode.normalize._char_to_lower_block_85
std.unicode.normalize._char_to_lower_block_83:
  jmp std.unicode.normalize._char_to_lower_block_83
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -472], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_85:
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq [rbp + -64], rax
  cmpq [rbp + -480], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -488]
  movq [rbp + -488], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_88
  jmp std.unicode.normalize._char_to_lower_block_90
std.unicode.normalize._char_to_lower_block_88:
  jmp std.unicode.normalize._char_to_lower_block_88
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -496], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_90:
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -64], rax
  cmpq [rbp + -504], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -512]
  movq [rbp + -512], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_93
  jmp std.unicode.normalize._char_to_lower_block_95
std.unicode.normalize._char_to_lower_block_93:
  jmp std.unicode.normalize._char_to_lower_block_93
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -520], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_95:
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -64], rax
  cmpq [rbp + -528], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -536]
  movq [rbp + -536], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_98
  jmp std.unicode.normalize._char_to_lower_block_100
std.unicode.normalize._char_to_lower_block_98:
  jmp std.unicode.normalize._char_to_lower_block_98
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -544]
  movq [rbp + -544], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_100:
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -552]
  movq [rbp + -64], rax
  cmpq [rbp + -552], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -560]
  movq [rbp + -560], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_103
  jmp std.unicode.normalize._char_to_lower_block_105
std.unicode.normalize._char_to_lower_block_103:
  jmp std.unicode.normalize._char_to_lower_block_103
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -568]
  movq [rbp + -568], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_105:
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -64], rax
  cmpq [rbp + -576], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -584]
  movq [rbp + -584], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_108
  jmp std.unicode.normalize._char_to_lower_block_110
std.unicode.normalize._char_to_lower_block_108:
  jmp std.unicode.normalize._char_to_lower_block_108
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -592]
  movq [rbp + -592], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_110:
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -600]
  movq [rbp + -64], rax
  cmpq [rbp + -600], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -608]
  movq [rbp + -608], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_113
  jmp std.unicode.normalize._char_to_lower_block_115
std.unicode.normalize._char_to_lower_block_113:
  jmp std.unicode.normalize._char_to_lower_block_113
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -616], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_115:
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rbp + -64], rax
  cmpq [rbp + -624], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -632]
  movq [rbp + -632], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_118
  jmp std.unicode.normalize._char_to_lower_block_120
std.unicode.normalize._char_to_lower_block_118:
  jmp std.unicode.normalize._char_to_lower_block_118
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_120:
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -648]
  movq [rbp + -64], rax
  cmpq [rbp + -648], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -656]
  movq [rbp + -656], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_123
  jmp std.unicode.normalize._char_to_lower_block_125
std.unicode.normalize._char_to_lower_block_123:
  jmp std.unicode.normalize._char_to_lower_block_123
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -664]
  movq [rbp + -664], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_125:
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -672]
  movq [rbp + -64], rax
  cmpq [rbp + -672], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -680]
  movq [rbp + -680], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_lower_block_128
  jmp std.unicode.normalize._char_to_lower_block_130
std.unicode.normalize._char_to_lower_block_128:
  jmp std.unicode.normalize._char_to_lower_block_128
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -688]
  movq [rbp + -688], rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_block_130:
  movq $0, rax
  jmp std.unicode.normalize._char_to_lower_epilogue
std.unicode.normalize._char_to_lower_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.normalize._char_to_lower:

.globl std.unicode.index.__init__
std.unicode.index.__init__:
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
std.unicode.index.__init___entry:
  movq $0, rax
  jmp std.unicode.index.__init___epilogue
std.unicode.index.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.index.__init__:

.globl std.unicode.index.to_lower
std.unicode.index.to_lower:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.unicode.index.to_lower_entry:
std.unicode.index.to_lower_block_0:
  movq [rbp + -64], rcx
  call std.unicode.normalize.to_lower
  movq $r1, rax
  jmp std.unicode.index.to_lower_epilogue
std.unicode.index.to_lower_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.index.to_lower:

.globl std.unicode.index.to_upper
std.unicode.index.to_upper:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.unicode.index.to_upper_entry:
std.unicode.index.to_upper_block_0:
  movq [rbp + -64], rcx
  call std.unicode.normalize.to_upper
  movq $r1, rax
  jmp std.unicode.index.to_upper_epilogue
std.unicode.index.to_upper_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.index.to_upper:

.globl std.unicode.index.is_whitespace
std.unicode.index.is_whitespace:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.unicode.index.is_whitespace_entry:
std.unicode.index.is_whitespace_block_0:
  movq [rbp + -64], rcx
  call std.unicode.category.is_whitespace
  movq $r1, rax
  jmp std.unicode.index.is_whitespace_epilogue
std.unicode.index.is_whitespace_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.index.is_whitespace:

.globl std.unicode.index.is_digit
std.unicode.index.is_digit:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.unicode.index.is_digit_entry:
std.unicode.index.is_digit_block_0:
  movq [rbp + -64], rcx
  call std.unicode.category.is_digit
  movq $r1, rax
  jmp std.unicode.index.is_digit_epilogue
std.unicode.index.is_digit_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.index.is_digit:

.globl std.unicode.index.is_lower
std.unicode.index.is_lower:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.unicode.index.is_lower_entry:
std.unicode.index.is_lower_block_0:
  movq [rbp + -64], rcx
  call std.unicode.category.is_lower
  movq $r1, rax
  jmp std.unicode.index.is_lower_epilogue
std.unicode.index.is_lower_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.index.is_lower:

.globl std.unicode.index.is_upper
std.unicode.index.is_upper:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.unicode.index.is_upper_entry:
std.unicode.index.is_upper_block_0:
  movq [rbp + -64], rcx
  call std.unicode.category.is_upper
  movq $r1, rax
  jmp std.unicode.index.is_upper_epilogue
std.unicode.index.is_upper_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.index.is_upper:

.globl std.unicode.index.Rune
std.unicode.index.Rune:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.unicode.index.Rune_entry:
std.unicode.index.Rune_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.unicode.rune.Rune.init
  movq [rbp + -72], rax
  jmp std.unicode.index.Rune_epilogue
std.unicode.index.Rune_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.index.Rune:

.globl std.unicode.index.is_alphanumeric
std.unicode.index.is_alphanumeric:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.unicode.index.is_alphanumeric_entry:
std.unicode.index.is_alphanumeric_block_0:
  movq [rbp + -64], rcx
  call std.unicode.category.is_alphanumeric
  movq $r1, rax
  jmp std.unicode.index.is_alphanumeric_epilogue
std.unicode.index.is_alphanumeric_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.index.is_alphanumeric:

.globl std.unicode.normalize._char_to_upper
std.unicode.normalize._char_to_upper:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 680
  mov [rbp + -64], rcx
std.unicode.normalize._char_to_upper_entry:
std.unicode.normalize._char_to_upper_block_0:
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_3
  jmp std.unicode.normalize._char_to_upper_block_5
std.unicode.normalize._char_to_upper_block_3:
  jmp std.unicode.normalize._char_to_upper_block_3
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_5:
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -64], rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_8
  jmp std.unicode.normalize._char_to_upper_block_10
std.unicode.normalize._char_to_upper_block_8:
  jmp std.unicode.normalize._char_to_upper_block_8
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_10:
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -64], rax
  cmpq [rbp + -120], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_13
  jmp std.unicode.normalize._char_to_upper_block_15
std.unicode.normalize._char_to_upper_block_13:
  jmp std.unicode.normalize._char_to_upper_block_13
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_15:
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -64], rax
  cmpq [rbp + -144], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_18
  jmp std.unicode.normalize._char_to_upper_block_20
std.unicode.normalize._char_to_upper_block_18:
  jmp std.unicode.normalize._char_to_upper_block_18
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_20:
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -64], rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_23
  jmp std.unicode.normalize._char_to_upper_block_25
std.unicode.normalize._char_to_upper_block_23:
  jmp std.unicode.normalize._char_to_upper_block_23
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_25:
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -64], rax
  cmpq [rbp + -192], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_28
  jmp std.unicode.normalize._char_to_upper_block_30
std.unicode.normalize._char_to_upper_block_28:
  jmp std.unicode.normalize._char_to_upper_block_28
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_30:
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -64], rax
  cmpq [rbp + -216], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_33
  jmp std.unicode.normalize._char_to_upper_block_35
std.unicode.normalize._char_to_upper_block_33:
  jmp std.unicode.normalize._char_to_upper_block_33
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_35:
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -64], rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_38
  jmp std.unicode.normalize._char_to_upper_block_40
std.unicode.normalize._char_to_upper_block_38:
  jmp std.unicode.normalize._char_to_upper_block_38
  movq [rel str_const_69], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_40:
  movq [rel str_const_70], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -64], rax
  cmpq [rbp + -264], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_43
  jmp std.unicode.normalize._char_to_upper_block_45
std.unicode.normalize._char_to_upper_block_43:
  jmp std.unicode.normalize._char_to_upper_block_43
  movq [rel str_const_71], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_45:
  movq [rel str_const_72], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -64], rax
  cmpq [rbp + -288], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_48
  jmp std.unicode.normalize._char_to_upper_block_50
std.unicode.normalize._char_to_upper_block_48:
  jmp std.unicode.normalize._char_to_upper_block_48
  movq [rel str_const_73], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_50:
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -64], rax
  cmpq [rbp + -312], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_53
  jmp std.unicode.normalize._char_to_upper_block_55
std.unicode.normalize._char_to_upper_block_53:
  jmp std.unicode.normalize._char_to_upper_block_53
  movq [rel str_const_75], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_55:
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -64], rax
  cmpq [rbp + -336], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_58
  jmp std.unicode.normalize._char_to_upper_block_60
std.unicode.normalize._char_to_upper_block_58:
  jmp std.unicode.normalize._char_to_upper_block_58
  movq [rel str_const_77], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_60:
  movq [rel str_const_78], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -64], rax
  cmpq [rbp + -360], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -368]
  movq [rbp + -368], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_63
  jmp std.unicode.normalize._char_to_upper_block_65
std.unicode.normalize._char_to_upper_block_63:
  jmp std.unicode.normalize._char_to_upper_block_63
  movq [rel str_const_79], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_65:
  movq [rel str_const_80], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -64], rax
  cmpq [rbp + -384], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_68
  jmp std.unicode.normalize._char_to_upper_block_70
std.unicode.normalize._char_to_upper_block_68:
  jmp std.unicode.normalize._char_to_upper_block_68
  movq [rel str_const_81], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_70:
  movq [rel str_const_82], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -64], rax
  cmpq [rbp + -408], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -416]
  movq [rbp + -416], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_73
  jmp std.unicode.normalize._char_to_upper_block_75
std.unicode.normalize._char_to_upper_block_73:
  jmp std.unicode.normalize._char_to_upper_block_73
  movq [rel str_const_83], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_75:
  movq [rel str_const_84], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rbp + -64], rax
  cmpq [rbp + -432], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_78
  jmp std.unicode.normalize._char_to_upper_block_80
std.unicode.normalize._char_to_upper_block_78:
  jmp std.unicode.normalize._char_to_upper_block_78
  movq [rel str_const_85], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -448], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_80:
  movq [rel str_const_86], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq [rbp + -64], rax
  cmpq [rbp + -456], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -464]
  movq [rbp + -464], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_83
  jmp std.unicode.normalize._char_to_upper_block_85
std.unicode.normalize._char_to_upper_block_83:
  jmp std.unicode.normalize._char_to_upper_block_83
  movq [rel str_const_87], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -472], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_85:
  movq [rel str_const_88], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq [rbp + -64], rax
  cmpq [rbp + -480], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -488]
  movq [rbp + -488], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_88
  jmp std.unicode.normalize._char_to_upper_block_90
std.unicode.normalize._char_to_upper_block_88:
  jmp std.unicode.normalize._char_to_upper_block_88
  movq [rel str_const_89], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -496], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_90:
  movq [rel str_const_90], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -64], rax
  cmpq [rbp + -504], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -512]
  movq [rbp + -512], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_93
  jmp std.unicode.normalize._char_to_upper_block_95
std.unicode.normalize._char_to_upper_block_93:
  jmp std.unicode.normalize._char_to_upper_block_93
  movq [rel str_const_91], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -520], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_95:
  movq [rel str_const_92], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -64], rax
  cmpq [rbp + -528], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -536]
  movq [rbp + -536], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_98
  jmp std.unicode.normalize._char_to_upper_block_100
std.unicode.normalize._char_to_upper_block_98:
  jmp std.unicode.normalize._char_to_upper_block_98
  movq [rel str_const_93], rcx
  call lm_box_string
  movq rax, [rbp + -544]
  movq [rbp + -544], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_100:
  movq [rel str_const_94], rcx
  call lm_box_string
  movq rax, [rbp + -552]
  movq [rbp + -64], rax
  cmpq [rbp + -552], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -560]
  movq [rbp + -560], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_103
  jmp std.unicode.normalize._char_to_upper_block_105
std.unicode.normalize._char_to_upper_block_103:
  jmp std.unicode.normalize._char_to_upper_block_103
  movq [rel str_const_95], rcx
  call lm_box_string
  movq rax, [rbp + -568]
  movq [rbp + -568], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_105:
  movq [rel str_const_96], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -64], rax
  cmpq [rbp + -576], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -584]
  movq [rbp + -584], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_108
  jmp std.unicode.normalize._char_to_upper_block_110
std.unicode.normalize._char_to_upper_block_108:
  jmp std.unicode.normalize._char_to_upper_block_108
  movq [rel str_const_97], rcx
  call lm_box_string
  movq rax, [rbp + -592]
  movq [rbp + -592], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_110:
  movq [rel str_const_98], rcx
  call lm_box_string
  movq rax, [rbp + -600]
  movq [rbp + -64], rax
  cmpq [rbp + -600], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -608]
  movq [rbp + -608], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_113
  jmp std.unicode.normalize._char_to_upper_block_115
std.unicode.normalize._char_to_upper_block_113:
  jmp std.unicode.normalize._char_to_upper_block_113
  movq [rel str_const_99], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -616], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_115:
  movq [rel str_const_100], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rbp + -64], rax
  cmpq [rbp + -624], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -632]
  movq [rbp + -632], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_118
  jmp std.unicode.normalize._char_to_upper_block_120
std.unicode.normalize._char_to_upper_block_118:
  jmp std.unicode.normalize._char_to_upper_block_118
  movq [rel str_const_101], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_120:
  movq [rel str_const_102], rcx
  call lm_box_string
  movq rax, [rbp + -648]
  movq [rbp + -64], rax
  cmpq [rbp + -648], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -656]
  movq [rbp + -656], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_123
  jmp std.unicode.normalize._char_to_upper_block_125
std.unicode.normalize._char_to_upper_block_123:
  jmp std.unicode.normalize._char_to_upper_block_123
  movq [rel str_const_103], rcx
  call lm_box_string
  movq rax, [rbp + -664]
  movq [rbp + -664], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_125:
  movq [rel str_const_104], rcx
  call lm_box_string
  movq rax, [rbp + -672]
  movq [rbp + -64], rax
  cmpq [rbp + -672], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -680]
  movq [rbp + -680], rax
  testq rax, rax
  jne std.unicode.normalize._char_to_upper_block_128
  jmp std.unicode.normalize._char_to_upper_block_130
std.unicode.normalize._char_to_upper_block_128:
  jmp std.unicode.normalize._char_to_upper_block_128
  movq [rel str_const_105], rcx
  call lm_box_string
  movq rax, [rbp + -688]
  movq [rbp + -688], rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_block_130:
  movq $0, rax
  jmp std.unicode.normalize._char_to_upper_epilogue
std.unicode.normalize._char_to_upper_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.normalize._char_to_upper:

.globl std.unicode.rune.Rune.init
std.unicode.rune.Rune.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.unicode.rune.Rune.init_entry:
  movq $0, rax
  jmp std.unicode.rune.Rune.init_epilogue
std.unicode.rune.Rune.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.rune.Rune.init:

.globl test_rune
test_rune:
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
test_rune_entry:
test_rune_block_0:
  movq [rel str_const_106], rcx
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
  movq [rel str_const_107], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.unicode.index.Rune
  movq $r3, rax
  movq rax, [rbp + -104]
  movq [rel str_const_108], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -112], rcx
  call std.unicode.index.Rune
  movq $r7, rax
  movq rax, [rbp + -120]
  movq [rel str_const_109], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  call std.unicode.index.Rune
  movq $r11, rax
  movq rax, [rbp + -136]
  movq [rbp + -104], rcx
  call std.unicode.rune.Rune.to_string
  movq [rel str_const_110], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq $r14, rax
  cmpq [rbp + -144], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_111], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq [rbp + -104], rcx
  movq [rbp + -120], rdx
  call std.unicode.rune.Rune.compare
  movq $9, rax
  negq rax
  movq rax, [rbp + -168]
  movq $r19, rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_112], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq [rbp + -120], rcx
  movq [rbp + -104], rdx
  call std.unicode.rune.Rune.compare
  movq $r25, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_113], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq [rbp + -104], rcx
  movq [rbp + -136], rdx
  call std.unicode.rune.Rune.compare
  movq $r30, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_114], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq $9, rax
  jmp test_rune_epilogue
test_rune_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_rune:

.globl std.unicode.category.is_upper
std.unicode.category.is_upper:
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
std.unicode.category.is_upper_entry:
std.unicode.category.is_upper_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.unicode.category.is_upper_block_4
  jmp std.unicode.category.is_upper_block_6
std.unicode.category.is_upper_block_4:
  jmp std.unicode.category.is_upper_block_4
  movq $10, rax
  jmp std.unicode.category.is_upper_epilogue
std.unicode.category.is_upper_block_6:
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $9, r8
  call substring
  movq [rel str_const_115], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  jmp std.unicode.category.is_upper_block_12
std.unicode.category.is_upper_block_12:
  jmp std.unicode.category.is_upper_block_14
std.unicode.category.is_upper_block_14:
  movq [rbp + -80], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r13, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.unicode.category.is_upper_block_17
  jmp std.unicode.category.is_upper_block_31
std.unicode.category.is_upper_block_17:
  jmp std.unicode.category.is_upper_block_17
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  movq [rbp + -80], rcx
  movq $1, rdx
  movq [rbp + -96], r8
  call substring
  movq $r18, rax
  cmpq $r8, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.unicode.category.is_upper_block_23
  jmp std.unicode.category.is_upper_block_25
std.unicode.category.is_upper_block_23:
  jmp std.unicode.category.is_upper_block_23
  movq $18, rax
  jmp std.unicode.category.is_upper_epilogue
std.unicode.category.is_upper_block_25:
  jmp std.unicode.category.is_upper_block_26
std.unicode.category.is_upper_block_26:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.unicode.category.is_upper_block_14
std.unicode.category.is_upper_block_31:
  movq $10, rax
  jmp std.unicode.category.is_upper_epilogue
std.unicode.category.is_upper_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.category.is_upper:

.globl std.unicode.category.is_whitespace
std.unicode.category.is_whitespace:
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
std.unicode.category.is_whitespace_entry:
std.unicode.category.is_whitespace_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.unicode.category.is_whitespace_block_4
  jmp std.unicode.category.is_whitespace_block_6
std.unicode.category.is_whitespace_block_4:
  jmp std.unicode.category.is_whitespace_block_4
  movq $10, rax
  jmp std.unicode.category.is_whitespace_epilogue
std.unicode.category.is_whitespace_block_6:
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $9, r8
  call substring
  movq [rel str_const_116], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq $r8, rax
  cmpq [rbp + -80], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.unicode.category.is_whitespace_block_18
  jmp std.unicode.category.is_whitespace_block_14
std.unicode.category.is_whitespace_block_14:
  jmp std.unicode.category.is_whitespace_block_14
  movq [rel str_const_117], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r8, rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  jmp std.unicode.category.is_whitespace_block_18
std.unicode.category.is_whitespace_block_18:
  movq [rbp + -104], rax
  testq rax, rax
  jne std.unicode.category.is_whitespace_block_24
  jmp std.unicode.category.is_whitespace_block_20
std.unicode.category.is_whitespace_block_20:
  jmp std.unicode.category.is_whitespace_block_20
  movq [rel str_const_118], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r8, rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  jmp std.unicode.category.is_whitespace_block_24
std.unicode.category.is_whitespace_block_24:
  movq [rbp + -120], rax
  testq rax, rax
  jne std.unicode.category.is_whitespace_block_30
  jmp std.unicode.category.is_whitespace_block_26
std.unicode.category.is_whitespace_block_26:
  jmp std.unicode.category.is_whitespace_block_26
  movq [rel str_const_119], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq $r8, rax
  cmpq [rbp + -128], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  jmp std.unicode.category.is_whitespace_block_30
std.unicode.category.is_whitespace_block_30:
  movq [rbp + -136], rax
  jmp std.unicode.category.is_whitespace_epilogue
std.unicode.category.is_whitespace_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.category.is_whitespace:

.globl std.unicode.rune.Rune.compare
std.unicode.rune.Rune.compare:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.unicode.rune.Rune.compare_entry:
  movq $0, rax
  jmp std.unicode.rune.Rune.compare_epilogue
std.unicode.rune.Rune.compare_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.rune.Rune.compare:

.globl std.unicode.rune.__init__
std.unicode.rune.__init__:
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
std.unicode.rune.__init___entry:
  movq $0, rax
  jmp std.unicode.rune.__init___epilogue
std.unicode.rune.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.rune.__init__:

.globl test_categories
test_categories:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 408
test_categories_entry:
test_categories_block_0:
  movq [rel str_const_120], rcx
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
  movq [rel str_const_121], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.unicode.index.is_upper
  movq $r3, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_122], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq [rel str_const_123], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  call std.unicode.index.is_upper
  movq $r9, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_124], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rel str_const_125], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  call std.unicode.index.is_lower
  movq $r15, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_126], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq [rel str_const_127], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -168], rcx
  call std.unicode.index.is_lower
  movq $r21, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_128], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq [rel str_const_129], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -192], rcx
  call std.unicode.index.is_digit
  movq $r27, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rel str_const_130], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -200], rcx
  movq [rbp + -208], rdx
  call lm_assert
  movq [rel str_const_131], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -216], rcx
  call std.unicode.index.is_digit
  movq $r33, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_132], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  movq [rel str_const_133], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -240], rcx
  call std.unicode.index.is_alpha
  movq $r39, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  movq [rel str_const_134], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -248], rcx
  movq [rbp + -256], rdx
  call lm_assert
  movq [rel str_const_135], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -264], rcx
  call std.unicode.index.is_alpha
  movq $r45, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -272]
  movq [rel str_const_136], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -272], rcx
  movq [rbp + -280], rdx
  call lm_assert
  movq [rel str_const_137], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -288], rcx
  call std.unicode.index.is_alphanumeric
  movq $r51, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rel str_const_138], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -296], rcx
  movq [rbp + -304], rdx
  call lm_assert
  movq [rel str_const_139], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -312], rcx
  call std.unicode.index.is_alphanumeric
  movq $r57, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -320]
  movq [rel str_const_140], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -320], rcx
  movq [rbp + -328], rdx
  call lm_assert
  movq [rel str_const_141], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -336], rcx
  call std.unicode.index.is_alphanumeric
  movq $r63, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -344]
  movq [rel str_const_142], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -344], rcx
  movq [rbp + -352], rdx
  call lm_assert
  movq [rel str_const_143], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -360], rcx
  call std.unicode.index.is_whitespace
  movq $r69, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -368]
  movq [rel str_const_144], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -368], rcx
  movq [rbp + -376], rdx
  call lm_assert
  movq [rel str_const_145], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -384], rcx
  call std.unicode.index.is_whitespace
  movq $r75, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rel str_const_146], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -392], rcx
  movq [rbp + -400], rdx
  call lm_assert
  movq [rel str_const_147], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -408], rcx
  call std.unicode.index.is_whitespace
  movq $r81, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -416]
  movq [rel str_const_148], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -416], rcx
  movq [rbp + -424], rdx
  call lm_assert
  movq $9, rax
  jmp test_categories_epilogue
test_categories_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_categories:

.globl test_normalize
test_normalize:
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
test_normalize_entry:
test_normalize_block_0:
  movq [rel str_const_149], rcx
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
  movq [rel str_const_150], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.unicode.index.to_upper
  movq [rel str_const_151], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r3, rax
  cmpq [rbp + -104], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_152], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq [rel str_const_153], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  call std.unicode.index.to_lower
  movq [rel str_const_154], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r9, rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_155], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $9, rax
  jmp test_normalize_epilogue
test_normalize_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_normalize:

.globl std.unicode.rune.char_code
std.unicode.rune.char_code:
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
std.unicode.rune.char_code_entry:
std.unicode.rune.char_code_block_0:
  movq [rel str_const_156], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -72], rcx
  call lm_list_len
  jmp std.unicode.rune.char_code_block_5
std.unicode.rune.char_code_block_5:
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.unicode.rune.char_code_block_7
  jmp std.unicode.rune.char_code_block_19
std.unicode.rune.char_code_block_7:
  jmp std.unicode.rune.char_code_block_7
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -88]
  movq [rbp + -72], rcx
  movq $1, rdx
  movq [rbp + -88], r8
  call substring
  movq $r10, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.unicode.rune.char_code_block_13
  jmp std.unicode.rune.char_code_block_14
std.unicode.rune.char_code_block_13:
  jmp std.unicode.rune.char_code_block_13
  movq $1, rax
  jmp std.unicode.rune.char_code_epilogue
std.unicode.rune.char_code_block_14:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.unicode.rune.char_code_block_5
std.unicode.rune.char_code_block_19:
  movq $7993, rax
  jmp std.unicode.rune.char_code_epilogue
std.unicode.rune.char_code_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.rune.char_code:

.globl std.unicode.category.__init__
std.unicode.category.__init__:
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
std.unicode.category.__init___entry:
  movq $0, rax
  jmp std.unicode.category.__init___epilogue
std.unicode.category.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.category.__init__:

.globl std.unicode.index.is_alpha
std.unicode.index.is_alpha:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.unicode.index.is_alpha_entry:
std.unicode.index.is_alpha_block_0:
  movq [rbp + -64], rcx
  call std.unicode.category.is_alpha
  movq $r1, rax
  jmp std.unicode.index.is_alpha_epilogue
std.unicode.index.is_alpha_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.index.is_alpha:

.globl std.unicode.category.is_lower
std.unicode.category.is_lower:
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
std.unicode.category.is_lower_entry:
std.unicode.category.is_lower_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.unicode.category.is_lower_block_4
  jmp std.unicode.category.is_lower_block_6
std.unicode.category.is_lower_block_4:
  jmp std.unicode.category.is_lower_block_4
  movq $10, rax
  jmp std.unicode.category.is_lower_epilogue
std.unicode.category.is_lower_block_6:
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $9, r8
  call substring
  movq [rel str_const_162], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  jmp std.unicode.category.is_lower_block_12
std.unicode.category.is_lower_block_12:
  jmp std.unicode.category.is_lower_block_14
std.unicode.category.is_lower_block_14:
  movq [rbp + -80], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r13, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.unicode.category.is_lower_block_17
  jmp std.unicode.category.is_lower_block_31
std.unicode.category.is_lower_block_17:
  jmp std.unicode.category.is_lower_block_17
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  movq [rbp + -80], rcx
  movq $1, rdx
  movq [rbp + -96], r8
  call substring
  movq $r18, rax
  cmpq $r8, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.unicode.category.is_lower_block_23
  jmp std.unicode.category.is_lower_block_25
std.unicode.category.is_lower_block_23:
  jmp std.unicode.category.is_lower_block_23
  movq $18, rax
  jmp std.unicode.category.is_lower_epilogue
std.unicode.category.is_lower_block_25:
  jmp std.unicode.category.is_lower_block_26
std.unicode.category.is_lower_block_26:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.unicode.category.is_lower_block_14
std.unicode.category.is_lower_block_31:
  movq $10, rax
  jmp std.unicode.category.is_lower_epilogue
std.unicode.category.is_lower_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.category.is_lower:

.globl std.unicode.category.is_alphanumeric
std.unicode.category.is_alphanumeric:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.unicode.category.is_alphanumeric_entry:
std.unicode.category.is_alphanumeric_block_0:
  movq [rbp + -64], rcx
  call std.unicode.category.is_alpha
  movq $r2, rax
  testq rax, rax
  jne std.unicode.category.is_alphanumeric_block_6
  jmp std.unicode.category.is_alphanumeric_block_3
std.unicode.category.is_alphanumeric_block_3:
  jmp std.unicode.category.is_alphanumeric_block_3
  movq [rbp + -64], rcx
  call std.unicode.category.is_digit
  jmp std.unicode.category.is_alphanumeric_block_6
std.unicode.category.is_alphanumeric_block_6:
  movq $r3, rax
  jmp std.unicode.category.is_alphanumeric_epilogue
std.unicode.category.is_alphanumeric_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.category.is_alphanumeric:

.globl std.unicode.category.is_alpha
std.unicode.category.is_alpha:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.unicode.category.is_alpha_entry:
std.unicode.category.is_alpha_block_0:
  movq [rbp + -64], rcx
  call std.unicode.category.is_upper
  movq $r2, rax
  testq rax, rax
  jne std.unicode.category.is_alpha_block_6
  jmp std.unicode.category.is_alpha_block_3
std.unicode.category.is_alpha_block_3:
  jmp std.unicode.category.is_alpha_block_3
  movq [rbp + -64], rcx
  call std.unicode.category.is_lower
  jmp std.unicode.category.is_alpha_block_6
std.unicode.category.is_alpha_block_6:
  movq $r3, rax
  jmp std.unicode.category.is_alpha_epilogue
std.unicode.category.is_alpha_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.category.is_alpha:

.globl std.unicode.category.is_digit
std.unicode.category.is_digit:
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
std.unicode.category.is_digit_entry:
std.unicode.category.is_digit_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.unicode.category.is_digit_block_4
  jmp std.unicode.category.is_digit_block_6
std.unicode.category.is_digit_block_4:
  jmp std.unicode.category.is_digit_block_4
  movq $10, rax
  jmp std.unicode.category.is_digit_epilogue
std.unicode.category.is_digit_block_6:
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $9, r8
  call substring
  movq [rel str_const_163], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  jmp std.unicode.category.is_digit_block_12
std.unicode.category.is_digit_block_12:
  jmp std.unicode.category.is_digit_block_14
std.unicode.category.is_digit_block_14:
  movq [rbp + -80], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r13, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.unicode.category.is_digit_block_17
  jmp std.unicode.category.is_digit_block_31
std.unicode.category.is_digit_block_17:
  jmp std.unicode.category.is_digit_block_17
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  movq [rbp + -80], rcx
  movq $1, rdx
  movq [rbp + -96], r8
  call substring
  movq $r18, rax
  cmpq $r8, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.unicode.category.is_digit_block_23
  jmp std.unicode.category.is_digit_block_25
std.unicode.category.is_digit_block_23:
  jmp std.unicode.category.is_digit_block_23
  movq $18, rax
  jmp std.unicode.category.is_digit_epilogue
std.unicode.category.is_digit_block_25:
  jmp std.unicode.category.is_digit_block_26
std.unicode.category.is_digit_block_26:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.unicode.category.is_digit_block_14
std.unicode.category.is_digit_block_31:
  movq $10, rax
  jmp std.unicode.category.is_digit_epilogue
std.unicode.category.is_digit_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.category.is_digit:

.globl std.unicode.rune.Rune.to_string
std.unicode.rune.Rune.to_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.unicode.rune.Rune.to_string_entry:
  movq $0, rax
  jmp std.unicode.rune.Rune.to_string_epilogue
std.unicode.rune.Rune.to_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.unicode.rune.Rune.to_string:

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

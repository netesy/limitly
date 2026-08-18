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
  .string "Testing String Frame..."
.align 8
str_const_1:
  .string "hello"
.align 8
str_const_2:
  .string "length failed"
.align 8
str_const_3:
  .string " world"
.align 8
str_const_4:
  .string "hello world"
.align 8
str_const_5:
  .string "concat failed"
.align 8
str_const_6:
  .string "ell"
.align 8
str_const_7:
  .string "substring failed"
.align 8
str_const_8:
  .string "ell"
.align 8
str_const_9:
  .string "contains true failed"
.align 8
str_const_10:
  .string "xyz"
.align 8
str_const_11:
  .string "contains false failed"
.align 8
str_const_12:
  .string "he"
.align 8
str_const_13:
  .string "starts_with true failed"
.align 8
str_const_14:
  .string "lo"
.align 8
str_const_15:
  .string "starts_with false failed"
.align 8
str_const_16:
  .string "lo"
.align 8
str_const_17:
  .string "ends_with true failed"
.align 8
str_const_18:
  .string "e"
.align 8
str_const_19:
  .string "char_at failed"
.align 8
str_const_20:
  .string "hellohello"
.align 8
str_const_21:
  .string "repeat failed"
.align 8
str_const_22:
  .string "-"
.align 8
str_const_23:
  .string "---hello"
.align 8
str_const_24:
  .string "pad_left failed"
.align 8
str_const_25:
  .string "-"
.align 8
str_const_26:
  .string "hello---"
.align 8
str_const_27:
  .string "pad_right failed"
.align 8
str_const_28:
  .string ""
.align 8
str_const_29:
  .string "=== String Module Test Suite ==="
.align 8
str_const_30:
  .string "String frame test failed"
.align 8
str_const_31:
  .string "StringBuilder test failed"
.align 8
str_const_32:
  .string "String helpers test failed"
.align 8
str_const_33:
  .string "All string tests passed successfully."
.align 8
str_const_34:
  .string "Testing StringBuilder..."
.align 8
str_const_35:
  .string "hello"
.align 8
str_const_36:
  .string " "
.align 8
str_const_37:
  .string "world"
.align 8
str_const_38:
  .string "hello world
"
.align 8
str_const_39:
  .string "StringBuilder failed"
.align 8
str_const_40:
  .string " "
.align 8
str_const_41:
  .string "	"
.align 8
str_const_42:
  .string "
"
.align 8
str_const_43:
  .string ""
.align 8
str_const_44:
  .string " "
.align 8
str_const_45:
  .string "	"
.align 8
str_const_46:
  .string "
"
.align 8
str_const_47:
  .string ""
.align 8
str_const_48:
  .string "Testing String Helpers..."
.align 8
str_const_49:
  .string "abc"
.align 8
str_const_50:
  .string "length helper failed"
.align 8
str_const_51:
  .string "abc"
.align 8
str_const_52:
  .string "def"
.align 8
str_const_53:
  .string "compare less failed"
.align 8
str_const_54:
  .string "def"
.align 8
str_const_55:
  .string "abc"
.align 8
str_const_56:
  .string "compare greater failed"
.align 8
str_const_57:
  .string "abc"
.align 8
str_const_58:
  .string "abc"
.align 8
str_const_59:
  .string "compare equal failed"
.align 8
str_const_60:
  .string "hello"
.align 8
str_const_61:
  .string "ell"
.align 8
str_const_62:
  .string "substring helper failed"
.align 8
str_const_63:
  .string "  hello  
"
.align 8
str_const_64:
  .string "hello"
.align 8
str_const_65:
  .string "trim failed"
.align 8
str_const_66:
  .string "a,b,c"
.align 8
str_const_67:
  .string ","
.align 8
str_const_68:
  .string "split length failed"
.align 8
str_const_69:
  .string "a"
.align 8
str_const_70:
  .string "split 0 failed"
.align 8
str_const_71:
  .string "b"
.align 8
str_const_72:
  .string "split 1 failed"
.align 8
str_const_73:
  .string "c"
.align 8
str_const_74:
  .string "split 2 failed"
.align 8
str_const_75:
  .string "-"
.align 8
str_const_76:
  .string "a-b-c"
.align 8
str_const_77:
  .string "join failed"
.align 8
str_const_78:
  .string "hello world"
.align 8
str_const_79:
  .string "world"
.align 8
str_const_80:
  .string "everyone"
.align 8
str_const_81:
  .string "hello everyone"
.align 8
str_const_82:
  .string "replace failed"
.align 8
str_const_83:
  .string " "
.align 8
str_const_84:
  .string "!"
.align 8
str_const_85:
  .string """
.align 8
str_const_86:
  .string "#"
.align 8
str_const_87:
  .string "$"
.align 8
str_const_88:
  .string "%"
.align 8
str_const_89:
  .string "&"
.align 8
str_const_90:
  .string "'"
.align 8
str_const_91:
  .string "("
.align 8
str_const_92:
  .string ")"
.align 8
str_const_93:
  .string "*"
.align 8
str_const_94:
  .string "+"
.align 8
str_const_95:
  .string ","
.align 8
str_const_96:
  .string "-"
.align 8
str_const_97:
  .string "."
.align 8
str_const_98:
  .string "/"
.align 8
str_const_99:
  .string "0"
.align 8
str_const_100:
  .string "1"
.align 8
str_const_101:
  .string "2"
.align 8
str_const_102:
  .string "3"
.align 8
str_const_103:
  .string "4"
.align 8
str_const_104:
  .string "5"
.align 8
str_const_105:
  .string "6"
.align 8
str_const_106:
  .string "7"
.align 8
str_const_107:
  .string "8"
.align 8
str_const_108:
  .string "9"
.align 8
str_const_109:
  .string ":"
.align 8
str_const_110:
  .string ";"
.align 8
str_const_111:
  .string "<"
.align 8
str_const_112:
  .string "="
.align 8
str_const_113:
  .string ">"
.align 8
str_const_114:
  .string "?"
.align 8
str_const_115:
  .string "@"
.align 8
str_const_116:
  .string "A"
.align 8
str_const_117:
  .string "B"
.align 8
str_const_118:
  .string "C"
.align 8
str_const_119:
  .string "D"
.align 8
str_const_120:
  .string "E"
.align 8
str_const_121:
  .string "F"
.align 8
str_const_122:
  .string "G"
.align 8
str_const_123:
  .string "H"
.align 8
str_const_124:
  .string "I"
.align 8
str_const_125:
  .string "J"
.align 8
str_const_126:
  .string "K"
.align 8
str_const_127:
  .string "L"
.align 8
str_const_128:
  .string "M"
.align 8
str_const_129:
  .string "N"
.align 8
str_const_130:
  .string "O"
.align 8
str_const_131:
  .string "P"
.align 8
str_const_132:
  .string "Q"
.align 8
str_const_133:
  .string "R"
.align 8
str_const_134:
  .string "S"
.align 8
str_const_135:
  .string "T"
.align 8
str_const_136:
  .string "U"
.align 8
str_const_137:
  .string "V"
.align 8
str_const_138:
  .string "W"
.align 8
str_const_139:
  .string "X"
.align 8
str_const_140:
  .string "Y"
.align 8
str_const_141:
  .string "Z"
.align 8
str_const_142:
  .string "["
.align 8
str_const_143:
  .string "\"
.align 8
str_const_144:
  .string "]"
.align 8
str_const_145:
  .string "^"
.align 8
str_const_146:
  .string "_"
.align 8
str_const_147:
  .string "`"
.align 8
str_const_148:
  .string "a"
.align 8
str_const_149:
  .string "b"
.align 8
str_const_150:
  .string "c"
.align 8
str_const_151:
  .string "d"
.align 8
str_const_152:
  .string "e"
.align 8
str_const_153:
  .string "f"
.align 8
str_const_154:
  .string "g"
.align 8
str_const_155:
  .string "h"
.align 8
str_const_156:
  .string "i"
.align 8
str_const_157:
  .string "j"
.align 8
str_const_158:
  .string "k"
.align 8
str_const_159:
  .string "l"
.align 8
str_const_160:
  .string "m"
.align 8
str_const_161:
  .string "n"
.align 8
str_const_162:
  .string "o"
.align 8
str_const_163:
  .string "p"
.align 8
str_const_164:
  .string "q"
.align 8
str_const_165:
  .string "r"
.align 8
str_const_166:
  .string "s"
.align 8
str_const_167:
  .string "t"
.align 8
str_const_168:
  .string "u"
.align 8
str_const_169:
  .string "v"
.align 8
str_const_170:
  .string "w"
.align 8
str_const_171:
  .string "x"
.align 8
str_const_172:
  .string "y"
.align 8
str_const_173:
  .string "z"
.align 8
str_const_174:
  .string "{"
.align 8
str_const_175:
  .string "|"
.align 8
str_const_176:
  .string "}"
.align 8
str_const_177:
  .string "~"
.align 8
str_const_178:
  .string ""
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
  call std.string.index.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq [rel str_const_29], rcx
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
  call test_string_frame
  movq $r2, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_string_builder
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  call test_string_helpers
  movq $r12, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rel str_const_33], rcx
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

.globl std.string.join.__init__
std.string.join.__init__:
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
std.string.join.__init___entry:
  movq $0, rax
  jmp std.string.join.__init___epilogue
std.string.join.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.join.__init__:

.globl std.string.string.String.index_of
std.string.string.String.index_of:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.string.String.index_of_entry:
  movq $0, rax
  jmp std.string.string.String.index_of_epilogue
std.string.string.String.index_of_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.String.index_of:

.globl test_string_frame
test_string_frame:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 392
test_string_frame_entry:
test_string_frame_block_0:
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
  movq [rbp + -96], rcx
  call std.string.index.String
  movq $r3, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  call std.string.string.String.length
  movq $r6, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -104], rcx
  movq [rbp + -128], rdx
  call std.string.string.String.concat
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r12, rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rbp + -104], rcx
  movq $9, rdx
  movq $33, r8
  call std.string.string.String.substring
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq $r19, rax
  cmpq [rbp + -160], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call lm_assert
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -104], rcx
  movq [rbp + -184], rdx
  call std.string.string.String.contains
  movq $r25, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -104], rcx
  movq [rbp + -208], rdx
  call std.string.string.String.contains
  movq $r31, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -216]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -216], rcx
  movq [rbp + -224], rdx
  call lm_assert
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -104], rcx
  movq [rbp + -232], rdx
  call std.string.string.String.starts_with
  movq $r37, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -104], rcx
  movq [rbp + -256], rdx
  call std.string.string.String.starts_with
  movq $r43, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -264]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -264], rcx
  movq [rbp + -272], rdx
  call lm_assert
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -104], rcx
  movq [rbp + -280], rdx
  call std.string.string.String.ends_with
  movq $r49, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -288]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -288], rcx
  movq [rbp + -296], rdx
  call lm_assert
  movq [rbp + -104], rcx
  movq $9, rdx
  call std.string.string.String.char_at
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq $r55, rax
  cmpq [rbp + -304], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -312]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -312], rcx
  movq [rbp + -320], rdx
  call lm_assert
  movq [rbp + -104], rcx
  movq $17, rdx
  call std.string.string.String.repeat
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq $r61, rax
  cmpq [rbp + -328], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -336]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -336], rcx
  movq [rbp + -344], rdx
  call lm_assert
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -104], rcx
  movq $65, rdx
  movq [rbp + -352], r8
  call std.string.string.String.pad_left
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq $r68, rax
  cmpq [rbp + -360], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -368]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -368], rcx
  movq [rbp + -376], rdx
  call lm_assert
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -104], rcx
  movq $65, rdx
  movq [rbp + -384], r8
  call std.string.string.String.pad_right
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq $r75, rax
  cmpq [rbp + -392], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -400]
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -400], rcx
  movq [rbp + -408], rdx
  call lm_assert
  movq $9, rax
  jmp test_string_frame_epilogue
test_string_frame_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_string_frame:

.globl std.string.string.String.concat
std.string.string.String.concat:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.string.String.concat_entry:
  movq $0, rax
  jmp std.string.string.String.concat_epilogue
std.string.string.String.concat_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.String.concat:

.globl std.string.string.String.contains
std.string.string.String.contains:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.string.String.contains_entry:
  movq $0, rax
  jmp std.string.string.String.contains_epilogue
std.string.string.String.contains_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.String.contains:

.globl std.string.trim.__init__
std.string.trim.__init__:
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
std.string.trim.__init___entry:
  movq $0, rax
  jmp std.string.trim.__init___epilogue
std.string.trim.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.trim.__init__:

.globl std.string.string.compare
std.string.string.compare:
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
  mov [rbp + -72], rdx
std.string.string.compare_entry:
std.string.string.compare_block_0:
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.string.string.compare_block_2
  jmp std.string.string.compare_block_4
std.string.string.compare_block_2:
  jmp std.string.string.compare_block_2
  movq $1, rax
  jmp std.string.string.compare_epilogue
std.string.string.compare_block_4:
  movq [rbp + -64], rcx
  call lm_list_len
  movq [rbp + -72], rcx
  call lm_list_len
  movq $r7, rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.string.string.compare_block_11
  jmp std.string.string.compare_block_13
std.string.string.compare_block_11:
  jmp std.string.string.compare_block_11
  jmp std.string.string.compare_block_13
std.string.string.compare_block_13:
  jmp std.string.string.compare_block_15
std.string.string.compare_block_15:
  movq $1, rax
  cmpq $r7, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.string.string.compare_block_17
  jmp std.string.string.compare_block_45
std.string.string.compare_block_17:
  jmp std.string.string.compare_block_17
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -104], r8
  call substring
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -112]
  movq [rbp + -72], rcx
  movq $1, rdx
  movq [rbp + -112], r8
  call substring
  movq $r18, rax
  cmpq $r23, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.string.string.compare_block_29
  jmp std.string.string.compare_block_40
std.string.string.compare_block_29:
  jmp std.string.string.compare_block_29
  movq $r18, rcx
  call std.string.string.char_code
  movq $r23, rcx
  call std.string.string.char_code
  movq $r27, rax
  cmpq $r29, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.string.string.compare_block_35
  jmp std.string.string.compare_block_38
std.string.string.compare_block_35:
  jmp std.string.string.compare_block_35
  movq $9, rax
  negq rax
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp std.string.string.compare_epilogue
std.string.string.compare_block_38:
  movq $9, rax
  jmp std.string.string.compare_epilogue
std.string.string.compare_block_40:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.string.string.compare_block_15
std.string.string.compare_block_45:
  movq $r5, rax
  cmpq $r7, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne std.string.string.compare_block_47
  jmp std.string.string.compare_block_50
std.string.string.compare_block_47:
  jmp std.string.string.compare_block_47
  movq $9, rax
  negq rax
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  jmp std.string.string.compare_epilogue
std.string.string.compare_block_50:
  movq $9, rax
  jmp std.string.string.compare_epilogue
std.string.string.compare_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.compare:

.globl std.string.replace.replace
std.string.replace.replace:
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
std.string.replace.replace_entry:
std.string.replace.replace_block_0:
  movq [rbp + -72], rcx
  call lm_list_len
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.string.replace.replace_block_7
  jmp std.string.replace.replace_block_8
std.string.replace.replace_block_7:
  jmp std.string.replace.replace_block_7
  movq $0, rax
  jmp std.string.replace.replace_epilogue
std.string.replace.replace_block_8:
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  jmp std.string.replace.replace_block_11
std.string.replace.replace_block_11:
  movq $r5, rax
  subq $r3, rax
  movq rax, $r12
  movq $1, rax
  cmpq $r12, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.string.replace.replace_block_14
  jmp std.string.replace.replace_block_37
std.string.replace.replace_block_14:
  jmp std.string.replace.replace_block_14
  movq $1, rax
  addq $r3, rax
  movq rax, [rbp + -112]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -112], r8
  call substring
  movq $r16, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.string.replace.replace_block_18
  jmp std.string.replace.replace_block_24
std.string.replace.replace_block_18:
  jmp std.string.replace.replace_block_18
  movq [rbp + -80], rcx
  call lm_to_string
  movq rax, [rbp + -128]
  movq [rbp + -96], rcx
  movq [rbp + -128], rdx
  call lm_str_concat
  movq rax, [rbp + -136]
  movq $1, rax
  addq $r3, rax
  movq rax, [rbp + -144]
  jmp std.string.replace.replace_block_36
std.string.replace.replace_block_24:
  movq [rbp + -144], rax
  addq $9, rax
  movq rax, [rbp + -152]
  movq [rbp + -64], rcx
  movq [rbp + -144], rdx
  movq [rbp + -152], r8
  call substring
  movq $r25, rcx
  call lm_to_string
  movq rax, [rbp + -160]
  movq [rbp + -136], rcx
  movq [rbp + -160], rdx
  call lm_str_concat
  movq rax, [rbp + -168]
  movq [rbp + -144], rax
  addq $9, rax
  movq rax, [rbp + -176]
  jmp std.string.replace.replace_block_36
std.string.replace.replace_block_36:
  jmp std.string.replace.replace_block_11
std.string.replace.replace_block_37:
  jmp std.string.replace.replace_block_38
std.string.replace.replace_block_38:
  movq [rbp + -176], rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  testq rax, rax
  jne std.string.replace.replace_block_40
  jmp std.string.replace.replace_block_52
std.string.replace.replace_block_40:
  jmp std.string.replace.replace_block_40
  movq [rbp + -176], rax
  addq $9, rax
  movq rax, [rbp + -192]
  movq [rbp + -64], rcx
  movq [rbp + -176], rdx
  movq [rbp + -192], r8
  call substring
  movq $r36, rcx
  call lm_to_string
  movq rax, [rbp + -200]
  movq [rbp + -168], rcx
  movq [rbp + -200], rdx
  call lm_str_concat
  movq rax, [rbp + -208]
  movq [rbp + -176], rax
  addq $9, rax
  movq rax, [rbp + -216]
  jmp std.string.replace.replace_block_38
std.string.replace.replace_block_52:
  movq [rbp + -208], rax
  jmp std.string.replace.replace_epilogue
std.string.replace.replace_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.replace.replace:

.globl std.string.split.__init__
std.string.split.__init__:
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
std.string.split.__init___entry:
  movq $0, rax
  jmp std.string.split.__init___epilogue
std.string.split.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.split.__init__:

.globl std.string.string.String.length
std.string.string.String.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.string.string.String.length_entry:
  movq $0, rax
  jmp std.string.string.String.length_epilogue
std.string.string.String.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.String.length:

.globl test_string_builder
test_string_builder:
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
test_string_builder_entry:
test_string_builder_block_0:
  movq [rel str_const_34], rcx
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
  call std.string.index.StringBuilder
  movq $r2, rax
  movq rax, [rbp + -96]
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call std.string.builder.StringBuilder.append
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -96], rcx
  movq [rbp + -112], rdx
  call std.string.builder.StringBuilder.append
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -96], rcx
  movq [rbp + -120], rdx
  call std.string.builder.StringBuilder.append_line
  movq [rbp + -96], rcx
  call std.string.builder.StringBuilder.to_string
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq $r11, rax
  cmpq [rbp + -128], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  movq $9, rax
  jmp test_string_builder_epilogue
test_string_builder_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_string_builder:

.globl std.string.string.String.init
std.string.string.String.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.string.String.init_entry:
  movq $0, rax
  jmp std.string.string.String.init_epilogue
std.string.string.String.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.String.init:

.globl std.string.string.String.repeat
std.string.string.String.repeat:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.string.String.repeat_entry:
  movq $0, rax
  jmp std.string.string.String.repeat_epilogue
std.string.string.String.repeat_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.String.repeat:

.globl std.string.trim.trim
std.string.trim.trim:
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
  mov [rbp + -64], rcx
std.string.trim.trim_entry:
std.string.trim.trim_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.string.trim.trim_block_4
std.string.trim.trim_block_4:
  movq $1, rax
  cmpq $r1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.string.trim.trim_block_6
  jmp std.string.trim.trim_block_39
std.string.trim.trim_block_6:
  jmp std.string.trim.trim_block_6
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -80]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -80], r8
  call substring
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $r9, rax
  cmpq [rbp + -88], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.string.trim.trim_block_19
  jmp std.string.trim.trim_block_15
std.string.trim.trim_block_15:
  jmp std.string.trim.trim_block_15
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r9, rax
  cmpq [rbp + -104], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  jmp std.string.trim.trim_block_19
std.string.trim.trim_block_19:
  movq [rbp + -112], rax
  testq rax, rax
  jne std.string.trim.trim_block_25
  jmp std.string.trim.trim_block_21
std.string.trim.trim_block_21:
  jmp std.string.trim.trim_block_21
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq $r9, rax
  cmpq [rbp + -120], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  jmp std.string.trim.trim_block_25
std.string.trim.trim_block_25:
  movq [rbp + -128], rax
  testq rax, rax
  jne std.string.trim.trim_block_31
  jmp std.string.trim.trim_block_27
std.string.trim.trim_block_27:
  jmp std.string.trim.trim_block_27
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r9, rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  jmp std.string.trim.trim_block_31
std.string.trim.trim_block_31:
  movq [rbp + -144], rax
  testq rax, rax
  jne std.string.trim.trim_block_32
  jmp std.string.trim.trim_block_38
std.string.trim.trim_block_32:
  jmp std.string.trim.trim_block_32
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -152]
  jmp std.string.trim.trim_block_37
std.string.trim.trim_block_37:
  jmp std.string.trim.trim_block_4
std.string.trim.trim_block_38:
  jmp std.string.trim.trim_block_39
std.string.trim.trim_block_39:
  jmp std.string.trim.trim_block_41
std.string.trim.trim_block_41:
  movq $r1, rax
  cmpq [rbp + -152], rax
  setg al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  testq rax, rax
  jne std.string.trim.trim_block_43
  jmp std.string.trim.trim_block_74
std.string.trim.trim_block_43:
  jmp std.string.trim.trim_block_43
  movq $r1, rax
  subq $9, rax
  movq rax, $r30
  movq [rbp + -64], rcx
  movq $r30, rdx
  movq $r1, r8
  call substring
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq $r31, rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne std.string.trim.trim_block_55
  jmp std.string.trim.trim_block_51
std.string.trim.trim_block_51:
  jmp std.string.trim.trim_block_51
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq $r31, rax
  cmpq [rbp + -184], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  jmp std.string.trim.trim_block_55
std.string.trim.trim_block_55:
  movq [rbp + -192], rax
  testq rax, rax
  jne std.string.trim.trim_block_61
  jmp std.string.trim.trim_block_57
std.string.trim.trim_block_57:
  jmp std.string.trim.trim_block_57
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq $r31, rax
  cmpq [rbp + -200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  jmp std.string.trim.trim_block_61
std.string.trim.trim_block_61:
  movq [rbp + -208], rax
  testq rax, rax
  jne std.string.trim.trim_block_67
  jmp std.string.trim.trim_block_63
std.string.trim.trim_block_63:
  jmp std.string.trim.trim_block_63
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq $r31, rax
  cmpq [rbp + -216], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  jmp std.string.trim.trim_block_67
std.string.trim.trim_block_67:
  movq [rbp + -224], rax
  testq rax, rax
  jne std.string.trim.trim_block_68
  jmp std.string.trim.trim_block_73
std.string.trim.trim_block_68:
  jmp std.string.trim.trim_block_68
  movq $r1, rax
  subq $9, rax
  movq rax, $r46
  jmp std.string.trim.trim_block_72
std.string.trim.trim_block_72:
  jmp std.string.trim.trim_block_41
std.string.trim.trim_block_73:
  jmp std.string.trim.trim_block_74
std.string.trim.trim_block_74:
  movq [rbp + -64], rcx
  movq [rbp + -152], rdx
  movq $r46, r8
  call substring
  movq $r47, rax
  jmp std.string.trim.trim_epilogue
std.string.trim.trim_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.trim.trim:

.globl std.string.string.String.starts_with
std.string.string.String.starts_with:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.string.String.starts_with_entry:
  movq $0, rax
  jmp std.string.string.String.starts_with_epilogue
std.string.string.String.starts_with_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.String.starts_with:

.globl std.string.string.String.char_at
std.string.string.String.char_at:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.string.String.char_at_entry:
  movq $0, rax
  jmp std.string.string.String.char_at_epilogue
std.string.string.String.char_at_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.String.char_at:

.globl test_string_helpers
test_string_helpers:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 456
test_string_helpers_entry:
test_string_helpers_block_0:
  movq [rel str_const_48], rcx
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
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call lm_list_len
  movq $r3, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call std.string.index.compare
  movq $9, rax
  negq rax
  movq rax, [rbp + -136]
  movq $r10, rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call std.string.index.compare
  movq $r18, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call std.string.index.compare
  movq $r25, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -224], rcx
  movq $9, rdx
  movq $33, r8
  call std.string.index.substring
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq $r33, rax
  cmpq [rbp + -232], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -256], rcx
  call std.string.index.trim
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq $r39, rax
  cmpq [rbp + -264], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -272]
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -272], rcx
  movq [rbp + -280], rdx
  call lm_assert
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -288], rcx
  movq [rbp + -296], rdx
  call std.string.index.split
  movq $r46, rcx
  call lm_list_len
  movq $r48, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -304]
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -304], rcx
  movq [rbp + -312], rdx
  call lm_assert
  movq $r46, rcx
  movq $1, rdx
  call lm_list_get
  movq [rel str_const_69], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq $r54, rax
  cmpq [rbp + -320], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -328]
  movq [rel str_const_70], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -328], rcx
  movq [rbp + -336], rdx
  call lm_assert
  movq $r46, rcx
  movq $9, rdx
  call lm_list_get
  movq [rel str_const_71], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq $r60, rax
  cmpq [rbp + -344], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -352]
  movq [rel str_const_72], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -352], rcx
  movq [rbp + -360], rdx
  call lm_assert
  movq $r46, rcx
  movq $17, rdx
  call lm_list_get
  movq [rel str_const_73], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq $r66, rax
  cmpq [rbp + -368], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -376]
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -376], rcx
  movq [rbp + -384], rdx
  call lm_assert
  movq [rel str_const_75], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq $r46, rcx
  movq [rbp + -392], rdx
  call std.string.index.join
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq $r72, rax
  cmpq [rbp + -400], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -408]
  movq [rel str_const_77], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -408], rcx
  movq [rbp + -416], rdx
  call lm_assert
  movq [rel str_const_78], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rel str_const_79], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rel str_const_80], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rbp + -424], rcx
  movq [rbp + -432], rdx
  movq [rbp + -440], r8
  call std.string.index.replace
  movq [rel str_const_81], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq $r81, rax
  cmpq [rbp + -448], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -456]
  movq [rel str_const_82], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq [rbp + -456], rcx
  movq [rbp + -464], rdx
  call lm_assert
  movq $9, rax
  jmp test_string_helpers_epilogue
test_string_helpers_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_string_helpers:

.globl std.string.string.length
std.string.string.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.string.string.length_entry:
std.string.string.length_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  jmp std.string.string.length_epilogue
std.string.string.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.length:

.globl std.string.string.String.ends_with
std.string.string.String.ends_with:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.string.String.ends_with_entry:
  movq $0, rax
  jmp std.string.string.String.ends_with_epilogue
std.string.string.String.ends_with_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.String.ends_with:

.globl std.string.string.String.pad_left
std.string.string.String.pad_left:
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
std.string.string.String.pad_left_entry:
  movq $0, rax
  jmp std.string.string.String.pad_left_epilogue
std.string.string.String.pad_left_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.String.pad_left:

.globl std.string.builder.StringBuilder.init
std.string.builder.StringBuilder.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.string.builder.StringBuilder.init_entry:
  movq $0, rax
  jmp std.string.builder.StringBuilder.init_epilogue
std.string.builder.StringBuilder.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.builder.StringBuilder.init:

.globl std.string.string.String.pad_right
std.string.string.String.pad_right:
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
std.string.string.String.pad_right_entry:
  movq $0, rax
  jmp std.string.string.String.pad_right_epilogue
std.string.string.String.pad_right_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.String.pad_right:

.globl std.string.string.String.substring
std.string.string.String.substring:
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
std.string.string.String.substring_entry:
  movq $0, rax
  jmp std.string.string.String.substring_epilogue
std.string.string.String.substring_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.String.substring:

.globl std.string.string.substring
std.string.string.substring:
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
std.string.string.substring_entry:
std.string.string.substring_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq [rbp + -64], rdx
  call std.string.string.String.init
  movq [rbp + -88], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.string.string.String.substring
  movq $r5, rax
  jmp std.string.string.substring_epilogue
std.string.string.substring_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.substring:

.globl std.string.builder.StringBuilder.append
std.string.builder.StringBuilder.append:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.builder.StringBuilder.append_entry:
  movq $0, rax
  jmp std.string.builder.StringBuilder.append_epilogue
std.string.builder.StringBuilder.append_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.builder.StringBuilder.append:

.globl std.string.index.compare
std.string.index.compare:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.index.compare_entry:
std.string.index.compare_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.string.string.compare
  movq $r2, rax
  jmp std.string.index.compare_epilogue
std.string.index.compare_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.index.compare:

.globl std.string.string.char_code
std.string.string.char_code:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 1592
  mov [rbp + -64], rcx
std.string.string.char_code_entry:
std.string.string.char_code_block_0:
  movq [rel str_const_83], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rel str_const_84], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rcx
  movq [rbp + -80], rdx
  call lm_str_concat
  movq rax, [rbp + -88]
  movq [rel str_const_85], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -88], rcx
  movq [rbp + -96], rdx
  call lm_str_concat
  movq rax, [rbp + -104]
  movq [rel str_const_86], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_str_concat
  movq rax, [rbp + -120]
  movq [rel str_const_87], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_str_concat
  movq rax, [rbp + -136]
  movq [rel str_const_88], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_str_concat
  movq rax, [rbp + -152]
  movq [rel str_const_89], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_str_concat
  movq rax, [rbp + -168]
  movq [rel str_const_90], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call lm_str_concat
  movq rax, [rbp + -184]
  movq [rel str_const_91], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -184], rcx
  movq [rbp + -192], rdx
  call lm_str_concat
  movq rax, [rbp + -200]
  movq [rel str_const_92], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -200], rcx
  movq [rbp + -208], rdx
  call lm_str_concat
  movq rax, [rbp + -216]
  movq [rel str_const_93], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -216], rcx
  movq [rbp + -224], rdx
  call lm_str_concat
  movq rax, [rbp + -232]
  movq [rel str_const_94], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rcx
  movq [rbp + -240], rdx
  call lm_str_concat
  movq rax, [rbp + -248]
  movq [rel str_const_95], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -248], rcx
  movq [rbp + -256], rdx
  call lm_str_concat
  movq rax, [rbp + -264]
  movq [rel str_const_96], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -264], rcx
  movq [rbp + -272], rdx
  call lm_str_concat
  movq rax, [rbp + -280]
  movq [rel str_const_97], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -280], rcx
  movq [rbp + -288], rdx
  call lm_str_concat
  movq rax, [rbp + -296]
  movq [rel str_const_98], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -296], rcx
  movq [rbp + -304], rdx
  call lm_str_concat
  movq rax, [rbp + -312]
  movq [rel str_const_99], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -312], rcx
  movq [rbp + -320], rdx
  call lm_str_concat
  movq rax, [rbp + -328]
  movq [rel str_const_100], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -328], rcx
  movq [rbp + -336], rdx
  call lm_str_concat
  movq rax, [rbp + -344]
  movq [rel str_const_101], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -344], rcx
  movq [rbp + -352], rdx
  call lm_str_concat
  movq rax, [rbp + -360]
  movq [rel str_const_102], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -360], rcx
  movq [rbp + -368], rdx
  call lm_str_concat
  movq rax, [rbp + -376]
  movq [rel str_const_103], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -376], rcx
  movq [rbp + -384], rdx
  call lm_str_concat
  movq rax, [rbp + -392]
  movq [rel str_const_104], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -392], rcx
  movq [rbp + -400], rdx
  call lm_str_concat
  movq rax, [rbp + -408]
  movq [rel str_const_105], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -408], rcx
  movq [rbp + -416], rdx
  call lm_str_concat
  movq rax, [rbp + -424]
  movq [rel str_const_106], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rbp + -424], rcx
  movq [rbp + -432], rdx
  call lm_str_concat
  movq rax, [rbp + -440]
  movq [rel str_const_107], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -440], rcx
  movq [rbp + -448], rdx
  call lm_str_concat
  movq rax, [rbp + -456]
  movq [rel str_const_108], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq [rbp + -456], rcx
  movq [rbp + -464], rdx
  call lm_str_concat
  movq rax, [rbp + -472]
  movq [rel str_const_109], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq [rbp + -472], rcx
  movq [rbp + -480], rdx
  call lm_str_concat
  movq rax, [rbp + -488]
  movq [rel str_const_110], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -488], rcx
  movq [rbp + -496], rdx
  call lm_str_concat
  movq rax, [rbp + -504]
  movq [rel str_const_111], rcx
  call lm_box_string
  movq rax, [rbp + -512]
  movq [rbp + -504], rcx
  movq [rbp + -512], rdx
  call lm_str_concat
  movq rax, [rbp + -520]
  movq [rel str_const_112], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -520], rcx
  movq [rbp + -528], rdx
  call lm_str_concat
  movq rax, [rbp + -536]
  movq [rel str_const_113], rcx
  call lm_box_string
  movq rax, [rbp + -544]
  movq [rbp + -536], rcx
  movq [rbp + -544], rdx
  call lm_str_concat
  movq rax, [rbp + -552]
  movq [rel str_const_114], rcx
  call lm_box_string
  movq rax, [rbp + -560]
  movq [rbp + -552], rcx
  movq [rbp + -560], rdx
  call lm_str_concat
  movq rax, [rbp + -568]
  movq [rel str_const_115], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -568], rcx
  movq [rbp + -576], rdx
  call lm_str_concat
  movq rax, [rbp + -584]
  movq [rel str_const_116], rcx
  call lm_box_string
  movq rax, [rbp + -592]
  movq [rbp + -584], rcx
  movq [rbp + -592], rdx
  call lm_str_concat
  movq rax, [rbp + -600]
  movq [rel str_const_117], rcx
  call lm_box_string
  movq rax, [rbp + -608]
  movq [rbp + -600], rcx
  movq [rbp + -608], rdx
  call lm_str_concat
  movq rax, [rbp + -616]
  movq [rel str_const_118], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rbp + -616], rcx
  movq [rbp + -624], rdx
  call lm_str_concat
  movq rax, [rbp + -632]
  movq [rel str_const_119], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -632], rcx
  movq [rbp + -640], rdx
  call lm_str_concat
  movq rax, [rbp + -648]
  movq [rel str_const_120], rcx
  call lm_box_string
  movq rax, [rbp + -656]
  movq [rbp + -648], rcx
  movq [rbp + -656], rdx
  call lm_str_concat
  movq rax, [rbp + -664]
  movq [rel str_const_121], rcx
  call lm_box_string
  movq rax, [rbp + -672]
  movq [rbp + -664], rcx
  movq [rbp + -672], rdx
  call lm_str_concat
  movq rax, [rbp + -680]
  movq [rel str_const_122], rcx
  call lm_box_string
  movq rax, [rbp + -688]
  movq [rbp + -680], rcx
  movq [rbp + -688], rdx
  call lm_str_concat
  movq rax, [rbp + -696]
  movq [rel str_const_123], rcx
  call lm_box_string
  movq rax, [rbp + -704]
  movq [rbp + -696], rcx
  movq [rbp + -704], rdx
  call lm_str_concat
  movq rax, [rbp + -712]
  movq [rel str_const_124], rcx
  call lm_box_string
  movq rax, [rbp + -720]
  movq [rbp + -712], rcx
  movq [rbp + -720], rdx
  call lm_str_concat
  movq rax, [rbp + -728]
  movq [rel str_const_125], rcx
  call lm_box_string
  movq rax, [rbp + -736]
  movq [rbp + -728], rcx
  movq [rbp + -736], rdx
  call lm_str_concat
  movq rax, [rbp + -744]
  movq [rel str_const_126], rcx
  call lm_box_string
  movq rax, [rbp + -752]
  movq [rbp + -744], rcx
  movq [rbp + -752], rdx
  call lm_str_concat
  movq rax, [rbp + -760]
  movq [rel str_const_127], rcx
  call lm_box_string
  movq rax, [rbp + -768]
  movq [rbp + -760], rcx
  movq [rbp + -768], rdx
  call lm_str_concat
  movq rax, [rbp + -776]
  movq [rel str_const_128], rcx
  call lm_box_string
  movq rax, [rbp + -784]
  movq [rbp + -776], rcx
  movq [rbp + -784], rdx
  call lm_str_concat
  movq rax, [rbp + -792]
  movq [rel str_const_129], rcx
  call lm_box_string
  movq rax, [rbp + -800]
  movq [rbp + -792], rcx
  movq [rbp + -800], rdx
  call lm_str_concat
  movq rax, [rbp + -808]
  movq [rel str_const_130], rcx
  call lm_box_string
  movq rax, [rbp + -816]
  movq [rbp + -808], rcx
  movq [rbp + -816], rdx
  call lm_str_concat
  movq rax, [rbp + -824]
  movq [rel str_const_131], rcx
  call lm_box_string
  movq rax, [rbp + -832]
  movq [rbp + -824], rcx
  movq [rbp + -832], rdx
  call lm_str_concat
  movq rax, [rbp + -840]
  movq [rel str_const_132], rcx
  call lm_box_string
  movq rax, [rbp + -848]
  movq [rbp + -840], rcx
  movq [rbp + -848], rdx
  call lm_str_concat
  movq rax, [rbp + -856]
  movq [rel str_const_133], rcx
  call lm_box_string
  movq rax, [rbp + -864]
  movq [rbp + -856], rcx
  movq [rbp + -864], rdx
  call lm_str_concat
  movq rax, [rbp + -872]
  movq [rel str_const_134], rcx
  call lm_box_string
  movq rax, [rbp + -880]
  movq [rbp + -872], rcx
  movq [rbp + -880], rdx
  call lm_str_concat
  movq rax, [rbp + -888]
  movq [rel str_const_135], rcx
  call lm_box_string
  movq rax, [rbp + -896]
  movq [rbp + -888], rcx
  movq [rbp + -896], rdx
  call lm_str_concat
  movq rax, [rbp + -904]
  movq [rel str_const_136], rcx
  call lm_box_string
  movq rax, [rbp + -912]
  movq [rbp + -904], rcx
  movq [rbp + -912], rdx
  call lm_str_concat
  movq rax, [rbp + -920]
  movq [rel str_const_137], rcx
  call lm_box_string
  movq rax, [rbp + -928]
  movq [rbp + -920], rcx
  movq [rbp + -928], rdx
  call lm_str_concat
  movq rax, [rbp + -936]
  movq [rel str_const_138], rcx
  call lm_box_string
  movq rax, [rbp + -944]
  movq [rbp + -936], rcx
  movq [rbp + -944], rdx
  call lm_str_concat
  movq rax, [rbp + -952]
  movq [rel str_const_139], rcx
  call lm_box_string
  movq rax, [rbp + -960]
  movq [rbp + -952], rcx
  movq [rbp + -960], rdx
  call lm_str_concat
  movq rax, [rbp + -968]
  movq [rel str_const_140], rcx
  call lm_box_string
  movq rax, [rbp + -976]
  movq [rbp + -968], rcx
  movq [rbp + -976], rdx
  call lm_str_concat
  movq rax, [rbp + -984]
  movq [rel str_const_141], rcx
  call lm_box_string
  movq rax, [rbp + -992]
  movq [rbp + -984], rcx
  movq [rbp + -992], rdx
  call lm_str_concat
  movq rax, [rbp + -1000]
  movq [rel str_const_142], rcx
  call lm_box_string
  movq rax, [rbp + -1008]
  movq [rbp + -1000], rcx
  movq [rbp + -1008], rdx
  call lm_str_concat
  movq rax, [rbp + -1016]
  movq [rel str_const_143], rcx
  call lm_box_string
  movq rax, [rbp + -1024]
  movq [rbp + -1016], rcx
  movq [rbp + -1024], rdx
  call lm_str_concat
  movq rax, [rbp + -1032]
  movq [rel str_const_144], rcx
  call lm_box_string
  movq rax, [rbp + -1040]
  movq [rbp + -1032], rcx
  movq [rbp + -1040], rdx
  call lm_str_concat
  movq rax, [rbp + -1048]
  movq [rel str_const_145], rcx
  call lm_box_string
  movq rax, [rbp + -1056]
  movq [rbp + -1048], rcx
  movq [rbp + -1056], rdx
  call lm_str_concat
  movq rax, [rbp + -1064]
  movq [rel str_const_146], rcx
  call lm_box_string
  movq rax, [rbp + -1072]
  movq [rbp + -1064], rcx
  movq [rbp + -1072], rdx
  call lm_str_concat
  movq rax, [rbp + -1080]
  movq [rel str_const_147], rcx
  call lm_box_string
  movq rax, [rbp + -1088]
  movq [rbp + -1080], rcx
  movq [rbp + -1088], rdx
  call lm_str_concat
  movq rax, [rbp + -1096]
  movq [rel str_const_148], rcx
  call lm_box_string
  movq rax, [rbp + -1104]
  movq [rbp + -1096], rcx
  movq [rbp + -1104], rdx
  call lm_str_concat
  movq rax, [rbp + -1112]
  movq [rel str_const_149], rcx
  call lm_box_string
  movq rax, [rbp + -1120]
  movq [rbp + -1112], rcx
  movq [rbp + -1120], rdx
  call lm_str_concat
  movq rax, [rbp + -1128]
  movq [rel str_const_150], rcx
  call lm_box_string
  movq rax, [rbp + -1136]
  movq [rbp + -1128], rcx
  movq [rbp + -1136], rdx
  call lm_str_concat
  movq rax, [rbp + -1144]
  movq [rel str_const_151], rcx
  call lm_box_string
  movq rax, [rbp + -1152]
  movq [rbp + -1144], rcx
  movq [rbp + -1152], rdx
  call lm_str_concat
  movq rax, [rbp + -1160]
  movq [rel str_const_152], rcx
  call lm_box_string
  movq rax, [rbp + -1168]
  movq [rbp + -1160], rcx
  movq [rbp + -1168], rdx
  call lm_str_concat
  movq rax, [rbp + -1176]
  movq [rel str_const_153], rcx
  call lm_box_string
  movq rax, [rbp + -1184]
  movq [rbp + -1176], rcx
  movq [rbp + -1184], rdx
  call lm_str_concat
  movq rax, [rbp + -1192]
  movq [rel str_const_154], rcx
  call lm_box_string
  movq rax, [rbp + -1200]
  movq [rbp + -1192], rcx
  movq [rbp + -1200], rdx
  call lm_str_concat
  movq rax, [rbp + -1208]
  movq [rel str_const_155], rcx
  call lm_box_string
  movq rax, [rbp + -1216]
  movq [rbp + -1208], rcx
  movq [rbp + -1216], rdx
  call lm_str_concat
  movq rax, [rbp + -1224]
  movq [rel str_const_156], rcx
  call lm_box_string
  movq rax, [rbp + -1232]
  movq [rbp + -1224], rcx
  movq [rbp + -1232], rdx
  call lm_str_concat
  movq rax, [rbp + -1240]
  movq [rel str_const_157], rcx
  call lm_box_string
  movq rax, [rbp + -1248]
  movq [rbp + -1240], rcx
  movq [rbp + -1248], rdx
  call lm_str_concat
  movq rax, [rbp + -1256]
  movq [rel str_const_158], rcx
  call lm_box_string
  movq rax, [rbp + -1264]
  movq [rbp + -1256], rcx
  movq [rbp + -1264], rdx
  call lm_str_concat
  movq rax, [rbp + -1272]
  movq [rel str_const_159], rcx
  call lm_box_string
  movq rax, [rbp + -1280]
  movq [rbp + -1272], rcx
  movq [rbp + -1280], rdx
  call lm_str_concat
  movq rax, [rbp + -1288]
  movq [rel str_const_160], rcx
  call lm_box_string
  movq rax, [rbp + -1296]
  movq [rbp + -1288], rcx
  movq [rbp + -1296], rdx
  call lm_str_concat
  movq rax, [rbp + -1304]
  movq [rel str_const_161], rcx
  call lm_box_string
  movq rax, [rbp + -1312]
  movq [rbp + -1304], rcx
  movq [rbp + -1312], rdx
  call lm_str_concat
  movq rax, [rbp + -1320]
  movq [rel str_const_162], rcx
  call lm_box_string
  movq rax, [rbp + -1328]
  movq [rbp + -1320], rcx
  movq [rbp + -1328], rdx
  call lm_str_concat
  movq rax, [rbp + -1336]
  movq [rel str_const_163], rcx
  call lm_box_string
  movq rax, [rbp + -1344]
  movq [rbp + -1336], rcx
  movq [rbp + -1344], rdx
  call lm_str_concat
  movq rax, [rbp + -1352]
  movq [rel str_const_164], rcx
  call lm_box_string
  movq rax, [rbp + -1360]
  movq [rbp + -1352], rcx
  movq [rbp + -1360], rdx
  call lm_str_concat
  movq rax, [rbp + -1368]
  movq [rel str_const_165], rcx
  call lm_box_string
  movq rax, [rbp + -1376]
  movq [rbp + -1368], rcx
  movq [rbp + -1376], rdx
  call lm_str_concat
  movq rax, [rbp + -1384]
  movq [rel str_const_166], rcx
  call lm_box_string
  movq rax, [rbp + -1392]
  movq [rbp + -1384], rcx
  movq [rbp + -1392], rdx
  call lm_str_concat
  movq rax, [rbp + -1400]
  movq [rel str_const_167], rcx
  call lm_box_string
  movq rax, [rbp + -1408]
  movq [rbp + -1400], rcx
  movq [rbp + -1408], rdx
  call lm_str_concat
  movq rax, [rbp + -1416]
  movq [rel str_const_168], rcx
  call lm_box_string
  movq rax, [rbp + -1424]
  movq [rbp + -1416], rcx
  movq [rbp + -1424], rdx
  call lm_str_concat
  movq rax, [rbp + -1432]
  movq [rel str_const_169], rcx
  call lm_box_string
  movq rax, [rbp + -1440]
  movq [rbp + -1432], rcx
  movq [rbp + -1440], rdx
  call lm_str_concat
  movq rax, [rbp + -1448]
  movq [rel str_const_170], rcx
  call lm_box_string
  movq rax, [rbp + -1456]
  movq [rbp + -1448], rcx
  movq [rbp + -1456], rdx
  call lm_str_concat
  movq rax, [rbp + -1464]
  movq [rel str_const_171], rcx
  call lm_box_string
  movq rax, [rbp + -1472]
  movq [rbp + -1464], rcx
  movq [rbp + -1472], rdx
  call lm_str_concat
  movq rax, [rbp + -1480]
  movq [rel str_const_172], rcx
  call lm_box_string
  movq rax, [rbp + -1488]
  movq [rbp + -1480], rcx
  movq [rbp + -1488], rdx
  call lm_str_concat
  movq rax, [rbp + -1496]
  movq [rel str_const_173], rcx
  call lm_box_string
  movq rax, [rbp + -1504]
  movq [rbp + -1496], rcx
  movq [rbp + -1504], rdx
  call lm_str_concat
  movq rax, [rbp + -1512]
  movq [rel str_const_174], rcx
  call lm_box_string
  movq rax, [rbp + -1520]
  movq [rbp + -1512], rcx
  movq [rbp + -1520], rdx
  call lm_str_concat
  movq rax, [rbp + -1528]
  movq [rel str_const_175], rcx
  call lm_box_string
  movq rax, [rbp + -1536]
  movq [rbp + -1528], rcx
  movq [rbp + -1536], rdx
  call lm_str_concat
  movq rax, [rbp + -1544]
  movq [rel str_const_176], rcx
  call lm_box_string
  movq rax, [rbp + -1552]
  movq [rbp + -1544], rcx
  movq [rbp + -1552], rdx
  call lm_str_concat
  movq rax, [rbp + -1560]
  movq [rel str_const_177], rcx
  call lm_box_string
  movq rax, [rbp + -1568]
  movq [rbp + -1560], rcx
  movq [rbp + -1568], rdx
  call lm_str_concat
  movq rax, [rbp + -1576]
  movq [rbp + -1576], rcx
  call lm_list_len
  jmp std.string.string.char_code_block_287
std.string.string.char_code_block_287:
  movq $1, rax
  cmpq $r191, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -1584]
  movq [rbp + -1584], rax
  testq rax, rax
  jne std.string.string.char_code_block_289
  jmp std.string.string.char_code_block_301
std.string.string.char_code_block_289:
  jmp std.string.string.char_code_block_289
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -1592]
  movq [rbp + -1576], rcx
  movq $1, rdx
  movq [rbp + -1592], r8
  call substring
  movq $r198, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1600]
  movq [rbp + -1600], rax
  testq rax, rax
  jne std.string.string.char_code_block_295
  jmp std.string.string.char_code_block_296
std.string.string.char_code_block_295:
  jmp std.string.string.char_code_block_295
  movq $1, rax
  jmp std.string.string.char_code_epilogue
std.string.string.char_code_block_296:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -1608]
  jmp std.string.string.char_code_block_287
std.string.string.char_code_block_301:
  movq $7993, rax
  jmp std.string.string.char_code_epilogue
std.string.string.char_code_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.char_code:

.globl std.string.string.__init__
std.string.string.__init__:
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
std.string.string.__init___entry:
  movq $0, rax
  jmp std.string.string.__init___epilogue
std.string.string.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.__init__:

.globl std.string.index.String
std.string.index.String:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.string.index.String_entry:
std.string.index.String_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.string.string.String.init
  movq [rbp + -72], rax
  jmp std.string.index.String_epilogue
std.string.index.String_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.index.String:

.globl std.string.split.split
std.string.split.split:
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
std.string.split.split_entry:
std.string.split.split_block_0:
  movq [rbp + -72], rcx
  call lm_list_len
  movq [rbp + -64], rcx
  call lm_list_len
  movq $0, rcx
  call lm_list_new
  movq $r2, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.string.split.split_block_9
  jmp std.string.split.split_block_24
std.string.split.split_block_9:
  jmp std.string.split.split_block_9
  jmp std.string.split.split_block_11
std.string.split.split_block_11:
  movq $1, rax
  cmpq $r4, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.string.split.split_block_13
  jmp std.string.split.split_block_23
std.string.split.split_block_13:
  jmp std.string.split.split_block_13
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -96], r8
  call substring
  movq $r6, rcx
  movq $r17, rdx
  call lm_list_append
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.string.split.split_block_11
std.string.split.split_block_23:
  movq $r6, rax
  jmp std.string.split.split_epilogue
std.string.split.split_block_24:
  jmp std.string.split.split_block_27
std.string.split.split_block_27:
  movq $r4, rax
  subq $r2, rax
  movq rax, $r25
  movq $1, rax
  cmpq $r25, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.string.split.split_block_30
  jmp std.string.split.split_block_46
std.string.split.split_block_30:
  jmp std.string.split.split_block_30
  movq $1, rax
  addq $r2, rax
  movq rax, [rbp + -120]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -120], r8
  call substring
  movq $r29, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.string.split.split_block_34
  jmp std.string.split.split_block_40
std.string.split.split_block_34:
  jmp std.string.split.split_block_34
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $1, r8
  call substring
  movq $r6, rcx
  movq $r32, rdx
  call lm_list_append
  movq $1, rax
  addq $r2, rax
  movq rax, [rbp + -136]
  jmp std.string.split.split_block_45
std.string.split.split_block_40:
  movq [rbp + -136], rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.string.split.split_block_45
std.string.split.split_block_45:
  jmp std.string.split.split_block_27
std.string.split.split_block_46:
  movq [rbp + -64], rcx
  movq [rbp + -136], rdx
  movq $r4, r8
  call substring
  movq $r6, rcx
  movq $r39, rdx
  call lm_list_append
  movq $r6, rax
  jmp std.string.split.split_epilogue
std.string.split.split_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.split.split:

.globl std.string.join.join
std.string.join.join:
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
std.string.join.join_entry:
std.string.join.join_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r2, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.string.join.join_block_5
  jmp std.string.join.join_block_7
std.string.join.join_block_5:
  jmp std.string.join.join_block_5
  movq [rel str_const_178], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.string.join.join_epilogue
std.string.join.join_block_7:
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  jmp std.string.join.join_block_12
std.string.join.join_block_12:
  movq $9, rax
  cmpq $r2, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.string.join.join_block_14
  jmp std.string.join.join_block_24
std.string.join.join_block_14:
  jmp std.string.join.join_block_14
  movq [rbp + -72], rcx
  call lm_to_string
  movq rax, [rbp + -104]
  movq $r9, rcx
  movq [rbp + -104], rdx
  call lm_str_concat
  movq rax, [rbp + -112]
  movq [rbp + -64], rcx
  movq $9, rdx
  call lm_list_get
  movq [rbp + -112], rcx
  movq $r16, rdx
  call lm_str_concat
  movq rax, [rbp + -120]
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -128]
  jmp std.string.join.join_block_12
std.string.join.join_block_24:
  movq [rbp + -120], rax
  jmp std.string.join.join_epilogue
std.string.join.join_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.join.join:

.globl std.string.replace.__init__
std.string.replace.__init__:
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
std.string.replace.__init___entry:
  movq $0, rax
  jmp std.string.replace.__init___epilogue
std.string.replace.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.replace.__init__:

.globl std.string.index.split
std.string.index.split:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.index.split_entry:
std.string.index.split_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.string.split.split
  movq $r2, rax
  jmp std.string.index.split_epilogue
std.string.index.split_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.index.split:

.globl std.string.index.__init__
std.string.index.__init__:
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
std.string.index.__init___entry:
  movq $0, rax
  jmp std.string.index.__init___epilogue
std.string.index.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.index.__init__:

.globl std.string.builder.StringBuilder.append_line
std.string.builder.StringBuilder.append_line:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.builder.StringBuilder.append_line_entry:
  movq $0, rax
  jmp std.string.builder.StringBuilder.append_line_epilogue
std.string.builder.StringBuilder.append_line_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.builder.StringBuilder.append_line:

.globl std.string.builder.StringBuilder.to_string
std.string.builder.StringBuilder.to_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.string.builder.StringBuilder.to_string_entry:
  movq $0, rax
  jmp std.string.builder.StringBuilder.to_string_epilogue
std.string.builder.StringBuilder.to_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.builder.StringBuilder.to_string:

.globl std.string.index.StringBuilder
std.string.index.StringBuilder:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.string.index.StringBuilder_entry:
std.string.index.StringBuilder_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.string.builder.StringBuilder.init
  movq $0, rax
  jmp std.string.index.StringBuilder_epilogue
std.string.index.StringBuilder_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.index.StringBuilder:

.globl std.string.builder.__init__
std.string.builder.__init__:
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
std.string.builder.__init___entry:
  movq $0, rax
  jmp std.string.builder.__init___epilogue
std.string.builder.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.builder.__init__:

.globl std.string.string.String.last_index_of
std.string.string.String.last_index_of:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.string.String.last_index_of_entry:
  movq $0, rax
  jmp std.string.string.String.last_index_of_epilogue
std.string.string.String.last_index_of_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.string.String.last_index_of:

.globl std.string.index.length
std.string.index.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.string.index.length_entry:
std.string.index.length_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  jmp std.string.index.length_epilogue
std.string.index.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.index.length:

.globl std.string.index.substring
std.string.index.substring:
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
std.string.index.substring_entry:
std.string.index.substring_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.string.string.substring
  movq $r3, rax
  jmp std.string.index.substring_epilogue
std.string.index.substring_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.index.substring:

.globl std.string.index.join
std.string.index.join:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.index.join_entry:
std.string.index.join_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.string.join.join
  movq $r2, rax
  jmp std.string.index.join_epilogue
std.string.index.join_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.index.join:

.globl std.string.index.replace
std.string.index.replace:
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
std.string.index.replace_entry:
std.string.index.replace_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.string.replace.replace
  movq $r3, rax
  jmp std.string.index.replace_epilogue
std.string.index.replace_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.index.replace:

.globl std.string.index.trim
std.string.index.trim:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.string.index.trim_entry:
std.string.index.trim_block_0:
  movq [rbp + -64], rcx
  call std.string.trim.trim
  movq $r1, rax
  jmp std.string.index.trim_epilogue
std.string.index.trim_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.index.trim:

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

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
  .string "{"
.align 8
str_const_2:
  .string "}"
.align 8
str_const_3:
  .string "_"
.align 8
str_const_4:
  .string ""
.align 8
str_const_5:
  .string ""
.align 8
str_const_6:
  .string ""
.align 8
str_const_7:
  .string " "
.align 8
str_const_8:
  .string "_"
.align 8
str_const_9:
  .string ""
.align 8
str_const_10:
  .string ""
.align 8
str_const_11:
  .string " "
.align 8
str_const_12:
  .string ""
.align 8
str_const_13:
  .string ""
.align 8
str_const_14:
  .string " "
.align 8
str_const_15:
  .string " "
.align 8
str_const_16:
  .string ""
.align 8
str_const_17:
  .string ""
.align 8
str_const_18:
  .string ""
.align 8
str_const_19:
  .string ""
.align 8
str_const_20:
  .string "Testing Format Frame..."
.align 8
str_const_21:
  .string "123"
.align 8
str_const_22:
  .string "int failed"
.align 8
str_const_23:
  .string "4"
.align 8
str_const_24:
  .string "."
.align 8
str_const_25:
  .string "5"
.align 8
str_const_26:
  .string "6"
.align 8
str_const_27:
  .string "float failed"
.align 8
str_const_28:
  .string "true"
.align 8
str_const_29:
  .string "bool failed"
.align 8
str_const_30:
  .string "abc"
.align 8
str_const_31:
  .string "-"
.align 8
str_const_32:
  .string "--abc"
.align 8
str_const_33:
  .string "pad_left failed"
.align 8
str_const_34:
  .string "abc"
.align 8
str_const_35:
  .string "-"
.align 8
str_const_36:
  .string "abc--"
.align 8
str_const_37:
  .string "pad_right failed"
.align 8
str_const_38:
  .string "abc"
.align 8
str_const_39:
  .string "-"
.align 8
str_const_40:
  .string "-abc-"
.align 8
str_const_41:
  .string "center failed"
.align 8
str_const_42:
  .string "abcdef"
.align 8
str_const_43:
  .string "ab..."
.align 8
str_const_44:
  .string "truncate failed"
.align 8
str_const_45:
  .string "hello world"
.align 8
str_const_46:
  .string "Hello World"
.align 8
str_const_47:
  .string "title_case failed"
.align 8
str_const_48:
  .string "hello world"
.align 8
str_const_49:
  .string "hello_world"
.align 8
str_const_50:
  .string "snake_case failed"
.align 8
str_const_51:
  .string "hello world"
.align 8
str_const_52:
  .string "helloWorld"
.align 8
str_const_53:
  .string "camel_case failed"
.align 8
str_const_54:
  .string "hello world"
.align 8
str_const_55:
  .string "hello-world"
.align 8
str_const_56:
  .string "kebab_case failed"
.align 8
str_const_57:
  .string "hello world"
.align 8
str_const_58:
  .string "HelloWorld"
.align 8
str_const_59:
  .string "pascal_case failed"
.align 8
str_const_60:
  .string " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
.align 8
str_const_61:
  .string "_"
.align 8
str_const_62:
  .string ""
.align 8
str_const_63:
  .string ""
.align 8
str_const_64:
  .string "=== Format Module Test Suite ==="
.align 8
str_const_65:
  .string "Format frame test failed"
.align 8
str_const_66:
  .string "Format helpers test failed"
.align 8
str_const_67:
  .string "All format tests passed successfully."
.align 8
str_const_68:
  .string ""
.align 8
str_const_69:
  .string "Testing Format Helpers..."
.align 8
str_const_70:
  .string "456"
.align 8
str_const_71:
  .string "format_int failed"
.align 8
str_const_72:
  .string "7"
.align 8
str_const_73:
  .string "."
.align 8
str_const_74:
  .string "8"
.align 8
str_const_75:
  .string "9"
.align 8
str_const_76:
  .string "format_float failed"
.align 8
str_const_77:
  .string "false"
.align 8
str_const_78:
  .string "format_bool failed"
.align 8
str_const_79:
  .string "abc"
.align 8
str_const_80:
  .string "  abc"
.align 8
str_const_81:
  .string "pad_string failed"
.align 8
str_const_82:
  .string "abcdef"
.align 8
str_const_83:
  .string "ab..."
.align 8
str_const_84:
  .string "truncate_string failed"
.align 8
str_const_85:
  .string "hello world"
.align 8
str_const_86:
  .string "Hello World"
.align 8
str_const_87:
  .string "title_case helper failed"
.align 8
str_const_88:
  .string "hello world"
.align 8
str_const_89:
  .string "hello_world"
.align 8
str_const_90:
  .string "snake_case helper failed"
.align 8
str_const_91:
  .string "hello world"
.align 8
str_const_92:
  .string "helloWorld"
.align 8
str_const_93:
  .string "camel_case helper failed"
.align 8
str_const_94:
  .string "hello {}, today is {}"
.align 8
str_const_95:
  .string "world"
.align 8
str_const_96:
  .string "sunny"
.align 8
str_const_97:
  .string "hello world, today is sunny"
.align 8
str_const_98:
  .string "printf_template failed"
.align 8
str_const_99:
  .string ""
.align 8
str_const_100:
  .string "..."
.align 8
str_const_101:
  .string "a"
.align 8
str_const_102:
  .string "A"
.align 8
str_const_103:
  .string "b"
.align 8
str_const_104:
  .string "B"
.align 8
str_const_105:
  .string "c"
.align 8
str_const_106:
  .string "C"
.align 8
str_const_107:
  .string "d"
.align 8
str_const_108:
  .string "D"
.align 8
str_const_109:
  .string "e"
.align 8
str_const_110:
  .string "E"
.align 8
str_const_111:
  .string "f"
.align 8
str_const_112:
  .string "F"
.align 8
str_const_113:
  .string "g"
.align 8
str_const_114:
  .string "G"
.align 8
str_const_115:
  .string "h"
.align 8
str_const_116:
  .string "H"
.align 8
str_const_117:
  .string "i"
.align 8
str_const_118:
  .string "I"
.align 8
str_const_119:
  .string "j"
.align 8
str_const_120:
  .string "J"
.align 8
str_const_121:
  .string "k"
.align 8
str_const_122:
  .string "K"
.align 8
str_const_123:
  .string "l"
.align 8
str_const_124:
  .string "L"
.align 8
str_const_125:
  .string "m"
.align 8
str_const_126:
  .string "M"
.align 8
str_const_127:
  .string "n"
.align 8
str_const_128:
  .string "N"
.align 8
str_const_129:
  .string "o"
.align 8
str_const_130:
  .string "O"
.align 8
str_const_131:
  .string "p"
.align 8
str_const_132:
  .string "P"
.align 8
str_const_133:
  .string "q"
.align 8
str_const_134:
  .string "Q"
.align 8
str_const_135:
  .string "r"
.align 8
str_const_136:
  .string "R"
.align 8
str_const_137:
  .string "s"
.align 8
str_const_138:
  .string "S"
.align 8
str_const_139:
  .string "t"
.align 8
str_const_140:
  .string "T"
.align 8
str_const_141:
  .string "u"
.align 8
str_const_142:
  .string "U"
.align 8
str_const_143:
  .string "v"
.align 8
str_const_144:
  .string "V"
.align 8
str_const_145:
  .string "w"
.align 8
str_const_146:
  .string "W"
.align 8
str_const_147:
  .string "x"
.align 8
str_const_148:
  .string "X"
.align 8
str_const_149:
  .string "y"
.align 8
str_const_150:
  .string "Y"
.align 8
str_const_151:
  .string "z"
.align 8
str_const_152:
  .string "Z"
.align 8
str_const_153:
  .string "A"
.align 8
str_const_154:
  .string "a"
.align 8
str_const_155:
  .string "B"
.align 8
str_const_156:
  .string "b"
.align 8
str_const_157:
  .string "C"
.align 8
str_const_158:
  .string "c"
.align 8
str_const_159:
  .string "D"
.align 8
str_const_160:
  .string "d"
.align 8
str_const_161:
  .string "E"
.align 8
str_const_162:
  .string "e"
.align 8
str_const_163:
  .string "F"
.align 8
str_const_164:
  .string "f"
.align 8
str_const_165:
  .string "G"
.align 8
str_const_166:
  .string "g"
.align 8
str_const_167:
  .string "H"
.align 8
str_const_168:
  .string "h"
.align 8
str_const_169:
  .string "I"
.align 8
str_const_170:
  .string "i"
.align 8
str_const_171:
  .string "J"
.align 8
str_const_172:
  .string "j"
.align 8
str_const_173:
  .string "K"
.align 8
str_const_174:
  .string "k"
.align 8
str_const_175:
  .string "L"
.align 8
str_const_176:
  .string "l"
.align 8
str_const_177:
  .string "M"
.align 8
str_const_178:
  .string "m"
.align 8
str_const_179:
  .string "N"
.align 8
str_const_180:
  .string "n"
.align 8
str_const_181:
  .string "O"
.align 8
str_const_182:
  .string "o"
.align 8
str_const_183:
  .string "P"
.align 8
str_const_184:
  .string "p"
.align 8
str_const_185:
  .string "Q"
.align 8
str_const_186:
  .string "q"
.align 8
str_const_187:
  .string "R"
.align 8
str_const_188:
  .string "r"
.align 8
str_const_189:
  .string "S"
.align 8
str_const_190:
  .string "s"
.align 8
str_const_191:
  .string "T"
.align 8
str_const_192:
  .string "t"
.align 8
str_const_193:
  .string "U"
.align 8
str_const_194:
  .string "u"
.align 8
str_const_195:
  .string "V"
.align 8
str_const_196:
  .string "v"
.align 8
str_const_197:
  .string "W"
.align 8
str_const_198:
  .string "w"
.align 8
str_const_199:
  .string "X"
.align 8
str_const_200:
  .string "x"
.align 8
str_const_201:
  .string "Y"
.align 8
str_const_202:
  .string "y"
.align 8
str_const_203:
  .string "Z"
.align 8
str_const_204:
  .string "z"
.align 8
str_const_205:
  .string " "
.align 8
str_const_206:
  .string "	"
.align 8
str_const_207:
  .string "
"
.align 8
str_const_208:
  .string ""
.align 8
str_const_209:
  .string " "
.align 8
str_const_210:
  .string "	"
.align 8
str_const_211:
  .string "
"
.align 8
str_const_212:
  .string ""
.align 8
str_const_213:
  .string "true"
.align 8
str_const_214:
  .string "false"
.align 8
str_const_215:
  .string "_"
.align 8
str_const_216:
  .string "-"
.align 8
str_const_217:
  .string " "
.align 8
str_const_218:
  .string "%s"
.align 8
str_const_219:
  .string ""
.align 8
str_const_220:
  .string "%s"
.align 8
str_const_221:
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
  sub rsp, 136
main_entry:
main_block_0:
  call std.format.index.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq [rel str_const_64], rcx
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
  call test_format_frame
  movq $r2, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_format_helpers
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  addq $16, rax
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  mov rax, [rax]
  movq rax, [rbp + -152]
  movq [rbp + -152], rcx
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

.globl std.format.index.kebab_case
std.format.index.kebab_case:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.format.index.kebab_case_entry:
std.format.index.kebab_case_block_0:
  movq [rbp + -64], rcx
  call std.format.formatter.kebab_case
  movq $r1, rax
  jmp std.format.index.kebab_case_epilogue
std.format.index.kebab_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.kebab_case:

.globl std.format.index.camel_case
std.format.index.camel_case:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.format.index.camel_case_entry:
std.format.index.camel_case_block_0:
  movq [rbp + -64], rcx
  call std.format.formatter.camel_case
  movq $r1, rax
  jmp std.format.index.camel_case_epilogue
std.format.index.camel_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.camel_case:

.globl std.format.index.Format.init
std.format.index.Format.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.format.index.Format.init_entry:
  movq $0, rax
  jmp std.format.index.Format.init_epilogue
std.format.index.Format.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.Format.init:

.globl std.format.index.Format.kebab_case
std.format.index.Format.kebab_case:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.format.index.Format.kebab_case_entry:
  movq $0, rax
  jmp std.format.index.Format.kebab_case_epilogue
std.format.index.Format.kebab_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.Format.kebab_case:

.globl std.format.index.Format.camel_case
std.format.index.Format.camel_case:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.format.index.Format.camel_case_entry:
  movq $0, rax
  jmp std.format.index.Format.camel_case_epilogue
std.format.index.Format.camel_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.Format.camel_case:

.globl std.format.index.format_float
std.format.index.format_float:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.format.index.format_float_entry:
std.format.index.format_float_block_0:
  movq [rbp + -64], rcx
  call std.format.formatter.format_float
  movq $r1, rax
  jmp std.format.index.format_float_epilogue
std.format.index.format_float_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.format_float:

.globl std.format.index.Format.snake_case
std.format.index.Format.snake_case:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.format.index.Format.snake_case_entry:
  movq $0, rax
  jmp std.format.index.Format.snake_case_epilogue
std.format.index.Format.snake_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.Format.snake_case:

.globl std.format.index.Format.title_case
std.format.index.Format.title_case:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.format.index.Format.title_case_entry:
  movq $0, rax
  jmp std.format.index.Format.title_case_epilogue
std.format.index.Format.title_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.Format.title_case:

.globl std.format.index.Format.pad_right
std.format.index.Format.pad_right:
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
std.format.index.Format.pad_right_entry:
  movq $0, rax
  jmp std.format.index.Format.pad_right_epilogue
std.format.index.Format.pad_right_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.Format.pad_right:

.globl std.format.index.Format.pascal_case
std.format.index.Format.pascal_case:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.format.index.Format.pascal_case_entry:
  movq $0, rax
  jmp std.format.index.Format.pascal_case_epilogue
std.format.index.Format.pascal_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.Format.pascal_case:

.globl std.format.index.Format.format_bool
std.format.index.Format.format_bool:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.format.index.Format.format_bool_entry:
  movq $0, rax
  jmp std.format.index.Format.format_bool_epilogue
std.format.index.Format.format_bool_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.Format.format_bool:

.globl std.format.index.Format.format_float
std.format.index.Format.format_float:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.format.index.Format.format_float_entry:
  movq $0, rax
  jmp std.format.index.Format.format_float_epilogue
std.format.index.Format.format_float_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.Format.format_float:

.globl std.format.printf.printf_template
std.format.printf.printf_template:
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
std.format.printf.printf_template_entry:
std.format.printf.printf_template_block_0:
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.format.printf.printf_template_block_6
std.format.printf.printf_template_block_6:
  movq $1, rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.format.printf.printf_template_block_8
  jmp std.format.printf.printf_template_block_62
std.format.printf.printf_template_block_8:
  jmp std.format.printf.printf_template_block_8
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -96], r8
  call substring
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r12, rax
  cmpq [rbp + -104], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.format.printf.printf_template_block_17
  jmp std.format.printf.printf_template_block_23
std.format.printf.printf_template_block_17:
  jmp std.format.printf.printf_template_block_17
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -128]
  jmp std.format.printf.printf_template_block_23
std.format.printf.printf_template_block_23:
  movq [rbp + -128], rax
  testq rax, rax
  jne std.format.printf.printf_template_block_25
  jmp std.format.printf.printf_template_block_36
std.format.printf.printf_template_block_25:
  jmp std.format.printf.printf_template_block_25
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -136]
  movq $1, rax
  addq $17, rax
  movq rax, [rbp + -144]
  movq [rbp + -64], rcx
  movq [rbp + -136], rdx
  movq [rbp + -144], r8
  call substring
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq $r28, rax
  cmpq [rbp + -152], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  jmp std.format.printf.printf_template_block_36
std.format.printf.printf_template_block_36:
  movq [rbp + -160], rax
  testq rax, rax
  jne std.format.printf.printf_template_block_37
  jmp std.format.printf.printf_template_block_54
std.format.printf.printf_template_block_37:
  jmp std.format.printf.printf_template_block_37
  movq [rbp + -72], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r32, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  testq rax, rax
  jne std.format.printf.printf_template_block_40
  jmp std.format.printf.printf_template_block_49
std.format.printf.printf_template_block_40:
  jmp std.format.printf.printf_template_block_40
  movq [rbp + -72], rcx
  movq $1, rdx
  call lm_list_get
  movq $r35, rax
  movq rax, [rbp + -176]
  movq [rbp + -80], rcx
  movq [rbp + -176], rdx
  call lm_str_concat
  movq rax, [rbp + -184]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -192]
  jmp std.format.printf.printf_template_block_49
std.format.printf.printf_template_block_49:
  movq $1, rax
  addq $17, rax
  movq rax, [rbp + -200]
  jmp std.format.printf.printf_template_block_61
std.format.printf.printf_template_block_54:
  movq [rbp + -184], rcx
  movq $r12, rdx
  call lm_str_concat
  movq rax, [rbp + -208]
  movq [rbp + -200], rax
  addq $9, rax
  movq rax, [rbp + -216]
  jmp std.format.printf.printf_template_block_61
std.format.printf.printf_template_block_61:
  jmp std.format.printf.printf_template_block_6
std.format.printf.printf_template_block_62:
  movq [rbp + -208], rax
  jmp std.format.printf.printf_template_epilogue
std.format.printf.printf_template_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.printf.printf_template:

.globl std.format.index.format_bool
std.format.index.format_bool:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.format.index.format_bool_entry:
std.format.index.format_bool_block_0:
  movq [rbp + -64], rcx
  call std.format.formatter.format_bool
  movq $r1, rax
  jmp std.format.index.format_bool_epilogue
std.format.index.format_bool_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.format_bool:

.globl std.format.formatter.__init__
std.format.formatter.__init__:
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
std.format.formatter.__init___entry:
  movq $0, rax
  jmp std.format.formatter.__init___epilogue
std.format.formatter.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.formatter.__init__:

.globl std.format.index.Format.format_int
std.format.index.Format.format_int:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.format.index.Format.format_int_entry:
  movq $0, rax
  jmp std.format.index.Format.format_int_epilogue
std.format.index.Format.format_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.Format.format_int:

.globl std.format.formatter.pascal_case
std.format.formatter.pascal_case:
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
std.format.formatter.pascal_case_entry:
std.format.formatter.pascal_case_block_0:
  movq [rbp + -64], rcx
  call std.format.formatter.snake_case
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $r1, rcx
  movq [rbp + -72], rdx
  call std.string.split
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  jmp std.format.formatter.pascal_case_block_8
std.format.formatter.pascal_case_block_8:
  movq $r4, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r8, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.format.formatter.pascal_case_block_11
  jmp std.format.formatter.pascal_case_block_38
std.format.formatter.pascal_case_block_11:
  jmp std.format.formatter.pascal_case_block_11
  movq $r4, rcx
  movq $1, rdx
  call lm_list_get
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r11, rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.format.formatter.pascal_case_block_16
  jmp std.format.formatter.pascal_case_block_21
std.format.formatter.pascal_case_block_16:
  jmp std.format.formatter.pascal_case_block_16
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.format.formatter.pascal_case_block_8
std.format.formatter.pascal_case_block_21:
  movq $r11, rcx
  movq $1, rdx
  movq $9, r8
  call substring
  movq $r21, rcx
  call std.string.to_upper
  movq $r11, rcx
  call lm_list_len
  movq $r11, rcx
  movq $9, rdx
  movq $r25, r8
  call substring
  movq [rbp + -80], rcx
  movq $r22, rdx
  call lm_str_concat
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  movq $r26, rdx
  call lm_str_concat
  movq rax, [rbp + -128]
  movq [rbp + -112], rax
  addq $9, rax
  movq rax, [rbp + -136]
  jmp std.format.formatter.pascal_case_block_8
std.format.formatter.pascal_case_block_38:
  movq [rbp + -128], rax
  jmp std.format.formatter.pascal_case_epilogue
std.format.formatter.pascal_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.formatter.pascal_case:

.globl std.format.formatter.snake_case
std.format.formatter.snake_case:
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
std.format.formatter.snake_case_entry:
std.format.formatter.snake_case_block_0:
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.format.formatter.snake_case_block_5
std.format.formatter.snake_case_block_5:
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.format.formatter.snake_case_block_7
  jmp std.format.formatter.snake_case_block_29
std.format.formatter.snake_case_block_7:
  jmp std.format.formatter.snake_case_block_7
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -88], r8
  call substring
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r10, rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.format.formatter.snake_case_block_15
  jmp std.format.formatter.snake_case_block_19
std.format.formatter.snake_case_block_15:
  jmp std.format.formatter.snake_case_block_15
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -72], rcx
  movq [rbp + -112], rdx
  call lm_str_concat
  movq rax, [rbp + -120]
  jmp std.format.formatter.snake_case_block_24
std.format.formatter.snake_case_block_19:
  movq $r10, rcx
  call std.string.to_lower
  movq $r17, rcx
  call lm_to_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_str_concat
  movq rax, [rbp + -136]
  jmp std.format.formatter.snake_case_block_24
std.format.formatter.snake_case_block_24:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.format.formatter.snake_case_block_5
std.format.formatter.snake_case_block_29:
  movq [rbp + -136], rax
  jmp std.format.formatter.snake_case_epilogue
std.format.formatter.snake_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.formatter.snake_case:

.globl std.format.formatter.title_case
std.format.formatter.title_case:
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
std.format.formatter.title_case_entry:
std.format.formatter.title_case_block_0:
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.format.formatter.title_case_block_3
  jmp std.format.formatter.title_case_block_5
std.format.formatter.title_case_block_3:
  jmp std.format.formatter.title_case_block_3
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.format.formatter.title_case_epilogue
std.format.formatter.title_case_block_5:
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call std.string.split
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  jmp std.format.formatter.title_case_block_11
std.format.formatter.title_case_block_11:
  movq $r6, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r10, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.format.formatter.title_case_block_14
  jmp std.format.formatter.title_case_block_53
std.format.formatter.title_case_block_14:
  jmp std.format.formatter.title_case_block_14
  movq $r6, rcx
  movq $1, rdx
  call lm_list_get
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq $r13, rax
  cmpq [rbp + -120], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.format.formatter.title_case_block_19
  jmp std.format.formatter.title_case_block_27
std.format.formatter.title_case_block_19:
  jmp std.format.formatter.title_case_block_19
  movq $1, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne std.format.formatter.title_case_block_22
  jmp std.format.formatter.title_case_block_26
std.format.formatter.title_case_block_22:
  jmp std.format.formatter.title_case_block_22
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -104], rcx
  movq [rbp + -144], rdx
  call lm_str_concat
  movq rax, [rbp + -152]
  jmp std.format.formatter.title_case_block_26
std.format.formatter.title_case_block_26:
  jmp std.format.formatter.title_case_block_48
std.format.formatter.title_case_block_27:
  movq $1, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  testq rax, rax
  jne std.format.formatter.title_case_block_30
  jmp std.format.formatter.title_case_block_34
std.format.formatter.title_case_block_30:
  jmp std.format.formatter.title_case_block_30
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -152], rcx
  movq [rbp + -168], rdx
  call lm_str_concat
  movq rax, [rbp + -176]
  jmp std.format.formatter.title_case_block_34
std.format.formatter.title_case_block_34:
  movq $r13, rcx
  movq $1, rdx
  movq $9, r8
  call substring
  movq $r30, rcx
  call std.string.to_upper
  movq $r13, rcx
  call lm_list_len
  movq $r13, rcx
  movq $9, rdx
  movq $r34, r8
  call substring
  movq $r35, rcx
  call std.string.to_lower
  movq [rbp + -176], rcx
  movq $r31, rdx
  call lm_str_concat
  movq rax, [rbp + -184]
  movq [rbp + -184], rcx
  movq $r36, rdx
  call lm_str_concat
  movq rax, [rbp + -192]
  jmp std.format.formatter.title_case_block_48
std.format.formatter.title_case_block_48:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -200]
  jmp std.format.formatter.title_case_block_11
std.format.formatter.title_case_block_53:
  movq [rbp + -192], rax
  jmp std.format.formatter.title_case_epilogue
std.format.formatter.title_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.formatter.title_case:

.globl std.format.formatter.center
std.format.formatter.center:
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
std.format.formatter.center_entry:
std.format.formatter.center_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  cmpq [rbp + -72], rax
  setge al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.format.formatter.center_block_3
  jmp std.format.formatter.center_block_4
std.format.formatter.center_block_3:
  jmp std.format.formatter.center_block_3
  movq $0, rax
  jmp std.format.formatter.center_epilogue
std.format.formatter.center_block_4:
  movq [rbp + -64], rcx
  call lm_list_len
  movq [rbp + -72], rax
  subq $r6, rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  cqto
  movq $17, rcx
  idivq rcx
  movq rax, [rbp + -104]
  movq [rbp + -96], rax
  subq [rbp + -104], rax
  movq rax, [rbp + -112]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  jmp std.format.formatter.center_block_15
std.format.formatter.center_block_15:
  movq $1, rax
  cmpq [rbp + -104], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.format.formatter.center_block_17
  jmp std.format.formatter.center_block_25
std.format.formatter.center_block_17:
  jmp std.format.formatter.center_block_17
  movq [rbp + -80], rcx
  call lm_to_string
  movq rax, [rbp + -136]
  movq [rbp + -120], rcx
  movq [rbp + -136], rdx
  call lm_str_concat
  movq rax, [rbp + -144]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -152]
  jmp std.format.formatter.center_block_15
std.format.formatter.center_block_25:
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  jmp std.format.formatter.center_block_29
std.format.formatter.center_block_29:
  movq $1, rax
  cmpq [rbp + -112], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  testq rax, rax
  jne std.format.formatter.center_block_31
  jmp std.format.formatter.center_block_39
std.format.formatter.center_block_31:
  jmp std.format.formatter.center_block_31
  movq [rbp + -80], rcx
  call lm_to_string
  movq rax, [rbp + -176]
  movq [rbp + -160], rcx
  movq [rbp + -176], rdx
  call lm_str_concat
  movq rax, [rbp + -184]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -192]
  jmp std.format.formatter.center_block_29
std.format.formatter.center_block_39:
  movq [rbp + -64], rcx
  call lm_to_string
  movq rax, [rbp + -200]
  movq [rbp + -144], rcx
  movq [rbp + -200], rdx
  call lm_str_concat
  movq rax, [rbp + -208]
  movq [rbp + -208], rcx
  movq [rbp + -184], rdx
  call lm_str_concat
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  jmp std.format.formatter.center_epilogue
std.format.formatter.center_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.formatter.center:

.globl std.format.formatter.pad_right
std.format.formatter.pad_right:
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
std.format.formatter.pad_right_entry:
std.format.formatter.pad_right_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  cmpq [rbp + -72], rax
  setge al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.format.formatter.pad_right_block_3
  jmp std.format.formatter.pad_right_block_4
std.format.formatter.pad_right_block_3:
  jmp std.format.formatter.pad_right_block_3
  movq $0, rax
  jmp std.format.formatter.pad_right_epilogue
std.format.formatter.pad_right_block_4:
  movq [rbp + -64], rcx
  call lm_list_len
  movq [rbp + -72], rax
  subq $r6, rax
  movq rax, [rbp + -96]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  jmp std.format.formatter.pad_right_block_10
std.format.formatter.pad_right_block_10:
  movq $1, rax
  cmpq [rbp + -96], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.format.formatter.pad_right_block_12
  jmp std.format.formatter.pad_right_block_20
std.format.formatter.pad_right_block_12:
  jmp std.format.formatter.pad_right_block_12
  movq [rbp + -80], rcx
  call lm_to_string
  movq rax, [rbp + -120]
  movq [rbp + -104], rcx
  movq [rbp + -120], rdx
  call lm_str_concat
  movq rax, [rbp + -128]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -136]
  jmp std.format.formatter.pad_right_block_10
std.format.formatter.pad_right_block_20:
  movq [rbp + -64], rcx
  call lm_to_string
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  movq [rbp + -128], rdx
  call lm_str_concat
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  jmp std.format.formatter.pad_right_epilogue
std.format.formatter.pad_right_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.formatter.pad_right:

.globl std.format.formatter.pad_left
std.format.formatter.pad_left:
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
std.format.formatter.pad_left_entry:
std.format.formatter.pad_left_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  cmpq [rbp + -72], rax
  setge al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.format.formatter.pad_left_block_3
  jmp std.format.formatter.pad_left_block_4
std.format.formatter.pad_left_block_3:
  jmp std.format.formatter.pad_left_block_3
  movq $0, rax
  jmp std.format.formatter.pad_left_epilogue
std.format.formatter.pad_left_block_4:
  movq [rbp + -64], rcx
  call lm_list_len
  movq [rbp + -72], rax
  subq $r6, rax
  movq rax, [rbp + -96]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  jmp std.format.formatter.pad_left_block_10
std.format.formatter.pad_left_block_10:
  movq $1, rax
  cmpq [rbp + -96], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.format.formatter.pad_left_block_12
  jmp std.format.formatter.pad_left_block_20
std.format.formatter.pad_left_block_12:
  jmp std.format.formatter.pad_left_block_12
  movq [rbp + -80], rcx
  call lm_to_string
  movq rax, [rbp + -120]
  movq [rbp + -104], rcx
  movq [rbp + -120], rdx
  call lm_str_concat
  movq rax, [rbp + -128]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -136]
  jmp std.format.formatter.pad_left_block_10
std.format.formatter.pad_left_block_20:
  movq [rbp + -64], rcx
  call lm_to_string
  movq rax, [rbp + -144]
  movq [rbp + -128], rcx
  movq [rbp + -144], rdx
  call lm_str_concat
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  jmp std.format.formatter.pad_left_epilogue
std.format.formatter.pad_left_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.formatter.pad_left:

.globl test_format_frame
test_format_frame:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 520
test_format_frame_entry:
test_format_frame_block_0:
  movq [rel str_const_20], rcx
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
  call std.format.index.Format.init
  movq [rbp + -96], rcx
  movq $985, rdx
  call std.format.index.Format.format_int
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r7, rax
  cmpq [rbp + -104], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq [rbp + -96], rcx
  movq $2, rdx
  call std.format.index.Format.format_float
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_str_concat
  movq rax, [rbp + -144]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_str_concat
  movq rax, [rbp + -160]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_str_concat
  movq rax, [rbp + -176]
  movq $r13, rax
  cmpq [rbp + -176], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -184], rcx
  movq [rbp + -192], rdx
  call lm_assert
  movq [rbp + -96], rcx
  movq $18, rdx
  call std.format.index.Format.format_bool
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq $r26, rax
  cmpq [rbp + -200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -96], rcx
  movq [rbp + -224], rdx
  movq $41, r8
  movq [rbp + -232], r9
  call std.format.index.Format.pad_left
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq $r34, rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -248], rcx
  movq [rbp + -256], rdx
  call lm_assert
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -96], rcx
  movq [rbp + -264], rdx
  movq $41, r8
  movq [rbp + -272], r9
  call std.format.index.Format.pad_right
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq $r42, rax
  cmpq [rbp + -280], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -288]
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -288], rcx
  movq [rbp + -296], rdx
  call lm_assert
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -96], rcx
  movq [rbp + -304], rdx
  movq $41, r8
  movq [rbp + -312], r9
  call std.format.index.Format.center
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq $r50, rax
  cmpq [rbp + -320], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -328]
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -328], rcx
  movq [rbp + -336], rdx
  call lm_assert
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -96], rcx
  movq [rbp + -344], rdx
  movq $41, r8
  movq $18, r9
  call std.format.index.Format.truncate
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq $r58, rax
  cmpq [rbp + -352], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -360], rcx
  movq [rbp + -368], rdx
  call lm_assert
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -96], rcx
  movq [rbp + -376], rdx
  call std.format.index.Format.title_case
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq $r64, rax
  cmpq [rbp + -384], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -392], rcx
  movq [rbp + -400], rdx
  call lm_assert
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -96], rcx
  movq [rbp + -408], rdx
  call std.format.index.Format.snake_case
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq $r70, rax
  cmpq [rbp + -416], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -424]
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rbp + -424], rcx
  movq [rbp + -432], rdx
  call lm_assert
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rbp + -96], rcx
  movq [rbp + -440], rdx
  call std.format.index.Format.camel_case
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq $r76, rax
  cmpq [rbp + -448], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -456]
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq [rbp + -456], rcx
  movq [rbp + -464], rdx
  call lm_assert
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -96], rcx
  movq [rbp + -472], rdx
  call std.format.index.Format.kebab_case
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq $r82, rax
  cmpq [rbp + -480], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -488]
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -488], rcx
  movq [rbp + -496], rdx
  call lm_assert
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -96], rcx
  movq [rbp + -504], rdx
  call std.format.index.Format.pascal_case
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -512]
  movq $r88, rax
  cmpq [rbp + -512], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -520]
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -520], rcx
  movq [rbp + -528], rdx
  call lm_assert
  movq $9, rax
  jmp test_format_frame_epilogue
test_format_frame_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_format_frame:

.globl std.string.char_code
std.string.char_code:
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
std.string.char_code_entry:
std.string.char_code_block_0:
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -72], rcx
  call lm_list_len
  jmp std.string.char_code_block_5
std.string.char_code_block_5:
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.string.char_code_block_7
  jmp std.string.char_code_block_19
std.string.char_code_block_7:
  jmp std.string.char_code_block_7
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
  jne std.string.char_code_block_13
  jmp std.string.char_code_block_14
std.string.char_code_block_13:
  jmp std.string.char_code_block_13
  movq $1, rax
  jmp std.string.char_code_epilogue
std.string.char_code_block_14:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.string.char_code_block_5
std.string.char_code_block_19:
  movq $7993, rax
  jmp std.string.char_code_epilogue
std.string.char_code_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.char_code:

.globl std.format.formatter.camel_case
std.format.formatter.camel_case:
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
std.format.formatter.camel_case_entry:
std.format.formatter.camel_case_block_0:
  movq [rbp + -64], rcx
  call std.format.formatter.snake_case
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $r1, rcx
  movq [rbp + -72], rdx
  call std.string.split
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  jmp std.format.formatter.camel_case_block_8
std.format.formatter.camel_case_block_8:
  movq $r4, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r8, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.format.formatter.camel_case_block_11
  jmp std.format.formatter.camel_case_block_45
std.format.formatter.camel_case_block_11:
  jmp std.format.formatter.camel_case_block_11
  movq $r4, rcx
  movq $1, rdx
  call lm_list_get
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r11, rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.format.formatter.camel_case_block_16
  jmp std.format.formatter.camel_case_block_21
std.format.formatter.camel_case_block_16:
  jmp std.format.formatter.camel_case_block_16
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.format.formatter.camel_case_block_8
std.format.formatter.camel_case_block_21:
  movq [rbp + -112], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.format.formatter.camel_case_block_24
  jmp std.format.formatter.camel_case_block_27
std.format.formatter.camel_case_block_24:
  jmp std.format.formatter.camel_case_block_24
  movq [rbp + -80], rcx
  movq $r11, rdx
  call lm_str_concat
  movq rax, [rbp + -128]
  jmp std.format.formatter.camel_case_block_40
std.format.formatter.camel_case_block_27:
  movq $r11, rcx
  movq $1, rdx
  movq $9, r8
  call substring
  movq $r25, rcx
  call std.string.to_upper
  movq $r11, rcx
  call lm_list_len
  movq $r11, rcx
  movq $9, rdx
  movq $r29, r8
  call substring
  movq [rbp + -128], rcx
  movq $r26, rdx
  call lm_str_concat
  movq rax, [rbp + -136]
  movq [rbp + -136], rcx
  movq $r30, rdx
  call lm_str_concat
  movq rax, [rbp + -144]
  jmp std.format.formatter.camel_case_block_40
std.format.formatter.camel_case_block_40:
  movq [rbp + -112], rax
  addq $9, rax
  movq rax, [rbp + -152]
  jmp std.format.formatter.camel_case_block_8
std.format.formatter.camel_case_block_45:
  movq [rbp + -144], rax
  jmp std.format.formatter.camel_case_epilogue
std.format.formatter.camel_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.formatter.camel_case:

.globl std.string.length
std.string.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.string.length_entry:
std.string.length_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  jmp std.string.length_epilogue
std.string.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.length:

.globl std.string.join
std.string.join:
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
std.string.join_entry:
std.string.join_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r2, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.string.join_block_5
  jmp std.string.join_block_7
std.string.join_block_5:
  jmp std.string.join_block_5
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.string.join_epilogue
std.string.join_block_7:
  movq [rbp + -64], rcx
  movq $1, rdx
  call lm_list_get
  jmp std.string.join_block_12
std.string.join_block_12:
  movq $9, rax
  cmpq $r2, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.string.join_block_14
  jmp std.string.join_block_24
std.string.join_block_14:
  jmp std.string.join_block_14
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
  jmp std.string.join_block_12
std.string.join_block_24:
  movq [rbp + -120], rax
  jmp std.string.join_epilogue
std.string.join_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.join:

.globl std.string.String.replace
std.string.String.replace:
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
std.string.String.replace_entry:
  movq $0, rax
  jmp std.string.String.replace_epilogue
std.string.String.replace_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.replace:

.globl std.format.index.snake_case
std.format.index.snake_case:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.format.index.snake_case_entry:
std.format.index.snake_case_block_0:
  movq [rbp + -64], rcx
  call std.format.formatter.snake_case
  movq $r1, rax
  jmp std.format.index.snake_case_epilogue
std.format.index.snake_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.snake_case:

.globl std.string.String.to_upper
std.string.String.to_upper:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.string.String.to_upper_entry:
  movq $0, rax
  jmp std.string.String.to_upper_epilogue
std.string.String.to_upper_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.to_upper:

.globl std.string.String.concat
std.string.String.concat:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.String.concat_entry:
  movq $0, rax
  jmp std.string.String.concat_epilogue
std.string.String.concat_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.concat:

.globl std.string.split
std.string.split:
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
std.string.split_entry:
std.string.split_block_0:
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
  jne std.string.split_block_9
  jmp std.string.split_block_24
std.string.split_block_9:
  jmp std.string.split_block_9
  jmp std.string.split_block_11
std.string.split_block_11:
  movq $1, rax
  cmpq $r4, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.string.split_block_13
  jmp std.string.split_block_23
std.string.split_block_13:
  jmp std.string.split_block_13
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
  jmp std.string.split_block_11
std.string.split_block_23:
  movq $r6, rax
  jmp std.string.split_epilogue
std.string.split_block_24:
  jmp std.string.split_block_27
std.string.split_block_27:
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
  jne std.string.split_block_30
  jmp std.string.split_block_46
std.string.split_block_30:
  jmp std.string.split_block_30
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
  jne std.string.split_block_34
  jmp std.string.split_block_40
std.string.split_block_34:
  jmp std.string.split_block_34
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
  jmp std.string.split_block_45
std.string.split_block_40:
  movq [rbp + -136], rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.string.split_block_45
std.string.split_block_45:
  jmp std.string.split_block_27
std.string.split_block_46:
  movq [rbp + -64], rcx
  movq [rbp + -136], rdx
  movq $r4, r8
  call substring
  movq $r6, rcx
  movq $r39, rdx
  call lm_list_append
  movq $r6, rax
  jmp std.string.split_epilogue
std.string.split_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.split:

.globl std.string.String.split
std.string.String.split:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.String.split_entry:
  movq $0, rax
  jmp std.string.String.split_epilogue
std.string.String.split_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.split:

.globl std.format.index.Format.pad_left
std.format.index.Format.pad_left:
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
std.format.index.Format.pad_left_entry:
  movq $0, rax
  jmp std.format.index.Format.pad_left_epilogue
std.format.index.Format.pad_left_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.Format.pad_left:

.globl test_format_helpers
test_format_helpers:
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
test_format_helpers_entry:
test_format_helpers_block_0:
  movq [rel str_const_69], rcx
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
  movq $3649, rcx
  call std.format.index.format_int
  movq [rel str_const_70], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r3, rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_71], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq [rel str_const_72], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rel str_const_73], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_str_concat
  movq rax, [rbp + -136]
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_str_concat
  movq rax, [rbp + -152]
  movq [rel str_const_75], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_str_concat
  movq rax, [rbp + -168]
  movq $2, rcx
  call std.format.index.format_float
  movq $r16, rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq $10, rcx
  call std.format.index.format_bool
  movq [rel str_const_77], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq $r21, rax
  cmpq [rbp + -192], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rel str_const_78], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -200], rcx
  movq [rbp + -208], rdx
  call lm_assert
  movq [rel str_const_79], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -216], rcx
  movq $41, rdx
  call std.format.index.pad_string
  movq [rel str_const_80], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq $r28, rax
  cmpq [rbp + -224], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  movq [rel str_const_81], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rcx
  movq [rbp + -240], rdx
  call lm_assert
  movq [rel str_const_82], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -248], rcx
  movq $41, rdx
  call std.format.index.truncate_string
  movq [rel str_const_83], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq $r35, rax
  cmpq [rbp + -256], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -264]
  movq [rel str_const_84], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -264], rcx
  movq [rbp + -272], rdx
  call lm_assert
  movq [rel str_const_85], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -280], rcx
  call std.format.index.title_case
  movq [rel str_const_86], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq $r41, rax
  cmpq [rbp + -288], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rel str_const_87], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -296], rcx
  movq [rbp + -304], rdx
  call lm_assert
  movq [rel str_const_88], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -312], rcx
  call std.format.index.snake_case
  movq [rel str_const_89], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq $r47, rax
  cmpq [rbp + -320], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -328]
  movq [rel str_const_90], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -328], rcx
  movq [rbp + -336], rdx
  call lm_assert
  movq [rel str_const_91], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -344], rcx
  call std.format.index.camel_case
  movq [rel str_const_92], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq $r53, rax
  cmpq [rbp + -352], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rel str_const_93], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -360], rcx
  movq [rbp + -368], rdx
  call lm_assert
  movq [rel str_const_94], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_95], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq $r59, rcx
  movq [rbp + -384], rdx
  call lm_list_append
  movq [rel str_const_96], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq $r59, rcx
  movq [rbp + -392], rdx
  call lm_list_append
  movq [rbp + -376], rcx
  movq $r59, rdx
  call std.format.index.printf_template
  movq [rel str_const_97], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq $r64, rax
  cmpq [rbp + -400], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -408]
  movq [rel str_const_98], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -408], rcx
  movq [rbp + -416], rdx
  call lm_assert
  movq $9, rax
  jmp test_format_helpers_epilogue
test_format_helpers_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_format_helpers:

.globl std.string.to_lower
std.string.to_lower:
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
std.string.to_lower_entry:
std.string.to_lower_block_0:
  movq [rel str_const_99], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.string.to_lower_block_5
std.string.to_lower_block_5:
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.string.to_lower_block_7
  jmp std.string.to_lower_block_20
std.string.to_lower_block_7:
  jmp std.string.to_lower_block_7
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -88], r8
  call substring
  movq $r10, rcx
  call std.string._char_to_lower
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
  jmp std.string.to_lower_block_5
std.string.to_lower_block_20:
  movq [rbp + -104], rax
  jmp std.string.to_lower_epilogue
std.string.to_lower_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.to_lower:

.globl std.string.compare
std.string.compare:
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
std.string.compare_entry:
std.string.compare_block_0:
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.string.compare_block_2
  jmp std.string.compare_block_4
std.string.compare_block_2:
  jmp std.string.compare_block_2
  movq $1, rax
  jmp std.string.compare_epilogue
std.string.compare_block_4:
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
  jne std.string.compare_block_11
  jmp std.string.compare_block_13
std.string.compare_block_11:
  jmp std.string.compare_block_11
  jmp std.string.compare_block_13
std.string.compare_block_13:
  jmp std.string.compare_block_15
std.string.compare_block_15:
  movq $1, rax
  cmpq $r7, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.string.compare_block_17
  jmp std.string.compare_block_45
std.string.compare_block_17:
  jmp std.string.compare_block_17
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
  jne std.string.compare_block_29
  jmp std.string.compare_block_40
std.string.compare_block_29:
  jmp std.string.compare_block_29
  movq $r18, rcx
  call std.string.char_code
  movq $r23, rcx
  call std.string.char_code
  movq $r27, rax
  cmpq $r29, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.string.compare_block_35
  jmp std.string.compare_block_38
std.string.compare_block_35:
  jmp std.string.compare_block_35
  movq $9, rax
  negq rax
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp std.string.compare_epilogue
std.string.compare_block_38:
  movq $9, rax
  jmp std.string.compare_epilogue
std.string.compare_block_40:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.string.compare_block_15
std.string.compare_block_45:
  movq $r5, rax
  cmpq $r7, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne std.string.compare_block_47
  jmp std.string.compare_block_50
std.string.compare_block_47:
  jmp std.string.compare_block_47
  movq $9, rax
  negq rax
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  jmp std.string.compare_epilogue
std.string.compare_block_50:
  movq $9, rax
  jmp std.string.compare_epilogue
std.string.compare_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.compare:

.globl std.format.formatter.truncate
std.format.formatter.truncate:
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
  mov [rbp + -80], r8
std.format.formatter.truncate_entry:
std.format.formatter.truncate_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r3, rax
  cmpq [rbp + -72], rax
  setle al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.format.formatter.truncate_block_3
  jmp std.format.formatter.truncate_block_4
std.format.formatter.truncate_block_3:
  jmp std.format.formatter.truncate_block_3
  movq $0, rax
  jmp std.format.formatter.truncate_epilogue
std.format.formatter.truncate_block_4:
  movq [rbp + -80], rax
  testq rax, rax
  jne std.format.formatter.truncate_block_6
  jmp std.format.formatter.truncate_block_10
std.format.formatter.truncate_block_6:
  jmp std.format.formatter.truncate_block_6
  movq [rbp + -72], rax
  cmpq $25, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -96]
  jmp std.format.formatter.truncate_block_10
std.format.formatter.truncate_block_10:
  movq [rbp + -96], rax
  testq rax, rax
  jne std.format.formatter.truncate_block_11
  jmp std.format.formatter.truncate_block_19
std.format.formatter.truncate_block_11:
  jmp std.format.formatter.truncate_block_11
  movq [rbp + -72], rax
  subq $25, rax
  movq rax, [rbp + -104]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -104], r8
  call substring
  movq [rel str_const_100], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r13, rcx
  call lm_to_string
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  movq [rbp + -112], rdx
  call lm_str_concat
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  jmp std.format.formatter.truncate_epilogue
std.format.formatter.truncate_block_19:
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -72], r8
  call substring
  movq $r18, rax
  jmp std.format.formatter.truncate_epilogue
std.format.formatter.truncate_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.formatter.truncate:

.globl std.string.String.length
std.string.String.length:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.string.String.length_entry:
  movq $0, rax
  jmp std.string.String.length_epilogue
std.string.String.length_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.length:

.globl std.string.String.index_of
std.string.String.index_of:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.String.index_of_entry:
  movq $0, rax
  jmp std.string.String.index_of_epilogue
std.string.String.index_of_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.index_of:

.globl std.string.String._builtin_substring
std.string.String._builtin_substring:
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
std.string.String._builtin_substring_entry:
  movq $0, rax
  jmp std.string.String._builtin_substring_epilogue
std.string.String._builtin_substring_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String._builtin_substring:

.globl std.format.index.printf_template
std.format.index.printf_template:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.format.index.printf_template_entry:
std.format.index.printf_template_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.format.printf.printf_template
  movq $r2, rax
  jmp std.format.index.printf_template_epilogue
std.format.index.printf_template_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.printf_template:

.globl std.string.String.to_lower
std.string.String.to_lower:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.string.String.to_lower_entry:
  movq $0, rax
  jmp std.string.String.to_lower_epilogue
std.string.String.to_lower_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.to_lower:

.globl std.string.String.contains
std.string.String.contains:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.String.contains_entry:
  movq $0, rax
  jmp std.string.String.contains_epilogue
std.string.String.contains_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.contains:

.globl std.string._char_to_upper
std.string._char_to_upper:
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
std.string._char_to_upper_entry:
std.string._char_to_upper_block_0:
  movq [rel str_const_101], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.string._char_to_upper_block_3
  jmp std.string._char_to_upper_block_5
std.string._char_to_upper_block_3:
  jmp std.string._char_to_upper_block_3
  movq [rel str_const_102], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_5:
  movq [rel str_const_103], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -64], rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.string._char_to_upper_block_8
  jmp std.string._char_to_upper_block_10
std.string._char_to_upper_block_8:
  jmp std.string._char_to_upper_block_8
  movq [rel str_const_104], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_10:
  movq [rel str_const_105], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -64], rax
  cmpq [rbp + -120], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.string._char_to_upper_block_13
  jmp std.string._char_to_upper_block_15
std.string._char_to_upper_block_13:
  jmp std.string._char_to_upper_block_13
  movq [rel str_const_106], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_15:
  movq [rel str_const_107], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -64], rax
  cmpq [rbp + -144], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne std.string._char_to_upper_block_18
  jmp std.string._char_to_upper_block_20
std.string._char_to_upper_block_18:
  jmp std.string._char_to_upper_block_18
  movq [rel str_const_108], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_20:
  movq [rel str_const_109], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -64], rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne std.string._char_to_upper_block_23
  jmp std.string._char_to_upper_block_25
std.string._char_to_upper_block_23:
  jmp std.string._char_to_upper_block_23
  movq [rel str_const_110], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_25:
  movq [rel str_const_111], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -64], rax
  cmpq [rbp + -192], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  testq rax, rax
  jne std.string._char_to_upper_block_28
  jmp std.string._char_to_upper_block_30
std.string._char_to_upper_block_28:
  jmp std.string._char_to_upper_block_28
  movq [rel str_const_112], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_30:
  movq [rel str_const_113], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -64], rax
  cmpq [rbp + -216], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  testq rax, rax
  jne std.string._char_to_upper_block_33
  jmp std.string._char_to_upper_block_35
std.string._char_to_upper_block_33:
  jmp std.string._char_to_upper_block_33
  movq [rel str_const_114], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_35:
  movq [rel str_const_115], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -64], rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  testq rax, rax
  jne std.string._char_to_upper_block_38
  jmp std.string._char_to_upper_block_40
std.string._char_to_upper_block_38:
  jmp std.string._char_to_upper_block_38
  movq [rel str_const_116], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_40:
  movq [rel str_const_117], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -64], rax
  cmpq [rbp + -264], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  testq rax, rax
  jne std.string._char_to_upper_block_43
  jmp std.string._char_to_upper_block_45
std.string._char_to_upper_block_43:
  jmp std.string._char_to_upper_block_43
  movq [rel str_const_118], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_45:
  movq [rel str_const_119], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -64], rax
  cmpq [rbp + -288], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  testq rax, rax
  jne std.string._char_to_upper_block_48
  jmp std.string._char_to_upper_block_50
std.string._char_to_upper_block_48:
  jmp std.string._char_to_upper_block_48
  movq [rel str_const_120], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_50:
  movq [rel str_const_121], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -64], rax
  cmpq [rbp + -312], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  testq rax, rax
  jne std.string._char_to_upper_block_53
  jmp std.string._char_to_upper_block_55
std.string._char_to_upper_block_53:
  jmp std.string._char_to_upper_block_53
  movq [rel str_const_122], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_55:
  movq [rel str_const_123], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -64], rax
  cmpq [rbp + -336], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  testq rax, rax
  jne std.string._char_to_upper_block_58
  jmp std.string._char_to_upper_block_60
std.string._char_to_upper_block_58:
  jmp std.string._char_to_upper_block_58
  movq [rel str_const_124], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_60:
  movq [rel str_const_125], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -64], rax
  cmpq [rbp + -360], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -368]
  movq [rbp + -368], rax
  testq rax, rax
  jne std.string._char_to_upper_block_63
  jmp std.string._char_to_upper_block_65
std.string._char_to_upper_block_63:
  jmp std.string._char_to_upper_block_63
  movq [rel str_const_126], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_65:
  movq [rel str_const_127], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -64], rax
  cmpq [rbp + -384], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  testq rax, rax
  jne std.string._char_to_upper_block_68
  jmp std.string._char_to_upper_block_70
std.string._char_to_upper_block_68:
  jmp std.string._char_to_upper_block_68
  movq [rel str_const_128], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_70:
  movq [rel str_const_129], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -64], rax
  cmpq [rbp + -408], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -416]
  movq [rbp + -416], rax
  testq rax, rax
  jne std.string._char_to_upper_block_73
  jmp std.string._char_to_upper_block_75
std.string._char_to_upper_block_73:
  jmp std.string._char_to_upper_block_73
  movq [rel str_const_130], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_75:
  movq [rel str_const_131], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rbp + -64], rax
  cmpq [rbp + -432], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  testq rax, rax
  jne std.string._char_to_upper_block_78
  jmp std.string._char_to_upper_block_80
std.string._char_to_upper_block_78:
  jmp std.string._char_to_upper_block_78
  movq [rel str_const_132], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -448], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_80:
  movq [rel str_const_133], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq [rbp + -64], rax
  cmpq [rbp + -456], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -464]
  movq [rbp + -464], rax
  testq rax, rax
  jne std.string._char_to_upper_block_83
  jmp std.string._char_to_upper_block_85
std.string._char_to_upper_block_83:
  jmp std.string._char_to_upper_block_83
  movq [rel str_const_134], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -472], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_85:
  movq [rel str_const_135], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq [rbp + -64], rax
  cmpq [rbp + -480], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -488]
  movq [rbp + -488], rax
  testq rax, rax
  jne std.string._char_to_upper_block_88
  jmp std.string._char_to_upper_block_90
std.string._char_to_upper_block_88:
  jmp std.string._char_to_upper_block_88
  movq [rel str_const_136], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -496], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_90:
  movq [rel str_const_137], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -64], rax
  cmpq [rbp + -504], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -512]
  movq [rbp + -512], rax
  testq rax, rax
  jne std.string._char_to_upper_block_93
  jmp std.string._char_to_upper_block_95
std.string._char_to_upper_block_93:
  jmp std.string._char_to_upper_block_93
  movq [rel str_const_138], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -520], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_95:
  movq [rel str_const_139], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -64], rax
  cmpq [rbp + -528], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -536]
  movq [rbp + -536], rax
  testq rax, rax
  jne std.string._char_to_upper_block_98
  jmp std.string._char_to_upper_block_100
std.string._char_to_upper_block_98:
  jmp std.string._char_to_upper_block_98
  movq [rel str_const_140], rcx
  call lm_box_string
  movq rax, [rbp + -544]
  movq [rbp + -544], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_100:
  movq [rel str_const_141], rcx
  call lm_box_string
  movq rax, [rbp + -552]
  movq [rbp + -64], rax
  cmpq [rbp + -552], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -560]
  movq [rbp + -560], rax
  testq rax, rax
  jne std.string._char_to_upper_block_103
  jmp std.string._char_to_upper_block_105
std.string._char_to_upper_block_103:
  jmp std.string._char_to_upper_block_103
  movq [rel str_const_142], rcx
  call lm_box_string
  movq rax, [rbp + -568]
  movq [rbp + -568], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_105:
  movq [rel str_const_143], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -64], rax
  cmpq [rbp + -576], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -584]
  movq [rbp + -584], rax
  testq rax, rax
  jne std.string._char_to_upper_block_108
  jmp std.string._char_to_upper_block_110
std.string._char_to_upper_block_108:
  jmp std.string._char_to_upper_block_108
  movq [rel str_const_144], rcx
  call lm_box_string
  movq rax, [rbp + -592]
  movq [rbp + -592], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_110:
  movq [rel str_const_145], rcx
  call lm_box_string
  movq rax, [rbp + -600]
  movq [rbp + -64], rax
  cmpq [rbp + -600], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -608]
  movq [rbp + -608], rax
  testq rax, rax
  jne std.string._char_to_upper_block_113
  jmp std.string._char_to_upper_block_115
std.string._char_to_upper_block_113:
  jmp std.string._char_to_upper_block_113
  movq [rel str_const_146], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -616], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_115:
  movq [rel str_const_147], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rbp + -64], rax
  cmpq [rbp + -624], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -632]
  movq [rbp + -632], rax
  testq rax, rax
  jne std.string._char_to_upper_block_118
  jmp std.string._char_to_upper_block_120
std.string._char_to_upper_block_118:
  jmp std.string._char_to_upper_block_118
  movq [rel str_const_148], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_120:
  movq [rel str_const_149], rcx
  call lm_box_string
  movq rax, [rbp + -648]
  movq [rbp + -64], rax
  cmpq [rbp + -648], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -656]
  movq [rbp + -656], rax
  testq rax, rax
  jne std.string._char_to_upper_block_123
  jmp std.string._char_to_upper_block_125
std.string._char_to_upper_block_123:
  jmp std.string._char_to_upper_block_123
  movq [rel str_const_150], rcx
  call lm_box_string
  movq rax, [rbp + -664]
  movq [rbp + -664], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_125:
  movq [rel str_const_151], rcx
  call lm_box_string
  movq rax, [rbp + -672]
  movq [rbp + -64], rax
  cmpq [rbp + -672], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -680]
  movq [rbp + -680], rax
  testq rax, rax
  jne std.string._char_to_upper_block_128
  jmp std.string._char_to_upper_block_130
std.string._char_to_upper_block_128:
  jmp std.string._char_to_upper_block_128
  movq [rel str_const_152], rcx
  call lm_box_string
  movq rax, [rbp + -688]
  movq [rbp + -688], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_130:
  movq $0, rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string._char_to_upper:

.globl std.format.index.truncate_string
std.format.index.truncate_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.format.index.truncate_string_entry:
std.format.index.truncate_string_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq $18, r8
  call std.format.formatter.truncate
  movq $r3, rax
  jmp std.format.index.truncate_string_epilogue
std.format.index.truncate_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.truncate_string:

.globl std.format.index.__init__
std.format.index.__init__:
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
std.format.index.__init___entry:
  movq $0, rax
  jmp std.format.index.__init___epilogue
std.format.index.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.__init__:

.globl std.string._char_to_lower
std.string._char_to_lower:
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
std.string._char_to_lower_entry:
std.string._char_to_lower_block_0:
  movq [rel str_const_153], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.string._char_to_lower_block_3
  jmp std.string._char_to_lower_block_5
std.string._char_to_lower_block_3:
  jmp std.string._char_to_lower_block_3
  movq [rel str_const_154], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_5:
  movq [rel str_const_155], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -64], rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.string._char_to_lower_block_8
  jmp std.string._char_to_lower_block_10
std.string._char_to_lower_block_8:
  jmp std.string._char_to_lower_block_8
  movq [rel str_const_156], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_10:
  movq [rel str_const_157], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -64], rax
  cmpq [rbp + -120], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.string._char_to_lower_block_13
  jmp std.string._char_to_lower_block_15
std.string._char_to_lower_block_13:
  jmp std.string._char_to_lower_block_13
  movq [rel str_const_158], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_15:
  movq [rel str_const_159], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -64], rax
  cmpq [rbp + -144], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne std.string._char_to_lower_block_18
  jmp std.string._char_to_lower_block_20
std.string._char_to_lower_block_18:
  jmp std.string._char_to_lower_block_18
  movq [rel str_const_160], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_20:
  movq [rel str_const_161], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -64], rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne std.string._char_to_lower_block_23
  jmp std.string._char_to_lower_block_25
std.string._char_to_lower_block_23:
  jmp std.string._char_to_lower_block_23
  movq [rel str_const_162], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_25:
  movq [rel str_const_163], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -64], rax
  cmpq [rbp + -192], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  testq rax, rax
  jne std.string._char_to_lower_block_28
  jmp std.string._char_to_lower_block_30
std.string._char_to_lower_block_28:
  jmp std.string._char_to_lower_block_28
  movq [rel str_const_164], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_30:
  movq [rel str_const_165], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -64], rax
  cmpq [rbp + -216], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  testq rax, rax
  jne std.string._char_to_lower_block_33
  jmp std.string._char_to_lower_block_35
std.string._char_to_lower_block_33:
  jmp std.string._char_to_lower_block_33
  movq [rel str_const_166], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_35:
  movq [rel str_const_167], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -64], rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  testq rax, rax
  jne std.string._char_to_lower_block_38
  jmp std.string._char_to_lower_block_40
std.string._char_to_lower_block_38:
  jmp std.string._char_to_lower_block_38
  movq [rel str_const_168], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_40:
  movq [rel str_const_169], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -64], rax
  cmpq [rbp + -264], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  testq rax, rax
  jne std.string._char_to_lower_block_43
  jmp std.string._char_to_lower_block_45
std.string._char_to_lower_block_43:
  jmp std.string._char_to_lower_block_43
  movq [rel str_const_170], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_45:
  movq [rel str_const_171], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -64], rax
  cmpq [rbp + -288], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  testq rax, rax
  jne std.string._char_to_lower_block_48
  jmp std.string._char_to_lower_block_50
std.string._char_to_lower_block_48:
  jmp std.string._char_to_lower_block_48
  movq [rel str_const_172], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_50:
  movq [rel str_const_173], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -64], rax
  cmpq [rbp + -312], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  testq rax, rax
  jne std.string._char_to_lower_block_53
  jmp std.string._char_to_lower_block_55
std.string._char_to_lower_block_53:
  jmp std.string._char_to_lower_block_53
  movq [rel str_const_174], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_55:
  movq [rel str_const_175], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -64], rax
  cmpq [rbp + -336], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  testq rax, rax
  jne std.string._char_to_lower_block_58
  jmp std.string._char_to_lower_block_60
std.string._char_to_lower_block_58:
  jmp std.string._char_to_lower_block_58
  movq [rel str_const_176], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_60:
  movq [rel str_const_177], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -64], rax
  cmpq [rbp + -360], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -368]
  movq [rbp + -368], rax
  testq rax, rax
  jne std.string._char_to_lower_block_63
  jmp std.string._char_to_lower_block_65
std.string._char_to_lower_block_63:
  jmp std.string._char_to_lower_block_63
  movq [rel str_const_178], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_65:
  movq [rel str_const_179], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -64], rax
  cmpq [rbp + -384], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  testq rax, rax
  jne std.string._char_to_lower_block_68
  jmp std.string._char_to_lower_block_70
std.string._char_to_lower_block_68:
  jmp std.string._char_to_lower_block_68
  movq [rel str_const_180], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_70:
  movq [rel str_const_181], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -64], rax
  cmpq [rbp + -408], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -416]
  movq [rbp + -416], rax
  testq rax, rax
  jne std.string._char_to_lower_block_73
  jmp std.string._char_to_lower_block_75
std.string._char_to_lower_block_73:
  jmp std.string._char_to_lower_block_73
  movq [rel str_const_182], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_75:
  movq [rel str_const_183], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rbp + -64], rax
  cmpq [rbp + -432], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  testq rax, rax
  jne std.string._char_to_lower_block_78
  jmp std.string._char_to_lower_block_80
std.string._char_to_lower_block_78:
  jmp std.string._char_to_lower_block_78
  movq [rel str_const_184], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -448], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_80:
  movq [rel str_const_185], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq [rbp + -64], rax
  cmpq [rbp + -456], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -464]
  movq [rbp + -464], rax
  testq rax, rax
  jne std.string._char_to_lower_block_83
  jmp std.string._char_to_lower_block_85
std.string._char_to_lower_block_83:
  jmp std.string._char_to_lower_block_83
  movq [rel str_const_186], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -472], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_85:
  movq [rel str_const_187], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq [rbp + -64], rax
  cmpq [rbp + -480], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -488]
  movq [rbp + -488], rax
  testq rax, rax
  jne std.string._char_to_lower_block_88
  jmp std.string._char_to_lower_block_90
std.string._char_to_lower_block_88:
  jmp std.string._char_to_lower_block_88
  movq [rel str_const_188], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -496], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_90:
  movq [rel str_const_189], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -64], rax
  cmpq [rbp + -504], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -512]
  movq [rbp + -512], rax
  testq rax, rax
  jne std.string._char_to_lower_block_93
  jmp std.string._char_to_lower_block_95
std.string._char_to_lower_block_93:
  jmp std.string._char_to_lower_block_93
  movq [rel str_const_190], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -520], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_95:
  movq [rel str_const_191], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -64], rax
  cmpq [rbp + -528], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -536]
  movq [rbp + -536], rax
  testq rax, rax
  jne std.string._char_to_lower_block_98
  jmp std.string._char_to_lower_block_100
std.string._char_to_lower_block_98:
  jmp std.string._char_to_lower_block_98
  movq [rel str_const_192], rcx
  call lm_box_string
  movq rax, [rbp + -544]
  movq [rbp + -544], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_100:
  movq [rel str_const_193], rcx
  call lm_box_string
  movq rax, [rbp + -552]
  movq [rbp + -64], rax
  cmpq [rbp + -552], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -560]
  movq [rbp + -560], rax
  testq rax, rax
  jne std.string._char_to_lower_block_103
  jmp std.string._char_to_lower_block_105
std.string._char_to_lower_block_103:
  jmp std.string._char_to_lower_block_103
  movq [rel str_const_194], rcx
  call lm_box_string
  movq rax, [rbp + -568]
  movq [rbp + -568], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_105:
  movq [rel str_const_195], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -64], rax
  cmpq [rbp + -576], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -584]
  movq [rbp + -584], rax
  testq rax, rax
  jne std.string._char_to_lower_block_108
  jmp std.string._char_to_lower_block_110
std.string._char_to_lower_block_108:
  jmp std.string._char_to_lower_block_108
  movq [rel str_const_196], rcx
  call lm_box_string
  movq rax, [rbp + -592]
  movq [rbp + -592], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_110:
  movq [rel str_const_197], rcx
  call lm_box_string
  movq rax, [rbp + -600]
  movq [rbp + -64], rax
  cmpq [rbp + -600], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -608]
  movq [rbp + -608], rax
  testq rax, rax
  jne std.string._char_to_lower_block_113
  jmp std.string._char_to_lower_block_115
std.string._char_to_lower_block_113:
  jmp std.string._char_to_lower_block_113
  movq [rel str_const_198], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -616], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_115:
  movq [rel str_const_199], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rbp + -64], rax
  cmpq [rbp + -624], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -632]
  movq [rbp + -632], rax
  testq rax, rax
  jne std.string._char_to_lower_block_118
  jmp std.string._char_to_lower_block_120
std.string._char_to_lower_block_118:
  jmp std.string._char_to_lower_block_118
  movq [rel str_const_200], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_120:
  movq [rel str_const_201], rcx
  call lm_box_string
  movq rax, [rbp + -648]
  movq [rbp + -64], rax
  cmpq [rbp + -648], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -656]
  movq [rbp + -656], rax
  testq rax, rax
  jne std.string._char_to_lower_block_123
  jmp std.string._char_to_lower_block_125
std.string._char_to_lower_block_123:
  jmp std.string._char_to_lower_block_123
  movq [rel str_const_202], rcx
  call lm_box_string
  movq rax, [rbp + -664]
  movq [rbp + -664], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_125:
  movq [rel str_const_203], rcx
  call lm_box_string
  movq rax, [rbp + -672]
  movq [rbp + -64], rax
  cmpq [rbp + -672], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -680]
  movq [rbp + -680], rax
  testq rax, rax
  jne std.string._char_to_lower_block_128
  jmp std.string._char_to_lower_block_130
std.string._char_to_lower_block_128:
  jmp std.string._char_to_lower_block_128
  movq [rel str_const_204], rcx
  call lm_box_string
  movq rax, [rbp + -688]
  movq [rbp + -688], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_130:
  movq $0, rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string._char_to_lower:

.globl std.string.String.ends_with
std.string.String.ends_with:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.String.ends_with_entry:
  movq $0, rax
  jmp std.string.String.ends_with_epilogue
std.string.String.ends_with_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.ends_with:

.globl std.string.String.substring
std.string.String.substring:
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
std.string.String.substring_entry:
  movq $0, rax
  jmp std.string.String.substring_epilogue
std.string.String.substring_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.substring:

.globl std.string.trim
std.string.trim:
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
std.string.trim_entry:
std.string.trim_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.string.trim_block_4
std.string.trim_block_4:
  movq $1, rax
  cmpq $r1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.string.trim_block_6
  jmp std.string.trim_block_39
std.string.trim_block_6:
  jmp std.string.trim_block_6
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -80]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -80], r8
  call substring
  movq [rel str_const_205], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $r9, rax
  cmpq [rbp + -88], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.string.trim_block_19
  jmp std.string.trim_block_15
std.string.trim_block_15:
  jmp std.string.trim_block_15
  movq [rel str_const_206], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r9, rax
  cmpq [rbp + -104], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  jmp std.string.trim_block_19
std.string.trim_block_19:
  movq [rbp + -112], rax
  testq rax, rax
  jne std.string.trim_block_25
  jmp std.string.trim_block_21
std.string.trim_block_21:
  jmp std.string.trim_block_21
  movq [rel str_const_207], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq $r9, rax
  cmpq [rbp + -120], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  jmp std.string.trim_block_25
std.string.trim_block_25:
  movq [rbp + -128], rax
  testq rax, rax
  jne std.string.trim_block_31
  jmp std.string.trim_block_27
std.string.trim_block_27:
  jmp std.string.trim_block_27
  movq [rel str_const_208], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r9, rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  jmp std.string.trim_block_31
std.string.trim_block_31:
  movq [rbp + -144], rax
  testq rax, rax
  jne std.string.trim_block_32
  jmp std.string.trim_block_38
std.string.trim_block_32:
  jmp std.string.trim_block_32
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -152]
  jmp std.string.trim_block_37
std.string.trim_block_37:
  jmp std.string.trim_block_4
std.string.trim_block_38:
  jmp std.string.trim_block_39
std.string.trim_block_39:
  jmp std.string.trim_block_41
std.string.trim_block_41:
  movq $r1, rax
  cmpq [rbp + -152], rax
  setg al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  testq rax, rax
  jne std.string.trim_block_43
  jmp std.string.trim_block_74
std.string.trim_block_43:
  jmp std.string.trim_block_43
  movq $r1, rax
  subq $9, rax
  movq rax, $r30
  movq [rbp + -64], rcx
  movq $r30, rdx
  movq $r1, r8
  call substring
  movq [rel str_const_209], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq $r31, rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne std.string.trim_block_55
  jmp std.string.trim_block_51
std.string.trim_block_51:
  jmp std.string.trim_block_51
  movq [rel str_const_210], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq $r31, rax
  cmpq [rbp + -184], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  jmp std.string.trim_block_55
std.string.trim_block_55:
  movq [rbp + -192], rax
  testq rax, rax
  jne std.string.trim_block_61
  jmp std.string.trim_block_57
std.string.trim_block_57:
  jmp std.string.trim_block_57
  movq [rel str_const_211], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq $r31, rax
  cmpq [rbp + -200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  jmp std.string.trim_block_61
std.string.trim_block_61:
  movq [rbp + -208], rax
  testq rax, rax
  jne std.string.trim_block_67
  jmp std.string.trim_block_63
std.string.trim_block_63:
  jmp std.string.trim_block_63
  movq [rel str_const_212], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq $r31, rax
  cmpq [rbp + -216], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  jmp std.string.trim_block_67
std.string.trim_block_67:
  movq [rbp + -224], rax
  testq rax, rax
  jne std.string.trim_block_68
  jmp std.string.trim_block_73
std.string.trim_block_68:
  jmp std.string.trim_block_68
  movq $r1, rax
  subq $9, rax
  movq rax, $r46
  jmp std.string.trim_block_72
std.string.trim_block_72:
  jmp std.string.trim_block_41
std.string.trim_block_73:
  jmp std.string.trim_block_74
std.string.trim_block_74:
  movq [rbp + -64], rcx
  movq [rbp + -152], rdx
  movq $r46, r8
  call substring
  movq $r47, rax
  jmp std.string.trim_epilogue
std.string.trim_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.trim:

.globl std.string.String.pad_right
std.string.String.pad_right:
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
std.string.String.pad_right_entry:
  movq $0, rax
  jmp std.string.String.pad_right_epilogue
std.string.String.pad_right_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.pad_right:

.globl std.string.String.char_at
std.string.String.char_at:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.String.char_at_entry:
  movq $0, rax
  jmp std.string.String.char_at_epilogue
std.string.String.char_at_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.char_at:

.globl std.string.String.repeat
std.string.String.repeat:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.String.repeat_entry:
  movq $0, rax
  jmp std.string.String.repeat_epilogue
std.string.String.repeat_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.repeat:

.globl std.string.uppercase
std.string.uppercase:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.string.uppercase_entry:
std.string.uppercase_block_0:
  movq [rbp + -64], rcx
  call std.string.to_upper
  movq $r1, rax
  jmp std.string.uppercase_epilogue
std.string.uppercase_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.uppercase:

.globl std.format.formatter.format_bool
std.format.formatter.format_bool:
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
std.format.formatter.format_bool_entry:
std.format.formatter.format_bool_block_0:
  movq [rbp + -64], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.format.formatter.format_bool_block_3
  jmp std.format.formatter.format_bool_block_5
std.format.formatter.format_bool_block_3:
  jmp std.format.formatter.format_bool_block_3
  movq [rel str_const_213], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.format.formatter.format_bool_epilogue
std.format.formatter.format_bool_block_5:
  movq [rel str_const_214], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.format.formatter.format_bool_epilogue
std.format.formatter.format_bool_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.formatter.format_bool:

.globl std.format.formatter.kebab_case
std.format.formatter.kebab_case:
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
std.format.formatter.kebab_case_entry:
std.format.formatter.kebab_case_block_0:
  movq [rbp + -64], rcx
  call std.format.formatter.snake_case
  movq [rel str_const_215], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rel str_const_216], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq $r1, rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.string.replace
  movq $r4, rax
  jmp std.format.formatter.kebab_case_epilogue
std.format.formatter.kebab_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.formatter.kebab_case:

.globl std.string.String.pad_left
std.string.String.pad_left:
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
std.string.String.pad_left_entry:
  movq $0, rax
  jmp std.string.String.pad_left_epilogue
std.string.String.pad_left_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.pad_left:

.globl std.string.String.trim
std.string.String.trim:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.string.String.trim_entry:
  movq $0, rax
  jmp std.string.String.trim_epilogue
std.string.String.trim_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.trim:

.globl std.string.String.last_index_of
std.string.String.last_index_of:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.String.last_index_of_entry:
  movq $0, rax
  jmp std.string.String.last_index_of_epilogue
std.string.String.last_index_of_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.last_index_of:

.globl std.format.index.pascal_case
std.format.index.pascal_case:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.format.index.pascal_case_entry:
std.format.index.pascal_case_block_0:
  movq [rbp + -64], rcx
  call std.format.formatter.pascal_case
  movq $r1, rax
  jmp std.format.index.pascal_case_epilogue
std.format.index.pascal_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.pascal_case:

.globl std.string.String.init
std.string.String.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.String.init_entry:
  movq $0, rax
  jmp std.string.String.init_epilogue
std.string.String.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.init:

.globl std.string.contains
std.string.contains:
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
std.string.contains_entry:
std.string.contains_block_0:
  movq [rbp + -72], rcx
  call lm_list_len
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r2, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.string.contains_block_7
  jmp std.string.contains_block_9
std.string.contains_block_7:
  jmp std.string.contains_block_7
  movq $18, rax
  jmp std.string.contains_epilogue
std.string.contains_block_9:
  movq $r2, rax
  cmpq $r4, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.string.contains_block_11
  jmp std.string.contains_block_13
std.string.contains_block_11:
  jmp std.string.contains_block_11
  movq $10, rax
  jmp std.string.contains_epilogue
std.string.contains_block_13:
  jmp std.string.contains_block_15
std.string.contains_block_15:
  movq $r4, rax
  subq $r2, rax
  movq rax, $r14
  movq $1, rax
  cmpq $r14, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.string.contains_block_18
  jmp std.string.contains_block_29
std.string.contains_block_18:
  jmp std.string.contains_block_18
  movq $1, rax
  addq $r2, rax
  movq rax, [rbp + -104]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -104], r8
  call substring
  movq $r18, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.string.contains_block_22
  jmp std.string.contains_block_24
std.string.contains_block_22:
  jmp std.string.contains_block_22
  movq $18, rax
  jmp std.string.contains_epilogue
std.string.contains_block_24:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -120]
  jmp std.string.contains_block_15
std.string.contains_block_29:
  movq $10, rax
  jmp std.string.contains_epilogue
std.string.contains_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.contains:

.globl std.format.index.format_int
std.format.index.format_int:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.format.index.format_int_entry:
std.format.index.format_int_block_0:
  movq [rbp + -64], rcx
  call std.format.formatter.format_int
  movq $r1, rax
  jmp std.format.index.format_int_epilogue
std.format.index.format_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.format_int:

.globl std.format.index.Format.truncate
std.format.index.Format.truncate:
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
std.format.index.Format.truncate_entry:
  movq $0, rax
  jmp std.format.index.Format.truncate_epilogue
std.format.index.Format.truncate_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.Format.truncate:

.globl std.string.starts_with
std.string.starts_with:
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
std.string.starts_with_entry:
std.string.starts_with_block_0:
  movq [rbp + -72], rcx
  call lm_list_len
  movq $r2, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.string.starts_with_block_5
  jmp std.string.starts_with_block_7
std.string.starts_with_block_5:
  jmp std.string.starts_with_block_5
  movq $18, rax
  jmp std.string.starts_with_epilogue
std.string.starts_with_block_7:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r2, rax
  cmpq $r8, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.string.starts_with_block_10
  jmp std.string.starts_with_block_12
std.string.starts_with_block_10:
  jmp std.string.starts_with_block_10
  movq $10, rax
  jmp std.string.starts_with_epilogue
std.string.starts_with_block_12:
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $r2, r8
  call substring
  movq $r13, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp std.string.starts_with_epilogue
std.string.starts_with_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.starts_with:

.globl std.format.index.pad_string
std.format.index.pad_string:
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
std.format.index.pad_string_entry:
std.format.index.pad_string_block_0:
  movq [rel str_const_217], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.format.formatter.pad_left
  movq $r3, rax
  jmp std.format.index.pad_string_epilogue
std.format.index.pad_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.pad_string:

.globl std.format.printf.__init__
std.format.printf.__init__:
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
std.format.printf.__init___entry:
  movq $0, rax
  jmp std.format.printf.__init___epilogue
std.format.printf.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.printf.__init__:

.globl std.format.formatter.format_float
std.format.formatter.format_float:
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
std.format.formatter.format_float_entry:
std.format.formatter.format_float_block_0:
  movq [rel str_const_218], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call lm_rt_str_format
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.format.formatter.format_float_epilogue
std.format.formatter.format_float_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.formatter.format_float:

.globl std.string.ends_with
std.string.ends_with:
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
std.string.ends_with_entry:
std.string.ends_with_block_0:
  movq [rbp + -72], rcx
  call lm_list_len
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r2, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.string.ends_with_block_7
  jmp std.string.ends_with_block_9
std.string.ends_with_block_7:
  jmp std.string.ends_with_block_7
  movq $18, rax
  jmp std.string.ends_with_epilogue
std.string.ends_with_block_9:
  movq $r2, rax
  cmpq $r4, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.string.ends_with_block_11
  jmp std.string.ends_with_block_13
std.string.ends_with_block_11:
  jmp std.string.ends_with_block_11
  movq $10, rax
  jmp std.string.ends_with_epilogue
std.string.ends_with_block_13:
  movq $r4, rax
  subq $r2, rax
  movq rax, $r13
  movq [rbp + -64], rcx
  movq $r13, rdx
  movq $r4, r8
  call substring
  movq $r14, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp std.string.ends_with_epilogue
std.string.ends_with_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.ends_with:

.globl std.format.index.title_case
std.format.index.title_case:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.format.index.title_case_entry:
std.format.index.title_case_block_0:
  movq [rbp + -64], rcx
  call std.format.formatter.title_case
  movq $r1, rax
  jmp std.format.index.title_case_epilogue
std.format.index.title_case_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.title_case:

.globl std.format.index.Format.center
std.format.index.Format.center:
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
std.format.index.Format.center_entry:
  movq $0, rax
  jmp std.format.index.Format.center_epilogue
std.format.index.Format.center_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.index.Format.center:

.globl std.string.replace
std.string.replace:
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
std.string.replace_entry:
std.string.replace_block_0:
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
  jne std.string.replace_block_7
  jmp std.string.replace_block_8
std.string.replace_block_7:
  jmp std.string.replace_block_7
  movq $0, rax
  jmp std.string.replace_epilogue
std.string.replace_block_8:
  movq [rel str_const_219], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  jmp std.string.replace_block_11
std.string.replace_block_11:
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
  jne std.string.replace_block_14
  jmp std.string.replace_block_37
std.string.replace_block_14:
  jmp std.string.replace_block_14
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
  jne std.string.replace_block_18
  jmp std.string.replace_block_24
std.string.replace_block_18:
  jmp std.string.replace_block_18
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
  jmp std.string.replace_block_36
std.string.replace_block_24:
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
  jmp std.string.replace_block_36
std.string.replace_block_36:
  jmp std.string.replace_block_11
std.string.replace_block_37:
  jmp std.string.replace_block_38
std.string.replace_block_38:
  movq [rbp + -176], rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  testq rax, rax
  jne std.string.replace_block_40
  jmp std.string.replace_block_52
std.string.replace_block_40:
  jmp std.string.replace_block_40
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
  jmp std.string.replace_block_38
std.string.replace_block_52:
  movq [rbp + -208], rax
  jmp std.string.replace_epilogue
std.string.replace_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.replace:

.globl std.format.formatter.format_int
std.format.formatter.format_int:
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
std.format.formatter.format_int_entry:
std.format.formatter.format_int_block_0:
  movq [rel str_const_220], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call lm_rt_str_format
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.format.formatter.format_int_epilogue
std.format.formatter.format_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.format.formatter.format_int:

.globl std.string.String.starts_with
std.string.String.starts_with:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.string.String.starts_with_entry:
  movq $0, rax
  jmp std.string.String.starts_with_epilogue
std.string.String.starts_with_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.String.starts_with:

.globl std.string.to_upper
std.string.to_upper:
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
std.string.to_upper_entry:
std.string.to_upper_block_0:
  movq [rel str_const_221], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.string.to_upper_block_5
std.string.to_upper_block_5:
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.string.to_upper_block_7
  jmp std.string.to_upper_block_20
std.string.to_upper_block_7:
  jmp std.string.to_upper_block_7
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -88], r8
  call substring
  movq $r10, rcx
  call std.string._char_to_upper
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
  jmp std.string.to_upper_block_5
std.string.to_upper_block_20:
  movq [rbp + -104], rax
  jmp std.string.to_upper_epilogue
std.string.to_upper_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.to_upper:

.globl std.string.substr
std.string.substr:
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
std.string.substr_entry:
std.string.substr_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call substring
  movq $r3, rax
  jmp std.string.substr_epilogue
std.string.substr_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.substr:

.globl std.string.substring
std.string.substring:
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
std.string.substring_entry:
std.string.substring_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call substring
  movq $r3, rax
  jmp std.string.substring_epilogue
std.string.substring_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.substring:

.globl std.string.__init__
std.string.__init__:
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
std.string.__init___entry:
  movq $0, rax
  jmp std.string.__init___epilogue
std.string.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.string.__init__:

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

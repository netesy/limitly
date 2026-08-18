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
  .string ""
.align 8
str_const_3:
  .string ""
.align 8
str_const_4:
  .string " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
.align 8
str_const_5:
  .string "abc"
.align 8
str_const_6:
  .string "abc"
.align 8
str_const_7:
  .string "a"
.align 8
str_const_8:
  .string "a"
.align 8
str_const_9:
  .string "A"
.align 8
str_const_10:
  .string "twice"
.align 8
str_const_11:
  .string "positive"
.align 8
str_const_12:
  .string "twice"
.align 8
str_const_13:
  .string "bad"
.align 8
str_const_14:
  .string "ERR"
.align 8
str_const_15:
  .string ""
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
  .string "a"
.align 8
str_const_20:
  .string "A"
.align 8
str_const_21:
  .string "b"
.align 8
str_const_22:
  .string "B"
.align 8
str_const_23:
  .string "c"
.align 8
str_const_24:
  .string "C"
.align 8
str_const_25:
  .string "d"
.align 8
str_const_26:
  .string "D"
.align 8
str_const_27:
  .string "e"
.align 8
str_const_28:
  .string "E"
.align 8
str_const_29:
  .string "f"
.align 8
str_const_30:
  .string "F"
.align 8
str_const_31:
  .string "g"
.align 8
str_const_32:
  .string "G"
.align 8
str_const_33:
  .string "h"
.align 8
str_const_34:
  .string "H"
.align 8
str_const_35:
  .string "i"
.align 8
str_const_36:
  .string "I"
.align 8
str_const_37:
  .string "j"
.align 8
str_const_38:
  .string "J"
.align 8
str_const_39:
  .string "k"
.align 8
str_const_40:
  .string "K"
.align 8
str_const_41:
  .string "l"
.align 8
str_const_42:
  .string "L"
.align 8
str_const_43:
  .string "m"
.align 8
str_const_44:
  .string "M"
.align 8
str_const_45:
  .string "n"
.align 8
str_const_46:
  .string "N"
.align 8
str_const_47:
  .string "o"
.align 8
str_const_48:
  .string "O"
.align 8
str_const_49:
  .string "p"
.align 8
str_const_50:
  .string "P"
.align 8
str_const_51:
  .string "q"
.align 8
str_const_52:
  .string "Q"
.align 8
str_const_53:
  .string "r"
.align 8
str_const_54:
  .string "R"
.align 8
str_const_55:
  .string "s"
.align 8
str_const_56:
  .string "S"
.align 8
str_const_57:
  .string "t"
.align 8
str_const_58:
  .string "T"
.align 8
str_const_59:
  .string "u"
.align 8
str_const_60:
  .string "U"
.align 8
str_const_61:
  .string "v"
.align 8
str_const_62:
  .string "V"
.align 8
str_const_63:
  .string "w"
.align 8
str_const_64:
  .string "W"
.align 8
str_const_65:
  .string "x"
.align 8
str_const_66:
  .string "X"
.align 8
str_const_67:
  .string "y"
.align 8
str_const_68:
  .string "Y"
.align 8
str_const_69:
  .string "z"
.align 8
str_const_70:
  .string "Z"
.align 8
str_const_71:
  .string "A"
.align 8
str_const_72:
  .string "a"
.align 8
str_const_73:
  .string "B"
.align 8
str_const_74:
  .string "b"
.align 8
str_const_75:
  .string "C"
.align 8
str_const_76:
  .string "c"
.align 8
str_const_77:
  .string "D"
.align 8
str_const_78:
  .string "d"
.align 8
str_const_79:
  .string "E"
.align 8
str_const_80:
  .string "e"
.align 8
str_const_81:
  .string "F"
.align 8
str_const_82:
  .string "f"
.align 8
str_const_83:
  .string "G"
.align 8
str_const_84:
  .string "g"
.align 8
str_const_85:
  .string "H"
.align 8
str_const_86:
  .string "h"
.align 8
str_const_87:
  .string "I"
.align 8
str_const_88:
  .string "i"
.align 8
str_const_89:
  .string "J"
.align 8
str_const_90:
  .string "j"
.align 8
str_const_91:
  .string "K"
.align 8
str_const_92:
  .string "k"
.align 8
str_const_93:
  .string "L"
.align 8
str_const_94:
  .string "l"
.align 8
str_const_95:
  .string "M"
.align 8
str_const_96:
  .string "m"
.align 8
str_const_97:
  .string "N"
.align 8
str_const_98:
  .string "n"
.align 8
str_const_99:
  .string "O"
.align 8
str_const_100:
  .string "o"
.align 8
str_const_101:
  .string "P"
.align 8
str_const_102:
  .string "p"
.align 8
str_const_103:
  .string "Q"
.align 8
str_const_104:
  .string "q"
.align 8
str_const_105:
  .string "R"
.align 8
str_const_106:
  .string "r"
.align 8
str_const_107:
  .string "S"
.align 8
str_const_108:
  .string "s"
.align 8
str_const_109:
  .string "T"
.align 8
str_const_110:
  .string "t"
.align 8
str_const_111:
  .string "U"
.align 8
str_const_112:
  .string "u"
.align 8
str_const_113:
  .string "V"
.align 8
str_const_114:
  .string "v"
.align 8
str_const_115:
  .string "W"
.align 8
str_const_116:
  .string "w"
.align 8
str_const_117:
  .string "X"
.align 8
str_const_118:
  .string "x"
.align 8
str_const_119:
  .string "Y"
.align 8
str_const_120:
  .string "y"
.align 8
str_const_121:
  .string "Z"
.align 8
str_const_122:
  .string "z"
.align 8
str_const_123:
  .string " "
.align 8
str_const_124:
  .string "	"
.align 8
str_const_125:
  .string "
"
.align 8
str_const_126:
  .string ""
.align 8
str_const_127:
  .string " "
.align 8
str_const_128:
  .string "	"
.align 8
str_const_129:
  .string "
"
.align 8
str_const_130:
  .string ""
.align 8
str_const_131:
  .string "ERR"
.align 8
str_const_132:
  .string ""
.align 8
str_const_133:
  .string ""
.align 8
str_const_134:
  .string ""
.align 8
str_const_135:
  .string "ERR"
.align 8
str_const_136:
  .string ""
.align 8
str_const_137:
  .string "ERR"
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
  sub rsp, 168
main_entry:
main_block_0:
  call std.string.__init__
  call std.option.__init__
  call std.result.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  cmpq $25, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne main_block_5
  jmp main_block_7
main_block_5:
  jmp main_block_5
  movq $9, rax
  jmp main_epilogue
main_block_7:
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -80], rcx
  movq [rbp + -88], rdx
  call std.string.starts_with
  movq $r8, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne main_block_13
  jmp main_block_15
main_block_13:
  jmp main_block_13
  movq $17, rax
  jmp main_epilogue
main_block_15:
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  call std.string.uppercase
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r14, rax
  cmpq [rbp + -112], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne main_block_20
  jmp main_block_22
main_block_20:
  jmp main_block_20
  movq $25, rax
  jmp main_epilogue
main_block_22:
  movq $17, rcx
  call std.option.Some
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq $r20, rcx
  movq [rbp + -128], rdx
  call std.option.Option.map
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r22, rcx
  movq [rbp + -136], rdx
  call std.option.Option.filter
  movq $r24, rcx
  call std.option.Option.unwrap
  movq $r26, rax
  cmpq $33, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  testq rax, rax
  jne main_block_33
  jmp main_block_35
main_block_33:
  jmp main_block_33
  movq $33, rax
  jmp main_epilogue
main_block_35:
  call std.option.None
  movq $r31, rcx
  movq $73, rdx
  call std.option.Option.unwrap_or
  movq $r34, rax
  cmpq $73, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne main_block_42
  jmp main_block_44
main_block_42:
  jmp main_block_42
  movq $41, rax
  jmp main_epilogue
main_block_44:
  movq $25, rcx
  call std.result.Ok
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq $r40, rcx
  movq [rbp + -160], rdx
  call std.result.Result.map
  movq $r42, rcx
  call std.result.Result.unwrap
  movq $r44, rax
  cmpq $49, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  testq rax, rax
  jne main_block_53
  jmp main_block_55
main_block_53:
  jmp main_block_53
  movq $49, rax
  jmp main_epilogue
main_block_55:
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -176], rcx
  call std.result.Err
  movq $r50, rcx
  call std.result.Result.is_err
  movq $r52, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  testq rax, rax
  jne main_block_62
  jmp main_block_64
main_block_62:
  jmp main_block_62
  movq $57, rax
  jmp main_epilogue
main_block_64:
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

.globl std.option.__init__
std.option.__init__:
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
std.option.__init___entry:
  movq $0, rax
  jmp std.option.__init___epilogue
std.option.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.option.__init__:

.globl std.option.Option.init
std.option.Option.init:
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
std.option.Option.init_entry:
  movq $0, rax
  jmp std.option.Option.init_epilogue
std.option.Option.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.option.Option.init:

.globl std.option.Option.filter
std.option.Option.filter:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.option.Option.filter_entry:
  movq $0, rax
  jmp std.option.Option.filter_epilogue
std.option.Option.filter_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.option.Option.filter:

.globl std.option.Option.unwrap
std.option.Option.unwrap:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.option.Option.unwrap_entry:
  movq $0, rax
  jmp std.option.Option.unwrap_epilogue
std.option.Option.unwrap_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.option.Option.unwrap:

.globl std.option.Option.is_none
std.option.Option.is_none:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.option.Option.is_none_entry:
  movq $0, rax
  jmp std.option.Option.is_none_epilogue
std.option.Option.is_none_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.option.Option.is_none:

.globl std.option.Option.is_some
std.option.Option.is_some:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.option.Option.is_some_entry:
  movq $0, rax
  jmp std.option.Option.is_some_epilogue
std.option.Option.is_some_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.option.Option.is_some:

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

.globl std.result.Err
std.result.Err:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.result.Err_entry:
std.result.Err_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq $10, rdx
  movq $2, r8
  movq [rbp + -64], r9
  call std.result.Result.init
  movq [rbp + -72], rax
  jmp std.result.Err_epilogue
std.result.Err_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.result.Err:

.globl std.result.Ok
std.result.Ok:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.result.Ok_entry:
std.result.Ok_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq $18, rdx
  movq [rbp + -64], r8
  movq $2, r9
  call std.result.Result.init
  movq [rbp + -72], rax
  jmp std.result.Ok_epilogue
std.result.Ok_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.result.Ok:

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

.globl std.result.Result.unwrap_err
std.result.Result.unwrap_err:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.result.Result.unwrap_err_entry:
  movq $0, rax
  jmp std.result.Result.unwrap_err_epilogue
std.result.Result.unwrap_err_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.result.Result.unwrap_err:

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

.globl std.result.Result.unwrap_or
std.result.Result.unwrap_or:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.result.Result.unwrap_or_entry:
  movq $0, rax
  jmp std.result.Result.unwrap_or_epilogue
std.result.Result.unwrap_or_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.result.Result.unwrap_or:

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
  movq [rel str_const_4], rcx
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

.globl positive
positive:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
positive_entry:
positive_block_0:
  movq [rbp + -64], rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp positive_epilogue
positive_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_positive:

.globl std.option.Option.map
std.option.Option.map:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.option.Option.map_entry:
  movq $0, rax
  jmp std.option.Option.map_epilogue
std.option.Option.map_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.option.Option.map:

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
  movq [rel str_const_14], rcx
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
  movq [rel str_const_15], rcx
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
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_17], rcx
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
  movq [rel str_const_18], rcx
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

.globl std.result.Result.init
std.result.Result.init:
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
std.result.Result.init_entry:
  movq $0, rax
  jmp std.result.Result.init_epilogue
std.result.Result.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.result.Result.init:

.globl std.option.Some
std.option.Some:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.option.Some_entry:
std.option.Some_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq $18, rdx
  movq [rbp + -64], r8
  call std.option.Option.init
  movq [rbp + -72], rax
  jmp std.option.Some_epilogue
std.option.Some_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.option.Some:

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
  movq [rel str_const_19], rcx
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
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_5:
  movq [rel str_const_21], rcx
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
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_10:
  movq [rel str_const_23], rcx
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
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_15:
  movq [rel str_const_25], rcx
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
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_20:
  movq [rel str_const_27], rcx
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
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_25:
  movq [rel str_const_29], rcx
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
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_30:
  movq [rel str_const_31], rcx
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
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_35:
  movq [rel str_const_33], rcx
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
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_40:
  movq [rel str_const_35], rcx
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
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_45:
  movq [rel str_const_37], rcx
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
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_50:
  movq [rel str_const_39], rcx
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
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_55:
  movq [rel str_const_41], rcx
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
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_60:
  movq [rel str_const_43], rcx
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
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_65:
  movq [rel str_const_45], rcx
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
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_70:
  movq [rel str_const_47], rcx
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
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_75:
  movq [rel str_const_49], rcx
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
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -448], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_80:
  movq [rel str_const_51], rcx
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
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -472], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_85:
  movq [rel str_const_53], rcx
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
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -496], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_90:
  movq [rel str_const_55], rcx
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
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -520], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_95:
  movq [rel str_const_57], rcx
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
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -544]
  movq [rbp + -544], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_100:
  movq [rel str_const_59], rcx
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
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -568]
  movq [rbp + -568], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_105:
  movq [rel str_const_61], rcx
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
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -592]
  movq [rbp + -592], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_110:
  movq [rel str_const_63], rcx
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
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -616], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_115:
  movq [rel str_const_65], rcx
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
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_120:
  movq [rel str_const_67], rcx
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
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -664]
  movq [rbp + -664], rax
  jmp std.string._char_to_upper_epilogue
std.string._char_to_upper_block_125:
  movq [rel str_const_69], rcx
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
  movq [rel str_const_70], rcx
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

.globl std.result.__init__
std.result.__init__:
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
std.result.__init___entry:
  movq $0, rax
  jmp std.result.__init___epilogue
std.result.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.result.__init__:

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
  movq [rel str_const_71], rcx
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
  movq [rel str_const_72], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_5:
  movq [rel str_const_73], rcx
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
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_10:
  movq [rel str_const_75], rcx
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
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_15:
  movq [rel str_const_77], rcx
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
  movq [rel str_const_78], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_20:
  movq [rel str_const_79], rcx
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
  movq [rel str_const_80], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_25:
  movq [rel str_const_81], rcx
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
  movq [rel str_const_82], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_30:
  movq [rel str_const_83], rcx
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
  movq [rel str_const_84], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_35:
  movq [rel str_const_85], rcx
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
  movq [rel str_const_86], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_40:
  movq [rel str_const_87], rcx
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
  movq [rel str_const_88], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_45:
  movq [rel str_const_89], rcx
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
  movq [rel str_const_90], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_50:
  movq [rel str_const_91], rcx
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
  movq [rel str_const_92], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_55:
  movq [rel str_const_93], rcx
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
  movq [rel str_const_94], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_60:
  movq [rel str_const_95], rcx
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
  movq [rel str_const_96], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_65:
  movq [rel str_const_97], rcx
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
  movq [rel str_const_98], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_70:
  movq [rel str_const_99], rcx
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
  movq [rel str_const_100], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_75:
  movq [rel str_const_101], rcx
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
  movq [rel str_const_102], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -448], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_80:
  movq [rel str_const_103], rcx
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
  movq [rel str_const_104], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -472], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_85:
  movq [rel str_const_105], rcx
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
  movq [rel str_const_106], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -496], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_90:
  movq [rel str_const_107], rcx
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
  movq [rel str_const_108], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -520], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_95:
  movq [rel str_const_109], rcx
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
  movq [rel str_const_110], rcx
  call lm_box_string
  movq rax, [rbp + -544]
  movq [rbp + -544], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_100:
  movq [rel str_const_111], rcx
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
  movq [rel str_const_112], rcx
  call lm_box_string
  movq rax, [rbp + -568]
  movq [rbp + -568], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_105:
  movq [rel str_const_113], rcx
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
  movq [rel str_const_114], rcx
  call lm_box_string
  movq rax, [rbp + -592]
  movq [rbp + -592], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_110:
  movq [rel str_const_115], rcx
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
  movq [rel str_const_116], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -616], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_115:
  movq [rel str_const_117], rcx
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
  movq [rel str_const_118], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_120:
  movq [rel str_const_119], rcx
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
  movq [rel str_const_120], rcx
  call lm_box_string
  movq rax, [rbp + -664]
  movq [rbp + -664], rax
  jmp std.string._char_to_lower_epilogue
std.string._char_to_lower_block_125:
  movq [rel str_const_121], rcx
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
  movq [rel str_const_122], rcx
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

.globl std.result.Result.unwrap
std.result.Result.unwrap:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.result.Result.unwrap_entry:
  movq $0, rax
  jmp std.result.Result.unwrap_epilogue
std.result.Result.unwrap_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.result.Result.unwrap:

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

.globl std.option.Option.unwrap_or
std.option.Option.unwrap_or:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.option.Option.unwrap_or_entry:
  movq $0, rax
  jmp std.option.Option.unwrap_or_epilogue
std.option.Option.unwrap_or_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.option.Option.unwrap_or:

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
  movq [rel str_const_123], rcx
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
  movq [rel str_const_124], rcx
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
  movq [rel str_const_125], rcx
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
  movq [rel str_const_126], rcx
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
  movq [rel str_const_127], rcx
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
  movq [rel str_const_128], rcx
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
  movq [rel str_const_129], rcx
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
  movq [rel str_const_130], rcx
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
  movq [rel str_const_131], rcx
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

.globl std.option.None
std.option.None:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.option.None_entry:
std.option.None_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  movq $10, rdx
  movq $2, r8
  call std.option.Option.init
  movq [rbp + -64], rax
  jmp std.option.None_epilogue
std.option.None_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.option.None:

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
  movq [rel str_const_132], rcx
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
  movq [rel str_const_133], rcx
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

.globl std.result.Result.map
std.result.Result.map:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.result.Result.map_entry:
  movq $0, rax
  jmp std.result.Result.map_epilogue
std.result.Result.map_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.result.Result.map:

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
  movq [rel str_const_134], rcx
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
  movq [rel str_const_135], rcx
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
  movq [rel str_const_136], rcx
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
  movq [rel str_const_137], rcx
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

.globl std.result.Result.is_ok
std.result.Result.is_ok:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.result.Result.is_ok_entry:
  movq $0, rax
  jmp std.result.Result.is_ok_epilogue
std.result.Result.is_ok_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.result.Result.is_ok:

.globl std.result.Result.is_err
std.result.Result.is_err:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.result.Result.is_err_entry:
  movq $0, rax
  jmp std.result.Result.is_err_epilogue
std.result.Result.is_err_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.result.Result.is_err:

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

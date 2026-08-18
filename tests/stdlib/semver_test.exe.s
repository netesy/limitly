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
  .string "0"
.align 8
str_const_3:
  .string "abcdefghijklmnopqrstuvwxyz"
.align 8
str_const_4:
  .string "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
.align 8
str_const_5:
  .string "123456789"
.align 8
str_const_6:
  .string "-"
.align 8
str_const_7:
  .string "."
.align 8
str_const_8:
  .string "+"
.align 8
str_const_9:
  .string ""
.align 8
str_const_10:
  .string "123456789"
.align 8
str_const_11:
  .string ""
.align 8
str_const_12:
  .string "."
.align 8
str_const_13:
  .string ""
.align 8
str_const_14:
  .string ""
.align 8
str_const_15:
  .string "0"
.align 8
str_const_16:
  .string "1"
.align 8
str_const_17:
  .string "2"
.align 8
str_const_18:
  .string "3"
.align 8
str_const_19:
  .string "4"
.align 8
str_const_20:
  .string "5"
.align 8
str_const_21:
  .string "6"
.align 8
str_const_22:
  .string "7"
.align 8
str_const_23:
  .string "8"
.align 8
str_const_24:
  .string "9"
.align 8
str_const_25:
  .string "Running SemVer compatibility tests..."
.align 8
str_const_26:
  .string "1.2.3"
.align 8
str_const_27:
  .string "1.5.0"
.align 8
str_const_28:
  .string "2.0.0"
.align 8
str_const_29:
  .string "1.1.0"
.align 8
str_const_30:
  .string "1.5.0 should be compatible with 1.2.3"
.align 8
str_const_31:
  .string "2.0.0 should not be compatible with 1.2.3"
.align 8
str_const_32:
  .string "1.1.0 (older) should not be compatible with 1.2.3"
.align 8
str_const_33:
  .string "0.2.3"
.align 8
str_const_34:
  .string "0.2.5"
.align 8
str_const_35:
  .string "0.3.0"
.align 8
str_const_36:
  .string "0.2.5 is compatible with 0.2.3"
.align 8
str_const_37:
  .string "0.3.0 is not compatible with 0.2.3"
.align 8
str_const_38:
  .string "0.0.5"
.align 8
str_const_39:
  .string "0.0.5"
.align 8
str_const_40:
  .string "0.0.6"
.align 8
str_const_41:
  .string "0.0.5 is compatible with 0.0.5"
.align 8
str_const_42:
  .string "0.0.6 is not compatible with 0.0.5"
.align 8
str_const_43:
  .string "Compatibility tests passed!"
.align 8
str_const_44:
  .string "Running SemVer comparison tests..."
.align 8
str_const_45:
  .string "1.2.3"
.align 8
str_const_46:
  .string "2.0.0"
.align 8
str_const_47:
  .string "1.3.0"
.align 8
str_const_48:
  .string "1.2.4"
.align 8
str_const_49:
  .string "1.2.3 < 2.0.0"
.align 8
str_const_50:
  .string "2.0.0 > 1.2.3"
.align 8
str_const_51:
  .string "1.2.3 < 1.3.0"
.align 8
str_const_52:
  .string "1.3.0 > 1.2.3"
.align 8
str_const_53:
  .string "1.2.3 < 1.2.4"
.align 8
str_const_54:
  .string "1.2.3 == 1.2.3"
.align 8
str_const_55:
  .string "1.0.0-alpha"
.align 8
str_const_56:
  .string "1.0.0"
.align 8
str_const_57:
  .string "1.0.0-alpha < 1.0.0"
.align 8
str_const_58:
  .string "1.0.0 > 1.0.0-alpha"
.align 8
str_const_59:
  .string "1.0.0-alpha"
.align 8
str_const_60:
  .string "1.0.0-alpha.1"
.align 8
str_const_61:
  .string "1.0.0-alpha.beta"
.align 8
str_const_62:
  .string "1.0.0-beta"
.align 8
str_const_63:
  .string "1.0.0-beta.2"
.align 8
str_const_64:
  .string "1.0.0-beta.11"
.align 8
str_const_65:
  .string "1.0.0-rc.1"
.align 8
str_const_66:
  .string "alpha < alpha.1"
.align 8
str_const_67:
  .string "alpha.1 < alpha.beta (numeric < non-numeric)"
.align 8
str_const_68:
  .string "alpha.beta < beta"
.align 8
str_const_69:
  .string "beta < beta.2"
.align 8
str_const_70:
  .string "beta.2 < beta.11 (numeric comparison 2 < 11)"
.align 8
str_const_71:
  .string "beta.11 < rc.1"
.align 8
str_const_72:
  .string "1.2.3+build.1"
.align 8
str_const_73:
  .string "1.2.3+build.2"
.align 8
str_const_74:
  .string "1.2.3+build.1 == 1.2.3+build.2 in precedence"
.align 8
str_const_75:
  .string "vb1 should equal vb2"
.align 8
str_const_76:
  .string "Comparison tests passed!"
.align 8
str_const_77:
  .string "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-"
.align 8
str_const_78:
  .string "Running SemVer formatting tests..."
.align 8
str_const_79:
  .string "1.2.3-alpha.1+build.12"
.align 8
str_const_80:
  .string "1.2.3-alpha.1+build.12"
.align 8
str_const_81:
  .string "to_string matches input"
.align 8
str_const_82:
  .string "2.0.1"
.align 8
str_const_83:
  .string "2.0.1"
.align 8
str_const_84:
  .string "to_string matches input (simple)"
.align 8
str_const_85:
  .string "Formatting tests passed!"
.align 8
str_const_86:
  .string "0"
.align 8
str_const_87:
  .string "Running SemVer parsing tests..."
.align 8
str_const_88:
  .string "1.2.3"
.align 8
str_const_89:
  .string "Failed to parse 1.2.3"
.align 8
str_const_90:
  .string "v1.major should be 1"
.align 8
str_const_91:
  .string "v1.minor should be 2"
.align 8
str_const_92:
  .string "v1.patch should be 3"
.align 8
str_const_93:
  .string ""
.align 8
str_const_94:
  .string "v1.prerelease should be empty"
.align 8
str_const_95:
  .string ""
.align 8
str_const_96:
  .string "v1.build should be empty"
.align 8
str_const_97:
  .string "0.0.0"
.align 8
str_const_98:
  .string "Failed to parse 0.0.0"
.align 8
str_const_99:
  .string "v2.major should be 0"
.align 8
str_const_100:
  .string "v2.minor should be 0"
.align 8
str_const_101:
  .string "v2.patch should be 0"
.align 8
str_const_102:
  .string "1.2.3-alpha.1"
.align 8
str_const_103:
  .string "Failed to parse 1.2.3-alpha.1"
.align 8
str_const_104:
  .string "alpha.1"
.align 8
str_const_105:
  .string "v3.prerelease should be alpha.1"
.align 8
str_const_106:
  .string ""
.align 8
str_const_107:
  .string "v3.build should be empty"
.align 8
str_const_108:
  .string "1.2.3+build.12"
.align 8
str_const_109:
  .string "Failed to parse 1.2.3+build.12"
.align 8
str_const_110:
  .string ""
.align 8
str_const_111:
  .string "v4.prerelease should be empty"
.align 8
str_const_112:
  .string "build.12"
.align 8
str_const_113:
  .string "v4.build should be build.12"
.align 8
str_const_114:
  .string "1.2.3-beta.2+20141223"
.align 8
str_const_115:
  .string "Failed to parse 1.2.3-beta.2+20141223"
.align 8
str_const_116:
  .string "beta.2"
.align 8
str_const_117:
  .string "v5.prerelease should be beta.2"
.align 8
str_const_118:
  .string "20141223"
.align 8
str_const_119:
  .string "v5.build should be 20141223"
.align 8
str_const_120:
  .string ""
.align 8
str_const_121:
  .string "Empty string should fail"
.align 8
str_const_122:
  .string "1.20000000000000000e+00"
.align 8
str_const_123:
  .string "Missing patch version should fail"
.align 8
str_const_124:
  .string "1.2.3.4"
.align 8
str_const_125:
  .string "Four parts should fail"
.align 8
str_const_126:
  .string "01.2.3"
.align 8
str_const_127:
  .string "Leading zeroes in core version should fail"
.align 8
str_const_128:
  .string "1.2.3-alpha.01"
.align 8
str_const_129:
  .string "Leading zeroes in numeric pre-release should fail"
.align 8
str_const_130:
  .string "1.2.3-alpha..1"
.align 8
str_const_131:
  .string "Empty pre-release identifiers should fail"
.align 8
str_const_132:
  .string "1.2.3+build..12"
.align 8
str_const_133:
  .string "Empty build identifiers should fail"
.align 8
str_const_134:
  .string "1.2.3-alpha_1"
.align 8
str_const_135:
  .string "Invalid characters in pre-release should fail"
.align 8
str_const_136:
  .string "Parsing tests passed!"
.align 8
str_const_137:
  .string "=== SemVer Test Suite ==="
.align 8
str_const_138:
  .string "Parsing tests failed"
.align 8
str_const_139:
  .string "Comparison tests failed"
.align 8
str_const_140:
  .string "Compatibility tests failed"
.align 8
str_const_141:
  .string "Formatting tests failed"
.align 8
str_const_142:
  .string "All SemVer tests completed successfully."
.align 8
str_const_143:
  .string ""
.align 8
str_const_144:
  .string "+"
.align 8
str_const_145:
  .string ""
.align 8
str_const_146:
  .string "-"
.align 8
str_const_147:
  .string ""
.align 8
str_const_148:
  .string "."
.align 8
str_const_149:
  .string "."
.align 8
str_const_150:
  .string "."
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
  sub rsp, 168
main_entry:
main_block_0:
  call std.semver.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq [rel str_const_137], rcx
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
  call test_parsing
  movq $r2, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_138], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_comparison
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_139], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  call test_compatibility
  movq $r12, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_140], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  call test_formatting
  movq $r17, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_141], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rel str_const_142], rcx
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

.globl std.semver.__init__
std.semver.__init__:
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
std.semver.__init___entry:
  movq $0, rax
  jmp std.semver.__init___epilogue
std.semver.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.__init__:

.globl std.semver.is_valid_build_id
std.semver.is_valid_build_id:
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
std.semver.is_valid_build_id_entry:
std.semver.is_valid_build_id_block_0:
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.semver.is_valid_build_id_block_3
  jmp std.semver.is_valid_build_id_block_5
std.semver.is_valid_build_id_block_3:
  jmp std.semver.is_valid_build_id_block_3
  movq $10, rax
  jmp std.semver.is_valid_build_id_epilogue
std.semver.is_valid_build_id_block_5:
  jmp std.semver.is_valid_build_id_block_7
std.semver.is_valid_build_id_block_7:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r6, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.semver.is_valid_build_id_block_10
  jmp std.semver.is_valid_build_id_block_25
std.semver.is_valid_build_id_block_10:
  jmp std.semver.is_valid_build_id_block_10
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -96], r8
  call substring
  movq $r12, rcx
  call std.semver.is_valid_char
  movq $r13, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.semver.is_valid_build_id_block_18
  jmp std.semver.is_valid_build_id_block_20
std.semver.is_valid_build_id_block_18:
  jmp std.semver.is_valid_build_id_block_18
  movq $10, rax
  jmp std.semver.is_valid_build_id_epilogue
std.semver.is_valid_build_id_block_20:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.semver.is_valid_build_id_block_7
std.semver.is_valid_build_id_block_25:
  movq $18, rax
  jmp std.semver.is_valid_build_id_epilogue
std.semver.is_valid_build_id_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.is_valid_build_id:

.globl std.semver.is_valid_prerelease_id
std.semver.is_valid_prerelease_id:
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
std.semver.is_valid_prerelease_id_entry:
std.semver.is_valid_prerelease_id_block_0:
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.semver.is_valid_prerelease_id_block_3
  jmp std.semver.is_valid_prerelease_id_block_5
std.semver.is_valid_prerelease_id_block_3:
  jmp std.semver.is_valid_prerelease_id_block_3
  movq $10, rax
  jmp std.semver.is_valid_prerelease_id_epilogue
std.semver.is_valid_prerelease_id_block_5:
  jmp std.semver.is_valid_prerelease_id_block_7
std.semver.is_valid_prerelease_id_block_7:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r6, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.semver.is_valid_prerelease_id_block_10
  jmp std.semver.is_valid_prerelease_id_block_25
std.semver.is_valid_prerelease_id_block_10:
  jmp std.semver.is_valid_prerelease_id_block_10
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -96], r8
  call substring
  movq $r12, rcx
  call std.semver.is_valid_char
  movq $r13, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.semver.is_valid_prerelease_id_block_18
  jmp std.semver.is_valid_prerelease_id_block_20
std.semver.is_valid_prerelease_id_block_18:
  jmp std.semver.is_valid_prerelease_id_block_18
  movq $10, rax
  jmp std.semver.is_valid_prerelease_id_epilogue
std.semver.is_valid_prerelease_id_block_20:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.semver.is_valid_prerelease_id_block_7
std.semver.is_valid_prerelease_id_block_25:
  movq [rbp + -64], rcx
  call std.semver.is_numeric
  movq $r21, rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.semver.is_valid_prerelease_id_block_29
  jmp std.semver.is_valid_prerelease_id_block_45
std.semver.is_valid_prerelease_id_block_29:
  jmp std.semver.is_valid_prerelease_id_block_29
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r25, rax
  cmpq $9, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.semver.is_valid_prerelease_id_block_34
  jmp std.semver.is_valid_prerelease_id_block_41
std.semver.is_valid_prerelease_id_block_34:
  jmp std.semver.is_valid_prerelease_id_block_34
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $9, r8
  call substring
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r30, rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  jmp std.semver.is_valid_prerelease_id_block_41
std.semver.is_valid_prerelease_id_block_41:
  movq [rbp + -144], rax
  testq rax, rax
  jne std.semver.is_valid_prerelease_id_block_42
  jmp std.semver.is_valid_prerelease_id_block_44
std.semver.is_valid_prerelease_id_block_42:
  jmp std.semver.is_valid_prerelease_id_block_42
  movq $10, rax
  jmp std.semver.is_valid_prerelease_id_epilogue
std.semver.is_valid_prerelease_id_block_44:
  jmp std.semver.is_valid_prerelease_id_block_45
std.semver.is_valid_prerelease_id_block_45:
  movq $18, rax
  jmp std.semver.is_valid_prerelease_id_epilogue
std.semver.is_valid_prerelease_id_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.is_valid_prerelease_id:

.globl std.semver.byte_ord
std.semver.byte_ord:
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
  mov [rbp + -64], rcx
std.semver.byte_ord_entry:
std.semver.byte_ord_block_0:
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  jmp std.semver.byte_ord_block_3
std.semver.byte_ord_block_3:
  movq [rbp + -72], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.semver.byte_ord_block_6
  jmp std.semver.byte_ord_block_21
std.semver.byte_ord_block_6:
  jmp std.semver.byte_ord_block_6
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -88]
  movq [rbp + -72], rcx
  movq $1, rdx
  movq [rbp + -88], r8
  call substring
  movq $r9, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.semver.byte_ord_block_12
  jmp std.semver.byte_ord_block_16
std.semver.byte_ord_block_12:
  jmp std.semver.byte_ord_block_12
  movq $777, rax
  addq $1, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  jmp std.semver.byte_ord_epilogue
std.semver.byte_ord_block_16:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.semver.byte_ord_block_3
std.semver.byte_ord_block_21:
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  jmp std.semver.byte_ord_block_25
std.semver.byte_ord_block_25:
  movq [rbp + -120], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r20, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.semver.byte_ord_block_28
  jmp std.semver.byte_ord_block_43
std.semver.byte_ord_block_28:
  jmp std.semver.byte_ord_block_28
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -136]
  movq [rbp + -120], rcx
  movq $1, rdx
  movq [rbp + -136], r8
  call substring
  movq $r26, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  testq rax, rax
  jne std.semver.byte_ord_block_34
  jmp std.semver.byte_ord_block_38
std.semver.byte_ord_block_34:
  jmp std.semver.byte_ord_block_34
  movq $521, rax
  addq $1, rax
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  jmp std.semver.byte_ord_epilogue
std.semver.byte_ord_block_38:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -160]
  jmp std.semver.byte_ord_block_25
std.semver.byte_ord_block_43:
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  jmp std.semver.byte_ord_block_47
std.semver.byte_ord_block_47:
  movq [rbp + -168], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r37, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne std.semver.byte_ord_block_50
  jmp std.semver.byte_ord_block_65
std.semver.byte_ord_block_50:
  jmp std.semver.byte_ord_block_50
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -184]
  movq [rbp + -168], rcx
  movq $1, rdx
  movq [rbp + -184], r8
  call substring
  movq $r43, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  testq rax, rax
  jne std.semver.byte_ord_block_56
  jmp std.semver.byte_ord_block_60
std.semver.byte_ord_block_56:
  jmp std.semver.byte_ord_block_56
  movq $385, rax
  addq $1, rax
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  jmp std.semver.byte_ord_epilogue
std.semver.byte_ord_block_60:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -208]
  jmp std.semver.byte_ord_block_47
std.semver.byte_ord_block_65:
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -64], rax
  cmpq [rbp + -216], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  testq rax, rax
  jne std.semver.byte_ord_block_68
  jmp std.semver.byte_ord_block_70
std.semver.byte_ord_block_68:
  jmp std.semver.byte_ord_block_68
  movq $361, rax
  jmp std.semver.byte_ord_epilogue
std.semver.byte_ord_block_70:
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -64], rax
  cmpq [rbp + -232], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  testq rax, rax
  jne std.semver.byte_ord_block_73
  jmp std.semver.byte_ord_block_75
std.semver.byte_ord_block_73:
  jmp std.semver.byte_ord_block_73
  movq $369, rax
  jmp std.semver.byte_ord_epilogue
std.semver.byte_ord_block_75:
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -64], rax
  cmpq [rbp + -248], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  testq rax, rax
  jne std.semver.byte_ord_block_78
  jmp std.semver.byte_ord_block_80
std.semver.byte_ord_block_78:
  jmp std.semver.byte_ord_block_78
  movq $345, rax
  jmp std.semver.byte_ord_epilogue
std.semver.byte_ord_block_80:
  movq $1, rax
  jmp std.semver.byte_ord_epilogue
std.semver.byte_ord_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.byte_ord:

.globl std.semver.is_numeric
std.semver.is_numeric:
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
std.semver.is_numeric_entry:
std.semver.is_numeric_block_0:
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
  jne std.semver.is_numeric_block_3
  jmp std.semver.is_numeric_block_5
std.semver.is_numeric_block_3:
  jmp std.semver.is_numeric_block_3
  movq $10, rax
  jmp std.semver.is_numeric_epilogue
std.semver.is_numeric_block_5:
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  jmp std.semver.is_numeric_block_8
std.semver.is_numeric_block_8:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r7, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.semver.is_numeric_block_11
  jmp std.semver.is_numeric_block_27
std.semver.is_numeric_block_11:
  jmp std.semver.is_numeric_block_11
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -104], r8
  call substring
  movq [rbp + -88], rcx
  movq $r13, rdx
  call std.semver.index_of
  movq $9, rax
  negq rax
  movq rax, [rbp + -112]
  movq $r14, rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.semver.is_numeric_block_20
  jmp std.semver.is_numeric_block_22
std.semver.is_numeric_block_20:
  jmp std.semver.is_numeric_block_20
  movq $10, rax
  jmp std.semver.is_numeric_epilogue
std.semver.is_numeric_block_22:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -128]
  jmp std.semver.is_numeric_block_8
std.semver.is_numeric_block_27:
  movq $18, rax
  jmp std.semver.is_numeric_epilogue
std.semver.is_numeric_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.is_numeric:

.globl std.semver.split_by_dot
std.semver.split_by_dot:
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
std.semver.split_by_dot_entry:
std.semver.split_by_dot_block_0:
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  jmp std.semver.split_by_dot_block_5
std.semver.split_by_dot_block_5:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.semver.split_by_dot_block_8
  jmp std.semver.split_by_dot_block_28
std.semver.split_by_dot_block_8:
  jmp std.semver.split_by_dot_block_8
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -88], r8
  call substring
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r11, rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.semver.split_by_dot_block_16
  jmp std.semver.split_by_dot_block_20
std.semver.split_by_dot_block_16:
  jmp std.semver.split_by_dot_block_16
  movq $r1, rcx
  movq [rbp + -72], rdx
  call lm_list_append
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  jmp std.semver.split_by_dot_block_23
std.semver.split_by_dot_block_20:
  movq [rbp + -112], rcx
  movq $r11, rdx
  call lm_str_concat
  movq rax, [rbp + -120]
  jmp std.semver.split_by_dot_block_23
std.semver.split_by_dot_block_23:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -128]
  jmp std.semver.split_by_dot_block_5
std.semver.split_by_dot_block_28:
  movq $r1, rcx
  movq [rbp + -120], rdx
  call lm_list_append
  movq $r1, rax
  jmp std.semver.split_by_dot_epilogue
std.semver.split_by_dot_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.split_by_dot:

.globl std.semver.to_int
std.semver.to_int:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 504
  mov [rbp + -64], rcx
std.semver.to_int_entry:
std.semver.to_int_block_0:
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.semver.to_int_block_3
  jmp std.semver.to_int_block_6
std.semver.to_int_block_3:
  jmp std.semver.to_int_block_3
  movq $9, rax
  negq rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.semver.to_int_epilogue
std.semver.to_int_block_6:
  jmp std.semver.to_int_block_9
std.semver.to_int_block_9:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r8, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.semver.to_int_block_12
  jmp std.semver.to_int_block_154
std.semver.to_int_block_12:
  jmp std.semver.to_int_block_12
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -104], r8
  call substring
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r14, rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.semver.to_int_block_20
  jmp std.semver.to_int_block_29
std.semver.to_int_block_20:
  jmp std.semver.to_int_block_20
  movq $1, rax
  imulq $81, rax
  movq rax, [rbp + -128]
  movq $1, rax
  imulq $81, rax
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  addq $1, rax
  movq rax, [rbp + -144]
  jmp std.semver.to_int_block_146
std.semver.to_int_block_29:
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq $r14, rax
  cmpq [rbp + -152], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  testq rax, rax
  jne std.semver.to_int_block_32
  jmp std.semver.to_int_block_41
std.semver.to_int_block_32:
  jmp std.semver.to_int_block_32
  movq [rbp + -144], rax
  imulq $81, rax
  movq rax, [rbp + -168]
  movq [rbp + -144], rax
  imulq $81, rax
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  addq $9, rax
  movq rax, [rbp + -184]
  jmp std.semver.to_int_block_145
std.semver.to_int_block_41:
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq $r14, rax
  cmpq [rbp + -192], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  testq rax, rax
  jne std.semver.to_int_block_44
  jmp std.semver.to_int_block_53
std.semver.to_int_block_44:
  jmp std.semver.to_int_block_44
  movq [rbp + -184], rax
  imulq $81, rax
  movq rax, [rbp + -208]
  movq [rbp + -184], rax
  imulq $81, rax
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  addq $17, rax
  movq rax, [rbp + -224]
  jmp std.semver.to_int_block_144
std.semver.to_int_block_53:
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq $r14, rax
  cmpq [rbp + -232], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  testq rax, rax
  jne std.semver.to_int_block_56
  jmp std.semver.to_int_block_65
std.semver.to_int_block_56:
  jmp std.semver.to_int_block_56
  movq [rbp + -224], rax
  imulq $81, rax
  movq rax, [rbp + -248]
  movq [rbp + -224], rax
  imulq $81, rax
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  addq $25, rax
  movq rax, [rbp + -264]
  jmp std.semver.to_int_block_143
std.semver.to_int_block_65:
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq $r14, rax
  cmpq [rbp + -272], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  testq rax, rax
  jne std.semver.to_int_block_68
  jmp std.semver.to_int_block_77
std.semver.to_int_block_68:
  jmp std.semver.to_int_block_68
  movq [rbp + -264], rax
  imulq $81, rax
  movq rax, [rbp + -288]
  movq [rbp + -264], rax
  imulq $81, rax
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  addq $33, rax
  movq rax, [rbp + -304]
  jmp std.semver.to_int_block_142
std.semver.to_int_block_77:
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq $r14, rax
  cmpq [rbp + -312], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  testq rax, rax
  jne std.semver.to_int_block_80
  jmp std.semver.to_int_block_89
std.semver.to_int_block_80:
  jmp std.semver.to_int_block_80
  movq [rbp + -304], rax
  imulq $81, rax
  movq rax, [rbp + -328]
  movq [rbp + -304], rax
  imulq $81, rax
  movq rax, [rbp + -336]
  movq [rbp + -336], rax
  addq $41, rax
  movq rax, [rbp + -344]
  jmp std.semver.to_int_block_141
std.semver.to_int_block_89:
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq $r14, rax
  cmpq [rbp + -352], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rbp + -360], rax
  testq rax, rax
  jne std.semver.to_int_block_92
  jmp std.semver.to_int_block_101
std.semver.to_int_block_92:
  jmp std.semver.to_int_block_92
  movq [rbp + -344], rax
  imulq $81, rax
  movq rax, [rbp + -368]
  movq [rbp + -344], rax
  imulq $81, rax
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  addq $49, rax
  movq rax, [rbp + -384]
  jmp std.semver.to_int_block_140
std.semver.to_int_block_101:
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq $r14, rax
  cmpq [rbp + -392], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  testq rax, rax
  jne std.semver.to_int_block_104
  jmp std.semver.to_int_block_113
std.semver.to_int_block_104:
  jmp std.semver.to_int_block_104
  movq [rbp + -384], rax
  imulq $81, rax
  movq rax, [rbp + -408]
  movq [rbp + -384], rax
  imulq $81, rax
  movq rax, [rbp + -416]
  movq [rbp + -416], rax
  addq $57, rax
  movq rax, [rbp + -424]
  jmp std.semver.to_int_block_139
std.semver.to_int_block_113:
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq $r14, rax
  cmpq [rbp + -432], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  testq rax, rax
  jne std.semver.to_int_block_116
  jmp std.semver.to_int_block_125
std.semver.to_int_block_116:
  jmp std.semver.to_int_block_116
  movq [rbp + -424], rax
  imulq $81, rax
  movq rax, [rbp + -448]
  movq [rbp + -424], rax
  imulq $81, rax
  movq rax, [rbp + -456]
  movq [rbp + -456], rax
  addq $65, rax
  movq rax, [rbp + -464]
  jmp std.semver.to_int_block_138
std.semver.to_int_block_125:
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq $r14, rax
  cmpq [rbp + -472], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -480]
  movq [rbp + -480], rax
  testq rax, rax
  jne std.semver.to_int_block_128
  jmp std.semver.to_int_block_151
std.semver.to_int_block_128:
  jmp std.semver.to_int_block_128
  movq [rbp + -464], rax
  imulq $81, rax
  movq rax, [rbp + -488]
  movq [rbp + -464], rax
  imulq $81, rax
  movq rax, [rbp + -496]
  movq [rbp + -496], rax
  addq $73, rax
  movq rax, [rbp + -504]
  jmp std.semver.to_int_block_137
std.semver.to_int_block_137:
  jmp std.semver.to_int_block_138
std.semver.to_int_block_138:
  jmp std.semver.to_int_block_139
std.semver.to_int_block_139:
  jmp std.semver.to_int_block_140
std.semver.to_int_block_140:
  jmp std.semver.to_int_block_141
std.semver.to_int_block_141:
  jmp std.semver.to_int_block_142
std.semver.to_int_block_142:
  jmp std.semver.to_int_block_143
std.semver.to_int_block_143:
  jmp std.semver.to_int_block_144
std.semver.to_int_block_144:
  jmp std.semver.to_int_block_145
std.semver.to_int_block_145:
  jmp std.semver.to_int_block_146
std.semver.to_int_block_146:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -512]
  jmp std.semver.to_int_block_9
std.semver.to_int_block_151:
  movq $9, rax
  negq rax
  movq rax, [rbp + -520]
  movq [rbp + -520], rax
  jmp std.semver.to_int_epilogue
std.semver.to_int_block_154:
  movq [rbp + -504], rax
  jmp std.semver.to_int_epilogue
std.semver.to_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.to_int:

.globl std.semver.compare
std.semver.compare:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.semver.compare_entry:
std.semver.compare_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.semver.Version.compare
  movq $r2, rax
  jmp std.semver.compare_epilogue
std.semver.compare_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.compare:

.globl test_compatibility
test_compatibility:
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
test_compatibility_entry:
test_compatibility_block_0:
  movq [rel str_const_25], rcx
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
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.semver.parse
  movq $r3, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne test_compatibility_block_7
  jmp test_compatibility_block_6
test_compatibility_block_6:
  jmp test_compatibility_block_6
  jmp test_compatibility_block_11
test_compatibility_block_7:
  jmp test_compatibility_block_14
test_compatibility_block_11:
  jmp test_compatibility_block_14
test_compatibility_block_14:
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -112], rcx
  call std.semver.parse
  movq $r11, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne test_compatibility_block_20
  jmp test_compatibility_block_19
test_compatibility_block_19:
  jmp test_compatibility_block_19
  jmp test_compatibility_block_24
test_compatibility_block_20:
  jmp test_compatibility_block_27
test_compatibility_block_24:
  jmp test_compatibility_block_27
test_compatibility_block_27:
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  call std.semver.parse
  movq $r19, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne test_compatibility_block_33
  jmp test_compatibility_block_32
test_compatibility_block_32:
  jmp test_compatibility_block_32
  jmp test_compatibility_block_37
test_compatibility_block_33:
  jmp test_compatibility_block_40
test_compatibility_block_37:
  jmp test_compatibility_block_40
test_compatibility_block_40:
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  call std.semver.parse
  movq $r27, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne test_compatibility_block_46
  jmp test_compatibility_block_45
test_compatibility_block_45:
  jmp test_compatibility_block_45
  jmp test_compatibility_block_50
test_compatibility_block_46:
  jmp test_compatibility_block_53
test_compatibility_block_50:
  jmp test_compatibility_block_53
test_compatibility_block_53:
  movq $r3, rcx
  movq $r11, rdx
  call std.semver.Version.is_compatible
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq $r34, rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq $r3, rcx
  movq $r19, rdx
  call std.semver.Version.is_compatible
  movq $r37, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call lm_assert
  movq $r3, rcx
  movq $r27, rdx
  call std.semver.Version.is_compatible
  movq $r42, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -184], rcx
  movq [rbp + -192], rdx
  call lm_assert
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  call std.semver.parse
  movq $r48, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  testq rax, rax
  jne test_compatibility_block_72
  jmp test_compatibility_block_71
test_compatibility_block_71:
  jmp test_compatibility_block_71
  jmp test_compatibility_block_76
test_compatibility_block_72:
  jmp test_compatibility_block_79
test_compatibility_block_76:
  jmp test_compatibility_block_79
test_compatibility_block_79:
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -216], rcx
  call std.semver.parse
  movq $r56, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  testq rax, rax
  jne test_compatibility_block_85
  jmp test_compatibility_block_84
test_compatibility_block_84:
  jmp test_compatibility_block_84
  jmp test_compatibility_block_89
test_compatibility_block_85:
  jmp test_compatibility_block_92
test_compatibility_block_89:
  jmp test_compatibility_block_92
test_compatibility_block_92:
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -232], rcx
  call std.semver.parse
  movq $r64, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  testq rax, rax
  jne test_compatibility_block_98
  jmp test_compatibility_block_97
test_compatibility_block_97:
  jmp test_compatibility_block_97
  jmp test_compatibility_block_102
test_compatibility_block_98:
  jmp test_compatibility_block_105
test_compatibility_block_102:
  jmp test_compatibility_block_105
test_compatibility_block_105:
  movq $r48, rcx
  movq $r56, rdx
  call std.semver.Version.is_compatible
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq $r71, rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq $r48, rcx
  movq $r64, rdx
  call std.semver.Version.is_compatible
  movq $r74, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -256], rcx
  movq [rbp + -264], rdx
  call lm_assert
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -272], rcx
  call std.semver.parse
  movq $r80, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  testq rax, rax
  jne test_compatibility_block_119
  jmp test_compatibility_block_118
test_compatibility_block_118:
  jmp test_compatibility_block_118
  jmp test_compatibility_block_123
test_compatibility_block_119:
  jmp test_compatibility_block_126
test_compatibility_block_123:
  jmp test_compatibility_block_126
test_compatibility_block_126:
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -288], rcx
  call std.semver.parse
  movq $r88, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  testq rax, rax
  jne test_compatibility_block_132
  jmp test_compatibility_block_131
test_compatibility_block_131:
  jmp test_compatibility_block_131
  jmp test_compatibility_block_136
test_compatibility_block_132:
  jmp test_compatibility_block_139
test_compatibility_block_136:
  jmp test_compatibility_block_139
test_compatibility_block_139:
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -304], rcx
  call std.semver.parse
  movq $r96, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -312]
  movq [rbp + -312], rax
  testq rax, rax
  jne test_compatibility_block_145
  jmp test_compatibility_block_144
test_compatibility_block_144:
  jmp test_compatibility_block_144
  jmp test_compatibility_block_149
test_compatibility_block_145:
  jmp test_compatibility_block_152
test_compatibility_block_149:
  jmp test_compatibility_block_152
test_compatibility_block_152:
  movq $r80, rcx
  movq $r88, rdx
  call std.semver.Version.is_compatible
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq $r103, rcx
  movq [rbp + -320], rdx
  call lm_assert
  movq $r80, rcx
  movq $r96, rdx
  call std.semver.Version.is_compatible
  movq $r106, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -328]
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -328], rcx
  movq [rbp + -336], rdx
  call lm_assert
  movq [rel str_const_43], rcx
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
  movq $9, rax
  jmp test_compatibility_epilogue
test_compatibility_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_compatibility:

.globl test_comparison
test_comparison:
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
test_comparison_entry:
test_comparison_block_0:
  movq [rel str_const_44], rcx
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
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.semver.parse
  movq $r3, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne test_comparison_block_7
  jmp test_comparison_block_6
test_comparison_block_6:
  jmp test_comparison_block_6
  jmp test_comparison_block_11
test_comparison_block_7:
  jmp test_comparison_block_14
test_comparison_block_11:
  jmp test_comparison_block_14
test_comparison_block_14:
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -112], rcx
  call std.semver.parse
  movq $r11, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne test_comparison_block_20
  jmp test_comparison_block_19
test_comparison_block_19:
  jmp test_comparison_block_19
  jmp test_comparison_block_24
test_comparison_block_20:
  jmp test_comparison_block_27
test_comparison_block_24:
  jmp test_comparison_block_27
test_comparison_block_27:
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  call std.semver.parse
  movq $r19, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne test_comparison_block_33
  jmp test_comparison_block_32
test_comparison_block_32:
  jmp test_comparison_block_32
  jmp test_comparison_block_37
test_comparison_block_33:
  jmp test_comparison_block_40
test_comparison_block_37:
  jmp test_comparison_block_40
test_comparison_block_40:
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  call std.semver.parse
  movq $r27, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne test_comparison_block_46
  jmp test_comparison_block_45
test_comparison_block_45:
  jmp test_comparison_block_45
  jmp test_comparison_block_50
test_comparison_block_46:
  jmp test_comparison_block_53
test_comparison_block_50:
  jmp test_comparison_block_53
test_comparison_block_53:
  movq $r3, rcx
  movq $r11, rdx
  call std.semver.Version.compare
  movq $9, rax
  negq rax
  movq rax, [rbp + -160]
  movq $r34, rax
  cmpq [rbp + -160], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call lm_assert
  movq $r11, rcx
  movq $r3, rdx
  call std.semver.Version.compare
  movq $r40, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -184], rcx
  movq [rbp + -192], rdx
  call lm_assert
  movq $r3, rcx
  movq $r19, rdx
  call std.semver.Version.compare
  movq $9, rax
  negq rax
  movq rax, [rbp + -200]
  movq $r45, rax
  cmpq [rbp + -200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq $r19, rcx
  movq $r3, rdx
  call std.semver.Version.compare
  movq $r51, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  movq $r3, rcx
  movq $r27, rdx
  call std.semver.Version.compare
  movq $9, rax
  negq rax
  movq rax, [rbp + -240]
  movq $r56, rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -248], rcx
  movq [rbp + -256], rdx
  call lm_assert
  movq $r3, rcx
  movq $r3, rdx
  call std.semver.Version.compare
  movq $r62, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -264]
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -264], rcx
  movq [rbp + -272], rdx
  call lm_assert
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -280], rcx
  call std.semver.parse
  movq $r68, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -288]
  movq [rbp + -288], rax
  testq rax, rax
  jne test_comparison_block_92
  jmp test_comparison_block_91
test_comparison_block_91:
  jmp test_comparison_block_91
  jmp test_comparison_block_96
test_comparison_block_92:
  jmp test_comparison_block_99
test_comparison_block_96:
  jmp test_comparison_block_99
test_comparison_block_99:
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -296], rcx
  call std.semver.parse
  movq $r76, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  testq rax, rax
  jne test_comparison_block_105
  jmp test_comparison_block_104
test_comparison_block_104:
  jmp test_comparison_block_104
  jmp test_comparison_block_109
test_comparison_block_105:
  jmp test_comparison_block_112
test_comparison_block_109:
  jmp test_comparison_block_112
test_comparison_block_112:
  movq $r68, rcx
  movq $r76, rdx
  call std.semver.Version.compare
  movq $9, rax
  negq rax
  movq rax, [rbp + -312]
  movq $r83, rax
  cmpq [rbp + -312], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -320]
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -320], rcx
  movq [rbp + -328], rdx
  call lm_assert
  movq $r76, rcx
  movq $r68, rdx
  call std.semver.Version.compare
  movq $r89, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -336]
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -336], rcx
  movq [rbp + -344], rdx
  call lm_assert
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -352], rcx
  call std.semver.parse
  movq $r95, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rbp + -360], rax
  testq rax, rax
  jne test_comparison_block_129
  jmp test_comparison_block_128
test_comparison_block_128:
  jmp test_comparison_block_128
  jmp test_comparison_block_133
test_comparison_block_129:
  jmp test_comparison_block_136
test_comparison_block_133:
  jmp test_comparison_block_136
test_comparison_block_136:
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -368], rcx
  call std.semver.parse
  movq $r103, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  testq rax, rax
  jne test_comparison_block_142
  jmp test_comparison_block_141
test_comparison_block_141:
  jmp test_comparison_block_141
  jmp test_comparison_block_146
test_comparison_block_142:
  jmp test_comparison_block_149
test_comparison_block_146:
  jmp test_comparison_block_149
test_comparison_block_149:
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -384], rcx
  call std.semver.parse
  movq $r111, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  testq rax, rax
  jne test_comparison_block_155
  jmp test_comparison_block_154
test_comparison_block_154:
  jmp test_comparison_block_154
  jmp test_comparison_block_159
test_comparison_block_155:
  jmp test_comparison_block_162
test_comparison_block_159:
  jmp test_comparison_block_162
test_comparison_block_162:
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -400], rcx
  call std.semver.parse
  movq $r119, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -408]
  movq [rbp + -408], rax
  testq rax, rax
  jne test_comparison_block_168
  jmp test_comparison_block_167
test_comparison_block_167:
  jmp test_comparison_block_167
  jmp test_comparison_block_172
test_comparison_block_168:
  jmp test_comparison_block_175
test_comparison_block_172:
  jmp test_comparison_block_175
test_comparison_block_175:
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -416], rcx
  call std.semver.parse
  movq $r127, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  testq rax, rax
  jne test_comparison_block_181
  jmp test_comparison_block_180
test_comparison_block_180:
  jmp test_comparison_block_180
  jmp test_comparison_block_185
test_comparison_block_181:
  jmp test_comparison_block_188
test_comparison_block_185:
  jmp test_comparison_block_188
test_comparison_block_188:
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rbp + -432], rcx
  call std.semver.parse
  movq $r135, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  testq rax, rax
  jne test_comparison_block_194
  jmp test_comparison_block_193
test_comparison_block_193:
  jmp test_comparison_block_193
  jmp test_comparison_block_198
test_comparison_block_194:
  jmp test_comparison_block_201
test_comparison_block_198:
  jmp test_comparison_block_201
test_comparison_block_201:
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -448], rcx
  call std.semver.parse
  movq $r143, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -456]
  movq [rbp + -456], rax
  testq rax, rax
  jne test_comparison_block_207
  jmp test_comparison_block_206
test_comparison_block_206:
  jmp test_comparison_block_206
  jmp test_comparison_block_211
test_comparison_block_207:
  jmp test_comparison_block_214
test_comparison_block_211:
  jmp test_comparison_block_214
test_comparison_block_214:
  movq $r95, rcx
  movq $r103, rdx
  call std.semver.Version.compare
  movq $9, rax
  negq rax
  movq rax, [rbp + -464]
  movq $r150, rax
  cmpq [rbp + -464], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -472]
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq [rbp + -472], rcx
  movq [rbp + -480], rdx
  call lm_assert
  movq $r103, rcx
  movq $r111, rdx
  call std.semver.Version.compare
  movq $9, rax
  negq rax
  movq rax, [rbp + -488]
  movq $r156, rax
  cmpq [rbp + -488], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -496]
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -496], rcx
  movq [rbp + -504], rdx
  call lm_assert
  movq $r111, rcx
  movq $r119, rdx
  call std.semver.Version.compare
  movq $9, rax
  negq rax
  movq rax, [rbp + -512]
  movq $r162, rax
  cmpq [rbp + -512], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -520]
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -520], rcx
  movq [rbp + -528], rdx
  call lm_assert
  movq $r119, rcx
  movq $r127, rdx
  call std.semver.Version.compare
  movq $9, rax
  negq rax
  movq rax, [rbp + -536]
  movq $r168, rax
  cmpq [rbp + -536], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -544]
  movq [rel str_const_69], rcx
  call lm_box_string
  movq rax, [rbp + -552]
  movq [rbp + -544], rcx
  movq [rbp + -552], rdx
  call lm_assert
  movq $r127, rcx
  movq $r135, rdx
  call std.semver.Version.compare
  movq $9, rax
  negq rax
  movq rax, [rbp + -560]
  movq $r174, rax
  cmpq [rbp + -560], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -568]
  movq [rel str_const_70], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -568], rcx
  movq [rbp + -576], rdx
  call lm_assert
  movq $r135, rcx
  movq $r143, rdx
  call std.semver.Version.compare
  movq $9, rax
  negq rax
  movq rax, [rbp + -584]
  movq $r180, rax
  cmpq [rbp + -584], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -592]
  movq [rel str_const_71], rcx
  call lm_box_string
  movq rax, [rbp + -600]
  movq [rbp + -592], rcx
  movq [rbp + -600], rdx
  call lm_assert
  movq [rel str_const_72], rcx
  call lm_box_string
  movq rax, [rbp + -608]
  movq [rbp + -608], rcx
  call std.semver.parse
  movq $r187, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -616]
  movq [rbp + -616], rax
  testq rax, rax
  jne test_comparison_block_256
  jmp test_comparison_block_255
test_comparison_block_255:
  jmp test_comparison_block_255
  jmp test_comparison_block_260
test_comparison_block_256:
  jmp test_comparison_block_263
test_comparison_block_260:
  jmp test_comparison_block_263
test_comparison_block_263:
  movq [rel str_const_73], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rbp + -624], rcx
  call std.semver.parse
  movq $r195, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -632]
  movq [rbp + -632], rax
  testq rax, rax
  jne test_comparison_block_269
  jmp test_comparison_block_268
test_comparison_block_268:
  jmp test_comparison_block_268
  jmp test_comparison_block_273
test_comparison_block_269:
  jmp test_comparison_block_276
test_comparison_block_273:
  jmp test_comparison_block_276
test_comparison_block_276:
  movq $r187, rcx
  movq $r195, rdx
  call std.semver.Version.compare
  movq $r202, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -640]
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -648]
  movq [rbp + -640], rcx
  movq [rbp + -648], rdx
  call lm_assert
  movq $r187, rcx
  movq $r195, rdx
  call std.semver.Version.equals
  movq [rel str_const_75], rcx
  call lm_box_string
  movq rax, [rbp + -656]
  movq $r207, rcx
  movq [rbp + -656], rdx
  call lm_assert
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -664]
  movq [rbp + -664], rax
  addq $16, rax
  movq rax, [rbp + -672]
  movq [rbp + -672], rax
  movq rax, [rbp + -680]
  movq [rbp + -680], rax
  mov rax, [rax]
  movq rax, [rbp + -688]
  movq [rbp + -688], rcx
  call lm_print_str
  movq $9, rax
  jmp test_comparison_epilogue
test_comparison_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_comparison:

.globl std.semver.is_valid_char
std.semver.is_valid_char:
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
std.semver.is_valid_char_entry:
std.semver.is_valid_char_block_0:
  movq [rel str_const_77], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.semver.index_of
  movq $9, rax
  negq rax
  movq rax, [rbp + -80]
  movq $r2, rax
  cmpq [rbp + -80], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.semver.is_valid_char_epilogue
std.semver.is_valid_char_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.is_valid_char:

.globl test_formatting
test_formatting:
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
test_formatting_entry:
test_formatting_block_0:
  movq [rel str_const_78], rcx
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
  movq [rel str_const_79], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.semver.parse
  movq $r3, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne test_formatting_block_7
  jmp test_formatting_block_6
test_formatting_block_6:
  jmp test_formatting_block_6
  jmp test_formatting_block_11
test_formatting_block_7:
  jmp test_formatting_block_14
test_formatting_block_11:
  jmp test_formatting_block_14
test_formatting_block_14:
  movq $r3, rcx
  call std.semver.Version.to_string
  movq [rel str_const_80], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r10, rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_81], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq [rel str_const_82], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -136], rcx
  call std.semver.parse
  movq $r16, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  testq rax, rax
  jne test_formatting_block_25
  jmp test_formatting_block_24
test_formatting_block_24:
  jmp test_formatting_block_24
  jmp test_formatting_block_29
test_formatting_block_25:
  jmp test_formatting_block_32
test_formatting_block_29:
  jmp test_formatting_block_32
test_formatting_block_32:
  movq $r16, rcx
  call std.semver.Version.to_string
  movq [rel str_const_83], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq $r23, rax
  cmpq [rbp + -152], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_84], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq [rel str_const_85], rcx
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
  movq $9, rax
  jmp test_formatting_epilogue
test_formatting_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_formatting:

.globl std.semver.is_compatible
std.semver.is_compatible:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.semver.is_compatible_entry:
std.semver.is_compatible_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.semver.Version.is_compatible
  movq $r2, rax
  jmp std.semver.is_compatible_epilogue
std.semver.is_compatible_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.is_compatible:

.globl std.semver.Version.compare
std.semver.Version.compare:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.semver.Version.compare_entry:
  movq $0, rax
  jmp std.semver.Version.compare_epilogue
std.semver.Version.compare_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.Version.compare:

.globl std.semver.compare_strings
std.semver.compare_strings:
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
std.semver.compare_strings_entry:
std.semver.compare_strings_block_0:
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.semver.compare_strings_block_2
  jmp std.semver.compare_strings_block_4
std.semver.compare_strings_block_2:
  jmp std.semver.compare_strings_block_2
  movq $1, rax
  jmp std.semver.compare_strings_epilogue
std.semver.compare_strings_block_4:
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
  jne std.semver.compare_strings_block_11
  jmp std.semver.compare_strings_block_13
std.semver.compare_strings_block_11:
  jmp std.semver.compare_strings_block_11
  jmp std.semver.compare_strings_block_13
std.semver.compare_strings_block_13:
  jmp std.semver.compare_strings_block_15
std.semver.compare_strings_block_15:
  movq $1, rax
  cmpq $r7, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.semver.compare_strings_block_17
  jmp std.semver.compare_strings_block_45
std.semver.compare_strings_block_17:
  jmp std.semver.compare_strings_block_17
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
  jne std.semver.compare_strings_block_29
  jmp std.semver.compare_strings_block_40
std.semver.compare_strings_block_29:
  jmp std.semver.compare_strings_block_29
  movq $r18, rcx
  call std.semver.byte_ord
  movq $r23, rcx
  call std.semver.byte_ord
  movq $r27, rax
  cmpq $r29, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.semver.compare_strings_block_35
  jmp std.semver.compare_strings_block_37
std.semver.compare_strings_block_35:
  jmp std.semver.compare_strings_block_35
  movq $9, rax
  jmp std.semver.compare_strings_epilogue
std.semver.compare_strings_block_37:
  movq $9, rax
  negq rax
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  jmp std.semver.compare_strings_epilogue
std.semver.compare_strings_block_40:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.semver.compare_strings_block_15
std.semver.compare_strings_block_45:
  movq $r5, rax
  cmpq $r7, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne std.semver.compare_strings_block_47
  jmp std.semver.compare_strings_block_49
std.semver.compare_strings_block_47:
  jmp std.semver.compare_strings_block_47
  movq $9, rax
  jmp std.semver.compare_strings_epilogue
std.semver.compare_strings_block_49:
  movq $r5, rax
  cmpq $r7, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  testq rax, rax
  jne std.semver.compare_strings_block_51
  jmp std.semver.compare_strings_block_54
std.semver.compare_strings_block_51:
  jmp std.semver.compare_strings_block_51
  movq $9, rax
  negq rax
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  jmp std.semver.compare_strings_epilogue
std.semver.compare_strings_block_54:
  movq $1, rax
  jmp std.semver.compare_strings_epilogue
std.semver.compare_strings_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.compare_strings:

.globl std.semver.Version.is_compatible
std.semver.Version.is_compatible:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.semver.Version.is_compatible_entry:
  movq $0, rax
  jmp std.semver.Version.is_compatible_epilogue
std.semver.Version.is_compatible_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.Version.is_compatible:

.globl std.semver.Version.less_than
std.semver.Version.less_than:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.semver.Version.less_than_entry:
  movq $0, rax
  jmp std.semver.Version.less_than_epilogue
std.semver.Version.less_than_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.Version.less_than:

.globl std.semver.index_of
std.semver.index_of:
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
std.semver.index_of_entry:
std.semver.index_of_block_0:
  jmp std.semver.index_of_block_2
std.semver.index_of_block_2:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.semver.index_of_block_5
  jmp std.semver.index_of_block_17
std.semver.index_of_block_5:
  jmp std.semver.index_of_block_5
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -88], r8
  call substring
  movq $r9, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.semver.index_of_block_11
  jmp std.semver.index_of_block_12
std.semver.index_of_block_11:
  jmp std.semver.index_of_block_11
  movq $1, rax
  jmp std.semver.index_of_epilogue
std.semver.index_of_block_12:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.semver.index_of_block_2
std.semver.index_of_block_17:
  movq $9, rax
  negq rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp std.semver.index_of_epilogue
std.semver.index_of_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.index_of:

.globl std.semver.has_invalid_leading_zero
std.semver.has_invalid_leading_zero:
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
std.semver.has_invalid_leading_zero_entry:
std.semver.has_invalid_leading_zero_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r2, rax
  cmpq $9, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.semver.has_invalid_leading_zero_block_5
  jmp std.semver.has_invalid_leading_zero_block_12
std.semver.has_invalid_leading_zero_block_5:
  jmp std.semver.has_invalid_leading_zero_block_5
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $9, r8
  call substring
  movq [rel str_const_86], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq $r7, rax
  cmpq [rbp + -80], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  jmp std.semver.has_invalid_leading_zero_block_12
std.semver.has_invalid_leading_zero_block_12:
  movq [rbp + -88], rax
  testq rax, rax
  jne std.semver.has_invalid_leading_zero_block_13
  jmp std.semver.has_invalid_leading_zero_block_15
std.semver.has_invalid_leading_zero_block_13:
  jmp std.semver.has_invalid_leading_zero_block_13
  movq $18, rax
  jmp std.semver.has_invalid_leading_zero_epilogue
std.semver.has_invalid_leading_zero_block_15:
  movq $10, rax
  jmp std.semver.has_invalid_leading_zero_epilogue
std.semver.has_invalid_leading_zero_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.has_invalid_leading_zero:

.globl std.semver.Version.init
std.semver.Version.init:
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
std.semver.Version.init_entry:
  movq $0, rax
  jmp std.semver.Version.init_epilogue
std.semver.Version.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.Version.init:

.globl test_parsing
test_parsing:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 824
test_parsing_entry:
test_parsing_block_0:
  movq [rel str_const_87], rcx
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
  movq [rel str_const_88], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.semver.parse
  movq $r3, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne test_parsing_block_7
  jmp test_parsing_block_6
test_parsing_block_6:
  jmp test_parsing_block_6
  jmp test_parsing_block_14
test_parsing_block_7:
  movq [rel str_const_89], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $10, rcx
  movq [rbp + -112], rdx
  call lm_assert
  jmp test_parsing_block_17
test_parsing_block_14:
  jmp test_parsing_block_17
test_parsing_block_17:
  movq $r3, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_90], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq $r3, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_91], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq $r3, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_92], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq $r3, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -192]
  movq [rel str_const_93], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rax
  cmpq [rbp + -200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_94], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq $r3, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -224]
  movq [rel str_const_95], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rax
  cmpq [rbp + -232], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_96], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq [rel str_const_97], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -256], rcx
  call std.semver.parse
  movq $r39, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  testq rax, rax
  jne test_parsing_block_48
  jmp test_parsing_block_47
test_parsing_block_47:
  jmp test_parsing_block_47
  jmp test_parsing_block_55
test_parsing_block_48:
  movq [rel str_const_98], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq $10, rcx
  movq [rbp + -272], rdx
  call lm_assert
  jmp test_parsing_block_58
test_parsing_block_55:
  jmp test_parsing_block_58
test_parsing_block_58:
  movq $r39, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -288]
  movq [rel str_const_99], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -288], rcx
  movq [rbp + -296], rdx
  call lm_assert
  movq $r39, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -312]
  movq [rel str_const_100], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -312], rcx
  movq [rbp + -320], rdx
  call lm_assert
  movq $r39, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -336]
  movq [rel str_const_101], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -336], rcx
  movq [rbp + -344], rdx
  call lm_assert
  movq [rel str_const_102], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -352], rcx
  call std.semver.parse
  movq $r65, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rbp + -360], rax
  testq rax, rax
  jne test_parsing_block_79
  jmp test_parsing_block_78
test_parsing_block_78:
  jmp test_parsing_block_78
  jmp test_parsing_block_86
test_parsing_block_79:
  movq [rel str_const_103], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq $10, rcx
  movq [rbp + -368], rdx
  call lm_assert
  jmp test_parsing_block_89
test_parsing_block_86:
  jmp test_parsing_block_89
test_parsing_block_89:
  movq $r65, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -376]
  movq [rel str_const_104], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -376], rax
  cmpq [rbp + -384], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rel str_const_105], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -392], rcx
  movq [rbp + -400], rdx
  call lm_assert
  movq $r65, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -408]
  movq [rel str_const_106], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -408], rax
  cmpq [rbp + -416], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -424]
  movq [rel str_const_107], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rbp + -424], rcx
  movq [rbp + -432], rdx
  call lm_assert
  movq [rel str_const_108], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rbp + -440], rcx
  call std.semver.parse
  movq $r86, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -448]
  movq [rbp + -448], rax
  testq rax, rax
  jne test_parsing_block_105
  jmp test_parsing_block_104
test_parsing_block_104:
  jmp test_parsing_block_104
  jmp test_parsing_block_112
test_parsing_block_105:
  movq [rel str_const_109], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq $10, rcx
  movq [rbp + -456], rdx
  call lm_assert
  jmp test_parsing_block_115
test_parsing_block_112:
  jmp test_parsing_block_115
test_parsing_block_115:
  movq $r86, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -464]
  movq [rel str_const_110], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -464], rax
  cmpq [rbp + -472], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -480]
  movq [rel str_const_111], rcx
  call lm_box_string
  movq rax, [rbp + -488]
  movq [rbp + -480], rcx
  movq [rbp + -488], rdx
  call lm_assert
  movq $r86, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -496]
  movq [rel str_const_112], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq [rbp + -496], rax
  cmpq [rbp + -504], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -512]
  movq [rel str_const_113], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -512], rcx
  movq [rbp + -520], rdx
  call lm_assert
  movq [rel str_const_114], rcx
  call lm_box_string
  movq rax, [rbp + -528]
  movq [rbp + -528], rcx
  call std.semver.parse
  movq $r107, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -536]
  movq [rbp + -536], rax
  testq rax, rax
  jne test_parsing_block_131
  jmp test_parsing_block_130
test_parsing_block_130:
  jmp test_parsing_block_130
  jmp test_parsing_block_138
test_parsing_block_131:
  movq [rel str_const_115], rcx
  call lm_box_string
  movq rax, [rbp + -544]
  movq $10, rcx
  movq [rbp + -544], rdx
  call lm_assert
  jmp test_parsing_block_141
test_parsing_block_138:
  jmp test_parsing_block_141
test_parsing_block_141:
  movq $r107, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -552]
  movq [rel str_const_116], rcx
  call lm_box_string
  movq rax, [rbp + -560]
  movq [rbp + -552], rax
  cmpq [rbp + -560], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -568]
  movq [rel str_const_117], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -568], rcx
  movq [rbp + -576], rdx
  call lm_assert
  movq $r107, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -584]
  movq [rel str_const_118], rcx
  call lm_box_string
  movq rax, [rbp + -592]
  movq [rbp + -584], rax
  cmpq [rbp + -592], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -600]
  movq [rel str_const_119], rcx
  call lm_box_string
  movq rax, [rbp + -608]
  movq [rbp + -600], rcx
  movq [rbp + -608], rdx
  call lm_assert
  movq [rel str_const_120], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -616], rcx
  call std.semver.parse
  movq $r129, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -624]
  movq [rbp + -624], rax
  testq rax, rax
  jne test_parsing_block_158
  jmp test_parsing_block_157
test_parsing_block_157:
  jmp test_parsing_block_157
  jmp test_parsing_block_162
test_parsing_block_158:
  jmp test_parsing_block_165
test_parsing_block_162:
  jmp test_parsing_block_165
test_parsing_block_165:
  movq [rel str_const_121], rcx
  call lm_box_string
  movq rax, [rbp + -632]
  movq $18, rcx
  movq [rbp + -632], rdx
  call lm_assert
  movq [rel str_const_122], rcx
  call lm_box_string
  movq rax, [rbp + -640]
  movq [rbp + -640], rcx
  call std.semver.parse
  movq $r140, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -648]
  movq [rbp + -648], rax
  testq rax, rax
  jne test_parsing_block_175
  jmp test_parsing_block_174
test_parsing_block_174:
  jmp test_parsing_block_174
  jmp test_parsing_block_179
test_parsing_block_175:
  jmp test_parsing_block_182
test_parsing_block_179:
  jmp test_parsing_block_182
test_parsing_block_182:
  movq [rel str_const_123], rcx
  call lm_box_string
  movq rax, [rbp + -656]
  movq $18, rcx
  movq [rbp + -656], rdx
  call lm_assert
  movq [rel str_const_124], rcx
  call lm_box_string
  movq rax, [rbp + -664]
  movq [rbp + -664], rcx
  call std.semver.parse
  movq $r151, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -672]
  movq [rbp + -672], rax
  testq rax, rax
  jne test_parsing_block_192
  jmp test_parsing_block_191
test_parsing_block_191:
  jmp test_parsing_block_191
  jmp test_parsing_block_196
test_parsing_block_192:
  jmp test_parsing_block_199
test_parsing_block_196:
  jmp test_parsing_block_199
test_parsing_block_199:
  movq [rel str_const_125], rcx
  call lm_box_string
  movq rax, [rbp + -680]
  movq $18, rcx
  movq [rbp + -680], rdx
  call lm_assert
  movq [rel str_const_126], rcx
  call lm_box_string
  movq rax, [rbp + -688]
  movq [rbp + -688], rcx
  call std.semver.parse
  movq $r162, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -696]
  movq [rbp + -696], rax
  testq rax, rax
  jne test_parsing_block_209
  jmp test_parsing_block_208
test_parsing_block_208:
  jmp test_parsing_block_208
  jmp test_parsing_block_213
test_parsing_block_209:
  jmp test_parsing_block_216
test_parsing_block_213:
  jmp test_parsing_block_216
test_parsing_block_216:
  movq [rel str_const_127], rcx
  call lm_box_string
  movq rax, [rbp + -704]
  movq $18, rcx
  movq [rbp + -704], rdx
  call lm_assert
  movq [rel str_const_128], rcx
  call lm_box_string
  movq rax, [rbp + -712]
  movq [rbp + -712], rcx
  call std.semver.parse
  movq $r173, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -720]
  movq [rbp + -720], rax
  testq rax, rax
  jne test_parsing_block_226
  jmp test_parsing_block_225
test_parsing_block_225:
  jmp test_parsing_block_225
  jmp test_parsing_block_230
test_parsing_block_226:
  jmp test_parsing_block_233
test_parsing_block_230:
  jmp test_parsing_block_233
test_parsing_block_233:
  movq [rel str_const_129], rcx
  call lm_box_string
  movq rax, [rbp + -728]
  movq $18, rcx
  movq [rbp + -728], rdx
  call lm_assert
  movq [rel str_const_130], rcx
  call lm_box_string
  movq rax, [rbp + -736]
  movq [rbp + -736], rcx
  call std.semver.parse
  movq $r184, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -744]
  movq [rbp + -744], rax
  testq rax, rax
  jne test_parsing_block_243
  jmp test_parsing_block_242
test_parsing_block_242:
  jmp test_parsing_block_242
  jmp test_parsing_block_247
test_parsing_block_243:
  jmp test_parsing_block_250
test_parsing_block_247:
  jmp test_parsing_block_250
test_parsing_block_250:
  movq [rel str_const_131], rcx
  call lm_box_string
  movq rax, [rbp + -752]
  movq $18, rcx
  movq [rbp + -752], rdx
  call lm_assert
  movq [rel str_const_132], rcx
  call lm_box_string
  movq rax, [rbp + -760]
  movq [rbp + -760], rcx
  call std.semver.parse
  movq $r195, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -768]
  movq [rbp + -768], rax
  testq rax, rax
  jne test_parsing_block_260
  jmp test_parsing_block_259
test_parsing_block_259:
  jmp test_parsing_block_259
  jmp test_parsing_block_264
test_parsing_block_260:
  jmp test_parsing_block_267
test_parsing_block_264:
  jmp test_parsing_block_267
test_parsing_block_267:
  movq [rel str_const_133], rcx
  call lm_box_string
  movq rax, [rbp + -776]
  movq $18, rcx
  movq [rbp + -776], rdx
  call lm_assert
  movq [rel str_const_134], rcx
  call lm_box_string
  movq rax, [rbp + -784]
  movq [rbp + -784], rcx
  call std.semver.parse
  movq $r206, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -792]
  movq [rbp + -792], rax
  testq rax, rax
  jne test_parsing_block_277
  jmp test_parsing_block_276
test_parsing_block_276:
  jmp test_parsing_block_276
  jmp test_parsing_block_281
test_parsing_block_277:
  jmp test_parsing_block_284
test_parsing_block_281:
  jmp test_parsing_block_284
test_parsing_block_284:
  movq [rel str_const_135], rcx
  call lm_box_string
  movq rax, [rbp + -800]
  movq $18, rcx
  movq [rbp + -800], rdx
  call lm_assert
  movq [rel str_const_136], rcx
  call lm_box_string
  movq rax, [rbp + -808]
  movq [rbp + -808], rax
  addq $16, rax
  movq rax, [rbp + -816]
  movq [rbp + -816], rax
  movq rax, [rbp + -824]
  movq [rbp + -824], rax
  mov rax, [rax]
  movq rax, [rbp + -832]
  movq [rbp + -832], rcx
  call lm_print_str
  movq $9, rax
  jmp test_parsing_epilogue
test_parsing_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_parsing:

.globl std.semver.Version.equals
std.semver.Version.equals:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.semver.Version.equals_entry:
  movq $0, rax
  jmp std.semver.Version.equals_epilogue
std.semver.Version.equals_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.Version.equals:

.globl std.semver.Version.greater_than
std.semver.Version.greater_than:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.semver.Version.greater_than_entry:
  movq $0, rax
  jmp std.semver.Version.greater_than_epilogue
std.semver.Version.greater_than_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.Version.greater_than:

.globl std.semver.Version.to_string
std.semver.Version.to_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.semver.Version.to_string_entry:
  movq $0, rax
  jmp std.semver.Version.to_string_epilogue
std.semver.Version.to_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.Version.to_string:

.globl std.semver.parse
std.semver.parse:
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
  mov [rbp + -64], rcx
std.semver.parse_entry:
std.semver.parse_block_0:
  movq [rel str_const_143], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.semver.parse_block_3
  jmp std.semver.parse_block_5
std.semver.parse_block_3:
  jmp std.semver.parse_block_3
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_5:
  movq [rel str_const_144], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call std.semver.index_of
  movq [rel str_const_145], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $9, rax
  negq rax
  movq rax, [rbp + -112]
  movq $r6, rax
  cmpq [rbp + -112], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.semver.parse_block_14
  jmp std.semver.parse_block_43
std.semver.parse_block_14:
  jmp std.semver.parse_block_14
  movq $r6, rax
  addq $9, rax
  movq rax, $r16
  movq [rbp + -64], rcx
  call lm_list_len
  movq [rbp + -64], rcx
  movq $r16, rdx
  movq $r17, r8
  call substring
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $r6, r8
  call substring
  movq $r18, rcx
  call std.semver.split_by_dot
  jmp std.semver.parse_block_27
std.semver.parse_block_27:
  movq $r21, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r24, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.semver.parse_block_30
  jmp std.semver.parse_block_42
std.semver.parse_block_30:
  jmp std.semver.parse_block_30
  movq $r21, rcx
  movq $1, rdx
  call lm_list_get
  movq $r27, rcx
  call std.semver.is_valid_build_id
  movq $r28, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne std.semver.parse_block_35
  jmp std.semver.parse_block_37
std.semver.parse_block_35:
  jmp std.semver.parse_block_35
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_37:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -152]
  jmp std.semver.parse_block_27
std.semver.parse_block_42:
  jmp std.semver.parse_block_43
std.semver.parse_block_43:
  movq [rel str_const_146], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq $r20, rcx
  movq [rbp + -160], rdx
  call std.semver.index_of
  movq [rel str_const_147], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq $9, rax
  negq rax
  movq rax, [rbp + -176]
  movq $r37, rax
  cmpq [rbp + -176], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  testq rax, rax
  jne std.semver.parse_block_52
  jmp std.semver.parse_block_81
std.semver.parse_block_52:
  jmp std.semver.parse_block_52
  movq $r37, rax
  addq $9, rax
  movq rax, $r47
  movq $r20, rcx
  call lm_list_len
  movq $r20, rcx
  movq $r47, rdx
  movq $r48, r8
  call substring
  movq $r20, rcx
  movq $1, rdx
  movq $r37, r8
  call substring
  movq $r49, rcx
  call std.semver.split_by_dot
  jmp std.semver.parse_block_65
std.semver.parse_block_65:
  movq $r52, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r55, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  testq rax, rax
  jne std.semver.parse_block_68
  jmp std.semver.parse_block_80
std.semver.parse_block_68:
  jmp std.semver.parse_block_68
  movq $r52, rcx
  movq $1, rdx
  call lm_list_get
  movq $r58, rcx
  call std.semver.is_valid_prerelease_id
  movq $r59, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  testq rax, rax
  jne std.semver.parse_block_73
  jmp std.semver.parse_block_75
std.semver.parse_block_73:
  jmp std.semver.parse_block_73
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_75:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -216]
  jmp std.semver.parse_block_65
std.semver.parse_block_80:
  jmp std.semver.parse_block_81
std.semver.parse_block_81:
  movq [rel str_const_148], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq $r51, rcx
  movq [rbp + -224], rdx
  call std.semver.index_of
  movq $9, rax
  negq rax
  movq rax, [rbp + -232]
  movq $r68, rax
  cmpq [rbp + -232], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  testq rax, rax
  jne std.semver.parse_block_88
  jmp std.semver.parse_block_90
std.semver.parse_block_88:
  jmp std.semver.parse_block_88
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_90:
  movq $r51, rcx
  movq $1, rdx
  movq $r68, r8
  call substring
  movq $r68, rax
  addq $9, rax
  movq rax, $r80
  movq $r51, rcx
  call lm_list_len
  movq $r51, rcx
  movq $r80, rdx
  movq $r81, r8
  call substring
  movq [rel str_const_149], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq $r82, rcx
  movq [rbp + -256], rdx
  call std.semver.index_of
  movq $9, rax
  negq rax
  movq rax, [rbp + -264]
  movq $r85, rax
  cmpq [rbp + -264], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  testq rax, rax
  jne std.semver.parse_block_106
  jmp std.semver.parse_block_108
std.semver.parse_block_106:
  jmp std.semver.parse_block_106
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_108:
  movq $r82, rcx
  movq $1, rdx
  movq $r85, r8
  call substring
  movq $r85, rax
  addq $9, rax
  movq rax, $r97
  movq $r82, rcx
  call lm_list_len
  movq $r82, rcx
  movq $r97, rdx
  movq $r98, r8
  call substring
  movq [rel str_const_150], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq $r99, rcx
  movq [rbp + -288], rdx
  call std.semver.index_of
  movq $9, rax
  negq rax
  movq rax, [rbp + -296]
  movq $r102, rax
  cmpq [rbp + -296], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  testq rax, rax
  jne std.semver.parse_block_123
  jmp std.semver.parse_block_125
std.semver.parse_block_123:
  jmp std.semver.parse_block_123
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -312]
  movq [rbp + -312], rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_125:
  movq $r76, rcx
  call std.semver.has_invalid_leading_zero
  movq $r110, rax
  testq rax, rax
  jne std.semver.parse_block_131
  jmp std.semver.parse_block_128
std.semver.parse_block_128:
  jmp std.semver.parse_block_128
  movq $r93, rcx
  call std.semver.has_invalid_leading_zero
  jmp std.semver.parse_block_131
std.semver.parse_block_131:
  movq $r111, rax
  testq rax, rax
  jne std.semver.parse_block_136
  jmp std.semver.parse_block_133
std.semver.parse_block_133:
  jmp std.semver.parse_block_133
  movq $r99, rcx
  call std.semver.has_invalid_leading_zero
  jmp std.semver.parse_block_136
std.semver.parse_block_136:
  movq $r112, rax
  testq rax, rax
  jne std.semver.parse_block_137
  jmp std.semver.parse_block_139
std.semver.parse_block_137:
  jmp std.semver.parse_block_137
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_139:
  movq $r76, rcx
  call std.semver.to_int
  movq $9, rax
  negq rax
  movq rax, [rbp + -328]
  movq $r115, rax
  cmpq [rbp + -328], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -336]
  movq [rbp + -336], rax
  testq rax, rax
  jne std.semver.parse_block_145
  jmp std.semver.parse_block_147
std.semver.parse_block_145:
  jmp std.semver.parse_block_145
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_147:
  movq $r93, rcx
  call std.semver.to_int
  movq $9, rax
  negq rax
  movq rax, [rbp + -352]
  movq $r122, rax
  cmpq [rbp + -352], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rbp + -360], rax
  testq rax, rax
  jne std.semver.parse_block_153
  jmp std.semver.parse_block_155
std.semver.parse_block_153:
  jmp std.semver.parse_block_153
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -368]
  movq [rbp + -368], rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_155:
  movq $r99, rcx
  call std.semver.to_int
  movq $9, rax
  negq rax
  movq rax, [rbp + -376]
  movq $r129, rax
  cmpq [rbp + -376], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -384]
  movq [rbp + -384], rax
  testq rax, rax
  jne std.semver.parse_block_161
  jmp std.semver.parse_block_163
std.semver.parse_block_161:
  jmp std.semver.parse_block_161
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  jmp std.semver.parse_epilogue
std.semver.parse_block_163:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -400], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -400], rcx
  movq $r115, rdx
  movq $r122, r8
  movq $r129, r9
  call std.semver.Version.init
  movq [rbp + -400], rax
  jmp std.semver.parse_epilogue
std.semver.parse_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.semver.parse:

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

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
  .string "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
.align 8
str_const_2:
  .string "abcdefghijklmnopqrstuvwxyz"
.align 8
str_const_3:
  .string " "
.align 8
str_const_4:
  .string "	"
.align 8
str_const_5:
  .string "
"
.align 8
str_const_6:
  .string ""
.align 8
str_const_7:
  .string " "
.align 8
str_const_8:
  .string "	"
.align 8
str_const_9:
  .string "
"
.align 8
str_const_10:
  .string ""
.align 8
str_const_11:
  .string ""
.align 8
str_const_12:
  .string "0123456789abcdef"
.align 8
str_const_13:
  .string "Running UUID generation tests..."
.align 8
str_const_14:
  .string "g1 should be valid"
.align 8
str_const_15:
  .string "g1 version should be 4"
.align 8
str_const_16:
  .string "g1 variant should be 1 (RFC 4122)"
.align 8
str_const_17:
  .string "g2 should be valid"
.align 8
str_const_18:
  .string "g2 version should be 4"
.align 8
str_const_19:
  .string "g1 should not equal g2 (must be unique)"
.align 8
str_const_20:
  .string "g1_str should be 36 characters"
.align 8
str_const_21:
  .string "parsed_g1 should be valid"
.align 8
str_const_22:
  .string "parsed_g1 should equal g1"
.align 8
str_const_23:
  .string "Generation tests passed!"
.align 8
str_const_24:
  .string "=== UUID Module Test Suite ==="
.align 8
str_const_25:
  .string "Parsing tests failed"
.align 8
str_const_26:
  .string "Generation tests failed"
.align 8
str_const_27:
  .string "All UUID tests completed successfully."
.align 8
str_const_28:
  .string "Running UUID parsing tests..."
.align 8
str_const_29:
  .string "f81d4fae-7dec-11d0-a765-00a0c91e6bf6"
.align 8
str_const_30:
  .string "u1 should be valid"
.align 8
str_const_31:
  .string "f81d4fae-7dec-11d0-a765-00a0c91e6bf6"
.align 8
str_const_32:
  .string "to_string matches input"
.align 8
str_const_33:
  .string "u1 version should be 1"
.align 8
str_const_34:
  .string "u1 variant should be 1 (RFC 4122)"
.align 8
str_const_35:
  .string "{"
.align 8
str_const_36:
  .string "}"
.align 8
str_const_37:
  .string "F81D4FAE-7DEC-11D0-A765-00A0C91E6BF6"
.align 8
str_const_38:
  .string "u2 should be valid"
.align 8
str_const_39:
  .string "f81d4fae-7dec-11d0-a765-00a0c91e6bf6"
.align 8
str_const_40:
  .string "to_string should be lowercase"
.align 8
str_const_41:
  .string "u1 should equal u2"
.align 8
str_const_42:
  .string "f81d4fae7dec-11d0-a765-00a0c91e6bf6"
.align 8
str_const_43:
  .string "u3 should be invalid (missing dash)"
.align 8
str_const_44:
  .string "f81d4fae-7dec-11d0-a765-00a0c91e6bfg"
.align 8
str_const_45:
  .string "u4 should be invalid (invalid hex character g)"
.align 8
str_const_46:
  .string "f81d4fae-7dec-11d0"
.align 8
str_const_47:
  .string "u5 should be invalid (short)"
.align 8
str_const_48:
  .string "Parsing tests passed!"
.align 8
str_const_49:
  .string "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
.align 8
str_const_50:
  .string "{"
.align 8
str_const_51:
  .string "}"
.align 8
str_const_52:
  .string "-"
.align 8
str_const_53:
  .string "-"
.align 8
str_const_54:
  .string "-"
.align 8
str_const_55:
  .string "-"
.align 8
str_const_56:
  .string "0123456789abcdef"
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
  call std.uuid.index.__init__
  call std.uuid.uuid.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq [rel str_const_24], rcx
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
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_generation
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq [rel str_const_27], rcx
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

.globl std.uuid.generator.__init__
std.uuid.generator.__init__:
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
std.uuid.generator.__init___entry:
  movq $0, rax
  jmp std.uuid.generator.__init___epilogue
std.uuid.generator.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.generator.__init__:

.globl std.uuid.index.generate_v4
std.uuid.index.generate_v4:
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
std.uuid.index.generate_v4_entry:
std.uuid.index.generate_v4_block_0:
  call std.uuid.generator.generate_v4
  movq $0, rax
  jmp std.uuid.index.generate_v4_epilogue
std.uuid.index.generate_v4_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.index.generate_v4:

.globl std.uuid.uuid.__init__
std.uuid.uuid.__init__:
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
std.uuid.uuid.__init___entry:
  movq $0, rax
  jmp std.uuid.uuid.__init___epilogue
std.uuid.uuid.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.uuid.__init__:

.globl std.uuid.uuid.index_of
std.uuid.uuid.index_of:
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
std.uuid.uuid.index_of_entry:
std.uuid.uuid.index_of_block_0:
  jmp std.uuid.uuid.index_of_block_2
std.uuid.uuid.index_of_block_2:
  movq [rbp + -64], rcx
  call lm_list_len
  movq [rbp + -72], rcx
  call lm_list_len
  movq $r3, rax
  subq $r4, rax
  movq rax, $r5
  movq $1, rax
  cmpq $r5, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.uuid.uuid.index_of_block_7
  jmp std.uuid.uuid.index_of_block_19
std.uuid.uuid.index_of_block_7:
  jmp std.uuid.uuid.index_of_block_7
  movq [rbp + -72], rcx
  call lm_list_len
  movq [rbp + -72], rcx
  call lm_list_len
  movq $1, rax
  addq $r9, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -88], r8
  call substring
  movq $r11, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.uuid.uuid.index_of_block_13
  jmp std.uuid.uuid.index_of_block_14
std.uuid.uuid.index_of_block_13:
  jmp std.uuid.uuid.index_of_block_13
  movq $1, rax
  jmp std.uuid.uuid.index_of_epilogue
std.uuid.uuid.index_of_block_14:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.uuid.uuid.index_of_block_2
std.uuid.uuid.index_of_block_19:
  movq $9, rax
  negq rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp std.uuid.uuid.index_of_epilogue
std.uuid.uuid.index_of_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.uuid.index_of:

.globl std.uuid.uuid.to_lower
std.uuid.uuid.to_lower:
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
std.uuid.uuid.to_lower_entry:
std.uuid.uuid.to_lower_block_0:
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  jmp std.uuid.uuid.to_lower_block_5
std.uuid.uuid.to_lower_block_5:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.uuid.uuid.to_lower_block_8
  jmp std.uuid.uuid.to_lower_block_35
std.uuid.uuid.to_lower_block_8:
  jmp std.uuid.uuid.to_lower_block_8
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -104], r8
  call substring
  movq [rbp + -80], rcx
  movq $r11, rdx
  call std.uuid.uuid.index_of
  movq $9, rax
  negq rax
  movq rax, [rbp + -112]
  movq $r13, rax
  cmpq [rbp + -112], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.uuid.uuid.to_lower_block_19
  jmp std.uuid.uuid.to_lower_block_27
std.uuid.uuid.to_lower_block_19:
  jmp std.uuid.uuid.to_lower_block_19
  movq $r13, rax
  addq $9, rax
  movq rax, $r21
  movq [rbp + -88], rcx
  movq $r13, rdx
  movq $r21, r8
  call substring
  movq $r22, rcx
  call lm_to_string
  movq rax, [rbp + -128]
  movq [rbp + -72], rcx
  movq [rbp + -128], rdx
  call lm_str_concat
  movq rax, [rbp + -136]
  jmp std.uuid.uuid.to_lower_block_30
std.uuid.uuid.to_lower_block_27:
  movq [rbp + -136], rcx
  movq $r11, rdx
  call lm_str_concat
  movq rax, [rbp + -144]
  jmp std.uuid.uuid.to_lower_block_30
std.uuid.uuid.to_lower_block_30:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -152]
  jmp std.uuid.uuid.to_lower_block_5
std.uuid.uuid.to_lower_block_35:
  movq [rbp + -144], rax
  jmp std.uuid.uuid.to_lower_epilogue
std.uuid.uuid.to_lower_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.uuid.to_lower:

.globl std.uuid.uuid.trim
std.uuid.uuid.trim:
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
std.uuid.uuid.trim_entry:
std.uuid.uuid.trim_block_0:
  jmp std.uuid.uuid.trim_block_2
std.uuid.uuid.trim_block_2:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.uuid.uuid.trim_block_6
  jmp std.uuid.uuid.trim_block_44
std.uuid.uuid.trim_block_6:
  jmp std.uuid.uuid.trim_block_6
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -80]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -80], r8
  call substring
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $r11, rax
  cmpq [rbp + -88], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.uuid.uuid.trim_block_22
  jmp std.uuid.uuid.trim_block_14
std.uuid.uuid.trim_block_14:
  jmp std.uuid.uuid.trim_block_14
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -104], r8
  call substring
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r17, rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  jmp std.uuid.uuid.trim_block_22
std.uuid.uuid.trim_block_22:
  movq [rbp + -120], rax
  testq rax, rax
  jne std.uuid.uuid.trim_block_32
  jmp std.uuid.uuid.trim_block_24
std.uuid.uuid.trim_block_24:
  jmp std.uuid.uuid.trim_block_24
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -128]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -128], r8
  call substring
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r23, rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  jmp std.uuid.uuid.trim_block_32
std.uuid.uuid.trim_block_32:
  movq [rbp + -144], rax
  testq rax, rax
  jne std.uuid.uuid.trim_block_42
  jmp std.uuid.uuid.trim_block_34
std.uuid.uuid.trim_block_34:
  jmp std.uuid.uuid.trim_block_34
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -152]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -152], r8
  call substring
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq $r29, rax
  cmpq [rbp + -160], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  jmp std.uuid.uuid.trim_block_42
std.uuid.uuid.trim_block_42:
  jmp std.uuid.uuid.trim_block_44
std.uuid.uuid.trim_block_44:
  movq [rbp + -168], rax
  testq rax, rax
  jne std.uuid.uuid.trim_block_45
  jmp std.uuid.uuid.trim_block_50
std.uuid.uuid.trim_block_45:
  jmp std.uuid.uuid.trim_block_45
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -176]
  jmp std.uuid.uuid.trim_block_2
std.uuid.uuid.trim_block_50:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r36, rax
  subq $9, rax
  movq rax, $r38
  jmp std.uuid.uuid.trim_block_55
std.uuid.uuid.trim_block_55:
  movq $r38, rax
  cmpq [rbp + -176], rax
  setge al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  testq rax, rax
  jne std.uuid.uuid.trim_block_58
  jmp std.uuid.uuid.trim_block_96
std.uuid.uuid.trim_block_58:
  jmp std.uuid.uuid.trim_block_58
  movq $r38, rax
  addq $9, rax
  movq rax, $r47
  movq [rbp + -64], rcx
  movq $r38, rdx
  movq $r47, r8
  call substring
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq $r48, rax
  cmpq [rbp + -192], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  testq rax, rax
  jne std.uuid.uuid.trim_block_74
  jmp std.uuid.uuid.trim_block_66
std.uuid.uuid.trim_block_66:
  jmp std.uuid.uuid.trim_block_66
  movq $r38, rax
  addq $9, rax
  movq rax, $r53
  movq [rbp + -64], rcx
  movq $r38, rdx
  movq $r53, r8
  call substring
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq $r54, rax
  cmpq [rbp + -208], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -216]
  jmp std.uuid.uuid.trim_block_74
std.uuid.uuid.trim_block_74:
  movq [rbp + -216], rax
  testq rax, rax
  jne std.uuid.uuid.trim_block_84
  jmp std.uuid.uuid.trim_block_76
std.uuid.uuid.trim_block_76:
  jmp std.uuid.uuid.trim_block_76
  movq $r38, rax
  addq $9, rax
  movq rax, $r59
  movq [rbp + -64], rcx
  movq $r38, rdx
  movq $r59, r8
  call substring
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq $r60, rax
  cmpq [rbp + -224], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  jmp std.uuid.uuid.trim_block_84
std.uuid.uuid.trim_block_84:
  movq [rbp + -232], rax
  testq rax, rax
  jne std.uuid.uuid.trim_block_94
  jmp std.uuid.uuid.trim_block_86
std.uuid.uuid.trim_block_86:
  jmp std.uuid.uuid.trim_block_86
  movq $r38, rax
  addq $9, rax
  movq rax, $r65
  movq [rbp + -64], rcx
  movq $r38, rdx
  movq $r65, r8
  call substring
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq $r66, rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  jmp std.uuid.uuid.trim_block_94
std.uuid.uuid.trim_block_94:
  jmp std.uuid.uuid.trim_block_96
std.uuid.uuid.trim_block_96:
  movq [rbp + -248], rax
  testq rax, rax
  jne std.uuid.uuid.trim_block_97
  jmp std.uuid.uuid.trim_block_101
std.uuid.uuid.trim_block_97:
  jmp std.uuid.uuid.trim_block_97
  movq $r38, rax
  subq $9, rax
  movq rax, $r71
  jmp std.uuid.uuid.trim_block_55
std.uuid.uuid.trim_block_101:
  movq [rbp + -176], rax
  cmpq $r71, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  testq rax, rax
  jne std.uuid.uuid.trim_block_103
  jmp std.uuid.uuid.trim_block_105
std.uuid.uuid.trim_block_103:
  jmp std.uuid.uuid.trim_block_103
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  jmp std.uuid.uuid.trim_epilogue
std.uuid.uuid.trim_block_105:
  movq $r71, rax
  addq $9, rax
  movq rax, $r77
  movq [rbp + -64], rcx
  movq [rbp + -176], rdx
  movq $r77, r8
  call substring
  movq $r78, rax
  jmp std.uuid.uuid.trim_epilogue
std.uuid.uuid.trim_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.uuid.trim:

.globl std.uuid.uuid.byte_to_hex
std.uuid.uuid.byte_to_hex:
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
std.uuid.uuid.byte_to_hex_entry:
std.uuid.uuid.byte_to_hex_block_0:
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  movq $33, rcx
  shrq %cl, rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  andq $121, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  andq $121, rax
  movq rax, [rbp + -96]
  movq [rbp + -88], rax
  addq $9, rax
  movq rax, [rbp + -104]
  movq [rbp + -72], rcx
  movq [rbp + -88], rdx
  movq [rbp + -104], r8
  call substring
  movq [rbp + -96], rax
  addq $9, rax
  movq rax, [rbp + -112]
  movq [rbp + -72], rcx
  movq [rbp + -96], rdx
  movq [rbp + -112], r8
  call substring
  movq [rbp + -88], rax
  addq $9, rax
  movq rax, [rbp + -120]
  movq [rbp + -72], rcx
  movq [rbp + -88], rdx
  movq [rbp + -120], r8
  call substring
  movq [rbp + -96], rax
  addq $9, rax
  movq rax, [rbp + -128]
  movq [rbp + -72], rcx
  movq [rbp + -96], rdx
  movq [rbp + -128], r8
  call substring
  movq $r21, rax
  addq $r25, rax
  movq rax, $r26
  movq $r26, rax
  jmp std.uuid.uuid.byte_to_hex_epilogue
std.uuid.uuid.byte_to_hex_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.uuid.byte_to_hex:

.globl std.uuid.uuid.UUID.init
std.uuid.uuid.UUID.init:
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
std.uuid.uuid.UUID.init_entry:
  movq $0, rax
  jmp std.uuid.uuid.UUID.init_epilogue
std.uuid.uuid.UUID.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.uuid.UUID.init:

.globl std.uuid.uuid.UUID.equals
std.uuid.uuid.UUID.equals:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.uuid.uuid.UUID.equals_entry:
  movq $0, rax
  jmp std.uuid.uuid.UUID.equals_epilogue
std.uuid.uuid.UUID.equals_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.uuid.UUID.equals:

.globl std.uuid.uuid.UUID.variant
std.uuid.uuid.UUID.variant:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.uuid.uuid.UUID.variant_entry:
  movq $0, rax
  jmp std.uuid.uuid.UUID.variant_epilogue
std.uuid.uuid.UUID.variant_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.uuid.UUID.variant:

.globl std.uuid.uuid.UUID.version
std.uuid.uuid.UUID.version:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.uuid.uuid.UUID.version_entry:
  movq $0, rax
  jmp std.uuid.uuid.UUID.version_epilogue
std.uuid.uuid.UUID.version_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.uuid.UUID.version:

.globl std.internal.runtime.create
std.internal.runtime.create:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.internal.runtime.create_entry:
std.internal.runtime.create_block_0:
  movq $0, rax
  jmp std.internal.runtime.create_epilogue
std.internal.runtime.create_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.internal.runtime.create:

.globl std.random.random.__init__
std.random.random.__init__:
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
std.random.random.__init___entry:
  movq $0, rax
  jmp std.random.random.__init___epilogue
std.random.random.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.__init__:

.globl std.random.random.random_bool
std.random.random.random_bool:
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
std.random.random.random_bool_entry:
std.random.random.random_bool_block_0:
  movq $0, rcx
  call std.random.random.Random.next_bool
  movq $r1, rax
  jmp std.random.random.random_bool_epilogue
std.random.random.random_bool_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.random_bool:

.globl std.random.random.random_float
std.random.random.random_float:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.random.random.random_float_entry:
std.random.random.random_float_block_0:
  movq $0, rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.random.random.Random.range_float
  movq $r3, rax
  jmp std.random.random.random_float_epilogue
std.random.random.random_float_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.random_float:

.globl std.internal.runtime.call
std.internal.runtime.call:
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
std.internal.runtime.call_entry:
std.internal.runtime.call_block_0:
  movq $0, rax
  jmp std.internal.runtime.call_epilogue
std.internal.runtime.call_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.internal.runtime.call:

.globl std.random.random.SecureRandom.init
std.random.random.SecureRandom.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.random.random.SecureRandom.init_entry:
  movq $0, rax
  jmp std.random.random.SecureRandom.init_epilogue
std.random.random.SecureRandom.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.SecureRandom.init:

.globl std.random.random.SecureRandom.next_bytes
std.random.random.SecureRandom.next_bytes:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.random.random.SecureRandom.next_bytes_entry:
  movq $0, rax
  jmp std.random.random.SecureRandom.next_bytes_epilogue
std.random.random.SecureRandom.next_bytes_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.SecureRandom.next_bytes:

.globl std.random.random.SecureRandom.next_float
std.random.random.SecureRandom.next_float:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.random.random.SecureRandom.next_float_entry:
  movq $0, rax
  jmp std.random.random.SecureRandom.next_float_epilogue
std.random.random.SecureRandom.next_float_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.SecureRandom.next_float:

.globl std.random.random.SecureRandom.next_int
std.random.random.SecureRandom.next_int:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.random.random.SecureRandom.next_int_entry:
  movq $0, rax
  jmp std.random.random.SecureRandom.next_int_epilogue
std.random.random.SecureRandom.next_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.SecureRandom.next_int:

.globl std.internal.runtime.destroy
std.internal.runtime.destroy:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.internal.runtime.destroy_entry:
std.internal.runtime.destroy_block_0:
  movq $0, rax
  jmp std.internal.runtime.destroy_epilogue
std.internal.runtime.destroy_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.internal.runtime.destroy:

.globl std.resource.ResourceWriter.init
std.resource.ResourceWriter.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.resource.ResourceWriter.init_entry:
  movq $0, rax
  jmp std.resource.ResourceWriter.init_epilogue
std.resource.ResourceWriter.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.ResourceWriter.init:

.globl std.resource.ResourceWriter.write
std.resource.ResourceWriter.write:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.resource.ResourceWriter.write_entry:
  movq $0, rax
  jmp std.resource.ResourceWriter.write_epilogue
std.resource.ResourceWriter.write_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.ResourceWriter.write:

.globl test_generation
test_generation:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 328
test_generation_entry:
test_generation_block_0:
  movq [rel str_const_13], rcx
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
  call std.uuid.index.generate_v4
  movq $r2, rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  addq $0, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.uuid.uuid.UUID.version
  movq $r10, rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.uuid.uuid.UUID.variant
  movq $r15, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  call std.uuid.index.generate_v4
  movq $r20, rax
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  addq $0, rax
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq [rbp + -168], rcx
  call std.uuid.uuid.UUID.version
  movq $r28, rax
  cmpq $33, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq [rbp + -96], rcx
  movq [rbp + -168], rdx
  call std.uuid.uuid.UUID.equals
  movq $r33, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  movq [rbp + -96], rcx
  call std.uuid.uuid.UUID.to_string
  movq $r38, rcx
  call lm_list_len
  movq $r40, rax
  cmpq $289, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq $r38, rcx
  call std.uuid.index.parse
  movq $r45, rax
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  addq $0, rax
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -280]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -280], rcx
  movq [rbp + -288], rdx
  call lm_assert
  movq [rbp + -96], rcx
  movq [rbp + -256], rdx
  call std.uuid.uuid.UUID.equals
  movq $r53, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -296], rcx
  movq [rbp + -304], rdx
  call lm_assert
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -312], rax
  addq $16, rax
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  mov rax, [rax]
  movq rax, [rbp + -336]
  movq [rbp + -336], rcx
  call lm_print_str
  movq $9, rax
  jmp test_generation_epilogue
test_generation_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_generation:

.globl std.resource.Resource._handle
std.resource.Resource._handle:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.resource.Resource._handle_entry:
  movq $0, rax
  jmp std.resource.Resource._handle_epilogue
std.resource.Resource._handle_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Resource._handle:

.globl std.resource.Resource.close
std.resource.Resource.close:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.resource.Resource.close_entry:
  movq $0, rax
  jmp std.resource.Resource.close_epilogue
std.resource.Resource.close_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Resource.close:

.globl std.uuid.index.parse
std.uuid.index.parse:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.uuid.index.parse_entry:
std.uuid.index.parse_block_0:
  movq [rbp + -64], rcx
  call std.uuid.uuid.parse
  movq $r1, rax
  jmp std.uuid.index.parse_epilogue
std.uuid.index.parse_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.index.parse:

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
  sub rsp, 472
test_parsing_entry:
test_parsing_block_0:
  movq [rel str_const_28], rcx
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
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.uuid.index.parse
  movq $r3, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rbp + -104], rcx
  call std.uuid.uuid.UUID.to_string
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq $r11, rax
  cmpq [rbp + -144], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq [rbp + -104], rcx
  call std.uuid.uuid.UUID.version
  movq $r16, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call lm_assert
  movq [rbp + -104], rcx
  call std.uuid.uuid.UUID.variant
  movq $r21, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -184], rcx
  movq [rbp + -192], rdx
  call lm_assert
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -200], rcx
  movq [rbp + -216], rdx
  call lm_str_concat
  movq rax, [rbp + -224]
  movq [rbp + -224], rcx
  movq [rbp + -208], rdx
  call lm_str_concat
  movq rax, [rbp + -232]
  movq [rbp + -232], rcx
  call std.uuid.index.parse
  movq $r32, rax
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  addq $0, rax
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -264]
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -264], rcx
  movq [rbp + -272], rdx
  call lm_assert
  movq [rbp + -240], rcx
  call std.uuid.uuid.UUID.to_string
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq $r40, rax
  cmpq [rbp + -280], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -288]
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -288], rcx
  movq [rbp + -296], rdx
  call lm_assert
  movq [rbp + -104], rcx
  movq [rbp + -240], rdx
  call std.uuid.uuid.UUID.equals
  movq $r45, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -304]
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -304], rcx
  movq [rbp + -312], rdx
  call lm_assert
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -320], rcx
  call std.uuid.index.parse
  movq $r51, rax
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  addq $0, rax
  movq rax, [rbp + -336]
  movq [rbp + -336], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -352]
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -352], rcx
  movq [rbp + -360], rdx
  call lm_assert
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -368], rcx
  call std.uuid.index.parse
  movq $r60, rax
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  addq $0, rax
  movq rax, [rbp + -384]
  movq [rbp + -384], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -400]
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -400], rcx
  movq [rbp + -408], rdx
  call lm_assert
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -416], rcx
  call std.uuid.index.parse
  movq $r69, rax
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  addq $0, rax
  movq rax, [rbp + -432]
  movq [rbp + -432], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -448]
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq [rbp + -448], rcx
  movq [rbp + -456], rdx
  call lm_assert
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq [rbp + -464], rax
  addq $16, rax
  movq rax, [rbp + -472]
  movq [rbp + -472], rax
  movq rax, [rbp + -480]
  movq [rbp + -480], rax
  mov rax, [rax]
  movq rax, [rbp + -488]
  movq [rbp + -488], rcx
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

.globl std.resource.ResourceReader.init
std.resource.ResourceReader.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.resource.ResourceReader.init_entry:
  movq $0, rax
  jmp std.resource.ResourceReader.init_epilogue
std.resource.ResourceReader.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.ResourceReader.init:

.globl std.uuid.index.UUID
std.uuid.index.UUID:
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
std.uuid.index.UUID_entry:
std.uuid.index.UUID_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.uuid.uuid.UUID.init
  movq [rbp + -80], rax
  jmp std.uuid.index.UUID_epilogue
std.uuid.index.UUID_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.index.UUID:

.globl std.resource.create
std.resource.create:
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
std.resource.create_entry:
std.resource.create_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -80]
  movq $r2, rax
  cmpq [rbp + -80], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.resource.create_block_6
  jmp std.resource.create_block_8
std.resource.create_block_6:
  jmp std.resource.create_block_6
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp std.resource.create_epilogue
std.resource.create_block_8:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -104], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -104], rcx
  movq $r2, rdx
  movq [rbp + -64], r8
  call std.resource.Resource.init
  movq [rbp + -104], rax
  jmp std.resource.create_epilogue
std.resource.create_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.create:

.globl std.uuid.uuid.UUID.to_string
std.uuid.uuid.UUID.to_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.uuid.uuid.UUID.to_string_entry:
  movq $0, rax
  jmp std.uuid.uuid.UUID.to_string_epilogue
std.uuid.uuid.UUID.to_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.uuid.UUID.to_string:

.globl std.internal.runtime.__init__
std.internal.runtime.__init__:
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
std.internal.runtime.__init___entry:
  movq $0, rax
  jmp std.internal.runtime.__init___epilogue
std.internal.runtime.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.internal.runtime.__init__:

.globl std.resource.Resource.is_open
std.resource.Resource.is_open:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.resource.Resource.is_open_entry:
  movq $0, rax
  jmp std.resource.Resource.is_open_epilogue
std.resource.Resource.is_open_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Resource.is_open:

.globl std.resource.Poller.poll
std.resource.Poller.poll:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.resource.Poller.poll_entry:
  movq $0, rax
  jmp std.resource.Poller.poll_epilogue
std.resource.Poller.poll_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Poller.poll:

.globl std.uuid.generator.generate_v4
std.uuid.generator.generate_v4:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.uuid.generator.generate_v4_entry:
std.uuid.generator.generate_v4_block_0:
  movq $129, rcx
  call std.random.random.random_bytes
  movq $r1, rcx
  movq $49, rdx
  call lm_list_get
  movq $r4, rax
  andq $121, rax
  movq rax, $r6
  movq $r6, rax
  orq $513, rax
  movq rax, $r8
  movq $0, rcx
  movq $65, rdx
  call lm_list_get
  movq $r12, rax
  andq $505, rax
  movq rax, $r14
  movq $r14, rax
  orq $1025, rax
  movq rax, $r16
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  movq $0, rdx
  movq $18, r8
  call std.uuid.uuid.UUID.init
  movq [rbp + -64], rax
  jmp std.uuid.generator.generate_v4_epilogue
std.uuid.generator.generate_v4_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.generator.generate_v4:

.globl std.resource.Pollable.init
std.resource.Pollable.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.resource.Pollable.init_entry:
  movq $0, rax
  jmp std.resource.Pollable.init_epilogue
std.resource.Pollable.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Pollable.init:

.globl std.random.random.Random.range_int
std.random.random.Random.range_int:
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
std.random.random.Random.range_int_entry:
  movq $0, rax
  jmp std.random.random.Random.range_int_epilogue
std.random.random.Random.range_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.Random.range_int:

.globl std.random.random.random_string
std.random.random.random_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.random.random.random_string_entry:
std.random.random.random_string_block_0:
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $0, rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.random.random.Random.next_string
  movq $r3, rax
  jmp std.random.random.random_string_epilogue
std.random.random.random_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.random_string:

.globl std.resource.Resource.init
std.resource.Resource.init:
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
std.resource.Resource.init_entry:
  movq $0, rax
  jmp std.resource.Resource.init_epilogue
std.resource.Resource.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Resource.init:

.globl std.random.random.random_bytes
std.random.random.random_bytes:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.random.random.random_bytes_entry:
std.random.random.random_bytes_block_0:
  movq $0, rcx
  movq [rbp + -64], rdx
  call std.random.random.Random.next_bytes
  movq $r2, rax
  jmp std.random.random.random_bytes_epilogue
std.random.random.random_bytes_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.random_bytes:

.globl std.random.random.Random.next_bool
std.random.random.Random.next_bool:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.random.random.Random.next_bool_entry:
  movq $0, rax
  jmp std.random.random.Random.next_bool_epilogue
std.random.random.Random.next_bool_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.Random.next_bool:

.globl std.resource.Pollable.poll
std.resource.Pollable.poll:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.resource.Pollable.poll_entry:
  movq $0, rax
  jmp std.resource.Pollable.poll_epilogue
std.resource.Pollable.poll_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Pollable.poll:

.globl std.uuid.index.__init__
std.uuid.index.__init__:
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
std.uuid.index.__init___entry:
  movq $0, rax
  jmp std.uuid.index.__init___epilogue
std.uuid.index.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.index.__init__:

.globl std.resource.Poller.init
std.resource.Poller.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.resource.Poller.init_entry:
  movq $0, rax
  jmp std.resource.Poller.init_epilogue
std.resource.Poller.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Poller.init:

.globl std.resource.Connector.connect
std.resource.Connector.connect:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.resource.Connector.connect_entry:
  movq $0, rax
  jmp std.resource.Connector.connect_epilogue
std.resource.Connector.connect_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Connector.connect:

.globl std.resource.Accepter.accept
std.resource.Accepter.accept:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.resource.Accepter.accept_entry:
  movq $0, rax
  jmp std.resource.Accepter.accept_epilogue
std.resource.Accepter.accept_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Accepter.accept:

.globl std.resource.create_socket
std.resource.create_socket:
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
std.resource.create_socket_entry:
std.resource.create_socket_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_socket_block_8
  jmp std.resource.create_socket_block_10
std.resource.create_socket_block_8:
  jmp std.resource.create_socket_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_socket_epilogue
std.resource.create_socket_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_socket_epilogue
std.resource.create_socket_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.create_socket:

.globl std.resource.Connector.init
std.resource.Connector.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.resource.Connector.init_entry:
  movq $0, rax
  jmp std.resource.Connector.init_epilogue
std.resource.Connector.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Connector.init:

.globl std.resource.Binder.bind
std.resource.Binder.bind:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.resource.Binder.bind_entry:
  movq $0, rax
  jmp std.resource.Binder.bind_epilogue
std.resource.Binder.bind_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Binder.bind:

.globl std.resource.create_hash_engine
std.resource.create_hash_engine:
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
std.resource.create_hash_engine_entry:
std.resource.create_hash_engine_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_hash_engine_block_8
  jmp std.resource.create_hash_engine_block_10
std.resource.create_hash_engine_block_8:
  jmp std.resource.create_hash_engine_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_hash_engine_epilogue
std.resource.create_hash_engine_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_hash_engine_epilogue
std.resource.create_hash_engine_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.create_hash_engine:

.globl std.random.random.Random.next_bytes
std.random.random.Random.next_bytes:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.random.random.Random.next_bytes_entry:
  movq $0, rax
  jmp std.random.random.Random.next_bytes_epilogue
std.random.random.Random.next_bytes_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.Random.next_bytes:

.globl std.resource.Binder.init
std.resource.Binder.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.resource.Binder.init_entry:
  movq $0, rax
  jmp std.resource.Binder.init_epilogue
std.resource.Binder.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Binder.init:

.globl std.resource.Listener.listen
std.resource.Listener.listen:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.resource.Listener.listen_entry:
  movq $0, rax
  jmp std.resource.Listener.listen_epilogue
std.resource.Listener.listen_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Listener.listen:

.globl std.resource.Listener.init
std.resource.Listener.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.resource.Listener.init_entry:
  movq $0, rax
  jmp std.resource.Listener.init_epilogue
std.resource.Listener.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Listener.init:

.globl std.resource.Accepter.init
std.resource.Accepter.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.resource.Accepter.init_entry:
  movq $0, rax
  jmp std.resource.Accepter.init_epilogue
std.resource.Accepter.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.Accepter.init:

.globl std.resource.ResourceReader.read
std.resource.ResourceReader.read:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.resource.ResourceReader.read_entry:
  movq $0, rax
  jmp std.resource.ResourceReader.read_epilogue
std.resource.ResourceReader.read_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.ResourceReader.read:

.globl std.resource.create_dns_resolver
std.resource.create_dns_resolver:
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
std.resource.create_dns_resolver_entry:
std.resource.create_dns_resolver_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_dns_resolver_block_8
  jmp std.resource.create_dns_resolver_block_10
std.resource.create_dns_resolver_block_8:
  jmp std.resource.create_dns_resolver_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_dns_resolver_epilogue
std.resource.create_dns_resolver_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_dns_resolver_epilogue
std.resource.create_dns_resolver_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.create_dns_resolver:

.globl std.resource.create_udp_socket
std.resource.create_udp_socket:
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
std.resource.create_udp_socket_entry:
std.resource.create_udp_socket_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_udp_socket_block_8
  jmp std.resource.create_udp_socket_block_10
std.resource.create_udp_socket_block_8:
  jmp std.resource.create_udp_socket_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_udp_socket_epilogue
std.resource.create_udp_socket_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_udp_socket_epilogue
std.resource.create_udp_socket_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.create_udp_socket:

.globl std.resource.create_websocket
std.resource.create_websocket:
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
std.resource.create_websocket_entry:
std.resource.create_websocket_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_websocket_block_8
  jmp std.resource.create_websocket_block_10
std.resource.create_websocket_block_8:
  jmp std.resource.create_websocket_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_websocket_epilogue
std.resource.create_websocket_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_websocket_epilogue
std.resource.create_websocket_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.create_websocket:

.globl std.resource.open_file
std.resource.open_file:
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
std.resource.open_file_entry:
std.resource.open_file_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r3, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -80]
  movq $r4, rax
  cmpq [rbp + -80], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.resource.open_file_block_8
  jmp std.resource.open_file_block_10
std.resource.open_file_block_8:
  jmp std.resource.open_file_block_8
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp std.resource.open_file_epilogue
std.resource.open_file_block_10:
  movq $0, rcx
  call lm_list_new
  movq $r12, rcx
  movq [rbp + -64], rdx
  call lm_list_append
  movq $r12, rcx
  movq [rbp + -72], rdx
  call lm_list_append
  movq $r4, rcx
  movq $0, rdx
  movq $r12, r8
  call std.internal.runtime.call
  movq $r15, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.resource.open_file_block_19
  jmp std.resource.open_file_block_22
std.resource.open_file_block_19:
  jmp std.resource.open_file_block_19
  movq $r4, rcx
  call std.internal.runtime.destroy
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp std.resource.open_file_epilogue
std.resource.open_file_block_22:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -120], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -120], rcx
  movq $r4, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -120], rax
  jmp std.resource.open_file_epilogue
std.resource.open_file_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.open_file:

.globl std.resource.create_entropy
std.resource.create_entropy:
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
std.resource.create_entropy_entry:
std.resource.create_entropy_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_entropy_block_8
  jmp std.resource.create_entropy_block_10
std.resource.create_entropy_block_8:
  jmp std.resource.create_entropy_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_entropy_epilogue
std.resource.create_entropy_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_entropy_epilogue
std.resource.create_entropy_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.create_entropy:

.globl std.random.random.random_int
std.random.random.random_int:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.random.random.random_int_entry:
std.random.random.random_int_block_0:
  movq $0, rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.random.random.Random.range_int
  movq $r3, rax
  jmp std.random.random.random_int_epilogue
std.random.random.random_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.random_int:

.globl std.resource.adopt_socket
std.resource.adopt_socket:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.resource.adopt_socket_entry:
std.resource.adopt_socket_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -72], rax
  jmp std.resource.adopt_socket_epilogue
std.resource.adopt_socket_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.adopt_socket:

.globl std.resource.create_fs_resource
std.resource.create_fs_resource:
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
std.resource.create_fs_resource_entry:
std.resource.create_fs_resource_block_0:
  movq $0, rcx
  call lm_list_new
  movq $0, rcx
  movq $r1, rdx
  call std.internal.runtime.create
  movq $9, rax
  negq rax
  movq rax, [rbp + -64]
  movq $r2, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.resource.create_fs_resource_block_8
  jmp std.resource.create_fs_resource_block_10
std.resource.create_fs_resource_block_8:
  jmp std.resource.create_fs_resource_block_8
  movq $0, rcx
  call lm_error_new
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp std.resource.create_fs_resource_epilogue
std.resource.create_fs_resource_block_10:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq $r2, rdx
  movq $0, r8
  call std.resource.Resource.init
  movq [rbp + -88], rax
  jmp std.resource.create_fs_resource_epilogue
std.resource.create_fs_resource_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.create_fs_resource:

.globl std.resource._call
std.resource._call:
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
std.resource._call_entry:
std.resource._call_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.internal.runtime.call
  movq $r3, rax
  jmp std.resource._call_epilogue
std.resource._call_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource._call:

.globl std.uuid.uuid.parse
std.uuid.uuid.parse:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 312
  mov [rbp + -64], rcx
std.uuid.uuid.parse_entry:
std.uuid.uuid.parse_block_0:
  movq [rbp + -64], rcx
  call std.uuid.uuid.trim
  movq $r1, rcx
  call std.uuid.uuid.to_lower
  movq $r2, rcx
  call lm_list_len
  movq $r6, rax
  cmpq $305, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_8
  jmp std.uuid.uuid.parse_block_15
std.uuid.uuid.parse_block_8:
  jmp std.uuid.uuid.parse_block_8
  movq $r2, rcx
  movq $1, rdx
  movq $9, r8
  call substring
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq $r11, rax
  cmpq [rbp + -80], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  jmp std.uuid.uuid.parse_block_15
std.uuid.uuid.parse_block_15:
  movq [rbp + -88], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_17
  jmp std.uuid.uuid.parse_block_24
std.uuid.uuid.parse_block_17:
  jmp std.uuid.uuid.parse_block_17
  movq $r2, rcx
  movq $297, rdx
  movq $305, r8
  call substring
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r16, rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  jmp std.uuid.uuid.parse_block_24
std.uuid.uuid.parse_block_24:
  movq [rbp + -104], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_25
  jmp std.uuid.uuid.parse_block_30
std.uuid.uuid.parse_block_25:
  jmp std.uuid.uuid.parse_block_25
  movq $r2, rcx
  movq $9, rdx
  movq $297, r8
  call substring
  jmp std.uuid.uuid.parse_block_30
std.uuid.uuid.parse_block_30:
  movq $r22, rcx
  call lm_list_len
  movq $r23, rax
  cmpq $289, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_34
  jmp std.uuid.uuid.parse_block_40
std.uuid.uuid.parse_block_34:
  jmp std.uuid.uuid.parse_block_34
  movq $0, rcx
  call lm_list_new
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -120], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -120], rcx
  movq $r27, rdx
  movq $10, r8
  call std.uuid.uuid.UUID.init
  movq [rbp + -120], rax
  jmp std.uuid.uuid.parse_epilogue
std.uuid.uuid.parse_block_40:
  movq $r22, rcx
  movq $65, rdx
  movq $73, r8
  call substring
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq $r37, rax
  cmpq [rbp + -128], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_54
  jmp std.uuid.uuid.parse_block_47
std.uuid.uuid.parse_block_47:
  jmp std.uuid.uuid.parse_block_47
  movq $r22, rcx
  movq $105, rdx
  movq $113, r8
  call substring
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq $r42, rax
  cmpq [rbp + -144], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -152]
  jmp std.uuid.uuid.parse_block_54
std.uuid.uuid.parse_block_54:
  movq [rbp + -152], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_63
  jmp std.uuid.uuid.parse_block_56
std.uuid.uuid.parse_block_56:
  jmp std.uuid.uuid.parse_block_56
  movq $r22, rcx
  movq $145, rdx
  movq $153, r8
  call substring
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq $r47, rax
  cmpq [rbp + -160], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -168]
  jmp std.uuid.uuid.parse_block_63
std.uuid.uuid.parse_block_63:
  movq [rbp + -168], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_72
  jmp std.uuid.uuid.parse_block_65
std.uuid.uuid.parse_block_65:
  jmp std.uuid.uuid.parse_block_65
  movq $r22, rcx
  movq $185, rdx
  movq $193, r8
  call substring
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq $r52, rax
  cmpq [rbp + -176], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -184]
  jmp std.uuid.uuid.parse_block_72
std.uuid.uuid.parse_block_72:
  movq [rbp + -184], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_73
  jmp std.uuid.uuid.parse_block_79
std.uuid.uuid.parse_block_73:
  jmp std.uuid.uuid.parse_block_73
  movq $0, rcx
  call lm_list_new
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -192], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -192], rcx
  movq $r56, rdx
  movq $10, r8
  call std.uuid.uuid.UUID.init
  movq [rbp + -192], rax
  jmp std.uuid.uuid.parse_epilogue
std.uuid.uuid.parse_block_79:
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  jmp std.uuid.uuid.parse_block_85
std.uuid.uuid.parse_block_85:
  movq $1, rax
  cmpq $289, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_88
  jmp std.uuid.uuid.parse_block_158
std.uuid.uuid.parse_block_88:
  jmp std.uuid.uuid.parse_block_88
  movq $1, rax
  cmpq $65, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_96
  jmp std.uuid.uuid.parse_block_92
std.uuid.uuid.parse_block_92:
  jmp std.uuid.uuid.parse_block_92
  movq $1, rax
  cmpq $105, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  jmp std.uuid.uuid.parse_block_96
std.uuid.uuid.parse_block_96:
  movq [rbp + -224], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_102
  jmp std.uuid.uuid.parse_block_98
std.uuid.uuid.parse_block_98:
  jmp std.uuid.uuid.parse_block_98
  movq $1, rax
  cmpq $145, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  jmp std.uuid.uuid.parse_block_102
std.uuid.uuid.parse_block_102:
  movq [rbp + -232], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_108
  jmp std.uuid.uuid.parse_block_104
std.uuid.uuid.parse_block_104:
  jmp std.uuid.uuid.parse_block_104
  movq $1, rax
  cmpq $185, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  jmp std.uuid.uuid.parse_block_108
std.uuid.uuid.parse_block_108:
  movq [rbp + -240], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_109
  jmp std.uuid.uuid.parse_block_114
std.uuid.uuid.parse_block_109:
  jmp std.uuid.uuid.parse_block_109
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -248]
  jmp std.uuid.uuid.parse_block_157
std.uuid.uuid.parse_block_114:
  movq [rbp + -248], rax
  addq $9, rax
  movq rax, [rbp + -256]
  movq $r22, rcx
  movq [rbp + -248], rdx
  movq [rbp + -256], r8
  call substring
  movq [rbp + -248], rax
  addq $9, rax
  movq rax, [rbp + -264]
  movq [rbp + -248], rax
  addq $17, rax
  movq rax, [rbp + -272]
  movq $r22, rcx
  movq [rbp + -264], rdx
  movq [rbp + -272], r8
  call substring
  movq [rbp + -200], rcx
  movq $r87, rdx
  call std.uuid.uuid.index_of
  movq [rbp + -200], rcx
  movq $r95, rdx
  call std.uuid.uuid.index_of
  movq $9, rax
  negq rax
  movq rax, [rbp + -280]
  movq $r97, rax
  cmpq [rbp + -280], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -288]
  movq [rbp + -288], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_141
  jmp std.uuid.uuid.parse_block_136
std.uuid.uuid.parse_block_136:
  jmp std.uuid.uuid.parse_block_136
  movq $9, rax
  negq rax
  movq rax, [rbp + -296]
  movq $r99, rax
  cmpq [rbp + -296], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -304]
  jmp std.uuid.uuid.parse_block_141
std.uuid.uuid.parse_block_141:
  movq [rbp + -304], rax
  testq rax, rax
  jne std.uuid.uuid.parse_block_142
  jmp std.uuid.uuid.parse_block_148
std.uuid.uuid.parse_block_142:
  jmp std.uuid.uuid.parse_block_142
  movq $0, rcx
  call lm_list_new
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -312], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -312], rcx
  movq $r109, rdx
  movq $10, r8
  call std.uuid.uuid.UUID.init
  movq [rbp + -312], rax
  jmp std.uuid.uuid.parse_epilogue
std.uuid.uuid.parse_block_148:
  movq $r97, rax
  movq $33, rcx
  shlq %cl, rax
  movq rax, $r115
  movq $r115, rax
  orq $r99, rax
  movq rax, $r116
  movq $r61, rcx
  movq $r116, rdx
  call lm_list_append
  movq [rbp + -248], rax
  addq $17, rax
  movq rax, [rbp + -320]
  jmp std.uuid.uuid.parse_block_157
std.uuid.uuid.parse_block_157:
  jmp std.uuid.uuid.parse_block_85
std.uuid.uuid.parse_block_158:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -328], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -328], rcx
  movq $r61, rdx
  movq $18, r8
  call std.uuid.uuid.UUID.init
  movq [rbp + -328], rax
  jmp std.uuid.uuid.parse_epilogue
std.uuid.uuid.parse_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.uuid.uuid.parse:

.globl std.resource.__init__
std.resource.__init__:
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
std.resource.__init___entry:
  movq $0, rax
  jmp std.resource.__init___epilogue
std.resource.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.resource.__init__:

.globl std.random.random.Random.next_int
std.random.random.Random.next_int:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.random.random.Random.next_int_entry:
  movq $0, rax
  jmp std.random.random.Random.next_int_epilogue
std.random.random.Random.next_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.Random.next_int:

.globl std.random.random.Random.range_float
std.random.random.Random.range_float:
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
std.random.random.Random.range_float_entry:
  movq $0, rax
  jmp std.random.random.Random.range_float_epilogue
std.random.random.Random.range_float_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.Random.range_float:

.globl std.random.random.Random.next_float
std.random.random.Random.next_float:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.random.random.Random.next_float_entry:
  movq $0, rax
  jmp std.random.random.Random.next_float_epilogue
std.random.random.Random.next_float_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.Random.next_float:

.globl std.random.random.Random.next_string
std.random.random.Random.next_string:
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
std.random.random.Random.next_string_entry:
  movq $0, rax
  jmp std.random.random.Random.next_string_epilogue
std.random.random.Random.next_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.Random.next_string:

.globl std.random.random.Random.init
std.random.random.Random.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.random.random.Random.init_entry:
  movq $0, rax
  jmp std.random.random.Random.init_epilogue
std.random.random.Random.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.random.random.Random.init:

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

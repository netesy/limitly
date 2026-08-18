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
  .string "=== Path Tests ==="
.align 8
str_const_1:
  .string "hello"
.align 8
str_const_2:
  .string "str_len hello"
.align 8
str_const_3:
  .string ""
.align 8
str_const_4:
  .string "str_len empty"
.align 8
str_const_5:
  .string "abcdefghijklmnopqrstuvwxyz"
.align 8
str_const_6:
  .string "str_len alphabet"
.align 8
str_const_7:
  .string "/usr"
.align 8
str_const_8:
  .string "/"
.align 8
str_const_9:
  .string "starts_with slash"
.align 8
str_const_10:
  .string "hello"
.align 8
str_const_11:
  .string "hel"
.align 8
str_const_12:
  .string "starts_with prefix"
.align 8
str_const_13:
  .string "hello"
.align 8
str_const_14:
  .string "world"
.align 8
str_const_15:
  .string "starts_with no match"
.align 8
str_const_16:
  .string "file.txt"
.align 8
str_const_17:
  .string ".txt"
.align 8
str_const_18:
  .string "ends_with extension"
.align 8
str_const_19:
  .string "file.txt"
.align 8
str_const_20:
  .string ".md"
.align 8
str_const_21:
  .string "ends_with no match"
.align 8
str_const_22:
  .string "a"
.align 8
str_const_23:
  .string "a"
.align 8
str_const_24:
  .string "char_eq a"
.align 8
str_const_25:
  .string "A"
.align 8
str_const_26:
  .string "A"
.align 8
str_const_27:
  .string "char_eq A"
.align 8
str_const_28:
  .string "a"
.align 8
str_const_29:
  .string "b"
.align 8
str_const_30:
  .string "char_eq diff"
.align 8
str_const_31:
  .string "abc"
.align 8
str_const_32:
  .string "abd"
.align 8
str_const_33:
  .string "char_eq multi char"
.align 8
str_const_34:
  .string "bin"
.align 8
str_const_35:
  .string "basename hello"
.align 8
str_const_36:
  .string "parent wrapper"
.align 8
str_const_37:
  .string "is_absolute wrapper"
.align 8
str_const_38:
  .string "join conditions"
.align 8
str_const_39:
  .string "Path tests passed!"
.align 8
str_const_40:
  .string "/a/"
.align 8
str_const_41:
  .string "/"
.align 8
str_const_42:
  .string "/a/"
.align 8
str_const_43:
  .string "/"
.align 8
str_const_44:
  .string "join cond 1"
.align 8
str_const_45:
  .string ""
.align 8
str_const_46:
  .string ""
.align 8
str_const_47:
  .string "join cond 2"
.align 8
str_const_48:
  .string "/a"
.align 8
str_const_49:
  .string "/"
.align 8
str_const_50:
  .string "join cond 3"
.align 8
str_const_51:
  .string "a"
.align 8
str_const_52:
  .string ""
.align 8
str_const_53:
  .string "b"
.align 8
str_const_54:
  .string ""
.align 8
str_const_55:
  .string "join cond 4"
.align 8
str_const_56:
  .string "/usr/local/bin"
.align 8
str_const_57:
  .string "bn0 len"
.align 8
str_const_58:
  .string ""
.align 8
str_const_59:
  .string "/"
.align 8
str_const_60:
  .string ""
.align 8
str_const_61:
  .string "file"
.align 8
str_const_62:
  .string "stem hello"
.align 8
str_const_63:
  .string "noext"
.align 8
str_const_64:
  .string "stem no ext"
.align 8
str_const_65:
  .string "/a/b/c"
.align 8
str_const_66:
  .string "/a/b"
.align 8
str_const_67:
  .string "parent"
.align 8
str_const_68:
  .string "file.txt"
.align 8
str_const_69:
  .string ""
.align 8
str_const_70:
  .string "parent file"
.align 8
str_const_71:
  .string "/"
.align 8
str_const_72:
  .string ""
.align 8
str_const_73:
  .string "parent root"
.align 8
str_const_74:
  .string ""
.align 8
str_const_75:
  .string ""
.align 8
str_const_76:
  .string "basename empty"
.align 8
str_const_77:
  .string "/"
.align 8
str_const_78:
  .string "/"
.align 8
str_const_79:
  .string "basename slash"
.align 8
str_const_80:
  .string "noext.txt"
.align 8
str_const_81:
  .string "noext.txt"
.align 8
str_const_82:
  .string "basename noext"
.align 8
str_const_83:
  .string "/abs/path"
.align 8
str_const_84:
  .string "abs"
.align 8
str_const_85:
  .string "/"
.align 8
str_const_86:
  .string "root"
.align 8
str_const_87:
  .string "relative"
.align 8
str_const_88:
  .string "relative"
.align 8
str_const_89:
  .string "a/b/c"
.align 8
str_const_90:
  .string "a/b/c"
.align 8
str_const_91:
  .string "file.txt"
.align 8
str_const_92:
  .string "ext hello"
.align 8
str_const_93:
  .string "file.txt"
.align 8
str_const_94:
  .string "ext no ext"
.align 8
str_const_95:
  .string "noext"
.align 8
str_const_96:
  .string "ext no ext"
.align 8
str_const_97:
  .string ""
.align 8
str_const_98:
  .string "/"
.align 8
str_const_99:
  .string ""
.align 8
str_const_100:
  .string "/"
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
  sub rsp, 472
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
  movq [rbp + -96], rcx
  call str_len
  movq $r3, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  call str_len
  movq $r9, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  call str_len
  movq $r15, rax
  cmpq $209, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call starts_with
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq $r22, rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call starts_with
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq $r27, rcx
  movq [rbp + -208], rdx
  call lm_assert
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -216], rcx
  movq [rbp + -224], rdx
  call starts_with
  movq $r32, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -232]
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rcx
  movq [rbp + -240], rdx
  call lm_assert
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -248], rcx
  movq [rbp + -256], rdx
  call ends_with
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq $r39, rcx
  movq [rbp + -264], rdx
  call lm_assert
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -272], rcx
  movq [rbp + -280], rdx
  call ends_with
  movq $r44, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -288]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -288], rcx
  movq [rbp + -296], rdx
  call lm_assert
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -304], rcx
  movq [rbp + -312], rdx
  call char_eq
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq $r51, rcx
  movq [rbp + -320], rdx
  call lm_assert
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -328], rcx
  movq [rbp + -336], rdx
  call char_eq
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq $r56, rcx
  movq [rbp + -344], rdx
  call lm_assert
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -352], rcx
  movq [rbp + -360], rdx
  call char_eq
  movq $r61, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -368]
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -368], rcx
  movq [rbp + -376], rdx
  call lm_assert
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq [rbp + -384], rcx
  movq [rbp + -392], rdx
  call char_eq
  movq $r68, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -400]
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -400], rcx
  movq [rbp + -408], rdx
  call lm_assert
  call test_basename_hello
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq $r73, rax
  cmpq [rbp + -416], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -424]
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rbp + -424], rcx
  movq [rbp + -432], rdx
  call lm_assert
  call test_parent_wrapper
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq $r78, rcx
  movq [rbp + -440], rdx
  call lm_assert
  call test_is_absolute_wrapper
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq $r81, rcx
  movq [rbp + -448], rdx
  call lm_assert
  call test_join_conditions
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq $r84, rcx
  movq [rbp + -456], rdx
  call lm_assert
  movq [rel str_const_39], rcx
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

.globl test_join_conditions
test_join_conditions:
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
test_join_conditions_entry:
test_join_conditions_block_0:
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call starts_with
  movq $r3, rax
  testq rax, rax
  jne test_join_conditions_block_5
  jmp test_join_conditions_block_10
test_join_conditions_block_5:
  jmp test_join_conditions_block_5
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -80], rcx
  movq [rbp + -88], rdx
  call ends_with
  jmp test_join_conditions_block_10
test_join_conditions_block_10:
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r6, rcx
  movq [rbp + -96], rdx
  call lm_assert
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call starts_with
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq $r18, rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rax
  cmpq [rbp + -168], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne test_join_conditions_block_30
  jmp test_join_conditions_block_35
test_join_conditions_block_30:
  jmp test_join_conditions_block_30
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -184], rax
  cmpq [rbp + -192], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -200]
  jmp test_join_conditions_block_35
test_join_conditions_block_35:
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -200], rcx
  movq [rbp + -208], rdx
  call lm_assert
  movq $18, rax
  jmp test_join_conditions_epilogue
test_join_conditions_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_join_conditions:

.globl test_basename_hello
test_basename_hello:
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
test_basename_hello_entry:
test_basename_hello_block_0:
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rcx
  call str_len
  movq $r1, rax
  cmpq $113, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rcx
  movq [rbp + -80], rdx
  call lm_assert
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $r1, rax
  subq $9, rax
  movq rax, $r9
  jmp test_basename_hello_block_12
test_basename_hello_block_12:
  movq $r9, rax
  cmpq $1, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne test_basename_hello_block_15
  jmp test_basename_hello_block_25
test_basename_hello_block_15:
  jmp test_basename_hello_block_15
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $0, rax
  cmpq [rbp + -104], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne test_basename_hello_block_20
  jmp test_basename_hello_block_21
test_basename_hello_block_20:
  jmp test_basename_hello_block_20
  jmp test_basename_hello_block_25
test_basename_hello_block_21:
  movq $r9, rax
  subq $9, rax
  movq rax, $r20
  jmp test_basename_hello_block_12
test_basename_hello_block_25:
  movq $r20, rax
  addq $9, rax
  movq rax, $r23
  jmp test_basename_hello_block_30
test_basename_hello_block_30:
  movq $r23, rax
  cmpq $r1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne test_basename_hello_block_32
  jmp test_basename_hello_block_40
test_basename_hello_block_32:
  jmp test_basename_hello_block_32
  movq [rbp + -88], rcx
  movq $0, rdx
  call lm_str_concat
  movq rax, [rbp + -128]
  movq $r23, rax
  addq $9, rax
  movq rax, $r31
  jmp test_basename_hello_block_30
test_basename_hello_block_40:
  movq [rbp + -128], rax
  jmp test_basename_hello_epilogue
test_basename_hello_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_basename_hello:

.globl str_len
str_len:
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
str_len_entry:
str_len_block_0:
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne str_len_block_3
  jmp str_len_block_5
str_len_block_3:
  jmp str_len_block_3
  movq $1, rax
  jmp str_len_epilogue
str_len_block_5:
  jmp str_len_block_8
str_len_block_8:
  movq $1, rax
  cmpq $80001, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne str_len_block_11
  jmp str_len_block_26
str_len_block_11:
  jmp str_len_block_11
  movq $0, rax
  cmpq $2, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne str_len_block_16
  jmp str_len_block_17
str_len_block_16:
  jmp str_len_block_16
  movq $1, rax
  jmp str_len_epilogue
str_len_block_17:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp str_len_block_8
str_len_block_26:
  movq [rbp + -104], rax
  jmp str_len_epilogue
str_len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_str_len:

.globl char_eq
char_eq:
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
char_eq_entry:
char_eq_block_0:
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  jmp char_eq_epilogue
char_eq_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_char_eq:

.globl str_eq
str_eq:
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
str_eq_entry:
str_eq_block_0:
  movq [rbp + -64], rcx
  call str_len
  movq [rbp + -72], rcx
  call str_len
  movq $r2, rax
  cmpq $r4, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne str_eq_block_6
  jmp str_eq_block_8
str_eq_block_6:
  jmp str_eq_block_6
  movq $10, rax
  jmp str_eq_epilogue
str_eq_block_8:
  jmp str_eq_block_10
str_eq_block_10:
  movq $1, rax
  cmpq $r2, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne str_eq_block_12
  jmp str_eq_block_23
str_eq_block_12:
  jmp str_eq_block_12
  movq $0, rax
  cmpq $0, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne str_eq_block_16
  jmp str_eq_block_18
str_eq_block_16:
  jmp str_eq_block_16
  movq $10, rax
  jmp str_eq_epilogue
str_eq_block_18:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp str_eq_block_10
str_eq_block_23:
  movq $18, rax
  jmp str_eq_epilogue
str_eq_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_str_eq:

.globl starts_with
starts_with:
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
starts_with_entry:
starts_with_block_0:
  movq [rbp + -72], rcx
  call str_len
  movq [rbp + -64], rcx
  call str_len
  movq $r2, rax
  cmpq $r4, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne starts_with_block_6
  jmp starts_with_block_8
starts_with_block_6:
  jmp starts_with_block_6
  movq $10, rax
  jmp starts_with_epilogue
starts_with_block_8:
  jmp starts_with_block_10
starts_with_block_10:
  movq $1, rax
  cmpq $r2, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne starts_with_block_12
  jmp starts_with_block_23
starts_with_block_12:
  jmp starts_with_block_12
  movq $0, rax
  cmpq $0, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne starts_with_block_16
  jmp starts_with_block_18
starts_with_block_16:
  jmp starts_with_block_16
  movq $10, rax
  jmp starts_with_epilogue
starts_with_block_18:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp starts_with_block_10
starts_with_block_23:
  movq $18, rax
  jmp starts_with_epilogue
starts_with_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_starts_with:

.globl test_stem
test_stem:
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
test_stem_entry:
test_stem_block_0:
  call test_basename_hello
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq $r0, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rcx
  movq [rbp + -80], rdx
  call lm_assert
  call test_basename_empty
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $r5, rax
  cmpq [rbp + -88], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  movq $0, rax
  jmp test_stem_epilogue
test_stem_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_stem:

.globl ends_with
ends_with:
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
ends_with_entry:
ends_with_block_0:
  movq [rbp + -64], rcx
  call str_len
  movq [rbp + -72], rcx
  call str_len
  movq $r4, rax
  cmpq $r2, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne ends_with_block_6
  jmp ends_with_block_8
ends_with_block_6:
  jmp ends_with_block_6
  movq $10, rax
  jmp ends_with_epilogue
ends_with_block_8:
  jmp ends_with_block_10
ends_with_block_10:
  movq $1, rax
  cmpq $r4, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne ends_with_block_12
  jmp ends_with_block_26
ends_with_block_12:
  jmp ends_with_block_12
  movq $r2, rax
  subq $r4, rax
  movq rax, $r12
  movq $r2, rax
  subq $r4, rax
  movq rax, $r13
  movq $r13, rax
  addq $1, rax
  movq rax, $r14
  movq $0, rax
  cmpq $0, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne ends_with_block_19
  jmp ends_with_block_21
ends_with_block_19:
  jmp ends_with_block_19
  movq $10, rax
  jmp ends_with_epilogue
ends_with_block_21:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp ends_with_block_10
ends_with_block_26:
  movq $18, rax
  jmp ends_with_epilogue
ends_with_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_ends_with:

.globl test_parent_wrapper
test_parent_wrapper:
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
test_parent_wrapper_entry:
test_parent_wrapper_block_0:
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rcx
  call test_parent
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $r1, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -80], rcx
  movq [rbp + -88], rdx
  call lm_assert
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call test_parent
  movq [rel str_const_69], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r7, rax
  cmpq [rbp + -104], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_70], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq [rel str_const_71], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  call test_parent
  movq [rel str_const_72], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r13, rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_73], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $18, rax
  jmp test_parent_wrapper_epilogue
test_parent_wrapper_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_parent_wrapper:

.globl test_basename_empty
test_basename_empty:
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
test_basename_empty_entry:
test_basename_empty_block_0:
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rel str_const_75], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -80], rcx
  movq [rbp + -88], rdx
  call lm_assert
  movq [rel str_const_77], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rel str_const_78], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rax
  cmpq [rbp + -104], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_79], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq [rel str_const_80], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rel str_const_81], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_82], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq $0, rax
  jmp test_basename_empty_epilogue
test_basename_empty_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_basename_empty:

.globl test_is_absolute_wrapper
test_is_absolute_wrapper:
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
test_is_absolute_wrapper_entry:
test_is_absolute_wrapper_block_0:
  movq [rel str_const_83], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rcx
  call test_is_absolute
  movq [rel str_const_84], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $r1, rcx
  movq [rbp + -72], rdx
  call lm_assert
  movq [rel str_const_85], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -80], rcx
  call test_is_absolute
  movq [rel str_const_86], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $r5, rcx
  movq [rbp + -88], rdx
  call lm_assert
  movq [rel str_const_87], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call test_is_absolute
  movq $r9, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_88], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq [rel str_const_89], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -120], rcx
  call test_is_absolute
  movq $r15, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_90], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq $18, rax
  jmp test_is_absolute_wrapper_epilogue
test_is_absolute_wrapper_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_is_absolute_wrapper:

.globl test_extension
test_extension:
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
test_extension_entry:
test_extension_block_0:
  call test_basename_hello
  movq [rel str_const_91], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq $r0, rax
  cmpq [rbp + -64], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rel str_const_92], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rcx
  movq [rbp + -80], rdx
  call lm_assert
  call test_basename_hello
  movq [rel str_const_93], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $r5, rax
  cmpq [rbp + -88], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_94], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_basename_empty
  movq [rel str_const_95], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r10, rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_96], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq $0, rax
  jmp test_extension_epilogue
test_extension_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_extension:

.globl test_parent
test_parent:
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
test_parent_entry:
test_parent_block_0:
  movq [rbp + -64], rcx
  call str_len
  movq [rel str_const_97], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $r1, rax
  subq $9, rax
  movq rax, $r5
  jmp test_parent_block_7
test_parent_block_7:
  movq $r5, rax
  cmpq $1, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne test_parent_block_10
  jmp test_parent_block_20
test_parent_block_10:
  jmp test_parent_block_10
  movq [rel str_const_98], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $0, rax
  cmpq [rbp + -88], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne test_parent_block_15
  jmp test_parent_block_16
test_parent_block_15:
  jmp test_parent_block_15
  jmp test_parent_block_20
test_parent_block_16:
  movq $r5, rax
  subq $9, rax
  movq rax, $r16
  jmp test_parent_block_7
test_parent_block_20:
  movq $r16, rax
  cmpq $1, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne test_parent_block_23
  jmp test_parent_block_25
test_parent_block_23:
  jmp test_parent_block_23
  movq [rel str_const_99], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp test_parent_epilogue
test_parent_block_25:
  jmp test_parent_block_27
test_parent_block_27:
  movq $1, rax
  cmpq $r16, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne test_parent_block_29
  jmp test_parent_block_37
test_parent_block_29:
  jmp test_parent_block_29
  movq [rbp + -72], rcx
  movq $0, rdx
  call lm_str_concat
  movq rax, [rbp + -128]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -136]
  jmp test_parent_block_27
test_parent_block_37:
  movq [rbp + -128], rax
  jmp test_parent_epilogue
test_parent_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_parent:

.globl test_is_absolute
test_is_absolute:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
test_is_absolute_entry:
test_is_absolute_block_0:
  movq [rel str_const_100], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call starts_with
  movq $r2, rax
  jmp test_is_absolute_epilogue
test_is_absolute_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_is_absolute:

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

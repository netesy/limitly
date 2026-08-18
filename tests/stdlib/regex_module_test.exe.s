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
  .string "ERR"
.align 8
str_const_1:
  .string "=== Regex Module Test Suite ==="
.align 8
str_const_2:
  .string "Regex frame test failed"
.align 8
str_const_3:
  .string "Regex patterns test failed"
.align 8
str_const_4:
  .string "Regex helpers test failed"
.align 8
str_const_5:
  .string "All regex tests passed successfully."
.align 8
str_const_6:
  .string "ERR"
.align 8
str_const_7:
  .string ""
.align 8
str_const_8:
  .string "Testing Regex Helpers..."
.align 8
str_const_9:
  .string "cat"
.align 8
str_const_10:
  .string "the cat sat"
.align 8
str_const_11:
  .string "is_match helper failed"
.align 8
str_const_12:
  .string "cat"
.align 8
str_const_13:
  .string "the cat sat"
.align 8
str_const_14:
  .string "dog"
.align 8
str_const_15:
  .string "the dog sat"
.align 8
str_const_16:
  .string "replace helper failed"
.align 8
str_const_17:
  .string "Testing Regex Patterns..."
.align 8
str_const_18:
  .string "[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}"
.align 8
str_const_19:
  .string "email pattern failed"
.align 8
str_const_20:
  .string ""
.align 8
str_const_21:
  .string ""
.align 8
str_const_22:
  .string "Testing Regex Frame..."
.align 8
str_const_23:
  .string "cat"
.align 8
str_const_24:
  .string "the cat sat"
.align 8
str_const_25:
  .string "matches true failed"
.align 8
str_const_26:
  .string "the dog sat"
.align 8
str_const_27:
  .string "matches false failed"
.align 8
str_const_28:
  .string "the cat sat"
.align 8
str_const_29:
  .string "cat"
.align 8
str_const_30:
  .string "find_first_match failed"
.align 8
str_const_31:
  .string "cat cat dog cat"
.align 8
str_const_32:
  .string "find_all_matches length failed"
.align 8
str_const_33:
  .string "cat"
.align 8
str_const_34:
  .string "find_all_matches 0 failed"
.align 8
str_const_35:
  .string "the cat sat"
.align 8
str_const_36:
  .string "dog"
.align 8
str_const_37:
  .string "the dog sat"
.align 8
str_const_38:
  .string "replace failed"
.align 8
str_const_39:
  .string "cat cat dog"
.align 8
str_const_40:
  .string "bird"
.align 8
str_const_41:
  .string "bird bird dog"
.align 8
str_const_42:
  .string "replace_all failed"
.align 8
str_const_43:
  .string "the cat sat"
.align 8
str_const_44:
  .string "split length failed"
.align 8
str_const_45:
  .string "the "
.align 8
str_const_46:
  .string "split 0 failed"
.align 8
str_const_47:
  .string " sat"
.align 8
str_const_48:
  .string "split 1 failed"
.align 8
str_const_49:
  .string "is_valid failed"
.align 8
str_const_50:
  .string "/cat/"
.align 8
str_const_51:
  .string "to_string failed"
.align 8
str_const_52:
  .string "ERR"
.align 8
str_const_53:
  .string "ERR"
.align 8
str_const_54:
  .string ""
.align 8
str_const_55:
  .string ""
.align 8
str_const_56:
  .string ""
.align 8
str_const_57:
  .string ""
.align 8
str_const_58:
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
  call std.regex.index.__init__
  call std.regex.regex.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq [rel str_const_1], rcx
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
  call test_regex_frame
  movq $r2, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_regex_patterns
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  call test_regex_helpers
  movq $r12, rax
  cmpq $9, rax
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

.globl std.regex.regex.RegexPatterns.phone
std.regex.regex.RegexPatterns.phone:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.regex.regex.RegexPatterns.phone_entry:
  movq $0, rax
  jmp std.regex.regex.RegexPatterns.phone_epilogue
std.regex.regex.RegexPatterns.phone_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.RegexPatterns.phone:

.globl std.regex.regex.RegexPatterns.url
std.regex.regex.RegexPatterns.url:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.regex.regex.RegexPatterns.url_entry:
  movq $0, rax
  jmp std.regex.regex.RegexPatterns.url_epilogue
std.regex.regex.RegexPatterns.url_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.RegexPatterns.url:

.globl std.regex.regex.Regex.init
std.regex.regex.Regex.init:
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
std.regex.regex.Regex.init_entry:
  movq $0, rax
  jmp std.regex.regex.Regex.init_epilogue
std.regex.regex.Regex.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.Regex.init:

.globl std.regex.regex.Regex.to_string
std.regex.regex.Regex.to_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.regex.regex.Regex.to_string_entry:
  movq $0, rax
  jmp std.regex.regex.Regex.to_string_epilogue
std.regex.regex.Regex.to_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.Regex.to_string:

.globl std.regex.regex.Regex.replace_all
std.regex.regex.Regex.replace_all:
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
std.regex.regex.Regex.replace_all_entry:
  movq $0, rax
  jmp std.regex.regex.Regex.replace_all_epilogue
std.regex.regex.Regex.replace_all_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.Regex.replace_all:

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

.globl std.regex.regex.Regex.find_match_start
std.regex.regex.Regex.find_match_start:
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
std.regex.regex.Regex.find_match_start_entry:
  movq $0, rax
  jmp std.regex.regex.Regex.find_match_start_epilogue
std.regex.regex.Regex.find_match_start_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.Regex.find_match_start:

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

.globl std.regex.regex.Regex.is_valid
std.regex.regex.Regex.is_valid:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.regex.regex.Regex.is_valid_entry:
  movq $0, rax
  jmp std.regex.regex.Regex.is_valid_epilogue
std.regex.regex.Regex.is_valid_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.Regex.is_valid:

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
  movq [rel str_const_0], rcx
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

.globl std.regex.regex.Regex.is_balanced_pattern
std.regex.regex.Regex.is_balanced_pattern:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.regex.regex.Regex.is_balanced_pattern_entry:
  movq $0, rax
  jmp std.regex.regex.Regex.is_balanced_pattern_epilogue
std.regex.regex.Regex.is_balanced_pattern_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.Regex.is_balanced_pattern:

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
  movq [rel str_const_7], rcx
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

.globl test_regex_helpers
test_regex_helpers:
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
test_regex_helpers_entry:
test_regex_helpers_block_0:
  movq [rel str_const_8], rcx
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
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call std.regex.index.is_match
  movq $r4, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  movq [rbp + -144], r8
  call std.regex.index.replace
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq $r12, rax
  cmpq [rbp + -152], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq $9, rax
  jmp test_regex_helpers_epilogue
test_regex_helpers_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_regex_helpers:

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

.globl test_regex_patterns
test_regex_patterns:
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
test_regex_patterns_entry:
test_regex_patterns_block_0:
  movq [rel str_const_17], rcx
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
  call std.regex.index.RegexPatterns
  movq $r2, rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.regex.regex.RegexPatterns.email
  movq $r5, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -104]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq $9, rax
  jmp test_regex_patterns_epilogue
test_regex_patterns_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_regex_patterns:

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

.globl std.regex.regex.RegexPatterns.email
std.regex.regex.RegexPatterns.email:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.regex.regex.RegexPatterns.email_entry:
  movq $0, rax
  jmp std.regex.regex.RegexPatterns.email_epilogue
std.regex.regex.RegexPatterns.email_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.RegexPatterns.email:

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

.globl std.regex.regex.__init__
std.regex.regex.__init__:
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
std.regex.regex.__init___entry:
  movq $0, rax
  jmp std.regex.regex.__init___epilogue
std.regex.regex.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.__init__:

.globl std.regex.regex.Regex.simple_match
std.regex.regex.Regex.simple_match:
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
std.regex.regex.Regex.simple_match_entry:
  movq $0, rax
  jmp std.regex.regex.Regex.simple_match_epilogue
std.regex.regex.Regex.simple_match_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.Regex.simple_match:

.globl std.regex.index.Regex
std.regex.index.Regex:
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
std.regex.index.Regex_entry:
std.regex.index.Regex_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.regex.regex.Regex.init
  movq [rbp + -80], rax
  jmp std.regex.index.Regex_epilogue
std.regex.index.Regex_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.index.Regex:

.globl std.regex.regex.RegexPatterns.init
std.regex.regex.RegexPatterns.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.regex.regex.RegexPatterns.init_entry:
  movq $0, rax
  jmp std.regex.regex.RegexPatterns.init_epilogue
std.regex.regex.RegexPatterns.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.RegexPatterns.init:

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
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_21], rcx
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

.globl test_regex_frame
test_regex_frame:
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
test_regex_frame_entry:
test_regex_frame_block_0:
  movq [rel str_const_22], rcx
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
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  movq $1, rdx
  call std.regex.index.Regex
  movq $r4, rax
  movq rax, [rbp + -104]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call std.regex.regex.Regex.matches
  movq $r8, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -104], rcx
  movq [rbp + -136], rdx
  call std.regex.regex.Regex.matches
  movq $r14, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -104], rcx
  movq [rbp + -160], rdx
  call std.regex.regex.Regex.find_first_match
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq $r20, rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -104], rcx
  movq [rbp + -192], rdx
  call std.regex.regex.Regex.find_all_matches
  movq $r27, rcx
  call lm_list_len
  movq $r29, rax
  cmpq $25, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -200], rcx
  movq [rbp + -208], rdx
  call lm_assert
  movq $r27, rcx
  movq $1, rdx
  call lm_list_get
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq $r35, rax
  cmpq [rbp + -216], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -104], rcx
  movq [rbp + -240], rdx
  movq [rbp + -248], r8
  call std.regex.regex.Regex.replace
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq $r42, rax
  cmpq [rbp + -256], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -264]
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -264], rcx
  movq [rbp + -272], rdx
  call lm_assert
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -104], rcx
  movq [rbp + -280], rdx
  movq [rbp + -288], r8
  call std.regex.regex.Regex.replace_all
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq $r50, rax
  cmpq [rbp + -296], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -304]
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -304], rcx
  movq [rbp + -312], rdx
  call lm_assert
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -104], rcx
  movq [rbp + -320], rdx
  call std.regex.regex.Regex.split
  movq $r57, rcx
  call lm_list_len
  movq $r59, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -328]
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -328], rcx
  movq [rbp + -336], rdx
  call lm_assert
  movq $r57, rcx
  movq $1, rdx
  call lm_list_get
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq $r65, rax
  cmpq [rbp + -344], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -352]
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -352], rcx
  movq [rbp + -360], rdx
  call lm_assert
  movq $r57, rcx
  movq $9, rdx
  call lm_list_get
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq $r71, rax
  cmpq [rbp + -368], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -376]
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -376], rcx
  movq [rbp + -384], rdx
  call lm_assert
  movq [rbp + -104], rcx
  call std.regex.regex.Regex.is_valid
  movq $r76, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -392], rcx
  movq [rbp + -400], rdx
  call lm_assert
  movq [rbp + -104], rcx
  call std.regex.regex.Regex.to_string
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq $r81, rax
  cmpq [rbp + -408], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -416]
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -416], rcx
  movq [rbp + -424], rdx
  call lm_assert
  movq $9, rax
  jmp test_regex_frame_epilogue
test_regex_frame_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_regex_frame:

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
  movq [rel str_const_52], rcx
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

.globl std.regex.index.is_match
std.regex.index.is_match:
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
std.regex.index.is_match_entry:
std.regex.index.is_match_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq $1, r8
  call std.regex.regex.Regex.init
  movq [rbp + -80], rcx
  movq [rbp + -72], rdx
  call std.regex.regex.Regex.matches
  movq $r6, rax
  jmp std.regex.index.is_match_epilogue
std.regex.index.is_match_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.index.is_match:

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
  movq [rel str_const_53], rcx
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
  movq [rel str_const_54], rcx
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

.globl std.regex.regex.Regex.split
std.regex.regex.Regex.split:
  push rbp
  mov rbp, rsp
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
std.regex.regex.Regex.split_entry:
  movq $0, rax
  jmp std.regex.regex.Regex.split_epilogue
std.regex.regex.Regex.split_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.Regex.split:

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

.globl std.regex.regex.Regex.replace
std.regex.regex.Regex.replace:
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
std.regex.regex.Regex.replace_entry:
  movq $0, rax
  jmp std.regex.regex.Regex.replace_epilogue
std.regex.regex.Regex.replace_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.Regex.replace:

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
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_56], rcx
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
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_58], rcx
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

.globl std.regex.index.replace
std.regex.index.replace:
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
std.regex.index.replace_entry:
std.regex.index.replace_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq [rbp + -64], rdx
  movq $1, r8
  call std.regex.regex.Regex.init
  movq [rbp + -88], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.regex.regex.Regex.replace
  movq $r7, rax
  jmp std.regex.index.replace_epilogue
std.regex.index.replace_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.index.replace:

.globl std.regex.index.RegexPatterns
std.regex.index.RegexPatterns:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.regex.index.RegexPatterns_entry:
std.regex.index.RegexPatterns_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.regex.regex.RegexPatterns.init
  movq $0, rax
  jmp std.regex.index.RegexPatterns_epilogue
std.regex.index.RegexPatterns_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.index.RegexPatterns:

.globl std.regex.index.__init__
std.regex.index.__init__:
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
std.regex.index.__init___entry:
  movq $0, rax
  jmp std.regex.index.__init___epilogue
std.regex.index.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.index.__init__:

.globl std.regex.regex.Regex.matches
std.regex.regex.Regex.matches:
  push rbp
  mov rbp, rsp
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
std.regex.regex.Regex.matches_entry:
  movq $0, rax
  jmp std.regex.regex.Regex.matches_epilogue
std.regex.regex.Regex.matches_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.Regex.matches:

.globl std.regex.regex.Regex.find_first_match
std.regex.regex.Regex.find_first_match:
  push rbp
  mov rbp, rsp
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
std.regex.regex.Regex.find_first_match_entry:
  movq $0, rax
  jmp std.regex.regex.Regex.find_first_match_epilogue
std.regex.regex.Regex.find_first_match_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.Regex.find_first_match:

.globl std.regex.regex.Regex.find_all_matches
std.regex.regex.Regex.find_all_matches:
  push rbp
  mov rbp, rsp
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
std.regex.regex.Regex.find_all_matches_entry:
  movq $0, rax
  jmp std.regex.regex.Regex.find_all_matches_epilogue
std.regex.regex.Regex.find_all_matches_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.regex.regex.Regex.find_all_matches:

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

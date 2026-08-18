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
  .string "=== Net Tests ==="
.align 8
str_const_1:
  .string "127.0.0.1"
.align 8
str_const_2:
  .string "valid ipv4"
.align 8
str_const_3:
  .string "127.0.0.256"
.align 8
str_const_4:
  .string "invalid ipv4"
.align 8
str_const_5:
  .string "::1"
.align 8
str_const_6:
  .string "valid ipv6"
.align 8
str_const_7:
  .string "Net tests passed!"
.align 8
str_const_8:
  .string "a"
.align 8
str_const_9:
  .string "b"
.align 8
str_const_10:
  .string "c"
.align 8
str_const_11:
  .string "d"
.align 8
str_const_12:
  .string "e"
.align 8
str_const_13:
  .string "f"
.align 8
str_const_14:
  .string "A"
.align 8
str_const_15:
  .string "B"
.align 8
str_const_16:
  .string "C"
.align 8
str_const_17:
  .string "D"
.align 8
str_const_18:
  .string "E"
.align 8
str_const_19:
  .string "F"
.align 8
str_const_20:
  .string "0"
.align 8
str_const_21:
  .string "1"
.align 8
str_const_22:
  .string "2"
.align 8
str_const_23:
  .string "3"
.align 8
str_const_24:
  .string "4"
.align 8
str_const_25:
  .string "5"
.align 8
str_const_26:
  .string "6"
.align 8
str_const_27:
  .string "7"
.align 8
str_const_28:
  .string "8"
.align 8
str_const_29:
  .string "9"
.align 8
str_const_30:
  .string ""
.align 8
str_const_31:
  .string ""
.align 8
str_const_32:
  .string ""
.align 8
str_const_33:
  .string ""
.align 8
str_const_34:
  .string "ERR"
.align 8
str_const_35:
  .string ""
.align 8
str_const_36:
  .string "ERR"
.align 8
str_const_37:
  .string ""
.align 8
str_const_38:
  .string ""
.align 8
str_const_39:
  .string ""
.align 8
str_const_40:
  .string "ERR"
.align 8
str_const_41:
  .string ""
.align 8
str_const_42:
  .string ""
.align 8
str_const_43:
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
  sub rsp, 168
main_entry:
main_block_0:
  call std.net.dns.__init__
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
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -96], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call std.net.dns.DNS.is_ipv4
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r6, rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -96], rcx
  movq [rbp + -120], rdx
  call std.net.dns.DNS.is_ipv4
  movq $r10, rax
  cmpq $18, rax
  setne al
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
  movq [rbp + -96], rcx
  movq [rbp + -144], rdx
  call std.net.dns.DNS.is_ipv6
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq $r16, rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rel str_const_7], rcx
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

.globl std.net.dns.__init__
std.net.dns.__init__:
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
std.net.dns.__init___entry:
  movq $0, rax
  jmp std.net.dns.__init___epilogue
std.net.dns.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.net.dns.__init__:

.globl std.net.dns.is_hex_digit
std.net.dns.is_hex_digit:
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
std.net.dns.is_hex_digit_entry:
std.net.dns.is_hex_digit_block_0:
  movq [rbp + -64], rcx
  call std.net.dns.is_digit
  movq $r1, rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.net.dns.is_hex_digit_block_4
  jmp std.net.dns.is_hex_digit_block_6
std.net.dns.is_hex_digit_block_4:
  jmp std.net.dns.is_hex_digit_block_4
  movq $18, rax
  jmp std.net.dns.is_hex_digit_epilogue
std.net.dns.is_hex_digit_block_6:
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -64], rax
  cmpq [rbp + -80], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.net.dns.is_hex_digit_block_14
  jmp std.net.dns.is_hex_digit_block_10
std.net.dns.is_hex_digit_block_10:
  jmp std.net.dns.is_hex_digit_block_10
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -64], rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  jmp std.net.dns.is_hex_digit_block_14
std.net.dns.is_hex_digit_block_14:
  movq [rbp + -104], rax
  testq rax, rax
  jne std.net.dns.is_hex_digit_block_20
  jmp std.net.dns.is_hex_digit_block_16
std.net.dns.is_hex_digit_block_16:
  jmp std.net.dns.is_hex_digit_block_16
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -64], rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  jmp std.net.dns.is_hex_digit_block_20
std.net.dns.is_hex_digit_block_20:
  movq [rbp + -120], rax
  testq rax, rax
  jne std.net.dns.is_hex_digit_block_26
  jmp std.net.dns.is_hex_digit_block_22
std.net.dns.is_hex_digit_block_22:
  jmp std.net.dns.is_hex_digit_block_22
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -64], rax
  cmpq [rbp + -128], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  jmp std.net.dns.is_hex_digit_block_26
std.net.dns.is_hex_digit_block_26:
  movq [rbp + -136], rax
  testq rax, rax
  jne std.net.dns.is_hex_digit_block_32
  jmp std.net.dns.is_hex_digit_block_28
std.net.dns.is_hex_digit_block_28:
  jmp std.net.dns.is_hex_digit_block_28
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -64], rax
  cmpq [rbp + -144], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  jmp std.net.dns.is_hex_digit_block_32
std.net.dns.is_hex_digit_block_32:
  movq [rbp + -152], rax
  testq rax, rax
  jne std.net.dns.is_hex_digit_block_38
  jmp std.net.dns.is_hex_digit_block_34
std.net.dns.is_hex_digit_block_34:
  jmp std.net.dns.is_hex_digit_block_34
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -64], rax
  cmpq [rbp + -160], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  jmp std.net.dns.is_hex_digit_block_38
std.net.dns.is_hex_digit_block_38:
  movq [rbp + -168], rax
  testq rax, rax
  jne std.net.dns.is_hex_digit_block_39
  jmp std.net.dns.is_hex_digit_block_41
std.net.dns.is_hex_digit_block_39:
  jmp std.net.dns.is_hex_digit_block_39
  movq $18, rax
  jmp std.net.dns.is_hex_digit_epilogue
std.net.dns.is_hex_digit_block_41:
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -64], rax
  cmpq [rbp + -176], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  testq rax, rax
  jne std.net.dns.is_hex_digit_block_49
  jmp std.net.dns.is_hex_digit_block_45
std.net.dns.is_hex_digit_block_45:
  jmp std.net.dns.is_hex_digit_block_45
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -64], rax
  cmpq [rbp + -192], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  jmp std.net.dns.is_hex_digit_block_49
std.net.dns.is_hex_digit_block_49:
  movq [rbp + -200], rax
  testq rax, rax
  jne std.net.dns.is_hex_digit_block_55
  jmp std.net.dns.is_hex_digit_block_51
std.net.dns.is_hex_digit_block_51:
  jmp std.net.dns.is_hex_digit_block_51
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -64], rax
  cmpq [rbp + -208], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -216]
  jmp std.net.dns.is_hex_digit_block_55
std.net.dns.is_hex_digit_block_55:
  movq [rbp + -216], rax
  testq rax, rax
  jne std.net.dns.is_hex_digit_block_61
  jmp std.net.dns.is_hex_digit_block_57
std.net.dns.is_hex_digit_block_57:
  jmp std.net.dns.is_hex_digit_block_57
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -64], rax
  cmpq [rbp + -224], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  jmp std.net.dns.is_hex_digit_block_61
std.net.dns.is_hex_digit_block_61:
  movq [rbp + -232], rax
  testq rax, rax
  jne std.net.dns.is_hex_digit_block_67
  jmp std.net.dns.is_hex_digit_block_63
std.net.dns.is_hex_digit_block_63:
  jmp std.net.dns.is_hex_digit_block_63
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -64], rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  jmp std.net.dns.is_hex_digit_block_67
std.net.dns.is_hex_digit_block_67:
  movq [rbp + -248], rax
  testq rax, rax
  jne std.net.dns.is_hex_digit_block_73
  jmp std.net.dns.is_hex_digit_block_69
std.net.dns.is_hex_digit_block_69:
  jmp std.net.dns.is_hex_digit_block_69
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -64], rax
  cmpq [rbp + -256], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -264]
  jmp std.net.dns.is_hex_digit_block_73
std.net.dns.is_hex_digit_block_73:
  movq [rbp + -264], rax
  testq rax, rax
  jne std.net.dns.is_hex_digit_block_74
  jmp std.net.dns.is_hex_digit_block_76
std.net.dns.is_hex_digit_block_74:
  jmp std.net.dns.is_hex_digit_block_74
  movq $18, rax
  jmp std.net.dns.is_hex_digit_epilogue
std.net.dns.is_hex_digit_block_76:
  movq $10, rax
  jmp std.net.dns.is_hex_digit_epilogue
std.net.dns.is_hex_digit_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.net.dns.is_hex_digit:

.globl std.net.dns.is_digit
std.net.dns.is_digit:
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
std.net.dns.is_digit_entry:
std.net.dns.is_digit_block_0:
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.net.dns.is_digit_block_3
  jmp std.net.dns.is_digit_block_5
std.net.dns.is_digit_block_3:
  jmp std.net.dns.is_digit_block_3
  movq $18, rax
  jmp std.net.dns.is_digit_epilogue
std.net.dns.is_digit_block_5:
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  cmpq [rbp + -88], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.net.dns.is_digit_block_8
  jmp std.net.dns.is_digit_block_10
std.net.dns.is_digit_block_8:
  jmp std.net.dns.is_digit_block_8
  movq $18, rax
  jmp std.net.dns.is_digit_epilogue
std.net.dns.is_digit_block_10:
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -64], rax
  cmpq [rbp + -104], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.net.dns.is_digit_block_13
  jmp std.net.dns.is_digit_block_15
std.net.dns.is_digit_block_13:
  jmp std.net.dns.is_digit_block_13
  movq $18, rax
  jmp std.net.dns.is_digit_epilogue
std.net.dns.is_digit_block_15:
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
  jne std.net.dns.is_digit_block_18
  jmp std.net.dns.is_digit_block_20
std.net.dns.is_digit_block_18:
  jmp std.net.dns.is_digit_block_18
  movq $18, rax
  jmp std.net.dns.is_digit_epilogue
std.net.dns.is_digit_block_20:
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -64], rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  testq rax, rax
  jne std.net.dns.is_digit_block_23
  jmp std.net.dns.is_digit_block_25
std.net.dns.is_digit_block_23:
  jmp std.net.dns.is_digit_block_23
  movq $18, rax
  jmp std.net.dns.is_digit_epilogue
std.net.dns.is_digit_block_25:
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -64], rax
  cmpq [rbp + -152], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  testq rax, rax
  jne std.net.dns.is_digit_block_28
  jmp std.net.dns.is_digit_block_30
std.net.dns.is_digit_block_28:
  jmp std.net.dns.is_digit_block_28
  movq $18, rax
  jmp std.net.dns.is_digit_epilogue
std.net.dns.is_digit_block_30:
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -64], rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne std.net.dns.is_digit_block_33
  jmp std.net.dns.is_digit_block_35
std.net.dns.is_digit_block_33:
  jmp std.net.dns.is_digit_block_33
  movq $18, rax
  jmp std.net.dns.is_digit_epilogue
std.net.dns.is_digit_block_35:
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -64], rax
  cmpq [rbp + -184], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  testq rax, rax
  jne std.net.dns.is_digit_block_38
  jmp std.net.dns.is_digit_block_40
std.net.dns.is_digit_block_38:
  jmp std.net.dns.is_digit_block_38
  movq $18, rax
  jmp std.net.dns.is_digit_epilogue
std.net.dns.is_digit_block_40:
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -64], rax
  cmpq [rbp + -200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  testq rax, rax
  jne std.net.dns.is_digit_block_43
  jmp std.net.dns.is_digit_block_45
std.net.dns.is_digit_block_43:
  jmp std.net.dns.is_digit_block_43
  movq $18, rax
  jmp std.net.dns.is_digit_epilogue
std.net.dns.is_digit_block_45:
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -64], rax
  cmpq [rbp + -216], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  testq rax, rax
  jne std.net.dns.is_digit_block_48
  jmp std.net.dns.is_digit_block_50
std.net.dns.is_digit_block_48:
  jmp std.net.dns.is_digit_block_48
  movq $18, rax
  jmp std.net.dns.is_digit_epilogue
std.net.dns.is_digit_block_50:
  movq $10, rax
  jmp std.net.dns.is_digit_epilogue
std.net.dns.is_digit_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.net.dns.is_digit:

.globl std.net.dns.split_string
std.net.dns.split_string:
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
std.net.dns.split_string_entry:
std.net.dns.split_string_block_0:
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  jmp std.net.dns.split_string_block_5
std.net.dns.split_string_block_5:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r6, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.net.dns.split_string_block_8
  jmp std.net.dns.split_string_block_36
std.net.dns.split_string_block_8:
  jmp std.net.dns.split_string_block_8
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -96], r8
  call substring
  movq $r12, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.net.dns.split_string_block_14
  jmp std.net.dns.split_string_block_23
std.net.dns.split_string_block_14:
  jmp std.net.dns.split_string_block_14
  movq $0, rcx
  call lm_list_new
  movq $r15, rcx
  movq [rbp + -80], rdx
  call lm_list_append
  movq $0, rcx
  call lm_list_new
  movq $r17, rcx
  movq [rbp + -80], rdx
  call lm_list_append
  movq $r2, rax
  addq $r17, rax
  movq rax, $r19
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  jmp std.net.dns.split_string_block_31
std.net.dns.split_string_block_23:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -120]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -120], r8
  call substring
  movq $r24, rcx
  call lm_to_string
  movq rax, [rbp + -128]
  movq [rbp + -112], rcx
  movq [rbp + -128], rdx
  call lm_str_concat
  movq rax, [rbp + -136]
  jmp std.net.dns.split_string_block_31
std.net.dns.split_string_block_31:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.net.dns.split_string_block_5
std.net.dns.split_string_block_36:
  movq $0, rcx
  call lm_list_new
  movq $r30, rcx
  movq [rbp + -136], rdx
  call lm_list_append
  movq $0, rcx
  call lm_list_new
  movq $r32, rcx
  movq [rbp + -136], rdx
  call lm_list_append
  movq $r19, rax
  addq $r32, rax
  movq rax, $r34
  movq $r34, rax
  jmp std.net.dns.split_string_epilogue
std.net.dns.split_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.net.dns.split_string:

.globl std.net.dns.DNS.is_ipv4
std.net.dns.DNS.is_ipv4:
  push rbp
  mov rbp, rsp
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
std.net.dns.DNS.is_ipv4_entry:
  movq $0, rax
  jmp std.net.dns.DNS.is_ipv4_epilogue
std.net.dns.DNS.is_ipv4_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.net.dns.DNS.is_ipv4:

.globl std.net.dns.DNS.resolve
std.net.dns.DNS.resolve:
  push rbp
  mov rbp, rsp
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
std.net.dns.DNS.resolve_entry:
  movq $0, rax
  jmp std.net.dns.DNS.resolve_epilogue
std.net.dns.DNS.resolve_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.net.dns.DNS.resolve:

.globl std.net.dns.Resolver.init
std.net.dns.Resolver.init:
  push rbp
  mov rbp, rsp
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
std.net.dns.Resolver.init_entry:
  movq $0, rax
  jmp std.net.dns.Resolver.init_epilogue
std.net.dns.Resolver.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.net.dns.Resolver.init:

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
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_33], rcx
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
  movq [rel str_const_34], rcx
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
  movq [rel str_const_35], rcx
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
  movq [rel str_const_36], rcx
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
  movq [rel str_const_37], rcx
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
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_39], rcx
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
  movq [rel str_const_40], rcx
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

.globl std.net.dns.DNS.is_ipv6
std.net.dns.DNS.is_ipv6:
  push rbp
  mov rbp, rsp
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
std.net.dns.DNS.is_ipv6_entry:
  movq $0, rax
  jmp std.net.dns.DNS.is_ipv6_epilogue
std.net.dns.DNS.is_ipv6_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.net.dns.DNS.is_ipv6:

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

.globl std.net.dns.Resolver.resolve
std.net.dns.Resolver.resolve:
  push rbp
  mov rbp, rsp
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
std.net.dns.Resolver.resolve_entry:
  movq $0, rax
  jmp std.net.dns.Resolver.resolve_epilogue
std.net.dns.Resolver.resolve_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.net.dns.Resolver.resolve:

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

.globl std.net.dns.DNS.resolve_or_passthrough
std.net.dns.DNS.resolve_or_passthrough:
  push rbp
  mov rbp, rsp
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
std.net.dns.DNS.resolve_or_passthrough_entry:
  movq $0, rax
  jmp std.net.dns.DNS.resolve_or_passthrough_epilogue
std.net.dns.DNS.resolve_or_passthrough_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.net.dns.DNS.resolve_or_passthrough:

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
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_42], rcx
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
  movq [rel str_const_43], rcx
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

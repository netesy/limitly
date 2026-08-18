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
  .string "Testing Error frame..."
.align 8
str_const_1:
  .string "E101"
.align 8
str_const_2:
  .string "Database offline"
.align 8
str_const_3:
  .string "E101"
.align 8
str_const_4:
  .string "error_instance.code should be E101"
.align 8
str_const_5:
  .string "Database offline"
.align 8
str_const_6:
  .string "error_instance.message mismatch"
.align 8
str_const_7:
  .string "[E101] Database offline"
.align 8
str_const_8:
  .string "error_instance.to_string() incorrect"
.align 8
str_const_9:
  .string "E102"
.align 8
str_const_10:
  .string "Disk full"
.align 8
str_const_11:
  .string "E102"
.align 8
str_const_12:
  .string "idx_err_val.code incorrect"
.align 8
str_const_13:
  .string "Disk full"
.align 8
str_const_14:
  .string "idx_err_val.message mismatch"
.align 8
str_const_15:
  .string "Error frame tests passed!"
.align 8
str_const_16:
  .string "=== Core Module Test Suite ==="
.align 8
str_const_17:
  .string "Error tests failed"
.align 8
str_const_18:
  .string "Option tests failed"
.align 8
str_const_19:
  .string "Result tests failed"
.align 8
str_const_20:
  .string "Trait tests failed"
.align 8
str_const_21:
  .string "All standard library core tests passed successfully."
.align 8
str_const_22:
  .string "Testing Option frame..."
.align 8
str_const_23:
  .string "hello"
.align 8
str_const_24:
  .string "opt_some should be Some"
.align 8
str_const_25:
  .string "opt_some should not be None"
.align 8
str_const_26:
  .string "hello"
.align 8
str_const_27:
  .string "opt_some unwrap failed"
.align 8
str_const_28:
  .string "fallback"
.align 8
str_const_29:
  .string "hello"
.align 8
str_const_30:
  .string "opt_some unwrap_or failed"
.align 8
str_const_31:
  .string "opt_none should not be Some"
.align 8
str_const_32:
  .string "opt_none should be None"
.align 8
str_const_33:
  .string "fallback"
.align 8
str_const_34:
  .string "fallback"
.align 8
str_const_35:
  .string "opt_none unwrap_or fallback failed"
.align 8
str_const_36:
  .string "map_string_len"
.align 8
str_const_37:
  .string "opt_mapped should be Some"
.align 8
str_const_38:
  .string "opt_mapped value should be 5"
.align 8
str_const_39:
  .string "map_string_len"
.align 8
str_const_40:
  .string "mapped opt_none should be None"
.align 8
str_const_41:
  .string "is_positive_int"
.align 8
str_const_42:
  .string "opt_filtered_true should be Some"
.align 8
str_const_43:
  .string "opt_filtered_true value incorrect"
.align 8
str_const_44:
  .string "is_positive_int"
.align 8
str_const_45:
  .string "opt_filtered_false should be None"
.align 8
str_const_46:
  .string "idx_some should be Some"
.align 8
str_const_47:
  .string "idx_some value incorrect"
.align 8
str_const_48:
  .string "idx_none should be None"
.align 8
str_const_49:
  .string "Option frame tests passed!"
.align 8
str_const_50:
  .string ""
.align 8
str_const_51:
  .string ""
.align 8
str_const_52:
  .string "Testing Result frame..."
.align 8
str_const_53:
  .string "res_ok_val should be Ok"
.align 8
str_const_54:
  .string "res_ok_val should not be Err"
.align 8
str_const_55:
  .string "res_ok_val unwrap failed"
.align 8
str_const_56:
  .string "res_ok_val unwrap_or failed"
.align 8
str_const_57:
  .string "E500"
.align 8
str_const_58:
  .string "Server Timeout"
.align 8
str_const_59:
  .string "res_err_val should not be Ok"
.align 8
str_const_60:
  .string "res_err_val should be Err"
.align 8
str_const_61:
  .string "res_err_val unwrap_or fallback failed"
.align 8
str_const_62:
  .string "E500"
.align 8
str_const_63:
  .string "res_err_val unwrap_err code incorrect"
.align 8
str_const_64:
  .string "add_one"
.align 8
str_const_65:
  .string "res_mapped should be Ok"
.align 8
str_const_66:
  .string "res_mapped value should be 101"
.align 8
str_const_67:
  .string "add_one"
.align 8
str_const_68:
  .string "res_err_mapped should be Err"
.align 8
str_const_69:
  .string "success"
.align 8
str_const_70:
  .string "idx_ok_val should be Ok"
.align 8
str_const_71:
  .string "success"
.align 8
str_const_72:
  .string "idx_ok_val unwrap failed"
.align 8
str_const_73:
  .string "E404"
.align 8
str_const_74:
  .string "Not Found"
.align 8
str_const_75:
  .string "idx_err_val2 should be Err"
.align 8
str_const_76:
  .string "Result frame tests passed!"
.align 8
str_const_77:
  .string "Testing Traits..."
.align 8
str_const_78:
  .string "10 should be less than 20"
.align 8
str_const_79:
  .string "20 should be greater than 10"
.align 8
str_const_80:
  .string "10 should equal 10"
.align 8
str_const_81:
  .string "should not be disposed initially"
.align 8
str_const_82:
  .string "should be disposed after calling dispose()"
.align 8
str_const_83:
  .string "cloned_data"
.align 8
str_const_84:
  .string "cloned_data"
.align 8
str_const_85:
  .string "cloned data mismatch"
.align 8
str_const_86:
  .string "modified"
.align 8
str_const_87:
  .string "cloned_data"
.align 8
str_const_88:
  .string "clone should be separate from source"
.align 8
str_const_89:
  .string "hash value mismatch (5 * 31 = 155)"
.align 8
str_const_90:
  .string "Trait tests passed!"
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
  call std.core.error.__init__
  call std.core.option.__init__
  call std.core.result.__init__
  call std.core.comparable.__init__
  call std.core.disposable.__init__
  call std.core.cloneable.__init__
  call std.core.hashable.__init__
  call std.core.index.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq [rel str_const_16], rcx
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
  call test_error
  movq $r2, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_option
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  call test_result
  movq $r12, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  call test_traits
  movq $r17, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rel str_const_21], rcx
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

.globl std.core.comparable.__init__
std.core.comparable.__init__:
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
std.core.comparable.__init___entry:
  movq $0, rax
  jmp std.core.comparable.__init___epilogue
std.core.comparable.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.comparable.__init__:

.globl std.core.index.__init__
std.core.index.__init__:
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
std.core.index.__init___entry:
  movq $0, rax
  jmp std.core.index.__init___epilogue
std.core.index.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.index.__init__:

.globl std.core.index.Err
std.core.index.Err:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.index.Err_entry:
std.core.index.Err_block_0:
  movq [rbp + -64], rcx
  call std.core.result.Err
  movq $r1, rax
  jmp std.core.index.Err_epilogue
std.core.index.Err_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.index.Err:

.globl std.core.index.Ok
std.core.index.Ok:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.index.Ok_entry:
std.core.index.Ok_block_0:
  movq [rbp + -64], rcx
  call std.core.result.Ok
  movq $r1, rax
  jmp std.core.index.Ok_epilogue
std.core.index.Ok_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.index.Ok:

.globl std.core.index.None
std.core.index.None:
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
std.core.index.None_entry:
std.core.index.None_block_0:
  call std.core.option.None
  movq $0, rax
  jmp std.core.index.None_epilogue
std.core.index.None_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.index.None:

.globl std.core.index.Some
std.core.index.Some:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.index.Some_entry:
std.core.index.Some_block_0:
  movq [rbp + -64], rcx
  call std.core.option.Some
  movq $r1, rax
  jmp std.core.index.Some_epilogue
std.core.index.Some_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.index.Some:

.globl is_positive_int
is_positive_int:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
is_positive_int_entry:
is_positive_int_block_0:
  movq [rbp + -64], rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp is_positive_int_epilogue
is_positive_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_is_positive_int:

.globl test_error
test_error:
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
test_error_entry:
test_error_block_0:
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
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -112], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -112], rcx
  movq [rbp + -96], rdx
  movq [rbp + -104], r8
  call std.core.error.Error.init
  movq [rbp + -112], rax
  addq $0, rax
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  mov rax, [rax]
  movq rax, [rbp + -128]
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rbp + -112], rax
  addq $0, rax
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  mov rax, [rax]
  movq rax, [rbp + -168]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rax
  cmpq [rbp + -176], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -184], rcx
  movq [rbp + -192], rdx
  call lm_assert
  movq [rbp + -112], rcx
  call std.core.error.Error.to_string
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq $r17, rax
  cmpq [rbp + -200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call std.core.index.Error
  movq $r24, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -240]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rax
  cmpq [rbp + -248], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -256], rcx
  movq [rbp + -264], rdx
  call lm_assert
  movq $r24, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -272]
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -272], rax
  cmpq [rbp + -280], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -288]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -288], rcx
  movq [rbp + -296], rdx
  call lm_assert
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  addq $16, rax
  movq rax, [rbp + -312]
  movq [rbp + -312], rax
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  mov rax, [rax]
  movq rax, [rbp + -328]
  movq [rbp + -328], rcx
  call lm_print_str
  movq $9, rax
  jmp test_error_epilogue
test_error_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_error:

.globl DummyHashable.hash
DummyHashable.hash:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
DummyHashable.hash_entry:
  movq $0, rax
  jmp DummyHashable.hash_epilogue
DummyHashable.hash_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_DummyHashable.hash:

.globl std.core.index.main
std.core.index.main:
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
std.core.index.main_entry:
std.core.index.main_block_0:
  movq $0, rax
  jmp std.core.index.main_epilogue
std.core.index.main_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.index.main:

.globl DummyComparable.compare
DummyComparable.compare:
  push rbp
  mov rbp, rsp
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
DummyComparable.compare_entry:
  movq $0, rax
  jmp DummyComparable.compare_epilogue
DummyComparable.compare_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_DummyComparable.compare:

.globl std.core.option.Option.init
std.core.option.Option.init:
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
std.core.option.Option.init_entry:
  movq $0, rax
  jmp std.core.option.Option.init_epilogue
std.core.option.Option.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.option.Option.init:

.globl DummyDisposable.dispose
DummyDisposable.dispose:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
DummyDisposable.dispose_entry:
  movq $0, rax
  jmp DummyDisposable.dispose_epilogue
DummyDisposable.dispose_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_DummyDisposable.dispose:

.globl std.core.option.Option.unwrap_or
std.core.option.Option.unwrap_or:
  push rbp
  mov rbp, rsp
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
std.core.option.Option.unwrap_or_entry:
  movq $0, rax
  jmp std.core.option.Option.unwrap_or_epilogue
std.core.option.Option.unwrap_or_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.option.Option.unwrap_or:

.globl std.core.hashable.__init__
std.core.hashable.__init__:
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
std.core.hashable.__init___entry:
  movq $0, rax
  jmp std.core.hashable.__init___epilogue
std.core.hashable.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.hashable.__init__:

.globl add_one
add_one:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
add_one_entry:
add_one_block_0:
  movq [rbp + -64], rax
  addq $9, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp add_one_epilogue
add_one_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_add_one:

.globl DummyComparable.init
DummyComparable.init:
  push rbp
  mov rbp, rsp
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
DummyComparable.init_entry:
  movq $0, rax
  jmp DummyComparable.init_epilogue
DummyComparable.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_DummyComparable.init:

.globl std.core.result.Result.unwrap
std.core.result.Result.unwrap:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.result.Result.unwrap_entry:
  movq $0, rax
  jmp std.core.result.Result.unwrap_epilogue
std.core.result.Result.unwrap_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.result.Result.unwrap:

.globl DummyDisposable.init
DummyDisposable.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
DummyDisposable.init_entry:
  movq $0, rax
  jmp DummyDisposable.init_epilogue
DummyDisposable.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_DummyDisposable.init:

.globl DummyCloneable.init
DummyCloneable.init:
  push rbp
  mov rbp, rsp
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
DummyCloneable.init_entry:
  movq $0, rax
  jmp DummyCloneable.init_epilogue
DummyCloneable.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_DummyCloneable.init:

.globl std.core.option.Option.is_none
std.core.option.Option.is_none:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.option.Option.is_none_entry:
  movq $0, rax
  jmp std.core.option.Option.is_none_epilogue
std.core.option.Option.is_none_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.option.Option.is_none:

.globl std.core.error.Error.to_string
std.core.error.Error.to_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.error.Error.to_string_entry:
  movq $0, rax
  jmp std.core.error.Error.to_string_epilogue
std.core.error.Error.to_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.error.Error.to_string:

.globl test_option
test_option:
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
test_option_entry:
test_option_block_0:
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
  call std.core.option.Some
  movq $r3, rcx
  call std.core.option.Option.is_some
  movq $r5, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call lm_assert
  movq $r3, rcx
  call std.core.option.Option.is_none
  movq $r10, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq $r3, rcx
  call std.core.option.Option.unwrap
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r15, rax
  cmpq [rbp + -136], rax
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
  movq $r3, rcx
  movq [rbp + -160], rdx
  call std.core.option.Option.unwrap_or
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq $r21, rax
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
  call std.core.option.None
  movq $r26, rcx
  call std.core.option.Option.is_some
  movq $r28, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq $r26, rcx
  call std.core.option.Option.is_none
  movq $r33, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq $r26, rcx
  movq [rbp + -224], rdx
  call std.core.option.Option.unwrap_or
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq $r39, rax
  cmpq [rbp + -232], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq $r3, rcx
  movq [rbp + -256], rdx
  call std.core.option.Option.map
  movq $r45, rcx
  call std.core.option.Option.is_some
  movq $r47, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -264]
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -264], rcx
  movq [rbp + -272], rdx
  call lm_assert
  movq $r45, rcx
  call std.core.option.Option.unwrap
  movq $r52, rax
  cmpq $41, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -280]
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -280], rcx
  movq [rbp + -288], rdx
  call lm_assert
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq $r26, rcx
  movq [rbp + -296], rdx
  call std.core.option.Option.map
  movq $r58, rcx
  call std.core.option.Option.is_none
  movq $r60, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -304]
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -304], rcx
  movq [rbp + -312], rdx
  call lm_assert
  movq $81, rcx
  call std.core.option.Some
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq $r66, rcx
  movq [rbp + -320], rdx
  call std.core.option.Option.filter
  movq $r69, rcx
  call std.core.option.Option.is_some
  movq $r71, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -328]
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -328], rcx
  movq [rbp + -336], rdx
  call lm_assert
  movq $r69, rcx
  call std.core.option.Option.unwrap
  movq $r76, rax
  cmpq $81, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -344]
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -344], rcx
  movq [rbp + -352], rdx
  call lm_assert
  movq $41, rax
  negq rax
  movq rax, [rbp + -360]
  movq [rbp + -360], rcx
  call std.core.option.Some
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq $r83, rcx
  movq [rbp + -368], rdx
  call std.core.option.Option.filter
  movq $r86, rcx
  call std.core.option.Option.is_none
  movq $r88, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -376]
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -376], rcx
  movq [rbp + -384], rdx
  call lm_assert
  movq $337, rcx
  call std.core.index.Some
  movq $r94, rcx
  call std.core.option.Option.is_some
  movq $r96, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -392], rcx
  movq [rbp + -400], rdx
  call lm_assert
  movq $r94, rcx
  call std.core.option.Option.unwrap
  movq $r101, rax
  cmpq $337, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -408]
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -408], rcx
  movq [rbp + -416], rdx
  call lm_assert
  call std.core.index.None
  movq $r106, rcx
  call std.core.option.Option.is_none
  movq $r108, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -424]
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rbp + -424], rcx
  movq [rbp + -432], rdx
  call lm_assert
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  addq $16, rax
  movq rax, [rbp + -448]
  movq [rbp + -448], rax
  movq rax, [rbp + -456]
  movq [rbp + -456], rax
  mov rax, [rax]
  movq rax, [rbp + -464]
  movq [rbp + -464], rcx
  call lm_print_str
  movq $9, rax
  jmp test_option_epilogue
test_option_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_option:

.globl DummyCloneable.clone
DummyCloneable.clone:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
DummyCloneable.clone_entry:
  movq $0, rax
  jmp DummyCloneable.clone_epilogue
DummyCloneable.clone_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_DummyCloneable.clone:

.globl std.core.option.__init__
std.core.option.__init__:
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
std.core.option.__init___entry:
  movq $0, rax
  jmp std.core.option.__init___epilogue
std.core.option.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.option.__init__:

.globl std.core.result.Result.is_err
std.core.result.Result.is_err:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.result.Result.is_err_entry:
  movq $0, rax
  jmp std.core.result.Result.is_err_epilogue
std.core.result.Result.is_err_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.result.Result.is_err:

.globl std.core.result.Result.unwrap_or
std.core.result.Result.unwrap_or:
  push rbp
  mov rbp, rsp
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
std.core.result.Result.unwrap_or_entry:
  movq $0, rax
  jmp std.core.result.Result.unwrap_or_epilogue
std.core.result.Result.unwrap_or_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.result.Result.unwrap_or:

.globl std.core.option.Option.filter
std.core.option.Option.filter:
  push rbp
  mov rbp, rsp
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
std.core.option.Option.filter_entry:
  movq $0, rax
  jmp std.core.option.Option.filter_epilogue
std.core.option.Option.filter_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.option.Option.filter:

.globl std.core.result.Result.unwrap_err
std.core.result.Result.unwrap_err:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.result.Result.unwrap_err_entry:
  movq $0, rax
  jmp std.core.result.Result.unwrap_err_epilogue
std.core.result.Result.unwrap_err_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.result.Result.unwrap_err:

.globl std.core.result.Result.map
std.core.result.Result.map:
  push rbp
  mov rbp, rsp
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
std.core.result.Result.map_entry:
  movq $0, rax
  jmp std.core.result.Result.map_epilogue
std.core.result.Result.map_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.result.Result.map:

.globl std.core.option.Option.map
std.core.option.Option.map:
  push rbp
  mov rbp, rsp
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
std.core.option.Option.map_entry:
  movq $0, rax
  jmp std.core.option.Option.map_epilogue
std.core.option.Option.map_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.option.Option.map:

.globl std.core.result.Result.init
std.core.result.Result.init:
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
std.core.result.Result.init_entry:
  movq $0, rax
  jmp std.core.result.Result.init_epilogue
std.core.result.Result.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.result.Result.init:

.globl std.core.result.Ok
std.core.result.Ok:
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
std.core.result.Ok_entry:
std.core.result.Ok_block_0:
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -88], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -88], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  call std.core.error.Error.init
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -96], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -96], rcx
  movq $18, rdx
  movq [rbp + -64], r8
  movq [rbp + -88], r9
  call std.core.result.Result.init
  movq [rbp + -96], rax
  jmp std.core.result.Ok_epilogue
std.core.result.Ok_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.result.Ok:

.globl std.core.result.Err
std.core.result.Err:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.result.Err_entry:
std.core.result.Err_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq $10, rdx
  movq $2, r8
  movq [rbp + -64], r9
  call std.core.result.Result.init
  movq [rbp + -72], rax
  jmp std.core.result.Err_epilogue
std.core.result.Err_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.result.Err:

.globl std.core.result.__init__
std.core.result.__init__:
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
std.core.result.__init___entry:
  movq $0, rax
  jmp std.core.result.__init___epilogue
std.core.result.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.result.__init__:

.globl std.core.result.Result.is_ok
std.core.result.Result.is_ok:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.result.Result.is_ok_entry:
  movq $0, rax
  jmp std.core.result.Result.is_ok_epilogue
std.core.result.Result.is_ok_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.result.Result.is_ok:

.globl map_string_len
map_string_len:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
map_string_len_entry:
map_string_len_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r1, rax
  jmp map_string_len_epilogue
map_string_len_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_map_string_len:

.globl test_result
test_result:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 424
test_result_entry:
test_result_block_0:
  movq [rel str_const_52], rcx
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
  movq $801, rcx
  call std.core.result.Ok
  movq $r3, rcx
  call std.core.result.Result.is_ok
  movq $r5, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  movq $r3, rcx
  call std.core.result.Result.is_err
  movq $r10, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq $r3, rcx
  call std.core.result.Result.unwrap
  movq $r15, rax
  cmpq $801, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq $r3, rcx
  movq $1601, rdx
  call std.core.result.Result.unwrap_or
  movq $r21, rax
  cmpq $801, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -176], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -176], rcx
  movq [rbp + -160], rdx
  movq [rbp + -168], r8
  call std.core.error.Error.init
  movq [rbp + -176], rcx
  call std.core.result.Err
  movq $r31, rcx
  call std.core.result.Result.is_ok
  movq $r33, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -184], rcx
  movq [rbp + -192], rdx
  call lm_assert
  movq $r31, rcx
  call std.core.result.Result.is_err
  movq $r38, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -200], rcx
  movq [rbp + -208], rdx
  call lm_assert
  movq $r31, rcx
  movq $1601, rdx
  call std.core.result.Result.unwrap_or
  movq $r44, rax
  cmpq $1601, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -216]
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -216], rcx
  movq [rbp + -224], rdx
  call lm_assert
  movq $r31, rcx
  call std.core.result.Result.unwrap_err
  movq $r49, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -232]
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -248], rcx
  movq [rbp + -256], rdx
  call lm_assert
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq $r3, rcx
  movq [rbp + -264], rdx
  call std.core.result.Result.map
  movq $r57, rcx
  call std.core.result.Result.is_ok
  movq $r59, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -272]
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -272], rcx
  movq [rbp + -280], rdx
  call lm_assert
  movq $r57, rcx
  call std.core.result.Result.unwrap
  movq $r64, rax
  cmpq $809, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -288]
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -288], rcx
  movq [rbp + -296], rdx
  call lm_assert
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq $r31, rcx
  movq [rbp + -304], rdx
  call std.core.result.Result.map
  movq $r70, rcx
  call std.core.result.Result.is_err
  movq $r72, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -312]
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -312], rcx
  movq [rbp + -320], rdx
  call lm_assert
  movq [rel str_const_69], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -328], rcx
  call std.core.index.Ok
  movq $r78, rcx
  call std.core.result.Result.is_ok
  movq $r80, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -336]
  movq [rel str_const_70], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -336], rcx
  movq [rbp + -344], rdx
  call lm_assert
  movq $r78, rcx
  call std.core.result.Result.unwrap
  movq [rel str_const_71], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq $r85, rax
  cmpq [rbp + -352], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rel str_const_72], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -360], rcx
  movq [rbp + -368], rdx
  call lm_assert
  movq [rel str_const_73], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -392], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -392], rcx
  movq [rbp + -376], rdx
  movq [rbp + -384], r8
  call std.core.error.Error.init
  movq [rbp + -392], rcx
  call std.core.index.Err
  movq $r94, rcx
  call std.core.result.Result.is_err
  movq $r96, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -400]
  movq [rel str_const_75], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -400], rcx
  movq [rbp + -408], rdx
  call lm_assert
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -416], rax
  addq $16, rax
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  movq rax, [rbp + -432]
  movq [rbp + -432], rax
  mov rax, [rax]
  movq rax, [rbp + -440]
  movq [rbp + -440], rcx
  call lm_print_str
  movq $9, rax
  jmp test_result_epilogue
test_result_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_result:

.globl std.core.error.Error.init
std.core.error.Error.init:
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
std.core.error.Error.init_entry:
  movq $0, rax
  jmp std.core.error.Error.init_epilogue
std.core.error.Error.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.error.Error.init:

.globl std.core.option.Option.is_some
std.core.option.Option.is_some:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.option.Option.is_some_entry:
  movq $0, rax
  jmp std.core.option.Option.is_some_epilogue
std.core.option.Option.is_some_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.option.Option.is_some:

.globl std.core.option.Option.unwrap
std.core.option.Option.unwrap:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.option.Option.unwrap_entry:
  movq $0, rax
  jmp std.core.option.Option.unwrap_epilogue
std.core.option.Option.unwrap_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.option.Option.unwrap:

.globl std.core.option.Some
std.core.option.Some:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.core.option.Some_entry:
std.core.option.Some_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq $18, rdx
  movq [rbp + -64], r8
  call std.core.option.Option.init
  movq [rbp + -72], rax
  jmp std.core.option.Some_epilogue
std.core.option.Some_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.option.Some:

.globl std.core.disposable.__init__
std.core.disposable.__init__:
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
std.core.disposable.__init___entry:
  movq $0, rax
  jmp std.core.disposable.__init___epilogue
std.core.disposable.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.disposable.__init__:

.globl std.core.option.None
std.core.option.None:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.core.option.None_entry:
std.core.option.None_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  movq $10, rdx
  movq $2, r8
  call std.core.option.Option.init
  movq [rbp + -64], rax
  jmp std.core.option.None_epilogue
std.core.option.None_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.option.None:

.globl std.core.cloneable.__init__
std.core.cloneable.__init__:
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
std.core.cloneable.__init___entry:
  movq $0, rax
  jmp std.core.cloneable.__init___epilogue
std.core.cloneable.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.cloneable.__init__:

.globl std.core.error.__init__
std.core.error.__init__:
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
std.core.error.__init___entry:
  movq $0, rax
  jmp std.core.error.__init___epilogue
std.core.error.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.error.__init__:

.globl test_traits
test_traits:
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
test_traits_entry:
test_traits_block_0:
  movq [rel str_const_77], rcx
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
  movq $81, rdx
  call DummyComparable.init
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -104], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -104], rcx
  movq $161, rdx
  call DummyComparable.init
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call DummyComparable.compare
  movq $9, rax
  negq rax
  movq rax, [rbp + -112]
  movq $r10, rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rel str_const_78], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rcx
  movq [rbp + -128], rdx
  call lm_assert
  movq [rbp + -104], rcx
  movq [rbp + -96], rdx
  call DummyComparable.compare
  movq $r16, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_79], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -152], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -152], rcx
  movq $81, rdx
  call DummyComparable.init
  movq [rbp + -96], rcx
  movq [rbp + -152], rdx
  call DummyComparable.compare
  movq $r24, rax
  cmpq $1, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_80], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -176], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -176], rcx
  call DummyDisposable.init
  movq [rbp + -176], rax
  addq $0, rax
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  mov rax, [rax]
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rel str_const_81], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -200], rcx
  movq [rbp + -208], rdx
  call lm_assert
  movq [rbp + -176], rcx
  call DummyDisposable.dispose
  movq [rbp + -176], rax
  addq $0, rax
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  mov rax, [rax]
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  movq [rel str_const_82], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rcx
  movq [rbp + -240], rdx
  call lm_assert
  movq [rel str_const_83], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -256], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -256], rcx
  movq [rbp + -248], rdx
  call DummyCloneable.init
  movq [rbp + -256], rcx
  call DummyCloneable.clone
  movq $r47, rax
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  addq $0, rax
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -280]
  movq [rel str_const_84], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -280], rax
  cmpq [rbp + -288], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rel str_const_85], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -296], rcx
  movq [rbp + -304], rdx
  call lm_assert
  movq [rel str_const_86], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -256], rax
  addq $0, rax
  movq rax, [rbp + -320]
  movq [rbp + -64], rax
  movq [rbp + -320], rdx
  mov [rdx], rax
  movq [rbp + -264], rax
  addq $0, rax
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -336]
  movq [rel str_const_87], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -336], rax
  cmpq [rbp + -344], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -352]
  movq [rel str_const_88], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -352], rcx
  movq [rbp + -360], rdx
  call lm_assert
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -368], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -368], rcx
  movq $41, rdx
  call DummyHashable.init
  movq [rbp + -368], rcx
  call DummyHashable.hash
  movq $r65, rax
  cmpq $1241, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -376]
  movq [rel str_const_89], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -376], rcx
  movq [rbp + -384], rdx
  call lm_assert
  movq [rel str_const_90], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  addq $16, rax
  movq rax, [rbp + -400]
  movq [rbp + -400], rax
  movq rax, [rbp + -408]
  movq [rbp + -408], rax
  mov rax, [rax]
  movq rax, [rbp + -416]
  movq [rbp + -416], rcx
  call lm_print_str
  movq $9, rax
  jmp test_traits_epilogue
test_traits_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_traits:

.globl DummyHashable.init
DummyHashable.init:
  push rbp
  mov rbp, rsp
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
DummyHashable.init_entry:
  movq $0, rax
  jmp DummyHashable.init_epilogue
DummyHashable.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_DummyHashable.init:

.globl std.core.index.Error
std.core.index.Error:
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
std.core.index.Error_entry:
std.core.index.Error_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -80], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  call std.core.error.Error.init
  movq [rbp + -80], rax
  jmp std.core.index.Error_epilogue
std.core.index.Error_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.core.index.Error:

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

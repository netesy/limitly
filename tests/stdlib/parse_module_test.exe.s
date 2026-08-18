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
  .string "%s"
.align 8
str_const_1:
  .string "0"
.align 8
str_const_2:
  .string ""
.align 8
str_const_3:
  .string ""
.align 8
str_const_4:
  .string "ERR"
.align 8
str_const_5:
  .string "ERR"
.align 8
str_const_6:
  .string ""
.align 8
str_const_7:
  .string ""
.align 8
str_const_8:
  .string "+"
.align 8
str_const_9:
  .string "-"
.align 8
str_const_10:
  .string ""
.align 8
str_const_11:
  .string "0"
.align 8
str_const_12:
  .string "1"
.align 8
str_const_13:
  .string "2"
.align 8
str_const_14:
  .string "3"
.align 8
str_const_15:
  .string "4"
.align 8
str_const_16:
  .string "5"
.align 8
str_const_17:
  .string "6"
.align 8
str_const_18:
  .string "7"
.align 8
str_const_19:
  .string "8"
.align 8
str_const_20:
  .string "9"
.align 8
str_const_21:
  .string "ERR"
.align 8
str_const_22:
  .string "Testing Parse Helpers..."
.align 8
str_const_23:
  .string "789"
.align 8
str_const_24:
  .string "parse_int helper err failed"
.align 8
str_const_25:
  .string "parse_int helper failed"
.align 8
str_const_26:
  .string "0"
.align 8
str_const_27:
  .string "parse_bool helper failed"
.align 8
str_const_28:
  .string "1970-01-12 13:46:40"
.align 8
str_const_29:
  .string "parse_datetime nil failed"
.align 8
str_const_30:
  .string "parse_datetime year failed"
.align 8
str_const_31:
  .string "parse_datetime month failed"
.align 8
str_const_32:
  .string "parse_datetime day failed"
.align 8
str_const_33:
  .string ""
.align 8
str_const_34:
  .string ""
.align 8
str_const_35:
  .string "Testing Parse Frame..."
.align 8
str_const_36:
  .string "123"
.align 8
str_const_37:
  .string "parse_int err failed"
.align 8
str_const_38:
  .string "parse_int failed"
.align 8
str_const_39:
  .string "-456"
.align 8
str_const_40:
  .string "parse_int negative err failed"
.align 8
str_const_41:
  .string "parse_int negative failed"
.align 8
str_const_42:
  .string "true"
.align 8
str_const_43:
  .string "parse_bool failed"
.align 8
str_const_44:
  .string "=== Parse Module Test Suite ==="
.align 8
str_const_45:
  .string "Parse frame test failed"
.align 8
str_const_46:
  .string "Parse helpers test failed"
.align 8
str_const_47:
  .string "All parse tests passed successfully."
.align 8
str_const_48:
  .string "ERR"
.align 8
str_const_49:
  .string ""
.align 8
str_const_50:
  .string "true"
.align 8
str_const_51:
  .string "1"
.align 8
str_const_52:
  .string ""
.align 8
str_const_53:
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
  call std.parse.index.__init__
  call std.time.datetime.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
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
  call test_parse_frame
  movq $r2, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_parse_helpers
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq [rel str_const_47], rcx
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

.globl std.parse.datetime.__init__
std.parse.datetime.__init__:
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
std.parse.datetime.__init___entry:
  movq $0, rax
  jmp std.parse.datetime.__init___epilogue
std.parse.datetime.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.datetime.__init__:

.globl std.parse.datetime.parse_datetime
std.parse.datetime.parse_datetime:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.parse.datetime.parse_datetime_entry:
std.parse.datetime.parse_datetime_block_0:
  movq $0, rcx
  movq [rbp + -64], rdx
  call std.time.datetime.DateTime.from_string
  movq $r2, rax
  jmp std.parse.datetime.parse_datetime_epilogue
std.parse.datetime.parse_datetime_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.datetime.parse_datetime:

.globl std.time.duration.__init__
std.time.duration.__init__:
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
std.time.duration.__init___entry:
  movq $0, rax
  jmp std.time.duration.__init___epilogue
std.time.duration.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.__init__:

.globl std.time.duration.TimeDuration.init
std.time.duration.TimeDuration.init:
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
std.time.duration.TimeDuration.init_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.init_epilogue
std.time.duration.TimeDuration.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.init:

.globl std.time.duration.TimeDuration.human_readable
std.time.duration.TimeDuration.human_readable:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.duration.TimeDuration.human_readable_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.human_readable_epilogue
std.time.duration.TimeDuration.human_readable_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.human_readable:

.globl std.time.duration.TimeDuration.to_milliseconds
std.time.duration.TimeDuration.to_milliseconds:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.duration.TimeDuration.to_milliseconds_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.to_milliseconds_epilogue
std.time.duration.TimeDuration.to_milliseconds_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.to_milliseconds:

.globl std.time.duration.TimeDuration.greater_than
std.time.duration.TimeDuration.greater_than:
  push rbp
  mov rbp, rsp
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
std.time.duration.TimeDuration.greater_than_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.greater_than_epilogue
std.time.duration.TimeDuration.greater_than_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.greater_than:

.globl std.time.duration.TimeDuration.subtract
std.time.duration.TimeDuration.subtract:
  push rbp
  mov rbp, rsp
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
std.time.duration.TimeDuration.subtract_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.subtract_epilogue
std.time.duration.TimeDuration.subtract_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.subtract:

.globl std.time.duration.TimeDuration.add
std.time.duration.TimeDuration.add:
  push rbp
  mov rbp, rsp
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
std.time.duration.TimeDuration.add_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.add_epilogue
std.time.duration.TimeDuration.add_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.add:

.globl std.time.duration.TimeDuration.from_minutes
std.time.duration.TimeDuration.from_minutes:
  push rbp
  mov rbp, rsp
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
std.time.duration.TimeDuration.from_minutes_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.from_minutes_epilogue
std.time.duration.TimeDuration.from_minutes_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.from_minutes:

.globl std.time.duration.TimeDuration.from_hours
std.time.duration.TimeDuration.from_hours:
  push rbp
  mov rbp, rsp
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
std.time.duration.TimeDuration.from_hours_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.from_hours_epilogue
std.time.duration.TimeDuration.from_hours_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.from_hours:

.globl std.time.duration.TimeDuration.from_days
std.time.duration.TimeDuration.from_days:
  push rbp
  mov rbp, rsp
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
std.time.duration.TimeDuration.from_days_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.from_days_epilogue
std.time.duration.TimeDuration.from_days_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.from_days:

.globl std.time.duration.pad_int
std.time.duration.pad_int:
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
std.time.duration.pad_int_entry:
std.time.duration.pad_int_block_0:
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -80], rcx
  movq [rbp + -64], rdx
  call lm_rt_str_format
  movq rax, [rbp + -88]
  jmp std.time.duration.pad_int_block_4
std.time.duration.pad_int_block_4:
  movq [rbp + -88], rcx
  call lm_list_len
  movq $r5, rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.time.duration.pad_int_block_7
  jmp std.time.duration.pad_int_block_11
std.time.duration.pad_int_block_7:
  jmp std.time.duration.pad_int_block_7
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -104], rcx
  movq [rbp + -88], rdx
  call lm_str_concat
  movq rax, [rbp + -112]
  jmp std.time.duration.pad_int_block_4
std.time.duration.pad_int_block_11:
  movq [rbp + -112], rax
  jmp std.time.duration.pad_int_epilogue
std.time.duration.pad_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.pad_int:

.globl std.parse.index.__init__
std.parse.index.__init__:
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
std.parse.index.__init___entry:
  movq $0, rax
  jmp std.parse.index.__init___epilogue
std.parse.index.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.index.__init__:

.globl std.time.duration.TimeDuration.to_string
std.time.duration.TimeDuration.to_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.duration.TimeDuration.to_string_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.to_string_epilogue
std.time.duration.TimeDuration.to_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.to_string:

.globl std.time.duration.TimeDuration.multiply
std.time.duration.TimeDuration.multiply:
  push rbp
  mov rbp, rsp
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
std.time.duration.TimeDuration.multiply_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.multiply_epilogue
std.time.duration.TimeDuration.multiply_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.multiply:

.globl std.parse.index.parse_datetime
std.parse.index.parse_datetime:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.parse.index.parse_datetime_entry:
std.parse.index.parse_datetime_block_0:
  movq [rbp + -64], rcx
  call std.parse.datetime.parse_datetime
  movq $r1, rax
  jmp std.parse.index.parse_datetime_epilogue
std.parse.index.parse_datetime_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.index.parse_datetime:

.globl std.parse.index.parse_bool
std.parse.index.parse_bool:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.parse.index.parse_bool_entry:
std.parse.index.parse_bool_block_0:
  movq [rbp + -64], rcx
  call std.parse.bool.parse_bool
  movq $r1, rax
  jmp std.parse.index.parse_bool_epilogue
std.parse.index.parse_bool_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.index.parse_bool:

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

.globl std.time.timezone.TimeZone.utc
std.time.timezone.TimeZone.utc:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.timezone.TimeZone.utc_entry:
  movq $0, rax
  jmp std.time.timezone.TimeZone.utc_epilogue
std.time.timezone.TimeZone.utc_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.timezone.TimeZone.utc:

.globl std.time.timezone.TimeZone.offset_string
std.time.timezone.TimeZone.offset_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.timezone.TimeZone.offset_string_entry:
  movq $0, rax
  jmp std.time.timezone.TimeZone.offset_string_epilogue
std.time.timezone.TimeZone.offset_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.timezone.TimeZone.offset_string:

.globl std.time.duration.TimeDuration.to_seconds
std.time.duration.TimeDuration.to_seconds:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.duration.TimeDuration.to_seconds_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.to_seconds_epilogue
std.time.duration.TimeDuration.to_seconds_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.to_seconds:

.globl std.time.datetime.DateTime.end_of_year
std.time.datetime.DateTime.end_of_year:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.end_of_year_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.end_of_year_epilogue
std.time.datetime.DateTime.end_of_year_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.end_of_year:

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

.globl std.time.datetime.DateTime.is_between
std.time.datetime.DateTime.is_between:
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
std.time.datetime.DateTime.is_between_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.is_between_epilogue
std.time.datetime.DateTime.is_between_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.is_between:

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
  movq [rel str_const_4], rcx
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
  movq [rel str_const_5], rcx
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
  movq [rel str_const_6], rcx
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

.globl std.parse.numbers.parse_int
std.parse.numbers.parse_int:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 232
  mov [rbp + -64], rcx
std.parse.numbers.parse_int_entry:
std.parse.numbers.parse_int_block_0:
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.parse.numbers.parse_int_block_3
  jmp std.parse.numbers.parse_int_block_5
std.parse.numbers.parse_int_block_3:
  jmp std.parse.numbers.parse_int_block_3
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.parse.numbers.parse_int_epilogue
std.parse.numbers.parse_int_block_5:
  movq [rbp + -64], rcx
  call lm_list_len
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $9, r8
  call substring
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r13, rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.parse.numbers.parse_int_block_18
  jmp std.parse.numbers.parse_int_block_21
std.parse.numbers.parse_int_block_18:
  jmp std.parse.numbers.parse_int_block_18
  jmp std.parse.numbers.parse_int_block_31
std.parse.numbers.parse_int_block_21:
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r13, rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.parse.numbers.parse_int_block_24
  jmp std.parse.numbers.parse_int_block_30
std.parse.numbers.parse_int_block_24:
  jmp std.parse.numbers.parse_int_block_24
  movq $9, rax
  negq rax
  movq rax, [rbp + -128]
  jmp std.parse.numbers.parse_int_block_30
std.parse.numbers.parse_int_block_30:
  jmp std.parse.numbers.parse_int_block_31
std.parse.numbers.parse_int_block_31:
  movq $9, rax
  cmpq $r5, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne std.parse.numbers.parse_int_block_33
  jmp std.parse.numbers.parse_int_block_35
std.parse.numbers.parse_int_block_33:
  jmp std.parse.numbers.parse_int_block_33
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  jmp std.parse.numbers.parse_int_epilogue
std.parse.numbers.parse_int_block_35:
  jmp std.parse.numbers.parse_int_block_36
std.parse.numbers.parse_int_block_36:
  movq $9, rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne std.parse.numbers.parse_int_block_38
  jmp std.parse.numbers.parse_int_block_64
std.parse.numbers.parse_int_block_38:
  jmp std.parse.numbers.parse_int_block_38
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -160]
  movq [rbp + -64], rcx
  movq $9, rdx
  movq [rbp + -160], r8
  call substring
  movq $r33, rcx
  call std.parse.numbers.char_to_digit
  movq $9, rax
  negq rax
  movq rax, [rbp + -168]
  movq $r35, rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne std.parse.numbers.parse_int_block_49
  jmp std.parse.numbers.parse_int_block_51
std.parse.numbers.parse_int_block_49:
  jmp std.parse.numbers.parse_int_block_49
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  jmp std.parse.numbers.parse_int_epilogue
std.parse.numbers.parse_int_block_51:
  movq $1, rax
  imulq $81, rax
  movq rax, [rbp + -192]
  movq $1, rax
  imulq $81, rax
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  addq $r35, rax
  movq rax, [rbp + -208]
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -216]
  jmp std.parse.numbers.parse_int_block_36
std.parse.numbers.parse_int_block_64:
  movq $18, rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  testq rax, rax
  jne std.parse.numbers.parse_int_block_67
  jmp std.parse.numbers.parse_int_block_69
std.parse.numbers.parse_int_block_67:
  jmp std.parse.numbers.parse_int_block_67
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  jmp std.parse.numbers.parse_int_epilogue
std.parse.numbers.parse_int_block_69:
  movq [rbp + -128], rax
  imulq [rbp + -208], rax
  movq rax, [rbp + -240]
  movq [rbp + -240], rax
  jmp std.parse.numbers.parse_int_epilogue
std.parse.numbers.parse_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.numbers.parse_int:

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

.globl std.parse.numbers.parse_float
std.parse.numbers.parse_float:
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
std.parse.numbers.parse_float_entry:
std.parse.numbers.parse_float_block_0:
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.parse.numbers.parse_float_block_3
  jmp std.parse.numbers.parse_float_block_5
std.parse.numbers.parse_float_block_3:
  jmp std.parse.numbers.parse_float_block_3
  movq [rbp + -64], rcx
  call lm_error_new
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.parse.numbers.parse_float_epilogue
std.parse.numbers.parse_float_block_5:
  movq [rbp + -64], rax
  jmp std.parse.numbers.parse_float_epilogue
std.parse.numbers.parse_float_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.numbers.parse_float:

.globl std.time.datetime.DateTime.day
std.time.datetime.DateTime.day:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.day_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.day_epilogue
std.time.datetime.DateTime.day_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.day:

.globl std.time.datetime.__init__
std.time.datetime.__init__:
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
std.time.datetime.__init___entry:
  movq $0, rax
  jmp std.time.datetime.__init___epilogue
std.time.datetime.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.__init__:

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

.globl std.parse.index.parse_float
std.parse.index.parse_float:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.parse.index.parse_float_entry:
std.parse.index.parse_float_block_0:
  movq [rbp + -64], rcx
  call std.parse.numbers.parse_float
  movq $r1, rax
  jmp std.parse.index.parse_float_epilogue
std.parse.index.parse_float_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.index.parse_float:

.globl std.time.datetime.DateTime.day_of_year
std.time.datetime.DateTime.day_of_year:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.day_of_year_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.day_of_year_epilogue
std.time.datetime.DateTime.day_of_year_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.day_of_year:

.globl std.parse.numbers.char_to_digit
std.parse.numbers.char_to_digit:
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
std.parse.numbers.char_to_digit_entry:
std.parse.numbers.char_to_digit_block_0:
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.parse.numbers.char_to_digit_block_3
  jmp std.parse.numbers.char_to_digit_block_5
std.parse.numbers.char_to_digit_block_3:
  jmp std.parse.numbers.char_to_digit_block_3
  movq $1, rax
  jmp std.parse.numbers.char_to_digit_epilogue
std.parse.numbers.char_to_digit_block_5:
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  cmpq [rbp + -88], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.parse.numbers.char_to_digit_block_8
  jmp std.parse.numbers.char_to_digit_block_10
std.parse.numbers.char_to_digit_block_8:
  jmp std.parse.numbers.char_to_digit_block_8
  movq $9, rax
  jmp std.parse.numbers.char_to_digit_epilogue
std.parse.numbers.char_to_digit_block_10:
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -64], rax
  cmpq [rbp + -104], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.parse.numbers.char_to_digit_block_13
  jmp std.parse.numbers.char_to_digit_block_15
std.parse.numbers.char_to_digit_block_13:
  jmp std.parse.numbers.char_to_digit_block_13
  movq $17, rax
  jmp std.parse.numbers.char_to_digit_epilogue
std.parse.numbers.char_to_digit_block_15:
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -64], rax
  cmpq [rbp + -120], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.parse.numbers.char_to_digit_block_18
  jmp std.parse.numbers.char_to_digit_block_20
std.parse.numbers.char_to_digit_block_18:
  jmp std.parse.numbers.char_to_digit_block_18
  movq $25, rax
  jmp std.parse.numbers.char_to_digit_epilogue
std.parse.numbers.char_to_digit_block_20:
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -64], rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  testq rax, rax
  jne std.parse.numbers.char_to_digit_block_23
  jmp std.parse.numbers.char_to_digit_block_25
std.parse.numbers.char_to_digit_block_23:
  jmp std.parse.numbers.char_to_digit_block_23
  movq $33, rax
  jmp std.parse.numbers.char_to_digit_epilogue
std.parse.numbers.char_to_digit_block_25:
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -64], rax
  cmpq [rbp + -152], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  testq rax, rax
  jne std.parse.numbers.char_to_digit_block_28
  jmp std.parse.numbers.char_to_digit_block_30
std.parse.numbers.char_to_digit_block_28:
  jmp std.parse.numbers.char_to_digit_block_28
  movq $41, rax
  jmp std.parse.numbers.char_to_digit_epilogue
std.parse.numbers.char_to_digit_block_30:
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -64], rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne std.parse.numbers.char_to_digit_block_33
  jmp std.parse.numbers.char_to_digit_block_35
std.parse.numbers.char_to_digit_block_33:
  jmp std.parse.numbers.char_to_digit_block_33
  movq $49, rax
  jmp std.parse.numbers.char_to_digit_epilogue
std.parse.numbers.char_to_digit_block_35:
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -64], rax
  cmpq [rbp + -184], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  testq rax, rax
  jne std.parse.numbers.char_to_digit_block_38
  jmp std.parse.numbers.char_to_digit_block_40
std.parse.numbers.char_to_digit_block_38:
  jmp std.parse.numbers.char_to_digit_block_38
  movq $57, rax
  jmp std.parse.numbers.char_to_digit_epilogue
std.parse.numbers.char_to_digit_block_40:
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -64], rax
  cmpq [rbp + -200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  testq rax, rax
  jne std.parse.numbers.char_to_digit_block_43
  jmp std.parse.numbers.char_to_digit_block_45
std.parse.numbers.char_to_digit_block_43:
  jmp std.parse.numbers.char_to_digit_block_43
  movq $65, rax
  jmp std.parse.numbers.char_to_digit_epilogue
std.parse.numbers.char_to_digit_block_45:
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -64], rax
  cmpq [rbp + -216], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  testq rax, rax
  jne std.parse.numbers.char_to_digit_block_48
  jmp std.parse.numbers.char_to_digit_block_50
std.parse.numbers.char_to_digit_block_48:
  jmp std.parse.numbers.char_to_digit_block_48
  movq $73, rax
  jmp std.parse.numbers.char_to_digit_epilogue
std.parse.numbers.char_to_digit_block_50:
  movq $9, rax
  negq rax
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  jmp std.parse.numbers.char_to_digit_epilogue
std.parse.numbers.char_to_digit_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.numbers.char_to_digit:

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
  movq [rel str_const_21], rcx
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

.globl test_parse_helpers
test_parse_helpers:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 232
test_parse_helpers_entry:
test_parse_helpers_block_0:
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
  call std.parse.index.parse_int
  jmp test_parse_helpers_block_6
test_parse_helpers_block_6:
  movq $r3, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne test_parse_helpers_block_9
  jmp test_parse_helpers_block_8
test_parse_helpers_block_8:
  jmp test_parse_helpers_block_8
  jmp test_parse_helpers_block_17
test_parse_helpers_block_9:
  movq $r3, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne test_parse_helpers_block_11
  jmp test_parse_helpers_block_24
test_parse_helpers_block_11:
  jmp test_parse_helpers_block_11
  jmp test_parse_helpers_block_12
test_parse_helpers_block_12:
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq $10, rcx
  movq [rbp + -120], rdx
  call lm_assert
  jmp test_parse_helpers_block_24
test_parse_helpers_block_17:
  movq $r3, rax
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  cmpq $6313, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  jmp test_parse_helpers_block_24
test_parse_helpers_block_24:
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -152], rcx
  call std.parse.index.parse_bool
  movq $r18, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -176], rcx
  call std.parse.index.parse_datetime
  jmp test_parse_helpers_block_34
test_parse_helpers_block_34:
  movq $r24, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  testq rax, rax
  jne test_parse_helpers_block_37
  jmp test_parse_helpers_block_36
test_parse_helpers_block_36:
  jmp test_parse_helpers_block_36
  jmp test_parse_helpers_block_42
test_parse_helpers_block_37:
  jmp test_parse_helpers_block_38
test_parse_helpers_block_38:
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq $10, rcx
  movq [rbp + -192], rdx
  call lm_assert
  jmp test_parse_helpers_block_61
test_parse_helpers_block_42:
  movq $r24, rax
  movq rax, [rbp + -200]
  movq [rbp + -200], rcx
  call std.time.datetime.DateTime.year
  movq $r30, rax
  cmpq $15761, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq [rbp + -200], rcx
  call std.time.datetime.DateTime.month
  movq $r35, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  movq [rbp + -200], rcx
  call std.time.datetime.DateTime.day
  movq $r40, rax
  cmpq $97, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  jmp test_parse_helpers_block_61
test_parse_helpers_block_61:
  movq $9, rax
  jmp test_parse_helpers_epilogue
test_parse_helpers_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_parse_helpers:

.globl std.time.duration.TimeDuration.from_microseconds
std.time.duration.TimeDuration.from_microseconds:
  push rbp
  mov rbp, rsp
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
std.time.duration.TimeDuration.from_microseconds_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.from_microseconds_epilogue
std.time.duration.TimeDuration.from_microseconds_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.from_microseconds:

.globl std.time.datetime.DateTime.end_of_day
std.time.datetime.DateTime.end_of_day:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.end_of_day_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.end_of_day_epilogue
std.time.datetime.DateTime.end_of_day_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.end_of_day:

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

.globl std.time.datetime.timestamp_to_year
std.time.datetime.timestamp_to_year:
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
std.time.datetime.timestamp_to_year_entry:
std.time.datetime.timestamp_to_year_block_0:
  movq [rbp + -64], rax
  cmpq $1, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.time.datetime.timestamp_to_year_block_3
  jmp std.time.datetime.timestamp_to_year_block_22
std.time.datetime.timestamp_to_year_block_3:
  jmp std.time.datetime.timestamp_to_year_block_3
  movq $691201, rax
  movq rax, [rbp + -80]
  movq [rbp + -64], rax
  cqto
  movq [rbp + -80], rcx
  idivq rcx
  movq rax, [rbp + -88]
  jmp std.time.datetime.timestamp_to_year_block_10
std.time.datetime.timestamp_to_year_block_10:
  movq $15761, rcx
  call std.time.datetime.get_days_in_year
  movq [rbp + -88], rax
  cmpq $r10, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.time.datetime.timestamp_to_year_block_13
  jmp std.time.datetime.timestamp_to_year_block_21
std.time.datetime.timestamp_to_year_block_13:
  jmp std.time.datetime.timestamp_to_year_block_13
  movq $15761, rcx
  call std.time.datetime.get_days_in_year
  movq [rbp + -88], rax
  subq $r13, rax
  movq rax, [rbp + -104]
  movq $15761, rax
  addq $9, rax
  movq rax, [rbp + -112]
  jmp std.time.datetime.timestamp_to_year_block_10
std.time.datetime.timestamp_to_year_block_21:
  movq [rbp + -112], rax
  jmp std.time.datetime.timestamp_to_year_epilogue
std.time.datetime.timestamp_to_year_block_22:
  movq [rbp + -64], rax
  negq rax
  movq rax, [rbp + -120]
  movq $691201, rax
  movq rax, [rbp + -128]
  movq [rbp + -120], rax
  cqto
  movq [rbp + -128], rcx
  idivq rcx
  movq rax, [rbp + -136]
  movq [rbp + -64], rax
  negq rax
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  cqto
  movq $691201, rcx
  idivq rcx
  movq rdx, [rbp + -152]
  movq [rbp + -152], rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  testq rax, rax
  jne std.time.datetime.timestamp_to_year_block_33
  jmp std.time.datetime.timestamp_to_year_block_38
std.time.datetime.timestamp_to_year_block_33:
  jmp std.time.datetime.timestamp_to_year_block_33
  movq [rbp + -136], rax
  addq $9, rax
  movq rax, [rbp + -168]
  jmp std.time.datetime.timestamp_to_year_block_38
std.time.datetime.timestamp_to_year_block_38:
  jmp std.time.datetime.timestamp_to_year_block_41
std.time.datetime.timestamp_to_year_block_41:
  movq $15761, rax
  subq $9, rax
  movq rax, [rbp + -176]
  movq [rbp + -176], rcx
  call std.time.datetime.get_days_in_year
  movq [rbp + -168], rax
  cmpq $r36, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  testq rax, rax
  jne std.time.datetime.timestamp_to_year_block_46
  jmp std.time.datetime.timestamp_to_year_block_53
std.time.datetime.timestamp_to_year_block_46:
  jmp std.time.datetime.timestamp_to_year_block_46
  movq $15761, rax
  subq $9, rax
  movq rax, [rbp + -192]
  movq [rbp + -192], rcx
  call std.time.datetime.get_days_in_year
  movq [rbp + -168], rax
  subq $r41, rax
  movq rax, [rbp + -200]
  jmp std.time.datetime.timestamp_to_year_block_41
std.time.datetime.timestamp_to_year_block_53:
  movq [rbp + -192], rax
  subq $9, rax
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  jmp std.time.datetime.timestamp_to_year_epilogue
std.time.datetime.timestamp_to_year_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.timestamp_to_year:

.globl std.time.timezone.TimeZone.to_seconds_offset
std.time.timezone.TimeZone.to_seconds_offset:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.timezone.TimeZone.to_seconds_offset_entry:
  movq $0, rax
  jmp std.time.timezone.TimeZone.to_seconds_offset_epilogue
std.time.timezone.TimeZone.to_seconds_offset_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.timezone.TimeZone.to_seconds_offset:

.globl std.time.timezone.TimeZone.from_offset
std.time.timezone.TimeZone.from_offset:
  push rbp
  mov rbp, rsp
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
std.time.timezone.TimeZone.from_offset_entry:
  movq $0, rax
  jmp std.time.timezone.TimeZone.from_offset_epilogue
std.time.timezone.TimeZone.from_offset_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.timezone.TimeZone.from_offset:

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

.globl std.time.datetime.DateTime.to_iso_string
std.time.datetime.DateTime.to_iso_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.to_iso_string_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.to_iso_string_epilogue
std.time.datetime.DateTime.to_iso_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.to_iso_string:

.globl std.time.datetime.DateTime.difference
std.time.datetime.DateTime.difference:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.difference_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.difference_epilogue
std.time.datetime.DateTime.difference_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.difference:

.globl std.time.datetime.DateTime.from_timestamp
std.time.datetime.DateTime.from_timestamp:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.from_timestamp_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.from_timestamp_epilogue
std.time.datetime.DateTime.from_timestamp_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.from_timestamp:

.globl std.time.datetime.DateTime.to_string
std.time.datetime.DateTime.to_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.to_string_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.to_string_epilogue
std.time.datetime.DateTime.to_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.to_string:

.globl std.time.datetime.get_days_in_month
std.time.datetime.get_days_in_month:
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
std.time.datetime.get_days_in_month_entry:
std.time.datetime.get_days_in_month_block_0:
  movq $0, rcx
  call lm_list_new
  movq $r2, rcx
  movq $249, rdx
  call lm_list_append
  movq $r2, rcx
  movq $225, rdx
  call lm_list_append
  movq $r2, rcx
  movq $249, rdx
  call lm_list_append
  movq $r2, rcx
  movq $241, rdx
  call lm_list_append
  movq $r2, rcx
  movq $249, rdx
  call lm_list_append
  movq $r2, rcx
  movq $241, rdx
  call lm_list_append
  movq $r2, rcx
  movq $249, rdx
  call lm_list_append
  movq $r2, rcx
  movq $249, rdx
  call lm_list_append
  movq $r2, rcx
  movq $241, rdx
  call lm_list_append
  movq $r2, rcx
  movq $249, rdx
  call lm_list_append
  movq $r2, rcx
  movq $241, rdx
  call lm_list_append
  movq $r2, rcx
  movq $249, rdx
  call lm_list_append
  movq [rbp + -72], rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.time.datetime.get_days_in_month_block_30
  jmp std.time.datetime.get_days_in_month_block_33
std.time.datetime.get_days_in_month_block_30:
  jmp std.time.datetime.get_days_in_month_block_30
  movq [rbp + -64], rcx
  call std.time.datetime.is_leap_year
  jmp std.time.datetime.get_days_in_month_block_33
std.time.datetime.get_days_in_month_block_33:
  movq $r31, rax
  testq rax, rax
  jne std.time.datetime.get_days_in_month_block_34
  jmp std.time.datetime.get_days_in_month_block_36
std.time.datetime.get_days_in_month_block_34:
  jmp std.time.datetime.get_days_in_month_block_34
  movq $233, rax
  jmp std.time.datetime.get_days_in_month_epilogue
std.time.datetime.get_days_in_month_block_36:
  movq [rbp + -72], rax
  subq $9, rax
  movq rax, [rbp + -88]
  movq $r2, rcx
  movq [rbp + -88], rdx
  call lm_list_get
  movq $r36, rax
  jmp std.time.datetime.get_days_in_month_epilogue
std.time.datetime.get_days_in_month_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.get_days_in_month:

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
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_34], rcx
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

.globl std.time.datetime.DateTime.day_of_week
std.time.datetime.DateTime.day_of_week:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.day_of_week_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.day_of_week_epilogue
std.time.datetime.DateTime.day_of_week_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.day_of_week:

.globl test_parse_frame
test_parse_frame:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 232
test_parse_frame_entry:
test_parse_frame_block_0:
  movq [rel str_const_35], rcx
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
  call std.parse.index.Parse.init
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call std.parse.index.Parse.parse_int
  jmp test_parse_frame_block_10
test_parse_frame_block_10:
  movq $r7, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne test_parse_frame_block_13
  jmp test_parse_frame_block_12
test_parse_frame_block_12:
  jmp test_parse_frame_block_12
  jmp test_parse_frame_block_21
test_parse_frame_block_13:
  movq $r7, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne test_parse_frame_block_15
  jmp test_parse_frame_block_28
test_parse_frame_block_15:
  jmp test_parse_frame_block_15
  jmp test_parse_frame_block_16
test_parse_frame_block_16:
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq $10, rcx
  movq [rbp + -128], rdx
  call lm_assert
  jmp test_parse_frame_block_28
test_parse_frame_block_21:
  movq $r7, rax
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  cmpq $985, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  jmp test_parse_frame_block_28
test_parse_frame_block_28:
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -96], rcx
  movq [rbp + -160], rdx
  call std.parse.index.Parse.parse_int
  jmp test_parse_frame_block_32
test_parse_frame_block_32:
  movq $r22, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  testq rax, rax
  jne test_parse_frame_block_35
  jmp test_parse_frame_block_34
test_parse_frame_block_34:
  jmp test_parse_frame_block_34
  jmp test_parse_frame_block_43
test_parse_frame_block_35:
  movq $r22, rax
  cmpq $9223372036854775807, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne test_parse_frame_block_37
  jmp test_parse_frame_block_51
test_parse_frame_block_37:
  jmp test_parse_frame_block_37
  jmp test_parse_frame_block_38
test_parse_frame_block_38:
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq $10, rcx
  movq [rbp + -184], rdx
  call lm_assert
  jmp test_parse_frame_block_51
test_parse_frame_block_43:
  movq $r22, rax
  movq rax, [rbp + -192]
  movq $3649, rax
  negq rax
  movq rax, [rbp + -200]
  movq [rbp + -192], rax
  cmpq [rbp + -200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  jmp test_parse_frame_block_51
test_parse_frame_block_51:
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -96], rcx
  movq [rbp + -224], rdx
  call std.parse.index.Parse.parse_bool
  movq $r38, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rcx
  movq [rbp + -240], rdx
  call lm_assert
  movq $9, rax
  jmp test_parse_frame_epilogue
test_parse_frame_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_parse_frame:

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

.globl std.time.datetime.DateTime.greater_than
std.time.datetime.DateTime.greater_than:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.greater_than_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.greater_than_epilogue
std.time.datetime.DateTime.greater_than_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.greater_than:

.globl std.time.datetime.DateTime.start_of_year
std.time.datetime.DateTime.start_of_year:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.start_of_year_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.start_of_year_epilogue
std.time.datetime.DateTime.start_of_year_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.start_of_year:

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

.globl std.time.duration.TimeDuration.less_than
std.time.duration.TimeDuration.less_than:
  push rbp
  mov rbp, rsp
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
std.time.duration.TimeDuration.less_than_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.less_than_epilogue
std.time.duration.TimeDuration.less_than_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.less_than:

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

.globl std.time.datetime.timestamp_to_day
std.time.datetime.timestamp_to_day:
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
std.time.datetime.timestamp_to_day_entry:
std.time.datetime.timestamp_to_day_block_0:
  movq [rbp + -64], rcx
  call std.time.datetime.timestamp_to_year
  movq [rbp + -64], rcx
  call std.time.datetime.timestamp_to_month
  movq $r1, rcx
  movq $r3, rdx
  movq $9, r8
  movq $1, r9
  call std.time.datetime.datetime_to_timestamp
  movq [rbp + -64], rax
  subq $r9, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  cmpq $1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.time.datetime.timestamp_to_day_block_15
  jmp std.time.datetime.timestamp_to_day_block_18
std.time.datetime.timestamp_to_day_block_15:
  jmp std.time.datetime.timestamp_to_day_block_15
  jmp std.time.datetime.timestamp_to_day_block_18
std.time.datetime.timestamp_to_day_block_18:
  movq $1, rax
  cqto
  movq $691201, rcx
  idivq rcx
  movq rax, [rbp + -88]
  movq $1, rax
  cqto
  movq $691201, rcx
  idivq rcx
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  addq $9, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  jmp std.time.datetime.timestamp_to_day_epilogue
std.time.datetime.timestamp_to_day_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.timestamp_to_day:

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
  movq [rel str_const_48], rcx
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
  movq [rel str_const_49], rcx
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

.globl std.time.duration.TimeDuration.to_microseconds
std.time.duration.TimeDuration.to_microseconds:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.duration.TimeDuration.to_microseconds_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.to_microseconds_epilogue
std.time.duration.TimeDuration.to_microseconds_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.to_microseconds:

.globl std.time.datetime.DateTime.with_second
std.time.datetime.DateTime.with_second:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.with_second_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.with_second_epilogue
std.time.datetime.DateTime.with_second_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.with_second:

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

.globl std.time.datetime.DateTime.minute
std.time.datetime.DateTime.minute:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.minute_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.minute_epilogue
std.time.datetime.DateTime.minute_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.minute:

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

.globl std.time.timezone.__init__
std.time.timezone.__init__:
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
std.time.timezone.__init___entry:
  movq $0, rax
  jmp std.time.timezone.__init___epilogue
std.time.timezone.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.timezone.__init__:

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

.globl std.time.duration.TimeDuration.from_seconds
std.time.duration.TimeDuration.from_seconds:
  push rbp
  mov rbp, rsp
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
std.time.duration.TimeDuration.from_seconds_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.from_seconds_epilogue
std.time.duration.TimeDuration.from_seconds_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.from_seconds:

.globl std.parse.bool.parse_bool
std.parse.bool.parse_bool:
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
std.parse.bool.parse_bool_entry:
std.parse.bool.parse_bool_block_0:
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.parse.bool.parse_bool_block_8
  jmp std.parse.bool.parse_bool_block_4
std.parse.bool.parse_bool_block_4:
  jmp std.parse.bool.parse_bool_block_4
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  cmpq [rbp + -88], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  jmp std.parse.bool.parse_bool_block_8
std.parse.bool.parse_bool_block_8:
  movq [rbp + -96], rax
  jmp std.parse.bool.parse_bool_epilogue
std.parse.bool.parse_bool_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.bool.parse_bool:

.globl std.parse.bool.__init__
std.parse.bool.__init__:
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
std.parse.bool.__init___entry:
  movq $0, rax
  jmp std.parse.bool.__init___epilogue
std.parse.bool.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.bool.__init__:

.globl std.time.datetime.DateTime.subtract
std.time.datetime.DateTime.subtract:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.subtract_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.subtract_epilogue
std.time.datetime.DateTime.subtract_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.subtract:

.globl std.time.datetime.to_i
std.time.datetime.to_i:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.to_i_entry:
std.time.datetime.to_i_block_0:
  movq [rbp + -64], rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  jmp std.time.datetime.to_i_epilogue
std.time.datetime.to_i_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.to_i:

.globl std.time.datetime.is_leap_year
std.time.datetime.is_leap_year:
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
std.time.datetime.is_leap_year_entry:
std.time.datetime.is_leap_year_block_0:
  movq [rbp + -64], rax
  cqto
  movq $33, rcx
  idivq rcx
  movq rdx, [rbp + -72]
  movq [rbp + -72], rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.time.datetime.is_leap_year_block_5
  jmp std.time.datetime.is_leap_year_block_7
std.time.datetime.is_leap_year_block_5:
  jmp std.time.datetime.is_leap_year_block_5
  movq $10, rax
  jmp std.time.datetime.is_leap_year_epilogue
std.time.datetime.is_leap_year_block_7:
  movq [rbp + -64], rax
  cqto
  movq $801, rcx
  idivq rcx
  movq rdx, [rbp + -88]
  movq [rbp + -88], rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.time.datetime.is_leap_year_block_12
  jmp std.time.datetime.is_leap_year_block_14
std.time.datetime.is_leap_year_block_12:
  jmp std.time.datetime.is_leap_year_block_12
  movq $18, rax
  jmp std.time.datetime.is_leap_year_epilogue
std.time.datetime.is_leap_year_block_14:
  movq [rbp + -64], rax
  cqto
  movq $3201, rcx
  idivq rcx
  movq rdx, [rbp + -104]
  movq [rbp + -104], rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.time.datetime.is_leap_year_block_19
  jmp std.time.datetime.is_leap_year_block_21
std.time.datetime.is_leap_year_block_19:
  jmp std.time.datetime.is_leap_year_block_19
  movq $10, rax
  jmp std.time.datetime.is_leap_year_epilogue
std.time.datetime.is_leap_year_block_21:
  movq $18, rax
  jmp std.time.datetime.is_leap_year_epilogue
std.time.datetime.is_leap_year_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.is_leap_year:

.globl std.time.datetime.DateTime.add
std.time.datetime.DateTime.add:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.add_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.add_epilogue
std.time.datetime.DateTime.add_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.add:

.globl std.time.datetime.DateTime.second
std.time.datetime.DateTime.second:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.second_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.second_epilogue
std.time.datetime.DateTime.second_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.second:

.globl std.parse.numbers.__init__
std.parse.numbers.__init__:
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
std.parse.numbers.__init___entry:
  movq $0, rax
  jmp std.parse.numbers.__init___epilogue
std.parse.numbers.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.numbers.__init__:

.globl std.time.datetime.get_days_in_year
std.time.datetime.get_days_in_year:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.get_days_in_year_entry:
std.time.datetime.get_days_in_year_block_0:
  movq [rbp + -64], rcx
  call std.time.datetime.is_leap_year
  movq $r1, rax
  cmpq $1, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.time.datetime.get_days_in_year_block_4
  jmp std.time.datetime.get_days_in_year_block_6
std.time.datetime.get_days_in_year_block_4:
  jmp std.time.datetime.get_days_in_year_block_4
  movq $2929, rax
  jmp std.time.datetime.get_days_in_year_epilogue
std.time.datetime.get_days_in_year_block_6:
  movq $2921, rax
  jmp std.time.datetime.get_days_in_year_epilogue
std.time.datetime.get_days_in_year_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.get_days_in_year:

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
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -72], rax
  addq $0, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rel str_const_53], rcx
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

.globl std.time.datetime.datetime_to_timestamp
std.time.datetime.datetime_to_timestamp:
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
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.time.datetime.datetime_to_timestamp_entry:
std.time.datetime.datetime_to_timestamp_block_0:
  jmp std.time.datetime.datetime_to_timestamp_block_3
std.time.datetime.datetime_to_timestamp_block_3:
  movq $15761, rax
  cmpq [rbp + -64], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.time.datetime.datetime_to_timestamp_block_5
  jmp std.time.datetime.datetime_to_timestamp_block_14
std.time.datetime.datetime_to_timestamp_block_5:
  jmp std.time.datetime.datetime_to_timestamp_block_5
  movq $15761, rcx
  call std.time.datetime.get_days_in_year
  movq $15761, rcx
  call std.time.datetime.get_days_in_year
  movq $1, rax
  addq $r11, rax
  movq rax, [rbp + -120]
  movq $15761, rax
  addq $9, rax
  movq rax, [rbp + -128]
  jmp std.time.datetime.datetime_to_timestamp_block_3
std.time.datetime.datetime_to_timestamp_block_14:
  jmp std.time.datetime.datetime_to_timestamp_block_15
std.time.datetime.datetime_to_timestamp_block_15:
  movq [rbp + -128], rax
  cmpq [rbp + -64], rax
  setg al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne std.time.datetime.datetime_to_timestamp_block_17
  jmp std.time.datetime.datetime_to_timestamp_block_24
std.time.datetime.datetime_to_timestamp_block_17:
  jmp std.time.datetime.datetime_to_timestamp_block_17
  movq [rbp + -128], rax
  subq $9, rax
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  call std.time.datetime.get_days_in_year
  movq [rbp + -120], rax
  subq $r20, rax
  movq rax, [rbp + -152]
  jmp std.time.datetime.datetime_to_timestamp_block_15
std.time.datetime.datetime_to_timestamp_block_24:
  jmp std.time.datetime.datetime_to_timestamp_block_26
std.time.datetime.datetime_to_timestamp_block_26:
  movq $9, rax
  cmpq [rbp + -72], rax
  setl al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  testq rax, rax
  jne std.time.datetime.datetime_to_timestamp_block_28
  jmp std.time.datetime.datetime_to_timestamp_block_37
std.time.datetime.datetime_to_timestamp_block_28:
  jmp std.time.datetime.datetime_to_timestamp_block_28
  movq [rbp + -64], rcx
  movq $9, rdx
  call std.time.datetime.get_days_in_month
  movq [rbp + -64], rcx
  movq $9, rdx
  call std.time.datetime.get_days_in_month
  movq [rbp + -152], rax
  addq $r26, rax
  movq rax, [rbp + -168]
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -176]
  jmp std.time.datetime.datetime_to_timestamp_block_26
std.time.datetime.datetime_to_timestamp_block_37:
  movq [rbp + -80], rax
  subq $9, rax
  movq rax, [rbp + -184]
  movq [rbp + -80], rax
  subq $9, rax
  movq rax, [rbp + -192]
  movq [rbp + -168], rax
  addq [rbp + -192], rax
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  imulq $691201, rax
  movq rax, [rbp + -208]
  movq [rbp + -88], rax
  imulq $28801, rax
  movq rax, [rbp + -216]
  movq [rbp + -200], rax
  imulq $691201, rax
  movq rax, [rbp + -224]
  movq [rbp + -88], rax
  imulq $28801, rax
  movq rax, [rbp + -232]
  movq [rbp + -224], rax
  addq [rbp + -232], rax
  movq rax, [rbp + -240]
  movq [rbp + -96], rax
  imulq $481, rax
  movq rax, [rbp + -248]
  movq [rbp + -200], rax
  imulq $691201, rax
  movq rax, [rbp + -256]
  movq [rbp + -88], rax
  imulq $28801, rax
  movq rax, [rbp + -264]
  movq [rbp + -200], rax
  imulq $691201, rax
  movq rax, [rbp + -272]
  movq [rbp + -88], rax
  imulq $28801, rax
  movq rax, [rbp + -280]
  movq [rbp + -272], rax
  addq [rbp + -280], rax
  movq rax, [rbp + -288]
  movq [rbp + -96], rax
  imulq $481, rax
  movq rax, [rbp + -296]
  movq [rbp + -288], rax
  addq [rbp + -296], rax
  movq rax, [rbp + -304]
  movq [rbp + -200], rax
  imulq $691201, rax
  movq rax, [rbp + -312]
  movq [rbp + -88], rax
  imulq $28801, rax
  movq rax, [rbp + -320]
  movq [rbp + -200], rax
  imulq $691201, rax
  movq rax, [rbp + -328]
  movq [rbp + -88], rax
  imulq $28801, rax
  movq rax, [rbp + -336]
  movq [rbp + -328], rax
  addq [rbp + -336], rax
  movq rax, [rbp + -344]
  movq [rbp + -96], rax
  imulq $481, rax
  movq rax, [rbp + -352]
  movq [rbp + -200], rax
  imulq $691201, rax
  movq rax, [rbp + -360]
  movq [rbp + -88], rax
  imulq $28801, rax
  movq rax, [rbp + -368]
  movq [rbp + -200], rax
  imulq $691201, rax
  movq rax, [rbp + -376]
  movq [rbp + -88], rax
  imulq $28801, rax
  movq rax, [rbp + -384]
  movq [rbp + -376], rax
  addq [rbp + -384], rax
  movq rax, [rbp + -392]
  movq [rbp + -96], rax
  imulq $481, rax
  movq rax, [rbp + -400]
  movq [rbp + -392], rax
  addq [rbp + -400], rax
  movq rax, [rbp + -408]
  movq [rbp + -408], rax
  addq [rbp + -104], rax
  movq rax, [rbp + -416]
  movq [rbp + -416], rax
  jmp std.time.datetime.datetime_to_timestamp_epilogue
std.time.datetime.datetime_to_timestamp_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.datetime_to_timestamp:

.globl std.time.datetime.DateTime.now
std.time.datetime.DateTime.now:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.now_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.now_epilogue
std.time.datetime.DateTime.now_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.now:

.globl std.time.datetime.DateTime.with_timezone
std.time.datetime.DateTime.with_timezone:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.with_timezone_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.with_timezone_epilogue
std.time.datetime.DateTime.with_timezone_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.with_timezone:

.globl std.time.datetime.DateTime.from_string
std.time.datetime.DateTime.from_string:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.from_string_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.from_string_epilogue
std.time.datetime.DateTime.from_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.from_string:

.globl std.time.datetime.DateTime.from_components
std.time.datetime.DateTime.from_components:
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
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.time.datetime.DateTime.from_components_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.from_components_epilogue
std.time.datetime.DateTime.from_components_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.from_components:

.globl std.time.duration.TimeDuration.total_seconds
std.time.duration.TimeDuration.total_seconds:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.duration.TimeDuration.total_seconds_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.total_seconds_epilogue
std.time.duration.TimeDuration.total_seconds_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.total_seconds:

.globl std.time.datetime.DateTime.week_of_year
std.time.datetime.DateTime.week_of_year:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.week_of_year_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.week_of_year_epilogue
std.time.datetime.DateTime.week_of_year_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.week_of_year:

.globl std.time.datetime.DateTime.year
std.time.datetime.DateTime.year:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.year_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.year_epilogue
std.time.datetime.DateTime.year_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.year:

.globl std.time.datetime.DateTime.month
std.time.datetime.DateTime.month:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.month_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.month_epilogue
std.time.datetime.DateTime.month_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.month:

.globl std.time.datetime.DateTime.hour
std.time.datetime.DateTime.hour:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.hour_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.hour_epilogue
std.time.datetime.DateTime.hour_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.hour:

.globl std.parse.index.parse_int
std.parse.index.parse_int:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.parse.index.parse_int_entry:
std.parse.index.parse_int_block_0:
  movq [rbp + -64], rcx
  call std.parse.numbers.parse_int
  movq $r1, rax
  jmp std.parse.index.parse_int_epilogue
std.parse.index.parse_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.index.parse_int:

.globl std.time.datetime.DateTime.start_of_week
std.time.datetime.DateTime.start_of_week:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.start_of_week_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.start_of_week_epilogue
std.time.datetime.DateTime.start_of_week_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.start_of_week:

.globl std.time.datetime.DateTime.is_leap_year
std.time.datetime.DateTime.is_leap_year:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.is_leap_year_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.is_leap_year_epilogue
std.time.datetime.DateTime.is_leap_year_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.is_leap_year:

.globl std.time.datetime.DateTime.days_in_month
std.time.datetime.DateTime.days_in_month:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.days_in_month_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.days_in_month_epilogue
std.time.datetime.DateTime.days_in_month_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.days_in_month:

.globl std.time.datetime.sleep_duration
std.time.datetime.sleep_duration:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.sleep_duration_entry:
std.time.datetime.sleep_duration_block_0:
  movq [rbp + -64], rcx
  call std.time.duration.TimeDuration.to_milliseconds
  movq $r1, rcx
  call std.time.datetime.sleep_ms
  movq $0, rax
  jmp std.time.datetime.sleep_duration_epilogue
std.time.datetime.sleep_duration_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.sleep_duration:

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

.globl std.time.datetime.DateTime.quarter
std.time.datetime.DateTime.quarter:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.quarter_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.quarter_epilogue
std.time.datetime.DateTime.quarter_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.quarter:

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

.globl std.time.datetime.DateTime.with_year
std.time.datetime.DateTime.with_year:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.with_year_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.with_year_epilogue
std.time.datetime.DateTime.with_year_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.with_year:

.globl std.parse.index.Parse.parse_float
std.parse.index.Parse.parse_float:
  push rbp
  mov rbp, rsp
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
std.parse.index.Parse.parse_float_entry:
  movq $0, rax
  jmp std.parse.index.Parse.parse_float_epilogue
std.parse.index.Parse.parse_float_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.index.Parse.parse_float:

.globl std.time.datetime.DateTime.format
std.time.datetime.DateTime.format:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.format_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.format_epilogue
std.time.datetime.DateTime.format_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.format:

.globl std.time.datetime.DateTime.with_month
std.time.datetime.DateTime.with_month:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.with_month_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.with_month_epilogue
std.time.datetime.DateTime.with_month_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.with_month:

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

.globl std.time.datetime.DateTime.to_iso8601
std.time.datetime.DateTime.to_iso8601:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.to_iso8601_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.to_iso8601_epilogue
std.time.datetime.DateTime.to_iso8601_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.to_iso8601:

.globl std.time.datetime.DateTime.with_day
std.time.datetime.DateTime.with_day:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.with_day_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.with_day_epilogue
std.time.datetime.DateTime.with_day_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.with_day:

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

.globl std.parse.index.Parse.parse_int
std.parse.index.Parse.parse_int:
  push rbp
  mov rbp, rsp
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
std.parse.index.Parse.parse_int_entry:
  movq $0, rax
  jmp std.parse.index.Parse.parse_int_epilogue
std.parse.index.Parse.parse_int_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.index.Parse.parse_int:

.globl std.time.datetime.sleep_seconds
std.time.datetime.sleep_seconds:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.sleep_seconds_entry:
std.time.datetime.sleep_seconds_block_0:
  movq [rbp + -64], rcx
  call sleep
  movq $0, rax
  jmp std.time.datetime.sleep_seconds_epilogue
std.time.datetime.sleep_seconds_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.sleep_seconds:

.globl std.time.datetime.DateTime.with_hour
std.time.datetime.DateTime.with_hour:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.with_hour_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.with_hour_epilogue
std.time.datetime.DateTime.with_hour_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.with_hour:

.globl std.parse.index.Parse.init
std.parse.index.Parse.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.parse.index.Parse.init_entry:
  movq $0, rax
  jmp std.parse.index.Parse.init_epilogue
std.parse.index.Parse.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.index.Parse.init:

.globl std.time.timezone.TimeZone.init
std.time.timezone.TimeZone.init:
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
std.time.timezone.TimeZone.init_entry:
  movq $0, rax
  jmp std.time.timezone.TimeZone.init_epilogue
std.time.timezone.TimeZone.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.timezone.TimeZone.init:

.globl std.time.datetime.timestamp_to_month
std.time.datetime.timestamp_to_month:
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
std.time.datetime.timestamp_to_month_entry:
std.time.datetime.timestamp_to_month_block_0:
  movq [rbp + -64], rcx
  call std.time.datetime.timestamp_to_year
  movq $r1, rcx
  movq $9, rdx
  movq $9, r8
  movq $1, r9
  call std.time.datetime.datetime_to_timestamp
  movq [rbp + -64], rax
  subq $r8, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  cmpq $1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.time.datetime.timestamp_to_month_block_14
  jmp std.time.datetime.timestamp_to_month_block_17
std.time.datetime.timestamp_to_month_block_14:
  jmp std.time.datetime.timestamp_to_month_block_14
  jmp std.time.datetime.timestamp_to_month_block_17
std.time.datetime.timestamp_to_month_block_17:
  movq $1, rax
  cqto
  movq $691201, rcx
  idivq rcx
  movq rax, [rbp + -88]
  jmp std.time.datetime.timestamp_to_month_block_22
std.time.datetime.timestamp_to_month_block_22:
  movq $9, rax
  cmpq $97, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.time.datetime.timestamp_to_month_block_25
  jmp std.time.datetime.timestamp_to_month_block_37
std.time.datetime.timestamp_to_month_block_25:
  jmp std.time.datetime.timestamp_to_month_block_25
  movq $r1, rcx
  movq $9, rdx
  call std.time.datetime.get_days_in_month
  movq [rbp + -88], rax
  cmpq $r23, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.time.datetime.timestamp_to_month_block_29
  jmp std.time.datetime.timestamp_to_month_block_30
std.time.datetime.timestamp_to_month_block_29:
  jmp std.time.datetime.timestamp_to_month_block_29
  movq $9, rax
  jmp std.time.datetime.timestamp_to_month_epilogue
std.time.datetime.timestamp_to_month_block_30:
  movq [rbp + -88], rax
  subq $r23, rax
  movq rax, [rbp + -112]
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -120]
  jmp std.time.datetime.timestamp_to_month_block_22
std.time.datetime.timestamp_to_month_block_37:
  movq $97, rax
  jmp std.time.datetime.timestamp_to_month_epilogue
std.time.datetime.timestamp_to_month_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.timestamp_to_month:

.globl std.time.datetime.DateTime.with_minute
std.time.datetime.DateTime.with_minute:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.with_minute_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.with_minute_epilogue
std.time.datetime.DateTime.with_minute_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.with_minute:

.globl std.time.datetime.DateTime.to_rfc2822
std.time.datetime.DateTime.to_rfc2822:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.to_rfc2822_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.to_rfc2822_epilogue
std.time.datetime.DateTime.to_rfc2822_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.to_rfc2822:

.globl std.time.datetime.DateTime.to_timezone
std.time.datetime.DateTime.to_timezone:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.to_timezone_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.to_timezone_epilogue
std.time.datetime.DateTime.to_timezone_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.to_timezone:

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

.globl std.time.datetime.DateTime.equals
std.time.datetime.DateTime.equals:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.equals_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.equals_epilogue
std.time.datetime.DateTime.equals_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.equals:

.globl std.time.datetime.DateTime.less_than
std.time.datetime.DateTime.less_than:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.less_than_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.less_than_epilogue
std.time.datetime.DateTime.less_than_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.less_than:

.globl std.time.datetime.DateTime.to_date_string
std.time.datetime.DateTime.to_date_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.to_date_string_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.to_date_string_epilogue
std.time.datetime.DateTime.to_date_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.to_date_string:

.globl std.time.duration.TimeDuration.equals
std.time.duration.TimeDuration.equals:
  push rbp
  mov rbp, rsp
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
std.time.duration.TimeDuration.equals_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.equals_epilogue
std.time.duration.TimeDuration.equals_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.equals:

.globl std.time.datetime.DateTime.to_time_string
std.time.datetime.DateTime.to_time_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.to_time_string_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.to_time_string_epilogue
std.time.datetime.DateTime.to_time_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.to_time_string:

.globl std.time.datetime.DateTime.is_weekend
std.time.datetime.DateTime.is_weekend:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.is_weekend_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.is_weekend_epilogue
std.time.datetime.DateTime.is_weekend_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.is_weekend:

.globl std.time.datetime.DateTime.init
std.time.datetime.DateTime.init:
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
std.time.datetime.DateTime.init_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.init_epilogue
std.time.datetime.DateTime.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.init:

.globl std.time.datetime.DateTime.is_weekday
std.time.datetime.DateTime.is_weekday:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.is_weekday_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.is_weekday_epilogue
std.time.datetime.DateTime.is_weekday_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.is_weekday:

.globl std.parse.index.Parse.parse_bool
std.parse.index.Parse.parse_bool:
  push rbp
  mov rbp, rsp
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
std.parse.index.Parse.parse_bool_entry:
  movq $0, rax
  jmp std.parse.index.Parse.parse_bool_epilogue
std.parse.index.Parse.parse_bool_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.parse.index.Parse.parse_bool:

.globl std.time.datetime.DateTime.start_of_day
std.time.datetime.DateTime.start_of_day:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.start_of_day_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.start_of_day_epilogue
std.time.datetime.DateTime.start_of_day_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.start_of_day:

.globl std.time.datetime.DateTime.start_of_month
std.time.datetime.DateTime.start_of_month:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.start_of_month_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.start_of_month_epilogue
std.time.datetime.DateTime.start_of_month_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.start_of_month:

.globl std.time.datetime.DateTime.end_of_month
std.time.datetime.DateTime.end_of_month:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.end_of_month_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.end_of_month_epilogue
std.time.datetime.DateTime.end_of_month_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.end_of_month:

.globl std.time.duration.TimeDuration.from_milliseconds
std.time.duration.TimeDuration.from_milliseconds:
  push rbp
  mov rbp, rsp
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
std.time.duration.TimeDuration.from_milliseconds_entry:
  movq $0, rax
  jmp std.time.duration.TimeDuration.from_milliseconds_epilogue
std.time.duration.TimeDuration.from_milliseconds_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.duration.TimeDuration.from_milliseconds:

.globl std.time.datetime.DateTime.start_of_quarter
std.time.datetime.DateTime.start_of_quarter:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.time.datetime.DateTime.start_of_quarter_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.start_of_quarter_epilogue
std.time.datetime.DateTime.start_of_quarter_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.start_of_quarter:

.globl std.time.datetime.DateTime.age
std.time.datetime.DateTime.age:
  push rbp
  mov rbp, rsp
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
std.time.datetime.DateTime.age_entry:
  movq $0, rax
  jmp std.time.datetime.DateTime.age_epilogue
std.time.datetime.DateTime.age_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.DateTime.age:

.globl std.time.datetime.sleep_ms
std.time.datetime.sleep_ms:
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
std.time.datetime.sleep_ms_entry:
std.time.datetime.sleep_ms_block_0:
  movq [rbp + -64], rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  cqto
  movq $2, rcx
  idivq rcx
  movq rax, [rbp + -80]
  movq [rbp + -80], rcx
  call sleep
  movq $0, rax
  jmp std.time.datetime.sleep_ms_epilogue
std.time.datetime.sleep_ms_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.time.datetime.sleep_ms:

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

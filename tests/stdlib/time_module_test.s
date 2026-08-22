.section .rodata
.Lproc_environ:
  .string "/proc/self/environ"
.Lproc_cmdline:
  .string "/proc/self/cmdline"
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
str_hdr_0:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 19
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 19
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 84
  .byte 101
  .byte 115
  .byte 116
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 68
  .byte 117
  .byte 114
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 46
  .byte 46
  .byte 46
  .byte 0
.align 8
str_nil:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 3
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 3
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 110
  .byte 105
  .byte 108
  .byte 0
.align 8
nl:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 1
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 1
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 10
  .byte 0
.align 8
str_hdr_1:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 19
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 19
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 100
  .byte 117
  .byte 114
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 97
  .byte 100
  .byte 100
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
std_time_duration_TimeDuration:
  .quad 0
.align 8
str_hdr_3:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 19
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 19
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 102
  .byte 114
  .byte 111
  .byte 109
  .byte 95
  .byte 115
  .byte 101
  .byte 99
  .byte 111
  .byte 110
  .byte 100
  .byte 115
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_5:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 30
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 30
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 61
  .byte 61
  .byte 61
  .byte 32
  .byte 84
  .byte 105
  .byte 109
  .byte 101
  .byte 32
  .byte 77
  .byte 111
  .byte 100
  .byte 117
  .byte 108
  .byte 101
  .byte 32
  .byte 84
  .byte 101
  .byte 115
  .byte 116
  .byte 32
  .byte 83
  .byte 117
  .byte 105
  .byte 116
  .byte 101
  .byte 32
  .byte 61
  .byte 61
  .byte 61
  .byte 0
.align 8
str_hdr_6:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 20
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 20
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 68
  .byte 117
  .byte 114
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_8:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 20
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 20
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 84
  .byte 105
  .byte 109
  .byte 101
  .byte 90
  .byte 111
  .byte 110
  .byte 101
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_10:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 16
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 16
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 84
  .byte 105
  .byte 109
  .byte 101
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_12:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 29
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 29
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 73
  .byte 110
  .byte 115
  .byte 116
  .byte 97
  .byte 110
  .byte 116
  .byte 32
  .byte 97
  .byte 110
  .byte 100
  .byte 32
  .byte 84
  .byte 105
  .byte 109
  .byte 101
  .byte 114
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_14:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 35
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 35
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 65
  .byte 108
  .byte 108
  .byte 32
  .byte 116
  .byte 105
  .byte 109
  .byte 101
  .byte 32
  .byte 116
  .byte 101
  .byte 115
  .byte 116
  .byte 115
  .byte 32
  .byte 112
  .byte 97
  .byte 115
  .byte 115
  .byte 101
  .byte 100
  .byte 32
  .byte 115
  .byte 117
  .byte 99
  .byte 99
  .byte 101
  .byte 115
  .byte 115
  .byte 102
  .byte 117
  .byte 108
  .byte 108
  .byte 121
  .byte 46
  .byte 0
.align 8
str_hdr_15:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 15
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 15
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 84
  .byte 101
  .byte 115
  .byte 116
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 84
  .byte 105
  .byte 109
  .byte 101
  .byte 46
  .byte 46
  .byte 46
  .byte 0
.align 8
str_hdr_16:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 3
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 3
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 85
  .byte 84
  .byte 67
  .byte 0
.align 8
str_hdr_17:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 16
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 16
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 116
  .byte 105
  .byte 109
  .byte 101
  .byte 115
  .byte 116
  .byte 97
  .byte 109
  .byte 112
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_19:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 121
  .byte 101
  .byte 97
  .byte 114
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_21:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 12
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 12
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 109
  .byte 111
  .byte 110
  .byte 116
  .byte 104
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_23:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 10
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 10
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 100
  .byte 97
  .byte 121
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_25:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 19
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 19
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 84
  .byte 101
  .byte 115
  .byte 116
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 84
  .byte 105
  .byte 109
  .byte 101
  .byte 90
  .byte 111
  .byte 110
  .byte 101
  .byte 46
  .byte 46
  .byte 46
  .byte 0
.align 8
str_hdr_26:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 3
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 3
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 85
  .byte 84
  .byte 67
  .byte 0
.align 8
str_hdr_27:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 3
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 3
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 85
  .byte 84
  .byte 67
  .byte 0
.align 8
str_hdr_28:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 20
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 20
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 116
  .byte 105
  .byte 109
  .byte 101
  .byte 122
  .byte 111
  .byte 110
  .byte 101
  .byte 32
  .byte 110
  .byte 97
  .byte 109
  .byte 101
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_30:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 6
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 6
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 43
  .byte 48
  .byte 48
  .byte 58
  .byte 48
  .byte 48
  .byte 0
.align 8
str_hdr_31:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 22
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 22
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 116
  .byte 105
  .byte 109
  .byte 101
  .byte 122
  .byte 111
  .byte 110
  .byte 101
  .byte 32
  .byte 111
  .byte 102
  .byte 102
  .byte 115
  .byte 101
  .byte 116
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_33:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 28
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 28
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 84
  .byte 101
  .byte 115
  .byte 116
  .byte 105
  .byte 110
  .byte 103
  .byte 32
  .byte 73
  .byte 110
  .byte 115
  .byte 116
  .byte 97
  .byte 110
  .byte 116
  .byte 32
  .byte 97
  .byte 110
  .byte 100
  .byte 32
  .byte 84
  .byte 105
  .byte 109
  .byte 101
  .byte 114
  .byte 46
  .byte 46
  .byte 46
  .byte 0
.align 8
str_hdr_34:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 22
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 22
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 105
  .byte 110
  .byte 115
  .byte 116
  .byte 97
  .byte 110
  .byte 116
  .byte 32
  .byte 101
  .byte 108
  .byte 97
  .byte 112
  .byte 115
  .byte 101
  .byte 100
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_36:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 20
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 20
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 116
  .byte 105
  .byte 109
  .byte 101
  .byte 114
  .byte 32
  .byte 101
  .byte 108
  .byte 97
  .byte 112
  .byte 115
  .byte 101
  .byte 100
  .byte 32
  .byte 102
  .byte 97
  .byte 105
  .byte 108
  .byte 101
  .byte 100
  .byte 0
.align 8
str_hdr_38:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 2
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 2
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 37
  .byte 115
  .byte 0
.align 8
str_hdr_39:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 1
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 1
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 48
  .byte 0
.align 8
fmt_float:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 2
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 2
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 37
  .byte 103
  .byte 0
.align 8
list_lbracket:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 1
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 1
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 91
  .byte 0
.align 8
list_comma:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 2
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 2
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 44
  .byte 32
  .byte 0
.align 8
list_rbracket:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 1
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 1
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 93
  .byte 0
.text
.globl main
.globl _start
_start:
  call main
  movq %rax, %rdi
  movq $60, %rax
  syscall

.globl main
main:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $280, %rsp
main_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -48(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  jmp main_block_0
main_block_0:
  call std.time.duration.__init__
  mov -224(%rbp), rax
  movq -224(%rbp), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  call std.time.timezone.__init__
  mov -232(%rbp), rax
  movq -232(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  call std.time.datetime.__init__
  mov -240(%rbp), rax
  movq -240(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  call std.time.instant.__init__
  mov -248(%rbp), rax
  movq -248(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  call std.time.timer.__init__
  mov -256(%rbp), rax
  movq -256(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  call std.time.duration.__init__
  mov -264(%rbp), rax
  movq -264(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  call std.time.timezone.__init__
  mov -272(%rbp), rax
  movq -272(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  call std.time.datetime.__init__
  mov -280(%rbp), rax
  movq -280(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  call std.time.instant.__init__
  mov -288(%rbp), rax
  movq -288(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  call std.time.timer.__init__
  mov -296(%rbp), rax
  movq -296(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  call __user_main
  mov -304(%rbp), rax
  movq -304(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp main_epilogue
main_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_main:

.globl std.time.duration.__init__
std.time.duration.__init__:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
std.time.duration.__init___entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -48(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.__init___epilogue
std.time.duration.__init___epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.__init__:

.globl std.time.duration.TimeDuration.init
std.time.duration.TimeDuration.init:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
  movq %rdx, -64(%rbp)
std.time.duration.TimeDuration.init_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.init_epilogue
std.time.duration.TimeDuration.init_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.init:

.globl std.time.duration.TimeDuration.human_readable
std.time.duration.TimeDuration.human_readable:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.duration.TimeDuration.human_readable_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.human_readable_epilogue
std.time.duration.TimeDuration.human_readable_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.human_readable:

.globl std.time.datetime.DateTime.is_leap_year
std.time.datetime.DateTime.is_leap_year:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.is_leap_year_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.is_leap_year_epilogue
std.time.datetime.DateTime.is_leap_year_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.is_leap_year:

.globl std.time.datetime.DateTime.day_of_week
std.time.datetime.DateTime.day_of_week:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.day_of_week_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.day_of_week_epilogue
std.time.datetime.DateTime.day_of_week_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.day_of_week:

.globl std.time.datetime.get_days_in_month
std.time.datetime.get_days_in_month:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $840, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.get_days_in_month_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -272(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -280(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -288(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -296(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -304(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -312(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -320(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -328(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -336(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -344(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -352(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -360(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -368(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -376(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -384(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -392(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -400(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -408(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -416(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -424(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.get_days_in_month_block_0
std.time.datetime.get_days_in_month_block_0:
  movq $0, %rdi
  call lm_list_new
  mov -432(%rbp), rax
  movq -432(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq $31, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -440(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -440(%rbp), %rdi
  movq -448(%rbp), %rsi
  call lm_list_append
  mov -456(%rbp), rax
  movq $28, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -464(%rbp), %rdi
  movq -472(%rbp), %rsi
  call lm_list_append
  mov -480(%rbp), rax
  movq $31, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -488(%rbp), %rdi
  movq -496(%rbp), %rsi
  call lm_list_append
  mov -504(%rbp), rax
  movq $30, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -512(%rbp), %rdi
  movq -520(%rbp), %rsi
  call lm_list_append
  mov -528(%rbp), rax
  movq $31, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -536(%rbp), %rdi
  movq -544(%rbp), %rsi
  call lm_list_append
  mov -552(%rbp), rax
  movq $30, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -560(%rbp), %rdi
  movq -568(%rbp), %rsi
  call lm_list_append
  mov -576(%rbp), rax
  movq $31, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -584(%rbp), %rdi
  movq -592(%rbp), %rsi
  call lm_list_append
  mov -600(%rbp), rax
  movq $31, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -608(%rbp), %rdi
  movq -616(%rbp), %rsi
  call lm_list_append
  mov -624(%rbp), rax
  movq $30, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -632(%rbp), %rdi
  movq -640(%rbp), %rsi
  call lm_list_append
  mov -648(%rbp), rax
  movq $31, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -656(%rbp), %rdi
  movq -664(%rbp), %rsi
  call lm_list_append
  mov -672(%rbp), rax
  movq $30, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -680(%rbp), %rdi
  movq -688(%rbp), %rsi
  call lm_list_append
  mov -696(%rbp), rax
  movq $31, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -712(%rbp)
  movq -704(%rbp), %rdi
  movq -712(%rbp), %rsi
  call lm_list_append
  mov -720(%rbp), rax
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -728(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq $2, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -744(%rbp), %rax
  cmpq -736(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -752(%rbp)
  movq -752(%rbp), %rax
  movq -304(%rbp), %rdx
  movl %eax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -760(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -768(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.get_days_in_month_block_30
  jmp std.time.datetime.get_days_in_month_block_33
std.time.datetime.get_days_in_month_block_30:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -776(%rbp), %rdi
  call std.time.datetime.is_leap_year
  mov -784(%rbp), rax
  movq -784(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -792(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.get_days_in_month_block_33
std.time.datetime.get_days_in_month_block_33:
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -800(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.get_days_in_month_block_34
  jmp std.time.datetime.get_days_in_month_block_36
std.time.datetime.get_days_in_month_block_34:
  movq $29, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -808(%rbp), %rax
  jmp std.time.datetime.get_days_in_month_epilogue
std.time.datetime.get_days_in_month_block_36:
  movq $1, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -824(%rbp), %rax
  subq -816(%rbp), %rax
  movq %rax, -832(%rbp)
  movq -832(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -840(%rbp), %rdi
  movq -848(%rbp), %rsi
  call lm_list_get
  mov -856(%rbp), rax
  movq -856(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -864(%rbp), %rax
  jmp std.time.datetime.get_days_in_month_epilogue
std.time.datetime.get_days_in_month_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.get_days_in_month:

.globl std.time.datetime.DateTime.minute
std.time.datetime.DateTime.minute:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.minute_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.minute_epilogue
std.time.datetime.DateTime.minute_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.minute:

.globl std.time.duration.TimeDuration.from_minutes
std.time.duration.TimeDuration.from_minutes:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.duration.TimeDuration.from_minutes_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.from_minutes_epilogue
std.time.duration.TimeDuration.from_minutes_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.from_minutes:

.globl std.time.datetime.DateTime.day
std.time.datetime.DateTime.day:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.day_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.day_epilogue
std.time.datetime.DateTime.day_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.day:

.globl std.time.datetime.__init__
std.time.datetime.__init__:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
std.time.datetime.__init___entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -48(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.__init___epilogue
std.time.datetime.__init___epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.__init__:

.globl std.time.datetime.DateTime.difference
std.time.datetime.DateTime.difference:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.difference_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.difference_epilogue
std.time.datetime.DateTime.difference_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.difference:

.globl std.time.datetime.DateTime.now
std.time.datetime.DateTime.now:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.now_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.now_epilogue
std.time.datetime.DateTime.now_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.now:

.globl std.time.datetime.DateTime.with_timezone
std.time.datetime.DateTime.with_timezone:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.with_timezone_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.with_timezone_epilogue
std.time.datetime.DateTime.with_timezone_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.with_timezone:

.globl std.time.datetime.DateTime.from_timestamp
std.time.datetime.DateTime.from_timestamp:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.from_timestamp_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.from_timestamp_epilogue
std.time.datetime.DateTime.from_timestamp_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.from_timestamp:

.globl std.time.datetime.DateTime.to_string
std.time.datetime.DateTime.to_string:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.to_string_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.to_string_epilogue
std.time.datetime.DateTime.to_string_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.to_string:

.globl std.time.datetime.DateTime.subtract
std.time.datetime.DateTime.subtract:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.subtract_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.subtract_epilogue
std.time.datetime.DateTime.subtract_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.subtract:

.globl std.time.datetime.to_i
std.time.datetime.to_i:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $136, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.to_i_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.to_i_block_0
std.time.datetime.to_i_block_0:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -152(%rbp)
  movq -152(%rbp), %rax
  movq %rax, -160(%rbp)
  movq -160(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -168(%rbp), %rax
  jmp std.time.datetime.to_i_epilogue
std.time.datetime.to_i_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.to_i:

.globl std.time.datetime.DateTime.from_components
std.time.datetime.DateTime.from_components:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $152, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
  movq %rdx, -64(%rbp)
  movq %rcx, -72(%rbp)
  movq %r8, -80(%rbp)
  movq %r9, -88(%rbp)
std.time.datetime.DateTime.from_components_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.from_components_epilogue
std.time.datetime.DateTime.from_components_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.from_components:

.globl test_duration
test_duration:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $856, %rsp
test_duration_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -48(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -272(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -280(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -288(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -296(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -304(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -312(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -320(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -328(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -336(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -344(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -352(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -360(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -368(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -376(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -384(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_duration_block_0
test_duration_block_0:
  leaq str_hdr_0(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -392(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -400(%rbp)
  movq -400(%rbp), %rax
  testq %rax, %rax
  jne test_duration_pr_nil_0_9383
  jmp test_duration_pr_str_0_9383
test_duration_pr_nil_0_9383:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -408(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -408(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -416(%rbp)
  jmp test_duration_pr_next_0_9383
test_duration_pr_str_0_9383:
  movq -392(%rbp), %rax
  addq $8, %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -392(%rbp), %rax
  addq $24, %rax
  movq %rax, -440(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -440(%rbp), %rsi
  movq -432(%rbp), %rdx
  syscall
  movq %rax, -448(%rbp)
  jmp test_duration_pr_next_0_9383
test_duration_pr_next_0_9383:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -456(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -456(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -464(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $10, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 16 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -472(%rbp)
  addq $16, %rax
  movq %rax, heap_ptr(%rip)
  movq -472(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -480(%rbp), %rdi
  movq -488(%rbp), %rsi
  movq -496(%rbp), %rdx
  call std.time.duration.TimeDuration.init
  mov -504(%rbp), rax
  movq -504(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq $20, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 16 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -528(%rbp)
  addq $16, %rax
  movq %rax, heap_ptr(%rip)
  movq -528(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -536(%rbp), %rdi
  movq -544(%rbp), %rsi
  movq -552(%rbp), %rdx
  call std.time.duration.TimeDuration.init
  mov -560(%rbp), rax
  movq -560(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -576(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -584(%rbp), %rdi
  movq -592(%rbp), %rsi
  call std.time.duration.TimeDuration.add
  mov -600(%rbp), rax
  movq -600(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -624(%rbp), %rax
  addq $8, %rax
  movq %rax, -632(%rbp)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -640(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq $30, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rax
  cmpq -648(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  movq -200(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_1(%rip), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -672(%rbp), %rax
  testq %rax, %rax
  jne test_duration_assert_pass_2
  jmp test_duration_assert_fail_2
test_duration_assert_pass_2:
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq std_time_duration_TimeDuration(%rip), %rax
  movq %rax, -688(%rbp)
  movq -688(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq $5, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -696(%rbp), %rdi
  movq -704(%rbp), %rsi
  call std.time.duration.TimeDuration.from_seconds
  mov -712(%rbp), rax
  movq -712(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -720(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -728(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -736(%rbp), %rax
  addq $8, %rax
  movq %rax, -744(%rbp)
  movq -744(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -752(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq $5, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -760(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -768(%rbp), %rax
  cmpq -760(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -776(%rbp)
  movq -776(%rbp), %rax
  movq -280(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_3(%rip), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -784(%rbp)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -784(%rbp), %rax
  testq %rax, %rax
  jne test_duration_assert_pass_4
  jmp test_duration_assert_fail_4
test_duration_assert_fail_2:
  movq -680(%rbp), %rax
  addq $8, %rax
  movq %rax, -800(%rbp)
  movq -800(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -680(%rbp), %rax
  addq $24, %rax
  movq %rax, -816(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -816(%rbp), %rsi
  movq -808(%rbp), %rdx
  syscall
  movq %rax, -824(%rbp)
  movq $50397203, %rax
  movq %rax, -832(%rbp)
  jmp test_duration_assert_pass_2
test_duration_assert_pass_4:
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -840(%rbp), %rax
  jmp test_duration_epilogue
test_duration_assert_fail_4:
  movq -792(%rbp), %rax
  addq $8, %rax
  movq %rax, -848(%rbp)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -856(%rbp)
  movq -792(%rbp), %rax
  addq $24, %rax
  movq %rax, -864(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -864(%rbp), %rsi
  movq -856(%rbp), %rdx
  syscall
  movq %rax, -872(%rbp)
  movq $50397203, %rax
  movq %rax, -880(%rbp)
  jmp test_duration_assert_pass_4
test_duration_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_test_duration:

.globl std.time.duration.TimeDuration.from_hours
std.time.duration.TimeDuration.from_hours:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.duration.TimeDuration.from_hours_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.from_hours_epilogue
std.time.duration.TimeDuration.from_hours_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.from_hours:

.globl std.time.datetime.DateTime.hour
std.time.datetime.DateTime.hour:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.hour_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.hour_epilogue
std.time.datetime.DateTime.hour_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.hour:

.globl std.time.datetime.DateTime.day_of_year
std.time.datetime.DateTime.day_of_year:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.day_of_year_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.day_of_year_epilogue
std.time.datetime.DateTime.day_of_year_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.day_of_year:

.globl std.time.duration.TimeDuration.from_days
std.time.duration.TimeDuration.from_days:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.duration.TimeDuration.from_days_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.from_days_epilogue
std.time.duration.TimeDuration.from_days_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.from_days:

.globl std.time.datetime.DateTime.second
std.time.datetime.DateTime.second:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.second_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.second_epilogue
std.time.datetime.DateTime.second_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.second:

.globl std.time.datetime.DateTime.add
std.time.datetime.DateTime.add:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.add_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.add_epilogue
std.time.datetime.DateTime.add_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.add:

.globl std.time.datetime.is_leap_year
std.time.datetime.is_leap_year:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $440, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.is_leap_year_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.is_leap_year_block_0
std.time.datetime.is_leap_year_block_0:
  movq $4, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -272(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -280(%rbp)
  movq -280(%rbp), %rax
  cqto
  movq -272(%rbp), %rcx
  idivq %rcx
  movq %rdx, -288(%rbp)
  movq -288(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -296(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -304(%rbp)
  movq -304(%rbp), %rax
  cmpq -296(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -312(%rbp)
  movq -312(%rbp), %rax
  movq -88(%rbp), %rdx
  movl %eax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.is_leap_year_block_5
  jmp std.time.datetime.is_leap_year_block_7
std.time.datetime.is_leap_year_block_5:
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rax
  jmp std.time.datetime.is_leap_year_epilogue
std.time.datetime.is_leap_year_block_7:
  movq $100, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -344(%rbp)
  movq -344(%rbp), %rax
  cqto
  movq -336(%rbp), %rcx
  idivq %rcx
  movq %rdx, -352(%rbp)
  movq -352(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -360(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rax
  cmpq -360(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -376(%rbp)
  movq -376(%rbp), %rax
  movq -128(%rbp), %rdx
  movl %eax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -384(%rbp)
  movq -384(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.is_leap_year_block_12
  jmp std.time.datetime.is_leap_year_block_14
std.time.datetime.is_leap_year_block_12:
  movq $1, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -392(%rbp), %rax
  jmp std.time.datetime.is_leap_year_epilogue
std.time.datetime.is_leap_year_block_14:
  movq $400, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -408(%rbp), %rax
  cqto
  movq -400(%rbp), %rcx
  idivq %rcx
  movq %rdx, -416(%rbp)
  movq -416(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  cmpq -424(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -440(%rbp)
  movq -440(%rbp), %rax
  movq -168(%rbp), %rdx
  movl %eax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.is_leap_year_block_19
  jmp std.time.datetime.is_leap_year_block_21
std.time.datetime.is_leap_year_block_19:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rax
  jmp std.time.datetime.is_leap_year_epilogue
std.time.datetime.is_leap_year_block_21:
  movq $1, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -464(%rbp), %rax
  jmp std.time.datetime.is_leap_year_epilogue
std.time.datetime.is_leap_year_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.is_leap_year:

.globl std.time.datetime.DateTime.month
std.time.datetime.DateTime.month:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.month_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.month_epilogue
std.time.datetime.DateTime.month_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.month:

.globl std.time.duration.TimeDuration.greater_than
std.time.duration.TimeDuration.greater_than:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.duration.TimeDuration.greater_than_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.greater_than_epilogue
std.time.duration.TimeDuration.greater_than_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.greater_than:

.globl std.time.duration.TimeDuration.to_milliseconds
std.time.duration.TimeDuration.to_milliseconds:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.duration.TimeDuration.to_milliseconds_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.to_milliseconds_epilogue
std.time.duration.TimeDuration.to_milliseconds_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.to_milliseconds:

.globl std.time.datetime.datetime_to_timestamp
std.time.datetime.datetime_to_timestamp:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $1896, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
  movq %rdx, -64(%rbp)
  movq %rcx, -72(%rbp)
  movq %r8, -80(%rbp)
  movq %r9, -88(%rbp)
std.time.datetime.datetime_to_timestamp_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -272(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -280(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -288(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -296(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -304(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -312(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -320(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -328(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -336(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -344(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -352(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -360(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -368(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -376(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -384(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -392(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -400(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -408(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -416(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -424(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -432(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -440(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -448(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -456(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -464(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -472(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -480(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -488(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -496(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -504(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -512(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -520(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -528(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -536(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -544(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -552(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -560(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -568(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -576(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -584(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -592(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -600(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -608(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -616(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -624(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -632(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -640(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -648(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -656(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -664(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -672(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -680(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -688(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -696(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -704(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -712(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -720(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -728(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -736(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -736(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -744(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -744(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -752(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -752(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -760(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -760(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -768(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -768(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -776(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -776(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -784(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -784(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -792(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -800(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -800(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -808(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -808(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.datetime_to_timestamp_block_0
std.time.datetime.datetime_to_timestamp_block_0:
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1970, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.datetime_to_timestamp_block_3
std.time.datetime.datetime_to_timestamp_block_3:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -824(%rbp), %rax
  cmpq -816(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -832(%rbp)
  movq -832(%rbp), %rax
  movq -160(%rbp), %rdx
  movl %eax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -840(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.datetime_to_timestamp_block_5
  jmp std.time.datetime.datetime_to_timestamp_block_14
std.time.datetime.datetime_to_timestamp_block_5:
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -848(%rbp), %rdi
  call std.time.datetime.get_days_in_year
  mov -856(%rbp), rax
  movq -856(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -864(%rbp), %rdi
  call std.time.datetime.get_days_in_year
  mov -872(%rbp), rax
  movq -872(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -888(%rbp)
  movq -888(%rbp), %rax
  addq -880(%rbp), %rax
  movq %rax, -896(%rbp)
  movq -896(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -904(%rbp)
  movq -904(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -912(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -920(%rbp)
  movq -920(%rbp), %rax
  addq -912(%rbp), %rax
  movq %rax, -928(%rbp)
  movq -928(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -936(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.datetime_to_timestamp_block_3
std.time.datetime.datetime_to_timestamp_block_14:
  jmp std.time.datetime.datetime_to_timestamp_block_15
std.time.datetime.datetime_to_timestamp_block_15:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -944(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -952(%rbp)
  movq -952(%rbp), %rax
  cmpq -944(%rbp), %rax
  setg %al
  movzbq %al, %rax
  movq %rax, -960(%rbp)
  movq -960(%rbp), %rax
  movq -216(%rbp), %rdx
  movl %eax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -968(%rbp)
  movq -968(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.datetime_to_timestamp_block_17
  jmp std.time.datetime.datetime_to_timestamp_block_24
std.time.datetime.datetime_to_timestamp_block_17:
  movq $1, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -984(%rbp)
  movq -984(%rbp), %rax
  subq -976(%rbp), %rax
  movq %rax, -992(%rbp)
  movq -992(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1000(%rbp)
  movq -1000(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1008(%rbp)
  movq -1008(%rbp), %rdi
  call std.time.datetime.get_days_in_year
  mov -1016(%rbp), rax
  movq -1016(%rbp), %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1024(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1032(%rbp)
  movq -1032(%rbp), %rax
  subq -1024(%rbp), %rax
  movq %rax, -1040(%rbp)
  movq -1040(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1048(%rbp)
  movq -1048(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.datetime_to_timestamp_block_15
std.time.datetime.datetime_to_timestamp_block_24:
  movq $1, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.datetime_to_timestamp_block_26
std.time.datetime.datetime_to_timestamp_block_26:
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1056(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1064(%rbp)
  movq -1064(%rbp), %rax
  cmpq -1056(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -1072(%rbp)
  movq -1072(%rbp), %rax
  movq -264(%rbp), %rdx
  movl %eax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1080(%rbp)
  movq -1080(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.datetime_to_timestamp_block_28
  jmp std.time.datetime.datetime_to_timestamp_block_37
std.time.datetime.datetime_to_timestamp_block_28:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1088(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1096(%rbp)
  movq -1088(%rbp), %rdi
  movq -1096(%rbp), %rsi
  call std.time.datetime.get_days_in_month
  mov -1104(%rbp), rax
  movq -1104(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1112(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1120(%rbp)
  movq -1112(%rbp), %rdi
  movq -1120(%rbp), %rsi
  call std.time.datetime.get_days_in_month
  mov -1128(%rbp), rax
  movq -1128(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1136(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1144(%rbp)
  movq -1144(%rbp), %rax
  addq -1136(%rbp), %rax
  movq %rax, -1152(%rbp)
  movq -1152(%rbp), %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1160(%rbp)
  movq -1160(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1168(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1176(%rbp)
  movq -1176(%rbp), %rax
  addq -1168(%rbp), %rax
  movq %rax, -1184(%rbp)
  movq -1184(%rbp), %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1192(%rbp)
  movq -1192(%rbp), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.datetime_to_timestamp_block_26
std.time.datetime.datetime_to_timestamp_block_37:
  movq $1, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1200(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1208(%rbp)
  movq -1208(%rbp), %rax
  subq -1200(%rbp), %rax
  movq %rax, -1216(%rbp)
  movq -1216(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1224(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1232(%rbp)
  movq -1232(%rbp), %rax
  subq -1224(%rbp), %rax
  movq %rax, -1240(%rbp)
  movq -1240(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1248(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1256(%rbp)
  movq -1256(%rbp), %rax
  addq -1248(%rbp), %rax
  movq %rax, -1264(%rbp)
  movq -1264(%rbp), %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1272(%rbp)
  movq -1272(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $86400, %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1280(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1288(%rbp)
  movq -1288(%rbp), %rax
  imulq -1280(%rbp), %rax
  movq %rax, -1296(%rbp)
  movq -1296(%rbp), %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3600, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -376(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1304(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1312(%rbp)
  movq -1312(%rbp), %rax
  imulq -1304(%rbp), %rax
  movq %rax, -1320(%rbp)
  movq -1320(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq $86400, %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1328(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1336(%rbp)
  movq -1336(%rbp), %rax
  imulq -1328(%rbp), %rax
  movq %rax, -1344(%rbp)
  movq -1344(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3600, %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -408(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1352(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1360(%rbp)
  movq -1360(%rbp), %rax
  imulq -1352(%rbp), %rax
  movq %rax, -1368(%rbp)
  movq -1368(%rbp), %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1376(%rbp)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1384(%rbp)
  movq -1384(%rbp), %rax
  addq -1376(%rbp), %rax
  movq %rax, -1392(%rbp)
  movq -1392(%rbp), %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  movq $60, %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1400(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1408(%rbp)
  movq -1408(%rbp), %rax
  imulq -1400(%rbp), %rax
  movq %rax, -1416(%rbp)
  movq -1416(%rbp), %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq $86400, %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1424(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1432(%rbp)
  movq -1432(%rbp), %rax
  imulq -1424(%rbp), %rax
  movq %rax, -1440(%rbp)
  movq -1440(%rbp), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3600, %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1448(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1456(%rbp)
  movq -1456(%rbp), %rax
  imulq -1448(%rbp), %rax
  movq %rax, -1464(%rbp)
  movq -1464(%rbp), %rax
  movq -472(%rbp), %rdx
  movq %rax, (%rdx)
  movq $86400, %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1472(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1480(%rbp)
  movq -1480(%rbp), %rax
  imulq -1472(%rbp), %rax
  movq %rax, -1488(%rbp)
  movq -1488(%rbp), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3600, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1496(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1504(%rbp)
  movq -1504(%rbp), %rax
  imulq -1496(%rbp), %rax
  movq %rax, -1512(%rbp)
  movq -1512(%rbp), %rax
  movq -504(%rbp), %rdx
  movq %rax, (%rdx)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1520(%rbp)
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1528(%rbp)
  movq -1528(%rbp), %rax
  addq -1520(%rbp), %rax
  movq %rax, -1536(%rbp)
  movq -1536(%rbp), %rax
  movq -512(%rbp), %rdx
  movq %rax, (%rdx)
  movq $60, %rax
  movq -520(%rbp), %rdx
  movq %rax, (%rdx)
  movq -520(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1544(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1552(%rbp)
  movq -1552(%rbp), %rax
  imulq -1544(%rbp), %rax
  movq %rax, -1560(%rbp)
  movq -1560(%rbp), %rax
  movq -528(%rbp), %rdx
  movq %rax, (%rdx)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1568(%rbp)
  movq -512(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1576(%rbp)
  movq -1576(%rbp), %rax
  addq -1568(%rbp), %rax
  movq %rax, -1584(%rbp)
  movq -1584(%rbp), %rax
  movq -536(%rbp), %rdx
  movq %rax, (%rdx)
  movq $86400, %rax
  movq -544(%rbp), %rdx
  movq %rax, (%rdx)
  movq -544(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1592(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1600(%rbp)
  movq -1600(%rbp), %rax
  imulq -1592(%rbp), %rax
  movq %rax, -1608(%rbp)
  movq -1608(%rbp), %rax
  movq -552(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3600, %rax
  movq -560(%rbp), %rdx
  movq %rax, (%rdx)
  movq -560(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1616(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1624(%rbp)
  movq -1624(%rbp), %rax
  imulq -1616(%rbp), %rax
  movq %rax, -1632(%rbp)
  movq -1632(%rbp), %rax
  movq -568(%rbp), %rdx
  movq %rax, (%rdx)
  movq $86400, %rax
  movq -576(%rbp), %rdx
  movq %rax, (%rdx)
  movq -576(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1640(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1648(%rbp)
  movq -1648(%rbp), %rax
  imulq -1640(%rbp), %rax
  movq %rax, -1656(%rbp)
  movq -1656(%rbp), %rax
  movq -584(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3600, %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1664(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1672(%rbp)
  movq -1672(%rbp), %rax
  imulq -1664(%rbp), %rax
  movq %rax, -1680(%rbp)
  movq -1680(%rbp), %rax
  movq -600(%rbp), %rdx
  movq %rax, (%rdx)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1688(%rbp)
  movq -584(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1696(%rbp)
  movq -1696(%rbp), %rax
  addq -1688(%rbp), %rax
  movq %rax, -1704(%rbp)
  movq -1704(%rbp), %rax
  movq -608(%rbp), %rdx
  movq %rax, (%rdx)
  movq $60, %rax
  movq -616(%rbp), %rdx
  movq %rax, (%rdx)
  movq -616(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1712(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1720(%rbp)
  movq -1720(%rbp), %rax
  imulq -1712(%rbp), %rax
  movq %rax, -1728(%rbp)
  movq -1728(%rbp), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq $86400, %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -632(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1736(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1744(%rbp)
  movq -1744(%rbp), %rax
  imulq -1736(%rbp), %rax
  movq %rax, -1752(%rbp)
  movq -1752(%rbp), %rax
  movq -640(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3600, %rax
  movq -648(%rbp), %rdx
  movq %rax, (%rdx)
  movq -648(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1760(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1768(%rbp)
  movq -1768(%rbp), %rax
  imulq -1760(%rbp), %rax
  movq %rax, -1776(%rbp)
  movq -1776(%rbp), %rax
  movq -656(%rbp), %rdx
  movq %rax, (%rdx)
  movq $86400, %rax
  movq -664(%rbp), %rdx
  movq %rax, (%rdx)
  movq -664(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1784(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1792(%rbp)
  movq -1792(%rbp), %rax
  imulq -1784(%rbp), %rax
  movq %rax, -1800(%rbp)
  movq -1800(%rbp), %rax
  movq -672(%rbp), %rdx
  movq %rax, (%rdx)
  movq $3600, %rax
  movq -680(%rbp), %rdx
  movq %rax, (%rdx)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1808(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1816(%rbp)
  movq -1816(%rbp), %rax
  imulq -1808(%rbp), %rax
  movq %rax, -1824(%rbp)
  movq -1824(%rbp), %rax
  movq -688(%rbp), %rdx
  movq %rax, (%rdx)
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1832(%rbp)
  movq -672(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1840(%rbp)
  movq -1840(%rbp), %rax
  addq -1832(%rbp), %rax
  movq %rax, -1848(%rbp)
  movq -1848(%rbp), %rax
  movq -696(%rbp), %rdx
  movq %rax, (%rdx)
  movq $60, %rax
  movq -704(%rbp), %rdx
  movq %rax, (%rdx)
  movq -704(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1856(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1864(%rbp)
  movq -1864(%rbp), %rax
  imulq -1856(%rbp), %rax
  movq %rax, -1872(%rbp)
  movq -1872(%rbp), %rax
  movq -712(%rbp), %rdx
  movq %rax, (%rdx)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1880(%rbp)
  movq -696(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1888(%rbp)
  movq -1888(%rbp), %rax
  addq -1880(%rbp), %rax
  movq %rax, -1896(%rbp)
  movq -1896(%rbp), %rax
  movq -720(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1904(%rbp)
  movq -720(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1912(%rbp)
  movq -1912(%rbp), %rax
  addq -1904(%rbp), %rax
  movq %rax, -1920(%rbp)
  movq -1920(%rbp), %rax
  movq -728(%rbp), %rdx
  movq %rax, (%rdx)
  movq -728(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1928(%rbp)
  movq -1928(%rbp), %rax
  jmp std.time.datetime.datetime_to_timestamp_epilogue
std.time.datetime.datetime_to_timestamp_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.datetime_to_timestamp:

.globl std.time.timer.__init__
std.time.timer.__init__:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
std.time.timer.__init___entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -48(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.timer.__init___epilogue
std.time.timer.__init___epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.timer.__init__:

.globl std.time.datetime.DateTime.start_of_week
std.time.datetime.DateTime.start_of_week:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.start_of_week_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.start_of_week_epilogue
std.time.datetime.DateTime.start_of_week_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.start_of_week:

.globl std.time.datetime.get_days_in_year
std.time.datetime.get_days_in_year:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $168, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.get_days_in_year_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.get_days_in_year_block_0
std.time.datetime.get_days_in_year_block_0:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -168(%rbp), %rdi
  call std.time.datetime.is_leap_year
  mov -176(%rbp), rax
  movq -176(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.get_days_in_year_block_2
  jmp std.time.datetime.get_days_in_year_block_4
std.time.datetime.get_days_in_year_block_2:
  movq $366, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -192(%rbp)
  movq -192(%rbp), %rax
  jmp std.time.datetime.get_days_in_year_epilogue
std.time.datetime.get_days_in_year_block_4:
  movq $365, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -200(%rbp)
  movq -200(%rbp), %rax
  jmp std.time.datetime.get_days_in_year_epilogue
std.time.datetime.get_days_in_year_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.get_days_in_year:

.globl std.time.datetime.DateTime.year
std.time.datetime.DateTime.year:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.year_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.year_epilogue
std.time.datetime.DateTime.year_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.year:

.globl std.time.datetime.DateTime.from_string
std.time.datetime.DateTime.from_string:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.from_string_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.from_string_epilogue
std.time.datetime.DateTime.from_string_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.from_string:

.globl std.time.duration.TimeDuration.subtract
std.time.duration.TimeDuration.subtract:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.duration.TimeDuration.subtract_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.subtract_epilogue
std.time.duration.TimeDuration.subtract_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.subtract:

.globl std.time.duration.TimeDuration.from_seconds
std.time.duration.TimeDuration.from_seconds:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.duration.TimeDuration.from_seconds_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.from_seconds_epilogue
std.time.duration.TimeDuration.from_seconds_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.from_seconds:

.globl std.time.instant.Instant.now
std.time.instant.Instant.now:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.instant.Instant.now_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.instant.Instant.now_epilogue
std.time.instant.Instant.now_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.instant.Instant.now:

.globl std.time.timer.Timer.elapsed
std.time.timer.Timer.elapsed:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.timer.Timer.elapsed_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.timer.Timer.elapsed_epilogue
std.time.timer.Timer.elapsed_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.timer.Timer.elapsed:

.globl std.time.datetime.DateTime.start_of_year
std.time.datetime.DateTime.start_of_year:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.start_of_year_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.start_of_year_epilogue
std.time.datetime.DateTime.start_of_year_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.start_of_year:

.globl __user_main
__user_main:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $808, %rsp
__user_main_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -48(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -272(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -280(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -288(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -296(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -304(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -312(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -320(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  jmp __user_main_block_0
__user_main_block_0:
  leaq str_hdr_5(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -336(%rbp)
  movq -336(%rbp), %rax
  testq %rax, %rax
  jne __user_main_pr_nil_0_886
  jmp __user_main_pr_str_0_886
__user_main_pr_nil_0_886:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -344(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -344(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -352(%rbp)
  jmp __user_main_pr_next_0_886
__user_main_pr_str_0_886:
  movq -328(%rbp), %rax
  addq $8, %rax
  movq %rax, -360(%rbp)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -328(%rbp), %rax
  addq $24, %rax
  movq %rax, -376(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -376(%rbp), %rsi
  movq -368(%rbp), %rdx
  syscall
  movq %rax, -384(%rbp)
  jmp __user_main_pr_next_0_886
__user_main_pr_next_0_886:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -392(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -392(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -400(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  call test_duration
  mov -408(%rbp), rax
  movq -408(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -416(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  cmpq -416(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  movq -80(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_6(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -440(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -440(%rbp), %rax
  testq %rax, %rax
  jne __user_main_assert_pass_7
  jmp __user_main_assert_fail_7
__user_main_assert_pass_7:
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  call test_timezone
  mov -456(%rbp), rax
  movq -456(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  cmpq -464(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -480(%rbp)
  movq -480(%rbp), %rax
  movq -120(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_8(%rip), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -488(%rbp), %rax
  testq %rax, %rax
  jne __user_main_assert_pass_9
  jmp __user_main_assert_fail_9
__user_main_assert_fail_7:
  movq -448(%rbp), %rax
  addq $8, %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -448(%rbp), %rax
  addq $24, %rax
  movq %rax, -520(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -520(%rbp), %rsi
  movq -512(%rbp), %rdx
  syscall
  movq %rax, -528(%rbp)
  movq $50397203, %rax
  movq %rax, -536(%rbp)
  jmp __user_main_assert_pass_7
__user_main_assert_pass_9:
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  call test_time
  mov -544(%rbp), rax
  movq -544(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -560(%rbp), %rax
  cmpq -552(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rax
  movq -160(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_10(%rip), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -576(%rbp), %rax
  testq %rax, %rax
  jne __user_main_assert_pass_11
  jmp __user_main_assert_fail_11
__user_main_assert_fail_9:
  movq -496(%rbp), %rax
  addq $8, %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -496(%rbp), %rax
  addq $24, %rax
  movq %rax, -608(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -608(%rbp), %rsi
  movq -600(%rbp), %rdx
  syscall
  movq %rax, -616(%rbp)
  movq $50397203, %rax
  movq %rax, -624(%rbp)
  jmp __user_main_assert_pass_9
__user_main_assert_pass_11:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  call test_instant_and_timer
  mov -632(%rbp), rax
  movq -632(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  cmpq -640(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rax
  movq -200(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_12(%rip), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -664(%rbp), %rax
  testq %rax, %rax
  jne __user_main_assert_pass_13
  jmp __user_main_assert_fail_13
__user_main_assert_fail_11:
  movq -584(%rbp), %rax
  addq $8, %rax
  movq %rax, -680(%rbp)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -584(%rbp), %rax
  addq $24, %rax
  movq %rax, -696(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -696(%rbp), %rsi
  movq -688(%rbp), %rdx
  syscall
  movq %rax, -704(%rbp)
  movq $50397203, %rax
  movq %rax, -712(%rbp)
  jmp __user_main_assert_pass_11
__user_main_assert_pass_13:
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_14(%rip), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -720(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -728(%rbp)
  movq -728(%rbp), %rax
  testq %rax, %rax
  jne __user_main_pr_nil_0_2777
  jmp __user_main_pr_str_0_2777
__user_main_assert_fail_13:
  movq -672(%rbp), %rax
  addq $8, %rax
  movq %rax, -736(%rbp)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -672(%rbp), %rax
  addq $24, %rax
  movq %rax, -752(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -752(%rbp), %rsi
  movq -744(%rbp), %rdx
  syscall
  movq %rax, -760(%rbp)
  movq $50397203, %rax
  movq %rax, -768(%rbp)
  jmp __user_main_assert_pass_13
__user_main_pr_nil_0_2777:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -776(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -776(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -784(%rbp)
  jmp __user_main_pr_next_0_2777
__user_main_pr_str_0_2777:
  movq -720(%rbp), %rax
  addq $8, %rax
  movq %rax, -792(%rbp)
  movq -792(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -720(%rbp), %rax
  addq $24, %rax
  movq %rax, -808(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -808(%rbp), %rsi
  movq -800(%rbp), %rdx
  syscall
  movq %rax, -816(%rbp)
  jmp __user_main_pr_next_0_2777
__user_main_pr_next_0_2777:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -824(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -824(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -832(%rbp)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -840(%rbp), %rax
  jmp __user_main_epilogue
__user_main_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end___user_main:

.globl std.time.duration.TimeDuration.less_than
std.time.duration.TimeDuration.less_than:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.duration.TimeDuration.less_than_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.less_than_epilogue
std.time.duration.TimeDuration.less_than_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.less_than:

.globl std.time.datetime.DateTime.greater_than
std.time.datetime.DateTime.greater_than:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.greater_than_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.greater_than_epilogue
std.time.datetime.DateTime.greater_than_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.greater_than:

.globl std.time.datetime.DateTime.days_in_month
std.time.datetime.DateTime.days_in_month:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.days_in_month_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.days_in_month_epilogue
std.time.datetime.DateTime.days_in_month_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.days_in_month:

.globl std.time.datetime.sleep_duration
std.time.datetime.sleep_duration:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $168, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.sleep_duration_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.sleep_duration_block_0
std.time.datetime.sleep_duration_block_0:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -160(%rbp)
  movq -160(%rbp), %rdi
  call std.time.duration.TimeDuration.to_milliseconds
  mov -168(%rbp), rax
  movq -168(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -176(%rbp)
  movq -176(%rbp), %rdi
  call std.time.datetime.sleep_ms
  mov -184(%rbp), rax
  movq -184(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -192(%rbp)
  movq -192(%rbp), %rax
  jmp std.time.datetime.sleep_duration_epilogue
std.time.datetime.sleep_duration_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.sleep_duration:

.globl std.time.datetime.DateTime.quarter
std.time.datetime.DateTime.quarter:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.quarter_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.quarter_epilogue
std.time.datetime.DateTime.quarter_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.quarter:

.globl std.time.datetime.DateTime.with_year
std.time.datetime.DateTime.with_year:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.with_year_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.with_year_epilogue
std.time.datetime.DateTime.with_year_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.with_year:

.globl test_time
test_time:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $952, %rsp
test_time_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -48(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -272(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -280(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -288(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -296(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -304(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -312(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -320(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -328(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -336(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -344(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -352(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -360(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -368(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -376(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -384(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -392(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_time_block_0
test_time_block_0:
  leaq str_hdr_15(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -400(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -408(%rbp)
  movq -408(%rbp), %rax
  testq %rax, %rax
  jne test_time_pr_nil_0_6915
  jmp test_time_pr_str_0_6915
test_time_pr_nil_0_6915:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -416(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -416(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -424(%rbp)
  jmp test_time_pr_next_0_6915
test_time_pr_str_0_6915:
  movq -400(%rbp), %rax
  addq $8, %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -440(%rbp)
  movq -400(%rbp), %rax
  addq $24, %rax
  movq %rax, -448(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -448(%rbp), %rsi
  movq -440(%rbp), %rdx
  syscall
  movq %rax, -456(%rbp)
  jmp test_time_pr_next_0_6915
test_time_pr_next_0_6915:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -464(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -464(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -472(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1000000, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_16(%rip), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 24 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -480(%rbp)
  addq $24, %rax
  movq %rax, heap_ptr(%rip)
  movq -480(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -488(%rbp), %rdi
  movq -496(%rbp), %rsi
  movq -504(%rbp), %rdx
  movq -512(%rbp), %rcx
  call std.time.timezone.TimeZone.init
  mov -520(%rbp), rax
  movq -520(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 24 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -528(%rbp)
  addq $24, %rax
  movq %rax, heap_ptr(%rip)
  movq -528(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -536(%rbp), %rdi
  movq -544(%rbp), %rsi
  movq -552(%rbp), %rdx
  movq -560(%rbp), %rcx
  call std.time.datetime.DateTime.init
  mov -568(%rbp), rax
  movq -568(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -576(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -584(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rax
  addq $0, %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1000000, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -624(%rbp), %rax
  cmpq -616(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -632(%rbp)
  movq -632(%rbp), %rax
  movq -168(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_17(%rip), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -640(%rbp), %rax
  testq %rax, %rax
  jne test_time_assert_pass_18
  jmp test_time_assert_fail_18
test_time_assert_pass_18:
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rdi
  call std.time.datetime.DateTime.year
  mov -664(%rbp), rax
  movq -664(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1970, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -680(%rbp), %rax
  cmpq -672(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -688(%rbp)
  movq -688(%rbp), %rax
  movq -208(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_19(%rip), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -696(%rbp), %rax
  testq %rax, %rax
  jne test_time_assert_pass_20
  jmp test_time_assert_fail_20
test_time_assert_fail_18:
  movq -648(%rbp), %rax
  addq $8, %rax
  movq %rax, -712(%rbp)
  movq -712(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -648(%rbp), %rax
  addq $24, %rax
  movq %rax, -728(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -728(%rbp), %rsi
  movq -720(%rbp), %rdx
  syscall
  movq %rax, -736(%rbp)
  movq $50397203, %rax
  movq %rax, -744(%rbp)
  jmp test_time_assert_pass_18
test_time_assert_pass_20:
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -752(%rbp), %rdi
  call std.time.datetime.DateTime.month
  mov -760(%rbp), rax
  movq -760(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -776(%rbp), %rax
  cmpq -768(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -784(%rbp)
  movq -784(%rbp), %rax
  movq -248(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_21(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -792(%rbp), %rax
  testq %rax, %rax
  jne test_time_assert_pass_22
  jmp test_time_assert_fail_22
test_time_assert_fail_20:
  movq -704(%rbp), %rax
  addq $8, %rax
  movq %rax, -808(%rbp)
  movq -808(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -704(%rbp), %rax
  addq $24, %rax
  movq %rax, -824(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -824(%rbp), %rsi
  movq -816(%rbp), %rdx
  syscall
  movq %rax, -832(%rbp)
  movq $50397203, %rax
  movq %rax, -840(%rbp)
  jmp test_time_assert_pass_20
test_time_assert_pass_22:
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -848(%rbp)
  movq -848(%rbp), %rdi
  call std.time.datetime.DateTime.day
  mov -856(%rbp), rax
  movq -856(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq $12, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -872(%rbp)
  movq -872(%rbp), %rax
  cmpq -864(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -880(%rbp)
  movq -880(%rbp), %rax
  movq -288(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_23(%rip), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -888(%rbp)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -888(%rbp), %rax
  testq %rax, %rax
  jne test_time_assert_pass_24
  jmp test_time_assert_fail_24
test_time_assert_fail_22:
  movq -800(%rbp), %rax
  addq $8, %rax
  movq %rax, -904(%rbp)
  movq -904(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -912(%rbp)
  movq -800(%rbp), %rax
  addq $24, %rax
  movq %rax, -920(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -920(%rbp), %rsi
  movq -912(%rbp), %rdx
  syscall
  movq %rax, -928(%rbp)
  movq $50397203, %rax
  movq %rax, -936(%rbp)
  jmp test_time_assert_pass_22
test_time_assert_pass_24:
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -944(%rbp)
  movq -944(%rbp), %rax
  jmp test_time_epilogue
test_time_assert_fail_24:
  movq -896(%rbp), %rax
  addq $8, %rax
  movq %rax, -952(%rbp)
  movq -952(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -960(%rbp)
  movq -896(%rbp), %rax
  addq $24, %rax
  movq %rax, -968(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -968(%rbp), %rsi
  movq -960(%rbp), %rdx
  syscall
  movq %rax, -976(%rbp)
  movq $50397203, %rax
  movq %rax, -984(%rbp)
  jmp test_time_assert_pass_24
test_time_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_test_time:

.globl std.time.datetime.DateTime.format
std.time.datetime.DateTime.format:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.format_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.format_epilogue
std.time.datetime.DateTime.format_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.format:

.globl std.time.datetime.DateTime.with_month
std.time.datetime.DateTime.with_month:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.with_month_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.with_month_epilogue
std.time.datetime.DateTime.with_month_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.with_month:

.globl std.time.datetime.DateTime.to_iso8601
std.time.datetime.DateTime.to_iso8601:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.to_iso8601_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.to_iso8601_epilogue
std.time.datetime.DateTime.to_iso8601_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.to_iso8601:

.globl std.time.datetime.DateTime.with_day
std.time.datetime.DateTime.with_day:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.with_day_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.with_day_epilogue
std.time.datetime.DateTime.with_day_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.with_day:

.globl std.time.datetime.sleep_seconds
std.time.datetime.sleep_seconds:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $136, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.sleep_seconds_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.sleep_seconds_block_0
std.time.datetime.sleep_seconds_block_0:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -152(%rbp)
  movq -152(%rbp), %rdi
  call sleep
  movq $r1, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -160(%rbp)
  movq -160(%rbp), %rax
  jmp std.time.datetime.sleep_seconds_epilogue
std.time.datetime.sleep_seconds_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.sleep_seconds:

.globl std.time.datetime.DateTime.with_hour
std.time.datetime.DateTime.with_hour:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.with_hour_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.with_hour_epilogue
std.time.datetime.DateTime.with_hour_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.with_hour:

.globl std.time.timer.Timer.init
std.time.timer.Timer.init:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.timer.Timer.init_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.timer.Timer.init_epilogue
std.time.timer.Timer.init_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.timer.Timer.init:

.globl std.time.duration.TimeDuration.to_string
std.time.duration.TimeDuration.to_string:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.duration.TimeDuration.to_string_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.to_string_epilogue
std.time.duration.TimeDuration.to_string_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.to_string:

.globl std.time.duration.TimeDuration.multiply
std.time.duration.TimeDuration.multiply:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.duration.TimeDuration.multiply_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.multiply_epilogue
std.time.duration.TimeDuration.multiply_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.multiply:

.globl std.time.datetime.DateTime.to_rfc2822
std.time.datetime.DateTime.to_rfc2822:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.to_rfc2822_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.to_rfc2822_epilogue
std.time.datetime.DateTime.to_rfc2822_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.to_rfc2822:

.globl std.time.datetime.DateTime.to_timezone
std.time.datetime.DateTime.to_timezone:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.to_timezone_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.to_timezone_epilogue
std.time.datetime.DateTime.to_timezone_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.to_timezone:

.globl std.time.datetime.DateTime.equals
std.time.datetime.DateTime.equals:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.equals_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.equals_epilogue
std.time.datetime.DateTime.equals_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.equals:

.globl std.time.datetime.DateTime.less_than
std.time.datetime.DateTime.less_than:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.less_than_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.less_than_epilogue
std.time.datetime.DateTime.less_than_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.less_than:

.globl std.time.datetime.DateTime.is_between
std.time.datetime.DateTime.is_between:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
  movq %rdx, -64(%rbp)
std.time.datetime.DateTime.is_between_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.is_between_epilogue
std.time.datetime.DateTime.is_between_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.is_between:

.globl std.time.datetime.DateTime.to_iso_string
std.time.datetime.DateTime.to_iso_string:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.to_iso_string_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.to_iso_string_epilogue
std.time.datetime.DateTime.to_iso_string_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.to_iso_string:

.globl std.time.datetime.DateTime.to_date_string
std.time.datetime.DateTime.to_date_string:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.to_date_string_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.to_date_string_epilogue
std.time.datetime.DateTime.to_date_string_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.to_date_string:

.globl std.time.instant.Instant.elapsed
std.time.instant.Instant.elapsed:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.instant.Instant.elapsed_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.instant.Instant.elapsed_epilogue
std.time.instant.Instant.elapsed_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.instant.Instant.elapsed:

.globl std.time.datetime.DateTime.is_weekend
std.time.datetime.DateTime.is_weekend:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.is_weekend_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.is_weekend_epilogue
std.time.datetime.DateTime.is_weekend_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.is_weekend:

.globl test_timezone
test_timezone:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $600, %rsp
test_timezone_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -48(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -272(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -280(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_timezone_block_0
test_timezone_block_0:
  leaq str_hdr_25(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -296(%rbp)
  movq -296(%rbp), %rax
  testq %rax, %rax
  jne test_timezone_pr_nil_0_7793
  jmp test_timezone_pr_str_0_7793
test_timezone_pr_nil_0_7793:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -304(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -304(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -312(%rbp)
  jmp test_timezone_pr_next_0_7793
test_timezone_pr_str_0_7793:
  movq -288(%rbp), %rax
  addq $8, %rax
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -328(%rbp)
  movq -288(%rbp), %rax
  addq $24, %rax
  movq %rax, -336(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -336(%rbp), %rsi
  movq -328(%rbp), %rdx
  syscall
  movq %rax, -344(%rbp)
  jmp test_timezone_pr_next_0_7793
test_timezone_pr_next_0_7793:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -352(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -352(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -360(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_26(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 24 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -368(%rbp)
  addq $24, %rax
  movq %rax, heap_ptr(%rip)
  movq -368(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -376(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -384(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -376(%rbp), %rdi
  movq -384(%rbp), %rsi
  movq -392(%rbp), %rdx
  movq -400(%rbp), %rcx
  call std.time.timezone.TimeZone.init
  mov -408(%rbp), rax
  movq -408(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -416(%rbp)
  movq -416(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  addq $0, %rax
  movq %rax, -440(%rbp)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_27(%rip), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -456(%rbp), %rdi
  movq -464(%rbp), %rsi
  call lm_key_eq
  mov -472(%rbp), rax
  movq -472(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_28(%rip), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -480(%rbp), %rax
  testq %rax, %rax
  jne test_timezone_assert_pass_29
  jmp test_timezone_assert_fail_29
test_timezone_assert_pass_29:
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rdi
  call std.time.timezone.TimeZone.offset_string
  mov -504(%rbp), rax
  movq -504(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_30(%rip), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -512(%rbp), %rdi
  movq -520(%rbp), %rsi
  call lm_key_eq
  mov -528(%rbp), rax
  movq -528(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_31(%rip), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -536(%rbp), %rax
  testq %rax, %rax
  jne test_timezone_assert_pass_32
  jmp test_timezone_assert_fail_32
test_timezone_assert_fail_29:
  movq -488(%rbp), %rax
  addq $8, %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -488(%rbp), %rax
  addq $24, %rax
  movq %rax, -568(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -568(%rbp), %rsi
  movq -560(%rbp), %rdx
  syscall
  movq %rax, -576(%rbp)
  movq $50397203, %rax
  movq %rax, -584(%rbp)
  jmp test_timezone_assert_pass_29
test_timezone_assert_pass_32:
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rax
  jmp test_timezone_epilogue
test_timezone_assert_fail_32:
  movq -544(%rbp), %rax
  addq $8, %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -544(%rbp), %rax
  addq $24, %rax
  movq %rax, -616(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -616(%rbp), %rsi
  movq -608(%rbp), %rdx
  syscall
  movq %rax, -624(%rbp)
  movq $50397203, %rax
  movq %rax, -632(%rbp)
  jmp test_timezone_assert_pass_32
test_timezone_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_test_timezone:

.globl std.time.datetime.DateTime.init
std.time.datetime.DateTime.init:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $136, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
  movq %rdx, -64(%rbp)
  movq %rcx, -72(%rbp)
std.time.datetime.DateTime.init_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.init_epilogue
std.time.datetime.DateTime.init_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.init:

.globl std.time.datetime.DateTime.is_weekday
std.time.datetime.DateTime.is_weekday:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.is_weekday_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.is_weekday_epilogue
std.time.datetime.DateTime.is_weekday_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.is_weekday:

.globl std.time.datetime.DateTime.start_of_day
std.time.datetime.DateTime.start_of_day:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.start_of_day_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.start_of_day_epilogue
std.time.datetime.DateTime.start_of_day_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.start_of_day:

.globl std.time.datetime.DateTime.start_of_month
std.time.datetime.DateTime.start_of_month:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.start_of_month_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.start_of_month_epilogue
std.time.datetime.DateTime.start_of_month_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.start_of_month:

.globl std.time.datetime.DateTime.end_of_month
std.time.datetime.DateTime.end_of_month:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.end_of_month_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.end_of_month_epilogue
std.time.datetime.DateTime.end_of_month_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.end_of_month:

.globl std.time.datetime.DateTime.to_time_string
std.time.datetime.DateTime.to_time_string:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.to_time_string_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.to_time_string_epilogue
std.time.datetime.DateTime.to_time_string_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.to_time_string:

.globl std.time.duration.TimeDuration.equals
std.time.duration.TimeDuration.equals:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.duration.TimeDuration.equals_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.equals_epilogue
std.time.duration.TimeDuration.equals_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.equals:

.globl std.time.datetime.DateTime.age
std.time.datetime.DateTime.age:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.age_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.age_epilogue
std.time.datetime.DateTime.age_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.age:

.globl std.time.datetime.sleep_ms
std.time.datetime.sleep_ms:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $200, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.sleep_ms_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.sleep_ms_block_0
std.time.datetime.sleep_ms_block_0:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -176(%rbp)
  movq -176(%rbp), %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq $4652007308841189376, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -192(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -200(%rbp)
  movq -200(%rbp), %rax
  cqto
  movq -192(%rbp), %rcx
  idivq %rcx
  movq %rax, -208(%rbp)
  movq -208(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -216(%rbp)
  movq -216(%rbp), %rdi
  call sleep
  movq $r4, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -224(%rbp)
  movq -224(%rbp), %rax
  jmp std.time.datetime.sleep_ms_epilogue
std.time.datetime.sleep_ms_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.sleep_ms:

.globl test_instant_and_timer
test_instant_and_timer:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $792, %rsp
test_instant_and_timer_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -48(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -272(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -280(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -288(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -296(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -304(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -312(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -320(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -328(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -336(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -344(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -352(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  jmp test_instant_and_timer_block_0
test_instant_and_timer_block_0:
  leaq str_hdr_33(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -360(%rbp)
  movq -360(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rax
  testq %rax, %rax
  jne test_instant_and_timer_pr_nil_0_8335
  jmp test_instant_and_timer_pr_str_0_8335
test_instant_and_timer_pr_nil_0_8335:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -376(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -376(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -384(%rbp)
  jmp test_instant_and_timer_pr_next_0_8335
test_instant_and_timer_pr_str_0_8335:
  movq -360(%rbp), %rax
  addq $8, %rax
  movq %rax, -392(%rbp)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -360(%rbp), %rax
  addq $24, %rax
  movq %rax, -408(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -408(%rbp), %rsi
  movq -400(%rbp), %rdx
  syscall
  movq %rax, -416(%rbp)
  jmp test_instant_and_timer_pr_next_0_8335
test_instant_and_timer_pr_next_0_8335:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -424(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -424(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -432(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -440(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -440(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -448(%rbp), %rdi
  movq -456(%rbp), %rsi
  call std.time.instant.Instant.init
  mov -464(%rbp), rax
  movq -464(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -480(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rdi
  call std.time.instant.Instant.elapsed
  mov -496(%rbp), rax
  movq -496(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  addq $8, %rax
  movq %rax, -528(%rbp)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -536(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rax
  cmpq -544(%rbp), %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -560(%rbp)
  movq -560(%rbp), %rax
  movq -144(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_34(%rip), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -568(%rbp), %rax
  testq %rax, %rax
  jne test_instant_and_timer_assert_pass_35
  jmp test_instant_and_timer_assert_fail_35
test_instant_and_timer_assert_pass_35:
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -584(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -584(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rdi
  call std.time.timer.Timer.init
  mov -600(%rbp), rax
  movq -600(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -624(%rbp), %rdi
  call std.time.timer.Timer.reset
  mov -632(%rbp), rax
  movq -632(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -640(%rbp), %rdi
  call std.time.timer.Timer.elapsed
  mov -648(%rbp), rax
  movq -648(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -672(%rbp), %rax
  addq $8, %rax
  movq %rax, -680(%rbp)
  movq -680(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -688(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -704(%rbp), %rax
  cmpq -696(%rbp), %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -712(%rbp)
  movq -712(%rbp), %rax
  movq -248(%rbp), %rdx
  movl %eax, (%rdx)
  leaq str_hdr_36(%rip), %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -720(%rbp), %rax
  testq %rax, %rax
  jne test_instant_and_timer_assert_pass_37
  jmp test_instant_and_timer_assert_fail_37
test_instant_and_timer_assert_fail_35:
  movq -576(%rbp), %rax
  addq $8, %rax
  movq %rax, -736(%rbp)
  movq -736(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -576(%rbp), %rax
  addq $24, %rax
  movq %rax, -752(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -752(%rbp), %rsi
  movq -744(%rbp), %rdx
  syscall
  movq %rax, -760(%rbp)
  movq $50397203, %rax
  movq %rax, -768(%rbp)
  jmp test_instant_and_timer_assert_pass_35
test_instant_and_timer_assert_pass_37:
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -776(%rbp), %rax
  jmp test_instant_and_timer_epilogue
test_instant_and_timer_assert_fail_37:
  movq -728(%rbp), %rax
  addq $8, %rax
  movq %rax, -784(%rbp)
  movq -784(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -792(%rbp)
  movq -728(%rbp), %rax
  addq $24, %rax
  movq %rax, -800(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -800(%rbp), %rsi
  movq -792(%rbp), %rdx
  syscall
  movq %rax, -808(%rbp)
  movq $50397203, %rax
  movq %rax, -816(%rbp)
  jmp test_instant_and_timer_assert_pass_37
test_instant_and_timer_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_test_instant_and_timer:

.globl std.time.instant.Instant.init
std.time.instant.Instant.init:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.instant.Instant.init_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.instant.Instant.init_epilogue
std.time.instant.Instant.init_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.instant.Instant.init:

.globl std.time.timezone.TimeZone.offset_string
std.time.timezone.TimeZone.offset_string:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.timezone.TimeZone.offset_string_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.timezone.TimeZone.offset_string_epilogue
std.time.timezone.TimeZone.offset_string_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.timezone.TimeZone.offset_string:

.globl std.time.instant.__init__
std.time.instant.__init__:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
std.time.instant.__init___entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -48(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.instant.__init___epilogue
std.time.instant.__init___epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.instant.__init__:

.globl std.time.timezone.TimeZone.utc
std.time.timezone.TimeZone.utc:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.timezone.TimeZone.utc_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.timezone.TimeZone.utc_epilogue
std.time.timezone.TimeZone.utc_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.timezone.TimeZone.utc:

.globl std.time.timezone.TimeZone.from_offset
std.time.timezone.TimeZone.from_offset:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.timezone.TimeZone.from_offset_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.timezone.TimeZone.from_offset_epilogue
std.time.timezone.TimeZone.from_offset_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.timezone.TimeZone.from_offset:

.globl std.time.datetime.timestamp_to_year
std.time.datetime.timestamp_to_year:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $968, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.timestamp_to_year_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -272(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -280(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -288(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -296(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -304(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -312(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -320(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -328(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -336(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -344(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -352(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -360(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -368(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -368(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -376(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -384(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -392(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -392(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -400(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -408(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -416(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -424(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -424(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -432(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -432(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -440(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -440(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.timestamp_to_year_block_0
std.time.datetime.timestamp_to_year_block_0:
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rax
  cmpq -448(%rbp), %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -464(%rbp)
  movq -464(%rbp), %rax
  movq -72(%rbp), %rdx
  movl %eax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.timestamp_to_year_block_3
  jmp std.time.datetime.timestamp_to_year_block_21
std.time.datetime.timestamp_to_year_block_3:
  movq $86400, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rax
  cqto
  movq -480(%rbp), %rcx
  idivq %rcx
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1970, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.timestamp_to_year_block_9
std.time.datetime.timestamp_to_year_block_9:
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rdi
  call std.time.datetime.get_days_in_year
  mov -528(%rbp), rax
  movq -528(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -544(%rbp)
  movq -544(%rbp), %rax
  cmpq -536(%rbp), %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rax
  movq -128(%rbp), %rdx
  movl %eax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -560(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.timestamp_to_year_block_12
  jmp std.time.datetime.timestamp_to_year_block_20
std.time.datetime.timestamp_to_year_block_12:
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rdi
  call std.time.datetime.get_days_in_year
  mov -576(%rbp), rax
  movq -576(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rax
  subq -584(%rbp), %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -624(%rbp), %rax
  addq -616(%rbp), %rax
  movq %rax, -632(%rbp)
  movq -632(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -640(%rbp)
  movq -640(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.timestamp_to_year_block_9
std.time.datetime.timestamp_to_year_block_20:
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  jmp std.time.datetime.timestamp_to_year_epilogue
std.time.datetime.timestamp_to_year_block_21:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rax
  negq %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq $86400, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -680(%rbp)
  movq -680(%rbp), %rax
  cqto
  movq -672(%rbp), %rcx
  idivq %rcx
  movq %rax, -688(%rbp)
  movq -688(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -696(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -704(%rbp), %rax
  negq %rax
  movq %rax, -712(%rbp)
  movq -712(%rbp), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq $86400, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -728(%rbp), %rax
  cqto
  movq -720(%rbp), %rcx
  idivq %rcx
  movq %rdx, -736(%rbp)
  movq -736(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -752(%rbp)
  movq -752(%rbp), %rax
  cmpq -744(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -760(%rbp)
  movq -760(%rbp), %rax
  movq -240(%rbp), %rdx
  movl %eax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -768(%rbp)
  movq -768(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.timestamp_to_year_block_31
  jmp std.time.datetime.timestamp_to_year_block_36
std.time.datetime.timestamp_to_year_block_31:
  movq $1, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -784(%rbp)
  movq -784(%rbp), %rax
  addq -776(%rbp), %rax
  movq %rax, -792(%rbp)
  movq -792(%rbp), %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -800(%rbp)
  movq -800(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.timestamp_to_year_block_36
std.time.datetime.timestamp_to_year_block_36:
  movq $1970, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -808(%rbp)
  movq -808(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.timestamp_to_year_block_39
std.time.datetime.timestamp_to_year_block_39:
  movq $1, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -824(%rbp)
  movq -824(%rbp), %rax
  subq -816(%rbp), %rax
  movq %rax, -832(%rbp)
  movq -832(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -840(%rbp)
  movq -840(%rbp), %rdi
  call std.time.datetime.get_days_in_year
  mov -848(%rbp), rax
  movq -848(%rbp), %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -856(%rbp)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -864(%rbp)
  movq -864(%rbp), %rax
  cmpq -856(%rbp), %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -872(%rbp)
  movq -872(%rbp), %rax
  movq -312(%rbp), %rdx
  movl %eax, (%rdx)
  movq -312(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -880(%rbp)
  movq -880(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.timestamp_to_year_block_44
  jmp std.time.datetime.timestamp_to_year_block_51
std.time.datetime.timestamp_to_year_block_44:
  movq $1, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  movq -320(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -888(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -896(%rbp), %rax
  subq -888(%rbp), %rax
  movq %rax, -904(%rbp)
  movq -904(%rbp), %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -912(%rbp)
  movq -912(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -920(%rbp)
  movq -920(%rbp), %rdi
  call std.time.datetime.get_days_in_year
  mov -928(%rbp), rax
  movq -928(%rbp), %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  movq -336(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -944(%rbp)
  movq -944(%rbp), %rax
  subq -936(%rbp), %rax
  movq %rax, -952(%rbp)
  movq -952(%rbp), %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  movq -344(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -960(%rbp)
  movq -960(%rbp), %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.timestamp_to_year_block_39
std.time.datetime.timestamp_to_year_block_51:
  movq $1, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -968(%rbp)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -976(%rbp), %rax
  subq -968(%rbp), %rax
  movq %rax, -984(%rbp)
  movq -984(%rbp), %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -360(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -992(%rbp)
  movq -992(%rbp), %rax
  jmp std.time.datetime.timestamp_to_year_epilogue
std.time.datetime.timestamp_to_year_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.timestamp_to_year:

.globl std.time.timezone.TimeZone.to_seconds_offset
std.time.timezone.TimeZone.to_seconds_offset:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.timezone.TimeZone.to_seconds_offset_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.timezone.TimeZone.to_seconds_offset_epilogue
std.time.timezone.TimeZone.to_seconds_offset_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.timezone.TimeZone.to_seconds_offset:

.globl std.time.datetime.timestamp_to_month
std.time.datetime.timestamp_to_month:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $696, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.timestamp_to_month_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -272(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -280(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -288(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -296(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -304(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -312(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -320(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -320(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -328(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -328(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -336(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -336(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -344(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -344(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -352(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -352(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -360(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -360(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.timestamp_to_month_block_0
std.time.datetime.timestamp_to_month_block_0:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rdi
  call std.time.datetime.timestamp_to_year
  mov -376(%rbp), rax
  movq -376(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -384(%rbp)
  movq -384(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -416(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -392(%rbp), %rdi
  movq -400(%rbp), %rsi
  movq -408(%rbp), %rdx
  movq -416(%rbp), %rcx
  movq -424(%rbp), %r8
  movq -432(%rbp), %r9
  call std.time.datetime.datetime_to_timestamp
  mov -440(%rbp), rax
  movq -440(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -464(%rbp), %rax
  subq -456(%rbp), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -480(%rbp)
  movq -480(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rax
  cmpq -488(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  movq -160(%rbp), %rdx
  movl %eax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.timestamp_to_month_block_14
  jmp std.time.datetime.timestamp_to_month_block_17
std.time.datetime.timestamp_to_month_block_14:
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.timestamp_to_month_block_17
std.time.datetime.timestamp_to_month_block_17:
  movq $86400, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -536(%rbp), %rax
  cqto
  movq -528(%rbp), %rcx
  idivq %rcx
  movq %rax, -544(%rbp)
  movq -544(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.timestamp_to_month_block_22
std.time.datetime.timestamp_to_month_block_22:
  movq $12, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rax
  cmpq -560(%rbp), %rax
  setle %al
  movzbq %al, %rax
  movq %rax, -576(%rbp)
  movq -576(%rbp), %rax
  movq -216(%rbp), %rdx
  movl %eax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -584(%rbp)
  movq -584(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.timestamp_to_month_block_25
  jmp std.time.datetime.timestamp_to_month_block_37
std.time.datetime.timestamp_to_month_block_25:
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -592(%rbp), %rdi
  movq -600(%rbp), %rsi
  call std.time.datetime.get_days_in_month
  mov -608(%rbp), rax
  movq -608(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -632(%rbp)
  movq -632(%rbp), %rax
  cmpq -624(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -640(%rbp)
  movq -640(%rbp), %rax
  movq -240(%rbp), %rdx
  movl %eax, (%rdx)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.timestamp_to_month_block_29
  jmp std.time.datetime.timestamp_to_month_block_30
std.time.datetime.timestamp_to_month_block_29:
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rax
  jmp std.time.datetime.timestamp_to_month_epilogue
std.time.datetime.timestamp_to_month_block_30:
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -664(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -672(%rbp), %rax
  subq -664(%rbp), %rax
  movq %rax, -680(%rbp)
  movq -680(%rbp), %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  movq -248(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -688(%rbp)
  movq -688(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -704(%rbp), %rax
  addq -696(%rbp), %rax
  movq %rax, -712(%rbp)
  movq -712(%rbp), %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -720(%rbp)
  movq -720(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.timestamp_to_month_block_22
std.time.datetime.timestamp_to_month_block_37:
  movq $12, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -728(%rbp)
  movq -728(%rbp), %rax
  jmp std.time.datetime.timestamp_to_month_epilogue
std.time.datetime.timestamp_to_month_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.timestamp_to_month:

.globl std.time.datetime.DateTime.with_minute
std.time.datetime.DateTime.with_minute:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.with_minute_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.with_minute_epilogue
std.time.datetime.DateTime.with_minute_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.with_minute:

.globl std.time.timezone.TimeZone.init
std.time.timezone.TimeZone.init:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $136, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
  movq %rdx, -64(%rbp)
  movq %rcx, -72(%rbp)
std.time.timezone.TimeZone.init_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.timezone.TimeZone.init_epilogue
std.time.timezone.TimeZone.init_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.timezone.TimeZone.init:

.globl std.time.timezone.__init__
std.time.timezone.__init__:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
std.time.timezone.__init___entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -48(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.timezone.__init___epilogue
std.time.timezone.__init___epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.timezone.__init__:

.globl std.time.datetime.timestamp_to_day
std.time.datetime.timestamp_to_day:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $552, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.timestamp_to_day_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -240(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -240(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -248(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -248(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -256(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -256(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -264(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -264(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -272(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -272(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -280(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -280(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -288(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -288(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -296(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -304(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -304(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -312(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -312(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.timestamp_to_day_block_0
std.time.datetime.timestamp_to_day_block_0:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rdi
  call std.time.datetime.timestamp_to_year
  mov -328(%rbp), rax
  movq -328(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -336(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -344(%rbp)
  movq -344(%rbp), %rdi
  call std.time.datetime.timestamp_to_month
  mov -352(%rbp), rax
  movq -352(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -360(%rbp)
  movq -360(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -376(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -384(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -368(%rbp), %rdi
  movq -376(%rbp), %rsi
  movq -384(%rbp), %rdx
  movq -392(%rbp), %rcx
  movq -400(%rbp), %r8
  movq -408(%rbp), %r9
  call std.time.datetime.datetime_to_timestamp
  mov -416(%rbp), rax
  movq -416(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -440(%rbp)
  movq -440(%rbp), %rax
  subq -432(%rbp), %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -472(%rbp)
  movq -472(%rbp), %rax
  cmpq -464(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -480(%rbp)
  movq -480(%rbp), %rax
  movq -168(%rbp), %rdx
  movl %eax, (%rdx)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -488(%rbp)
  movq -488(%rbp), %rax
  testq %rax, %rax
  jne std.time.datetime.timestamp_to_day_block_15
  jmp std.time.datetime.timestamp_to_day_block_18
std.time.datetime.timestamp_to_day_block_15:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.datetime.timestamp_to_day_block_18
std.time.datetime.timestamp_to_day_block_18:
  movq $86400, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -504(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  cqto
  movq -504(%rbp), %rcx
  idivq %rcx
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq $86400, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -536(%rbp), %rax
  cqto
  movq -528(%rbp), %rcx
  idivq %rcx
  movq %rax, -544(%rbp)
  movq -544(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq $1, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -560(%rbp)
  movq -560(%rbp), %rax
  addq -552(%rbp), %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -576(%rbp), %rax
  jmp std.time.datetime.timestamp_to_day_epilogue
std.time.datetime.timestamp_to_day_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.timestamp_to_day:

.globl std.time.timer.Timer.reset
std.time.timer.Timer.reset:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.timer.Timer.reset_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.timer.Timer.reset_epilogue
std.time.timer.Timer.reset_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.timer.Timer.reset:

.globl std.time.duration.pad_int
std.time.duration.pad_int:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $296, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.duration.pad_int_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -152(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -200(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -208(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.duration.pad_int_block_0
std.time.duration.pad_int_block_0:
  leaq str_hdr_38(%rip), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -216(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -224(%rbp)
  movq -216(%rbp), %rdi
  movq -224(%rbp), %rsi
  call lm_rt_str_format
  mov -232(%rbp), rax
  movq -232(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -240(%rbp)
  movq -240(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.duration.pad_int_block_4
std.time.duration.pad_int_block_4:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -248(%rbp)
  movq -248(%rbp), %rdi
  call lm_list_len
  mov -256(%rbp), rax
  movq -256(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -264(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -272(%rbp)
  movq -272(%rbp), %rax
  cmpq -264(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -280(%rbp)
  movq -280(%rbp), %rax
  movq -112(%rbp), %rdx
  movl %eax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rax
  testq %rax, %rax
  jne std.time.duration.pad_int_block_7
  jmp std.time.duration.pad_int_block_11
std.time.duration.pad_int_block_7:
  leaq str_hdr_39(%rip), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -296(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -304(%rbp)
  movq -296(%rbp), %rdi
  movq -304(%rbp), %rsi
  call lm_str_concat
  mov -312(%rbp), rax
  movq -312(%rbp), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp std.time.duration.pad_int_block_4
std.time.duration.pad_int_block_11:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rax
  jmp std.time.duration.pad_int_epilogue
std.time.duration.pad_int_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.pad_int:

.globl std.time.datetime.DateTime.start_of_quarter
std.time.datetime.DateTime.start_of_quarter:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.start_of_quarter_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.start_of_quarter_epilogue
std.time.datetime.DateTime.start_of_quarter_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.start_of_quarter:

.globl std.time.duration.TimeDuration.from_milliseconds
std.time.duration.TimeDuration.from_milliseconds:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.duration.TimeDuration.from_milliseconds_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.from_milliseconds_epilogue
std.time.duration.TimeDuration.from_milliseconds_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.from_milliseconds:

.globl std.time.datetime.DateTime.end_of_day
std.time.datetime.DateTime.end_of_day:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.end_of_day_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.end_of_day_epilogue
std.time.datetime.DateTime.end_of_day_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.end_of_day:

.globl std.time.duration.TimeDuration.from_microseconds
std.time.duration.TimeDuration.from_microseconds:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.duration.TimeDuration.from_microseconds_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.from_microseconds_epilogue
std.time.duration.TimeDuration.from_microseconds_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.from_microseconds:

.globl std.time.duration.TimeDuration.add
std.time.duration.TimeDuration.add:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.duration.TimeDuration.add_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.add_epilogue
std.time.duration.TimeDuration.add_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.add:

.globl std.time.datetime.DateTime.end_of_year
std.time.datetime.DateTime.end_of_year:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.end_of_year_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.end_of_year_epilogue
std.time.datetime.DateTime.end_of_year_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.end_of_year:

.globl std.time.duration.TimeDuration.to_seconds
std.time.duration.TimeDuration.to_seconds:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.duration.TimeDuration.to_seconds_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.to_seconds_epilogue
std.time.duration.TimeDuration.to_seconds_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.to_seconds:

.globl std.time.datetime.DateTime.with_second
std.time.datetime.DateTime.with_second:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $120, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
std.time.datetime.DateTime.with_second_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -144(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.with_second_epilogue
std.time.datetime.DateTime.with_second_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.with_second:

.globl std.time.duration.TimeDuration.to_microseconds
std.time.duration.TimeDuration.to_microseconds:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.duration.TimeDuration.to_microseconds_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.to_microseconds_epilogue
std.time.duration.TimeDuration.to_microseconds_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.to_microseconds:

.globl std.time.datetime.DateTime.week_of_year
std.time.datetime.DateTime.week_of_year:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.datetime.DateTime.week_of_year_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.datetime.DateTime.week_of_year_epilogue
std.time.datetime.DateTime.week_of_year_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.datetime.DateTime.week_of_year:

.globl std.time.duration.TimeDuration.total_seconds
std.time.duration.TimeDuration.total_seconds:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
std.time.duration.TimeDuration.total_seconds_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -80(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -88(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -104(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -128(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp std.time.duration.TimeDuration.total_seconds_epilogue
std.time.duration.TimeDuration.total_seconds_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_std.time.duration.TimeDuration.total_seconds:

.globl lm_list_new
lm_list_new:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $88, %rsp
  movq %rdi, -48(%rbp)
lm_list_new_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -48(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  cmpq $0, %rax
  setle %al
  movzbq %al, %rax
  movq %rax, -64(%rbp)
  movq -64(%rbp), %rax
  testq %rax, %rax
  jne lm_list_new_def_cap
  jmp lm_list_new_alloc
lm_list_new_def_cap:
  movq $8, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_new_alloc
lm_list_new_alloc:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -72(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq $24, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -80(%rbp)
  movq -72(%rbp), %rax
  imulq $8, %rax
  movq %rax, -88(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq -88(%rbp), %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -96(%rbp)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  addq $8, %rax
  movq %rax, -104(%rbp)
  movq -72(%rbp), %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  addq $16, %rax
  movq %rax, -112(%rbp)
  movq -96(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  jmp lm_list_new_epilogue
lm_list_new_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_list_new:

.globl lm_list_append
lm_list_append:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $216, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
lm_list_append_entry:
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -64(%rbp)
  movq -48(%rbp), %rax
  addq $8, %rax
  movq %rax, -72(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -80(%rbp)
  movq -64(%rbp), %rax
  cmpq -80(%rbp), %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -88(%rbp)
  movq -88(%rbp), %rax
  testq %rax, %rax
  jne lm_list_append_realloc
  jmp lm_list_append_insert
lm_list_append_realloc:
  movq -80(%rbp), %rax
  imulq $2, %rax
  movq %rax, -96(%rbp)
  movq -96(%rbp), %rax
  imulq $8, %rax
  movq %rax, -104(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq -104(%rbp), %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -112(%rbp)
  movq -48(%rbp), %rax
  addq $16, %rax
  movq %rax, -120(%rbp)
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -128(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -136(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_append_copy_loop
lm_list_append_copy_loop:
  movq -136(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -144(%rbp)
  movq -144(%rbp), %rax
  cmpq -64(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -152(%rbp)
  movq -152(%rbp), %rax
  testq %rax, %rax
  jne lm_list_append_copy_body
  jmp lm_list_append_copy_done
lm_list_append_copy_body:
  movq -144(%rbp), %rax
  imulq $8, %rax
  movq %rax, -160(%rbp)
  movq -128(%rbp), %rax
  addq -160(%rbp), %rax
  movq %rax, -168(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -176(%rbp)
  movq -112(%rbp), %rax
  addq -160(%rbp), %rax
  movq %rax, -184(%rbp)
  movq -176(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  addq $1, %rax
  movq %rax, -192(%rbp)
  movq -192(%rbp), %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_append_copy_loop
lm_list_append_copy_done:
  movq -96(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_append_insert
lm_list_append_insert:
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -200(%rbp)
  movq -48(%rbp), %rax
  addq $16, %rax
  movq %rax, -208(%rbp)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -216(%rbp)
  movq -200(%rbp), %rax
  imulq $8, %rax
  movq %rax, -224(%rbp)
  movq -216(%rbp), %rax
  addq -224(%rbp), %rax
  movq %rax, -232(%rbp)
  movq -56(%rbp), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  addq $1, %rax
  movq %rax, -240(%rbp)
  movq -240(%rbp), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp lm_list_append_epilogue
lm_list_append_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_list_append:

.globl lm_list_get
lm_list_get:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
lm_list_get_entry:
  movq -48(%rbp), %rax
  addq $16, %rax
  movq %rax, -64(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -72(%rbp)
  movq -72(%rbp), %rax
  cmpq $65536, %rax
  setb %al
  movzbq %al, %rax
  movq %rax, -80(%rbp)
  movq -80(%rbp), %rax
  testq %rax, %rax
  jne lm_list_get_get_tuple
  jmp lm_list_get_get_list
lm_list_get_get_list:
  movq -56(%rbp), %rax
  imulq $8, %rax
  movq %rax, -88(%rbp)
  movq -72(%rbp), %rax
  addq -88(%rbp), %rax
  movq %rax, -96(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -104(%rbp)
  movq -104(%rbp), %rax
  jmp lm_list_get_epilogue
lm_list_get_get_tuple:
  movq -56(%rbp), %rax
  addq $1, %rax
  movq %rax, -112(%rbp)
  movq -112(%rbp), %rax
  imulq $8, %rax
  movq %rax, -120(%rbp)
  movq -48(%rbp), %rax
  addq -120(%rbp), %rax
  movq %rax, -128(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -136(%rbp)
  movq -136(%rbp), %rax
  jmp lm_list_get_epilogue
lm_list_get_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_list_get:

.globl lm_key_eq
lm_key_eq:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $424, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
lm_key_eq_entry:
  movq -48(%rbp), %rax
  cmpq -56(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -64(%rbp)
  movq -64(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_ret_true
  jmp lm_key_eq_ptrcmp
lm_key_eq_ptrcmp:
  movq -48(%rbp), %rax
  cmpq $65536, %rax
  setb %al
  movzbq %al, %rax
  movq %rax, -72(%rbp)
  movq -56(%rbp), %rax
  cmpq $65536, %rax
  setb %al
  movzbq %al, %rax
  movq %rax, -80(%rbp)
  movq -72(%rbp), %rax
  orq -80(%rbp), %rax
  movq %rax, -88(%rbp)
  movq -88(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_ret_false
  jmp lm_key_eq_chk_enum
lm_key_eq_loop_init:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_key_eq_loop_cond
lm_key_eq_loop_cond:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -104(%rbp)
  movq -48(%rbp), %rax
  addq -104(%rbp), %rax
  movq %rax, -112(%rbp)
  movq -56(%rbp), %rax
  addq -104(%rbp), %rax
  movq %rax, -120(%rbp)
  movq -112(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -128(%rbp)
  movq -120(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -136(%rbp)
  movq -128(%rbp), %rax
  cmpq -136(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -144(%rbp)
  movq -144(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_ret_false
  jmp lm_key_eq_check_end
lm_key_eq_check_end:
  movq -128(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -152(%rbp)
  movq -152(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_ret_true
  jmp lm_key_eq_advance
lm_key_eq_advance:
  movq -104(%rbp), %rax
  addq $1, %rax
  movq %rax, -160(%rbp)
  movq -160(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_key_eq_loop_cond
lm_key_eq_ret_true:
  movq $1, %rax
  jmp lm_key_eq_epilogue
lm_key_eq_ret_false:
  movq $0, %rax
  jmp lm_key_eq_epilogue
lm_key_eq_chk_enum:
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -176(%rbp)
  movq -168(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -184(%rbp)
  movq -176(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -192(%rbp)
  movq -184(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -200(%rbp)
  movq -192(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -208(%rbp)
  movq -200(%rbp), %rax
  andq -208(%rbp), %rax
  movq %rax, -216(%rbp)
  movq -216(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_str_hdr_cmp
  jmp lm_key_eq_enum_chk
lm_key_eq_str_hdr_cmp:
  movq -48(%rbp), %rax
  addq $8, %rax
  movq %rax, -224(%rbp)
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -232(%rbp)
  movq -56(%rbp), %rax
  addq $8, %rax
  movq %rax, -240(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -248(%rbp)
  movq -232(%rbp), %rax
  cmpq -248(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -256(%rbp)
  movq -256(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_str_hdr_bytes
  jmp lm_key_eq_ret_false
lm_key_eq_enum_chk:
  movq -168(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -264(%rbp)
  movq -176(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -272(%rbp)
  movq -264(%rbp), %rax
  andq -272(%rbp), %rax
  movq %rax, -280(%rbp)
  movq -264(%rbp), %rax
  orq -272(%rbp), %rax
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_enum_only
  jmp lm_key_eq_loop_init
lm_key_eq_str_hdr_bytes:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -296(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_key_eq_str_hdr_loop
lm_key_eq_str_hdr_loop:
  movq -296(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -304(%rbp)
  movq -304(%rbp), %rax
  cmpq -232(%rbp), %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -312(%rbp)
  movq -312(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_ret_true
  jmp lm_key_eq_str_hdr_body
lm_key_eq_str_hdr_body:
  movq -48(%rbp), %rax
  addq $24, %rax
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rax
  addq -304(%rbp), %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -56(%rbp), %rax
  addq $24, %rax
  movq %rax, -344(%rbp)
  movq -344(%rbp), %rax
  addq -304(%rbp), %rax
  movq %rax, -352(%rbp)
  movq -352(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -360(%rbp)
  movq -336(%rbp), %rax
  cmpq -360(%rbp), %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -368(%rbp)
  movq -304(%rbp), %rax
  addq $1, %rax
  movq %rax, -376(%rbp)
  movq -376(%rbp), %rax
  movq -296(%rbp), %rdx
  movq %rax, (%rdx)
  movq -368(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_ret_false
  jmp lm_key_eq_str_hdr_loop
lm_key_eq_enum_only:
  movq -280(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_enum_cmp
  jmp lm_key_eq_ret_false
lm_key_eq_enum_cmp:
  movq -48(%rbp), %rax
  addq $8, %rax
  movq %rax, -384(%rbp)
  movq -384(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -392(%rbp)
  movq -56(%rbp), %rax
  addq $8, %rax
  movq %rax, -400(%rbp)
  movq -400(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -392(%rbp), %rax
  cmpq -408(%rbp), %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -416(%rbp)
  movq -416(%rbp), %rax
  testq %rax, %rax
  jne lm_key_eq_pay_cmp
  jmp lm_key_eq_ret_false
lm_key_eq_pay_cmp:
  movq -48(%rbp), %rax
  addq $16, %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -56(%rbp), %rax
  addq $16, %rax
  movq %rax, -440(%rbp)
  movq -440(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -448(%rbp)
  movq -432(%rbp), %rdi
  movq -448(%rbp), %rsi
  call lm_key_eq
  mov -456(%rbp), rax
  movq -456(%rbp), %rax
  jmp lm_key_eq_epilogue
lm_key_eq_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_key_eq:

.globl lm_rt_str_format
lm_rt_str_format:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $760, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
lm_rt_str_format_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -56(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -80(%rbp)
  movq -56(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -88(%rbp)
  movq -88(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -96(%rbp)
  movq -80(%rbp), %rax
  andq -96(%rbp), %rax
  movq %rax, -104(%rbp)
  movq -104(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_is_str
  jmp lm_rt_str_format_fmt_is_num
lm_rt_str_format_fmt_is_num:
  movq -88(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -112(%rbp)
  movq -112(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_is_float
  jmp lm_rt_str_format_fmt_is_int
lm_rt_str_format_fmt_is_float:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -120(%rbp)
  movq $11, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  addq $24, %rax
  movq %rax, -128(%rbp)
  leaq fmt_float(%rip), %rax
  addq $24, %rax
  movq %rax, -136(%rbp)
  movq $184614912, %rax
  movq %rax, -144(%rbp)
  movq -120(%rbp), %rax
  addq $8, %rax
  movq %rax, -152(%rbp)
  movq -144(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  addq $16, %rax
  movq %rax, -160(%rbp)
  movq -144(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -120(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_slen_prep
lm_rt_str_format_fmt_is_int:
  movq $9, %rax
  movq $0, %rdi
  movq $32, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -168(%rbp)
  movq -168(%rbp), %rax
  addq $31, %rax
  movq %rax, -176(%rbp)
  movq $0, %rax
  movq -176(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -184(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -192(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -56(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_num_loop
lm_rt_str_format_fmt_is_str:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -200(%rbp)
  movq -200(%rbp), %rax
  andq $4294967295, %rax
  movq %rax, -208(%rbp)
  movq -208(%rbp), %rax
  cmpq $11, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -216(%rbp)
  movq -216(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_is_rawstr
  jmp lm_rt_str_format_fmt_is_enum_c
lm_rt_str_format_fmt_proc:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  addq $24, %rax
  movq %rax, -232(%rbp)
  movq -48(%rbp), %rax
  addq $8, %rax
  movq %rax, -240(%rbp)
  movq -240(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -248(%rbp)
  jmp lm_rt_str_format_fmt_scan_loop
lm_rt_str_format_fmt_slen_prep:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -256(%rbp)
  movq -256(%rbp), %rax
  addq $8, %rax
  movq %rax, -264(%rbp)
  movq -264(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -272(%rbp)
  movq -256(%rbp), %rax
  addq $24, %rax
  movq %rax, -280(%rbp)
  movq -280(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -272(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_proc
lm_rt_str_format_fmt_num_loop:
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -296(%rbp)
  movq -288(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -304(%rbp)
  movq -296(%rbp), %rax
  addq $48, %rax
  movq %rax, -312(%rbp)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rax
  subq $1, %rax
  movq %rax, -328(%rbp)
  movq -312(%rbp), %rax
  movq -328(%rbp), %rdx
  movb %al, (%rdx)
  movq -304(%rbp), %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  movq -328(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  cmpq $1, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -336(%rbp)
  movq -336(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_num_loop
  jmp lm_rt_str_format_fmt_num_done
lm_rt_str_format_fmt_num_done:
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -344(%rbp)
  movq -176(%rbp), %rax
  subq -344(%rbp), %rax
  movq %rax, -352(%rbp)
  movq -344(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -352(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_proc
lm_rt_str_format_fmt_is_enum_p:
  movq -56(%rbp), %rdi
  call lm_enum_to_str
  mov -360(%rbp), rax
  movq -360(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_slen_prep
lm_rt_str_format_fmt_is_enum_c:
  movq -200(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_is_enum_p
  jmp lm_rt_str_format_fmt_is_list
lm_rt_str_format_fmt_is_list:
  movq -56(%rbp), %rdi
  call lm_list_to_str
  mov -376(%rbp), rax
  movq -376(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_slen_prep
lm_rt_str_format_fmt_is_rawstr:
  movq -56(%rbp), %rax
  addq $24, %rax
  movq %rax, -384(%rbp)
  movq -56(%rbp), %rax
  addq $8, %rax
  movq %rax, -392(%rbp)
  movq -392(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -400(%rbp)
  movq -384(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -400(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_proc
lm_rt_str_format_fmt_scan_loop:
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -408(%rbp)
  movq -408(%rbp), %rax
  cmpq -248(%rbp), %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -416(%rbp)
  movq -416(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_no_pct
  jmp lm_rt_str_format_fmt_check_s
lm_rt_str_format_fmt_check_s:
  movq -232(%rbp), %rax
  addq -408(%rbp), %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -432(%rbp)
  movq -432(%rbp), %rax
  cmpq $37, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -440(%rbp)
  movq -408(%rbp), %rax
  addq $1, %rax
  movq %rax, -448(%rbp)
  movq -232(%rbp), %rax
  addq -448(%rbp), %rax
  movq %rax, -456(%rbp)
  movq -456(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -464(%rbp)
  movq -464(%rbp), %rax
  cmpq $115, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -472(%rbp)
  movq -440(%rbp), %rax
  andq -472(%rbp), %rax
  movq %rax, -480(%rbp)
  movq -432(%rbp), %rax
  cmpq $123, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -488(%rbp)
  movq -464(%rbp), %rax
  cmpq $125, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -496(%rbp)
  movq -488(%rbp), %rax
  andq -496(%rbp), %rax
  movq %rax, -504(%rbp)
  movq -480(%rbp), %rax
  orq -504(%rbp), %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_do_replace
  jmp lm_rt_str_format_fmt_scan_next
lm_rt_str_format_fmt_scan_next:
  movq -408(%rbp), %rax
  addq $1, %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_scan_loop
lm_rt_str_format_fmt_no_pct:
  movq -48(%rbp), %rax
  jmp lm_rt_str_format_epilogue
lm_rt_str_format_fmt_do_replace:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -528(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -408(%rbp), %rax
  addq $2, %rax
  movq %rax, -544(%rbp)
  movq -248(%rbp), %rax
  subq -544(%rbp), %rax
  movq %rax, -552(%rbp)
  movq -408(%rbp), %rax
  addq -536(%rbp), %rax
  movq %rax, -560(%rbp)
  movq -560(%rbp), %rax
  addq -552(%rbp), %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rdi
  call lm_str_alloc
  mov -576(%rbp), rax
  movq -576(%rbp), %rax
  addq $24, %rax
  movq %rax, -584(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -592(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_c1_loop
lm_rt_str_format_fmt_c1_loop:
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -600(%rbp)
  movq -600(%rbp), %rax
  cmpq -408(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_c1_body
  jmp lm_rt_str_format_fmt_c1_done
lm_rt_str_format_fmt_c1_body:
  movq -232(%rbp), %rax
  addq -600(%rbp), %rax
  movq %rax, -616(%rbp)
  movq -616(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -624(%rbp)
  movq -584(%rbp), %rax
  addq -600(%rbp), %rax
  movq %rax, -632(%rbp)
  movq -624(%rbp), %rax
  movq -632(%rbp), %rdx
  movb %al, (%rdx)
  movq -600(%rbp), %rax
  addq $1, %rax
  movq %rax, -640(%rbp)
  movq -640(%rbp), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_c1_loop
lm_rt_str_format_fmt_c1_done:
  movq $0, %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_c2_loop
lm_rt_str_format_fmt_c2_loop:
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -648(%rbp)
  movq -648(%rbp), %rax
  cmpq -536(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_c2_body
  jmp lm_rt_str_format_fmt_c2_done
lm_rt_str_format_fmt_c2_body:
  movq -528(%rbp), %rax
  addq -648(%rbp), %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -672(%rbp)
  movq -408(%rbp), %rax
  addq -648(%rbp), %rax
  movq %rax, -680(%rbp)
  movq -584(%rbp), %rax
  addq -680(%rbp), %rax
  movq %rax, -688(%rbp)
  movq -672(%rbp), %rax
  movq -688(%rbp), %rdx
  movb %al, (%rdx)
  movq -648(%rbp), %rax
  addq $1, %rax
  movq %rax, -696(%rbp)
  movq -696(%rbp), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_c2_loop
lm_rt_str_format_fmt_c2_done:
  movq $0, %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_c3_loop
lm_rt_str_format_fmt_c3_loop:
  movq -592(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -704(%rbp)
  movq -704(%rbp), %rax
  cmpq -552(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -712(%rbp)
  movq -712(%rbp), %rax
  testq %rax, %rax
  jne lm_rt_str_format_fmt_c3_body
  jmp lm_rt_str_format_fmt_c3_done
lm_rt_str_format_fmt_c3_body:
  movq -408(%rbp), %rax
  addq $2, %rax
  movq %rax, -720(%rbp)
  movq -720(%rbp), %rax
  addq -704(%rbp), %rax
  movq %rax, -728(%rbp)
  movq -232(%rbp), %rax
  addq -728(%rbp), %rax
  movq %rax, -736(%rbp)
  movq -736(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -744(%rbp)
  movq -408(%rbp), %rax
  addq -536(%rbp), %rax
  movq %rax, -752(%rbp)
  movq -752(%rbp), %rax
  addq -704(%rbp), %rax
  movq %rax, -760(%rbp)
  movq -584(%rbp), %rax
  addq -760(%rbp), %rax
  movq %rax, -768(%rbp)
  movq -744(%rbp), %rax
  movq -768(%rbp), %rdx
  movb %al, (%rdx)
  movq -704(%rbp), %rax
  addq $1, %rax
  movq %rax, -776(%rbp)
  movq -776(%rbp), %rax
  movq -592(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_rt_str_format_fmt_c3_loop
lm_rt_str_format_fmt_c3_done:
  movq -584(%rbp), %rax
  addq -568(%rbp), %rax
  movq %rax, -784(%rbp)
  movq $0, %rax
  movq -784(%rbp), %rdx
  movb %al, (%rdx)
  movq -576(%rbp), %rax
  addq $8, %rax
  movq %rax, -792(%rbp)
  movq -568(%rbp), %rax
  movq -792(%rbp), %rdx
  movq %rax, (%rdx)
  movq -576(%rbp), %rax
  jmp lm_rt_str_format_epilogue
lm_rt_str_format_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_rt_str_format:

.globl lm_list_len
lm_list_len:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $24, %rsp
  movq %rdi, -48(%rbp)
lm_list_len_entry:
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -56(%rbp)
  movq -56(%rbp), %rax
  jmp lm_list_len_epilogue
lm_list_len_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_list_len:

.globl lm_str_concat
lm_str_concat:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $248, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
lm_str_concat_entry:
  movq -48(%rbp), %rax
  addq $8, %rax
  movq %rax, -64(%rbp)
  movq -64(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -72(%rbp)
  movq -56(%rbp), %rax
  addq $8, %rax
  movq %rax, -80(%rbp)
  movq -80(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -88(%rbp)
  movq -72(%rbp), %rax
  addq -88(%rbp), %rax
  movq %rax, -96(%rbp)
  movq -96(%rbp), %rax
  addq $25, %rax
  movq %rax, -104(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq -104(%rbp), %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -112(%rbp)
  movq $11, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  addq $8, %rax
  movq %rax, -120(%rbp)
  movq -96(%rbp), %rax
  movq -120(%rbp), %rdx
  movb %al, (%rdx)
  movq -112(%rbp), %rax
  addq $16, %rax
  movq %rax, -128(%rbp)
  movq -96(%rbp), %rax
  movq -128(%rbp), %rdx
  movb %al, (%rdx)
  movq -112(%rbp), %rax
  addq $24, %rax
  movq %rax, -136(%rbp)
  movq -48(%rbp), %rax
  addq $24, %rax
  movq %rax, -144(%rbp)
  movq -56(%rbp), %rax
  addq $24, %rax
  movq %rax, -152(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_str_concat_c1_loop
lm_str_concat_done:
  movq -112(%rbp), %rax
  jmp lm_str_concat_epilogue
lm_str_concat_c1_loop:
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -168(%rbp)
  movq -168(%rbp), %rax
  cmpq -72(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -176(%rbp)
  movq -176(%rbp), %rax
  testq %rax, %rax
  jne lm_str_concat_c1_body
  jmp lm_str_concat_c1_done
lm_str_concat_c1_body:
  movq -144(%rbp), %rax
  addq -168(%rbp), %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -192(%rbp)
  movq -136(%rbp), %rax
  addq -168(%rbp), %rax
  movq %rax, -200(%rbp)
  movq -192(%rbp), %rax
  movq -200(%rbp), %rdx
  movb %al, (%rdx)
  movq -168(%rbp), %rax
  addq $1, %rax
  movq %rax, -208(%rbp)
  movq -208(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_str_concat_c1_loop
lm_str_concat_c1_done:
  movq $0, %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_str_concat_c2_loop
lm_str_concat_c2_loop:
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -216(%rbp)
  movq -216(%rbp), %rax
  cmpq -88(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -224(%rbp)
  movq -224(%rbp), %rax
  testq %rax, %rax
  jne lm_str_concat_c2_body
  jmp lm_str_concat_c2_done
lm_str_concat_c2_body:
  movq -152(%rbp), %rax
  addq -216(%rbp), %rax
  movq %rax, -232(%rbp)
  movq -232(%rbp), %rax
  movzbq (%rax), %rax
  movq %rax, -240(%rbp)
  movq -72(%rbp), %rax
  addq -216(%rbp), %rax
  movq %rax, -248(%rbp)
  movq -136(%rbp), %rax
  addq -248(%rbp), %rax
  movq %rax, -256(%rbp)
  movq -240(%rbp), %rax
  movq -256(%rbp), %rdx
  movb %al, (%rdx)
  movq -216(%rbp), %rax
  addq $1, %rax
  movq %rax, -264(%rbp)
  movq -264(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_str_concat_c2_loop
lm_str_concat_c2_done:
  movq -136(%rbp), %rax
  addq -96(%rbp), %rax
  movq %rax, -272(%rbp)
  movq $0, %rax
  movq -272(%rbp), %rdx
  movb %al, (%rdx)
  jmp lm_str_concat_done
lm_str_concat_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_str_concat:

.globl lm_enum_new
lm_enum_new:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $72, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
  movq %rdx, -64(%rbp)
lm_enum_new_entry:
  movq $9, %rax
  movq $0, %rdi
  movq $32, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -72(%rbp)
  movq $1162761549, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  addq $8, %rax
  movq %rax, -80(%rbp)
  movq -48(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  addq $16, %rax
  movq %rax, -88(%rbp)
  movq -56(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  addq $24, %rax
  movq %rax, -96(%rbp)
  movq -64(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  jmp lm_enum_new_epilogue
lm_enum_new_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_enum_new:

.globl lm_enum_tag
lm_enum_tag:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $40, %rsp
  movq %rdi, -48(%rbp)
lm_enum_tag_entry:
  movq -48(%rbp), %rax
  addq $8, %rax
  movq %rax, -56(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -64(%rbp)
  movq -64(%rbp), %rax
  jmp lm_enum_tag_epilogue
lm_enum_tag_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_enum_tag:

.globl lm_enum_payload
lm_enum_payload:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $40, %rsp
  movq %rdi, -48(%rbp)
lm_enum_payload_entry:
  movq -48(%rbp), %rax
  addq $16, %rax
  movq %rax, -56(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -64(%rbp)
  movq -64(%rbp), %rax
  jmp lm_enum_payload_epilogue
lm_enum_payload_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_enum_payload:

.globl lm_enum_to_str
lm_enum_to_str:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $632, %rsp
  movq %rdi, -48(%rbp)
lm_enum_to_str_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -48(%rbp), %rax
  addq $8, %rax
  movq %rax, -64(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -72(%rbp)
  movq -48(%rbp), %rax
  addq $16, %rax
  movq %rax, -80(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -88(%rbp)
  movq -48(%rbp), %rax
  addq $24, %rax
  movq %rax, -96(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -104(%rbp)
  movq -88(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -112(%rbp)
  movq -88(%rbp), %rax
  cmpq $18446744073709551615, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -120(%rbp)
  movq -112(%rbp), %rax
  orq -120(%rbp), %rax
  movq %rax, -128(%rbp)
  movq -128(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_no_pay
  jmp lm_enum_to_str_has_pay
lm_enum_to_str_no_pay:
  movq -104(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -136(%rbp)
  movq -136(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_has_vname
  jmp lm_enum_to_str_no_vname
lm_enum_to_str_has_vname:
  movq -104(%rbp), %rax
  jmp lm_enum_to_str_epilogue
lm_enum_to_str_no_vname:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -144(%rbp)
  movq $11, %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  addq $63, %rax
  movq %rax, -152(%rbp)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -160(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -152(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -168(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -176(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -72(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_i2s_neg_1
  jmp lm_enum_to_str_i2s_pos_1
lm_enum_to_str_has_pay:
  movq -88(%rbp), %rax
  cmpq $65536, %rax
  setae %al
  movzbq %al, %rax
  movq %rax, -192(%rbp)
  movq -88(%rbp), %rax
  movq $48, %rcx
  shrq %cl, %rax
  movq %rax, -200(%rbp)
  movq -200(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -208(%rbp)
  movq -192(%rbp), %rax
  andq -208(%rbp), %rax
  movq %rax, -216(%rbp)
  movq -216(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_pay_ptr
  jmp lm_enum_to_str_pay_int
lm_enum_to_str_pay_int:
  movq -200(%rbp), %rax
  cmpq $0, %rax
  setne %al
  movzbq %al, %rax
  movq %rax, -224(%rbp)
  movq -224(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_pay_float
  jmp lm_enum_to_str_pay_i64
lm_enum_to_str_pay_ptr:
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -232(%rbp)
  movq -232(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -240(%rbp)
  movq -240(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_pay_enum
  jmp lm_enum_to_str_pay_rawstr
lm_enum_to_str_pay_enum:
  movq -88(%rbp), %rdi
  call lm_enum_to_str
  mov -248(%rbp), rax
  movq -248(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_build_pay
lm_enum_to_str_pay_rawstr:
  movq -88(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_build_pay
lm_enum_to_str_build_pay:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -256(%rbp)
  movq -256(%rbp), %rax
  jmp lm_enum_to_str_epilogue
lm_enum_to_str_i2s_neg_1:
  movq $1, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  negq %rax
  movq %rax, -264(%rbp)
  movq -264(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_1
lm_enum_to_str_i2s_pos_1:
  movq $0, %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_1
lm_enum_to_str_i2s_loop_1:
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -272(%rbp)
  movq -272(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -280(%rbp)
  movq -272(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  movq -280(%rbp), %rax
  addq $48, %rax
  movq %rax, -296(%rbp)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -304(%rbp)
  movq -304(%rbp), %rax
  subq $1, %rax
  movq %rax, -312(%rbp)
  movq -296(%rbp), %rax
  movq -312(%rbp), %rdx
  movb %al, (%rdx)
  movq -312(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -288(%rbp), %rax
  cmpq $1, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -320(%rbp)
  movq -320(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_i2s_loop_1
  jmp lm_enum_to_str_i2s_sign_1
lm_enum_to_str_i2s_sign_1:
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -336(%rbp)
  movq -336(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_i2s_minus_1
  jmp lm_enum_to_str_i2s_done_1
lm_enum_to_str_i2s_minus_1:
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -344(%rbp)
  movq -344(%rbp), %rax
  subq $1, %rax
  movq %rax, -352(%rbp)
  movq $45, %rax
  movq -352(%rbp), %rdx
  movb %al, (%rdx)
  movq -352(%rbp), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_done_1
lm_enum_to_str_i2s_done_1:
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -360(%rbp)
  movq -152(%rbp), %rax
  subq -360(%rbp), %rax
  movq %rax, -368(%rbp)
  movq -144(%rbp), %rax
  addq $8, %rax
  movq %rax, -376(%rbp)
  movq -368(%rbp), %rax
  movq -376(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  addq $16, %rax
  movq %rax, -384(%rbp)
  movq -368(%rbp), %rax
  movq -384(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  addq $24, %rax
  movq %rax, -392(%rbp)
  movq -368(%rbp), %rax
  addq $1, %rax
  movq %rax, -400(%rbp)
  movq $184614912, %rax
  movq %rax, -408(%rbp)
  movq -144(%rbp), %rax
  jmp lm_enum_to_str_epilogue
lm_enum_to_str_pay_float:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -416(%rbp)
  movq $11, %rax
  movq -416(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  addq $24, %rax
  movq %rax, -424(%rbp)
  leaq fmt_float(%rip), %rax
  addq $24, %rax
  movq %rax, -432(%rbp)
  movq $184614912, %rax
  movq %rax, -440(%rbp)
  movq -416(%rbp), %rax
  addq $8, %rax
  movq %rax, -448(%rbp)
  movq -440(%rbp), %rax
  movq -448(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  addq $16, %rax
  movq %rax, -456(%rbp)
  movq -440(%rbp), %rax
  movq -456(%rbp), %rdx
  movq %rax, (%rdx)
  movq -416(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_build_pay
lm_enum_to_str_pay_i64:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -464(%rbp)
  movq $11, %rax
  movq -464(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  addq $63, %rax
  movq %rax, -472(%rbp)
  movq $0, %rax
  movq -472(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -480(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -472(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -488(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -496(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -88(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_i2s_neg_2
  jmp lm_enum_to_str_i2s_pos_2
lm_enum_to_str_i2s_neg_2:
  movq $1, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  negq %rax
  movq %rax, -512(%rbp)
  movq -512(%rbp), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_2
lm_enum_to_str_i2s_pos_2:
  movq $0, %rax
  movq -496(%rbp), %rdx
  movq %rax, (%rdx)
  movq -88(%rbp), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_loop_2
lm_enum_to_str_i2s_loop_2:
  movq -488(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -520(%rbp)
  movq -520(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -528(%rbp)
  movq -520(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -536(%rbp)
  movq -536(%rbp), %rax
  movq -488(%rbp), %rdx
  movq %rax, (%rdx)
  movq -528(%rbp), %rax
  addq $48, %rax
  movq %rax, -544(%rbp)
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -552(%rbp)
  movq -552(%rbp), %rax
  subq $1, %rax
  movq %rax, -560(%rbp)
  movq -544(%rbp), %rax
  movq -560(%rbp), %rdx
  movb %al, (%rdx)
  movq -560(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  movq -536(%rbp), %rax
  cmpq $1, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -568(%rbp)
  movq -568(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_i2s_loop_2
  jmp lm_enum_to_str_i2s_sign_2
lm_enum_to_str_i2s_sign_2:
  movq -496(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -576(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -584(%rbp)
  movq -584(%rbp), %rax
  testq %rax, %rax
  jne lm_enum_to_str_i2s_minus_2
  jmp lm_enum_to_str_i2s_done_2
lm_enum_to_str_i2s_minus_2:
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -592(%rbp)
  movq -592(%rbp), %rax
  subq $1, %rax
  movq %rax, -600(%rbp)
  movq $45, %rax
  movq -600(%rbp), %rdx
  movb %al, (%rdx)
  movq -600(%rbp), %rax
  movq -480(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_i2s_done_2
lm_enum_to_str_i2s_done_2:
  movq -480(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -608(%rbp)
  movq -472(%rbp), %rax
  subq -608(%rbp), %rax
  movq %rax, -616(%rbp)
  movq -464(%rbp), %rax
  addq $8, %rax
  movq %rax, -624(%rbp)
  movq -616(%rbp), %rax
  movq -624(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  addq $16, %rax
  movq %rax, -632(%rbp)
  movq -616(%rbp), %rax
  movq -632(%rbp), %rdx
  movq %rax, (%rdx)
  movq -464(%rbp), %rax
  addq $24, %rax
  movq %rax, -640(%rbp)
  movq -616(%rbp), %rax
  addq $1, %rax
  movq %rax, -648(%rbp)
  movq $184614912, %rax
  movq %rax, -656(%rbp)
  movq -464(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_enum_to_str_build_pay
lm_enum_to_str_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_enum_to_str:

.globl lm_list_set
lm_list_set:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $72, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
  movq %rdx, -64(%rbp)
lm_list_set_entry:
  movq -48(%rbp), %rax
  addq $16, %rax
  movq %rax, -72(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -80(%rbp)
  movq -56(%rbp), %rax
  imulq $8, %rax
  movq %rax, -88(%rbp)
  movq -80(%rbp), %rax
  addq -88(%rbp), %rax
  movq %rax, -96(%rbp)
  movq -64(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp lm_list_set_epilogue
lm_list_set_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_list_set:

.globl lm_list_to_str
lm_list_to_str:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $408, %rsp
  movq %rdi, -48(%rbp)
lm_list_to_str_entry:
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -56(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -64(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -72(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -80(%rbp)
  movq -48(%rbp), %rax
  addq $16, %rax
  movq %rax, -88(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -96(%rbp)
  leaq list_lbracket(%rip), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_loop
lm_list_to_str_loop:
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -104(%rbp)
  movq -104(%rbp), %rax
  cmpq -80(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -112(%rbp)
  movq -112(%rbp), %rax
  testq %rax, %rax
  jne lm_list_to_str_body
  jmp lm_list_to_str_done
lm_list_to_str_body:
  movq -104(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -120(%rbp)
  movq -120(%rbp), %rax
  testq %rax, %rax
  jne lm_list_to_str_elem
  jmp lm_list_to_str_sep
lm_list_to_str_next:
  movq -104(%rbp), %rax
  addq $1, %rax
  movq %rax, -128(%rbp)
  movq -128(%rbp), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_loop
lm_list_to_str_done:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -136(%rbp)
  movq -136(%rbp), %rdi
  leaq list_rbracket(%rip), %rsi
  call lm_str_concat
  mov -144(%rbp), rax
  movq -144(%rbp), %rax
  jmp lm_list_to_str_epilogue
lm_list_to_str_sep:
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -152(%rbp)
  movq -152(%rbp), %rdi
  leaq list_comma(%rip), %rsi
  call lm_str_concat
  mov -160(%rbp), rax
  movq -160(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_elem
lm_list_to_str_elem:
  movq -104(%rbp), %rax
  imulq $8, %rax
  movq %rax, -168(%rbp)
  movq -96(%rbp), %rax
  addq -168(%rbp), %rax
  movq %rax, -176(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rax
  cmpq $65536, %rax
  setb %al
  movzbq %al, %rax
  movq %rax, -192(%rbp)
  movq -192(%rbp), %rax
  testq %rax, %rax
  jne lm_list_to_str_e_num
  jmp lm_list_to_str_e_ptr
lm_list_to_str_e_num:
  movq $9, %rax
  movq $0, %rdi
  movq $64, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -200(%rbp)
  movq $11, %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  addq $63, %rax
  movq %rax, -208(%rbp)
  movq $0, %rax
  movq -208(%rbp), %rdx
  movb %al, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -216(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -208(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -224(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -232(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq -184(%rbp), %rax
  cmpq $0, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -240(%rbp)
  movq -240(%rbp), %rax
  testq %rax, %rax
  jne lm_list_to_str_i2s_neg_3
  jmp lm_list_to_str_i2s_pos_3
lm_list_to_str_e_ptr:
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -248(%rbp)
  movq -248(%rbp), %rax
  cmpq $1162761549, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -256(%rbp)
  movq -256(%rbp), %rax
  testq %rax, %rax
  jne lm_list_to_str_e_enum
  jmp lm_list_to_str_e_str
lm_list_to_str_e_done:
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -264(%rbp)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -272(%rbp)
  movq -272(%rbp), %rdi
  movq -264(%rbp), %rsi
  call lm_str_concat
  mov -280(%rbp), rax
  movq -280(%rbp), %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_next
lm_list_to_str_i2s_neg_3:
  movq $1, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  negq %rax
  movq %rax, -288(%rbp)
  movq -288(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_i2s_loop_3
lm_list_to_str_i2s_pos_3:
  movq $0, %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -184(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_i2s_loop_3
lm_list_to_str_i2s_loop_3:
  movq -224(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -296(%rbp)
  movq -296(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rdx, -304(%rbp)
  movq -296(%rbp), %rax
  cqto
  movq $10, %rcx
  idivq %rcx
  movq %rax, -312(%rbp)
  movq -312(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  movq -304(%rbp), %rax
  addq $48, %rax
  movq %rax, -320(%rbp)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -328(%rbp)
  movq -328(%rbp), %rax
  subq $1, %rax
  movq %rax, -336(%rbp)
  movq -320(%rbp), %rax
  movq -336(%rbp), %rdx
  movb %al, (%rdx)
  movq -336(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -312(%rbp), %rax
  cmpq $1, %rax
  setge %al
  movzbq %al, %rax
  movq %rax, -344(%rbp)
  movq -344(%rbp), %rax
  testq %rax, %rax
  jne lm_list_to_str_i2s_loop_3
  jmp lm_list_to_str_i2s_sign_3
lm_list_to_str_i2s_sign_3:
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -352(%rbp)
  movq -352(%rbp), %rax
  cmpq $1, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -360(%rbp)
  movq -360(%rbp), %rax
  testq %rax, %rax
  jne lm_list_to_str_i2s_minus_3
  jmp lm_list_to_str_i2s_done_3
lm_list_to_str_i2s_minus_3:
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rax
  subq $1, %rax
  movq %rax, -376(%rbp)
  movq $45, %rax
  movq -376(%rbp), %rdx
  movb %al, (%rdx)
  movq -376(%rbp), %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_i2s_done_3
lm_list_to_str_i2s_done_3:
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -384(%rbp)
  movq -208(%rbp), %rax
  subq -384(%rbp), %rax
  movq %rax, -392(%rbp)
  movq -200(%rbp), %rax
  addq $8, %rax
  movq %rax, -400(%rbp)
  movq -392(%rbp), %rax
  movq -400(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  addq $16, %rax
  movq %rax, -408(%rbp)
  movq -392(%rbp), %rax
  movq -408(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  addq $24, %rax
  movq %rax, -416(%rbp)
  movq -392(%rbp), %rax
  addq $1, %rax
  movq %rax, -424(%rbp)
  movq $184614912, %rax
  movq %rax, -432(%rbp)
  movq -200(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_e_done
lm_list_to_str_e_enum:
  movq -184(%rbp), %rdi
  call lm_enum_to_str
  mov -440(%rbp), rax
  movq -440(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_e_done
lm_list_to_str_e_str:
  movq -184(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_list_to_str_e_done
lm_list_to_str_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_list_to_str:

.globl lm_str_alloc
lm_str_alloc:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $72, %rsp
  movq %rdi, -48(%rbp)
lm_str_alloc_entry:
  movq -48(%rbp), %rax
  addq $25, %rax
  movq %rax, -56(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq -56(%rbp), %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -64(%rbp)
  movq $11, %rax
  movq -64(%rbp), %rdx
  movl %eax, (%rdx)
  movq -64(%rbp), %rax
  addq $4, %rax
  movq %rax, -72(%rbp)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movl %eax, (%rdx)
  movq -64(%rbp), %rax
  addq $8, %rax
  movq %rax, -80(%rbp)
  movq $0, %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  addq $16, %rax
  movq %rax, -88(%rbp)
  movq -48(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  addq $24, %rax
  movq %rax, -96(%rbp)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movb %al, (%rdx)
  movq -64(%rbp), %rax
  jmp lm_str_alloc_epilogue
lm_str_alloc_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_str_alloc:

.globl lm_dict_new
lm_dict_new:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $104, %rsp
lm_dict_new_entry:
  movq $9, %rax
  movq $0, %rdi
  movq $32, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -48(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq $256, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -56(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq $256, %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -64(%rbp)
  movq $0, %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  addq $8, %rax
  movq %rax, -72(%rbp)
  movq $32, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  addq $16, %rax
  movq %rax, -80(%rbp)
  movq -56(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  addq $24, %rax
  movq %rax, -88(%rbp)
  movq -64(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_dict_new_init_loop
lm_dict_new_init_loop:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -104(%rbp)
  movq -104(%rbp), %rax
  cmpq $32, %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -112(%rbp)
  movq -112(%rbp), %rax
  testq %rax, %rax
  jne lm_dict_new_init_body
  jmp lm_dict_new_init_done
lm_dict_new_init_body:
  movq -104(%rbp), %rax
  imulq $8, %rax
  movq %rax, -120(%rbp)
  movq -56(%rbp), %rax
  addq -120(%rbp), %rax
  movq %rax, -128(%rbp)
  movq $0, %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -104(%rbp), %rax
  addq $1, %rax
  movq %rax, -136(%rbp)
  movq -136(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_dict_new_init_loop
lm_dict_new_init_done:
  movq -48(%rbp), %rax
  jmp lm_dict_new_epilogue
lm_dict_new_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_dict_new:

.globl lm_dict_set
lm_dict_set:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $184, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
  movq %rdx, -64(%rbp)
lm_dict_set_entry:
  movq -48(%rbp), %rax
  addq $16, %rax
  movq %rax, -72(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -80(%rbp)
  movq -48(%rbp), %rax
  addq $24, %rax
  movq %rax, -88(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -96(%rbp)
  movq -48(%rbp), %rax
  addq $8, %rax
  movq %rax, -104(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -112(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_dict_set_loop
lm_dict_set_loop:
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -128(%rbp)
  movq -128(%rbp), %rax
  cmpq -112(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -136(%rbp)
  movq -136(%rbp), %rax
  testq %rax, %rax
  jne lm_dict_set_check
  jmp lm_dict_set_done
lm_dict_set_check:
  movq -128(%rbp), %rax
  imulq $8, %rax
  movq %rax, -144(%rbp)
  movq -80(%rbp), %rax
  addq -144(%rbp), %rax
  movq %rax, -152(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -160(%rbp)
  movq -160(%rbp), %rdi
  movq -56(%rbp), %rsi
  call lm_key_eq
  mov -168(%rbp), rax
  movq -160(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -176(%rbp)
  movq -168(%rbp), %rax
  orq -176(%rbp), %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rax
  testq %rax, %rax
  jne lm_dict_set_store
  jmp lm_dict_set_next
lm_dict_set_store:
  movq -56(%rbp), %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  addq -144(%rbp), %rax
  movq %rax, -192(%rbp)
  movq -64(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  testq %rax, %rax
  jne lm_dict_set_inc_cnt
  jmp lm_dict_set_store_ret
lm_dict_set_next:
  movq -128(%rbp), %rax
  addq $1, %rax
  movq %rax, -200(%rbp)
  movq -200(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_dict_set_loop
lm_dict_set_done:
  movq $0, %rax
  jmp lm_dict_set_epilogue
lm_dict_set_inc_cnt:
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -208(%rbp)
  movq -208(%rbp), %rax
  addq $1, %rax
  movq %rax, -216(%rbp)
  movq -216(%rbp), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_dict_set_store_ret
lm_dict_set_store_ret:
  movq $0, %rax
  jmp lm_dict_set_epilogue
lm_dict_set_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_dict_set:

.globl lm_dict_get
lm_dict_get:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $168, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
lm_dict_get_entry:
  movq -48(%rbp), %rax
  addq $16, %rax
  movq %rax, -64(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -72(%rbp)
  movq -48(%rbp), %rax
  addq $24, %rax
  movq %rax, -80(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -88(%rbp)
  movq -48(%rbp), %rax
  addq $8, %rax
  movq %rax, -96(%rbp)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -104(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -112(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_dict_get_loop
lm_dict_get_loop:
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -120(%rbp)
  movq -120(%rbp), %rax
  cmpq -104(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -128(%rbp)
  movq -128(%rbp), %rax
  testq %rax, %rax
  jne lm_dict_get_check
  jmp lm_dict_get_not_found
lm_dict_get_check:
  movq -120(%rbp), %rax
  imulq $8, %rax
  movq %rax, -136(%rbp)
  movq -72(%rbp), %rax
  addq -136(%rbp), %rax
  movq %rax, -144(%rbp)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -152(%rbp)
  movq -152(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -160(%rbp)
  movq -160(%rbp), %rax
  testq %rax, %rax
  jne lm_dict_get_next
  jmp lm_dict_get_dict_get_cmp
lm_dict_get_found:
  movq -88(%rbp), %rax
  addq -136(%rbp), %rax
  movq %rax, -168(%rbp)
  movq -168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -176(%rbp)
  movq -176(%rbp), %rax
  jmp lm_dict_get_epilogue
lm_dict_get_next:
  movq -120(%rbp), %rax
  addq $1, %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_dict_get_loop
lm_dict_get_not_found:
  movq $0, %rax
  jmp lm_dict_get_epilogue
lm_dict_get_dict_get_cmp:
  movq -152(%rbp), %rdi
  movq -56(%rbp), %rsi
  call lm_key_eq
  mov -192(%rbp), rax
  movq -192(%rbp), %rax
  testq %rax, %rax
  jne lm_dict_get_found
  jmp lm_dict_get_next
lm_dict_get_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_dict_get:

.globl lm_dict_has
lm_dict_has:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $136, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
lm_dict_has_entry:
  movq -48(%rbp), %rax
  addq $16, %rax
  movq %rax, -64(%rbp)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -72(%rbp)
  movq -48(%rbp), %rax
  addq $8, %rax
  movq %rax, -80(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -88(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -96(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_dict_has_loop
lm_dict_has_loop:
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -104(%rbp)
  movq -104(%rbp), %rax
  cmpq -88(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -112(%rbp)
  movq -112(%rbp), %rax
  testq %rax, %rax
  jne lm_dict_has_check
  jmp lm_dict_has_not_found
lm_dict_has_check:
  movq -104(%rbp), %rax
  imulq $8, %rax
  movq %rax, -120(%rbp)
  movq -72(%rbp), %rax
  addq -120(%rbp), %rax
  movq %rax, -128(%rbp)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -136(%rbp)
  movq -136(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -144(%rbp)
  movq -144(%rbp), %rax
  testq %rax, %rax
  jne lm_dict_has_next
  jmp lm_dict_has_dict_has_cmp
lm_dict_has_found:
  movq $1, %rax
  jmp lm_dict_has_epilogue
lm_dict_has_next:
  movq -104(%rbp), %rax
  addq $1, %rax
  movq %rax, -152(%rbp)
  movq -152(%rbp), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_dict_has_loop
lm_dict_has_not_found:
  movq $0, %rax
  jmp lm_dict_has_epilogue
lm_dict_has_dict_has_cmp:
  movq -136(%rbp), %rdi
  movq -56(%rbp), %rsi
  call lm_key_eq
  mov -160(%rbp), rax
  movq -160(%rbp), %rax
  testq %rax, %rax
  jne lm_dict_has_found
  jmp lm_dict_has_next
lm_dict_has_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_dict_has:

.globl lm_dict_items
lm_dict_items:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $200, %rsp
  movq %rdi, -48(%rbp)
lm_dict_items_entry:
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -56(%rbp)
  movq -56(%rbp), %rdi
  call lm_list_new
  mov -64(%rbp), rax
  movq -48(%rbp), %rax
  addq $8, %rax
  movq %rax, -72(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -80(%rbp)
  movq -48(%rbp), %rax
  addq $16, %rax
  movq %rax, -88(%rbp)
  movq -88(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -96(%rbp)
  movq -48(%rbp), %rax
  addq $24, %rax
  movq %rax, -104(%rbp)
  movq -104(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -112(%rbp)
  # Bump Allocation: 8 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -120(%rbp)
  addq $8, %rax
  movq %rax, heap_ptr(%rip)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_dict_items_loop
lm_dict_items_loop:
  movq -120(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -128(%rbp)
  movq -128(%rbp), %rax
  cmpq -80(%rbp), %rax
  setl %al
  movzbq %al, %rax
  movq %rax, -136(%rbp)
  movq -136(%rbp), %rax
  testq %rax, %rax
  jne lm_dict_items_check
  jmp lm_dict_items_done
lm_dict_items_check:
  movq -128(%rbp), %rax
  imulq $8, %rax
  movq %rax, -144(%rbp)
  movq -96(%rbp), %rax
  addq -144(%rbp), %rax
  movq %rax, -152(%rbp)
  movq -152(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -160(%rbp)
  movq -160(%rbp), %rax
  cmpq $0, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -168(%rbp)
  movq -168(%rbp), %rax
  testq %rax, %rax
  jne lm_dict_items_next
  jmp lm_dict_items_add_item
lm_dict_items_add_item:
  movq -112(%rbp), %rax
  addq -144(%rbp), %rax
  movq %rax, -176(%rbp)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -184(%rbp)
  movq $2, %rdi
  call lm_tuple_new
  mov -192(%rbp), rax
  movq -192(%rbp), %rdi
  movq $0, %rsi
  movq -160(%rbp), %rdx
  call lm_tuple_set
  mov -200(%rbp), rax
  movq -192(%rbp), %rdi
  movq $1, %rsi
  movq -184(%rbp), %rdx
  call lm_tuple_set
  mov -208(%rbp), rax
  movq -64(%rbp), %rdi
  movq -192(%rbp), %rsi
  call lm_list_append
  mov -216(%rbp), rax
  jmp lm_dict_items_next
lm_dict_items_next:
  movq -128(%rbp), %rax
  addq $1, %rax
  movq %rax, -224(%rbp)
  movq -224(%rbp), %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  jmp lm_dict_items_loop
lm_dict_items_done:
  movq -64(%rbp), %rax
  jmp lm_dict_items_epilogue
lm_dict_items_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_dict_items:

.globl lm_tuple_new
lm_tuple_new:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $40, %rsp
  movq %rdi, -48(%rbp)
lm_tuple_new_entry:
  movq -48(%rbp), %rax
  addq $1, %rax
  movq %rax, -56(%rbp)
  movq -56(%rbp), %rax
  imulq $8, %rax
  movq %rax, -64(%rbp)
  movq $9, %rax
  movq $0, %rdi
  movq -64(%rbp), %rsi
  movq $3, %rdx
  movq $34, %r10
  movq $18446744073709551615, %r8
  movq $0, %r9
  syscall
  movq %rax, -72(%rbp)
  movq -48(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -72(%rbp), %rax
  jmp lm_tuple_new_epilogue
lm_tuple_new_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_tuple_new:

.globl lm_tuple_get
lm_tuple_get:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $56, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
lm_tuple_get_entry:
  movq -56(%rbp), %rax
  addq $1, %rax
  movq %rax, -64(%rbp)
  movq -64(%rbp), %rax
  imulq $8, %rax
  movq %rax, -72(%rbp)
  movq -48(%rbp), %rax
  addq -72(%rbp), %rax
  movq %rax, -80(%rbp)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -88(%rbp)
  movq -88(%rbp), %rax
  jmp lm_tuple_get_epilogue
lm_tuple_get_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_tuple_get:

.globl lm_tuple_set
lm_tuple_set:
  .cfi_startproc
  pushq %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq %rsp, %rbp
  .cfi_def_cfa_register 6
  pushq %rbx
  .cfi_offset 3, -24
  pushq %r12
  .cfi_offset 12, -32
  pushq %r13
  .cfi_offset 13, -40
  pushq %r14
  .cfi_offset 14, -48
  pushq %r15
  .cfi_offset 15, -56
  subq $56, %rsp
  movq %rdi, -48(%rbp)
  movq %rsi, -56(%rbp)
  movq %rdx, -64(%rbp)
lm_tuple_set_entry:
  movq -56(%rbp), %rax
  addq $1, %rax
  movq %rax, -72(%rbp)
  movq -72(%rbp), %rax
  imulq $8, %rax
  movq %rax, -80(%rbp)
  movq -48(%rbp), %rax
  addq -80(%rbp), %rax
  movq %rax, -88(%rbp)
  movq -64(%rbp), %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq $0, %rax
  jmp lm_tuple_set_epilogue
lm_tuple_set_epilogue:
  leaq -40(%rbp), %rsp
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
  popq %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.Lfunc_end_lm_tuple_set:

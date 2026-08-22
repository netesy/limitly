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
  .byte 61
  .byte 61
  .byte 61
  .byte 32
  .byte 83
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 97
  .byte 108
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 84
  .byte 101
  .byte 115
  .byte 116
  .byte 115
  .byte 32
  .byte 61
  .byte 61
  .byte 61
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
  .byte 39
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 39
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 10
  .byte 45
  .byte 45
  .byte 45
  .byte 32
  .byte 84
  .byte 101
  .byte 115
  .byte 116
  .byte 32
  .byte 49
  .byte 58
  .byte 32
  .byte 66
  .byte 97
  .byte 115
  .byte 105
  .byte 99
  .byte 32
  .byte 83
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 97
  .byte 108
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
  .byte 0
.align 8
str_hdr_2:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 41
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 41
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 10
  .byte 45
  .byte 45
  .byte 45
  .byte 32
  .byte 84
  .byte 101
  .byte 115
  .byte 116
  .byte 32
  .byte 50
  .byte 58
  .byte 32
  .byte 67
  .byte 111
  .byte 109
  .byte 112
  .byte 108
  .byte 101
  .byte 120
  .byte 32
  .byte 83
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 97
  .byte 108
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
  .byte 0
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
  .byte 40
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 40
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 10
  .byte 45
  .byte 45
  .byte 45
  .byte 32
  .byte 84
  .byte 101
  .byte 115
  .byte 116
  .byte 32
  .byte 51
  .byte 58
  .byte 32
  .byte 78
  .byte 101
  .byte 115
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 83
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 97
  .byte 108
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
  .byte 0
.align 8
str_hdr_4:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 38
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 38
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 10
  .byte 45
  .byte 45
  .byte 45
  .byte 32
  .byte 84
  .byte 101
  .byte 115
  .byte 116
  .byte 32
  .byte 52
  .byte 58
  .byte 32
  .byte 77
  .byte 105
  .byte 120
  .byte 101
  .byte 100
  .byte 32
  .byte 80
  .byte 114
  .byte 105
  .byte 109
  .byte 105
  .byte 116
  .byte 105
  .byte 118
  .byte 101
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 37
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 37
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 10
  .byte 45
  .byte 45
  .byte 45
  .byte 32
  .byte 84
  .byte 101
  .byte 115
  .byte 116
  .byte 32
  .byte 53
  .byte 58
  .byte 32
  .byte 86
  .byte 97
  .byte 114
  .byte 105
  .byte 111
  .byte 117
  .byte 115
  .byte 32
  .byte 70
  .byte 105
  .byte 101
  .byte 108
  .byte 100
  .byte 32
  .byte 67
  .byte 111
  .byte 117
  .byte 110
  .byte 116
  .byte 115
  .byte 32
  .byte 45
  .byte 45
  .byte 45
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
  .byte 39
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 39
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 83
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 97
  .byte 108
  .byte 32
  .byte 116
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 100
  .byte 101
  .byte 99
  .byte 108
  .byte 97
  .byte 114
  .byte 97
  .byte 116
  .byte 105
  .byte 111
  .byte 110
  .byte 115
  .byte 32
  .byte 99
  .byte 111
  .byte 109
  .byte 112
  .byte 108
  .byte 101
  .byte 116
  .byte 101
  .byte 100
  .byte 33
  .byte 0
.align 8
str_hdr_7:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 68
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 68
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 78
  .byte 111
  .byte 116
  .byte 101
  .byte 58
  .byte 32
  .byte 83
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 97
  .byte 108
  .byte 32
  .byte 116
  .byte 121
  .byte 112
  .byte 101
  .byte 115
  .byte 32
  .byte 97
  .byte 114
  .byte 101
  .byte 32
  .byte 110
  .byte 111
  .byte 119
  .byte 32
  .byte 102
  .byte 117
  .byte 108
  .byte 108
  .byte 121
  .byte 32
  .byte 105
  .byte 109
  .byte 112
  .byte 108
  .byte 101
  .byte 109
  .byte 101
  .byte 110
  .byte 116
  .byte 101
  .byte 100
  .byte 32
  .byte 105
  .byte 110
  .byte 32
  .byte 116
  .byte 104
  .byte 101
  .byte 32
  .byte 116
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 115
  .byte 121
  .byte 115
  .byte 116
  .byte 101
  .byte 109
  .byte 46
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
  .byte 46
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 46
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 10
  .byte 45
  .byte 45
  .byte 45
  .byte 32
  .byte 84
  .byte 101
  .byte 115
  .byte 116
  .byte 32
  .byte 54
  .byte 58
  .byte 32
  .byte 83
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 97
  .byte 108
  .byte 32
  .byte 84
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 67
  .byte 111
  .byte 109
  .byte 112
  .byte 97
  .byte 116
  .byte 105
  .byte 98
  .byte 105
  .byte 108
  .byte 105
  .byte 116
  .byte 121
  .byte 32
  .byte 45
  .byte 45
  .byte 45
  .byte 0
.align 8
str_hdr_9:
  .byte 11
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 8
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 8
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 74
  .byte 111
  .byte 104
  .byte 110
  .byte 32
  .byte 68
  .byte 111
  .byte 101
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
  .byte 43
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 43
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 0
  .byte 83
  .byte 116
  .byte 114
  .byte 117
  .byte 99
  .byte 116
  .byte 117
  .byte 114
  .byte 97
  .byte 108
  .byte 32
  .byte 116
  .byte 121
  .byte 112
  .byte 101
  .byte 32
  .byte 99
  .byte 111
  .byte 109
  .byte 112
  .byte 97
  .byte 116
  .byte 105
  .byte 98
  .byte 105
  .byte 108
  .byte 105
  .byte 116
  .byte 121
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
  .byte 33
  .byte 0
.align 8
str_hdr_11:
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
  .byte 78
  .byte 97
  .byte 109
  .byte 101
  .byte 58
  .byte 32
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
  subq $1176, %rsp
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
  jmp main_block_0
main_block_0:
  leaq str_hdr_0(%rip), %rax
  movq -48(%rbp), %rdx
  movq %rax, (%rdx)
  movq -48(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -336(%rbp)
  movq -336(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -344(%rbp)
  movq -344(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_9383
  jmp main_pr_str_0_9383
main_pr_nil_0_9383:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -352(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -352(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -360(%rbp)
  jmp main_pr_next_0_9383
main_pr_str_0_9383:
  movq -336(%rbp), %rax
  addq $8, %rax
  movq %rax, -368(%rbp)
  movq -368(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -376(%rbp)
  movq -336(%rbp), %rax
  addq $24, %rax
  movq %rax, -384(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -384(%rbp), %rsi
  movq -376(%rbp), %rdx
  syscall
  movq %rax, -392(%rbp)
  jmp main_pr_next_0_9383
main_pr_next_0_9383:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -400(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -400(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -408(%rbp)
  movq $0, %rax
  movq -56(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_1(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -416(%rbp)
  movq -416(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -424(%rbp)
  movq -424(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_886
  jmp main_pr_str_0_886
main_pr_nil_0_886:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -432(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -432(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -440(%rbp)
  jmp main_pr_next_0_886
main_pr_str_0_886:
  movq -416(%rbp), %rax
  addq $8, %rax
  movq %rax, -448(%rbp)
  movq -448(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -456(%rbp)
  movq -416(%rbp), %rax
  addq $24, %rax
  movq %rax, -464(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -464(%rbp), %rsi
  movq -456(%rbp), %rdx
  syscall
  movq %rax, -472(%rbp)
  jmp main_pr_next_0_886
main_pr_next_0_886:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -480(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -480(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -488(%rbp)
  movq $0, %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_2(%rip), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -496(%rbp)
  movq -496(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -504(%rbp)
  movq -504(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_2777
  jmp main_pr_str_0_2777
main_pr_nil_0_2777:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -512(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -512(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -520(%rbp)
  jmp main_pr_next_0_2777
main_pr_str_0_2777:
  movq -496(%rbp), %rax
  addq $8, %rax
  movq %rax, -528(%rbp)
  movq -528(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -536(%rbp)
  movq -496(%rbp), %rax
  addq $24, %rax
  movq %rax, -544(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -544(%rbp), %rsi
  movq -536(%rbp), %rdx
  syscall
  movq %rax, -552(%rbp)
  jmp main_pr_next_0_2777
main_pr_next_0_2777:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -560(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -560(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -568(%rbp)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_3(%rip), %rax
  movq -96(%rbp), %rdx
  movq %rax, (%rdx)
  movq -96(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -576(%rbp)
  movq -576(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -584(%rbp)
  movq -584(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6915
  jmp main_pr_str_0_6915
main_pr_nil_0_6915:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -592(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -592(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -600(%rbp)
  jmp main_pr_next_0_6915
main_pr_str_0_6915:
  movq -576(%rbp), %rax
  addq $8, %rax
  movq %rax, -608(%rbp)
  movq -608(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -616(%rbp)
  movq -576(%rbp), %rax
  addq $24, %rax
  movq %rax, -624(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -624(%rbp), %rsi
  movq -616(%rbp), %rdx
  syscall
  movq %rax, -632(%rbp)
  jmp main_pr_next_0_6915
main_pr_next_0_6915:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -640(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -640(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -648(%rbp)
  movq $0, %rax
  movq -104(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_4(%rip), %rax
  movq -112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -112(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -656(%rbp)
  movq -656(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -664(%rbp)
  movq -664(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_7793
  jmp main_pr_str_0_7793
main_pr_nil_0_7793:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -672(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -672(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -680(%rbp)
  jmp main_pr_next_0_7793
main_pr_str_0_7793:
  movq -656(%rbp), %rax
  addq $8, %rax
  movq %rax, -688(%rbp)
  movq -688(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -696(%rbp)
  movq -656(%rbp), %rax
  addq $24, %rax
  movq %rax, -704(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -704(%rbp), %rsi
  movq -696(%rbp), %rdx
  syscall
  movq %rax, -712(%rbp)
  jmp main_pr_next_0_7793
main_pr_next_0_7793:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -720(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -720(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -728(%rbp)
  movq $0, %rax
  movq -120(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_5(%rip), %rax
  movq -128(%rbp), %rdx
  movq %rax, (%rdx)
  movq -128(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -736(%rbp)
  movq -736(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -744(%rbp)
  movq -744(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_8335
  jmp main_pr_str_0_8335
main_pr_nil_0_8335:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -752(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -752(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -760(%rbp)
  jmp main_pr_next_0_8335
main_pr_str_0_8335:
  movq -736(%rbp), %rax
  addq $8, %rax
  movq %rax, -768(%rbp)
  movq -768(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -776(%rbp)
  movq -736(%rbp), %rax
  addq $24, %rax
  movq %rax, -784(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -784(%rbp), %rsi
  movq -776(%rbp), %rdx
  syscall
  movq %rax, -792(%rbp)
  jmp main_pr_next_0_8335
main_pr_next_0_8335:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -800(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -800(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -808(%rbp)
  movq $0, %rax
  movq -136(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_6(%rip), %rax
  movq -144(%rbp), %rdx
  movq %rax, (%rdx)
  movq -144(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -816(%rbp)
  movq -816(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -824(%rbp)
  movq -824(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_5386
  jmp main_pr_str_0_5386
main_pr_nil_0_5386:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -832(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -832(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -840(%rbp)
  jmp main_pr_next_0_5386
main_pr_str_0_5386:
  movq -816(%rbp), %rax
  addq $8, %rax
  movq %rax, -848(%rbp)
  movq -848(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -856(%rbp)
  movq -816(%rbp), %rax
  addq $24, %rax
  movq %rax, -864(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -864(%rbp), %rsi
  movq -856(%rbp), %rdx
  syscall
  movq %rax, -872(%rbp)
  jmp main_pr_next_0_5386
main_pr_next_0_5386:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -880(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -880(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -888(%rbp)
  movq $0, %rax
  movq -152(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_7(%rip), %rax
  movq -160(%rbp), %rdx
  movq %rax, (%rdx)
  movq -160(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -896(%rbp)
  movq -896(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -904(%rbp)
  movq -904(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_492
  jmp main_pr_str_0_492
main_pr_nil_0_492:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -912(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -912(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -920(%rbp)
  jmp main_pr_next_0_492
main_pr_str_0_492:
  movq -896(%rbp), %rax
  addq $8, %rax
  movq %rax, -928(%rbp)
  movq -928(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -936(%rbp)
  movq -896(%rbp), %rax
  addq $24, %rax
  movq %rax, -944(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -944(%rbp), %rsi
  movq -936(%rbp), %rdx
  syscall
  movq %rax, -952(%rbp)
  jmp main_pr_next_0_492
main_pr_next_0_492:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -960(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -960(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -968(%rbp)
  movq $0, %rax
  movq -168(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_8(%rip), %rax
  movq -176(%rbp), %rdx
  movq %rax, (%rdx)
  movq -176(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -976(%rbp)
  movq -976(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -984(%rbp)
  movq -984(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_6649
  jmp main_pr_str_0_6649
main_pr_nil_0_6649:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -992(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -992(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1000(%rbp)
  jmp main_pr_next_0_6649
main_pr_str_0_6649:
  movq -976(%rbp), %rax
  addq $8, %rax
  movq %rax, -1008(%rbp)
  movq -1008(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1016(%rbp)
  movq -976(%rbp), %rax
  addq $24, %rax
  movq %rax, -1024(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1024(%rbp), %rsi
  movq -1016(%rbp), %rdx
  syscall
  movq %rax, -1032(%rbp)
  jmp main_pr_next_0_6649
main_pr_next_0_6649:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1040(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1040(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1048(%rbp)
  movq $0, %rax
  movq -184(%rbp), %rdx
  movq %rax, (%rdx)
  # Bump Allocation: 16 bytes
  movq heap_ptr(%rip), %rax
  movq %rax, -1056(%rbp)
  addq $16, %rax
  movq %rax, heap_ptr(%rip)
  movq -1056(%rbp), %rax
  movq -192(%rbp), %rdx
  movq %rax, (%rdx)
  movq -192(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1064(%rbp)
  movq -1064(%rbp), %rax
  movq -200(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_9(%rip), %rax
  movq -208(%rbp), %rdx
  movq %rax, (%rdx)
  movq -208(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1072(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1080(%rbp)
  movq -1080(%rbp), %rax
  addq $0, %rax
  movq %rax, -1088(%rbp)
  movq -1072(%rbp), %rax
  movq -1088(%rbp), %rdx
  movq %rax, (%rdx)
  movq $30, %rax
  movq -216(%rbp), %rdx
  movq %rax, (%rdx)
  movq -216(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1096(%rbp)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1104(%rbp)
  movq -1104(%rbp), %rax
  addq $8, %rax
  movq %rax, -1112(%rbp)
  movq -1096(%rbp), %rax
  movq -1112(%rbp), %rdx
  movq %rax, (%rdx)
  movq -200(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1120(%rbp)
  movq -1120(%rbp), %rdi
  call print_name
  mov -1128(%rbp), rax
  movq -1128(%rbp), %rax
  movq -224(%rbp), %rdx
  movq %rax, (%rdx)
  leaq str_hdr_10(%rip), %rax
  movq -232(%rbp), %rdx
  movq %rax, (%rdx)
  movq -232(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1136(%rbp)
  movq -1136(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -1144(%rbp)
  movq -1144(%rbp), %rax
  testq %rax, %rax
  jne main_pr_nil_0_1421
  jmp main_pr_str_0_1421
main_pr_nil_0_1421:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -1152(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1152(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -1160(%rbp)
  jmp main_pr_next_0_1421
main_pr_str_0_1421:
  movq -1136(%rbp), %rax
  addq $8, %rax
  movq %rax, -1168(%rbp)
  movq -1168(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -1176(%rbp)
  movq -1136(%rbp), %rax
  addq $24, %rax
  movq %rax, -1184(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1184(%rbp), %rsi
  movq -1176(%rbp), %rdx
  syscall
  movq %rax, -1192(%rbp)
  jmp main_pr_next_0_1421
main_pr_next_0_1421:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -1200(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -1200(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -1208(%rbp)
  movq $0, %rax
  movq -240(%rbp), %rdx
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

.globl print_name
print_name:
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
  movq %rdi, -48(%rbp)
print_name_entry:
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
  jmp print_name_block_0
print_name_block_0:
  leaq str_hdr_11(%rip), %rax
  movq -64(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -176(%rbp)
  movq -176(%rbp), %rax
  addq $0, %rax
  movq %rax, -184(%rbp)
  movq -184(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -192(%rbp)
  movq -192(%rbp), %rax
  movq -72(%rbp), %rdx
  movq %rax, (%rdx)
  movq -64(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -200(%rbp)
  movq -72(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -208(%rbp)
  movq -200(%rbp), %rdi
  movq -208(%rbp), %rsi
  call lm_str_concat
  mov -216(%rbp), rax
  movq -216(%rbp), %rax
  movq -80(%rbp), %rdx
  movq %rax, (%rdx)
  movq -80(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -224(%rbp)
  movq -224(%rbp), %rax
  cmpq $2, %rax
  sete %al
  movzbq %al, %rax
  movq %rax, -232(%rbp)
  movq -232(%rbp), %rax
  testq %rax, %rax
  jne print_name_pr_nil_0_2362
  jmp print_name_pr_str_0_2362
print_name_pr_nil_0_2362:
  leaq str_nil(%rip), %rax
  addq $24, %rax
  movq %rax, -240(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -240(%rbp), %rsi
  movq $3, %rdx
  syscall
  movq %rax, -248(%rbp)
  jmp print_name_pr_next_0_2362
print_name_pr_str_0_2362:
  movq -224(%rbp), %rax
  addq $8, %rax
  movq %rax, -256(%rbp)
  movq -256(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -264(%rbp)
  movq -224(%rbp), %rax
  addq $24, %rax
  movq %rax, -272(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -272(%rbp), %rsi
  movq -264(%rbp), %rdx
  syscall
  movq %rax, -280(%rbp)
  jmp print_name_pr_next_0_2362
print_name_pr_next_0_2362:
  leaq nl(%rip), %rax
  addq $24, %rax
  movq %rax, -288(%rbp)
  movq $1, %rax
  movq $1, %rdi
  movq -288(%rbp), %rsi
  movq $1, %rdx
  syscall
  movq %rax, -296(%rbp)
  movq $0, %rax
  movq -88(%rbp), %rdx
  movq %rax, (%rdx)
  movq -56(%rbp), %rax
  movq (%rax), %rax
  movq %rax, -304(%rbp)
  movq -304(%rbp), %rax
  jmp print_name_epilogue
print_name_epilogue:
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
.Lfunc_end_print_name:

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
